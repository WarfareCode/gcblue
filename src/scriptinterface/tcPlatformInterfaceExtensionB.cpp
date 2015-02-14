/**  
**  @file tcPlatformInterfaceExtensionB.cpp
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
#endif // WIN32
#endif // WX_PRECOMP

#include <string>
#include "tcSimState.h"
#include "simmath.h"
#include "tcPlatformInterface.h"
#include "tcSoundConsole.h"
#include "ai/BlackboardInterface.h"
#include "tcFlightPortInterface.h"
#include "tcMissionInterface.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif 

using namespace boost::python;
using namespace ai;
using ai::BlackboardInterface;

namespace scriptinterface {

    object tcPlatformInterface::InitPythonPlatformInterface() 
    {
        return class_<tcPlatformInterface>("UnitInfoClass")
            // navigation related commands
            .def("GetLongitude", &tcPlatformInterface::GetLongitude)
            .def("GetLatitude", &tcPlatformInterface::GetLatitude)
            .def("GetAlt", &tcPlatformInterface::GetAltitude)
            .def("GetAltitude", &tcPlatformInterface::GetAltitude)
            .def("GetFuel", &tcPlatformInterface::GetFuel)
            .def("GetMaxAlt", &tcPlatformInterface::GetMaxAltitude)
            .def("GetMaxAltitude", &tcPlatformInterface::GetMaxAltitude)
            .def("GetSpeed",&tcPlatformInterface::GetSpeed)
            .def("GetCruiseAltitude", &tcPlatformInterface::GetCruiseAltitude)
            .def("GetCruiseSpeedForAltitude", &tcPlatformInterface::GetCruiseSpeedForAltitude)
            .def("GetCruiseRangeForAltitude", &tcPlatformInterface::GetCruiseRangeForAltitude)
			.def("GetStallSpeedForAltitude", &tcPlatformInterface::GetStallSpeedForAltitude)
            .def("GetMaxSpeed",&tcPlatformInterface::GetMaxSpeed)
            .def("GetMaxSpeedForAltitude",&tcPlatformInterface::GetMaxSpeedForAltitude)
            .def("GetMaxSpeedForAltitudeAB",&tcPlatformInterface::GetMaxSpeedForAltitudeAB)
            .def("GetThrottle", &tcPlatformInterface::GetThrottle)
            .def("GetHeading",&tcPlatformInterface::GetHeading)
            .def("GetHeadingRad",&tcPlatformInterface::GetHeadingRad)
            .def("GetHeadingToDatum",&tcPlatformInterface::GetHeadingToDatum)
            .def("GetRangeToDatum",&tcPlatformInterface::GetRangeToDatum)
            .def("GetTerrainElevation",&tcPlatformInterface::GetTerrainElevation)
			.def("GetMapTerrainElevation",&tcPlatformInterface::GetMapTerrainElevation)
            .def("HasThrottle",&tcPlatformInterface::HasThrottle)
            .def("SetAlt", &tcPlatformInterface::SetAltitude)
            .def("SetAltitude", &tcPlatformInterface::SetAltitude)
            .def("SetPitchLimit", &tcPlatformInterface::SetPitchLimitDeg)
            .def("SetClimbDeg", &tcPlatformInterface::SetClimbDeg)
            .def("GetClimbDeg", &tcPlatformInterface::GetClimbDeg)
            .def("SetClimbRad", &tcPlatformInterface::SetClimbRad)
            .def("CalculateBombElevationDeg", &tcPlatformInterface::CalculateBombElevationDeg)
			.def("EstimateMissileRangeKm", &tcPlatformInterface::EstimateMissileRangeKm)
            .def("SetMaxTurnRate", &tcPlatformInterface::SetMaxTurnRate)
            .def("SetSpeed", &tcPlatformInterface::SetSpeed)
            .def("SetSpeedToMax", &tcPlatformInterface::SetSpeedToMax)
            .def("SetThrottle",&tcPlatformInterface::SetThrottle)
            .def("SetHeading", &tcPlatformInterface::SetHeading)
            .def("SetHeadingRad", &tcPlatformInterface::SetHeadingRad)

            // formation
            .def("SetFormationLeader", &tcPlatformInterface::SetFormationLeader)
            .def("IsInFormation", &tcPlatformInterface::IsInFormation)
            .def("IsFormationLeader", &tcPlatformInterface::IsFormationLeader)
            .def("SetFormationEdit", &tcPlatformInterface::SetFormationEdit)
            .def("GetFormationLeader", &tcPlatformInterface::GetFormationLeader)
            .def("GetFormationEditId", &tcPlatformInterface::GetFormationEditId)
            .def("SetFormationPosition", &tcPlatformInterface::SetFormationPosition)
			.def("GetFormationPosition", &tcPlatformInterface::GetFormationPosition)
            .def("SetFormationAltitudeOffset", &tcPlatformInterface::SetFormationAltitudeOffset)
			.def("GetFormationAltitudeOffset", &tcPlatformInterface::GetFormationAltitudeOffset)
            .def("SetFormationMode", &tcPlatformInterface::SetFormationMode)
            .def("GetFormationMode", &tcPlatformInterface::GetFormationMode)
            .def("SetFormationUseNorthBearing", &tcPlatformInterface::SetFormationUseNorthBearing)
			.def("IsFormationUsingNorthBearing", &tcPlatformInterface::IsFormationUsingNorthBearing)

            // platform information
            .def("GetName", &tcPlatformInterface::GetPlatformName)
            .def("GetPlatformName", &tcPlatformInterface::GetPlatformName)
            .def("GetClass", &tcPlatformInterface::GetPlatformClass)
            .def("GetPlatformClass", &tcPlatformInterface::GetPlatformClass)
            .def("GetPlatformId", &tcPlatformInterface::GetPlatformId)
            .def("GetPlatformAlliance", &tcPlatformInterface::GetPlatformAlliance)
            .def("IsSurface", &tcPlatformInterface::IsSurface)
            .def("IsAir", &tcPlatformInterface::IsAir)
			.def("IsFixed", &tcPlatformInterface::IsFixed)
            .def("IsGroundVehicle", &tcPlatformInterface::IsGroundVehicle)
			.def("IsHelo", &tcPlatformInterface::IsHelo)
            .def("IsSub", &tcPlatformInterface::IsSub)
            .def("SetActionText", &tcPlatformInterface::SetActionText)
            .def("GetSubInterface", &tcPlatformInterface::GetSubInterface)

            // weapons and targeting
            .def("GetTarget",&tcPlatformInterface::GetTarget)
            .def("SetTarget",&tcPlatformInterface::SetTarget)
            .def("GetRangeToTarget",&tcPlatformInterface::GetRangeToTarget)
            .def("SetHeadingToInterceptTarget",&tcPlatformInterface::SetHeadingToInterceptTarget)
            .def("GetTargetTrackInfo",&tcPlatformInterface::GetTargetTrackInfo)
            .def("GetLauncherCount",&tcPlatformInterface::GetLauncherCount)
            .def("GetLauncherWeaponName",&tcPlatformInterface::GetLauncherWeaponName)
            .def("GetBestLauncher",&tcPlatformInterface::GetBestLauncher)
            .def("GetLauncherInfo", &tcPlatformInterface::GetLauncherInfoByValue)
            .def("GetLauncherStatus", &tcPlatformInterface::GetLauncherStatus)
            .def("IsTargetInRange", &tcPlatformInterface::IsTargetInRange)
            .def("SendDatumToLauncher", &tcPlatformInterface::SendDatumToLauncher)
            .def("HandoffTargetToLauncher", &tcPlatformInterface::HandoffTargetToLauncher)
            .def("SendTargetToLauncher", &tcPlatformInterface::SendTargetToLauncher)
            .def("IsLauncherEffective", &tcPlatformInterface::IsLauncherEffective)
			.def("IsEquippedForTargetType", &tcPlatformInterface::IsEquippedForTargetType)
            .def("Launch", &tcPlatformInterface::Launch)
            .def("GetLauncherQuantity", &tcPlatformInterface::GetLauncherQuantity)
            .def("IsDatumLaunch", &tcPlatformInterface::IsDatumLaunch)
			.def("GetLauncherInterceptTime", &tcPlatformInterface::GetLauncherInterceptTime)
            .def("GetFireControlInfo", &tcPlatformInterface::GetFireControlInfo)

            .def("GetLauncherTypesCount", &tcPlatformInterface::GetLauncherTypesCount)
            .def("GetLauncherTypeName", &tcPlatformInterface::GetLauncherTypeName)
            .def("CanMagazineAcceptItem", &tcPlatformInterface::CanMagazineAcceptItem)
            .def("GetMagazineQuantity", &tcPlatformInterface::GetMagazineQuantity)
            .def("GetMagazineIdQuantity", &tcPlatformInterface::GetMagazineIdQuantity)
            .def("HasMagazine", &tcPlatformInterface::HasMagazine)
            .def("GetMagazineItems", &tcPlatformInterface::GetMagazineItems)
            .def("SetMagazineEmpty", &tcPlatformInterface::SetMagazineEmpty)
            .def("AddItemToMagazine", &tcPlatformInterface::AddItemToMagazine)
            .def("GetCompatibleItemList", &tcPlatformInterface::GetCompatibleItemList)
            .def("LoadLauncher", &tcPlatformInterface::LoadLauncher)
			.def("GetItemCapacityForLauncher", &tcPlatformInterface::GetItemCapacityForLauncher)
            .def("LoadLauncherTest", &tcPlatformInterface::LoadLauncherTest)
            .def("UnloadLauncher", &tcPlatformInterface::UnloadLauncher)
			.def("LoadOther", &tcPlatformInterface::LoadOther)
            .def("MaintenanceHold", &tcPlatformInterface::MaintenanceHold)
            .def("GetEquipmentListByClass", &tcPlatformInterface::GetEquipmentListByClass)
            .def("GetLoadoutList", &tcPlatformInterface::GetLoadoutList)
            .def("EquipLoadout", &tcPlatformInterface::EquipLoadout)
            .def("GetPlatformSetups", &tcPlatformInterface::GetPlatformSetups)
            .def("AutoConfigurePlatform", &tcPlatformInterface::AutoConfigurePlatform)
			.def("IsRefueling", &tcPlatformInterface::IsRefueling)
            .def("GetWeightMargin", &tcPlatformInterface::GetWeightMargin)
            .def("CanRefuelInFlight", &tcPlatformInterface::CanRefuelInFlight)
            .def("StartRefuelWith", &tcPlatformInterface::StartRefuelWith)
            .def("IsTankerAircraft", &tcPlatformInterface::IsTankerAircraft)
            .def("GetTankerSpotsFree", &tcPlatformInterface::GetTankerSpotsFree)

            // task interface commands
            .def("AddNavWaypoint", &tcPlatformInterface::AddNavWaypoint)
            .def("AddNavWaypointAdvanced", &tcPlatformInterface::AddNavWaypointAdvanced)
			.def("EditNavWaypoint", &tcPlatformInterface::EditNavWaypoint)
            .def("EditNavWaypointAdvanced", &tcPlatformInterface::EditNavWaypointAdvanced)
            .def("EditNavWaypointReference", &tcPlatformInterface::EditNavWaypointReference)
            .def("InsertNavWaypoint", &tcPlatformInterface::InsertNavWaypoint)
            .def("DeleteNavWaypoint", &tcPlatformInterface::DeleteNavWaypoint)
			.def("GetCurrentWaypoint", &tcPlatformInterface::GetCurrentWaypoint)
            .def("SetCurrentWaypoint", &tcPlatformInterface::SetCurrentWaypoint)
			.def("SetNavLoopState", &tcPlatformInterface::SetNavLoopState)
            .def("GetNavLoopState", &tcPlatformInterface::GetNavLoopState)
            .def("SetNavWaypointTasks", &tcPlatformInterface::SetNavWaypointTasks)
            .def("AddWaypointTask", &tcPlatformInterface::AddWaypointTask)
            .def("RemoveWaypointTask", &tcPlatformInterface::RemoveWaypointTask)
            .def("GetMissionInfo", &tcPlatformInterface::GetMissionInfo)
            .def("GetRandomPatrolPoint", &tcPlatformInterface::GetRandomPatrolPoint)

            .def("AddTask", &tcPlatformInterface::AddTask)
            .def("ClearTasks", &tcPlatformInterface::ClearTasks)
            .def("DeleteTask", &tcPlatformInterface::DeleteTask)
            .def("SetTaskRun", &tcPlatformInterface::SetTaskRun)
            .def("GetBlackboardInterface", &tcPlatformInterface::GetBlackboardInterface)
            .def("TaskExists", &tcPlatformInterface::TaskExists)
            .def("GetTaskList", &tcPlatformInterface::GetTaskList)

            // TODO why is this exposed??
            .def("GetLocalObj",&tcPlatformInterface::GetLocalObj)

            // sensors
            .def("GetFirstTrack",&tcPlatformInterface::GetFirstTrack)
            .def("GetClosestAirTrack",&tcPlatformInterface::GetClosestAirTrack)
            .def("GetClosestSurfaceTrack",&tcPlatformInterface::GetClosestSurfaceTrack)
            .def("GetClosestMissileTrack",&tcPlatformInterface::GetClosestMissileTrack)
            .def("GetClosestTrack",&tcPlatformInterface::GetClosestTrack)
            .def("SetAllSensorState",&tcPlatformInterface::SetAllSensorState)
            .def("GetSensorCount",&tcPlatformInterface::GetSensorCount)
            .def("GetSensorInfo",&tcPlatformInterface::GetSensorInfo)
            .def("SetSensorState",&tcPlatformInterface::SetSensorState)
            .def("GetInterceptHeadingToTrack",&tcPlatformInterface::GetInterceptHeadingToTrack)
            .def("GetRangeToTrack",&tcPlatformInterface::GetRangeToTrack)
            .def("SetHeadingToInterceptTrack",&tcPlatformInterface::SetHeadingToInterceptTrack)
            .def("GetTrackById",&tcPlatformInterface::GetTrackById)
            .def("GetTrackList",&tcPlatformInterface::GetTrackList)
            .def("GetFriendlyTrackList",&tcPlatformInterface::GetFriendlyTrackList)

            // flightport, landing
            .def("GetLandingState",&tcPlatformInterface::GetLandingState)
            .def("SetLandingState",&tcPlatformInterface::SetLandingState)
            .def("HasFlightPort",&tcPlatformInterface::HasFlightPort)
			.def("GetFlightPortInfo",&tcPlatformInterface::GetFlightPortInfo)
			.def("GetLandingData", &tcPlatformInterface::GetLandingData)
            .def("GetUserInput",&tcPlatformInterface::GetUserInput)
            .def("SendCommand",&tcPlatformInterface::SendCommand)

			// multiplayer related
			.def("GetController", &tcPlatformInterface::GetController)
			.def("IsAvailable", &tcPlatformInterface::IsAvailable)
			.def("IsMultiplayerActive", &tcPlatformInterface::IsMultiplayerActive)
			.def("ReleaseControl", &tcPlatformInterface::ReleaseControl)
			.def("TakeControl", &tcPlatformInterface::TakeControl)
			
            // miscellaneous
            .def("GetTime", &tcPlatformInterface::GetTime)
            .def("LookupFriendlyId", &tcPlatformInterface::LookupFriendlyId)
            .def("LookupFriendlyName", &tcPlatformInterface::LookupFriendlyName)
            .def("DisplayMessage",&tcPlatformInterface::DisplayMessage)
            .def("DisplayPopupMessage", &tcPlatformInterface::DisplayPopupMessage)
            .def("IsPlayerControlled", &tcPlatformInterface::IsPlayerControlled)
            .def("IsValid",&tcPlatformInterface::IsValid)
            .def("PlaySound",&tcPlatformInterface::PlaySound)
            .def("Rand",&tcPlatformInterface::GetRand)
			.def("GetROE", &tcPlatformInterface::GetROE)
			.def("QueryDatabase", &tcPlatformInterface::QueryDatabase)

			// mission editor mode and dev tool mode
			.def("DeletePlatform", &tcPlatformInterface::DeletePlatform)
			.def("MovePlatform", &tcPlatformInterface::MovePlatform)
			.def("RenamePlatform", &tcPlatformInterface::RenamePlatform)
            .def("IsDeveloperMode", &tcPlatformInterface::IsDeveloperMode)
            .def("SetInvulnerable", &tcPlatformInterface::SetInvulnerable)
            .def("LaunchAtMe", &tcPlatformInterface::LaunchAtMe)
            .def("SetTestParameter", &tcPlatformInterface::SetTestParameter)
			.def("ApplyDamage", &tcPlatformInterface::ApplyDamage)
			.def("ApplyAdvancedDamage", &tcPlatformInterface::ApplyAdvancedDamage)
            .def("GetPlatformListByClass", &tcPlatformInterface::GetPlatformListByClass)
            .def("GetPlatformNameList", &tcPlatformInterface::GetPlatformNameList)
            .def("GetUnitInterface", &tcPlatformInterface::GetUnitInterface)
            .def("GetScenarioInterface", &tcPlatformInterface::GetScenarioInterface)
            .def("AddUnitToFlightDeck", &tcPlatformInterface::AddUnitToFlightDeck)
            .def("SetAirGroupName", &tcPlatformInterface::SetAirGroupName)
            .def("GetAirGroupName", &tcPlatformInterface::GetAirGroupName)
            .def("GetAirUnitId", &tcPlatformInterface::GetAirUnitId)
            .def("SetAirGroupCount", &tcPlatformInterface::SetAirGroupCount)
            .def("GetAirGroupCount", &tcPlatformInterface::GetAirGroupCount)
            .def("SetMagazineAddCount", &tcPlatformInterface::SetMagazineAddCount)
            .def("GetMagazineAddCount", &tcPlatformInterface::GetMagazineAddCount)
            .def("SetIncludeProbability", &tcPlatformInterface::SetIncludeProbability)
            .def("GetIncludeProbability", &tcPlatformInterface::GetIncludeProbability)
            .def("AddRandomBox", &tcPlatformInterface::AddRandomBox)
            .def("DeleteAllRandomBoxes", &tcPlatformInterface::DeleteAllRandomBoxes)
            .def("UpdateMissionEditGraphics", &tcPlatformInterface::UpdateMissionEditGraphics)
            .def("SetAlwaysVisible", &tcPlatformInterface::SetAlwaysVisible)
            .def("GetAlwaysVisible", &tcPlatformInterface::GetAlwaysVisible)
            .def("SetFuelTest", &tcPlatformInterface::SetFuelTest)
            .def("GetCost", &tcPlatformInterface::GetCost)
            .def("SetCost", &tcPlatformInterface::SetCost)
            ; 
    }
    /** 
    * Initialization of python classes is broken into multiple
    * files to workaround compiler overflow problem.
    * Multiple calls of this have not been tested. Recommend calling only once.
    * @return python object for PlatformInterface type.
    */
    object tcPlatformInterface::GetPlatformInterface() 
    {
        InitPythonClassesA();
        return InitPythonPlatformInterface();
    }
}

