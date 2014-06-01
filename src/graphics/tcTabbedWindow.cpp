/**  
**  @file tcTabbedWindow.cpp
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

#include "tcTabbedWindow.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif 



void tcTabbedWindow::AddTab(const std::string& tabName)
{
    tabs.push_back(tabName);
}

void tcTabbedWindow::ClearTabs()
{
    tabs.clear();
    currentTab = "";
}

const std::vector<std::string>& tcTabbedWindow::GetTabList() const
{
    return tabs;
}

const std::string& tcTabbedWindow::GetTab() const
{
    return currentTab;
}

size_t tcTabbedWindow::GetTabCount() const
{
    return tabs.size();
}


float tcTabbedWindow::GetTabWidth() const
{
	return tabWidth;
}

void tcTabbedWindow::SetTab(const std::string& s)
{
    if (currentTab == s) return; // already set

    bool matched = false;
    for (size_t k=0; (k<tabs.size())&&(!matched); k++)
    {
        if (tabs[k] == s) matched = true;
    }

    if (!matched)
    {
        wxASSERT(false);
        fprintf(stderr, "tcTabbedWindow::SetTab - not found\n");
        return;
    }

    currentTab = s;
}

void tcTabbedWindow::SetTabWidth(float w)
{
	tabWidth = w;
}



tcTabbedWindow::tcTabbedWindow()
: tabWidth(70.0f)
{
}

tcTabbedWindow::~tcTabbedWindow()
{
}