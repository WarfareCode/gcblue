/**
**  @file SelfPreservation.cpp
*/
/*
**  Copyright (c) 2014, GCBLUE PROJECT
**  All rights reserved.
**
**  Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
**
**  1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
**
**  2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the 
**     documentation and/or other materials provided with the distribution.
**
**  3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from 
**     this software without specific prior written permission.
**
**  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT 
**  NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE 
**  COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
**  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
**  HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING 
**  IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "stdwx.h"

#ifndef WX_PRECOMP
#include "wx/wx.h" 
#endif

#include "ai/SelfPreservation.h"
#include "scriptinterface/tcPlatformInterface.h"
#include "tcGameStream.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif 

using namespace ai;
using scriptinterface::tcPlatformInterface;



/**
* Read from stream
*/
tcGameStream& SelfPreservation::operator<<(tcGameStream& stream)
{
    Task::operator<<(stream);

    stream >> haveAltitudeControl;

    return stream;
}

/**
* Write to stream
*/
tcGameStream& SelfPreservation::operator>>(tcGameStream& stream)
{
    Task::operator>>(stream);

    stream << haveAltitudeControl;

    return stream; 
}


/**
* version for air objects
*/
void SelfPreservation::UpdateAir(double t)
{
    tcPlatformInterface platformInterface = GetPlatformInterface();
    
    // avoid crashing
    float alt_m = platformInterface.GetAltitude();
    float terrain_m = platformInterface.GetTerrainElevation();
    
    if (alt_m < terrain_m + 50)
    {
        if (!haveAltitudeControl)
        {
            haveAltitudeControl = Write("Altitude", "");
        }
        if (haveAltitudeControl)
        {
            platformInterface.SetAltitude(terrain_m + 70);
        }
    }
    else
    {
        if (haveAltitudeControl)
        {
            Erase("Altitude");
            haveAltitudeControl = false;
        }
    }
    
}


void SelfPreservation::Update(double t)
{
    if (!IsReadyForUpdate(t)) return;
    
    tcPlatformInterface platformInterface = GetPlatformInterface();
    
    if (platformInterface.IsAir())
    {
        UpdateAir(t);
    }

    FinishUpdate(t);
}

SelfPreservation::SelfPreservation(tcPlatformObject* platform_, Blackboard* bb, 
        long id_, double priority_, int attributes_, const std::string& taskName_)
: Task(platform_, bb, id_, priority_, attributes_, taskName_)
{
    wxASSERT(platform);
}



SelfPreservation::~SelfPreservation()
{
}



