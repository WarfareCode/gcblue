/**
**  @file tcSensorMapTrack.cpp
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

#include "tcSensorMapTrack.h"
#include "aerror.h"
#include "simmath.h"
#include "tcSimState.h"
#include "tcWeaponObject.h"
#include "tcPlatformDBObject.h"
#include "tcOpticalSensor.h"
#include "common/tcObjStream.h"
#include "tcGameStream.h"
#include "tcDatabaseIterator.h"
#include "tc3DModel.h"
#include "nsNav.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const char* EmitterInfo::GetEmitterName() const
{
	static wxString result;
	if (mnEmitterID != -1)
	{
		result = tcDatabase::Get()->GetObjectClassName(mnEmitterID);
	}
	else
	{
		result = "";
	}

	return result.ToAscii();
}

tcDatabase* tcSensorMapTrack::database = NULL;
tcSimState* tcSensorMapTrack::simState = NULL;
unsigned int tcSensorMapTrack::ambiguityListUpdates = 0;
bool tcSensorMapTrack::autoKillAssess = false;
bool tcSensorMapTrack::sendDetailedTrackInfo = false;


float tcSensorMapTrack::unknownStale = 45.0f;
float tcSensorMapTrack::unknownAgeOut = 120.0f;
float tcSensorMapTrack::missileStale = 15.0f;
float tcSensorMapTrack::missileAgeOut = 40.0f;
float tcSensorMapTrack::torpedoStale = 30.0f;
float tcSensorMapTrack::torpedoAgeOut = 120.0f;
float tcSensorMapTrack::airStale = 30.0f;
float tcSensorMapTrack::airAgeOut = 300.0f;
float tcSensorMapTrack::surfaceStale = 120.0f;
float tcSensorMapTrack::surfaceAgeOut = 1800.0f;
float tcSensorMapTrack::groundStale = 99999.0f;
float tcSensorMapTrack::groundAgeOut = 99999.0f;
float tcSensorMapTrack::reportAgeOut = 120.0f;


struct SensorReportInfo
{
    size_t index;
    float time_s;
    float lonlatUncertainty;
    float altVariance;
};

bool SensorReportSortPredicate(const SensorReportInfo& a, const SensorReportInfo& b)
{
    return (a.time_s > b.time_s);
}


/**
* Set to true to automatically check and mark stale tracks that
* are destroyed.
*/
void tcSensorMapTrack::SetAutoKillAssess(bool state)
{
    autoKillAssess = state;
}




/**
* Loads state from update stream
*/
tcUpdateStream& tcSensorMapTrack::operator<<(tcUpdateStream& stream)
{
    tcTrack::operator<<(stream);

    unsigned char hasTrackDetails;
    stream >> hasTrackDetails;

    maSensorReport.clear();
    emitterInfo.clear();

    if (hasTrackDetails != 0)
    {
        unsigned char nContribs;
        stream >> nContribs;
        wxASSERT(nContribs <= MAX_SENSOR_REPORTS);

        for (unsigned char n=0; n<nContribs; n++)
        {
            float t;
            stream >> t;
            tcSensorReport report_n;
            report_n.timeStamp = double(t);
            
            stream >> report_n.platformID;

            maSensorReport.push_back(report_n);
        }


        unsigned char nEmitters;
        stream >> nEmitters;
        for (unsigned char k=0; k<nEmitters; k++)
        {
            EmitterInfo info;
            std::string emitterClass;
            stream >> emitterClass;
            tcDatabaseObject* data = (emitterClass.size() > 0) ? database->GetObject(emitterClass) : 0;
            if (data != 0)
            {
                info.mfTimestamp = 0;
                info.mnMode = 0;
                info.mnEmitterID = data->mnKey;
                emitterInfo.push_back(info);
            }
        }
    }


    std::string databaseClass;
	stream >> databaseClass;
    tcDatabaseObject* data = (databaseClass.size() > 0) ? database->GetObject(databaseClass) : 0;
	
    if (data != 0)
    {
        IdentifyTrack(data->mnKey);
    }

	stream >> sensorFlags;

    errorPoly.clear();

    unsigned char nPoints;
    stream >> nPoints;

    for (unsigned char n=0; n<nPoints; n++)
    {
        tcPoint p;
        stream >> p.x;
        stream >> p.y;
        
        errorPoly.push_back(p);
    }
    
    UpdateErrorPolyWidth();

    return stream;
}

/**
* Saves state to update stream
*/
tcUpdateStream& tcSensorMapTrack::operator>>(tcUpdateStream& stream)
{
    tcTrack::operator>>(stream);

    unsigned char hasTrackDetails = sendDetailedTrackInfo ? 1 : 0;
    stream << hasTrackDetails;

    if (hasTrackDetails != 0)
    {
        unsigned char nContribs(maSensorReport.size());
        stream << nContribs;

        for (unsigned char n = 0; n<nContribs; n++)
        {
            stream << float(maSensorReport[n].timeStamp);
            stream << maSensorReport[n].platformID;
        }


        unsigned char nEmitters = (unsigned char)emitterInfo.size();
        stream << nEmitters;
        for (unsigned char k=0; k<nEmitters; k++)
        {
            std::string emitterClass = database->GetObjectClassName(emitterInfo[k].mnEmitterID);
            stream << emitterClass;
        }
    }

    // 20SEP2009, changed this, client/server databases don't have same name,key pairs anymore
    std::string databaseClass = database->GetObjectClassName(mnDatabaseID);
	stream << databaseClass;


	stream << sensorFlags;

    unsigned char nPoints = errorPoly.size();
    stream << nPoints;

    for (unsigned char n=0; n<nPoints; n++)
    {
        stream << errorPoly[n].x;
        stream << errorPoly[n].y;
    }

    return stream;
}

/**
* Loads state from game stream
*/
tcGameStream& tcSensorMapTrack::operator<<(tcGameStream& stream)
{
    Clear();

    tcTrack::operator<<(stream);

    maSensorReport.clear();

    unsigned int nContributors;
    stream >> nContributors;

    for (unsigned int k=0; k<nContributors; k++)
    {
        tcSensorReport report_k;
        report_k << stream;
        maSensorReport.push_back(report_k);
    }


    emitterInfo.clear();
    unsigned char nEmitters = 0;
    stream >> nEmitters;
    tcDatabase* database = tcDatabase::Get();
    for (unsigned char k=0; k<nEmitters; k++)
    {
        std::string emitterClass;

        EmitterInfo info;
        stream >> info.mfTimestamp;
        stream >> emitterClass;
        stream >> info.mnMode;

        if (emitterClass.size() > 1)
        {
            info.mnEmitterID = database->GetKey(emitterClass.c_str());
        }
        else
        {
            info.mnEmitterID = -1;
        }

        emitterInfo.push_back(info);
    }

	stream >> assessedDamage;

    unsigned int nIntercepts;
    stream >> nIntercepts;
    for (unsigned int k=0; k<nIntercepts; k++)
    {
        long val;
        stream >> val;
        intercepts.push_back(val);
    }

    unsigned int nEngaged;
    stream >> nEngaged;
    wxASSERT(nEngaged < 256);
    for (unsigned int k=0; k<nEngaged; k++)
    {
        long val;
        stream >> val;
        engaged.push_back(val);
    }

    unsigned int nAmbiguity;
    stream >> nAmbiguity;
    wxASSERT(nAmbiguity < 256);
    for (unsigned int k=0; k<nAmbiguity; k++)
    {
        std::string ambiguityClass;
        long val;

        stream >> ambiguityClass;
        if (ambiguityClass.size() > 1)
        {
            val = database->GetKey(ambiguityClass.c_str());
        }
        else
        {
            val = -1;
        }

        ambiguityList.push_back(val);
    }
    

    stream >> sensorFlags;

    std::string idClass;
	stream >> idClass;
    if (idClass.size() > 1)
    {
        mnDatabaseID = database->GetKey(idClass.c_str());
    }
    IdentifyTrack(mnDatabaseID); // problem here if database modified between save and load!

    size_t nPoints;
    stream >> nPoints;

    for (size_t n=0; n<nPoints; n++)
    {
        tcPoint p;
        stream >> p.x;
        stream >> p.y;
        
        errorPoly.push_back(p);
    }
    UpdateErrorPolyWidth();

    stream >> alwaysVisible;

    return stream;
}

/**
* Saves state to game stream
*/
tcGameStream& tcSensorMapTrack::operator>>(tcGameStream& stream)
{
    tcTrack::operator>>(stream);

    unsigned int nContributors = (unsigned int)maSensorReport.size();
    stream << nContributors;

    for (unsigned int k=0; k<nContributors; k++)
    {
        maSensorReport[k] >> stream;
    }

	

    tcDatabase* database = tcDatabase::Get();
    unsigned char nEmitters = (unsigned char)emitterInfo.size();
    stream << nEmitters;
    for (unsigned char k=0; k<nEmitters; k++)
    {
        stream << emitterInfo[k].mfTimestamp;

        //stream << emitterInfo[k].mnEmitterID;
        std::string emitterClass;
        if (tcDatabaseObject* data = database->GetObject(emitterInfo[k].mnEmitterID))
        {
            emitterClass = data->mzClass.c_str();
        }
        stream << emitterClass;

        stream << emitterInfo[k].mnMode;
    }

	stream << assessedDamage;

    unsigned int nIntercepts = (unsigned int)intercepts.size();
    stream << nIntercepts;
    for (unsigned int k=0; k<nIntercepts; k++)
    {
        stream << intercepts[k];
    }

    unsigned int nEngaged = (unsigned int)engaged.size();
    stream << nEngaged;
    for (unsigned int k=0; k<nEngaged; k++)
    {
        stream << engaged[k];
    }

    unsigned int nAmbiguity = (unsigned int)ambiguityList.size();
    stream << nAmbiguity;
    for (unsigned int k=0; k<nAmbiguity; k++)
    {
        std::string ambiguityClass;
        if (tcDatabaseObject* data = database->GetObject(ambiguityList[k]))
        {
            ambiguityClass = data->mzClass.c_str();
        }
        stream << ambiguityClass;
    }
    

    stream << sensorFlags;

    std::string idClass;
    if (tcDatabaseObject* data = database->GetObject(mnDatabaseID))
    {
        idClass = data->mzClass.c_str();
    }
    stream << idClass;

    size_t nPoints = errorPoly.size();
    stream << nPoints;

    for (size_t n=0; n<nPoints; n++)
    {
        stream << errorPoly[n].x;
        stream << errorPoly[n].y;
    }

    stream << alwaysVisible;


    return stream;
}




/**
* @return false if id already in engaged vector
*/
bool tcSensorMapTrack::AddEngagement(long id)
{
    if (id == -1) return false;

    unsigned nEngaged = engaged.size();
    for(unsigned n=0;n<nEngaged;n++)
    {
        if (engaged[n] == id) return false;
    }
    engaged.push_back(id);
    return true;
}

/**
* @return false if id already in intercepts vector
*/
bool tcSensorMapTrack::AddIntercept(long id)
{
    if (id == -1) return false;

    unsigned nIntercepts = intercepts.size();
    for(unsigned n=0;n<nIntercepts;n++)
    {
        if (intercepts[n] == id) return false;
    }
    intercepts.push_back(id);
    return true;
}

/**
* Try to triangulate track using 2 passive reports
* @return true if successful, false otherwise
*/
bool tcSensorMapTrack::AttemptPassiveTriangulation()
{
#if 0 // obsolete with multivariate gaussian fusion
    // first check if there are multiple bearing-only reports
    // technically unnecessary since this is only called if there are no active reports
    unsigned nPassive = 0;
    for(int n=0;n<mnContributors;n++) 
    {
        tcSensorReport *pSensorReport = &maSensorReport[n];
        if ((pSensorReport->mnFlags & TRACK_BEARING_ONLY) != 0) nPassive++;
    }
    
    if (nPassive < 2)
    {
        return false;
    }
    wxASSERT(mnContributors == 2);

    float brg1_rad = maSensorReport[0].bearingEstimate_rad;
    float err1_rad = maSensorReport[0].bearingError_rad;

    float brg2_rad = maSensorReport[1].bearingEstimate_rad;
    float err2_rad = maSensorReport[1].bearingError_rad;

    float separation_rad = brg1_rad - brg2_rad;
    if ( fabsf(sinf(separation_rad)) < sinf(1.0f*(err1_rad+err2_rad)) ) // better to avoid trig with compares?
    {
        return false; // not enough angular separation
    }

    tcPoint p1;
    p1.x = maSensorReport[0].mfLon_rad;
    p1.y = maSensorReport[0].mfLat_rad;

    tcPoint p2;
    p2.x = maSensorReport[1].mfLon_rad;
    p2.y = maSensorReport[1].mfLat_rad;

    tcPoint result;
    bool valid = TriangulateBearings(p1, brg1_rad, p2, brg2_rad, result);
    if (!valid) return false;

    tcSensorReport* report =  &maSensorReport[0];

    tcTrack::mnID = report->mnTrackID;
    tcTrack::mfLat_rad = result.y;
    tcTrack::mfLon_rad = result.x;

    if ((report->mnFlags & TRACK_HEADING_VALID) != 0)
    {
        tcTrack::mfHeading_rad = report->mfHeading_rad;
        tcTrack::mnFlags |= TRACK_HEADING_VALID;
    }

    if ((report->mnFlags & TRACK_ALT_VALID) != 0)
    {
        tcTrack::mfAlt_m = report->mfAlt_m;
        tcTrack::mnFlags |= TRACK_ALT_VALID;
    }

    if ((report->mnFlags & TRACK_SPEED_VALID) != 0)
    {
        tcTrack::mfSpeed_kts = report->mfSpeed_kts;
        tcTrack::mnFlags |= TRACK_SPEED_VALID;
    }

    tcTrack::mfTimestamp = report->mfTimestamp;
    tcTrack::mnFlags &= ~TRACK_BEARING_ONLY;
    tcTrack::mnFlags |= TRACK_TRIANGULATED;

    errorPoly.clear();

    tcPoint p;
    valid = TriangulateBearings(p1, brg1_rad-err1_rad, p2, brg2_rad-err2_rad, p);
    if (valid) errorPoly.push_back(p);

    valid = TriangulateBearings(p1, brg1_rad-err1_rad, p2, brg2_rad+err2_rad, p);
    if (valid) errorPoly.push_back(p);

    valid = TriangulateBearings(p1, brg1_rad+err1_rad, p2, brg2_rad+err2_rad, p);
    if (valid) errorPoly.push_back(p);

    valid = TriangulateBearings(p1, brg1_rad+err1_rad, p2, brg2_rad-err2_rad, p);
    if (valid) errorPoly.push_back(p);

    ClearStale();

    //nsNav::OffsetApprox(pSensorReport->mfLat_rad, pSensorReport->mfLon_rad,
    //    mfLat_rad, mfLon_rad,
    //    pSensorReport->mfHeading_rad,C_KMTORAD*pSensorReport->rangeEstimate_km);

    //tcPoint platform(pSensorReport->mfLon_rad, pSensorReport->mfLat_rad);

    //float minRange_rad = C_KMTORAD*pSensorReport->rangeEstimate_km * pSensorReport->rangeError;
    //float maxRange_rad = C_KMTORAD*pSensorReport->rangeEstimate_km / pSensorReport->rangeError;

    //tcPoint p;

    //nsNav::OffsetApprox(platform, p, 
    //    pSensorReport->mfHeading_rad - pSensorReport->bearingError_rad,
    //    minRange_rad);
    //errorPoly.push_back(p);

    //nsNav::OffsetApprox(platform, p, 
    //    pSensorReport->mfHeading_rad - pSensorReport->bearingError_rad,
    //    maxRange_rad);
    //errorPoly.push_back(p);

    //nsNav::OffsetApprox(platform, p, 
    //    pSensorReport->mfHeading_rad + pSensorReport->bearingError_rad,
    //    maxRange_rad);
    //errorPoly.push_back(p);

    //nsNav::OffsetApprox(platform, p, 
    //    pSensorReport->mfHeading_rad + pSensorReport->bearingError_rad,
    //    minRange_rad);
    //errorPoly.push_back(p);
#endif
    return true;
}

float tcSensorMapTrack::RangeToKm(float lon_rad, float lat_rad)
{
    return C_RADTOKM * nsNav::GCDistanceApprox_rad(mfLat_rad, mfLon_rad, lat_rad, lon_rad);
}

float tcSensorMapTrack::BearingToRad(float lon_rad, float lat_rad)
{
    return nsNav::GCHeadingApprox_rad(mfLat_rad, mfLon_rad, lat_rad, lon_rad);
}


void tcSensorMapTrack::Clear()
{
    maSensorReport.clear();

    emitterInfo.clear();
	mnDatabaseID = -1;
    assessedDamage = 0;
	intercepts.clear();
	engaged.clear();
    ambiguityList.clear();
    errorPoly.clear();
    errorPolyLonWidth_rad = 0;
    errorPolyLatWidth_rad = 0;

	tcTrack::Clear();
}

/**
* @return number of contributors to this track
*/
size_t tcSensorMapTrack::GetContributorCount() const
{
    return maSensorReport.size();
}

/**
* @return name of contributing platform <idx> or pointer to "" if bad idx
*/
const char* tcSensorMapTrack::GetContributorName(unsigned idx) const
{
    static const std::string emptyString("");

    if (idx >= (unsigned)maSensorReport.size()) return emptyString.c_str();

    long contributorId = maSensorReport[idx].platformID;
    if (tcGameObject* obj = simState->GetObject(contributorId))
    {
        return obj->mzUnit.c_str();
    }
    else
    {
        return emptyString.c_str();
    }
}


unsigned tcSensorMapTrack::GetEngagedCount() const
{
    return engaged.size();
}


unsigned tcSensorMapTrack::GetInterceptCount() const
{
    return intercepts.size();
}

/**
* @return time of most recent report
* mfTimeStamp could be a coasted value, so is not accurate for staleness
*/
double tcSensorMapTrack::GetLastReportTime() const
{
	double t = -1.0f;

    size_t nContributors = maSensorReport.size();
    for (size_t n=0; n<nContributors; n++) 
    {
        const tcSensorReport* report = &maSensorReport[n];

        t = std::max(t, report->timeStamp);
	}

	return t;
}

tc3DModel* tcSensorMapTrack::GetModel() const
{
    return model;
}

float tcSensorMapTrack::GetStaleTime() const
{
    switch (mnClassification)
    {

    case PTYPE_SURFACE:
    case PTYPE_SMALLSURFACE:
    case PTYPE_LARGESURFACE:
    case PTYPE_CARRIER:
    case PTYPE_SUBSURFACE:
    case PTYPE_SUBMARINE:
        return surfaceStale;
        break;

    case PTYPE_AIR:
    case PTYPE_FIXEDWING:
    case PTYPE_HELO:
        return airStale;
        break;

    case PTYPE_MISSILE:
    case PTYPE_BALLISTIC:
        return missileStale;
        break;

    case PTYPE_GROUND:
    case PTYPE_AIRFIELD:
        return groundStale;
        break;

    case PTYPE_TORPEDO:
    case PTYPE_SONOBUOY:
        return torpedoStale;
        break;

    case PTYPE_UNKNOWN:
    default:
        return unknownStale;
        break;
    }

}

float tcSensorMapTrack::GetTrackLife() const
{
	double firstReport_s = 1e40; // start time of first contributor

    size_t nContributors = maSensorReport.size();
	for (size_t n=0; n<nContributors; n++)
	{
		firstReport_s = std::min(maSensorReport[n].startTime, firstReport_s);
	}
	return float(tcSimState::Get()->GetTime() - firstReport_s);
}


float tcSensorMapTrack::GetAgeOutTime() const
{
    switch (mnClassification)
    {

    case PTYPE_SURFACE:
    case PTYPE_SMALLSURFACE:
    case PTYPE_LARGESURFACE:
    case PTYPE_CARRIER:
    case PTYPE_SUBSURFACE:
    case PTYPE_SUBMARINE:
        return surfaceAgeOut;
        break;

    case PTYPE_AIR:
    case PTYPE_FIXEDWING:
    case PTYPE_HELO:
        return airAgeOut;
        break;

    case PTYPE_MISSILE:
    case PTYPE_BALLISTIC:
        return missileAgeOut;
        break;

    case PTYPE_GROUND:
    case PTYPE_AIRFIELD:
        return groundAgeOut;
        break;

    case PTYPE_TORPEDO:
    case PTYPE_SONOBUOY:
        return torpedoAgeOut;
        break;

    case PTYPE_UNKNOWN:
    default:
        return unknownAgeOut;
        break;
    }
}

void tcSensorMapTrack::SetModel(tc3DModel* model_)
{
	if (model)
	{
        model->Enable(false);

		// why isn't this part of tc3DModel destructor? (same issue in tcGameObject)
		model->SetSmokeMode(0);
		model->UpdateEffects(); // clear smoke particle generator
		delete model;
	}
	model = model_;
}

/**
* @return approximate radius of circle in km that bounds the error polygon, 0 if no error, 999 if bearing only
*/
float tcSensorMapTrack::TrackErrorKm() const
{
    const float maxError_km = 999.0f;

    size_t nPoints = errorPoly.size();
    bool noErrorPoly = (nPoints == 0);

    if (tcTrack::IsBearingOnly() && noErrorPoly) return maxError_km;

    if (noErrorPoly) return 0;

    wxASSERT((tcTrack::mfLon_rad >= -C_PI) && (tcTrack::mfLon_rad < C_PI));
    bool useWrappedCoords = (tcTrack::mfLon_rad > 3.0f) || (tcTrack::mfLon_rad < -3.0f);

    std::vector<tcPoint> poly = errorPoly;
    if (useWrappedCoords)
    {
        for (size_t n=0; n<nPoints; n++)
        {
            poly[n].x += C_PI;
            poly[n].x -= C_TWOPI*(poly[n].x >= C_TWOPI);
        }
    }

    // calculate centroid
    tcPoint centroid(0, 0);
    for (size_t n=0; n<nPoints; n++)
    {
        centroid.x += poly[n].x;
        centroid.y += poly[n].y;
    }
    float scale = 1.0f / float(nPoints);
    centroid.x = scale * centroid.x;
    centroid.y = scale * centroid.y;
    
    float xscale = 1.0f / cosf(centroid.x); // coarse correction for latitude
    float maxDistance_rad2 = 0;
    for (size_t n=0; n<nPoints; n++)
    {
        float dx = xscale*(poly[n].x - centroid.x);
        float dy = poly[n].y - centroid.y;
        float dist2 = dx*dx + dy*dy;
        maxDistance_rad2 = std::max(maxDistance_rad2, dist2);
    }

    float r_km = C_RADTOKM * sqrtf(maxDistance_rad2);
    return r_km;
}


/**
* This method is called periodically to cleanup the engaged vector.
* There will be some lag between the state of this vector and true
* state in the sim.
*/
void tcSensorMapTrack::UpdateEngagements()
{
    wxASSERT(simState);
    int nEngaged = (int)engaged.size();
    for (int n=nEngaged-1;n>=0;n--)
    {
        long id = engaged[n];
        tcWeaponObject *weapon = dynamic_cast<tcWeaponObject*>(simState->GetObject(id));
        if (weapon)
        {
            if (!weapon->IsIntendedTarget(tcTrack::mnID))
            {
                engaged.erase(engaged.begin() + n); // weapon isn't targeting track
            }
        }
        else // weapon doesn't exist anymore, erase engaged id
        {
            engaged.erase(engaged.begin() + n); 
        }
    }
}

/**
* This method is called periodically to cleanup the intercepts vector.
* There will be some lag between the state of this vector and true
* state in the sim.
*/
void tcSensorMapTrack::UpdateIntercepts()
{
    wxASSERT(simState);

    int nIntercepts = (int)intercepts.size();
    for (int n=nIntercepts-1;n>=0;n--)
    {
        long id = intercepts[n];
        tcPlatformObject *platform = dynamic_cast<tcPlatformObject*>(simState->GetObject(id));
        if (platform)
        {
            if (!platform->IsInterceptingTrack(tcTrack::mnID))
            {
                intercepts.erase(intercepts.begin() + n); // platform isn't intercepting track
            }
        }
        else // platform doesn't exist anymore, erase intercepts id
        {
            intercepts.erase(intercepts.begin() + n); 
        }

    }
}


bool tcSensorMapTrack::UpdateEmitter(EmitterInfo*& rpEmitterInfo, long anEmitterID) 
{
    // search for existing match
    for(size_t n=0; n<emitterInfo.size(); n++) 
    {
        EmitterInfo* pEmitterInfo = &emitterInfo[n];
        if (pEmitterInfo->mnEmitterID == anEmitterID) 
        {
            rpEmitterInfo = pEmitterInfo;
            return true;
        }
    }
    // add new emitter if there is room
    if (emitterInfo.size() < MAX_EMITTERS) 
    {
        EmitterInfo temp;
        temp.mnEmitterID = anEmitterID;
        temp.mfTimestamp = 0;
        temp.mnMode = 0;

        emitterInfo.push_back(temp);

        rpEmitterInfo = &emitterInfo[emitterInfo.size()-1];


        UpdateAmbiguityList();
        return true;
    }
    return false;
}

/**
* Remove emitters that are no longer active
*/
void tcSensorMapTrack::UpdateEmitters()
{
    if (emitterInfo.size() == 0) return;

    tcSensorPlatform* sensorPlatform = dynamic_cast<tcSensorPlatform*>(GetAssociated());

    if (sensorPlatform == 0) // associated obj is either destroyed (possible) or was not a sensor platform (error)
    {
        emitterInfo.clear();
        return;
    }

    std::vector<EmitterInfo> temp;

    // iterate through emitters, keep only the active emitters
    size_t nEmitters = emitterInfo.size();

    for (size_t n=0; n<nEmitters; n++)
    {
        long emitterID = emitterInfo[n].mnEmitterID; // database id of emitter sensor
        const tcSensorState* sensor = sensorPlatform->GetSensorByDatabaseID(emitterID);
        if ((sensor != 0) && sensor->IsActive())
        {
            temp.push_back(emitterInfo[n]);
        }
    }

    emitterInfo = temp;
}

/**
* @return pointer to matching report if exists, otherwise create one and return pointer, return 0 if no room due to contributor limit
*/
tcSensorReport* tcSensorMapTrack::GetOrCreateReport(long platformID, long sensorID)
{
    size_t nContributors = maSensorReport.size();
    for (size_t n=0; n<nContributors; n++)
    {
        tcSensorReport* sensorReport = &maSensorReport[n];

        if ((sensorReport->platformID == platformID) && (sensorReport->sensorID == sensorID))
        {
            return sensorReport;
        }
    }

    if (nContributors < MAX_SENSOR_REPORTS)
    {
        tcSensorReport newReport;
        newReport.platformID = platformID;
        newReport.sensorID = sensorID;
        maSensorReport.push_back(newReport);

        return &maSensorReport.back();
    }
    else
    {
        return 0;
    }
}



/**
* Using database, updates ambiguity list of platforms
* consistent with detected emitters
*/
void tcSensorMapTrack::UpdateAmbiguityList()
{
	ambiguityList.clear();

	// return if coarse classification is not available
	if ((mnClassification == PTYPE_UNKNOWN)||(mnDatabaseID != -1)) return;

    size_t nEmitters = emitterInfo.size();
	if (nEmitters == 0) return;

	std::vector<long> emitterList;
	for (size_t n=0; n<nEmitters; n++)
	{
		emitterList.push_back(emitterInfo[n].mnEmitterID);
	}

	tcDatabaseIterator iter(mnClassification);
	for (iter.First(); !iter.IsDone(); iter.Next())
	{
		bool platformMatches = false;
		tcDatabaseObject* obj = iter.Get();
		wxASSERT(obj);
		if (tcPlatformDBObject* generic = dynamic_cast<tcPlatformDBObject*>(obj))
		{
			if (generic->HasAllEmitters(emitterList)) platformMatches = true;
		}
		else if (tcMissileDBObject* missile = dynamic_cast<tcMissileDBObject*>(obj))
		{
			if (missile->HasAllEmitters(emitterList)) platformMatches = true;
		}

		if (platformMatches)
		{
			ambiguityList.push_back(obj->mnKey);
		}
		
	}

	/* use esm ambiguity list for identification if platform not
	** identified, and there is exactly one entry in ambiguity list */
	if ((ambiguityList.size() == 1) && (mnDatabaseID == -1))
	{
		IdentifyTrack(ambiguityList[0]);
	}

	ambiguityListUpdates++;
}



void tcSensorMapTrack::UpdateClassification(UINT16 mnClassification) 
{
    UINT16 startClassification = tcTrack::mnClassification;

    tcTrack::mnClassification |= mnClassification;

    // update generic model if classification has changed
    if ((mnDatabaseID == -1) && (tcTrack::mnClassification != startClassification))
    {
        UpdateGenericModel();
    }

}


void tcSensorMapTrack::UpdateGenericModel()
{
    if (model != 0)
    {
        model->SetGenericMesh(tcTrack::mnClassification);
    }
    else
    {
        model = new tc3DModel();
        model->SetGenericMesh(tcTrack::mnClassification);
    }
}


/**
* check if reporting sensor has reported, if so update report
* if not add new report if slots are free
*/
bool tcSensorMapTrack::AddReport(const tcSensorReport& report) 
{
    size_t nContributors = maSensorReport.size();

    // search for existing match
    for(size_t n=0; n<nContributors; n++) 
    {
        tcSensorReport *pSensorReport = &maSensorReport[n];
        //bool bActivePassiveMatch = (pSensorReport->mnFlags & report.mnFlags & TRACK_BEARING_ONLY);
        if ((pSensorReport->platformID == report.platformID) &&
            (pSensorReport->sensorID == report.sensorID)) 
        {
            *pSensorReport = report;
            return true;
        }
    }

    // add new report if there is room
    if (nContributors < MAX_SENSOR_REPORTS) 
    {
        maSensorReport.push_back(report);
        return true;
    }

    // no room
    return false;
}

/**
* Queries simState to check if track object exists. If
* not the track is marked as destroyed.
* This assumes that the track id matches the simState object
* id. This assumption will be invalid someday once the two
* sets of ids are decoupled.
* TODO repair for this
*/
void tcSensorMapTrack::KillAssess()
{
    tcGameObject* obj = simState->GetObject(mnID);
    if (obj == 0)
    {
        MarkDestroyed();
#ifdef _DEBUG
        fprintf(stdout, "Track %d marked destroyed\n", mnID);
#endif
    }
}

/**
* Do updates for always visible tracks so they remain in map
*/
void tcSensorMapTrack::UpdateAlwaysVisible()
{
    if (!alwaysVisible) return;

    double t = simState->GetTime();
    if ((t - tcTrack::mfTimestamp) > 25.0)
    {
        tcTrack::mfTimestamp = t - 1.0;
        wxASSERT(mnID >= 0);
    }
}

/**
* @param linearTime_s time in seconds to assume linear track behavior
* @param defaultSpeed_mps default speed to assume for this class of track
* @param defaultClimbAngle_rad climb angle to assume for alt error when no better data
*/
void tcSensorMapTrack::GetModelParameters(float& linearTime_s, float& defaultSpeed_mps, float& defaultClimbAngle_rad,
                                          float& accel_mps2, float& climbRate_radps, float& headingRate_radps)
{
    linearTime_s = 0;
    defaultSpeed_mps = 0;
    defaultClimbAngle_rad = 0;
    accel_mps2 = 0;
    climbRate_radps = 0; // rate of climb angle
    headingRate_radps = 0;

    switch (tcTrack::mnClassification)
    {
        case PTYPE_UNKNOWN:
            linearTime_s = 10.0f;
            defaultSpeed_mps = 20.0f;
            defaultClimbAngle_rad = C_PIOVER180 * 10.0f;
            accel_mps2 = 1.0f;
            climbRate_radps = C_PIOVER180 * 2.0f;
            headingRate_radps = C_PIOVER180 * 5.0f;
            break;
        case PTYPE_SURFACE:
        case PTYPE_SMALLSURFACE:
        case PTYPE_LARGESURFACE:
        case PTYPE_CARRIER:
            linearTime_s = 20.0f;
            defaultSpeed_mps = 5.0f;
            accel_mps2 = 0.25f;
            headingRate_radps = C_PIOVER180 * 2.0f;
            break;
        case PTYPE_AIR:
        case PTYPE_FIXEDWING:
            linearTime_s = 5.0f;
            defaultSpeed_mps = 150.0f;
            defaultClimbAngle_rad = C_PIOVER180 * 10.0f;
            accel_mps2 = 10.0f;
            climbRate_radps = C_PIOVER180 * 1.0f;
            headingRate_radps = C_PIOVER180 * 5.0f;
            break;
        case PTYPE_HELO:
            linearTime_s = 5.0f;
            defaultSpeed_mps = 50.0f;
            defaultClimbAngle_rad = C_PIOVER180 * 10.0f;
            accel_mps2 = 5.0f;
            climbRate_radps = C_PIOVER180 * 1.0f;
            headingRate_radps = C_PIOVER180 * 5.0f;
            break;
        case PTYPE_AIRCM:
        case PTYPE_MISSILE:
            linearTime_s = 2.0f;
            defaultSpeed_mps = 300.0f;
            defaultClimbAngle_rad = C_PIOVER180 * 20.0f;
            accel_mps2 = 15.0f;
            climbRate_radps = C_PIOVER180 * 3.0f;
            headingRate_radps = C_PIOVER180 * 8.0f;
            break;
        case PTYPE_SUBSURFACE:
        case PTYPE_SUBMARINE:
            linearTime_s = 60.0f;
            defaultSpeed_mps = 3.0f;
            defaultClimbAngle_rad = C_PIOVER180 * 10.0f;
            accel_mps2 = 0.125f;
            climbRate_radps = C_PIOVER180 * 1.0f;
            headingRate_radps = C_PIOVER180 * 1.0f;
            break;
        case PTYPE_TORPEDO:
            linearTime_s = 5.0f;
            defaultSpeed_mps = 20.0f;
            defaultClimbAngle_rad = C_PIOVER180 * 10.0f;
            accel_mps2 = 1.0f;
            climbRate_radps = C_PIOVER180 * 3.0f;
            headingRate_radps = C_PIOVER180 * 3.0f;
            break;
        case PTYPE_SONOBUOY:
        case PTYPE_WATERCM:
        case PTYPE_WATERMINE:
            linearTime_s = 2.0f;
            defaultSpeed_mps = 0.25f;
            accel_mps2 = 0.125f;
            climbRate_radps = C_PIOVER180 * 0.5f;
            headingRate_radps = C_PIOVER180 * 1.0f;
            break;
        case PTYPE_GROUND:
            linearTime_s = 15.0f;
            defaultSpeed_mps = 5.0f;
            accel_mps2 = 1.0f;
            headingRate_radps = C_PIOVER180 * 2.0f;
            break;
        case PTYPE_AIRFIELD:
            linearTime_s = 9999.0f;
            defaultSpeed_mps = 0;
            break;
        case PTYPE_GROUNDVEHICLE:
            linearTime_s = 15;
            defaultSpeed_mps = 5.0f;
            accel_mps2 = 1.0f;
            headingRate_radps = C_PIOVER180 * 2.0f;
            break;
        case PTYPE_BALLISTIC:
            linearTime_s = 3.0f;
            defaultSpeed_mps = 100.0f;
            defaultClimbAngle_rad = C_PIOVER180 * 30.0f;
            accel_mps2 = 5.0f;
            climbRate_radps = C_PIOVER180 * 5.0f;
            headingRate_radps = C_PIOVER180 * 5.0f;
            break;
        default:
            linearTime_s = 10.0f;
            defaultSpeed_mps = 20.0f;
            accel_mps2 = 1.0f;
            climbRate_radps = C_PIOVER180 * 5.0f;
            headingRate_radps = C_PIOVER180 * 5.0f;
            wxASSERT(false);
            break;
    }
}

void tcSensorMapTrack::PredictReport(double t, const tcSensorReport& base, tcSensorReport& prediction)
{
    double dt_s = t - base.timeStamp;
    wxASSERT(dt_s >= 0); // prediction should be into future

    prediction = base;

    bool isFixedGround = tcTrack::IsGround() && tcTrack::IsSpeedValid() && (tcTrack::mfSpeed_kts == 0);
    if ((dt_s <= 0) || isFixedGround) return; // no prediction required

    float trackLinearTime_s = 0;
    float defaultSpeed_mps = 0;
    float defaultClimbAngle_rad = 0;
    float accel_mps2 = 0;
    float climbRate_radps = 0; // rate of climb angle
    float headingRate_radps = 0;
    GetModelParameters(trackLinearTime_s, defaultSpeed_mps, defaultClimbAngle_rad, 
                       accel_mps2, climbRate_radps, headingRate_radps);

    // use mixture of report linear track and random movement
    bool reportLonLatValid = (base.validFlags & tcSensorReport::LONLAT_VALID) != 0;
    bool reportHeadingValid = (base.validFlags & tcSensorReport::HEADING_VALID) != 0;
    bool reportSpeedValid = (base.validFlags & tcSensorReport::SPEED_VALID) != 0;
    bool reportAltValid = (base.validFlags & tcSensorReport::ALT_VALID) != 0;
    bool reportClimbValid = (base.validFlags & tcSensorReport::CLIMB_VALID) != 0;

    if (!reportHeadingValid) trackLinearTime_s = 0;

    float speed_mps = reportSpeedValid ? base.speedEstimate_mps : defaultSpeed_mps;
    float speed_radps = C_MTORAD * speed_mps;
    float invcos_factor = (1.0 / cosf(base.latEstimate_rad));

    if (reportLonLatValid)
    {
        if (dt_s <= trackLinearTime_s)
        {
            float dist_rad = speed_radps * dt_s;
            prediction.lonEstimate_rad += invcos_factor * dist_rad * sinf(base.headingEstimate_rad);
            prediction.latEstimate_rad += dist_rad * cosf(base.headingEstimate_rad);
        }
        else
        {
            float dist_rad = speed_radps * trackLinearTime_s;
            prediction.lonEstimate_rad += invcos_factor * dist_rad * sinf(base.headingEstimate_rad);
            prediction.latEstimate_rad += dist_rad * cosf(base.headingEstimate_rad);

            float errorTime_s = dt_s - trackLinearTime_s;
            float errorSigma_rad = 0.5f * speed_radps * errorTime_s; // take speed as a 2-sigma number
            float errorVar_rad2 = errorSigma_rad * errorSigma_rad;
            prediction.C11 += invcos_factor * errorVar_rad2; // lon component
            prediction.C22 += errorVar_rad2; // lat component
        }
    }

    // update altitude prediction
    if (reportAltValid)
    {
        if (reportClimbValid)
        {
            prediction.altEstimate_m += sinf(base.climbEstimate_rad) * speed_mps * std::min((float)dt_s, trackLinearTime_s);
        }
        float altitudeError_m = 0.5f * sinf(defaultClimbAngle_rad) * speed_mps * dt_s; // 0.5 for 2-sigma
        prediction.altVariance += altitudeError_m * altitudeError_m;
        prediction.altVariance = std::min(prediction.altVariance, 4e6f); // max 1-sigma of 2000 m
    }

    // update speed prediction
    if (reportSpeedValid)
    {
        float speedError_mps = 0.5 * accel_mps2 * dt_s;
        prediction.speedVariance += speedError_mps * speedError_mps;
        if (dt_s > 30.0f)
        {
            prediction.speedEstimate_mps = 0;
        }
    }

    // update heading prediction
    if (reportHeadingValid)
    {
        float headingError_rad = 0.5 * headingRate_radps * dt_s;
        prediction.headingVariance += headingError_rad * headingError_rad;
    }

    // update climbAngle prediction
    if (reportClimbValid)
    {
        float climbAngleError_rad = 0.5 * climbRate_radps * dt_s;
        prediction.climbVariance += climbAngleError_rad * climbAngleError_rad;
    }
}

void tcSensorMapTrack::SetAffiliation(tcAllianceInfo::Affiliation affil)
{
    if (tcTrack::mnAffiliation == 0)
    {
        tcTrack::mnAffiliation = affil;
    }
}

/**
* @param tCoast_s time to predict to, if later than most recent report time
* check for update reports and update track
*/
void tcSensorMapTrack::UpdateTrack(double tCoast_s) 
{
    UpdateAlwaysVisible();

    if (simState->IsMultiplayerClient() || IsDestroyed()) return;

    UpdateEmitters();

    PruneReports();

    double mostRecentReportTime_s = 0;
    size_t nContributors = maSensorReport.size();
    for (size_t n=0; n<nContributors; n++)
    {
        tcSensorReport* report = &maSensorReport[n];
        mostRecentReportTime_s = std::max(report->timeStamp, mostRecentReportTime_s);
    }

    if ((mostRecentReportTime_s <= tcTrack::mfTimestamp) && (tCoast_s <= tcTrack::mfTimestamp)) return; // no update required

    double invC11sum = 0;
    double invC22sum = 0;
    double invC12sum = 0;
    double lon_estimate = 0;
    double lat_estimate = 0;
    unsigned int nLatLonReports = 0;

    float invAltVarSum = 0;
    float alt_estimate = 0;
    unsigned int nAltReports = 0;

    float invSpeedVarSum = 0;
    float speed_estimate = 0;
    unsigned int nSpeedReports = 0;

    float invHeadingVarSum = 0;
    float heading_estimate = 0;
    unsigned int nHeadingReports = 0;

    float invClimbVarSum = 0;
    float climb_estimate = 0;
    unsigned int nClimbReports = 0;

    double tPredict_s = std::max(mostRecentReportTime_s, tCoast_s);
    const double min_det = 1e-32;

    tcSensorReport predicted;
    for (size_t n=0; n<nContributors; n++)
    {
        tcSensorReport* report = &maSensorReport[n];

        PredictReport(tPredict_s, *report, predicted);

        // update combined estimate for each contributor with valid lat/lon
        if ((report->validFlags & tcSensorReport::LONLAT_VALID) != 0)
        {
            double det = (predicted.C11*predicted.C22) - (predicted.C12*predicted.C12);
            wxASSERT(det > -1e-30);
            det = std::max(det, min_det);

            double inv_det = 1.0 / det;
            double invC11 = inv_det * (double)predicted.C22;
            double invC22 = inv_det * (double)predicted.C11;
            double invC12 = inv_det * (double)-predicted.C12;

            lon_estimate += invC11 * predicted.lonEstimate_rad + invC12 * predicted.latEstimate_rad;
            lat_estimate += invC12 * predicted.lonEstimate_rad + invC22 * predicted.latEstimate_rad;
            invC11sum += invC11;
            invC22sum += invC22;
            invC12sum += invC12;

            nLatLonReports++;
        }

        // update alt
        if ((report->validFlags & tcSensorReport::ALT_VALID) != 0)
        {
            float inv_alt_variance = 1.0f / predicted.altVariance;
            alt_estimate += inv_alt_variance * predicted.altEstimate_m;
            invAltVarSum += inv_alt_variance;
            nAltReports++;

            wxASSERT(predicted.altEstimate_m >= 0);
        }

        // update speed
        if ((report->validFlags & tcSensorReport::SPEED_VALID) != 0)
        {
            float inv_speed_variance = 1.0f / predicted.speedVariance;
            speed_estimate += inv_speed_variance * predicted.speedEstimate_mps;
            invSpeedVarSum += inv_speed_variance;
            nSpeedReports++;
        }

        // update heading
        if ((report->validFlags & tcSensorReport::HEADING_VALID) != 0)
        {
            float inv_heading_variance = 1.0f / predicted.headingVariance;
            heading_estimate += inv_heading_variance * predicted.headingEstimate_rad; // TO-DO need to handle wrapped heading
            invHeadingVarSum += inv_heading_variance;
            nHeadingReports++;
        }

        // update climb
        if ((report->validFlags & tcSensorReport::CLIMB_VALID) != 0)
        {
            float inv_climb_variance = 1.0f / predicted.climbVariance;
            climb_estimate += inv_climb_variance * predicted.climbEstimate_rad;
            invClimbVarSum += inv_climb_variance;
            nClimbReports++;
        }

        if (report->timeStamp > tcTrack::mfTimestamp)
        {
            UpdateClassification(report->classification);

            if ((mnDatabaseID == -1) && (report->databaseID != -1))
            {
                IdentifyTrack(report->databaseID);

            }

			if ((tcTrack::mnAffiliation == tcAllianceInfo::UNKNOWN) && (report->alliance != 0))
			{
				tcGameObject* reporter = simState->GetObject(report->platformID);
				if (reporter != 0)
				{
					tcTrack::mnAffiliation = reporter->GetAffiliationWith(report->alliance);
				}
			}

            if (IsMissile() && (tcTrack::mnAffiliation == tcAllianceInfo::UNKNOWN))
            {
                tcTrack::mnAffiliation = tcAllianceInfo::HOSTILE;
            }

            // may need to limit rate of these updates, looks potentially expensive
            size_t nEmittersReported = report->emitterList.size();
            for (size_t k=0; k<nEmittersReported; k++)
            {
                long emitter_id = report->emitterList[k];
                bool searching = true;
                for (size_t idx=0; (idx<emitterInfo.size())&&(searching); idx++)
                {
                    if (emitterInfo[idx].mnEmitterID == emitter_id)
                    {
                        searching = false;
                        emitterInfo[idx].mfTimestamp = report->timeStamp;
                    }
                }
                if (searching)
                {
                    EmitterInfo em;
                    em.mnEmitterID = emitter_id;
                    em.mfTimestamp = report->timeStamp;
                    em.mnMode = 0;
                    emitterInfo.push_back(em);
                }
            }

            UpdateAmbiguityList();
        }
    }

    tcTrack::mfTimestamp = tPredict_s;

    if (nLatLonReports > 0)
    {
        double det_sum = (invC11sum * invC22sum) - (invC12sum * invC12sum);
        wxASSERT(det_sum > 0);
        double inv_det_sum = 1.0 / det_sum;
        double C11sum = inv_det_sum * invC22sum;
        double C22sum = inv_det_sum * invC11sum;
        double C12sum = inv_det_sum * -invC12sum;

        // combined estimate
        tcTrack::mfLon_rad = float(C11sum * lon_estimate + C12sum * lat_estimate);
        tcTrack::mfLat_rad = float(C12sum * lon_estimate + C22sum * lat_estimate);

        tcTrack::mnFlags |= TRACK_ACTIVE;
        ClearStale(); // why do this here?

        // update error poly
        errorPoly.clear();
        
        float cos_lat = cosf(tcTrack::mfLat_rad);
        float inv_cos_lat = 1.0f / cos_lat;

        float C11sumb = C11sum*cos_lat*cos_lat;
        float C12sumb = C12sum*cos_lat;

        float C22mC11 = C22sum - C11sumb;
        float C22pC11 = C22sum + C11sumb;
        float theta_rad = 0.5f * atan2f(2.0f*C12sumb, C22mC11);
        float det_term = sqrtf((C22mC11*C22mC11) + 4.0f*C12sumb*C12sumb);
        float dmaj = sqrtf(1.5f * (C22pC11 - det_term)); // 3 x 1-sigma major axis
        float dmin = sqrtf(1.5f * (C22pC11 + det_term)); // 3 x 1-sigma minor axis

        float cos_theta = cosf(theta_rad);
        float sin_theta = sinf(theta_rad);
        float dx1_rad = inv_cos_lat*sin_theta*dmin;
        float dy1_rad = cos_theta*dmin;
        float dx2_rad = inv_cos_lat*cos_theta*dmaj;
        float dy2_rad = -sin_theta*dmaj;

        float x1 = mfLon_rad + dx1_rad;
        float x2 = mfLon_rad + dx2_rad;
        float x3 = mfLon_rad - dx1_rad;
        float x4 = mfLon_rad - dx2_rad;

        float y1 = mfLat_rad + dy1_rad;
        float y2 = mfLat_rad + dy2_rad;
        float y3 = mfLat_rad - dy1_rad;
        float y4 = mfLat_rad - dy2_rad;


        errorPoly.push_back(tcPoint(x1, y1));
        errorPoly.push_back(tcPoint(x2, y2));
        errorPoly.push_back(tcPoint(x3, y3));
        errorPoly.push_back(tcPoint(x4, y4));
        errorPoly.push_back(tcPoint(x1, y1));

        UpdateErrorPolyWidth();
    }

    if (nAltReports > 0)
    {
        float altVariance = 1.0f / invAltVarSum;
        tcTrack::mfAlt_m = altVariance * alt_estimate;
        tcTrack::mnFlags |= TRACK_ALT_VALID;
    }
    else
    {
        tcTrack::mnFlags &= ~TRACK_ALT_VALID;
    }

    if (nSpeedReports > 0)
    {
        float speedVariance = 1.0f / invSpeedVarSum;
        tcTrack::mfSpeed_kts = C_MPSTOKTS * speedVariance * speed_estimate;
        tcTrack::mnFlags |= TRACK_SPEED_VALID;
    }
    else
    {
        tcTrack::mnFlags &= ~TRACK_SPEED_VALID;
    }

    if (nHeadingReports > 0)
    {
        float headingVariance = 1.0f / invHeadingVarSum;
        tcTrack::mfHeading_rad = headingVariance * heading_estimate;
        tcTrack::mnFlags |= TRACK_HEADING_VALID;
    }
    else
    {
        tcTrack::mnFlags &= ~TRACK_HEADING_VALID;
    }

    if (nClimbReports > 0)
    {
        float climbVariance = 1.0f / invClimbVarSum;
        tcTrack::mfClimbAngle_rad = climbVariance * climb_estimate;
        tcTrack::mnFlags |= TRACK_CLIMB_VALID;
    }
    else
    {
        tcTrack::mnFlags &= ~TRACK_CLIMB_VALID;
    }

    wxASSERT(mnID >= 0);

	if (autoKillAssess)
	{
		if (!IsNew() && !IsDestroyed())
		{
			KillAssess();
		}
	}
}


/**
* If we exceeded GOAL_SENSOR_REPORTS, then remove least valuable reports
*/
void tcSensorMapTrack::PruneReports()
{
    size_t nContributors = maSensorReport.size();
    if (nContributors <= (GOAL_SENSOR_REPORTS + 3))
    {
        return;
    }

    // keep the following and remove oldest of remaining to get back to GOAL_SENSOR_REPORTS:
    // (1) Best lat/lon estimate
    // (2) Best altitude estimate

    std::vector<SensorReportInfo> infoVect;
    SensorReportInfo ri;

    float bestArea = 1e20f;
    size_t bestAreaIdx = 99999;
    float nextBestArea = 1e20f;
    size_t nextBestAreaIdx = 99999;
    float bestAltitudeVar = 1e20f;
    size_t bestAltitudeIdx = 99999;
    
    for (size_t n=0; n<nContributors; n++)
    {
        tcSensorReport& report = maSensorReport[n];

        ri.index = n;
        ri.time_s = report.timeStamp;
        ri.lonlatUncertainty = report.UncertaintyArea();
        ri.altVariance = report.altVariance;

        infoVect.push_back(ri);

        if (ri.lonlatUncertainty < bestArea)
        {
            nextBestArea = bestArea;
            nextBestAreaIdx = bestAreaIdx;
            bestArea = ri.lonlatUncertainty;
            bestAreaIdx = n;
        }
        else if (ri.lonlatUncertainty < nextBestArea)
        {
            nextBestArea = ri.lonlatUncertainty;
            nextBestAreaIdx = n;
        }
        if (ri.altVariance < bestAltitudeVar)
        {
            bestAltitudeVar = ri.altVariance;
            bestAltitudeIdx = n;
        }
    }

    // sort in descending order of time, first item is oldest report
    std::sort(infoVect.begin(), infoVect.end(), SensorReportSortPredicate);

    std::vector<size_t> indexToDelete;
    size_t nDelete = nContributors - GOAL_SENSOR_REPORTS;
      
    size_t n = 0;
    while ((n<nContributors) && (indexToDelete.size() < nDelete))
    {
        size_t index_n = infoVect[n].index;
        if ((index_n != bestAreaIdx) && (index_n != nextBestAreaIdx) && (index_n != bestAltitudeIdx))
        {
            indexToDelete.push_back(index_n);
        }
        n++;
    }

    std::deque<tcSensorReport> prunedReports;

    for (size_t n=0; n<nContributors; n++)
    {
        bool keep = true;
        for (size_t k=0; (k<indexToDelete.size()) && keep; k++)
        {
            keep = keep && (n != indexToDelete[k]);
        }
        if (keep)
        {
            prunedReports.push_back(maSensorReport[n]);
        }
    }

    maSensorReport = prunedReports;

    wxASSERT(maSensorReport.size() == GOAL_SENSOR_REPORTS);
}

/**
* Updates main track with passive report data. Should call only when
* there are no active reports.
*/
void tcSensorMapTrack::UpdateTrackWithPassive()
{   
    wxASSERT(false);
#if 0 // obsolete 26 AUG 2011
    wxASSERT(MAX_SENSOR_REPORTS == 2); // need to update code if more than 2

    bool triangulated = AttemptPassiveTriangulation();

    if (triangulated) return;

    // if there is only one passive contributor and its timestamp is new, then use that
    // if there is more than one passive contributor, and at least one has a new timestamp, then arbitrate for the best contributor

    int updateReportIdx = -1;
    size_t nPassive = 0;
    int newContributorIdx = -1;

    for (int n=0;n<mnContributors;n++) 
    {
        tcSensorReport* sensorReport = &maSensorReport[n];

        bool isPassiveReport = (sensorReport->mnFlags & (TRACK_BEARING_ONLY | TRACK_TRIANGULATED)) != 0;
        bool isNewReport = (sensorReport->mfTimestamp > tcTrack::mfTimestamp);

        nPassive = nPassive + int(isPassiveReport); // true gets converted to int(1)
        if (isNewReport && isPassiveReport)
        {
            newContributorIdx = n;
        }
    }

    if (newContributorIdx == -1)
    {
        return;
    }
    
	ClearStale();

	if ((newContributorIdx != -1) && (nPassive == 1))
    {
        updateReportIdx = newContributorIdx;
    }
    else
    {
        wxASSERT(newContributorIdx != -1);
        wxASSERT(nPassive == 2);
        wxASSERT(mnContributors == 2);

        // compare new report to other report to check if new report should be used for position update
        int otherContributorIdx = (newContributorIdx == 0) ? 1 : 0;

        tcSensorReport* otherReport = &maSensorReport[otherContributorIdx];
        tcSensorReport* newReport = &maSensorReport[newContributorIdx];


        bool moreAccurate = ((newReport->rangeError > 0) && (otherReport->rangeError == 0)) ||
            ((newReport->rangeError > 0) && 
            ((newReport->rangeError * newReport->rangeEstimate_km) < (otherReport->rangeError * otherReport->rangeEstimate_km))
            );
        bool moreCurrent = (newReport->mfTimestamp > (otherReport->mfTimestamp + 60.0f)); // prefer recent over "stale" report
        bool slowMover = ((mnClassification & PTYPE_GROUND) != 0) ||
            ((mnClassification & PTYPE_SURFACE) != 0) ||
            (mnClassification == PTYPE_SUBMARINE);


        if (moreAccurate || (moreCurrent && !slowMover))
        {
            updateReportIdx = newContributorIdx;
        }
        else
        {
            updateReportIdx = -1;
        }
    }


    if (updateReportIdx < 0) return; // no updates to process


    float updateSpeed_kts = 0;
    float speedUpdateTime = -999.0f;

    float updateHeading_rad = 0;
    float headingUpdateTime = -999.0f;

    float updateAlt_m = -999.0f;
    float altUpdateTime = -999.0f;

    // iterate through contributors to get latest speed, alt, and heading
    for (int n=0;n<mnContributors;n++) 
    {
        tcSensorReport* sensorReport = &maSensorReport[n];

        bool speedValid = (sensorReport->mnFlags & TRACK_SPEED_VALID) != 0;
        bool headingValid = (sensorReport->mnFlags & TRACK_HEADING_VALID) != 0;
        bool altValid = (sensorReport->mnFlags & TRACK_ALT_VALID) != 0;

        if (speedValid && (sensorReport->mfTimestamp > speedUpdateTime))
        {
            updateSpeed_kts = sensorReport->mfSpeed_kts;
            speedUpdateTime = sensorReport->mfTimestamp;
        }

        if (headingValid && (sensorReport->mfTimestamp > headingUpdateTime))
        {
            updateHeading_rad = sensorReport->mfHeading_rad;
            headingUpdateTime = sensorReport->mfTimestamp;
        }

        if (altValid && (sensorReport->mfTimestamp > altUpdateTime))
        {
            updateAlt_m = sensorReport->mfAlt_m;
            altUpdateTime = sensorReport->mfTimestamp;
        }
    }

    // update track with new update report
    wxASSERT((updateReportIdx >= 0) && (updateReportIdx < mnContributors));
    tcSensorReport* updateReport = &maSensorReport[updateReportIdx];

    tcTrack::mnID = updateReport->mnTrackID;
    tcTrack::mfLat_rad = updateReport->mfLat_rad;
    tcTrack::mfLon_rad = updateReport->mfLon_rad;
    tcTrack::bearing_rad = updateReport->bearingEstimate_rad;
	tcTrack::bearingRate_radps = updateReport->bearingRateEstimate_radps;

    tcTrack::mfTimestamp = updateReport->mfTimestamp;
    tcTrack::mnFlags = updateReport->mnFlags;
    wxASSERT(mnID >= 0);

    if (speedUpdateTime >= 0)
    {
        tcTrack::mfSpeed_kts = updateSpeed_kts;
        tcTrack::mnFlags |= TRACK_SPEED_VALID;
    }

    if (headingUpdateTime >= 0)
    {
        tcTrack::mfHeading_rad = updateHeading_rad;
        tcTrack::mnFlags |= TRACK_HEADING_VALID;
    }

    if (altUpdateTime >= 0)
    {
        tcTrack::mfAlt_m = updateAlt_m;
        tcTrack::mnFlags |= TRACK_ALT_VALID;
    }

    float rangeEstimate_km = updateReport->rangeEstimate_km;
    float rangeError = updateReport->rangeError;
    float bearingError_rad = updateReport->bearingError_rad;

     
    if (rangeEstimate_km > 0) 
    {
        errorPoly.clear();
        
        float platformLat_rad = mfLat_rad;
        float platformLon_rad = mfLon_rad;
        nsNav::OffsetApprox(platformLat_rad, platformLon_rad,
            mfLat_rad, mfLon_rad,
            tcTrack::bearing_rad, C_KMTORAD*rangeEstimate_km);

        tcPoint platform(platformLon_rad, platformLat_rad);

        float rangeScaleError = 1.0f - rangeError;

        wxASSERT((rangeScaleError > 0.0f)&&(rangeScaleError <= 1.0f));
        float minRange_rad = (C_KMTORAD*rangeEstimate_km) * rangeScaleError;
        float maxRange_rad = (C_KMTORAD*rangeEstimate_km) / rangeScaleError;

        tcPoint p;

        nsNav::OffsetApprox(platform, p, 
            tcTrack::bearing_rad - bearingError_rad,
            minRange_rad);
        errorPoly.push_back(p);

        nsNav::OffsetApprox(platform, p, 
            tcTrack::bearing_rad - bearingError_rad,
            maxRange_rad);
        errorPoly.push_back(p);

        nsNav::OffsetApprox(platform, p, 
            tcTrack::bearing_rad + bearingError_rad,
            maxRange_rad);
        errorPoly.push_back(p);

        nsNav::OffsetApprox(platform, p, 
            tcTrack::bearing_rad + bearingError_rad,
            minRange_rad);
        errorPoly.push_back(p);

    }
    else
    {
        errorPoly.clear();
    }
#endif
    return;
}

void tcSensorMapTrack::ValidateTrack()
{
#ifdef _DEBUG
    if (errorPoly.size() > 0)
    {
        float minLon_rad = 999.0f;
        for (size_t k=0; k<errorPoly.size(); k++)
        {
            if (errorPoly[k].x < minLon_rad) minLon_rad = errorPoly[k].x;
        }
        wxASSERT(mfLon_rad > minLon_rad);
    }
#endif
}


void tcSensorMapTrack::RemoveReports(const std::vector<size_t>& reportsToRemove)
{
    std::deque<tcSensorReport> tempReports;

    size_t nReports = maSensorReport.size();
    for (size_t n=0; n<nReports; n++)
    {
        bool keep = true;
        for (size_t k=0; (k<reportsToRemove.size())&&(keep); k++)
        {
            if (reportsToRemove[k] == n) 
            {
                keep = false;
            }
        }
        if (keep)
        {
            tempReports.push_back(maSensorReport[n]);
        }
    }

    maSensorReport = tempReports;
}

/**
* remove report n and shift other reports to fill array from beginning
*/
void tcSensorMapTrack::RemoveReport(size_t n) 
{
    maSensorReport.erase(maSensorReport.begin() + n);

    //// update flags based on remaining contributors
    //UINT8 currentFlags = 0;
    //for (int n=0; n<mnContributors; n++)
    //{
    //    currentFlags |= maSensorReport[n].mnFlags;
    //}

    //const UINT8 ACTIVE_MASK = TRACK_ACTIVE | TRACK_HEADING_VALID | TRACK_CLIMB_VALID |
    //                          TRACK_SPEED_VALID | TRACK_ALT_VALID;
    //const UINT8 PASSIVE_MASK = TRACK_BEARING_ONLY | TRACK_TRIANGULATED |
    //                           TRACK_BEARINGRATE_VALID;

    //if ((currentFlags & TRACK_ACTIVE) != 0)
    //{
    //    tcTrack::mnFlags = currentFlags & ACTIVE_MASK;
    //}
    //else
    //{
    //    tcTrack::mnFlags = currentFlags & PASSIVE_MASK;
    //}

}

/**
* @return tcGameObject that is associated with this track
* Currently this relies on track id matching game obj id
*/
tcGameObject* tcSensorMapTrack::GetAssociated()
{
    tcGameObject* obj = simState->GetObject(tcTrack::mnID);

    return obj;
}
 
/**
* @return tcGameObject that is associated with this track
* Currently this relies on track id matching game obj id
*/
const tcGameObject* tcSensorMapTrack::GetAssociatedConst() const
{
    const tcGameObject* obj = simState->GetObjectConst(tcTrack::mnID);

    return obj;
}


/**
* @returns database id of track or -1 if not identified
*/
long tcSensorMapTrack::GetDatabaseId() const
{
	return mnDatabaseID;
}


size_t tcSensorMapTrack::GetEmitterCount() const
{
    return emitterInfo.size();
}

const EmitterInfo* tcSensorMapTrack::GetEmitter(unsigned idx) 
{
    if (idx < emitterInfo.size())
    {
        return &emitterInfo[idx];
    }
    else
    {
        return 0;
    }
}

EmitterInfo tcSensorMapTrack::GetEmitterInfo(unsigned idx)
{
	EmitterInfo errorInfo;
	errorInfo.mnEmitterID = -1;
	errorInfo.mfTimestamp = -1;
	errorInfo.mnMode = 0;

	if (idx < emitterInfo.size())
    {
		tcDatabaseObject* objData = tcDatabase::Get()->GetObject(emitterInfo[idx].mnEmitterID);
		tcRadarDBObject* radarData = dynamic_cast<tcRadarDBObject*>(objData);
		if (radarData != 0)
		{
			if (radarData->maxFireControlTracks > 0)
			{
				emitterInfo[idx].mnMode = 7;
			}
			else
			{
				emitterInfo[idx].mnMode = 1;
			}
		}

        return emitterInfo[idx];
    }
    else
    {
        return errorInfo;
    }
}

void tcSensorMapTrack::IdentifyTrack(long id)
{
	if (mnDatabaseID == id) return;
	mnDatabaseID = id;

	// load new 3D model
	tcDatabaseObject* objData = tcDatabase::Get()->GetObject(id);
    if (objData != 0) SetModel(objData->Copy3DModel());
}

bool tcSensorMapTrack::IsBearingOnly() const
{
    return (tcTrack::IsBearingOnly() && (errorPoly.size() == 0));
}

bool tcSensorMapTrack::IsDestroyed() const
{
    return (sensorFlags & TRACK_DESTROYED) != 0;
}

bool tcSensorMapTrack::IsIdentified() const
{
	return mnDatabaseID != -1;
}

bool tcSensorMapTrack::IsNew() const
{
	return mfTimestamp == 0;
}

bool tcSensorMapTrack::IsStale() const
{
    return (sensorFlags & TRACK_STALE) != 0;
}

void tcSensorMapTrack::MarkDestroyed()
{
    sensorFlags |= TRACK_DESTROYED;
    mfSpeed_kts = 0;
}

void tcSensorMapTrack::MarkStale()
{
    sensorFlags |= TRACK_STALE;
}

void tcSensorMapTrack::ClearStale()
{
    sensorFlags &= (~TRACK_STALE);
}

void tcSensorMapTrack::UpdateErrorPolyWidth()
{
    errorPolyLonWidth_rad = 0;
    errorPolyLatWidth_rad = 0;

    size_t nPoints = errorPoly.size();
    if (errorPoly.size() == 0) return;

    float minLon = 99.0f;
    float maxLon = -99.0f;
    float minLat = 99.0f;
    float maxLat = -99.0f;

    const float wrapZoneLon = C_PIOVER180*170.0f;
    if ((errorPoly[0].x < wrapZoneLon) && (errorPoly[0].x > -wrapZoneLon))
    {
        for (size_t n=0; n<nPoints; n++)
        {
            minLon = std::min(minLon, errorPoly[n].x);
            maxLon = std::max(maxLon, errorPoly[n].x);
            minLat = std::min(minLat, errorPoly[n].y);
            maxLat = std::max(maxLat, errorPoly[n].y);
        }

    }
    else // use shifted lon coordinates to avoid pi/-pi wrap
    {
        for (size_t n=0; n<nPoints; n++)
        {
            float xunwrap = errorPoly[n].x + C_PI;
            xunwrap -= C_TWOPI * float(xunwrap >= C_PI);

            minLon = std::min(minLon, xunwrap);
            maxLon = std::max(maxLon, xunwrap);
            minLat = std::min(minLat, errorPoly[n].y);
            maxLat = std::max(maxLat, errorPoly[n].y);
        }
    }

    errorPolyLonWidth_rad = maxLon - minLon;
    errorPolyLatWidth_rad = maxLat - minLat;
}



tcSensorMapTrack& tcSensorMapTrack::operator= (const tcSensorMapTrack& t) 
{
    *(tcTrack*)this = t ;

    maSensorReport = t.maSensorReport;

    emitterInfo = t.emitterInfo;
    mnDatabaseID = t.mnDatabaseID; 
    sensorFlags = t.sensorFlags;
    intercepts = t.intercepts; 
    engaged = t.engaged; 
    assessedDamage = t.assessedDamage;
    errorPoly = t.errorPoly;

    alwaysVisible = t.alwaysVisible;

	/* model is deliberately not copied to avoid overhead. This is 
	** a side effect of mixing graphics and data within tcSensorMapTrack
	*/
	model = 0; 

    return(*this);
}

/**
* Careful with this--it doesn't copy all data from src
*/
tcSensorMapTrack::tcSensorMapTrack(const tcSensorMapTrack& src)
: tcTrack(src),
  maSensorReport(src.maSensorReport),
  emitterInfo(src.emitterInfo),
  assessedDamage(src.assessedDamage),
  errorPoly(src.errorPoly),
  errorPolyLonWidth_rad(src.errorPolyLonWidth_rad),
  errorPolyLatWidth_rad(src.errorPolyLatWidth_rad),
  intercepts(src.intercepts),
  engaged(src.engaged),
  ambiguityList(src.ambiguityList),
  sensorFlags(src.sensorFlags),
  mnDatabaseID(src.mnDatabaseID),
  model(0),
  alwaysVisible(src.alwaysVisible)
{

}

/**
* Careful with this--it doesn't copy all data from src
*/
tcSensorMapTrack::tcSensorMapTrack(const tcTrack& src)
: tcTrack(src),
  assessedDamage(0),
  sensorFlags(0),
  model(0),
  alwaysVisible(false)
{   

}


tcSensorMapTrack::tcSensorMapTrack()
: sensorFlags(0),
  mnDatabaseID(-1),
  assessedDamage(0),
  model(0),
  alwaysVisible(false)
{   
    tcTrack::mnID = NULL_INDEX;
    tcTrack::mnAffiliation = 0;
    tcTrack::mnAlliance = 0;
    tcTrack::mnClassification = 0;
    tcTrack::mfTimestamp = 0;
    tcTrack::mnFlags = 0;

}

tcSensorMapTrack::~tcSensorMapTrack() 
{  
	/* model is used for multiplayer client and for enemy alliances in single-play,
	** otherwise it will remain 0
	*/
    if (model)
    {
        model->SetSmokeMode(0);
        model->UpdateEffects(); // clear smoke particle generator
        model->Enable(false);
        delete model;
    }
}

