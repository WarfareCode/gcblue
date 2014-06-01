/**
**  @file tcCAPMission.cpp
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

#include "ai/tcCAPMission.h"
#include "ai/tcMissionManager.h"
#include "ai/Brain.h"
#include "ai/BlackboardInterface.h"
#include "tcWeaponDBObject.h"
#include "tcAirObject.h"
#include "tcPlatformObject.h"
#include "tcSimState.h"
#include "common/tcStream.h"
#include "common/tcObjStream.h"
#include "common/tcGameStream.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace ai;



/**
* Loads state from update stream
*/
tcUpdateStream& tcCAPMission::operator<<(tcUpdateStream& stream)
{
    stream >> station.x;
    stream >> station.y;

    CalculatePatrolOffset();

    return stream;
}

/**
* Saves state to update stream
*/
tcUpdateStream& tcCAPMission::operator>>(tcUpdateStream& stream)
{
    stream << station.x;
    stream << station.y;

    return stream;
}

/**
* Loads state from game stream
*/
tcGameStream& tcCAPMission::operator<<(tcGameStream& stream)
{
    tcMission::operator<<(stream);

    stream >> quantity;
    stream >> station.x;
    stream >> station.y;

    CalculatePatrolOffset();

    return stream;
}

/**
* Saves state to game stream
*/
tcGameStream& tcCAPMission::operator>>(tcGameStream& stream)
{
    tcMission::operator>>(stream);

    stream << quantity;
    stream << station.x;
    stream << station.y;

    return stream;
}



void tcCAPMission::CalculatePatrolOffset()
{
    if (missionManager ==  0) return;

	tcGameObject* parent = missionManager->GetFlightportParent();
	if (parent == 0)
	{
		wxASSERT(false);
		return;
	}

	range_km = parent->mcKin.RangeToKm(station.x, station.y);
	az_deg = C_180OVERPI * parent->mcKin.HeadingToGeoRad(station.x, station.y);
}

void tcCAPMission::GetPatrolOffset(float& range_km_, float& az_deg_) const
{
    range_km_ = range_km;
    az_deg_ = az_deg;
}

tcPoint tcCAPMission::GetStation() const
{
    return station;
}

/**
* If no mission aircraft are in flight with an active "CAP" task,
* then restart the mission
*/
void tcCAPMission::MonitorMissionInProgress()
{
	tcSimState* simState = tcSimState::Get();

	bool anyInFlight = false;
	for (size_t n=0; (n<missionAircraft.size()) && (!anyInFlight); n++)
	{
		tcPlatformObject* obj = dynamic_cast<tcPlatformObject*>(simState->GetObjectByName(missionAircraft[n].name));
		if (obj != 0)
		{
			if (obj->GetBrain()->TaskExists("CAP")) anyInFlight = true;
		}
	}

	if (!anyInFlight) stage = "init"; // launch another patrol
}

void tcCAPMission::SetStation(float lon_rad, float lat_rad)
{
	station.x = lon_rad;
	station.y = lat_rad;

    CalculatePatrolOffset();
}


void tcCAPMission::Update(double t)
{
	wxASSERT(missionManager != 0);
	if (missionManager == 0) return;

	// step 1, get aircraft for mission
	// step 2, outfit aircraft
	// step 3, create tasks for mission on each aircraft
	// step 4, order launch of aircraft
	// step 5, when all aircraft launched, wait until aircraft landed
	// step 6, start over (recurring mission)


	if (stage == "init")
	{
        CalculatePatrolOffset();

		// query available aircraft and take first from list
		std::vector<MissionAircraftInfo> candidates = missionManager->GetAvailableAircraft(AIR_TARGET);
		missionAircraft.clear();

		for (size_t n=0; (n<quantity)&&(n<candidates.size()); n++)
		{
			missionAircraft.push_back(candidates[n]);
		}
		if (missionAircraft.size() == 0) return; // none available

		stage = "outfit";
	}
	else if (stage == "outfit")
	{
		bool allOutfitted = true;

		for (size_t n=0; n<missionAircraft.size(); n++)
		{
			tcAirObject* aircraft = missionManager->GetAircraft(missionAircraft[n].id);
			if (aircraft != 0)
			{
				if (!aircraft->IsEquippedForTargetType(AIR_TARGET))
				{
					aircraft->EquipForTargetType(AIR_TARGET);
					allOutfitted = false;
				}
                if (aircraft->GetDamageLevel() > 0)
                {
                    stage = "init"; // damaged aircraft, let's restart mission
                    return;
                }
			}
		}
		if (allOutfitted) stage = "task";
	}
	else if (stage == "task")
	{
		wxString s;
		for (size_t n=0; n<missionAircraft.size(); n++)
		{
			tcAirObject* aircraft = missionManager->GetAircraft(missionAircraft[n].id);
			if (aircraft != 0)
			{
				ai::Brain* brain = aircraft->GetBrain();
				brain->AddTask("CAP", 2.0);
				brain->AddTask("EngageAll", 3.0);
				ai::BlackboardInterface bb = brain->GetBlackboardInterface();
				
				s.Printf("%.1f", range_km);
				bb.Write("PatrolRange_km", s.ToStdString());

				s.Printf("%.1f", az_deg);
				bb.Write("PatrolAzimuth_deg", s.ToStdString());

				s.Printf("%d", missionManager->GetFlightportParentId());
				bb.Write("AnchorPlatformId", s.ToStdString());
			}
		}

		stage = "launch";
	}
	else if (stage == "launch")
	{
		for (size_t n=0; n<missionAircraft.size(); n++)
		{
			missionManager->LaunchAircraft(missionAircraft[n].id);
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

	// do following at slower update
	double dt = t - lastUpdate;
	if (dt < 20.0) return;
	lastUpdate = t;

	if (stage == "waitland")
	{
		MonitorMissionInProgress();
	}

}

void tcCAPMission::UpdateStation()
{
    if (missionManager == 0)
    {
        wxASSERT(false);
        return;
    }

    tcSimState* simState = tcSimState::Get();

    for (size_t n=0; n<missionAircraft.size(); n++)
    {
        tcPlatformObject* obj = dynamic_cast<tcPlatformObject*>(simState->GetObjectByName(missionAircraft[n].name));
        if (obj != 0)
        {
            ai::Brain* brain = obj->GetBrain();
            ai::BlackboardInterface bb = brain->GetBlackboardInterface();

            wxString s;
            s.Printf("%.1f", range_km);
            bb.Write("PatrolRange_km", s.ToStdString());

            s.Printf("%.1f", az_deg);
            bb.Write("PatrolAzimuth_deg", s.ToStdString());
        }
    }
}


const tcCAPMission& tcCAPMission::operator=(const tcCAPMission& src)
{
	tcMission::operator=(src);

	quantity = src.quantity;
	station = src.station;

	return *this;
}


tcCAPMission::tcCAPMission(unsigned int id_, tcMissionManager* mm)
: tcMission(id_, mm),
  quantity(2),
  range_km(0),
  az_deg(0)
{
}

tcCAPMission::tcCAPMission(const tcCAPMission& src)
: tcMission(src),
  quantity(src.quantity),
  range_km(src.range_km),
  az_deg(src.az_deg),
  station(src.station)
{
}

tcCAPMission::tcCAPMission()
: tcMission(),
  quantity(2),
  range_km(0),
  az_deg(0)
{


}


tcCAPMission::~tcCAPMission() 
{
}