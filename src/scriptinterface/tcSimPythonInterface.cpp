/**
**  @file tcSimPythonInterface.cpp
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

#include "tcSimPythonInterface.h"
#include "simmath.h"
#include "tcSimState.h"
#include "tcMapOverlay.h"
#include "tcMenu.h"
#include "tcTrackInterface.h"
#include "tcPlatformInterface.h"
#include "tcScenarioInterface.h"
#include "tcMissionInterface.h"
#include "tcSoundConsole.h"
#include "tcDirector.h"
#include "tcMessageInterface.h"
#include "tcTime.h"
#include "network/tcMultiplayerInterface.h"

#include "ai/ScriptedTask.h"
#include "ai/ScriptedTaskInterface.h"
#include "common/tcStream.h"
#include "common/tcObjStream.h"
#include "common/tcOptions.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif 


using namespace boost::python;
using namespace ai;
using namespace network;

namespace scriptinterface 
{
    /**
    * Adds a menu item with command string
    * @param caption caption for menu item
    * @param command command string for item
    */
    void tcMenuInterface::AddItem(std::string caption, std::string command) 
    {
        if (mpMenu == NULL) {return;}
        mpMenu->AddItem(caption, command);
    }
    /**
    * Adds a menu item with command string and command parameter
    * @param caption caption for menu item
    * @param command command string for item
    * @param param integer command parameter
    */
    void tcMenuInterface::AddItemWithParam(std::string caption, std::string command, int param) 
    {
        if (mpMenu == NULL) {return;}
        mpMenu->AddItem(caption, command, param);
    }

    /**
    * Adds a menu item with command string and command parameter
    * @param caption caption for menu item
    * @param command command string for item
    * @param textParam std::string parameter
    */
    void tcMenuInterface::AddItemWithTextParam(std::string caption, std::string command, 
        std::string textParam) 
    {
        if (mpMenu == NULL) {return;}
        mpMenu->AddItem(caption, command, textParam);
    }

    /**
    * Adds a menu item that gets a coordinate or target from the user via a mouse click
    * @param caption caption for menu item
    * @param callback script to call after user data is obtained
    * @param input type of user data: "Heading", "Target", or "Datum"
    */
    void tcMenuInterface::AddItemUI(std::string caption, std::string callback, std::string input) 
    {
        AddItemUIWithParam(caption, callback, input, -1);
    }

    /**
    * Adds a menu item that gets a coordinate or target from the user via a mouse click
    * @param caption caption for menu item
    * @param callback script to call after user data is obtained 
    * @param input type of user data: "Null", "Heading", "Target", or "Datum" ("Null" is a way to treat as callback for multiplayer purposes)
    * @param param integer callback parameter for additional information
    */
    void tcMenuInterface::AddItemUIWithParam(std::string caption, std::string callback, 
        std::string input, int param)
    {
        if (mpMenu == NULL) {return;}
     
        if (UITypeIsValid(input))
        {
            mpMenu->AddItemUI(caption, callback, input, param);
        }
        else
        {
            fprintf(stderr, "tcMenuInterface::AddItemUIWithParam -- Bad UI input type (%s)\n",
                input.c_str());
        }
    }

    /**
    * Adds a menu item that gets a coordinate or target from the user via a mouse click
    * @param caption caption for menu item
    * @param callback script to call after user data is obtained 
    * @param input type of user data: "Null", "Heading", "Target", or "Datum" ("Null" is a way to treat as callback for multiplayer purposes)
    * @param textParam string callback parameter for additional information
    */
	void tcMenuInterface::AddItemUIWithTextParam(const std::string& caption, const std::string& callback, 
			const std::string& input, const std::string &textParam)
	{
        if (mpMenu == NULL) {return;}

        if (UITypeIsValid(input))
        {
            mpMenu->AddItemUI(caption, callback, input, textParam);
        }
        else
        {
            fprintf(stderr, "tcMenuInterface::AddItemUIWithTextParam -- Bad UI input type (%s)\n",
                input.c_str());
        }
	}


    /**
    * Begin a submenu in current menu
    */
    void tcMenuInterface::BeginSubMenu() {
        if (mpMenu == NULL) {return;}
        mpMenu->BeginSubMenu();
    }

    /**
    * Clear menu
    */
    void tcMenuInterface::Clear() {
        if (mpMenu == NULL) {return;}
        mpMenu->Clear();
    }

    /**
    * End submenu in current menu
    */
    void tcMenuInterface::EndSubMenu() {
        if (mpMenu == NULL) {return;}
        mpMenu->EndSubMenu();
    }

    void tcMenuInterface::SetStayOpen(bool state)
    {
        tcMenu::SetStayOpen(state);
    }

    bool tcMenuInterface::UITypeIsValid(const std::string& text) const
    {
        wxString s(text.c_str());
        s = s.BeforeFirst(' ');

        bool valid = (s == "Null") ||
                     (s == "Heading") ||
                     (s == "Target") ||
                     (s == "Datum") ||
                     (s == "Box") ||
                     (s == "Text") ||
                     (s == "File") ||
                     (s == "Paragraph");

        return valid;
    }

    tcMenu* tcMenuInterface::mpMenu = NULL;

    tcMenuInterface::tcMenuInterface()
    {
    }

    tcMenuInterface::~tcMenuInterface()
    {
    }

}


/**
* Singleton accessor
*/
tcSimPythonInterface* tcSimPythonInterface::Get()
{
    static tcSimPythonInterface instance;

    return &instance;
}



/**
* Loads state from command stream
* MetaString of stream must be set to player name for control validation
*/
tcCommandStream& tcSimPythonInterface::operator<<(tcCommandStream& stream)
{
	wxASSERT(!mpSimState->IsMultiplayerClient());

	const std::string& playerName = stream.GetMetaString();

    tcMultiplayerInterface* multiplayerInterface = tcMultiplayerInterface::Get();
    int connId = multiplayerInterface->GetPlayerConnectionId(playerName);
    if (connId == -1)
    {
        fprintf(stderr, "tcSimPythonInterface::operator<< - Bad playername (%s)\n",
            playerName.c_str());
        return stream;
    }
    tcPlayerStatus playerStatus = multiplayerInterface->GetPlayerStatus(connId);
    
    tcAllianceSensorMap* playerSensorMap = mpSimState->GetSensorMap()->GetMap(playerStatus.alliance);
    if (playerSensorMap == 0)
    {
        fprintf(stderr, "tcSimPythonInterface::operator<< - Player has no sensor map, bad alliance? (%s, %d)\n",
            playerName.c_str(), playerStatus.alliance);
        return stream;
    }
    tcAllianceSensorMap* previousSensorMap = tcTrackInterface::GetSensorMap(); // save current map
    tcTrackInterface::SetSensorMap(playerSensorMap);

    unsigned char prevAlliance = mpSimState->mpUserInfo->GetOwnAlliance();
    mpSimState->mpUserInfo->SetOwnAlliance(playerStatus.alliance);

	unsigned char nCommands;
	stream >> nCommands;

	for (unsigned char n=0; n<nCommands; n++)
	{
        char menuMode;
        stream >> menuMode;

		unsigned char nId;
		stream >> nId;

		std::vector<long> idList;
		for (unsigned char n=0; n<nId; n++)
		{
			long id;
			stream >> id;
			idList.push_back(id);
		}

		std::string command;
		stream >> command;

		if (command.size() < 128)
		{
			bool playerHasControl = true;
			for (unsigned int n=0; (n<idList.size()) && playerHasControl; n++)
			{
				tcGameObject* obj = mpSimState->GetObject(idList[n]);
                playerHasControl = (obj != 0) ? obj->IsControlledBy(playerName) : false;
                if (obj == 0)
                {
                    fprintf(stderr, "tcSimPythonInterface::operator<< - bad idList passed, menuMode: %d\n",
                        int(menuMode));
                }
			}

            bool trackMode = menuMode == TRACK_MENU;

            if (!trackMode)
            {
                if (playerHasControl)
                {
#ifdef _DEBUG
                    long id0 = (idList.size() > 0) ? idList[0] : -1;
                    fprintf(stdout, "Script cmd (%d/%d): %s\n", id0, idList.size(), command.c_str());
#endif
                    ProcessCallbackString(command, idList);
                }
                else
                {
                    fprintf(stderr, "Script command issued for obj that player does not control, "
                        "player: %s\n", playerName.c_str());
                }
            }
            else // track mode
            {
                if (!playerHasControl)
                {
#ifdef _DEBUG
                    long id0 = (idList.size() > 0) ? idList[0] : -1;
                    fprintf(stdout, "Script track cmd (%d/%d): %s\n", id0, idList.size(), command.c_str());
#endif
                    ProcessCallbackString(command, idList);
                }
                else
                {
                    fprintf(stderr, "Script track command issued for obj that player controls, "
                        "player: %s\n", playerName.c_str());
                }
            }
		}
		else
		{
			fprintf(stderr, "Overlength command string received from client\n");
			wxASSERT(false);
		}
	}

    tcTrackInterface::SetSensorMap(previousSensorMap); // restore sensor map
    mpSimState->mpUserInfo->SetOwnAlliance(prevAlliance);

    return stream;
}


/**
* Saves state to command stream
*/
tcCommandStream& tcSimPythonInterface::operator>>(tcCommandStream& stream)
{
	wxASSERT(mpSimState->IsMultiplayerClient());

	wxASSERT(clientCommands.size() < 16);

	unsigned char nCommands = clientCommands.size();
	stream << nCommands;

	for (unsigned char n=0; n<nCommands; n++)
	{
		ClientCommand& cmd = clientCommands[n];

        stream << cmd.menuMode;

		wxASSERT(cmd.idList.size() < 256);
		unsigned char nId = cmd.idList.size();
		stream << nId;

		for (unsigned char n=0; n<nId; n++)
		{
			long id = cmd.idList[n];
			stream << id;
		}

		stream << cmd.commandText;
	}

    return stream;
}

void tcSimPythonInterface::ClearNewCommand()
{
	clientCommands.clear();
}

bool tcSimPythonInterface::HasNewCommand() const
{
	return (clientCommands.size() > 0);
}

void tcSimPythonInterface::InitCommandBypass()
{
    wxASSERT(commandBypass.size() == 0);

    commandBypass["TakeControl"] = true;
    commandBypass["TakeControlGroup"] = true;
    commandBypass["EnableFormationEdit"] = true;
    commandBypass["DisableFormationEdit"] = true;
    commandBypass["ShowFlightPanel"] = true;
    commandBypass["ShowPlatformPanel"] = true;
    commandBypass["ReleaseControlGroup"] = true;
}


// write apObj
void tcSimPythonInterface::SetUnitInfo(tcPlatformObject *apObj) {
    tcPlatformInterface::SetObj(apObj);
}



/**
* Task script for ai
* @return false if error with task
*/
bool tcSimPythonInterface::CallTaskScript(ScriptedTask* task, const char* azCommand) 
{
    wxASSERT(taskInterface);

    taskInterface->SetTask(task);

    try 
    {   
        handle<>( PyRun_String(azCommand
            , Py_file_input, main_namespace.ptr(), main_namespace.ptr()) );
        return true;
    }
    catch (error_already_set) 
    {
        // handle the exception in some way
        fprintf(stderr,"Exception occured in CallTaskScript\n");
        PyErr_Print();
        return false;
    }
}

tcPlatformObject* tcSimPythonInterface::GetHookedObj() const
{
	return mpHookedObj;
}

tcFlightPort* tcSimPythonInterface::GetHookedObjFlightPort()
{
    tcFlightOpsObject* flightOps = dynamic_cast<tcFlightOpsObject*>(mpHookedObj);
    if (flightOps == 0) return 0;
	return flightOps->GetFlightPort();
}

void tcSimPythonInterface::AttachCommandQueue(tcCommandQueue *cq) 
{
    tcPlatformInterface::AttachCommandQueue(cq);
    tcGroupInterface::AttachCommandQueue(cq);
    tcScenarioInterface::AttachCommandQueue(cq);
}

void tcSimPythonInterface::AttachConsole(tcSoundConsole *apConsole) 
{
    tcPlatformInterface::AttachConsole(apConsole);
    mpConsole = apConsole;
}

void tcSimPythonInterface::AttachDirector(tcDirector *dir)
{
    tcScenarioInterface::AttachDirector(dir);
    director = dir;
}

void tcSimPythonInterface::AttachMapData(tcMapData *md)
{
	tcPlatformInterface::AttachMapData(md);
    tcScenarioInterface::AttachMapData(md);
}

void tcSimPythonInterface::AttachMapOverlay(tcMapOverlay* mo)
{
    overlay = mo;
    tcScenarioInterface::AttachMapOverlay(mo);
    tcFlightPortInterface::AttachMapOverlay(mo);
}

void tcSimPythonInterface::AttachSimState(tcSimState *apSimState) 
{
    tcPlatformInterface::AttachSimState(apSimState);
    tcScenarioInterface::AttachSimState(apSimState);
    tcFlightPortInterface::AttachSimState(apSimState);
    mpSimState=apSimState;
}

void tcSimPythonInterface::AttachTacticalMap(tcTacticalMapView* mv)
{
    tcPlatformInterface::AttachTacticalMap(mv);
}


void tcSimPythonInterface::BuildEditMenu()
{
	CallPython("Menu.BuildEditMenu(UserMenu, ScenarioManager)",
		"Exception occured in BuildEditMenu");
}

/**
* Creates menu customized to selected group of units
*/
void tcSimPythonInterface::BuildGroupMenu() 
{
    try 
	{   
        handle<>( PyRun_String("Menu.BuildGroupMenu(UserMenu, GroupInfo)"
            , Py_file_input, main_namespace.ptr(), main_namespace.ptr()) );
    }
    catch(error_already_set) 
	{
        fprintf(stderr,"Exception occured in BuildGroupMenu\n");
        PyErr_Print();
    }   
}

/**
* creates platform menu customized to selected unit 
*/
void tcSimPythonInterface::BuildPlatformMenu() 
{
	//wxASSERT(mpHookedObj != 0);
	if (mpHookedObj == 0) return; // occurs normally when missile is hooked

    try 
	{   
        handle<>( PyRun_String("Menu.BuildUnitMenu(UserMenu, HookedUnitInfo)"
            , Py_file_input, main_namespace.ptr(), main_namespace.ptr()) );
    }
    catch(error_already_set) 
	{
        fprintf(stderr,"Exception occured in BuildPlatformMenu\n");
        PyErr_Print();
    }   
}

/**
* Version for mission editor mode
*/
void tcSimPythonInterface::BuildPlatformEditMenu() 
{
    try 
	{   
        handle<>( PyRun_String("Menu.BuildUnitEditMenu(UserMenu, HookedUnitInfo)"
            , Py_file_input, main_namespace.ptr(), main_namespace.ptr()) );
    }
    catch(error_already_set) 
	{
        fprintf(stderr,"Exception occured in BuildPlatformEditMenu\n");
        PyErr_Print();
    }   
}

/**
* Version for mission editor mode
*/
void tcSimPythonInterface::BuildGroupEditMenu() 
{
    try 
	{   
        handle<>( PyRun_String("Menu.BuildGroupEditMenu(UserMenu, GroupInfo)"
            , Py_file_input, main_namespace.ptr(), main_namespace.ptr()) );
    }
    catch(error_already_set) 
	{
        fprintf(stderr,"Exception occured in BuildGroupEditMenu\n");
        PyErr_Print();
    }   
}

void tcSimPythonInterface::BuildWeaponMenu()
{
    try 
	{   
        handle<>( PyRun_String("Menu.BuildWeaponMenu(UserMenu, WeaponInfo)"
            , Py_file_input, main_namespace.ptr(), main_namespace.ptr()) );
    }
    catch(error_already_set) 
	{
        fprintf(stderr,"Exception occured in BuildWeaponMenu\n");
        PyErr_Print();
    }   
}

void tcSimPythonInterface::BuildWeaponEditMenu()
{
    try 
	{   
        handle<>( PyRun_String("Menu.BuildWeaponEditMenu(UserMenu, WeaponInfo)"
            , Py_file_input, main_namespace.ptr(), main_namespace.ptr()) );
    }
    catch(error_already_set) 
	{
        fprintf(stderr,"Exception occured in BuildWeaponEditMenu\n");
        PyErr_Print();
    }   
}

/* If menu platform has a flightport, get a pointer to it and pass the
** pointer to the FlightPortInterface python object. 
** Then pass PanelInterface, FlightPortInterface, and UnitInfo to python 
** script to build the panel object.
*/
void tcSimPythonInterface::BuildFlightPortPanel() 
{

    tcFlightPort* flightport = GetHookedObjFlightPort();
    if (flightport == NULL) 
    {
        /*
        tcFlightPortInterface::SetObj(NULL);
        FlightPortInterface.attr("GetLocalObj")(); // load through this call   
        */
        flightPortInterface->SetFlightPort(NULL);
        tcPanelInterface::Reset();// sets to "no data available" state
        return;
    }
    flightPortInterface->SetFlightPort(flightport);
    /*
    tcFlightPortInterface::SetObj(flightport);
    FlightPortInterface.attr("GetLocalObj")(); // load through this call
    */
    CallPython("Menu.BuildFlightPortPanel(UserPanel, FlightPortInfo, HookedUnitInfo)",
                "Exception occured in BuildFlightPortMenu\n");
}

// creates platform menu customized to object 
void tcSimPythonInterface::BuildTrackMenu() {
    CallPython("Menu.BuildTrackMenu(UserMenu, HookedTrackInfo)",
                "Exception occured in BuildTrackMenu\n"); 
}

/**
* @return true if this command should be executed on client instead of sending to server
* Multiplayer method
*/
bool tcSimPythonInterface::BypassClientCommand(const std::string& command) const
{
    std::map<std::string, bool>::const_iterator iter = 
        commandBypass.find(command);
    return (iter != commandBypass.end());
}

/**
** Executes command line in command text in embedded Python
** using PyRun_String. If there is an exception an error message
** is output to various destinations. 
** @return 0 on success, non-zero for error
*/
int tcSimPythonInterface::CallPython(const char *commandtext, const char *errortext)
{
    try 
    {   
        handle<> ignored( PyRun_String(commandtext
            , Py_file_input, main_namespace.ptr(), main_namespace.ptr()) );
        return 0;
    }
    catch (error_already_set) 
    {
        ReportError(errortext);
        PyErr_Print();
        return 1;
    }   
}

/* Copies name of python global object to pass to python function.
** It might be better to encode the object type into the command itself,
** vs. relying on the meMenuMode. The HotKey case doesn't have an active
** menu. */
void tcSimPythonInterface::GetObjectStringByMode(char *str)
{
	switch (meMenuMode)
	{
	case UNIT_MENU:
		strcpy(str, "HookedUnitInfo");
		return;
	case GROUP_MENU:
		strcpy(str, "GroupInfo");
		return;
	case TRACK_MENU:
		strcpy(str, "HookedTrackInfo");
		return;
	case FLIGHT_MENU:
		strcpy(str, "FlightPortInfo");
		return;
	case GAME_MENU:
		strcpy(str, "ScenarioManager");
		return;
    case WEAPON_MENU:
        strcpy(str, "WeaponInfo");
        return;
	}
}

tcScenarioInterface* tcSimPythonInterface::GetScenarioInterface() const
{
    wxASSERT(scenarioInterface);
    
    return scenarioInterface;
}


void tcSimPythonInterface::ClearScenario()
{
    wxASSERT(mpSimState);
    wxASSERT(director);
    wxASSERT(overlay);

    // start with clear state for new scenario
    mpSimState->Clear(); 

    // clear db if using dynamic load so that only units from scenario are in memory
    tcDatabase* database = tcDatabase::Get();
    if (database->IsUsingDynamicLoad() && (!mpSimState->IsMultiplayerClient())) 
    {
        database->ClearForNewScenario(); // (let server clear database for multiplayer client mode)
    }

    director->ClearEvents();
    overlay->ClearMapObjects();
}

/**
* Loads scenario from Python script file. File should have
* method "CreateScenario(scenario_manager)".
*
* @param filePath complete file path, e.g. "scenario\\fastattack.txt"
*        filePath is only used for information when logging error
* @param fileName just the file name, e.g. "fastattack.txt"
*/
void tcSimPythonInterface::LoadScenario(const char *filePath, const char *fileName)
{
    wxASSERT(mpSimState);
    wxASSERT(director);
    wxASSERT(overlay);

    // start with clear state for new scenario
    ClearScenario();

    wxString cmdText;
    wxString errText;

    if (strlen(fileName) < 2) return; // work-around to support clear only

	wxString fileNameWx(fileName);
	if (fileNameWx.Contains(".py"))
	{
		// remove .py extension from fileName
		int findIdx = fileNameWx.Find(".py");
		fileNameWx = fileNameWx.SubString(0, findIdx - 1);
		fprintf(stdout, "tcSimPythonInterface -- Loading scenario %s\n", fileNameWx.c_str());
	}


    // import scenario file
    //cmdText = wxString::Format("from %s import *\n", fileNameWx.c_str());
    cmdText = wxString::Format("import %s\nreload(%s)\nfrom %s import *\n", fileNameWx.c_str(), fileNameWx.c_str(), fileNameWx.c_str());
    //cmdText = wxString::Format("execfile(%s)\n", fileNameWx.c_str());
    errText = wxString::Format("Error importing scenario file: %s\n", filePath);
    int errorCode = CallPython(cmdText.c_str(), errText.c_str());
    if (errorCode != 0)
    {
        mpSimState->Clear(); 
        director->ClearEvents();
        overlay->ClearMapObjects();
        return;
    }

    // call CreateScenario method with ScenarioManager global object
    errorCode = CallPython("CreateScenario(ScenarioManager)\n", "Error with CreateScenario method\n");
    if (errorCode != 0)
    {
        mpSimState->Clear(); 
        director->ClearEvents();
        overlay->ClearMapObjects();
        return;
    }


    // call CreateBriefing method with ScenarioManager global object
    // ignore error here
    //CallPython("CreateBriefing(ScenarioManager)\n", "Error with CreateBriefing method\n");
}

/**
*
*/
void tcSimPythonInterface::ProcessCommand(const std::string& command, const std::vector<long>& id, 
                                          int param, std::string textParam) 
{
    PushMode();
    SetMenuGroup(id);

    std::string s = "Menu.";

    s += command;
    s += "(";

    char zObject[64];
    GetObjectStringByMode(zObject);
    s += zObject;

    if (param != -1) // add parameter to python call if param != -1
    {
        char zBuff[64];
        sprintf(zBuff,", %d", param);
        s += zBuff;
    }
    else if (textParam.length() > 0)
    {
        s += ",'";
        s += textParam;
        s += "'";
    }

    s += ")\n";


	if (!mpSimState->IsMultiplayerClient() || BypassClientCommand(command))
	{
		CallPython(s.c_str(), "Exception occurred in ProcessCommand\n"); 
	}
	else
	{
		ClientCommand cmd;
        cmd.menuMode = meMenuMode;
		cmd.idList = id;
		cmd.commandText = s;

        if (cmd.idList.size() == 0)
        {
            cmd.idList = groupInterface->GetUnits();
        }

		clientCommands.push_back(cmd);
	}


    PopMode();
}

/**
* Calls python command of the form Menu.<command>(<command object><argString>)
* argString should start with a comma if it is non-empty
*/
void tcSimPythonInterface::ProcessCommandWithArguments(const std::string& command, const std::vector<long>& id, 
													   const std::string& argString)
{
	PushMode();
	SetMenuGroup(id);

	std::string s = "Menu.";

	s += command;
	s += "(";

	char zObject[64];
	GetObjectStringByMode(zObject);
	s += zObject;

	s += argString;

	s += ")\n";

    if (!mpSimState->IsMultiplayerClient())
    {
        CallPython(s.c_str(), "Exception occurred in ProcessCommand\n"); 
    }
    else
    {
        ClientCommand cmd;
        cmd.menuMode = meMenuMode;
        cmd.idList = id;
        cmd.commandText = s;

        if (cmd.idList.size() == 0)
        {
            cmd.idList = groupInterface->GetUnits();
        }

        clientCommands.push_back(cmd);
    }

    PopMode();
}

/**
* Saves menu state. Restore with PopMode()
*/
void tcSimPythonInterface::PushMode()
{
    pushedMode = meMenuMode;

    pushedPlatformIds = groupInterface->GetUnits();

    isModePushed = true;
}

/**
* Recalls menu state after call to push mode.
*/
void tcSimPythonInterface::PopMode()
{
    if (!isModePushed)
    {
        fprintf(stderr, "tcSimPythonInterface::PopMode() - Mode not pushed\n");
        return;
    }

    meMenuMode = pushedMode;

    // reselect menu platform
    SetMenuGroup(pushedPlatformIds);

    pushedPlatformIds.clear();

    isModePushed = false;
}


/**
* Version without any data (added for multiplayer client "Null" callback support)
*/
void tcSimPythonInterface::ProcessCallback(const std::string& command, const std::vector<long>& id) 
{
    PushMode();
    SetMenuGroup(id);

    if ((mpHookedObj == 0)  && (meMenuMode != GAME_MENU) && (meMenuMode != WEAPON_MENU) && (meMenuMode != GROUP_MENU))
    {
        PopMode();
        return;
    }
    char zBuff[128];
    char zObject[64];

    GetObjectStringByMode(zObject);
    
    sprintf(zBuff, "Menu.%s(%s)\n", command.c_str(), zObject);
    

	if (!mpSimState->IsMultiplayerClient())
	{
		CallPython(zBuff, "Exception occurred in ProcessCallback\n"); 
	}
	else
	{
		ClientCommand cmd;
        cmd.menuMode = meMenuMode;
		cmd.idList = id;
		cmd.commandText = std::string(zBuff);

		clientCommands.push_back(cmd);
	}

    PopMode();
}


/**
*
*/
void tcSimPythonInterface::ProcessCallback(const std::string& command, const std::vector<long>& id, 
                                           float afData, int param, const std::string& textParam) 
{
    PushMode();
    SetMenuGroup(id);

    if ((mpHookedObj == 0)  && (meMenuMode != GAME_MENU) && (meMenuMode != WEAPON_MENU) && (meMenuMode != GROUP_MENU))
    {
        PopMode();
        return;
    }
    char zBuff[128];
    char zObject[64];


    GetObjectStringByMode(zObject);
    
	if ((param == -1) && (textParam.size() == 0))
	{
        sprintf(zBuff, "Menu.%s(%s,%.3f)\n",command.c_str(),zObject,afData);
	}
    else if (param != -1)
	{
        sprintf(zBuff, "Menu.%s(%s,%.3f,%d)\n",command.c_str(),zObject,afData,param);
	}
	else
	{
		sprintf(zBuff, "Menu.%s(%s,%.3f,'%s')\n", command.c_str(), zObject, afData, textParam.c_str());
	}

	if (!mpSimState->IsMultiplayerClient())
	{
		CallPython(zBuff, "Exception occurred in ProcessCallback\n"); 
	}
	else
	{
		ClientCommand cmd;
        cmd.menuMode = meMenuMode;
		cmd.idList = id;
		cmd.commandText = std::string(zBuff);

		clientCommands.push_back(cmd);
	}

    PopMode();
}


/**
* version for sending lat/lon coordinates
*/
void tcSimPythonInterface::ProcessCallback(const std::string& command, const std::vector<long>& id, 
                                           float afData1, float afData2, int param, const std::string& textParam) 
{
    PushMode();
    SetMenuGroup(id);

    if ((mpHookedObj == 0)  && (meMenuMode != GAME_MENU) && (meMenuMode != WEAPON_MENU) && (meMenuMode != GROUP_MENU))
    {
        PopMode();
        return;
    }
    char zBuff[128];
    char zObject[64];

    GetObjectStringByMode(zObject);
	if ((param == -1) && (textParam.size() == 0))
	{
        sprintf(zBuff,"Menu.%s(%s,%f,%f)\n",command.c_str(),zObject,afData1,afData2);
	}
    else if (param != -1)
    {
        sprintf(zBuff,"Menu.%s(%s,%f,%f,%d)\n",
                    command.c_str(),zObject,afData1,afData2,param);
    }
	else
	{
        sprintf(zBuff,"Menu.%s(%s,%f,%f,'%s')\n",
                    command.c_str(), zObject, afData1, afData2, textParam.c_str());
	}



	if (!mpSimState->IsMultiplayerClient())
	{
		CallPython(zBuff, "Exception occurred in ProcessCallback\n"); 
	}
	else
	{
		ClientCommand cmd;
        cmd.menuMode = meMenuMode;
		cmd.idList = id;
//		unsigned nId = id.size();
		
		cmd.commandText = std::string(zBuff);

		clientCommands.push_back(cmd);
	}

    PopMode();
}

/**
*
*/
void tcSimPythonInterface::ProcessCallback(const std::string& command, const std::vector<long>& id, 
                                           long anData, int param, const std::string& textParam) 
{
    PushMode();
    SetMenuGroup(id);

    if ((mpHookedObj == 0)  && (meMenuMode != GAME_MENU) && (meMenuMode != WEAPON_MENU) && (meMenuMode != GROUP_MENU))
    {
        PopMode();
        return;
    }
    char zBuff[128];
    char zObject[64];


    GetObjectStringByMode(zObject);
	if ((param == -1) && (textParam.size() == 0))
	{
        sprintf(zBuff,"Menu.%s(%s,%d)\n",command.c_str(),zObject,anData);
	}
    else if (param != -1)
	{
        sprintf(zBuff,"Menu.%s(%s,%d,%d)\n",command.c_str(),zObject,anData,param);
	}
	else
	{
		sprintf(zBuff,"Menu.%s(%s,%d,%s)\n", command.c_str(), zObject, anData, textParam.c_str());
	}


	if (!mpSimState->IsMultiplayerClient())
	{
		CallPython(zBuff, "Exception occurred in ProcessCallback\n"); 
	}
	else
	{
		ClientCommand cmd;
        cmd.menuMode = meMenuMode;
		cmd.idList = id;
		cmd.commandText = std::string(zBuff);

		clientCommands.push_back(cmd);
	}

    PopMode();
}


/**
* Yet another version for passing a string from the user
*/
void tcSimPythonInterface::ProcessCallback(const std::string& command, const std::vector<long>& id, 
										   const std::string& text, int param) 
{
    PushMode();
    SetMenuGroup(id);

    if ((mpHookedObj == 0)  && (meMenuMode != GAME_MENU) && (meMenuMode != WEAPON_MENU) && (meMenuMode != GROUP_MENU))
    {
        PopMode();
        return;
    }
    wxString zBuff;
    char zObject[64];

    GetObjectStringByMode(zObject);

    wxString niceText(text.c_str());
    size_t nReplaced = niceText.Replace("\n", "\\n");
    //nReplaced = niceText.Replace("'", ""); // try triple quote instead JUN2010

    if (param == -1)
    {
        zBuff.Printf("Menu.%s(%s,\"\"\"%s\"\"\")\n", command.c_str(), zObject, niceText.c_str());
    }
    else
    {
        zBuff.Printf("Menu.%s(%s,\"\"\"%s\"\"\",%d)\n", command.c_str(), zObject, niceText.c_str(), param);
    }

	if (!mpSimState->IsMultiplayerClient())
	{
        CallPython(zBuff.c_str(), "Exception occurred in ProcessCallback\n"); 
	}
	else
	{
		ClientCommand cmd;
        cmd.menuMode = meMenuMode;
		cmd.idList = id;
        cmd.commandText = std::string(zBuff.c_str());

		clientCommands.push_back(cmd);
	}

    PopMode();
}



/**
* Version for passing a string of arguments, use a comma after the first argument
*/
void tcSimPythonInterface::ProcessCallbackArgList(const std::string& command, const std::vector<long>& id, 
										   const std::string& arguments) 
{
    PushMode();
    SetMenuGroup(id);

    if ((mpHookedObj == 0)  && (meMenuMode != GAME_MENU) && (meMenuMode != WEAPON_MENU) && (meMenuMode != GROUP_MENU))
    {
        PopMode();
        return;
    }
    wxString zBuff;
    char zObject[128];

    GetObjectStringByMode(zObject);

 
    zBuff.Printf("Menu.%s(%s,%s)\n", command.c_str(), zObject, arguments.c_str());


	if (!mpSimState->IsMultiplayerClient())
	{
        CallPython(zBuff.c_str(), "Exception occurred in ProcessCallbackArgList\n"); 
	}
	else
	{
		ClientCommand cmd;
        cmd.menuMode = meMenuMode;
		cmd.idList = id;
        cmd.commandText = std::string(zBuff.c_str());

		clientCommands.push_back(cmd);
	}

    PopMode();
}



/**
* Version with string that includes exact call syntax
*/
void tcSimPythonInterface::ProcessCallbackString(const std::string& command, const std::vector<long>& id) 
{
    PushMode();
    SetMenuGroup(id);

    if ((mpHookedObj == 0)  && (meMenuMode != GAME_MENU) && (meMenuMode != WEAPON_MENU) && (meMenuMode != GROUP_MENU))
    {
        PopMode();
        return;
    }


	if (mpSimState->IsMultiplayerServer())
	{
#ifdef _DEBUG
		fprintf(stdout, "Processed callback string:%s (%d ids)\n", command.c_str(),
			id.size());
#endif
		CallPython(command.c_str(), "Exception occurred in ProcessCallbackString\n"); 
	}
	else
	{
		ClientCommand cmd;
        cmd.menuMode = meMenuMode;
		cmd.idList = id;
		cmd.commandText = command;

		clientCommands.push_back(cmd);
	}

    PopMode();
}

/**
* @param flags : bitfield describing keys pressed during double click: 
*     1 - shift pressed, 2 - ctrl pressed, 4 - alt pressed
*/
void tcSimPythonInterface::ProcessDoubleClickHook(unsigned int flags)
{
    char zBuff[128];
    if (mpHookedObj == 0) return;
    if (!mpSimState->mpUserInfo->IsOwnAlliance(mpHookedObj->GetAlliance())) return;

    sprintf(zBuff, "Menu.ProcessDoubleClickHook(HookedUnitInfo, %d)\n", flags);


	CallPython(zBuff, "Exception occurred in ProcessHotKey\n"); 
}


/**
* Calls the ProcessHotKey script in Menu.py with an argument based
* on whether or not a unit is hooked and, if so, the type of unit 
* hooked (own-alliance or sensor track). Initially this will only
* support the own-alliance hooked unit case 
* @param flags does nothing right now
* @param key hotkey character, send as %c to hotkey python script
*/
void tcSimPythonInterface::ProcessHotKey(unsigned int key, unsigned int flags)
{
    char zBuff[128];
    if (mpHookedObj == 0) return;
    if (!mpSimState->mpUserInfo->IsOwnAlliance(mpHookedObj->GetAlliance())) return;

    sprintf(zBuff, "Menu.ProcessHotKey(HookedUnitInfo,'%c')\n", key);


	CallPython(zBuff, "Exception occurred in ProcessHotKey\n"); 
}

/**
* Group version
*/
void tcSimPythonInterface::ProcessHotKeyGroup(unsigned int key, unsigned int flags)
{
    char zBuff[128];
    if (mpHookedObj == 0) return;
    if (!mpSimState->mpUserInfo->IsOwnAlliance(mpHookedObj->GetAlliance())) return;

    sprintf(zBuff, "Menu.ProcessHotKeyGroup(GroupInfo,'%c')\n", key);


	CallPython(zBuff, "Exception occurred in ProcessHotKey\n"); 
}

/**
* Calls the ProcessSecondaryHook script in Menu.py with an argument based
* on whether or not a unit is hooked and, if so, the type of unit 
* hooked (own-alliance or sensor track). Initially this will only
* support friendly / own-alliance hooks. Intended to be used for a quick
* mouse targeting feature.
*/
void tcSimPythonInterface::ProcessSecondaryHook(long id)
{
	char zBuff[128];
	if (mpHookedObj == 0) return;
	if (!mpSimState->mpUserInfo->IsOwnAlliance(mpHookedObj->GetAlliance())) return;

	sprintf(zBuff,"Menu.ProcessSecondaryHook(HookedUnitInfo,%d)\n",id);
	CallPython(zBuff,"Exception occurred in ProcessSecondaryHook\n");
}

void tcSimPythonInterface::ReimportModules()
{
	try 
	{   
		handle<>( PyRun_String("import AI\n"
			, Py_file_input, main_namespace.ptr(),main_namespace.ptr()) );
		handle<>( PyRun_String("import Menu\n"
			, Py_file_input, main_namespace.ptr(), main_namespace.ptr()) );
		handle<>( PyRun_String("print ''\nprint 'Re-imported modules'\n"
			, Py_file_input, main_namespace.ptr(), main_namespace.ptr()) );
	}
	catch (error_already_set) 
	{
		// handle the exception in some way
		fprintf(stderr, "tcSimPythonInterface::ReimportModules - Python error occurred during re-import\n");
		PyErr_Print();
	}
	catch (...)
	{
		fprintf(stderr,"tcSimPythonInterface::ReimportModules - Unknown exception occurred\n");
	}
}

/**
* writes error message in text out to console, if console is attached 
*/
void tcSimPythonInterface::ReportError(const char* text)
{
	fprintf(stderr,text);
	if (mpConsole == 0) return;
	mpConsole->Print(text);
}

void tcSimPythonInterface::SelectFlightInterface() 
{
	meMenuMode = FLIGHT_MENU;
}

void tcSimPythonInterface::SelectTrackMenu() 
{
	meMenuMode = TRACK_MENU;
}

void tcSimPythonInterface::SelectUnitMenu()
{
	meMenuMode = UNIT_MENU;
}

void tcSimPythonInterface::SelectGroupMenu() 
{
	meMenuMode = GROUP_MENU;
}

void tcSimPythonInterface::SelectGameMenu()
{
	meMenuMode = GAME_MENU;
}

void tcSimPythonInterface::SelectWeaponMenu()
{
	meMenuMode = WEAPON_MENU;
}

void tcSimPythonInterface::SetMenuGroup(const std::vector<long>& unitIds)
{
	// allow any units to be selected at multiplayer server, otherwise check
	if (!mpSimState->IsMultiplayerServer())
	{
		// if any of the ids are invalid or not own-alliance, then return
		for (unsigned idx=0; idx<unitIds.size(); idx++)
		{
			tcGameObject* gameObj = mpSimState->GetObject(unitIds[idx]);
			if ((!gameObj) || 
				(!mpSimState->mpUserInfo->IsOwnAlliance(gameObj->GetAlliance())))
			{
				fprintf(stderr, "tcSimPythonInterface::SetMenuGroup - null or "
					" not own-alliance id\n");
				return;
			}
		}
	}

    if (unitIds.size() > 0)
    {
        SetMenuPlatform(unitIds[0]);
    }

    // kind of a mess, needs refactoring DEC 2008
    // call SetMenuPlatform first for group so that mpHookedObj gets set. It isn't
    // used but needs to be set to get callbacks to execute !!?
    if (unitIds.size() > 1)
    {
	    meMenuMode = GROUP_MENU;
	    groupInterface->SetUnits(unitIds);
    }



}

bool tcSimPythonInterface::IsHooked(long id) const
{
    std::vector<long>& hookedId = groupInterface->GetUnits();

    for (size_t n=0; n<hookedId.size(); n++)
    {
        if (hookedId[n] == id) return true;
    }
    return false;
}


/**
* updates object reference for platform menu
*/
void tcSimPythonInterface::SetMenuPlatform(long anID) 
{
    // TODO: this causes exception on game quit sometimes
    //if (mpHookedObj && (mpHookedObj->mnID == anID)) return; // already set

    groupInterface->SetUnit(anID);

    tcTrackInterface::SetTrack(anID);

	wxASSERT(mpSimState);

    tcGameObject *pGameObj = mpSimState->GetObject(anID);

    if (!pGameObj)
	{
		mpHookedObj = 0;
		return;
	}


    if (mpSimState->mpUserInfo->IsOwnAlliance(pGameObj->GetAlliance()))
    {
        if (dynamic_cast<tcWeaponObject*>(pGameObj) == 0)
        {
            meMenuMode = UNIT_MENU;
        }
        else
        {
            meMenuMode = WEAPON_MENU;
        }
    }
    else 
    {
        meMenuMode = TRACK_MENU;
    }
    if (tcPlatformObject *pPlatformObj = dynamic_cast<tcPlatformObject*>(pGameObj))
    {
        mpHookedObj = pPlatformObj;
        hookedInterface->SetPlatform(pPlatformObj);
        weaponInterface->SetWeapon(0);
    }
    else if (tcWeaponObject* weapon = dynamic_cast<tcWeaponObject*>(pGameObj))
    {
        mpHookedObj = 0;
        hookedInterface->SetPlatform(0);
        weaponInterface->SetWeapon(weapon);
    }
    else
    {
        mpHookedObj = 0;
        hookedInterface->SetPlatform(0);
        weaponInterface->SetWeapon(0);
    }
}

void tcSimPythonInterface::Test() 
{
    try 
    {   
        handle<>( PyRun_String("hello = file('settest.txt', 'a')\n"
            "hello.write('Y is ' + str(Y) + '\\n')\n"
            "hello.close()", Py_file_input, main_namespace.ptr(), main_namespace.ptr()) );
    }
    catch (error_already_set) 
    {
        // handle the exception in some way
        fprintf(stderr,"Exception occurred in Test()\n");
        PyErr_Print();
    }
}

void tcSimPythonInterface::Update()
{
	static unsigned int lastUpdate = 0;

	// limit update frequency
	unsigned int t = tcTime::Get()->Get30HzCount();
	if ((t - lastUpdate) < 60) return;
	lastUpdate = t;

	UpdateLogs();
}

/**
* Called immediately before a platform is destroyed. Clear menu platform if necessary
*/
void tcSimPythonInterface::UpdateForDestroyedPlatform(long id)
{
    groupInterface->RemoveUnit(id);

    //tcTrackInterface::SetTrack(anID);

    if (hookedInterface->GetPlatformId() == id)
    {
        hookedInterface->SetPlatform(0);
    }
}

/**
* FEB2014 This used to be in destructor but moved out after crash in vc11
*/
void tcSimPythonInterface::FlushLogs()
{
    /*** print standard error to file ***/
	handle<> ignored( PyRun_String(
      "outfile = file('log\\pyout.txt', 'a')\n"
      "errfile = file('log\\pyerr.txt', 'a')\n"
      "outfile.write(myout.getvalue())\n"
      "errfile.write(myerr.getvalue())\n"
      "outfile.close()\n"
      "errfile.close()\n"
      , Py_file_input, main_namespace.ptr(), main_namespace.ptr()) );
}

/**
* Update output and error text logs
* If showPythonErrors is true, then send errors to "Python" message channel in game 
*/
void tcSimPythonInterface::UpdateLogs()
{
    wxString errorText;

	try 
	{   
		handle<>( PyRun_String(
			"outfile = file('log\\pyout.txt', 'a')\n"
			"errfile = file('log\\pyerr.txt', 'a')\n"
			"outfile.write(myout.getvalue())\n"
			"ErrorText = myerr.getvalue()\n"
			"errfile.write(ErrorText)\n"
			"outfile.close()\n"
			"errfile.close()\n"
			"myout.truncate(0)\n"
			"myerr.truncate(0)\n"
			, Py_file_input, main_namespace.ptr(), main_namespace.ptr()) );

		if (showPythonErrors)
		{
			handle<> errorTextHandle(borrowed(PyDict_GetItemString(main_namespace.ptr(), "ErrorText")));
			str textObject(errorTextHandle);

			errorText = extract<const char*>(textObject);
		}
	}
	catch(error_already_set) 
	{
		fprintf(stderr,"Exception occurred during SendTextToConsole\n");
		PyErr_Print();
	}
	catch(...) 
	{
		fprintf(stderr,"Unknown exception occurred during SendTextToConsole\n");
		PyErr_Print();
	}

	if (errorText.size() > 0)
	{
		tcMessageInterface::Get()->ChannelMessage("Python", "", 0);
		while (errorText.size() > 0)
		{
			wxString line = errorText.BeforeFirst('\n');
			errorText = errorText.AfterFirst('\n');

			tcMessageInterface::Get()->ChannelMessage("Python", line.ToStdString(), 0);
		}
	}


}


tcSimPythonInterface::tcSimPythonInterface() :
    mpConsole(0),
    director(0),
    mpHookedObj(0),
    overlay(0),
    isModePushed(false),
	showPythonErrors(false)
{
	mpSimState = tcSimState::Get();

    InitCommandBypass();

	tcPlatformInterface::AttachSimState(mpSimState);
    tcScenarioInterface::AttachSimState(mpSimState);

    object platformInterfaceType = tcPlatformInterface::GetPlatformInterface();

    PlatformInterface = platformInterfaceType();
    HookedPlatformInterface = platformInterfaceType();
    
    platformInterface = extract<tcPlatformInterface*>(PlatformInterface);
    hookedInterface = extract<tcPlatformInterface*>(HookedPlatformInterface);


	object GroupInterfaceType = class_<tcGroupInterface>("GroupInterfaceClass")
		.def("GetPlatformInterface", &tcGroupInterface::GetPlatformInterface)
        .def("GetWeaponInterface", &tcGroupInterface::GetWeaponInterface)
		.def("GetUnitCount", &tcGroupInterface::GetUnitCount)
		.def("GetUnitId", &tcGroupInterface::GetUnitId)
        .def("IsPlatform", &tcGroupInterface::IsPlatform)
        .def("IsWeapon", &tcGroupInterface::IsWeapon)
        .def("GetTankerList", &tcGroupInterface::GetTankerList)
        .def("LookupUnit", &tcGroupInterface::LookupUnit)
        .def("LookupUnitIdx", &tcGroupInterface::LookupUnitIdx)
        .def("TakeControl", &tcGroupInterface::TakeControl)
        .def("ReleaseControl", &tcGroupInterface::ReleaseControl)
        .def("GetUserInput", &tcGroupInterface::GetUserInput)
        .def("GetScenarioInterface", &tcGroupInterface::GetScenarioInterface)
		;
	GroupInterface = GroupInterfaceType();
	groupInterface = extract<tcGroupInterface*>(GroupInterface);


    MenuInterfaceType = class_<tcMenuInterface>("MenuInterfaceClass")
        .def("AddItem", &tcMenuInterface::AddItem)
        .def("AddItemWithParam", &tcMenuInterface::AddItemWithParam)
        .def("AddItemWithTextParam", &tcMenuInterface::AddItemWithTextParam)
        .def("AddItemUI",&tcMenuInterface::AddItemUI)
        .def("AddItemUIWithParam",&tcMenuInterface::AddItemUIWithParam)
		.def("AddItemUIWithTextParam", &tcMenuInterface::AddItemUIWithTextParam)
        .def("BeginSubMenu", &tcMenuInterface::BeginSubMenu)
        .def("Clear", &tcMenuInterface::Clear)
        .def("EndSubMenu", &tcMenuInterface::EndSubMenu)
        .def("SetStayOpen", &tcMenuInterface::SetStayOpen)
        ;
    MenuInterface = MenuInterfaceType();

    PanelInterfaceType = class_<tcPanelInterface>("PanelInterfaceClass")
        .def("AddItem", &tcPanelInterface::AddItem)
        .def("AddItemWithParam", &tcPanelInterface::AddItemWithParam)
        .def("AddItemUI",&tcPanelInterface::AddItemUI)
        .def("AddItemUIWithParam",&tcPanelInterface::AddItemUIWithParam)
        .def("BoldLastItem",&tcPanelInterface::BoldLastItem)
        .def("Clear", &tcPanelInterface::Clear)
        .def("SetTitle",&tcPanelInterface::SetTitle)
        ;
    PanelInterface = PanelInterfaceType();

    SubInterfaceType = class_<tcSubInterface>("SubInterfaceClass")
		.def("GetBatteryFraction", &tcSubInterface::GetBatteryFraction)
        .def("GetMaxDepth", &tcSubInterface::GetMaxDepth)
        .def("GoToPeriscopeDepth", &tcSubInterface::GoToPeriscopeDepth)
        .def("IsAtPeriscopeDepth", &tcSubInterface::IsAtPeriscopeDepth)
		.def("IsDieselElectric", &tcSubInterface::IsDieselElectric)
        .def("IsPeriscopeRaised", &tcSubInterface::IsPeriscopeRaised)
        .def("IsRadarMastRaised", &tcSubInterface::IsRadarMastRaised)
		.def("IsSnorkeling", &tcSubInterface::IsSnorkeling)
        .def("IsValid", &tcSubInterface::IsValid)
        .def("LowerPeriscope", &tcSubInterface::LowerPeriscope)
        .def("LowerRadarMast", &tcSubInterface::LowerRadarMast)
        .def("RaisePeriscope", &tcSubInterface::RaisePeriscope)
        .def("RaiseRadarMast", &tcSubInterface::RaiseRadarMast)
		.def("SetSnorkelState", &tcSubInterface::SetSnorkelState)
        .def("GetCavitatingSpeed", &tcSubInterface::GetCavitatingSpeed)
        ;


    TrackInterfaceType = class_<tcTrackInterface>("TrackInfoClass")
        .def("DeclareHostile", &tcTrackInterface::DeclareHostile)
        .def("DeclareNeutral", &tcTrackInterface::DeclareNeutral)
        .def("DeclareFriendly", &tcTrackInterface::DeclareFriendly)
        .def("DropTrack", &tcTrackInterface::DropTrack)
		.def("UpdateAmbiguityList", &tcTrackInterface::UpdateAmbiguityList)
        ;
    TrackInterface = TrackInterfaceType();


    object flightPortInterfaceType = tcFlightPortInterface::GetInterface();
    FlightPortInterface = flightPortInterfaceType();
    flightPortInterface = extract<tcFlightPortInterface*>(FlightPortInterface);

    object weaponInterfaceType = tcWeaponInterface::GetInterface();
    WeaponInterface = weaponInterfaceType();
    weaponInterface = extract<tcWeaponInterface*>(WeaponInterface);


    object missionInterfaceType = tcMissionInterface::GetInterface();
    
    object scenarioInterfaceType = tcScenarioInterface::GetInterface();
    tcScenarioInterface::AddGoalClasses();
    ScenarioInterface = scenarioInterfaceType();
    scenarioInterface = extract<tcScenarioInterface*>(ScenarioInterface);
    tcPlatformInterface::AttachScenarioInterface(scenarioInterface);
    tcWeaponInterface::AttachScenarioInterface(scenarioInterface);
    tcGroupInterface::AttachScenarioInterface(scenarioInterface);

    ScriptedTaskInterface tempInterface;
    TaskInterfaceObject = object(tempInterface);
    taskInterface = extract<ScriptedTaskInterface*>(TaskInterfaceObject);

    // add PlatformInterface to python environment as global var 
    // called "UnitInfo"
    PyDict_SetItemString(main_namespace.ptr(), "UnitInfo", PlatformInterface.ptr());  
    PyDict_SetItemString(main_namespace.ptr(), "HookedUnitInfo", HookedPlatformInterface.ptr());  
    PyDict_SetItemString(main_namespace.ptr(), "UserMenu", MenuInterface.ptr());  
    PyDict_SetItemString(main_namespace.ptr(), "UserPanel", PanelInterface.ptr());  
    PyDict_SetItemString(main_namespace.ptr(), "FlightPortInfo", FlightPortInterface.ptr());  
    PyDict_SetItemString(main_namespace.ptr(), "HookedTrackInfo", TrackInterface.ptr()); 
    PyDict_SetItemString(main_namespace.ptr(), "ScenarioManager", ScenarioInterface.ptr()); 
	PyDict_SetItemString(main_namespace.ptr(), "GroupInfo", GroupInterface.ptr()); 
   	PyDict_SetItemString(main_namespace.ptr(), "TaskInterface", TaskInterfaceObject.ptr());  
   	PyDict_SetItemString(main_namespace.ptr(), "WeaponInfo", WeaponInterface.ptr());  

    PyDict_SetItemString(main_namespace.ptr(), "Y", PyInt_FromLong(2));      /* dict['Y']=2 */

    // import AI script
    try 
    {   
        handle<> ignored( PyRun_String("import sys\n"
			                   "import StringIO\n"
							   "myout = StringIO.StringIO()\n"
							   "myerr = StringIO.StringIO()\n"
                               "sys.stdout = myout\n"
                               "sys.stderr = myerr\n"
							   "outfile = file('log\\pyout.txt', 'w')\n"
							   "errfile = file('log\\pyerr.txt', 'w')\n"
                               //"outfile.write("")\n"
                               //"errfile.write("")\n"
                               "outfile.close()\n"
                               "errfile.close()\n"
            , Py_file_input, main_namespace.ptr(), main_namespace.ptr()) );
  

        handle<> ignored2( PyRun_String("import AI\n"
            , Py_file_input, main_namespace.ptr(), main_namespace.ptr()) );
        handle<> ignored3( PyRun_String("import Menu\n"
            , Py_file_input, main_namespace.ptr(), main_namespace.ptr()) );
        handle<> ignored4( PyRun_String("print globals()\n"
            , Py_file_input, main_namespace.ptr(), main_namespace.ptr()) );
    }
    catch (error_already_set) 
    {
        // handle the exception in some way
        fprintf(stderr,"Exception occurred during import\n");
        PyErr_Print();
    }

	if (tcOptions::Get()->OptionStringExists("ShowPythonErrors"))
	{
		showPythonErrors = true;
	}


}


tcSimPythonInterface::~tcSimPythonInterface() 
{


}
