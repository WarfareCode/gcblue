/**
**  @file tcTorpedoObject.cpp
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

#include "tcTorpedoObject.h"
#include "common/tcStream.h"
#include "common/tcObjStream.h"
#include "common/tcGameStream.h"
#include "database/tcPlatformDBObject.h"
#include "database/tcSonarDBObject.h"
#include "database/tcTorpedoDBObject.h"
#include "database/tcBallisticDBObject.h"
#include "tc3DModel.h"
//#include "tcParticleEffect.h"
#include "tcLauncher.h"
#include "tcMissileObject.h"
#include "tcBallisticWeapon.h"
#include "tcSimState.h"
#include "tc3DPoint.h"
#include "tcGameObjIterator.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/**
* Load state from update stream
*/
tcUpdateStream& tcTorpedoObject::operator<<(tcUpdateStream& stream)
{
	tcWeaponObject::operator<<(stream);

	stream >> goalHeading_rad;
	stream >> goalPitch_rad;
	stream >> goalSpeed_kts; 
	stream >> interceptTime;
	stream >> lastGuidanceUpdate;
	stream >> guidanceUpdateInterval;
	waypoint << stream;
	seeker->operator<<(stream);

	return stream;
}

/**
* Save state to update stream
*/
tcUpdateStream& tcTorpedoObject::operator>>(tcUpdateStream& stream)
{
	tcWeaponObject::operator>>(stream);

	stream << goalHeading_rad;
	stream << goalPitch_rad;
	stream << goalSpeed_kts; 
	stream << interceptTime;
	stream << lastGuidanceUpdate;
	stream << guidanceUpdateInterval;
	waypoint >> stream;
	seeker->operator>>(stream);

	return stream;
}

/**
* Load state from game stream
*/
tcGameStream& tcTorpedoObject::operator<<(tcGameStream& stream)
{
	int version = stream.GetVersionId();

	tcWeaponObject::operator<<(stream);
    tcSensorPlatform::operator<<(stream);

    stream >> goalDepth_m;
    stream >> goalHeading_rad;
    stream >> goalPitch_rad;
    stream >> goalSpeed_kts; 
    stream >> interceptTime;
    stream >> runTime;
	if (version > 8) {stream >> searchStartTime;}
    stream >> lastGuidanceUpdate;
    stream >> guidanceUpdateInterval;

    waypoint << stream;

    stream >> runToEnable_m;   
    stream >> ceiling_m;
    stream >> floor_m;
    stream >> isWireActive;
    stream >> autoWireUpdates;
    stream >> battery_kJ;
    stream >> searchHeading_rad;
    stream >> searchMode;

    stream.ReadCheckValue(263);

	return stream;
}

/**
* Save state to game stream
*/
tcGameStream& tcTorpedoObject::operator>>(tcGameStream& stream)
{
	int version = stream.GetVersionId();

	tcWeaponObject::operator>>(stream);
    tcSensorPlatform::operator>>(stream);

    stream << goalDepth_m;
    stream << goalHeading_rad;
    stream << goalPitch_rad;
    stream << goalSpeed_kts; 
    stream << interceptTime;
    stream << runTime;
	if (version > 8) {stream << searchStartTime;}
    stream << lastGuidanceUpdate;
    stream << guidanceUpdateInterval;

    waypoint >> stream;

    stream << runToEnable_m;   
    stream << ceiling_m;
    stream << floor_m;
    stream << isWireActive;
    stream << autoWireUpdates;
    stream << battery_kJ;
    stream << searchHeading_rad;
    stream << searchMode;

    stream.WriteCheckValue(263);

	return stream;
}



/**
* Initializes missile state for launch from game object.
* Adds self to simulation
*
* @param obj launching game object
* @param launcher index of launcher
*/
void tcTorpedoObject::LaunchFrom(tcGameObject* obj, unsigned nLauncher)
{
    isWireActive = false;
    autoWireUpdates = true;

    tcLauncher virtualLauncher; // for missile deployment
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

        if (mcKin.mfAlt_m <= 0)
        {
            tcSonarDBObject* sonar = mpDBObject->GetSeekerDBObj();
            
            mcKin.mfSpeed_kts = obj->mcKin.mfSpeed_kts + C_MPSTOKTS * mpDBObject->launchSpeed_mps;

            if ((sonar != 0) && ((sonar->isWakeHoming) || (sonar->mfMaxRange_km <= 0.1f)))
            {
                searchMode = SEARCH_STRAIGHT;
            }
            else
            {
                searchMode = SEARCH_SNAKE;
            }
            isWireActive = mpDBObject->wireGuidance;
        }
        else // air launched
        {
            mcKin.mfSpeed_kts = obj->mcKin.mfSpeed_kts;
            searchMode = randbool() ? SEARCH_LEFTCIRCLE : SEARCH_RIGHTCIRCLE;
        }
    }
	else if (tcMissileObject* missile = dynamic_cast<tcMissileObject*>(obj))
	{
		mcKin.mfLon_rad = obj->mcKin.mfLon_rad;
		mcKin.mfLat_rad = obj->mcKin.mfLat_rad;
		mcKin.mfAlt_m = obj->mcKin.mfAlt_m;

        virtualLauncher.pointingAngle = 0;
	    virtualLauncher.pointingElevation = 0;
		virtualLauncher.firingArc_deg = 0;
        virtualLauncher.runToEnable_m = 0;
        virtualLauncher.msDatum = missile->msWaypoint;
        virtualLauncher.runDepth_m = 0;
        virtualLauncher.preEnableSpeed_kts = 35.0f;
        virtualLauncher.ceiling_m = 0;
        virtualLauncher.floor_m = 0;
        virtualLauncher.usePassive = false;
        virtualLauncher.mnTargetID = missile->GetIntendedTarget();

        mcKin.mfSpeed_kts = obj->mcKin.mfSpeed_kts;
        searchMode = randbool() ? SEARCH_LEFTCIRCLE : SEARCH_RIGHTCIRCLE;
    }
    else if (tcTorpedoObject* torpedo = dynamic_cast<tcTorpedoObject*>(obj))
    {
		mcKin.mfLon_rad = obj->mcKin.mfLon_rad;
		mcKin.mfLat_rad = obj->mcKin.mfLat_rad;
		mcKin.mfAlt_m = obj->mcKin.mfAlt_m;

        virtualLauncher.pointingAngle = 0;
	    virtualLauncher.pointingElevation = 0;
        virtualLauncher.runToEnable_m = 1.0; // start enabled
        virtualLauncher.msDatum = torpedo->waypoint;
        virtualLauncher.runDepth_m = torpedo->goalDepth_m;
        virtualLauncher.preEnableSpeed_kts = 35.0f;
        virtualLauncher.ceiling_m = 0;
        virtualLauncher.floor_m = 0;
        virtualLauncher.usePassive = false;
        virtualLauncher.mnTargetID = torpedo->GetIntendedTarget();

        mcKin.mfSpeed_kts = obj->mcKin.mfSpeed_kts + C_MPSTOKTS * mpDBObject->launchSpeed_mps;
        searchMode = randbool() ? SEARCH_LEFTCIRCLE : SEARCH_RIGHTCIRCLE;
    }
	else if (tcBallisticWeapon* ballistic = dynamic_cast<tcBallisticWeapon*>(obj))
	{
		mcKin.mfLon_rad = obj->mcKin.mfLon_rad;
		mcKin.mfLat_rad = obj->mcKin.mfLat_rad;
		mcKin.mfAlt_m = obj->mcKin.mfAlt_m;
		mcKin.mfSpeed_kts = obj->mcKin.mfSpeed_kts + C_MPSTOKTS * mpDBObject->launchSpeed_mps;

        virtualLauncher.pointingAngle = 0;
	    virtualLauncher.pointingElevation = 0;
        virtualLauncher.runToEnable_m = 1.0; // start enabled
		virtualLauncher.msDatum.Set(mcKin.mfLon_rad, mcKin.mfLat_rad, 0);
        virtualLauncher.runDepth_m = 0;
        virtualLauncher.preEnableSpeed_kts = 35.0f;
        virtualLauncher.ceiling_m = 0;
        virtualLauncher.floor_m = 0;
        virtualLauncher.usePassive = false;
        virtualLauncher.mnTargetID = ballistic->GetIntendedTarget();

		if (ballistic->mpDBObject->payloadQuantity > 1) // assume this is a RBU type
		{
			virtualLauncher.pointingAngle += randfc(1.0f);
			virtualLauncher.pointingElevation += randfc(0.1f);
		}
	}
    else
    {
        wxASSERT(false);
        fprintf(stderr, "tcTorpedoObject::LaunchFrom - Launched from invalid platform (%s)\n",
            obj->GetName());
        return;
    }

	// added this for unguided torpedo modeling, 11 APR 2011
	if (seeker == 0) // straight run if no seeker
	{
		searchMode = SEARCH_STRAIGHT;
	}



	mcKin.mfHeading_rad = obj->mcKin.mfHeading_rad + pLauncher->pointingAngle;
	mcKin.mfPitch_rad = obj->mcKin.mfPitch_rad + pLauncher->pointingElevation;
	mcKin.mfClimbAngle_rad = mcKin.mfPitch_rad;

	waypoint = pLauncher->msDatum;

	goalHeading_rad = mcKin.HeadingToGeoRad(&waypoint);
    if (pLauncher->runToEnable_m > 0)
    {
        runToEnable_m = pLauncher->runToEnable_m;
    }
    else if (mpDBObject->payloadClass.size() == 0)
    {
        runToEnable_m = 500.0f * mcKin.RangeToKm(&waypoint); // enable halfway to waypoint
    }
    else // has payload
    {
        runToEnable_m = 1000.0f * mcKin.RangeToKm(&waypoint); // set run to enable to deploy payload at waypoint
    }

    if (pLauncher->runDepth_m > 0)
    {
        goalDepth_m = pLauncher->runDepth_m;
    }
    else if (mpDBObject->weaponType == tcTorpedoDBObject::TORPEDO)  // run depth not specified
    {
        // set run depth based on target classification
        tcTrack track;
        bool found = simState->mcSensorMap.GetTrack(pLauncher->mnTargetID, track, obj->GetAlliance());
        if (found && (track.mnClassification != 0))
        {
            if (track.IsSurface())
            {
                goalDepth_m = 5.0f;
            }
            else if (track.IsSub())
            {
                if ((track.mnFlags & TRACK_ALT_VALID) != 0)
                {
                    goalDepth_m = -track.mfAlt_m;
                }
                else
                {
					float terrain_m = tcMapData::Get()->GetTerrainHeight(
						C_180OVERPI*obj->mcKin.mfLon_rad, C_180OVERPI*obj->mcKin.mfLat_rad, obj->mfStatusTime);
					float maxDepth_m = std::min(-terrain_m - 15.0f, mpDBObject->maxDepth_m);
					maxDepth_m = std::max(maxDepth_m, 10.0f);
                    goalDepth_m = ((maxDepth_m - 10.0f) * randf()) + 10.0f; // randomly pick a depth
                }
            }
        }
        else
        {
			bool subValid = (mpDBObject->targetFlags & SUBSURFACE_TARGET) != 0;
			bool surfaceValid = (mpDBObject->targetFlags & SURFACE_TARGET) != 0;
			
			if (surfaceValid && !subValid)
			{
				goalDepth_m = 5.0f;
			}
			else
			{
				float terrain_m = tcMapData::Get()->GetTerrainHeight(
					C_180OVERPI*obj->mcKin.mfLon_rad, C_180OVERPI*obj->mcKin.mfLat_rad, obj->mfStatusTime);
				float maxDepth_m = std::min(-terrain_m - 15.0f, mpDBObject->maxDepth_m);
				maxDepth_m = std::max(maxDepth_m, 10.0f);
				goalDepth_m = ((maxDepth_m - 10.0f) * randf()) + 10.0f; // randomly pick a depth
			}
        }
    }
    else // mine or depth charge
    {
		float terrain_m = tcMapData::Get()->GetTerrainHeight(
			C_180OVERPI*obj->mcKin.mfLon_rad, C_180OVERPI*obj->mcKin.mfLat_rad, obj->mfStatusTime);
		float maxDepth_m = std::min(-terrain_m - 50.0f, mpDBObject->maxDepth_m);
		maxDepth_m = std::max(maxDepth_m, 100.0f);
		goalDepth_m = ((maxDepth_m - 100.0f) * randf()) + 100.0f; // randomly pick a depth
    }

    // keep off bottom and surface
    float bottom_m = -obj->mcTerrain.mfHeight_m;
    goalDepth_m = std::max(std::min(goalDepth_m, bottom_m - 15.0f), 5.0f);

    // limit speed to 10 - max_speed
    goalSpeed_kts = std::max(std::min(pLauncher->preEnableSpeed_kts, mpDBObject->maxSpeed_kts), 10.0f);

    ceiling_m = pLauncher->ceiling_m;
    
    if (floor_m > 0)
    {
        floor_m = pLauncher->floor_m;
    }
    else
    {
        floor_m = 8096.0f;
    }


    if (mpDBObject->weaponType == tcTorpedoDBObject::BOTTOM_MINE_CAPTOR)
    {
        if (mpDBObject->payloadClass.size() == 0)
        {
            fprintf(stderr, "tcTorpedoObject::LaunchFrom - CAPTOR has no payload (%s)\n",
                mpDBObject->mzClass.c_str());
            return;
        }
    }


	mfStatusTime = obj->mfStatusTime;

    battery_kJ = mpDBObject->battery_kJ; // start with full battery charge
	
	if (seeker != 0)
	{
		if (pLauncher->usePassive)
		{
			seeker->SetPassiveSonar();
		}
		else
		{
			seeker->SetActiveSonar();
		}

		seeker->mnMode = SSMODE_SEEKERSEARCH;
		seeker->SetActive(false); // override default for passive to always be active
	}

    wxString s = wxString::Format("Torp %d-%d", obj->mnID, launchedCounter++);
    mzUnit = s.c_str();      
        
	SetAlliance(obj->GetAlliance());     

	simState->AddPlatform(static_cast<tcGameObject*>(this));

	// Set intended target (has to be done after alliance and id is set).
	// This is a tcWeaponObject method
	SetIntendedTarget(pLauncher->mnTargetID);

}

/**
* @return time remaining in seconds based on current fuel consumption
*/
float tcTorpedoObject::RuntimeRemaining()
{
    return 0; // not implemented yet
}

/**
* For wire guidance updates
*/
void tcTorpedoObject::SetAltitude(float alt_m)
{
    goalDepth_m = -alt_m;
    autoWireUpdates = false;

    if (IsEditMode())
    {
        mcKin.mfAlt_m = alt_m;
    }
}

/**
*
*/
void tcTorpedoObject::SetHeading(float newHeading) 
{
    goalHeading_rad = newHeading;
    searchHeading_rad = goalHeading_rad;
    if (seeker != 0) seeker->mnMode = SSMODE_SEEKERSEARCH;
    autoWireUpdates = false; // don't do auto updates once manual update has occurred

    if (IsEditMode())
    {
        mcKin.mfHeading_rad = goalHeading_rad;
    }
}

/**
*
*/
void tcTorpedoObject::SetSpeed(float newSpeed) 
{
    goalSpeed_kts = newSpeed;
}

/**
*
*/
tcSonar* tcTorpedoObject::GetSensorState() 
{
    return seeker;
}



/**
* @returns sonar source level of object or, if object has active sonar on, maximum of source level of 
* target and max active sonar source level.
*/
float tcTorpedoObject::GetSonarSourceLevel(float az_deg) const
{
    float SLp = mpDBObject->GetSourceLevel(C_KTSTOMPS*goalSpeed_kts, -mcKin.mfAlt_m, az_deg);
	if (!IsEnsonifying()) return SLp;

	if (seeker->mpDBObj->SL > SLp)
	{
		return seeker->mpDBObj->SL;
	}
	else
	{
		return SLp;
	}
}

/**
*
*/
void tcTorpedoObject::Update(double afStatusTime)
{
	float dt_s = (float)(afStatusTime - mfStatusTime);
	mfStatusTime = afStatusTime;

    wxASSERT(mpDBObject);

    // air launched torpedoes drop into water first
    bool outOfWater = (mcKin.mfAlt_m > 0.0f);
    if (outOfWater)
    {
        UpdateDrop(dt_s);
        return;
    }

    switch (mpDBObject->weaponType)
    {
    case tcTorpedoDBObject::DEPTH_CHARGE:
        UpdateDepthCharge(dt_s);
        return;
    case tcTorpedoDBObject::BOTTOM_MINE:
    case tcTorpedoDBObject::BOTTOM_MINE_CAPTOR:
        UpdateBottomMine(dt_s);
        return;
    default:
        // continue
        break;
    }


    UpdateSpeedSimple(dt_s);

    float speed_mps = C_KTSTOMPS * mcKin.mfSpeed_kts;
    float disp_m = speed_mps * dt_s; // distance moved this update
    float disp_rad = C_MTORAD * disp_m; // distance in equator radians
    runToEnable_m -= disp_m;

    float disp_xy_rad = disp_rad * cosf(mcKin.mfClimbAngle_rad);
    float disp_z_m = disp_m * sinf(mcKin.mfClimbAngle_rad);
    float heading_rad = mcKin.mfHeading_rad;

    mcKin.mfLon_rad += disp_xy_rad * (double)(sinf(heading_rad) / cosf((float)mcKin.mfLat_rad));
    mcKin.mfLat_rad += (double)cosf(heading_rad) * disp_xy_rad; 
    mcKin.mfAlt_m += disp_z_m;

	

	if (!clientMode)
	{
		UpdateGuidance(afStatusTime);
	}
    	
    
  
    if (runTime > 5.0f)  // swim level for first few seconds
    {
        /*** heading calculation ***/
        float dh_rad, dh_min, dh_max;
        dh_rad = goalHeading_rad - mcKin.mfHeading_rad;
        radtoplusminuspi(dh_rad); // map dh_deg to [-pi,pi)
        dh_max = mpDBObject->maxTurnRate_radps * dt_s; 
        dh_min = -dh_max;
        if (dh_rad < dh_min) {dh_rad = dh_min;} // restrict to turn rate
        else if (dh_rad > dh_max) {dh_rad = dh_max;}
        mcKin.mfHeading_rad += dh_rad;
        if (mcKin.mfHeading_rad >= C_TWOPI) {mcKin.mfHeading_rad -= C_TWOPI;}
        if (mcKin.mfHeading_rad < 0) {mcKin.mfHeading_rad += C_TWOPI;}

        /*** pitch calculation ***/
        float dp_rad, dp_min, dp_max;
        dp_rad = goalPitch_rad - mcKin.mfPitch_rad;
        dp_max = 2 * mpDBObject->maxTurnRate_radps * dt_s;
        dp_min = -dp_max;
        if (dp_rad < dp_min) {dp_rad = dp_min;} 
        else if (dp_rad > dp_max) {dp_rad = dp_max;}
        mcKin.mfPitch_rad += dp_rad;
        mcKin.mfClimbAngle_rad = mcKin.mfPitch_rad;
    }

    HandlePoleWrap();

	UpdateEffects();

    Update3D();

    runTime += dt_s;

	if (clientMode) return;

    UpdateDetonation();

//    float priorDamage = mfDamageLevel;

	/*** check for crash ***/

	if (mcTerrain.mfHeight_m >= mcKin.mfAlt_m)
    {
		ApplyGeneralDamage(1.0f, 0);
		tcString s;
		s.Format("Torpedo %s hit bottom at time %.1f lon %.3f, lat %.3f",
			mzUnit.c_str(), afStatusTime, mcKin.mfLon_rad*C_180OVERPI, mcKin.mfLat_rad*C_180OVERPI);
		WTL(s.GetBuffer());
	}

    // update battery

    battery_kJ -= dt_s * mpDBObject->batteryRate_kWpkt * mcKin.mfSpeed_kts;

	if (battery_kJ <= 0) 
    {
		ApplyGeneralDamage(1.0f, 0); // self-destruct
#ifdef _DEBUG
		tcString s;
		s.Format("Torpedo %s shut down at time %.1f lon %.3f, lat %.3f",
			mzUnit.c_str(), afStatusTime, mcKin.mfLon_rad*C_180OVERPI, mcKin.mfLat_rad*C_180OVERPI);
		WTL(s.GetBuffer());
#endif
	}

    // post-launch malfunction check
    if (!tcWeaponObject::malfunctionChecked && (runTime > 60.0f))
    {
        MalfunctionCheck();
    }

	tcSensorPlatform::Update(afStatusTime);

}

/**
* If intended target is set, automatically update guidance based on latest sensor map track
*/
void tcTorpedoObject::UpdateAutoWireGuidance()
{
    if (!(isWireActive && autoWireUpdates && (intendedTarget != -1))) return;

    tcSensorMapTrack track;
    if (tcSimState::Get()->GetTrack(intendedTarget, GetAlliance(), track))
    {
        if (!track.IsBearingOnly())
        {
            goalHeading_rad = mcKin.HeadingToTrack(track);
        }
    }
}


/**
* Depth charge just sinks at max speed
*/
void tcTorpedoObject::UpdateDepthCharge(float dt_s)
{
    float alpha = 0.1f * dt_s;
    mcKin.mfClimbAngle_rad = (1.0f-alpha)*mcKin.mfClimbAngle_rad - alpha*1.55f; // slowly change to -89 deg
    mcKin.mfPitch_rad = mcKin.mfClimbAngle_rad;

    goalSpeed_kts = mpDBObject->maxSpeed_kts;
    UpdateSpeedSimple(dt_s);

    float speed_mps = C_KTSTOMPS * mcKin.mfSpeed_kts;
    float disp_m = speed_mps * dt_s; // distance moved this update

    float disp_z_m = disp_m * sinf(mcKin.mfClimbAngle_rad);
    mcKin.mfAlt_m += disp_z_m;

    if (mcKin.mfClimbAngle_rad > -1.50f)
    {
        float disp_rad = C_MTORAD * disp_m; // distance in equator radians
        float heading_rad = mcKin.mfHeading_rad;
        float disp_xy_rad = disp_rad * cosf(mcKin.mfClimbAngle_rad);
        mcKin.mfLon_rad += disp_xy_rad * (double)(sinf(heading_rad) / cosf((float)mcKin.mfLat_rad));
        mcKin.mfLat_rad += (double)cosf(heading_rad) * disp_xy_rad;
        
        HandlePoleWrap();
    }

	UpdateEffects();

    Update3D();

	if (clientMode) return;

	if (mcKin.mfAlt_m < -10.0f)
	{
		UpdateDepthChargeDetonation();
	}

    if (mcKin.mfAlt_m <= mcTerrain.mfHeight_m)
    {
		SelfDestruct();
	}

}

/**
* Assumes that all depth charges have either contact or proximity fuse
*/
void tcTorpedoObject::UpdateDepthChargeDetonation()
{
    // if we're this close to the detonation point then detonate, otherwise defer to future time step
    const float tminDet_s = 0.05f; 

	float detRange_m = mpDBObject->detonationRange_m;

	tcGeoRect region;
	float checkDistance_rad = (100.0f + detRange_m) * C_MTORAD;

	region.Set(mcKin.mfLon_rad-checkDistance_rad, mcKin.mfLon_rad+checkDistance_rad,
		mcKin.mfLat_rad-checkDistance_rad, mcKin.mfLat_rad+checkDistance_rad);

	tcGameObjIterator iter(region);

	for (iter.First();iter.NotDone();iter.Next())
	{
		tcGameObject *target = iter.Get();
		if ((target != this) && (target->mpDBObject != mpDBObject)) // no self detection, and cheat and ignore other depth charges
		{
			float dx, dy, dz, dt;
			Vec3 collisionPoint;
			float collisionRange_m;

			// first check for impact
			if (target->CalculateCollisionPoint(this, collisionPoint, dt, collisionRange_m))
			{
				// if this isn't a direct hit weapon, check if we're close enough despite impending collision
				if (detRange_m > 0)
				{
					float dt_det_s = dt * (1.0 - (detRange_m / collisionRange_m));
					if (dt_det_s > tminDet_s) return;

					Detonate(dt_det_s);
					SetDirectHitTargetId(-1);
					return;
				}

				if (dt <= tminDet_s)
				{
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

			// check for proximity detonation if this isn't a direct hit weapon
			if (detRange_m > 0)
			{
				// check for future closest point of approach
				dt = target->mcKin.CalculateCollisionPoint(mcKin, dx, dy, dz);

				if (dt <= tminDet_s)
				{
					float damageRange_m = sqrtf(dx*dx + dy*dy + dz*dz); // start with range to model origin

					// check if "up" ray is closer
					if (target->CalculateCollisionPointDir(this, Vec3(0, 1, 0), collisionPoint, collisionRange_m))
					{
						damageRange_m = std::min(collisionRange_m, damageRange_m);
					}

					if (damageRange_m <= 2*detRange_m)
					{
						Detonate(dt);
						SetDirectHitTargetId(-1);
						return;
					}
				}
			}

		}
	}
}


void tcTorpedoObject::UpdateDetonation()
{
    // if we're this close to the detonation point then detonate, otherwise defer to future time step
    const float tminDet_s = 0.05f; 
    

    tcSensorState* sensor = GetSensorMutable(0);
	if (sensor == 0)
	{
		UpdateDetonationUnguided();
		return;
	}

	wxASSERT(sensor != 0);
    if (sensor->mnMode != SSMODE_SEEKERTRACK) return; 

    if ((interceptTime > 3.0f) || (sensor->mcTrack.mnID == -1)) return;

    tcGameObject* target = simState->GetObject(sensor->mcTrack.mnID);

    if (target != 0)
    {
        SetIntendedTarget(sensor->mcTrack.mnID); // in case it doesn't match
    }
    else
    {
        SetIntendedTarget(-1);
        sensor->mcTrack.mnID = -1;
        return;
    }

    float dx, dy, dz, dt;
	Vec3 collisionPoint;
    float collisionRange_m;

    float detRange_m = mpDBObject->detonationRange_m;

	// first check for impact
	if (target->CalculateCollisionPoint(this, collisionPoint, dt, collisionRange_m))
	{
        // if this isn't a direct hit weapon, check if we're close enough despite impending collision
        if (detRange_m > 0)
        {
            float dt_det_s = dt * (1.0 - (detRange_m / collisionRange_m));
            if (dt_det_s > tminDet_s) return;

            Detonate(dt_det_s);
            SetDirectHitTargetId(-1);
            return;
        }

        /*fprintf(stdout, "Collision detect: dt: %f, x: %.1f, y:%.1f, z:%.1f\n",
            dt, collisionPoint.x, collisionPoint.y, collisionPoint.z);*/
        if (dt > tminDet_s) return; // defer until future time step

		collisionPoint = target->ConvertModelCoordinatesToWorld(collisionPoint);
		dx = collisionPoint.x;
		dy = collisionPoint.y;
		dz = collisionPoint.z;

        Detonate(dt);
        SetDirectHitTargetId(target->mnID);
        SetImpactPoint(Vec3(dx, dy, dz));
        return;
	}

    // if this is a direct hit weapon (detonation range == 0) then return
    if (detRange_m == 0) return;

    //// check for sufficient proximity to target now
    //float currentRange_m = 1000.0f * target->mcKin.RangeToKmAlt(mcKin);

    //if (currentRange_m <= detRange_m)
    //{
    //    Detonate(0);
    //    SetDamageRange(0);
    //    SetDirectHitTargetId(-1);
    //    return;
    //}

    // check for future closest point of approach
    dt = target->mcKin.CalculateCollisionPoint(mcKin, dx, dy, dz);

    //float keelDepth_m = target->GetZmin();

    if (dt > tminDet_s) return; // defer until future time step

    float damageRange_m = sqrtf(dx*dx + dy*dy + dz*dz); // start with range to model origin

    // check if "up" ray is closer
    if (target->CalculateCollisionPointDir(this, Vec3(0, 1, 0), collisionPoint, collisionRange_m))
	{
        damageRange_m = std::min(collisionRange_m, damageRange_m);
    }

    if (damageRange_m <= 2*detRange_m)
    {
        Detonate(dt);
        SetDirectHitTargetId(-1);
    }


}

// expensive since does collision testing on all objects that are close to this torpedo every update
void tcTorpedoObject::UpdateDetonationUnguided()
{
	if (runToEnable_m > 0) return;

	tcGeoRect region;
	const float dlat = C_MTORAD * 200.0f;
	float dlon = dlat / cosf(mcKin.mfLat_rad);

	region.Set(mcKin.mfLon_rad - dlon, mcKin.mfLon_rad + dlon,
		mcKin.mfLat_rad - dlat, mcKin.mfLat_rad + dlat);

	tcGameObjIterator iter(region);

	for (iter.First(); iter.NotDone(); iter.Next())
	{
		tcGameObject* target = iter.Get();

		if ((target != this) && (target != 0))
		{
			// if we're this close to the detonation point then detonate, otherwise defer to future time step
			const float tminDet_s = 0.05f; 

			float dx, dy, dz, dt;
			Vec3 collisionPoint;
			float collisionRange_m;

			float detRange_m = mpDBObject->detonationRange_m;

			// first check for impact
			if (target->CalculateCollisionPoint(this, collisionPoint, dt, collisionRange_m))
			{
				// if this isn't a direct hit weapon, check if we're close enough despite impending collision
				if (detRange_m > 0)
				{
					float dt_det_s = dt * (1.0 - (detRange_m / collisionRange_m));
					if (dt_det_s > tminDet_s) return;

					Detonate(dt_det_s);
					SetDirectHitTargetId(-1);
					return;
				}

				/*fprintf(stdout, "Collision detect: dt: %f, x: %.1f, y:%.1f, z:%.1f\n",
				dt, collisionPoint.x, collisionPoint.y, collisionPoint.z);*/
				if (dt > tminDet_s) return; // defer until future time step

				collisionPoint = target->ConvertModelCoordinatesToWorld(collisionPoint);
				dx = collisionPoint.x;
				dy = collisionPoint.y;
				dz = collisionPoint.z;

				Detonate(dt);
                SetDirectHitTargetId(target->mnID);
				SetImpactPoint(Vec3(dx, dy, dz));
				return;
			}

			// if this is a direct hit weapon (detonation range == 0) then return
			if (detRange_m == 0) return;

			// check for future closest point of approach
			dt = target->mcKin.CalculateCollisionPoint(mcKin, dx, dy, dz);

			if (dt > tminDet_s) return; // defer until future time step

			float damageRange_m = sqrtf(dx*dx + dy*dy + dz*dz); // start with range to model origin

			// check if "up" ray is closer
			if (target->CalculateCollisionPointDir(this, Vec3(0, 1, 0), collisionPoint, collisionRange_m))
			{
				damageRange_m = std::min(collisionRange_m, damageRange_m);
			}

			if (damageRange_m <= 2*detRange_m)
			{
				Detonate(dt);
				SetDirectHitTargetId(-1);
			}
			
		}
	}


   


}



/**
*
*/
void tcTorpedoObject::UpdateDrop(float dt_s)
{
    float heading_rad = mcKin.mfHeading_rad;
    float fGroundSpeed_kts = cosf(mcKin.mfClimbAngle_rad) * mcKin.mfSpeed_kts;
    float vz_mps = C_KTSTOMPS * sinf(mcKin.mfClimbAngle_rad) * mcKin.mfSpeed_kts;
    float vxy_mps = C_KTSTOMPS * fGroundSpeed_kts;
    //float z = mcKin.mfAlt_m;

    float dvz = C_G * dt_s;

    if (vz_mps < -30)
    {
        dvz = 0;
    }
    else if (vz_mps < -20)
    {
        dvz = 0.1f * (vz_mps + 30) * dvz; // gradually limit acceleration
    }

    vz_mps = vz_mps - dvz;


    if (vxy_mps > 0)
    {
        vxy_mps = vxy_mps - dt_s * 0.02f * vxy_mps * vxy_mps; // air drag
    }
    if (vxy_mps < 0)
    {
        vxy_mps = 0;
    }

    double fDistance_rad = fGroundSpeed_kts*dt_s*(float)C_KTSTORADPS;

    mcKin.mfLon_rad += fDistance_rad*(double)(sinf(heading_rad)/cosf((float)mcKin.mfLat_rad));
    mcKin.mfLat_rad += (double)cosf(heading_rad)*fDistance_rad; 
    mcKin.mfAlt_m += vz_mps*dt_s;

    mcKin.mfClimbAngle_rad = atan2(vz_mps, vxy_mps);
    mcKin.mfPitch_rad = mcKin.mfClimbAngle_rad;
    mcKin.mfSpeed_kts = C_MPSTOKTS * sqrtf(vz_mps*vz_mps + vxy_mps*vxy_mps);
    
    if (mcKin.mfAlt_m <= 0)
    {
        mcKin.mfSpeed_kts *= 0.1f; // lose speed after hitting water
        if (mcKin.mfSpeed_kts < 5.0) mcKin.mfSpeed_kts = 5.0f;

        mcKin.mfClimbAngle_rad *= 0.125f;
        mcKin.mfPitch_rad = mcKin.mfClimbAngle_rad;
    }

    Update3D();
	
}

/**
*
*/
void tcTorpedoObject::UpdateEffects()
{	
    if (model)
    {
        if ((mcKin.mfAlt_m < -5) && (mcKin.mfSpeed_kts > 15))
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
void tcTorpedoObject::UpdateGuidance(double t) 
{
    const float torpedo_acz = 50.0f;
    const float one_over_torpedo_acz = 1.0f / 50.0f;

    float dt_s = t - lastGuidanceUpdate;
	if (dt_s < guidanceUpdateInterval) return;
	lastGuidanceUpdate = t;

	//************ GuidanceMode update **************
	bool useInterceptPitch = false;
	float interceptPitch_rad = 0;
    
    if (runToEnable_m <= 0)
    {
        if ((seeker != 0) && (!seeker->IsActive()))
		{
            UpdateAutoWireGuidance();
			seeker->SetActive(true);
	        seeker->mnMode = SSMODE_SEEKERSEARCH;
            searchHeading_rad = goalHeading_rad;
            goalSpeed_kts = mpDBObject->maxSpeed_kts;
			searchStartTime = runTime;
        }

        guidanceUpdateInterval = 0.5f;

		short int seekerMode = (seeker != 0) ? seeker->mnMode : SSMODE_NULL;

		switch (seekerMode)
		{
		case SSMODE_NULL:
			break;
		case SSMODE_SEEKERTRACK:
			{
				tcTrack predictedtrack;   
				float tti_s;
				float range_km;

				goalDepth_m = -seeker->mcTrack.mfAlt_m;
				seeker->mcTrack.GetPrediction(predictedtrack, t);

				// if this is a surface target then set depth to detonate under keel
				if (seeker->mcTrack.mfAlt_m >= -5.0f)
				{
					goalDepth_m = 10.0;
					predictedtrack.mfAlt_m = -10.0f;
				}

				if (seeker->mcTrack.mnFlags & TRACK_BEARING_ONLY)
				{
					goalHeading_rad = predictedtrack.mfHeading_rad; // bearing in this case

					// attempt to lead target (ad-hoc intercept course)
					if (predictedtrack.mnFlags & TRACK_BEARINGRATE_VALID)
					{
						goalHeading_rad += 0.5f * predictedtrack.bearingRate_radps;
					}
				}
				else
				{
					mcKin.GetInterceptData3D(predictedtrack, goalHeading_rad, 
						interceptPitch_rad, tti_s, range_km);

					useInterceptPitch = true;
					interceptTime = tti_s;

					if (interceptTime < 100)
					{
						searchMode = randbool() ? SEARCH_LEFTCIRCLE : SEARCH_RIGHTCIRCLE; // to revert to circle search if we lose track when close
					}
				}
			}
			break;
		case SSMODE_SEEKERSEARCH:
			{
				switch (searchMode)
				{
				case SEARCH_SNAKE:
					goalHeading_rad = searchHeading_rad + 0.4f * sinf(0.2f * (runTime - searchStartTime));
					break;
				case SEARCH_LEFTCIRCLE:
					goalHeading_rad = searchHeading_rad - 0.209f * (runTime - searchStartTime); // 12 deg/sec
					goalHeading_rad = fmodf(goalHeading_rad, C_TWOPI) + C_PI;
					break;
				case SEARCH_RIGHTCIRCLE:
					goalHeading_rad = searchHeading_rad + 0.209f * (runTime - searchStartTime);
					goalHeading_rad = fmodf(goalHeading_rad, C_TWOPI) - C_PI;
					break;
				default:
					break;
				}      
			}
			break;
		case SSMODE_SEEKERACQUIRE:
			{
				goalHeading_rad = mcKin.mfHeading_rad; // maintain heading during acquire
			}
			break;
		default:
			{
				wxASSERT(false);
				seeker->mnMode = SSMODE_SEEKERSEARCH;
			}
			break;
		}
        
    } //  if (runToEnable_m <= 0)
    else
    {
        if (mpDBObject->payloadClass.size() > 0)
        {
            if (!payloadDeployed)
            {
                runToEnable_m = 1000.0f * mcKin.RangeToKm(&waypoint); // set run to enable to deploy payload at waypoint
                if (runToEnable_m <= mpDBObject->detonationRange_m)
                {
                    DeployPayload();
                }
                goalHeading_rad = mcKin.HeadingToGeoRad(waypoint.mfLon_rad, waypoint.mfLat_rad);
            }
            else
            {
                SelfDestruct();
            }
        }
    }


    // do not exceed max depth or get too close to the bottom (cheating here somewhat with knowledge of bottom? or have depth finders on torps)
    float maxDepth_m = std::min(mpDBObject->maxDepth_m - 10.0f, -(mcTerrain.mfHeight_m + 10.0f));

    float depth_m = -mcKin.mfAlt_m;
    if (depth_m > maxDepth_m)
    {
        goalDepth_m = maxDepth_m - 5.0f;
        interceptPitch_rad = 0.1f;
    }

	// update guidance update rate and seeker scan rate based on time to intercept
	if (interceptTime <= 2.0) 
	{
		guidanceUpdateInterval = 0.1f;
		seeker->mfCurrentScanPeriod_s = 0.1f;
	}
	else if (interceptTime <= 5.0) 
	{
		guidanceUpdateInterval = 0.2f;
		seeker->mfCurrentScanPeriod_s = 0.2f;
	}

    // depth control
	if (useInterceptPitch) 
	{
        wxASSERT(!_isnan(interceptPitch_rad));
		goalPitch_rad = interceptPitch_rad;
	}
	else 
	{
		if (depth_m > goalDepth_m + torpedo_acz) 
		{
			goalPitch_rad = 0.7f;
		}
		else if (depth_m < goalDepth_m - torpedo_acz) 
		{
			goalPitch_rad = -0.7f;
		}
		else 
		{
            goalPitch_rad = 0.7f * (depth_m - goalDepth_m) * one_over_torpedo_acz;
		}
	}


}


void tcTorpedoObject::UpdateBottomMine(float dt_s)
{
    if ((mcKin.mfSpeed_kts == 0) && (mcKin.mfAlt_m < 0))
    { 
        UpdateBottomMineTrigger(mfStatusTime);
    }
    else
    {
        // sink to bottom
        const float sinkSpeed_kts = 8.0f;
        float alpha = 0.1f * dt_s;
        mcKin.mfClimbAngle_rad = (1.0f-alpha)*mcKin.mfClimbAngle_rad - alpha*1.55f; // slowly change to -89 deg
        mcKin.mfPitch_rad = mcKin.mfClimbAngle_rad;

        goalSpeed_kts = sinkSpeed_kts;
        UpdateSpeedSimple(dt_s);

        float speed_mps = C_KTSTOMPS * mcKin.mfSpeed_kts;
        float disp_m = speed_mps * dt_s; // distance moved this update

        float disp_z_m = disp_m * sinf(mcKin.mfClimbAngle_rad);
        mcKin.mfAlt_m += disp_z_m;

        if (mcKin.mfClimbAngle_rad > -1.50f)
        {
            float disp_rad = C_MTORAD * disp_m; // distance in equator radians
            float heading_rad = mcKin.mfHeading_rad;
            float disp_xy_rad = disp_rad * cosf(mcKin.mfClimbAngle_rad);
            mcKin.mfLon_rad += disp_xy_rad * (double)(sinf(heading_rad) / cosf((float)mcKin.mfLat_rad));
            mcKin.mfLat_rad += (double)cosf(heading_rad) * disp_xy_rad;

            HandlePoleWrap();
        }
        guidanceUpdateInterval = 30.0;

        if (mcKin.mfAlt_m < -mpDBObject->maxDepth_m)
        {
            ApplyGeneralDamage(1.0f, 0);
        }

        if (mcKin.mfAlt_m <= mcTerrain.mfHeight_m)
        {   
            // deploy mine
            mcKin.mfSpeed_kts = 0;
            mcKin.mfAlt_m = std::max(std::min(-goalDepth_m, -10.0f), mcTerrain.mfHeight_m);
            mcKin.mfPitch_rad = 1.55f;
            mcKin.mfClimbAngle_rad = mcKin.mfPitch_rad;
            lastGuidanceUpdate = mfStatusTime + 60.0; // delay arming
        }
    }

	//UpdateEffects();

    Update3D();

	
}

void tcTorpedoObject::UpdateBottomMineTrigger(double t)
{
    float dt_s = t - lastGuidanceUpdate;
    if ((dt_s < guidanceUpdateInterval) || (clientMode)) return;
    lastGuidanceUpdate = t;

    switch (mpDBObject->weaponType)
    {
    case  tcTorpedoDBObject::BOTTOM_MINE:
        {
            // find all objects within +/- 1 km
            float rangeY_rad = C_KMTORAD*1.0f;
            float rangeX_rad = rangeY_rad/cosf(mcKin.mfLat_rad);
            tcGeoRect region;
            region.left = mcKin.mfLon_rad - rangeX_rad;
            region.right = mcKin.mfLon_rad + rangeX_rad;
            region.bottom = mcKin.mfLat_rad - rangeY_rad;
            region.top = mcKin.mfLat_rad + rangeY_rad;

            tcGameObjIterator iter(region);
            float closestRange_km = 999.0f;
            tcGameObject* closestTarget = 0;
            for (iter.First();iter.NotDone();iter.Next())
            {
                tcGameObject* target = iter.Get();           

                bool isEligible = ((target->mpDBObject->mnType & PTYPE_SURFACE) != 0) ||
                    (target->mpDBObject->mnType == PTYPE_SUBMARINE);
                isEligible = isEligible && (target != this); // no self detection
                if (isEligible)
                {
                    float range_km = this->mcKin.RangeToKmAlt(target->mcKin);
                    if (range_km < closestRange_km)
                    {
                        closestTarget = target;
                        closestRange_km = range_km;
                    }
                }
            }

            float detonationRange_km = 0.001f*mpDBObject->detonationRange_m;

            if (closestRange_km <= detonationRange_km)
            {
                tcKinematics targetKin = closestTarget->mcKin;
                targetKin.Extrapolate(0.25f);
                float futureRange_km = targetKin.RangeToKmAlt(this->mcKin);
                if (futureRange_km < closestRange_km)
                {
                    guidanceUpdateInterval = 0.25f;
                }
                else
                {
                    Detonate(0);
                }
            }
            else if (closestRange_km < 1.0f)
            {
                guidanceUpdateInterval = 1.0f + 10.0f*closestRange_km;
            }
            else
            {
                guidanceUpdateInterval = 30.0f;
            }
        }
        break;
    case tcTorpedoDBObject::BOTTOM_MINE_CAPTOR:
        {
            if (seeker == 0)
            {
                wxASSERT(false);
                return;
            }

            if (!seeker->IsActive())
            {
                seeker->SetActive(true);
                seeker->mnMode = SSMODE_SEEKERSEARCH;
            }
            tcSensorPlatform::Update(mfStatusTime);
            if (seeker->mnMode == SSMODE_SEEKERTRACK)
            {
                if (!payloadDeployed) DeployPayload();
                else SelfDestruct();
            }
        }
        break;
    default:
        wxASSERT(false);
        break;
    }
    


    
}


/**
* Simple model for speed update
* Flat max acceleration
*/
void tcTorpedoObject::UpdateSpeedSimple(float dt_s)
{
    float ds_kts = goalSpeed_kts - mcKin.mfSpeed_kts;
    float ds_max = mpDBObject->acceleration_ktsps * dt_s;
    float ds_min = -ds_max;

    if (ds_kts < ds_min) {ds_kts = ds_min;} // restrict to acceleration
    else if (ds_kts > ds_max) {ds_kts = ds_max;}

    mcKin.mfSpeed_kts += ds_kts;

	if (mcKin.mfSpeed_kts < 0) mcKin.mfSpeed_kts = 0;
}

/**
*
*/
void tcTorpedoObject::Clear()  
{  
	tcGameObject::Clear();
}

/**
*
*/
void tcTorpedoObject::DesignateTarget(long anID) 
{
	seeker->mcTrack.mnID = anID;

    // needs to SSMODE_SEEKERACQUIRE so track is updated before guidance update
	seeker->mnMode = SSMODE_SEEKERACQUIRE; 
}

/**
*
*/
void tcTorpedoObject::RandInitNear(float afLon, float afLat) 
{

	//strcpy(mzClass.mz,mpDBObject->mzClass.mz);
	mzUnit.AssignRandomStringB();

	mfStatusTime = 0;        
	mcKin.mfLon_rad = afLon + randfc(1.1f);      
	mcKin.mfLat_rad = afLat + randfc(1.1f);
          
	mcKin.mfHeading_rad = 360*randf();           
	mcKin.mfSpeed_kts = 100;
	mfDamageLevel = 0;    

	//tcGameObject::RandInitNear(afLon,afLat);
	mcKin.mfAlt_m = -100.0f;  
	SetHeading(mcKin.mfHeading_rad);
	SetSpeed(mcKin.mfSpeed_kts);    
	
	mcKin.SetRelativeGeo(waypoint, mcKin.mfHeading_rad*(float)C_PIOVER180, 100.0f);
}

/**
* If missile is targeting a land datum, gp.mnTargetID will be
* set to -1. Otherwise gp.mnTargetID is set to the intended 
* target of the missile.
*
* @return 1 if missile is in terminal phase
*/
int tcTorpedoObject::GetGuidanceParameters(tsGuidanceParameters& gp) 
{
	if (seeker->mnMode == SSMODE_SEEKERTRACK) 
	{
		gp.mnTargetID = seeker->mcTrack.mnID;

        if (seeker->IsPassive())
        {
            gp.mfInterceptTime = 0;
        }
        else
        {
		    gp.mfInterceptTime = interceptTime;
        }
		return 1;
	}
	else
	{
		return 0;
	}
}

/**
*
*/
void tcTorpedoObject::PrintToFile(tcFile& file)
{
	tcString s;
	tcGameObject::PrintToFile(file);
	s.Format(" Missile Object\n");
	file.WriteString(s.GetBuffer());
}

/**
*
*/
void tcTorpedoObject::SaveToFile(tcFile& file) 
{
	tcGameObject::SaveToFile(file);

    wxASSERT(false);
}

/**
*
*/
void tcTorpedoObject::LoadFromFile(tcFile& file) 
{
	tcGameObject::LoadFromFile(file);
	
    wxASSERT(false);
}

/**
*
*/
void tcTorpedoObject::Serialize(tcFile& file, bool mbLoad) 
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

/**
*
*/
tcTorpedoObject::tcTorpedoObject() 
: tcWeaponObject(),
	guidanceUpdateInterval(1.0f),
	lastGuidanceUpdate(0.0f),
	interceptTime(9999.0f),
    runTime(0),
	searchStartTime(0),
	goalPitch_rad(0),
    goalSpeed_kts(35),
    searchHeading_rad(0),
    searchMode(SEARCH_SNAKE),
    mpDBObject(0)
{
	Clear();

	seeker->mnMode = SSMODE_SEEKERSEARCH;
	mnModelType = MTYPE_TORPEDO;
}

/**
* Copy constructor.
*/
tcTorpedoObject::tcTorpedoObject(tcTorpedoObject& o) 
: tcWeaponObject(o)
{
	mnModelType = MTYPE_TORPEDO;
	goalHeading_rad = o.goalHeading_rad;
	goalPitch_rad = o.goalPitch_rad;
	goalSpeed_kts = o.goalSpeed_kts; 
	interceptTime = o.interceptTime;
    runTime = o.runTime;
	searchStartTime = o.searchStartTime;

	lastGuidanceUpdate = o.lastGuidanceUpdate;
	guidanceUpdateInterval = o.guidanceUpdateInterval;
	waypoint = o.waypoint;   
    seeker = o.seeker;
	mpDBObject = o.mpDBObject;
}
/**
* Constructor that initializes using info from database entry.
*/
tcTorpedoObject::tcTorpedoObject(tcTorpedoDBObject* obj)
: tcWeaponObject(obj),
	guidanceUpdateInterval(1.0f),
	lastGuidanceUpdate(0.0f),
	interceptTime(9999.0f),
    runTime(0),
	searchStartTime(0),
	goalPitch_rad(0),
    goalSpeed_kts(35),
    searchHeading_rad(0),
    searchMode(SEARCH_SNAKE),
    mpDBObject(obj)
{
	mnModelType = MTYPE_TORPEDO;

	tcSensorPlatform::Init(obj->sonarClass.c_str(), this); // to avoid using this in initializer

	seeker = dynamic_cast<tcSonar*>(GetSensorMutable(0));
}

/**
*
*/
tcTorpedoObject::~tcTorpedoObject() 
{
}


