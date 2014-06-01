/**
**  @file tcCarrierObject.cpp
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

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "tcCarrierObject.h"
#include "tcAirObject.h"
#include "tcAeroAirObject.h"
#include "tcJetDBObject.h"
#include "tcShipDBObject.h"
#include "tcFlightOpsObject.h"
#include "common/tcStream.h"
#include "common/tcObjStream.h"
#include "common/tcGameStream.h"
#include "tcScenarioLogger.h"
#include "ai/Brain.h"
#include "ai/Task.h"
#include "tcDatabase.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



/**
* Loads state from command stream
*/
tcCommandStream& tcCarrierObject::operator<<(tcCommandStream& stream)
{
    tcPlatformObject::operator<<(stream);

	tcFlightOpsObject::operator<<(stream);

    return stream;
}

/**
* Saves state to command stream
*/
tcCommandStream& tcCarrierObject::operator>>(tcCommandStream& stream)
{
    tcPlatformObject::operator>>(stream);

	tcFlightOpsObject::operator>>(stream);

    return stream;
}

/**
* Loads state from create stream
*/
tcCreateStream& tcCarrierObject::operator<<(tcCreateStream& stream)
{
    tcPlatformObject::operator<<(stream);

	tcFlightOpsObject::operator<<(stream);

    return stream;
}

/**
* Saves state to create stream
*/
tcCreateStream& tcCarrierObject::operator>>(tcCreateStream& stream)
{
    tcPlatformObject::operator>>(stream);  

	tcFlightOpsObject::operator>>(stream);

    return stream;
}


/**
* Loads state from update stream
*/
tcUpdateStream& tcCarrierObject::operator<<(tcUpdateStream& stream)
{
    tcPlatformObject::operator<<(stream);

	tcFlightOpsObject::operator<<(stream);

    return stream;
}

/**
* Saves state to update stream
*/
tcUpdateStream& tcCarrierObject::operator>>(tcUpdateStream& stream)
{
    tcPlatformObject::operator>>(stream);

	tcFlightOpsObject::operator>>(stream);

    return stream;
}


/**
* Loads state from game stream
*/
tcGameStream& tcCarrierObject::operator<<(tcGameStream& stream)
{
    tcPlatformObject::operator<<(stream);

	tcFlightOpsObject::operator<<(stream);

    return stream;
}

/**
* Saves state to game stream
*/
tcGameStream& tcCarrierObject::operator>>(tcGameStream& stream)
{
    tcPlatformObject::operator>>(stream);

	tcFlightOpsObject::operator>>(stream);

    return stream;
}


/**
* @return damage fraction for new damage, 0 means no new damage
*/
float tcCarrierObject::ApplyAdvancedDamage(const Damage& damage, tcGameObject* damager)
{
    float startDamageLevel = mfDamageLevel;

    float damageFraction = tcPlatformObject::ApplyAdvancedDamage(damage, damager);

    float generalDamage = mfDamageLevel - startDamageLevel;

    bool aircraftDamaged = tcFlightOpsObject::ApplyAdvancedDamage(damage, damager, generalDamage);

    if (aircraftDamaged)
    {   // add an "A" to the damage string to indicate that aircraft were damaged
        std::string s = GetLastDamageDescription();
        s += "A";
        SetLastDamageDescription(s);

        damageFraction += 0.0001f; // so that damage is reported
    }

    return damageFraction;
}



void tcCarrierObject::ApplyGeneralDamage(float damage, tcGameObject* damager)
{
	tcPlatformObject::ApplyGeneralDamage(damage, damager);

	if (mfDamageLevel >= 1.0f)
	{
        tcFlightOpsObject::DestroyAllChildrenAndUpdateScore(damager);
		tcFlightOpsObject::Clear(); // destroy all captive entities
	}
}

void tcCarrierObject::ClearNewCommand()
{
	tcPlatformObject::ClearNewCommand();

	tcFlightOpsObject::ClearNewCommand();
}

bool tcCarrierObject::HasNewCommand() const
{
	return (tcPlatformObject::HasNewCommand() || tcFlightOpsObject::HasNewCommand());
}

void tcCarrierObject::AutoConfigurePlatform(const std::string& setupName)
{
    std::vector<database::AirComplement> airComplement;
    std::vector<database::MagazineLoadout> magazineLoadout;
    std::vector<database::LauncherLoadout> launcherLoadout;

    tcPlatformObject::GetAutoConfigurationData(setupName, airComplement, magazineLoadout, launcherLoadout);

    tcPlatformObject::AutoConfigureMagazines(magazineLoadout);
    tcPlatformObject::AutoConfigureLaunchers(launcherLoadout);

    tcFlightOpsObject::AutoConfigureAirComplement(airComplement);
}


void tcCarrierObject::Clear() 
{
   tcSurfaceObject::Clear();
   tcFlightOpsObject::Clear();
}

/**
* Randomly initializes object
*/
void tcCarrierObject::RandInitNear(float afLon_deg, float afLat_deg) 
{
 //  tcGameObject::RandInitNear(afLon,afLat);  // why can't we call base here ? virtual issue?
   if (mpDBObject == NULL) {return;}
   mzClass = mpDBObject->mzClass;
   mzUnit = "CV_";
   mzUnit.AssignRandomSuffix();

   mfStatusTime = 0;        
   mcKin.mfLon_rad = C_PIOVER180*(afLon_deg + randfc(1.1f));      
   mcKin.mfLat_rad = C_PIOVER180*(afLat_deg + randfc(1.1f));
   mcKin.mfAlt_m = 0.0f;               
   mcKin.mfHeading_rad = C_TWOPI*randf();           
   mcKin.mfSpeed_kts = mpDBObject->mfMaxSpeed_kts;
   mfDamageLevel = 0;  
   mcGS.SetHeading(mcKin.mfHeading_rad);
   mcGS.SetSpeed(mcKin.mfSpeed_kts);   
   mcGS.SetAltitude(mcKin.mfAlt_m);

   tcFlightOpsObject::RandInitNear(afLon_deg, afLat_deg);

}

/******************************************************************************/
void tcCarrierObject::PrintToFile(tcFile& file) 
{
   tcSurfaceObject::PrintToFile(file);
   tcFlightOpsObject::PrintToFile(file);
}
/******************************************************************************/
void tcCarrierObject::SaveToFile(tcFile& file) 
{
   tcSurfaceObject::SaveToFile(file); 
}
/******************************************************************************/
void tcCarrierObject::LoadFromFile(tcFile& file) 
{
   tcSurfaceObject::LoadFromFile(file);
}
/******************************************************************************/
void tcCarrierObject::Serialize(tcFile& file, bool mbLoad) 
{
   if (mbLoad) 
   {
      LoadFromFile(file);
   }
   else 
   {
      SaveToFile(file);
   }
}


void tcCarrierObject::SaveToPython(scriptinterface::tcScenarioLogger& logger)
{
	tcPlatformObject::SaveToPython(logger);
	tcFlightOpsObject::SaveToPython(logger);
}

/**
*
*/
void tcCarrierObject::Update(double afStatusTime) 
{
   tcSurfaceObject::Update(afStatusTime);
   tcFlightOpsObject::Update(afStatusTime);
}

#pragma warning (disable : 4355)
/**
*
*/
tcCarrierObject::tcCarrierObject() 
: tcFlightOpsObject(0, this)
{
   Clear();

   mpDBObject = NULL;
   mnModelType = MTYPE_CARRIER;

   if (addTasksOnCreate) brain->AddTask("RefuelAllAircraft", 3.0, ai::Task::PERMANENT | ai::Task::HIDDEN);
}


/******************************************************************************/
/*
tcCarrierObject::tcCarrierObject(tcCarrierObject& o) 
: tcSurfaceObject(o) 
{
}
*/

/**
* Constructor that initializes using info from database entry.
* This object will have its own database object eventually. The
* DB object will have info on number and types of aircraft the carrier
* can hold.
*/
tcCarrierObject::tcCarrierObject(tcShipDBObject* obj)
: tcSurfaceObject(obj), tcFlightOpsObject(obj->GetFlightport(), this)
{
    mpDBObject = obj;
    mnModelType = MTYPE_CARRIER;

    if (addTasksOnCreate) brain->AddTaskDirectly("RefuelAllAircraft", 3.0, ai::Task::PERMANENT | ai::Task::HIDDEN);
}

tcCarrierObject::~tcCarrierObject() 
{
}