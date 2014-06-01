/**
**  @file tcGroundDBObject.cpp
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

#include "tcGroundDBObject.h"
#include "tcDatabase.h"
#include "tcFlightportDBObject.h"

#include "database/tcSqlReader.h"
#include <sstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


namespace database
{

tcDatabaseObject* tcGroundDBObject::AsDatabaseObject()
{
	return this;
}

tcFlightportDBObject* tcGroundDBObject::GetFlightport()
{
	tcFlightportDBObject* flightport = dynamic_cast<tcFlightportDBObject*>
        (database->GetObject(flightportClass.c_str()));

    if (!flightport)
	{
		fprintf(stderr, "Error - Class: %s - flightport (%s) not found\n",
			mzClass.c_str(), flightportClass.c_str());
	}
	return flightport;
}


/**
* Adds sql column definitions to columnString. This is used for
* SQL create table command
*/
void tcGroundDBObject::AddSqlColumns(std::string& columnString)
{
	tcPlatformDBObject::AddSqlColumns(columnString);

    columnString += ",";

    columnString += "FlightportClass varchar(30)";

    tcAirDetectionDBObject::AddSqlColumns(columnString);
}

void tcGroundDBObject::ReadSql(tcSqlReader& entry)
{
	tcPlatformDBObject::ReadSql(entry);

    flightportClass = entry.GetString("FlightportClass").c_str();

    tcAirDetectionDBObject::ReadSql(entry);
}

void tcGroundDBObject::WriteSql(std::string& valueString)
{
	tcPlatformDBObject::WriteSql(valueString);

    std::stringstream s;

	s << ",";

	s << "'" << flightportClass.c_str() << "'";

	valueString += s.str();

    tcAirDetectionDBObject::WriteSql(valueString);
}


tcGroundDBObject::tcGroundDBObject() : 
    tcPlatformDBObject(),
    tcAirDetectionDBObject()
{
    mnModelType = MTYPE_OBJECT;
}

tcGroundDBObject::tcGroundDBObject(const tcGroundDBObject& obj)
: tcPlatformDBObject(obj), 
  tcAirDetectionDBObject(obj),
  flightportClass(obj.flightportClass)
{
}

tcGroundDBObject::~tcGroundDBObject() 
{
}

}
