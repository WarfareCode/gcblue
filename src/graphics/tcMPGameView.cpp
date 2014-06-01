/** 
**  @file tcMPGameView.cpp 
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

#include "stdwx.h"

#ifndef WX_PRECOMP
#include "wx/wx.h" 
#endif

#include "tcMPGameView.h"
#include "tcButton.h"
#include "tcEditBox.h"
#include "tcConsoleBox.h"
#include "common/tinyxml.h"
#include "network/tcMultiplayerInterface.h"
#include "wxcommands.h"
#include "tcSimState.h"
#include "common/tcOptions.h"
#include "tcUserInfo.h"


BEGIN_EVENT_TABLE(tcMPGameView, tcXmlWindow)
EVT_COMMAND(2, wxEVT_COMMAND_TEXT_UPDATED, tcMPGameView::SendChatText)
EVT_COMMAND(-1, wxEVT_COMMAND_BUTTON_CLICKED, tcMPGameView::ProcessButtonClick)
END_EVENT_TABLE()

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using network::tcMultiplayerInterface;

void tcMPGameView::Draw() 
{
	UpdateButtonState();

	StartDraw();

	DrawScenarioInfo();

	DrawTeamInfo();

	FinishDraw();
}

void tcMPGameView::DrawScenarioInfo()
{
	float x = 520.0f;
	y = 30.0f;

	tcSimState* simState = tcSimState::Get();

	DrawTextR(simState->GetScenarioName(), x, y, defaultFont.get(), Vec4(1, 1, 0.6f, 1), 16.0f, LEFT_BASE_LINE);

	y += 3.0f;

	float maxWidth = float(mnWidth)-x-10.0f;

	wxSize sz;
	MeasureText(defaultFont.get(), 14.0f, simState->GetScenarioDescription(), sz);

	y += sz.GetHeight();

	DrawTextR(simState->GetScenarioDescription(), x, y, defaultFont.get(), Vec4(1, 1, 0.6f, 1), 14.0f, LEFT_BASE_LINE, maxWidth);

    // if game has started, draw current time
    if (simState->GetTime() > 0)
    {
        tcDateTime dateTime = simState->GetDateTime();

        wxString s;

        int year = dateTime.GetYear();
        int month = dateTime.GetMonth();
        int day = dateTime.GetDay();
        int hoursZulu = dateTime.GetHour();
        int minutes = dateTime.GetMinute();
        int seconds = dateTime.GetSecond();
        
        s.Printf("%4d/%02d/%02d %02d:%02d:%02dZ ", year, month, day, 
            hoursZulu, minutes, seconds);
    
        // measure the scenario name size so we can put text to the right of it
        wxSize scenNameSize;
	    MeasureText(defaultFont.get(), 16.0f, simState->GetScenarioName(), scenNameSize);

        DrawTextR(s.c_str(), x + float(scenNameSize.GetWidth()) + 20.0f, 29.0f, 
            defaultFont.get(), Vec4(1, 1, 1, 1), 14.0f, LEFT_BASE_LINE);
    }


	//mpSimState->msScenarioInfo.mzName
	//	    infostring += mpSimState->msScenarioInfo.mzDescription;
}

void tcMPGameView::DrawTeamInfo() 
{
	tcSimState* simState = tcSimState::Get();

	float xteam = 520.0f;
	float xplayer = 540.0f;
	
	y = std::max(y + 25.0f, 120.0f);

	for (size_t k=0; k<teamList.size(); k++)
	{
		DrawTextR(teamList[k].name.c_str(), xteam, y, defaultFont.get(), Vec4(1, 1, 1, 1), 16.0f, LEFT_BASE_LINE);
		tcRect r = GetLastTextBoundingBox();

		DrawLineR(xteam, y, xteam+150.0f, y, Vec4(1, 1, 1, 1));

		// update team join button position
		wxASSERT(teamJoinButtons.size() > k);
		wxASSERT(teamJoinButtons[k] != 0);

		if (simState->IsMultiplayerClient())
		{
			teamJoinButtons[k]->SetPosition(wxPoint(xteam + r.GetRight() + 5.0f, y - r.Height() + 2.0f));
		}
		else
		{
			teamJoinButtons[k]->SetPosition(wxPoint(5000.0f, -5000.0f));
		}

		y += 18.0f;

		// Draw players
		for (size_t n=0; n<teamList[k].playerList.size(); n++)
		{
			const std::string& playerName = teamList[k].playerList[n].name;

			DrawTextR(playerName.c_str(), xplayer, y, defaultFont.get(), Vec4(1, 1, 1, 1), 12.0f, LEFT_BASE_LINE);
			tcRect r = GetLastTextBoundingBox();

			float xtemp = xplayer + r.GetRight() + 5.0f;
			// draw commander flag if commander
			if (teamList[k].playerList[n].isCommander)
			{
				DrawImageR(commanderFlag.get(), xtemp, y - r.GetTop() + 0.0f, 
					15.0f, 15.0f, ALIGN_BOTTOM_LEFT);

				xtemp += 20.0f;
			}

			if (teamList[k].playerList[n].isReady)
			{
				DrawImageR(readySymbol.get(), xtemp, y - r.GetTop() + 0.0f, 
					15.0f, 15.0f, ALIGN_BOTTOM_LEFT);
			}



			y += 18.0f;
		}

		y += 20.0f;
	}
}


unsigned int tcMPGameView::GetTeamSpeed() const
{
    return teamGameSpeed;
}

unsigned int tcMPGameView::GetFastestSpeed() const
{
    return fastestGameSpeed;
}


bool tcMPGameView::IsEveryoneReady()
{
	UpdateReadyState();

	return allReady;
}


void tcMPGameView::OnLButtonDown(wxMouseEvent& event)
{
}


void tcMPGameView::ProcessButtonClick(wxCommandEvent& event)
{
	long nCommand = event.GetExtraLong();

	bool isMultiplayerClient = tcSimState::Get()->IsMultiplayerClient();

	if (!isMultiplayerClient) return;

    tcMultiplayerInterface* multiplayerInterface = tcMultiplayerInterface::Get();

	// check for and process join team command
	if ((nCommand >= 100) && (nCommand <= 116))
	{
		wxString commandText = wxString::Format("//alliance %d", nCommand-100);

		multiplayerInterface->BroadcastChatText(commandText.ToStdString());
	}
	else if ((nCommand >= 51) && (nCommand <= 54)) // stand down, ready, etc buttons
	{
		wxString commandText;

		switch (nCommand)
		{
		case 51: // stand down
			commandText = "//ready 0";
			multiplayerInterface->BroadcastChatText(commandText.ToStdString());
			break;
		case 52: // ready
			commandText = "//ready 1";
			multiplayerInterface->BroadcastChatText(commandText.ToStdString());
			break;
		case 53: // start game
			commandText = "//startgame";
			multiplayerInterface->BroadcastChatText(commandText.ToStdString());
			break;
		case 54: // join game
			{
			// post start game event
			wxEvtHandler* evtHandler = tcMultiplayerInterface::Get()->GetEvtHandler();
			wxCommandEvent command(wxEVT_COMMAND_BUTTON_CLICKED, ID_STARTGAME);    
			evtHandler->AddPendingEvent(command);
			}
			break;
		}
	}
}


/**
* Send chat text to all connections
*/
void tcMPGameView::SendChatText(wxCommandEvent& event)
{
    tcMultiplayerInterface* multiplayerInterface = tcMultiplayerInterface::Get();

    bool isServer = multiplayerInterface->IsServer();
    std::string chatText = event.GetString().c_str();

    if (isServer && (multiplayerInterface->IsCommand(chatText)))
    {
        chatBox->Print(chatText.c_str());
        multiplayerInterface->ProcessCommandServer(chatText);
        return;
    }

    /* prepend name tag if server, this is done for clients by server, server has
    ** to do tagging itself */
    if (isServer)
    {
        chatText = std::string("<") + multiplayerInterface->GetName() + 
            std::string("> ") + chatText;
    }

	tcMultiplayerInterface::Get()->BroadcastChatText(chatText);

}


void tcMPGameView::SetTeamList(const std::vector<TeamInfo>& tl)
{
	teamList = tl;

	// add buttons to teamJoinButtons if teamList size greater than teamJoinButtons size
	for (size_t k=teamJoinButtons.size(); k<teamList.size(); k++)
	{
		tcButton* button = new tcButton(this, wxPoint(0, 0), wxSize(30, 15), "TJBUTTON");
		teamJoinButtons.push_back(button);
	}

	// set mouse over caption based on team name
	for (size_t k=0; k<teamList.size(); k++)
	{
		teamJoinButtons[k]->SetCaption("JOIN");
		teamJoinButtons[k]->SetMouseOverCaption("Join this team");
		teamJoinButtons[k]->SetFontSize(10.0f);
		teamJoinButtons[k]->SetMouseOverCaptionPosition(wxPoint(75, 10));
		teamJoinButtons[k]->SetBackgroundAlpha(0.6f);
		teamJoinButtons[k]->SetCommand(100 + teamList[k].alliance);

		teamJoinButtons[k]->SetActive(true);
	}

	// deactivate any excess buttons
	for (size_t k=teamList.size(); k<teamJoinButtons.size(); k++)
	{
		teamJoinButtons[k]->SetActive(false);
	}

	// If server then deactivate all buttons
	if (tcSimState::Get()->IsMultiplayerServer())
	{
		for (size_t k=0; k<teamJoinButtons.size(); k++)
		{
			teamJoinButtons[k]->SetActive(false);
		}
	}

    UpdateGameSpeedRequests();

}

/**
* Update button state for standDown, ready, start, join
*/
void tcMPGameView::UpdateButtonState()
{
	tcSimState* simState = tcSimState::Get();

	// default all buttons to off and non-interactive
	standDown->SetOn(false);
	standDown->SetInteractive(false);
	ready->SetOn(false);
	ready->SetInteractive(false);
	startGame->SetOn(false);
	startGame->SetInteractive(false);
	joinGame->SetOn(false);
	joinGame->SetInteractive(false);

	if (!simState->IsMultiplayerActive() || !simState->IsScenarioLoaded()) return;

	bool isServer = simState->IsMultiplayerServer();
    bool gameStarted = simState->IsMultiplayerGameStarted();

	if (gameStarted)
	{
		startGame->SetOn(true);
        startGame->SetCaption("GAME STARTED");
		joinGame->SetInteractive(true);
		return;
	}
    else
    {
        startGame->SetCaption("START GAME");
    }

	if (isServer)
	{
		startGame->SetInteractive(true);
		return;
	}

	UpdateReadyState();

	if (!userReady)
	{
		standDown->SetOn(true);
		ready->SetInteractive(true);
	}
	else
	{
		ready->SetOn(true);
		standDown->SetInteractive(true);
	}
	
	if (userReady && allReady)
	{
		startGame->SetInteractive(true);
	}

	
}


void tcMPGameView::UpdateGameSpeedRequests()
{
    wxString userName = tcUserInfo::Get()->GetUsernameWithRank().c_str();

    std::vector<unsigned> teamSpeeds;
    size_t myTeam = 99;

	for (size_t k=0; k<teamList.size(); k++)
	{
        teamSpeeds.push_back(0);

		for (size_t n=0; n<teamList[k].playerList.size(); n++)
		{
            if (teamList[k].playerList[n].isCommander)
            {
                teamSpeeds[k] = teamList[k].playerList[n].gameSpeed;
            }

            if (userName == teamList[k].playerList[n].name.c_str())
			{
				myTeam = k;
			}
		}
	}

    if (myTeam >= teamSpeeds.size())
    {
        teamGameSpeed = 0;
        fastestGameSpeed = 0;
        return;
    }

    teamGameSpeed = teamSpeeds[myTeam];
    fastestGameSpeed = 0;
    for (size_t k=0; k<teamSpeeds.size(); k++)
	{
        fastestGameSpeed = std::max(fastestGameSpeed, teamSpeeds[k]);
    }
}


void tcMPGameView::UpdateReadyState()
{
	wxString userName = tcUserInfo::Get()->GetUsername().c_str();

	allReady = true;
	userReady = false;

	for (size_t k=0; k<teamList.size(); k++)
	{
		for (size_t n=0; n<teamList[k].playerList.size(); n++)
		{
			allReady = allReady && teamList[k].playerList[n].isReady;

			wxString playerName = teamList[k].playerList[n].name.c_str();
			playerName = playerName.AfterFirst(' ');
			if (userName == playerName)
			{
				userReady = teamList[k].playerList[n].isReady;
			}
		}
	}
}



/**
* @param surfaceHost tcWindow to share surface of
*/
tcMPGameView::tcMPGameView(wxWindow *parent, 
                             const wxPoint& pos, const wxSize& size, const wxString& name, tc3DWindow2* host) 
                             : tcXmlWindow(parent, pos, size, "xml/mpgame_view.xml", name, host),
							 allReady(false),
							 userReady(false)
{

    //LoadBackgroundImage("background.jpg");

    if (config)
    {
//        AddXMLControls();
    }
    else
    {
        fprintf(stderr, "tcMPGameView::tcMPGameView - NULL xml config node\n");
        return;
    }

    TiXmlNode* root = config->FirstChild("Window");
    if (!root)
    {
        fprintf(stderr, "tcMPGameView::tcMPGameView - Missing top level <Window> tag\n");
        return;
    }


    // add chat text console
    TiXmlNode* current = root->FirstChild("ChatBox");
    chatBox = new tcConsoleBox(this, current);
    //chatBox->SetBackgroundColor(Vec4(0, 0, 0, 1));
    //chatBox->SetBackgroundDraw(true);
	chatBox->SetActive(true);


    tcMultiplayerInterface::Get()->AddChatSubscriber(chatBox);

    // add chat text edit box
    current = root->FirstChild("ChatEntry");
    chatEntry = new tcEditBox(this, current);
	chatEntry->SetActive(true);
    chatEntry->SetCommand(2);
    chatEntry->SetClearOnReturn(true);
    chatEntry->SetBuffer("");


	// force chat and edit box to be within main window
	wxPoint cePos = chatEntry->GetPosition();
	wxSize ceSize = chatEntry->GetSize();

	int yStray = 10 + cePos.y + ceSize.GetHeight() - size.GetHeight();

	if (yStray > 0)
	{
		wxPoint chatPos = chatBox->GetPosition();
		chatPos.y -= yStray;
		chatBox->SetPosition(chatPos);

		wxPoint entryPos = chatEntry->GetPosition();
		entryPos.y -= yStray;
		chatEntry->SetPosition(entryPos);
	}

	commanderFlag = tc3DWindow2::LoadTexture("commander_icon.jpg");
	readySymbol = tc3DWindow2::LoadTexture("check_box.png");

	// add stand-down, ready, start game buttons
	int yButton = chatEntry->GetPosition().y + chatEntry->GetSize().GetHeight() + 20;
	int xButton = 30;
	int wButton = 113;
	int hButton = 30;

	standDown = new tcButton(this, wxPoint(xButton, yButton), wxSize(wButton, hButton));
	standDown->SetFontSize(12.0f);
	standDown->SetBackgroundAlpha(0.5f);
	standDown->SetCaption("STAND DOWN");
	standDown->SetCommand(51);
	standDown->SetOnColor(Vec4(0.4f, 1.0f, 0.4f, 1.0f));
    standDown->SetOverColor(Vec4(0.6f, 0.8f, 1.0f, 1.0f));
	xButton += wButton + 5;

	ready = new tcButton(this, wxPoint(xButton, yButton), wxSize(wButton, hButton));
	ready->SetFontSize(12.0f);
	ready->SetBackgroundAlpha(0.5f);
	ready->SetCaption("READY");
	ready->SetCommand(52);
	ready->SetOnColor(Vec4(0.4f, 1.0f, 0.4f, 1.0f));
    ready->SetOverColor(Vec4(0.6f, 0.8f, 1.0f, 1.0f));
	xButton += wButton + 5;

	startGame = new tcButton(this, wxPoint(xButton, yButton), wxSize(wButton, hButton));
	startGame->SetFontSize(12.0f);
	startGame->SetBackgroundAlpha(0.5f);
	startGame->SetCaption("START GAME");
	startGame->SetCommand(53);
	startGame->SetOnColor(Vec4(0.4f, 1.0f, 0.4f, 1.0f));
    startGame->SetOverColor(Vec4(0.6f, 0.8f, 1.0f, 1.0f));
	xButton += wButton + 5;

	joinGame = new tcButton(this, wxPoint(xButton, yButton), wxSize(wButton, hButton));
	joinGame->SetFontSize(12.0f);
	joinGame->SetBackgroundAlpha(0.5f);
	joinGame->SetCaption("JOIN GAME");
	joinGame->SetCommand(54);
	joinGame->SetOnColor(Vec4(0.4f, 1.0f, 0.4f, 1.0f));
    joinGame->SetOverColor(Vec4(0.6f, 0.8f, 1.0f, 1.0f));
	xButton += wButton + 5;
    

	//TeamInfo ti;
	//PlayerInfo pi;
	//pi.isCommander = false;

	//ti.alliance = 0;
	//ti.name = "Observers";
	//
	//pi.name = "Ob1player";
	//ti.playerList.push_back(pi);
	//pi.name = "AnotherPlayer";
	//pi.isCommander = true;
	//ti.playerList.push_back(pi);

	//teamList.push_back(ti);

	//ti.alliance = 1;
	//ti.name = "EvilAlliance";
	//teamList.push_back(ti);

	//ti.alliance = 2;
	//ti.name = "TheGoodOnes";
	//teamList.push_back(ti);

	//SetTeamList(teamList);

}

tcMPGameView::~tcMPGameView() 
{
}


