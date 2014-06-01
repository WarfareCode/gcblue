/** 
**  @file tcAirCM.h 
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

#if _MSC_VER > 1000
#pragma once
#endif

#ifndef _AIRCM_H_
#define _AIRCM_H_

#include "tcGameObject.h"

class tcStream;
class tcUpdateStream;

namespace database
{
    class tcCounterMeasureDBObject;
}

/**
* Class for countermeasures such as chaff, flares, decoys, noisemakers
*/
class tcAirCM : public tcGameObject
{
public:

    tcCounterMeasureDBObject* mpDBObject;  

    virtual void LaunchFrom(tcGameObject* obj, unsigned nLauncher);
    virtual void Update(double t);

    virtual float ApplyAdvancedDamage(const Damage& damage, tcGameObject* damager); ///< called when new damage occurs

    virtual tcUpdateStream& operator<<(tcUpdateStream& stream);
    virtual tcUpdateStream& operator>>(tcUpdateStream& stream);

    virtual tcGameStream& operator<<(tcGameStream& stream);
    virtual tcGameStream& operator>>(tcGameStream& stream);


    tcAirCM();
    tcAirCM(const tcAirCM& src);
    tcAirCM(tcCounterMeasureDBObject* obj);
    virtual ~tcAirCM();
    
private:
    enum {CM_CHAFF = 1, CM_FLARE = 2, CM_WATERFLARE};
    int typeCode;

    float timeRemaining_s; ///< when 0, remove obj from sim
    float vg_mps;
    float vup_mps;
    
    void ApplyRestrictions();
    bool IsChaff() const;
    bool IsFlare() const;
    void Move(float dt_s);
	void UpdateSpeed(float dt_s);
};

#endif
