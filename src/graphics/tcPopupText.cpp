/** 
**  @file tcPopupText.cpp 
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

#include "tcPopupText.h"

#include <stdio.h>
#include <iostream>
#include "tv_types.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif 




/**
*
*/
void tcPopupText::Draw()
{
    //if (!redraw) return;

    StartDraw();

    Vec4 color(1, 1, 1, 1);

//    float x = 0.5f * float(mnWidth);
    float y = 0.5f * float(mnHeight);


    Vec4 fillColor(0.4f, 0.4f, 0.5f, 0.8f);
	Vec4 borderColor(0.0f, 0.0f, 0.0f, 1.0f);
	Vec4 textColor(1.0f, 1.0f, 1.0f, 1.0f);

	tcFont* font = GetDefaultFont();

    DrawRectangleR(0, 0, float(mnWidth), float(mnHeight), fillColor, FILL_ON);
    DrawRectangleR(0, 0, float(mnWidth), float(mnHeight), borderColor, FILL_OFF);

	DrawTextR(text.c_str(), 4.0f, y, 
		font, textColor, popupFontSize, LEFT_CENTER);

	FinishDraw();

    redraw = false;
}



void tcPopupText::OnMouseMove(wxMouseEvent& event)
{
	event.Skip();
}


/**
*
*/
tcPopupText::tcPopupText(const std::string& text_, const wxPoint& pos, tc3DWindow2* parent)
            : tc3DWindow2(parent, pos, wxSize(100, 25), "PopupText", parent),
   text(text_),
   popupFontSize(12.0f),
   redraw(true)
{
    SetBaseRenderBin(parent->GetBaseRenderBin() + 10);

	// calculate size based on text
	tcFont* defaultFont = GetDefaultFont();
	wxSize size;
	MeasureText(defaultFont, popupFontSize, text.c_str(), size);

	int width = size.GetWidth() + (int)popupFontSize;
	int height = size.GetHeight() + (int)popupFontSize;

	SetSize(pos.x, pos.y, width, height); // set all size params

	SetActive(true);

    SetBorderDraw(true);
}

tcPopupText::~tcPopupText() 
{

}

