/**
**  @file tcRadar.h
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

#ifndef _tcRadar_H_
#define _tcRadar_H_

#include "tcSensorState.h"
#include "tcRadarDBObject.h"
#include <map>
#include <vector>

namespace database
{
	class tcRadarDBObject;
}
using database::tcRadarDBObject;

/*
struct tsRadarTargetInfo
{
    float mfLat_rad;
    float mfLon_rad;
    float mfAlt_m;
    float mfHeading_rad;
    float mfSpeed_mps;
    float mfRCS_dbsm;
} ;
*/

class tcGameObject;
class tcStream;
class tcUpdateStream;
class tcGameStream;
class tcSensorMapTrack;

/**
* Class to handle surveillance, fire control, and seeker radars.
* May want to break this up use derived classes for detailed
* functions.
* 
*/
class tcRadar : public tcSensorState
{
    friend class tcPlatformDebugPopup;
    friend class tcECMEvaluationDialog;
public:
    tcRadarDBObject* mpDBObj;

    // semi-active and command mode vars

    virtual bool CanDetectTarget(const tcGameObject* target, float& range_km, bool useRandom=true); 
    virtual bool InitFromDatabase(long key); ///< initializes sensor using database data at key

    // fire control methods
	virtual unsigned GetFireControlTrackCount() const;
	virtual unsigned GetMaxFireControlTracks() const;
    virtual bool IsTrackAvailable();
    virtual bool RequestTrack(long targetId);
    virtual bool ReleaseTrack(long targetId);
	virtual bool IsTrackingWithRadar(long targetId) const;

    virtual bool IsSemiactive() const {return isSemiactive;}
    virtual void SetFireControlSensor(long id, unsigned char idx);

    void Serialize(tcFile& file, bool mbLoad);

    void AddOrUpdateJammer(long id, float JNR_dB, float az_rad, float el_rad);
    bool IsJammed() const;
    void RemoveJammer(long id);

    virtual bool IsRadar() const;
    virtual void Update(double t);

    tcRadar& operator=(tcRadar& ss);
    
    virtual tcUpdateStream& operator<<(tcUpdateStream& stream);
    virtual tcUpdateStream& operator>>(tcUpdateStream& stream);

    virtual tcGameStream& operator<<(tcGameStream& stream);
    virtual tcGameStream& operator>>(tcGameStream& stream);

    tcRadar* Clone();
    tcRadar();
    tcRadar(tcRadarDBObject* dbObj);
    virtual ~tcRadar();

protected:
    struct JamInfo
    {
        float JNR_dB; ///< main beam J/N in dB
        float az_rad; ///< az of jammer
        float el_rad; ///< el of jammer
    };
    bool isSemiactive;
	float last_range_km; ///< [km] target range from last call to CanDetectTarget

	float target_x_offset_m; ///< offset for seeker target point in model coords
	float target_z_offset_m; ///< may want to move params like this to a seeker derived class
    std::map<long, JamInfo> jamMap;
    float jammingDegradation_dB;
    double jamTime_s; ///< time that jammingDegradation_dB was last updated
    bool isJammed;
	std::vector<long> fireControlTracks;

    static float lastTargetRCS_dBsm; ///< target RCS from last call to CanDetectTarget
    static float last_snr_margin_dB; ///< [dB] from last call to CanDetectTarget
    static float lastTargetElevation_rad; ///< [rad] from last call to TargetInElevationCoverage

    float CalculateJammingDegradation();
    float CalculateJammingDegradation2(float az_rad, float el_rad);
    float CalculateTargetRCS_dBsm(const tcGameObject* target, float& targetAz_rad, float& targetHeight_m) const;
    bool TargetInElevationCoverage(const tcGameObject* target, float targetRange_km, float& targetEl_rad) const;
    bool TargetInElevationCoverageWeapon(const tcGameObject* target, float targetRange_km, float& targetEl_rad) const;
    float CalculateClutterAdjustment_dB(const tcGameObject* target, float targetEl_rad) const;

    void RemoveAllJammers();
    void UpdateJammingDegradation();

    void CounterMeasureTest(double t);
    void AdjustTrackForFineTargeting(const tcGameObject* target);
    void UpdateSeeker(double t);
    void UpdateSensorMap(double t, const tcGameObject* target, float range_km);
    void UpdateSurveillance(double t);
    void UpdateTrackData(double t);
    void UpdateTrack(const tcGameObject* target, double t);
    void UpdateSensorMapTrackMode(const tcGameObject* target, tcSensorMapTrack* track, double t, float range_km);
};





#endif