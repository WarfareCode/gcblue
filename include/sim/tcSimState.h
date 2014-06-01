/**
**  @file tcSimState.h
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

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef _TCSIMSTATE_H_
#define _TCSIMSTATE_H_


#include "tcDatabase.h"
#include "tcSensorMap.h"
#include "simmath.h"
#include "tcGameObject.h"
#include "tcPlatformObject.h"
#include "tcSurfaceObject.h"
#include "tcCarrierObject.h"
#include "tcAirObject.h"
#include "tcWeaponObject.h"
#include "tcSound.h"
#include "tcMapData.h"
#include "tcPool.h"
#include "tcAero.h"
#include "tcUserInfo.h"
#include "commandlist.h"
#include "tcString.h"
#include "tcESMSensor.h"
#include "tcRadar.h"
#include "tcDateTime.h"

#ifndef SCENARIO_PATH
#define SCENARIO_PATH "scenarios"
#endif

namespace scriptinterface
{
    class tcSimPythonInterface;
}

using namespace scriptinterface;

class tcCommandQueue;
class tcGoalTracker;
class tcStream;
class tcMissileObject;
class tcTorpedoObject;
class tcBallisticWeapon;
class tcPositionRegistry;
class tcWeaponTester;

#define N_GAME_OBJECTS 8192 // have to match tcAllianceSensorMap::MAX_TRACKS and ::MAX_SMTRACKS
#define SCEN_STRING_LENGTH 1024

/**
* Singleton class that manages core simulation
*/
class tcSimState
{
    struct tsScenarioInfo
    {
        char mzName[128];
        char mzDescription[SCEN_STRING_LENGTH];
        bool mbLoaded; ///< true if scenario is loaded
    };
    enum MultiplayerMode
    {
        MM_OFF = 0,
        MM_CLIENT = 1,
        MM_SERVER = 2
    }; ///< multiplayer mode options
public:
    friend class tcGameSerializer;
    friend class scriptinterface::tcScenarioLogger;
    friend class tcWeaponTester;

    tcPool<tcGameObject,N_GAME_OBJECTS> maPlatformState;
    tcDatabase *mpDatabase; // these should be private with better design
    tcUserInfo *mpUserInfo;
    tcGoalTracker *goalTracker; ///< tracks win/lose victory conditions for each alliance
    tcCommandQueue *mpCommandInterface;
    tcSimPythonInterface *mpPythonInterface;
    tcSensorMap mcSensorMap;
    tcRadar mcDefaultRadar; // used to test for detections before creating object
    double mfLastSensorUpdate;
    double mfLastSensorAgeOut;
    double mfLastTileAgeOut; // for tcMapData high res tiles
    std::vector<long> flightportPlatforms;
    std::vector<long> landingPlatforms;
    double lastLandingStateUpdate;
    tsScenarioInfo msScenarioInfo;

    static tcSimState* Get(); ///< accessor for singleton instance

    void AddLaunchedPlatform(long newKey, tcGameObject* launchingPlatform, unsigned nLauncher);
    void AddPlatform(tcGameObject *pplat);
    void AddPlatformWithKey(tcGameObject *pplat, long key);
    void AddRandomPlatform();
    void AttachCommandInterface(tcCommandQueue *apCommandInterface) {mpCommandInterface=apCommandInterface;}
    void AttachDB(tcDatabase *pDatabase);
    void AttachMapData(tcMapData *apMapData) {mpMapData=apMapData;}
    void AttachPythonInterface(tcSimPythonInterface *apIF) {mpPythonInterface = apIF;}
    void AttachUserInfo(tcUserInfo *apUserInfo) {mpUserInfo=apUserInfo;}
    void AttachWeaponTester();

    void BuildCollisionGroups();
    void ChangeHeading(long anKey, float afNewHeading);
    void ChangeHeadingForced(long anKey, float afNewHeading); // for scen edit mode
    void ChangeHeadingToLocation(long anKey, float afLon, float afLat);
    void ChangeLocation(long anKey, float afLon_rad, float afLat_rad);
    void ChangeNormSpeed(long anKey, float afNewNormSpeed);
    void Clear(); ///< clear all objects and reset simstate
    void ClearSensorMaps();
    tcGameObject* CreateGameObject(tcDatabaseObject *apDBObject);
    tcGameObject* CreateRandomPlatform(UINT platform_type);
    void DeleteAllPlatforms();
    void DeleteObject(long key);
    void DesignateTarget(long anKey, long anTargetKey);
    void DesignateDatum(long anKey, tcPoint p);
    void DesignateLauncherDatum(long anKey, GeoPoint p, unsigned anLauncher);
    bool DesignateLauncherTarget(long anKey, long anTargetKey, unsigned anLauncher);
    void GenerateRandomGoals();
    int GetAllSensorPlatforms(long *apKeyList, int anMaxLength);
    unsigned GetAlliancePlatforms(long *aaKeyList, unsigned anMaxLength, int anAlliance);
    int GetAllWeaponObjects(long *apKeyList,int anMaxLength);
    void GetDateTime(tcDateTime& dt) const;
    const tcDateTime& GetDateTime() const;
    void GetDescription(long anKey, tcString& s);
    void GetNextPlatform(long& pos, long& key, tcGameObject*& obj)
    {
        maPlatformState.GetNextAssoc(pos,key,obj);
    }
    int GetPlatformAlliance(long anKey, UINT& rnAlliance);
    unsigned int GetPlatformCount() {return maPlatformState.GetCount();}
    long GetPlatformStartPosition() {return maPlatformState.GetStartPosition();}
    int GetPlatformState(long anKey, tcGameObject*& pplat);
    tcGameObject* GetObject(long anKey);
    const tcGameObject* GetObjectConst(long id) const;
    tcGameObject* GetObjectByName(const std::string& unitName);
    void GetPlatformsWithinRegion(std::vector<long>& keyList, tcRect *apRegion);
    long GetRandomPlatform();
	const char* GetScenarioDescription() const;
    const char* GetScenarioName() const;
    tcSensorMap* GetSensorMap();
    double GetTime() {return mfSimTime;}
    long GetTimeAcceleration() const;
    bool GetTrack(long id, unsigned alliance, tcSensorMapTrack& track);
    bool GetTruthTrack(long id, tcTrack& track);

    bool IsLauncherReady(tcGameObject *apGameObj, unsigned anLauncher);
    bool IsLauncherReady(long anKey, unsigned anLauncher);
	bool IsScenarioLoaded() const;
    bool IsMultiplayerGameStarted() const;
    void SetMultiplayerGameStarted(bool state);
    void LoadTimeFromStream(tcStream& stream);
    void PrintToFile(tcString);
    void ProcessLanding(tcGameObject *receiver, tcGameObject *landing_unit);

    bool RadarCanDetect(long anSensorKey, const tcGameObject* target,
        tcGameObject* reference, float afSensorAz, long fcID = -1, unsigned fcIdx = 0);
    bool SensorCanDetect(long sensorKey, const tcGameObject* target,
        tcGameObject* reference, float sensorAz, long fcID = -1, unsigned fcIdx = 0);
    void RegisterChildObject(const std::string& name, tcGameObject* parent); ///< call when adding child to flightdeck
    void RemoveDestroyedObjects();
	void RenameObject(tcGameObject* obj, const std::string& s);
    void RequestLaunch(long anKey,int anLauncher);
    void SaveTimeToStream(tcStream& stream);

	void SaveToPython(const std::string& scenarioName);
    int Serialize(tcString scenname, bool mbLoad);
    void SetDateTime(const tcDateTime& dt); ///< Sets tcDateTime object for environment date (sky, etc)
    void SetMultiplayerOff();
    void SetMultiplayerClient();
    void SetMultiplayerServer();
	bool IsMultiplayerActive() const;
	bool IsMultiplayerClient() const;
	bool IsMultiplayerServer() const;
    double GetMultiplayerTimeLag() const;

    void PreloadScenarioDatabase();

    void SetScenarioDescription(const std::string& s);
    void SetScenarioLoaded(bool state);
    void SetScenarioName(const std::string& s);
    void SetTime(double afNewTime) {mfSimTime=afNewTime;} /////< Sets sim time, normally 0 at start of sim
    void SetTimeAcceleration(long accel);
    void UnregisterChildObject(const std::string& name);
    void Update();
    void UpdateLandings(double afSimTime);
    void UpdateLandingState(double afSimTime);
    void UpdateLaunch();
    void UpdateObjTerrainInfo();
    void UpdateWeaponHits();
    void UpdateWeaponHits2();
    void StartDamageLog(const std::string& fileName);
    void ResyncObjAlliance();

    void ToggleUserAlliance();

private:
    tcSimState();
    ~tcSimState();

    tcMapData *mpMapData;
    double mfSimTime;
    tcDateTime dateTime;
    MultiplayerMode multiplayerMode; ///< multiplayer mode, default = MM_OFF
	long timeAcceleration; ///< 0 - paused, 1 - normal, N - Nx accelerated time
    std::map<std::string, long> objectNameMap; ///< for fast lookup by object name
    std::map<std::string, long> captiveObjectMap; ///< lookup of captive flightdeck objects, secondary key is parent id
    tcPositionRegistry* positionRegistry; ///< for fast(er) lookup by region
    tcWeaponTester* weaponTester;

    bool clientPause;
    double multiplayerTimeLag_s; ///< last value of server update time - client time
    tcFile damageLog;
    bool logDamage;
    bool isMultiplayerGameStarted;

	void EvaluateGuidedMissileHit(tcMissileObject* missile, tcGameObject* target);
	void EvaluateImpactWeaponHit(tcWeaponObject* weapon);
    void EvaluatePointDefenseWeaponHit(tcWeaponObject* weapon);

    void EvaluateTorpedoHit(tcTorpedoObject* torp, tcGameObject* target);
    float GetFractionalDamage(float afDamage, tcGameObject *apGameObj);

	void PlayEntitySoundEffect(tcGameObject* obj, const std::string& effect);
    void ProcessRadarDetection(tcGameObject *apRadarPlat,tcGameObject *apTarget,
        tcRadar *apRadarSS);
    void RegisterPlatform(tcGameObject* obj);
	void UnregisterPlatform(tcGameObject* obj);
    void ReportDamage(tcGameObject* obj);
    void UpdateFireControl(tcGameObject *apGameObj, tcRadar *apRadarSS);
    void UpdateSeeker(tcGameObject *applat, tcRadar *apRadarSS);
    void UpdateSurveillance(tcGameObject *applat, tcSensorState *apSensorState);

    void TestDamageModel();
    void EvaluateMissileDamage(tcMissileObject* missile);
    void EvaluateTorpedoDamage(tcTorpedoObject* torp);
    void EvaluateBallisticDamage(tcBallisticWeapon* ballistic);
    void EvaluateWeaponDamage(tcWeaponObject* weapon, float minAlt_m, float maxAlt_m);
    void LogWeaponDamage(tcGameObject* target, tcWeaponObject* weapon, const Damage& damage, float damageFraction);
    void ReportHighYieldDetonation(tcWeaponObject* weapon);
    void EvaluateDirectHitDamage(tcWeaponObject* weapon, tcDamageModel* damageModel);

    void PreloadAssociatedRecords(tcDatabaseObject* obj);
};

#endif
