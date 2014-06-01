/** 
**  @file tcFlightOpsObject.h
**  
**  Header for tcFlightOpsObject class.
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

#ifndef _TCFLIGHTOPSOBJECT_H_
#define _TCFLIGHTOPSOBJECT_H_

#if _MSC_VER > 1000
#pragma once
#endif


#include "tcFile.h"
#include "tcFlightPort.h"

class tcGameObject;

class tcStream;
class tcCommandStream;
class tcCreateStream;
class tcUpdateStream;
class tcGameStream;

namespace database
{
	class tcDatabase;
    struct AirComplement;
}
namespace scriptinterface
{
	class tcScenarioLogger;
}
class tcTrack;

/**
 * Models a sim object with a flightport for air ops.
 * tcFlightOpsObjects can launch, land, and reposition aircraft.
 *
 * This code started as part of tcCarrierObject and was extracted
 * in an attempt to generalize application to airstrips, helo decks
 * etc.
 *
 * @see tcFlightPort
 */
class tcFlightOpsObject 
{
public:
    virtual tcGameObject* AddChildToFlightDeck(const std::string& className, std::string unitName, 
		teLocation loc, unsigned int position);
	virtual tcGameObject* AddChildToFlightDeck(tcDatabaseObject* databaseObject, std::string unitName, 
		teLocation loc, unsigned int position);
    virtual int CheckLanding(tcAirObject* obj);
    virtual void Clear();
    tcFlightPort* GetFlightPort();
    size_t CurrentAirComplementSize() const;
	tcTrack GetLandingData();
    void PrintToFile(tcFile& file);
	void RandInitNear(float afLon_deg, float afLat_deg); 

    void DestroyAllChildrenAndUpdateScore(tcGameObject* damager);
    bool ApplyAdvancedDamage(const Damage& damage, tcGameObject* damager, float generalDamage);

    virtual void SetFlightportDefaults();
    virtual void Update(double afStatusTime);
    virtual void UpdateLaunch();

    void AutoConfigureAirComplement(const std::vector<database::AirComplement>& airComplement);
    void GetAirBlockName(std::string& prefix, unsigned int blockSize, unsigned int& startId);

    long GetParentId() const;

	virtual void SaveToPython(scriptinterface::tcScenarioLogger& logger);

    virtual tcCommandStream& operator<<(tcCommandStream& stream);
    virtual tcCreateStream& operator<<(tcCreateStream& stream);
    virtual tcUpdateStream& operator<<(tcUpdateStream& stream);
    virtual tcGameStream& operator<<(tcGameStream& stream);

    virtual tcCommandStream& operator>>(tcCommandStream& stream);
    virtual tcCreateStream& operator>>(tcCreateStream& stream);
    virtual tcUpdateStream& operator>>(tcUpdateStream& stream);
    virtual tcGameStream& operator>>(tcGameStream& stream);

    virtual void ClearNewCommand();
    virtual bool HasNewCommand() const;

    tcFlightOpsObject(tcFlightportDBObject* dbObject, tcGameObject* gameObject);
    virtual ~tcFlightOpsObject();
private:
	static database::tcDatabase* database;
    tcFlightPort flight_deck;
	tcGameObject* gameObj; ///< to avoid (some) virtual inheritance inefficiency

    size_t nextUpdateIdx; ///< to track partial updates on multiplayer server

    void AddRandomNameModifier(std::string& prefix);

    tcFlightOpsObject();
};

#endif