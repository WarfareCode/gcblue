/**  
**  @file tcStartView.cpp
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


#include "stdwx.h" // precompiled header file

#ifndef WX_PRECOMP
#include "wx/wx.h" 
#endif

#include "tcStartView.h"

#include "tcTexture2D.h"

#include "tcSound.h"
#include "tcOptions.h"
#include "AError.h"
#include "tcTime.h"
#include "wxcommands.h"
#include "tcTVEngine.h"

#include "tcScenarioSelectView.h"
#include "tcOptionsView.h"
#include "tcOptionsView2.h"
#include "tcDatabaseViewer.h"
#include "tcCreditView.h"
#include "tcNetworkView.h"
#include "tcTabHeader.h"
#include "tc3DViewer.h"
#include "tcSimState.h" // to switch button captions for MP mode

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_EVENT_TABLE(tcStartView, tc3DWindow2)
EVT_COMMAND(ID_TABCLICKED, wxEVT_COMMAND_BUTTON_CLICKED , tcStartView::OnTab)
EVT_CHAR(tcStartView::OnChar)
END_EVENT_TABLE()



bool tcStartView::Init() 
{
	wxString s;

    for(int i=0; i < N_START_BUTTONS; i++) 
    {
        tsButtonInfo *pButton = &maButton[i];

		s = wxString::Format("start%d%s", i, "_off.jpg");
        
		pButton->mpiButtonOff = boost::shared_ptr<tcTexture2D>(LoadTexture(s.c_str()));
        pButton->mnButtonWidth = 150; //buttonSize;
        pButton->mnButtonHeight = 30; //buttonSize / 4;

        s = wxString::Format("start%d%s", i, "_on.jpg");
        pButton->mpiButtonOver = boost::shared_ptr<tcTexture2D>(LoadTexture(s.c_str()));

        s = wxString::Format("start%d%s", i, "_on.jpg");
        pButton->mpiButtonOn = boost::shared_ptr<tcTexture2D>(LoadTexture(s.c_str()));

        pButton->subWindow = 0;
    }

    maButton[0].altText = "SCENARIO";
    maButton[0].mzCaption = "Select scenario";
    maButton[0].paneName = "Scenario";

    maButton[1].altText = "OPTIONS";
    maButton[1].mzCaption = "Configure game options";
    maButton[1].paneName = "Options";

    maButton[2].altText = "DATABASE";
    maButton[2].mzCaption = "Browse database";
    maButton[2].paneName = "Database";

    maButton[3].altText = "CREDITS";
    maButton[3].mzCaption = "Show credits";
    maButton[3].paneName = "Credits";

    maButton[4].altText = "MULTIPLAYER";
    maButton[4].mzCaption = "Multiplayer configuration";
    maButton[4].paneName = "Multiplayer";

    maButton[5].altText = "START GAME";
    maButton[5].mzCaption = "Start the game";
    maButton[5].paneName = "Play";

    maButton[6].altText = "EDIT SCEN";
    maButton[6].mzCaption = "Edit scenario";
    maButton[6].paneName = "Edit";

    maButton[7].altText = "CREATE SCEN";
    maButton[7].mzCaption = "Create new scenario";
    maButton[7].paneName = "Create";

    maButton[8].altText = "QUIT";
    maButton[8].mzCaption = "Quit the game";
    maButton[8].paneName = "Quit";

    PlaceButtons();


    rightPane = new tc3DWindow2(this, panePosition, paneSize, "StartPane");
    rightPane->SetCharPropagationLevel(1);
    rightPane->SetBackgroundColor(Vec4(0.15f, 0.15f, 0.2f, 0.9f));

    rightPane->SetBackgroundDraw(true);
    rightPane->SetBorderDraw(true);
    rightPane->SetUseRenderSurface(true);
    AddChild(rightPane);

    tabHeader = new tcTabHeader(this, tabPosition, tabSize, "TabHeader");
    //tabHeader->SetBackgroundColor(Vec4(0.1f, 0.1f, 0.3f, 0.9f));
    //tabHeader->SetBackgroundDraw(true);
    //tabHeader->SetBorderDraw(true);
    AddChild(tabHeader);
    
    // Init sub windows
    tsButtonInfo* button = &maButton[0];
    scenarioSelectView = new tcScenarioSelectView(rightPane, wxPoint(0, 0), paneSize, "EmbeddedScenarioSelect");

    scenarioSelectView->SetCharPropagationLevel(1);
    button->subWindow = scenarioSelectView;
    button->subWindow->SetActive(false);


    button = &maButton[1];
    button->subWindow = new tcOptionsView2(rightPane, wxPoint(0, 0), paneSize, "EmbeddedOptions");
    button->subWindow->SetCharPropagationLevel(1);
    button->subWindow->SetActive(false);

    button = &maButton[2];
    databaseViewer = new tcDatabaseViewer(rightPane, wxPoint(0, 0), paneSize, "EmbeddedDatabaseViewer");
    button->subWindow = databaseViewer;
    button->subWindow->SetCharPropagationLevel(1);
    button->subWindow->SetActive(false);

    button = &maButton[3];
    button->subWindow = new tcCreditView(rightPane, wxPoint(0, 0), paneSize, "EmbeddedCredits");
    button->subWindow->SetCharPropagationLevel(1);
    button->subWindow->SetActive(false);

    button = &maButton[4];
    networkView = new tcNetworkView(rightPane, wxPoint(0, 0), paneSize, "EmbeddedMultiplayer");
    button->subWindow = networkView;
    button->subWindow->SetCharPropagationLevel(1);
    button->subWindow->SetActive(false);

    SetPane(0);
	
    return true;
}

void tcStartView::Draw() 
{
    StartDraw();

    if (!tcGameObject::IsEditMode())
    {
        if (!gameStarted)
        {
            maButton[5].altText = "START GAME";
            maButton[5].mzCaption = "Start the game";
        }
        else
        {
            maButton[5].altText = "RETURN";
            maButton[5].mzCaption = "Return to the game";
        }
    }
    else
    {
        maButton[5].altText = "RETURN";
        maButton[5].mzCaption = "Return to edit scenario";
    }

    /*** Draw buttons ***/   

    //for(int i=0; i<N_START_BUTTONS; i++) 
    //{
    //    DrawButtonLine(i);
    //}

    for(int i=0; i<N_START_BUTTONS; i++) 
    {
        DrawButton(i);
    }

    Vec4 color(1.0f, 1.0f, 0.6f, 0.5f);

    //unsigned int count = tcTime::Get()->Get30HzCount();
    //float alpha = 0.4f + 0.4f * sinf(0.01f * float(count));
    //color.w = alpha;
    

    DrawTextR(versionString.c_str(), 25.0, float(mnHeight)-25.0f, 
        GetBoldFont(), color, 10.0, LEFT_CENTER);

	FinishDraw();


    //if (mnActiveButton != 2)
    //{
    //    viewer->SetDatabaseView(false);
    //}
    //else
    //{
    //    viewer->SetDatabaseView(true);
    //}
}

void tcStartView::DrawButton(int anButton) 
{
	tcTexture2D* pButtonImage;
    int x, y, nState;

    if ((anButton < 0)||(anButton >= N_START_BUTTONS)) {return;}

	Vec4 captionColor(1, 1, 1, 1);
    Vec4 textOffColor(0.6f, 0.6f, 0.3f, 1.0f);
    Vec4 textOnColor(1.0f, 1.0f, 0.7f, 1.0f);

    tsButtonInfo *pButton = &maButton[anButton];
    nState = pButton->mnState;
    if (nState == 0) {pButtonImage = pButton->mpiButtonOff.get();}
    else {pButtonImage = (nState == 1) ? pButton->mpiButtonOver.get() : 
				pButton->mpiButtonOn.get();}

    x = pButton->mnButtonX + pButton->mnButtonWidth/2;
    y = mnHeight - pButton->mnButtonY - pButton->mnButtonHeight/2;

    unsigned t = tcTime::Get()->Get30HzCount();
    unsigned dt = t - pButton->timeStamp;

    if (nState == 0)
    {
        Vec4 col = textOffColor;

        if (dt < buttonFadeTime)
        {        
            float alpha = float(dt) / float(buttonFadeTime);
            col = textOffColor*alpha + textOnColor*(1.0-alpha);
        }

        DrawText(pButton->altText.c_str(), x, y, boldFont.get(), col, 20.0, CENTER_CENTER);
    }
    else
    {   
        Vec4 col = textOnColor;

        if ((nState == 1) && (dt < buttonFadeTime))
        {        
            float alpha = float(dt) / float(buttonFadeTime);
            col = textOnColor*alpha + textOffColor*(1.0-alpha);
        }

        DrawText(pButton->altText.c_str(), x, y, boldFont.get(), col, 20.0, CENTER_CENTER);

        float textx = (float)pButton->mnTextX;
        float texty = float(mnHeight) - float(pButton->mnTextY)-5;

        DrawText(pButton->mzCaption.GetBuffer(), textx + 0.5f*float(pButton->mnButtonWidth), texty, defaultFont.get(),
			captionColor, 10.0f, CENTER_CENTER);
    }

	DrawRectangle(pButton->mnButtonX, mnHeight-pButton->mnButtonY-pButton->mnButtonHeight,
         pButton->mnButtonWidth, pButton->mnButtonHeight, Vec4(0.0f, 0.0f, 0.0f, 0.7f), FILL_ON);


	//Vec4 outlineColor;
	//if (nState == 0) outlineColor = Vec4(0.45f, 0.55f, 0.55f, 1.0f); // button off
	//else outlineColor = Vec4(1.0f, 1.0f, 1.0f, 1.0f); 

	//DrawRectangle(pButton->mnButtonX, mnHeight-pButton->mnButtonY-pButton->mnButtonHeight,
 //       pButton->mnButtonWidth, pButton->mnButtonHeight, outlineColor);
}

void tcStartView::DrawButtonLine(int anButton) 
{
    int nState;

    if ((anButton < 0)||(anButton >= N_START_BUTTONS)) {return;}

    tsButtonInfo *pButton = &maButton[anButton];
    nState = pButton->mnState;

	Vec4 color;

    if (nState != 0) 
    {
		color = Vec4(0.7f, 0.92f, 0.92f, 1.0f);
    }
    else 
    {
		color = Vec4(0.45f, 0.55f, 0.55f, 1.0f);
    }

    int nLineY = pButton->mnButtonY + pButton->mnButtonHeight/2;
	nLineY = mnHeight - nLineY;
    int nLineX1 = pButton->mnButtonX;
    int nLineX2 = pButton->mnButtonX + pButton->mnButtonWidth;

    DrawLine(nLineX1-50, nLineY, nLineX1, nLineY, color);
    DrawLine(nLineX2, nLineY, nLineX2+50, nLineY, color);
}

tcDatabaseViewer* tcStartView::GetDatabaseViewer() const
{
    return databaseViewer;
}

tcMPGameView* tcStartView::GetMPGameView() const
{
	wxASSERT(networkView != 0);

	return networkView->GetMPGameView();
}

tcNetworkView* tcStartView::GetNetworkView() const
{
    return networkView;
}


const std::string& tcStartView::GetPane() const
{
    static std::string s = "None";

    if ((mnActiveButton < 0) || (mnActiveButton >= N_START_BUTTONS))
    {
        return s;
    }
    else
    {
        return maButton[mnActiveButton].paneName;
    }
}

tcScenarioSelectView* tcStartView::GetScenarioSelectView() const
{
    return scenarioSelectView;
}


void tcStartView::OnMouseMove(wxMouseEvent& event)
{
    bool bButtonOver;
    int nButton;

    //TranslatePoint(point); // adjust for flipped up/down 
    bButtonOver = ButtonContainingPoint(event.GetPosition(), nButton);
    if (!bButtonOver)
    {
        unsigned t = tcTime::Get()->Get30HzCount();
        for (int i=0; i<N_START_BUTTONS; i++)
        {
            if (maButton[i].mnState == tsButtonInfo::OVER)
            {
                unsigned dt = t - maButton[i].timeStamp;
                maButton[i].mnState = tsButtonInfo::OFF;
                if (dt > buttonFadeTime)
                {
                    maButton[i].timeStamp = t;
                }
                else
                {
                    maButton[i].timeStamp = t + (dt - buttonFadeTime);
                }
            }
        }
        return;
    }

    if (nButton >= N_START_BUTTONS) 
    {
        wxASSERT(false);
        return;
    } 
    //tcSound::Get()->PlayEffect("Beep2");

    if (maButton[nButton].mnState == tsButtonInfo::OVER) return; // already over

    for (int i=0; i<N_START_BUTTONS; i++)
    {
        if (maButton[i].mnState != tsButtonInfo::ON)
        {
            maButton[i].mnState = tsButtonInfo::OFF;
        }
    }

    // code to disable the mouseover graphics for start game button
    // when in multiplayer client mode
    bool buttonEnabled = ((nButton==5) || (nButton==6)) ? mbPlayEnabled : true;
    if (!buttonEnabled)
    {
        maButton[nButton].mnState = tsButtonInfo::OFF;
        return;
    }

    int currentState = maButton[nButton].mnState;
    if (currentState == tsButtonInfo::OFF)
    {                
        tcSound::Get()->PlayEffect("Thuck");
        maButton[nButton].timeStamp = tcTime::Get()->Get30HzCount();
        maButton[nButton].mnState = tsButtonInfo::OVER; // set to OVER state
    }

}

void tcStartView::OnChar(wxKeyEvent& event)
{
    event.Skip();
    event.ResumePropagation(1);
}

void tcStartView::OnKeyDown(wxKeyEvent& event)
{    
    event.Skip();
    event.ResumePropagation(1);
}

void tcStartView::OnLButtonDown(wxMouseEvent& event) 
{
    bool bButtonClicked;
    int nButton;

    if (!mbActive) 
    {
        event.Skip();
        return;
    }
    //TranslatePoint(point); // adjust for flipped up/down 
    bButtonClicked = ButtonContainingPoint(event.GetPosition(), nButton);
    bool bButtonEnabled = (nButton==5) ? mbPlayEnabled : true;
    if (!bButtonEnabled) {bButtonClicked = false;}

    if (bButtonClicked) 
    {
        if (nButton >= N_START_BUTTONS) 
        {
            WTL("tcStartView::OnLButtonDown error");
            return;
        } 

        if (nButton != 2)
        {
            tcSound::Get()->PlayEffect("MutedBeep");
        }
        int command_id = 0;
        switch (nButton)
        {
        case 5: command_id = ID_STARTGAME; break;
        case 6: command_id = ID_EDITGAME; break;
        case 7: command_id = ID_CREATESCEN; break;
        case 8: command_id = ID_QUITGAME; break;
        default: command_id = 0; break;
        }

        if (command_id)
        {
            wxCommandEvent command(wxEVT_COMMAND_BUTTON_CLICKED, command_id) ;    
            command.SetEventObject(this);
            AddPendingEvent(command);
        }

    }
    else 
    {
        return; // don't clear selection
    }

    for(int i=0;i<N_START_BUTTONS;i++) 
    {
        if ((i == nButton)&&(bButtonClicked)) 
        {
            maButton[i].mnState = 2;
            if (maButton[i].subWindow != 0)
            {
                SetPane(maButton[i].paneName);
                //maButton[i].subWindow->SetActive(true);
            }
        }
        else 
        {
            maButton[i].mnState = 0;
            if (maButton[i].subWindow != 0) maButton[i].subWindow->SetActive(false);
        }
    }
    mnActiveButton = nButton;
}

void tcStartView::OnSize(wxSizeEvent& event)
{
    tc3DWindow2::OnSize(event);

    wxSize size = event.GetSize();

    if (size.GetHeight() > 800)
    {
        mnXStart = 25;
        mnYStart = 70;
    }
    else if (size.GetHeight() > 700)
    {
        mnXStart = 25;
        mnYStart = 50;

    }
    else
    {
        mnXStart = 25;
        mnYStart = 40;
    }

    panePosition.x = mnXStart + 175;
    panePosition.y = mnYStart-10;
    paneSize.Set(size.GetWidth() - panePosition.x - 50, size.GetHeight() - panePosition.y - 50);
    
    const int tabHeight = 20;
    const int tabIndent = 20;
    tabPosition.x = panePosition.x + tabIndent;
    tabPosition.y = panePosition.y - tabHeight;
    tabSize.Set(paneSize.GetWidth() - 2*tabIndent, tabHeight);

    if (rightPane != 0)
    {
        rightPane->SetSize(panePosition.x, panePosition.y, paneSize.x, paneSize.y);
    }

    for (size_t n=0; n<5; n++)
    {
        tsButtonInfo* button = &maButton[n];
        if ((button != 0) && (button->subWindow != 0))
        {
            button->subWindow->SetSize(paneSize);
        }
    }

    if (tabHeader != 0)
    {
        tabHeader->SetSize(tabPosition.x, tabPosition.y, tabSize.x, tabSize.y);
    }
}

void tcStartView::OnTab(wxCommandEvent& event)
{
    wxASSERT((mnActiveButton < N_START_BUTTONS) && (mnActiveButton >= 0));
    if (mnActiveButton >= N_START_BUTTONS) return;

    std::string newTab(event.GetString().c_str());

    tabHeader->SetActiveTab(newTab);
    if (tcTabbedWindow* tabbedWindow = dynamic_cast<tcTabbedWindow*>(maButton[mnActiveButton].subWindow))
    {
        tabbedWindow->SetTab(newTab);
    }
}


/**
* Update button placement fields
*/
void tcStartView::PlaceButtons() 
{
    int xpos,ypos;
    ypos = mnYStart;
    xpos = mnXStart;

    for(int i=0; i < N_START_BUTTONS; i++) 
    {
        tsButtonInfo *pButton = &maButton[i];

        pButton->mnTextX = xpos; 
        pButton->mnTextY = ypos+pButton->mnButtonHeight+2;
        pButton->mnButtonX = xpos; 
        pButton->mnButtonY = ypos;
        xpos += 0*pButton->mnButtonWidth;
        ypos += 2*pButton->mnButtonHeight;
        ypos += 24;
    }

    // place Play button to right of Scenario button
    //const int nPlayIdx = 4;
    //const int nScenarioIdx = 0;
    //tsButtonInfo *pPlayButton = &maButton[nPlayIdx];
    //tsButtonInfo *pScenarioButton = &maButton[nScenarioIdx];

    //pPlayButton->mnButtonX = pScenarioButton->mnButtonX + 2*pScenarioButton->mnButtonWidth; 
    //pPlayButton->mnButtonY = pScenarioButton->mnButtonY;
    //pPlayButton->mnTextX = pPlayButton->mnButtonX; 
    //pPlayButton->mnTextY = pPlayButton->mnButtonY+pPlayButton->mnButtonHeight+8;

    //// place Multiplay button to right of Options button
    //const int nMultiIdx = 5;
    //const int nOptionsIdx = 1;
    //tsButtonInfo *pMultiButton = &maButton[nMultiIdx];
    //tsButtonInfo *pOptionButton = &maButton[nOptionsIdx];

    //pMultiButton->mnButtonX = pOptionButton->mnButtonX + 2*pOptionButton->mnButtonWidth; 
    //pMultiButton->mnButtonY = pOptionButton->mnButtonY;
    //pMultiButton->mnTextX = pMultiButton->mnButtonX; 
    //pMultiButton->mnTextY = pMultiButton->mnButtonY+pMultiButton->mnButtonHeight+8;

}

/**
* A hack to pass viewer through to database viewer sub window
*/
void tcStartView::Set3DViewer(tc3DViewer* v)
{
    viewer = v;

    if (tcDatabaseViewer* databaseViewer = dynamic_cast<tcDatabaseViewer*>(maButton[2].subWindow))
    {
        databaseViewer->Set3DViewer(v);
    }
    else
    {
        wxASSERT(false);
    }
    
}

void tcStartView::SetActive(bool abActive)
{
    if (IsActive() == abActive) return;

    tc3DWindow2::SetActive(abActive);

    if (abActive) SetPane(size_t(mnActiveButton));

    if (!abActive && (mnActiveButton == 2))
    {
        viewer->SetDatabaseView(false);
    }
}

void tcStartView::SetPane(const std::string& s)
{
    for(size_t k=0; k<N_START_BUTTONS; k++)
    {
        if (maButton[k].paneName == s)
        {
            SetPane(k);
            return;
        }
    }
    
    wxASSERT(false); // not found
}

void tcStartView::SetPane(size_t n)
{
    for(size_t k=0; k<N_START_BUTTONS; k++)
    {
        if (maButton[k].subWindow != 0)
        {
            maButton[k].subWindow->SetActive(false);
        }
		maButton[k].mnState = tsButtonInfo::OFF;
    }

    if (n < N_START_BUTTONS)
    {
        mnActiveButton = int(n);
    }
    else
    {
        mnActiveButton = -1;
        return;
    }

    if (maButton[n].subWindow != 0)
    {
        maButton[n].subWindow->SetActive(true);

        tabHeader->ClearTabs();
        if (tcTabbedWindow* tabbed = dynamic_cast<tcTabbedWindow*>(maButton[n].subWindow))
        {
            tabHeader->SetTabs(tabbed->GetTabList());
            tabHeader->SetActiveTab(tabbed->GetTab());
			tabHeader->SetTabWidth(tabbed->GetTabWidth());
        }

		maButton[n].mnState = tsButtonInfo::ON;
    }
  
}

void tcStartView::SetGameStarted(bool state)
{
    //if (gameStarted == state) return;

    gameStarted = state;

    bool multiplayerClient = tcSimState::Get()->IsMultiplayerClient();

    // Update start button caption
    for(size_t k=0; k<N_START_BUTTONS; k++)
    {
        if (maButton[k].paneName == "Play")
        {
            if (multiplayerClient)
            {
                maButton[k].altText = "JOIN GAME";
                maButton[k].mzCaption = "Join game in progress";
            }
            else if (gameStarted)
            {
                maButton[k].altText = "RETURN";
                maButton[k].mzCaption = "Return to the game";
            }
            else
            {
                maButton[k].altText = "START GAME";
                maButton[k].mzCaption = "Start the game";
            }
            return;
        }
    }
}

void tcStartView::SetPlayEnabled(bool state)
{
    if (mbPlayEnabled == state) return;

    mbPlayEnabled = state;
}

void tcStartView::SetVersionString(const std::string& s)
{
    versionString = s;
}


bool tcStartView::ButtonContainingPoint(wxPoint point, int& rnButton) 
{
    int i;
    int nx, ny, nButtonWidth, nButtonHeight;

    for(i=0; i < N_START_BUTTONS; i++) 
    {
        nx = maButton[i].mnButtonX;
        ny = maButton[i].mnButtonY;
        nButtonWidth = maButton[i].mnButtonWidth;
        nButtonHeight = maButton[i].mnButtonHeight;
        wxRect cr(nx,ny,nButtonWidth,nButtonHeight);
        if (cr.Contains(point)) 
        {
            rnButton = i;
            return true;
        }
    }
    return false;
}

/**
 * tcStartView constructor.
 */
tcStartView::tcStartView(wxWindow *parent, 
                         const wxPoint& pos,
                         const wxSize& size, 
                         const wxString& name) : 
           tc3DWindow2(parent, pos, size, name) ,
		   buttonSize(64),
           buttonFadeTime(15),
           scenarioSelectView(0),
           databaseViewer(0),
           mbPlayEnabled(false),
           gameStarted(false),
           viewer(0)
{
    wxSize parentSize = parent->GetSize();

    if (parentSize.GetHeight() > 800)
    {
        mnXStart = 25;
        mnYStart = 70;
    }
    else if (parentSize.GetHeight() > 700)
    {
        mnXStart = 25;
        mnYStart = 50;

    }
    else
    {
        mnXStart = 25;
        mnYStart = 40;
    }

    panePosition.x = mnXStart + 175;
    panePosition.y = mnYStart-10;
    paneSize.Set(size.GetWidth() - panePosition.x - 50, size.GetHeight() - panePosition.y - 50);
    
    const int tabHeight = 20;
    const int tabIndent = 20;
    tabPosition.x = panePosition.x + tabIndent;
    tabPosition.y = panePosition.y - tabHeight;
    tabSize.Set(paneSize.GetWidth() - 2*tabIndent, tabHeight);
    

    mpOptions = NULL;


    for (int i=0; i < N_START_BUTTONS; i++)
    {
        maButton[i].mnButtonX = -100;
        maButton[i].mnButtonY = -100;
        maButton[i].mnTextX = -100;
        maButton[i].mnTextY = -100;
        maButton[i].mzCaption = "X";
        maButton[i].mnState = 0;
    }

    mnActiveButton = -1;
    mbPlayEnabled = false;

    SetBorderDraw(true);
}

/**
 * tcStartView destructor.
 */
tcStartView::~tcStartView() 
{

}