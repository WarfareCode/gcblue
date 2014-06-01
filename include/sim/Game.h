/** 
**  @file Game.h
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

#if !defined _GAME_H_
#define _GAME_H_

#include "wx/wx.h" 

#ifdef WIN32
#include "wx/msw/private.h" // for MS Windows specific definitions
#endif

#include "wx/datetime.h"

#include "tcMapView.h"
#include "tcSoundConsole.h"
#include "commandlist.h"
#include "tcDatabase.h"
#include "tcSimState.h"
#include "tcGameView.h"
#include "tcUserInfo.h"
#include "tcOptions.h"
#include "tcOptionsView.h"
#include "tcObjectControl.h"
#include "tcTime.h"
#include "tcStartView.h"
#include "tcCreditView.h"
#include "tcScenarioSelectView.h"
#include "wxcommands.h"
#include "tcDateTime.h"


namespace scriptinterface
{
    tcSimPythonInterface;
}

class tcCommandQueue;
class tcHookInfo;
class tcOOBView;
class tcPopupControl;
enum teMenuMode;
class tc3DViewer;
class tcGoalTracker;
class tcDateTime;
class tcDirector;
class tcMessageCenter;
class tcNetworkView;
class tcDisplaySettingsView;
class tcChatBox;
class tc3DWindow2;
class tcDraggedIconDisplay;
class tcMapData;
class tcBriefingView;
class tcDatabaseViewer;
class tcMPGameView;
class tcTVEngine;
class wxProgressDialog;

using namespace scriptinterface;



#ifndef SCENARIO_PATH
#define SCENARIO_PATH "scenarios"
#endif


/** 
 * Main game application class.
 *
 * tcGame holds all of the single instance objects and has the
 * main loop for the simulation. It also handles all mouse events
 * and game commands.
 *
 * cpp file needs to be broken up. Compiler heap overflow error occurs unless
 * /Zm option is used. Using /Zm500 as workaround for now.
 */
class tcGame : public wxFrame
{
    enum teScreenMode
    {
        START, ///< show main, multi-pane start view
        TACTICAL,
        TEST,
        NONE
    };

    enum teGameMode 
    {
        GM_START, ///< Game not started
        GM_PLAY ///< Game started
    };
    enum
	{
        N_BUTTON_BARS = 4
    };

public:
    typedef void (tcGame::*commandFunctionPtr)(const tsCommandInfo &);

    double gameTime;
    double directorTime; // kind of a hack to keep director going during pause
    LONGLONG nLastCount; // for timing

    tcDateTime gameDateTime; ///< object combining date and time
    wxDateTime startTime;
    //tcGraphicsInfo* mpGraphicsEngine;  // Graphics engine object
    tc3DViewer *viewer;
    tcTVEngine* tvEngine;
    long frameStyle;

    // Window locations
    RECT mrectMap;    
    RECT mrectWorldMap;
    RECT mrectConsole;
    RECT mrectHook;
    RECT mrectOOB;
    RECT mrect3D;
    RECT mrect3DSmall;
    RECT mrectEdit;
    RECT mrectLowerLeft;

    int mnWidth;
    int mnHeight;  // dimensions of main window
    wxPoint framePos;
    wxSize frameSize;
    int mnBriefingWidth; // dimensions of briefing window
    int mnLeftMargin;    // width of left auxiliary windows
    int mnBottomMargin;  // height of bottom aux windows
	tc3DWindow2* gameWindow; ///< main window for game windows (refactor this)
    tcSoundConsole* infoConsole; ///< console object for info messages
    tcSoundConsole* briefingConsoleLeft; ///< console object for briefing text
    tcSoundConsole* briefingConsoleBottom; ///< to fill space at bottom for now
	tcBriefingView* briefingView; ///< full screen window for simple briefing
    tcTacticalMapView* tacticalMap; ///< tactical map object
    tcWorldMapView* worldMap; ///< world map object
    //tcEditControl* editControl;
    tcHookInfo* hookInfo;  ///< window displaying info on hooked object    
    tcObjectControl* objectControl; ///< platform control GUI window
    tcOOBView* oobView;
    tcPopupControl* popupControl; // popup control object
    tcDatabase* database;
    tcSimState* simState;
    tcMapData* mapData;
    tcCommandQueue* commandQueue;
    tcSimPythonInterface* pythonInterface;
    tcUserInfo* userInfo;    
    tcGameView mcGameView;
    tcGoalTracker* goalTracker; ///< monitors simstate vs. victory goals
    tcDirector* director; ///< displays scripted graphics and controls view for dramatic mission brief
    tcMessageCenter* messageCenter; ///< tasking, intel, etc. message view


    tcChatBox* chatBox; ///< popup for multiplayer chat
    tcDraggedIconDisplay* draggedIconDisplay; ///< display of drag-drop icons


    tcStartView* startView;
    tcScenarioSelectView* scenarioSelectView;
    tcNetworkView* networkView;

	tc3DWindow2* test3DWindow;


    enum _editctrlstate 
    {
        ECS_GETSAVESCENARIO,
        ECS_GETLOADSCENARIO,
        ECS_NONE
    } meEditControlState;
    enum te3DSize
    {
        MODE3D_OFF = 0,
        MODE3D_SMALL = 1,       ///< corner view
        MODE3D_MEDIUM = 2,      ///< size of tactical map
        MODE3D_FULL = 3,        ///< full screen
		MODE3D_START = 4,       ///< mode for start screen display
        MODE3D_DATABASE = 5     ///< mode for database viewer screen
    };
    enum teTacticalMapSize
    {
        TM_MEDIUM = 0, ///< narrower version for briefing
        TM_LARGE = 1   ///< wider version for normal game play
    } tacticalMapSize;

    int mbPaused;
    bool mbQuit; ///< set to true to exit game to desktop
	bool endGame; ///< set to true to exit game to start screen
    bool mbScenarioEdit; ///< scenario edit mode
    int accelerateTime; ///< time acceleration factor, 0 is no accel, 1 is 2x, 2 is 3x, etc
                        ///< could try merge with pause, so 0 = pause, 1 = norm, 2 = 2x, etc
    bool mb3DActive;
    te3DSize size3D; ///< @see te3DSize
    te3DSize lastGame3DSize; ///< to restore in-game 3D size when switching from database view
    teScreenMode meScreenMode;
    teScreenMode lastMode;
    teGameMode meGameMode;
    bool mbSwitchToPlay;
    wxPoint smallViewerPosition;
    wxSize smallViewerSize;
	wxPoint startViewerPosition;
	wxSize startViewerSize;
    wxSize currentWindowSize;
    wxSize updatedWindowSize;

    int multiplayerMode; ///< 0 - single-player, 1 - client, 2 - server
	bool enableGraphicsEngine;
	bool enableTacticalMap;
	bool togglePopup; ///< true to toggle popup menu state
	wxPoint rightButtonPoint; ///< position of mouse at last right button event
	std::vector<long> hookedUnits; ///< vector of hooked unit ids
    bool enableClientSync; ///< for multiplayer client
    std::string versionString;
    long outcomeDialogKey; ///< key for game outcome dialog, -1 if not open
    long dbInfoPopupKey; ///< key for last database window popup to keep only one open at a time
    bool drawReported; ///< true if draw has been reported for game in progress

    std::map<std::string, commandFunctionPtr> textCommands;
	wxProgressDialog* progressDialog;


    void Activate();
    bool DirectoryExists(wchar_t *azDirectory);
	void DisplayOutcomeDialog(const char* message);
    void EndGame();
	void EndGame(wxCommandEvent& event);
	void QuitGame(wxCommandEvent& event);
    bool Finish();
    teMenuMode GetMenuMode();
    void GetUserInput(const tsCommandInfo& cmd); ///< for python interface
    void Init(); ///< basic initialization and start screen init
    bool InitGame(); ///< game initialization called prior to starting game
    bool InitSim();
    
    void CheckGoals(); ///< checks if any win/loss goals satisfied
    void CheckMultiplayerEndGame(); ///< checks for MP end game or surrender

    void ConsoleMessage(const char *s); ///< print string to info console
    const char* GetTimeString();
	void HookRandomFriendly(); ///< hooks random friendly platform
    void NewGroupHook(wxCommandEvent& event); ///< event for group of units hooked
	void NewGroupHook(std::vector<long>& groupUnits); ///< implements group hook
    void NewHook(wxCommandEvent& event); ///< event for single unit hooked (deprecated)
    void NewHook(long hookID);
	void DoubleClickHook(wxCommandEvent& event);
    void OnChar(wxKeyEvent& event);
    void OnCloseWindow(wxCloseEvent& event);
    void OnEraseBackground(wxEraseEvent& event);
    void OnKeyDown(wxKeyEvent& event);
    void OnLButtonDown(wxMouseEvent& event);
    void OnLButtonUp(wxMouseEvent& event);
	void OnLeaveWindow(wxMouseEvent& event);
    void OnMouseMove(wxMouseEvent& event);
    void OnMouseWheel(wxMouseEvent& event);
	void OnNcPaint(wxNcPaintEvent& event);
    void OnPaint(wxPaintEvent& event);
    void OnRButtonDown(wxMouseEvent& event);
    void OnSize(wxSizeEvent& event);
    bool HandleEraseBkgnd(WXHDC hDC); /// override of wxWindow method to eliminate flicker
	void ProcessCallback(tsCommandInfo& cmd); ///< for python interface
    void ProcessCommandList();
    void ProcessEsc();
    void ProcessTextCommand(tsCommandInfo cmd_info);
	void RefreshMaps(wxCommandEvent& event); ///< for changing map color types during game
	void RefreshMaps();
    bool ResizeWindows();
    void SecondaryHook(wxCommandEvent& event);
    void Set3D(wxCommandEvent& event);
    void Set3D(long state);
    void Minimize3D(wxCommandEvent& event);
    void Maximize3D(wxCommandEvent& event);
    void SetBriefingMode(wxCommandEvent& event);
    void SetBriefingMode(long state);
    void SetDeveloperMode(bool state);
    void SetMultiplayerMode(wxCommandEvent& event);
    void SetPauseMode(wxCommandEvent& event);
    void SetTacticalMapSize(teTacticalMapSize mapSize);
	void SetScenarioEdit(bool state);

    void SetTacticalView(wxCommandEvent& event);
    void SetTacticalView(float lon_deg, float lat_deg, float zoom);
    void SetTheater(wxCommandEvent& event); 
	void SetTheater(float lat_deg, float lon_deg); ///< sets theater view center
    void TheaterHighRes(wxCommandEvent& event);
    void TheaterHighRes();
    void TheaterMediumRes(wxCommandEvent& event);
    void TheaterMediumRes();
    void TheaterLowRes(wxCommandEvent& event);
    void TheaterLowRes();

    void SetTimeAccel(long accel);
    void SetTimeAccel(wxCommandEvent& event);
    void SetMaxTimeAccel(wxCommandEvent& event);
    int NextTimeAccelVal(int current, bool goFaster) const;
    void ShiftTime(float delta_s); ///< shifts time for sky/environment updates
	void ShowDatabaseInfo();
    void SkipBriefing(wxCommandEvent& event);
    void StartGame(wxCommandEvent& event);
    void ReloadGame(wxCommandEvent& event);
    void StartGamePlay(wxCommandEvent& event);
    void StartGameEdit(wxCommandEvent& event);
    void StartGameEditCreate(wxCommandEvent& event);

    void SwitchToBriefing(wxCommandEvent& event);
    void SwitchToCredit(wxCommandEvent& event);
	void SwitchToDatabaseView(wxCommandEvent& event);
	void SwitchToDisplaySettings(wxCommandEvent& event);
    void SwitchToMPGameView(wxCommandEvent& event);
    void SwitchToNetwork(wxCommandEvent& event);
    void SwitchToOptions(wxCommandEvent& event);
    void SwitchToScenarioSelect(wxCommandEvent& event);
    void SwitchToStart(wxCommandEvent& event);

    void SynchTimeAcceleration();
    void Toggle3DSize();
	void TogglePopup();
    void UninitGame(); ///< uninitializes components initialized by InitGame()

    void Update3DSize();
    void UpdateForScreenMode();
    bool UpdateFrame();
    bool UpdateStart();
    void UpdateOptions();

    void Initialize3DViewer();
    void InitializeBriefingConsoles();
    void InitializeDirector();
    void InitializeGameWindow();
    void InitializeMessageCenter();
    void InitializeSound();
    void InitializeStartView();    
    void InitializeTacticalMap();
	void InitializeWorldMap();

    float GetClientSyncFactor();
    bool GetAppVersion(wchar_t* libName, unsigned short* majorVersion, unsigned short* minorVersion, unsigned short* buildNumber, unsigned short* revisionNumber);
    void ShowPlatformDebug();
    void ShowSonarPanel();
    void ShowAirInfo();
    void TestCollision();
    void TestCrossSection();
    void ValidateHooked();

    // text commands
    void RegisterTextCommands();
    void TextCommandShowFlightPanel(const tsCommandInfo& cmd);
    void TextCommandShowStoresPanel(const tsCommandInfo& cmd);
    void TextCommandShowPlatformPanel(const tsCommandInfo& cmd);
    void TextCommandCopperMap(const tsCommandInfo& cmd);
    void TextCommandYellowBlueMap(const tsCommandInfo& cmd);
    void TextCommandBlackBlueMap(const tsCommandInfo& cmd);
    void TextCommandSetFormationEditId(const tsCommandInfo& cmd);
    void TextCommandShowAirInfo(const tsCommandInfo& cmd);
    void TextCommandShowSonarPanel(const tsCommandInfo& cmd);
    void TextCommandTestCollision(const tsCommandInfo& cmd);
    void TextCommandTestCrossSection(const tsCommandInfo& cmd);
    void TextCommandToggleUserAlliance(const tsCommandInfo& cmd);
    void TextCommandShowPlatformDebug(const tsCommandInfo& cmd);
    void TextCommandReimportPython(const tsCommandInfo& cmd);

    void SetInGame(bool state); ///< test command for multiplayer


    bool ValidateCopyProtection();

    static tcSoundConsole* messageConsole;
    static void DisplayMessage(const char* msg);

    tcGame(const wxPoint& pos, const wxSize& size, long frameStyle_);
    ~tcGame();

	DECLARE_EVENT_TABLE()
};
#endif