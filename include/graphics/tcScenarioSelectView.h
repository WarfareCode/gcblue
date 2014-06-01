/**  
**  @file tcScenarioSelectView.h
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

#ifndef _SCENARIOSELECTVIEW_H_
#define _SCENARIOSELECTVIEW_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "wx/wx.h" 
#include "wx/dir.h"

#include <boost/shared_ptr.hpp>


#include "tcXmlWindow.h"
#include "tcTabbedWindow.h"
#include "tcSound.h"
#include "tcSimState.h" // to load scenario
#include "aerror.h"
#include "tcString.h"
#include "ScenarioInfo.h"

#ifndef SCENARIO_PATH
#define SCENARIO_PATH "scenarios"
#endif


class tcTexture2D;
class tcBriefingView;
class tcMessageCenter;
class tcScenarioBrowsePanel;
class tcScenarioInfoWindow;
class tcAARViewer;
class wxFileName;

/** 
* GUI view for selecting scenarios and viewing briefing info
*/
class tcScenarioSelectView : public tcXmlWindow, public tcTabbedWindow
{
public:
	void Init();
	void Draw();
    void LoadScenario(const std::string& filePath, const std::string& caption, bool startInEditMode);
	bool LoadScenarioByName(const std::string& scenarioName, bool startInEditMode);
    void SetEditMode(bool state);

    void OnChar(wxKeyEvent& event);
    void OnKeyDown(wxKeyEvent& event);
	void OnLButtonDown(wxMouseEvent& event);
	void OnMouseMove(wxMouseEvent& event);
    void OnSize(wxSizeEvent& event);
    virtual void OnButtonCommand(wxCommandEvent& event);

    tcBriefingView* GetBriefingView() const;
    tcMessageCenter* GetMessageCenter() const;
    void SetGameStarted(bool state);
	virtual void SetActive(bool abActive);
    void SynchScenarioInfo();
    void RefreshBrowsePanel();

    tcScenarioSelectView(tc3DWindow2* parent,
        const wxPoint& pos, const wxSize& size, 
        const wxString& name);

	virtual ~tcScenarioSelectView();
private:
    enum {SHOW_HTML_BRIEFING = 300};
	const float xIndent;
	const float xStart;
	const float xWidth;
	const float yHeight; ///< vertical spacing between scen items
	const float yHeightDir; ///< vertical spacing between directory and next item
	const float yStart;
	const float fontSizeDirectory; ///< font size for directory name
	const float fontSizeScenario; ///< font size for scenario file name
	const wxRealPoint basePosition;
	wxPoint mousePosition;
    bool gameStarted;
    std::vector<tcButton*> sideSelectButtons;
    tcButton* showHtmlBriefingButton;

	tcOptions* mpOptions;

	std::string loadedScenarioCaption;

	int mnButtonWidth;
	int mnButtonHeight;

	tcSimState* mpSimState;
    tcBriefingView* briefingView;
    tcMessageCenter* messageCenter;
    tcScenarioBrowsePanel* browsePanel;
    tcScenarioInfoWindow* scenarioInfo;
    tcAARViewer* aarView;

	void BuildScenarioInfo();
    void DrawBriefing();

	wxArrayString GetListOfScenarioFiles();
	std::string FindMatchingScenario(const std::vector<ScenarioInfo>& info, 
		const std::string& scenarioName);
	void LogScenarioInfo(std::vector<ScenarioInfo>& info, int level);
    void UpdateSideSelectButtons();
    void EnableSideSelectButtons(bool state);
    void DrawScenarioHeader();
    void UpdateHtmlBriefingButton();
    bool GetHtmlFileName(wxFileName& fileName);


    DECLARE_EVENT_TABLE()

};




#endif