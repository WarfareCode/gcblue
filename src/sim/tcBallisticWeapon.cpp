/** 
**  @file tcBallisticWeapon.cpp
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

#include "tcBallisticWeapon.h"
#include "tcBallisticDBObject.h"
#include "common/tcStream.h"
#include "common/tcObjStream.h"
#include "common/tcGameStream.h"
#include "database/tcPlatformDBObject.h"
#include "tc3DModel.h"
//#include "tcParticleEffect.h"
#include "tcLauncher.h"
#include "tcSimState.h"
#include "tc3DPoint.h"
#include "tcBallisticMissile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/**
* Load state from update stream
*/
tcUpdateStream& tcBallisticWeapon::operator<<(tcUpdateStream& stream)
{
	tcWeaponObject::operator<<(stream);

	stream >> vxy_mps;
	stream >> vz_mps;

	return stream;
}

/**
* Save state to update stream
*/
tcUpdateStream& tcBallisticWeapon::operator>>(tcUpdateStream& stream)
{
	tcWeaponObject::operator>>(stream);

	stream << vxy_mps;
	stream << vz_mps;

	return stream;
}

/**
* Load state from game stream
*/
tcGameStream& tcBallisticWeapon::operator<<(tcGameStream& stream)
{
	tcWeaponObject::operator<<(stream);

	stream >> vz_mps;
	stream >> vxy_mps;
    stream >> distFromLaunch_m;
    targetPos << stream;

	return stream;
}

/**
* Save state to game stream
*/
tcGameStream& tcBallisticWeapon::operator>>(tcGameStream& stream)
{
	tcWeaponObject::operator>>(stream);

	stream << vz_mps;
	stream << vxy_mps;
    stream << distFromLaunch_m;
    targetPos >> stream;

	return stream;
}

/**
* @return targeting solution or (0,0,0) if targetId not valid
*/
const GeoPoint& tcBallisticWeapon::CalculateGunSolution(long targetId)
{
    static GeoPoint targetDatum;
    tcTrack targetTrack;
    tcTrack interceptTrack;

    // if the launcher has a target, set launch az based on projected position
    // cheat with truth track
    if (simState->GetTruthTrack(targetId, targetTrack))
    {
        float range_m = 1000.0f * mcKin.RangeToKm(targetTrack);
        float dz_m = targetTrack.mfAlt_m - mcKin.mfAlt_m;
        float tti_s;
        mpDBObject->GetGunneryElevation(range_m, dz_m, tti_s);
        interceptTrack = targetTrack.PredictAhead(tti_s);

        if (targetTrack.mfSpeed_kts > 0)
        {
            // second iteration
            range_m = 1000.0f * mcKin.RangeToKm(interceptTrack);
            dz_m = interceptTrack.mfAlt_m - mcKin.mfAlt_m;
            mpDBObject->GetGunneryElevation(range_m, dz_m, tti_s);
            interceptTrack = targetTrack.PredictAhead(tti_s);

            // third iteration
            range_m = 1000.0f * mcKin.RangeToKm(interceptTrack);
            dz_m = interceptTrack.mfAlt_m - mcKin.mfAlt_m;
            mpDBObject->GetGunneryElevation(range_m, dz_m, tti_s);
            interceptTrack = targetTrack.PredictAhead(tti_s);

            range_m = 1000.0f * mcKin.RangeToKm(interceptTrack);
            dz_m = interceptTrack.mfAlt_m - mcKin.mfAlt_m;
            mpDBObject->GetGunneryElevation(range_m, dz_m, tti_s);
            interceptTrack = targetTrack.PredictAhead(tti_s);
        }

        targetDatum.mfLon_rad = interceptTrack.mfLon_rad;
        targetDatum.mfLat_rad = interceptTrack.mfLat_rad;
        targetDatum.mfAlt_m = interceptTrack.mfAlt_m;
    }
    else
    {
        targetDatum.Set(0, 0, 0);
    }

    return targetDatum;
}

/**
* Initializes ballistic weapon state for launch from game object.
* Adds self to simulation
*
* @param obj launching game object
* @param launcher index of launcher
*/
void tcBallisticWeapon::LaunchFrom(tcGameObject* obj, unsigned nLauncher)
{
	tcLauncher virtualLauncher; // for ballistic missile deployment
	virtualLauncher.mnTargetID = -1;
	virtualLauncher.pointingAngle = 0;
	virtualLauncher.pointingElevation = 0;
	virtualLauncher.firingArc_deg = 0;
	virtualLauncher.mfTimeToReady = 0;

	tcLauncher* pLauncher = &virtualLauncher;

    if (tcPlatformObject* platObj = dynamic_cast<tcPlatformObject*>(obj))
	{
		tc3DPoint launcherPos = platObj->mpDBObject->GetLauncherPosition(nLauncher);
		GeoPoint pos = obj->RelPosToLatLonAlt(launcherPos.x, launcherPos.y,
			launcherPos.z);
		mcKin.mfLon_rad = pos.mfLon_rad;
		mcKin.mfLat_rad = pos.mfLat_rad;
		mcKin.mfAlt_m = pos.mfAlt_m;
        
        pLauncher = obj->GetLauncher(nLauncher);
	}
	else if (tcBallisticMissile* bmissile = dynamic_cast<tcBallisticMissile*>(obj))
	{
		mcKin.mfLon_rad = obj->mcKin.mfLon_rad;
		mcKin.mfLat_rad = obj->mcKin.mfLat_rad;
		mcKin.mfAlt_m = obj->mcKin.mfAlt_m;

        virtualLauncher.msDatum = bmissile->GetTargetDatum();
        virtualLauncher.mnTargetID = bmissile->GetIntendedTarget();
        virtualLauncher.pointingAngle = 0;
	    virtualLauncher.pointingElevation = 0;
	}
	else if (tcBallisticWeapon* ballistic = dynamic_cast<tcBallisticWeapon*>(obj))
	{
		mcKin.mfLon_rad = obj->mcKin.mfLon_rad;
		mcKin.mfLat_rad = obj->mcKin.mfLat_rad;
		mcKin.mfAlt_m = obj->mcKin.mfAlt_m;

        virtualLauncher.msDatum = targetPos;
        virtualLauncher.mnTargetID = ballistic->GetIntendedTarget();
        virtualLauncher.pointingAngle = 0;
	    virtualLauncher.pointingElevation = 0;
	}
	else
	{
		mcKin.mfLon_rad = obj->mcKin.mfLon_rad;
		mcKin.mfLat_rad = obj->mcKin.mfLat_rad;
		mcKin.mfAlt_m = obj->mcKin.mfAlt_m;
	}

	mcKin.mfSpeed_kts = obj->mcKin.mfSpeed_kts;
	mcKin.mfHeading_rad = obj->mcKin.mfHeading_rad;

    /* use parent platform climb angle for pitch, since pitch determines vertical
	** velocity for ballistic objects. For gravity bombs we want zero initial vertical 
	** velocity if parent plaform is in level flight.
	*/
	mcKin.mfPitch_rad = obj->mcKin.mfClimbAngle_rad; 
	mcKin.mfClimbAngle_rad = mcKin.mfPitch_rad;

	mfStatusTime = obj->mfStatusTime;
	mcKin.mfHeading_rad += pLauncher->pointingAngle;
	mcKin.mfPitch_rad += pLauncher->pointingElevation;

    distFromLaunch_m = 0;

	// For gun round, set az and el to intercept target datum
    switch (mpDBObject->ballisticType)
    {
    case tcBallisticDBObject::GUN_ROUND:
        {
            GeoPoint targetDatum = CalculateGunSolution(pLauncher->mnTargetID);
            if (!targetDatum.IsZero())
            {
                pLauncher->msDatum = targetDatum; // to keep launcher from auto-firing as target moves out of range
                SetFuseMode(TARGET_FUSE); // cheat a little more here, use target fuse if has a target
            }
            else
            {
                targetDatum = pLauncher->msDatum;
            }

            mcKin.mfSpeed_kts = C_MPSTOKTS * mpDBObject->launchSpeed_mps;
            mcKin.mfHeading_rad = mcKin.HeadingToGeoRad(&targetDatum);

            float range_m = 1000.0f * mcKin.RangeToKm(&targetDatum);
            float dz_m = targetDatum.mfAlt_m - mcKin.mfAlt_m;
            float tti_s;

            mcKin.mfPitch_rad = mpDBObject->GetGunneryElevation(range_m, dz_m, tti_s);

            // add some error to launch az and el
            mcKin.mfPitch_rad += randfc(mpDBObject->angleError_rad);
            mcKin.mfHeading_rad += randfc(mpDBObject->angleError_rad);

            // limit launch heading to firing arc
            float mountAz_rad = pLauncher->mountPointingAngle + obj->mcKin.mfHeading_rad;
            float dh_rad = mcKin.mfHeading_rad - mountAz_rad;
            dh_rad += C_TWOPI*float(dh_rad < -C_PI) - C_TWOPI*float(dh_rad > C_PI);
            float halfFiringArc_rad = (0.5f * C_PIOVER180) * pLauncher->firingArc_deg;
            if (dh_rad > halfFiringArc_rad)
            {
                mcKin.mfHeading_rad = mountAz_rad + halfFiringArc_rad;
            }
            else if (dh_rad < -halfFiringArc_rad)
            {
                mcKin.mfHeading_rad = mountAz_rad - halfFiringArc_rad;
            }

            mcKin.mfClimbAngle_rad = mcKin.mfPitch_rad;
            /*
            fprintf(stdout, "Gun launched from (%.3f, %.3f) to (%.3f, %.3f), "
            "range %.1f m, spd %.1f m/s\n",
            obj->mcKin.mfLat_rad * C_180OVERPI, obj->mcKin.mfLon_rad * C_180OVERPI,
            targetDatum.mfLat_rad * C_180OVERPI, targetDatum.mfLon_rad * C_180OVERPI,
            range_m, mpDBObject->launchSpeed_mps);
            */
        }
        break;
    case tcBallisticDBObject::AUTO_CANNON:
        {
            if (pLauncher->IsAutoPoint())
            {
                // not adding platform speed to avoid complicated intercept calculations
                mcKin.mfSpeed_kts = C_MPSTOKTS * mpDBObject->launchSpeed_mps;
                /* get intercept az and el to target, if target is bad then launch
                ** at 0 deg az, 45 deg el, and write error */
                tcTrack targetTrack;
                float launchAz_rad = 0;
                float launchEl_rad = 1.0f;
                float tti_s;
                float range_km;
                if (simState->GetTruthTrack(pLauncher->mnTargetID, targetTrack))
                {
                    mcKin.GetInterceptData3D(targetTrack, launchAz_rad, launchEl_rad, tti_s, range_km);
                }
                else
                {
                    SelfDestruct(); // should block launch instead 
                }

                mcKin.mfHeading_rad = launchAz_rad;
                mcKin.mfPitch_rad = launchEl_rad;

                mcKin.mfHeading_rad += randfc(mpDBObject->angleError_rad);
                mcKin.mfPitch_rad += randfc(mpDBObject->angleError_rad);

                mcKin.mfClimbAngle_rad = mcKin.mfPitch_rad;
            }
            else // assume fixed mounting in forward position
            {
                mcKin.mfSpeed_kts += C_MPSTOKTS * mpDBObject->launchSpeed_mps;
            }

            SetFuseMode(TARGET_FUSE);
        }
        break;
    case tcBallisticDBObject::SMART_BOMB:
        {
            targetPos = pLauncher->msDatum;
            float northError_m = 0.707 * GaussianRandom::Get()->randn_fast() * mpDBObject->smartError_m;
            float eastError_m = 0.707 * GaussianRandom::Get()->randn_fast() * mpDBObject->smartError_m;

            targetPos.mfLat_rad += C_MTORAD * northError_m;
            targetPos.mfLon_rad += C_MTORAD * eastError_m / cosf(targetPos.mfLat_rad);
        }
        break;
    case tcBallisticDBObject::GRAVITY_BOMB:
        {
            // override ready time for dumb bombs to make sure group is tight
            pLauncher->mfTimeToReady = std::max(pLauncher->mfTimeToReady, 0.05f);

			// 19NOV2010 add in random error so we can model cluster bombs
			mcKin.mfHeading_rad += randfc(mpDBObject->angleError_rad);
			mcKin.mfPitch_rad += randfc(mpDBObject->angleError_rad);
			mcKin.mfClimbAngle_rad = mcKin.mfPitch_rad;
        }
        break;
    case tcBallisticDBObject::CM_ROUND:
        {
            mcKin.mfSpeed_kts = C_MPSTOKTS * mpDBObject->launchSpeed_mps;
        }
        break;
    }

    mcKin.mfYaw_rad = mcKin.mfHeading_rad; // 9DEC2011 was having problem where autocannon local coordinates for hit calculation incorrect because this was missing

    wxString s = wxString::Format("Ball %d-%d", obj->mnID, launchedCounter++);
    mzUnit = s.c_str();    
        
	SetAlliance(obj->GetAlliance());     



	simState->AddPlatform(static_cast<tcGameObject*>(this));

	// Set intended target (has to be done after alliance and id is set).
	// This is a tcWeaponObject method
	SetIntendedTarget(pLauncher->mnTargetID);

}



/**
*
*/
void tcBallisticWeapon::Update(double afStatusTime)
{
	float dt_s = (float)(afStatusTime - mfStatusTime);

	mfStatusTime = afStatusTime;

	wxASSERT(mpDBObject);

    if (dt_s <= 0) return;


	// initialize local kinematic state variables if vxy_mps == 0
	if (vxy_mps == 0)
	{
		float v = C_KTSTOMPS * mcKin.mfSpeed_kts;
		vz_mps = v * sinf(mcKin.mfPitch_rad);
		float cospitch = cosf(mcKin.mfPitch_rad);
		vxy_mps = v * cospitch;
	}

    float vz_prev = vz_mps; // for trapezoidal integration

    // point defense and autocannon rounds magically defy gravity
    // apply gravity for gravity bomb model only
    if (IsGravityBomb() || IsGunRound())
    {
	    vz_mps += -C_G * dt_s;
    }

    if (mpDBObject->ballisticType == tcBallisticDBObject::SMART_BOMB)
    {
        UpdateSmartBombMotion(dt_s);
    }


    float distxy_m = dt_s * vxy_mps;
	float dist = C_MTORAD * distxy_m;
    float dlon = dist * sinf(mcKin.mfHeading_rad) / cosf(mcKin.mfLat_rad);
    float dlat = dist * cosf(mcKin.mfHeading_rad);
	
    if (IsAutocannon())
    {
        float distxyz_m = dt_s * C_KTSTOMPS * mcKin.mfSpeed_kts;
        distFromLaunch_m += distxyz_m;
    }
    else
    {
        distFromLaunch_m += distxy_m;
    }

	mcKin.mfLon_rad += dlon;
	mcKin.mfLat_rad += dlat;
	mcKin.mfAlt_m += (vz_mps + vz_prev) * dt_s * 0.5f;

	mcKin.mfPitch_rad = atan2f(vz_mps, vxy_mps);
	mcKin.mfClimbAngle_rad = mcKin.mfPitch_rad;
	mcKin.mfSpeed_kts = C_MPSTOKTS * sqrtf(vxy_mps*vxy_mps + vz_mps*vz_mps);

    HandlePoleWrap();

    Update3D();

	if (clientMode) return;

    if ((mpDBObject->maxRange_km > 0) && 
        (distFromLaunch_m > 1000.0f * mpDBObject->maxRange_km))
    {
        if ((mpDBObject->payloadClass.size() == 0) || payloadDeployed)
        {
            SelfDestruct();
        }
        else
        {
            DeployPayload();
        }
    }

    if (mcKin.mfAlt_m < -1.0f)
    {
        SelfDestruct();
    }

    /*** check for impact ***/
    switch (mpDBObject->ballisticType)
    {
    case tcBallisticDBObject::GUN_ROUND:
        UpdateTargetFuse();
		UpdateGroundFuse();
        break;
    case tcBallisticDBObject::GRAVITY_BOMB:
        UpdateGroundFuse();
        break;
    case tcBallisticDBObject::AUTO_CANNON:
        UpdateAutocannon();
        break;
    case tcBallisticDBObject::SMART_BOMB:
        UpdateSmartBombFuse();
        break;
    case tcBallisticDBObject::CM_ROUND:
        break;
    default:
        fprintf(stderr, "tcBallisticWeapon::Update - Bad BallisticType field (%s)\n",
            mpDBObject->mzClass.c_str());
        SelfDestruct();
        break;
    }



}

/**
* "Ground fuse" refers to detonation at fixed altitude above ground or with impact with
* ground
*
* Enhance this in future by testing for collision with ground objects for penetrating bombs
*/
void tcBallisticWeapon::UpdateGroundFuse()
{
    // check for impact with ground
    float terrainHeight_m = mcTerrain.mfHeight_m;
    if (terrainHeight_m < 0) terrainHeight_m = 0;

    // interpret detonation range as altitude of detonation for bombs
    float detAlt_m = mpDBObject->detonationRange_m;

    float dz =  terrainHeight_m + detAlt_m - mcKin.mfAlt_m; // height above ground or sea level

    float t_impact = dz / vz_mps;

    if ((vz_mps > 0)||(t_impact > 0.03f)) return;

	// this for "cluster bomb" logic
	if (mpDBObject->payloadClass.size() > 0)
	{
		if (!payloadDeployed)
		{
			DeployPayload();
		}
		else
		{
			SelfDestruct();
		}
		return;
	}

    bool directHitOccurred = false;
    // check for impact with nearby objects if detonation range of bomb is zero, and this isn't a cluster bomb
	if ((mpDBObject->detonationRange_m == 0) && (mpDBObject->clusterCount == 0))
    {
        directHitOccurred = CheckGravityBombImpact();
    }


    if (!directHitOccurred)
    {
        Detonate(t_impact);
    }
    else
    { // already detonated
    }
    
}

/**
* Check if bomb has collided with any objects close to impact point
* @return true if bomb has directly collided
*/
bool tcBallisticWeapon::CheckGravityBombImpact()
{
    const float checkRange_m = 500.0f;

    float rLat = checkRange_m * C_MTORAD;
    float rLon = rLat / cosf(mcKin.mfLat_rad);

    tcRect checkRegion;
    float west = mcKin.mfLon_rad - rLon;
    float east = mcKin.mfLon_rad + rLon;
    float north = mcKin.mfLat_rad + rLat;
    float south = mcKin.mfLat_rad - rLat;
    if (west < -C_PI) west += C_TWOPI;
    if (east >= C_PI) east -= C_TWOPI;
    checkRegion.Set(west, east, south, north);

    std::vector<long> nearbyPlatsAll;
    simState->GetPlatformsWithinRegion(nearbyPlatsAll, &checkRegion);

	// remove own platform from list 9JUL2011
	std::vector<long> nearbyPlats;
	size_t nPlatsAll = nearbyPlatsAll.size();
	for (size_t n=0; n<nPlatsAll; n++)
	{
		long id_n = nearbyPlatsAll[n];
		if (id_n != this->mnID) nearbyPlats.push_back(id_n);
	}

    int nPlats = (int)nearbyPlats.size();

    long initialTarget = intendedTarget;

    for (int idx = 0; idx < nPlats; idx++)
    {
        intendedTarget = nearbyPlats[idx];
        UpdateTargetFuse();
        if (IsDirectHit()) return true;
    }

    // restore intendedTarget if no direct hit
    intendedTarget = initialTarget;
    return false;
}


/**
* Model for point defense and aircraft cannons
* "Detonate" weapon when burst reaches closest point to target
*/
void tcBallisticWeapon::UpdateAutocannon()
{
    const float checkInterceptRange = 0.5f;
    const float tminDet_s = 0.05f;

    if (tcGameObject* target = simState->GetObject(intendedTarget))
    {
        float range_km = mcKin.RangeToKmAlt(target->mcKin);

        if (range_km <= checkInterceptRange)
        {
            float dx, dy, dz;
            float dt_s = target->mcKin.CalculateCollisionPoint(mcKin, dx, dy, dz);
            if (dt_s > tminDet_s) return;

            Detonate(dt_s); // not really a detonation, but a signal for simstate to check for hit
        }
        else
        {
            fuseHasTriggered = false;
        }
    }
    else
    {
    }
}


void tcBallisticWeapon::UpdateSmartBombFuse()
{
    const float checkDetonateRange = 0.2f;
    const float tminDet_s = 0.05f;

    float range_km = mcKin.RangeToKmAlt(targetPos.mfLon_rad, targetPos.mfLat_rad, targetPos.mfAlt_m);
    
    if (range_km > checkDetonateRange) return;
    

    CheckGravityBombImpact();
    if (IsDetonated()) return;


    // --- check for impact with ground ---
    float terrainHeight_m = mcTerrain.mfHeight_m;
    if (terrainHeight_m < 0) terrainHeight_m = 0;

    // interpret detonation range as altitude of detonation for bombs
    float detAlt_m = mpDBObject->detonationRange_m;

    float dz_ground =  terrainHeight_m + detAlt_m - mcKin.mfAlt_m; // height above ground or sea level

    float t_impact_ground = dz_ground / vz_mps;
    if (t_impact_ground <= tminDet_s)
    {
        Detonate(t_impact_ground);
        return;
    }
    // ---

}

void tcBallisticWeapon::UpdateSmartBombMotion(float dt_s)
{
    wxASSERT(mpDBObject->ballisticType == tcBallisticDBObject::SMART_BOMB);

    tcTrack groundTrack;

    groundTrack.mfAlt_m = targetPos.mfAlt_m;
    groundTrack.mfLon_rad = targetPos.mfLon_rad;
    groundTrack.mfLat_rad = targetPos.mfLat_rad;
    groundTrack.mfSpeed_kts = 0;

    
    
    float goalPitch_rad; // actually goal climb angle

    float range_km = mcKin.RangeToKm(groundTrack);
    float goalHeading_rad = mcKin.HeadingToTrack(groundTrack);

    if (range_km > 1.5f)
    {
        goalPitch_rad = mpDBObject->smartMaxClimb_rad;
    }
    else
    {
        float tti_s;
        float range_rad;
        mcKin.GetInterceptData3D(groundTrack, goalHeading_rad, 
            goalPitch_rad, tti_s, range_rad);
    }

    goalPitch_rad = std::min(mpDBObject->smartMaxClimb_rad, goalPitch_rad);


    float dh_rad = goalHeading_rad - mcKin.mfHeading_rad;
    radtoplusminuspi(dh_rad); // map dh_deg to [-180,180]

    float dh_max_rad = 0.05f * dt_s; // about 3 deg/sec
    dh_rad = std::max(dh_rad, -dh_max_rad);
    dh_rad = std::min(dh_rad, dh_max_rad);

    mcKin.mfHeading_rad += dh_rad;
    mcKin.mfPitch_rad += dt_s * (goalPitch_rad - mcKin.mfPitch_rad);
    mcKin.mfClimbAngle_rad = mcKin.mfPitch_rad;
    mcKin.mfYaw_rad = mcKin.mfHeading_rad;

    mcKin.mfSpeed_kts += 0.05f * dt_s * (650 - mcKin.mfSpeed_kts);

    float v = C_KTSTOMPS * mcKin.mfSpeed_kts;

    vz_mps = v * sinf(mcKin.mfPitch_rad);
    float cospitch = cosf(mcKin.mfPitch_rad);
    vxy_mps = v * cospitch;

}


/**
* Model for gun rounds for naval gunfire and hit-to-kill rounds
*/
void tcBallisticWeapon::UpdateTargetFuse()
{
    const float tminDet_s = 0.05f;

	if (HasPayload())
	{
		if ((vz_mps < 0) && (mcKin.mfAlt_m < mpDBObject->detonationRange_m))
		{
			if (!payloadDeployed)
			{
				DeployPayload();
			}
			else
			{
				SelfDestruct();
			}
		}
		return;
	}

    tcGameObject* target = simState->GetObject(intendedTarget);
    if (target == 0)
	{
		return;
	}

    float range_km = mcKin.RangeToKmAlt(target->mcKin);

	float checkInterceptRange_km = 0.001f * target->GetSpan(); // technically should be 0.5*, but just to be safe
	checkInterceptRange_km = std::max(checkInterceptRange_km, 0.1f);
	if (range_km > checkInterceptRange_km) return;

	if (mpDBObject->detonationRange_m == 0)
	{
		float dx, dy, dz, dt;
		Vec3 collisionPoint;
		float collisionRange_m;
		if (target->CalculateCollisionPoint(this, collisionPoint, dt, collisionRange_m))
		{
			if ((dt < -0.1f) || (dt > tminDet_s)) return; // defer until future time step

			collisionPoint = target->ConvertModelCoordinatesToWorld(collisionPoint);
			dx = collisionPoint.x;
			dy = collisionPoint.y;
			dz = collisionPoint.z;
			Detonate(dt);
            SetDirectHitTargetId(target->mnID);
			SetImpactPoint(Vec3(dx, dy, dz));
			return;
		}
	}
	else
	{
		float currentRange_m = 1000.0f * range_km;
		if (currentRange_m <= mpDBObject->detonationRange_m)
		{
			Detonate(0);
			SetDirectHitTargetId(-1);
			return;
		}

		// check for future closest point of approach
		float dx=0, dy=0, dz=0;
		float dt = target->mcKin.CalculateCollisionPoint(mcKin, dx, dy, dz);

		if (dt > tminDet_s) return; // defer until future time step
		float trueRange2 = dx*dx + dy*dy + dz*dz;

		if (trueRange2 <= mpDBObject->detonationRange_m * mpDBObject->detonationRange_m)
		{
			Detonate(dt);
			SetDirectHitTargetId(-1);
		}
	}

}

/**
*
*/
void tcBallisticWeapon::Clear()  
{  
	tcGameObject::Clear();

	vz_mps = 0;
	vxy_mps = 0;
    distFromLaunch_m = 0;
    targetPos.Set(0, 0, 0);
}


/**
*
*/
void tcBallisticWeapon::PrintToFile(tcFile& file)
{
	tcString s;
	tcWeaponObject::PrintToFile(file);

	s.Format(" Ballistic Weapon Object\n");
	file.WriteString(s.GetBuffer());
}

/**
*
*/
void tcBallisticWeapon::SaveToFile(tcFile& file) 
{
	tcWeaponObject::SaveToFile(file);
}

/**
*
*/
void tcBallisticWeapon::LoadFromFile(tcFile& file) 
{
	tcWeaponObject::LoadFromFile(file);
}

/**
*
*/
void tcBallisticWeapon::Serialize(tcFile& file, bool mbLoad) 
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

float tcBallisticWeapon::GetAngleErrorRad() const
{
    return mpDBObject->angleError_rad;
}

unsigned int tcBallisticWeapon::GetBurstCount() const
{
    return mpDBObject->burstCount;
}

float tcBallisticWeapon::GetDamageEffectRadius() const
{
	float weaponDamageEffectRadius = tcWeaponObject::GetDamageEffectRadius();
	
	if (!IsGravityBomb())
	{
		return weaponDamageEffectRadius;
	}
	else
	{
		return std::max(weaponDamageEffectRadius, mpDBObject->clusterEffectRadius_m);
	}
}

float tcBallisticWeapon::GetDistanceTraveled() const
{
    return distFromLaunch_m;
}

bool tcBallisticWeapon::IsGravityBomb() const
{
    return mpDBObject->IsGravityBomb();
}

bool tcBallisticWeapon::IsGunRound() const
{
    return mpDBObject->IsGunRound();
}

bool tcBallisticWeapon::IsAutocannon() const
{
    return mpDBObject->IsAutocannon();
}

bool tcBallisticWeapon::IsClusterBomb() const
{
	return (mpDBObject->IsGravityBomb() && (mpDBObject->clusterCount > 1));
}

bool tcBallisticWeapon::IsSmartBomb() const
{
    return mpDBObject->IsSmartBomb();
}

bool tcBallisticWeapon::IsRocket() const
{
	return mpDBObject->IsRocket();
}

/**
*
*/
tcBallisticWeapon::tcBallisticWeapon() 
: tcWeaponObject()
{
	Clear();

	mnModelType = MTYPE_BALLISTIC;
	mpDBObject = 0;
}

/**
* Copy constructor.
*/
tcBallisticWeapon::tcBallisticWeapon(const tcBallisticWeapon& o) 
: tcWeaponObject(o)
{
	mnModelType = MTYPE_BALLISTIC;
	mpDBObject = o.mpDBObject;
	vz_mps = o.vz_mps;
	vxy_mps = o.vxy_mps;
    distFromLaunch_m = o.distFromLaunch_m;
}

/**
* Constructor that initializes using info from database entry.
*/
tcBallisticWeapon::tcBallisticWeapon(tcBallisticDBObject* obj)
: tcWeaponObject(obj),
	vz_mps(0),
	vxy_mps(0),
    distFromLaunch_m(0)
{
	mnModelType = MTYPE_BALLISTIC;
	mpDBObject = obj;
}

/**
*
*/
tcBallisticWeapon::~tcBallisticWeapon() 
{
}

