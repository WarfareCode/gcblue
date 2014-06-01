/**  
**  @file tcESMSensor.cpp
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

#include "tcESMSensor.h"
#include "aerror.h"
#include "nsNav.h"
#include "tcGameObject.h"
#include "tcMissileObject.h"
#include "tcPlatformObject.h"
#include "tcECM.h"
#include "tcRadar.h"
#include "common/tcStream.h"
#include "common/tcGameStream.h"
#include "common/tcObjStream.h"
#include "tcGameObjIterator.h"
#include "tcSimState.h"
#include "tcMessageInterface.h"
#include "tcEventManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


float tcESMSensor::targetRange_km = -88.8f; 
float tcESMSensor::last_margin_dB = -88.8f;
float tcESMSensor::last_ERP_dBW = -88.8f;
bool tcESMSensor::rwrUpdate = false;


tcGameStream& tcESMSensor::operator<<(tcGameStream& stream)
{    
    tcSensorState::operator<<(stream);

    stream >> lastRWRupdate;
    stream >> rwrWarningLevel;

    return stream;
}

tcGameStream& tcESMSensor::operator>>(tcGameStream& stream)
{
    tcSensorState::operator>>(stream);

    stream << lastRWRupdate;
    stream << rwrWarningLevel;

    return stream;
}


/**
* Load state from stream
*/
tcUpdateStream& tcESMSensor::operator<<(tcUpdateStream& stream)
{
    tcSensorState::operator<<(stream);

    stream >> rwrWarningLevel;

    return stream;
}

/**
* Save state to stream
*/
tcUpdateStream& tcESMSensor::operator>>(tcUpdateStream& stream)
{
    tcSensorState::operator>>(stream);

    stream << rwrWarningLevel;

    return stream;
}




/**
* This method is used for passive seeker (anti-rad or home-on-jam) detection testing. It
* doesn't build an emitter id list like ProcessESMDetection.
*
* TODO: merge this with ProcessESMDetection method, look at search method that
* uses maximum received power vs. range (cheating?)
*/
bool tcESMSensor::CanDetectTarget(const tcGameObject* target, float& range_km, bool useRandom)
{
	float fAz_rad = 0;
	range_km = 0;
    last_margin_dB = -99.0f; ///< from last call to IsDetected
    last_ERP_dBW = -99.0f; ///< from last call to IsDetected

	if (const tcMissileObject *pMissileObj = dynamic_cast<const tcMissileObject*>(target)) 
	{
		if (tcRadar* emitter = pMissileObj->GetSeekerRadar()) // some AGMs have no sensor
		{
			bool bDetected = IsDetectedRadar(emitter, fAz_rad);
			range_km = targetRange_km;
			return bDetected;
		}
		else
		{
			return false;
		}
	}
	else if (const tcPlatformObject *pPlatformObj = dynamic_cast<const tcPlatformObject*>(target))
	{
		if (!pPlatformObj->IsRadiating()) return false;

        bool bDetected = false;
		unsigned nSensors = pPlatformObj->GetSensorCount();
		for (unsigned n=0; (n<nSensors) && (!bDetected); n++) 
		{
			const tcSensorState* sensor = pPlatformObj->GetSensor(n);
			if (const tcRadar* emitter = dynamic_cast<const tcRadar*>(sensor)) 
			{
				bDetected = bDetected || IsDetectedRadar(emitter, fAz_rad);
				range_km = targetRange_km;
			}
            else if (const tcECM* emitter = dynamic_cast<const tcECM*>(sensor)) 
			{
				bDetected = bDetected || IsDetectedECM(emitter, fAz_rad);
				range_km = targetRange_km;
			}
		}

		return bDetected;
	}
	
	return false; // target class does not have radar, so impossible to detect
}

/**
* @return false if key not found in database
*/
bool tcESMSensor::InitFromDatabase(long key)
{
	wxASSERT(database);

    tcSensorState::InitFromDatabase(key);

    mpDBObj = dynamic_cast<tcESMDBObject*>(database->GetObject(key));
    if (mpDBObj == NULL) 
    {
        fprintf(stderr, "Error - tcESMSensor::InitFromDatabase - Not found in db or bad class for key\n");
        return false;
    }

	mfSensorHeight_m = 10.0f;
    mnMode = SSMODE_SURVEILLANCE;
    mbActive = true;

    return true;
}


bool tcESMSensor::IsDetectedECM(const tcECM* emitter, float& az_rad)
{
    wxASSERT(emitter);
    if (emitter == 0) return false;

    float ERP_dBW = emitter->mpDBObj->ERP_dBW; // make ECM easier to detect until model is improved

    return IsDetected(emitter, ERP_dBW, az_rad);

}

bool tcESMSensor::IsDetectedRadar(const tcRadar* emitter, float& az_rad)
{
    wxASSERT(emitter);
    if (emitter == 0) return false;
    if (emitter->IsSemiactive()) return false;

    float ERP_dBW = emitter->mpDBObj->ERPpeak_dBW;

    return IsDetected(emitter, ERP_dBW, az_rad);
}

/**
 *
 */
bool tcESMSensor::IsDetected(const tcSensorState* emitter, float ERP_dBW, float& az_rad)
{
    wxASSERT(emitter);
    wxASSERT(emitter->parent);

    targetRange_km = 0;
    last_margin_dB = -99.0f;
    last_ERP_dBW = -99.0f;

	if ((!mbActive) || (!emitter->IsActive())) return false;

    float emitterFreq_Hz = emitter->mpDBObj->averageFrequency_Hz;
    bool inBand = (mpDBObj->minFrequency_Hz <= emitterFreq_Hz) && 
                  (mpDBObj->maxFrequency_Hz >= emitterFreq_Hz);
    if (!inBand)
    {
        return false;
    }

    const tcKinematics& emitter_kin = emitter->parent->mcKin;

    float emitterERP_dBW = ERP_dBW;
    last_ERP_dBW = ERP_dBW;
    float emitterFOV_rad = C_PIOVER180*emitter->mpDBObj->mfFieldOfView_deg;

    // look az is az relative to north, might have to change later
//    float lookAz_rad = parent->mcKin.mfHeading_rad + mountAz_rad;
    float emitterAz_rad = emitter_kin.mfHeading_rad + emitter->mountAz_rad;


    float fTargetAz_rad; 
    float fCoverageAz1, fCoverageAz2;
    bool bInSearchVolume = false;
    bool bInEmitterScan = false;

    wxASSERT(mpDBObj);
    wxASSERT(parent);

    const tcKinematics& sensor_kin = parent->mcKin; // kinematic state of parent object

    fTargetAz_rad = nsNav::GCHeadingApprox_rad(sensor_kin.mfLat_rad, sensor_kin.mfLon_rad,
        emitter_kin.mfLat_rad, emitter_kin.mfLon_rad);
    az_rad = fTargetAz_rad;
    if (az_rad < 0) {az_rad += C_TWOPI;}

    if (mpDBObj->mfFieldOfView_deg >= 360.0f)
    {
        bInSearchVolume = true;
    }
    else 
    {
        float lookAz_rad = sensor_kin.mfHeading_rad + mountAz_rad;
        float fHalfFOV_rad = 0.5f*C_PIOVER180*mpDBObj->mfFieldOfView_deg;
        fCoverageAz1 = lookAz_rad - fHalfFOV_rad;
        fCoverageAz2 = lookAz_rad + fHalfFOV_rad;
        bInSearchVolume = AngleWithinRange(fTargetAz_rad, fCoverageAz1, fCoverageAz2) != 0;
        if (!bInSearchVolume) {return false;}
    }

    // check same for emitter
    if (emitterFOV_rad >= C_TWOPIM) 
    {
        bInEmitterScan = true;
    }
    else 
    {
        float esmBearing_rad = fTargetAz_rad + C_PI; // bearing of ESM platform relative to emitter
        if (esmBearing_rad > C_TWOPI) {esmBearing_rad -= C_TWOPI;}
        float fHalfFOV_rad = 0.5f * emitterFOV_rad;
        fCoverageAz1 = emitterAz_rad - fHalfFOV_rad;
        fCoverageAz2 = emitterAz_rad + fHalfFOV_rad;
        bInEmitterScan = AngleWithinRange(esmBearing_rad, fCoverageAz1, fCoverageAz2) != 0;
        if (!bInEmitterScan) {return false;}
    }

    float fRadarHorizon = C_RADARHOR*(sqrtf(emitter_kin.mfAlt_m + emitter->mfSensorHeight_m) + sqrtf(sensor_kin.mfAlt_m + mfSensorHeight_m));
    targetRange_km = C_RADTOKM*nsNav::GCDistanceApprox_rad(
        sensor_kin.mfLat_rad, sensor_kin.mfLon_rad,
        emitter_kin.mfLat_rad, emitter_kin.mfLon_rad);

    if (targetRange_km > fRadarHorizon) 
    {
        return false;
    }

    if (!HasLOS(emitter->parent)) return false;

    float fSNR = emitterERP_dBW 
        + 20.0f*(log10f(mpDBObj->mfRefRange_km)-log10f(targetRange_km));

    last_margin_dB = fSNR;

	return RandomDetect(fSNR);
}


bool tcESMSensor::IsESM() const
{
	return true;
}



/**
 *
 */
void tcESMSensor::Serialize(tcFile& file, bool mbLoad) 
{
    tcSensorState::Serialize(file, mbLoad);
}


void tcESMSensor::Update(double t)
{
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
* Special update that only looks at sensors on platforms that are targeting parent
*/
bool tcESMSensor::UpdateScanRWR(double t)
{
    if (!mbActive || (!mpDBObj->isRWR))
    {
        rwrWarningLevel = 0;
        return false;
    }

    if ((t - lastRWRupdate) >= 2.0f)
    {
        lastRWRupdate = t;
        return true;
    }
    else 
    {
        return false;
    }
}

/**
* Updates anti-radiation type seekers
*/
void tcESMSensor::UpdateSeeker(double t)
{
    if (!UpdateScan(t)) return; // only update once per scan period

    long nTargetID;
    tcGameObject *ptarget = 0;
    int bFound;


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
            bFound = simState->maPlatformState.Lookup(nTargetID, ptarget);
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
        /* Shut down missile if track lost for too long
		** Missile will coast up until then allowing hits if missile was close enough
		** to the target before it shut down
		*/
        if ((mnMode == SSMODE_SEEKERTRACK)&&
            (t - mcTrack.mfTimestamp) > 300.0) // set high for now to coast
        {
            parent->SelfDestruct();

            mcTrack.mnID = NULL_INDEX;
#ifdef _DEBUG
            if(simState->mpUserInfo->IsOwnAlliance(parent->GetAlliance())) 
            {
                char zBuff[128];
				_snprintf(zBuff, 128, "Mis %d shut down (%s)\n", parent->mnID, parent->mzClass.c_str());
				tcMessageInterface::Get()->ConsoleMessage(zBuff);
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
            parent->DesignateTarget(minID); // select closest as target
        }
    }
}


void tcESMSensor::UpdateSurveillance(double t)
{
    if (UpdateScanRWR(t))
    {
        UpdateSurveillanceRWR(t);
    }

    if (!UpdateScan(t)) return; // only update once per scan period

    tcGeoRect region;
    GetTestArea(region);

    tcGameObjIterator iter(region);

    for (iter.First();iter.NotDone();iter.Next())
    {
        tcGameObject *target = iter.Get();

		ProcessESMDetection(target, t);
    }
}

void tcESMSensor::UpdateSurveillanceRWR(double t)
{
    wxASSERT(mpDBObj->isRWR);

    rwrUpdate = true;
    rwrWarningLevel = 0;

    std::vector<long> targetersToRemove;

    size_t nTargeters = parent->targeters.size();
    for (size_t n=0; n<nTargeters; n++)
    {
        long targeterId = parent->targeters[n];
        if (tcGameObject* target = simState->GetObject(targeterId))
        {
            float range_km = parent->RangeTo(*target);
            if (range_km < mpDBObj->mfMaxRange_km)
            {
                ProcessESMDetection(target, t);
            }
        }
        else
        {
            targetersToRemove.push_back(targeterId);
        }
    }

    for (size_t n=0; n<targetersToRemove.size(); n++)
    {
        parent->RemoveTargeter(targetersToRemove[n]);
    }

    rwrUpdate = false;
}

/**
* Update sensor track with target state. Normally used with
* missile seekers.
* This version cheats since passive sensor can't directly measure range.
*/
void tcESMSensor::UpdateTrack(const tcGameObject* target, double t)
{
    mcTrack.mfLat_rad = (float)target->mcKin.mfLat_rad;
    mcTrack.mfLon_rad = (float)target->mcKin.mfLon_rad;

	// perturb the latitude to simulate track inaccuracy at longer range
	if (targetRange_km > 1.0f)
	{
		mcTrack.mfLat_rad += randfc(1.6e-6 * targetRange_km); // about 100 m of error at 10 km
	}

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




void tcESMSensor::ProcessESMDetection(tcGameObject* target, double t)
{
    enum {MAX_EMITTERS=4};
    float fAz_rad = 0;

	wxASSERT(parent);

    if (parent->GetAlliance() == target->GetAlliance()) return;

    bool bDetected = false;
    long maEmitter[MAX_EMITTERS];
    int nEmitters = 0;

    if (tcMissileObject *pMissileObj = dynamic_cast<tcMissileObject*>(target)) 
    {
        if (tcRadar* emitter = pMissileObj->GetSeekerRadar()) // some AGMs have no sensor
        {
            bDetected = IsDetectedRadar(emitter, fAz_rad);
            if ((bDetected) && (nEmitters < MAX_EMITTERS)) 
            {
                maEmitter[nEmitters++] = emitter->mnDBKey;
            }
            if (rwrUpdate && bDetected) rwrWarningLevel = 2;
        }
    }
    else if (tcPlatformObject *pPlatformObj = dynamic_cast<tcPlatformObject*>(target))
    {
        if (!pPlatformObj->IsRadiating()) return;

        unsigned nSensors = pPlatformObj->GetSensorCount();
        for (unsigned n=0; n<nSensors; n++) 
        {
            const tcSensorState* sensor = pPlatformObj->GetSensor(n);
            if (const tcRadar* emitter = dynamic_cast<const tcRadar*>(sensor)) 
            {
                if (IsDetectedRadar(emitter, fAz_rad)) 
                {
                    bDetected = true;
                    if (nEmitters < MAX_EMITTERS) 
                    {
                        maEmitter[nEmitters++] = emitter->mnDBKey;
                    }
                    if (rwrUpdate && (rwrWarningLevel == 0)) rwrWarningLevel = 1;
                }
            }
            else if (const tcECM* emitter = dynamic_cast<const tcECM*>(sensor))
            {
                if (IsDetectedECM(emitter, fAz_rad)) 
                {
                    bDetected = true;
                    if (nEmitters < MAX_EMITTERS) 
                    {
                        maEmitter[nEmitters++] = emitter->mnDBKey;
                    }
                }
            }
        }
    }

    if (!bDetected) {return;}

	UpdateSensorMap(target, maEmitter, nEmitters, fAz_rad, t);
}


/**
* Called after ESM detection to update sensor map
*/
void tcESMSensor::UpdateSensorMap(const tcGameObject* target, long* emitters, unsigned int nEmitters,
								  float az_rad, double t)
{
    tcSensorMapTrack *pSMTrack = 0;

	wxASSERT(simState);
	wxASSERT(emitters);

    if (targetRange_km == 0)
    {
        targetRange_km = parent->mcKin.RangeToKmAlt(target); // target range may not be updated when multiple emitters on target
    }

    // call update to check for this report already in track, or for an empty slot
    tcSensorReport* report = 
        simState->mcSensorMap.GetOrCreateReport(parent->mnID, mpDBObj->mnKey, target->mnID, pSMTrack, parent->GetAlliance());

    // update passive report if available
    if (report != 0)
    {
        //bool bNewReport = report->IsNew();
        //if (bNewReport) // new detection report
        //{
        //    // RWR reports jump to classify and range info much quicker
        //    report->startTime = rwrUpdate ? t - 60.0f : t;
        //} 
        
        tcSensorState::UpdatePassiveReport(report, t, az_rad, targetRange_km, pSMTrack);

        double trackLife = report->GetTrackLife();

        unsigned int nClassification = target->mpDBObject->mnType;
        bool isMissile = (nClassification & PTYPE_MISSILE) != 0;
        bool updateClassification = (isMissile || (trackLife > 30.0));

        // TODO: problem here with radar and ESM updates competing
        // need to merge updates vs. taking first one only
        if (updateClassification) 
        {
            report->classification = nClassification & 0xFFF0;
            if (isMissile)
            {
                report->alliance = target->GetAlliance();
            }

            //tcAllianceInfo::Affiliation eAffil = tcAllianceInfo::UNKNOWN;
            //if (isMissile) 
            //{
            //    eAffil = tcAllianceInfo::HOSTILE;
            //}
            //pSMTrack->UpdateClassification(nClassification & 0xFFF0, eAffil, NULL_INDEX);

            //tcEventManager::Get()->UpdatedContact(parent->GetAlliance(), pSMTrack);
        }
        else
        {
            report->classification = 0;
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
            //char zBuff[128];
            //sprintf(zBuff, "target %d detected with ESM at %3.1f deg at time %.1f [a:%d]",
            //    target->mnID, az_rad, t, parent->GetAlliance());
            //WTLC(zBuff);
        }

        /* this section is called even if no free reports are available, (?)
        ** so that ESM can update classification and emitters 
        */

        // update emitter info
        report->emitterList.clear();
        if (last_margin_dB >= mpDBObj->idThreshold_dB)
        {
            for (unsigned int n=0; n<nEmitters; n++) 
            {
                report->emitterList.push_back(emitters[n]);
            }
        }


    }



}



/**
 *
 */
tcESMSensor& tcESMSensor::operator=(tcESMSensor& ss) 
{
    tcSensorState::operator =(ss);

    mpDBObj = ss.mpDBObj;
    return(*this);
}
#if 0
/**
* Load state from stream
*/
tcStream& tcESMSensor::operator<<(tcStream& stream)
{
    tcSensorState::operator<<(stream);

    return stream;
}

/**
* Save state to stream
*/
tcStream& tcESMSensor::operator>>(tcStream& stream)
{
    tcSensorState::operator>>(stream);

    return stream;
}
#endif
/**
 *
 */
tcESMSensor* tcESMSensor::Clone(void) 
{
    tcESMSensor *pNew = new tcESMSensor();
    *pNew = *this;
    return pNew;
}

unsigned char tcESMSensor::GetRWRWarningLevel() const
{
    return rwrWarningLevel;
}



/**
 *
 */
tcESMSensor::tcESMSensor() 
: tcSensorState()
{
    mpDBObj = NULL;
}

tcESMSensor::tcESMSensor(tcESMDBObject* dbObj)
: tcSensorState(dbObj),
  mpDBObj(dbObj),
  lastRWRupdate(0),
  rwrWarningLevel(0)
{
	wxASSERT(dbObj);

    mfSensorHeight_m = 10.0f;
    mnMode = SSMODE_SURVEILLANCE;
    mbActive = true;
}

/**
 *
 */
tcESMSensor::~tcESMSensor() {}