/**
**  @file tcConsoleBox.h 
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


#ifndef _CONSOLEBOX_H_
#define _CONSOLEBOX_H_

#if _MSC_VER > 1000
#pragma once
#endif 

#include "wx/wx.h" 
#include "wx/string.h"

#include "tc3DWindow2.h"

#include "tv_types.h"

class TiXmlNode;


class tcScrollBar;

/**
* Class based on tcConsole modified to use 3D window graphics
*/
class tcConsoleBox  : public tc3DWindow2 
{
public:
    enum
    {
        REMOVE_LINES = 64,
        MAX_LINES = 256,
        MIN_LINES_DISPLAY = 8, ///< in offset mode, show at least this many lines
        SCROLL_LINES = 4 ///< number of lines to scroll up/down
    };
    wxArrayString textArray;
    
    int nlinespace;	///< spacing between lines
    int cursorLine; ///< position of last line drawn (for delayed draw effect)
    int cursorCol; ///< position of last character drawn

    int nyzero;		///< start y in console window for text (text scrolls up)
    int nwrapcol;  ///< column to wrap at
    int nwrapbuff; ///< buffer for searching for space to wrap at

    int Print(const char* line, int n);
    int Print(const char* line);

    void ScrollBuffer(int delta);
	void Clear();
    virtual void Draw();

    void ForceRedraw() {forceRedraw = true;}
    unsigned int GetLineOffset() const;
    bool IsCurrentLineEmpty();
    virtual void OnKeyDown(wxKeyEvent& event);
	virtual void OnSize(wxSizeEvent& event);
    bool Redraw() const {return redraw != 0;} ///< @return true if console will be updated

    void SetDelayedTextEffect(bool effectOn) {useDelayedTextEffect = effectOn;}
    void SetLineOffset(unsigned int offset);
    void SetLineSpacing(int anSpacing) {nlinespace = anSpacing;}
    void SetWrap(int n) {nwrapcol = n;}
    void UpdateCursor();

    tcConsoleBox(tc3DWindow2* parent, TiXmlNode* config); ///< for shared surface console box
    virtual ~tcConsoleBox();
protected:
    int useDelayedTextEffect;
    int redraw; ///< redraw based on cursor update state
    bool forceRedraw; ///< a workaround to force redraw when button state changes
    bool isMouseOver;
    bool isFocused;
	unsigned int lineOffset; ///< for reviewing buffer history 
	float fontSize;
	Vec4 fontColor;

	tcScrollBar* scrollBar;
	float yOffset; ///< offset for scrolling
	float yCurrent; ///< used to track how much space the text needs for scrolling


    void InitFromXml(TiXmlNode* config);
	void OnChildRedraw(wxCommandEvent& event);
	void OnScrollbarUpdated(wxCommandEvent& event);

    DECLARE_EVENT_TABLE()
};

#endif

