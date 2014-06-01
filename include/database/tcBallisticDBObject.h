/*
**  @file tcBallisticDBObject.h
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

#ifndef _BALLISTICDBOBJECT_H_
#define _BALLISTICDBOBJECT_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "tcWeaponDBObject.h"

class TiXmlElement;

namespace database
{
	class tcSqlReader;

	class tcBallisticDBObject : public tcWeaponDBObject 
	{
	public:
        enum {GUN_ROUND = 0, GRAVITY_BOMB = 1, AUTO_CANNON = 2, SMART_BOMB = 3, CM_ROUND = 4, ROCKET = 5};
        int ballisticType;
        //float maxRange_km; ///< maximum effective range (replaced with maxRange_km in tcWeaponDBObject
        float angleError_rad; ///< angular error for gun rounds and point defense
        int burstCount; ///< for rapid fire guns, the number of rounds in a burst
        float burstDuration_s; ///< for rapid fire guns, the duration of the burst

		unsigned int clusterCount;
		float clusterEffectRadius_m;

        std::string sensorClass;
        float smartMaxClimb_rad; ///< max climb angle allowed for smart bomb
        float smartError_m; ///< distance error relative to target
        bool lockOnAfterLaunch;

        long sensorKey; ///< key for fast access of seeker

        // calculated parameters
        float one_over_launchSpeed; ///< 1.0f / tcWeaponDBObject::launchSpeed_mps
        float launchSpeed2; ///< tcWeaponDBObject::launchSpeed_mps^2

		float GetGunneryElevation(float range_m, float dz_m, float& tti_s);
		float GetGunneryElevation2(float range_m, float dz_m, float& tti_s);
		float GetMaxLevelGunRangeKm();
        float CalculateRangeKm(float altitude_m, float speed_mps);
        bool IsGravityBomb() const;
        bool IsSmartBomb() const;
        bool IsGunRound() const;
        bool IsAutocannon() const;
        bool IsCMRound() const;
		bool IsRocket() const;

        long GetSensorKey();

		virtual const char* GetClassName() const {return "Ballistic";} ///< returns class name of database object
		virtual void PrintToFile(tcFile& file);

		static void AddSqlColumns(std::string& columnString);
		void ReadSql(tcSqlReader& entry);
		void WriteSql(std::string& valueString);

        static float CalculateBallisticElevation(float range_m, float dz_m, float v_mps, float min_x2, float& tti_s);
        static float CalculateMissDistance(float range_m, float dz_m, float v_mps, float el_rad);

		tcBallisticDBObject(const tcBallisticDBObject& obj); ///< copy constructor
		tcBallisticDBObject();
		virtual ~tcBallisticDBObject();

    private:
        void CalculateParams();

	};

} // namespace database

#endif

