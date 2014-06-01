/**  
**  @file tcScrollBar.h
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



#ifndef _TCSCROLLBAR_H_
#define _TCSCROLLBAR_H_

#if _MSC_VER > 1000
#pragma once
#endif 

#include "tc3DWindow2.h"
#include <string>
#include <boost/shared_ptr.hpp>
#include "tv_types.h"

class tcTexture2D;
class TiXmlNode;

/**
* GUI scroll bar class
*/
class tcScrollBar : public tc3DWindow2
{
public:
    virtual void Draw();

    virtual void OnMouseWheel(wxMouseEvent& event);

	virtual void SetActive(bool abActive);
    void SetBackgroundAlpha(float val);
	void SetBarFraction(float val);
	void SetScrollFromBottom(bool state);
	void SetSendRedraw(bool state);
    void SetBarPosition(float scrollAmount, float showSize);

    tcScrollBar(tc3DWindow2 *parent, const wxPoint& pos, const wxSize& size,
            const wxString& name = "ScrollBar");

    virtual ~tcScrollBar();

protected:
	float barFraction; ///< thumb fractional height relative to scroll extent, ratio of "in view" and "full list"
	float ybar;
	tcRect barRect;
	tcRect buttonUpRect;
	tcRect buttonDownRect;
    Vec4 barColor;
    Vec4 baseColor;

    bool isMouseOver;
	bool leftButtonDown;
	bool scrollDrag;
	bool overArrowUp; ///< true if mouse is over up arrow
	bool overArrowDown; ///< true if mouse if over down arrow
	bool overScrollBar;

	wxPoint scrollDragStart;
	float ybarStart;

    bool autoScroll; ///< true if mouse is down long enough on up/down arrow, will auto scroll
    float autoScrollIncrement; ///< set to 0 when left button is not down over up/down arrow
	unsigned int buttonDownTime;
    bool sendRedraw; ///< true to send redraw messages to parent
	bool scrollFromBottom; ///< true to scroll from bottom (console mode)
    float backgroundAlpha;  ///< transparency value for solid color background
    

    virtual void OnEnterWindow(wxMouseEvent& event);
    virtual void OnLButtonDown(wxMouseEvent& event);
	virtual void OnLButtonDClick(wxMouseEvent& event);
    virtual void OnLButtonUp(wxMouseEvent& event);
	virtual void OnMouseMove(wxMouseEvent& event);
    virtual void OnLeaveWindow(wxMouseEvent& event);


private:
	float clickScrollAmount; ///< amount to scroll by when up/down arrow clicked
    boost::shared_ptr<tcTexture2D> arrowUp;
	boost::shared_ptr<tcTexture2D> arrowDown;
	boost::shared_ptr<tcTexture2D> arrowUpOver;
	boost::shared_ptr<tcTexture2D> arrowDownOver;
	float lastybar;

	void LoadImages();
	void SendScrollbarUpdated();
	void SendRedrawMessage();
	void UpdateAutoScroll();
	void UpdateYbar(float ynew);

};

#endif

