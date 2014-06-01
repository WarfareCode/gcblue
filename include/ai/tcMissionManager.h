/**
**  @file tcMissionManager.h
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

#ifndef _TCMISSIONMANAGER_H_
#define _TCMISSIONMANAGER_H_

#include <map>
#include <vector>
#include "ai/MissionAircraftInfo.h"

class tcFlightPort;
class tcAirObject;
class tcGameObject;

class tcStream;
class tcCommandStream;
class tcUpdateStream;
class tcGameStream;
class tcMapOverlay;
class tcDateTime;

namespace scriptinterface
{
    class tcScenarioLogger;
}

namespace ai {

class tcMission;

/**
* Organizes and controls missions for aircraft in flightport.
*
* Select aircraft based on mission type and outfits according to mission
* type. Set AI tasks (waypoints, etc) for aircraft to carry out mission.
* Schedule launches. 
* 
* @see tcFlightPort
*/
class tcMissionManager
{
public:	
    static void AttachMapOverlay(tcMapOverlay* overlay);

    // data for multiplayer commands
	struct CommandInfo
	{
        enum {DELETE_MISSION = 0, MOVE_CAP = 1};
		unsigned int id; ///< mission id that command applies to
		unsigned char op; ///< 0 - delete mission, 1 - move CAP
        float val_a;
        float val_b;
	};
    void AddCommand(const CommandInfo& cmd);

    void AdjustMissionsForNewStartDate(const tcDateTime& oldStart, const tcDateTime& newStart);

	void AddMission(tcMission* mission_);
	void DeleteMission(unsigned int missionId);
	void PerformDeletions();
    void Clear();

	std::vector<MissionAircraftInfo>& GetAvailableAircraft(int targetMask);
	tcAirObject* GetAircraft(long id);
    tcAirObject* GetAircraft(const std::string& unitName);

    unsigned int GetAircraftMissionId(long aircraftId);
    unsigned int GetAircraftMissionId(const std::string& unitName);
	long GetFlightportParentId() const;
	tcGameObject* GetFlightportParent();
	bool IsAircraftReserved(long id) const;
	void LaunchAircraft(long id);
	void Update(double t);

    void UpdateReserved(); // update map of aircraft involved in missions


    tcMission* GetMission(unsigned int id);
    tcMission* GetMissionByIdx(unsigned int idx);
    size_t GetMissionCount() const;

    unsigned int GetEditMissionId() const;
    void SetEditMissionId(unsigned int id);

    void SaveToPython(scriptinterface::tcScenarioLogger& logger);

    virtual tcUpdateStream& operator<<(tcUpdateStream& stream);
    virtual tcUpdateStream& operator>>(tcUpdateStream& stream);

    virtual tcCommandStream& operator<<(tcCommandStream& stream);
    virtual tcCommandStream& operator>>(tcCommandStream& stream);

    virtual tcGameStream& operator<<(tcGameStream& stream);
    virtual tcGameStream& operator>>(tcGameStream& stream);

    void ClearNewCommand();
    bool HasNewCommand() const;

	tcMissionManager(tcFlightPort* fp);
	virtual ~tcMissionManager();

private:
	tcFlightPort* flightPort;
	std::vector<tcMission*> missions;
	std::map<long, unsigned int> reserved; ///< map of reserved aircraft (aircraft id, mission id)
    std::map<std::string, unsigned int> reserved2; ///< map of reserved aircraft (aircraft name, mission id)

	double lastUpdate;
	std::vector<unsigned int> missionsToDelete;

    /// to work-around limitation of tactical map waypoint edit, show/edit waypoints of this mission when
    /// host flight ops object is hooked. If 0, then disable mission waypoint editing
    unsigned int editMissionId; 


	std::vector<CommandInfo> commandList;


    static tcMapOverlay* mapOverlay;

    void CreateMapMissionObject(unsigned int missionId);

	
};

} // namespace


#endif

