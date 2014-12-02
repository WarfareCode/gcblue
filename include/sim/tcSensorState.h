/** 
**  @file tcSensorState.h
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

#ifndef _TCSENSORSTATE_H_
#define _TCSENSORSTATE_H_

#include "tcPool.h"
#include "simmath.h"

namespace database
{
	class tcDatabase;
	class tcSensorDBObject;
}

using database::tcDatabase;
using database::tcSensorDBObject;

#define SSMODE_NULL 0 ///< seeker that doesn't exist or damaged
#define SSMODE_SURVEILLANCE 1 ///< surveillance or both FC and surveillance
#define SSMODE_SEEKERTRACK 2  ///< seeker is tracking target
#define SSMODE_SEEKERSEARCH 3 ///< seeker searching for target
#define SSMODE_SEEKERACQUIRE 4 ///< seeker has target cue and attempting to track
#define SSMODE_FC 5 // fire control only

class tcRadar;
class tcOpticalSensor;
class tcSimState;
class tcGameObject;
class tcUpdateStream;
class tcGameStream;
class tcSensorPlatform;
class tcSensorReport;
class tcLOS;
struct Damage;
class tcSensorMapTrack;

/**
 * Represents the state of a sensor.
 */
class tcSensorState
{
	friend class tcGameSerializer;
public:
    short int mbActive;
    tcGameObject* parent;
	tcSensorPlatform* sensorPlatform; ///< parent should always be a sensor plat, this is a down-cast for convenience
    long mnDBKey; 
    tcSensorDBObject* mpDBObj;
    double mfLastScan;
    float mfCurrentScanPeriod_s;
    short int mnMode;
    tcTrack mcTrack;
    //GeoPoint msCurrentPos; ///< current true position of sensor
    //float mfLookAz_rad;      ///< azimuth of center of coverage relative to north
    float mountAz_rad;       ///< mounted azimuth of boresight relative to nose/bow of platform
    float mfSensorHeight_m;     ///< height of sensor relative to platform altitude

    static void AttachDatabase(tcDatabase* db) {database = db;}
    static void AttachSimState(tcSimState* ss) {simState = ss;}
    static void AttachLOS();
	virtual bool CanDetectTarget(const tcGameObject* target, float& range_km, bool useRandom=true);

    tcRadar* GetFireControlRadar();
    tcOpticalSensor* GetLaserDesignator();
	tcSensorState* GetFireControlSensor();
    void GetTestArea(tcRect& region);
	bool GetTrack(tcTrack& track_);
    long GetFireControlPlatform() const;
    bool HasFireControlSensor() const;

    virtual unsigned GetFireControlTrackCount() const;
    virtual unsigned GetMaxFireControlTracks() const;
    virtual bool IsTrackAvailable();
    virtual bool RequestTrack(long targetId);
    virtual bool ReleaseTrack(long targetId);
	virtual bool IsTrackingWithRadar(long targetId) const;

    virtual bool InitFromDatabase(long key); ///< initializes sensor using database data at key
	bool IsActive() const;
	bool IsDamaged() const;
    bool IsHidden() const;
    
	virtual bool IsECM() const;
    virtual bool IsESM() const;
    virtual bool IsRadar() const;
    virtual bool IsSonar() const;
    virtual bool IsOptical() const;

    void Serialize(tcFile& file, bool mbLoad);
    virtual tcUpdateStream& operator<<(tcUpdateStream& stream);
    virtual tcUpdateStream& operator>>(tcUpdateStream& stream);
    virtual tcGameStream& operator<<(tcGameStream& stream);
    virtual tcGameStream& operator>>(tcGameStream& stream);

    virtual void SetActive(bool active);
    void SetCommandReceiver(bool state);
    bool IsCommandReceiver() const;
    void SetDamaged(bool state);
	virtual void SetFireControlSensor(long id, unsigned char idx);
    void SetMountAz(float az);
    void SetParent(tcGameObject* obj);
    virtual void Update(double t);
    int UpdateScan(double afTime);
    tcSensorState& operator=(tcSensorState& ss);

    static void InitErrorFactor();

    bool ApplyAdvancedDamage(const Damage& damage);

    tcSensorState* Clone() const;
    tcSensorState();
    tcSensorState(tcSensorDBObject* dbObj);
    virtual ~tcSensorState();

protected:
    enum {N_ERROR_FACTOR=4096};
    static tcSimState* simState;
	static tcDatabase* database;
    static tcLOS* los;
    static long nextSensorId; ///< for assigning sensorId
    static float errorFactor[N_ERROR_FACTOR];

	bool isHidden; ///< hidden sensors are not displayed in object control view
    bool isDamaged;
    long fireControlId; ///< id of platform with fire control sensor (semi-active illuminator, or command guidance sensor)
    unsigned char fireControlIdx; ///< sensor index of fire control sensor platform
    const long sensorId; ///< unique id for this sensor (used for sonar TL cache)
    double lastCounterMeasureTime; ///< last time that sensor checked vs. countermeasures
    bool isCommandReceiver;


	bool RandomDetect(float margin_dB);
    void UpdateActiveReport(tcSensorReport* report, double t, float az_rad, float range_km, float alt_m, 
        const tcSensorMapTrack* track);
    void UpdatePassiveReport(tcSensorReport* report, double t, float az_rad, float range_km,
		const tcSensorMapTrack* track);
    bool HasLOS(const tcGameObject* target);
    void CalculateLonLatCovariance(float az_rad, float lat_rad, float sigmaCrossRange_m, float sigmaDownRange_m,
        float& C11, float& C22, float& C12);
    bool GetAltitudeEstimate(float& altitudeEstimate_m, float& altitudeVariance, float range_km, float az_rad, float alt_m);

    static float GetErrorFactor(long platformId, long sensorId, float targetAz_rad);
};
#endif