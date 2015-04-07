/** 
**  @file tcPlatformObject
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

#ifndef _TCPLATFORMOBJECT_H_
#define _TCPLATFORMOBJECT_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "tcFile.h"
#include "tcLaunchRequest.h"
#include "tcSensorState.h"
#include "tcGuidanceState.h"
#include "tcGameObject.h"
#include "tcSensorPlatform.h"
#include "tcCommandObject.h"
#include "tcFormation.h"


class tcStream;
class tcCommandStream;
class tcCreateStream;
class tcUpdateStream;
class tcGameStream;
class tcStores;

namespace database
{
    class tcPlatformDBObject;
    struct AirComplement;
    struct MagazineLoadout;
    struct LauncherLoadout;
}

namespace ai
{
    class Brain;
}

namespace scriptinterface
{
	class tcScenarioLogger;
}

using ai::Brain;


/**
* A generic moving object with sensors, launchers, and guidance.
*
* @see tcGameObject
*/
class tcPlatformObject : public tcGameObject, public tcSensorPlatform
{
public:
    friend class tcFormation;
    enum
    {
        HEADING_CMD = 0x0001,
        SPEED_CMD = 0x0002,
        ALT_CMD = 0x0004,
        LAUNCH_CMD = 0x0008,
        AI_CMD = 0x0010
    };
    enum
    {
        UPDATE_GUIDANCE = 0x01,
        UPDATE_LAUNCHERS = 0x02,
        UPDATE_SENSORS = 0x04,
		UPDATE_AI = 0x08,
		UPDATE_STORES = 0x10,
        UPDATE_FORMATION = 0x20
    };

    double fuel_kg; ///< current fuel
	float externalFuelCapacity_kg; ///< for external fuel tanks

    tcLauncherState mcLauncherState; 
    std::vector<tcStores*> magazines;

    //int mnSensors;
    tcGuidanceState mcGS;
    Brain* brain;
    tcLaunchRequest mcLaunchRequest;
    GeoPoint msTargetDatum;
    tcFormation formation;
    tcPlatformDBObject *mpDBObject;
    tcCommandObject commandObj;

    std::vector<GeoPoint> missilePreplan; ///< waypoints for missile preplan of next launch

    virtual void ApplyGeneralDamage(float damage, tcGameObject* damager);
    virtual float ApplyAdvancedDamage(const Damage& damage, tcGameObject* damager); ///< called when new damage occurs
    virtual void ApplyRepairs(float repair); ///< called when repairs occur (damage removed)    
    virtual void Clear();
    virtual void DesignateDatum(tcPoint p); 
    virtual void DesignateLauncherDatum(GeoPoint p, unsigned int anLauncher);  
    virtual bool DesignateLauncherTarget(long anID, unsigned anLauncher);
    virtual void DesignateTarget(long anID); 
    Brain* GetBrain();
    virtual void GetDatum(GeoPoint& p) {p=msTargetDatum;}
	virtual tcLauncher* GetLauncher(unsigned idx);
    virtual const tcLauncher* GetLauncher(unsigned idx) const;
    tcLauncher* GetLauncherById(unsigned int id);
    unsigned int GetLauncherCount() const;
	wxString GetLauncherDescription();
    virtual int GetLauncherQuantity(unsigned anLauncher);
    virtual void GetLauncherState(tcLauncherState*& pLauncherState) {pLauncherState=&mcLauncherState;}
    

    unsigned int GetMagazineCount() const;
    tcStores* GetMagazine(unsigned int idx);
	const tcStores* GetMagazineConst(unsigned int idx) const;
    tcStores* GetMagazineById(unsigned int id);
    unsigned int GetMagazineQuantity(const std::string& item);
	void SetLoadoutTag(const std::string& s);
	const std::string& GetLoadoutTag() const;
    const std::string& GetLoadoutCommand() const; ///< get string summarizing current loadout state
    void SetLoadoutCommand(const std::string& s);
    void ScheduleLoadoutCommand(const std::string& s);
    

    virtual void SetFormationLeader(long id);
	virtual void SetFormationMode(int mode);
    virtual void SetFormationPosition(float range_km, float span_km, float bearing_rad, float span_rad);
    virtual void SetFormationAltitudeOffset(float dh_m);
    virtual long GetFormationLeader() const;
    void MarkFormationUpdated(); ///< for multiplayer to trigger cmd msg for updated formation
    void DestroyFormation();
    virtual void AutoConfigurePlatform(const std::string& setupName);
    void GetAutoConfigurationData(const std::string& setupName, 
        std::vector<database::AirComplement>& airComplement, std::vector<database::MagazineLoadout>& magazineLoadout,
        std::vector<database::LauncherLoadout>& launcherLoadout);
    void AutoConfigureMagazines(const std::vector<database::MagazineLoadout>& magazineLoadout);
    void AutoConfigureLaunchers(const std::vector<database::LauncherLoadout>& launcherLoadout);

    virtual bool IsInterceptingTrack(long id);
    bool IsRefueling() const;
	float GetFuelCapacity() const;
	void AdjustExternalFuelCapacity(float change_kg);

	bool IsCapableVsTargetType(int targetFlag);
	bool IsEquippedForTargetType(int targetFlag);
    bool IsEquippedWithNuclear(int targetFlag);
	bool RatingForTargetType(int targetFlag, float& weaponWeight_kg, float& maxRange_km);
    bool RatingForTargetTypeAEW(float& weaponWeight_kg, float& maxRange_km);
	bool AllLaunchersEmpty();
	bool AllLaunchersFull();
    bool AllLaunchersReady();
    bool IsLoading() const;
	void UnloadAllLaunchers();
	virtual void EquipForTargetType(int targetFlag);
	virtual void EquipForTargetType(const std::string& targetType);

    virtual void Launch(long& rnKey, unsigned& rnLauncher);
    virtual void RandInitNear(float afLon_deg, float afLat_deg);
    virtual void SetAltitude(float new_altitude_m);
    virtual void SetHeading(float afNewHeading);
    virtual void SetMaxTurnRate(float rate_degps);
    float GetMaxTurnRate() const;
	void SetRefueling(bool state);
    virtual void SetSpeed(float newSpeed);
    virtual int SetLaunch(int anLauncher, int anQuantity);
    virtual void Update(double afStatusTime);
    virtual void UpdateMagazines(double t);

	virtual void SetController(const std::string& username);

    void PrintToFile(tcFile&);
    void SaveToFile(tcFile& file);
    void LoadFromFile(tcFile& file);
    virtual void Serialize(tcFile& file, bool mbLoad);
	virtual void SaveToPython(scriptinterface::tcScenarioLogger& logger);

    virtual bool IsPlatformObject() const;

    virtual tcCommandStream& operator<<(tcCommandStream& stream);
    virtual tcCreateStream& operator<<(tcCreateStream& stream);
    virtual tcUpdateStream& operator<<(tcUpdateStream& stream);
    virtual tcGameStream& operator<<(tcGameStream& stream);

    virtual tcCommandStream& operator>>(tcCommandStream& stream);
    virtual tcCreateStream& operator>>(tcCreateStream& stream);
    virtual tcUpdateStream& operator>>(tcUpdateStream& stream);
    virtual tcGameStream& operator>>(tcGameStream& stream);

    virtual void ClearNewCommand();
    virtual bool HasNewCommand() const;

    static void InitPlatformObject();

    tcPlatformObject();
    tcPlatformObject(tcPlatformObject&);
    tcPlatformObject(tcPlatformDBObject *obj); 
    virtual ~tcPlatformObject();

protected:
    float lastHeadingDelta; // a workaround to smooth heading rate changes
	bool isRefueling; ///< true if refuel is in progress
	std::string loadoutTag; ///< string to identify current loadout type
    float reducedTurnRate_degps; ///< for slower turns, use for current turn only then reset
	float ShipAccel();
	float fuel_rate;

    virtual void ApplyRestrictions();
    virtual void SetFireControlSensors();

    virtual void Move(float dt_s);
    virtual void UpdateAI(float t);
    virtual void UpdateClimb(float dt_s) {};
    virtual void UpdateFormationGuidance(void);
    virtual void UpdateHeading(float dt_s);
    virtual void UpdateLauncherState(float dt_s);
    virtual void UpdateSensors(double t);
    virtual void UpdateSpeed(float dt_s);

    void SaveFormationPositionToPython(scriptinterface::tcScenarioLogger& logger);
    void ApplyLauncherDamage(float damage, tcGameObject* damager);
    void ParseLoadoutCommand(const std::string& cmd, std::vector<std::string>& item, std::vector<unsigned int>& quantity);
};

#endif
