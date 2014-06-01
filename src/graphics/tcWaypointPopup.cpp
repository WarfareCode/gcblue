/** 
**  @file tcWaypointPopup.cpp 
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
#include "tcWaypointPopup.h"
#include "tcLauncher.h"
#include "tcNumberWidget.h"
#include "tcListBox.h"
#include "tcWaypointTaskPopup.h"
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
#include "tcTacticalMapView.h"

#include <stdio.h>
#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif 


BEGIN_EVENT_TABLE(tcWaypointPopup, tc3DWindow2)
    EVT_COMMAND(LP_CLOSE, wxEVT_COMMAND_BUTTON_CLICKED, tcWaypointPopup::OnCloseCommand)
    EVT_COMMAND(LP_UPDATE, wxEVT_COMMAND_BUTTON_CLICKED, tcWaypointPopup::OnUpdateCommand)
    EVT_COMMAND(ID_BUTTONREDRAW, wxEVT_COMMAND_BUTTON_CLICKED , tcWaypointPopup::OnChildRedraw)
    EVT_COMMAND(55, wxEVT_COMMAND_BUTTON_CLICKED, tcWaypointPopup::OnShowTaskEditCommand)
    EVT_COMMAND(WP_SETANCHOR, wxEVT_COMMAND_BUTTON_CLICKED, tcWaypointPopup::OnSetAnchor)
    EVT_COMMAND(WP_TOGGLEANCHORMODE, wxEVT_COMMAND_BUTTON_CLICKED, tcWaypointPopup::OnToggleAnchorMode)
    EVT_COMMAND(WP_CLEARANCHOR, wxEVT_COMMAND_BUTTON_CLICKED, tcWaypointPopup::OnClearAnchor)
    EVT_COMMAND(WP_PREVWAYPOINT, wxEVT_COMMAND_BUTTON_CLICKED, tcWaypointPopup::OnPrevWaypoint)
    EVT_COMMAND(WP_NEXTWAYPOINT, wxEVT_COMMAND_BUTTON_CLICKED, tcWaypointPopup::OnNextWaypoint)
    EVT_COMMAND(WP_INSERTWAYPOINT, wxEVT_COMMAND_BUTTON_CLICKED, tcWaypointPopup::OnInsertWaypoint)
    EVT_COMMAND(WP_DELETEWAYPOINT, wxEVT_COMMAND_BUTTON_CLICKED, tcWaypointPopup::OnDeleteWaypoint)
END_EVENT_TABLE()

tc3DWindow2* tcWaypointPopup::parent = 0;
tcCommandQueue* tcWaypointPopup::commandInterface = 0;
tcTacticalMapView* tcWaypointPopup::tacticalMap = 0;
/**
*
*/
void tcWaypointPopup::SetParent(tc3DWindow2* par)
{
    parent = par;

    tcWaypointTaskPopup::SetParent(par);
}




/**
*
*/
void tcWaypointPopup::Draw()
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

    UpdateButtonState();

    StartDraw();

    redraw = false;

    Vec4 color(1, 1, 1, 1);

    float x = 10.0f;
    float y = 10.0f;

    tcPlatformObject* obj = 
        dynamic_cast<tcPlatformObject*>(simState->GetObject(platformId));

    DrawRectangleR(0, 0, float(mnWidth), float(mnHeight), 
        Vec4(0, 0, 0, 0.6f), FILL_ON);

    bool dataUpdated = IsDataUpdated();

    if (dataUpdated)
    {
        updateButton->SetOffColor(Vec4(0.2f, 0.6f, 0.2f, 1.0f));
    }
    else
    {
        updateButton->SetOffColor(Vec4(0, 0, 0, 1));
        if ((age % 4) == 0)
        {
            UpdateFromParent();
        }
    }

    if (!obj)
    {
        DrawTextR("CONTROL UNAVAILABLE", x, y, defaultFont.get(),
            color, fontSize, CENTER_CENTER);
	    FinishDraw();
        return;
    }

    wxString s = wxString::Format("EDIT WAYPOINT %d", waypointIdx+1);
    if (missionId != -1)
    {
        s += wxString::Format("\nM%03d", missionId);
        y += 3.0f;
    }
    DrawTextR(s.c_str(), x, y, defaultFont.get(),
            color, 10.0f, LEFT_CENTER);

    //ai::Nav::WaypointData waypoint = GetWaypoint();

    if ((referenceMode != 0) && (referencePlatform != -1))
    {
        if (tcGameObject* obj = tcSimState::Get()->GetObject(referencePlatform))
        {
            DrawTextInRectR(obj->mzUnit.c_str(), referenceUnitBox, defaultFont.get(), color, 10.0f, LEFT_CENTER);
        }
    }

	
    FinishDraw();
}

/**
* @return route of parent or 0 if error
*/
ai::Route* tcWaypointPopup::GetParentRoute()
{
    tcGameObject* gameObj = simState->GetObject(platformId);
    
    if (missionId == -1)
    {
        tcPlatformObject* obj = dynamic_cast<tcPlatformObject*>(gameObj);
        if (obj == 0) return 0;

        ai::Nav* nav = obj->GetBrain()->GetNavTask();
        return nav;
    }
    else
    {
        tcFlightOpsObject* flightOps = dynamic_cast<tcFlightOpsObject*>(gameObj);
        tcFlightPort* flightPort = flightOps->GetFlightPort();
        if (flightPort == 0) return 0;

        ai::tcMissionManager* missionManager = flightPort->GetMissionManager();
        if (missionManager == 0) return 0;

        ai::tcMission* mission = missionManager->GetMission(missionId);
        if (mission == 0) return 0;

        return mission->GetRoute();
    }
}


/**
* @return associated waypoint data
*/
ai::Nav::WaypointData tcWaypointPopup::GetWaypoint()
{
    ai::Nav::WaypointData result;
    result.waypoint.Set(0, 0, 0);
    result.speed_kts = 0;
    result.referenceMode = 0;
    result.referencePlatform = -1;

    tcGameObject* gameObj = simState->GetObject(platformId);
    
    if (missionId == -1)
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

        const std::vector<ai::Nav::WaypointData>& waypoints = mission->GetRoute()->GetWaypoints();

        if (waypointIdx < waypoints.size())
        {
            result = waypoints[waypointIdx];
        }

        return result;
    }

}

/**
* @return number of parent waypoints
*/
size_t tcWaypointPopup::GetNumberWaypoints()
{
    size_t error = 0;

    tcGameObject* gameObj = simState->GetObject(platformId);
    
    if (missionId == -1)
    {
        tcPlatformObject* obj = dynamic_cast<tcPlatformObject*>(gameObj);
        if (obj == 0) return error;

        ai::Nav* nav = obj->GetBrain()->GetNavTask();
        if (nav == 0) return error;

        const std::vector<ai::Nav::WaypointData>& waypoints = nav->GetWaypoints();

        return waypoints.size();
    }
    else
    {
        tcFlightOpsObject* flightOps = dynamic_cast<tcFlightOpsObject*>(gameObj);
        tcFlightPort* flightPort = flightOps->GetFlightPort();
        if (flightPort == 0) return error;

        ai::tcMissionManager* missionManager = flightPort->GetMissionManager();
        if (missionManager == 0) return error;

        ai::tcMission* mission = missionManager->GetMission(missionId);
        if (mission == 0) return error;

        const std::vector<ai::Nav::WaypointData>& waypoints = mission->GetRoute()->GetWaypoints();

        return waypoints.size();
    }

}


/**
* Create and initialize GUI objects 
*/
void tcWaypointPopup::InitControls()
{
    const int widgetWidth = 75;
    const int widgetHeight = 15;
    const float widgetFontSize = 14.0;
    const float widgetAlpha = 1.0f;
    int x = 90;
    int y = 28;

    ai::Nav::WaypointData waypoint = GetWaypoint();

    tcPlatformObject* obj = 
        dynamic_cast<tcPlatformObject*>(simState->GetObject(platformId));
    if (obj == 0) return;

    referenceMode = waypoint.referenceMode;
    referencePlatform = waypoint.referencePlatform;

    latitudeEntry = new tcNumberWidget<double>(latitude_deg, this, wxPoint(x, y), 
        wxSize(widgetWidth, widgetHeight));
    latitudeEntry->SetCaption("Latitude [deg]");
    latitudeEntry->SetFormatString("%.5f");
    latitudeEntry->SetFontSize(widgetFontSize);
    latitudeEntry->SetActive(true);
    latitudeEntry->SetSendRedraw(true);
    latitudeEntry->SetBounds(-90.0, 90.0);
    latitudeEntry->SetSmallestIncrement(0.00001);
    latitude_deg = C_180OVERPI * waypoint.waypoint.mfLat_rad;
    latitude_prev_deg = latitude_deg;

    y += widgetHeight + 5;

    longitudeEntry = new tcNumberWidget<double>(longitude_deg, this, wxPoint(x, y), 
        wxSize(widgetWidth, widgetHeight));
    longitudeEntry->SetCaption("Longitude [deg]");
    longitudeEntry->SetFormatString("%.5f");
    longitudeEntry->SetFontSize(widgetFontSize);
    longitudeEntry->SetActive(true);
    longitudeEntry->SetSendRedraw(true);
    longitudeEntry->SetBounds(0, 30000);
    longitudeEntry->SetSmallestIncrement(0.00001);
    longitude_deg = C_180OVERPI * waypoint.waypoint.mfLon_rad;
    longitude_prev_deg = longitude_deg;

    y += widgetHeight + 5;



    if (tcAirObject* air = dynamic_cast<tcAirObject*>(obj))
    {
        altitudeAdjust = new tcNumberWidget<float>(altitude_m, this, wxPoint(x, y), 
            wxSize(widgetWidth, widgetHeight));
        altitudeAdjust->SetCaption("Altitude [m]");
        altitudeAdjust->SetFontSize(widgetFontSize);
        altitudeAdjust->SetActive(true);
        altitudeAdjust->SetSendRedraw(true);
        altitudeAdjust->SetBounds(0, 30000);
        altitude_m = waypoint.waypoint.mfAlt_m;
        altitude_prev_m = waypoint.waypoint.mfAlt_m;

        y += widgetHeight + 5;
    }
    else if (tcSubObject* sub = dynamic_cast<tcSubObject*>(obj))
    {
        altitudeAdjust = new tcNumberWidget<float>(altitude_m, this, wxPoint(x, y), 
            wxSize(widgetWidth, widgetHeight));
        altitudeAdjust->SetCaption("Altitude [m]");
        altitudeAdjust->SetFontSize(widgetFontSize);
        altitudeAdjust->SetActive(true);
        altitudeAdjust->SetSendRedraw(true);
        altitudeAdjust->SetBounds(-2000, 0);

        altitude_m = waypoint.waypoint.mfAlt_m;
        altitude_prev_m = waypoint.waypoint.mfAlt_m;

        y += widgetHeight + 5;
    }
    else if (missionId > 0)
    {
        altitudeAdjust = new tcNumberWidget<float>(altitude_m, this, wxPoint(x, y), 
            wxSize(widgetWidth, widgetHeight));
        altitudeAdjust->SetCaption("Altitude [m]");
        altitudeAdjust->SetFontSize(widgetFontSize);
        altitudeAdjust->SetActive(true);
        altitudeAdjust->SetSendRedraw(true);
        altitudeAdjust->SetBounds(0, 30000);

        altitude_m = waypoint.waypoint.mfAlt_m;
        altitude_prev_m = waypoint.waypoint.mfAlt_m;

        y += widgetHeight + 5;
    }
    

    speedAdjust = new tcNumberWidget<float>(speed_kts, this, wxPoint(x, y), 
        wxSize(widgetWidth, widgetHeight));
    speedAdjust->SetCaption("Speed [kts]");
    speedAdjust->SetFontSize(widgetFontSize);
    speedAdjust->SetActive(true);
    speedAdjust->SetSendRedraw(true);
    speed_kts = waypoint.speed_kts;
    speed_prev_kts = waypoint.speed_kts;
    y += widgetHeight + 5;

    updateButton = new tcButton(this, wxPoint(x, y), 
        wxSize(widgetWidth, widgetHeight));
    updateButton->SetActive(true);
    updateButton->SetBackgroundAlpha(widgetAlpha);
    updateButton->SetCaption("Update");
    updateButton->SetCommand(LP_UPDATE);
    updateButton->SetFontSize(12.0);
    updateButton->SetSendRedraw(true);
	updateButton->SetFillColors(Vec4(0.0, 0.0, 0.0, 1.0), Vec4(1.0, 1.0, 1.0, 1.0), 
        Vec4(0.4f, 1.0, 0.4f, 1.0));

    showTaskEdit = new tcButton(this, wxPoint(x-22, y), wxSize(16, 16), "ShowTaskList");
    showTaskEdit->LoadImages("plus_dark.png", "plus.png", "plus.png", "plus.png");
    showTaskEdit->SetOn(false);
    showTaskEdit->SetInteractive(true);
    showTaskEdit->SetCommand(55);
    showTaskEdit->SetMouseOverCaption("ORDERS");
    showTaskEdit->SetMouseOverCaptionPosition(wxPoint(-25, 8));
    showTaskEdit->SetFontSize(14.0f);
    
    y += 20.0f;

    setReferencePlatform = new tcButton(this, wxPoint(5, y), wxSize(16, 16), "SetRefPlat");
    setReferencePlatform->SetCommand(WP_SETANCHOR);
    setReferencePlatform->LoadImages("anchor.png", "anchor.png", "anchor.png", "anchor.png");
    setReferencePlatform->SetCaption("");
    setReferencePlatform->SetFillColors(Vec4(0.5f, 0.5f, 0.5f, 1.0f), Vec4(0.8f, 0.8f, 1.0f, 1.0f), Vec4(1.0f, 1.0f, 1.0f, 1.0f));
    setReferencePlatform->SetApplyColorToImage(true);
    setReferencePlatform->SetInteractive(true);
    setReferencePlatform->SetActive(true);
    setReferencePlatform->SetMouseOverCaption("SET ANCHOR PLATFORM");
    setReferencePlatform->SetMouseOverCaptionAlignment(LEFT_BASE_LINE);
    setReferencePlatform->SetMouseOverCaptionFontSize(8.0f);
    setReferencePlatform->SetMouseOverCaptionPosition(wxPoint(0, -11));

    toggleReferenceMode = new tcButton(this, wxPoint(25, y+2), wxSize(12, 12), "ToggleRefMode");
    toggleReferenceMode->SetCommand(WP_TOGGLEANCHORMODE);
    //toggleReferenceMode->LoadImages("anchor.png", "anchor.png", "anchor.png", "anchor.png");
    toggleReferenceMode->SetCaption("");
    toggleReferenceMode->SetFontSize(12.0f);
    toggleReferenceMode->SetFillColors(Vec4(0.5f, 0.5f, 0.5f, 1.0f), Vec4(0.8f, 0.8f, 1.0f, 1.0f), Vec4(1.0f, 1.0f, 1.0f, 1.0f));
    toggleReferenceMode->SetApplyColorToImage(true);
    toggleReferenceMode->SetMouseOverCaption("TOGGLE ANCHOR MODE");
    toggleReferenceMode->SetMouseOverCaptionAlignment(LEFT_BASE_LINE);
    toggleReferenceMode->SetMouseOverCaptionFontSize(8.0f);
    toggleReferenceMode->SetMouseOverCaptionPosition(wxPoint(0, -11));

    clearReferenceMode = new tcButton(this, wxPoint(mnWidth-20, y+2), wxSize(12, 12), "ClearRefMode");
    clearReferenceMode->SetCommand(WP_CLEARANCHOR);
    clearReferenceMode->LoadImages("close_gray.png", "close_gray.png", "close_gray.png", "close_gray.png");
    clearReferenceMode->SetCaption("");
    clearReferenceMode->SetFillColors(Vec4(0.5f, 0.5f, 0.5f, 1.0f), Vec4(0.8f, 0.8f, 1.0f, 1.0f), Vec4(1.0f, 1.0f, 1.0f, 1.0f));
    clearReferenceMode->SetApplyColorToImage(true);
    clearReferenceMode->SetMouseOverCaption("CLEAR ANCHOR");
    clearReferenceMode->SetMouseOverCaptionAlignment(RIGHT_BASE_LINE);
    clearReferenceMode->SetMouseOverCaptionFontSize(8.0f);
    clearReferenceMode->SetMouseOverCaptionPosition(wxPoint(0, -11));

    referenceUnitBox.Set(40.0f, mnWidth-25, y, y+16.0f);

    UpdateButtonState();
}

bool tcWaypointPopup::IsDataUpdated() const
{
    bool dataUpdated = (speed_kts != speed_prev_kts) || (altitude_m != altitude_prev_m) ||
        (longitude_deg != longitude_prev_deg) || (latitude_deg != latitude_prev_deg);

    return dataUpdated;
}

/**
* @return false if not a mission waypoint. If mission waypoint, return true if mission not found or locked
*/
bool tcWaypointPopup::IsMissionLocked() const
{
    if (missionId == -1) return false;

    tcGameObject* gameObj = simState->GetObject(platformId);

    tcFlightOpsObject* flightOps = dynamic_cast<tcFlightOpsObject*>(gameObj);
    tcFlightPort* flightPort = flightOps->GetFlightPort();
    if (flightPort == 0) return true;

    ai::tcMissionManager* missionManager = flightPort->GetMissionManager();
    if (missionManager == 0) return true;

    ai::tcMission* mission = missionManager->GetMission(missionId);
    if (mission != 0)
    {
        return mission->IsLocked();
    }
    else
    {
        return true;
    }

}

void tcWaypointPopup::UpdateButtonState()
{
    ai::Nav::WaypointData waypoint = GetWaypoint();
    referenceMode = waypoint.referenceMode;
    referencePlatform = waypoint.referencePlatform;

    switch (referenceMode)
    {
    case 0:
        clearReferenceMode->SetActive(false);
        toggleReferenceMode->SetActive(false);
        break;
    case 1:
        clearReferenceMode->SetActive(true);
        toggleReferenceMode->SetActive(true);
        toggleReferenceMode->SetCaption("N");
        break;
    case 2:
        clearReferenceMode->SetActive(true);
        toggleReferenceMode->SetActive(true);
        toggleReferenceMode->SetCaption("R");
        break;
    }
}

/**
* Update parent with GUI params
*/
void tcWaypointPopup::UpdateParentWaypoint()
{
    ai::Nav::WaypointData waypoint = GetWaypoint();

    if ((waypoint.waypoint.mfLat_rad == 0) && (waypoint.waypoint.mfLon_rad == 0))
    {
        return; // unable to get waypoint
    }

    double lat_rad = C_PIOVER180 * latitude_deg;
    double lon_rad = C_PIOVER180 * longitude_deg;

    if (missionId == -1)
    {
        wxString s = wxString::Format(",%d, %f, %f, %f, %f", 
            waypointIdx, lon_rad, lat_rad, altitude_m, speed_kts);

        std::vector<long> commandId;
        commandId.push_back(platformId);
        commandInterface->AddPythonCommandGeneral("EditWaypointAdvanced", s.ToStdString(), commandId);
    }
    else
    {
        if (IsMissionLocked()) return; // don't update if locked

        wxString s = wxString::Format(",%d, %d, %f, %f, %f, %f", 
            missionId, waypointIdx, lon_rad, lat_rad, altitude_m, speed_kts);

        std::vector<long> commandId;
        commandId.push_back(platformId);
        commandInterface->AddPythonCommandGeneral("EditMissionWaypointAdvanced", s.ToStdString(), commandId);
    }

    altitude_prev_m = altitude_m;
    speed_prev_kts = speed_kts;
    latitude_prev_deg = latitude_deg;
    longitude_prev_deg = longitude_deg;
}



void tcWaypointPopup::OnChar(wxKeyEvent& event)
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
void tcWaypointPopup::OnChildRedraw(wxCommandEvent& event)
{
    redraw = true;
}

/**
* Close and destroy popup
*/
void tcWaypointPopup::OnCloseCommand(wxCommandEvent& event)
{
    DestroyWindow();
}

void tcWaypointPopup::OnSetAnchor(wxCommandEvent& event)
{
    ai::Nav::WaypointData waypoint = GetWaypoint();

    if ((waypoint.waypoint.mfLat_rad == 0) && (waypoint.waypoint.mfLon_rad == 0))
    {
        return; // unable to get waypoint
    }

    if (referenceMode == 0) referenceMode = 1;

    if (missionId == -1)
    {
        wxString s = wxString::Format(",%d, %d", 
            waypointIdx, referenceMode);
        std::vector<long> commandId;
        commandId.push_back(platformId);
        commandInterface->GetUserInputForID("EditWaypointReferencePlatform", "Target", commandId, std::string(s.c_str()));
    }
    else
    {
        if (IsMissionLocked()) return; // don't update if locked

        wxString s = wxString::Format(",%d,%d,%d", 
            missionId, waypointIdx, referenceMode);
        std::vector<long> commandId;
        commandId.push_back(platformId);
        commandInterface->GetUserInputForID("EditMissionWaypointReferencePlatform", "Target", commandId, std::string(s.c_str()));
    }
}

void tcWaypointPopup::OnToggleAnchorMode(wxCommandEvent& event)
{
    if (referenceMode == 0) return;

    int newReferenceMode = (referenceMode == 1) ? 2 : 1;

    if (missionId == -1)
    {
        wxString s = wxString::Format(",%d,%d,%d", 
            referencePlatform, waypointIdx, newReferenceMode);
        std::vector<long> commandId;
        commandId.push_back(platformId);
        commandInterface->AddPythonCommandGeneral("EditWaypointReferencePlatform", s.ToStdString(), commandId);
    }
    else
    {
        wxString s = wxString::Format(",%d,%d,%d,%d", 
            referencePlatform, missionId, waypointIdx, newReferenceMode);
        std::vector<long> commandId;
        commandId.push_back(platformId);
        commandInterface->AddPythonCommandGeneral("EditMissionWaypointReferencePlatform", s.ToStdString(), commandId);
    }
}

void tcWaypointPopup::OnClearAnchor(wxCommandEvent& event)
{
    if (missionId == -1)
    {
        int newReferenceMode = 0;
        wxString s = wxString::Format(",-1,%d,%d", 
            waypointIdx, newReferenceMode);
        std::vector<long> commandId;
        commandId.push_back(platformId);
        commandInterface->AddPythonCommandGeneral("EditWaypointReferencePlatform", s.ToStdString(), commandId);
    }
    else
    {
        int newReferenceMode = 0;
        wxString s = wxString::Format(",-1,%d,%d,%d", 
            missionId, waypointIdx, newReferenceMode);
        std::vector<long> commandId;
        commandId.push_back(platformId);
        commandInterface->AddPythonCommandGeneral("EditMissionWaypointReferencePlatform", s.ToStdString(), commandId);
    }
}


void tcWaypointPopup::OnShowTaskEditCommand(wxCommandEvent& event)
{
    if (showTaskEdit == 0) return;

    int eventId = event.GetId();
    if (eventId != 55)
    {
        wxASSERT(false);
        return;
    }


    if ((taskEditPopupId == -1) || !tcRegistered::WindowExists(taskEditPopupId))
    {
        if ((missionId > 0) && IsMissionLocked())
        {
            return; // don't show task edit if mission locked
        }

        wxPoint pos = wxWindow::GetPosition();
        pos.x -= 160;

        tcWaypointTaskPopup* taskPopup = 
            new tcWaypointTaskPopup(platformId, missionId, waypointIdx, pos);

        taskEditPopupId = taskPopup->GetKey();
        showTaskEdit->SetOn(true);
    }
    else
    {
        tcRegistered::ForceClose(taskEditPopupId);
        showTaskEdit->SetOn(false);
        taskEditPopupId = -1;
    }

    
}



void tcWaypointPopup::OnUpdateCommand(wxCommandEvent& event)
{
    UpdateParentWaypoint();
}

/**
* A hack job for now :)
*/
void tcWaypointPopup::OnLButtonDown(wxMouseEvent& event)
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
void tcWaypointPopup::OnLButtonUp(wxMouseEvent& event)
{
    isLButtonDown = false;
    dragOn = false;

	ReleaseMouse();
}

/**
*
*/
void tcWaypointPopup::OnMouseMove(wxMouseEvent& event)
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

void tcWaypointPopup::OnPrevWaypoint(wxCommandEvent& event)
{
    size_t nWaypoints = GetNumberWaypoints();

    if (nWaypoints == 0)
    {
        waypointIdx = 0;
    }
    else if (waypointIdx > 0)
    {
        waypointIdx = waypointIdx - 1;
    }
    else
    {
        waypointIdx = nWaypoints - 1;
    }

    UpdateFromParent();
}

void tcWaypointPopup::OnNextWaypoint(wxCommandEvent& event)
{
    size_t nWaypoints = GetNumberWaypoints();
    if (nWaypoints == 0)
    {
        waypointIdx = 0;
        return;
    }

    waypointIdx = (waypointIdx + 1) % nWaypoints;

    UpdateFromParent();
}

void tcWaypointPopup::OnInsertWaypoint(wxCommandEvent& event)
{
    size_t nWaypoints = GetNumberWaypoints();
    ai::Nav::WaypointData waypoint = GetWaypoint();

    if ((waypoint.waypoint.mfLat_rad == 0) && (waypoint.waypoint.mfLon_rad == 0) && (nWaypoints > 0))
    {
        return; // unable to get waypoint
    }

    ai::Route* route = GetParentRoute();
    if (route == 0) return;

    if (nWaypoints == 0) // no waypoints exist yet, add
    {
        if (tcGameObject* gameObj = simState->GetObject(platformId))
        {
            route->AddWaypoint(
                gameObj->mcKin.mfLon_rad + 0.001, gameObj->mcKin.mfLat_rad + 0.001, 0, 0);

            waypointIdx = 0;
        }
        else
        {
            return; // error, no host platform
        }
    }
    else if ((waypointIdx + 1) == nWaypoints) // on last waypoint, add
    {
        route->AddWaypoint(
            waypoint.waypoint.mfLon_rad + 0.001, waypoint.waypoint.mfLat_rad + 0.001, 
            waypoint.waypoint.mfAlt_m, waypoint.speed_kts);

        waypointIdx++;
    }
    else // insert before next, then move to inserted
    {
        route->InsertWaypoint(waypointIdx + 1, 
            waypoint.waypoint.mfLon_rad + 0.001, waypoint.waypoint.mfLat_rad + 0.001, 
            waypoint.waypoint.mfAlt_m, waypoint.speed_kts);

        waypointIdx++;
    }
    
    UpdateFromParent();
}

void tcWaypointPopup::OnDeleteWaypoint(wxCommandEvent& event)
{
    ai::Route* route = GetParentRoute();
    if (route == 0) return;
    size_t nWaypoints = GetNumberWaypoints();

    route->DeleteWaypoint(waypointIdx);


    if (waypointIdx > 0)
    {
        waypointIdx = waypointIdx - 1;
    }
    

    UpdateFromParent();
}


void tcWaypointPopup::OnRButtonDown(wxMouseEvent& event)
{
    // do nothing, but keep event from getting passed upward
}


void tcWaypointPopup::SetActive(bool abActive)
{
    tc3DWindow2::SetActive(abActive);

    if (abActive)
    {
        UpdateButtonState();
    }
}

/**
* Call after waypoint index changed to refresh with new data
*/
void tcWaypointPopup::UpdateFromParent()
{
    ai::Nav::WaypointData waypoint = GetWaypoint();

    if ((waypoint.waypoint.mfLat_rad == 0) && (waypoint.waypoint.mfLon_rad == 0))
    {
        return; // unable to get waypoint
    }

    latitude_deg = C_180OVERPI * waypoint.waypoint.mfLat_rad;
    longitude_deg = C_180OVERPI * waypoint.waypoint.mfLon_rad;
    altitude_m = waypoint.waypoint.mfAlt_m;
    speed_kts = waypoint.speed_kts;

    latitude_prev_deg = latitude_deg;
    longitude_prev_deg = longitude_deg;
    altitude_prev_m = altitude_m;
    speed_prev_kts = speed_kts;

    tacticalMap->UpdateDetailedEditPointIndex(int(waypointIdx) + 1);
}


/**
* @param id Id of platform with launcher to control
* @param idx Launcher idx on platform
*/
tcWaypointPopup::tcWaypointPopup(long platformId_, long missionId_, unsigned int waypointIdx_, const wxPoint& pos)
            : tc3DWindow2(parent, pos, wxSize(180, 160), "WaypointEditPopup", parent),
   platformId(platformId_),
   missionId(missionId_),
   waypointIdx(waypointIdx_),
   redraw(true),
   dragOn(false),
   taskEditPopupId(-1),
   referenceMode(0),
   referencePlatform(-1)
{
    wxASSERT(tacticalMap != 0);

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

    int buttonSize = 12;
    int buttonSpacing = 15;

    previousWaypoint = new tcButton(this, wxPoint(mnWidth - 75, 4), 
        wxSize(buttonSize, buttonSize));
    previousWaypoint->SetActive(true);
    previousWaypoint->SetBackgroundAlpha(1.0);
    previousWaypoint->SetCaption("");
    previousWaypoint->SetCommand(WP_PREVWAYPOINT);
    previousWaypoint->LoadImages("decel_time.jpg", "decel_time.jpg", "decel_time_over.jpg", "decel_time_over.jpg");
    previousWaypoint->SetSendRedraw(true);

    nextWaypoint = new tcButton(this, wxPoint(mnWidth - 75 + buttonSpacing, 4), 
        wxSize(buttonSize, buttonSize));
    nextWaypoint->SetActive(true);
    nextWaypoint->SetBackgroundAlpha(1.0);
    nextWaypoint->SetCaption("");
    nextWaypoint->SetCommand(WP_NEXTWAYPOINT);
    nextWaypoint->LoadImages("accel_time.jpg", "accel_time.jpg", "accel_time_over.jpg", "accel_time_over.jpg");
    nextWaypoint->SetSendRedraw(true);

    insertWaypoint = new tcButton(this, wxPoint(mnWidth - 75 + 2*buttonSpacing, 4), 
        wxSize(buttonSize, buttonSize));
    insertWaypoint->SetActive(true);
    insertWaypoint->SetBackgroundAlpha(1.0);
    insertWaypoint->SetCaption("");
    insertWaypoint->SetCommand(WP_INSERTWAYPOINT);
    insertWaypoint->LoadImages("square_plus.jpg", "square_plus.jpg", "square_plus_over.jpg", "square_plus_over.jpg");
    insertWaypoint->SetSendRedraw(true);

    deleteWaypoint = new tcButton(this, wxPoint(mnWidth - 75 + 3*buttonSpacing, 4), 
        wxSize(buttonSize, buttonSize));
    deleteWaypoint->SetActive(true);
    deleteWaypoint->SetBackgroundAlpha(1.0);
    deleteWaypoint->SetCaption("");
    deleteWaypoint->SetCommand(WP_DELETEWAYPOINT);
    deleteWaypoint->LoadImages("square_x.jpg", "square_x.jpg", "square_x_over.jpg", "square_x_over.jpg");
    deleteWaypoint->SetSendRedraw(true);


    InitControls();

    SetActive(true);

    SetBorderDraw(true);
}

tcWaypointPopup::~tcWaypointPopup() 
{
    if (taskEditPopupId != -1)
    {
        tcRegistered::ForceClose(taskEditPopupId);
    }
}

