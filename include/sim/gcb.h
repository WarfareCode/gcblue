/**
**  @file gcb.h
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
/*
 *  Some material and comments from "a tiny tutorial by Robert Roebling"
 *  http://www.wxwindows.org
 */

#ifndef _GCB_H_
#define _GCB_H_

#include "wx/wx.h" 


class tcGame;

/**
 * Global Conflict Blue's application class.
 * 
 * By overriding wxApp's OnInit() the program can be initialized, e.g. by creating a new main window. 
 */
class GcbApp : public wxApp
{
public:
    bool Close() {closeApp = true;return true;}
    void OnChar(wxKeyEvent& event);
    void OnEraseBackground(wxEraseEvent& event);
    void OnKeyDown(wxKeyEvent& event);
    void OnLButtonDown(wxMouseEvent& event);
    void OnLeaveWindow(wxMouseEvent& event);
	void OnMouseMove(wxMouseEvent& event);
	void OnRButtonDown(wxMouseEvent& event);

private:
    //WXMSG *current_msg;
    tcGame *gameFrame; ///< main game frame object with game loop, holds all subwindows
    bool closeApp;
	wxEventLoop *eventLoop;

    //void DoMessage(WXMSG *pMsg);
    int MainLoop();
    int OnExit();
    bool OnInit();
    void SetWorkingDirectory(); ///< sets working directory to level above bin/ dir if necessary
	void InitializeGameFrame();
	void CheckDirectories();

	DECLARE_EVENT_TABLE()
};
#endif