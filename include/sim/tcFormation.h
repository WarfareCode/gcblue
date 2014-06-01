/** 
**  @file tcFormation.h
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

#ifndef _TCFORMATION_H_
#define _TCFORMATION_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>

class tcPlatformObject;
class tcAirObject;
class tcKinematics;
class tcCommandStream;
class tcGameStream;

namespace scriptinterface
{
	class tcScenarioLogger;
}

/**
*
*/
class tcFormation
{
public:
	enum FormationMode
	{
		FOLLOW = 1, ///< stay in center of formation sector
		SPRINTDRIFT = 2 ///< alternate slow drift periods, with sprint to catch up to formation
	};
	FormationMode formationMode;

    bool isActive; ///< true if formation is active
    bool useNorthBearing; ///< true for brg relative north, false relative to leader course
    long leaderId;
    float range_center_km;
    float range_span_km;
    float bearing_center_rad; ///< bearing from leader to center of zone
    float bearing_span_rad;
    float altitudeOffset_m; ///< for air formations, the altitude offset
    std::vector<long> followers;

    void Update(tcPlatformObject* platform);
    void Update(tcAirObject* air);
	void UpdateFollow(tcPlatformObject* platform);
	void UpdateSprintDrift(tcPlatformObject* platform);

    void Clear();
    bool IsLeader() const;
    bool IsFollower() const;
    bool IsInPosition(tcPlatformObject* platform, float bearing_rad, float range_km) const;
    bool IsInPositionLoose(tcPlatformObject* platform, float bearing_rad, float range_km) const;
    bool IsInPositionLoose2(tcPlatformObject* platform, float bearing_rad, float range_km, 
        float& deltaBearing_rad, float& deltaRange_km) const;

	void SetFormationMode(int mode);
    void SetFormationPosition(float range_km, float span_km, float bearing_rad, float span_rad);
    void SetAltitudeOffset(float dh_m);
    void SetUseNorthBearing(bool state);

    void AddFollower(long id);
    void RemoveFollower(long id);
    void RemoveAllFollowers();
    void LeaveFormation();

    bool HasNewCommand() const;
    void SetNewCommand();
    void ClearNewCommand();

    void SetPlatformId(long id);

    void SaveToPython(scriptinterface::tcScenarioLogger& logger);

    virtual tcGameStream& operator<<(tcGameStream& stream);
    virtual tcGameStream& operator>>(tcGameStream& stream);

    virtual tcCommandStream& operator<<(tcCommandStream& stream);
    virtual tcCommandStream& operator>>(tcCommandStream& stream);

    tcFormation();
    virtual ~tcFormation();

private:
    double lastUpdateTime;
    bool repositioning;
	enum Maneuver
	{
		DRIFT = 1,
		SPRINT_IN = 2,
		SPRINT_OUT = 3
	} maneuverType;

    bool hasNewCommand; ///< for multiplayer
    long platformId;

    float GetInterceptHeading(float tgt_east_m, float tgt_north_m, float tgt_heading_rad, 
        float tgt_speed_mps, float own_speed_mps, bool& valid);
    float GetLazyInterceptHeading(float tgt_east_m, float tgt_north_m, float tgt_heading_rad, 
        float tgt_speed_mps, float& own_speed_mps, bool& valid);
    float GetLazyInterceptHeadingFixedSpeed(float tgt_east_m, float tgt_north_m, float tgt_heading_rad, 
        float tgt_speed_mps, float own_speed_mps, bool& valid);
    float GetLazyInterceptHeadingClosingSpeed(float tgt_east_m, float tgt_north_m, float tgt_heading_rad, 
        float tgt_speed_mps, float& own_speed_mps, float closingSpeed_mps, bool& valid);
    const tcPlatformObject* GetLeader(const tcPlatformObject* platform) const;
	void GetPositionError(tcPlatformObject* platform, 
		float& drange_km, float& dbearing_rad, float& deast_km, float& dnorth_km, tcKinematics& leaderKin);
};

#endif
