/**
**  @file tcPlatformDBObject.h
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

#ifndef _PLATFORMDBOBJECT_H_
#define _PLATFORMDBOBJECT_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "tcDatabaseObject.h"
#include "tcSensorPlatformDBObject.h"
#include <vector>
#include "tv_types.h"
#include "tc3DPoint.h"
#include "tcLoadoutData.h"

struct animationDBInfo;
class TiXmlElement;


namespace database
{
	class tcSqlReader;

    /**
    * Models a generic platform that has weapon launchers and
    * sensors and basic movement restrictions. This can be used
    * for a simple surface ship or aircraft model.
    */
    class tcPlatformDBObject : public tcDatabaseObject, public tcSensorPlatformDBObject
    {
    public:
        enum 
        { 
            MAXLAUNCHERS = 24,
            MAXANIMATIONS = 4,
            MAXMAGAZINES = 5
        };
        float mfMaxSpeed_kts;               ///< max speed, [kts]
        float mfAccel_ktsps;                ///< [kts/s] acceleration, simple model
        float mfTurnRate_degps;             ///< [deg/s]
        float mfFuelCapacity_kg;            ///< [kg], 0 is infinite fuel
        float mfFuelRate_kgps;              ///< [kg/s] at max thrust, simple model for now
        float mfToughness;                  ///< 0 - 100 for now, survivability
        std::string damageEffect;           ///< advanced damage model "toughness"

        int mnNumLaunchers;
        int mnNumMagazines;
        std::vector<std::string> maLauncherClass;  
        std::vector<std::string> maMagazineClass;
        std::vector<unsigned int> magazineId; // id for each magazine
        std::vector<unsigned int> launcherId; // id for each launcher
        
        std::vector<std::string> launcherDescription;
        std::vector<std::string> launcherName; ///< display names of launchers, e.g. "Tube 1"
        std::vector<float> launcherFOV_deg;
        std::vector<float> launcherAz_deg;
        std::vector<float> launcherEl_deg;
        std::vector<std::string> launcherFireControl; ///< fire control sensors for launchers (empty for none)
        std::vector<std::string> launcherFireControl2; ///< fire control sensors for launchers, second option (empty for none)
        std::vector<bool> launcherIsReloadable; ///< true if launcher is reloadable

        std::vector<animationDBInfo> animationInfo;

		tcDatabaseObject* AsDatabaseObject();
        virtual const char* GetClassName() const {return "Generic";} ///< returns class name of database object

		virtual float GetFuelConsumptionConstant(float speed_kts = 0) const;
		Vec2 GetLauncherAttitude(unsigned n) const;
        float GetLauncherFOV_deg(unsigned n) const;
		tc3DPoint GetLauncherPosition(unsigned n);
        size_t GetItemCapacityForLauncher(size_t launcherIdx, const std::string& item);
        int GetLauncherIndex(unsigned int id) const;
        tcLoadoutData* GetLoadout(const std::string& setupName);
        const std::vector<tcLoadoutData>& GetLoadoutList(float searchYear);

		float GetInternalFuelCapacity() const;
		bool HasInfiniteFuel() const;

        void ReorderMagazines();

        virtual void PrintToFile(tcFile& file);
        
		static void AddSqlColumns(std::string& columnString);
		void ReadSql(tcSqlReader& entry);
		void WriteSql(std::string& valueString);

        tcPlatformDBObject();
        tcPlatformDBObject(const tcPlatformDBObject& obj); ///< copy constructor
        virtual ~tcPlatformDBObject();
	protected:
		float fuelConsumptionConstant; ///< = (fuel rate / max speed)
		float invMaxSpeed; ///< 1/max_speed

		void CalculateParams();

    };

}

#endif

