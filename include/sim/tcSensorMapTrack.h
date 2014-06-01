/**
**  @file tcSensorMapTrack.h
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


#ifndef _SENSORMAPTRACK_H_ 
#define _SENSORMAPTRACK_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "simmath.h"
#include "tcFile.h"
#include <vector>
#include <deque>
#include "tcAllianceInfo.h"
#include "tcSensorReport.h"

class tcSimState;
class tcUpdateStream;
class tcGameStream;

namespace database
{
	class tcDatabase;
}
using database::tcDatabase;



struct EmitterInfo 
{
	long mnEmitterID; ///< database ID of emitter
	double mfTimestamp;
	int mnMode;

	const char* GetEmitterName() const;
};



/**
* State info for track stored in alliance sensor map.
* The targetedRating is used by the AI to avoid inefficient ganging up on track.
* engageRating controls how much ordance
*/
class tcSensorMapTrack : public tcTrack
{
public:	
    enum {MAX_SENSOR_REPORTS = 64, GOAL_SENSOR_REPORTS = 8, MAX_EMITTERS = 4};

    std::deque<tcSensorReport> maSensorReport; ///< most recent data from contributing sensors

    std::vector<EmitterInfo> emitterInfo;
	float assessedDamage;
	std::vector<long> intercepts; ///< vector of platform ids that are intercepting this track
	std::vector<long> engaged; ///< vector of weapon ids that are tracking / engaging
	std::vector<long> ambiguityList; ///< vector of platform ids consistent with detected emitters

    std::vector<tcPoint> errorPoly;
    float errorPolyLonWidth_rad;
    float errorPolyLatWidth_rad;
    bool alwaysVisible; ///< true to make this track always visible until dropped

	static unsigned int ambiguityListUpdates; // for debug purposes? (SEP2010)
    static bool sendDetailedTrackInfo; // set by tcMultiplayerInterface to determine if server passes track details to client

	/// called to indicate weapon launched at target
	bool AddEngagement(long id);

	/// called to indicate platform intercepting target
	bool AddIntercept(long id);

	bool AddReport(const tcSensorReport& report);
	void RemoveReport(size_t n);
    void RemoveReports(const std::vector<size_t>& reportsToRemove);

	///< static method to set pointer to tcSimState object
	static void AttachDatabase(tcDatabase* db) {database = db;}
	static void AttachSimState(tcSimState* ss) {simState = ss;}

	virtual void Clear();

	size_t GetEmitterCount() const;
	const EmitterInfo* GetEmitter(unsigned idx);
	EmitterInfo GetEmitterInfo(unsigned idx);

	/// gets number of weapons engaging this track
	unsigned GetEngagedCount() const;

	/// gets number of platforms intercepting this track
	unsigned GetInterceptCount() const;

	size_t GetContributorCount() const;
	const char* GetContributorName(unsigned idx) const;
	long GetDatabaseId() const;
	double GetLastReportTime() const;

	tc3DModel* GetModel() const;
	void SetModel(tc3DModel* model_);
	const tcTrack* GetTrack() const {return this;}
	void IdentifyTrack(long id);
    void SetAffiliation(tcAllianceInfo::Affiliation affil);

	bool IsIdentified() const;
    virtual bool IsBearingOnly() const;
    float TrackErrorKm() const;
	bool IsNew() const;
	bool IsDestroyed() const;
	bool IsStale() const;
	void MarkDestroyed();
	void MarkStale();
	void ClearStale();

    float GetStaleTime() const;
    float GetAgeOutTime() const;
	float GetTrackLife() const;

    float RangeToKm(float lon_rad, float lat_rad);
    float BearingToRad(float lon_rad, float lat_rad);

    tcSensorReport* GetOrCreateReport(long platformID, long sensorID);

	void UpdateAmbiguityList();
    void UpdateClassification(UINT16 mnClassification);
	bool UpdateEmitter(EmitterInfo*& rpEmitterInfo, long anEmitterID);

	/// removes engagement ids for weapons no longer engaging this track
	void UpdateEngagements();

	/// removes intercept ids for platforms no longer intercepting this track
	void UpdateIntercepts();

	void UpdateTrack(double tCoast_s);

    tcGameObject* GetAssociated();
    const tcGameObject* GetAssociatedConst() const;

	tcUpdateStream& operator<<(tcUpdateStream& stream);
	tcUpdateStream& operator>>(tcUpdateStream& stream);

	tcGameStream& operator<<(tcGameStream& stream);
	tcGameStream& operator>>(tcGameStream& stream);

	tcSensorMapTrack* operator= (tcSensorMapTrack *pa) {return pa;}
	tcSensorMapTrack& operator= (const tcSensorMapTrack&);
	tcSensorMapTrack(const tcSensorMapTrack& src);
    tcSensorMapTrack(const tcTrack& src);
	tcSensorMapTrack();
	~tcSensorMapTrack();

	static void SetAutoKillAssess(bool state);
private:
	static tcSimState* simState;
	static tcDatabase* database;
	static bool autoKillAssess; ///< set to true to automatically mark destroyed tracks
	enum {TRACK_STALE = 1, TRACK_DESTROYED = 2};
	unsigned char sensorFlags; ///< 1 - stale, 2 - destroyed
	long mnDatabaseID; ///< database ID of track, -1 for unknown
	tc3DModel* model;

    // age out and stale times for tracks
    static float unknownStale;
    static float unknownAgeOut;
    static float missileStale;
    static float missileAgeOut;
    static float torpedoStale;
    static float torpedoAgeOut;
    static float airStale;
    static float airAgeOut;
    static float surfaceStale;
    static float surfaceAgeOut;
    static float groundStale;
    static float groundAgeOut;
    static float reportAgeOut;

    bool AttemptPassiveTriangulation();
	void KillAssess();
    void UpdateAlwaysVisible();
    void UpdateGenericModel();
    void UpdateTrackWithPassive();
    void UpdateEmitters();
    void ValidateTrack();
    void PredictReport(double t, const tcSensorReport& base, tcSensorReport& prediction);
    void GetModelParameters(float& linearTime_s, float& defaultSpeed_mps, float& defaultClimbAngle_rad,
                            float& accel_mps2, float& climbRate_radps, float& headingRate_radps);
    void UpdateErrorPolyWidth();
    void PruneReports();
};

#endif 

