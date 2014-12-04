/**
**  @file tcPlatformInterface.h
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

#ifndef __tcPlatformInterface_h__
#define __tcPlatformInterface_h__

#if _MSC_VER > 1000
#pragma once
#endif

#include "tcPlatformObject.h"
#include "tcSensorMap.h"
#include "tcSubInterface.h"
#include "tcScenarioInterface.h"
#include "tcStringTable.h"

#include <boost/python.hpp>

using namespace boost::python;


class tcAllianceSensorMap;

namespace ai
{
    class BlackboardInterface;
    class Nav;
}
class tcSimState;
class tcSoundConsole;
class tcCommandQueue;
class tcTacticalMapView;

namespace database
{
    class tcWeaponDBObject;
}

namespace scriptinterface {
	class tcFlightPortInterface;
    class tcMissionInterface;

	class tcLauncherInfo 
	{
	public:
		int mnLauncher;     ///< index of launcher, or -1 for none
		int mnQuantity;
		int mnTargetFlags;  ///< 0x01 - surface, 0x02 - air, 0x04 - land
        float minLaunchAlt_m; ///< min altitude for launch
        float maxLaunchAlt_m; ///< max altitude for launch
        float minRange_km; ///< minimum recommended launch range
        float maxRange_km; ///< maximum range that ai considers
		float mfRange_km;   ///< maximum range that ai considers (for compatiblity, same as maxRange_km)
        float maxDepth_m;   ///< max depth for subsurface launch (max depth that torpedo can achieve?)
        float speed_mps; ///< nominal speed for adjusting future target position
		int mnLaunchMode;   ///< 0 - datum, 1 - handoff Fire and Forget, 2 - handoff, 3 - bomb, 4 - autocannon, 10 - air CM, 11 - sonobuoy,  -1 error
        int launcherStatus; ///< see @see tcLauncher::teLauncherStatus
        double sectorCenter; ///< az of center of launch engagement sector in deg
        double sectorWidth;  ///< width of engagement sector in deg
		int fireControlTracks; ///< number of active FC tracks (0 if N/A)
		int maxFireControlTracks; ///< max number of FC tracks (999 if N/A)
        bool isARM; ///< true if uses ESM seeker (need target with active emitter)
        bool isNuclear; ///< true if launcher loaded with nuclear weapons
        bool isLoading; ///< true if launcher is loading or unloading
        bool acceptsWaypoints; ///< true if weapon accepts preplan waypoints
        float lifeTime_s; ///< effective time that item operates (normally for CM or sonobuoy)
        tcWeaponDBObject* weaponData;

        bool IsValid() const {return mnLauncher != -1;}
	};

	class tcSensorInfo
	{
	public:
		int isActive;   ///< 0 if OFF, 1 if ON
		int type;       ///< FLAGS: 1 radar, 2 ESM, 4 passive sonar, 8 active sonar, 16 optical, 0 error

        bool IsPassive() {return ((type & 0x16) != 0);}
	};

	/// wrapper around tcSensorMapTrack with additional info for iterating
	class tcTrackIterator : public tcSensorMapTrack 
	{
	public:
		long mnKey;
	};

	class tcTrackList
	{
	public:
		std::vector<tcSensorMapTrack> track;
		std::vector<float> range_km; ///< range relative to calling platform (this is sketchy 9NOV2010)

		tcSensorMapTrack GetTrack(int n) {return track[n];}
		tcSensorMapTrack* GetTrackPointer(int n) {return &track[n];}
		int Size() {return (int)track.size();}

		tcTrackList() {}
	};

	class tcFormationPosition
	{
	public:
		float range_km;
		float span_km;
		float bearing_rad;
		float span_rad;		
	};


    /**
    * Info on missiles currently under fire control guidance
    */
    class tcFireControlInfo
    {
    public:
        bool radarGuidanceActive; ///< true if guiding SA or command missile
        float maxLeft_deg;  ///< most platform can turn to the left (negative) to keep radar on child missile
        float maxRight_deg; ///< most platform can turn to the right
		unsigned int weaponsOut; ///< number of weapons active launched by this platform
    };

	/**
	* Interface class for Python-unit interface. 
	* Holds static reference to platform of interest,
	* this static reference is set before passing object to Python.
	* Note, there is probably a better way to do this. 
	*/
	class tcPlatformInterface 
	{
	public:
		double mfCurrentTime;
		static void InitPythonClassesA();
		static object InitPythonPlatformInterface();
		static object GetPlatformInterface();

		// basic nav commands: heading, speed, altitude
		/// [Python: GetAlt] gets platform altitude in meters
        float GetLongitude() const;
        float GetLatitude() const;
		float GetAltitude() const; 
		/// gets fraction of fuel remaining from 0 - 1
		float GetFuel() const;
		/// [Python: GetMaxAlt] gets max altitude in meters indicated in database entry
		float GetMaxAltitude(); 
		/// gets current platform speed in kts
		float GetSpeed(); 
		///  gets max platform speed in kts indicated in database at current altitude (calculated at full mil throttle for aerodynamic air platforms)
		float GetMaxSpeed();
		///  gets max platform speed in kts indicated in database (calculated at full mil throttle for aerodynamic air platforms)
		float GetMaxSpeedForAltitude(float alt_m);
		///  gets max platform speed in kts indicated in database (calculated at full AB throttle for aerodynamic air platforms only)
		float GetMaxSpeedForAltitudeAB(float alt_m);
		/// gets current heading in degrees
		float GetHeading(); 
		/// gets current heading in radians
		float GetHeadingRad();
		/// gets height of terrain in meters at (lon, lat)
		float GetMapTerrainElevation(float lon_rad, float lat_rad);
		/// gets height of terrain under platform in meters
		float GetTerrainElevation();
		/// true if platform has a throttle control (aero air models)
		bool HasThrottle();

        /// gets current throttle setting, returns -1.0 if has no throttle
        float GetThrottle();

        /// gets cruise speed for altitude in kts
        float GetCruiseSpeedForAltitude(float alt_m);

        /// range in km at cruise speed for given altitude
        float GetCruiseRangeForAltitude(float alt_m);

        float GetCruiseAltitude() const;

        /// gets stall speed for altitude in kts
        float GetStallSpeedForAltitude(float alt_m);


		/// set goal altitude for platform in meters
		/**
		* [Python: SetAlt]
		* For air objects
		* @param alt_m goal altitude of platform in meters
		*/
		void SetAltitude(float alt_m);
		/// sets maximum +/- pitch for air objects in degrees, workaround to slow descent for cv landing
		void SetPitchLimitDeg(float lim_deg);
		/// overrides climb for air objects in degrees
		void SetClimbDeg(float angle_deg);
        /// gets current climb angle
        float GetClimbDeg();
		/// overrides climb for air objects in radians
		void SetClimbRad(float angle_rad);
		/// sets maximum turn rate in deg/s for current turn
		void SetMaxTurnRate(float rate_degps);

		/// sets speed of platform
		void SetSpeed(float speed_kts);
		/// set speed of platform to maximum speed (use SetThrottle for aero air objects)
		void SetSpeedToMax();  
		/// set throttle for air objects
		/**
		* for air objects, sets throttle
		* @param throttleFraction 0 - 1.1, use 0 - 1 for non afterburning throttle, 1.1 for afterburners
		*/
		void SetThrottle(float throttleFraction);
		/// sets heading in degrees
		void SetHeading(float heading_deg);
		/// sets heading in radians
		void SetHeadingRad(float heading_rad);
		/// get heading to (lon,lat) datum in degrees
		float GetHeadingToDatum(float afLon_rad, float afLat_rad);
		/// get range to (lon,lat) datum in km
		float GetRangeToDatum(float afLon_rad, float afLat_rad);

        long GetFormationLeader() const;
        void SetFormationLeader(long id);
        bool IsInFormation() const;
        bool IsFormationLeader() const;
        void SetFormationEdit(bool state);
        long GetFormationEditId() const;
        void SetFormationPosition(float range_km, float span_km, float bearing_rad, float span_rad);
		tcFormationPosition GetFormationPosition();
        void SetFormationAltitudeOffset(float dh_m);
		float GetFormationAltitudeOffset() const;
        void SetFormationMode(int mode);
        int GetFormationMode() const;
        void SetFormationUseNorthBearing(bool state);
		bool IsFormationUsingNorthBearing() const;

		// platform info
		/// get unit name of platform
		std::string GetPlatformName();
		/// get database class name of platform
		std::string GetPlatformClass();
        /// get sim id of platform
        long GetPlatformId() const;
        /// get platform alliance
        unsigned int GetPlatformAlliance() const;

		/// returns true if platform is a surface platform
		bool IsSurface() const;
		/// returns true if platform is an air platform
		bool IsAir() const;
		/// returns true if platform is a helo
		bool IsHelo() const;
        bool IsGroundVehicle() const;

		bool IsFixed() const;

		/// returns true if platform is a submarine
        bool IsSub() const;

        /// returns a sub interface object, @see scriptinterface::tcSubInterface
        tcSubInterface GetSubInterface();

        /// in-flight refueling
        bool CanRefuelInFlight() const;
        bool StartRefuelWith(long id);
        bool IsTankerAircraft(long id);
        unsigned int GetTankerSpotsFree(long id);

		// target commands
		/// set target for platform
		void SetTarget(long anID);
		/// get platform target, -1 for no target
		long GetTarget();
		/// get range to target in km
		float GetRangeToTarget();
		/// get track info object for target
		tcSensorMapTrack GetTargetTrackInfo();
		tcGameObject* GetTargetObj();
		bool GetTargetTrack(tcSensorMapTrack& track);
		/// estimates time for launched missile / gun to intercept track
		float GetLauncherInterceptTime(int anLauncher, tcSensorMapTrack& track);
		/// returns true if launcher is effective vs. current target
		bool IsLauncherEffective(int anLauncher); 
		/// returns true if any launchers effective vs. target type
		bool IsEquippedForTargetType(unsigned int class_mask);
        /// if target is valid, sets heading to intercept target (collision course intercept)
		float SetHeadingToInterceptTarget();
		tcAllianceROEInfo GetROE() const;


		// weapon related commands
		/// gets launcher info object for best launcher for target
		tcLauncherInfo GetBestLauncher(); 
		/// gets number of launchers available on platform
		int GetLauncherCount();
		/// sets datum for launcher
		void SendDatumToLauncher(float afLon_rad, float afLat_rad, float alt_m, int anLauncher);
		/// hands off platform target to launcher
		bool HandoffTargetToLauncher(int anLauncher);
        /// better method to use than handoff above
        bool SendTargetToLauncher(long targetId, int anLauncher);
		/// orders launch
		void Launch(int anLauncher, int quantity);
		/// get class name of launcher weapon
		std::string GetLauncherWeaponName(int anLauncher);
		/// get quantity available for launch in launcher
		int GetLauncherQuantity(int anLauncher);
		/// true if launcher can launch using datum only (i.e. no track just a set of coordinates)
		bool IsDatumLaunch(int anLauncher) {return mpPlatformObj->mcLauncherState.IsDatumLaunch(anLauncher);}
		/// C++ only
		bool GetLauncherInfo(tcLauncherInfo& info, int anLauncher);
        /// [Python: GetLauncherInfo] returns launcher info object
        tcLauncherInfo GetLauncherInfoByValue(int launcher);
        int GetLauncherStatus(int launcher);
        tcFireControlInfo GetFireControlInfo();
        void SetMissilePreplan(const std::string& preplan);
        bool IsTargetInRange(int nLauncher, float lon_rad, float lat_rad, float alt_m, float targetHeading_rad, float targetSpeed_kts);
        float CalculateBombElevationDeg(float targetLon_rad, float targetLat_rad);
		float EstimateMissileRangeKm(float launchSpeed_mps, float launchAlt_m, float targetAlt_m, const std::string& missileType);

        /// count of types of weapons accepted by this launcher
        int GetLauncherTypesCount(int anLauncher);
        /// class name of type
        std::string GetLauncherTypeName(int anLauncher, int anType);
        /// true if magazine can accept item (unloaded from launcher)
        bool CanMagazineAcceptItem(std::string item);
        /// quantity of item available in platform magazines
        int GetMagazineQuantity(std::string item);
        /// list of items in all platform magazines
        tcStringArray GetMagazineItems();
        bool HasMagazine() const;
        /// loads item into launcher, launcher must be empty
        void LoadLauncher(int anLauncher, const std::string& item);
        /// loads any item into launcher, dev mode only (ignores database)
        void LoadLauncherTest(int anLauncher, const std::string& item, int quantity);
        /// unloads launcher
        void UnloadLauncher(int anLauncher);
		/// used to refuel launcher
		void LoadOther(const std::string& item, unsigned long quantity=999999);
        /// true if aircraft is on maintenance hold in flightport
        bool MaintenanceHold() const;
        /// general database query of equipment
        tcStringArray GetEquipmentListByClass(const std::string& classString);

        /// get list of database loadouts
        tcStringArray GetLoadoutList();
        /// equip loadout (edit mode)
        void EquipLoadout(const std::string& loadout);
        /// get list of platform flight-complement/mag-loadout setups
        tcStringArray GetPlatformSetups();
        void AutoConfigurePlatform(const std::string& setupName);

		/// @return true if platform is refueling
		bool IsRefueling() const;
        float GetWeightMargin(); // weight margin for aircraft

        /// dev mode only, set fuel fraction
        void SetFuelTest(float fuelFraction);
        

		// order related commands
		/// add a task
		void AddTask(const std::string& taskName, double priority, int attributes);
		/// adds navigation waypoint (creates nav task if necessary)
		void AddNavWaypoint(float afLon_rad, float afLat_rad);
		/// adds navigation waypoint with alt and speed params (creates nav task if necessary)
		void AddNavWaypointAdvanced(float afLon_rad, float afLat_rad, float alt_m, float speed_kts);
        /// 
        void DeleteNavWaypoint(size_t idx);
		/// edits existing navigation waypoint
		void EditNavWaypoint(size_t idx, float afLon_rad, float afLat_rad);
		/// edits existing navigation waypoint with alt and speed params
		void EditNavWaypointAdvanced(size_t idx, float afLon_rad, float afLat_rad, float alt_m, float speed_kts);
        /// edits reference/anchor mode of waypoint
        void EditNavWaypointReference(size_t idx, unsigned char referenceMode, long referencePlatform);
        /// inserts navigation waypoint before point at idx
		void InsertNavWaypoint(size_t idx, float lon_rad, float lat_rad);
        ///
        void SetNavWaypointTasks(size_t idx, const std::string& taskList);
        void AddWaypointTask(size_t idx, const std::string& task);
        void RemoveWaypointTask(size_t idx, const std::string& task);
        tcDatum GetRandomPatrolPoint() const;

        /// @return idx of current waypoint    
		unsigned int GetCurrentWaypoint() const;
        /// change current waypoint (for script based looping)
        void SetCurrentWaypoint(unsigned int idx);
		/// true to loop through waypoints indefinitely
		void SetNavLoopState(bool state);
        /// true if looping through waypoints
        bool GetNavLoopState() const;
        /// clear all tasks
		void ClearTasks();
		/// delete task
        void DeleteTask(const std::string& taskName);
        /// sets run(true) suspend(false) state of task
        void SetTaskRun(const std::string& taskName, bool state);

		/// gets low-priority, anonymous interface to unit blackboard
		ai::BlackboardInterface GetBlackboardInterface();
		/// @return true if task exists
		bool TaskExists(const std::string& taskName);
        /// @return list of all visible tasks
        tcStringArray GetTaskList();

		// sensor map and sensor commands
		/// get first track in alliance sensor map, track iterator object is returned
		tcTrackIterator GetFirstTrack();
		/// gets total number of tracks in alliance sensor map
		int GetTrackCount();
		/// gets next track in sensor map, nPos is obtained from track iterator from last call
		tcTrackIterator GetNextTrack(long nPos);
		/// gets number of sensors on platform
		int GetSensorCount();
		/// gets sensor info object for sensor n
		tcSensorInfo GetSensorInfo(int n);
		/// sets state of sensor n, 0 - off, 1 - on
		void SetSensorState(int n, int state);
		/// sets state of all sensors on platform, 0 - off, 1 - on
		void SetAllSensorState(int anState); 
		/// gets track info object for closest track within range that matches classification and affiliation parameters
		tcSensorMapTrack GetClosestTrack(float afMaxRange_km, UINT16 anClassMask, 
			UINT8 anAffiliation, int maxEngagements);
		/// gets track info object for closest air track within range matching affiliation
		tcSensorMapTrack GetClosestAirTrack(float afMaxRange_km, 
			UINT8 anAffiliation, int maxEngagements);
		/// gets track info object for closest surface track within range matching affiliation
		tcSensorMapTrack GetClosestSurfaceTrack(float afMaxRange_km, 
			UINT8 anAffiliation, int maxEngagements);
		/// gets track info object for closest missile track within range matching affiliation
		tcSensorMapTrack GetClosestMissileTrack(float afMaxRange_km, 
			UINT8 anAffiliation, int maxEngagements);
		/// gets track list object that has all tracks within range matching affiliation
		tcTrackList GetTrackList(int anClassMask, float afMaxRange_km, UINT8 anAffiliation);
		tcTrackList GetTrackListValidROE(int anClassMask, float afMaxRange_km);
        /// Gets friendly tracks
        tcTrackList GetFriendlyTrackList(unsigned int classMask, float maxRange_km, const std::string& mode = "");

		/// get intercept heading to track in radians
		float GetInterceptHeadingToTrack(const tcSensorMapTrack& track);
		// get range to track in km
		float GetRangeToTrack(const tcSensorMapTrack& track);
		/// set heading to intercept track
		float SetHeadingToInterceptTrack(tcSensorMapTrack track);
		/// get track info object corresponding to track id
		tcSensorMapTrack GetTrackById(long id);

		// flightport (airstrip, cv flight deck, helo pad)
		/// true if platform has a flight port (e.g. carrier)
		bool HasFlightPort();
		/// return flightport interface object
		tcFlightPortInterface GetFlightPortInfo();
		/// returns track with landing data for landing on platform matching id
		tcTrack GetLandingData(long id);
		/// Get landing state (gear up = 0, down = 1)
		int GetLandingState();
		/// Set gear up (state = 0) or gear down (state = 1)
		void SetLandingState(int state);

        tcMissionInterface GetMissionInfo();

		// multiplayer related
		/// return name of player controlling this platform
		std::string GetController() const;
		/// true if platform is available for control by client
		bool IsAvailable() const;
		/// true if game is in multiplayer mode
		bool IsMultiplayerActive() const;
		/// release control of this platform (multiplayer)
		void ReleaseControl();
		/// take control of this platform (multiplayer)
		void TakeControl();

		// miscellaneous
		
		/// Gets id from unit name, -1 if not found or not own-alliance
		long LookupFriendlyId(const std::string& unitName);
		/// Gets name from unit id, "" if not found or not own-alliance
		std::string LookupFriendlyName(long id);
        /// Get sim time for last platform update (current time)
		double GetTime() const;
		void GetUserInput(std::string callback, std::string uitype);
        /// @return true if platform is under local player control
        bool IsPlayerControlled() const;
        bool IsValid() const;
		void SendCommand(const std::string& command);
		/// display text message in user console
		void DisplayMessage(const std::string& text);
		/// popup text message
		void DisplayPopupMessage(const std::string& text);
		/// play sound effect
        void PlaySound(const std::string& effect);
		/// sets text displayed in platform info panel
		void SetActionText(const std::string& text);
		/// returns a random number between 0 and 1
		float GetRand() {return randf();}

		/// queries field info from database
		scriptinterface::tcStringTable QueryDatabase(const std::string& table, const std::string& databaseClass, const std::string& fields);

		// mission editor mode commands

        /// mission edit mode only
        tcStringArray GetPlatformListByClass(const std::string& classString);
        void AddUnitToFlightDeck(const std::string& className);
        void SetAirGroupName(const std::string& groupName);
        std::string GetAirGroupName() const;
        unsigned int GetAirUnitId() const;
        void SetAirGroupCount(unsigned int n);
        unsigned int GetAirGroupCount() const;
        void SetMagazineAddCount(unsigned int n);
        unsigned int GetMagazineAddCount() const;
        void AddItemToMagazine(const std::string& item, unsigned int quantity);
        tcStringArray GetCompatibleItemList(int launcher_idx) const;
        void SetIncludeProbability(float probability);
        float GetIncludeProbability() const;
        void AddRandomBox(float lon1_deg, float lon2_deg, float lat1_deg, float lat2_deg);
        void DeleteAllRandomBoxes();
        void UpdateMissionEditGraphics();
        void SetAlwaysVisible(bool state);
        bool GetAlwaysVisible() const;
		void DeletePlatform();
		/// move platform to new position [mission edit only]
		void MovePlatform(float afLon_rad, float afLat_rad);
		/// change name of platform [mission edit only]
		void RenamePlatform(const std::string& s);
        tcStringArray GetPlatformNameList();
        tcPlatformInterface GetUnitInterface(const std::string& unitName);
        tcScenarioInterface GetScenarioInterface();
        float GetCost() const;
        void SetCost(float val);

        static bool IsDeveloperModeStatic();
        bool IsDeveloperMode() const; ///< non-static version for calling within script (?)
        void SetInvulnerable(bool state); ///< dev mode only
        void LaunchAtMe(const std::string& weaponClass, unsigned int quantity); ///< dev mode only
        void SetTestParameter(const std::string& paramName, float val); ///< dev mode
		void ApplyDamage(float damageFraction); ///< dev mode
		void ApplyAdvancedDamage(bool isPen, float kinetic_J, float explosive_kg, float blast_psi,
			float waterBlast_psi, float thermal_J_cm2,float fragHits,float fragEnergy_J);

		static void SetObj(tcPlatformObject *apObj) {mpStaticPlatformObj = apObj;}
		void GetLocalObj();
		void SetPlatform(tcPlatformObject *obj);
		static void AttachCommandQueue(tcCommandQueue *cq) {mpCommandQueue = cq;}
		static void AttachSimState(tcSimState *apSS) {mpSimState = apSS;}
		static void AttachConsole(tcSoundConsole *apConsole) {mpConsole = apConsole;}
		static void AttachMapData(tcMapData* md) {mapData = md;}
        static void AttachTacticalMap(tcTacticalMapView* mv) {tacticalMap = mv;}
        static void AttachScenarioInterface(tcScenarioInterface* si) {scenarioInterface = si;}
        static void SetDeveloperMode(bool state) {isDeveloperMode = state;}
        static bool GetDeveloperMode() {return isDeveloperMode;}
        static tcScenarioInterface* GetScenarioInterfaceStatic();
		void GetSensorMap();

		tcPlatformInterface();
		tcPlatformInterface(tcPlatformObject* obj);
		~tcPlatformInterface();

	private:
		enum {ALL_AFFILIATIONS=4, VALID_ROE=100};

		tcPlatformObject *mpPlatformObj;
		bool isPlatformOwnAlliance; ///< true if platform is part of user's alliance
		static tcPlatformObject *mpStaticPlatformObj;
		static tcSimState *mpSimState;
		static tcAllianceSensorMap *mpSensorMap;
		static tcSoundConsole *mpConsole;
		static tcCommandQueue *mpCommandQueue; // for requesting GUI commands
		static tcMapData* mapData; ///< for getting terrain elevation
        static tcTacticalMapView* tacticalMap; ///< for get formation edit information
        static bool isDeveloperMode; ///< special mode for developer test
        static tcScenarioInterface* scenarioInterface; ///< to allow hooked units access in edit mode

        ai::Nav* GetNav(); ///< helper function for other methods
        const ai::Nav* GetNav() const;
	};
}
#endif