/** 
**  @file tcBallisticWeapon.h
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

#ifndef _TCBALLISTICWEAPON_H_
#define _TCBALLISTICWEAPON_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "tcWeaponObject.h"


namespace database
{
    class tcBallisticDBObject;
}

class tcUpdateStream;
class tcGameStream;

/**
* Class for unguided ballistic weapons e.g. gun rounds, dumb bombs.
* Detonation is on impact with terrain or ocean surface.
* Currently this does not model drag to make targeting easy.
*
* @see tcWeaponObject
*/
class tcBallisticWeapon : public tcWeaponObject
{
public:
	tcBallisticDBObject* mpDBObject;

    void Clear();
	virtual void LaunchFrom(tcGameObject* obj, unsigned nLauncher);
    virtual void Update(double afStatusTime);
    bool IsGravityBomb() const;
    bool IsGunRound() const;
    bool IsAutocannon() const;
    bool IsSmartBomb() const;
	bool IsClusterBomb() const;
	bool IsRocket() const;
    float GetDistanceTraveled() const;
    float GetAngleErrorRad() const;
    unsigned int GetBurstCount() const;
	virtual float GetDamageEffectRadius() const;

    void PrintToFile(tcFile&);
    void SaveToFile(tcFile& file);
    void LoadFromFile(tcFile& file);
    virtual void Serialize(tcFile& file, bool mbLoad);
    virtual tcUpdateStream& operator<<(tcUpdateStream& stream);
    virtual tcUpdateStream& operator>>(tcUpdateStream& stream);
    virtual tcGameStream& operator<<(tcGameStream& stream);
    virtual tcGameStream& operator>>(tcGameStream& stream);

    tcBallisticWeapon();
    tcBallisticWeapon(const tcBallisticWeapon&);
    tcBallisticWeapon(tcBallisticDBObject* obj);
	~tcBallisticWeapon();
protected:
	float vz_mps;  ///< vertical velocity [m/s]
	float vxy_mps; ///< lateral velocity [m/s]
    float distFromLaunch_m; ///< distance from launch point [m] (horizontal for ballistic)
    GeoPoint targetPos;   // target position for guided weapons

    bool CheckGravityBombImpact();
    void UpdateSmartBombMotion(float dt_s);
    void UpdateGroundFuse();
    void UpdateAutocannon();
    void UpdateSmartBombFuse();
    void UpdateTargetFuse();
    const GeoPoint& CalculateGunSolution(long targetId);

};
#endif