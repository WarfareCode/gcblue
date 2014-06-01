/**
**  @file tcAcousticModel.cpp
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


#include "tcAcousticModel.h"
#include "database/tcSqlReader.h"
#include "math_constants.h"

#include <sstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;

namespace database
{


/**
* Adds sql column definitions to columnString. This is used for
* SQL create table command
*/
void tcAcousticModel::AddSqlColumns(std::string& columnString)
{
    columnString += "DatabaseClass text primary key,";

    columnString += "Speed1_kts real,";
    columnString += "SL1 real,";
    columnString += "Speed2_kts real,";
    columnString += "SL2 real,";
    columnString += "Speed3_kts real,";
    columnString += "SL3 real,";
    columnString += "Speed4_kts real,";
    columnString += "SL4 real,";

    columnString += "SpeedMinNL_kts real,";
	columnString += "NL_min real,";
    columnString += "SpeedMaxNL_kts real,";
	columnString += "NL_max real,";

    columnString += "CavitationOffset_kts real,";
    columnString += "CavitationSlope_ktsperft real,";
    columnString += "CavitationSL real,";
    columnString += "SnorkelingSL real";
}

/**
* Build lookup table for SL vs. speed table
*/
void tcAcousticModel::BuildSLTable()
{    
    std::vector<float> invDiffs; // 1 / (xSpeed_kts[n+1] - xSpeed_kts[n])
    for (size_t n=1; n<4; n++)
    {
        wxASSERT(xSpeed_kts[n] > xSpeed_kts[n-1]);
        if (ySL_dB[n] < ySL_dB[n-1])
        {
			fprintf(stderr, "tcAcousticModel (%s) -- SL must be non-decreasing, values were increased\n", databaseClass.c_str());
            ySL_dB[n] = ySL_dB[n-1]; // force non-decreasing SL vs speed
        }

        invDiffs.push_back(1.0f / (xSpeed_kts[n] - xSpeed_kts[n-1]));
    }
    
    for (int n=0; n<SL_TABLE_SIZE; n++)
    {
        float speed_kts = float(n) * dv_kts;
        float val = 0;
        if (speed_kts < xSpeed_kts[0])
        {
            val = ySL_dB[0];
        }
        else if (speed_kts < xSpeed_kts[1])
        {
            val = ySL_dB[0] + ((ySL_dB[1] - ySL_dB[0])*(speed_kts - xSpeed_kts[0]) * invDiffs[0]);
        }
        else if (speed_kts < xSpeed_kts[2])
        {
            val = ySL_dB[1] + ((ySL_dB[2] - ySL_dB[1])*(speed_kts - xSpeed_kts[1]) * invDiffs[1]);
        }
        else if (speed_kts < xSpeed_kts[3])
        {
            val = ySL_dB[2] + ((ySL_dB[3] - ySL_dB[2])*(speed_kts - xSpeed_kts[2]) * invDiffs[2]);
        }
        else
        {
            val = ySL_dB[3];
        }
        SL_dB[n] = val;
    }
}

/**
* @return minimum depth in m to avoid cavitation at speed_kts
*/
float tcAcousticModel::GetCavitationDepth(float speed_kts) const
{
    return std::max(invCavitationSlope_mperkts * (speed_kts - cavitationOffset_kts), 0.0f);
}

float tcAcousticModel::GetCavitationSpeedKts(float depth_m) const
{
    return cavitationOffset_kts + (cavitationSlope_ktsperm*depth_m);
}

const char* tcAcousticModel::GetName() const
{
    return databaseClass.c_str();
}

float tcAcousticModel::GetNoiseLevelForSpeed(float speed_mps) const
{
    return GetNoiseLevelForSpeedKts(C_MPSTOKTS*speed_mps);
}

float tcAcousticModel::GetNoiseLevelForSpeedKts(float speed_kts) const
{
    bool bBelowMin = speed_kts < speedMinNL_kts;
    bool bAboveMax = speed_kts > speedMaxNL_kts;
    bool bInRange = (!bBelowMin) && (!bAboveMax);

    float belowMin = float(bBelowMin);
    float aboveMax = float(bAboveMax);
    float inRange = float(bInRange);

    wxASSERT((belowMin + aboveMax + inRange) == 1.0f);

    float NL = belowMin*NL_min + aboveMax*NL_max + inRange*((speed_kts-speedMinNL_kts)*NL_slope + NL_min);

    return NL;
}

float tcAcousticModel::GetSourceLevel(float speed_kts, float depth_m) const
{
    if (speed_kts < GetCavitationSpeedKts(depth_m))
    {
        return GetVelocitySL(speed_kts);
    }
    else
    {
        return cavitationSL_dB;
    }
}

float tcAcousticModel::GetSourceLevelSnorkeling() const
{
    return snorkelingSL_dB;
}

/**
* Internal method to calculate SL from lookup table
*/
float tcAcousticModel::GetVelocitySL(float speed_kts) const
{
    int bin = int(floorf((one_over_dv*speed_kts) + 0.5f));
    bin = std::min(std::max(bin, 0), SL_TABLE_SIZE - 1);

    return SL_dB[bin];
}

void tcAcousticModel::ReadSql(tcSqlReader& entry)
{
    databaseClass = entry.GetString("DatabaseClass").c_str();


    xSpeed_kts.clear();
    ySL_dB.clear();

    for (int n=1; n<=4; n++)
    {
        wxString s_speed = wxString::Format("Speed%d_kts", n);
        wxString s_SL = wxString::Format("SL%d", n);

        xSpeed_kts.push_back(float(entry.GetDouble(s_speed.c_str())));
        ySL_dB.push_back(float(entry.GetDouble(s_SL.c_str())));
    }

    speedMinNL_kts = entry.GetDouble("SpeedMinNL_kts");
	NL_min = entry.GetDouble("NL_min");
    speedMaxNL_kts = entry.GetDouble("SpeedMaxNL_kts");
	NL_max = entry.GetDouble("NL_max");

    cavitationOffset_kts = entry.GetDouble("CavitationOffset_kts");
    cavitationSlope_ktsperft = entry.GetDouble("CavitationSlope_ktsperft");
    cavitationSL_dB = entry.GetDouble("CavitationSL");
    snorkelingSL_dB = entry.GetDouble("SnorkelingSL");

    // calculated parameters
    cavitationSlope_ktsperm = C_MTOFT * cavitationSlope_ktsperft;
    invCavitationSlope_mperkts = 1.0f / (cavitationSlope_ktsperm + 0.000001f);

    invSpeedRange_kts = 1.0 / (speedMaxNL_kts - speedMinNL_kts);
    NL_slope = (NL_max - NL_min) * invSpeedRange_kts;

    BuildSLTable();
    
}

void tcAcousticModel::WriteSql(std::string& valueString)
{
	std::stringstream s;

    s << "'" << databaseClass.c_str() << "'";

	s << ",";

    for (int n=0; n<4; n++)
    {
        s << xSpeed_kts[n] << ",";
        s << ySL_dB[n] << ",";
    }

    s << speedMinNL_kts << ",";
    s << NL_min << ",";
    s << speedMaxNL_kts << ",";
    s << NL_max << ",";

    s << cavitationOffset_kts << ",";
    s << cavitationSlope_ktsperft << ",";
    s << cavitationSL_dB << ",";
    s << snorkelingSL_dB;
	
	valueString += s.str();
}


tcAcousticModel::tcAcousticModel()
: speedMinNL_kts(0),
  NL_min(0),
  speedMaxNL_kts(1),
  NL_max(0),
  cavitationOffset_kts(0),
  cavitationSlope_ktsperft(0),
  cavitationSlope_ktsperm(0),
  invCavitationSlope_mperkts(0),
  cavitationSL_dB(0),
  snorkelingSL_dB(0),
  dv_kts(0.25f),
  one_over_dv(4.0f)
{

}

tcAcousticModel::tcAcousticModel(const tcAcousticModel& obj)
:   speedMinNL_kts(obj.speedMinNL_kts),
    NL_min(obj.NL_min),
    speedMaxNL_kts(obj.speedMaxNL_kts),
    NL_max(obj.NL_max),
    cavitationOffset_kts(obj.cavitationOffset_kts),
    cavitationSlope_ktsperft(obj.cavitationSlope_ktsperft),
    cavitationSL_dB(obj.cavitationSL_dB),
    snorkelingSL_dB(obj.snorkelingSL_dB),
    cavitationSlope_ktsperm(obj.cavitationSlope_ktsperm),
    invCavitationSlope_mperkts(obj.invCavitationSlope_mperkts),
    dv_kts(obj.dv_kts),
    one_over_dv(obj.one_over_dv),
    invSpeedRange_kts(obj.invSpeedRange_kts),
    NL_slope(obj.NL_slope)
{
    for (size_t n=0; n<4; n++)
    {
        xSpeed_kts.push_back(obj.xSpeed_kts[n]);
        ySL_dB.push_back(obj.ySL_dB[n]);
    }

    for (size_t n=0; n<SL_TABLE_SIZE; n++)
    {
        SL_dB[n] = obj.SL_dB[n];
    }
}

tcAcousticModel::~tcAcousticModel() 
{
}

}
