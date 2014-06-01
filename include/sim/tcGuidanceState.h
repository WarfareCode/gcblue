/**
** @file tcGuidanceState.h
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

#ifndef _TCGUIDANCESTATE_H_
#define _TCGUIDANCESTATE_H_

#include "simmath.h"

class tcStream;

/**
 *
 */
struct tsGuidanceParameters
{
    long mnTargetID;
    double mfInterceptTime;
};

/**
 *
 */
class tcGuidanceState
{
public:
    // UPDATE Serialize() method after modifying member variables
    float mfGoalHeading_rad; // units are radians
    float mfGoalSpeed_kts;
    float mfGoalAltitude_m;

    void Serialize(tcFile& file, bool abLoad);
    void SetHeading(float afNewHeading) {mfGoalHeading_rad=afNewHeading;}
    void SetSpeed(float afNewSpeed) {mfGoalSpeed_kts=afNewSpeed;}
    void SetAltitude(float afNewAltitude_m) {mfGoalAltitude_m=afNewAltitude_m;}
    void GetKinGoal(tcKinematics& rsKinCurrent,tcKinematics& rsKinGoal);
    tcStream& operator<<(tcStream& stream);
    tcStream& operator>>(tcStream& stream);
};
#endif