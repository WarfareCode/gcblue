/**
**  @file tcAirDBObject.h
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

#ifndef _AIRDBOBJECT_H_
#define _AIRDBOBJECT_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "tcDatabaseObject.h"
#include "tcPlatformDBObject.h"
#include "tcAirDetectionDBObject.h"
#include "tcWaterDetectionDBObject.h"

namespace database
{
	class tcSqlReader;

    /**
    * Models a simple air platform (fixed wing or helo). Specialization of
	* old tcGenericDBObject.
    *
    * Added tcWaterDetectionDBObject parent to support dipping sonar
    */
    class tcAirDBObject :  public tcPlatformDBObject, public tcAirDetectionDBObject, public tcWaterDetectionDBObject
    {
    public:
        float maxTakeoffWeight_kg;          ///< [kg] maximum weight at takeoff
        float maxAltitude_m;                ///< [m] operating ceiling
        float climbRate_mps;                ///< [m/s]
        float gmax;                         ///< max Gs
        float minimumRunway_m;              ///< minimum runway length required (with no arrestor)
        bool isCarrierCompatible;           ///< 1 - can land on aircraft carriers, 0 - otherwise
        int outFuelPods;                    ///< number of aircraft that this aircraft can refuel simultaneously
        float fuelOut_kgps;                 ///< fuel output for each pod in kg/s
        float fuelIn_kgps;                  ///< amount of fuel this a/c can receive in kg/s, use 0 for no A/A refueling
        float maintenanceMin_s;             ///< minimum amount of random maintenance time required after landing
        float maintenanceMax_s;             ///< maximum amount of random maintenance time required after landing

		tcDatabaseObject* AsDatabaseObject();
        virtual const char* GetClassName() const {return "Air";} ///< returns class name of database object

		virtual float GetFuelConsumptionConstant(float speed_kts = 0) const;
		float GetRandomMaintenanceTime() const;

        bool IsCarrierCompatible() const;

        void ValidateLoadouts();

        virtual void PrintToFile(tcFile& file);

		static void AddSqlColumns(std::string& columnString);
		void ReadSql(tcSqlReader& entry);
		void WriteSql(std::string& valueString);

        tcAirDBObject();
        tcAirDBObject(const tcAirDBObject& obj); ///< copy constructor
        virtual ~tcAirDBObject();
	private:

		void CalculateParams();

    };

}

#endif

