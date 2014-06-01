/** 
**  @file tcTextEntryBox.cpp 
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

#include "tcTextEntryBox.h"
#include "tcButton.h"
#include "tcEditBox.h"
#include "common/tinyxml.h"
#include "network/tcMultiplayerInterface.h"
#include "wxcommands.h"
#include "common/tcOptions.h"
#include "tcCommandQueue.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_EVENT_TABLE(tcTextEntryBox, tcXmlWindow)
EVT_COMMAND(1, wxEVT_COMMAND_TEXT_UPDATED, tcTextEntryBox::SendText)
EVT_COMMAND(CLOSE_BUTTON, wxEVT_COMMAND_BUTTON_CLICKED, tcTextEntryBox::OnCloseCommand)
END_EVENT_TABLE()

using network::tcMultiplayerInterface;

tc3DWindow2* tcTextEntryBox::parent = 0;

void tcTextEntryBox::SetParent(tc3DWindow2* par)
{
    parent = par;
}

void tcTextEntryBox::Draw() 
{
	if (destroyMe)
	{
		DestroyWindow();
		return;
	}
    
    StartDraw();

	if (!IsBackgroundEnabled())
	{
		DrawRectangle(0, 0, float(mnWidth), float(mnHeight), 
			Vec4(0, 0, 0, 0.8f), FILL_ON);

		DrawThickRectangle(0, 0, float(mnWidth), float(mnHeight), 2.0f,
			Vec4(1, 1, 1, 0.6f));
	}


	FinishDraw(); 
}



void tcTextEntryBox::OnChar(wxKeyEvent& event)
{
	int nChar = event.GetKeyCode();
	//bool controlDown = event.ControlDown();
	//bool altDown = event.AltDown();

    switch(nChar)
	{
    	case WXK_ESCAPE:
            destroyMe = true;
		break;
    }
}


/**
* Close and destroy window
*/
void tcTextEntryBox::OnCloseCommand(wxCommandEvent& event)
{
    destroyMe = true;
}

void tcTextEntryBox::OnKeyDown(wxKeyEvent& event)
{
}


void tcTextEntryBox::OnLButtonDown(wxMouseEvent& event)
{
}

/**
* Send chat text to all connections
*/
void tcTextEntryBox::SendText(wxCommandEvent& event)
{
	// copy user text in textParam field of command
	command.textParam = event.GetString().c_str();

	tcCommandQueue::Get()->AddCommand(command);

	destroyMe = true;
}

void tcTextEntryBox::SetCaption(const std::string& s)
{
	caption = s;

    textEntry->SetCaption(caption.c_str());
}

void tcTextEntryBox::SetCommand(const tsCommandInfo& cmd)
{
	command = cmd;
}


/**
* @param surfaceHost tcWindow to share surface of
*/
tcTextEntryBox::tcTextEntryBox(const wxPoint& pos, const wxSize& size, 
                             const wxString& name, const wxString& configFile) 
                             : tcXmlWindow(parent, pos, size, configFile, name, parent),
							 destroyMe(false)
{
    if (!config)
    {
        std::cerr << "tcTextEntryBox::tcTextEntryBox - NULL xml config node\n";
        return;
    }

    TiXmlNode* root = config->FirstChild("Window");
    if (!root)
    {
        std::cerr << "tcTextEntryBox::tcTextEntryBox - Missing top level <Window> tag\n";
        return;
    }

	SetBaseRenderBin(parent->GetBaseRenderBin() + 10);
	tc3DWindow2::MoveToTop();

    // add chat text edit box
    TiXmlNode* current = root->FirstChild("TextEntry");
    textEntry = new tcEditBox(this, current);
    textEntry->SetCommand(1);
    textEntry->SetClearOnReturn(false);
    textEntry->SetBuffer("");

	const int closeButtonSize = 12;
    closeButton = new tcButton(this, wxPoint(mnWidth - closeButtonSize, 0), 
        wxSize(closeButtonSize, closeButtonSize));
    closeButton->SetActive(true);
    closeButton->SetBackgroundAlpha(1.0);
    closeButton->SetCaption("");
    closeButton->SetCommand(CLOSE_BUTTON);
    closeButton->LoadImages("close.png", "close.png", "close.png", "close.png");
    closeButton->SetSendRedraw(true);
}

tcTextEntryBox::~tcTextEntryBox() 
{
}


