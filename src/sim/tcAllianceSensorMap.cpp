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

#include "tcAllianceSensorMap.h"
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

#ifdef _DEBUG
#define new DEBUG_NEW
#endif




/******************************* tcAllianceSensorMap ****************************/

/**
* Loads state from update stream.
*/
tcUpdateStream& tcAllianceSensorMap::operator<<(tcUpdateStream& stream)
{
    unsigned int nUpdates;
    stream >> nUpdates;

    for (unsigned int n=0; n<nUpdates; n++)
    {
        long nTrackID;
        stream >> nTrackID;

        long nIdx = maTrackToSensorTrack[nTrackID];
        if (nIdx == NULL_INDEX)
        {
            tcSensorMapTrack *psmtrack = new tcSensorMapTrack();
            long nKey;
            maTrack.AddElement(psmtrack, nKey);
            maTrackToSensorTrack[nTrackID] = nKey;
            (*psmtrack) << stream;
        }
        else 
        {
            tcSensorMapTrack *psmtrack;
            if (maTrack.Lookup(nIdx, psmtrack) == false)
            {
                fprintf(stderr, "tcAllianceSensorMap::operator<< -- "
                                "sensor map index corrupt\n");
                return stream;
            }
            (*psmtrack) << stream;
        }

    }

    return stream;
}

/**
* Saves state to update stream
* Iterates through tracks, saving tracks that have been recently
* updated to stream.
*/
tcUpdateStream& tcAllianceSensorMap::operator>>(tcUpdateStream& stream)
{
    long freeSpace = stream.GetMaxSize() - stream.size() - sizeof(unsigned int); // unsigned int for update count header

    // if freeSpace < 0, the message should be rejected anyway so don't worry about special case
    // for this

    tcUpdateStream tempStream1;
    tcUpdateStream tempStream2;
    unsigned int nUpdates = 0;

    long pos;
    if (nextUpdateKey == -1)
    {
        pos = maTrack.GetStartPosition();
        updatesRemaining = maTrack.GetCount();
    }
    else
    {
        pos = nextUpdateKey;
    }


    tcSensorMapTrack* sensorMapTrack = 0;
 
    while ((updatesRemaining > 0) && (freeSpace > 0))
    {
        tempStream1.clear();
        
        maTrack.GetNextAssoc(pos, nextUpdateKey, sensorMapTrack);
        updatesRemaining--;
        double dt = mfPreviousStatusTime - sensorMapTrack->mfTimestamp;
        if (dt < 2.0)
        {
            tempStream1 << sensorMapTrack->mnID;
            *sensorMapTrack >> tempStream1;

            if ((long)tempStream1.size() <= freeSpace)
            {
                tempStream2 << tempStream1;
                freeSpace -= tempStream1.size();
                nUpdates++;
            }
            else
            {
                freeSpace = 0;
                updatesRemaining++; // have to redo this update
            }

        }

    }

    if (nUpdates == 0)
    {
        nextUpdateKey = -1;
        updatesRemaining = 0;
        stream.SetDoneFlag(true);
        return stream;
    }

    stream << nUpdates;
    stream << tempStream2;

    if (updatesRemaining < 0)
    {
        wxASSERT(updatesRemaining == 0);
        nextUpdateKey = -1;
        updatesRemaining = 0;
        stream.SetDoneFlag(true);
    }
    else
    {
        stream.SetDoneFlag(false);
    }



    return stream;
}


/**
* Save
*/
tcGameStream& tcAllianceSensorMap::operator>>(tcGameStream& stream)
{    
    // save track to sensor track lookup
    for (int k=0; k<MAX_TRACKS; k++)
    {
	    stream << maTrackToSensorTrack[k];
    }

    // save track count
    tcSensorTrackIterator iterCount(alliance);
    unsigned int nTracks = 0;
    for (iterCount.First(); iterCount.NotDone(); iterCount.Next())
    {
        nTracks++;
    }
    stream << nTracks;

    // save track data
    tcSensorTrackIterator iter(alliance);
    for (iter.First(); iter.NotDone(); iter.Next())
    {
        tcSensorMapTrack* track = iter.Get();
        *track >> stream;
    }

    // save other member variables
	stream << mfPreviousStatusTime;
	stream << lastEngagementsUpdate;
    stream << nextUpdateKey;
    stream << updatesRemaining;

    return stream;
}

/**
* Load
*/
tcGameStream& tcAllianceSensorMap::operator<<(tcGameStream& stream)
{
    Clear();

    // load track to sensor track lookup
    for (int k=0; k<MAX_TRACKS; k++)
    {
	    stream >> maTrackToSensorTrack[k];
    }

    // load track count
    unsigned int nTracks;
    stream >> nTracks;

    // load tracks
    for (unsigned int k=0; k<nTracks; k++)
    {
        tcSensorMapTrack* track = new tcSensorMapTrack;
        *track << stream;

        long mapId = maTrackToSensorTrack[track->mnID];
        maTrack.AddElementForceKey(track, mapId);
    }

    // load other member variables
	stream >> mfPreviousStatusTime;
	stream >> lastEngagementsUpdate;
    stream >> nextUpdateKey;
    stream >> updatesRemaining;

    return stream;
}

void tcAllianceSensorMap::AddAlwaysVisibleTrack(tcGameObject* obj)
{
    wxASSERT(obj != 0);
    if (obj == 0) return;

    tcSensorMapTrack* track = 0;

    long nTrackID = obj->mnID;
    long nIdx = maTrackToSensorTrack[nTrackID];
    if (nIdx == NULL_INDEX)
    {
        track = new tcSensorMapTrack();
        long nKey;
        maTrack.AddElement(track, nKey);
        maTrackToSensorTrack[nTrackID] = nKey;
    }
    else // already exists
    {
        if (maTrack.Lookup(nIdx, track) == false)
        {
            fprintf(stderr, "tcAllianceSensorMap::AddAlwaysVisibleTrack - sensor map index corrupt\n");
            wxASSERT(false);
            return;
        }
    }

    wxASSERT(track != 0);

    track->alwaysVisible = true;
    track->mnID = obj->mnID;
    track->mfLat_rad = obj->mcKin.mfLat_rad;
    track->mfLon_rad = obj->mcKin.mfLon_rad;
    track->mfAlt_m = obj->mcKin.mfAlt_m;
    track->mfTimestamp = obj->mfStatusTime;
    track->mnFlags = TRACK_ACTIVE | TRACK_ALT_VALID | TRACK_SPEED_VALID;
    track->mfHeading_rad = 0;
    track->mfSpeed_kts = 0;

    UINT16 nClassification = obj->mpDBObject->mnType;
    tcAllianceInfo::Affiliation affil = tcAllianceInfo::Get()->GetAffiliation(GetAlliance(), obj->GetAlliance());

    track->UpdateClassification(nClassification);
    track->IdentifyTrack(obj->mpDBObject->mnKey);
    track->SetAffiliation(affil);

    tcSensorReport report;
    report.timeStamp = obj->mfStatusTime;
    track->AddReport(report);
}

/**
* Used to "cheat" and immediately mark track corresponding to tcGameObject as destroyed
*/
void tcAllianceSensorMap::MarkObjectDestroyed(const tcGameObject* obj)
{
	wxASSERT(obj != 0);
    if (obj == 0) return;

    tcSensorMapTrack* track = 0;

    long objectID = obj->mnID;
    long nIdx = maTrackToSensorTrack[objectID];
    if (nIdx != NULL_INDEX)
    {
		maTrack.Lookup(nIdx, track);
    }
	else
	{
		return; // don't have this
	}

	wxASSERT(track != 0);
	track->MarkDestroyed();
}



tcSensorReport* tcAllianceSensorMap::GetOrCreateReport(long platformID, long sensorID, long trackID, tcSensorMapTrack*& pSMTrack)
{
    pSMTrack = 0;
    long nIdx = maTrackToSensorTrack[trackID];
    if (nIdx == NULL_INDEX) 
    {
        tcSensorMapTrack *psmtrack = new tcSensorMapTrack();
        long nKey;
        maTrack.AddElement(psmtrack, nKey);
        maTrackToSensorTrack[trackID] = nKey;
        psmtrack->mnID = trackID;

        pSMTrack = psmtrack;

        return psmtrack->GetOrCreateReport(platformID, sensorID);
    }
    else
    {
        tcSensorMapTrack *psmtrack;
        if (maTrack.Lookup(nIdx, psmtrack) == true) 
        {
            pSMTrack = psmtrack;
            return psmtrack->GetOrCreateReport(platformID, sensorID);
        }
        else
        {
            fprintf(stderr, "Error - sensor map index corrupt");
            wxASSERT(false);
            return 0;
        }
    }
}


void tcAllianceSensorMap::ValidateMap()
{
#ifdef _DEBUG
    long cmappos = maTrack.GetStartPosition();
    long nSize = maTrack.GetCount();
    long nKey;
    tcSensorMapTrack *psmtrack;

    for (long i=0;i<nSize;i++) 
    {
        maTrack.GetNextAssoc(cmappos,nKey,psmtrack);

       
        wxASSERT(psmtrack != 0);
        wxASSERT(psmtrack->mnID >= 0);
        wxASSERT(psmtrack->mnID < 512);

        wxASSERT(psmtrack->GetContributorCount() <= tcSensorMapTrack::MAX_SENSOR_REPORTS);
        wxASSERT(nKey >= 0);

        long poolKey = maTrackToSensorTrack[psmtrack->mnID];
        wxASSERT(poolKey == nKey);

        unsigned int nContributors = psmtrack->GetContributorCount();
        for (unsigned int n=0; n<nContributors; n++)
        {
            wxASSERT(psmtrack->maSensorReport[n].startTime <= psmtrack->maSensorReport[n].timeStamp);
        }
    }


    wxASSERT(maTrack.CheckForCorruption() == false);

    for (size_t n=0; n<MAX_TRACKS; n++)
    {
        long idx = maTrackToSensorTrack[n];
        if (idx != NULL_INDEX) 
        {
            tcSensorMapTrack *psmtrack;
            if (maTrack.Lookup(idx, psmtrack) == false) 
            {
                wxASSERT(false);
            }
        }
    }
#endif
}


int tcAllianceSensorMap::GetTrackCount() 
{
    return maTrack.GetCount();
}

long tcAllianceSensorMap::GetStartTrackPosition() 
{
    return maTrack.GetStartPosition();
}

void tcAllianceSensorMap::GetNextTrack(long& pos, tcSensorMapTrack*& pTrack) 
{
    long nKey;
    maTrack.GetNextAssoc(pos, nKey, pTrack);
}

#define SENSORMAP_AGEOUTTIME 30.0f

void tcAllianceSensorMap::DropTrack(long anID)
{
	tcSensorMapTrack* track = GetSensorMapTrack(anID);
	if (track == 0)
	{
		fprintf(stderr, "Error - tcAllianceSensorMap::DropTrack - track does not exist\n");
		return;
	}

	track->Clear();

    long nKey = maTrackToSensorTrack[anID];
    if (nKey == NULL_INDEX) 
	{
		fprintf(stderr, "Error - tcAllianceSensorMap::DropTrack - track does not exist (B)\n");
		return;
	} 

    maTrackToSensorTrack[anID] = -1;
    maTrack.RemoveKey(nKey);
}


void tcAllianceSensorMap::UpdateMultiplayerClient(double statusTime)
{
    long cmappos = maTrack.GetStartPosition();
    long nSize = maTrack.GetCount();
    long nKey;
    tcSensorMapTrack *psmtrack;

    for (long i=0;i<nSize;i++) 
    {
        maTrack.GetNextAssoc(cmappos,nKey,psmtrack);

        double timeSinceUpdate = statusTime - psmtrack->mfTimestamp;

        float ageOutTime = psmtrack->GetAgeOutTime();

        // updated to never drop ground tracks
        bool dropTrack = (timeSinceUpdate > ageOutTime);

        if (dropTrack)
        {
            if (psmtrack->mnID >= 0) 
            {
                maTrackToSensorTrack[psmtrack->mnID] = NULL_INDEX; // used to be = maTrack.GetPoolSize();
            }
            char zBuff[128];
            sprintf(zBuff,"Dropped track %d at time %.1f",psmtrack->mnID,statusTime);
            WTL(zBuff);

            maTrack.RemoveKey(nKey);
        }
        else 
        {
            // check for new data and update
            //psmtrack->UpdateTrack(); // never called for client
        }
    }

#ifdef _DEBUG
    wxASSERT(maTrack.CheckForCorruption()==false);
#endif
}

void tcAllianceSensorMap::Update(double statusTime) 
{
    if ((statusTime - mfPreviousStatusTime) < 1.0f) {return;}
    mfPreviousStatusTime = statusTime;

    if (tcSimState::Get()->IsMultiplayerClient())
    {
        UpdateMultiplayerClient(statusTime);
        return;
    }

    long cmappos = maTrack.GetStartPosition();
    long nSize = maTrack.GetCount();
    long nKey;
    tcSensorMapTrack *psmtrack;


    bool updateEngagements = false;
    if (statusTime - lastEngagementsUpdate > 8.0f)
    {
        updateEngagements = true;
        lastEngagementsUpdate = statusTime;
    }


    for (long i=0; i<nSize; i++) 
    {
        maTrack.GetNextAssoc(cmappos,nKey,psmtrack);

        bool freshReport = false; // true if at least one report isn't stale

        std::vector<size_t> reportsToRemove;

        float staleTime = psmtrack->GetStaleTime();
        float ageOutTime = psmtrack->GetAgeOutTime();

        size_t nContributors = psmtrack->GetContributorCount();
        for (size_t n=0; n<nContributors; n++) 
        {
            double timeSinceUpdate = statusTime - psmtrack->maSensorReport[n].timeStamp;
            if (timeSinceUpdate >= ageOutTime) 
            {
                reportsToRemove.push_back(n);
            }
            else if (timeSinceUpdate >= staleTime)
            {
                if (psmtrack->IsDestroyed() && (timeSinceUpdate >= staleTime + 10.0))
                {
                    reportsToRemove.push_back(n);
                }
            }
            else
            {
                freshReport = true;
            }
        }

        if (reportsToRemove.size() > 0)
        {
            psmtrack->RemoveReports(reportsToRemove);
        }

        if (!freshReport)
        {
            // periodically coast stale tracks so they get reported to multiplayer clients
            if (statusTime - psmtrack->mfTimestamp > 10.0f)
            {
                psmtrack->UpdateTrack(statusTime);
            }

            psmtrack->MarkStale(); // note can get stale cleared in UpdateTrack
        }


        bool dropTrack = (psmtrack->GetContributorCount() == 0) && (!psmtrack->alwaysVisible);


        if (dropTrack)
        {
            if (psmtrack->mnID >= 0) 
            {
                maTrackToSensorTrack[psmtrack->mnID] = NULL_INDEX; // used to be = maTrack.GetPoolSize();
            }

            maTrack.RemoveKey(nKey);
            
#ifdef _DEBUG
            char zBuff[128];
            sprintf(zBuff,"Dropped track %d at time %.1f",psmtrack->mnID,statusTime);
            WTL(zBuff);
#endif

        }
        else 
        {
            // check for new data and update
            psmtrack->UpdateTrack(0);
            if (updateEngagements)
            {
                psmtrack->UpdateEngagements();
                psmtrack->UpdateIntercepts();
            }
        }
    }


#ifdef _DEBUG
    wxASSERT(maTrack.CheckForCorruption()==false);
#endif
}

unsigned int tcAllianceSensorMap::GetAlliance() const
{
	return alliance;
}

/*******************************************************************************/
tcSensorMapTrack* tcAllianceSensorMap::GetSensorMapTrack(long anTrackID) 
{
    long nMapID;
    tcSensorMapTrack *pSMTrack;

    if (anTrackID >= MAX_TRACKS) {return NULL;}
    nMapID = maTrackToSensorTrack[anTrackID];
    if (nMapID == NULL_INDEX) {return NULL;}
    maTrack.Lookup(nMapID,pSMTrack);
    return pSMTrack;
}
/*******************************************************************************/
bool tcAllianceSensorMap::GetTrack(long anTrackID, tcTrack& track) 
{
    tcSensorMapTrack* pSensorTrack = GetSensorMapTrack(anTrackID);

    if (pSensorTrack == 0) 
	{
        return false;
    }
    track = *((tcTrack*)pSensorTrack); 
    return true;
}

/*******************************************************************************/
void tcAllianceSensorMap::Clear() 
{
    maTrack.RemoveAll();
    for(long k=0;k<MAX_TRACKS;k++) 
    {
        maTrackToSensorTrack[k] = NULL_INDEX;
    }
    // randomize updates so alliances don't all update at once
    mfPreviousStatusTime = 1.0f*randf();
    lastEngagementsUpdate = 10.0f*randf();

    nextUpdateKey = -1;
    updatesRemaining = 0;
}
/********************************************************************/
int tcAllianceSensorMap::Serialize(tcFile& file, bool mbLoad) {
    long nMapSize, nKey;
    tcSensorMapTrack *psmtrack;

    /* load SensorMap from file */
    if (mbLoad) {
        Clear();

        file.Read(maTrackToSensorTrack,MAX_TRACKS*sizeof(long));
        file.Read(&nMapSize,sizeof(nMapSize));
        for(int i=0;i<nMapSize;i++) {
            psmtrack = new tcSensorMapTrack;
            file.Read(psmtrack,sizeof(tcSensorMapTrack));
            if ((unsigned long)psmtrack->mnID >= MAX_TRACKS) {
                WTL("tcAllianceSensorMap::Serialize - corrupt scenario file");
                return false;
            }
            nKey = maTrackToSensorTrack[psmtrack->mnID];
            maTrack.AddElementForceKey(psmtrack,nKey);
        }
    }
    /* save to file */
    else {   
        long cmappos = maTrack.GetStartPosition();

        file.Write(maTrackToSensorTrack,MAX_TRACKS*sizeof(long));

        nMapSize = maTrack.GetCount();
        file.Write(&nMapSize,sizeof(nMapSize));
        for (long i=0;i<nMapSize;i++) {
            maTrack.GetNextAssoc(cmappos,nKey,psmtrack);
            file.Write(psmtrack,sizeof(tcSensorMapTrack));
        }  
    }
    return true;
}

tcAllianceSensorMap::tcAllianceSensorMap(unsigned int mapAlliance) 
: alliance(mapAlliance),
  nextUpdateKey(-1),
  updatesRemaining(0)
{
    Clear();

    bool autoKillAssessment = tcOptions::Get()->OptionStringExists("AutoKillAssessment");
    tcSensorMapTrack::SetAutoKillAssess(autoKillAssessment);
    
}

tcAllianceSensorMap::~tcAllianceSensorMap() 
{
}
