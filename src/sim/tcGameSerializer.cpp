/** 
**  @file tcGameSerializer.cpp 
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

#include "tcGameSerializer.h"
#include "tcSimState.h"
#include "tcGameStream.h"
#include "tcAllianceInfo.h"
#include "tcGameObjIterator.h"
#include "tcCommandQueue.h"
#include "tcGoalTracker.h"
#include "tcTacticalMapView.h"
#include "tcWorldMapView.h"
#include "tcMapOverlay.h"
#include "tcSonarEnvironment.h"

#include <wx/xml/xml.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


tcTacticalMapView* tcGameSerializer::tacticalMap = 0;
tcWorldMapView* tcGameSerializer::worldMap = 0;

void tcGameSerializer::AttachMapViews(tcTacticalMapView* tactical, tcWorldMapView* world)
{
    tacticalMap = tactical;
    worldMap = world;
}


void tcGameSerializer::SaveToBinary(const char* fileName)
{
    tcGameStream stream;
    stream.SetDirection(tcStream::INPUT);
    stream.SetVersionId(currentVersion);


    stream.WriteCheckValue(777);
    stream.WriteCheckValue(888);

    // save tcDatabase
    tcDatabase::Get()->operator>>(stream);

    // save tcAllianceInfo
    tcAllianceInfo::Get()->operator>>(stream);

    tcUserInfo::Get()->operator>>(stream);

    // save SensorMap
    tcSimState* simState = tcSimState::Get();
    simState->mcSensorMap >> stream;

    // save tcSimState
    SaveSimObjects(simState, stream);
    SaveSimOther(simState, stream);

    stream.WriteCheckValue(87135);

    // save tcGoalTracker
    tcGoalTracker::Get()->operator>>(stream);

    // save map view info
    SaveMapView(stream);

    SaveHookInfo(stream);

    tcSonarEnvironment::Get()->operator>>(stream);

    // write stream to file
    stream.SetDirection(tcStream::OUTPUT);
    stream.SaveToFile(fileName);
    
}

void tcGameSerializer::LoadFromBinary(const char* fileName)
{
    tcSimState* simState = tcSimState::Get();
    simState->Clear();

    // load stream from file
    tcGameStream stream;
    stream.LoadFromFile(fileName);
    stream.SetDirection(tcStream::OUTPUT);

    bool valid = stream.ReadCheckValue(777);
    valid = valid && stream.ReadCheckValue(888);
    if (!valid) return;

    int streamVersion = stream.GetVersionId();
    if ((streamVersion != currentVersion))
    {
        wxString msg;
        msg.Printf("Old save file format (version %d) may not be compatible, try to load anyway?", streamVersion);

        wxMessageDialog confirmLoad(tacticalMap, msg, "Confirm", wxOK | wxCANCEL | wxICON_EXCLAMATION, wxDefaultPosition);
        if (confirmLoad.ShowModal() != wxID_OK)
        {
            return;
        }
    }

    // load tcDatabase
    tcDatabase::Get()->operator<<(stream);

    // load tcAllianceInfo
    tcAllianceInfo::Get()->operator<<(stream);

    tcUserInfo::Get()->operator<<(stream);

    // load SensorMap
    simState->mcSensorMap << stream;

    // load tcSimState
    if (!LoadSimObjects(simState, stream)) return;
    if (!LoadSimOther(simState, stream)) return;

    stream.ReadCheckValue(87135);

    // tcGoalTracker
    tcGoalTracker::Get()->operator<<(stream);

    // load map view info
    if (!LoadMapView(stream)) return;

    if (!LoadHookInfo(stream)) return;

    tcSonarEnvironment::Get()->operator<<(stream);

    simState->SetScenarioLoaded(true);


}


void tcGameSerializer::SaveMapView(tcGameStream& stream)
{
    tcMapData* mapData = tcMapData::Get();
    int theaterDecimation = mapData->GetTheaterDecimation();
    stream << theaterDecimation;

    // world map
    tcPoint theaterCenter_deg = worldMap->GetTheaterCenter();

    stream << theaterCenter_deg.x;
    stream << theaterCenter_deg.y;

    stream << worldMap->mfLonCenter;
    stream << worldMap->mfLatCenter;
    stream << worldMap->mfLonWidth;

    worldMap->mrectTheater >> stream;

    // tactical map
    tacticalMap->mrectViewBounds >> stream;

    stream << tacticalMap->mfLonCenter;
    stream << tacticalMap->mfLatCenter;
    stream << tacticalMap->mfLonWidth;

    // tactical overlay
    tacticalMap->GetMapOverlay()->operator>>(stream);
}

bool tcGameSerializer::LoadMapView(tcGameStream& stream)
{
    int theaterDecimation;
    stream >> theaterDecimation;
    tcMapData* mapData = tcMapData::Get();
    mapData->SetTheaterDecimation(theaterDecimation);

    // world map
    float lon_center_deg, lat_center_deg;
    stream >> lon_center_deg;
    stream >> lat_center_deg;
    worldMap->ChangeTheaterNow(lon_center_deg, lat_center_deg);
    tacticalMap->Refresh();


    float worldLonCenter;
    float worldLatCenter;
    float worldLonWidth;
    stream >> worldLonCenter;
    stream >> worldLatCenter;
    stream >> worldLonWidth;
    worldMap->SetView(tcPoint(worldLonCenter, worldLatCenter), worldLonWidth);

    tcGeoRect r;
    r << stream;
    worldMap->SetTheater(r);
    

    // tactical map
    tacticalMap->mrectViewBounds << stream;

    float tacticalLonCenter; // rad
    float tacticalLatCenter;
    float tacticalLonWidth;
    stream >> tacticalLonCenter;
    stream >> tacticalLatCenter;
    stream >> tacticalLonWidth;
    tacticalMap->SetView(tcPoint(tacticalLonCenter, tacticalLatCenter), tacticalLonWidth);

    // tactical overlay
    tacticalMap->GetMapOverlay()->operator<<(stream);

    return true;
}

bool tcGameSerializer::LoadHookInfo(tcGameStream& stream)
{
    unsigned int nHooked;
    stream >> nHooked;
    if (nHooked > 255) return false;

    std::vector<long> hookedId;

    for (unsigned int n=0; n<nHooked; n++)
    {
        long id;
        stream >> id;
        hookedId.push_back(id);
    }

    tacticalMap->SetGroupHook(hookedId);
    tacticalMap->SendGroupHookMessage();

    return true;
}

void tcGameSerializer::SaveHookInfo(tcGameStream& stream)
{
    std::vector<long> hookedId = tacticalMap->GetHookedGroup();
    unsigned int nHooked = hookedId.size();
    stream << nHooked;
    for (unsigned int n=0; n<nHooked; n++)
    {
        stream << hookedId[n];
    }
}


void tcGameSerializer::SaveSimObjects(tcSimState* simState, tcGameStream& stream)
{
    // go through game objects, count them (could just get size I suppose)
    // and write the count to the stream
    tcGameObjIterator iterCount;
    unsigned int nObjects = 0;
    for (iterCount.First();iterCount.NotDone();iterCount.Next())
    {
        nObjects++;
    }
    stream << nObjects;

    // repeat and write data for each object
    tcGameObjIterator iter;
    for (iter.First();iter.NotDone();iter.Next())
    {
        tcGameObject* obj = iter.Get();

        std::string databaseClass = obj->mpDBObject->mzClass.c_str();
        stream << databaseClass;
        stream << obj->mnID;

        *obj >> stream;

        stream.WriteCheckValue(123);
    }
	
}

/**
* @return true if successful
*/
bool tcGameSerializer::LoadSimObjects(tcSimState* simState, tcGameStream& stream)
{
    tcDatabase* database = tcDatabase::Get();

    unsigned int nObjects;
    stream >> nObjects;

    for (unsigned int k=0; k<nObjects; k++)
    {
        std::string databaseClass;
        stream >> databaseClass;

        long id;
        stream >> id;

        tcDatabaseObject* dataObj = database->GetObject(databaseClass);
        if (dataObj == 0)
        {
            wxString errorMessage = 
                wxString::Format("Error while loading binary save file. Could not find class name \"%s\" in database, "
                "\"%s\" may be incompatible with database\n", 
                databaseClass.c_str(), simState->GetScenarioName());

            fprintf(stderr, errorMessage.c_str());
            return false;
        }

        tcGameObject* obj = simState->CreateGameObject(dataObj);
        if (obj == 0)
        {
            fprintf(stderr, "Error while loading binary save file. Game obj creation error\n");
            return false;
        }
        obj->mnID = id; // set here otherwise parent id isn't valid during addchild calls

        *obj << stream;

        stream.ReadCheckValue(123);

        simState->AddPlatformWithKey(obj, id);
    }


    return true;

}



void tcGameSerializer::SaveSimOther(tcSimState* simState, tcGameStream& stream)
{
    std::string scenName = (char*)&(simState->msScenarioInfo.mzName);
    stream << scenName;

    std::string scenDescription = (char*)&(simState->msScenarioInfo.mzDescription);
    stream << scenDescription;

    float gameTime = simState->GetTime();
    stream << gameTime;

    tcDateTime gameDateTime = simState->GetDateTime();
    gameDateTime >> stream;


    stream << simState->mfLastSensorUpdate;
    stream << simState->mfLastSensorAgeOut;
    stream << simState->mfLastTileAgeOut;
    stream << simState->lastLandingStateUpdate;

    int multiplayerMode = (int)simState->multiplayerMode;
    stream << multiplayerMode;


    //simState->mpCommandInterface->operator>>(stream);

    size_t nFlightportPlatforms = simState->flightportPlatforms.size();
    stream << nFlightportPlatforms;
    for (size_t k=0; k<nFlightportPlatforms; k++)
    {
        stream << simState->flightportPlatforms[k];
    }

    size_t nLandingPlatforms = simState->landingPlatforms.size();
    stream << nLandingPlatforms;
    for (size_t k=0; k<nLandingPlatforms; k++)
    {
        stream << simState->landingPlatforms[k];
    }

	stream << tcGameObject::launchedCounter;

	// save tcSensorState static vars
	stream << tcSensorState::nextSensorId;
	for (int n=0; n<tcSensorState::N_ERROR_FACTOR; n++)
	{
		stream << tcSensorState::errorFactor[n];
	}

    stream.WriteCheckValue(853);
}

/**
* @return true if successful
*/
bool tcGameSerializer::LoadSimOther(tcSimState* simState, tcGameStream& stream)
{
    std::string scenName;
    stream >> scenName;
    simState->SetScenarioName(scenName);

    std::string scenDescription;
    stream >> scenDescription;
    simState->SetScenarioDescription(scenDescription);

    float gameTime = simState->GetTime();
    stream >> gameTime;
    simState->mfSimTime = gameTime;

    tcDateTime gameDateTime;
    gameDateTime << stream;
    simState->SetDateTime(gameDateTime);

    stream >> simState->mfLastSensorUpdate;
    stream >> simState->mfLastSensorAgeOut;
    stream >> simState->mfLastTileAgeOut;
    stream >> simState->lastLandingStateUpdate;

    int multiplayerMode;
    stream >> multiplayerMode;

    // 11OCT, don't update tcSimState::multiplayerMode, should not change multiplayer state when loading game

    //simState->mpCommandInterface->operator<<(stream);

    size_t nFlightportPlatforms;
    stream >> nFlightportPlatforms;
    if (nFlightportPlatforms > 4096)
    {
        wxASSERT(false);
        return false;
    }
    for (size_t k=0; k<nFlightportPlatforms; k++)
    {
        long val;
        stream >> val;
        simState->flightportPlatforms.push_back(val);
    }

    size_t nLandingPlatforms;
    stream >> nLandingPlatforms;
    if (nLandingPlatforms > 4096)
    {
        wxASSERT(false);
        return false;
    }
    for (size_t k=0; k<nLandingPlatforms; k++)
    {
        long val;
        stream >> val;
        simState->landingPlatforms.push_back(val);
    }

	stream >> tcGameObject::launchedCounter;

	// load tcSensorState static vars
	stream >> tcSensorState::nextSensorId;
	for (int n=0; n<tcSensorState::N_ERROR_FACTOR; n++)
	{
		stream >> tcSensorState::errorFactor[n];
	}

    return stream.ReadCheckValue(853);;
}

void tcGameSerializer::SaveToXml(wxXmlDocument& doc)
{
    wxXmlNode* root = doc.GetRoot();
    if (root == 0)
    {
        doc.SetRoot(new wxXmlNode(wxXML_ELEMENT_NODE, "Root", ""));
        root = doc.GetRoot();
        wxASSERT(root != 0);
    }

    tcSimState* simState = tcSimState::Get();

    wxXmlNode* update = new wxXmlNode(root, wxXML_ELEMENT_NODE, "ObjectUpdate", "");
    update->AddProperty("Time", wxString::Format("%.2f", simState->GetTime()));

    // write data for each object
    tcGameObjIterator iter;
    for (iter.First();iter.NotDone();iter.Next())
    {
        tcGameObject* obj = iter.Get();

        wxXmlNode* objUpdate = new wxXmlNode(update, wxXML_ELEMENT_NODE, "Object", "");

        long platformId = obj->mnID;
        wxString platformName = obj->mzUnit.c_str();
        wxString databaseClass = obj->mpDBObject->mzClass.c_str();
        objUpdate->AddProperty("class", databaseClass);
        objUpdate->AddProperty("name", platformName);
        objUpdate->AddProperty("side", wxString::Format("%d", obj->GetAlliance()));
        objUpdate->AddProperty("lon_deg", wxString::Format("%.6f", C_180OVERPI*obj->mcKin.mfLon_rad));
        objUpdate->AddProperty("lat_deg", wxString::Format("%.6f", C_180OVERPI*obj->mcKin.mfLat_rad));
        objUpdate->AddProperty("alt_m", wxString::Format("%.1f", obj->mcKin.mfAlt_m));
        objUpdate->AddProperty("speed_mps", wxString::Format("%.1f", C_KTSTOMPS*obj->mcKin.mfSpeed_kts));
        objUpdate->AddProperty("heading_deg", wxString::Format("%.1f", C_180OVERPI*obj->mcKin.mfHeading_rad));
        objUpdate->AddProperty("climb_deg", wxString::Format("%.1f", C_180OVERPI*obj->mcKin.mfClimbAngle_rad));
    }
}



tcGameSerializer::tcGameSerializer()
: currentVersion(16)
{
    wxASSERT(tacticalMap != 0);
    wxASSERT(worldMap != 0);
    
}

tcGameSerializer::~tcGameSerializer()
{
}
