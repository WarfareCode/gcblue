/**  
**  @file tcCounterMeasureDBObject.cpp
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

//#if _MSC_VER > 1000
//#pragma warning(disable:4786) // suppress warning for STL bug in VC6, see Q167355 in the MSDN Library.
//#endif // _MSC_VER > 1000

#include "tcCounterMeasureDBObject.h"
#include "math_constants.h"
#include "randfn.h"
#include "CsvTranslator.h"
#include "common/tinyxml.h"
#include "database/tcSqlReader.h"
#include <sstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



namespace database
{

    void tcCounterMeasureDBObject::PrintToFile(tcFile& file) 
    {
        char zBuff[128];

        tcDatabaseObject::PrintToFile(file);

        sprintf(zBuff,"   CM: No data yet \n");
        file.WriteString(zBuff);
    }

    /**
    * Adds sql column definitions to columnString. This is used for
    * SQL create table command
    */
    void tcCounterMeasureDBObject::AddSqlColumns(std::string& columnString)
    {
        tcDatabaseObject::AddSqlColumns(columnString);

        columnString += ",";

        columnString += "SubType varchar(20),";
        columnString += "LifeSpan_s number(5),";
        columnString += "Effectiveness number(5),";
        columnString += "MaxSpeed_mps number(5),";

        tcAirDetectionDBObject::AddSqlColumns(columnString);
        tcWaterDetectionDBObject::AddSqlColumns(columnString);
    }


    /**
    * Call once after object is loaded from db
    */
    void tcCounterMeasureDBObject::CalculateParams()
    {
        if (maxSpeed_mps > 0)
        {
            airDragFactor = C_G / (maxSpeed_mps * maxSpeed_mps);
        }
        else
        {
            wxASSERT(false); // bad data
            fprintf(stderr, "tcCounterMeasureDBObject::CalculateParams() -- %s invalid MaxSpeed_mps (%f)\n",
                mzClass.c_str(), maxSpeed_mps);
            airDragFactor = 0.1f;
        }

		isFlare = ((subType == "Flare") || (subType == "WaterFlare"));
    }

    float tcCounterMeasureDBObject::GetAirDragFactor() const
    {
        return airDragFactor;
    }

	bool tcCounterMeasureDBObject::IsFlare() const
	{
		return isFlare;
	}

    void tcCounterMeasureDBObject::ReadSql(tcSqlReader& entry)
    {
        tcDatabaseObject::ReadSql(entry);

        subType = entry.GetString("SubType").c_str();
        lifeSpan_s = entry.GetDouble("LifeSpan_s");
        effectiveness = entry.GetDouble("Effectiveness");
        maxSpeed_mps = entry.GetDouble("MaxSpeed_mps");

        tcAirDetectionDBObject::ReadSql(entry);
        tcWaterDetectionDBObject::ReadSql(entry);

        CalculateParams();
    }

    void tcCounterMeasureDBObject::WriteSql(std::string& valueString)
    {
        tcDatabaseObject::WriteSql(valueString);

        std::stringstream s;

        s << ",";

        s << "'" << subType.c_str() << "',";
        s << lifeSpan_s << ",";
        s << effectiveness << ",";
        s << maxSpeed_mps << ",";

        valueString += s.str();

        tcAirDetectionDBObject::WriteSql(valueString);
        tcWaterDetectionDBObject::WriteSql(valueString);
    }


    tcCounterMeasureDBObject::tcCounterMeasureDBObject() : tcDatabaseObject(),
        tcAirDetectionDBObject(),
        tcWaterDetectionDBObject(),
        subType(""),
        lifeSpan_s(0),
        effectiveness(0),
        maxSpeed_mps(0),
        airDragFactor(1.0f),
		isFlare(false)
    {
        mzClass = "Default CM";
    }

    tcCounterMeasureDBObject::tcCounterMeasureDBObject(const tcCounterMeasureDBObject& obj) 
      : tcDatabaseObject(obj),
        tcAirDetectionDBObject(obj),
        tcWaterDetectionDBObject(obj),
        subType(obj.subType),
        lifeSpan_s(obj.lifeSpan_s),
        effectiveness(obj.effectiveness),
        maxSpeed_mps(obj.maxSpeed_mps),
        airDragFactor(obj.airDragFactor),
		isFlare(obj.isFlare)
    {

    }

    tcCounterMeasureDBObject::~tcCounterMeasureDBObject() 
    {
    }

}

