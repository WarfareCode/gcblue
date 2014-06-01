/**
**  @file tcMissionManager.cpp
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

#include "ai/tcMissionManager.h"
#include "ai/tcMission.h"
#include "ai/tcCAPMission.h"
#include "ai/tcAttackMission.h"
#include "tcFlightPort.h"
#include "tcPlatformObject.h"
#include "tcAirObject.h"
#include "tcHeloObject.h"
#include "tcWeaponDBObject.h"
#include "common/tcStream.h"
#include "common/tcObjStream.h"
#include "common/tcGameStream.h"
#include "tcMapOverlay.h"
#include "tcMapMissionObject.h"
#include "tcScenarioLogger.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace ai;


tcMapOverlay* tcMissionManager::mapOverlay = 0;

void tcMissionManager::AttachMapOverlay(tcMapOverlay* overlay)
{
    mapOverlay = overlay;
}


/**
* Loads state from update stream
*/
tcUpdateStream& tcMissionManager::operator<<(tcUpdateStream& stream)
{
    Clear();

    unsigned char nMissions;
    stream >> nMissions;

    for (unsigned char n=0; n<nMissions; n++)
    {
        unsigned char missionType;
        stream >> missionType;

        switch (missionType)
        {
        case 0: 
            break; // skip, do nothing
        case 1:
            {
                unsigned int missionId;
                stream >> missionId;

                tcCAPMission* cap = new tcCAPMission(missionId, this);
                cap->operator<<(stream);
                AddMission(cap);

                CreateMapMissionObject(missionId);
            }
            break;
        default:
            wxASSERT(false);
            break;
        }

    }

    unsigned char checko = 0;
    stream >> checko; // should be 34

    return stream;
}

/**
* Saves state to update stream
*/
tcUpdateStream& tcMissionManager::operator>>(tcUpdateStream& stream)
{
    wxASSERT(missions.size() < 256);

    unsigned char nMissions = (unsigned char)missions.size();
    stream << nMissions;

    for (unsigned char n=0; n<nMissions; n++)
    {
        tcMission* mission = missions[n];
        unsigned char missionType = 0;
        if (tcCAPMission* cap = dynamic_cast<tcCAPMission*>(mission))
        {
            missionType = 1;
            stream << missionType;

            unsigned int missionId = mission->GetId();
            stream << missionId;

            cap->operator>>(stream);
        }
        else if (tcAttackMission* attack = dynamic_cast<tcAttackMission*>(mission))
        {
            missionType = 0;
            stream << missionType;
        }
        else
        {
            wxASSERT(false);
            missionType = 0;
            stream << missionType;
        }
    }

    unsigned char checko = 34;
    stream << checko;

    return stream;
}


/**
* Loads state from command stream
*/
tcCommandStream& tcMissionManager::operator<<(tcCommandStream& stream)
{
	unsigned char nCommands;
	stream >> nCommands;

	for (unsigned char n=0; n<nCommands; n++)
	{
		unsigned int id;
		unsigned char op;
		float val_a;
        float val_b;

		stream >> id;
		stream >> op;
		stream >> val_a;
        stream >> val_b;

        tcMission* mission = GetMission(id);
        if (mission != 0)
        {
            switch (op)
            {
            case 0: // delete mission
                DeleteMission(id);
                break;
            case 1: // move CAP station
                {
                    if (ai::tcCAPMission* cap = dynamic_cast<ai::tcCAPMission*>(mission))
                    {
                        cap->SetStation(val_a, val_b);
                        cap->UpdateStation();
                    }
                    else
                    {
                        fprintf(stderr, "tcMissionManager::operator<< - not CAP mission (%d)\n", id);
                    }
                }
                break;
            default:
                fprintf(stderr, "tcMissionManager::operator<< - Bad op (%d)\n", op);
                wxASSERT(false);
                break;
            }
        }
        else
        {
            fprintf(stderr, "tcMissionManager::operator<< - Bad mission id (%d)\n", id);
            wxASSERT(false);
        }

	}

    return stream;
}

/**
* Saves state to command stream
*/
tcCommandStream& tcMissionManager::operator>>(tcCommandStream& stream)
{
	unsigned char nCommands = (unsigned char)commandList.size();
    wxASSERT(commandList.size() < 256);

	stream << nCommands;

	for (unsigned char n=0; n<nCommands; n++)
	{
		stream << commandList[n].id;
		stream << commandList[n].op;
		stream << commandList[n].val_a;
        stream << commandList[n].val_b;
	}

    return stream;
}


/**
* Loads state from game stream
*/
tcGameStream& tcMissionManager::operator<<(tcGameStream& stream)
{
    Clear();

    unsigned char nMissions;
    stream >> nMissions;
    wxASSERT(nMissions < 256);

    for (unsigned char n=0; n<nMissions; n++)
    {
        unsigned char missionType;
        unsigned int missionId;
        stream >> missionType;
        stream >> missionId;

        switch (missionType)
        {
        case 1:
            {
            tcCAPMission* cap = new tcCAPMission(missionId, this);
            cap->operator<<(stream);
            AddMission(cap);
            }
            break;
        case 2:
            {
            tcAttackMission* attack = new tcAttackMission(missionId, this);
            attack->operator<<(stream);
            AddMission(attack);
            }
            break;
        default:
            wxASSERT(false);
            break;
        }
    }
        

    stream.ReadCheckValue(-34);
 
    return stream;
}

/**
* Saves state to game stream
*/
tcGameStream& tcMissionManager::operator>>(tcGameStream& stream)
{
    wxASSERT(missions.size() < 256);

    unsigned char nMissions = (unsigned char)missions.size();
    stream << nMissions;

    for (unsigned char n=0; n<nMissions; n++)
    {
        tcMission* mission = missions[n];
        unsigned char missionType = 0;
        unsigned int missionId = 0;
        if (tcCAPMission* cap = dynamic_cast<tcCAPMission*>(mission))
        {
            missionType = 1;
            missionId = mission->GetId();
        }
        else if (tcAttackMission* attack = dynamic_cast<tcAttackMission*>(mission))
        {
            missionType = 2;
            missionId = mission->GetId();
        }
        else
        {
            wxASSERT(false);
        }

        stream << missionType;
        stream << missionId;

        mission->operator>>(stream);
    }

    stream.WriteCheckValue(-34);
 
    return stream;
}


void tcMissionManager::AdjustMissionsForNewStartDate(const tcDateTime& oldStart, const tcDateTime& newStart)
{
    double offset_hr = 24.0 * (newStart.GetJulianDate() - oldStart.GetJulianDate());

	for (size_t n=0; n<missions.size(); n++)
	{
        if (tcAttackMission* attack = dynamic_cast<tcAttackMission*>(missions[n]))
        {
            attack->AdjustLaunchTimeHours(offset_hr);
        }
	}
}


void tcMissionManager::ClearNewCommand()
{
	commandList.clear();
}

bool tcMissionManager::HasNewCommand() const
{
	return (commandList.size() > 0);
}


void tcMissionManager::AddCommand(const CommandInfo& cmd)
{
    commandList.push_back(cmd);
}



void tcMissionManager::AddMission(tcMission* mission_)
{
	mission_->SetMissionManager(this);
	missions.push_back(mission_);
	tcMission::nextId = std::max(tcMission::nextId, mission_->GetId()+1);
}

void tcMissionManager::Clear()
{
    missions.clear();
	reserved.clear();
    reserved2.clear();
	lastUpdate = 0;
	missionsToDelete.clear();
    editMissionId = 0;
}

/**
* For multiplayer client, create tcMapMissionObject if it doesn't exist
* for this missionId
*/
void tcMissionManager::CreateMapMissionObject(unsigned int missionId)
{
    // query tcMapOverlay to see if corresponding tcMapMissionObject exists. If not then create one
    // for this mission.
    wxASSERT(mapOverlay != 0);

    tcMapMissionObject* missionObject = mapOverlay->GetMissionObject(missionId);
    if (missionObject == 0)
    {
        wxASSERT(flightPort != 0);
        wxASSERT(flightPort->parent != 0);

        tcMapMissionObject* missionObj = new tcMapMissionObject(flightPort->parent->mnID, missionId);
        missionObj->SetInteractive(true);

        mapOverlay->AddMapObject(missionObj);
    }
}


void tcMissionManager::DeleteMission(unsigned int missionId)
{
	missionsToDelete.push_back(missionId);
}

tcAirObject* tcMissionManager::GetAircraft(long id)
{
	return dynamic_cast<tcAirObject*>(flightPort->GetObjectById(id));
}

tcAirObject* tcMissionManager::GetAircraft(const std::string& unitName)
{
    return dynamic_cast<tcAirObject*>(flightPort->GetObjectByName(unitName));
}

/**
* @param aircraftId local flightport id of aircraft to search for
* @return missionId of mission that aircraft is assigned to, or 0 if not assigned
* Should call UpdateReserved() first if mission aircraft changes have been made
*/
unsigned int tcMissionManager::GetAircraftMissionId(long aircraftId)
{
    std::map<long, unsigned int>::const_iterator iter = 
        reserved.find(aircraftId);

    if (iter != reserved.end())
    {
        return iter->second;
    }
    else
    {
        return 0;
    }
}

/**
* @param unitName unit name of platform to search for
* @return missionId of mission that aircraft is assigned to, or 0 if not assigned
* Should call UpdateReserved() first if mission aircraft changes have been made
*/
unsigned int tcMissionManager::GetAircraftMissionId(const std::string& unitName)
{
    std::map<std::string, unsigned int>::const_iterator iter = 
        reserved2.find(unitName);

    if (iter != reserved2.end())
    {
        return iter->second;
    }
    else
    {
        return 0;
    }
}

bool MAIRatingSort(const MissionAircraftInfo& a, const MissionAircraftInfo& b)
{
	return (a.rating > b.rating);
}

/**
* Will only use helos for sub targets
*/
std::vector<MissionAircraftInfo>& tcMissionManager::GetAvailableAircraft(int targetMask)
{
	static std::vector<MissionAircraftInfo> availableAircraft;
	availableAircraft.clear();

    const bool subsurfaceTarget = (targetMask == SUBSURFACE_TARGET);
    const bool aewPatrol = (targetMask == AEW_TARGET);

	UpdateReserved();

	size_t nAircraft = flightPort->GetCount();

	for (size_t n=0; n<nAircraft; n++)
	{
		tcAirState* airState = flightPort->GetAirState((unsigned int)n);

		long id = airState->obj->mnID;
		if (!IsAircraftReserved(id))
		{
			tcPlatformObject* platform = dynamic_cast<tcPlatformObject*>(airState->obj);
			wxASSERT(platform != 0);
            bool isHelo = dynamic_cast<tcHeloObject*>(platform) != 0;
    
			if ((platform != 0) && (!isHelo || subsurfaceTarget || aewPatrol) && (platform->IsCapableVsTargetType(targetMask)) &&
                (platform->GetDamageLevel() <= 0))
			{
				MissionAircraftInfo info;
				info.id = id;
				info.name = airState->obj->mzUnit.c_str();
				
				float weaponWeight_kg = 0;
				float weaponMaxRange_km = 0;
				if (platform->RatingForTargetType(targetMask, weaponWeight_kg, weaponMaxRange_km))
				{
					info.rating = weaponWeight_kg + 20.0f * weaponMaxRange_km;
				}
				else
				{
					info.rating = 0;
				}


				availableAircraft.push_back(info);
			}
		}

	}

	std::sort(availableAircraft.begin(), availableAircraft.end(), MAIRatingSort);

	return availableAircraft;
}

unsigned int tcMissionManager::GetEditMissionId() const
{
    return editMissionId;
}

tcGameObject* tcMissionManager::GetFlightportParent()
{
	return flightPort->parent;
}

long tcMissionManager::GetFlightportParentId() const
{
	return flightPort->parent->mnID;
}

tcMission* tcMissionManager::GetMission(unsigned int id)
{
    for (size_t n=0; n<missions.size(); n++)
	{
        if (missions[n]->GetId() == id)
        {
            return missions[n];
        }
    }

    return 0;
}

/**
* @returns mission at specified index or 0 if out of range
*/
tcMission* tcMissionManager::GetMissionByIdx(unsigned int idx)
{
    if (idx < missions.size())
	{
        return missions[idx];
    }
    else
    {
        return 0;
    }
}

size_t tcMissionManager::GetMissionCount() const
{
    return missions.size();
}

bool tcMissionManager::IsAircraftReserved(long id) const
{
	std::map<long, unsigned int>::const_iterator iter =
		reserved.find(id);

	return (iter != reserved.end());
}

void tcMissionManager::LaunchAircraft(long id)
{
	flightPort->LaunchID(id);
}


/**
* Called internally to perform queued deletions
*/
void tcMissionManager::PerformDeletions()
{
	if (missionsToDelete.size() == 0) return;

	std::vector<tcMission*> temp;

	for (size_t n=0; n<missions.size(); n++)
	{
		unsigned int missionId = missions[n]->GetId();
		bool deleteMatch = false;
		for (size_t k=0; (k<missionsToDelete.size()) && (!deleteMatch); k++)
		{
			if (missionsToDelete[k] == missionId) deleteMatch = true;
		}
		
		if (!deleteMatch)
		{
			temp.push_back(missions[n]);
		}
		else
		{
			delete missions[n];
            if (missionId == editMissionId) editMissionId = 0;
		}
	}

	missions = temp;
}

void tcMissionManager::SaveToPython(scriptinterface::tcScenarioLogger& logger)
{
    wxString s;

    s.Printf("FP = UI.GetFlightPortInfo()");
    logger.AddScenarioText(s);

    logger.AddScenarioText("base_track = UI.GetTrackById(UI.GetPlatformId())");

	wxASSERT(flightPort->parent != 0);
    float lon_rad = flightPort->parent->mcKin.mfLon_rad;
    float lat_rad = flightPort->parent->mcKin.mfLat_rad;

    for (size_t n=0; n<missions.size(); n++)
	{
		if (tcCAPMission* cap = dynamic_cast<tcCAPMission*>(missions[n]))
        {
            tcPoint station = cap->GetStation();
            s.Printf("FP.AddCAPMission(base_track.Lon + %f, base_track.Lat + %f)", 
                station.x - lon_rad, station.y - lat_rad);
            logger.AddScenarioText(s);
        }
        else if (tcAttackMission* attack = dynamic_cast<tcAttackMission*>(missions[n]))
        {
            attack->SaveToPython(logger);
        }
	}
}


void tcMissionManager::SetEditMissionId(unsigned int id)
{
    if (tcMission* mission = GetMission(id))
    {
        editMissionId = id;
    }
    else
    {
        editMissionId = 0;
    }
}


void tcMissionManager::Update(double t)
{
    if (tcGameObject::IsEditMode())
    {
        PerformDeletions();
        UpdateReserved();
        return;
    }

    if ((t - lastUpdate) < 1.0f) return;

	lastUpdate = t;

	for (size_t n=0; n<missions.size(); n++)
	{
		missions[n]->Update(t);
	}

	PerformDeletions();

	UpdateReserved();
}

void tcMissionManager::UpdateReserved()
{
	reserved.clear();
    reserved2.clear();

	for (size_t n=0; n<missions.size(); n++)
	{
		const std::vector<MissionAircraftInfo>& missionAircraft = missions[n]->GetMissionAircraft();
		unsigned int missionId = missions[n]->GetId();
		
		for (size_t k=0; k<missionAircraft.size(); k++)
		{
			reserved[missionAircraft[k].id] = missionId;
            reserved2[missionAircraft[k].name] = missionId;
		}
	}
}


tcMissionManager::tcMissionManager(tcFlightPort* fp)
: flightPort(fp),
  lastUpdate(randf()),
  editMissionId(0)
{
	wxASSERT(fp != 0);

}


tcMissionManager::~tcMissionManager() 
{
	for (size_t n=0; n<missions.size(); n++)
	{
		delete missions[n];
	}
}