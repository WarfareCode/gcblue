/*
**  @file tcJetDBObject.cpp
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

#include "tcJetDBObject.h"
#include "tcPlatformDBObject.h"
#include "CsvTranslator.h"
#include "common/tinyxml.h"
#include <sstream>
#include "tcAero.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

namespace database
{
    double tcJetDBObject::rho_sealevel = 1.225; // must match atmosphere.csv
    double tcJetDBObject::inv_rho_sealevel = 0.8163265; // must match atmosphere.csv

	std::vector<float> tcJetDBObject::tableAltitudes;

	/**
	* Static function to initialize common table of altitude points (in meters)
	* Must be called once before starting simulation
	*/
	void tcJetDBObject::InitializeTableAltitudes()
	{
		wxASSERT(tableAltitudes.size() == 0);
		tableAltitudes.clear();

	    tableAltitudes.push_back(2000.0f);
		tableAltitudes.push_back(4000.0f);
		tableAltitudes.push_back(6000.0f);
		tableAltitudes.push_back(8000.0f);
		tableAltitudes.push_back(10000.0f);
		tableAltitudes.push_back(12000.0f);
		tableAltitudes.push_back(16000.0f);
		tableAltitudes.push_back(20000.0f);
		tableAltitudes.push_back(25000.0f);
		tableAltitudes.push_back(30000.0f);
	}

    /**
    * Calculate private parameters. Should be called after
    * object is loaded.
    */
    void tcJetDBObject::CalculateParams()
    {
        // invMachRange
        if (mfMsupm <= mfMcm)
        {
            mfMsupm = 1.005f*mfMcm;
        }
        
        if (mfMsupm > mfMcm)
        {
            invMachRange = 1.0f / (mfMsupm - mfMcm);
        }
        else
        {
            invMachRange = 0;
        } 

        Cdi = 0.333333 * mfCdpsub * (rho_sealevel * rho_sealevel) * powf(cruiseSpeed_mps, 4.0f);
    }

    /**
    * @return cruise speed in m/s
    */
    float tcJetDBObject::GetCruiseSpeedForAltitude(float alt_m) const
    {
        float rho = Aero::GetAirDensity(alt_m);
        float vmach_mps = Aero::GetSoundSpeed(alt_m);
        
        float factor = powf(inv_rho_sealevel * rho, -0.5f);

        float speed_mps = factor * cruiseSpeed_mps;

        return std::min(speed_mps, mfMcm*vmach_mps);
    }
    
    /**
    * @return stall speed in m/s
    */
    float tcJetDBObject::GetStallSpeedForAltitude(float alt_m) const
    {
        float rho = Aero::GetAirDensity(alt_m);
        
        float factor = powf(inv_rho_sealevel * rho, -0.5f);

        float speed_mps = factor * stallSpeed_mps;

		return speed_mps;
    }

	void tcJetDBObject::GetCruiseAndStallSpeeds(float alt_m, float& cruise_mps, float& stall_mps) const
	{
        float rho = Aero::GetAirDensity(alt_m);
        float vmach_mps = Aero::GetSoundSpeed(alt_m);
        
        float factor = powf(inv_rho_sealevel * rho, -0.5f);

        cruise_mps = factor * cruiseSpeed_mps;
        cruise_mps = std::min(cruise_mps, mfMcm*vmach_mps);

		stall_mps = factor * stallSpeed_mps;
	}

    /**
    * @param vmach Speed divided by speed of sound (mach number)
    * @return interpolated parasitic drag coeff
    */
    float tcJetDBObject::GetParasiticDragCoefficient(float vmach) const
    {
        float K_dp;  // parasitic drag coeff
        float mcrit = mfMcm; // critical mach number
        float msup = mfMsupm; // midpoint of transonic region
        float mtran = 0.5f*(mcrit + msup); // start of supersonic region
    
        if (vmach <= mcrit) 
        {
            K_dp = mfCdpsub; // drag coeff includes 0.5*area factor
        }
        else if (vmach >= msup)
        {
            K_dp = mfCdpsup;
        }
        else if (vmach <= mtran) 
        {
            K_dp = 2.0f * (vmach - mcrit) * (mfCdptran - mfCdpsub) * invMachRange
                + mfCdpsub;
        }
        else // (vmach > mtran)&&(vmach < msup)
        { 
            K_dp = 2.0f * (msup - vmach) * (mfCdptran - mfCdpsup) * invMachRange 
                + mfCdpsup;
        }
        return K_dp;
    }
    
    /**
    * Placed here to allow better thrust decay model to be incorporated into
    * database without affecting air model
    */
	void tcJetDBObject::GetThrustAndEfficiencyFactors(float alt_m, float& thrustFactor, float& fuelEfficiencyFactor) const
    {
	    thrustFactor = 1.0f;
		fuelEfficiencyFactor = 1.0f;

		size_t nAlt = tableAltitudes.size();

		if (alt_m < tableAltitudes[0])
        {
            float alpha = 0.0005f * alt_m;
            wxASSERT(tableAltitudes[0] == 2000.0f);
            wxASSERT(alpha <= 1.0f);

            // assume thrustFactor is always 1.0 at 0 m
            fuelEfficiencyFactor = (1.0f - alpha) + alpha * fuelEfficiencyTable[0];
            thrustFactor = (1.0f - alpha) + alpha * thrustTable[0];
            return;
        }
		if (alt_m >= tableAltitudes[nAlt-1])
		{
			thrustFactor = thrustTable[nAlt-1];
			fuelEfficiencyFactor = fuelEfficiencyTable[nAlt-1];
			return;
		}

		// search for position in table and linearly interpolate factors
		for (size_t idx=1; idx<nAlt; idx++)
		{
			float alt_low = tableAltitudes[idx-1];
			float alt_high = tableAltitudes[idx];
			if (alt_m <= alt_high)
			{
				float low_weight = (alt_high - alt_m) / (alt_high - alt_low);
				float high_weight = 1.0f - low_weight;
				thrustFactor = low_weight * thrustTable[idx-1] + high_weight * thrustTable[idx];
				fuelEfficiencyFactor = low_weight * fuelEfficiencyTable[idx-1] + 
					high_weight * fuelEfficiencyTable[idx];
				return;
			}
		}

		wxASSERT(false); // error, corrupt table
    }
    

    /**
    * Version that only returns thrust factor
    *
    * @return thrust factor
    */
	float tcJetDBObject::GetThrustFactor(float alt_m) const
    {
	    float thrustFactor = 1.0f;

		size_t nAlt = tableAltitudes.size();

		if (alt_m < tableAltitudes[0])
        {
            float alpha = 0.0005f * alt_m;
            wxASSERT(tableAltitudes[0] == 2000.0f);
            wxASSERT(alpha <= 1.0f);

            // assume thrustFactor is always 1.0 at 0 m
            thrustFactor = (1.0f - alpha) + alpha * thrustTable[0];
            return thrustFactor;
        }

		if (alt_m >= tableAltitudes[nAlt-1])
		{
			thrustFactor = thrustTable[nAlt-1];
			return thrustFactor;
		}

		// search for position in table and linearly interpolate factors
		for (size_t idx=1; idx<nAlt; idx++)
		{
			float alt_low = tableAltitudes[idx-1];
			float alt_high = tableAltitudes[idx];
			if (alt_m <= alt_high)
			{
				float low_weight = (alt_high - alt_m) / (alt_high - alt_low);
				float high_weight = 1.0f - low_weight;
				thrustFactor = low_weight * thrustTable[idx-1] + high_weight * thrustTable[idx];
				return thrustFactor;
			}
		}

		wxASSERT(false); // error, corrupt table
        return thrustFactor;
    }
    
    /**
    * Version that only returns fuel efficiency factor
    * 
    * @param inv_ias_mps = (1.0 / indicated air speed in m/s), used for fuel efficiency penalty when below cruise IAS
    * @return fuel efficiency factor, lower means burns less fuel
    */
    float tcJetDBObject::GetFuelEfficiencyFactor(float alt_m, float inv_ias_mps) const
    {
		float fuelEfficiencyFactor = 1.0f;

		float cruise_penalty = cruiseSpeed_mps * inv_ias_mps;

        cruise_penalty = std::max(cruise_penalty, 1.0f);

		size_t nAlt = tableAltitudes.size();

		if (alt_m < tableAltitudes[0])
        {
            float alpha = 0.0005f * alt_m;
            wxASSERT(tableAltitudes[0] == 2000.0f);
            wxASSERT(alpha <= 1.0f);

            // assume fuelEfficiencyFactor is always 1.0 at 0 m
            fuelEfficiencyFactor = (1.0f - alpha) + alpha * fuelEfficiencyTable[0];
            return fuelEfficiencyFactor;
        }


		if (alt_m >= tableAltitudes[nAlt-1])
		{
			fuelEfficiencyFactor = cruise_penalty * fuelEfficiencyTable[nAlt-1];
			return fuelEfficiencyFactor;
		}

		// search for position in table and linearly interpolate factors
		for (size_t idx=1; idx<nAlt; idx++)
		{
			float alt_low = tableAltitudes[idx-1];
			float alt_high = tableAltitudes[idx];
			if (alt_m <= alt_high)
			{
				float low_weight = (alt_high - alt_m) / (alt_high - alt_low);
				float high_weight = 1.0f - low_weight;

				fuelEfficiencyFactor = low_weight * fuelEfficiencyTable[idx-1] + 
					high_weight * fuelEfficiencyTable[idx];
				fuelEfficiencyFactor *= cruise_penalty;
				return fuelEfficiencyFactor;
			}
		}

		wxASSERT(false); // error, corrupt table
		return fuelEfficiencyFactor;
    }
    

    float tcJetDBObject::GetInducedDragCoefficient() const
    {
        return Cdi;
    }

    /**
    * Adds sql column definitions to columnString. This is used for
    * SQL create table command
    */
    void tcJetDBObject::AddSqlColumns(std::string& columnString)
    {
        tcAirDBObject::AddSqlColumns(columnString);

        columnString += ",";

        columnString += "MilitaryThrust_N number(8),";
        columnString += "MilitaryThrustSpeedSlope number(8),";
        columnString += "ABThrust_N number(8),";  
        columnString += "ABThrustSpeedSlope number(8),";
        columnString += "ABFuelRate_kgps number(8),";  
        columnString += "Cdpsub number(8),";
        columnString += "Cdptran number(8),";
        columnString += "Cdpsup number(8),";
        columnString += "Mcm number(8),";
        columnString += "Msupm number(8),";
        columnString += "CruiseSpeed_mps number(8),";
        columnString += "StallSpeed_mps number(8)";

		if (tableAltitudes.size() == 0)
		{
			InitializeTableAltitudes();
		}

		for (size_t idx=0; idx<tableAltitudes.size(); idx++)
		{
			wxString s;
			s.Printf(",T%d number(5)", int(0.001f*tableAltitudes[idx]));
			columnString += s.c_str();
		}

		for (size_t idx=0; idx<tableAltitudes.size(); idx++)
		{
			wxString s;
			s.Printf(",FE%d number(5)", int(0.001f*tableAltitudes[idx]));
			columnString += s.c_str();
		}

    }

    void tcJetDBObject::ReadSql(tcSqlReader& entry)
    {
        tcAirDBObject::ReadSql(entry);
        
        militaryThrust_N = entry.GetDouble("MilitaryThrust_N");
        militaryThrustSpeedSlope = entry.GetDouble("MilitaryThrustSpeedSlope");
        mfAfterburnThrust_N = entry.GetDouble("ABThrust_N");  
        abThrustSpeedSlope = entry.GetDouble("ABThrustSpeedSlope");
        mfAfterburnFuelRate_kgps = entry.GetDouble("ABFuelRate_kgps");       
        mfCdpsub = entry.GetDouble("Cdpsub");                    
        mfCdptran = entry.GetDouble("Cdptran");                  
        mfCdpsup = entry.GetDouble("Cdpsup");                   
        mfMcm = entry.GetDouble("Mcm");
        mfMsupm = entry.GetDouble("Msupm");
        cruiseSpeed_mps = entry.GetDouble("CruiseSpeed_mps");
        stallSpeed_mps = entry.GetDouble("StallSpeed_mps");
        
		thrustTable.clear();
		for (size_t idx=0; idx<tableAltitudes.size(); idx++)
		{
			wxString s;
			s.Printf("T%d", int(0.001f*tableAltitudes[idx]));
			float thrustFactor = entry.GetDouble(s.c_str());
			thrustTable.push_back(thrustFactor);
		}

		fuelEfficiencyTable.clear();
		for (size_t idx=0; idx<tableAltitudes.size(); idx++)
		{
			wxString s;
			s.Printf("FE%d", int(0.001f*tableAltitudes[idx]));
			float fuelEfficiency = entry.GetDouble(s.c_str());
			fuelEfficiencyTable.push_back(fuelEfficiency);
		}


        CalculateParams();
    }

    void tcJetDBObject::WriteSql(std::string& valueString)
    {
        tcAirDBObject::WriteSql(valueString);

        std::stringstream s;

        s << ",";

        s << militaryThrust_N << ",";
        s << militaryThrustSpeedSlope << ",";
        s << mfAfterburnThrust_N << ",";
        s << abThrustSpeedSlope << ",";
        s << mfAfterburnFuelRate_kgps << ",";
        s << mfCdpsub << ",";
        s << mfCdptran << ",";
        s << mfCdpsup << ",";
        s << mfMcm << ",";
        s << mfMsupm << ",";
        s << cruiseSpeed_mps << ",";
        s << stallSpeed_mps;


		for (size_t idx=0; idx<tableAltitudes.size(); idx++)
		{
			s << ",";
			s << thrustTable[idx];
		}

		for (size_t idx=0; idx<tableAltitudes.size(); idx++)
		{
			s << ",";
			s << fuelEfficiencyTable[idx];
		}

        valueString += s.str();

    }


    tcJetDBObject::tcJetDBObject()
    : invMachRange(0)
    {
        mnModelType = MTYPE_FIXEDWINGX;
        mnType = PTYPE_FIXEDWING; // functional classification

		if (tableAltitudes.size() == 0)
		{
			InitializeTableAltitudes();
		}
    }

    tcJetDBObject::tcJetDBObject(tcJetDBObject& obj)
        :   tcAirDBObject(obj), 
            invMachRange(obj.invMachRange),
            Cdi(obj.Cdi),
            militaryThrust_N(obj.militaryThrust_N),
            militaryThrustSpeedSlope(obj.militaryThrustSpeedSlope),
            mfAfterburnThrust_N(obj.mfAfterburnThrust_N),
            abThrustSpeedSlope(obj.abThrustSpeedSlope),
            mfAfterburnFuelRate_kgps(obj.mfAfterburnFuelRate_kgps),
            mfCdpsub(obj.mfCdpsub),
            mfCdptran(obj.mfCdptran),
            mfCdpsup(obj.mfCdpsup),
            mfMcm(obj.mfMcm),
            mfMsupm(obj.mfMsupm),
            cruiseSpeed_mps(obj.cruiseSpeed_mps),
            stallSpeed_mps(obj.stallSpeed_mps)
    {

		if (tableAltitudes.size() == 0)
		{
			InitializeTableAltitudes();
		}
    }


    tcJetDBObject::~tcJetDBObject()
    {
    }


}