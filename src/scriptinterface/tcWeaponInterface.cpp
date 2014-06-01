/**  
**  @file tcWeaponInterface.cpp
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
#include "tcWeaponInterface.h"
#include "tcWeaponObject.h"

#include "tcTorpedoObject.h"
#include "tcMissileObject.h"
#include "tcBallisticMissile.h"
#include "tcBallisticWeapon.h"
#include "tcGuidedBomb.h"
#include "tcTorpedoDBObject.h"
#include "tcMapData.h"
#include "tcScenarioRandomizer.h"
#include "tcSimState.h"
#include "tcSimPythonInterface.h"
#include "tcMessageCenter.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif 

using namespace boost::python;

namespace scriptinterface 
{

    scriptinterface::tcScenarioInterface* tcWeaponInterface::scenarioInterface = 0;

    object tcWeaponInterface::GetInterface() 
    {
        object InterfaceType = class_<tcWeaponInterface>("WeaponInterface")
            .def("IsValid", &tcWeaponInterface::IsValid)
            .def("GetWeaponType", &tcWeaponInterface::GetWeaponType)
            .def("IsLinkActive", &tcWeaponInterface::IsLinkActive)
            .def("UpdateTargetPosition", &tcWeaponInterface::UpdateTargetPosition)
            .def("DisplayMessage", &tcWeaponInterface::DisplayMessage)
            .def("GetPlatformName", &tcWeaponInterface::GetPlatformName)
            .def("GetPlatformClass", &tcWeaponInterface::GetPlatformClass)
            .def("GetPlatformAlliance", &tcWeaponInterface::GetPlatformAlliance)
            .def("GetLongitude", &tcWeaponInterface::GetLongitude)
            .def("GetLatitude", &tcWeaponInterface::GetLatitude)
		    .def("GetAltitude", &tcWeaponInterface::GetAltitude)
            .def("GetHeading", &tcWeaponInterface::GetHeading)
            .def("GetSpeed", &tcWeaponInterface::GetSpeed)
            .def("DeletePlatform", &tcWeaponInterface::DeletePlatform)
            .def("MovePlatform", &tcWeaponInterface::MovePlatform)
            .def("RenamePlatform", &tcWeaponInterface::RenamePlatform)
            .def("GetScenarioInterface", &tcWeaponInterface::GetScenarioInterface)
            .def("GetLocalObj", &tcWeaponInterface::GetLocalObj)
            ; 
        return InterfaceType;
    }

    tcWeaponObject* tcWeaponInterface::static_weapon = 0;

    bool tcWeaponInterface::IsValid()
    {
        return (weapon != 0);
    }

    /// get unit name of platform
    std::string tcWeaponInterface::GetPlatformName()
    {        
        std::string s;
        if (weapon != 0) 
        {
            s = weapon->mzUnit.c_str();
        }
        else 
        {
             s == "err";
        }
        return s;
    }

    /// get database class name of platform
    std::string tcWeaponInterface::GetPlatformClass()
    {
        std::string s;
        if (weapon != 0) 
        {
            s = weapon->mzClass.c_str();
        }
        else 
        {
            s == "err";
        }
        return s;
    }

    unsigned int tcWeaponInterface::GetPlatformAlliance() const
    {
        if (weapon != 0)
        {
            return weapon->GetAlliance();
        }
        else
        {
            wxASSERT(false);
            return 0;
        }
    }

    /**
    * @return longitude in rad
    */
    float tcWeaponInterface::GetLongitude() const
    {
        if (weapon != 0)
        {
            return weapon->mcKin.mfLon_rad;
        }
        else
        {
            return 0;
        }
    }

    /**
    * @return latitude in rad
    */
    float tcWeaponInterface::GetLatitude() const
    {
        if (weapon != 0)
        {
            return weapon->mcKin.mfLat_rad;
        }
        else
        {
            return 0;
        }
    }

    /**
    * @return altitude in m
    */
	float tcWeaponInterface::GetAltitude() const
    {
        if (weapon != 0)
        {
            return weapon->mcKin.mfAlt_m;
        }
        else
        {
            return 0;
        }
    } 


    float tcWeaponInterface::GetHeading() 
    {
        if (weapon == 0) return 0;
        return C_180OVERPI*weapon->mcKin.mfHeading_rad;
    }

    float tcWeaponInterface::GetSpeed() 
    {
        if (weapon == 0) return 0;
        return weapon->mcKin.mfSpeed_kts;
    }


    std::string tcWeaponInterface::GetWeaponType()
    {
        if (weapon == 0) return std::string("Error");

        tcTorpedoObject* torpedo = dynamic_cast<tcTorpedoObject*>(weapon);
        tcMissileObject* missile = dynamic_cast<tcMissileObject*>(weapon);
        tcBallisticMissile* ballisticMissile = dynamic_cast<tcBallisticMissile*>(weapon);
        tcBallisticWeapon* ballistic = dynamic_cast<tcBallisticWeapon*>(weapon);
        tcGuidedBomb* guidedBomb = dynamic_cast<tcGuidedBomb*>(weapon);

        if (missile != 0) return std::string("Missile");
        if (guidedBomb != 0) return std::string("GuidedBomb");
        if (ballistic != 0) return std::string("Ballistic");
        if (ballisticMissile != 0) return std::string("BallisticMissile");

        if (torpedo != 0)
        {
            tcTorpedoDBObject* torpedoData = torpedo->mpDBObject;
            bool isMine = (torpedoData->weaponType == tcTorpedoDBObject::BOTTOM_MINE) ||
                (torpedoData->weaponType == tcTorpedoDBObject::BOTTOM_MINE_CAPTOR);
            if (!isMine)
            {
                return std::string("Torpedo");
            }
            else
            {
                return std::string("Mine");
            }
        }

        return std::string("Error2");
    }

    /**
    * @return true if within datalink range and weapon accepts user datalink commands
    */
    bool tcWeaponInterface::IsLinkActive()
    {
        if (weapon == 0) return false;

        return weapon->IsDatalinkActive();
    }

    void tcWeaponInterface::UpdateTargetPosition(float lon_rad, float lat_rad)
    {
        if ((weapon == 0) || (!weapon->IsDatalinkActive())) return;

        if (tcGuidedBomb* guidedBomb = dynamic_cast<tcGuidedBomb*>(weapon))
        {
            guidedBomb->UpdateTargetPos(lon_rad, lat_rad);
        }
        else if (tcMissileObject* missile = dynamic_cast<tcMissileObject*>(weapon))
        {
            missile->UpdateTargetPos(lon_rad, lat_rad);
        }
    }

/**
    * print message to user console
    */
    void tcWeaponInterface::DisplayMessage(const std::string& text) 
    {
        wxASSERT(weapon != 0);
        if (weapon == 0) return;

        if (weapon->IsOwnAlliance())
		{
            tcMessageCenter::Get()->ConsoleMessage(text);
			fprintf(stdout, "* msg from weapon:%d %s\n", weapon->mnID, text.c_str());
		}
#ifdef _DEBUG
		else
		{
			fprintf(stdout, "* msg from OPFOR weapon:%d %s\n", weapon->mnID, text.c_str());
		}
#endif
    }


	void tcWeaponInterface::DeletePlatform()
	{
        if (weapon == 0) return;

		if (!weapon->IsEditMode()) return;

        tcScenarioRandomizer* randomizer = tcScenarioRandomizer::Get();
        randomizer->DeleteUnit(weapon->mzUnit.c_str());

        tcSimState* simState = tcSimState::Get();
		simState->DeleteObject(weapon->mnID);

        SetWeapon(0);

        tcSimPythonInterface::Get()->SetMenuPlatform(-1);
	}


	void tcWeaponInterface::MovePlatform(float afLon_rad, float afLat_rad)
	{
        if (weapon == 0) return;

		if (!(weapon->IsEditMode())) return;

        if (afLon_rad < -C_PI) afLon_rad += C_TWOPI;
        else if (afLon_rad >= C_PI) afLon_rad -= C_TWOPI;

        if ((afLon_rad >= C_PI) || (afLon_rad < -C_PI) || (afLat_rad < -C_PIOVER2) || (afLat_rad > C_PIOVER2))
        {
            fprintf(stderr, "tcWeaponInterface::MovePlatform - coordinate out of bounds (%f, %f)\n",
                afLon_rad, afLat_rad);
            wxASSERT(false);
            return;
        }

        tcKinematics& kin = weapon->mcKin;

        tcMapData* mapData = tcMapData::Get();
        //float oldTerrainHeight = mapData->GetTerrainHeight(C_180OVERPI*kin.mfLon_rad, C_180OVERPI*kin.mfLat_rad, 0);
        float newTerrainHeight = mapData->GetTerrainHeight(C_180OVERPI*afLon_rad, C_180OVERPI*afLat_rad, 0);

        if (kin.mfAlt_m < newTerrainHeight + 5.0f)
        {
            kin.mfAlt_m = newTerrainHeight + 5.0f;
        }

		weapon->mcKin.mfLon_rad = afLon_rad;
		weapon->mcKin.mfLat_rad = afLat_rad;
	}

	void tcWeaponInterface::RenamePlatform(const std::string& s)
	{
        if (weapon == 0) return;

		if (!weapon->IsEditMode()) return;

		if (s.size() < 2) return;

        tcSimState* simState = tcSimState::Get();
        if (simState->GetObjectByName(s) != 0)
        {
            wxString msg = wxString::Format("Platform name already exists, ignoring rename (%s)", s.c_str());
            wxMessageBox(msg, "Rename Failed");
            return; // already exists
        }

        tcScenarioRandomizer* randomizer = tcScenarioRandomizer::Get();
        randomizer->RenameUnit(weapon->mzUnit.c_str(), s);

		simState->RenameObject(weapon, s);
	}

    /**
    * Intended for edit mode only
    */
    tcScenarioInterface tcWeaponInterface::GetScenarioInterface()
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

    tcWeaponInterface::tcWeaponInterface(tcWeaponObject* weaponObject)
        : weapon(weaponObject)
    {
    }

    tcWeaponInterface::tcWeaponInterface()
    : weapon(0)
    {
    }
    
    tcWeaponInterface::~tcWeaponInterface()
    {
    }


}


