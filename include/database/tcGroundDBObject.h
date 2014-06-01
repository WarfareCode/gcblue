/**
**  @file tcGroundDBObject.h
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

#ifndef _GROUNDDBOBJECT_H_
#define _GROUNDDBOBJECT_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "tcPlatformDBObject.h"
#include "tcAirDetectionDBObject.h"


namespace database
{
	class tcFlightportDBObject;
	class tcSqlReader;

    /**
    * Models a ground (non-airfield) platform. Specialization of old tcGenericDBObject
    */
    class tcGroundDBObject :  public tcPlatformDBObject, public tcAirDetectionDBObject
    {
    public:
        tcDBString flightportClass; ///< database class name of flightport (or empty if none)

		tcDatabaseObject* AsDatabaseObject();
        virtual const char* GetClassName() const {return "Ground";} ///< returns class name of database object
        tcFlightportDBObject* GetFlightport();

		static void AddSqlColumns(std::string& columnString);
		void ReadSql(tcSqlReader& entry);
		void WriteSql(std::string& valueString);

        tcGroundDBObject();
        tcGroundDBObject(const tcGroundDBObject& obj); ///< copy constructor
        virtual ~tcGroundDBObject();

	private:

    };

}

#endif

