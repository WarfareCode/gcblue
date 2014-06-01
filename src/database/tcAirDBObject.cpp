/**
**  @file tcAirDBObject.cpp
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

#if _MSC_VER > 1000
#pragma warning(disable:4786) // suppress warning for STL bug in VC6, see Q167355 in the MSDN Library.
#endif

#include "tcAirDBObject.h"
#include "tcDatabase.h"
#include "tcFlightportDBObject.h"
#include "math_constants.h"
#include "randfn.h"
#include "CsvTranslator.h"
#include "tc3DModel.h"
#include "common/tinyxml.h"
#include "database/tcSqlReader.h"
#include <sstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;

namespace database
{

tcDatabaseObject* tcAirDBObject::AsDatabaseObject()
{
	return this;
}



/**
* Calculate private parameters. Should be called after
* object is loaded.
*/
void tcAirDBObject::CalculateParams()
{
    if (climbRate_mps <= 0)
    {
        fprintf(stderr, "tcAirDBObject -- %s, ClimbRate (%.1f) <= 0, defaulting to 15 m/s\n",
            tcDatabaseObject::GetName(), climbRate_mps);
        climbRate_mps = 15.0f;
    }
}


float tcAirDBObject::GetFuelConsumptionConstant(float speed_kts) const
{
	// Fuel burn penalty:
	// penalty = 0 for speed <= 0.7 max, above 0.7 penalty increases to 1 (2X) at max speed
	float excess_speed_penalty = 3.333f * ((speed_kts * invMaxSpeed) - 0.7f); 

	if (excess_speed_penalty < 0)
	{
		return fuelConsumptionConstant;
	}
	else
	{
		return fuelConsumptionConstant * (1.0 + excess_speed_penalty);
	}
}


float tcAirDBObject::GetRandomMaintenanceTime() const
{
    return maintenanceMin_s + randf() * (maintenanceMax_s - maintenanceMin_s);
}

bool tcAirDBObject::IsCarrierCompatible() const
{
    return isCarrierCompatible;
}


void tcAirDBObject::PrintToFile(tcFile& file) 
{
   tcPlatformDBObject::PrintToFile(file);
}


/**
* Adds sql column definitions to columnString. This is used for
* SQL create table command
*/
void tcAirDBObject::AddSqlColumns(std::string& columnString)
{
	tcPlatformDBObject::AddSqlColumns(columnString);
	
    tcAirDetectionDBObject::AddSqlColumns(columnString);
    tcWaterDetectionDBObject::AddSqlColumns(columnString);

	columnString += ",";
           
    columnString += "MaxTakeoffWeight_kg number(8),";
    columnString += "MaxAltitude_m number(8),";
    columnString += "ClimbRate_mps number(8),";
    columnString += "Gmax number(4),";
    columnString += "MinimumRunway_m numeric,";
    columnString += "IsCarrierCompatible number(2),";
    columnString += "OutFuelPods number(2),";
    columnString += "FuelOut_kgps number(5),";
    columnString += "FuelIn_kgps number(5),";
    columnString += "MaintenanceMin_s real,";
    columnString += "MaintenanceMax_s real";

}

void tcAirDBObject::ReadSql(tcSqlReader& entry)
{
	tcPlatformDBObject::ReadSql(entry);

	tcAirDetectionDBObject::ReadSql(entry);
	tcWaterDetectionDBObject::ReadSql(entry);

	maxTakeoffWeight_kg = entry.GetDouble("MaxTakeoffWeight_kg");
	maxAltitude_m = entry.GetDouble("MaxAltitude_m");
	climbRate_mps = entry.GetDouble("ClimbRate_mps");
    gmax = entry.GetDouble("Gmax");
    minimumRunway_m = entry.GetDouble("MinimumRunway_m");
	isCarrierCompatible = entry.GetInt("IsCarrierCompatible") != 0;
    outFuelPods = std::max(entry.GetInt("OutFuelPods"), 0); // don't allow negative values
    fuelOut_kgps = entry.GetDouble("FuelOut_kgps");
    fuelIn_kgps = entry.GetDouble("FuelIn_kgps");
    maintenanceMin_s = entry.GetDouble("MaintenanceMin_s");
    maintenanceMax_s = entry.GetDouble("MaintenanceMax_s");

    CalculateParams();
}


void tcAirDBObject::WriteSql(std::string& valueString)
{
	tcPlatformDBObject::WriteSql(valueString);

	tcAirDetectionDBObject::WriteSql(valueString);
	tcWaterDetectionDBObject::WriteSql(valueString);

	std::stringstream s;

	s << ",";
            
	s << maxTakeoffWeight_kg << ",";
	s << maxAltitude_m << ",";
	s << climbRate_mps << ",";
    s << gmax << ",";
    s << minimumRunway_m << ",";
	s << isCarrierCompatible << ",";
	s << outFuelPods << ",";
    s << fuelOut_kgps << ",";
    s << fuelIn_kgps << ",";
    s << maintenanceMin_s << ",";
    s << maintenanceMax_s;

	valueString += s.str();
}


tcAirDBObject::tcAirDBObject() : 
  tcPlatformDBObject(),
  tcAirDetectionDBObject(),
  tcWaterDetectionDBObject(),
  maxTakeoffWeight_kg(0),     
  maxAltitude_m(0),
  climbRate_mps(0),
  gmax(0),
  minimumRunway_m(0),
  isCarrierCompatible(false),
  outFuelPods(0),
  fuelOut_kgps(0),
  fuelIn_kgps(0),
  maintenanceMin_s(0),
  maintenanceMax_s(0)
{
   mnModelType = MTYPE_AIR;
}

tcAirDBObject::tcAirDBObject(const tcAirDBObject& obj)
: tcPlatformDBObject(obj), 
  tcAirDetectionDBObject(obj),
  tcWaterDetectionDBObject(obj),
  maxTakeoffWeight_kg(obj.maxTakeoffWeight_kg),     
  maxAltitude_m(obj.maxAltitude_m),
  climbRate_mps(obj.climbRate_mps),
  gmax(obj.gmax),
  minimumRunway_m(obj.minimumRunway_m),
  isCarrierCompatible(obj.isCarrierCompatible),
  outFuelPods(obj.outFuelPods),
  fuelOut_kgps(obj.fuelOut_kgps),
  fuelIn_kgps(obj.fuelIn_kgps),
  maintenanceMin_s(obj.maintenanceMin_s),
  maintenanceMax_s(obj.maintenanceMax_s)
{

}

tcAirDBObject::~tcAirDBObject() 
{
}

}
