/** @file tcFlightportDBObject.h */
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

#ifndef _FLIGHTPORTDBOBJECT_H_
#define _FLIGHTPORTDBOBJECT_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "tcDatabaseObject.h"
#include <vector>

class TiXmlElement;

namespace database
{
	class tcSqlReader;

    /**
    * Data for flightport model.
    */
    class tcFlightportDBObject : public tcDatabaseObject 
    {
    public:
        struct spotDBInfo
        {
            int isLaunch; ///< 1 - if launch/land spot, 0 - if ready spot 
            float x; ///< location of spot relative to parent
            float y; 
            float z;
            float orientation_deg; ///< orientation for runway, 0 is along -z axis (heading axis for ships)
            float length;
        };
        enum
        {
            MAX_DB_SPOTS = 16  ///< max spots in database--can be increased if needed
        };
        int heloOnly;  ///< set non-zero for helo-only flight port
        unsigned int hangarCapacity;
        std::vector<spotDBInfo> spotInfo;

        virtual const char* GetClassName() const {return "FlightPort";} ///< returns class name of database object

		static void AddSqlColumns(std::string& columnString);
		void ReadSql(tcSqlReader& entry);
		void WriteSql(std::string& valueString);

        tcFlightportDBObject();
        tcFlightportDBObject(tcFlightportDBObject& obj); ///< copy constructor
        virtual ~tcFlightportDBObject();
    };

}

#endif

