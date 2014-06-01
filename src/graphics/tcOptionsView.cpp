/**
**  @file tcOptionsView.cpp
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

#include "tcOptionsView.h"
#include "AError.h"
#include "tcString.h"
#include "wxcommands.h"
#include "tcOptions.h"
#include "tcSound.h"

#include "tcTexture2D.h"
#include "tv_types.h"


/*******************************************************************************/
void tcOptionsView::Init() 
{
	wxString s;

    //LoadBackgroundImage("options_bk.jpg");

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
		fprintf(stderr, "tcOptionsView::Init - error loading button images\n");
	}

    AddTab("Game");
    AddTab("Sound");
    AddTab("Graphics");
    AddTab("Units");
    AddTab("Multiplayer");
    AddTab("Lighting");
    AddTab("Water");
    AddTab("Other3D");

    SetTab("Game");
}

void tcOptionsView::UpdateButtonInfo()
{
    std::string activeTab(GetTab());

    if (activeTab == lastTab) return; // no update required
    lastTab = activeTab;

    std::vector<tcOptions::OptionInfo>& optionList = mpOptions->maOptionInfo;

    buttonInfo.clear();

    int ypos = mnYStart;

	for (size_t i=0; i<optionList.size(); i++) 
	{
		int xpos = mnXStart;

        if (optionList[i].group == activeTab.c_str())
        {
            if (optionList[i].associatedFloat == 0)
            {
                for (size_t j=0; j<optionList[i].mzCaption.size(); j++) 
                {
                    tsButtonInfo info;
                    info.optionIdx = i;
                    info.valueIdx = j;
                    info.isSlider = false;

                    wxString& sText = optionList[i].mzCaption[j];
                    wxSize rstring;

                    MeasureText(defaultFont.get(), fontSize, sText.c_str(), rstring);

                    info.textX = xpos;
                    info.textY = ypos;

                    xpos += (int)(rstring.GetWidth()) + 5;

                    info.buttonX = xpos;
                    info.buttonY = ypos-mnButtonHeight/2;

                    buttonInfo.push_back(info);

                    xpos += 3*mnButtonWidth;
                }
            }
            else // slider for float value adjustment
            {
                tsButtonInfo info;
                info.optionIdx = i;
                info.valueIdx = 0;
                info.isSlider = true;

                wxString& sText = optionList[i].mzCaption[0];
                wxSize rstring;

                MeasureText(defaultFont.get(), fontSize, sText.c_str(), rstring);

                info.textX = xpos;
                info.textY = ypos;

                xpos += (int)(rstring.GetWidth()) + 5;

                info.buttonX = xpos;
                info.buttonY = ypos;

                buttonInfo.push_back(info);
            }

            ypos -= 5*(mnButtonHeight >> 1); // 2.5x
        }
	}

}

/**
* 
*/
void tcOptionsView::Draw() 
{
	static unsigned int drawCount = 0;


    std::string activeTab = GetTab();

    StartDraw();

	wxASSERT(mpOptions);   


    UpdateButtonInfo();

    std::vector<tcOptions::OptionInfo>& optionList = mpOptions->maOptionInfo;

    for(size_t k=0; k<buttonInfo.size(); k++) 
    {
        if (!buttonInfo[k].isSlider)
        {
            int optionIdx = buttonInfo[k].optionIdx;
            int valueIdx = buttonInfo[k].valueIdx;

            tcString sText = optionList[optionIdx].mzCaption[valueIdx];

            float x = (float)buttonInfo[k].textX;
            float y = (float)buttonInfo[k].textY;

            DrawText(sText.c_str(), x, y, defaultFont.get(), 
                Vec4(0.86f, 0.86f, 1.0f, 1.0f), fontSize, LEFT_CENTER);

            if (optionList[optionIdx].mnValue == valueIdx) 
            {
                DrawButton(buttonInfo[k].buttonX, buttonInfo[k].buttonY, 1);
            }
            else 
            {
                DrawButton(buttonInfo[k].buttonX, buttonInfo[k].buttonY, 0);
            }
        }
        else
        {
            int optionIdx = buttonInfo[k].optionIdx;

            tcString sText = optionList[optionIdx].mzCaption[0];

            bool thisSliderActive = sliderDragActive && (sliderIdx == k);

            float sliderVal = thisSliderActive ? 
                                sliderDragValue : optionList[optionIdx].floatVal;
            float sliderMin = optionList[optionIdx].floatMin;
            float sliderMax = optionList[optionIdx].floatMax;
            float sliderFraction = (sliderVal - sliderMin) / (sliderMax - sliderMin);

  
            float xText = (float)buttonInfo[k].textX;
            float yText = (float)buttonInfo[k].textY;
            float xBar = (float)buttonInfo[k].buttonX;
            float yBar = (float)buttonInfo[k].buttonY;

            DrawText(sText.c_str(), xText, yText, defaultFont.get(), 
                Vec4(0.86f, 0.86f, 1.0f, 1.0f), fontSize, LEFT_CENTER);

            float xThumb = xBar + sliderFraction*sliderBarWidth;
            tcRect thumbRect(xThumb-2.0f, xThumb+2.0f, yBar-8.0f, yBar+8.0f);
            buttonInfo[k].thumbRect = thumbRect;

            // draw slider here
            DrawSlider(xBar, yBar, thumbRect, sliderVal, thisSliderActive);

        }

	}


	FinishDraw();
}

/**
* 
*/
void tcOptionsView::DrawButton(int x, int y, int abOn) 
{
	tcTexture2D* pButton;

	pButton = (abOn == 1) ? mpiButtonOn.get() : mpiButtonOff.get();

	DrawImage(pButton, x, y, float(mnButtonWidth), float(mnButtonHeight), 
		ALIGN_BOTTOM_LEFT);
}

/**
* 
*/
void tcOptionsView::DrawSlider(int x, int y, tcRect thumbRect, float value, bool interacting) 
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



void tcOptionsView::OnLButtonDown(wxMouseEvent& event)
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
				WTL("tcOptionsView::OnLButtonDown error");
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
bool tcOptionsView::OnLButtonDownSlider(const wxPoint& pos)
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



void tcOptionsView::OnLButtonUp(wxMouseEvent& event)
{
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

void tcOptionsView::OnLeaveWindow(wxMouseEvent& event)
{
    sliderDragActive = false;
}

void tcOptionsView::OnMouseMove(wxMouseEvent& event)
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

void tcOptionsView::OnSize(wxSizeEvent& event)
{
    tcXmlWindow::OnSize(event);

    wxSize size = event.GetSize();

    mnYStart = mnHeight - 50;

    lastTab = ""; // to force update button to execute
    UpdateButtonInfo();
}



bool tcOptionsView::ButtonContainingPoint(wxPoint point, int& rnOption, int& rnValue) 
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



tcOptionsView::tcOptionsView(wxWindow *parent, const wxPoint& pos, 
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
		fprintf(stderr, "tcOptionsView::tcOptionsView - NULL xml config node\n");
		return;
	}


	mpOptions = tcOptions::Get();

	mnXStart = 100;
	mnYStart = 100;


    SetBorderDraw(true);
    
    SetTabWidth(90.0f);

    Init();
}

tcOptionsView::tcOptionsView(tc3DWindow2* parent,
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
		fprintf(stderr, "tcOptionsView::tcOptionsView - NULL xml config node\n");
		return;
	}


	mpOptions = tcOptions::Get();

	mnXStart = 30;
	mnYStart = mnHeight - 50;

    SetBorderDraw(true);

    SetTabWidth(90.0f);

    Init();
}

tcOptionsView::~tcOptionsView() 
{
}
