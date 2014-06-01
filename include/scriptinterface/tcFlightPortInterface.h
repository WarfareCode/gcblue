/**  
**  @file tcFlightPortInterface.h
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

#ifndef __tcFlightPortInterface_h__
#define __tcFlightPortInterface_h__


#if _MSC_VER > 1000
#pragma once
#endif 


#include "tcFlightPort.h"
#include "tcSensorMap.h" // for tcTrack

#include <string>
#include <boost/python.hpp>


class tcSimState;
class tcSoundConsole;
class tcMapOverlay;

using namespace boost::python;

namespace ai
{
    class Route;
    class tcAttackMission;
}

namespace scriptinterface 
{
	class tcPlatformInterface;

    /**
    *
    */
    class tcFlightUnitStatus 
    {
    public:
        std::string unit_name;
        std::string current_loc;
        std::string goal_loc;
        bool atDestination;
        bool isIdle;
        int runway; ///< -1 if not on a runway, otherwise runway number
        double ready_time;
    };
    /* Static variable is used as a way to pass a pointer to the Python object.
    ** It is likely that there's a way to do this directly without awkwardness
    ** associated with the static vars, etc.
    */
    /**
    * Interface for control of flightport (airfield, helo deck, carrier deck)
    */
    class tcFlightPortInterface
    {
    public:        
        tcFlightPort *flightport;
        static tcFlightPort *static_flightport;
        double mfCurrentTime;
        
        // Interface class management functions
        static object GetInterface(void);
        static void SetObj(tcFlightPort *port) {static_flightport = port;}
        void GetLocalObj(void) {flightport = static_flightport;}
        void SetFlightPort(tcFlightPort *port) {flightport = port;} ///< method to directly set local flightport
        static void AttachSimState(tcSimState *apSS) {mpSimState = apSS;}
        static void AttachConsole(tcSoundConsole *apConsole) {mpConsole = apConsole;}

        // Interface functions to be called through Python
        bool IsValid();
        /// @returns simulation time of last update of this flightport
        double GetTime();
        /// @returns number of air units in this flightport
        int GetUnitCount();
        /// @returns id of unit n (index starts at 0)
        long GetUnitID(int n); // long used for compatibility with Python
        /// @returns status object for unit n, @see scriptinterface::tcFlightUnitStatus
        tcFlightUnitStatus GetUnitStatus(int n);
        std::string GetUnitName(int n);
        /// @returns string for loc, @see tcAirState::LocationToString
        std::string GetUnitLocation(int n);
        /// @returns string for goal loc, @see tcAirState::LocationToString
        std::string GetUnitGoalLocation(int n);
		/// @return platform interface object for unit
		tcPlatformInterface GetUnitPlatformInterface(int n);
        /// launch unit on indicated runway
        void Launch(int runway);
        /// launch unit matching id (if unit is on runway)
        void LaunchID(long id);
        /// sets destination of unit n; dest_code: 0 - hangar, 1 - ready, 2 - runway/launch
        void SetDestination(int n, int dest_code);

        // mission commands
		void AddAttackMission(long targetId);
		void AddCAPMission(float lon_rad, float lat_rad); ///< auto-mission for CAP only
        void AddAEWMission(float lon_rad, float lat_rad); ///< auto-mission for AEW only
        void AddASWMission(float lon_rad, float lat_rad); ///< auto-mission for ASW only
		unsigned int AddGenericMission(); ///< new format which handles variety of mission types
        void AddAircraftToMission(unsigned int missionId, const std::string& aircraft);
        void RemoveAircraftFromMission(unsigned int missionId, const std::string& aircraft);
        void SetMissionLaunchTime(unsigned int missionId, const std::string& timeString);
        void SetMissionDatum(unsigned int missionId, float lon_rad, float lat_rad);
        void SetMissionType(unsigned int missionId, const std::string& missionType);
        const char* GetMissionType(unsigned int missionId);
        void SetMissionLandingTarget(unsigned int missionId, const std::string& baseName);
        bool HasAircraftForMission(const std::string& missionType);

        unsigned int GetMissionWaypointCount(unsigned int missionId);
        void AddMissionWaypoint(unsigned int missionId, float lon_rad, float lat_rad);
        void AddMissionWaypointAdvanced(unsigned int missionId, 
            float lon_rad, float lat_rad, float alt_m, float speed_kts);
        void EditMissionWaypoint(unsigned int missionId, unsigned int idx, float lon_rad, float lat_rad);
        void EditMissionWaypointAdvanced(unsigned int missionId, unsigned int idx, 
                                         float lon_rad, float lat_rad, float alt_m, float speed_kts);
        void EditMissionWaypointReference(unsigned int missionId, unsigned int idx, 
                                         unsigned char referenceMode, long referencePlatform);
        void InsertMissionWaypoint(unsigned int missionId, unsigned int idx, float lon_rad, float lat_rad);
        void DeleteMissionWaypoint(unsigned int missionId, unsigned int idx);
        void ClearMissionWaypoints(unsigned int missionId);
        void SetMissionWaypointTasks(unsigned int missionId, size_t idx, const std::string& taskList);
        void AddMissionWaypointTask(unsigned int missionId, size_t idx, const std::string& task);
        void RemoveMissionWaypointTask(unsigned int missionId, size_t idx, const std::string& task);
        void SetMissionPatrolArea(unsigned int missionId, const std::string& areaString);
        const char* GetMissionPatrolArea(unsigned int missionId);
        void SetMissionPatrolAnchor(unsigned int missionId, const std::string& anchorUnit, int anchorMode);
        void SetMissionWaveQuantity(unsigned int missionId, unsigned int quantity);
        void TransformToRelativePatrolArea(unsigned int missionId);
        void TransformToAbsolutePatrolArea(unsigned int missionId);

        unsigned int GetMissionCount() const;
        unsigned int GetMissionId(unsigned int idx) const;
        unsigned int GetEditMissionId() const;
        void SetEditMissionId(unsigned int id);
        


        tcFlightPortInterface();
        virtual ~tcFlightPortInterface();

        static void AttachMapOverlay(tcMapOverlay* mo) {overlay = mo;}

    private:
        static tcSimState* mpSimState;
        static tcSoundConsole* mpConsole;
        static tcMapOverlay* overlay;
        char buff[128];

        ai::Route* GetMissionRoute(unsigned int missionId);
        ai::tcAttackMission* GetAttackMission(unsigned int missionId);
    };

}

#endif // __tcFlightPortInterface_h__

