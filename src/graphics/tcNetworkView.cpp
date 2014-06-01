/** 
**  @file tcNetworkView.cpp 
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

#include "tcNetworkView.h"
#include "tcButton.h"
#include "tcEditBox.h"
#include "tcConsoleBox.h"
#include "common/tinyxml.h"
#include "network/tcMultiplayerInterface.h"
#include "wxcommands.h"
#include "tcSimState.h"
#include "common/tcOptions.h"
#include "tcUserInfo.h"
#include "ai/Blackboard.h"
#include "tcMPGameView.h"


BEGIN_EVENT_TABLE(tcNetworkView, tcXmlWindow)
EVT_COMMAND(ID_MULTIPLAYERMODE, wxEVT_COMMAND_BUTTON_CLICKED , tcNetworkView::SetNetworkMode)
EVT_COMMAND(ID_CONNECT, wxEVT_COMMAND_BUTTON_CLICKED , tcNetworkView::OnConnect)
EVT_COMMAND(ID_JOINGAME, wxEVT_COMMAND_BUTTON_CLICKED , tcNetworkView::JoinGame)
EVT_COMMAND(ID_CHATPROTOCOL, wxEVT_COMMAND_BUTTON_CLICKED , tcNetworkView::SetChatProtocol)
EVT_COMMAND(ID_LOGINMODE, wxEVT_COMMAND_BUTTON_CLICKED , tcNetworkView::SetLoginMode)
EVT_COMMAND(1, wxEVT_COMMAND_TEXT_UPDATED, tcNetworkView::SetIPText)
EVT_COMMAND(2, wxEVT_COMMAND_TEXT_UPDATED, tcNetworkView::SendChatText)
EVT_COMMAND(3, wxEVT_COMMAND_TEXT_UPDATED, tcNetworkView::SetUsername)
EVT_COMMAND(4, wxEVT_COMMAND_TEXT_UPDATED, tcNetworkView::SetPassword)
END_EVENT_TABLE()

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using network::tcMultiplayerInterface;

void tcNetworkView::Draw() 
{
	std::string activeTab(GetTab());

    tcMultiplayerInterface* mp = tcMultiplayerInterface::Get();

	if (autoSwitchToLobby)
	{
		if ((mp->GetNumConnections() > 0) && (!mp->IsConnecting()))
		{
			autoSwitchToLobby = false;

			// post as event so that tab header stays in sync
			wxCommandEvent command(wxEVT_COMMAND_BUTTON_CLICKED, ID_TABCLICKED);    
            command.SetEventObject(this);
            command.SetString("Game Lobby");
            AddPendingEvent(command);
		}
	}

    if (activeTab == "Game Lobby")
    {
        if (mp->GetNumConnections() == 0)
        {
            // switch back to network screen if connection lost
            wxCommandEvent command(wxEVT_COMMAND_BUTTON_CLICKED, ID_TABCLICKED);    
            command.SetEventObject(this);
            command.SetString("Connection");
            AddPendingEvent(command);
        }

		ipEdit->SetActive(false);
		usernameEdit->SetActive(false);
		passwordEdit->SetActive(false);
		chatBox->SetActive(false);
		chatEntry->SetActive(false);
		SetAllButtonState(false);

        gameLobby->SetActive(true);

        StartDraw();
        FinishDraw();
        return;
    }
    else
    {
		ipEdit->SetActive(true);
		usernameEdit->SetActive(true);
		passwordEdit->SetActive(true);
		chatBox->SetActive(true);
		chatEntry->SetActive(true);
		SetAllButtonState(true);

        gameLobby->SetActive(false);
    }

    StartDraw();

    DrawStatusBox();

	FinishDraw();
}


void tcNetworkView::DrawStatusBox()
{
	Vec4 color(1, 1, 1, 1);

    DrawRectangleR(statusBoxBounds.x, statusBoxBounds.y, 
        statusBoxBounds.width, statusBoxBounds.height, color);

    float x = (float)statusBoxBounds.x + 0.5*(float)statusBoxBounds.width;
    float y = (float)statusBoxBounds.y + 10.0f;

	DrawTextR("Connection Status", x, y, defaultFont.get(), color, 14.0f,
		CENTER_CENTER);

    x = (float)statusBoxBounds.x + 10.0f;

	tcMultiplayerInterface* mp = tcMultiplayerInterface::Get();
	if (!mp->IsConnecting())
	{
		const std::list<int>& connectionList = tcMultiplayerInterface::Get()->GetConnectionList();
		std::list<int>::const_iterator iter = connectionList.begin();
		for ( ; iter != connectionList.end(); ++iter)
		{
			y += 14.0f;
			std::string connectionStatus = mp->GetConnectionStatus(*iter);

			DrawTextR(connectionStatus.c_str(), x, y, defaultFont.get(), color, 14.0f, 
				LEFT_CENTER);
		}
	}
	else
	{
		y += 14.0f;
		std::string connectionStatus = mp->GetConnectionStatus(0);

		DrawTextR(connectionStatus.c_str(), x, y, defaultFont.get(), color, 14.0f, 
			LEFT_CENTER);
	}

	wxString s = wxString::Format("Max update: %d", mp->updateCount);
	DrawTextR(s.c_str(), x, (float)statusBoxBounds.y - 15.0f, defaultFont.get(), color, 12.0f,
		LEFT_CENTER);

}


tcMPGameView* tcNetworkView::GetMPGameView() const
{
	return gameLobby;
}


int tcNetworkView::GetNetworkMode() const
{
	return networkMode;
}


void tcNetworkView::InitializeLobby()
{
	gameLobby = new tcMPGameView(this, wxPoint(0, 0), wxSize(mnWidth, mnHeight), "GameLobby", this);

	AddTab("Connection");
    AddTab("Game Lobby");

    SetTab("Connection");

	SetTabWidth(100.0f);
}


/**
* Only applies in client mode when already connected
*/
void tcNetworkView::JoinGame(wxCommandEvent& event)
{
    if (networkMode == MULTIPLAYER_OFF)
	{
		chatBox->Print("Must be in multiplayer mode to join game");
		return;
	}
	else if (networkMode == MULTIPLAYER_CLIENT)
	{
		if (tcMultiplayerInterface::Get()->GetNumConnections() == 0)
		{
			chatBox->Print("Must connect first to join game");
			return;
		}
	}
	else if (!tcSimState::Get()->IsScenarioLoaded())
	{
		chatBox->Print("Server must load scenario before starting game");
		return;
	}

	// post start game event
	wxEvtHandler* evtHandler = tcMultiplayerInterface::Get()->GetEvtHandler();
	wxCommandEvent command(wxEVT_COMMAND_BUTTON_CLICKED, ID_STARTGAME);    
	evtHandler->AddPendingEvent(command);

}

/**
* Only applies in client mode
*/
void tcNetworkView::OnConnect(wxCommandEvent& event)
{
    if (networkMode != 1) return;

    std::string s(usernameEdit->GetBuffer());
	tcMultiplayerInterface::Get()->SetName(s);

	s = passwordEdit->GetBuffer();
	tcMultiplayerInterface::Get()->SetPassword(s);

    tcMultiplayerInterface::Get()->OpenConnection(ipText.c_str());

	autoSwitchToLobby = true;
}

void tcNetworkView::OnLButtonDown(wxMouseEvent& event)
{
}

/**
* Send chat text to all connections
*/
void tcNetworkView::SendChatText(wxCommandEvent& event)
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

    // if server, print chat text locally since no echo comes back (modified to use chat subscriber function, so commented out)
    //if (isServer)
    //{
    //    chatBox->Print(chatText.c_str());
    //}

}

void tcNetworkView::SetChatProtocol(wxCommandEvent& event)
{
    int protocol = event.GetExtraLong(); // 2.6.3 m_extraLong;


    tcMultiplayerInterface::Get()->SetChatProtocol(protocol == 0);
}

void tcNetworkView::SetIPText(wxCommandEvent& event)
{
    ipText = event.GetString().c_str();
    tcOptions::Get()->SetOptionString("HostAddress", ipText.c_str());
}

void tcNetworkView::SetLoginMode(wxCommandEvent& event)
{
    int mode = event.GetExtraLong(); // m_extraLong;

	SetLoginMode(mode);
}

void tcNetworkView::SetLoginMode(int mode)
{
	if (mode == ALLOW_ALL)
	{
		tcMultiplayerInterface::Get()->SetAcceptAllClients(true);
	}
	else if (mode == ALLOW_REGISTERED)
	{
		tcMultiplayerInterface::Get()->SetAcceptAllClients(false);
	}
	else
	{
		wxASSERT(false); // unrecognized mode
	}
}

void tcNetworkView::SetNetworkMode(wxCommandEvent& event)
{
    int mode = event.GetExtraLong(); // 2.6.3 m_extraLong;

	SetNetworkMode(mode);

    event.Skip(); // send event on to application
}

void tcNetworkView::SetNetworkMode(int mode)
{
    if (networkMode == mode) return;

    if (mode == MULTIPLAYER_OFF)
    {
		// terminate all connections
		tcMultiplayerInterface::Get()->Reset();
        tcSimState::Get()->SetMultiplayerOff();
		ai::Blackboard::SetMultiplayerClientMode(false);
    }
	else if (tcMultiplayerInterface::Get()->GetNumConnections() > 0)
	{
		chatBox->Print("Disconnect before switching multiplayer mode");
		return;
	}
    else if (mode == MULTIPLAYER_CLIENT)
    {
        tcMultiplayerInterface::Get()->MakeClient();
        tcSimState::Get()->SetMultiplayerClient();
		ai::Blackboard::SetMultiplayerClientMode(true);
    }
    else if (mode == MULTIPLAYER_SERVER)
    {
        tcMultiplayerInterface::Get()->MakeServer();
        tcSimState::Get()->SetMultiplayerServer();
		tcUserInfo::Get()->SetScore(10.0e6); // set high score for high server "rank"
		tcUserInfo::Get()->SetUsername("SERVER");

		ai::Blackboard::SetMultiplayerClientMode(false);
    }
	else
	{
		fprintf(stderr, "tcNetworkView::SetNetworkMode, bad mode %d\n", mode);
		return;
	}

    networkMode = mode;
}

void tcNetworkView::SetUsername(wxCommandEvent& event)
{
	std::string s = event.GetString().c_str();

	tcMultiplayerInterface::Get()->SetName(s);
	tcOptions::Get()->SetOptionString("UserName", s.c_str());

	if (networkMode != MULTIPLAYER_SERVER) tcUserInfo::Get()->SetUsername(s); // server not allowed to change name
}

void tcNetworkView::SetPassword(wxCommandEvent& event)
{
	std::string s = event.GetString().c_str();

	tcMultiplayerInterface::Get()->SetPassword(s);
}

void tcNetworkView::SendTest(wxCommandEvent& event)
{
	/* 
    std::string testText = "Test text for UDP";

    unsigned nConnections = tcMultiplayerInterface::Get()->GetNumConnections();

    for (unsigned n=0;n<nConnections;n++)
    {
        int connId = tcMultiplayerInterface::Get()->GetConnectionId(n);
        tcMultiplayerInterface::Get()->SendTestUDP(connId, testText);
    }

    // if server, print chat text locally since no echo comes back
    if (tcMultiplayerInterface::Get()->IsServer())
    {
        std::string localText = std::string("Sent UDP test: ") +
            testText;
        chatBox->Print(localText.c_str());
    }
	*/
}

/**
* @param surfaceHost tcWindow to share surface of
*/
tcNetworkView::tcNetworkView(wxWindow *parent, 
                             const wxPoint& pos, const wxSize& size, const wxString& name) 
                             : tcXmlWindow(parent, pos, size, "xml/network_view.xml", name),
                             networkMode(0)
{

	wxASSERT(false); // shouldn't be used, not updated

    LoadBackgroundImage("background.jpg");

    if (config)
    {
//        AddXMLControls();
    }
    else
    {
        std::cerr << "tcNetworkView::tcNetworkView - NULL xml config node\n";
        return;
    }

    TiXmlNode* root = config->FirstChild("Window");
    if (!root)
    {
        std::cerr << "tcNetworkView::tcNetworkView - Missing top level <Window> tag\n";
        return;
    }

    // add IP edit box
    TiXmlNode* current = root->FirstChild("EditIP");
    ipEdit = new tcEditBox(this, current);
    ipEdit->SetCommand(1);
    ipEdit->SetClearOnReturn(false);

	// add username edit box
    current = root->FirstChild("EditName");
    usernameEdit = new tcEditBox(this, current);
    usernameEdit->SetCommand(3);
    usernameEdit->SetClearOnReturn(false);
    if (!tcOptions::Get()->OptionStringExists("UserName"))
    {
        tcOptions::Get()->SetOptionString("UserName", "Observer");
    }
	const std::string& username = tcOptions::Get()->GetOptionString("UserName");
	usernameEdit->SetBuffer(username.c_str());
	tcMultiplayerInterface::Get()->SetName(username);
	tcUserInfo::Get()->SetUsername(username);


	// add password edit box
    current = root->FirstChild("EditPassword");
    passwordEdit = new tcEditBox(this, current);
    passwordEdit->SetCommand(4);
    passwordEdit->SetClearOnReturn(false);
	passwordEdit->SetBuffer("");
    tcMultiplayerInterface::Get()->SetPassword("");

    if (!tcOptions::Get()->OptionStringExists("HostAddress"))
    {
        tcOptions::Get()->SetOptionString("HostAddress", "192.168.1.2");
    }
    ipEdit->SetBuffer(tcOptions::Get()->GetOptionString("HostAddress"));
    ipText = tcOptions::Get()->GetOptionString("HostAddress");

    

    // read status box parameters
    current = root->FirstChild("StatusBox");

    if (current)
    {
        TiXmlElement* elt = current->ToElement();
        elt->Attribute("X", &statusBoxBounds.x);
        elt->Attribute("Y", &statusBoxBounds.y);
        elt->Attribute("Width", &statusBoxBounds.width);
        elt->Attribute("Height", &statusBoxBounds.height);
    }
    else
    {
        std::cerr << "tcNetworkView::tcNetworkView - no StatusBox xml node\n";
    }

    // add chat text console
    current = root->FirstChild("ChatBox");
    chatBox = new tcConsoleBox(this, current);
	chatBox->SetActive(true);

    tcMultiplayerInterface::Get()->AddChatSubscriber(chatBox);

    // add chat text edit box
    current = root->FirstChild("ChatEntry");
    chatEntry = new tcEditBox(this, current);
	chatEntry->SetActive(true);
    chatEntry->SetCommand(2);
    chatEntry->SetClearOnReturn(true);
    chatEntry->SetBuffer("");

	// set client policy to match tcMultiplayerInterface
	if (tcMultiplayerInterface::Get()->GetAcceptAllClients())
	{
		SetRadioButtonState(ID_LOGINMODE, 0);
	}
	else
	{
		SetRadioButtonState(ID_LOGINMODE, 1);
	}
}


/**
* @param surfaceHost tcWindow to share surface of
*/
tcNetworkView::tcNetworkView(tc3DWindow2* parent, 
                             const wxPoint& pos, const wxSize& size, const wxString& name) 
                             : tcXmlWindow(parent, pos, size, "xml/network_view.xml", name, parent),
                             networkMode(0),
							 gameLobby(0),
							 autoSwitchToLobby(false)
{
    //LoadBackgroundImage("background.jpg");

    if (config)
    {
//        AddXMLControls();
    }
    else
    {
        std::cerr << "tcNetworkView::tcNetworkView - NULL xml config node\n";
        return;
    }

    TiXmlNode* root = config->FirstChild("Window");
    if (!root)
    {
        std::cerr << "tcNetworkView::tcNetworkView - Missing top level <Window> tag\n";
        return;
    }

    // add IP edit box
    TiXmlNode* current = root->FirstChild("EditIP");
    ipEdit = new tcEditBox(this, current);
    ipEdit->SetCommand(1);
    ipEdit->SetClearOnReturn(false);

	// add username edit box
    current = root->FirstChild("EditName");
    usernameEdit = new tcEditBox(this, current);
    usernameEdit->SetCommand(3);
    usernameEdit->SetClearOnReturn(false);
    if (!tcOptions::Get()->OptionStringExists("UserName"))
    {
        tcOptions::Get()->SetOptionString("UserName", "Observer");
    }
	const std::string& username = tcOptions::Get()->GetOptionString("UserName");
	usernameEdit->SetBuffer(username.c_str());
	tcMultiplayerInterface::Get()->SetName(username);
	tcUserInfo::Get()->SetUsername(username);


	// add password edit box
    current = root->FirstChild("EditPassword");
    passwordEdit = new tcEditBox(this, current);
    passwordEdit->SetCommand(4);
    passwordEdit->SetClearOnReturn(false);
	passwordEdit->SetBuffer("");
    tcMultiplayerInterface::Get()->SetPassword("");

    if (!tcOptions::Get()->OptionStringExists("HostAddress"))
    {
        tcOptions::Get()->SetOptionString("HostAddress", "192.168.1.2");
    }
    ipEdit->SetBuffer(tcOptions::Get()->GetOptionString("HostAddress"));
    ipText = tcOptions::Get()->GetOptionString("HostAddress");

    

    // read status box parameters
    current = root->FirstChild("StatusBox");

    if (current)
    {
        TiXmlElement* elt = current->ToElement();
        elt->Attribute("X", &statusBoxBounds.x);
        elt->Attribute("Y", &statusBoxBounds.y);
        elt->Attribute("Width", &statusBoxBounds.width);
        elt->Attribute("Height", &statusBoxBounds.height);
    }
    else
    {
        std::cerr << "tcNetworkView::tcNetworkView - no StatusBox xml node\n";
    }

    // add chat text console
    current = root->FirstChild("ChatBox");
    chatBox = new tcConsoleBox(this, current);
	chatBox->SetActive(true);

    tcMultiplayerInterface::Get()->AddChatSubscriber(chatBox);

    // add chat text edit box
    current = root->FirstChild("ChatEntry");
    chatEntry = new tcEditBox(this, current);
	chatEntry->SetActive(true);
    chatEntry->SetCommand(2);
    chatEntry->SetClearOnReturn(true);
    chatEntry->SetBuffer("");

	// set client policy to match tcMultiplayerInterface
	if (tcMultiplayerInterface::Get()->GetAcceptAllClients())
	{
		SetRadioButtonState(ID_LOGINMODE, 0);
	}
	else
	{
		SetRadioButtonState(ID_LOGINMODE, 1);
	}



	InitializeLobby();
}


tcNetworkView::~tcNetworkView() 
{
}


