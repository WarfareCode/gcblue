/**
**  @file tcAllianceSensorMap.h
**  
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


#ifndef _ALLIANCESENSORMAP_H_ 
#define _ALLIANCESENSORMAP_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "simmath.h"
#include "tcPool.h"
#include "tcFile.h"
#include <vector>
#include "tcSensorMapTrack.h"

class tcSimState;
class tcUpdateStream;
class tcGameStream;

namespace database
{
	class tcDatabase;
}
using database::tcDatabase;

/**
* Sensor track management code. This is older code
* that needs refactoring.
*/
class tcAllianceSensorMap  
{
	enum {MAX_SMTRACKS = 8192, MAX_TRACKS = 8192}; // these have to match tcSimState::N_GAME_OBJECTS!
public:
	unsigned int GetAlliance() const;
	int GetTrackCount();
	long GetStartTrackPosition();
	void GetNextTrack(long& pos, tcSensorMapTrack*& pTrack);
	void Clear();
	void DropTrack(long anID);

    tcSensorReport* GetOrCreateReport(long platformID, long sensorID, long trackID, tcSensorMapTrack*& pSMTrack);

    void AddAlwaysVisibleTrack(tcGameObject* obj);
	void MarkObjectDestroyed(const tcGameObject* obj);

	void Update(double statusTime);
    void UpdateMultiplayerClient(double statusTime);
	tcSensorMapTrack* GetSensorMapTrack(long anTrackID);
	bool GetTrack(long anTrackID, tcTrack& track);
	int Serialize(tcFile& file, bool mbLoad);

	tcUpdateStream& operator<<(tcUpdateStream& stream);
	tcUpdateStream& operator>>(tcUpdateStream& stream);

	tcGameStream& operator<<(tcGameStream& stream);
	tcGameStream& operator>>(tcGameStream& stream);

    void ValidateMap();

	tcAllianceSensorMap(unsigned int mapAlliance);
	virtual ~tcAllianceSensorMap();
private:
	tcPool<tcSensorMapTrack,MAX_SMTRACKS> maTrack;
	long maTrackToSensorTrack[MAX_TRACKS];
	double mfPreviousStatusTime;
	double lastEngagementsUpdate;
	const unsigned int alliance;
    long nextUpdateKey; ///< track key for partial mp update
    long updatesRemaining; ///< remaining updates for partial mp update
};

#endif // _ALLIANCESENSORMAP_H_
