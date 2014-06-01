/**
**  @file tcAttackMission.cpp
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

#include "ai/tcAttackMission.h"
#include "ai/tcMissionManager.h"
#include "ai/Brain.h"
#include "ai/BlackboardInterface.h"
#include "ai/Nav.h"
#include "ai/Route.h"
#include "tcWeaponDBObject.h"
#include "tcAirObject.h"
#include "tcPlatformObject.h"
#include "tcSimState.h"
#include "tcScenarioLogger.h"
#include "tcSensorTrackIterator.h"
#include "common/tcGameStream.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace ai;

/**
* Saves state to game stream
*/
tcGameStream& tcAttackMission::operator>>(tcGameStream& stream)
{
    tcMission::operator>>(stream);

    earliestLaunchTime.operator>>(stream);
    stream << launchWindow_min;
    launchTime.operator>>(stream);
    stream << repeatInterval_hr;
	stream << quantity;
    stream << targetType;
	stream << autoAdd;
    stream << targetLon_rad;
    stream << targetLat_rad;
    stream << landingTarget;

    wxASSERT(patrolArea.size() < 256);
    unsigned char nPoints = patrolArea.size();
    stream << nPoints;
    for (unsigned char n=0; n<nPoints; n++)
    {
        patrolArea[n].operator>>(stream);
    }

    return stream;
}

/**
* Loads state from game stream
*/
tcGameStream& tcAttackMission::operator<<(tcGameStream& stream)
{
    tcMission::operator<<(stream);

    earliestLaunchTime.operator<<(stream);
    stream >> launchWindow_min;
    launchTime.operator<<(stream);
    stream >> repeatInterval_hr;
	stream >> quantity;
    stream >> targetType;
	stream >> autoAdd;
    stream >> targetLon_rad;
    stream >> targetLat_rad;
    stream >> landingTarget;

    patrolArea.clear();
    unsigned char nPoints;
    stream >> nPoints;
    for (unsigned char n=0; n<nPoints; n++)
    {
        GeoPoint temp;
        temp.operator<<(stream);

        patrolArea.push_back(temp);
    }

    return stream;
}


void tcAttackMission::AddMissionAircraft(const std::string& name, const std::string& role)
{
    bool autoUpdateQty = ((missionAircraft.size() == quantity) || (quantity == 24) || (quantity == 0));

    tcMission::AddMissionAircraft(name, role);

    if (autoUpdateQty)
    {
        quantity = missionAircraft.size();
    }
}

void tcAttackMission::AdjustLaunchTimeHours(double offset_hr)
{
    earliestLaunchTime.AdjustTimeHours(offset_hr);
    launchTime.AdjustTimeHours(offset_hr);
}


const std::vector<GeoPoint>& tcAttackMission::GetArea() const
{
    return patrolArea;
}

/**
* @return center of patrol area (mean of coordinates)
*/
void tcAttackMission::GetAreaCenter(double& lon_rad, double& lat_rad)
{
    lon_rad = 0;
    lat_rad = 0;

    if (patrolArea.size() == 0)
    {
        wxASSERT(false);
        return;
    }

    std::vector<GeoPoint> patrolAreaUnwrapped = patrolArea;
	// transform from relative to world coordinates (for 1/2 patrolAnchorMode)
	ai::Brain::TransformPatrolAreaForAnchor(patrolAreaUnwrapped, patrolAnchorUnit, patrolAnchorMode, true);


    for (size_t n=0; n<patrolAreaUnwrapped.size(); n++)
    {
        if (patrolAreaUnwrapped[n].mfLon_rad < 0)
        {
            patrolAreaUnwrapped[n].mfLon_rad += C_TWOPI;
        }
    }

    for (size_t n=0; n<patrolAreaUnwrapped.size(); n++)
    {
        lat_rad += patrolAreaUnwrapped[n].mfLat_rad;
        lon_rad += patrolAreaUnwrapped[n].mfLon_rad;
    }

    float rescale = 1.0f / float(patrolAreaUnwrapped.size());
    lat_rad *= rescale;
    lon_rad *= rescale;

    lon_rad += C_TWOPI * (double(lon_rad < -C_PI) - double(lon_rad >= C_PI));
}

void tcAttackMission::GetAreaBounds(tcGeoRect& r)
{
    if (patrolArea.size() < 4)
    {
        wxASSERT(false);
        return;
    }

    TransformToAbsolutePatrolArea();

    std::vector<GeoPoint> patrolAreaUnwrapped = patrolArea;
    for (size_t n=0; n<patrolAreaUnwrapped.size(); n++)
    {
        if (patrolAreaUnwrapped[n].mfLon_rad < 0)
        {
            patrolAreaUnwrapped[n].mfLon_rad += C_TWOPI;
        }
    }
    
    double latMin_rad(999.0);
    double latMax_rad(-999.0);
    double lonMin_rad(999.0);
    double lonMax_rad(-999.0);

    for (size_t n=0; n<patrolAreaUnwrapped.size(); n++)
    {
        latMin_rad = std::min(patrolAreaUnwrapped[n].mfLat_rad, latMin_rad);
        latMax_rad = std::max(patrolAreaUnwrapped[n].mfLat_rad, latMax_rad);

        lonMin_rad = std::min(patrolAreaUnwrapped[n].mfLon_rad, lonMin_rad);
        lonMax_rad = std::max(patrolAreaUnwrapped[n].mfLon_rad, lonMax_rad);
    }

    lonMin_rad += C_TWOPI * (double(lonMin_rad < -C_PI) - double(lonMin_rad >= C_PI));
    lonMax_rad += C_TWOPI * (double(lonMax_rad < -C_PI) - double(lonMax_rad >= C_PI));

    r.Set(lonMin_rad, lonMax_rad, latMin_rad, latMax_rad);

    TransformToRelativePatrolArea();
}



/**
* @return string version of area command
*/
const char* tcAttackMission::GetAreaString() const
{
    static wxString s;
    
    s = "";
    for (size_t n=0; n<patrolArea.size(); n++)
    {
        s += wxString::Format("%.7f,%.7f,", patrolArea[n].mfLon_rad, patrolArea[n].mfLat_rad);
    }

    return s.c_str();
}

bool tcAttackMission::GetAutoAdd() const
{
	return autoAdd;
}

const std::string& tcAttackMission::GetPatrolAnchorUnit() const
{
    return patrolAnchorUnit;
}

int tcAttackMission::GetPatrolAnchorMode() const
{
    return patrolAnchorMode;
}


const std::string& tcAttackMission::GetLandingTarget() const
{
    return landingTarget;
}


const tcDateTime& tcAttackMission::GetLaunchTime() const
{
    return launchTime;
}

/**
* @return a string description of launch time in same format accepted by SetLaunchTimeString
* If launch time is within current UTC day, don't show date. Otherwise start string with YYYY/MM/DD
* If in scenario edit mode, use format with random window HH:MM:SS+<rand min>
*/
const char* tcAttackMission::GetLaunchTimeString() const
{
    static wxString s;

    tcSimState* simState = tcSimState::Get();

    tcDateTime current = simState->GetDateTime();
    bool isEditMode = tcGameObject::IsEditMode();
    tcDateTime launch = isEditMode ? earliestLaunchTime : launchTime;

    bool sameDay = (current.GetYear() == launch.GetYear()) && (current.GetMonth() == launch.GetMonth()) &&
        (current.GetDay() == launch.GetDay());

    if (sameDay)
    {
        s.Printf("%02d:%02d:%02d", launch.GetHour(), launch.GetMinute(), launch.GetSecond());
    }
    else
    {
        s.Printf("%04d/%02d/%02d %02d:%02d:%02d", launch.GetYear(), launch.GetMonth(), launch.GetDay(),
            launch.GetHour(), launch.GetMinute(), launch.GetSecond());
    }

    if (isEditMode)
    {
        s += wxString::Format("+%.0fm", launchWindow_min);

        
    }
    if (repeatInterval_hr > 0)
    {
        s += wxString::Format("+R%.1f", repeatInterval_hr);
    }

    return s.c_str();
}

const char* tcAttackMission::GetMissionType() const
{
    return missionType.c_str();
}

long tcAttackMission::GetSecondsToLaunch() const
{
    tcSimState* simState = tcSimState::Get();
    tcDateTime current = simState->GetDateTime();
    bool isEditMode = tcGameObject::IsEditMode();
    tcDateTime launch = isEditMode ? earliestLaunchTime : launchTime;

    const float days_to_sec = 24.0f*3600.0f;
    float dt_s = days_to_sec * (launch.GetJulianDate() - current.GetJulianDate());

    return long(dt_s + 0.5f);
}

float tcAttackMission::GetTargetLon() const
{
    return targetLon_rad;
}

float tcAttackMission::GetTargetLat() const
{
    return targetLat_rad;
}

int tcAttackMission::GetTargetType() const
{
	return targetType;
}

unsigned int tcAttackMission::GetWaveQuantity() const
{
    return quantity;
}

/**
* Call after all aircraft have departed to remove
* destroyed or landed aircraft from missionAircraft
*
* Don't remove landed aircraft if this is a repetitive mission
*/
void tcAttackMission::RemoveInactiveAircraft()
{
    wxASSERT(missionManager != 0);
    bool repetitive = (repeatInterval_hr > 0);

    tcSimState* simState = tcSimState::Get();

    std::vector<MissionAircraftInfo> temp;
    for (size_t n=0; n<missionAircraft.size(); n++)
    {
        // if aircraft is in the air, then keep it, otherwise remove
        tcGameObject* obj = simState->GetObjectByName(missionAircraft[n].name);

        bool inAir = (obj != 0) && (obj->parent == 0);
        bool landedAtHome = (obj != 0) && (obj->parent == missionManager->GetFlightportParent());

		if (inAir || (repetitive && landedAtHome))
		{
			temp.push_back(missionAircraft[n]);
		}
    }

    missionAircraft = temp;
}


void tcAttackMission::SetMissionType(const std::string& s)    
{
    missionType = s;
}

void tcAttackMission::SetWaveQuantity(unsigned int val)
{
    quantity = val;
}

/**
* If patrolAnchorMode is 1 or 2, transform absolute (world) patrol coordinates to relative coordinates
* expected for these modes
*/
void tcAttackMission::TransformToRelativePatrolArea()
{
    ai::Brain::TransformPatrolAreaForAnchor(patrolArea, patrolAnchorUnit, patrolAnchorMode, false); // false for last arg to do world->relative
}

/**
* If patrolAnchorMode is 1 or 2, transform relative to absolute (world) patrol coordinates
* expected for these modes
*/
void tcAttackMission::TransformToAbsolutePatrolArea()
{
    ai::Brain::TransformPatrolAreaForAnchor(patrolArea, patrolAnchorUnit, patrolAnchorMode, true); // false for last arg to do world->relative
}


/**
* Update active status of aircraft
* @param nActive set to number of active aircraft
*/
void tcAttackMission::UpdateActiveAircraft(unsigned int& nActive)
{
    nActive = 0;
    wxASSERT(missionManager != 0);

    tcSimState* simState = tcSimState::Get();

    std::vector<MissionAircraftInfo> temp;
    for (size_t n=0; n<missionAircraft.size(); n++)
    {
        if (missionAircraft[n].active)
        {
            // if aircraft is in the air, then keep it, otherwise remove
            tcAirObject* air = dynamic_cast<tcAirObject*>(simState->GetObjectByName(missionAircraft[n].name));

            bool inAir = (air != 0) && (air->parent == 0);
            bool landedAtHome = (air != 0) && (air->parent == missionManager->GetFlightportParent());

            if (inAir)
            {
                ai::Brain* brain = air->GetBrain();
                if (brain->TaskExists("Land"))
                {
                    missionAircraft[n].active = false;
                }
            }
            else if (landedAtHome)
            {
                missionAircraft[n].active = false;
            }
        }

        if (missionAircraft[n].active) nActive++;
    }
}

/**
* Update mission parameters of in-flight aircraft to match mission
*/
void tcAttackMission::UpdateInFlightAircraft()
{
	tcSimState* simState = tcSimState::Get();

	for (size_t n=0; n<missionAircraft.size(); n++)
	{
		tcAirObject* obj = dynamic_cast<tcAirObject*>(simState->GetObjectByName(missionAircraft[n].name));
        if ((obj != 0) && (obj->parent == 0))
		{
			UploadUnitMissionInfo(obj);     
		}
	}
}


void tcAttackMission::SaveToPython(scriptinterface::tcScenarioLogger& logger)
{
    wxString s;

    logger.AddScenarioText("");

    s.Printf("mission_id = FP.AddGenericMission()");
    logger.AddScenarioText(s);

    for (size_t n=0; n<missionAircraft.size(); n++)
    {
        s.Printf("FP.AddAircraftToMission(mission_id, '%s')", missionAircraft[n].name.c_str());
        logger.AddScenarioText(s);
    }

    s.Printf("FP.SetMissionLaunchTime(mission_id, '%s')", GetLaunchTimeString());
    logger.AddScenarioText(s);

    s.Printf("FP.SetMissionDatum(mission_id, %.7f, %.7f)", targetLon_rad, targetLat_rad);
    logger.AddScenarioText(s);

    s.Printf("FP.SetMissionLandingTarget(mission_id, '%s')", landingTarget.c_str());
    logger.AddScenarioText(s);

    s.Printf("FP.SetMissionWaveQuantity(mission_id, %d)", quantity);
    logger.AddScenarioText(s);

    s.Printf("FP.SetMissionType(mission_id, '%s')", missionType.c_str());
    logger.AddScenarioText(s);

    if (patrolArea.size() > 2)
    {
        s.Printf("FP.SetMissionPatrolArea(mission_id, '%s')", GetAreaString());
        logger.AddScenarioText(s);

        if (patrolAnchorMode != 0)
        {
            s.Printf("FP.SetMissionPatrolAnchor(mission_id, '%s', %d)", 
                patrolAnchorUnit.c_str(), patrolAnchorMode);
            logger.AddScenarioText(s);
        }
    }

    const std::vector<Route::WaypointData>& waypoints = route.GetWaypoints();
    for (size_t k=0; k<waypoints.size(); k++)
    {
        s.Printf("FP.AddMissionWaypointAdvanced(mission_id, %.7f, %.7f, %.1f, %.1f)", 
            waypoints[k].waypoint.mfLon_rad, waypoints[k].waypoint.mfLat_rad,
            waypoints[k].waypoint.mfAlt_m,  waypoints[k].speed_kts);
        logger.AddScenarioText(s);

        if (route.GetWaypointTasklist(k).size() > 0)
        {
            s.Printf("FP.SetMissionWaypointTasks(mission_id, %d, '%s')", k,
                route.GetWaypointTasklistString(k));
            logger.AddScenarioText(s);
        }
    }


}

void tcAttackMission::SetLandingTarget(const std::string& s)
{
    if (isLocked) return;
    landingTarget = s;
}


void tcAttackMission::SetLaunchTimeFromString(const char* s)
{
    if (isLocked) return;

    tcSimState* simState = tcSimState::Get();
    tcDateTime current = simState->GetDateTime();
    
    long nYear = current.GetYear();
    long nMonth = current.GetMonth();
    long nDay = current.GetDay();
    long nHour = current.GetHour();
    long nMin = current.GetMinute();
    long nSec = 0;
    double launch_window = 0;
    double repeat_interval = 0;

    wxString s2(s);
    if (s2.Contains('/'))
    { // assume YYYY/MM/DD HH:MM:SS format
        wxString yyyy = s2.BeforeFirst('/');
        yyyy.ToLong(&nYear);
        s2 = s2.AfterFirst('/');

        wxString mm = s2.BeforeFirst('/');
        mm.ToLong(&nMonth);
        s2 = s2.AfterFirst('/');

        wxString dd = s2.BeforeFirst(' ');
        dd.ToLong(&nDay);
        s2 = s2.AfterFirst(' ');
    }

    wxString hh = s2.BeforeFirst(':');
    hh.ToLong(&nHour);
    s2 = s2.AfterFirst(':');

    wxString minmin = s2.BeforeFirst(':');
    minmin.ToLong(&nMin);
    s2 = s2.AfterFirst(':');

    wxString ss = s2.BeforeFirst('+');
    ss.ToLong(&nSec);

    wxString randmin = s2.AfterFirst('+');
    randmin = randmin.BeforeFirst('m');
    randmin.ToDouble(&launch_window);

    // update launch time params
    tcDateTime updatedLaunch(nYear, nMonth, nDay, nHour, nMin, nSec);

    SetRandomLaunchTime(updatedLaunch, float(launch_window));
    if (launchTime < current) SetLaunchTime(current);

    // update repeat params
    wxString repeatInterval = s2.AfterFirst('R');
    repeatInterval.ToDouble(&repeat_interval);
    repeatInterval_hr = repeat_interval;

}

void tcAttackMission::SetPatrolAnchor(const std::string& unitName, int mode)
{
    patrolAnchorUnit = unitName;
    patrolAnchorMode = mode;

    if (patrolAnchorMode > 0)
    {
        tcSimState* simState = tcSimState::Get();
        tcPlatformObject* obj = dynamic_cast<tcPlatformObject*>(simState->GetObjectByName(patrolAnchorUnit));
        if (obj != 0)
        {
            referencePosition.mfLon_rad = obj->mcKin.mfLon_rad;
            referencePosition.mfLat_rad = obj->mcKin.mfLat_rad;
            referenceHeading_rad = obj->mcKin.mfHeading_rad;
        }
    }
}


void tcAttackMission::UpdateTargetInfo()
{
    wxASSERT(missionManager != 0);
	if (missionManager == 0) return;

 //   tcGameObject* host = missionManager->GetFlightportParent();
 //   if (host == 0)
 //   {
 //       EndMission();
 //       return;
 //   }

 //   
	//tcSimState* simState = tcSimState::Get();
 //   tcSensorMapTrack targetTrack;
 //   if (!simState->GetTrack(targetId, host->GetAlliance(), targetTrack))
 //   {
 //       EndMission(); // target doesn't exist
 //       return;
 //   }

 //   if (targetTrack.IsSurface())
 //   {
 //       targetType = SURFACE_TARGET;
 //   }
 //   else if (targetTrack.IsAir())
 //   {
 //       targetType = AIR_TARGET;
 //   }
 //   else if (targetTrack.IsMissile())
 //   {
 //       targetType = MISSILE_TARGET;
 //   }
 //   else if (targetTrack.IsSub())
 //   {
 //       targetType = SUBSURFACE_TARGET;
 //   }
 //   else if (targetTrack.IsGround())
 //   {
 //       targetType = LAND_TARGET;
 //   }
 //   else 
 //   {
 //       targetType = 0; // error, unknown target type
 //   }

}

/**
* @return number of mission aircraft in the air (remainder still launching presumably)
*/
unsigned int tcAttackMission::GetAirborneAircraftCount() const
{
    unsigned int nAirborne = 0;

    tcSimState* simState = tcSimState::Get();

	for (size_t n=0; n<missionAircraft.size(); n++)
	{
		tcPlatformObject* obj = dynamic_cast<tcPlatformObject*>(simState->GetObjectByName(missionAircraft[n].name));
        if ((obj != 0) && (obj->parent == 0))
		{
            nAirborne++;
		}
	}
    return nAirborne;
}

/**
* Gets vector of aircraft indices that are loaded and ready to launch for the mission
*/
void tcAttackMission::GetReadyAircraft(std::vector<unsigned int>& readyAircraft)
{
    readyAircraft.clear();

    for (size_t n=0; n<missionAircraft.size(); n++)
    {
        tcAirObject* aircraft = missionManager->GetAircraft(missionAircraft[n].name);
        if ((aircraft != 0) && (!missionAircraft[n].active))
        {
            if (!aircraft->IsLoading() && !aircraft->IsOverweight() && !aircraft->IsRefueling() && !aircraft->MaintenanceHold())
            {
                readyAircraft.push_back(n);
            }
        }
    }
}

float tcAttackMission::GetRepeatIntervalHours() const
{
	return repeatInterval_hr;
}

/**
* Gets vector of aircraft indices that are landed, inactive, unloaded, and ready to load with equipment
*/
void tcAttackMission::GetAircraftToLoad(std::vector<unsigned int>& loadTheseAircraft)
{
    loadTheseAircraft.clear();

    for (size_t n=0; n<missionAircraft.size(); n++)
    {
        tcAirObject* aircraft = missionManager->GetAircraft(missionAircraft[n].name);
        if ((aircraft != 0) && (!missionAircraft[n].active))
        {
            std::string loadoutTag = aircraft->GetLoadoutTag();
            bool isEmpty = (loadoutTag.size() == 0) || (loadoutTag == "Empty");
            if (isEmpty && !aircraft->MaintenanceHold() && !aircraft->IsLoading())
            {
                loadTheseAircraft.push_back(n);
            }
        }
    }
}


/**
* @return true if a target datum or target track ID has been loaded
*/
bool tcAttackMission::HasTarget() const
{
    return ((targetLon_rad != 0) || (targetLat_rad != 0));
}

/**
* @return true if a target datum has been loaded
*/
bool tcAttackMission::HasTargetDatum() const
{
    return ((targetLon_rad != 0) || (targetLat_rad != 0));
}

void tcAttackMission::InitializeLaunchTime()
{
    tcSimState* simState = tcSimState::Get();
    launchTime = simState->GetDateTime();
    launchTime.AdjustTimeSeconds(3600.0f); // 1 hour offset for now
    earliestLaunchTime = launchTime;
    launchWindow_min = 0;
    repeatInterval_hr = 0;
}

/**
* If mission type is non-empty and not "default", check if mission type
* conditions are satisfied for launch (e.g. targets in patrol area)
*/
bool tcAttackMission::MissionTypeIsReady()
{
    wxString missionTypeString(missionType.c_str());

    if ((patrolArea.size() < 4) || (missionTypeString.size() == 0) || (missionTypeString == "Default"))
    {
        return true;
    }

    if (missionTypeString.Contains("Standby"))
    {
        wxString standbyType = missionTypeString.AfterFirst('-');
        unsigned int classificationId = 0x1000; // set to classification that doesn't match anything
        if (standbyType == "AAW")
        {
            classificationId = PTYPE_AIR;
        }
        else if (standbyType == "ASW")
        {
            classificationId = PTYPE_SUBSURFACE;
        }
        else if (standbyType == "ASuW")
        {
            classificationId = PTYPE_SURFACE;
        }
        else if (standbyType == "Strike")
        {
            classificationId = PTYPE_GROUND;
        }

        tcGeoRect filterRegion;
        GetAreaBounds(filterRegion);

        unsigned char alliance = missionManager->GetFlightportParent()->GetAlliance();

        tcSensorTrackIterator iter(alliance, classificationId, filterRegion);
        return (iter.Size() > 0);
    }

    return true;
}

/**
* If no mission aircraft are in flight with an active "CAP" task,
* then restart the mission
*/
void tcAttackMission::MonitorMissionInProgress()
{
	//tcSimState* simState = tcSimState::Get();

	//bool anyInFlight = false;
	//for (size_t n=0; (n<missionAircraft.size()) && (!anyInFlight); n++)
	//{
	//	tcPlatformObject* obj = dynamic_cast<tcPlatformObject*>(simState->GetObjectByName(missionAircraft[n].name));
	//	if (obj != 0)
	//	{
	//		if (obj->GetBrain()->TaskExists("CAP")) anyInFlight = true;
	//	}
	//}

	//if (!anyInFlight) stage = "init"; // launch another patrol
}


void tcAttackMission::RemoveMissionAircraft(const std::string& name)
{
    bool autoUpdateQty = (missionAircraft.size() == quantity);

    tcMission::RemoveMissionAircraft(name);

    if (autoUpdateQty) quantity = missionAircraft.size();
}

void tcAttackMission::SetArea(const std::vector<GeoPoint>& area)
{
    if (isLocked) return;

    patrolArea = area;

    for (size_t n=1; n<patrolArea.size(); n++)
    {
        if ((patrolArea[n].mfLat_rad == patrolArea[n-1].mfLat_rad) && 
            (patrolArea[n].mfLon_rad == patrolArea[n-1].mfLon_rad))
        {
            // duplicate point, try to fix it
            patrolArea[n].mfLat_rad = patrolArea[n-1].mfLat_rad + 0.001f;
            patrolArea[n].mfLon_rad = patrolArea[n-1].mfLon_rad + 0.001f;
        }
    }

}

void tcAttackMission::SetAreaByString(const std::string& s)
{
    if (isLocked) return;

    std::vector<GeoPoint> patrolAreaTemp;
    
    wxString areaString(s.c_str());

    wxString slon = areaString.BeforeFirst(',');
    areaString = areaString.AfterFirst(',');
    wxString slat = areaString.BeforeFirst(',');
    areaString = areaString.AfterFirst(',');

    while (slat.size() > 0)
    {
        double lon_rad = 0;
        double lat_rad = 0;
        slon.ToDouble(&lon_rad);
        slat.ToDouble(&lat_rad);
        
        GeoPoint p;
        p.Set(lon_rad, lat_rad, 0);
        patrolAreaTemp.push_back(p);

        slon = areaString.BeforeFirst(',');
        areaString = areaString.AfterFirst(',');
        slat = areaString.BeforeFirst(',');
        areaString = areaString.AfterFirst(',');
    }

    SetArea(patrolAreaTemp);

}

void tcAttackMission::SetAutoAdd(bool state)
{
	autoAdd = state;
}


void tcAttackMission::SetLaunchTime(const tcDateTime& dateTime)
{
    if (isLocked) return;

    launchTime = dateTime;
    if (tcGameObject::IsEditMode())
    {
        earliestLaunchTime = launchTime;
    }
}

void tcAttackMission::SetRandomLaunchTime(const tcDateTime& earliest, float window_min)
{
    if (isLocked) return;

    earliestLaunchTime = earliest;
    launchWindow_min = window_min;
    launchTime = earliest;

    if (!tcGameObject::IsEditMode())
    {
        launchTime.AdjustTimeHours(randf(0.0166666667*launchWindow_min)); // pick a random time
    }
}


void tcAttackMission::SetRepeatIntervalHours(float val)
{
	repeatInterval_hr = val;
}


void tcAttackMission::SetTargetDatum(float lon_rad, float lat_rad)
{
    if (isLocked) return;

    targetLon_rad = lon_rad;
    targetLat_rad = lat_rad;
}


void tcAttackMission::SetTargetType(int val)
{
	targetType = val;
}


void tcAttackMission::Update(double t)
{
	wxASSERT(missionManager != 0);
	if (missionManager == 0) return;

    UpdateRelativePosition();

	// step 1, get aircraft for mission
    // step 2, wait for launch time
	// step 2, outfit aircraft
	// step 3, create tasks for mission on each aircraft
	// step 4, order launch of aircraft
	// step 5, when all aircraft launched, wait until aircraft landed
	// step 6, start over if target not destroyed
    
    tcSimState* simState = tcSimState::Get();

	if (stage == "init")
	{
		stage = "wait";
	}
	else if (stage == "wait")
	{
        ReadyAllAircraft();

        // wait until at least <quantity> aircraft are ready
        std::vector<unsigned int> readyAircraft;
        GetReadyAircraft(readyAircraft);
        size_t nReady = readyAircraft.size();

        tcDateTime currentTime = simState->GetDateTime();
        if ((nReady >= quantity) && (currentTime > launchTime) && MissionTypeIsReady())
        {
            stage = "launch";
        }
		else if ((nReady < quantity) && (missionAircraft.size() < 3*quantity) && autoAdd)
		{	
			size_t numberToAdd = size_t(quantity) - nReady;
			std::vector<MissionAircraftInfo> candidates = missionManager->GetAvailableAircraft(targetType);
			unsigned int startQuantity = quantity;
			for (size_t n=0; (n<numberToAdd)&&(n<candidates.size()); n++)
			{
				AddMissionAircraft(candidates[n].name, candidates[n].role);
				quantity = startQuantity; // hack to keep autoadd from increasing quantity
			}
		}
	}
	else if (stage == "launch")
	{
        isLocked = true;

        std::vector<unsigned int> readyAircraft;
        GetReadyAircraft(readyAircraft);

        for (size_t k=0; (k<readyAircraft.size()) && (k < quantity); k++)
		{
            size_t n = readyAircraft[k];

            if (tcAirObject* air = missionManager->GetAircraft(missionAircraft[n].name))
            {
                UploadUnitMissionInfo(air);

                // record loadout so we can reload the same for repeat missions
                missionAircraft[n].loadout = air->GetLoadoutCommand();
                missionAircraft[n].active = true;
			    missionManager->LaunchAircraft(missionAircraft[n].id);
            }
		}
		stage = "waitlaunch";
	}
	else if (stage == "waitlaunch")
	{
		// verify all aircraft have launched and end mission
		if (AllMissionAircraftDeparted())
		{
			stage = "waitland";
		}
	}
    else if (stage == "waitland")
    {	
        // do following at slower update
	    double dt = t - lastUpdate;
	    if (dt < 30.0) return;
	    lastUpdate = t;

        RemoveInactiveAircraft();

        unsigned int nActive = 0;
        UpdateActiveAircraft(nActive);

        ReadyAllAircraft();

        if (nActive == 0)
        {
            if ((missionAircraft.size() == 0) || (repeatInterval_hr <= 0))
            {
                stage = "complete";
            }
            else
            {
                stage = "reload";
            }
        }
    }
    else if (stage == "reload")
    {
        // schedule next launch
        isLocked = false;
        tcDateTime nextLaunch = launchTime;
        nextLaunch.AdjustTimeHours(repeatInterval_hr); 
        SetRandomLaunchTime(nextLaunch, launchWindow_min);

        stage = "wait"; // loop back to wait stage for next mission
    }

    if (stage == "complete")
    {
        EndMission();
    }
}

/**
* Attempt to reload and ready all aircraft that aren't active or currently ready
*/
void tcAttackMission::ReadyAllAircraft()
{
    ReadyOverweightAircraft();

    std::vector<unsigned int> loadTheseAircraft;
    GetAircraftToLoad(loadTheseAircraft);

    // order loadout for aircraft
    for (size_t n=0; n<loadTheseAircraft.size(); n++)
    {
        unsigned int idx = loadTheseAircraft[n];
        if (tcAirObject* air = missionManager->GetAircraft(missionAircraft[idx].name))
        {
            missionAircraft[idx].id = air->mnID; // update ID since it may have changed after landing (?)
            if (missionAircraft[idx].loadout.size() == 0)
            {
                missionAircraft[idx].loadout = air->GetLoadoutCommand();
            }
            air->ScheduleLoadoutCommand(missionAircraft[idx].loadout);
        }
    }
}

/**
* Find overweight aircraft and try defueling, removing equipment
*/
void tcAttackMission::ReadyOverweightAircraft()
{
    for (size_t n=0; n<missionAircraft.size(); n++)
    {
        tcAirObject* aircraft = missionManager->GetAircraft(missionAircraft[n].name);
        if ((aircraft != 0) && (!missionAircraft[n].active))
        {
            if (aircraft->IsOverweight() && !aircraft->IsLoading() && !aircraft->IsRefueling())
            {
                aircraft->LightenLoad();
            }
        }
    }
}

/**
* Update patrol area to new center
* Handle transforms for world/relative automatically, input parameters are absolute lon and lat
*/
void tcAttackMission::RecenterArea(double lon_rad, double lat_rad)
{
	double lonCenter_rad = 0;
	double latCenter_rad = 0;

	// get current center
	GetAreaCenter(lonCenter_rad, latCenter_rad);
	double dlon_rad = lon_rad - lonCenter_rad;
	double dlat_rad = lat_rad - latCenter_rad;

	std::vector<GeoPoint> updatedPatrolArea = patrolArea;

	// false for last arg to do world->relative, true to do relative->world
	ai::Brain::TransformPatrolAreaForAnchor(updatedPatrolArea, patrolAnchorUnit, patrolAnchorMode, true);

	for (size_t n=0; n<updatedPatrolArea.size(); n++)
	{
		updatedPatrolArea[n].mfLon_rad += dlon_rad;
		updatedPatrolArea[n].mfLat_rad += dlat_rad;

		// adjust for any wrapping that occurred
		updatedPatrolArea[n].mfLon_rad += C_TWOPI * (double(lon_rad < -C_PI) - double(lon_rad >= C_PI));
	}

	ai::Brain::TransformPatrolAreaForAnchor(updatedPatrolArea, patrolAnchorUnit, patrolAnchorMode, false);
	patrolArea = updatedPatrolArea;
}



/**
* For patrolAnchorMode > 0, update route waypoint coordinates to maintain relative offset from mission host
*/
void tcAttackMission::UpdateRelativePosition()
{
    if (patrolAnchorMode <= 0) return;

    tcSimState* simState = tcSimState::Get();
    tcPlatformObject* obj = dynamic_cast<tcPlatformObject*>(simState->GetObjectByName(patrolAnchorUnit));
    if (obj == 0) return;

    float dlon_rad = obj->mcKin.mfLon_rad - referencePosition.mfLon_rad;
    float dlat_rad = obj->mcKin.mfLat_rad - referencePosition.mfLat_rad;
    float dhdg_rad = obj->mcKin.mfHeading_rad - referenceHeading_rad;
    float cos_hdg = cosf(dhdg_rad);
    float sin_hdg = sinf(dhdg_rad);
    float cos_lat = cosf(referencePosition.mfLat_rad);
    float sec_lat = 1.0 / cos_lat;

    std::vector<Route::WaypointData>& waypoints = route.GetWaypointsMutable();
    for (size_t n=0; n<waypoints.size(); n++)
    {
        float east_rad = cos_lat * (waypoints[n].waypoint.mfLon_rad - referencePosition.mfLon_rad);
        float north_rad = waypoints[n].waypoint.mfLat_rad - referencePosition.mfLat_rad;

        waypoints[n].waypoint.mfLon_rad = sec_lat*(cos_hdg*east_rad + sin_hdg*north_rad) + dlon_rad + referencePosition.mfLon_rad;
        waypoints[n].waypoint.mfLat_rad = cos_hdg*north_rad - sin_hdg*east_rad + dlat_rad + referencePosition.mfLat_rad;
    }

    referencePosition.mfLon_rad = obj->mcKin.mfLon_rad;
    referencePosition.mfLat_rad = obj->mcKin.mfLat_rad;
    referenceHeading_rad = obj->mcKin.mfHeading_rad;

    wxASSERT(patrolAnchorMode == 2);

}

void tcAttackMission::UploadUnitMissionInfo(tcAirObject* air)
{
	wxASSERT(air != 0);

	ai::Brain* brain = air->GetBrain();

	if (brain->GetNavTask() == 0)
	{
		brain->AddTaskDirectly("Nav", 2.0, 0);
	}
	ai::Nav* nav = brain->GetNavTask();
	if (nav != 0)
	{
		unsigned currentWaypoint = nav->GetCurrentWaypoint(); // preserve current waypoint in case this is an in-flight update
		nav->SetRoute(&route); // upload mission route
		nav->SetCurrentWaypoint(currentWaypoint);
	}
	ai::BlackboardInterface bb = brain->GetBlackboardInterface();

	// upload target information
	if ((targetLon_rad != 0) || (targetLat_rad != 0))
	{
		wxString lonString = wxString::Format("%.7f", targetLon_rad);
		wxString latString = wxString::Format("%.7f", targetLat_rad);
		bb.Write("DatumLongitude", lonString.ToStdString());
		bb.Write("DatumLatitude", latString.ToStdString());
	}

	if (landingTarget.size() > 0)
	{
		bb.Write("LandTarget", landingTarget);
	}

	UploadUnitPatrolInfo(bb);

	// mission ID string to access mission data
	wxString missionIdent = wxString::Format("%04d-%04d", missionManager->GetFlightportParentId(), this->GetId());
	bb.Write("Mission", missionIdent.ToStdString());
}

void tcAttackMission::UploadUnitPatrolInfo(ai::BlackboardInterface& bb)
{
    bb.Erase("PatrolArea");
    bb.Erase("PatrolAnchor");

    if (patrolArea.size() > 2)
    {
        wxString s;
        for (size_t n=0; n<patrolArea.size(); n++)
        {
            s += wxString::Format("%.7f,%.7f,", patrolArea[n].mfLon_rad, patrolArea[n].mfLat_rad);
        }
        bb.Write("PatrolArea", s.ToStdString());

        if ((patrolAnchorMode > 0) && (patrolAnchorUnit.size() > 0))
        {
            tcSimState* simState = tcSimState::Get();
            if (tcGameObject* anchorObj = simState->GetObjectByName(patrolAnchorUnit))
            {
                s.Printf("%s,%d", patrolAnchorUnit.c_str(), patrolAnchorMode);
                bb.Write("PatrolAnchor", s.ToStdString());
            }
        }
    }
}


const tcAttackMission& tcAttackMission::operator=(const tcAttackMission& src)
{
    tcMission::operator=(src);

    quantity = src.quantity;
    targetType = src.targetType;
	autoAdd = src.autoAdd;
    targetLon_rad = src.targetLon_rad;
    targetLat_rad = src.targetLat_rad;

    launchTime = src.launchTime;
    earliestLaunchTime = src.earliestLaunchTime;
    launchWindow_min = src.launchWindow_min;
    repeatInterval_hr = src.repeatInterval_hr;

    referencePosition = src.referencePosition;
    referenceHeading_rad = src.referenceHeading_rad;

    return *this;
}


tcAttackMission::tcAttackMission(const tcAttackMission& src)
: tcMission(src),
  quantity(src.quantity),
  targetType(src.targetType),
  autoAdd(src.autoAdd),
  targetLon_rad(src.targetLon_rad),
  targetLat_rad(src.targetLat_rad),
  launchTime(src.launchTime),
  earliestLaunchTime(src.earliestLaunchTime),
  launchWindow_min(src.launchWindow_min),
  repeatInterval_hr(src.repeatInterval_hr),
  patrolAnchorUnit(src.patrolAnchorUnit),
  patrolAnchorMode(src.patrolAnchorMode),
  referencePosition(src.referencePosition),
  referenceHeading_rad(src.referenceHeading_rad)
{
}

tcAttackMission::tcAttackMission(unsigned int id_, tcMissionManager* mm)
: tcMission(id_, mm),
  quantity(24),
  targetType(0),
  autoAdd(false),
  targetLon_rad(0),
  targetLat_rad(0),
  launchWindow_min(0),
  repeatInterval_hr(0),
  patrolAnchorMode(0),
  referenceHeading_rad(0)
{
}

tcAttackMission::tcAttackMission()
: tcMission(),
  quantity(24),
  targetType(0),
  autoAdd(false),
  targetLon_rad(0),
  targetLat_rad(0),
  launchWindow_min(0),
  repeatInterval_hr(0),
  patrolAnchorMode(0),
  referenceHeading_rad(0)
{
    InitializeLaunchTime();
}


tcAttackMission::~tcAttackMission() 
{
}