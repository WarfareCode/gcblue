/** 
**  @file tcDraggableWindow.cpp 
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

#include "tcDraggableWindow.h"
#include "tc3DWindow2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void tcDraggableWindow::SetWindowDragEnabled(bool state)
{
    windowDragEnabled = state;

    if (windowDragOn && !windowDragEnabled)
    {
        StopWindowDrag();
    }
}

/**
* @return true if window drag started
* Checks if mouse is in valid area of window to start drag
*/
bool tcDraggableWindow::StartWindowDrag(const wxPoint& pos)
{
    if (!windowDragEnabled || ((pos.y > 20) && (pos.y < windowToDrag->mnHeight)))
    {
        return false;
    }
    else
    {        
        windowDragOn = true;
        // position in parent's frame of mouse pointer
        windowDragPoint = wxPoint(windowToDrag->mrectWindow.GetLeft() + pos.x, 
            windowToDrag->mrectWindow.GetBottom() + pos.y);

		windowToDrag->CaptureMouse();
        return true;
    }
}

void tcDraggableWindow::StopWindowDrag()
{
    if (windowDragOn)
    {
        windowDragOn = false;
        windowToDrag->ReleaseMouse();
    }
}


void tcDraggableWindow::UpdateWindowDrag(const wxPoint& pos)
{
    if (!windowDragOn) return;

    // position in parent's frame of mouse pointer
    wxPoint current = wxPoint(windowToDrag->mrectWindow.GetLeft() + pos.x, windowToDrag->mrectWindow.GetBottom() + pos.y);
    if (current != windowDragPoint)
    {
        wxPoint delta = current - windowDragPoint;
		int xmove = windowToDrag->mrectWindow.GetLeft() + delta.x;
		int ymove = windowToDrag->mrectWindow.GetTop() + delta.y;
        windowToDrag->MoveWindow(xmove, ymove);
        windowDragPoint = current;
    }
}

tcDraggableWindow::tcDraggableWindow(tc3DWindow2* window_)
: windowToDrag(window_),
  windowDragOn(false),
  windowDragPoint(0, 0),
  windowDragEnabled(true)
{
}

tcDraggableWindow::~tcDraggableWindow()
{
}