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

#include "tcFlightportDBObject.h"
#include "math_constants.h"
#include "randfn.h"
#include "CsvTranslator.h"
#include "common/tinyxml.h"
#include "database/tcSqlReader.h"
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
    void tcFlightportDBObject::AddSqlColumns(std::string& columnString)
    {
        tcDatabaseObject::AddSqlColumns(columnString);

        columnString += ",";
        columnString += "IsHeloOnly number(1),";              
        columnString += "HangarCapacity number(4),";              

        int i;
        for(i=0;i<MAX_DB_SPOTS;i++) 
        {
            tcString s;
            s.Format("Sp%d_launch number(1),",i+1);
            columnString += s.GetBuffer();

            s.Format("Sp%d_x number(5),",i+1);
            columnString += s.GetBuffer();

            s.Format("Sp%d_y number(5),",i+1);  
            columnString += s.GetBuffer();

            s.Format("Sp%d_z number(5),",i+1);
            columnString += s.GetBuffer();

            s.Format("Sp%d_dir_deg number(3),",i+1);
            columnString += s.GetBuffer();

            s.Format("Sp%d_len number(5)",i+1);
            columnString += s.GetBuffer();

            if (i < MAX_DB_SPOTS - 1) columnString += ",";
        }

    }

    void tcFlightportDBObject::ReadSql(tcSqlReader& entry)
    {
        tcDatabaseObject::ReadSql(entry);

        heloOnly = entry.GetInt("IsHeloOnly");
        hangarCapacity = entry.GetInt("HangarCapacity");

        spotInfo.clear();
        int i;
        for(i=0;i<MAX_DB_SPOTS;i++) 
        {
            spotDBInfo info;
            info.isLaunch = entry.GetInt("Sp%d_launch", i+1);
            info.x = entry.GetDouble("Sp%d_x", i+1);
            info.y = entry.GetDouble("Sp%d_y", i+1);  
            info.z = entry.GetDouble("Sp%d_z", i+1);
            info.orientation_deg = entry.GetDouble("Sp%d_dir_deg", i+1);
            info.length = entry.GetDouble("Sp%d_len", i+1);

            bool isValid = (info.x != 0)||(info.y !=0)||(info.z != 0);
            if (isValid)
            {
                spotInfo.push_back(info);
            }
        }


    }

    void tcFlightportDBObject::WriteSql(std::string& valueString)
    {
        tcDatabaseObject::WriteSql(valueString);

        std::stringstream s;

        s << ",";

        s << heloOnly << ",";  ///< set non-zero for helo-only flight port
        s << hangarCapacity << ",";     

        size_t numSpots = spotInfo.size();
        size_t i;
        for(i=0; i<MAX_DB_SPOTS; i++) 
        {
            if (i<numSpots) 
            {
                spotDBInfo info = spotInfo[i];
                s << (long)info.isLaunch << ",";
                s << info.x << ",";
                s << info.y << ","; // y and z swapped in header due to OSG coord change
                s << info.z << ",";
                s << info.orientation_deg << ",";
                s << info.length;
            }
            else
            {
                s << "0,";
                s << "0,";
                s << "0,";
                s << "0,";
                s << "0,";
                s << "0";
            }
            if (i < MAX_DB_SPOTS - 1) s << ",";
        }

        valueString += s.str();

    }

    tcFlightportDBObject::tcFlightportDBObject() : tcDatabaseObject() 
    {
        mnModelType = MTYPE_OBJECT;
        heloOnly = 0;  ///< set non-zero for helo-only flight port
        hangarCapacity = 0;
        spotInfo.clear();  
    }

    tcFlightportDBObject::tcFlightportDBObject(tcFlightportDBObject& obj)
        : tcDatabaseObject(obj)
    {
        heloOnly = obj.heloOnly;
        hangarCapacity = obj.hangarCapacity;
        spotInfo.clear();

        size_t nSpots = obj.spotInfo.size();
        for(size_t i=0;i<nSpots;i++)
        {
            spotInfo.push_back(obj.spotInfo[i]);
        }
    }

    tcFlightportDBObject::~tcFlightportDBObject() 
    {
    }

}
