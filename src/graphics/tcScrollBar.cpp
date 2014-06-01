/**
**  @file tcScrollBar.cpp
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

#include "tcScrollBar.h"
#include "tcTime.h"
#include "tcTexture2D.h"
#include "wxcommands.h"
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
void tcScrollBar::Draw()
{
    if (!mbActive) return;
    //if ((!mbActive) || (barFraction > 1)) return;

    StartDraw();

	UpdateAutoScroll();

	float w = float(mnWidth);
	float h = float(mnHeight);

	//DrawRectangle(0, 0, w, h, Vec4(0, 0, 0, 1), FILL_ON);

	if (!overArrowUp)
	{
		DrawImageR(arrowUp.get(), 0, 0, w, w, ALIGN_BOTTOM_LEFT);
	}
	else
	{
		DrawImageR(arrowUpOver.get(), 0, 0, w, w, ALIGN_BOTTOM_LEFT);
	}

	if (!overArrowDown)
	{
		DrawImageR(arrowDown.get(), 0, h-w, w, w, ALIGN_BOTTOM_LEFT);
	}
	else
	{
		DrawImageR(arrowDownOver.get(), 0, h-w, w, w, ALIGN_BOTTOM_LEFT);
	}

	Vec4 barColor;


    if (!scrollDrag)
    {
		if (!overScrollBar)
		{
			barColor = Vec4(0.4f, 0.4f, 0.5f, backgroundAlpha);
		}
		else
		{
			barColor = Vec4(0.85f, 0.85f, 0.9f, backgroundAlpha);
		}
    }
    else
    {
        barColor = Vec4(1, 1, 1, backgroundAlpha);
    }
    
	Vec4 baseColor(0.3f, 0.3f, 0.4f, backgroundAlpha);

	//DrawRectangle(0, w, mnWidth, mnHeight-w, backgroundColor, FILL_ON);
	DrawRectangle(0, 0, w, h, baseColor, FILL_OFF);

	DrawLine(0, w, w, w, baseColor);

	DrawLine(0, h-w, w, h-w, baseColor);

	// draw scroll bar rectangle
	float barHeight = barFraction*(h - 2*w);
	barRect.Set(0, w, w+ybar, w+ybar+barHeight);

	buttonUpRect.Set(0, w, 0, w);
	buttonDownRect.Set(0, w, h-w, h);

	DrawRectangleR(barRect, barColor, FILL_ON);


	FinishDraw();
}


void tcScrollBar::LoadImages()
{
 //   arrowUp = boost::shared_ptr<tcTexture2D>(tc3DWindow2::LoadTexture("up_arrow.png"));
	//arrowDown = boost::shared_ptr<tcTexture2D>(tc3DWindow2::LoadTexture("down_arrow.png"));
	//arrowUpOver = boost::shared_ptr<tcTexture2D>(tc3DWindow2::LoadTexture("up_arrow_over.png"));
	//arrowDownOver = boost::shared_ptr<tcTexture2D>(tc3DWindow2::LoadTexture("down_arrow_over.png"));

    arrowUp = boost::shared_ptr<tcTexture2D>(tc3DWindow2::LoadTexture("arrow_up.jpg"));
	arrowDown = boost::shared_ptr<tcTexture2D>(tc3DWindow2::LoadTexture("arrow_down.jpg"));
	arrowUpOver = boost::shared_ptr<tcTexture2D>(tc3DWindow2::LoadTexture("arrow_up_over.jpg"));
	arrowDownOver = boost::shared_ptr<tcTexture2D>(tc3DWindow2::LoadTexture("arrow_down_over.jpg"));

}

/**
*
*/
void tcScrollBar::OnEnterWindow(wxMouseEvent& event)
{
    isMouseOver = true;
}


/**
* Treat double click as single click
*/
void tcScrollBar::OnLButtonDClick(wxMouseEvent& event)
{
    OnLButtonDown(event);
}


/**
*
*/
void tcScrollBar::OnLButtonDown(wxMouseEvent& event)
{
    wxPoint pos = event.GetPosition();

	autoScrollIncrement = 0;

    leftButtonDown = true;

	if (barRect.ContainsPoint(pos.x, pos.y))
	{
		scrollDrag = true;
		scrollDragStart = pos;
		ybarStart = ybar;
		CaptureMouse();
	}
	else if ((buttonUpRect.ContainsPoint(pos.x, pos.y)) || (pos.y < (int)barRect.GetTop()))
	{
		UpdateYbar(ybar - clickScrollAmount);
		buttonDownTime = tcTime::Get()->Get30HzCount();
		autoScrollIncrement = -clickScrollAmount;
	}
	else if ((buttonDownRect.ContainsPoint(pos.x, pos.y)) || (pos.y > (int)barRect.GetBottom()))
	{
		UpdateYbar(ybar + clickScrollAmount);
		buttonDownTime = tcTime::Get()->Get30HzCount();
		autoScrollIncrement = clickScrollAmount;
	}

	SendRedrawMessage();
}

/**
*
*/
void tcScrollBar::OnLButtonUp(wxMouseEvent& event)
{
	if (scrollDrag)
	{
		ReleaseMouse();
	}

    leftButtonDown = false;
	scrollDrag = false;
	autoScrollIncrement = 0;
	autoScroll = false;

	SendRedrawMessage();
}

/**
*
*/
void tcScrollBar::OnLeaveWindow(wxMouseEvent& event)
{
	autoScrollIncrement = 0;
	autoScroll = false;

	overScrollBar = false;
	overArrowUp = false;
	overArrowDown = false;

	SendRedrawMessage();
}

/**
*
*/
void tcScrollBar::OnMouseMove(wxMouseEvent& event)
{
	wxPoint pos = event.GetPosition();

	overScrollBar = false;
	overArrowUp = false;
	overArrowDown = false;

	if (barRect.ContainsPoint(pos.x, pos.y))
	{
		overScrollBar = true;
	}
	else if (buttonUpRect.ContainsPoint(pos.x, pos.y))
	{
		overArrowUp = true;
	}
	else if (buttonDownRect.ContainsPoint(pos.x, pos.y))
	{
		overArrowDown = true;
	}

	if (scrollDrag)
	{
		float dy = float(pos.y - scrollDragStart.y);

		UpdateYbar(ybarStart + dy);	
	}

	SendRedrawMessage();
}

void tcScrollBar::OnMouseWheel(wxMouseEvent& event)
{
    int zDelta = event.GetWheelRotation();
    
    if (zDelta > 0) 
    {
        UpdateYbar(ybar - clickScrollAmount);
    }
    else if (zDelta < 0) 
    {
        UpdateYbar(ybar + clickScrollAmount);
    }
}

void tcScrollBar::SendScrollbarUpdated()
{
	if (ybar == lastybar) return;
	lastybar = ybar;

    wxCommandEvent cmd(wxEVT_COMMAND_SCROLLBAR_UPDATED, 1);    
    cmd.SetEventObject(this);

	if (scrollFromBottom)
	{	
		float rectHeight = float(mnHeight) - 2*float(mnWidth);
		float barHeight = barFraction*rectHeight;
		
		//cmd.m_extraLong = long((rectHeight - barHeight - ybar)* 4.0f / barFraction * (float(mnHeight)/rectHeight)); // 2.6.3
        long extraLong = long((rectHeight - barHeight - ybar)* 4.0f / barFraction * (float(mnHeight)/rectHeight));
        if (extraLong < 0) extraLong = 0;
        cmd.SetExtraLong(extraLong);
	}
	else
	{
		float rectHeight = float(mnHeight) - 2*float(mnWidth);
		//cmd.m_extraLong = long(ybar * 4.0f / barFraction * (float(mnHeight)/rectHeight)); // 2.6.3
        cmd.SetExtraLong(long(ybar * 4.0f / barFraction * (float(mnHeight)/rectHeight)));
        // DEC 2011, max returned appears to be 4x ((1-barFract)/barFract) * scrollbar height (??)
	}
	

    AddPendingEvent(cmd);
}


void tcScrollBar::SetActive(bool abActive)
{
	if (barFraction >= 1.0)
	{
		tc3DWindow2::SetActive(false);
	}
	else
	{
		tc3DWindow2::SetActive(abActive);
	}
}

/**
*
*/
void tcScrollBar::SetBackgroundAlpha(float val)
{
    backgroundAlpha = val;
}


void tcScrollBar::SetBarFraction(float val)
{
	if (barFraction == val) return;

	float barFractionPrev = barFraction;

	barFraction = val;
	if (barFraction < 0.005f) barFraction = 0.005f;
	else if (barFraction > 1.0) barFraction = 1.0;

	SetActive(barFraction < 1.0);

	float ybar_adjust = 0;
	if (scrollFromBottom)
	{
		float rectHeight = float(mnHeight) - 2*float(mnWidth);
		ybar_adjust = (barFractionPrev - barFraction) * rectHeight;
	}
	
	UpdateYbar(ybar + ybar_adjust);

    clickScrollAmount = 0.07f * barFraction * float(mnHeight);
}

/**
* Does not send message
*/
void tcScrollBar::SetBarPosition(float scrollAmount, float showSize)
{
    float rectHeight = float(mnHeight) - 2*float(mnWidth);
	ybar = (scrollAmount / showSize) * barFraction * rectHeight;
}


void tcScrollBar::SendRedrawMessage()
{
	if (!sendRedraw) return;

	wxCommandEvent cmd(wxEVT_COMMAND_BUTTON_CLICKED, ID_BUTTONREDRAW);    
    cmd.SetEventObject(this);

    AddPendingEvent(cmd);
}

void tcScrollBar::SetScrollFromBottom(bool state)
{
	scrollFromBottom = state;

	if (scrollFromBottom)
	{
		ybar = 99999.9f;
	}
	else
	{
		ybar = 0;
	}
}

void tcScrollBar::SetSendRedraw(bool state)
{
	sendRedraw = state;
}

/**
* Check if mouse button down long enough and
* periodically increment / decrement val if so
* Allows user to change value quickly by holding mouse
* button down.
*
* Similar to method in tcNumberWidget
* @see tcNumberWidget::UpdateAutoChange
*/
void tcScrollBar::UpdateAutoScroll()
{
	if (autoScrollIncrement == 0) return;

    unsigned currentTime = tcTime::Get()->Get30HzCount();

    if (currentTime - buttonDownTime > 20)
    {
        autoScroll = true;
    }

    if (autoScroll)
    {
        UpdateYbar(ybar + autoScrollIncrement);
    }
}


void tcScrollBar::UpdateYbar(float ynew)
{
	ybar = ynew;

	float ybarMax = (float(mnHeight) - float(2*mnWidth))*(1.0-barFraction);

	if (ybar < 0) ybar = 0;
	else if (ybar > ybarMax) ybar = ybarMax;

	SendScrollbarUpdated();
}


/**
*
*/
tcScrollBar::tcScrollBar(tc3DWindow2 *parent, const wxPoint& pos, const wxSize& size,
                   const wxString& name) :
    tc3DWindow2(parent, pos, size, name, parent),
    isMouseOver(false),
    leftButtonDown(false),
	overArrowUp(false),
	overArrowDown(false),
	overScrollBar(false),
	scrollDrag(false),
    backgroundAlpha(0.8f),
	barFraction(1.234f),
	ybar(0),
	lastybar(9999.9f),
	clickScrollAmount(2.0f),
    autoScroll(false),
    autoScrollIncrement(0),
	buttonDownTime(0),
	sendRedraw(false),
	scrollFromBottom(false),
	barRect(0, 0, 0, 0)
{
    LoadImages();

	SetBaseRenderBin(parent->GetBaseRenderBin() + 10);
	wxWindow::Raise();

	SetActive(false);
}

tcScrollBar::~tcScrollBar()
{
#ifdef _DEBUG
    fprintf(stdout, "Destroying tcScrollBar\n");
#endif
}



