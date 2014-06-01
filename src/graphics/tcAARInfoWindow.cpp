/** 
**  @file tcAARInfoWindow.cpp 
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

#include "tcAARInfoWindow.h"
#include "common/tinyxml.h"
#include "tcTime.h"
#include "tcTexture2D.h"
#include "tcGeometry.h"
#include "tcScrollBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_EVENT_TABLE(tcAARInfoWindow, tcXmlWindow)
    EVT_COMMAND(86, wxEVT_COMMAND_BUTTON_CLICKED, tcAARInfoWindow::OnCloseCommand)
    EVT_COMMAND(-1, wxEVT_COMMAND_SCROLLBAR_UPDATED, tcAARInfoWindow::OnScrollbarUpdated)
END_EVENT_TABLE()


tc3DWindow2* tcAARInfoWindow::parent = 0;


void tcAARInfoWindow::SetParent(tc3DWindow2* win)
{
	parent = win;
}


void tcAARInfoWindow::Draw() 
{
 //   if (drawCount++ % 2 != 0) return;

    StartDraw();

	//if (!IsBackgroundEnabled())
	//{
	//	DrawRectangleR(0, 0, mnWidth, mnHeight, Vec4(0.15, 0.15, 0.15, 1.0f), 
	//		FILL_ON);
	//}

	DrawAARInfo();

	FinishDraw();
}


void tcAARInfoWindow::DrawAARInfo()
{
    float xleft = 10.0f;
    float textx = xleft;
	//float maxWidth = float(mnWidth) - textx - 5.0f;
    float texty = 23.0f;
	tcRect textBox;
    const float indent = 10.0f;

	Vec4 color(0.4f, 1.0f, 0.4f, 1.0f);
    Vec4 unitColor(1.0f, 1.0f, 0.4f, 1.0f);
    Vec4 white(1.0f, 1.0f, 1.0f, 1.0f);

    if (aar.alliances.size() == 0)
    {
        return;
    }

    wxString s = aar.scenarioName.ToStdString().c_str();
    s += " (";
    s += aar.completedTime;
    s += ")";
    PrintText(xleft, textx, texty, white, true, s.ToStdString().c_str());
    PrintText(xleft+indent, textx, texty, color, true, "");


    // reorder alliances so that player alliance is first
    std::vector<unsigned int> allianceOrder;

    for (size_t n=0; (n<aar.alliances.size())&&(allianceOrder.size()==0); n++)
    {
        if (aar.alliances[n] == aar.playerAlliance)
        {
            allianceOrder.push_back(n);
        }
    }

    for (size_t n=0; n<aar.alliances.size(); n++)
    {
        if (aar.alliances[n] != aar.playerAlliance)
        {
            allianceOrder.push_back(n);
        }
    }

    for (size_t m=0; m<allianceOrder.size(); m++)
    {
        size_t n = allianceOrder[m];

        wxString sideText = wxString::Format("SIDE: %d (%s)", aar.alliances[n], aar.allianceNames[n].ToStdString().c_str());
        if (aar.alliances[n] == aar.playerAlliance)
        {
            sideText += " (PLAYER)";

            // print goal summary
            for (size_t line_idx=0; line_idx<aar.playerGoalStatus.size(); line_idx++)
            {
                PrintText(xleft+indent, textx, texty, color, true, aar.playerGoalStatus[line_idx].ToStdString().c_str());
            }
            PrintText(xleft, textx, texty, color, true, "");

        }
        PrintText(xleft+indent, textx, texty, white, true, sideText.ToStdString().c_str());
        PrintText(xleft+indent, textx, texty, color, true, "");

        // first count how many unit in damaged/lost categories
        size_t nDamaged = 0;
        size_t nLost = 0;
        for (size_t k=0; k<aar.damageSummary[n].size(); k++)
        {
            if (aar.damageSummary[n][k].damageFraction >= 1.0f)
            {
                nLost++;
            }
            else if (aar.damageSummary[n][k].damageFraction >= 0)
            {
                nDamaged++;
            }
        }

        if (nLost > 0)
        {
            PrintText(xleft+indent, textx, texty, color, true, "UNITS LOST:");
        }
        else
        {
            PrintText(xleft+indent, textx, texty, color, true, "NO UNITS LOST");
        }
        
        for (size_t k=0; k<aar.damageSummary[n].size(); k++)
        {
            wxString unit = aar.damageSummary[n][k].unitName;
            if (aar.damageSummary[n][k].landed)
            {
                unit += " landed";
            }

            wxString databaseClass = aar.damageSummary[n][k].databaseClass;
            float damage = aar.damageSummary[n][k].damageFraction;
            wxString damager = aar.damageSummary[n][k].damagerString;

            if (damage >= 1.0f)
            {

				PrintText(xleft+indent, textx, texty, color, false, "%s (%s) ", unit.ToStdString().c_str(), databaseClass.ToStdString().c_str());
                PrintText(xleft+indent, textx, texty, color, true, " %s", damager.ToStdString().c_str());
            }
        }

        PrintText(xleft+indent, textx, texty, color, true, "");


        if (nDamaged > 0)
        {
            PrintText(xleft+indent, textx, texty, color, true, "UNITS DAMAGED:");
        }
        else
        {
            PrintText(xleft+indent, textx, texty, color, true, "NO UNITS DAMAGED");
        }
        
        for (size_t k=0; k<aar.damageSummary[n].size(); k++)
        {
            wxString unit = aar.damageSummary[n][k].unitName;
            if (aar.damageSummary[n][k].landed)
            {
                unit += " landed";
            }

            wxString databaseClass = aar.damageSummary[n][k].databaseClass;
            float damage = aar.damageSummary[n][k].damageFraction;
            wxString damager = aar.damageSummary[n][k].damagerString;

            if (damage < 1.0f)
            {
                PrintText(xleft+indent, textx, texty, color, false, "%s (%s) ", unit.ToStdString().c_str(), databaseClass.ToStdString().c_str());
                PrintText(xleft+indent, textx, texty, color, true, "%.1f%%  %s", 100.0f*damage, damager.ToStdString().c_str());
            }
        }

        PrintText(xleft+indent, textx, texty, color, true, "");

        // equipment
        PrintText(xleft+indent, textx, texty, color, true, "EQUIPMENT EXPENDED:");
        
        for (size_t k=0; k<aar.equipmentSummary[n].size(); k++)
        {
            PrintText(xleft+indent, textx, texty, color, true, "%s (%d)", aar.equipmentSummary[n][k].databaseClass.ToStdString().c_str(), aar.equipmentSummary[n][k].quantity);
        }
        PrintText(xleft, textx, texty, color, true, "");

    }


	//DrawTextR(s.c_str(), textx, texty, 
	//		boldFont.get(), color, fontSizeLarge, LEFT_BASE_LINE, maxWidth, textBox);

 //   texty += textBox.Height() + 5.0f;



	float maxSpan = float(mnHeight);
	scrollBar->SetBarFraction(maxSpan / texty);

}



void tcAARInfoWindow::PrintText(float xleft, float& x, float& y, const Vec4& color, bool newLine, const char* formatString, ...)
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
void tcAARInfoWindow::OnCloseCommand(wxCommandEvent& event)
{
    DestroyWindow();
}

void tcAARInfoWindow::OnChar(wxKeyEvent& event)
{
    event.Skip();
    event.ResumePropagation(1);
}

void tcAARInfoWindow::OnEnterWindow(wxMouseEvent& event)
{
    SetFocus(); // to receive mousewheel events
}


void tcAARInfoWindow::OnKeyDown(wxKeyEvent& event)
{
    event.Skip();
    event.ResumePropagation(1);
}

void tcAARInfoWindow::OnLButtonDown(wxMouseEvent& event)
{
    tcXmlWindow::OnLButtonDown(event);
}



void tcAARInfoWindow::OnLButtonUp(wxMouseEvent& event)
{
    tcXmlWindow::OnLButtonUp(event);
}

void tcAARInfoWindow::OnLeaveWindow(wxMouseEvent& event)
{

}

/**
* Update mouseover status of slots
*/
void tcAARInfoWindow::OnMouseMove(wxMouseEvent& event)
{
    tcXmlWindow::OnMouseMove(event);
}

void tcAARInfoWindow::OnMouseWheel(wxMouseEvent& event)
{
    wxASSERT(scrollBar != 0);

    scrollBar->OnMouseWheel(event);
}

void tcAARInfoWindow::OnScrollbarUpdated(wxCommandEvent& event)
{
    yOffset = 0.25 * float(event.GetExtraLong());
}


void tcAARInfoWindow::SetAARFileName(const wxString& fileName)
{
    displayFileName = fileName;

	tcGoalTracker::Get()->ReadAAR(aar, fileName.ToStdString());
}



/**
* if hostParent argument is not used then static method SetParent must be called first
*/
tcAARInfoWindow::tcAARInfoWindow(const wxPoint& pos, const wxString& configFile, const wxString& name, tc3DWindow2* hostParent) 
                             : tcXmlWindow(hostParent, pos, wxSize(10, 10), configFile, name, hostParent),
	drawCount(0),
    yOffset(0),
	displayFileName("")
{

	wxASSERT(hostParent != 0);

	// put gui window on top
	SetBaseRenderBin(hostParent->GetBaseRenderBin() + windowLayer*10);
	wxWindow::Raise();

	windowLayer++;

    TiXmlNode* root = config->FirstChild("Window");
    if (!root)
    {
        fprintf(stderr, "tcAARInfoWindow::tcAARInfoWindow - Missing top level <Window> tag\n");
        return;
    }

    wxSize parentSize(hostParent->GetSize());
	int panelWidth = parentSize.GetWidth()-pos.x-150;

    SetSize(pos.x, pos.y, panelWidth, parentSize.GetHeight()-pos.y-75); // set all size params
    SetBackgroundColor(Vec4(0.2f, 0.2f, 0.2f, 0.5f));
    SetBackgroundDraw(true);
	SetActive(true);


	int panely = 25;
	//int panelHeight = mnHeight - panely - 10.0f;


    SetBorderDraw(true);
    SetBorderColor(Vec4(0.5, 0.5, 0.5, 0.5));


	int scrollBarWidth = 16;
    SetUseRenderSurface(true, scrollBarWidth+1);


	scrollBar = new tcScrollBar(this, wxPoint(panelWidth-scrollBarWidth-1, 2), wxSize(scrollBarWidth, mnHeight-3));
	scrollBar->SetBackgroundAlpha(0.7f);
    scrollBar->SetUseRenderSurface(true);
    scrollBar->SetActive(true);


}

tcAARInfoWindow::~tcAARInfoWindow() 
{
	windowLayer--;
}


