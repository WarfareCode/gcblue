/**  
**  @file tcSimState.cpp
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
#endif

#include "tcSimState.h"
#include "simmath.h"
#include "aerror.h"
#include <wx/datetime.h>
#include <vector>
#include "tcFile.h"
#include "tcSimPythonInterface.h"
#include "tcScenarioInterface.h"
//#include "osg/Group"
#include "tcCommandQueue.h"
#include "tcESMDBObject.h"
#include "tcESMSensor.h"
#include "tcGoalTracker.h"
#include "tcGoal.h"
#include "tcMissileObject.h"
#include "tcAirObject.h"
#include "tcAirfieldObject.h"
#include "tcAeroAirObject.h"
#include "tcBallisticWeapon.h"
#include "tcBallisticMissile.h"
#include "tcBallisticDBObject.h"
#include "tcGroundDBObject.h"
#include "tcGroundObject.h"
#include "tcGroundVehicleObject.h"
#include "tcGuidedBomb.h"
#include "tcRocket.h"
#include "tcOpticalDBObject.h"
#include "tcOpticalSensor.h"
#include "tcShipDBObject.h"
#include "tcSonobuoy.h"
#include "tcSonobuoyDBObject.h"
#include "tcTorpedoObject.h"
#include "tcTorpedoDBObject.h"
#include "tcHeloObject.h"
#include "tcSimpleAirDBObject.h"
#include "tcSubObject.h"
#include "tcSubDBObject.h"
#include "tcAirCM.h"
#include "tcWaterCM.h"
#include "tcCounterMeasureDBObject.h"
#include "tcBallisticMissileDBObject.h"
#include "tcStores.h"

#include "tcSonarEnvironment.h"

#include "tcLauncher.h"
#include "tcJetDBObject.h"
#include "tc3DModel.h"
#include "tcGameObjIterator.h"
#include "tcCommandObject.h"
#include "common/tcStream.h"
#include "tcMessageInterface.h"
#include "tcPositionRegistry.h"
#include "network/tcMultiplayerInterface.h"
#include "tcScenarioLogger.h"
#include "tv_types.h"
#include "tcAllianceInfo.h"
#include "tcGameStream.h"

#include "tcDamageModel.h"
#include "tcLOS.h"
#include "tcWeaponTester.h"
#include "tcEventManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace database;
using namespace scriptinterface;


/** 
* @return singleton instance 
*/
tcSimState* tcSimState::Get()
{
    static tcSimState instance;
    return &instance;
}

void tcSimState::AttachWeaponTester()
{
    weaponTester = tcWeaponTester::Get();
}


void tcSimState::ChangeHeadingToLocation(long anKey, float afLon, float afLat) 
{
    int bFound;
    tcGameObject *po;

    bFound = maPlatformState.Lookup(anKey,po);
    if (!bFound) {WTL("Err - ChangeHeadingToLocation - 1");return;}
    po->SetHeading((float)C_180OVERPI*
        (float)atan2(afLon-po->mcKin.mfLon_rad,afLat-po->mcKin.mfLat_rad));
    maPlatformState[anKey] = po;
}

/**
*
*/
void tcSimState::ChangeHeading(long anKey, float afNewHeading)
{
    int bFound;
    tcGameObject *po;

    bFound = maPlatformState.Lookup(anKey,po);
    if (!bFound) {WTL("Err - ChangeHeading - 1");return;}
    po->SetHeading(afNewHeading);
    maPlatformState[anKey] = po;
}

/**
* for scen edit mode
*/
void tcSimState::ChangeHeadingForced(long anKey, float afNewHeading) 
{
    int bFound;
    tcGameObject *po;

    bFound = maPlatformState.Lookup(anKey,po);
    if (!bFound) {WTL("Err - ChangeHeadingForced - 1");return;}
    po->SetHeading(afNewHeading);
    po->mcKin.mfHeading_rad = afNewHeading;
}

/**
* meant for scenario edit mode only
*/
void tcSimState::ChangeLocation(long anKey, float afLon_rad, float afLat_rad) 
{
    int bFound;
    tcGameObject *po;

    bFound = maPlatformState.Lookup(anKey,po);
    if (!bFound) {WTLC("Err - ChangeLocation - 1");return;}
    po->mcKin.mfLon_rad = afLon_rad;
    po->mcKin.mfLat_rad = afLat_rad;
}

/**
*
*/
void tcSimState::ChangeNormSpeed(long anKey, float afNewNormSpeed) 
{
    int bFound;
    tcGameObject *po;
    tcPlatformDBObject *pdata;

    bFound = maPlatformState.Lookup(anKey,po);
    if (!bFound) {WTL("Err - ChangeNormSpeed - 1");return;}

    pdata = dynamic_cast<tcPlatformDBObject*>(mpDatabase->GetObject(po->mnDBKey));
    if(pdata==NULL) {WTL("Err - ChangeNormSpeed - pdata");return;}

    afNewNormSpeed = (afNewNormSpeed < 0) ? 0 : afNewNormSpeed;
    afNewNormSpeed = (afNewNormSpeed > 1) ? 1 : afNewNormSpeed;
    po->SetSpeed(pdata->mfMaxSpeed_kts*afNewNormSpeed);
    maPlatformState[anKey] = po;
}

/**
*
*/
void tcSimState::RequestLaunch(long anKey,int anLauncher) 
{
    int bFound;
    tcGameObject *po;

    bFound = maPlatformState.Lookup(anKey,po);
    if (!bFound) {WTL("Err - RequestLaunch - not found");return;}
    po->SetLaunch(anLauncher,1);
    maPlatformState[anKey] = po;
}

/**
* Call after alliance country is changed to update country params for
* objects of modified alliance
*/
void tcSimState::ResyncObjAlliance()
{
    tcGameObject *obj;
    long cmappos = maPlatformState.GetStartPosition();
    int nSize = maPlatformState.GetCount();
    long nKey;

    // needs to be re-written to use the toLaunch queue
    for (int i=0;i<nSize;i++)
    {
        maPlatformState.GetNextAssoc(cmappos,nKey,obj);

        obj->SetAlliance(obj->GetAlliance());
    }
}


/**
* This method is not named well. The intent is to use this to check if 
* a target is detectable with a radar that does not exist yet. So e.g. 
* to simulate a missile seeker locking on before launch. This allows a
* detection test without creating the object. 
* Since normal use is with missiles, the sensor az is assumed to be 0.
* If this is used with a non forward looking radar, it will not work
* correctly.
* @param reference object that radar is assumed co-located with
* @param afSensorAz mount azimuth relative to reference obj heading
* @param fcID id of platform that has fire control sensor (for semi-active)
* @param fcIdx index of fire control sensor on fc platform (for semi-active)
*/
bool tcSimState::RadarCanDetect(long anSensorKey, const tcGameObject* target,
                                tcGameObject* reference, float afSensorAz,
                                long fcID, unsigned fcIdx) 
{
    float fRange_km;

    if (mcDefaultRadar.InitFromDatabase(anSensorKey) == false) 
    {
        return false;
    }
    mcDefaultRadar.SetActive(true);
    mcDefaultRadar.SetParent(reference);
	mcDefaultRadar.SetMountAz(afSensorAz);

    if (mcDefaultRadar.IsSemiactive() || mcDefaultRadar.IsCommandReceiver())
    {
        mcDefaultRadar.SetFireControlSensor(fcID, fcIdx);
    }

    return mcDefaultRadar.CanDetectTarget(target,fRange_km);
}

bool tcSimState::SensorCanDetect(long sensorKey, const tcGameObject* target,
					 tcGameObject* reference, float sensorAz, long fcID, unsigned fcIdx)
{
    if (target == 0) return false;

	tcDatabaseObject* databaseObj = mpDatabase->GetObject(sensorKey);
	if (databaseObj == 0)
	{
		wxASSERT(false);
		return false;
	}

	tcSensorState* sensor = 0;

	if (tcRadarDBObject* radarData = dynamic_cast<tcRadarDBObject*>(databaseObj))
	{
		tcRadar* radar = new tcRadar(radarData);
		if (radar->IsSemiactive() || radar->IsCommandReceiver())
		{
			radar->SetFireControlSensor(fcID, fcIdx);
		}
		sensor = radar;
	}
	else if (tcOpticalDBObject* opticalData = dynamic_cast<tcOpticalDBObject*>(databaseObj))
	{
        tcOpticalSensor* optical = new tcOpticalSensor(opticalData);
        if (optical->IsSemiactive())
        {
            optical->SetFireControlSensor(fcID, fcIdx);
        }
		sensor = optical;
	}
	else if (tcESMDBObject* esmData = dynamic_cast<tcESMDBObject*>(databaseObj))
	{
		sensor = new tcESMSensor(esmData);
	}		
	
	if (sensor != 0)
	{
		sensor->SetActive(true);
		sensor->SetParent(reference);
		sensor->SetMountAz(sensorAz);
        sensor->mnMode = SSMODE_SEEKERSEARCH; ///< something other than surveillance to avoid random detection
		
		float range_km;
        const bool useRandom = false; // never use random, since this is normally a pre-launch test
		bool canDetect = sensor->CanDetectTarget(target, range_km, useRandom);

		/* Clear fire control sensor so that delete doesn't remove a fire control track.
		** This might be better handled by not involving any real sim objects for detection tests
		** involving uninstantiated sim entities.
		*/
		sensor->SetFireControlSensor(-1, 0); 

		delete sensor;

		return canDetect;
	}
	else
	{
		fprintf(stderr, "tcSimState::SensorCanDetect - Bad sensor\n");
		return false;
	}
}


/**
*
*/
void tcSimState::DesignateTarget(long anKey, long anTargetKey) 
{
    int bFound;
    tcGameObject *po;

    bFound = maPlatformState.Lookup(anKey,po);
    if (!bFound) {WTL("Err - tcSimState::DesignateTarget - source not found");return;}
    po->DesignateTarget(anTargetKey);
}

/**
*
*/
void tcSimState::DesignateDatum(long anKey, tcPoint p) 
{
    int bFound;
    tcGameObject *po;

    bFound = maPlatformState.Lookup(anKey,po);
    if (!bFound) {WTL("Err - tcSimState::DesignateDatum - source not found");return;}

    po->DesignateDatum(p);
}

/**
*
*/
void tcSimState::DesignateLauncherDatum(long anKey, GeoPoint p, unsigned anLauncher) 
{
    int bFound;
    tcGameObject *po;

    bFound = maPlatformState.Lookup(anKey,po);
    if (!bFound) {WTL("Err - tcSimState::DesignateLauncherDatum - source not found");return;}
    tcPlatformObject* pPlatformObj = dynamic_cast<tcPlatformObject*>(po);
    if (pPlatformObj==NULL) {return;}
    pPlatformObj->DesignateLauncherDatum(p, anLauncher);
}

/**
* [DEC08] Why go through simstate for this?
*/
bool tcSimState::DesignateLauncherTarget(long anKey, long anTargetKey, unsigned anLauncher) 
{
    int bFound;
    tcGameObject *po;

    bFound = maPlatformState.Lookup(anKey,po);
    if (!bFound) {WTL("Err - tcSimState::DesignateLauncherTarget - source not found");return false;}

    tcPlatformObject* pPlatformObj = dynamic_cast<tcPlatformObject*>(po);
    if (pPlatformObj==NULL) {return false;}

    pPlatformObj->DesignateLauncherTarget(anTargetKey, anLauncher);

    tcLauncherState *pLauncherState;
    po->GetLauncherState(pLauncherState);
    if (pLauncherState->GetLauncherStatus(anLauncher) == tcLauncher::LAUNCHER_READY)
    {
        if (mpUserInfo->IsOwnAlliance(pPlatformObj->GetAlliance()) && (pPlatformObj->IsHooked()))
        {
            tcSound::Get()->PlayEffect("NoisyBeepLow");
        }
        return true;
    }
    else
    {
        return false;
    }
}

void tcSimState::EvaluateMissileDamage(tcMissileObject* missile)
{
    EvaluateWeaponDamage(missile, -5.0f, 100e3f);
}


void tcSimState::EvaluateDirectHitDamage(tcWeaponObject* weapon, tcDamageModel* damageModel)
{
    if (!weapon->IsDirectHit()) return;

    long targetId = weapon->GetDirectHitTargetId();
    tcGameObject* target = GetObject(targetId);

    Damage damage;
    damageModel->CalculateTotalDamage(weapon, target, damage);

    float damageFraction = target->ApplyAdvancedDamage(damage, weapon);

    if (damageFraction > 0) 
    {
        if (mpUserInfo->IsOwnAlliance(target->GetAlliance())) 
        {
            bool alreadyDestroyed = target->GetDamageLevel() >= 1.0f;
            if (!alreadyDestroyed) ReportDamage(target);
        }
        else if (weapon->IsOwnAlliance()) 
        {
            wxString msg = wxString::Format("Weapon (%s) hit Track %d\n", weapon->mzClass.c_str(),
                target->mnID);
			tcMessageInterface::Get()->ConsoleMessage(msg.ToStdString());
        }
        PlayEntitySoundEffect(weapon, "Explosion2");

        Vec3 explosionPoint(0, 0, 0);
        if ((target->mnID == weapon->GetIntendedTarget()) && weapon->IsDirectHit())
        {
            explosionPoint = weapon->GetImpactPoint();
        }


        target->model->AddExplosion(explosionPoint);

#ifdef _DEBUG
        if (damageFraction > 0.01)
        {
            float range_m = 1000.0f * weapon->mcKin.RangeToKmAlt(target->mcKin);
            wxString msg = wxString::Format("%s %.2f [%s] to %d (%s) %.1f m DIRECT HIT\n", weapon->mzClass.c_str(),
                damageFraction, target->GetLastDamageDescription().c_str(), 
                target->mnID, target->mzUnit.c_str(), range_m);
            tcMessageInterface::Get()->ConsoleMessage(msg.ToStdString());
        }
#endif

        if (target->IsInvulnerable())
        {
            target->ApplyRepairs(1.0f);
        }

    }

    if (logDamage)
    {
        LogWeaponDamage(target, weapon, damage, damageFraction);
    }


}

/**
* @param minAlt_m and maxAlt_m used to restrict altitude range for weapon effects so e.g. subs aren't affected by high altitude blast
*/
void tcSimState::EvaluateWeaponDamage(tcWeaponObject* weapon, float minAlt_m, float maxAlt_m)
{
#ifdef _DEBUG
    if (weapon->IsGoodDetonation())
    {
        tcMessageInterface::Get()->ConsoleMessage("GOOD DET");
    }
    else
    {
        tcMessageInterface::Get()->ConsoleMessage("DUD");
    }
#endif

    // update position of missile to precise time of detonation
    float detonationDelay_s = weapon->GetDetonationDelay();
    double lon_rad;
    double lat_rad;
    float alt_m;
    weapon->mcKin.PredictPosition(detonationDelay_s,
        lon_rad, lat_rad, alt_m);
    weapon->mcKin.mfAlt_m = alt_m;
    weapon->mcKin.mfLon_rad = lon_rad;
    weapon->mcKin.mfLat_rad = lat_rad;
    
    // update terrain height at detonation point
    weapon->mcTerrain.mfHeight_m = 
        mpMapData->GetTerrainHeight(C_180OVERPI * (float)lon_rad,
                   C_180OVERPI * (float)lat_rad, mfSimTime);

    // get damage model for this weapon
    tcDamageModel* damageModel = tcDamageModel::Get();
    const tcWeaponDamage* weaponDamageData = damageModel->GetWeaponDamageModel(weapon);

	float maxRange_m = weapon->GetDamageEffectRadius();

    if (weapon->IsGoodDetonation() && (weaponDamageData->radCharge_kg > 5e5))
    {
        ReportHighYieldDetonation(weapon);
    }

    // apply damage for direct hit first
    EvaluateDirectHitDamage(weapon, damageModel);

    // apply damage to all platforms within effect radius
    float rLat = maxRange_m * C_MTORAD;
    float rLon = rLat / cosf(weapon->mcKin.mfLat_rad);

    std::vector<long> blastPlats;

    tcRect blastRegion;
    float west = weapon->mcKin.mfLon_rad - rLon;
    float east = weapon->mcKin.mfLon_rad + rLon;
    float north = weapon->mcKin.mfLat_rad + rLat;
    float south = weapon->mcKin.mfLat_rad - rLat;
    if (west < -C_PI) west += C_TWOPI;
    if (east >= C_PI) east -= C_TWOPI;
    blastRegion.Set(west, east, south, north);

    GetPlatformsWithinRegion(blastPlats, &blastRegion);
    int nPlats = (int)blastPlats.size();

    for (int idx = 0; idx < nPlats; idx++)
    {
        tcGameObject* target = GetObject(blastPlats[idx]);

        bool eligible = target && (target->mnID != weapon->mnID) && 
            (target->mcKin.mfAlt_m >= minAlt_m) && (target->mcKin.mfAlt_m <= maxAlt_m) &&
            (target->mnID != weapon->GetDirectHitTargetId());
        bool alreadyDestroyed = target->GetDamageLevel() >= 1.0f;
        
        if (eligible)
        {
            Damage damage;
            damageModel->CalculateTotalDamage(weapon, target, damage);

            float damageFraction = target->ApplyAdvancedDamage(damage, weapon);

            if (damageFraction > 0) 
            {
                if (mpUserInfo->IsOwnAlliance(target->GetAlliance())) 
                {
                    if (!alreadyDestroyed) ReportDamage(target);
                }
                else if (weapon->IsOwnAlliance()) 
                {
                    wxString msg = wxString::Format("Weapon (%s) hit Track %d\n", weapon->mzClass.c_str(),
                        target->mnID);
                    tcMessageInterface::Get()->ConsoleMessage(msg.ToStdString());
                }
                PlayEntitySoundEffect(weapon, "Explosion2");

                Vec3 explosionPoint(0, 0, 0);
                if ((target->mnID == weapon->GetIntendedTarget()) && weapon->IsDirectHit())
                {
                    explosionPoint = weapon->GetImpactPoint();
                }


                target->model->AddExplosion(explosionPoint);

#ifdef _DEBUG
                if (damageFraction > 0.01)
                {
                    float range_m = 1000.0f * weapon->mcKin.RangeToKmAlt(target->mcKin);
                    wxString msg = wxString::Format("%s %.2f [%s] to %d (%s) %.1f m\n", weapon->mzClass.c_str(),
                        damageFraction, target->GetLastDamageDescription().c_str(), 
                        target->mnID, target->mzUnit.c_str(), range_m);
                    tcMessageInterface::Get()->ConsoleMessage(msg.ToStdString());
                }
#endif

                if (target->IsInvulnerable())
                {
                    target->ApplyRepairs(1.0f);
                }

            }

            if (logDamage)
            {
                LogWeaponDamage(target, weapon, damage, damageFraction);
            }



        }
    }


}







void tcSimState::EvaluateTorpedoDamage(tcTorpedoObject* torp)
{
    EvaluateWeaponDamage(torp, -99999.0f, 0.0f);
}

void tcSimState::EvaluateBallisticDamage(tcBallisticWeapon* ballistic)
{
    // first determine if this is a bomb or a gun burst, these are handled differently
	if (ballistic->IsGravityBomb() || ballistic->IsGunRound() || ballistic->IsSmartBomb() || ballistic->IsRocket())
    {
        EvaluateWeaponDamage(ballistic, -5.0f, 100e3f); // handle bombs and gun rounds with general case
        return;
    }

    // gun burst "autocannon" model
    // calculate the target pos in local coords to gun burst
    tcGameObject* target = GetObject(ballistic->GetIntendedTarget());
    if (target == 0) return;

    Vec3 pos;
    Vec3 vel;
    ballistic->GetRelativeStateLocal(target, pos, vel);

    // check that forward/backward error is within tolerance
    const float maxAlongTrackError_m = 50.0f;
    if (fabsf(pos.z) > maxAlongTrackError_m) return;
    
    // check that target is within spread

    float crossTrackError_m = sqrtf(pos.x*pos.x + pos.y*pos.y);

    float distanceTraveled_m = ballistic->GetDistanceTraveled();
    float angleError_rad = ballistic->GetAngleErrorRad(); // +/- this error
    float spread_m = distanceTraveled_m * angleError_rad; // small angle approx

    const float targetWidthGuess_m = 20.0f; // assume target is big at this stage
    if (crossTrackError_m > (4.0f*spread_m + targetWidthGuess_m)) return; // miss

    Vec3 pos_eun;
    Vec3 vel_eun;
    target->GetRelativeStateWorld(ballistic, pos_eun, vel_eun);

	unsigned int burstCount = ballistic->GetBurstCount();
	unsigned int hits = 0;

	if (burstCount <= 50) // simulate each round
	{
		hits = target->CalculateRandomHits(pos_eun, vel_eun, distanceTraveled_m, angleError_rad, burstCount);
	}
	else // scale damage based on 50 rounds
	{
		hits = unsigned int(0.5f + float(burstCount) * 
			0.02f * float(target->CalculateRandomHits(pos_eun, vel_eun, distanceTraveled_m, angleError_rad, 50)));
	}

    //pos_eun = pos_eun / pos_eun.Length();
    //float targetCrossSection_m2 = target->CalculateCrossSectionDir(pos_eun);
    //
    //// calculate fraction of target within spread assuming square cross-section
    //float targetHalfWidth_m = sqrtf(targetCrossSection_m2); // half width of tgt assuming rectangular cross-section

    //if (spread_m < (crossTrackError_m - targetHalfWidth_m)) return; // miss

    //float exposedFraction = 1.0f;
    //if (spread_m > (crossTrackError_m + targetHalfWidth_m))
    //{
    //    exposedFraction = 1.0f;
    //}
    //else
    //{
    //    exposedFraction = 0.5f + 0.5f*((spread_m - crossTrackError_m) / targetHalfWidth_m);
    //}

    //float avg_hits = float(ballistic->GetBurstCount()) * exposedFraction * targetCrossSection_m2 / (4 * spread_m * spread_m);

    //unsigned int hits = Poisson(avg_hits);

    if (hits == 0) return;

    // model as 1 kinetic impact + remainder as fragments

    tcDamageModel* damageModel = tcDamageModel::Get();
    const tcWeaponDamage* weaponDamageData = damageModel->GetWeaponDamageModel(ballistic);


    ballistic->SetDirectHitTargetId(target->mnID);
    float speedRel_mps2 = vel.x*vel.x + vel.y*vel.y + vel.z*vel.z;

    Damage damage;
    damage.Clear();
    damage.isPenetration = true;
    damage.kinetic_J = 0.5*ballistic->GetMassKg()*speedRel_mps2;

    if (hits > 1)
    {
        damage.fragEnergy_J = damage.kinetic_J;
        damage.fragHits = hits - 1;
    }

    if (randf() < weaponDamageData->probDetonate)
    {
        damage.explosive_kg = float(hits)*weaponDamageData->blastCharge_kg;
    }

    float damageFraction = target->ApplyAdvancedDamage(damage, ballistic);

    if (damageFraction > 0) 
    {
        if (mpUserInfo->IsOwnAlliance(target->GetAlliance())) 
        {
            bool alreadyDestroyed = target->GetDamageLevel() >= 1.0f;
            if (!alreadyDestroyed) ReportDamage(target);
        }
        else if (ballistic->IsOwnAlliance()) 
        {
            wxString msg = wxString::Format("Weapon (%s) hit Track %d\n", ballistic->mzClass.c_str(),
                target->mnID);
            tcMessageInterface::Get()->ConsoleMessage(msg.ToStdString());
        }
        PlayEntitySoundEffect(ballistic, "Explosion2");

        Vec3 explosionPoint(0, 0, 0);
        target->model->AddExplosion(explosionPoint);

#ifdef _DEBUG
        float range_m = 1000.0f * ballistic->mcKin.RangeToKmAlt(target->mcKin);
        wxString msg = wxString::Format("%s %.2f [%s] to %d (%s) %.1f m\n", ballistic->mzClass.c_str(),
            damageFraction, target->GetLastDamageDescription().c_str(), 
            target->mnID, target->mzUnit.c_str(), range_m);
        tcMessageInterface::Get()->ConsoleMessage(msg.ToStdString());
#endif

        if (target->IsInvulnerable())
        {
            target->ApplyRepairs(1.0f);
        }

    }


}




/**
*
*/
void tcSimState::Update() 
{
    tcGameObject *obj;
    long cmappos = maPlatformState.GetStartPosition();
    int nSize = maPlatformState.GetCount();
    long nKey,nNewKey;
    unsigned nLauncher;
    static unsigned int updateCounter = 0;


	if (multiplayerMode != MM_CLIENT)
	{
		UpdateObjTerrainInfo();
	}
    

    bool usePositionRegistry = (positionRegistry != 0);

    // needs to be re-written to use the toLaunch queue
    for (int i=0;i<nSize;i++) 
    {
        maPlatformState.GetNextAssoc(cmappos,nKey,obj);

        wxASSERT((obj->mcKin.mfLon_rad >= -C_PI) && (obj->mcKin.mfLon_rad < C_PI));
        wxASSERT((obj->mcKin.mfLat_rad >= -C_PIOVER2) && (obj->mcKin.mfLat_rad <= C_PIOVER2));

        obj->Update(mfSimTime);

        if (usePositionRegistry) 
        {
            positionRegistry->UpdatePosition(obj->mnID, obj->mcKin.mfLon_rad, obj->mcKin.mfLat_rad);
        }
    }

    // iterate through again for launched objects, after we've updated all objects first
    cmappos = maPlatformState.GetStartPosition();
    for (int i=0;i<nSize;i++) 
    {
        maPlatformState.GetNextAssoc(cmappos,nKey,obj);

        bool isPlatformObject = obj->IsPlatformObject();
        //tcPlatformObject *pPlatformObj = dynamic_cast<tcPlatformObject*>(obj);

        if (isPlatformObject && (multiplayerMode != MM_CLIENT))
        {
            obj->Launch(nNewKey, nLauncher); 
            if (nNewKey != NULL_INDEX) {AddLaunchedPlatform(nNewKey, obj, nLauncher);}
        }

    }




    if (multiplayerMode != MM_CLIENT)
    {
        UpdateWeaponHits2();
        UpdateLandings(mfSimTime);
        RemoveDestroyedObjects();

        weaponTester->Update(); // relevant in dev mode only
    }
    UpdateLaunch();
    mcSensorMap.Update(mfSimTime);

    if (multiplayerMode != MM_CLIENT)
    {
        //UpdateObjFormations(mfSimTime);
        //UpdateObjEngagements(mfSimTime); // FC engagement list and auto launch
    }
    
    if ((mfSimTime-mfLastTileAgeOut) > 25.4f) 
    {
        mfLastTileAgeOut = mfSimTime;
        mpMapData->AgeOutTiles(mfSimTime);
        
        tcSonarEnvironment::Get()->Update(mfSimTime);
        tcLOS::Get()->Update(mfSimTime); // age out old LOS paths
    }

    if (multiplayerMode != MM_CLIENT)
    {
        goalTracker->Update(mfSimTime);
    }
}



/**
* Used for a missile that is guided with a sensor to a target. The
* assumption is that the intended target is the only possible target
* that can be hit. This saves time by not looking for nearby accidental 
* targets.
*/
void tcSimState::EvaluateGuidedMissileHit(tcMissileObject* missile, tcGameObject* target)
{
	//float range_m = 1000.0f*missile->mcKin.RangeToKmAlt(target->mcKin);
	//float fFactor = 0.01f*(missile->mcKin.mfSpeed_kts + target->mcKin.mfSpeed_kts + 2000.0f);

	//if (range_m >= fFactor) return; // too far away, no damage

    float dx, dy, dz, dt;
	Vec3 collisionPoint;
    float trueRange2;
    float dist_m;

	// first check for impact
	if (target->CalculateCollisionPoint(missile, collisionPoint, dt, dist_m))
	{
        if (dt > 0.05) return; // defer until future time step

		collisionPoint = target->ConvertModelCoordinatesToWorld(collisionPoint);
		dx = collisionPoint.x;
		dy = collisionPoint.y;
		dz = collisionPoint.z;
		trueRange2 = 0;
	}
	else // if no impact, check for sufficient proximity to target
	{
		dt = target->mcKin.CalculateCollisionPoint(missile->mcKin, dx, dy, dz);
		if (dt > 0.05) return; // defer until future time step
		trueRange2 = dx*dx + dy*dy + 0.5*dz*dz;
	}

	if (trueRange2 < 144.0f) // 12.0 m range
	{
		bool alreadyDestroyed = target->GetDamageLevel() >= 1.0f;
		float fDamage = missile->mpDBObject->mfDamage;
		float damageFraction = GetFractionalDamage(fDamage, target);

        missile->ApplyGeneralDamage(1.0f, 0); // missile destroys itself on impact
        
		if (damageFraction > 0)
		{
            target->ApplyGeneralDamage(damageFraction, missile);

			if (mpUserInfo->IsOwnAlliance(target->GetAlliance())) 
			{
                if (!alreadyDestroyed) ReportDamage(target);
			}
			else if (missile->IsOwnAlliance()) 
			{
				wxString msg = wxString::Format("Missile (%s) hit Track %d\n", missile->mzClass.c_str(),
					target->mnID);
				tcMessageInterface::Get()->ConsoleMessage(msg.ToStdString());
			}
			PlayEntitySoundEffect(missile, "Explosion2");

			target->model->AddExplosion(Vec3(dx, dy, dz));
		}

#ifdef _DEBUG
        wxString s = wxString::Format("weapon %d hit target %d, range^2: %3.1f m, dmg: %3.1f %%, time %.1f s",
			missile->mnID, target->mnID, trueRange2, 100.0f*damageFraction, mfSimTime);
        WTL(s.c_str());
        std::cout << s.c_str();
		fprintf(stdout,"   collision relative time: %f, dx:%f dy:%f dz:%f\n",
			dt, dx, dy, dz);
#endif
	}

}

/**
* Used for a torpedo that is guided with a sensor to a target. The
* assumption is that the intended target is the only possible target
* that can be hit. This saves time by not looking for nearby accidental 
* targets.
*/
void tcSimState::EvaluateTorpedoHit(tcTorpedoObject* torp, tcGameObject* target)
{
	float range_m = 1000.0f * torp->mcKin.RangeToKmAlt(target->mcKin);

	if ((range_m > 200.0) || (range_m >= 0.6*target->GetSpan()))
	{
		return; // too far away, no damage
	}


    float dx, dy, dz, dt;
	Vec3 collisionPoint;
    float trueRange2;
    float dist_m;

	// first check for impact
	if (target->CalculateCollisionPoint(torp, collisionPoint, dt, dist_m))
	{
		collisionPoint = target->ConvertModelCoordinatesToWorld(collisionPoint);
		dx = collisionPoint.x;
		dy = collisionPoint.y;
		dz = collisionPoint.z;
		trueRange2 = 0;
	}
	else // if no impact, check for sufficient proximity to target
	{
		dt = target->mcKin.CalculateCollisionPoint(torp->mcKin, dx, dy, dz);
		if (dt > 0.1) return; // defer until future time step
		trueRange2 = dx*dx + dy*dy + 0.5*dz*dz;
	}

	
	if (trueRange2 < 144.0f) // 12.0 m "range", dz not counted as heavily
	{
		bool alreadyDestroyed = target->GetDamageLevel() >= 1.0f;
		float fDamage = torp->mpDBObject->mfDamage;
		float damageFraction = GetFractionalDamage(fDamage, target);

		torp->ApplyGeneralDamage(1.0f, 0);
        
		if (damageFraction > 0)
		{
            target->ApplyGeneralDamage(damageFraction, torp);

			if (mpUserInfo->IsOwnAlliance(target->GetAlliance())) 
			{
                if (!alreadyDestroyed) ReportDamage(target);
			}
			else if (torp->IsOwnAlliance())
			{
				wxString msg = wxString::Format("Torpedo (%s) hit track %d\n", torp->mzClass.c_str(),
					target->mnID);
				tcMessageInterface::Get()->ConsoleMessage(msg.ToStdString());
			}
			PlayEntitySoundEffect(torp, "Explosion2");
		}

		target->model->AddExplosion(Vec3(dx, dy, dz));

#ifdef _DEBUG
        wxString s = wxString::Format("torpedo %d hit target %d, range^2: %3.1f m, dmg: %3.1f %%, time %.1f s",
			torp->mnID, target->mnID, trueRange2, 100.0f*damageFraction, mfSimTime);
        WTL(s.c_str());
        std::cout << s.c_str();
		fprintf(stdout,"   collision relative time: %f, dx:%f dy:%f dz:%f\n",
			dt, dx, dy, dz);
#endif
	}

}

/**
* Used for a weapon used against fixed land targets. The region near
* the collision point is searched for nearby targets. Damage is applied
* to all targets that are close enough.
*/
void tcSimState::EvaluateImpactWeaponHit(tcWeaponObject* weapon)
{
	wxASSERT(weapon);

	if (!weapon->IsDetonated()) return;

	float blastDelay = weapon->GetDetonationDelay();
	if (blastDelay > 0.033) return;

	if (blastDelay > 0)
	{
		double lon_rad;
		double lat_rad;
		float alt_m;

		weapon->mcKin.PredictPosition(blastDelay,
			lon_rad, lat_rad, alt_m);

		weapon->mcKin.mfAlt_m = alt_m;
		weapon->mcKin.mfLon_rad = lon_rad;
		weapon->mcKin.mfLat_rad = lat_rad;
	}

	float effectRadius_m = weapon->GetDamageEffectRadius();
	float rLat = effectRadius_m * C_MTORAD;
	float rLon = rLat / cosf(weapon->mcKin.mfLat_rad);

    std::vector<long> blastPlats;

	tcRect blastRegion;
	float west = weapon->mcKin.mfLon_rad - rLon;
	float east = weapon->mcKin.mfLon_rad + rLon;
	float north = weapon->mcKin.mfLat_rad + rLat;
	float south = weapon->mcKin.mfLat_rad - rLat;
	if (west < -C_PI) west += C_TWOPI;
	if (east >= C_PI) east -= C_TWOPI;
	blastRegion.Set(west, east, south, north);

    GetPlatformsWithinRegion(blastPlats, &blastRegion);
    int nPlats = (int)blastPlats.size();
	float fDamage = weapon->GetDamage();

	for (int idx = 0; idx < nPlats; idx++)
	{
		tcGameObject* target = GetObject(blastPlats[idx]);
        
        bool eligible = target && (target->mnID != weapon->mnID) && (target->mcKin.mfAlt_m >= -5.0f);

		if (eligible)
		{
			float range_m = 1000.0f * target->mcKin.RangeToKmAlt(weapon->mcKin);
			float damage_range_m = 0.6f * target->GetSpan();
			if (range_m <= damage_range_m)
			{
				float damageFraction = GetFractionalDamage(fDamage, target);
                bool alreadyDestroyed = target->GetDamageLevel() >= 1.0f;

				if (damageFraction > 0)
				{
                    target->ApplyGeneralDamage(damageFraction, weapon);
                    
#ifdef _DEBUG
					tcString s;
					s.Format("weapon (impact) %d hit track %d, range: %3.1f m, time %.1f s",
						weapon->mnID, target->mnID, range_m, mfSimTime);
					WTL(s.GetBuffer());
#endif

					if (mpUserInfo->IsOwnAlliance(target->GetAlliance())) 
					{
						if (!alreadyDestroyed) ReportDamage(target);
					}
					else if (weapon->IsOwnAlliance())
					{
						wxString msg = wxString::Format("Weapon (%s) hit track %d\n", weapon->mzClass.c_str(),
							target->mnID);
						tcMessageInterface::Get()->ConsoleMessage(msg.ToStdString());
					}
					PlayEntitySoundEffect(weapon, "Explosion2");

					// use a random explosion point for display purposes only
					float dx = randfc(20.0f);
					float dy = randfc(20.0f);
					float dz = randf(10.0f);
					target->model->AddExplosion(Vec3(dx, dy, dz));
				}
				else
				{
#ifdef _DEBUG
					tcString s;
					s.Format("weapon (DUD) %d target %d, range: %3.1f m, time %.1f s",
						weapon->mnID, target->mnID, range_m, mfSimTime);
					WTL(s.GetBuffer());
#endif
				}

			}
			else
			{
#ifdef _DEBUG
				tcString s;
				s.Format("weapon (impact) %d missed target %d, range: %3.1f m, time %.1f s",
					weapon->mnID, target->mnID, range_m, mfSimTime);
				WTL(s.GetBuffer());
#endif
			}
		}
	}


    weapon->ApplyGeneralDamage(1.0, 0);
}


/**
* Temporary special case for point defense ballistic weaps
*/
void tcSimState::EvaluatePointDefenseWeaponHit(tcWeaponObject* weapon)
{
	wxASSERT(weapon);

    tcGameObject* target = GetObject(weapon->GetIntendedTarget());
    if (target == 0) return;


    // return if weapon is still too far away
    const float min_distance_km = 1.0f;
    if (weapon->RangeTo(*target) > min_distance_km) return;

    float dist_m;
    float trueRange2, dx, dy, dz;
    // first check for direct hit (collision test)
    Vec3 impactPoint(0, 0, 0);
    float impactTime(0);
    bool directHit = target->CalculateCollisionPoint(weapon, impactPoint, impactTime, dist_m);

    if (!directHit)
    {
        tcKinematics trailingKin = weapon->mcKin;
        trailingKin.Extrapolate(-1.0f); // assume gun burst is 1 second in duration

        float dx_head, dy_head, dz_head, tclosest_head;
        tclosest_head = target->mcKin.CalculateCollisionPoint(weapon->mcKin, dx_head, dy_head, dz_head);

        float dx_tail, dy_tail, dz_tail, tclosest_tail;
        tclosest_tail = target->mcKin.CalculateCollisionPoint(weapon->mcKin, dx_tail, dy_tail, dz_tail);


        if ((tclosest_head > 0.03) && (tclosest_tail > 0.03)) return; // defer until future time step

        float trueRange2_head = dx_head*dx_head + dy_head*dy_head + dz_head*dz_head;
        float trueRange2_tail = dx_tail*dx_tail + dy_tail*dy_tail + dz_tail*dz_tail;

        
        if (trueRange2_head < trueRange2_tail)
        {
            trueRange2 = trueRange2_head;
            dx = dx_head;
            dy = dy_head;
            dz = dz_head;
        }
        else
        {
            trueRange2 = trueRange2_tail;
            dx = dx_tail;
            dy = dy_tail;
            dz = dz_tail;
        }

        //trueRange2 = 1e6; // temporary!
    }
    else
    {
        dx = impactPoint.x;
        dy = impactPoint.y;
        dz = impactPoint.z;

        trueRange2 = (impactPoint.y >= 0) ? 0 : 1e6; // don't allow hits below water
    }

	if (trueRange2 < 1600.0f) // 40.0 m range
	{
        float fDamage = weapon->GetDamage();
		float damageFraction = GetFractionalDamage(fDamage, target);

        if (randf() < 0.3f) damageFraction = 0; // additional miss chance

        bool alreadyDestroyed = target->GetDamageLevel() >= 1.0f;

        weapon->ApplyGeneralDamage(1.0f, 0);

		if (damageFraction > 0)
		{
            target->ApplyGeneralDamage(damageFraction, weapon);

			if (mpUserInfo->IsOwnAlliance(target->GetAlliance())) 
			{
                if (!alreadyDestroyed) ReportDamage(target);
			}

			PlayEntitySoundEffect(weapon, "Explosion2");
		}

		target->model->AddExplosion(Vec3(dx, dy, dz));
    }

}



/**
* JUL2004 This was modified to use EvaluateGuidedMissileHit and
* EvaluateImpactMissileHit.
*/
void tcSimState::UpdateWeaponHits() 
{
    wxASSERT(false); // obsolete
    return;
#if 0
    long aKeyList[512];
    int nCount;
    tsGuidanceParameters gp;

    nCount = GetAllWeaponObjects(aKeyList,512);
    for(int k=0;k<nCount;k++) 
    {
        tcGameObject* obj = GetObject(aKeyList[k]);

        if (tcMissileObject* missileObj = dynamic_cast<tcMissileObject*>(obj))
        {
            bool bTerminal = (missileObj->GetGuidanceParameters(gp) != 0);
			if (bTerminal && (gp.mnTargetID != -1))
			{
				if ((gp.mfInterceptTime < 10.0))
				{
					if (tcGameObject* target = GetObject(gp.mnTargetID))
					{
						EvaluateGuidedMissileHit(missileObj, target);
					}
				}
			}
        }
        else if (tcTorpedoObject* torp = dynamic_cast<tcTorpedoObject*>(obj))
        {
            bool bTerminal = (torp->GetGuidanceParameters(gp) != 0);
			if (bTerminal && (gp.mnTargetID != -1))
			{
                if (gp.mfInterceptTime < 10.0)
				{
					if (tcGameObject* target = GetObject(gp.mnTargetID))
					{
						EvaluateTorpedoHit(torp, target);
					}
				}
			}
        }
		else if (tcWeaponObject* weapon = dynamic_cast<tcWeaponObject*>(obj))
		{
            if (weapon->IsGroundFused())
            {
                bool evaluate = (weapon->mcKin.mfAlt_m < weapon->mcTerrain.mfHeight_m + 200.0) || 
                    (weapon->mcKin.mfAlt_m < 100.0);
                if (evaluate) EvaluateImpactWeaponHit(weapon);
            }
            else
            {
                EvaluatePointDefenseWeaponHit(weapon);
            }
		}
    }
#endif
}





/**
* MAY2008 This version for advance weapon damage model
*/
void tcSimState::UpdateWeaponHits2() 
{
    long aKeyList[512];
    int nCount;
    const float maxDetonationDelay_s = 0.05f;

    nCount = GetAllWeaponObjects(aKeyList,512);
    for(int k=0; k<nCount; k++) 
    {
        tcGameObject* obj = GetObject(aKeyList[k]);

        if (tcWeaponObject* weapon = dynamic_cast<tcWeaponObject*>(obj))
        {
            if (weapon->IsDetonated() && (weapon->GetDetonationDelay() < maxDetonationDelay_s))
            {
                weapon->ApplyGeneralDamage(1.0f, 0); // weapon destroys itself

                if (tcMissileObject* missileObj = dynamic_cast<tcMissileObject*>(obj))
                {
                    EvaluateMissileDamage(missileObj);
                }
                else if (tcTorpedoObject* torp = dynamic_cast<tcTorpedoObject*>(obj))
                {
                    EvaluateTorpedoDamage(torp);
                }
                else if (tcBallisticWeapon* ballistic = dynamic_cast<tcBallisticWeapon*>(obj))
                {
                    EvaluateBallisticDamage(ballistic);
                }
                else
                {
                    EvaluateWeaponDamage(weapon, -20.0f, 100e3f);
                }
            }
        }
    }


}









/**
* normalize to toughness if a platform obj, otherwise return afDamage.
* This effectively sets all missile toughness to 1.0
*/
float tcSimState::GetFractionalDamage(float afDamage, tcGameObject *apGameObj) 
{
    float damageEffectiveness = randf(1.0f);

    if (damageEffectiveness < 0.1f) return 0; // 10% of weapons duds for now!

    afDamage = afDamage * damageEffectiveness; // scale damage by effectiveness

	// allow small chance of quadruple damage critical hit
	if (damageEffectiveness > 0.98f)
	{
		afDamage *= 4.0f;
	}


    tcPlatformObject *pPlatformObj = dynamic_cast<tcPlatformObject*>(apGameObj);
    if (pPlatformObj != NULL) 
    {
        return afDamage / pPlatformObj->mpDBObject->mfToughness;
    }

    return afDamage;
}


double tcSimState::GetMultiplayerTimeLag() const
{
    return multiplayerTimeLag_s;
}

/**
*
*/
void tcSimState::UpdateObjTerrainInfo() 
{
    tcGameObject *pobj;
    long cmappos = maPlatformState.GetStartPosition();
    long nSize = maPlatformState.GetCount();
    long nKey;
    tcKinematics *pKin;
    tcTerrainInfo *terrainInfo;

    const float updateDistance_rad = 50.0 * C_MTORAD;
	const float lookAheadUpdateSpeed_kts = 200.0f; // speed threshold for updating lookAheadHeight_m

    for (long i=0;i<nSize;i++) 
    {
        maPlatformState.GetNextAssoc(cmappos,nKey,pobj);
        pKin = &pobj->mcKin;
        terrainInfo = &pobj->mcTerrain;
        if ( (pKin->mfAlt_m < 30e3) &&
             ((fabs(pKin->mfLat_rad - terrainInfo->mfLatDatum) > updateDistance_rad)|| 
             (fabs(pKin->mfLon_rad - terrainInfo->mfLonDatum) > updateDistance_rad))
           )
        { // about 10 meters
            terrainInfo->mfHeight_m = 
                mpMapData->GetTerrainHeight(C_180OVERPI*(float)pKin->mfLon_rad,
                C_180OVERPI*(float)pKin->mfLat_rad,mfSimTime);
            terrainInfo->mfLonDatum = (float)pKin->mfLon_rad;
            terrainInfo->mfLatDatum = (float)pKin->mfLat_rad;

			if (pobj->mcKin.mfSpeed_kts > lookAheadUpdateSpeed_kts)
			{
				double lon_rad, lat_rad;
				float alt_m;
				pKin->PredictPosition(3.0f, lon_rad, lat_rad, alt_m);
				terrainInfo->lookAheadHeight_m = mpMapData->GetTerrainHeight(C_180OVERPI * (float)lon_rad,
                   C_180OVERPI * (float)lat_rad, mfSimTime);
			}
			else
			{
				terrainInfo->lookAheadHeight_m = terrainInfo->mfHeight_m;
			}
        }
    }
}



bool tcSimState::IsLauncherReady(long anKey, unsigned anLauncher) 
{
    int bFound;
    tcGameObject *po;

    bFound = maPlatformState.Lookup(anKey,po);
    if (!bFound) {WTL("Err - IsLauncherReady - 1");return false;}
    return IsLauncherReady(po, anLauncher);
}

bool tcSimState::IsLauncherReady(tcGameObject *apGameObj, unsigned anLauncher) 
{
    tcLauncherState *pLauncherState;
    
    bool bReadyForLaunch;

    if (apGameObj == NULL) {return false;}

    apGameObj->GetLauncherState(pLauncherState);
    if (pLauncherState == NULL) {return false;}

    const tcLauncher* pLauncher = pLauncherState->GetLauncher(anLauncher);
    if (pLauncher == 0) return false;

    int nLaunchCount = pLauncher->mnUncommitted;

    // determine if launcher is ready for launch
    bool bLauncherActive = (nLaunchCount > 0);
    bool bDatumActive = (pLauncher->msDatum.mfLat_rad!=0)&&(pLauncher->msDatum.mfLon_rad!=0);
    bool bTrackActive = (pLauncher->mnTargetID != NULL_INDEX);

    if (pLauncher->meLaunchMode == AUTO) 
    {
        bReadyForLaunch = bLauncherActive;
    }
    else if (pLauncher->meLaunchMode == DATUM_ONLY) 
    {
        bReadyForLaunch = bLauncherActive && bDatumActive;
    }
    else if (pLauncher->meLaunchMode == SEEKER_TRACK) 
    {
        bReadyForLaunch = bLauncherActive && bTrackActive;
    }
    else {
        bReadyForLaunch = false;
    }
    return bReadyForLaunch;
}

bool tcSimState::IsMultiplayerActive() const
{
	return (multiplayerMode != MM_OFF);
}

bool tcSimState::IsMultiplayerClient() const
{
	return (multiplayerMode == MM_CLIENT);
}

bool tcSimState::IsMultiplayerGameStarted() const
{
    return isMultiplayerGameStarted;
}

bool tcSimState::IsMultiplayerServer() const
{
	return (multiplayerMode == MM_SERVER);
}




/**
* In single player mode, play sound effect if entity is owned by user.
* In multiplayer server mode, send sound effect message to player
*/
void tcSimState::PlayEntitySoundEffect(tcGameObject* obj, const std::string& effect)
{
    wxASSERT(obj != 0);
	using network::tcMultiplayerInterface;

	if (multiplayerMode == MM_OFF)
	{
        if ((mpUserInfo->IsOwnAlliance(obj->GetAlliance()))  && (mpPythonInterface->IsHooked(obj->mnID)))
		{
			tcSound::Get()->PlayEffect(effect);
		}
	}
	else if (multiplayerMode == MM_SERVER)
	{
		const std::string& controller = obj->GetController();
		if (controller.size())
		{
			tcMultiplayerInterface::Get()->SendSoundEffect(controller, effect, obj->mnID);
		}
	}
	else
	{
		wxASSERT(false);
	}
}

/**
* Iterate through all game objects and pre-load any database entries that haven't been loaded (stores)
*/
void tcSimState::PreloadScenarioDatabase()
{
    long cmappos = maPlatformState.GetStartPosition();
    int nSize = maPlatformState.GetCount();
    

    for (int i=0;i<nSize;i++) 
    {
        tcGameObject* obj = 0;
        long nKey = -1;

        maPlatformState.GetNextAssoc(cmappos, nKey, obj);

        if (tcPlatformObject* platform = dynamic_cast<tcPlatformObject*>(obj))
        {
            size_t nLaunchers = platform->GetLauncherCount();
            for (size_t n=0; n<nLaunchers; n++)
            {
                tcLauncher* launcher = platform->GetLauncher(n);
                wxASSERT(launcher != 0);
                tcDatabaseObject* data = launcher->GetChildDatabaseObject();
                PreloadAssociatedRecords(data);
            }

            size_t nMagazines = platform->GetMagazineCount();
            for (size_t n=0; n<nMagazines; n++)
            {
                tcStores* stores = platform->GetMagazine(n);
                size_t nItems = stores->GetNumberItemTypes();
                for (size_t k=0; k<nItems; k++)
                {
                    std::string itemName = stores->GetItemName(k);
                    tcDatabaseObject* data = mpDatabase->GetObject(itemName);
                    PreloadAssociatedRecords(data);
                }
            }
        }
        
    }
}

void tcSimState::PreloadAssociatedRecords(tcDatabaseObject* obj)
{
    if (tcMissileDBObject* missileData = dynamic_cast<tcMissileDBObject*>(obj))
    {
        tcDatabaseObject* payloadData = mpDatabase->GetObject(missileData->payloadClass);
        PreloadAssociatedRecords(payloadData);

        tcDatabaseObject* sensorData =  mpDatabase->GetObject(missileData->maSensorClass.c_str());
    }
    else if (tcTorpedoDBObject* torpedoData = dynamic_cast<tcTorpedoDBObject*>(obj))
    {
        tcDatabaseObject* sensorData =  mpDatabase->GetObject(torpedoData->sonarClass);
    }
    else if (tcBallisticDBObject* ballisticData = dynamic_cast<tcBallisticDBObject*>(obj))
    {
        tcDatabaseObject* sensorData =  mpDatabase->GetObject(ballisticData->sensorClass);
    }
}

/**
*
*/
int tcSimState::GetAllWeaponObjects(long *apKeyList,int anMaxLength) 
{
    tcGameObject *pobj;
    long cmappos = maPlatformState.GetStartPosition();
    long nSize = maPlatformState.GetCount();
    long nKey;
    int nListIndex=0;

    for (long i=0;(i<nSize)&&(nListIndex<anMaxLength);i++) 
    {
        maPlatformState.GetNextAssoc(cmappos,nKey,pobj);
        if (dynamic_cast<tcWeaponObject*>(pobj))
        {
            apKeyList[nListIndex++] = nKey;
        }
    }
    return nListIndex;
}

void tcSimState::GetDateTime(tcDateTime& dt) const
{
    dt = dateTime;
}

const tcDateTime& tcSimState::GetDateTime() const
{
    return dateTime;
}


/**
*
*/
void tcSimState::RemoveDestroyedObjects() 
{
    tcGameObject *obj;
    long cmappos = maPlatformState.GetStartPosition();
    long nSize = maPlatformState.GetCount();
    long nKey;

    for (long i=0; i<nSize; i++) 
    {
        maPlatformState.GetNextAssoc(cmappos, nKey, obj);
        if (obj->IsDestroyed()) 
        {
            DeleteObject(nKey);
        }
    }
}

/**
* Use this method to rename without corrupting name-based registry
*/
void tcSimState::RenameObject(tcGameObject* obj, const std::string& s)
{
	wxASSERT(obj);
	if (obj == 0) return;

    std::string oldName(obj->mzUnit.c_str());
	UnregisterPlatform(obj);

	obj->mzUnit.operator=(s.c_str());

	RegisterPlatform(obj);

    tcGoalTracker* goalTracker = tcGoalTracker::Get();
    goalTracker->RenameTarget(oldName, s);
}

/**
* Writes out damage report message
*/
void tcSimState::ReportDamage(tcGameObject* obj)
{
    if (tcWeaponObject* weapon = dynamic_cast<tcWeaponObject*>(obj))
    {
        return;
    }

	PlayEntitySoundEffect(obj, "Implosion");

    std::string damageString = "reports light damage [";

    float damageLevel = obj->GetDamageLevel();

    if (damageLevel >= 1.0) damageString = "destroyed [";
    else if (damageLevel >= 0.5) damageString = "reports heavy damage [";
    else if (damageLevel >= 0.2) damageString = "reports moderate damage [";

    damageString += obj->GetLastDamageDescription(); // add damage type code
    damageString += "]";

    wxString s = wxString::Format("%s: %s (%s) %s\n", 
        dateTime.asString(), obj->mzUnit.c_str(), obj->mzClass.c_str(), 
        damageString.c_str());

    tcMessageInterface::Get()->ChannelMessage("Damage", s.ToStdString(), obj->GetAlliance());
}

/**
* Report nuclear detonation to players (instantaneous report, very efficient intel!)
*/
void tcSimState::ReportHighYieldDetonation(tcWeaponObject* weapon)
{
    wxString s;

    s.Printf("FLASH3 %2.5f %2.5f High yield detonation detected",
        C_180OVERPI*weapon->mcKin.mfLat_rad, C_180OVERPI*weapon->mcKin.mfLon_rad);

    tcMessageInterface::Get()->ChannelMessage("MapAlert", s.ToStdString(), 0);
}

/**
*
*/
void tcSimState::ProcessRadarDetection(tcGameObject *apRadarPlat,tcGameObject *apTarget,
                                       tcRadar *apRadarSS) 
{
    wxASSERT(false); // obsolete
#if 0
    float fRange_km;


    if (apRadarPlat->GetAlliance() == apTarget->GetAlliance()) {return;}

    bool bDetected = apRadarSS->CanDetectTarget(apTarget,fRange_km); 
    if (!bDetected) {return;}

    tcSensorReport *pReport;
    tcSensorMapTrack *pSMTrack;
    bool bAccept = mcSensorMap.UpdateActiveReport(pReport,apRadarPlat->mnID,apTarget->mnID,
        pSMTrack,apRadarPlat->GetAlliance());

    if (bAccept) 
    {
        pReport->latEstimate_rad = (float)apTarget->mcKin.mfLat_rad;
        pReport->lonEstimate_rad = (float)apTarget->mcKin.mfLon_rad;
        pReport->mfSpeed_kts = apTarget->mcKin.mfSpeed_kts*cosf(apTarget->mcKin.mfClimbAngle_rad);
        pReport->mfHeading_rad = apTarget->mcKin.mfHeading_rad;
        pReport->timeStamp = mfSimTime;
        pReport->platformID = apRadarPlat->mnID;
        pReport->sensorID = apRadarSS->mpDBObj->mnKey;
        pReport->mnTrackID = apTarget->mnID;
        bool bNewReport = pReport->IsNew();
        bool bNewDetection = pSMTrack->IsNew();
        if (bNewReport) {pReport->startTime = mfSimTime;} // new detection
        double fTrackLife = pReport->timeStamp - pReport->startTime;
        if (fTrackLife >= 16.0) 
        {
            pReport->validFlags = TRACK_SPEED_VALID | TRACK_HEADING_VALID;
        }
        else 
        {
            pReport->validFlags = 0;
        }
        if ((!pReport->mbClassified)&&(fTrackLife > 10.0)) 
        {
            tcDatabaseObject *pTargetData;
            mpDatabase->GetObject(apTarget->mnDBKey,pTargetData); // watch out for bad call here
            UINT16 nClassification = pTargetData->mnType;
            tcAllianceInfo::Affiliation eAffil = tcAllianceInfo::UNKNOWN;
            if (nClassification & PTYPE_MISSILE) {eAffil = tcAllianceInfo::HOSTILE;}
            pSMTrack->UpdateClassification(nClassification, eAffil, NULL_INDEX);
            pReport->mbClassified = 1;
        }


        if (bNewDetection) 
        {
            pSMTrack->UpdateTrack();
            if (mpUserInfo->IsOwnAlliance(apRadarPlat->GetAlliance())) 
            {
                tcSound::Get()->PlayEffect("Ping");
            }
            char zBuff[128];
            sprintf(zBuff,"target %d detected at %3.1f km at time %.1f [a:%d]",
                apTarget->mnID,fRange_km,mfSimTime,apRadarPlat->GetAlliance());
            WTLC(zBuff);
        }
    }
#endif

}




/**
* Deprecated method
*/
void tcSimState::UpdateSurveillance(tcGameObject *applat, tcSensorState *apSensorState)
{
#if 0
    long aTargetKeys[100];
    long nTargetID;
    int nCount;
    tcRect region;
    tcGameObject *pTarget;

	wxASSERT(false); // deprecated


    apSensorState->GetTestArea(region);
    nCount = GetPlatformsWithinRegion(aTargetKeys, 100, &region);
//    bool bOwnAllianceUpdate = mpUserInfo->IsOwnAlliance(applat->GetAlliance());
    for(int k=0;k<nCount;k++) 
    {
        nTargetID = aTargetKeys[k];            
        if (nTargetID != applat->mnID) // no self detection   
        { 
            pTarget = GetObject(nTargetID);
            tcRadar *pRadarSS = dynamic_cast<tcRadar*>(apSensorState);
            if (pRadarSS) 
            {
                ProcessRadarDetection(applat,pTarget,pRadarSS);
            }
            else if (tcESMSensor *pESMSS = dynamic_cast<tcESMSensor*>(apSensorState)) 
            {
                ProcessESMDetection(applat,pTarget,pESMSS);
            }
        }
    }
#endif
}


#define N_TARGET_KEYS 100
#define N_FC_KEYS 32
void tcSimState::UpdateFireControl(tcGameObject *apGameObj, tcRadar *apRadarSS) 
{
    wxASSERT(false); // deprecated?
#if 0
    long aTargetKeys[N_TARGET_KEYS];
    long aFCKeys[N_FC_KEYS];
    float afRanges[N_FC_KEYS];
    long nTargetID;
    int nCount,nFCCount;
    tcRect region;
    GeoPoint currentpos;
    //   tcDatabaseObject *pTargetDBObj;
    tcGameObject *pTargetObj;

    currentpos.Set((float)apGameObj->mcKin.mfLon_rad,(float)apGameObj->mcKin.mfLat_rad,
        apGameObj->mcKin.mfAlt_m);
    //apRadarSS->UpdateCoverage(currentpos,apGameObj->mcKin.mfHeading_rad);
    apRadarSS->GetTestArea(region);
    nCount = GetPlatformsWithinRegion(aTargetKeys, 100, &region);
    nFCCount = 0;
    for(int k=0;(k<nCount)&&(nFCCount<N_FC_KEYS);k++) 
    {
        nTargetID = aTargetKeys[k];
        if (nTargetID != apGameObj->mnID) // no self detection
        { 
            bool bDetected = false;
            int bTargetExists = maPlatformState.Lookup(nTargetID,pTargetObj);
            bool bOwnAlliance = (pTargetObj->GetAlliance() == apGameObj->GetAlliance());
            float fRange_km = 0;
            if ((bTargetExists)&&(!bOwnAlliance)) // no own-alliance detections
            { 
                bDetected = apRadarSS->CanDetectTarget(pTargetObj,fRange_km) == 1; 
            }
            if (bDetected) {  
                afRanges[nFCCount] = fRange_km;
                aFCKeys[nFCCount++] = nTargetID;
            }
        }
    }
    // update engagement handler object if apGameObj is a tcSurfaceObj*
    tcSurfaceObject *pSurfaceObj = dynamic_cast<tcSurfaceObject*>(apGameObj);
    if (pSurfaceObj != NULL) {
        if ((nFCCount > 0)||(pSurfaceObj->mcEngagementData.mnCount > 0)) {
            pSurfaceObj->mcEngagementData.Update(aFCKeys,afRanges,nFCCount);
        }
    }
#endif
}

/**
* Test objects for landing criteria. Land objects that meet
* criteria. 
* @see UpdateLandingState
* @see flightportPlatforms
* @see landingPlatforms
*/
void tcSimState::UpdateLandings(double afSimTime)
{
    UpdateLandingState(afSimTime);

    int receiving_count = (int)flightportPlatforms.size();
    int air_count = (int)landingPlatforms.size();
    for (int n=0;n<receiving_count;n++)
    {
        tcGameObject *receiver = GetObject(flightportPlatforms.at(n));
        if (receiver)
        {
            for (int m=0;m<air_count;m++)
            {
                tcGameObject *landing_unit = GetObject(landingPlatforms.at(m));
                ProcessLanding(receiver, landing_unit);
            }
        }
    }
}

/**
* Periodically update landing-related data structures. Data
* is used by UpdateLandings to narrow down list of objects
* to test for landing criteria.
* @see UpdateLandings
* @see flightportPlatforms
* @see landingPlatforms
*/
void tcSimState::UpdateLandingState(double afSimTime)
{
    if (afSimTime - lastLandingStateUpdate < 1.125f) return;

    lastLandingStateUpdate = afSimTime;
    flightportPlatforms.clear();
    landingPlatforms.clear();

    long pos = maPlatformState.GetStartPosition();
    int nSize = maPlatformState.GetCount();

    for (int i=0;i<nSize;i++) 
    {    
        tcGameObject *gameObj;
        long nKey;
        maPlatformState.GetNextAssoc(pos,nKey,gameObj);
        if (dynamic_cast<tcFlightOpsObject*>(gameObj))
        {
            flightportPlatforms.push_back(gameObj->mnID);
        }
        else if (dynamic_cast<tcAirObject*>(gameObj))
        {
            float terrainHeight_m = std::max(gameObj->mcTerrain.mfHeight_m, 0.0f);
            if ((gameObj->mcKin.mfAlt_m - terrainHeight_m) <= 1000.0f)
            {
                landingPlatforms.push_back(gameObj->mnID);
            }
        }
    }
}

/**
* Checks each object's toLaunch queue and "launches" by transfering
* ownership of queued objects to tcSimState. The parent of launched
* objects is set to NULL.
*/ 
void tcSimState::UpdateLaunch()
{
    long pos = maPlatformState.GetStartPosition();
    int nSize = maPlatformState.GetCount();

    for (int i=0;i<nSize;i++) 
    {    
        tcGameObject *gameObj;
        long nKey;
        maPlatformState.GetNextAssoc(pos,nKey,gameObj);
        int launch_count = (int)gameObj->toLaunch.size();
        for(int n=0;n<(int)launch_count;n++)
        {
            tcGameObject *child = gameObj->toLaunch.at(n);
            child->parent = NULL;

            AddPlatform(child);

			if (dynamic_cast<tcHeloObject*>(child))
			{
				PlayEntitySoundEffect(gameObj, "helolaunch");

			}
			else if (dynamic_cast<tcAirObject*>(child))
			{
				PlayEntitySoundEffect(gameObj, "jetlaunch");

			}
		}
        if (launch_count) 
        {
            gameObj->toLaunch.clear();
        }
    }
}

/**
* Deprecated?
*/
void tcSimState::UpdateSeeker(tcGameObject *applat, tcRadar *apRadarSS) 
{
    wxASSERT(false);
    
#if 0
    long nTargetID;
    GeoPoint currentpos;
    tcTrack *pTrack;
    tcGameObject *ptarget;
    long aTargetKeys[100];
    int nCount;
    tcRect region;   
    long nMinID;
    float fRange,fMinRange;
    int bFound;
    int bDetectable;

    currentpos.Set((float)applat->mcKin.mfLon_rad,(float)applat->mcKin.mfLat_rad);
    //apRadarSS->UpdateCoverage(currentpos,applat->mcKin.mfHeading_rad);
    pTrack = &apRadarSS->mcTrack;

    switch (apRadarSS->mnMode) 
    {
   case SSMODE_SEEKERACQUIRE:
       nTargetID = pTrack->mnID;
       // fall through to SEEKERTRACK
   case SSMODE_SEEKERTRACK:
       nTargetID = pTrack->mnID;
       if (nTargetID == applat->mnID)
       { // no self detection
           apRadarSS->mnMode = SSMODE_SEEKERSEARCH;
           return;
       } 
       bFound = maPlatformState.Lookup(nTargetID,ptarget);
       if (bFound) 
       {  // own-alliance is allowed
           float fRange_km;
           bDetectable = apRadarSS->CanDetectTarget(ptarget,fRange_km); 
           if (bDetectable) 
           {
               // update track info
               pTrack->mfLat_rad = (float)ptarget->mcKin.mfLat_rad;
               pTrack->mfLon_rad = (float)ptarget->mcKin.mfLon_rad;
               pTrack->mfAlt_m = ptarget->mcKin.mfAlt_m;
               pTrack->mfSpeed_kts = ptarget->mcKin.mfSpeed_kts;
               pTrack->mfHeading_rad = ptarget->mcKin.mfHeading_rad;
               pTrack->mfClimbAngle_rad = ptarget->mcKin.mfClimbAngle_rad;
               pTrack->mfTimestamp = mfSimTime;
               pTrack->mnFlags = (TRACK_HEADING_VALID | TRACK_SPEED_VALID 
                   | TRACK_ALT_VALID | TRACK_CLIMB_VALID);
               if (apRadarSS->mnMode == SSMODE_SEEKERACQUIRE)
               {
                   apRadarSS->mnMode=SSMODE_SEEKERTRACK;
                   if(mpUserInfo->IsOwnAlliance(applat->GetAlliance())) 
                   {
                       tcSound::Get()->PlayEffect("TwoBeeps");
                   }
               }
               return;
           }
       }
       // shut down missile if track lost for > 7 seconds
       if ((apRadarSS->mnMode == SSMODE_SEEKERTRACK)&&
           (mfSimTime - pTrack->mfTimestamp) > 7.0)
       {
           applat->mfDamageLevel = 1.0f; 
           pTrack->mnID = NULL_INDEX;
           if(mpUserInfo->IsOwnAlliance(applat->GetAlliance())) 
           {
               char zBuff[128];
               sprintf(zBuff,"Missile %d shut down\n",applat->mnID);
               mpCommandInterface->DisplayInfoMessage(zBuff);
           }
           return;
       }
       // this code to enter search mode after track lost
       //pTrack->mnID = NULL_INDEX; 
       //apRadarSS->mnMode = SSMODE_SEEKERSEARCH; 
       break;
   case SSMODE_SEEKERSEARCH:
       // get list of candidate tracks/detections
       apRadarSS->GetTestArea(region);
       nCount = GetPlatformsWithinRegion(aTargetKeys, 100, &region);
       // choose closest detectable candidate
       fMinRange = 1e15f;
       nMinID = NULL_INDEX;
       for(int k=0;k<nCount;k++) 
       {
           nTargetID = aTargetKeys[k];
           if (nTargetID != applat->mnID) 
           { // no self detection
               bFound = maPlatformState.Lookup(nTargetID,ptarget);
               if (bFound) 
               {
                   bDetectable = apRadarSS->CanDetectTarget(ptarget,fRange); // (GeoPoint,float rcs_dbsm)
                   if ((bDetectable)&&(fRange<fMinRange)) 
                   {
                       nMinID = nTargetID;
                       fMinRange = fRange;
                   }
               }
           }
       }
       // add track data and designate as target
       if (nMinID==NULL_INDEX) return;
       maPlatformState.Lookup(nMinID,ptarget);
       applat->DesignateTarget(nMinID);
       break;
    }
#endif
}

/**
*
*/
void tcSimState::AddPlatform(tcGameObject *pplat) 
{
    long newkey;
    maPlatformState.AddElement(pplat, newkey);
    pplat->mnID = newkey;
    
    RegisterPlatform(pplat);
}

/**
* Used to force key for particular platform when restoring scenario from file
*/
void tcSimState::AddPlatformWithKey(tcGameObject *pplat, long key)
{
    maPlatformState.AddElementForceKey(pplat,key);
    pplat->mnID = key;
    
    RegisterPlatform(pplat);
}

/**
* Adds unit name to objectNameMap for quick lookup by name
*/
void tcSimState::RegisterPlatform(tcGameObject* obj)
{
    wxASSERT(obj);
    std::string unitName(obj->mzUnit.c_str());
    std::map<std::string, long>::iterator iter = objectNameMap.find(unitName);
    
    if (iter == objectNameMap.end())
    {
        objectNameMap[unitName] = obj->mnID;
    }
    else
    {
        fprintf(stderr, "Error - tcSimState::AddPlatform - "
            "duplicate objectNameMap entry, overwriting (%s)\n", 
            unitName.c_str());
        objectNameMap[unitName] = obj->mnID;
    }
}

void tcSimState::UnregisterPlatform(tcGameObject* obj)
{
	wxASSERT(obj);
	if (obj == 0) return;

    std::string unitName(obj->mzUnit.c_str());
    std::map<std::string, long>::iterator iter = objectNameMap.find(unitName);
    
    if (iter != objectNameMap.end())
    {
		objectNameMap.erase(iter);
    }
    else
    {
        fprintf(stderr, "Error - tcSimState::UnregisterPlatform - "
            "not found (%s)\n", unitName.c_str());
    }
}




/**
*
*/
void tcSimState::AddLaunchedPlatform(long newKey, tcGameObject* launchingPlatform, 
									 unsigned nLauncher) 
{
    tcDatabaseObject *pDBObject;

    pDBObject = mpDatabase->GetObject(newKey);
    if (pDBObject == NULL) {return;}


	tcGameObject* launched = CreateGameObject(pDBObject);

    // why isn't this done with virtual methods vs big if/else-if network?

    if (tcMissileObject* missile = dynamic_cast<tcMissileObject*>(launched))
	{
		missile->LaunchFrom(launchingPlatform, nLauncher);
		
        if (launchingPlatform->mcKin.mfAlt_m >= 0)
		{
		    PlayEntitySoundEffect(launchingPlatform, "MissileLaunch");
        }
        else
        {
            PlayEntitySoundEffect(launchingPlatform, "torpedo_launch");
        }
        tcEventManager::Get()->WeaponLaunched(launchingPlatform->GetAlliance());
	}
    else if (tcTorpedoObject* torp = dynamic_cast<tcTorpedoObject*>(launched))
	{
		torp->LaunchFrom(launchingPlatform, nLauncher);

		if (launchingPlatform->mcKin.mfAlt_m <= 0)
		{
			PlayEntitySoundEffect(launchingPlatform, "torpedo_launch");
		}
        tcEventManager::Get()->WeaponLaunched(launchingPlatform->GetAlliance());
	}
    else if (tcGuidedBomb* guided = dynamic_cast<tcGuidedBomb*>(launched))
    {
        guided->LaunchFrom(launchingPlatform, nLauncher);
        tcEventManager::Get()->WeaponLaunched(launchingPlatform->GetAlliance());
    }	
    else if (tcBallisticWeapon* ballistic = dynamic_cast<tcBallisticWeapon*>(launched))
	{
		ballistic->LaunchFrom(launchingPlatform, nLauncher);

		if (ballistic->IsGunRound())
		{
			PlayEntitySoundEffect(launchingPlatform, "NavalGun1");
		}
		else if (ballistic->IsAutocannon())
		{
			PlayEntitySoundEffect(launchingPlatform, "Gatling");
		}
		else if (ballistic->IsRocket())
		{
			PlayEntitySoundEffect(launchingPlatform, "MissileLaunch");
		}
        tcEventManager::Get()->WeaponLaunched(launchingPlatform->GetAlliance());
	}
    else if (tcSonobuoy* sonobuoy = dynamic_cast<tcSonobuoy*>(launched))
    {
        sonobuoy->LaunchFrom(launchingPlatform, nLauncher);
    }
    else if (tcAirCM* cm = dynamic_cast<tcAirCM*>(launched))
    {
        cm->LaunchFrom(launchingPlatform, nLauncher);
    }
    else if (tcWaterCM* cm = dynamic_cast<tcWaterCM*>(launched))
    {
        cm->LaunchFrom(launchingPlatform, nLauncher);
    }
    else if (tcBallisticMissile* bm = dynamic_cast<tcBallisticMissile*>(launched))
    {
        bm->LaunchFrom(launchingPlatform, nLauncher);
        tcEventManager::Get()->WeaponLaunched(launchingPlatform->GetAlliance());
    }
    else
	{
		fprintf(stderr, "tcSimState::AddLaunchedPlatform - "
            "Unrecognized or NULL obj from CreateGameObject");
		return;
	}
  

}

/**
* Factory method to create new objects from a database object.
* Recently reworked this so that game objects initialize themselves.
*/
tcGameObject* tcSimState::CreateGameObject(tcDatabaseObject *apDBObject) 
{
    if (apDBObject == 0) {return 0;}

    // make sure more specialized classes are tested first to avoid
    // accidental upcast
    if (tcJetDBObject *pAirData = dynamic_cast<tcJetDBObject*>(apDBObject))
    {
        return new tcAeroAirObject(pAirData);
    }
	else if (tcSubDBObject* subData = dynamic_cast<tcSubDBObject*>(apDBObject))
	{
		return new tcSubObject(subData);
	}
    else if (tcShipDBObject* shipData = dynamic_cast<tcShipDBObject*>(apDBObject))
    {
        /* these types are defined in tcDatabase.h */
        switch (apDBObject->mnModelType)
        {
        case MTYPE_CARRIER:
			{
				if (mpDatabase->GetObject(shipData->flightportClass.c_str()) != 0)
				{
					return new tcCarrierObject(shipData);
				}
				else
				{
					wxString msg = wxString::Format("Error creating carrier type surface ship (%s), reverting to non-carrier model. Invalid flightport class (%s). Check database.",
                        shipData->mzClass.c_str(), shipData->flightportClass.c_str());
                    fprintf(stderr, "%s\n", msg.c_str());
                    #ifdef _DEBUG
                    wxMessageBox(msg, "Object Create Error");
                    #endif
                    return new tcSurfaceObject(shipData);
				}
			}
            break;
        case MTYPE_SURFACE:
            return new tcSurfaceObject(shipData);
            break;
        default:
            fprintf(stderr, "tcSimState::CreateGameObject - "
                "Invalid model type for Ship DB obj (%d)\n", apDBObject->mnModelType);
            return 0;
        }
    }
    else if (tcSimpleAirDBObject* airData = dynamic_cast<tcSimpleAirDBObject*>(apDBObject))
    {
        /* these types are defined in tcDatabase.h */
        switch (apDBObject->mnModelType)
        {
        case MTYPE_FIXEDWING:
        case MTYPE_AIR:
            return new tcAirObject(airData);
            break;
        case MTYPE_HELO:
            return new tcHeloObject(airData);
            break;
        default:
            fprintf(stderr, "tcSimState::CreateGameObject - "
                "Invalid model type for Simple Air DB obj (%d)\n", apDBObject->mnModelType);
            return NULL;
        }
    }
    else if (tcGroundDBObject* groundData = dynamic_cast<tcGroundDBObject*>(apDBObject))
    {
        /* these types are defined in tcDatabase.h */
        switch (apDBObject->mnModelType)
        {
        case MTYPE_AIRFIELD:
            return new tcAirfieldObject(groundData);
            break;
        case MTYPE_FIXED:
            return new tcGroundObject(groundData);
            break;

        case MTYPE_GROUNDVEHICLE:
            return new tcGroundVehicleObject(groundData);
            break;
        default:
            fprintf(stderr, "tcSimState::CreateGameObject - "
                "Invalid model type for ground DB obj (%d)\n", apDBObject->mnModelType);
            return NULL;
        }
    }
    else if (tcMissileDBObject *pMissileData = dynamic_cast<tcMissileDBObject*>(apDBObject))
    {
        return new tcMissileObject(pMissileData);
    }
    else if (tcTorpedoDBObject *torpData = dynamic_cast<tcTorpedoDBObject*>(apDBObject))
    {
        return new tcTorpedoObject(torpData);
    }
	else if (tcBallisticDBObject* ballisticData = dynamic_cast<tcBallisticDBObject*>(apDBObject))
	{
		switch (apDBObject->mnModelType)
		{
		case MTYPE_LASERGUIDEDBOMB:
			{
				return new tcGuidedBomb(ballisticData);
			}
			break;
		case MTYPE_ROCKET:
			{
				return new tcRocket(ballisticData);
			}
			break;
		default:
			{
				return new tcBallisticWeapon(ballisticData);
			}
			break;
		}
	}
    else if (tcSonobuoyDBObject* sonobuoyData = dynamic_cast<tcSonobuoyDBObject*>(apDBObject))
    {
        return new tcSonobuoy(sonobuoyData);
    }
    else if (tcCounterMeasureDBObject* cmData = dynamic_cast<tcCounterMeasureDBObject*>(apDBObject))
    {
        if (apDBObject->mnModelType == MTYPE_AIRCM)
        {
            return new tcAirCM(cmData);
        }
        else 
        {
            wxASSERT(apDBObject->mnModelType == MTYPE_WATERCM);
            return new tcWaterCM(cmData);
        }
    }
    else if (tcBallisticMissileDBObject* bmData = dynamic_cast<tcBallisticMissileDBObject*>(apDBObject))
    {
        return new tcBallisticMissile(bmData);
    }
    else
    {
        wxASSERT(false);
        WTL("Error - tcSimState::CreateGameObject - Unrecognized database object");
        return NULL;
    }
}

/**
* Removes game object from simulation
*/
void tcSimState::DeleteObject(long key) 
{
    tcGameObject* obj = GetObject(key);

    if (!obj)
    {
        fprintf(stderr, "Error - tcSimState::DeletePlatform - not found\n");
        return;
    }

    tcSimPythonInterface::Get()->UpdateForDestroyedPlatform(key);

	UnregisterPlatform(obj);

    if ((dynamic_cast<tcWeaponObject*>(obj) == 0) && (dynamic_cast<tcAirCM*>(obj) == 0) && 
        (dynamic_cast<tcSonobuoy*>(obj) == 0) && (!IsMultiplayerClient()))
    {
        tcString s;
        s.Format("%s (%s) destroyed\n", obj->mzUnit.c_str(), obj->mzClass.c_str());
        mpCommandInterface->DisplayInfoMessage(s.GetBuffer());
    }

    if (positionRegistry)
    {
        positionRegistry->RemoveId(obj->mnID);
    }

    maPlatformState.RemoveKey(key);
}


/**
*
*/
void tcSimState::DeleteAllPlatforms() 
{
    maPlatformState.RemoveAll();
}

/**
*
*/
void tcSimState::ClearSensorMaps() 
{
    mcSensorMap.Clear();
}


/**
* Call when adding child object, e.g. aircraft to flightdeck.
* This allows child object to be looked up by name (but not id) during scenario creation 
*/
void tcSimState::RegisterChildObject(const std::string& name, tcGameObject* parent)
{
    wxASSERT(parent != 0);

    std::map<std::string, long>::iterator iter = 
        captiveObjectMap.find(name);
    if (iter != captiveObjectMap.end())
    {
        wxString msg;
        msg.Printf("Unit name, %s, already exists. Tried to add to parent %s. Fix the scenario file!\n", 
            name.c_str(), parent->GetName());
        wxMessageBox(msg, "Scenario Error", wxICON_ERROR);

        fprintf(stderr, "RegisterChildObject - %s already exists in captiveObjectMap\n", 
            name.c_str());
        return;
    }

    wxASSERT(parent->mnID != -1);

    captiveObjectMap[name] = parent->mnID;
}

void tcSimState::TestDamageModel()
{
    tcDamageModel* damage = tcDamageModel::Get();

    float altitude_m = 1000;
    float range_m = 30.0f;
    float blast_charge_kg = 100.0f;

    float blast_psi = damage->CalculateBlastOverpressure(range_m, blast_charge_kg);

    tcDamageModel::FragWeapon weap;
    weap.charge_kg = 10.0f;
    weap.metal_kg = 10.0f;
    weap.fragment_kg = 0.005f;
    weap.spread_factor = 0.5f;
    
    float targetArea_m2 = 20.0f;

    tcDamageModel::FragHits fragResult =
        damage->CalculateFragmentImpact(range_m, altitude_m, weap, targetArea_m2);



}


void tcSimState::ToggleUserAlliance()
{
    tcUserInfo* userInfo = tcUserInfo::Get();
    unsigned char userAlliance = userInfo->GetOwnAlliance();
    
    for (unsigned char n=userAlliance+1; n<8; n++)
    {
        if (mcSensorMap.MapExists((unsigned)n))
        {
            userInfo->SetOwnAlliance(n);
            tcAllianceSensorMap* sensorMap = mcSensorMap.GetMap((unsigned)n);
            mpPythonInterface->AttachSensorMap(sensorMap);
            return;
        }
    }

    userInfo->SetOwnAlliance(1);
    tcAllianceSensorMap* sensorMap = mcSensorMap.GetMap(1);
    mpPythonInterface->AttachSensorMap(sensorMap);
}

/**
* Call when removing child object, e.g. launching aircraft from flightdeck
*/
void tcSimState::UnregisterChildObject(const std::string& name)
{
    std::map<std::string, long>::iterator iter = 
        captiveObjectMap.find(name);
    if (iter == captiveObjectMap.end())
    {
        wxASSERT(false);
        fprintf(stderr, "UnregisterChildObject - %s does not exist in captiveObjectMap\n", 
            name.c_str());
        return;
    }

    captiveObjectMap.erase(iter);
}

/**
*
*/
tcGameObject* tcSimState::CreateRandomPlatform(UINT platform_type) 
{
    bool bSearching = true;
    bool bFound = false;
    int nTries = 0;
    tcDatabaseObject *pdata = 0;

    while ((bSearching)&&(nTries++ < 128)) 
    {
        long nKey = mpDatabase->GetRandomKey();
        bFound = mpDatabase->mcObjectData.Lookup(nKey,pdata);
        if (pdata->mnType == platform_type) {bSearching = false;}
    }
    if (bSearching) {WTL("Error - tcSimState::AddRandomPlatform - timed out");return NULL;}
    if (!bFound) {WTL("Error - tcSimState::AddRandomPlatform");return NULL;}

    return CreateGameObject(pdata);
}


/**
*
*/
void tcSimState::AttachDB(tcDatabase *pDatabase) 
{
    mpDatabase = pDatabase;
}

/**
*
*/
void tcSimState::PrintToFile(tcString sFileName) 
{
    tcFile file;
    tcGameObject *pplat;
    char buff[256];

    file.Open(sFileName.GetBuffer(),tcFile::modeCreate|tcFile::modeWrite|tcFile::modeText);

    sprintf(buff,"Total platform count: %d\n", maPlatformState.GetCount());
    file.WriteString(buff);

    tcGameObjIterator iter;
    int idx = 0;
    for (iter.First();iter.NotDone();iter.Next())
    {
        pplat = iter.Get();
        sprintf(buff,"%d %s (%s) AL:%d (lat: %.2f, lon: %.2f) \n",idx, 
            pplat->mzUnit.c_str(), pplat->mzClass.c_str(), pplat->GetAlliance(),
            pplat->mcKin.mfLat_rad*C_180OVERPI, pplat->mcKin.mfLon_rad*C_180OVERPI);
        file.WriteString(buff);

        /*
        tcStream test2;
        size_t s1 = test2.size();

        *pplat >> test2;
        
        size_t s2 = test2.size();

        pplat->Clear();
        *pplat << test2;

        size_t s3 = test2.size();

        int x = 7;
        test2 >> x;
        
        bool isEOF = false;
        isEOF = test2.eof();
        */

        idx++;
    }


    file.Close();
}

/**
* Call CheckLanding for receiver. If landing is accepted, remove the object
* from the maPlatformState container.
*/
void tcSimState::ProcessLanding(tcGameObject *receiver, tcGameObject *landing_unit)
{
    if ((landing_unit==NULL)||(receiver==NULL)) return;

    tcAirObject *air = dynamic_cast<tcAirObject*>(landing_unit);
    if (air == NULL) return; // only AirObject are supported currently
    float range = landing_unit->mcKin.RangeToKmAlt(receiver->mcKin);
    bool notClimbing = landing_unit->mcKin.mfClimbAngle_rad < 0.01f;

    if ((range < 0.8f)&&(notClimbing)&&(air->readyForLanding))
    {
        if (tcFlightOpsObject* flightOps = dynamic_cast<tcFlightOpsObject*>(receiver))
        {
            // save key since AddChild can be called from CheckLanding, replaces mnID
            long key = landing_unit->mnID; 
            if (flightOps->CheckLanding(air) == 1) // if landing is successful
            {
                // remove from platformstate container
                maPlatformState.RemoveKeyWithoutDelete(key);

				UnregisterPlatform(landing_unit);

                if (positionRegistry)
                {
                    positionRegistry->RemoveId(key);
                }
            }
        }
    }
}

/**
*
*/
int tcSimState::GetPlatformAlliance(long anKey, UINT& rnAlliance) 
{
    tcGameObject *pplat;
    int bFound;
    bFound = GetPlatformState(anKey, pplat);
    if (bFound)
    {
        rnAlliance = pplat->GetAlliance();
    }
    else 
    {
        rnAlliance = 0;
    }
    return rnAlliance;
}

/**
*
*/
int tcSimState::GetPlatformState(long anKey, tcGameObject*& pplat) 
{
    int bFound;
    bFound = maPlatformState.Lookup(anKey,pplat);
    return bFound;
}

/**
*
*/
tcGameObject* tcSimState::GetObject(long anKey) 
{
#ifdef _DEBUG
    if (anKey == -99) // hack to get non-maPlatformState obj for WeaponTester returned
    {
        return tcWeaponTester::Get()->GetPlatform();
    }
#endif
    tcGameObject *pGameObj;
    maPlatformState.Lookup(anKey,pGameObj);
    return pGameObj; // tcPool sets pGameObj NULL if not found
}

const tcGameObject* tcSimState::GetObjectConst(long id) const
{
    return maPlatformState.LookupConst(id);
}

/**
* @return game object matching unitName or 0 if not found.
*/
tcGameObject* tcSimState::GetObjectByName(const std::string& unitName)
{
    // first try to lookup in map
    std::map<std::string, long>::iterator iter = objectNameMap.find(unitName);
    if (iter != objectNameMap.end())
    {
        if (tcGameObject *obj = GetObject(iter->second))
        {
            return obj;
        }
        else // object doesnt exist any more, clear map entry
        {
            wxASSERT(false);
            objectNameMap.erase(iter);
            return 0;
        }
    }
    else // check captiveObjectMap to see if this is a flightdeck object
    {
        std::map<std::string, long>::iterator iter = captiveObjectMap.find(unitName);
        if (iter != captiveObjectMap.end())
        {
            tcGameObject* parent = GetObject(iter->second);
            if (parent != 0)
            {
                return parent->GetChildByName(unitName);
            }
            else
            {
                wxASSERT(false);
                captiveObjectMap.erase(iter);
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }

}


/**
* @return pointer to sensor map
*/
tcSensorMap* tcSimState::GetSensorMap()
{
    return &mcSensorMap;
}

/**
*
*/
void tcSimState::GetDescription(long anKey, tcString& s) 
{
    int bFound;
    tcGameObject *pplat;
    bFound = maPlatformState.Lookup(anKey, pplat);
    if (bFound) 
    {
        s.Format("%s %2.0f kts %3.0f deg",pplat->mzUnit.c_str(),pplat->mcKin.mfSpeed_kts,
            pplat->mcKin.mfHeading_rad);
    }
    else 
    {
        s = "NOT FOUND";
    }
}

/**
* 
*/
void tcSimState::GetPlatformsWithinRegion(std::vector<long>& keyList, tcRect *apRegion) 
{
    tcGameObject *pplat;
    long cmappos = maPlatformState.GetStartPosition();
    long nSize = maPlatformState.GetCount();
    long nKey;
    //int nListIndex=0;
    tcKinematics *pKin = 0;
    GeoPoint p;

    keyList.clear();

    if (positionRegistry)
    {
        // position registry returns a superset of all the platforms we want (coarse bins)
        std::vector<long> temp = 
            positionRegistry->GetAllWithinRegion(apRegion->GetLeft(), apRegion->GetRight(),
            apRegion->GetBottom(), apRegion->GetTop());

        // narrow down to just platforms in requested region
        for (size_t n=0; n<temp.size(); n++)
        {
            if (tcGameObject* obj = GetObject(temp[n]))
            {
                pKin = &obj->mcKin;
                p.Set((float)pKin->mfLon_rad,(float)pKin->mfLat_rad);
                if (GeoWithinRegion(p,apRegion))
                {
                    keyList.push_back(temp[n]);
                }
            }
        }

        return;
    }

    for (long i=0; (i<nSize); i++) 
    {
        maPlatformState.GetNextAssoc(cmappos,nKey,pplat);
        pKin = &pplat->mcKin;
        p.Set((float)pKin->mfLon_rad,(float)pKin->mfLat_rad);
        if (GeoWithinRegion(p,apRegion))
        {
            keyList.push_back(nKey);
        }
    }
}

/**
*
*/
long tcSimState::GetRandomPlatform() 
{
    tcGameObject *pplat;
    long cmappos = maPlatformState.GetStartPosition();
    long nSize = maPlatformState.GetCount();
    long nKey;

    int k = rand() % nSize; // k [0,nSize-1]
    maPlatformState.GetNextAssoc(cmappos,nKey,pplat);
    for (int i=0;i<k;i++) 
    {
        maPlatformState.GetNextAssoc(cmappos,nKey,pplat);
    }
    return nKey;
}

/**
* Intended to be called after RandInit(). This generates
* a random destroy goal for each side. Goals are added to
* goalTracker object.
*/
void tcSimState::GenerateRandomGoals()
{
    long key;
    tcGameObject *obj;

    GetAlliancePlatforms(&key,1,1);
    obj = GetObject(key);
	wxASSERT(obj);
    goalTracker->SetAllianceGoal(2, new tcDestroyGoal(obj->mzUnit.c_str()));
    fprintf(stdout,"Added destroy goal for alliance %d: %s\n",2,obj->mzUnit.c_str());

    GetAlliancePlatforms(&key,1,2);
    obj = GetObject(key);
	wxASSERT(obj);
    goalTracker->SetAllianceGoal(1, new tcDestroyGoal(obj->mzUnit.c_str()));
    fprintf(stdout,"Added destroy goal for alliance %d: %s\n",1,obj->mzUnit.c_str());
}


/**
*
*/
int tcSimState::GetAllSensorPlatforms(long *apKeyList, int anMaxLength) 
{
    tcGameObject *pplat;
    long cmappos = maPlatformState.GetStartPosition();
    long nSize = maPlatformState.GetCount();
    long nKey;
    int nListIndex=0;
    tcSensorState *pSensorState; 

    for (long i=0;(i<nSize)&&(nListIndex<anMaxLength);i++)
    {
        maPlatformState.GetNextAssoc(cmappos,nKey,pplat);
        bool bActiveFound = false;
        if (tcPlatformObject *pPlatformObj = dynamic_cast<tcPlatformObject*>(pplat))
        {
            bActiveFound = pPlatformObj->HasActivatedSensor();
        }
        else if (tcMissileObject *pMissileObj = dynamic_cast<tcMissileObject*>(pplat))
        {
            pSensorState = pMissileObj->GetSeekerSensor();
            bActiveFound = pSensorState->IsActive();
        }

        if (bActiveFound) 
        {
            apKeyList[nListIndex++]=nKey;
        }
    }
    return nListIndex;
}

/**
*
*/
unsigned tcSimState::GetAlliancePlatforms(long *aaKeyList, unsigned anMaxLength, int anAlliance) 
{
    tcGameObject *pGameObj;
    long cmappos = maPlatformState.GetStartPosition();
    long nSize = maPlatformState.GetCount();
    long nKey;
    long nListIndex=0;

    for (int i=0;(i<nSize)&&(nListIndex<(int)anMaxLength);i++) 
    {
        maPlatformState.GetNextAssoc(cmappos,nKey,pGameObj);
        if (pGameObj->GetAlliance() == anAlliance) 
        {
            aaKeyList[nListIndex++]=nKey;
        }
    }
    return (unsigned)nListIndex;
}

/**
* Gets time acceleration for simulation.
* Currently an info-only parameter, but will be changed
* in the future to give simstate control over its own
* time acceleration vs. having this at the main game loop level.
*/
long tcSimState::GetTimeAcceleration() const
{
    return timeAcceleration;
}

/**
* Populates <track> with track from sensor map or truth data
* if <id> is own-alliance.
* @param alliance alliance of requesting entity
* @return true if successful, false if id not found
*/
bool tcSimState::GetTrack(long id, unsigned alliance, tcSensorMapTrack& track)
{
    tcGameObject* obj = GetObject(id);

    // return truth data if own alliance or we're in edit mode
    if ((obj != 0) && ((alliance == obj->GetAlliance()) || (tcGameObject::IsEditMode())))
    {
        tcKinematics *kin = &obj->mcKin;
		track.mfTimestamp = obj->mfStatusTime;
        track.mfAlt_m = kin->mfAlt_m;
        track.mfHeading_rad = kin->mfHeading_rad;
        track.mfLat_rad = (float)kin->mfLat_rad;
        track.mfLon_rad = (float)kin->mfLon_rad;
        track.mfSpeed_kts = kin->mfSpeed_kts;
		track.mnFlags = TRACK_SPEED_VALID | TRACK_HEADING_VALID |
				TRACK_ALT_VALID;
        track.mnClassification = obj->mpDBObject->mnType;
        track.mnID = obj->mnID;
        track.mnAffiliation = tcAllianceInfo::FRIENDLY;
    }
    else
    {
        tcSensorMapTrack *pTrack = 
            mcSensorMap.GetSensorMapTrack(id, alliance);
        if (pTrack) track = *pTrack;
		else return false; // track not found
    }

    return true;
}


/**
* Populates <track> with truth data
* @return true if successful, false if id not found
*/
bool tcSimState::GetTruthTrack(long id, tcTrack& track)
{
    tcGameObject* obj = GetObject(id);
    if (obj == 0) return false; // target not found

    tcKinematics *kin = &obj->mcKin;
    track.mfAlt_m = kin->mfAlt_m;
    track.mfHeading_rad = kin->mfHeading_rad;
    track.mfClimbAngle_rad = kin->mfClimbAngle_rad;
    track.mfLat_rad = (float)kin->mfLat_rad;
    track.mfLon_rad = (float)kin->mfLon_rad;
    track.mfSpeed_kts = kin->mfSpeed_kts;
    track.mnClassification = obj->mpDBObject->mnType;
    track.mnID = obj->mnID;
    track.mnAffiliation = tcAllianceInfo::FRIENDLY;
	track.mfTimestamp = obj->mfStatusTime;
	track.SetAllValid();

    return true;
}

/**
* @return true if valid scenario is loaded
*/
bool tcSimState::IsScenarioLoaded() const
{
	return msScenarioInfo.mbLoaded;
}

/**
* Loads sim time and date-time from stream.
* In client mode, backward jumps and small forward jumps are ignored
*/
void tcSimState::LoadTimeFromStream(tcStream& stream)
{
    if (multiplayerMode == MM_CLIENT)
    {
        double tempSimTime;
        tcDateTime tempDateTime;
        stream >> tempSimTime;
        tempDateTime << stream;
        stream >> timeAcceleration;
        stream >> isMultiplayerGameStarted;

        double dt = tempSimTime - mfSimTime; // positive means server time is ahead of client time
        multiplayerTimeLag_s = dt;

        if ((tempSimTime == 0) || (dt > 0))
        {
            mfSimTime = tempSimTime;
            dateTime = tempDateTime;
        }
        // if client time is too much ahead, pause the client
        double lagThresh = clientPause ? -0.25 : -1.0; 
        if (dt < lagThresh)
        {
            timeAcceleration = 0; 
            clientPause = true;
        }
        else
        {
            clientPause = false;
        }
    }
    else
    {
        stream >> mfSimTime;
        dateTime << stream;
        stream >> timeAcceleration;
        stream >> isMultiplayerGameStarted;
    }
    /**
    * 
    gameTime += fdt;
    gameDateTime.addTime(fdt*dateTimeScale);
    */
}


void tcSimState::LogWeaponDamage(tcGameObject* target, tcWeaponObject* weapon, const Damage& damage, float damageFraction)
{
    if (!damageLog.IsOpen())
    {
        wxASSERT(false);
        return;
    }

    if ((target == 0) || (weapon == 0))
    {
        wxASSERT(false);
        return;
    }

    wxString line;

    //line.Printf("TargetId, TargetClass, TargetClassId, WeaponClass, WeaponClassId, DamageFraction, blast_psi, xDet, yDet, zDet, rangeDet_m\n");
    
    float rangeDet_m = 1000.0f * weapon->mcKin.RangeToKmAlt(target->mcKin);

    line.Printf("%s, %s, %d, %d, %d, "
                "%f, %f, %f, %f, %f, %d, "
                "%f, %f, %f, "
                "%f, %f, %f, %f\n",
        target->mzClass.c_str(), weapon->mzClass.c_str(), target->mnID, target->mpDBObject->mnKey,  weapon->GetDBObject()->mnKey,
        damageFraction, damage.blast_psi, damage.explosive_kg, damage.fragHits, damage.fragEnergy_J, damage.isPenetration, 
        damage.kinetic_J, damage.thermal_J_cm2, damage.waterBlast_psi, 
        0.0, 0.0, 0.0, rangeDet_m);

    damageLog.WriteString(line.c_str());
}


/**
* Saves game state to python scenario file
*/
void tcSimState::SaveToPython(const std::string& scenarioName)
{
	tcScenarioLogger logger(scenarioName);

    logger.BuildScenarioFile();

	logger.WriteAll();
}

/**
* Saves sim time and date-time to stream
*/
void tcSimState::SaveTimeToStream(tcStream& stream)
{
    stream << mfSimTime;
    dateTime >> stream;
    stream << timeAcceleration;
    stream << isMultiplayerGameStarted;
}


/**
* scenname does not include file path or extension
*/
int tcSimState::Serialize(tcString scenname, bool mbLoad) 
{
    tcFile file;
    tcString filepath;

    filepath = SCENARIO_PATH;
    filepath += "\\";
    filepath += scenname;
    filepath += ".dat";

    /* load SimState from file */
    if (mbLoad) 
    {
        Clear();
        if (file.Open(filepath.GetBuffer(),tcFile::modeRead)==0) 
        {
            WTL("tcSimState::Serialize - failed open scenario file");
            strcpy(msScenarioInfo.mzName,"FILE NOT FOUND");
            return false;
        }
        mcSensorMap.Serialize(file,true); // load mcSensorMap from file
        file.Read(&mfSimTime,sizeof(mfSimTime));
        file.Read(&mfLastSensorUpdate,sizeof(mfLastSensorUpdate));
        file.Read(&mfLastSensorAgeOut,sizeof(mfLastSensorAgeOut));
        file.Read(&mfLastTileAgeOut,sizeof(mfLastTileAgeOut));

        // load game objects
        tcGameObject *pGameObj;
        long nSize;

        file.Read(&nSize,sizeof(nSize));
        for (long i=0;i<nSize;i++) 
        {
            long nDBKey;
            file.Read(&nDBKey,sizeof(nDBKey));
            tcDatabaseObject* pDatabaseObj = mpDatabase->GetObject(nDBKey);
            pGameObj = CreateGameObject(pDatabaseObj);
            if (pGameObj == NULL) 
            {
                WTL("tcSimState::Serialize - corrupt scenario file\n");
                file.Close();
                strcpy(msScenarioInfo.mzName,"FILE CORRUPT");
                return false;
            }
            pGameObj->Serialize(file,true);
            AddPlatformWithKey(pGameObj,pGameObj->mnID);
        }
        // read scenario info
        file.Read(msScenarioInfo.mzDescription, SCEN_STRING_LENGTH);
        strcpy(msScenarioInfo.mzName,scenname.GetBuffer());
        msScenarioInfo.mbLoaded = true;

        PrintToFile(tcString("log\\serialize_load.txt"));
    }
    /* save to file */
    else
    {   
        PrintToFile(tcString("log\\serialize_save.txt"));
        if (file.Open(filepath.GetBuffer(),tcFile::modeCreate|tcFile::modeWrite)==0) 
        {
            WTL("tcSimState::Serialize - failed to create save scenario file");
            return false;
        }
        mcSensorMap.Serialize(file,false);
        file.Write(&mfSimTime,sizeof(mfSimTime));
        file.Write(&mfLastSensorUpdate,sizeof(mfLastSensorUpdate));
        file.Write(&mfLastSensorAgeOut,sizeof(mfLastSensorAgeOut));
        file.Write(&mfLastTileAgeOut,sizeof(mfLastTileAgeOut));

        // save game objects
        tcGameObject *pGameObj;
        long cmappos = maPlatformState.GetStartPosition();
        long nSize = maPlatformState.GetCount();
        long nKey;

        file.Write(&nSize,sizeof(nSize));
        for (long i=0;i<nSize;i++) 
        {
            maPlatformState.GetNextAssoc(cmappos,nKey,pGameObj);
            file.Write(&pGameObj->mnDBKey,sizeof(pGameObj->mnDBKey));
            pGameObj->Serialize(file,false);
        }
        // write scenario info
        file.Write(msScenarioInfo.mzDescription, SCEN_STRING_LENGTH);
    }

    file.Close();
    return true;
}

/// Sets tcDateTime object for environment date (sky, etc)
void tcSimState::SetDateTime(const tcDateTime& dt) 
{
    dateTime = dt;
} 

/**
* Sets multiplayer mode to MM_OFF, the default single-player state.
* Loads random scenario for the play button default.
*/
void tcSimState::SetMultiplayerOff()
{
    multiplayerMode = MM_OFF;

    tcGameObject::SetClientMode(false);
    tcCommandObject::SetClientMode(false);
	tcControllableObject::SetBypassControlCheck(true);

	if (tcOptions::Get()->OptionStringExists("UsePositionRegistry"))
    {
		if (positionRegistry == 0)
		{
			positionRegistry = new tcPositionRegistry;
		}
    }
}

/**
* Sets multiplayer mode to MM_CLIENT. In client mode sim state only
* performs updates necessary to predict game state in between server
* updates to reduce apparent lag. The real work is done on the server.
* Client updates are for visual smoothness only.
*
* Creates a single sensor map for client player's sensor tracks. 
* Client player alliance is always set to 1 (for now).
*/
void tcSimState::SetMultiplayerClient()
{
    Clear();
    mcSensorMap.CreateMapForAlliance(mpUserInfo->GetOwnAlliance()); 
    multiplayerMode = MM_CLIENT;
    tcGameObject::SetClientMode(true);
    tcCommandObject::SetClientMode(true);
	tcControllableObject::SetBypassControlCheck(false);

	if (positionRegistry)
	{
		delete positionRegistry;
		positionRegistry = 0;
	}
}

void tcSimState::SetMultiplayerGameStarted(bool state)
{
    if (multiplayerMode == MM_SERVER)
    {
        isMultiplayerGameStarted = state;
    }
    else
    {
        wxASSERT(false);
    }
}

/**
* Sets multiplayer mode to MM_SERVER. Server mode performs all of
* the simulation done in single player / MM_OFF mode.
*/
void tcSimState::SetMultiplayerServer()
{
    multiplayerMode = MM_SERVER;

    tcGameObject::SetClientMode(false);
    tcCommandObject::SetClientMode(false);
	tcControllableObject::SetBypassControlCheck(true);

	if (tcOptions::Get()->OptionStringExists("UsePositionRegistry"))
    {
		if (positionRegistry == 0)
		{
			positionRegistry = new tcPositionRegistry;
		}
    }

    PreloadScenarioDatabase(); // in case we play the currently loaded scen

}

const char* tcSimState::GetScenarioDescription() const
{
	return msScenarioInfo.mzDescription;
}

void tcSimState::SetScenarioDescription(const std::string& s)
{
    if (s.size() < SCEN_STRING_LENGTH)
    {
        strcpy(msScenarioInfo.mzDescription,s.c_str());
    }
    else
    {
        strncpy(msScenarioInfo.mzDescription,s.c_str(),SCEN_STRING_LENGTH-1);
    }
}

void tcSimState::SetScenarioLoaded(bool state)
{
    msScenarioInfo.mbLoaded = state;
}

const char* tcSimState::GetScenarioName() const
{
    return msScenarioInfo.mzName;
}

void tcSimState::SetScenarioName(const std::string& s)
{
    if (s.size() < 128)
    {
        strcpy(msScenarioInfo.mzName,s.c_str());
    }
    else
    {
        strncpy(msScenarioInfo.mzName,s.c_str(),127);
    }
}

/**
* Sets time acceleration for simulation.
* Currently an info-only parameter, but will be changed
* in the future to give simstate control over its own
* time acceleration vs. having this at the main game loop level.
*/
void tcSimState::SetTimeAcceleration(long accel)
{
    timeAcceleration = accel;
}

void tcSimState::StartDamageLog(const std::string& fileName)
{
    if (damageLog.IsOpen()) return; // already open

    damageLog.Open(fileName.c_str(),  tcFile::modeWrite | tcFile::modeText);

    wxString line;
    line.Printf("TargetClass, WeaponClass, TargetId, TargetClassId, WeaponClassId, "
                "DamageFraction, blast_psi, explosive_kg, fragHits, fragEnergy_J, isPen, "
                "kinetic_J, thermal_J_cm2, waterBlast_psi, "
                "xDet, yDet, zDet, rangeDet_m\n");

    damageLog.WriteString(line.c_str());

    logDamage = true;
}

/**
*
*/
void tcSimState::Clear() 
{
    msScenarioInfo.mbLoaded = false;
    strcpy(msScenarioInfo.mzDescription,"");
    strcpy(msScenarioInfo.mzName, "NONE SELECTED");
    maPlatformState.RemoveAll();
    if (positionRegistry)
    {
        positionRegistry->RemoveAll();
    }

    mcSensorMap.Clear();
    flightportPlatforms.clear();
    landingPlatforms.clear();
    lastLandingStateUpdate = 0;
    goalTracker->Clear();

    mfSimTime = 0;
    mfLastSensorUpdate = 0;
    mfLastSensorAgeOut = 0;
    mfLastTileAgeOut = 0;
    clientPause = false;
    timeAcceleration = 0;
    isMultiplayerGameStarted = false;

    objectNameMap.clear();
    captiveObjectMap.clear();

    tcSonarEnvironment::Get()->Clear();
    tcLOS::Get()->Clear();

    tcAllianceInfo::Get()->Clear();
}

/**
*
*/
tcSimState::tcSimState() 
: dateTime(2000,4,10,5,0,0),
  multiplayerMode(MM_OFF),
  timeAcceleration(0),
  positionRegistry(0),
  clientPause(false),
  lastLandingStateUpdate(0),
  multiplayerTimeLag_s(0),
  logDamage(false),
  weaponTester(0),
  isMultiplayerGameStarted(false)
{ 
    wxDateTime t = wxDateTime::Now();
    srand(t.GetSecond());


    mpCommandInterface = NULL;
    mpDatabase = NULL;
    mpMapData = NULL;
    mpPythonInterface = NULL;
    mpUserInfo = NULL;
    mfSimTime = 0;
    mfLastSensorUpdate = 0;
    mfLastSensorAgeOut = 0;
    mfLastTileAgeOut = 0;
    strcpy(msScenarioInfo.mzName,"NONE SELECTED");
    strcpy(msScenarioInfo.mzDescription,"");
    msScenarioInfo.mbLoaded = false;
	goalTracker = tcGoalTracker::Get();

    tcGoal::AttachSimState(this);
    tcLauncher::AttachSimState(this);
    tcLauncherState::AttachSimState(this);
    
    tcSensorState::AttachSimState(this);
    tcSensorState::AttachLOS();
    tcSensorState::InitErrorFactor();

    tcGameObjIterator::SetSimState(this);
    tcGameObject::SetSimState(this);
    tcSensorMapTrack::AttachSimState(this);

    mcSensorMap.CreateMapForAlliance(1);
    mcSensorMap.CreateMapForAlliance(2);
    //mcSensorMap.Test();

    if (tcOptions::Get()->OptionStringExists("UsePositionRegistry"))
    {
        positionRegistry = new tcPositionRegistry;
        fprintf(stdout, "Using position registry\n");
    }

#ifdef _DEBUG
    tcString s;
    s.Format("tcGameObject size: %d bytes",sizeof(tcGameObject));
    WTL(s.GetBuffer());

    s.Format("tcSurfaceObject size: %d bytes",sizeof(tcSurfaceObject));
    WTL(s.GetBuffer());
   
    s.Format("tcMissileObject size: %d bytes",sizeof(tcMissileObject));
    WTL(s.GetBuffer());

    s.Format("tcSimState size: %d kB",sizeof(tcSimState)/1024);
    WTL(s.GetBuffer());
#endif

    //TestDamageModel();

    //GaussianRandom::Get()->WriteTableToFile("randf.csv");

}

/**
*
*/
tcSimState::~tcSimState() 
{
    maPlatformState.RemoveAll();

    if (positionRegistry) delete positionRegistry;

    if (damageLog.IsOpen())
    {
        damageLog.Close();
    }
}


