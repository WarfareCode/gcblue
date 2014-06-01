/** 
**  @file tcLauncher.cpp
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
#endif // WX_PRECOMP

#include "tcLauncher.h"
#include "tcDatabase.h"
#include "tcBallisticDBObject.h"
#include "tcFuelTankDBObject.h"
#include "tcPlatformDBObject.h"
#include "tcLauncherDBObject.h"
#include "tcMissileDBObject.h"
#include "tcSonarDBObject.h"
#include "tcTorpedoDBObject.h"
#include "tcCounterMeasureDBObject.h"
#include "tcPlatformObject.h"
#include "tcRadar.h"
#include "tcOpticalSensor.h"
#include "tcSimState.h"
#include "tcGoalTracker.h"
#include <iostream>
#include "common/tcObjStream.h"
#include "tcGameStream.h"
#include "tcGameObject.h"
#include "tcFloatCompressor.h"
#include "tcStores.h"
#include "tcStoresDBObject.h"
#include "tcGroundObject.h"

#include "nsNav.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using std::max;
using std::min;

tcSimState* tcLauncher::simState = 0;

void tcLauncher::AttachSimState(tcSimState* ss)
{
    simState = ss;
}


/**
*
*/
tcCreateStream& tcLauncher::operator<<(tcCreateStream& stream)
{
    stream >> mnCurrent;

    if (mnUncommitted > mnCurrent) mnUncommitted = mnCurrent;

	stream >> mnChildDBKey;
	if ((mpChildDBObj == 0) || (mpChildDBObj->mnKey != mnChildDBKey))
	{
		mpChildDBObj = tcDatabase::Get()->GetObject(mnChildDBKey);
		InitForNewChild();
	}

    return stream;
}


/**
*
*/
tcCreateStream& tcLauncher::operator>>(tcCreateStream& stream)
{
    stream << mnCurrent;

	stream << mnChildDBKey;

    return stream;
}


/**
* Loads state from update stream
*/
tcUpdateStream& tcLauncher::operator<<(tcUpdateStream& stream)
{
    int oldCurrent = mnCurrent;

    stream >> tcIntervalCompressor(mfTimeToReady, 0.0f, 6500.0f);
    stream >> mnCurrent;

    // update mnUncommited after reload
    if (mnCurrent > oldCurrent)
    {
        mnUncommitted = mnCurrent;
    }
    //stream >> mnUncommitted;

    if (mnUncommitted > mnCurrent) mnUncommitted = mnCurrent;

	stream >> status;
    SetLoadState(status == LAUNCHER_LOADING);

	stream >> mnChildDBKey;
	if ((mpChildDBObj == 0) || (mpChildDBObj->mnKey != mnChildDBKey))
	{
		mpChildDBObj = tcDatabase::Get()->GetObject(mnChildDBKey);
		if (mpChildDBObj)
		{
			InitForNewChild();
		}
	}

    return stream;
}

/**
* Saves state to update stream
*/
tcUpdateStream& tcLauncher::operator>>(tcUpdateStream& stream)
{
    stream << tcIntervalCompressor(mfTimeToReady, 0.0f, 6500.0f);
    stream << mnCurrent;
    //stream << mnUncommitted;
    stream << status;
	stream << mnChildDBKey;


    return stream;
}





/**
*
*/
tcCommandStream& tcLauncher::operator<<(tcCommandStream& stream)
{
    stream >> mnTargetID;
    stream >> mnUncommitted;
    stream >> msDatum.mfAlt_m;
    stream >> msDatum.mfLat_rad;
    stream >> msDatum.mfLon_rad;

	unsigned char useTorpedoParams;
	stream >> useTorpedoParams;
	if (useTorpedoParams != 0)
	{
		stream >> usePassive;
		stream >> preEnableSpeed_kts;
		stream >> runDepth_m;
		stream >> ceiling_m;
		stream >> floor_m;
		stream >> runToEnable_m;
		//fprintf(stdout, "Updating launcher torpedo params (%d/%d)\n", this, parent);
	}

    return stream;
}

/**
*
*/
tcCommandStream& tcLauncher::operator>>(tcCommandStream& stream)
{
    stream << mnTargetID;
    stream << mnUncommitted;
    stream << msDatum.mfAlt_m;
    stream << msDatum.mfLat_rad;
    stream << msDatum.mfLon_rad;

	unsigned char useTorpedoParams = (preEnableSpeed_kts > 0);
	stream << useTorpedoParams;
	if (useTorpedoParams != 0)
	{
		stream << usePassive;
		stream << preEnableSpeed_kts;
		stream << runDepth_m;
		stream << ceiling_m;
		stream << floor_m;
		stream << runToEnable_m;
	}

    return stream;
}


/**
* Loads state from game stream
*/
tcGameStream& tcLauncher::operator<<(tcGameStream& stream)
{
    std::string childClass;
    stream >> childClass;
    SetChildClass(childClass);

    stream >> mbActive;
    stream >> itemWeight_kg;

    stream >> mfTimeToReady;
    stream >> mnCurrent;
    stream >> mnUncommitted;
    stream >> isLoading;
    stream >> capacity;
    stream >> repeatShots;
    
    msDatum << stream;
    stream >> mnTargetID;
    
    int launchMode;
    stream >> launchMode;
    meLaunchMode = (teWeaponLaunchMode)launchMode;

    stream >> mnTargetFlags;
    stream >> pointingAngle;
	stream >> pointingElevation;
    stream >> firingArc_deg;
	stream >> mountPointingAngle;
    stream >> cycleTime_s;
    stream >> isReloadable;

    stream >> usePassive;
    stream >> preEnableSpeed_kts;
    stream >> runDepth_m;
    stream >> ceiling_m;
    stream >> floor_m;
    stream >> runToEnable_m;
    stream >> isDamaged;
	stream >> status;

    return stream;
}

/**
* Saves state to game stream
*/
tcGameStream& tcLauncher::operator>>(tcGameStream& stream)
{
    std::string childClass = (mpChildDBObj != 0) ? (mpChildDBObj->mzClass.c_str()) : "";
    stream << childClass;
    stream << mbActive;
    stream << itemWeight_kg;

    stream << mfTimeToReady;
    stream << mnCurrent;
    stream << mnUncommitted;
    stream << isLoading;
    stream << capacity;
    stream << repeatShots;
    
    msDatum >> stream;
    stream << mnTargetID;
    
    int launchMode = (int)meLaunchMode;
    stream << launchMode;

    stream << mnTargetFlags;
    stream << pointingAngle;
	stream << pointingElevation;
    stream << firingArc_deg;
	stream << mountPointingAngle;
    stream << cycleTime_s;
    stream << isReloadable;

    stream << usePassive;
    stream << preEnableSpeed_kts;
    stream << runDepth_m;
    stream << ceiling_m;
    stream << floor_m;
    stream << runToEnable_m;
    stream << isDamaged;
	stream << status;

    return stream;
}


/**
* If launcher needs fire control for launch and FC sensor is inactive, then
* activate the FC sensor
*/
void tcLauncher::ActivateFireControl()
{
    bool checkForActivate = (fireControlSensor != 0) && (!fireControlSensor->IsActive()) && (mnTargetID != -1) &&
        ((meLaunchMode == FC_TRACK) || (meLaunchMode == SEEKER_TRACK));

    if (!checkForActivate) return;

    if (meLaunchMode == FC_TRACK)   
    {
        fireControlSensor->SetActive(true);
        return;
    }

    wxASSERT(meLaunchMode == SEEKER_TRACK);

    if (tcMissileDBObject* missileDBObj = dynamic_cast<tcMissileDBObject*>(mpChildDBObj))
    {
        /* check fire control state if necessary (this should be able to be handled without
        ** all of this sprawling code) */
        if (missileDBObj->NeedsFireControl())
        {
            fireControlSensor->SetActive(true);
        }
    }
}

/**
* @return true if repeatShots > 0 after updating status
* Added this to support automatically firing again if target still exists in sensor map for naval gun rounds and point defense
* 23OCT2010 -- changed to use repeatShots variable. This function is now called to zero repeatShots if target is lost or destroyed
*/
bool tcLauncher::AutoLaunchAgain()
{
    if (repeatShots == 0) return false;
    if (mnTargetID == -1)
    {
        repeatShots = 0;
        return false;
    }

    const tcAirObject* air = dynamic_cast<const tcAirObject*>(parent);
    if (air != 0)
    {
        wxASSERT(false);
        repeatShots = 0;
        return false; // don't autolaunch for aircraft cannons
    }

    if (tcBallisticDBObject* ballisticData = 
        dynamic_cast<tcBallisticDBObject*>(mpChildDBObj))
    {
        switch (ballisticData->ballisticType)
        {
        case tcBallisticDBObject::GUN_ROUND:
        case tcBallisticDBObject::AUTO_CANNON:
            {
                tcTrack targetTrack;
                if (simState->GetTruthTrack(mnTargetID, targetTrack))
                {
                    if (tcGameObject* obj = simState->GetObject(mnTargetID))
                    {
                        if (obj->GetDamageLevel() >= 1.0f) // cheating here, perfect kill assessment
                        {
                            repeatShots = 0;
                        }
                    }
                }

            }

        default:
            {
            }
        }
    }

    return (repeatShots > 0);

}


/**
* @return true if multiplayer command info in launcher and this launcher match
*/
bool tcLauncher::CommandInfoMatches(const tcLauncher& launcher)
{
    if ((mnTargetID != launcher.mnTargetID) ||
        (mnUncommitted != launcher.mnUncommitted) ||
        (msDatum.mfAlt_m != launcher.msDatum.mfAlt_m) ||
        (msDatum.mfLat_rad != launcher.msDatum.mfLat_rad) ||
        (msDatum.mfLon_rad != launcher.msDatum.mfLon_rad)
        )
    {
        return false;
    }
    else
    {
        return true;
    }
}

/**
* Copies multiplayer command parameters from source launcher to
* this launcher. Could define operator= instead, but this may be
* used for non-multiplayer purposes. Another way might be to derive
* a container class that is only used for these multiplayer functions.
*/
void tcLauncher::CopyCommandInfoFrom(const tcLauncher& launcher)
{
    mnTargetID = launcher.mnTargetID;
    mnUncommitted = launcher.mnUncommitted;
    msDatum.mfAlt_m = launcher.msDatum.mfAlt_m;
    msDatum.mfLat_rad = launcher.msDatum.mfLat_rad;
    msDatum.mfLon_rad = launcher.msDatum.mfLon_rad;
}

void tcLauncher::CancelLoadInProgress()
{
    if (!IsLoading()) return;

    unsigned int opId = 0;
    if (tcStores* stores = FindLoadingStores(opId))
    {
        if (stores->CancelOperation(opId))
        {
            SetLoadState(false);
        }
    }

}

/**
* @return true if UpdateStatus should check that target is within traversal FOV of launcher
* Normally this is for gun rounds
*/
bool tcLauncher::CheckTraversalFOV() const
{
	if ((firingArc_deg <= 0) || (firingArc_deg >= 360.0f)) return false;

	if (tcBallisticDBObject* ballisticData = 
		dynamic_cast<tcBallisticDBObject*>(mpChildDBObj))
	{
		return ((ballisticData->ballisticType == tcBallisticDBObject::GUN_ROUND) ||
			(ballisticData->ballisticType == tcBallisticDBObject::AUTO_CANNON) ||
            (ballisticData->ballisticType == tcBallisticDBObject::ROCKET));
	}
	else
	{
		return false;
	}
}

/**
* Clears pending launch by resetting mnUncommitted
*/
void tcLauncher::ClearPendingLaunch()
{
    mnUncommitted = (int)mnCurrent;
}


/**
* @return time to complete load/unload, or 0 if not involved in stores op
*/
float tcLauncher::GetLoadingTime()
{
    unsigned int opId = 99999;
    if (tcStores* stores = FindLoadingStores(opId))
    {
        if (const tcStores::StoreOperation* op = stores->FindOpById(opId))
        {
            return op->timeToComplete;
        }
        else
        {
            return -111.0f;
        }
        
    }
    else
    {
        return -222.0f;
    }
}

/**
* @return stores associated with load/unload, or 0 if not found or load/unload not in progress
* @param opId set to opId of operation within loading stores
*/
tcStores* tcLauncher::FindLoadingStores(unsigned int& opId)
{
    if (!isLoading) return 0;

    wxASSERT(parent != 0);
    
    unsigned int launcherIdx = 999;
    bool searching = true;
    for (unsigned int n=0; (n<parent->GetLauncherCount())&&(searching); n++)
    {
        if (parent->GetLauncher(n) == this)
        {
            launcherIdx = n;
            searching = false;
        }
    }
    wxASSERT(!searching);
    
    // search parent's stores first
    size_t nStores = parent->GetMagazineCount();
    for (size_t n=0; n<nStores; n++)
    {
        tcStores* stores = parent->GetMagazine(n);
        if (stores->FindLauncherOp(parent, launcherIdx, opId))
        {
            return stores;
        }
    }

    // if parent has parent, search those stores
    if (tcPlatformObject* parentParent = dynamic_cast<tcPlatformObject*>(parent->parent))
    {
        size_t nStores = parentParent->GetMagazineCount();
        for (size_t n=0; n<nStores; n++)
        {
            tcStores* stores = parentParent->GetMagazine(n);
            if (stores->FindLauncherOp(parent, launcherIdx, opId))
            {
                return stores;
            }
        }
    }

    opId = 0;
    return 0;
}

/**
* @return class name of child, or "Empty" if none
*/
const std::string& tcLauncher::GetChildClassName() const
{
    static std::string s;
    if ((mpChildDBObj) && (isLoading || mnCurrent))
    {
        s = mpChildDBObj->mzClass.c_str();
    }
    else
    {
        s = "Empty";
    }
    return s;
}


/**
* @return display class name of child (NATO/ASCC option), or "Empty" if none
*/
const std::string& tcLauncher::GetChildClassDisplayName() const
{
    static std::string s;
    if ((mpChildDBObj) && (isLoading || mnCurrent))
    {
        s = mpChildDBObj->GetDisplayName();
    }
    else
    {
        s = "Empty";
    }
    return s;
}

tcDatabaseObject* tcLauncher::GetChildDatabaseObject() const
{
    return mpChildDBObj;
}

/**
* This version returns a list of all compatible equipment, including matches to
* wildcard expressions
*/
wxArrayString tcLauncher::GetAllCompatibleList()
{
    tcDatabase* database = tcDatabase::Get();
    wxArrayString result;

    size_t nConfigurations = mpLauncherDBObj->GetNumberConfigurations();
    for (size_t k=0; k<nConfigurations; k++)
    {
        wxArrayString result_k = 
            database->WildcardSearch(mpLauncherDBObj->GetConfigurationClass(k).c_str(), "loadout");
        for (size_t n=0; n<result_k.size(); n++)
        {
            result.push_back(result_k[n]);
        }
    }

    return result;
}

/**
* @return true if launcher auto-pointing is valid, for launchers with adjustable travel
* @param az_rad and el_rad are set to point at target or at closest extreme if launcher auto-pointing is available
* @param az_rad is relative to north, el_rad is relative to horizon
*/
bool tcLauncher::GetAutoPointing(float& az_rad, float& el_rad) const
{
    if (firingArc_deg > 0)
    {
        tcGameObject* targetObj = simState->GetObject(mnTargetID);
        if (targetObj != 0)
        {
            float targetRange_m = 1000.0f * parent->RangeTo(*targetObj);
            float targetAltOffset_m = targetObj->mcKin.mfAlt_m - parent->mcKin.mfAlt_m;
            el_rad = atanf(targetAltOffset_m / (targetRange_m + 0.1f));
            el_rad = std::max(std::min(el_rad, C_PIOVER180*60.0f), 0.0f);

            float targetBearing_rad = parent->BearingToRad(*targetObj);
            float targetAngle_rad = targetBearing_rad - parent->mcKin.mfHeading_rad;
            float angleOffset_rad = targetAngle_rad - pointingAngle;
            angleOffset_rad += (float(angleOffset_rad < -C_PI) - float(angleOffset_rad >= C_PI))*C_TWOPI;

            float halfFOV_rad = 0.5f*C_PIOVER180*firingArc_deg;

            if ((firingArc_deg >= 360.0f) || ((angleOffset_rad >= -halfFOV_rad) && (angleOffset_rad <= halfFOV_rad)))
            {
                az_rad = targetBearing_rad;
            }
            else if (angleOffset_rad < -halfFOV_rad)
            {
                az_rad = parent->mcKin.mfHeading_rad + pointingAngle - halfFOV_rad;
            }
            else // (angleOffset_rad > halfFOV_rad)
            {
                az_rad = parent->mcKin.mfHeading_rad + pointingAngle + halfFOV_rad;
            }

            return true;
        }
    }

    az_rad = pointingAngle;
    el_rad = pointingElevation;
    return false;
}

/**
* Automatically adjust pointAngle within traversal sector, if target is present
* Updated method to point missiles to enable seeker track
* @see tcLauncher::GetAutoPointing
*/
void tcLauncher::UpdatePointingAngle()
{
	if (firingArc_deg <= 0) return;

	tcGameObject* targetObj = simState->GetObject(mnTargetID);
	if (targetObj != 0)
	{
		float targetRange_m = 1000.0f * parent->RangeTo(*targetObj);
        float targetAltOffset_m = targetObj->mcKin.mfAlt_m - parent->mcKin.mfAlt_m;
        float el_rad = atanf(targetAltOffset_m / (targetRange_m + 0.1f));
        el_rad = std::max(std::min(el_rad, C_PIOVER180*60.0f), 0.0f);
		pointingElevation = el_rad;

		float targetBearing_rad = parent->BearingToRad(*targetObj);
		float targetAngle_rad = targetBearing_rad - parent->mcKin.mfHeading_rad; // relative angle from platform nose
		float angleOffset_rad = targetAngle_rad - mountPointingAngle; // relative angle from mount traversal center
		angleOffset_rad += (float(angleOffset_rad < -C_PI) - float(angleOffset_rad >= C_PI))*C_TWOPI;

		float halfFOV_rad = 0.5f*C_PIOVER180*firingArc_deg;

		if ((firingArc_deg >= 360.0f) || ((angleOffset_rad >= -halfFOV_rad) && (angleOffset_rad <= halfFOV_rad)))
		{
			pointingAngle = mountPointingAngle + angleOffset_rad;
		}
		else if (angleOffset_rad < -halfFOV_rad)
		{
			pointingAngle = mountPointingAngle - halfFOV_rad;
		}
		else // (angleOffset_rad > halfFOV_rad)
		{
			pointingAngle = mountPointingAngle + halfFOV_rad;
		}

	}

}


/**
* This can be a substitute for IsItemCompatible by testing != 0
* @see IsItemCompatible
*/
unsigned short tcLauncher::GetCapacityForItem(const std::string& item) const
{
    return mpLauncherDBObj->GetCapacityForItem(item);
}

/**
* This can be a substitute for IsItemCompatible by testing != 0
* @see IsItemCompatible
*/
unsigned short tcLauncher::GetCapacityForItem(const std::string& item, float& loadTime_s, float& cycleTime_s) const
{
    return mpLauncherDBObj->GetCapacityForItem(item, loadTime_s, cycleTime_s);
}

/**
* @return number of compatible items for this launcher
*/
unsigned int tcLauncher::GetCompatibleCount() const
{
    wxASSERT(mpLauncherDBObj);
    return mpLauncherDBObj->GetNumberConfigurations();
}

/**
* Use this to iterate through load options for launcher
* @return class name of item with idx
* @see tcLauncher::GetCompatibleCount
*/
const std::string& tcLauncher::GetCompatibleName(unsigned int idx) const
{
	static std::string s;

    wxASSERT(mpLauncherDBObj);
    if (idx >= mpLauncherDBObj->GetNumberConfigurations())
	{
		s = "";
		return s;
	}
	else
	{
		return mpLauncherDBObj->GetConfigurationClass(idx);
	}
}

/**
* The names of this method and the GetCompatibleCount method are confusing,
* should be renamed.
* @see tcLauncher::GetCompatibleCount
* @return quantity of configuration <idx> that can be loaded into launcher
*/
unsigned int tcLauncher::GetCompatibleQuantity(unsigned int idx) const
{
	if (idx >= mpLauncherDBObj->GetNumberConfigurations())
	{
		return 0;
	}
	else
	{
		return mpLauncherDBObj->GetConfigurationCapacity(idx);
	}
}

/**
* Accessor for cycle time parameter
* Changed 13JUN2009 to use cycleTime_s from launcher_configuration table
* @return cycle time for launcher in seconds
*/
float tcLauncher::GetCycleTime() const
{
	return cycleTime_s;
}

unsigned tcLauncher::GetFireControlTrackCount() const
{
	if (meLaunchMode != FC_TRACK)
	{
		return 0;
	}
	else
	{
		if (fireControlSensor != 0)
		{
			return fireControlSensor->GetFireControlTrackCount();
		}
		else
		{
			wxASSERT(false);
			return 0;
		}

	}
}


unsigned tcLauncher::GetMaxFireControlTracks() const
{
	if ((meLaunchMode != FC_TRACK) || (!fireControlSensor))
	{
		return 999;
	}
	else
	{
		return fireControlSensor->GetMaxFireControlTracks();
	}
}


/**
* @return display name of launcher e.g. "Tube 1"
*/
const std::string& tcLauncher::GetLauncherName() const
{
    return displayName;
}


/**
 * @return LAUNCHER_READY if launcher is ready to launch. Launch readiness
 * @return conditions depend on meLaunchMode for the launcher.
 * @return Otherwise return error code
 * @see teWeaponLaunchMode
 * @see tcLauncherState::teLauncherStatus
 * This method needs to be separated into smaller pieces.
 */
int tcLauncher::GetLauncherStatus()
{
	if (!parent->IsClientMode())
	{
		UpdateStatus();
	}
	return (int)status;
}

tcGameObject* tcLauncher::GetParent() const
{
	return parent;
}

/**
* @return pointing elevation in radians
*/
float tcLauncher::GetPointingElevation() const
{
	return pointingElevation;
}

/**
* @return sector center in radians over which target can be engaged
*/
float tcLauncher::GetSectorCenter() const
{
    if (tcBallisticDBObject* ball = dynamic_cast<tcBallisticDBObject*>(mpChildDBObj))
    {
        return pointingAngle;
    }

    if (fireControlSensor)
    {
        return fireControlSensor->mountAz_rad;
    }
    else
    {
        return pointingAngle;
    }
}

/**
* @return sector width in radians over which target can be engaged
*/
float tcLauncher::GetSectorWidth() const
{
    // if ballistic then use firing arc of launcher
    if (tcBallisticDBObject* ball = dynamic_cast<tcBallisticDBObject*>(mpChildDBObj))
    {
        return C_PIOVER180 * firingArc_deg; // set when launcher is created, from platform_launcher table, (updated with each child for override 26JUN2011)
    }

    if (fireControlSensor)
    {
        float fcFov = C_PIOVER180 * fireControlSensor->mpDBObj->mfFieldOfView_deg;

        if ((meLaunchMode == SEEKER_TRACK) && (!IsAutoPoint()))
        {
            if (tcMissileDBObject* missile = dynamic_cast<tcMissileDBObject*>(mpChildDBObj))
            {
                return missile->GetSeekerFOV();
            }

            return min(0.524f, fcFov); // guess 30 deg for FOV, TODO: calculate true number
        }
        else
        {
            return fcFov;
        }
    }
    else
    {
        return C_TWOPI;
    }
}

unsigned char tcLauncher::GetStatus() const
{
	return status;
}

/**
* @return unit weight in kg of item type loaded
*/
float tcLauncher::GetItemWeight() const
{
    return isLoading ? 0: itemWeight_kg;
}

/**
* @return current weight in kg of loaded items
*/
float tcLauncher::GetWeight() const
{
    return isLoading ? 0: (itemWeight_kg * float(mnCurrent));
}


/**
* autopoint launchers will automatically point to target before launch
* @return true if launcher is auto-pointable 
*/
bool tcLauncher::IsAutoPoint() const
{
    return firingArc_deg > 0;
}

bool tcLauncher::IsDamaged() const
{
    return isDamaged;
}

/**
* @return true if item is compatible with launcher (can be loaded)
*/
bool tcLauncher::IsItemCompatible(const std::string& item) const
{
    unsigned short capacity = mpLauncherDBObj->GetCapacityForItem(item);

    return capacity != 0;
}

bool tcLauncher::IsEffective(const tcSensorMapTrack& track) const
{
	unsigned int targetClassification = track.mnClassification;

	if ((mnCurrent == 0)||(isExternalFuelTank)) return false;

	if ((targetClassification & PTYPE_SURFACE)&&(mnTargetFlags & SURFACE_TARGET)) 
	{
		return true;
	}
	else if ((targetClassification & PTYPE_AIR)&&(mnTargetFlags & AIR_TARGET)) 
	{
		return true;
	}
	else if ((targetClassification & PTYPE_MISSILE)&&(mnTargetFlags & MISSILE_TARGET))
	{
		return true;
	}
	else if ((targetClassification & PTYPE_GROUND)&&(mnTargetFlags & LAND_TARGET))
	{
		return true;
	}
	else if ((targetClassification == PTYPE_SUBMARINE))
	{
		const float subOnSurfaceAltitude_m = -3.0f;
		return ((mnTargetFlags & SUBSURFACE_TARGET) != 0) || 
			((mnTargetFlags & SURFACE_TARGET) && (track.mfAlt_m > subOnSurfaceAltitude_m) && (track.IsAltitudeValid()));
		//return true;
	}

	return false;
}

bool tcLauncher::IsEffective(unsigned int targetClassification) const
{
	if ((mnCurrent == 0)||(isExternalFuelTank)) return false;

	if ((targetClassification & PTYPE_SURFACE)&&(mnTargetFlags & SURFACE_TARGET)) 
	{
		return true;
	}
	else if ((targetClassification & PTYPE_AIR)&&(mnTargetFlags & AIR_TARGET)) 
	{
		return true;
	}
	else if ((targetClassification & PTYPE_MISSILE)&&(mnTargetFlags & MISSILE_TARGET))
	{
		return true;
	}
	else if ((targetClassification & PTYPE_GROUND)&&(mnTargetFlags & LAND_TARGET))
	{
		return true;
	}
	else if ((targetClassification == PTYPE_SUBMARINE) && (mnTargetFlags & SUBSURFACE_TARGET))
	{
		return true;
	}

	return false;
}


bool tcLauncher::IsLoading() const
{
	return isLoading;
}


bool tcLauncher::IsLoadedNuclear() const
{
    const tcWeaponDBObject* weaponData = dynamic_cast<const tcWeaponDBObject*>(mpChildDBObj);

    if ((!isLoading) && (mnCurrent > 0) && (weaponData != 0)) 
    {
        return weaponData->IsNuclear();
    }
    else
    {
        return false;
    }
    
}

void tcLauncher::QueueAutoReload()
{
    if ((mnCurrent == 0) && (mpChildDBObj != 0))
    {
        status = LAUNCHER_EMPTY_AUTORELOAD;
    }
    else
    {
        wxASSERT(false); // bad queue state
    }
}

/**
* Automatically reload launcher if reload is available in magazines
* @return true if reload started, false otherwise
*/
bool tcLauncher::Reload()
{
    wxASSERT(parent != 0);
    tcPlatformObject* platform = parent;
    if (platform == 0) return false;

    unsigned int launcherIdx = 999;
    bool searching = true;
    for (unsigned int n=0; (n<platform->GetLauncherCount())&&(searching); n++)
    {
        if (platform->GetLauncher(n) == this)
        {
            launcherIdx = n;
            searching = false;
        }
    }
    wxASSERT(!searching);

    wxASSERT(mpChildDBObj != 0);

    std::string childClass(mpChildDBObj->mzClass.c_str());
    
    tcStores* fastestMag = 0;
    float fastestTime_s = 9e9f;

    size_t nMagazines = platform->GetMagazineCount();
    for (size_t n=0; n<nMagazines; n++)
    {
        tcStores* mag = platform->GetMagazine(n);
        std::string matchingItem;
        size_t nAvailable = mag->CurrentItemQuantity(childClass, matchingItem);
        if (nAvailable > 0)
        {
            float moveTime_s = mag->GetDatabaseObject()->moveTime;
            if (moveTime_s < fastestTime_s)
            {
                fastestMag = mag;
                fastestTime_s = moveTime_s;
            }         
        }
    }
    // could also presort mags by moveTime, since moveTime never changes
    if (fastestMag != 0)
    {
        fastestMag->LoadLauncher(launcherIdx, childClass);
        return true;
    }

    // out of last loadout, try other loadouts
    std::string fastestMatchingItem;
    unsigned int nConfigurations = mpLauncherDBObj->GetNumberConfigurations();
    for (unsigned int m=0; m<nConfigurations; m++)
    {
        std::string item = mpLauncherDBObj->GetConfigurationClass(m);
        for (size_t n=0; n<nMagazines; n++)
        {
            tcStores* mag = platform->GetMagazine(n);
            std::string matchingItem;
            size_t nAvailable = mag->CurrentItemQuantity(item, matchingItem);
            if (nAvailable > 0)
            {
                float moveTime_s = mag->GetDatabaseObject()->moveTime;
                if (moveTime_s < fastestTime_s)
                {
                    fastestMag = mag;
                    fastestTime_s = moveTime_s;
                    fastestMatchingItem = matchingItem;
                }  
            }
        }
        if (fastestMag != 0)
        {
            fastestMag->LoadLauncher(launcherIdx, fastestMatchingItem);
            return true;
        }
    }

    return false;
}

/**
* Call after first shot to automatically set repeatShots count based on weapon type
*/
void tcLauncher::SetRepeatShotsForType()
{
    repeatShots = 0;

    if (mnUncommitted < (mnCurrent - 1))
    {
        return; // if a burst of launches already schedule, don't do repeats
    }

    if (tcBallisticDBObject* ballisticData = dynamic_cast<tcBallisticDBObject*>(mpChildDBObj))
    {                
        bool pointDefense = (typeid(*parent) == typeid(tcSurfaceObject)) ||
                                    (typeid(*parent) == typeid(tcCarrierObject)) ||
                                    (typeid(*parent) == typeid(tcGroundObject));

        switch (ballisticData->ballisticType)
        {
        case tcBallisticDBObject::GUN_ROUND:
            {
                if (tcAirObject* airTarget = dynamic_cast<tcAirObject*>(simState->GetObject(mnTargetID)))
                {
                    repeatShots = pointDefense ? 99 : 4;
                }
                else
                {
                    repeatShots = 4;
                }
            }
            break;
        case tcBallisticDBObject::AUTO_CANNON:
            {
                if (pointDefense)
                {
                    repeatShots = 99;
                }
            }
            break;
        default:
            {
            }
        }
    }

}


/**
* Use to change child class (e.g. while changing loadout via tcStores)
* Use SetChildClass("") to clear previous child for empty launcher
*/
void tcLauncher::SetChildClass(const std::string& childClass, bool ignoreRestrictions)
{
    if (mpChildDBObj && (childClass == mpChildDBObj->mzClass.c_str())) return;

    if ((mpChildDBObj != 0) && (isExternalFuelTank))
    {
        SetChildQuantity(0); // remove fuel tank first to make sure external fuel is adjusted correctly
    }

	if (childClass.size() == 0)
	{
		mnChildDBKey = -1;
		mpChildDBObj = 0;
		mnCurrent = 0;
        isExternalFuelTank = false;
		return;
	}

    mpChildDBObj = tcDatabase::Get()->GetObject(childClass);
    if (mpChildDBObj)
    {
        mnChildDBKey = mpChildDBObj->mnKey;
    }
    else
    {
        mnChildDBKey = -1;
        mpChildDBObj = 0;
		mnCurrent = 0;
        char zBuff[128];

        sprintf(zBuff, "Error - tcLauncher::SetChildClass - "
            "Launcher child not found in database (%s)\n", childClass.c_str());

        fprintf(stderr, zBuff);
        return;
    }

	InitForNewChild(ignoreRestrictions);
}

void tcLauncher::SetFOV(float fov_deg_)
{
	firingArc_deg = fov_deg_;
	if (tcBallisticDBObject* ballisticDBObj = 
		dynamic_cast<tcBallisticDBObject*>(mpChildDBObj))
	{
		if ((ballisticDBObj->IsAutocannon() || ballisticDBObj->IsRocket()) && (firingArc_deg <= 0))
		{
			firingArc_deg = 5.0f;
		}
	}
}


/**
* Call after new child class is selected to initialize launcher params
* for child
*/
void tcLauncher::InitForNewChild(bool ignoreRestrictions)
{
	if (mpChildDBObj == 0) return;

    mbActive = 1;
    mnCurrent = 0;
    mfTimeToReady = 0;
    msDatum.mfLon_rad = 0;
    msDatum.mfLat_rad = 0;
    mnTargetID = -1;
    meLaunchMode = AUTO;
    mnUncommitted = 0;
    repeatShots = 0;
	mnTargetFlags = 0;
	isExternalFuelTank = false;
    itemWeight_kg = mpChildDBObj->weight_kg;

	std::string childClass(mpChildDBObj->mzClass.c_str());
    if (!ignoreRestrictions)
    {
        capacity = GetCapacityForItem(childClass);
    }
    else
    {
        capacity = 999; // test mode
    }

	// find parent launcher index for this launcher
	wxASSERT(parent != 0);
	unsigned int launcherIdx = 999;
    bool searching = true;
    for (unsigned int n=0; (n<parent->GetLauncherCount())&&(searching); n++)
    {
        if (parent->GetLauncher(n) == this)
        {
            launcherIdx = n;
            searching = false;
        }
    }

	// update firing arc for this child, normally this is what's in the platform launcher table, but
	// for ballistic auto cannons and rockets, override 0 value with small sector for easier targeting
	if (launcherIdx < parent->GetLauncherCount())
	{
		SetFOV(parent->mpDBObject->GetLauncherFOV_deg(launcherIdx));
	}

    // set detailed launch mode if missile
    if (tcMissileDBObject* pMissileDBObj = 
        dynamic_cast<tcMissileDBObject*>(mpChildDBObj)) 
    {
        meLaunchMode = pMissileDBObj->GetLaunchMode();
        mnTargetFlags = pMissileDBObj->targetFlags;
    }
    else if (tcTorpedoDBObject* torpDBObj = 
        dynamic_cast<tcTorpedoDBObject*>(mpChildDBObj))
    {
        meLaunchMode = DATUM_ONLY;
        mnTargetFlags = torpDBObj->targetFlags;

        if (tcSonarDBObject* seekerDBObj = torpDBObj->GetSeekerDBObj())
        {
            if (seekerDBObj->isActive) usePassive = false;
            else if (seekerDBObj->isPassive) usePassive = true;
            else usePassive = false;
        }
        else
        {
            fprintf(stderr, "tcLauncher::InitForNewChild - no seeker\n");
        }

        preEnableSpeed_kts = torpDBObj->preEnableSpeed_kts;
        runDepth_m = 0; // zero to use platform depth
        ceiling_m = 0;
        floor_m = torpDBObj->maxDepth_m;
        runToEnable_m = 0; // zero to use launcher waypoint
    }
    else if (tcBallisticDBObject* ballisticDBObj = 
        dynamic_cast<tcBallisticDBObject*>(mpChildDBObj))
    {
        if (ballisticDBObj->IsAutocannon())
        {
            meLaunchMode = TARGET_ONLY;
        }
        else if (ballisticDBObj->mnModelType == MTYPE_LASERGUIDEDBOMB)
        {
            if (ballisticDBObj->sensorClass.size() > 0)
            {
                meLaunchMode = ballisticDBObj->lockOnAfterLaunch ? DATUM_ONLY : SEEKER_TRACK;
            }
            else
            {
                meLaunchMode = DATUM_ONLY;
            }
        }
        else if (ballisticDBObj->IsCMRound())
        {
            meLaunchMode = AUTO;
        }
        else
        {
            meLaunchMode = DATUM_ONLY;
        }
        mnTargetFlags = ballisticDBObj->targetFlags;
    }
	else if (tcFuelTankDBObject* fuelTankDBObj = 
		dynamic_cast<tcFuelTankDBObject*>(mpChildDBObj))
	{
		isExternalFuelTank = true;
	}
    else if (tcCounterMeasureDBObject* cmData = dynamic_cast<tcCounterMeasureDBObject*>(mpChildDBObj))
    {
        if (cmData->subType == "Decoy")
        {
            meLaunchMode = DATUM_ONLY;
        }
        else
        {
            meLaunchMode = AUTO;
        }
    }
    else // sonobuoy or other
    {
        meLaunchMode = mpChildDBObj->GetLaunchMode(); // should all be using this method
    }

    UpdateFireControlSensor();

    int configIdx = mpLauncherDBObj->GetConfigurationIndex(childClass);
    if (configIdx >= 0)
    {
        //firingArc_deg = mpLauncherDBObj->Get; ///< from platform_launcher table

        /// from launcher_configuration table of current loaded child
        cycleTime_s = mpLauncherDBObj->GetConfigurationCycleTime((unsigned int)configIdx);
    }
}

/**
* @return true if child does not require platform guidance after launch
*/
bool tcLauncher::IsChildFireAndForget()
{
    if (tcMissileDBObject* missileData = dynamic_cast<tcMissileDBObject*>(mpChildDBObj)) 
    {
		return missileData->IsFireAndForget();
    }
	else
	{
		return true;
	}
}


/**
* Sets child quantity, up to capacity
*/
void tcLauncher::SetChildQuantity(unsigned int quantity)
{
	short mnPrevious = mnCurrent;

    mnCurrent = quantity;
    if (mnCurrent > (int)capacity)
    {
        mnCurrent = (int)capacity;
    }
    mnUncommitted = mnCurrent;
    mfTimeToReady = 0;
    SetLoadState(false);

	if (isExternalFuelTank)
	{
		if (tcFuelTankDBObject* fuel = dynamic_cast<tcFuelTankDBObject*>(mpChildDBObj))
		{
			tcPlatformObject* platform = (parent);
			if (platform != 0)
			{
				platform->AdjustExternalFuelCapacity(float(mnCurrent-mnPrevious) * fuel->fuelCapacity_kg);
                if (mnCurrent > mnPrevious)
                {
                    platform->fuel_kg = platform->GetFuelCapacity(); // set fuel to max
                }
			}
		}
		else
		{
			fprintf(stderr, "tcLauncher::SetChildQuantity - bad isExternalFuelTank flag\n");
			wxASSERT(false);
		}
	}
}

/**
* Sets damaged state of launcher
*/
void tcLauncher::SetDamaged(bool state)
{
    isDamaged = state;
}

void tcLauncher::SetDatum(double lon_rad, double lat_rad, float alt_m)
{
	msDatum.Set(lon_rad, lat_rad, alt_m);

	// update run to enable for torpedo 
	if (tcTorpedoDBObject* torpedoData = dynamic_cast<tcTorpedoDBObject*>(mpChildDBObj))
	{
		runToEnable_m = 500.0f * parent->mcKin.RangeToKm(lon_rad, lat_rad);
	}
}

/**
* Added so that appropriate commandObj receives new command for multiplayer
*/
void tcLauncher::SetLaunch(unsigned int quantity)
{
	if (tcPlatformObject* platform = (parent))
	{
		// find launcher index
		bool searching = true;
		unsigned int nLaunchers = platform->GetLauncherCount();
		for (unsigned int n=0; (n<nLaunchers) && searching; n++)
		{
			if (platform->GetLauncher(n) == this)
			{
				platform->SetLaunch(n, quantity);
				searching = false;
			}
		}
		if (searching)
		{
			fprintf(stderr, "tcLauncher::SetLaunch - couldn't find launcher in parent\n");
		}
	}
	else
	{
		wxASSERT(false);
	}
}

/**
*
*/
void tcLauncher::SetLoadState(bool state)
{
    isLoading = state;
}

/**
*
*/
void tcLauncher::SetParent(tcPlatformObject *obj) 
{
    parent = obj;
}


/**
* Call when loading a new child
*
* If parent platform has <= 1 fire control sensor, do nothing
* Otherwise check if the alternate fire control sensor is a better match for
* the current launcher loadout, and if so switch to the alternate FC sensor
*/
void tcLauncher::UpdateFireControlSensor()
{
    // updated 11OCT2010 to automatically search for a fire control sensor
    // The two launcher fields, FireControlSensor and FireControlSensor2 are checked first as preferences
    // If FireControlSensor and FireControlSensor2 are empty or not a match, check ALL sensors on platform for a match
    
    fireControlSensor = 0;
    fireControlSensorIdx = 0;

    // *** Determine the fire control requirements of the child. Needs FC if a weapon AND
    //    launch mode is FC_TRACK OR
    //    launch mode is SEEKER_TRACK and is ballistic OR (missile with NeedsFireControl)

    tcWeaponDBObject* weaponData = dynamic_cast<tcWeaponDBObject*>(mpChildDBObj);
    if (weaponData == 0) return; // not a weapon, no fire control required

    tcMissileDBObject* missileData = dynamic_cast<tcMissileDBObject*>(weaponData);
    tcBallisticDBObject* ballisticData = dynamic_cast<tcBallisticDBObject*>(weaponData);

    bool needsFireControl = (meLaunchMode == FC_TRACK) ||
        ((meLaunchMode == SEEKER_TRACK) && ((ballisticData != 0) || ((missileData != 0) && (missileData->NeedsFireControl()))));
    if (!needsFireControl) return;

    // *** Determine whether radar or laser designator is required
    long seekerKey = -1;
    if (missileData != 0)
    {
        seekerKey = missileData->GetSensorKey();
        wxASSERT((seekerKey != -1) || (missileData->maSensorClass.size() == 0));
    }
    else if (ballisticData != 0)
    {
        seekerKey = ballisticData->GetSensorKey();
        wxASSERT((seekerKey != -1) || (ballisticData->sensorClass.size() == 0));
    }

    bool needsRadar = true;
    if (tcOpticalDBObject* opticalData = dynamic_cast<tcOpticalDBObject*>(tcDatabase::Get()->GetObject(seekerKey)))
    {
        needsRadar = !opticalData->isSemiactive;
    }
    
    // *** Search for FireControlSensor and FireControlSensor2 first
    tcPlatformObject* platform = (parent);
    if (platform == 0)
    {
        wxASSERT(false); 
        return;
    }

    // find our launcher idx in platform
    unsigned int nLaunchers = platform->GetLauncherCount();
    bool searching = true;
    int launcherIdx = -1;
    for (unsigned int n=0; (n<nLaunchers)&&(searching); n++)
    {
        if (platform->GetLauncher(n) == this)
        {
            launcherIdx = int(n);
            searching = false;
        }
    }

    if (searching)
    {
        wxASSERT(parent->mfStatusTime == 0); // should only occur when platform created
        return; // couldn't find this launcher
    }

    wxASSERT(launcherIdx >= 0);
    wxASSERT(((int)platform->mpDBObject->launcherFireControl.size() > launcherIdx) &&
             ((int)platform->mpDBObject->launcherFireControl2.size() > launcherIdx));


    std::string fc1(platform->mpDBObject->launcherFireControl[launcherIdx]);
    std::string fc2(platform->mpDBObject->launcherFireControl2[launcherIdx]);

    struct SensorData
    {
        tcSensorState* sensor; // pointer to sensor
        unsigned int idx; // index of this sensor on platform
    };
    std::vector<SensorData> sensorsToSearch;

    static unsigned int messageBoxCount = 0;

    if (fc1.size() > 0)
    {
        SensorData dat;
        dat.sensor = platform->GetSensorMutable(fc1, dat.idx);
        if (dat.sensor != 0)
        {
            sensorsToSearch.push_back(dat);
        }
        else
        {
            wxString msg = wxString::Format("Failed to find FireControlSensor %s on platform %s", fc1.c_str(), platform->mzClass.c_str());
            fprintf(stderr, "%s\n", msg.c_str());
            if (messageBoxCount++ < 8) wxMessageBox(msg);
        }
    }

    if (fc2.size() > 0)
    {
        SensorData dat;
        dat.sensor = platform->GetSensorMutable(fc2, dat.idx);
        if (dat.sensor != 0)
        {
            sensorsToSearch.push_back(dat);
        }
        else
        {
            wxString msg = wxString::Format("Failed to find FireControlSensor2 %s on platform %s", fc2.c_str(), platform->mzClass.c_str());
            fprintf(stderr, "%s\n", msg.c_str());
            if (messageBoxCount++ < 8) wxMessageBox(msg);
        }
    }

    for (unsigned int n=0; n<platform->GetSensorCount(); n++)
    {
        SensorData dat;
        dat.sensor = platform->GetSensorMutable(n);
        dat.idx = n;
        sensorsToSearch.push_back(dat);
    }

    for (size_t n=0; n<sensorsToSearch.size(); n++)
    {
        if (needsRadar)
        {
            if (tcRadar* radar = dynamic_cast<tcRadar*>(sensorsToSearch[n].sensor))
            {
                if (radar->GetMaxFireControlTracks() > 0)
                {
                    fireControlSensor = radar;
                    fireControlSensorIdx = sensorsToSearch[n].idx;
                    //wxMessageBox(wxString::Format("Selected %s radar FC %d for child %s on platform %s",
                    //    fireControlSensor->mpDBObj->mzClass.c_str(), fireControlSensorIdx, mpChildDBObj->mzClass.c_str(), platform->mzClass.c_str()));
                    return; // success
                }
            }
        }
        else
        {
            if (tcOpticalSensor* optical = dynamic_cast<tcOpticalSensor*>(sensorsToSearch[n].sensor))
            {
                if (optical->IsDesignator() && (optical->GetMaxFireControlTracks() > 0))
                {
                    fireControlSensor = optical;
                    fireControlSensorIdx = sensorsToSearch[n].idx;
                   /* wxMessageBox(wxString::Format("Selected %s designator FC %d for child %s on platform %s",
                        fireControlSensor->mpDBObj->mzClass.c_str(), fireControlSensorIdx, mpChildDBObj->mzClass.c_str(), platform->mzClass.c_str()));*/
                    return; // success
                }
            }
        }
    }

    wxString sensorType = needsRadar ? "radar" : "laser designator";
    wxString msg = wxString::Format("Failed to find valid Fire Control Sensor (%s) for platform %s weapon %s, check database", 
        sensorType.c_str(), platform->mzClass.c_str(), weaponData->mzClass.c_str());
    wxMessageBox(msg);
    fprintf(stderr, msg.c_str());

}

/**
* Call after damage to launcher. This assumes all items in launcher are
* destroyed.
*/
void tcLauncher::UpdateScoreForDamage(tcGameObject* damager)
{
    if (!isDamaged) return;

    float cost = 0;
    if (mpChildDBObj)
    {
        cost = float(mnCurrent) * mpChildDBObj->GetCost();
    }

    if (damager != 0)
    {
        tcGoalTracker::Get()->AdjustAllianceScore(damager->GetAlliance(), cost);
    }
    tcGoalTracker::Get()->AdjustAllianceScore(parent->GetAlliance(), -cost);
}

void tcLauncher::UpdateStatus()
{
	using namespace database;

    bool ready1 = (mnCurrent > 0) && (!isLoading) && (mfTimeToReady <= 0) && mbActive && (!isDamaged) && (!isExternalFuelTank);

    if (!ready1)
    {

        if (mnCurrent <= 0)
        {
            if (status != LAUNCHER_EMPTY_AUTORELOAD)
            {
                status = isLoading ? LAUNCHER_LOADING : LAUNCHER_EMPTY;
                // if empty and not loading then clear child class
                if ((mpChildDBObj != 0) && (!isLoading))
                {
                    SetChildClass("");
                }
            }
            else
            {
                status = LAUNCHER_EMPTY;
                Reload(); // try an auto reload
            }

            return;
        }

        if (isLoading)
        {
            status = LAUNCHER_UNLOADING;
            return;
        }

        if (mfTimeToReady > 0)
        {
            status = LAUNCHER_BUSY;
            return;
        } 

        if (!mbActive)
        {
            status = LAUNCHER_INACTIVE;
            return;
        }

        if (isDamaged) 
        {
            status = DAMAGED;
            return;
        }

        if (isExternalFuelTank)
        {
            status = LAUNCHER_BUSY;
            return;
        }
    }

	wxASSERT(simState);
	wxASSERT(parent);

	// limit depth for launching sub-launched missiles
	if (tcMissileDBObject* missile = 
		dynamic_cast<tcMissileDBObject*>(mpChildDBObj))
	{
		/* Check database minLaunchAlt_m to determine if too low/deep or
		** high/shallow for launch */
		if (parent->mcKin.mfAlt_m < missile->minLaunchAlt_m)
		{
			status = (parent->mcKin.mfAlt_m < 0) ? TOO_DEEP : TOO_LOW;
			return;
		}
		else if (parent->mcKin.mfAlt_m > missile->maxLaunchAlt_m)
		{
			status = TOO_HIGH;
			return;
		}
	}
	else if (tcTorpedoDBObject* torpedo =  
		dynamic_cast<tcTorpedoDBObject*>(mpChildDBObj))
	{
		if (-parent->mcKin.mfAlt_m > torpedo->maxDepth_m)
		{
			status = TOO_DEEP;
			return;
		}
	}

	bool hasTarget = (mnTargetID != NULL_INDEX);
    bool hasDatum = (msDatum.mfLat_rad != 0) || (msDatum.mfLon_rad != 0);

	if (meLaunchMode == AUTO)
	{
		status = LAUNCHER_READY;
		return;
	}

    tcGameObject* targetObj = simState->GetObject(mnTargetID);
    bool badTarget = hasTarget && (targetObj == 0);

	// TODO: called here as quick way to add autopoint feature, move to better location
	// apply this check for gun launchers and others that have unguided rounds, if the target isn't within
	// the launcher traversal return OUT_OF_FOV status
	if (CheckTraversalFOV() && (targetObj != 0))
	{
		float targetAngle_rad = parent->BearingToRad(*targetObj) - parent->mcKin.mfHeading_rad;
        float angleOffset_rad = targetAngle_rad - mountPointingAngle;
        angleOffset_rad += (float(angleOffset_rad < -C_PI) - float(angleOffset_rad >= C_PI))*C_TWOPI;
		
        if (fabsf(angleOffset_rad) > (0.5*C_PIOVER180*firingArc_deg))
        {
            status = OUT_OF_FOV;
            return;
        }
	}

	if (meLaunchMode == DATUM_ONLY)   // needs a datum programmed to launch
	{
		if (hasDatum && !badTarget)
		{
			status = LAUNCHER_READY;
		}
		else
		{
			status = NO_DATUM;
            return;
		}

        // for datum_only weapon types, check that target range is between min and max range
        if (tcWeaponDBObject* weaponData = dynamic_cast<tcWeaponDBObject*>(mpChildDBObj))
        {
            GeoPoint current;
            current.Set(parent->mcKin.mfLon_rad, parent->mcKin.mfLat_rad);
            float range_km = C_RADTOKM * nsNav::GCDistance_rad(current, msDatum);
            if (range_km > weaponData->maxRange_km)
            {
                status = OUT_OF_RANGE;
                return;
            }
            else if (range_km < weaponData->minRange_km)
            {
                status = TOO_CLOSE;
                return;
            }
        }

        //// check ROE, disabled this, annoying and feedback to user isn't great, do this at AI script level 7NOV2010
        //tcGoalTracker* goalTracker = tcGoalTracker::Get();
        //if (!goalTracker->IsTargetLegal(parent, msDatum.mfLon_rad, msDatum.mfLat_rad))
        //{
        //    status = ROE_HOLD;
        //    return;
        //}
        return;
	}

	// all modes after here require a target
	if (!hasTarget)
	{
		status = NO_TARGET;
		return;
	}

	tcSensorMapTrack track;
	if (simState->GetTrack(mnTargetID, parent->GetAlliance(), track) == false)
	{
		mnTargetID = -1; // target wasn't found in alliance sensor map
		status = NO_TARGET;
		return;
	}

	// verify that launcher is effective vs target type
	if (!IsEffective(track.mnClassification))
	{
		status = INVALID_TARGET; // or unknown classification?
		return;
	}

    float range_km = parent->mcKin.RangeToKm(track);

    // check for target mode ballistic in range
    if (tcBallisticDBObject* ballisticData = 
		dynamic_cast<tcBallisticDBObject*>(mpChildDBObj))
	{
        if (ballisticData->ballisticType != tcBallisticDBObject::SMART_BOMB)
        {
            if (range_km > ballisticData->GetMaxLevelGunRangeKm())
            {
                status = OUT_OF_RANGE;
                return;
            }
        }
        else
        {
            
            if (range_km > ballisticData->CalculateRangeKm(parent->mcKin.mfAlt_m, C_KTSTOMPS*parent->mcKin.mfSpeed_kts))
            {
                status = OUT_OF_RANGE;
                return;
            }
        }
    }


	// verify that platform is within 2x database maximum range
    // TODO since range isn't a common base class parameter (needs to be in weapondata?)
    // if (tcWeaponDBObject* weaponData = 
	// dynamic_cast<tcWeaponDBObject*>(mpChildDBObj))
	// {
    // }
	

	if ((meLaunchMode == TARGET_ONLY) || (meLaunchMode == AUTO))
	{
		status = LAUNCHER_READY; 		
		return;
	}


	// if running as multiplayer client, seeker track can't be checked so defer checking to server
	if (parent->IsClientMode())
	{
		status = LAUNCHER_READY;
		return;
	}




	// needs a fire control track (launching platform) to launch    
	if (meLaunchMode == FC_TRACK)   
	{
		if (!fireControlSensor)
		{
			status = NO_FIRECONTROL; // database error
			return;
		}

		if (!fireControlSensor->IsTrackAvailable())
		{
			status = FC_BUSY; // no FC tracks available
			return;
		}

		if (targetObj == 0)
		{
			status = NOT_DETECTED_FC; // target doesn't exist
			return;
		}

		float range;
        const bool useRandomDetect = false;
		if (!fireControlSensor->CanDetectTarget(targetObj, range, useRandomDetect))
		{
			status = NOT_DETECTED_FC;
			return;
		}

		if (meLaunchMode == FC_TRACK)
		{
			status = LAUNCHER_READY;
			UpdatePointingAngle();
			return;
		}
	}

	// needs a seeker track to launch
	if (meLaunchMode == SEEKER_TRACK)
	{
		UpdatePointingAngle();
        UpdateStatusSeekerTrack(targetObj);
        return;
	}

	status = LAUNCHER_ERROR; // bad meLaunchMode
}

/**
* Allows either missile or laser guided bomb child obj
*/
void tcLauncher::UpdateStatusSeekerTrack(tcGameObject* target)
{
    if (tcMissileDBObject *pMissileDBObj = dynamic_cast<tcMissileDBObject*>(mpChildDBObj))
    {
        /* check fire control state if necessary (this should be able to be handled without
        ** all of this sprawling code) */
        if (pMissileDBObj->NeedsFireControl())
        {
            if (!fireControlSensor)
            {
                status =  NO_FIRECONTROL; // database error
                return;
            }

            if (!fireControlSensor->IsTrackAvailable())
            {
                status = FC_BUSY; // no FC tracks available
                return;
            }

            if (target == 0)
            {
                status = NOT_DETECTED_FC; // target doesn't exist
                return;
            }

            float range;
            if (fireControlSensor->CanDetectTarget(target, range))
            {
                if (meLaunchMode == FC_TRACK)
                {
                    status = LAUNCHER_READY;
                    return;
                }
            }
            else
            {
                status = NOT_DETECTED_FC;
                return;
            }
        }

        long nSensorKey = pMissileDBObj->GetSensorKey();

        long fcID = parent->mnID;
        unsigned int fcIdx = fireControlSensorIdx;

        bool canDetect = simState->SensorCanDetect(nSensorKey, target,
            parent, pointingAngle, fcID, fcIdx);

        if (canDetect)
        {
            status = LAUNCHER_READY;
        }
        else
        {
            status = NOT_DETECTED_SEEKER;
        }
    }
    else if (tcBallisticDBObject* ballistic = dynamic_cast<tcBallisticDBObject*>(mpChildDBObj))
    {
        /* check fire control state if necessary (this should be able to be handled without
        ** all of this sprawling code) */
        if (ballistic->sensorClass.size() > 0)
        {
            if (!fireControlSensor)
            {
                status =  NO_FIRECONTROL; // database error
                return;
            }

            if (!fireControlSensor->IsTrackAvailable())
            {
                status = FC_BUSY; // no FC tracks available
                return;
            }

            if (target == 0)
            {
                status = NOT_DETECTED_FC; // target doesn't exist
                return;
            }

            float range;
            if (!fireControlSensor->CanDetectTarget(target, range))
            {
                status = NOT_DETECTED_FC;
                return;
            }
        }

        long nSensorKey = ballistic->GetSensorKey();

        long fcID = parent->mnID;
        unsigned int fcIdx = fireControlSensorIdx;

        bool canDetect = simState->SensorCanDetect(nSensorKey, target,
            parent, pointingAngle, fcID, fcIdx);

        if (canDetect)
        {
            status = LAUNCHER_READY;
        }
        else
        {
            status = NOT_DETECTED_SEEKER;
        }
    }
    else
    {
        fprintf(stderr, "GetLauncherStatus -- Error: SEEKER_TRACK guidance with non-missile or ballistic\n");
        status = LAUNCHER_ERROR;
        return;
    } 
}

/**
* @return string with more detail than TranslateStatus, specialized for this launcher
* For example, if too deep what is min depth
*/
const wxString& tcLauncher::TranslateStatusDetailed(int statusCode) const
{
    static wxString s;
    

    s = "";
    tcWeaponDBObject* weaponData = dynamic_cast<tcWeaponDBObject*>(mpChildDBObj);
    tcTorpedoDBObject* torpedoData = dynamic_cast<tcTorpedoDBObject*>(mpChildDBObj);


    switch (statusCode)
    {
    case LAUNCHER_READY: 
        s = "Launcher ready"; 
        break;
    case LAUNCHER_EMPTY: 
        s = "Launcher empty"; 
        break;
    case LAUNCHER_BUSY: 
        s = "Launcher busy"; 
        break;
    case NO_DATUM: 
        s = "No datum"; 
        break;
    case NO_TARGET: 
        s = "No target"; 
        break;
    case NOT_DETECTED_FC: 
        s = "Not detected by fire control"; 
        break;
    case NOT_DETECTED_SEEKER: 
        s = "Not detected by seeker"; 
        break;
    case FC_BUSY: 
        s = "Fire control busy"; 
        break;
    case LAUNCHER_ERROR: 
        s = "Corrupt launcher error"; 
        break;
    case LAUNCHER_INACTIVE: 
        s = "Launcher inactive or damaged";
        break;
    case NO_FIRECONTROL:
        s = "No fire control sensor (database error)"; 
        break;
    case TOO_DEEP:
        if (torpedoData != 0)
        {
            s.Printf("Too deep for launch (%.0f m max)", torpedoData->maxDepth_m);
        }
        else if (weaponData != 0)
        {
            s.Printf("Too deep for launch (%.0f m max)", -weaponData->minLaunchAlt_m);
        }
        else
        {
            s = "Too deep for launch";
            wxASSERT(false);
        }
        break;
    case TOO_LOW:
        if (weaponData != 0)
        {
            s.Printf("Too low for launch (%.0f m min)", weaponData->minLaunchAlt_m);
        }
        else
        {
            s = "Too low for launch";
            wxASSERT(false);
        }
        break;
    case TOO_HIGH: 
        if (weaponData != 0)
        {
            s.Printf("Too high for launch (%.0f m max)", weaponData->maxLaunchAlt_m);
        }
        else
        {
            s = "Too high for launch";
            wxASSERT(false);
        }
        break;
    case DAMAGED: 
        s = "Launcher damaged"; 
        break;
    case BAD_LAUNCHER:
        s = "Invalid launcher"; 
        break;
    case INVALID_TARGET: 
        s = "Ineffective vs. target";
        break;
    case OUT_OF_RANGE:
        if (weaponData != 0)
        {
            s.Printf("Out of range (%.1f km max)", weaponData->maxRange_km);
        }
        else
        {
            s = "Out of range";
            wxASSERT(false);
        }
        break;
    case INVALID_FUEL_OPERATION: 
        s = "Invalid fuel op"; 
        break;
    case LAUNCHER_LOADING: 
        s = "Launcher loading"; 
        break;
    case LAUNCHER_UNLOADING: 
        s = "Launcher unloading"; 
        break;
    case OUT_OF_FOV: 
        s = "Out of field of view"; 
        break;
    case TOO_CLOSE:
        if (weaponData != 0)
        {
            s.Printf("Too close for launch (%.1f km min)", weaponData->minRange_km);
        }
        else
        {
            s = "Too close for launch";
            wxASSERT(false);
        }
        break;
    case LAUNCHER_EMPTY_AUTORELOAD: 
        s = "Launcher empty, reload queued"; 
        break;
    case ROE_HOLD: 
        s = "ROE prohibits launch";
        break;
    default:
        fprintf(stderr, "Bad launcher status code (%d)\n", statusCode);
        s = "Bad launcher status code";
        break;
    }

    return s;
}


/**
* Converts launcher status code into string.
*/
std::string tcLauncher::TranslateStatus(int statusCode)
{
	switch (statusCode)
	{
	case LAUNCHER_READY: return "Launcher ready"; break;
	case LAUNCHER_EMPTY: return "Launcher empty"; break;
	case LAUNCHER_BUSY: return "Launcher busy"; break;
	case NO_DATUM: return "No datum"; break;
	case NO_TARGET: return "No target"; break;
	case NOT_DETECTED_FC: return "Not detected by fire control"; break;
	case NOT_DETECTED_SEEKER: return "Not detected by seeker"; break;
	case FC_BUSY: return "Fire control busy"; break;
	case LAUNCHER_ERROR: return "Corrupt launcher error"; break;
	case LAUNCHER_INACTIVE: return "Launcher inactive or damaged"; break;
	case NO_FIRECONTROL: return "No fire control sensor (database error)"; break;
	case TOO_DEEP: return "Too deep for launch"; break;
	case TOO_LOW: return "Too low for launch"; break;
	case TOO_HIGH: return "Too high for launch"; break;
	case DAMAGED: return "Launcher damaged"; break;
	case BAD_LAUNCHER: return "Invalid launcher"; break;
	case INVALID_TARGET: return "Ineffective vs. target"; break;
	case OUT_OF_RANGE: return "Out of range"; break;
	case INVALID_FUEL_OPERATION: return "Invalid fuel op"; break;
    case LAUNCHER_LOADING: return "Launcher loading"; break;
    case LAUNCHER_UNLOADING: return "Launcher unloading"; break;
    case OUT_OF_FOV: return "Out of field of view"; break;
    case TOO_CLOSE: return "Too close for launch"; break;
    case LAUNCHER_EMPTY_AUTORELOAD: return "Launcher empty, reload queued"; break;
    case ROE_HOLD: return "ROE prohibits launch"; break;
	default:
		fprintf(stderr, "Bad launcher status code (%d)\n", statusCode);
		return "Bad launcher status code";
		break;
	}
}

/**
*
*/
tcLauncher::tcLauncher() :
	mbActive(false),
    mnDBKey(-1),
    mpLauncherDBObj(0),
    mnChildDBKey(-1),
    mpChildDBObj(0),
	isExternalFuelTank(false),
    itemWeight_kg(0),
	mfTimeToReady(0),
    mnCurrent(0),
    mnUncommitted(0),
    isLoading(false),
    capacity(0),
    repeatShots(0),
    msDatum(0,0,0),
    mnTargetID(-1),
	meLaunchMode(DATUM_ONLY),
    mnTargetFlags(0),
    pointingAngle(0),
	pointingElevation(0),
    firingArc_deg(0),
	mountPointingAngle(0),
    cycleTime_s(1.0f),
    isReloadable(false),
    fireControlSensor(0),
    fireControlSensorIdx(0),
    usePassive(false),
    preEnableSpeed_kts(0),
    runDepth_m(0),
    ceiling_m(0),
    floor_m(0),
    runToEnable_m(0)
{

}

/**
*
*/
tcLauncher::tcLauncher(tcLauncherDBObject* dbObj, tcPlatformObject* parent_)
: mnDBKey(dbObj->mnKey),
  mpLauncherDBObj(dbObj),
  parent(parent_),
  mpChildDBObj(0),
  isExternalFuelTank(false),
  fireControlSensor(0),
  pointingElevation(0),
  isReloadable(false),
  firingArc_deg(0),
  isLoading(false),
  isDamaged(false),
  preEnableSpeed_kts(0),
  status(LAUNCHER_INACTIVE),
  mnTargetID(-1),
  repeatShots(0)
{
    wxASSERT(dbObj);
    wxASSERT(parent);
    wxASSERT(simState);
    
    SetChildClass(dbObj->GetDefaultChildClass());

    if (mpChildDBObj != 0)
    {
        SetChildQuantity(dbObj->GetDefaultChildCapacity());
    }
    else
    {
        SetChildClass("");
        SetChildQuantity(0);
    }
}

tcLauncher::~tcLauncher()
{
}

