/**
**  @file tcSimPythonInterface.h
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

#ifndef __tcSimPythonInterface_h__
#define __tcSimPythonInterface_h__

#if _MSC_VER > 1000
#pragma once
#endif

// Python interface to tcPlatformObject for scripting
#include "wx/wx.h"

#include "tcPythonInterface.h"
#include "tcPlatformObject.h"
#include "tcSubInterface.h"
#include "tcTrackInterface.h"
#include "tcPlatformInterface.h"
#include "tcFlightPortInterface.h"
#include "tcPanelInterface.h"
#include "tcGroupInterface.h"
#include "tcWeaponInterface.h"
#include <map>


class tcMenu;
class tcDirector;


class tcAllianceSensorMap;
class tcSoundConsole;
class tcCommandQueue;
class tcMapOverlay;
class tcStream;
class tcCommandStream;
class tcTacticalMapView;

namespace ai
{
    class ScriptedTask;
    class ScriptedTaskInterface;
}
using ai::ScriptedTask;
using ai::ScriptedTaskInterface;


/**
* Embedded python scripting interface code.
* Contains all python interface classes.
*/
namespace scriptinterface 
{
	class tcScenarioInterface;

    /**
    * Interface class for creating popup mouse menus.
    */
    class tcMenuInterface 
    {
    public:
        void AddItem(std::string caption, std::string command);
        void AddItemWithParam(std::string caption, std::string command, int param);
        void AddItemWithTextParam(std::string caption, std::string command, std::string textParam);
        void AddItemUI(std::string caption, std::string callback, std::string input);
        void AddItemUIWithParam(std::string caption, std::string callback, 
                                std::string input, int param);
		void AddItemUIWithTextParam(const std::string& caption, const std::string& callback, 
			const std::string& input, const std::string &textParam);
        void BeginSubMenu();
        void Clear();
        void EndSubMenu();
        void SetStayOpen(bool state);

        tcMenuInterface();
        virtual ~tcMenuInterface();

        static void AttachMenu(tcMenu *apMenu) {mpMenu = apMenu;}
    private:
        static tcMenu* mpMenu;

        bool UITypeIsValid(const std::string& text) const;
    };


    /**
    * Singleton class
    */
    class tcSimPythonInterface : public tcPythonInterface 
    {
    public:
        void SetUnitInfo(tcPlatformObject *apObj);
        void Test();

        // must be better way vs. all of these Attach methods?
        void AttachCommandQueue(tcCommandQueue *cq);
        void AttachConsole(tcSoundConsole *apConsole);
        void AttachDirector(tcDirector *dir);
        void AttachMapData(tcMapData *md);
        void AttachMapOverlay(tcMapOverlay* mo);
        void AttachMenu(tcMenu *apMenu) {tcMenuInterface::AttachMenu(apMenu);}
        void AttachPanel(tcPanel *apPanel) {tcPanelInterface::AttachPanel(apPanel);}
        void AttachSensorMap(tcAllianceSensorMap *apSM) {tcTrackInterface::SetSensorMap(apSM);}
        void AttachSimState(tcSimState *apSimState);
        void AttachTacticalMap(tcTacticalMapView* mv);

		void BuildEditMenu(); ///< top-level edit menu
		void BuildGroupMenu(); ///< creates menu customized to group of units
        void BuildPlatformMenu(); ///< creates menu customized to unit 
		void BuildPlatformEditMenu();
        void BuildGroupEditMenu();
        void BuildTrackMenu(); ///< creates menu for track commands
        void BuildWeaponMenu();
        void BuildWeaponEditMenu();

        void BuildFlightPortPanel();
        int CallPython(const char *commandtext, const char *errortext);
        bool CallTaskScript(ScriptedTask* task, const char* azCommand);
		tcPlatformObject* GetHookedObj() const;
		tcFlightPort* GetHookedObjFlightPort();
        bool IsHooked(long id) const;

        void GetObjectStringByMode(char *str); // gets name of python object to pass to python function
        tcScenarioInterface* GetScenarioInterface() const;

        void ClearScenario();
        void LoadScenario(const char *filePath, const char *fileName); ///< loads scenario from Python script file

        void ProcessCommand(const std::string& command, const std::vector<long>& id, 
            int param = -1, std::string textParam = "");
		void ProcessCommandWithArguments(const std::string& command, const std::vector<long>& id, 
            const std::string& argString);
        void ProcessCallback(const std::string& command, const std::vector<long>& id);
        void ProcessCallback(const std::string& command, const std::vector<long>& id, 
			float afData, int param, const std::string& textParam);
        void ProcessCallback(const std::string& command, const std::vector<long>& id, 
			float afData1, float afData2, int param, const std::string& textParam);
		void ProcessCallback(const std::string& command, const std::vector<long>& id, 
			long anData, int param, const std::string& textParam);
		void ProcessCallback(const std::string& command, const std::vector<long>& id, 
			const std::string& text, int param = -1);
        void ProcessCallbackArgList(const std::string& command, const std::vector<long>& id, 
										   const std::string& arguments);
		void ProcessCallbackString(const std::string& command, const std::vector<long>& id);
        void ProcessHotKey(unsigned int key, unsigned int flags);
        void ProcessHotKeyGroup(unsigned int key, unsigned int flags);
		void ProcessDoubleClickHook(unsigned int flags);
        void ProcessSecondaryHook(long id);
        void PushMode();
        void PopMode();
		void ReimportModules(); ///< allows python code to be changed while game is running
        void ReportError(const char* text);
        void SelectFlightInterface(); ///< change to flightport menu
        void SelectTrackMenu(); ///< change to track menu
        void SelectUnitMenu(); ///< change to unit menu
		void SelectGroupMenu(); ///< change to group menu
		void SelectGameMenu(); ///< change to top-level game menu (no platforms hooked)
        void SelectWeaponMenu(); ///< change to weapon menu, for tcWeaponObject's
        void SetMenuPlatform(long anID);
		void SetMenuGroup(const std::vector<long>& unitIds);
		
        void UpdateForDestroyedPlatform(long id);

		void Update(); ///< call periodically to send output and error text to console

		void FlushLogs();

		tcCommandStream& operator<<(tcCommandStream& stream);
		tcCommandStream& operator>>(tcCommandStream& stream);
		
		void ClearNewCommand();
		bool HasNewCommand() const;

        static tcSimPythonInterface* Get(); ///< singleton accessor

    private:
        tcSimPythonInterface();
        virtual ~tcSimPythonInterface();

		bool showPythonErrors; ///< true to send python errors to F7 console in game

        object PlatformInterface; ///< python tcPlatformInterface
        tcPlatformInterface *platformInterface; ///< C++ handle to PlatformInterface

		object GroupInterfaceType;
		object GroupInterface; ///< python tcGroupInterface
		tcGroupInterface* groupInterface; ///< C++ handle to GroupInterface

        object HookedPlatformInterface; ///< interface for hooked platform for menu
        tcPlatformInterface *hookedInterface; ///< C++ handle to hooked plat interface
        object MenuInterfaceType;
        object MenuInterface;
        object PanelInterfaceType;
        object PanelInterface;
        object SubInterfaceType;
        object TrackInterfaceType;
        object TrackInterface;
        object FlightPortInterface;
        tcFlightPortInterface *flightPortInterface; ///< C++ handle to flightport interface
        
        object WeaponInterfaceType;
        object WeaponInterface;
        tcWeaponInterface* weaponInterface;


        object ScenarioInterface;
        tcScenarioInterface* scenarioInterface; ///< C++ handle to scenario interface
        tcDirector *director;
        tcSimState *mpSimState;
        tcPlatformObject *mpHookedObj;
        tcSoundConsole *mpConsole;
        tcMapOverlay* overlay;

        ScriptedTaskInterface* taskInterface;
        object TaskInterfaceObject;

        enum teInterfaceMode 
		{
            UNIT_MENU,
			GROUP_MENU,
            TRACK_MENU,
            FLIGHT_MENU,
			GAME_MENU, ///< top-level menu with nothing hooked
            WEAPON_MENU
        } meMenuMode;

        bool isModePushed; ///< true if mode is pushed and available for recall with PopMode
        teInterfaceMode pushedMode;
        std::vector<long> pushedPlatformIds;

		struct ClientCommand
		{
            char menuMode;
			std::vector<long> idList;
			std::string commandText;
		};
		std::vector<ClientCommand> clientCommands; ///< commands to send to server

        std::map<std::string, bool> commandBypass;

        bool BypassClientCommand(const std::string& command) const;
        void InitCommandBypass();
		void UpdateLogs();
    };
}

#endif // __tcSimPythonInterface_h__

