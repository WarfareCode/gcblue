/**
**  @file tcOptionsView2.cpp
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

#include "tcOptionsView2.h"
#include "tcString.h"
#include "wxcommands.h"
#include "tcOptions.h"
#include "tcSound.h"

#include "tcListBox.h"
#include "tcSlider.h"
#include "tcStaticText.h"
#include "tcTexture2D.h"
#include "tv_types.h"


BEGIN_EVENT_TABLE(tcOptionsView2, tc3DWindow2)
    EVT_COMMAND(-1, wxEVT_COMMAND_TEXT_UPDATED, tcOptionsView2::OnControlUpdate)
END_EVENT_TABLE()

/*******************************************************************************/
void tcOptionsView2::Init() 
{
    wxASSERT(controlGroups.size() == 0);

	wxString s;


	mpiButtonOn = LoadTexture("options_bon.bmp");
	mpiButtonOff = LoadTexture("options_boff.bmp");

	wxASSERT(mpiButtonOn.get() != 0);
	wxASSERT(mpiButtonOn->IsLoaded());
	if ((mpiButtonOn.get() != 0) && mpiButtonOn->IsLoaded())
	{
        mnButtonWidth = mpiButtonOn->Width();
		mnButtonHeight = mpiButtonOn->Height();
	}
	else
	{
		fprintf(stderr, "tcOptionsView2::Init - error loading button images\n");
	}

    std::vector<std::string> tabList;
    tabList.push_back("Game");
    tabList.push_back("Sound");
    tabList.push_back("Graphics");
    tabList.push_back("Units");
    tabList.push_back("Events");
    tabList.push_back("Interface");
    tabList.push_back("Multiplayer");
    tabList.push_back("Lighting");
    tabList.push_back("Water");
    tabList.push_back("Other3D");

    for (size_t n=0; n<tabList.size(); n++)
    {
        AddTab(tabList[n]);
    }

    SetTab("Game");


    //struct ControlGroup
    //{
    //    std::string groupName;
    //    std::vector<tc3DWindow2*> controls;
    //};

    //std::vector<ControlGroup> controlGroups;

    Vec4 textColor(0.7f, 0.7f, 0.7f, 0.9f);
    Vec4 textColorOver(1.0f, 1.0f, 0.6f, 1.0f);
    Vec4 borderColor(0.5, 0.5, 0.5, 0.5);
    Vec4 borderColorOver(0.9f, 0.9f, 0.9f, 0.9f);
    Vec4 backgroundColor(0.0f, 0.0f, 0.0f, 0.95f);
    Vec4 backgroundColorOver(0.0f, 0.0f, 0.0f, 0.95f);

    wxSize boxSize(200, 20);
    wxSize capSize(200, 20);
    int xCaption = mnXStart;
    int xControl = xCaption + capSize.GetWidth();

    int controlSpacing = boxSize.GetHeight() + 11;

    std::vector<tcOptions::OptionInfo>& optionList = mpOptions->maOptionInfo;

    // add controls for each tab
    for (size_t n=0; n<tabList.size(); n++)
    {
        std::string tabName = tabList[n];
        wxPoint boxPos(xControl, mnYStart);
        wxPoint capPos(xCaption, mnYStart);

        ControlGroup group;
        group.groupName = tabName;

        // add in reverse order for correct draw order

        for (size_t k=0; k<optionList.size(); k++)
        {
            if (optionList[k].group == tabName.c_str())
            {
                boxPos.y += controlSpacing;
                capPos.y += controlSpacing;
            }
        }

        for (size_t k=0; k<optionList.size(); k++)
        {
            size_t rev_idx = optionList.size() - k - 1;

            if (optionList[rev_idx].group == tabName.c_str())
            {
                switch (optionList[rev_idx].meType)
                {
                case tcOptions::OptionInfo::OT_RADIOBUTTON:
                    {
                        boxPos.y -= controlSpacing;
                        capPos.y -= controlSpacing;

                        tcListBox* listBox = new tcListBox(this, boxPos, boxSize);
                        listBox->SetMaxShow(10);
                        listBox->SetColor(textColor, textColorOver,
                            borderColor, borderColorOver,
                            backgroundColor, backgroundColorOver);

                        for (size_t idx=0; idx<optionList[rev_idx].mzCaption.size(); idx++)
                        {
                            listBox->AddItem(optionList[rev_idx].mzCaption[idx].ToStdString());
                        }

                        listBox->SelectItemByIndex(optionList[rev_idx].mnValue);
                        listBox->LinkValue(optionList[rev_idx].associatedInt);
                        
                        listBox->CloseList();

                        group.controls.push_back(listBox);

                        // add caption
                        tcStaticText* text = new tcStaticText(this, capPos, capSize);
                        text->SetCaption(optionList[rev_idx].description.ToStdString());
                        group.labels.push_back(text);
                    }
                    break;
                case tcOptions::OptionInfo::OT_SLIDER:
                    {
                        boxPos.y -= controlSpacing;
                        capPos.y -= controlSpacing;

                        tcSlider* slider = new tcSlider(this, boxPos, boxSize);
                        slider->LinkValue(optionList[rev_idx].associatedFloat);
                        slider->SetValidRange(optionList[rev_idx].floatMin, optionList[rev_idx].floatMax);
                        group.controls.push_back(slider);

                        // add caption
                        tcStaticText* text = new tcStaticText(this, capPos, capSize);
                        text->SetCaption(optionList[rev_idx].description.ToStdString());
                        group.labels.push_back(text);
                    }
                    break;
                }
            }
        }

        controlGroups.push_back(group);
    }

}

void tcOptionsView2::UpdateButtonInfo()
{
    std::string activeTab(GetTab());

    if (activeTab == lastTab) return; // no update required
    lastTab = activeTab;

    for (size_t n=0; n<controlGroups.size(); n++)
    {
        bool groupActive = (controlGroups[n].groupName == activeTab);

        for (size_t k=0; k<controlGroups[n].controls.size(); k++)
        {
            controlGroups[n].controls[k]->SetActive(groupActive);
        }

        for (size_t k=0; k<controlGroups[n].labels.size(); k++)
        {
            controlGroups[n].labels[k]->SetActive(groupActive);
        }
    }

 
    buttonInfo.clear();


}

void tcOptionsView2::CloseAllLists()
{
    for (size_t n=0; n<controlGroups.size(); n++)
    {
        for (size_t k=0; k<controlGroups[n].controls.size(); k++)
        {
            tcListBox* listBox = dynamic_cast<tcListBox*>(controlGroups[n].controls[k]);
            if (listBox != 0)
            {
                listBox->CloseList();
            }
        }
    }
}


/**
* 
*/
void tcOptionsView2::Draw() 
{
	static unsigned int drawCount = 0;


    std::string activeTab = GetTab();

    StartDraw();

	wxASSERT(mpOptions);   


    UpdateButtonInfo();


	FinishDraw();
}

/**
* 
*/
void tcOptionsView2::DrawButton(int x, int y, int abOn) 
{
	tcTexture2D* pButton;

	pButton = (abOn == 1) ? mpiButtonOn.get() : mpiButtonOff.get();

	DrawImage(pButton, x, y, float(mnButtonWidth), float(mnButtonHeight), 
		ALIGN_BOTTOM_LEFT);
}

/**
* 
*/
void tcOptionsView2::DrawSlider(int x, int y, tcRect thumbRect, float value, bool interacting) 
{
    // draw underlying slider bar
	DrawRectangle(x, y-4.0f, sliderBarWidth, 8.0f, Vec4(1.0f, 1.0f, 1.0f, 0.5f), FILL_ON);

    Vec4 color(0.7f, 0.7f, 1.0f, 0.6f);
    if (interacting)
    {
        color.set(1, 1, 1, 1);
    }

    // draw slider thumb (draggable vertical bar)
	DrawRectangle(thumbRect, color, FILL_ON);

    // draw text caption of current value on right
    wxString s;
    if (value < 1.0)
    {
        s.Printf("%.2f", value);
    }
    else
    {
        s.Printf("%.1f", value);
    }
    DrawText(s.c_str(), x + sliderBarWidth + 5.0f, y, boldFont.get(), Vec4(1, 1, 1, 1), 16.0f, LEFT_CENTER);
}


void tcOptionsView2::OnControlUpdate(wxCommandEvent& event)
{
    mpOptions->Serialize(false); // update options file
}


void tcOptionsView2::OnLButtonDown(wxMouseEvent& event)
{
	bool bButtonClicked;
	int nOption, nValue;

	if (!mbActive) 
	{
		event.Skip();
		return;
	}

    wxPoint pos = event.GetPosition();
    if (OnLButtonDownSlider(pos))
    {
        return;
    }


	int startMapMode = mpOptions->mnMapMode;

	// TranslatePoint(point); // adjust for flipped up/down 
	bButtonClicked = ButtonContainingPoint(pos, nOption, nValue);
	if (bButtonClicked) 
	{
		if ((nOption >= int(mpOptions->maOptionInfo.size()))||
			(nValue >= mpOptions->maOptionInfo[nOption].mnStateCount)) 
		{
                wxASSERT(false);
				return;
			} 
			mpOptions->maOptionInfo[nOption].mnValue = nValue;
			if (mpOptions->maOptionInfo[nOption].associatedInt != NULL) 
			{
				*mpOptions->maOptionInfo[nOption].associatedInt = nValue;
			}
			mpOptions->Serialize(false); // create new options file

			tcSound::Get()->PlayEffect("MutedBeep");
	}
	else
	{
		/* Now this uses tcXmlWindow button bar to switch back to start
		// switch back to start view if no buttons clicked (for now)
		wxCommandEvent command(wxEVT_COMMAND_BUTTON_CLICKED, ID_STARTVIEW) ;    
		command.SetEventObject(this);
		AddPendingEvent(command);
		*/
	}

	if (mpOptions->mnMapMode != startMapMode)
	{
		wxCommandEvent command(wxEVT_COMMAND_BUTTON_CLICKED, ID_REFRESHMAPS);    
		command.SetEventObject(this);
		
		AddPendingEvent(command);
    }

}

/**
* @return true if button down on slider thumb, false otherwise
*/
bool tcOptionsView2::OnLButtonDownSlider(const wxPoint& pos)
{
    bool foundSlider = false;

    for (size_t k=0; (k<buttonInfo.size())&&(!foundSlider); k++)
    {
        if (buttonInfo[k].isSlider)
        {
            if (buttonInfo[k].thumbRect.ContainsPoint(float(pos.x), float(mnHeight-pos.y)))
            {
                foundSlider = true;
                sliderIdx = k;
            }
        }
    }

    if (!foundSlider) return false;

    std::vector<tcOptions::OptionInfo>& optionList = mpOptions->maOptionInfo;

    // initialize sliderDragValue here since mouse may not move initially
    int optionIdx = buttonInfo[sliderIdx].optionIdx;
    float sliderVal = optionList[optionIdx].floatVal;
    sliderDragValue = sliderVal; 

    sliderDragActive = true;
    buttonDownPoint = pos;
    buttonDownTab = GetTab();
	return true;
}



void tcOptionsView2::OnLButtonUp(wxMouseEvent& event)
{
    CloseAllLists();

    if (!sliderDragActive) return;

    std::vector<tcOptions::OptionInfo>& optionList = mpOptions->maOptionInfo;
    int optionIdx = buttonInfo[sliderIdx].optionIdx;
    
    optionList[optionIdx].floatVal = sliderDragValue;
    if (optionList[optionIdx].associatedFloat != 0)
    {
        *optionList[optionIdx].associatedFloat = sliderDragValue;
    }
    mpOptions->Serialize(false); // update options file

    sliderDragActive = false;

}

void tcOptionsView2::OnLeaveWindow(wxMouseEvent& event)
{
    sliderDragActive = false;
}

void tcOptionsView2::OnMouseMove(wxMouseEvent& event)
{
    if (!sliderDragActive) return;

    if (buttonDownTab != GetTab())
    {
        sliderDragActive = false; // cancel slider drag
        return;
    }

    wxPoint pos = event.GetPosition();

    int dx = pos.x - buttonDownPoint.x;

    std::vector<tcOptions::OptionInfo>& optionList = mpOptions->maOptionInfo;

    int optionIdx = buttonInfo[sliderIdx].optionIdx;

    float sliderVal = optionList[optionIdx].floatVal;
    float sliderMin = optionList[optionIdx].floatMin;
    float sliderMax = optionList[optionIdx].floatMax;

    sliderDragValue = sliderVal + dx*(sliderMax-sliderMin)/sliderBarWidth;
    sliderDragValue = std::max(sliderDragValue, sliderMin);
    sliderDragValue = std::min(sliderDragValue, sliderMax);
}

void tcOptionsView2::OnSize(wxSizeEvent& event)
{
    tcXmlWindow::OnSize(event);

    wxSize size = event.GetSize();

    mnYStart = mnHeight - 50;

    lastTab = ""; // to force update button to execute
    UpdateButtonInfo();
}



bool tcOptionsView2::ButtonContainingPoint(wxPoint point, int& rnOption, int& rnValue) 
{
	int nx, ny;

	point.y = mnHeight - point.y;

    for (size_t k=0; k<buttonInfo.size(); k++)
    {
        nx = buttonInfo[k].buttonX;
        ny = buttonInfo[k].buttonY;
        wxRect cr(nx, ny, mnButtonWidth, mnButtonHeight);
        if (cr.Contains(point)) 
        {
            rnOption = buttonInfo[k].optionIdx;
            rnValue = buttonInfo[k].valueIdx;
            return true;
        }
    }

	return false;
}



tcOptionsView2::tcOptionsView2(wxWindow *parent, const wxPoint& pos, 
							 const wxSize& size, const wxString& name) 
							 : 
    tcXmlWindow(parent, pos, size, "xml/options_view.xml", name),
    fontSize(16.0f),
    sliderBarWidth(150.0f)
{

	if (config)
	{
	}
	else
	{
		fprintf(stderr, "tcOptionsView2::tcOptionsView2 - NULL xml config node\n");
		return;
	}


	mpOptions = tcOptions::Get();

	mnXStart = 100;
	mnYStart = 100;


    SetBorderDraw(true);
    
    SetTabWidth(90.0f);

    Init();
}

void tcOptionsView2::SetActive(bool abActive)
{
    tc3DWindow2::SetActive(abActive);

    lastTab = "";
    UpdateButtonInfo();
}


tcOptionsView2::tcOptionsView2(tc3DWindow2* parent,
		const wxPoint& pos, const wxSize& size, 
		const wxString& name) : 
    tcXmlWindow(parent, pos, size, "xml/options_view.xml", name, parent),
    fontSize(16.0f),
    sliderBarWidth(150.0f)
{
	if (config)
	{
	}
	else
	{
		fprintf(stderr, "tcOptionsView2::tcOptionsView2 - NULL xml config node\n");
		return;
	}


	mpOptions = tcOptions::Get();

	mnXStart = 30;
	mnYStart = 50;

    SetBorderDraw(true);

    SetTabWidth(90.0f);

    Init();
}

tcOptionsView2::~tcOptionsView2() 
{
}
