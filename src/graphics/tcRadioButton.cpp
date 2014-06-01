/**
**  @file tcRadioButton.cpp
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

#include "tcRadioButton.h"
#include "tcButton.h"
#include "tv_types.h"
#include "wxcommands.h"
#include "common/tinyxml.h"
#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif 

BEGIN_EVENT_TABLE(tcRadioButton, tc3DWindow2)
   EVT_COMMAND(-1, wxEVT_COMMAND_BUTTON_CLICKED , tcRadioButton::OnButtonCommand)
END_EVENT_TABLE()


unsigned tcRadioButton::ref_count = 0;


void tcRadioButton::Draw()
{
    if (!mbActive) return;

    StartDraw();

    Vec4 backgroundColor;
    Vec4 textColor;

    /*
    if (isMouseOver)
    {
        backgroundColor = 0xFFFFFFFF;
        textColor = 0xFE000000;
    }
    else
    {
        backgroundColor = 0xFF000000;
        textColor = 0xFEFFFFFF;
    }
    */
    backgroundColor = Vec4(0.5f, 0.5f, 0.5f, 0.5f);
    textColor = Vec4(1, 1, 1, 1);

	float width = float(mnWidth);
	float height = float(mnHeight);
    DrawRectangleR(0, 0, width, height, backgroundColor, FILL_ON);

    float x = 0.5 * width;
    float y = 9.0f;
	DrawTextR(caption.c_str(), x, y, defaultFont.get(), textColor, fontSize, CENTER_CENTER);

	FinishDraw();  
}


void tcRadioButton::OnButtonCommand(wxCommandEvent& event)
{
    int cmdId = event.GetId(); // 2.6.3 m_id;

    if (command == cmdId)
    {
        event.Skip();
        return;
    }
    // set clicked button on, others off
    // if new button is clicked, post a command event
    for(size_t n=0;n<buttons.size();n++)
    {
        if (buttons[n]->GetCommand() == cmdId)
        {
            if (!buttons[n]->IsOn())
            {
                wxCommandEvent cmd(wxEVT_COMMAND_BUTTON_CLICKED, command);    
                cmd.SetEventObject(this);
                cmd.SetExtraLong((long)n);
                AddPendingEvent(cmd);
                buttons[n]->SetOn(true);
            }
        }
        else
        {
            buttons[n]->SetOn(false);
        }

    }

}


void tcRadioButton::OnEnterWindow(wxMouseEvent& event)
{
    isMouseOver = true;
}

void tcRadioButton::OnLButtonDown(wxMouseEvent& event)
{
    event.Skip();
}

void tcRadioButton::OnLButtonUp(wxMouseEvent& event)
{
    event.Skip();
}

void tcRadioButton::OnLeaveWindow(wxMouseEvent& event)
{
    isMouseOver = false;
}

/**
* Sets button with command matching buttonCommand on and all others off
*/
void tcRadioButton::ActivateButton(long buttonCommand)
{
    for(size_t n=0;n<buttons.size();n++)
    {
        if (buttons[n]->GetCommand() == buttonCommand)
        {
			buttons[n]->SetOn(true);
        }
        else
        {
            buttons[n]->SetOn(false);
        }

    }

}


/**
* version to initialize from XML file
*/
tcRadioButton::tcRadioButton(tc3DWindow2 *parent, TiXmlNode *config)
: tc3DWindow2(parent, wxPoint(0,0), wxSize(10,10), "XMLButton", parent),
   caption("NULL"),
   command(-1),
   isMouseOver(false),
   soundEffect(-1),
   fontSize(16.0f)
{
    ref_count++;

    wxASSERT(config);
    if (config == NULL) return;
    
    TiXmlElement* current = config->ToElement();
    wxASSERT(current);
    if (current == NULL) return;

    int x;
    int y;
    int width;
    int height;
    int command;

    current->Attribute("X", &x);
    current->Attribute("Y", &y);
    current->Attribute("Width", &width);
    current->Attribute("Height", &height);

    current->Attribute("Command", &command);
    SetCommand(command);

    caption = current->Attribute("Caption");


    wxWindow::SetSize(x, y, width, height);


    // add buttons
    TiXmlNode* buttonNode = config->FirstChild("Button");
    while (buttonNode)
    {
        tcButton *button = new tcButton(this, buttonNode);
        buttons.push_back(button);
		button->SetActive(true);

        buttonNode = buttonNode->NextSibling("Button");
    }

    if (buttons.size())
    {
        buttons[0]->SetOn(true); // set first button ON by default
    }

    fprintf(stdout,"Created radio button %s, pos (%d,%d), size: (%d,%d)\n",
        caption.c_str(), x, y, width, height);
}





tcRadioButton::~tcRadioButton()
{
    wxASSERT(ref_count); 

    ref_count--;
 
}

