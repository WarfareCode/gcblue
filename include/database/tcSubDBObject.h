/**
**  @file tcSubDBObject.h
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

#ifndef _SUBDBOBJECT_H_
#define _SUBDBOBJECT_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wx/wx.h" 

#include "tcDBString.h"
#include "tcPlatformDBObject.h"
#include "tcAirDetectionDBObject.h"
#include "tcWaterDetectionDBObject.h"
#include "tcFile.h"
#include "database/tcSqlReader.h"

class TiXmlElement;

namespace database 
{


    /**
    * 
    */
    class tcSubDBObject : public tcPlatformDBObject, public tcAirDetectionDBObject, public tcWaterDetectionDBObject
    {
    public:
        float draft_m;                    ///< max navigational draft on surface
        float surfaceSpeed_kts;           ///< speed while surfaced
        float mfMaxDepth_m;

        bool isDieselElectric;            ///< true if diesel electric
        float batteryCapacity_kJ;         ///< battery capacity when fully charged
        float batteryRate_kW;             ///< battery drain rate at min thrust, scaled to 4x at max thrust
        float batteryCharge_kW;           ///< charge rate when snorkeling on generators

        float GetBatteryRate(float speed_mps) const;

        float GetMaxNonCavitatingSpeed(float depth_m) const;
        float GetNoiseLevelForSpeed(float speed_mps) const;  
        float GetNoiseLevelForSpeedKts(float speed_kts) const;      
        bool IsCavitatingMps(float speed_mps, float depth_m) const;
        bool IsCavitatingKts(float speed_kts, float depth_m) const;
        
        float GetInvDraft() const;

        virtual const char* GetClassName() const {return "Sub";} ///< returns class name of database object
        void PrintToFile(tcFile& file) {} ///< not supported, redundant with CSV serialization, TODO get rid of these

		static void AddSqlColumns(std::string& columnString);
		void ReadSql(tcSqlReader& entry);
		void WriteSql(std::string& valueString);

        tcSubDBObject();
        tcSubDBObject(const tcSubDBObject& obj); ///< copy constructor
        virtual ~tcSubDBObject();
        
    private:
        // calculated parameters               
        float invMaxSpeed_mps;
        float invDraft_m; ///< 1/draft_m
        float batteryDrainConstant; ///< [kW/mps]

        void CalculateParams();

    };
}

#endif

