/** 
**  @file tcGuidedBomb.cpp
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

#include "tcGuidedBomb.h"
#include "tcBallisticDBObject.h"
#include "common/tcStream.h"
#include "common/tcObjStream.h"
#include "common/tcGameStream.h"
#include "database/tcPlatformDBObject.h"
#include "tc3DModel.h"
#include "tcLauncher.h"
#include "tcSimState.h"
#include "tc3DPoint.h"
#include "tcOpticalSensor.h"
#include "tcGameObjIterator.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



/**
* Load state from game stream
*/
tcGameStream& tcGuidedBomb::operator<<(tcGameStream& stream)
{
	tcBallisticWeapon::operator<<(stream);

    tcSensorPlatform::operator<<(stream);

	return stream;
}

/**
* Save state to game stream
*/
tcGameStream& tcGuidedBomb::operator>>(tcGameStream& stream)
{
	tcBallisticWeapon::operator>>(stream);

    tcSensorPlatform::operator>>(stream);

	return stream;
}



/**
* Initializes ballistic weapon state for launch from game object.
* Adds self to simulation
*
* @param obj launching game object
* @param launcher index of launcher
*/
void tcGuidedBomb::LaunchFrom(tcGameObject* obj, unsigned nLauncher)
{
    const tcLauncher* pLauncher = obj->GetLauncher(nLauncher);

    if (tcPlatformObject* platObj = dynamic_cast<tcPlatformObject*>(obj))
	{
		tc3DPoint launcherPos = platObj->mpDBObject->GetLauncherPosition(nLauncher);
		GeoPoint pos = obj->RelPosToLatLonAlt(launcherPos.x, launcherPos.y,
			launcherPos.z);
		mcKin.mfLon_rad = pos.mfLon_rad;
		mcKin.mfLat_rad = pos.mfLat_rad;
		mcKin.mfAlt_m = pos.mfAlt_m;
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

    launchingPlatform = obj->mnID;

    distFromLaunch_m = 0;

    switch (mpDBObject->ballisticType)
    {
    
    case tcBallisticDBObject::SMART_BOMB:
        {
            targetPos = pLauncher->msDatum;
            float northError_m = 0.707 * GaussianRandom::Get()->randn_fast() * mpDBObject->smartError_m;
            float eastError_m = 0.707 * GaussianRandom::Get()->randn_fast() * mpDBObject->smartError_m;
            
            latError_rad = C_MTORAD * northError_m;
            lonError_rad = C_MTORAD * eastError_m / cosf(obj->mcKin.mfLat_rad);
        }
        break;
    default:
        wxASSERT(false);
    }

    // if bomb has a semiactive sensor, then set the fire control info
    tcSensorState* sensor = GetSensorMutable(0);
    tcOpticalSensor* optical = dynamic_cast<tcOpticalSensor*>(sensor);
    if ((optical != 0) && (optical->IsSemiactive()))
    {
        if (pLauncher->fireControlSensor != 0)
		{
            wxASSERT(dynamic_cast<tcOpticalSensor*>(pLauncher->fireControlSensor) != 0);
			sensor->SetFireControlSensor(
				obj->mnID, pLauncher->fireControlSensorIdx);
			pLauncher->fireControlSensor->RequestTrack(pLauncher->mnTargetID);
		}
    }


    if ((pLauncher->meLaunchMode == SEEKER_TRACK) 
		|| (pLauncher->meLaunchMode == FC_TRACK))
	{
		wxASSERT(sensor != 0);
		if (sensor != 0)
        {		
            sensor->SetActive(true);
            sensor->mnMode = SSMODE_SEEKERACQUIRE;
            sensor->mfLastScan = -30; // ensure rapid update to get a valid track for guidance
            sensor->mcTrack.mnID = pLauncher->mnTargetID;
        }
        else
        {
            wxASSERT(false);
            return;
        }
	}
    else if (pLauncher->meLaunchMode == DATUM_ONLY)
    {
        if (sensor != 0)
        {
            wxASSERT(mpDBObject->lockOnAfterLaunch);
            sensor->SetActive(false);
            sensor->mfLastScan = -30;
        }
    }
    else
    {
        wxASSERT(false);
    }


    wxString s = wxString::Format("GB %d-%d", obj->mnID, launchedCounter++);
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
void tcGuidedBomb::Update(double afStatusTime)
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

    // check for a current seeker track, and update targetPos
    bool trackIsGood = false;
    tcSensorState* sensor = GetSensorMutable(0);
    if (sensor != 0)
    {
        UpdateSensor(sensor, afStatusTime);

        if (sensor->IsActive() && (sensor->mnMode == SSMODE_SEEKERTRACK))
        {
            tcTrack predictedtrack;   
            sensor->mcTrack.GetPrediction(predictedtrack, afStatusTime);
            targetPos.mfLon_rad = predictedtrack.mfLon_rad;
            targetPos.mfLat_rad = predictedtrack.mfLat_rad;
            targetPos.mfAlt_m = predictedtrack.mfAlt_m;

            targetPos.mfLat_rad += latError_rad;
            targetPos.mfLon_rad += lonError_rad;

            trackIsGood = (sensor->mcTrack.mfTimestamp > (afStatusTime - 20.0));

            if (trackIsGood)
            {
                UpdateSmartBombMotion(dt_s);
            }
            else
            {
                vz_mps += -C_G * dt_s; // if sensor is active and tracking, but has lost track, let bomb fall off target
            }
        }
        else
        {
            UpdateSmartBombMotion(dt_s);
        }
    }
    else
    {
        UpdateSmartBombMotion(dt_s); // with no sensor assume GPS guidance
    }



    float distxy_m = dt_s * vxy_mps;
	float dist = C_MTORAD * distxy_m;
    float dlon = dist * sinf(mcKin.mfHeading_rad) / cosf(mcKin.mfLat_rad);
    float dlat = dist * cosf(mcKin.mfHeading_rad);
	
    distFromLaunch_m += distxy_m;
    
	mcKin.mfLon_rad += dlon;
	mcKin.mfLat_rad += dlat;
	mcKin.mfAlt_m += vz_mps * dt_s;

	mcKin.mfPitch_rad = atan2f(vz_mps, vxy_mps);
	mcKin.mfClimbAngle_rad = mcKin.mfPitch_rad;
	mcKin.mfSpeed_kts = C_MPSTOKTS * sqrtf(vxy_mps*vxy_mps + vz_mps*vz_mps);

    HandlePoleWrap();

    Update3D();

	if (clientMode) return;

    UpdateDatalinkStatus();

    if ((mpDBObject->maxRange_km > 0) && 
        (distFromLaunch_m > 1000.0f * mpDBObject->maxRange_km))
    {
        SelfDestruct();
    }

    if (mcKin.mfAlt_m < -1.0f)
    {
        SelfDestruct();
    }

    /*** check for impact ***/
    wxASSERT(mpDBObject->ballisticType == tcBallisticDBObject::SMART_BOMB);
    
    UpdateSmartBombFuse();

    tcSensorPlatform::Update(afStatusTime);
}


void tcGuidedBomb::UpdateSensor(tcSensorState* sensor, double t)
{
    const float maximumSearchDistance_km = 2.0f; // only lock on targets within this distance of targetPos

    wxASSERT(sensor != 0);

    // if sensor isn't active, then check if we're within range of target datum and, if so, start sensor search
    if (!sensor->IsActive())
    {
        float rangeToTarget_km = mcKin.RangeToKmAlt(targetPos.mfLon_rad, targetPos.mfLat_rad, targetPos.mfAlt_m);
        if (rangeToTarget_km <= 0.9f*sensor->mpDBObj->mfMaxRange_km)
        {
            sensor->SetActive(true);
            sensor->mnMode = SSMODE_SEEKERSEARCH;
        }
        else
        {
            return;
        }
    }

    wxASSERT(sensor->IsActive());

    // if sensor is in search mode, do custom search here to find detectable target that is closest to targetPos
    if (sensor->mnMode == SSMODE_SEEKERSEARCH)
    {
        tcGeoRect region;   
        sensor->GetTestArea(region);

        tcGameObjIterator iter(region);
        float closestRange_km = 1e15f;
        long closestID = -1;

        // find closest detectable target to targetPos
        for (iter.First();iter.NotDone();iter.Next())
        {
            tcGameObject *target = iter.Get();
            if (target != parent) // no self detection
            {
                float range_km;
                /* Substitute this to disable own-alliance seeker detections:
                ** bool bDetected = (parent->GetAlliance() != target->GetAlliance()) &&
                **    CanDetectTarget(target,range_km);
                */
                bool isDetected = sensor->CanDetectTarget(target, range_km);
                if (isDetected)
                {
                    float rangeFromTarget_km = target->mcKin.RangeToKm(&targetPos);
                    if (rangeFromTarget_km < closestRange_km)
                    {
                        closestID = target->mnID;
                        closestRange_km = rangeFromTarget_km;
                    }
                }
            }
        }

        if ((closestID != -1) && (closestRange_km <= maximumSearchDistance_km))
        {
            SetIntendedTarget(closestID);
            sensor->mcTrack.mnID = closestID;
            sensor->mnMode = SSMODE_SEEKERTRACK;
            sensor->mfLastScan = t - 30.0f; // to force fast switch to track for optical
        }
    }

    if (sensor->mnMode == SSMODE_SEEKERTRACK)
    {
        tcSensorPlatform::Update(t);
    }
    
}

/**
* Used to change target datum for datalink active condition.
* If in SEEKER_TRACK mode then break the track and adjust targetpos
*/
void tcGuidedBomb::UpdateTargetPos(float lon_rad, float lat_rad)
{
    if (!datalinkActive) return;

    targetPos.mfLon_rad = lon_rad;
    targetPos.mfLat_rad = lat_rad;
    targetPos.mfAlt_m = tcMapData::Get()->GetTerrainHeight(C_180OVERPI*lon_rad, C_180OVERPI*lat_rad, mfStatusTime);

    targetPos.mfLat_rad += latError_rad;
    targetPos.mfLon_rad += lonError_rad;

    tcSensorState* sensor = GetSensorMutable(0);
    if ((sensor != 0) && sensor->IsActive() && (sensor->mnMode == SSMODE_SEEKERTRACK))
    {
        sensor->mnMode = SSMODE_SEEKERSEARCH;
    }
}


/**
*
*/
tcGuidedBomb::tcGuidedBomb() 
: tcBallisticWeapon()
{
	mnModelType = MTYPE_LASERGUIDEDBOMB;
    mpDBObject = 0;
}

/**
* Copy constructor.
*/
tcGuidedBomb::tcGuidedBomb(const tcGuidedBomb& obj) 
: tcBallisticWeapon(obj), tcSensorPlatform(obj)
{
	mnModelType = MTYPE_LASERGUIDEDBOMB;

    mpDBObject = obj.mpDBObject;
}

/**
* Constructor that initializes using info from database entry.
*/
tcGuidedBomb::tcGuidedBomb(tcBallisticDBObject* obj)
: tcBallisticWeapon(obj),
  latError_rad(0.002f),
  lonError_rad(0.002f)
{
	mnModelType = MTYPE_LASERGUIDEDBOMB;

    tcSensorPlatform::Init(obj->sensorClass.c_str(), this); // to avoid using this in initializer

    mpDBObject = obj;
}

/**
*
*/
tcGuidedBomb::~tcGuidedBomb() 
{
}

