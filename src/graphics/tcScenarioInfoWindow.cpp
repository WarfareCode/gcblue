/** 
**  @file tcScenarioInfoWindow.cpp 
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

#include "tcScenarioInfoWindow.h"
#include "common/tinyxml.h"
#include "tcTime.h"
#include "tcTexture2D.h"
#include "tcGeometry.h"
#include "tcScrollBar.h"
#include "tcSimState.h"
#include "tcSimPythonInterface.h"
#include "tcScenarioInterface.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_EVENT_TABLE(tcScenarioInfoWindow, tcXmlWindow)
    EVT_COMMAND(-1, wxEVT_COMMAND_SCROLLBAR_UPDATED, tcScenarioInfoWindow::OnScrollbarUpdated)
END_EVENT_TABLE()





void tcScenarioInfoWindow::Draw() 
{
    StartDraw();

    float y1 = yStart - yOffset;
    float y2 = 0;
	DrawScenarioInfo(y1, y2);

    DrawBriefingInfo(y2 + 25.0f, y2);

    float textBottom = (y2 - y1) + yStart + 50.0f;

	float maxSpan = float(mnHeight);

	scrollBar->SetBarFraction(maxSpan / textBottom);


	FinishDraw();
}



void tcScenarioInfoWindow::DrawScenarioInfo(float y1, float& y2)
{
    tcSimState* simState = tcSimState::Get();

    Vec4 color;

    /*** Draw description ***/
    tcString infostring;
    if (simState->msScenarioInfo.mbLoaded) 
	{
        //color.set(0.68f, 0.98f, 1.0f, 1.0f);
        color.set(0.6f, 1, 0.6f, 1);
    }
    else 
	{
		color.set(0.4f, 0.52f, 0.52f, 1.0f);
    }

    float textx = xStart;
	float texty = y1 + 15.0f;
    float maxWidth = (float)(mnWidth - xStart - 25);

    infostring.Format("SCENARIO: %s\n\n", simState->msScenarioInfo.mzName);
    infostring += simState->msScenarioInfo.mzDescription;

    tcRect r;
	DrawTextR(infostring.GetBuffer(), textx, texty,
		defaultFont.get(), color, 16.0f, LEFT_TOP, maxWidth, r);

    y2 = texty + r.Height();
    
	
}

void tcScenarioInfoWindow::DrawBriefingInfo(float y1, float& y2)
{
	tcScenarioInterface* scenarioInterface = tcSimPythonInterface::Get()->GetScenarioInterface();
	wxASSERT(scenarioInterface);

	Vec4 color(0.6f, 1, 0.6f, 1);

	int userAlliance = tcUserInfo::Get()->GetOwnAlliance();

	const std::string& briefingText = scenarioInterface->GetSimpleBriefing(userAlliance);

    float x = xStart;
    float y = y1;
    float maxWidth = (float)(mnWidth - xStart - 25);

	float fontSize;
    if (mnWidth > 1200)
	{
		fontSize = 18.0f;
	}
	else if (mnWidth > 1000)
	{
		fontSize = 16.0f;
	}
	else
	{
		fontSize = 14.0f;
	}


    tcRect r;
	DrawTextR(briefingText.c_str(), x, y,
		defaultFont.get(), color, fontSize, LEFT_TOP, maxWidth, r);

    y2 = y + r.Height();
}



void tcScenarioInfoWindow::PrintText(float xleft, float& x, float& y, const Vec4& color, bool newLine, const char* formatString, ...)
{
    enum {STR_LENGTH = 1024};
    static char textBuffer[STR_LENGTH];
    //static Vec4 color(0.4f, 1.0f, 0.4f, 1.0f);
    static tcRect textBox;

    const float textFontSize = 12.0f;

    va_list arguments;

    va_start(arguments, formatString);
    _vsnprintf_s(textBuffer, sizeof(textBuffer), _TRUNCATE, formatString, arguments);
    va_end(arguments);

    float maxWidth = float(mnWidth) - x;

    DrawTextR(textBuffer, x, y - yOffset, 
			defaultFont.get(), color, textFontSize, LEFT_CENTER, maxWidth, textBox);

    if (newLine)
    {
        y += textBox.Height() + 2.0f;
        x = xleft;
    }
    else
    {
        x += textBox.Width();
    }
}


/**
* Close and destroy window at next safe opportunity
*/
void tcScenarioInfoWindow::OnCloseCommand(wxCommandEvent& event)
{
    DestroyWindow();
}

void tcScenarioInfoWindow::OnChar(wxKeyEvent& event)
{
    event.Skip();
    event.ResumePropagation(1);
}


void tcScenarioInfoWindow::OnKeyDown(wxKeyEvent& event)
{
    event.Skip();
    event.ResumePropagation(1);
}


void tcScenarioInfoWindow::OnLButtonDown(wxMouseEvent& event)
{
    tcXmlWindow::OnLButtonDown(event);
}



void tcScenarioInfoWindow::OnLButtonUp(wxMouseEvent& event)
{
    tcXmlWindow::OnLButtonUp(event);
}

void tcScenarioInfoWindow::OnLeaveWindow(wxMouseEvent& event)
{

}

/**
* Update mouseover status of slots
*/
void tcScenarioInfoWindow::OnMouseMove(wxMouseEvent& event)
{
    tcXmlWindow::OnMouseMove(event);
}

void tcScenarioInfoWindow::OnScrollbarUpdated(wxCommandEvent& event)
{
    yOffset = 0.25 * float(event.GetExtraLong());
}

void tcScenarioInfoWindow::OnSize(wxSizeEvent& event)
{
    tcXmlWindow::OnSize(event);

	wxPoint pos = GetPosition();
	wxSize mySize = GetSize();

	wxSize parentSize(hostParent->GetSize());
	int panelWidth = parentSize.GetWidth()-pos.x-40;

    //SetSize(pos.x, pos.y, panelWidth, parentSize.GetHeight()-pos.y-60); // set all size params
	SetSize(pos.x, pos.y, mySize.GetWidth(), mySize.GetHeight());
    SetBackgroundColor(Vec4(0.2f, 0.2f, 0.2f, 0.5f));
    SetBackgroundDraw(true);
	SetActive(IsActive());



    SetBorderDraw(true);
    SetBorderColor(Vec4(0.5, 0.5, 0.5, 0.5));


	int scrollBarWidth = 16;
    SetUseRenderSurface(true, scrollBarWidth+1);
    wxASSERT(scrollBar != 0);
    if (scrollBar == 0) return;

	scrollBar->SetSize(mySize.GetWidth()-scrollBarWidth-1, 2, scrollBarWidth, mnHeight-3);

	//RemoveChild(scrollBar);

	//scrollBar = new tcScrollBar(this, wxPoint(panelWidth-scrollBarWidth-1, 2), wxSize(scrollBarWidth, mnHeight-3));
	//scrollBar->SetBackgroundAlpha(0.7f);
 //   scrollBar->SetUseRenderSurface(true);
 //   scrollBar->SetActive(true);

}



/**
* if hostParent argument is not used then static method SetParent must be called first
*/
tcScenarioInfoWindow::tcScenarioInfoWindow(const wxPoint& pos, const wxString& configFile, const wxString& name, tc3DWindow2* hostParent) 
                             : tcXmlWindow(hostParent, pos, wxSize(10, 10), configFile, name, hostParent),
	drawCount(0),
    yOffset(0),
    xStart(25.0f),
	yStart(10.0f),
	scrollBar(0)
{
	wxASSERT(hostParent != 0);

	// put gui window on top
	SetBaseRenderBin(hostParent->GetBaseRenderBin() + windowLayer*10);
	wxWindow::Raise();

	windowLayer++;

	wxASSERT(config != 0);
    TiXmlNode* root = config->FirstChild("Window");
    if (!root)
    {
        fprintf(stderr, "tcScenarioInfoWindow::tcScenarioInfoWindow - Missing top level <Window> tag\n");
        return;
    }

    wxSize parentSize(hostParent->GetSize());

	int panelWidth = parentSize.GetWidth()-pos.x-40;

	// moved scrollbar creation before SetSize, sometimes OnSize is called without initialized scrollBar?
	int scrollBarWidth = 16;
	scrollBar = new tcScrollBar(this, wxPoint(panelWidth-scrollBarWidth-1, 2), wxSize(scrollBarWidth, mnHeight-3));
	scrollBar->SetBackgroundAlpha(0.7f);
    scrollBar->SetUseRenderSurface(true);
    scrollBar->SetActive(true);

    SetSize(pos.x, pos.y, panelWidth, parentSize.GetHeight()-pos.y-60); // set all size params
    SetBackgroundColor(Vec4(0.2f, 0.2f, 0.2f, 0.5f));

    SetBackgroundDraw(true);
	SetActive(true);

    SetBorderDraw(true);
    SetBorderColor(Vec4(0.5, 0.5, 0.5, 0.5));

    SetUseRenderSurface(true, scrollBarWidth+1);
}

tcScenarioInfoWindow::~tcScenarioInfoWindow() 
{
	windowLayer--;
}


