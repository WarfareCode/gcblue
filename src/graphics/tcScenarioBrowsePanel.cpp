/**
** @file tcScenarioBrowsePanel.cpp
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

#include "stdwx.h"

#ifndef WX_PRECOMP
#include "wx/wx.h" 
#endif

#include "wx/dir.h"
#include "wx/gdicmn.h"
#include "tcTexture2D.h"
#include "tv_types.h"

#include "tcScenarioBrowsePanel.h"
#include "aerror.h"
#include "tcString.h"
#include "wxcommands.h"
#include "tcSimPythonInterface.h"
#include "tcScenarioInterface.h"
#include "common/tinyxml.h"
#include "network/tcMultiplayerInterface.h"

#include "tcGameSerializer.h"
#include "tcScenarioRandomizer.h"
#include "tcScrollBar.h"
#include "tcScenarioSelectView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif 


BEGIN_EVENT_TABLE(tcScenarioBrowsePanel, tc3DWindow2)
    EVT_COMMAND(-1, wxEVT_COMMAND_SCROLLBAR_UPDATED, tcScenarioBrowsePanel::OnScrollbarUpdated)
END_EVENT_TABLE()


tcScenarioBrowsePanel::wxScenarioTraverser::wxScenarioTraverser(
	std::vector<ScenarioInfo>& sInfo)
: info(sInfo)
{
}

/**
* Handles files encountered during directory traversal.
*
* If the file contains a double underscore or does not end in .py 
* then return with wxDIR_CONTINUE.
* Otherwise save the path up to the last \ in path 
* and the remainder (without the .py extension) in
* caption.
*/
wxDirTraverseResult tcScenarioBrowsePanel::wxScenarioTraverser
::OnFile(const wxString& filename)
{
    bool isScenarioFile = ((!filename.Contains(".pyc")) && (filename.Contains(".py"))) ||
                           filename.Contains(".dat");
    isScenarioFile = isScenarioFile && (!filename.Contains("__"));
                           
	if (!isScenarioFile)
	{
		return wxDIR_CONTINUE;
	}

	wxString scenarioDir(SCENARIO_PATH);
//	size_t scenarioDirLength = scenarioDir.size();

	int findIdx = filename.find(scenarioDir);
	if (findIdx == -1)
	{
		fprintf(stderr, "Corrupt scen structure\n");
		return wxDIR_CONTINUE;
	}
	
	findIdx += scenarioDir.size() + 1; // omit SCENARIO_PATH from pathString
	wxString pathString = filename.Mid(findIdx);

	wxString captionString;
	if (pathString.Contains("\\"))
	{
		findIdx = pathString.find_last_of("\\");
		captionString = pathString.Mid(findIdx+1);
	}
	else
	{
		captionString = pathString;
	}

    wxString extension = captionString.AfterLast('.');
	captionString = captionString.BeforeLast('.'); // remove extension

    if (extension == "py")
    {
	    pathString.Replace("\\", "."); // for python compatibility
    }

	ScenarioInfo scen;
	scen.path = pathString.GetData();
	scen.caption = captionString.GetData();
    scen.extension = extension.c_str();
	scen.drawState = ScenarioInfo::OFF;

	info.push_back(scen);

	return wxDIR_CONTINUE;
}

wxDirTraverseResult tcScenarioBrowsePanel::wxScenarioTraverser
						::OnDir(const wxString& dirname)
{
	// ignore CVS directories or dir names that start with underscore
	wxString dirTail = dirname.AfterLast('\\');
	if ((dirTail == "CVS")||(dirTail.at(0) == '_'))
	{
		return wxDIR_IGNORE;
	}

	// create a candidate parent, and then run traverser to find children
	ScenarioInfo parent;


	wxDir scenarioDir(dirname);
	wxScenarioTraverser traverser(parent.children);
	scenarioDir.Traverse(traverser);

	// if any children are found, add this parent to the ScenarioInfo member
	if (parent.children.size())
	{	
		parent.caption = dirname.AfterLast('\\');
		parent.showChildren = false;
		parent.drawState = ScenarioInfo::OFF;
		info.push_back(parent);
	}

	return wxDIR_IGNORE;
}




/**
* Scan scenario directories and populate scenInfo
*/
void tcScenarioBrowsePanel::BuildScenarioInfo()
{
	scenInfo.clear();

	wxString cwd = wxGetCwd();
	cwd += wxString::Format("\\%s", SCENARIO_PATH);

	wxDir scenarioDir(cwd);

	if (scenarioDir.IsOpened())
	{
		wxScenarioTraverser traverser(scenInfo);
		scenarioDir.Traverse(traverser);
	}
    else
    {
		scenInfo.clear();
        wxMessageBox("scenario directory does not exist!");
		return;
    }


}

void tcScenarioBrowsePanel::DrawScenarioDirectory(std::vector<ScenarioInfo>& info)
{
	Vec4 color;

	for (size_t n=0; n<info.size(); ++n)
	{
		ScenarioInfo& item = info[n];
		bool isDirectory = item.children.size();

		if (item.drawState == ScenarioInfo::ON) color.set(0.98f, 0.98f, 0.87f, 1.0f);
		else if (item.drawState == ScenarioInfo::OVER) color.set(0.52f, 0.52f, 0.90f, 1.0f);
		else color.set(0.58f, 0.52f, 0.58f,  1.0f);
        

		if (isDirectory)
		{
            directoryIcon->UpdateTextureInfo();
			DrawImageR(directoryIcon.get(), item.drawBox.x, 
				(item.drawBox.y-1), xIndent, 0.8f*yHeight, ALIGN_BOTTOM_LEFT);

			DrawTextR(item.caption.c_str(), item.drawBox.x + xIndent, 
				item.drawBox.y + item.drawBox.height - 3, defaultFont.get(), 
				color, fontSizeDirectory, LEFT_BASE_LINE);

			if (item.showChildren)
			{
				DrawScenarioDirectory(item.children);
			}
		}
		else
		{
			DrawTextR(item.caption.c_str(), item.drawBox.x, 
				item.drawBox.y + item.drawBox.height - 3,
				defaultFont.get(), color, fontSizeScenario, LEFT_BASE_LINE);
		}


	}
}

/**
* recursive method to find first matching scenario
*/
std::string tcScenarioBrowsePanel::FindMatchingScenario(const std::vector<ScenarioInfo>& info, 
		const std::string& scenarioName)
{
	static std::string notFound("");

	for (size_t k=0; k<info.size(); k++)
	{
		if (info[k].children.size() > 0)
		{
			std::string match = FindMatchingScenario(info[k].children, scenarioName);
			if (match.size() > 0) return match;
		}
		else
		{
			wxString filename = wxString(info[k].path.c_str()).BeforeLast('.'); // remove extension
			filename = filename.AfterLast('.');
			if (filename == scenarioName.c_str())
			{
				return info[k].path;
			}
		}
	}

	return notFound;
}


std::vector<ScenarioInfo>& tcScenarioBrowsePanel::GetScenarioInfo()
{
    return scenInfo;
}


/**
* 
*/
bool tcScenarioBrowsePanel::ProcessMouseClick(wxMouseEvent& mouseEvent, std::vector<ScenarioInfo>& info, wxPoint pos, bool startInEditMode)
{
	for (size_t n=0; n < info.size(); ++n)
	{
		wxRect r(info[n].drawBox.x, info[n].drawBox.y, 
					info[n].drawBox.width, info[n].drawBox.height);

		bool isDirectory = info[n].children.size();

		if (r.Contains(pos))
		{
			if (isDirectory)
			{
				info[n].showChildren = !info[n].showChildren;
			}
			else
			{
                // a little dangerous, could have unexpected destruction order and crash on exit
                wxASSERT(scenarioSelectView != 0);
                scenarioSelectView->LoadScenario(info[n].path, info[n].caption, startInEditMode);
			}
			return true;
		}
		if (isDirectory && (info[n].showChildren))
		{
			if (ProcessMouseClick(mouseEvent, info[n].children, pos, startInEditMode))
			{
				return true;
			}
		}
	}

    return false;
}


/**
* 
*/
bool tcScenarioBrowsePanel::ClickOnLoadedScenario(wxMouseEvent& mouseEvent, std::vector<ScenarioInfo>& info, wxPoint pos) const
{
	for (size_t n=0; n < info.size(); ++n)
	{
		wxRect r(info[n].drawBox.x, info[n].drawBox.y, 
					info[n].drawBox.width, info[n].drawBox.height);

		bool isDirectory = info[n].children.size();

		if (r.Contains(pos))
		{
			if (isDirectory)
			{
				return false;
			}
			else
			{
                wxString currentPath(loadedScenarioPath.c_str());
                
                return (currentPath.IsSameAs(info[n].path.c_str()));
			}
		}
		if (isDirectory && (info[n].showChildren))
		{
			if (ClickOnLoadedScenario(mouseEvent, info[n].children, pos)) return true;
		}
	}

    return false;
}


void tcScenarioBrowsePanel::SetActive(bool abActive)
{
	tc3DWindow2::SetActive(abActive);

	if (abActive)
	{
        wxRealPoint currentPos(basePosition);
        currentPos.y -= yOffset;
		UpdateDrawInfo(scenInfo, currentPos, true);
	}
}

void tcScenarioBrowsePanel::SetLoadedScenarioInfo(const std::string& caption, const std::string& path)
{
    loadedScenarioCaption = caption;
    loadedScenarioPath = path;
}

void tcScenarioBrowsePanel::SetScenarioSelectView(tcScenarioSelectView* ssv)
{
    scenarioSelectView = ssv;
}

/**
* Recursive method to check if child matches loaded scenario
* This is used to expand the correct parent directories to show the initial scenario loaded
* at the start of the game.
*/
bool tcScenarioBrowsePanel::IsChildScenarioLoaded(const std::vector<ScenarioInfo>& info) const
{
    if (loadedScenarioCaption.size() == 0) return false;

	for (size_t n=0; n < info.size(); ++n)
	{
		const ScenarioInfo& item = info[n];
		bool hasChildren = item.children.size();
		if (hasChildren)
		{
			if (IsChildScenarioLoaded(item.children)) return true;
		}
		else 
		{
            bool isLoaded = (item.caption == loadedScenarioCaption) && 
                ((loadedScenarioPath.size() == 0) || (item.path == loadedScenarioPath));

			if (isLoaded) return true;
		}
	}

	return false;
}

/**
* Recursive method to update drawing info of ScenarioInfo vector
*/
void tcScenarioBrowsePanel::UpdateDrawInfo(std::vector<ScenarioInfo>& info, 
										  wxRealPoint& currentPos, bool isTopLevel)
{
    float yStart = currentPos.y;

	currentPos.x += xIndent;
	for (size_t n=0; n < info.size(); ++n)
	{
		ScenarioInfo& item = info[n];

		item.drawBox.x = currentPos.x;
		item.drawBox.y = currentPos.y;
		item.drawBox.height = yHeight - 2;
		item.drawBox.width = xWidth;
		currentPos.y += yHeight;

		bool hasChildren = item.children.size();
		if (hasChildren)
		{
			// extend left side of draw box for icon
			item.drawBox.x -= xIndent;
			item.drawBox.width += xIndent;

			if (!item.showChildren && (IsChildScenarioLoaded(item.children)))
			{
				item.showChildren = true;
			}

			if (item.showChildren)
			{
				UpdateDrawInfo(item.children, currentPos, false);
			}
		}

		wxRect r(item.drawBox.x, item.drawBox.y, 
					item.drawBox.width, item.drawBox.height);

		int oldState = item.drawState;

        bool isLoaded = (item.caption == loadedScenarioCaption) && 
                ((loadedScenarioPath.size() == 0) || (item.path == loadedScenarioPath));

		if (isLoaded || (hasChildren && IsChildScenarioLoaded(item.children)))
		{
			item.drawState = ScenarioInfo::ON;
			if (item.drawState != oldState) tcSound::Get()->PlayEffect("Beep2");
			
		}
		else if (r.Contains(mousePosition))
		{
			item.drawState = ScenarioInfo::OVER;
			if (item.drawState != oldState) tcSound::Get()->PlayEffect("Thuck");
		}
		else
		{
			item.drawState = ScenarioInfo::OFF;
		}
	}
	currentPos.x -= xIndent;

    if (isTopLevel)
    {
        // update scroll bar
        float ySpan = currentPos.y - yStart;
        float maxSpan = float(mnHeight);

        scrollBar->SetBarFraction(0.9f*maxSpan / ySpan);
    }
}

/**
 * Initialize the tcScenarioBrowsePanel object.
 */
void tcScenarioBrowsePanel::Init() 
{
	BuildScenarioInfo();
    wxRealPoint currentPos(basePosition);
    currentPos.y -= yOffset;
	UpdateDrawInfo(scenInfo, currentPos, true);

    if (directoryIcon.get() == 0)
    {
	    directoryIcon = LoadTexture("folder.png");
    }
}

/**
 *
 */
void tcScenarioBrowsePanel::Draw()
{
    StartDraw();

	DrawScenarioDirectory(scenInfo);

	FinishDraw();
}


/**
 *
 */
void tcScenarioBrowsePanel::OnMouseMove(wxMouseEvent& event) 
{
	mousePosition = event.GetPosition();

    wxRealPoint currentPos(basePosition);
    currentPos.y -= yOffset;
	UpdateDrawInfo(scenInfo, currentPos, true);
}

/**
 *
 */
void tcScenarioBrowsePanel::OnLButtonDown(wxMouseEvent& event) 
{
    if (!mbActive) 
    {
        event.Skip();
        return;
    }

    mousePosition = event.GetPosition();

    bool startInEditMode = false; //event.ControlDown();

	if (ProcessMouseClick(event, scenInfo, mousePosition, startInEditMode))
	{
        wxRealPoint currentPos(basePosition);
        currentPos.y -= yOffset;
		UpdateDrawInfo(scenInfo, currentPos, true);
		return;
	}
}

void tcScenarioBrowsePanel::OnLButtonDClick(wxMouseEvent& event)
{
    if (!mbActive) 
    {
        event.Skip();
        return;
    }

    //mousePosition = event.GetPosition();

    //if (ClickOnLoadedScenario(event, scenInfo, mousePosition))
    //{
    //    wxASSERT(scenarioSelectView != 0);
    //    scenarioSelectView->SetEditMode(true);
    //}
}

void tcScenarioBrowsePanel::OnEnterWindow(wxMouseEvent& event)
{
    SetFocus(); // to receive mousewheel events
    event.Skip();
}

void tcScenarioBrowsePanel::OnLeaveWindow(wxMouseEvent& event)
{
    event.Skip();
}

void tcScenarioBrowsePanel::OnMouseWheel(wxMouseEvent& event)
{
    wxASSERT(scrollBar != 0);

    scrollBar->OnMouseWheel(event);
}

void tcScenarioBrowsePanel::OnScrollbarUpdated(wxCommandEvent& event)
{
    yOffset = 0.25 * float(event.GetExtraLong());

    wxRealPoint currentPos(basePosition);
    currentPos.y -= yOffset;

	UpdateDrawInfo(scenInfo, currentPos, true);
}

void tcScenarioBrowsePanel::OnSize(wxSizeEvent& event)
{
    tc3DWindow2::OnSize(event);
    
    wxASSERT(scrollBar != 0);
    if (scrollBar == 0) return;

    const int scrollBarWidth = 16;
    SetUseRenderSurface(true, scrollBarWidth+1);

    RemoveChild(scrollBar);
	scrollBar = new tcScrollBar(this, wxPoint(mnWidth-scrollBarWidth-1, 2), wxSize(scrollBarWidth, mnHeight-3));
	scrollBar->SetBackgroundAlpha(0.7f);
    scrollBar->SetUseRenderSurface(true);

    wxRealPoint currentPos(basePosition);
    currentPos.y -= yOffset;
	UpdateDrawInfo(scenInfo, currentPos, true);
}


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/**
*
*/
tcScenarioBrowsePanel::tcScenarioBrowsePanel(wxWindow *parent, 
                             const wxPoint& pos, const wxSize& size, const wxString& name,
                             tc3DWindow2* graphicsHost) 
                             : 
    tc3DWindow2(parent, pos, size, name, graphicsHost),
	xIndent(20),
	xStart(25),
	xWidth(120),
	yHeight(24),
	yHeightDir(32),
	yStart(20),
	fontSizeDirectory(15.0),
	fontSizeScenario(13.0),
	basePosition(xStart, yStart),
	loadedScenarioCaption(""),
    loadedScenarioPath(""),
    scenarioSelectView(0)
{

    SetBackgroundColor(Vec4(0, 0, 0, 0.01f)); // 0.01 so it doesn't get culled !?
    SetBackgroundDraw(true);

	// put gui window on top
	SetBaseRenderBin(hostParent->GetBaseRenderBin() + 10);
	wxWindow::Raise();

	const int scrollBarWidth = 16;
    SetUseRenderSurface(true, scrollBarWidth+1);


	scrollBar = new tcScrollBar(this, wxPoint(mnWidth-scrollBarWidth-1, 2), wxSize(scrollBarWidth, mnHeight-3));
	scrollBar->SetBackgroundAlpha(0.7f);
    scrollBar->SetUseRenderSurface(true);
    scrollBar->SetBarFraction(1.1f);

    // border is drawn in tcDatabaseViewer to work around scrollbar border issue
    SetBorderDraw(false);

    Init();
}



tcScenarioBrowsePanel::~tcScenarioBrowsePanel() 
{
}


