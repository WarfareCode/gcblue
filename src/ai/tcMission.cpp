/**
**  @file tcMission.cpp
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

#include "ai/tcMission.h"
#include "ai/tcMissionManager.h"
#include "tcAirObject.h"
#include "tcSimState.h"
#include "common/tcGameStream.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace ai;

unsigned int tcMission::nextId = 1;

/**
* Call when loading new scenario to start mission numbering from 1,
* looks like just a cosmetic detail
*/
void tcMission::ResetNextId()
{
    nextId = 1;
}

/**
* Load
*/
tcGameStream& tcMission::operator<<(tcGameStream& stream)
{
    stream >> stage;
    stream >> lastUpdate;
    stream >> isLocked;
    route.operator<<(stream);

    missionAircraft.clear();
    unsigned char nAircraft;
    stream >> nAircraft;
    for (unsigned char n=0; n<nAircraft; n++)
    {
        MissionAircraftInfo temp;

        stream >> temp.id;
        stream >> temp.loadout;
        stream >> temp.name;
        stream >> temp.role;
        stream >> temp.active;

        missionAircraft.push_back(temp);
    }

    return stream;
}

/**
* Save
*/
tcGameStream& tcMission::operator>>(tcGameStream& stream)
{
    stream << stage;
    stream << lastUpdate;
    stream << isLocked;
    route.operator>>(stream);

    wxASSERT(missionAircraft.size() < 256);
    unsigned char nAircraft = missionAircraft.size();
    stream << nAircraft;
    for (unsigned char n=0; n<nAircraft; n++)
    {
        stream << missionAircraft[n].id;
        stream << missionAircraft[n].loadout;
        stream << missionAircraft[n].name;
        stream << missionAircraft[n].role;
        stream << missionAircraft[n].active;
    }

    return stream;
}


void tcMission::AddMissionAircraft(const std::string& name, const std::string& role)
{
    if (isLocked) return;

    // check that aircraft with matching name isn't already in list
    bool found = false;
    for (size_t n=0; n<missionAircraft.size(); n++)
    {
        if (missionAircraft[n].name == name)
        {
            found = true;
        }
    }

    if (!found)
    {
        if (tcAirObject* air = missionManager->GetAircraft(name))
        {

            MissionAircraftInfo info;
            info.id = air->mnID;
            info.name = name;
            info.role = role;
            info.active = false;

            missionAircraft.push_back(info);
        }
    }
}


/**
* @return true if all active mission aircraft do not exist within flightport
* Normally this occurs when all have launched (could also be due to damage)
*/
bool tcMission::AllMissionAircraftDeparted() const
{
	for (size_t n=0; n<missionAircraft.size(); n++)
	{
        if ((missionAircraft[n].active) && (missionManager->GetAircraft(missionAircraft[n].id) != 0))
		{
			return false;
		}
	}

	return true;
}

/**
* @return true if all mission aircraft landed at flightport
*/
bool tcMission::AllMissionAircraftLanded() const
{
	for (size_t n=0; n<missionAircraft.size(); n++)
	{
        if (missionManager->GetAircraft(missionAircraft[n].name) == 0)
		{
			return false; // couldn't find aircraft n (assume in flight)
		}
	}

	return true;
}


/**
* End mission (safely deletes from mission manager)
*/
void tcMission::EndMission()
{
	missionManager->DeleteMission(id);
}

unsigned int tcMission::GetId() const
{
	return id;
}

const std::vector<MissionAircraftInfo>& tcMission::GetMissionAircraft() const
{
	return missionAircraft;
}

const std::vector<MissionAircraftInfo>& tcMission::GetAirborneMissionAircraft() const
{
	static std::vector<MissionAircraftInfo> airborneAircraft;
	airborneAircraft.clear();
	tcSimState* simState = tcSimState::Get();

	for (size_t n=0; n<missionAircraft.size(); n++)
	{
		MissionAircraftInfo aircraft_n(missionAircraft[n]);

		tcAirObject* air = dynamic_cast<tcAirObject*>(simState->GetObjectByName(aircraft_n.name));
		bool inAir = (air != 0) && (air->parent == 0);
		if (inAir)
		{
			wxASSERT(aircraft_n.id == air->mnID);
			aircraft_n.id = air->mnID;
			airborneAircraft.push_back(aircraft_n);
		}
	}

	return airborneAircraft;
}

Route* tcMission::GetRoute()
{
    return &route;
}

bool tcMission::IsLocked() const
{
    return isLocked;
}


/**
* Use "All" to clear all mission aircraft
*/
void tcMission::RemoveMissionAircraft(const std::string& name)
{
    if (isLocked) return;

    if (name == "All")
    {
        missionAircraft.clear();
        return;
    }

    std::vector<MissionAircraftInfo> temp;
    for (size_t n=0; n<missionAircraft.size(); n++)
    {
        if (missionAircraft[n].name != name)
        {
            temp.push_back(missionAircraft[n]);
        }
    }

    missionAircraft = temp;
}



void tcMission::SetMissionManager(tcMissionManager* mm)
{
	missionManager = mm;
}

/**
* If air1 isn't in list, do nothing. If air2 is new replace air1 with air2.
* Otherwise swap position of air2 and air1. Keep role fields in old position.
*/
void tcMission::SwapMissionAircraft(const std::string& air1, long id1,  const std::string& air2, long id2)
{
    size_t idx1 = 999;
    size_t idx2 = 999;
    bool found1 = false;
    bool found2 = false;

    for (size_t n=0; n<missionAircraft.size(); n++)
    {
        if (missionAircraft[n].name == air1)
        {
            idx1 = n;
            found1 = true;
        }

        if (missionAircraft[n].name == air2)
        {
            idx2 = n;
            found2 = true;
        }
    }

    if (!found1) return;

    MissionAircraftInfo temp(missionAircraft[idx1]);

    missionAircraft[idx1].name = air2;
    missionAircraft[idx1].id = id2;

    if (found2)
    {
        missionAircraft[idx2].name = air1;
        missionAircraft[idx2].id = id1;
    }

}

void tcMission::Update(double t)
{
}


const tcMission& tcMission::operator=(const tcMission& src)
{
	missionManager = src.missionManager;
	id = src.id;
	stage = src.stage;
	missionAircraft = src.missionAircraft;
	lastUpdate = src.lastUpdate;
    isLocked = src.isLocked;

	return *this;
}


tcMission::tcMission(unsigned int id_, tcMissionManager* mm)
: missionManager(mm),
  id(id_),
  stage("init"),
  lastUpdate(0),
  isLocked(false)
{
    nextId = std::max(id, nextId);
}


tcMission::tcMission(const tcMission& src)
: missionManager(src.missionManager),
  id(src.id),
  stage(src.stage),
  missionAircraft(src.missionAircraft),
  lastUpdate(src.lastUpdate),
  isLocked(src.isLocked)
{
}

tcMission::tcMission()
: missionManager(0),
  id(nextId++),
  stage("init"),
  lastUpdate(0),
  isLocked(false)
{

}


tcMission::~tcMission() 
{
}