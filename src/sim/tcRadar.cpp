/**
**  @file tcRadar.cpp
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
#include "aerror.h"
#include "tcCommandQueue.h"
#include "nsNav.h"
#include "tcRadar.h"
#include "tcGameObject.h"

#include "tcAirfieldObject.h"
#include "tcAirObject.h"
#include "tcBallisticWeapon.h"
#include "tcGroundObject.h"
#include "tcMissileObject.h"
#include "tcSubObject.h"
#include "tcSubDBObject.h"
#include "tcSurfaceObject.h"
#include "tcAirCM.h"

#include "tcPlatformDBObject.h"
#include "tcMissileDBObject.h"
#include "tcCounterMeasureDBObject.h"
#include "tcSimState.h"
#include "tcGameObjIterator.h"
#include "tcSensorTrackIterator.h"
#include "common/tcObjStream.h"
#include "tcGameStream.h"
#include "tcAllianceInfo.h"
#include "tcEventManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// break up this file later


float tcRadar::lastTargetRCS_dBsm = -88.0f;
float tcRadar::last_snr_margin_dB = -88.0f;
float tcRadar::lastTargetElevation_rad = 1.72787596f;

/**
* Load state from stream
*/
tcUpdateStream& tcRadar::operator<<(tcUpdateStream& stream)
{
    tcSensorState::operator<<(stream);

	unsigned char fireControlTrackCount;
    stream >> fireControlTrackCount;
	fireControlTracks.clear();

	for (unsigned char n=0; n<fireControlTrackCount; n++)
	{
		long trackId;
		stream >> trackId;
		fireControlTracks.push_back(trackId);
	}

    //stream >> isSemiactive;

    return stream;
}

/**
* Save state to stream
*/
tcUpdateStream& tcRadar::operator>>(tcUpdateStream& stream)
{
    tcSensorState::operator>>(stream);

	wxASSERT(fireControlTracks.size() < 256);
	unsigned char fireControlTrackCount = (unsigned char)fireControlTracks.size();
    stream << fireControlTrackCount;

	for (unsigned char n=0; n<fireControlTrackCount; n++)
	{
		stream << fireControlTracks[n];
	}

    //stream << isSemiactive;

    return stream;
}

tcGameStream& tcRadar::operator<<(tcGameStream& stream)
{    
    tcSensorState::operator<<(stream);

	unsigned char fireControlTrackCount;
    stream >> fireControlTrackCount;
	fireControlTracks.clear();

	for (unsigned char n=0; n<fireControlTrackCount; n++)
	{
		long trackId;
		stream >> trackId;
		fireControlTracks.push_back(trackId);
	}

    stream >> isSemiactive;
	stream >> last_range_km;

	stream >> target_x_offset_m;
	stream >> target_z_offset_m;

    jamMap.clear();
    size_t nJam;
    stream >> nJam;

    for (size_t k=0; k<nJam; k++)
    {
        JamInfo ji;
        long id;

        stream >> id;
        stream >> ji.az_rad;
        stream >> ji.JNR_dB;

        jamMap[id] = ji;
    }

    stream >> jammingDegradation_dB;
    stream >> jamTime_s;
    stream >> isJammed;

    stream.ReadCheckValue(3785);

    return stream;
}

tcGameStream& tcRadar::operator>>(tcGameStream& stream)
{
    tcSensorState::operator>>(stream);

	wxASSERT(fireControlTracks.size() < 256);
	unsigned char fireControlTrackCount = (unsigned char)fireControlTracks.size();
    stream << fireControlTrackCount;

	for (unsigned char n=0; n<fireControlTrackCount; n++)
	{
		stream << fireControlTracks[n];
	}

    stream << isSemiactive;
	stream << last_range_km; ///< [km] target range from last call to CanDetectTarget

	stream << target_x_offset_m; ///< offset for seeker target point in model coords
	stream << target_z_offset_m; ///< may want to move params like this to a seeker derived class

    size_t nJam = jamMap.size();
    stream << nJam;
    std::map<long, JamInfo>::const_iterator iter = jamMap.begin();

    for (; iter != jamMap.end(); ++iter)
    {
        long id = iter->first;

        stream << id;
        stream << (float)iter->second.az_rad;
        stream << (float)iter->second.JNR_dB;
    }

    stream << jammingDegradation_dB;
    stream << jamTime_s;
    stream << isJammed;

    stream.WriteCheckValue(3785);

    return stream;
}

/**
*
*/
tcRadar& tcRadar::operator=(tcRadar& ss) 
{
    tcSensorState::operator =(ss);

    mpDBObj = ss.mpDBObj;
    return(*this);
}

/**
* This will not work correctly if there is more than one active jammer on the same platform
* that affects this radar. Need generalized key that includes sensor idx to do this correctly.
* @param JNR_dB mainbeam JNR, sidelobes are modeled for jammer out of az/el beam to target
*/
void tcRadar::AddOrUpdateJammer(long id, float JNR_dB, float az_rad, float el_rad)
{
    std::map<long, JamInfo>::iterator iter = jamMap.find(id);
    if (iter != jamMap.end())
    {
        // update
        iter->second.JNR_dB = JNR_dB;
        iter->second.az_rad = az_rad;
        iter->second.el_rad = el_rad;
    }
    else
    {
        JamInfo jamInfo;
        jamInfo.JNR_dB = JNR_dB;
        jamInfo.az_rad = az_rad;
        jamInfo.el_rad = el_rad;
        
        jamMap[id] = jamInfo;
#ifdef _DEBUG
        fprintf(stdout, "New jammer, %d jamming %d, az: %f, JNR_dB: %f\n", id, parent->mnID, az_rad, JNR_dB);
#endif
    }
}


float tcRadar::CalculateJammingDegradation()
{
    wxASSERT(false); // obsolete
    return 0;
#if 0
    if (jamMap.size() == 0) return 0;

    /* Iterate through jam map
    ** Find max jammer power in coverage (don't add powers for now)
    **
    ** Interference power is dropped 30 dB for jammers outside of sensor coverage. 
    ** Eventually upgrade this (or add realism option) to recalculate for each target based on separation between 
    ** jammer and target angle.
    */

    // calculate az coverage
    bool covers360 = false;
    float az1_rad = 0;
    float az2_rad = 0;
    if (mpDBObj->mfFieldOfView_deg >= 360.0f) 
    {
        covers360 = true;
    }
    else 
    {
        float lookAz_rad = parent->mcKin.mfHeading_rad + mountAz_rad;

        float fHalfFOV_rad = (0.5f*C_PIOVER180)*mpDBObj->mfFieldOfView_deg;
        az1_rad = lookAz_rad - fHalfFOV_rad;
        az2_rad = lookAz_rad + fHalfFOV_rad;
    }


    float maxPdens_dB = -999.0f;

    std::map<long, JamInfo>::iterator iter = jamMap.begin();
    for(;iter != jamMap.end(); ++iter)
    {
        float effectivePowerDensity = iter->second.powerDensity;

        if (covers360 || (AngleWithinRange(iter->second.az_rad, az1_rad, az2_rad) != 0))
        {   
        }
        else
        {
            effectivePowerDensity -= 30.0f; // 30 dB sidelobes
        }
        
        if (effectivePowerDensity > maxPdens_dB) maxPdens_dB = effectivePowerDensity;
    }

    float JtoN_dB = maxPdens_dB + jamConstant;
    
    // approximation of power add
    if (JtoN_dB < -6.0) return 0;
    else if (JtoN_dB < 6.0) return (3.0f + 0.5*JtoN_dB);
    else return JtoN_dB;
#endif
}

/**
* Calculates jamming degradation vs target at az_rad, el_rad accounting for az and el beamwidth
* @returns jamming degradation factor in dB, 0 dB is no degradation
*/
float tcRadar::CalculateJammingDegradation2(float az_rad, float el_rad)
{
    if (jamMap.size() == 0) return 0;

    /* Iterate through jam map
    ** Find max jammer power in coverage (don't add powers for now)
    **
    ** Interference power is dropped 30 dB for jammers outside of sensor coverage. 
    ** Eventually upgrade this (or add realism option) to recalculate for each target based on separation between 
    ** jammer and target angle.
    */

    // calculate az coverage
    bool covers360 = false;
    float az1_rad = 0;
    float az2_rad = 0;
    if (mpDBObj->mfFieldOfView_deg >= 360.0f) 
    {
        covers360 = true;
    }
    else 
    {
        float lookAz_rad = parent->mcKin.mfHeading_rad + mountAz_rad;

        float fHalfFOV_rad = (0.5f*C_PIOVER180)*mpDBObj->mfFieldOfView_deg;
        az1_rad = lookAz_rad - fHalfFOV_rad;
        az2_rad = lookAz_rad + fHalfFOV_rad;

        // assume that the target (not the jammer necessarily) is within the az/el coverage of the sensor
        wxASSERT(AngleWithinRange(az_rad, az1_rad, az2_rad) != 0);
    }


    // for each jammer, assume that radar beam is centered on target
    float jnr_sum = 0; // linear (not dB) value to accumulate sum

    std::map<long, JamInfo>::iterator iter = jamMap.begin();
    for(;iter != jamMap.end(); ++iter)
    {
        float effectiveJNR = iter->second.JNR_dB; // dB value

        float daz_rad = iter->second.az_rad - az_rad;
        daz_rad += C_TWOPI * (float(daz_rad < -C_PI) - float(daz_rad > C_PI));

        float daz_beamwidths = fabsf(C_180OVERPI * daz_rad) * mpDBObj->invAzBeamwidth_deg;
        
        if (daz_beamwidths > 2)
        {
            effectiveJNR += mpDBObj->effectiveSidelobes_dB; // effective SLL always negative
        }
        else if (daz_beamwidths > 1)
        {
            effectiveJNR += (daz_beamwidths - 1) * mpDBObj->effectiveSidelobes_dB;
        }
        else // check elevation offset if az within beam, avoid doubling jammer rejection from being out of both az and el beams
        {
            float del_rad = iter->second.el_rad - el_rad;
            float del_beamwidths = fabsf(C_180OVERPI * del_rad) * mpDBObj->invElBeamwidth_deg;

            if (del_beamwidths > 2) effectiveJNR += mpDBObj->effectiveSidelobes_dB;
            else if (del_beamwidths > 1) effectiveJNR += (del_beamwidths - 1) * mpDBObj->effectiveSidelobes_dB;
        }
       
        jnr_sum += powf(10.0f, 0.1f * effectiveJNR);
    }

    float noise_degradation_dB = 10.0f * log10f(1.0f + jnr_sum);
    
    return noise_degradation_dB;
}

/**
* For missile seekers call to check for switch
* to countermeasure target
*/
void tcRadar::CounterMeasureTest(double t)
{
    const unsigned int maxAttempts = 4; // don't test any more than this number of CMs

    lastCounterMeasureTime = t;

    tcGameObject* target = simState->GetObject(mcTrack.mnID);
    if (target == 0)
    {
        wxASSERT(false); // called with no target
        return;
    }

    if (tcAirCM* cm = dynamic_cast<tcAirCM*>(target))
    {
        // already tracking a CM, don't check for switch back right now
        return;
    }

    
    float targetRangeRate_mps = parent->mcKin.CalculateRangeRate(target->mcKin);
    float targetRange_km = parent->mcKin.RangeToKmAlt(target);

    float targetHeight_m = 0; // equivalent height of target for radar horizon
    float fTargetAz_rad = 0;
    // could probably find way to use rcs from parent routine
    float targetRCS_dBsm = CalculateTargetRCS_dBsm(target, fTargetAz_rad, targetHeight_m); 

    tcGeoRect region;
    region.Set(target->mcKin.mfLon_rad, target->mcKin.mfLon_rad, target->mcKin.mfLat_rad, target->mcKin.mfLat_rad);
    float dy_rad = C_MTORAD*500.0f;
    float dx_rad = dy_rad / cosf(target->mcKin.mfLat_rad);
    region.Expand(dx_rad, dy_rad);

    unsigned int attempts = 0;
    tcGameObjIterator iter(region);

    for (iter.First();iter.NotDone();iter.Next())
    {
        tcGameObject* obj = iter.Get();

        wxASSERT(obj != 0);
        tcCounterMeasureDBObject* cmData = dynamic_cast<tcCounterMeasureDBObject*>(obj->mpDBObject);

        bool isEligible = (cmData != 0) && (cmData->subType == "Chaff") &&
            (obj->mpDBObject->mnType == PTYPE_AIRCM);
        float range_km;

        if (isEligible && CanDetectTarget(obj, range_km))
        {
            float objRangeRate_mps = parent->mcKin.CalculateRangeRate(obj->mcKin);
            float objRange_km = parent->mcKin.RangeToKmAlt(obj->mcKin);
            float objRCS_dBsm = lastTargetRCS_dBsm;

            float rangeRateFactor = (objRangeRate_mps < (targetRangeRate_mps - 30.0f)) ? 0.5f : 1.0f;
            float rangeFactor = (fabsf(objRange_km - targetRange_km) > 0.25f) ? 0.5f : 1.0f;
            float rcsFactor = (objRCS_dBsm < (targetRCS_dBsm - 3)) ? 0.5f : 1.0f;
            
            float prob_success = mpDBObj->counterMeasureFactor * cmData->effectiveness * 
                rangeRateFactor * rangeFactor * rcsFactor;
            if (randf() < prob_success)
            {
                mcTrack.mnID = obj->mnID;
                UpdateTrack(obj, t);
                return;
            }
            else
            {
                if (++attempts >= maxAttempts) return;
            }
            
        }
    }
}

bool tcRadar::IsJammed() const
{
    return isJammed;
}

void tcRadar::RemoveAllJammers()
{
    jamMap.clear();
}

void tcRadar::RemoveJammer(long id)
{
    std::map<long, JamInfo>::iterator iter = jamMap.find(id);
    if (iter != jamMap.end())
    {
        jamMap.erase(iter);
    }
}

void tcRadar::UpdateJammingDegradation()
{
    float dt_s = mfLastScan - jamTime_s; // time since last jammer update
    if (dt_s > 30.0f) // periodically clear jam stats to allow new updates
    {
        jammingDegradation_dB = 0;
        isJammed = false;
        jamTime_s = mfLastScan;
    }

    wxASSERT(jammingDegradation_dB >= 0);
}

float tcRadar::CalculateTargetRCS_dBsm(const tcGameObject* target, float& targetAz_rad, float& targetHeight_m) const
{
    wxASSERT(target != 0);

    const tcKinematics *rdr_kin = &parent->mcKin;  // kinematic state of radar parent object
    const tcKinematics *tgt_kin = &target->mcKin;  // state of target object

    targetHeight_m = tgt_kin->mfAlt_m;

    if (const tcAirDetectionDBObject* detectionData = dynamic_cast<const tcAirDetectionDBObject*>(target->mpDBObject))
    {
        // calc target az from sensor platform and target aspect considering tgt heading
        targetAz_rad = nsNav::GCHeadingApprox_rad(rdr_kin->mfLat_rad, rdr_kin->mfLon_rad,
            tgt_kin->mfLat_rad, tgt_kin->mfLon_rad);

        float aspect_rad = targetAz_rad - tgt_kin->mfHeading_rad + C_PI;
        aspect_rad += (float(aspect_rad >= C_TWOPI))*(-C_TWOPI) + (float(aspect_rad < -C_TWOPI))*C_TWOPI;
        //if (aspect_rad >= C_TWOPI) aspect_rad -= C_TWOPI;

        float rcs_dBsm = detectionData->GetRCS_dBsm(C_180OVERPI*aspect_rad);
        targetHeight_m += detectionData->effectiveHeight_m;

        // adjust RCS for radarblind speed
        if (mpDBObj->blindSpeed_mps > 0)
        {
            // target radial speed (unsigned)
            float radial_mps = fabsf(C_KTSTOMPS*target->mcKin.mfSpeed_kts*cosf(aspect_rad));

            float radial_fraction = radial_mps * mpDBObj->invBlindSpeed_mps; // 1.0 if at blind speed

            // perhaps unnecessary optimization to avoid branches
            float underBlindSpeed = float(radial_fraction < 1.0f);
            float nearBlindSpeed = float((radial_fraction >= 1.0f) && (radial_fraction < 2.0f));

            // 24 dB penalty if < blindSpeed, 0 to 24 dB for 2*blindspeed to blindspeed
            float speedPenalty = 24.0f*(underBlindSpeed + nearBlindSpeed*(2.0f - radial_fraction));
            rcs_dBsm -= speedPenalty;
        }

        return rcs_dBsm;
    }
    else
    {
        return -999.0f;
    }

}

/**
* @return dB adjustment to RCS based on elevation angle to target and terrain type under target
*/
float tcRadar::CalculateClutterAdjustment_dB(const tcGameObject* target, float targetEl_rad) const
{
    wxASSERT(target != 0);

    if (targetEl_rad > ((0.5f*C_PIOVER180)*mpDBObj->elevationBeamwidth_deg))
    {
        return 0;
    }
    else
    {
        bool isOverWater = (target->mcTerrain.mfHeight_m <= 0); // else over land
        float adjustment_dB = isOverWater ? mpDBObj->lookdownWater_dB : mpDBObj->lookdownLand_dB;

        return adjustment_dB;
    }
}

/**
* @return true if target within elevation coverage of radar
*
* @param targetRange_km must be 3D range, otherwise get NaN for some low range geometries
* @param targetEl_rad elevation assuming platform is level
*/
bool tcRadar::TargetInElevationCoverage(const tcGameObject* target, float targetRange_km, float& targetEl_rad) const
{
    wxASSERT((target != 0)&&(parent != 0));

    if (const tcWeaponObject* weapon = dynamic_cast<const tcWeaponObject*>(parent))
    {
        return TargetInElevationCoverageWeapon(target, targetRange_km, targetEl_rad);
    }

    float dalt_m = target->mcKin.mfAlt_m - parent->mcKin.mfAlt_m;

    wxASSERT(fabsf(dalt_m) <= (1000.0f*targetRange_km));

    targetEl_rad = asinf(dalt_m / (1000.0f*targetRange_km));

    lastTargetElevation_rad = targetEl_rad;

    bool inCoverage = (targetEl_rad >= mpDBObj->minElevation_rad) && (targetEl_rad <= mpDBObj->maxElevation_rad);

    return inCoverage;
}

/**
* @return true if target within elevation coverage of radar
* This version uses cone angle between platform boresight (assumes forward-looking radar) and target
*
* @param targetRange_km must be 3D range, otherwise get NaN for some low range geometries
* @param targetEl_rad cone angle from parent boresight to target
*/
bool tcRadar::TargetInElevationCoverageWeapon(const tcGameObject* target, float targetRange_km, float& targetEl_rad) const
{
    wxASSERT((target != 0)&&(parent != 0));

    float cos_pitch_parent = cosf(parent->mcKin.mfPitch_rad);
    float zplatform = sinf(parent->mcKin.mfPitch_rad);
    float xplatform = cos_pitch_parent * cosf(parent->mcKin.mfHeading_rad);
    float yplatform = cos_pitch_parent * sinf(parent->mcKin.mfHeading_rad);

    float bearing_rad = parent->BearingToRad(*target);
    float dalt_m = target->mcKin.mfAlt_m - parent->mcKin.mfAlt_m;
    wxASSERT(fabsf(dalt_m) <= (1000.0f*targetRange_km));
    float sin_el_target = dalt_m / (1000.0f*targetRange_km);
    float cos_el_target = sqrtf(1.0 - sin_el_target*sin_el_target);

    float ztarget = sin_el_target;
    float xtarget = cos_el_target * cosf(bearing_rad);
    float ytarget = cos_el_target * sinf(bearing_rad);
    
    float cos_cone = xplatform*xtarget + yplatform*ytarget + zplatform*ztarget;
    targetEl_rad = acosf(cos_cone);

    bool inCoverage = (targetEl_rad <= mpDBObj->maxElevation_rad);

    return inCoverage;
}


/**
*
*/
bool tcRadar::CanDetectTarget(const tcGameObject* target, float& range_km, bool useRandom)
{

    float fTargetRange_km;
    float fCoverageAz1, fCoverageAz2;
    bool bInSearchVolume = false;
    last_snr_margin_dB = -99.0f;
    lastTargetElevation_rad = 1.72787596f; // 99 deg

    wxASSERT((mpDBObj != 0) && (target != 0));

    if (!mbActive && !isCommandReceiver) return false;

    float illuminatorTargetRange_km = 1e8;
    if (isSemiactive || isCommandReceiver)
    {
        tcRadar* illum = GetFireControlRadar();
        if (illum == NULL) return false;
        if (!illum->CanDetectTarget(target, illuminatorTargetRange_km, false)) return false; // assume illuminator receiver is missile, so no random detection
        if (isCommandReceiver) return true; 
    }

    lastTargetRCS_dBsm = -999.0f;

    const tcKinematics *rdr_kin = &parent->mcKin;  // kinematic state of radar parent object
    const tcKinematics *tgt_kin = &target->mcKin;  // state of target object

    float targetHeight_m = 0; // equivalent height of target for radar horizon
    float fTargetAz_rad = 0;

    float rcs_dBsm = CalculateTargetRCS_dBsm(target, fTargetAz_rad, targetHeight_m);

    if ((targetHeight_m < 0) || (rcs_dBsm < -100.0f))
    {
        return false; // submerged sub || not detectable by radar
    }

    lastTargetRCS_dBsm = rcs_dBsm;

    //#define PTYPE_UNKNOWN 0x0000
    //#define PTYPE_SURFACE 0x0010
    //#define PTYPE_SMALLSURFACE 0x0011
    //#define PTYPE_LARGESURFACE 0x0012
    //#define PTYPE_CARRIER 0x0014
    //#define PTYPE_AIR 0x0020
    //#define PTYPE_FIXEDWING 0x0021
    //#define PTYPE_HELO 0x0022
    //#define PTYPE_MISSILE 0x0040
    //#define PTYPE_SUBSURFACE 0x0080
    //#define PTYPE_SUBMARINE 0x0081
    //#define PTYPE_TORPEDO 0x0082
    //#define PTYPE_SONOBUOY 0x0084
    //#define PTYPE_GROUND 0x0100
    //#define PTYPE_AIRFIELD 0x0101
    //#define PTYPE_BALLISTIC 0x0200

    unsigned int classification = target->mpDBObject->mnType;

    bool isSurface = ((classification & PTYPE_SURFACE) != 0) || (classification == PTYPE_AIRCM);
    bool isAir = (classification & PTYPE_AIR) != 0;
	bool isMissile = (classification & PTYPE_MISSILE) != 0;
	bool isGround = (classification & PTYPE_GROUND) != 0;
    bool isSub = (classification & PTYPE_SUBSURFACE) != 0;

    if (isMissile && (target->mcKin.mfSpeed_kts < 600.0f))
    {
        isAir = true; // consider missile an air target if moving under about Mach 1
    }

    if (isSub) isSurface = true; // treat surfaced sub as surface

    if (mpDBObj->mfFieldOfView_deg >= 360.0f) 
    {
        bInSearchVolume = true;
    }
    else 
    {
        float lookAz_rad = parent->mcKin.mfHeading_rad + mountAz_rad;
        float fHalfFOV_rad = 0.5f*C_PIOVER180*mpDBObj->mfFieldOfView_deg;
        fCoverageAz1 = lookAz_rad - fHalfFOV_rad;
        fCoverageAz2 = lookAz_rad + fHalfFOV_rad;
        bInSearchVolume = AngleWithinRange(fTargetAz_rad,fCoverageAz1,fCoverageAz2) != 0;
        if (!bInSearchVolume) {range_km=0;return false;}
    }

    float clutterHorizon_km = C_RADARHOR * sqrtf(rdr_kin->mfAlt_m + mfSensorHeight_m); // break up radar horizon for clutter degradation calc later
    float fRadarHorizon = C_RADARHOR*sqrtf(targetHeight_m) + clutterHorizon_km;

    fTargetRange_km = C_RADTOKM*nsNav::GCDistanceApprox_rad(rdr_kin->mfLat_rad, rdr_kin->mfLon_rad,
		tgt_kin->mfLat_rad,tgt_kin->mfLon_rad, rdr_kin->mfAlt_m, tgt_kin->mfAlt_m);
    range_km = fTargetRange_km;
	last_range_km = range_km;

    if (fTargetRange_km > fRadarHorizon) 
    {
        return false;
    }

    float targetEl_rad = 0;
    bool inElevationCoverage = TargetInElevationCoverage(target, fTargetRange_km, targetEl_rad);

    if (!inElevationCoverage || !HasLOS(target)) return false;

    // adjustment for "look-down" geometry, can also apply to targets near horizon for surface based radars
    if (fTargetRange_km <= clutterHorizon_km)
    {
        float clutterAdjustment_dB = CalculateClutterAdjustment_dB(target, targetEl_rad);
        rcs_dBsm += clutterAdjustment_dB;
        lastTargetRCS_dBsm = rcs_dBsm;
    }

    bool bTargetTypeMatch = (mpDBObj->mbDetectsAir && isAir) ||
		(mpDBObj->mbDetectsMissile && isMissile) ||
        (mpDBObj->mbDetectsSurface && isSurface) ||
		(mpDBObj->mbDetectsGround && isGround);

	if (bTargetTypeMatch == false) return false;

	float margin_dB; // SNR margin

    if (isSemiactive)
    {
		margin_dB = 
            20.0f*(2.0f*log10f(mpDBObj->mfRefRange_km) 
            - log10f(fTargetRange_km)
            - log10f(illuminatorTargetRange_km)
            ) + rcs_dBsm ;
    }
    else
    {
		margin_dB = 
            40.0f*(log10f(mpDBObj->mfRefRange_km) - log10f(fTargetRange_km)) + rcs_dBsm;
    }

    float targetJammingDegradation_dB = 
            CalculateJammingDegradation2(fTargetAz_rad, targetEl_rad);
    if (targetJammingDegradation_dB >= jammingDegradation_dB)
    {
        jammingDegradation_dB = targetJammingDegradation_dB;
        isJammed = (jammingDegradation_dB > 0);
        jamTime_s = target->mfStatusTime; // not sure if tcSensorState::mfLastScan is updated at this point so use target time
    }

    margin_dB = margin_dB - targetJammingDegradation_dB;
    last_snr_margin_dB = margin_dB;

    // don't do random detections for missiles (problem where launched with lock that disappears in transition region)
    if (((mnMode == SSMODE_SURVEILLANCE) || (mnMode == SSMODE_SEEKERSEARCH)) && useRandom)
    {
        return RandomDetect(margin_dB);
    }
    else
    {
        return margin_dB >= 0;
    }
}


/**
* @return false if key not found in database
*/
bool tcRadar::InitFromDatabase(long key)
{
	wxASSERT(database);

    tcSensorState::InitFromDatabase(key);

	tcDatabaseObject* databaseObj = database->GetObject(key);
	if (databaseObj == 0)
	{
        fprintf(stderr, "Error - tcRadar::InitFromDatabase - Not found in db\n");
        return false;
	}

    mpDBObj = dynamic_cast<tcRadarDBObject*>(databaseObj);
    if (mpDBObj == 0) 
    {
        fprintf(stderr, "Error - tcRadar::InitFromDatabase - Not a radar database class (%s)\n",
			databaseObj->mzClass.c_str());
        return false;
    }

    if (mpDBObj->isSurveillance)
    {
        mnMode = SSMODE_SURVEILLANCE;
    }
    else
    {
        mnMode = SSMODE_FC;
    }
    mfSensorHeight_m = 10.0f;

    isSemiactive = mpDBObj->isSemiactive;

    return true;
}

/**
*
*/
void tcRadar::Serialize(tcFile& file, bool mbLoad) 
{
    tcSensorState::Serialize(file, mbLoad);
}


/**
* Sets illuminator info for semi-active radars and command receivers.
* isCommandReceiver indicates the "radar" is a simple receiver of command
* guidance from the fire control radar.
*/
void tcRadar::SetFireControlSensor(long id, unsigned char idx)
{
    wxASSERT((id == -1) || isSemiactive || isCommandReceiver);

	tcSensorState::SetFireControlSensor(id, idx);
}


/**
*
*/
tcRadar* tcRadar::Clone(void) 
{
    tcRadar *pNew = new tcRadar();
    *pNew = *this;
    return pNew;
}


unsigned tcRadar::GetFireControlTrackCount() const
{
	return (unsigned)fireControlTracks.size();
}

unsigned tcRadar::GetMaxFireControlTracks() const
{
	return mpDBObj->maxFireControlTracks;
}

/**
* Alternative to dynamic_cast
*/
bool tcRadar::IsRadar() const
{
    return true;
}

/**
* Does not test if radar can detect target.
* @return true if track is available.
*/
bool tcRadar::IsTrackAvailable()
{
    return (GetFireControlTrackCount() < mpDBObj->maxFireControlTracks);
}

/**
* if track is available, reserve a track.
* The current approach to semi-active guidance is to require each 
* missile to request one track per target, even if it is the same 
* target as a pre-existing track.
* Calling method must check if target is detectable for this to
* work properly.
*/
bool tcRadar::RequestTrack(long targetId)
{
	if (!IsTrackAvailable())
	{
		return false;
	}

	fireControlTracks.push_back(targetId);

	if ((parent != 0) && (!parent->IsClientMode()))
	{
        tcSimState* simState = tcSimState::Get();

        if (tcGameObject* newTargetObj = simState->GetObject(targetId))
        {
            newTargetObj->AddTargeter(parent->mnID);
        }
    }

	return true;
}

bool tcRadar::ReleaseTrack(long targetId)
{
	std::vector<long> updatedTracks;
	for (size_t n=0; n<fireControlTracks.size(); n++)
	{
		if (fireControlTracks[n] != targetId)
		{
			updatedTracks.push_back(fireControlTracks[n]);
		}
	}

	if (updatedTracks.size() == fireControlTracks.size())
	{
		fprintf(stderr, "tcRadar::ReleaseTrack targetId not found (%d)", targetId);
		return false;
	}

	fireControlTracks = updatedTracks;

	if ((parent != 0) && (parent->IsClientMode())) return true;

	// after releasing track, check if any other radars on parent platform have active fire control track. If not, remove parent from targeter list
	wxASSERT((parent != 0) && (sensorPlatform != 0));

	bool isTrackingTarget = false;
	unsigned int nParentSensors = sensorPlatform->GetSensorCount();
	for (unsigned int n=0; n<nParentSensors; n++)
	{
		const tcSensorState* sensor = sensorPlatform->GetSensor(n);
		isTrackingTarget = isTrackingTarget || sensor->IsTrackingWithRadar(targetId);
	}

	if (!isTrackingTarget)
	{
		tcGameObject* target = simState->GetObject(targetId);
		if (target != 0)
		{
			target->RemoveTargeter(parent->mnID);
		}
	}

	return true;

}

/**
* @return true if this radar has any active fire control tracks on targetId
*/
bool tcRadar::IsTrackingWithRadar(long targetId) const
{
	size_t nFireControlTracks = fireControlTracks.size();
	for (size_t n=0; n<nFireControlTracks; n++)
	{
		if (fireControlTracks[n] == targetId) return true;
	}

	return false;
}

/**
* Updates missile seeker radar.
*/
void tcRadar::UpdateSeeker(double t)
{
    long nTargetID;
    tcGameObject *ptarget = 0;
    bool bFound = false;
    bool isEligible = false;
    tcMissileObject* missile = dynamic_cast<tcMissileObject*>(parent);

    switch (mnMode) 
    {
    case SSMODE_SEEKERACQUIRE:        // fall through to SEEKERTRACK
        if (missile != 0) missile->SetSeekerTarget(mcTrack.mnID);

    case SSMODE_SEEKERTRACK:
        nTargetID = mcTrack.mnID;
        if (nTargetID != parent->mnID)
        { 
            bFound = simState->maPlatformState.Lookup(nTargetID,ptarget);
        } 
        else // no self detection
        {
            bFound = false;
        }

        if ((missile != 0) && bFound && (missile->mfInterceptTime < 5.0f) && 
            (lastCounterMeasureTime < (t - 1.0)))
        {
            CounterMeasureTest(t);
        }

        if (bFound) 
        {  // own-alliance is allowed
            float fRange_km;

            bool surfacedSub = (ptarget->mpDBObject->mnType == PTYPE_SUBMARINE) && 
                (ptarget->mcKin.mfAlt_m > -2.0f);

            isEligible = surfacedSub || 
                ((ptarget->mpDBObject->mnType & 
                (PTYPE_AIR | PTYPE_GROUND | PTYPE_MISSILE | PTYPE_SURFACE)) != 0);

            if (isEligible && CanDetectTarget(ptarget, fRange_km)) 
            {
                UpdateTrack(ptarget, t);
                return;
            }
            else
            {
#ifdef _DEBUG
                bool result = CanDetectTarget(ptarget, fRange_km);
#endif
            }
        }

		// shut down missile if target doesn't exist or can't detect
		/*{
            parent->SelfDestruct();
            mcTrack.mnID = -1;
#ifdef _DEBUG
            if(simState->mpUserInfo->IsOwnAlliance(parent->GetAlliance())) 
            {
                char zBuff[128];
				_snprintf(zBuff, 128, "Mis %d shut down (%s)\n", parent->mnID, parent->mzClass.c_str());
                simState->mpCommandInterface->DisplayInfoMessage(zBuff);
            }
#endif
            return;
		}*/


        if (missile != 0)
        {
            /* if range to target is close enough, assume this is a terminal missile
            ** and ignore failed detection */
            const float terminalRange_km = 0.5f;
            bool cheatUpdate = (ptarget != 0) && ((missile->RangeTo(*ptarget) < terminalRange_km) || (missile->msKState.mfFlightTime < 3.0f)); 

            if ((ptarget != 0) && isEligible && cheatUpdate)
            {
                UpdateTrack(ptarget, t);
                return;
            }

            mcTrack.mnID = -1;
            missile->goalHeading_rad = missile->mcKin.mfHeading_rad;
            missile->goalPitch_rad = missile->mcKin.mfPitch_rad;

            bool hasSegments = (missile->mpDBObject->mnNumSegments > 0);
            bool datumLaunched = hasSegments && (missile->mpDBObject->maFlightProfile[0].meGuidanceMode == GM_NAV);

            if (datumLaunched)
            {
                mnMode = SSMODE_SEEKERSEARCH; 
            }
            else
            {
                parent->SelfDestruct();
            }
        }
        else
        {
            parent->SelfDestruct();
        }
        


        // shut down missile if track lost for > 7 seconds
        //if ((mnMode == SSMODE_SEEKERTRACK)&&
        //    (t - mcTrack.mfTimestamp) > 7.0)
        //{
        //    parent->mfDamageLevel = 1.0f; 
        //    mcTrack.mnID = NULL_INDEX;
        //    if(simState->mpUserInfo->IsOwnAlliance(parent->GetAlliance())) 
        //    {
        //        char zBuff[128];
        //        sprintf(zBuff,"Missile %d shut down\n", parent->mnID);
        //        simState->mpCommandInterface->DisplayInfoMessage(zBuff);
        //    }
        //    return;
        //}

        // this code to enter search mode after track lost

        break;
    case SSMODE_SEEKERSEARCH:
        {
            // get list of candidate tracks/detections
            tcGeoRect region;   
            GetTestArea(region);

            tcGameObjIterator iter(region);
            float minRange = 1e15f;
            float maxRCS = -12345.0f;
            long minID = NULL_INDEX;

            // find closest detectable target
            for (iter.First();iter.NotDone();iter.Next())
            {
                tcGameObject *target = iter.Get();
                if (target != parent) // no self detection
                {
                    float range_km = 0;
                    /* Substitute this to disable own-alliance seeker detections:
                    ** bool bDetected = (parent->GetAlliance() != target->GetAlliance()) &&
                    **    CanDetectTarget(target,range_km);
                    */
                    bool bDetected = CanDetectTarget(target, range_km);
                    float rcs_dBsm = lastTargetRCS_dBsm;

                    bDetected = bDetected && (range_km > 1.0f); // don't allow lock inside 1.0 km range

                    bool targetPreferred = (range_km < minRange) ||
                        ((range_km < minRange + 1.0f) && (rcs_dBsm > maxRCS));

                    if (bDetected && targetPreferred)
                    {
                        minID = target->mnID;
                        minRange = range_km;
                        maxRCS = rcs_dBsm;
                    }
                }
            }
           
            if (minID==NULL_INDEX) return; // no targets found

            // if seeker has locked on a countermeasure, roll against the effectiveness * cm_factor to start a track
            if (tcAirCM* airCM = dynamic_cast<tcAirCM*>(simState->GetObject(minID)))
            {
                float prob_success = mpDBObj->counterMeasureFactor * airCM->mpDBObject->effectiveness;
                if (randf() > prob_success)
                {
                    return; // CM rejected
                }
            }

            parent->DesignateTarget(minID); // select closest as target
        }
    }
}

/**
* Called after a surveillance detection to update sensor map for
* appropriate alliance.
*/
void tcRadar::UpdateSensorMap(double t, const tcGameObject* target, float range_km)
{
    tcSensorMapTrack* pSMTrack = 0;
    tcSensorReport* report = simState->mcSensorMap.GetOrCreateReport(parent->mnID, mpDBObj->mnKey, target->mnID,
        pSMTrack, parent->GetAlliance());

    if (report == 0) return;

    float az_rad = parent->mcKin.HeadingToRad(target->mcKin);

    tcSensorState::UpdateActiveReport(report, t, az_rad, range_km, target->mcKin.mfAlt_m, pSMTrack);


    double trackLife = report->timeStamp - report->startTime;
    if (trackLife >= 16.0) 
    {
        report->speedEstimate_mps = C_KTSTOMPS * target->mcKin.mfSpeed_kts * cosf(target->mcKin.mfClimbAngle_rad);
        report->speedVariance = 1.0f;
        report->headingEstimate_rad = target->mcKin.mfHeading_rad;
        report->headingVariance = 0.001f;
        report->validFlags |= tcSensorReport::SPEED_VALID | tcSensorReport::HEADING_VALID;

        if (last_snr_margin_dB >= mpDBObj->idThreshold_dB)
        {
            report->alliance = target->GetAlliance();
            report->databaseID = target->mnDBKey;
        }
    }


    if (trackLife > 10.0)
    {
        unsigned int classification = target->mpDBObject->mnType;

        // surfaced sub classified as small surface
        if (classification == PTYPE_SUBMARINE)
        {
            classification = PTYPE_SMALLSURFACE; 
        }
        else if (classification == PTYPE_CARRIER)
        {
            classification = PTYPE_LARGESURFACE;
        }

        report->classification = classification;

        if ((classification & PTYPE_MISSILE) != 0) 
        {
            report->alliance = target->GetAlliance();
        }
    }
    else
    {
        report->classification = 0;
        report->alliance = 0;
    }

    bool bNewDetection = pSMTrack->IsNew();
    if (bNewDetection) 
    {
        pSMTrack->UpdateTrack(0);
        
        tcEventManager::Get()->NewContact(parent->GetAlliance(), pSMTrack);

        if (simState->mpUserInfo->IsOwnAlliance(parent->GetAlliance())) 
        {
            tcSound::Get()->PlayEffect("Ping");
        }

        //fprintf(stdout, "target %d detected at %3.1f km at time %.1f [a:%d]\n",
        //    target->mnID,range_km,t,parent->GetAlliance());

    }

}

void tcRadar::UpdateSurveillance(double t)
{
    tcGeoRect region;
    GetTestArea(region);

    tcGameObjIterator iter(region);

    for (iter.First();iter.NotDone();iter.Next())
    {
        tcGameObject *target = iter.Get();
        if (target != parent) // no self detection
        {
            float range_km = 0;

            bool surfacedSub = (target->mpDBObject->mnType == PTYPE_SUBMARINE) && 
                (target->mcKin.mfAlt_m > -2.0f);

            bool isEligible = surfacedSub || 
                ((target->mpDBObject->mnType & 
                (PTYPE_AIR | PTYPE_GROUND | PTYPE_MISSILE | PTYPE_SURFACE)) != 0);
          
            bool bDetected = (parent->GetAlliance() != target->GetAlliance()) &&
                isEligible &&
                CanDetectTarget(target,range_km);
            if (bDetected) UpdateSensorMap(t, target, range_km);

        }
    }
}


/**
* Loops through existing sensor map tracks and updates those in range with track data from this sensor
* Used to model cued track_only type sensors that do not provide initial detection
*/
void tcRadar::UpdateTrackData(double t)
{
    tcGeoRect region;
    GetTestArea(region);

    unsigned int classificationMask = 0;
    if (mpDBObj->mbDetectsAir) classificationMask |= PTYPE_AIR;
    if (mpDBObj->mbDetectsMissile) classificationMask |= PTYPE_MISSILE;
    if (mpDBObj->mbDetectsGround) classificationMask |= PTYPE_GROUND;
    if (mpDBObj->mbDetectsSurface) classificationMask |= (PTYPE_SURFACE | PTYPE_SUBSURFACE); // sub might be surfaced so add to mask

    tcSensorTrackIterator iter(parent->GetAlliance(), classificationMask, region);

    for (iter.First();iter.NotDone();iter.Next())
    {
        tcSensorMapTrack* track = iter.Get();
        wxASSERT(track != 0);

        bool isActiveTrack = (track != 0) && (track->errorPoly.size() == 0) && ((track->mnFlags & TRACK_ACTIVE) != 0);

        // only check tracks that are tracked with active sensor
        if (isActiveTrack)
        {
            tcGameObject* target = track->GetAssociated();

            float range_km = 0;
            bool isDetected = CanDetectTarget(target, range_km);
            if (isDetected && (target != 0))
            {
                UpdateSensorMapTrackMode(target, track, t, range_km);
            }
        }
    }
}

void tcRadar::UpdateSensorMapTrackMode(const tcGameObject* target, tcSensorMapTrack* track, double t, float range_km)
{
    wxASSERT(target->mnID == track->mnID);

    if (track->mnFlags)
    if (mpDBObj->angleError_deg < 5.0f)
    {
        track->mfLat_rad = (float)target->mcKin.mfLat_rad;
        track->mfLon_rad = (float)target->mcKin.mfLon_rad;
        track->mfSpeed_kts = target->mcKin.mfSpeed_kts * cosf(target->mcKin.mfClimbAngle_rad);
        track->mfHeading_rad = target->mcKin.mfHeading_rad;
        track->mfTimestamp = t;
    }

    float altitudeEstimate_m;
    float altitudeVariance;
    float az_rad = parent->mcKin.HeadingToRad(target->mcKin);
    if (GetAltitudeEstimate(altitudeEstimate_m, altitudeVariance, range_km, az_rad, target->mcKin.mfAlt_m))
    {
        track->mfAlt_m = altitudeEstimate_m;
    }
}


/**
* Update sensor track with target state. Normally used with
* missile seekers.
*/
void tcRadar::UpdateTrack(const tcGameObject* target, double t)
{

    mcTrack.mfLat_rad = (float)target->mcKin.mfLat_rad;
    mcTrack.mfLon_rad = (float)target->mcKin.mfLon_rad;
    mcTrack.mfAlt_m = target->mcKin.mfAlt_m;
    mcTrack.mfSpeed_kts = target->mcKin.mfSpeed_kts;
    mcTrack.mfHeading_rad = target->mcKin.mfHeading_rad;
    mcTrack.mfClimbAngle_rad = target->mcKin.mfClimbAngle_rad;
    mcTrack.mfTimestamp = t;
    mcTrack.mnFlags = (TRACK_HEADING_VALID | TRACK_SPEED_VALID 
        | TRACK_ALT_VALID | TRACK_CLIMB_VALID);
    if ((mnMode == SSMODE_SEEKERACQUIRE)  && !isCommandReceiver)
    {
        mnMode = SSMODE_SEEKERTRACK;
//#ifdef _DEBUG
//        if (simState->mpUserInfo->IsOwnAlliance(parent->GetAlliance())) 
//        {
//            tcSound::Get()->PlayEffect("TwoBeeps");
//        }
//#endif
    }

	AdjustTrackForFineTargeting(target);
}

/**
* If sufficiently close to target, adjust track to lock on to random feature
* of target. Intended to add more realism so that weapons do not always strike 
* origin of target model.
*/
void tcRadar::AdjustTrackForFineTargeting(const tcGameObject* target)
{
	if (last_range_km > 1.0f) return;

	/* if target offset has not been selected yet, randomly select
	** based on box around target model. This assumes that only one
	** target will be engaged throughout life of seeker */
	if ((target_x_offset_m == 0) && (target_z_offset_m == 0))
	{
        tcGameObject* targetMutable = const_cast<tcGameObject*>(target); // TV3D making me do this
        Vec3 finePos = targetMutable->GetRandomExteriorPoint();

		target_x_offset_m = finePos.x;
        target_z_offset_m = finePos.z;
	}
	Vec3 worldOffset = 
		target->ConvertModelCoordinatesToWorld(Vec3(target_x_offset_m, 0, target_z_offset_m));

	float lon_corr = C_MTORAD / cosf(mcTrack.mfLat_rad);
	mcTrack.mfAlt_m += worldOffset.y;
	if (mcTrack.mfAlt_m < 1) mcTrack.mfAlt_m = 1;
	mcTrack.mfLat_rad += C_MTORAD * worldOffset.z;
    mcTrack.mfLon_rad += lon_corr * worldOffset.x;
}


void tcRadar::Update(double t)
{    
	wxASSERT(sensorPlatform);
	if (mbActive != 0)
	{
		sensorPlatform->SetActivityFlag(tcSensorPlatform::RADAR_ACTIVE);
	}

    if (!UpdateScan(t)) return; // only update once per scan period

    UpdateJammingDegradation();

    if (mnMode == SSMODE_SURVEILLANCE)
    {
        UpdateSurveillance(t);
    }
    else if ((mnMode == SSMODE_SEEKERTRACK)||(mnMode == SSMODE_SEEKERSEARCH)
        ||(mnMode == SSMODE_SEEKERACQUIRE))
    {
        UpdateSeeker(t);
    }

}

/**
*
*/
tcRadar::tcRadar() 
:   tcSensorState(),
    mpDBObj(0)
{
}

tcRadar::tcRadar(tcRadarDBObject* dbObj)
:   tcSensorState(dbObj),
    mpDBObj(dbObj),
    isSemiactive(mpDBObj->isSemiactive),
	last_range_km(0),
	target_x_offset_m(0),
	target_z_offset_m(0),
    isJammed(false),
    jammingDegradation_dB(0)
{
	wxASSERT(dbObj);

    if (dbObj->isSurveillance)
    {
        mnMode = SSMODE_SURVEILLANCE;
    }
    else
    {
        mnMode = SSMODE_FC; // do not do surveillance updates
    }

    mfSensorHeight_m = 10.0f;
}

/**
*
*/
tcRadar::~tcRadar() 
{

}