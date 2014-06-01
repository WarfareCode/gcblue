/** 
**  @file tcPopupMessage.cpp 
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

#include "tcPopupMessage.h"

#include <stdio.h>
#include <iostream>
#include "tcTime.h"
#include "wxcommands.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif 

tc3DWindow2* tcPopupMessage::parent = 0;

/**
*
*/
void tcPopupMessage::SetParent(tc3DWindow2* par)
{
    parent = par;
}




/**
* Clears the text buffer
*/
void tcPopupMessage::Clear()
{
	messageText = "";
}

/**
*
*/
void tcPopupMessage::Draw()
{
    unsigned currentCount = tcTime::Get()->Get30HzCount();

    unsigned age = currentCount - birthCount;
    float alpha = 0.6f;

    if (age < 20)
    {
        bool blinkOn = age % 8 < 4;
        if (blinkOn)
        {
            redraw = true;
        }
        else
        {
            redraw = true;
            return;
        }
    }
    else if (age > 300) // 10 second display time
    {
        DestroyWindow();
        return;
    }
    else if (age > 210)
    {
        alpha = 0.006f * (310 - age);
    }

    if (!redraw) return;

    StartDraw();

    Vec4 color(1, 1, 1, 1);

    float x = 0.5f * float(mnWidth);
    float y = 0.5f * float(mnHeight);


    DrawRectangleR(0, 0, float(mnWidth), float(mnHeight), 
        Vec4(0, 0, 0, alpha), FILL_ON);

    DrawTextR(messageText.c_str(), x, y, defaultFont.get(),
        color, fontSize, CENTER_CENTER, float(mnWidth)-10.0f);


	FinishDraw();

    redraw = true;
}



void tcPopupMessage::OnLButtonDown(wxMouseEvent& event)
{
    if (associatedId != -1)
    {
        wxCommandEvent command(wxEVT_COMMAND_BUTTON_CLICKED, ID_NEWHOOK);    
        command.SetEventObject(parent);
        command.SetExtraLong(associatedId);
        AddPendingEvent(command);
    }

    DestroyWindow();
}


void tcPopupMessage::SetAssociatedId(long val)
{
    associatedId = val;
}

/**
*
*/
tcPopupMessage::tcPopupMessage(std::string text, const wxPoint& pos, int width)
            : tc3DWindow2(parent, pos, wxSize(width, 25), "PopupMessage", parent),
   messageText(text),
   redraw(true),
   associatedId(-1)
{
    fontSize = 11.0f;

    SetBaseRenderBin(parent->GetBaseRenderBin() + 10);
    birthCount = tcTime::Get()->Get30HzCount();

    SetBorderDraw(true);
    Raise();
}

tcPopupMessage::~tcPopupMessage() 
{

}

