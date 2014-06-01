/** 
**  @file tcLauncherState.cpp
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
#include "tcLauncherState.h"
#include "tcLauncher.h"

#include "tcDatabase.h"
#include "tcBallisticDBObject.h"
#include "tcPlatformDBObject.h"
#include "tcLauncherDBObject.h"
#include "tcMissileDBObject.h"
#include "tcTorpedoDBObject.h"

#include "tcRadar.h"
#include "tcOpticalSensor.h"
#include "tcSimState.h"
#include <iostream>
#include "common/tcObjStream.h"
#include "tcGameStream.h"
#include "Game.h"
 
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

tcDatabase* tcLauncherState::mpDatabase = 0;
tcSimState* tcLauncherState::simState = 0;



/**
 * @param anKey, key of launcher database object in database
 * @param azimuth_rad mount angle of (fixed) launcher in radians relative to bow/nose
 * @param displayName name to display in GUI controls, e.g. "Tube 1"
 */
void tcLauncherState::AddFullLauncher(long anKey, float azimuth_rad, float elevation_rad, float fov_deg, 
                                      const std::string& displayName, bool isReloadable)
{
    wxASSERT(mpDatabase);

    tcLauncherDBObject* ldata = dynamic_cast<tcLauncherDBObject*>(mpDatabase->GetObject(anKey));
    if (ldata == 0) 
    {
        fprintf(stderr, "Error - tcLauncherState::AddFullLauncher - Not found in db (%d)\n",
			anKey);
        return;
    }
    
    if (mnCount >= tcPlatformDBObject::MAXLAUNCHERS) 
    {
        fprintf(stderr, "Error - tcLauncherState::AddFullLauncher - full\n");
        return;
    }

    // add new launcher
    wxASSERT(parent);
    tcLauncher* new_launcher = new tcLauncher(ldata, parent);

    new_launcher->pointingAngle = azimuth_rad;
	new_launcher->mountPointingAngle = azimuth_rad;
	new_launcher->pointingElevation = elevation_rad;
    new_launcher->SetFOV(fov_deg);
    new_launcher->displayName = displayName;
    new_launcher->isReloadable = isReloadable;

    // hack to get flares and chaff mix on default
    if (((mnCount % 2) == 1) && (ldata->mzClass == "CM Ejector"))
    {
        wxString childClass(ldata->GetConfigurationClass(1).c_str());
        if ((childClass.Find('?') == wxNOT_FOUND) && (childClass.Find('*') == wxNOT_FOUND))
        {
            new_launcher->SetChildClass(childClass.ToStdString());
            new_launcher->SetChildQuantity(ldata->GetConfigurationCapacity(1));
        }
    }

    wxASSERT((new_launcher->mpChildDBObj != 0) || (ldata->mzClass == "Test Launcher"));
    

    launchers.push_back(new_launcher);
    mnCount = (int)launchers.size();
}

/**
* @return approximate intercept time for target track
* For missiles this is assumes 600 kts velocity for now.
* For guns the range and speed are estimated using ballistics.
*/
float tcLauncherState::EstimateInterceptTimeForLauncher(unsigned nLauncher, tcTrack& track)
{
	tcLauncher* launcher = GetLauncher(nLauncher);
	if (!launcher)
	{
		fprintf(stderr, "EstimateInterceptTimeForLauncher - bad launcher\n");
		return 0;
	}
	tcDatabaseObject* child = launcher->mpChildDBObj;
	tcKinematics kin = parent->mcKin;
	float heading_rad = 0;
	float tti_s = 0;

	if (tcMissileDBObject* missileInfo = dynamic_cast<tcMissileDBObject*>(child))
	{
		kin.mfSpeed_kts = 600;

		kin.GetInterceptData2D(track, heading_rad, tti_s);

	}
	else if (tcBallisticDBObject* ballInfo = dynamic_cast<tcBallisticDBObject*>(child))
	{
		float targetAlt_m = track.GetOrGuessAltitude();
		float range_km = kin.RangeToKm(track);

		ballInfo->GetGunneryElevation(1000 * range_km, targetAlt_m, tti_s);

		tcKinematics launcherKin(parent->mcKin);

	}
	else if (tcTorpedoDBObject* torpedo = dynamic_cast<tcTorpedoDBObject*>(child))
	{
		if (!track.IsBearingOnly() && (track.IsHeadingValid() && track.IsSpeedValid()))
		{
			kin.mfSpeed_kts = 0.5f * torpedo->maxSpeed_kts + 0.5f * launcher->preEnableSpeed_kts;

			kin.GetInterceptData2D(track, heading_rad, tti_s);
		}
	}
	else
	{
		fprintf(stderr, "EstimateInterceptTimeForLauncher - unhandled data type\n");
	}

	return tti_s;
}


tcLauncher* tcLauncherState::GetLauncher(unsigned int nLauncher)
{
    if (nLauncher >= (unsigned int)mnCount) return 0;

    return launchers[nLauncher];
}

const tcLauncher* tcLauncherState::GetLauncher(unsigned nLauncher) const
{
    if ((int)nLauncher >= mnCount) return 0;

    return launchers[nLauncher];
}

std::string tcLauncherState::GetLauncherChildClass(unsigned nLauncher) const
{
    wxASSERT((int)nLauncher < mnCount);

    return launchers[nLauncher]->GetChildClassName();
}

/**
* @return number of launchers
*/
unsigned int tcLauncherState::GetLauncherCount() const
{
    return (mnCount >= 0) ? (unsigned int)mnCount : 0;
}


int tcLauncherState::GetLauncherQuantity(unsigned anLauncher) const
{
    if (anLauncher > launchers.size()) {return -1;}
    return launchers[anLauncher]->mnUncommitted;
}


/**
 * @return LAUNCHER_READY if launcher is ready to launch. Launch readiness
 * @return conditions depend on meLaunchMode for the launcher.
 * @return Otherwise return error code
 * @see teWeaponLaunchMode
 * @see tcLauncherState::teLauncherStatus
 * This method needs to be separated into smaller pieces.
 */
int tcLauncherState::GetLauncherStatus(unsigned nLauncher)
{
    using namespace database;

    if (nLauncher > launchers.size()) 
    {
        std::cerr << "Bad launcher index" << std::endl;
        return tcLauncher::BAD_LAUNCHER;
    }
    tcLauncher* ldata = launchers[nLauncher];
    wxASSERT(ldata);

    return ldata->GetLauncherStatus();
}

bool tcLauncherState::IsDatumLaunch(unsigned anLauncher) 
{
    if (anLauncher > launchers.size()) {return false;}
    return launchers[anLauncher]->meLaunchMode == DATUM_ONLY;
}

bool tcLauncherState::IsSeekerLaunch(unsigned anLauncher) 
{
    if (anLauncher > launchers.size()) {return false;}
    return launchers[anLauncher]->meLaunchMode == SEEKER_TRACK;
}

/**
* sets key to database id of object to launch, otherwise NULL_INDEX
* nLauncher is set to launcher idx of launching launcher
* This only handles one launch per call (not efficient for simultaneous launches)
*/
void tcLauncherState::Launch(long& key, unsigned& nLauncher) 
{
    for (int n=0; n<mnCount; n++) 
    {
        tcLauncher* pLauncher = launchers[n];

        if ((pLauncher->mbActive)&&((int)pLauncher->mnCurrent > pLauncher->mnUncommitted))
        {
            bool bLaunch = (pLauncher->mnCurrent > 0)&&(pLauncher->mfTimeToReady <= 0);
            if (bLaunch)
            {
                int statusCode = GetLauncherStatus(n);

                if (statusCode == tcLauncher::LAUNCHER_READY)
                {
                    pLauncher->mnCurrent--;
                    key = pLauncher->mnChildDBKey;
                    nLauncher = n;
					pLauncher->mfTimeToReady = pLauncher->GetCycleTime(); 

                    if (pLauncher->mnCurrent > 0)
                    {
                        if ((pLauncher->mnUncommitted == pLauncher->mnCurrent) && (pLauncher->AutoLaunchAgain()))
                        {
                            pLauncher->mnUncommitted--; // queue another launch
                            pLauncher->repeatShots--;
                        }
                    }
                    else // (pLauncher->mnCurrent == 0)
                    {
                        pLauncher->QueueAutoReload();
                        // moved reload AFTER child is launched to avoid screwing up datum, etc. 
                        // pLauncher->Reload(); 
                    }
                    return;
                }
                else
                {
                    pLauncher->mnUncommitted = pLauncher->mnCurrent; // reset
                }

            }
        }
        else
        {
        }
    }
    key = NULL_INDEX;
    nLauncher = 0;
}


/**
* @param nLauncher launcher index
* @param sesnor pointer to tcRadar or tcOpticalSensor object that acts as fire control sensor
* @param sensorIdx index of sensor object on parent platform
*/
void tcLauncherState::SetFireControlSensor(unsigned nLauncher, tcSensorState* sensor, unsigned sensorIdx)
{
    wxASSERT(sensor);

	tcRadar* radar = dynamic_cast<tcRadar*>(sensor);
    tcOpticalSensor* optical = dynamic_cast<tcOpticalSensor*>(sensor);

	if ((radar == 0) && (optical == 0))
	{
		fprintf(stderr, "tcLauncherState::SetFireControlSensor - Only radar and laser fire control supported\n");
		return;
	}

    if (nLauncher > launchers.size()) {return;}
    launchers[nLauncher]->fireControlSensor = sensor;
    launchers[nLauncher]->fireControlSensorIdx = sensorIdx;

    // Launchers with fireControlSensor must have a FC track to launch
    // SEEKER_TRACK already requires a fire control track (and a seeker track) so do not change
    // added DATUM_ONLY too so that dumb bombs don't require laser designator (kind of a mess!)
    if ((launchers[nLauncher]->meLaunchMode != SEEKER_TRACK) && (launchers[nLauncher]->meLaunchMode != DATUM_ONLY))
    {
        launchers[nLauncher]->meLaunchMode = FC_TRACK; 
    }
}



/**
* If launcher is ready, decrement mnUncommitted of nLauncher by quantity.
* This method does not support targeting multiple targets.
* @return tcLauncherState::teLauncherStatus error code, LAUNCHER_READY = 0 for success
*/
int tcLauncherState::SetLaunch(int nLauncher, int quantity)
{   
    int statusCode;

    tcLauncher* pLauncher = launchers[nLauncher];
    pLauncher->ActivateFireControl();

    statusCode = GetLauncherStatus(nLauncher);

    if (statusCode != tcLauncher::LAUNCHER_READY) 
    {
        return statusCode;
    }

    pLauncher->mnUncommitted -= quantity;
    if (pLauncher->mnUncommitted < 0) 
    {
        pLauncher->mnUncommitted = 0; // don't set new cmd here since this is an error case
#ifdef _DEBUG
        fprintf(stderr, "Warning - tcLauncherState::SetLaunch - request exceeds capacity\n");
#endif
    }
    else
    {
        commandObj.SetNewCommand(GetLauncherFlag(nLauncher)); 
    }

    pLauncher->SetRepeatShotsForType();

    return statusCode;
}

/**
* @return true if success
*/
bool tcLauncherState::SetLauncherDatum(unsigned nLauncher, 
									   double lon_rad, double lat_rad, float alt_m)
{
    size_t nLaunchers = launchers.size();
    if (nLauncher > nLaunchers)     
    {
        std::cerr << "Bad launcher index" << std::endl;
        return false;
    }

    bool nullTarget = (lon_rad == 0) && (lat_rad == 0) && (alt_m == 0);

	// do not set datum if not in range of launcher (only check for guns for now)
	if (!nullTarget)
    {
        if (tcBallisticDBObject* ballDB = dynamic_cast<tcBallisticDBObject*>
            (launchers[nLauncher]->mpChildDBObj))
        {
            float maxRange_km = ballDB->GetMaxLevelGunRangeKm();
            
            if (maxRange_km <= 0)
            {
                maxRange_km = 20.0f; // hack for non-guns for now
                wxASSERT(false);
            }

            if (parent->mcKin.RangeToKm(lon_rad, lat_rad) > maxRange_km)
            {
                /*if (!tcSimState::Get()->IsMultiplayerServer())
                {
                    wxString msg = wxString::Format("%s gun out of range (%.1f km)",
                        parent->GetName(), maxRange_km);
                    tcGame::DisplayMessage(msg.c_str());
                }*/
                return false;
            }
        }
    }


    launchers[nLauncher]->SetDatum(lon_rad, lat_rad, alt_m);
    
    commandObj.SetNewCommand(GetLauncherFlag(nLauncher)); 
    
    return true;
}

/**
* @return true if success
*/
bool tcLauncherState::SetLauncherTarget(unsigned nLauncher, long targetID)
{
    size_t nLaunchers = launchers.size();
    if (nLauncher > nLaunchers)
    {
        std::cerr << "Bad launcher index" << std::endl;
        return false;
    }

    tcLauncher* launcher = launchers[nLauncher];
    launcher->mnTargetID = targetID;
    launcher->msDatum.Set(0, 0, 0); // clear datum
    launcher->ClearPendingLaunch();

    commandObj.SetNewCommand(GetLauncherFlag(nLauncher)); 

    return true;
}

/**
* Converts launcher status code into string.
*/
std::string tcLauncherState::TranslateLauncherStatus(int status)
{
    return tcLauncher::TranslateStatus(status);
}

/**
*
*/
tcCommandStream& tcLauncherState::operator<<(tcCommandStream& stream)
{
    for (int n = 0; n < mnCount; n++)
    {
		*launchers[n] << stream;
    }

    return stream;
}

/**
* Save launcher state to command stream
*/
tcCommandStream& tcLauncherState::operator>>(tcCommandStream& stream)
{
    for(int n = 0; n < mnCount; n++)
    {
        *launchers[n] >> stream;
    }

    return stream;
}




/**
* Loads state from update stream
*/
tcUpdateStream& tcLauncherState::operator<<(tcUpdateStream& stream)
{
    for(int n = 0; n < mnCount; n++)
    {
        tcLauncher& ldata = *launchers[n];

        int oldStatus = ldata.GetLauncherStatus();

        ldata << stream;

        int launcherStatus = ldata.GetLauncherStatus();

        if ((launcherStatus != 0) && (launcherStatus != oldStatus) && 
            (ldata.mnUncommitted < ldata.mnCurrent))
        {
            ldata.ClearPendingLaunch();
            // set the new command flag to allow the launch request to be cleared
            commandObj.SetNewCommand(GetLauncherFlag(n));  
            tcGame::DisplayMessage(TranslateLauncherStatus(launcherStatus).c_str());
        }
    }

    // update damage
    unsigned short launcherDamage;
    stream >> launcherDamage;
    
    unsigned short damageFlag = 0x0001;
    
    size_t nLaunchers = launchers.size();
    wxASSERT(nLaunchers <= 8*sizeof(launcherDamage));
    for (size_t k=0; k<nLaunchers; k++)
    {
        bool damageState = (launcherDamage & damageFlag) != 0;
        launchers[k]->SetDamaged(damageState);
        
        damageFlag = damageFlag << 1;
    }
    

    return stream;
}


/**
* Saves state to update stream
*/
tcUpdateStream& tcLauncherState::operator>>(tcUpdateStream& stream)
{
    unsigned short launcherDamage = 0;
    
    unsigned short damageFlag = 0x0001;
    
    wxASSERT(mnCount <= 8*sizeof(launcherDamage));

    for(int n = 0; n < mnCount; n++)
    {
        tcLauncher& ldata = *launchers[n];
        ldata >> stream;

		// update damage flag
        if (launchers[n]->IsDamaged())
        {
            launcherDamage |= damageFlag;
        }
        damageFlag = damageFlag << 1;
    }
    
    stream << launcherDamage;

    return stream;
}


/**
* Loads state from game stream
*/
tcGameStream& tcLauncherState::operator<<(tcGameStream& stream)
{
    commandObj << stream;

    for(size_t n=0; n<launchers.size(); n++)
    {
        tcLauncher& ldata = *launchers[n];
        ldata << stream;
    }
    
    return stream;
}


/**
* Saves state to game stream
*/
tcGameStream& tcLauncherState::operator>>(tcGameStream& stream)
{
    commandObj >> stream;

    for(size_t n=0; n<launchers.size(); n++)
    {
        tcLauncher& ldata = *launchers[n];
        ldata >> stream;
    }

    return stream;
}



void tcLauncherState::ClearNewCommand()
{
    commandObj.ClearNewCommand();
}

bool tcLauncherState::HasNewCommand() const
{
    return commandObj.HasNewCommand();
}


/**
 *
 */
void tcLauncherState::Serialize(tcFile& file, bool abLoad) 
{
    if (abLoad) 
    {
        file.Read(&mnCount,sizeof(mnCount));
        for(int i=0;(i<mnCount)&&(i<tcPlatformDBObject::MAXLAUNCHERS);i++) 
        {
            /*
            file.Read(&ma[i],sizeof(tcLauncher));
            // replace serialized pointer
            tcDatabaseObject *pDatabaseObj = mpDatabase->GetObject(ma[i].mnDBKey);
            ma[i].mpLauncherDBObj = dynamic_cast<tcLauncherDBObject*>(pDatabaseObj);
            ma[i].mpChildDBObj = mpDatabase->GetObject(ma[i].mnChildDBKey);
            */
        }
    }
    else 
    {
        /*
        file.Write(&mnCount,sizeof(mnCount));
        for(int i=0;(i<mnCount)&&(i<tcPlatformDBObject::MAXLAUNCHERS);i++) 
        {
            file.Write(&ma[i],sizeof(tcLauncher));
        }
        */
    }
}

/**
 *
 */
std::string tcLauncherState::GetLaunchMode(unsigned anLauncher) 
{
    std::string s;
    if (anLauncher > launchers.size())
    {
        s = "err";
        return s;
    }
    teWeaponLaunchMode lm = launchers[anLauncher]->meLaunchMode;
    if (lm == DATUM_ONLY) 
    {
        s = "Datum";
    }
    else if (lm == SEEKER_TRACK) 
    {
        s = "Seeker";
    }
    else 
    {
        s = "Unknown";
    }
    return s;
}

/**
* update launcher state (reload time) 
*/
void tcLauncherState::Update(float dt_s) 
{
    for(int n=0; n<mnCount; n++) 
    {
        tcLauncher* launcher = launchers[n];

		if (simState->IsMultiplayerServer())
		{
            launcher->UpdateStatus();
        }

        if ((launcher->mbActive) && (launcher->mfTimeToReady > 0))
        {
            launcher->mfTimeToReady -= dt_s;
        }
    }
}


/**
 *
 */
tcLauncherState::tcLauncherState() 
:   mnCount(0),
    parent(0)
{
}

tcLauncherState::tcLauncherState(tcPlatformObject* parentObj)
:   parent(parentObj),
    mnCount(0)
{
}

/**
 *
 */
tcLauncherState::tcLauncherState(tcLauncherState& lstate)
:   parent(0)
{
    for(unsigned i=0;i<lstate.launchers.size();i++) 
    {
        launchers.push_back(lstate.launchers[i]);
    }
    mnCount = (int)launchers.size();
}

/**
 *
 */
tcLauncherState::~tcLauncherState() 
{
    for (size_t n=0; n<launchers.size(); n++)
    {
        delete launchers[n];
    }
    
}
