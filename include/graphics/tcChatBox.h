/** 
**  @file tcChatBox.h 
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

#ifndef _CHATBOX_H_
#define _CHATBOX_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "wx/wx.h" 

#include "tcXmlWindow.h"


class tcEditBox;
class tcConsoleBox;

/**
* User interface window for multiplayer chat. The ChatBox
* is a small popup window used from within the game.
*/
class tcChatBox : public tcXmlWindow 
{
public:
    void Draw();
    void OnLButtonDown(wxMouseEvent& event);
    void OnRButtonDown(wxMouseEvent& event);
	void OnChar(wxKeyEvent& event);
    void OnCloseCommand(wxCommandEvent& event);
	void OnKeyDown(wxKeyEvent& event);
    void OnChatModeAll(wxCommandEvent& event);
    void OnChatModeTeam(wxCommandEvent& event);
    void SendChatText(wxCommandEvent& event);

    tcChatBox(wxWindow *parent, 
        const wxPoint& pos, const wxSize& size, 
        const wxString& name = "ChatBox",
        const wxString& configFile = "xml/chat_box.xml");
    virtual ~tcChatBox();
private:
    tcConsoleBox *chatHistory;
    tcEditBox *chatEntry;
    bool chatModeTeam;

    void UpdateChatModeButtons();

    DECLARE_EVENT_TABLE()
};

#endif
