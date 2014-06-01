/** 
**  @file tcChatBox.cpp 
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

#include "tcChatBox.h"
#include "tcButton.h"
#include "tcEditBox.h"
#include "tcConsoleBox.h"
#include "common/tinyxml.h"
#include "network/tcMultiplayerInterface.h"
#include "wxcommands.h"
#include "common/tcOptions.h"



BEGIN_EVENT_TABLE(tcChatBox, tcXmlWindow)
EVT_COMMAND(1, wxEVT_COMMAND_TEXT_UPDATED, tcChatBox::SendChatText)
EVT_COMMAND(86, wxEVT_COMMAND_BUTTON_CLICKED, tcChatBox::OnCloseCommand)
EVT_COMMAND(10, wxEVT_COMMAND_BUTTON_CLICKED, tcChatBox::OnChatModeAll)
EVT_COMMAND(20, wxEVT_COMMAND_BUTTON_CLICKED, tcChatBox::OnChatModeTeam)
END_EVENT_TABLE()

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using network::tcMultiplayerInterface;

void tcChatBox::Draw() 
{
    StartDraw();

	if (!IsBackgroundEnabled())
	{
		DrawRectangle(0, 0, float(mnWidth), float(mnHeight), 
			Vec4(0, 0, 0, 0.3f), FILL_ON);
	}

	FinishDraw();

}



void tcChatBox::OnChar(wxKeyEvent& event)
{
}

void tcChatBox::OnChatModeAll(wxCommandEvent& event)
{
    chatModeTeam = false;
    UpdateChatModeButtons();
}

void tcChatBox::OnChatModeTeam(wxCommandEvent& event)
{
    chatModeTeam = true;
    UpdateChatModeButtons();
}

/**
* Close and destroy window at next safe opportunity
*/
void tcChatBox::OnCloseCommand(wxCommandEvent& event)
{
    SetActive(false);
}

void tcChatBox::OnKeyDown(wxKeyEvent& event)
{
}


void tcChatBox::OnLButtonDown(wxMouseEvent& event)
{
    tcXmlWindow::OnLButtonDown(event);
}

void tcChatBox::OnRButtonDown(wxMouseEvent& event)
{
    // event stops here
}

/**
* Send chat text to all connections
*/
void tcChatBox::SendChatText(wxCommandEvent& event)
{
    tcMultiplayerInterface* multiplayerInterface = tcMultiplayerInterface::Get();

    std::string chatText = event.GetString().c_str();

    bool isServer = multiplayerInterface->IsServer();
    bool isCommand = multiplayerInterface->IsCommand(chatText);

    if (!isServer && !isCommand && chatModeTeam)
    {
        chatText = std::string("//team ") + chatText;
    }
    

    if (isServer && isCommand)
    {
        chatHistory->Print(chatText.c_str());
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

    // if server, print chat text locally since no echo comes back
    if (isServer)
    {
        chatHistory->Print(chatText.c_str());
    }

}

void tcChatBox::UpdateChatModeButtons()
{
    tcButton* all = GetButtonWithCommand(10);
    tcButton* team = GetButtonWithCommand(20);

    if ((all == 0) || (team == 0))
    {
        wxASSERT(false);
        fprintf(stderr, "tcChatBox::UpdateChatModeButtons - buttons not found\n");
        return;
    }

    all->SetOn(!chatModeTeam);
    team->SetOn(chatModeTeam);
}


/**
* @param surfaceHost tcWindow to share surface of
*/
tcChatBox::tcChatBox(wxWindow *parent,
                             const wxPoint& pos, const wxSize& size, 
                             const wxString& name, const wxString& configFile) 
                             : tcXmlWindow(parent, pos, size, configFile, name),
                             chatModeTeam(false)
{

    //LoadBackgroundImage("background.jpg");

    if (config)
    {
//        AddXMLControls();
    }
    else
    {
        std::cerr << "tcChatBox::tcChatBox - NULL xml config node\n";
        return;
    }

    TiXmlNode* root = config->FirstChild("Window");
    if (!root)
    {
        std::cerr << "tcChatBox::tcChatBox - Missing top level <Window> tag\n";
        return;
    }

    // add chat text console
    TiXmlNode* current = root->FirstChild("ChatBox");
    chatHistory = new tcConsoleBox(this, current);
	chatHistory->SetWrap(65);
    tcMultiplayerInterface::Get()->AddChatSubscriber(chatHistory);

    // add chat text edit box
    current = root->FirstChild("ChatEntry");
    chatEntry = new tcEditBox(this, current);
    chatEntry->SetCommand(1);
    chatEntry->SetClearOnReturn(true);
    chatEntry->SetBuffer("Enter chat text here");

    UpdateChatModeButtons();
}

tcChatBox::~tcChatBox() 
{
    tcMultiplayerInterface::Get()->RemoveChatSubscriber(chatHistory);
}


