/**
**  @file tcAirObject.h
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
#ifndef _AIROBJECT_H_
#define _AIROBJECT_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "tcPlatformObject.h"
#include "tcCommandObject.h"

namespace database
{
    class tcAirDBObject;
}

class tcUpdateStream;
class tcCommandStream;
class tcGameStream;

#define MAX_PITCH_RAD 0.875f

/**
* Models air object that can land
*/
class tcAirObject : public tcPlatformObject 
{
public:
    enum
    {
        LANDING_CMD = 0x0001
    };

    tcAirDBObject* mpDBObject;
    int readyForLanding; ///< 1 if gear down/ready for landing, 0 otherwise


    virtual void ApplyRestrictions();
    virtual void Clear();
    virtual bool IsDestroyed();
    virtual void RandInitNear(float afLon_deg, float afLat_deg);
    float GetTotalWeight() const;
    virtual void SetAltitude(float new_altitude_m);
    virtual void SetLandingState(int state);
    void SetPitchLimit(float limit_rad);
    void SetClimbCommand(float climb_rad);
    float GetClimbCommand() const;
    virtual void UpdateClimb(float dt_s);
    virtual void Update(double afStatusTime);
    
    virtual float GetCruiseSpeedForAltitude(float alt_m) const;
    virtual float GetCurrentFuelRate() const;
    virtual float GetCruiseRangeKm(float alt_m) const;
    virtual float GetCruiseAltitude() const;
	virtual float GetStallSpeedForAltitude(float alt_m) const;

    bool AddFuelTarget(long id);
    bool CanRefuelInFlight() const;
    bool IsTanker() const;
    unsigned int TankerSpotsFree() const;

    bool IsOverweight() const;
	bool IsReadyForLaunch();
    void UpdateLoadoutTag();
    bool MaintenanceHold() const;
    void LightenLoad();

    float CalculateBombElevationRad(float targetLon_rad, float targetLat_rad) const;

	virtual void EquipForTargetType(int targetFlag);
	virtual void EquipForTargetType(const std::string& targetType);

    void PrintToFile(tcFile& file);
    void SaveToFile(tcFile& file);
    void LoadFromFile(tcFile& file);
    virtual void Serialize(tcFile& file, bool mbLoad);

    virtual tcCommandStream& operator<<(tcCommandStream& stream);
    virtual tcUpdateStream& operator<<(tcUpdateStream& stream);
    virtual tcGameStream& operator<<(tcGameStream& stream);

    virtual tcCommandStream& operator>>(tcCommandStream& stream);
    virtual tcUpdateStream& operator>>(tcUpdateStream& stream);
    virtual tcGameStream& operator>>(tcGameStream& stream);

    virtual void ClearNewCommand();
    virtual bool HasNewCommand() const;

    virtual float GetOpticalCrossSection() const;
    virtual float GetIRSignature(float az_deg) const;

    tcAirObject();
    tcAirObject(tcAirObject&);
    tcAirObject(tcAirDBObject* obj);
    virtual ~tcAirObject();
protected:
    tcCommandObject commandObj;

    float GlimitedHeadingRate() const;
    virtual void UpdateDestroyed(double t);
    virtual void UpdateEffects();
    virtual void UpdateHeading(float dt_s);
    virtual void UpdateSpeed(float dt_s);
    void UpdateInFlightRefuel(float dt_s);
    void UpdateClimbCommand(float dt_s);

    float maxPitch_rad; ///< user imposed restriction to pitch angle
    float climbCommand_rad; ///< user/ai override on climb angle, zero for no command
    bool doneCrashing;
    std::vector<long> fuelTargets; ///< for tanker
};

#endif
