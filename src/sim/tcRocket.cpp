/** 
**  @file tcRocket.cpp
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

#include "tcRocket.h"
#include "tcBallisticDBObject.h"
#include "common/tcStream.h"
#include "common/tcObjStream.h"
#include "common/tcGameStream.h"
#include "database/tcPlatformDBObject.h"
#include "tc3DModel.h"
#include "tcLauncher.h"
#include "tcSimState.h"
#include "tc3DPoint.h"
#include "tcGameObjIterator.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



/**
* Load state from game stream
*/
tcGameStream& tcRocket::operator<<(tcGameStream& stream)
{
	tcBallisticWeapon::operator<<(stream);

	return stream;
}

/**
* Save state to game stream
*/
tcGameStream& tcRocket::operator>>(tcGameStream& stream)
{
	tcBallisticWeapon::operator>>(stream);

	return stream;
}



/**
* Initializes ballistic weapon state for launch from game object.
* Adds self to simulation
*
* @param obj launching game object
* @param launcher index of launcher
*/
void tcRocket::LaunchFrom(tcGameObject* obj, unsigned nLauncher)
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

	mcKin.mfPitch_rad = obj->mcKin.mfPitch_rad;

	mcKin.mfPitch_rad += pLauncher->pointingElevation;
	mcKin.mfHeading_rad += pLauncher->pointingAngle;
	
	// add angle error to model inaccuracy in trajectory
	mcKin.mfHeading_rad += 0.707 * GaussianRandom::Get()->randn_fast() * mpDBObject->angleError_rad;
	mcKin.mfPitch_rad += 0.707 * GaussianRandom::Get()->randn_fast() * mpDBObject->angleError_rad;

	mcKin.mfClimbAngle_rad = mcKin.mfPitch_rad;
	mfStatusTime = obj->mfStatusTime;
	

	if (pLauncher->IsAutoPoint()) // normally should be AutoPoint for rockets to make targeting easier
	{
		mcKin.mfSpeed_kts = C_MPSTOKTS * mpDBObject->launchSpeed_mps;

		/* get intercept az and el to target, if target is bad then launch
		** at 0 deg az, 45 deg el, and write error */
		tcTrack targetTrack;
		float launchAz_rad = 0;
		float launchEl_rad = 0;
		float tti_s;
		float range_km;
		if (simState->GetTruthTrack(pLauncher->mnTargetID, targetTrack))
		{
			mcKin.GetInterceptData3D(targetTrack, launchAz_rad, launchEl_rad, tti_s, range_km);
		}
		else if (!pLauncher->msDatum.IsZero())
		{
			targetTrack.mfLon_rad = pLauncher->msDatum.mfLon_rad;
			targetTrack.mfLat_rad = pLauncher->msDatum.mfLat_rad;
			targetTrack.mfAlt_m = pLauncher->msDatum.mfAlt_m;
			targetTrack.mfSpeed_kts = 0;
			mcKin.GetInterceptData3D(targetTrack, launchAz_rad, launchEl_rad, tti_s, range_km);
		}
		else
		{
			return; // no target ID or datum
		}

		mcKin.mfHeading_rad = launchAz_rad;
		mcKin.mfPitch_rad = launchEl_rad;
	}
	else // assume fixed mounting in forward position
	{
		mcKin.mfSpeed_kts += C_MPSTOKTS * mpDBObject->launchSpeed_mps;
	}

	mcKin.mfHeading_rad += GaussianRandom::Get()->randn_fast() * mpDBObject->angleError_rad;
	mcKin.mfPitch_rad += GaussianRandom::Get()->randn_fast() * mpDBObject->angleError_rad;
	mcKin.mfClimbAngle_rad = mcKin.mfPitch_rad;

	
    launchingPlatform = obj->mnID;

    distFromLaunch_m = 0;

    switch (mpDBObject->ballisticType)
    {
    case tcBallisticDBObject::ROCKET:
        {
            targetPos = pLauncher->msDatum;
        }
        break;
    default:
        wxASSERT(false);
		return; // error
    }

	wxASSERT(pLauncher->meLaunchMode == DATUM_ONLY);


    wxString s = wxString::Format("RKT %d-%d", obj->mnID, launchedCounter++);
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
void tcRocket::Update(double afStatusTime)
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

    float distxy_m = dt_s * vxy_mps;
	float dist = C_MTORAD * distxy_m;
    float dlon = dist * sinf(mcKin.mfHeading_rad) / cosf(mcKin.mfLat_rad);
    float dlat = dist * cosf(mcKin.mfHeading_rad);
	

    float distxyz_m = dt_s * C_KTSTOMPS * mcKin.mfSpeed_kts;
    distFromLaunch_m += distxyz_m;
   

	mcKin.mfLon_rad += dlon;
	mcKin.mfLat_rad += dlat;
	mcKin.mfAlt_m += vz_mps * dt_s;

	// pitch, climb angle, and speed are constant--no need to update

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

    /*** check for impact detonation with ground ***/
	if (distFromLaunch_m < 150.0f) return;

    float terrainHeight_m = mcTerrain.mfHeight_m;
    if (terrainHeight_m < 0) terrainHeight_m = 0;
    // interpret detonation range as altitude of detonation for ground detonation
    float detAlt_m = mpDBObject->detonationRange_m;

    float dz =  terrainHeight_m + detAlt_m - mcKin.mfAlt_m; // height above ground or sea level

    float t_impact = dz / vz_mps;

	if ((t_impact <= 0.03f) && (vz_mps < 0))
	{
		Detonate(0);
		return;
	}

	/*** check for detonation with nearby targets ***/
	tcBallisticWeapon::CheckGravityBombImpact();
}




/**
*
*/
tcRocket::tcRocket() 
: tcBallisticWeapon()
{
	mnModelType = MTYPE_ROCKET;
    mpDBObject = 0;
}

/**
* Copy constructor.
*/
tcRocket::tcRocket(const tcRocket& obj) 
: tcBallisticWeapon(obj)
{
	mnModelType = MTYPE_ROCKET;

    mpDBObject = obj.mpDBObject;
}

/**
* Constructor that initializes using info from database entry.
*/
tcRocket::tcRocket(tcBallisticDBObject* obj)
: tcBallisticWeapon(obj)
{
	mnModelType = MTYPE_ROCKET;

    mpDBObject = obj;
}

/**
*
*/
tcRocket::~tcRocket() 
{
}

