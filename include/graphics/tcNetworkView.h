/** 
**  @file tcNetworkView.h 
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

#ifndef _NETWORKVIEW_H_
#define _NETWORKVIEW_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "wx/wx.h" 

#include "tcXmlWindow.h"
#include "tcTabbedWindow.h"

class tcEditBox;
class tcConsoleBox;
class tcMPGameView;

/**
* User interface window for multiplayer and network
* setup and test.
* Called a "view" even though this class has data and more
* included to be consistent with other view classes.
*/
class tcNetworkView : public tcXmlWindow, public tcTabbedWindow
{
public:
	enum
	{
		MULTIPLAYER_OFF = 0,
		MULTIPLAYER_CLIENT = 1,
		MULTIPLAYER_SERVER = 2,
		ALLOW_ALL = 0, // allow any client to login, creating account if necessary
		ALLOW_REGISTERED = 1 // only allow clients registered in account database to login
	};
    void Draw();
    void DrawStatusBox();
	int GetNetworkMode() const;
	void JoinGame(wxCommandEvent& event);
    void OnConnect(wxCommandEvent& event); 
    void OnLButtonDown(wxMouseEvent& event);
    void SendChatText(wxCommandEvent& event);
    void SendTest(wxCommandEvent& event);
    void SetChatProtocol(wxCommandEvent& event); 
    void SetIPText(wxCommandEvent& event);
	void SetLoginMode(wxCommandEvent& event);
	void SetLoginMode(int mode);
    void SetNetworkMode(wxCommandEvent& event); 
	void SetNetworkMode(int mode);
    void SetUsername(wxCommandEvent& event);
	void SetPassword(wxCommandEvent& event);

	tcMPGameView* GetMPGameView() const;

    tcNetworkView(wxWindow* parent, 
        const wxPoint& pos, const wxSize& size, 
        const wxString& name = "NetworkView");

    tcNetworkView(tc3DWindow2* parent, 
        const wxPoint& pos, const wxSize& size, 
        const wxString& name);

    virtual ~tcNetworkView();
private:
    std::string ipText;
    int networkMode;
    tcEditBox* ipEdit;
	tcEditBox* usernameEdit;
	tcEditBox* passwordEdit;
    tcConsoleBox* chatBox;
    tcEditBox* chatEntry;

	tcMPGameView* gameLobby;

    wxRect statusBoxBounds;
	bool autoSwitchToLobby; ///< when true, switch to lobby tab when connected

	void InitializeLobby();

    DECLARE_EVENT_TABLE()
};

#endif