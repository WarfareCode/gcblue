/**
**  @file tcTrack.h
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


#ifndef _TCTRACK_H_
#define _TCTRACK_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>


class tcStream;
class tcCommandStream;
class tcCreateStream;
class tcUpdateStream;
class tcGameStream;
class tcPoint;

#define TRACK_ALT_VALID 0x01
#define TRACK_SPEED_VALID 0x02
#define TRACK_HEADING_VALID 0x04
#define TRACK_CLIMB_VALID 0x08
#define TRACK_BEARING_ONLY 0x10
#define TRACK_ACTIVE 0x20
#define TRACK_TRIANGULATED 0x40
#define TRACK_BEARINGRATE_VALID 0x80
#define TRACK_ALLVALID 0x2F
#define TRACK_ALLVALIDEXCEPTHEADING 0x2B

class tcTrack 
{
public:
    float mfLon_rad;
    float mfLat_rad;
    float mfAlt_m;
    float mfSpeed_kts;
    float mfHeading_rad;
    float mfClimbAngle_rad;
    float bearing_rad; ///< bearing for bearing-only tracks
    float bearingRate_radps;       ///< bearing rate in rad/s for bearing-only tracks
    double mfTimestamp;
    long mnID;
    //long mnPassivePlatformID; ///< long vs. unsigned int vs. long issue here to resolve eventually
    UINT16 mnClassification;
    UINT8 mnAffiliation; ///< 0 - unknown, 1 - friendly, 2 - neutral, 3 - hostile, 
    UINT8 mnAlliance; ///< 0 if unknown
    UINT8 mnFlags;

    void ClearFlags() {mnFlags=0;}
    /// why is mnID set to 0 instead of -1 ?
    virtual void Clear();
    bool IsAir() const {return ((mnClassification & PTYPE_AIR) != 0);}
    bool IsGround() const {return ((mnClassification & PTYPE_GROUND) != 0);}
    bool IsMissile() const {return ((mnClassification & PTYPE_MISSILE) != 0);}
    bool IsSurface() const {return ((mnClassification & PTYPE_SURFACE) != 0);}
    bool IsSub() const {return (mnClassification == PTYPE_SUBMARINE);}
    bool IsTorpedo() const {return (mnClassification == PTYPE_TORPEDO);}
    bool IsValid() const {return mnID != -1;}
    virtual bool IsBearingOnly() const;
	virtual bool IsBearingRateValid() const;
	bool IsHeadingValid() const;
	bool IsSpeedValid() const;
	bool IsAltitudeValid() const;

    bool MatchesMask(unsigned int mask) const;
    
    void SetAllValid() {mnFlags |= 0x0F;}
    float GetOrGuessAltitude() const;
    void GetPrediction(tcTrack& td, double mfTime);
	tcTrack PredictAhead(float timeDelta_s);
    void CoastToTime(double t_s);


    void Offset(float range_km, float heading_rad);
    void OffsetDeg(float range_km, float heading_deg);
    tcUpdateStream& operator<<(tcUpdateStream& stream);
    tcUpdateStream& operator>>(tcUpdateStream& stream);
    tcGameStream& operator<<(tcGameStream& stream);
    tcGameStream& operator>>(tcGameStream& stream);


	tcTrack& operator==(const tcTrack& src);
    tcTrack();
    tcTrack(const tcTrack& src);
    virtual ~tcTrack();
};


#endif

