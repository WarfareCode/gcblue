/**  
**  @file tcDisplaySettingsView.cpp
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

#include "wx/string.h"

#include "tcDisplaySettingsView.h"
#include "tcDisplayModes.h"
#include "wxcommands.h"
#include "tc3DWindow2.h"
#include "tcTVEngine.h"
#include "CTVDeviceInfo.h"
#include "CTVTextureFactory.h"
//#include "tcGraphicsInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif 

/*******************************************************************************/
bool tcDisplaySettingsView::Init() 
{
#if 0
	FontFamily ff(L"Arial");
	mpFont = new Font(&ff,12,FontStyleBold,UnitPixel);
	if (mpFont == NULL) 
	{
		fprintf(stderr, "tcDisplaySettingsView - mpFont creation failed\n");
		return false;
	}
	mpBrush = new SolidBrush(Color(0xFEFFFFFF)); // color is ARGB 
	if (mpBrush == NULL) 
	{
		fprintf(stderr, "tcDisplaySettingsView - mpBrush creation failed\n");
		return false;
	}
	mpPen = new Pen(Color(255,200,200,200),2);
	if (mpPen == NULL) 
	{
		fprintf(stderr, "tcDisplaySettingsView - mpPen creation failed\n");
		return false;
	}
#endif

	return true;
}


void tcDisplaySettingsView::Draw() 
{
	static int nTestCount = 0;
   
    StartDraw();

	if (!modeListUpdated)
	{
		UpdateModeList();
		modeListUpdated = true;
	}

	DrawText("To change display settings, select new display settings and restart game.",
			25.0f, mnHeight - 80.0f, defaultFont.get(), 
			Vec4(1, 1, 1, 1), 16.0f, LEFT_BASE_LINE);

    CTVDeviceInfo deviceInfo;


    std::string driverInfo(deviceInfo.GetDriverName());
	driverInfo = std::string("Driver info: ") + driverInfo;
	DrawTextR(driverInfo.c_str(),
			25.0f, 110.0f, defaultFont.get(), 
			Vec4(1, 1, 1, 1), 16.0f, LEFT_BASE_LINE);

    CTVTextureFactory* texFactory = tcTVEngine::Get()->GetTextureFactory();
    wxString s = wxString::Format("Texture memory used: %d MB, free: %d MB", 
        texFactory->GetUsedTextureMemory() >> 20, texFactory->GetFreeTextureMemory() >> 20);

	DrawTextR(s.c_str(),
			25.0f, 130.0f, defaultFont.get(), 
			Vec4(1, 1, 1, 1), 16.0f, LEFT_BASE_LINE);

	unsigned nModes = tcDisplayModes::Get()->GetModeCount();

	tcRect rstring;
	for(int n=0; n<(int)nModes; n++) 
	{
		modeDrawingInfo& drawingInfo = modeList[n];

		wxString& modeText = drawingInfo.modeText;
		float xpos = drawingInfo.x;
		float ypos = mnHeight - drawingInfo.y - drawingInfo.height;
		float height = drawingInfo.height;
		//float textWidth = drawingInfo.width;

		Vec4 color;
		if (n == mouseOverIdx)
		{
			color.set(0.5f, 0.2f, 0.15f, 1.0f);
		}
		else if (tcDisplayModes::Get()->IsCurrentMode(n))
		{
			color.set(0.2f, 0.5f, 0.2f, 1.0f);
		}
		else
		{
			color.set(0.05f, 0.1f, 0.05f, 1.0f);
		}

		DrawRectangle(xpos, ypos, boxWidth, height, color);
		color.set(1, 1, 1, 1);

		if (n == selectedModeIdx)
		{
			DrawRectangle(xpos, ypos, boxWidth, height, color);
		}

		float xoffset = 0.0f;
		
		tcRect textRect;
		textRect.Set(xpos + xoffset, xpos + xoffset + boxWidth,
			ypos + 1.0f, ypos + 1.0f + height);
		DrawTextInRect(modeText.GetData(), textRect, defaultFont.get(), color, 
			fontSize, CENTER_CENTER);
	}

	FinishDraw();    
}

/**
* @return index of mode containing screen point or -1 if none
*/
int tcDisplaySettingsView::GetBoxContainingPoint(const wxPoint& point)
{
	std::map<unsigned int, modeDrawingInfo>::iterator iter 
		= modeList.begin();
	for(; iter != modeList.end(); ++iter)
	{
		wxRect r((int)iter->second.x, (int)iter->second.y, 
			(int)iter->second.width, (int)iter->second.height);
		if (r.Contains(point))
		{
			return (int)iter->first;
		}
	}

	return -1;
}


void tcDisplaySettingsView::OnLButtonDown(wxMouseEvent& event)
{
	wxPoint point = event.GetPosition();

	int downIdx = GetBoxContainingPoint(point);
	if ((downIdx >= 0) && 
		((unsigned)downIdx < tcDisplayModes::Get()->GetModeCount()))
	{
		const tcDisplayModes::Info& info = 
			tcDisplayModes::Get()->GetModeInfo((unsigned)downIdx);
		tcDisplayModes::Get()->ChangeOptionsMode(info.width, info.height, info.bits,
			info.frequency);

		selectedModeIdx = downIdx;
	}

}


void tcDisplaySettingsView::OnMouseMove(wxMouseEvent& event)
{
	wxPoint point = event.GetPosition();

	mouseOverIdx = GetBoxContainingPoint(point);
}


/**
* Updates modeList with bounding rectangle and mode text info.
* Used for drawing and associating mouse location with a mode index.
* Should be called at least once before drawing.
*/
void tcDisplaySettingsView::UpdateModeList()
{
	float xpos = 25.0f;
	const float ystart = 150.0f;
	float ypos = ystart;

	unsigned nModes = tcDisplayModes::Get()->GetModeCount();

	for(unsigned n=0; n<nModes; n++) 
	{
		modeDrawingInfo drawingInfo;

		const tcDisplayModes::Info& info = tcDisplayModes::Get()->GetModeInfo(n);

		drawingInfo.modeText = wxString::Format("%d x %d (%d) %d Hz", 
			info.width, info.height, info.bits, info.frequency);

		wxSize rstring;
		MeasureText(defaultFont.get(), fontSize, drawingInfo.modeText.c_str(), rstring);
	
		drawingInfo.x = xpos;
		drawingInfo.y = ypos - 1.0f;
		drawingInfo.width = rstring.GetWidth();
		drawingInfo.height = rstring.GetHeight() + 2.0f;

		modeList[n] = drawingInfo;

		ypos += rstring.GetHeight() + 5.0f;
		if (ypos > float(mnHeight) - 20.0f)
		{
			ypos = ystart;
			xpos += boxWidth + 50.0f;
		}
	}
}

/**
* @param surfaceHost tcWindow to share surface of
*/
tcDisplaySettingsView::tcDisplaySettingsView(wxWindow *parent, 
                             const wxPoint& pos, const wxSize& size, const wxString& name) 
                             : 
    tcXmlWindow(parent, pos, size, "xml/displaysettings_gui.xml", name),
	selectedModeIdx(-1),
	mouseOverIdx(-1),
	boxWidth(140.0f),
	modeListUpdated(false),
	fontSize(12.0f)
{

	Init();

    LoadBackgroundImage("background.jpg");

    if (config)
    {
//        AddXMLControls();
    }
    else
    {
        fprintf(stderr, "tcDisplaySettingsView::tcDisplaySettingsView - "
			"NULL xml config node\n");
        return;
    }

    SetBorderDraw(true);
}



tcDisplaySettingsView::~tcDisplaySettingsView() 
{

}
