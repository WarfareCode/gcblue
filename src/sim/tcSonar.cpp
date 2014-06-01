/**
**  @file tcSonar.cpp
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
#include "nsNav.h"
#include "tcSonar.h"
#include "tcGameObject.h"
#include "tcHeloObject.h"
#include "tcSurfaceObject.h"
#include "tcSubObject.h"
#include "tcTorpedoObject.h"
#include "tcWaterCM.h"
#include "tcPlatformDBObject.h"
#include "tcSonarDBObject.h"
#include "tcWaterDetectionDBObject.h"
#include "tcCounterMeasureDBObject.h"
#include "tcSimState.h"
#include "tcGameObjIterator.h"
#include "tcSonarEnvironment.h"
#include "common/tcObjStream.h"
#include "tcGameStream.h"
#include "simmath.h"
#include "tcAllianceInfo.h"
#include "tcEventManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// break up this file later

float tcSonar::last_TL = 0;
float tcSonar::DT = 0.0f;

/**
* Load state from stream
*/
tcUpdateStream& tcSonar::operator<<(tcUpdateStream& stream)
{
    tcSensorState::operator<<(stream);


    return stream;
}

/**
* Save state to stream
*/
tcUpdateStream& tcSonar::operator>>(tcUpdateStream& stream)
{
    tcSensorState::operator>>(stream);

    return stream;
}


tcGameStream& tcSonar::operator<<(tcGameStream& stream)
{    
    tcSensorState::operator<<(stream);

    stream >> isPassive;
	stream >> scope_m;
	stream >> depth_m;
    stream >> last_az_rad;
    stream >> last_range_km;
    stream >> last_snr_excess;
    stream >> emitterId;

    return stream;
}

tcGameStream& tcSonar::operator>>(tcGameStream& stream)
{
    tcSensorState::operator>>(stream);

    stream << isPassive;
	stream << scope_m;
	stream << depth_m;
    stream << last_az_rad;
    stream << last_range_km;
    stream << last_snr_excess;
    stream << emitterId;

    return stream;
}

/**
* For debug purposes, calculates detection range using simple TL model
* Assumes omni coverage and sonar active
* Uses target terrain height for bottom depth
* Changed this 15MAY2011 to iterate through calls to CanDetectTarget for range estimate
*   instead of maintaining a separate calculation
*/
float tcSonar::CalculateSimpleDetectionRange(tcGameObject* target, float& NL, float& SLp)
{
	std::vector<float> range_km;
	std::vector<float> snr_dB;
	std::vector<bool> canDetect;

	tcKinematics targetKin(target->mcKin); // save kinematics to restore original values when done
	GeoPoint p(parent->mcKin.mfLon_rad, parent->mcKin.mfLat_rad, parent->mcKin.mfAlt_m);
	float targetBearing_rad = parent->mcKin.HeadingToRad(target->mcKin);

	float maxRange_km = 0;

	float minSearchRange_km = 0.1f;
	float maxSearchRange_km = 100.0f;
	

	std::vector<float> searchStepVect_km;
	searchStepVect_km.push_back(1.0f);
	searchStepVect_km.push_back(0.1f);

	for (size_t n=0; n<searchStepVect_km.size(); n++)
	{
		float searchStep_km = searchStepVect_km[n];
		bool searching = true;

		for (float r_km=minSearchRange_km; (r_km<maxSearchRange_km)&&searching; r_km+=searchStep_km)
		{
			GeoPoint ptgt(p.mfLon_rad, p.mfLat_rad, p.mfAlt_m);
			ptgt.Offset(r_km, targetBearing_rad);
			target->mcKin.mfLon_rad = ptgt.mfLon_rad;
			target->mcKin.mfLat_rad = ptgt.mfLat_rad;

			float actualRange_km = 0;
			if (CanDetectTarget(target, actualRange_km, false))
			{
				maxRange_km = std::max(maxRange_km, actualRange_km);
			}
			else
			{
				searching = false;
			}
		}

		// next iteration
		minSearchRange_km = maxRange_km;
		maxSearchRange_km = maxRange_km + searchStep_km;
	}

	target->mcKin = targetKin; // restore values

	return maxRange_km;
}

/**
* Basic sonar equation, R. Urick, Principles of Underwater Sound, 1983.
*/
bool tcSonar::CanDetectTarget(const tcGameObject* target, float& range_km, bool useRandom)
{
    float fCoverageAz1, fCoverageAz2;
    bool isInSearchVolume = false;
    last_snr_excess = -99.9f;
    last_TL = -99.9f;
    range_km = 0;
    emitterId = -1;

    wxASSERT(mpDBObj);

    if (!mbActive) return false;

    const tcKinematics *par_kin = &parent->mcKin;  // kinematic state of sonar parent object
    const tcKinematics *tgt_kin = &target->mcKin;  // state of target object


    tcWaterDetectionDBObject* targetData = dynamic_cast<tcWaterDetectionDBObject*>(target->mpDBObject);
    if (targetData == 0) return false;

    tcWaterDetectionDBObject* parentData = dynamic_cast<tcWaterDetectionDBObject*>(parent->mpDBObject);
    if (parentData == 0)
    {
        wxASSERT(false);
        fprintf(stderr, "tcSonar::CanDetectTarget - invalid parent database type\n");
        return false;
    }

	float targetAz_rad = nsNav::GCHeadingApprox_rad(par_kin->mfLat_rad, par_kin->mfLon_rad,
            tgt_kin->mfLat_rad, tgt_kin->mfLon_rad);

    float targetAspect_rad = targetAz_rad - tgt_kin->mfHeading_rad + C_PI;
    targetAspect_rad += (float(targetAspect_rad >= C_TWOPI))*(-C_TWOPI) + (float(targetAspect_rad < -C_TWOPI))*C_TWOPI;
    float targetAspect_deg = C_180OVERPI * targetAspect_rad;

    float SLp = -999.0f; // passive source level
    float NL = parentData->GetNoiseLevelForSpeedKts(par_kin->mfSpeed_kts); // noise level of parent

	if (isPassive)
	{
		SLp = target->GetSonarSourceLevel(targetAspect_deg);
	}



    if (mpDBObj->mfFieldOfView_deg >= 360.0f)
    {
        isInSearchVolume = true;
    }
	else 
	{
		float lookAz_rad = parent->mcKin.mfHeading_rad + mountAz_rad;

        // 24NOV2009 old code below, couldn't see why not always use mount az as above? old version maybe had no mount az?
		//if (!mpDBObj->isTowed) // blind area to the rear
		//{
		//	lookAz_rad = parent->mcKin.mfHeading_rad + mountAz_rad;
		//}
		//else // towed array has blind area in direction of bow
		//{
		//	lookAz_rad = parent->mcKin.mfHeading_rad - C_PI;
		//}

		float fHalfFOV_rad = 0.5f*C_PIOVER180*mpDBObj->mfFieldOfView_deg;

		fCoverageAz1 = lookAz_rad - fHalfFOV_rad;
		fCoverageAz2 = lookAz_rad + fHalfFOV_rad;

		isInSearchVolume = AngleWithinRange(targetAz_rad, fCoverageAz1, fCoverageAz2) != 0;
	}        


    last_az_rad = targetAz_rad;

	if (!isInSearchVolume) 
	{
		return false;
	}
    
    range_km = C_RADTOKM * nsNav::GCDistanceApprox_rad(par_kin->mfLat_rad, par_kin->mfLon_rad,
        tgt_kin->mfLat_rad, tgt_kin->mfLon_rad);
    float range_m = 1000.0f * range_km;



    float sonarAlt_m = (par_kin->mfAlt_m == 0) ? -5.0f : par_kin->mfAlt_m;
    float targetAlt_m = (tgt_kin->mfAlt_m == 0) ? -5.0f : tgt_kin->mfAlt_m;

    // if parent or target airborne, assume helo dipping sonar and subtract scope_m from alt
    if (sonarAlt_m > 0)
    {
        sonarAlt_m -= scope_m; 
        if (sonarAlt_m > 0) return false; // sonar out of water
    }

    if (targetAlt_m > 0)
    {
        const tcHeloObject* helo = dynamic_cast<const tcHeloObject*>(target);
        if (helo != 0)
        {
            targetAlt_m = helo->GetDippingSonarAlt();
            if (targetAlt_m > 0) return false; // sonar out of water
            
            const tcSonar* sonar = helo->GetStrongestActiveSonar();
            emitterId = sonar->mpDBObj->mnKey;
        }
        else
        {
            return false; // e.g. sonobuoy not in the water yet
        }
    }

    // use average bottom depth of parent platform and target
    float averageBottom_m = -0.5f*(parent->mcTerrain.mfHeight_m + target->mcTerrain.mfHeight_m);
    //averageBottom_m = std::max(averageBottom_m, 

    long key = sensorId;
    float TL = tcSonarEnvironment::Get()->GetTL(key, parent->mfStatusTime, -sonarAlt_m, range_m, -targetAlt_m, averageBottom_m);
    TL += mpDBObj->alpha * range_km;   // add freq based atten here (not in tcSonarEnvironment yet)
    last_TL = TL;

    // ambient noise (flawed as is because assumes target signal is always centered in sonar passband)
    float NL_background_dB = tcSonarEnvironment::Get()->GetAmbientNL(mpDBObj->averageFreq_Hz);
    NL = Add_dB(NL_background_dB, NL);


    float excessSNR;

	if (isPassive)
	{
		// add additional loss if towed array isn't fully deployed
		float scopeLoss_dB = 0;
		if (mpDBObj->isTowed && (scope_m < mpDBObj->maxScope_m))
		{
			scopeLoss_dB = -10.0f*log10f(scope_m / mpDBObj->maxScope_m);
		}

		excessSNR = SLp - TL + mpDBObj->DI - NL - scopeLoss_dB - DT;  // DT now set at init with tcSonar::DT
	}
    else
    {
        float TS = targetData->GetTargetStrength(targetAspect_deg); // target strength for active case

        excessSNR = mpDBObj->SL - 2.0f*TL + TS + mpDBObj->DI - NL - DT; /// DT now set at init with tcSonar::DT
    }
    last_snr_excess = excessSNR;
    last_range_km = range_km;

    if (useRandom)
	{
		return RandomDetect(excessSNR);
	}
	else
	{
		return (excessSNR >= 0);
	}
}


/**
* @return true if CM is rejected by sensor
*/
bool tcSonar::CountermeasureRejected(const tcGameObject* target) const
{
    const tcWaterCM* waterCM = dynamic_cast<const tcWaterCM*>(target);
    if (waterCM == 0)
    {
        wxASSERT(false); // called with invalid target
        return false;
    }

    float prob_failure = mpDBObj->counterMeasureFactor * waterCM->mpDBObject->effectiveness;
    return (randf() > prob_failure);
}

/**
* @return false if key not found in database
*/
bool tcSonar::InitFromDatabase(long key)
{
	wxASSERT(database);

    tcSensorState::InitFromDatabase(key);

    mpDBObj = dynamic_cast<tcSonarDBObject*>(database->GetObject(key));
    if (mpDBObj == NULL) 
    {
        fprintf(stderr, "Error - tcSonar::InitFromDatabase - Not found in db or bad class for key\n");
        return false;
    }
    mnMode = SSMODE_SURVEILLANCE;
    mfSensorHeight_m = 0;
    isPassive = mpDBObj->isPassive;

    return true;
}

/**
*
*/
void tcSonar::Serialize(tcFile& file, bool mbLoad) 
{
    tcSensorState::Serialize(file, mbLoad);
}

/**
*
*/
void tcSonar::SetActiveSonar()
{
    if (mpDBObj->isActive)
    {
        isPassive = false;
    }
    else
    {
        fprintf(stderr, "tcSonar::SetActiveSonar - no active capability (%s)\n", 
            mpDBObj->mzClass.c_str());
    }
}

/**
*
*/
void tcSonar::SetPassiveSonar()
{
    if (mpDBObj->isPassive)
    {
        isPassive = true;
    }
    else
    {
        fprintf(stderr, "tcSonar::SetActiveSonar - no passive capability\n");
    }
}


/**
*
*/
tcSonar& tcSonar::operator=(tcSonar& ss) 
{
    tcSensorState::operator =(ss);

    mpDBObj = ss.mpDBObj;
    return(*this);
}

/**
*
*/
tcSonar* tcSonar::Clone() 
{
    tcSonar *pNew = new tcSonar();
    *pNew = *this;
    return pNew;
}

// added for dbeditor modeling to allow scope to be externally set
void tcSonar::ForceScope(float val_m)
{
	scope_m = val_m;
}

float tcSonar::GetLastSNRExcess() const
{
	return last_snr_excess;
}

float tcSonar::GetScope() const
{
    return scope_m;
}

/**
* @return true if torpedo is running in passive mode
*/
bool tcSonar::IsPassive() const
{
    return isPassive;
}

/**
* Alternative to dynamic_cast
*/
bool tcSonar::IsRadar() const
{
    return false;
}

/**
* Alternative to dynamic_cast
*/
bool tcSonar::IsSonar() const
{
    return true;
}



/**
* Updates torpedo sonar
*/
void tcSonar::UpdateSeeker(double t)
{

    if (mpDBObj->isWakeHoming)
    {
        UpdateSeekerWakeHoming(t);
        return;
    }


    long nTargetID;
    tcGameObject *ptarget = 0;
    int bFound;


    switch (mnMode) 
    {
    case SSMODE_SEEKERACQUIRE:        // fall through to SEEKERTRACK
    case SSMODE_SEEKERTRACK:
        {
            nTargetID = mcTrack.mnID;
            if (nTargetID == parent->mnID) // no self detection
            { 
                bFound = false;
            } 
            else
            {
                bFound = simState->maPlatformState.Lookup(nTargetID,ptarget);
            }

            if (bFound) 
            {  // own-alliance is allowed
                float fRange_km;
                if (CanDetectTarget(ptarget, fRange_km)) 
                {
                    //fprintf(stdout, "Torpedo %d updating target %d\n", parent->mnID, ptarget->mnID);
                    UpdateTrack(ptarget, t);
                    return;
                }
            }
            // switch back to search mode if track lost or acquire failed
            bool returnToSearch = (mnMode == SSMODE_SEEKERACQUIRE) || (!bFound) ||
                ((mnMode == SSMODE_SEEKERTRACK)&&(t - mcTrack.mfTimestamp) > 6.0);
            if (returnToSearch)
            {
                //fprintf(stdout, "Torpedo %d lost target %d\n", parent->mnID, ptarget->mnID);
                mcTrack.mnID = -1; 
                mnMode = SSMODE_SEEKERSEARCH;
                return;
            }
        }
        break;
    case SSMODE_SEEKERSEARCH:
        {
            // get list of candidate tracks/detections
            tcGeoRect region;   
            GetTestArea(region);

            tcGameObjIterator iter(region);
            float minParam = 1e15f;
            long minID = -1;

            unsigned int detectMask = PTYPE_SURFACE;
            if (!mpDBObj->isWakeHoming) detectMask |= PTYPE_SUBSURFACE;
            tcTorpedoObject* torpedo = dynamic_cast<tcTorpedoObject*>(parent);

            // find closest detectable target
            for (iter.First();iter.NotDone();iter.Next())
            {
                tcGameObject *target = iter.Get();

                bool isEligible = (target->mpDBObject->mnType != PTYPE_TORPEDO) &&
                    ((target->mpDBObject->mnType & detectMask) != 0) && (target != parent);

                // ignore targets (don't test) outside of programmed depth limits
                if (torpedo && ((-target->mcKin.mfAlt_m > torpedo->floor_m) ||
                    (-target->mcKin.mfAlt_m < torpedo->ceiling_m)))
                {
                    isEligible = false;
                }

                if (isEligible)
                {
                    float range_km;
                    float searchParam;
                    /* Substitute this to disable own-alliance seeker detections:
                    ** bool bDetected = (parent->GetAlliance() != target->GetAlliance()) &&
                    **    CanDetectTarget(target,range_km);
                    */
                    bool bDetected = CanDetectTarget(target, range_km);

                    // do additional CM success check if necessary
                    if (bDetected && (target->mpDBObject->mnType == PTYPE_WATERCM))
                    {
                        bDetected = bDetected && (!CountermeasureRejected(target));
                    }


                    /* For active sonars, choose closest target in range,
                    ** for passive choose target with strongest receive signal
                    */
                    if (isPassive) searchParam = -last_snr_excess;
                    else searchParam = range_km;
                        
                    if ((bDetected) && (searchParam < minParam))
                    {
                        minID = target->mnID;
                        minParam = searchParam;
                    }
                }
            }
           
            if (minID == -1) return; // no targets found
            parent->DesignateTarget(minID); // select closest as target
            //fprintf(stdout, "Torpedo %d targeting %d\n", parent->mnID, minID);
        }
    }

}


void tcSonar::UpdateSeekerWakeHoming(double t)
{
    tcSurfaceObject* trackTarget = 0;
    tcTorpedoObject* torpedo = dynamic_cast<tcTorpedoObject*>(parent);

    const float detectionDist_m = 500.0f; // hard code 0.5 km dist from wake

    switch (mnMode) 
    {
    case SSMODE_SEEKERACQUIRE:        // fall through to SEEKERTRACK
    case SSMODE_SEEKERTRACK:
        {
            long nTargetID = mcTrack.mnID;
            if (nTargetID == parent->mnID) // no self detection
            { 
                mcTrack.mnID = -1; 
                mnMode = SSMODE_SEEKERSEARCH;
                return;
            } 
            else
            {
                tcGameObject* obj = 0;
                simState->maPlatformState.Lookup(nTargetID, obj);
                trackTarget = dynamic_cast<tcSurfaceObject*>(obj);
            }
        }
        break;
    case SSMODE_SEEKERSEARCH:
        {
            // get list of candidate tracks/detections
            tcGeoRect region;   
            GetTestArea(region);

            tcGameObjIterator iter(region);

            wxASSERT(torpedo != 0);

            // find first detectable target
            for (iter.First();(iter.NotDone() && (trackTarget == 0));iter.Next())
            {
                tcSurfaceObject *target = dynamic_cast<tcSurfaceObject*>(iter.Get());

                bool isEligible = (target != 0) && (target != parent);

                if (isEligible && (torpedo != 0))
                {
                    tcPoint currentPos(torpedo->mcKin.mfLon_rad, torpedo->mcKin.mfLat_rad);
                    tcPoint nextPos;
                    size_t leg;
                    bool bDetected = target->IsNearWake(currentPos, detectionDist_m, nextPos, leg);

                    if (bDetected)
                    {
                        parent->DesignateTarget(target->mnID);
                        mnMode = SSMODE_SEEKERTRACK;
                        trackTarget = target;
                    }
                }
            }
           
        }
    }

    // update track if applicable
    if (trackTarget != 0)
    {
        tcPoint currentPos(torpedo->mcKin.mfLon_rad, torpedo->mcKin.mfLat_rad);
        tcPoint nextPos;
        size_t leg;
        bool bDetected = trackTarget->IsNearWake(currentPos, detectionDist_m, nextPos, leg);

        if (bDetected)
        {
            if (leg != 0) // tracking wake
            {
                mcTrack.mfLat_rad = nextPos.y;
                mcTrack.mfLon_rad = nextPos.x;
                mcTrack.mfAlt_m = -5.0f;
                mcTrack.mfSpeed_kts = 0;
                mcTrack.mfHeading_rad = 0;
                mcTrack.mfClimbAngle_rad = 0;
                mcTrack.mfTimestamp = t;
                mcTrack.mnFlags = TRACK_ALT_VALID;
            }
            else // terminal leg, just cheat and use target obj kin
            {
                mcTrack.mfLat_rad = (float)trackTarget->mcKin.mfLat_rad;
                mcTrack.mfLon_rad = (float)trackTarget->mcKin.mfLon_rad;
                mcTrack.mfAlt_m = -5.0f;
                mcTrack.mfSpeed_kts = trackTarget->mcKin.mfSpeed_kts;
                mcTrack.mfHeading_rad = trackTarget->mcKin.mfHeading_rad;
                mcTrack.mfClimbAngle_rad = 0;
                mcTrack.mfTimestamp = t;
                mcTrack.mnFlags = (TRACK_HEADING_VALID | TRACK_SPEED_VALID 
                    | TRACK_ALT_VALID);
            }
        }
    }
}


/**
* Called after a surveillance detection to update sensor map for
* appropriate alliance.
*/
void tcSonar::UpdateSensorMapActive(double t, const tcGameObject* target, float range_km)
{
    tcSensorMapTrack* pSMTrack = 0;
    tcSensorReport* report = simState->mcSensorMap.GetOrCreateReport(parent->mnID, mpDBObj->mnKey, target->mnID,
            pSMTrack, parent->GetAlliance());
    if (report == 0) return;

    float az_rad = parent->mcKin.HeadingToRad(target->mcKin);

    tcSensorState::UpdateActiveReport(report, t, az_rad, range_km, target->mcKin.mfAlt_m, pSMTrack);

    double trackLife = report->GetTrackLife();

	if (trackLife > 20.0)
	{
        const float headingErrorFactor_rad = (C_PIOVER180 * 10.0f);
        float headingError_rad = headingErrorFactor_rad * tcSensorState::GetErrorFactor(parent->mnID + 300, mpDBObj->mnKey, az_rad);
        report->headingEstimate_rad = target->mcKin.mfHeading_rad + headingError_rad;
        report->headingVariance = headingErrorFactor_rad * headingErrorFactor_rad * C_U2GVAR;

        report->speedEstimate_mps = C_KTSTOMPS * target->mcKin.mfSpeed_kts;
        report->speedVariance = 1.0f;

        report->validFlags |= tcSensorReport::SPEED_VALID | tcSensorReport::HEADING_VALID;
	}
	else
	{
		report->headingEstimate_rad = 0;
        report->headingVariance = 99.0f;
        report->speedEstimate_mps = 0;
        report->speedVariance = 99.0f;
	}


    if (trackLife > 10.0)
    {
        UINT16 nClassification = target->mpDBObject->mnType;
        report->classification = nClassification;

        if (nClassification & PTYPE_TORPEDO) 
        {
            report->alliance = target->GetAlliance();
        }

        if (last_snr_excess >= mpDBObj->idThreshold_dB)
        {
            report->databaseID = target->mnDBKey;
        }
    }

    bool bNewDetection = pSMTrack->IsNew();
    if (bNewDetection) 
    {
        pSMTrack->UpdateTrack(0);
        if (simState->mpUserInfo->IsOwnAlliance(parent->GetAlliance())) 
        {
            tcSound::Get()->PlayEffect("shishding");
        }
        tcEventManager::Get()->NewContact(parent->GetAlliance(), pSMTrack);
        //fprintf(stdout, "%s (%s): target %d (%s) detected by active sonar at %3.1f km at time %.1f "
        //    "(%.1f dB) (a:%d)\n",
        //    parent->mzUnit.c_str(), parent->mzClass.c_str(), target->mnID, target->mzClass.c_str(),
        //    range_km, t, last_snr_excess, parent->GetAlliance());
    }

}

/**
* Called after a surveillance detection to update sensor map for
* appropriate alliance.
*/
void tcSonar::UpdateSensorMapPassive(double t, const tcGameObject* target, 
                                     float range_km, float az_rad)
{
    wxASSERT(simState != 0);

    tcSensorMapTrack* pSMTrack = 0;
    tcSensorReport* report = simState->mcSensorMap.GetOrCreateReport(parent->mnID, mpDBObj->mnKey, target->mnID,
            pSMTrack, parent->GetAlliance());
    if (report == 0) return;

    bool bNewDetection = pSMTrack->IsNew();

    tcSensorState::UpdatePassiveReport(report, t, az_rad, range_km, pSMTrack);

    double trackLife = report->GetTrackLife();


	if (trackLife > 20.0)
	{
        GeoPoint p(report->lonEstimate_rad, report->latEstimate_rad, 0);
        float estimatedRange_km = parent->mcKin.RangeToKm(&p);
        float snr_scale = 1.0f / (10.0f + last_snr_excess);
        float headingErrorFactor_rad = (C_PIOVER180 * 200.0f) * snr_scale;
        float headingError_rad = headingErrorFactor_rad * tcSensorState::GetErrorFactor(parent->mnID + 300, mpDBObj->mnKey, az_rad);
        report->headingEstimate_rad = target->mcKin.mfHeading_rad + headingError_rad;
        report->headingVariance = headingErrorFactor_rad * headingErrorFactor_rad * C_U2GVAR;

        float speedErrorFactor = 0.5f * 25.0f * snr_scale;
        float speedError_mps = speedErrorFactor * tcSensorState::GetErrorFactor(parent->mnID + 305, mpDBObj->mnKey, az_rad);
        //float rangeErrorFactor = (estimatedRange_km / range_km);
        report->speedEstimate_mps = speedError_mps + C_KTSTOMPS * target->mcKin.mfSpeed_kts;
        report->speedEstimate_mps = std::max(report->speedEstimate_mps, 0.5f);
        report->speedVariance = speedErrorFactor * speedErrorFactor * C_U2GVAR; // arbitrary number

        report->validFlags |= tcSensorReport::SPEED_VALID | tcSensorReport::HEADING_VALID;
	}
	else
	{
		report->headingEstimate_rad = 0;
        report->headingVariance = 99.0f;
        report->speedEstimate_mps = 0;
        report->speedVariance = 99.0f;
	}

    unsigned int nClassification = target->mpDBObject->mnType;
    bool isTorpedo = (nClassification == PTYPE_TORPEDO);

    if ((trackLife > 30.0) || isTorpedo)
    {
        wxASSERT(target->mpDBObject);
        unsigned int nClassification = target->mpDBObject->mnType;
        if (nClassification & PTYPE_SURFACE)
        {
            nClassification &= 0xFFF0; // leave size field unknown
        }
        if (isTorpedo)
        {
            report->alliance = target->GetAlliance();
        }
        report->classification = nClassification;
    }

    if ((trackLife > 60.0) && (last_snr_excess >= mpDBObj->idThreshold_dB))
	{
        report->databaseID = target->mnDBKey;
        report->alliance = target->GetAlliance();
	}

    
    // update emitter info if applicable
    report->emitterList.clear();
    if (emitterId != -1)
    {
        report->emitterList.push_back(emitterId);
    }

    if (bNewDetection) 
    {
        pSMTrack->UpdateTrack(0);
        if (simState->mpUserInfo->IsOwnAlliance(parent->GetAlliance())) 
        {
            tcSound::Get()->PlayEffect("shishding");
        }
        fprintf(stdout, "%s (%s): target %d (%s) detected by passive sonar at %3.1f km"
            " at time %.1f (%.1f dB) (a:%d)\n",
            parent->mzUnit.c_str(), parent->mzClass.c_str(), target->mnID, target->mzClass.c_str(),
            range_km, t, last_snr_excess, parent->GetAlliance());
    }

}


void tcSonar::UpdateSurveillance(double t)
{
    tcGeoRect region;
    GetTestArea(region);

    tcGameObjIterator iter(region);

    for (iter.First();iter.NotDone();iter.Next())
    {
        tcGameObject* target = iter.Get();
        if (target != parent) // no self detection
        {
            bool isEligible = (target->mpDBObject->mnType & (PTYPE_SUBSURFACE | PTYPE_SURFACE)) != 0;
            
            // if this sonar is passive, allow detection of helo dipping sonar
            bool possibleDippingSonar = isPassive && (target->mpDBObject->mnType == PTYPE_HELO) &&
                (target->mcKin.mfAlt_m < 500.0f);
            isEligible = isEligible || possibleDippingSonar;

            float range_km = 0;
            bool bDetected = 
                (parent->GetAlliance() != target->GetAlliance()) &&
                isEligible &&
                CanDetectTarget(target, range_km);

            if (bDetected)
            {
                if (isPassive)
                {
                    UpdateSensorMapPassive(t, target, range_km, last_az_rad);
                }
                else
                {
                    UpdateSensorMapActive(t, target, range_km);
                }

            }
        }
    }
}

/**
* Update sensor track with target state. Used with
* torpedos
* Assumes CanDetectTarget has been called immediately before with
* this target.
*/
void tcSonar::UpdateTrack(const tcGameObject* target, double t)
{
    bool cheatPassive = last_range_km <= 2.0f; 

    if (isPassive && !cheatPassive)
    {
        float bearingRate = parent->mcKin.BearingRateTo(last_range_km, last_az_rad, 
            target->mcKin.mfSpeed_kts, target->mcKin.mfHeading_rad);

        mcTrack.mfLat_rad = 0;
        mcTrack.mfLon_rad = 0;
        mcTrack.mfAlt_m = target->mcKin.mfAlt_m; // workaround instead of having a passive elevation
        mcTrack.mfSpeed_kts = 0;
        mcTrack.mfHeading_rad = 0;
        mcTrack.bearing_rad = last_az_rad;
        mcTrack.mfClimbAngle_rad = 0; // or could use this as passive elevation
        mcTrack.bearingRate_radps = bearingRate;
        mcTrack.mfTimestamp = t;
        mcTrack.mnFlags = TRACK_BEARING_ONLY | TRACK_ALT_VALID | TRACK_BEARINGRATE_VALID; 
    }
    else
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

    }       

    if (mcTrack.mfAlt_m > -5) mcTrack.mfAlt_m = -5; // limit min depth

    if (mnMode == SSMODE_SEEKERACQUIRE)  
    {
        mnMode = SSMODE_SEEKERTRACK;
    }
}

void tcSonar::Update(double t)
{    
	wxASSERT(sensorPlatform);
	if ((mbActive != 0) && !isPassive)
	{
		sensorPlatform->SetActivityFlag(tcSensorPlatform::ACTIVE_SONAR_ACTIVE);
	}

	UpdateScope(t);

    if (!UpdateScan(t)) return; // only update once per scan period

	float depth_m = -parent->mcKin.mfAlt_m;
	if ((!mpDBObj->isTowed) && (mpDBObj->maxScope_m > 0))
	{
		depth_m += scope_m; // adjust depth with dipping sonar scope
		// de-activate and retract dipping sonar if it's fully deployed and still not in water
		if ((scope_m == mpDBObj->maxScope_m) && (depth_m < 0))
		{
			SetActive(false); 
		}
	}

	if (depth_m < 0) return; // no detections if sonar out of water

    if (mnMode == SSMODE_SURVEILLANCE)
    {
        UpdateSurveillance(t);
    }
    else if ((mnMode == SSMODE_SEEKERTRACK)||(mnMode == SSMODE_SEEKERSEARCH)||(mnMode == SSMODE_SEEKERACQUIRE))
    {
        UpdateSeeker(t);
    }

}

/**
* If this is a towed array or dipping sonar, update the array scope based on state and platform speed
*/
void tcSonar::UpdateScope(double t)
{
	if (mpDBObj->maxScope_m <= 0) return;

	float dt_s = t - parent->mfStatusTime;

	if (IsActive())
	{
		if (scope_m == mpDBObj->maxScope_m) return;

		if (scope_m < mpDBObj->maxScope_m) // stream the towed array (or dipping sonar)
		{
			// towed array streamed at parent platform speed, dipping sonar at fixed 10 m/s
			float dscope_m = (mpDBObj->isTowed) ? dt_s * parent->mcKin.mfSpeed_kts * C_KTSTOMPS :
			        dt_s * 10.0f; 
			scope_m += dscope_m;
		}
		else if (scope_m > mpDBObj->maxScope_m)
		{
			scope_m = mpDBObj->maxScope_m;
		}
	}
	else
	{
		if (scope_m == 0) return;

		if (scope_m > 0) // retract towed array
		{
			float dscope_m = (mpDBObj->isTowed) ? dt_s * parent->mcKin.mfSpeed_kts * C_KTSTOMPS :
			         dt_s * 10.0f; 
			scope_m -= dscope_m;
		}
		else if (scope_m < 0)
		{
			scope_m = 0;
		}
	}

}

/**
*
*/
tcSonar::tcSonar() 
: tcSensorState(),
  mpDBObj(0),
  isPassive(false),
  last_az_rad(0),
  depth_m(0),
  scope_m(0),
  emitterId(-1)
{
    mnMode = SSMODE_SURVEILLANCE;
    mfSensorHeight_m = 0.0f;
}

tcSonar::tcSonar(tcSonarDBObject* dbObj)
: tcSensorState(dbObj),
  mpDBObj(dbObj),
  isPassive(dbObj->isPassive),
  last_az_rad(0),
  depth_m(0),
  scope_m(0),
  emitterId(-1)
{
	wxASSERT(dbObj);

    mnMode = SSMODE_SURVEILLANCE;
    mfSensorHeight_m = 0.0f;
    mbActive = isPassive; // passive sonar default to "on" state
}

/**
*
*/
tcSonar::~tcSonar() 
{
}