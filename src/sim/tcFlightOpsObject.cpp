/** 
**  @file tcFlightOpsObject.cpp
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

#include "tcFlightOpsObject.h"
#include "tcGameObject.h"
#include "tcAirObject.h"
#include "tcAeroAirObject.h"
#include "tcHeloObject.h"
#include "tcJetDBObject.h"
#include "tcFlightportDBObject.h"
#include "tcDatabase.h"
#include "tcLauncher.h"
#include "tcScenarioLogger.h"
#include "common/tcStream.h"
#include "common/tcObjStream.h"
#include "common/tcGameStream.h"
#include "tcDamageModel.h"
#include "ai/tcMissionManager.h"
#include "tcDatabase.h"
#include "tcSimState.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


database::tcDatabase* tcFlightOpsObject::database = 0;




/**
* Loads state from command stream
*/
tcCommandStream& tcFlightOpsObject::operator<<(tcCommandStream& stream)
{
	flight_deck.operator<<(stream);

    return stream;
}

/**
* Saves state to command stream
*/
tcCommandStream& tcFlightOpsObject::operator>>(tcCommandStream& stream)
{
	flight_deck.operator>>(stream);

    return stream;
}

/**
* Loads state from create stream
*/
tcCreateStream& tcFlightOpsObject::operator<<(tcCreateStream& stream)
{
 	unsigned char nChildren;
	stream >> nChildren;

	for (unsigned short k=0; k < nChildren; k++)
	{
		long key;
		stream >> key;

		tcDatabaseObject* databaseObj = database->GetObject(key);

		short int localId;
		stream >> localId;

		std::string unitName;
		stream >> unitName;

		unsigned char loc;
		stream >> loc;

		unsigned char pos;
		stream >> pos;

        int idx = flight_deck.GetAirStateIdx(localId);
        if (idx == -1)
        {
            tcGameObject* child = AddChildToFlightDeck(databaseObj, unitName, teLocation(loc), pos);
            child->mnID = long(localId); // override default localId assigned by flightport

            // initialize launchers to empty, since this info isn't updated for hangar aircraft
            if (tcPlatformObject* platform = dynamic_cast<tcPlatformObject*>(child))
            {
                size_t nLaunchers = platform->GetLauncherCount();
                for (size_t n=0; n<nLaunchers; n++)
                {
                    tcLauncher* launcher = platform->GetLauncher(n);
                    launcher->SetChildClass("");
                }
            }

        }

		// load launcher create from stream
		//if (tcPlatformObject* platform = dynamic_cast<tcPlatformObject*>(child))
		//{
		//	size_t nLaunchers = platform->GetLauncherCount();
		//	for (size_t n=0; n<nLaunchers; n++)
		//	{
		//		tcLauncher* launcher = platform->GetLauncher(n);
		//		launcher->operator<<(stream);
		//	}
		//}
	}

    return stream;
}

/**
* Saves state to create stream
* Do partial save if stream size limit is reached
*/
tcCreateStream& tcFlightOpsObject::operator>>(tcCreateStream& stream)
{
    long freeSpace = stream.GetMaxSize() - stream.size() - 1; // 1 byte for update count header
    //wxASSERT(freeSpace > 0);

    tcCreateStream tempStream1;
    tcCreateStream tempStream2;

    wxASSERT(flight_deck.GetCount() < 256);
	unsigned char nChildren = flight_deck.GetCount();
    if (nextUpdateIdx >= nChildren) nextUpdateIdx = 0;
    size_t nUpdates = 0;

    while ((nextUpdateIdx < nChildren) && (freeSpace > 0))
	{
        tempStream1.clear();

		tcAirState* airState = flight_deck.GetAirState(nextUpdateIdx);
		tcGameObject* obj = airState->obj;
		wxASSERT(obj);

		tempStream1 << obj->mnDBKey;

		short int localId = short(obj->mnID);
		tempStream1 << localId;

		std::string unitName = obj->mzUnit.c_str();
		tempStream1 << unitName;

		unsigned char loc = unsigned char(airState->current_location);
		tempStream1 << loc;

		unsigned char pos = unsigned char(airState->current_spot); // doesn't matter for HANGAR loc
		tempStream1 << pos;

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

		// add launcher create to tempStream1
		//if (tcPlatformObject* platform = dynamic_cast<tcPlatformObject*>(obj))
		//{
		//	size_t nLaunchers = platform->GetLauncherCount();
		//	for (size_t n=0; n<nLaunchers; n++)
		//	{
		//		tcLauncher* launcher = platform->GetLauncher(n);
		//		launcher->operator>>(tempStream1);
		//	}
		//}
	}

    unsigned char nUpdatesChar = (unsigned char)nUpdates;
    stream << nUpdatesChar;

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
* Loads state from update stream
*/
tcUpdateStream& tcFlightOpsObject::operator<<(tcUpdateStream& stream)
{
	flight_deck.operator<<(stream);

    return stream;
}

/**
* Saves state to update stream
*/
tcUpdateStream& tcFlightOpsObject::operator>>(tcUpdateStream& stream)
{
	flight_deck.operator>>(stream);

    return stream;
}



/**
* Loads state from game stream
*/
tcGameStream& tcFlightOpsObject::operator<<(tcGameStream& stream)
{
    flight_deck.operator<<(stream);

    stream.ReadCheckValue(8237);

    return stream;
}

/**
* Saves state to game stream
*/
tcGameStream& tcFlightOpsObject::operator>>(tcGameStream& stream)
{
    flight_deck.operator>>(stream);

    stream.WriteCheckValue(8237);

    return stream;
}





void tcFlightOpsObject::ClearNewCommand()
{
    flight_deck.ClearNewCommand();
}

size_t tcFlightOpsObject::CurrentAirComplementSize() const
{
    return flight_deck.GetCount();
}

bool tcFlightOpsObject::HasNewCommand() const
{
	return flight_deck.HasNewCommand();
}


tcGameObject* tcFlightOpsObject::AddChildToFlightDeck(const std::string& className, std::string unitName, 
                                           teLocation loc, unsigned int position)
{
	tcDatabaseObject* objData = database->GetObject(className);
	if (objData)
	{
		return AddChildToFlightDeck(objData, unitName, loc, position);
	}
	else
	{
		fprintf(stderr, "tcFlightOpsObject::AddChildToFlightDeck - child not in database (%s)\n",
			className.c_str());
		return 0;
	}
}



/**
* Supports aero air model and air generic models. Adding other
* model types will fail.
* @param position preferred spot position, use 0 for any
* @return true if successful, false otherwise
*/
tcGameObject* tcFlightOpsObject::AddChildToFlightDeck(tcDatabaseObject* databaseObject, std::string unitName, 
                                           teLocation loc, unsigned int position)
{
    wxASSERT(databaseObject);

	tcAirObject* child = 0; // object to add to flight_deck
	
	std::string className = databaseObject->mzClass.c_str();

	if (tcJetDBObject *airDBObj = dynamic_cast<tcJetDBObject*>(databaseObject))
	{
		child = new tcAeroAirObject(airDBObj);
	}
	else if (tcAirDBObject *air2DBObj = dynamic_cast<tcAirDBObject*>(databaseObject))
	{
		if (air2DBObj->mnModelType == MTYPE_FIXEDWING)
		{
			child = new tcAirObject(air2DBObj);
        }
		else if (air2DBObj->mnModelType == MTYPE_HELO)
		{
			child = new tcHeloObject(air2DBObj);
		}
        else
        {
            std::cerr << "Attempted to add non-air generic object type to FO obj: " <<
                className << "\n";
            return 0;
        }
    }
    else
    {
        std::cerr << "Attempted to add non-air object type to FO obj: " <<
            className << "\n";
        return 0;
    }

    child->mzUnit = unitName.c_str();
    child->SetAlliance(gameObj->GetAlliance());
    child->SetRelativePosition(0,0,0); 
    child->SetRelativeOrientation(0,0,0); 

    if (flight_deck.AddObject(child, loc, position))
	{
		gameObj->AddChild(child); // add child to flight ops object
	}
	else
	{
		delete child;
		child = 0;
		std::cerr << "Failed to add child to flight_deck: " <<
                className << "\n";
	}

    return child;
}

void tcFlightOpsObject::AutoConfigureAirComplement(const std::vector<database::AirComplement>& airComplement)
{
    if (airComplement.size() == 0) return;

    flight_deck.Clear();

    // flightOps->AddChildToFlightDeck(className, unitName, loc, 0);
    for (size_t n=0; n<airComplement.size(); n++)
    {
        tcDatabaseObject* databaseObject = database->GetObject(airComplement[n].airClass);
        if (databaseObject != 0)
        {
            std::string prefix = airComplement[n].prefix;
            unsigned int quantity = airComplement[n].quantity;
            teLocation loc = (teLocation)std::max(std::min(airComplement[n].readyLevel, 3), 1); // 1 - HANGAR, 2 - ALERT15, 3 - ALERT5
            unsigned int startId = 1;
            GetAirBlockName(prefix, quantity, startId);
       
            for (unsigned int k=0; k<quantity; k++)
            {
                wxString unitName = wxString::Format("%s%d", prefix.c_str(), startId+k);
                AddChildToFlightDeck(databaseObject, unitName.ToStdString(), loc, 0);
            }
        }
    }
}


/**
* @return true if any aircraft were damaged
*/
bool tcFlightOpsObject::ApplyAdvancedDamage(const Damage& damage, tcGameObject* damager, float generalDamage)
{   
    Damage exposedAircraftDamage;
    exposedAircraftDamage.Clear();

    exposedAircraftDamage.blast_psi = 0.75f * damage.blast_psi; // blast shelter from being on CV or base
    exposedAircraftDamage.thermal_J_cm2 = damage.thermal_J_cm2;

    // define light damage that aircraft have chance of taking
    Damage lightAircraftDamage = exposedAircraftDamage;
    lightAircraftDamage.blast_psi *= 0.5f;
    lightAircraftDamage.thermal_J_cm2 *= 0.5f;


    // for aircraft that are not in hangar, apply blast and thermal damage    
    unsigned nChildren = flight_deck.GetCount();
    float totalDamage = 0;
    if ((damage.blast_psi > 0) || (damage.thermal_J_cm2 > 0))
    {
        for (unsigned short k=0; k < nChildren; k++)
        {
            tcAirState* airState = flight_deck.GetAirState(k);
            tcGameObject* obj = airState->obj;
            wxASSERT(obj);

            if (airState->current_location != HANGAR)
            {
                if (randf() < 0.5f)
                {
                    totalDamage += obj->ApplyAdvancedDamage(exposedAircraftDamage, damager);
                }
                else
                {
                    totalDamage += obj->ApplyAdvancedDamage(lightAircraftDamage, damager);
                }
            }
        }
    }

    bool result = totalDamage > 0;

    // next make pass through aircraft and test for damage based on generalDamage param
    float damageProbability = (gameObj->GetDamageLevel() < 0.5f) ? 0.5f*generalDamage : generalDamage;
    for (unsigned short k=0; k < nChildren; k++)
	{
		tcAirState* airState = flight_deck.GetAirState(k);
		tcGameObject* obj = airState->obj;

        if (randf() < damageProbability)
        {
            obj->ApplyGeneralDamage(randf(), damager);
            result = true;
        }
	}

    return result;
}


/**
* Determines if obj has landed on runway or crashed into flightport.
* Calls tcFlightPort method.
* If object successfully lands, it is added as a child. 
* @param obj Object to attempt landing
* @return -1 if crash, 0 if not close enough for landing, 1 if landed
* @see tcFlightPort::CheckLanding
*/
int tcFlightOpsObject::CheckLanding(tcAirObject *obj)
{
    gameObj->GetRelPosOf(obj, obj->rel_pos); // set update rel_pos field of landing candidate
    int result = flight_deck.CheckLanding(obj);
    if (result == 1)
    {
        gameObj->AddChild(obj); 
    }
    return result;
}

void tcFlightOpsObject::Clear() 
{
   flight_deck.Clear();
}

/**
* Finds a range of unit names that are not taken with form: prefix+<startId> to prefix+<startId+blockSize-1>
*/
void tcFlightOpsObject::GetAirBlockName(std::string& prefix, unsigned int blockSize, unsigned int& startId)
{
    tcSimState* simState = tcSimState::Get();

    for (size_t iteration=0; iteration<50; iteration++)
    {
        bool blockClear = true;
        for (unsigned int id=startId; (id<startId+blockSize)&&(blockClear); id++)
        {
            wxString nameCheck = wxString::Format("%s%d", prefix.c_str(), id);
            if (simState->GetObjectByName(nameCheck.ToStdString()) != 0)
            {
                blockClear = false;
            }
        }
        if (blockClear)
        {
            return;
        }
        else
        {
            startId = startId + 100;
        }

        if (iteration > 15)
        {
            AddRandomNameModifier(prefix);
        }
    }

    
    wxASSERT(false); // couldn't find free name
    
}

void tcFlightOpsObject::AddRandomNameModifier(std::string& prefix)
{
    int x = rand() % 10;

    switch (x)
    {
    case 0:
        prefix += "A";
        break;
    case 1:
        prefix += "B";
        break;
    case 2:
        prefix += "C";
        break;
    case 3:
        prefix += "D";
        break;
    case 4:
        prefix += "E";
        break;
    case 5:
        prefix += "J";
        break;
    case 6:
        prefix += "L";
        break;
    case 7:
        prefix += "M";
        break;
    case 8:
        prefix += "T";
        break;
    case 9:
        prefix += "X";
        break;
    default:
        prefix += "Y";
        break;
    };
}

/**
* @return pointer to flight_deck
*/
tcFlightPort* tcFlightOpsObject::GetFlightPort()
{
	return &flight_deck;
}

/**
* @return track with landing point coord and heading with orientation 
*/
tcTrack tcFlightOpsObject::GetLandingData()
{
	return flight_deck.GetLandingData(gameObj);
}


/**
* @return id of parent game object or -1 if error
*/
long tcFlightOpsObject::GetParentId() const
{
    if (gameObj != 0)
    {
        return gameObj->mnID;
    }
    else
    {
        wxASSERT(false);
        return -1;
    }
}

/**
* Randomly initializes object
*/
void tcFlightOpsObject::RandInitNear(float afLon_deg, float afLat_deg) 
{
 //  tcGameObject::RandInitNear(afLon,afLat);  // why can't we call base here ? virtual issue?
   if (gameObj->mpDBObject == NULL) {return;}

   bool heloOnly = flight_deck.IsHeloOnly();
   unsigned int modelType = (heloOnly) ? MTYPE_HELO : MTYPE_FIXEDWINGX;

   int nAircraft = flight_deck.GetHangarCapacity();
   for(int i=0; i<nAircraft; i++) 
   {
       // add FW air child for test
       tcDatabaseObject* dbObj = database->GetRandomOfType(modelType); 
//       tcJetDBObject* airDBObj = dynamic_cast<tcJetDBObject*>(dbObj);

	   tcAirObject* child = 0;
		
	   if (heloOnly)
	   {
		   child = new tcHeloObject(dynamic_cast<tcAirDBObject*>(dbObj));
	   }
	   else
	   {
		   child = new tcAeroAirObject(dynamic_cast<tcJetDBObject*>(dbObj));
	   }

	   /* This ASSERT can happen if bad model ids are in a database table (e.g. 
	   ** air object in generics database table ) */
       wxASSERT(child); 

       if (child != NULL) 
       {
		   child->mzUnit = (heloOnly) ? "HELO_" : "AIRX_";
           child->mzUnit.AssignRandomSuffix();
           float z = -20.0f + (float)i * 18.0f;
           child->SetRelativePosition(7.5,12.0,z);
           child->SetRelativeOrientation(0,0,0);
           gameObj->AddChild(child);
           flight_deck.AddObject(child, ALERT5, 0);
       }
   }

}


/**
* Print state info to text file for debug
*/
void tcFlightOpsObject::PrintToFile(tcFile& file) 
{

}


void tcFlightOpsObject::SaveToPython(scriptinterface::tcScenarioLogger& logger)
{	
	wxString s;
	unsigned nChildren = flight_deck.GetCount();

	for (unsigned short k=0; k < nChildren; k++)
	{
		tcAirState* airState = flight_deck.GetAirState(k);
        tcPlatformObject* platform = dynamic_cast<tcPlatformObject*>(airState->obj);
        wxASSERT(platform != 0);
        if (platform != 0)
        {
            logger.AddScenarioText(""); // blank line for readability
            s.Printf("SM.AddUnitToFlightDeck('%s', '%s', '%s', %d)", gameObj->mzUnit.c_str(),
                platform->mzClass.c_str(), platform->mzUnit.c_str(), airState->current_location);
            logger.AddScenarioText(s);

            s.Printf("SM.SetFlightDeckUnitLoadout('%s', '%s', '%s')", gameObj->mzUnit.c_str(),
                platform->mzUnit.c_str(), platform->GetLoadoutCommand().c_str());
            logger.AddScenarioText(s);
        }
	}

    if (ai::tcMissionManager* missionManager = flight_deck.GetMissionManager())
    {
        missionManager->SaveToPython(logger);
    }

}

/**
* Call before ::Clear() to update damage level of all children and 
* adjust game score for destroying all child objects
*/
void tcFlightOpsObject::DestroyAllChildrenAndUpdateScore(tcGameObject* damager)
{
    unsigned nChildren = flight_deck.GetCount();

	for (unsigned short k=0; k < nChildren; k++)
	{
		tcAirState* airState = flight_deck.GetAirState(k);
		tcGameObject* obj = airState->obj;
		wxASSERT(obj);

        obj->ApplyGeneralDamage(1.0, damager);
	}

}



/**
* Set up default spots and capacities for carrier flightport.
*/
void tcFlightOpsObject::SetFlightportDefaults()
{
    flight_deck.Clear();
    flight_deck.SetParent(gameObj);

    flight_deck.AddSpot(ALERT5, -7.5, 16.0f, 18.8f, 0.03f);

    flight_deck.AddSpot(ALERT15, 5.0f, 16.0f, 36.25f, -0.5f);
    flight_deck.AddSpot(ALERT15, 1.25f, 16.0f, 45.0f, -0.5f);
    flight_deck.AddSpot(ALERT15, 7.5f, 16.0f, 60.0f, 0.4f);
    flight_deck.AddSpot(ALERT15, 7.5f, 16.0f, 72.5f, 0.4f);
    flight_deck.AddSpot(ALERT15, 7.5f, 16.0f, 85.0f, 0.4f);
    flight_deck.AddSpot(ALERT15, 7.5f, 16.0f, 97.5f, 0.4f);

    flight_deck.SetHangarCapacity(16);
}
/******************************************************************************/
void tcFlightOpsObject::Update(double afStatusTime) 
{
   flight_deck.Update(afStatusTime);
   UpdateLaunch();
}
/******************************************************************************/
/* Check if flight_deck has an objects in the toLaunch vector. If so, move them
** to the tcGameObject::toLaunch vector and delete the matching pointer in the
** child list. This is a bit awkward because tcGameObject is holding an object
** in its child list that functionally belongs to the flight deck.
*/
void tcFlightOpsObject::UpdateLaunch()
{
    int nLaunch = (int)flight_deck.toLaunch.size();
    if (nLaunch==0) return;
    for(int n=0; n < nLaunch; n++)
    {
        tcGameObject *object_to_launch = flight_deck.toLaunch[n];
        gameObj->toLaunch.push_back(object_to_launch);
        gameObj->RemoveChild(object_to_launch);
    }
    flight_deck.toLaunch.clear();
}

/******************************************************************************/
tcFlightOpsObject::tcFlightOpsObject() 
{
	wxASSERT(false);
	Clear();

	//SetFlightportDefaults();
}
/******************************************************************************/
/*
tcFlightOpsObject::tcFlightOpsObject(tcFlightOpsObject& o) 
: tcSurfaceObject(o) 
{
}
*/

/**
* Constructor that initializes using info from database entry.
* This object will have its own database object eventually. The
* DB object will have info on number and types of aircraft the carrier
* can hold.
*/
tcFlightOpsObject::tcFlightOpsObject(tcFlightportDBObject* dbObject, tcGameObject* gameObject)
: gameObj(gameObject),
  nextUpdateIdx(0)
{
	wxASSERT(gameObj);
	if (database == 0)
	{
		database = tcDatabase::Get();
	}
    wxASSERT(database);

    if (dbObject == NULL)
    {
        std::cerr << "Flightport database obj not found for flight ops obj: ";
        std::cerr << gameObj->mzUnit.c_str() << "\n";
        return; 
    }

    flight_deck.InitFromDatabase(dbObject);
	flight_deck.SetParent(gameObj);
}
/******************************************************************************/
tcFlightOpsObject::~tcFlightOpsObject() 
{
}