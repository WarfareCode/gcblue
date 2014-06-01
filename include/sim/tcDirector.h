/**  
**  @file tcDirector.h header for tcDirector class that manages cut scenes and dramatic briefings
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

#ifndef _TCDIRECTOR_H_
#define _TCDIRECTOR_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "wx/wx.h"

#include <vector>

class tcDirectorEvent;
class tcConsoleBox;
class tc3DViewer;

class tcTacticalMapView;
class tcWorldMapView;


/**
* Manages cut scenes and dramatic briefings. 
* Sequences through director event list to dispatch camera 
* and game commands.
*/
class tcDirector
{
public:
    bool controlActive; ///< true if director is controlling game
    double startTime;
    std::vector<tcDirectorEvent*> events;

    bool IsControlling() const {return controlActive;}
    void AddEvent(tcDirectorEvent* event);
    void ClearEvents();
    void InitTest(); ///< initializes director with a series of hard-coded events to help test
    //tcMapView* GetMapView() {return mapView;}
    //void SetMapView(tcMapView *mv) {mapView = mv;}
    void SetStartTime(double t) {startTime = t;} ///< Sets reference time for events
    void Update(double t);
    void AddGameStartEvents();

	static void AttachMapViews(tcTacticalMapView* tmv, tcWorldMapView* wmv);

    tcDirector(tc3DViewer *view3D, tcConsoleBox *console, wxWindow *win);
    ~tcDirector();
private:
    //tcMapView *mapView; ///< tcMapView object for map events (only one supported currently)
    tc3DViewer *viewer; ////< tc3DViewer object for camera events
};


#endif