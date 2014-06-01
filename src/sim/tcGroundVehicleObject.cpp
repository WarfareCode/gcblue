/**
**  @file tcGroundVehicleObject.cpp
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

#include "tcGroundVehicleObject.h"
#include "tcPlatformDBObject.h"
#include "tcGroundDBObject.h"
#include "tcMapData.h"
//#include "tcParticleEffect.h"
#include "tc3DModel.h"
#include "common/tcGameStream.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/**
* Load
*/
tcGameStream& tcGroundVehicleObject::operator<<(tcGameStream& stream)
{
    tcPlatformObject::operator<<(stream);

    stream >> vehicleMode;
    stream >> doneDestroyed;
    stream >> lastAlt_m;

    return stream;
}

/**
* Save
*/
tcGameStream& tcGroundVehicleObject::operator>>(tcGameStream& stream)
{
    tcPlatformObject::operator>>(stream);

    stream << vehicleMode;
    stream << doneDestroyed;
    stream << lastAlt_m;

    return stream;
}


void tcGroundVehicleObject::ApplyRestrictions() 
{
    // check for adequate water
    if (mcTerrain.mfHeight_m < 0.0f) 
    {
        mcKin.mfSpeed_kts = 0.0f; // zero speed in water
    }
}


void tcGroundVehicleObject::UpdateHeading(float dt_s) 
{
    float heading_start,heading_end,dh;

    float previous_roll = mcKin.mfRoll_rad;

    float new_roll = 0;

    heading_start = mcKin.mfHeading_rad;

    tcPlatformObject::UpdateHeading(dt_s);

    heading_end = mcKin.mfHeading_rad;
    dh = heading_end - heading_start;


    if (dh != 0) {    // skip rest of function if no heading change
        if (dh > C_PI) {dh -= C_TWOPI;}
        else if (dh < -C_PI) {dh += C_TWOPI;}

        // crude version of induced by center of buoyancy / Cg moment
        new_roll += 0.5f*dh/dt_s;
    }
    float alpha = dt_s; // really dt_s*1.0f, falls apart for dt_s close to or > 1
    mcKin.mfRoll_rad = alpha*new_roll + (1-alpha)*previous_roll;
}

void tcGroundVehicleObject::Update(double afStatusTime) 
{
    const float min_update_s = 0.0f;
    float dt_s = (float)(afStatusTime - mfStatusTime);

    UpdateEffects();

    if (parent != 0) return; // captive, let parent update if applicable
    if (dt_s <= min_update_s) return; // added for pause case
    if (mpDBObject == 0) return;

    if (mfDamageLevel >= 1.0f)
    {
        UpdateDestroyed(afStatusTime);
        mfStatusTime = afStatusTime;
        return;
    }

    UpdateFormationGuidance(); // formation heading/speed calculation

    UpdateHeading(dt_s);

    UpdateSpeed(dt_s);

    UpdateClimb(dt_s);

    ApplyRestrictions();

    Move(dt_s);

    UpdateLauncherState(dt_s);

    UpdateSensors(afStatusTime);

    UpdateAI(afStatusTime);

	UpdateMagazines(afStatusTime);

    Update3D();

    mfStatusTime = afStatusTime; 
}

/**
* Adjust pitch and climb angle to follow terrain while
* moving. Keep vehicle on top of ground.
*/
void tcGroundVehicleObject::UpdateClimb(float dt_s)
{
    const float maxPitch_rad = 0.4f;

    if (dt_s < 0) return;

    float ground_m;
    if (mcKin.mfSpeed_kts == 0)
    {
        ground_m = mcTerrain.mfHeight_m;
    }
    else // update pitch while moving
    {
        ground_m = mapData->GetTerrainHeight(C_180OVERPI*mcKin.mfLon_rad, C_180OVERPI*mcKin.mfLat_rad, mfStatusTime);
        mcTerrain.mfHeight_m = ground_m;

        float dalt_m = ground_m - lastAlt_m;
        float dist_m = C_KTSTOMPS * mcKin.mfSpeed_kts * dt_s; 

        // set pitch to keep vehicle near ground level
        float pitch_rad = atanf(dalt_m / dist_m);
        if (pitch_rad < -maxPitch_rad) pitch_rad = -maxPitch_rad;
        else if (pitch_rad > maxPitch_rad) pitch_rad = maxPitch_rad;

        mcKin.mfPitch_rad = 0.25f * pitch_rad + 0.75f * mcKin.mfPitch_rad;
        mcKin.mfClimbAngle_rad = 0;
    }

    // "float" to ground level
    mcKin.mfAlt_m = 0.25f * ground_m + 0.75f * mcKin.mfAlt_m;

    lastAlt_m = ground_m;

}

void tcGroundVehicleObject::UpdateDestroyed(double t)
{
    float dt_s = (float)(t - mfStatusTime);

    if (mcKin.mfSpeed_kts >= 0.5f)
    {
        mcKin.mfSpeed_kts -= 1.0f * dt_s;
    }
    else
    {
        mcKin.mfSpeed_kts = 0;
        doneDestroyed = true;
    }

    mcKin.mfRoll_rad += 0.01f * dt_s;
    mcKin.mfPitch_rad += 0.001f * dt_s;

    Move(dt_s);
}

void tcGroundVehicleObject::UpdateEffects()
{
    if (model)
    {
        if ((mfDamageLevel > 0.1f) && (mcKin.mfAlt_m > -10.0f))
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



void tcGroundVehicleObject::Clear()  
{  
    tcPlatformObject::Clear();
}


float tcGroundVehicleObject::GetOpticalCrossSection() const
{
    return mpDBObject->opticalCrossSection_dBsm;
}



float tcGroundVehicleObject::GetIRSignature(float az_deg) const
{
    return mpDBObject->GetIRSig_dB(az_deg, tcAirDetectionDBObject::IRMODELA);
}



bool tcGroundVehicleObject::IsDestroyed()
{
    return (mfDamageLevel >= 1.0f);
}


/**
* mapData must be set with static method tcGameObject::SetGameObjectMapData before 
* using this method.
* @see SetGameObjectMapData
*/
void tcGroundVehicleObject::RandInitNear(float afLon_deg, float afLat_deg)
{
    wxASSERT(mapData);
    if (mpDBObject == 0) return;
    mzClass = mpDBObject->mzClass;
    mzUnit = "VEH_";
    mzUnit.AssignRandomSuffix();

    mfStatusTime = 0;       
    GeoPoint randomPoint = mapData->GetRandomPointNear(afLon_deg, afLat_deg, 1.1f, -16000.0f, -20.0f);
    mcKin.mfLon_rad = randomPoint.mfLon_rad;      
    mcKin.mfLat_rad = randomPoint.mfLat_rad;
    mcKin.mfAlt_m = mapData->GetTerrainHeightHighRes(mcKin.mfLon_rad, mcKin.mfLat_rad);

    mcKin.mfHeading_rad = C_TWOPI*randf();           
    mcKin.mfSpeed_kts = 0.25f * mpDBObject->mfMaxSpeed_kts;
    mfDamageLevel = 0;  
    SetHeading(mcKin.mfHeading_rad);
    SetSpeed(mcKin.mfSpeed_kts);   
    SetAltitude(mcKin.mfAlt_m);
}


void tcGroundVehicleObject::PrintToFile(tcFile& file) 
{
    tcPlatformObject::PrintToFile(file);
}


void tcGroundVehicleObject::SaveToFile(tcFile& file) 
{
    tcPlatformObject::SaveToFile(file); 
}


void tcGroundVehicleObject::LoadFromFile(tcFile& file) 
{
    tcPlatformObject::LoadFromFile(file);
}


void tcGroundVehicleObject::Serialize(tcFile& file, bool mbLoad) 
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


tcGroundVehicleObject::tcGroundVehicleObject() 
{
    Clear();
    mpDBObject = NULL;
    mnModelType = MTYPE_GROUNDVEHICLE;
    doneDestroyed = false;
    vehicleMode = READY;
}

tcGroundVehicleObject::tcGroundVehicleObject(tcGroundVehicleObject& o) : tcPlatformObject(o) 
{
    wxASSERT(false); // this method never called?
    mpDBObject = o.mpDBObject;
    doneDestroyed = false;
    vehicleMode = READY;
}

tcGroundVehicleObject::tcGroundVehicleObject(tcGroundDBObject *obj)
: tcPlatformObject(obj),
  doneDestroyed(false),
  vehicleMode(READY),
  lastAlt_m(0)
{
    mpDBObject = obj;
    mnModelType = MTYPE_GROUNDVEHICLE;
    mcGS.mfGoalAltitude_m = 0;
}


tcGroundVehicleObject::~tcGroundVehicleObject() 
{
}