/*  
**  @file tcBallisticMissileDBObject.cpp
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


#include "tcBallisticMissileDBObject.h"
#include "math_constants.h"
#include "randfn.h"
#include "CsvTranslator.h"
#include "tcDatabase.h"
#include "common/tinyxml.h"
#include "database/tcSqlReader.h"
#include "tcAirDetectionDBObject.h"
#include "tcAero.h"
#include <sstream>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;

namespace database
{

    void tcBallisticMissileDBObject::CalculateParams()
    {
        const float minBC = 0.001f;
        bcStage1 = std::max(bcStage1, minBC);
        bcStage2 = std::max(bcStage2, minBC);
        bcStage3 = std::max(bcStage3, minBC);
        bcStage4 = std::max(bcStage4, minBC);

        inv_bcStage1 = 1.0f / bcStage1;
        inv_bcStage2 = 1.0f / bcStage2;
        inv_bcStage3 = 1.0f / bcStage3;
        inv_bcStage4 = 1.0f / bcStage4;

        float t1 = timeStage1_s;
        float t2 = t1 + timeStage2_s;
        float t3 = t2 + timeStage3_s;
        float t4 = t3 + timeStage4_s;

        if (accelStage4_mps2 > 0)
        {
            thrustShutoffTime_s = t4;
        }
        else if (accelStage3_mps2 > 0)
        {
            thrustShutoffTime_s = t3;
        }
        else if (accelStage2_mps2 > 0)
        {
            thrustShutoffTime_s = t2;
        }
        else
        {
            thrustShutoffTime_s = t1;
        }
    }


    /**
    * Adds sql column definitions to columnString. This is used for
    * SQL create table command
    */
    void tcBallisticMissileDBObject::AddSqlColumns(std::string& columnString)
    {
        tcWeaponDBObject::AddSqlColumns(columnString);

        tcAirDetectionDBObject::AddSqlColumns(columnString);

        columnString += ",";

        columnString += "Gmax numeric,";

        columnString += "TimeStage1_s,";
        columnString += "AccelStage1_mps2,";
        columnString += "BCStage1,";

        columnString += "TimeStage2_s,";
        columnString += "AccelStage2_mps2,";
        columnString += "BCStage2,";

        columnString += "TimeStage3_s,";
        columnString += "AccelStage3_mps2,";
        columnString += "BCStage3,";

        columnString += "TimeStage4_s,";
        columnString += "AccelStage4_mps2,";
        columnString += "BCStage4";
    }

    teWeaponLaunchMode tcBallisticMissileDBObject::GetLaunchMode() const
    {
        return DATUM_ONLY;
    }

    void tcBallisticMissileDBObject::ReadSql(tcSqlReader& entry)
    {
        tcWeaponDBObject::ReadSql(entry);
        tcAirDetectionDBObject::ReadSql(entry);

        gmax = entry.GetDouble("Gmax");

        timeStage1_s = entry.GetDouble("TimeStage1_s");
        accelStage1_mps2 = entry.GetDouble("AccelStage1_mps2");
        bcStage1 = entry.GetDouble("BCStage1");

        timeStage2_s = entry.GetDouble("TimeStage2_s");
        accelStage2_mps2 = entry.GetDouble("AccelStage2_mps2");
        bcStage2 = entry.GetDouble("BCStage2");

        timeStage3_s = entry.GetDouble("TimeStage3_s");
        accelStage3_mps2 = entry.GetDouble("AccelStage3_mps2");
        bcStage3 = entry.GetDouble("BCStage3");

        timeStage4_s = entry.GetDouble("TimeStage4_s");
        accelStage4_mps2 = entry.GetDouble("AccelStage4_mps2");
        bcStage4 = entry.GetDouble("BCStage4");

        CalculateParams();
    }

    void tcBallisticMissileDBObject::WriteSql(std::string& valueString)
    {
        tcWeaponDBObject::WriteSql(valueString);
        tcAirDetectionDBObject::WriteSql(valueString);

        std::stringstream s;

        s << ",";

        s << gmax << ",";

        s << timeStage1_s << ",";
        s << accelStage1_mps2 << ",";
        s << bcStage1 << ",";

        s << timeStage2_s << ",";
        s << accelStage2_mps2 << ",";
        s << bcStage2 << ",";

        s << timeStage3_s << ",";
        s << accelStage3_mps2 << ",";
        s << bcStage3 << ",";

        s << timeStage4_s << ",";
        s << accelStage4_mps2 << ",";
        s << bcStage4;

        valueString += s.str();
    }


    tcBallisticMissileDBObject::tcBallisticMissileDBObject(const tcBallisticMissileDBObject& obj) 
        : tcWeaponDBObject(obj),
        tcAirDetectionDBObject(obj),
        gmax(obj.gmax),
        timeStage1_s(obj.timeStage1_s),
        accelStage1_mps2(obj.accelStage1_mps2),
        bcStage1(obj.bcStage1),
        timeStage2_s(obj.timeStage2_s),
        accelStage2_mps2(obj.accelStage2_mps2),
        bcStage2(obj.bcStage2),
        timeStage3_s(obj.timeStage3_s),
        accelStage3_mps2(obj.accelStage3_mps2),
        bcStage3(obj.bcStage3),
        timeStage4_s(obj.timeStage4_s),
        accelStage4_mps2(obj.accelStage4_mps2),
        bcStage4(obj.bcStage4)
    {
        mnModelType = MTYPE_BALLISTICMISSILE;

        CalculateParams();
    }

    tcBallisticMissileDBObject::tcBallisticMissileDBObject() : tcWeaponDBObject(), tcAirDetectionDBObject(),
        gmax(0),
        timeStage1_s(0),
        accelStage1_mps2(0),
        bcStage1(0),
        timeStage2_s(0),
        accelStage2_mps2(0),
        bcStage2(0),
        timeStage3_s(0),
        accelStage3_mps2(0),
        bcStage3(0),
        timeStage4_s(0),
        accelStage4_mps2(0),
        bcStage4(0)
    {
        mnModelType = MTYPE_BALLISTICMISSILE;
        mnType = PTYPE_MISSILE;
    }

    tcBallisticMissileDBObject::~tcBallisticMissileDBObject() 
    {
    }

} // namespace database

