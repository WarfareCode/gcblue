/** 
**  @file tcWaypointTaskPopup.cpp 
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
#include "tcWaypointTaskPopup.h"
#include "tcLauncher.h"
#include "tcListBox.h"
#include "tcPlatformObject.h"
#include "tcSubObject.h"
#include "tcAirObject.h"
#include "tcSimState.h"
#include "tcTime.h"
#include "tcCommandQueue.h"
#include "ai/Brain.h"
#include "tcCommandQueue.h"
#include "ai/tcMissionManager.h"
#include "ai/tcMission.h"

#include <stdio.h>
#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif 


BEGIN_EVENT_TABLE(tcWaypointTaskPopup, tc3DWindow2)
    EVT_COMMAND(LP_CLOSE, wxEVT_COMMAND_BUTTON_CLICKED, tcWaypointTaskPopup::OnCloseCommand)
    EVT_COMMAND(LP_UPDATE, wxEVT_COMMAND_BUTTON_CLICKED, tcWaypointTaskPopup::OnUpdateCommand)
	EVT_COMMAND(ID_BUTTONREDRAW, wxEVT_COMMAND_BUTTON_CLICKED , tcWaypointTaskPopup::OnChildRedraw)
    EVT_COMMAND(55, wxEVT_COMMAND_TEXT_UPDATED, tcWaypointTaskPopup::OnTaskCommand)
END_EVENT_TABLE()

tc3DWindow2* tcWaypointTaskPopup::parent = 0;
tcCommandQueue* tcWaypointTaskPopup::commandInterface = 0;

/**
*
*/
void tcWaypointTaskPopup::SetParent(tc3DWindow2* par)
{
    parent = par;
}



void tcWaypointTaskPopup::AddTask(const wxString& task)
{
    for (size_t n=0; n<taskList.size(); n++)
    {
        if (taskList[n] == task.ToAscii())
        {
            return; // already exists in taskList, no dups allowed
        }
    }

	taskList.push_back(task.ToStdString());

    updateButton->SetOn(true);
}

void tcWaypointTaskPopup::RemoveTask(const wxString& task)
{
    std::vector<std::string> temp;

    for (size_t n=0; n<taskList.size(); n++)
    {
        if (taskList[n] != task.ToAscii())
        {
            temp.push_back(taskList[n]);
        }
    }

    if (taskList.size() > temp.size())
    {
        updateButton->SetOn(true);
    }

    taskList = temp;
}


/**
*
*/
void tcWaypointTaskPopup::Draw()
{
    if (CloseRequested())
    {
        DestroyWindow();
        return;
    }


    unsigned currentCount = tcTime::Get()->Get30HzCount();
    unsigned age = currentCount - birthCount;

    if (age % 1 == 0) redraw = true;

    if (!redraw) return;

    StartDraw();

    redraw = false;

    Vec4 color(1, 1, 1, 1);

    float x = 10.0f;
    float y = 10.0f;

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

    wxString s = wxString::Format("WPT %d", waypointIdx+1);
    if (missionId != -1)
    {
        s += wxString::Format(" M%03d", missionId);
    }
    DrawTextR(s.c_str(), x, y, defaultFont.get(),
            color, 10.0f, LEFT_CENTER);

    //ai::Nav::WaypointData waypoint = GetWaypoint();


	
	FinishDraw();
}




/**
* @return associated waypoint data
*/
ai::Nav::WaypointData tcWaypointTaskPopup::GetWaypoint()
{
    ai::Nav::WaypointData result;
    result.waypoint.Set(0, 0, 0);
    result.speed_kts = 0;

    tcGameObject* gameObj = simState->GetObject(platformId);
    
    if (missionId <= 0)
    {
        tcPlatformObject* obj = dynamic_cast<tcPlatformObject*>(gameObj);
        if (obj == 0) return result;

        ai::Nav* nav = obj->GetBrain()->GetNavTask();
        if (nav == 0) return result;

        const std::vector<ai::Nav::WaypointData>& waypoints = nav->GetWaypoints();

        if (waypointIdx < waypoints.size())
        {
            result = waypoints[waypointIdx];
        }

        return result;
    }
    else
    {
        tcFlightOpsObject* flightOps = dynamic_cast<tcFlightOpsObject*>(gameObj);
        tcFlightPort* flightPort = flightOps->GetFlightPort();
        if (flightPort == 0) return result;

        ai::tcMissionManager* missionManager = flightPort->GetMissionManager();
        if (missionManager == 0) return result;

        ai::tcMission* mission = missionManager->GetMission(missionId);
        if (mission == 0) return result;
        if (mission->IsLocked()) return result;

        const std::vector<ai::Nav::WaypointData>& waypoints = mission->GetRoute()->GetWaypoints();

        if (waypointIdx < waypoints.size())
        {
            result = waypoints[waypointIdx];
        }

        return result;
    }

}

/**
* Create and initialize GUI objects 
*/
void tcWaypointTaskPopup::InitControls()
{
    const float widgetAlpha = 1.0f;

    ai::Nav::WaypointData waypoint = GetWaypoint();
    if ((waypoint.waypoint.mfLat_rad == 0) && (waypoint.waypoint.mfLon_rad == 0))
    {
        return;
    }
    tcPlatformObject* obj = 
        dynamic_cast<tcPlatformObject*>(simState->GetObject(platformId));
    if (obj == 0) return;

    updateButton = new tcButton(this, wxPoint(5, 20), 
        wxSize(140, 15));
    updateButton->SetActive(true);
    updateButton->SetOn(false);
    updateButton->SetBackgroundAlpha(widgetAlpha);
    updateButton->SetCaption("Update");
    updateButton->SetCommand(LP_UPDATE);
    updateButton->SetFontSize(12.0);
    updateButton->SetSendRedraw(true);
    updateButton->SetFillColors(Vec4(0.0, 0.0, 0.0, 1.0), Vec4(1.0, 1.0, 1.0, 1.0), 
        Vec4(0.4f, 1.0, 0.4f, 1.0));


    taskEdit = new tcListBox(this, wxPoint(5, 42), wxSize(140, 15));
    taskEdit->SetActive(true);
    taskEdit->SetCommand(55);
    taskEdit->SetMaxShow(9);
    taskEdit->SetForceShow(true);

    taskList = waypoint.tasks;


    UpdateTaskList();

}

/**
* Update parent with GUI params
*/
void tcWaypointTaskPopup::UpdateParentWaypoint()
{
    ai::Nav::WaypointData waypoint = GetWaypoint();

    if ((waypoint.waypoint.mfLat_rad == 0) && (waypoint.waypoint.mfLon_rad == 0))
    {
        return; // unable to get waypoint
    }

    std::string allTasks = "'";
    for (size_t n=0; n<taskList.size(); n++)
    {
        allTasks += taskList[n];
        if ((n+1) < taskList.size())
        {
            allTasks += ",";
        }
    }
    allTasks += "'";

    if (missionId == -1)
    {
        wxString s = wxString::Format(",%d, %s", waypointIdx, allTasks.c_str());

        std::vector<long> commandId;
        commandId.push_back(platformId);
        commandInterface->AddPythonCommandGeneral("SetNavWaypointTasks", s.ToStdString(), commandId);
    }
    else
    {
        wxString s = wxString::Format(",%d, %d, %s", missionId, waypointIdx, allTasks.c_str());

        std::vector<long> commandId;
        commandId.push_back(platformId);
        commandInterface->AddPythonCommandGeneral("SetMissionWaypointTasks", s.ToStdString(), commandId);
    }

    updateButton->SetOn(false);
    taskEdit->SetCaption("");
}


/**
* Updates list box items for editing task list
*/
void tcWaypointTaskPopup::UpdateTaskList()
{
    std::string currentCaption = taskEdit->GetCaption();

    availableTasks.clear();
    wxString optionText = tcOptions::Get()->GetOptionString("WaypointTasks");
    wxString taskName = optionText.BeforeFirst(',');
    optionText = optionText.AfterFirst(',');
    while (taskName.size() > 0)
    {
        availableTasks.push_back(taskName.ToStdString());

        taskName = optionText.BeforeFirst(',');
        optionText = optionText.AfterFirst(',');
    }


    taskEdit->Clear();

    for (size_t n=0; n<availableTasks.size(); n++)
    {
        bool taskAdded = false;
        for (size_t k=0; (k<taskList.size()) && (!taskAdded); k++)
        {
            if (availableTasks[n] == taskList[k])
            {
                taskAdded = true;
            }
        }

        wxString itemString(availableTasks[n].c_str());
        if (taskAdded)
        {
            itemString += " [-]";
        }
        else
        {
            itemString += " [+]";
        }

        taskEdit->AddItem(itemString.ToStdString());
    }

    taskEdit->SetCaption(currentCaption);
}

void tcWaypointTaskPopup::OnChar(wxKeyEvent& event)
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
void tcWaypointTaskPopup::OnChildRedraw(wxCommandEvent& event)
{
    redraw = true;
}

/**
* Close and destroy popup
*/
void tcWaypointTaskPopup::OnCloseCommand(wxCommandEvent& event)
{
    DestroyWindow();
}

void tcWaypointTaskPopup::OnTaskCommand(wxCommandEvent& event)
{
    if (taskEdit == 0) return;

    int eventId = event.GetId();
    if (eventId != 55)
    {
        wxASSERT(false);
        return;
    }

    wxString itemText = event.GetString().c_str();

    wxString task = itemText.BeforeFirst('[');
    task.Trim(true);
    task.Trim(false);
    wxString s = itemText.AfterFirst('[');
    s = s.BeforeFirst(']');

    if (s == "+")
    {
        AddTask(task);
        UpdateTaskList();
    }
    else if (s == "-")
    {
        RemoveTask(task);
        UpdateTaskList();
    }
    else
    {
        wxASSERT(false); // list box items bad format
    }

}



void tcWaypointTaskPopup::OnUpdateCommand(wxCommandEvent& event)
{
    UpdateParentWaypoint();
}

/**
* A hack job for now :)
*/
void tcWaypointTaskPopup::OnLButtonDown(wxMouseEvent& event)
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
void tcWaypointTaskPopup::OnLButtonUp(wxMouseEvent& event)
{
    isLButtonDown = false;
    dragOn = false;

	ReleaseMouse();
}

/**
*
*/
void tcWaypointTaskPopup::OnMouseMove(wxMouseEvent& event)
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
		//SetUserPosition(launcherIdx, pos);
    }
}


void tcWaypointTaskPopup::OnRButtonDown(wxMouseEvent& event)
{
    // do nothing, but keep event from getting passed upward
}



/**
* @param id Id of platform with launcher to control
* @param idx Launcher idx on platform
*/
tcWaypointTaskPopup::tcWaypointTaskPopup(long platformId_, long missionId_, unsigned int waypointIdx_, const wxPoint& pos)
            : tc3DWindow2(parent, pos, wxSize(150, 200), "WaypointEditPopup", parent),
   platformId(platformId_),
   missionId(missionId_),
   waypointIdx(waypointIdx_),
   redraw(true),
   dragOn(false)
{
    SetBaseRenderBin(parent->GetBaseRenderBin() + 10);
	tc3DWindow2::MoveToTop();

    birthCount = tcTime::Get()->Get30HzCount();

    simState = tcSimState::Get();
    wxASSERT(simState);
    commandInterface = tcCommandQueue::Get();

    const int closeButtonSize = 12;
    closeButton = new tcButton(this, wxPoint(mnWidth - closeButtonSize, 0), 
        wxSize(closeButtonSize, closeButtonSize));
    closeButton->SetActive(true);
    closeButton->SetBackgroundAlpha(1.0);
    closeButton->SetCaption("");
    closeButton->SetCommand(LP_CLOSE);
    closeButton->LoadImages("close.png", "close.png", "close.png", "close.png");
    closeButton->SetSendRedraw(true);

    InitControls();

    SetActive(true);

    SetBorderDraw(true);
}

tcWaypointTaskPopup::~tcWaypointTaskPopup() 
{

}

