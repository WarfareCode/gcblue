/**
**  @file tcSensorMap.h
**  TODO needs cleanup, this area is a mess
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


#ifndef _SENSORMAP_H_ 
#define _SENSORMAP_H_

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

class tcAllianceSensorMap;

/**
* holds tcAllianceSensorMaps for all alliances
* @see tcAllianceSensorMap
*/
class tcSensorMap 
{
	enum {MAX_MAPS = 16, MAX_ALLIANCES = 16}; // MAX_ALLIANCES should be merged with tcAllianceInfo::MAX_ALLIANCES
public:
	int GetTrackCount(UINT8 anAlliance);
	long GetStartTrackPosition(UINT8 anAlliance);
	void GetNextTrack(long& pos, tcSensorMapTrack*& pTrack, UINT8 anAlliance);

	tcAllianceSensorMap* GetMap(UINT8 anAlliance);
	tcAllianceSensorMap* GetOrCreateMap(UINT8 alliance);
	void CreateMapForAlliance(UINT8 anAlliance);
	bool MapExists(UINT8 alliance) const;
    size_t GetMapCount() const; ///< @return number of sensor maps created

    tcSensorReport* GetOrCreateReport(long platformID, long sensorID, long trackID, tcSensorMapTrack*& pSMTrack, unsigned int alliance);

    void AddAlwaysVisibleTrack(const std::string& unitName);
    void DropAlwaysVisibleTrack(const std::string& unitName);
    bool GetAlwaysVisibleState(tcGameObject* obj) const;
	void MarkObjectDestroyed(const tcGameObject* obj);

	void Clear();

	void Update(double afStatusTime);
	tcSensorMapTrack* GetSensorMapTrack(long anTrackID, UINT8 anAlliance);
	bool GetTrack(unsigned long anTrackID, tcTrack& track, UINT8 anAlliance);
	int Serialize(tcFile& file, bool mbLoad);
	bool Test();

	tcGameStream& operator<<(tcGameStream& stream);
	tcGameStream& operator>>(tcGameStream& stream);

	tcSensorMap();
	virtual ~tcSensorMap();

private:
	tcAllianceSensorMap* mapMap[MAX_MAPS];
	int mnMaps;
	int maMapIdxForAlliance[MAX_ALLIANCES];
};

#endif // _SENSORMAP_H_
