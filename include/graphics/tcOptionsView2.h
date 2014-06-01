/**
**  @file tcOptionsView2.h
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


#ifndef _OPTIONSVIEW2_H_
#define _OPTIONSVIEW2_H_

#if _MSC_VER > 1000
#pragma once
#endif 

#include "wx/wx.h" 
#include <boost/shared_ptr.hpp>

#include "tcOptions.h"
#include "tcXmlWindow.h"
#include "tcTabbedWindow.h"

class tcTexture2D;

class tcOptions;
class tcSound;

/// View and GUI for user options data
class tcOptionsView2 : public tcXmlWindow, public tcTabbedWindow
{
	// placement info for GUI buttons, text, etc.
	struct tsButtonInfo 
	{
		int buttonX;
		int buttonY;
		int textX;
		int textY;
        int optionIdx;
        int valueIdx;
        bool isSlider; ///< a hack to add sliders
        tcRect thumbRect; ///< rect of slider "thumb"
	};

public:
	void Init();
	void Draw();
	void DrawButton(int x, int y, int abOn);
    void DrawSlider(int x, int y, tcRect thumbRect, float value, bool interacting);

	void OnLButtonDown(wxMouseEvent& event);
    void OnLButtonUp(wxMouseEvent& event);
    void OnLeaveWindow(wxMouseEvent& event);
    void OnMouseMove(wxMouseEvent& event);
	bool OnLButtonDownSlider(const wxPoint& pos);
    void OnSize(wxSizeEvent& event);
    
    virtual void SetActive(bool abActive);


	bool ButtonContainingPoint(wxPoint point, int& rnOption, int& rnValue);

	tcOptionsView2(wxWindow* parent,
		const wxPoint& pos, const wxSize& size, 
		const wxString& name = "OptionsView");

	tcOptionsView2(tc3DWindow2* parent,
		const wxPoint& pos, const wxSize& size, 
		const wxString& name);

	virtual ~tcOptionsView2();
private:
	tcOptions *mpOptions;

    struct ControlGroup
    {
        std::string groupName;
        std::vector<tc3DWindow2*> controls;
        std::vector<tc3DWindow2*> labels;
    };

    std::vector<ControlGroup> controlGroups;
    
    boost::shared_ptr<tcTexture2D> mpiButtonOn;
	boost::shared_ptr<tcTexture2D> mpiButtonOff;
	
	float fontSize; ///< font size of options choice text
	int mnButtonWidth;
	int mnButtonHeight;
    std::vector<tsButtonInfo> buttonInfo;
	int mnXStart;
	int mnYStart;
    std::string lastTab;

    // section to support dragging slider bar
    const float sliderBarWidth;
    bool sliderDragActive;
    size_t sliderIdx; ///< index in buttonInfo of slider being dragged
    wxPoint buttonDownPoint;
    float sliderDragValue;
    std::string buttonDownTab; ///< to detect if tab has been changed in middle of drag

    void OnControlUpdate(wxCommandEvent& event);
    void CloseAllLists();
    void UpdateButtonInfo();

	DECLARE_EVENT_TABLE()
};

#endif // _OPTIONSVIEW_H_

