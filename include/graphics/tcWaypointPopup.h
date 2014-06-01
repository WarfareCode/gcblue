/**
**  @file tcWaypointPopup.h 
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

#ifndef _WAYPOINTPOPUP_H_
#define _WAYPOINTPOPUP_H_

#if _MSC_VER > 1000
#pragma once
#endif 

#include "wx/wx.h" 
#include "wx/string.h"
#include <map>
#include "tv_types.h"

#include "tc3DWindow2.h"
#include "tcRegistered.h"
#include "ai/Nav.h"

class tcSimState;
class tcButton;
template <class T> class tcNumberWidget;
class tcListBox;
class tcCommandQueue;
class tcTacticalMapView;

/**
* Popup control for editing nav waypoint parameters
*/
class tcWaypointPopup : public tc3DWindow2, public tcRegistered
{
public:
    virtual void Draw();

    static void SetParent(tc3DWindow2* par);

    static tcTacticalMapView* tacticalMap;

    tcWaypointPopup(long platformId_, long missionId_, unsigned int waypointIdx_, const wxPoint& pos); 
    virtual ~tcWaypointPopup();

protected:
    static tc3DWindow2* parent;
    static tcCommandQueue* commandInterface;
    
    bool redraw;
    unsigned int birthCount;
    bool isLButtonDown;
    bool dragOn;
    wxPoint dragPoint; ///< initial point at start of drag


    virtual void OnChildRedraw(wxCommandEvent& event);
    virtual void OnCloseCommand(wxCommandEvent& event);
    virtual void OnUpdateCommand(wxCommandEvent& event);
    virtual void OnShowTaskEditCommand(wxCommandEvent& event);

    virtual void OnSetAnchor(wxCommandEvent& event);
    virtual void OnToggleAnchorMode(wxCommandEvent& event);
    virtual void OnClearAnchor(wxCommandEvent& event);
    virtual void OnPrevWaypoint(wxCommandEvent& event);
    virtual void OnNextWaypoint(wxCommandEvent& event);
    virtual void OnInsertWaypoint(wxCommandEvent& event);
    virtual void OnDeleteWaypoint(wxCommandEvent& event);

    virtual void OnChar(wxKeyEvent& event);
    virtual void OnLButtonDown(wxMouseEvent& event);
    virtual void OnLButtonUp(wxMouseEvent& event);
    virtual void OnMouseMove(wxMouseEvent& event);
    virtual void OnRButtonDown(wxMouseEvent& event);

    virtual void SetActive(bool abActive);
    

private:
    enum {LP_CLOSE = 0, LP_UPDATE = 1, WP_SETANCHOR = 60, WP_TOGGLEANCHORMODE = 61, WP_CLEARANCHOR = 62, 
          WP_PREVWAYPOINT = 201, WP_NEXTWAYPOINT = 202, WP_INSERTWAYPOINT = 205, WP_DELETEWAYPOINT = 206};

    long platformId;
    long missionId; ///< -1 for not a mission waypoint
    unsigned int waypointIdx;
    tcSimState* simState;

    tcButton* closeButton;
    tcButton* updateButton; // update parent with latest gui data

    tcButton* previousWaypoint;
    tcButton* nextWaypoint;
    tcButton* insertWaypoint;
    tcButton* deleteWaypoint;

    tcNumberWidget<double>* latitudeEntry;
    tcNumberWidget<double>* longitudeEntry;
    tcNumberWidget<float>* altitudeAdjust;
    tcNumberWidget<float>* speedAdjust;
    tcButton* showTaskEdit;
    long taskEditPopupId;

    tcButton* setReferencePlatform;
    tcButton* toggleReferenceMode;
    tcButton* clearReferenceMode;
    tcRect referenceUnitBox; // draw reference unit name here

    double latitude_deg;
    double longitude_deg;
    float altitude_m;
    float speed_kts;

    double latitude_prev_deg; // to detect update
    double longitude_prev_deg;
    float altitude_prev_m;
    float speed_prev_kts;

    unsigned char referenceMode;
    long referencePlatform;
    


    void InitControls();
    void UpdateParentWaypoint();
    void UpdateFromParent();
    ai::Nav::WaypointData GetWaypoint();
    ai::Route* GetParentRoute();

    size_t GetNumberWaypoints();
    bool IsMissionLocked() const;
    bool IsDataUpdated() const;
    void UpdateButtonState();


    DECLARE_EVENT_TABLE()
};

#endif

