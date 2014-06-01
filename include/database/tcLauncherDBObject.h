/**
**  @file tcLauncherDBObject.h
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

#ifndef _LAUNCHERDBOBJECT_H_
#define _LAUNCHERDBOBJECT_H_

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
    *
    */
    class tcLauncherDBObject : public tcDatabaseObject 
    {
    public:
        //float cycleTime;   ///< down time between shots
        ///// firing arc in deg, use >= 360 to be equivalent to old isAutoPoint = 1, use 0 for old isAutoPoint=0
        //float firingArc_deg; 

        unsigned short GetCapacityForItem(const std::string& item) const;
        unsigned short GetCapacityForItem(const std::string& item, float& loadTime_s, float& cycleTime_s) const;
        virtual const char* GetClassName() const {return "Launcher";} ///< returns class name of database object
        
        int GetConfigurationIndex(const std::string& item) const;
        unsigned short GetConfigurationCapacity(unsigned int idx) const;    
        const std::string& GetConfigurationClass(unsigned int idx) const;
        float GetConfigurationLoadTime(unsigned int idx) const;
        float GetConfigurationCycleTime(unsigned int idx) const;
        unsigned int GetNumberConfigurations() const;
        const wxString& GetConfigurationDescription() const;
        unsigned short GetDefaultChildCapacity() const;
        const char* GetDefaultChildClass() const; ///< @returns default class name for this launcher
        virtual void PrintToFile(tcFile& file);
        
        static void AddSqlColumns(std::string& columnString);
        void ReadSql(tcSqlReader& entry);
        void WriteSql(std::string& valueString);

        void ClearConfigs();
        void AddConfig(const std::string& childClass, unsigned short capacity, float loadTime_s, float cycleTime_s);

        tcLauncherDBObject();
        tcLauncherDBObject(const tcLauncherDBObject& obj); ///< copy constructor
        tcLauncherDBObject(const std::string& databaseClass);
        virtual ~tcLauncherDBObject();
        
    private:
        // these should be combined as a structure
        std::vector<std::string> childClassList; ///< vector of different loadout configs
        std::vector<unsigned short> childCapacityList; ///< corresponding vector of max quantities
        std::vector<float> childLoadTime_s; ///< vector of load times
        std::vector<float> childCycleTime_s; ///< vector of cycle times
            
    };

} // namespace database

#endif
