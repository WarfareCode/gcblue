/**
**  @file tcWaypointTaskPopup.h 
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


#ifndef _WAYPOINTTASKPOPUP_H_
#define _WAYPOINTTASKPOPUP_H_

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
class tcListBox;
class tcCommandQueue;

/**
* Popup control for editing (adding/removing) tasks for waypoint
*/
class tcWaypointTaskPopup : public tc3DWindow2, public tcRegistered
{
public:
    virtual void Draw();

    static void SetParent(tc3DWindow2* par);

    tcWaypointTaskPopup(long platformId_, long missionId_, unsigned int waypointIdx_, const wxPoint& pos); 
    virtual ~tcWaypointTaskPopup();

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
    virtual void OnTaskCommand(wxCommandEvent& event);

    virtual void OnChar(wxKeyEvent& event);
    virtual void OnLButtonDown(wxMouseEvent& event);
    virtual void OnLButtonUp(wxMouseEvent& event);
    virtual void OnMouseMove(wxMouseEvent& event);
    virtual void OnRButtonDown(wxMouseEvent& event);
    

private:
    enum {LP_CLOSE = 0, LP_UPDATE = 1};

    long platformId;
    long missionId; ///< -1 for not a mission waypoint
    unsigned int waypointIdx;
    tcSimState* simState;

    tcButton* closeButton;
    tcButton* updateButton; // update parent with latest gui data

    tcListBox* taskEdit;

    std::vector<std::string> taskList; ///< local version of waypoint tasks
    std::vector<std::string> availableTasks; ///< tasks as defined in options.xml

    void InitControls();
    void UpdateParentWaypoint();
    ai::Nav::WaypointData GetWaypoint();
    void UpdateTaskList();

    void AddTask(const wxString& task);
    void RemoveTask(const wxString& task);

    DECLARE_EVENT_TABLE()
};

#endif

