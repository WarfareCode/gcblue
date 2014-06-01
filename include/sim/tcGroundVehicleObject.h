/**
**  @file tcGroundVehicleObject.h
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

#if _MSC_VER > 1000
#pragma once
#endif

#ifndef _TCGROUNDVEHICLEOBJECT_H_
#define _TCGROUNDVEHICLEOBJECT_H_

#include "tcFile.h"
#include "tcEngagementData.h"
#include "tcPlatformObject.h"

namespace database
{
	class tcPlatformDBObject;
    class tcGroundDBObject;
}
class tcGameStream;

/**
* Represents a vehicle that moves along the ground, e.g. a mobile SAM
*
* @see tcPlatformObject
*/
class tcGroundVehicleObject : public tcPlatformObject
{
public:
	tcGroundDBObject* mpDBObject;

	virtual void Clear();

	virtual bool IsDestroyed();
	virtual void RandInitNear(float afLon_deg, float afLat_deg);
	virtual void Update(double afStatusTime);

	void PrintToFile(tcFile& file);
	void SaveToFile(tcFile& file);
	void LoadFromFile(tcFile& file);
	virtual void Serialize(tcFile& file, bool mbLoad);

    const std::string& GetVehicleMode() const;
    bool OperatesOnMove() const;
    float OperationTimeRemaining() const;
    void SetupEquipment();
    void TakedownEquipment();

    virtual float GetOpticalCrossSection() const;
    virtual float GetIRSignature(float az_deg) const;

    virtual tcGameStream& operator<<(tcGameStream& stream);
    virtual tcGameStream& operator>>(tcGameStream& stream);

	tcGroundVehicleObject();
	tcGroundVehicleObject(tcGroundVehicleObject&);
	tcGroundVehicleObject(tcGroundDBObject* obj);
	~tcGroundVehicleObject();

protected:
    enum
    {
        MOVING = 1, ///< vehicle is moving, equipment inoperable if setup/takedown time > 0
        SETUP = 2, ///< vehicle stopped and readying equipment
        READY = 3, ///< vehicle stopped and all equipment ready 
        TAKEDOWN = 4 ///< vehicle stopped and stowing equipment for move
    };

    int vehicleMode;
    bool doneDestroyed;
    float lastAlt_m;

	virtual void ApplyRestrictions();    
    virtual void UpdateClimb(float dt_s);
	virtual void UpdateEffects();
	virtual void UpdateHeading(float dt_s);
	virtual void UpdateDestroyed(double t);

};

#endif