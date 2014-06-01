/**
**  @file tcSensorPlatformDBObject.cpp
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

#include "tcSensorPlatformDBObject.h"
#include "tcDatabase.h"
#include "math_constants.h"
#include "randfn.h"
#include "CsvTranslator.h"
#include "common/tinyxml.h"
#include "common/tcFile.h"
#include "database/tcSqlReader.h"
#include "database/CsvTranslator.h"
#include <sstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;

namespace database
{

/**
* This checks that the database object has all of the emitters in the 
* emitters vector. Somewhat expensive, nEmitters * nSensors
* comparisons for positive result, fewer for negative result.
* @return true if this database object has all of the emitters
*/
bool tcSensorPlatformDBObject::HasAllEmitters(std::vector<long>& emitters)
{
	size_t nEmitters = emitters.size();
    size_t nSensors = sensorClass.size();
	if ((int)nEmitters > nSensors) return false;

	/* watch out for problems with this lazy init done inside this method
	** sensorId will not be available until this is called first */
	if (sensorId.size() == 0) UpdateSensorList();

	for (size_t k=0; k<nEmitters; k++)
	{
		bool bFound = false;
		long emitterId = emitters[k];
		for (size_t n=0; (n<nSensors) && !bFound; n++)
		{
			if (sensorId[n] == emitterId) bFound = true;
		}
		if (!bFound) return false;
	}
	return true;
}



void tcSensorPlatformDBObject::PrintToFile(tcFile& file) 
{
}


/**
* Updates sensorId vector with database ids for each sensor
*/
void tcSensorPlatformDBObject::UpdateSensorList()
{
	sensorId.clear();

    tcDatabase* database = tcDatabase::Get();

	for(size_t n=0; n<sensorClass.size(); n++)
	{
		tcDatabaseObject* obj = database->GetObject(sensorClass[n]);
		if (obj)
		{
			sensorId.push_back(obj->mnKey);
		}
		else
		{
			fprintf(stderr, "Error - tcSensorPlatformDBObject::UpdateSensorList - sensor %s not found\n",
				sensorClass[n].c_str());
			sensorId.push_back(-1);
		}
	}
}

/**
* Adds sql column definitions to columnString. This is used for
* SQL create table command
*/
void tcSensorPlatformDBObject::AddSqlColumns(std::string& columnString)
{
    // no longer needed since all covered by platform_sensors table
    /*
	columnString += ",";

    for(int i=0;i<MAXSENSORS;i++) 
    {
        tcString s;
        s.Format("S%d_class varchar(30),",i+1);
        columnString += s.GetBuffer();

        s.Format("S%d_az number(8)",i+1);
        columnString += s.GetBuffer();

        if (i < MAXSENSORS - 1) columnString += ",";
    }
    */


}

void tcSensorPlatformDBObject::ReadSql(tcSqlReader& entry)
{
    sensorClass.clear();
    sensorAz.clear();
    sensorId.clear();
    
    // no longer needed since all covered by platform_sensors table
    //
	//for(int i=0;i<MAXSENSORS;i++) 
	//{
	//	std::string className;
	//	tcString s;

	//	s.Format("S%d_class", i+1);
	//	className = entry.GetString(s.GetBuffer());

	//	if (className.size() > 0)
	//	{
	//		sensorClass.push_back(className);

	//		s.Format("S%d_az", i+1);
	//		sensorAz.push_back(entry.GetDouble(s.GetBuffer()));
	//	}

	//}

}

void tcSensorPlatformDBObject::WriteSql(std::string& valueString)
{
    // no longer needed since all covered by platform_sensors table
    /*
	std::stringstream s;

	s << ",";

	
	for(size_t i=0; i<MAXSENSORS; i++) 
	{
		if (i < sensorClass.size()) 
		{
			s << "'" << sensorClass[i] << "',";
			s << sensorAz[i];
		}
		else
		{
			s << "'',";
			s << "0";
		}
        if (i < MAXSENSORS - 1) s << ",";
	}
			

	
	valueString += s.str();
    */

}


tcSensorPlatformDBObject::tcSensorPlatformDBObject()
{
 
}

tcSensorPlatformDBObject::tcSensorPlatformDBObject(const tcSensorPlatformDBObject& obj)
: sensorClass(obj.sensorClass),
  sensorAz(obj.sensorAz),
  sensorId(obj.sensorId)
{

}

tcSensorPlatformDBObject::~tcSensorPlatformDBObject() 
{
}

}
