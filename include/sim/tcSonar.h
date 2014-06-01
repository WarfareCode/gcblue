/**
**  @file tcSonar.h
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

#ifndef _TCSONAR_H_
#define _TCSONAR_H_

#include "tcSensorState.h"
#include <vector>

namespace database
{
	class tcSonarDBObject;
}

using database::tcSonarDBObject;


class tcGameObject;
class tcStream;
class tcUpdateStream;
class tcGameStream;

/**
* Class to handle surveillance, fire control, and seeker radars.
* May want to break this up use derived classes for detailed
* functions.
* 
*/
class tcSonar : public tcSensorState
{
    friend class tcPlatformDebugPopup;
public:
    tcSonarDBObject *mpDBObj;

    float CalculateSimpleDetectionRange(tcGameObject* target, float& NL, float& SLp);
    virtual bool CanDetectTarget(const tcGameObject* target, float& range_km, bool useRandom=true); 
    virtual bool InitFromDatabase(long key); ///< initializes sensor using database data at key
	float GetLastSNRExcess() const;

    void Serialize(tcFile& file, bool mbLoad);

    float GetScope() const;
    bool IsPassive() const; ///< Warning: don't confuse with !tcSensorState::IsActive()
    virtual bool IsRadar() const;
    virtual bool IsSonar() const;
    void SetActiveSonar();
    void SetPassiveSonar();
    virtual void Update(double t);
	void ForceScope(float val_m);

    static float DT; ///< sonar detection threshold, set as constant for all sonars

    tcSonar& operator=(tcSonar& ss);
    
    virtual tcUpdateStream& operator<<(tcUpdateStream& stream);
    virtual tcUpdateStream& operator>>(tcUpdateStream& stream);
    virtual tcGameStream& operator<<(tcGameStream& stream);
    virtual tcGameStream& operator>>(tcGameStream& stream);

    tcSonar* Clone();
    tcSonar();
    tcSonar(tcSonarDBObject* dbObj);
    virtual ~tcSonar();

protected:
    bool isPassive;
	float scope_m; ///< [m] scope of towed array

	void UpdateScope(double t);
    void UpdateSeeker(double t);
    void UpdateSeekerWakeHoming(double t);

    void UpdateSensorMapActive(double t, const tcGameObject* target, float range_km);
    void UpdateSensorMapPassive(double t, const tcGameObject* target, float range_km, float az_rad);
    void UpdateSurveillance(double t);
    void UpdateTrack(const tcGameObject* target, double t);
private:
	float depth_m; ///< [m] depth of sonar
    float last_az_rad; ///< [rad] target azimuth from last call to CanDetectTarget
    float last_range_km; ///< [km] target range from last call to CanDetectTarget
    float last_snr_excess; ///< [dB] snr excess from last call to CanDetectTarget
    static float last_TL; ///< [dB] last transmission loss from last call to CanDetectTarget
    long emitterId; ///< if active sonar has been detected, database id of active sonar, -1 otherwise

    bool CountermeasureRejected(const tcGameObject* target) const;
};





#endif