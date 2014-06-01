/**
**  @file tcDatabaseBrowsePanel.cpp
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

#include "tcDatabaseBrowsePanel.h"
#include "tv_types.h"
#include "tcTexture2D.h"
#include "wxcommands.h"
#include "common/tinyxml.h"
#include "tcDatabase.h"
#include "tcDatabaseObject.h"
#include "tcDatabaseIterator.h"
#include "tcScrollBar.h"
#include "tcSound.h"
#include "tc3DViewer.h"

#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif 



BEGIN_EVENT_TABLE(tcDatabaseBrowsePanel, tc3DWindow2)
    EVT_COMMAND(-1, wxEVT_COMMAND_SCROLLBAR_UPDATED, tcDatabaseBrowsePanel::OnScrollbarUpdated)
END_EVENT_TABLE()


bool BrowseSortPredicate(const tcDatabaseBrowsePanel::BrowseItem& a, const tcDatabaseBrowsePanel::BrowseItem& b)
{
    return (a.displayName.compare(b.displayName) < 0);
}


/**
* Updates browse info data based on classificationMask
* Should be called after changing classificationMask
*/
void tcDatabaseBrowsePanel::BuildBrowseInfo()
{
    database::tcDatabase* database = database::tcDatabase::Get();

    std::vector<database::tcDatabase::RecordSummary> recordSummary;
    std::vector<database::tcDatabase::RecordSummary> recordSummary2;
    bool filterByClassification = false;

    switch (classificationMask)
    {
    case PTYPE_SURFACE:
        recordSummary = database->GetTableSummary("ship");
        break;
    case PTYPE_SUBMARINE:
        recordSummary = database->GetTableSummary("sub");
        break;
    case PTYPE_FIXEDWING:
        recordSummary = database->GetTableSummary("air");
        recordSummary2 = database->GetTableSummary("simpleair");
        recordSummary.insert(recordSummary.end(), recordSummary2.begin(), recordSummary2.end());
        filterByClassification = true;
        break;
    case PTYPE_HELO:
        recordSummary = database->GetTableSummary("simpleair");
        filterByClassification = true;
        break;
    case PTYPE_GROUND:
        recordSummary = database->GetTableSummary("ground");
        break;
    case PTYPE_MISSILE:
        recordSummary = database->GetTableSummary("missile");
        recordSummary2 = database->GetTableSummary("ballistic_missile");
        recordSummary.insert(recordSummary.end(), recordSummary2.begin(), recordSummary2.end());
        filterByClassification = true;
        break;
    case PTYPE_TORPEDO:
        recordSummary = database->GetTableSummary("torpedo");
        break;
    case PTYPE_BALLISTIC:
        recordSummary = database->GetTableSummary("ballistic");
        break;
    }


    std::vector<BrowseItem> sortedRecords;

    if (filterByClassification)
    {
        for (size_t n=0; n<recordSummary.size(); n++)
        {
            if (recordSummary[n].classificationId == classificationMask)
            {
                BrowseItem item;
                item.className = wxString(recordSummary[n].databaseClass.c_str());
                item.displayName = wxString(recordSummary[n].databaseDisplayClass.c_str());

                sortedRecords.push_back(item);
            }
        }
    }
    else
    {
        for (size_t n=0; n<recordSummary.size(); n++)
        {
            BrowseItem item;
            item.className = wxString(recordSummary[n].databaseClass.c_str());
            item.displayName = wxString(recordSummary[n].databaseDisplayClass.c_str());

            sortedRecords.push_back(item);
        }
    }

    std::sort(sortedRecords.begin(), sortedRecords.end(), BrowseSortPredicate);
//    sortedRecords.Sort();

	yOffset = 0;

    browseInfo.clear();

    // database::tcDatabaseIterator iter(classificationMask); // old way, only returns currently loaded db

    for (size_t n=0; n<sortedRecords.size(); n++)
    {
        BrowseItem item;

        item = sortedRecords[n];
        //item.className = sortedRecords[n].c_str();

        browseInfo.push_back(item);
    }

}

const std::string& tcDatabaseBrowsePanel::GetDisplayClass() const
{
    return displayClassName;
}

/**
* 
*/
bool tcDatabaseBrowsePanel::ProcessMouseClick(const wxPoint& pos)
{
	std::vector<BrowseItem>& info = browseInfo;

	for (size_t n=0; n < info.size(); ++n)
	{
		wxRect r(info[n].drawBox.x, info[n].drawBox.y, 
					info[n].drawBox.width, info[n].drawBox.height);

		if (r.Contains(pos))
		{
            SelectDisplayClass(info[n].className);
			return true;
		}
	}

	return false;
}

void tcDatabaseBrowsePanel::SetClassificationMask(unsigned int mask)
{
    if (mask == classificationMask) return;

    classificationMask = mask;

    BuildBrowseInfo();
    UpdateDrawInfo();

}

void tcDatabaseBrowsePanel::ClearMouseOver()
{
	std::vector<BrowseItem>& info = browseInfo;

	for (size_t n=0; n < info.size(); ++n)
	{
		BrowseItem& item = info[n];

		if (item.className == displayClassName)
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
void tcDatabaseBrowsePanel::UpdateDrawInfo()
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

		if (item.className == displayClassName)
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
void tcDatabaseBrowsePanel::Draw()
{
    StartDraw();

    for (size_t n=0; n<browseInfo.size(); n++)
    {
        BrowseItem& item = browseInfo[n];

        DrawTextR(item.displayName.c_str(), item.drawBox.x, 
            item.drawBox.y + 0.5f*item.drawBox.height, defaultFont.get(), 
            item.color, 16.0f, LEFT_CENTER);
    }

	FinishDraw();
}




/**
 *
 */
void tcDatabaseBrowsePanel::OnMouseMove(wxMouseEvent& event) 
{
	mousePosition = event.GetPosition();

	UpdateDrawInfo();
}

/**
 *
 */
void tcDatabaseBrowsePanel::OnLButtonDown(wxMouseEvent& event) 
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


void tcDatabaseBrowsePanel::OnEnterWindow(wxMouseEvent& event)
{
	mouseOver = true;
    SetFocus(); // to receive mousewheel events
}

void tcDatabaseBrowsePanel::OnLeaveWindow(wxMouseEvent& event)
{
	ClearMouseOver();
	mouseOver = false;

}

void tcDatabaseBrowsePanel::OnMouseWheel(wxMouseEvent& event)
{
    wxASSERT(scrollBar != 0);

    scrollBar->OnMouseWheel(event);
}


void tcDatabaseBrowsePanel::OnScrollbarUpdated(wxCommandEvent& event)
{
    yOffset = 0.25 * float(event.GetExtraLong());

	UpdateDrawInfo();
}

void tcDatabaseBrowsePanel::OnSize(wxSizeEvent& event)
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


void tcDatabaseBrowsePanel::SelectDisplayClass(const std::string& className)
{
    displayClassName = className;

	wxCommandEvent cmd(wxEVT_COMMAND_TEXT_UPDATED, 1);    
    cmd.SetEventObject(this);
	//cmd.m_cmdString = className.c_str(); // 2.6.3
    cmd.SetString(className.c_str());
    AddPendingEvent(cmd);

}





tcDatabaseBrowsePanel::tcDatabaseBrowsePanel(wxWindow* parent, const wxPoint& pos, const wxSize& size, 
										 const wxString& name, tc3DWindow2* graphicsHost) 
    : tc3DWindow2(parent, pos, size, name, graphicsHost),
    classificationMask(0),
    displayClassName(""),
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

    // border is drawn in tcDatabaseViewer to work around scrollbar border issue
    SetBorderDraw(false);
    //SetBorderColor(Vec4(0.5, 0.5, 0.5, 0.5));
}



tcDatabaseBrowsePanel::~tcDatabaseBrowsePanel()
{
}


