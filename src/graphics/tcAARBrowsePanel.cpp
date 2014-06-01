/**
**  @file tcAARBrowsePanel.cpp
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

#include "tcAARBrowsePanel.h"
#include "tv_types.h"
#include "tcTexture2D.h"
#include "wxcommands.h"
#include "common/tinyxml.h"
#include "tcScrollBar.h"
#include "tcSound.h"
#include "tc3DViewer.h"
#include "tcGoalTracker.h"
#include "wx/dir.h"

#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif 



BEGIN_EVENT_TABLE(tcAARBrowsePanel, tc3DWindow2)
    EVT_COMMAND(-1, wxEVT_COMMAND_SCROLLBAR_UPDATED, tcAARBrowsePanel::OnScrollbarUpdated)
END_EVENT_TABLE()


bool BrowseSortPredicate(const tcAARBrowsePanel::BrowseItem& a, const tcAARBrowsePanel::BrowseItem& b)
{
    return (a.fileName.compare(b.fileName) > 0);
}


/**
* Updates browse info data based on classificationMask
* Should be called after changing classificationMask
*/
void tcAARBrowsePanel::BuildBrowseInfo()
{
    browseInfo.clear();

    tcGoalTracker* goalTracker = tcGoalTracker::Get();

    wxArrayString fileList;

    wxDir::GetAllFiles("aar", &fileList, "*.xml");
    fileList.Sort(true);

    for (size_t n=0; n<fileList.size(); n++)
    {
        tcGoalTracker::AARInfo info;
		if (goalTracker->ReadAARInfo(info, fileList[n].ToStdString()))
        {
            BrowseItem item;

            item.fileName = fileList[n].c_str();
            item.scenarioName = info.scenarioName;
            item.date = info.completedTime;
            item.playerAlliance = info.playerAlliance;

            browseInfo.push_back(item);
        }
    }

    UpdateDrawInfo();
}

const wxString& tcAARBrowsePanel::GetDisplayFileName() const
{
    return displayFileName;
}

/**
* 
*/
bool tcAARBrowsePanel::ProcessMouseClick(const wxPoint& pos)
{
	std::vector<BrowseItem>& info = browseInfo;

	for (size_t n=0; n < info.size(); ++n)
	{
		wxRect r(info[n].drawBox.x, info[n].drawBox.y, 
					info[n].drawBox.width, info[n].drawBox.height);

		if (r.Contains(pos))
		{
            SelectDisplayFileName(info[n].fileName);
			return true;
		}
	}

	return false;
}



void tcAARBrowsePanel::ClearMouseOver()
{
	std::vector<BrowseItem>& info = browseInfo;

	for (size_t n=0; n < info.size(); ++n)
	{
		BrowseItem& item = info[n];

		if (item.fileName == displayFileName)
		{
			item.drawState = BrowseItem::ON;
			item.color = Vec4(1, 1, 1, 1);
		}
		else
		{
			item.drawState = BrowseItem::OFF;
			item.color = Vec4(0.6f, 0.6f, 0.5f, 1);
		}
	}
}


/**
* Update drawing info of browseInfo vector
*/
void tcAARBrowsePanel::UpdateDrawInfo()
{
	std::vector<BrowseItem>& info = browseInfo;

    float x = 5.0f;
    float y = 15.0f;
    float xWidth = float(mnWidth);
    float yHeight = 15.0f;

	for (size_t n=0; n < info.size(); ++n)
	{
		BrowseItem& item = info[n];

		item.drawBox.x = x;
		item.drawBox.y = y - yOffset;
		item.drawBox.height = yHeight - 2;
		item.drawBox.width = xWidth;

		y += yHeight;

		wxRect r(item.drawBox.x, item.drawBox.y, 
					item.drawBox.width, item.drawBox.height);

		int oldState = item.drawState;

		if (item.fileName == displayFileName)
		{
			item.drawState = BrowseItem::ON;
            item.color = Vec4(1, 1, 1, 1);
			if (item.drawState != oldState) tcSound::Get()->PlayEffect("MutedBeep");
		}
		else if (mouseOver && (r.Contains(mousePosition)))
		{
			item.drawState = BrowseItem::OVER;
            item.color = Vec4(0.6f, 0.6f, 1, 1);
			if (item.drawState != oldState) tcSound::Get()->PlayEffect("Thuck");
		}
		else
		{
			item.drawState = BrowseItem::OFF;
            item.color = Vec4(0.6f, 0.6f, 0.5f, 1);
		}
	}


	// update scroll bar (only need to do this once per browse change)
	float ySpan = 50.0f + float(info.size())*yHeight;
	float maxSpan = float(mnHeight);
	
	scrollBar->SetBarFraction(maxSpan / ySpan);
}

/**
 *
 */
void tcAARBrowsePanel::Draw()
{
    StartDraw();

    for (size_t n=0; n<browseInfo.size(); n++)
    {
        BrowseItem& item = browseInfo[n];

        wxString s = item.scenarioName;
        s += " (";
        s += item.date;
        s += ")";

        DrawTextR(s.c_str(), item.drawBox.x, 
            item.drawBox.y + 0.5f*item.drawBox.height, defaultFont.get(), 
            item.color, 14.0f, LEFT_CENTER);
    }

	FinishDraw();
}


/**
* @return true if browse summary has at least one item
* Set fileName to first item name, used to auto select last game played
*/
bool tcAARBrowsePanel::GetFirstFileName(wxString& fileName) const
{
    if (browseInfo.size() > 0)
    {
        fileName = browseInfo[0].fileName;
        return true;
    }
    else
    {
        fileName.clear();
        return false;
    }
}

/**
 *
 */
void tcAARBrowsePanel::OnMouseMove(wxMouseEvent& event) 
{
	mousePosition = event.GetPosition();

	UpdateDrawInfo();
}

/**
 *
 */
void tcAARBrowsePanel::OnLButtonDown(wxMouseEvent& event) 
{
    if (!mbActive) 
    {
        event.Skip();
        return;
    }

    mousePosition = event.GetPosition();

	if (ProcessMouseClick(mousePosition))
	{
		UpdateDrawInfo();
		return;
	}
}


void tcAARBrowsePanel::OnEnterWindow(wxMouseEvent& event)
{
	mouseOver = true;
    SetFocus(); // to receive mousewheel events
}

void tcAARBrowsePanel::OnLeaveWindow(wxMouseEvent& event)
{
	ClearMouseOver();

	mouseOver = false;
}

void tcAARBrowsePanel::OnMouseWheel(wxMouseEvent& event)
{
    wxASSERT(scrollBar != 0);

    scrollBar->OnMouseWheel(event);
}

void tcAARBrowsePanel::OnScrollbarUpdated(wxCommandEvent& event)
{
    yOffset = 0.25 * float(event.GetExtraLong());

	UpdateDrawInfo();
}

void tcAARBrowsePanel::OnSize(wxSizeEvent& event)
{
    wxSize size = event.GetSize();

    tc3DWindow2::OnSize(event);

    UpdateDrawInfo();

    if (scrollBar != 0)
    {
        int scrollBarWidth = scrollBar->GetSize().GetWidth();

        scrollBar->SetSize(mnWidth-scrollBarWidth-1, 2, scrollBarWidth, mnHeight-3);
    }
}


void tcAARBrowsePanel::SelectDisplayFileName(const wxString& fileName)
{
    displayFileName = fileName;

	wxCommandEvent cmd(wxEVT_COMMAND_TEXT_UPDATED, 1);    
    cmd.SetEventObject(this);
	//cmd.m_cmdString = className.c_str(); // 2.6.3
    cmd.SetString(fileName.c_str());
    AddPendingEvent(cmd);

    UpdateDrawInfo();

}





tcAARBrowsePanel::tcAARBrowsePanel(wxWindow* parent, const wxPoint& pos, const wxSize& size, 
										 const wxString& name, tc3DWindow2* graphicsHost) 
    : tc3DWindow2(parent, pos, size, name, graphicsHost),
    displayFileName(""),
	yOffset(0),
	mouseOver(false)
{
	SetBackgroundColor(Vec4(0, 0, 0, 0.01f)); // 0.01 so it doesn't get culled !?
    SetBackgroundDraw(true);

	// put gui window on top
	SetBaseRenderBin(hostParent->GetBaseRenderBin() + 10);
	wxWindow::Raise();

	SetStencilLayer(1 + hostParent->GetBaseRenderBin()/ 8); // 1+ hack to ensure different than tcDatabaseInfoPanel

	int scrollBarWidth = 16;
    SetUseRenderSurface(true, scrollBarWidth+1);


	scrollBar = new tcScrollBar(this, wxPoint(mnWidth-scrollBarWidth-1, 2), wxSize(scrollBarWidth, mnHeight-3));
	scrollBar->SetBackgroundAlpha(0.7f);
    scrollBar->SetUseRenderSurface(true);
    scrollBar->SetActive(true);

    // border is drawn in tcDatabaseViewer to work around scrollbar border issue
    SetBorderDraw(false);
    //SetBorderColor(Vec4(0.5, 0.5, 0.5, 0.5));

    BuildBrowseInfo();
}



tcAARBrowsePanel::~tcAARBrowsePanel()
{
}


