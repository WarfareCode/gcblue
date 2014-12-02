/**
**  @file tcOpticalSensor.cpp
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
#include "tcOpticalSensor.h"
#include "tcGameObject.h"
#include "tcSurfaceObject.h"
#include "tcAeroAirObject.h"
#include "tcAirObject.h"
#include "tcMissileObject.h"
#include "tcAirfieldObject.h"
#include "tcBallisticWeapon.h"
#include "tcAirCM.h"
#include "ai/Brain.h"

#include "tcPlatformDBObject.h"
#include "tcMissileDBObject.h"
#include "tcCounterMeasureDBObject.h"
#include "tcSimState.h"
#include "tcGameObjIterator.h"
#include "common/tcObjStream.h"
#include "tcEventManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

float tcOpticalSensor::lastTargetSignature_dB = -99.0f;
float tcOpticalSensor::last_az_rad = -77.0f;

// break up this file later

/**
* Load state from stream
*/
tcUpdateStream& tcOpticalSensor::operator<<(tcUpdateStream& stream)
{
    tcSensorState::operator<<(stream);

    return stream;
}

/**
* Save state to stream
*/
tcUpdateStream& tcOpticalSensor::operator>>(tcUpdateStream& stream)
{
    tcSensorState::operator>>(stream);

    return stream;
}

float tcOpticalSensor::CalculateNightPenalty(const tcGameObject* target) const
{
    static tcDateTime dt;

    simState->GetDateTime(dt);


    float localHours = float(dt.GetHour()) + C_RADTOHRS * target->mcKin.mfLon_rad;
    if (localHours >= 24.0) localHours -= 24.0;
    else if (localHours < 0) localHours += 24.0;

    if ((localHours < 6) || (localHours > 18))
    {
        return mpDBObj->nightFactor;
    }
    else
    {
        return 1.0f;
    }
}

/**
* @returns either IR signature [dB] or EO signature [dBsm] depending on sensor
*/
float tcOpticalSensor::CalculateTargetSignature(const tcGameObject* target, float& targetAz_rad, float& targetAlt_m) const
{
    const tcKinematics *parent_kin = &parent->mcKin;  // kinematic state of radar parent object
    const tcKinematics *tgt_kin = &target->mcKin;  // state of target object

    tcAirDetectionDBObject* detectionData = dynamic_cast<tcAirDetectionDBObject*>(target->mpDBObject);
    if (detectionData == 0) return -999.0f;


    targetAz_rad = nsNav::GCHeadingApprox_rad(parent_kin->mfLat_rad, parent_kin->mfLon_rad,
        tgt_kin->mfLat_rad, tgt_kin->mfLon_rad);
    targetAlt_m = target->mcKin.mfAlt_m + detectionData->effectiveHeight_m;

    float signature = -123.4f;
    if (mpDBObj->isIR)
    {
        float aspect_rad = targetAz_rad - tgt_kin->mfHeading_rad + C_PI;
        if (aspect_rad >= C_TWOPI) aspect_rad -= C_TWOPI;

        signature = 
            target->GetIRSignature(C_180OVERPI*aspect_rad);
    }
    else
    {
        signature = target->GetOpticalCrossSection(); // no aspect dependence for EO yet
    }

    return signature;
    
}


/**
*
*/
bool tcOpticalSensor::CanDetectTarget(const tcGameObject* target, float& range_km, bool useRandom)
{

    float targetRange_km;
    float coverageAz1, coverageAz2;
    bool bInSearchVolume = false;

    wxASSERT(mpDBObj);

	detectionCandidate = target->mnID;
	last_margin_dB = -99.9f;
    lastTargetSignature_dB = -999.0f;
    last_az_rad = -99.9f;

    if (!mbActive) return false;

    if (isSemiactive)
    {
        float designatorRange_km = 0;
        tcOpticalSensor* designator = GetLaserDesignator();
        if (designator == 0) return false;
        if (!designator->CanDetectTarget(target, designatorRange_km)) return false;
    }

    float targetAz_rad = 0;
    float targetAlt_m = -999.0f;
    float targetCrossSection_dBsm = CalculateTargetSignature(target, targetAz_rad, targetAlt_m);

    last_az_rad = targetAz_rad;

    const tcKinematics *parent_kin = &parent->mcKin;  // kinematic state of radar parent object
    const tcKinematics *tgt_kin = &target->mcKin;  // state of target object

    lastTargetSignature_dB = targetCrossSection_dBsm;

    unsigned int targetClassification = target->mpDBObject->mnType;
    if (targetClassification & PTYPE_SUBSURFACE)
    {
        if (target->mcKin.mfAlt_m >= -18.0f)
        {
            targetClassification |= PTYPE_SURFACE;
        }
    }

    unsigned int targetMask = 0;
    if (mpDBObj->mbDetectsAir) targetMask |= PTYPE_AIR;
	if (mpDBObj->mbDetectsMissile) targetMask |= PTYPE_MISSILE;
    if (mpDBObj->mbDetectsSurface) targetMask |= PTYPE_SURFACE;
	if (mpDBObj->mbDetectsGround) targetMask |= PTYPE_GROUND;

    bool bTargetTypeMatch = (targetClassification & targetMask) != 0;
    bTargetTypeMatch = bTargetTypeMatch || (mpDBObj->mbDetectsAir && (targetClassification == PTYPE_AIRCM)); // treat AIR_CM's as potential air targets

	if (!bTargetTypeMatch) return false;


    if (mpDBObj->mfFieldOfView_deg >= 360.0f) 
    {
        bInSearchVolume = true;
    }
    else 
    {
        float lookAz_rad = parent->mcKin.mfHeading_rad + mountAz_rad;
        float fHalfFOV_rad = 0.5f*C_PIOVER180*mpDBObj->mfFieldOfView_deg;
        coverageAz1 = lookAz_rad - fHalfFOV_rad;
        coverageAz2 = lookAz_rad + fHalfFOV_rad;
        bInSearchVolume = AngleWithinRange(targetAz_rad,coverageAz1,coverageAz2) != 0;
        if (!bInSearchVolume) {range_km=0;return false;}
    }

    float horizonRange_km = C_VISUALHOR*(sqrtf(targetAlt_m) +sqrtf(parent_kin->mfAlt_m + mfSensorHeight_m));

    targetRange_km = C_RADTOKM*nsNav::GCDistanceApprox_rad(parent_kin->mfLat_rad, parent_kin->mfLon_rad,
		tgt_kin->mfLat_rad,tgt_kin->mfLon_rad, parent_kin->mfAlt_m, tgt_kin->mfAlt_m);

    range_km = targetRange_km;
	if ((targetRange_km > horizonRange_km) || (targetRange_km > mpDBObj->mfMaxRange_km))
    {
        return false;
    }

    if (!HasLOS(target)) return false;

    if ((isSemiactive || isDesignator) && !mpDBObj->isSurveillance)
    {
        last_margin_dB = 99.9f;
        return true; // assume designator always bright enough, semiactive sens enough to detect if within max range
    }

    // add 0.25 dB/km atmospheric attenuation
    float atmosphericAtten_dB = 0.25 * (mpDBObj->mfRefRange_km - targetRange_km);

    // calculate night penalty
    float nightPenalty = CalculateNightPenalty(target);

    float margin_dB = 
            20.0f*(log10f(nightPenalty * mpDBObj->mfRefRange_km) - log10f(targetRange_km)) + targetCrossSection_dBsm + atmosphericAtten_dB;

    last_margin_dB = margin_dB;

    // don't do random detections for missiles (problem where launched with lock that disappears in transition region)
    if (mnMode == SSMODE_SURVEILLANCE)
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
bool tcOpticalSensor::InitFromDatabase(long key)
{
	wxASSERT(database);

    tcSensorState::InitFromDatabase(key);

    mpDBObj = dynamic_cast<tcOpticalDBObject*>(database->GetObject(key));
    if (mpDBObj == NULL) 
    {
        fprintf(stderr, "Error - tcOpticalSensor::InitFromDatabase - Not found in db or bad class for key\n");
        return false;
    }

	mfSensorHeight_m = 10.0f;
    mnMode = SSMODE_SURVEILLANCE;
    mbActive = true;

    return true;
}

bool tcOpticalSensor::IsDesignator() const
{
    return isDesignator;
}

/**
* Alternative to dynamic_cast
*/
bool tcOpticalSensor::IsOptical() const
{
    return true;
}

/**
*
*/
void tcOpticalSensor::Serialize(tcFile& file, bool mbLoad) 
{
    tcSensorState::Serialize(file, mbLoad);
}



/**
*
*/
tcOpticalSensor& tcOpticalSensor::operator=(tcOpticalSensor& ss) 
{
    tcSensorState::operator =(ss);

    mpDBObj = ss.mpDBObj;
    return(*this);
}

/**
*
*/
tcOpticalSensor* tcOpticalSensor::Clone(void) 
{
    tcOpticalSensor *pNew = new tcOpticalSensor();
    *pNew = *this;
    return pNew;
}



/**
* For missile seekers call to check for switch
* to countermeasure target
*/
void tcOpticalSensor::CounterMeasureTest(double t)
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

    
    //float targetRangeRate_mps = parent->mcKin.CalculateRangeRate(target->mcKin);
    float targetRange_km = parent->mcKin.RangeToKmAlt(target->mcKin);
    float targetBearing_rad = parent->mcKin.HeadingToRad(target->mcKin);

    float targetHeight_m = 0; // equivalent height of target for radar horizon
    float fTargetAz_rad = 0;
    // could probably find way to use rcs from parent routine
    float targetSignature_dB = CalculateTargetSignature(target, fTargetAz_rad, targetHeight_m); 

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

		bool isEligible = (cmData != 0) && cmData->IsFlare() && 
            (obj->mpDBObject->mnType == PTYPE_AIRCM);
        float range_km;

        if (isEligible && CanDetectTarget(obj, range_km))
        {
            float objRange_km = parent->mcKin.RangeToKmAlt(obj->mcKin);
            float objSignature_dB = lastTargetSignature_dB;
            float objBearing_rad = parent->mcKin.HeadingToRad(obj->mcKin);

            float dBearing_rad = fabsf(objBearing_rad - targetBearing_rad);
            if (dBearing_rad > C_PI) dBearing_rad = C_TWOPI - dBearing_rad;

            float rangeFactor = (fabsf(objRange_km - targetRange_km) > 0.25f) ? 0.5f : 1.0f;
            float rcsFactor = (objSignature_dB < (targetSignature_dB - 3)) ? 0.5f : 1.0f;
            float bearingFactor = (dBearing_rad > 0.349) ? 0.25f: 1.0f; // penalize more than 20 deg off

            float prob_success = mpDBObj->counterMeasureFactor * cmData->effectiveness * 
                 rangeFactor * rcsFactor * bearingFactor;
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


unsigned tcOpticalSensor::GetFireControlTrackCount() const
{
	return fireControlTrackCount;
}

unsigned tcOpticalSensor::GetMaxFireControlTracks() const
{
	return mpDBObj->maxFireControlTracks;
}

bool tcOpticalSensor::IsSemiactive() const
{
    return isSemiactive;
}

/**
* Does not test if radar can detect target.
* @return true if track is available.
*/
bool tcOpticalSensor::IsTrackAvailable()
{
    return (fireControlTrackCount < mpDBObj->maxFireControlTracks);
}

/**
* if track is available, reserve a track.
* The current approach to semi-active guidance is to require each 
* missile to request one track per target, even if it is the same 
* target as a pre-existing track.
* Calling method must check if target is detectable for this to
* work properly.
*/
bool tcOpticalSensor::RequestTrack(long targetId)
{
    if (IsTrackAvailable())
    {
        fireControlTrackCount++;
        return true;
    }
    else
    {
        return false;
    }
}

bool tcOpticalSensor::ReleaseTrack(long targetId)
{
    if (fireControlTrackCount > 0)
    {
        fireControlTrackCount--;
        return true;
    }
    else
    {
        fprintf(stderr, "tcRadar::tcOpticalSensor called with no tracks\n");
        return false;
    }
}


/**
* Updates missile seeker radar.
*/
void tcOpticalSensor::UpdateSeeker(double t)
{
    long nTargetID;
    tcGameObject *ptarget = 0;
    int bFound;
    tcMissileObject* missile = 0;

    switch (mnMode) 
    {
    case SSMODE_SEEKERACQUIRE:        // fall through to SEEKERTRACK
    case SSMODE_SEEKERTRACK:
        nTargetID = mcTrack.mnID;
        if (nTargetID == parent->mnID) // no self detection
        { 
            bFound = false;
        } 
        else
        {
            bFound = simState->maPlatformState.Lookup(nTargetID,ptarget);
        }

        missile = dynamic_cast<tcMissileObject*>(parent);
        if ((missile != 0) && bFound && (missile->mfInterceptTime < 5.0f) && 
            (lastCounterMeasureTime < (t - 1.0)))
        {
            CounterMeasureTest(t);
        }


        if (bFound) 
        {  // own-alliance is allowed
            float fRange_km;
            if (CanDetectTarget(ptarget, fRange_km)) 
            {
                UpdateTrack(ptarget, t);
                return;
            }
        }
        // shut down missile if track lost for > 7 seconds

		parent->SetHeading(parent->mcKin.mfHeading_rad); // stop turning if track lost
        if ((mnMode == SSMODE_SEEKERTRACK)&&
            (t - mcTrack.mfTimestamp) > 7.0)
        {
            parent->SelfDestruct();
            mcTrack.mnID = NULL_INDEX;
#ifdef _DEBUG
            if(simState->mpUserInfo->IsOwnAlliance(parent->GetAlliance())) 
            {
                char zBuff[128];
                _snprintf(zBuff, 128, "%s shut down (%s)\n", parent->mzUnit.c_str(), parent->mzClass.c_str());
                simState->mpCommandInterface->DisplayInfoMessage(zBuff);
            }
#endif
            return;
        }
        // this code to enter search mode after track lost
        //pTrack->mnID = NULL_INDEX; 
        //apRadarSS->mnMode = SSMODE_SEEKERSEARCH; 
        break;
    case SSMODE_SEEKERSEARCH:
        {
            // get list of candidate tracks/detections
            tcGeoRect region;   
            GetTestArea(region);

            tcGameObjIterator iter(region);
            float minRange = 1e15f;
            long minID = NULL_INDEX;

            // find closest detectable target
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
                    bool bDetected = CanDetectTarget(target, range_km);
                    if ((bDetected) && (range_km < minRange))
                    {
                        minID = target->mnID;
                        minRange = range_km;
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
            mfLastScan = t - 30.0f; // to force fast switch to track for optical
        }
    }
}

/**
* Called after a surveillance detection to update sensor map for
* appropriate alliance.
*/
void tcOpticalSensor::UpdateSensorMap(double t, const tcGameObject* target, float range_km, float az_rad)
{
	wxASSERT(detectionCandidate == target->mnID);

    tcSensorMapTrack* pSMTrack = 0;
    tcSensorReport* report = simState->mcSensorMap.GetOrCreateReport(parent->mnID, mpDBObj->mnKey, target->mnID,
            pSMTrack, parent->GetAlliance());
    if (report == 0) return;

    // check if this should use active or passive model first
    wxASSERT(mpDBObj->rangeError > 0);
    bool activeOptical = mpDBObj->rangeError > 1.0f; // values 0+ to 1 are passive fractional range errors, > 1 is active absolute errors
    
    if (activeOptical)
    {
        tcSensorState::UpdateActiveReport(report, t, az_rad, range_km, target->mcKin.mfAlt_m, pSMTrack);

        report->speedEstimate_mps = C_KTSTOMPS * target->mcKin.mfSpeed_kts * cosf(target->mcKin.mfClimbAngle_rad);
        report->speedVariance = 1.0f;
        report->headingEstimate_rad = target->mcKin.mfHeading_rad;
        report->headingVariance = 0.001f;
        report->validFlags |= tcSensorReport::SPEED_VALID | tcSensorReport::HEADING_VALID;
    }
    else
    {
        tcSensorState::UpdatePassiveReport(report, t, az_rad, range_km, pSMTrack);
    }


    wxASSERT(pSMTrack != 0);
    if (pSMTrack == 0) return;

	// update classification
    report->classification = target->mpDBObject->mnType;
    if ((report->classification & PTYPE_MISSILE) != 0) 
    {
        report->alliance = target->GetAlliance();
    }

    if (last_margin_dB >= mpDBObj->idThreshold_dB)
    {
        report->alliance = target->GetAlliance();
        report->databaseID = target->mnDBKey;
    }


    bool bNewDetection = pSMTrack->IsNew();
    if (bNewDetection) 
    {
        pSMTrack->UpdateTrack(0);
        if (simState->mpUserInfo->IsOwnAlliance(parent->GetAlliance())) 
        {
            tcSound::Get()->PlayEffect("LowBeep");
        }
        //fprintf(stdout, "target %d detected (optical) at %3.1f km at time %.1f [a:%d]\n",
        //    target->mnID,range_km,t,parent->GetAlliance());
        tcEventManager::Get()->NewContact(parent->GetAlliance(), pSMTrack);
    }

}

void tcOpticalSensor::UpdateSurveillance(double t)
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
            bool bDetected = (parent->GetAlliance() != target->GetAlliance()) &&
                CanDetectTarget(target,range_km);
            if (bDetected) UpdateSensorMap(t, target, range_km, last_az_rad);

        }
    }
}

/**
* Update sensor track with target state. Normally used with
* missile seekers.
*/
void tcOpticalSensor::UpdateTrack(const tcGameObject* target, double t)
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
    if (mnMode == SSMODE_SEEKERACQUIRE) 
    {
        mnMode = SSMODE_SEEKERTRACK;
        //if (simState->mpUserInfo->IsOwnAlliance(parent->GetAlliance())) 
        //{
        //    tcSound::Get()->PlayEffect("TwoBeeps");
        //}
    }
}

void tcOpticalSensor::Update(double t)
{
    if (!UpdateScan(t)) return; // only update once per scan period
    wxASSERT(parent);

    switch (mnMode)
    {
    case SSMODE_SURVEILLANCE:
        {
            UpdateSurveillance(t);
        }
        break;
    case SSMODE_SEEKERTRACK:
    case SSMODE_SEEKERSEARCH:
    case SSMODE_SEEKERACQUIRE:
        {
            UpdateSeeker(t);
        }
    case SSMODE_FC:
        break;
    default:
        wxASSERT(false);
        break;
    }

}

/**
*
*/
tcOpticalSensor::tcOpticalSensor() 
: tcSensorState(),
  last_margin_dB(0)
{
    mpDBObj = NULL;
}

tcOpticalSensor::tcOpticalSensor(tcOpticalDBObject* dbObj)
: tcSensorState(dbObj),
  mpDBObj(dbObj),
  last_margin_dB(0),
  fireControlTrackCount(0),
  isSemiactive(mpDBObj->isSemiactive),
  isDesignator(mpDBObj->isDesignator)
{
	wxASSERT(dbObj);

    mnMode = dbObj->isSurveillance ? SSMODE_SURVEILLANCE : SSMODE_FC;
    mfSensorHeight_m = 10.0f;
	mbActive = true; // optical defaults to always on

    if (!dbObj->isDesignator)
    {
	    isHidden = true; // hide optical sensors
    }
    else
    {
        isHidden = false;
    }
}

/**
*
*/
tcOpticalSensor::~tcOpticalSensor() 
{

}