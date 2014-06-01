/** 
**  @file tcBallisticMissile.h
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

#if _MSC_VER > 1000
#pragma once
#endif

#ifndef _TCBALLISTICMISSILE_H_
#define _TCBALLISTICMISSILE_H_

#include "tcAero.h"
#include "tcWeaponObject.h"
#include "tcBallisticMissileDBObject.h"

class tcUpdateStream;
class tcGameStream;

/**
 * A class that represents a missle.
 *
 * @see tcGameObject
 */
class tcBallisticMissile : public tcWeaponObject
{
public:
    void Clear();
	virtual void LaunchFrom(tcGameObject* obj, unsigned nLauncher);

    virtual void Update(double t);
    virtual void UpdateEffects();
    virtual void UpdateGuidance(double t);

    const GeoPoint& GetTargetDatum() const;

    virtual tcUpdateStream& operator<<(tcUpdateStream& stream);
    virtual tcUpdateStream& operator>>(tcUpdateStream& stream);

    virtual tcGameStream& operator<<(tcGameStream& stream);
    virtual tcGameStream& operator>>(tcGameStream& stream);

    tcBallisticMissile(const tcBallisticMissile& obj);
    tcBallisticMissile(tcBallisticMissileDBObject* obj);
    ~tcBallisticMissile();

private:
    tcBallisticMissileDBObject* mpDBObject;

    bool subSurfaceLaunch; ///< true during subsurface launch phase for sub-launched missiles

    double lastGuidanceUpdateTime;
    double guidanceUpdateInterval;

    float flightTime_s;
    float thrustShutoffTime_s; ///< allows for early shutoff of thrust for closer range target

    GeoPoint targetDatum;

    // ECEF parameters
    double x;
    double y;
    double z;
    float vx;
    float vy;
    float vz;

    double xt; // targetDatum ECEF
    double yt;
    double zt;
    double rt; // mag (xt,yt,zt)

    float gx; // ECEF goal velocity, unit vector, updated by guidance
    float gy;
    float gz;

    float speed_mps;
    float speed2_mps2;
    double r_ecef; // distance from ECEF origin [m]

    
    void CalculateECEF();
    void CalculateLLA();

    void Enu2ecef(float lat_rad, float lon_rad, float ke, float kn, float ku, float& kx, float& ky, float& kz);
    void Ecef2enu(float lat_rad, float lon_rad, float kx, float ky, float kz, float& ke, float& kn, float& ku);

    void UpdateDetonation();
    void UpdateSubsurface(double t);
    void UpdateFlight(float dt_s);

    float GlimitedTurnRate() const;
    void CalculateSecondFocus(float xa, float ya, float xb, float yb, float ae, float& xf, float& yf);
};

#endif
