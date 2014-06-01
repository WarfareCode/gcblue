/**  
**  @file tcDirector.cpp
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
/// @file tcDirector.cpp source file for tcDirector class


#include "stdwx.h" // precompiled header file

#ifndef WX_PRECOMP
#include "wx/wx.h" 
#endif

#include "tcDirector.h"
#include "tcDirectorEvent.h"
#include "tcConsoleBox.h"
#include "tcSound.h"
#include "tcSimState.h"
#include "wxcommands.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/**
* static method to set static members for map views
* 
* @see tcMapEvent::AttachMapViews
*/
void tcDirector::AttachMapViews(tcTacticalMapView* tmv, tcWorldMapView* wmv)
{
	tcMapEvent::AttachMapViews(tmv, wmv);
}

/**
* Add default events for game start
*/
void tcDirector::AddGameStartEvents()
{
    tcSimState* simState = tcSimState::Get();
    const tcDateTime dt = simState->GetDateTime();
    
    wxString timeString = wxString::Format("%d %s %d", 
        dt.GetDay(), dt.GetMonthString(), dt.GetYear());

    AddEvent(new tcSoundEffectEvent(0.1, "Boom"));

    tcMapTextEvent* mapText = new tcMapTextEvent(simState->GetScenarioName(), 0.0, 5.0f, 0.5, 0.75, 7);
    mapText->SetTextColor(Vec4(1, 1, 1, 0.8f));
    mapText->SetTextSize(24.0f);
    mapText->SetTextAlignment(tc3DWindow2::CENTER_CENTER);
    AddEvent(mapText);

    tcMapTextEvent* mapText2 = new tcMapTextEvent(timeString.ToStdString(), 0.0, 5.0f, 0.5, 0.72, 7);
    mapText2->SetTextColor(Vec4(1, 1, 1, 0.8f));
    mapText2->SetTextSize(24.0f);
    mapText2->SetTextAlignment(tc3DWindow2::CENTER_CENTER);
    AddEvent(mapText2);


}

/**
* Director will delete events when finished. This system
* may benefit from a referenced/smart pointer system to
* guard against double deletions.
*/
void tcDirector::AddEvent(tcDirectorEvent* event)
{
    events.push_back(event);
}

/**
* Clear event vector and delete non-null elements.
*/
void tcDirector::ClearEvents()
{
    int nEvents = (int)events.size();
    for(int n=0; n<nEvents; n++)
    {
        if (events[n])
        {
            delete events[n];
        }
    }
    events.clear();
}


void tcDirector::InitTest()
{
#if 0
    AddEvent(new tcGameCommandEvent(ID_SETPAUSE, 0, 1));
    AddEvent(new tcGameCommandEvent(ID_SETBRIEFING, 0, 1));
    AddEvent(new tcGameCommandEvent(ID_SET3D, 0, 0)); // deactivate 3D window

    //AddEvent(new tcSoundEffectEvent(1.0f,"Welcome"));
    //AddEvent(new tcMusicEvent("","pause",0,0,0));
    AddEvent(new tcMusicEvent("tension1","play",0,2.0,30.0));
    //AddEvent(new tcMusicEvent("","seek",0,20.0,30.0));

    
    AddEvent(new tcMessageTextEvent("ORDERS:",4));
    AddEvent(new tcMessageTextEvent("Engage enemy to the Northwest",5));

    AddEvent(new tcMapViewEvent(7, -5.9, 49.5, 4.0, true));
    AddEvent(new tcSoundEffectEvent(7,"Thuck"));
    AddEvent(new tcMapTextEvent("OPFOR", 7.0, 18.0f, -6.0, 49.9, 1));

    AddEvent(new tcMessageTextEvent("", 9));
    AddEvent(new tcMessageTextEvent("Enemy is believed to be a medium sized task force", 9));
    AddEvent(new tcMessageTextEvent("similar in makeup to your own.", 9));
    AddEvent(new tcMessageTextEvent("", 12));
    AddEvent(new tcMessageTextEvent("Extreme caution is advised", 12));
    AddEvent(new tcMessageTextEvent("", 13));
    AddEvent(new tcMessageTextEvent("Good hunting", 13));

    AddEvent(new tcGameCommandEvent(ID_SETPAUSE, 18 , 0));
    AddEvent(new tcGameCommandEvent(ID_SETBRIEFING, 18, 0));
    AddEvent(new tcGameCommandEvent(ID_SET3D, 18, 1)); // deactivate 3D window
    //AddEvent(new tcMapViewEvent(24, -5.9, 49.5, 4.0));
#endif
}

void tcDirector::Update(double t)
{
    int nEvents = (int)events.size();
    for(int n=0; n<nEvents; n++)
    {
        events[n]->Update(t - startTime);
    }
}

tcDirector::tcDirector(tc3DViewer *view3D, tcConsoleBox *console
                       , wxWindow *win)
: viewer(view3D)
{
    tcDirectorEvent::AttachEventHandler(win);
//    tcCameraEvent::AttachViewer(viewer);
    events.clear();
    startTime = 0;
    controlActive = false;
}

tcDirector::~tcDirector()
{
    ClearEvents();
}

