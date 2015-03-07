/** 
**  @file tcSubObject.cpp 
**  Basic submarine model
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

#include "tcSubObject.h"
#include "tcSubDBObject.h"
#include "tcSonar.h"
#include "tcSonarDBObject.h"
#include "tc3DModel.h"
#include "tcMessageInterface.h"
//#include "tcParticleEffect.h"
#include "common/tcObjStream.h"
#include "common/tcGameStream.h"
#include "ai/brain.h"
#include "ai/task.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/******************************************************************************/
/****************************** tcSubObject *******************************/
/******************************************************************************/

/**
*
*/
tcCommandStream& tcSubObject::operator<<(tcCommandStream& stream)
{
    tcPlatformObject::operator<<(stream);

	unsigned char mastFlags;
	stream >> mastFlags;

	SetPeriscopeState((mastFlags & PERISCOPE) != 0);
	SetRadarMastState((mastFlags & RADARMAST) != 0);
	SetSnorkelState((mastFlags & SNORKEL) != 0);

	commandObj.ClearNewCommand();

    return stream;
}

/**
*
*/
tcCommandStream& tcSubObject::operator>>(tcCommandStream& stream)
{
    tcPlatformObject::operator>>(stream);

	unsigned char mastFlags = 0;
	if (periscopeRaised) mastFlags |= PERISCOPE;
	if (radarMastRaised) mastFlags |= RADARMAST;
	if (isSnorkeling) mastFlags |= SNORKEL;

	stream << mastFlags;

    return stream;
}

/**
*
*/
tcUpdateStream& tcSubObject::operator<<(tcUpdateStream& stream)
{
    tcPlatformObject::operator<<(stream);

    stream >> batteryCharge;

    return stream;
}

/**
*
*/
tcUpdateStream& tcSubObject::operator>>(tcUpdateStream& stream)
{
    tcPlatformObject::operator>>(stream);

    stream << batteryCharge;

    return stream;
}

/**
* Load
*/
tcGameStream& tcSubObject::operator<<(tcGameStream& stream)
{
    tcPlatformObject::operator<<(stream);

    commandObj << stream;
    stream >> radarMastRaised;
    stream >> periscopeRaised;
	stream >> isSnorkeling;
    stream >> periscopeDepth_m;
    stream >> invPeriscopeDepth;
    stream >> lastDepth_m;
    stream >> doneSinking;
	stream >> batteryCharge;

    return stream;
}

/**
* Save
*/
tcGameStream& tcSubObject::operator>>(tcGameStream& stream)
{
    tcPlatformObject::operator>>(stream);

    commandObj >> stream;
    stream << radarMastRaised;
    stream << periscopeRaised;
	stream << isSnorkeling;
    stream << periscopeDepth_m;
    stream << invPeriscopeDepth;
    stream << lastDepth_m;
    stream << doneSinking;
	stream << batteryCharge;

    return stream;
}


/**
*
*/
void tcSubObject::ClearNewCommand()
{
    tcPlatformObject::ClearNewCommand();
    commandObj.ClearNewCommand();
}

bool tcSubObject::HasNewCommand() const
{
    return tcPlatformObject::HasNewCommand() || commandObj.HasNewCommand();
}


bool tcSubObject::IsDestroyed()
{
    return (mfDamageLevel >= 1.0f) && doneSinking;
}


/**
*
*/
void tcSubObject::Clear()  
{  
    tcPlatformObject::Clear();
}

/**
*
*/
void tcSubObject::RandInitNear(float afLon_deg, float afLat_deg)
{
    if (mpDBObject == NULL) {return;}
    mzClass = mpDBObject->mzClass;
    mzUnit = "SUB_";
    mzUnit.AssignRandomSuffix();

    mfStatusTime = 0;        
    mcKin.mfLon_rad = C_PIOVER180*(afLon_deg + randfc(1.1f));      
    mcKin.mfLat_rad = C_PIOVER180*(afLat_deg + randfc(1.1f));
    mcKin.mfAlt_m = -65.0f;               
    mcKin.mfHeading_rad = C_TWOPI*randf();           
    mcKin.mfSpeed_kts = 0.20f*mpDBObject->mfMaxSpeed_kts;
    mcKin.mfPitch_rad = 0;
    mcKin.mfRoll_rad = 0;
    mfDamageLevel = 0;  
    SetHeading(mcKin.mfHeading_rad);
    SetSpeed(mcKin.mfSpeed_kts);   
    SetAltitude(mcKin.mfAlt_m);
}

/**
*
*/
void tcSubObject::PrintToFile(tcFile& file) 
{
    tcPlatformObject::PrintToFile(file);
}

/**
*
*/
void tcSubObject::SaveToFile(tcFile& file) 
{
    tcPlatformObject::SaveToFile(file); 
}

/**
*
*/
void tcSubObject::LoadFromFile(tcFile& file) 
{
    tcPlatformObject::LoadFromFile(file);
}

/**
*
*/
void tcSubObject::Serialize(tcFile& file, bool mbLoad)
{
    if (mbLoad) 
    {
        LoadFromFile(file);
    }
    else {
        SaveToFile(file);
    }
}

float tcSubObject::GetBatteryCharge() const
{
	return batteryCharge;
}

/**
* @return periscope depth in meters (negative number)
*/
float tcSubObject::GetPeriscopeDepth() const
{
    return periscopeDepth_m;
}

/**
*
*/
bool tcSubObject::GetPeriscopeState() const
{
    return periscopeRaised;
}

/**
*
*/
bool tcSubObject::GetRadarMastState() const
{
    return radarMastRaised;
}


/**
* @returns sonar source level of object or, if object has active sonar on, maximum of source level of 
* target and max active sonar source level.
*/
float tcSubObject::GetSonarSourceLevel(float az_deg) const
{
    float speed_mps = C_KTSTOMPS * mcKin.mfSpeed_kts;

    float SLp = mpDBObject->GetSourceLevel(speed_mps, -mcKin.mfAlt_m, az_deg);

    if (mpDBObject->IsCavitatingMps(speed_mps, -mcKin.mfAlt_m) || isSnorkeling)
    {
		float SL_special = isSnorkeling ? mpDBObject->GetSnorkelingSourceLevel() : mpDBObject->GetCavitatingSourceLevel();
		SLp = std::max(SLp, SL_special);
    }
    
	if (!IsEnsonifying()) return SLp;

	const tcSonar* sonar = GetStrongestActiveSonar();
	if (sonar && (sonar->mpDBObj->SL > SLp))
	{
		return sonar->mpDBObj->SL;
	}
	else
	{
		return SLp;
	}
}

bool tcSubObject::IsAtPeriscopeDepth() const
{
    return mcKin.mfAlt_m >= -periscopeDepth_m;
}

/**
* @return true if this is a diesel electric submarine
*/
bool tcSubObject::IsDieselElectric() const
{
	return mpDBObject->isDieselElectric;
}

/**
* @return true if snorkeling, false otherwise
*/
bool tcSubObject::IsSnorkeling() const
{
	return isSnorkeling;
}


bool tcSubObject::IsSurfaced() const
{
    return mcKin.mfAlt_m >= 0;
}


void tcSubObject::SetAltitude(float new_altitude_m)
{
    tcPlatformObject::SetAltitude(new_altitude_m);

    bool isScopeDepth = IsAtPeriscopeDepth();
    SetRadarMastState(isScopeDepth);
    SetPeriscopeState(isScopeDepth);
}

/**
*
*/
void tcSubObject::SetPeriscopeState(bool state)
{
	if (periscopeRaised == state) return;

    periscopeRaised = state;

    //if (IsHooked() && IsOwnAlliance() && (mcKin.mfAlt_m >= -periscopeDepth_m))
    //{
    //    std::string s;
    //    if (state) s = "Raising ";
    //    else s = "Lowering";
    //    s += "scope, aye.";

    //    tcMessageInterface::Get()->PopupMessage(s);
    //}

	commandObj.SetNewCommand(MAST_CMD);
}

/**
*
*/
void tcSubObject::SetRadarMastState(bool state)
{
	if (radarMastRaised == state) return;

    radarMastRaised = state;

    //if (IsHooked() && IsOwnAlliance() && (mcKin.mfAlt_m >= -periscopeDepth_m))
    //{
    //    std::string s;
    //    if (state) s = "Raising ";
    //    else s = "Lowering";
    //    s += "the radar mast, aye.";

    //    tcMessageInterface::Get()->PopupMessage(s);
    //}

	commandObj.SetNewCommand(MAST_CMD);
}

/**
* Diesel-electric boats only
*/
void tcSubObject::SetSnorkelState(bool state)
{
	if (!IsDieselElectric()) return;

	if (isSnorkeling == state) return;

	isSnorkeling = state;


	commandObj.SetNewCommand(MAST_CMD);
}

/**
*
*/
void tcSubObject::ApplyRestrictions() 
{
    // check for crash (bottom)
    if ((mcTerrain.mfHeight_m + mpDBObject->draft_m) > mcKin.mfAlt_m)
    {
        if (mcKin.mfSpeed_kts > 10.0f)
        {
            ApplyGeneralDamage(1.0f, 0);
        }
        else
        {
            ApplyGeneralDamage(0.1f, 0);
            mcKin.mfAlt_m = mcTerrain.mfHeight_m + mpDBObject->draft_m + 0.1f;
            mcKin.mfClimbAngle_rad = 0;
            mcKin.mfPitch_rad = 0;
            SetAltitude(std::max(mcKin.mfAlt_m, -periscopeDepth_m));
        }
    }

    if (mcKin.mfAlt_m < -periscopeDepth_m)
    {
        SetPeriscopeState(false);
        SetRadarMastState(false);
		SetSnorkelState(false);

		if (mcKin.mfSpeed_kts > 0)
		{
			mcKin.mfSpeed_kts = std::min(mcKin.mfSpeed_kts, mpDBObject->mfMaxSpeed_kts); // restrict speed for case where surface speed > submerged
		}
		else
		{
			mcKin.mfSpeed_kts = std::max(mcKin.mfSpeed_kts, mpDBObject->mfMaxSpeed_kts * -0.5f); // restrict speed for case where surface speed > submerged
		}
    }
    else if (mcKin.mfAlt_m <= 0) // restrict speed near surface
    {
        float maxSpeed_kts = GetMaxSpeedForDepth(mcKin.mfAlt_m);
		if (mcKin.mfSpeed_kts > 0 && mcKin.mfSpeed_kts > maxSpeed_kts)
        {
            mcKin.mfSpeed_kts = maxSpeed_kts;
        }
		else if (mcKin.mfSpeed_kts < 0 && mcKin.mfSpeed_kts < maxSpeed_kts * 0.5)
        {
            mcKin.mfSpeed_kts = maxSpeed_kts * -0.5;
        }
    }
    else if (mcKin.mfAlt_m > 0)
    {
        mcKin.mfAlt_m = 0; // subs can't fly
        mcKin.mfClimbAngle_rad = 0;
    }
}

float tcSubObject::GetMaxQuietSpeedKts() const
{
    float depth_m = -mcKin.mfAlt_m;
    //float goalDepth_m = -mcGS.mfGoalAltitude_m;
    //float currentSpeed_kts = mcKin.mfSpeed_kts;

    float maxQuietSpeed_kts = mpDBObject->GetCavitationSpeedKts(depth_m) - 0.25f;

    return maxQuietSpeed_kts;
}

/**
* Accounts for different max speed on surface vs. submerged
* @param altitude_m negative of depth
*/
float tcSubObject::GetMaxSpeedForDepth(float altitude_m) const
{
    float alpha = -invPeriscopeDepth * altitude_m; // 0 at surface, 1 at periscope depth
    float maxSpeed_kts = std::min(alpha * mpDBObject->mfMaxSpeed_kts + (1.0f - alpha) * mpDBObject->surfaceSpeed_kts,mpDBObject->mfMaxSpeed_kts);

    return maxSpeed_kts;
}


float tcSubObject::GetOpticalCrossSection() const
{
    if (mcKin.mfAlt_m < -GetPeriscopeDepth())
    {
        return -999.0f;
    }

    if (mcKin.mfAlt_m >= 0)
    {
        return mpDBObject->opticalCrossSection_dBsm;
    }

    // periscope depth < depth < 0
    float body_factor = -999.0f;

    if (mcKin.mfAlt_m >= -mpDBObject->draft_m)
    {
        float alpha = mpDBObject->GetInvDraft() * mcKin.mfAlt_m; // 0 to -1, more negative with depth
        body_factor = mpDBObject->opticalCrossSection_dBsm + alpha * 12.0f;
    }

    if (periscopeRaised)
    {
        float speed_factor = std::min(0.5f*mcKin.mfSpeed_kts, 10.0f);
        float periscope_factor = mpDBObject->opticalCrossSection_dBsm - 15.0f + speed_factor;
        return std::max(body_factor, periscope_factor);
    }
    else
    {
        return body_factor;
    }
}



float tcSubObject::GetIRSignature(float az_deg) const
{
    if (mcKin.mfAlt_m < -GetPeriscopeDepth())
    {
        return -999.0f;
    }

    float signature = -999.0f;

    if (mcKin.mfAlt_m >= -mpDBObject->draft_m)
    {
        float alpha = mpDBObject->GetInvDraft() * mcKin.mfAlt_m; // 0 to -1, more negative with depth

        signature = mpDBObject->GetIRSig_dB(az_deg, tcAirDetectionDBObject::IRMODELA) + alpha * 12.0f;
    }

    if (isSnorkeling)
    {
        signature = std::max(signature, mpDBObject->GetIRSig_dB(az_deg, tcAirDetectionDBObject::IRMODELB));
    }


    return signature;
}

/**
* Update climb related parameters. This has problems for large time 
* steps, > about 1 sec
*/
void tcSubObject::UpdateClimb(float dt_s) 
{
    // restrict to max depth 
    if (mcGS.mfGoalAltitude_m < -mpDBObject->mfMaxDepth_m)
    {
        mcGS.mfGoalAltitude_m = -mpDBObject->mfMaxDepth_m;
    }

    // avoid bottoming out
    float minGoalAltitude_m = mcTerrain.mfHeight_m + mpDBObject->draft_m + 3.0f;
    if (mcGS.mfGoalAltitude_m < minGoalAltitude_m)
    {
        mcGS.mfGoalAltitude_m = minGoalAltitude_m;
    }
    else if (mcGS.mfGoalAltitude_m > 0)
    {
        mcGS.mfGoalAltitude_m = 0;
    }

    float dalt_m = mcGS.mfGoalAltitude_m - mcKin.mfAlt_m;

    const float levelThresh_rad = 0.0035f; // 0.2 deg
    if ((dalt_m > -0.05f)&&(dalt_m < 0.05f)&&
        (mcKin.mfClimbAngle_rad < levelThresh_rad)&&(mcKin.mfClimbAngle_rad > -levelThresh_rad)) 
    {
        mcKin.mfClimbAngle_rad = 0;
        mcKin.mfPitch_rad = 0; 
        mcKin.mfAlt_m += dalt_m;

        if (dalt_m == 0)
        {
            return;
        }
    }


    const float fHighZone = 50.0f;
    const float fLowZone = -50.0f;
   
    float goalPitch = 0;

    float maxPitch = maxPitch_rad;
    if (mcKin.mfAlt_m > -10) maxPitch *= 0.5f;

    if (dalt_m > fHighZone) 
    {
        goalPitch = maxPitch_rad;
    }
    else if (dalt_m < fLowZone)
    {
        goalPitch = -maxPitch_rad;
    }
    else 
    {
        goalPitch = 0.02f * dalt_m * maxPitch_rad;
    }

    if (goalPitch > maxPitch) goalPitch = maxPitch;
    else if (goalPitch < -maxPitch) goalPitch = -maxPitch;

    float oldAngle_rad = mcKin.mfClimbAngle_rad;

	bool divingNearBottom = (mcKin.mfAlt_m < minGoalAltitude_m + 10.0f) && (goalPitch <= 0);

	float dPitchMax_rad = (!divingNearBottom) ? dt_s * 0.1f : dt_s * 0.2f;

	float dPitch_rad = goalPitch - oldAngle_rad;
	if (dPitch_rad > dPitchMax_rad) dPitch_rad = dPitchMax_rad;
	else if (dPitch_rad < -dPitchMax_rad) dPitch_rad = -dPitchMax_rad;

	//float alpha = divingNearBottom ? 0.6f : 0.2f; // (goalPitch < 0) ? 0.1f * dt_s : 0.15f * dt_s;  // 20101127 increased this for issue related to hitting bottom during high speed dives

    mcKin.mfClimbAngle_rad = oldAngle_rad + dPitch_rad; // alpha*goalPitch + (1-alpha)*oldAngle_rad;

    mcKin.mfPitch_rad = mcKin.mfClimbAngle_rad; 

    // add slow vertical ascent/descent component near surface or for near stopped sub (e.g. out of battery)
	if ((mcKin.mfAlt_m > -5) || (abs(mcKin.mfSpeed_kts) < 1))
    {
        float dz = (dalt_m > 0) ? 0.5f * dt_s : -0.5f * dt_s;
        mcKin.mfAlt_m += dz;
    }

    // automatically raise/lower radar mast and scope
    bool isScopeDepth = IsAtPeriscopeDepth();
    SetRadarMastState(isScopeDepth);
    SetPeriscopeState(isScopeDepth);

    if (IsSurfaced())
    {
        SetSnorkelState(true);
    }

}


void tcSubObject::UpdateDestroyed(double t)
{
    float dt_s = (float)(t - mfStatusTime);

    if (mcKin.mfSpeed_kts <= 12.0f)
    {
        mcKin.mfSpeed_kts += 1.0f * dt_s;
    }
    else
    {
        mcKin.mfSpeed_kts = 12.0f;
    }

    if (mcKin.mfClimbAngle_rad > -0.3f)
    {
        mcKin.mfClimbAngle_rad -= 0.1f * dt_s;
    }

    mcKin.mfPitch_rad = mcKin.mfClimbAngle_rad;


    if (mcKin.mfAlt_m <= mcTerrain.mfHeight_m + 5.0f)
    {
        doneSinking = true;
    }

    Move(dt_s);
}

/**
*
*/
void tcSubObject::UpdateEffects()
{
    if (model)
    {
        if ((mcKin.mfAlt_m < -10)&&(mcKin.mfSpeed_kts > 10))
		{
            model->SetSmokeMode(tc3DModel::BUBBLES);
		}
        else
        {
            model->SetSmokeMode(tc3DModel::OFF);
        }
        model->UpdateEffects();
    }
}

/**
*
*/
void tcSubObject::UpdateHeading(float dt_s) 
{
    if (dt_s == 0) {return;}

    tcPlatformObject::UpdateHeading(dt_s);

    mcKin.mfRoll_rad = 0;
}

/**
* Messages to user
*/
void tcSubObject::UpdateMessages()
{
    if (!IsHooked() || !IsOwnAlliance()) 
    {
        lastDepth_m = -mcKin.mfAlt_m;
        return;
    }

    if (mfStatusTime < 5) return;


    //if ((-mcKin.mfAlt_m <= periscopeDepth_m) && (lastDepth_m > periscopeDepth_m))
    //{
    //    tcMessageInterface::Get()->PopupMessage("The boat is at periscope depth, sir.");
    //}


    lastDepth_m = -mcKin.mfAlt_m;
}

/**
* Update radars if radar mast is raised
* Update visual sensors if periscope is raised
* Deactivate sensors that do not have mast/periscope in required state
* Update sensor height for periscope and radar mast to be 4.0 m above water
*/
void tcSubObject::UpdateSensors(double t)
{
    if (clientMode) return; // no sensor update for client

    unsigned nSensors = GetSensorCount();
    for(unsigned n=0; n<nSensors; n++)
    {
        tcSensorState* sensor = GetSensorMutable(n);
        wxASSERT(sensor);
        if (sensor->IsSonar())
        {
        }
        else if (sensor->IsRadar() && radarMastRaised)
        {
            sensor->mfSensorHeight_m = 4.0f + mcKin.mfAlt_m;
        }
        else if ((sensor->IsESM() && radarMastRaised) ||
                 (sensor->IsOptical() && periscopeRaised))
        {
            sensor->mfSensorHeight_m = 4.0f + mcKin.mfAlt_m;
            sensor->SetActive(true); // assume ESM and optical always active if possible
        }

        else
        {
            SetSensorState(n, false); // vs. sensor->SetActive(false) to have correct multiplayer messages sent
        }
    }

    tcSensorPlatform::Update(t);
}

/**
*
*/
void tcSubObject::UpdateSpeed(float dt_s)
{
	float ds_kts = mcGS.mfGoalSpeed_kts - mcKin.mfSpeed_kts;
	float ds_max = mpDBObject->mfAccel_ktsps*dt_s;
	float ds_min = -ds_max;

	if (ds_kts < ds_min) {ds_kts = ds_min;} // restrict to acceleration
	else if (ds_kts > ds_max) {ds_kts = ds_max;}
	mcKin.mfSpeed_kts += ds_kts;

	//if (mcKin.mfSpeed_kts < 0) mcKin.mfSpeed_kts = 0;  amram - allowing subs to reverse

	if (!IsDieselElectric()) return;

	// update battery and fuel state for diesel electric subs

	float speed_mps = C_KTSTOMPS * mcKin.mfSpeed_kts;
	float batteryRate = -mpDBObject->GetBatteryRate(speed_mps);
	
	if (isSnorkeling && (fuel_kg > 0)) 
	{
		batteryRate += mpDBObject->batteryCharge_kW;
	    fuel_kg -= dt_s * mpDBObject->mfFuelRate_kgps;
	}

	batteryCharge += dt_s * batteryRate; 
	if (batteryCharge <= 0)
	{
		batteryCharge = 0;
		if (mcKin.mfSpeed_kts > 0) mcKin.mfSpeed_kts -= 2*ds_max;

		if (mcKin.mfSpeed_kts < 0) mcKin.mfSpeed_kts += 2*ds_max;  //amram - permitting recharge while backing up for subs
	}
	else if (batteryCharge > mpDBObject->batteryCapacity_kJ)
	{
		batteryCharge = mpDBObject->batteryCapacity_kJ;
	}


	if (fuel_kg <= 0)
	{
		SetSnorkelState(false);
		fuel_kg = 0;
	}
}

/**
*
*/
void tcSubObject::Update(double afStatusTime) 
{
    const float min_update_s = 0.0f;
    float dt_s = (float)(afStatusTime - mfStatusTime);

    UpdateEffects();

    // shouldn't be called for child objects
    if (parent != NULL) {return;} // captive, let parent update if applicable
    if ((dt_s <= min_update_s)&& !tcGameObject::IsEditMode()) {return;} // added for pause case
    wxASSERT(mpDBObject);

    if (mfDamageLevel >= 1.0f)
    {
        UpdateDestroyed(afStatusTime);
        mfStatusTime = afStatusTime;
        return;
    }


    UpdateFormationGuidance(); // formation heading/speed calculation


	/* In multiplayer mode, skip command based updates for client objects not controlled
	** by client. This will cause object to jump more but avoids having to broadcast command
	** changes to all alliance clients. The controller of the object will see smoother
	** behavior.
	*/
	if (!IsClientMode() || IsControlled())
	{
		UpdateHeading(dt_s);

		UpdateSpeed(dt_s);

		UpdateClimb(dt_s);

		ApplyRestrictions(); // crash check
	}

    Move(dt_s);

    UpdateLauncherState(dt_s);

    UpdateMagazines(afStatusTime);

    UpdateSensors(afStatusTime);

    UpdateMessages();

    UpdateAI(afStatusTime);

    Update3D();

    mfStatusTime = afStatusTime; 
}


/**
*
*/
tcSubObject::tcSubObject()
: maxPitch_rad(0.5),
  periscopeDepth_m(18)
{
    mnModelType = MTYPE_SUBMARINE;
    invPeriscopeDepth = 1.0f / periscopeDepth_m;
    
    SetAltitude(-100.0f);
    SetHeading(75.0f);
    SetSpeed(7.0f);
}

/**
* Constructor that initializes using info from database entry.
*/
tcSubObject::tcSubObject(tcSubDBObject* obj)
: tcPlatformObject(obj),
  maxPitch_rad(0.5),
  periscopeDepth_m(18),
  doneSinking(false),
  isSnorkeling(false),
  mpDBObject(obj),
  batteryCharge(obj->batteryCapacity_kJ)
{
    mnModelType = MTYPE_SUBMARINE;
    
    invPeriscopeDepth = 1.0f / periscopeDepth_m;

    if (addTasksOnCreate)
    {
        brain->AddTaskDirectly("SubEvade", 3.0, ai::Task::HIDDEN | ai::Task::PERMANENT);
        brain->AddTaskDirectly("AvoidCav", 3.0, ai::Task::HIDDEN | ai::Task::PERMANENT);
        brain->AddTaskDirectly("SubBattery", 4.0, ai::Task::HIDDEN | ai::Task::PERMANENT);
    }
}

/**
*
*/
tcSubObject::~tcSubObject()
{
}
