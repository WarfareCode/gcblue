/**  
**  @file tcWeaponTester.cpp
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
#endif

#include "tcWeaponTester.h"
#include "tcSimState.h"
#include "tcGameObject.h"
#include "tcPlatformObject.h"
#include "tcDatabase.h"
#include "tcDatabaseObject.h"
#include "tcPlatformDBObject.h"
#include "tcWeaponDBObject.h"
#include "tcBallisticDBObject.h"
#include "tcSensorDBObject.h"
#include "tcSensorState.h"
#include "tcLauncher.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


tcWeaponTester* tcWeaponTester::Get()
{
    static tcWeaponTester instance;

    return &instance;
}

tcGameObject* tcWeaponTester::GetPlatform()
{
    return ghost;
}

void tcWeaponTester::InitializePlatform()
{    
    if (ghost != 0)
    {
        delete ghost;
    }

    tcPlatformDBObject* ghostData = dynamic_cast<tcPlatformDBObject*>(tcDatabase::Get()->GetObject("F-16C"));
    ghost = new tcPlatformObject(ghostData);
    ghost->mnID = -99; // hack, use this ID as code to simstate to return weapontester platform (debug build only)

	tcSensorDBObject* sensorData = dynamic_cast<tcSensorDBObject*>(
		tcDatabase::Get()->GetObject("Test Radar"));

	if (sensorData == 0)
	{
		fprintf(stderr, "Error - tcWeaponTest::InitializePlatform() - Test Radar not found in database\n");
		wxASSERT(false);
		return;
	}

	tcSensorState* sensor = sensorData->CreateSensor(ghost); // factory method
	wxASSERT(sensor);

	sensor->mfSensorHeight_m = 20.0f; //< guess sensor height is 80% of zmax
	sensor->SetMountAz(0);
    sensor->SetActive(true);
	ghost->sensorState.push_back(sensor);

    tcLauncher* launcher = ghost->GetLauncher(0);
    if (launcher == 0)
    {
        wxASSERT(false);
        return;
    }
    ghost->mcLauncherState.SetFireControlSensor(0, sensor, ghost->sensorState.size()-1); // use last (Test) sensor for fire control

    ghost->SetAlliance(2);


}

void tcWeaponTester::SetLaunchAltitude_m(float val)
{
    launchAltitude_m = val;
}

void tcWeaponTester::SetLaunchInterval(float t)
{
    launchInterval_s = t;
}

void tcWeaponTester::SetLaunchRange_km(float val)
{
    launchRange_km = val;
}

void tcWeaponTester::SetQuantity(unsigned int n)
{
    quantity = n;
}

void tcWeaponTester::SetTarget(const std::string& s)
{
    targetName = s;
    
    lastUpdate_s = 0;
    lastLaunch_s = 0;
}

void tcWeaponTester::SetWeapon(const std::string& s)
{
    weaponClass = s;

    lastUpdate_s = 0;
    lastLaunch_s = 0;
}

void tcWeaponTester::Update()
{
    tcSimState* simState = tcSimState::Get();
    double t = simState->GetTime();
    if ((t - lastUpdate_s) < 0.5) return;
    lastUpdate_s = t;

    if ((quantity == 0) || (targetName.size() == 0) || (weaponClass.size() == 0)) return;

    if ((t - lastLaunch_s) < launchInterval_s) return;

    tcGameObject* target = simState->GetObjectByName(targetName);
    tcWeaponDBObject* weaponData = dynamic_cast<tcWeaponDBObject*>(tcDatabase::Get()->GetObject(weaponClass));
    if ((target == 0) || (weaponData == 0)) return;

    float launchBearing_rad = C_PI*randfc(2.0f);

    GeoPoint launchPoint;
    target->mcKin.SetRelativeGeo(launchPoint, launchBearing_rad, launchRange_km);
    ghost->mcKin.mfLon_rad = launchPoint.mfLon_rad;
    ghost->mcKin.mfLat_rad = launchPoint.mfLat_rad;
    ghost->mcKin.mfAlt_m = launchAltitude_m;
    ghost->mcKin.mfHeading_rad = ghost->mcKin.HeadingToRad(target->mcKin);
    ghost->mcKin.mfPitch_rad = 0;
    ghost->mcKin.mfRoll_rad = 0;
    ghost->mcKin.mfSpeed_kts = 300;
    ghost->mfStatusTime = t;

    // for dumb gravity bomb, just drop with no horizontal velocity
    if (tcBallisticDBObject* ballistic = dynamic_cast<tcBallisticDBObject*>(weaponData))
    {
        if (ballistic->IsGravityBomb())
        {
            ghost->mcKin.mfSpeed_kts = 0;
        }
    }

    tcLauncher* launcher = ghost->GetLauncher(0);
    if (launcher == 0)
    {
        wxASSERT(false);
        return;
    }

    launcher->msDatum.mfLat_rad = target->mcKin.mfLat_rad;
    launcher->msDatum.mfLon_rad = target->mcKin.mfLon_rad;
    launcher->msDatum.mfAlt_m = target->mcKin.mfAlt_m;

    launcher->mnTargetID = target->mnID;

    simState->AddLaunchedPlatform(weaponData->mnKey, ghost, 0); // always use launcher 0
    quantity--;

    lastLaunch_s = t;

}






tcWeaponTester::tcWeaponTester()
: targetName(""),
  weaponClass(""),
  quantity(1),
  launchInterval_s(1.0f),
  launchRange_km(5.0f),
  launchAltitude_m(0),
  ghost(0),
  lastLaunch_s(0),
  lastUpdate_s(0)
{
    InitializePlatform();

//#ifdef _DEBUG
//    GaussianRandom::Get()->WriteTableToFile("log/randn.txt");
//#endif
}

tcWeaponTester::~tcWeaponTester()
{
    if (ghost != 0)
    {
        delete ghost;
        ghost = 0;
    }
}