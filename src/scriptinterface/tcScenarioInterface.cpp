/**  
**  @file tcScenarioInterface.cpp
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
#include "wx/datetime.h"
#include "wx/file.h"
#include "wx/msgdlg.h"
#include "wx/progdlg.h"

#include "tcAeroAirObject.h"
#include "tcAirfieldObject.h"
#include "tcCarrierObject.h"
#include "tcDatabase.h"
#include "tcDirector.h"
#include "tcDirectorEvent.h"
#include "tcPlatformDBObject.h"
#include "tcGoal.h"
#include "tcGoalTracker.h"
#include "tcGroundObject.h"
#include "tcGroundVehicleObject.h"
#include "tcLauncher.h"
#include "tcMapData.h"
#include "tcMapObject.h"
#include "tcMapOverlay.h"
#include "tcScenarioInterface.h"
#include "tcSimState.h"
#include "tcSoundConsole.h"
#include "tcStores.h"
#include "tcSubObject.h"
#include "ai/Brain.h"
#include "tcPlatformInterface.h"
#include "tcDatabaseIterator.h"
#include "wxcommands.h"
#include "tcAllianceInfo.h"
#include "tcCommandQueue.h"
#include "tcGameSerializer.h"
#include "tcScenarioRandomizer.h"
#include "tcSimPythonInterface.h"
#include "tcSonarEnvironment.h"
#include "tcGameObjIterator.h"
#include "ai/tcMissionManager.h"
#include "ai/Nav.h"
#include "tcGameStream.h"
#include "tcOptions.h"
#include "tcTorpedoDBObject.h"
#include "tcMessageCenter.h"

using namespace std;
using namespace boost::python;
using ai::Brain;
using database::tcDatabaseIterator;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif 

namespace scriptinterface
{
    using namespace ai;


    void tcScenarioUnit::SetPosition(double lon_deg, double lat_deg, float alt_m)
    {
        lon = lon_deg;
        lat = lat_deg;
        alt = alt_m;
    }

    /**
    * Test that fields are valid. Display message box if not.
    * @return true if validation okay
    */
    bool tcScenarioUnit::Validate()
    {
        if (className == "Not defined")
        {
            wxMessageBox("Scenario unit class not defined","Error",wxICON_ERROR);
            return false;
        }
        if (unitName == "Not defined")
        {
            wxString s = wxString::Format("Scenario unit name not defined (class: %s)",className.c_str());
			wxMessageBox(s.c_str(),"Error",wxICON_ERROR);
			return false;
		}
		return true;

	}




    tcDirector* tcScenarioInterface::director = 0;
    tcMapData* tcScenarioInterface::mapData = 0;
    tcMapOverlay* tcScenarioInterface::overlay = 0;
    tcSimState* tcScenarioInterface::simState = 0;
    tcCommandQueue* tcScenarioInterface::commandQueue = 0;

    // non-python methods
    
    tcGameObject* tcScenarioInterface::GetLastObjectAdded() const
    {
        return lastObjectAdded;
    }

	tcMapOverlay* tcScenarioInterface::GetMapOverlay() const
	{
		return overlay;
	}


    // Interface class management methods

    void tcScenarioInterface::AddGoalClasses()
    {
        InitGoalPython();
    }

    object tcScenarioInterface::GetInterface() 
    {
        object DatumType =
            class_<tcDatum>("Datum")
            .def_readwrite("lat",&tcDatum::lat)
            .def_readwrite("lon",&tcDatum::lon)
            .def_readwrite("alt",&tcDatum::alt)
            ;

        object ScenarioUnitType =
            class_<tcScenarioUnit>("ScenarioUnit")
            .def_readwrite("className",&tcScenarioUnit::className)
            .def_readwrite("unitName",&tcScenarioUnit::unitName)
            .def_readwrite("lat",&tcScenarioUnit::lat)
            .def_readwrite("lon",&tcScenarioUnit::lon)
            .def_readwrite("alt",&tcScenarioUnit::alt)
            .def_readwrite("heading",&tcScenarioUnit::heading)
            .def_readwrite("speed",&tcScenarioUnit::speed)
            .def_readwrite("throttle",&tcScenarioUnit::throttle)
            .def_readwrite("cost",&tcScenarioUnit::cost)
            .def("SetPosition",&tcScenarioUnit::SetPosition)
            ;

		object StringArrayType = 
			class_<tcStringArray>("StringArray")
			.def("Size", &tcStringArray::Size)
			.def("GetString", &tcStringArray::GetString)
            .def("PushBack", &tcStringArray::PushBack)
			;

        object ParsedUnitNameType = 
            class_<tcParsedUnitName>("ParsedUnitName")
            .def_readwrite("isValid", &tcParsedUnitName::isValid)
            .def_readwrite("root", &tcParsedUnitName::root)
            .def_readwrite("separator", &tcParsedUnitName::separator)
            .def_readwrite("id", &tcParsedUnitName::id)
            ;

		object AllianceROEInfo = 
			class_<tcAllianceROEInfo>("AllianceROEInfo")
			.def_readwrite("AirROE", &tcAllianceROEInfo::airROE)
			.def_readwrite("SurfaceROE", &tcAllianceROEInfo::surfaceROE)
			.def_readwrite("SubROE", &tcAllianceROEInfo::subROE)
			.def_readwrite("LandROE", &tcAllianceROEInfo::landROE)
			;
	

        object InterfaceType =
            class_<tcScenarioInterface>("ScenarioInterface")
            .def("AddUnitToAlliance",&tcScenarioInterface::AddUnitToAlliance)
            .def("AddUnitToFlightDeck",&tcScenarioInterface::AddUnitToFlightDeck)
            .def("AddUnitTask", &tcScenarioInterface::AddUnitTask)
            .def("AddToUnitMagazine",&tcScenarioInterface::AddToUnitMagazine)
            .def("GetUnitInterface", &tcScenarioInterface::GetUnitInterface)
			.def("GetUnitNameById", &tcScenarioInterface::GetUnitNameById)
            .def("GetUnitIdByName", &tcScenarioInterface::GetUnitIdByName)
            .def("SetUnitLauncherItem",&tcScenarioInterface::SetUnitLauncherItem)
            .def("SetFlightDeckUnitLoadout", &tcScenarioInterface::SetFlightDeckUnitLoadout)
            .def("SetUnitAlwaysVisibleState", &tcScenarioInterface::SetUnitAlwaysVisibleState)

			.def("AllianceExists", &tcScenarioInterface::AllianceExists)
            .def("CreateAlliance",&tcScenarioInterface::CreateAlliance)
            .def("SetAllianceRelationship", &tcScenarioInterface::SetAllianceRelationship)
            .def("SetAllianceDefaultCountry", &tcScenarioInterface::SetAllianceDefaultCountry)
            .def("GetAllianceCountry", &tcScenarioInterface::GetAllianceCountry)
            .def("SetAlliancePlayable", &tcScenarioInterface::SetAlliancePlayable)
            .def("IsAlliancePlayable", &tcScenarioInterface::IsAlliancePlayable)
            .def("GetAllianceROE", &tcScenarioInterface::GetAllianceROE)
            .def("SetAllianceROE", &tcScenarioInterface::SetAllianceROE)
			.def("SetAllianceROEByType", &tcScenarioInterface::SetAllianceROEByType)
            .def("GetDefaultUnit",&tcScenarioInterface::GetDefaultUnit)
            .def("GetRandomDatum",&tcScenarioInterface::GetRandomDatum)
            .def("GetRandomPlatformName", &tcScenarioInterface::GetRandomPlatformName)
            .def("GetParsedUnitName", &tcScenarioInterface::GetParsedUnitName)
			.def("GetUserAlliance", &tcScenarioInterface::GetUserAlliance)
			.def("SaveGame", &tcScenarioInterface::SaveGame)
            .def("SetAllianceGoal",&tcScenarioInterface::SetAllianceGoal)
            .def("GetAllianceGoal",&tcScenarioInterface::GetAllianceGoal)
            .def("GetGoalById",&tcScenarioInterface::GetGoalById)
            .def("AddChildGoalToId", &tcScenarioInterface::AddChildGoalToId)
            .def("DeleteGoalById", &tcScenarioInterface::DeleteGoalById)
            .def("SetDateTime",&tcScenarioInterface::SetDateTime)
            .def("SetDateTimeByString",&tcScenarioInterface::SetDateTimeByString)
			.def("GetScenarioDateAsString",&tcScenarioInterface::GetScenarioDateAsString)
            .def("SetPerfectScore",&tcScenarioInterface::SetPerfectScore)
            .def("SetScenarioDescription",&tcScenarioInterface::SetScenarioDescription)
            .def("SetScenarioLoaded",&tcScenarioInterface::SetScenarioLoaded)
            .def("SetScenarioName",&tcScenarioInterface::SetScenarioName)
            .def("SetScenarioLocked", &tcScenarioInterface::SetScenarioLocked)
            .def("DuplicateUnitTasking", &tcScenarioInterface::DuplicateUnitTasking)
			.def("IsUsingNATONames", &tcScenarioInterface::IsUsingNATONames)
			.def("GetDisplayName", &tcScenarioInterface::GetDisplayName)
            .def("GetUnitList", &tcScenarioInterface::GetUnitList)

			.def("SetStartTheater", &tcScenarioInterface::SetStartTheater)
            .def("SetUserAlliance",&tcScenarioInterface::SetUserAlliance)
            // time/mode events
            .def("ClearEvents",&tcScenarioInterface::ClearEvents)
            .def("HookPlatform",&tcScenarioInterface::HookPlatform)
            .def("Pause",&tcScenarioInterface::Pause)
            .def("Resume",&tcScenarioInterface::Resume)
            .def("Set3DMode",&tcScenarioInterface::Set3DMode)
            .def("SetBriefingMode",&tcScenarioInterface::SetBriefingMode)
            .def("SetEventTime",&tcScenarioInterface::SetEventTime)
            // audio events
            .def("PauseAudio",&tcScenarioInterface::PauseAudio)
            .def("PlayAudio",&tcScenarioInterface::PlayAudio)
            .def("PlayEffect",&tcScenarioInterface::PlayEffect)
            .def("SeekAudio",&tcScenarioInterface::SeekAudio)
            // send command
            .def("SendCommand", &tcScenarioInterface::SendCommand)
            // text console and map events
            .def("ChangeMapView",&tcScenarioInterface::ChangeMapView)
            .def("ChangeWorldMapView",&tcScenarioInterface::ChangeWorldMapView)
            .def("SetStartView",&tcScenarioInterface::SetStartView)
			.def("ChangeMapTheater",&tcScenarioInterface::ChangeMapTheater)
            .def("ConsoleText",&tcScenarioInterface::ConsoleText)
            .def("ChannelMessage", &tcScenarioInterface::ChannelMessage)
            .def("MapText",&tcScenarioInterface::MapText)
            // overlay graphics
            .def("OverlayText", &tcScenarioInterface::OverlayText)
            .def("OverlayTextInteractive", &tcScenarioInterface::OverlayTextInteractive)
            // camera and 3D viewer events
            .def("FlybyCamera",&tcScenarioInterface::FlybyCamera)
            .def("TrackCamera",&tcScenarioInterface::TrackCamera)
            .def("Text3D",&tcScenarioInterface::Text3D)
            // goal creation workaround
            .def("CompoundGoal",&tcScenarioInterface::CompoundGoal)
            .def("TimeGoal",&tcScenarioInterface::TimeGoal)
            .def("DestroyGoal",&tcScenarioInterface::DestroyGoal)
			.def("ProtectGoal",&tcScenarioInterface::ProtectGoal)
            .def("AreaGoal",&tcScenarioInterface::AreaGoal)
			// simple briefing text
			.def("SetSimpleBriefing", &tcScenarioInterface::SetSimpleBriefing)
			// database query
			.def("GetPlatformListByClass", &tcScenarioInterface::GetPlatformListByClass)
            .def("SetFilterByYear", &tcScenarioInterface::SetFilterByYear)
            .def("GetFilterByYear", &tcScenarioInterface::GetFilterByYear)
            .def("SetFilterByCountry", &tcScenarioInterface::SetFilterByCountry)
            .def("GetFilterByCountry", &tcScenarioInterface::GetFilterByCountry)

            // database management
            .def("LoadDatabaseMod", &tcScenarioInterface::LoadDatabaseMod)
            .def("RestoreDefaultDatabase", &tcScenarioInterface::RestoreDefaultDatabase)

            // more scenario edit commands, started Oct 2008
            .def("SetAirGroupName", &tcScenarioInterface::SetAirGroupName)
            .def("GetAirGroupName", &tcScenarioInterface::GetAirGroupName)
            .def("GetAirUnitId", &tcScenarioInterface::GetAirUnitId)
            .def("SetAirGroupCount", &tcScenarioInterface::SetAirGroupCount)
            .def("GetAirGroupCount", &tcScenarioInterface::GetAirGroupCount)
            .def("SetMagazineAddCount", &tcScenarioInterface::SetMagazineAddCount)
            .def("GetMagazineAddCount", &tcScenarioInterface::GetMagazineAddCount)

            // scenario randomization commands
            .def("SetIncludeProbability", &tcScenarioInterface::SetIncludeProbability)
            .def("IncludeUnit", &tcScenarioInterface::IncludeUnit)
            .def("AddRandomBox", &tcScenarioInterface::AddRandomBox)

            // sonar
            .def("SetSeaState", &tcScenarioInterface::SetSeaState)
            .def("GetSeaState", &tcScenarioInterface::GetSeaState)
            .def("SetSVP", &tcScenarioInterface::SetSVP)
			.def("SetSonarTemplate", &tcScenarioInterface::SetSonarTemplate)
			.def("GetSonarTemplate", &tcScenarioInterface::GetSonarTemplate)
			.def("GetNumberSonarTemplates", &tcScenarioInterface::GetNumberSonarTemplates)
			.def("GetTemplateName", &tcScenarioInterface::GetTemplateName)
            ;
        return InterfaceType;
    }

	bool tcScenarioInterface::AddUnitToAlliance(scriptinterface::tcScenarioUnit unit, int alliance)
    {
        lastObjectAdded = 0;
        
        if (!unit.Validate()) return false;

		if (simState->GetObjectByName(unit.unitName) != 0)
		{
			fprintf(stderr, "tcScenarioInterface::AddUnitToAlliance - Duplicate unit (%s) in scenario %s\n",
                unit.unitName.c_str(), simState->GetScenarioName());
			return false;
		}

        tcDatabaseObject *dbObj = simState->mpDatabase->GetObject(unit.className);
        if (dbObj == NULL)
        {
            wxString errorMessage = 
                wxString::Format("Could not find class name \"%s\" in database, "
                "check entry in scenario \"%s\"\n", 
                unit.className.c_str(), simState->GetScenarioName());

            fprintf(stderr, errorMessage.c_str());
            // don't popup errors if sim is running
            if (simState->GetTime() == 0)
            {
                wxMessageBox(errorMessage.c_str(), "Error", wxICON_ERROR);
            }
            return false;
        }

        if ((unit.lon < -360) || (unit.lon > 360.0) || (unit.lat < -90) || (unit.lat > 90))
        {
            fprintf(stderr, "tcScenarioInterface::AddUnitToAlliance - %s coordinates out of bounds (lon: %.4f deg, lat: %.4f deg)\n",
                unit.unitName.c_str(), unit.lon, unit.lat);
            return false;
        }

        if (unit.lon < -180.0) unit.lon += 360.0;
        else if (unit.lon >= 180.0) unit.lon -= 360.0;

        tcGameObject *gameObj = simState->CreateGameObject(dbObj);
        if (gameObj == 0)
        {
            fprintf(stderr, "game obj creation error\n");
            return false;
        }

		tcKinematics& kin = gameObj->mcKin;

        kin.mfLon_rad = C_PIOVER180*unit.lon;
        kin.mfLat_rad = C_PIOVER180*unit.lat;
        kin.mfAlt_m = unit.alt;

        kin.mfHeading_rad = C_PIOVER180*unit.heading;
        gameObj->SetHeading(kin.mfHeading_rad);
        kin.mfPitch_rad = 0;
        kin.mfRoll_rad = 0;
        if (unit.speed < 0) {unit.speed = 0;}
        kin.mfSpeed_kts = unit.speed;

        gameObj->SetAlliance(alliance);
        gameObj->mfStatusTime = 0; // for lack of a better time
        gameObj->mzUnit = unit.unitName.c_str();
        gameObj->SetCost(unit.cost);

        float terrainHeight = mapData->GetTerrainHeight(unit.lon, unit.lat, 0);
            
        // class-specific initialization
        tcPlatformObject* platObj = dynamic_cast<tcPlatformObject*>(gameObj);
        if (platObj != 0)
        {
            // limit speed to max
            if (kin.mfSpeed_kts > platObj->mpDBObject->mfMaxSpeed_kts)
            {
                platObj->mcKin.mfSpeed_kts = platObj->mpDBObject->mfMaxSpeed_kts;
            }
            platObj->SetSpeed(kin.mfSpeed_kts);
        }
        // need something to calculate steady state speed based on throttle and altitude.
        if (tcAeroAirObject *aeroAirObj = dynamic_cast<tcAeroAirObject*>(gameObj))
        {   
            if (kin.mfSpeed_kts < 200.0f) kin.mfSpeed_kts = 200.0f;
            aeroAirObj->SetSpeed(kin.mfSpeed_kts);
            if (unit.throttle >= 0.3)
            {
                aeroAirObj->SetThrottleFraction(unit.throttle);
            }
        }

        if (tcAirObject *airObj = dynamic_cast<tcAirObject*>(gameObj))
        {
            if (kin.mfAlt_m < terrainHeight + 10.0f)
            {
                kin.mfAlt_m = terrainHeight + 10.0f;
            }
			if (kin.mfAlt_m < 50.0f)
			{
				kin.mfAlt_m = 50.0f;
			}
            
            airObj->SetAltitude(airObj->mcKin.mfAlt_m);
            ai::Brain* brain = airObj->GetBrain();
            brain->AddTask("RTB", 2.0f, ai::Task::PERMANENT | ai::Task::HIDDEN);
        }
        if (tcSubObject* sub = dynamic_cast<tcSubObject*>(gameObj))
        {
            if (kin.mfAlt_m < terrainHeight + 10.0f)
            {
                kin.mfAlt_m = terrainHeight + 10.0f;
            }
            sub->SetAltitude(kin.mfAlt_m);
        }

        if (tcSurfaceObject* surface = dynamic_cast<tcSurfaceObject*>(gameObj))
        {
            surface->SetAltitude(0); // ignore altitude field and set to sea level
        }

		// place ground objects relative to terrain height
		if (tcAirfieldObject* fieldObj = dynamic_cast<tcAirfieldObject*>(gameObj))
		{
			kin.mfAlt_m += 
				mapData->GetTerrainHeight(unit.lon, unit.lat, 0);
		}
		else if (tcGroundObject* groundObj = dynamic_cast<tcGroundObject*>(gameObj))
		{
            kin.mfAlt_m = max(kin.mfAlt_m, 1.0f); // minimum 1 m over ground

			kin.mfAlt_m += 
				mapData->GetTerrainHeight(unit.lon, unit.lat, 0);
		}
		else if (tcGroundVehicleObject* groundVehicleObj = dynamic_cast<tcGroundVehicleObject*>(gameObj))
		{
			kin.mfAlt_m += 
				mapData->GetTerrainHeight(unit.lon, unit.lat, 0);
		}

		gameObj->mfStatusTime = simState->GetTime();
        simState->AddPlatform(gameObj);

		lastObjectAdded = gameObj;

        if (tcGameObject::IsEditMode() && (platObj != 0))
        {
            platObj->AutoConfigurePlatform("");
        }
         
		if (progressDialog != 0)
		{
			wxString msg = "Loading units"; //wxString::Format("Adding %s", unit.unitName.c_str());
			progressDialog->Pulse(msg);
		}

        return true;
    }

    /**
    * @param parentName unitname of parent carrier object
    * @param className class of (air) unit to add
    * @param unitName unitname of unit to add
    * @param loc, HANGAR = 1, ALERT15 = 2, ALERT5 = 3
    * @return true if successful, false otherwise
    */
    bool tcScenarioInterface::AddUnitToFlightDeck(std::string parentName, 
        std::string className, 
        std::string unitName, int locCode)
    {
        unitId++;

        wxASSERT(simState);
        tcGameObject* parentObj = simState->GetObjectByName(parentName);
        if (tcFlightOpsObject* flightOps = dynamic_cast<tcFlightOpsObject*>(parentObj))
        {
            teLocation loc;
            if (locCode == 1) loc = HANGAR;
            else if (locCode == 2) loc = ALERT15;
            else if (locCode == 3) loc = ALERT5;
            else
            {
                cerr << "Bad location code when adding to " << parentName << "\n";
                return false;
            }
            tcGameObject* child = flightOps->AddChildToFlightDeck(className, unitName, loc, 0);
			if (child != 0)
			{
				if (progressDialog != 0)
				{
					wxString msg = "Loading units"; //wxString::Format("Adding %s to %s", unitName.c_str(), parentName.c_str());
					progressDialog->Pulse(msg);
				}
				return true;
			}
			else
			{
				wxString errorMessage = 
					wxString::Format("Could not find class name \"%s\" in database, "
					"check entry in scenario \"%s\"\n", 
					className.c_str(), simState->GetScenarioName());

				// don't popup errors if sim is running
				if (simState->GetTime() == 0)
				{
					wxMessageBox(errorMessage.c_str(), "Error", wxICON_ERROR);
				}
				return false;
			}

        }
        else
        {
            cerr << "Parent object not found: " << parentName << "\n";
            return false;
        }
    }

    /**
    * Adds items (normally weapons) to first compatible magazine of unit
    */
    void tcScenarioInterface::AddToUnitMagazine(const std::string& unitName, 
        const std::string& item, unsigned long quantity)
    {
        wxASSERT(simState);
        tcGameObject* parentObj = simState->GetObjectByName(unitName);
        if (tcPlatformObject* platform = dynamic_cast<tcPlatformObject*>(parentObj))
        {
            unsigned int nMagazines = platform->GetMagazineCount();
            for (unsigned int n=0; n<nMagazines; n++)
            {
                tcStores* mag = platform->GetMagazine(n);
                if (!mag->IsFull() && mag->IsCompatible(item))
                {
                    mag->AddItems(item, quantity);
                    return;
                }
            }
			
				
			// log error to stderr.txt
            fprintf(stderr, "tcScenarioInterface::AddToUnitMagazine - "
                "Failed to load %s to unit %s ", item.c_str(),unitName.c_str());
            for (unsigned int n=0; n<nMagazines; n++)
            {
                tcStores* mag = platform->GetMagazine(n);
				fprintf(stderr, "(%d ", n);
				if (!mag->IsCompatible(item)) fprintf(stderr, "INCOMPAT");
				else if (mag->IsFull()) fprintf(stderr, "FULL");
				else fprintf(stderr, "OK"); // should never happen
				
				fprintf(stderr, ") ");
            }
			fprintf(stderr, "\n");
            
        }
        else
        {
            fprintf(stderr, "tcScenarioInterface::AddToUnitMagazine - "
                "Unit not found: %s\n", unitName.c_str());
        }
    }
    

    /**
    * if state is true, then adds an "always visible" track to all other alliance sensor maps
    * if false, then drops track in all other alliance sensor maps
    */
    void tcScenarioInterface::SetUnitAlwaysVisibleState(const std::string& unitName, bool state)
    {
        wxASSERT(simState != 0);

        if (tcGameObject* obj = simState->GetObjectByName(unitName))
        {
            if (state)
            {
                simState->mcSensorMap.AddAlwaysVisibleTrack(unitName);
            }
            else
            {
                simState->mcSensorMap.DropAlwaysVisibleTrack(unitName);
            }
        }
        else
        {
            fprintf(stderr, "tcScenarioInterface::SetUnitAlwaysVisibleState - %s not found\n",
                unitName.c_str());
        }

    }

    /**
    * Adds task to unit (newer AI system with parallel tasks)
    * Logs error if unit is not eligible
    */
    void tcScenarioInterface::AddUnitTask(const std::string& unitName, const std::string& taskName, 
        double priority, int attributes)
    {
        wxASSERT(simState);
        tcGameObject* parentObj = simState->GetObjectByName(unitName);
        if (tcPlatformObject* platform = dynamic_cast<tcPlatformObject*>(parentObj))
        {
            ai::Brain* brain = platform->GetBrain();
            wxASSERT(brain);
            brain->AddTask(taskName, priority, attributes);
        }
        else
        {
            fprintf(stderr, "tcScenarioInterface::AddUnitTask - "
                "Unit not found: %s\n", unitName.c_str());
        }       
        
    }
    

    tcPlatformInterface tcScenarioInterface::GetUnitInterface(const std::string& unitName)
    {
        wxASSERT(simState);
        tcGameObject* obj = simState->GetObjectByName(unitName);
        if (tcPlatformObject* platform = dynamic_cast<tcPlatformObject*>(obj))
        { 
            return tcPlatformInterface(platform);
        }
        else
        {
            return tcPlatformInterface(0);
        }
    }

	std::string tcScenarioInterface::GetUnitNameById(long id) const
	{
		tcGameObject* obj = simState->GetObject(id);

        if (obj == 0)
		{
			return std::string("");
		} 
		else
		{
            return std::string(obj->mzUnit.c_str());
        }
	}

    long tcScenarioInterface::GetUnitIdByName(const std::string& unitName) const
    {
        wxASSERT(simState != 0);
        tcGameObject* obj = simState->GetObjectByName(unitName);
        if (obj != 0)
        {
            return obj->mnID;
        }
        else
        {
            return -1;
        }
    }

    /**
    * Sets launcher item and quantity of unit
    */
    void tcScenarioInterface::SetUnitLauncherItem(const std::string& unitName, 
        unsigned int launcherIdx, const std::string& item, unsigned int quantity)
    {
        wxASSERT(simState);
        tcGameObject* parentObj = simState->GetObjectByName(unitName);
        if (tcPlatformObject* platform = dynamic_cast<tcPlatformObject*>(parentObj))
        {
            if (tcLauncher* launcher = platform->GetLauncher(launcherIdx))
            {
                if (quantity == 0)
                {
                    launcher->SetChildQuantity(0);
                }
                else if (launcher->IsItemCompatible(item))
                {
                    launcher->SetChildClass(item);
                    if (launcher->mpChildDBObj != 0)
                    {
                        launcher->SetChildQuantity(quantity);
                    }
                    else
                    {
                        launcher->SetChildQuantity(0);
                    }
                }
                else
                {
                    fprintf(stderr, "tcScenarioInterface::SetUnitLauncherItem - "
                        "%s not compatible with unit %s, launcher %d\n", item.c_str(),
                        unitName.c_str(), launcherIdx);
                }
            }
            else
            {
                fprintf(stderr, "tcScenarioInterface::SetUnitLauncherItem - "
                    "Bad launcher index (unit %s, launcher %d)\n",
                    unitName.c_str(), launcherIdx);
            }
        }
        else
        {
            fprintf(stderr, "tcScenarioInterface::AddToUnitMagazine - "
                "Unit not found or bad type (%s)\n", unitName.c_str());
        }
    }

    /**
    * Sets child unit loadout with compact text string command
    */
    void tcScenarioInterface::SetFlightDeckUnitLoadout(const std::string& parent, const std::string& child, 
            const std::string& loadoutCommand)
    {
        tcGameObject* parentObj = simState->GetObjectByName(parent);
        if (tcFlightOpsObject* flightOps = dynamic_cast<tcFlightOpsObject*>(parentObj))
        {
            tcGameObject* obj = flightOps->GetFlightPort()->GetObjectByName(child);
            if (tcPlatformObject* platform = dynamic_cast<tcPlatformObject*>(obj))
            {
                platform->SetLoadoutCommand(loadoutCommand);
            }
        }
    }


	bool tcScenarioInterface::AllianceExists(int alliance) const
	{
		if (alliance < 0) return false;

		return simState->mcSensorMap.MapExists((unsigned)alliance);
	}

    void tcScenarioInterface::CreateAlliance(int alliance, const std::string& name)
    {
        tcAllianceInfo* allianceInfo = tcAllianceInfo::Get();
        if ((alliance < 0)||(alliance >= allianceInfo->MAX_ALLIANCES))
        {
            fprintf(stderr, "Scenario error: Alliance out of range [0,%d]\n",
                allianceInfo->MAX_ALLIANCES-1);
            return;
        }

        simState->mcSensorMap.CreateMapForAlliance(alliance);
        allianceInfo->AddAlliance(unsigned char(alliance));
        allianceInfo->SetAllianceName(unsigned char(alliance), name);
        allianceInfo->SetAllianceDefaultCountry(unsigned char(alliance), name);
    }

    void tcScenarioInterface::SetAlliancePlayable(int alliance, bool state)
    {
        if (AllianceExists(alliance))
        {
            tcAllianceInfo* allianceInfo = tcAllianceInfo::Get();
            allianceInfo->SetAlliancePlayable(unsigned char(alliance), state);
        }
        else
        {
            fprintf(stderr, "tcScenarioInterface::SetAlliancePlayable - Alliance %d not found\n",
                alliance);
        }
    }

    bool tcScenarioInterface::IsAlliancePlayable(int alliance) const
    {
        if (AllianceExists(alliance))
        {
            tcAllianceInfo* allianceInfo = tcAllianceInfo::Get();
            return allianceInfo->IsAlliancePlayable(unsigned char(alliance));
        }
        else
        {
            fprintf(stderr, "tcScenarioInterface::IsAlliancePlayable - Alliance %d not found\n",
                alliance);
            return false;
        }
    }

    /**
    *  WEAPONS_HOLD = 0, WEAPONS_TIGHT = 1, WEAPONS_FREE = 2, ROE_ERROR = 99
    *  @see tcGoalTracker
    */
    tcAllianceROEInfo tcScenarioInterface::GetAllianceROE(int alliance) const
    {
		tcAllianceROEInfo result;

		result.airROE = 99;
		result.surfaceROE = 99;
		result.subROE = 99;
		result.landROE = 99;

        if (AllianceExists(alliance))
        {
			tcGoalTracker::ROEStatus roeStatus = tcGoalTracker::Get()->GetAllianceROE(alliance);
			result.airROE = roeStatus.airMode;
			result.surfaceROE = roeStatus.surfMode;
			result.subROE = roeStatus.subMode;
			result.landROE = roeStatus.landMode;
        }
        else
        {
            fprintf(stderr, "tcScenarioInterface::GetAllianceROE - Alliance %d not found\n",
                alliance);
        }

		return result;
    }

    /**
    *  WEAPONS_HOLD = 0, WEAPONS_TIGHT = 1, WEAPONS_FREE = 2, ROE_ERROR = 99
    *  @see tcGoalTracker
    */
    void tcScenarioInterface::SetAllianceROEByType(int alliance,int airRoe, int surfaceROE, int subROE, int landROE)
    {
        if (AllianceExists(alliance))
        {
            tcGoalTracker::Get()->SetAllianceROE(alliance, 
				tcGoalTracker::ROEMode(airRoe), tcGoalTracker::ROEMode(surfaceROE), 
				tcGoalTracker::ROEMode(subROE), tcGoalTracker::ROEMode(landROE));
        }
        else
        {
            fprintf(stderr, "tcScenarioInterface::SetAllianceROE - Alliance %d not found\n",
                alliance);
        }
    }

    /**
    *  WEAPONS_HOLD = 0, WEAPONS_TIGHT = 1, WEAPONS_FREE = 2, ROE_ERROR = 99
    *  @see tcGoalTracker
	*  Version sets all type ROE the same (for backward compatibility)
    */
    void tcScenarioInterface::SetAllianceROE(int alliance, int allRoe)
    {
        if (AllianceExists(alliance))
        {
            tcGoalTracker::Get()->SetAllianceROE(alliance, 
				tcGoalTracker::ROEMode(allRoe), tcGoalTracker::ROEMode(allRoe), 
				tcGoalTracker::ROEMode(allRoe), tcGoalTracker::ROEMode(allRoe));
        }
        else
        {
            fprintf(stderr, "tcScenarioInterface::SetAllianceROE - Alliance %d not found\n",
                alliance);
        }
    }


    void tcScenarioInterface::SetAllianceDefaultCountry(int alliance, const std::string& countryName)
    {
        if (AllianceExists(alliance))
        {
            tcAllianceInfo* allianceInfo = tcAllianceInfo::Get();
            allianceInfo->SetAllianceDefaultCountry(alliance, countryName);
            allianceInfo->SetAllianceName(alliance, countryName); // make country name same as alliance name for now
            simState->ResyncObjAlliance();
        }
        else
        {
            fprintf(stderr, "tcScenarioInterface::SetAllianceDefaultCountry - Alliance %d not found\n",
                alliance);
        }
    }

    std::string tcScenarioInterface::GetAllianceCountry(int alliance)
    {
        if (AllianceExists(alliance))
        {
            tcAllianceInfo* allianceInfo = tcAllianceInfo::Get();
            return std::string(allianceInfo->GetAllianceDefaultCountry(alliance));
        }
        else
        {
            return std::string("Error");
        }
    }

    tcScenarioUnit tcScenarioInterface::GetDefaultUnit()
    {
        tcScenarioUnit unit;
        unit.className = "Not defined";
        unit.unitName = "Not defined";
        unit.lat = 0;
        unit.lon = 0;
        unit.alt = 0;
        unit.heading = 12;
        unit.speed = 0.5;
        unit.throttle = 0.25;
        unit.cost = -123.0;
        return unit;
    }

    /**
    * @param lon reference longitude in deg
    * @param lat ref latitude in deg
    * @param min_alt minimum terrain elevation (depth negative) in meters
    * @param max_alt max terrain elevation in meters
    * @param rand_offset random offset in deg lon/lat at equator, 1 deg = 60 nmi
    * @see tcDatum
    */
    tcDatum tcScenarioInterface::GetRandomDatum(double lon, double lat, 
            float min_alt, float max_alt, float rand_offset)
    {
        tcDatum datum;
        wxASSERT(mapData);
        GeoPoint randomPoint = 
            mapData->GetRandomPointNear(lon, lat, rand_offset, min_alt, max_alt);
        datum.lon = C_180OVERPI*randomPoint.mfLon_rad;
        datum.lat = C_180OVERPI*randomPoint.mfLat_rad;
        datum.alt = randomPoint.mfAlt_m;
        return datum;
    }

    /**
    * @return a random "real world" platform name, or return a Temp ### name if none exists
    * @param referenceName if "real world" name doesn't exist, make a new name with referenceName + number, try to make this a sequential number
    */
    std::string tcScenarioInterface::GetRandomPlatformName(const std::string& databaseClass, const std::string& referenceName)
    {
        std::string result;

        tcDatabase* database = tcDatabase::Get();
        //wxArrayString arrayString = database->GetPlatformNames(databaseClass.c_str());

		tcDateTime dateTime = simState->GetDateTime();
		float dateYear = dateTime.GetFractionalYear();
		wxArrayString arrayString = database->GetPlatformNamesByDate(databaseClass.c_str(), dateYear);

        size_t nNames = arrayString.size();
        size_t random_offset = (rand() % std::max((size_t)1, nNames));
        for (size_t n=0; n<nNames; n++)
        {
            size_t idx = (n + random_offset) % nNames;

            std::string name_n(arrayString[idx].c_str());

            if (simState->GetObjectByName(name_n) == 0)
            {   // don't allow duplicate names
                result = name_n;
                return result;
            }
        }

        wxString root;
        wxString separator;
        long id = 0;
        bool isParsed = ParseUnitName(referenceName, root, separator, id);
        const long maxIdToTry = 30;
        if (isParsed)
        {
            for (long id_try=id+1; id_try<id+maxIdToTry; id_try++)
            {
                wxString name_try = wxString::Format("%s%s%d", root.c_str(), separator.c_str(), id_try);
                if (simState->GetObjectByName(name_try.ToStdString()) == 0)
                {
                    return std::string(name_try.ToAscii());
                }
            }
        }

        // default to old temp name behavior
        wxString tempName = wxString::Format("Temp %04d", rand() % 1000);
        result = tempName.c_str();

        if (simState->GetObjectByName(result) == 0)
        {
            return result;
        }
        else
        { // unlucky, try again
            tempName = wxString::Format("Temp %04d", rand() % 1000);
            result = tempName.c_str();
        }

        return result;
    }

    tcParsedUnitName tcScenarioInterface::GetParsedUnitName(const std::string& referenceName) const
    {
        tcParsedUnitName result;

        wxString root;
        wxString separator;
        long id;
        
        result.isValid = ParseUnitName(referenceName, root, separator, id);
        result.root = root.c_str();
        result.separator = separator.c_str();
        result.id = id;

        return result;
    }

    /**
    * @return true if referenceName can be parsed into <root> + <separator> + <number> form, e.g. Frog-1 is "Frog", "-", and 1
    */
    bool tcScenarioInterface::ParseUnitName(const std::string& referenceName, wxString& root, wxString& separator, long& id) const
    {
        wxString ref(referenceName.c_str());
        ref.Trim(true); // remove whitespace right
        ref.Trim(false); // remove whitespace left

        root.clear();
        separator = ' ';
        id = 0;

        bool parsingNumber = true;
        for (size_t n=0; (n<ref.size()) && parsingNumber; n++)
        {
            wxString sn(ref.Right(n+1));
            if (sn.IsNumber())
            {
                sn.ToLong(&id);
            }
            else
            {
                parsingNumber = false;
                wxChar left_char = sn.GetChar(0);
                if ((left_char == ' '))
                {
                    separator = sn.GetChar(0);
                    root = ref.Left(ref.size() - n - 1);
                }
                else
                {
                    root = ref.Left(ref.size() - n);
                    if (id < 0) // correct for dash separator interpreted as negative number
                    {
                        id = -id;
                        separator = '-';
                    }
                }
            }
        }

        return (id != 0);
    }

    /**
    * Copy tasks, waypoints from unitName1 to unitName2
    */
    void tcScenarioInterface::DuplicateUnitTasking(const std::string& unitName1, const std::string& unitName2)
    {
        tcPlatformObject* platform1 = dynamic_cast<tcPlatformObject*>(simState->GetObjectByName(unitName1));
        tcPlatformObject* platform2 = dynamic_cast<tcPlatformObject*>(simState->GetObjectByName(unitName2));

        if ((platform1 == 0) || (platform2 == 0)) return;

        // do brain copy
        tcGameStream brainState;
        platform1->brain->operator>>(brainState);
        platform2->brain->operator<<(brainState);

        // correct waypoint referencing
        ai::Nav* nav1 = platform1->brain->GetNavTask();
        ai::Nav* nav2 = platform2->brain->GetNavTask();
        if (nav1 != 0)
        {
            const std::vector<ai::Nav::WaypointData>& waypoints1 = nav1->GetWaypoints();
            std::vector<ai::Nav::WaypointData>& waypoints2 = nav2->GetWaypointsMutable();
            wxASSERT(waypoints1.size() == waypoints2.size());

            for (size_t n=0; n<waypoints1.size(); n++)
            {
                if (waypoints1[n].referencePlatform == platform1->mnID) // if 1 had self-reference, make 2 have self-ref
                {
                    waypoints2[n].referencePlatform = platform2->mnID;
                }
                nav2->UpdateRelativeWaypointCoordinate(n);
            }
        }
    }


	void tcScenarioInterface::GetStartTheater(double& lon_deg, double& lat_deg) const
	{
		 lon_deg = lon_theater_deg;
		 lat_deg = lat_theater_deg;
	}

	void tcScenarioInterface::SaveGame(const std::string& fileName)
	{
		wxString saveName = wxString(fileName.c_str());
		saveName = saveName.BeforeLast('.'); // .py extension is added by scenarioLogger

        saveName.Replace(wxT(" "), wxT("_"));
        saveName.Replace(wxT(")"), wxT(""));
        saveName.Replace(wxT("("), wxT(""));

		// extract scenario name from path
		wxString scenarioName = wxString(fileName.c_str()).AfterLast('/').BeforeFirst('.');
		//simState->SetScenarioName(scenarioName.c_str());
        //wxString scenarioName(simState->GetScenarioName());


		wxDateTime now = wxDateTime::Now();
		

        bool fileExists = wxFile::Exists(saveName.c_str());
        if (fileExists)
        {
            wxString s;
            s.Printf("Scenario file '%s' exists. Overwrite file?", saveName.c_str());
            wxMessageDialog confirmQuit(overlay, s.c_str(), "Confirm", wxOK | wxCANCEL, wxDefaultPosition);
            if (confirmQuit.ShowModal() != wxID_OK)
            {
                return;
            }
        }

		simState->SaveToPython(saveName.ToStdString());
        
      //  saveName = wxString::Format("scenarios//EditorSaved//%s_%d_%d_%02d%02d%02d_DAT",
		    //scenarioName.c_str(), now.GetMonth()+1, now.GetDay(), now.GetHour(), now.GetMinute(), now.GetSecond());
      //  tcGameSerializer gameSaver;
      //  gameSaver.SaveToBinary(saveName.c_str());
	}

    /**
    * Copies and sets root goal for alliance
    */
    void tcScenarioInterface::SetAllianceGoal(int alliance, tcGoal& goal)
    {
        wxASSERT(simState);
        wxASSERT(tcGoalTracker::Get());

        tcGoal *allianceGoal = goal.Clone();
		tcGoalTracker::Get()->SetAllianceGoal(alliance, allianceGoal);
    }

    tcGoalWrap tcScenarioInterface::GetAllianceGoal(int alliance)
    {
        return tcGoalWrap(tcGoalTracker::Get()->GetAllianceGoal(alliance));
    }

    tcGoalWrap tcScenarioInterface::GetGoalById(unsigned long id)
    {
        return tcGoalWrap(tcGoalTracker::Get()->LookupGoalById(id));
    }

    void tcScenarioInterface::AddChildGoalToId(unsigned long id, tcGoal& goal)
    {
        tcGoalTracker::Get()->AddChildGoalToId(id, &goal);
    }

    void tcScenarioInterface::DeleteGoalById(unsigned long id)
    {
        tcGoalTracker::Get()->DeleteGoalById(id);
    }

	bool tcScenarioInterface::IsUsingNATONames() const
	{
		return (tcOptions::Get()->natoNames != 0);
	}

	std::string tcScenarioInterface::GetDisplayName(const std::string& className)
	{
		return tcDatabase::Get()->GetDisplayName(className);
	}

    /**
    * Sets relationship between alliances
    * @param relationship "Friendly", "Neutral", "Hostile"
    */
    void tcScenarioInterface::SetAllianceRelationship(int alliance_a, int alliance_b, const std::string& relationship)
    {
        tcAllianceInfo::Affiliation affil = tcAllianceInfo::HOSTILE;

        if (relationship == "Hostile")
        {
            affil = tcAllianceInfo::HOSTILE;
        }
        else if (relationship == "Neutral")
        {
            affil = tcAllianceInfo::NEUTRAL;
        }
        else if (relationship == "Friendly")
        {
            affil = tcAllianceInfo::FRIENDLY;
        }
        else
        {
            fprintf(stderr, "tcScenarioInterface::SetAllianceRelationship - Bad relationship string (%s)\n",
                relationship.c_str());
            wxASSERT(false);
            return;
        }

        tcAllianceInfo::Get()->SetRelationship(unsigned char(alliance_a), unsigned char(alliance_b), affil);
    }

    void tcScenarioInterface::SetDateTime(int year, int month, int day, int hour, int min, int sec)
    {
        tcDateTime newTime(year, month, day, hour, min, sec);
        tcDateTime oldTime(simState->GetDateTime());

        simState->SetDateTime(newTime);

        tcGameObjIterator iter;
        for (iter.First();iter.NotDone();iter.Next())
        {
            tcGameObject* obj = iter.Get();
            if (tcFlightOpsObject* flightOps = dynamic_cast<tcFlightOpsObject*>(obj))
            {
                tcFlightPort* flightPort = flightOps->GetFlightPort();
                wxASSERT(flightPort != 0);
                if (tcMissionManager* missionManager = flightPort->GetMissionManager())
                {
                    missionManager->AdjustMissionsForNewStartDate(oldTime, newTime);
                }
            }
        }

    }

    void tcScenarioInterface::SetDateTimeByString(const char* s)
    {
        wxDateTime parsed;
        if (parsed.ParseDateTime(s) == 0)
        {
            fprintf(stderr, "tcScenarioInterface::SetDateTimeByString -- Failed to parse date time string (%s)\n",
                s);
            return;
        }

        int year = parsed.GetYear();
        int month = parsed.GetMonth()+1; // january is month 0 in wxDateTime
        int day = parsed.GetDay();
        int hour = parsed.GetHour();
        int minute = parsed.GetMinute();
        int second = parsed.GetSecond();
        
        SetDateTime(year, month, day, hour, minute, second);
        //simState->SetDateTime(tcDateTime(parsed.GetYear(), parsed.GetMonth()+1, parsed.GetDay(),
        //    parsed.GetHour(), parsed.GetMinute(), parsed.GetSecond()));
    }

	std::string tcScenarioInterface::GetScenarioDateAsString() const
	{
		std::string result;

		tcDateTime dt = simState->GetDateTime();
		result = dt.asString();

		return result;
	}

    void tcScenarioInterface::SetPerfectScore(float score)
    {
        tcGoalTracker::Get()->SetPerfectScore(score);
    }

    void tcScenarioInterface::SetScenarioDescription(std::string s)
    {
        simState->SetScenarioDescription(s);
    }

    void tcScenarioInterface::SetScenarioLoaded(bool state)
    {
        simState->SetScenarioLoaded(state);
    }

    void tcScenarioInterface::SetScenarioName(const std::string& s)
    {
        simState->SetScenarioName(s);
    }

    void tcScenarioInterface::SetScenarioLocked(bool state)
    {
        isScenarioLocked = state;
    }

    bool tcScenarioInterface::IsScenarioLocked() const
    {
        return isScenarioLocked;
    }

	void tcScenarioInterface::SetStartTheater(double lon_deg, double lat_deg)
	{
		lon_theater_deg = lon_deg;
		lat_theater_deg = lat_deg;

		ChangeMapTheater(lon_deg, lat_deg);
	}

	int tcScenarioInterface::GetUserAlliance() const
	{
		return simState->mpUserInfo->GetOwnAlliance();
	}

    void tcScenarioInterface::SetUserAlliance(int alliance)
    {
        if ((alliance < 0)||(alliance > 255))
        {
            fprintf(stderr, "Scenario error: Alliance out of range [0,255]\n");
            return;
        }

        // switch to next playable alliance, if not in edit or dev mode
        if (!IsAlliancePlayable(alliance) && !tcGameObject::IsEditMode() && !tcPlatformInterface::GetDeveloperMode())
        {
            bool searching = true;
            for (int n=alliance+1; (n<alliance+255) && searching; n++)
            {
                int allianceToTry = n % 256;
                if (IsAlliancePlayable(allianceToTry))
                {
                    alliance = allianceToTry;
                    searching = false;
                }
            }
        }

        simState->mpUserInfo->SetOwnAlliance(alliance);
        tcAllianceSensorMap* sensorMap = simState->mcSensorMap.GetMap(simState->mpUserInfo->GetOwnAlliance());
        if (sensorMap != 0)
        {
            tcSimPythonInterface::Get()->AttachSensorMap(sensorMap);
        }
		else
		{
			fprintf(stderr, "tcScenarioInterface::SetUserAlliance - Alliance %d does not exist? Check scenario\n", alliance);
			wxASSERT(false);
		}
    }

    /***** tcDirector interface for briefing events *****/
    // time/mode events

    /**
    * This method should not be needed since LoadScenario
    * calls ClearEvents before each load.
    * @see tcSimPythonInterface::LoadScenario
    */
    void tcScenarioInterface::ClearEvents()
    {
        wxASSERT(director);
        director->ClearEvents();

		ClearSimpleBriefing();
    }

    /**
    * Looks up platform id by unitName and creates game command event
    * to hook object. If unitName is not found no event is created.
    */
    void tcScenarioInterface::HookPlatform(std::string unitName)
    {
        wxASSERT(director);
        wxASSERT(simState);
        tcGameObject* obj = simState->GetObjectByName(unitName);
        if (obj == NULL) 
        {
            std::cerr << "HookPlatform: Object not found ("
                << unitName << ")\n";
            return;
        }
        director->AddEvent(new tcGameCommandEvent(ID_NEWHOOK, eventTime, obj->mnID));
    }

    /**
    * Pauses game. This should be called at the start of every
    * briefing.
    */
    void tcScenarioInterface::Pause()
    {
        wxASSERT(director);
        director->AddEvent(new tcGameCommandEvent(ID_SETPAUSE, eventTime, 1));
    }

    /**
    * Resumes (unpauses) game. This should be called at the end of
    * every briefing.
    */
    void tcScenarioInterface::Resume()
    {
        if (tcGameObject::IsEditMode()) return; // a hack so we don't leave edit mode for ctrl-click scenario load

        wxASSERT(director);
        director->AddEvent(new tcGameCommandEvent(ID_SETPAUSE, eventTime, 0));
    }

    void tcScenarioInterface::Set3DMode(int modeCode)
    {
        wxASSERT(director);
        director->AddEvent(new tcGameCommandEvent(ID_SET3D, eventTime, modeCode)); 
    }

    void tcScenarioInterface::SetBriefingMode(bool state)
    {
        wxASSERT(director);
        director->AddEvent(new tcGameCommandEvent(ID_SETBRIEFING, eventTime, state));
    }

    void tcScenarioInterface::SetEventTime(double t)
    {
        wxASSERT(director);
        eventTime = t;
    }


    // audio events
    void tcScenarioInterface::PauseAudio()
    {
        wxASSERT(director);
        director->AddEvent(new tcMusicEvent("","pause",0,eventTime,eventTime));
    }

    /**
    * @param audioName name of ogg file to play without .ogg extension. 
    * @param audioName So "test1.ogg" would be "test1"
    * @param seekTime time in seconds within audio file 
    */
    void tcScenarioInterface::PlayAudio(const std::string& audioName, double seekTime)
    {
        wxASSERT(director);
        director->AddEvent(new tcMusicEvent(audioName,"play",seekTime,eventTime,eventTime));
    }

    void tcScenarioInterface::PlayEffect(const std::string& effectName)
    {
        wxASSERT(director);
        director->AddEvent(new tcSoundEffectEvent(eventTime, effectName));
    }

    /**
    * @param seekTime time in seconds within audio file 
    */
    void tcScenarioInterface::SeekAudio(double seekTime)
    {
        wxASSERT(director);
        director->AddEvent(new tcMusicEvent("","seek",seekTime,eventTime,eventTime));
    }


    /**
    * Send command through command queue, used for special commands to game engine
    * such as activating the flight deck control panel. 
    */
    void tcScenarioInterface::SendCommand(const std::string& command)
    {
        if (commandQueue == 0)
        {
            wxASSERT(false);
            return;
        }
        commandQueue->AddCommand(command.c_str(),-1);
    }



    // text console and map events

    /**
	* Changes tactical map theater. The theater is the high resolution view
	* area that is accessible from the tactical map.
	*
    * @param lon_deg longitude in deg for center of new theater
    * @param lat_deg latitude in deg for center of new theater
    */
	void tcScenarioInterface::ChangeMapTheater(double lon_deg, double lat_deg)
	{
        wxASSERT(overlay != 0);
        wxCommandEvent command(wxEVT_COMMAND_BUTTON_CLICKED, ID_SETTHEATER);    
        command.SetEventObject(overlay);

        long lon = (lon_deg > 0) ? long(8.0f*lon_deg + 0.5f) : long(8.0f*lon_deg - 0.5f);
        long lat = (lat_deg > 0) ? long(8.0f*lat_deg + 0.5f) : long(8.0f*lat_deg - 0.5f);

        long coordField = (lat << 16) + (lon & 0xFFFF);
        command.SetExtraLong(coordField); // 2.6.3 m_extraLong = coordField;
        overlay->GetEventHandler()->AddPendingEvent(command);

  //      wxASSERT(director);

		//// tcMapViewEvent with lonSpan_deg = 0 is used for theater change
  //      director->AddEvent(new tcMapViewEvent(eventTime, 
  //          lon_deg, lat_deg, 0, true));
	}

    /**
    * @param lon_deg longitude in deg for center of view
    * @param lat_deg latitude in deg for center of view
    * @param lonSpan_deg longitude span in deg for width of view
    */
    void tcScenarioInterface::ChangeMapView(double lon_deg, double lat_deg, 
        double lonSpan_deg)
    {
        wxASSERT(director);

        director->AddEvent(new tcMapViewEvent(eventTime, 
            lon_deg, lat_deg, lonSpan_deg, true)); // true for 5th arg to adjust tactical map
    }

    /**
    * @param lon_deg longitude in deg for center of view
    * @param lat_deg latitude in deg for center of view
    * @param lonSpan_deg longitude span in deg for width of view
    */
    void tcScenarioInterface::ChangeWorldMapView(double lon_deg, double lat_deg, 
        double lonSpan_deg)
    {
        wxASSERT(director);

        director->AddEvent(new tcMapViewEvent(eventTime, 
            lon_deg, lat_deg, lonSpan_deg, false)); // false for 5th arg to adjust world map
    }

    /**
    * Sets the start view of the tactical map, useful for making sure start view includes
    * friendly units or starts a particular way
    */
    void tcScenarioInterface::SetStartView(double lon_deg, double lat_deg, double lonSpan_deg)
    {
        wxASSERT(director);

        director->AddEvent(new tcMapViewEvent(0.1f, 
            lon_deg, lat_deg, lonSpan_deg, true));
        director->AddEvent(new tcMapViewEvent(0.1f, 
            lon_deg, lat_deg, 30.0f, false));
    }

    void tcScenarioInterface::ChannelMessage(const std::string& message, const std::string& channel, unsigned int alliance)
    {
        wxASSERT(director);
        director->AddEvent(new tcMessageTextEvent(message, channel, alliance, eventTime));
    }

    void tcScenarioInterface::ConsoleText(const std::string& text)
    {
        tcMessageCenter::Get()->ConsoleMessage(text);
    }

    void tcScenarioInterface::MapText(const std::string& text, double lon_deg, double lat_deg, 
        double duration, int effect)
    {
        wxASSERT(director);

        director->AddEvent(new tcMapTextEvent(text, eventTime, eventTime+duration,
            lon_deg, lat_deg, effect));
    }

    void tcScenarioInterface::OverlayText(const std::string& text, 
                       double lon_deg, double lat_deg, const std::string& color)
    {
        wxASSERT(overlay);

        tcMapTextObject* obj = new tcMapTextObject(text, lon_deg, lat_deg);

        obj->ConfigureWithString(color);

        overlay->AddMapObject(obj);
    }

     void tcScenarioInterface::OverlayTextInteractive(const std::string& text, double lon_deg, double lat_deg)
     {
        wxASSERT(overlay);

        tcMapTextObject* obj = new tcMapTextObject(text, lon_deg, lat_deg);
        obj->SetColor(Vec4(0, 0, 0, 1));
        obj->SetInteractive(true);

        overlay->AddMapObject(obj);
     }


    void tcScenarioInterface::FlybyCamera(const std::string& unitName, double duration, 
        float az1_deg, float az2_deg,
        float el1_deg, float el2_deg, float r1_m, float r2_m)
    {
        wxASSERT(director);

        // repeated code from HookPlatform, refactor this
        wxASSERT(simState);
        tcGameObject* obj = simState->GetObjectByName(unitName);
        if (obj == NULL) 
        {
            std::cerr << "FlybyCamera: Object not found ("
                << unitName << ")\n";
            return;
        }
        director->AddEvent(new tcFlybyCameraEvent(eventTime, eventTime+duration, obj->mnID,
            C_PIOVER180*az1_deg, C_PIOVER180*az2_deg,
            C_PIOVER180*el1_deg, C_PIOVER180*el2_deg,
            r1_m, r2_m));
    }

    void tcScenarioInterface::TrackCamera(const std::string& unitName, double duration, 
        float x1, float x2, float y1, float y2, float z1, float z2)
    {
        wxASSERT(director);

        // repeated code from HookPlatform, refactor this
        wxASSERT(simState);
        tcGameObject* obj = simState->GetObjectByName(unitName);
        if (obj == NULL) 
        {
            std::cerr << "TrackCamera: Object not found ("
                << unitName << ")\n";
            return;
        }
        director->AddEvent(new tcTrackCameraEvent(eventTime, eventTime+duration, obj->mnID,
            x1, x2, y1, y2, z1, z2));
    }

    void tcScenarioInterface::Text3D(const std::string& text, double duration, 
        float x, float y, float size, int effect)
    {
        wxASSERT(director);

        director->AddEvent(new tc3DTextEvent(text, eventTime, eventTime+duration,
            x, y, size, effect));
    }

    /**
    * workaround to construct goal class
    */
    tcCompoundGoal tcScenarioInterface::CompoundGoal(int type)
    {
        tcCompoundGoal goal(type);
        return goal;
    }

    /**
    * workaround to construct goal class
    */
    tcTimeGoal tcScenarioInterface::TimeGoal()
    {
        tcTimeGoal goal;
        return goal;
    }

    /**
    * workaround to construct goal class
    */
    tcDestroyGoal tcScenarioInterface::DestroyGoal(const std::string& target)
    {
        tcDestroyGoal goal(target);
        return goal;
    }

	tcProtectGoal tcScenarioInterface::ProtectGoal(const std::string& target)
	{
		tcProtectGoal goal(target);
		return goal;
	}

    tcAreaGoal tcScenarioInterface::AreaGoal()
    {
		tcAreaGoal goal;
		return goal;
    }

	void tcScenarioInterface::ClearSimpleBriefing()
	{
		simpleBriefingText.clear();
	}

	const std::string& tcScenarioInterface::GetSimpleBriefing(int alliance) const
	{
		static std::string errorText = "No briefing found";

		std::map<int, std::string>::const_iterator iter = 
			simpleBriefingText.find(alliance);

		if (iter != simpleBriefingText.end())
		{
			return iter->second;
		}
		else
		{
			return errorText;
		}
	}

	void tcScenarioInterface::SetSimpleBriefing(int alliance, const std::string& briefingText)
	{
		simpleBriefingText[alliance] = briefingText;
	}

    /**
    * @return list of units within box defined by (lon1, lat2) and (lon2, lat2) for matching alliance
    * @param alliance set to -1 or 0 to include all alliance values, otherwise filters by <alliance>
    */
    tcStringArray tcScenarioInterface::GetUnitList(float lon1_rad, float lat1_rad, float lon2_rad, float lat2_rad, int alliance)
    {
        tcStringArray unitList;

        tcGeoRect region;
        if (lat2_rad > lat1_rad)
        {
            region.Set(lon1_rad, lon2_rad, lat1_rad, lat2_rad);
        }
        else
        {
            region.Set(lon1_rad, lon2_rad, lat2_rad, lat1_rad);
        }

        tcGameObjIterator iter(region);
        if (alliance > 0)
        {
            iter.SetAllianceFilter((unsigned int)alliance);
        }

        for (iter.First();iter.NotDone();iter.Next())
        {
            tcGameObject* obj = iter.Get();

            unitList.PushBack(std::string(obj->GetName()));
        }

        return unitList;
    }


	tcStringArray tcScenarioInterface::GetPlatformListByClass(const std::string& classString)
	{
		tcStringArray stringArray;

        float scenarioYear = simState->GetDateTime().GetFractionalYear(); // fractional year of scenario
        std::string sideCountry = tcAllianceInfo::Get()->GetAllianceDefaultCountry(tcUserInfo::Get()->GetOwnAlliance());

        database::tcDatabase* database = tcDatabase::Get();
        if (database->IsUsingDynamicLoad())
        { // database isn't populated yet, so do something different
            unsigned int classMask = 0;
            tcStringArray tables; // database tables to search for platforms

            if (classString == "Sub") 
            {
                classMask = PTYPE_SUBSURFACE;
                tables.AddString("sub");
            }
            else if (classString == "Surface")
            {
                classMask = PTYPE_SURFACE;
                tables.AddString("ship");
            }
            else if (classString == "AirFW")
            {
                classMask = PTYPE_FIXEDWING;
                tables.AddString("air");
                tables.AddString("simpleair");
            }
            else if (classString == "Helo")
            {
                classMask = PTYPE_HELO;
                tables.AddString("simpleair");
            }
            else if (classString == "Land")
            {
                classMask = PTYPE_GROUND;
                tables.AddString("ground");
            }
            else if (classString == "Mine")
            {
                classMask = PTYPE_WATERMINE;
                tables.AddString("torpedo");
            }
            else
            {
                fprintf(stderr, "tcScenarioInterface::GetPlatformListByClass - "
                    "unrecognized classString (%s)\n", classString.c_str());
                return stringArray;
            }

            for (size_t k=0; k<tables.Size(); k++)
            {
                std::vector<tcDatabase::RecordSummary> records = database->GetTableSummary(tables.GetString(k));
                for (size_t n=0; n<records.size(); n++)
                {
                    unsigned int classificationId = records[n].classificationId;

                    bool coarsePasses = (classificationId & classMask & 0xFFF0) != 0;
                    bool finePasses = (classificationId & classMask & 0x000F) != 0;

                    bool yearPasses = !filterByYear ||
                        ((records[n].yearStart <= scenarioYear) && (records[n].yearStop >= scenarioYear));

                    bool countryPasses = !filterByCountry || (records[n].country.size() == 0) || (sideCountry.size() == 0) ||
                        (records[n].country == sideCountry);

                    // if mask has fine classification set then use it, otherwise ignore
                    bool passes = false;
                    if (classMask & 0x000F) 
                    {
                        passes = coarsePasses && finePasses && yearPasses && countryPasses;
                    }
                    else
                    {
                        passes = coarsePasses && yearPasses && countryPasses;
                    }

                    if (passes)
                    {
                        stringArray.AddString(records[n].databaseClass);
                    }
                }
            }

            ApplySpecialFiltering(classString, stringArray);

            stringArray.Sort();

            return stringArray;
        }


		//#define PTYPE_UNKNOWN 0x0000
		//#define PTYPE_SURFACE 0x0010
		//#define PTYPE_SMALLSURFACE 0x0011
		//#define PTYPE_LARGESURFACE 0x0012
		//#define PTYPE_AIR 0x0020
		//#define PTYPE_FIXEDWING 0x0021
		//#define PTYPE_HELO 0x0022
		//#define PTYPE_MISSILE 0x0040
		//#define PTYPE_SUBSURFACE 0x0080
		//#define PTYPE_SUBMARINE 0x0081
		//#define PTYPE_TORPEDO 0x0082
		//#define PTYPE_SONOBUOY 0x0084
		//#define PTYPE_GROUND 0x0100
		//#define PTYPE_BALLISTIC 0x0200

		unsigned int classMask = 0;

		if (classString == "Sub") 
		{
			classMask = PTYPE_SUBMARINE;
		}
		else if (classString == "Surface")
		{
			classMask = PTYPE_SURFACE;
		}
		else if (classString == "AirFW")
		{
			classMask = PTYPE_FIXEDWING;
		}
		else if (classString == "Helo")
		{
			classMask = PTYPE_HELO;
		}
		else if (classString == "Land")
		{
			classMask = PTYPE_GROUND;
		}
        else if (classString == "Mine")
        {
            classMask = PTYPE_WATERMINE;
        }
		else
		{
			fprintf(stderr, "tcScenarioInterface::GetPlatformListByClass - "
				"unrecognized classString (%s)\n", classString.c_str());
			return stringArray;
		}

		tcDatabaseIterator iter(classMask);
        if (filterByYear)
        {
            iter.SetFilterYear(scenarioYear);
        }
        if (filterByCountry)
        {
            iter.SetFilterCountry(sideCountry);
        }

		for (iter.First(); !iter.IsDone(); iter.Next())
		{
			tcDatabaseObject* obj = iter.Get();
			wxASSERT(obj);
			wxASSERT(obj->mnKey != -1);
	
			stringArray.AddString(obj->mzClass.c_str());
		}

        ApplySpecialFiltering(classString, stringArray);

		return stringArray;

	}

    void tcScenarioInterface::ApplySpecialFiltering(const std::string& className, tcStringArray& stringArray)
    {
        return; // should not need this anymore
        if (className == "Mine")
        {
            tcDatabase* database = tcDatabase::Get();
            tcStringArray filteredArray;
            for (size_t n=0; n<stringArray.Size(); n++)
            {
                std::string objectName(stringArray.GetString(n));
                if (tcTorpedoDBObject* torpedoData = dynamic_cast<tcTorpedoDBObject*>(database->GetObject(objectName)))
                {
                    bool isMine = (torpedoData->weaponType == tcTorpedoDBObject::BOTTOM_MINE) ||
                                  (torpedoData->weaponType == tcTorpedoDBObject::BOTTOM_MINE_CAPTOR);
                    if (isMine)
                    {
                        filteredArray.AddString(objectName);
                    }
                }
            }
            stringArray = filteredArray;
        }
        else
        {
            return;
        }
    }

    void tcScenarioInterface::SetFilterByYear(bool state)
    {
        filterByYear = state;
    }

    bool tcScenarioInterface::GetFilterByYear() const
    {
        return filterByYear;
    }

    void tcScenarioInterface::SetFilterByCountry(bool state)
    {
        filterByCountry = state;
    }

    bool tcScenarioInterface::GetFilterByCountry() const
    {
        return filterByCountry;
    }

    /**
    * This must be called before any setup is performed on the simulation
    * e.g. creating sensor maps, scenario description, etc. Since this method
    * clears the simulation state.
    */
    void tcScenarioInterface::LoadDatabaseMod(const std::string& fileName)
    {
        bool scenarioError =
            (simState->mcSensorMap.GetMapCount() > 0) ||
            (strlen(simState->GetScenarioDescription()) > 0) ||
            (simState->IsScenarioLoaded()) ;
        
        if (scenarioError)
        {
            wxMessageBox("LoadDatabaseMod must be called at top of scenario file "
                "BEFORE any scenario setup is performed. Fix this and restart.", "Scenario Error", wxICON_ERROR);
            return;
        }

        simState->Clear();
        database::tcDatabase::Get()->UpdateSql(fileName);
    }

    void tcScenarioInterface::RestoreDefaultDatabase()
    {
        simState->Clear();
		database::tcDatabase::Get()->SerializeSql("", true); // reload default database
    }


    void tcScenarioInterface::SetAirGroupName(const std::string& groupName)
    {
        if (groupName.length() > 1)
        {
            airGroupName = groupName;
            unitId = 1; // reset unit ID
        }
    }

    std::string tcScenarioInterface::GetAirGroupName() const
    {
        return airGroupName;
    }

    unsigned int tcScenarioInterface::GetAirUnitId() const
    {
        return unitId;
    }

    void tcScenarioInterface::SetAirGroupCount(unsigned int n)
    {
        airGroupCount = n;
    }

    unsigned int tcScenarioInterface::GetAirGroupCount() const
    {
        return airGroupCount;
    }

    void tcScenarioInterface::SetMagazineAddCount(unsigned int n)
    {
        magazineAddCount = n;
    }

    unsigned int tcScenarioInterface::GetMagazineAddCount() const
    {
        return magazineAddCount;
    }

    void tcScenarioInterface::SetIncludeProbability(const std::string& unit, float prob)
    {
        tcScenarioRandomizer* randomizer = tcScenarioRandomizer::Get();
        randomizer->SetIncludeProbability(unit, prob);
    }

    float tcScenarioInterface::GetIncludeProbability(const std::string& unit) const
    {
        tcScenarioRandomizer* randomizer = tcScenarioRandomizer::Get();
        return randomizer->GetIncludeProbability(unit);
    }

    /**
    * Done this way to allow loading all units when loading in edit mode
    */
    bool tcScenarioInterface::IncludeUnit(float prob) const
    {
        return (tcGameObject::IsEditMode() || (randf() < prob));
    }

    void tcScenarioInterface::AddRandomBox(const std::string& unit, float lon1_deg, float lon2_deg, float lat1_deg, float lat2_deg)
    {
        tcScenarioRandomizer* randomizer = tcScenarioRandomizer::Get();
        tcRect box(C_PIOVER180*lon1_deg, C_PIOVER180*lon2_deg, C_PIOVER180*lat1_deg, C_PIOVER180*lat2_deg);
        randomizer->AddRandomBox(unit, box);
    }

    void tcScenarioInterface::SetSeaState(unsigned int val)
    {
        tcSonarEnvironment::Get()->SetSeaState(val);
    }

    unsigned int tcScenarioInterface::GetSeaState() const
    {
        return tcSonarEnvironment::Get()->GetSeaState();
    }

    /**
    * Set SVP using string "depth1_m, speed1_mps, depth2_m, speed2_mps, ..."
    */
    void tcScenarioInterface::SetSVP(const std::string& s)
    {
        wxString s2(s.c_str());

        std::vector<double> depth_m;
        std::vector<double> speed_mps;

        unsigned iteration = 0;
        while ((s2.size() > 0) && (iteration++ < 16))
        {
            wxString s_depth = s2.BeforeFirst(',');
            s2 = s2.AfterFirst(',');
            wxString s_speed = s2.BeforeFirst(',');
            s2 = s2.AfterFirst(',');

            double depth_n = -1.0;
            double speed_n = -1.0;
            bool depth_valid = s_depth.ToDouble(&depth_n);
            bool speed_valid = s_speed.ToDouble(&speed_n);

            depth_valid = depth_valid && (depth_n >= 0);
            speed_valid = speed_valid && (speed_n >= 1000.0);

            if (depth_valid && speed_valid)
            {
                depth_m.push_back(depth_n);
                speed_mps.push_back(speed_n);
            }
        }

        if ((depth_m.size() < 2) || (depth_m.size() != speed_mps.size()))
        {
            wxASSERT(false);
            fprintf(stderr, "tcScenarioInterface::SetSVP - invalid SVP string\n");
            return;
        }

        tcSonarEnvironment::Get()->ClearSVP();

        for (size_t n=0; n<depth_m.size(); n++)
        {
            tcSonarEnvironment::Get()->AddSVPPoint(depth_m[n], speed_mps[n]);
        }
    }

	/**
	* use a preset template for SVP, surface loss, bottom loss
	* @param id 0-simple, 1-winter, 2-spring, 3-summer, 4-autumn
	*/
	void tcScenarioInterface::SetSonarTemplate(int id)
	{
		tcSonarEnvironment::Get()->SetTemplate(id);
	}

	int tcScenarioInterface::GetSonarTemplate() const
	{
		return tcSonarEnvironment::Get()->GetTemplate();
	}

	unsigned int tcScenarioInterface::GetNumberSonarTemplates() const
	{
		return tcSonarEnvironment::Get()->GetNumberTemplates();
	}

    std::string tcScenarioInterface::GetTemplateName(unsigned int id) const
	{
		return tcSonarEnvironment::Get()->GetTemplateName(id);
	}

	void tcScenarioInterface::SetProgressReporting(wxProgressDialog* dlg)
	{
		progressDialog = dlg;
	}


	tcScenarioInterface::tcScenarioInterface()
		: lon_theater_deg(0),
		  lat_theater_deg(0),
		  eventTime(0),
		  sideCode(0),
          isScenarioLocked(false),
          airGroupName("Temp"),
          unitId(1),
          airGroupCount(1),
          magazineAddCount(10),
		  progressDialog(0),
          filterByYear(false),
          filterByCountry(false)
	{
	}

	tcScenarioInterface::~tcScenarioInterface()
	{
	}


}

