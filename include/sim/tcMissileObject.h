/** 
**  @file tcMissileObject.h
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

#ifndef _TCMISSLEOBJECT_H_
#define _TCMISSLEOBJECT_H_

#include "tcAero.h"
#include "tcWeaponObject.h"
#include "tcGuidanceState.h"
#include "tcRadar.h"
#include "tcSensorPlatform.h"
#include "tcSensorMapTrack.h"

class tcUpdateStream;
class tcGameStream;

/**
 * A class that represents a missle.
 *
 * @see tcGameObject
 */
class tcMissileObject : public tcWeaponObject, public tcSensorPlatform
{
public:
    float goalHeading_rad;
    float goalPitch_rad;
    float goalAltitude_m;
    double mfInterceptTime;
    bool subSurfaceLaunch; ///< true during subsurface launch phase for sub-launched missiles

	// are all 3 of these necessary? needs refactoring
    float mfLastGuidanceUpdate;
	double guidanceStatusTime; 
    float mfGuidanceUpdateInterval;

    GeoPoint msWaypoint;   // nav datum
    std::vector<GeoPoint> preplanRoute; ///< for missiles that have this feature, a preplanned route to fly first
    float mfRangeToObjective_km; // for segment determination
    unsigned int mnCurrentSegment;

	Aero::tsMissileKState msKState;
    tcMissileDBObject *mpDBObject; // pointer to valid database obj

    void Clear();
	virtual void LaunchFrom(tcGameObject* obj, unsigned nLauncher);
    void RandInitNear(float afLon_deg, float afLat_deg);
    virtual void Update(double afStatusTime);
    virtual void UpdateEffects();
    virtual void UpdateGuidance(double afStatusTime);
    virtual void SetHeading(float afNewHeading) {goalHeading_rad=afNewHeading;}
	teAltitudeMode GetCurrentAltitudeMode();
	teGuidanceMode GetCurrentGuidanceMode();
    float GetDistanceFromLaunch() const;
    void SetSeekerTarget(long id);
    virtual void ApplyRepairs(float repair);

    void UpdateTargetPos(float lon_rad, float lat_rad);

	virtual tcRadar* GetSeekerRadar() const;
    virtual tcSensorState* GetSeekerSensor() const;
    virtual void DesignateTarget(long anID);
    virtual int GetGuidanceParameters(tsGuidanceParameters& gp);
    float RuntimeRemaining();
    bool StillNeedsIlluminator(long& platformId) const;

    virtual float GetOpticalCrossSection() const;
    virtual float GetIRSignature(float az_deg) const;

    void SetRandomPreplan(const std::string& planType);

    void PrintToFile(tcFile&);
    void SaveToFile(tcFile& file);
    void LoadFromFile(tcFile& file);
    virtual void Serialize(tcFile& file, bool mbLoad);

    virtual tcUpdateStream& operator<<(tcUpdateStream& stream);
    virtual tcUpdateStream& operator>>(tcUpdateStream& stream);
    virtual tcGameStream& operator<<(tcGameStream& stream);
    virtual tcGameStream& operator>>(tcGameStream& stream);

	struct MissileTrajectory
	{
		std::vector<double> time_s;
		std::vector<double> range_m; // ground range covered
		std::vector<double> altitude_m;
		std::vector<double> speed_mps;
	};
    static float EstimateRangeKm(float evalMin_km, float evalMax_km, float evalStep_km,
                                 float launchSpeed_kts, float launchAltitude_m, float targetAltitude_m, tcMissileDBObject* missileData, bool logData=true);
    static float EstimateRangeFaster(float evalMin_km, float evalMax_km, unsigned int nSteps,
                                 float launchSpeed_kts, float launchAltitude_m, float targetAltitude_m, tcMissileDBObject* missileData);
    static bool EvaluateTarget(tcKinematics& missileKin, const tcSensorMapTrack& target, tcMissileDBObject* missileData, MissileTrajectory* trajectory=0);
    tcMissileObject();
    tcMissileObject(tcMissileObject&);
    tcMissileObject(tcMissileDBObject *obj);
    ~tcMissileObject();

private:
    struct MissileSimData
    {
        Aero::tsMissileKState kstate;
        tcKinematics missileKin;
        GeoPoint waypoint;   // nav datum
        float rangeToObjective_km; // for segment determination
        float seekerDetectionRange_km;
        unsigned int segment;
        float goalAltitude_m;
        float goalHeading_rad;
        float goalPitch_rad;
        tcTrack targetTrack;
        double interceptTime_s;
        float terrainHeight_m;
        bool endFlight;
        bool forceHit; ///< if true, then treat end of flight as "hit" for range estimate
    };

    float distanceFromLaunch; ///< distance traveled from launch [m]
    bool isTerminal;
    bool isCommandHandoff; ///< flag to indicate we are in "command handoff" mode
    
    void UpdateDetonation();
    void UpdateGoalPitch();
    void UpdateDatumInterceptGuidance(double t, bool& useInterceptPitch, float& interceptPitch_rad);
    static void UpdateGoalPitchSim(MissileSimData& simData, const tcMissileDBObject* missileData);

    void UpdateCommandHandoff();
    void UpdateSubsurface(double t);
    float GlimitedTurnRate() const;
    static float GlimitedTurnRate(float speed_kts, const tcMissileDBObject* missileData);
    
    static void UpdateGuidanceSim(MissileSimData& simData, const tcMissileDBObject* missileData);
	static float EstimateSeekerDetectionRange(const tcSensorMapTrack& target, tcMissileDBObject* missileData);

};

#endif
