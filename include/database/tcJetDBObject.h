/**
**  @file tcJetDBObject.h
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

#ifndef _JETDBOBJECT_H_
#define _JETDBOBJECT_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wx/wx.h" 

#include "tcDBString.h"
#include "tcAirDBObject.h"
#include "tcFile.h"
#include "database/tcSqlReader.h"

class TiXmlElement;

namespace database 
{


    /**
    * This class is used to support a more realistic aerodynamic model. Though
    * it is still not at the level of detail of a flight sim. The intent is to model
    * level flight to get more realistic acceleration, top speed, and 
    * fuel consumption.
    */
    class tcJetDBObject : public tcAirDBObject 
    {
    public:
        float militaryThrust_N;             ///< [N] max static engine thrust, 100% military power
        float militaryThrustSpeedSlope;     ///< Tmil = Tmil0 * (1 + militaryThrustSpeedSlope * v_mps)
        float mfAfterburnThrust_N;          ///< [N] afterburners engine thrust
        float abThrustSpeedSlope;           ///< Tab = Tab0 * (1 + abThrustSpeedSlope * v_mps)
        float mfAfterburnFuelRate_kgps;     ///< [kg/s] with afterburners
        float mfCdpsub;                     ///< parasitic "flat plate" drag area, subsonic
        float mfCdptran;                    ///< transonic drag area
        float mfCdpsup;                     ///< supersonic drag area
        float mfMcm;                        ///< critical mach number
        float mfMsupm;                      ///< supersonic mach number
        float cruiseSpeed_mps;              ///< [m/s] cruise speed ias
        float stallSpeed_mps;               ///< [m/s] stall speed at sea level
        
        static double rho_sealevel;         ///< [kg/m3] air density at sea level
        static double inv_rho_sealevel;     ///< inverse of air density at sea level


        float GetParasiticDragCoefficient(float vmach) const;
        float GetInducedDragCoefficient() const;
        void GetThrustAndEfficiencyFactors(float alt_m, float& thrustFactor, float& fuelEfficiencyFactor) const;
        float GetThrustFactor(float alt_m) const;
        float GetFuelEfficiencyFactor(float alt_m, float inv_ias_mps) const;
        float GetCruiseSpeedForAltitude(float alt_m) const;
		float GetStallSpeedForAltitude(float alt_m) const;
		void GetCruiseAndStallSpeeds(float alt_m, float& cruise_mps, float& stall_mps) const;

        virtual const char* GetClassName() const {return "Air";} ///< returns class name of database object
        void PrintToFile(tcFile& file) {} ///< not supported, redundant with CSV serialization, TODO get rid of these

		static void AddSqlColumns(std::string& columnString);
		void ReadSql(tcSqlReader& entry);
		void WriteSql(std::string& valueString);

        tcJetDBObject();
        tcJetDBObject(tcJetDBObject& obj); ///< copy constructor
        virtual ~tcJetDBObject();
        
    private:
        // calculated parameters
        float invMachRange; ///< 1 / (width of transonic)
        float Cdi; ///< induced drag param Fdi = Cdi / (rho*v^2)
		
		std::vector<float> thrustTable; ///< vector of thrust factor vs. altitude point
		std::vector<float> fuelEfficiencyTable; ///< vector of fuel efficiency vs. altitude point
		static std::vector<float> tableAltitudes; ///< altitudes for thrust and fuel efficiency tables

        void CalculateParams();
		static void InitializeTableAltitudes();

    };
}

#endif

