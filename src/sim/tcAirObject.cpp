/** 
**  @file tcAirObject.cpp 
**  Basic aircraft model
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

#include "tcAirObject.h"
#include "tcAirDBObject.h"
#include "tc3DModel.h"
#include "tcLauncher.h"
//#include "tcParticleEffect.h"
#include "tcSimState.h"
#include "common/tcObjStream.h"
#include "tcGameStream.h"
#include "tcStores.h"
#include "tcMessageInterface.h"
#include "ai/Brain.h"
#include "ai/Task.h"
#include "tcFloatCompressor.h"
#include "tcFuelTankDBObject.h"
#include "tcBallisticDBObject.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/******************************************************************************/
/****************************** tcAirObject *******************************/
/******************************************************************************/

tcCommandStream& tcAirObject::operator<<(tcCommandStream& stream)
{
	ClearNewCommand();

    tcPlatformObject::operator<<(stream);

	stream >> readyForLanding;

    return stream;
}

tcCommandStream& tcAirObject::operator>>(tcCommandStream& stream)
{
    tcPlatformObject::operator>>(stream);

    stream << readyForLanding;

    return stream;
}

tcUpdateStream& tcAirObject::operator<<(tcUpdateStream& stream)
{
    tcPlatformObject::operator<<(stream);

	stream >> fuel_kg;

    stream >> tcAngleCompressor(maxPitch_rad);

    UpdateLoadoutTag();

    return stream;
}

tcUpdateStream& tcAirObject::operator>>(tcUpdateStream& stream)
{
    tcPlatformObject::operator>>(stream);

	stream << fuel_kg;

    stream << tcAngleCompressor(maxPitch_rad);

    return stream;
}

/**
* Load
*/
tcGameStream& tcAirObject::operator<<(tcGameStream& stream)
{
    tcPlatformObject::operator<<(stream);

    commandObj << stream;
    stream >> readyForLanding;
    stream >> maxPitch_rad;
    stream >> climbCommand_rad;
	stream >> doneCrashing;

    fuelTargets.clear();
    unsigned char nFuelTargets;
    stream >> nFuelTargets;
    for (unsigned char n=0; n<nFuelTargets; n++)
    {
        long id;
        stream >> id;
        fuelTargets.push_back(id);
    }

    return stream;
}

/**
* Save
*/
tcGameStream& tcAirObject::operator>>(tcGameStream& stream)
{
    tcPlatformObject::operator>>(stream);

    commandObj >> stream;
    stream << readyForLanding;
    stream << maxPitch_rad;
    stream << climbCommand_rad;
	stream << doneCrashing;

    unsigned char nFuelTargets = fuelTargets.size();
    stream << nFuelTargets;
    for (unsigned char n=0; n<nFuelTargets; n++)
    {
        stream << fuelTargets[n];
    }

    return stream;
}


/**
* @return true if id successfully added as fuel target
*/
bool tcAirObject::AddFuelTarget(long id)
{
    const float maxRefuelRange_km = 0.25f;

    size_t nFuelPoints = (size_t)mpDBObject->outFuelPods;
    if (fuelTargets.size() >= nFuelPoints) return false;

    tcAirObject* target = dynamic_cast<tcAirObject*>(simState->GetObject(id));
    if (target == 0) return false;
    if (target->GetAffiliationWith(this->GetAlliance()) != tcAllianceInfo::FRIENDLY)
    {
        return false;
    }
    
    if (!target->CanRefuelInFlight()) return false;

    float range_km = mcKin.RangeToKmAlt(target->mcKin);
    if (range_km > maxRefuelRange_km) return false;

    // check that id isn't already in fuelTargets
    for (size_t n=0; n<fuelTargets.size(); n++)
    {
        if (fuelTargets[n] == id) return true;
    }

    fuelTargets.push_back(id);
    return true;
}


void tcAirObject::ClearNewCommand()
{
    tcPlatformObject::ClearNewCommand();
    commandObj.ClearNewCommand();
}

bool tcAirObject::HasNewCommand() const
{
    return tcPlatformObject::HasNewCommand() || commandObj.HasNewCommand();
}

/**
* @return gravity bomb elevation at present speed and altitude that would hit specified target at 0 m AGL
* @return pi if no solution exists (out of range)
*/
float tcAirObject::CalculateBombElevationRad(float targetLon_rad, float targetLat_rad) const
{
    const float noSolution = C_PI;

    float terrain_m = mapData->GetTerrainHeight(targetLon_rad * C_180OVERPI, targetLat_rad * C_180OVERPI,
			simState->GetTime());

    float groundRange_m = mcKin.RangeToM(targetLon_rad, targetLat_rad);

    float h_m = terrain_m - mcKin.mfAlt_m;

    float speed_mps = C_KTSTOMPS * mcKin.mfSpeed_kts;

    const float min_x2 = 0.5f; // +/-45 deg
    float tti_s = 0;
    float elevation_rad = tcBallisticDBObject::CalculateBallisticElevation(groundRange_m, h_m, speed_mps, min_x2, tti_s);

    return elevation_rad;
}

bool tcAirObject::CanRefuelInFlight() const
{
    return (mpDBObject->fuelIn_kgps > 0);
}

float tcAirObject::GetClimbCommand() const
{
    return climbCommand_rad;
}


bool tcAirObject::IsTanker() const
{
    return (mpDBObject->outFuelPods > 0);
}

/**
* If overweight, automatically lighten load to reduce weight
*/
void tcAirObject::LightenLoad()
{
    const float defuelThreshold = 0.15; // defuel up to this fraction of INTERNAL fuel load to lighten weight

    if (IsLoading() || IsRefueling()) return; // wait for current load or fuel op to finish

    tcPlatformObject* parentPlatform = dynamic_cast<tcPlatformObject*>(parent);
    if (parentPlatform == 0)
    {
        fprintf(stderr, "tcAirObject::LightenLoad - no host platform (%s)\n", 
            GetName());
        wxASSERT(false);
        return; // not landed or docked, or parent is not tcPlatformObject
    }

    float excessWeight_kg = GetTotalWeight() - mpDBObject->maxTakeoffWeight_kg;
    if (excessWeight_kg <= 0) return;




    // defuel a little if that fixes it
    if (excessWeight_kg < (defuelThreshold*mpDBObject->GetInternalFuelCapacity()))
    {
        size_t nMagazines = parentPlatform->GetMagazineCount();
        bool searching = true;
        for (size_t n=0; (n<nMagazines) && searching; n++)
        {
            tcStores* mag = parentPlatform->GetMagazine(n);
            if (mag->IsCompatible("Fuel"))
            {
                bool result = mag->UnloadOther("Fuel", unsigned long(excessWeight_kg)+1, this);
                searching = false;
                if (result) return;
            }
        }
    }

    // try to unload one of the heaviest weapons or fuel tanks
    size_t nLaunchers = GetLauncherCount();

    int heaviestIdx = -1;
    float heaviestItem_kg = 1e9f;
    for (size_t n=0; n<nLaunchers; n++)
    {
        const tcLauncher* launcher = GetLauncher(n);
        float itemWeight_kg = launcher->GetItemWeight();
        tcWeaponDBObject* weaponData = dynamic_cast<tcWeaponDBObject*>(launcher->mpChildDBObj);
        tcFuelTankDBObject* tankData = dynamic_cast<tcFuelTankDBObject*>(launcher->mpChildDBObj);
        if ((launcher->mnCurrent > 0) && (itemWeight_kg < heaviestItem_kg) && 
            ((weaponData != 0) || (tankData != 0)))
        {
            heaviestItem_kg = itemWeight_kg;
            heaviestIdx = int(n);
        }
    }

    if (heaviestIdx >= 0)
    {
        // find a mag that will accept unload, and schedule unload
        const tcLauncher* launcher = GetLauncher(heaviestIdx);
        wxASSERT(launcher != 0);
        std::string itemName = launcher->GetChildClassName();
        
        size_t nMagazines = parentPlatform->GetMagazineCount();
        for (size_t n=0; n<nMagazines; n++)
        {
            tcStores* mag = parentPlatform->GetMagazine(n);
            if (mag->CanUnloadThisObject(this) && (mag->IsCompatible(itemName)))
            {
                bool result = mag->UnloadLauncher(heaviestIdx, this, 1);
                if (result)
                {
                    return;
                }
            }
        }
    }


}


void tcAirObject::Clear()  
{  
    tcPlatformObject::Clear();
}


float tcAirObject::GetCruiseRangeKm(float alt_m) const
{
	float cruise_kts = GetCruiseSpeedForAltitude(alt_m);
	float cruise_kps = (0.001f * C_KTSTOMPS) * cruise_kts;

	float fuelRate_kgps = mpDBObject->GetFuelConsumptionConstant(cruise_kts) * cruise_kts;
	if (fuelRate_kgps > 0)
	{
		float time_s = fuel_kg / fuelRate_kgps;
		float distance_km = cruise_kps * time_s;
		return distance_km;
	}
	else
	{
		return 99999.0f;
	}
}

float tcAirObject::GetCruiseAltitude() const
{
    return 6000.0f; // put non-aero model aircraft at about 20,000 ft
}

/**
* @return cruise speed in kts
*/
float tcAirObject::GetCruiseSpeedForAltitude(float alt_m) const
{
    return 0.7f * mpDBObject->mfMaxSpeed_kts; // set to 70% max for simple model (fuel penalty above this speed)
}

/**
* @return stall speed in kts (use 0 speed for non-aero, should limit to minimum)
*/
float tcAirObject::GetStallSpeedForAltitude(float alt_m) const
{
    return 0;
}


float tcAirObject::GetOpticalCrossSection() const
{
    return mpDBObject->opticalCrossSection_dBsm;
}



float tcAirObject::GetIRSignature(float az_deg) const
{
    bool isSupersonic = (mcKin.mfSpeed_kts > 600.0f); // a rough test, no altitude variation

    if (!isSupersonic)
    {
        return mpDBObject->GetIRSig_dB(az_deg, tcAirDetectionDBObject::IRMODELA);
    }
    else
    {
        return mpDBObject->GetIRSig_dB(az_deg, tcAirDetectionDBObject::IRMODELC);
    }

    //const tcAeroAirObject* jet = dynamic_cast<const tcAeroAirObject*>(target);
    //bool afterburnersOn = (jet == 0) ? false : (jet->GetThrottleFraction() > 1.0f);


    //return mpDBObject->GetIRSig_dB(az_deg, tcAirDetectionDBObject::IRMODELA);
}


void tcAirObject::EquipForTargetType(int targetFlag)
{
    if ((targetFlag != 0) && MaintenanceHold())
    {
        return;
    }

    tcPlatformObject::EquipForTargetType(targetFlag);
}

/**
* @param targetType: Auto loadouts: "Empty" "AAW" "ASuW" "ASW" "Strike", otherwise string with loadout name
*/
void tcAirObject::EquipForTargetType(const std::string& targetType)
{
    if ((targetType != "Empty") && MaintenanceHold())
    {
        return;
    }

    tcPlatformObject* parentPlatform = dynamic_cast<tcPlatformObject*>(parent);
	if (parentPlatform == 0)
	{
		fprintf(stderr, "tcAirObject::EquipForTargetType - no host platform (%s)\n", 
			GetName());
		wxASSERT(false);
		return; // not landed or docked, or parent is not tcPlatformObject
	}

    // check for custom loadout
    if (const tcLoadoutData* loadoutData = 
        mpDBObject->GetLoadout(targetType))
    {	
        size_t nMagazines = parentPlatform->GetMagazineCount();
        for (size_t n=0; n<nMagazines; n++)
        {
            tcStores* mag = parentPlatform->GetMagazine(n);
            bool loadoutAvailable = mag->HasStoresForLoadout(*loadoutData);
            if (loadoutAvailable)
            {
                mag->AddAutomationOp(targetType, this);
                return;
            }
        }

    }
    else
    {
        tcPlatformObject::EquipForTargetType(targetType);
    }

}


float tcAirObject::GetCurrentFuelRate() const
{
    return mpDBObject->GetFuelConsumptionConstant(mcKin.mfSpeed_kts) * mcKin.mfSpeed_kts;
}

/**
* @return weight including fuel and weapons
*/
float tcAirObject::GetTotalWeight() const
{
    float weight_kg = mpDBObject->weight_kg + fuel_kg;

    size_t nLaunchers = GetLauncherCount();
    for (size_t n=0; n<nLaunchers; n++)
    {
        const tcLauncher* launcher = GetLauncher(n);
        weight_kg += launcher->GetWeight();
    }

	size_t nStores = GetMagazineCount();
	for (size_t n=0; n<nStores; n++)
	{
		const tcStores* store = GetMagazineConst(n);
		weight_kg += store->GetWeightKg();
	}
    
    return weight_kg;
}

/**
* @return g-limited heading rate in radians/s
*/
float tcAirObject::GlimitedHeadingRate() const
{
    const float C_NUM = 19.0691f; // = (9.81 m/s2) / (kts to mps constant)

    return (C_NUM * mpDBObject->gmax) / mcKin.mfSpeed_kts;
}

bool tcAirObject::IsOverweight() const
{
    return (GetTotalWeight() > mpDBObject->maxTakeoffWeight_kg);
}


bool tcAirObject::IsDestroyed()
{
    return (mfDamageLevel >= 1.0f) && (doneCrashing || (parent != 0));
}

bool tcAirObject::IsReadyForLaunch()
{
    const float minimumFuelFraction = 0.8f;
    
	bool adequatelyFueled = (fuel_kg >= minimumFuelFraction * mpDBObject->GetInternalFuelCapacity()) && (!isRefueling);
	bool launchersReady = AllLaunchersReady();
    bool weightOkay = !IsOverweight();

	return adequatelyFueled && launchersReady && weightOkay;
}



void tcAirObject::RandInitNear(float afLon_deg, float afLat_deg)
{
    if (mpDBObject == NULL) {return;}
    mzClass = mpDBObject->mzClass;
    mzUnit = "AIR_";
    mzUnit.AssignRandomSuffix();

    mfStatusTime = 0;        
    mcKin.mfLon_rad = C_PIOVER180*(afLon_deg + randfc(1.1f));      
    mcKin.mfLat_rad = C_PIOVER180*(afLat_deg + randfc(1.1f));
    mcKin.mfAlt_m = 5000.0f;               
    mcKin.mfHeading_rad = C_TWOPI*randf();           
    mcKin.mfSpeed_kts = 0.80f*mpDBObject->mfMaxSpeed_kts;
    mcKin.mfPitch_rad = 0;
    mcKin.mfRoll_rad = 0;
    mfDamageLevel = 0;  
    SetHeading(mcKin.mfHeading_rad);
    SetSpeed(mcKin.mfSpeed_kts);   
    SetAltitude(mcKin.mfAlt_m);
    readyForLanding = 0;
}


/**
* Sets goal altitude in guidance
*/
void tcAirObject::SetAltitude(float new_altitude_m) 
{
	if (IsEditMode())
	{
		mcKin.mfAlt_m = new_altitude_m;
		if (mcKin.mfAlt_m > mpDBObject->maxAltitude_m)
		{
			mcKin.mfAlt_m = mpDBObject->maxAltitude_m;
		}
	}

    tcPlatformObject::SetAltitude(new_altitude_m);

    climbCommand_rad = 0; // cancel climb command
}

void tcAirObject::SetClimbCommand(float angle_rad)
{
    climbCommand_rad = angle_rad;
}

/**
* Sets landing state for air object (gear up/down)
*/
void tcAirObject::SetLandingState(int state) 
{
    readyForLanding = state;
    commandObj.SetNewCommand(LANDING_CMD);
}

/**
* @param limit_rad Pitch angle limit in radians. Must be positive.
*/
void tcAirObject::SetPitchLimit(float limit_rad)
{
    if (maxPitch_rad < 0) return; // error, negative pitch limit
    if (limit_rad > MAX_PITCH_RAD) 
    {
        maxPitch_rad = MAX_PITCH_RAD;
    }
    else
    {
        maxPitch_rad = limit_rad;
    }
}

void tcAirObject::PrintToFile(tcFile& file) 
{
    tcPlatformObject::PrintToFile(file);
}

void tcAirObject::SaveToFile(tcFile& file) 
{
    tcPlatformObject::SaveToFile(file); 
    file.Write(&maxPitch_rad,sizeof(maxPitch_rad));
    file.Write(&readyForLanding,sizeof(readyForLanding));
}

void tcAirObject::LoadFromFile(tcFile& file) 
{
    tcPlatformObject::LoadFromFile(file);
    file.Read(&maxPitch_rad,sizeof(maxPitch_rad));
    file.Read(&readyForLanding,sizeof(readyForLanding));
}

/**
* @return true if obj is in flightport and in OP_MAINTENANCE or OP_REPAIR state
* load, move, refuel operations are not allowed during maintenance down-time
*/
bool tcAirObject::MaintenanceHold() const
{
    tcFlightOpsObject* flightOps = dynamic_cast<tcFlightOpsObject*>(parent);
	if (flightOps == 0) return false;

    const tcAirState* airState = flightOps->GetFlightPort()->FindAirStateObj(this);
    if (airState != 0)
    {
        return ((airState->op == OP_MAINTENANCE) || (airState->op == OP_REPAIR));
    }
    else
    {
        wxASSERT(false); // parent should always have airState for this obj
        return false;
    }
}

void tcAirObject::Serialize(tcFile& file, bool mbLoad)
{
    if (mbLoad) {
        LoadFromFile(file);
    }
    else {
        SaveToFile(file);
    }
}

void tcAirObject::ApplyRestrictions() 
{
    if (IsClientMode()) return;

    // check for crash
    if ((mcKin.mfAlt_m <= 0) || (mcTerrain.mfHeight_m >= mcKin.mfAlt_m)) 
	{
        if ((mcKin.mfClimbAngle_rad >= 0) && (mcKin.mfAlt_m > (mcTerrain.mfHeight_m - 3.0f)))
        {
            mcKin.mfAlt_m = mcTerrain.mfHeight_m + 3.0f;
            SetAltitude(mcTerrain.mfHeight_m + 500.0f);
            return; // save by climb cheat for this case
        }

        ApplyGeneralDamage(1.0f, 0);

        if (IsOwnAlliance())
        {
            wxString msg;
            msg.Printf("%s %s crashed", mzClass.c_str(), mzUnit.c_str());

            tcMessageInterface::Get()->PopupMessage(msg.ToStdString());
        }
    }
}

/**
* @return number of "spots" available at the moment for in-flight refueling
*/
unsigned int tcAirObject::TankerSpotsFree() const
{
    size_t nFuelPoints = (size_t)mpDBObject->outFuelPods;
    if (fuelTargets.size() >= nFuelPoints)
    {
        return 0;
    }
    else
    {
        return nFuelPoints - fuelTargets.size();
    }
}

/**
* Update climb related parameters. This has problems for large time 
* steps, > about 1 sec
*/
void tcAirObject::UpdateClimb(float dt_s) 
{
    if (climbCommand_rad != 0)
    {
        return UpdateClimbCommand(dt_s);
    }

    float dalt_min, dalt_max, fAltitudeRate_mps;

    // restrict to max altitude
    if (mcGS.mfGoalAltitude_m > mpDBObject->maxAltitude_m)
    {
        mcGS.mfGoalAltitude_m = mpDBObject->maxAltitude_m;
    }

    // avoid crashing
	float& terrain_m = mcTerrain.mfHeight_m;
    if (terrain_m < 0) terrain_m = 0;

	// handle mountainous (high-alt) terrain differently
	float minAGL_m;
	float correction_m;

	if (readyForLanding)
	{
		minAGL_m = 10.0f;
		correction_m = 7.0f;
	}
	else if (terrain_m < 500.0f) 
	{
		minAGL_m = 50.0f;
		correction_m = 75.0f;
	}
	else
	{
		minAGL_m = 200.0f;
		correction_m = 300.0f;
	}


    float maxTerrain_m = std::max(mcTerrain.mfHeight_m, mcTerrain.lookAheadHeight_m);

    if (mcGS.mfGoalAltitude_m < maxTerrain_m + minAGL_m)
    {
        mcGS.mfGoalAltitude_m = mcTerrain.mfHeight_m + correction_m;
    }
	

    float dalt_m = mcGS.mfGoalAltitude_m - mcKin.mfAlt_m;
    // float valt_kts = (daltitude_m/dt_s)*C_MPSTOKTS;
    const float fAOA_rad = C_PIOVER180*4.0f; // angle of attack

    if ((dalt_m > -1.0f)&&(dalt_m < 1.0f)&&
        (mcKin.mfClimbAngle_rad < C_PIOVER180*0.2f)&&(mcKin.mfClimbAngle_rad > -C_PIOVER180*0.2f)) 
	{
		mcKin.mfClimbAngle_rad = 0;
		if (mcKin.mfClimbAngle_rad > maxPitch_rad)
		{
			mcKin.mfClimbAngle_rad = maxPitch_rad;
		}
		mcKin.mfPitch_rad = fAOA_rad; 
        return;
    }


    const float fHighZone = 250.0f;
    const float invHighZone = 1.0f / fHighZone;

    const float fLowZone = -1000.0f;
    const float invLowZone = 1.0f / fLowZone;

    const float fMaxRate = mpDBObject->climbRate_mps;

    if ((dalt_m > fHighZone)||(dalt_m < fLowZone)) 
    {
        fAltitudeRate_mps = fMaxRate;
    }
    else if (dalt_m < 0) 
    {
        fAltitudeRate_mps = fMaxRate*(dalt_m*invLowZone) + 2.0f; // ??? why this +2.0f, helos? 27SEP2008
    }
    else 
    {
        fAltitudeRate_mps = fMaxRate*(dalt_m*invHighZone) + 2.0f;
    }


    if (fuel_kg > 0)
    {
        dalt_max = fAltitudeRate_mps * dt_s; 
        dalt_min = (mcKin.mfAlt_m <= 200.0f) ? -dalt_max : -2.0f*dalt_max;
    }
    else
    {
        dalt_max = -0.25f * fAltitudeRate_mps * dt_s;
        dalt_min = (mcKin.mfAlt_m <= 200.0f) ? -fAltitudeRate_mps * dt_s : -2.0f*fAltitudeRate_mps * dt_s;
    }

    if (dalt_m < dalt_min) {dalt_m = dalt_min;} // restrict to altitude rate
    else if (dalt_m > dalt_max) {dalt_m = dalt_max;}

    float denom = dt_s*mcKin.mfSpeed_kts;
    float fOldAngle_rad = mcKin.mfClimbAngle_rad;
    float alpha = ((mcKin.mfAlt_m > terrain_m + 75.0f) || (dalt_m < 0)) ? 1.0f*dt_s : 10.0f*dt_s ;

    if (denom > 0) 
    {
        float arg = dalt_m*C_MPSTOKTS/denom;
        if (arg > maxPitch_rad) arg = maxPitch_rad;   // restrict climb angle 
        else if (arg < -1.05f) arg = -1.05f; // limit to abt -60 deg
        float fNewAngle_rad = arg; // used to be asinf(arg);
        mcKin.mfClimbAngle_rad = alpha*fNewAngle_rad + (1-alpha)*fOldAngle_rad;
    }
    else 
    {
        mcKin.mfClimbAngle_rad = 0;
    }
	
	if (mcKin.mfClimbAngle_rad > maxPitch_rad)
	{
		mcKin.mfClimbAngle_rad = maxPitch_rad;
	}

    mcKin.mfPitch_rad = mcKin.mfClimbAngle_rad + fAOA_rad; 
}



/**
* Update climb when climb command is active (user or AI input)
*/
void tcAirObject::UpdateClimbCommand(float dt_s) 
{
    const float fAOA_rad = C_PIOVER180*4.0f; // angle of attack

    // restrict to max altitude
    if (mcKin.mfAlt_m >= mpDBObject->maxAltitude_m)
    {
        mcKin.mfAlt_m = mpDBObject->maxAltitude_m;
        climbCommand_rad = 0;
        mcKin.mfClimbAngle_rad = std::min(mcKin.mfClimbAngle_rad, 0.0f);
    }

    float oldAngle_rad = mcKin.mfClimbAngle_rad;
    float alpha = dt_s; // DEC2013 changed this to reduce pitch rate

    mcKin.mfClimbAngle_rad = alpha*climbCommand_rad + (1.0f-alpha)*oldAngle_rad;

	if (mcKin.mfClimbAngle_rad > maxPitch_rad)
	{
		mcKin.mfClimbAngle_rad = maxPitch_rad;
	}

    mcKin.mfPitch_rad = mcKin.mfClimbAngle_rad + fAOA_rad; 
}



void tcAirObject::UpdateDestroyed(double t)
{
    float dt_s = (float)(t - mfStatusTime);

    if (mcKin.mfSpeed_kts <= 450.0f)
    {
        mcKin.mfSpeed_kts += 20.0f * dt_s;
    }

    if (mcKin.mfClimbAngle_rad > -0.9f)
    {
        mcKin.mfClimbAngle_rad -= 0.1f * dt_s;
    }

    mcKin.mfPitch_rad = mcKin.mfClimbAngle_rad;
    mcKin.mfRoll_rad += 0.1f * dt_s;

    if ((mcKin.mfAlt_m <= mcTerrain.mfHeight_m + 20.0f) || 
        (mcKin.mfAlt_m <= 20.0f))
    {
        doneCrashing = true;
    }

    Move(dt_s);
}




void tcAirObject::UpdateEffects()
{
    if (model)
    {
		if (mfDamageLevel > 0.1f)
		{
			model->SetSmokeMode(tc3DModel::DAMAGE);
		}
        else
        {
            model->SetSmokeMode(tc3DModel::OFF);
        }
        model->UpdateEffects();
    }
}

void tcAirObject::UpdateHeading(float dt_s) 
{
    float heading_start,heading_end,dh;
    float roll_start;

    if (dt_s == 0) {return;}
    const float rps_to_roll = 3.0f;
    const float roll_to_rps = 1.0f/rps_to_roll;
    float dtinv = 1.0f/dt_s;

    heading_start = mcKin.mfHeading_rad;
    roll_start = mcKin.mfRoll_rad;

    tcPlatformObject::UpdateHeading(dt_s);

    heading_end = mcKin.mfHeading_rad;
    dh = heading_end - heading_start;

    if (fabsf(heading_end - mcGS.mfGoalHeading_rad) < 0.00003f)
    {
        mcKin.mfHeading_rad = mcGS.mfGoalHeading_rad;
        mcKin.mfRoll_rad = 0;
        return;
    }

    if (IsClientMode()) return;

    //if ((dh <= 0.00004)&&(dh >= -0.00004))  // skip rest of function if negligible heading change
    //{   
    //    mcKin.mfRoll_rad = 0;
    //    return; 
    //}

    if (dh > C_PI) {dh -= C_TWOPI;}
    else if (dh < -C_PI) {dh += C_TWOPI;}

    float dh_gmax = dt_s * GlimitedHeadingRate();
    if (dh > dh_gmax) dh = dh_gmax;
    else if (dh < -dh_gmax) dh = -dh_gmax;


    // if heading rate exceeds max due to roll rate limit then restrict heading rate
    float droll_max = 85.0f*C_PIOVER180*dt_s;

    float roll_max = roll_start + droll_max;
    float roll_min = roll_start - droll_max;
    float dh_min, dh_max;

    if (roll_min < roll_max) 
    {
        dh_min = roll_min*roll_to_rps*dt_s;
        dh_max = roll_max*roll_to_rps*dt_s;
    }
    else 
    {
        dh_min = roll_max*roll_to_rps*dt_s;
        dh_max = roll_min*roll_to_rps*dt_s;
    }

    if (dh > dh_max)
    {
        mcKin.mfHeading_rad = heading_start + dh_max;
        if (mcKin.mfHeading_rad >= C_TWOPI) {mcKin.mfHeading_rad -= C_TWOPI;}
        else if (mcKin.mfHeading_rad < 0) {mcKin.mfHeading_rad += C_TWOPI;}
        dh = dh_max;
    }
    else if (dh < dh_min) 
    {
        mcKin.mfHeading_rad = heading_start + dh_min;
        if (mcKin.mfHeading_rad >= C_TWOPI) {mcKin.mfHeading_rad -= C_TWOPI;}
        else if (mcKin.mfHeading_rad < 0) {mcKin.mfHeading_rad += C_TWOPI;}
        dh = dh_min;
    }

    float dh_rps = dh*dtinv;
    mcKin.mfRoll_rad = dh_rps*rps_to_roll;

	mcKin.mfYaw_rad = mcKin.mfHeading_rad;
}

/**
* Should be called by tankers only
*/
void tcAirObject::UpdateInFlightRefuel(float dt_s)
{
    if ((fuelTargets.size() == 0) || clientMode) return;

    // stop refueling below some minimum tanker fuel level
    if (fuel_kg < 0.1f * GetFuelCapacity())
    {
        fuelTargets.clear();
        return;
    }

    const float maxRefuelRange_km = 0.25f;

    std::vector<long> validId;

    for (size_t n=0; n<fuelTargets.size(); n++)
    {
        long id = fuelTargets[n];
        tcAirObject* target = dynamic_cast<tcAirObject*>(simState->GetObject(id));
        if ((target != 0) && (target->fuel_kg < target->GetFuelCapacity() - 30) &&
            (mcKin.RangeToKmAlt(target->mcKin) <= maxRefuelRange_km))
        {
            validId.push_back(id);

            float fuelRate_kgps = std::min(target->mpDBObject->fuelIn_kgps, mpDBObject->fuelOut_kgps);
            float dFuel_kg = fuelRate_kgps*dt_s;
            fuel_kg -= dFuel_kg;
            target->fuel_kg += dFuel_kg;
        }
    }

    fuelTargets = validId;
}


/**
* Automatically updates loadout tag with best guess at loadout
*/
void tcAirObject::UpdateLoadoutTag()
{    
    if (IsEquippedForTargetType(SUBSURFACE_TARGET))
    {
        SetLoadoutTag("ASW");
    }
    else if (IsEquippedForTargetType(SURFACE_TARGET))
    {
        SetLoadoutTag("ASuW");
    }
    else if (IsEquippedForTargetType(LAND_TARGET))
    {
        SetLoadoutTag("STK");
    }
    else if (IsEquippedForTargetType(AIR_TARGET))
    {
        SetLoadoutTag("AAW");
    }
    else
    {
        SetLoadoutTag("---");
    }

    // if equipped with nuclear, override tag and just call it nuclear
    if (IsEquippedWithNuclear(0xFFFF))
    {
        SetLoadoutTag("NUC");
    }

}

/**
* Limits speed to 100 kts min
*/
void tcAirObject::UpdateSpeed(float dt_s)
{
    tcPlatformObject::UpdateSpeed(dt_s);

	if (mcKin.mfSpeed_kts < 100) mcKin.mfSpeed_kts = 100;
}

void tcAirObject::Update(double afStatusTime) 
{
    const float min_update_s = 0.0f;
    float dt_s = (float)(afStatusTime - mfStatusTime);

    UpdateEffects();

    // shouldn't be called for child objects
    if (parent != NULL) {return;} // captive, let parent update if applicable
    if ((dt_s <= min_update_s) && !tcGameObject::IsEditMode())
    {
        return;
    } // added for pause case

    wxASSERT(mpDBObject);

    if (mfDamageLevel >= 1.0f)
    {
        UpdateDestroyed(afStatusTime);
        mfStatusTime = afStatusTime;
        return;
    }

    //UpdateFormationGuidance(); // formation heading/speed calculation

    // if (!IsClientMode() || IsControlled()) // not sure why IsControlled()? supposed to be smoother for controlled obj?
    if (!IsClientMode())
	{
        formation.Update((tcAirObject*)this);
        
		UpdateHeading(dt_s);

		UpdateSpeed(dt_s);

		UpdateClimb(dt_s);

        UpdateInFlightRefuel(dt_s);

		ApplyRestrictions(); // crash check
	}
    else if (IsControlled()) // 18SEP08
    {
        UpdateHeading(dt_s);
    }

    Move(dt_s);

    UpdateLauncherState(dt_s);
    
    UpdateSensors(afStatusTime);
    
    UpdateAI(afStatusTime);
    
    Update3D();
    
    mfStatusTime = afStatusTime; 
}



tcAirObject::tcAirObject() 
: climbCommand_rad(0)
{
    mnModelType = MTYPE_FIXEDWING;
    SetAltitude(2000.0f);
    SetHeading(75.0f);
    SetSpeed(300.0f);
    readyForLanding = 0;
    maxPitch_rad = MAX_PITCH_RAD;

    wxASSERT(false);
}

/**
* Constructor that initializes using info from database entry.
*/
tcAirObject::tcAirObject(tcAirDBObject* obj)
: tcPlatformObject(obj),
  doneCrashing(false),
  climbCommand_rad(0),
  maxPitch_rad(MAX_PITCH_RAD)
{
    mpDBObject = obj;
    mnModelType = MTYPE_FIXEDWING;
    readyForLanding = 0;
    
    if (addTasksOnCreate) brain->AddTaskDirectly("AirEvade", 3.0, ai::Task::HIDDEN | ai::Task::PERMANENT);
    
}

tcAirObject::~tcAirObject()
{
}
