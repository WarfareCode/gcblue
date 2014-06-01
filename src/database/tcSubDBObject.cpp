/*
**  @file tcSubDBObject.cpp
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

#include "stdwx.h"

#include "tcSubDBObject.h"
#include "tcPlatformDBObject.h"
#include "CsvTranslator.h"
#include "common/math_constants.h"
#include "common/tinyxml.h"
#include <sstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

namespace database
{
    /**
    * Calculate private parameters. Should be called after
    * object is loaded.
    */
    void tcSubDBObject::CalculateParams()
    {
        invMaxSpeed_mps = 1.0f / (C_KTSTOMPS*mfMaxSpeed_kts);
        batteryDrainConstant = batteryRate_kW * invMaxSpeed_mps;
        invDraft_m = 1.0f / std::max(draft_m, 0.1f);
    }

	/**
	* Drain rate is scaled to 4x at max speed, database rate is for near zero speed
	*/
    float tcSubDBObject::GetBatteryRate(float speed_mps) const
    {
		float speed_factor = 1.0f + 3.0f * speed_mps * invMaxSpeed_mps;

        return batteryDrainConstant * speed_mps * speed_factor;
    }
    
    float tcSubDBObject::GetInvDraft() const
    {
        return invDraft_m;
    }

    /**
    * @returns max speed without cavitation in kts
    */
    float tcSubDBObject::GetMaxNonCavitatingSpeed(float depth_m) const
    {
        return tcWaterDetectionDBObject::GetCavitationSpeedKts(depth_m);
    }
    
    bool tcSubDBObject::IsCavitatingMps(float speed_mps, float depth_m) const
    {
        return (speed_mps > (C_KTSTOMPS*GetMaxNonCavitatingSpeed(depth_m)));
    }
    
    bool tcSubDBObject::IsCavitatingKts(float speed_kts, float depth_m) const
    {
        return (speed_kts > GetMaxNonCavitatingSpeed(depth_m));
    }
    

    /**
    * Adds sql column definitions to columnString. This is used for
    * SQL create table command
    */
    void tcSubDBObject::AddSqlColumns(std::string& columnString)
    {
        tcPlatformDBObject::AddSqlColumns(columnString);

        columnString += ",Draft_m real";
        columnString += ",SurfaceSpeed_kts real";

        tcAirDetectionDBObject::AddSqlColumns(columnString); // Applies to surfaced sub
        tcWaterDetectionDBObject::AddSqlColumns(columnString);

        columnString += ",";
        
        columnString += "MaxDepth_m number(8),";

        columnString += "IsDieselElectric number(1),";
        columnString += "BatteryCapacity_kJ number(8),";
        columnString += "BatteryRate_kW number(8),";
        columnString += "BatteryCharge_kW number(8)";
    }

    void tcSubDBObject::ReadSql(tcSqlReader& entry)
    {
        tcPlatformDBObject::ReadSql(entry);

        draft_m = (float)entry.GetDouble("Draft_m");
        surfaceSpeed_kts = (float)entry.GetDouble("SurfaceSpeed_kts");

        tcAirDetectionDBObject::ReadSql(entry);
        tcWaterDetectionDBObject::ReadSql(entry);

        mfMaxDepth_m = entry.GetDouble("MaxDepth_m");

        isDieselElectric = entry.GetInt("IsDieselElectric") != 0;
        batteryCapacity_kJ = entry.GetDouble("BatteryCapacity_kJ");
        batteryRate_kW = entry.GetDouble("BatteryRate_kW");
        batteryCharge_kW = entry.GetDouble("BatteryCharge_kW");

        CalculateParams();
    }

    void tcSubDBObject::WriteSql(std::string& valueString)
    {
        tcPlatformDBObject::WriteSql(valueString);

        std::stringstream s2;
        s2 << ",";
        s2 << draft_m << ",";
        s2 << surfaceSpeed_kts;
        valueString += s2.str();

        tcAirDetectionDBObject::WriteSql(valueString);
        tcWaterDetectionDBObject::WriteSql(valueString);

        std::stringstream s;
        s << ",";

        s << mfMaxDepth_m << ",";

        s << isDieselElectric << ",";
        s << batteryCapacity_kJ << ",";
        s << batteryRate_kW << ",";
        s << batteryCharge_kW;

        valueString += s.str();
    }


    tcSubDBObject::tcSubDBObject()
    :   batteryDrainConstant(0),
        invMaxSpeed_mps(0),
        invDraft_m(0)
    {
        mnModelType = MTYPE_SUBMARINE;
        mnType = PTYPE_SUBMARINE; // functional classification
    }

    tcSubDBObject::tcSubDBObject(const tcSubDBObject& obj)
        :
        draft_m(obj.draft_m),
        surfaceSpeed_kts(obj.surfaceSpeed_kts),
        invMaxSpeed_mps(obj.invMaxSpeed_mps),
        invDraft_m(obj.invDraft_m),
        batteryDrainConstant(obj.batteryDrainConstant),
        mfMaxDepth_m(obj.mfMaxDepth_m),
        isDieselElectric(obj.isDieselElectric),
        batteryCapacity_kJ(obj.batteryCapacity_kJ),
        batteryRate_kW(obj.batteryRate_kW),
        batteryCharge_kW(obj.batteryCharge_kW)
    {
    }


    tcSubDBObject::~tcSubDBObject()
    {
    }


}