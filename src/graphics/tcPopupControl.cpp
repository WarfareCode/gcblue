/**  
**  @file tcPopupControl.cpp
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

#include "tcPopupControl.h"
#include "AError.h"
#include "tcCommandQueue.h"
#include "tcSimPythonInterface.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif 

using namespace scriptinterface;


void tcPopupControl::BuildGameMenu()
{    
    mcGameMenu.Clear();
    //mcGameMenu.AddItem("Switch to scenedit mode", GC_TOGGLEEDIT);
    //mcGameMenu.AddItem("File", 0);

    // mcGameMenu.BeginSubMenu();
    //mcGameMenu.AddItem("Save scenario", GC_SAVESCEN);
    //mcGameMenu.AddItem("Load scenario", GC_LOADSCEN);

	
    //mcGameMenu.EndSubMenu();

    mcGameMenu.AddItem("Show briefing", GC_SHOWBRIEFING);
	mcGameMenu.AddItem("Show mission status", GC_SHOWMISSIONSTATUS);
	
	mcGameMenu.AddItem("Map mode", 0);
	mcGameMenu.BeginSubMenu();
	mcGameMenu.AddItem("Default map", "YellowBlueMap");
	mcGameMenu.AddItem("Copper map", "CopperMap");
	mcGameMenu.AddItem("Black-blue map", "BlackBlueMap");
	mcGameMenu.EndSubMenu();


	mcGameMenu.AddItem("Add graphic", 0);
	mcGameMenu.BeginSubMenu();
	mcGameMenu.AddItemUI("Dot", "AddMapText", "Datum");
	mcGameMenu.EndSubMenu();


	mcGameMenu.AddItem("Save game", GC_SAVEGAME);
    mcGameMenu.AddItem("Quit to start screen", GC_QUIT);
	mcGameMenu.AddItem("Quit to desktop", GC_QUITTODESKTOP);

    if (!tcPlatformInterface::GetDeveloperMode()) return;
    mcGameMenu.AddItem("Dev tools", 0);
    mcGameMenu.BeginSubMenu();

    mcGameMenu.AddItem("ToggleUserAlliance", "*ToggleUserAlliance");
    mcGameMenu.AddItem("Show Sonar Panel", "*ShowSonarPanel");
    mcGameMenu.AddItem("ReimportPython", "*ReimportPython");


    mcGameMenu.EndSubMenu();
}


void tcPopupControl::Draw() 
{
    if (!mbActive) return;
    
	//if (++drawCount % 2 != 0) return;
    StartDraw();

    Thaw();

    if (mpPanel != NULL)
	{
        mbRebuildMenu = (drawCount % 16) == 0; // periodically update panel display
	}
    
    if (mbRebuildMenu)
    {
        mbRebuildMenu = false;

        std::vector<unsigned int> selections;
        if (mpMenu != 0) mpMenu->GetCurrentSelections(selections);

        SetMenu();

        if (mpMenu != 0) mpMenu->SetCurrentSelections(selections);
    }

    if (mpMenu != NULL) mpMenu->Draw();
    if (mpPanel != NULL) mpPanel->Draw();

	FinishDraw();
}



void tcPopupControl::InitMenu() 
{
    mcGameMenu.Clear();
    BuildGameMenu();

    mcPlatformMenu.Clear();

    mcTrackMenu.Clear();

    mcGameEditMenu.Clear();
    
    // platform edit menu
    mcPlatformEditMenu.Clear();

    mcGroupEditMenu.Clear();

    // panel
    mcPanel.Clear();

}

void tcPopupControl::SetActive(bool abActive)
{
	if (abActive == false)
	{
		if (mpMenu != 0) mpMenu->ClearSelected();
		if (mpPanel != 0) mpPanel->ClearSelected();
	}

	tc3DWindow2::SetActive(abActive);
}

void tcPopupControl::SetBaseRenderBin(int n)
{
	tc3DWindow2::SetBaseRenderBin(n);
	tcMenu::SetSubmenuIconRenderBin(n + lineRenderBin);
}

void tcPopupControl::SetMenu(teMenuMode mode) 
{
    meMode = mode;
    SetMenu();
}

void tcPopupControl::SetMenu() 
{
    switch (meMode) {
      case MENUMODE_GAME:
          mpMenu = &mcGameMenu;
          mpPanel = NULL;
          mpPythonInterface->SelectGameMenu();
          BuildGameMenu();
          break;
      case MENUMODE_PLATFORM:
          mpMenu = &mcPlatformMenu;
          mpPanel = NULL;
          mpPythonInterface->AttachMenu(mpMenu);
          mpPythonInterface->SelectUnitMenu();
          mpPythonInterface->BuildPlatformMenu();         
          break;
	  case MENUMODE_GROUP:
          mpMenu = &mcPlatformMenu;
          mpPanel = NULL;
          mpPythonInterface->AttachMenu(mpMenu);
          mpPythonInterface->SelectGroupMenu();
          mpPythonInterface->BuildGroupMenu();    
		  break;
      case MENUMODE_TRACK:
          mpMenu = &mcTrackMenu;
          mpPanel = NULL;
          mpPythonInterface->AttachMenu(mpMenu);
          mpPythonInterface->SelectTrackMenu();
          mpPythonInterface->BuildTrackMenu();
          break;
      case MENUMODE_GAMEEDIT:
          mpMenu = &mcGameEditMenu;
          mpPanel = NULL;
		  mpPythonInterface->AttachMenu(mpMenu);
		  mpPythonInterface->SelectGameMenu();
          mpPythonInterface->BuildEditMenu();
          break;
      case MENUMODE_PLATFORMEDIT:
          mpMenu = &mcPlatformEditMenu;
          mpPanel = NULL;
		  mpPythonInterface->AttachMenu(mpMenu);
		  mpPythonInterface->SelectUnitMenu();
          mpPythonInterface->BuildPlatformEditMenu();
          break;
      case MENUMODE_GROUPEDIT:
          mpMenu = &mcPlatformEditMenu;
          mpPanel = NULL;
		  mpPythonInterface->AttachMenu(mpMenu);
		  mpPythonInterface->SelectGroupMenu();
          mpPythonInterface->BuildGroupEditMenu();
          break;
      case MENUMODE_FLIGHTPANEL:
          mpMenu = NULL;
          mpPanel = &mcPanel;
          mpPythonInterface->AttachPanel(mpPanel);
          mpPythonInterface->SelectFlightInterface();
          mpPythonInterface->BuildFlightPortPanel();
          // to avoid flicker during panel update
          mpPanel->UpdateSelection(wxRealPoint((float)mpointMouse.x,(float)mpointMouse.y)); 
          break;
      case MENUMODE_WEAPON:
          mpMenu = &mcWeaponMenu;
          mpPanel = NULL;
          mpPythonInterface->AttachMenu(mpMenu);
          mpPythonInterface->SelectWeaponMenu();
          mpPythonInterface->BuildWeaponMenu();
          break;
      case MENUMODE_WEAPONEDIT:
          mpMenu = &mcWeaponEditMenu;
          mpPanel = NULL;
		  mpPythonInterface->AttachMenu(mpMenu);
		  mpPythonInterface->SelectWeaponMenu();
          mpPythonInterface->BuildWeaponEditMenu();
          break;
      default:
          mpMenu = NULL;
          mpPanel = NULL;
          break;
    }
}

bool tcPopupControl::Track(wxPoint point) 
{
    if (mbActive == true) 
    {
        SetActive(false);
        return true;
    }

	drawCount = -1; // so draw occurs next frame

    SetActive(true);
	wxWindow::Raise();
    mpointUpperLeft = point;   
	mpointMouse = point;

    MoveWindow(point.x, point.y - tcMenu::yOffset); // yOffset to allow menu to draw above popup point when near screen bottom
    SetMenu();

    return true;
}

/**
* modified to handle panel, TODO system needs rework
* This is a mess.
*/
void tcPopupControl::OnLButtonDown(wxMouseEvent& event) 
{
    int builtInCommand = -1;
    std::string pythonCommand;
    std::string uiCommand;
    bool callCommand = false;

    if (!mbActive) {return;}

    if (mpCommandInterface == NULL) return;
    /* if buttondown is inside the menu, call Game::ProcessCommand */
    wxPoint p = event.GetPosition();
    wxRealPoint pointf((float)p.x,(float)p.y);
    std::string textParam = "";

    bool closeAfterCommand = true;

    if (mpMenu != NULL)
    {
        tsMenuData *pmd = mpMenu->ItemContainingPoint(pointf);
        if (pmd != NULL)
        {
            builtInCommand = pmd->mnCommand; // also used as parameter for python cmd
            pythonCommand = pmd->mzCommand;
            uiCommand = pmd->mzUserInput;
            textParam = pmd->textParam;
            callCommand = true;
            closeAfterCommand = pmd->closePopup;
        }
        else 
        {
            SetActive(false); // close the popup
            return;
        }
    }
    if ((!callCommand)&&(mpPanel != NULL))
    {
        tsItemData *item = mpPanel->ItemContainingPoint(pointf);
        if (item != NULL)
        {
            builtInCommand = item->cmd;
            pythonCommand = item->command;
            uiCommand = item->userInput;
            callCommand = true;
        }
        else 
        {
            SetActive(false);
            return;
        }
    }

    // another exception, if the command starts with * then skip python and
    // send it as a direct text command (all text following the '*' char)
    wxString pythonCommand2(pythonCommand.c_str());
    wxString directCommand = pythonCommand2.AfterFirst('*');
    if (directCommand.size() > 1)
    {
        mpCommandInterface->AddCommand(directCommand.c_str(), -1);
        SetActive(false); // close the menu
        return;
    }


    if (pythonCommand.length() > 0) 
    {
        if (uiCommand.length() > 0) 
        {
            mpCommandInterface->GetUserInput(pythonCommand.c_str(),
                uiCommand.c_str(), builtInCommand, textParam); // builtInCommand used as a param here
        }
        else 
        {
            if (builtInCommand == -1)
            {
                wxString textParam2(textParam.c_str());
                if (textParam2.Contains(",")) // assume this is an argument list if it has commas
                {
                    std::vector<long> idList;
                    mpCommandInterface->AddPythonCommandGeneral(pythonCommand.c_str(), textParam, idList);
                }
                else
                {
                    mpCommandInterface->AddPythonCommand(pythonCommand.c_str(), textParam);
                }
            }
            else
            {
                mpCommandInterface->AddPythonCommand(pythonCommand.c_str(), builtInCommand); // builtInCommand used as a param here
            }
        }
    }    
    else if (builtInCommand != 0) 
    {
        mpCommandInterface->AddCommand((teGameCommand)builtInCommand,0,0);
    }
    else 
    {
        return; // exit without closing menu
    }

    if ((mpPanel == 0) && (closeAfterCommand))
    {
        SetActive(false);
    }
    else
    {
        mbRebuildMenu = true;  
    }


    return;
}

/**
*
*/
void tcPopupControl::OnMouseMove(wxMouseEvent& event) 
{
    if (!mbActive) {return;}
    wxPoint point = event.GetPosition();

    mpointMouse = point;

    if (mpMenu != NULL) mpMenu->UpdateSelection(wxRealPoint((float)point.x,(float)point.y));
    if (mpPanel != NULL) mpPanel->UpdateSelection(wxRealPoint((float)point.x,(float)point.y));
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

tcPopupControl::tcPopupControl(wxWindow *parent, 
                         const wxPoint& pos, const wxSize& size, 
                         const wxString& name) :
tc3DWindow2(parent, pos, size, name),
drawCount(0)
{
    mpointUpperLeft.x = 250;
    mpointUpperLeft.y = 150;
    mbActive = false;  
    mbRebuildMenu = false;
    mpCommandInterface = NULL;
    mpPythonInterface = NULL;
    meMode = MENUMODE_GAME;

    mpMenu = &mcGameMenu;
    mpPanel = NULL;

    InitMenu();

    mbShowDebug = false;

	tcMenu::SetParentWindow(this);
	tcPanel::SetParentWindow(this);
}

tcPopupControl::~tcPopupControl() 
{

}
