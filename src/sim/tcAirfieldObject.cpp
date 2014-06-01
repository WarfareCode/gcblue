/**
**  @file tcAirfieldObject.cpp
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
#endif

#include "tcAirfieldObject.h"
#include "tcFlightOpsObject.h"
#include "tcGroundDBObject.h"
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
tcCommandStream& tcAirfieldObject::operator<<(tcCommandStream& stream)
{
    tcPlatformObject::operator<<(stream);

	tcFlightOpsObject::operator<<(stream);

    return stream;
}

/**
* Saves state to command stream
*/
tcCommandStream& tcAirfieldObject::operator>>(tcCommandStream& stream)
{
    tcPlatformObject::operator>>(stream);

	tcFlightOpsObject::operator>>(stream);

    return stream;
}

/**
* Loads state from create stream
*/
tcCreateStream& tcAirfieldObject::operator<<(tcCreateStream& stream)
{
    tcPlatformObject::operator<<(stream);

	tcFlightOpsObject::operator<<(stream);

    return stream;
}

/**
* Saves state to create stream
*/
tcCreateStream& tcAirfieldObject::operator>>(tcCreateStream& stream)
{
    tcPlatformObject::operator>>(stream);  

	tcFlightOpsObject::operator>>(stream);

    return stream;
}


/**
* Loads state from update stream
*/
tcUpdateStream& tcAirfieldObject::operator<<(tcUpdateStream& stream)
{
    tcPlatformObject::operator<<(stream);

	tcFlightOpsObject::operator<<(stream);

    return stream;
}

/**
* Saves state to update stream
*/
tcUpdateStream& tcAirfieldObject::operator>>(tcUpdateStream& stream)
{
    tcPlatformObject::operator>>(stream);

	tcFlightOpsObject::operator>>(stream);

    return stream;
}

/**
* Loads state from game stream
*/
tcGameStream& tcAirfieldObject::operator<<(tcGameStream& stream)
{
    tcPlatformObject::operator<<(stream);

	tcFlightOpsObject::operator<<(stream);

    return stream;
}

/**
* Saves state to game stream
*/
tcGameStream& tcAirfieldObject::operator>>(tcGameStream& stream)
{
    tcPlatformObject::operator>>(stream);

	tcFlightOpsObject::operator>>(stream);

    return stream;
}



void tcAirfieldObject::ApplyGeneralDamage(float damage, tcGameObject* damager)
{
	tcPlatformObject::ApplyGeneralDamage(damage, damager);

	if (mfDamageLevel >= 1.0f)
	{
        tcFlightOpsObject::DestroyAllChildrenAndUpdateScore(damager);
		tcFlightOpsObject::Clear(); // destroy all captive entities
	}
}

void tcAirfieldObject::AutoConfigurePlatform(const std::string& setupName)
{
    std::vector<database::AirComplement> airComplement;
    std::vector<database::MagazineLoadout> magazineLoadout;
    std::vector<database::LauncherLoadout> launcherLoadout;

    tcPlatformObject::GetAutoConfigurationData(setupName, airComplement, magazineLoadout, launcherLoadout);

    tcPlatformObject::AutoConfigureMagazines(magazineLoadout);
    tcPlatformObject::AutoConfigureLaunchers(launcherLoadout);

    tcFlightOpsObject::AutoConfigureAirComplement(airComplement);
}


void tcAirfieldObject::ClearNewCommand()
{
	tcPlatformObject::ClearNewCommand();

	tcFlightOpsObject::ClearNewCommand();
}

bool tcAirfieldObject::HasNewCommand() const
{
	return (tcPlatformObject::HasNewCommand() || tcFlightOpsObject::HasNewCommand());
}



void tcAirfieldObject::Clear() 
{
   tcPlatformObject::Clear();
   tcFlightOpsObject::Clear();
}



float tcAirfieldObject::GetOpticalCrossSection() const
{
    return mpDBObject->opticalCrossSection_dBsm;
}



float tcAirfieldObject::GetIRSignature(float az_deg) const
{
    return mpDBObject->GetIRSig_dB(az_deg, tcAirDetectionDBObject::IRMODELA);
}


/**
* Randomly initializes object
*/
void tcAirfieldObject::RandInitNear(float afLon_deg, float afLat_deg) 
{
   if (mpDBObject == NULL) {return;}
   mzClass = mpDBObject->mzClass;
   mzUnit = "AF_";
   mzUnit.AssignRandomSuffix();

   mfStatusTime = 0;        
   mcKin.mfLon_rad = C_PIOVER180*(afLon_deg + randfc(1.1f));      
   mcKin.mfLat_rad = C_PIOVER180*(afLat_deg + randfc(1.1f));
   mcKin.mfAlt_m = 0.0f;               
   mcKin.mfHeading_rad = C_TWOPI*randf();           
   mcKin.mfSpeed_kts = 0;
   mfDamageLevel = 0;  

   tcFlightOpsObject::RandInitNear(afLon_deg, afLat_deg);

}

/******************************************************************************/
void tcAirfieldObject::PrintToFile(tcFile& file) 
{
   tcPlatformObject::PrintToFile(file);
   tcFlightOpsObject::PrintToFile(file);
}
/******************************************************************************/
void tcAirfieldObject::SaveToFile(tcFile& file) 
{
   tcPlatformObject::SaveToFile(file); 
}
/******************************************************************************/
void tcAirfieldObject::LoadFromFile(tcFile& file) 
{
   tcPlatformObject::LoadFromFile(file);
}
/******************************************************************************/
void tcAirfieldObject::Serialize(tcFile& file, bool mbLoad) 
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

void tcAirfieldObject::SaveToPython(scriptinterface::tcScenarioLogger& logger)
{
	tcPlatformObject::SaveToPython(logger);
	tcFlightOpsObject::SaveToPython(logger);
}

/**
* Update method calls flightops update and updates that are not 
* related to motion from tcPlatformObject. (tcAirfieldObject does 
* ot move. )
* TODO: extract sensor and launcher functionality from 
* tcPlatformObject and use as parent classes instead. Then any 
* class that needs sensors or launchers can derive from the 
* appropriate parent class. 
*/
void tcAirfieldObject::Update(double afStatusTime) 
{
	const float min_update_s = 0.0f;
	float dt_s = (float)(afStatusTime - mfStatusTime);

	if ((dt_s <= min_update_s) && !tcGameObject::IsEditMode()) {return;} // added for pause case
	
	tcFlightOpsObject::Update(afStatusTime);

	UpdateEffects();

	wxASSERT(mpDBObject);

	UpdateLauncherState(dt_s);

	UpdateSensors(afStatusTime);

	UpdateMagazines(afStatusTime);

    UpdateAI(afStatusTime);

    Update3D();

	mfStatusTime = afStatusTime; 
}



#pragma warning (disable : 4355)
/**
*
*/
tcAirfieldObject::tcAirfieldObject() 
: tcFlightOpsObject(0, this)
{
   Clear();

   mpDBObject = NULL;
   mnModelType = MTYPE_AIRFIELD;
}


/**
* Constructor that initializes using info from database entry.
* This object will have its own database object eventually. The
* DB object will have info on number and types of aircraft the carrier
* can hold.
*/
tcAirfieldObject::tcAirfieldObject(tcGroundDBObject *obj)
: tcPlatformObject(obj), tcFlightOpsObject(obj->GetFlightport(), this),
  mpDBObject(obj)
{
	mcKin.mfSpeed_kts = 0; // make sure this doesn't move (shouldn't be necessary)
	mnModelType = MTYPE_AIRFIELD;

	
    brain->AddTask("RefuelAllAircraft", 3.0, ai::Task::PERMANENT | ai::Task::HIDDEN);
}

tcAirfieldObject::~tcAirfieldObject() 
{
}