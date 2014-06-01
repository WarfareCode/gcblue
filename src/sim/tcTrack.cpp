/**
**  @file tcTrack.cpp
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

#pragma warning (disable : 4996) // 'strdup' was declared deprecated

#include "simmath.h"
#include "tcTrack.h"
#include "common/tcObjStream.h"
#include "tcGameStream.h"
#include "nsNav.h"
#include "tcMapData.h"
#include "tcFloatCompressor.h"

/**
* Load state from stream
*/
tcUpdateStream& tcTrack::operator<<(tcUpdateStream& stream)
{
    stream >> mfLon_rad;
    stream >> mfLat_rad;
    stream >> tcIntervalCompressor(mfAlt_m, -15000.0f, 50535.0f);
    stream >> tcIntervalCompressor(mfSpeed_kts, 0.0f, 4000.0f);
    stream >> tcAngleCompressor(mfHeading_rad);
    stream >> tcAngleCompressor(bearing_rad);
    //stream >> mfClimbAngle_rad;
	mfClimbAngle_rad = 0; // use 0 for multiplayer track climb angle
    stream >> mfTimestamp;
    stream >> mnID;
    stream >> mnClassification;
    stream >> mnAffiliation;
    stream >> mnAlliance;
    stream >> mnFlags;

    return stream;
}

/**
* Save state to stream
*/
tcUpdateStream& tcTrack::operator>>(tcUpdateStream& stream)
{
    stream << mfLon_rad;
    stream << mfLat_rad;
    stream << tcIntervalCompressor(mfAlt_m, -15000.0f, 50535.0f);
    stream << tcIntervalCompressor(mfSpeed_kts, 0.0f, 4000.0f);
    stream << tcAngleCompressor(mfHeading_rad);
    stream << tcAngleCompressor(bearing_rad);
    //stream << mfClimbAngle_rad;
    stream << mfTimestamp;
    stream << mnID;
    stream << mnClassification;
    stream << mnAffiliation;
    stream << mnAlliance;
    stream << mnFlags;

    return stream;
}

/**
* Load state from stream
*/
tcGameStream& tcTrack::operator<<(tcGameStream& stream)
{
    stream >> mfLon_rad;
    stream >> mfLat_rad;
    stream >> mfAlt_m;
    stream >> mfSpeed_kts;
    stream >> mfHeading_rad;
    stream >> mfClimbAngle_rad;
    stream >> bearing_rad;
    stream >> bearingRate_radps;
    stream >> mfTimestamp;
    stream >> mnID;
    stream >> mnClassification;
    stream >> mnAffiliation;
    stream >> mnAlliance;
    stream >> mnFlags;

    return stream;
}

/**
* Save state to stream
*/
tcGameStream& tcTrack::operator>>(tcGameStream& stream)
{
    stream << mfLon_rad;
    stream << mfLat_rad;
    stream << mfAlt_m;
    stream << mfSpeed_kts;
    stream << mfHeading_rad;
    stream << mfClimbAngle_rad;
    stream << bearing_rad;
    stream << bearingRate_radps;
    stream << mfTimestamp;
    stream << mnID;
    stream << mnClassification;
    stream << mnAffiliation;
    stream << mnAlliance;
    stream << mnFlags;

    return stream;
}


void tcTrack::Clear() 
{
    mfLon_rad=0;
    mfLat_rad=0;
    mfAlt_m=0;
    mfSpeed_kts=0;
    mfHeading_rad=0;
    mfTimestamp=0;
    mnID=0;
    mfClimbAngle_rad=0;
    bearing_rad = 0;
    bearingRate_radps=0;
    mnFlags = 0;
    mnClassification = 0;
} 


/**
* Predict ahead (or behind) to t_s and mark track as updated.
* Added this to perform a fake update to get server to send track 
* stale and destroyed status to clients.
*/
void tcTrack::CoastToTime(double t_s)
{
    tcTrack coastedTrack;
    GetPrediction(coastedTrack, t_s);

    *this = coastedTrack;
}


bool tcTrack::MatchesMask(unsigned int mask) const
{
    bool coarseMatch = ((mnClassification & mask & 0xFFF0) != 0);
    bool fineMatch = ((mask & 0x000F) == 0) || ((mask & 0x000F) == (mnClassification & 0x000F));

    return coarseMatch && fineMatch;
}

/**
* Offsets location of track.
* @param range_km range to offset in km
* @param heading_rad direction to offset in radians
*/
void tcTrack::Offset(float range_km, float heading_rad)
{
    nsNav::OffsetApprox(mfLat_rad,mfLon_rad,mfLat_rad,mfLon_rad,heading_rad,C_KMTORAD*range_km);
}

/**
* Offsets location of track.
* @param range_km range to offset in km
* @param heading_rad direction to offset in degrees
*/
void tcTrack::OffsetDeg(float range_km, float heading_deg)
{
    nsNav::OffsetApprox(mfLat_rad,mfLon_rad,mfLat_rad,mfLon_rad,C_PIOVER180*heading_deg,C_KMTORAD*range_km);
}

/** 
* This is a version of GetPrediction that returns a predicted track instead of using a reference
* and uses delta time vs. absolute time.
*
* @param timeDelta_s time difference from track time to predict ahead or use < 0 to predict back
* @see tcTrack::GetPrediction
*/
tcTrack tcTrack::PredictAhead(float timeDelta_s)
{
	tcTrack track;

	GetPrediction(track, mfTimestamp + timeDelta_s);

	return track;
}

/**
* @returns track altitude or default based on classification if not avail
*/
float tcTrack::GetOrGuessAltitude() const
{
    if (mnFlags & TRACK_ALT_VALID)
    {
        return mfAlt_m;
    }
    else if (mnClassification & (PTYPE_AIR | PTYPE_MISSILE))
    {
		float terrain_height_m =
			tcMapData::Get()->GetTerrainHeight(C_180OVERPI*mfLon_rad, C_180OVERPI*mfLat_rad, mfTimestamp);
		if (terrain_height_m <= 900.0f)
		{
			return 1000.0f;
		}
		else
		{
			return terrain_height_m + 100.0f;
		}
    }
	else if (mnClassification & PTYPE_GROUND)
	{
		float terrain_height_m =
			tcMapData::Get()->GetTerrainHeight(C_180OVERPI*mfLon_rad, C_180OVERPI*mfLat_rad, mfTimestamp);
		return terrain_height_m + 5.0f;
	}
	else if (mnClassification & PTYPE_SUBSURFACE)
	{
		return -20.0f;
	}
    else
    {
        return 0;
    }
}


void tcTrack::GetPrediction(tcTrack& td, double afTime)
{
   float dt_s = (float)(afTime - mfTimestamp);

   bool bSpeedValid = (mnFlags & TRACK_SPEED_VALID) != 0;
   bool bHeadingValid = (mnFlags & TRACK_HEADING_VALID) != 0;
   bool bAltValid = (mnFlags & TRACK_ALT_VALID) != 0;
   bool bClimbValid = (mnFlags & TRACK_CLIMB_VALID) != 0;
   bool bearingRateValid = (mnFlags & TRACK_BEARINGRATE_VALID) != 0;
   bool isBearingOnly = (mnFlags & TRACK_BEARING_ONLY) != 0;

   if (isBearingOnly) 
   {
       td = *this;

	   if (bearingRateValid)
	   {
		   const float db_max = C_PIOVER180 * 15.0f;
		   const float db_min = -C_PIOVER180 * 15.0f;
		   float dBearing = dt_s * bearingRate_radps;
		   if (dBearing < db_min) dBearing = db_min;
		   else if (dBearing > db_max) dBearing = db_max;

           td.bearing_rad = bearing_rad + dBearing;
	   }
       // MAR 2009 note this was broken with addition of errorPoly logic, some tracks marked "bearing only"
       // actually have an error poly and position estimate, so they do not behave like the old bearing only
       // tracks
       //
	   //else
	   //{
		  // td.mfHeading_rad = mfHeading_rad;
	   //}

	   //// bearing-only track arbitrarily plotted 10 km from sensing platform
	   //td.mfLat_rad = mfLat_rad;
	   //td.mfLon_rad = mfLon_rad;
	   //td.Offset(10.0f, td.mfHeading_rad);
   }
   else
   {
	   if (bHeadingValid) 
	   {
		   td.mfHeading_rad = mfHeading_rad;
	   }
	   else
	   {
		   td.mfHeading_rad = 0;
	   }

	   if (bSpeedValid && bHeadingValid) 
	   {
		   float fGroundSpeed_kts;
		   if (bClimbValid) 
		   {
			   fGroundSpeed_kts = mfSpeed_kts*cosf(mfClimbAngle_rad);
		   }
		   else 
		   {
			   fGroundSpeed_kts = mfSpeed_kts;
		   }
		   float fRange_rad = fGroundSpeed_kts*C_KTSTORADPS*dt_s;
		   nsNav::OffsetApprox(mfLat_rad,mfLon_rad, td.mfLat_rad,td.mfLon_rad, mfHeading_rad,fRange_rad);

		   td.mfSpeed_kts = mfSpeed_kts;
	   }
	   else 
	   {
		   td.mfLat_rad = mfLat_rad;
		   td.mfLon_rad = mfLon_rad;
		   td.mfSpeed_kts = 0;
	   }
   }

   if (bAltValid && bClimbValid)
   {
      float fClimbRate_mps = C_KTSTOMPS*mfSpeed_kts*sinf(mfClimbAngle_rad);
      td.mfAlt_m = mfAlt_m + fClimbRate_mps*dt_s;
      td.mfClimbAngle_rad = mfClimbAngle_rad;

	  if ((mfAlt_m >= 0)&&(td.mfAlt_m < 0)) {td.mfAlt_m = 0;}
   }
   else 
   {
      td.mfAlt_m = mfAlt_m;   
      td.mfClimbAngle_rad = 0;
   }

   if (bHeadingValid)
   {
        td.mfHeading_rad += (float(td.mfHeading_rad < 0) - float(td.mfHeading_rad >= C_TWOPI))*C_TWOPI;
        wxASSERT((td.mfHeading_rad < 10.0f)&&(td.mfHeading_rad > -10.0f));
   }
   else
   {
       td.mfHeading_rad = 0;
   }

   td.bearingRate_radps = bearingRate_radps; // for bearing only tracks, copy rate
   td.mnFlags = mnFlags;
   td.mnID = mnID;
   td.mfTimestamp = afTime;
   td.mnAffiliation = mnAffiliation;
   td.mnAlliance = mnAlliance;
   td.mnClassification = mnClassification;
}

bool tcTrack::IsAltitudeValid() const
{
	return (mnFlags & TRACK_ALT_VALID) != 0;
}

bool tcTrack::IsBearingOnly() const
{
	return (mnFlags & TRACK_BEARING_ONLY) != 0;
}

bool tcTrack::IsBearingRateValid() const
{
	return ((mnFlags & TRACK_BEARING_ONLY) != 0) &&
		   ((mnFlags & TRACK_BEARINGRATE_VALID) != 0);
}

bool tcTrack::IsHeadingValid() const
{
	return (mnFlags & TRACK_HEADING_VALID) != 0;
}

bool tcTrack::IsSpeedValid() const
{
	return (mnFlags & TRACK_SPEED_VALID) != 0;
}

/**
* copy track
*/
tcTrack& tcTrack::operator==(const tcTrack& src)
{
    mfLon_rad = src.mfLon_rad;
    mfLat_rad = src.mfLat_rad;
    mfAlt_m = src.mfAlt_m;
    mfSpeed_kts = src.mfSpeed_kts;
    mfHeading_rad = src.mfHeading_rad;
    mfClimbAngle_rad = src.mfClimbAngle_rad;
    bearing_rad = src.bearing_rad;
    bearingRate_radps = src.bearingRate_radps;
    mfTimestamp = src.mfTimestamp;
    mnID = src.mnID;
    mnClassification = src.mnClassification;
    mnAffiliation = src.mnAffiliation;
    mnAlliance = src.mnAlliance;
    mnFlags = src.mnFlags;

    return *this;
}


tcTrack::tcTrack()
:   mfLon_rad(0),
    mfLat_rad(0),
    mfAlt_m(0),
    mfSpeed_kts(0),
    mfHeading_rad(0),
    mfClimbAngle_rad(0),
    bearing_rad(0),
    bearingRate_radps(0),
    mfTimestamp(0),
    mnID(0),
    mnClassification(0),
    mnAffiliation(0),
    mnAlliance(0),
    mnFlags(0)
{
}

tcTrack::tcTrack(const tcTrack& src)
:   mfLon_rad(src.mfLon_rad),
    mfLat_rad(src.mfLat_rad),
    mfAlt_m(src.mfAlt_m),
    mfSpeed_kts(src.mfSpeed_kts),
    mfHeading_rad(src.mfHeading_rad),
    mfClimbAngle_rad(src.mfClimbAngle_rad),
    bearing_rad(src.bearing_rad),
    bearingRate_radps(src.bearingRate_radps),
    mfTimestamp(src.mfTimestamp),
    mnID(src.mnID),
    mnClassification(src.mnClassification),
    mnAffiliation(src.mnAffiliation),
    mnAlliance(src.mnAlliance),
    mnFlags(src.mnFlags)
{
}

tcTrack::~tcTrack()
{
}
