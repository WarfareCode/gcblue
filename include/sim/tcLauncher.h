/** 
**  @file tcLauncher.h
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

#ifndef _TCLAUNCHER_H_
#define _TCLAUNCHER_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "simmath.h"
#include "AError.h"
#include <vector>

namespace database
{
    class tcDatabase;
    class tcLauncherDBObject;
    class tcDatabaseObject;
    enum teWeaponLaunchMode;
}

using namespace database;

class tcGameObject;
class tcPlatformObject;
class tcSimState;
class tcSensorState;
class tcRadar;
class tcStream;
class tcCommandStream;
class tcCreateStream;
class tcUpdateStream;
class tcGameStream;
class tcStores;
class tcSensorMapTrack;

/**
 * State for individual launcher.
 */
class tcLauncher
{
public:
    enum teLauncherStatus
    {
        LAUNCHER_READY = 0,
        BAD_LAUNCHER = 1, ///< launcher index does not exist
        LAUNCHER_EMPTY = 2,
        LAUNCHER_BUSY = 3, ///< launcher auto reloading
        NO_DATUM = 4,
        NO_TARGET = 5,
        NOT_DETECTED_FC = 6, ///< fire control sensor can't detect target (could be off)
        NOT_DETECTED_SEEKER = 7,  ///< seeker can't detect target
        FC_BUSY = 8,  ///< fire control sensor has no free tracks
        LAUNCHER_ERROR = 9,
        LAUNCHER_INACTIVE = 10,
        NO_FIRECONTROL = 11,
        TOO_DEEP = 12, ///< too deep for sub launch
		TOO_LOW = 13, ///< too low for aircraft missile launch
		TOO_HIGH = 14, ///< too high for aircraft missile launch
        DAMAGED = 15, ///< cannot operate due to damage
		INVALID_TARGET = 16, ///< not effective vs. target type
		OUT_OF_RANGE = 17, ///< target is beyond max range
		INVALID_FUEL_OPERATION = 18, ///< invalid op for external fuel tank
        LAUNCHER_LOADING = 19, ///< added for multiplayer, loading from magazine
        LAUNCHER_UNLOADING = 20, ///< added for multiplayer, unloading to magazine
        OUT_OF_FOV = 21, ///< target is outside of field of view of this launcher
        TOO_CLOSE = 22, ///< target is inside minimum range
        LAUNCHER_EMPTY_AUTORELOAD = 23, ///< empty, try autoreload when ready, workaround to delay auto-reload until after launch
        ROE_HOLD = 24 ///< ready, but launch violates ROE
    }; ///< launcher status codes

    short int mbActive;

    std::string displayName;
    long mnDBKey; ///< key in launcher database
    tcLauncherDBObject *mpLauncherDBObj;
    long mnChildDBKey;
    tcDatabaseObject *mpChildDBObj;
	bool isExternalFuelTank; ///< true if child is fuel tank
    float itemWeight_kg; ///< current unit weight of loaded items

    float mfTimeToReady;
    short int mnCurrent;
    short int mnUncommitted; ///< mnCurrent - mnUncommitted = # pending launch
    bool isLoading; ///< true if launcher is offline to load/unload weapons
    unsigned short capacity; ///< max capacity for current child class
    unsigned char repeatShots; ///< set to non-zero to automatically repeat shots (for guns)

    GeoPoint msDatum; ///< datum to pass to weapon nav guidance
    long mnTargetID; ///< track that seeker can acquire
    teWeaponLaunchMode meLaunchMode;
    short int mnTargetFlags;  ///< 0x01 - surface, 0x02 - air, 0x03 - land
    float pointingAngle; ///< current boresight azimuth angle in radians relative nose/bow
	float pointingElevation; ///< elevation angle in radians relative (to horizon?)
    float firingArc_deg; ///< from platform_launcher table
	float mountPointingAngle; ///< center of traversal region for pointable launchers or fixed pointing angle for fixed launchers (RELATIVE angle)
    float cycleTime_s; ///< from launcher_configuration table of current loaded child
    bool isReloadable; ///< from platform_launcher table

    tcSensorState* fireControlSensor; ///< sensor for fire control guidance
    unsigned char fireControlSensorIdx; ///< index of sensor on parent platform

    // torpedo programming params
    bool usePassive;
    float preEnableSpeed_kts;
    float runDepth_m;
    float ceiling_m;
    float floor_m;
    float runToEnable_m;

    tcCommandStream& operator<<(tcCommandStream& stream);
    tcCreateStream& operator<<(tcCreateStream& stream);
    tcUpdateStream& operator<<(tcUpdateStream& stream);
    tcGameStream& operator<<(tcGameStream& stream);

    tcCommandStream& operator>>(tcCommandStream& stream);
    tcCreateStream& operator>>(tcCreateStream& stream);
    tcUpdateStream& operator>>(tcUpdateStream& stream);
    tcGameStream& operator>>(tcGameStream& stream);

    void ClearPendingLaunch();
    bool CommandInfoMatches(const tcLauncher& launcher);
    void CopyCommandInfoFrom(const tcLauncher& launcher);
    const std::string& GetChildClassName() const;
    const std::string& GetChildClassDisplayName() const;
    tcDatabaseObject* GetChildDatabaseObject() const;
    
    const std::string& GetLauncherName() const;
	float GetCycleTime() const;
	unsigned GetFireControlTrackCount() const; ///< active FC tracks (0 if N/A)
	unsigned GetMaxFireControlTracks() const; ///< max FC tracks (999 if N/A)
    int GetLauncherStatus();
	tcGameObject* GetParent() const;
	float GetPointingElevation() const;
    float GetSectorCenter() const; ///< returns center of engagement sector in radians
    float GetSectorWidth() const; ///< returns width of engagement sector in radians
    float GetWeight() const;
    float GetItemWeight() const;
    bool IsAutoPoint() const;
    bool CheckTraversalFOV() const; ///< true to require target to be within FiringArc_deg of launcher (gun rounds)
    bool GetAutoPointing(float& az_rad, float& el_rad) const;

    bool IsDamaged() const;
	bool IsLoading() const;
	bool IsEffective(unsigned int targetClassification) const;
	bool IsEffective(const tcSensorMapTrack& track) const;
	bool IsChildFireAndForget();
    bool IsLoadedNuclear() const;

    void SetChildClass(const std::string& childClass, bool ignoreRestrictions = false);
    void SetChildQuantity(unsigned int quantity);
    void SetDamaged(bool state);
	void SetDatum(double lon_rad, double lat_rad, float alt_m);
	void SetLaunch(unsigned int quantity);
    void SetLoadState(bool state);
    void SetParent(tcPlatformObject *obj);
	void SetFOV(float fov_deg_);

    /// @return max quantity of item that launcher can hold, 0 if not compatible
    unsigned short GetCapacityForItem(const std::string& item) const;
    unsigned short GetCapacityForItem(const std::string& item, float& loadTime_s, float& cycleTime_s) const;
    unsigned int GetCompatibleCount() const;
    const std::string& GetCompatibleName(unsigned int idx) const;
	unsigned int GetCompatibleQuantity(unsigned int idx) const;
    wxArrayString GetAllCompatibleList();
    bool IsItemCompatible(const std::string& item) const;
    bool Reload();
    tcStores* FindLoadingStores(unsigned int& opId);
    float GetLoadingTime();
    void CancelLoadInProgress();
    void QueueAutoReload();

	unsigned char GetStatus() const;
	void UpdateStatus();
    void UpdateStatusSeekerTrack(tcGameObject* target);

    void UpdateScoreForDamage(tcGameObject* damager);
    void ActivateFireControl();
	bool AutoLaunchAgain();
    void SetRepeatShotsForType();

    void UpdateFireControlSensor();

    static void AttachSimState(tcSimState* ss);
    static std::string TranslateStatus(int statusCode);
    const wxString& TranslateStatusDetailed(int statusCode) const;

    tcLauncher();
    tcLauncher(tcLauncherDBObject* dbObj, tcPlatformObject* parent_);
    ~tcLauncher();
private:
    tcPlatformObject* parent;
    bool isDamaged;
	unsigned char status;
    static tcSimState* simState;

	void InitForNewChild(bool ignoreRestrictions = false);
	void UpdatePointingAngle();

};
#endif
