/** 
**  @file tcWeaponObject.h 
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

#ifndef _TCWEAPONOBJECT_H_
#define _TCWEAPONOBJECT_H_

#include "tcGameObject.h"

class tcStream;
class tcUpdateStream;
class tcGameStream;

namespace database
{
    class tcWeaponDBObject;
    class tcWeaponDamage;
}

struct Damage;

/**
 * Base class for weapons, e.g. missiles, bombs, gun rounds.
 *
 * @see tcGameObject
 */
class tcWeaponObject : public tcGameObject
{
public:
	float GetDamage() const;
	float GetDetonationDelay() const;

	/// returns intended target for weap or -1 if none exists
	long GetIntendedTarget() const;

	/// returns radius around detonation point to consider for target damage
	virtual float GetDamageEffectRadius() const;
    
	bool IsDetonated();
    bool IsDirectHit() const;
    long GetDirectHitTargetId() const;
    void SetDirectHitTargetId(long id);

    bool IsGoodDetonation() const;
    bool IsGroundFused() const;
    
    bool IsDatalinkActive() const;

    virtual float GetMassKg() const;
    const tcWeaponDBObject* GetDBObject() const;
    const database::tcWeaponDamage* GetDamageModel() const;

    /// returns true if id is intended target of this weapon
    bool IsIntendedTarget(long id);
	/// true if launched by platform id
	bool WasLaunchedBy(long id) const;

	void SetDetonationDelay(float delay_s);
    

    void SetImpactPoint(const Vec3& pos);
    const Vec3& GetImpactPoint() const;

    /// sets intended target
    void SetIntendedTarget(long targetId);

    virtual float ApplyAdvancedDamage(const Damage& damage, tcGameObject* damager); ///< called when new damage occurs
    
protected:
    long intendedTarget;
    bool fuseHasTriggered; ///< set true when weapon detonates
    long directHitTargetId; ///< set to target id when weapon collides/impacts target as part of detonation, -1 otherwise
    bool goodDetonation; ///< true if weapon not dud
    Vec3 impactPoint; ///< direct hit point in relative world coordinates
    bool payloadDeployed; ///< true after payload has been deployed (e.g. ASROC)
    bool malfunctionChecked; ///< true after in-flight malfunction has been tested, so test is done once

    // mid-course guidance parameters
    long launchingPlatform;
    bool datalinkActive;


    tcWeaponDBObject* mpDBObject;  

	/** 
	* Delay in seconds before detonation (allows some movement 
	* closer to target between time steps)
	*/
	float fuseDelay; 
    enum FuseMode
    {
        GROUND_FUSE = 0, ///< detonate on hitting ground
        TARGET_FUSE = 1  ///< detonate when near target (used for point defense ballistics)
    };
    FuseMode fuseMode;

    virtual tcUpdateStream& operator<<(tcUpdateStream& stream);
    virtual tcUpdateStream& operator>>(tcUpdateStream& stream);
    virtual tcGameStream& operator<<(tcGameStream& stream);
    virtual tcGameStream& operator>>(tcGameStream& stream);

	void Detonate(float delay_s = 0);
    void SetFuseMode(FuseMode mode);
    void TestForDud();
    void MalfunctionCheck();
    void HandlePoleWrap();
    static void HandlePoleWrap(tcKinematics& kin);

	bool HasPayload() const;
    void DeployPayload();
    void LaunchPayload(tcGameObject* payload);

    void UpdateDatalinkStatus();

    tcWeaponObject();
    tcWeaponObject(const tcWeaponObject&);
    tcWeaponObject(tcWeaponDBObject* obj);
    ~tcWeaponObject();
};

#endif
