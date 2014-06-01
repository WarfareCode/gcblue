/**  
**  @file tcWeaponDBObject.cpp
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
#endif // _MSC_VER > 1000

#include "tcWeaponDBObject.h"
#include "math_constants.h"
#include "randfn.h"
#include "CsvTranslator.h"
#include "common/tinyxml.h"
#include "database/tcSqlReader.h"
#include "tcDatabase.h"
#include "tcWeaponDamage.h"
#include <sstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;

namespace database
{

    void tcWeaponDBObject::PrintToFile(tcFile& file) 
    {
        char zBuff[128];

        tcDatabaseObject::PrintToFile(file);

        sprintf(zBuff,"   damage: %.1f \n", mfDamage);
        file.WriteString(zBuff);

        sprintf(zBuff,"   launch speed: %.1f mps \n", launchSpeed_mps);
        file.WriteString(zBuff);
    }

    /**
    * Adds sql column definitions to columnString. This is used for
    * SQL create table command
    */
    void tcWeaponDBObject::AddSqlColumns(std::string& columnString)
    {
        tcDatabaseObject::AddSqlColumns(columnString);

        columnString += ",";

        columnString += "Damage numeric,";
        columnString += "DamageModel text,";
        columnString += "DamageEffect text,";
        columnString += "LaunchSpeed_mps numeric,";
        columnString += "targetFlags numeric,";
	    columnString += "MinLaunchAlt_m numeric,";
	    columnString += "MaxLaunchAlt_m numeric,";
	    columnString += "MinRange_km numeric,";
	    columnString += "MaxRange_km numeric,";
        columnString += "ProbNoFaults real,";
        columnString += "PayloadClass text,";
		columnString += "PayloadQuantity numeric,";
        columnString += "DatalinkRange_km real,";
        columnString += "AcceptsUserCommands numeric,";
        columnString += "DetonationRange_m numeric";
    }

    void tcWeaponDBObject::ReadSql(tcSqlReader& entry)
    {
        tcDatabaseObject::ReadSql(entry);

        mfDamage = entry.GetDouble("Damage");
        damageModel = entry.GetString("DamageModel");
        damageEffect = entry.GetString("DamageEffect");
        launchSpeed_mps = entry.GetDouble("LaunchSpeed_mps");
        targetFlags = entry.GetInt("targetFlags");
        minLaunchAlt_m = entry.GetDouble("MinLaunchAlt_m");
        maxLaunchAlt_m = entry.GetDouble("MaxLaunchAlt_m");
        minRange_km = entry.GetDouble("MinRange_km");
        maxRange_km = entry.GetDouble("MaxRange_km");
        probNoFaults = entry.GetDouble("ProbNoFaults");
        payloadClass = entry.GetString("PayloadClass");
		payloadQuantity = (unsigned int)entry.GetLong("PayloadQuantity");
        datalinkRange_km = entry.GetDouble("DatalinkRange_km");
        acceptsUserCommands = entry.GetLong("AcceptsUserCommands") != 0;
        detonationRange_m = entry.GetDouble("DetonationRange_m");

		payloadQuantity = std::max(std::min(payloadQuantity, (unsigned int)16), (unsigned int)1);
    }

    void tcWeaponDBObject::WriteSql(std::string& valueString)
    {
        tcDatabaseObject::WriteSql(valueString);

        std::stringstream s;

        s << ",";

        s << mfDamage << ",";
        s << "'" << damageModel.c_str() << "',";
        s << "'" << damageEffect.c_str() << "',";
        s << launchSpeed_mps << ",";
        s << targetFlags << ",";
        s << minLaunchAlt_m << ",";
        s << maxLaunchAlt_m << ",";
        s << minRange_km << ",";
        s << maxRange_km << ",";
        s << probNoFaults << ",";
        s << "'" << payloadClass.c_str() << "',";
		s << payloadQuantity << ",";
        s << datalinkRange_km << ",";
        s << acceptsUserCommands << ",";
        s << detonationRange_m;

        valueString += s.str();
    }

    bool tcWeaponDBObject::IsNuclear() const
    {
        if (const tcWeaponDamage* weaponDamage = database->GetWeaponDamageData(damageModel))
        {
            return ((weaponDamage->blastCharge_kg + weaponDamage->radCharge_kg) > 500e3);
        }
        else
        {
            return false;
        }
    }


    tcWeaponDBObject::tcWeaponDBObject() : tcDatabaseObject(),
        mfDamage(1.0),
        damageModel(""),
        damageEffect(""),
        launchSpeed_mps(0),
        targetFlags(0),
        minLaunchAlt_m(0),
        maxLaunchAlt_m(0),
        minRange_km(0),
        maxRange_km(0),
        probNoFaults(1.0f),
        payloadClass(""),
		payloadQuantity(0),
        datalinkRange_km(0),
        acceptsUserCommands(false),
        detonationRange_m(0)
    {
        mzClass = "Default weapon";
    }

    tcWeaponDBObject::tcWeaponDBObject(const tcWeaponDBObject& obj) 
        :   tcDatabaseObject(obj),
            mfDamage(obj.mfDamage),
            damageModel(obj.damageModel),
            damageEffect(obj.damageEffect),
            launchSpeed_mps(obj.launchSpeed_mps),
            targetFlags(obj.targetFlags),
            minLaunchAlt_m(obj.minLaunchAlt_m),
            maxLaunchAlt_m(obj.maxLaunchAlt_m),
            minRange_km(obj.minRange_km),
            maxRange_km(obj.maxRange_km),
            probNoFaults(obj.probNoFaults),
            payloadClass(obj.payloadClass),
			payloadQuantity(obj.payloadQuantity),
            datalinkRange_km(obj.datalinkRange_km),
            acceptsUserCommands(obj.acceptsUserCommands),
            detonationRange_m(obj.detonationRange_m)
    {

    }

    tcWeaponDBObject::~tcWeaponDBObject() 
    {
    }

}

