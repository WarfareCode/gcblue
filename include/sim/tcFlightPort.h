/**
**  @file tcFlightPort.h
**
**  tcFlightPort object: descibes objects that allow air objects to take off
**  and land. This includes land-based runways, carrier runways, helipads, VTOL pads.
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

#ifndef _FLIGHTPORT_H_
#define _FLIGHTPORT_H_

#include <vector>
#include "tcGameObject.h"

class tcStream;
class tcCommandStream;
class tcCreateStream;
class tcUpdateStream;
class tcAirObject;

namespace ai
{
	class tcMissionManager;
}

namespace database
{
    class tcFlightportDBObject;
}

/** Location info for air unit in flightport.
 *  TODO get this out of top level namespace.
 */
enum teLocation 
{
   NOWHERE = 0,
   HANGAR = 1,   ///< longer term storage or repair
   ALERT15 = 2,    ///< out of hangar, on deck
   ALERT5 = 3,   ///< ready to take off
   PRETAKEOFF = 4, ///< a hack to get a/c to stay in launch spot but take some time to takeoff
   TAKEOFF = 5   ///< move to launch and take off
};
enum teOperation
{
   OP_NONE = 0,
   OP_TRANSIT = 1,
   OP_UNLOAD = 2,
   OP_LOAD = 3,   ///< or refuel
   OP_REPAIR = 4,
   OP_MAINTENANCE = 5
};

/**
* state info for units in the flightport
* This state info is unique info particular to flightport operations
*/
class tcAirState
{
public:
	teLocation current_location;
	int current_spot;
	teLocation goal_location;
	int goal_spot;     // destination within deck1, deck2, or launch 
	bool inTransit;
	teOperation op;
	double ready_time; // time for op to be completed
	tcAirObject* obj;
    
    unsigned int lastMultiplayerUpdate; // for multiplayer client
	tcUpdateStream& operator<<(tcUpdateStream& stream);
	tcUpdateStream& operator>>(tcUpdateStream& stream);
	tcGameStream& operator<<(tcGameStream& stream);
	tcGameStream& operator>>(tcGameStream& stream);

	std::string LocationToString(teLocation loc);
	std::string OperationToString(teOperation op);
};

/** Physical information about spot along with pointer to tcAirState object 
 * for occupying unit. obj_info is NULL if the spot is empty. 
 */
struct tsSpotInfo 
{
   tcAirState *obj_info;  ///< air state info for object occupying or in transit to spot, NULL if empty
   float x,y,z; ///< surface assumed flat in between spots [m]
   float orientation; ///< orientation for runway, 0 along -z axis (heading axis for ships)
   float length; ///< [m]

   bool IsEmpty() const {return obj_info == 0;}
};

/**
* Models carrier flight deck, airstrips, helo pads.
* Possibly should be modified to inherit from tcGameObject in the future.
*/
class tcFlightPort
{
public:   
    std::vector<tcAirObject*> toLand; ///< objects that have landed but haven't been added to units yet
    std::vector<tcAirState*> units; ///< air units in tcFlightPort
    std::vector<tcAirObject*> toLaunch; ///< air units for game engine to launch (take ownership of)
    tcGameObject* parent; ///< parent object of flightport
    double last_update_time;

    int AddObject(tcAirObject *obj, teLocation loc, unsigned int position);
    void AddSpot(teLocation loc, float x, float y, float z, float orientation = 0, float length = 0);
    int CheckLanding(tcAirObject* obj);
    void Clear(); 
    int FindAirState(tcAirState* airstate);
	int FindAirState(tcGameObject* obj);
    tcAirState* FindAirStateObj(tcGameObject* obj);
    const tcAirState* FindAirStateObj(const tcGameObject* obj) const;
    int FindEmptySpot(std::vector<tsSpotInfo> *loc_vector);
    int FindEmptySpot(teLocation loc, std::vector<tsSpotInfo>*& loc_vector);
    tcAirState* GetAirState(unsigned n);
	const tcAirState* GetAirState(unsigned n) const;
    int GetAirStateIdx(long id) const;
    size_t GetCount() const {return units.size();}
    tsSpotInfo* GetCurrentSpotInfo(tcAirState *airstate);
    tcFlightportDBObject* GetDatabaseObject() const;
    unsigned GetHangarCapacity() const {return hangarCapacity;}
	tcTrack GetLandingData(const tcGameObject* obj);
    tcGameObject* GetObject(unsigned n);
	tcGameObject* GetObjectById(long id);
    tcGameObject* GetObjectByName(const std::string& unitName);

    float GetTimeToDestination(const tcAirState* airstate) const;
    const wxString& GetTimeToDestinationString(const tcAirState* airstate) const;

    std::vector<tsSpotInfo>* GetLocVector(teLocation loc);
    void InitFromDatabase(database::tcFlightportDBObject *dbObj);
    void InitRelPos(tcAirState *airstate);
	bool IsHeloOnly() const;
    int LaunchRunway(int runway); // order unit on runway to take off
    int LaunchID(long id);  // order unit with id to take off
    int LaunchAirstate(tcAirState* airstate);
	bool IsQueuedForTakeoff(long id) const;

    float GetMaxRunwayLength() const;

    bool MoveToLaunchQueue(tcAirState *airstate);
    void SetObjectDestination(unsigned n, teLocation loc, unsigned int position = 0);
	void SetObjectDestination(tcAirState* airstate, teLocation loc, unsigned int position = 0);
    void SetParent(tcGameObject *newparent) {parent=newparent;}
    void SetHangarCapacity(unsigned cap) {hangarCapacity = cap;}
    void Update(double t);
    void UpdateLanded();
	void UpdateRefueling(tcAirState *airstate);
    void UpdateRelPos(tcAirState *airstate, double time);
    void UpdateUnitKin(tcAirState *airstate); // update unit kinematics based on parent info and rel_pos

	ai::tcMissionManager* GetMissionManager();
	ai::tcMissionManager* GetOrCreateMissionManager();

    tcCommandStream& operator<<(tcCommandStream& stream);
    tcCreateStream& operator<<(tcCreateStream& stream);
    tcUpdateStream& operator<<(tcUpdateStream& stream);
    tcGameStream& operator<<(tcGameStream& stream);

    tcCommandStream& operator>>(tcCommandStream& stream);
    tcCreateStream& operator>>(tcCreateStream& stream);
    tcUpdateStream& operator>>(tcUpdateStream& stream);
    tcGameStream& operator>>(tcGameStream& stream);

    void ClearNewCommand();
    bool HasNewCommand() const;

    static void InitTransitionTimes();

    tcFlightPort();
    ~tcFlightPort();
private:
    const float maxTakeoffDamage; ///< max damage level where takeoff is allowed
    /* tcAirState objects for all units in flightport are stored in 
    ** the units vector */
    std::vector<tsSpotInfo> ready_spots;
    std::vector<tsSpotInfo> launch_spots;
    static float transitionTimesFast[6][6];
    static float transitionTimesNormal[6][6];

	tcFlightportDBObject* mpDBObject;
    unsigned hangarCapacity;
    unsigned inHangarCount; // count of units in hangar or in transit to hangar
	short int localId; ///< used to assign object id within flightport

	// data for multiplayer commands
	struct CommandInfo
	{
		short int id; ///< id of unit that command applies to
		unsigned char op; ///< 0, launch unit, 1-3 move unit
		unsigned char pos; ///< position parameter to specify which launch or ready spot to move to
	};
	std::vector<CommandInfo> commandList;
	ai::tcMissionManager* missionManager;
    size_t nextUpdateIdx; ///< to track partial updates on multiplayer server


	teLocation GetNextStop(teLocation current, teLocation destination) const;
    void MoveObjectToDestination(tcAirState *airstate, teLocation destination, int spot);
	bool IsSpotEmpty(teLocation loc, unsigned int spot);
	void ResyncSpots();
    void RemoveStaleUnits();
    void RemoveDestroyedUnits();
    void SetReadyTime(double t, tcAirState* airstate, teLocation nextLocation);
    void UpdateMaintenance(tcAirState* airstate);
    void UpdatePlatform(tcAirState* airstate);
};









#endif

