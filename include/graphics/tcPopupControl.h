/**  
**  @file tcPopupControl.h
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


#ifndef _POPUPCONTROL_H_
#define _POPUPCONTROL_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "wx/wx.h" 

#include <string>
#include <vector>
#include "tcMenu.h"
#include "tcPanel.h"
#include "tc3DWindow2.h"
#include "commandlist.h"


namespace scriptinterface 
{
    class tcSimPythonInterface;
}

class tcCommandQueue;

using namespace scriptinterface;

enum teMenuMode
{
    MENUMODE_GAME,
    MENUMODE_PLATFORM,
	MENUMODE_GROUP,
    MENUMODE_TRACK,
    MENUMODE_GAMEEDIT,
    MENUMODE_PLATFORMEDIT,
    MENUMODE_WEAPONEDIT,
    MENUMODE_GROUPEDIT,
    MENUMODE_FLIGHTPANEL,
    MENUMODE_WEAPON
};

class tcPopupControl : public tc3DWindow2
{
public:
    tcCommandQueue *mpCommandInterface;
    tcSimPythonInterface *mpPythonInterface;
    teMenuMode meMode;

    void AttachCommandInterface(tcCommandQueue *apCommandInterface) {mpCommandInterface=apCommandInterface;}
    void AttachPythonInterface(tcSimPythonInterface *apIF) {mpPythonInterface = apIF;}
	virtual void SetBaseRenderBin(int n);
	virtual void SetActive(bool abActive);
    void SetMenu(teMenuMode mode);
    void SetMenu(); ///< this shouldn't be an override?
    bool Track(wxPoint point);
    void OnLButtonDown(wxMouseEvent& event);
    void OnMouseMove(wxMouseEvent& event);
    void Draw();
    void InitMenu();

    tcPopupControl(wxWindow *parent, 
        const wxPoint& pos, const wxSize& size, 
        const wxString& name = "PopupControl");
    virtual ~tcPopupControl();

private:
    tcMenu mcGameMenu;
    tcMenu mcGameEditMenu;
    tcMenu mcPlatformMenu;
    tcMenu mcPlatformEditMenu;
    tcMenu mcGroupEditMenu;
    tcMenu mcTrackMenu; // menu for (non-alliance) sensor tracks
    tcMenu mcWeaponMenu;
    tcMenu mcWeaponEditMenu;

    tcPanel mcPanel;
    tcMenu *mpMenu; // current menu
    tcPanel *mpPanel; // current panel (may have more than one panel in future)

    wxPoint mpointUpperLeft;          // upperleft coords of menu   
    wxRect mrectMenuExtent;

	int drawCount;
    bool mbShowDebug;
    bool mbRebuildMenu;  // set true to rebuild menu before draw
    wxPoint mpointMouse;

    void BuildGameMenu(); // "hard coded" game menu, rest are build in python scripts


};

#endif 
