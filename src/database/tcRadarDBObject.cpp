/** 
**  @file tcRadarDBObject.cpp
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

#include "tcRadarDBObject.h"
//#include "math_constants.h"
//#include "randfn.h"
#include "CsvTranslator.h"
#include "common/tinyxml.h"
#include "database/tcSqlReader.h"
#include <sstream>
#include "tcRadar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

namespace database
{




tcSensorState* tcRadarDBObject::CreateSensor(tcGameObject* parent)
{
    tcRadar* radar = new tcRadar(this);
	radar->SetParent(parent);
	
	return radar;
}

void tcRadarDBObject::CalculateParams()
{
    invBlindSpeed_mps = (blindSpeed_mps > 0) ? 1.0f / blindSpeed_mps : 0.0f;

    bandwidth_Hz = std::max(bandwidth_Hz, 0.1e6f); // don't allow bandwidth less than 0.1 MHz to avoid divide by zero and neg number problems

    effectiveSidelobes_dB = std::min(-fabsf(effectiveSidelobes_dB), -15.0f); // don't allow sidelobes higher than -15 dB, convert pos SLL to negative dB

    elevationBeamwidth_deg = std::max(elevationBeamwidth_deg, 0.1f);
    azimuthBeamwidth_deg = std::max(azimuthBeamwidth_deg, 0.1f);

    invAzBeamwidth_deg = 1.0f / azimuthBeamwidth_deg;
    invElBeamwidth_deg = 1.0f / elevationBeamwidth_deg;

    antennaGain = C_TWOPI / (sinf(0.5f*C_PIOVER180*elevationBeamwidth_deg) * C_PIOVER180*azimuthBeamwidth_deg);
    antennaGain_dBi = 10.0f * log10f(antennaGain);

    rangeError = std::max(rangeError, 1.0f); // range error in meters, set lower bound of 1 m

    float lambda2 = 1.0f;
    float FL_dB = CalculateFL(lambda2);
    FL_dB = std::max(FL_dB, 10.0f);

    jamConstant_dB = 10*log10f(lambda2 / (C_FOURPI * 1.38e-23f * 300.0f * bandwidth_Hz)) - FL_dB;
}

float tcRadarDBObject::CalculateFL(float& lambda2)
{
    float lambda_m = C_CLIGHT_MPS / averageFrequency_Hz;

    float coverageSolidAngle = (sinf(maxElevation_rad) - sinf(minElevation_rad)) * mfFieldOfView_deg * C_PIOVER180;
    float beamSolidAngle = 2*sinf(elevationBeamwidth_deg * 0.5f * C_PIOVER180) * (azimuthBeamwidth_deg * C_PIOVER180);
    float nBeams = coverageSolidAngle / beamSolidAngle;
    if (_isnan(nBeams) || (nBeams <= 0))
    {
        nBeams = 1.0f;
        wxASSERT(false);
    }
    cpi_s = mfScanPeriod_s / nBeams;

    const float A = 4.1077e-016f; // 100 * (4*pi)^3 * kT, 50 (17 dB) is detection threshold
    const float B = 1e12f; // convert km^4 to m^4
    float range2 = mfRefRange_km * mfRefRange_km;
    float range4 = B*range2 * range2;
    
    lambda2 = lambda_m * lambda_m;
    float FL_dB = ERPaverage_dBW + antennaGain_dBi + 10*log10f(cpi_s*lambda2/(A*range4));

    return FL_dB;
}


float tcRadarDBObject::EstimateDetectionRange(float rcs_dBsm, bool overWater, bool overLand) const
{
	float rcsEffective_dBsm = rcs_dBsm + float(overWater)*lookdownWater_dB + float(overLand)*lookdownLand_dB;

	return mfRefRange_km * powf(10.0f, 0.025f*rcsEffective_dBsm);
}

const char* tcRadarDBObject::GetTypeDescription() const
{
    static wxString s;

    if (isSurveillance)
    {
        s = "Radar ";
        if (mbDetectsAir)
        {
            s += "Air";
            if (mbDetectsSurface) s += "-Surf";
            if (mbDetectsGround) s += "-Gnd";
        }
        else if (mbDetectsSurface)
        {
            s += "Surf";
            if (mbDetectsGround) s += "-Gnd";
        }
        else if (mbDetectsGround)
        {
            s += "Ground";
        }
    }
    else
    {
        s = "Radar ";    
        if (mbDetectsAir) s += "Air ";
        if (mbDetectsMissile) s += "Mis ";
        if (mbDetectsSurface) s += "Surf ";
        if (mbDetectsGround) s += "Gnd ";
        s += "FC";
    }



    return s.c_str();
}

/**
*
*/
void tcRadarDBObject::PrintToFile(tcFile& file) 
{
   tcString s;
   
   tcDatabaseObject::PrintToFile(file);
   
   s.Format("   ref range: %3.1f km\n",mfRefRange_km);
   file.WriteString(s.GetBuffer());
}

/**
* Adds sql column definitions to columnString. This is used for
* SQL create table command
*/
void tcRadarDBObject::AddSqlColumns(std::string& columnString)
{
	tcSensorDBObject::AddSqlColumns(columnString);

	columnString += ",";

	columnString +=  "ERPpeak_dBW number(3),";
    columnString +=  "ERPaverage_dBW number(3),";
	columnString +=  "MaxFireControlTracks number(3),";
	columnString +=  "IsSemiactive number(1),";
    columnString +=  "BlindSpeed_mps number(5),";
    columnString +=  "LookdownWater_dB number(3),";
    columnString +=  "LookdownLand_dB number(3),";
    columnString +=  "Bandwidth_Hz numeric,";
    columnString +=  "AzimuthBeamwidth_deg numeric,";
    columnString +=  "ElevationBeamwidth_deg number(4),";
    columnString +=  "EffectiveSidelobes_dB numeric,";
	columnString +=  "DetectsSurface number(1),";
	columnString +=  "DetectsAir number(1),";
	columnString +=  "DetectsMissile number(1),";
	columnString +=  "DetectsGround number(1)";
}

void tcRadarDBObject::ReadSql(tcSqlReader& entry)
{
	tcSensorDBObject::ReadSql(entry);

	ERPpeak_dBW = entry.GetDouble("ERPpeak_dBW");
    ERPaverage_dBW = entry.GetDouble("ERPaverage_dBW");
	maxFireControlTracks = entry.GetInt("MaxFireControlTracks");
	isSemiactive = entry.GetInt("IsSemiactive") != 0;
    blindSpeed_mps = entry.GetDouble("BlindSpeed_mps");
    lookdownWater_dB = entry.GetDouble("LookdownWater_dB");
    lookdownLand_dB = entry.GetDouble("LookdownLand_dB");
    bandwidth_Hz = entry.GetDouble("Bandwidth_Hz");
    azimuthBeamwidth_deg = entry.GetDouble("AzimuthBeamwidth_deg");
    elevationBeamwidth_deg = entry.GetDouble("ElevationBeamwidth_deg");
    effectiveSidelobes_dB = entry.GetDouble("EffectiveSidelobes_dB");
	mbDetectsSurface = entry.GetInt("DetectsSurface") != 0;
	mbDetectsAir = entry.GetInt("DetectsAir") != 0;
	mbDetectsMissile = entry.GetInt("DetectsMissile") != 0;
	mbDetectsGround = entry.GetInt("DetectsGround") != 0;

    CalculateParams();
}

void tcRadarDBObject::WriteSql(std::string& valueString)
{
	tcSensorDBObject::WriteSql(valueString);

	std::stringstream s;

	s << ",";

	s << ERPpeak_dBW << ",";
    s << ERPaverage_dBW << ",";
	s << (long)maxFireControlTracks << ",";
	s << (long)isSemiactive << ",";
    s << blindSpeed_mps << ",";
    s << lookdownWater_dB << ",";
    s << lookdownLand_dB << ",";
    s << bandwidth_Hz << ",";
    s << azimuthBeamwidth_deg << ",";
    s << elevationBeamwidth_deg << ",";
    s << effectiveSidelobes_dB << ",";
	s << (long)mbDetectsSurface << ",";
	s << (long)mbDetectsAir << ",";
	s << (long)mbDetectsMissile << ",";
	s << (long)mbDetectsGround;

	valueString += s.str();

}

tcRadarDBObject::tcRadarDBObject() : tcSensorDBObject(),
    ERPpeak_dBW(0),
    ERPaverage_dBW(0),
	maxFireControlTracks(0),
	isSemiactive(false),
    blindSpeed_mps(0),
    lookdownWater_dB(0),
    lookdownLand_dB(0),
    bandwidth_Hz(2e6f),
    azimuthBeamwidth_deg(1.0f),
    elevationBeamwidth_deg(1.0f),
    effectiveSidelobes_dB(-30.0f),
	mbDetectsSurface(false),
	mbDetectsAir(false),
	mbDetectsMissile(false),
	mbDetectsGround(false),
    invBlindSpeed_mps(0),
    invAzBeamwidth_deg(0),
    invElBeamwidth_deg(0),
    antennaGain(1.0f),
    antennaGain_dBi(0),
    cpi_s(0.01f)
{
   mzClass = "Default Radar";
}

tcRadarDBObject::tcRadarDBObject(const tcRadarDBObject& obj) 
	: 
	tcSensorDBObject(obj), 
	ERPpeak_dBW(obj.ERPpeak_dBW),
    ERPaverage_dBW(obj.ERPaverage_dBW),
	maxFireControlTracks(obj.maxFireControlTracks),
	isSemiactive(obj.isSemiactive),
    blindSpeed_mps(obj.blindSpeed_mps),
    lookdownWater_dB(obj.lookdownWater_dB),
    lookdownLand_dB(obj.lookdownLand_dB),
    bandwidth_Hz(obj.bandwidth_Hz),
    azimuthBeamwidth_deg(obj.azimuthBeamwidth_deg),
    elevationBeamwidth_deg(obj.elevationBeamwidth_deg),
    effectiveSidelobes_dB(obj.effectiveSidelobes_dB),
	mbDetectsSurface(obj.mbDetectsSurface),
	mbDetectsAir(obj.mbDetectsAir),
	mbDetectsMissile(obj.mbDetectsMissile),
	mbDetectsGround(obj.mbDetectsGround)
{
    CalculateParams();
}

tcRadarDBObject::~tcRadarDBObject() 
{
}


}

