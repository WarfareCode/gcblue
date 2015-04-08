/** 
**  @file tcPlatformObject.cpp
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

#include "tcPlatformObject.h"
#include "tcPlatformDBObject.h"
#include "tcLauncherDBObject.h"
#include "tcMissileObject.h"
#include "tcStoresDBObject.h"
#include "tcWeaponDBObject.h"
#include "tcString.h"
#include "tcRadar.h"
#include "tcESMSensor.h"
#include "tcLauncher.h"
#include "tc3DModel.h"
#include "tcSimState.h"
#include "tcStores.h"
#include "common/tcStream.h"
#include "common/tcObjStream.h"
#include "tcGameStream.h"
#include "ai/Brain.h"
#include "tcScenarioLogger.h"
#include "tcDamageModel.h"
#include "tcScenarioRandomizer.h"
#include "tcDatabase.h"
#include "tcEventManager.h"
#include "tcShipDBObject.h"
#include "tcMessageInterface.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace ai;

/**
* Static method, call once at startup
*/
void tcPlatformObject::InitPlatformObject()
{
    Brain::InitTaskNameLookup();
}


void tcPlatformObject::DesignateDatum(tcPoint p) 
{
    float fRange_km;

    msTargetDatum.mfLon_rad=p.x;
    msTargetDatum.mfLat_rad=p.y;

    fRange_km = mcKin.RangeToKm(&msTargetDatum);
    tcString s;
    s.Format("datum is %3.1f km from platform", fRange_km);
    WTLC(s.GetBuffer());
}

void tcPlatformObject::DesignateLauncherDatum(GeoPoint p, unsigned int anLauncher) 
{
	mcLauncherState.SetLauncherDatum(anLauncher, p.mfLon_rad, p.mfLat_rad, p.mfAlt_m);
}

/**
* @return false if target cannot be designated, out of seeker coverage or no fire
* @return false control support available.
*/
bool tcPlatformObject::DesignateLauncherTarget(long anID, unsigned anLauncher) 
{
    if (tcLauncher* launcher = mcLauncherState.GetLauncher(anLauncher))
    {
        launcher->ActivateFireControl();
    }

    return mcLauncherState.SetLauncherTarget(anLauncher, anID);
}

/**
* set AI target, also set all launcher targets. This
* may have some undesirable side effects !?
*/
void tcPlatformObject::DesignateTarget(long anID)
{
    if (anID == -1)
    {
        brain->SetTarget(-1);
        unsigned nLaunchers = mcLauncherState.GetLauncherCount();
        for (size_t n=0; n<nLaunchers; n++)
        {
            tcLauncher* launcher = mcLauncherState.GetLauncher(n);
            if (launcher->mnCurrent == launcher->mnUncommitted) // don't wipe out previous target info if launch in progress
            {
                mcLauncherState.SetLauncherTarget(n, -1);
                mcLauncherState.SetLauncherDatum(n, 0, 0, 0);
            }
        }
        return;
    }

    tcSensorMapTrack track;
    bool trackFound = simState->GetTrack(anID, GetAlliance(), track);
    if (!trackFound)
    {
        return;
    }

    brain->SetTarget(anID);
    unsigned nLaunchers = mcLauncherState.GetLauncherCount();
    for (size_t n=0; n<nLaunchers; n++)
    {
        tcLauncher* launcher = mcLauncherState.GetLauncher(n);
        if ((launcher->IsEffective(track)) && (!track.IsBearingOnly()))
        {
            mcLauncherState.SetLauncherTarget(n, anID);
            mcLauncherState.SetLauncherDatum(n, track.mfLon_rad, track.mfLat_rad, 0);
        }
        else
        {
            mcLauncherState.SetLauncherTarget(n, -1);
            mcLauncherState.SetLauncherDatum(n, 0, 0, 0);
        }
    }
}

/**
* Call in destructor to clean up formation references
*/
void tcPlatformObject::DestroyFormation()
{
    if (!formation.isActive) return;

    if (formation.IsLeader())
    {
    }
    else
    {
        tcPlatformObject* leader = 
            dynamic_cast<tcPlatformObject*>(simState->GetObject(formation.leaderId));
        if ((leader != 0) && (leader->GetAlliance() == GetAlliance()))
        {
            leader->formation.RemoveFollower(mnID);
        }

    }
}

/**
*
*/
void tcPlatformObject::UpdateAI(float t)
{
    wxASSERT(brain);

    brain->Update(t);
}

// update guidance to maintain/achieve formation position
void tcPlatformObject::UpdateFormationGuidance() 
{
    formation.Update(this);
}

/**
* turn by maximum amount toward goal heading
*/
void tcPlatformObject::UpdateHeading(float dt_s) 
{
    float dh_rad = mcGS.mfGoalHeading_rad - mcKin.mfHeading_rad;
    radtoplusminuspi(dh_rad); // map dh_deg to [-180,180]
    float absdh_rad = fabsf(dh_rad);

    if (absdh_rad < 0.0001f)
    {
        mcKin.mfHeading_rad = mcGS.mfGoalHeading_rad;
        mcKin.mfYaw_rad = mcKin.mfHeading_rad;
        reducedTurnRate_degps = 360.0f; // clear slow turn
        return;
    }


    float effectiveTurnRate_degps = std::min(reducedTurnRate_degps, mpDBObject->mfTurnRate_degps);

    float dh_max = C_PIOVER180*effectiveTurnRate_degps*dt_s;
    if (mfDamageLevel > 0.2f)
    {
        dh_max *= 0.5f;
    }
    // linearly reduce turn rate near goal

    const float dh_thresh = 10.0f*C_PIOVER180;
    const float k_dh = 1.0f/dh_thresh;
    if (absdh_rad < dh_thresh) 
    {
        dh_max *= absdh_rad*k_dh;
    }

    float dh_min = -dh_max;
    if (dh_rad < dh_min) {dh_rad = dh_min;} // restrict to turn rate
    else if (dh_rad > dh_max) {dh_rad = dh_max;}
    
    
    // simple way to smooth heading rate changes when not near goal
    if (absdh_rad > dh_thresh) 
    {
        float ddh_rad = dh_rad - lastHeadingDelta;
        const float ddh_max = 0.0002f;
        if (ddh_rad < -ddh_max) dh_rad = lastHeadingDelta - ddh_max;
        else if (ddh_rad > ddh_max) dh_rad = lastHeadingDelta + ddh_max;
    }

    lastHeadingDelta = dh_rad;

    mcKin.mfHeading_rad += dh_rad;
    if (mcKin.mfHeading_rad >= C_TWOPI) {mcKin.mfHeading_rad -= C_TWOPI;}
    if (mcKin.mfHeading_rad < 0) {mcKin.mfHeading_rad += C_TWOPI;}

	mcKin.mfYaw_rad = mcKin.mfHeading_rad;
}

float tcPlatformObject::ShipAccel() 
{
	if (abs(std::max(mcGS.mfGoalSpeed_kts, mcKin.mfSpeed_kts) - std::min(mcGS.mfGoalSpeed_kts, mcKin.mfSpeed_kts)) < 0.005)
	{
		return 0;
	}

	float accel = std::max(0.001, 1 - (pow(abs(mcKin.mfSpeed_kts), 0.9) / pow(mpDBObject->mfMaxSpeed_kts, 0.9))) * mpDBObject->mfAccel_ktsps;
	if ((abs(mcGS.mfGoalSpeed_kts) > abs(mcKin.mfSpeed_kts)) && ((mcGS.mfGoalSpeed_kts < 0 && mcKin.mfSpeed_kts < 0)  || (mcGS.mfGoalSpeed_kts > 0 && mcKin.mfSpeed_kts > 0)))
	 {
		if (mcGS.mfGoalSpeed_kts > mcKin.mfSpeed_kts) //forwards acceleration
		{
			return accel;
		}
		else
		{
			return accel * -1;
		}
	}
	else// if (abs(mcGS.mfGoalSpeed_kts) < abs(mcKin.mfSpeed_kts)) //slowing to stop
	{
		tcDatabaseObject* databaseObject = tcDatabase::Get()->GetObject(mpDBObject->mzClass.c_str());
		tcShipDBObject* shipDBObj = dynamic_cast<tcShipDBObject*>(databaseObject);
		//float block_coefficient = shipDBObj->weight_kg / (shipDBObj->draft_m * shipDBObj->length_m * shipDBObj->beam_m * 1030);
		float water_force = shipDBObj->beam_m * shipDBObj->draft_m * pow(mcKin.mfSpeed_kts * 0.514444f, 2) * 1030;
		float water_accel = (water_force / mpDBObject->weight_kg) / 0.514444;
		float crash_stop = std::min(2.0f,std::max(1.0f, 0.3f / mcKin.mfSpeed_kts));
		accel *= crash_stop;

		if (mcGS.mfGoalSpeed_kts < mcKin.mfSpeed_kts) //slowing from forwards velocity
		{
			return accel * -1 - water_accel;
		}
		else
		{
			return accel + water_accel;
		}
	}
}

/**
* Adjust speed to goal speed, limited by max acceleration
* Also updates fuel state (setting fuel capacity to 0 in db gives infinite fuel)
*/
void tcPlatformObject::UpdateSpeed(float dt_s) 
{
    float ds_kts = mcGS.mfGoalSpeed_kts - mcKin.mfSpeed_kts;
    float ds_max = mpDBObject->mfAccel_ktsps*dt_s;
    float ds_min = -ds_max;
    unsigned int classification = mpDBObject->mnType;
    bool isSurface = ((classification & PTYPE_SURFACE) != 0);
	if (isSurface)
	{
		ds_kts = ShipAccel() * dt_s;
	}
	else
	{
		if (ds_kts < ds_min) {ds_kts = ds_min;} // restrict to acceleration
		else if (ds_kts > ds_max) {ds_kts = ds_max;}
	}

    mcKin.mfSpeed_kts += ds_kts;


	// if a fuel capacity is indicated then update fuel consumption
	if (!mpDBObject->HasInfiniteFuel())
	{
		fuel_rate = mpDBObject->GetFuelConsumptionConstant(mcKin.mfSpeed_kts) * mcKin.mfSpeed_kts;
		fuel_kg -= dt_s * fuel_rate;
		if (fuel_kg < 0) fuel_kg = 0;

		if (fuel_kg == 0)
		{
			if (mcKin.mfSpeed_kts > 0) mcKin.mfSpeed_kts -= 2*ds_max;
			if (mcKin.mfAlt_m > 0) mcKin.mfAlt_m -= dt_s * 10;
		}
	}
}

/**
* apply movement restrictions (based on terrain height and altitude normally)
*/
void tcPlatformObject::ApplyRestrictions() 
{
}

void tcPlatformObject::Move(float dt_s) 
{
    float fHeading_rad = mcKin.mfHeading_rad;
    float fGroundSpeed_kts = cosf(mcKin.mfClimbAngle_rad)*mcKin.mfSpeed_kts;
    double fDistance_rad = fGroundSpeed_kts*dt_s*(float)C_KTSTORADPS;

    mcKin.mfLon_rad += fDistance_rad*(double)(sinf(fHeading_rad)/cosf((float)mcKin.mfLat_rad));
    mcKin.mfLat_rad += (double)cosf(fHeading_rad)*fDistance_rad; 
    mcKin.mfAlt_m += sinf(mcKin.mfClimbAngle_rad)*mcKin.mfSpeed_kts*C_KTSTOMPS*dt_s;

    float wrapLow = float(mcKin.mfLon_rad < -C_PI);
    float wrapHigh = float(mcKin.mfLon_rad >= C_PI);

    mcKin.mfLon_rad += (wrapLow - wrapHigh) * C_TWOPI;

    // check for pole crossing
    if (fabsf(mcKin.mfLat_rad) >= C_PIOVER2)
    {
        if (mcKin.mfLat_rad >= C_PIOVER2)
        {
            mcKin.mfLat_rad = C_PI - mcKin.mfLat_rad;
        }
        else
        {
            mcKin.mfLat_rad = -C_PI - mcKin.mfLat_rad;
        }
        mcKin.mfHeading_rad = C_PI - mcKin.mfHeading_rad;
        mcGS.mfGoalHeading_rad = C_PI - mcGS.mfGoalHeading_rad;
    }

    wxASSERT((mcKin.mfLon_rad >= -C_PI) && (mcKin.mfLon_rad < C_PI));
    wxASSERT((mcKin.mfLat_rad >= -C_PIOVER2) && (mcKin.mfLat_rad <= C_PIOVER2));
	wxASSERT(!_isnan(mcKin.mfRoll_rad));
	wxASSERT(!_isnan(mcKin.mfPitch_rad));
}



/**
* update launcher state (reload time) 
*/
void tcPlatformObject::UpdateLauncherState(float dt_s) 
{
    mcLauncherState.Update(dt_s);
}

/** 
* update platform magazines 
*/
void tcPlatformObject::UpdateMagazines(double t)
{
    if (clientMode) return; // no magazine update for client
    size_t nMagazines = magazines.size();
    for (size_t n=0; n<nMagazines; n++)
    {
        tcStores* mag = magazines[n];
        wxASSERT(mag);
        mag->Update(t);
    }
}

/** 
* update platform sensors 
*/
void tcPlatformObject::UpdateSensors(double t)
{
    if (clientMode) return; // no sensor update for client
    
    tcSensorPlatform::Update(t);
}

void tcPlatformObject::Update(double afStatusTime) 
{
    float dt_s = (float)(afStatusTime - mfStatusTime);

    UpdateEffects();

    if (parent != NULL) {return;} // captive, let parent update if applicable
    if (mpDBObject == NULL) {return;}
    

	/* In multiplayer mode, skip command based updates for client objects not controlled
	** by client. This will cause object to jump more but avoids having to broadcast command
	** changes to all alliance clients. The controller of the object will see smoother
	** behavior.
	*/
	if (!IsClientMode() || IsControlled())
	{
        UpdateFormationGuidance(); // formation heading/speed calculation

		UpdateHeading(dt_s);

		UpdateSpeed(dt_s);

		UpdateClimb(dt_s);

		ApplyRestrictions();
	}

    Move(dt_s);

    UpdateLauncherState(dt_s);

    UpdateSensors(afStatusTime);

    UpdateMagazines(afStatusTime);

    UpdateAI(afStatusTime);

    Update3D();

    mfStatusTime = afStatusTime;
}

/**
* @return pointer to platform's "brain" (AI)
*/
Brain* tcPlatformObject::GetBrain()
{
    return brain;
}

long tcPlatformObject::GetFormationLeader() const
{
    return formation.leaderId;
}

/**
* @return fuel capacity in kg including external fuel tanks
*/
float tcPlatformObject::GetFuelCapacity() const
{
	return (mpDBObject->GetInternalFuelCapacity() + externalFuelCapacity_kg);
}

/**
* @return pointer to launcher with index of <idx> or NULL (0) for error
*/
tcLauncher* tcPlatformObject::GetLauncher(unsigned idx)
{
    return mcLauncherState.GetLauncher(idx);
}

const tcLauncher* tcPlatformObject::GetLauncher(unsigned idx) const
{
    return mcLauncherState.GetLauncher(idx);
}

unsigned int tcPlatformObject::GetLauncherCount() const
{
    return mcLauncherState.GetLauncherCount();
}

/**
* @return description of launchers for display
*/
wxString tcPlatformObject::GetLauncherDescription()
{
	static std::string errorString = "Error";
	wxString description;

	unsigned nLaunchers = mcLauncherState.GetLauncherCount();
	for (unsigned n=0; n < nLaunchers; n++)
	{
		tcLauncher* launcher = GetLauncher(n);

		const char* childClassName = (launcher->mpChildDBObj != 0) ? launcher->mpChildDBObj->mzClass.c_str() :
		                 errorString.c_str();

		description += wxString::Format("%s, %d x %s\n",
			launcher->mpLauncherDBObj->mzClass.c_str(),
			launcher->mnCurrent,
			childClassName);
	}

	if (nLaunchers == 0)
	{
		description = "No weapons\n";
	}

	return description;
}


/**
*
*/
int tcPlatformObject::GetLauncherQuantity(unsigned anLauncher) 
{
    return mcLauncherState.GetLauncherQuantity(anLauncher);
}

/**
* Intended to allow scenario edit to save loadout state in compact format
*/
const std::string& tcPlatformObject::GetLoadoutCommand() const
{
    static std::string result;

    wxString s;

    unsigned int nLaunchers = mcLauncherState.GetLauncherCount();
    for (unsigned int n=0; n<nLaunchers; n++)
    {
        std::string item = mcLauncherState.GetLauncherChildClass(n);
        int qty = mcLauncherState.GetLauncherQuantity(n);
        s += wxString::Format("%d %s;", qty, item.c_str());
    }

    result = s.c_str();
    
    return result;
}

/**
* This version instantly sets the platform to use the specified
* loadout items and quantities. Should only be used for edit mode,
* loading scenarios, and testing.
*/
void tcPlatformObject::SetLoadoutCommand(const std::string& s)
{
    std::vector<std::string> item;
    std::vector<unsigned int> quantity;
    ParseLoadoutCommand(s, item, quantity);

    unsigned int nLaunchers = mcLauncherState.GetLauncherCount();
    for (unsigned int launcherIdx=0; 
        (launcherIdx<item.size()) && (launcherIdx < nLaunchers); launcherIdx++)
    {
        tcLauncher* launcher = mcLauncherState.GetLauncher(launcherIdx);
        wxASSERT(launcher != 0);

        if (quantity[launcherIdx] > 0)
        {
            launcher->SetChildClass(item[launcherIdx].c_str());
            if (launcher->mpChildDBObj != 0)
            {
                launcher->SetChildQuantity(quantity[launcherIdx]);
            }
            else
            {
				wxASSERT(false);
				fprintf(stderr, "tcPlatformObject::SetLoadoutCommand - bad item (%s)\n", item[launcherIdx].c_str());
                launcher->SetChildQuantity(0);
            }
        }
        else
        {
            launcher->SetChildClass("");
            launcher->SetChildQuantity(0);
        }
    }
}

/**
* This version schedules platform to load specified items from host
* parent. Can be used during normal simulation.
*/
void tcPlatformObject::ScheduleLoadoutCommand(const std::string& s)
{
    std::vector<std::string> item;
    std::vector<unsigned int> quantity;
    ParseLoadoutCommand(s, item, quantity);

    tcPlatformObject* parentPlatform = dynamic_cast<tcPlatformObject*>(parent);
    if (parentPlatform == 0)
    {
        fprintf(stderr, "tcPlatformObject::ScheduleLoadoutCommand - no host platform (%s)\n", 
            GetName());
        wxASSERT(false);
        return; // not landed or docked, or parent is not tcPlatformObject
    }


    unsigned int nLaunchers = mcLauncherState.GetLauncherCount();
    for (unsigned int launcherIdx=0; 
        (launcherIdx<item.size()) && (launcherIdx < nLaunchers); launcherIdx++)
    {
        tcLauncher* launcher = mcLauncherState.GetLauncher(launcherIdx);
        wxASSERT(launcher != 0);

        if (quantity[launcherIdx] > 0)
        {
            size_t nMagazines = parentPlatform->GetMagazineCount();
            for (size_t n=0; n<nMagazines; n++)
            {
                tcStores* mag = parentPlatform->GetMagazine(n);
                bool result = mag->LoadLauncher(launcherIdx, item[launcherIdx], this, quantity[launcherIdx]);
            }
        }
    }
}


void tcPlatformObject::ParseLoadoutCommand(const std::string& cmd, 
                                           std::vector<std::string>& item, std::vector<unsigned int>& quantity)
{
    item.clear();
    quantity.clear();

    wxString s2(cmd.c_str());

    bool parsing = true;
    unsigned int launcherIdx = 0;

    while (parsing && (launcherIdx < mcLauncherState.GetLauncherCount()))
    {
        wxString loadout = s2.BeforeFirst(';');
        s2 = s2.AfterFirst(';');

        wxString qtyText = loadout.BeforeFirst(' ');

        wxString itemText = loadout.AfterFirst(' ');
        itemText.Trim(true); // remove spaces at beginning and end
        itemText.Trim(false);
        
        unsigned long qty = 0;
        if (qtyText.ToULong(&qty, 10))
        {
            item.push_back(std::string(itemText.c_str()));
            quantity.push_back(unsigned int(qty));
        }

        parsing = (s2.size() > 0);
        launcherIdx++;
    }
}


const std::string& tcPlatformObject::GetLoadoutTag() const
{
	return loadoutTag;
}


void tcPlatformObject::SetLoadoutTag(const std::string& s)
{
	loadoutTag = s;
}

void tcPlatformObject::SetMaxTurnRate(float rate_degps)
{
    reducedTurnRate_degps = rate_degps;
}

/**
* @return true if platform is intercepting (has targeted) track with id
*/
bool tcPlatformObject::IsInterceptingTrack(long id)
{
    wxASSERT(id >= 0);

    return brain->GetTarget() == id;
}

/**
* Called when new general damage occurs. 
* @param damage fractional amount of new damage
*/
void tcPlatformObject::ApplyGeneralDamage(float damage, tcGameObject* damager)
{
    float priorDamage = mfDamageLevel;
    mfDamageLevel += damage;
    mfDamageLevel = std::min(mfDamageLevel, 1.0f);

    UpdateScoreForDamage(damager, priorDamage);

    float scaledDamage = (mfDamageLevel <= 0.5f) ? (0.4f * damage) : damage;

    unsigned int nLaunchers = GetLauncherCount();
    for (unsigned int m=0; m<nLaunchers; m++)
    {
        tcLauncher* launcher = GetLauncher(m);
        wxASSERT(launcher);
        
        if ( !launcher->IsDamaged() && (randf() <= scaledDamage))
        {
            launcher->SetDamaged(true);
            launcher->UpdateScoreForDamage(damager);
        }
    }

    // higher probability of sensor damage
    scaledDamage = (mfDamageLevel <= 0.5f) ? (0.6f * damage) : damage;

    unsigned int nSensors = GetSensorCount();
    for (unsigned int n=0; n<nSensors; n++)
    {
        tcSensorState* sensor = GetSensorMutable(n);
        wxASSERT(sensor);

        if ( !sensor->IsDamaged() && (randf() <= scaledDamage))
        {
            sensor->SetDamaged(true);
        }
    }

    if (damage > 0)
    {
        tcEventManager::Get()->DamageReceived(GetAlliance());
    }
}



/**
* @return damage fraction for new damage, 0 means no new damage
*/
float tcPlatformObject::ApplyAdvancedDamage(const Damage& damage, tcGameObject* damager)
{
    float impactDamage = 0;
    float internalDamage = 0;
    float blastDamage = 0;
    float waterBlastDamage = 0;
    float thermalDamage = 0;
    float fragDamage = 0;

    if (mfDamageLevel >= 1) return 0;

    float priorDamage = mfDamageLevel;

    const database::tcDamageEffect* damageEffect = 
        database->GetDamageEffectData(mpDBObject->damageEffect);
    
    if (damageEffect == 0)
    {
        fprintf(stderr, "tcPlatformObject::ApplyAdvancedDamage -- NULL damageEffect for %s\n",
            mzClass.c_str());
        wxASSERT(false);
        return 0;
    }

    impactDamage = damageEffect->GetFragmentDamageFactor(damage.kinetic_J);
    if (damage.isPenetration && ((impactDamage > 0.002f) || damager->mcKin.mfAlt_m < -1.0f)) // if it's underwater always apply penetration damage
    {
        internalDamage = damageEffect->GetInternalDamageFactor(damage.explosive_kg);
    }
    blastDamage = damageEffect->GetBlastDamageFactor(damage.blast_psi);
    waterBlastDamage = damageEffect->GetWaterBlastDamageFactor(damage.waterBlast_psi);
    thermalDamage = damageEffect->GetRadiationDamageFactor(damage.thermal_J_cm2);

    if (damage.fragHits > 0)
    {
        float hitsFactor = 1.0f + log10f(float(damage.fragHits)); 
        fragDamage = hitsFactor * damageEffect->GetFragmentDamageFactor(damage.fragEnergy_J);
    }


    float cumulativeDamage = impactDamage + internalDamage + blastDamage + waterBlastDamage + thermalDamage + fragDamage;

    wxString damageDescription;
    float newDamage = 0;

    if (cumulativeDamage > 0) 
    {
        if (impactDamage > 0) damageDescription.append("K");
        if (internalDamage > 0) damageDescription.append("X");
        if (blastDamage > 0) damageDescription.append("B");
        if (waterBlastDamage > 0) damageDescription.append("U");
        if (thermalDamage > 0) damageDescription.append("T");
        if (fragDamage > 0) damageDescription.append("F");

        float rand_val = GaussianRandom::Get()->randn_fast();
        rand_val = 0.642f * fabsf(rand_val) + 0.05f; // median about 0.5, min 0.05 (database factors are doubled on load see tcDamageEffect::ParseEffectString)
        newDamage = rand_val * cumulativeDamage;

        mfDamageLevel += newDamage;

        mfDamageLevel = std::min(mfDamageLevel, 1.0f);

        UpdateScoreForDamage(damager, priorDamage);

        ApplyLauncherDamage(newDamage, damager);
    }
    

    bool sensorDamage = tcSensorPlatform::ApplyAdvancedDamage(damage, damager, newDamage);
    if (sensorDamage)
    {
        damageDescription.append("S");
        newDamage += 0.0001f; // so that new damage is reported
    }

    SetLastDamageDescription(damageDescription.ToStdString());

    if (newDamage > 0)
    {
        tcEventManager::Get()->DamageReceived(GetAlliance());
    }

    return newDamage;
}

/**
* Checks each launcher for failure when new damage occurs
*/
void tcPlatformObject::ApplyLauncherDamage(float damage, tcGameObject* damager)
{
    float scaledDamage = (mfDamageLevel <= 0.5f) ? (0.4f * damage) : damage;

    unsigned int nLaunchers = GetLauncherCount();
    for (unsigned int m=0; m<nLaunchers; m++)
    {
        tcLauncher* launcher = GetLauncher(m);
        wxASSERT(launcher);
        
        if ( !launcher->IsDamaged() && (randf() <= scaledDamage))
        {
            launcher->SetDamaged(true);
            launcher->UpdateScoreForDamage(damager);
        }
    }
}




/**
* Called when repairs remove damage. Launchers, sensors, etc.
* are tested for fix.
* @param fractional amount of new repairs
*/
void tcPlatformObject::ApplyRepairs(float repair)
{
    mfDamageLevel -= repair;
    if (mfDamageLevel <= 0) mfDamageLevel = 0;

    float scaledRepairs = (mfDamageLevel <= 0.5f) ? repair : (0.5f * repair);

    unsigned int nLaunchers = GetLauncherCount();
    for (unsigned int m=0; m<nLaunchers; m++)
    {
        tcLauncher* launcher = GetLauncher(m);
        wxASSERT(launcher);
        
        if (launcher->IsDamaged() && (randf() <= scaledRepairs))
        {
            launcher->SetDamaged(false);
        }
    }

    unsigned int nSensors = GetSensorCount();
    for (unsigned int n=0; n<nSensors; n++)
    {
        tcSensorState* sensor = GetSensorMutable(n);
        wxASSERT(sensor);
        
        if (sensor->IsDamaged() && (randf() <= scaledRepairs))
        {
            sensor->SetDamaged(false);
        }
    }

}

/**
* Automatically configure platform magazine contents and air complement
* If setupName is empty, then use first setup with valid date range
* Clear magazines and aircraft before autoconfiguring if setupName is valid
*/
void tcPlatformObject::AutoConfigurePlatform(const std::string& setupName)
{
    std::vector<database::AirComplement> airComplement;
    std::vector<database::MagazineLoadout> magazineLoadout;
    std::vector<database::LauncherLoadout> launcherLoadout;

    GetAutoConfigurationData(setupName, airComplement, magazineLoadout, launcherLoadout);

    AutoConfigureMagazines(magazineLoadout);
    AutoConfigureLaunchers(launcherLoadout);
}

void tcPlatformObject::AutoConfigureLaunchers(const std::vector<database::LauncherLoadout>& launcherLoadout)
{
    if (launcherLoadout.size() == 0)
    {
        return;
    }

    // clear all launchers
    size_t nLaunchers = (size_t)GetLauncherCount();
    for (size_t n=0; n<nLaunchers; n++)
    {
        tcLauncher* launcher = GetLauncher(n);
        launcher->SetChildQuantity(0);
    }

    for (size_t k=0; k<launcherLoadout.size(); k++)
    {
        if (tcLauncher* launcher = GetLauncherById(launcherLoadout[k].launcherId))
        {
            launcher->SetChildClass(launcherLoadout[k].item);
            launcher->SetChildQuantity(launcherLoadout[k].quantity);
        }
        else
        {
            wxASSERT(false); // invalid launcher id
        }
    }
}


void tcPlatformObject::AutoConfigureMagazines(const std::vector<database::MagazineLoadout>& magazineLoadout)
{
    if (magazineLoadout.size() == 0)
    {
        return;
    }

    // clear all magazines
    size_t nMagazines = GetMagazineCount();
    for (size_t n=0; n<nMagazines; n++)
    {
        tcStores* stores = GetMagazine(n);
        stores->RemoveAllItems();
    }

    for (size_t k=0; k<magazineLoadout.size(); k++)
    {
        if (tcStores* stores = GetMagazineById(magazineLoadout[k].magazineId))
        {
            stores->AddItems(magazineLoadout[k].item, (unsigned long)magazineLoadout[k].quantity);
        }
        else
        {
            wxASSERT(false); // invalid magazine id
        }
    }
}

void tcPlatformObject::GetAutoConfigurationData(const std::string& setupName, 
        std::vector<database::AirComplement>& airComplement, std::vector<database::MagazineLoadout>& magazineLoadout,
        std::vector<database::LauncherLoadout>& launcherLoadout)
{
    std::string databaseClass = mpDBObject->mzClass.c_str();

    std::string selectedSetup = setupName;
    if (selectedSetup.size() == 0)
    {
        tcDateTime current = simState->GetDateTime();
        float currentYear = float(current.GetYear()) + (1.0f/12.0f)*(float(current.GetMonth()) - 0.5f);

        std::vector<std::string> platformSetups;
        bool valid = database->FindPlatformSetups(databaseClass, currentYear, platformSetups);
        if (valid && (platformSetups.size() > 0))
        {
            selectedSetup = platformSetups[0];
        }
        if (!valid) return;
    }
    
    database->GetPlatformSetupData(databaseClass, selectedSetup, airComplement, magazineLoadout, launcherLoadout);
}


void tcPlatformObject::Clear()  
{  
    tcGameObject::Clear();
    
    formation.Clear();

//    mcAI.ClearOrders();
    fuel_kg = 0;
    lastHeadingDelta = 0;

    reducedTurnRate_degps = 360.0f;
}

/**
*
*/
unsigned int tcPlatformObject::GetMagazineCount() const
{
    return (unsigned int)magazines.size();
}

/**
*
*/
tcStores* tcPlatformObject::GetMagazine(unsigned int idx)
{
    if (idx >= magazines.size()) return 0;
    else return magazines[idx];
}

const tcStores* tcPlatformObject::GetMagazineConst(unsigned int idx) const
{
    if (idx >= magazines.size()) return 0;
    else return magazines[idx];
}

tcStores* tcPlatformObject::GetMagazineById(unsigned int id)
{
    if (magazines.size() != mpDBObject->magazineId.size())
    {
        wxASSERT(false); // had an invalid magazine reference in db?
        return 0;
    }

    for (size_t n=0; n<mpDBObject->magazineId.size(); n++)
    {
        if (mpDBObject->magazineId[n] == id)
        {
            return magazines[n];
        }
    }

    return 0;
}

tcLauncher* tcPlatformObject::GetLauncherById(unsigned int id)
{
    if (mcLauncherState.mnCount != mpDBObject->launcherId.size())
    {
        wxASSERT(false); // had an invalid launcher reference in db?
        return 0;
    }

    for (size_t n=0; n<mpDBObject->launcherId.size(); n++)
    {
        if (mpDBObject->launcherId[n] == id)
        {
            return mcLauncherState.GetLauncher(n);
        }
    }

    return 0;
}


/**
* @return quantity of item available in all magazines on platform
*/
unsigned int tcPlatformObject::GetMagazineQuantity(const std::string& item)
{
    std::string s;
    unsigned int quantity = 0;
    size_t nMagazines = magazines.size();
    for (size_t n=0; n<nMagazines; n++)
    {
        quantity += magazines[n]->CurrentItemQuantity(item, s);
    }

    return quantity;
}

float tcPlatformObject::GetMaxTurnRate() const
{
    return reducedTurnRate_degps;
}

/**
* @return true if either currently equipped for target type or
* parent magazines have compatible weapons in stock for target type
*/
bool tcPlatformObject::IsCapableVsTargetType(int targetFlag)
{
	if (IsEquippedForTargetType(targetFlag)) return true;

	tcPlatformObject* parentPlatform = dynamic_cast<tcPlatformObject*>(parent);
	if (parentPlatform == 0) return false; // not landed or docked, or parent is not tcPlatformObject

	size_t nMagazines = parentPlatform->GetMagazineCount();
	for (size_t n=0; n<nMagazines; n++)
	{
		tcStores* mag = parentPlatform->GetMagazine(n);
		int magFlags = mag->GetAvailableTargetFlags(this);
		if ((magFlags & targetFlag) != 0) return true;
	}

	return false;
}

void tcPlatformObject::AdjustExternalFuelCapacity(float change_kg)
{
	externalFuelCapacity_kg += change_kg;
	
	if (externalFuelCapacity_kg < 0)
	{
		wxASSERT(externalFuelCapacity_kg >= -0.1f); // allow for some rounding error here
		externalFuelCapacity_kg = 0;
	}

	float adjustedCapacity_kg = GetFuelCapacity();
	if (fuel_kg > adjustedCapacity_kg) fuel_kg = adjustedCapacity_kg;
	
}


/**
* @return true if all launchers empty and not loading
*/
bool tcPlatformObject::AllLaunchersEmpty()
{
	size_t nLaunchers = GetLauncherCount();
	for (size_t n=0; n<nLaunchers; n++)
	{
		tcLauncher* launcher = GetLauncher(n);
		if ((launcher->IsLoading()) || (launcher->mnCurrent > 0)) return false;
	}

	return true;
}

/**
* @return true if all launchers full and not loading
*/
bool tcPlatformObject::AllLaunchersFull()
{
	size_t nLaunchers = GetLauncherCount();
	for (size_t n=0; n<nLaunchers; n++)
	{
		tcLauncher* launcher = GetLauncher(n);
		//if ((launcher->IsLoading()) || (launcher->mnCurrent < launcher->capacity)) return false;
        if ((launcher->IsLoading()) || (launcher->mnCurrent == 0)) return false;
	}

	return true;
}

/**
* @return true if all launchers not loading
*/
bool tcPlatformObject::AllLaunchersReady()
{
	size_t nLaunchers = GetLauncherCount();
	for (size_t n=0; n<nLaunchers; n++)
	{
		tcLauncher* launcher = GetLauncher(n);
		//if ((launcher->IsLoading()) || (launcher->mnCurrent < launcher->capacity)) return false;
        if (launcher->IsLoading()) return false;
	}

	return true;
}


/**
* @return true if fully equipped, done loading, and at least one 
* launcher is effective vs. target type
*/
bool tcPlatformObject::IsEquippedForTargetType(int targetFlag)
{
	if (targetFlag == 0) return false; // don't call this to check empty

    if ((targetFlag & AEW_TARGET) != 0)
    {
        size_t nSensors = (size_t)GetSensorCount();

        for (size_t n=0; n<nSensors; n++)
        {
            const tcRadar* radar = dynamic_cast<const tcRadar*>(GetSensor(n));
            if ((radar != 0) && 
                (radar->mpDBObj->isSurveillance) && 
                (radar->mpDBObj->mfFieldOfView_deg >= 360))
            {
                return true;
            }
        }
        return false;
    }

	bool anyEffective = false;

	size_t nLaunchers = GetLauncherCount();
	for (size_t n=0; n<nLaunchers; n++)
	{
		tcLauncher* launcher = GetLauncher(n);
		if (launcher->IsLoading() || (launcher->mnCurrent == 0)) // 30MAY2011 changed to allow undercapacity, no particular reason, just seems too restrictive with weight limits
        {
            return false;
        }
		anyEffective = anyEffective || ((launcher->mnTargetFlags & targetFlag) != 0);
	}

	return anyEffective;
}

/**
* @return true if fully equipped, done loading, and at least one launcher is effective vs. target type
*/
bool tcPlatformObject::RatingForTargetType(int targetFlag, float& weaponWeight_kg, float& maxRange_km)
{
	if (targetFlag == 0) return false; // don't call this to check empty

    if ((targetFlag & AEW_TARGET) != 0)
    {
        return RatingForTargetTypeAEW(weaponWeight_kg, maxRange_km);
    }

	bool anyEffective = false;
	bool stillLoading = false;
	weaponWeight_kg = 0;
	maxRange_km = 0;

	size_t nLaunchers = GetLauncherCount();
	for (size_t n=0; n<nLaunchers; n++)
	{
		tcLauncher* launcher = GetLauncher(n);
		stillLoading = stillLoading || launcher->IsLoading();
		
		if (((launcher->mnTargetFlags & targetFlag) != 0) && (launcher->mnCurrent > 0))
		{
			anyEffective = true;
			weaponWeight_kg += float(launcher->mnCurrent) * launcher->GetItemWeight();
			tcWeaponDBObject* weaponData = dynamic_cast<tcWeaponDBObject*>(launcher->GetChildDatabaseObject());
			if (weaponData != 0)
			{
				maxRange_km = std::max(weaponData->maxRange_km, maxRange_km);
			}
			else
			{
				wxASSERT(false);
			}
		}

		
	}

	return anyEffective && !stillLoading;
}

/**
* Version "work-around" to support AEW missions
* @maxRange_km max ref range of search radar
* @return true if fully equipped, done loading, and at least one launcher is effective vs. target type
*/
bool tcPlatformObject::RatingForTargetTypeAEW(float& weaponWeight_kg, float& maxRange_km)
{
	bool anyEffective = false;
	weaponWeight_kg = 0;
	maxRange_km = 0;
    const float minRefRange_km = 25.0f;
    const float minMaxRange_km = 100.0f;

    size_t nSensors = (size_t)GetSensorCount();

	for (size_t n=0; n<nSensors; n++)
	{
		const tcRadar* radar = dynamic_cast<const tcRadar*>(GetSensor(n));
        if ((radar != 0) && (!radar->IsDamaged()) && 
            (radar->mpDBObj->mfFieldOfView_deg >= 360) &&
            (radar->mpDBObj->isSurveillance) &&
            (radar->mpDBObj->mfRefRange_km >= minRefRange_km) && 
            (radar->mpDBObj->mfMaxRange_km >= minMaxRange_km))
        {
            anyEffective = true;
            maxRange_km = std::max(maxRange_km, radar->mpDBObj->mfRefRange_km);
        }
	}

	return anyEffective;
}


/**
* @return true if fully equipped, done loading, and at least one 
* launcher is effective vs. target type and has at least one nuclear weapon
*/
bool tcPlatformObject::IsEquippedWithNuclear(int targetFlag)
{
	if (targetFlag == 0) return false; // don't call this to check empty

	bool anyEffective = false;

	size_t nLaunchers = GetLauncherCount();
	for (size_t n=0; n<nLaunchers; n++)
	{
		tcLauncher* launcher = GetLauncher(n);
		if (launcher->IsLoading() || (launcher->mnCurrent == 0) || 
            (launcher->capacity > launcher->mnCurrent))
        {
            return false;
        }

		anyEffective = anyEffective || 
            (launcher->IsLoadedNuclear() && ((launcher->mnTargetFlags & targetFlag) != 0));
	}

	return anyEffective;
}


/**
* @return true if any launchers are loading or unloading
*/
bool tcPlatformObject::IsLoading() const
{
    size_t nLaunchers = GetLauncherCount();
	for (size_t n=0; n<nLaunchers; n++)
	{
		const tcLauncher* launcher = GetLauncher(n);
		if (launcher->IsLoading()) return true;
	}

    return false;
}



void tcPlatformObject::UnloadAllLaunchers()
{
	tcPlatformObject* parentPlatform = dynamic_cast<tcPlatformObject*>(parent);
	if (parentPlatform == 0)
	{
		fprintf(stderr, "tcPlatformObject::UnloadAllLaunchers - no host platform (%s)\n", 
			GetName());
		wxASSERT(false);
		return; // not landed or docked, or parent is not tcPlatformObject
	}
    
    // check if anything loaded
	size_t nLaunchers = GetLauncherCount();
    bool anyLoaded = false;
	for (size_t n=0; (n<nLaunchers)&&(!anyLoaded); n++)
	{
		tcLauncher* launcher = GetLauncher(n);    
		wxASSERT(launcher);

        anyLoaded = anyLoaded || (launcher->mnCurrent > 0);
    }
    if (!anyLoaded)
    {
        SetLoadoutTag("");
        return; // already empty
    }

	size_t nMagazines = parentPlatform->GetMagazineCount();
	for (size_t n=0; n<nMagazines; n++)
	{
		tcStores* mag = parentPlatform->GetMagazine(n);
        if (mag->CanUnloadThisObject(this))
		{
			mag->AddAutomationOp("Empty", this); // all equip for platform has to be in one magazine
			return;
		}
	}

	fprintf(stderr, "tcPlatformObject::EquipForTargetType('empty') - no mags available (%s)\n", 
		GetName());
	wxASSERT(false);
}

/**
* @param targetType "Empty" "AAW" "ASuW" "ASW" "Strike"
*/
void tcPlatformObject::EquipForTargetType(const std::string& targetType)
{
	if (targetType == "Empty")
	{
		UnloadAllLaunchers();
		return;
	}

	tcPlatformObject* parentPlatform = dynamic_cast<tcPlatformObject*>(parent);
	if (parentPlatform == 0)
	{
		fprintf(stderr, "tcPlatformObject::EquipForTargetType - no host platform (%s)\n", 
			GetName());
		wxASSERT(false);
		return; // not landed or docked, or parent is not tcPlatformObject
	}

    bool useNuclear = false;

	int targetFlag = 0;
	if (targetType == "AAW") targetFlag = AIR_TARGET;
	else if (targetType == "ASuW") targetFlag = SURFACE_TARGET;
	else if (targetType == "ASW") targetFlag = SUBSURFACE_TARGET;
	else if (targetType == "Strike") targetFlag = LAND_TARGET;
    else if (targetType == "Nuclear")
    {
        targetFlag = AIR_TARGET | SURFACE_TARGET | LAND_TARGET;
        useNuclear = true;
    }
	else 
	{
		fprintf(stderr, "tcPlatformObject::EquipForTargetType - targetType not found (%s)\n", 
			GetName());
		wxASSERT(false);
		return;
	}

	size_t nMagazines = parentPlatform->GetMagazineCount();
	for (size_t n=0; n<nMagazines; n++)
	{
		tcStores* mag = parentPlatform->GetMagazine(n);
		int magFlags = mag->GetAvailableTargetFlags(this, useNuclear);
		if ((magFlags & targetFlag) != 0)
		{
			mag->AddAutomationOp(targetType, this);
			return;
		}
	}

	fprintf(stdout, "tcPlatformObject::EquipForTargetType - no compatible equipment found (%s)\n", 
		GetName());
}

/**
* Schedule automatic loadout op for target type. Platform must be
* landed and have access to appropriate stores
*/
void tcPlatformObject::EquipForTargetType(int targetFlag)
{
	if ((targetFlag != 0) && (IsEquippedForTargetType(targetFlag))) return; // already equipped

	std::string loadoutType;
	if (targetFlag == 0)
	{
		loadoutType = "Empty";
	}
	else if ((targetFlag & AIR_TARGET) != 0)
	{
		loadoutType = "AAW";
	}
	else if ((targetFlag & SURFACE_TARGET) != 0)
	{
		loadoutType = "ASuW";
	}	
	else if ((targetFlag & SUBSURFACE_TARGET) != 0)
	{
		loadoutType = "ASW";
	}	
	else if ((targetFlag & LAND_TARGET) != 0)
	{
		loadoutType = "Strike";
	}
	else
	{
		fprintf(stderr, "tcPlatformObject::EquipForTargetType - bad target flag (%s)\n", 
			GetName());
		wxASSERT(false); // bad targetFlag
		return;
	}

	EquipForTargetType(loadoutType);
}


/**
* To avoid dynamic_cast for testing if tcPlatformObject
*/
bool tcPlatformObject::IsPlatformObject() const
{
    return true;
}

bool tcPlatformObject::IsRefueling() const
{
	return isRefueling;
}

/**
* @return key of object to launch, otherwise NULL_INDEX
*/
void tcPlatformObject::Launch(long& rnKey, unsigned& rnLauncher) 
{
    mcLauncherState.Launch(rnKey, rnLauncher);
}

/**
* Sets goal altitude in guidance
*/
void tcPlatformObject::SetAltitude(float new_altitude_m) 
{
    mcGS.SetAltitude(new_altitude_m);
    commandObj.SetNewCommand(ALT_CMD);

	if (IsEditMode())
	{
		mcKin.mfAlt_m = new_altitude_m;
	}
}

/**
* Sets goal heading in guidance
*/
void tcPlatformObject::SetHeading(float afNewHeading) 
{
    mcGS.SetHeading(afNewHeading);
    commandObj.SetNewCommand(HEADING_CMD);

	if (IsEditMode())
	{
		mcKin.mfHeading_rad = afNewHeading;
		if (mcKin.mfHeading_rad < 0) mcKin.mfHeading_rad += C_TWOPI;
	}
}

void tcPlatformObject::SetRefueling(bool state)
{
	isRefueling = state;
}

/**
* Set goal speed to afNewSpeed. If goal speed
* is greater than max speed then set goal to
* max speed.
*/
void tcPlatformObject::SetSpeed(float newSpeed) 
{
    mcGS.SetSpeed(newSpeed);
    commandObj.SetNewCommand(SPEED_CMD);

	if (IsEditMode())
	{
		mcKin.mfSpeed_kts = newSpeed;
	}
}

/**
* If launcher is ready, increment pending of anLauncher by anQuantity.
* This method does not support targeting multiple targets.
* @return tcLauncherState::teLauncherStatus error code, LAUNCHER_READY = 0 for success
*/
int tcPlatformObject::SetLaunch(int anLauncher, int anQuantity) 
{
    return mcLauncherState.SetLaunch(anLauncher, anQuantity);
}



void tcPlatformObject::RandInitNear(float afLon_deg, float afLat_deg) 
{
    //  tcGameObject::RandInitNear(afLon,afLat);
    if (mpDBObject == NULL) {return;}
    mzClass = mpDBObject->mzClass;
    mzUnit = "PL_";
    mzUnit.AssignRandomSuffix();

    mfStatusTime = 0;        
    mcKin.mfLon_rad = C_PIOVER180*(afLon_deg + randfc(1.1f));      
    mcKin.mfLat_rad = C_PIOVER180*(afLat_deg + randfc(1.1f));
    mcKin.mfAlt_m = (mpDBObject->mnType == PTYPE_FIXEDWING) ? 5000.0f : 0.0f;               
    mcKin.mfHeading_rad = C_TWOPI*randf();           
    mcKin.mfSpeed_kts = 0.80f*mpDBObject->mfMaxSpeed_kts;
    mcKin.mfPitch_rad = 0;
    mcKin.mfRoll_rad = 0;
    mfDamageLevel = 0;  
    SetHeading(mcKin.mfHeading_rad);
    SetSpeed(mcKin.mfSpeed_kts);   
    SetAltitude(mcKin.mfAlt_m);
	fuel_kg = mpDBObject->GetInternalFuelCapacity();
    lastHeadingDelta = 0;
}


void tcPlatformObject::PrintToFile(tcFile& file) 
{
    tcString s;

    tcGameObject::PrintToFile(file);
    int nLaunchers = mcLauncherState.mnCount;

    if (nLaunchers > tcPlatformDBObject::MAXLAUNCHERS) 
    {
        file.WriteString("Error - launcher count overflow");
        mcLauncherState.mnCount = 0;
        nLaunchers = 0;
    }

    for(int i=0;i<nLaunchers;i++) 
    {
        s.Format("   LAU%d: %s x %d\n",i, 
            mcLauncherState.GetLauncherChildClass(i),
            mcLauncherState.GetLauncherQuantity(i));
        file.WriteString(s.GetBuffer());
    }
    
    tcSensorPlatform::PrintToFile(file);
    
}

void tcPlatformObject::SaveToFile(tcFile& file) 
{
    wxASSERT(false);

    tcGameObject::SaveToFile(file); 

    file.Write(&fuel_kg,sizeof(fuel_kg));
    
    tcSensorPlatform::SaveToFile(file);
    
    // other data
    mcLauncherState.Serialize(file, false);
    mcGS.Serialize(file, false);
}

/**
*
*/
void tcPlatformObject::LoadFromFile(tcFile& file) 
{
    tcGameObject::LoadFromFile(file);

    file.Read(&fuel_kg,sizeof(fuel_kg));
    
    tcSensorPlatform::LoadFromFile(file);

    // other data
    mcLauncherState.Serialize(file, true);
    mcGS.Serialize(file, true);
}


/**
*
*/
void tcPlatformObject::Serialize(tcFile& file, bool mbLoad) 
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

void tcPlatformObject::SaveToPython(scriptinterface::tcScenarioLogger& logger)
{
    tcScenarioRandomizer* randomizer = tcScenarioRandomizer::Get();

	wxString s;

    float terrainHeight_m = mapData->GetTerrainHeight(C_180OVERPI*mcKin.mfLon_rad, C_180OVERPI*mcKin.mfLat_rad, 0);
    if (terrainHeight_m < 0) terrainHeight_m = 0;

	logger.AddScenarioText("unit = SM.GetDefaultUnit()");
    
	s.Printf("unit.className = '%s'", mzClass.c_str());
	logger.AddScenarioText(s);

	s.Printf("unit.unitName = \"%s\"", mzUnit.c_str());
	logger.AddScenarioText(s);

	wxASSERT((mcKin.mfLon_rad >= -C_PI) && (mcKin.mfLon_rad < C_PI));
	wxASSERT((mcKin.mfLat_rad >= -C_PIOVER2) && (mcKin.mfLat_rad <= C_PIOVER2));

    if (!formation.IsFollower())
    {
        std::vector<tcRect> randomBoxes = randomizer->GetRandomBoxes(mzUnit.c_str());
        if (randomBoxes.size() == 0)
        {
            s.Printf("unit.SetPosition(%f, %f, %.1f)", C_180OVERPI*mcKin.mfLon_rad,
                C_180OVERPI*mcKin.mfLat_rad, mcKin.mfAlt_m - terrainHeight_m);
            logger.AddScenarioText(s);
        }
        else
        {
            s = "boxes = [";
            for (size_t k=0; k<randomBoxes.size(); k++)
            {
                if (k > 0) s += ",";
                s += wxString::Format("[%.4f, %.4f, %.4f, %.4f]",
                    C_180OVERPI*randomBoxes[k].left, C_180OVERPI*randomBoxes[k].right, 
                    C_180OVERPI*randomBoxes[k].bottom, C_180OVERPI*randomBoxes[k].top);
            }
            s += "]";
            logger.AddScenarioText(s);

            s.Printf("box = boxes[int(%d*random())]", randomBoxes.size());
            logger.AddScenarioText(s);

            logger.AddScenarioText("lon_deg = random()*(box[1]-box[0]) + box[0]");
            logger.AddScenarioText("lat_deg = random()*(box[3]-box[2]) + box[2]");

            s.Printf("unit.SetPosition(lon_deg, lat_deg, %.1f)", mcKin.mfAlt_m - terrainHeight_m);
            logger.AddScenarioText(s);
        }
    }
    else
    {
        SaveFormationPositionToPython(logger);
    }

	s.Printf("unit.heading = %.2f", C_180OVERPI*mcKin.mfHeading_rad);
    logger.AddScenarioText(s);

	s.Printf("unit.speed = %.1f", mcKin.mfSpeed_kts);
	logger.AddScenarioText(s);

    if (GetCost() >= 0)
    {
        s.Printf("unit.cost = %.1f", GetCost());
        logger.AddScenarioText(s);
    }

	s.Printf("SM.AddUnitToAlliance(unit, %d)", GetAlliance());
	logger.AddScenarioText(s);

    size_t nLaunchers = GetLauncherCount();
    for (size_t k=0; k<nLaunchers; k++)
    {
        tcLauncher* launcher = GetLauncher(k);
        if (launcher->mnCurrent > 0)
        {
            s.Printf("SM.SetUnitLauncherItem(unit.unitName, %d, '%s', %d)", k,
                launcher->GetChildClassName().c_str(), launcher->mnCurrent);
        }
        else
        {
            s.Printf("SM.SetUnitLauncherItem(unit.unitName, %d, '', 0)", k);
        }
        logger.AddScenarioText(s);
    }    
    
    if (simState->mcSensorMap.GetAlwaysVisibleState(this))
    {
        logger.AddScenarioText("SM.SetUnitAlwaysVisibleState(unit.unitName, 1)");
    }

    logger.AddScenarioText("UI = SM.GetUnitInterface(unit.unitName)");

	for (size_t k=0; k<magazines.size(); k++)
	{
		magazines[k]->SaveToPython(logger);
	}

    tcSensorPlatform::SaveToPython(logger);

	brain->SaveToPython(logger);

    formation.SaveToPython(logger);
}

void tcPlatformObject::SaveFormationPositionToPython(scriptinterface::tcScenarioLogger& logger)
{
    wxString s;
    const tcPlatformObject* leader = dynamic_cast<tcPlatformObject*>(simState->GetObject(formation.leaderId));
    if (leader == 0)
    {
        s.Printf("unit.SetPosition(%f, %f, %.1f)", C_180OVERPI*mcKin.mfLon_rad,
                C_180OVERPI*mcKin.mfLat_rad, mcKin.mfAlt_m);
        logger.AddScenarioText(s);
        wxASSERT(false); // follower without leader, shouldn't happen
        return;
    }

    float dlon_deg = C_180OVERPI * (mcKin.mfLon_rad - leader->mcKin.mfLon_rad);
    float dlat_deg = C_180OVERPI * (mcKin.mfLat_rad - leader->mcKin.mfLat_rad);

    s.Printf("UI = SM.GetUnitInterface('%s')", leader->mzUnit.c_str());
    logger.AddScenarioText(s);

    s.Printf("leader_track = UI.GetTrackById(UI.GetPlatformId())");
    logger.AddScenarioText(s);

    s.Printf("lon_deg = 57.296*leader_track.Lon + %.4f", dlon_deg);
    logger.AddScenarioText(s);

    s.Printf("lat_deg = 57.296*leader_track.Lat + %.4f", dlat_deg);
    logger.AddScenarioText(s);

    s.Printf("unit.SetPosition(lon_deg, lat_deg, %.1f)", mcKin.mfAlt_m);
    logger.AddScenarioText(s);
}


/**
* Loads state from command stream
*/
tcCommandStream& tcPlatformObject::operator<<(tcCommandStream& stream)
{
    tcGameObject::operator<<(stream);

	ClearNewCommand();

    unsigned short updateMask;
    stream >> updateMask;

    if (updateMask & UPDATE_GUIDANCE)
    {
		stream >> mcGS.mfGoalHeading_rad;
		stream >> mcGS.mfGoalSpeed_kts;
		stream >> mcGS.mfGoalAltitude_m;
	}

    if (updateMask & UPDATE_LAUNCHERS)
    {
        mcLauncherState << stream;
    }

    if (updateMask & UPDATE_SENSORS)
    {
        tcSensorPlatform::operator<<(stream);
    }

	if (updateMask & UPDATE_AI)
	{
		brain->operator<<(stream);
	}
	
    if (updateMask & UPDATE_STORES)
    {
        for (size_t n=0; n<magazines.size(); n++)
	    {
            unsigned char updateMag;
            stream >> updateMag;
            if (updateMag != 0)
            {   
                magazines[n]->operator<<(stream);
            }
        }
    }

    if (updateMask & UPDATE_FORMATION)
    {
        formation.operator<<(stream);
    }


    return stream;
}

/**
* Saves state to command stream
*/
tcCommandStream& tcPlatformObject::operator>>(tcCommandStream& stream)
{
    tcGameObject::operator>>(stream);

    // form update mask
    unsigned short updateMask = 0;
    updateMask = UPDATE_GUIDANCE; // always update guidance for now

	if (mcLauncherState.HasNewCommand())
    {
        updateMask |= UPDATE_LAUNCHERS;
    }
    if (tcSensorPlatform::HasNewCommand())
    {
        updateMask |= UPDATE_SENSORS;
    }
	if (brain->HasNewCommand())
	{
		updateMask |= UPDATE_AI;
	}
	
	for (size_t n=0; n<magazines.size(); n++)
	{
        if (magazines[n]->HasNewCommand())
        {
            updateMask |= UPDATE_STORES;
        }
    }

    if (formation.HasNewCommand())
    {
        updateMask |= UPDATE_FORMATION;
    }
    
	if (stream.GetDetailLevel() == tcStream::WRITE_ALL) updateMask = 0xFF;

	//if (IsClientMode()) updateMask &= (~UPDATE_AI); // don't do ai updates at client

    stream << updateMask;


    if (updateMask & UPDATE_GUIDANCE)
    {
        stream << mcGS.mfGoalHeading_rad;
        stream << mcGS.mfGoalSpeed_kts;
        stream << mcGS.mfGoalAltitude_m;
    }
    
    if (updateMask & UPDATE_LAUNCHERS)
    {
        mcLauncherState >> stream;
    }

    if (updateMask & UPDATE_SENSORS)
    {
        tcSensorPlatform::operator>>(stream);
    }

	if (updateMask & UPDATE_AI)
	{
		brain->operator>>(stream);
	}

    if (updateMask & UPDATE_STORES)
    {
        for (size_t n=0; n<magazines.size(); n++)
	    {
            if (magazines[n]->HasNewCommand())
            {   
                unsigned char updateMag = 1;
                stream << updateMag;
                magazines[n]->operator>>(stream);
            }
            else
            {
                unsigned char updateMag = 0;
                stream << updateMag;
            }
        }
    }

    if (updateMask & UPDATE_FORMATION)
    {
        formation.operator>>(stream);
    }

    return stream;
}

/**
* Loads state from create stream
*/
tcCreateStream& tcPlatformObject::operator<<(tcCreateStream& stream)
{
    tcGameObject::operator<<(stream);

    tcSensorPlatform::operator<<(stream);    

    return stream;
}

/**
* Saves state to create stream
*/
tcCreateStream& tcPlatformObject::operator>>(tcCreateStream& stream)
{
    tcGameObject::operator>>(stream);
    
    tcSensorPlatform::operator>>(stream);    

    return stream;
}


/**
* Loads state from update stream
*/
tcUpdateStream& tcPlatformObject::operator<<(tcUpdateStream& stream)
{
    tcGameObject::operator<<(stream);

    mcLauncherState.operator<<(stream);

    tcSensorPlatform::operator<<(stream);

	unsigned char nMagazines;
	stream >> nMagazines;
	if (magazines.size() != nMagazines)
	{
		fprintf(stderr, "tcPlatformObject::operator<< - bad platform update\n");
		wxASSERT(false);
		return stream;
	}

	for (unsigned char n=0; n<nMagazines; n++)
	{
		magazines[n]->operator<<(stream);
	}

    return stream;
}

/**
* Saves state to update stream
*/
tcUpdateStream& tcPlatformObject::operator>>(tcUpdateStream& stream)
{
    tcGameObject::operator>>(stream);

    mcLauncherState.operator>>(stream);

    tcSensorPlatform::operator>>(stream);

	unsigned char nMagazines = (unsigned char)magazines.size();
	stream << nMagazines;
	for (unsigned char n=0; n<nMagazines; n++)
	{
		magazines[n]->operator>>(stream);
	}

    return stream;
}


/**
* Loads state from game stream
*/
tcGameStream& tcPlatformObject::operator<<(tcGameStream& stream)
{
    tcGameObject::operator<<(stream);

    mcLauncherState.operator<<(stream);

    tcSensorPlatform::operator<<(stream);

	unsigned char nMagazines;
	stream >> nMagazines;
	if (magazines.size() != nMagazines)
	{
		fprintf(stderr, "tcPlatformObject::operator<<(tcGameStream) -- corrupt stream\n");
		wxASSERT(false);
		return stream;
	}
	for (unsigned char n=0; n<nMagazines; n++)
	{
		magazines[n]->operator<<(stream);
	}

    stream >> fuel_kg;
	stream >> externalFuelCapacity_kg;
    stream >> lastHeadingDelta;
	stream >> isRefueling;
	stream >> loadoutTag;
    stream >> reducedTurnRate_degps;
    mcGS << stream;

    *brain << stream;

    stream >> mcLaunchRequest.mnLauncher;
    stream >> mcLaunchRequest.mnQuantity;
    msTargetDatum << stream;

	if (stream.GetVersionId() >= 10) formation.operator<<(stream);

    commandObj << stream;

    missilePreplan.clear();
    unsigned char nPreplan;
    stream >> nPreplan;
    for (unsigned char n=0; n<nPreplan; n++)
    {
        GeoPoint p;
        p << stream;
        missilePreplan.push_back(p);
    }

    stream.ReadCheckValue(143);

    return stream;
}

/**
* Saves state to game stream
*/
tcGameStream& tcPlatformObject::operator>>(tcGameStream& stream)
{
    tcGameObject::operator>>(stream);

    mcLauncherState.operator>>(stream);

    tcSensorPlatform::operator>>(stream);

	unsigned char nMagazines = magazines.size();
	stream << nMagazines;
	for (unsigned char n=0; n<nMagazines; n++)
	{
		magazines[n]->operator>>(stream);
	}

    stream << fuel_kg;
	stream << externalFuelCapacity_kg;
    stream << lastHeadingDelta;
	stream << isRefueling;
	stream << loadoutTag;
    stream << reducedTurnRate_degps;
    mcGS >> stream;

    *brain >> stream;

    stream << mcLaunchRequest.mnLauncher;
    stream << mcLaunchRequest.mnQuantity;
    msTargetDatum >> stream;

	if (stream.GetVersionId() >= 10) formation.operator>>(stream);

    commandObj >> stream;

    wxASSERT(missilePreplan.size() < 256);
    unsigned char nPreplan = (unsigned char)missilePreplan.size();
    stream << nPreplan;
    for (unsigned char n=0; n<nPreplan; n++)
    {
        missilePreplan[n] >> stream;
    }

    stream.WriteCheckValue(143);

    return stream;
}


void tcPlatformObject::ClearNewCommand()
{
    commandObj.ClearNewCommand();
    mcLauncherState.ClearNewCommand();
    tcSensorPlatform::ClearNewCommand();
	brain->ClearNewCommand();
    formation.ClearNewCommand();
	
	for (size_t n=0; n<magazines.size(); n++)
	{
        magazines[n]->ClearNewCommand();
    }
}

bool tcPlatformObject::HasNewCommand() const
{
	bool newBrainCommand = brain->HasNewCommand();
	
	if (newBrainCommand) return true;

	for (size_t n=0; n<magazines.size(); n++)
	{
		if (magazines[n]->HasNewCommand()) return true;
    }

    return commandObj.HasNewCommand() || mcLauncherState.HasNewCommand() ||
		tcSensorPlatform::HasNewCommand() || formation.HasNewCommand();
}

void tcPlatformObject::SetController(const std::string& username)
{
	// set controller for all children
	size_t nChildren = children.size();
	for (size_t n=0; n<nChildren; n++)
	{
		children[n]->SetController(username);
	}

	tcControllableObject::SetController(username);
}

/**
* Set fire control sensors for launchers. If launcher
* has a non-null fire control sensor, then find and set
* it.
*/
void tcPlatformObject::SetFireControlSensors()
{
    size_t nSensors = tcSensorPlatform::GetSensorCount();
    
	size_t nLaunchers = mcLauncherState.GetLauncherCount();
 
    wxASSERT(mpDBObject->launcherFireControl.size() == nLaunchers);

    for (size_t nLauncher=0; nLauncher<nLaunchers; nLauncher++) 
    {
        tcLauncher* launcher = GetLauncher(nLauncher);
        launcher->UpdateFireControlSensor();
    }
}

void tcPlatformObject::SetFormationAltitudeOffset(float dh_m)
{
    formation.SetAltitudeOffset(dh_m);
}

void tcPlatformObject::SetFormationLeader(long id)
{
    formation.SetPlatformId(mnID);

    if (id < 0)
    {
        formation.LeaveFormation();
        return;
    }

    tcPlatformObject* leader = dynamic_cast<tcPlatformObject*>(simState->GetObject(id));

    // allow formation with non-friendly if within 1.0 km range 
    if (leader == 0) return;
    
    bool hostileFormation = (leader->GetAlliance() != GetAlliance());
    const float hostileFormationRange_km = 1.5f;
    if (hostileFormation && (leader->RangeTo(*this) > hostileFormationRange_km))
    {
        return;
    }

    // for hostile formations, there is no leader participation

    // check that leader is not part of a formation as a follower
    if (leader->formation.isActive && (!hostileFormation) && (leader->formation.leaderId != -1)) return;

    // check that current leader != id
    if (formation.isActive && (formation.leaderId == id)) return;

    // if already part of formation, remove from old formation
    if (formation.isActive && (formation.leaderId != -1))
    {
        tcPlatformObject* oldLeader = 
            dynamic_cast<tcPlatformObject*>(simState->GetObject(formation.leaderId));
        if ((oldLeader != 0) && (oldLeader->GetAlliance() == GetAlliance()))
        {
            oldLeader->formation.RemoveFollower(mnID);
        }
    }

    if (!hostileFormation)
    {
        leader->formation.isActive = true;
        leader->formation.leaderId = -1;
        leader->formation.AddFollower(mnID);
    }


    formation.isActive = true;
    formation.leaderId = id;
    formation.useNorthBearing = false;
    formation.range_center_km = 2.0f;
    formation.range_span_km = 0.5f;
    formation.bearing_center_rad = 0.2f;
    formation.bearing_span_rad = 0.2f;

	SetFormationMode(tcFormation::SPRINTDRIFT);
}

void tcPlatformObject::SetFormationMode(int mode)
{
	formation.SetFormationMode(mode);

    MarkFormationUpdated();
}

void tcPlatformObject::SetFormationPosition(float range_km, float span_km, float bearing_rad, float span_rad)
{
    formation.SetFormationPosition(range_km, span_km, bearing_rad, span_rad);
}

void tcPlatformObject::MarkFormationUpdated()
{
    formation.SetNewCommand();
}


/**
*
*/
tcPlatformObject::tcPlatformObject()
: mpDBObject(0),
  loadoutTag(""),
  reducedTurnRate_degps(0)
{
    wxASSERT(false);
    Clear();
    brain = new Brain(this);
    mcLauncherState.mnCount = 0;
    mnModelType = MTYPE_PLATFORM;
}


tcPlatformObject::tcPlatformObject(tcPlatformDBObject *obj)
: tcGameObject(obj), tcSensorPlatform(),
  isRefueling(false),
  loadoutTag(""),
  reducedTurnRate_degps(360.0f),
  externalFuelCapacity_kg(0)
{
    using namespace database;

    tcSensorPlatform::Init(obj, this);

    brain = new Brain(this);

    mpDBObject = obj;
    mnModelType = MTYPE_PLATFORM;

//    mcAI.ClearOrders();

	fuel_kg = mpDBObject->GetInternalFuelCapacity(); // max internal fuel


    // add magazines
    if (mpDBObject->mnNumMagazines > tcPlatformDBObject::MAXMAGAZINES) 
    {
        mpDBObject->mnNumMagazines = tcPlatformDBObject::MAXMAGAZINES;
        fprintf(stderr, "tcPlatformObject::tcPlatformObject - Warning - "
            "DB magazine count exceeded limit\n");
    }

    magazines.clear();
    for (int i=0; i<mpDBObject->mnNumMagazines; i++) 
    {
        tcDatabaseObject* pDBObj = database->GetObject(mpDBObject->maMagazineClass[i].c_str());

        if (tcStoresDBObject* storesDBObj = dynamic_cast<tcStoresDBObject*>(pDBObj))
		{
            tcStores* mag = new tcStores(storesDBObj);
            mag->SetParent(this);
            magazines.push_back(mag);
		}
		else
		{
			fprintf(stderr, "Error - tcPlatformObject::tcPlatformObject(tcPlatformDBObject *obj)"
				" - Stores obj not found\n");
		}
        
    }

    // add launchers
    mcLauncherState.SetParent(this);
    mcLauncherState.mnCount = 0;

    for (int nLauncher=0; nLauncher<mpDBObject->mnNumLaunchers; nLauncher++) 
    {
        long nLauncherKey = database->GetKey(mpDBObject->maLauncherClass[nLauncher].c_str());
		if (nLauncherKey != -1)
		{
			Vec2 attitude = mpDBObject->GetLauncherAttitude(nLauncher);
            float FOV_deg = mpDBObject->GetLauncherFOV_deg(nLauncher);
            bool isReloadable = mpDBObject->launcherIsReloadable[nLauncher];

			mcLauncherState.AddFullLauncher(nLauncherKey, C_PIOVER180*attitude.x, 
				C_PIOVER180*attitude.y, FOV_deg, mpDBObject->launcherName[nLauncher], isReloadable);
		}
		else
		{
            wxASSERT(false);
			fprintf(stderr, "tcPlatformObject::tcPlatformObject - Launcher not in database (%s)\n",
				mpDBObject->maLauncherClass[nLauncher].c_str());
		}
    }

    SetFireControlSensors();

    model->SetupAnimation(this);

    lastHeadingDelta = 0;
}


/**
*
*/
tcPlatformObject::tcPlatformObject(tcPlatformObject& o) : 
    tcGameObject(o),
    tcSensorPlatform(o),
    commandObj(o.commandObj),
	isRefueling(o.isRefueling),
	loadoutTag(o.loadoutTag),
    reducedTurnRate_degps(o.reducedTurnRate_degps),
	externalFuelCapacity_kg(o.externalFuelCapacity_kg),
    formation(o.formation)
{
    brain = new Brain(this); // need copy constructor for this

    fuel_kg = o.fuel_kg;
//    mcAI = o.mcAI;
    mcGS = o.mcGS;
    mcLauncherState = o.mcLauncherState;
    mcLauncherState.SetParent(this);
    mcLaunchRequest = o.mcLaunchRequest;
    mpDBObject = o.mpDBObject;
    msTargetDatum = o.msTargetDatum;

    wxASSERT(magazines.size() == 0);
    int nMagazines = (int)o.magazines.size();
    for (int n=0; n<nMagazines; n++) 
    {
        wxASSERT(false); // need to write this code
    }

    formation.SetPlatformId(mnID);

}
/**
*
*/
tcPlatformObject::~tcPlatformObject()
{
    DestroyFormation();

    if (brain) delete brain;

    for (size_t n=0; n<magazines.size(); n++)
    {
        delete magazines[n];
    }

}


