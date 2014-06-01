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

#ifdef _DEBUG
#define new DEBUG_NEW
#endif 

using namespace boost::python;
using namespace ai;

namespace scriptinterface {

   void tcPlatformInterface::InitPythonClassesA() 
   {
     class_<tcTrack>("tcTrack") 
         .def_readwrite("Alt",&tcTrack::mfAlt_m)
         .def_readwrite("Lat",&tcTrack::mfLat_rad)
         .def_readwrite("Lon",&tcTrack::mfLon_rad)
         .def_readonly("Speed",&tcTrack::mfSpeed_kts)
         .def_readonly("Flags", &tcTrack::mnFlags)
         .def_readonly("Heading_rad",&tcTrack::mfHeading_rad)
		 .def_readonly("Bearing_rad", &tcTrack::bearing_rad)
		 .def_readonly("BearingRate_radps", &tcTrack::bearingRate_radps)
         .def_readonly("Classification",&tcTrack::mnClassification)
         .def_readonly("Affiliation",&tcTrack::mnAffiliation)
         .def_readonly("ID",&tcTrack::mnID)
		 .def_readonly("Time", &tcTrack::mfTimestamp)
         .def("IsAir", &tcTrack::IsAir)
         .def("IsMissile", &tcTrack::IsMissile)
         .def("IsSurface", &tcTrack::IsSurface)
         .def("IsGround", &tcTrack::IsGround)
         .def("IsSub", &tcTrack::IsSub)
         .def("IsTorpedo", &tcTrack::IsTorpedo)
         .def("IsBearingOnly", &tcTrack::IsBearingOnly)
		 .def("IsBearingRateValid", &tcTrack::IsBearingRateValid)
         .def("IsValid", &tcTrack::IsValid)
         .def("Offset", &tcTrack::Offset)
		 .def("PredictAhead", &tcTrack::PredictAhead)
         ;

	 

     class_<tcSensorMapTrack>("tcSMTrack") 
         .def_readwrite("Alt",&tcSensorMapTrack::mfAlt_m)
         .def_readwrite("Lat",&tcSensorMapTrack::mfLat_rad)
         .def_readwrite("Lon",&tcSensorMapTrack::mfLon_rad)
         .def_readonly("Speed",&tcSensorMapTrack::mfSpeed_kts)
         .def_readonly("Flags", &tcSensorMapTrack::mnFlags)
         .def_readonly("Heading_rad",&tcSensorMapTrack::mfHeading_rad)
		 .def_readonly("Bearing_rad", &tcSensorMapTrack::bearing_rad)
		 .def_readonly("BearingRate_radps", &tcSensorMapTrack::bearingRate_radps)
         .def_readonly("Classification",&tcSensorMapTrack::mnClassification)
         .def_readonly("Affiliation",&tcSensorMapTrack::mnAffiliation)
         .def_readonly("ID",&tcSensorMapTrack::mnID)
		 .def_readonly("Time", &tcSensorMapTrack::mfTimestamp)
         .def("IsAir", &tcSensorMapTrack::IsAir)
		 .def("IsDestroyed", &tcSensorMapTrack::IsDestroyed)
         .def("IsMissile", &tcSensorMapTrack::IsMissile)
         .def("IsSurface", &tcSensorMapTrack::IsSurface)
         .def("IsGround", &tcSensorMapTrack::IsGround)
         .def("IsSub", &tcSensorMapTrack::IsSub)
         .def("IsTorpedo", &tcSensorMapTrack::IsTorpedo)
         .def("IsBearingOnly", &tcSensorMapTrack::IsBearingOnly)
		 .def("IsBearingRateValid", &tcSensorMapTrack::IsBearingRateValid)
		 .def("IsStale", &tcSensorMapTrack::IsStale)
         .def("IsValid", &tcSensorMapTrack::IsValid)
         .def("Offset", &tcSensorMapTrack::Offset)
		 .def("PredictAhead", &tcSensorMapTrack::PredictAhead)
         .def("GetEngagedCount", &tcSensorMapTrack::GetEngagedCount)
		 .def("GetEmitterCount", &tcSensorMapTrack::GetEmitterCount)
		 .def("GetEmitterInfo",  &tcSensorMapTrack::GetEmitterInfo)
         .def("TrackErrorKm", &tcSensorMapTrack::TrackErrorKm)
         .def("BearingToRad", &tcSensorMapTrack::BearingToRad)
         .def("RangeToKm", &tcSensorMapTrack::RangeToKm)
		 .def("GetTrackLife", &tcSensorMapTrack::GetTrackLife)
         ;


      class_<tcTrackIterator>("TrackIterator")
         .def_readonly("Alt",&tcTrackIterator::mfAlt_m)
         .def_readonly("Lat",&tcTrackIterator::mfLat_rad)
         .def_readonly("Lon",&tcTrackIterator::mfLon_rad)
         .def_readonly("Speed",&tcTrackIterator::mfSpeed_kts)
         .def_readonly("Heading_rad",&tcTrackIterator::mfHeading_rad)
         .def_readonly("Classification",&tcTrackIterator::mnClassification)
         .def_readonly("Affiliation",&tcTrackIterator::mnAffiliation)
         .def_readonly("ID",&tcTrackIterator::mnID)
         .def_readonly("Key",&tcTrackIterator::mnKey)
         ;

      class_<tcTrackList>("TrackList")
          .def("Size",&tcTrackList::Size)
          .def("GetTrack",&tcTrackList::GetTrack)
          ;

      class_<GeoPoint>("GeoPoint")
         .def_readonly("Alt",&GeoPoint::mfAlt_m)
         .def_readonly("Lon",&GeoPoint::mfLon_rad)
         .def_readonly("Lat",&GeoPoint::mfLat_rad)
         ;

      class_<tcLauncherInfo>("LauncherInfo")
         .def_readonly("Launcher",&tcLauncherInfo::mnLauncher)   // index of launcher, or -1 for none
         .def_readonly("Quantity",&tcLauncherInfo::mnQuantity)
         .def_readonly("TargetFlags",&tcLauncherInfo::mnTargetFlags) // 0x01 - surface, 0x02 - air, 0x04 - land
         .def_readonly("Range_km",&tcLauncherInfo::mfRange_km)
         .def_readonly("MinLaunchAlt_m", &tcLauncherInfo::minLaunchAlt_m)
         .def_readonly("MaxLaunchAlt_m", &tcLauncherInfo::maxLaunchAlt_m)
         .def_readonly("MinRange_km", &tcLauncherInfo::minRange_km)
         .def_readonly("MaxRange_km", &tcLauncherInfo::maxRange_km)
         .def_readonly("LaunchMode",&tcLauncherInfo::mnLaunchMode)  // 0 - datum, 1 - handoff
         .def_readonly("MaxDepth_m",&tcLauncherInfo::maxDepth_m) 
         .def_readonly("Speed_mps", &tcLauncherInfo::speed_mps)
         .def_readonly("SectorCenter", &tcLauncherInfo::sectorCenter)
         .def_readonly("SectorWidth", &tcLauncherInfo::sectorWidth)
		 .def_readonly("FireControlTracks", &tcLauncherInfo::fireControlTracks)
		 .def_readonly("MaxFireControlTracks", &tcLauncherInfo::maxFireControlTracks)
         .def_readonly("IsNuclear", &tcLauncherInfo::isNuclear)
         .def_readonly("IsLoading", &tcLauncherInfo::isLoading)
         .def_readonly("AcceptsWaypoints", &tcLauncherInfo::acceptsWaypoints)
         .def_readonly("LifeTime_s", &tcLauncherInfo::lifeTime_s)
         .def_readonly("Status", &tcLauncherInfo::launcherStatus)
         .def("IsValid", &tcLauncherInfo::IsValid)
         ;

      class_<tcSensorInfo>("SensorInfo")
          .def_readonly("isActive",&tcSensorInfo::isActive)
          .def_readonly("type",&tcSensorInfo::type)
          .def("IsPassive", &tcSensorInfo::IsPassive)
          ;

      class_<tcFireControlInfo>("FireControlInfo")
          .def_readonly("radarGuidanceActive", &tcFireControlInfo::radarGuidanceActive)
          .def_readonly("maxLeft_deg", &tcFireControlInfo::maxLeft_deg)
          .def_readonly("maxRight_deg", &tcFireControlInfo::maxRight_deg)
		  .def_readonly("weaponsOut", &tcFireControlInfo::weaponsOut)
          ;

	  class_<EmitterInfo>("EmitterInfo")
		  .def_readonly("EmitterID", &EmitterInfo::mnEmitterID)
		  .def_readonly("Timestamp", &EmitterInfo::mfTimestamp)
		  .def_readonly("Mode", &EmitterInfo::mnMode)
		  .def("GetEmitterName", &EmitterInfo::GetEmitterName)
		  ;
   }

}

