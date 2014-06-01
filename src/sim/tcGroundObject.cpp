/**
**  @file tcGroundObject.cpp
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

#include "tcGroundObject.h"
#include "tcPlatformDBObject.h"
#include "tcGroundDBObject.h"
#include "ai/Brain.h"
#include "ai/Task.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void tcGroundObject::Clear() 
{
   tcPlatformObject::Clear();
}

float tcGroundObject::GetOpticalCrossSection() const
{
    return mpDBObject->opticalCrossSection_dBsm;
}



float tcGroundObject::GetIRSignature(float az_deg) const
{
    return mpDBObject->GetIRSig_dB(az_deg, tcAirDetectionDBObject::IRMODELA);
}


/**
* Randomly initializes object
*/
void tcGroundObject::RandInitNear(float afLon_deg, float afLat_deg) 
{
   if (mpDBObject == NULL) {return;}
   mzClass = mpDBObject->mzClass;
   mzUnit = "GR_";
   mzUnit.AssignRandomSuffix();

   mfStatusTime = 0;        
   mcKin.mfLon_rad = C_PIOVER180*(afLon_deg + randfc(1.1f));      
   mcKin.mfLat_rad = C_PIOVER180*(afLat_deg + randfc(1.1f));
   mcKin.mfAlt_m = 0.0f;               
   mcKin.mfHeading_rad = C_TWOPI*randf();           
   mcKin.mfSpeed_kts = 0;
   mfDamageLevel = 0;  

}


void tcGroundObject::PrintToFile(tcFile& file) 
{
   tcPlatformObject::PrintToFile(file);
}

void tcGroundObject::SaveToFile(tcFile& file) 
{
   tcPlatformObject::SaveToFile(file); 
}

void tcGroundObject::LoadFromFile(tcFile& file) 
{
   tcPlatformObject::LoadFromFile(file);
}

void tcGroundObject::Serialize(tcFile& file, bool mbLoad) 
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



/**
* Update method calls updates that are not 
* related to motion from tcPlatformObject. (tcGroundObject does 
* not move. )
* TODO: extract sensor and launcher functionality from 
* tcPlatformObject and use as parent classes instead. Then any 
* class that needs sensors or launchers can derive from the 
* appropriate parent class. Same thing needs to be done with 
* tcAirfieldObject
*/
void tcGroundObject::Update(double afStatusTime) 
{
	const float min_update_s = 0.0f;
	float dt_s = (float)(afStatusTime - mfStatusTime);

	if (dt_s <= min_update_s) {return;} // added for pause case
	

	UpdateEffects();

	wxASSERT(mpDBObject);

	UpdateLauncherState(dt_s);

	UpdateSensors(afStatusTime);

    UpdateAI(afStatusTime);

    Update3D();

	mfStatusTime = afStatusTime; 
}



#pragma warning (disable : 4355)

/**
*
*/
tcGroundObject::tcGroundObject() 
{
    wxASSERT(false);
    Clear();

    mpDBObject = NULL;
    mnModelType = MTYPE_FIXED;
}



/**
* Constructor that initializes using info from database entry.
*/
tcGroundObject::tcGroundObject(tcGroundDBObject *obj)
: tcPlatformObject(obj),
  mpDBObject(obj)
{
	mcKin.mfSpeed_kts = 0; // make sure this doesn't move (shouldn't be necessary)
	mnModelType = MTYPE_FIXED;

    if (addTasksOnCreate) brain->AddTaskDirectly("PointDefense", 3.0, ai::Task::HIDDEN | ai::Task::PERMANENT);
}

tcGroundObject::~tcGroundObject() 
{
}