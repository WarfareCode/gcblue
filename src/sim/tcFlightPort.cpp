/** 
**  @file tcFlightport.cpp 
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
#endif

#include "tcFlightPort.h"
#include "tcAirObject.h"
#include "tcAeroAirObject.h"
#include "tcHeloObject.h"
#include "tcAirDBObject.h"
#include "tcFlightportDBObject.h"
#include "tcPlatformDBObject.h"
#include "tcCarrierObject.h"
#include "ai/BlackboardInterface.h"
#include "ai/Brain.h"
#include "ai/Task.h"
#include "common/tcStream.h"
#include "common/tcObjStream.h"
#include "common/tcGameStream.h"
#include "tcPlatformObject.h"
#include "tcLauncher.h"
#include "ai/tcMissionManager.h"
#include "tcTime.h"
#include "tcFloatCompressor.h"
#include "tcOptions.h"
#include "scriptinterface/tcPlatformInterface.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/**
*   case HANGAR: return "Hangr";
*   case ALERT15: return "Deck";
*   case ALERT5: return "Runwy";
*   case TRANSIT: return "Trans";
*   default: return "Error";
*/
std::string tcAirState::LocationToString(teLocation loc)
{
    switch (loc) 
    {
    case HANGAR: return "Hangr";
    case ALERT15: return "AL15";
    case ALERT5: return "AL05";
    case PRETAKEOFF: return "PTO";
    case TAKEOFF: return "TO";
    default: return "Error";
    }
}

/**
*   case OP_NONE: return "None";
*   case OP_TRANSIT: return "Transit";
*   case OP_UNLOAD: return "Unload";
*   case OP_LOAD: return "Load";
*   case OP_REPAIR: return "Repair";
*   case OP_MAINTENANCE: return "Maint";
*   default: return "Error";
*/
std::string tcAirState::OperationToString(teOperation op)
{   
    switch (op)
    {
    case OP_NONE: return "None";
    case OP_TRANSIT: return "Transit";
    case OP_UNLOAD: return "Unload";
    case OP_LOAD: return "Load";
    case OP_REPAIR: return "Repair";
    case OP_MAINTENANCE: return "Maint";
    default: return "Error";
    }
}

/**
* Loads state from update stream
*/
tcUpdateStream& tcAirState::operator<<(tcUpdateStream& stream)
{
    bool detailedUpdate = (stream.GetDetailLevel() > 0);
    
    char val;

	stream >> val;
	current_location = (teLocation)val;
	
	stream >> val;
	current_spot = val;

	stream >> val;
	goal_location = (teLocation)val;

	stream >> val;
	goal_spot = val;

	stream >> val;
	op = (teOperation)val;

	float x;
	stream >> tcIntervalCompressor(x, 0.0f, 6500.0f);
	ready_time = x;
	
	// if this obj is in a ready or launch spot, then update launcher and fuel state
    if (detailedUpdate || (current_location != HANGAR))
    {
        if (tcPlatformObject* platform = obj)
        {
            size_t nLaunchers = platform->GetLauncherCount();
            for (size_t n=0; n<nLaunchers; n++)
            {
                tcLauncher* launcher = platform->GetLauncher(n);
                launcher->operator<<(stream);

                unsigned char isLoading;
                stream >> isLoading;
                launcher->SetLoadState(isLoading != 0);
            }
            float fuel;
            stream >> tcIntervalCompressor(fuel, 0.0f, 655350.0f);
            platform->fuel_kg = fuel;

            char isRefueling;
            stream >> isRefueling;
            platform->SetRefueling(isRefueling != 0);
        }
    }



	return stream;
}

/**
* Saves state to update stream
*/
tcUpdateStream& tcAirState::operator>>(tcUpdateStream& stream)
{
    bool detailedUpdate = (stream.GetDetailLevel() > 0);

    //if (detailedUpdate)
    //{
    //    int jj = 55;
    //}

	char val;

	val = (char)current_location;
	stream << val;

	val = ((char)current_spot);
	stream << val;

	val = ((char)goal_location);
	stream << val;

	val = ((char)goal_spot);
	stream << val;

	val = ((char)op);
	stream << val;

	float x = (float)ready_time;
	stream << tcIntervalCompressor(x, 0.0f, 6500.0f);
	
    if (detailedUpdate || (current_location != HANGAR))
    {
        if (tcPlatformObject* platform = obj)
        {
            size_t nLaunchers = platform->GetLauncherCount();
            for (size_t n=0; n<nLaunchers; n++)
            {
                tcLauncher* launcher = platform->GetLauncher(n);
                launcher->operator>>(stream);

                // additional info that we don't want part of the normal launcher update (could use detail level instead)
                unsigned char isLoading = launcher->IsLoading() ? 1 : 0;
                stream << isLoading;
            }
            float fuel = platform->fuel_kg;
            stream << tcIntervalCompressor(fuel, 0.0f, 655350.0f);

            char isRefueling = platform->IsRefueling() ? 1 : 0;
            stream << isRefueling;
            platform->SetRefueling(isRefueling != 0);
        }
    }


	return stream;
}


/**
* Loads state from game stream
*/
tcGameStream& tcAirState::operator<<(tcGameStream& stream)
{
	char val;

	stream >> val;
    current_location = teLocation(val);

    stream >> val;
	current_spot = int(val);

    stream >> val;
    goal_location = teLocation(val);

    stream >> val;
	goal_spot = int(val);

    stream >> inTransit;

    stream >> val;
    op = teOperation(val);

	stream >> ready_time;

	return stream;
}

/**
* Saves state to game stream
*/
tcGameStream& tcAirState::operator>>(tcGameStream& stream)
{
	char val;

	val = (char)current_location;
	stream << val;

	val = ((char)current_spot);
	stream << val;

	val = ((char)goal_location);
	stream << val;

	val = ((char)goal_spot);
	stream << val;

    stream << inTransit;

	val = ((char)op);
	stream << val;

	stream << ready_time;


	return stream;
}


float tcFlightPort::transitionTimesFast[6][6];
float tcFlightPort::transitionTimesNormal[6][6];


void tcFlightPort::InitTransitionTimes()
{
    for (int m=0; m<6; m++)
    {
        for (int n=0; n<6; n++)
        {
            transitionTimesFast[m][n] = 0;
            transitionTimesNormal[m][n] = 0;
        }
    }

   /*
   NOWHERE = 0,
   HANGAR = 1,   ///< longer term storage or repair
   ALERT15 = 2,    ///< out of hangar, on deck
   ALERT5 = 3,   ///< ready to take off
   PRETAKEOFF = 4, ///< a hack to get a/c to stay in launch spot but take some time to takeoff
   TAKEOFF = 5   ///< move to launch and take off
   */
   transitionTimesFast[HANGAR][ALERT15] = 60.0f;
   transitionTimesFast[HANGAR][ALERT5] = 120.0f;
   transitionTimesFast[HANGAR][TAKEOFF] = 180.0f;
   transitionTimesFast[ALERT15][ALERT5] = 60.0f;
   transitionTimesFast[ALERT15][TAKEOFF] = 120.0f;
   // these are all the same state transitions (why?? 23AUG2009)
   transitionTimesFast[ALERT5][PRETAKEOFF] = 60.0f;
   transitionTimesFast[PRETAKEOFF][TAKEOFF] = 60.0f;
   transitionTimesFast[ALERT5][TAKEOFF] = 60.0f; 

   transitionTimesNormal[HANGAR][ALERT15] = 900.0f; // 15 min to move from "hangar" to ready (alert30 to alert15)
   transitionTimesNormal[HANGAR][ALERT5] = 1500.0f;
   transitionTimesNormal[HANGAR][TAKEOFF] = 1800.0f;
   transitionTimesNormal[ALERT15][ALERT5] = 600.0f; // alert15 to alert5
   transitionTimesNormal[ALERT15][TAKEOFF] = 900.0f;
   // these are all the same state transitions
   transitionTimesNormal[ALERT5][PRETAKEOFF] = 300.0f; // 5 minutes to takeoff from alert5
   transitionTimesNormal[PRETAKEOFF][TAKEOFF] = 300.0f; // 5 minutes to takeoff from alert5
   transitionTimesNormal[ALERT5][TAKEOFF] = 300.0f; // 5 minutes to takeoff from alert5



}

/**
* Loads state from update stream
* Objects that are not updated are deleted
*/
tcUpdateStream& tcFlightPort::operator<<(tcUpdateStream& stream)
{
	static tcAirState tempAirState;

    unsigned int updateTimestamp = tcTime::Get()->GetUpdated30HzCount();

	unsigned short nChildren = GetCount();

    unsigned char detailedUpdate;
    stream >> detailedUpdate;

    if (detailedUpdate == 1)
    {
        stream.SetDetailLevel(1);
    }
    else
    {
        stream.SetDetailLevel(0);
    }

	unsigned char nUpdate;	
	stream >> nUpdate;


	unsigned short updateIdx = 0;
	unsigned short childIdx = 0;
	unsigned nUpdated = 0;

	while ((updateIdx < nUpdate))
	{
		short int updateId;
		stream >> updateId;

		bool foundMatch = false;
		childIdx = 0;
		while ((!foundMatch) && (childIdx < nChildren))
		{
			tcAirState* airState = GetAirState(childIdx);
			tcGameObject* obj = airState->obj;
			wxASSERT(obj);

			short int childId = (short)obj->mnID;
			if (childId == updateId)
			{
				*airState << stream;
                airState->lastMultiplayerUpdate = updateTimestamp;

				foundMatch = true;
				nUpdated++;
			}
			childIdx++;
		}

        if (!foundMatch)
        {
            parent->SetRecreate(true); // request re-create
        }

		updateIdx++;
	}

	for ( ; updateIdx < nUpdate; updateIdx++)
	{
		tempAirState << stream;
	}


	ResyncSpots();

	/* request recreate if not all updates were matched (new child)
	** or if not all children were update (deleted child)
	** In future, would be more efficient to have messages to selectively add
	** and delete children vs. re-creating all of the children.
	*/
	//if ((nUpdated < nUpdate) || (nUpdated < nChildren))
	//{
	//	parent->SetRecreate(true);
	//}

	/*
	std::vector<tcAirState*>::iterator iter = units.begin();
	while (iter != units.end())
	{
		if ((*iter)->obj == 0)
		{
			units.erase(iter++);
		}
		else
		{
			++iter;
		}
	}
	*/

    return stream;
}

/**
* Saves state to update stream
* Do partial update if stream size limit is reached
*/
tcUpdateStream& tcFlightPort::operator>>(tcUpdateStream& stream)
{
    // if freeSpace < 0, the message should be rejected anyway so don't worry about special case
    // for this
    long freeSpace = stream.GetMaxSize() - stream.size() - 2; // 1 byte for update count header, 1 for detailedUpdate

    tcUpdateStream tempStream1;
    tcUpdateStream tempStream2;

    unsigned char detailedUpdate;
    if (stream.GetDetailLevel() > 0)
    {
        detailedUpdate = 1;
    }
    else
    {
        detailedUpdate = 0;
    }


    unsigned short nChildren = GetCount();
    if (nextUpdateIdx >= nChildren) nextUpdateIdx = 0;

    unsigned char nUpdates = 0;

	//stream << nChildren;

    while ((nextUpdateIdx < nChildren) && (freeSpace > 0))
	{
        tempStream1.clear();
        tempStream1.SetDetailLevel(stream.GetDetailLevel());

		tcAirState* airState = GetAirState(nextUpdateIdx);
		tcGameObject* obj = airState->obj;
		wxASSERT(obj);

		short int localId = (short int)obj->mnID;
		tempStream1 << localId;

        *airState >> tempStream1;

        if ((long)tempStream1.size() <= freeSpace)
        {
            tempStream2 << tempStream1;
            freeSpace -= tempStream1.size();
            nextUpdateIdx++;
            nUpdates++;
        }
        else
        {
            freeSpace = 0;
        }

    }

    stream << detailedUpdate;
    stream << nUpdates;

    stream << tempStream2;

    if (nextUpdateIdx >= nChildren)
    {
        nextUpdateIdx = 0;
        stream.SetDoneFlag(true);
    }
    else
    {
        stream.SetDoneFlag(false);
    }



    return stream;
}


/**
* Loads state from command stream
*/
tcCommandStream& tcFlightPort::operator<<(tcCommandStream& stream)
{
	unsigned char nCommands;
	stream >> nCommands;

	for (unsigned char n=0; n<nCommands; n++)
	{
		short int id;
		unsigned char op;
		unsigned char pos;

		stream >> id;
		stream >> op;
		stream >> pos;

		if (op == 0) // launch command
		{
			LaunchID(id);
		}
		else // search for matching id and set new destination
		{
			bool found = false;
			size_t obj_count = units.size();
			for (size_t n=0; (n<obj_count)&&(!found); n++)
			{
				tcAirState *airstate = units[n];
				if (airstate->obj->mnID == (long)id)
				{
					found = true;
					SetObjectDestination(n, (teLocation)op, pos);
				}
			}
		}
	}

    // load mission manager commands (always do this even if no commands)
    ai::tcMissionManager* mm = GetOrCreateMissionManager();
    return mm->operator<<(stream);
}

/**
* Saves state to command stream
*/
tcCommandStream& tcFlightPort::operator>>(tcCommandStream& stream)
{
	unsigned char nCommands = commandList.size();
	stream << nCommands;

	for (unsigned char n=0; n<nCommands; n++)
	{
		stream << commandList[n].id;
		stream << commandList[n].op;
		stream << commandList[n].pos;
	}

    // save mission manager commands (always do this even if no commands)
    ai::tcMissionManager* mm = GetOrCreateMissionManager();
    return mm->operator>>(stream);
}

/**
* Loads state from game stream
*/
tcGameStream& tcFlightPort::operator<<(tcGameStream& stream)
{
    wxASSERT(units.size() == 0);

    stream >> last_update_time;
    stream >> inHangarCount;
    stream >> localId;

    size_t nUnits = units.size();

    stream >> nUnits;

    for (size_t n=0; n<nUnits; n++)
    {
        long objId;
        stream >> objId;

        tcAirState* airstate = new tcAirState;

        airstate->lastMultiplayerUpdate = 0;

        tcAirObject* obj = dynamic_cast<tcAirObject*>(parent->GetChildById(objId));
        airstate->obj = obj;
        wxASSERT(obj != 0);
        
        airstate->operator<<(stream);

        units.push_back(airstate);

        // update spot (if pos not hangar)
        tsSpotInfo* spot = GetCurrentSpotInfo(airstate);
        if (spot != 0) spot->obj_info = airstate;
    }

    bool hasMissionManager;
    stream >> hasMissionManager;
    if (hasMissionManager)
    {
        missionManager = GetOrCreateMissionManager();
        missionManager->operator<<(stream);   
    }

    stream.ReadCheckValue(1278);

    return stream;
}

/**
* Saves state to game stream
*/
tcGameStream& tcFlightPort::operator>>(tcGameStream& stream)
{
    stream << last_update_time;
    stream << inHangarCount;
    stream << localId;

    size_t nUnits = units.size();

    stream << nUnits;

    for (size_t n=0; n<nUnits; n++)
    {
        stream << units[n]->obj->mnID;
        units[n]->operator>>(stream);
    }

    bool hasMissionManager = (missionManager != 0);
    stream << hasMissionManager;
    if (hasMissionManager)
    {
        missionManager->operator>>(stream);   
    }

    stream.WriteCheckValue(1278);

    return stream;
}






void tcFlightPort::ClearNewCommand()
{
	commandList.clear();

    if (missionManager != 0) missionManager->ClearNewCommand();
}

bool tcFlightPort::HasNewCommand() const
{
    bool missionManagerCommand = (missionManager != 0) && (missionManager->HasNewCommand());

	return (commandList.size() > 0) || missionManagerCommand;
}

/** 
* Adds obj to loc if available, otherwise adds to best available location.
* If no location is available (can't add) returns 0, otherwise 1.
* @param obj Game object to add.
* @param loc Desired location for obj.
* @param position Desired position for obj (e.g. which runway)
* @return 1 success, 0 failure
*/
int tcFlightPort::AddObject(tcAirObject *obj, teLocation loc, unsigned int position)
{
    std::vector<tsSpotInfo> *bestLocation = NULL;
    int emptySpotIdx = -1;

	// over-ride location if such location doesn't exist on this flightport
	if ((loc == HANGAR) && (inHangarCount >= hangarCapacity)) loc = ALERT15;
	if ((loc == ALERT15) && (ready_spots.size() == 0)) loc = ALERT5;

    if (loc == ALERT5)
    {
		if ((position < launch_spots.size()) && launch_spots[position].IsEmpty())
		{
			emptySpotIdx = (int)position;
		}
		else
		{
			emptySpotIdx = FindEmptySpot(&launch_spots);
		}
        if (emptySpotIdx >= 0)
            bestLocation = &launch_spots;
        else
            loc = ALERT15; // try ALERT15 if no free launch_spots
    }
    if (loc == ALERT15)
    {
		if ((position < ready_spots.size()) && ready_spots[position].IsEmpty())
		{
			emptySpotIdx = (int)position;
		}
		else
		{
			emptySpotIdx = FindEmptySpot(&ready_spots);
		}
        if (emptySpotIdx >= 0)
            bestLocation = &ready_spots;
        else
            loc = HANGAR; 
    }

    if ((loc == HANGAR)&&(inHangarCount >= hangarCapacity)) return 0;

    tcAirState *airstate = new tcAirState;
    airstate->obj = obj;
	airstate->obj->mnID = localId++; // assign local id
    airstate->op = OP_NONE;
    airstate->ready_time = last_update_time;
    airstate->current_location = loc;
    airstate->current_spot = emptySpotIdx;
    airstate->goal_location = loc;
    airstate->goal_spot = airstate->current_spot;
	airstate->inTransit = false;
    airstate->lastMultiplayerUpdate = tcTime::Get()->GetUpdated30HzCount();
    units.push_back(airstate); // add to fport units vector

    if (loc == HANGAR) inHangarCount++;
    if ((bestLocation != NULL)&&(emptySpotIdx >= 0))
    {
        tsSpotInfo *spot = &bestLocation->at(emptySpotIdx);
        spot->obj_info = airstate;
    }
    InitRelPos(airstate);
    return 1;
}
/**
* Add spot to flightport. 
*/
void tcFlightPort::AddSpot(teLocation loc, float x, float y, float z, 
                           float orientation, float length)
{
    tsSpotInfo spot;
    spot.x = x;
    spot.y = y;
    spot.z = z;
    spot.orientation = orientation;
    spot.length = length;
    spot.obj_info = NULL; // empty initially

    if (loc == ALERT5) {launch_spots.push_back(spot);return;}
    else if (loc == ALERT15) {ready_spots.push_back(spot);return;}
}

/**
* Determines if obj has landed on runway or crashed into flightport.
* If object successfully lands, it is added to the toLand queue.
* Landing criteria are very crude in this version. Anything close is
* considered landed. Crashes are not checked. Higher-level code is relied 
* on to check that the obj is decending.
* @param obj Object to attempt landing
* @return -1 if crash, 0 if not close enough for landing, 1 if landed
*/
int tcFlightPort::CheckLanding(tcAirObject *obj)
{
	tcAirObject* air = obj;
    bool isAir = (air != 0);
	//bool isHelo = dynamic_cast<tcHeloObject*>(air) != 0;
    bool isHelo = typeid(*air) == typeid(tcHeloObject);
	bool compatible = isAir && (!mpDBObject->heloOnly || isHelo);

    tcCarrierObject* carrier = dynamic_cast<tcCarrierObject*>(parent);
    bool carrierLanding = (carrier != 0);
    bool carrierCompatible = air->mpDBObject->IsCarrierCompatible();

    compatible = compatible && (!carrierLanding || carrierCompatible);

	if (!compatible) return 0;

    int nRunways = (int)launch_spots.size();
    for (int n=0;n<nRunways;n++)
    {
        tsSpotInfo *spot = &launch_spots.at(n);
        //float dx = obj->rel_pos.dx - spot->x;
        //float dy = obj->rel_pos.dy - spot->y;
        //float dz = obj->rel_pos.dz - spot->z;

        //if ((dx*dx + dz*dz <= 1600.0f)&&(dy < 25.0f)&&(dy > -25.0f))
        if ((spot->length >= air->mpDBObject->minimumRunway_m) || carrierLanding)
        {
			air->GetBrain()->RemoveAllTasks();
			air->SetLandingState(false); // retract landing gear
            toLand.push_back(obj);
            return 1;
        }
    }

    return 0;
}


void tcFlightPort::Clear() 
{
    size_t nSpots = units.size();
    for(size_t n=0;n<nSpots;n++) 
    {
        tcAirState *airstate = units.at(n);
		parent->RemoveChild(airstate->obj);
		delete airstate->obj;
        delete airstate;
    }
    units.clear();

	for (size_t n=0; n<toLaunch.size(); n++)
	{
		delete toLaunch[n];
	}
    toLaunch.clear();


	for (size_t n=0; n<toLand.size(); n++)
	{
		delete toLand[n];
	}
    toLand.clear();

	for (size_t n=0; n<ready_spots.size(); n++)
	{
		ready_spots[n].obj_info = 0;
	}

	for (size_t n=0; n<launch_spots.size(); n++)
	{
		launch_spots[n].obj_info = 0;
	}

    inHangarCount = 0;

    last_update_time = 0;

	if (missionManager != 0)
	{
		delete missionManager;
		missionManager = 0;
	}

    nextUpdateIdx = 0;
}

/**
 * Search units vector and return matching index. Return -1 if not found.
 */
int tcFlightPort::FindAirState(tcAirState *airstate)
{
    size_t nUnits = units.size();
    for(size_t n=0;n<nUnits;n++) 
    {
        tcAirState* airstate_n = units.at(n);
        if (airstate_n == airstate) return (int)n;
    }
    return -1; // not found
}

/**
 * Searches loc for empty spot returns spot index if found,
 * otherwise returns -1.
 */
int tcFlightPort::FindEmptySpot(std::vector<tsSpotInfo> *loc_vector)
{
    size_t nSpots = loc_vector->size();
    for(size_t n=0;n<nSpots;n++) 
    {
        tsSpotInfo *spot = &loc_vector->at(n);
        if (spot->obj_info == NULL) return (int)n;
    }
    return -1;
}

/**
 * Searches for empty spot at loc and returns spot index if found,
 * otherwise returns -1.
 */
int tcFlightPort::FindEmptySpot(teLocation loc, std::vector<tsSpotInfo>*& loc_vector)
{
    loc_vector = GetLocVector(loc);
    if (loc == HANGAR) return (inHangarCount >= hangarCapacity) ? -1 : 0;
    if ((loc == TAKEOFF)||(loc == NOWHERE)) return -1; // error
   
    return FindEmptySpot(loc_vector);   
}

/**
* Search (linear) units vector for obj
* @return index with matching obj or -1 if not found.
*/
int tcFlightPort::FindAirState(tcGameObject* obj)
{
	wxASSERT(obj);

	size_t nUnits = units.size();
    for(size_t n=0; n<nUnits; n++) 
    {
        tcAirState* airstate_n = units[n];
		if (airstate_n->obj == obj) return (int)n;
    }
    return -1; // not found
}

/**
* Search (linear) units vector for obj
* @return tcAirState ptr for matching obj or 0 if not found.
*/
tcAirState* tcFlightPort::FindAirStateObj(tcGameObject* obj)
{
	wxASSERT(obj);

	size_t nUnits = units.size();
    for(size_t n=0; n<nUnits; n++) 
    {
        tcAirState* airstate_n = units[n];
		if (airstate_n->obj == obj) return airstate_n;
    }
    return 0; // not found
}

/**
* Search (linear) units vector for obj
* @return tcAirState ptr for matching obj or 0 if not found.
*/
const tcAirState* tcFlightPort::FindAirStateObj(const tcGameObject* obj) const
{
	wxASSERT(obj);

	size_t nUnits = units.size();
    for(size_t n=0; n<nUnits; n++) 
    {
        const tcAirState* airstate_n = units[n];
		if (airstate_n->obj == obj) return airstate_n;
    }
    return 0; // not found
}


tcAirState* tcFlightPort::GetAirState(unsigned n)
{
	return units[n];
}

const tcAirState* tcFlightPort::GetAirState(unsigned n) const
{
	return units[n];
}

int tcFlightPort::GetAirStateIdx(long id) const
{
    size_t nUnits = units.size();
    for(size_t n=0;n<nUnits;n++) 
    {
        tcAirState* airstate = units.at(n);
        if (airstate->obj->mnID == id) return (int)n;
    }
    return -1; // not found
}

tcFlightportDBObject* tcFlightPort::GetDatabaseObject() const
{
    return mpDBObject;
}

/**
* @returns game object for unit with index n
*/
tcGameObject* tcFlightPort::GetObject(unsigned n)
{
	wxASSERT(n < units.size());

	return units[n]->obj;
}

/**
* @return game object for unit with matching id
*/
tcGameObject* tcFlightPort::GetObjectById(long id)
{
	int idx = GetAirStateIdx(id);
	if (idx < 0) return 0;
	return GetObject(unsigned(idx));
}

tcGameObject* tcFlightPort::GetObjectByName(const std::string& unitName)
{
    size_t nUnits = units.size();
    for (size_t n=0; n<nUnits; n++) 
    {
        tcAirState* airstate = units[n];
        if ((airstate->obj != 0) && (airstate->obj->mzUnit == unitName.c_str()))
        {
            return airstate->obj;
        }
    }
    return 0;
}

/**
* @return length of longest runway in meters
*/
float tcFlightPort::GetMaxRunwayLength() const
{
    float maxRunway_m = 0;
	for (size_t n=0; n<launch_spots.size(); n++)
	{
        maxRunway_m = std::max(maxRunway_m, launch_spots[n].length);
	}
    return maxRunway_m;
}

ai::tcMissionManager* tcFlightPort::GetMissionManager()
{
	return missionManager;
}

ai::tcMissionManager* tcFlightPort::GetOrCreateMissionManager()
{
	if (missionManager == 0)
	{
        missionManager = new ai::tcMissionManager(this);
	}
	
	return missionManager;
}

/**
* @return time in seconds
* For displaying status to player. Show time to move to ultimate destination.
* Or for maintenance or load/unload, show time until operation is done
*/
float tcFlightPort::GetTimeToDestination(const tcAirState* airstate) const
{
    wxASSERT(airstate != 0);

    float ready_s = airstate->ready_time - last_update_time;

    if ((airstate->op == OP_MAINTENANCE) || (airstate->op == OP_REPAIR))
    {
        return ready_s;
    }

    ready_s = std::max(ready_s, 0.0f);
    if (airstate->goal_location != airstate->current_location)
    {
        if (tcOptions::Get()->fastAircraftReady != 0)
        {
            ready_s += transitionTimesFast[airstate->current_location][airstate->goal_location];
            
            if ((!airstate->inTransit) || (airstate->current_location == PRETAKEOFF))
            {
                teLocation nextStop = GetNextStop(airstate->current_location, airstate->goal_location);
                if (nextStop > 0) 
                {
                    ready_s -= transitionTimesFast[airstate->current_location][nextStop];
                }
            }           
        }
        else
        {
            ready_s += transitionTimesNormal[airstate->current_location][airstate->goal_location];

            if ((!airstate->inTransit) || (airstate->current_location == PRETAKEOFF))
            {
                teLocation nextStop = GetNextStop(airstate->current_location, airstate->goal_location);
                if (nextStop > 0) 
                {
                    ready_s -= transitionTimesNormal[airstate->current_location][nextStop];
                }
            }
        }
        
    }

    return ready_s;
}

const wxString& tcFlightPort::GetTimeToDestinationString(const tcAirState* airstate) const
{
    static wxString readyTimeString;
    readyTimeString.clear();

    long ready_s = long(GetTimeToDestination(airstate) + 0.5f);
    if (ready_s > 0)
    {
	    long hours = ready_s / 3600;
        long min = (ready_s - 3600*hours)/60;
        long sec = ready_s % 60;
        
        if (ready_s > 59)
        {
            readyTimeString.Printf(" %02d:%02d", hours, min);
        }
        else
        {
            readyTimeString.Printf(" %02ds", sec);
        }

        switch (airstate->goal_location)
        {
        case HANGAR:
            readyTimeString += " -";
            break;
        case ALERT15:
            readyTimeString += " R15";
            break;
        case ALERT5:
            readyTimeString += " R5";
            break;
        case PRETAKEOFF:
        case TAKEOFF:
            readyTimeString += " L";
            break;
        }
    }
    else
    {
        return readyTimeString; // empty string
    }

    if ((airstate->op == OP_MAINTENANCE) || (airstate->op == OP_REPAIR))
    {
        readyTimeString += "*";
    }
    else if (!airstate->inTransit)
    {
        readyTimeString += "!";
    }

    return readyTimeString;
}


int tcFlightPort::LaunchAirstate(tcAirState* airstate)
{
    if (airstate == NULL) return 0; // not found on runway

	if (parent->IsClientMode())
	{
		CommandInfo cmd;
		cmd.id = (unsigned short)airstate->obj->mnID;
		cmd.op = 0;
		commandList.push_back(cmd);
		return 1;
	}

    bool notReady = (airstate->ready_time > last_update_time);
    bool damaged = (airstate->obj->GetDamageLevel() > maxTakeoffDamage);

    if (airstate->current_location != PRETAKEOFF)
    {
        SetObjectDestination(airstate, TAKEOFF, 0);
        return 0;
    }

	if (notReady || damaged)
	{
		if (damaged) // added this 2APR2011 to keep aircraft from getting stuck launching after damaged
		{
			airstate->current_location = ALERT5;
			SetObjectDestination(airstate, HANGAR, 0);
		}
		return 0; // not ready yet or damaged, do not allow takeoff
	}
    
    tcAirObject* air = airstate->obj;
    if (air == 0)
    {
        fprintf(stderr, "tcFlightPort::Launch -- tried to launch non-air object\n");
        wxASSERT(false);
        return 0;
    }

    if (air->IsOverweight())
    {
        if (airstate->goal_location == TAKEOFF) // dequeue for takeoff
        {
            airstate->goal_location = ALERT5;
            airstate->goal_spot = airstate->current_spot;
        }
        return 0; // too heavy to launch
    }

    MoveToLaunchQueue(airstate);

    tsSpotInfo* spotInfo = GetCurrentSpotInfo(airstate);
    if (spotInfo != 0)
    {
        spotInfo->obj_info = 0; // set spot empty
    }
    return 1;
}

int tcFlightPort::LaunchRunway(int runway)
{
    int nRunways = (int)launch_spots.size();
    if ((runway < 0)||(runway >= nRunways)) return 0;

    tsSpotInfo *spot = &launch_spots[runway];

    tcAirState* airstate = spot->obj_info;

    return LaunchAirstate(airstate);
}

/// Find runway that object with id is on
int tcFlightPort::LaunchID(long id)
{
	if (parent->IsClientMode())
	{
		CommandInfo cmd;
		cmd.id = id;
		cmd.op = 0;
		commandList.push_back(cmd);
		return 1;
	}

  //  size_t nSpots = launch_spots.size();
  //  for (size_t n=0;n<nSpots;n++) 
  //  {
  //      tsSpotInfo *spot = &launch_spots.at(n);
		//if ((spot->obj_info != 0) && (spot->obj_info->obj != 0) && 
		//	(spot->obj_info->obj->mnID == id))
  //      {
		//	bool isReady = (spot->obj_info->ready_time <= last_update_time);
		//	if (isReady)
		//	{
		//		Launch((int)n);
		//		return 1;
		//	}
		//	else
		//	{
		//		return 0;
		//	}
  //      }
  //  }

	// queue for takeoff by moving to TAKEOFF destination
	int idx = GetAirStateIdx(id);
	if (idx >= 0)
	{
		tcAirState* airState = GetAirState(idx);
		if (airState != 0)
		{
			SetObjectDestination(airState, TAKEOFF, 0);
			return 1;
		}
	}


    fprintf(stderr, "tcFlightPort::LaunchID - Bad air state (id:%d)\n", id);
	//wxASSERT(false);
	return 0;

}

/**
 * Move object to new location if valid. Remove object from old location. 
 */
void tcFlightPort::MoveObjectToDestination(tcAirState *airstate, teLocation destination, int spot)
{
    if (spot == -1) return; // no valid goal spot yet
    if (airstate->current_location == destination) return; // no need to move (may need spot move in future)
    if (airstate->inTransit) return; // already moving, error

	wxASSERT(destination != TAKEOFF);
    if (destination == HANGAR) inHangarCount++;

    if (destination == PRETAKEOFF)
    {
        wxASSERT(airstate->current_location == ALERT5);
        airstate->current_location = PRETAKEOFF;
        airstate->inTransit = true;
        return; // no need to move between loc vectors, since is virtual loc and should already be in ALERT5
    }

    std::vector<tsSpotInfo>* current_loc_vect = GetLocVector(airstate->current_location);
    std::vector<tsSpotInfo>* dest_loc_vect = GetLocVector(destination);
    
    if (current_loc_vect)
    {
        tsSpotInfo& current_spot = current_loc_vect->at(airstate->current_spot);
        current_spot.obj_info = NULL; // remove from current spot
    }
    if (dest_loc_vect)
    {
        tsSpotInfo& dest_spot = dest_loc_vect->at(spot);
        dest_spot.obj_info = airstate; // add to dest spot
    }

    airstate->current_location = destination;
    airstate->current_spot = spot;

	airstate->inTransit = true;

    airstate->op = OP_TRANSIT;
}
/**
 * Find airstate in units vector. Add tcGameObject* to toLaunch vector. 
 * Remove airstate from units vector.
 */
bool tcFlightPort::MoveToLaunchQueue(tcAirState *airstate)
{
    int unit_idx = FindAirState(airstate);
    if (unit_idx == -1) return false; // error not found
    UpdateUnitKin(airstate);
    toLaunch.push_back(airstate->obj);
    // delete launched element and move last element into its place
    tcAirState*& launched = units.at(unit_idx);
    delete launched;
    tcAirState *back = units.back();
    launched = back;
    units.pop_back(); // remove last element
    return true;
}

/**
* Remove units that are marked destroyed from the flight deck
*/
void tcFlightPort::RemoveDestroyedUnits()
{
    size_t nUnits = units.size();
    std::vector<tcAirState*> temp;

    for (size_t n=0; n<nUnits; n++)
    {
        if (!units[n]->obj->IsDestroyed())
        {
            temp.push_back(units[n]);
        }
        else
        {
            parent->RemoveChild(units[n]->obj);
            delete(units[n]->obj);
            delete units[n];
        }
    }

    units = temp;

    ResyncSpots();
}

/**
* For multiplayer client
*/
void tcFlightPort::RemoveStaleUnits()
{
    unsigned int t = tcTime::Get()->GetUpdated30HzCount();


    int minTimeLag = 999;
    int maxTimeLag = 0;

    size_t nUnits = units.size();
    for (size_t n=0; n<nUnits; n++)
    {
        int lag = t - units[n]->lastMultiplayerUpdate;
        if (lag < minTimeLag) minTimeLag = lag;
        else if (lag > maxTimeLag) maxTimeLag = lag;
    }

    // remove units with lastMultiplayerUpdate more than 3 seconds
    // older than latest update
    int lagThresh = minTimeLag + 90;
    std::vector<tcAirState*> temp;

    for (size_t n=0; n<nUnits; n++)
    {
        int lag = t - units[n]->lastMultiplayerUpdate;
        if (lag <= lagThresh)
        {
            temp.push_back(units[n]);
        }
        else
        {
            parent->RemoveChild(units[n]->obj);
            delete(units[n]->obj);
            delete units[n];
        }
    }

    units = temp;

    ResyncSpots();
}

/**
 * @return pointer to tsSpotInfo for current location and spot.
 */
tsSpotInfo* tcFlightPort::GetCurrentSpotInfo(tcAirState *airstate)
{
    std::vector<tsSpotInfo>* loc_vect = GetLocVector(airstate->current_location);
    if (loc_vect == NULL) return NULL;
    int spot_idx = airstate->current_spot;
    if ((spot_idx < 0)||(spot_idx >= (int)loc_vect->size())) return NULL; // error, bad spot idx
    return &loc_vect->at(spot_idx);
}

/**
* This version returns info for the first runway spot only
*
* @return track with landing point coord and heading with orientation 
*/
tcTrack tcFlightPort::GetLandingData(const tcGameObject* obj)
{
	tcTrack data;

    int nRunways = (int)launch_spots.size();

	if (nRunways > 0)
	{
		tsSpotInfo *spot = &launch_spots.at(0);

		wxASSERT(obj);
		GeoPoint p = obj->RelPosToLatLonAlt(spot->x, spot->y, spot->z);

		data.mfLat_rad = p.mfLat_rad;
		data.mfLon_rad = p.mfLon_rad;
		data.mfAlt_m = p.mfAlt_m;
		data.mfHeading_rad = spot->orientation + obj->mcKin.mfHeading_rad;
		if (data.mfHeading_rad >= C_PI) data.mfHeading_rad -= C_TWOPI;
		else if (data.mfHeading_rad < -C_PI) data.mfHeading_rad += C_TWOPI;
		
		data.mnID = obj->mnID;

		return data;
	}
	else
	{
		data.mnID = -1;
		return data;
	}

}

/**
 * @return location vector corresponding to loc, or NULL if loc = HANGAR, TRANSIT, or NOWHERE.
 */
std::vector<tsSpotInfo>* tcFlightPort::GetLocVector(teLocation loc)
{
    switch (loc)
    {
    case HANGAR: return NULL; break;
    case ALERT15: return &ready_spots; break;
    case ALERT5: return &launch_spots; break;
    case PRETAKEOFF: return &launch_spots; break;
    default: return NULL; break;
    }
}

/**
* Initialize flightport using data in dbObj.
*/
void tcFlightPort::InitFromDatabase(database::tcFlightportDBObject *dbObj)
{
    wxASSERT(dbObj);

    Clear();

	mpDBObject = dbObj;

    hangarCapacity = mpDBObject->hangarCapacity;
    inHangarCount = 0;
	
    size_t nSpots = dbObj->spotInfo.size();
    for(size_t spot=0;spot<nSpots;spot++)
    {
        tcFlightportDBObject::spotDBInfo info = dbObj->spotInfo[spot];

        teLocation loc = (info.isLaunch) ? ALERT5 : ALERT15;
        AddSpot(loc, info.x, info.y, info.z, C_PIOVER180*info.orientation_deg, info.length);
    }

}

/**
* Set unit position and orientation to match that of current spot.
* Set visible to false if in hangar, otherwise true. This should be called
* once during initialization. Additional calls can be used to handle non-animated
* movement. Eventually UpdateRelPos should handle all of the movement after init.
*/
void tcFlightPort::InitRelPos(tcAirState *airstate)
{
    tcGameObject *pGameObj = airstate->obj;
    if ((airstate->current_location == HANGAR)||(airstate->current_location == ALERT15))
    {
        pGameObj->SetRelativePosition(0,0,0);
        pGameObj->SetVisible(false);
        return;
    }
    pGameObj->SetVisible(true);

    tsSpotInfo *spotinfo = GetCurrentSpotInfo(airstate);
    if (spotinfo == NULL) return; // error

    pGameObj->SetRelativePosition(spotinfo->x,spotinfo->y,spotinfo->z);
    pGameObj->SetRelativeOrientation(C_PIOVER180*spotinfo->orientation, 0, 0);
}

/**
* @return true if all launch spots are heloOnly
*/
bool tcFlightPort::IsHeloOnly() const
{
	return mpDBObject->heloOnly != 0;
}

/**
* @return true if unit matching id is queued for takeoff 
* (goal loc == TAKEOFF)
*/
bool tcFlightPort::IsQueuedForTakeoff(long id) const
{
	int idx = GetAirStateIdx(id);
	if (idx < 0) return false;

    const tcAirState* airState = GetAirState((unsigned)idx);
	if (airState != 0)
	{
		return (airState->goal_location == TAKEOFF);
	}
	else
	{
		wxASSERT(false);
		return false;
	}
}

/**
* Use to check status of specific spot, e.g. runway 1
* @return true if spot is empty, hangar spot is empty if hangar is not full
*/
bool tcFlightPort::IsSpotEmpty(teLocation loc, unsigned int spot)
{
    if (loc == HANGAR) return (inHangarCount < hangarCapacity);

    if (loc == PRETAKEOFF) return true;

	std::vector<tsSpotInfo>* loc_vector = GetLocVector(loc);

    if ((loc == NOWHERE)||(loc == TAKEOFF))
	{
		wxASSERT(false);
		return false; // error
	}
   
	if (spot >= loc_vector->size()) return false;

	return ((*loc_vector)[spot].obj_info == 0);
}

/**
* Workaround for multiplayer client. 
* This clears spot info and reassigns units to spots based on the info in airstate
*/
void tcFlightPort::ResyncSpots()
{
	// first clear the obj_info in each ready and launch spot
	for (size_t n=0; n<ready_spots.size(); n++)
	{
		ready_spots[n].obj_info = 0;
	}

	for (size_t n=0; n<launch_spots.size(); n++)
	{
		launch_spots[n].obj_info = 0;
	}

    inHangarCount = 0;

	for (size_t n=0; n<units.size(); n++)
	{
		tcAirState* airstate = units[n];
		if (airstate->current_location == HANGAR)
		{
            inHangarCount++;
		}
		else if (airstate->current_location == ALERT15)
		{
			if ((airstate->current_spot >= 0) && ((unsigned)airstate->current_spot < ready_spots.size()))
			{
				ready_spots[airstate->current_spot].obj_info = airstate;
			}
		}
		else if ((airstate->current_location == ALERT5) || (airstate->current_location == PRETAKEOFF))
		{
			if ((airstate->current_spot >= 0) && ((unsigned)airstate->current_spot < launch_spots.size()))
			{
				launch_spots[airstate->current_spot].obj_info = airstate;
			}
		}
	}
}

/**
* 
*/
void tcFlightPort::SetObjectDestination(unsigned n, teLocation loc, unsigned int position)
{
    if (n >= (unsigned)units.size()) return; // error, out of range
    tcAirState* airstate = units.at(n);
    
	SetObjectDestination(airstate, loc, position);
}

/**
* 
*/
void tcFlightPort::SetObjectDestination(tcAirState* airstate, teLocation loc, unsigned int position)
{
	wxASSERT(airstate != 0);

    teLocation currentLoc = airstate->current_location;
    bool validMove = false;
    
	validMove = (currentLoc != loc);

	/*
    if (loc == HANGAR)
    {
        validMove = (currentLoc == ALERT15);
    }
    else if (loc == ALERT15)
    {
        validMove = (currentLoc == ALERT15) || (currentLoc == HANGAR) ||
                    (currentLoc == ALERT5);
    }
    else if (loc == ALERT5)
    {
        validMove = (currentLoc == ALERT15);
    }
    
	*/
    if (!validMove) return;

    if ((loc == TAKEOFF) && (airstate->current_location == PRETAKEOFF))
    {
        LaunchAirstate(airstate);
        return;
    }
    
    airstate->goal_location = loc;
	airstate->goal_spot = position;

    if (parent->IsClientMode())
	{
		CommandInfo cmd;
		cmd.id = (short int)airstate->obj->mnID;
		cmd.op = loc;
		cmd.pos = position;
		commandList.push_back(cmd);
		return;
	}
}


void tcFlightPort::UpdateRelPos(tcAirState *airstate, double time)
{
//    tcGameObject *pGameObj = airstate->obj;
    if (airstate->inTransit)
    {
        if (time >= airstate->ready_time) 
		{
			if (airstate->current_location == HANGAR) inHangarCount--;
			if (airstate->goal_location == HANGAR) inHangarCount++;

            airstate->op = OP_NONE;
			airstate->inTransit = false;

			
			wxASSERT(inHangarCount <= hangarCapacity);

            InitRelPos(airstate);
        }
    }
}

/**
* Update the kinematics of entities in launch queue. Called once
* when moving to launch queue.
*/
void tcFlightPort::UpdateUnitKin(tcAirState *airstate)
{
    tcAirObject* air_unit = airstate->obj;
    if (air_unit == NULL) return; // error
    tcGameObject* parent = air_unit->parent;
    if (parent == NULL) return; // error

    air_unit->mcKin = parent->mcKin;
    air_unit->mcKin.mfHeading_rad += air_unit->rel_pos.yaw;
    air_unit->mcKin.mfAlt_m += air_unit->rel_pos.dz;
    air_unit->SetHeading(air_unit->mcKin.mfHeading_rad);
    air_unit->mfStatusTime = parent->mfStatusTime;

    GeoPoint childPos = parent->RelPosToLatLonAlt(air_unit->rel_pos);
    air_unit->mcKin.mfAlt_m = childPos.mfAlt_m;
    air_unit->mcKin.mfLat_rad = childPos.mfLat_rad;
    air_unit->mcKin.mfLon_rad = childPos.mfLon_rad;

    if (air_unit == 0)
    {
        wxASSERT(false);
        return;
    }



	// write base name to unit blackboard to allow it to RTB when mission complete
    ai::Brain* brain = air_unit->GetBrain();
    wxASSERT(brain);
    ai::BlackboardInterface bb = brain->GetBlackboardInterface();

    bb.Write("Home", parent->mzUnit.c_str());


    if (tcAeroAirObject* aa_unit = dynamic_cast<tcAeroAirObject*>(air_unit))
    {
		aa_unit->mcKin.mfSpeed_kts += 200.0f;
        aa_unit->SetThrottleFraction(1.1f);
        aa_unit->SetAltitude(air_unit->mcKin.mfAlt_m + 500.0f);
        aa_unit->SetLandingState(0); 
        brain->AddTask("JetTakeoff", 2.0f);

    }
	else if (tcHeloObject* helo_unit = dynamic_cast<tcHeloObject*>(air_unit))
	{
		helo_unit->mcKin.mfClimbAngle_rad = 1.5f;
		helo_unit->SetSpeed(100);
        helo_unit->SetAltitude(helo_unit->mcKin.mfAlt_m + 500.0f);
		helo_unit->SetLandingState(0); 
	}
    else if (air_unit != 0)
    {
		air_unit->mcKin.mfSpeed_kts += 200.0f;
        air_unit->SetSpeed(air_unit->mpDBObject->mfMaxSpeed_kts);
        air_unit->SetAltitude(air_unit->mcKin.mfAlt_m + 500.0f);
        air_unit->SetLandingState(0); 
    }
    brain->AddTask("RTB", 2.0f, ai::Task::PERMANENT | ai::Task::HIDDEN);
}

/**
* @return next location if jumping more than one stage 
* e.g. HANGAR to ALERT5 would stop at ALERT15 first
*/
teLocation tcFlightPort::GetNextStop(teLocation current, teLocation destination) const
{
	if (destination == HANGAR) return HANGAR;
	else if (destination == ALERT15) return ALERT15;
	else if (destination == ALERT5)
	{
		return (current == HANGAR) ? ALERT15 : ALERT5;
	}
	else if (destination == TAKEOFF)
	{
		switch (current)
		{
		case HANGAR: return ALERT15; break;
		case ALERT15: return ALERT5; break;
		case ALERT5: return PRETAKEOFF; break;
        case PRETAKEOFF: return TAKEOFF; break;
		default: wxASSERT(false); return current; break;
		}
	}
	else
	{
		wxASSERT(false);
		return current;
	}

}

/**
* Sets ready time of unit based on next destination. Check options
* to see if player has selected quick launch under realism settings
*/
void tcFlightPort::SetReadyTime(double t, tcAirState* airstate, teLocation nextLocation)
{
    wxASSERT((airstate->current_location >= 0) && (airstate->current_location < 6));
    wxASSERT((nextLocation >= 0) && (nextLocation < 6));
    wxASSERT(transitionTimesNormal[0][0] == 0); // crude check for unitialized static variable

    if (tcGameObject::IsEditMode())
    {
        airstate->ready_time = t;
    }
    else if (tcOptions::Get()->fastAircraftReady != 0)
    {
        airstate->ready_time = t + transitionTimesFast[airstate->current_location][nextLocation];
    }
    else
    {
        airstate->ready_time = t + transitionTimesNormal[airstate->current_location][nextLocation];
    }

    // OLD LOGIC (< 22 AUG 2009):  airstate->ready_time = tcGameObject::IsEditMode() ? t : t + 30.0; // short times for test
}

/**
*
*/
void tcFlightPort::Update(double t)
{
	if (((t - last_update_time) < 1.0f) && !tcGameObject::IsEditMode()) return;  // restrict to slower update, increased to 1 sec, 23OCT2010
    last_update_time = t;

    RemoveDestroyedUnits();

	// in mp client mode, update relative pos for display purposes, omit other updates
	if (parent->IsClientMode())
	{    
        RemoveStaleUnits();

		size_t obj_count = units.size();
		for(size_t n=0;n<obj_count;n++)
		{
			UpdateRelPos(units[n], t);
            units[n]->inTransit = (units[n]->goal_location != units[n]->current_location);
		}

        if (missionManager != 0) missionManager->PerformDeletions();

		return;
	}

    UpdateLanded();

	

	std::vector<long> idsToLaunch; // queue to launch when done updating all airstates

    size_t obj_count = units.size();
    for(size_t n=0;n<obj_count;n++)
    {
        tcAirState *airstate = units.at(n);
        
        UpdateMaintenance(airstate);

		UpdateRefueling(airstate);

        UpdatePlatform(airstate);

        bool moveable = false;
        if (tcAirObject* air = airstate->obj)
        {
            moveable = !air->IsRefueling() && !air->IsLoading() && (airstate->op != OP_MAINTENANCE);

            air->mfStatusTime = t; // added this 9JAN2010 to get time into tcGoalTracker::damageLog
        }
        else
        {
            wxASSERT(false);
        }

        /* if the unit is not in transit and is not at goal location, 
        ** check for a free spot in goal location. If there is a free spot in 
        ** goal location, then take spot and set current location to TRANSIT */
        bool inTransit = airstate->inTransit;
        
        bool needsAction = (!inTransit) && moveable && (airstate->current_location != airstate->goal_location);
        if (needsAction) 
        {
            wxASSERT(airstate->current_location != TAKEOFF);

			if (airstate->current_location == PRETAKEOFF)
			{
				idsToLaunch.push_back(airstate->obj->mnID);
			}
			else
			{
				teLocation nextLoc = GetNextStop(airstate->current_location, airstate->goal_location);
				int nextSpot = airstate->goal_spot; // guess goal_spot

				// goal_spot has spot for next destination if more than one move is required
				if (!IsSpotEmpty(nextLoc, nextSpot))
				{
					std::vector<tsSpotInfo> *loc_vector = 0;
					int spot_idx = FindEmptySpot(nextLoc, loc_vector);
					nextSpot = spot_idx;
				}
                SetReadyTime(t, airstate, nextLoc);

				MoveObjectToDestination(airstate, nextLoc, nextSpot);
			}
        }
        UpdateRelPos(airstate, t);
    }

	for (size_t n=0; n<idsToLaunch.size(); n++)
	{
		LaunchID(idsToLaunch[n]);
	}

	if (missionManager != 0) missionManager->Update(t);
}

/**
* Move landed units to hangar. In the future this will animate landing
* and set unit spot to the appropriate landing area. Launch spots may
* see double use as landing areas
*/
void tcFlightPort::UpdateLanded()
{
    size_t landing_count = toLand.size();
    for(size_t n=0;n<landing_count;n++)
    {
        tcAirObject* obj = toLand.at(n);

		// add landed objects to hangar and set to maintenance state
        if (AddObject(obj, HANGAR, 0))
		{
            double maintenanceTime_s = 300.0; // "fast" maintenance time

            if (tcAirObject* air = obj)
            {
                air->SetLoadoutTag(""); // clear loadout tag on land, regardless of equip state
                air->UnloadAllLaunchers();
                if (tcOptions::Get()->fastMaintenance == 0)
                {
                    maintenanceTime_s = (double)air->mpDBObject->GetRandomMaintenanceTime();
                }
            }
            int airStateIdx = FindAirState(obj);
            if (tcAirState* airState = GetAirState(unsigned int(airStateIdx)))
            {
                airState->op = OP_MAINTENANCE;
                airState->ready_time = last_update_time + maintenanceTime_s;
            }
            else
            {
                wxASSERT(false);
            }

        }
        else
        {
			//obj->mfDamageLevel += 10000; // destroy object
			toLaunch.push_back(obj); // kick it out
		}
    }
    toLand.clear();
}

void tcFlightPort::UpdateMaintenance(tcAirState* airstate)
{
    wxASSERT(airstate != 0);
    if ((airstate->op == OP_MAINTENANCE) && (airstate->ready_time <= last_update_time))
    {
        airstate->op = OP_NONE;
        airstate->ready_time = last_update_time;
    }
}

void tcFlightPort::UpdatePlatform(tcAirState* airstate)
{
    wxASSERT(airstate != 0);
    if (airstate->obj != 0)
    {
        airstate->obj->UpdateMagazines(last_update_time);

        if (airstate->obj->IsOverweight())
        {
            airstate->obj->LightenLoad();
        }
    }
}


/**
* If units not in hangar, schedule refuel operations to top off fuel if needed
* Assumes that 
*/
void tcFlightPort::UpdateRefueling(tcAirState *airstate)
{
	wxASSERT(airstate != 0);
	tcAirObject* aircraft = airstate->obj;
	if ((aircraft != 0) && (airstate->current_location != HANGAR) &&
		(!aircraft->IsOverweight()) && (!aircraft->IsRefueling()))
	{
		float fuelMargin_kg = aircraft->GetFuelCapacity() - aircraft->fuel_kg;
		float weightMargin_kg = aircraft->mpDBObject->maxTakeoffWeight_kg - aircraft->GetTotalWeight();
		if ((fuelMargin_kg > 1.0f) && (weightMargin_kg > 10.0f))
		{
			unsigned long fuelToAdd_kg = (unsigned long)floorf(std::min(fuelMargin_kg, weightMargin_kg));
			tcPlatformInterface platformInterface(aircraft);
			platformInterface.LoadOther("Fuel", fuelToAdd_kg);
		}
	}
}

tcFlightPort::tcFlightPort() 
: localId(10), 
  parent(0),
  mpDBObject(0),
  missionManager(0),
  nextUpdateIdx(0),
  maxTakeoffDamage(0.1f)
{

    Clear();

	ready_spots.clear();
    launch_spots.clear();
}

tcFlightPort::~tcFlightPort() 
{
	Clear();
}