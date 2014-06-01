/** 
**  @file tcSonarDBObject.cpp
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

#include "tcSonarDBObject.h"
#include "tcSonar.h"
#include "common/tinyxml.h"
#include "database/tcSqlReader.h"
#include <sstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

namespace database
{

    /**
    * Calculate parameters based on database values.
    * e.g. alpha, attenuation coefficient
    */
    void tcSonarDBObject::CalculateParams()
    {
        // Thorp eqn
        //averageFreq_Hz = 0.5 * (minFrequency_Hz + maxFrequency_Hz);
        //if (averageFreq_Hz <= 0) averageFreq_Hz = 2000.0f;

        averageFreq_Hz = 1000.0f; // simplified 4 JUL 2009, everything at 2 kHz
        // 17OCT2009, everything referenced to 1 kHz, easier to explain, better compromise between active and passive, slightly lower atten

        float freq_avg_kHz = 0.001f * averageFreq_Hz;
        
        float f2 = freq_avg_kHz * freq_avg_kHz;

        alpha = (0.1f * f2 / (1.0 + f2)) + 
                (40.0f * f2 / (4100.0f + f2)) +
                (2.75e-4f * f2) +
                0.003;

        alpha *= 1.0936133f; // convert dB/kyd to dB/km

        if (rangeError <= 0) rangeError = 1.5f; // 0 previously interpreted as active sensor with perfect range, now 0 < x <= 1 is passive, > 1 is active
    }

    tcSensorState* tcSonarDBObject::CreateSensor(tcGameObject* parent)
    {
        tcSonar* sonar = new tcSonar(this);
        sonar->SetParent(parent);

        return sonar;
    }


    const char* tcSonarDBObject::GetTypeDescription() const
    {
        static wxString s;

        s = "Sonar";

        if (isActive) s += " Active";
        if (isPassive) s += " Passive";

        if (isTowed) s += " Towed";

        return s.c_str();
    }

    /**
    *
    */
    void tcSonarDBObject::PrintToFile(tcFile& file) 
    {
        tcString s;

        tcSensorDBObject::PrintToFile(file);

        s.Format("   SL: %f, passive: %d, alpha: %f dB/km\n", SL, isPassive, alpha);
        file.WriteString(s.GetBuffer());
    }

   

    /**
    * Adds sql column definitions to columnString. This is used for
    * SQL create table command
    */
    void tcSonarDBObject::AddSqlColumns(std::string& columnString)
    {
        tcSensorDBObject::AddSqlColumns(columnString);

        columnString += ",";

        columnString += "SL number(4),";
        columnString += "DI number(4),";
        /*columnString += "minFrequency_Hz number(5),";
        columnString += "maxFrequency_Hz number(5),";*/
        columnString += "isPassive number(1),";
        columnString += "isActive number(1),";
        columnString += "isTowed number(1),";
        columnString += "maxScope_m number(4),";
        columnString += "isWakeHoming number(1)";
    }

    void tcSonarDBObject::ReadSql(tcSqlReader& entry)
    {
        tcSensorDBObject::ReadSql(entry);

        SL = entry.GetDouble("SL");
        DI = entry.GetDouble("DI");
        /*minFrequency_Hz = entry.GetDouble("minFrequency_Hz");
        maxFrequency_Hz = entry.GetDouble("maxFrequency_Hz");*/
        isPassive = entry.GetInt("isPassive") != 0;

        isActive = entry.GetInt("isActive") != 0;
        isTowed = entry.GetInt("isTowed") != 0;
        maxScope_m = entry.GetDouble("maxScope_m");
        isWakeHoming = entry.GetInt("isWakeHoming") != 0;

        CalculateParams();
    }

    void tcSonarDBObject::WriteSql(std::string& valueString)
    {
        tcSensorDBObject::WriteSql(valueString);

        std::stringstream s;

        s << ",";

        s << SL << ",";
        s << DI << ",";
        /*s << minFrequency_Hz << ",";
        s << maxFrequency_Hz << ",";*/
        s << (long)isPassive << ",";

        s << (long)isActive << ",";
        s << (long)isTowed << ",";
        s << maxScope_m << ",";
        s << (long)isWakeHoming;

        valueString += s.str();
    }

    tcSonarDBObject::tcSonarDBObject() : tcSensorDBObject(),
        SL(10),
        DI(3),
        minFrequency_Hz(1000.0f),
        maxFrequency_Hz(1000.0f),
        isPassive(false),
        isActive(true),
        isTowed(false),
        maxScope_m(0),
        isWakeHoming(false)
    {
        mzClass = "Default Sonar";
        mfMaxRange_km = 10.0f;
        mfRefRange_km = 1.0f;
        mfFieldOfView_deg = 90.0f;
        mfScanPeriod_s = 4.0f;

        CalculateParams();
    }

    tcSonarDBObject::tcSonarDBObject(tcSonarDBObject& obj) 
        : tcSensorDBObject(obj),
        SL(obj.SL),
        DI(obj.DI),
        minFrequency_Hz(obj.minFrequency_Hz),
        maxFrequency_Hz(obj.maxFrequency_Hz),
        isPassive(obj.isPassive),
        isActive(obj.isActive),
        isTowed(obj.isTowed),
        maxScope_m(obj.maxScope_m),
        isWakeHoming(obj.isWakeHoming)
    {
        CalculateParams();
    }

    tcSonarDBObject::~tcSonarDBObject() 
    {
    }


}

