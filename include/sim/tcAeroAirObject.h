/**
**  @file tcAeroAirObject.h
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

#ifndef _AEROAIROBJECT_H_
#define _AEROAIROBJECT_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "tcAirObject.h"

namespace database
{
    class tcJetDBObject;
}
namespace scriptinterface
{
	class tcScenarioLogger;
}

class tcCommandStream;
class tcGameStream;

/**
* Aerodynamic air object model.
* A cross between a basic constant-velocity model
* and a flight-sim style model
*/
class tcAeroAirObject : public tcAirObject 
{
public:
    tcJetDBObject *mpDBObject;

    virtual void ApplyRestrictions();
    virtual void Clear(void);
    virtual void RandInitNear(float afLon_deg, float afLat_deg);

    void PrintToFile(tcFile& file);
    void SaveToFile(tcFile& file);

    float GetThrottleFraction() const {return throttleFraction;}
    void SetThrottleFraction(float fract);
    virtual void SetSpeed(float newSpeed);

    static void CalculateSpeedParams(float altitude_m, float throttle,
        float& maxSpeed_mps, float& fuelRate_kgps, float damageLevel, const tcJetDBObject* airData);
    virtual float GetCurrentFuelRate() const;
    virtual float GetCruiseSpeedForAltitude(float alt_m) const;
    virtual float CalculateFuelRate(float speed_mps, float alt_m) const;
    virtual float GetCruiseRangeKm(float alt_m) const;
	static float GetAeroCruiseRangeKm(float alt_m, float fuelLoad_kg, float damageLevel, const tcJetDBObject* airData, float& cruise_mps);
    virtual float GetCruiseAltitude() const;
	virtual float GetStallSpeedForAltitude(float alt_m) const;
	float MilThrottleForThrust(float thrust_N) const;

    void LoadFromFile(tcFile& file);
    virtual void Serialize(tcFile& file, bool mbLoad);
	virtual void SaveToPython(scriptinterface::tcScenarioLogger& logger);

    virtual tcCommandStream& operator<<(tcCommandStream& stream);
    virtual tcCommandStream& operator>>(tcCommandStream& stream);
    virtual tcGameStream& operator<<(tcGameStream& stream);
    virtual tcGameStream& operator>>(tcGameStream& stream);

    virtual void ClearNewCommand();
    virtual bool HasNewCommand() const;

    virtual float GetOpticalCrossSection() const;
    virtual float GetIRSignature(float az_deg) const;

    tcAeroAirObject();
    tcAeroAirObject(tcAeroAirObject&);
    tcAeroAirObject(tcJetDBObject *obj);
    virtual ~tcAeroAirObject();
protected:    
    virtual void UpdateClimb(float dt_s);
    virtual void UpdateEffects();
    virtual void UpdateHeading(float dt_s);
    virtual void Update(double afStatusTime);
    virtual void UpdateSpeed(float dt_s);
private:
	enum
	{
		THROTTLE_CMD = 0x0001
	};
	tcCommandObject commandObj;
    float throttleFraction; ///< throttle setting from 0 to 1 military, greater than 1 to use afterburners
    float levelThrottleFraction; ///< if this is non-zero, set throttle to this when in level flight again
	float levelThrust_N;
    float angleOfAttack; ///< angle of attack in radians, solved assuming level flight
	float lastThrust_N; ///< saved for updating throttle to maintain speed in climb
	float lastWeight_N; ///< saved for updating throttle to maintain speed in climb

    static float GetFuelRate(float throttle, float efficiencyFactor, float thrustFactor, float damageLevel, const tcJetDBObject* airData);
    static float GetThrust(float throttle, float thrustFactor, float speed_mps, const tcJetDBObject* airData);
    float GetParasiticDragCoefficient(float vmach) const;
    static float SolveForSpeed(float throttle, float altitude_m, float& rho, float damageLevel, const tcJetDBObject* airData);
    static float SolveForThrottle(float speed_mps, float altitude_m, float damageLevel, const tcJetDBObject* airData);
    float UpdateThrust(float dt_s);
};

#endif
