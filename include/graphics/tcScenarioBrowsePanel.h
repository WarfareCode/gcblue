/*  
**  @file tcScenarioBrowsePanel.h
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

#ifndef _SCENARIOBROWSEPANEL_H_
#define _SCENARIOBROWSEPANEL_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "wx/wx.h" 
#include "wx/dir.h"

#include <boost/shared_ptr.hpp>

#include "tc3DWindow2.h"
#include "tcSound.h"
#include "aerror.h"
#include "tcString.h"
#include "ScenarioInfo.h"

#ifndef SCENARIO_PATH
#define SCENARIO_PATH "scenarios"
#endif


class tcTexture2D;
class tcScrollBar;
class tcScenarioSelectView;

/** 
* Scrollable panel for browsing and selecting scenario
*/
class tcScenarioBrowsePanel : public tc3DWindow2
{
public:
	/**
	* Directory traverser to build scenario tree
	*/
	class wxScenarioTraverser : public wxDirTraverser
	{
	public:
		wxScenarioTraverser(std::vector<ScenarioInfo>& sInfo);

		wxDirTraverseResult OnFile(const wxString& filename);

		wxDirTraverseResult OnDir(const wxString& WXUNUSED(dirname));

	private:
		std::vector<ScenarioInfo>& info;
	};



    void Draw();

	void OnEnterWindow(wxMouseEvent& event);
	void OnLButtonDown(wxMouseEvent& event);
    void OnLButtonDClick(wxMouseEvent& event);
	void OnLeaveWindow(wxMouseEvent& event);
    void OnMouseMove(wxMouseEvent& event);
    void OnMouseWheel(wxMouseEvent& event);
	void OnScrollbarUpdated(wxCommandEvent& event);
    void OnSize(wxSizeEvent& event);

    std::vector<ScenarioInfo>& GetScenarioInfo();
    void SetLoadedScenarioInfo(const std::string& caption, const std::string& path);
    void SetScenarioSelectView(tcScenarioSelectView* ssv);

    virtual void SetActive(bool abActive);
    void Init();

	tcScenarioBrowsePanel(wxWindow* parent, const wxPoint& pos, const wxSize& size, 
										 const wxString& name="ScenarioBrowsePanel", tc3DWindow2* graphicsHost=0);
	virtual ~tcScenarioBrowsePanel();
private:
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

	boost::shared_ptr<tcTexture2D> directoryIcon;
	boost::shared_ptr<tcTexture2D> scenarioIcon;
	std::string loadedScenarioCaption;
    std::string loadedScenarioPath;

	int mnButtonWidth;
	int mnButtonHeight;

	std::vector<ScenarioInfo> scenInfo;

	bool mouseOver;
	tcScrollBar* scrollBar;
	float yOffset;

    tcScenarioSelectView* scenarioSelectView;

	void BuildScenarioInfo();
    void DrawBriefing();
	void DrawScenarioDirectory(std::vector<ScenarioInfo>& info);
	wxArrayString GetListOfScenarioFiles();
	bool IsChildScenarioLoaded(const std::vector<ScenarioInfo>& info) const;
	std::string FindMatchingScenario(const std::vector<ScenarioInfo>& info, 
		const std::string& scenarioName);
	bool ProcessMouseClick(wxMouseEvent& mouseEvent, std::vector<ScenarioInfo>& info, wxPoint pos, bool startInEditMode);
    bool ClickOnLoadedScenario(wxMouseEvent& mouseEvent, std::vector<ScenarioInfo>& info, wxPoint pos) const;
	void UpdateDrawInfo(std::vector<ScenarioInfo>& info, wxRealPoint& currentPos, bool isTopLevel);

    DECLARE_EVENT_TABLE()
};




#endif