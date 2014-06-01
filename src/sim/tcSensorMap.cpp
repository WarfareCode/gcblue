/**
**  @file tcSensorMap.cpp
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

#include "tcSensorMap.h"
#include "aerror.h"
#include "simmath.h"
#include "tcSimState.h"
#include "tcWeaponObject.h"
#include "tcPlatformDBObject.h"
#include "common/tcObjStream.h"
#include "tcGameStream.h"
#include "tcDatabaseIterator.h"
#include "tcAllianceInfo.h"
#include "tcSensorTrackIterator.h"
#include "tcAllianceSensorMap.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


/**
* Load
*/
tcGameStream& tcSensorMap::operator<<(tcGameStream& stream)
{
    Clear();

    for (int k=0; k<MAX_ALLIANCES; k++)
    {
        stream >> maMapIdxForAlliance[k];
    }

    int nMaps;
    stream >> nMaps; // mnMaps will be incremented in CreateMapForAlliance

    for (int k=0; k<nMaps; k++)
    {
        unsigned int alliance_k;
        stream >> alliance_k;
        CreateMapForAlliance(alliance_k);

        wxASSERT(mapMap[k] != 0);
        *mapMap[k] << stream;
    }

    return stream;
}

/**
* Save
*/
tcGameStream& tcSensorMap::operator>>(tcGameStream& stream)
{
    for (int k=0; k<MAX_ALLIANCES; k++)
    {
        stream << maMapIdxForAlliance[k];
    }
    stream << mnMaps;

    for (int k=0; k<mnMaps; k++)
    {
        unsigned int alliance_k = mapMap[k]->GetAlliance();
        stream << alliance_k;
        *mapMap[k] >> stream;
    }

    return stream;
}


tcAllianceSensorMap* tcSensorMap::GetMap(UINT8 anAlliance) 
{
    int nMapIdx = maMapIdxForAlliance[anAlliance];
    if (nMapIdx == -1) 
    {
        fprintf(stderr, "Bad alliance passed to sensormap (%d, nMaps: %d)\n", anAlliance, mnMaps);
        return NULL;
    }
    return mapMap[nMapIdx];
}

size_t tcSensorMap::GetMapCount() const
{
    return (size_t)mnMaps;
}


bool tcSensorMap::MapExists(UINT8 alliance) const
{
    return (maMapIdxForAlliance[alliance] != -1);
}

/**
* Gets sensor map for alliance, creating if necessary
* @return pointer to alliance sensor map
*/
tcAllianceSensorMap* tcSensorMap::GetOrCreateMap(UINT8 alliance)
{
    int mapIdx = maMapIdxForAlliance[alliance];
    if (mapIdx == -1) 
    {
        CreateMapForAlliance(alliance);
    }
    return GetMap(alliance);
}

int tcSensorMap::GetTrackCount(UINT8 anAlliance) 
{
    if (tcAllianceSensorMap *pMap = GetMap(anAlliance))
    {
        return pMap->GetTrackCount();
    }
    else
    {
        return 0;
    }
}
long tcSensorMap::GetStartTrackPosition(UINT8 anAlliance) 
{
    if (tcAllianceSensorMap *pMap = GetMap(anAlliance))
    {
        return pMap->GetStartTrackPosition();
    }
    else
    {
        return -1;
    }
}
void tcSensorMap::GetNextTrack(long& pos, tcSensorMapTrack*& pTrack, UINT8 anAlliance) 
{
    if (tcAllianceSensorMap *pMap = GetMap(anAlliance))
    {
        return pMap->GetNextTrack(pos, pTrack);
    }
    else
    {
        pos = -1;
        pTrack = 0;
    }
}

void tcSensorMap::CreateMapForAlliance(UINT8 anAlliance) 
{
    if (mnMaps >= MAX_MAPS) 
    {
        fprintf(stderr, "tcSensorMap::CreateMapForAlliance - Exceeded number of maps\n");
        return;
    }
    mapMap[mnMaps] = new tcAllianceSensorMap(anAlliance);
    maMapIdxForAlliance[anAlliance] = mnMaps;
    mnMaps++;
}

/**
* Adds an "always visible" track to all alliance maps except owner's
*/
void tcSensorMap::AddAlwaysVisibleTrack(const std::string& unitName)
{
    tcSimState* simState = tcSimState::Get();

    tcGameObject* obj = simState->GetObjectByName(unitName);
    if (obj == 0)
    {
        fprintf(stderr, "tcSensorMap::AddAlwaysVisibleTrack - %s not found\n", unitName.c_str());
        return;
    }

    unsigned int unitAlliance = obj->GetAlliance();
    for(int n=0; n<mnMaps ;n++) 
    {
        if (mapMap[n]->GetAlliance() != unitAlliance)
        {
            mapMap[n]->AddAlwaysVisibleTrack(obj);
        }
    }
}


void tcSensorMap::DropAlwaysVisibleTrack(const std::string& unitName)
{
    tcSimState* simState = tcSimState::Get();

    tcGameObject* obj = simState->GetObjectByName(unitName);
    if (obj == 0)
    {
        fprintf(stderr, "tcSensorMap::DropAlwaysVisibleTrack - %s not found\n", unitName.c_str());
        return;
    }

    unsigned int unitAlliance = obj->GetAlliance();
    for(int n=0; n<mnMaps ;n++) 
    {
        if (mapMap[n]->GetAlliance() != unitAlliance)
        {
            mapMap[n]->DropTrack(obj->mnID);
        }
    }
}

bool tcSensorMap::GetAlwaysVisibleState(tcGameObject* obj) const
{
    wxASSERT(obj != 0);

    unsigned int unitAlliance = obj->GetAlliance();
    for(int n=0; n<mnMaps ;n++) 
    {
        if (mapMap[n]->GetAlliance() != unitAlliance)
        {
            tcSensorMapTrack* track = mapMap[n]->GetSensorMapTrack(obj->mnID);
            if ((track != 0) && (track->alwaysVisible)) return true;
        }
    }

    return false;
}

/**
* Used to "cheat" and immediately mark track corresponding to tcGameObject as destroyed
*/
void tcSensorMap::MarkObjectDestroyed(const tcGameObject* obj)
{
    for(int n=0;n<mnMaps;n++) 
    {
        mapMap[n]->MarkObjectDestroyed(obj);
    }
}

tcSensorReport* tcSensorMap::GetOrCreateReport(long platformID, long sensorID, long trackID, tcSensorMapTrack*& pSMTrack, unsigned int alliance)
{
    tcAllianceSensorMap* pMap = GetMap(alliance);
    wxASSERT(pMap != 0);

    return pMap->GetOrCreateReport(platformID, sensorID, trackID, pSMTrack);
}


void tcSensorMap::Clear() 
{
    int n;
    for(n=0;n<MAX_ALLIANCES;n++) 
    {
        maMapIdxForAlliance[n] = -1;
    }
    for(n=0;n<mnMaps;n++) 
    {
        if (mapMap[n] != NULL) 
        {
            delete mapMap[n];
            mapMap[n] = NULL;
        }
    }
    mnMaps = 0;
}

void tcSensorMap::Update(double afStatusTime) 
{
    for(int n=0;n<mnMaps;n++) 
    {
        mapMap[n]->Update(afStatusTime);
    }
}

bool tcSensorMap::GetTrack(unsigned long anTrackID, tcTrack& track, UINT8 anAlliance) 
{
    tcAllianceSensorMap *pMap = GetMap(anAlliance);
    return pMap->GetTrack(anTrackID, track);
}

tcSensorMapTrack* tcSensorMap::GetSensorMapTrack(long anTrackID, UINT8 anAlliance)
{
    tcAllianceSensorMap *pMap = GetMap(anAlliance);
	if (pMap != 0)
	{
		return pMap->GetSensorMapTrack(anTrackID);
	}
	else
	{
		return 0;
	}
}

int tcSensorMap::Serialize(tcFile& file, bool mbLoad) 
{
    if (mbLoad)
	{
        Clear();
        file.Read(maMapIdxForAlliance,MAX_ALLIANCES*sizeof(int));
        file.Read(&mnMaps,sizeof(mnMaps));
        for(int n=0;n<mnMaps;n++)
		{
            mapMap[n] = new tcAllianceSensorMap(0);
            mapMap[n]->Serialize(file,mbLoad);
        }
    }
    /* save to file */
    else {   
        file.Write(maMapIdxForAlliance,MAX_ALLIANCES*sizeof(int));
        file.Write(&mnMaps,sizeof(mnMaps));
        for(int n=0;n<mnMaps;n++) {
            mapMap[n]->Serialize(file,mbLoad);
        }
    }
    return true;
}

bool tcSensorMap::Test() 
{
    return false;
}

tcSensorMap::tcSensorMap() 
{
    wxASSERT(tcSensorMap::MAX_ALLIANCES == tcAllianceInfo::MAX_ALLIANCES);

    for(int n=0;n<MAX_MAPS;n++) 
	{
        mapMap[n] = NULL;
    }
    mnMaps = 0;
    Clear();
}

tcSensorMap::~tcSensorMap() 
{
    for(int n=0;n<MAX_MAPS;n++) 
	{
        if (mapMap[n] != NULL) 
		{
            delete mapMap[n];
        }
    }
	fprintf(stdout, "Total ambiguity list updates: %d\n", 
		tcSensorMapTrack::ambiguityListUpdates);
}