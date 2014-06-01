/** 
**  @file tcHeloObject.cpp  
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

#ifndef WX_PRECOMP
#include "wx/wx.h" 
#endif

#include "tcHeloObject.h"
#include "tcAirDBObject.h"
#include "tcSonarDBObject.h"
#include "tcSonar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using std::min;
using std::max;

void tcHeloObject::Clear()  
{  
    tcAirObject::Clear();
}

float tcHeloObject::GetCruiseAltitude() const
{
    return 600.0f;
}


float tcHeloObject::GetCurrentFuelRate() const
{
    // this needs to match calculation in UpdateSpeed
    float effectiveSpeed_kts = std::max(50.0f, mcKin.mfSpeed_kts);

    return mpDBObject->GetFuelConsumptionConstant(0) * effectiveSpeed_kts;
}


/**
* @returns altitude of dipping sonar if dipping sonar active, 999.9 m otherwise
*/
float tcHeloObject::GetDippingSonarAlt() const
{
    const float NOT_APPLICABLE = 999.9f;
	if (!IsEnsonifying()) return NOT_APPLICABLE;

	const tcSonar* sonar = GetStrongestActiveSonar();

	if (sonar != 0)
	{
        return mcKin.mfAlt_m - sonar->GetScope();
	}
	else
	{
		return NOT_APPLICABLE;
	}
}


/**
* @returns max active sonar source level (dipping sonar)
*/
float tcHeloObject::GetSonarSourceLevel(float az_deg) const
{
    const float NOT_APPLICABLE = -999.9f;
 
	if (!IsEnsonifying()) return NOT_APPLICABLE;

	const tcSonar* sonar = GetStrongestActiveSonar();
	if (sonar != 0)
	{
		return sonar->mpDBObj->SL;
	}
	else
	{
		return NOT_APPLICABLE;
	}
}


void tcHeloObject::RandInitNear(float afLon_deg, float afLat_deg)
{
    if (mpDBObject == NULL) {return;}

	tcAirObject::RandInitNear(afLon_deg, afLat_deg);

    // replace unit prefix, otherwise use tcAirObject RandInitNear
    mzUnit = "HELO_";
    mzUnit.AssignRandomSuffix();
}


void tcHeloObject::PrintToFile(tcFile& file) 
{
    tcAirObject::PrintToFile(file);
}

void tcHeloObject::SaveToFile(tcFile& file) 
{
    tcAirObject::SaveToFile(file); 
}

void tcHeloObject::LoadFromFile(tcFile& file) 
{
    tcAirObject::LoadFromFile(file);
}

void tcHeloObject::Serialize(tcFile& file, bool mbLoad)
{
    if (mbLoad) 
	{
        LoadFromFile(file);
    }
    else 
	{
        SaveToFile(file);
    }
}

void tcHeloObject::ApplyRestrictions() 
{
    // check for crash
    if ((mcKin.mfAlt_m <= 0)||(mcTerrain.mfHeight_m >= mcKin.mfAlt_m))
	{
        mfDamageLevel = 1.0f;
    }
}

/**
* Has problems for large time steps, > about 1 sec
*/
void tcHeloObject::UpdateClimb(float dt_s) 
{
    float dalt_min, dalt_max, fAltitudeRate_mps;
    float dalt_m = mcGS.mfGoalAltitude_m - mcKin.mfAlt_m;

	// set pitch based on speed
	mcKin.mfPitch_rad = -0.20f * mcKin.mfSpeed_kts / mpDBObject->mfMaxSpeed_kts;

	// set climb angle to zero and let this method update altitude
    mcKin.mfClimbAngle_rad = 0; 

    if ((dalt_m > -0.25f)&&(dalt_m < 0.25f)&&(fuel_kg > 0)) 
    {
        return;
    }


    const float fHighZone = 100.0f;
    const float fLowZone = -100.0f;
	float maxClimbRate = mpDBObject->climbRate_mps;
    float maxDescentRate = 2.0f*mpDBObject->climbRate_mps;
	
	// reduce rate to zero near max altitude
	if (mcKin.mfAlt_m > mpDBObject->maxAltitude_m - 200)
	{
		maxClimbRate *= 0.005f * (mpDBObject->maxAltitude_m - mcKin.mfAlt_m);
	}

    if ((dalt_m > fHighZone)||(dalt_m < fLowZone)) 
    {
        fAltitudeRate_mps = (dalt_m >= 0) ? maxClimbRate : maxDescentRate;
    }
    else if (dalt_m < 0) 
    {
        fAltitudeRate_mps = maxDescentRate*(dalt_m/fLowZone) + 2.0f;
    }
    else 
    {
        fAltitudeRate_mps = maxClimbRate*(dalt_m/fHighZone) + 2.0f;
    }

	// restrict climb to altitude rate
    if (fuel_kg > 0)
    {
	    dalt_max = fAltitudeRate_mps * dt_s;
        dalt_min = (mcKin.mfAlt_m <= 200.0f) ? -dalt_max : -2.0f*dalt_max;
    }
    else
    {
	    dalt_max = -30.0f * dt_s;
        dalt_min = -50.0f * dt_s;
    }

    if (dalt_m < dalt_min) {dalt_m = dalt_min;} 
    else if (dalt_m > dalt_max) {dalt_m = dalt_max;}

	mcKin.mfAlt_m += dalt_m;
	
}

/**
* No min speed for helo, can hover
*/
void tcHeloObject::UpdateSpeed(float dt_s)
{
    float ds_kts = mcGS.mfGoalSpeed_kts - mcKin.mfSpeed_kts;
    float ds_max = mpDBObject->mfAccel_ktsps*dt_s;
    float ds_min = -ds_max;

    if (ds_kts < ds_min) {ds_kts = ds_min;} // restrict to acceleration
    else if (ds_kts > ds_max) {ds_kts = ds_max;}
    mcKin.mfSpeed_kts += ds_kts;

	if (mcKin.mfSpeed_kts < 0) mcKin.mfSpeed_kts = 0;

	// if a fuel capacity is indicated then update fuel consumption
	if (!mpDBObject->HasInfiniteFuel())
	{
		// do not allow fuel consumption to be less than a minimum value (hover consumes fuel)
		float fuelConsumptionSpeed = max(mcKin.mfSpeed_kts, 50.0f);

		fuel_kg -= dt_s * mpDBObject->GetFuelConsumptionConstant(0) * fuelConsumptionSpeed;
		if (fuel_kg < 0) fuel_kg = 0;

		if (fuel_kg == 0)
		{
			if (mcKin.mfSpeed_kts > 0) mcKin.mfSpeed_kts -= 2*ds_max;
			//if (mcKin.mfAlt_m > 0) mcKin.mfAlt_m -= dt_s * 10;
		}
	}
}


void tcHeloObject::Update(double afStatusTime) 
{
    const float min_update_s = 0.0f;
    float dt_s = (float)(afStatusTime - mfStatusTime);

    UpdateEffects();

    // shouldn't be called for child objects
    if (parent != NULL) {return;} // captive, let parent update if applicable
    if (dt_s <= min_update_s) {return;} // added for pause case
    wxASSERT(mpDBObject);


    if (mfDamageLevel >= 1.0f)
    {
        UpdateDestroyed(afStatusTime);
        mfStatusTime = afStatusTime;
        return;
    }

   // UpdateFormationGuidance(); // formation heading/speed calculation

	/* In multiplayer mode, skip command based updates for client objects not controlled
	** by client. This will cause object to jump more but avoids having to broadcast command
	** changes to all alliance clients. The controller of the object will see smoother
	** behavior.
	*/
	if (!IsClientMode() || IsControlled())
	{
        formation.Update((tcAirObject*)this);

		// don't use air method since we don't care about roll
		tcPlatformObject::UpdateHeading(dt_s); 

		UpdateSpeed(dt_s);

		UpdateClimb(dt_s);

		ApplyRestrictions(); // crash check
	}

    Move(dt_s);

    UpdateLauncherState(dt_s);

    UpdateSensors(afStatusTime);

    UpdateAI(afStatusTime);

    Update3D();

    mfStatusTime = afStatusTime; 
}


void tcHeloObject::UpdateDestroyed(double t)
{
    float dt_s = (float)(t - mfStatusTime);

    if (mcKin.mfSpeed_kts <= 100.0f)
    {
        mcKin.mfSpeed_kts += 20.0f * dt_s;
    }

    if (mcKin.mfClimbAngle_rad > -0.3f)
    {
        mcKin.mfClimbAngle_rad -= 0.1f * dt_s;
    }

    mcKin.mfPitch_rad = mcKin.mfClimbAngle_rad;
    mcKin.mfRoll_rad += 0.2f * dt_s;

    if ((mcKin.mfAlt_m <= mcTerrain.mfHeight_m + 20.0f) || 
        (mcKin.mfAlt_m <= 20.0f))
    {
        doneCrashing = true;
    }

    Move(dt_s);
}


tcHeloObject::tcHeloObject() 
{
    mnModelType = MTYPE_HELO;

    SetAltitude(1000.0f);
    SetHeading(75.0f);
    SetSpeed(100.0f);
    readyForLanding = 0;
}

/**
* Constructor that initializes using info from database entry.
*/
tcHeloObject::tcHeloObject(tcAirDBObject *obj)
: tcAirObject(obj)
{
    mnModelType = MTYPE_HELO;
}

tcHeloObject::~tcHeloObject()
{
}
