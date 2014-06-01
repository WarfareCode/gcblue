/**  
**  @file tcFlightPortInterface.cpp
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

#include "stdwx.h" // precompiled header file

#ifndef WX_PRECOMP
#include "wx/wx.h"
#ifdef WIN32
#include "wx/msw/private.h" // for MS Windows specific definitions
#endif
#endif

#include <string>
#include "tcFlightPortInterface.h"
#include "tcPlatformInterface.h"
#include "tcMapOverlay.h"
#include "tcMapMissionObject.h"
#include "tcSimState.h"
#include "tcHeloObject.h"
#include "simmath.h"
#include "tcSoundConsole.h"
#include "ai/tcMissionManager.h"
#include "ai/tcAttackMission.h"
#include "ai/tcCAPMission.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif 

using namespace boost::python;

namespace scriptinterface 
{

    object tcFlightPortInterface::GetInterface() 
    {
        class_<tcFlightUnitStatus>("FlightUnitStatus")
            .def_readonly("name",&tcFlightUnitStatus::unit_name)
            .def_readonly("current_loc",&tcFlightUnitStatus::current_loc)
            .def_readonly("goal_loc",&tcFlightUnitStatus::goal_loc)
            .def_readonly("atDestination",&tcFlightUnitStatus::atDestination)
            .def_readonly("isIdle",&tcFlightUnitStatus::isIdle)
            .def_readonly("runway",&tcFlightUnitStatus::runway)
            .def_readonly("ready_time",&tcFlightUnitStatus::ready_time)
            ;

        object InterfaceType = class_<tcFlightPortInterface>("FlightPortInterface")
            .def("GetCurrentTime",&tcFlightPortInterface::GetTime)
            .def("GetUnitCount", &tcFlightPortInterface::GetUnitCount)
            .def("GetUnitID", &tcFlightPortInterface::GetUnitID)
            .def("GetUnitName", &tcFlightPortInterface::GetUnitName)
            .def("GetUnitStatus", &tcFlightPortInterface::GetUnitStatus)
            .def("GetUnitLocation", &tcFlightPortInterface::GetUnitLocation)
            .def("GetUnitGoalLocation", &tcFlightPortInterface::GetUnitGoalLocation)
			.def("GetUnitPlatformInterface", &tcFlightPortInterface::GetUnitPlatformInterface)
            .def("IsValid", &tcFlightPortInterface::IsValid)
            .def("Launch", &tcFlightPortInterface::Launch)
            .def("LaunchID", &tcFlightPortInterface::LaunchID)
            .def("SetDestination", &tcFlightPortInterface::SetDestination)

            .def("GetLocalObj",&tcFlightPortInterface::GetLocalObj)

            // mission related commands			
            .def("AddGenericMission", &tcFlightPortInterface::AddGenericMission)
            .def("AddAircraftToMission", &tcFlightPortInterface::AddAircraftToMission)
			.def("AddCAPMission", &tcFlightPortInterface::AddCAPMission)
            .def("AddAEWMission", &tcFlightPortInterface::AddAEWMission)
            .def("AddASWMission", &tcFlightPortInterface::AddASWMission)
			.def("AddAttackMission", &tcFlightPortInterface::AddAttackMission)
            .def("GetMissionCount", &tcFlightPortInterface::GetMissionCount)
            .def("GetMissionId", &tcFlightPortInterface::GetMissionId)
            .def("GetEditMissionId", &tcFlightPortInterface::GetEditMissionId)
            .def("SetEditMissionId", &tcFlightPortInterface::SetEditMissionId)
            .def("AddMissionWaypoint", &tcFlightPortInterface::AddMissionWaypoint)
            .def("AddMissionWaypointAdvanced", &tcFlightPortInterface::AddMissionWaypointAdvanced)
            .def("EditMissionWaypoint", &tcFlightPortInterface::EditMissionWaypoint)
            .def("EditMissionWaypointAdvanced", &tcFlightPortInterface::EditMissionWaypointAdvanced)
            .def("EditMissionWaypointReference", &tcFlightPortInterface::EditMissionWaypointReference)
            .def("GetMissionWaypointCount", &tcFlightPortInterface::GetMissionWaypointCount)
            .def("InsertMissionWaypoint", &tcFlightPortInterface::InsertMissionWaypoint)
            .def("ClearMissionWaypoints", &tcFlightPortInterface::ClearMissionWaypoints)
            .def("DeleteMissionWaypoint", &tcFlightPortInterface::DeleteMissionWaypoint)
            .def("SetMissionWaypointTasks", &tcFlightPortInterface::SetMissionWaypointTasks)
            .def("AddMissionWaypointTask", &tcFlightPortInterface::AddMissionWaypointTask)
            .def("RemoveMissionWaypointTask", &tcFlightPortInterface::RemoveMissionWaypointTask)
            .def("SetMissionDatum", &tcFlightPortInterface::SetMissionDatum)
            .def("SetMissionLandingTarget", &tcFlightPortInterface::SetMissionLandingTarget)
            .def("SetMissionLaunchTime", &tcFlightPortInterface::SetMissionLaunchTime)
            .def("SetMissionPatrolArea", &tcFlightPortInterface::SetMissionPatrolArea)
            .def("GetMissionPatrolArea", &tcFlightPortInterface::GetMissionPatrolArea)
            .def("SetMissionPatrolAnchor", &tcFlightPortInterface::SetMissionPatrolAnchor)
            .def("SetMissionType", &tcFlightPortInterface::SetMissionType)
            .def("GetMissionType", &tcFlightPortInterface::GetMissionType)
            .def("TransformToRelativePatrolArea", &tcFlightPortInterface::TransformToRelativePatrolArea)
            .def("TransformToAbsolutePatrolArea", &tcFlightPortInterface::TransformToAbsolutePatrolArea)
            .def("SetMissionWaveQuantity", &tcFlightPortInterface::SetMissionWaveQuantity)
            .def("HasAircraftForMission", &tcFlightPortInterface::HasAircraftForMission)
            ; 
        return InterfaceType;
    }

    tcFlightPort* tcFlightPortInterface::static_flightport = 0;
    tcSimState* tcFlightPortInterface::mpSimState = 0;
    tcSoundConsole* tcFlightPortInterface::mpConsole = 0;
    tcMapOverlay* tcFlightPortInterface::overlay = 0;


	unsigned int tcFlightPortInterface::AddGenericMission()
    {
        if (flightport == 0) return 0; // 0 is error id

        ai::tcMissionManager* missionManager = flightport->GetOrCreateMissionManager();
		
        ai::tcAttackMission* attack = new ai::tcAttackMission();
		//attack->SetTarget(targetId);

		missionManager->AddMission(attack);

        return attack->GetId();

        //tcMapMissionObject* missionObj = new tcMapMissionObject(flightport->parent->mnID, cap->GetId());
        //missionObj->SetInteractive(true);

        //overlay->AddMapObject(missionObj);
    }

    void tcFlightPortInterface::AddAircraftToMission(unsigned int missionId, const std::string& aircraft)
    {
        if (flightport == 0) return;
        ai::tcMissionManager* missionManager = flightport->GetOrCreateMissionManager();

        if (ai::tcMission* mission = missionManager->GetMission(missionId))
        {
            mission->AddMissionAircraft(aircraft, "Strike");
        }

    }

	void tcFlightPortInterface::AddAttackMission(long targetId)
	{
		if ((flightport == 0) || (flightport->parent == 0)) return;
        ai::tcMissionManager* missionManager = flightport->GetOrCreateMissionManager();

		tcSensorMapTrack track;
		if (!mpSimState->GetTrack(targetId, flightport->parent->GetAlliance(), track))
		{
			return; // targetId track not found
		}
		
		float lon_rad = track.mfLon_rad;
		float lat_rad = track.mfLat_rad;
		float alt_m = track.mfAlt_m;

		int targetType = 0;
		if (track.IsAir()) targetType = AIR_TARGET;
		else if (track.IsSurface()) targetType = SURFACE_TARGET;
		else if (track.IsSub()) targetType = SUBSURFACE_TARGET;
		else if (track.IsGround()) targetType = LAND_TARGET;
		else
		{
			return;
		}

		ai::tcAttackMission* attackMission = new ai::tcAttackMission();
		std::vector<GeoPoint> patrolArea;
		float lonOffset_rad = (1/cosf(lat_rad)) * C_MTORAD * 15e3f;
		float latOffset_rad =  C_MTORAD * 15e3f;
		patrolArea.push_back(GeoPoint(lon_rad - lonOffset_rad, lat_rad + latOffset_rad, 0));
		patrolArea.push_back(GeoPoint(lon_rad + lonOffset_rad, lat_rad + latOffset_rad, 0));
		patrolArea.push_back(GeoPoint(lon_rad + lonOffset_rad, lat_rad - latOffset_rad, 0));
		patrolArea.push_back(GeoPoint(lon_rad - lonOffset_rad, lat_rad - latOffset_rad, 0));

		attackMission->SetArea(patrolArea);
		
		// use absolute coordinates for attack missions
		//attackMission->SetPatrolAnchor(flightport->parent->mzUnit.c_str(), tcAttackMission::HEADING_ANCHOR);
		//attackMission->TransformToRelativePatrolArea();

		attackMission->SetWaveQuantity(4);
		attackMission->SetAutoAdd(true);
		attackMission->SetTargetType(targetType);

		tcDateTime launchTime = mpSimState->GetDateTime();
		launchTime.AdjustTimeHours(0.25);
		attackMission->SetLaunchTime(launchTime);

		ai::Route* route = attackMission->GetRoute();

		// staging point near launching platform
		float bearing_rad = flightport->parent->mcKin.HeadingToGeoRad(lon_rad, lat_rad);
		GeoPoint p(flightport->parent->mcKin.mfLon_rad, flightport->parent->mcKin.mfLat_rad, 2000.0f);
		p.Offset(10.0f, flightport->parent->mcKin.mfHeading_rad + 45.0*C_PIOVER180);

		route->AddWaypoint(p.mfLon_rad, p.mfLat_rad, p.mfAlt_m, 0);

		p.Offset(5.0f, flightport->parent->mcKin.mfHeading_rad + 0.0*C_PIOVER180);
		route->AddWaypoint(p.mfLon_rad, p.mfLat_rad, p.mfAlt_m, 0);

		route->AddWaypoint(lon_rad, lat_rad, 3000.0f, 300.0f);

		route->AddWaypointTask(0, "EngageAll");
		route->AddWaypointTask(0, "WaitForGroup");

		route->AddWaypointTask(1, "EnterFormation");

		route->AddWaypointTask(2, "EngageAll");
		route->AddWaypointTask(2, "RadarOn");
		route->AddWaypointTask(2, "AirPatrolArea");
	

		missionManager->AddMission(attackMission);

        tcMapMissionObject* missionObj = new tcMapMissionObject(flightport->parent->mnID, attackMission->GetId());
        missionObj->SetInteractive(true);

        overlay->AddMapObject(missionObj);

	}


	void tcFlightPortInterface::AddCAPMission(float lon_rad, float lat_rad)
	{
		if (flightport == 0) return;

        ai::tcMissionManager* missionManager = flightport->GetOrCreateMissionManager();
		
  //      ai::tcCAPMission* cap = new ai::tcCAPMission();
		//cap->SetStation(lon_rad, lat_rad);

		//missionManager->AddMission(cap);
  //      cap->SetStation(lon_rad, lat_rad); // offset params dont get calculated until missionManager is bound (problem in mission edit mode, don't see cap appear)

		
		ai::tcAttackMission* cap = new ai::tcAttackMission();
		std::vector<GeoPoint> patrolArea;
		float lonOffset_rad = (1/cosf(lat_rad)) * C_MTORAD * 15e3f;
		float latOffset_rad =  C_MTORAD * 15e3f;
		patrolArea.push_back(GeoPoint(lon_rad - lonOffset_rad, lat_rad + latOffset_rad, 0));
		patrolArea.push_back(GeoPoint(lon_rad + lonOffset_rad, lat_rad + latOffset_rad, 0));
		patrolArea.push_back(GeoPoint(lon_rad + lonOffset_rad, lat_rad - latOffset_rad, 0));
		patrolArea.push_back(GeoPoint(lon_rad - lonOffset_rad, lat_rad - latOffset_rad, 0));

		cap->SetArea(patrolArea);
		cap->SetPatrolAnchor(flightport->parent->mzUnit.c_str(), tcAttackMission::HEADING_ANCHOR);
		cap->TransformToRelativePatrolArea();

		cap->SetWaveQuantity(2);
		cap->SetAutoAdd(true);
		cap->SetTargetType(AIR_TARGET);

		tcDateTime launchTime = mpSimState->GetDateTime();
		launchTime.AdjustTimeHours(0.25);
		cap->SetLaunchTime(launchTime);
		cap->SetRepeatIntervalHours(1.0);

		ai::Route* route = cap->GetRoute();

		// staging point near launching platform
		float bearing_rad = flightport->parent->mcKin.HeadingToGeoRad(lon_rad, lat_rad);
		GeoPoint p(flightport->parent->mcKin.mfLon_rad, flightport->parent->mcKin.mfLat_rad, 2000.0f);
		p.Offset(10.0f, flightport->parent->mcKin.mfHeading_rad + 45.0*C_PIOVER180);

		route->AddWaypoint(p.mfLon_rad, p.mfLat_rad, p.mfAlt_m, 0);
		route->AddWaypoint(lon_rad, lat_rad, 3000.0f, 300.0f);

		route->AddWaypointTask(0, "EngageAll");
		route->AddWaypointTask(1, "EngageAll");
		route->AddWaypointTask(1, "AirPatrolArea");
	

		missionManager->AddMission(cap);

        tcMapMissionObject* missionObj = new tcMapMissionObject(flightport->parent->mnID, cap->GetId());
        missionObj->SetInteractive(true);

        overlay->AddMapObject(missionObj);
    }

    void tcFlightPortInterface::AddAEWMission(float lon_rad, float lat_rad)
    {
        if (flightport == 0) return;

        ai::tcMissionManager* missionManager = flightport->GetOrCreateMissionManager();

        ai::tcAttackMission* aew = new ai::tcAttackMission();
        std::vector<GeoPoint> patrolArea;
        float lonOffset_rad = (1/cosf(lat_rad)) * C_MTORAD * 15e3f;
        float latOffset_rad =  C_MTORAD * 15e3f;
        patrolArea.push_back(GeoPoint(lon_rad - lonOffset_rad, lat_rad + latOffset_rad, 0));
        patrolArea.push_back(GeoPoint(lon_rad + lonOffset_rad, lat_rad + latOffset_rad, 0));
        patrolArea.push_back(GeoPoint(lon_rad + lonOffset_rad, lat_rad - latOffset_rad, 0));
        patrolArea.push_back(GeoPoint(lon_rad - lonOffset_rad, lat_rad - latOffset_rad, 0));

        aew->SetArea(patrolArea);
        aew->SetPatrolAnchor(flightport->parent->mzUnit.c_str(), tcAttackMission::HEADING_ANCHOR);
        aew->TransformToRelativePatrolArea();

        aew->SetWaveQuantity(1);
        aew->SetAutoAdd(true);
        aew->SetTargetType(AEW_TARGET);

        tcDateTime launchTime = mpSimState->GetDateTime();
        launchTime.AdjustTimeHours(0.25);
        aew->SetLaunchTime(launchTime);
        aew->SetRepeatIntervalHours(1.0);

        ai::Route* route = aew->GetRoute();

        // staging point near launching platform
        float bearing_rad = flightport->parent->mcKin.HeadingToGeoRad(lon_rad, lat_rad);
        GeoPoint p(flightport->parent->mcKin.mfLon_rad, flightport->parent->mcKin.mfLat_rad, 2000.0f);
        p.Offset(10.0f, flightport->parent->mcKin.mfHeading_rad + 45.0*C_PIOVER180);

        route->AddWaypoint(p.mfLon_rad, p.mfLat_rad, p.mfAlt_m, 0);
        route->AddWaypoint(lon_rad, lat_rad, 3000.0f, 300.0f);

        route->AddWaypointTask(0, "EngageAll");
        route->AddWaypointTask(1, "EngageAll");
        route->AddWaypointTask(1, "AirPatrolArea");
        route->AddWaypointTask(1, "RadarOn");


        missionManager->AddMission(aew);

        tcMapMissionObject* missionObj = new tcMapMissionObject(flightport->parent->mnID, aew->GetId());
        missionObj->SetInteractive(true);

        overlay->AddMapObject(missionObj);
    }

    void tcFlightPortInterface::AddASWMission(float lon_rad, float lat_rad)
    {
        if (flightport == 0) return;

        ai::tcMissionManager* missionManager = flightport->GetOrCreateMissionManager();

        ai::tcAttackMission* aswPatrol = new ai::tcAttackMission();
        std::vector<GeoPoint> patrolArea;
        float lonOffset_rad = (1/cosf(lat_rad)) * C_MTORAD * 15e3f;
        float latOffset_rad =  C_MTORAD * 15e3f;
        patrolArea.push_back(GeoPoint(lon_rad - lonOffset_rad, lat_rad + latOffset_rad, 0));
        patrolArea.push_back(GeoPoint(lon_rad + lonOffset_rad, lat_rad + latOffset_rad, 0));
        patrolArea.push_back(GeoPoint(lon_rad + lonOffset_rad, lat_rad - latOffset_rad, 0));
        patrolArea.push_back(GeoPoint(lon_rad - lonOffset_rad, lat_rad - latOffset_rad, 0));

        aswPatrol->SetArea(patrolArea);
        aswPatrol->SetPatrolAnchor(flightport->parent->mzUnit.c_str(), tcAttackMission::HEADING_ANCHOR);
        aswPatrol->TransformToRelativePatrolArea();

        aswPatrol->SetWaveQuantity(1);
        aswPatrol->SetAutoAdd(true);
        aswPatrol->SetTargetType(SUBSURFACE_TARGET);

        tcDateTime launchTime = mpSimState->GetDateTime();
        launchTime.AdjustTimeHours(0.25);
        aswPatrol->SetLaunchTime(launchTime);
        aswPatrol->SetRepeatIntervalHours(1.0);

        ai::Route* route = aswPatrol->GetRoute();

        // staging point near launching platform
        float bearing_rad = flightport->parent->mcKin.HeadingToGeoRad(lon_rad, lat_rad);
        GeoPoint p(flightport->parent->mcKin.mfLon_rad, flightport->parent->mcKin.mfLat_rad, 2000.0f);
        p.Offset(10.0f, flightport->parent->mcKin.mfHeading_rad + 45.0*C_PIOVER180);

        route->AddWaypoint(p.mfLon_rad, p.mfLat_rad, p.mfAlt_m, 0);
        route->AddWaypoint(lon_rad, lat_rad, 3000.0f, 300.0f);

        route->AddWaypointTask(0, "EngageAll");
        route->AddWaypointTask(1, "EngageAll");
        route->AddWaypointTask(1, "ASWPatrolArea");


        missionManager->AddMission(aswPatrol);

        tcMapMissionObject* missionObj = new tcMapMissionObject(flightport->parent->mnID, aswPatrol->GetId());
        missionObj->SetInteractive(true);

        overlay->AddMapObject(missionObj);
    }

    unsigned int tcFlightPortInterface::GetMissionCount() const
    {
        if (flightport == 0) return 0;

        ai::tcMissionManager* missionManager = flightport->GetOrCreateMissionManager();

        return (unsigned int)missionManager->GetMissionCount();
    }

    unsigned int tcFlightPortInterface::GetMissionId(unsigned int idx) const
    {
        if (flightport == 0) return 0;
        ai::tcMissionManager* missionManager = flightport->GetOrCreateMissionManager();

        ai::tcMission* mission = missionManager->GetMissionByIdx(idx);
        if (mission != 0) return mission->GetId();
        else return 0;
    }

    unsigned int tcFlightPortInterface::GetEditMissionId() const
    {
        if (flightport == 0) return 0;
        ai::tcMissionManager* missionManager = flightport->GetOrCreateMissionManager();

        return missionManager->GetEditMissionId();
    }

    void tcFlightPortInterface::SetEditMissionId(unsigned int id)
    {
        if (flightport == 0) return;
        ai::tcMissionManager* missionManager = flightport->GetOrCreateMissionManager();

        missionManager->SetEditMissionId(id);
    }

    void tcFlightPortInterface::AddMissionWaypoint(unsigned int missionId, float lon_rad, float lat_rad)
    {
        if (flightport == 0) return;
        ai::tcMissionManager* missionManager = flightport->GetOrCreateMissionManager();

        ai::tcMission* mission = missionManager->GetMission(missionId);
        if (mission != 0)
        {
            mission->GetRoute()->AddWaypoint(lon_rad, lat_rad, 0, 0);
        }
    }

    void tcFlightPortInterface::AddMissionWaypointAdvanced(unsigned int missionId, 
            float lon_rad, float lat_rad, float alt_m, float speed_kts)
    {
        if (flightport == 0) return;
        ai::tcMissionManager* missionManager = flightport->GetOrCreateMissionManager();

        ai::tcMission* mission = missionManager->GetMission(missionId);
        if (mission != 0)
        {
            mission->GetRoute()->AddWaypoint(lon_rad, lat_rad, alt_m, speed_kts);
        }
    }

    unsigned int tcFlightPortInterface::GetMissionWaypointCount(unsigned int missionId)
    {
        if (const ai::Route* route = GetMissionRoute(missionId))
        {
            return (unsigned int)route->GetWaypointCount();
        }
        else
        {
            return 0;
        }
    }

    void tcFlightPortInterface::EditMissionWaypoint(unsigned int missionId, unsigned int idx, float lon_rad, float lat_rad)
    {
        EditMissionWaypointAdvanced(missionId, idx, lon_rad, lat_rad, 0, 0);
    }

    void tcFlightPortInterface::EditMissionWaypointAdvanced(unsigned int missionId, unsigned int idx, 
        float lon_rad, float lat_rad, float alt_m, float speed_kts)
    {
        if (ai::Route* route = GetMissionRoute(missionId))
        {
            route->EditWaypoint(idx, lon_rad, lat_rad, alt_m, speed_kts);
        }
    }

    void tcFlightPortInterface::EditMissionWaypointReference(unsigned int missionId, unsigned int idx, 
                                         unsigned char referenceMode, long referencePlatform)
    {
        if (ai::Route* route = GetMissionRoute(missionId))
        {
            if (referenceMode != 0)
            {
                ai::tcMissionManager* missionManager = flightport->GetOrCreateMissionManager();
                tcGameObject* host = missionManager->GetFlightportParent();
                tcGameObject* ref = mpSimState->GetObject(referencePlatform);
                if ((host == 0) || (ref == 0) || (host->GetAlliance() != ref->GetAlliance()))
                {
                    return; // invalid waypoint referencing
                }
            }

            route->EditWaypointReference(idx, referenceMode, referencePlatform);
        }
    }

    /**
    * Clear all mission waypoints
    */
    void tcFlightPortInterface::ClearMissionWaypoints(unsigned int missionId)
    {
        if (ai::Route* route = GetMissionRoute(missionId))
        {
            route->ClearWaypoints();
        }
    }

    void tcFlightPortInterface::DeleteMissionWaypoint(unsigned int missionId, unsigned int idx)
    {
        if (ai::Route* route = GetMissionRoute(missionId))
        {
            route->DeleteWaypoint(idx);
        }
    }

    void tcFlightPortInterface::InsertMissionWaypoint(unsigned int missionId, unsigned int idx, float lon_rad, float lat_rad)
    {
        if (ai::Route* route = GetMissionRoute(missionId))
        {
            route->InsertWaypoint(idx, lon_rad, lat_rad, 0, 0);
        }
    }

    /**
    * Helper method, not intended to be exposed
    */
    ai::Route* tcFlightPortInterface::GetMissionRoute(unsigned int missionId)
    {
        if (flightport == 0) return 0;
        ai::tcMissionManager* missionManager = flightport->GetOrCreateMissionManager();

        ai::tcMission* mission = missionManager->GetMission(missionId);
        if (mission == 0) return 0;
        
        return mission->GetRoute();
    }

    /**
    * Helper method, not intended to be exposed
    */
    ai::tcAttackMission* tcFlightPortInterface::GetAttackMission(unsigned int missionId)
    {
        if (flightport == 0) return 0;
        ai::tcMissionManager* missionManager = flightport->GetOrCreateMissionManager();

        ai::tcAttackMission* mission = dynamic_cast<ai::tcAttackMission*>(missionManager->GetMission(missionId));
        return mission;
    }

    void tcFlightPortInterface::SetMissionWaypointTasks(unsigned int missionId, size_t idx, const std::string& taskList)
    {
        if (ai::Route* route = GetMissionRoute(missionId))
        {
            route->SetWaypointTasklist(idx, taskList);
        }
    }

    void tcFlightPortInterface::AddMissionWaypointTask(unsigned int missionId, size_t idx, const std::string& task)
    {
        if (ai::Route* route = GetMissionRoute(missionId))
        {
            route->AddWaypointTask(idx, task);
        }
    }

    void tcFlightPortInterface::RemoveMissionWaypointTask(unsigned int missionId, size_t idx, const std::string& task)
    {
        if (ai::Route* route = GetMissionRoute(missionId))
        {
            route->RemoveWaypointTask(idx, task);
        }
    }

    void tcFlightPortInterface::SetMissionLaunchTime(unsigned int missionId, const std::string& timeString)
    {
        ai::tcAttackMission* mission = GetAttackMission(missionId);
        if (mission != 0)
        {
            mission->SetLaunchTimeFromString(timeString.c_str());
        }
    }

    void tcFlightPortInterface::SetMissionDatum(unsigned int missionId, float lon_rad, float lat_rad)
    {
        ai::tcAttackMission* mission = GetAttackMission(missionId);
        if (mission != 0)
        {
            mission->SetTargetDatum(lon_rad, lat_rad);
        }
    }

    void tcFlightPortInterface::SetMissionLandingTarget(unsigned int missionId, const std::string& baseName)
    {
        ai::tcAttackMission* mission = GetAttackMission(missionId);
        if (mission != 0)
        {
            mission->SetLandingTarget(baseName);
        }
    }

    void tcFlightPortInterface::SetMissionPatrolArea(unsigned int missionId, const std::string& areaString)
    {
        ai::tcAttackMission* mission = GetAttackMission(missionId);
        if (mission != 0)
        {
            mission->SetAreaByString(areaString);
        }
    }

    const char* tcFlightPortInterface::GetMissionPatrolArea(unsigned int missionId)
    {
        static std::string areaStringError = "";

        ai::tcAttackMission* mission = GetAttackMission(missionId);
        if (mission != 0)
        {
            return mission->GetAreaString();
        }
        else
        {
            return areaStringError.c_str();
        }

    }

    void tcFlightPortInterface::SetMissionPatrolAnchor(unsigned int missionId, const std::string& anchorUnit, int anchorMode)
    {
        ai::tcAttackMission* mission = GetAttackMission(missionId);
        if (mission != 0)
        {
            mission->SetPatrolAnchor(anchorUnit, anchorMode);
        }
    }

    void tcFlightPortInterface::SetMissionType(unsigned int missionId, const std::string& missionType)
    {
        ai::tcAttackMission* mission = GetAttackMission(missionId);
        if (mission != 0)
        {
            mission->SetMissionType(missionType);
        }
    }

    const char* tcFlightPortInterface::GetMissionType(unsigned int missionId)
    {
        static std::string error("");
        ai::tcAttackMission* mission = GetAttackMission(missionId);
        if (mission != 0)
        {
            return mission->GetMissionType();
        }
        else
        {
            return error.c_str();
        }
    }

    void tcFlightPortInterface::SetMissionWaveQuantity(unsigned int missionId, unsigned int quantity)
    {
        ai::tcAttackMission* mission = GetAttackMission(missionId);
        if (mission != 0)
        {
            mission->SetWaveQuantity(quantity); 
        }
    }

    /**
    * Hack so that absolute lat/lon can be entered in script and then later be transformed to relative
    * coordinates
    */
    void tcFlightPortInterface::TransformToRelativePatrolArea(unsigned int missionId)
    {
        ai::tcAttackMission* mission = GetAttackMission(missionId);
        if (mission != 0)
        {
            mission->TransformToRelativePatrolArea();
        }
    }

    /**
    * Hack so that relative coordinates can be temporarily transformed to absolute in script
    */
    void tcFlightPortInterface::TransformToAbsolutePatrolArea(unsigned int missionId)
    {
        ai::tcAttackMission* mission = GetAttackMission(missionId);
        if (mission != 0)
        {
            mission->TransformToAbsolutePatrolArea();
        }
    }



    // Interface function declaration
    double tcFlightPortInterface::GetTime()
    {
        if (flightport==0) return 1e32;
        return flightport->last_update_time;
    }

    int tcFlightPortInterface::GetUnitCount()
    {
        if (flightport==0) return 0;
        return (int)flightport->units.size();
    }

    long tcFlightPortInterface::GetUnitID(int n)
    {
        if (flightport==0) return -1;
        if ((n<=0)||(n>=(int)flightport->units.size())) return -1;
        tcAirState* airstate = flightport->units.at(n);
        return airstate->obj->mnID;
    }

    std::string tcFlightPortInterface::GetUnitName(int n)
    {
        if (flightport==0) return "err";
        if ((n<0)||(n>=(int)flightport->units.size())) return "err";
        tcAirState* airstate = flightport->units.at(n);
        return airstate->obj->mzClass.c_str();
    }

    std::string tcFlightPortInterface::GetUnitLocation(int n)
    {
        if (flightport==0) return "err";
        if ((n<0)||(n>=(int)flightport->units.size())) return "err";
        tcAirState* airstate = flightport->units.at(n);
        std::string s = airstate->LocationToString(airstate->current_location);
        if (airstate->current_location == ALERT5)
        {
            sprintf(buff,"-%d",airstate->current_spot);       
            s += buff;
        }
        return s;
    }

    std::string tcFlightPortInterface::GetUnitGoalLocation(int n)
    {
        if (flightport==0) return "err";
        if ((n<0)||(n>=(int)flightport->units.size())) return "err";
        tcAirState* airstate = flightport->units.at(n);
        std::string s = airstate->LocationToString(airstate->goal_location);
        return s;
    }

    tcFlightUnitStatus tcFlightPortInterface::GetUnitStatus(int n)
    {
        tcFlightUnitStatus status;

        status.runway = -1;

        if (flightport==0) return status;
        if ((n<0)||(n>=(int)flightport->units.size())) return status;
        tcAirState* airstate = flightport->units.at(n);
        status.unit_name = airstate->obj->mzClass.c_str();

        status.current_loc = airstate->LocationToString(airstate->current_location);
        if (airstate->current_location == ALERT5)
        {
            status.runway = airstate->current_spot;
            sprintf(buff,"-%d",airstate->current_spot);       
            status.current_loc += buff;
        }
        status.goal_loc = airstate->LocationToString(airstate->goal_location);
        status.atDestination = airstate->current_location == airstate->goal_location;
        status.isIdle = airstate->op == OP_NONE;
        status.ready_time = airstate->ready_time;
        return status;
    }

	tcPlatformInterface tcFlightPortInterface::GetUnitPlatformInterface(int n)
	{
		if ((n<0)||(n>=(int)flightport->units.size())) return tcPlatformInterface(0);

		tcAirState* airstate = flightport->units[n];
		wxASSERT(airstate != 0);
		tcPlatformObject *obj = dynamic_cast<tcPlatformObject*>(airstate->obj);
		return tcPlatformInterface(obj);
	}

    bool tcFlightPortInterface::HasAircraftForMission(const std::string& missionType)
    {
        int targetFlags = 0;
        if (missionType == "cap")
        {
            targetFlags = AIR_TARGET;
        }
        else if (missionType == "aew")
        {
            targetFlags = AEW_TARGET;
        }
        else if (missionType == "strike")
        {
            targetFlags = SURFACE_TARGET | LAND_TARGET;
        }
        else if (missionType == "asw")
        {
            targetFlags = SUBSURFACE_TARGET;
        }
        else
        {
            return false;
        }

        ai::tcMissionManager* missionManager = flightport->GetOrCreateMissionManager();
        size_t nAircraft = flightport->GetCount();
        const bool subsurfaceTarget = (targetFlags == SUBSURFACE_TARGET);
        const bool aewPatrol = (targetFlags == AEW_TARGET);
        for (size_t n=0; n<nAircraft; n++)
        {
            tcAirState* airState = flightport->GetAirState((unsigned int)n);

            long id = airState->obj->mnID;
            if (!missionManager->IsAircraftReserved(id))
            {
                tcPlatformObject* platform = dynamic_cast<tcPlatformObject*>(airState->obj);
                wxASSERT(platform != 0);
                bool isHelo = dynamic_cast<tcHeloObject*>(platform) != 0;
                if ((platform != 0) && (!isHelo || subsurfaceTarget || aewPatrol) && (platform->IsCapableVsTargetType(targetFlags)) &&
                    (platform->GetDamageLevel() <= 0))
                {
                    return true;
                }
            }
        }
        return false;
    }

    bool tcFlightPortInterface::IsValid()
    {
        return (flightport != 0);
    }

    void tcFlightPortInterface::Launch(int runway)
    {
        if (flightport==0) return;
        flightport->LaunchRunway(runway);
    }

    void tcFlightPortInterface::LaunchID(long id)
    {
        if (flightport==0) return;
        flightport->LaunchID(id);
    }

    /** 
     * n is unit index to move
     * dest_code is used to specify destination
     *      0 - hangar, 1 - ready, 2 - runway, other - runway
     */
    void tcFlightPortInterface::SetDestination(int n, int dest_code)
    {
        if (flightport==0) return;

        teLocation dest;
        if (dest_code==0) dest = HANGAR;
        else if (dest_code==1) dest = ALERT15;
        else dest = ALERT5;
        flightport->SetObjectDestination(n, dest);
    }

    tcFlightPortInterface::tcFlightPortInterface()
    : flightport(0)
    {
    }
    
    tcFlightPortInterface::~tcFlightPortInterface()
    {
    }


}


