/**  
**  @file tcMapOverlay.h
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


#ifndef _MAPOVERLAY_H_
#define _MAPOVERLAY_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "wx/wx.h" 

#include "tc3DWindow2.h"

class tcGeometry;

class tcMapObject;

class tcStream;
class tcCommandStream;
class tcCreateStream;
class tcUpdateStream;
class tcGameStream;
class tcTacticalMapView;
class tcMapMissionObject;

namespace scriptinterface
{
    class tcScenarioLogger;
}

/**
* Class intended to draw map objects on top of map.
* Example uses are to mark geopolitical borders, cities, and
* items of interest for current scenario.
*/
class tcMapOverlay : public tc3DWindow2
{
public:
    friend class scriptinterface::tcScenarioLogger;

    void AddMapObject(tcMapObject *obj);
    void ClearMapObjects();
    void Draw();

    /// redraw overlay during next call to Draw()
    void Redraw();
	void SetColor(const Vec4& color);

    bool IsInteracting() const;

    tcMapObject* GetObjectByRegisteredId(long id);

    virtual void OnChar(wxKeyEvent& event);
    virtual void OnLButtonDown(wxMouseEvent& event);
	virtual void OnLButtonUp(wxMouseEvent& event);
    virtual void OnMButtonDown(wxMouseEvent& event);
	virtual void OnMButtonUp(wxMouseEvent& event);
    virtual void OnLButtonDClick(wxMouseEvent& event);
    virtual void OnLeaveWindow(wxMouseEvent& event);
	virtual void OnMouseMove(wxMouseEvent& event);
    virtual void OnMouseWheel(wxMouseEvent& event);
    virtual void OnRButtonDown(wxMouseEvent& event);
    virtual void OnSize(wxSizeEvent& event);

    void ClearInteraction(); 
    bool IsInteractionBlocked() const;
    void SetInteractionBlocked(bool state);
    void SetAllTextInteractive(bool state);

    tcMapMissionObject* GetMissionObject(unsigned int missionId);

    virtual tcUpdateStream& operator<<(tcUpdateStream& stream);
    virtual tcUpdateStream& operator>>(tcUpdateStream& stream);

    virtual tcGameStream& operator<<(tcGameStream& stream);
    virtual tcGameStream& operator>>(tcGameStream& stream);

    tcMapOverlay(tcTacticalMapView* parent, 
        const wxPoint& pos, const wxSize& size, 
        const wxString& name = "MapOverlay");

    virtual ~tcMapOverlay();

private:
    tcTacticalMapView * const tacticalMap;

    std::vector<tcMapObject*> overlayObjects; // objects to draw
    /// used to redraw (create and add objects to scenegraph) only when necessary
    bool redraw;
    bool isInteracting;
    size_t hookedIdx;
    bool interactionBlocked;


    void DeleteFlaggedObjects();
    void HookObject(size_t idx);
};

#endif


