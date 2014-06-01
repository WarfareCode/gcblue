/** 
**  @file tcXmlWindow.h 
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

#ifndef _XMLWINDOW_H_
#define _XMLWINDOW_H_

#if _MSC_VER > 1000
#pragma once
#endif 

#ifndef WX_PRECOMP
#include "wx/wx.h" 
#endif // WX_PRECOMP

#include "tc3DWindow2.h"
#include "tcSound.h"

class TiXmlDocument;
class tcButton;
class tcRadioButton;

/**
* tcWindow with Gdiplus drawing objects and sound
*/
class tcXmlWindow : public tc3DWindow2 
{
public:
    /// find first button with matching command and set force disable state
    void SetButtonDisable(long command, bool state);

	/// find first button with matching command
	tcButton* GetButtonWithCommand(long command);
	/// find first button with matching command and change caption
	void SetButtonCaption(long command, const std::string& caption);
    void SetDragable(bool state);
	void SetRadioButtonState(long radioCommand, long buttonCommand);
	/// return first radiobutton with matching command
	tcRadioButton* GetRadioButtonWithCommand(long command);

	void SetAllButtonState(bool state);

    tcXmlWindow(wxWindow *parent, 
        const wxPoint& pos, const wxSize& size, 
        const wxString& configFile = "",
        const wxString& name = "StandardWindow",
		tc3DWindow2* graphicsHost = 0);
    virtual ~tcXmlWindow();

protected:
    TiXmlDocument* config; ///< XML auto-configuration file for window
	static int windowLayer;  ///< used to achieve some layering of GUI windows (last always on top)

	// params for window drag
    bool isLButtonDown;
    bool windowDragOn;
	wxPoint windowDragPoint;
    bool isDragable; ///< true if window can be dragged (moved)

    void UpdateWindowDrag(const wxPoint& pos);

    virtual void OnButtonCommand(wxCommandEvent& event);
    virtual void OnLButtonDown(wxMouseEvent& event);
    virtual void OnLButtonUp(wxMouseEvent& event);
	virtual void OnMouseMove(wxMouseEvent& event);
    virtual void OnSize(wxSizeEvent& event);
    virtual void OnKeyDown(wxKeyEvent& event);

    void UpdateObjectsForResize(); // call after resize to adjust button position, etc, if necessary

private:
    static unsigned ref_count;

    void AddXMLControls(); ///< adds XML controls to window that can be added automatically

    DECLARE_EVENT_TABLE()
};

#endif

