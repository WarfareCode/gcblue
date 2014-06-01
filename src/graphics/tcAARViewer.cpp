/**
**  @file tcAARViewer.cpp
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

#include "tcAARViewer.h"
#include "tv_types.h"
#include "wxcommands.h"
#include "common/tinyxml.h"
#include "tcTexture2D.h"
#include "tcButton.h"
#include "tcAARInfoWindow.h"
#include "tcAARBrowsePanel.h"
#include "tc3DViewer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


BEGIN_EVENT_TABLE(tcAARViewer, tcXmlWindow)
	EVT_COMMAND(-1, wxEVT_COMMAND_TEXT_UPDATED, tcAARViewer::SelectDisplayFileName)
END_EVENT_TABLE()



const wxString& tcAARViewer::GetDisplayFileName() const
{
    return displayFileName;
}


void tcAARViewer::BuildBrowseInfo()
{
    browsePanel->BuildBrowseInfo();

    wxString fileName;
    if (browsePanel->GetFirstFileName(fileName))
    {
        browsePanel->SelectDisplayFileName(fileName);
    }
}

/**
 *
 */
void tcAARViewer::Draw()
{
    StartDraw();

    // draw border here to work around scroll bar border issues (for browse/select box on left)
    wxSize browseSize = browsePanel->GetSize();
    DrawRectangleR(50, 51, float(browseSize.GetWidth()), float(browseSize.GetHeight()), 
        Vec4(0.5, 0.5, 0.5, 0.5));

	FinishDraw();
}


void tcAARViewer::InitializeButtons()
{
    size_t nButtons = 0;
    float x = 50.0f;
    float y = 50.0f;
    float width = 64.0f;

    wxASSERT(buttons.size() == 0);
    buttons.clear();

    for (size_t n=0; n<nButtons; n++)
    {
       
    }

		
}

void tcAARViewer::InitializeBrowsePanel()
{
    // border draw coordinates are hard-coded in Draw
	browsePanel = new tcAARBrowsePanel(this, wxPoint(50, 50), wxSize(320, mnHeight-125), "AARBrowsePanel", this);
}


void tcAARViewer::InitializeInfoWindow()
{
	infoWindow = new tcAARInfoWindow(wxPoint(400, 50), "xml/aar_info.xml", "AARViewInfo", this);
    wxASSERT(infoWindow != 0);

    infoWindow->SetBackgroundColor(Vec4(0.1f, 0.1f, 0.1f, 0.2f));
    infoWindow->SetButtonDisable(86, true); // disable the close button
    infoWindow->SetDragable(false);
    //infoWindow->SetUseRenderSurface(true);
}


void tcAARViewer::OnChar(wxKeyEvent& event)
{
    event.Skip();
    event.ResumePropagation(1);
}


void tcAARViewer::OnKeyDown(wxKeyEvent& event)
{
    event.Skip();
    event.ResumePropagation(1);
}


/**
 *
 */
void tcAARViewer::OnMouseMove(wxMouseEvent& event) 
{
	mousePosition = event.GetPosition();
}

/**
 *
 */
void tcAARViewer::OnLButtonDown(wxMouseEvent& event) 
{
    if (!mbActive) 
    {
        event.Skip();
        return;
    }

    mousePosition = event.GetPosition();
}

void tcAARViewer::OnSize(wxSizeEvent& event)
{
    tcXmlWindow::OnSize(event);

    wxSize size = event.GetSize();

    if (browsePanel != 0)
    {
        browsePanel->SetSize(50, 50, 320, mnHeight - 50-25);
    }

	if (infoWindow != 0)
	{
		infoWindow->SetSize(400, 50, mnWidth-400-10, mnHeight-50-25);
	}
}

void tcAARViewer::SetButtonOn(size_t idx)
{
    return;
    wxASSERT(buttons.size() == 0);

    // first set all buttons off
    for (size_t n=0; n<buttons.size(); n++)
    {
        buttons[n]->SetOn(false);
    }

    // set indicated button on
    if (idx < buttons.size())
    {
        buttons[idx]->SetOn(true);
    }
    else
    {
        wxASSERT(false);
    }

}

void tcAARViewer::SelectDisplayFileName(wxCommandEvent& event)
{
	wxString fileName = event.GetString().c_str();

	SelectDisplayFileName(fileName);
}

void tcAARViewer::SelectDisplayFileName(const wxString& fileName)
{
    displayFileName = fileName;
    infoWindow->SetAARFileName(fileName);
}

/**
*
*/
tcAARViewer::tcAARViewer(wxWindow *parent, 
                             const wxPoint& pos, const wxSize& size, const wxString& name, tc3DWindow2* graphicsHost) 
                             : 
    tcXmlWindow(parent, pos, size, "xml/aar_viewer.xml", name, graphicsHost),
	basePosition(20, 50),
    displayFileName("")
{

	//LoadBackgroundImage("start_background_plain.jpg");

    if (!config)
    {
        fprintf(stderr, "tcAARViewer::tcAARViewer - NULL xml config node\n");
        return;
    }

    TiXmlNode* root = config->FirstChild("Window");
    if (!root)
    {
        fprintf(stderr, "tcAARViewer::tcAARViewer - "
			"Missing top level <Window> tag\n");
        return;
    }

    InitializeButtons();
	InitializeBrowsePanel();
    InitializeInfoWindow();


    SetBorderDraw(false);
}



tcAARViewer::~tcAARViewer() 
{
}


