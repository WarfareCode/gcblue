/**
** @file tcWeaponObject.cpp
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

#include "stdwx.h" // precompiled header file
#include "tcWeaponObject.h"
#include "tcGameObject.h"
#include "tcMissileObject.h"
#include "tcTorpedoObject.h"
#include "tcBallisticWeapon.h"
#include "tcAirCM.h"
#include "tcWeaponDBObject.h"
#include "tcSensorMap.h"
#include "tcSimState.h"
#include "common/tcStream.h"
#include "common/tcObjStream.h"
#include "common/tcGameStream.h"
#include "database/tcDamageEffect.h"
#include "tcDamageModel.h"
#include "tcMessageInterface.h"
#include "tc3DModel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



/**
* Load state from update stream
*/
tcUpdateStream& tcWeaponObject::operator<<(tcUpdateStream& stream)
{
    tcGameObject::operator<<(stream);

    stream >> intendedTarget;

    return stream;
}

/**
* Save state to update stream
*/
tcUpdateStream& tcWeaponObject::operator>>(tcUpdateStream& stream)
{
    tcGameObject::operator>>(stream);

    stream << intendedTarget;

    return stream;
}


/**
* Load state from game stream
*/
tcGameStream& tcWeaponObject::operator<<(tcGameStream& stream)
{
    tcGameObject::operator<<(stream);

    stream >> intendedTarget;
    stream >> fuseHasTriggered;
    stream >> directHitTargetId;
	stream >> fuseDelay;
    stream >> payloadDeployed;
    stream >> malfunctionChecked;

    stream >> launchingPlatform;
    stream >> datalinkActive;

    int val;
    stream >> val;
    fuseMode = (FuseMode)val;

    return stream;
}

/**
* Save state to game stream
*/
tcGameStream& tcWeaponObject::operator>>(tcGameStream& stream)
{
    tcGameObject::operator>>(stream);

    stream << intendedTarget;
    stream << fuseHasTriggered;
    stream << directHitTargetId;
	stream << fuseDelay;
    stream << payloadDeployed;
    stream << malfunctionChecked;

    stream << launchingPlatform;
    stream << datalinkActive;

    int val = (int)fuseMode;
    stream << val;

    return stream;
}


/**
* @return damage fraction for new damage, 0 means no new damage
*/
float tcWeaponObject::ApplyAdvancedDamage(const Damage& damage, tcGameObject* damager)
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
        fprintf(stderr, "tcWeaponObject::ApplyAdvancedDamage -- NULL damageEffect for %s\n",
            mzClass.c_str());
        wxASSERT(false);
        return 0;
    }

    impactDamage = damageEffect->GetFragmentDamageFactor(damage.kinetic_J);
    if (damage.isPenetration && (impactDamage > 0.02f))
    {
        internalDamage = damageEffect->GetInternalDamageFactor(damage.explosive_kg);
    }
    blastDamage = damageEffect->GetBlastDamageFactor(damage.blast_psi);
    waterBlastDamage = damageEffect->GetWaterBlastDamageFactor(damage.waterBlast_psi);
    thermalDamage = damageEffect->GetRadiationDamageFactor(damage.thermal_J_cm2);
    fragDamage = sqrtf(damage.fragHits) * damageEffect->GetFragmentDamageFactor(damage.fragEnergy_J);


    float cumulativeDamage = impactDamage + internalDamage + blastDamage + waterBlastDamage + thermalDamage + fragDamage;

    wxString damageDescription;
    if (impactDamage > 0) damageDescription.append("K");
    if (internalDamage > 0) damageDescription.append("X");
    if (blastDamage > 0) damageDescription.append("B");
    if (waterBlastDamage > 0) damageDescription.append("U");
    if (thermalDamage > 0) damageDescription.append("T");
    if (fragDamage > 0) damageDescription.append("F");
    SetLastDamageDescription(damageDescription.ToStdString());

    

    if (cumulativeDamage <= 0) return 0; // no damage, exit now

    //float newDamage = randf() * cumulativeDamage;
    float newDamage = (0.7 + (randf() * 0.6)) * cumulativeDamage;
	// Amram - calming this down, a fluctuation from 0 through 200% is a bit much?  The doubling factor already replaced with equivalence
	//		   Set to achieve 100% ±30%, for a range from 70% through 130%.

    mfDamageLevel += newDamage;

    mfDamageLevel = std::min(mfDamageLevel, 1.0f);

    UpdateScoreForDamage(damager, priorDamage);

	if (mfDamageLevel >= 1.0f)
	{
		simState->mcSensorMap.MarkObjectDestroyed(this);
	}

    return newDamage;
}



/**
* Create payload and add to simState
*/
void tcWeaponObject::DeployPayload()
{
    database::tcDatabaseObject* payloadData = database->GetObject(mpDBObject->payloadClass);
    if (payloadData == 0)
    {
        payloadDeployed = true;
        fprintf(stderr, "tcWeaponObject::DeployPayload - Invalid payload (%s)\n",
            mpDBObject->payloadClass.c_str());
        return;
    }


	for (unsigned int n=0; n<mpDBObject->payloadQuantity; n++)
	{
		tcGameObject* payload = simState->CreateGameObject(payloadData);
		if (payload == 0)
		{
			fprintf(stderr, "tcWeaponObject::DeployPayload - Failed to create payload (%s)\n",
				mpDBObject->payloadClass.c_str());
			return;
		}

		LaunchPayload(payload);
	}

   
    payloadDeployed = true;
}



/**
* Called when weapon detonates
*/
void tcWeaponObject::Detonate(float delay_s)
{
	fuseHasTriggered = true;
	fuseDelay = delay_s;

    TestForDud();

	if (goodDetonation)
	{
        if (tcBallisticWeapon* ballistic = dynamic_cast<tcBallisticWeapon*>(this))
        {
            if (ballistic->IsAutocannon()) return;
        }

		tcGameObject* target = simState->GetObject(intendedTarget);
		if (target != 0)
		{
			Vec3 pos;
			Vec3 vel;
			target->GetRelativeStateWorld(this, pos, vel);
			target->GetModel()->AddExplosion(pos);
		}
	}
}

float tcWeaponObject::GetDamage() const
{
	return mpDBObject->mfDamage;
}

float tcWeaponObject::GetDamageEffectRadius() const
{
	if (const database::tcWeaponDamage* weaponDamage = GetDamageModel())
	{
		return weaponDamage->maxRange_m;
	}
	else
	{
		return 0;
	}
}

const database::tcWeaponDamage* tcWeaponObject::GetDamageModel() const
{
    const database::tcWeaponDamage* weaponDamageData = database->GetWeaponDamageData(mpDBObject->damageModel);

    return weaponDamageData;
}

const tcWeaponDBObject* tcWeaponObject::GetDBObject() const
{
    return mpDBObject;
       
}

float tcWeaponObject::GetDetonationDelay() const
{
	return fuseDelay;
}

long tcWeaponObject::GetDirectHitTargetId() const
{
    return directHitTargetId;
}

const Vec3& tcWeaponObject::GetImpactPoint() const
{
    return impactPoint;
}

long tcWeaponObject::GetIntendedTarget() const
{
	return intendedTarget;
}

float tcWeaponObject::GetMassKg() const
{
    return mpDBObject->weight_kg;
}

/**
* Handles case where object has wrapped over +/- 90 latitude at pole
* Same as what tcPlatformObject::Move is doing
*/
void tcWeaponObject::HandlePoleWrap()
{
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
    }
}

/**
* Handles case where object has wrapped over +/- 90 latitude at pole
* Same as what tcPlatformObject::Move is doing
*/
void tcWeaponObject::HandlePoleWrap(tcKinematics& kin)
{
    float wrapLow = float(kin.mfLon_rad < -C_PI);
    float wrapHigh = float(kin.mfLon_rad >= C_PI);

    kin.mfLon_rad += (wrapLow - wrapHigh) * C_TWOPI;

    // check for pole crossing
    if (fabsf(kin.mfLat_rad) >= C_PIOVER2)
    {
        if (kin.mfLat_rad >= C_PIOVER2)
        {
            kin.mfLat_rad = C_PI - kin.mfLat_rad;
        }
        else
        {
            kin.mfLat_rad = -C_PI - kin.mfLat_rad;
        }
        kin.mfHeading_rad = C_PI - kin.mfHeading_rad;
    }
}

bool tcWeaponObject::HasPayload() const
{
	return (mpDBObject->payloadClass.size() > 0);
}


bool tcWeaponObject::IsDatalinkActive() const
{
    return datalinkActive;
}

/**
* @return true if weapon has detonated
*/
bool tcWeaponObject::IsDetonated()
{
	return fuseHasTriggered;
}

bool tcWeaponObject::IsDirectHit() const
{
    return (directHitTargetId != -1);
}

bool tcWeaponObject::IsGoodDetonation() const
{
    return goodDetonation;
}

bool tcWeaponObject::IsGroundFused() const
{
    return (fuseMode == GROUND_FUSE);
}

bool tcWeaponObject::IsIntendedTarget(long id)
{
    if (id == -1) return false;
    return intendedTarget == id;
}

/**
* Initialize state of payload to be launched and call LaunchFrom method
* Possibly move this method higher and combine with tcSimState::AddLaunchedPlatform
* Watch out for side effects from adding to sim objects while they are being updated
*
* @see tcSimState::AddLaunchedPlatform
*/
void tcWeaponObject::LaunchPayload(tcGameObject* payload)
{
    wxASSERT(payload != 0);

	payload->LaunchFrom(this, 0);

 //   if (tcTorpedoObject* torpedo = dynamic_cast<tcTorpedoObject*>(payload))
	//{
	//	torpedo->LaunchFrom(this, 0);
	//}
	//else if (tcMissileObject* missile = dynamic_cast<tcMissileObject*>(payload))
 //   {
 //       missile->LaunchFrom(this, 0);
 //   }
 //   else if (tcBallisticWeapon* ballistic = dynamic_cast<tcBallisticWeapon*>(payload))
 //   {
 //       ballistic->LaunchFrom(this, 0);
 //   }
 //   else if (tcAirCM* airCM = dynamic_cast<tcAirCM*>(payload))
 //   {
 //       airCM->LaunchFrom(this, 0);
 //   }
 //   else
	//{
	//	fprintf(stderr, "tcWeaponObject::LaunchPayload - Invalid payload type (%s)\n",
 //           payload->mpDBObject->GetClassName());
	//}
}

/**
* If malfunctionChecked, just return. Otherwise test for malfunction and 
* SelfDestruct on malfunction.
*/
void tcWeaponObject::MalfunctionCheck()
{
    if (malfunctionChecked) return;

    malfunctionChecked = true;

    bool malfunction = (randf() > mpDBObject->probNoFaults);

    if (malfunction)
    {
        SelfDestruct();

#ifdef _DEBUG
        fprintf(stdout, "%s %s malfunctioned (pr_nf:%.2f)\n", mzClass.c_str(), mzUnit.c_str(), mpDBObject->probNoFaults);

        wxString msg = wxString::Format("WPN MALFUNCTION (%s)", mzClass.c_str());
        tcMessageInterface::Get()->ConsoleMessage(msg.ToStdString());
#endif
    }

}


void tcWeaponObject::SetDetonationDelay(float delay_s)
{
	fuseDelay = delay_s;
}


void tcWeaponObject::SetDirectHitTargetId(long id)
{
    directHitTargetId = id;
}

/**
* @param pos world coordinates (east, up, north) of collision point relative to target origin
*/
void tcWeaponObject::SetImpactPoint(const Vec3& pos)
{
    impactPoint = pos;
}

void tcWeaponObject::SetFuseMode(FuseMode mode)
{
    fuseMode = mode;
}

void tcWeaponObject::SetIntendedTarget(long targetId)
{
    if (intendedTarget == targetId) return;

    intendedTarget = targetId;
    if (targetId == -1) return;
    tcSensorMapTrack *smtrack = 
        simState->mcSensorMap.GetSensorMapTrack(targetId, GetAlliance());
    if (smtrack != 0)
    {
		smtrack->AddEngagement(tcGameObject::mnID);
    }
	else
	{
        // check if this is a friendly
        if (tcGameObject* target = simState->GetObject(targetId))
        { 
            if (target->GetAlliance() != GetAlliance())
            {
                fprintf(stderr, "tcWeaponObject::SetIntendedTarget - targetId %d not found in sensor map and is not a friendly" 
                    "(%s %s)\n", targetId, mzClass.c_str(), mzUnit.c_str());
            }
        }
        else
        {
            fprintf(stderr, "tcWeaponObject::SetIntendedTarget - targetId %d not found in sensor map or simState" 
                "(%s %s)\n", targetId, mzClass.c_str(), mzUnit.c_str());
        }
	}
}

/**
* Should be called exactly once after detonation
* Do random test for dud based on probDetonate in weapon damage model
* If no damage model then set not dud
*/
void tcWeaponObject::TestForDud()
{
    wxASSERT(IsDetonated());

    if (const database::tcWeaponDamage* damageModel = GetDamageModel())
    {
        goodDetonation = (randf() <= damageModel->probDetonate);
    }
    else
    {
        goodDetonation = true;
    }
}



void tcWeaponObject::UpdateDatalinkStatus()
{
    if ((launchingPlatform == -1) || (!mpDBObject->acceptsUserCommands))
    {
        datalinkActive = false;
        return;
    }

    if (tcGameObject* source = simState->GetObject(launchingPlatform))
    {
        float range_km = mcKin.RangeToKmAlt(source);

        float radioHorizon_km = C_RADARHOR * (sqrtf(mcKin.mfAlt_m) + sqrtf(std::max(source->mcKin.mfAlt_m, source->GetZmax()-3.0f)));

        datalinkActive = (range_km <= mpDBObject->datalinkRange_km) && (range_km <= radioHorizon_km);
    }
    else
    {
        launchingPlatform = -1;
        datalinkActive = false;
    }

}


bool tcWeaponObject::WasLaunchedBy(long id) const
{
	return (launchingPlatform == id);
}


/**
 *
 */
tcWeaponObject::tcWeaponObject() 
: fuseHasTriggered(false), fuseDelay(0), intendedTarget(-1),
  mpDBObject(0),
  fuseMode(GROUND_FUSE),
  directHitTargetId(-1),
  impactPoint(0, 0, 0),
  goodDetonation(false),
  payloadDeployed(false),
  malfunctionChecked(false)
{

}

/**
 * Copy constructor.
 */
tcWeaponObject::tcWeaponObject(const tcWeaponObject& o) 
{
    wxASSERT(false); // not supported
}

/**
* Constructor that initializes using info from database entry.
*/
tcWeaponObject::tcWeaponObject(tcWeaponDBObject* obj)
: tcGameObject(obj), 
  fuseHasTriggered(false), fuseDelay(0), intendedTarget(-1),
  mpDBObject(obj),
  fuseMode(GROUND_FUSE),
  directHitTargetId(-1),
  impactPoint(0, 0, 0),
  goodDetonation(false),
  payloadDeployed(false),
  malfunctionChecked(false),
  launchingPlatform(-1),
  datalinkActive(false)
{
    wxASSERT(simState);
}

/**
 *
 */
tcWeaponObject::~tcWeaponObject() 
{
}

