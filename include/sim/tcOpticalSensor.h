/**
**  @file tcOpticalSensor.h
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

#ifndef _TCOPTICALSENSOR_H_
#define _TCOPTICALSENSOR_H_

#include "tcSensorState.h"
#include "tcOpticalDBObject.h"
#include <vector>

using database::tcOpticalDBObject;

class tcGameObject;
class tcStream;
class tcUpdateStream;

/**
* Class to model optical and IR sensors. Handles visual detections.
*/
class tcOpticalSensor : public tcSensorState
{
    friend class tcPlatformDebugPopup;
public:
    tcOpticalDBObject* mpDBObj;

    virtual bool CanDetectTarget(const tcGameObject* target, float& range_km, bool useRandom=true); 
    virtual bool InitFromDatabase(long key); ///< initializes sensor using database data at key
    
    // fire control methods (for laser designator)
	virtual unsigned GetFireControlTrackCount() const;
	virtual unsigned GetMaxFireControlTracks() const;
    virtual bool IsTrackAvailable();
    virtual bool RequestTrack();
    virtual bool ReleaseTrack();
    bool IsDesignator() const;
    bool IsSemiactive() const;


    void Serialize(tcFile& file, bool mbLoad);

    virtual bool IsOptical() const;
    virtual void Update(double t);

    tcOpticalSensor& operator=(tcOpticalSensor& ss);
    
    virtual tcUpdateStream& operator<<(tcUpdateStream& stream);
    virtual tcUpdateStream& operator>>(tcUpdateStream& stream);

    tcOpticalSensor* Clone();
    tcOpticalSensor();
    tcOpticalSensor(tcOpticalDBObject* dbObj);
    virtual ~tcOpticalSensor();

protected:
    float CalculateNightPenalty(const tcGameObject* target) const;
    float CalculateTargetSignature(const tcGameObject* target, float& targetAz_rad, float& targetAlt_m) const;

    void CounterMeasureTest(double t);
    // bool isSemiactive;
    //tcRadar* GetSemiactiveIlluminator(); // add semi-active later for laser designated guidance
    void UpdateSeeker(double t);
    void UpdateSensorMap(double t, const tcGameObject* target, float range_km, float az_rad);
    void UpdateSurveillance(double t);
    void UpdateTrack(const tcGameObject* target, double t);

    // fire-control vars (laser designator)
    unsigned char fireControlTrackCount;
    bool isSemiactive;
    bool isDesignator;

	/* parameters saved by CanDetectTarget so that this info is available in UpdateSensorMap
	** (didn't want to modify virtual method CanDetectTarget to pass this info directly) */
	long detectionCandidate;
	float last_margin_dB; // detection margin from last CanDetectTarget call
    static float lastTargetSignature_dB; ///< target signature from last call to CanDetectTarget
    static float last_az_rad; ///< target azimuth form last call to CanDetectTarget
};





#endif