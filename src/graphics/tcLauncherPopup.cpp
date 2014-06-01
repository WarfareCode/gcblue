/** 
**  @file tcLauncherPopup.cpp 
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

#include "wxcommands.h"
#include "tcButton.h"
#include "tcLauncherPopup.h"
#include "tcLauncher.h"
#include "tcNumberWidget.h"
#include "tcPlatformObject.h"
#include "tcSimState.h"
#include "tcTime.h"
#include "tcCommandQueue.h"
#include "tcSonarDBObject.h"
#include "tcTorpedoDBObject.h"

#include <stdio.h>
#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif 


BEGIN_EVENT_TABLE(tcLauncherPopup, tc3DWindow2)
    EVT_COMMAND(LP_CLOSE, wxEVT_COMMAND_BUTTON_CLICKED, tcLauncherPopup::OnCloseCommand)
    EVT_COMMAND(LP_LAUNCH, wxEVT_COMMAND_BUTTON_CLICKED, tcLauncherPopup::OnLaunchCommand)
    EVT_COMMAND(LP_SETDATUM, wxEVT_COMMAND_BUTTON_CLICKED, tcLauncherPopup::OnDatumCommand)
	EVT_COMMAND(LP_TOGGLEPASSIVE, wxEVT_COMMAND_BUTTON_CLICKED, tcLauncherPopup::OnTogglePassiveCommand)
	EVT_COMMAND(ID_BUTTONREDRAW, wxEVT_COMMAND_BUTTON_CLICKED , tcLauncherPopup::OnChildRedraw)
END_EVENT_TABLE()

tc3DWindow2* tcLauncherPopup::parent = 0;
wxPoint tcLauncherPopup::userPositions[MAX_LAUNCHERS];
bool tcLauncherPopup::userPositionsInitialized = false;
std::map<long, bool> tcLauncherPopup::registry;

const wxPoint& tcLauncherPopup::GetUserPosition(unsigned int idx)
{
	if (!userPositionsInitialized)
	{
		for (unsigned int k=0; k<MAX_LAUNCHERS; k++)
		{
			userPositions[k] = wxPoint(220 + (k%3)*210, 200 + 155*(k/3));
		}
		userPositionsInitialized = true;
	}

	if (idx >= MAX_LAUNCHERS)
	{
		fprintf(stderr, "tcLauncherPopup::GetUserPosition - Idx out of range\n");
		return userPositions[0];
	}
	else
	{
		return userPositions[idx];
	}
}

/**
*
*/
void tcLauncherPopup::SetParent(tc3DWindow2* par)
{
    parent = par;
}

void tcLauncherPopup::SetUserPosition(unsigned int idx, const wxPoint& pos)
{
	if (idx >= MAX_LAUNCHERS)
	{
		wxASSERT(false);
		return;
	}
	userPositions[idx] = pos;
}



bool tcLauncherPopup::ForceClose(long id, unsigned idx)
{
    long key = GetKey(id, idx);

    std::map<long, bool>::iterator iter = 
        registry.find(key);
    if (iter != registry.end())
    {
        iter->second = true;
        return true;
    }
    else
    {
        return false; // not found
    }
}

bool tcLauncherPopup::GetForceClose(long id, unsigned idx)
{
    long key = GetKey(id, idx);

    std::map<long, bool>::iterator iter = 
        registry.find(key);
    if (iter != registry.end())
    {
        return iter->second;
    }
    else
    {
        fprintf(stderr, "tcLauncherPopup::GetForceClose - not in registry!\n");
        wxASSERT(false);
        return false; // not found
    }
}

long tcLauncherPopup::GetKey(long id, unsigned idx)
{
    return long((id << 4) + idx);
}

void tcLauncherPopup::RegisterWindow(long id, unsigned idx)
{
    long key = GetKey(id, idx);

    std::map<long, bool>::iterator iter = 
        registry.find(key);

    if (iter != registry.end())
    {
        fprintf(stderr, "tcLauncherPopup::RegisterWindow - already exists!\n");
        wxASSERT(false);
        return;
    }
    
    registry[key] = false;
}

void tcLauncherPopup::UnregisterWindow(long id, unsigned idx)
{
    long key = GetKey(id, idx);

    std::map<long, bool>::iterator iter = 
        registry.find(key);

    if (iter == registry.end())
    {
        fprintf(stderr, "tcLauncherPopup::UnregisterWindow - does not exist!\n");
        wxASSERT(false);
        return;
    }

    registry.erase(iter);
}


void tcLauncherPopup::UnregisterAll()
{
    registry.clear();
}

bool tcLauncherPopup::WindowExists(long id, unsigned idx)
{
    long key = GetKey(id, idx);

    std::map<long, bool>::iterator iter = 
        registry.find(key);

    return (iter != registry.end());
}



/**
*
*/
void tcLauncherPopup::Draw()
{
    if (GetForceClose(platformId, launcherIdx)) DestroyWindow();


    unsigned currentCount = tcTime::Get()->Get30HzCount();
    unsigned age = currentCount - birthCount;

    if (age % 1 == 0) redraw = true;

    if (!redraw) return;

    StartDraw();

    UpdateTorpedoLauncher();

    redraw = false;

    Vec4 color(1, 1, 1, 1);

    float x = 10.0f;
    float y = 12.0f;

    
    tcPlatformObject* obj = 
        dynamic_cast<tcPlatformObject*>(simState->GetObject(platformId));

    DrawRectangleR(0, 0, float(mnWidth), float(mnHeight), 
        Vec4(0, 0, 0, 0.6f), FILL_ON);

    if (!obj)
    {
        DrawTextR("CONTROL UNAVAILABLE", x, y, defaultFont.get(),
            color, fontSize, CENTER_CENTER);
	    FinishDraw();
        return;
    }

    tcLauncher* launcher = obj->GetLauncher(launcherIdx);
    if (!launcher)
    {
        DrawTextR("LAUNCHER ERROR", x, y, defaultFont.get(),
            color, fontSize, CENTER_CENTER);
	    FinishDraw();
        return;
    }

    wxString s;
    wxSize textSize;

    s = wxString::Format("%s : %s x %d\n", launcher->displayName.c_str(),
        launcher->GetChildClassName().c_str(), launcher->mnCurrent);

    DrawTextR(s.c_str(), x, y, defaultFont.get(),
        color, fontSize, LEFT_CENTER);

    
    if (launcher->GetLauncherStatus() == tcLauncher::LAUNCHER_READY)
    {
        launchButton->SetFillColors(Vec4(0.2f, 0.5f, 0.2f, 1.0f), Vec4(0.4f, 1.0f, 0.4f, 1.0f), 
            Vec4(0.4f, 1.0f, 0.4f, 1.0f));
    }
    else
    {
        launchButton->SetFillColors(Vec4(0.5f, 0.2f, 0.2f, 1.0f), Vec4(1.0f, 0.4f, 0.4f, 1.0f), 
            Vec4(1.0f, 0.4f, 0.4f, 1.0f));
    }

	if (launcher->usePassive)
	{
		activePassiveButton->SetCaption("Passive");
	}
	else
	{
		activePassiveButton->SetCaption("Active");
	}
	
	FinishDraw();
}

/**
* @return associated launcher or NULL if error
*/
tcLauncher* tcLauncherPopup::GetLauncher()
{
    tcPlatformObject* obj = 
        dynamic_cast<tcPlatformObject*>(simState->GetObject(platformId));

    if (!obj)
    {
        return 0;
    }
    else
    {
        return obj->GetLauncher(launcherIdx);
    }
}

/**
* Create and initialize GUI objects for torpedo control
*/
void tcLauncherPopup::InitTorpedoControls()
{
    const int widgetWidth = 48;
    const int widgetHeight = 14;
    const float widgetFontSize = 14.0;
    const float widgetAlpha = 1.0f;
    int x = 90;
    int y = 20;

    tcLauncher* launcher = GetLauncher();
    wxASSERT(launcher);
    if (!launcher) return;


    launchButton = new tcButton(this, wxPoint(mnWidth - 40, 20), 
        wxSize(widgetHeight, widgetHeight));
    launchButton->SetActive(true);
    launchButton->SetBackgroundAlpha(widgetAlpha);
    launchButton->SetCaption("L");
    launchButton->SetCommand(LP_LAUNCH);
    launchButton->SetFontSize(12.0);
    launchButton->SetSendRedraw(true);


    selectDatumButton = new tcButton(this, wxPoint(mnWidth - 55, 20), 
        wxSize(widgetHeight, widgetHeight));
    selectDatumButton->SetActive(true);
    selectDatumButton->SetBackgroundAlpha(widgetAlpha);
    selectDatumButton->SetCaption("D");
    selectDatumButton->SetCommand(LP_SETDATUM);
    selectDatumButton->SetFontSize(12.0);
    selectDatumButton->SetSendRedraw(true);


    runToEnableAdjust = new tcNumberWidget<float>(runToEnable, this, wxPoint(x, y), 
        wxSize(widgetWidth, widgetHeight));
    runToEnableAdjust->SetCaption("Run dist");
    runToEnableAdjust->SetFontSize(widgetFontSize);
    runToEnableAdjust->SetActive(true);
    runToEnableAdjust->SetSendRedraw(true);
    runToEnable = launcher->runToEnable_m;
	runToEnable_prev = runToEnable;
    y += widgetHeight + 5;

    depthAdjust = new tcNumberWidget<float>(depth, this, wxPoint(x, y), 
        wxSize(widgetWidth, widgetHeight));
    depthAdjust->SetCaption("Depth");
    depthAdjust->SetFontSize(widgetFontSize);
    depthAdjust->SetActive(true);
    depthAdjust->SetSendRedraw(true);
    depth = launcher->runDepth_m;
    y += widgetHeight + 5;

    speedAdjust = new tcNumberWidget<float>(speed, this, wxPoint(x, y), 
        wxSize(widgetWidth, widgetHeight));
    speedAdjust->SetCaption("Speed");
    speedAdjust->SetFontSize(widgetFontSize);
    speedAdjust->SetActive(true);
    speedAdjust->SetSendRedraw(true);
    speedAdjust->SetBounds(0, 99);
    speed = launcher->preEnableSpeed_kts;
    y += widgetHeight + 5;

    ceilingAdjust = new tcNumberWidget<float>(ceiling, this, wxPoint(x, y), 
        wxSize(widgetWidth, widgetHeight));
    ceilingAdjust->SetCaption("Ceiling");
    ceilingAdjust->SetFontSize(widgetFontSize);
    ceilingAdjust->SetActive(true);
    ceilingAdjust->SetSendRedraw(true);
    ceiling = launcher->ceiling_m;
    y += widgetHeight + 5;

    floorAdjust = new tcNumberWidget<float>(floor, this, wxPoint(x, y), 
        wxSize(widgetWidth, widgetHeight));
    floorAdjust->SetCaption("Floor");
    floorAdjust->SetFontSize(widgetFontSize);
    floorAdjust->SetActive(true);
    floorAdjust->SetSendRedraw(true);
    floor = launcher->floor_m;
    y += widgetHeight + 5;


    activePassiveButton = new tcButton(this, wxPoint(x, y), 
        wxSize(widgetWidth, widgetHeight));
    activePassiveButton->SetActive(true);
    activePassiveButton->SetBackgroundAlpha(widgetAlpha);
    activePassiveButton->SetCaption("Pass");
    activePassiveButton->SetCommand(LP_TOGGLEPASSIVE);
    activePassiveButton->SetFontSize(12.0);
    activePassiveButton->SetSendRedraw(true);
	activePassiveButton->SetFillColors(Vec4(0.0, 0.0, 0.0, 1.0), Vec4(1.0, 1.0, 1.0, 1.0), 
        Vec4(0.4f, 1.0, 0.4f, 1.0));

	isPassive = launcher->usePassive;
}

/**
* Update torpedo launcher with GUI params
*/
void tcLauncherPopup::UpdateTorpedoLauncher()
{
    tcLauncher* launcher = GetLauncher();
    wxASSERT(launcher);
	if (launcher == 0) return;

    if (tcTorpedoDBObject* torpedoData = dynamic_cast<tcTorpedoDBObject*>(launcher->GetChildDatabaseObject()))
    {
        speedAdjust->SetBounds(0, torpedoData->maxSpeed_kts);
    }
    else
    {
        speedAdjust->SetBounds(0, 99.0f);
    }

	// use launcher value if local value hasn't changed to pick up changes due to
	// datum changes
	if (runToEnable != runToEnable_prev)
	{
		launcher->runToEnable_m = runToEnable;
	}
	else
	{
		runToEnable = launcher->runToEnable_m;
	}
	runToEnable_prev = runToEnable;
    
    launcher->runDepth_m = depth;
    launcher->preEnableSpeed_kts = speed;
    launcher->ceiling_m = ceiling;
    launcher->floor_m = floor;
    launcher->usePassive = isPassive;

	activePassiveButton->SetOn(!isPassive);
}

void tcLauncherPopup::OnChar(wxKeyEvent& event)
{
    int nChar = event.GetKeyCode();


    switch(nChar)
    {
    case WXK_ESCAPE:
        DestroyWindow(); //destroy = true;
        break;
    default:
        event.Skip();
        break;
    }
}

/**
* Intended to be overrided to intercept command events from GUI
* objects within the window.
* This routine intercepts the ID_BUTTONREDRAW event.
*/
void tcLauncherPopup::OnChildRedraw(wxCommandEvent& event)
{
    redraw = true;
}

/**
* Close and destroy popup
*/
void tcLauncherPopup::OnCloseCommand(wxCommandEvent& event)
{
    DestroyWindow();
}


void tcLauncherPopup::OnDatumCommand(wxCommandEvent& event)
{
	static std::vector<long> idVect;

    redraw = true;

    if (tcLauncher* launcher = GetLauncher())
    {
		idVect.clear();
		idVect.push_back(platformId);
        tcCommandQueue::Get()->GetUserInputForID("SetDatum", "Datum", 
            idVect, launcherIdx);
    }
}

void tcLauncherPopup::OnLaunchCommand(wxCommandEvent& event)
{
    redraw = true;

    if (tcLauncher* launcher = GetLauncher())
    {
        if (launcher->GetLauncherStatus() == tcLauncher::LAUNCHER_READY)
        {
			launcher->SetLaunch(1);
        }
    }
}

/**
* A hack job for now :)
*/
void tcLauncherPopup::OnLButtonDown(wxMouseEvent& event)
{
    wxPoint pos = event.GetPosition();

    isLButtonDown = true;
    if ((pos.y <= 10) || (pos.y >= mnHeight))
    {
        dragOn = true;
        // position in parent's frame of mouse pointer
        dragPoint = wxPoint(mrectWindow.GetLeft() + pos.x, mrectWindow.GetBottom() + pos.y);

		CaptureMouse();
        return;
    }

}

/**
*
*/
void tcLauncherPopup::OnLButtonUp(wxMouseEvent& event)
{
    isLButtonDown = false;
    dragOn = false;

	ReleaseMouse();
}

/**
*
*/
void tcLauncherPopup::OnMouseMove(wxMouseEvent& event)
{
    if (!dragOn) return;

    wxPoint pos = event.GetPosition();

    // position in parent's frame of mouse pointer
    wxPoint current = wxPoint(mrectWindow.GetLeft() + pos.x, mrectWindow.GetBottom() + pos.y);
    if (current != dragPoint)
    {
        wxPoint delta = current - dragPoint;
		int xmove = mrectWindow.GetLeft() + delta.x;
		int ymove = mrectWindow.GetTop() + delta.y;
        tc3DWindow2::MoveWindow(xmove, ymove);
        dragPoint = current;

		wxPoint pos(xmove, ymove);
		SetUserPosition(launcherIdx, pos);
    }
}


void tcLauncherPopup::OnRButtonDown(wxMouseEvent& event)
{
    // do nothing, but keep event from getting passed upward
}

/**
* Applies to torpedoes only
*/
void tcLauncherPopup::OnTogglePassiveCommand(wxCommandEvent& event)
{
    tcLauncher* launcher = GetLauncher();
	if (launcher == 0)
	{
		wxASSERT(false);
		return;
	}
	if (tcTorpedoDBObject* torpedoData = dynamic_cast<tcTorpedoDBObject*>(launcher->GetChildDatabaseObject()))
    {
		tcSonarDBObject* sonarData = torpedoData->GetSeekerDBObj();
		if (sonarData == 0)
		{
			wxASSERT(false);
			return;
		}
		isPassive = !isPassive;

		if (isPassive && !sonarData->isPassive)
		{
			isPassive = false;
		}
		if (!isPassive && sonarData->isPassive && !sonarData->isActive)
		{
			isPassive = true;
		}

		activePassiveButton->SetOn(!launcher->usePassive);
	}
}

/**
* @param id Id of platform with launcher to control
* @param idx Launcher idx on platform
*/
tcLauncherPopup::tcLauncherPopup(long id, unsigned idx, const wxPoint& pos)
            : tc3DWindow2(parent, pos, wxSize(200, 150), "LauncherPopupControl", parent),
   platformId(id),
   launcherIdx(idx),
   redraw(true),
   dragOn(false)
{
    SetBaseRenderBin(parent->GetBaseRenderBin() + 10);
	tc3DWindow2::MoveToTop();

    birthCount = tcTime::Get()->Get30HzCount();

    simState = tcSimState::Get();
    wxASSERT(simState);

    const int closeButtonSize = 12;
    closeButton = new tcButton(this, wxPoint(mnWidth - closeButtonSize, 0), 
        wxSize(closeButtonSize, closeButtonSize));
    closeButton->SetActive(true);
    closeButton->SetBackgroundAlpha(1.0);
    closeButton->SetCaption("");
    closeButton->SetCommand(LP_CLOSE);
    closeButton->LoadImages("close.png", "close.png", "close.png", "close.png");
    closeButton->SetSendRedraw(true);


    InitTorpedoControls();

    RegisterWindow(id, idx);

    SetActive(true);

    SetBorderDraw(true);
}

tcLauncherPopup::~tcLauncherPopup() 
{
    UnregisterWindow(platformId, launcherIdx);
}

