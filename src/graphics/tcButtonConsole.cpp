/** @file tcButtonConsole.cpp */
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
#ifdef WIN32
#include "wx/msw/private.h" // for MS Windows specific definitions
#endif
#endif

#include "tcButtonConsole.h"
#include "tcButton.h"
#include "wxcommands.h"
#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_EVENT_TABLE(tcButtonConsole, tcWindow)
    EVT_COMMAND(ID_BUTTONREDRAW, wxEVT_COMMAND_BUTTON_CLICKED, tcButtonConsole::ButtonRequestedRedraw)
END_EVENT_TABLE()

void tcButtonConsole::AddButton(wxRect bounds, long command, std::string caption)
{
    wxSize buttonSize = bounds.GetSize();
    wxPoint buttonPosition = bounds.GetPosition();

#if 0
    tcButton *buttonToAdd = new tcButton(this, buttonPosition, buttonSize);
    buttonToAdd->SetCaption(caption);
    buttonToAdd->SetCommand(command);
    buttonToAdd->SetSendRedraw(true);

    buttons.push_back(buttonToAdd);
#endif
}

void tcButtonConsole::ButtonRequestedRedraw(wxCommandEvent& event)
{
    tcConsole::ForceRedraw();
}

int tcButtonConsole::Draw() 
{
    if (tcSoundConsole::Draw())
    {
        Gdiplus::Graphics *graphics;
        if (!GetGraphics(graphics)) 
        {   
            std::cerr << "Failed to get Graphics object in tcButtonConsole::Draw()" << std::endl;  
            return 0;
        } 
        /**
        size_t nButtons = buttons.size();
        for(size_t n=0;n<nButtons;n++)
        {
            buttons[n]->Draw(graphics);
        }
        */
        DrawChildren(graphics);
        ReleaseGraphics(graphics);
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
* Override to call SetActive of child button windows 
*/
void tcButtonConsole::SetActive(bool abActive)
{
    tcWindow::SetActive(abActive);

    size_t nButtons = buttons.size();
    for(size_t n=0;n<nButtons;n++)
    {
        buttons[n]->SetActive(abActive);
    }
}

/********************************************************************/
tcButtonConsole::tcButtonConsole(wxWindow *parent, 
                         const wxPoint& pos, const wxSize& size, 
                         const wxString& name) :
    tcSoundConsole(parent, pos, size, name) 
{
    buttons.clear();
    nyzero = mnHeight - 50; // margin for buttons at bottom
}
/********************************************************************/
tcButtonConsole::~tcButtonConsole() {

}
