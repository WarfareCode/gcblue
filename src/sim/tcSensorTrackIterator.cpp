/** 
**  @file tcSensorTrackIterator.cpp 
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

#include "stdwx.h" // precompiled header file

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "tcSensorTrackIterator.h"
#include "tcGameObject.h"
#include "tcSensorMap.h"
#include "tcAllianceSensorMap.h"
#include "tcSimState.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



tcSimState* tcSensorTrackIterator::simState = NULL;

/**
*
*/
void tcSensorTrackIterator::First()
{
    if (!map)
    {
        currentPos = -1;
        currentObj = 0;
        nIterated = 1;
        return;
    }

    wxASSERT(map->GetTrackCount() >= 0);

    nSize = (unsigned int)map->GetTrackCount();
    nIterated = 0;

    if (nSize == 0)
    {
        currentPos = -1;
        currentObj = 0;
        nIterated = 1;
        return;
    }
    currentPos = map->GetStartTrackPosition();
    
    Next();
}

/**
*
*/
tcSensorMapTrack* tcSensorTrackIterator::Get()
{
    return currentObj;
}



/**
* Advance to next object that meets filter criteria. If
* no objects are found, set currentObj to NULL
*/
void tcSensorTrackIterator::Next()
{
    if (!map)
    {
        nIterated++;
        return;
    }

    bool searching = true;

    while ((nIterated <= nSize) && searching)
    {
        if (nIterated < nSize) // kind of a hack, nIterated > nSize is used for end condition
        {
            map->GetNextTrack(currentPos, currentObj);
        }
        nIterated++;

        if (PassesFilter(currentObj))
        {
            searching = false; // found eligible object
        }
        else
        {
            currentObj = 0;
        }
    }
}

/**
*
*/
bool tcSensorTrackIterator::NotDone()
{
    return (map != 0) && (nIterated <= nSize);
}


/**
* Checks currentObj against filtering criteria. This is used
* to iterate through a filtered set of objects.
* @return true if current obj meets filtering criteria, false otherwise
*/
bool tcSensorTrackIterator::PassesFilter(const tcSensorMapTrack* track) const
{
    if (!track) return false;

    bool passesClassMask = (classMask == 0xFFFF) || ((classMask & track->mnClassification) != 0);

    if (!passesClassMask) return false;

    if (!useRegion) return true;

    return region.ContainsPoint(track->mfLon_rad, track->mfLat_rad) && ((!track->IsBearingOnly()) || (track->errorPoly.size() > 0));
}

/**
* @return number of tracks that pass filter
*/
unsigned int tcSensorTrackIterator::Size() const
{
    unsigned int result = 0;

    int nTotal = map->GetTrackCount();
    long poolpos = map->GetStartTrackPosition();
    int n = 0;
    while(n++ < nTotal)  
    {    
        tcSensorMapTrack* track;
        map->GetNextTrack(poolpos, track);

        if (PassesFilter(track)) result++;
    }

    return result;
}


tcSensorTrackIterator::tcSensorTrackIterator(unsigned int alliance_, 
                                             unsigned int classificationMask, 
                                             const tcGeoRect& filterRegion) :
    useRegion(true),
    alliance(alliance_),
    classMask(classificationMask)
{
    if (!simState)
    {
        simState = tcSimState::Get();
    }

    region = filterRegion;

    map = simState->mcSensorMap.GetMap(alliance);

    First();
}

/**
* Version that doesn't require region argument
*/
tcSensorTrackIterator::tcSensorTrackIterator(unsigned int alliance_, unsigned int classificationMask)
:
    useRegion(false),
    alliance(alliance_),
    classMask(classificationMask)
{
    if (!simState)
    {
        simState = tcSimState::Get();
    }

    map = simState->mcSensorMap.GetMap(alliance);

    First();
}

tcSensorTrackIterator::tcSensorTrackIterator() :
    useRegion(false),
    alliance(0),
    classMask(0)
{
    if (!simState)
    {
        simState = tcSimState::Get();
    }

    map = simState->mcSensorMap.GetMap(alliance);

    First();
}

tcSensorTrackIterator::~tcSensorTrackIterator()
{
}

