/**  
**  @file tcDamageModel.h
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


#ifndef _TCDAMAGEMODEL_H_
#define _TCDAMAGEMODEL_H_

#ifdef WIN32
#pragma once
#endif


class tcGameObject;
class tcWeaponObject;
class tcBallisticWeapon;

namespace database
{
    class tcDatabase;
    class tcWeaponDamage;
}

struct Damage
{
    bool isPenetration; // weap can penetrate, if false ignore explosive dmg
    float kinetic_J; // kin energy impact damage
    float explosive_kg; // damage from internal explosion when weap penetrates
    float blast_psi;
    float waterBlast_psi; // underwater blast
    float thermal_J_cm2;
    float fragHits;
    float fragEnergy_J;

    void Clear();
};

/**
* Singleton class for advanced damage modeling
*/
class tcDamageModel
{
public:
    /// details of fragmenting weapon
    struct FragWeapon
    {
        float charge_kg; ///< equivalent kg TNT
        float metal_kg; ///< total mass of fragmenting metal
        float fragment_kg; ///< mass of single fragment
        float spread_factor; ///< 1 = isotropic, 0.5 hemisphere, etc
    };

    struct FragHits
    {
        float hits; ///< number of hits (poisson actual, not average)
        float ke_J; ///< fragment impact kinetic energy [J]
        float v_mps; ///< fragment impact speed
    };
    

    void CalculateTotalDamage(tcWeaponObject* weapon, tcGameObject* target, Damage& damage);
	void CalculateTotalDamageCluster(tcBallisticWeapon* ballistic, tcGameObject* target, Damage& damage);

    float CalculateBlastOverpressure(float range_m, float w_kg) const;
    float CalculateWaterBlastOverpressure(float range_m, float w_kg) const;
    FragHits CalculateFragmentImpact(float range_m, float altitude_m, const FragWeapon& weap, float targetArea_m2) const;
    float CalculateRadiationIntensity(float range_m, float w_kg) const;

    const database::tcWeaponDamage* GetWeaponDamageModel(tcWeaponObject* weapon) const;


    static tcDamageModel* Get();
private:
    database::tcDatabase* database;

    tcDamageModel();
    virtual ~tcDamageModel();

};


#endif