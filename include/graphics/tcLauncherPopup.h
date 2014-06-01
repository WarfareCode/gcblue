/**
**  @file tcLauncherPopup.h 
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


#ifndef _LAUNCHERPOPUP_H_
#define _LAUNCHERPOPUP_H_

#if _MSC_VER > 1000
#pragma once
#endif 

#include "wx/wx.h" 
#include "wx/string.h"
#include <map>
#include "tv_types.h"

#include "tc3DWindow2.h"

class tcLauncher;
class tcSimState;
class tcButton;

template <class T>
class tcNumberWidget;

/**
* Popup control to configure launcher, set torpedo presets
*/
class tcLauncherPopup  : public tc3DWindow2
{
public:
    virtual void Draw();

    static void SetParent(tc3DWindow2* par);
	static const wxPoint& GetUserPosition(unsigned int idx);
    static void SetUserPosition(unsigned int idx, const wxPoint& pos);

    static bool ForceClose(long id, unsigned idx); ///< message to close matching popup
    static bool WindowExists(long id, unsigned idx); ///< to check if popup is already open

    tcLauncherPopup(long id, unsigned idx, const wxPoint& pos); 
    virtual ~tcLauncherPopup();

protected:
    static tc3DWindow2* parent;
    
    bool redraw;
    unsigned int birthCount;
    bool isLButtonDown;
    bool dragOn;
    wxPoint dragPoint; ///< initial point at start of drag


    virtual void OnChildRedraw(wxCommandEvent& event);
    virtual void OnCloseCommand(wxCommandEvent& event);
    virtual void OnDatumCommand(wxCommandEvent& event);
    virtual void OnLaunchCommand(wxCommandEvent& event);
    virtual void OnTogglePassiveCommand(wxCommandEvent& event);

    virtual void OnChar(wxKeyEvent& event);
    virtual void OnLButtonDown(wxMouseEvent& event);
    virtual void OnLButtonUp(wxMouseEvent& event);
    virtual void OnMouseMove(wxMouseEvent& event);
    virtual void OnRButtonDown(wxMouseEvent& event);
    
    


private:
    enum {LP_CLOSE = 0, LP_LAUNCH = 1, LP_SETDATUM = 2, LP_TOGGLEPASSIVE = 3};
	enum {MAX_LAUNCHERS = 10};
    long platformId;
    unsigned launcherIdx;
    tcSimState* simState;
    
    tcLauncher* GetLauncher();
    void InitTorpedoControls();
    void UpdateTorpedoLauncher();

    tcButton* closeButton;

    // torpedo launcher controls
    tcButton* launchButton;
    tcButton* selectDatumButton;

    tcNumberWidget<float>* runToEnableAdjust;
    tcNumberWidget<float>* depthAdjust;
    tcNumberWidget<float>* speedAdjust;
    tcNumberWidget<float>* ceilingAdjust;
    tcNumberWidget<float>* floorAdjust;
    tcButton* activePassiveButton;

    float runToEnable;
	float runToEnable_prev;
    float depth;
    float speed;
    float ceiling;
    float floor;
    bool isPassive;

	static wxPoint userPositions[MAX_LAUNCHERS]; ///< saves last user move position for each launcher
	static bool userPositionsInitialized;
    static std::map<long, bool> registry; ///< means of checking which windows are open and forcing closed without having pointer
    
    
    static bool GetForceClose(long id, unsigned idx);
    static long GetKey(long id, unsigned idx);
    static void RegisterWindow(long id, unsigned idx);
    static void UnregisterWindow(long id, unsigned idx);
    static void UnregisterAll();

    DECLARE_EVENT_TABLE()
};

#endif

