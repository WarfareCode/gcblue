/**
**  @file tcXmlWindow.cpp 
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

#include "tcXmlWindow.h"
#include "wxcommands.h"
#include "common/tinyxml.h"
#include "tcButton.h"
#include "tcRadioButton.h"
#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif 

unsigned tcXmlWindow::ref_count = 0;
int tcXmlWindow::windowLayer = 4;




BEGIN_EVENT_TABLE(tcXmlWindow, tc3DWindow2)
	EVT_COMMAND(-1, wxEVT_COMMAND_BUTTON_CLICKED , tcXmlWindow::OnButtonCommand)
END_EVENT_TABLE()



void tcXmlWindow::AddXMLControls()
{
    if ((config == NULL)||(config->Error()))
    {
        std::cerr << "Error - tcXmlWindow::AddXMLControls - Null or invalid xml file"
            << std::endl;
        return;
    }

    // config is also the root node
    TiXmlNode* root = config->FirstChild("Window");
    
    if (!root)
    {
        std::cerr << 
            "Error - tcXmlWindow::AddXMLControls - <Window> xml tag not found at doc top\n";
        return;
    }

	TiXmlElement* elt = root->ToElement();
    
	// background image
	std::string imageName;
	if (const char* s = elt->Attribute("BackgroundImage"))
	{
		imageName = s;
	}

	if (imageName.size() > 2)
	{
		LoadBackgroundImage(imageName.c_str());
	}


	int xmlWidth = 0;
	int xmlHeight = 0;
	elt->Attribute("Width", &xmlWidth);
	elt->Attribute("Height", &xmlHeight);
	if ((xmlWidth > 0) && (xmlHeight > 0))
	{
		wxPoint pos = wxWindow::GetPosition();
	    SetSize(pos.x, pos.y, xmlWidth, xmlHeight); // set all size params
	}

    // add buttons

    TiXmlNode* current = root->FirstChild("Button");
    while (current)
    {
        tcButton* button = new tcButton(this, current);
		//button->SetBaseRenderBin(baseRenderBin + 10);
		button->SetActive(true);

        current = current->NextSibling("Button");
    }

    // add radio buttons
    current = root->FirstChild("RadioButton");
    while (current)
    {
        tcRadioButton *radioButton = new tcRadioButton(this, current);
		//radioButton->SetBaseRenderBin(baseRenderBin + 10);
		radioButton->SetActive(true);

        current = current->NextSibling("RadioButton");
    }

}


void tcXmlWindow::SetAllButtonState(bool state)
{
	for (unsigned int n=0; n<children.size(); n++)
	{
		if (tcButton* button = dynamic_cast<tcButton*>(children[n]))
		{
			button->SetActive(state);
		}
		else if (tcRadioButton* radio = dynamic_cast<tcRadioButton*>(children[n]))
		{
			radio->SetActive(state);
		}
	}
}


/**
* Intended to be overrided to intercept command events from GUI
* objects within the window.
* This routine intercepts the ID_BUTTONREDRAW event which is
* a workaround for the older style of owner controlled buttons.
*/
void tcXmlWindow::OnButtonCommand(wxCommandEvent& event)
{
    if (event.GetId() == ID_BUTTONREDRAW)
    {
    }
    else
    {
        event.Skip();
    }
}

void tcXmlWindow::OnKeyDown(wxKeyEvent& event)
{
    event.Skip();
}

void tcXmlWindow::OnLButtonDown(wxMouseEvent& event)
{
	/* check if cursor is over a non-empty slot, if so
	** arm drag with slot idx */
	wxPoint point = event.GetPosition();

//    float x = (float)point.x;
//    float y = (float)point.y;

    isLButtonDown = true;
    if (isDragable && ((point.y <= 20) || (point.y >= mnHeight)))
    {
        windowDragOn = true;
        // position in parent's frame of mouse pointer
        windowDragPoint = wxPoint(mrectWindow.GetLeft() + point.x, mrectWindow.GetBottom() + point.y);

		CaptureMouse();
        return;
    }

}

void tcXmlWindow::OnLButtonUp(wxMouseEvent& event)
{
    isLButtonDown = false;
    windowDragOn = false;
	ReleaseMouse();
}


void tcXmlWindow::OnMouseMove(wxMouseEvent& event)
{
    wxPoint point = event.GetPosition();

	UpdateWindowDrag(point);
}

void tcXmlWindow::OnSize(wxSizeEvent& event)
{
    tc3DWindow2::OnSize(event);

    UpdateObjectsForResize();
}


void tcXmlWindow::SetButtonDisable(long command, bool state)
{
    for (unsigned int n=0; n<children.size(); n++)
	{
		if (tcButton* button = dynamic_cast<tcButton*>(children[n]))
		{
			if (button->GetCommand() == command)
			{
                button->SetForceDisable(state);
				return;
			}
		}
		
	}
}

tcButton* tcXmlWindow::GetButtonWithCommand(long command)
{
	for (unsigned int n=0; n<children.size(); n++)
	{
		if (tcButton* button = dynamic_cast<tcButton*>(children[n]))
		{
			if (button->GetCommand() == command)
			{
				return button;
			}
		}
	}

	return 0;
}


tcRadioButton* tcXmlWindow::GetRadioButtonWithCommand(long command)
{
	for (unsigned int n=0; n<children.size(); n++)
	{
		if (tcRadioButton* button = dynamic_cast<tcRadioButton*>(children[n]))
		{
			if (button->GetCommand() == command)
			{
				return button;
			}
		}
	}

	return 0;
}

/**
* This allows a window to change the caption of a button based on game state
* Using this will override the caption specified in the xml file
*/
void tcXmlWindow::SetButtonCaption(long command, const std::string& caption)
{
	for (unsigned int n=0; n<children.size(); n++)
	{
		if (tcButton* button = dynamic_cast<tcButton*>(children[n]))
		{
			if (button->GetCommand() == command)
			{
				button->SetCaption(caption);
				return;
			}
		}
		
	}
}

void tcXmlWindow::SetDragable(bool state)
{
    isDragable = state;
}


/**
* Finds first radio button with command matching radioCommand and sets
* button on with command matching buttonCommand.
*/
void tcXmlWindow::SetRadioButtonState(long radioCommand, long buttonCommand)
{
	for (unsigned int n=0; n<children.size(); n++)
	{
		if (tcRadioButton* radio = dynamic_cast<tcRadioButton*>(children[n]))
		{
			if (radio->GetCommand() == radioCommand)
			{
				radio->ActivateButton(buttonCommand);
				return;
			}
		}
		
	}
}

/**
* Call after resize to adjust button position, etc, if necessary
*/
void tcXmlWindow::UpdateObjectsForResize()
{
    if (children.size() == 0) return; // children not added yet

    if (config == 0)
    {
        wxASSERT(false);
        return;
    }

    // config is also the root node
    TiXmlNode* root = config->FirstChild("Window");
    
    if (!root)
    {
        wxASSERT(false);
        return;
    }

    // update buttons
    TiXmlNode* current = root->FirstChild("Button");
    while (current)
    {
        TiXmlElement* elt = current->ToElement();
        wxASSERT(elt != 0);
        if (elt == 0) return;

        int command;
        elt->Attribute("Command", &command);
    
        if (tcButton* button = GetButtonWithCommand(command))
        {
            button->ReapplyConfig(current);
        }
        else
        {
            wxASSERT(false);
        }

        current = current->NextSibling("Button");
    }
}


void tcXmlWindow::UpdateWindowDrag(const wxPoint& pos)
{
    if (!windowDragOn) return;

    // position in parent's frame of mouse pointer
    wxPoint current = wxPoint(mrectWindow.GetLeft() + pos.x, mrectWindow.GetBottom() + pos.y);
    if (current != windowDragPoint)
    {
        wxPoint delta = current - windowDragPoint;
		int xmove = mrectWindow.GetLeft() + delta.x;
		int ymove = mrectWindow.GetTop() + delta.y;
        tc3DWindow2::MoveWindow(xmove, ymove);
        windowDragPoint = current;
    }
}


tcXmlWindow::tcXmlWindow(wxWindow *parent, 
                                   const wxPoint& pos, const wxSize& size, 
                                   const wxString& configFile, const wxString& name,
								   tc3DWindow2* graphicsHost) 
                                   : tc3DWindow2(parent, pos, size, name, graphicsHost),
                                     isDragable(false),
                                     windowDragOn(false),
                                     isLButtonDown(false)
{
    if (configFile.length() > 2)
    {

        config = new TiXmlDocument(configFile.c_str());
        if (!config->LoadFile())
        {
            delete config;
            config = NULL;
            std::cerr << "Error loading XML file " << configFile.c_str() << std::endl;
			wxString s = wxString::Format("Missing xml file %s", configFile.c_str());
			wxMessageBox(s, "Error", wxICON_ERROR);
        }
    }
    else
    {
        config = NULL;
    }

	if (config)
	{
		AddXMLControls();
	}

    if (ref_count++ > 0) return;

}

/**
* If this is the last object destroyed, 
* clean up Gdiplus objects.
*/
tcXmlWindow::~tcXmlWindow() 
{
    if (config) delete config;

    wxASSERT(ref_count);
    if (--ref_count > 0) return;
}

