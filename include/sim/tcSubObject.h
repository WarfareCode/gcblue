/**
**  @file tcSubObject.h
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

#ifndef _SUBOBJECT_H_
#define _SUBOBJECT_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "tcPlatformObject.h"
#include "tcCommandObject.h"

class tcUpdateStream;
class tcCommandStream;
class tcGameStream;
namespace database
{
	class tcSubDBObject;
}


/**
* Models air object that can land
*/
class tcSubObject : public tcPlatformObject 
{
public:
    tcSubDBObject* mpDBObject;

    virtual void ApplyRestrictions();
    virtual void Clear();
    virtual bool IsDestroyed();
    virtual void RandInitNear(float afLon_deg, float afLat_deg);
    virtual void UpdateClimb(float dt_s);
    virtual void Update(double afStatusTime);

    void PrintToFile(tcFile& file);
    void SaveToFile(tcFile& file);
    void LoadFromFile(tcFile& file);
    virtual void Serialize(tcFile& file, bool mbLoad);

	float GetBatteryCharge() const;
	float GetAIPFuel() const;
    float GetPeriscopeDepth() const;
    bool GetPeriscopeState() const;
    bool GetRadarMastState() const;
	float GetMaxSpeedForDepth(float altitude_m) const;
	float SubAccel(float accel_rate);

    virtual float GetSonarSourceLevel(float az_deg) const;
    bool IsAtPeriscopeDepth() const;
	bool IsDieselElectric() const;
	bool IsAIP() const;
	bool IsSnorkeling() const;
    bool IsSurfaced() const;
    void SetPeriscopeState(bool state);
    void SetRadarMastState(bool state);
	void SetSnorkelState(bool state);
    virtual void SetAltitude(float new_altitude_m);
    float GetMaxQuietSpeedKts() const;
	float tcSubObject::GetBatteryRate() const;
	float tcSubObject::GetAIPRate() const;


    virtual float GetOpticalCrossSection() const;
    virtual float GetIRSignature(float az_deg) const;

    virtual tcCommandStream& operator<<(tcCommandStream& stream);
    virtual tcUpdateStream& operator<<(tcUpdateStream& stream);
    virtual tcGameStream& operator<<(tcGameStream& stream);

    virtual tcCommandStream& operator>>(tcCommandStream& stream);
    virtual tcUpdateStream& operator>>(tcUpdateStream& stream);
    virtual tcGameStream& operator>>(tcGameStream& stream);

    virtual void ClearNewCommand();
    virtual bool HasNewCommand() const;

    tcSubObject();
    tcSubObject(tcSubObject&);
    tcSubObject(tcSubDBObject* obj);
    virtual ~tcSubObject();
protected:
	enum
	{
		MAST_CMD = 0x01 ///< flag for periscope, radar mast, or snorkeling cmds
	};
	enum
	{
		PERISCOPE = 0x01,
		RADARMAST = 0x02,
		SNORKEL = 0x04
	};
    tcCommandObject commandObj;
    const float maxPitch_rad;
    bool radarMastRaised;
    bool periscopeRaised;
	bool isSnorkeling; ///< true if diesel generator active and snorkeling (DE subs only)
    float periscopeDepth_m; ///< periscope depth (positive number)
    float invPeriscopeDepth; ///< 1/periscopeDepth_m
    float lastDepth_m; ///< for depth notification messages
    bool doneSinking;
	float batteryCharge; ///< current battery charge (DE subs only)
	float AIP_fuel_kg; ///< current AIP fuel, for AIP subs only.
	float aipRate;	//current rate of AIP depletion
	float batteryRate;	///current rate of battery depletion

    void UpdateDestroyed(double t);
    virtual void UpdateEffects();
    virtual void UpdateHeading(float dt_s);
    virtual void UpdateMessages();
    virtual void UpdateSensors(double t);
    virtual void UpdateSpeed(float dt_s);
};

#endif
