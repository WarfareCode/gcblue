/**  
**  @file tcTabHeader.cpp
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

#include "tcTabHeader.h"
#include "wxcommands.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif 


void tcTabHeader::Draw()
{
    StartDraw();

    size_t nTabs = tabs.size();

    float x = 0;
//    float y = 0;

    const Vec4 onTextColor(1.0f, 1.0f, 0.7f, 1.0f);
    const Vec4 offTextColor(0.6f, 0.6f, 0.6f, 1.0f);
    const Vec4 overFillColor(0.4f, 0.4f, 0.2f, 0.7f);
    const Vec4 offFillColor(0, 0, 0, 0.7f);

    for (size_t k=0; k<nTabs; k++)
    {
        if (k != mouseOverTab)
        {
		    DrawRectangle(tabRect[k], offFillColor, FILL_ON);
        }
        else
        {
		    DrawRectangle(tabRect[k], overFillColor, FILL_ON);
        }

        if (tabs[k] != activeTab.c_str())
        {
		    DrawText(tabs[k].c_str(), tabRect[k].XCenter(), tabRect[k].YCenter(), boldFont.get(), 
				    offTextColor, fontSize, CENTER_CENTER);
        }
        else
        {
            DrawText(tabs[k].c_str(), tabRect[k].XCenter(), tabRect[k].YCenter(), boldFont.get(), 
				    onTextColor, fontSize, CENTER_CENTER);
        }

        x += tabWidth + 10.0f;
    }


	FinishDraw();

}

void tcTabHeader::ClearTabs()
{
    tabs.clear();
}

void tcTabHeader::OnLButtonDown(wxMouseEvent& event)
{
    wxPoint pos = event.GetPosition();
    
    for (size_t k=0; k<tabs.size(); k++)
    {
        if (tabRect[k].ContainsPoint(float(pos.x), float(pos.y)))
        {
            wxCommandEvent command(wxEVT_COMMAND_BUTTON_CLICKED, ID_TABCLICKED) ;    
            command.SetEventObject(this);
            command.SetString(tabs[k].c_str());
            AddPendingEvent(command);
            return;
        }
    }
}

void tcTabHeader::OnLeaveWindow(wxMouseEvent& event)
{
    mouseOverTab = 999; // clear mouseOverTab
}

void tcTabHeader::OnMouseMove(wxMouseEvent& event)
{
    wxPoint pos = event.GetPosition();
    
    for (size_t k=0; k<tabs.size(); k++)
    {
        if (tabRect[k].ContainsPoint(float(pos.x), float(pos.y)))
        {
            mouseOverTab = k;
            return;
        }
    }

    mouseOverTab = 999;
}

void tcTabHeader::SetActiveTab(const std::string& s)
{
    if (activeTab == s) return;

    bool matched = false;
    for (size_t k=0; (k<tabs.size())&&(!matched); k++)
    {
        if (tabs[k] == s) matched = true;
    }

    if (!matched)
    {
        wxASSERT(false);
        return;
    }

    activeTab = s;
}

void tcTabHeader::SetTabs(const std::vector<std::string>& tabList)
{
    tabRect.clear();
    tabs = tabList;
    
    float x = 0;
//    float y = 0;

    tcRect r;
    r.top = float(mnHeight);
    r.bottom = 0;

    for (size_t k=0; k<tabs.size(); k++)
    {
        r.left = x;
        r.right = r.left + tabWidth;

        tabRect.push_back(r);

        x += tabWidth + 5.0f;
    }

}

void tcTabHeader::SetTabWidth(float w)
{
	tabWidth = w;

	SetTabs(tabs);
}

tcTabHeader::tcTabHeader(wxWindow *parent, 
                         const wxPoint& pos,
                         const wxSize& size, 
                         const wxString& name) 
                         : tc3DWindow2(parent, pos, size, name),
    tabWidth(70.0f),
    mouseOverTab(999)
{

    fontSize = 14.0f;
}

tcTabHeader::~tcTabHeader()
{
}