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
	* Drain rate uses Peukert battery formula in amp hours format.  800 volt electrical system assumed.
	*/
    float tcSubDBObject::GetAIPBatteryRate(float speed_kts) const
	{
		if (!isDieselElectric && !isAIP){return 0;}

		float move_cost_hp = pow(speed_kts * pow(Electric_ShaftHP,0.3333f) / mfMaxSpeed_kts,3.0f);
		float hotel_load_hp = electricalLoadAdjustment * 10.72386;	//given in kwhr, converted to hp seconds.
		float capacity_ah = batteryCapacityRated_kWhr * 4.5;	//800volt electrical assumed.
		float self_discharge = 0.000278 * capacity_ah;			//20% per month self discharge rate, in amps.
		float self_discharge_hp = self_discharge * 10.72386;	//self discharge, in hp.
		float AIP_expend_hp = std::max(move_cost_hp,self_discharge_hp) + hotel_load_hp;
		
		if (isAIP && (AIP_ShaftHP >= AIP_expend_hp))
		{
			//if AIP can afford the move_cost, and has power to spare, we can recharge the battery
			float recharge_hp = AIP_ShaftHP - AIP_expend_hp;
			float recharge_kW = std::max(0.0f,std::min(recharge_kW, recharge_hp * 0.45f * 746)) / 3600;
			return recharge_kW;
		}
		else if (isAIP)
		{
			//have aip, but AIP cannot sustain current rate, battery takes excess workload.
			move_cost_hp = std::max(move_cost_hp + std::min(move_cost_hp,self_discharge_hp) + hotel_load_hp / AIP_ShaftHP,0.0f);
		}

		float batteryRate = move_cost_hp * 0.9325f;
		float battery_endurance_hours = batteryRatedHours * pow(capacity_ah/(batteryRate*batteryRatedHours),batteryPeukert);
		float adjusted_draw = capacity_ah / battery_endurance_hours;
		batteryRate = -adjusted_draw / 16200;
        return batteryRate;
	}

	/**
	* Drain rate uses Peukert battery formula in amp hours format.  800 volt electrical system assumed.
	*/
    float tcSubDBObject::GetBatteryRate(float speed_kts) const
    {
		if (!isDieselElectric){return 0;}
		float move_cost_hp = pow(speed_kts * pow(Electric_ShaftHP,0.3333f) / mfMaxSpeed_kts,3.0f);
		float hotel_load_hp = electricalLoadAdjustment * 10.72386;	//given in kwhr, converted to hp seconds.
		float capacity_ah = batteryCapacityRated_kWhr * 4.5;	//800volt electrical assumed.
		float self_discharge = 0.000278 * capacity_ah;			//20% per month self discharge rate, in amps.
		float self_discharge_hp = self_discharge * 10.72386;	//self discharge, in hp.
		
		move_cost_hp = move_cost_hp + std::min(move_cost_hp,self_discharge_hp) + hotel_load_hp;
		float batteryRate = move_cost_hp * 0.9325f;
		float battery_endurance_hours = batteryRatedHours * pow(capacity_ah/(batteryRate*batteryRatedHours),batteryPeukert);
		float adjusted_draw = capacity_ah / battery_endurance_hours;
		batteryRate = -adjusted_draw / 16200;

		return batteryRate;
    }
    
	/**
	* Drain rate uses Peukert battery formula in amp hours format.  800 volt electrical system assumed.
	*/
    float tcSubDBObject::GetBatteryRate(float speed_kts, bool snorkel) const
    {
		if (!isDieselElectric){return 0;}
		float batteryRate = 0;
		float move_cost_hp = pow(speed_kts * pow(Electric_ShaftHP,0.3333f) / mfMaxSpeed_kts,3.0f);
		float hotel_load_hp = electricalLoadAdjustment * 10.72386;	//given in kwhr, converted to hp seconds.
		float capacity_ah = batteryCapacityRated_kWhr * 4.5;	//800volt electrical assumed.
		float self_discharge = 0.000278 * capacity_ah;			//20% per month self discharge rate, in amps.
		float self_discharge_hp = self_discharge * 10.72386;	//self discharge, in hp.
		
		move_cost_hp = move_cost_hp + std::min(move_cost_hp,self_discharge_hp) + hotel_load_hp;
		if (!snorkel)
		{
			batteryRate = move_cost_hp * 0.9325f;
			float battery_endurance_hours = batteryRatedHours * pow(capacity_ah/(batteryRate*batteryRatedHours),batteryPeukert);
			float adjusted_draw = capacity_ah / battery_endurance_hours;
			batteryRate = -adjusted_draw / 16200;
		}
		else
		{
			batteryRate = std::min((Primary_ShaftHP - move_cost_hp) * 0.45f * 746,batteryCharge_kW) / 3600;
		}
		return batteryRate;
    }
    
	/**
    * returns current consumption rate of AIP fuel
    */
    float tcSubDBObject::GetAIPRate(float speed_kts) const
	{
		if (!isAIP){return 0;}

		float hotel_load_hp = electricalLoadAdjustment * 10.72386;	//given in kwhr, converted to hp seconds.
		float move_cost_hp = pow(speed_kts * pow(Electric_ShaftHP,0.3333f) / mfMaxSpeed_kts,3.0f);
		float AIP_Expenditure_hp = std::min(hotel_load_hp + move_cost_hp,AIP_ShaftHP);
		float sustained_aip_speed = std::max(mfMaxSpeed_kts/pow(Electric_ShaftHP,0.3333f)*pow(AIP_ShaftHP,0.3333f),0.0f);
		float aip_rate = (1+std::max((std::min(speed_kts,sustained_aip_speed)/sustained_aip_speed-0.67f),0.0f))*AIP_Expenditure_hp/(AIP_ShaftHP-hotel_load_hp);
		return -aip_rate;
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
    
    float tcSubDBObject::GetAIPSpeed() const
    {
        return mfMaxSpeed_kts / pow(Electric_ShaftHP,0.3333f) * pow(AIP_ShaftHP,0.3333f);
    }
    

    /**
    * Adds sql column definitions to columnString. This is used for
    * SQL create table command
    */
    void tcSubDBObject::AddSqlColumns(std::string& columnString)
    {
        tcPlatformDBObject::AddSqlColumns(columnString);

        columnString += ",Length_m real,";
        columnString += "Beam_m real,";
        columnString += "Draft_m real,";
        columnString += "SurfaceSpeed_kts real";

        tcAirDetectionDBObject::AddSqlColumns(columnString); // Applies to surfaced sub
        tcWaterDetectionDBObject::AddSqlColumns(columnString);

        columnString += ",";
        
        columnString += "MaxDepth_m number(8),";
        columnString += "Primary_ShaftHP number(8),";
        columnString += "IsDieselElectric number(1),";
        columnString += "Electric_ShaftHP number(8),";
        columnString += "BatteryCapacityRated_kWhr number(8),";
        columnString += "BatteryRate_kW number(8),";
        columnString += "BatteryCharge_kW number(8)";
        columnString += "BatteryRatedHours number(8)";
        columnString += "BatteryPeukert number(8)";
		columnString += "IsAIP number(1),";
        columnString += "AIP_ShaftHP number(8),";
        columnString += "AIP_Capacity_kg number(8),";
        columnString += "AIP_Rate_kgps number(8),";
        columnString += "PropulsionShafts number(2),";
        columnString += "Electrical_Accel_ktsps number(8),";
        columnString += "AIP_Accel_ktsps number(8),";
        columnString += "ElectricalLoadAdjustement_kWps number(8),";
    }

    void tcSubDBObject::ReadSql(tcSqlReader& entry)
    {
        tcPlatformDBObject::ReadSql(entry);

        length_m = (float)entry.GetDouble("Length_m");
        beam_m = (float)entry.GetDouble("Beam_m");
        draft_m = (float)entry.GetDouble("Draft_m");
        surfaceSpeed_kts = (float)entry.GetDouble("SurfaceSpeed_kts");

        tcAirDetectionDBObject::ReadSql(entry);
        tcWaterDetectionDBObject::ReadSql(entry);

        mfMaxDepth_m = entry.GetDouble("MaxDepth_m");

		Primary_ShaftHP = entry.GetDouble("Primary_ShaftHP");
        isDieselElectric = entry.GetInt("IsDieselElectric") != 0;
		Electric_ShaftHP = entry.GetDouble("Electric_ShaftHP");
        batteryCapacityRated_kWhr = entry.GetDouble("BatteryCapacityRated_kWhr");
        batteryRate_kW = entry.GetDouble("BatteryRate_kW");
        batteryCharge_kW = entry.GetDouble("BatteryCharge_kW");
        batteryRatedHours = entry.GetDouble("BatteryRatedHours");
        batteryPeukert= entry.GetDouble("BatteryPeukert");
        isAIP = entry.GetInt("IsAIP") != 0;
		AIP_ShaftHP = entry.GetDouble("AIP_ShaftHP");
        AIP_Capacity_kg = entry.GetDouble("AIP_Capacity_kg");
        AIP_Rate_kgps = entry.GetDouble("AIP_Rate_kgps");
        PropulsionShafts = entry.GetInt("PropulsionShafts");
        electricalAcceleration_ktsps = entry.GetDouble("Electrical_Accel_ktsps");
        aipAcceleration_ktsps = entry.GetDouble("AIP_Accel_ktsps");
        electricalLoadAdjustment = entry.GetDouble("ElectricalLoadAdjustment_kWps");

        CalculateParams();
    }

    void tcSubDBObject::WriteSql(std::string& valueString)
    {
        tcPlatformDBObject::WriteSql(valueString);

        std::stringstream s2;
        s2 << ",";
        s2 << length_m << ",";
        s2 << beam_m << ",";
        s2 << draft_m << ",";
        s2 << surfaceSpeed_kts;
        valueString += s2.str();

        tcAirDetectionDBObject::WriteSql(valueString);
        tcWaterDetectionDBObject::WriteSql(valueString);

        std::stringstream s;
        s << ",";

        s << mfMaxDepth_m << ",";

        s << Primary_ShaftHP << ",";
        s << isDieselElectric << ",";
        s << Electric_ShaftHP << ",";
        s << batteryCapacityRated_kWhr << ",";
        s << batteryRate_kW << ",";
        s << batteryCharge_kW;
        s << batteryRatedHours;
        s << batteryPeukert;
        s << isAIP << ",";
        s << AIP_ShaftHP << ",";
        s << AIP_Capacity_kg << ",";
        s << AIP_Rate_kgps << ",";
        s << PropulsionShafts << ",";
        s << electricalAcceleration_ktsps << ",";
        s << aipAcceleration_ktsps << ",";
        s << electricalLoadAdjustment << ",";

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
        length_m(obj.length_m),
        beam_m(obj.beam_m),
        draft_m(obj.draft_m),
        surfaceSpeed_kts(obj.surfaceSpeed_kts),
        invMaxSpeed_mps(obj.invMaxSpeed_mps),
        invDraft_m(obj.invDraft_m),
        batteryDrainConstant(obj.batteryDrainConstant),
        mfMaxDepth_m(obj.mfMaxDepth_m),
        isDieselElectric(obj.isDieselElectric),
        batteryCapacityRated_kWhr(obj.batteryCapacityRated_kWhr),
        batteryRate_kW(obj.batteryRate_kW),
        batteryCharge_kW(obj.batteryCharge_kW),
        batteryRatedHours(obj.batteryRatedHours),
        batteryPeukert(obj.batteryPeukert),
		isAIP(obj.isAIP),
		Primary_ShaftHP(obj.Primary_ShaftHP),
		Electric_ShaftHP(obj.Electric_ShaftHP),
		AIP_ShaftHP(obj.AIP_ShaftHP),
		AIP_Capacity_kg(obj.AIP_Capacity_kg),
		AIP_Rate_kgps(obj.AIP_Rate_kgps),
		PropulsionShafts(obj.PropulsionShafts),
		electricalAcceleration_ktsps(obj.electricalAcceleration_ktsps),
		aipAcceleration_ktsps(obj.aipAcceleration_ktsps),
		electricalLoadAdjustment(obj.electricalLoadAdjustment)
    {
    }


    tcSubDBObject::~tcSubDBObject()
    {
    }


}