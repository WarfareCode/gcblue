/**
**  @file tcBallisticMissile.cpp
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
#include "tcBallisticMissile.h"
#include "common/tcStream.h"
#include "common/tcObjStream.h"
#include "common/tcGameStream.h"
#include "database/tcPlatformDBObject.h"

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
tcUpdateStream& tcBallisticMissile::operator<<(tcUpdateStream& stream)
{
	tcWeaponObject::operator<<(stream);

	return stream;
}

/**
* Save state to update stream
*/
tcUpdateStream& tcBallisticMissile::operator>>(tcUpdateStream& stream)
{
	tcWeaponObject::operator>>(stream);

	return stream;
}




/**
* Load state from game stream
*/
tcGameStream& tcBallisticMissile::operator<<(tcGameStream& stream)
{
	tcWeaponObject::operator<<(stream);

    stream >> subSurfaceLaunch;

    stream >> lastGuidanceUpdateTime;
    stream >> guidanceUpdateInterval;
    stream >> flightTime_s;
    stream >> thrustShutoffTime_s;

    targetDatum << stream;

    stream >> x;
    stream >> y;
    stream >> z;
    stream >> vx;
    stream >> vy;
    stream >> vz;
    stream >> xt;
    stream >> yt;
    stream >> zt;
    stream >> rt;

    stream >> gx;
    stream >> gy;
    stream >> gz;

    stream >> speed_mps;
    stream >> speed2_mps2;
    stream >> r_ecef;

    stream.ReadCheckValue(6223);

	return stream;
}

/**
* Save state to game stream
*/
tcGameStream& tcBallisticMissile::operator>>(tcGameStream& stream)
{
	tcWeaponObject::operator>>(stream);

    stream << subSurfaceLaunch;

    stream << lastGuidanceUpdateTime;
    stream << guidanceUpdateInterval;
    stream << flightTime_s;
    stream << thrustShutoffTime_s;

    targetDatum >> stream;

    stream << x;
    stream << y;
    stream << z;
    stream << vx;
    stream << vy;
    stream << vz;
    stream << xt;
    stream << yt;
    stream << zt;
    stream << rt;

    stream << gx;
    stream << gy;
    stream << gz;

    stream << speed_mps;
    stream << speed2_mps2;
    stream << r_ecef;

    stream.WriteCheckValue(6223);

	return stream;
}




/**
* Initializes missile state for launch from game object.
* Adds self to simulation
*
* @param obj launching game object
* @param launcher index of launcher
*/
void tcBallisticMissile::LaunchFrom(tcGameObject* obj, unsigned nLauncher)
{
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
        if (tcSubObject* sub = dynamic_cast<tcSubObject*>(obj))
        {
            subSurfaceLaunch = true;
        }

        pLauncher = obj->GetLauncher(nLauncher);
	}
	else
	{
        fprintf(stderr, "tcBallisticMissile::LaunchFrom - Bad launch platform type\n");
        return;
	}

	mcKin.mfSpeed_kts = C_MPSTOKTS * mpDBObject->launchSpeed_mps;
	mcKin.mfHeading_rad = obj->mcKin.mfHeading_rad + pLauncher->pointingAngle;
	mcKin.mfPitch_rad = obj->mcKin.mfPitch_rad + pLauncher->GetPointingElevation();
	mcKin.mfClimbAngle_rad = mcKin.mfPitch_rad;

    CalculateECEF();

    // calculate target ECEF coordinates
    targetDatum = pLauncher->msDatum;
    const double Rearth_m = double(C_REARTHM);
    rt = Rearth_m + targetDatum.mfAlt_m;
    zt = rt * sin(targetDatum.mfLat_rad);
    double R_cos_lat = rt * cos(targetDatum.mfLat_rad);
    xt = R_cos_lat * cos(targetDatum.mfLon_rad);
    yt = R_cos_lat * sin(targetDatum.mfLon_rad);

    thrustShutoffTime_s = mpDBObject->thrustShutoffTime_s; // start with full thrust profile

	mfStatusTime = obj->mfStatusTime;


    wxString s = wxString::Format("BM %d-%d", obj->mnID, launchedCounter++);
  
	/* Workaround, for some reason duplicate names were appearing with missiles
	** despite statistical unlikelihood. E.g. Missile 11-133 showed up three times!?
	** Changed from 3 to 4 digit random suffix and added test and second chance to 
	** get a unique object name.
	*/
	if (simState->GetObjectByName(s.ToStdString()))
	{
        wxASSERT(false); // checkpoint to see if this ever happens
        launchedCounter += 1000;
        s = wxString::Format("BM %d-%d", obj->mnID, launchedCounter++);
	}

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
void tcBallisticMissile::Update(double t)
{
	float dt_s = (float)(t - mfStatusTime);

	wxASSERT(mpDBObject != NULL);
    
    if (subSurfaceLaunch)
    {
        UpdateSubsurface(t);
        return;
    }
   
	mfStatusTime = t;

    if (!clientMode)
    {
        UpdateGuidance(t);

        UpdateFlight(dt_s);

	    UpdateEffects();

        Update3D();
    }
    else // MP client mode
    {
        UpdateFlight(dt_s);
	    UpdateEffects();
        Update3D();
        return;
    }


    guidanceUpdateInterval = (flightTime_s < (thrustShutoffTime_s - 1.0f)) ? 1.0f : 0.01f;

    

    UpdateDetonation();

    

	/*** check for crash ***/
    bool underWater = (mcKin.mfAlt_m <= 0.0f);
    bool seaSurfaceCrash = (!subSurfaceLaunch) && underWater;

    // clear subSurfaceLaunch once weapon breaks surface
    if (!underWater) subSurfaceLaunch = false;


	if ((mcTerrain.mfHeight_m >= mcKin.mfAlt_m) || seaSurfaceCrash || payloadDeployed)
    {
        ApplyGeneralDamage(1.0f, 0);

        if (!payloadDeployed)
        {
            tcString s;
            s.Format("Object %s crashed at time %.1f lon %.3f, lat %.3f",
                mzUnit.c_str(), t, mcKin.mfLon_rad*C_180OVERPI, mcKin.mfLat_rad*C_180OVERPI);
            WTL(s.GetBuffer());
        }
	}


}

void tcBallisticMissile::UpdateSubsurface(double t)
{
    wxASSERT(subSurfaceLaunch);

    float dt_s = (float)(t - mfStatusTime);

    float speed_mps = C_KTSTOMPS * mcKin.mfSpeed_kts;
    
    float alpha = dt_s;
    speed_mps = (1-alpha)*speed_mps + alpha*2.0f; // settle to 2 m/s
    mcKin.mfSpeed_kts = speed_mps*(float)C_MPSTOKTS;

    mcKin.mfClimbAngle_rad = (1-alpha)*mcKin.mfClimbAngle_rad + alpha*1.55f; // settle to 89 deg pitch, floating up
    mcKin.mfPitch_rad = mcKin.mfClimbAngle_rad;

    float heading_rad = mcKin.mfHeading_rad;

    float distance_m = speed_mps * dt_s;
    double distance_rad = (double)distance_m * C_MTORAD;
    mcKin.mfLon_rad += distance_rad*(double)(sinf(heading_rad)/cosf((float)mcKin.mfLat_rad));
    mcKin.mfLat_rad += distance_rad*(double)cosf(heading_rad); 
    mcKin.mfAlt_m += distance_m * sinf(mcKin.mfClimbAngle_rad);

    HandlePoleWrap();

    bool underWater = (mcKin.mfAlt_m <= 0.0f);

    // clear subSurfaceLaunch once weapon breaks surface
    if (!underWater)
    {
        CalculateECEF();
        subSurfaceLaunch = false;
    }

    mfStatusTime = t;

    UpdateEffects();

    Update3D();
}


void tcBallisticMissile::UpdateDetonation()
{    
    const float tminDet_s = 0.05f;

    if ((mcKin.mfClimbAngle_rad > 0) || (mcKin.mfAlt_m > 30e3)) return;

    float terrainHeight_m = std::max(mcTerrain.mfHeight_m, 0.0f);
    // interpret detonation range parameter as altitude of detonation
    // if payloadClass is non-empty then use this altitude to deploy payload

    float triggerAlt_m = mpDBObject->detonationRange_m;

    float dz_m = mcKin.mfAlt_m - (terrainHeight_m + triggerAlt_m); // height above ground or sea level

    float vz_mps = C_KTSTOMPS * sinf(mcKin.mfClimbAngle_rad) * mcKin.mfSpeed_kts;

    float dt_impact = -dz_m / vz_mps;

    if (dt_impact > tminDet_s) return; // defer to future time step

    if (mpDBObject->payloadClass.size() == 0)
    {
        Detonate(dt_impact);
    }
    else
    {
        DeployPayload();
    }
}


void tcBallisticMissile::UpdateEffects()
{
	if (model)
	{
        if (mcKin.mfAlt_m > 0)
        {
		    model->SetSmokeMode(tc3DModel::MISSILE);
        }
        else
        {
            model->SetSmokeMode(tc3DModel::BUBBLES);
        }
		model->UpdateEffects();
	}
}



void tcBallisticMissile::UpdateFlight(float dt_s)
{
    if (dt_s <= 0) return;

    // determine stage
    float t1 = mpDBObject->timeStage1_s;
    float t2 = t1 + mpDBObject->timeStage2_s;
    float t3 = t2 + mpDBObject->timeStage3_s;
    float t4 = t3 + mpDBObject->timeStage4_s;

    int stage = int(flightTime_s < t1) * int(1) +
                int((flightTime_s >= t1) && (flightTime_s < t2)) * int(2) +
                int((flightTime_s >= t2) && (flightTime_s < t3)) * int(3) +
                int((flightTime_s >= t3) && (flightTime_s < t4)) * int(4) +
                int(flightTime_s >= t4) * int(5);
    wxASSERT((stage >= 1) && (stage <= 5));

    flightTime_s += dt_s;

    // calculate thrust acceleration based on flight time (stage #)
    float thrustAccel_mps2 = 0;
    float invBC = 0;
    switch (stage)
    {
    case 1:
        thrustAccel_mps2 = mpDBObject->accelStage1_mps2;
        invBC = mpDBObject->inv_bcStage1;
        break;
    case 2: 
        thrustAccel_mps2 = mpDBObject->accelStage2_mps2;
        invBC = mpDBObject->inv_bcStage2;
        break;
    case 3: 
        thrustAccel_mps2 = mpDBObject->accelStage3_mps2;
        invBC = mpDBObject->inv_bcStage3;
        break;
    case 4:
        thrustAccel_mps2 = mpDBObject->accelStage4_mps2;
        invBC = mpDBObject->inv_bcStage4;
        break;
    default: 
        thrustAccel_mps2 = 0;
        invBC = mpDBObject->inv_bcStage4;
        break;
    }


    // assume speed_mps and speed2_mps2 are valid

    if (thrustAccel_mps2 > 0)
    {
        // apply "steering" to adjust ECEF velocity vector orientation, limit by g limit        
        // might be better to just use a rotation instead of doing it this way
        float dvx = speed_mps*gx - vx;
        float dvy = speed_mps*gy - vy;
        float dvz = speed_mps*gz - vz;

        // remove component in direction of v to get the perpendicular component
        float a_proj = (dvx*vx + dvy*vy + dvz*vz) / speed2_mps2;
        dvx -= a_proj*vx;
        dvy -= a_proj*vy;
        dvz -= a_proj*vz;

        float dv = sqrtf(dvx*dvx + dvy*dvy + dvz*dvz);
        float max_dv = dt_s * C_G * mpDBObject->gmax;

        bool allowPerfectSteering = (flightTime_s > (thrustShutoffTime_s - 1.0f)); // cheat and allow perfect steering right before burnout
        if ((dv > max_dv) && (!allowPerfectSteering))
        {
            float a_limit = (max_dv / dv);
            dvx *= a_limit;
            dvy *= a_limit;
            dvz *= a_limit;
        }

        vx += dvx;
        vy += dvy;
        vz += dvz;
    }

    
    // calculate drag based on BC, altitude, and speed
    float rhov2 = Aero::GetAirDensity(mcKin.mfAlt_m) * speed2_mps2;
    float dragAccel_mps2 = (stage < 5) ? rhov2 * invBC : 0;
    
    thrustAccel_mps2 = (flightTime_s > thrustShutoffTime_s) ? 0 : thrustAccel_mps2;

    // update speed
    speed_mps += dt_s * (thrustAccel_mps2 - dragAccel_mps2);

    // adjust magnitude of (vx,vy,vz) to match updated speed from thrust/drag acceleration, also removes any small speed change from steering
    float a_rescale = speed_mps / sqrtf(vx*vx + vy*vy + vz*vz);
    vx *= a_rescale;
    vy *= a_rescale;
    vz *= a_rescale;

    // apply acceleration from gravity
    float a_grav = dt_s * C_GM / (r_ecef * r_ecef * r_ecef);
    vx -= a_grav * x;
    vy -= a_grav * y;
    vz -= a_grav * z;

    speed2_mps2 = vx*vx + vy*vy + vz*vz;
    speed_mps = sqrtf(speed2_mps2);
    
    // move unit
    x += dt_s * vx;
    y += dt_s * vy;
    z += dt_s * vz;

    r_ecef = sqrt(x*x + y*y + z*z);

    // update LLA
    CalculateLLA();


    // malfunction check
    if (!tcWeaponObject::malfunctionChecked && (stage >= 3))
    {
        MalfunctionCheck();
    }

}



/**
* Update goal heading and pitch controls
*/
void tcBallisticMissile::UpdateGuidance(double t) 
{
	if ((t - lastGuidanceUpdateTime) < guidanceUpdateInterval)
	{
		return;
	}
    lastGuidanceUpdateTime = t;

    float dx = float(xt - x);
    float dy = float(yt - y);
    float dz = float(zt - z);

    float ke = 0;
    float kn = 0;
    float ku = 0;
    Ecef2enu(mcKin.mfLat_rad, mcKin.mfLon_rad, dx, dy, dz, ke, kn, ku); // enu vector toward target datum

    // just keep east-north component and normalize to 1
    float ken_norm = sqrtf(ke*ke + kn*kn);
    float inv_ken_norm = 1.0f / ken_norm;
    ke *= inv_ken_norm;
    kn *= inv_ken_norm;
    ku = 0;

    if (flightTime_s < 30.0f)
    {
        ku = 0.98544973f; // about 80 deg climb
        ke *= 0.1700f;
        kn *= 0.1700f;

        Enu2ecef(mcKin.mfLat_rad, mcKin.mfLon_rad, ke, kn, ku, gx, gy, gz);
        return;
    }



    // project into 2D u-v plane
    double dst = sqrt((xt-x)*(xt-x)+ (yt-y)*(yt-y) + (zt-z)*(zt-z));

    double cos_gamma_rad = (r_ecef*r_ecef + rt*rt - dst*dst) / (2*r_ecef*rt);
    double sin_gamma_rad = sqrt(1 - cos_gamma_rad*cos_gamma_rad);
    float us = r_ecef;
    float vs = 0;
    float ut = rt * cos_gamma_rad;
    float vt = rt * sin_gamma_rad;
    
    float two_over_r = 2.0f / r_ecef; 
    float a_orbit = 1.0f / (two_over_r - (speed2_mps2 * C_GMINV)); // semi major axis of orbit ellipse

    float uf;
    float vf;
    CalculateSecondFocus(us, vs, ut, vt, a_orbit, uf, vf);
    
    float aa2 = us*us + vs*vs;
    float aa = sqrtf(aa2);  //sqrt((us - 0)^2 + (vs - 0)^2);
    float bb2 = (us-uf)*(us-uf) + (vs-vf)*(vs-vf);
    float bb = sqrtf(bb2); //sqrt((us - uf)^2 + (vs - vf)^2);
    float cc2 = uf*uf + vf*vf;

    // beta is climb angle in local LLA frame
    float acos_arg = (aa2 + bb2 - cc2) / (2*aa*bb);
    if ((acos_arg >= -1.0f) && (acos_arg <= 1.0f))
    {
        float beta_rad = 0.5f * acosf((aa2 + bb2 - cc2) / (2*aa*bb));
    
        float cos_beta = cosf(beta_rad);
        float sin_beta = sinf(beta_rad);

        ku = sin_beta;
        ke *= cos_beta;
        kn *= cos_beta;
    }
    else
    {
        ku = 0.707107f; // 45 deg climb
        ke *= 0.707107f;
        kn *= 0.707107f;
    }

    Enu2ecef(mcKin.mfLat_rad, mcKin.mfLon_rad, ke, kn, ku, gx, gy, gz);

    // shut off thrust early if have enough speed to comfortably reach target, should reduce flight time
    float a_orbit_min = 0.25*(dst + r_ecef +  rt);
    float min_speed_mps = sqrtf(C_GM * (two_over_r - (1.0f/a_orbit_min)));
    if (speed_mps > (min_speed_mps + 300.0f))
    {
        thrustShutoffTime_s = std::min(thrustShutoffTime_s, flightTime_s + 2.0f);
    }

}

/**
* Update ECEF parameters based on mcKin
*/
void tcBallisticMissile::CalculateECEF()
{
    const double Rearth_m = double(C_REARTHM);
    r_ecef = Rearth_m + double(mcKin.mfAlt_m);

    z = r_ecef * sin(mcKin.mfLat_rad);
    double R_cos_lat = r_ecef * cos(mcKin.mfLat_rad);
    x = R_cos_lat * cos(mcKin.mfLon_rad);
    y = R_cos_lat * sin(mcKin.mfLon_rad);

    speed_mps = C_KTSTOMPS * mcKin.mfSpeed_kts;
    speed2_mps2 = speed_mps * speed_mps;

    float vu = speed_mps * sinf(mcKin.mfClimbAngle_rad);
    float vh = speed_mps * cosf(mcKin.mfClimbAngle_rad);
    float ve = vh * sinf(mcKin.mfHeading_rad);
    float vn = vh * cosf(mcKin.mfHeading_rad);

    Enu2ecef(mcKin.mfLat_rad, mcKin.mfLon_rad, ve, vn, vu, vx, vy, vz);
}

/**
* Update mcKin based on ECEF parameters
*/
void tcBallisticMissile::CalculateLLA()
{
    const double Rearth_m = double(C_REARTHM);

    mcKin.mfLat_rad = asin(z / r_ecef);
    mcKin.mfLon_rad = atan2(y, x);
    mcKin.mfAlt_m = float(r_ecef - Rearth_m);


    mcKin.mfSpeed_kts = C_MPSTOKTS * speed_mps;

    float ve = 0;
    float vn = 0;
    float vu = 0;
    Ecef2enu(mcKin.mfLat_rad, mcKin.mfLon_rad, vx, vy, vz, ve, vn, vu);

    mcKin.mfHeading_rad = atan2(ve, vn);
    mcKin.mfClimbAngle_rad = asin(vu / speed_mps);
    mcKin.mfPitch_rad = mcKin.mfClimbAngle_rad;
}

/**
* Calculates second focus of ellipse (xf, yf) with one focus assumed at (0, 0) and given
* two points on the ellipse (xa, ya) and (xb, yb), and semimajor axis ae
*/
void tcBallisticMissile::CalculateSecondFocus(float xa, float ya, float xb, float yb, float ae, float& xf, float& yf)
{
    float da = sqrtf(xa*xa + ya*ya);
    float db = sqrtf(xb*xb + yb*yb);
    float d = sqrtf((xa-xb)*(xa-xb) + (ya-yb)*(ya-yb));
    float inv_d = 1.0f / d;

    float major_axis = 2.0f * ae;
    float ra = major_axis - da;
    float rb = major_axis - db;
    
    float ra2 = ra*ra;
    float rb2 = rb*rb;
    float d2 = d*d;

    float a = 0.5f * inv_d * (ra2 - rb2 + d2);
    float h = sqrtf(ra2 - a*a);

    float a_over_d = a * inv_d;
    float xm = xa + a_over_d * (xb - xa);
    float ym = ya + a_over_d * (yb - ya);

    float h_over_d = h * inv_d;
    
    xf = xm + h_over_d * (yb - ya);
    yf = ym - h_over_d * (xb - xa);
}


/**
*
*/
void tcBallisticMissile::Clear()  
{  
	tcGameObject::Clear();

	guidanceUpdateInterval = 1.0f; // 1 second default
	lastGuidanceUpdateTime = 0.0f;
}



void tcBallisticMissile::Enu2ecef(float lat_rad, float lon_rad, float ke, float kn, float ku, float& kx, float& ky, float& kz)
{
    float sin_lat = sinf(lat_rad);
    float cos_lat = cosf(lat_rad);
    float sin_lon = sinf(lon_rad);
    float cos_lon = cosf(lon_rad);

    kx = (-sin_lon*ke) + (-sin_lat*cos_lon*kn) + (cos_lat*cos_lon*ku);
    ky = (cos_lon*ke) + (-sin_lat*sin_lon*kn) + (cos_lat*sin_lon*ku);
    kz = (cos_lat*kn) + (sin_lat*ku);
}

void tcBallisticMissile::Ecef2enu(float lat_rad, float lon_rad, float kx, float ky, float kz, float& ke, float& kn, float& ku)
{
    float sin_lat = sinf(lat_rad);
    float cos_lat = cosf(lat_rad);
    float sin_lon = sinf(lon_rad);
    float cos_lon = cosf(lon_rad);

    ke = (-sin_lon*kx) + (cos_lon*ky);
    kn = (-sin_lat*cos_lon*kx) + (-sin_lat*sin_lon*ky) + (cos_lat*kz);
    ku = (cos_lat*cos_lon*kx) + (cos_lat*sin_lon*ky) + (sin_lat*kz);
}

const GeoPoint& tcBallisticMissile::GetTargetDatum() const
{
    return targetDatum;
}


/**
* @return g-limited turn rate in radians/s
*/
float tcBallisticMissile::GlimitedTurnRate() const
{
    const float C_NUM = 19.0691f; // = (9.81 m/s2) / (kts to mps constant)

    return (C_NUM * mpDBObject->gmax) / (mcKin.mfSpeed_kts + 0.1f);
}




/**
* Copy constructor.
*/
tcBallisticMissile::tcBallisticMissile(const tcBallisticMissile& obj) 
: tcWeaponObject(obj),
    mpDBObject(obj.mpDBObject),
    subSurfaceLaunch(obj.subSurfaceLaunch),
    lastGuidanceUpdateTime(obj.lastGuidanceUpdateTime),
    guidanceUpdateInterval(obj.guidanceUpdateInterval),
    flightTime_s(obj.flightTime_s),
    thrustShutoffTime_s(obj.thrustShutoffTime_s),
    targetDatum(obj.targetDatum),
    x(obj.x),
    y(obj.y),
    z(obj.z),
    vx(obj.vx),
    vy(obj.vy),
    vz(obj.vz),
    xt(obj.xt),
    yt(obj.yt),
    zt(obj.zt),
    rt(obj.rt),
    gx(obj.gx),
    gy(obj.gy),
    gz(obj.gz),
    speed_mps(obj.speed_mps),
    speed2_mps2(obj.speed2_mps2),
    r_ecef(obj.r_ecef)
{
	mnModelType = MTYPE_BALLISTICMISSILE;
}

/**
* Constructor that initializes using info from database entry.
*/
tcBallisticMissile::tcBallisticMissile(tcBallisticMissileDBObject *obj)
:   tcWeaponObject(obj),
	mpDBObject(obj),
    subSurfaceLaunch(false),
    lastGuidanceUpdateTime(0),
    guidanceUpdateInterval(0.5),
    flightTime_s(0),
    thrustShutoffTime_s(0),
    x(0),
    y(0),
    z(0),
    vx(0),
    vy(0),
    vz(0),
    xt(0),
    yt(0),
    zt(0),
    rt(0),
    gx(0),
    gy(0),
    gz(0),
    speed_mps(0),
    speed2_mps2(0),
    r_ecef(0)
{
	mnModelType = MTYPE_BALLISTICMISSILE;

    targetDatum.Set(0, 0, 0);
}


tcBallisticMissile::~tcBallisticMissile() 
{
}

