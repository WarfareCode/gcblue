/**
**  @file tcAirDetectionDBObject.cpp
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


#include "tcAirDetectionDBObject.h"
#include "database/tcSqlReader.h"
#include "database/tcSignatureModel.h"
#include "database/tcDatabase.h"
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
void tcAirDetectionDBObject::AddSqlColumns(std::string& columnString)
{
	columnString += ",";

    columnString += "RCS_dBsm number(8),";
    columnString += "RCS_Model varchar(20),";
	columnString += "OpticalCrossSection_dBsm number(8),";
	columnString += "IRSignature_dB number(8),";
    columnString += "IR_ModelA varchar(20),";
    columnString += "IR_ModelB varchar(20),";
    columnString += "IR_ModelC varchar(20),";
    columnString += "EffectiveHeight_m number(8)";
}

void tcAirDetectionDBObject::BindSignatureModels()
{
    tcDatabase* database = tcDatabase::Get();

    radarSignature = database->GetSignatureModel(RCS_Model);
    irSignatureA = database->GetSignatureModel(IR_ModelA);
    irSignatureB = database->GetSignatureModel(IR_ModelB);
    irSignatureC = database->GetSignatureModel(IR_ModelC);

    if (radarSignature == 0)
    {
        radarSignature = database->GetSignatureModel("Default");
        fprintf(stderr, "tcAirDetectionDBObject::BindSignatureModels - %s missing or bad RCS model\n",
            RCS_Model.c_str());
    }
    if (irSignatureA == 0)
    {
        irSignatureA = database->GetSignatureModel("Default");
        fprintf(stderr, "tcAirDetectionDBObject::BindSignatureModels - %s missing or bad IR model\n",
            IR_ModelA.c_str());
    }
    if (irSignatureB == 0)
    {
        irSignatureB = database->GetSignatureModel("Default");
        fprintf(stderr, "tcAirDetectionDBObject::BindSignatureModels - %s missing or bad IR model\n",
            IR_ModelB.c_str());
    }
    if (irSignatureC == 0)
    {
        irSignatureC = database->GetSignatureModel("Default");
        fprintf(stderr, "tcAirDetectionDBObject::BindSignatureModels - %s missing or bad IR model\n",
            IR_ModelC.c_str());
    }

    // test code
    //for (float az_deg=-180.0f; az_deg<=180.0f; az_deg+=1.0f)
    //{
    //    float val = radarSignature->GetModifier(az_deg, 0);
    //    fprintf(stdout, "az_deg: %.1f val: %.1f\n", az_deg, val);
    //}
}

float tcAirDetectionDBObject::GetIRSig_dB(float az_deg, int irModel) const
{
    float val_dB = irSignature_dB;

    switch (irModel)
    {
    case IRMODELA:
        val_dB += irSignatureA->GetModifier(az_deg, 0);
        break;
    case IRMODELB:
        val_dB += irSignatureB->GetModifier(az_deg, 0);
        break;
    case IRMODELC:
        val_dB += irSignatureC->GetModifier(az_deg, 0);
        break;
    default:
        break;
    }

    return val_dB;
}


float tcAirDetectionDBObject::GetRCS_dBsm(float az_deg) const
{
    return RCS_dBsm + radarSignature->GetModifier(az_deg, 0);
}

void tcAirDetectionDBObject::ReadSql(tcSqlReader& entry)
{
	RCS_dBsm = entry.GetDouble("RCS_dBsm");   
    RCS_Model = entry.GetString("RCS_Model");
	opticalCrossSection_dBsm = entry.GetDouble("OpticalCrossSection_dBsm");               
	irSignature_dB = entry.GetDouble("IRSignature_dB");
    IR_ModelA = entry.GetString("IR_ModelA");
    IR_ModelB = entry.GetString("IR_ModelA");
    IR_ModelC = entry.GetString("IR_ModelA");
    effectiveHeight_m = entry.GetDouble("EffectiveHeight_m");

    BindSignatureModels();
}

void tcAirDetectionDBObject::WriteSql(std::string& valueString)
{
	std::stringstream s;

	s << ",";

	s << RCS_dBsm << ",";
    s << "'" << RCS_Model.c_str() << "',";
	s << opticalCrossSection_dBsm << ",";               
	s << irSignature_dB << ",";
    s << "'" << IR_ModelA.c_str() << "',";
    s << "'" << IR_ModelB.c_str() << "',";
    s << "'" << IR_ModelC.c_str() << "',";
    s << effectiveHeight_m;
	
	valueString += s.str();
}


tcAirDetectionDBObject::tcAirDetectionDBObject()
:   RCS_dBsm(0),
    RCS_Model(""),
	opticalCrossSection_dBsm(0),           
	irSignature_dB(0),
    IR_ModelA(""),
    IR_ModelB(""),
    IR_ModelC(""),
    effectiveHeight_m(0),
    radarSignature(0),
    irSignatureA(0),
    irSignatureB(0),
    irSignatureC(0)
{

}

tcAirDetectionDBObject::tcAirDetectionDBObject(const tcAirDetectionDBObject& obj)
:   RCS_dBsm(obj.RCS_dBsm),
    RCS_Model(obj.RCS_Model),
	opticalCrossSection_dBsm(obj.opticalCrossSection_dBsm),           
	irSignature_dB(obj.irSignature_dB),
    IR_ModelA(obj.IR_ModelA),
    IR_ModelB(obj.IR_ModelB),
    IR_ModelC(obj.IR_ModelC),
    effectiveHeight_m(obj.effectiveHeight_m),
    radarSignature(0),
    irSignatureA(0),
    irSignatureB(0),
    irSignatureC(0)
{
    BindSignatureModels();   
}

tcAirDetectionDBObject::~tcAirDetectionDBObject() 
{
}

}
