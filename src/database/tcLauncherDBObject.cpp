/**   
**  @file tcLauncherDBObject.cpp
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



#include "tcLauncherDBObject.h"
#include "math_constants.h"
#include "randfn.h"
#include "CsvTranslator.h"
#include "common/tinyxml.h"
#include "database/tcSqlReader.h"
#include "database/tcDatabase.h"

#include <sstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;

namespace database
{
    void tcLauncherDBObject::ClearConfigs()
    {
        childClassList.clear();
        childCapacityList.clear();
        childLoadTime_s.clear();
    }

    void tcLauncherDBObject::AddConfig(const std::string& childClass, unsigned short capacity, float loadTime_s, float cycleTime_s)
    {
        childClassList.push_back(childClass);
        childCapacityList.push_back(capacity);
        childLoadTime_s.push_back(loadTime_s);
        childCycleTime_s.push_back(cycleTime_s);
    }


    /**
    * @return index of matching configuration or -1 if no match
    */
    int tcLauncherDBObject::GetConfigurationIndex(const std::string& item) const
    {
        wxString s(item.c_str());

        size_t nTypes = childClassList.size();
        for (size_t k=0; k<nTypes; k++)
        {
            if (s.Matches(childClassList[k].c_str()))
            { 
                return int(k);
            }
        }

        return -1;
    }

    /**
    * This can be a substitute for IsItemCompatible by testing != 0
    * @see IsItemCompatible
    */
    unsigned short tcLauncherDBObject::GetCapacityForItem(const std::string& item) const
    {
        wxString s(item.c_str());

        size_t nTypes = childClassList.size();
        for (size_t k=0; k<nTypes; k++)
        {
            if (s.Matches(childClassList[k].c_str()))
            { 
                wxASSERT(childClassList.size() == childCapacityList.size());
                return childCapacityList[k];
            }
        }
    
        return 0; 
    }

    unsigned short tcLauncherDBObject::GetCapacityForItem(const std::string& item, float& loadTime_s, float& cycleTime_s) const
    {
        wxString s(item.c_str());

        size_t nTypes = childClassList.size();
        for (size_t k=0; k<nTypes; k++)
        {
            if (s.Matches(childClassList[k].c_str()))
            { 
                wxASSERT(childClassList.size() == childCapacityList.size());
                loadTime_s = childLoadTime_s[k];
                cycleTime_s = childCycleTime_s[k];
                return childCapacityList[k];
            }
        }
    
        return 0; 
    }
    
    unsigned short tcLauncherDBObject::GetConfigurationCapacity(unsigned int idx) const
    {
        wxASSERT(idx < childCapacityList.size());
        return childCapacityList[idx];
    }
        
    const std::string& tcLauncherDBObject::GetConfigurationClass(unsigned int idx) const
    {
        wxASSERT(idx < childClassList.size());
        return childClassList[idx];
    }

    float tcLauncherDBObject::GetConfigurationCycleTime(unsigned int idx) const
    {
        wxASSERT(idx < childCycleTime_s.size());
        return childCycleTime_s[idx];
    }

    float tcLauncherDBObject::GetConfigurationLoadTime(unsigned int idx) const
    {
        wxASSERT(idx < childClassList.size());
        return childLoadTime_s[idx];
    }
    
    const wxString& tcLauncherDBObject::GetConfigurationDescription() const
    {
        static wxString description;

        description = "";

        size_t nConfigs = GetNumberConfigurations();

        for (size_t n=0; n<nConfigs; n++)
        {
			wxString config_string;
            config_string.Printf("%d x %s", GetConfigurationCapacity((unsigned int)n), 
				GetConfigurationClass((unsigned int)n).c_str());

			description.Append(config_string);
            if (n < nConfigs - 1)
            {
                description.Append(",");
            }
        }

        return description;
    }

    unsigned int tcLauncherDBObject::GetNumberConfigurations() const
    {
        return (unsigned int)childClassList.size();
    }
        
    
    unsigned short tcLauncherDBObject::GetDefaultChildCapacity() const
    {
        if (childCapacityList.size() == 0)
        {
            return 0;
        }
        else
        {
            return childCapacityList[0];
        }  
    }   
    
    /**
    * @returns first configuration in childClassList as a default, or "" if error
    */
    const char* tcLauncherDBObject::GetDefaultChildClass() const
    {
        static std::string errorString = "";
        static wxArrayString matches;
        if (childClassList.size() > 0)
        {
            wxString candidate(childClassList[0].c_str());
            if ((candidate.Find('?') == wxNOT_FOUND) && (candidate.Find('*') == wxNOT_FOUND))
            {
                return childClassList[0].c_str();
            }
            else // default has a wild card
            {
                matches = tcDatabase::Get()->WildcardSearch(candidate, "loadout");
                if (matches.size() > 0)
                {
                    return matches[0].c_str();
                }
                else
                {
                    return errorString.c_str();
                }
            }
        }
        else
        {
            return errorString.c_str();
        }
    }
    


	void tcLauncherDBObject::PrintToFile(tcFile& file) 
	{
		tcString s;

		tcDatabaseObject::PrintToFile(file);

		s.Format("   default child class: %s mnCapacity:%d\n", 
            GetDefaultChildClass(), GetDefaultChildCapacity());
		file.WriteString(s.GetBuffer());
	}

	/**
	* Adds sql column definitions to columnString. This is used for
	* SQL create table command
	*/
	void tcLauncherDBObject::AddSqlColumns(std::string& columnString)
	{
        wxASSERT(false); // no longer using this table (for now 13Jun2009)
		tcDatabaseObject::AddSqlColumns(columnString);

		columnString += ",";

		columnString += "CycleTime_s number(5),";
        columnString += "FiringArc_deg number(4)";
	}

	void tcLauncherDBObject::ReadSql(tcSqlReader& entry)
	{
        wxASSERT(false); // no longer using this table (for now 13Jun2009)
		tcDatabaseObject::ReadSql(entry);

		//cycleTime = entry.GetDouble("CycleTime_s");
        //firingArc_deg = entry.GetDouble("FiringArc_deg");	
	}

	void tcLauncherDBObject::WriteSql(std::string& valueString)
	{
        wxASSERT(false); // no longer using this table (for now 13Jun2009)
		tcDatabaseObject::WriteSql(valueString);

		std::stringstream s;

		s << ",";

		//s << cycleTime << ",";
        //s << firingArc_deg;

		valueString += s.str();
	}


	tcLauncherDBObject::tcLauncherDBObject() : tcDatabaseObject()
        //,
        //cycleTime(0),
        //firingArc_deg(0)
	{        
        mzClass = "Default Launcher";
	}

	tcLauncherDBObject::tcLauncherDBObject(const tcLauncherDBObject& obj) 
		: tcDatabaseObject(obj),
        //cycleTime(obj.cycleTime),
		childClassList(obj.childClassList),
		childCapacityList(obj.childCapacityList)
        //,firingArc_deg(obj.firingArc_deg)
	{
	}

    tcLauncherDBObject::tcLauncherDBObject(const std::string& databaseClass)
        : tcDatabaseObject(databaseClass)
         //,cycleTime(0),
         //firingArc_deg(0)
    {
    }


	tcLauncherDBObject::~tcLauncherDBObject() 
	{
	}


}
