/**
** @file tcScenarioSelectView.cpp
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
#include "wx/filename.h"
#include "wx/gdicmn.h"
#include "tcTexture2D.h"
#include "tcButton.h"
#include "tv_types.h"

#include "tcScenarioSelectView.h"
#include "aerror.h"
#include "tcString.h"
#include "wxcommands.h"
#include "tcSimPythonInterface.h"
#include "tcScenarioInterface.h"
#include "common/tinyxml.h"
#include "network/tcMultiplayerInterface.h"
#include "tcBriefingView.h"
#include "tcGameSerializer.h"
#include "tcMessageCenter.h"
#include "tcScenarioRandomizer.h"
#include "tcScenarioBrowsePanel.h"
#include "tcScenarioInfoWindow.h"
#include "tcAARViewer.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif 



BEGIN_EVENT_TABLE(tcScenarioSelectView, tcXmlWindow)
    EVT_COMMAND(-1, wxEVT_COMMAND_BUTTON_CLICKED, tcScenarioSelectView::OnButtonCommand)
END_EVENT_TABLE()


/**
* recursive method to find first matching scenario
*/
std::string tcScenarioSelectView::FindMatchingScenario(const std::vector<ScenarioInfo>& info, 
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


tcBriefingView* tcScenarioSelectView::GetBriefingView() const
{
    return briefingView;
}

tcMessageCenter* tcScenarioSelectView::GetMessageCenter() const
{
    return messageCenter;
}

/**
* Loads scenario with path+filename of SCENARIO_PATH\<filePath>
*/
void tcScenarioSelectView::LoadScenario(const std::string& filePath, const std::string& caption, bool startInEditMode)
{
    tcGameObject::SetEditMode(false);

	using network::tcMultiplayerInterface;

    if (gameStarted)
    {
        return; // no scenario changes after game started
    }

	if (mpSimState->IsMultiplayerClient())
	{
        wxString scenarioName = filePath;
        scenarioName = scenarioName.BeforeLast('.');
        scenarioName = scenarioName.AfterLast('.');

        wxString scenarioCommand;
        scenarioCommand.Printf("/scenario %s", scenarioName.c_str());

        tcMultiplayerInterface* multiplayerInterface = tcMultiplayerInterface::Get();
        multiplayerInterface->BroadcastChatText(scenarioCommand.ToStdString());

		return; // don't load scenarios directly as multiplayer client
	}

    tcSimPythonInterface* pythonInterface =	tcSimPythonInterface::Get();

    // if this scenario is already loaded, then just adjust SetEditMode and return, don't reload it
    std::string loadedFilePath = tcOptions::Get()->GetOptionString("LastScenarioPath");
    if (mpSimState->msScenarioInfo.mbLoaded && (loadedScenarioCaption == caption) && (loadedFilePath == filePath))
    {
        if (startInEditMode && !pythonInterface->GetScenarioInterface()->IsScenarioLocked())
        {
            tcGameObject::SetEditMode(true);
        }
        else
        {
            tcGameObject::SetEditMode(false);
        }
        return;
    }

    
	std::string totalPath = SCENARIO_PATH;
	totalPath += "\\"; // generalize this for Linux?
	totalPath += filePath;


	
    // clear briefing in case scenario fails to set it
	pythonInterface->GetScenarioInterface()->ClearSimpleBriefing(); 

    wxString extension = wxString(filePath.c_str()).AfterLast('.');

    tcScenarioRandomizer::Get()->Clear();


    if (extension == "py")
    {
        wxSetCursor(*wxHOURGLASS_CURSOR);
        pythonInterface->LoadScenario(totalPath.c_str(), filePath.c_str());
        wxSetCursor(wxNullCursor);
    }
    else if (extension == "dat")
    {
        tcGameSerializer gameSerializer;

        wxSetCursor(*wxHOURGLASS_CURSOR);
        try
        {
            gameSerializer.LoadFromBinary(totalPath.c_str());
        }
        catch (...)
        {
            wxMessageBox("Error loading scenario, file may be corrupt.", "Scenario Load Error", wxICON_ERROR);
        }
        wxSetCursor(wxNullCursor);
    }
    else
    {
        fprintf(stderr, "tcScenarioSelectView::LoadScenario - Bad extension (%s)\n",
            extension.c_str());
        return;
    }



	if (mpSimState->msScenarioInfo.mbLoaded)
	{
		loadedScenarioCaption = caption;
        browsePanel->SetLoadedScenarioInfo(loadedScenarioCaption, filePath);

		tcOptions::Get()->SetOptionString("LastScenarioPath", filePath.c_str());
		tcOptions::Get()->SetOptionString("LastScenarioName", caption.c_str());
		tcOptions::Get()->SetOptionString("LastScenarioExtension", extension.c_str());

        wxString filePathToSave(filePath.c_str());
        filePathToSave = filePathToSave.BeforeLast('.'); // remove extension
        filePathToSave.Replace(".","/");
        filePathToSave = wxString("scenarios/") + filePathToSave + wxString(".") + extension;
        wxFileName fileName(filePathToSave);
        bool fileExists = fileName.FileExists();
        wxASSERT(fileExists);
        tcOptions::Get()->SetOptionString("ScenarioSavePath", filePathToSave.c_str());

		if (mpSimState->IsMultiplayerServer())
		{
            tcMultiplayerInterface* multiplayerInterface = tcMultiplayerInterface::Get();

			multiplayerInterface->ResetGame();
			multiplayerInterface->BroadcastScenarioInfo();
            multiplayerInterface->SetAllReadyState(false);

            mpSimState->PreloadScenarioDatabase();
            multiplayerInterface->BroadcastDatabaseInfo();
		}

        if (startInEditMode && !pythonInterface->GetScenarioInterface()->IsScenarioLocked())
        {
            tcGameObject::SetEditMode(true);
        }
	}
	else
	{
		wxString s = 
			wxString::Format("Error in scenario %s (File may be missing, file name may have space in it, or error in scenario). "
			"Check log/pyerr.txt for details.", 
			totalPath.c_str());
		
		// suppress message box if multiplayer server
		if (!mpSimState->IsMultiplayerActive())
		{
			wxMessageBox(s.c_str(),"Error",wxICON_ERROR);
		}
	}

    wxWindow::Freeze();
    UpdateSideSelectButtons();
    UpdateHtmlBriefingButton();
    wxWindow::Thaw();
}

/**
* This method searches the scenario directories and loads the first scenario with
* name matching scenarioName
*/
bool tcScenarioSelectView::LoadScenarioByName(const std::string& scenarioName, bool startInEditMode)
{
    std::vector<ScenarioInfo>& scenInfo = browsePanel->GetScenarioInfo();

	std::string match = FindMatchingScenario(scenInfo, scenarioName);

	LoadScenario(match, scenarioName, startInEditMode);
	
	return (match.size() > 3) && (mpSimState->msScenarioInfo.mbLoaded);
	
}

/**
* recursive method to write ScenarioInfo vector to stdout
*/
void tcScenarioSelectView::LogScenarioInfo(std::vector<ScenarioInfo>& info, int level)
{


	for (size_t ind=0; ind<info.size(); ++ind)
	{
		for (int i=0; i<level; ++i)
		{
			fprintf(stdout, "  ");
		}
		fprintf(stdout, "%s (%s)\n", info[ind].caption.c_str(), info[ind].path.c_str());
		if (info[ind].children.size())
		{
			LogScenarioInfo(info[ind].children, level + 1);
		}
	}


}

void tcScenarioSelectView::RefreshBrowsePanel()
{
    wxASSERT(browsePanel != 0);
    browsePanel->Init();
}


void tcScenarioSelectView::SetActive(bool abActive)
{
    bool refreshBrowse = false;
    if (abActive && (!tc3DWindow2::IsActive()))
    {
        refreshBrowse = true;
    }

	tc3DWindow2::SetActive(abActive);

    if (refreshBrowse)
    {
        RefreshBrowsePanel();
    }

    UpdateHtmlBriefingButton(); // to make show/hide state correct
}

void tcScenarioSelectView::SetEditMode(bool state)
{
    if (!mpSimState->IsScenarioLoaded() || (mpSimState->GetTime() > 0))
    {
        return;
    }

	if (mpSimState->IsMultiplayerClient())
	{
		return;
	}

    if (state)
    {
        tcSimPythonInterface* pythonInterface =	tcSimPythonInterface::Get();
        if (!pythonInterface->GetScenarioInterface()->IsScenarioLocked())
        {
            tcGameObject::SetEditMode(true);
        }
    }
    else
    {
        tcGameObject::SetEditMode(false);
    }

}

void tcScenarioSelectView::SetGameStarted(bool state)
{
    gameStarted = state;
}

/**
* Used for multiplayer to load scenario name and info from simstate
*/
void tcScenarioSelectView::SynchScenarioInfo()
{
    wxString scenarioName(mpSimState->GetScenarioName());
    scenarioName = scenarioName.BeforeFirst(' ');

    std::vector<ScenarioInfo>& scenInfo = browsePanel->GetScenarioInfo();
    loadedScenarioCaption = FindMatchingScenario(scenInfo, scenarioName.ToStdString());

    // for MP, don't know full path so set empty for now (client will highlight all scenarios with matching name)
    browsePanel->SetLoadedScenarioInfo(loadedScenarioCaption, ""); 
}



/**
 * Initialize the tcScenarioSelectView object.
 */
void tcScenarioSelectView::Init()
{
    if (briefingView == 0)
    {
        briefingView = new tcBriefingView(this, wxPoint(0, 0), wxSize(mnWidth, mnHeight), "EmbeddedSimpleBrief", this);
        briefingView->SetCharPropagationLevel(1);
        briefingView->SetActive(false);
    }

    if (messageCenter == 0)
    {
        messageCenter = new tcMessageCenter(this,wxPoint(0, 0), wxSize(mnWidth, mnHeight), "MessageCenter", this);
        messageCenter->SetCharPropagationLevel(1);
    }

    if (aarView == 0)
    {
        aarView = new tcAARViewer(this, wxPoint(0, 0), wxSize(mnWidth, mnHeight), "AARView", this);
    }
    else
    {
        aarView->BuildBrowseInfo();
    }

    if (GetTabCount() == 0)
    {
        std::vector<ScenarioInfo>& scenInfo = browsePanel->GetScenarioInfo();
        LogScenarioInfo(scenInfo, 0);
        AddTab("Select");
        AddTab("Briefing");
        AddTab("Messages");
        AddTab("AAR");

        SetTab("Select");
    }
}

/**
 *
 */
void tcScenarioSelectView::Draw()
{
    static int nTestCount = 0;

    //if (gameStarted)
    //{
    //    SetTab("Briefing");
    //}

    std::string activeTab(GetTab());

    if (activeTab == "Briefing")
    {
        browsePanel->SetActive(false);
        messageCenter->SetActive(false);
        briefingView->SetActive(true);
        aarView->SetActive(false);
        scenarioInfo->SetActive(false);
        EnableSideSelectButtons(false);
        StartDraw();
        FinishDraw();
        return;
    }
    else if (activeTab == "Messages")
    {
        browsePanel->SetActive(false);
        briefingView->SetActive(false);
        aarView->SetActive(false);
        messageCenter->SetActive(true);
        scenarioInfo->SetActive(false);
        EnableSideSelectButtons(false);
        StartDraw();
        FinishDraw();
        return;
    }
    else if (activeTab == "AAR")
    {
        browsePanel->SetActive(false);
        briefingView->SetActive(false);
        messageCenter->SetActive(false);
        scenarioInfo->SetActive(false);
        aarView->SetActive(true);
        EnableSideSelectButtons(false);
        StartDraw();
        FinishDraw();
        return;
    }
    else
    {
        browsePanel->SetActive(true);
        scenarioInfo->SetActive(true);
        EnableSideSelectButtons(true);
        briefingView->SetActive(false);
        messageCenter->SetActive(false);
        aarView->SetActive(false);
    }

    if (mpSimState->IsMultiplayerClient())
    {
        SynchScenarioInfo();
        // kind of a hack to get scenario selection to change in client
    }

    StartDraw();

    DrawScenarioHeader();

	FinishDraw();
}

void tcScenarioSelectView::DrawScenarioHeader()
{
    Vec4 color;
    /*** Draw line ***/
    if (mpSimState->msScenarioInfo.mbLoaded) 
	{
        color.set(0.68f, 0.98f, 1.0f, 1.0f);
    }
    else 
	{
		color.set(0.4f, 0.52f, 0.52f, 1.0f);
    } 

    const float nMargin = 50;

    DrawLineR(nMargin, (yStart-nMargin), mnWidth-nMargin, 
		(yStart-nMargin), color);

    /*** Draw caption ***/
    tcString caption;
    if (mpSimState->msScenarioInfo.mbLoaded) 
	{
        if (!tcGameObject::IsEditMode())
        {
            caption.Format("Scenario loaded   (%s)",mpSimState->msScenarioInfo.mzName);
            color.set(0.68f, 0.98f, 1.0f, 1.0f);
        }
        else
        {
            caption.Format("Scenario loaded (%s) EDIT MODE",mpSimState->msScenarioInfo.mzName);
            color.set(0.5f, 0.6f, 1.0f, 1.0f);
        }
    }
    else 
	{
        caption = "Please select a scenario.";
		color.set(0.4f, 0.52f, 0.52f, 1.0f);
    }

    DrawTextR(caption.GetBuffer(), nMargin, (yStart-nMargin), 
		defaultFont.get(), color, 16.0f, LEFT_BASE_LINE);

    // if game has started, draw current time
    if (mpSimState->GetTime() > 0)
    {
        tcDateTime dateTime = mpSimState->GetDateTime();

        wxString s;

        int year = dateTime.GetYear();
        int month = dateTime.GetMonth();
        int day = dateTime.GetDay();
        int hoursZulu = dateTime.GetHour();
        int minutes = dateTime.GetMinute();
        int seconds = dateTime.GetSecond();
        
        s.Printf("%4d/%02d/%02d %02d:%02d:%02dZ ", year, month, day, 
            hoursZulu, minutes, seconds);
    
        // measure the scenario name size so we can put text to the right of it
        /*wxSize scenNameSize;
	    MeasureText(defaultFont.get(), 16.0f, mpSimState->GetScenarioName(), scenNameSize);*/

        DrawTextR(s.c_str(), 50.0f, 90.0f, 
            defaultFont.get(), Vec4(1, 1, 1, 1), 14.0f, LEFT_BASE_LINE);
    }


}

void tcScenarioSelectView::EnableSideSelectButtons(bool state)
{
    for (size_t n=0; n<sideSelectButtons.size(); n++)
    {
        sideSelectButtons[n]->SetActive(state);
    }
}

void tcScenarioSelectView::OnButtonCommand(wxCommandEvent& event)
{
    std::string activeTab(GetTab());
    int buttonId = event.GetId();

    if (buttonId == SHOW_HTML_BRIEFING)
    {
        wxFileName htmlFileName;
        bool found = GetHtmlFileName(htmlFileName);
        if (found)
        {
            htmlFileName.Normalize();
            wxLaunchDefaultBrowser(htmlFileName.GetFullPath());
        }
        return;
    }


    if ((activeTab != "Select") || gameStarted)
    {
        event.Skip();
        return;
    }



    if ((buttonId < 0) || (buttonId >= tcAllianceInfo::MAX_ALLIANCES))
    {
        event.Skip();
        return;
    }

    tcUserInfo::Get()->SetOwnAlliance(unsigned char(buttonId));

    UpdateSideSelectButtons();
}

void tcScenarioSelectView::OnChar(wxKeyEvent& event)
{
    event.Skip();
    event.ResumePropagation(1);
}

void tcScenarioSelectView::OnKeyDown(wxKeyEvent& event)
{
    event.Skip();
    event.ResumePropagation(1);
}

void tcScenarioSelectView::OnLButtonDown(wxMouseEvent& event) 
{
    if (!mbActive) 
    {
        event.Skip();
        return;
    }

    mousePosition = event.GetPosition();
}

void tcScenarioSelectView::OnMouseMove(wxMouseEvent& event) 
{
	mousePosition = event.GetPosition();
}
void tcScenarioSelectView::OnSize(wxSizeEvent& event)
{
    tcXmlWindow::OnSize(event);
    
    browsePanel->SetSize(325, mnHeight-125);
	
	scenarioInfo->SetSize(345, 140, mnWidth-345-10, mnHeight-140-20);

	briefingView->SetSize(0, 0, mnWidth, mnHeight);

	aarView->SetSize(0, 0, mnWidth, mnHeight);
}

void tcScenarioSelectView::UpdateSideSelectButtons()
{
    if (gameStarted) return;

    for (size_t n=0; n<sideSelectButtons.size(); n++)
    {
        sideSelectButtons[n]->SetActive(false);
        RemoveChild(sideSelectButtons[n]);
    }
    sideSelectButtons.clear();

    if (!mpSimState->msScenarioInfo.mbLoaded) return;

    wxWindow::Freeze();

    tcUserInfo* userInfo = tcUserInfo::Get();
    tcAllianceInfo* allianceInfo = tcAllianceInfo::Get();
    std::vector<unsigned char> allianceList = allianceInfo->GetAllianceList();
    
    wxASSERT(browsePanel != 0);
    int buttonLeft = browsePanel->GetSize().GetWidth() + 30;


    wxPoint buttonPos(buttonLeft, yStart-40);
    wxSize buttonSize(60, 15);
    wxSize buttonSpacing(100, 0);

    tcDatabase* database = tcDatabase::Get();

    for (size_t n=0; n<allianceList.size(); n++)
    {
        boost::shared_ptr<tcTexture2D> tex = database->GetEnsignShared(allianceInfo->GetAllianceDefaultCountry(allianceList[n]));
        wxSize imageSize(tex->Width()/2, tex->Height()/2);

        tcButton* button = new tcButton(this, buttonPos, imageSize, "");
       
        button->SetMouseOverCaption(allianceInfo->GetAllianceName(allianceList[n]));
        button->SetMouseOverCaptionPosition(wxPoint(0, -10));
        button->SetMouseOverCaptionFontSize(12.0f);
        button->SetMouseOverCaptionAlignment(LEFT_CENTER);
        button->SetShowCaptionWhenOn(true);
        button->SetCommand(allianceList[n]);
        button->SetFillColors(Vec4(0.3f, 0.3f, 0.3f, 1.0f), Vec4(0.5f, 0.5f, 1.0f, 1.0f), Vec4(1.0f, 1.0f, 1.0f, 1.0f));
        button->SetApplyColorToImage(true);

        button->SetFontSize(10);
        button->LoadImages(tex, tex, tex, tex);
        button->SetOn(userInfo->IsOwnAlliance(allianceList[n]));

        button->SetInteractive(allianceInfo->IsAlliancePlayable(allianceList[n])); // don't allow selection of unplayable alliances

        sideSelectButtons.push_back(button);

        buttonPos += buttonSpacing;
    }

    wxWindow::Thaw();
}

/**
* @return true if html file found, false otherwise
* @param fileName html file name and path associated with current loaded scenario
*/
bool tcScenarioSelectView::GetHtmlFileName(wxFileName& fileName)
{
    if (!mpSimState->msScenarioInfo.mbLoaded) return false;

    // path has form: SinglePlayer.ColdWar.Backfires.py
    wxString loadedFilePath = tcOptions::Get()->GetOptionString("LastScenarioPath");
    loadedFilePath.Replace(".py", "");
    loadedFilePath.Replace(".", "/");
    loadedFilePath.Prepend("scenarios/");
    loadedFilePath += ".html";

    fileName = wxFileName(loadedFilePath);
    bool readable = fileName.IsFileReadable();
    return readable;
}

void tcScenarioSelectView::UpdateHtmlBriefingButton()
{
    if (showHtmlBriefingButton == 0)
    {
        int buttonLeft = browsePanel->GetSize().GetWidth() + scenarioInfo->GetSize().GetWidth() - 60;
        wxPoint buttonPos(buttonLeft, yStart-40);
        wxSize buttonSize(32, 32);

        showHtmlBriefingButton = new tcButton(this, buttonPos, buttonSize, "ShowHtmlButton");
        showHtmlBriefingButton->SetCommand(SHOW_HTML_BRIEFING);

        showHtmlBriefingButton->SetMouseOverCaption("Show HTML Briefing");
        showHtmlBriefingButton->SetMouseOverCaptionPosition(wxPoint(0, -10));
        showHtmlBriefingButton->SetMouseOverCaptionFontSize(12.0f);
        showHtmlBriefingButton->SetMouseOverCaptionAlignment(CENTER_CENTER);

        showHtmlBriefingButton->LoadImages("show_html.png", "show_html.png", "show_html_over.png", "show_html_over.png");
    }

    wxFileName htmlFileName;
    bool briefingExists = GetHtmlFileName(htmlFileName);
    if (briefingExists)
    {
        showHtmlBriefingButton->SetActive(true);
    }
    else
    {
        showHtmlBriefingButton->SetActive(false);
    }

}


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


tcScenarioSelectView::tcScenarioSelectView(tc3DWindow2* parent,
        const wxPoint& pos, const wxSize& size, 
        const wxString& name) 
        : 
    tcXmlWindow(parent, pos, size, "xml/scenarioselect_view.xml", name, parent),
	xIndent(15),
	xStart(55),
	xWidth(120),
	yHeight(24),
	yHeightDir(32),
	yStart(120.0f),
	fontSizeDirectory(15.0),
	fontSizeScenario(13.0),
	basePosition(xStart, yStart),
	loadedScenarioCaption(""),
    briefingView(0),
    messageCenter(0),
    aarView(0),
    gameStarted(false),
    showHtmlBriefingButton(0)
{
    //LoadBackgroundImage("start_background_plain.jpg");

    if (config)
    {
//        AddXMLControls();
    }
    else
    {
        std::cerr << "tcScenarioSelectView::tcScenarioSelectView - "
			"NULL xml config node\n";
        return;
    }

    TiXmlNode* root = config->FirstChild("Window");
    if (!root)
    {
        std::cerr << "tcScenarioSelectView::tcScenarioSelectView - "
			"Missing top level <Window> tag\n";
        return;
    }


	mpOptions = tcOptions::Get();
	mpSimState = tcSimState::Get();

    SetBorderDraw(false);


    browsePanel = new tcScenarioBrowsePanel(this, wxPoint(5, 100), wxSize(325, mnHeight-125), "ScenarioBrowsePanel", this);

    browsePanel->SetScenarioSelectView(this);

    scenarioInfo = new tcScenarioInfoWindow(wxPoint(345, 140), "xml/scenario_info.xml", "ScenarioInfo", this);

    Init();
}

tcScenarioSelectView::~tcScenarioSelectView() 
{
}


