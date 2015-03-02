/**
**  @file tcSurfaceObject.cpp
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

#include "tcSurfaceObject.h"
#include "tcShipDBObject.h"
#include "tcSonar.h"
#include "tcSonarDBObject.h"
#include "tcMapData.h"
//#include "tcParticleEffect.h"
#include "tc3DModel.h"
#include "tcGameStream.h"
#include "ai/Brain.h"
#include "ai/Task.h"
#include <math.h>
#include "tcSonarEnvironment.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/******************************************************************************/
/****************************** tcSurfaceObject *******************************/
/******************************************************************************/

/**
* Save
*/
tcGameStream& tcSurfaceObject::operator>>(tcGameStream& stream)
{
    tcPlatformObject::operator>>(stream);

    stream << doneSinking;

    stream << lastHistoryUpdate;

    wxASSERT(positionHistory.size() < 256);
    unsigned char nHistory = (unsigned char)positionHistory.size();
    stream << nHistory;
    for (unsigned char n=0; n<nHistory; n++)
    {
        stream << positionHistory[n].x;
        stream << positionHistory[n].y;
    }

    return stream;
}

/**
* Load
*/
tcGameStream& tcSurfaceObject::operator<<(tcGameStream& stream)
{
    tcPlatformObject::operator<<(stream);

    stream >> doneSinking;

    stream >> lastHistoryUpdate;

    positionHistory.clear();
    unsigned char nHistory;
    stream >> nHistory;
    for (unsigned char n=0; n<nHistory; n++)
    {
        tcPoint p;
        stream >> p.x;
        stream >> p.y;
        positionHistory.push_back(p);
    }

    return stream;
}

void tcSurfaceObject::ApplyRestrictions() 
{
    // check for adequate water
    if (mcTerrain.mfHeight_m >= 0.0f) 
    {
        mfDamageLevel += 1.0f; // destroy totally beached surface naval (bad random placement?)
    }

    if (mcTerrain.mfHeight_m >= -mpDBObject->draft_m) 
    {
        mcKin.mfSpeed_kts = 0.0f; // zero speed if not
    }

    if (mfDamageLevel < 0.25f)
    {
        return;
    }
    else
    {
		if (mcGS.mfGoalSpeed_kts < 0)
			{ mcGS.mfGoalSpeed_kts = std::min(mcGS.mfGoalSpeed_kts, (1.0f - 0.5f*mfDamageLevel)*mpDBObject->mfMaxSpeed_kts);}
		else
			{ mcGS.mfGoalSpeed_kts = std::max(mcGS.mfGoalSpeed_kts, (1.0f - 0.5f*mfDamageLevel)*-0.5f*mpDBObject->mfMaxSpeed_kts);}
    }
}


float tcSurfaceObject::GetOpticalCrossSection(float view_alt_m, float view_dist_km) const
{
	float wake_horizon_km = 3.57*sqrt(view_alt_m);
	float viewable_wake_dbsm = 0;
	if (view_dist_km < wake_horizon_km) //calculate the wake dBsm if we can see it
	{
		float speed_mps = mcKin.mfSpeed_kts * 0.5144444;
		float speed_kts = mcKin.mfSpeed_kts;
		float tonnage = mpDBObject->weight_kg * 0.001;
		float beam_m = mpDBObject->beam_m;
		if (beam_m == 0)
		{
			float beam = 0.1 * pow(log10f(tonnage) / log10(1.4),1.65);
		}
		float wake_m2 = speed_mps * pow(1.6873323, 0.1 * (speed_kts - 9)) * 0.05 * beam_m * (log10f(speed_kts * speed_kts) / log10f(2.3403474)*100+100);
		float above_horizon_m = view_alt_m - pow(view_dist_km / 3.57,2);
		float slant_range = sqrt(pow(view_alt_m * .001,2) + pow(view_dist_km,2));
		float sin_view_fraction = (above_horizon_m * 0.001) / slant_range;
		float viewable_wake_m2 = sin_view_fraction * wake_m2;
		viewable_wake_dbsm = 10*log10f(viewable_wake_m2);

	}
	int SeaState = tcSonarEnvironment::Get()->GetSeaState();
	float SeaStateHullFactor = 10*log10f(std::max(4, SeaState)-3);
	float SeaStateWakeFactor = 10*log10(pow(std::max(2,SeaState)-1,2));
	float opticalCrossSection = mpDBObject->opticalCrossSection_dBsm;
	float opticalCrossSection_m2 = pow(10,0.1*(opticalCrossSection - SeaStateHullFactor));
	float viewable_wake_m2 = pow(10,0.1*(viewable_wake_dbsm - SeaStateWakeFactor));
	float total_cross_section = 10*log10f(opticalCrossSection_m2 + viewable_wake_m2);

    return total_cross_section;
}

const std::deque<tcPoint>& tcSurfaceObject::GetPositionHistory() const
{
    return positionHistory;
}

float tcSurfaceObject::GetIRSignature(float az_deg) const
{
    return mpDBObject->GetIRSig_dB(az_deg, tcAirDetectionDBObject::IRMODELA);
}


void tcSurfaceObject::UpdateHeading(float dt_s) 
{
    float heading_start,heading_end,dh;

    float previous_roll = mcKin.mfRoll_rad;

    float new_roll = 0.03f*sinf((float)mfStatusTime*0.25f); // sinusoidal "wave roll"

    heading_start = mcKin.mfHeading_rad;

    tcPlatformObject::UpdateHeading(dt_s);

    heading_end = mcKin.mfHeading_rad;
    dh = heading_end - heading_start;


    if (dh != 0) 
    {    // skip rest of function if no heading change
        if (dh > C_PI) {dh -= C_TWOPI;}
        else if (dh < -C_PI) {dh += C_TWOPI;}

        // crude version of induced by center of buoyancy / Cg moment
		new_roll += (dt_s > 0) ? 0.75f*dh/dt_s : 0;
    }
    float alpha = dt_s; // really dt_s*1.0f, falls apart for dt_s close to or > 1
    mcKin.mfRoll_rad = alpha*new_roll + (1-alpha)*previous_roll;
}

void tcSurfaceObject::UpdateHistory(double t)
{
    const double updateInterval = 90.1;
    if (t < (lastHistoryUpdate + updateInterval)) return;
    lastHistoryUpdate = t;

    tcPoint p;
    p.x = mcKin.mfLon_rad;
    p.y = mcKin.mfLat_rad;
    positionHistory.push_front(p);

    if (positionHistory.size() > MAX_HISTORY)
    {
        positionHistory.pop_back();
    }
}

void tcSurfaceObject::Update(double afStatusTime) 
{
    const float min_update_s = 0.0f;
    float dt_s = (float)(afStatusTime - mfStatusTime);

    UpdateEffects();

    if (parent != NULL) {return;} // captive, let parent update if applicable
    if ((dt_s <= min_update_s) && !tcGameObject::IsEditMode())
    {
        return;
    } // added for pause case


    if (mpDBObject == NULL) {return;}

    if (mfDamageLevel >= 1.0f)
    {
        UpdateDestroyed(afStatusTime);
        mfStatusTime = afStatusTime;
        Update3D();
        return;
    }

    UpdateFormationGuidance(); // formation heading/speed calculation

    UpdateHeading(dt_s);

    UpdateSpeed(dt_s);

    //UpdateClimb(dt_s);

    ApplyRestrictions();

    Move(dt_s);

    UpdateLauncherState(dt_s);

    UpdateSensors(afStatusTime);

    UpdateAI(afStatusTime);

	UpdateMagazines(afStatusTime);

    Update3D();

    UpdateHistory(afStatusTime);

    mfStatusTime = afStatusTime;
}

void tcSurfaceObject::UpdateDestroyed(double t)
{
    float dt_s = (float)(t - mfStatusTime);

    if (mcKin.mfSpeed_kts >= 0.5f)
    {
        mcKin.mfSpeed_kts -= 1.0f * dt_s;
    }
    else
    {
        mcKin.mfSpeed_kts = 0;
    }

    mcKin.mfAlt_m -= 0.2 * dt_s;
    mcKin.mfRoll_rad += 0.01f * dt_s;
    mcKin.mfPitch_rad += 0.001f * dt_s;

    if (mcKin.mfAlt_m <= -10.0f)
    {
        doneSinking = true;
    }

    Move(dt_s);
}

void tcSurfaceObject::UpdateEffects()
{
    if (model)
    {
        if ((mfDamageLevel > 0.1f) && (mcKin.mfAlt_m > -10.0f))
		{
			model->SetSmokeMode(tc3DModel::DAMAGE);
		}
		else
		{
			model->SetSmokeMode(tc3DModel::WAKE);
		}

        if (mcKin.mfSpeed_kts > 5)
        {
		    model->SetWakeEnable(true);
        }
        else
        {
            model->SetWakeEnable(false);
        }

        model->UpdateEffects();
    }
}



void tcSurfaceObject::Clear()  
{  
    tcPlatformObject::Clear();
}


/**
* @returns sonar source level of object or, if object has active sonar on, maximum of source level of 
* target and max active sonar source level.
*/
float tcSurfaceObject::GetSonarSourceLevel(float az_deg) const
{
    float SLp = mpDBObject->GetSourceLevel(C_KTSTOMPS*mcKin.mfSpeed_kts, 0, az_deg);

	if (!IsEnsonifying()) return SLp;

	const tcSonar* sonar = GetStrongestActiveSonar();
	if (sonar && (sonar->mpDBObj->SL > SLp))
	{
		return sonar->mpDBObj->SL;
	}
	else
	{
		return SLp;
	}
}

bool tcSurfaceObject::IsDestroyed()
{
    return (mfDamageLevel >= 1.0f) && doneSinking;
}

/**
* @return true if pos is within distance_m of any segment of positionHistory. Set nextPos to next point in
* positionHistory
* Used for wake homing guidance model
*/
bool tcSurfaceObject::IsNearWake(const tcPoint& pos, float distance_m, tcPoint& nextPos, size_t& leg) const
{
    nextPos.x = 0;
    nextPos.y = 0;
    leg = 99;

    if (positionHistory.size() == 0) return false;

    float dy = C_MTORAD * distance_m;
    float cos_lat = cosf(pos.y);
    float xscale = 1.0f / cos_lat;
    float dx = xscale * dy;

    // check most recent leg first, and work back in time
    float x2 = mcKin.mfLon_rad;
    float y2 = mcKin.mfLat_rad;
    for (size_t n=0; n<positionHistory.size(); n++)
    {
        float x1 = positionHistory[n].x;
        float y1 = positionHistory[n].y;

        bool nearx = false;
        if (x2 > x1)
        {
            nearx = (pos.x < (x2 + dx)) && (pos.x > (x1 - dx));
        }
        else
        {
            nearx = (pos.x < (x1 + dx)) && (pos.x > (x2 - dx));
        }

        bool neary = false;
        if (y2 > y1)
        {
            neary = (pos.y < (y2 + dy)) && (pos.y > (y1 - dy));
        }
        else
        {
            neary = (pos.y < (y1 + dy)) && (pos.y > (y2 - dy));
        }

        bool nearsegment = nearx && neary;

        if (nearsegment) // check for min distance to segment
        {
            float ax = (x2 - x1);
            float ay = (y2 - y1);

            float t = (ax*(pos.x - x1) + ay*(pos.y - y1)) / (2.0 * (ax*ax + ay*ay));

            float xterm = cos_lat * (x1 + ax*t - pos.x);
            float yterm = (y1 + ay*t - pos.y);
            float d2 = xterm*xterm + yterm*yterm;

            if (d2 < (dy * dy))
            {
                nextPos.x = x2;
                nextPos.y = y2;
                leg = n;
                return true;
            }
        }

        x2 = x1;
        y2 = y1;
    }

    return false;
}


/******************************************************************************/
/**
* mapData must be set with static method tcGameObject::SetGameObjectMapData before 
* using this method.
* @see SetGameObjectMapData
*/
void tcSurfaceObject::RandInitNear(float afLon_deg, float afLat_deg)
{
    //  tcGameObject::RandInitNear(afLon,afLat);  // why can't we call base here ? virtual issue?
    // TODO fix this
    wxASSERT(mapData);
    if (mpDBObject == NULL) {return;}
    mzClass = mpDBObject->mzClass;
    mzUnit = "SURF_";
    mzUnit.AssignRandomSuffix();

    mfStatusTime = 0;       
    GeoPoint randomPoint = mapData->GetRandomPointNear(afLon_deg, afLat_deg, 1.1f, -16000.0f, -20.0f);
    mcKin.mfLon_rad = randomPoint.mfLon_rad;      
    mcKin.mfLat_rad = randomPoint.mfLat_rad;
    mcKin.mfAlt_m = (mpDBObject->mnType == PTYPE_FIXEDWING) ? 5000.0f : 0.0f; 

    mcKin.mfHeading_rad = C_TWOPI*randf();           
    mcKin.mfSpeed_kts = mpDBObject->mfMaxSpeed_kts;
    mfDamageLevel = 0;  
    SetHeading(mcKin.mfHeading_rad);
    SetSpeed(mcKin.mfSpeed_kts);   
    SetAltitude(mcKin.mfAlt_m);
}


void tcSurfaceObject::PrintToFile(tcFile& file) 
{
    tcPlatformObject::PrintToFile(file);
}

void tcSurfaceObject::SaveToFile(tcFile& file) 
{
    tcPlatformObject::SaveToFile(file); 
}


void tcSurfaceObject::LoadFromFile(tcFile& file) 
{
    tcPlatformObject::LoadFromFile(file);
}

void tcSurfaceObject::Serialize(tcFile& file, bool mbLoad) 
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

tcSurfaceObject::tcSurfaceObject() 
{
    Clear();
    mpDBObject = NULL;
    mnModelType = MTYPE_SURFACE;
}

tcSurfaceObject::tcSurfaceObject(tcSurfaceObject& o) : tcPlatformObject(o) 
{
    mpDBObject = o.mpDBObject;
}

tcSurfaceObject::tcSurfaceObject(tcShipDBObject *obj)
: tcPlatformObject(obj),
  doneSinking(false)
{
    mpDBObject = obj;
    mnModelType = MTYPE_SURFACE;
    mcGS.mfGoalAltitude_m = 0;

    lastHistoryUpdate = 3.0f*randf();

    if (addTasksOnCreate) brain->AddTaskDirectly("MissileWarning", 3.0, ai::Task::HIDDEN | ai::Task::PERMANENT);
    if (addTasksOnCreate) brain->AddTaskDirectly("PointDefense", 3.0, ai::Task::HIDDEN | ai::Task::PERMANENT);
}

/******************************************************************************/
tcSurfaceObject::~tcSurfaceObject() 
{
}