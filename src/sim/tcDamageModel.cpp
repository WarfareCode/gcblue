/**
**  @file tcDamageModel.cpp
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

#include "stdwx.h" // precompiled header file

#ifndef WX_PRECOMP
#include "wx/wx.h" 
#endif

#include "tcDamageModel.h"
#include "tcAero.h"
#include "math_constants.h"
#include "randfn.h"
#include "tcGameObject.h"
#include "tcWeaponObject.h"
#include "tcDatabase.h"
#include "tcPlatformObject.h"
#include "tcPlatformDBObject.h"
#include "tcWeaponDamage.h"
#include "tcBallisticWeapon.h"
#include "tcBallisticDBObject.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



void Damage::Clear()
{
    isPenetration = false;
    kinetic_J = 0;
    explosive_kg = 0;
    blast_psi = 0;
    waterBlast_psi = 0;
    thermal_J_cm2 = 0;
    fragHits = 0;
    fragEnergy_J = 0;
}

/**
* Singleton accessor
*/
tcDamageModel* tcDamageModel::Get()
{
    static tcDamageModel instance;

    return &instance;
}

/**
* @return blast overpressure in PSI
* See http://www.fas.org/man/dod-101/navy/docs/es310/warheads/Warheads.htm , 
*   ES310 COURSE SYLLABUS SPRING 98 Last Revision: January 20, 1998 
*/
float tcDamageModel::CalculateBlastOverpressure(float range_m, float w_kg) const
{
    if ((w_kg > 0) && (range_m > 0))
    {
        float scaled_range_m = range_m * powf((1.1e-6 * w_kg), -0.333f);
    
        return (3.25e6 * powf(scaled_range_m, -2.3f)) + (4800.0f * powf((scaled_range_m + 305.0f), -1.2f));
    }
    else
    {
        return 0;
    }
}

/**
* Calculate fragment hit data
*/
tcDamageModel::FragHits 
    tcDamageModel::CalculateFragmentImpact(float range_m, float altitude_m, 
                                           const tcDamageModel::FragWeapon& weap, float targetArea_m2) const
{
    FragHits result;
    result.hits = 0;
    result.ke_J = 0;
    result.v_mps = 0;

    // J/kg, heat of explosion for TNT from http://www.fas.org/man/dod-101/navy/docs/es310/warheads/Warheads.htm
    const float delta_E = 2.7e6; 
    const float K_shape = 0.5f; // shape factor of warhead
    const float frag_density_kg_m3 = 8000.0f; // approx steel density
    const float Cgurney = sqrtf(2.0*delta_E); // http://en.wikipedia.org/wiki/Gurney_equations

    float rho = Aero::GetAirDensity(altitude_m);



    float N_frag = weap.metal_kg / weap.fragment_kg;

    float A_frag_m2 = powf((1.3293f * weap.fragment_kg / frag_density_kg_m3), 0.667f);

    float CtoM = weap.charge_kg / weap.metal_kg; // charge to metal ratio

    float v0_mps = Cgurney * sqrtf((CtoM / (1.0f + K_shape*CtoM)));

    float v_mps = v0_mps * expf(-rho*0.5f*A_frag_m2*range_m/(2.0f * weap.fragment_kg)); // model fragment speed deceleration from aero drag
    float ke_J = 0.5f*weap.fragment_kg*v_mps*v_mps;
    
    float avg_hits = targetArea_m2*(N_frag / (weap.spread_factor*4*C_PI*range_m*range_m));

    result.hits = (float)std::min(Poisson(avg_hits), (unsigned int)50);
    result.ke_J = ke_J;
    result.v_mps = v_mps;

    return result;
}

/**
* Intended for nuclear thermal radiation damage, but maybe can be used for lasers and similar
* @return J/cm2 radiation intensity
*/
float tcDamageModel::CalculateRadiationIntensity(float range_m, float w_kg) const
{
    if (w_kg <= 0)
    {
        return 0;
    }
    else
    {
        const float delta_E = 2.7e2;

        float J_cm2 = w_kg*delta_E / (C_FOURPI*range_m*range_m); // https://en.wikipedia.org/wiki/Effects_of_nuclear_explosions#Electromagnetic_pulse

        return J_cm2;
    }
}

/**
* This version calculates damage for weapon with many submunitions. Each submunition is randomly tested
* for impact or proximity damage to target
*/
void tcDamageModel::CalculateTotalDamageCluster(tcBallisticWeapon* ballistic, tcGameObject* target, Damage& damage)
{
	const unsigned int maxHits = 10;

	float damageRadius_m = ballistic->mpDBObject->clusterEffectRadius_m;
	float clusterArea_m2 = C_PI * damageRadius_m * damageRadius_m;

	float targetSpan_m = target->GetSpan();
	float targetArea_m2 = (C_PI * 0.25) * targetSpan_m * targetSpan_m;

	const database::tcWeaponDamage* weaponDamage = ballistic->GetDamageModel();
	wxASSERT(weaponDamage != 0);
	if (weaponDamage == 0) return; // error

	float weaponRadius_m = weaponDamage->maxRange_m;
	float weaponArea_m2 = C_PI * weaponRadius_m * weaponRadius_m;
	targetArea_m2 = std::min(targetArea_m2, weaponArea_m2);


	float pnear = weaponArea_m2 / clusterArea_m2;
	float pdirect = targetArea_m2 / clusterArea_m2;
	unsigned int nCluster = ballistic->mpDBObject->clusterCount;
	unsigned int nHits = 0;
	unsigned int nDirect = 0;
	for (unsigned int n=0; (n<nCluster) && (nHits<maxHits); n++)
	{
		float randval = randf();
		nHits += unsigned int(randval < pnear);
		nDirect += unsigned int(randval < pdirect);
	}

	// for now, just treat this all as blast or frag / non-direct damage
	float minRange_m = std::min(0.1f * target->GetSpan(), 50.0f);
    minRange_m = std::max(minRange_m, 10.0f);

	for (unsigned int n=0; n<nHits; n++)
	{
		float range_m = (1.0 - (randf() * randf())) * weaponRadius_m;
		range_m = std::max(range_m, minRange_m);

		damage.blast_psi += CalculateBlastOverpressure(range_m, weaponDamage->blastCharge_kg);

		if (weaponDamage->fragCharge_kg > 0)
		{
			FragWeapon fragWeap;
			fragWeap.charge_kg = weaponDamage->fragCharge_kg;
			fragWeap.metal_kg = weaponDamage->fragMetal_kg;
			fragWeap.fragment_kg = weaponDamage->fragFragment_kg;
			fragWeap.spread_factor = weaponDamage->fragSpread;

			float targetRadius_m = 0.5*target->GetSpan();
			float targetArea_m2 = 0.5 * C_PI * targetRadius_m * targetRadius_m; // approx for now, 0.5 for rect shape
			float fragRange_m = std::max(range_m, targetRadius_m);

			tcDamageModel::FragHits fragHits = 
				CalculateFragmentImpact(fragRange_m, target->mcKin.mfAlt_m, fragWeap, targetArea_m2);

			if (fragHits.hits > 0)
			{
				damage.fragHits += fragHits.hits;
				float alpha = fragHits.hits / damage.fragHits;
				damage.fragEnergy_J = (1-alpha)*damage.fragEnergy_J + alpha*fragHits.ke_J;
			}
		}
	}
    
}

/**
* @param damage damage description for this weapon detonation
* Point defense and air cannons should use a different model
*/
void tcDamageModel::CalculateTotalDamage(tcWeaponObject* weapon, tcGameObject* target, Damage& damage)
{
    if ((weapon == 0) || (target == 0))
    {
        wxASSERT(false);
        return;
    }

    bool goodDetonation = weapon->IsGoodDetonation();

    damage.Clear();


    const tcWeaponDamage* weaponDamage = GetWeaponDamageModel(weapon);


    /* if missile is targeted and has scored direct hit, then apply
    ** kinetic damage from missile (big fragment) and apply
    ** internal damage assuming missile has delayed warhead that explodes
    ** after penetrating target exterior
    */
    if (weapon->IsDirectHit() && (weapon->GetIntendedTarget() == target->mnID))
    {
        float speed_collide = weapon->mcKin.CalculateRangeRate(target->mcKin);
        if (speed_collide < 0)
        {
            wxASSERT(false);
            speed_collide = 0; // opening range rate case, shouldnt happen
        }

        float kinEnergy_J = 0.5*weapon->GetMassKg()*speed_collide*speed_collide;

        // fractional damage from kinetic energy of impact
        damage.kinetic_J = kinEnergy_J;

        damage.isPenetration = weaponDamage->isPenetration;

        // treat blast and frag as the same for now
        damage.explosive_kg = weaponDamage->blastCharge_kg + weaponDamage->fragCharge_kg + weaponDamage->fragMetal_kg; 
        return;
    }

    // no damage for direct hit weapons to other targets, or if weapon is a dud
    if (weapon->IsDirectHit() || (!goodDetonation)) return;

	tcBallisticWeapon* ballistic = dynamic_cast<tcBallisticWeapon*>(weapon);
	if ((ballistic != 0) && ballistic->IsClusterBomb())
	{
		CalculateTotalDamageCluster(ballistic, target, damage);
		return;
	}


    // determine if this is an underwater or underground explosion
    bool underwaterExplosion = ((weapon->mcKin.mfAlt_m <= -1.0f) && (weapon->mcTerrain.mfHeight_m < -1.0f));
    bool targetUnderwater = (target->mcKin.mfAlt_m <= 0) && (target->mcTerrain.mfHeight_m < -1.0f);
    bool targetAbovewater = (target->mcKin.mfAlt_m >= -3.0f); // target can be both under and above water
    
    bool affectsTarget = (underwaterExplosion && targetUnderwater) || (!underwaterExplosion && targetAbovewater);
    if (!affectsTarget) return;


    float range_m = 1000.0f * weapon->mcKin.RangeToKmAlt(target->mcKin);

    //float cumulativeDamage = 0;

    if (underwaterExplosion)
    {
        float damageRange_m = range_m;
        Vec3 collisionPoint;
        float collisionRange_m;

        if (damageRange_m < 250.0f) // dont check collisions for distance platforms affected by blast
        {
            // check collision along ray to origin
            if (target->CalculateCollisionPointOrigin(weapon, collisionPoint, collisionRange_m))
            {
                // wxASSERT(collisionRange_m < damageRange_m);
                damageRange_m = std::min(damageRange_m, collisionRange_m);
            }

            // check collision along "up" ray
            if (target->CalculateCollisionPointDir(weapon, Vec3(0, 1, 0), collisionPoint, collisionRange_m))
            {
                damageRange_m = std::min(damageRange_m, collisionRange_m);
            }
        }

        damageRange_m = std::max(damageRange_m, 10.0f); // don't allow anything closer than 10 m

        damage.waterBlast_psi = CalculateWaterBlastOverpressure(damageRange_m, weaponDamage->blastCharge_kg);
#ifdef _DEBUG
        fprintf(stdout, "Underwater explosion, %s, range: %.1f m, blast: %.1f PSI\n", target->mzClass.c_str(), damageRange_m, damage.waterBlast_psi);
#endif
        return; // no thermal or frag damage underwater
    }

    float minRange_m = std::min(0.05f * target->GetSpan(), 50.0f);
    minRange_m = std::max(minRange_m, 5.0f);

    range_m = std::max(range_m, minRange_m);

    damage.blast_psi = CalculateBlastOverpressure(range_m, weaponDamage->blastCharge_kg);

    damage.thermal_J_cm2 = CalculateRadiationIntensity(range_m, weaponDamage->radCharge_kg);

    if (weaponDamage->fragCharge_kg > 0)
    {
        FragWeapon fragWeap;
        fragWeap.charge_kg = weaponDamage->fragCharge_kg;
        fragWeap.metal_kg = weaponDamage->fragMetal_kg;
        fragWeap.fragment_kg = weaponDamage->fragFragment_kg;
        fragWeap.spread_factor = weaponDamage->fragSpread;

        float targetRadius_m = 0.5*target->GetSpan();
        float targetArea_m2 = 0.5 * C_PI * targetRadius_m * targetRadius_m; // approx for now, 0.5 for rect shape
        float fragRange_m = std::max(range_m, targetRadius_m);

        tcDamageModel::FragHits fragHits = 
            CalculateFragmentImpact(fragRange_m, target->mcKin.mfAlt_m, fragWeap, targetArea_m2);

        damage.fragHits = fragHits.hits;
        damage.fragEnergy_J = fragHits.ke_J;
    }

    return;
}

/**
* @return blast overpressure in PSI for underwater explosion
* @param range_m range in meters
* @param w_kg high explosive mass
*/
float tcDamageModel::CalculateWaterBlastOverpressure(float range_m, float w_kg) const
{
    if ((w_kg > 0) && (range_m > 0))
    {
		// Approximate blast scaling function
		// C. David Sulfredge, Robert H. Morris, and Robert L. Sanders, "Calculating the Effect of Surface or 
		//  Underwater Explosions on Submerged Equipment and Structures," Oak Ridge National Laboratory, Building 5700, MS-6085, 2001
        return 7592.2f * powf(w_kg, 0.376f) * powf(range_m, -1.13f); // 
    }
    else
    {
        return 0;
    }
}



const database::tcWeaponDamage* tcDamageModel::GetWeaponDamageModel(tcWeaponObject* weapon) const
{
    wxASSERT(weapon != 0);

    const database::tcWeaponDamage* weaponDamageData = weapon->GetDamageModel();
        
    if (weaponDamageData != 0)
    {
        return weaponDamageData;
    }
    else
    {
        wxASSERT(false); // should not happen, default returned by database
        return 0;
    }
}



tcDamageModel::tcDamageModel()
: database(0)
{
    database = tcDatabase::Get();
}


tcDamageModel::~tcDamageModel()
{
}
