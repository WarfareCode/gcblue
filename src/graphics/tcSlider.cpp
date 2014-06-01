/**
**  @file tcSlider.cpp
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

#include "tcSlider.h"

#include "tcTexture2D.h"

#include "wxcommands.h"
#include "common/tinyxml.h"
#include "tcSound.h"
#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif 


/**
* Drawing Graphics object is based on parent's window since
* button is sharing a surface with the parent.
* This also allows the button to draw outside of its wxWindow
* screen area.
*/
void tcSlider::Draw()
{
    if (!mbActive) return;

    if ((linkedValue != 0) && (!sliderDragActive))
    {
        sliderValue = *linkedValue;
    }

    UpdateThumb();

    StartDraw();

    float x = sliderMarginLeft;
    float ycenter = 0.5f * float(mnHeight);
    float y = 0.5f * float(mnHeight - sliderBarHeight);

    // draw underlying slider bar
	DrawRectangle(x, y, sliderBarWidth, sliderBarHeight, Vec4(1.0f, 1.0f, 1.0f, 0.5f), FILL_ON);

    Vec4 color(0.7f, 0.7f, 1.0f, 0.6f);
    if (sliderDragActive)
    {
        color.set(1, 1, 1, 1);
    }

    // draw slider thumb (draggable vertical bar)
	DrawRectangle(thumbRect, color, FILL_ON);

    // draw text caption of current value on right
    wxString s;
    if (sliderValue < 1.0)
    {
        s.Printf("%.2f", sliderValue);
    }
    else
    {
        s.Printf("%.1f", sliderValue);
    }
    DrawText(s.c_str(), x + sliderBarWidth + 8.0f, ycenter, boldFont.get(), Vec4(1, 1, 1, 1), 16.0f, LEFT_CENTER);


	FinishDraw();
}



long tcSlider::GetCommand() const 
{
    return commandId;
}

void tcSlider::LinkValue(float* pVal)
{
    linkedValue = pVal;
}

void tcSlider::OnEnterWindow(wxMouseEvent& event)
{

}


void tcSlider::OnLButtonDown(wxMouseEvent& event)
{
    wxPoint pos = event.GetPosition();

    if (!thumbRect.ContainsPoint(float(pos.x), float(pos.y))) return;

    buttonDownSliderValue = sliderValue; 
    buttonDownPoint = pos;
    sliderDragActive = true;
}

void tcSlider::OnLButtonUp(wxMouseEvent& event)
{
    if (!sliderDragActive) return;

    if (linkedValue != 0)
    {
        *linkedValue = sliderValue;
    }

    SendUpdateEvent();
    
    sliderDragActive = false;
}

void tcSlider::OnLeaveWindow(wxMouseEvent& event)
{
    sliderDragActive = false;
}

void tcSlider::OnMouseMove(wxMouseEvent& event)
{
    if (!sliderDragActive) return;

    wxPoint pos = event.GetPosition();

    int dx = pos.x - buttonDownPoint.x;

    sliderValue = buttonDownSliderValue + dx*(sliderMax-sliderMin)/sliderBarWidth;
    sliderValue = std::max(sliderValue, sliderMin);
    sliderValue = std::min(sliderValue, sliderMax);
}

void tcSlider::SendUpdateEvent()
{
    wxCommandEvent command(wxEVT_COMMAND_TEXT_UPDATED, commandId);    
    command.SetEventObject(this);
    AddPendingEvent(command);
}


void tcSlider::SetActive(bool abActive)
{
    tc3DWindow2::SetActive(abActive);
}


void tcSlider::SetCommand(long cmd) 
{
    commandId = cmd;
}

void tcSlider::SetFontSize(float val)
{
    fontSize = val;
}

void tcSlider::SetValidRange(float minVal, float maxVal)
{
    sliderMin = minVal;
    sliderMax = maxVal;

    wxASSERT(sliderMax > sliderMin);
}


void tcSlider::UpdateThumb()
{
    float sliderFraction = (sliderValue - sliderMin) / (sliderMax - sliderMin);

    float xthumb = (sliderFraction * sliderBarWidth) + sliderMarginLeft;
    float ythumb = 0.5f*float(mnHeight);
    thumbRect.Set(xthumb, xthumb, ythumb, ythumb);
    thumbRect.Expand(0.5f*thumbWidth, 0.5f*thumbHeight);
}


tcSlider::tcSlider(tc3DWindow2* parent, const wxPoint& pos, const wxSize& size,
                   const wxString& name) 
: tc3DWindow2(parent, pos, size, name, parent),
    commandId(0),
    fontSize(16.0f),
    sliderBarHeight(8.0f),
    thumbWidth(8.0f),
    thumbHeight(16.0f),
    sliderDragActive(false),
    sliderValue(0),
    sliderMin(0),
    sliderMax(1.0f),
    buttonDownSliderValue(0),
    linkedValue(0)
{
    sliderMarginLeft = 5.0f;
    sliderMarginRight = 16.0f;
    sliderBarWidth = float(size.GetWidth()) - sliderMarginLeft - sliderMarginRight;
    wxASSERT(sliderBarWidth >= 10.0f);

    sliderBarWidth = std::max(sliderBarWidth, 10.0f);
}

tcSlider::~tcSlider()
{

}



