/**  
**  @file tcESMDBObject.cpp
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


#include "tcESMDBObject.h"
#include "tcESMSensor.h"
//#include "math_constants.h"
//#include "randfn.h"
//#include "AError.h"
#include "CsvTranslator.h"
#include <sstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;

namespace database
{

tcSensorState* tcESMDBObject::CreateSensor(tcGameObject* parent)
{
    tcESMSensor* esm = new tcESMSensor(this);
	esm->SetParent(parent);
	
	return esm;
}

const char* tcESMDBObject::GetTypeDescription() const
{
    static wxString s;
    s = "ESM";

    if (isRWR) s += " RWR";
    

    return s.c_str();
}


void tcESMDBObject::PrintToFile(tcFile& file) 
{
    //char zBuff[128];

    tcSensorDBObject::PrintToFile(file);
}

/**
* Adds sql column definitions to columnString. This is used for
* SQL create table command
*/
void tcESMDBObject::AddSqlColumns(std::string& columnString)
{
	tcSensorDBObject::AddSqlColumns(columnString);

    columnString += ",";

	columnString += "IsRWR number(3)"; 

}

void tcESMDBObject::ReadSql(tcSqlReader& entry)
{
	tcSensorDBObject::ReadSql(entry);

    isRWR = entry.GetInt("IsRWR") != 0;
}

void tcESMDBObject::WriteSql(std::string& valueString)
{
	tcSensorDBObject::WriteSql(valueString);

    std::stringstream s;

	s << ",";

	s << (long)isRWR;

	valueString += s.str();
}


tcESMDBObject::tcESMDBObject() : tcSensorDBObject() 
{
    mzClass = "Default ESM";

    mfMaxRange_km = 100.0f;
    mfRefRange_km = 80.0f;
    mfFieldOfView_deg = 360.0f;
    mfScanPeriod_s = 4.0f;
    isRWR = false;
}

tcESMDBObject::tcESMDBObject(const tcESMDBObject& obj) 
: tcSensorDBObject(obj),
  isRWR(obj.isRWR)
{
}

tcESMDBObject::~tcESMDBObject() 
{
}


}
