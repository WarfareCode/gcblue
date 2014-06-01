/**
** @file tcWaterCM.cpp 
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

#include "tcWaterCM.h"
#include "tcCounterMeasureDBObject.h"
#include "tcPlatformDBObject.h"
#include "tcSensorMap.h"
#include "tcSimState.h"
#include "tc3DPoint.h"
#include "common/tcStream.h"
#include "common/tcObjStream.h"
#include "common/tcGameStream.h"
#include "tcDamageModel.h"
#include "tcLauncher.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


/**
* Load state from game stream
*/
tcGameStream& tcWaterCM::operator<<(tcGameStream& stream)
{
	tcGameObject::operator<<(stream);

    stream >> typeCode;
    stream >> timeRemaining_s;
    stream >> vz_mps;
    stream >> vxy_mps;


	return stream;
}

/**
* Save state to game stream
*/
tcGameStream& tcWaterCM::operator>>(tcGameStream& stream)
{
	tcGameObject::operator>>(stream);

    stream << typeCode;
    stream << timeRemaining_s;
    stream << vz_mps;
    stream << vxy_mps;

	return stream;
}



/**
* Load state from update stream
*/
tcUpdateStream& tcWaterCM::operator<<(tcUpdateStream& stream)
{
    tcGameObject::operator<<(stream);

    return stream;
}

/**
* Save state to update stream
*/
tcUpdateStream& tcWaterCM::operator>>(tcUpdateStream& stream)
{
    tcGameObject::operator>>(stream);

    return stream;
}

/**
* @return damage fraction for new damage, 0 means no new damage
*/
float tcWaterCM::ApplyAdvancedDamage(const Damage& damage, tcGameObject* damager)
{
    bool kill = (damage.waterBlast_psi > 50.0f); // || (damage.fragHits > 0) || (damage.kinetic_J > 0) || (damage.thermal_J_cm2 > 50.0f);

    if (kill)
    {
        ApplyGeneralDamage(1.0f, damager);
        return 1.0f;
    }
    else
    {
        return 0;
    }
}

/**
* apply movement restrictions (based on terrain height and altitude normally)
*/
void tcWaterCM::ApplyRestrictions() 
{
    // destroy on impact with sea bottom, or when operational time runs out
    if ((mcTerrain.mfHeight_m >= mcKin.mfAlt_m)||(timeRemaining_s <= 0))
    {
        mfDamageLevel = 1.0f;
    }    
}

/**
* @returns sonar source level
*/
float tcWaterCM::GetSonarSourceLevel(float az_deg) const
{
    float speed_mps = C_KTSTOMPS * mcKin.mfSpeed_kts;

    float SLp = mpDBObject->GetSourceLevel(speed_mps, -mcKin.mfAlt_m, az_deg);

	return SLp;
}


bool tcWaterCM::IsDecoy() const
{
    return typeCode == CM_DECOY;
}

bool tcWaterCM::IsNoisemaker() const
{
    return typeCode == CM_NOISEMAKER;
}


/**
* Initializes state for launch from game object.
* Adds self to simulation
*
* @param obj launching game object
* @param launcher index of launcher
*/
void tcWaterCM::LaunchFrom(tcGameObject* obj, unsigned nLauncher)
{
    tcLauncher* launcher = 0;

    if (tcPlatformObject* platObj = dynamic_cast<tcPlatformObject*>(obj))
	{
		tc3DPoint launcherPos = platObj->mpDBObject->GetLauncherPosition(nLauncher);
		GeoPoint pos = obj->RelPosToLatLonAlt(launcherPos.x, launcherPos.y,
			launcherPos.z);
		mcKin.mfLon_rad = pos.mfLon_rad;
		mcKin.mfLat_rad = pos.mfLat_rad;
		mcKin.mfAlt_m = pos.mfAlt_m;

        launcher = obj->GetLauncher(nLauncher);
	}
	else
	{
		mcKin.mfLon_rad = obj->mcKin.mfLon_rad;
		mcKin.mfLat_rad = obj->mcKin.mfLat_rad;
		mcKin.mfAlt_m = obj->mcKin.mfAlt_m;

        wxASSERT(false);
	}
	
    mcKin.mfPitch_rad = obj->mcKin.mfClimbAngle_rad;
	mcKin.mfClimbAngle_rad = obj->mcKin.mfClimbAngle_rad;
	mcKin.mfSpeed_kts = obj->mcKin.mfSpeed_kts + 15.0f;
	mcKin.mfHeading_rad = obj->mcKin.mfHeading_rad;
    mfStatusTime = obj->mfStatusTime;
	
    vz_mps = 0;
    vxy_mps = C_KTSTOMPS*mcKin.mfSpeed_kts;

    timeRemaining_s = mpDBObject->lifeSpan_s;

    if (launcher != 0)
    {    
        mcKin.mfHeading_rad += launcher->pointingAngle;
        mcKin.mfHeading_rad += -float(mcKin.mfHeading_rad >= C_TWOPI)*C_TWOPI;
        mcKin.mfClimbAngle_rad += launcher->pointingElevation;
        if (launcher->runDepth_m > 0)
        {
            goalDepth_m = launcher->runDepth_m;
        }

        goalHeading_rad = obj->mcKin.HeadingToGeoRad(&launcher->msDatum);
        goalSpeed_kts = C_MPSTOKTS * mpDBObject->maxSpeed_mps;
    }
    else
    {
        goalDepth_m = 100.0f;
        goalHeading_rad = obj->mcKin.mfHeading_rad + C_PI;
        goalHeading_rad += -C_TWOPI*float(goalHeading_rad >= C_TWOPI);

        goalSpeed_kts = C_MPSTOKTS * mpDBObject->maxSpeed_mps;
    }


    // keep off bottom and surface
    float bottom_m = -obj->mcTerrain.mfHeight_m;
    goalDepth_m = std::max(std::min(goalDepth_m, bottom_m - 15.0f), 5.0f);



    wxString s;
    if (IsNoisemaker())
    {
        s = wxString::Format("NM %d-%d", obj->mnID, launchedCounter++);
    }
    else if (IsDecoy())
    {
        s = wxString::Format("Decoy %d-%d", obj->mnID, launchedCounter++);
    }
    mzUnit = s.c_str();      

	SetAlliance(obj->GetAlliance());     

    tcSimState* simState = tcSimState::Get();
	simState->AddPlatform(static_cast<tcGameObject*>(this));
     
}

void tcWaterCM::Move(float dt_s)
{
    float heading_rad = mcKin.mfHeading_rad;

    float z_m = vz_mps * dt_s;
    float xy_rad = C_MTORAD * vxy_mps * dt_s;

    mcKin.mfLon_rad += xy_rad*(double)(sinf(heading_rad)/cosf((float)mcKin.mfLat_rad));
    mcKin.mfLat_rad += xy_rad*(double)cosf(heading_rad); 
    mcKin.mfAlt_m += z_m;    // use constant downward (slow) velocity for now
}

void tcWaterCM::Update(double t)
{
    float dt_s = (float)(t - mfStatusTime);
    
    UpdateSpeed(dt_s);

    UpdateHeading(dt_s);

    UpdateClimb(dt_s);
    
    Move(dt_s);

    timeRemaining_s -= dt_s;
    
    ApplyRestrictions();

    Update3D();
    
    mfStatusTime = t;    
}

void tcWaterCM::UpdateClimb(float dt_s)
{
    float dalt_m = -goalDepth_m - mcKin.mfAlt_m;
    dalt_m = std::max(std::min(dalt_m, 100.0f), -100.0f);

    float abs_dalt_m = fabsf(dalt_m);
    
    if (IsNoisemaker())
    {
        if (abs_dalt_m < 1.0f)
        {
            goalSpeed_kts = 0;
            return;
        }
        mcKin.mfClimbAngle_rad = (dalt_m > 0) ? 1.569f : -1.569f;
        goalSpeed_kts = 0.01f*C_MPSTOKTS*mpDBObject->maxSpeed_mps * abs_dalt_m;
    }
    else
    {
        dalt_m = std::max(std::min(dalt_m, 100.0f), -100.0f);
        float goalClimb_rad = 0.01f * dalt_m;
        
        float alpha = 0.5f * dt_s;
        mcKin.mfClimbAngle_rad = (1.0f-alpha)*mcKin.mfClimbAngle_rad + alpha*goalClimb_rad;
    }

    mcKin.mfPitch_rad = mcKin.mfClimbAngle_rad;
}

void tcWaterCM::UpdateHeading(float dt_s)
{   
    if (IsNoisemaker() || (timeRemaining_s >= (mpDBObject->lifeSpan_s - 1.0f)))
    {
        return;
    }

    
    float dh_rad = goalHeading_rad - mcKin.mfHeading_rad;
    radtoplusminuspi(dh_rad); // map dh_deg to [-180,180]

    float absdh_rad = fabsf(dh_rad);

    if (absdh_rad < 0.0001f)
    {
        mcKin.mfHeading_rad = goalHeading_rad;
        return;
    }
    

    float dh_max = dt_s * (10.0f * C_PIOVER180); // 10 deg/s turn rate

    dh_rad = std::min(dh_rad, dh_max);
    dh_rad = std::max(dh_rad, -dh_max);

    mcKin.mfHeading_rad += dh_rad;

    mcKin.mfHeading_rad += C_TWOPI* float((mcKin.mfHeading_rad < 0) - (mcKin.mfHeading_rad >= C_TWOPI));
}


void tcWaterCM::UpdateSpeed(float dt_s)
{   
    if (timeRemaining_s > (mpDBObject->lifeSpan_s - 1.0f)) return; // don't apply drag for short time after launch

    float accel_ktsps = 1.0f;
    
    // for noisemaker, decay xy speed and set vertical speed according to goal
    if (IsNoisemaker())
    {
        if (vxy_mps < 0.01f)
        {
            vxy_mps = 0;
            mcKin.mfSpeed_kts = 0;
        }
        else
        {
            vxy_mps = vxy_mps * (1.0f - dt_s);
            mcKin.mfSpeed_kts = C_MPSTOKTS * vxy_mps;
        }

        float dSpeed_kts = goalSpeed_kts - (C_MPSTOKTS * vz_mps);
        float dSpeedMax_kts = dt_s * accel_ktsps;
        dSpeed_kts = std::min(dSpeed_kts, dSpeedMax_kts);
        dSpeed_kts = std::max(dSpeed_kts, -dSpeedMax_kts);

        vz_mps += C_KTSTOMPS * dSpeed_kts;

        
    }
    else // decoy
    {
        float speed_mps = sqrt(vxy_mps*vxy_mps + vz_mps*vz_mps);
        float speed_kts = C_MPSTOKTS * speed_mps;
        float dSpeed_kts = goalSpeed_kts - speed_kts;
        float dSpeedMax_kts = dt_s * accel_ktsps;
        dSpeed_kts = std::min(dSpeed_kts, dSpeedMax_kts);
        dSpeed_kts = std::max(dSpeed_kts, -dSpeedMax_kts);

        speed_kts += dSpeed_kts;
        speed_mps = C_KTSTOMPS * speed_kts;
        vxy_mps = cosf(mcKin.mfClimbAngle_rad) * speed_mps;
        vz_mps = sinf(mcKin.mfClimbAngle_rad) * speed_mps;
        
        mcKin.mfSpeed_kts = C_MPSTOKTS * vxy_mps;
    }
}

/**
 *
 */
tcWaterCM::tcWaterCM() 
  : mpDBObject(0),
    typeCode(0)
{

}


tcWaterCM::tcWaterCM(const tcWaterCM& src) 
{
    wxASSERT(false); // not supported
}

/**
* Constructor that initializes using info from database entry.
*/
tcWaterCM::tcWaterCM(tcCounterMeasureDBObject* obj)
 :  tcGameObject(obj), 
    mpDBObject(obj)
{
    if (obj->subType == "Noisemaker")
    {
        typeCode = CM_NOISEMAKER;
    }
    else if (obj->subType == "Decoy")
    {
        typeCode = CM_DECOY;
    }
    else
    {
        typeCode = 0;
        fprintf(stderr, "tcWaterCM::tcWaterCM - Unrecognized subType (%s)\n",
            obj->subType.c_str());
    }
}

/**
 *
 */
tcWaterCM::~tcWaterCM() 
{
}

