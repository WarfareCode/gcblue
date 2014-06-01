/**  
**  @file tcECM.cpp
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

#include "tcECM.h"
#include "aerror.h"
#include "nsNav.h"
#include "tcGameObject.h"
#include "tcMissileObject.h"
#include "tcPlatformObject.h"
#include "tcRadar.h"
#include "common/tcStream.h"
#include "tcGameStream.h"
#include "tcGameObjIterator.h"
#include "tcSimState.h"
#include "tcMessageInterface.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


tcGameStream& RadarInterface::operator<<(tcGameStream& stream)
{
    stream >> id;
    stream >> idx;

    return stream;
}

tcGameStream& RadarInterface::operator>>(tcGameStream& stream)
{
    stream << id;
    stream << idx;

    return stream;
}


tcRadar* RadarInterface::GetRadar()
{
    tcGameObject* obj = tcSimState::Get()->GetObject(id);

    tcPlatformObject* platform = dynamic_cast<tcPlatformObject*>(obj);
    if (platform)
    {
        return dynamic_cast<tcRadar*>(platform->GetSensorMutable(idx));
    }
    else if (tcMissileObject* missile = dynamic_cast<tcMissileObject*>(obj))
    {
        return missile->GetSeekerRadar();
    }

    return 0;
}

RadarInterface::RadarInterface(long id_, unsigned idx_)
: id(id_), idx(idx_)
{
}

RadarInterface::RadarInterface(const RadarInterface& src)
: id(src.id), idx(src.idx)
{
}

RadarInterface::RadarInterface()
: id(-1), idx(0)
{
}

RadarInterface::~RadarInterface()
{
}

tcGameStream& tcECM::operator<<(tcGameStream& stream)
{    
    tcSensorState::operator<<(stream);

    jamList.clear();

    size_t nJam;
    stream >> nJam;

    for (size_t k=0; k<nJam; k++)
    {
        RadarInterface ri;
        ri.operator<<(stream);

        jamList.push_back(ri);
    }

    return stream;
}

tcGameStream& tcECM::operator>>(tcGameStream& stream)
{
    tcSensorState::operator>>(stream);

    size_t nJam = jamList.size();
    stream << nJam;

    for (size_t k=0; k<nJam; k++)
    {
        jamList[k].operator>>(stream);
    }

    return stream;
}



void tcECM::AddOrUpdateJammerToTarget(tcRadar* targetRadar, unsigned sensorIdx, float JNR_dB, 
                                      float jammerBearing_rad, float jammerElevation_rad)
{
    jamList.push_back(RadarInterface(targetRadar->parent->mnID, sensorIdx));

    targetRadar->AddOrUpdateJammer(parent->mnID, JNR_dB, jammerBearing_rad, jammerElevation_rad);
}


/**
* Remove jammer from each radar on jamList and clear
* This is somewhat expensive but better than having each radar
* independently search for jammers.
*/
void tcECM::ClearJamList()
{
    size_t nRadars = jamList.size();
    for (size_t n=0; n<nRadars; n++)
    {
        if (tcRadar* radar = jamList[n].GetRadar())
        {
            radar->RemoveJammer(parent->mnID);
        }
    }
}

/**
* @return false if key not found in database
*/
bool tcECM::InitFromDatabase(long key)
{
	wxASSERT(database);

    tcSensorState::InitFromDatabase(key);

    mpDBObj = dynamic_cast<tcECMDBObject*>(database->GetObject(key));
    if (mpDBObj == NULL) 
    {
        fprintf(stderr, "Error - tcECM::InitFromDatabase - Not found in db or bad class for key\n");
        return false;
    }

	mfSensorHeight_m = 10.0f;
    mnMode = 0;
    mbActive = false;

    return true;
}


bool tcECM::IsECM() const
{
	return true;
}

/**
 *
 */
void tcECM::Serialize(tcFile& file, bool mbLoad) 
{
    tcSensorState::Serialize(file, mbLoad);
}

/**
* Remove jamming from affected radars before deactivating
*/
void tcECM::SetActive(bool active)
{
    if (active == false)
    {
        ClearJamList();
    }

    tcSensorState::SetActive(active);
}


void tcECM::Update(double t)
{
	wxASSERT(sensorPlatform);
	if (mbActive != 0)
	{
        sensorPlatform->SetActivityFlag(tcSensorPlatform::ECM_ACTIVE);
	}

    if (!UpdateScan(t)) return;

    ClearJamList();
    UpdateBarrage();

}


/**
* Barrage jamming that affects all opfor radars in coverage sector
*/
void tcECM::UpdateBarrage()
{
    tcGeoRect region;
    GetTestArea(region);

    tcGameObjIterator iter(region);

    for (iter.First();iter.NotDone();iter.Next())
    {
        tcGameObject *target = iter.Get();

        UpdateBarrageTarget(target);
    }
}

void tcECM::UpdateBarrageTarget(tcGameObject* target)
{
    if (parent->GetAlliance() == target->GetAlliance()) return; // no own-alliance or self jamming

    bool jamsSeekers = mpDBObj->isEffectiveVsSeeker;
    bool jamsSurveillance = mpDBObj->isEffectiveVsSurveillance;

    tcMissileObject* missile = jamsSeekers ? dynamic_cast<tcMissileObject*>(target) : 0;
    tcPlatformObject* platform = jamsSurveillance ? dynamic_cast<tcPlatformObject*>(target) : 0;
    
    if (platform != 0)
    {        
        //if (!platform->IsRadiating()) return; // update inactive platform radars to prevent switch on/off exploits

        unsigned nSensors = platform->GetSensorCount();
        for (unsigned n=0; n<nSensors; n++) 
        {
            tcSensorState* sensor = platform->GetSensorMutable(n);
            if (tcRadar* radar = dynamic_cast<tcRadar*>(sensor)) 
            {
                UpdateBarrageTargetRadar(radar, n);
            }
        }
    }
    else if (missile != 0)
    {
        if (!missile->IsRadiating()) return;

        if (tcRadar* radar = missile->GetSeekerRadar()) // some AGMs have no sensor
        {
            UpdateBarrageTargetRadar(radar, 0);
        }
    }
}

/**
* Test if radar is within coverage az and radar horizon
* If so then add jammer to radar even if radar is off to prevent switch on/off exploits by game player
*/
void tcECM::UpdateBarrageTargetRadar(tcRadar* radar, unsigned sensorIdx)
{
    wxASSERT(radar);
    wxASSERT(radar->parent);
    wxASSERT(mpDBObj);
    wxASSERT(parent);

    if ((radar == 0) || (radar->parent == 0)) return;

    const tcKinematics& radar_kin = radar->parent->mcKin;
    const tcKinematics& ecm_kin = parent->mcKin; // kinematic state of parent object

    float targetAz_rad = nsNav::GCHeadingApprox_rad(ecm_kin.mfLat_rad, ecm_kin.mfLon_rad,
                                radar_kin.mfLat_rad, radar_kin.mfLon_rad);

    // test if radar is within az coverage of ECM system
    if (mpDBObj->mfFieldOfView_deg < 360.0f)
    { 
        float lookAz_rad = ecm_kin.mfHeading_rad + mountAz_rad;
        float fHalfFOV_rad = 0.5f*C_PIOVER180*mpDBObj->mfFieldOfView_deg;
        float coverageAz1 = lookAz_rad - fHalfFOV_rad;
        float coverageAz2 = lookAz_rad + fHalfFOV_rad;
        bool withinAzCoverage = AngleWithinRange(targetAz_rad, coverageAz1, coverageAz2) != 0;

        if (!withinAzCoverage) return;
    }

    // test if radar platform is within radar horizon of ECM system
    float fRadarHorizon = C_RADARHOR * (sqrtf(radar_kin.mfAlt_m) + sqrtf(ecm_kin.mfAlt_m));
    
    float targetRange_km = C_RADTOKM * nsNav::GCDistanceApprox_rad(
        ecm_kin.mfLat_rad, ecm_kin.mfLon_rad,
        radar_kin.mfLat_rad, radar_kin.mfLon_rad,
        ecm_kin.mfAlt_m, radar_kin.mfAlt_m);

    if (targetRange_km > fRadarHorizon) return;

    // test if radar within frequency range of ECM system
    const tcRadarDBObject* radarData = radar->mpDBObj;
    bool inBand = (mpDBObj->minFrequency_Hz <= radarData->averageFrequency_Hz) && 
                  (mpDBObj->maxFrequency_Hz >= radarData->averageFrequency_Hz);
    if (!inBand) return;

    // calculate bearing of this jammer at radar platform (rotate 180 deg)
    float jammerBearing_rad = targetAz_rad - C_PI;
    if (jammerBearing_rad < C_PI) jammerBearing_rad += C_TWOPI;

    float jammerElevation_rad = nsNav::ElevationAngle(radar_kin.mfAlt_m, ecm_kin.mfAlt_m, 1000.0f*targetRange_km);
    

    // power density in dB(W/m2)
    // use effectiveness rating to represent capability to focus power on parts of band that are needed for jamming
    float bandwidthMismatch = (mpDBObj->maxFrequency_Hz - mpDBObj->minFrequency_Hz) / (radarData->bandwidth_Hz * mpDBObj->effectivenessRating);
    if (_isnan(bandwidthMismatch) || (bandwidthMismatch < 1))
    {
        bandwidthMismatch = 1;
    }

    // calculated in tcRadarDBObject
    //const float A = 7895.68f; // 50 * (4*pi)^2, 50 is detection S/N
    //const float B = 1e12f; // convert km^4 to m^4
    //float range2 = mfRefRange_km * mfRefRange_km;
    //jamConstant_dB = 10*log10f(A * B * range2 * range2 / (cpi_s * bandwidth_Hz)) - ERPaverage_dBW;
	// free space power density calculation
    float Pdens_dBWm2 = mpDBObj->ERP_dBW - 10*log10f((C_FOURPI*1e6f) * targetRange_km * targetRange_km * bandwidthMismatch);
    float JNR_dB = Pdens_dBWm2 + radarData->antennaGain_dBi + radarData->jamConstant_dB;

    AddOrUpdateJammerToTarget(radar, sensorIdx, JNR_dB, jammerBearing_rad, jammerElevation_rad);
}


/**
 *
 */
tcECM& tcECM::operator=(tcECM& ss) 
{
    tcSensorState::operator =(ss);

    mpDBObj = ss.mpDBObj;
    return(*this);
}
#if 0
/**
* Load state from stream
*/
tcStream& tcECM::operator<<(tcStream& stream)
{
    tcSensorState::operator<<(stream);

    return stream;
}

/**
* Save state to stream
*/
tcStream& tcECM::operator>>(tcStream& stream)
{
    tcSensorState::operator>>(stream);

    return stream;
}
#endif
/**
 *
 */
tcECM* tcECM::Clone() 
{
    tcECM *pNew = new tcECM();
    *pNew = *this;
    return pNew;
}



/**
 *
 */
tcECM::tcECM() 
: tcSensorState()
{
    mpDBObj = NULL;
}

tcECM::tcECM(tcECMDBObject* dbObj)
: tcSensorState(dbObj),
  mpDBObj(dbObj)
{
	wxASSERT(dbObj);

    mfSensorHeight_m = 10.0f;
    mnMode = 0;
    mbActive = false; // 7NOV2010 changed default to inactive
}

/**
 *
 */
tcECM::~tcECM() 
{
    ClearJamList();
}

