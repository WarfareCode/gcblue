/** 
**  @file Game.cpp main application class 
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
#endif

#include "game.h"
#include "gcb.h"
#include "AError.h"
#include <direct.h>

#include "wx/datetime.h"
#include "wx/progdlg.h"
#include <wx/filedlg.h>
#include <wx/filename.h>
#include <wx/xml/xml.h>

#include "commandlist.h" // for custom command queue handler
#include "tcCommandQueue.h"
#include "tcHookInfo.h"
#include "tcOOBView.h"
#include "tcPopupControl.h"
#include "tc3DViewer.h"
#include "tcGoalTracker.h"
#include "tcString.h"
#include "tcSimPythonInterface.h"
#include "tcScenarioInterface.h"
#include "tcDirector.h"
#include "tcXmlWindow.h"
#include "tcMapData.h"
#include "tcMessageCenter.h"
#include "tcMessageInterface.h"
#include "tcMessageChannel.h"
#include "tcMPGameView.h"
#include "tcNetworkView.h"
#include "tcDisplaySettingsView.h"
#include "network/tcMultiplayerInterface.h"
#include "network/tcUpdateMessageHandler.h" // for attach
#include "tcChatBox.h"
#include "tc3DWindow2.h"
#include "tcPopupMessage.h"
#include "tcLauncherPopup.h"
#include "tcUserSelectedGroups.h"
#include "tcContainerGui.h"
#include "tcFlightPortGui.h"
#include "tcDraggedIconDisplay.h"
#include "tcStoresGui.h"
#include "tcPlatformGui.h"
#include "tcBriefingView.h"
#include "tcTextEntryBox.h"
#include "tcDatabaseInfoWindow.h"
#include "tcPlatformDBObject.h"
#include "tcDatabaseViewer.h"
#include "tcSonarEnvironment.h"
#include "tcTVEngine.h"
#include "tc3DWindow2.h"
#include "tcUnits.h"
#include "tcDateTime.h"
#include "tcSkyModel.h"
#include "tcTacticalMapView.h"
#include "tcWorldMapView.h"
#include "tcGameSerializer.h"
#include "ai/tcMissionManager.h"
#include "tcPlatformDebugPopup.h"
#include "tcAircraftInfoPopup.h"
#include "tcGameOutcomePopup.h"
#include "tc3DModel.h" // for TestCollision
#include "network/tcControlMessageHandler.h" // for test

#include "tcTextDialog.h"
#include "tcScenarioDialog.h"
#include "tcMapOverlay.h"
#include "tcWaypointPopup.h"
#include "tcSonarInfoPopup.h"
#include "tcEventManager.h"
#include "ai/tcMission.h"

#if defined(_MSC_VER)
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



using namespace std;
using network::tcMultiplayerInterface;

BEGIN_EVENT_TABLE(tcGame, wxFrame)
EVT_PAINT(tcGame::OnPaint)
EVT_NC_PAINT(tcGame::OnNcPaint)
EVT_ERASE_BACKGROUND(tcGame::OnEraseBackground)
EVT_LEAVE_WINDOW(tcGame::OnLeaveWindow)
EVT_LEFT_DOWN(tcGame::OnLButtonDown)
EVT_LEFT_UP(tcGame::OnLButtonUp)
EVT_RIGHT_DOWN(tcGame::OnRButtonDown)
EVT_MOTION(tcGame::OnMouseMove)
EVT_MOUSEWHEEL(tcGame::OnMouseWheel)
EVT_KEY_DOWN(tcGame::OnKeyDown)  ///< any key has been pressed
EVT_CHAR(tcGame::OnChar)
EVT_SIZE(tcGame::OnSize)
EVT_CLOSE(tcGame::OnCloseWindow)
EVT_COMMAND(ID_STARTVIEW, wxEVT_COMMAND_BUTTON_CLICKED , tcGame::SwitchToStart)
EVT_COMMAND(ID_CREDITVIEW, wxEVT_COMMAND_BUTTON_CLICKED , tcGame::SwitchToCredit)
EVT_COMMAND(ID_DATABASEVIEW, wxEVT_COMMAND_BUTTON_CLICKED , tcGame::SwitchToDatabaseView)
EVT_COMMAND(ID_DISPLAYSETTINGS, wxEVT_COMMAND_BUTTON_CLICKED , tcGame::SwitchToDisplaySettings)
EVT_COMMAND(ID_OPTIONSVIEW, wxEVT_COMMAND_BUTTON_CLICKED , tcGame::SwitchToOptions)
EVT_COMMAND(ID_SCENARIOSELECTVIEW, wxEVT_COMMAND_BUTTON_CLICKED , tcGame::SwitchToScenarioSelect)
EVT_COMMAND(ID_MPGAMEVIEW, wxEVT_COMMAND_BUTTON_CLICKED , tcGame::SwitchToMPGameView)
EVT_COMMAND(ID_MULTIPLAYERVIEW, wxEVT_COMMAND_BUTTON_CLICKED , tcGame::SwitchToNetwork)
EVT_COMMAND(ID_BRIEFINGVIEW, wxEVT_COMMAND_BUTTON_CLICKED , tcGame::SwitchToBriefing)
EVT_COMMAND(ID_ENDGAME, wxEVT_COMMAND_BUTTON_CLICKED , tcGame::EndGame)
EVT_COMMAND(ID_STARTGAME, wxEVT_COMMAND_BUTTON_CLICKED , tcGame::StartGamePlay)
EVT_COMMAND(ID_EDITGAME, wxEVT_COMMAND_BUTTON_CLICKED , tcGame::StartGameEdit)
EVT_COMMAND(ID_CREATESCEN, wxEVT_COMMAND_BUTTON_CLICKED , tcGame::StartGameEditCreate)
EVT_COMMAND(ID_QUITGAME, wxEVT_COMMAND_BUTTON_CLICKED , tcGame::QuitGame)
EVT_COMMAND(ID_RELOADGAME, wxEVT_COMMAND_BUTTON_CLICKED , tcGame::ReloadGame)
EVT_COMMAND(ID_NEWHOOK, wxEVT_COMMAND_BUTTON_CLICKED, tcGame::NewHook)
EVT_COMMAND(ID_GROUPHOOK, wxEVT_COMMAND_BUTTON_CLICKED, tcGame::NewGroupHook)
EVT_COMMAND(ID_DCLICKHOOK, wxEVT_COMMAND_BUTTON_CLICKED, tcGame::DoubleClickHook)
EVT_COMMAND(ID_SECONDARYHOOK, wxEVT_COMMAND_BUTTON_CLICKED, tcGame::SecondaryHook)
EVT_COMMAND(ID_SETBRIEFING, wxEVT_COMMAND_BUTTON_CLICKED, tcGame::SetBriefingMode)
EVT_COMMAND(ID_MULTIPLAYERMODE, wxEVT_COMMAND_BUTTON_CLICKED , tcGame::SetMultiplayerMode)
EVT_COMMAND(ID_REFRESHMAPS, wxEVT_COMMAND_BUTTON_CLICKED, tcGame::RefreshMaps)
EVT_COMMAND(ID_SETPAUSE, wxEVT_COMMAND_BUTTON_CLICKED, tcGame::SetPauseMode)
EVT_COMMAND(ID_SETTIMEACCEL, wxEVT_COMMAND_BUTTON_CLICKED, tcGame::SetTimeAccel)
EVT_COMMAND(ID_SETMAXTIMEACCEL, wxEVT_COMMAND_BUTTON_CLICKED, tcGame::SetMaxTimeAccel)
EVT_COMMAND(ID_SETTHEATER, wxEVT_COMMAND_BUTTON_CLICKED, tcGame::SetTheater)
EVT_COMMAND(ID_SETTACTICALVIEW, wxEVT_COMMAND_BUTTON_CLICKED, tcGame::SetTacticalView)
EVT_COMMAND(ID_HIGHRESTHEATER, wxEVT_COMMAND_BUTTON_CLICKED, tcGame::TheaterHighRes)
EVT_COMMAND(ID_MEDRESTHEATER, wxEVT_COMMAND_BUTTON_CLICKED, tcGame::TheaterMediumRes)
EVT_COMMAND(ID_LOWRESTHEATER, wxEVT_COMMAND_BUTTON_CLICKED, tcGame::TheaterLowRes)
EVT_COMMAND(ID_SET3D, wxEVT_COMMAND_BUTTON_CLICKED, tcGame::Set3D)
EVT_COMMAND(ID_MINIMIZE3D, wxEVT_COMMAND_BUTTON_CLICKED, tcGame::Minimize3D)
EVT_COMMAND(ID_MAXIMIZE3D, wxEVT_COMMAND_BUTTON_CLICKED, tcGame::Maximize3D)
EVT_COMMAND(ID_SKIPBRIEFING, wxEVT_COMMAND_BUTTON_CLICKED, tcGame::SkipBriefing)
END_EVENT_TABLE()



tcSoundConsole* tcGame::messageConsole = 0;



void tcGame::CheckGoals()
{
    if (tcGameObject::IsEditMode()) return;

    tcAllianceInfo* allianceInfo = tcAllianceInfo::Get();

    std::vector<unsigned char> allianceList = allianceInfo->GetAllianceList();

    tcMessageInterface::Get()->ClearChannel("Mission");


    unsigned char nAlliances = (unsigned char)allianceList.size();
	char buff[256];

    // check if everyone has failed (draw)
    bool everyoneFailed = true;
	for (unsigned char k=0; k<nAlliances; k++)
    {
        bool allianceFailed = goalTracker->HasAllianceFailed(allianceList[k]);
        bool allianceNeutral = allianceInfo->IsAllianceNeutral(allianceList[k]);

        if (!allianceFailed && !allianceNeutral)
        {
            everyoneFailed = false;
        }
    }

    if (everyoneFailed && !drawReported)
    {
        SetTimeAccel(0); // pause game
        infoConsole->Print("SCENARIO A DRAW\n");
        DisplayOutcomeDialog("Scenario is a draw\n");

        if (simState->IsMultiplayerServer())
        {
            wxString s;
            s = "*** SCENARIO A DRAW ***";
            tcMultiplayerInterface::Get()->BroadcastChatText("*** GAME OVER ***");
            tcMultiplayerInterface::Get()->BroadcastChatText(s.ToStdString());
            EndGame();
        }
        drawReported = true;
        return;
    }


	for (unsigned char idx=0; idx < nAlliances; idx++)
	{
		unsigned char alliance = allianceList[idx];

        bool allianceFailed = goalTracker->HasAllianceFailed((int)alliance);
        bool allianceSucceeded = goalTracker->HasAllianceSucceeded((int)alliance);
        
        Vec4 textColor(1, 1, 1, 1);
        if (allianceFailed)
        {
            textColor.set(1, 0.4f, 0.4f, 1);
        }
        else if (allianceSucceeded)
        {
            textColor.set(0.4f, 1.0f, 0.4f, 1);
        }

        tcMessageInterface::Get()->ChannelMessage("Mission", 
            goalTracker->GetAllianceGoalStatusDescription(alliance), alliance);
        tcMessageInterface::Get()->ChannelMessage("Mission", "", alliance);

		if (allianceFailed)
		{
			if (goalTracker->HasStatusChanged(alliance))
			{
                sprintf(buff, "Alliance %s UNABLE TO WIN\n", allianceInfo->GetAllianceName(alliance).c_str());
				infoConsole->Print(buff);
				if (userInfo->IsOwnAlliance(alliance))
                {
                    SetTimeAccel(0); // pause game
                    DisplayOutcomeDialog("You cannot win, play for draw?\n");
                }

                if (simState->IsMultiplayerServer())
                {
                    wxString s;
                    s.Printf("*** %s UNABLE TO WIN", allianceInfo->GetAllianceName((unsigned char)alliance).c_str());
                    tcMultiplayerInterface::Get()->BroadcastChatText("*** GAME UPDATE ***");
                    tcMultiplayerInterface::Get()->BroadcastChatText(s.ToStdString());
                    //EndGame();
                }
			}
		}

		if (allianceSucceeded)
		{
			if (goalTracker->HasStatusChanged(alliance))
			{
                SetTimeAccel(0); // pause game
				sprintf(buff, "Alliance %d WON\n", alliance);
				infoConsole->Print(buff);
                if (userInfo->IsOwnAlliance(alliance))
                {
				    DisplayOutcomeDialog("You have won!\n");
                }
                else
                {
                    DisplayOutcomeDialog("You have lost!\n");
                }

                if (simState->IsMultiplayerServer())
                {
                    wxString s;
                    s.Printf("*** %s WON", allianceInfo->GetAllianceName((unsigned char)alliance).c_str());
                    tcMultiplayerInterface::Get()->BroadcastChatText("*** GAME OVER ***");
                    tcMultiplayerInterface::Get()->BroadcastChatText(s.ToStdString());
                    EndGame();
                }
			}
		}
	}

    CheckMultiplayerEndGame();

}


void tcGame::CheckMultiplayerEndGame()
{
    if (simState->IsMultiplayerServer())
    {
        wxString message;
        bool gameOver = tcMultiplayerInterface::Get()->IsGameOver(message);

        if (gameOver)
        {
            tcMultiplayerInterface::Get()->BroadcastChatText("*** GAME OVER ***");
            tcMultiplayerInterface::Get()->BroadcastChatText(message.ToStdString());

            EndGame();
        }
    }
    else if (simState->IsMultiplayerClient())
    {
        if ((simState->GetTime() == 0))
        {
            DisplayOutcomeDialog("GAME OVER\n");
        }
    }

}


/**
* Prints message to info console.
*/
void tcGame::ConsoleMessage(const char *s)
{
	if (!infoConsole)
	{
		wxMessageBox("Tried to use 0 infoConsole");

		return;
	}

	infoConsole->Print(s);
	infoConsole->Draw();
}

/**
* Static method to display generic message to user in game
*/
void tcGame::DisplayMessage(const char* msg)
{
	if (messageConsole)
	{
		messageConsole->Print(msg);
	}
}

/**
* Displays a simple message box with won or lost message.
* Player is given the option to quit or continue.
*/
void tcGame::DisplayOutcomeDialog(const char* message)
{
	std::stringstream outcomeMessage;

	outcomeMessage << message;

	goalTracker->WriteStatus(outcomeMessage, userInfo->GetOwnAlliance());
	
    if (!simState->IsMultiplayerServer())
    {
        if (outcomeDialogKey != -1)
        {
            return; // only allow one dialog open at once
            //tcRegistered::ForceClose(outcomeDialogKey);
        }

        tcGameOutcomePopup* popup = 
            new tcGameOutcomePopup(wxPoint(320, 240), wxSize(400, 300));
        popup->SetActive(true);
        popup->SetMessageText(outcomeMessage.str());

        outcomeDialogKey = popup->GetKey();
        

        //wxMessageDialog confirmQuit(this, outcomeMessage.str().c_str(), 
        //    "Game over, quit game?", wxYES | wxNO, wxDefaultPosition);

        //if (confirmQuit.ShowModal() == wxID_YES)
        //{
        //    wxCommandEvent command(wxEVT_COMMAND_BUTTON_CLICKED, ID_ENDGAME);    
        //    AddPendingEvent(command);
        //}
    }
    else
    {
        tcMultiplayerInterface::Get()->BroadcastChatText("*** GAME OVER");
    }
}

/**
* m_extraLong has bitfield describing keys pressed during double clidk: 
*     1 - shift pressed, 2 - ctrl pressed, 4 - alt pressed
*/
void tcGame::DoubleClickHook(wxCommandEvent& event)
{
	unsigned int flags = (unsigned int)(event.GetExtraLong());

    pythonInterface->ProcessDoubleClickHook(flags);
}



void tcGame::QuitGame(wxCommandEvent& event)
{
	mbQuit = true;
}

void tcGame::EndGame(wxCommandEvent& event)
{
	EndGame();
}

/**
* Ends game and returns to start screen
*/
void tcGame::EndGame()
{
	if (meGameMode == GM_START) return; // ignore if game has not started

    wxString windowName("gcblue");
    wxTopLevelWindow::SetTitle(windowName);
    wxTopLevelWindow::Freeze();

    bool endingScenarioEdit = tcGameObject::IsEditMode();

    if (!endingScenarioEdit)
    {
        goalTracker->LogAllianceGoalStatus("log\\goal_results.txt", 
            userInfo->GetOwnAlliance());

        goalTracker->LogAllDamageReports("log\\damage_summary.csv");

        wxDateTime now = wxDateTime::Now();
        wxString aarName = wxString::Format("aar\\%04d_%02d_%02d_%02d%02d%02d.xml",
            now.GetYear(), now.GetMonth()+1, now.GetDay(), now.GetHour(), now.GetMinute(), now.GetSecond());
        goalTracker->WriteAAR(aarName.ToStdString());
    }


    tcTVEngine::Get()->AddToLog("---------- ENDING GAME ----------\n\n");

    // clear old hook info
    NewHook(-1);
    pythonInterface->SetMenuPlatform(-1);
	tcSimPythonInterface::Get()->ReimportModules();

	// close open gui windows
	tcContainerGui::CloseAll();

    // close all registered windows
    if (outcomeDialogKey != -1)
    {
        tcRegistered::ForceClose(outcomeDialogKey);
        outcomeDialogKey = -1;
    }
    if (dbInfoPopupKey != -1)
    {
        tcRegistered::ForceClose(dbInfoPopupKey);
        dbInfoPopupKey = -1;
    }


	UpdateForScreenMode(); // draw one more time for close-on-draw to take effect

	// hide all game windows
	briefingConsoleLeft->SetActive(false);
	briefingConsoleBottom->SetActive(false);
	briefingView->SetActive(false);
	chatBox->SetActive(false);
	hookInfo->SetActive(false);
	infoConsole->SetActive(false);
    messageCenter->SetActive(false);
	objectControl->SetActive(false);
	oobView->SetActive(false);
	popupControl->SetActive(false);
	tacticalMap->SetActive(false);
	viewer->SetActive(false);
	worldMap->SetActive(false);
	gameWindow->SetActive(false);
    
	briefingView->SetButtonCaption(ID_STARTVIEW, "Return");

	pythonInterface->GetScenarioInterface()->ClearSimpleBriefing();

    objectControl->SetHookID(-1);

    tcMission::ResetNextId();

	if (!simState->IsMultiplayerActive())
	{
		// reset time
		gameTime = 0;
		directorTime = 0; 
		nLastCount = 0;
		accelerateTime = 0;

		// clear briefing console text
		briefingConsoleLeft->Clear();
		briefingConsoleLeft->SetDelayedTextEffect(true);

		// reset director
		director->ClearEvents();
        tacticalMap->ClearMapObjects();
        tacticalMap->ClearSpecialGraphics();
		director->SetStartTime(0);

		// try to reload last scenario played
		std::string lastPath = tcOptions::Get()->GetOptionString("LastScenarioPath");
		std::string lastName = tcOptions::Get()->GetOptionString("LastScenarioName");
        std::string lastExtension = tcOptions::Get()->GetOptionString("LastScenarioExtension");

        simState->Clear();
        scenarioSelectView->SetGameStarted(false);
		if ((lastName.length() > 2) && (lastName != "default") && (lastExtension == "py"))
		{
			scenarioSelectView->LoadScenario(lastPath, lastName, false);
		}
        else
        {
            pythonInterface->ClearScenario();
        }

		if (simState->IsScenarioLoaded())
		{
			HookRandomFriendly();
		}
	}
    else if (simState->IsMultiplayerServer())
    {
        // try to reload last scenario played
		std::string lastPath = tcOptions::Get()->GetOptionString("LastScenarioPath");
		std::string lastName = tcOptions::Get()->GetOptionString("LastScenarioName");
        std::string lastExtension = tcOptions::Get()->GetOptionString("LastScenarioExtension");

        simState->Clear();
        scenarioSelectView->SetGameStarted(false);
		if ((lastName.length() > 2) && (lastName != "default") && (lastExtension == "py"))
		{
            scenarioSelectView->LoadScenario(lastPath, lastName, false);
        }
        else
        {
            pythonInterface->ClearScenario();
            
            tcMultiplayerInterface* multiplayerInterface = tcMultiplayerInterface::Get();
            multiplayerInterface->ResetGame();
            multiplayerInterface->SetAllReadyState(false);

            scenarioSelectView->SynchScenarioInfo();
        }
    }
	// if in multiplayer client mode, switch to multiplayer off mode
	else if (networkView->GetNetworkMode() == tcNetworkView::MULTIPLAYER_CLIENT)
	{
        // save these so we don't clear the scenario info when logging out of ongoing game
        bool isScenarioLoaded = simState->IsScenarioLoaded();
        std::string scenarioName = simState->GetScenarioName();
        std::string scenarioDescription = simState->GetScenarioDescription();

		/* TODO: should have one object for network state vs. current system
		** with state in tcGame, tcSimState, tcNetworkView */
		// 27AUG08 changed this to NOT log client off at quit
        //wxASSERT(multiplayerMode == 1); 
		//networkView->SetNetworkMode(tcNetworkView::MULTIPLAYER_OFF);
		//multiplayerMode = 0;
        tcMultiplayerInterface::Get()->BroadcastControlMessage(network::tcControlMessageHandler::CM_OUTGAME);

        pythonInterface->ClearScenario();

        // restore scenario info
        simState->SetScenarioLoaded(isScenarioLoaded);
        simState->SetScenarioName(scenarioName);
        simState->SetScenarioDescription(scenarioDescription);
        
	}

    tcMessageInterface::Get()->SetPopupState(false);

	// set viewer back to object display mode
	viewer->SetTerrainActive(false);
	viewer->SetClearMode(1); // depth clearing
	viewer->SetText(" ");

	size3D = MODE3D_START;
	Update3DSize();

	// switch mode back to start
	meGameMode = GM_START;
	meScreenMode = START;
    if (!simState->IsMultiplayerActive())
    {
        startView->SetPane("Scenario");
    }
    else
    {
        startView->SetPane("Multiplayer");
    }
	mbScenarioEdit = false;
	endGame = false;
    drawReported = false;
    startView->SetGameStarted(false);
    scenarioSelectView->SetGameStarted(false);

    if (!endingScenarioEdit)
    {
        scenarioSelectView->SetTab("AAR");
    }

    scenarioSelectView->Init(); // rescan for recently saved scenario

    if (infoConsole != 0) infoConsole->Clear();

    wxTopLevelWindow::Thaw();
}


/**
* Called to reload the game from within scenario edit mode
* Must be in "game started" mode, as this does not exit to start view
*/
void tcGame::ReloadGame(wxCommandEvent& event)
{
    if (meGameMode == GM_START) return; // ignore if game has not started

    bool endingScenarioEdit = tcGameObject::IsEditMode();

    wxString windowName("gcblue");
    wxTopLevelWindow::SetTitle(windowName);
    wxTopLevelWindow::Freeze();


    tcTVEngine::Get()->AddToLog("---------- RELOADING SCENARIO ----------\n\n");

    // clear old hook info
    NewHook(-1);
    pythonInterface->SetMenuPlatform(-1);
	tcSimPythonInterface::Get()->ReimportModules();

	// close open gui windows
	tcContainerGui::CloseAll();

    // close all registered windows
    if (outcomeDialogKey != -1)
    {
        tcRegistered::ForceClose(outcomeDialogKey);
        outcomeDialogKey = -1;
    }
    if (dbInfoPopupKey != -1)
    {
        tcRegistered::ForceClose(dbInfoPopupKey);
        dbInfoPopupKey = -1;
    }


	UpdateForScreenMode(); // draw one more time for close-on-draw to take effect


	pythonInterface->GetScenarioInterface()->ClearSimpleBriefing();

    objectControl->SetHookID(-1);

    tcMission::ResetNextId();

    // reset time
    gameTime = 0;
    directorTime = 0; 
    nLastCount = 0;
    accelerateTime = 0;

    // clear briefing console text
    briefingConsoleLeft->Clear();
    briefingConsoleLeft->SetDelayedTextEffect(true);

    // reset director
    director->ClearEvents();
    tacticalMap->ClearMapObjects();
    tacticalMap->ClearSpecialGraphics();
    director->SetStartTime(0);

    // try to reload last scenario played
    std::string lastPath = tcOptions::Get()->GetOptionString("LastScenarioPath");
    std::string lastName = tcOptions::Get()->GetOptionString("LastScenarioName");
    std::string lastExtension = tcOptions::Get()->GetOptionString("LastScenarioExtension");

    simState->Clear();
    scenarioSelectView->SetGameStarted(false);
    if ((lastName.length() > 2) && (lastName != "default") && (lastExtension == "py"))
    {
        scenarioSelectView->LoadScenario(lastPath, lastName, false);
    }
    else
    {
        pythonInterface->ClearScenario();
    }

    if (simState->IsScenarioLoaded())
    {
        HookRandomFriendly();
    }
	

    tcMessageInterface::Get()->SetPopupState(false);

    scenarioSelectView->Init(); // rescan for recently saved scenario

    if (infoConsole != 0) infoConsole->Clear();

    wxTopLevelWindow::Thaw();

    // clear message center
    messageCenter->Clear();
    tcMessageInterface::Get()->SetPopupState(true);

    tcString s;
    s.Format("Reloading scenario: %s", simState->msScenarioInfo.mzName);
    ConsoleMessage(s.GetBuffer());

    simState->PrintToFile("log\\simstate_text.txt");

    endGame = false;
    drawReported = false;
    meGameMode = GM_PLAY;
    meScreenMode = TACTICAL;

    if (endingScenarioEdit)
    {
        tcGameObject::SetEditMode(true);
        SetScenarioEdit(true);
    }
    SetTimeAccel(0);

}

/**
* If game mode is GM_START do nothing, since map isn't instantiated. Otherwise
* reload the high resolution map with the new color mode.
*/
void tcGame::RefreshMaps()
{
	if (meGameMode == GM_START) return;

	if (tacticalMap == 0)
	{
		wxASSERT(false);
		return;
	}

	tacticalMap->Refresh();
}

void tcGame::RefreshMaps(wxCommandEvent& event)
{
	RefreshMaps();
}

/**
* @return true if window resize occurred, false if not
*/
bool tcGame::ResizeWindows()
{
    // do resize if size has changed and button has been released (avoid rapid resizing)
    if ((updatedWindowSize == currentWindowSize) || (wxGetMouseState().LeftDown())) return false;

    wxASSERT(startView != 0);
    if (startView == 0) return false;

    mnWidth = updatedWindowSize.GetWidth();
    mnHeight = updatedWindowSize.GetHeight();
    frameSize = updatedWindowSize;

    startView->SetSize(updatedWindowSize);

    // 3D viewer size
    smallViewerPosition = wxPoint(mnWidth - 380, 2);
	smallViewerSize = wxSize(380, 200);
	startViewerSize = wxSize(mnWidth/2, mnHeight/2);
	startViewerPosition = wxPoint(mnWidth - startViewerSize.x, 
		                          mnHeight - startViewerSize.y);

    // tactical map
	mrectMap.right = mnWidth;
	mrectMap.bottom = mnHeight;
    tacticalMap->SetSize(wxSize(mnWidth, mnHeight));

    // world map
    mrectWorldMap = mrectMap;
	mrectWorldMap.bottom -= 200;
	mrectWorldMap.left = mrectWorldMap.right - 257;
	mrectWorldMap.top = mrectWorldMap.bottom - 129;
    wxRect r(mrectWorldMap.left, mrectWorldMap.top, 
        mrectWorldMap.right - mrectWorldMap.left, mrectWorldMap.bottom - mrectWorldMap.top);
    worldMap->SetSize(r);

    // 3D
    Update3DSize();

    // other game mode consoles
    int panelWidth = (mnWidth > 1000) ? 200 : 150;
	mrectLowerLeft.left = 0;
	mrectLowerLeft.top = mnHeight-200;
	mrectLowerLeft.right = panelWidth;
	mrectLowerLeft.bottom = mnHeight-2;

    if (infoConsole != 0)
    {
        infoConsole->SetSize(mrectLowerLeft.left, mrectLowerLeft.top, 
            panelWidth, mrectLowerLeft.bottom - mrectLowerLeft.top);
    }

    if (hookInfo != 0)
    {
        hookInfo->SetSize(mrectLowerLeft.right, mrectLowerLeft.top,
		    panelWidth, mrectLowerLeft.bottom - mrectLowerLeft.top);
    }

    if (objectControl != 0)
    {
        objectControl->SetSize(mrectLowerLeft.right+panelWidth, mrectLowerLeft.top, 
		    mnWidth-2*panelWidth, mrectLowerLeft.bottom - mrectLowerLeft.top);
    }

	mrectOOB.left = 0;
	mrectOOB.top = 0;
	mrectOOB.right = panelWidth;
	mrectOOB.bottom = mnHeight-200;
    if (oobView != 0)
    {
        oobView->SetSize(mrectOOB.left, mrectOOB.top,
            mrectOOB.right-mrectOOB.left, mrectOOB.bottom-mrectOOB.top);
    }


    currentWindowSize = updatedWindowSize;

    return true;
}

/**
* Skips to the end of the briefing and starts game
*/
void tcGame::SkipBriefing(wxCommandEvent& event)
{
    return;
	//if (meScreenMode != TACTICALBRIEF) return; // ignore if not in tactical briefing mode
	//directorTime = 1e10; // set directorTime to large value to skip to end

	//// deactivate delayed text so that briefing text is quickly available
	//briefingConsoleLeft->SetDelayedTextEffect(false); 

	//SetBriefingMode(0);
}

void tcGame::StartGameEdit(wxCommandEvent& event)
{
    mbScenarioEdit = true;
    tcGameObject::SetEditMode(true);

    StartGame(event);
}

void tcGame::StartGameEditCreate(wxCommandEvent& event)
{
    tcScenarioDialog scenarioDialog(this, -1, "Create New Scenario", "",
            wxPoint(200, 150), wxSize(550, 500));

    if (scenarioDialog.ShowModal() != wxID_OK)
    {
        startView->SetPane("Scenario");
        return;
    }


    tcSimPythonInterface* pythonInterface =	tcSimPythonInterface::Get();
    tcScenarioInterface* scenarioInterface = pythonInterface->GetScenarioInterface();
    pythonInterface->ClearScenario();
    scenarioInterface->ClearSimpleBriefing();
    
    scenarioInterface->SetScenarioName(scenarioDialog.GetScenarioNameText().ToStdString());
    scenarioInterface->SetScenarioDescription(scenarioDialog.GetScenarioDescriptionText().ToStdString());

    wxDateTime dt = scenarioDialog.GetScenarioDate();
    scenarioInterface->SetDateTime(dt.GetYear(), int(dt.GetMonth())+1, dt.GetDay(), dt.GetHour(), dt.GetMinute(), 0);

    wxArrayString sideList;
    scenarioDialog.GetSideList(sideList);
    int nSides = (int)sideList.size();
    for (int n=1; n<=nSides; n++)
    {
        scenarioInterface->CreateAlliance(n, sideList[n-1].ToStdString());
        scenarioInterface->SetAllianceDefaultCountry(n, sideList[n-1].ToStdString());
        scenarioInterface->SetAlliancePlayable(n, true);

        tcTimeGoal goal;
        goal.SetPassTimeout(36000);
        goal.SetFailTimeout(999*60);
        scenarioInterface->SetAllianceGoal(n, goal);
    }

    // set third+ side to neutral
    for (int n=3; n<=nSides; n++)
    {
        scenarioInterface->SetAllianceRelationship(n, 1, "Neutral");
        scenarioInterface->SetAllianceRelationship(n, 2, "Neutral");
    }

    scenarioInterface->SetUserAlliance(1);
    scenarioInterface->SetScenarioLoaded(true);


    mbScenarioEdit = true;
    tcGameObject::SetEditMode(true);

    StartGame(event);
}


void tcGame::StartGamePlay(wxCommandEvent& event)
{
    mbScenarioEdit = false;
    tcGameObject::SetEditMode(false);

    StartGame(event);
}

void tcGame::StartGame(wxCommandEvent& event)
{
	/* Only call InitGame() once. Previous system of calling InitGame() at
	** start of game and UninitGame() at end causes OOB and ObjectControl
	** windows to vanish in later games. May also leak memory.
	*/
	bool gameInitialized = (hookInfo != 0);

    if (meGameMode == GM_PLAY) // return to game
    {
        meScreenMode = TACTICAL;
    }
	else if (gameInitialized || InitGame())
	{
        wxString windowName = wxString::Format("gcblue - %s", simState->GetScenarioName());
        wxTopLevelWindow::SetTitle(windowName);
        tcTVEngine::Get()->AddToLog("---------- STARTING GAME ----------\n\n");

		if (simState->IsMultiplayerClient())
		{
			NewHook(-1); // clear hook for MP client, workaround for starting with bad hook for some unk reason
            tcMultiplayerInterface::Get()->BroadcastControlMessage(network::tcControlMessageHandler::CM_INGAME);
		}

        if (simState->IsMultiplayerServer())
        {
            simState->SetMultiplayerGameStarted(true);
        }

		// set hookID for windows that were just created
		long hookID = tacticalMap->GetHookID();
        NewHook(hookID);

		/*hookInfo->SetHookID(hookID);
		oobView->SetHookID(hookID);
		objectControl->SetHookID(hookID);*/

		startView->SetActive(false);

		viewer->SetTerrainActive(true);
		viewer->SetClearMode(2); // depth and color buffer clearing
		viewer->ClearDefaultTextObjects();
        size3D = MODE3D_SMALL;
        lastGame3DSize = MODE3D_SMALL;
        Update3DSize();

        if (!tcGameObject::IsEditMode())
        {
            director->AddGameStartEvents();
        }

        // clear message center
        messageCenter->Clear();
		tcMessageInterface::Get()->SetPopupState(true);

		tcString s;
		s.Format("Starting scenario: %s",simState->msScenarioInfo.mzName);
		ConsoleMessage(s.GetBuffer());

		simState->PrintToFile("log\\simstate_text.txt");

		endGame = false;
        drawReported = false;
		meGameMode = GM_PLAY;
		meScreenMode = TACTICAL;
        briefingView->SetButtonCaption(ID_STARTVIEW, "PLAY");
        startView->SetGameStarted(true);
        scenarioSelectView->SetGameStarted(true);


        tcAllianceSensorMap* allianceMap = simState->mcSensorMap.GetOrCreateMap(userInfo->GetOwnAlliance());
        pythonInterface->AttachSensorMap(allianceMap);

        // a hack, scenario select has special "start in edit mode" that
        // will have IsEditMode true at this point
        if (tcGameObject::IsEditMode())
        {
            SetScenarioEdit(true);
            SetTimeAccel(0);
        }
        else if (!simState->IsMultiplayerClient()) SetTimeAccel(1);
    }
    else
    {
        wxMessageBox("Error starting game","ERROR",wxICON_ERROR);
	}
}

void tcGame::SwitchToBriefing(wxCommandEvent& event)
{
	if (meGameMode != GM_START) return;

	meScreenMode = START;
    startView->SetPane("Scenario");
}

void tcGame::SwitchToCredit(wxCommandEvent& event)
{
	if (meGameMode != GM_START) return;

	meScreenMode = START;
	tcSound::Get()->PlayMusic("tension1");
	tcSound::Get()->SeekMusic(3.0);
}

void tcGame::SwitchToDatabaseView(wxCommandEvent& event)
{
	meScreenMode = START;
    startView->SetPane("Database");
}


void tcGame::SwitchToDisplaySettings(wxCommandEvent& event)
{
	meScreenMode = START;
}

void tcGame::SwitchToOptions(wxCommandEvent& event)
{
	meScreenMode = START;
    startView->SetPane("Options");
}

void tcGame::SwitchToMPGameView(wxCommandEvent& event)
{
    meScreenMode = START;
}

void tcGame::SwitchToNetwork(wxCommandEvent& event)
{
	meScreenMode = START;
    startView->SetPane("Multiplayer");
}

void tcGame::SwitchToScenarioSelect(wxCommandEvent& event)
{
	if (meGameMode != GM_START) return;

	meScreenMode = START;
    startView->SetPane("Scenario");

	scenarioSelectView->Init(); // initialize or re-initialize to check for new scenario files
}

void tcGame::SwitchToStart(wxCommandEvent& event)
{
	if (meGameMode == GM_START)
	{
		//if (meScreenMode == CREDIT) tcSound::Get()->PlayMusic("gcb_theme2");
		meScreenMode = START;
	}
	else
	{
		meScreenMode = TACTICAL;
	}
}

/**
* Call after a 3D viewer size change to 
* implement the change.
*/
void tcGame::Update3DSize()
{
	wxRect r;
	if (size3D == MODE3D_SMALL)
	{
		r = wxRect(smallViewerPosition, smallViewerSize);
	}
	else if (size3D == MODE3D_MEDIUM)
	{
		//int margin = (meScreenMode == TACTICALBRIEF) ? mnBriefingWidth : mnLeftMargin;
        int margin = mnLeftMargin;
		margin += 1;
		r.x = margin;
		r.y = 2;
		r.width = mnWidth-margin;
		r.height = mnHeight-mnBottomMargin-3;
	}
	else if (size3D == MODE3D_FULL)
	{
		r.x = 0;
		r.y = 0;
		r.width = mnWidth;
		r.height = mnHeight;
	}
    else if (size3D == MODE3D_DATABASE) // for database viewer screen
    {
        r.x = (mnWidth/2);
        r.y = (mnHeight/2);
        r.width = mnWidth - r.x;
        r.height = mnHeight - r.y;
    }
	else // (size3D == MODE3D_START)
	{
		r = wxRect(startViewerPosition, startViewerSize);
	}

	viewer->Freeze();
	viewer->SetSize(r);

    if ((meGameMode == GM_PLAY) && (meScreenMode == TACTICAL))
    {
        lastGame3DSize = size3D;
    }
}

void tcGame::TheaterHighRes(wxCommandEvent& event)
{
    TheaterHighRes();
}

void tcGame::TheaterHighRes()
{
    int theaterDecimation = mapData->GetTheaterDecimation();

    if (theaterDecimation == mapData->GetHighResDecimation()) return;

    if ((tacticalMap == 0) || (mapData == 0)) return;

    float centerLon_rad = tacticalMap->mfLonCenter;
    float centerLat_rad = tacticalMap->mfLatCenter;
    float lonExtent_rad = tacticalMap->mfLonWidth;

    // use center of current view for theater zoom
    tcGeoRect viewRect = tacticalMap->mrectCurrentView;
    float lat_deg = C_180OVERPI * viewRect.YCenter();
    float lon_deg = C_180OVERPI * viewRect.XCenter();

    mapData->LoadHighResC(lon_deg, lat_deg, mapData->GetHighResDecimation());

    tacticalMap->Refresh();

    tacticalMap->SetView(tcPoint(centerLon_rad, centerLat_rad), lonExtent_rad);
}

void tcGame::TheaterMediumRes(wxCommandEvent& event)
{
    TheaterMediumRes();
}

void tcGame::TheaterMediumRes()
{
    int theaterDecimation = mapData->GetTheaterDecimation();

    if (theaterDecimation == mapData->GetMedResDecimation()) return;

    if ((tacticalMap == 0) || (mapData == 0)) return;

    float centerLon_rad = tacticalMap->mfLonCenter;
    float centerLat_rad = tacticalMap->mfLatCenter;
    float lonExtent_rad = tacticalMap->mfLonWidth;

    // use center of current view for theater zoom
    tcGeoRect viewRect = tacticalMap->mrectCurrentView;
    float lat_deg = C_180OVERPI * viewRect.YCenter();
    float lon_deg = C_180OVERPI * viewRect.XCenter();

    mapData->LoadHighResC(lon_deg, lat_deg, mapData->GetMedResDecimation());

    tacticalMap->Refresh();

    tacticalMap->SetView(tcPoint(centerLon_rad, centerLat_rad), lonExtent_rad); 
}


void tcGame::TheaterLowRes(wxCommandEvent& event)
{
    TheaterLowRes();
}

void tcGame::TheaterLowRes()
{
    int theaterDecimation = mapData->GetTheaterDecimation();

    if (theaterDecimation == mapData->GetLowResDecimation()) return;

    if ((tacticalMap == 0) || (mapData == 0)) return;

    float centerLon_rad = tacticalMap->mfLonCenter;
    float centerLat_rad = tacticalMap->mfLatCenter;
    float lonExtent_rad = tacticalMap->mfLonWidth;

    // use center of current view for theater zoom
    tcGeoRect viewRect = tacticalMap->mrectCurrentView;
    float lat_deg = C_180OVERPI * viewRect.YCenter();
    float lon_deg = C_180OVERPI * viewRect.XCenter();

    mapData->LoadHighResC(lon_deg, lat_deg, mapData->GetLowResDecimation());

    tacticalMap->Refresh();

    tacticalMap->SetView(tcPoint(centerLon_rad, centerLat_rad), lonExtent_rad); 
}

void tcGame::Toggle3DSize()
{
    if (!mb3DActive)
    {
        Set3D(MODE3D_SMALL);
        return;
    }

    switch (size3D)
    {
    case MODE3D_SMALL:
    case MODE3D_START:
        Set3D(MODE3D_MEDIUM);
        break;
    case MODE3D_MEDIUM:
        Set3D(MODE3D_FULL);
        break;
    case MODE3D_FULL:
        Set3D(MODE3D_SMALL);
        break;
    }
}

/**
* Initializes the game.
*/
void tcGame::Init()
{
    double a = 2.0;
    double b = 2e-12;
    double c = a + b;
    wxASSERT(c > a); // check that double precision math is working

	wxASSERT(progressDialog != 0);

//    osg::Timer_t startTick = osg::Timer::instance()->tick();

	startTime = wxDateTime::Now();

	std::cout << "Time init success" << std::endl;

#ifdef _DEBUG
 //   tcSonarEnvironment::Get()->Test();
#endif

	progressDialog->Update(16, "Initializing sound");
	try
	{    
		InitializeSound();
		std::cout << "InitializeSound() completed" << std::endl;
    }
    catch (...)
    {
        wxMessageBox("Unknown sound initialization error, attempting to disable sound", 
			"Error", wxICON_ERROR);
        tcOptions::Get()->disableSound = true; // disable sound
		tcOptions::Get()->mbPlayMusic = false; // disable music
        tcOptions::Get()->Synchronize();
    }

    try
    {
        tc3DWindow2::SetEngine(tvEngine);

		progressDialog->Update(16, "Loading database");
		database->SetProgressReporting(progressDialog, 16, 55);

		database->SerializeSql("", true); // moved to top so that db is loaded for db browse panel
		database->SetProgressReporting(0, 0, 0);

        //database->ExportPlatformTables();
        //database->ExportLauncherConfigurations();

		progressDialog->Update(60, "Initializing views");

        InitializeStartView(); 

		meGameMode = GM_START;
		meScreenMode = START;

		progressDialog->Update(61, "Initializing 3D viewer");
		Initialize3DViewer();

		progressDialog->Update(62, "Initializing game window");
		InitializeGameWindow();

		progressDialog->Update(63, "Initializing message center");
        InitializeMessageCenter();


		tcMultiplayerInterface::Get()->SetEvtHandler(this);
        tcMultiplayerInterface::Get()->SetVersionString(versionString.c_str());

		/*** Init edit control  ***/
        /*
		editControl = new tcEditControl(glCanvas, wxPoint(200,200), wxSize(100,50));
		editControl->SetActive(false);
        */

		progressDialog->Update(64, "Creating chat box");

		chatBox = new tcChatBox(this, wxPoint(200, 200), wxSize(470, 280), "ChatBox");
		chatBox->SetBaseRenderBin(40);
		chatBox->SetActive(false);
        chatBox->SetDragable(true);

		progressDialog->Update(64, "Binding objects");

		//database->LoadDBCSV();


		// uncomment the SaveDBCSV line to save copy of database to _out suffix, 
		// warning, this erroneously puts a copy of air DB objects into the generic file
		// need to fix DB obj structure so that only leaf classes are used by game objects
		//database->SaveDBCSV("_out"); 

        if (tcOptions::Get()->OptionStringExists("CopyDatabase"))
        {
		    database->SerializeSql("_copy", false);
        }

		tcGameObject::SetGameObjectDatabase(database); // added to allow objects to init themselves

		simState->AttachDB(database);
		simState->AttachMapData(mapData);
		simState->AttachPythonInterface(pythonInterface);
		simState->AttachUserInfo(userInfo);

		pythonInterface->AttachMapData(mapData);

		tcLauncherState::mpDatabase = database;

		
		progressDialog->Update(65, "Loading low res map data");
		/* ** Initialize mcMapData  * **/
		mapData->AttachOptions(tcOptions::Get());
		mapData->LoadLowRes();
		//mapData->LoadHighRes(-8.0f, 55.0f);
		//mapData->LoadHighResB(-8.0f, 55.0f);

		// added mapdata reference to tcGameObject to allow RandInit()
		// to place objects at legal positions and to set altitude appropriately
		tcGameObject::SetGameObjectMapData(mapData);
        tcPlatformObject::InitPlatformObject();

		/* Initialize director
		** Added tactical map and briefing console init to support director init.
		** If briefing never occurs outside of game, we could add a tcDirector
		** constructor that doesn't require a tactical map and briefing console.
		*/
		InitializeTacticalMap();
		InitializeWorldMap();

		InitializeBriefingConsoles();
		InitializeDirector();
		pythonInterface->AttachDirector(director);
	
        tcGameSerializer::AttachMapViews(tacticalMap, worldMap);

		tcMessageInterface::Get()->SetPopupState(false);

		network::tcUpdateMessageHandler::AttachMPGameView(startView->GetMPGameView());
		tcMultiplayerInterface::Get()->AttachMPGameView(startView->GetMPGameView());
		tcMultiplayerInterface::Get()->AttachScenarioSelectView(startView->GetScenarioSelectView());

        viewer->Raise();

        tcEventManager::eventObject = this;

		progressDialog->Update(70, "Initializing simulation");

		InitSim();
	}
	catch(std::string s)
	{
		wxMessageBox(s.c_str(),"Fatal error",wxICON_ERROR);
		throw;
	}
	catch(...)
	{
		wxMessageBox("Unknown error before RandInit", 
			"Fatal error", wxICON_ERROR);
		throw;
	}
	try
	{
		progressDialog->Update(80, "Loading scenario");
		pythonInterface->GetScenarioInterface()->SetProgressReporting(progressDialog);

		// try to load last scenario played
		std::string lastPath = tcOptions::Get()->GetOptionString("LastScenarioPath");
		std::string lastName = tcOptions::Get()->GetOptionString("LastScenarioName");
		std::string lastExtension = tcOptions::Get()->GetOptionString("LastScenarioExtension");

		if ((lastName.length() > 2) && (lastName != "default") && (lastExtension == "py"))
		{
			scenarioSelectView->LoadScenario(lastPath, lastName, false);
		}
        else
        {
            // do nothing, state starts clear
        }

		pythonInterface->GetScenarioInterface()->SetProgressReporting(0); // clear so that future loads don't access bad ptr in game

		if (simState->IsScenarioLoaded())
		{
			HookRandomFriendly();
		}
        else
        {
        }
	}
	catch(std::string s)
	{
		pythonInterface->GetScenarioInterface()->SetProgressReporting(0);
		std::string message;
		message += "Error during scenario loading: ";
		message += s;
		wxMessageBox(message.c_str(), "Fatal error", wxICON_ERROR);
		throw;
	}
	catch (...)
	{
		pythonInterface->GetScenarioInterface()->SetProgressReporting(0);
		wxMessageBox("Unknown error during scenario loading", "Fatal error", wxICON_ERROR);
		throw;
	}

	progressDialog->Destroy();
	progressDialog = 0;

	try
	{
		meGameMode = GM_START;
		meScreenMode = START;

		wxWindow::Show(TRUE);
	}
	catch (...)
	{
		wxMessageBox("Error in PlayMusic (try disabling sound)", 
			"Fatal error", wxICON_ERROR);
		throw;
	}

    //osg::Timer_t stopTick = osg::Timer::instance()->tick();

    //double elapsedTime_ms = osg::Timer::instance()->delta_m(startTick, stopTick);

    //fprintf(stdout, "Game init success. Init time: %.3f ms\n\n", elapsedTime_ms);
    float af = 3.2f;
    float bf = 3.7f;
    float cf = -3.7f;
    long ai = long(af);
    long bi = long(bf);
    long ci = long(cf);

    wxASSERT(ai == 3);
    wxASSERT(bi == 3);
    wxASSERT(ci == -3);

}


/**
* Intialize the 3D Viewer window.
*/
void tcGame::Initialize3DViewer()
{
	smallViewerPosition = wxPoint(mnWidth - 380, 2);
	smallViewerSize = wxSize(380, 200);
	
	startViewerSize = wxSize(mnWidth/2, mnHeight/2);
	startViewerPosition = wxPoint(mnWidth - startViewerSize.x, 
		                          mnHeight - startViewerSize.y);
	

	viewer = new tc3DViewer(this, startViewerPosition, startViewerSize);

	viewer->SetActive(false);
	viewer->SetTerrainActive(false);
	viewer->SetClearMode(1); // depth clearing
	viewer->SetText("");

	viewer->Show(FALSE);
	viewer->Freeze();

	mb3DActive = false;
	size3D = MODE3D_START;

    wxASSERT(startView != 0);
    startView->Set3DViewer(viewer);

}

/**
* Initialize sound
*/
void tcGame::InitializeSound()
{
	if (tcOptions::Get()->disableSound)
	{
		tcOptions::Get()->mbPlayMusic = false;
		tcOptions::Get()->Synchronize();
		return;
	}

	if (tcSound::Get()->Init())
	{
		tcSound::Get()->Test();
	}
	else
	{
		std::cerr << "Error - tcSound initialization failure" << std::endl;
		// run without sound
		return;
	}
}

/**
* Initializes the Start View screen.
*
*/
void tcGame::InitializeStartView()
{
	startView = new tcStartView(this, wxPoint(0,0), frameSize, "StartView");

	startView->AttachOptions(tcOptions::Get());
	startView->LoadBackgroundImage("e2night.jpg"); // start_background.jpg

	if (startView->Init() == false)
	{
		throw exception();
	}

    scenarioSelectView = startView->GetScenarioSelectView();
    networkView = startView->GetNetworkView();

    startView->SetVersionString(versionString);

	startView->SetActive(false);
}



/**
* Initialize MessageCenter view interface
*/
void tcGame::InitializeMessageCenter()
{
    scenarioSelectView = startView->GetScenarioSelectView();
    wxASSERT(scenarioSelectView != 0);

    messageCenter = scenarioSelectView->GetMessageCenter();
    wxASSERT(messageCenter != 0);

    //messageCenter->SetBaseRenderBin(40);

    tcMessageInterface::SetMessageCenter(messageCenter);
}



/**
* Initialize tactical briefing consoles, bottom console
* may become a static image or some other type of custom window.
*/
void tcGame::InitializeBriefingConsoles()
{
	int leftConsoleHeight = mnHeight-mnBottomMargin;
	briefingConsoleLeft = new tcSoundConsole(this, wxPoint(0,0), 
		wxSize(mnBriefingWidth, leftConsoleHeight), "xml/briefing_left.xml") ;

	briefingConsoleLeft->SetBaseRenderBin(30);

	if (!briefingConsoleLeft)
	{
		cerr << "briefingConsoleLeft init failed\n";
		throw "briefingConsoleLeft init failed\n";
	}

	briefingConsoleLeft->SetEffect("MutedBeep"); 
	//briefingConsoleLeft->InitGdi(10.0f,0xFF64FF64);
	briefingConsoleLeft->SetLineSpacing(10);
	briefingConsoleLeft->SetWrap(48);
	briefingConsoleLeft->SetActive(false);
	briefingConsoleLeft->SetDelayedTextEffect(true);
	//briefingConsoleLeft->LoadBackgroundImage("briefing_left.jpg");
    briefingConsoleLeft->MoveToTop();

	briefingConsoleLeft->Print(" "); // need this to get it to display


	briefingConsoleBottom = new tcSoundConsole(this, wxPoint(0, mnHeight-mnBottomMargin), 
		wxSize(mnWidth, mnBottomMargin), "xml/briefing_bottom.xml");
	
	if (!briefingConsoleBottom)
	{
		cerr << "briefingConsoleBottom init failed\n";
		throw "briefingConsoleBottom init failed\n";
	}

	briefingConsoleBottom->SetEffect(""); 
	//briefingConsoleBottom->InitGdi(10.0f,0xFF64FF64);
	briefingConsoleBottom->SetLineSpacing(10);
	briefingConsoleBottom->SetWrap(100);
	briefingConsoleBottom->SetActive(false);
	briefingConsoleBottom->LoadBackgroundImage("briefing_bottom.jpg");
	briefingConsoleBottom->SetBaseRenderBin(20);
	briefingConsoleBottom->Print(" "); // need this to get it to display

    briefingView = scenarioSelectView->GetBriefingView();
}

/**
* Initializes tcDirector object
*/
void tcGame::InitializeDirector()
{
	wxASSERT(director == 0); 
	wxASSERT(tacticalMap);
	wxASSERT(worldMap);
	wxASSERT(briefingConsoleLeft);

	tcDirector::AttachMapViews(tacticalMap, worldMap); 
	director = new tcDirector(viewer, briefingConsoleLeft->GetConsoleBox(), this);
	director->SetStartTime(0);
	//director->InitTest(); // load test event sequence
}

void tcGame::InitializeGameWindow()
{
	gameWindow = new tc3DWindow2(this, wxPoint(0, 0), wxSize(mnWidth, mnHeight),
		"GameWindow");
	gameWindow->SetBaseRenderBin(0);

	if (!gameWindow)
	{
		fprintf(stderr, "gameWindow init failed\n");
		throw "gameWindow init failed\n";
	}
}


void tcGame::InitializeTacticalMap()
{
	mrectMap.left = 0;
	mrectMap.top = 0;
	mrectMap.right = mnWidth; //GetSystemMetrics(SM_CXFULLSCREEN);
	mrectMap.bottom = mnHeight - 0*200; //GetSystemMetrics(SM_CYFULLSCREEN);

	tacticalMap = new tcTacticalMapView(gameWindow, wxPoint(mrectMap.left,mrectMap.top), 
		wxSize(mrectMap.right-mrectMap.left, mrectMap.bottom-mrectMap.top), gameWindow);
	tacticalMap->SetBaseRenderBin(10);
    tacticalMap->SetTextLeftMargin(200.0f);
	
	tacticalMapSize = TM_LARGE;

	if (!tacticalMap)
	{
		cerr << "tacticalMap init failed\n";
		throw "tacticalMap init failed\n";
	}

	tacticalMap->AttachMapData(mapData);
	tacticalMap->AttachOptions(tcOptions::Get());
	tacticalMap->AttachCommandInterface(commandQueue);

	tacticalMap->Init();
	tacticalMap->SetActive(false);
	tacticalMap->SetBlend(true);
	tacticalMap->RefreshTerrainView();

    tcMissionManager::AttachMapOverlay(tacticalMap->GetMapOverlay());
    tcMessageChannel::AttachMapOverlay(tacticalMap->GetMapOverlay());
    tcGoal::AttachMapOverlay(tacticalMap->GetMapOverlay());

}

void tcGame::InitializeWorldMap()
{
	mrectWorldMap = mrectMap;
	mrectWorldMap.bottom -= 200;
	mrectWorldMap.left = mrectWorldMap.right - 257;
	mrectWorldMap.top = mrectWorldMap.bottom - 129;

	worldMap = new tcWorldMapView(gameWindow, wxPoint(mrectWorldMap.left, mrectWorldMap.top), 
		wxSize(mrectWorldMap.right - mrectWorldMap.left - 1, mrectWorldMap.bottom - mrectWorldMap.top - 1), 
		gameWindow);
	worldMap->SetBaseRenderBin(25);

	if (!worldMap)
	{
		cerr << "worldMap init failed\n";
		throw "worldMap init failed\n";
	}


	worldMap->AttachMapData(mapData);
	worldMap->AttachOptions(tcOptions::Get());
	worldMap->AttachCommandInterface(commandQueue);
	worldMap->Init();
	worldMap->SetActive(false);
	worldMap->SetBlend(true);
	worldMap->RefreshTerrainView();

    worldMap->SetShowTacticalMapView(true);
    wxASSERT(tacticalMap != 0);
    tacticalMap->SetWorldMap(worldMap);
}

bool tcGame::InitGame()
{
#ifdef _DEBUG
    SetDeveloperMode(true);
#endif

	int panelWidth = (mnWidth > 1000) ? 225 : 150;
	/* ** Info console init  * **/
	mrectLowerLeft.left = 0;
	mrectLowerLeft.top = mnHeight-200;
	mrectLowerLeft.right = panelWidth;
	mrectLowerLeft.bottom = mnHeight-2;

	infoConsole = new tcSoundConsole(gameWindow, 
		wxPoint(mrectLowerLeft.left, mrectLowerLeft.top), 
		wxSize(panelWidth, mrectLowerLeft.bottom - mrectLowerLeft.top),
		"xml/info_console.xml", "InfoConsole", gameWindow);
	infoConsole->SetBaseRenderBin(30);
	//infoConsole->LoadBackgroundImage("start_background_plain.jpg");
    infoConsole->SetBackgroundColor(Vec4(0.0f, 0.0f, 0.1f, 0.6f));
    infoConsole->SetLeaveWindowPropagationLevel(2);
	infoConsole->MoveToTop();
	messageConsole = infoConsole;

	if (!infoConsole)
	{
		cerr << "infoConsole init failed\n";
		return false;
	}

	infoConsole->SetEffect(""); //"MutedBeep"); // no sound
	infoConsole->SetLineSpacing(10);
	//infoConsole->SetWrap(28);
	infoConsole->SetActive(false);


	/* ** hookInfo init  * **/
	hookInfo = new tcHookInfo(gameWindow, 
		wxPoint(mrectLowerLeft.right,mrectLowerLeft.top),
		wxSize(panelWidth, mrectLowerLeft.bottom - mrectLowerLeft.top),
		"HookInfo",
		gameWindow);

	hookInfo->SetBaseRenderBin(30);
	if (!hookInfo)
	{
		cerr << "hookInfo init failed\n";
		return false;
	}

	//hookInfo->LoadBackgroundImage("console_b.jpg");
    hookInfo->SetBackgroundColor(Vec4(0.0f, 0.0f, 0.1f, 0.8f));
    hookInfo->SetBorderDraw(true);
	hookInfo->AttachSimState(simState);
	hookInfo->AttachOptions(tcOptions::Get());
	hookInfo->AttachUserInfo(userInfo);
	hookInfo->SetActive(false);

	// objectControl init
	objectControl = new tcObjectControl(gameWindow, 
		wxPoint(mrectLowerLeft.right+panelWidth, mrectLowerLeft.top), 
		wxSize(mnWidth-2*panelWidth, mrectLowerLeft.bottom - mrectLowerLeft.top), "ObjectControl",
		gameWindow);
	if (!objectControl)
	{
		cerr << "objectControl init failed\n";
		return false;
	}


	//objectControl->LoadBackgroundImage("console_b.jpg");
    objectControl->SetBackgroundColor(Vec4(0.0f, 0.0f, 0.1f, 0.8f));
    objectControl->SetBaseRenderBin(30);
	objectControl->MoveToTop();
	objectControl->AttachUserInfo(userInfo);

	/* ** tcOOBView init  * **/
	mrectOOB.left = 0;
	mrectOOB.top = 0;
	mrectOOB.right = panelWidth;
	mrectOOB.bottom = mnHeight-200;
	oobView = new tcOOBView(gameWindow, wxPoint(mrectOOB.left,mrectOOB.top),
		wxSize(mrectOOB.right-mrectOOB.left, mrectOOB.bottom-mrectOOB.top),
		"OrderOfBattle", gameWindow);
	oobView->SetBaseRenderBin(20);
    oobView->MoveToTop();
	if (!oobView)
	{
		cerr << "oobView init failed\n";
		return false;
	}


	oobView->AttachMapView(tacticalMap);

	// popupControl init
	popupControl = new tcPopupControl(gameWindow, wxPoint(1400, 400), 
		wxSize(800, 1200));
	popupControl->SetBaseRenderBin(40);
	if (!popupControl)
	{
		cerr << "popupControl init failed\n";
		return false;
	}

	popupControl->AttachCommandInterface(commandQueue);
	popupControl->AttachPythonInterface(pythonInterface);
	popupControl->SetActive(false);
	popupControl->SetBlend(true);
	popupControl->Raise(); // bring popup to top of windows hierarchy to receive mouse events


    // tcDraggedIconDisplay init
    draggedIconDisplay = new tcDraggedIconDisplay(this);
	draggedIconDisplay->SetBaseRenderBin(150);

	wxASSERT(tacticalMap);

    // should inherit these from common base?
    tcPopupMessage::SetParent(gameWindow);
    tcLauncherPopup::SetParent(gameWindow); 
    tcWaypointPopup::SetParent(gameWindow); 
	tcContainerGui::SetParent(gameWindow);
	tcTextEntryBox::SetParent(gameWindow);
	tcDatabaseInfoWindow::SetParent(gameWindow);
    tcPlatformDebugPopup::SetParent(gameWindow);
    tcSonarInfoPopup::SetParent(gameWindow);
    tcAircraftInfoPopup::SetParent(gameWindow);
    tcGameOutcomePopup::SetParent(gameWindow);

	wxASSERT(infoConsole);
	pythonInterface->AttachConsole(infoConsole);
	// sensor maps get cleared in tcSimState::RandInit()


    tcAllianceSensorMap* allianceMap = simState->mcSensorMap.GetOrCreateMap(userInfo->GetOwnAlliance());
	pythonInterface->AttachSensorMap(allianceMap);
	mcGameView.AttachObjectControl(objectControl);

    messageCenter->AttachConsole(infoConsole);

	return true;
}


void tcGame::UninitGame()
{
	if (!infoConsole) return;
	infoConsole->Destroy();
	infoConsole = 0;

	if (!hookInfo) return;
	hookInfo->Destroy();
	hookInfo = 0;

	objectControl->Destroy();
	objectControl = 0;

	oobView->Destroy();
	oobView = 0;

	popupControl->Destroy();
	popupControl = 0;

    draggedIconDisplay->Destroy();
	draggedIconDisplay = 0;

	tacticalMap->ClearMapObjects();
	worldMap->ClearMapObjects();

	briefingConsoleLeft->Clear();

	
	pythonInterface->AttachConsole(0);
	mcGameView.AttachObjectControl(0);
    messageCenter->AttachConsole(0);

}



bool tcGame::InitSim()
{
	simState->AttachMapData(mapData);
	simState->AttachPythonInterface(pythonInterface);
	simState->AttachUserInfo(userInfo);
	simState->AttachCommandInterface(commandQueue);

	

	wxASSERT(director);
	pythonInterface->AttachSensorMap(simState->mcSensorMap.GetMap(userInfo->GetOwnAlliance()));
	pythonInterface->AttachCommandQueue(commandQueue);
    pythonInterface->AttachMapOverlay(tacticalMap->GetMapOverlay());
    pythonInterface->AttachTacticalMap(tacticalMap);
    pythonInterface->AttachSimState(simState);

	mcGameView.AttachSimState(simState);
	mcGameView.AttachMapView(tacticalMap);
	mcGameView.AttachWorldMapView(worldMap);
	mcGameView.AttachUserInfo(userInfo);
	mcGameView.AttachOptions(tcOptions::Get());

	viewer->AttachSimState(simState);
	viewer->AttachMapData(mapData);

	tcSensorMapTrack::AttachDatabase(database);

    simState->AttachWeaponTester(); // dev mode feature

    tcFlightPort::InitTransitionTimes();

    Aero::LoadAtmosphereTable();

	//tcSound::Get()->PlayEffect("Welcome");

	return true;
}


/**
* 3D window size change using wxWindows event.
* State stored in event.m_extraLong
* 0 - 3D off, 1 - 3D small, 2 - 3D med, 3 - 3D full
*/
void tcGame::Set3D(wxCommandEvent& event)
{
    long state = event.GetExtraLong(); // 2.6.3 m_extraLong;

    Set3D(state);
}

/**
* 3D window size change using wxWindows event.
* State stored in event.m_extraLong
* 0 - 3D off, 1 - 3D small, 2 - 3D med, 3 - 3D full
*/
void tcGame::Set3D(long state)
{
	if (state == MODE3D_OFF)
	{
		mb3DActive = false;
		return;
	}
	mb3DActive = true;

    size3D = (te3DSize)state;
	
	Update3DSize();
}


/**
* Briefing mode change using wxWindows event. This is how
* subordinate objects (director in this case) communicate
* with the higher level game control.
* State stored in event.m_extraLong
*/
void tcGame::SetBriefingMode(wxCommandEvent& event)
{
    long state = event.GetExtraLong(); // 2.6.3 m_extraLong;
	SetBriefingMode(state);
}

/**
* @param state 0 - deactivate briefing mode, 1 - activate briefing
*/
void tcGame::SetBriefingMode(long state)
{
    meScreenMode = TACTICAL;
	//if (state == 1)
	//{
	//	if (meScreenMode == TACTICAL) meScreenMode = TACTICALBRIEF;
	//}
	//else
	//{
	//	if (meScreenMode == TACTICALBRIEF) meScreenMode = TACTICAL;
	//}
}

void tcGame::SetDeveloperMode(bool state)
{
    if (state)
    {
        tcPlatformInterface::SetDeveloperMode(true);
        if (infoConsole != 0)
        {
            infoConsole->Print("Activated dev mode");
        }

        simState->StartDamageLog("log/damage_log.csv");
    }
    else
    {
        tcPlatformInterface::SetDeveloperMode(false);
        if (infoConsole != 0)
        {
            infoConsole->Print("De-activated dev mode");
        }
    }
}


void tcGame::SetInGame(bool state)
{
    if (simState->IsMultiplayerClient())
    {
        if (state)
        {
            tcMultiplayerInterface::Get()->BroadcastControlMessage(network::tcControlMessageHandler::CM_INGAME);
            if (infoConsole != 0)
            {
                infoConsole->Print("Sent CM_INGAME");
            }
        }
        else
        {
            tcMultiplayerInterface::Get()->BroadcastControlMessage(network::tcControlMessageHandler::CM_OUTGAME);
            if (infoConsole != 0)
            {
                infoConsole->Print("Sent CM_OUTGAME");
            }
        }
    }
}

/**
* Set multiplayer mode
*/
void tcGame::SetMultiplayerMode(wxCommandEvent& event)
{
    int mode = event.GetExtraLong(); // 2.6.3 m_extraLong;

	if (multiplayerMode == mode) return;

	multiplayerMode = mode;
}

/**
* Pause mode change through wxWindows event.
* State stored in event.m_extraLong
*/
void tcGame::SetPauseMode(wxCommandEvent& event)
{
    long state = event.GetExtraLong(); // 2.6.3 m_extraLong;

    SetTimeAccel(long(state == 0));
}

void tcGame::SetScenarioEdit(bool state)
{
    if ((mbScenarioEdit == state) || simState->IsMultiplayerActive()) return;

    SetTimeAccel(0);
    tcGameObject::SetEditMode(state);
    viewer->SetShakeAirCamera(!state && 
        tcOptions::Get()->OptionStringExists("ShakeAirCamera"));

    pythonInterface->GetScenarioInterface()->GetMapOverlay()->SetAllTextInteractive(state);
    
    mbScenarioEdit = state;

}

/**
*
*/
void tcGame::SetTacticalMapSize(tcGame::teTacticalMapSize mapSize)
{
    // don't change tactical map size anymore, use overlays
#if 0
	if (mapSize == tacticalMapSize) return;
	int w = (mapSize == TM_MEDIUM) ? mnBriefingWidth : mnLeftMargin;

	tacticalMap->Freeze(); // call Freeze() to prevent flicker on resize
	wxWindow::Freeze();
	tacticalMap->SetSize(wxRect(w,0,mnWidth-w,mnHeight-mnBottomMargin));
	tacticalMapSize = mapSize;
	wxWindow::Thaw();
#endif
}

void tcGame::SetTacticalView(wxCommandEvent& event)
{
    long extraLong = event.GetExtraLong(); // 2.6.3 m_extraLong;

    long lonWord = (extraLong & 0xFFFF);
    if ((lonWord & 0x8000) != 0) 
    {
        // sign extend
        lonWord += long(-1) & ~0xFFFF;
    }
	float lon_deg = 0.01f * float(lonWord);
    if (lon_deg < -180.0f) lon_deg += 360.0f;
    if (lon_deg >= 180.0f) lon_deg -= 360.0f;
    

	float lat_deg = 0.01f * float(extraLong >> 16);

    if (lat_deg > 90.0f) lat_deg = 90.0f;
    if (lat_deg <-90.0f) lat_deg = -90.0f;

    if ((lon_deg < -180.0f) || (lon_deg >= 180.0f) || (lat_deg < -90.0f) || (lat_deg > 90.0f))
    {
        fprintf(stderr, "tcGame::SetTacticalView - out of bounds (lat %f deg, lon %f deg)",
            lat_deg, lon_deg);
        wxASSERT(false);
        return;
    }

	SetTacticalView(lon_deg, lat_deg, 1.0f);
}

void tcGame::SetTacticalView(float lon_deg, float lat_deg, float zoom)
{
    if (tacticalMap != 0)
    {
        tcPoint viewCenter(C_PIOVER180*lon_deg , C_PIOVER180*lat_deg);
        if (tacticalMap->mrectViewBounds.ContainsPoint(C_PIOVER180*lon_deg , C_PIOVER180*lat_deg))
        {
            tacticalMap->SetView(viewCenter, tacticalMap->GetLonSpan());
        }
    }

}


/**
* wxWidgets event to call SetTheater
* extralong variable contains lat and lon,
* lowest 16 bits is longitude, next 16 bits is
* latitude, both in units of 1/8 degrees.
*/
void tcGame::SetTheater(wxCommandEvent& event)
{
    long extraLong = event.GetExtraLong(); // 2.6.3 m_extraLong;

    long lonWord = (extraLong & 0xFFFF);
    if ((lonWord & 0x8000) != 0) 
    {
        // sign extend
        lonWord += long(-1) & ~0xFFFF;
    }
	float lon_deg = 0.125f * float(lonWord);
    if (lon_deg < -180.0f) lon_deg += 360.0f;
    if (lon_deg >= 180.0f) lon_deg -= 360.0f;
    

	float lat_deg = 0.125f * float(extraLong >> 16);

    if (lat_deg > 90.0f) lat_deg = 90.0f;
    if (lat_deg <-85.0f) lat_deg = -85.0f;

    if ((lon_deg < -180.0f) || (lon_deg >= 180.0f) || (lat_deg < -90.0f) || (lat_deg > 90.0f))
    {
        fprintf(stderr, "tcGame::SetTheater - out of bounds (lat %f deg, lon %f deg)",
            lat_deg, lon_deg);
        wxASSERT(false);
        return;
    }

	SetTheater(lat_deg, lon_deg);
}

/**
* Sets theater view center for tacticalMap.
*/
void tcGame::SetTheater(float lat_deg, float lon_deg)
{
    //wxString s = wxString::Format("lon %.2f lat %.2f", lon_deg, lat_deg);
    //if (infoConsole != 0) infoConsole->Print(s.c_str());

    if ((lon_deg < -180.0f) || (lon_deg >= 180.0f) || (lat_deg < -90.0f) || (lat_deg > 90.0f))
    {
        fprintf(stderr, "tcGame::SetTheater - out of bounds (lat %f deg, lon %f deg)",
            lat_deg, lon_deg);
        wxASSERT(false);
        return;
    }

    int theaterDecimation = mapData->GetTheaterDecimation();
    if (!mapData->IsTheaterDecimationValid(theaterDecimation) || (theaterDecimation > 4))
    {
        theaterDecimation = mapData->GetHighResDecimation();
    }

	mapData->LoadHighResC(lon_deg, lat_deg, theaterDecimation);
    worldMap->SetTheaterCenter(lon_deg, lat_deg); // may be able to eliminate theater center from worldMap, seems dangerously redundant
	if (tacticalMap)
	{
		tacticalMap->Refresh();
	}
}


/**
* Time acceleration mode LIMIT using a wxWindows event.
* If the current time accel exceeds the limit, then call SetTimeAccel to reduce
*/
void tcGame::SetMaxTimeAccel(wxCommandEvent& event)
{
	long accelLimit = event.GetExtraLong();

    if ((accelerateTime+1) > accelLimit)
    {
        SetTimeAccel(accelLimit);
    }
}

/**
* Time acceleration mode change
* This is a more general version of SetPauseMode
*/
void tcGame::SetTimeAccel(long accel)
{
    if (mbScenarioEdit) 
    {
        if ((accel != 0) && (simState->GetTime() == 0))
        {
            tcOptions* options = tcOptions::Get();
            wxString revertFile = options->GetOptionString("ScenarioSavePath"); // full path and file name of last scenario
            wxString msg;
            wxFileName revertFileName(revertFile);
            if (revertFileName.FileExists())
            {
                msg.Printf("Play scenario? (Last save is %s)", revertFile.c_str());
            }
            else
            {
                msg.Printf("Play scenario? (Last save is INVALID %s)", revertFile.c_str());
            }
            wxMessageDialog confirmPlay(this, msg, "Confirm", wxOK | wxCANCEL, wxDefaultPosition);
            if (confirmPlay.ShowModal() != wxID_OK)
            {
                return;
            }
            // interpret time change as command to leave scen edit mode
            //SetScenarioEdit(false);
        }
        //return;
    }

    if (accel == 0)
    {
        mbPaused = true;
        accelerateTime = 0;
    }
    else if ((accel <= 60) || (accel == 120))
    {
        mbPaused = false;
        accelerateTime = accel - 1;
    }
    else if (accel == 99)
    {
        if (!mbPaused && (accelerateTime > 0))
        {
            accelerateTime = NextTimeAccelVal(accelerateTime, false);
        }
        else
        {
            mbPaused = true;
            accelerateTime = 0;
        }
    }
    else if (accel == 100)
    {
        mbPaused = !mbPaused; // toggle pause
        accelerateTime = 0;
    }
    else if (accel == 101)
    {
        if (!mbPaused)
        {
            accelerateTime = NextTimeAccelVal(accelerateTime, true);
        }
        else
        {
            mbPaused = false;
            accelerateTime = 0;
        }
    }
    else
    {
        fprintf(stderr, "tcGame::SetTimeAccel - accel out of range\n");
        return;
    }

    if (simState->IsMultiplayerClient())
    {
        long accelRequest = mbPaused ? 0 : accelerateTime + 1;

        wxString commandText = wxString::Format("//gamespeed %d", accelRequest);
        tcMultiplayerInterface::Get()->BroadcastChatText(commandText.ToStdString());
    }
    else
    {
        simState->SetTimeAcceleration(mbPaused ? 0 : accelerateTime+1);
    }
}


/**
* Time acceleration mode change using a wxWindows event.
* This is a more general version of SetPauseMode
*/
void tcGame::SetTimeAccel(wxCommandEvent& event)
{
	long accel = event.GetExtraLong(); // 2.6.3 m_extraLong;
    
    SetTimeAccel(accel);
}

/**
* Used to test sky and date/time functions.
* @param delta_s time offset in seconds to apply to gameDateTime
*/
void tcGame::ShiftTime(float delta_s)
{
    tcDateTime dt;
    simState->GetDateTime(dt);
    dt.AdjustTimeSeconds(delta_s);
    simState->SetDateTime(dt);
}

/**
* Shows popup with speed and range vs. altitude for hooked aircraft
*/
void tcGame::ShowAirInfo()
{
    tcPlatformObject* platform = tcSimPythonInterface::Get()->GetHookedObj();

    if (platform == 0) return;

    tcAircraftInfoPopup* popup = 
        new tcAircraftInfoPopup(platform->mnID, wxPoint(220, 40), wxSize(300, 300));
    popup->SetActive(true);
}

/**
* Create tcDatabaseInfoWindow popup to display database info on hooked object
*/
void tcGame::ShowDatabaseInfo()
{	
    long hookId = tacticalMap->GetHookID();

    if (hookId != -1)
    {
        // close previous popup if open
        if (dbInfoPopupKey != -1)
        {
            tcRegistered::ForceClose(dbInfoPopupKey);
            dbInfoPopupKey = -1;
        }

        tcDatabaseInfoWindow* dbinf = new tcDatabaseInfoWindow(wxPoint(300, 300));
        dbinf->SetDatabaseObject(hookId);

        dbInfoPopupKey = dbinf->GetKey();
    }
}


void tcGame::ShowPlatformDebug()
{
    tcPlatformObject* platform = tcSimPythonInterface::Get()->GetHookedObj();

    if (platform == 0) return;

    tcPlatformDebugPopup* popup = 
        new tcPlatformDebugPopup(platform->mnID, wxPoint(220, 40), wxSize(420, 200));
    popup->SetActive(true);
}


void tcGame::ShowSonarPanel()
{
    tcSonarInfoPopup* popup = 
        new tcSonarInfoPopup(wxPoint(320, 40), wxSize(500, 400));
    popup->SetActive(true);
}


/**
* If this object is running as a multiplayer client,
* set tcGame (main loop) time accel to simstate time accel.
* If running as server, set simstate to main loop time accel.
* Eventually this will all be moved to simstate to avoid
* this awkwardness.
*/
void tcGame::SynchTimeAcceleration()
{
    if (multiplayerMode == 0) return;

    if (multiplayerMode == 1) // client
    {
        long accel = simState->GetTimeAcceleration();
        if (accel == 0)
        {
            mbPaused = true;
            accelerateTime = 0;
        }
        else
        {
            mbPaused = false;
            accelerateTime = accel - 1;
        }
    }
    else // server
    {
        if (mbPaused)
        {
            simState->SetTimeAcceleration(0);
        }
        else
        {
            simState->SetTimeAcceleration(accelerateTime + 1);
        }
    }
}

bool tcGame::DirectoryExists(wchar_t *azDirectory)
{
	return wxDir::Exists(wxString(azDirectory));
}

/**
* UpdateStart.
*
* This method is called at game startup.
*/
bool tcGame::UpdateStart()
{
    return mbQuit;
//
//    tcTVEngine* engine = tcTVEngine::Get();
//
//
//    static teScreenMode lastMode = NONE;
//    static bool musicStarted = false;
//    static unsigned lastTimeCount = 0;
//
//    tcTime::Get()->Update();
//
//    tcMultiplayerInterface::Get()->Update();
//    tcMultiplayerInterface::Get()->Update();
//
//    startView->mbPlayEnabled = simState->msScenarioInfo.mbLoaded;
//
//    if (meScreenMode != lastMode)
//    {
//        startView->SetActive(false);
//        optionsView->SetActive(false);
//        creditView->SetActive(false);
//        databaseViewer->SetActive(false);
//        displaySettingsView->SetActive(false);
//        scenarioSelectView->SetActive(false);
//        messageCenter->SetActive(false);
//        networkView->SetActive(false);
//        multiplayerGameSetup->SetActive(false);
//        chatBox->SetActive(false);
//        briefingView->SetActive(false);
//        gameWindow->SetActive(false);
//        viewer->SetActive(false);
//        viewer->SetDatabaseView(false);
//    }
//
//    // predraw for render surfaces
//    // ------------------------------
//    switch (meScreenMode)
//    {
//    case START:
//        startView->SetActive(true);
//        startView->DrawToRenderSurface();
//        //viewer->SetActive(true);
//        break;
//    case CREDIT:
//        if (lastMode != CREDIT)
//        {
//            creditView->Rewind();
//        }
//        creditView->SetActive(true);
//        creditView->DrawToRenderSurface();
//        break;
//    case DATABASEVIEW:
//        viewer->SetActive(true);
//        viewer->SetDatabaseView(true);
//        databaseViewer->SetActive(true);
//        databaseViewer->Raise();
//        databaseViewer->DrawToRenderSurface();
//
//        if (lastMode != DATABASEVIEW)
//        {
//            size3D = MODE3D_DATABASE;
//            Update3DSize();
//            /// reselect display class to update camera range
//            databaseViewer->SelectDisplayClass(databaseViewer->GetDisplayClass());
//        }
//        break;
//    case OPTIONS:
//        optionsView->SetActive(true);
//        optionsView->DrawToRenderSurface();
//        break;
//    case DISPLAYSETTINGS:
//        displaySettingsView->SetActive(true);
//        displaySettingsView->DrawToRenderSurface();
//        break;
//    case SCENARIOSELECT:
//        scenarioSelectView->SetActive(true);
//        scenarioSelectView->DrawToRenderSurface();
//        //viewer->SetActive(true);
//        break;
//    case NETWORK:
//        networkView->SetActive(true);
//        networkView->DrawToRenderSurface();
//        break;
//    case MPGAME:
//        multiplayerGameSetup->SetActive(true);
//        multiplayerGameSetup->DrawToRenderSurface();
//        break;
//    case SIMPLEBRIEF:
//        briefingView->SetActive(true);
//        briefingView->DrawToRenderSurface();
//        break;
//    }
//
//		
//    if (viewer->IsActive())
//    {
//        viewer->RenderRS();
//    }
//
//    // ------------------------------
//    // draw to screen
//
//    engine->Clear();
//
//	switch (meScreenMode)
//	{
//	case START:
//		startView->SetActive(true);
//		startView->DrawToScreen();
//        //viewer->SetActive(true);
//		break;
//	case CREDIT:
//		if (lastMode != CREDIT)
//		{
//			creditView->Rewind();
//		}
//		creditView->SetActive(true);
//		creditView->DrawToScreen();
//        //viewer->SetActive(false);
//		break;
//    case DATABASEVIEW:
//        //viewer->SetActive(true);
//        //viewer->SetDatabaseView(true);
//        databaseViewer->SetActive(true);
//		databaseViewer->Raise();
//        databaseViewer->DrawToScreen();
//
//        if (lastMode != DATABASEVIEW)
//        {
//            size3D = MODE3D_DATABASE;
//            Update3DSize();
//            /// reselect display class to update camera range
//            databaseViewer->SelectDisplayClass(databaseViewer->GetDisplayClass());
//        }
//        break;
//	case OPTIONS:
//		optionsView->SetActive(true);
//		optionsView->DrawToScreen();
//        //viewer->SetActive(false);
//		break;
//	case DISPLAYSETTINGS:
//		displaySettingsView->SetActive(true);
//		displaySettingsView->DrawToScreen();
//        //viewer->SetActive(false);
//		break;
//	case SCENARIOSELECT:
//		scenarioSelectView->SetActive(true);
//		scenarioSelectView->DrawToScreen();
//        //viewer->SetActive(true);
//		break;
//	case NETWORK:
//		networkView->SetActive(true);
//		networkView->DrawToScreen();
//        //viewer->SetActive(false);
//		break;
//    case MPGAME:
//        multiplayerGameSetup->SetActive(true);
//        multiplayerGameSetup->DrawToScreen();
//        //viewer->SetActive(false);
//        break;
//	case SIMPLEBRIEF:
//		briefingView->SetActive(true);
//		briefingView->DrawToScreen();
//        //viewer->SetActive(false);
//		break;
//	}
//
//    if ((lastMode == DATABASEVIEW) && (meScreenMode != DATABASEVIEW))
//    {
//        size3D = MODE3D_START;
//        Update3DSize();
//    }
//
//
//	static float cameraTime = 0;
//	unsigned currentTimeCount = tcTime::Get()->Get30HzCount();
//	if (currentTimeCount - lastTimeCount >= 1)
//	{
//		cameraTime += 0.03f;
//		lastTimeCount = currentTimeCount;
//	}
//
//	//viewer->SetCameraAz(cameraTime);
//	//viewer->SetCameraEl(0.5f * sinf(0.1f*cameraTime));
//
//    //viewer->SetCameraSpinRate(0.01f);
//	//viewer->SetBorderActive(false);
//
//    if (meScreenMode != DATABASEVIEW)
//    {
//#if 0
//        if (!viewer->TextObjectExists(0))
//        {
//            viewer->AddDefaultTextObjects();
//        }
//
//        long hookID = tacticalMap->GetHookID();
//        if (tcGameObject* obj = simState->GetObject(hookID))
//        {
//            viewer->SetCameraRange(1.2f * obj->GetSpan());
//            wxString description;
//            description = wxString::Format("%s\n%s", obj->mzClass.c_str(), obj->mzUnit.c_str());
//
//            wxString launcherDescription;
//            wxString sensorDescription;
//
//            if (tcPlatformObject* plat = dynamic_cast<tcPlatformObject*>(obj))
//            {
//                launcherDescription = plat->GetLauncherDescription();
//                sensorDescription = plat->GetSensorDescription();
//            }
//            else
//            {
//                launcherDescription = "No weapons\n";
//                sensorDescription = "No sensors\n";
//            }
//
//            wxString scenarioDescription = 
//                wxString::Format("Scenario: %s", simState->msScenarioInfo.mzName);
//
//            viewer->UpdateTextObject(2, description.c_str());
//
//            viewer->UpdateTextObject(0, launcherDescription.c_str());
//            viewer->UpdateTextObject(1, sensorDescription.c_str());
//            viewer->UpdateTextObject(3, scenarioDescription.c_str());
//
//        }
//        else
//        {
//            HookRandomFriendly();
//        }
//
//        if (cameraTime > 7)
//        {
//            cameraTime = 0;
//            HookRandomFriendly();
//        }
//#endif
//    }
//
//		
//    if (viewer->IsActive())
//    {
//	    viewer->Update(gameDateTime);
//
//	    viewer->Render();
//    }
//
//    engine->Frame();
//
//
//
//    if (!musicStarted && (tcOptions::Get()->mbPlayMusic))
//    {
//        tcSound::Get()->PlayMusic("gcb_theme2");
//        musicStarted = true;
//    }
//
//    tcSound::Get()->UpdateAutoMusic(0);
//
//	lastMode = meScreenMode;
//
//	return mbQuit;

}

/**
* Perform frame update applicable to current screen mode.
* Update window status and draw windows.
* TODO: clean this up
*/
void tcGame::UpdateForScreenMode()
{
    tcTVEngine* engine = tcTVEngine::Get();

    bool gameActive = (meGameMode == GM_PLAY);

    tcOptions* options = tcOptions::Get();

    if (meScreenMode != lastMode)
    {
        briefingConsoleLeft->SetActive(false);
        briefingConsoleBottom->SetActive(false);
        chatBox->SetActive(false);
        //messageCenter->SetActive(false);
        startView->SetActive(false);
        tacticalMap->SetActive(false);
        viewer->SetActive(false);
        viewer->SetDatabaseView(false);
        viewer->SetCameraSpinRate(0);

        worldMap->SetActive(false);
		tcMessageInterface::Get()->SetPopupChatText(false);
		gameWindow->SetActive(false);

        if (gameActive)
        {
            hookInfo->SetActive(false);
            infoConsole->SetActive(false);
            objectControl->SetActive(false);
            oobView->SetActive(false);
            draggedIconDisplay->SetActive(false);

            if (meScreenMode == TACTICAL)
            {
                size3D = lastGame3DSize;
                Update3DSize();
            }

        }

    }


    // predraw for render surfaces
    // ------------------------------

    switch (meScreenMode)
    {
    case START:
        {
            startView->SetActive(true);
            startView->DrawToRenderSurface();

            if ((startView->GetActiveButton() == 2) && (options->minimal3D == 0)) // database
            {
                size3D = MODE3D_DATABASE;
                Update3DSize();
                viewer->SetActive(true);
                viewer->Lower(); // move to bottom of wxwidget window hierarchy
                viewer->SetCameraSpinRate(0.01f);
                viewer->SetDatabaseView(true);
            }
            else
            {
                viewer->SetActive(false);
                viewer->SetDatabaseView(false);
            }
        }
        break;
    case TACTICAL:
        {	
            bool drawEdgeWindows = (size3D != MODE3D_FULL) || (!mb3DActive);
            bool drawTacticalMap = (size3D == MODE3D_SMALL) || (!mb3DActive);
            if (tacticalMapSize == TM_MEDIUM) SetTacticalMapSize(TM_LARGE);

            gameWindow->SetActive(drawEdgeWindows);
            tacticalMap->SetActive(drawTacticalMap);
            worldMap->SetActive(drawTacticalMap);
            infoConsole->SetActive(drawEdgeWindows);
            hookInfo->SetActive(drawEdgeWindows);
            objectControl->SetActive(drawEdgeWindows);
            oobView->SetActive(drawEdgeWindows);

            viewer->SetActive(mb3DActive);
            if (mb3DActive)
            {
                viewer->SetBorderActive(true);
                viewer->SetDatabaseView(false);
                viewer->Raise();
            }

            gameWindow->DrawToRenderSurface();

            if (popupControl->mbActive) popupControl->DrawToRenderSurface();
            if (chatBox->mbActive)
            {
                chatBox->DrawToRenderSurface();
                tcMessageInterface::Get()->SetPopupChatText(false);
            }
            else
            {
                tcMessageInterface::Get()->SetPopupChatText(true);
            }

            draggedIconDisplay->SetActive(true);
            draggedIconDisplay->DrawToRenderSurface();
        }
        break;
    default:
        {
            wxASSERT(false);
        }
        break;
    }


    if (viewer->IsActive())
    {
        viewer->Update(gameDateTime);
        viewer->RenderRS();
    }

    // ------------------------------
    // draw to screen

    engine->Clear();

    switch (meScreenMode)
    {
    case START:
        {
            startView->SetActive(true);
            startView->DrawToScreen();
            //viewer->SetActive(true);
        }
        break;
    case TACTICAL:
        {	
            gameWindow->DrawToScreen();

            if (popupControl->mbActive) popupControl->DrawToScreen();
            if (chatBox->mbActive)
            {
                chatBox->DrawToScreen();
            }
            else
            {
            }

            draggedIconDisplay->DrawToScreen();
        }
        break;
    }

    //if ((lastMode == DATABASEVIEW) && (meScreenMode != DATABASEVIEW))
    //{
    //    size3D = MODE3D_SMALL;
    //    Update3DSize();
    //}

    lastMode = meScreenMode;

}

bool tcGame::UpdateFrame()
{    
static unsigned optionsUpdateCounter = 0;


//#ifdef _DEBUG
    if (optionsUpdateCounter % 5 == 0)
    {
        wxMilliSleep(1);
    }
//#endif
    
    bool windowResizeOccurred = false;

    tcTVEngine* engine = tcTVEngine::Get();

    if (optionsUpdateCounter % 101 == 0)
    {
        UpdateOptions();

        windowResizeOccurred = ResizeWindows(); // periodically check for window resize
        
        if (mbScenarioEdit)
        {
            wxString windowName = wxString::Format("gcblue - %s", simState->GetScenarioName());
            wxTopLevelWindow::SetTitle(windowName);
        }

        tcSound::Get()->Update(); // to update effect timeouts
    }

    optionsUpdateCounter++;

	tcTime::Get()->Update();

	if (meGameMode == GM_START)
    {
        static unsigned int startFrameCounter = 0;
        meScreenMode = START;
        if (!simState->IsMultiplayerClient())
        {
            startView->SetPlayEnabled(simState->msScenarioInfo.mbLoaded);
        }
        else
        {
            bool gameIsStarted = (simState->GetTime() > 0);
            startView->SetPlayEnabled(gameIsStarted);
            startView->SetGameStarted(gameIsStarted);
        }

        bool musicStarted = tcSound::Get()->IsMusicStarted();
        if (!musicStarted && (tcOptions::Get()->mbPlayMusic))
        {
            tcSound::Get()->PlayMusic("gcb_theme2");
        }

        tcSound::Get()->UpdateAutoMusic(0);

        tcMultiplayerInterface::Get()->Update();
        UpdateForScreenMode();

        startFrameCounter++;

        if (!windowResizeOccurred && (startFrameCounter > 6)) // to avoid glitches when resizing window at start, not sure if > 6 does anything useful
        {
            if (viewer->IsActive())
            {	
                viewer->Render();
            }

            engine->Frame();
        }
        else if (windowResizeOccurred)
        {
            startFrameCounter = 0; // reset this counter to allow a few frames for resize
        }

        if (mbQuit) simState->Clear(); // prevent crash when gameobj model deleted after 3D engine

        return mbQuit;
    }
    

	wxTimeSpan lcSpan;
	tcString cstring;
	int bResult;

	static int nCount = 0;

	static unsigned long snFrameCount = 0;

	LARGE_INTEGER nPerformanceCount;
	static LARGE_INTEGER snFrequency;
	static DWORD ndt;
	static float fdt;
	static LARGE_INTEGER snStartCount;
	static float sfFrameRate;
	const float dateTimeScale = 1.0f; // for testing sky effects
	static std::string dateTimeString = "---";
	bool isLagging = false;

	if (endGame)
	{
		EndGame();
		return UpdateStart();
	}

	if (nLastCount == 0)
	{
		bResult = QueryPerformanceCounter(&nPerformanceCount);

        wxASSERT(bResult);
		
		bResult = QueryPerformanceFrequency(&snFrequency);

		wxASSERT(bResult);

		nLastCount = nPerformanceCount.QuadPart;

		ndt = (DWORD)snFrequency.QuadPart/30; // 30 updates per second
		fdt = (1.0f/30.0f);

		snStartCount = nPerformanceCount;
	}

	// update multiplayer interface at start and end of this method
	tcMultiplayerInterface::Get()->Update();
    bool mpEntityUpdate = tcMultiplayerInterface::EntityUpdateReceived();

	// periodically reset frame counter
	if (snFrameCount % 150 == 0)
	{
		QueryPerformanceCounter(&snStartCount);
		snFrameCount = 0;
	}

	QueryPerformanceCounter(&nPerformanceCount);
    
    /// ------- TIME EXPERIMENT
    //LONGLONG time_reference = nPerformanceCount.QuadPart;
    //float tics_to_ms = 1000.0f/float(snFrequency.QuadPart);


	unsigned long deltaCount = nPerformanceCount.QuadPart-nLastCount;
    if (deltaCount < 8*ndt)
    {
        isLagging = false;
    }
    else
    {
        isLagging = true; // cannot maintain real time

        // if really far behind then give up and slip time
        if (deltaCount > 32*ndt)
        {
            nLastCount = nPerformanceCount.QuadPart - ndt;
            deltaCount = nPerformanceCount.QuadPart-nLastCount;
        }
    }


	if (deltaCount >= ndt)
	{
	    float clientSyncFactor = GetClientSyncFactor();
        float fdt2 = clientSyncFactor*fdt;

        SynchTimeAcceleration();

        simState->Update();

		gameTime = simState->GetTime();
		simState->GetDateTime(gameDateTime);
		if (!mbPaused)
		{
			gameTime += fdt2;
			gameDateTime.AdjustTimeSeconds(fdt2*dateTimeScale);
			simState->SetTime(gameTime);
			simState->SetDateTime(gameDateTime);
			if (accelerateTime)
			{
				for (int step=0;step<accelerateTime;step++)
				{
					simState->Update();
					gameTime += fdt2;
					gameDateTime.AdjustTimeSeconds(fdt2*dateTimeScale);
					simState->SetTime(gameTime);
					simState->SetDateTime(gameDateTime);
				}
			}
		}
		if (meScreenMode != START) directorTime += fdt2; // run director when not in simple brief mode
		dateTimeString = GetTimeString();
		
        if (mbScenarioEdit)
        {
            tacticalMap->mnGameMode = GAMEMODE_EDIT;
        }
        else
        {
            tacticalMap->mnGameMode = GAMEMODE_NORMAL;
            if (mbPaused)
            {
                tacticalMap->mnGameMode = GAMEMODE_PAUSED;
                char buff[16];
                sprintf(buff," [PAUSED]");
                dateTimeString += buff;
            }        
            else if (accelerateTime)
            {
                char buff[16];
                sprintf(buff," [%dx]",accelerateTime+1);
                dateTimeString += buff;
            }
            if (isLagging)
            {
                dateTimeString += " !";
            }
        }

		tacticalMap->SetDateTime(dateTimeString);
		viewer->SetGameTime(gameTime);


		nLastCount += ndt;
	}
    else if (mpEntityUpdate)
    {
        simState->Update();
    }

    /// ------- TIME EXPERIMENT
	//QueryPerformanceCounter(&nPerformanceCount);
	//float sim_time_ms = tics_to_ms * float(nPerformanceCount.QuadPart-time_reference);
 //   time_reference = nPerformanceCount.QuadPart;


	/* Skip director update for multiplayer until
	** this is fixed. Currently there is no way to send briefing
	** state over to client.
	*/
	if (multiplayerMode == 0)
	{
		director->Update(directorTime);
	}
	else
	{
		director->Update(1000);
	}

	ProcessCommandList();

    /// ------- TIME EXPERIMENT
	//QueryPerformanceCounter(&nPerformanceCount);
	//float command_time_ms = tics_to_ms * float(nPerformanceCount.QuadPart-time_reference);
 //   time_reference = nPerformanceCount.QuadPart;


	if (togglePopup) TogglePopup(); // added to avoid asynchronously toggling popup state

    objectControl->UpdateSymbolList(); // call here so that range circles are in sync with gameview symbols
	mcGameView.Update(gameTime);

	if (((snFrameCount % 8) == 0) && (oobView != 0))
	{
		oobView->Update();
	}

	// skip frames if lagging and server
	bool doRender = !isLagging || !tcMultiplayerInterface::Get()->IsServer() || 
		(snFrameCount % 8 == 0);

    /// ------- TIME EXPERIMENT
	//QueryPerformanceCounter(&nPerformanceCount);
	//float gameview_time_ms = tics_to_ms * float(nPerformanceCount.QuadPart-time_reference);
 //   time_reference = nPerformanceCount.QuadPart;

	if (doRender)
	{
		// Draw 2D windows
		UpdateForScreenMode();
	}


    /// ------- TIME EXPERIMENT
	//QueryPerformanceCounter(&nPerformanceCount);
	//float screenmode_time_ms = tics_to_ms * float(nPerformanceCount.QuadPart-time_reference);
 //   time_reference = nPerformanceCount.QuadPart;

	if (tcOptions::Get()->mbPlayMusic)
	{
		tcSound::Get()->UpdateAutoMusic(gameTime);
	}
	else
	{
		tcSound::Get()->StopMusic();
	}


	lcSpan = wxDateTime::Now() - startTime;

	if (snFrameCount % 90 == 0)
	{
		CheckGoals(); // checks win/loss goals and prints status
	}


    if (doRender && viewer->IsActive()) // if ((directorTime > 0.1f) && doRender)
	{	
        viewer->Render();
	}


    /// ------- TIME EXPERIMENT
	//QueryPerformanceCounter(&nPerformanceCount);
	//float render_time_ms = tics_to_ms * float(nPerformanceCount.QuadPart-time_reference);
 //   time_reference = nPerformanceCount.QuadPart;

    engine->Frame();

	snFrameCount++;

	if (snFrameCount > 30)
	{
		sfFrameRate = (float)snFrameCount/(float)(nPerformanceCount.QuadPart - snStartCount.QuadPart);
		sfFrameRate *= (float)snFrequency.QuadPart;
	}

	static wxString viewerText;
	if (size3D == MODE3D_SMALL)
	{
		viewerText = " "; // "" causes dropout of line objects in consoles
	}
	else 
	{
		viewerText = wxString::Format("%s [%.1f FPS]",dateTimeString.c_str(),sfFrameRate);
	}

	viewer->SetText( viewerText.c_str());

	tacticalMap->mfFrameRate = sfFrameRate;

	// update multiplayer interface at start and end of this method
	tcMultiplayerInterface::Get()->Update();

	tcSimPythonInterface::Get()->Update();

    /// ------- TIME EXPERIMENT
	//QueryPerformanceCounter(&nPerformanceCount);
	//float final_time_ms = tics_to_ms * float(nPerformanceCount.QuadPart-time_reference);
 //   time_reference = nPerformanceCount.QuadPart;

    //float total_time_ms = sim_time_ms + command_time_ms + gameview_time_ms +
    //    screenmode_time_ms + render_time_ms + final_time_ms;
    //if (total_time_ms > 50.0f)
    //{
    //    fprintf(stdout, "\nSlow detected at %.1f simtime, total: %.1f ms\n"
    //        "    sim: %.1f, cmd: %.1f, gvw: %.1f, sm: %.1f, rend: %.1f, fin: %.1f\n\n",
    //        simState->GetTime(), total_time_ms, 
    //        sim_time_ms, command_time_ms, gameview_time_ms, screenmode_time_ms, render_time_ms, final_time_ms);
    //}

    if (mbQuit) simState->Clear(); // prevent crash when gameobj model deleted after 3D engine

	return mbQuit;
}


/**
* Periodically call to check apply any recent changes to tcOptions
*/
void tcGame::UpdateOptions()
{
    tcOptions* options = tcOptions::Get();
    tcTVEngine* engine = tcTVEngine::Get();

    engine->UpdateOptions();
    tcUnits::Get()->Update();
    enableClientSync = (options->syncClient != 0);

    tcSound* sound = tcSound::Get();
    sound->SetEffectVolume(options->effectVolume);
    sound->SetMusicVolume(options->musicVolume);

    tcDatabaseObject::displayNATO = (options->natoNames != 0);

//#ifdef _DEBUG
    static float lastUpdateTime = 0;
    float t = simState->GetTime();
    if (lastUpdateTime > t) lastUpdateTime = t;

    if (((t - lastUpdateTime) >= 1.0) && options->OptionStringExists("EnableXmlLog"))
    {
        tcGameSerializer serializer;
        lastUpdateTime = t;

        wxXmlDocument doc;
        serializer.SaveToXml(doc);
        wxString fileName = wxString::Format("log/unit_state.xml");
        doc.Save(fileName, wxXML_NO_INDENTATION);
    }

//#endif
}




void tcGame::Activate() {}

bool tcGame::Finish()
{
	tcSound::Get()->UnInit();

	if (director) delete director;

	tcMultiplayerInterface::Get()->LogOutAllPlayers();

#ifdef _DEBUG
	tcSimPythonInterface::Get()->FlushLogs();
#endif

	return true;
}


/**
* @returns a time scale factor to try to keep client synchronized with server
* returns 1.0 if not multiplayer client
*/
float tcGame::GetClientSyncFactor()
{
    if (multiplayerMode != 1) return 1.0; // return 1.0 if not multiplayer client

    if (!enableClientSync) return 1.0;

    const float targetLag = -0.15f;
    float multiplayerTimeLag_s = (float)simState->GetMultiplayerTimeLag();

    // scale factor applies to simulation time step, so < 1 slows down client
    float scaleFactor = 1.0f + 0.5*(multiplayerTimeLag_s - targetLag);
    scaleFactor = std::min(scaleFactor, 1.05f);
    scaleFactor = std::max(scaleFactor, 0.95f);
   
    return scaleFactor;
}

bool tcGame::HandleEraseBkgnd(WXHDC hDC)
{
    return TRUE;
}

/**
* Hooks first friendly platform.
* Used to avoid blank 3D screen in rand scenario
*/
void tcGame::HookRandomFriendly()
{
	const unsigned maxPlats = 32;
	long id[maxPlats];

	int ownAlliance = userInfo->GetOwnAlliance();
	if (ownAlliance == 0) return; // no alliance selected yet (multiplayer)

	unsigned count = simState->GetAlliancePlatforms(&id[0], maxPlats, ownAlliance);

	if (count)
	{
		unsigned idx = rand() % count;
		NewHook(id[idx]);
	}
//#ifdef _DEBUG
//	else
//	{
//		fprintf(stderr, "tcGame::HookRandomFriendly - No friendlies found.\n");
//	}
//#endif
}

void tcGame::OnMouseMove(wxMouseEvent& event)
{

	if (meGameMode != GM_PLAY) return;

	// pass back to tactical map to cancel edge scroll
	if (tacticalMap->IsActive())
	{
		tacticalMap->CancelScroll();
	}
}

void tcGame::OnMouseWheel(wxMouseEvent& event) 
{
//    int jj = 3;
}

void tcGame::OnNcPaint(wxNcPaintEvent& event)
{
	wxPaintDC dc(this);
}

void tcGame::OnPaint(wxPaintEvent& event)
{
	wxPaintDC dc(this);
}

void tcGame::OnLButtonDown(wxMouseEvent& event)
{
	if (popupControl && (popupControl->mbActive))
	{
		popupControl->Freeze(); // to prevent flicker caused by paint event
		popupControl->SetActive(false);
	}


	event.Skip();
    
}

void tcGame::OnLButtonUp(wxMouseEvent& event)
{

}


void tcGame::OnLeaveWindow(wxMouseEvent& event)
{
	if (meGameMode != GM_PLAY) return;

	// pass back to tactical map to handle edge scroll
	if (tacticalMap->IsActive())
	{
		// use screen coords since this event is passed from a sub window with local coords
		wxPoint pos = wxGetMousePosition();
		tacticalMap->UpdateEdgeScroll(pos);
	}
}



bool tcGame::GetAppVersion(wchar_t* libName, unsigned short* majorVersion, unsigned short* minorVersion, unsigned short* buildNumber, unsigned short* revisionNumber)
{
    DWORD dwHandle, dwLen;
    UINT BufLen;
    LPTSTR lpData;
    VS_FIXEDFILEINFO *pFileInfo;

    dwLen = GetFileVersionInfoSizeW(libName, &dwHandle);
    if (!dwLen) 
        return FALSE;

    lpData = (LPTSTR) malloc (dwLen);
    if (!lpData) 
        return FALSE;

    if( !GetFileVersionInfo(libName, dwHandle, dwLen, lpData) )
    {
        free (lpData);
        return FALSE;
    }
    if( VerQueryValue( lpData, L"\\", (LPVOID*) &pFileInfo, (PUINT)&BufLen ) ) 
    {
        *majorVersion = HIWORD(pFileInfo->dwFileVersionMS);
        *minorVersion = LOWORD(pFileInfo->dwFileVersionMS);
        *buildNumber = HIWORD(pFileInfo->dwFileVersionLS);
        *revisionNumber = LOWORD(pFileInfo->dwFileVersionLS);
        free (lpData);
        return TRUE;
    }
    free (lpData);
    return FALSE;
}


/**
* @return current menu mode
* this menu mode sytem needs refactoring!
*/
teMenuMode tcGame::GetMenuMode()
{
	long hookID = tacticalMap->GetHookID();
	bool isGroupHooked = tacticalMap->GetHookCount() > 1;

    if (mbScenarioEdit)
    {
        bool isWeapon = (dynamic_cast<tcWeaponObject*>(simState->GetObject(hookID)) != 0);
        if (hookID == -1)
        {
            return MENUMODE_GAMEEDIT;
        }
        else if (isGroupHooked)
        {
            return MENUMODE_GROUPEDIT;
        }
        else if (isWeapon)
        {
            return MENUMODE_WEAPONEDIT;
        }
        else
        {
            return MENUMODE_PLATFORMEDIT;
        }
    }


	if (hookID==NULL_INDEX)
	{
		return MENUMODE_GAME;
	}



	// check alliance
	UINT nAlliance;
	simState->GetPlatformAlliance(hookID, nAlliance);

	if ((userInfo->IsOwnAlliance(nAlliance))||
        ((tcOptions::Get()->mnCommandMode == 0) && tcPlatformInterface::GetDeveloperMode()))
	{
		if (isGroupHooked)
		{
			return MENUMODE_GROUP;
		}
		else
		{
            if (dynamic_cast<tcWeaponObject*>(simState->GetObject(hookID)) == 0)
            {
			    return MENUMODE_PLATFORM;
            }
            else
            {
                return MENUMODE_WEAPON;
            }
		}
	}
	else
	{
		return MENUMODE_TRACK;
	}
}

/**
* @return string with UTC (Zulu) and local time
*/
const char* tcGame::GetTimeString()
{
    static wxString s;

    if (tacticalMap != 0)
    {
        int localOffset = int(0.0666666 * C_180OVERPI * tacticalMap->mfLonCenter);

        int year = gameDateTime.GetYear();
        int month = gameDateTime.GetMonth();
        int day = gameDateTime.GetDay();
        int hoursZulu = gameDateTime.GetHour();
        int minutes = gameDateTime.GetMinute();
        int seconds = gameDateTime.GetSecond();
        int hoursLocal = hoursZulu + localOffset;
        if (hoursLocal > 23) hoursLocal -= 24;
        else if (hoursLocal < 0) hoursLocal += 24;
        
        s.Printf("%4d/%02d/%02d %02d:%02d:%02dZ %02d%02dL", year, month, day, 
            hoursZulu, minutes, seconds, hoursLocal, minutes);
    }
    else
    {
        wxASSERT(false);
    }

    return s.c_str();
}

void tcGame::OnCloseWindow(wxCloseEvent& event)
{
    if (meGameMode != GM_START)
    {
        wxMessageDialog confirmQuit(this, "Exit game?", "Confirm", wxOK | wxCANCEL, wxDefaultPosition);
        if (confirmQuit.ShowModal() == wxID_OK)
        {
            EndGame();
        }
    }
    else // exit to desktop
    {
        mbQuit = true;
    }
	return;
}

void tcGame::OnRButtonDown(wxMouseEvent& event)
{
    if (event.ControlDown())
    {
        event.Skip(); // to pass back to map for zoom out
        return;
    }

	rightButtonPoint = event.GetPosition();
	togglePopup = true;
}

void tcGame::OnSize(wxSizeEvent& event)
{
    //wxSize size = event.GetSize();
    wxSize size = GetClientSize();
    updatedWindowSize = size;
}

/**
* 
*/
void tcGame::TogglePopup()
{
	togglePopup = false; // clear

	if (!popupControl)
	{
		return;
	}
	popupControl->Freeze(); // to prevent flicker caused by paint event

	if (popupControl->mbActive)
	{
		popupControl->SetActive(false);
	}
	else
	{
        ValidateHooked();
		teMenuMode mm = GetMenuMode();
		popupControl->SetMenu(mm);

		wxPoint point = rightButtonPoint;
		// workaround to keep popup submenus on screen
		if (point.x > mnWidth - 250) point.x = mnWidth - 250;
		if (point.y > mnHeight - 200) point.y = mnHeight - 200;
		popupControl->Track(point);
	}
}

/**
* OnKeyDown is called for any key press that isn't captured by another
* application. This includes pressing Shift, CTRL, etc. If the key is a
* character then a call to OnChar will follow.
*/
void tcGame::OnKeyDown(wxKeyEvent& event) 
{
	int nChar = event.GetKeyCode();
	bool controlDown = (event.ControlDown() && (nChar != WXK_CONTROL));
//	bool altDown = event.AltDown();


	if (meGameMode == GM_START)
	{
        event.Skip();
		return;
	}	
	
	/* If control is down and character is a number, set user selected group
	*/
	if (controlDown)
	{
		wxString s = wxString::Format("%c", nChar);
		int val = (int)strtol(s.c_str(), 0, 10);
		if ((val >= 1) && (val <= 9))
		{
			tcUserSelectedGroups* groupCtrl = tcUserSelectedGroups::Get();

			groupCtrl->SetGroup(val, hookedUnits);
            s = wxString::Format("Formed group %d (%d units)\n", val, hookedUnits.size());
            DisplayMessage(s.c_str());
			return;
		}
	}

    event.Skip();

}


void tcGame::Minimize3D(wxCommandEvent& event)
{
	if (!mb3DActive) return; // already fully minimized

	if (size3D == MODE3D_FULL)
	{
		size3D = MODE3D_MEDIUM;
	}
	else if (size3D == MODE3D_MEDIUM)
	{
		size3D = MODE3D_SMALL;
	}
	else
	{
		mb3DActive = false;
	}

	Update3DSize();
}

void tcGame::Maximize3D(wxCommandEvent& event)
{
	if (size3D == MODE3D_FULL) return; // already fully maximized

	if (!mb3DActive)
	{
		mb3DActive = true;
		size3D = MODE3D_SMALL;
	}
	else if (size3D == MODE3D_SMALL)
	{
		size3D = MODE3D_MEDIUM;
	}
	else
	{
		size3D = MODE3D_FULL;
	}

	Update3DSize();
}


/**
* Update member objects with new hook ID.
* hook ID is stored in event.m_extraLong
*/
void tcGame::NewGroupHook(wxCommandEvent& event)
{
	long hookCount = event.GetExtraLong(); // 2.6.3 m_extraLong;

	//long* groupList = reinterpret_cast<long*>(event.m_clientData); // 2.6.3 code
    long* groupList = reinterpret_cast<long*>(event.GetClientData());

	std::vector<long> groupUnits;
	for (int n = 0; n < hookCount; n++)
	{
		groupUnits.push_back(groupList[n]);
	}

    NewGroupHook(groupUnits);

	// delete event.m_clientData; // 2.6.3 code, is this necessary?
}

/**
*
*/
void tcGame::NewGroupHook(std::vector<long>& groupUnits)
{
	size_t hookCount = groupUnits.size();

	if (hookCount == 0) 
	{
		groupUnits.push_back(-1); // clear hook with -1
		hookCount = 1;
	}

	long primaryHook = groupUnits[0];

	if (hookCount == 1)
	{
		NewHook(primaryHook);
		return;
	}
	
    tacticalMap->SetGroupHook(groupUnits);
	hookInfo->SetHookID(primaryHook);
	oobView->SetHookID(primaryHook);
	objectControl->SetHookID(groupUnits);
	viewer->SetHookID(primaryHook);
	tcGameObject::SetHookedId(primaryHook);
	
	pythonInterface->SetMenuGroup(groupUnits);

	hookedUnits = groupUnits;

	tcSound::Get()->PlayEffect("ShortBeep");
}

/**
* Update member objects with new hook ID.
* hook ID is stored in event.m_extraLong
*/
void tcGame::NewHook(wxCommandEvent& event)
{
	long nHookID = event.GetExtraLong(); // 2.6.3 m_extraLong;

	NewHook(nHookID);
}

/**
* Updates member objects with new hook ID.
* hookID = -1 is used to clear the hooked obj
* This was modified to check for null objects so that
* it works when called in start screen mode.
*/
void tcGame::NewHook(long hookID)
{
    if (!simState->IsMultiplayerClient())
    {
        if (simState->GetObject(hookID) == 0)
        {
            hookID = -1;
        }
    }
    else
    {
        tcSensorMapTrack track;
        if (!simState->GetTrack(hookID, tcUserInfo::Get()->GetOwnAlliance(), track))
        {
            hookID = -1;
        }
    }

	tacticalMap->SetHookID(hookID);
	if (hookInfo) hookInfo->SetHookID(hookID);
	if (oobView) oobView->SetHookID(hookID);
	if (objectControl) objectControl->SetHookID(hookID);
	viewer->SetHookID(hookID);
	pythonInterface->SetMenuPlatform(hookID);
    tcGameObject::SetHookedId(hookID);

	hookedUnits.clear();
	hookedUnits.push_back(hookID);

	if (hookID != NULL_INDEX)
	{
		tcSound::Get()->PlayEffect("ShortBeep");
	}

}

/**
* @return next value in sequence, up/down based on goFaster
* values are accel scale factor minus 1, e.g. 0 is real time
*/
int tcGame::NextTimeAccelVal(int current, bool goFaster) const
{
    // allow faster than
    if (tcPlatformInterface::IsDeveloperModeStatic())
    {
        if (current >= 119)
        {
            if (goFaster)
            {
                return (2*current + 1);
            }
            else
            {
                return ((current -1)/2);
            }
        }
    }

    if (goFaster)
    {
        switch (current)
        {
        case 0: return 1; // 1X -> 2X
        case 1: return 3; // 2X -> 4X
        case 3: return 9; // 4X -> 10X
        case 9: return 29; // 10X -> 30X
        case 29: return 59; // 30X -> 60X
        case 59: return 119; // 60X -> 120X
        default: return std::min(current, 119);
        }
    }
    else
    {
        switch (current)
        {
        case 1: return 0; // 2X -> 1X
        case 3: return 1; // 4X -> 2X
        case 9: return 3; // 10X -> 4X
        case 29: return 9; // 30X -> 10X
        case 59: return 29; // 60X -> 30X
        case 119: return 59; // 120X -> 60X
        default: return std::min(current, 119);
        }
    }

}

void tcGame::OnChar(wxKeyEvent& event)
{
	int nChar = event.GetKeyCode();
	bool controlDown = event.ControlDown();
	bool altDown = event.AltDown();


	if (meGameMode == GM_START)
	{
		switch(nChar)
		{
		case WXK_ESCAPE:
			mbQuit = true;
			return;
		default:
			return;
		}
	}

	/* If control is down and character is a number, set user selected group
	** If Alt is down, set group hook to user selected group (if group is empty
	** clear the current hook)
	*/
	if (altDown)
	{
		switch (nChar)
		{
        case 'D':
            SetDeveloperMode(true);
            break;
        case 'T':
            {
                tsCommandInfo cmd;
                TextCommandToggleUserAlliance(cmd);
            }
            break;
        case 'I':
            SetInGame(true);
            break;
        case 'O':
            SetInGame(false);
            break;
        case '[':
            {
            int theaterDecimation = mapData->GetTheaterDecimation();

            switch (theaterDecimation)
            {
            case 16: TheaterMediumRes(); break;
            case 4: TheaterHighRes(); break;
            }
            break;
            }
        case ']':
            {
            int theaterDecimation = mapData->GetTheaterDecimation();

            switch (theaterDecimation)
            {
            case 1: TheaterMediumRes(); break;
            case 4: TheaterLowRes(); break;
            }
            break;
            }
		}
		
		return;
	}

	if (controlDown)
    {
		switch (nChar)
		{
		case ('r'-'a'+1): // CTRL+r
            {
                tsCommandInfo cmd;
                TextCommandReimportPython(cmd);
            }
			return;
		}
        return;
    }

	// first check for control key or priority game command key
	switch(nChar)
	{
	case 'a':
	case '+':
        SetTimeAccel(101);
		//accelerateTime = 2*(accelerateTime + 1) - 1; 
  //      if (accelerateTime > 31)
		//{
		//	accelerateTime = 31;
		//}
		return;
	case 'c': // toggle chat box
		chatBox->SetActive(!chatBox->mbActive);
		if (chatBox->mbActive) chatBox->MoveToTop();
		return;
	case 'i': // database info popup
		ShowDatabaseInfo();
		return;
    case 'p':
        SetTimeAccel(100);
		//if (!mbScenarioEdit) mbPaused = !mbPaused;
		return;
	case 'A':
	case '-':
        SetTimeAccel(99);
		//accelerateTime = (accelerateTime + 1)/2 - 1; 
  //      if (accelerateTime < 0)
		//{
		//	accelerateTime = 0;
		//}
		return;
	case 'F':
		viewer->ToggleFog();
		return;
	case 'T':
		viewer->SetTerrainActive(!viewer->GetTerrainActive());
		return;
	case WXK_ESCAPE:
		ProcessEsc();
		return;
	case WXK_F1:
		meScreenMode = TACTICAL;
		return;
	case WXK_F2:
        meScreenMode = START;
        startView->SetPane("Options");
		return;
	case WXK_F3:
		Toggle3DSize();
		return;
	case WXK_F4: // toggle 3D active
		mb3DActive = !(viewer->IsActive());

        if (tcOptions::Get()->minimal3D != 0)
        {
            mb3DActive = false;
        }

		return;
	case WXK_F5:
		// toggle briefing screen mode
		//if (meScreenMode == TACTICAL)
		//{
		//	meScreenMode = TACTICALBRIEF;
		//}
		//else if (meScreenMode == TACTICALBRIEF)
		//{
		//	meScreenMode = TACTICAL;
		//}
		return;
	case WXK_F6:
		if (multiplayerMode != 0)
		{
			if (meScreenMode == START)
			{
				meScreenMode = TACTICAL;
			}
			else
			{
				meScreenMode = START;
                startView->SetPane("Multiplayer");
			}
		}
		return;
    case WXK_F7:
        if (meGameMode != GM_PLAY) return;
        if (meScreenMode == START)
        {
            meScreenMode = TACTICAL;
        }
        else
        {
            meScreenMode = START;
            startView->SetPane("Scenario");
            scenarioSelectView->SetTab("Messages");
        }
		return;
	case WXK_F8:
		viewer->ToggleWireframe();
        return;
    case WXK_F10:
        if (tcPlatformInterface::GetDeveloperMode())
        {
            ShiftTime(-900.0); // jump 15 minutes back
        }
        return;
    case WXK_F11:
        if (tcPlatformInterface::GetDeveloperMode())
        {
            ShiftTime(900.0); // jump 15 minutes ahead
        }
        return;
	case WXK_HOME:
        if (tcPlatformInterface::GetDeveloperMode())
        {
            SetScenarioEdit(!mbScenarioEdit);
        }
		return;
	}

	// pass key to python if exactly one object is hooked (no group support yet)
	if (tacticalMap->GetHookCount() == 1)
	{
		pythonInterface->ProcessHotKey(nChar, 0);
		return;
	}
    else if (tacticalMap->GetHookCount() > 1)
    {
		pythonInterface->ProcessHotKeyGroup(nChar, 0);
		return;
    }

	// otherwise process game level key command
	switch(nChar)
	{
	case '[':
		break;
	default:
		break;
	}
}

void tcGame::OnEraseBackground(wxEraseEvent& event) {}

void tcGame::ProcessCommandList()
{
	for (unsigned nCmd=0; nCmd < commandQueue->mnCount; nCmd++)
	{
		tsCommandInfo cmd_info;

		if (commandQueue->GetCommand(cmd_info))
		{
			switch (cmd_info.commandType)
			{
			case PYTHON_CALLBACK:
				ProcessCallback(cmd_info);
				break;
			case PYTHON_USERINPUT:
				if (cmd_info.platformID.size() == 0) cmd_info.platformID = tacticalMap->GetHookedGroup();
				GetUserInput(cmd_info);
				break;
			case PYTHON_COMMAND_TEXT:
				{
					std::string s = cmd_info.mzString;
					int param = cmd_info.mnData;
					pythonInterface->ProcessCommand(s, cmd_info.platformID, 
						param, cmd_info.textParam);
				}
				break;
			case PYTHON_COMMAND_GENERAL:
				{
					std::string s = cmd_info.mzString;
					pythonInterface->ProcessCommandWithArguments(s, cmd_info.platformID, cmd_info.textParam);
				}
				break;
			case GAME_COMMAND:
				if (cmd_info.meCmd == GC_TEXTCOMMAND)
				{
					ProcessTextCommand(cmd_info);
				}
				else if (cmd_info.meCmd == GC_DISPLAYMESSAGE)
				{
					infoConsole->Print(cmd_info.mzString);
				}
				else if (cmd_info.meCmd == GC_QUIT)
				{
					wxMessageDialog confirmQuit(this, "End game?", "Confirm", wxOK | wxCANCEL, wxDefaultPosition);
					if (confirmQuit.ShowModal() == wxID_OK)
					{
						endGame = true; // end game at next safe opportunity
					}
				}
				else if (cmd_info.meCmd == GC_QUITTODESKTOP)
				{
					wxMessageDialog confirmQuit(this, "Quit to desktop?", "Confirm", wxOK | wxCANCEL, wxDefaultPosition);
					if (confirmQuit.ShowModal() == wxID_OK)
					{
						mbQuit = true;
					}
				}
				else if (cmd_info.meCmd == GC_SHOWBRIEFING)
				{
					meScreenMode = START;
                    startView->SetPane("Scenario");
				}
				else if (cmd_info.meCmd == GC_SHOWMISSIONSTATUS)
				{
					meScreenMode = START;
                    startView->SetPane("Scenario");
					messageCenter->ActivateChannel("Mission");
				}
				else if (cmd_info.meCmd == GC_SAVEGAME)
				{
                    wxDateTime now = wxDateTime::Now();

                    if (mbScenarioEdit)
                    { 
                        // save in both binary and python mode 
                        wxString scenarioName(simState->GetScenarioName());
                        scenarioName.Replace(wxT(" "), wxT("_"));

                        wxDateTime now = wxDateTime::Now();
                        wxString saveName = wxString::Format("scenarios//EditorSaved//%s_%02d_%02d_%02d%02d%02d_PY",
                            scenarioName.c_str(), now.GetMonth()+1, now.GetDay(), now.GetHour(), now.GetMinute(), now.GetSecond());
                        simState->SaveToPython(saveName.ToStdString());

                        saveName = wxString::Format("scenarios//EditorSaved//%s_%02d_%02d_%02d%02d%02d_DAT",
                            scenarioName.c_str(), now.GetMonth()+1, now.GetDay(), now.GetHour(), now.GetMinute(), now.GetSecond());
                        tcGameSerializer gameSaver;
						gameSaver.SaveToBinary(saveName.ToAscii());
                    }
                    else
                    {
                        wxString scenarioName(simState->GetScenarioName());
                        scenarioName.Replace(wxT(" "), wxT("_"));
					
					    wxString saveName = wxString::Format("scenarios//Saved//%s.dat",
                            scenarioName.c_str());
                        saveName.Replace(",", "");
                        saveName.Replace(":", "");

                        tcGameSerializer gameSaver;
                        gameSaver.SaveToBinary(saveName.c_str()); // will overwrite last save

						// also save backup
					    wxString backupSaveName = wxString::Format("scenarios//Saved//backup//%s_%02d_%02d_%02d%02d%02d.dat",
                            scenarioName.c_str(),
                            now.GetMonth()+1, now.GetDay(), now.GetHour(), now.GetMinute(), now.GetSecond());
						::wxCopyFile(saveName.c_str(), backupSaveName.c_str(), false);
                    }
				}
				else
				{
					fprintf(stderr, "Unrecognized game command (%d)\n", cmd_info.meCmd);
				}

				break;
			default:
				fprintf(stderr, "Unrecognized command type (%d)\n", cmd_info.commandType);
				break;
			} // switch
		}
	}
}

/**
* Process ESC key event. Cancels GUI command if active,
* otherwise quits the game.
*/
void tcGame::ProcessEsc()
{
	if (popupControl->mbActive)
	{
		popupControl->SetActive(false);
		return;
	}
	else if (tacticalMap->IsMapCmdActive())
	{
		tacticalMap->DeactivateMapCommand();
		return;
	}
    else if (chatBox->mbActive)
    {
        chatBox->SetActive(false);
        return;
    }


	wxMessageDialog confirmQuit(this, "Exit game?", "Confirm", wxOK | wxCANCEL, wxDefaultPosition);
	if (confirmQuit.ShowModal() == wxID_OK)
	{
		EndGame();
	}
}


/**
* Calls Python callback
*/
void tcGame::ProcessCallback(tsCommandInfo& cmd)
{
	// done this way for easy compatibility with old code body
	char* azCallback = cmd.mzString;
	char* azUserInput = cmd.mzUserInput;
	std::vector<long>& id = cmd.platformID;
	int param = cmd.mnData;
	const std::string& textParam = cmd.textParam;

    wxString userInput(azUserInput);
    userInput = userInput.BeforeFirst(' ');

	if (userInput == "Heading")
	{
		float fHeading = tacticalMap->GetMapCmdHeading();
		pythonInterface->ProcessCallback(azCallback, id, fHeading, param, textParam);
	}
	else if (userInput == "Target")
	{
		long nTarget = tacticalMap->GetMapCmdTarget();
		pythonInterface->ProcessCallback(azCallback, id, nTarget, param, textParam);
	}
	else if (userInput == "Datum")
	{
		tcPoint p;
		tacticalMap->GetMapCmdDatum(p);
		pythonInterface->ProcessCallback(azCallback, id, p.x, p.y, param, textParam);
	}
    else if (userInput == "Box")
    {
		tcPoint p1;
        tcPoint p2;
		tacticalMap->GetMapCmdDatum(p1);
        tacticalMap->GetMapCmdDatum2(p2);
        wxString s;
        s.Printf("%f,%f,%f,%f", p1.x, p1.y, p2.x, p2.y);
        if (param != -1) s += wxString::Format(",%d", param);
        pythonInterface->ProcessCallbackArgList(azCallback, id, s.ToStdString());
    }
    else if (userInput == "Line")
    {
		tcPoint p1;
        tcPoint p2;
		tacticalMap->GetMapCmdDatum(p1);
        tacticalMap->GetMapCmdDatum2(p2);
        wxString s;
        s.Printf("%f,%f,%f,%f", p1.x, p1.y, p2.x, p2.y);
        if (param != -1) s += wxString::Format(",%d", param);
        pythonInterface->ProcessCallbackArgList(azCallback, id, s.ToStdString());
    }
	else if (userInput == "Text")
	{
        std::string s; /// don't need single quotes any more, triple quoting JUN2010 ("'");
        s += cmd.textParam;
        //s += "'";
		pythonInterface->ProcessCallback(azCallback, id, s, param);
	}
	else if (userInput == "Null") // necessary? or always handled in GetUserInput
	{
		pythonInterface->ProcessCallback(azCallback, id);
	}
	else 
	{
		fprintf(stderr, "tcGame::ProcessCallback -- unrecognized user input field (%s)\n",
            userInput.c_str());
	}
}

/**
* Gets user input for Python call back and then calls Python callback
*/
void tcGame::GetUserInput(const tsCommandInfo& cmd)
{
	const char* azCallback = cmd.mzString;
	const char* azUserInput = cmd.mzUserInput;
	std::vector<long> id = cmd.platformID;
	int param = cmd.mnData;

	tacticalMap->SetMapCmdCallback(azCallback, id, param, cmd.textParam);


    wxString userInput(azUserInput);
    wxString userInputRoot(userInput.BeforeFirst(' '));


	if (userInputRoot == "Heading")
	{
		tacticalMap->ActivateMapCommand(MC_HEADING);
	}
	else if (userInputRoot == "Target")
	{
		tacticalMap->ActivateMapCommand(MC_TARGET);
	}
	else if (userInputRoot == "Datum")
	{
		tacticalMap->ActivateMapCommand(MC_DATUM);
	}
    else if (userInputRoot == "Box")
    {
        tacticalMap->ActivateMapCommand(MC_BOX);
    }
    else if (userInputRoot == "Line")
    {
        tacticalMap->ActivateMapCommand(MC_LINE);
    }
	else if (userInputRoot == "Text")
	{
        wxString textCaption(userInput.AfterFirst(' '));
        if (textCaption.size() == 0)
        {
            textCaption = "Enter text";
        }

		tsCommandInfo callbackCmd = cmd;
		callbackCmd.commandType = PYTHON_CALLBACK;

		tcTextEntryBox* textEntry = new tcTextEntryBox(wxPoint(mnWidth/2-100, mnHeight/2-30), wxSize(210, 60));
        textEntry->SetCaption(textCaption.ToStdString());
		textEntry->SetCommand(callbackCmd);
        textEntry->SetActive(true);
        textEntry->Raise();
        
	}
    else if (userInputRoot == "File")
    {
        wxString wildCard(userInput.AfterFirst(' '));
        if (wildCard.size() == 0)
        {
            wildCard = "*.*";
        }

        wxFileDialog fileDialog(this, "Choose a file", "", "", wildCard);
        if (fileDialog.ShowModal() == wxID_OK)
        {
            wxString filePath(fileDialog.GetPath());
            for (size_t n=0; n<filePath.size(); n++)
            {
                wxChar cn = filePath[n];
                if (filePath[n] == wxChar('\\'))
                {
                    filePath.SetChar(n, '/');
                }
            }

            std::string filePath2(filePath.c_str()); // full path and filename

            std::string callback(cmd.mzString);
            pythonInterface->ProcessCallback(callback, id, filePath2, param);
        }
    }
    else if (userInputRoot == "Paragraph")
    {
        wxString startText;
        wxString caption(userInput.AfterFirst(' '));

        if (caption == "ScenarioDescription")
        {
            caption = "Enter scenario description";
            startText = simState->GetScenarioDescription();
        }
        else if (caption == "Briefing")
        {
            caption = "Enter briefing text";
            tcScenarioInterface* scenarioInterface = tcSimPythonInterface::Get()->GetScenarioInterface();
            startText = scenarioInterface->GetSimpleBriefing(userInfo->GetOwnAlliance()).c_str();
        }
        else
        {
            caption = "Enter text";
        }

        tcTextDialog inputDialog(tacticalMap, -1, caption, startText,
            wxPoint(200, 150), wxSize(400, 250) );

        if (inputDialog.ShowModal() != wxID_OK) return;

        wxString dialogText = inputDialog.GetText();

        std::string dialogText2(dialogText.c_str());

        std::string callback(cmd.mzString);
        pythonInterface->ProcessCallback(callback, id, dialogText2, param);
    }
    else if (userInputRoot == "Null")
	{
		pythonInterface->ProcessCallback(azCallback, id);
	}
	else
	{
		tacticalMap->SetMapCmdCallback("", id, -1, "");
	}
}



void tcGame::TextCommandShowFlightPanel(const tsCommandInfo& cmd)
{
    tcPlatformObject* platform = tcSimPythonInterface::Get()->GetHookedObj();
    tcFlightPort* flightPort = tcSimPythonInterface::Get()->GetHookedObjFlightPort();
    if (flightPort)
    {
        // Freeze() to prevent flicker, not sure why this works
        /*
        popupControl->Freeze(); 
        popupControl->SetMenu(MENUMODE_FLIGHTPANEL);
        popupControl->Track(wxPoint(mrectMap.left+220,mrectMap.top+70));
        */

        std::string xmlFile;
        if (flightPort->GetHangarCapacity() > 20)
        {
            xmlFile = "xml/flightport_gui_large.xml";
        }
        else
        {
            xmlFile = "xml/flightport_gui_default.xml";
        }

        tcFlightPortGui* existingGui = tcFlightPortGui::GetExistingGui(platform->mnID);
        if (existingGui == 0)
        {
            tcFlightPortGui* gui = new tcFlightPortGui(platform->mnID, wxPoint(250, 200), xmlFile.c_str());
        }
        else// toggle close if exists already
        {
            existingGui->DestroyWindow();
        }
    }
}

void tcGame::TextCommandShowStoresPanel(const tsCommandInfo& cmd)
{
    if (tcPlatformObject* obj = tcSimPythonInterface::Get()->GetHookedObj())
    {
        if (tcStores* stores = obj->GetMagazine(0))
        {
            tcStoresGui* existingGui = tcStoresGui::GetExistingGui(obj->mnID, -1);
            if (existingGui == 0)
            {
                tcStoresGui* gui = new tcStoresGui(obj->mnID, -1, 0, wxPoint(500, 200), "xml/stores_gui_table.xml");
            }
            else// toggle close if exists already
            {
                existingGui->DestroyWindow();
            }

        }
    }
}

void tcGame::TextCommandShowPlatformPanel(const tsCommandInfo& cmd)
{
    tcPlatformObject* obj = tcSimPythonInterface::Get()->GetHookedObj();
    if (obj)
    {
        tcPlatformGui* existingGui = tcPlatformGui::GetExistingGui(obj->mnID, -1);
        if (existingGui == 0)
        {
            tcPlatformGui* gui = new tcPlatformGui(obj->mnID, -1, wxPoint(220, 70), "xml/platform_gui_default.xml");
        }
        else // toggle close if exists already
        {
            existingGui->DestroyWindow();
        }
    }
}

void tcGame::TextCommandShowSonarPanel(const tsCommandInfo& cmd)
{
	if (!tcPlatformInterface::GetDeveloperMode() && !tcGameObject::IsEditMode()) return;

    ShowSonarPanel();
}

void tcGame::TextCommandCopperMap(const tsCommandInfo& cmd)
{
    tcOptions::Get()->mnMapMode = 0;
    RefreshMaps();
}

void tcGame::TextCommandYellowBlueMap(const tsCommandInfo& cmd)
{
    tcOptions::Get()->mnMapMode = 1;
    RefreshMaps();
}

void tcGame::TextCommandBlackBlueMap(const tsCommandInfo& cmd)
{
    tcOptions::Get()->mnMapMode = 2;
    RefreshMaps();
}

void tcGame::TextCommandReimportPython(const tsCommandInfo& cmd)
{
    if (!tcPlatformInterface::GetDeveloperMode()) return;

    tcSimPythonInterface::Get()->ReimportModules();

    infoConsole->Print("Reimporting python");
}

void tcGame::TextCommandSetFormationEditId(const tsCommandInfo& cmd)
{
    long id = long(cmd.mnData);
    if (tacticalMap != 0)
    {
        tacticalMap->SetFormationEditId(id);
    }
    else
    {
        wxASSERT(false);
    }
}



void tcGame::TextCommandShowAirInfo(const tsCommandInfo& cmd)
{
    if (!tcPlatformInterface::GetDeveloperMode()) return;
    ShowAirInfo();
}

void tcGame::TextCommandTestCollision(const tsCommandInfo& cmd)
{
    if (!tcPlatformInterface::GetDeveloperMode()) return;
    TestCollision();
}

void tcGame::TextCommandTestCrossSection(const tsCommandInfo& cmd)
{
    if (!tcPlatformInterface::GetDeveloperMode()) return;
    TestCrossSection();
}

void tcGame::TextCommandToggleUserAlliance(const tsCommandInfo& cmd)
{
    if (!tcPlatformInterface::GetDeveloperMode()) return;
    simState->ToggleUserAlliance();
	tacticalMap->UpdateROEButtons();
    infoConsole->Print("Toggling user alliance");
}

void tcGame::TextCommandShowPlatformDebug(const tsCommandInfo& cmd)
{
    if (!tcPlatformInterface::GetDeveloperMode()) return;
    ShowPlatformDebug();
}



/**
* Call once at startup
*/
void tcGame::RegisterTextCommands()
{
    textCommands.clear();

    textCommands["ShowFlightPanel"] = &tcGame::TextCommandShowFlightPanel;
    textCommands["ShowStoresPanel"] = &tcGame::TextCommandShowStoresPanel;
    textCommands["ShowPlatformPanel"] = &tcGame::TextCommandShowPlatformPanel;
    textCommands["CopperMap"] = &tcGame::TextCommandCopperMap;
    textCommands["YellowBlueMap"] = &tcGame::TextCommandYellowBlueMap;
    textCommands["BlackBlueMap"] = &tcGame::TextCommandBlackBlueMap;
    textCommands["SetFormationEditId"] = &tcGame::TextCommandSetFormationEditId;

    // "dev mode" commands
    textCommands["ShowAirInfo"] = &tcGame::TextCommandShowAirInfo;
    textCommands["TestCollision"] = &tcGame::TextCommandTestCollision;
    textCommands["TestCrossSection"] = &tcGame::TextCommandTestCrossSection;
    textCommands["ToggleUserAlliance"] = &tcGame::TextCommandToggleUserAlliance;
    textCommands["ShowPlatformDebug"] = &tcGame::TextCommandShowPlatformDebug;
    textCommands["ShowSonarPanel"] = &tcGame::TextCommandShowSonarPanel;
    textCommands["ReimportPython"] = &tcGame::TextCommandReimportPython;

}


/**
* command string is contained in cmd_info.mzString, this is the text version
* of ProcessCommand. Currently used for special commands originated in Python,
* such as "ShowFlightPanel".
*/
void tcGame::ProcessTextCommand(tsCommandInfo cmd_info)
{
	std::string s = cmd_info.mzString;

    std::map<std::string, commandFunctionPtr>::iterator iter = 
        textCommands.find(s);

    if (iter != textCommands.end())
    {
        (this->*iter->second)(cmd_info);
    }
    else
    {
        fprintf(stderr, "Unrecognized text command (%s)\n", s.c_str());
        wxASSERT(false);
    }

#if 0
	if (s == "ShowFlightPanel")
	{	
		tcPlatformObject* platform = tcSimPythonInterface::Get()->GetHookedObj();
		tcFlightPort* flightPort = tcSimPythonInterface::Get()->GetHookedObjFlightPort();
		if (flightPort)
		{
			// Freeze() to prevent flicker, not sure why this works
			/*
			popupControl->Freeze(); 
			popupControl->SetMenu(MENUMODE_FLIGHTPANEL);
			popupControl->Track(wxPoint(mrectMap.left+220,mrectMap.top+70));
			*/

            std::string xmlFile;
            if (flightPort->GetHangarCapacity() > 20)
            {
                xmlFile = "xml/flightport_gui_large.xml";
            }
            else
            {
                xmlFile = "xml/flightport_gui_default.xml";
            }

            tcFlightPortGui* existingGui = tcFlightPortGui::GetExistingGui(platform->mnID);
            if (existingGui == 0)
            {
                tcFlightPortGui* gui = new tcFlightPortGui(platform->mnID, wxPoint(250, 200), xmlFile.c_str());
            }
            else// toggle close if exists already
            {
                existingGui->DestroyWindow();
            }
		}
	}
	else if (s == "ShowStoresPanel")
	{
		if (tcPlatformObject* obj = tcSimPythonInterface::Get()->GetHookedObj())
		{
            if (tcStores* stores = obj->GetMagazine(0))
            {
                tcStoresGui* existingGui = tcStoresGui::GetExistingGui(obj->mnID, -1);
                if (existingGui == 0)
                {
                    tcStoresGui* gui = new tcStoresGui(obj->mnID, -1, 0, wxPoint(500, 200), "xml/stores_gui_table.xml");
                }
                else// toggle close if exists already
                {
                    existingGui->DestroyWindow();
                }

            }
		}
	}
	else if (s == "ShowPlatformPanel")
	{
		tcPlatformObject* obj = tcSimPythonInterface::Get()->GetHookedObj();
		if (obj)
		{
            tcPlatformGui* existingGui = tcPlatformGui::GetExistingGui(obj->mnID, -1);
            if (existingGui == 0)
            {
			    tcPlatformGui* gui = new tcPlatformGui(obj->mnID, -1, wxPoint(220, 70), "xml/platform_gui_default.xml");
            }
            else // toggle close if exists already
            {
                existingGui->DestroyWindow();
            }
		}
	}
	else if (s == "CopperMap")
	{
		tcOptions::Get()->mnMapMode = 0;
		RefreshMaps();
	}
	else if (s == "YellowBlueMap")
	{
		tcOptions::Get()->mnMapMode = 1;
		RefreshMaps();
	}
	else if (s == "BlackBlueMap")
	{
		tcOptions::Get()->mnMapMode = 2;
		RefreshMaps();
	}
    else if (s == "SetFormationEditId")
    {
        long id = long(cmd_info.mnData);
        if (tacticalMap != 0)
        {
            tacticalMap->SetFormationEditId(id);
        }
        else
        {
            wxASSERT(false);
        }
    }
#endif

}


/**
* Used for quick mouse-targeting of another platform.
* Map posts this event when right mouse button is 
* clicked over another platform.
* Python script is used to do the targeting to allow
* this to be customized.
*/
void tcGame::SecondaryHook(wxCommandEvent& event)
{
	long hookID = tacticalMap->GetHookID();
	long nSecondaryHookID = event.GetExtraLong(); // 2.6.3 m_extraLong;

	if ((hookID == NULL_INDEX) || (hookID == nSecondaryHookID))
	{
		return;
	}
	pythonInterface->ProcessSecondaryHook(nSecondaryHookID);

}

/**
* After game started, calculates collision point on current hooked obj
* based on look direction and position of camera. If collision occurs, 
* adds explosion graphic to obj at collision point
*/
void tcGame::TestCollision()
{
    if (meGameMode == GM_START) return; // ignore if game has not started

    infoConsole->Print("Testing collision");


    float cameraAz = viewer->GetCameraAz();
    float cameraEl = viewer->GetCameraEl();
    float cameraRange = viewer->GetCameraRange();

    float camx = -cosf(cameraEl)*sinf(cameraAz);
    float camz = -cosf(cameraEl)*cosf(cameraAz);
    float camy = -sinf(cameraEl);



    



    long hookID = tacticalMap->GetHookID();

    tcGameObject* hookedObj = simState->GetObject(hookID);
    if (hookedObj == 0) return;




    Vec3 start_eun(-camx*cameraRange, -camy*cameraRange, -camz*cameraRange);
    Vec3 dir_eun(camx, camy, camz);


    unsigned int nHits = hookedObj->CalculateRandomHits(start_eun, dir_eun, cameraRange, 0.01f, 8);


    tcGameObject testObj;
    testObj.mcKin = hookedObj->mcKin;
    testObj.mcKin.mfAlt_m += start_eun.y;
    testObj.mcKin.mfLat_rad += start_eun.z * C_MTORAD;
    testObj.mcKin.mfLon_rad += start_eun.x * C_MTORAD / cosf(testObj.mcKin.mfLat_rad);
    testObj.mcKin.mfHeading_rad = cameraAz + C_PI;
    testObj.mcKin.mfClimbAngle_rad = -cameraEl;
    testObj.mcKin.mfPitch_rad = -cameraEl;
    testObj.mcKin.mfRoll_rad = 0;
    testObj.mcKin.mfSpeed_kts = 20000;


    Vec3 pos;
    float distance_m;
    bool collides = hookedObj->CalculateCollisionPointArb(start_eun, dir_eun, pos, distance_m);

    Vec3 pos2;
    float dt_s;
    float dist_m;
    bool collides2 = hookedObj->CalculateCollisionPoint(&testObj, pos2, dt_s, dist_m);

    if (collides)
    {
        wxString s;
        s.Printf("RUF: %.1f %.1f %.1f", pos.x, pos.y, pos.z);
        infoConsole->Print(s.c_str());

        hookedObj->model->AddExplosion(pos);
    }
    else
    {
        infoConsole->Print("No collision");
    }
    
}



/**
* Prints computed cross-section of hooked object from current camera angle
*/
void tcGame::TestCrossSection()
{
    if (meGameMode == GM_START) return; // ignore if game has not started

    infoConsole->Print("Testing cross-section");


    float cameraAz = viewer->GetCameraAz();
    float cameraEl = viewer->GetCameraEl();
    float cameraRange = viewer->GetCameraRange();

    float camx = -cosf(cameraEl)*sinf(cameraAz); // east
    float camz = -cosf(cameraEl)*cosf(cameraAz); // north
    float camy = -sinf(cameraEl); // up


    long hookID = tacticalMap->GetHookID();

    tcGameObject* hookedObj = simState->GetObject(hookID);
    if (hookedObj == 0) return;

    Vec3 dir_eun(camx, camy, camz);

    unsigned int startCount = tcTime::Get()->GetUpdated30HzCount();
   
    float area_m2 = 0;
    for (size_t k=0; k<10; k++)
    {
        area_m2 = hookedObj->CalculateCrossSectionDir(dir_eun);
    }

    unsigned int duration = tcTime::Get()->GetUpdated30HzCount() - startCount;

    wxString s;
    s.Printf("Area: %.1f m2 (%d tics)", area_m2, duration);
    infoConsole->Print(s.c_str());
    
}

/**
* Check that each hooked id still exists in simulation, otherwise removed from hooked list
*/
void tcGame::ValidateHooked()
{
    unsigned char playerAlliance = tcUserInfo::Get()->GetOwnAlliance();
    std::vector<long> validHooks;

    for (size_t n=0; n<hookedUnits.size(); n++)
    {
        long id = hookedUnits[n];
        if (simState->GetObject(id) != 0)
        {
            validHooks.push_back(id);
        }
        else if (simState->IsMultiplayerClient())
        {
            if (tcSensorMapTrack* track = simState->mcSensorMap.GetSensorMapTrack(id, playerAlliance))
            {
                validHooks.push_back(id);
            }
        }
    }

    if (validHooks.size() < hookedUnits.size())
    {
        NewGroupHook(validHooks);
    }
}

/**
* The tcGame object constructor.
*
*/
tcGame::tcGame(const wxPoint& pos, const wxSize& size, long frameStyle_) 
  :
    wxFrame((wxFrame *)0, -1, "gcblue", pos, size, frameStyle_), //wxNO_FULL_REPAINT_ON_RESIZE), //  | wxNO_FULL_REPAINT_ON_RESIZE | wxCLIP_CHILDREN
    framePos(pos.x, pos.y), frameSize(size),
    frameStyle(frameStyle_),
    gameDateTime(2000,4,10,5,0,0),
    viewer(0),
    infoConsole(0),
    briefingConsoleLeft(0),
    briefingConsoleBottom(0),
    tacticalMap(0),
	worldMap(0),
	hookInfo(0),
	objectControl(0),
	oobView(0),
	popupControl(0),
	director(0),
    networkView(0),
    messageCenter(0),
    scenarioSelectView(0),
    lastGame3DSize(MODE3D_SMALL),
    enableClientSync(true),
    dbInfoPopupKey(-1),
    outcomeDialogKey(-1),
    drawReported(false),
    currentWindowSize(size),
    updatedWindowSize(size),
	progressDialog(0)
{

	progressDialog = new wxProgressDialog("Starting GCB2", "", 100, NULL, wxPD_SMOOTH);
	progressDialog->SetSize(300, 115);

    wxSize clientSize = GetClientSize();
    mnWidth = clientSize.GetWidth();
    mnHeight = clientSize.GetHeight();

    SetBackgroundColour(*wxBLACK);
    Show(FALSE);

    SetMinSize(wxSize(1024, 768));

	simState = tcSimState::Get();
	database = tcDatabase::Get();
    commandQueue = tcCommandQueue::Get();
    
#ifdef _DEBUG
    database->LogSqlColumns("column_log.csv");
#endif

	//int attribList[15];
	//attribList[0] = WX_GL_RGBA;
	//attribList[1] = 1;
	//attribList[2] = WX_GL_DEPTH_SIZE;
	//attribList[3] = 16;
	//attribList[4] = WX_GL_MIN_ALPHA;
	//attribList[5] = 8;
	//attribList[6] = WX_GL_STENCIL_SIZE;
	//attribList[7] = 8;
	//attribList[8] = WX_GL_DOUBLEBUFFER;
	//attribList[9] = 1;
	//attribList[10] = 0;


   // osg::Timer_t tick1 = osg::Timer::instance()->tick();

	progressDialog->Update(10, "Initializing graphics engine");
    tvEngine = tcTVEngine::Get();
    HWND hwnd = reinterpret_cast<HWND>(GetHandle());

    bool isWindowed = (frameStyle != wxNO_FULL_REPAINT_ON_RESIZE);
    tvEngine->InitTV3D(hwnd, isWindowed);

    //osg::Timer_t tick2 = osg::Timer::instance()->tick();

	progressDialog->Update(15, "Initializing Python interface");
    pythonInterface = tcSimPythonInterface::Get();
	goalTracker = tcGoalTracker::Get();

	userInfo = tcUserInfo::Get();
    tcUserInfo::AttachAllianceInfo();
	tcControllableObject::AttachUserInfo();
    tcControllableObject::AttachAllianceInfo();
    tcControllableObject::AttachDatabase();

	progressDialog->Update(15, "Initializing map data");
	mapData = tcMapData::Get();


	mbQuit = false;
	endGame = false;
	mbPaused = false;
	mbScenarioEdit = false;
	accelerateTime = 0;
	meScreenMode = TACTICAL;
    lastMode = NONE;

	mb3DActive = true;
	size3D = MODE3D_SMALL;
	meEditControlState = ECS_NONE;
	mbSwitchToPlay = false;
	gameTime = 0;
	directorTime = 0;
	nLastCount = 0;
	multiplayerMode = 0; // single-player default

	mnBriefingWidth = 300;
	mnLeftMargin = 200;
	mnBottomMargin = 200;

	enableGraphicsEngine = true;
	enableTacticalMap = true;
	togglePopup = false;

	std::cout << "Game constructor success" << std::endl;

	// popup warning if game is run lower than 1024 x 768
	if (mnWidth < 1024)
	{
		wxMessageBox("Graphics layout will not display properly at resolutions lower than 1024 x 768", 
			"GCB screen resolution warning", wxICON_WARNING);
	}

    unsigned short majorVersion = 0;
    unsigned short minorVersion = 0;
    unsigned short buildNumber = 0;
    unsigned short revisionNumber = 0;



#ifdef _DEBUG
    GetAppVersion(L"BlueIId.exe", &majorVersion, &minorVersion, &buildNumber, &revisionNumber);
    wxString s = wxString::Format("VERSION %d.%d.%03d DEBUG %s", 
        majorVersion, minorVersion, buildNumber, __DATE__);
#else
    GetAppVersion(L"BlueII.exe", &majorVersion, &minorVersion, &buildNumber, &revisionNumber);
    //wxString s = wxString::Format("VERSION %d.%d.%03d  %s EXP %s", 
    //    majorVersion, minorVersion, buildNumber, __DATE__, expirationDate.c_str());
    wxString s = wxString::Format("VERSION %d.%d.%03d  %s", 
        majorVersion, minorVersion, buildNumber, __DATE__);
#endif
    
    versionString = s.c_str();

   /* osg::Timer_t stopTick = osg::Timer::instance()->tick();

    double elapsedTime_ms = osg::Timer::instance()->delta_m(startTick, stopTick);
    double t1_ms = osg::Timer::instance()->delta_m(startTick, tick1);
    double t2_ms = osg::Timer::instance()->delta_m(startTick, tick2);
    fprintf(stdout, "tcGame::tcGame() canvas init: %.3f ms, total: %.3f ms\n", 
        t2_ms - t1_ms, elapsedTime_ms);*/

    RegisterTextCommands();
}

/**
* The tcGame object destructor.
*
*/
tcGame::~tcGame()
{
	messageConsole = 0;

	Finish();
}
