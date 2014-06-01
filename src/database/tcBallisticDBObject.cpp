/**  
**  @file tcBallisticDBObject.cpp
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

#include "tcBallisticDBObject.h"
#include "math_constants.h"
#include "randfn.h"
#include "CsvTranslator.h"
#include "common/tinyxml.h"
#include "database/tcSqlReader.h"
#include <sstream>
#include "tcDatabase.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;

namespace database
{

    float tcBallisticDBObject::CalculateRangeKm(float altitude_m, float speed_mps)
    {
        switch (ballisticType)
        {
        case GUN_ROUND:
            return maxRange_km;
            break;
        case GRAVITY_BOMB:
            {
                altitude_m = std::min(altitude_m, maxLaunchAlt_m);
                float dropTime_s = sqrtf((2.0 / C_G) * altitude_m);
                float dist_m = speed_mps * dropTime_s;
                return std::min(0.001f * dist_m, maxRange_km);
            }
            break;
        case AUTO_CANNON:
        case CM_ROUND:
            return maxRange_km;
            break;
        case SMART_BOMB:
            if (smartMaxClimb_rad < 0)
            {
                altitude_m = std::min(altitude_m, maxLaunchAlt_m);
                float dist_m = altitude_m / atanf(-smartMaxClimb_rad);
                return std::min(0.001f * dist_m, maxRange_km);
            }
            else
            {
                return maxRange_km;
            }
            break;
		case ROCKET:
			return 0.968f*maxRange_km; // 0.968 assuming altitude AGL is 25% or less of slant range to target
			break;
        default:
            wxASSERT(false);
            return maxRange_km;
            break;
        }
    }

    void tcBallisticDBObject::CalculateParams()
    {
        if (launchSpeed_mps > 0)
        {
            one_over_launchSpeed = 1.0f / launchSpeed_mps;
        }
        else
        {
            one_over_launchSpeed = 1.0f;
        }
        launchSpeed2 = launchSpeed_mps * launchSpeed_mps;

        if ((ballisticType == AUTO_CANNON) && (burstCount <= 0))
        {
            fprintf(stderr, "Database warning - autocannon burst count must be at least 1, setting to 1 (%s)",
                mzClass.c_str());
            burstCount = 1;
        }
    }

	/**
	* Gets elevation for ballistic shell to hit (non-moving) target at a 
	* horizontal range of range_m and altitude difference of dz_m
	* (Altitude difference is ignored for now.)
	*
	* @param tti_s this field is set to time to impact target in seconds
	*/
	float tcBallisticDBObject::GetGunneryElevation(float range_m, float dz_m, float& tti_s)
	{
		float abs_dz_m = fabsf(dz_m);

		if (abs_dz_m > 50.0f) return GetGunneryElevation2(range_m, dz_m, tti_s);

		float launchSpeed = launchSpeed_mps;
		
		float fac = range_m * range_m * C_G2; // 4 * 0.25  = 1
		float b = -launchSpeed2;
		const float two_over_g = 2.0f / C_G;

		float b2 = b * b;
		if (b2 < fac)
		{
			tti_s = 0;
			return 0.25f * C_PI;
		}

		float vz = sqrtf( 0.5f * (-b - sqrtf(b2 - fac)) ); // "-b +" for lofted trajectory

		tti_s = two_over_g * vz;

		float elevation_rad = asinf(one_over_launchSpeed * vz);

		// if target altitude difference is negligible, return
		if (abs_dz_m < 2.0f) return elevation_rad;
		
		
		/* otherwise re-estimate with range adjusted for altitude difference.
		** This is a coarse approximation and will still have error.
		** A better approximation can be done using an enhanced quadratic (or
		** an iterative solution of the exact equation).
		*/
		wxASSERT(dz_m != 0);
		range_m +=  (dz_m / vz) * launchSpeed * cosf(elevation_rad);

		// update calculations with new range_m
		fac = range_m * range_m * C_G2; 

		if (b2 < fac)
		{
			tti_s = 0;
			return 0.25f * C_PI;
		}

		vz = sqrtf( 0.5f * (-b - sqrtf(b2 - fac)) ); 
		tti_s = two_over_g * vz;
		elevation_rad = asinf(one_over_launchSpeed * vz);

		return elevation_rad;
	}

    /**
    * @return range_m if not solution (e.g. shooting down for target above) or miss distance
    * positive miss distance means overshooting target
    */
    float tcBallisticDBObject::CalculateMissDistance(float range_m, float dz_m, float v_mps, float el_rad)
    {
        const float two_over_G = 2.0f / C_G;

        float vz_mps = v_mps * sinf(el_rad);
        float vxy_mps = v_mps * cosf(el_rad);

        float det = sqrtf(vz_mps*vz_mps - 2*C_G*dz_m);
        if (det < 0)
        {
            return range_m; // no solution
        }

        float tflight_s = (vz_mps + det) * C_GINV;
        float rangeFlight_m = vxy_mps * tflight_s;

        return rangeFlight_m - range_m;
    }

    float tcBallisticDBObject::CalculateBallisticElevation(float range_m, float dz_m, float v_mps, float min_x2, float& tti_s)
    {
        // solves dz = V*sqrt(1-X^2)*T - (1/2)G*T^2, 
        //     where V is launch speed, X is cos(el), V*X is horizontal speed, 
        //     V*sqrt(1-X^2) is vertical speed, G is gravity constant, and T is flight time (tti_s).
        //     T = (R/(V*X)) is substituted to get equations below.
        // min_x2 is minimum X^2 value to search, 0.25 is 60 deg elevation
        //
        

        // choose to solve for positive or negative elevation angle
        float elevationSign = 1.0f; // negative to shoot/drop down (dive bombing)
        if (dz_m < 0)
        {
            const float two_over_G = 2.0f / C_G;
            float tlevel_s = sqrtf(-dz_m * two_over_G);
            float levelRange_m = tlevel_s * v_mps;
            if (range_m < levelRange_m)
            {
                elevationSign = -1.0f;
            }
        }


		const float A = elevationSign*(range_m / dz_m);
		const float B = (C_G * range_m * range_m) / (2.0f * v_mps*v_mps * dz_m);
		float best_x2 = 0;
		float best_y = 1e9f;
		float last_y = 1e9f;
		bool searching = true;
		for (float x2=1.0; (x2>=min_x2)&&(searching); x2-=0.01f)
		{
			float y = fabsf(x2 - A*sqrtf(x2*(1-x2)) + B);
			if (y < best_y)
			{
				best_x2 = x2;
				best_y = y;
			}
			searching = (y < last_y);

			last_y = y;
		}

		// do fine search
		float start_x2 = best_x2 + 0.01f;
		float stop_x2 = best_x2 - 0.01f;
		searching = true;
		last_y = 1e9f;

		for (float x2=start_x2; (x2>=stop_x2)&&(searching); x2-=0.001f)
		{
			float y = fabsf(x2 - A*sqrtf(x2*(1-x2)) + B);
			if (y < best_y)
			{
				best_x2 = x2;
				best_y = y;
			}
			searching = (y < last_y);

			last_y = y;
		}

		// do finest search
		start_x2 = best_x2 + 0.0006f;
		stop_x2 = best_x2 - 0.0006f;
		searching = true;
		last_y = 1e9f;

		for (float x2=start_x2; (x2>=stop_x2)&&(searching); x2-=0.0001f)
		{
			float y = fabsf(x2 - A*sqrtf(x2*(1-x2)) + B);
			if (y < best_y)
			{
				best_x2 = x2;
				best_y = y;
			}
			searching = (y < last_y);

			last_y = y;
		}

		// do finest finest search
		start_x2 = best_x2 + 0.00006f;
		stop_x2 = best_x2 - 0.00006f;
		searching = true;
		last_y = 1e9f;

		for (float x2=start_x2; (x2>=stop_x2)&&(searching); x2-=0.00001f)
		{
			float y = fabsf(x2 - A*sqrtf(x2*(1-x2)) + B);
			if (y < best_y)
			{
				best_x2 = x2;
				best_y = y;
			}
			searching = (y < last_y);

			last_y = y;
		}

		float cos_el_rad = sqrtf(best_x2);
		float elevation_rad = elevationSign * acosf(cos_el_rad);
		tti_s = range_m / (v_mps * cos_el_rad);
		return elevation_rad;
    }

	/**
	* This version numerically solves for case with non-zero (or non-small) dz_m
	*/
	float tcBallisticDBObject::GetGunneryElevation2(float range_m, float dz_m, float& tti_s)
	{
		wxASSERT(fabsf(dz_m) > 1.0f);

        const float min_x2 = 0.25f; // 60 deg max elevation angle (cos(60 deg)^2 = 0.25)
        return CalculateBallisticElevation(range_m, dz_m, launchSpeed_mps, min_x2, tti_s);
	}

    /**
	* @return max level gun range in km
	*/
	float tcBallisticDBObject::GetMaxLevelGunRangeKm()
	{
        if (launchSpeed_mps > 0)
        {
            return std::min( 0.001f * launchSpeed_mps * launchSpeed_mps * C_GINV,
                maxRange_km);
        }
        else
        {
            return maxRange_km; // case for gravity bombs
        }
    }

    long tcBallisticDBObject::GetSensorKey()
    {
        wxASSERT(database);
        if (sensorKey != -1) return sensorKey;

        sensorKey = database->GetKey(sensorClass.c_str());

        // do not report error for missiles with no sensor (e.g. some AGMs)
        if ((sensorKey == -1) && (sensorClass.size() > 0))
        {
            wxString msg = wxString::Format("DATABASE WARNING - Could not find sensor (%s) for ballistic db class (%s)\n", sensorClass.c_str(), mzClass.c_str());
            fprintf(stderr, msg.c_str());
            wxMessageBox(msg);
        }

        return sensorKey;
    }


    /**
    * @return true if this obj is a gravity bomb
    */
    bool tcBallisticDBObject::IsGravityBomb() const
    {
        return (ballisticType == GRAVITY_BOMB);
    }

    /**
    * @return true if this obj is a gun round
    */
    bool tcBallisticDBObject::IsGunRound() const
    {
        return (ballisticType == GUN_ROUND);
    }

    bool tcBallisticDBObject::IsAutocannon() const
    {
        return (ballisticType == AUTO_CANNON);
    }

    bool tcBallisticDBObject::IsSmartBomb() const
    {
        return (ballisticType == SMART_BOMB);
    }

    bool tcBallisticDBObject::IsCMRound() const
    {
        return (ballisticType == CM_ROUND);
    }

    bool tcBallisticDBObject::IsRocket() const
    {
        return (ballisticType == ROCKET);
    }

	void tcBallisticDBObject::PrintToFile(tcFile& file) 
	{ 
		tcWeaponDBObject::PrintToFile(file);
	}


	/**
	* Adds sql column definitions to columnString. This is used for
	* SQL create table command
	*/
	void tcBallisticDBObject::AddSqlColumns(std::string& columnString)
	{
		tcWeaponDBObject::AddSqlColumns(columnString);

        columnString += ",";

        columnString += "BallisticType numeric,";
        columnString += "MaxRange_km numeric,";
        columnString += "AngleError_rad numeric,";
        columnString += "BurstCount numeric,";
        columnString += "BurstDuration_s numeric,";
		columnString += "ClusterCount numeric,";
		columnString += "ClusterEffectRadius_m numeric,";
        columnString += "SensorClass numeric,";
        columnString += "SmartMaxClimb_rad numeric,";
        columnString += "SmartError_m numeric,";
        columnString += "LockOnAfterLaunch numeric";
	}

	void tcBallisticDBObject::ReadSql(tcSqlReader& entry)
	{
		tcWeaponDBObject::ReadSql(entry);

        ballisticType = entry.GetInt("BallisticType");
        angleError_rad = entry.GetDouble("AngleError_rad");
        burstCount = entry.GetInt("BurstCount");
        burstDuration_s = entry.GetDouble("BurstDuration_s");
		clusterCount = (unsigned int)entry.GetInt("ClusterCount");
		clusterEffectRadius_m = entry.GetDouble("ClusterEffectRadius_m");
        sensorClass = entry.GetString("SensorClass").c_str();
        smartMaxClimb_rad = entry.GetDouble("SmartMaxClimb_rad");
        smartError_m = entry.GetDouble("SmartError_m");
        lockOnAfterLaunch = entry.GetInt("LockOnAfterLaunch") != 0;

        if (maxRange_km <= 0) maxRange_km = 20.0f; // set to 20 km for lack of better information

        if ((sensorClass.size() > 0) && (ballisticType == SMART_BOMB) && (mnModelType != MTYPE_LASERGUIDEDBOMB))
        {
            wxString msg = wxString::Format("DATABASE WARNING - Ballistic DB object %s, model type not set to Guided Bomb but has sensor\n", mzClass.c_str());
            fprintf(stderr, msg.c_str());
            wxMessageBox(msg);
        }

        if ((ballisticType == ROCKET) && (mnModelType != MTYPE_ROCKET))
        {
			mnModelType = MTYPE_ROCKET;
            wxString msg = wxString::Format("DATABASE WARNING - Ballistic DB object %s, model type not set to Rocket but ballistic type is Rocket--forced model type to ROCKET\n", mzClass.c_str());
            fprintf(stderr, msg.c_str());
			//wxASSERT(false);
        }

        CalculateParams();
	}

	void tcBallisticDBObject::WriteSql(std::string& valueString)
	{
		tcWeaponDBObject::WriteSql(valueString);

        std::stringstream s;

        s << ",";

        s << ballisticType << ",";
        s << angleError_rad << ",";
        s << burstCount << ",";
        s << burstDuration_s << ",";
		s << clusterCount << ",";
		s << clusterEffectRadius_m << ",";
        s << "'" << std::string(sensorClass.c_str()) << "',";
        s << smartMaxClimb_rad << ",";
        s << smartError_m << ",";
        s << lockOnAfterLaunch;

        valueString += s.str();
	}


	tcBallisticDBObject::tcBallisticDBObject() : tcWeaponDBObject(),
        ballisticType(GUN_ROUND),
        sensorKey(-1)
	{
		mzClass = "Default Ballistic";
	}

	tcBallisticDBObject::tcBallisticDBObject(const tcBallisticDBObject& obj) 
		: tcWeaponDBObject(obj),
        ballisticType(obj.ballisticType),
        sensorKey(-1)
	{
		wxASSERT(false); // ever called? if so need to update
	}

	tcBallisticDBObject::~tcBallisticDBObject() 
	{
	}

}

