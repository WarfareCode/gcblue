/**
**  @file tcStaticText.cpp
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

#include "tcStaticText.h"

#include "tcTexture2D.h"

#include "wxcommands.h"
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
void tcStaticText::Draw()
{
    if (!mbActive) return;

    StartDraw();

    tcRect box(0, float(mnWidth), 0, float(mnHeight));
    if (!isMouseOver)
    {        
        DrawRectangleR(box, backgroundColor, FILL_ON);
        DrawTextInRectR(caption.c_str(), box, defaultFont.get(), textColor, fontSize, CENTER_CENTER);
    }
    else
    {
        DrawRectangleR(box, backgroundOverColor, FILL_ON);
        DrawTextInRectR(caption.c_str(), box, defaultFont.get(), textOverColor, fontSize, CENTER_CENTER);
    }

    FinishDraw();
}

void tcStaticText::DrawTooltipCaption()
{
    if (tooltipCaption.size() == 0) return;
	
    float x = (float)tooltipCaptionPosition.x;
    float y = (float)tooltipCaptionPosition.y;
    Vec4 color(1.0f, 1.0f, 1.0f, 1.0f);

    DrawText(tooltipCaption.c_str(), x, y, defaultFont.get(), color, tooltipCaptionFontSize, tc3DWindow2::AlignmentType(tooltipCaptionAlignment));
}


void tcStaticText::OnEnterWindow(wxMouseEvent& event)
{
    isMouseOver = true;
}


void tcStaticText::OnLeaveWindow(wxMouseEvent& event)
{
    isMouseOver = false;
}


void tcStaticText::SetActive(bool abActive)
{
    tc3DWindow2::SetActive(abActive);
}

void tcStaticText::SetColors(const Vec4& background_, const Vec4& backgroundOver_,
                   const Vec4& text_, const Vec4& textOver_)
{
    backgroundColor = background_;
    backgroundOverColor = backgroundOver_;
    textColor = text_;
    textOverColor = textOver_;
}


void tcStaticText::SetFontSize(float val)
{
    fontSize = val;
}


void tcStaticText::SetTooltipCaption(const std::string& s)
{
    tooltipCaption = s;
}

void tcStaticText::SetTooltipCaptionAlignment(int val)
{
    tooltipCaptionAlignment = val;
}

void tcStaticText::SetTooltipCaptionFontSize(float val)
{
    tooltipCaptionFontSize = val;
}

void tcStaticText::SetTooltipCaptionPosition(const wxPoint& pos)
{
    tooltipCaptionPosition = pos;
}


tcStaticText::tcStaticText(tc3DWindow2* parent, const wxPoint& pos, const wxSize& size,
                   const wxString& name) 
: tc3DWindow2(parent, pos, size, name, parent),
    backgroundColor(0, 0, 0, 0),
    backgroundOverColor(0, 0, 0, 0),
    textColor(1, 1, 1, 1),
    textOverColor(1, 1, 1, 1),
    caption("Caption goes here"),
    isMouseOver(false),
    fontSize(14.0f),
    tooltipCaption(""),
    tooltipCaptionPosition(size.GetWidth()/2, 0),
    tooltipCaptionFontSize(10.0f),
    tooltipCaptionAlignment(CENTER_CENTER)
{

}

tcStaticText::~tcStaticText()
{

}



