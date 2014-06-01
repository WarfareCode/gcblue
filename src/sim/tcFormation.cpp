/** 
**  @file tcFormation.cpp
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

#include "stdwx.h"

#ifndef WX_PRECOMP
#include "wx/wx.h" 
#endif

#include "tcFormation.h"
#include "tcGameObject.h"
#include "tcPlatformObject.h"
#include "tcAeroAirObject.h"
#include "tcAirObject.h"
#include "tcPlatformDBObject.h"
#include "tcJetDBObject.h"
#include "tcSimState.h"
#include "common/tcObjStream.h"
#include "common/tcGameStream.h"
#include "tcScenarioLogger.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



/**
* Load from stream
*/
tcCommandStream& tcFormation::operator<<(tcCommandStream& stream)
{
    char nFormationMode;
    stream >> nFormationMode;
    formationMode = (FormationMode)nFormationMode;

    stream >> isActive;
    stream >> useNorthBearing;
    stream >> leaderId;
    stream >> range_center_km;
    stream >> range_span_km;
    stream >> bearing_center_rad;
    stream >> bearing_span_rad;
	stream >> altitudeOffset_m;

    followers.clear();
    unsigned char nFollowers;
    stream >> nFollowers;

    for (unsigned char k=0; k<nFollowers; k++)
    {
        long id;
        stream >> id;
        followers.push_back(id);
    }

    return stream;
}

/**
* Save to stream
*/
tcCommandStream& tcFormation::operator>>(tcCommandStream& stream)
{
    char nFormationMode = (char)formationMode;
    stream << nFormationMode;

    stream << isActive;
    stream << useNorthBearing;
    stream << leaderId;
    stream << range_center_km;
    stream << range_span_km;
    stream << bearing_center_rad;
    stream << bearing_span_rad;
	stream << altitudeOffset_m;

    wxASSERT(followers.size() < 256);
    unsigned char nFollowers = (unsigned char)followers.size();
    stream << nFollowers;

    for (unsigned char k=0; k<nFollowers; k++)
    {
        stream << followers[k];
    }

    return stream;
}


/**
* Load from stream
*/
tcGameStream& tcFormation::operator<<(tcGameStream& stream)
{
    char nFormationMode;
    stream >> nFormationMode;
    formationMode = (FormationMode)nFormationMode;

    stream >> isActive;
    stream >> useNorthBearing;
    stream >> leaderId;
    stream >> range_center_km;
    stream >> range_span_km;
    stream >> bearing_center_rad;
    stream >> bearing_span_rad;
	stream >> altitudeOffset_m;

    followers.clear();
    unsigned char nFollowers;
    stream >> nFollowers;

    for (unsigned char k=0; k<nFollowers; k++)
    {
        long id;
        stream >> id;
        followers.push_back(id);
    }

    return stream;
}

/**
* Save to stream
*/
tcGameStream& tcFormation::operator>>(tcGameStream& stream)
{
    char nFormationMode = (char)formationMode;
    stream << nFormationMode;

    stream << isActive;
    stream << useNorthBearing;
    stream << leaderId;
    stream << range_center_km;
    stream << range_span_km;
    stream << bearing_center_rad;
    stream << bearing_span_rad;
	stream << altitudeOffset_m;

    wxASSERT(followers.size() < 256);
    unsigned char nFollowers = (unsigned char)followers.size();
    stream << nFollowers;

    for (unsigned char k=0; k<nFollowers; k++)
    {
        stream << followers[k];
    }

    return stream;
}



void tcFormation::AddFollower(long id)
{
    wxASSERT(IsLeader());

    followers.push_back(id);

    SetNewCommand();
}

void tcFormation::Clear()
{
    isActive = false; ///< true if formation is active
    useNorthBearing = false;
    leaderId = -1;
    range_center_km = 2.0f;
    range_span_km = 1.5f;
    bearing_center_rad = 0.2f;
    bearing_span_rad = 0.4f;
    lastUpdateTime = 0;
    repositioning = false;
	formationMode = FOLLOW;
    followers.clear();
    hasNewCommand = false;
}


void tcFormation::ClearNewCommand()
{
    hasNewCommand = false;
}

/**
* @param tgt_east_m east position of target - east pos of self
* @param tgt_north_m north pos of target - north pos of self
* @return intercept heading in rad
*/
float tcFormation::GetInterceptHeading(float tgt_east_m, float tgt_north_m, float tgt_heading_rad, 
        float tgt_speed_mps, float own_speed_mps, bool& valid)
{
    valid = false;

    float range_m = sqrtf(tgt_east_m*tgt_east_m + tgt_north_m*tgt_north_m);
    float inv_range_m = 1.0 / range_m;
    
    float ke = tgt_east_m * inv_range_m;
    float kn = tgt_north_m * inv_range_m;

    float ve = sinf(tgt_heading_rad) * tgt_speed_mps;
    float vn = cosf(tgt_heading_rad) * tgt_speed_mps;

    float a = ke*ke + kn*kn;
    float b = 2.0f*ke*ve + 2.0f*kn*vn;
    float c = ve*ve + vn*vn - own_speed_mps*own_speed_mps;

    float det_arg = b*b - 4.0f*a*c;
    if (det_arg >= 0)
    {
        float det = sqrtf(det_arg);
        float alpha = (a > 0) ? (det - b) / (2.0f*a) : (-det - b) / (2.0f*a);
        float ve_int = ve + alpha*ke;
        float vn_int = vn + alpha*kn;

        valid = (alpha > 0);

        return atan2f(ve_int, vn_int);
    }
    else
    {   // just head toward target, no collision course intercept exists
        return atan2f(tgt_east_m, tgt_north_m); 
    }
}

/**
* @param tgt_east_m east position of target - east pos of self
* @param tgt_north_m north pos of target - north pos of self
* @return intercept heading in rad
*/
float tcFormation::GetLazyInterceptHeading(float tgt_east_m, float tgt_north_m, float tgt_heading_rad, 
        float tgt_speed_mps, float& own_speed_mps, bool& valid)
{
    valid = false;

    float range_m = sqrtf(tgt_east_m*tgt_east_m + tgt_north_m*tgt_north_m);
    float inv_range_m = 1.0 / range_m;
    
    float ke = tgt_east_m * inv_range_m;
    float kn = tgt_north_m * inv_range_m;

    float ve = sinf(tgt_heading_rad) * tgt_speed_mps;
    float vn = cosf(tgt_heading_rad) * tgt_speed_mps;

    float b = ke*ve + kn*vn;

    if (b < 0)
    {
        float alpha = -b;
        float ve_int = ve + alpha*ke;
        float vn_int = vn + alpha*kn;

        valid = (alpha > 0.5f);

        own_speed_mps = sqrtf(ve_int*ve_int + vn_int*vn_int);

        return atan2f(ve_int, vn_int);
    }
    else
    {
        return 0;
    }
}

/**
* Version that solves for given speed instead of minimizing speed
*
* @param tgt_east_m east position of target - east pos of self
* @param tgt_north_m north pos of target - north pos of self
* @return intercept heading in rad
*/
float tcFormation::GetLazyInterceptHeadingFixedSpeed(float tgt_east_m, float tgt_north_m, float tgt_heading_rad, 
        float tgt_speed_mps, float own_speed_mps, bool& valid)
{
    valid = false;

    float range_m = sqrtf(tgt_east_m*tgt_east_m + tgt_north_m*tgt_north_m);
    float inv_range_m = 1.0 / range_m;
    
    float ke = tgt_east_m * inv_range_m;
    float kn = tgt_north_m * inv_range_m;

    float ve = sinf(tgt_heading_rad) * tgt_speed_mps;
    float vn = cosf(tgt_heading_rad) * tgt_speed_mps;

    float b = ke*ve + kn*vn;

    if (b > 0) return 0;

    float det = b*b - (tgt_speed_mps*tgt_speed_mps - own_speed_mps*own_speed_mps);
    if (det > 0)
    {
        float alpha = -b - sqrtf(det);
        float ve_int = ve + alpha*ke;
        float vn_int = vn + alpha*kn;

        return atan2f(ve_int, vn_int);
    }
    else
    {
        return 0;
    }
}


/**
* Version that solves for closing speed
*
* @param tgt_east_m east position of target - east pos of self
* @param tgt_north_m north pos of target - north pos of self
* @return intercept heading in rad
*/
float tcFormation::GetLazyInterceptHeadingClosingSpeed(float tgt_east_m, float tgt_north_m, float tgt_heading_rad, 
        float tgt_speed_mps, float& own_speed_mps, float closingSpeed_mps, bool& valid)
{
    valid = true;

    float range_m = sqrtf(tgt_east_m*tgt_east_m + tgt_north_m*tgt_north_m);
    float inv_range_m = 1.0 / range_m;
    
    float ke = tgt_east_m * inv_range_m;
    float kn = tgt_north_m * inv_range_m;

    float ve = sinf(tgt_heading_rad) * tgt_speed_mps;
    float vn = cosf(tgt_heading_rad) * tgt_speed_mps;

    float ve_int = ve + closingSpeed_mps*ke;
    float vn_int = vn + closingSpeed_mps*kn;

    own_speed_mps = sqrtf(ve_int*ve_int + vn_int*vn_int);

    return atan2f(ve_int, vn_int);
}


const tcPlatformObject* tcFormation::GetLeader(const tcPlatformObject* platform) const
{
    wxASSERT(platform != 0);

    if (platform != 0)
    {
        return dynamic_cast<const tcPlatformObject*>(platform->simState->GetObject(leaderId));
    }
    else
    {
        return 0;
    }
}

void tcFormation::GetPositionError(tcPlatformObject* platform, 
								   float& drange_km, float& dbearing_rad, float& deast_km, float& dnorth_km,
								   tcKinematics& leaderKin)
{
	tcGameObject* leader = platform->simState->GetObject(leaderId);
    if (leader == 0)
    {
        wxASSERT(false);
        return;
    }

    // get range and bearing from leader
    leaderKin = leader->mcKin;

    float range_km = leaderKin.RangeToKm(platform->mcKin);
    float bearing_rad = leaderKin.HeadingToGeoRad(platform->mcKin.mfLon_rad, platform->mcKin.mfLat_rad);

    float range_error_km = range_km - range_center_km;

    // bearing of sector center wrt North
    float effectiveBearing = useNorthBearing ? bearing_center_rad : bearing_center_rad + leaderKin.mfHeading_rad;
    if (effectiveBearing < -C_PI) effectiveBearing += C_TWOPI;
    else if (effectiveBearing >= C_PI) effectiveBearing -= C_TWOPI;

    float bearing_error_rad = bearing_rad - effectiveBearing;

    if (bearing_error_rad < -C_PI) bearing_error_rad += C_TWOPI;
    else if (bearing_error_rad >= C_PI) bearing_error_rad -= C_TWOPI;

	// distances from leader to ownship
	float north_km = cosf(bearing_rad)*range_km;
	float east_km = sinf(bearing_rad)*range_km;

	// distances from leader to goal position
	float goal_north_km = cosf(effectiveBearing) * range_center_km;
	float goal_east_km = sinf(effectiveBearing) * range_center_km;

	drange_km = range_error_km;
	dbearing_rad = bearing_error_rad;
	deast_km = goal_east_km - east_km;
	dnorth_km = goal_north_km - north_km;


}


bool tcFormation::HasNewCommand() const
{
    return hasNewCommand;
}

/**
* @return true if this formation is active as a follower
*/
bool tcFormation::IsFollower() const
{
    return (isActive && (leaderId != -1));
}


bool tcFormation::IsInPosition(tcPlatformObject* platform, float bearing_rad, float range_km) const
{
    const tcPlatformObject* leader = GetLeader(platform);
    wxASSERT(leader != 0);
    if (leader == 0) return false;

    float range_error_km = range_km - range_center_km;

    float effectiveBearing = 
        useNorthBearing ? bearing_center_rad : bearing_center_rad + leader->mcKin.mfHeading_rad;
    if (effectiveBearing < -C_PI) effectiveBearing += C_TWOPI;
    else if (effectiveBearing >= C_PI) effectiveBearing -= C_TWOPI;

    float bearing_error_rad = bearing_rad - effectiveBearing;

    if (bearing_error_rad < -C_PI) bearing_error_rad += C_TWOPI;
    else if (bearing_error_rad >= C_PI) bearing_error_rad -= C_TWOPI;

    bool inPosition = (fabsf(range_error_km) < 0.5*range_span_km) && (fabsf(bearing_error_rad) < 0.5*bearing_span_rad);

    return inPosition;
}

/**
* Version to allow a little slop for mouse clicking
*/
bool tcFormation::IsInPositionLoose(tcPlatformObject* platform, float bearing_rad, float range_km) const
{
    const tcPlatformObject* leader = GetLeader(platform);
    wxASSERT(leader != 0);
    if (leader == 0) return false;

    float range_error_km = range_km - range_center_km;

    float effectiveBearing = 
        useNorthBearing ? bearing_center_rad : bearing_center_rad + leader->mcKin.mfHeading_rad;
    if (effectiveBearing < -C_PI) effectiveBearing += C_TWOPI;
    else if (effectiveBearing >= C_PI) effectiveBearing -= C_TWOPI;

    float bearing_error_rad = bearing_rad - effectiveBearing;

    if (bearing_error_rad < -C_PI) bearing_error_rad += C_TWOPI;
    else if (bearing_error_rad >= C_PI) bearing_error_rad -= C_TWOPI;

    bool inPosition = (fabsf(range_error_km) < (0.55*range_span_km + 0.25)) && (fabsf(bearing_error_rad) < 0.5*(bearing_span_rad + 0.1));

    return inPosition;
}

/**
* Version to allow a little slop for mouse clicking
* On triggers near edges
*/
bool tcFormation::IsInPositionLoose2(tcPlatformObject* platform, float bearing_rad, float range_km, 
                                     float& deltaBearing_rad, float& deltaRange_km) const
{
    deltaBearing_rad = 0;
    deltaRange_km = 0;

    const tcPlatformObject* leader = GetLeader(platform);
    wxASSERT(leader != 0);
    if (leader == 0) return false;

    float range_error_km = range_km - range_center_km;

    float effectiveBearing = 
        useNorthBearing ? bearing_center_rad : bearing_center_rad + leader->mcKin.mfHeading_rad;
    if (effectiveBearing < -C_PI) effectiveBearing += C_TWOPI;
    else if (effectiveBearing >= C_PI) effectiveBearing -= C_TWOPI;

    float bearing_error_rad = bearing_rad - effectiveBearing;
    deltaBearing_rad = bearing_error_rad;
    deltaRange_km = range_error_km;

    if (bearing_error_rad < -C_PI) bearing_error_rad += C_TWOPI;
    else if (bearing_error_rad >= C_PI) bearing_error_rad -= C_TWOPI;

    bool nearRangeEdge =   ((range_error_km > -0.58f*range_span_km) && (range_error_km < -0.42f*range_span_km))
                        || ((range_error_km > 0.42f*range_span_km) && (range_error_km < 0.58f*range_span_km));

    bool nearBearingEdge = ((bearing_error_rad > -0.58f*bearing_span_rad) && (bearing_error_rad < -0.42f*bearing_span_rad))
                        || ((bearing_error_rad > 0.42f*bearing_span_rad) && (bearing_error_rad < 0.58f*bearing_span_rad));

    return nearRangeEdge || nearBearingEdge;
}



bool tcFormation::IsLeader() const
{
    return (isActive && (leaderId == -1));
}


void tcFormation::LeaveFormation()
{
    if (!isActive) return;

    if (IsLeader())
    {
        RemoveAllFollowers();
        Clear();
    }
    else
    {
        wxASSERT(platformId != -1);

        tcSimState* simState = tcSimState::Get();
        if (tcPlatformObject* leader = dynamic_cast<tcPlatformObject*>(simState->GetObject(leaderId)))
        {
            leader->formation.RemoveFollower(platformId);
        }

        Clear();
    }

    SetNewCommand();
}

/**
* Normally called when formation leader is destroyed
*/
void tcFormation::RemoveAllFollowers()
{
    wxASSERT(IsLeader());

    tcSimState* simState = tcSimState::Get();

    for (size_t k=0;k<followers.size();k++)
    {
        tcPlatformObject* follower = 
            dynamic_cast<tcPlatformObject*>(simState->GetObject(followers[k]));
        if (follower != 0)
        {
            follower->formation.Clear();
        }
        else
        {
            wxASSERT(false); // follower not found or not platformobj
        }
    }

    isActive = false;
    followers.clear();
}


void tcFormation::RemoveFollower(long id)
{
    if (followers.size() == 0)
    {
        isActive = false;
        SetNewCommand();
        return;
    }

#ifdef _DEBUG
    tcSimState* simState = tcSimState::Get();
    tcPlatformObject* follower = dynamic_cast<tcPlatformObject*>(simState->GetObject(id));
    tcPlatformObject* platform = dynamic_cast<tcPlatformObject*>(simState->GetObject(platformId));
    // in "hostile formation" for intercept, leader doesn't have information about followers
    if ((follower != 0) && (platform != 0) && (follower->GetAlliance() == platform->GetAlliance()))
    {
        wxASSERT(IsLeader());
    }
#endif

    std::vector<long> updatedFollowers;
    for (size_t k=0;k<followers.size();k++)
    {
        if (followers[k] != id) updatedFollowers.push_back(followers[k]);
    }

    wxASSERT(followers.size() == updatedFollowers.size() + 1);
    followers = updatedFollowers;

    // if no more followers, then de-activate this formation
    if (followers.size() == 0)
    {
        isActive = false;
    }

    SetNewCommand();
}

void tcFormation::SaveToPython(scriptinterface::tcScenarioLogger& logger)
{
    if (!IsFollower()) return;

    tcSimState* simState = tcSimState::Get();
    tcPlatformObject* leader = dynamic_cast<tcPlatformObject*>(simState->GetObject(leaderId));

    if (leader == 0) return;

    wxString s;

    s.Printf("leader_id = UI.LookupFriendlyId('%s')", leader->mzUnit.c_str());
    logger.AddScenarioText(s);

    s.Printf("UI.SetFormationLeader(leader_id)");
	logger.AddScenarioText(s);

    s.Printf("UI.SetFormationMode(%d)", int(formationMode));
	logger.AddScenarioText(s);

    s.Printf("UI.SetFormationPosition(%.3f, %.3f, %.3f, %.3f)", 
        range_center_km, range_span_km, bearing_center_rad, bearing_span_rad);
    logger.AddScenarioText(s);

    s.Printf("UI.SetFormationAltitudeOffset(%.1f)", altitudeOffset_m);
    logger.AddScenarioText(s);

    s.Printf("UI.SetFormationUseNorthBearing(%d)", int(useNorthBearing));
    logger.AddScenarioText(s);
}

void tcFormation::SetAltitudeOffset(float dh_m)
{
    altitudeOffset_m = dh_m;
}


void tcFormation::SetFormationMode(int mode)
{
	if (!isActive || IsLeader()) return;

	switch (mode)
	{
	case FOLLOW:
		break;
	case SPRINTDRIFT:
		maneuverType = DRIFT;
		break;
	default:
		wxASSERT(false);
		return;
	}

	formationMode = tcFormation::FormationMode(mode);
}

void tcFormation::SetFormationPosition(float range_km, float span_km, float bearing_rad, float span_rad)
{
    range_center_km = range_km;
    range_span_km = span_km;
    bearing_center_rad = bearing_rad;
    bearing_span_rad = span_rad;
}

void tcFormation::SetUseNorthBearing(bool state)
{
    useNorthBearing = state;
}


void tcFormation::SetNewCommand()
{
    hasNewCommand = true;
}

void tcFormation::SetPlatformId(long id)
{
    platformId = id;
}



void tcFormation::Update(tcPlatformObject* platform)
{
    if (!isActive || IsLeader()) 
    {
        return;
    }

    if (platform->mfStatusTime - lastUpdateTime < 0.5) return;
    lastUpdateTime = platform->mfStatusTime;

	tcGameObject* leader = platform->simState->GetObject(leaderId);
    if ((leader == 0) || (leader->GetDamageLevel() >= 1.0f))
    {
        LeaveFormation();
        return;
    }


    switch (formationMode)
	{
	case FOLLOW:
		UpdateFollow(platform);
		break;
	case SPRINTDRIFT:
		UpdateSprintDrift(platform);
		break;
	default:
		wxASSERT(false);
		break;
	}
    
}

/**
* This version for close formation flying for air-to-air refueling. Should
* work for general air formations too
*/
void tcFormation::Update(tcAirObject* air)
{
    if (!IsFollower()) return;

    if (air->mfStatusTime - lastUpdateTime < 0.5) return;
    lastUpdateTime = air->mfStatusTime;

    tcAirObject* leader = dynamic_cast<tcAirObject*>(air->simState->GetObject(leaderId));
    if ((leader == 0) || (leader->GetDamageLevel() >= 1.0f))
    {
        LeaveFormation();
        return;
    }

    tcAeroAirObject* aero = dynamic_cast<tcAeroAirObject*>(air);

    bool isAeroModel = aero != 0;

    // get range and bearing from leader
    const tcKinematics& leaderKin = leader->mcKin;

    float range_km = leaderKin.RangeToKm(air->mcKin);
    float bearing_rad = leaderKin.HeadingToGeoRad(air->mcKin.mfLon_rad, air->mcKin.mfLat_rad);
    float dAlt_m = leaderKin.mfAlt_m + altitudeOffset_m - air->mcKin.mfAlt_m;

    float range_error_km = range_km - range_center_km;

    // bearing of sector center wrt North
    useNorthBearing = false;
    float effectiveBearing = bearing_center_rad + leaderKin.mfHeading_rad; // always use relative bearing for air formation
    if (effectiveBearing < -C_PI) effectiveBearing += C_TWOPI;
    else if (effectiveBearing >= C_PI) effectiveBearing -= C_TWOPI;

    float bearing_error_rad = bearing_rad - effectiveBearing;

    if (bearing_error_rad < -C_PI) bearing_error_rad += C_TWOPI;
    else if (bearing_error_rad >= C_PI) bearing_error_rad -= C_TWOPI;


    bool inPosition = false;
    if (repositioning)
    {
        inPosition = (fabsf(range_error_km) < 0.25*range_span_km) && (fabsf(bearing_error_rad) < 0.25*bearing_span_rad);
    }
    else
    {
        inPosition = (fabsf(range_error_km) < 0.5*range_span_km) && (fabsf(bearing_error_rad) < 0.5*bearing_span_rad);
    }

    float climbSpeedOffset_kts = 0; // hack to reduce error while climbing/descending
    if (fabsf(dAlt_m) > 1.0f)
    {
        air->SetAltitude(leaderKin.mfAlt_m + altitudeOffset_m);
        if (dAlt_m > 600.0f) // leader above
        {
            climbSpeedOffset_kts = 50.0f;
        }
        else if (dAlt_m < -600.0f) // leader below
        {
            climbSpeedOffset_kts = -50.0f;
        }
    }

    if (inPosition)
    {
        // adjust goalSpeed_kts for faster accel/decel
        float goalSpeed_kts = leaderKin.mfSpeed_kts;
        float speedError_kts = goalSpeed_kts - air->mcKin.mfSpeed_kts;
        speedError_kts = std::max(speedError_kts, -5.0f);
        speedError_kts = std::min(speedError_kts, 5.0f);
        goalSpeed_kts += 2*speedError_kts;

        air->mcGS.mfGoalHeading_rad = leaderKin.mfHeading_rad;
        air->mcGS.mfGoalSpeed_kts = goalSpeed_kts;
        air->SetSpeed(goalSpeed_kts); // automatically set throttle
        repositioning = false;
        return;
    }

    // not in position, readjust to intercept formation position

    tcTrack formCenter;
    formCenter.mfLat_rad = leaderKin.mfLat_rad;
    formCenter.mfLon_rad = leaderKin.mfLon_rad;

    formCenter.Offset(range_center_km, effectiveBearing);

    float distance_error_km = air->mcKin.RangeToKm(formCenter);

    // distances from leader to ownship
    float north_km = cosf(bearing_rad)*range_km;
    float east_km = sinf(bearing_rad)*range_km;

    // distances from leader to goal position
    float goal_north_km = cosf(effectiveBearing) * range_center_km;
    float goal_east_km = sinf(effectiveBearing) * range_center_km;


    float maxMilitarySpeed_mps = 0;

    if (isAeroModel)
    {
        float fuelRate_kgps = 0;
		aero->CalculateSpeedParams(air->mcKin.mfAlt_m, 1.0, maxMilitarySpeed_mps, fuelRate_kgps, aero->GetDamageLevel(), aero->mpDBObject);
    }
    else
    {
        maxMilitarySpeed_mps = C_KTSTOMPS * air->mpDBObject->mfMaxSpeed_kts;
    }


    bool interceptValid = false;
    float intercept_speed_mps = 0;
    float intercept_hdg_rad = 0;

    
    if (distance_error_km < 5.0f)
    {
        float closingSpeed_mps = 5.0f + 7.0f*distance_error_km;

        intercept_hdg_rad = GetLazyInterceptHeadingClosingSpeed(goal_east_km - east_km, 
            goal_north_km - north_km, leaderKin.mfHeading_rad, C_KTSTOMPS*leaderKin.mfSpeed_kts,
            intercept_speed_mps, closingSpeed_mps, interceptValid);
    }
    else
    {
        intercept_hdg_rad = GetInterceptHeading(goal_east_km - east_km, goal_north_km - north_km,
            leaderKin.mfHeading_rad, C_KTSTOMPS*leaderKin.mfSpeed_kts, maxMilitarySpeed_mps,
            interceptValid);
        intercept_speed_mps = maxMilitarySpeed_mps;
        if (!interceptValid && isAeroModel)
        {   // try AB
            float fuelRate_kgps = 0;
            float ABspeed_mps = 0;
            aero->CalculateSpeedParams(air->mcKin.mfAlt_m, 1.0, ABspeed_mps, fuelRate_kgps, aero->GetDamageLevel(), aero->mpDBObject);

            intercept_hdg_rad = GetInterceptHeading(goal_east_km - east_km, goal_north_km - north_km,
                leaderKin.mfHeading_rad, C_KTSTOMPS*leaderKin.mfSpeed_kts, ABspeed_mps,
                interceptValid);
            intercept_speed_mps = ABspeed_mps;
        }
    }

    //// intercept for slowing down (only consider if close enough)
    //float intercept_speed_slow_kts = 0;
    //float intercept_hdg_slow_rad = 0;
    //bool slowValid = false;
    //if (distance_error_km < 5.0f)
    //{
    //    intercept_speed_slow_kts = leaderKin.mfSpeed_kts - 10.0f;
    //    float intercept_speed_slow_mps = C_KTSTOMPS*intercept_speed_slow_kts;

    //    intercept_hdg_slow_rad = GetLazyInterceptHeadingFixedSpeed(goal_east_km - east_km, 
    //        goal_north_km - north_km, leaderKin.mfHeading_rad, C_KTSTOMPS*leaderKin.mfSpeed_kts,
    //        intercept_speed_slow_mps, slowValid);
    //}

    //// intercept for speeding up
    //float intercept_speed_fast_kts = leaderKin.mfSpeed_kts + speed_offset_kts;
    //intercept_speed_fast_kts = std::min(intercept_speed_fast_kts, air->mpDBObject->mfMaxSpeed_kts);
    //bool fastValid = false;
    //float intercept_hdg_fast_rad = GetInterceptHeading(goal_east_km - east_km, goal_north_km - north_km,
    //    leaderKin.mfHeading_rad, C_KTSTOMPS*leaderKin.mfSpeed_kts, C_KTSTOMPS*intercept_speed_fast_kts,
    //    fastValid);

    //float goalSpeed_kts = 0;
    //float goalHeading_rad = 0;
    //if (slowValid)
    //{
    //    // only allow 5 deg deviation from tgt heading for slow intercept hdg
    //    //float dh_rad = intercept_hdg_slow_rad - leaderKin.mfHeading_rad;
    //    //if (dh_rad > C_PI) dh_rad -= C_TWOPI;
    //    //if (dh_rad < -C_PI) dh_rad += C_TWOPI;
    //    //
    //    //if (dh_rad > 0.1f) dh_rad = 0.1f;
    //    //else if (dh_rad < -0.1f) dh_rad = -0.1f;

    //    //goalHeading_rad = leaderKin.mfHeading_rad + dh_rad;

    //    goalHeading_rad = intercept_hdg_slow_rad;
    //    goalSpeed_kts = intercept_speed_slow_kts;

    //}
    //else
    //{            
    //    goalSpeed_kts = intercept_speed_fast_kts + climbSpeedOffset_kts;
    //    goalHeading_rad = intercept_hdg_fast_rad;
    //}

    float goalSpeed_kts = C_MPSTOKTS * intercept_speed_mps;
    float goalHeading_rad = intercept_hdg_rad;

    // adjust goalSpeed_kts for faster accel/decel
    float speedError_kts = goalSpeed_kts - air->mcKin.mfSpeed_kts;
    speedError_kts = std::max(speedError_kts, -10.0f);
    speedError_kts = std::min(speedError_kts, 10.0f);
    goalSpeed_kts += 2*speedError_kts;

    air->mcGS.mfGoalHeading_rad = goalHeading_rad;
    air->mcGS.mfGoalSpeed_kts = goalSpeed_kts;
    air->SetSpeed(goalSpeed_kts);

    repositioning = true;




}


void tcFormation::UpdateFollow(tcPlatformObject* platform)
{
	tcGameObject* leader = platform->simState->GetObject(leaderId);
    if (leader == 0)
    {
        wxASSERT(false);
        return;
    }

    // get range and bearing from leader
    const tcKinematics& leaderKin = leader->mcKin;

    float range_km = leaderKin.RangeToKm(platform->mcKin);
    float bearing_rad = leaderKin.HeadingToGeoRad(platform->mcKin.mfLon_rad, platform->mcKin.mfLat_rad);

    float range_error_km = range_km - range_center_km;

    // bearing of sector center wrt North
    float effectiveBearing = useNorthBearing ? bearing_center_rad : bearing_center_rad + leaderKin.mfHeading_rad;
    if (effectiveBearing < -C_PI) effectiveBearing += C_TWOPI;
    else if (effectiveBearing >= C_PI) effectiveBearing -= C_TWOPI;

    float bearing_error_rad = bearing_rad - effectiveBearing;

    if (bearing_error_rad < -C_PI) bearing_error_rad += C_TWOPI;
    else if (bearing_error_rad >= C_PI) bearing_error_rad -= C_TWOPI;


    bool inPosition = false;
    if (repositioning)
    {
        inPosition = (fabsf(range_error_km) < 0.25*range_span_km) && (fabsf(bearing_error_rad) < 0.25*bearing_span_rad);
    }
    else
    {
        inPosition = (fabsf(range_error_km) < 0.5*range_span_km) && (fabsf(bearing_error_rad) < 0.5*bearing_span_rad);
    }

    if (inPosition)
    {
        platform->mcGS.mfGoalHeading_rad = leaderKin.mfHeading_rad;
        platform->mcGS.mfGoalSpeed_kts = leaderKin.mfSpeed_kts;
        repositioning = false;
    }
    else
    {    
        tcTrack formCenter;
        formCenter.mfLat_rad = leaderKin.mfLat_rad;
        formCenter.mfLon_rad = leaderKin.mfLon_rad;
        
        formCenter.Offset(range_center_km, effectiveBearing);

        float distance_error_km = leaderKin.RangeToKm(formCenter);

        // distances from leader to ownship
        float north_km = cosf(bearing_rad)*range_km;
        float east_km = sinf(bearing_rad)*range_km;

        // distances from leader to goal position
        float goal_north_km = cosf(effectiveBearing) * range_center_km;
        float goal_east_km = sinf(effectiveBearing) * range_center_km;

        float speed_offset_kts = 10.0f;
        if (distance_error_km < 4.5f)
        {
            speed_offset_kts = 1.0f + 2*distance_error_km;
        }

        // intercept for slowing down
        float intercept_speed_slow_mps = 0;
        bool slowValid = false;
        float intercept_hdg_slow_rad = GetLazyInterceptHeading(goal_east_km - east_km, goal_north_km - north_km,
            leaderKin.mfHeading_rad, C_KTSTOMPS*leaderKin.mfSpeed_kts, intercept_speed_slow_mps,
            slowValid);
        float intercept_speed_slow_kts = C_MPSTOKTS*intercept_speed_slow_mps;
        intercept_speed_slow_kts = std::max(intercept_speed_slow_kts, 0.0f);
        
        // intercept for speeding up
        float intercept_speed_fast_kts = leaderKin.mfSpeed_kts + speed_offset_kts;
        intercept_speed_fast_kts = std::min(intercept_speed_fast_kts, platform->mpDBObject->mfMaxSpeed_kts);
        bool fastValid = false;
        float intercept_hdg_fast_rad = GetInterceptHeading(goal_east_km - east_km, goal_north_km - north_km,
            leaderKin.mfHeading_rad, C_KTSTOMPS*leaderKin.mfSpeed_kts, C_KTSTOMPS*intercept_speed_fast_kts,
            fastValid);

        if (slowValid)
        {
            platform->mcGS.mfGoalHeading_rad = intercept_hdg_slow_rad;
            platform->mcGS.mfGoalSpeed_kts = intercept_speed_slow_kts;
        }
        else
        {
            platform->mcGS.mfGoalHeading_rad = intercept_hdg_fast_rad;
            platform->mcGS.mfGoalSpeed_kts = intercept_speed_fast_kts;
        }
        repositioning = true;
    }
}

void tcFormation::UpdateSprintDrift(tcPlatformObject* platform)
{
	float drange_km = 0;
	float dbearing_rad = 0;
	float deast_km = 0;
	float dnorth_km = 0;
	tcKinematics leaderKin;

	GetPositionError(platform, drange_km, dbearing_rad, deast_km, dnorth_km, leaderKin);

	if (maneuverType == DRIFT)
	{
		bool inSector = (fabsf(drange_km) < 0.5*range_span_km) && (fabsf(dbearing_rad) < 0.5*bearing_span_rad);

		platform->mcGS.mfGoalSpeed_kts = 3.0f;
		platform->mcGS.mfGoalHeading_rad = leaderKin.mfHeading_rad;

		if (!inSector) maneuverType = SPRINT_IN;
	}
	else if (maneuverType == SPRINT_IN)
	{
		// intercept sector center until close enough
		float intercept_speed_fast_kts = platform->mpDBObject->mfMaxSpeed_kts;
        bool fastValid = false;
        float intercept_hdg_fast_rad = GetInterceptHeading(deast_km, dnorth_km,
            leaderKin.mfHeading_rad, C_KTSTOMPS*leaderKin.mfSpeed_kts, C_KTSTOMPS*intercept_speed_fast_kts,
            fastValid);

		platform->mcGS.mfGoalHeading_rad = intercept_hdg_fast_rad;
		platform->mcGS.mfGoalSpeed_kts = intercept_speed_fast_kts;

		bool inSector = (fabsf(drange_km) < 0.2*range_span_km) && (fabsf(dbearing_rad) < 0.2*bearing_span_rad);
		if (inSector) maneuverType = SPRINT_OUT;
	}
	else // SPRINT_OUT
	{
		// maintain heading until near edge of sector, then drift
		platform->mcGS.mfGoalHeading_rad = leaderKin.mfHeading_rad;
		platform->mcGS.mfGoalSpeed_kts = leaderKin.mfSpeed_kts + 5.0;

		bool inSectorOuter = (fabsf(drange_km) < 0.3*range_span_km) && (fabsf(dbearing_rad) < 0.3*bearing_span_rad);

		if (!inSectorOuter) maneuverType = DRIFT;
	}

}


tcFormation::tcFormation()
:  isActive(false),
   useNorthBearing(false),
   leaderId(-1),
   lastUpdateTime(0),
   repositioning(false),
   hasNewCommand(false),
   platformId(-1),
   altitudeOffset_m(0)
{
}


tcFormation::~tcFormation()
{
}