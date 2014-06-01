/**
**  @file tcMission.h
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

#ifndef _TCMISSION_H_
#define _TCMISSION_H_

#include <string>
#include <vector>
#include "ai/MissionAircraftInfo.h"
#include "ai/Route.h"

class tcStream;
class tcGameStream;

namespace ai {

class tcMissionManager;

/**
* Base class for air missions
*
* @see tcFlightPort, tcMissionManager
*/
class tcMission
{
public:
	friend class tcMissionManager; // to access nextId

	void EndMission();
	unsigned int GetId() const;
	const std::vector<MissionAircraftInfo>& GetMissionAircraft() const;
	const std::vector<MissionAircraftInfo>& GetAirborneMissionAircraft() const;

    virtual void AddMissionAircraft(const std::string& name, const std::string& role);
    virtual void RemoveMissionAircraft(const std::string& name);
    void RenameMissionAircraft(const std::string& oldName, const std::string& newName);
    void SwapMissionAircraft(const std::string& air1, long id1, const std::string& air2, long id2);

	bool AllMissionAircraftDeparted() const;
    bool AllMissionAircraftLanded() const;

	void SetMissionManager(tcMissionManager* mm);
	virtual void Update(double t);

    Route* GetRoute();
    bool IsLocked() const;

    virtual tcGameStream& operator<<(tcGameStream& stream);
    virtual tcGameStream& operator>>(tcGameStream& stream);

    static void ResetNextId();

	const tcMission& operator=(const tcMission& src);
	tcMission();
	tcMission(const tcMission& src);
    tcMission(unsigned int id_, tcMissionManager* mm);
	virtual ~tcMission();

protected:
	tcMissionManager* missionManager;
	std::vector<MissionAircraftInfo> missionAircraft;
	std::string stage;
	double lastUpdate;
    bool isLocked; ///< true if mission in progress, don't accept edits

    /// route data for this mission, loaded as default Nav task for mission aircraft
    Route route; 

private:
	static unsigned int nextId; ///< for assigning unique mission id
	unsigned int id; ///< unique identifier for mission
};


} // namespace



#endif