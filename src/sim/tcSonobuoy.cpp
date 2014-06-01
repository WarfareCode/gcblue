/**
**  @file tcSonobuoy.cpp
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

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "tcSonobuoy.h"
#include "tc3DPoint.h"
#include "math_constants.h"
#include "tcGameObject.h"
#include "tcPlatformDBObject.h"
#include "tcLauncher.h"
#include "tcPlatformObject.h"
#include "tcSimState.h"
#include "tcSonobuoyDBObject.h"
#include "common/tcGameStream.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


/**
* Load
*/
tcGameStream& tcSonobuoy::operator<<(tcGameStream& stream)
{
    tcGameObject::operator<<(stream);
    tcSensorPlatform::operator<<(stream);

    stream >> batteryTimeRemaining_s;
    stream >> parentId;
	stream >> sonobuoyDepth_m;

    return stream;
}

/**
* Save
*/
tcGameStream& tcSonobuoy::operator>>(tcGameStream& stream)
{
    tcGameObject::operator>>(stream);
    tcSensorPlatform::operator>>(stream);

    stream << batteryTimeRemaining_s;
    stream << parentId;
	stream << sonobuoyDepth_m;

    return stream;
}

void tcSonobuoy::Clear() 
{
    tcGameObject::Clear();
}



void tcSonobuoy::PrintToFile(tcFile& file) 
{
   tcGameObject::PrintToFile(file);
   tcSensorPlatform::PrintToFile(file);
}

void tcSonobuoy::SaveToFile(tcFile& file) 
{
   tcGameObject::SaveToFile(file);
   tcSensorPlatform::SaveToFile(file);
}

void tcSonobuoy::LoadFromFile(tcFile& file) 
{
   tcGameObject::LoadFromFile(file);
   tcSensorPlatform::LoadFromFile(file);
}

void tcSonobuoy::Serialize(tcFile& file, bool mbLoad) 
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
* Initializes sonobuoy for launch from game object.
* Adds self to simulation
*
* @param obj launching game object
* @param launcher index of launcher
*/
void tcSonobuoy::LaunchFrom(tcGameObject* obj, unsigned nLauncher)
{
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
        wxASSERT(false);

		mcKin.mfLon_rad = obj->mcKin.mfLon_rad;
		mcKin.mfLat_rad = obj->mcKin.mfLat_rad;
		mcKin.mfAlt_m = obj->mcKin.mfAlt_m;
	}

    mcKin.mfSpeed_kts = obj->mcKin.mfSpeed_kts;
    parentId = obj->mnID;

	const tcLauncher* pLauncher = obj->GetLauncher(nLauncher);

	mcKin.mfHeading_rad = obj->mcKin.mfHeading_rad + pLauncher->pointingAngle;
	mcKin.mfPitch_rad = obj->mcKin.mfPitch_rad + pLauncher->pointingElevation;
	mcKin.mfClimbAngle_rad = mcKin.mfPitch_rad;

	mfStatusTime = obj->mfStatusTime;

   

    wxString s = wxString::Format("Sonobuoy %d-%d", obj->mnID, launchedCounter++);
    mzUnit = s.c_str();           
	SetAlliance(obj->GetAlliance());     

	simState->AddPlatform(static_cast<tcGameObject*>(this));
}


/**
*
*/
void tcSonobuoy::Update(double afStatusTime) 
{
	const float min_update_s = 0.0f;
	float dt_s = (float)(afStatusTime - mfStatusTime);

	if (dt_s <= min_update_s) {return;} // added for pause case

    // air launched buoys drop into water first
    bool outOfWater = (mcKin.mfAlt_m > -sonobuoyDepth_m);
    if (outOfWater)
    {
        UpdateDrop(dt_s);
        mfStatusTime = afStatusTime;
        return;
    }

    // cheesy wave bob effect
    mcKin.mfAlt_m = 0.25f * cos(0.7f * afStatusTime) - sonobuoyDepth_m - 0.5;

    // TODO: Check that parent platform is in range before updating sensors
    tcSensorPlatform::Update(afStatusTime);

    batteryTimeRemaining_s -= dt_s;

    if (batteryTimeRemaining_s <= 0)
    {
        ApplyGeneralDamage(1.0f, 0);
    }

    Update3D();

	mfStatusTime = afStatusTime; 
}




/**
*
*/
void tcSonobuoy::UpdateDrop(float dt_s)
{
    float heading_rad = mcKin.mfHeading_rad;
    float fGroundSpeed_kts = cosf(mcKin.mfClimbAngle_rad) * mcKin.mfSpeed_kts;
    float vz_mps = C_KTSTOMPS * sinf(mcKin.mfClimbAngle_rad) * mcKin.mfSpeed_kts;
    float vxy_mps = C_KTSTOMPS * fGroundSpeed_kts;
    //float z = mcKin.mfAlt_m;

    float dvz = C_G * dt_s;

    if (vz_mps < -50.0f)
    {
        dvz = 0;
    }
    else if (vz_mps < -40.0f)
    {
        dvz = 0.1f * (vz_mps + 50.0f) * dvz; // gradually limit acceleration
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
    mcKin.mfPitch_rad = 0;
    mcKin.mfSpeed_kts = C_MPSTOKTS * sqrtf(vz_mps*vz_mps + vxy_mps*vxy_mps);
    
    // stop and activate all sensors after hitting water
    if (mcKin.mfAlt_m <= -sonobuoyDepth_m)
    {
        mcKin.mfAlt_m = -sonobuoyDepth_m;
        mcKin.mfSpeed_kts = 0; 
        unsigned nSensors = tcSensorPlatform::GetSensorCount();
        for (unsigned n=0; n<nSensors; n++)
        {
            tcSensorPlatform::SetSensorState(n, true);
        }
    }

    if (mcKin.mfAlt_m < mcTerrain.mfHeight_m)
    {
        ApplyGeneralDamage(1.0f, 0); // don't allow buoys to operate on land
    }

	
}

/**
*
*/
tcSonobuoy::tcSonobuoy()
: mpDBObject(0)
{
    wxASSERT(false);
    Clear();

    mnModelType = MTYPE_SONOBUOY;
}



/**
* Constructor that initializes using info from database entry.
*/
tcSonobuoy::tcSonobuoy(tcSonobuoyDBObject *obj)
:   tcGameObject(obj), tcSensorPlatform(),
    mpDBObject(obj),
    batteryTimeRemaining_s(obj->batteryLife_s),
    parentId(-1),
	sonobuoyDepth_m(8.0f)
{
    tcSensorPlatform::Init(obj, this);

	mcKin.mfSpeed_kts = 0; 
	mnModelType = MTYPE_SONOBUOY;
}

tcSonobuoy::~tcSonobuoy() 
{
}