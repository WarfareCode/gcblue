/**
**  @file tcEditBox.h
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


#ifndef _EDITBOX_H_
#define _EDITBOX_H_

#if _MSC_VER > 1000
#pragma once
#endif 

#include "tc3DWindow2.h"

class TiXmlNode;

/**
* User interface object based on tcEditControl for text entry.
*/
class tcEditBox : public tc3DWindow2
{
    enum { MAX_EDITBOX_CHAR = 96};
public:
    virtual void Draw();
    void GetBuffer(char* azDest);
    const char* GetBuffer() const;
    void SetBuffer(const char* azBuffer); 
    void SetCaption(const char* azCaption);
    void SetClearOnReturn(bool state);
    void SetCommand(long cmd);
    void SetBoxColor(const Vec4& c);
    void SetTextColor(const Vec4& c);
    void SetCaptionFontSize(float val);
    void SetCaptionAlignment(int type);
    void SetMouseWheelParameters(long upCommand, long downCommand, bool enable);

    tcEditBox(tc3DWindow2 *parent, TiXmlNode *config);
    virtual ~tcEditBox();
protected:
    static unsigned ref_count;
    bool isMouseOver;
    bool isFocused;
    bool textChanged;
    bool drawBackground; ///< true to draw image or default solid color background
    Vec4 boxColor; ///< color for box that text is drawn inside of
    Vec4 textColor;
    float captionFontSize;
    tc3DWindow2::AlignmentType captionAlignment;
    bool clearOnReturn; ///< clear text after ENTER is pressed, will also post text update message
    tcRect mrectTextBar; // region for text to be displayed
    tcRect mrectTextCaption; // caption region
    char mzCaption[MAX_EDITBOX_CHAR];
    char mzBuffer[MAX_EDITBOX_CHAR];
	char mzBufferHide[MAX_EDITBOX_CHAR]; ///< buffer with * chars for password entry mode
    long command;
	bool starText; ///< true to use * for text for password entry
	std::string lastBuffer;
	unsigned int cursorPosition;

    long mouseWheelUpCommand;
    long mouseWheelDownCommand;
    bool enableMouseWheelEvents;


    virtual void OnChar(wxKeyEvent& event);
    virtual void OnEnterWindow(wxMouseEvent& event);
    virtual void OnKeyDown(wxKeyEvent& event);
    virtual void OnLButtonDown(wxMouseEvent& event);
    virtual void OnLButtonUp(wxMouseEvent& event);
    virtual void OnLeaveWindow(wxMouseEvent& event);
    virtual void OnMouseWheel(wxMouseEvent& event);
    virtual void OnSetFocus(wxFocusEvent& event);
    virtual void OnKillFocus(wxFocusEvent& event);
};

#endif

