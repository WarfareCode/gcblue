/**
**  @file tcMissileObject.cpp
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
#include "tcMissileObject.h"
#include "common/tcStream.h"
#include "common/tcObjStream.h"
#include "common/tcGameStream.h"
#include "database/tcPlatformDBObject.h"
#include "database/tcSensorDBObject.h"
#include "database/tcRadarDBObject.h"
#include "database/tcOpticalDBObject.h"
#include "database/tcESMDBObject.h"
#include "tcRadar.h"
#include "tcOpticalSensor.h"
#include "tcESMSensor.h"
#include "tc3DModel.h"
//#include "tcParticleEffect.h"
#include "tcLauncher.h"
#include "tcSimState.h"
#include "tc3DPoint.h"
#include "tcSubObject.h"
#include "tcTorpedoObject.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define IGNORE_GOAL_ALTITUDE -999.0f

/**
* Load state from update stream
*/
tcUpdateStream& tcMissileObject::operator<<(tcUpdateStream& stream)
{
	tcWeaponObject::operator<<(stream);

	stream >> goalHeading_rad;
	stream >> goalPitch_rad;
    stream >> goalAltitude_m;
	stream >> mfRangeToObjective_km;
	msKState << stream;


    // update msKState params from mcKin to save bandwidth
    msKState.mfSpeed_mps = C_KTSTOMPS * mcKin.mfSpeed_kts;
    msKState.mfGroundSpeed_mps = cosf(mcKin.mfClimbAngle_rad) * msKState.mfSpeed_mps;
    msKState.mfPitch_rad = mcKin.mfPitch_rad;
    msKState.mfHeading_rad = mcKin.mfHeading_rad;
    msKState.mfAltitude_m = mcKin.mfAlt_m;

    mfInterceptTime = (msKState.mfSpeed_mps > 0) ? 1000.0f * mfRangeToObjective_km / msKState.mfSpeed_mps : 999.9;


	tcSensorState* sensor = GetSensorMutable(0);
	if (sensor)
	{
		sensor->operator<<(stream);
	}

	return stream;
}

/**
* Save state to update stream
*/
tcUpdateStream& tcMissileObject::operator>>(tcUpdateStream& stream)
{
	tcWeaponObject::operator>>(stream);

	stream << goalHeading_rad;
	stream << goalPitch_rad;
    stream << goalAltitude_m;
	stream << mfRangeToObjective_km;
	msKState >> stream;

	tcSensorState* sensor = GetSensorMutable(0);
	if (sensor)
	{
		sensor->operator>>(stream);
	}

	return stream;
}




/**
* Load state from game stream
*/
tcGameStream& tcMissileObject::operator<<(tcGameStream& stream)
{
	tcWeaponObject::operator<<(stream);
    tcSensorPlatform::operator<<(stream);

    stream >> goalHeading_rad;
    stream >> goalPitch_rad;
    stream >> goalAltitude_m;
    stream >> mfInterceptTime;
    stream >> subSurfaceLaunch;
    stream >> mfLastGuidanceUpdate;
	stream >> guidanceStatusTime; 
    stream >> mfGuidanceUpdateInterval;

    msWaypoint << stream;

    preplanRoute.clear();
    unsigned char nPreplan;
    stream >> nPreplan;
    for (unsigned char n=0; n<nPreplan; n++)
    {
        GeoPoint p;
        p << stream;
        preplanRoute.push_back(p);
    }

    stream >> mfRangeToObjective_km;
    stream >> mnCurrentSegment;

	msKState << stream;
    stream >> distanceFromLaunch;
    stream >> isTerminal;
    stream >> isCommandHandoff;

    stream.ReadCheckValue(9283);

	return stream;
}

/**
* Save state to game stream
*/
tcGameStream& tcMissileObject::operator>>(tcGameStream& stream)
{
	tcWeaponObject::operator>>(stream);
    tcSensorPlatform::operator>>(stream);

    stream << goalHeading_rad;
    stream << goalPitch_rad;
    stream << goalAltitude_m;
    stream << mfInterceptTime;
    stream << subSurfaceLaunch;
    stream << mfLastGuidanceUpdate;
	stream << guidanceStatusTime; 
    stream << mfGuidanceUpdateInterval;

    msWaypoint >> stream;

    wxASSERT(preplanRoute.size() < 256);
    unsigned char nPreplan = (unsigned char)preplanRoute.size();
    stream << nPreplan;
    for (unsigned char n=0; n<nPreplan; n++)
    {
        preplanRoute[n] >> stream;
    }

    stream << mfRangeToObjective_km;
    stream << mnCurrentSegment;

	msKState >> stream;
    stream << distanceFromLaunch;
    stream << isTerminal;
    stream << isCommandHandoff;

    stream.WriteCheckValue(9283);

	return stream;
}



/**
* @return altitude mode for current flight profile segment
*/
teAltitudeMode tcMissileObject::GetCurrentAltitudeMode()
{
	tsMissileFlightSegment* segmentInfo = 
		&mpDBObject->maFlightProfile[mnCurrentSegment];

	return segmentInfo->meAltitudeMode;
}

/**
* @return guidance mode for current flight profile segment
*/
teGuidanceMode tcMissileObject::GetCurrentGuidanceMode()
{
	tsMissileFlightSegment* segmentInfo = 
		&mpDBObject->maFlightProfile[mnCurrentSegment];

	return segmentInfo->meGuidanceMode;
}


/**
* Initializes missile state for launch from game object.
* Adds self to simulation
*
* @param obj launching game object
* @param launcher index of launcher
*/
void tcMissileObject::LaunchFrom(tcGameObject* obj, unsigned nLauncher)
{
    tcLauncher virtualLauncher; // for missile deployment
	tcLauncher* pLauncher = &virtualLauncher;


    tcPlatformObject* platObj = dynamic_cast<tcPlatformObject*>(obj);
    if (platObj != 0)
	{
		tc3DPoint launcherPos = platObj->mpDBObject->GetLauncherPosition(nLauncher);
		GeoPoint pos = obj->RelPosToLatLonAlt(launcherPos.x, launcherPos.y,
			launcherPos.z);
		mcKin.mfLon_rad = pos.mfLon_rad;
		mcKin.mfLat_rad = pos.mfLat_rad;
		mcKin.mfAlt_m = pos.mfAlt_m;
        if (tcSubObject* sub = dynamic_cast<tcSubObject*>(obj))
        {
            subSurfaceLaunch = true;
        }

        pLauncher = obj->GetLauncher(nLauncher);
	}
	else if (tcMissileObject* missile = dynamic_cast<tcMissileObject*>(obj))
	{   // missile deploying missile
		mcKin.mfLon_rad = obj->mcKin.mfLon_rad;
		mcKin.mfLat_rad = obj->mcKin.mfLat_rad;
		mcKin.mfAlt_m = obj->mcKin.mfAlt_m;

        virtualLauncher.pointingAngle = 0;
	    virtualLauncher.pointingElevation = 0;
		virtualLauncher.firingArc_deg = 0;
        virtualLauncher.msDatum = missile->msWaypoint;
        virtualLauncher.mnTargetID = missile->GetIntendedTarget();
        virtualLauncher.meLaunchMode = DATUM_ONLY;
	}
	else
	{
        wxASSERT(false);
        if (obj == 0) return;
		mcKin.mfLon_rad = obj->mcKin.mfLon_rad;
		mcKin.mfLat_rad = obj->mcKin.mfLat_rad;
		mcKin.mfAlt_m = obj->mcKin.mfAlt_m;
	}

    launchingPlatform = obj->mnID;

	mcKin.mfSpeed_kts = obj->mcKin.mfSpeed_kts;
	mcKin.mfHeading_rad = obj->mcKin.mfHeading_rad;

	if (dynamic_cast<tcAirObject*>(obj))
	{
		// assume air launch always aligned with velocity vector of parent platform
		mcKin.mfPitch_rad = obj->mcKin.mfPitch_rad;
	}
	else
	{
		mcKin.mfPitch_rad = obj->mcKin.mfPitch_rad + pLauncher->GetPointingElevation();
	}



	msKState.mfAltitude_m = mcKin.mfAlt_m;
	if (!subSurfaceLaunch && (msKState.mfAltitude_m < 5.0f))
	{
		msKState.mfAltitude_m = 5.0f;
	}

	msKState.mfSpeed_mps = obj->mcKin.mfSpeed_kts * (float)C_KTSTOMPS;

	goalHeading_rad = obj->mcKin.mfHeading_rad + pLauncher->pointingAngle;

    tcSensorState* sensor = GetSensorMutable(0);

	if (pLauncher->meLaunchMode == DATUM_ONLY) 
	{
		msWaypoint = pLauncher->msDatum;
        msWaypoint.mfAlt_m = mpDBObject->detonationRange_m;
        if (sensor != 0)
        {
            sensor->SetActive(false); // added this for "TV cam" seekers that were incorrectly starting active
        }
        
        if ((mpDBObject->acceptsWaypoints) && (platObj != 0))
        {
            if (platObj->missilePreplan.size() > 0)
            {
                preplanRoute = platObj->missilePreplan;
            }
            else
            {
                SetRandomPreplan("dogleg");
            }
        }

	}
	else if ((pLauncher->meLaunchMode == SEEKER_TRACK) 
		|| (pLauncher->meLaunchMode == FC_TRACK))
	{
		wxASSERT(sensor);
		if (sensor == 0) return;

		msWaypoint = pLauncher->msDatum;
		sensor->SetActive(true);
		sensor->mnMode = SSMODE_SEEKERACQUIRE;
        sensor->mfLastScan = -10; // ensure rapid update to get a valid track for guidance
        sensor->mcTrack.mnID = pLauncher->mnTargetID;

		if (mpDBObject->NeedsFireControl())
		{
			sensor->SetFireControlSensor(
				obj->mnID, pLauncher->fireControlSensorIdx);
			pLauncher->fireControlSensor->RequestTrack();
		}
	}


	mfStatusTime = obj->mfStatusTime;
	mcKin.mfHeading_rad += pLauncher->pointingAngle;

    // for launchers with adjustable travel, attempt to point launcher in direction of target
    if (pLauncher->IsAutoPoint())
    {
        float pointHeading_rad = 0;
        float pointPitch_rad = 0;
        if (pLauncher->GetAutoPointing(pointHeading_rad, pointPitch_rad))
        {
            mcKin.mfHeading_rad = pointHeading_rad;
            mcKin.mfPitch_rad = pointPitch_rad;
            goalHeading_rad = mcKin.mfHeading_rad;
        }
    }

    // for VLS launchers "point" them initially in direction of target
    if ((mcKin.mfPitch_rad > 1.4835) && (pLauncher->mnTargetID != -1))
    {
        
        tcTrack targetTrack;
        if (simState->mcSensorMap.GetTrack(pLauncher->mnTargetID, targetTrack, obj->GetAlliance()))
        {
            mcKin.mfHeading_rad = obj->mcKin.HeadingToTrack(targetTrack);
            goalHeading_rad = mcKin.mfHeading_rad;
        }
        else if (tcGameObject* target = simState->GetObject(pLauncher->mnTargetID))
        {
            mcKin.mfHeading_rad = obj->mcKin.HeadingToGeoRad(target->mcKin.mfLon_rad, target->mcKin.mfLat_rad);
            goalHeading_rad = mcKin.mfHeading_rad;
        }
    }

    mcKin.mfClimbAngle_rad = mcKin.mfPitch_rad;
	msKState.mfPitch_rad = mcKin.mfPitch_rad;
    goalPitch_rad = mcKin.mfPitch_rad;
    goalAltitude_m = IGNORE_GOAL_ALTITUDE;

    wxString s = wxString::Format("Missile %d-%d", obj->mnID, launchedCounter++);
  
	/* Workaround, for some reason duplicate names were appearing with missiles
	** despite statistical unlikelihood. E.g. Missile 11-133 showed up three times!?
	** Changed from 3 to 4 digit random suffix and added test and second chance to 
	** get a unique object name.
	*/
	if (simState->GetObjectByName(s.ToStdString()))
	{
        wxASSERT(false); // checkpoint to see if this ever happens
        launchedCounter += 1000;
        s = wxString::Format("Missile %d-%d", obj->mnID, launchedCounter++);
	}

    mzUnit = s.c_str();   

	SetAlliance(obj->GetAlliance());     

	simState->AddPlatform(static_cast<tcGameObject*>(this));

	// Set intended target (has to be done after alliance and id is set).
	// This is a tcWeaponObject method
	SetIntendedTarget(pLauncher->mnTargetID);

}

/**
* @return time remaining in seconds for rocket motor thrust
*/
float tcMissileObject::RuntimeRemaining()
{
    return mpDBObject->mfBoostTime_s + mpDBObject->mfSustTime_s - msKState.mfFlightTime;
}


/**
* Call from LaunchFrom to setup a random preplan route
*
* @param planType "dogleg" "zigzag"
*/
void tcMissileObject::SetRandomPreplan(const std::string& planType)
{
    preplanRoute.clear();
    
    if (planType == "dogleg")
    {
        // for 1/3 dogleg point, max additional distance at 30 deg is about 6%: (1 + sqrt((3-cos(30*pi/180))^2 + (sin(30*pi/180)^2))) / 3
        float range_km = mcKin.RangeToKm(&msWaypoint);
        float bearing_rad = mcKin.HeadingToGeoRad(&msWaypoint);

        GeoPoint p1(mcKin.mfLon_rad, mcKin.mfLat_rad, 0);
        p1.Offset(0.33f*range_km, bearing_rad + randfc(60.0f*C_PIOVER180));

        preplanRoute.push_back(p1);
    }
}

/**
*
*/
void tcMissileObject::Update(double afStatusTime)
{
	float dt_s = (float)(afStatusTime - mfStatusTime);

	wxASSERT(mpDBObject != NULL);
    
    if (!subSurfaceLaunch)
    {
	    Aero::UpdateMissileKState(msKState, mpDBObject, dt_s);
    }
    else
    {
        UpdateSubsurface(afStatusTime);
        return;
    }

    mcKin.mfSpeed_kts = msKState.mfSpeed_mps*(float)C_MPSTOKTS;	
    mcKin.mfClimbAngle_rad = msKState.mfPitch_rad;
    mcKin.mfPitch_rad = msKState.mfPitch_rad;
	float fHeading_rad = mcKin.mfHeading_rad;
	float fGroundSpeed_mps = msKState.mfGroundSpeed_mps;

    float distance_m = fGroundSpeed_mps * dt_s;
	double fDistance_rad = (double)distance_m * C_MTORAD;
	mcKin.mfLon_rad += fDistance_rad*(double)(sinf(fHeading_rad)/cosf((float)mcKin.mfLat_rad));
	mcKin.mfLat_rad += fDistance_rad*(double)cosf(fHeading_rad); 
	mcKin.mfAlt_m = msKState.mfAltitude_m;

    distanceFromLaunch += distance_m;

	if (!clientMode)
	{
		UpdateGuidance(afStatusTime);
	}

    float maxTurn_rad = dt_s * std::min(GlimitedTurnRate(), C_PIOVER180*mpDBObject->mfMaxTurnRate_degps); // g-limit or turn rate limit, whichever is less
    
	/*** heading calculation ***/
	float dh_rad,dh_min,dh_max;
	dh_rad = goalHeading_rad - mcKin.mfHeading_rad;
	radtoplusminuspi(dh_rad); // map dh_deg to [-pi,pi)
	dh_max = maxTurn_rad;
	dh_min = -dh_max;
	if (dh_rad < dh_min) {dh_rad = dh_min;} // restrict to turn rate
	else if (dh_rad > dh_max) {dh_rad = dh_max;}
	mcKin.mfHeading_rad += dh_rad;

    HandlePoleWrap();

	if (mcKin.mfHeading_rad >= C_TWOPI) {mcKin.mfHeading_rad -= C_TWOPI;}
	if (mcKin.mfHeading_rad < 0) {mcKin.mfHeading_rad += C_TWOPI;}

    UpdateGoalPitch();

	/*** pitch calculation ***/
	float dp_rad,dp_min,dp_max;
	dp_rad = goalPitch_rad - mcKin.mfPitch_rad;
	dp_max = maxTurn_rad; // 90 deg/s pitch rate, hard coded for now
	dp_min = -dp_max;
	if (dp_rad < dp_min) {dp_rad = dp_min;} 
	else if (dp_rad > dp_max) {dp_rad = dp_max;}
	mcKin.mfPitch_rad += dp_rad;
	msKState.mfPitch_rad = mcKin.mfPitch_rad;

	mfStatusTime = afStatusTime;

	UpdateEffects();

    Update3D();

	if (clientMode) return;

    UpdateDatalinkStatus();

    UpdateDetonation();

	/*** check for crash ***/
    bool underWater = (mcKin.mfAlt_m <= 0.0f);
    bool seaSurfaceCrash = (!subSurfaceLaunch) && underWater;

    // clear subSurfaceLaunch once weapon breaks surface
    if (!underWater) subSurfaceLaunch = false;

//    float priorDamage = mfDamageLevel;

	if ((mcTerrain.mfHeight_m >= mcKin.mfAlt_m) || seaSurfaceCrash)
    {
		ApplyGeneralDamage(1.0f, 0);
		tcString s;
		s.Format("Object %s crashed at time %.1f lon %.3f, lat %.3f",
			mzUnit.c_str(), afStatusTime, mcKin.mfLon_rad*C_180OVERPI, mcKin.mfLat_rad*C_180OVERPI);
		WTL(s.GetBuffer());
	}
	if ((msKState.mfFlightTime > 20.0f)&&(msKState.mfSpeed_mps < mpDBObject->mfShutdownSpeed_mps)) {
		ApplyGeneralDamage(1.0f, 0);
		tcString s;
		s.Format("Object %s shut down at time %.1f lon %.3f, lat %.3f",
			mzUnit.c_str(), afStatusTime, mcKin.mfLon_rad*C_180OVERPI, mcKin.mfLat_rad*C_180OVERPI);
		WTL(s.GetBuffer());
	}


	tcSensorPlatform::Update(afStatusTime);
}

void tcMissileObject::UpdateSubsurface(double t)
{
    wxASSERT(subSurfaceLaunch);

    float dt_s = (float)(t - mfStatusTime);

    float alpha = dt_s;
    msKState.mfGroundSpeed_mps = (1-alpha)*msKState.mfGroundSpeed_mps + alpha*2.0f; // settle to 2 m/s
    msKState.mfPitch_rad = (1-alpha)*msKState.mfPitch_rad + alpha*1.55f; // settle to 89 deg pitch, floating up
    msKState.mfAltitude_m += dt_s * msKState.mfGroundSpeed_mps * sinf(msKState.mfPitch_rad);

    mcKin.mfSpeed_kts = msKState.mfSpeed_mps*(float)C_MPSTOKTS;	
    mcKin.mfClimbAngle_rad = msKState.mfPitch_rad;
    mcKin.mfPitch_rad = msKState.mfPitch_rad;
    float fHeading_rad = mcKin.mfHeading_rad;
    float fGroundSpeed_mps = msKState.mfGroundSpeed_mps;

    float distance_m = fGroundSpeed_mps * dt_s;
    double fDistance_rad = (double)distance_m * C_MTORAD;
    mcKin.mfLon_rad += fDistance_rad*(double)(sinf(fHeading_rad)/cosf((float)mcKin.mfLat_rad));
    mcKin.mfLat_rad += fDistance_rad*(double)cosf(fHeading_rad); 
    mcKin.mfAlt_m = msKState.mfAltitude_m;

    HandlePoleWrap();

    bool underWater = (mcKin.mfAlt_m <= 0.0f);

    // clear subSurfaceLaunch once weapon breaks surface
    if (!underWater) subSurfaceLaunch = false;

    mfStatusTime = t;

    UpdateEffects();

    Update3D();
}


void tcMissileObject::UpdateDetonation()
{
    // if we're this close to the detonation point then detonate, otherwise defer to future time step
    const float tminDet_s = 0.05f; 
    /*if (isTerminal)
    {
        tcSensorState* sensor = GetSensorMutable(0);
        if ((sensor == 0) || (sensor->mnMode != SSMODE_SEEKERTRACK))
        {
            fprintf(stdout, "Terminal lost track mode\n");
        }
        else if ((mfInterceptTime > 3.0f) || (sensor->mcTrack.mnID == -1))
        {
            fprintf(stdout, "Terminal lost, tint: %f, trackId: %d\n", mfInterceptTime, sensor->mcTrack.mnID);
        }

    }*/

    if (mfInterceptTime > 3.0f) return;

    // for nav guided missiles, detonate is called in guidance update,
    // so return if missile is in any state but seeker track OR command guidance
    bool isTerminalCommandGuidance = 
        (mnCurrentSegment == (mpDBObject->mnNumSegments - 1)) &&
        (mpDBObject->maFlightProfile[mnCurrentSegment].meGuidanceMode == GM_COMMAND);


    tcSensorState* sensor = GetSensorMutable(0);
    bool isTerminalSeekerGuidance = (sensor != 0) && (sensor->mnMode == SSMODE_SEEKERTRACK);

    long targetID = -1;

    if (isTerminalSeekerGuidance)
    {
        targetID = sensor->mcTrack.mnID;
        SetIntendedTarget(sensor->mcTrack.mnID); // in case it doesn't match
    }
    else if (isTerminalCommandGuidance)
    {
        targetID = intendedTarget;
    }
    else
    {
        return;
    }

    if  (targetID == -1) return;

    isTerminal = true;

    tcGameObject* target = simState->GetObject(targetID);
    if (target == 0) return; // target lost

 
    float dx, dy, dz, dt;
	Vec3 collisionPoint;
    float trueRange2;
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
		trueRange2 = 0;
        Detonate(dt);
        SetDirectHitTargetId(target->mnID);
        SetImpactPoint(Vec3(dx, dy, dz));
        return;
	}

    // if this is a direct hit missile (detonation range == 0) then return
    if (detRange_m == 0) return;

    // check for sufficient proximity to target now
    float currentRange_m = 1000.0f * target->mcKin.RangeToKmAlt(mcKin);

    if (currentRange_m <= detRange_m)
    {
        Detonate(0);
        SetDirectHitTargetId(-1);
        return;
    }

    // check for future closest point of approach
    dt = target->mcKin.CalculateCollisionPoint(mcKin, dx, dy, dz);

    if (dt > tminDet_s) return; // defer until future time step
    trueRange2 = dx*dx + dy*dy + dz*dz;

    if (trueRange2 <= detRange_m * detRange_m)
    {
        Detonate(dt);
        SetDirectHitTargetId(-1);
    }


}


void tcMissileObject::UpdateEffects()
{
	if (model)
	{
		model->SetSmokeMode(tc3DModel::MISSILE);
		model->UpdateEffects();
	}
}




void tcMissileObject::UpdateGoalPitch()
{
    if (goalAltitude_m == IGNORE_GOAL_ALTITUDE) return; // using intercept pitch, no altitude goal

    float dAlt_m = msKState.mfAltitude_m - goalAltitude_m;
    if (fabsf(dAlt_m) < 0.5f)
    {
        goalPitch_rad = 0;
        return;
    }

    float missile_acz = mpDBObject->aczConstant_kts * mcKin.mfSpeed_kts;
    float inv_missile_acz = 1.0 / missile_acz;

	wxASSERT(mnCurrentSegment < mpDBObject->mnNumSegments);
	tsMissileFlightSegment* pSegmentInfo = &mpDBObject->maFlightProfile[mnCurrentSegment];

    if (dAlt_m < -missile_acz) 
    {
		goalPitch_rad = (pSegmentInfo->meAltitudeMode != AM_ASL_LOFT) ? 1.0f : 0.349f; // 57 or 20 deg
    }
    else if (dAlt_m > missile_acz) 
    {
        goalPitch_rad = -1.0f;
    }
    else 
    {
        goalPitch_rad = -inv_missile_acz * dAlt_m;
    }
}

void tcMissileObject::UpdateGoalPitchSim(MissileSimData& simData, const tcMissileDBObject* missileData)
{
    if (simData.goalAltitude_m == IGNORE_GOAL_ALTITUDE) return; // using intercept pitch, no altitude goal

    float dAlt_m = simData.kstate.mfAltitude_m - simData.goalAltitude_m;
    if (fabsf(dAlt_m) < 0.5f)
    {
        simData.goalPitch_rad = 0;
        return;
    }

    float missile_acz = missileData->aczConstant_kts * simData.missileKin.mfSpeed_kts;
    float inv_missile_acz = 1.0 / missile_acz;

	wxASSERT(simData.segment < missileData->mnNumSegments);
	const tsMissileFlightSegment* pSegmentInfo = &missileData->maFlightProfile[simData.segment];

    if (dAlt_m < -missile_acz) 
    {
        simData.goalPitch_rad = (pSegmentInfo->meAltitudeMode != AM_ASL_LOFT) ? 1.0f : 0.349f; // 57 or 20 deg
    }
    else if (dAlt_m > missile_acz) 
    {
        simData.goalPitch_rad = -1.0f;
    }
    else 
    {
        simData.goalPitch_rad = -inv_missile_acz * dAlt_m;
    }
}

/**
* For meGuidanceMode==GM_NAV and meAltitudeMode==AM_DATUM
*/
void tcMissileObject::UpdateDatumInterceptGuidance(double t, bool& useInterceptPitch, float& interceptPitch_rad)
{
    tcTrack groundTrack;

    groundTrack.mfAlt_m = msWaypoint.mfAlt_m; // 2014-07-06 note waypoint altitude already set to mpDBObject->detonationRange_m;
    groundTrack.mfLon_rad = msWaypoint.mfLon_rad;
    groundTrack.mfLat_rad = msWaypoint.mfLat_rad;
    groundTrack.mfSpeed_kts = 0;

    float tti_s;
    float range_rad;

    mcKin.GetInterceptData3D(groundTrack, goalHeading_rad, 
        interceptPitch_rad, tti_s, range_rad);


    mfRangeToObjective_km = C_RADTOKM * range_rad;


    if (mfRangeToObjective_km < 0.5f)
    {
        // detonate based on altitude
        float vz_mps = C_KTSTOMPS*mcKin.mfSpeed_kts*sinf(mcKin.mfClimbAngle_rad);
        float dz =  groundTrack.mfAlt_m - mcKin.mfAlt_m; // -height above ground or sea level
        float t_impact = dz / vz_mps;

        if (mfRangeToObjective_km <= 0.050)
        {
            Detonate(0);
        }
        else if ((tti_s < 0.05) || (t_impact < 0.05))
        {
            Detonate(std::min(tti_s, t_impact));
        }
        else // check for diverging range
        {
            // this section detonates at closest point within 100 m if missile misses first test
            double lonPredict_rad, latPredict_rad;
            float altPredict_m;
            mcKin.PredictPosition(0.1f, lonPredict_rad, latPredict_rad, altPredict_m);

            tcTrack groundTrack2;
            groundTrack2.mfLon_rad = lonPredict_rad;
            groundTrack2.mfLat_rad = latPredict_rad;
            groundTrack2.mfAlt_m = altPredict_m;
            groundTrack2.mfSpeed_kts = 0;

            float rangeToObjective2_km = mcKin.RangeToKmAlt(groundTrack2);
            bool rangeDiverging = (rangeToObjective2_km > mfRangeToObjective_km);
            if (rangeDiverging)
            { 
                if (mfRangeToObjective_km < 0.150f)
                {
                    Detonate(0);
                }
                else
                {
                    SelfDestruct();
                }
            }
        }

    }

    mfInterceptTime = tti_s;
    useInterceptPitch = true;
}

/**
* Update heading and pitch controls based on flight profile, intercept data, etc.
* This needs refactoring.
*/
void tcMissileObject::UpdateGuidance(double afStatusTime) 
{
	tsMissileFlightSegment* pSegmentInfo;

	if ((msKState.mfFlightTime - mfLastGuidanceUpdate) < mfGuidanceUpdateInterval) 
	{
		return;
	}

	tcSensorState* sensor = GetSensorMutable(0);

	if (guidanceStatusTime == 0) {guidanceStatusTime = afStatusTime;}
	guidanceStatusTime = afStatusTime;
	mfLastGuidanceUpdate = msKState.mfFlightTime;
	if (mpDBObject->mnNumSegments == 0) {wxASSERT(false); return;}
	if (mnCurrentSegment >= mpDBObject->mnNumSegments) {wxASSERT(false); return;} // error case, shouldn't happen
	pSegmentInfo = &mpDBObject->maFlightProfile[mnCurrentSegment];
	goalAltitude_m = msKState.mfAltitude_m;

	//************ GuidanceMode update **************
	bool useInterceptPitch = false;
	float interceptPitch_rad = 0;

	switch (pSegmentInfo->meGuidanceMode) 
	{
	case GM_NAV:
        if ((preplanRoute.size() == 0))
        {
            goalHeading_rad = mcKin.HeadingToGeoRad(&msWaypoint);
            mfRangeToObjective_km = mcKin.RangeToKm(&msWaypoint);
            if (pSegmentInfo->meAltitudeMode == AM_DATUM)
            {
                UpdateDatumInterceptGuidance(afStatusTime, useInterceptPitch, interceptPitch_rad);
            }
        }
        else
        {
            goalHeading_rad = mcKin.HeadingToGeoRad(&preplanRoute[0]);
            mfRangeToObjective_km = 9999.0f; // set this large to avoid triggering segment change until preplan is finished
            float rangeToWaypoint_km = mcKin.RangeToKm(&preplanRoute[0]);
            float waypointChangeThreshold_km = mfGuidanceUpdateInterval*mcKin.mfSpeed_kts*C_KTSTOKMPS*2.0f;
            if (rangeToWaypoint_km < waypointChangeThreshold_km)
            {   // remove completed preplan waypoint from route
                std::vector<GeoPoint> temp;
                for (size_t n=1; n<preplanRoute.size(); n++)
                {
                    temp.push_back(preplanRoute[n]);
                }
                preplanRoute = temp;
            }
        }
		break;
    case GM_COMMAND:
        {
            useInterceptPitch = false;
            /* Use alliance sensor map for command guidance (taking a shortcut here for simplicity)
			** Check that the fire control sensor is active. If no fire control sensor exists, skip
			** this check. 
			*/
            tcSensorMapTrack mapTrack;
            float tti_s = 999.0f;
            if (simState->GetTrack(intendedTarget, GetAlliance(), mapTrack))
            {
                tcTrack predictedTrack; 
                mapTrack.GetPrediction(predictedTrack, afStatusTime);

                float range3D_rad = 0;
                mcKin.GetInterceptData3D(predictedTrack, goalHeading_rad, 
                    interceptPitch_rad, tti_s, range3D_rad);

                // For few seconds after launch, head for track without prediction while missile accelerates
                if (msKState.mfFlightTime < 5)
                {
                    predictedTrack = mapTrack;
                    goalHeading_rad = mcKin.HeadingToTrack(predictedTrack);
                }
                
                mfRangeToObjective_km = mcKin.RangeToKm(predictedTrack); // 2D range
                
                useInterceptPitch = (pSegmentInfo->meAltitudeMode == AM_INTERCEPT) || isCommandHandoff || 
					((pSegmentInfo->meAltitudeMode == AM_INTERCEPT_HIGH) && (interceptPitch_rad > 0));
			    mfInterceptTime = tti_s;
                

                msWaypoint.mfLon_rad = predictedTrack.mfLon_rad;
                msWaypoint.mfLat_rad = predictedTrack.mfLat_rad;
                msWaypoint.mfAlt_m = predictedTrack.mfAlt_m;
            }
            else if ((mfInterceptTime < 9990.0f) && (msWaypoint.mfLon_rad != 0))
            {
                tcTrack predictedTrack;
            
                predictedTrack.mfAlt_m = msWaypoint.mfAlt_m;
                predictedTrack.mfLon_rad = msWaypoint.mfLon_rad;
                predictedTrack.mfLat_rad = msWaypoint.mfLat_rad;
                predictedTrack.mfSpeed_kts = 0;

                mcKin.GetInterceptData2D(predictedTrack, goalHeading_rad, tti_s);
                mfRangeToObjective_km = mcKin.RangeToKm(predictedTrack);
            }
            else
            {
                SelfDestruct(); // no track to command to
            }
			
			if ((sensor != 0) && sensor->HasFireControlSensor())
			{
				tcSensorState* fireControl = sensor->GetFireControlSensor();
				if ((fireControl == 0) || (!fireControl->IsActive()))
				{
					SelfDestruct();
				}
			}

            mfInterceptTime = tti_s;
        }
        break;
	case GM_SENSOR1:
		wxASSERT(sensor);
		if (sensor == 0) return;
		
		if (!sensor->IsActive()) 
		{
			sensor->SetActive(true);
	        sensor->mnMode = SSMODE_SEEKERSEARCH;
        }

        mfGuidanceUpdateInterval = 0.5f;


		if (sensor->mnMode == SSMODE_SEEKERTRACK) 
		{
			tcTrack predictedtrack;   
			float tti_s;
			sensor->mcTrack.GetPrediction(predictedtrack,afStatusTime);

			mcKin.GetInterceptData3D(predictedtrack, goalHeading_rad, 
				interceptPitch_rad, tti_s, mfRangeToObjective_km);

            // For few seconds after launch, head for track without prediction while missile accelerates
            if (msKState.mfFlightTime < 5)
            {
                predictedtrack = sensor->mcTrack;
                goalHeading_rad = mcKin.HeadingToTrack(sensor->mcTrack);
            }

            // limit intercept angle to keep target in seeker, goalHeading_rad is [-pi,pi) from atan2f,
            //  mcKin.mfHeading_rad is [0, 2*pi)
            float dh_rad = goalHeading_rad - mcKin.mfHeading_rad;
            dh_rad += C_TWOPI * (float(dh_rad < -C_PI) - float(dh_rad > C_PI));
            float seekerCoverage_rad = (0.9f*0.5f*C_PIOVER180)*sensor->mpDBObj->mfFieldOfView_deg; // 90% of half fov in rad
            if (dh_rad > seekerCoverage_rad)
            {
                goalHeading_rad = mcKin.mfHeading_rad + seekerCoverage_rad;
            }
            else if (dh_rad <-seekerCoverage_rad)
            {
                goalHeading_rad = mcKin.mfHeading_rad - seekerCoverage_rad;
            }


			mfRangeToObjective_km *= C_RADTOKM; // convert to km


			if (msKState.mfAltitude_m <= 4.0) 
			{
				if (interceptPitch_rad < 0) {interceptPitch_rad = 0;}
			}

			useInterceptPitch = (pSegmentInfo->meAltitudeMode == AM_INTERCEPT) || ((pSegmentInfo->meAltitudeMode == AM_INTERCEPT_HIGH) && (interceptPitch_rad > 0));

			mfInterceptTime = tti_s;

            // update waypoint just in case we want to go back to nav or command
            msWaypoint.mfLon_rad = predictedtrack.mfLon_rad;
            msWaypoint.mfLat_rad = predictedtrack.mfLat_rad;
            msWaypoint.mfAlt_m = predictedtrack.mfAlt_m;
		}
		else 
		{
			//goalAltitude_m = pSegmentInfo->mfAltitude_m; // used if AltOpt is AM_INTERCEPT
		}
        break;
    case GM_DEPLOY:
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
        break;
	default:
		break;
	}

    // mid-flight malfunction check
    if (!tcWeaponObject::malfunctionChecked && ((0.001f * distanceFromLaunch) > mfRangeToObjective_km))
    {
        MalfunctionCheck();
    }

	// update guidance update rate and seeker scan rate based on time to intercept

	if (mfInterceptTime <= 2.0) 
	{
		mfGuidanceUpdateInterval = 0.1f;
		if (sensor != 0) sensor->mfCurrentScanPeriod_s = 0.1f;
	}
    else if (mfInterceptTime <= 5.0) 
	{
		mfGuidanceUpdateInterval = 0.2f;
		if (sensor != 0) sensor->mfCurrentScanPeriod_s = 0.2f;
	}


	//************ update altitude control **************
	switch (pSegmentInfo->meAltitudeMode) 
	{
	case AM_ASL:
	case AM_ASL_LOFT:
		goalAltitude_m = pSegmentInfo->mfAltitude_m;
		break;
	case AM_AGL:
		{
            float maxHeight_m = std::max(mcTerrain.lookAheadHeight_m, mcTerrain.mfHeight_m);
            float effectiveTerrainHeight_m = std::max(maxHeight_m, (float)0);
			goalAltitude_m = pSegmentInfo->mfAltitude_m + effectiveTerrainHeight_m;
		}
		break;
	case AM_INTERCEPT:  // use seeker data or maintain altitude
	case AM_INTERCEPT_HIGH:
		break;
	case AM_DATUM: // use intercept pitch from msWaypoint
		wxASSERT(useInterceptPitch);
		break;
	default:
		goalAltitude_m = 10.0f;
		break;
	}

	if (useInterceptPitch) 
	{
        wxASSERT(!_isnan(interceptPitch_rad));
		goalPitch_rad = interceptPitch_rad;
        goalAltitude_m = IGNORE_GOAL_ALTITUDE;
	}
	else 
	{
        goalPitch_rad = 0; // calculated in UpdateGoalPitch();
	}

	// force level flight for first 0.5 sec for air-launched missiles
    if ((msKState.mfFlightTime < 0.5)&&(msKState.mfAltitude_m - mcTerrain.mfHeight_m > 50.0f)) 
	{
		goalHeading_rad = mcKin.mfHeading_rad;
        goalPitch_rad = mcKin.mfPitch_rad;
        goalAltitude_m = IGNORE_GOAL_ALTITUDE;
	}
	// switch to next flight profile segment if within range
	else if (mnCurrentSegment < (mpDBObject->mnNumSegments-1)) 
	{
		if (mfRangeToObjective_km < pSegmentInfo->mfRange_km) 
		{
            bool commandHandoff = (pSegmentInfo->meGuidanceMode == GM_COMMAND) &&
                                  (mpDBObject->maFlightProfile[mnCurrentSegment+1].meGuidanceMode != GM_COMMAND);
            if (!commandHandoff)
            {
			    mnCurrentSegment++;
            }
            else
            {
                UpdateCommandHandoff();
            }
		}
	}
}

void tcMissileObject::UpdateCommandHandoff()
{
    wxASSERT(mnCurrentSegment < (mpDBObject->mnNumSegments-1));
    wxASSERT(mfRangeToObjective_km < mpDBObject->maFlightProfile[mnCurrentSegment].mfRange_km);
    
    isCommandHandoff = true;

    tcSensorState* sensor = GetSensorMutable(0);
    wxASSERT(sensor != 0);
    if (sensor == 0) return;
    
    // activate seeker if not active
    if (!sensor->IsActive())
    {
        sensor->SetActive(true);
        sensor->mnMode = SSMODE_NULL; // so we don't update anything yet in sensor->Update()
    }

    // check if seeker can detect target
    tcGameObject* target = simState->GetObject(intendedTarget);
    float range_km = 0;
    sensor->SetCommandReceiver(false);
    if ((target != 0) && sensor->CanDetectTarget(target, range_km, false))
    {
        isCommandHandoff = false;
        sensor->mnMode = SSMODE_SEEKERTRACK;
        mnCurrentSegment++;
    }
    else
    {   // remain on this segment and continue handoff
        sensor->SetCommandReceiver(true);
    }
}

/**
* 
*/
void tcMissileObject::UpdateGuidanceSim(MissileSimData& simData, const tcMissileDBObject* missileData)
{
	if (missileData->mnNumSegments == 0) 
    {
        wxASSERT(false); 
        return;
    }
	wxASSERT(simData.segment < missileData->mnNumSegments);

	const tsMissileFlightSegment* segmentInfo = &missileData->maFlightProfile[simData.segment];
	simData.goalAltitude_m = simData.kstate.mfAltitude_m;

	//************ GuidanceMode update **************
	bool useInterceptPitch = false;
	float interceptPitch_rad = 0;

    switch (segmentInfo->meGuidanceMode) 
    {
    case GM_NAV:
        simData.goalHeading_rad = simData.missileKin.HeadingToGeoRad(&simData.waypoint);
        simData.rangeToObjective_km = simData.missileKin.RangeToKm(&simData.waypoint);
        if (segmentInfo->meAltitudeMode == AM_DATUM)
        {
            tcTrack groundTrack;

            groundTrack.mfAlt_m = simData.waypoint.mfAlt_m + missileData->detonationRange_m; // take det range as det alt for AM_DATUM
            groundTrack.mfLon_rad = simData.waypoint.mfLon_rad;
            groundTrack.mfLat_rad = simData.waypoint.mfLat_rad;
            groundTrack.mfSpeed_kts = 0;

            float tti_s;
            float range_rad;

            simData.missileKin.GetInterceptData3D(groundTrack, simData.goalHeading_rad, 
                interceptPitch_rad, tti_s, range_rad);

            simData.rangeToObjective_km = C_RADTOKM * range_rad;

            if (simData.rangeToObjective_km < 0.5f)
            {
                // detonate based on altitude
                float vz_mps = C_KTSTOMPS*simData.missileKin.mfSpeed_kts*sinf(simData.missileKin.mfClimbAngle_rad);
                float dz = groundTrack.mfAlt_m - simData.missileKin.mfAlt_m; // -height above ground or sea level
                float t_impact = dz / vz_mps;

                if (simData.rangeToObjective_km <= 0.050)
                {
                    simData.endFlight = true;
                }
                else if ((tti_s < 0.05) || (t_impact < 0.05))
                {
                    simData.endFlight = true;
                }
                else // check for diverging range
                {
                    // this section detonates at closest point within 100 m if missile misses first test
                    double lonPredict_rad, latPredict_rad;
                    float altPredict_m;
                    simData.missileKin.PredictPosition(0.1f, lonPredict_rad, latPredict_rad, altPredict_m);

                    tcTrack groundTrack2;
                    groundTrack2.mfLon_rad = lonPredict_rad;
                    groundTrack2.mfLat_rad = latPredict_rad;
                    groundTrack2.mfAlt_m = altPredict_m;
                    groundTrack2.mfSpeed_kts = 0;

                    float rangeToObjective2_km = simData.missileKin.RangeToKmAlt(groundTrack2);
                    bool rangeDiverging = (rangeToObjective2_km > simData.rangeToObjective_km);
                    if (rangeDiverging)
                    { 
                        simData.endFlight = true;
                    }
                }

            }

            simData.interceptTime_s = tti_s;
            useInterceptPitch = true;
        }
        break;
    case GM_COMMAND:
        {
            useInterceptPitch = false;

            float tti_s = 999.0f;
            float range3D_rad = 0;
            simData.missileKin.GetInterceptData3D(simData.targetTrack, simData.goalHeading_rad, 
                interceptPitch_rad, tti_s, range3D_rad);
            simData.rangeToObjective_km = simData.missileKin.RangeToKm(simData.targetTrack); // 2D range

			useInterceptPitch = (segmentInfo->meAltitudeMode == AM_INTERCEPT) || 
				((segmentInfo->meAltitudeMode == AM_INTERCEPT_HIGH) && (interceptPitch_rad > 0));



            simData.interceptTime_s = tti_s;


            simData.waypoint.mfLon_rad = simData.targetTrack.mfLon_rad;
            simData.waypoint.mfLat_rad = simData.targetTrack.mfLat_rad;
            simData.waypoint.mfAlt_m = simData.targetTrack.mfAlt_m;

            simData.interceptTime_s = tti_s;
        }
        break;
    case GM_SENSOR1:
        {
        float rangeToTarget_km = simData.missileKin.RangeToKmAlt(simData.targetTrack);
        if (rangeToTarget_km <= simData.seekerDetectionRange_km)
        {
            float tti_s;
            simData.missileKin.GetInterceptData3D(simData.targetTrack, simData.goalHeading_rad, 
                interceptPitch_rad, tti_s, simData.rangeToObjective_km);

            simData.rangeToObjective_km *= C_RADTOKM; // convert to km

            if (simData.kstate.mfAltitude_m <= 4.0) 
            {
                if (interceptPitch_rad < 0) {interceptPitch_rad = 0;}
            }


			useInterceptPitch = (segmentInfo->meAltitudeMode == AM_INTERCEPT) || ((segmentInfo->meAltitudeMode == AM_INTERCEPT_HIGH) && (interceptPitch_rad > 0));



            simData.interceptTime_s = tti_s;

            // update waypoint just in case we want to go back to nav or command
            simData.waypoint.mfLon_rad = simData.targetTrack.mfLon_rad;
            simData.waypoint.mfLat_rad = simData.targetTrack.mfLat_rad;
            simData.waypoint.mfAlt_m = simData.targetTrack.mfAlt_m;
        }
        else 
        {
            //goalAltitude_m = segmentInfo->mfAltitude_m; // used if AltOpt is AM_INTERCEPT
        }
        break;
        }
    case GM_DEPLOY:
        {
            simData.endFlight = true;
            simData.forceHit = true;
        }
        break;
    default:
        break;
    }


	//************ update altitude control **************
	switch (segmentInfo->meAltitudeMode) 
	{
	case AM_ASL:
	case AM_ASL_LOFT:
		simData.goalAltitude_m = segmentInfo->mfAltitude_m;
		break;
	case AM_AGL:
        simData.goalAltitude_m = segmentInfo->mfAltitude_m + simData.terrainHeight_m; 
		break;
	case AM_INTERCEPT:  // use seeker data or maintain altitude
	case AM_INTERCEPT_HIGH:
		break;
	case AM_DATUM: // use intercept pitch from simData.waypoint
		wxASSERT(useInterceptPitch);
		break;
	default:
		simData.goalAltitude_m = 10.0f + simData.terrainHeight_m;
		break;
	}

	if (useInterceptPitch) 
	{
        wxASSERT(!_isnan(interceptPitch_rad));
		simData.goalPitch_rad = interceptPitch_rad;
        simData.goalAltitude_m = IGNORE_GOAL_ALTITUDE;
	}
	else 
	{
        simData.goalPitch_rad = 0; // calculated in UpdateGoalPitch();
	}

	// force level flight for first 0.5 sec for air-launched missiles
    //   if ((simData.kstate.mfFlightTime < 0.5)&&((simData.kstate.mfAltitude_m-simData.terrainHeight_m) > 50.0f)) 
	//{
	//	     simData.goalHeading_rad = simData.missileKin.mfHeading_rad;
    //       simData.goalPitch_rad = simData.missileKin.mfPitch_rad;
    //       simData.goalAltitude_m = IGNORE_GOAL_ALTITUDE;
	//}
	// switch to next flight profile segment if within range
	if (simData.segment < (missileData->mnNumSegments-1)) 
	{
		if (simData.rangeToObjective_km < segmentInfo->mfRange_km) 
		{
			simData.segment++;
		}
	}
}


/**
* Used to change target datum for datalink active condition.
* If in SEEKER_TRACK mode then break the track and adjust targetpos
*/
void tcMissileObject::UpdateTargetPos(float lon_rad, float lat_rad)
{
    if (!datalinkActive) return;

    msWaypoint.mfLon_rad = lon_rad;
    msWaypoint.mfLat_rad = lat_rad;

    tcSensorState* sensor = GetSensorMutable(0);
    if ((sensor != 0) && sensor->IsActive())
    {
        if (sensor->mnMode == SSMODE_SEEKERTRACK)
        {
            sensor->mnMode = SSMODE_SEEKERSEARCH;
        }
        goalHeading_rad = mcKin.HeadingToGeoRad(&msWaypoint);
    }
}


/**
* Called when repairs remove damage. Launchers, sensors, etc.
* are tested for fix.
* @param fractional amount of new repairs
*/
void tcMissileObject::ApplyRepairs(float repair)
{
    mfDamageLevel -= repair;
    if (mfDamageLevel <= 0) mfDamageLevel = 0;

    if (mfDamageLevel > 0) return; // don't bother with sensors if still damaged

    unsigned int nSensors = GetSensorCount();
    for (unsigned int n=0; n<nSensors; n++)
    {
        tcSensorState* sensor = GetSensorMutable(n);
        wxASSERT(sensor);
        
        if (sensor->IsDamaged())
        {
            sensor->SetDamaged(false);
        }
    }

}

/**
*
*/
void tcMissileObject::Clear()  
{  
	tcGameObject::Clear();
    preplanRoute.clear();
	mfGuidanceUpdateInterval = 1.0f; // 1 second default
	mfLastGuidanceUpdate = 0.0f;
	mfInterceptTime = 9999.0f;
}

/**
*
*/
void tcMissileObject::DesignateTarget(long anID) 
{
    SetSeekerTarget(anID);

	tcSensorState* sensor = GetSensorMutable(0);
	if (sensor == 0)
	{
		wxASSERT(false);
		return;
	}

	sensor->mnMode = SSMODE_SEEKERACQUIRE;
}

/**
* Estimate range of missile in km based on launchAltitude_m
*/
float tcMissileObject::EstimateRangeKm(float evalMin_km, float evalMax_km, float evalStep_km, 
                                       float launchSpeed_kts, float launchAltitude_m, float targetAltitude_m, tcMissileDBObject* missileData,
                                       bool logData)
{
    if (missileData == 0)
    {
        wxASSERT(false);
        return 0;
    }

    tcKinematics missileKin;

    missileKin.mfSpeed_kts = launchSpeed_kts;
    missileKin.mfAlt_m = launchAltitude_m;
    missileKin.mfLon_rad = 0;
    missileKin.mfLat_rad = 0;
    missileKin.mfHeading_rad = 0;
    missileKin.mfClimbAngle_rad = 0;
    missileKin.mfPitch_rad = 0;
    missileKin.mfRoll_rad = 0;

    tcTrack targetTrack;
    targetTrack.mfAlt_m = targetAltitude_m;
    targetTrack.mfLon_rad = missileKin.mfLon_rad;
    targetTrack.mfLat_rad = missileKin.mfLat_rad;
    targetTrack.mfSpeed_kts = 0;

    wxString line;
    tcFile log;
    if (logData)
    {
        wxString fileName = wxString::Format("log/%s_%.0f_%.0f.csv", missileData->mzClass.c_str(), launchAltitude_m, targetAltitude_m);
        
        log.Open(fileName,  tcFile::modeWrite | tcFile::modeText);

        line.Printf("Missile:,%s\n", missileData->mzClass.c_str());
        log.WriteString(line.c_str());

        line.Printf("Launch Speed [kts]:,%.0f\n", launchSpeed_kts);
        log.WriteString(line.c_str());

        line.Printf("Launch Altitude [m]:,%.0f\n", launchAltitude_m);
        log.WriteString(line.c_str());

        line.Printf("Target Altitude [m]:,%.0f\n", targetAltitude_m);
        log.WriteString(line.c_str());

        line.Printf("Target Range [km],Flight Range [km],End Altitude [m],End Speed [m/s],Hit?\n");
        log.WriteString(line.c_str());
    }

    float maxHitRange_km = 0;
	unsigned int missCount = 0;

    for (float range_km=evalMin_km; (range_km<evalMax_km) && (missCount < 3); range_km += evalStep_km)
    {
        tcTrack target = targetTrack;
        target.Offset(range_km, missileKin.mfHeading_rad);  // assumes target in front of launching platform

        tcKinematics missile(missileKin);
        bool hit = EvaluateTarget(missile, target, missileData);
        if (hit)
        {
            maxHitRange_km = std::max(maxHitRange_km, range_km);
        }
		else
		{
			missCount++;
		}

        float endRange_km = missileKin.RangeToKm(missile);
        float endAltitude_m = missile.mfAlt_m;
        float endSpeed_mps = C_KTSTOMPS*missile.mfSpeed_kts;
        
        if (logData)
        {
            line.Printf("%.1f,%.1f,%.1f,%.1f,%d\n", range_km, endRange_km, endAltitude_m, endSpeed_mps, hit);
            log.WriteString(line.c_str());
        }
    }


    return maxHitRange_km;
}

/**
* This version uses power-of-two steps to reduce calls to EvaluateTarget
*/
float tcMissileObject::EstimateRangeFaster(float evalMin_km, float evalMax_km, unsigned int nSteps,
                                 float launchSpeed_kts, float launchAltitude_m, float targetAltitude_m, tcMissileDBObject* missileData)
{
    if (missileData == 0)
    {
        wxASSERT(false);
        return 0;
    }

    // search recent estimates for close enough match
    const size_t maxCache = 16;
    const float launchAltThresh_m = 25.0f;
    const float targetAltThresh_m = 25.0f;
    const float launchSpeedThresh_kts = 20.0f;

    struct CacheInfo
    {
        long id;
        float launchSpeed_kts;
        float launchAltitude_m;
        float targetAltitude_m;
        float range_km;
    };
    static std::deque<CacheInfo> cachedEstimates;
    for (size_t n=0; n<cachedEstimates.size(); n++)
    {
        if (cachedEstimates[n].id == missileData->mnKey)
        {
            float launchAltDiff = fabsf(launchAltitude_m - cachedEstimates[n].launchAltitude_m);
            float targetAltDiff = fabsf(targetAltitude_m - cachedEstimates[n].targetAltitude_m);
            float launchSpeedDiff = fabsf(launchSpeed_kts - cachedEstimates[n].launchSpeed_kts);
            if ((launchAltDiff < launchAltThresh_m) && (targetAltDiff < targetAltThresh_m) && (launchSpeedDiff < launchSpeedThresh_kts))
            {
                return cachedEstimates[n].range_km;
            }
        }
    }


    tcKinematics missileKin;

    missileKin.mfSpeed_kts = launchSpeed_kts;
    missileKin.mfAlt_m = launchAltitude_m;
    missileKin.mfLon_rad = 0;
    missileKin.mfLat_rad = 0;
    missileKin.mfHeading_rad = 0;
    missileKin.mfClimbAngle_rad = 0;
    missileKin.mfPitch_rad = 0;
    missileKin.mfRoll_rad = 0;

    tcTrack targetTrack;
    targetTrack.mfAlt_m = targetAltitude_m;
    targetTrack.mfLon_rad = missileKin.mfLon_rad;
    targetTrack.mfLat_rad = missileKin.mfLat_rad;
    targetTrack.mfSpeed_kts = 0;

    

    float maxHitRange_km = evalMin_km;
    float minMissRange_km = evalMax_km;

    float range_km = evalMax_km;
    unsigned int step = 0;

    while ((step++ < nSteps) && (maxHitRange_km < evalMax_km))
    {
        tcTrack target = targetTrack;
        target.Offset(range_km, missileKin.mfHeading_rad); // assumes target in front of launching platform

        tcKinematics missile(missileKin);
        bool hit = EvaluateTarget(missile, target, missileData);
        if (hit)
        {
            maxHitRange_km = std::max(maxHitRange_km, range_km);
        }
        else
        {
            minMissRange_km = std::min(minMissRange_km, range_km);
        }

        range_km = 0.5f*(maxHitRange_km + minMissRange_km);
    }

    // add result to cache
    CacheInfo cacheInfo;

    cacheInfo.id = missileData->mnKey;
    cacheInfo.launchSpeed_kts = launchSpeed_kts;
    cacheInfo.launchAltitude_m = launchAltitude_m;
    cacheInfo.targetAltitude_m = targetAltitude_m;
    cacheInfo.range_km = maxHitRange_km;

    cachedEstimates.push_back(cacheInfo);
    if (cachedEstimates.size() > maxCache)
    {
        cachedEstimates.pop_front();
    }
    wxASSERT(cachedEstimates.size() <= maxCache);
    

    return maxHitRange_km;
}

/**
* Estimate seeker detection range using database ID or general target type
*/
float tcMissileObject::EstimateSeekerDetectionRange(const tcSensorMapTrack& target,tcMissileDBObject* missileData)
{
	const float defaultRange_km = 50.0f;
	const float esmDefaultRange_km = 50.0f;
	tcSensorDBObject* seekerData = dynamic_cast<tcSensorDBObject*>(database->GetObject(missileData->GetSensorKey()));
	if (seekerData == 0) return	defaultRange_km;

	if (tcESMDBObject* esm = dynamic_cast<tcESMDBObject*>(seekerData))
	{
		return esmDefaultRange_km;
	}

	tcDatabaseObject* targetData = database->GetObject(target.GetDatabaseId());
	const tcAirDetectionDBObject* detectionData = dynamic_cast<const tcAirDetectionDBObject*>(targetData);
	const float aspect_deg = 10.0f; // just arbitrarily assume a target aspect for now

	if (tcRadarDBObject* radar = dynamic_cast<tcRadarDBObject*>(seekerData))
	{
		if (radar->isSemiactive) return radar->mfMaxRange_km;
		
		float rcs_dBsm = 15.0f;
		
		if (detectionData != 0)
		{
			rcs_dBsm = detectionData->GetRCS_dBsm(aspect_deg);
		}
		else if (target.IsMissile())
		{
			rcs_dBsm = 5.0f;
		}
		else if (target.IsSurface())
		{
			rcs_dBsm = 35.0f;
		}

		bool overLand = target.IsGround();
		bool overWater = target.IsSurface();

		float detectionRange_km = radar->EstimateDetectionRange(rcs_dBsm, overWater, overLand);
		return std::min(detectionRange_km, radar->mfMaxRange_km);
	}

	if (tcOpticalDBObject* optical = dynamic_cast<tcOpticalDBObject*>(seekerData))
	{
		float signature_dB = 20.0f;
		if (detectionData != 0)
		{
			signature_dB = detectionData->GetIRSig_dB(aspect_deg, 0);
		}
		float detectionRange_km = optical->EstimateDetectionRange(signature_dB, false);
		return std::min(detectionRange_km, optical->mfMaxRange_km);
	}

	return std::min(defaultRange_km, seekerData->mfMaxRange_km);
}

/**
* @return true if target is in range (approximate)
* @param missileKin IS MODIFIED with final missile state, be careful with this.
*/
bool tcMissileObject::EvaluateTarget(tcKinematics& missileKin, const tcSensorMapTrack& target, tcMissileDBObject* missileData, MissileTrajectory* trajectory)
{
    MissileSimData simData;

    simData.kstate.mfAltitude_m = std::max(missileKin.mfAlt_m, 0.0f);
    simData.kstate.mfFlightTime = 0;
    simData.kstate.mfSpeed_mps = (missileKin.mfSpeed_kts > 100) ? C_KTSTOMPS*missileKin.mfSpeed_kts : 0; 
    simData.kstate.mfGroundSpeed_mps = simData.kstate.mfSpeed_mps;
    simData.kstate.mfHeading_rad = missileKin.mfHeading_rad;
    simData.kstate.mfPitch_rad = missileKin.mfPitch_rad;
    simData.missileKin = missileKin;
    simData.targetTrack = target;
    simData.waypoint.mfAlt_m = target.mfAlt_m;
    simData.waypoint.mfLon_rad = target.mfLon_rad;
    simData.waypoint.mfLat_rad = target.mfLat_rad;
    simData.terrainHeight_m = 0;
    simData.seekerDetectionRange_km = EstimateSeekerDetectionRange(target, missileData);
    simData.segment = 0;
    simData.endFlight = false;
    simData.forceHit = false;

	float dt1_s = 0.033f; // initial time step
	float dt2_s = 0.2f;
    float dt_s = dt1_s;
    float tmax = missileData->mfBoostTime_s + missileData->mfSustTime_s + 300.0f;

    float t = 0;
    float distanceFromLaunch_m = 0;
    float lastGuidanceUpdate = -1.0f;
    float guidanceUpdateInterval_s = 0.5f;

    bool simulating = true;
    bool hitTarget = false;
    bool shutdown = false;
    bool crashed = false;

    while ((t < tmax) && simulating)
    {
		dt_s = (t > 15.0f) ? dt2_s : dt1_s;

		t += dt_s;

        Aero::UpdateMissileKState(simData.kstate, missileData, dt_s);

        simData.missileKin.mfSpeed_kts = simData.kstate.mfSpeed_mps*(float)C_MPSTOKTS;	
        simData.missileKin.mfClimbAngle_rad = simData.kstate.mfPitch_rad;
        simData.missileKin.mfPitch_rad = simData.kstate.mfPitch_rad;
        float fHeading_rad = simData.missileKin.mfHeading_rad;
        float fGroundSpeed_mps = simData.kstate.mfGroundSpeed_mps;

        float distance_m = fGroundSpeed_mps * dt_s;
        double fDistance_rad = (double)distance_m * C_MTORAD;
        simData.missileKin.mfLon_rad += fDistance_rad*(double)(sinf(fHeading_rad)/cosf((float)simData.missileKin.mfLat_rad));
        simData.missileKin.mfLat_rad += fDistance_rad*(double)cosf(fHeading_rad); 
        simData.missileKin.mfAlt_m = simData.kstate.mfAltitude_m;

        distanceFromLaunch_m += distance_m;

		if (trajectory != 0)
		{ // save trajectory history
			trajectory->time_s.push_back(t);
			trajectory->range_m.push_back(distanceFromLaunch_m);
			trajectory->altitude_m.push_back(simData.missileKin.mfAlt_m);
			trajectory->speed_mps.push_back(simData.kstate.mfSpeed_mps);
		}

        if ((t-lastGuidanceUpdate) > guidanceUpdateInterval_s)
        {
            UpdateGuidanceSim(simData, missileData);
            lastGuidanceUpdate = t;
        }

        float maxTurn_rad = dt_s * std::min(
            GlimitedTurnRate(simData.missileKin.mfSpeed_kts, missileData), 
            C_PIOVER180*missileData->mfMaxTurnRate_degps); // g-limit or turn rate limit, whichever is less

        /*** heading calculation ***/
        float dh_rad,dh_min,dh_max;
        dh_rad = simData.goalHeading_rad - simData.missileKin.mfHeading_rad;
        radtoplusminuspi(dh_rad); // map dh_deg to [-pi,pi)
        dh_max = maxTurn_rad;
        dh_min = -dh_max;
        if (dh_rad < dh_min) {dh_rad = dh_min;} // restrict to turn rate
        else if (dh_rad > dh_max) {dh_rad = dh_max;}
        simData.missileKin.mfHeading_rad += dh_rad;

        HandlePoleWrap(simData.missileKin);

        if (simData.missileKin.mfHeading_rad >= C_TWOPI) {simData.missileKin.mfHeading_rad -= C_TWOPI;}
        if (simData.missileKin.mfHeading_rad < 0) {simData.missileKin.mfHeading_rad += C_TWOPI;}

        UpdateGoalPitchSim(simData, missileData);	

        /*** pitch calculation ***/
        float dp_rad,dp_min,dp_max;
        dp_rad = simData.goalPitch_rad - simData.missileKin.mfPitch_rad;
        dp_max = maxTurn_rad; // 90 deg/s pitch rate, hard coded for now
        dp_min = -dp_max;
        if (dp_rad < dp_min) {dp_rad = dp_min;} 
        else if (dp_rad > dp_max) {dp_rad = dp_max;}
        simData.missileKin.mfPitch_rad += dp_rad;
        simData.kstate.mfPitch_rad = simData.missileKin.mfPitch_rad;

        crashed = (simData.terrainHeight_m > simData.missileKin.mfAlt_m);
        shutdown = (simData.kstate.mfFlightTime > 20.0f) && 
            (simData.kstate.mfSpeed_mps < missileData->mfShutdownSpeed_mps);
        hitTarget = simData.missileKin.RangeToKm(simData.targetTrack) < 0.1f;

        simulating = !(crashed || shutdown || simData.endFlight || hitTarget);

        if (simData.rangeToObjective_km < 5.0f)
        {
            dt_s = 0.1f;
        }
        else if (simData.rangeToObjective_km < 1.0f)
        {
            dt_s = 0.033333f;
            guidanceUpdateInterval_s = 0.1f;
        }

        simData.targetTrack = simData.targetTrack.PredictAhead(dt_s);
    }

    hitTarget = hitTarget || simData.forceHit;

    if (hitTarget)
    {
        if ((t-lastGuidanceUpdate) > 0)
        {
            UpdateGuidanceSim(simData, missileData);
        }

        dt_s = simData.interceptTime_s;
        simData.missileKin.Extrapolate(dt_s);
    }

    missileKin = simData.missileKin;

    return hitTarget;
}


/**
*
*/
void tcMissileObject::RandInitNear(float afLon, float afLat) 
{

	//strcpy(mzClass.mz,mpDBObject->mzClass.mz);
	mzUnit.AssignRandomStringB();
	mfStatusTime = 0;        
	mcKin.mfLon_rad = afLon + randfc(1.1f);      
	mcKin.mfLat_rad = afLat + randfc(1.1f);
	mcKin.mfAlt_m = 0;               
	mcKin.mfHeading_rad = 360*randf();           
	mcKin.mfSpeed_kts = 100;
	mfDamageLevel = 0;    

	//tcGameObject::RandInitNear(afLon,afLat);
	mcKin.mfAlt_m = 100.0f;  
	SetHeading(mcKin.mfHeading_rad);
	SetSpeed(mcKin.mfSpeed_kts);    
	msKState.mfAltitude_m = mcKin.mfAlt_m;
	msKState.mfPitch_rad = 0.3f;
	msKState.mfSpeed_mps = mcKin.mfSpeed_kts*(float)C_KTSTOMPS;
	mcKin.SetRelativeGeo(msWaypoint, mcKin.mfHeading_rad*(float)C_PIOVER180, 100.0f);
}

/**
* @return ground distance traveled from launch point
*/
float tcMissileObject::GetDistanceFromLaunch() const
{
    return distanceFromLaunch;
}

/**
* If missile is targeting a land datum, gp.mnTargetID will be
* set to -1. Otherwise gp.mnTargetID is set to the intended 
* target of the missile.
*
* @return 1 if missile is in terminal phase
*/
int tcMissileObject::GetGuidanceParameters(tsGuidanceParameters& gp) 
{
	tcSensorState* sensor = GetSensorMutable(0);
	if (sensor == 0) return 0;

	if (sensor->mnMode == SSMODE_SEEKERTRACK) 
	{
		gp.mnTargetID = sensor->mcTrack.mnID;
		gp.mfInterceptTime = mfInterceptTime;
		return 1;
	}
	else if (GetCurrentAltitudeMode() == AM_DATUM)
	{
		gp.mnTargetID = -1;
		gp.mfInterceptTime = mfInterceptTime;
		return 1;
	}
	else
	{
		return 0;
	}
}


float tcMissileObject::GetOpticalCrossSection() const
{
    return mpDBObject->opticalCrossSection_dBsm;
}



float tcMissileObject::GetIRSignature(float az_deg) const
{
    return mpDBObject->GetIRSig_dB(az_deg, tcAirDetectionDBObject::IRMODELA);
}

/**
* @return radar or 0 if sensor isn't a radar or doesn't exist (e.g. AGM cmd-only case)
*/
tcRadar* tcMissileObject::GetSeekerRadar() const
{
	tcSensorState* sensor = GetSensorMutable(0);
	return dynamic_cast<tcRadar*>(sensor);
}

tcSensorState* tcMissileObject::GetSeekerSensor() const
{
	return GetSensorMutable(0);
}

/**
* @return g-limited turn rate in radians/s
*/
float tcMissileObject::GlimitedTurnRate() const
{
    const float C_NUM = 19.0691f; // = (9.81 m/s2) / (kts to mps constant)

    return (C_NUM * mpDBObject->mfGmax) / (mcKin.mfSpeed_kts + 0.1f);
}

/**
* @return g-limited turn rate in radians/s
*/
float tcMissileObject::GlimitedTurnRate(float speed_kts, const tcMissileDBObject* missileData)
{
    const float C_NUM = 19.0691f; // = (9.81 m/s2) / (kts to mps constant)

    return (C_NUM * missileData->mfGmax) / (speed_kts + 0.1f);
}


/**
*
*/
void tcMissileObject::PrintToFile(tcFile& file)
{
	tcString s;
	tcGameObject::PrintToFile(file);
	s.Format(" Missile Object\n");
	file.WriteString(s.GetBuffer());
}

/**
*
*/
void tcMissileObject::SaveToFile(tcFile& file) 
{
    wxASSERT(false); // out of date
	tcGameObject::SaveToFile(file);
	file.Write(&goalHeading_rad,sizeof(goalHeading_rad));
	file.Write(&mfInterceptTime,sizeof(mfInterceptTime));
	file.Write(&mfLastGuidanceUpdate,sizeof(mfLastGuidanceUpdate));
	file.Write(&mfGuidanceUpdateInterval,sizeof(mfGuidanceUpdateInterval));
	file.Write(&msWaypoint,sizeof(msWaypoint));
	file.Write(&mfRangeToObjective_km,sizeof(mfRangeToObjective_km));
	file.Write(&mnCurrentSegment,sizeof(mnCurrentSegment));

	if (tcSensorState* sensor = GetSensorMutable(0))
	{
		sensor->Serialize(file,false);
	}
	file.Write(&msKState,sizeof(msKState));
}

/**
*
*/
void tcMissileObject::LoadFromFile(tcFile& file) 
{
    wxASSERT(false); // out of date
	tcGameObject::LoadFromFile(file);
	file.Read(&goalHeading_rad,sizeof(goalHeading_rad));
	file.Read(&mfInterceptTime,sizeof(mfInterceptTime));
	file.Read(&mfLastGuidanceUpdate,sizeof(mfLastGuidanceUpdate));
	file.Read(&mfGuidanceUpdateInterval,sizeof(mfGuidanceUpdateInterval));
	file.Read(&msWaypoint,sizeof(msWaypoint));
	file.Read(&mfRangeToObjective_km,sizeof(mfRangeToObjective_km));
	file.Read(&mnCurrentSegment,sizeof(mnCurrentSegment));
	if (tcSensorState* sensor = GetSensorMutable(0))
	{
		sensor->Serialize(file,true);
	}
	file.Read(&msKState,sizeof(msKState));
}

/**
*
*/
void tcMissileObject::Serialize(tcFile& file, bool mbLoad) 
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

void tcMissileObject::SetSeekerTarget(long id)
{
    tcSensorState* sensor = GetSensorMutable(0);
	if (sensor == 0)
	{
		wxASSERT(false);
		return;
	}

    long currentTarget = sensor->mcTrack.mnID;

    if (tcGameObject* target = simState->GetObject(currentTarget))
    {
        target->RemoveTargeter(mnID);
    }

    if (tcGameObject* target = simState->GetObject(id))
    {
        target->AddTargeter(mnID);
    }

    sensor->mcTrack.mnID = id;
}

/**
* @return true if missile is currently using or will need illuminator radar for
* future guidance segment
* @param platformId set to id of illuminating platform
*/
bool tcMissileObject::StillNeedsIlluminator(long& platformId) const
{
    platformId = -1;
    tcSensorState* sensor = GetSensorMutable(0);
    if ((sensor == 0) || (!sensor->HasFireControlSensor())) return false;

    wxASSERT(sensor->HasFireControlSensor());

    for (unsigned int n=mnCurrentSegment; n<mpDBObject->mnNumSegments; n++)
    {
        if (mpDBObject->maFlightProfile[n].meGuidanceMode == GM_COMMAND)
        {
            platformId = sensor->GetFireControlPlatform();
            return true;
        }
        else if (mpDBObject->maFlightProfile[n].meGuidanceMode == GM_SENSOR1)
        {
            if (tcRadar* radar = dynamic_cast<tcRadar*>(sensor))
            {
                if (radar->IsSemiactive() || radar->IsCommandReceiver())
                {
                    platformId = sensor->GetFireControlPlatform();
                    return true;
                }
            }
        }
    }

    return false;
}

/**
*
*/
tcMissileObject::tcMissileObject() 
:   tcWeaponObject(), 
    subSurfaceLaunch(false),
    distanceFromLaunch(0),
	mpDBObject(0),
    isTerminal(false),
    isCommandHandoff(false)
{
	Clear();
	mnModelType = MTYPE_MISSILE;
	// tsMissileKState for detailed missile modeling using tcAero 
	memset(&msKState,0x00,sizeof(msKState));

	guidanceStatusTime = 0;
	mfGuidanceUpdateInterval = 0.5f;
	mnCurrentSegment = 0;
	mfRangeToObjective_km = 9999.0f;
	goalPitch_rad = 0.01f;
}

/**
* Copy constructor.
*/
tcMissileObject::tcMissileObject(tcMissileObject& o) 
: tcWeaponObject(o), tcSensorPlatform(o),
	goalHeading_rad(o.goalHeading_rad),
	goalPitch_rad(o.goalPitch_rad),
	mfInterceptTime(o.mfInterceptTime),
    subSurfaceLaunch(o.subSurfaceLaunch),
	mfLastGuidanceUpdate(o.mfLastGuidanceUpdate),
	guidanceStatusTime(o.guidanceStatusTime),
	mfGuidanceUpdateInterval(o.mfGuidanceUpdateInterval),
	msWaypoint(o.msWaypoint),
    preplanRoute(o.preplanRoute),
	mfRangeToObjective_km(o.mfRangeToObjective_km),
	mnCurrentSegment(o.mnCurrentSegment),
	msKState(o.msKState),
	mpDBObject(o.mpDBObject),
    distanceFromLaunch(o.distanceFromLaunch),
    isTerminal(o.isTerminal),
    isCommandHandoff(o.isCommandHandoff)
{
	mnModelType = MTYPE_MISSILE;
}


/**
* Constructor that initializes using info from database entry.
*/
tcMissileObject::tcMissileObject(tcMissileDBObject *obj)
:   tcWeaponObject(obj), 
    subSurfaceLaunch(false),
    distanceFromLaunch(0),
	mpDBObject(obj),
	mfGuidanceUpdateInterval(1.0f), // 1 second default
	mfLastGuidanceUpdate(0),
	guidanceStatusTime(0),
	mfInterceptTime(9999.0f),
	mfRangeToObjective_km(9999.0f),
	mnCurrentSegment(0),
	goalPitch_rad(0.01f),
    isTerminal(false),
    isCommandHandoff(false)
{
	mnModelType = MTYPE_MISSILE;

	tcSensorPlatform::Init(obj->maSensorClass.c_str(), this); // to avoid using this in initializer


	// if these inits are missing, causes a crash with time accel after missile launch
	memset(&msKState,0x00,sizeof(msKState));

    msWaypoint.Set(0, 0, 0);

	// init sensors, only one sensor (primary) supported in this version
	/*
	tcSensorDBObject* databaseObj = dynamic_cast<tcSensorDBObject*>(database->GetObject(obj->maSensorClass.mz));

	if (databaseObj != 0)
	{
		if (tcRadarDBObject* radarData = dynamic_cast<tcRadarDBObject*>(databaseObj))
		{
			sensor = new tcRadar(radarData);
		}
		else if (tcOpticalDBObject* opticalData = dynamic_cast<tcOpticalDBObject*>(databaseObj))
		{
			sensor = new tcOpticalSensor(opticalData);
		}
		else if (tcESMDBObject* esmData = dynamic_cast<tcESMDBObject*>(databaseObj))
		{
			sensor = new tcESMSensor(esmData);
		}
		else
		{
			fprintf(stderr, "tcMissileObject - Unrecognized sensor type for missile (%s)\n", 
				obj->maSensorClass.mz);
		}

	}
    else // modified to handle case for AGMs without a sensor (use pointer for sensorstate?)
    {
#ifdef _DEBUG
        fprintf(stderr, "tcMissileObject - Warning - Sensor not found in DB (%s)\n", obj->maSensorClass.mz);
#endif
    }

	if (sensor)
	{
		sensor->SetParent(this);
		sensor->SetMountAz(0); // missile seeker always points forward
	}
	*/
}

/**
*
*/
tcMissileObject::~tcMissileObject() {}

