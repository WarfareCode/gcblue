/** 
**  @file tcGameOutcomePopup.cpp 
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

#include "tcGameOutcomePopup.h"

#include <stdio.h>
#include <iostream>
#include "tcTime.h"
#include "tcSimState.h"
#include "tcButton.h"
#include "wxcommands.h"


BEGIN_EVENT_TABLE(tcGameOutcomePopup, tc3DWindow2)
EVT_COMMAND(86, wxEVT_COMMAND_BUTTON_CLICKED, tcGameOutcomePopup::ExitGame)
EVT_COMMAND(123, wxEVT_COMMAND_BUTTON_CLICKED, tcGameOutcomePopup::ContinueGame)
END_EVENT_TABLE()


#ifdef _DEBUG
#define new DEBUG_NEW
#endif 

tc3DWindow2* tcGameOutcomePopup::parent = 0;

/**
*
*/
void tcGameOutcomePopup::SetParent(tc3DWindow2* par)
{
    parent = par;
}


/**
* Clears the text buffer
*/
void tcGameOutcomePopup::Clear()
{
	messageText = "";
}

/**
*
*/
void tcGameOutcomePopup::Draw()
{
    //unsigned currentCount = tcTime::Get()->Get30HzCount();

    //unsigned age = currentCount - birthCount;
    
    if (CloseRequested())
    {
        DestroyWindow();
        return;
    }

    Update();

    StartDraw();

    Vec4 color(1, 1, 1, 1);
    Vec4 titleColor(1, 1, 0.4f, 1);

    float x = 0.5f * float(mnWidth);
    float y = 0.5f * float(mnHeight);


    DrawRectangleR(0, 0, float(mnWidth), float(mnHeight), 
        Vec4(0, 0, 0, 0.5f), FILL_ON);

    DrawTextR("GAME OVER", x, 15.0, defaultFont.get(),
        titleColor, fontSize + 6.0f, CENTER_CENTER, float(mnWidth)-10.0f);

    DrawTextR(messageText.c_str(), 5.0f, y, defaultFont.get(),
        color, fontSize + 2.0f, LEFT_CENTER, float(mnWidth)-10.0f);


	FinishDraw();

}


void tcGameOutcomePopup::ExitGame(wxCommandEvent& event)
{
    wxCommandEvent command(wxEVT_COMMAND_BUTTON_CLICKED, ID_ENDGAME);    
    AddPendingEvent(command);
}

/**
* Close dialog and send message to un-pause game
*/
void tcGameOutcomePopup::ContinueGame(wxCommandEvent& event)
{
    wxCommandEvent command(wxEVT_COMMAND_BUTTON_CLICKED, ID_SETPAUSE);
    command.SetExtraLong(0); // 0 is un-pause, 1 to pause
    AddPendingEvent(command);

    DestroyWindow();
}


void tcGameOutcomePopup::OnLButtonDown(wxMouseEvent& event)
{
    //DestroyWindow(); // old way, before ContinueGame button was added
}

void tcGameOutcomePopup::SetMessageText(const std::string& text)
{
    messageText = text;
}

void tcGameOutcomePopup::Update()
{

}



/**
*
*/
tcGameOutcomePopup::tcGameOutcomePopup(const wxPoint& pos, const wxSize& size)
            : tc3DWindow2(parent, pos, size, "GameOutcome", parent)
{
    SetBaseRenderBin(parent->GetBaseRenderBin() + 10);
    Raise();
    birthCount = tcTime::Get()->Get30HzCount();

    SetBorderDraw(true);

    int w = 70;
    int h = 15;
    int x = (size.GetWidth() - w) / 2;
    int y = size.GetHeight() - 25;
    tcButton* exitButton = new tcButton(this, wxPoint(x - w, y), wxSize(w, h), "XBUTTON");
    exitButton->SetCaption("EXIT GAME");
    exitButton->SetFontSize(fontSize + 2.0f);
    exitButton->SetOffColor(Vec4(0.2f, 0.2f, 0.2f, 0.5f));
    exitButton->SetOverColor(Vec4(0.25f, 0.25f, 0.25f, 0.5f));
    exitButton->SetCommand(86);

    tcButton* continueButton = new tcButton(this, wxPoint(x + w, y), wxSize(w, h), "XBUTTON");
    continueButton->SetCaption("PLAY ON");
    continueButton->SetFontSize(fontSize + 2.0f);
    continueButton->SetOffColor(Vec4(0.2f, 0.2f, 0.2f, 0.5f));
    continueButton->SetOverColor(Vec4(0.25f, 0.25f, 0.25f, 0.5f));
    continueButton->SetCommand(123);

}

tcGameOutcomePopup::~tcGameOutcomePopup() 
{

}

