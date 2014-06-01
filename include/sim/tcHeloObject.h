/**
**  @file tcHeloObject.h
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

#ifndef _HELOOBJECT_H_
#define _HELOOBJECT_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "tcAirObject.h"

/**
* Models helo object that can hover
*/
class tcHeloObject : public tcAirObject 
{
public:

    virtual void ApplyRestrictions();
    virtual void Clear();
    virtual void RandInitNear(float afLon_deg, float afLat_deg);

    virtual void UpdateClimb(float dt_s);
	void UpdateDestroyed(double t);
    virtual void UpdateSpeed(float dt_s);
    virtual void Update(double afStatusTime);

    
    virtual float GetCurrentFuelRate() const;
    virtual float GetCruiseAltitude() const;
    float GetDippingSonarAlt() const;
    virtual float GetSonarSourceLevel(float az_deg) const;

    void PrintToFile(tcFile& file);
    void SaveToFile(tcFile& file);
    void LoadFromFile(tcFile& file);
    virtual void Serialize(tcFile& file, bool mbLoad);


    tcHeloObject();
    tcHeloObject(tcAirDBObject* obj);
    virtual ~tcHeloObject();
};

#endif
