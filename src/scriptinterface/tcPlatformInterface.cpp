/** 
**  @file tcPlatformInterface.cpp
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

#include "stdwx.h" // precompiled header file

#ifndef WX_PRECOMP
#include "wx/wx.h" 
#ifdef WIN32
#include "wx/msw/private.h" // for MS Windows specific definitions
#endif
#endif

#include <string>
#include "tcGameObject.h"
#include "tcMissileObject.h"
#include "tcSimState.h"
#include "simmath.h"
#include "tcPlatformInterface.h"
#include "tcFlightPortInterface.h"
#include "tcSound.h"
#include "tcSoundConsole.h"
#include "commandlist.h"
#include "tcCommandQueue.h"
#include "tcGameObjIterator.h"
#include "tcGroundVehicleObject.h"
#include "tcAeroAirObject.h"
#include "tcAirfieldObject.h"
#include "tcFlightOpsObject.h"
#include "tcGroundObject.h"
#include "tcHeloObject.h"
#include "tcAirDBObject.h"
#include "tcBallisticDBObject.h"
#include "tcBallisticMissileDBObject.h"
#include "tcPlatformDBObject.h"
#include "tcCounterMeasureDBObject.h"
#include "tcSonarDBObject.h"
#include "tcSonobuoyDBObject.h"
#include "tcSubObject.h"
#include "tcTorpedoDBObject.h"
#include "tcLauncherState.h"
#include "tcLauncher.h"
#include "tcMessageInterface.h"
#include "network/tcMultiplayerInterface.h"
#include "tcStores.h"
#include "tcTacticalMapView.h"
#include "ai/Brain.h"
#include "ai/Nav.h"
#include "ai/tcMissionManager.h"
#include "ai/tcAttackMission.h"
#include "tcDatabaseIterator.h"
#include "tcWeaponTester.h"
#include "tcScenarioRandomizer.h"
#include "tcSimPythonInterface.h"
#include "tcMissionInterface.h"
#include "tcGoalTracker.h"
#include "tcDamageModel.h"
#include "tcAllianceSensorMap.h"

//#include <atlbase.h> // for ATLTRACE2

#ifdef _DEBUG
#define new DEBUG_NEW
#endif 

using namespace boost::python;
using namespace ai;

namespace scriptinterface {

    bool tcPlatformInterface::IsDeveloperModeStatic()
    {
        return isDeveloperMode;
    }

    /**
    * Intended for access internal to game engine, not from scripts
    */
    tcScenarioInterface* tcPlatformInterface::GetScenarioInterfaceStatic()
    {
        return scenarioInterface;
    }

    std::string tcPlatformInterface::GetPlatformName() 
    {
        std::string s;
        if (mpPlatformObj == 0) 
        {
            s == "err";
        }
        else 
        {
            s = mpPlatformObj->mzUnit.c_str();
        }
        return s;
    }

    
    std::string tcPlatformInterface::GetPlatformClass() 
    {
        std::string s;
        if (mpPlatformObj == 0) 
        {
            s == "err";
        }
        else 
        {
            s = mpPlatformObj->mzClass.c_str();
        }
        return s;
    }

    long tcPlatformInterface::GetPlatformId() const
    {
        if (mpPlatformObj != 0)
        {
            return mpPlatformObj->mnID;
        }
        else
        {
            return -1;
        }
    }

    unsigned int tcPlatformInterface::GetPlatformAlliance() const
    {
        if (mpPlatformObj != 0)
        {
            return mpPlatformObj->GetAlliance();
        }
        else
        {
            wxASSERT(false);
            return 0;
        }
    }

    /**
    * @return sub interface object for sub-specific controls
    */
    tcSubInterface tcPlatformInterface::GetSubInterface()
    {
        return tcSubInterface(mpPlatformObj);
    }


    /**
    * @return longitude in rad
    */
    float tcPlatformInterface::GetLongitude() const
    {
        if (mpPlatformObj != 0)
        {
            return mpPlatformObj->mcKin.mfLon_rad;
        }
        else
        {
            return 0;
        }
    }

    /**
    * @return latitude in rad
    */
    float tcPlatformInterface::GetLatitude() const
    {
        if (mpPlatformObj != 0)
        {
            return mpPlatformObj->mcKin.mfLat_rad;
        }
        else
        {
            return 0;
        }
    }

    /**
    * @return altitude in m
    */
	float tcPlatformInterface::GetAltitude() const
    {
        if (mpPlatformObj != 0)
        {
            return mpPlatformObj->mcKin.mfAlt_m;
        }
        else
        {
            return 0;
        }
    } 


    /**
    * @return fraction of fuel remaining
    */
    float tcPlatformInterface::GetFuel() const
    {
        if (mpPlatformObj == 0) return 0;

        float fuelCapacity = mpPlatformObj->GetFuelCapacity();
        return (fuelCapacity > 0) ? (mpPlatformObj->fuel_kg / fuelCapacity) : 1.0f;
    }

    /**
    * Set fraction of fuel for platform (dev mode)
    */
    void tcPlatformInterface::SetFuelTest(float fuelFraction)
    {
        if (mpPlatformObj == 0) return;

        if (!isDeveloperMode) return;

        float fuelCapacity = mpPlatformObj->GetFuelCapacity();
        mpPlatformObj->fuel_kg = fuelFraction * fuelCapacity;
    }

    float tcPlatformInterface::GetMaxAltitude() 
    {
        if (tcAirObject* air = dynamic_cast<tcAirObject*>(mpPlatformObj))
        {
            return air->mpDBObject->maxAltitude_m;
        }
        else
        {
            return 0;
        }
    }

    float tcPlatformInterface::GetSpeed() 
    {
        if (mpPlatformObj == 0) return 0;
        return mpPlatformObj->mcKin.mfSpeed_kts;
    }

    /**
    * @return range in km
    */
    float tcPlatformInterface::GetCruiseRangeForAltitude(float alt_m)
    {
        if (tcAirObject* air = dynamic_cast<tcAirObject*>(mpPlatformObj))
        {
            return air->GetCruiseRangeKm(alt_m);
        }
        else
        {
            return 0;
        }
    }

    float tcPlatformInterface::GetCruiseSpeedForAltitude(float alt_m)
    {
        if (tcAirObject* air = dynamic_cast<tcAirObject*>(mpPlatformObj))
        {
            return air->GetCruiseSpeedForAltitude(alt_m);
        }
        else
        {
            return 0;
        }
    }

    float tcPlatformInterface::GetCruiseAltitude() const
    {
        if (tcAirObject* air = dynamic_cast<tcAirObject*>(mpPlatformObj))
        {
            return air->GetCruiseAltitude();
        }
        else
        {
            return 0;
        }
    }

    float tcPlatformInterface::GetStallSpeedForAltitude(float alt_m)
    {
        if (tcAirObject* air = dynamic_cast<tcAirObject*>(mpPlatformObj))
        {
            return air->GetStallSpeedForAltitude(alt_m);
        }
        else
        {
            return 0;
        }
    }

	float tcPlatformInterface::GetMaxSpeed()
	{
		if (mpPlatformObj == 0) return 0;

		float alt_m = mpPlatformObj->mcKin.mfAlt_m;

		return GetMaxSpeedForAltitude(alt_m);
	}

    float tcPlatformInterface::GetMaxSpeedForAltitude(float alt_m) 
    {
        if (mpPlatformObj == 0) return 0;

        if (tcAeroAirObject* aaObj = dynamic_cast<tcAeroAirObject*>(mpPlatformObj) )
        {
            float maxSpeed_mps;
            float fuelRate_kgps;
            aaObj->CalculateSpeedParams(alt_m, 1.0f, maxSpeed_mps, fuelRate_kgps, aaObj->GetDamageLevel(), aaObj->mpDBObject);
            return C_MPSTOKTS*maxSpeed_mps;
        }
        else
        {
            tcSubObject* sub = dynamic_cast<tcSubObject*>(mpPlatformObj);
            if (sub == 0)
            {
                return mpPlatformObj->mpDBObject->mfMaxSpeed_kts;
            }
            else
            {
                return sub->GetMaxSpeedForDepth(alt_m);
            }
        }

    }

    float tcPlatformInterface::GetMaxSpeedForAltitudeAB(float alt_m) 
    {
        if (mpPlatformObj == 0) return 0;

        if (tcAeroAirObject* aaObj = dynamic_cast<tcAeroAirObject*>(mpPlatformObj) )
        {
            float maxSpeed_mps;
            float fuelRate_kgps;
            aaObj->CalculateSpeedParams(alt_m, 2.0f, maxSpeed_mps, fuelRate_kgps, aaObj->GetDamageLevel(), aaObj->mpDBObject);
            return C_MPSTOKTS*maxSpeed_mps;
        }
        else
        {
			return 0;
        }

    }


    float tcPlatformInterface::GetThrottle()
    {
        if (mpPlatformObj == 0) return -1.0f;

        if (tcAeroAirObject* aaObj = dynamic_cast<tcAeroAirObject*>(mpPlatformObj) )
        {
            return aaObj->GetThrottleFraction();
        }
        else
        {
            return -1.0f;
        }
    }

    float tcPlatformInterface::GetHeading() 
    {
        if (mpPlatformObj == 0) return 0;
        return C_180OVERPI*mpPlatformObj->mcKin.mfHeading_rad;
    }

    float tcPlatformInterface::GetHeadingRad() 
    {
        if (mpPlatformObj == 0) return 0;
        return mpPlatformObj->mcKin.mfHeading_rad;
    }

    /**
    * Get landing state (gear up/down).
    * @return 1 gear down/ready to land, 0 otherwise or bad object
    */
    int tcPlatformInterface::GetLandingState()
    {
        if (tcAirObject *air = dynamic_cast<tcAirObject*>(mpPlatformObj))
        {
            return air->readyForLanding;
        }
        return 0;
    }

	/**
	* Get terrain elevation for (lon_rad, lat_rad). Over water this
	* returns a negative number for water depth.
	* @return terrain elevation in meters
	*/
	float tcPlatformInterface::GetMapTerrainElevation(float lon_rad, float lat_rad)
	{
		wxASSERT(mapData);

		return mapData->GetTerrainHeight(lon_rad * C_180OVERPI, lat_rad * C_180OVERPI,
			mpSimState->GetTime());
	}

    /**
    * Get terrain elevation for current position. Over water this
    * returns a negative number for water depth.
    * @return terrain elevation in meters
    */
    float tcPlatformInterface::GetTerrainElevation()
    {
        if (!mpPlatformObj) return 0; // error 
        return mpPlatformObj->GetTerrainElevation();
    }

    /**
    * @return true if object has a throttle control (aero-modeled aircraft)
    */
    bool tcPlatformInterface::HasThrottle()
    {
        if (tcAeroAirObject* aaObj = dynamic_cast<tcAeroAirObject*>(mpPlatformObj) )
        {
            return true;
        }
        else
        {
            return false;
        }
    }

	void tcPlatformInterface::SetAltitude(float alt_m) 
	{
        if (mpPlatformObj == 0) return;
		if (!mpPlatformObj->IsControlled()) return;

		mpPlatformObj->SetAltitude(alt_m);
        SetPitchLimitDeg(85.0);
	} 

    /**
    * Set state to 1 to land object if near appropriate flightport.
    * Set to 0 to clear. Only applies to air units.
    */
    void tcPlatformInterface::SetLandingState(int state)
    {
        if (mpPlatformObj == 0) return;
		if (!mpPlatformObj->IsControlled()) return;
        if (tcAirObject *air = dynamic_cast<tcAirObject*>(mpPlatformObj))
        {
            air->SetLandingState(state);
        }
    }

    /**
    * Applies to air objects only. Sets pitch angle limit. This is
    * used to restrict the rate of climb/descent e.g. when landing
    */
    void tcPlatformInterface::SetPitchLimitDeg(float lim_deg)
    {
        if (tcAirObject *air = dynamic_cast<tcAirObject*>(mpPlatformObj))
        {
            air->SetPitchLimit(lim_deg*C_PIOVER180);
        }
    }

    float tcPlatformInterface::GetClimbDeg()
    {
        if (mpPlatformObj != 0)
        {
            return C_180OVERPI * mpPlatformObj->mcKin.mfClimbAngle_rad;
        }
        else
        {
            return 0;
        }
    }

    void tcPlatformInterface::SetClimbDeg(float angle_deg)
    {
        if (tcAirObject *air = dynamic_cast<tcAirObject*>(mpPlatformObj))
        {
            air->SetClimbCommand(angle_deg*C_PIOVER180);
        }
    }

    void tcPlatformInterface::SetClimbRad(float angle_rad)
    {
        if (tcAirObject *air = dynamic_cast<tcAirObject*>(mpPlatformObj))
        {
            air->SetClimbCommand(angle_rad);
        }
    }

    /**
    * Only allowed for air objects. Sets maximum turn rate, useful
    * for doing slow turns for patrol orbits
    */
    void tcPlatformInterface::SetMaxTurnRate(float rate_degps)
    {
        if (tcAirObject *air = dynamic_cast<tcAirObject*>(mpPlatformObj))
        {
            air->SetMaxTurnRate(rate_degps);
        }
    }

	void tcPlatformInterface::SetSpeed(float speed_kts) 
	{
        if (mpPlatformObj == 0) return;
		if (!mpPlatformObj->IsControlled()) return;

        float maxSpeed_kts = GetMaxSpeed();

        mpPlatformObj->SetSpeed(std::min(speed_kts, maxSpeed_kts));
	}

    /**
    * Sets speed to max speed or max military power for aero modeled aircraft.
    */
    void tcPlatformInterface::SetSpeedToMax() 
    {
        if (mpPlatformObj == 0) {return;}
	    if (!mpPlatformObj->IsControlled()) return;

        if (tcAeroAirObject* aaObj = dynamic_cast<tcAeroAirObject*>(mpPlatformObj))
        {
            aaObj->SetThrottleFraction(1.0f);
        }
        else if (tcSubObject* sub = dynamic_cast<tcSubObject*>(mpPlatformObj))
        {
            SetSpeed(sub->GetMaxSpeedForDepth(mpPlatformObj->mcKin.mfAlt_m));
        }
        else
        {
            float fMaxSpeed_kts = mpPlatformObj->mpDBObject->mfMaxSpeed_kts;
            SetSpeed(fMaxSpeed_kts);
        }

    }

    void tcPlatformInterface::SetThrottle(float throttleFraction)
    {
        if (mpPlatformObj == 0) {return;}
	    if (!mpPlatformObj->IsControlled()) return;
        if (tcAeroAirObject* aaObj = dynamic_cast<tcAeroAirObject*>(mpPlatformObj))
        {
            aaObj->SetThrottleFraction(throttleFraction);
        }
    }

    /**
    * @return id of leader of formation being edited or -1 if none
    */
    long tcPlatformInterface::GetFormationEditId() const
    {
        wxASSERT(tacticalMap != 0);

        return tacticalMap->GetFormationEditId();
    }

    long tcPlatformInterface::GetFormationLeader() const
    {
        if (mpPlatformObj == 0) return -1;

        return mpPlatformObj->formation.leaderId;
    }

    void tcPlatformInterface::SetFormationAltitudeOffset(float dh_m)
    {
        if (mpPlatformObj == 0) {return;}

        mpPlatformObj->SetFormationAltitudeOffset(dh_m);
    }

	/**
	* @return formation altitude offset in meters
	*/
    float tcPlatformInterface::GetFormationAltitudeOffset() const
    {
        if (mpPlatformObj == 0) {return 0;}

        return mpPlatformObj->formation.altitudeOffset_m;
    }

    /**
    *
    */
    void tcPlatformInterface::SetFormationLeader(long id)
    {
        if (mpPlatformObj == 0) {return;}

        if (id < 0) // break formation request
        {
            mpPlatformObj->SetFormationLeader(-1);
            UpdateMissionEditGraphics();
            return;
        }

        tcPlatformObject* leader = dynamic_cast<tcPlatformObject*>(mpSimState->GetObject(id));
        
        if ((id == mpPlatformObj->mnID) || (leader == 0)) return;

        bool typeMatch = false;

        if (IsSurface() && (dynamic_cast<tcSurfaceObject*>(leader) != 0)) typeMatch = true;
        if (IsAir() && (dynamic_cast<tcAirObject*>(leader) != 0)) typeMatch = true;

        if (typeMatch)
        {
            mpPlatformObj->SetFormationLeader(id);
            UpdateMissionEditGraphics();
        }
        else
        {
            return;
        }
    }

    void tcPlatformInterface::SetFormationMode(int mode)
    {
        if (mpPlatformObj == 0) {return;}

        // FOLLOW = 1, ///< stay in center of formation sector
		// SPRINTDRIFT = 2 ///< alternate slow drift periods, with sprint to catch up to formation
        if (IsInFormation())
        {
            mpPlatformObj->SetFormationMode(mode);
        }
    }

    int tcPlatformInterface::GetFormationMode() const
    {
        if (mpPlatformObj == 0) {return 0;}

        // FOLLOW = 1, ///< stay in center of formation sector
		// SPRINTDRIFT = 2 ///< alternate slow drift periods, with sprint to catch up to formation
        if (IsInFormation())
        {
            return mpPlatformObj->formation.formationMode;
        }
		else
		{
			return 0;
		}
    }

    void tcPlatformInterface::SetFormationUseNorthBearing(bool state)
    {
        if (mpPlatformObj == 0) {return;}

        mpPlatformObj->formation.SetUseNorthBearing(state);
    }

	bool tcPlatformInterface::IsFormationUsingNorthBearing() const
	{
		if (mpPlatformObj != 0) 
		{
			return mpPlatformObj->formation.useNorthBearing;
		}
		else
		{
			return false;
		}
	}

    void tcPlatformInterface::SetFormationPosition(float range_km, float span_km, float bearing_rad, float span_rad)
    {
        if (mpPlatformObj == 0) {return;}

        mpPlatformObj->SetFormationPosition(range_km, span_km, bearing_rad, span_rad);
    }

    tcFormationPosition tcPlatformInterface::GetFormationPosition() 
	{
		tcFormationPosition result;
		result.bearing_rad = 0;
		result.range_km = 0;
		result.span_km = 0;
		result.span_rad = 0;

		if (mpPlatformObj != 0)
		{
			result.bearing_rad = 0;
			result.range_km = 0;
			result.span_km = 0;
			result.span_rad = 0;
		}

		return result;
    }

    bool tcPlatformInterface::IsInFormation() const
    {
        if (mpPlatformObj == 0) return false;

        return mpPlatformObj->formation.isActive;
    }

    bool tcPlatformInterface::IsFormationLeader() const
    {
        if (mpPlatformObj == 0) return false;

        return mpPlatformObj->formation.IsLeader();
    }

    void tcPlatformInterface::SetFormationEdit(bool state)
    {
        if (mpPlatformObj == 0) return;

        wxASSERT(mpCommandQueue != 0);
        if (mpCommandQueue == 0) return;

        if (state == false) // allow any platform to clear edit
        { 
            mpCommandQueue->AddCommand("SetFormationEditId", -1);
            return;
        }

        // formation must be active to enable edit
        if (!mpPlatformObj->formation.isActive) return;

        // if not leader, then send leader id for edit
        if (mpPlatformObj->formation.IsLeader())
        {
            mpCommandQueue->AddCommand("SetFormationEditId", mpPlatformObj->mnID);
        }
        else
        {
            mpCommandQueue->AddCommand("SetFormationEditId", mpPlatformObj->formation.leaderId);
        }
    }



	bool tcPlatformInterface::IsSurface() const 
	{
        if (mpPlatformObj == 0) return false;

		return (mpPlatformObj->mnModelType == MTYPE_SURFACE) ||
            (mpPlatformObj->mnModelType == MTYPE_CARRIER);
	}

	/// returns true if platform is an air platform
	bool tcPlatformInterface::IsAir() const
	{
        if (mpPlatformObj == 0) return false;

		UINT32 nModelType = mpPlatformObj->mnModelType;
		return (nModelType == MTYPE_FIXEDWING)||(nModelType == MTYPE_FIXEDWINGX)
			||(nModelType == MTYPE_AIR)||(nModelType == MTYPE_HELO);
	}

    bool tcPlatformInterface::IsGroundVehicle() const
    {
        if (mpPlatformObj == 0) return false;
		return (mpPlatformObj->mnModelType == MTYPE_GROUNDVEHICLE);
    }

	/// returns true if platform is a helo
	bool tcPlatformInterface::IsHelo() const
	{
        if (mpPlatformObj == 0) return false;
		return (mpPlatformObj->mnModelType == MTYPE_HELO);
	}

	bool tcPlatformInterface::IsFixed() const
	{
        if (mpPlatformObj == 0) return false;
		return (mpPlatformObj->mnModelType == MTYPE_FIXED) ||
			(mpPlatformObj->mnModelType == MTYPE_AIRFIELD);
	}

	/// returns true if platform is a submarine
	bool tcPlatformInterface::IsSub() const
	{
        if (mpPlatformObj == 0) return false;
		return (mpPlatformObj->mnModelType == MTYPE_SUBMARINE);
	}




    tcGameObject* tcPlatformInterface::GetTargetObj() 
    {
        wxASSERT(mpSimState != 0);
        return mpSimState->GetObject(GetTarget());
    }

    void tcPlatformInterface::SetTarget(long anID) 
    {
        if (mpPlatformObj == 0) return;
		if (!mpPlatformObj->IsControlled()) return;
        mpPlatformObj->DesignateTarget(anID);
    }

    long tcPlatformInterface::GetTarget() 
    {
        if (mpPlatformObj == 0) return -1;
        return mpPlatformObj->GetBrain()->GetTarget();
    }

    float tcPlatformInterface::GetRangeToTarget() 
    {
        if (mpPlatformObj == 0) return 0;
        tcSensorMapTrack track;
        if (!GetTargetTrack(track))
        {
            return 0;
        }
        return mpPlatformObj->mcKin.RangeToKm(track);
    }   

    // return false if no track , otherwise true
    bool tcPlatformInterface::GetTargetTrack(tcSensorMapTrack& track)
    {
        if (mpPlatformObj == 0) return false;
        tcGameObject* pGameObj = GetTargetObj();

        /* return truth data if obj found and own alliance
        ** On client machine, only own-alliance objects exist in sim state
        */
		bool isOwnAlliance = pGameObj && (pGameObj->GetAlliance() == mpPlatformObj->GetAlliance());
        if (pGameObj && isOwnAlliance)
        {
            tcKinematics *pTargetKin = &pGameObj->mcKin;
            track.mnID = pGameObj->mnID;
			track.mfTimestamp = pGameObj->mfStatusTime;
            track.mfAlt_m = pTargetKin->mfAlt_m;
            track.mfHeading_rad = pTargetKin->mfHeading_rad;
            track.mfLat_rad = (float)pTargetKin->mfLat_rad;
            track.mfLon_rad = (float)pTargetKin->mfLon_rad;
            track.mfSpeed_kts = pTargetKin->mfSpeed_kts;
			track.mnFlags = TRACK_SPEED_VALID | TRACK_HEADING_VALID |
				TRACK_ALT_VALID;

            track.mnClassification = pGameObj->mpDBObject->mnType;
            track.mnAffiliation = tcAllianceInfo::FRIENDLY;
            track.engaged.clear();
            track.intercepts.clear();
            track.assessedDamage = pGameObj->GetDamageLevel();
			

            return true;
        }
        else // check for sensor track
        {
            tcSensorMapTrack *smtrack = 
                mpSimState->mcSensorMap.GetSensorMapTrack(GetTarget(), mpPlatformObj->GetAlliance());
            if (smtrack)
            {
                track = *smtrack;
                return true;
            }
            else
            {
                track.mnID = NULL_INDEX;
                return false;
            }
        }
    }

	/**
	* @param class_mask see below:
	* PTYPE_UNKNOWN 0x0000
	* PTYPE_SURFACE 0x0010
	* PTYPE_SMALLSURFACE 0x0011
	* PTYPE_LARGESURFACE 0x0012
	* PTYPE_CARRIER 0x0014
	* PTYPE_AIR 0x0020
	* PTYPE_FIXEDWING 0x0021
	* PTYPE_HELO 0x0022
	* PTYPE_MISSILE 0x0040
	* PTYPE_SUBSURFACE 0x0080
	* PTYPE_SUBMARINE 0x0081
	* PTYPE_TORPEDO 0x0082
	* PTYPE_SONOBUOY 0x0084
	* PTYPE_GROUND 0x0100
	* PTYPE_AIRFIELD 0x0101
	* PTYPE_BALLISTIC 0x0200
	*/
	bool tcPlatformInterface::IsEquippedForTargetType(unsigned int class_mask)
	{
		if (mpPlatformObj == 0)
		{
			wxASSERT(false);
			return false;
		}

		size_t nLaunchers = mpPlatformObj->GetLauncherCount();
		for (size_t n=0; n<nLaunchers; n++)
		{
			tcLauncher* launcher = mpPlatformObj->GetLauncher(n);
			wxASSERT(launcher != 0);

			if (launcher->IsEffective(class_mask)) return true;
		}

		return false;
	}

    bool tcPlatformInterface::IsLauncherEffective(int anLauncher) 
    {
        if (mpPlatformObj == 0) return false;
		tcLauncher* pLauncher = mpPlatformObj->GetLauncher(anLauncher);
		if (pLauncher == 0) return false; // bad launcher index

        tcSensorMapTrack track;
        if (GetTargetTrack(track) == false) 
        {
            return false;
        }

		return pLauncher->IsEffective(track);
    }

    tcSensorMapTrack tcPlatformInterface::GetTargetTrackInfo() 
    {
        tcSensorMapTrack track;

        GetTargetTrack(track);

        double t = mpSimState->GetTime();
        tcSensorMapTrack predictedTrack(track);
        track.GetPrediction(predictedTrack, t);

        return predictedTrack;
    }

	float tcPlatformInterface::GetLauncherInterceptTime(int anLauncher, 
		tcSensorMapTrack& track)
	{
		wxASSERT(mpPlatformObj);
        if (mpPlatformObj == 0) return 0;

		tcLauncherState* launcherState;
		mpPlatformObj->GetLauncherState(launcherState);

		if (launcherState)
		{
			return launcherState->EstimateInterceptTimeForLauncher(anLauncher, track);
		}
		else
		{
			fprintf(stderr, "tcPlatformInterface::EstimateLauncherInterceptTime"
				" - NULL launcherState\n");
			return 0;
		}
	}

	tcAllianceROEInfo tcPlatformInterface::GetROE() const
    {		
		tcAllianceROEInfo result;

		result.airROE = 99;
		result.surfaceROE = 99;
		result.subROE = 99;
		result.landROE = 99;

		if (mpPlatformObj == 0) return result;

		int alliance = int(mpPlatformObj->GetAlliance());

		tcGoalTracker::ROEStatus roeStatus = tcGoalTracker::Get()->GetAllianceROE(alliance);

		result.airROE = roeStatus.airMode;
		result.surfaceROE = roeStatus.surfMode;
		result.subROE = roeStatus.subMode;
		result.landROE = roeStatus.landMode;

		return result;
	}

	/**
	*
	*/
	void tcPlatformInterface::SetHeading(float heading_deg) 
	{
        if (mpPlatformObj == 0) return;

		if (!mpPlatformObj->IsControlled()) return;

        wxASSERT((heading_deg >= -720.0f) && (heading_deg <= 720.0f));

        if ((heading_deg >= -720.0f) && (heading_deg <= 720.0f))
        {
            heading_deg = fmodf(heading_deg, 360.0f); // negative result for negative heading
		    mpPlatformObj->SetHeading(C_PIOVER180*heading_deg);
        }
	}

	/**
	*
	*/
	void tcPlatformInterface::SetHeadingRad(float heading_rad) 
	{
        if (mpPlatformObj == 0) return;

		if (!mpPlatformObj->IsControlled()) return;

        if ((heading_rad >= -12.5f) && (heading_rad <= 12.5f))
        {
            heading_rad = fmodf(heading_rad, C_TWOPI); // negative result for negative heading
		    mpPlatformObj->SetHeading(heading_rad);
        }
	}

    /**
    * If target is valid, sets heading to intercept target.
    * @return time to intercept in seconds
    */
    float tcPlatformInterface::SetHeadingToInterceptTarget() 
    {   
        if (mpPlatformObj == 0) return 0;

		if (!mpPlatformObj->IsControlled()) return 0;
        tcSensorMapTrack track;
        float fHeading_rad, fTTI;

        if (GetTargetTrack(track)==false) {return 0;}

        mpPlatformObj->mcKin.GetInterceptData2D(track, fHeading_rad, fTTI);
        mpPlatformObj->SetHeading(fHeading_rad);
        return fTTI;
    }

    /**
    * @return heading in deg to datum
    */
    float tcPlatformInterface::GetHeadingToDatum(float afLon_rad, float afLat_rad) 
    {
        if (mpPlatformObj == 0) return 0;

        GeoPoint p;
        p.mfAlt_m = 0;
        p.mfLon_rad = afLon_rad;
        p.mfLat_rad = afLat_rad;
        float heading_rad = mpPlatformObj->mcKin.HeadingToGeoRad(&p);
        wxASSERT(fabsf(heading_rad) <= C_TWOPI);

        return heading_rad*C_180OVERPI;
    }

    float tcPlatformInterface::GetRangeToDatum(float afLon_rad, float afLat_rad) 
    {
        if (mpPlatformObj == 0) return 0;

        GeoPoint p;
        p.mfAlt_m = 0;
        p.mfLon_rad = afLon_rad;
        p.mfLat_rad = afLat_rad;
        float range_km = mpPlatformObj->mcKin.RangeToKm(&p);
        return range_km;
    }

    /**
    * @return true if this platform can refuel in flight (receive fuel)
    */
    bool tcPlatformInterface::CanRefuelInFlight() const
    {
        if ((mpPlatformObj == 0) || (!mpPlatformObj->IsControlled())) return false;

        tcAirObject* air = dynamic_cast<tcAirObject*>(mpPlatformObj);
        
        return (air != 0) && (air->CanRefuelInFlight());
    }

    /**
    * Start in-flight refuel with tanker <id>
    * @return true if success, false if not started for any reason
    */
    bool tcPlatformInterface::StartRefuelWith(long id)
    {
        if ((mpPlatformObj == 0) || (!mpPlatformObj->IsControlled())) return false;

        tcAirObject* tanker = dynamic_cast<tcAirObject*>(mpSimState->GetObject(id));
        if (tanker == 0) return false;

        return tanker->AddFuelTarget(mpPlatformObj->mnID);
    }

    /**
    * @return true if <id> is a tanker aircraft
    */
    bool tcPlatformInterface::IsTankerAircraft(long id)
    {
        if ((mpPlatformObj == 0) || (!mpPlatformObj->IsControlled())) return false;

        tcAirObject* tanker = dynamic_cast<tcAirObject*>(mpSimState->GetObject(id));
        if (tanker == 0) return false;
        if (tanker->GetAffiliationWith(mpPlatformObj) == tcAllianceInfo::FRIENDLY)
        {
            return tanker->IsTanker() && (tanker->fuel_kg > 0.1*tanker->GetFuelCapacity());
        }
        else
        {
            return false;
        }
    }

    /**
    * @return number of tanker spots currently free in tanker <id>
    */
    unsigned int tcPlatformInterface::GetTankerSpotsFree(long id)
    {
        if ((mpPlatformObj == 0) || (!mpPlatformObj->IsControlled())) return 0;

        tcAirObject* tanker = dynamic_cast<tcAirObject*>(mpSimState->GetObject(id));
        if (tanker == 0) return 0;
        if (tanker->GetAffiliationWith(mpPlatformObj) == tcAllianceInfo::FRIENDLY)
        {
            return tanker->TankerSpotsFree();
        }
        else
        {
            return 0;
        }
    }



    /**
	* @return best launcher for target, best.mnLauncher set to -1 if 
    * no compatible launchers or no target is selected
	*/
    tcLauncherInfo tcPlatformInterface::GetBestLauncher() 
    {
        tcLauncherInfo best;
        best.mnLauncher = -1;
        best.mfRange_km = 0;
        best.minRange_km = 0;
        best.maxRange_km = 0;
        best.sectorCenter = 0;
        best.sectorWidth = 0;
        best.mnTargetFlags = 0;

        if (mpPlatformObj == 0) return best;

        tcSensorMapTrack track;
        if (!GetTargetTrack(track)) {return best;}

        // get range to target
        float mfTargetRange = mpPlatformObj->mcKin.RangeToKm(track);

        // set target type
        int nTargetType;

        if (track.IsSurface())
        {
            nTargetType = SURFACE_TARGET;
        }
        else if (track.IsAir())
        {
            nTargetType = AIR_TARGET;
        }
        else if (track.IsMissile())
        {
            nTargetType = MISSILE_TARGET;
        }
        else if (track.IsSub())
        {
            nTargetType = SUBSURFACE_TARGET;
        }
		else if (track.IsGround())
		{
			nTargetType = LAND_TARGET;
		}
        else 
        {
            nTargetType = 0; // error, unknown target type
        }

        // cheating, but don't allow AAMs to be targeted
        bool isAAM = false;
        if (nTargetType == MISSILE_TARGET)
        {
            const tcGameObject* target = track.GetAssociatedConst();
            const tcWeaponDBObject* weaponData = (target != 0) ? dynamic_cast<tcWeaponDBObject*>(target->mpDBObject) : 0;
            if (weaponData != 0)
            {
                isAAM = (weaponData->targetFlags & (AIR_TARGET | MISSILE_TARGET)) != 0;
            }
            else
            {
                wxASSERT(target == 0);
            }
            if (isAAM) return best;
        }


        std::vector<tcLauncherInfo> launcherInfoInRange;
        std::vector<tcLauncherInfo> launcherInfoOutOfRange;

        // return longest range launcher if target out of range
        // or shortest range launcher if target is in range
        int nCount = GetLauncherCount();
		for (int n=0;n<nCount;n++) 
		{
			tcLauncherInfo info;
			bool launcherValid = GetLauncherInfo(info, n);
            bool launcherOperational = launcherValid && ((info.launcherStatus == tcLauncher::LAUNCHER_READY) || 
                                       (info.launcherStatus != tcLauncher::DAMAGED) && 
				                       (info.launcherStatus != tcLauncher::LAUNCHER_EMPTY) && 
                                       (info.launcherStatus != tcLauncher::LAUNCHER_LOADING) &&
                                       (info.launcherStatus != tcLauncher::LAUNCHER_UNLOADING) &&
                                       (info.launcherStatus != tcLauncher::FC_BUSY));

            bool bCompatible = ((info.mnTargetFlags & nTargetType) != 0) &&
                               (!info.isARM || (track.GetEmitterCount() > 0));

			if (bCompatible && launcherOperational) 
			{
                bool inRangeCalculated = true;
                if (tcMissileDBObject* missileData = dynamic_cast<tcMissileDBObject*>(info.weaponData))
                {
                    tcSensorMapTrack targetTrack(track);
                    tcKinematics missileKin(mpPlatformObj->mcKin);
                    if (nTargetType != MISSILE_TARGET)
                    {
                        // assume target moving away for everything except missiles
                        float bearing_rad = mpPlatformObj->mcKin.HeadingToTrack(targetTrack);
                        targetTrack.mfHeading_rad = bearing_rad;
                    }
                    targetTrack.mfAlt_m = std::max(targetTrack.mfAlt_m - 200.0f, 5.0f); // assume altitude lower to be more conservative in range estimate
                    inRangeCalculated = tcMissileObject::EvaluateTarget(missileKin, targetTrack, missileData);

                    //if ((!inRangeCalculated) && (info.mfRange_km > mfTargetRange))
                    //{   // if not calculated in range, set range less than target range (not sure if necessary or how this affects behavior in the end)
                    //    info.mfRange_km = mfTargetRange - 5.0f;   
                    //}
                }

				bool isInRange = (mfTargetRange <= info.mfRange_km) && (mfTargetRange >= info.minRange_km) && inRangeCalculated;
 

                if (isInRange)
                {
                    launcherInfoInRange.push_back(info);
                }
                else
                {
                    launcherInfoOutOfRange.push_back(info);
                }


                if (isInRange && (info.mfRange_km < best.mfRange_km) && (info.mnLaunchMode != 4))  // exclude autocannon
				{
					best = info;
				}
				else if (info.mfRange_km > best.mfRange_km) 
				{
					best = info;
				}
			}

        } // for (int n=0;n<nCount;n++) 


        // if any launchers are in range, return one with shortest nominal range (to avoid wasting long-range weapons)
        if (launcherInfoInRange.size() > 0)
        {
            best.mfRange_km = 99999;
            for (size_t n=0; n<launcherInfoInRange.size(); n++)
            {
                if (launcherInfoInRange[n].mfRange_km < best.mfRange_km)
                {
                    best = launcherInfoInRange[n];
                }
            }
        }
        else // report longest range launcher (why do this? FEB 2012)
        {
            best.mfRange_km = 0;
            for (size_t n=0; n<launcherInfoOutOfRange.size(); n++)
            {
                if (launcherInfoOutOfRange[n].mfRange_km > best.mfRange_km)
                {
                    best = launcherInfoOutOfRange[n];
                }
            }
        }


		return best;
    }

    tcLauncherInfo tcPlatformInterface::GetLauncherInfoByValue(int launcher)
    {
        tcLauncherInfo info;

        GetLauncherInfo(info, launcher);
        
        return info;
    }


	/**
	* @return true if valid launcher
	*/
	bool tcPlatformInterface::GetLauncherInfo(scriptinterface::tcLauncherInfo& info, int anLauncher)
    {
        if ((mpPlatformObj == 0) || (anLauncher < 0)) return false;

        info.mnLauncher = -1;
        info.launcherStatus = tcLauncher::LAUNCHER_BUSY;
		info.mnLaunchMode = -1;
        info.isARM = false;
        info.minLaunchAlt_m = 0;
        info.maxLaunchAlt_m = 0;
        info.minRange_km = 0;
        info.maxRange_km = 0;
        info.speed_mps = 0;
        info.isNuclear = false;
        info.isLoading = false;
        info.acceptsWaypoints = false;
        info.weaponData = 0;
        info.lifeTime_s = 0;

        tcLauncher* pLauncher = mpPlatformObj->GetLauncher(anLauncher);
        if (pLauncher == 0)
		{
			wxASSERT(false);
			return false;
		}

        info.launcherStatus = pLauncher->GetLauncherStatus();
        info.mnLauncher = anLauncher;
        info.mnQuantity = pLauncher->mnUncommitted;
        info.mnTargetFlags = pLauncher->mnTargetFlags;
        info.isLoading = (info.launcherStatus == tcLauncher::LAUNCHER_LOADING) ||
                         (info.launcherStatus == tcLauncher::LAUNCHER_UNLOADING);

        // convert engagement sector values to degrees
        info.sectorCenter = C_180OVERPI * pLauncher->GetSectorCenter();
        info.sectorWidth = C_180OVERPI * pLauncher->GetSectorWidth();
        wxASSERT(fabsf(info.sectorCenter) <= 360.0f);

		info.fireControlTracks = pLauncher->GetFireControlTrackCount();
		info.maxFireControlTracks = pLauncher->GetMaxFireControlTracks();

        info.maxDepth_m = 0;

        bool isGunRound = false;

        tcWeaponDBObject* weaponData = dynamic_cast<tcWeaponDBObject*>(pLauncher->mpChildDBObj);
        info.weaponData = weaponData;

        if (weaponData != 0)
        {
            info.minLaunchAlt_m = weaponData->minLaunchAlt_m;
            info.maxLaunchAlt_m = weaponData->maxLaunchAlt_m;
            info.minRange_km = weaponData->minRange_km;
            info.maxRange_km = weaponData->maxRange_km;
            info.mfRange_km = info.maxRange_km;
            info.maxDepth_m = -info.minLaunchAlt_m;
            info.isNuclear = weaponData->IsNuclear();
        }
        

        if (tcMissileDBObject* missileDBObj = 
            dynamic_cast<tcMissileDBObject*>(weaponData))
		{
            info.isARM = missileDBObj->IsARM();
            info.speed_mps = missileDBObj->EstimateSpeed_mps();
            info.acceptsWaypoints = missileDBObj->AcceptsWaypoints();
		}
		else if (tcBallisticDBObject* ballisticDBObj = 
            dynamic_cast<tcBallisticDBObject*>(weaponData))
		{
            // not exact, higher target elevation could shorten range
            info.maxRange_km = ballisticDBObj->CalculateRangeKm(mpPlatformObj->mcKin.mfAlt_m, C_KTSTOMPS*mpPlatformObj->mcKin.mfSpeed_kts);
            switch (ballisticDBObj->ballisticType)
            {
            case tcBallisticDBObject::GRAVITY_BOMB:
                {
                    info.mnLaunchMode = 3;
                    return true;
                }
                break;
            case tcBallisticDBObject::GUN_ROUND:
                {
                    isGunRound = true; // not sure what happens in this case so leave alone for now
                }
                break;
            case tcBallisticDBObject::AUTO_CANNON:
			case tcBallisticDBObject::ROCKET:
                {
                    info.mnLaunchMode = 4;
                    return true;
                }
                break;
            case tcBallisticDBObject::SMART_BOMB:
                {
                    info.mnLaunchMode = 0;
                    return true;
                }
                break;
            case tcBallisticDBObject::CM_ROUND:
                {
                    info.mnLaunchMode = 10;
                     tcDatabase* database = tcDatabase::Get();
                    if (tcCounterMeasureDBObject* cmDBObj = 
                        dynamic_cast<tcCounterMeasureDBObject*>(database->GetObject(ballisticDBObj->payloadClass)))
                    {
                        info.lifeTime_s = cmDBObj->lifeSpan_s;
                    }
                    return true;
                }
                break;
            }
        }
		else if (tcTorpedoDBObject* torpDBObj = 
            dynamic_cast<tcTorpedoDBObject*>(weaponData))
        {
            info.maxDepth_m = torpDBObj->maxDepth_m;
        }
        else if (tcCounterMeasureDBObject* cmDBObj = 
            dynamic_cast<tcCounterMeasureDBObject*>(pLauncher->mpChildDBObj))
        {
            info.mnLaunchMode = 10;
            info.lifeTime_s = cmDBObj->lifeSpan_s;
            return true;
        }
        else if (tcSonobuoyDBObject* buoyData = 
            dynamic_cast<tcSonobuoyDBObject*>(pLauncher->mpChildDBObj))
        {
            info.mnLaunchMode = 11;
            return true;
        }
        else
		{
			//fprintf(stderr, "Error - unsupported launcher child class (%s)\n",
			//	pLauncher->mpChildDBObj->GetClassName());
			info.mnLauncher = -1;
			return false;
		}

		if (pLauncher->meLaunchMode == DATUM_ONLY) 
        {
            info.mnLaunchMode = 0;
        }
		else if (pLauncher->IsChildFireAndForget())
		{
			info.mnLaunchMode = 1; // platform guidance not required after launch
		}
		else
        {
            info.mnLaunchMode = 2; // requires platform sensor for initial guidance
        }
        

        return true;
    }

    int tcPlatformInterface::GetLauncherStatus(int launcher)
    {
        int status = tcLauncher::BAD_LAUNCHER;
        
        if ((mpPlatformObj != 0) && (launcher >= 0))
        {
            if (tcLauncher* pLauncher = mpPlatformObj->GetLauncher(launcher))
            {
                status = pLauncher->GetStatus();
            }
        }
        return status;
    }

    /**
    * Accurate calculation if target coordinate is range of weapon loaded in specified launcher
    */
    bool tcPlatformInterface::IsTargetInRange(int nLauncher, float lon_rad, float lat_rad, float alt_m, float targetHeading_rad, float targetSpeed_kts)
    {
        if ((mpPlatformObj == 0) || (nLauncher < 0)) return false;

        tcLauncher* launcher = mpPlatformObj->GetLauncher(nLauncher);
        if (launcher == 0)
		{
			wxASSERT(false);
			return false;
		}

        float rangeToTarget_km = GetRangeToDatum(lon_rad, lat_rad);

        tcWeaponDBObject* weaponData = dynamic_cast<tcWeaponDBObject*>(launcher->mpChildDBObj);
        
        if (tcMissileDBObject* missileDBObj = 
            dynamic_cast<tcMissileDBObject*>(weaponData))
        {
            tcSensorMapTrack targetTrack;
            targetTrack.mfLon_rad = lon_rad;
            targetTrack.mfLat_rad = lat_rad;
            targetTrack.mfAlt_m = alt_m;
            targetTrack.mfHeading_rad = targetHeading_rad;
            targetTrack.mfSpeed_kts = targetSpeed_kts;
            tcKinematics missileKin(mpPlatformObj->mcKin);

            targetTrack.mfAlt_m = std::max(targetTrack.mfAlt_m - 500.0f, 5.0f); // assume altitude lower to be more conservative in range estimate
            bool inRangeCalculated = tcMissileObject::EvaluateTarget(missileKin, targetTrack, missileDBObj);
            return inRangeCalculated;
        }
		else if (tcBallisticDBObject* ballisticDBObj = 
            dynamic_cast<tcBallisticDBObject*>(weaponData))
		{
            float maxRange_km = ballisticDBObj->CalculateRangeKm(mpPlatformObj->mcKin.mfAlt_m - alt_m, C_KTSTOMPS*mpPlatformObj->mcKin.mfSpeed_kts);
            
            return (rangeToTarget_km < maxRange_km);
        }
		else if (tcTorpedoDBObject* torpDBObj = 
            dynamic_cast<tcTorpedoDBObject*>(weaponData))
        {
            return (rangeToTarget_km < torpDBObj->maxRange_km);
        }
        else if (tcCounterMeasureDBObject* cmDBObj = 
            dynamic_cast<tcCounterMeasureDBObject*>(launcher->mpChildDBObj))
        {
            return true;
        }
        else if (tcSonobuoyDBObject* buoyData = 
            dynamic_cast<tcSonobuoyDBObject*>(launcher->mpChildDBObj))
        {
            return true;
        }
        else if (tcBallisticMissileDBObject* ballisticMissileData = 
            dynamic_cast<tcBallisticMissileDBObject*>(weaponData))
        {
            return (rangeToTarget_km < ballisticMissileData->maxRange_km);
        }
        else
		{
            wxASSERT(false);
			return false;
		}

    }

    float tcPlatformInterface::CalculateBombElevationDeg(float targetLon_rad, float targetLat_rad)
    {
        if (tcAirObject *air = dynamic_cast<tcAirObject*>(mpPlatformObj))
        {
            return C_180OVERPI * air->CalculateBombElevationRad(targetLon_rad, targetLat_rad);
        }
        else
        {
            return 180.0f;
        }
    }

	/**
	* @return missile range in km or 0 if error
	* @param launchSpeed_mps launch speed in m/s
	* @param missileType database class of missile
	* assumes target is not moving
	*/
	float tcPlatformInterface::EstimateMissileRangeKm(float launchSpeed_mps, float launchAlt_m, float targetAlt_m, const std::string& missileType)
	{
		tcMissileDBObject* missileData = dynamic_cast<tcMissileDBObject*>(tcDatabase::Get()->GetObject(missileType));
		if (missileData == 0)
		{
			fprintf(stderr, "tcPlatformInterface::EstimateMissileRangeKm - Missile (%s) not found\n", missileType.c_str());
			return 0;
		}
		float minEval_km = 10.0f;
		float maxEval_km = 1000.0f;
		float evalStep_km = 10.0f;
		float launchSpeed_kts = C_MPSTOKTS * launchSpeed_mps;
		float maxRange_km = tcMissileObject::EstimateRangeKm(minEval_km, maxEval_km, evalStep_km, launchSpeed_kts, launchAlt_m, targetAlt_m, missileData);

		// run a second time to improve accuracy
		if (maxRange_km >= 0)
		{
			minEval_km = maxRange_km;
			maxEval_km = minEval_km + evalStep_km;
			evalStep_km = 0.1f * evalStep_km;

			maxRange_km = tcMissileObject::EstimateRangeKm(minEval_km, maxEval_km, evalStep_km, launchSpeed_kts, launchAlt_m, targetAlt_m, missileData);
		}

		return maxRange_km;
	}

    int tcPlatformInterface::GetLauncherCount() 
    {
        if (mpPlatformObj == 0) 
        {
            return 0;
        }
        else 
        {
            return mpPlatformObj->mcLauncherState.mnCount;
        }
    }

    std::string tcPlatformInterface::GetLauncherWeaponName(int anLauncher) 
    {
        std::string s;

        if (mpPlatformObj == 0)
        {
            s = "Error";
            return s;
        }

        int nCount = GetLauncherCount();
        if ((anLauncher < 0)||(anLauncher >= nCount)) 
        {
            s = "Error";
            return s;
        }

        s = mpPlatformObj->mcLauncherState.GetLauncherChildClass(anLauncher);

        tcDatabase* database = tcDatabase::Get();
        if (tcDatabaseObject* data = database->GetObject(s))
        {
            return std::string(data->GetDisplayName());
        }
        else
        {
            //wxASSERT(false);
            return s;
        }
    }

    void tcPlatformInterface::SendDatumToLauncher(float afLon_rad, float afLat_rad, 
		float alt_m, int anLauncher) 
    {
        if (mpPlatformObj == 0) return;

        GeoPoint p;
		p.mfLon_rad = afLon_rad;
		p.mfLat_rad = afLat_rad;
		p.mfAlt_m = alt_m;
        mpPlatformObj->DesignateLauncherDatum(p, anLauncher);
    }

    bool tcPlatformInterface::SendTargetToLauncher(long targetId, int anLauncher) 
    {
        if ((mpPlatformObj == 0) || (anLauncher < 0)) return false;

        return mpPlatformObj->DesignateLauncherTarget(targetId, (unsigned int)anLauncher);
    }

    bool tcPlatformInterface::HandoffTargetToLauncher(int anLauncher) 
    {
        if (mpPlatformObj == 0) return false;

        UINT32 nTargetID = mpPlatformObj->GetBrain()->GetTarget();
        bool bAccept = mpSimState->DesignateLauncherTarget(mpPlatformObj->mnID, 
            nTargetID, anLauncher);
        return bAccept;
    }

    void tcPlatformInterface::Launch(int anLauncher, int quantity) 
    {
        if (mpPlatformObj == 0) return;

		if ((!mpPlatformObj->IsControlled()) || (quantity <= 0)) return;
        int launcherStatus = mpPlatformObj->SetLaunch(anLauncher, quantity);
        if (launcherStatus != tcLauncher::LAUNCHER_READY)
        {
            if (mpPlatformObj->IsOwnAlliance() && mpPlatformObj->IsHooked())
            {
                tcLauncher* launcher = mpPlatformObj->GetLauncher(anLauncher);
                if (launcher != 0)
                {
                    DisplayMessage(launcher->TranslateStatusDetailed(launcherStatus).ToStdString());
                }
            }
            
        }
    }

    int tcPlatformInterface::GetLauncherQuantity(int anLauncher) 
    {
        if (mpPlatformObj == 0) return 0;

        return mpPlatformObj->GetLauncherQuantity(anLauncher);
    }


    /**
    *
    */
    int tcPlatformInterface::GetLauncherTypesCount(int anLauncher)
    {
        if (mpPlatformObj == 0) return 0;

        if (tcLauncher* launcher = mpPlatformObj->GetLauncher(anLauncher))
        {
            return (int)launcher->GetCompatibleCount();
        }
        else
        {
            return 0;
        }
    }

    /**
    *
    */
    std::string tcPlatformInterface::GetLauncherTypeName(int anLauncher, int anType)
    {
        if (mpPlatformObj == 0) return std::string("Error");

        if (tcLauncher* launcher = mpPlatformObj->GetLauncher(anLauncher))
        {
            return launcher->GetCompatibleName(anType);
        }
        else
        {
            return std::string("Error");
        }
    }


    /**
    * @return tcFireControlInfo object with info on active fire control engagements
    * Used to keep semi-active child missile within radar coverage of platform
    */
    tcFireControlInfo tcPlatformInterface::GetFireControlInfo()
    {
        tcFireControlInfo info;
        info.radarGuidanceActive = false;
        info.maxLeft_deg = -360.0f;
        info.maxRight_deg = 360.0f;
		info.weaponsOut = 0;

        if (mpPlatformObj == 0) return info;
        
        // search all nearby missiles for any that are using this platform for fire
        // control AND still need the parent radar to illuminate the target
        tcGeoRect region;   
        const float dlat = 0.031f; // about +/- 200 km
        float dlon = dlat / cosf(mpPlatformObj->mcKin.mfLat_rad);

        region.Set(mpPlatformObj->mcKin.mfLon_rad - dlon, mpPlatformObj->mcKin.mfLon_rad + dlon,
            mpPlatformObj->mcKin.mfLat_rad - dlat, mpPlatformObj->mcKin.mfLat_rad + dlat);

        tcGameObjIterator iter(region);
        iter.SetAllianceFilter(mpPlatformObj->GetAlliance());

       
        for (iter.First(); iter.NotDone(); iter.Next())
        {
			if (tcWeaponObject* weapon = dynamic_cast<tcWeaponObject*>(iter.Get()))
			{
				info.weaponsOut += int(weapon->WasLaunchedBy(mpPlatformObj->mnID));
			}

            if (tcMissileObject* missile = dynamic_cast<tcMissileObject*>(iter.Get()))
            {
                long fireControlPlatform;
                if (missile->StillNeedsIlluminator(fireControlPlatform))
                {
                    if (fireControlPlatform == mpPlatformObj->mnID)
                    {
     
                        info.radarGuidanceActive = true;
                        wxASSERT(missile->GetSeekerSensor() != 0);
                        if (tcRadar* fireControlRadar = missile->GetSeekerSensor()->GetFireControlRadar())
                        {
                            float half_fov_rad = 0.5*C_PIOVER180*fireControlRadar->mpDBObj->mfFieldOfView_deg;
                            float look_az_rad = mpPlatformObj->mcKin.mfHeading_rad + fireControlRadar->mountAz_rad;
                            
                            float bearing_rad = mpPlatformObj->mcKin.HeadingToRad(missile->mcKin) - look_az_rad;
                            bearing_rad += C_TWOPI*(bearing_rad < -C_PI);
                            bearing_rad -= C_TWOPI*(bearing_rad > C_PI);

                            float left_rad = bearing_rad - half_fov_rad;
                            float right_rad = bearing_rad + half_fov_rad;

                            info.maxLeft_deg = std::max(info.maxLeft_deg, C_180OVERPI*left_rad);
                            info.maxRight_deg = std::min(info.maxRight_deg, C_180OVERPI*right_rad);
                        }
                    }
                }
            }
        }

        return info;
    }

    /**
    * Set preplan waypoints for future missile launches
    * Expects string "<lon1_rad>,<lat1_rad>,<lon2_rad>,<lat2_rad>,..."
    */
    void tcPlatformInterface::SetMissilePreplan(const std::string& preplan)
    {
        if (mpPlatformObj == 0) return;

        std::vector<GeoPoint> waypoints;

        wxString preplanString(preplan.c_str());

        wxString slon = preplanString.BeforeFirst(',');
        preplanString = preplanString.AfterFirst(',');
        wxString slat = preplanString.BeforeFirst(',');
        preplanString = preplanString.AfterFirst(',');

        while (slat.size() > 0)
        {
            double lon_rad = 0;
            double lat_rad = 0;
            slon.ToDouble(&lon_rad);
            slat.ToDouble(&lat_rad);

            GeoPoint p;
            p.Set(lon_rad, lat_rad, 0);
            waypoints.push_back(p);

            slon = preplanString.BeforeFirst(',');
            preplanString = preplanString.AfterFirst(',');
            slat = preplanString.BeforeFirst(',');
            preplanString = preplanString.AfterFirst(',');
        }
        
        mpPlatformObj->missilePreplan = waypoints;
    }

    /**
    * true if any of the magazines on the platform can accept the item
    */
    bool tcPlatformInterface::CanMagazineAcceptItem(std::string item)
    {
        if (mpPlatformObj == 0) return false;

        unsigned int nMagazines = mpPlatformObj->GetMagazineCount();
        for (unsigned int n=0; n<nMagazines; n++)
        {
            tcStores* mag = mpPlatformObj->GetMagazine(n);
            if (!mag->IsFull() && mag->IsCompatible(item)) return true;
        }
        return false;
    }

    void tcPlatformInterface::AddItemToMagazine(const std::string& item, unsigned int quantity)
    {
        if (mpPlatformObj == 0) return;
        if (!(mpPlatformObj->IsEditMode() || isDeveloperMode)) return;

        // check if quantity has been specified as part of item, e.g. 'AIM-9M [40]' if so 
        // then override quantity argument
        wxString bracketQuantity(item.c_str());
        wxString item2 = bracketQuantity.BeforeFirst('[');
        item2.Trim();
        std::string parsedItem(item2.c_str());
        bracketQuantity = bracketQuantity.AfterFirst('[');
        bracketQuantity = bracketQuantity.BeforeFirst(']');
        unsigned long otherQuantity = 0;
        if (bracketQuantity.ToULong(&otherQuantity, 10))
        {
            quantity = otherQuantity;
        }


        unsigned int nMagazines = mpPlatformObj->GetMagazineCount();
        for (unsigned int n=0; n<nMagazines; n++)
        {
            tcStores* mag = mpPlatformObj->GetMagazine(n);
            if (!mag->IsFull() && mag->IsCompatible(parsedItem))
            {
                mag->AddItems(parsedItem, quantity);
                return;
            }
        }
    }

    /**
    *
    */
    int tcPlatformInterface::GetMagazineQuantity(std::string item)
    {
        if (mpPlatformObj == 0) return 0;
        return (int)mpPlatformObj->GetMagazineQuantity(item);
    }

    int tcPlatformInterface::GetMagazineIdQuantity(std::string item, int magazine_id)
    {
        if (mpPlatformObj == 0) return 0;
        tcStores* mag = mpPlatformObj->GetMagazine(magazine_id);
        std::string matchingItem;
        size_t nAvailable = mag->CurrentItemQuantity(item, matchingItem);
        return nAvailable;
    }

    bool tcPlatformInterface::HasMagazine() const
    {
        if (mpPlatformObj == 0) return false;

        return (mpPlatformObj->GetMagazineCount() > 0);
    }

    // return list of all items in magazines (redundant entries removed)
    tcStringArray tcPlatformInterface::GetMagazineItems()
    {
        tcStringArray result;
        if (mpPlatformObj == 0) return result;

        wxArrayString itemList;
        unsigned int nMagazines = mpPlatformObj->GetMagazineCount();
        for (unsigned int n=0; n<nMagazines; n++)
        {
            tcStores* mag = mpPlatformObj->GetMagazine(n);
            wxASSERT(mag != 0);
            size_t nItems = mag->GetNumberItemTypes();
            for (size_t k=0; k<nItems; k++)
            {
                itemList.push_back(mag->GetItemName(k).c_str());
            }
        }

        if (itemList.size() == 0) return result;

        itemList.Sort();

        wxArrayString uniqueItems;

        uniqueItems.push_back(itemList[0]);
        for (size_t n=1; n<itemList.size(); n++)
        {
            if (itemList[n] != uniqueItems.back())
            {
                uniqueItems.push_back(itemList[n]);
            }
        }

        for (size_t n=0; n<uniqueItems.size(); n++)
        {
            result.PushBack(uniqueItems[n].ToStdString());
        }

        return result;
    }

    /**
    * @return list of equipment that is compatible with launchers of this platform
    * @param launcher_idx use -1 for all launchers, or 0-nLaunchers-1 for specific launcher
    * Useful for automatically filling airbase magazine
    */
    tcStringArray tcPlatformInterface::GetCompatibleItemList(int launcher_idx) const
    {
        // wxArrayString arrayString = WildcardSearch("AIM*", "loadout");
        tcStringArray result;

        if (mpPlatformObj == 0) return result;

        size_t nLaunchers = mpPlatformObj->GetLauncherCount();

        if (launcher_idx < 0)
        {
            for (size_t n=0; n<nLaunchers; n++)
            {
                tcLauncher* launcher = mpPlatformObj->GetLauncher(n);
                
                wxArrayString arrayString = launcher->GetAllCompatibleList();
                size_t nCompatible = arrayString.size();
                for (size_t k=0; k<nCompatible; k++)
                {
                    wxString s(arrayString[k]);
                    wxASSERT((s.Find('*') == wxNOT_FOUND) && (s.Find('?') == wxNOT_FOUND));
                    
                    result.AddString(s.ToStdString());
                }
            }
        }
        else if ((size_t)launcher_idx < nLaunchers)
        {
            tcLauncher* launcher = mpPlatformObj->GetLauncher(launcher_idx);
            wxASSERT(launcher != 0);

            wxArrayString arrayString = launcher->GetAllCompatibleList();
            size_t nCompatible = arrayString.size();
            for (size_t k=0; k<nCompatible; k++)
            {
                wxString s(arrayString[k]);
                wxASSERT((s.Find('*') == wxNOT_FOUND) && (s.Find('?') == wxNOT_FOUND));

                result.AddString(s.ToStdString());
            }
        }

        result.RemoveDuplicates();

		return result;   // amram- I'm pre-empting the filter here, I would much prefer the ability to have an unfiltered list I can filter later
						 //		   than one that unconditionally filters.  Ultimately, the ideal would be for the filtering to be optional.

        // filter by current scenario date
        tcDatabase* database = tcDatabase::Get();
        wxArrayString itemList;
        for (size_t n=0; n<result.Size(); n++)
        {
            itemList.push_back(result.GetString(n).c_str());
        }

        std::vector<tcDatabase::RecordSummary> itemRecords = database->GetItemSummary(itemList);
        result.Clear();
        float scenarioYear = mpSimState->GetDateTime().GetFractionalYear(); // fractional year of scenario
        for (size_t n=0; n<itemRecords.size(); n++)
        {
            bool yearPasses = ((itemRecords[n].yearStart <= scenarioYear) && (itemRecords[n].yearStop >= scenarioYear));
            if (yearPasses)
            {
                result.PushBack(itemRecords[n].databaseClass);
            }
        }

        return result;
    }


    /**
    *
    */
    void tcPlatformInterface::LoadLauncher(int anLauncher, const std::string& item)
    {
        if (mpPlatformObj == 0) return;

		if (!mpPlatformObj->IsControlled()) return;
        // verify launcher is empty and item is compatible with launcher  
        tcLauncher* launcher = mpPlatformObj->GetLauncher(anLauncher);
        if (!launcher) return;
        if (!launcher->IsItemCompatible(item)) return;

        if (tcGameObject::IsEditMode())
        {
            unsigned int launcherCapacity = launcher->GetCapacityForItem(item);
            launcher->SetChildClass(item);
            launcher->SetChildQuantity(launcherCapacity);
            return;
        }

        if (launcher->mnCurrent)
        {
            launcher->CancelLoadInProgress();
            return;
        }

        std::string exactItem;
        unsigned int nMagazines = mpPlatformObj->GetMagazineCount();
        for (unsigned int n=0; n<nMagazines; n++)
        {
            tcStores* mag = mpPlatformObj->GetMagazine(n);
            if (mag->CurrentItemQuantity(item, exactItem))
            {
                mag->LoadLauncher(anLauncher, exactItem);
                return;
            }
        }

        // error not found
    }

    void tcPlatformInterface::LoadLauncherTest(int anLauncher, const std::string& item, int quantity)
    {
        if (!isDeveloperMode) return;

        tcLauncher* launcher = mpPlatformObj->GetLauncher(anLauncher);
        if (!launcher) return;

        launcher->SetChildClass("", true);
        launcher->SetChildClass(item, true);
        launcher->SetChildQuantity(quantity);
    }


	void tcPlatformInterface::LoadOther(const std::string& item, unsigned long quantity)
	{
        if (mpPlatformObj == 0) return;

		if (!mpPlatformObj->IsControlled()) return;

        std::string exactItem;
		size_t nMagazines = mpPlatformObj->GetMagazineCount();
		for (size_t n=0; n<nMagazines; n++)
		{
			tcStores* mag = mpPlatformObj->GetMagazine(n);
			if (mag->CurrentItemQuantity(item, exactItem))
			{
				mag->LoadOther(exactItem, quantity, mpPlatformObj);
				return;
			}
		}

		if (tcPlatformObject* parent = dynamic_cast<tcPlatformObject*>(mpPlatformObj->parent))
		{
			size_t nMagazines = parent->GetMagazineCount();
			for (size_t n=0; n<nMagazines; n++)
			{
				tcStores* mag = parent->GetMagazine(n);
				if (mag->CurrentItemQuantity(item, exactItem))
				{
					mag->LoadOther(exactItem, quantity, mpPlatformObj);
					return;
				}
			}
		}
	}

    bool tcPlatformInterface::MaintenanceHold() const
    {
        if (tcAirObject* air = dynamic_cast<tcAirObject*>(mpPlatformObj))
        {
            return air->MaintenanceHold();
        }
        else
        {
            return false;
        }
    }

    tcStringArray tcPlatformInterface::GetEquipmentListByClass(const std::string& classString)
    {
        tcStringArray stringArray;

		//#define PTYPE_UNKNOWN 0x0000
		//#define PTYPE_SURFACE 0x0010
		//#define PTYPE_SMALLSURFACE 0x0011
		//#define PTYPE_LARGESURFACE 0x0012
		//#define PTYPE_AIR 0x0020
		//#define PTYPE_FIXEDWING 0x0021
		//#define PTYPE_HELO 0x0022
		//#define PTYPE_MISSILE 0x0040
		//#define PTYPE_SUBSURFACE 0x0080
		//#define PTYPE_SUBMARINE 0x0081
		//#define PTYPE_TORPEDO 0x0082
		//#define PTYPE_SONOBUOY 0x0084
		//#define PTYPE_GROUND 0x0100
		//#define PTYPE_BALLISTIC 0x0200

        std::vector<unsigned int> classMask;

		if (classString == "Missile") 
		{
            classMask.push_back(PTYPE_MISSILE);
		}
		else if (classString == "Torpedo")
		{
			classMask.push_back(PTYPE_TORPEDO);
		}
        else if (classString == "Mine")
        {
            classMask.push_back(PTYPE_WATERMINE);
        }
		else if (classString == "Ballistic")
		{
			classMask.push_back(PTYPE_BALLISTIC);
		}
        else if (classString == "CM")
        {
            classMask.push_back(PTYPE_AIRCM);
            classMask.push_back(PTYPE_WATERCM);
        }
		else
		{
			fprintf(stderr, "tcScenarioInterface::GetPlatformListByClass - "
				"unrecognized classString (%s)\n", classString.c_str());
			return stringArray;
		}

        for (size_t k=0; k<classMask.size(); k++)
        {
            tcDatabaseIterator iter(classMask[k]);

            for (iter.First(); !iter.IsDone(); iter.Next())
            {
                tcDatabaseObject* obj = iter.Get();
                wxASSERT(obj);
                wxASSERT(obj->mnKey != -1);

                stringArray.AddString(obj->mzClass.c_str());
            }
        }

		return stringArray;
    }


    /**
    * @return list of database air loadouts
    */
    tcStringArray tcPlatformInterface::GetLoadoutList()
    {
        tcStringArray stringArray;

        if (tcAirObject* air = dynamic_cast<tcAirObject*>(mpPlatformObj))
        {
			tcDateTime dateTime = mpSimState->GetDateTime();

			double searchYear = dateTime.GetFractionalYear();
			if (!enableDateFiltering)
			{
				searchYear = 0; // set year to 0 to have FindPlatformSetups ignore date filtering
			}

            const std::vector<tcLoadoutData>& loadoutList = air->mpDBObject->GetLoadoutList(searchYear);
            for (size_t n=0; n<loadoutList.size(); n++)
            {
                stringArray.AddString(loadoutList[n].setupName);
            }
        }

        return stringArray;
    }

	int tcPlatformInterface::GetItemCapacityForLauncher(int launcherIdx, const std::string& item)
    {
        if (mpPlatformObj == 0) return 0;

		if (!mpPlatformObj->IsControlled()) return 0;
        tcLauncher* launcher = mpPlatformObj->GetLauncher(launcherIdx);
        if (!launcher) return 0;
        if (!launcher->IsItemCompatible(item)) return 0;
		unsigned int launcherCapacity = launcher->GetCapacityForItem(item);
        return launcherCapacity;
        }



    void tcPlatformInterface::EquipLoadout(const std::string& loadout)
    {
        if (!tcGameObject::IsEditMode()) return;

        if (tcAirObject* air = dynamic_cast<tcAirObject*>(mpPlatformObj))
        {
            tcStores::LoadPlatformEditMode(air, loadout);
        }
    }

    tcStringArray tcPlatformInterface::GetPlatformSetups()
    {
        tcStringArray stringArray;

        if (!tcGameObject::IsEditMode() || (mpPlatformObj == 0)) return stringArray;

        std::string databaseClass = mpPlatformObj->mzClass.c_str();

        tcDateTime current = mpSimState->GetDateTime();
        float currentYear = float(current.GetYear()) + (1.0f/12.0f)*(float(current.GetMonth()) - 0.5f);

		if (!enableDateFiltering)
		{
			currentYear = 0; // set year to 0 to have FindPlatformSetups ignore date filtering
		}

        std::vector<std::string> platformSetups;
        tcDatabase* database = tcDatabase::Get();
        bool valid = database->FindPlatformSetups(databaseClass, currentYear, platformSetups);

        for (size_t n=0; n<platformSetups.size(); n++)
        {
            stringArray.AddString(platformSetups[n]);
        }

        return stringArray;
    }


    void tcPlatformInterface::AutoConfigurePlatform(const std::string& setupName)
    {
        if (!tcGameObject::IsEditMode() || (mpPlatformObj == 0)) return;

        mpPlatformObj->AutoConfigurePlatform(setupName);
    }


	bool tcPlatformInterface::IsRefueling() const
	{
        if (mpPlatformObj == 0) return false;

		return mpPlatformObj->IsRefueling();
	}

    /**
    * Added to check if at weight limit before refueling
    */
    float tcPlatformInterface::GetWeightMargin()
    {
        if (tcAirObject* air = dynamic_cast<tcAirObject*>(mpPlatformObj))
        {
            return air->mpDBObject->maxTakeoffWeight_kg - air->GetTotalWeight();
        }
        else
        {
            return 1e9f;
        }
    }

    /**
    *
    */
    void tcPlatformInterface::UnloadLauncher(int anLauncher)
    {
        if (mpPlatformObj == 0) return;

		if (!mpPlatformObj->IsControlled()) return;
        tcLauncher* launcher = mpPlatformObj->GetLauncher(anLauncher);
        if (!launcher) return;
        if (!launcher->mpChildDBObj) return;

        std::string item = launcher->mpChildDBObj->mzClass.c_str();

        if (tcGameObject::IsEditMode())
        {
            launcher->SetChildQuantity(0);
            return;
        }

        if (launcher->mnCurrent == 0)
        {
            launcher->CancelLoadInProgress();
            return;
        }

        unsigned int nMagazines = mpPlatformObj->GetMagazineCount();
        for (unsigned int n=0; n<nMagazines; n++)
        {
            tcStores* mag = mpPlatformObj->GetMagazine(n);
            if (!mag->IsFull() && mag->IsCompatible(item))
            {
                mag->UnloadLauncher(anLauncher);
                return;
            }
        }

        // error not found
    }

    void tcPlatformInterface::AddTask(const std::string& taskName, double priority, int attributes) 
    {
        if (mpPlatformObj == 0) return;

        ai::Brain* brain = mpPlatformObj->GetBrain();
        wxASSERT(brain);
        
        brain->AddTask(taskName, priority, attributes);
    }

    void tcPlatformInterface::AddNavWaypoint(float afLon_rad, float afLat_rad) 
    {
        if (mpPlatformObj == 0) return;

		if (mpPlatformObj->IsClientMode()) return;

        ai::Brain* brain = mpPlatformObj->GetBrain();
        wxASSERT(brain);

        ai::Nav* nav = brain->GetNavTask();
        if (!nav)
        {
            brain->AddTask("Nav", 1.0f);
            nav = brain->GetNavTask();
        }
        wxASSERT(nav);

        nav->AddWaypoint(afLon_rad, afLat_rad, 0, 0);
    }


    void tcPlatformInterface::AddNavWaypointAdvanced(float afLon_rad, float afLat_rad, float alt_m, float speed_kts) 
    {
        if (mpPlatformObj == 0) return;

		if (mpPlatformObj->IsClientMode()) return;

        ai::Brain* brain = mpPlatformObj->GetBrain();
        wxASSERT(brain);

        ai::Nav* nav = brain->GetNavTask();
        if (!nav)
        {
            brain->AddTask("Nav", 1.0f);
            nav = brain->GetNavTask();
        }
        wxASSERT(nav);

        nav->AddWaypoint(afLon_rad, afLat_rad, alt_m, speed_kts);
    }

    /**
    * @return nav task if it exists and we're not in client mode, otherwise return 0
    */
    ai::Nav* tcPlatformInterface::GetNav()
    {
        if (mpPlatformObj == 0) return 0;

		if (mpPlatformObj->IsClientMode()) return 0;

        ai::Brain* brain = mpPlatformObj->GetBrain();
        wxASSERT(brain);

        ai::Nav* nav = brain->GetNavTask();
        return nav;
    }

    const ai::Nav* tcPlatformInterface::GetNav() const
    {
        if (mpPlatformObj == 0) return 0;

		if (mpPlatformObj->IsClientMode()) return 0;

        ai::Brain* brain = mpPlatformObj->GetBrain();
        wxASSERT(brain);

        ai::Nav* nav = brain->GetNavTask();
        return nav;
    }


    void tcPlatformInterface::SetNavWaypointTasks(size_t idx, const std::string& taskList)
    {
        if (ai::Nav* nav = GetNav())
        {
            nav->SetWaypointTasklist(idx, taskList);
        }
    }

    void tcPlatformInterface::AddWaypointTask(size_t idx, const std::string& task)
    {
        if (ai::Nav* nav = GetNav())
        {
            nav->AddWaypointTask(idx, task);
        }
    }

    void tcPlatformInterface::RemoveWaypointTask(size_t idx, const std::string& task)
    {
        if (ai::Nav* nav = GetNav())
        {
            nav->RemoveWaypointTask(idx, task);
        }
    }


    void tcPlatformInterface::DeleteNavWaypoint(size_t idx)
    {
        if (ai::Nav* nav = GetNav())
        {
            nav->DeleteWaypoint(idx);
        }
    }

	void tcPlatformInterface::EditNavWaypoint(size_t idx, float afLon_rad, float afLat_rad) 
    {
        if (ai::Nav* nav = GetNav())
        {
		    nav->EditWaypoint(idx, afLon_rad, afLat_rad, 0, 0);
        }
    }

    void tcPlatformInterface::EditNavWaypointAdvanced(size_t idx, float afLon_rad, float afLat_rad, float alt_m, float speed_kts)
    {
        if (ai::Nav* nav = GetNav())
        {
		    nav->EditWaypoint(idx, afLon_rad, afLat_rad, alt_m, speed_kts);
        }
    }

    void tcPlatformInterface::EditNavWaypointReference(size_t idx, unsigned char referenceMode, long referencePlatform)
    {
        if (ai::Nav* nav = GetNav())
        {
            if (referenceMode != 0)
            {
                tcGameObject* ref = mpSimState->GetObject(referencePlatform);
                if ((mpPlatformObj == 0) || (ref == 0) || (mpPlatformObj->GetAlliance() != ref->GetAlliance()))
                {
                    return; // invalid waypoint referencing
                }
            }

		    nav->EditWaypointReference(idx, referenceMode, referencePlatform);
        }
    }

    void tcPlatformInterface::InsertNavWaypoint(size_t idx, float lon_rad, float lat_rad)
    {
        if (ai::Nav* nav = GetNav())
        {
            nav->InsertWaypoint(idx, lon_rad, lat_rad, 0, 0);
        }
    }

	unsigned int tcPlatformInterface::GetCurrentWaypoint() const
	{
        if (const ai::Nav* nav = GetNav())
        {
		    return nav->GetCurrentWaypoint();
        }
        else
        {
            return 0;
        }
	}

    void tcPlatformInterface::SetCurrentWaypoint(unsigned int idx)
    {
        if (ai::Nav* nav = GetNav())
        {
		    nav->SetCurrentWaypoint(idx);
        }
    }

	void tcPlatformInterface::SetNavLoopState(bool state)
	{
        if (ai::Nav* nav = GetNav())
        {
		    nav->SetLoopState(state);
        }
	}

    bool tcPlatformInterface::GetNavLoopState() const
    {
        if (const ai::Nav* nav = GetNav())
        {
		    return nav->GetLoopState();
        }
        else
        {
            return false;
        }
    }

    /**
    * Added this here for faster calculation vs. trying to do within python
    */
    tcDatum tcPlatformInterface::GetRandomPatrolPoint() const
    {
        tcDatum result;
        result.lon = 0;
        result.lat = 0;
        result.alt = 0;

        if (mpPlatformObj == 0) return result;

        std::vector<GeoPoint> patrolArea;
        if (mpPlatformObj->GetBrain()->GetPatrolArea(patrolArea))
        {        
            GeoPoint p = tcAreaGoal::GetRandomPointWithinArea(patrolArea);
            result.lon = p.mfLon_rad;
            result.lat = p.mfLat_rad;
        }

        return result;
    }

    /**
    * Remove all tasks from ai brain
    */
    void tcPlatformInterface::ClearTasks() 
    {
        if (mpPlatformObj == 0) return;

		if (mpPlatformObj->IsClientMode()) return;

        ai::Brain* brain = mpPlatformObj->GetBrain();
        wxASSERT(brain);

        brain->RemoveAllTasks();

        mpPlatformObj->SetMaxTurnRate(360.0f); // disable reduced turn rate
        SetPitchLimitDeg(85.0f);
    }

    void tcPlatformInterface::DeleteTask(const std::string& taskName)
    {
        if (mpPlatformObj == 0) return;

		//if (mpPlatformObj->IsClientMode()) return; // changed to send remove requests to server

        ai::Brain* brain = mpPlatformObj->GetBrain();
        wxASSERT(brain);
                
        brain->RemoveTask(taskName);
    }

    void tcPlatformInterface::SetTaskRun(const std::string& taskName, bool state)
    {
        if (mpPlatformObj == 0) return;

		if (mpPlatformObj->IsClientMode()) return;

        ai::Brain* brain = mpPlatformObj->GetBrain();
        wxASSERT(brain);
                
        if (ai::Task* task = brain->GetTask(taskName))
        {
            task->SetRunState(state);
        }
    }

    /**
    * Used to pass parameters to tasks by posting for all tasks to see
    */
    ai::BlackboardInterface tcPlatformInterface::GetBlackboardInterface()
    {
        static ai::Blackboard errorBoard;
        static ai::BlackboardInterface errorInterface(&errorBoard, -1, 0);

        if (mpPlatformObj == 0) return errorInterface;

        ai::Brain* brain = mpPlatformObj->GetBrain();
        wxASSERT(brain);
                
        return brain->GetBlackboardInterface();   
    }

	bool tcPlatformInterface::TaskExists(const std::string& taskName)
	{
        if (mpPlatformObj == 0) return false;

        ai::Brain* brain = mpPlatformObj->GetBrain();
        wxASSERT(brain);
                
        return brain->TaskExists(taskName); 
    }
    
    tcStringArray tcPlatformInterface::GetTaskList()
    {
        tcStringArray result;

        if (mpPlatformObj == 0) return result;

        ai::Brain* brain = mpPlatformObj->GetBrain();
        wxASSERT(brain);

        std::vector<std::string> taskList = brain->GetTaskList();
        result.SetStringArray(taskList);
        
        return result;
    }


    void tcPlatformInterface::GetSensorMap() 
    {
        if (mpPlatformObj)
        {
            unsigned int nAlliance = mpPlatformObj->GetAlliance();
            mpSensorMap = mpSimState->mcSensorMap.GetOrCreateMap(nAlliance);
            wxASSERT(mpSensorMap);
        }
        else
        {
            mpSensorMap = 0;
        }
    }

    // sensor map commands
    tcTrackIterator tcPlatformInterface::GetFirstTrack() 
    {
        tcTrackIterator t;
        t.mnID = -1;

        if (mpSensorMap == 0) {return t;}
        if (mpSensorMap->GetTrackCount()==0) 
        {
            t.mnID = NULL_INDEX;
            return t;
        }
        long nPos = mpSensorMap->GetStartTrackPosition();
        return GetNextTrack(nPos);
    }

    int tcPlatformInterface::GetTrackCount() 
    {
        if (mpSensorMap == 0) {return 0;}
        return mpSensorMap->GetTrackCount();
    }

    tcTrackIterator tcPlatformInterface::GetNextTrack(long nPos) 
    {
        tcSensorMapTrack *pSMTrack;
        tcTrackIterator t;

        long nKey = nPos;

        mpSensorMap->GetNextTrack(nKey, pSMTrack);
        t.mnKey = nKey;
        tcSensorMapTrack *pt = (tcSensorMapTrack*)&t;
        *pt = *pSMTrack;
        return t;
    }

    /**
    * @param maxEngagements use 0 to ignore engagement count
    */
    tcSensorMapTrack tcPlatformInterface::GetClosestAirTrack(float afMaxRange_km, UINT8 anAffiliation, int maxEngagements) 
    {
        return GetClosestTrack(afMaxRange_km, PTYPE_AIR, anAffiliation, maxEngagements);
    }

    /**
    * @param maxEngagements use 0 to ignore engagement count
    */
    tcSensorMapTrack tcPlatformInterface::GetClosestSurfaceTrack(float afMaxRange_km, UINT8 anAffiliation, int maxEngagements) 
    {
        return GetClosestTrack(afMaxRange_km, PTYPE_SURFACE, anAffiliation, maxEngagements);
    }

    /**
    * @param maxEngagements use 0 to ignore engagement count
    */
    tcSensorMapTrack tcPlatformInterface::GetClosestMissileTrack(float afMaxRange_km, UINT8 anAffiliation, int maxEngagements) 
    {
        return GetClosestTrack(afMaxRange_km, PTYPE_MISSILE, anAffiliation, maxEngagements);
    }

    // includes unknowns as matches to all affiliations
    /**
    * @param maxEngagements use 0 to ignore engagement count
    * @param anAffiliation, 0 - unknown, 1 - friendly, 2 - neutral, 3 - hostile, 4 - all, always includes unknown, 100 - legal targets for ROE
    */
    tcSensorMapTrack tcPlatformInterface::GetClosestTrack(float afMaxRange_km, 
        UINT16 anClassMask, UINT8 anAffiliation, int maxEngagements) 
    {
        tcSensorMapTrack track;
        tcSensorMapTrack *pTrack;

        if (mpSensorMap == 0) {return track;}

		tcTrackList trackList = GetTrackList(anClassMask, afMaxRange_km, anAffiliation);
		wxASSERT(trackList.track.size() == trackList.range_km.size());

        int nCount = trackList.Size();

        long nPos = mpSensorMap->GetStartTrackPosition();
        float fMinRange_km = 1e15f;
        for(int n=0; n<nCount; n++) 
        {
			pTrack = trackList.GetTrackPointer(n);

            bool engagementsMatch = (maxEngagements == 0) || 
                ((int)pTrack->GetEngagedCount() <= maxEngagements);

			if (engagementsMatch && (trackList.range_km[n] < fMinRange_km))
			{
				track = *pTrack;
                fMinRange_km = trackList.range_km[n];
			}
        }

        return track;
    }

	

    tcTrackList tcPlatformInterface::GetTrackList(int anClassMask, 
        float afMaxRange_km, UINT8 anAffiliation)
    {
		if (anAffiliation == VALID_ROE)
		{
			return GetTrackListValidROE(anClassMask, afMaxRange_km);
		}

		if (anAffiliation == tcAllianceInfo::FRIENDLY)
		{
			return GetFriendlyTrackList(anClassMask, afMaxRange_km);
		}

        double t = mpSimState->GetTime();

        tcTrackList trackList;

        tcSensorMapTrack *pTrack;

        wxASSERT(mpSensorMap);
        wxASSERT(anAffiliation != tcAllianceInfo::FRIENDLY);

        int nCount = mpSensorMap->GetTrackCount();
        if (nCount==0) 
        {
            return trackList;
        }

        long nPos = mpSensorMap->GetStartTrackPosition();
        for(int n=0;n<nCount;n++) 
        {
            mpSensorMap->GetNextTrack(nPos, pTrack);

            bool affilMatch = (pTrack->mnAffiliation == anAffiliation) || 
                (anAffiliation == ALL_AFFILIATIONS);

            bool classificationMatch = pTrack->MatchesMask(anClassMask);

			bool bearingOnlyValid = !pTrack->IsBearingOnly() || (pTrack->errorPoly.size() > 0);

            bool valid = affilMatch && classificationMatch && bearingOnlyValid && 
                !pTrack->IsDestroyed() && !pTrack->IsStale();

            if (valid)
            {
                tcSensorMapTrack predictedTrack(*pTrack);
                pTrack->GetPrediction(predictedTrack, t);

                GeoPoint p;
                p.mfAlt_m = 0;
                p.mfLat_rad = predictedTrack.mfLat_rad;
                p.mfLon_rad = predictedTrack.mfLon_rad;
                float fRange_km = mpPlatformObj->mcKin.RangeToKm(&p);
                if (fRange_km <= afMaxRange_km)
                {
                    trackList.track.push_back(predictedTrack);
					trackList.range_km.push_back(fRange_km);
                }
            }
        }
        return trackList;
    }

	/**
	* @return tcTrackList with only tracks that are engageable IAW current ROE
	*/
    tcTrackList tcPlatformInterface::GetTrackListValidROE(int anClassMask, 
        float afMaxRange_km)
    {
        tcTrackList trackList;

        double t = mpSimState->GetTime();

        tcSensorMapTrack *pTrack;
		tcGoalTracker* goalTracker = tcGoalTracker::Get();

        wxASSERT(mpSensorMap != 0);

        int nCount = mpSensorMap->GetTrackCount();
        if (nCount==0) 
        {
            return trackList;
        }

        long nPos = mpSensorMap->GetStartTrackPosition();
        for(int n=0;n<nCount;n++) 
        {
            mpSensorMap->GetNextTrack(nPos, pTrack);

			bool classificationMatch = pTrack->MatchesMask(anClassMask);

			bool bearingOnlyValid = !pTrack->IsBearingOnly() || (pTrack->errorPoly.size() > 0);

            bool valid = classificationMatch && bearingOnlyValid && 
                !pTrack->IsDestroyed() && !pTrack->IsStale();

			if (valid && (goalTracker->IsTargetLegal(mpPlatformObj, pTrack)))
            {
                GeoPoint p;
                p.mfAlt_m = 0;
                p.mfLat_rad = pTrack->mfLat_rad;
                p.mfLon_rad = pTrack->mfLon_rad;
                float fRange_km = mpPlatformObj->mcKin.RangeToKm(&p);
                if (fRange_km <= afMaxRange_km)
                {
                    tcSensorMapTrack predictedTrack(*pTrack);
                    pTrack->GetPrediction(predictedTrack, t);
                    trackList.track.push_back(predictedTrack);
                }
            }
        }

        return trackList;
    }


    /**
    * Get list of friendly tracks meeting criteria.
    * @param mode: "" -- default behavior, acts like GetTrackList used to except works with friendlies
    *              "airbases" -- return friendly airbases and carriers (if compatible) within maxRange_km
    *              "tankers" -- return friendly tankers that are airborne
    */
    tcTrackList tcPlatformInterface::GetFriendlyTrackList(unsigned int classMask, float maxRange_km, const std::string& mode)
    {
        tcTrackList trackList;
        if (mpPlatformObj == 0)
        {
            wxASSERT(false);
            return trackList;
        }
 

        tcGeoRect region;   
        float dlat = C_KMTORAD * maxRange_km;
        float dlon = dlat / cosf(mpPlatformObj->mcKin.mfLat_rad);
        region.Set(mpPlatformObj->mcKin.mfLon_rad - dlon, mpPlatformObj->mcKin.mfLon_rad + dlon,
            mpPlatformObj->mcKin.mfLat_rad - dlat, mpPlatformObj->mcKin.mfLat_rad + dlat);

        tcGameObjIterator iter(region);

        bool findAirbases = (mode == "airbases");
        bool findAll = (mode == "");
        bool findTankers = (mode == "tankers");

        if (!(findAirbases || findAll || findTankers))
        {
            wxASSERT(false);
            fprintf(stderr, "GetFriendlyTrackList -- bad mode parameter (%s)\n", mode.c_str());
            return trackList;
        }

        tcAirObject* air = dynamic_cast<tcAirObject*>(mpPlatformObj);
        tcAirObject* helo = dynamic_cast<tcHeloObject*>(air);

        bool thisPlatformIsHelo = (helo != 0);
        bool carrierCompatible = (air != 0) && (air->mpDBObject->IsCarrierCompatible());




        if (findAll) // find friendlies matching classMask within maxRange_km
        {
            for (iter.First();iter.NotDone();iter.Next())
            {
                tcGameObject* obj = iter.Get();

                if ((obj->GetAlliance() == mpPlatformObj->GetAlliance()) && (obj != mpPlatformObj))
                {
                    float range_km = obj->RangeTo(*mpPlatformObj);
                    if ((range_km <= maxRange_km) && (obj->MatchesClassificationMask(classMask)))
                    {
                        tcTrack track;
                        if (mpSimState->GetTruthTrack(obj->mnID, track))
                        {
                            trackList.track.push_back(track);
                        }
                    }
                }
            }
        }
        else if (findAirbases) // find friendly flight objs within maxRange_km, only returns compatible with this aircraft
        {
            for (iter.First();iter.NotDone();iter.Next())
            {
                tcGameObject* obj = iter.Get();

                if ((obj->GetAlliance() == mpPlatformObj->GetAlliance()) && (obj != mpPlatformObj) &&
                    (obj->RangeTo(*mpPlatformObj) <= maxRange_km)  )
                {
                    if (tcFlightOpsObject* flightOps = dynamic_cast<tcFlightOpsObject*>(obj))
                    {
                        tcFlightPort* flightPort = flightOps->GetFlightPort();
                        bool isCarrier = dynamic_cast<tcCarrierObject*>(obj) != 0;
                        bool heloOnly = flightPort->IsHeloOnly();
                        bool matches = (carrierCompatible || !isCarrier) && (!heloOnly || thisPlatformIsHelo);
                        bool runwayLengthOkay = (air != 0) && (flightPort->GetMaxRunwayLength() >= air->mpDBObject->minimumRunway_m);
                        if (matches && runwayLengthOkay)
                        {
                            tcTrack track;
                            if (mpSimState->GetTruthTrack(obj->mnID, track))
                            {
                                trackList.track.push_back(track);
                            }
                        } 
                    }
                }
            }
        }
        else // (findTankers) // find friendly tankers within maxRange_km
        {
            for (iter.First();iter.NotDone();iter.Next())
            {
                tcGameObject* obj = iter.Get();
                tcAirObject* air = dynamic_cast<tcAirObject*>(obj);

                if ((air != 0) && (air->IsTanker()) && (air->GetAffiliationWith(mpPlatformObj) == tcAllianceInfo::FRIENDLY) && 
                    (air != mpPlatformObj) && (air->RangeTo(*mpPlatformObj) <= maxRange_km))
                {
                    bool tankerHasFuel = (air->fuel_kg > 0.1f * air->GetFuelCapacity());
                    if (tankerHasFuel)
                    {
                        tcTrack track;
                        if (mpSimState->GetTruthTrack(air->mnID, track))
                        {
                            trackList.track.push_back(track);
                        }
                    }
                }
            }
        }

        return trackList;
    }


    /**
    * @param track Track to intercept.
    * @return intercept heading to track in radians.
    */
    float tcPlatformInterface::GetInterceptHeadingToTrack(const tcSensorMapTrack& track)
    {
        if (mpPlatformObj == 0) return 0;

        float fHeading_rad, fTTI;

        mpPlatformObj->mcKin.GetInterceptData2D(track, fHeading_rad, fTTI);
        return fHeading_rad;
    }

    /**
    * @param track Track to get range info about.
    * @return range in km
    */
    float tcPlatformInterface::GetRangeToTrack(const tcSensorMapTrack& track)
    {
        if (mpPlatformObj == 0) return 0;
        wxASSERT(mpPlatformObj);

        return mpPlatformObj->mcKin.RangeToKm(track);
    }


    /**
    * Sets heading to intercept track.
    * @param track Track to intercept.
    * @return time to intercept in seconds.
    */
    float tcPlatformInterface::SetHeadingToInterceptTrack(tcSensorMapTrack track)
    {
        if (mpPlatformObj == 0) return 0;
		if (!mpPlatformObj->IsControlled()) return 0;
        float fHeading_rad, fTTI;

        mpPlatformObj->mcKin.GetInterceptData2D(track, fHeading_rad, fTTI);
        mpPlatformObj->SetHeading(fHeading_rad);
        return fTTI;
    }


    tcSensorMapTrack tcPlatformInterface::GetTrackById(long id)
    {
        tcSensorMapTrack track;

        if (mpPlatformObj == 0) return track;

        mpSimState->GetTrack(id, mpPlatformObj->GetAlliance(), track);

        double t = mpSimState->GetTime();
        tcSensorMapTrack predictedTrack(track);
        track.GetPrediction(predictedTrack, t);

        return predictedTrack;
    }



    int tcPlatformInterface::GetSensorCount()
    {
        if (mpPlatformObj == 0) return 0;

        return (int)mpPlatformObj->GetSensorCount();
    }

    tcSensorInfo tcPlatformInterface::GetSensorInfo(int n)
    {
        tcSensorInfo info;

        info.type = 0xFF;

        if (mpPlatformObj == 0) return info;

        unsigned nSensors = mpPlatformObj->GetSensorCount();
        if ((n < 0)||((unsigned)n >= nSensors)) return info;

        const tcSensorState* sensor_state = mpPlatformObj->GetSensor(n);
        info.isActive = sensor_state->IsActive();
        info.type = 0;

        if (sensor_state->IsRadar())
        {
            info.type = 1;
        }
        else if (sensor_state->IsESM())
        {
            info.type = 2;
        }
        else if (sensor_state->IsSonar())
        {
            tcSonarDBObject* sonar = dynamic_cast<tcSonarDBObject*>(sensor_state->mpDBObj);
            if (sonar->isPassive) info.type += 4;
            if (sonar->isActive) info.type += 8;
        }
        else if (sensor_state->IsOptical())
        {
            info.type = 16;
        }
		else if (sensor_state->IsECM())
		{
			info.type = 32;
		}
        else // error
        {
            fprintf(stderr, "tcPlatformInterface::GetSensorInfo - bad sensor type\n");
        }

        return info;
    }

    /**
    * Activates or deactivates all sensors.
    * @param anState 0 - all sensors off, 1 - all sensors on
    */
    void tcPlatformInterface::SetAllSensorState(int anState) 
    {
        if (mpPlatformObj == 0) return;

		if (!mpPlatformObj->IsControlled()) return;
        unsigned nSensors = mpPlatformObj->GetSensorCount();

        for(unsigned n=0;n<nSensors;n++)
        {
            mpPlatformObj->SetSensorState(n, anState != 0);
        }
    }

    void tcPlatformInterface::SetSensorState(int n, int state)
    {
        if (mpPlatformObj == 0) return;

		if (!mpPlatformObj->IsControlled()) return;
        mpPlatformObj->SetSensorState((unsigned)n, state != 0);
    }


	std::string tcPlatformInterface::GetController() const
	{
        if (mpPlatformObj == 0) return std::string("Error, not platform");

		return std::string(mpPlatformObj->GetController());
	}

	bool tcPlatformInterface::IsAvailable() const
	{
        if (mpPlatformObj == 0) return false;

		return mpPlatformObj->IsAvailable();
	}

	bool tcPlatformInterface::IsMultiplayerActive() const
	{
		return mpSimState->IsMultiplayerActive();
	}

	void tcPlatformInterface::ReleaseControl()
	{
        if (mpPlatformObj == 0) return;

		using network::tcMultiplayerInterface;
		if (mpPlatformObj->IsControlled())
		{
			if (tcMultiplayerInterface::Get()->IsServer())
			{
				mpPlatformObj->SetController("");
			}
			else
			{
				tcMultiplayerInterface::Get()->SendControlRelease(mpPlatformObj->mnID);
			}
		}
	}


	void tcPlatformInterface::TakeControl()
	{
        if (mpPlatformObj == 0) return;

		using network::tcMultiplayerInterface;
		if (mpPlatformObj->IsAvailable())
		{
			if (tcMultiplayerInterface::Get()->IsServer())
			{
				mpPlatformObj->SetController(tcUserInfo::Get()->GetUsername());
			}
			else
			{
				tcMultiplayerInterface::Get()->SendControlRequest(mpPlatformObj->mnID);
			}
		}
	}



    double tcPlatformInterface::GetTime() const
    {
        if (mpPlatformObj == 0) return -123.4;

        wxASSERT(mpPlatformObj);
        return mpPlatformObj->mfStatusTime;
    }

    /**
    * Request user input. Python callback function is called after input is 
    * obtained 
    */
    void tcPlatformInterface::GetUserInput(std::string callback, std::string uitype)
    {
        if (mpCommandQueue == 0) return;
        mpCommandQueue->GetUserInput(callback.c_str(), uitype.c_str(), -1, "");
    }
    

    bool tcPlatformInterface::IsPlayerControlled() const
    {
        if (mpPlatformObj == 0) return false;

		// single player, check for alliance match only
		if (!mpSimState->IsMultiplayerActive())
		{
			return mpSimState->mpUserInfo->IsOwnAlliance(mpPlatformObj->GetAlliance());
		}
		else
		{
			return mpPlatformObj->IsControlled();
		}
    }

    long tcPlatformInterface::LookupFriendlyId(const std::string& unitName)
    {
        if (mpPlatformObj == 0) return -1;

        tcGameObject* obj = mpSimState->GetObjectByName(unitName);
        bool isOwnAlliance = (obj != 0) && (mpPlatformObj->GetAlliance() == obj->GetAlliance());

        if ((obj == 0) || !isOwnAlliance)
		{
			return -1;
		} 
		else
		{
            return obj->mnID;
        }
    }
    
    std::string tcPlatformInterface::LookupFriendlyName(long id)
    {
        if (mpPlatformObj == 0) return "Error, not platform";

        tcGameObject* obj = mpSimState->GetObject(id);
		bool isOwnAlliance = (obj != 0) && (mpPlatformObj->GetAlliance() == obj->GetAlliance());

        if ((obj == 0) || !isOwnAlliance)
		{
			return std::string("");
		} 
		else
		{
            return std::string(obj->mzUnit.c_str());
        }
    }

    /**
    * Send command through command queue, used for special commands to game engine
    * such as activating the flight deck control panel. 
    */
    void tcPlatformInterface::SendCommand(const std::string& command)
    {
        if (mpCommandQueue == 0) return;
        mpCommandQueue->AddCommand(command.c_str(),-1);
    }

    /**
    * @return true if interface has valid (non null) platform object
    */
    bool tcPlatformInterface::IsValid() const
    {
        return mpPlatformObj != 0;
    }


    /**
    * print message to user console
    */
    void tcPlatformInterface::DisplayMessage(const std::string& text) 
    {
        wxASSERT(mpConsole);
        wxASSERT(mpPlatformObj != 0);
        if (mpPlatformObj == 0) return;

        if (isPlatformOwnAlliance) 
		{
			mpConsole->Print(text.c_str());
			fprintf(stdout, "* msg from platform:%d %s\n", mpPlatformObj->mnID, text.c_str());
		}
#ifdef _DEBUG
		else
		{
			fprintf(stdout, "* msg from OPFOR:%d %s\n", mpPlatformObj->mnID, text.c_str());
		}
#endif
    }


    /**
    * print message to user console
    */
    void tcPlatformInterface::DisplayPopupMessage(const std::string& text) 
    {
        wxASSERT(mpConsole);

        if (isPlatformOwnAlliance) 
		{
            wxString s = wxString::Format("%s: %s", mpPlatformObj->mzUnit.c_str(), text.c_str());
            tcMessageInterface::Get()->PopupMessage(s.ToStdString(), mpPlatformObj->mnID);
#ifdef _DEBUG
			fprintf(stdout, "* popup msg from platform:%d %s\n", mpPlatformObj->mnID, text.c_str());
#endif
		}
#ifdef _DEBUG
		else
		{
			fprintf(stdout, "* popup msg from OPFOR:%d %s\n", mpPlatformObj->mnID, text.c_str());
		}
#endif
    }

    /**
    * Modified to use string argument
    * May want to handle this through a single instance class in the future
    */
    void tcPlatformInterface::PlaySound(const std::string& effect)
    {
        tcSound::Get()->PlayEffect(effect);
    }

	void tcPlatformInterface::SetActionText(const std::string& text) 
	{
        if (mpPlatformObj == 0) return;

        mpPlatformObj->GetBrain()->SetActionText(text);
	}

    // flightport (airstrip, cv flight deck, helo pad)
    bool tcPlatformInterface::HasFlightPort(void)
    {
        if (dynamic_cast<tcFlightOpsObject*>(mpPlatformObj))
		{
			return true;
		}
		else
		{
			return false;
		}
    }

	/**
	* Id is set to -1 if no landing data available
	* Heading_rad has runway orientation
	*
	* @returns track with landing data for platform matching id
	*/
	tcTrack tcPlatformInterface::GetLandingData(long id)
	{
        static tcTrack errorTrack;

        if (mpPlatformObj == 0) return errorTrack;

        tcGameObject* obj = mpSimState->GetObject(id);

		bool isOwnAlliance = mpPlatformObj->GetAlliance() == obj->GetAlliance();

        if ((obj == 0) || !isOwnAlliance)
		{
			tcTrack data;
			data.mnID = -1;
			return data;
		}

        tcFlightOpsObject* flightOps = dynamic_cast<tcFlightOpsObject*>(obj);
        if (flightOps == 0)
        {
			tcTrack data;
			data.mnID = -1;
			return data;
        }

        tcAirObject* air = dynamic_cast<tcAirObject*>(mpPlatformObj);

        // if target platform is a surface platform, check that landing aircraft
        // is carrier compatible
        if (tcSurfaceObject* surface = dynamic_cast<tcSurfaceObject*>(obj))
        {
            if ((air == 0) || !air->mpDBObject->IsCarrierCompatible())
            {
			    tcTrack data;
			    data.mnID = -1;
			    return data;
            }
        }
        else // verify that runway length is long enough
        {
            if ((air == 0) || (air->mpDBObject->minimumRunway_m > flightOps->GetFlightPort()->GetMaxRunwayLength()))
            {
			    tcTrack data;
			    data.mnID = -1;
			    return data;
            }
        }


		return flightOps->GetLandingData();
	}


    tcFlightPortInterface tcPlatformInterface::GetFlightPortInfo()
    {
        tcFlightPortInterface fpi;
        
        tcFlightOpsObject* flightOps = dynamic_cast<tcFlightOpsObject*>(mpPlatformObj);
        if (flightOps != 0) 
        {
			fpi.flightport = flightOps->GetFlightPort();
        }
        return fpi;
    }

    tcMissionInterface tcPlatformInterface::GetMissionInfo()
    {
        tcMissionInterface missionInterface;
        
        if (mpPlatformObj == 0) return missionInterface;

        ai::BlackboardInterface bb = mpPlatformObj->GetBrain()->GetBlackboardInterface();

        if (!bb.KeyExists("Mission")) return missionInterface;

        wxString missionIdent = bb.ReadMessage("Mission");
        if (missionIdent.size() == 0) return missionInterface;

        long hostId = -1; // id of base hosting mission
        long missionId = -1; // mission id within base

        wxString s = missionIdent.BeforeFirst('-');
        s.ToLong(&hostId);
        s = missionIdent.AfterFirst('-');
        s.ToLong(&missionId);

        tcFlightOpsObject* flightOps = dynamic_cast<tcFlightOpsObject*>(mpSimState->GetObject(hostId));
        if ((flightOps == 0) || (missionId < 1)) return missionInterface;

        tcFlightPort* flightPort = flightOps->GetFlightPort();
        if (flightPort == 0) return missionInterface;

        tcMissionManager* missionManager = flightPort->GetMissionManager();
        if (missionManager == 0) return missionInterface;

        ai::tcAttackMission* mission = dynamic_cast<ai::tcAttackMission*>(missionManager->GetMission(missionId));
        missionInterface.SetMission(mission);

        return missionInterface;
    }


	void tcPlatformInterface::DeletePlatform()
	{
        if (mpPlatformObj == 0) return;

		if (!mpPlatformObj->IsEditMode()) return;

        tcScenarioRandomizer* randomizer = tcScenarioRandomizer::Get();
        randomizer->DeleteUnit(mpPlatformObj->mzUnit.c_str());

		mpSimState->DeleteObject(mpPlatformObj->mnID);

        SetPlatform(0);

        tcSimPythonInterface::Get()->SetMenuPlatform(-1);
	}


	void tcPlatformInterface::MovePlatform(float afLon_rad, float afLat_rad)
	{
        if (mpPlatformObj == 0) return;

		if (!(mpPlatformObj->IsEditMode() || isDeveloperMode)) return;

        if (afLon_rad < -C_PI) afLon_rad += C_TWOPI;
        else if (afLon_rad >= C_PI) afLon_rad -= C_TWOPI;

        if ((afLon_rad >= C_PI) || (afLon_rad < -C_PI) || (afLat_rad < -C_PIOVER2) || (afLat_rad > C_PIOVER2))
        {
            fprintf(stderr, "tcPlatformInterface::MovePlatform - coordinate out of bounds (%f, %f)\n",
                afLon_rad, afLat_rad);
            wxASSERT(false);
            return;
        }

        tcKinematics& kin = mpPlatformObj->mcKin;
        float oldTerrainHeight = mapData->GetTerrainHeight(C_180OVERPI*kin.mfLon_rad, C_180OVERPI*kin.mfLat_rad, 0);
        float newTerrainHeight = mapData->GetTerrainHeight(C_180OVERPI*afLon_rad, C_180OVERPI*afLat_rad, 0);

        // class-specific altitude adjustment
        if (tcAirObject *airObj = dynamic_cast<tcAirObject*>(mpPlatformObj))
        {
            if (kin.mfAlt_m < newTerrainHeight + 10.0f)
            {
                kin.mfAlt_m = newTerrainHeight + 10.0f;
            }
			if (kin.mfAlt_m < 50.0f)
			{
				kin.mfAlt_m = 50.0f;
			}
            
            airObj->SetAltitude(airObj->mcKin.mfAlt_m);
        }
        if (tcSubObject* sub = dynamic_cast<tcSubObject*>(mpPlatformObj))
        {
            if (kin.mfAlt_m < newTerrainHeight + 10.0f)
            {
                kin.mfAlt_m = newTerrainHeight + 10.0f;
            }
            sub->SetAltitude(kin.mfAlt_m);
        }

		// place ground objects relative to terrain height
		if (tcAirfieldObject* fieldObj = dynamic_cast<tcAirfieldObject*>(mpPlatformObj))
		{
            kin.mfAlt_m = newTerrainHeight;
		}
		else if (tcGroundObject* groundObj = dynamic_cast<tcGroundObject*>(mpPlatformObj))
		{
			kin.mfAlt_m = newTerrainHeight;
		}
		else if (tcGroundVehicleObject* groundVehicleObj = dynamic_cast<tcGroundVehicleObject*>(mpPlatformObj))
		{
			kin.mfAlt_m = newTerrainHeight;
		}



		mpPlatformObj->mcKin.mfLon_rad = afLon_rad;
		mpPlatformObj->mcKin.mfLat_rad = afLat_rad;
	}

	void tcPlatformInterface::RenamePlatform(const std::string& s)
	{
        if (mpPlatformObj == 0) return;

		if (!mpPlatformObj->IsEditMode()) return;

		if (s.size() < 2) return;

        if (mpSimState->GetObjectByName(s) != 0)
        {
            wxString msg = wxString::Format("Platform name already exists, ignoring rename (%s)", s.c_str());
            wxMessageBox(msg, "Rename Failed");
            return; // already exists
        }

        tcScenarioRandomizer* randomizer = tcScenarioRandomizer::Get();
        randomizer->RenameUnit(mpPlatformObj->mzUnit.c_str(), s);

		mpSimState->RenameObject(mpPlatformObj, s);
	}

    tcStringArray tcPlatformInterface::GetPlatformListByClass(const std::string& classString)
    {
        tcStringArray error;

        if ((mpPlatformObj != 0) && (mpPlatformObj->IsEditMode()))
        {
            return scenarioInterface->GetPlatformListByClass(classString);
        }
        else
        {
            return error;
        }
    }

    /**
    * @return list of platform names for this class based on platform_names table in database
    *
    * Edit mode command (though not really necessary to restrict)
    */
    tcStringArray tcPlatformInterface::GetPlatformNameList()
    {
        tcStringArray result;
        if ((mpPlatformObj != 0) && (mpPlatformObj->IsEditMode()))
        {
            tcDatabase* database = tcDatabase::Get();
            wxArrayString arrayString = database->GetPlatformNames(mpPlatformObj->mzClass.c_str());

            for (size_t n=0; n<arrayString.size(); n++)
            {
                std::string name_n(arrayString[n].c_str());

                if (mpSimState->GetObjectByName(name_n) == 0)
                {   // don't allow duplicate names
                    result.AddString(name_n.c_str());
                }
            }

            return result;
        }
        else
        {
            return result;
        }
    }

    /**
    * Edit mode or friendly unit only
    */
    tcPlatformInterface tcPlatformInterface::GetUnitInterface(const std::string& unitName)
    {
        wxASSERT(mpSimState != 0);

		tcGameObject* obj = mpSimState->GetObjectByName(unitName);
		tcPlatformObject* platform = dynamic_cast<tcPlatformObject*>(obj);

		if (tcGameObject::IsEditMode())
		{
			return tcPlatformInterface(platform);
		}

		bool isFriendly = (platform != 0) && (mpPlatformObj != 0) && (mpPlatformObj->GetAffiliationWith(platform) == tcAllianceInfo::FRIENDLY);

		if (isFriendly)
		{
			return tcPlatformInterface(platform);
		}
		else
		{
			return tcPlatformInterface(0);
		}
    }

    /**
    * Intended for edit mode only
    */
    tcScenarioInterface tcPlatformInterface::GetScenarioInterface()
    {
        if (tcGameObject::IsEditMode())
        {
            return *scenarioInterface;
        }
        else
        {
            wxMessageBox("Access to ScenarioInterface blocked not allowed game play. Corrupt script file?", "Warning");
            return *scenarioInterface;
        }
    }


    void tcPlatformInterface::AddUnitToFlightDeck(const std::string& className)
    {
        if ((mpPlatformObj == 0) || (!mpPlatformObj->IsEditMode())) return;

        size_t nGroup = scenarioInterface->GetAirGroupCount();
        std::string groupName = scenarioInterface->GetAirGroupName();
        unsigned int startId = scenarioInterface->GetAirUnitId();
        for (size_t n=0; n<nGroup; n++)
        {
            wxString unitName = wxString::Format("%s-%d", groupName.c_str(), n+startId);
            //bool result = 
            scenarioInterface->AddUnitToFlightDeck(GetPlatformName(), className, unitName.ToStdString(), 2); // add to ready spot
        }
    }

    void tcPlatformInterface::SetAirGroupName(const std::string& groupName)
    {
        if ((mpPlatformObj == 0) || (!mpPlatformObj->IsEditMode())) return;

        scenarioInterface->SetAirGroupName(groupName);
    }

    std::string tcPlatformInterface::GetAirGroupName() const
    {
        if ((mpPlatformObj == 0) || (!mpPlatformObj->IsEditMode())) return std::string("err");

        return scenarioInterface->GetAirGroupName();
    }

    unsigned int tcPlatformInterface::GetAirUnitId() const
    {
        if ((mpPlatformObj == 0) || (!mpPlatformObj->IsEditMode())) return 0;

        return scenarioInterface->GetAirUnitId();
    }

    void tcPlatformInterface::SetAirGroupCount(unsigned int n)
    {
        if ((mpPlatformObj == 0) || (!mpPlatformObj->IsEditMode())) return;

        scenarioInterface->SetAirGroupCount(n);
    }

    unsigned int tcPlatformInterface::GetAirGroupCount() const
    {
        if ((mpPlatformObj == 0) || (!mpPlatformObj->IsEditMode())) return 0;

        return scenarioInterface->GetAirGroupCount();
    }

    void tcPlatformInterface::SetMagazineAddCount(unsigned int n)
    {
        if ((mpPlatformObj == 0) || (!mpPlatformObj->IsEditMode())) return;

        scenarioInterface->SetMagazineAddCount(n);
    }

    unsigned int tcPlatformInterface::GetMagazineAddCount() const
    {
        if ((mpPlatformObj == 0) || (!mpPlatformObj->IsEditMode())) return 0;

        return scenarioInterface->GetMagazineAddCount();
    }

    void tcPlatformInterface::SetIncludeProbability(float probability)
    {
        if ((mpPlatformObj == 0) || (!mpPlatformObj->IsEditMode())) return;

        return scenarioInterface->SetIncludeProbability(mpPlatformObj->mzUnit.c_str(), probability);
    }

    float tcPlatformInterface::GetIncludeProbability() const
    {
        if ((mpPlatformObj == 0) || (!mpPlatformObj->IsEditMode())) return 1.0f;

        return scenarioInterface->GetIncludeProbability(mpPlatformObj->mzUnit.c_str());
    }

    void tcPlatformInterface::AddRandomBox(float lon1_deg, float lon2_deg, float lat1_deg, float lat2_deg)
    {
        if ((mpPlatformObj == 0) || (!mpPlatformObj->IsEditMode())) return;

        scenarioInterface->AddRandomBox(mpPlatformObj->mzUnit.c_str(), lon1_deg, lon2_deg, lat1_deg, lat2_deg);
    }

    void tcPlatformInterface::DeleteAllRandomBoxes()
    {
        if ((mpPlatformObj == 0) || (!mpPlatformObj->IsEditMode())) return;

        tcScenarioRandomizer::Get()->DeleteAllRandomBoxes(mpPlatformObj->mzUnit.c_str());
    }

    void tcPlatformInterface::UpdateMissionEditGraphics()
    {
        if (mpPlatformObj == 0) return;
            
        if (mpPlatformObj->formation.IsFollower())
        {
            tacticalMap->SetFormationEditId(-1);
            tacticalMap->SetFormationEditId(mpPlatformObj->formation.leaderId);
            tacticalMap->UpdateFormationGraphics();
        }

        tacticalMap->UpdatePatrolAreaGraphics();

        if (!mpPlatformObj->IsEditMode()) return;

        if ((tacticalMap->GetHookCount() == 1) && (tacticalMap->GetHookID(0) == mpPlatformObj->mnID))
        {
            tacticalMap->SetMissionEditId(-1);
            tacticalMap->SetMissionEditId(mpPlatformObj->mnID);
        }
    }

    void tcPlatformInterface::SetAlwaysVisible(bool state)
    {
        if ((mpPlatformObj == 0) || !mpPlatformObj->IsEditMode()) return;

        if (state)
        {
            mpSimState->mcSensorMap.AddAlwaysVisibleTrack(mpPlatformObj->GetName());
        }
        else
        {
            mpSimState->mcSensorMap.DropAlwaysVisibleTrack(mpPlatformObj->GetName());
        }
    }

    bool tcPlatformInterface::GetAlwaysVisible() const
    {
        if ((mpPlatformObj == 0) || !mpPlatformObj->IsEditMode()) return false;

        return mpSimState->mcSensorMap.GetAlwaysVisibleState(mpPlatformObj);
    }


    float tcPlatformInterface::GetCost() const
    {
        if (mpPlatformObj != 0)
        {
            return mpPlatformObj->GetCost();
        }
        else
        {
            wxASSERT(false);
            return 0;
        }
    }

    void tcPlatformInterface::SetCost(float val)
    {
        if ((mpPlatformObj == 0) || !mpPlatformObj->IsEditMode()) return;

        mpPlatformObj->SetCost(val);
    }


    bool tcPlatformInterface::IsDeveloperMode() const
    {
        return isDeveloperMode;
    }

    void tcPlatformInterface::SetInvulnerable(bool state)
    {
        if ((!isDeveloperMode)) return;

        if (mpPlatformObj != 0)
        {
            mpPlatformObj->SetInvulnerable(state);
        }
        else
        {
            wxASSERT(tacticalMap != 0);
            if (tacticalMap->hookedId.size() > 0)
            {
                tcGameObject* obj = mpSimState->GetObject(tacticalMap->hookedId[0]);
                if (obj != 0)
                {
                    obj->SetInvulnerable(state);
                }
            }
        }

    }


    void tcPlatformInterface::LaunchAtMe(const std::string& weaponClass, unsigned int quantity)
    {
        std::string targetName;

        if ((!isDeveloperMode)) return;

        if (mpPlatformObj != 0)
        {
            targetName = GetPlatformName();
        }
        else
        {
            wxASSERT(tacticalMap != 0);
            if (tacticalMap->hookedId.size() > 0)
            {
                tcGameObject* obj = mpSimState->GetObject(tacticalMap->hookedId[0]);
                if (obj != 0)
                {
                    targetName = obj->GetName();
                }
            }
        }

        if (targetName.size() == 0) return;

        tcWeaponTester* weaponTester = tcWeaponTester::Get();
        wxASSERT(weaponTester != 0);

        weaponTester->InitializePlatform(); // in case database has changed

        weaponTester->SetTarget(targetName);
        weaponTester->SetWeapon(weaponClass);
        //weaponTester->SetQuantity(quantity);

        //mpPlatformObj->SetInvulnerable(state);
    }

    void tcPlatformInterface::SetTestParameter(const std::string& paramName, float val)
    {
        if ((!isDeveloperMode)) return;

        tcWeaponTester* weaponTester = tcWeaponTester::Get();
        wxASSERT(weaponTester != 0);

        weaponTester->InitializePlatform(); // in case database has changed

        if (paramName == "WeaponTesterLaunchRangeKm")
        {
            weaponTester->SetLaunchRange_km(val);
        }
        else if (paramName == "WeaponTesterLaunchQuantity")
        {
            weaponTester->SetQuantity(unsigned int(val));
        }
        else if (paramName == "WeaponTesterLaunchAltitude")
        {
            weaponTester->SetLaunchAltitude_m(val);
        }
        else if (paramName == "WeaponTesterLaunchInterval")
        {
            weaponTester->SetLaunchInterval(val);
        }

    }

	void tcPlatformInterface::ApplyDamage(float damageFraction)
	{
		if ((!isDeveloperMode)) return;

		if (mpPlatformObj != 0)
        {
			if (damageFraction > 0)
			{
				mpPlatformObj->ApplyGeneralDamage(damageFraction, 0);
			}
			else if (damageFraction < 0)
			{
				mpPlatformObj->ApplyRepairs(-damageFraction);
			}
        }
	}

	void tcPlatformInterface::ApplyAdvancedDamage(bool isPen, float kinetic_J, float explosive_kg, float blast_psi,
		float waterBlast_psi, float thermal_J_cm2, float fragHits,float fragEnergy_J)
	{
		if ((!isDeveloperMode)) return;

		if (mpPlatformObj != 0)
		{
			Damage dmg;
			dmg.isPenetration = isPen;
			dmg.kinetic_J = kinetic_J;
			dmg.explosive_kg = explosive_kg;
			dmg.blast_psi = blast_psi;
			dmg.waterBlast_psi = waterBlast_psi;
			dmg.thermal_J_cm2 = thermal_J_cm2;
			dmg.fragHits = fragHits;
			dmg.fragEnergy_J = fragEnergy_J;

			mpPlatformObj->ApplyAdvancedDamage(dmg, 0);
		}
	}

	tcStringTable tcPlatformInterface::QueryDatabase(const std::string& table, const std::string& databaseClass, const std::string& fields)
	{
		tcDatabase* database = tcDatabase::Get();

		tcStringTable result = database->GetFieldsForAllRows(table, databaseClass, fields);

		if (result.Size() > 0)
		{
			return result;
		}
		else
		{
			tcStringArray errorArray;
			errorArray.PushBack("Error");
			result.AddStringArray(errorArray);
			return result;
		}
	}


	void tcPlatformInterface::GetLocalObj() 
	{
		wxASSERT(mpSimState);

		mpPlatformObj = mpStaticPlatformObj;
		GetSensorMap();

		if (mpSimState->IsMultiplayerServer())
		{
			isPlatformOwnAlliance = mpPlatformObj != 0;
		}
		else
		{
			isPlatformOwnAlliance = (mpPlatformObj) ?
				(mpSimState->mpUserInfo->IsOwnAlliance(mpPlatformObj->GetAlliance()) != 0) : false;
		}
	}

    /**
    * This method directly sets local obj
    */
    void tcPlatformInterface::SetPlatform(tcPlatformObject *obj) 
    {
        wxASSERT(mpSimState);

        mpPlatformObj = obj;
        GetSensorMap();

		if (mpSimState->IsMultiplayerServer())
		{
			isPlatformOwnAlliance = mpPlatformObj != 0;
		}
		else
		{
			isPlatformOwnAlliance = (mpPlatformObj) ?
				(mpSimState->mpUserInfo->IsOwnAlliance(mpPlatformObj->GetAlliance()) != 0) : false;
		}
    } 

	void tcPlatformInterface::SetDateFiltering(bool state)
	{
		enableDateFiltering = state;
	}


    tcPlatformObject* tcPlatformInterface::mpStaticPlatformObj = 0;
    tcSimState* tcPlatformInterface::mpSimState = 0;
    tcAllianceSensorMap* tcPlatformInterface::mpSensorMap = 0;
    tcSoundConsole* tcPlatformInterface::mpConsole = 0;
    tcCommandQueue* tcPlatformInterface::mpCommandQueue = 0;
	tcMapData* tcPlatformInterface::mapData = 0;
    tcTacticalMapView* tcPlatformInterface::tacticalMap = 0;
    bool tcPlatformInterface::isDeveloperMode = false;
    tcScenarioInterface* tcPlatformInterface::scenarioInterface = 0;
	bool tcPlatformInterface::enableDateFiltering = false;

	tcPlatformInterface::tcPlatformInterface()
		: mpPlatformObj(0)
	{
		wxASSERT(mpSimState);
	}

	tcPlatformInterface::tcPlatformInterface(tcPlatformObject* obj)
		: mpPlatformObj(obj)
	{
		wxASSERT(mpSimState);

		if (mpSimState->IsMultiplayerServer())
		{
			isPlatformOwnAlliance = mpPlatformObj != 0;
		}
		else
		{
			isPlatformOwnAlliance = (mpPlatformObj) ?
				(mpSimState->mpUserInfo->IsOwnAlliance(mpPlatformObj->GetAlliance()) != 0) : false;
		}

		mpSensorMap = (mpPlatformObj != 0) ? mpSimState->mcSensorMap.GetMap(mpPlatformObj->GetAlliance()) : 0;

	}

	tcPlatformInterface::~tcPlatformInterface()
	{
	}


}

