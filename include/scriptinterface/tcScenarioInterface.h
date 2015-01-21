/**  
**  @file tcScenarioInterface.h
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

#ifndef _SCENARIOINTERFACE_H_
#define _SCENARIOINTERFACE_H_

#ifdef WIN32
#pragma once
#endif

#include <map>
#include <string>
#include <boost/python.hpp>
#include "tcGoal.h"
#include "tcStringArray.h"
#include "tcStringTable.h"
#include "tcAllianceInfo.h"

class tcMapData;
class tcMapOverlay;
class tcSimState;
class tcDirector;
class tcCommandQueue;
class wxProgressDialog;

using namespace boost::python;

namespace ai
{
    class BlackboardInterface;
    class Nav;
}

/**
*
*/
namespace scriptinterface 
{
    using namespace ai;
    /**
    * This may be redundant with other 3D point structs/classes.
    * A new one is declared here to use with Python.
    */
    class tcDatum
    {
    public:
        double lat; ///< lat in degrees
        double lon; ///< lon in degrees
        double alt; ///< alt in meters
    };

    class tcPlatformInterface;

    /**
    *
    */
    class tcScenarioUnit
    {
    public:
        std::string className; ///< name to lookup type in database
        std::string unitName;  ///< specific name of instance
        double lat; ///< lat in degrees
        double lon; ///< lon in degrees
        double alt; ///< alt in meters
        double heading; ///< heading in deg
        double speed; ///< speed in knots
        double throttle; ///< throttle setting, 0 to 1, or > 1 for afterburner
        double cost; ///< custom cost for scoring, negative to use database default

        void SetPosition(double lon_deg, double lat_deg, float alt_m);
        bool Validate();
    };

    class tcParsedUnitName
    {
    public:
        bool isValid;
        std::string root;
        std::string separator;
        long id;
    };

	class tcAllianceROEInfo
	{
	public:
		int airROE; ///< 0 weapons hold, 1 weapons tight, 2 weapons free, 99 error
		int surfaceROE;
		int subROE;
		int landROE;
	};

    /**
    * Interface class to python scenario generation scripts. 
    */
    class tcScenarioInterface 
    {
    public:        
        // Interface functions to be called through Python
        bool AddUnitToAlliance(tcScenarioUnit unit, int alliance);
        bool AddUnitToFlightDeck(std::string parentName, std::string className, 
            std::string unitName, int locCode);
        void AddToUnitMagazine(const std::string& unitName, 
            const std::string& item, unsigned long quantity);
        tcPlatformInterface GetUnitInterface(const std::string& unitName);
		std::string GetUnitNameById(long id) const;
        long GetUnitIdByName(const std::string& unitName) const;
        void SetUnitLauncherItem(const std::string& unitName, 
            unsigned int launcherIdx, const std::string& item, unsigned int quantity);
        void SetFlightDeckUnitLoadout(const std::string& parent, const std::string& child, 
            const std::string& loadoutCommand);
        std::string GetRandomPlatformName(const std::string& databaseClass, const std::string& referenceName);
        bool ParseUnitName(const std::string& referenceName, wxString& root, wxString& separator, long& id) const;
        tcParsedUnitName GetParsedUnitName(const std::string& referenceName) const;
        void DuplicateUnitTasking(const std::string& unitName1, const std::string& unitName2);

        void SetUnitAlwaysVisibleState(const std::string& unitName, bool state);

        void AddUnitTask(const std::string& unitName, const std::string& taskName, 
            double priority, int attributes);
        bool AllianceExists(int alliance) const;
        void CreateAlliance(int alliance, const std::string& name);
        void SetAllianceRelationship(int alliance_a, int alliance_b, const std::string& relationship);
        void SetAllianceDefaultCountry(int alliance, const std::string& countryName);
        std::string GetAllianceCountry(int alliance);
        void SetAlliancePlayable(int alliance, bool state);
        bool IsAlliancePlayable(int alliance) const;
        tcAllianceROEInfo GetAllianceROE(int alliance) const;
        void SetAllianceROEByType(int alliance, int airRoe, int surfaceROE, int subROE, int landROE);
		void SetAllianceROE(int alliance, int allRoe);

        tcScenarioUnit GetDefaultUnit();
        tcDatum GetRandomDatum(double lon, double lat, 
            float min_alt, float max_alt, float rand_offset);
		void GetStartTheater(double& lon_deg, double& lat_deg) const;
	    int GetUserAlliance() const;
		void SaveGame(const std::string& fileName);
        void SetAllianceGoal(int alliance, tcGoal& goal);
        tcGoalWrap GetAllianceGoal(int alliance);
        tcGoalWrap GetGoalById(unsigned long id);
        void AddChildGoalToId(unsigned long id, tcGoal& goal);
        void DeleteGoalById(unsigned long id);
		bool IsUsingNATONames() const;
		std::string GetDisplayName(const std::string& className);

        void SetDateTime(int year, int month, int day, int hour, int min, int sec);
        void SetDateTimeByString(const char* s);
		std::string GetScenarioDateAsString() const;
        void SetPerfectScore(float score);
        void SetScenarioDescription(std::string s);
        void SetScenarioLoaded(bool state);
        void SetScenarioName(const std::string& s);
        void SetScenarioLocked(bool state);
        bool IsScenarioLocked() const;
		void SetStartTheater(double lon_deg, double lat_deg);
        void SetUserAlliance(int alliance);

        tcStringArray GetUnitList(float lon1_rad, float lat1_rad, float lon2_rad, float lat2_rad, int alliance);

        // tcDirector interface functions for briefing events
        // time/mode events
        void ClearEvents();
        void HookPlatform(std::string unitName);
        void Pause();
        void Resume();
        void Set3DMode(int modeCode);
        void SetBriefingMode(bool state);
        void SetEventTime(double t);

        // audio events
        void PauseAudio();
        void PlayAudio(const std::string& audioName, double seekTime);
        void PlayEffect(const std::string& effectName); ///< may want to use string for this instead
        void SeekAudio(double seekTime);

        // text console and map events
		void ChangeMapTheater(double lon_deg, double lat_deg);
        void ChangeMapView(double lon_deg, double lat_deg, double lonSpan_deg);
        void ChangeWorldMapView(double lon_deg, double lat_deg, double lonSpan_deg);
        void SetStartView(double lon_deg, double lat_deg, double lonSpan_deg);
        void ConsoleText(const std::string& text);
        void ChannelMessage(const std::string& message, const std::string& channel, unsigned int alliance);
        void MapText(const std::string& text, double lon_deg, double lat_deg, double duration, int effect);

        // overlay graphics
        void OverlayText(const std::string& text, double lon_deg, double lat_deg, const std::string& color="black");
        void OverlayTextInteractive(const std::string& text, double lon_deg, double lat_deg);

        // camera and 3D events
        void FlybyCamera(const std::string& unitName, double duration, float az1_deg, float az2_deg,
            float el1_deg, float el2_deg, float r1_m, float r2_m);
        void TrackCamera(const std::string& unitName, double duration, float x1, float x2, 
            float y1, float y2, float z1, float z2);
        void Text3D(const std::string& text, double duration, float x, float y, float size, int effect);

		tcMapOverlay* GetMapOverlay() const;

        // goal class creation methods (cannot find a way to do directly)
        tcCompoundGoal CompoundGoal(int type);
        tcTimeGoal TimeGoal();
        tcDestroyGoal DestroyGoal(const std::string& target);
		tcProtectGoal ProtectGoal(const std::string& target);
        tcAreaGoal AreaGoal();
        
        // simple briefing text
		void ClearSimpleBriefing();
		const std::string& GetSimpleBriefing(int alliance) const;
		void SetSimpleBriefing(int alliance, const std::string& briefingText);

		// database query methods
		tcStringArray GetPlatformListByClass(const std::string& classString);
        void SetFilterByYear(bool state);
        bool GetFilterByYear() const;
        void SetFilterByCountry(bool state);
        bool GetFilterByCountry() const;

        // database management
        void LoadDatabaseMod(const std::string& fileName);
        void RestoreDefaultDatabase();

        // additional scenario edit support
        void SetAirGroupName(const std::string& groupName);
        std::string GetAirGroupName() const;
        unsigned int GetAirUnitId() const;
        void SetAirGroupCount(unsigned int n);
        unsigned int GetAirGroupCount() const;
        void SetMagazineAddCount(unsigned int n);
        unsigned int GetMagazineAddCount() const;

        // scenario edit, randomization commands
        void SetIncludeProbability(const std::string& unit, float prob);
        float GetIncludeProbability(const std::string& unit) const;
        bool IncludeUnit(float prob) const;
        void AddRandomBox(const std::string& unit, float lon1_deg, float lon2_deg, float lat1_deg, float lat2_deg);

        // sonar
        void SetSeaState(unsigned int val);
        unsigned int GetSeaState() const;
        void SetSVP(const std::string& s);
		void SetSonarTemplate(int id);
		int GetSonarTemplate() const;
		unsigned int GetNumberSonarTemplates() const;
		std::string GetTemplateName(unsigned int id) const;

        // non-python methods
        tcGameObject* GetLastObjectAdded() const;
		void SetProgressReporting(wxProgressDialog* dlg);

        // Interface class management methods
        static object GetInterface();
        static void InitPythonClasses();
        static void AddGoalClasses();
        static void AttachDirector(tcDirector *dir) {director = dir;}
        static void AttachMapData(tcMapData *md) {mapData = md;}
        static void AttachMapOverlay(tcMapOverlay* mo) {overlay = mo;}
        static void AttachSimState(tcSimState *apSS) {simState = apSS;}
        static void AttachCommandQueue(tcCommandQueue* cq) {commandQueue = cq;}


        /**
        * Send command through command queue, used for special commands to game engine
        * such as activating the flight deck control panel. 
        */
        void SendCommand(const std::string& command);

		/// queries field info from database -amram: So I can call this from SM if UI is unavailable(no units).
		scriptinterface::tcStringTable QueryDatabase(const std::string& table, const std::string& databaseClass, const std::string& fields);
		
		/// retrieves the alliance affiliation.
		int tcScenarioInterface::GetAllianceRelationship(unsigned char alliance_a, unsigned char alliance_b) const;

		tcScenarioInterface();
		~tcScenarioInterface();
    private:

        double eventTime; ///< start time for briefing event functions
        tcGameObject* lastObjectAdded; ///< last object added to sim
        double lon_theater_deg; ///< default starting longitude for theater
		double lat_theater_deg; ///< default starting latitude for theater
		int sideCode; ///< used to toggle user's alliance in scenario, 0 means uninitialized
        bool isScenarioLocked; ///< true to block edit mode for scenario that has been loaded
        std::map<int, std::string> simpleBriefingText; ///< text for each alliance for simple briefing screen
        
        std::string airGroupName;
        unsigned int unitId; ///< reset to 1 on  airGroupName change, incremented on every add to flight deck, success or not
        unsigned int airGroupCount; ///< number to add at once (used by scripts, not directly in this class)
        unsigned int magazineAddCount; ///< number to add at once to magazine (used by scripts)
        wxArrayString filterOptions; ///< list of string options for platform filtering
        bool filterByYear; ///< filters platforms by current scenario date
        bool filterByCountry; ///< filters platforms by country of active side

		wxProgressDialog* progressDialog;

        static tcDirector* director;
        static tcMapData* mapData;
        static tcSimState* simState;
        static tcMapOverlay* overlay;
        static tcCommandQueue* commandQueue; // for requesting GUI commands

        void ApplySpecialFiltering(const std::string& className, tcStringArray& stringArray);
    };

}

#endif

