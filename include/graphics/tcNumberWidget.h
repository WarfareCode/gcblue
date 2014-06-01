/**  
**  @file tcNumberWidget.h
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



#ifndef _TCNUMBERWIDGET_H_
#define _TCNUMBERWIDGET_H_

#if _MSC_VER > 1000
#pragma once
#endif 

#include "tc3DWindow2.h"
#include <string>

class tcTexture2D;
class TiXmlNode;

/**
* GUI widget class derived from tc3DWindow2.
* Used to adjust and display T parameter graphically
*/
template<class T>
class tcNumberWidget : public tc3DWindow2
{
public:
    virtual void Draw();
    std::string GetCaption() const {return caption;}
 
    bool EditInProgress() const;
    void SetFillColor(const Vec4& resting, const Vec4& mouseOver, const Vec4& keyboardWait);
    void SetTextColor(const Vec4& resting, const Vec4& active);
    void SetFormatString(const wxString& s);

    virtual void SetActive(bool abActive);
    void SetCaption(std::string s) {caption = s;}
    void SetCaptionParameters(float x, float y, float captionFontSize_, int alignment);
    void SetFontSize(float size);
    void SetSendRedraw(bool state);
    void SetSoundEffect(const std::string& effect) {soundEffect = effect;}
    void SetBounds(T minVal_, T maxVal_);
    void SetSmallestIncrement(T x);
    //void SetMouseWheelCommand(long val);
    void EnableUpdateMessages(bool state, long cmd);

    tcNumberWidget(T& param, tc3DWindow2 *parent, const wxPoint& pos, const wxSize& size,
            const wxString& name = "NumberWidget");

    virtual ~tcNumberWidget();

protected:
    T& val;  ///< reference to parameter to adjust

    std::string caption;
    wxString formatString;
   
    bool isMouseOver;
    std::string soundEffect;
    float fontSize;

    T minVal;
    T maxVal;
    T smallestIncrement; ///< increment associated with last decimal place

    Vec4 restingColor;
    Vec4 mouseOverColor;
    Vec4 keyboardWaitColor;
    Vec4 restingTextColor;
    Vec4 activeTextColor;

    float xcaption;
    float ycaption;
    float captionFontSize;
    int captionAlignment;

    bool sendRedraw;
    bool autoChange; ///< true if mouse is down long enough, val will auto increment/decrement
    T changeIncrement;
    bool leftButtonDown; ///< true if left button is down
    unsigned int buttonDownTime;
    unsigned int lastAutoChange;

    bool sendUpdateMessages; ///< true to send update msg to parent when value changed
    long updateCommand; ///< command value to use for SendUpdate()

    virtual void OnChar(wxKeyEvent& event);
    virtual void OnEnterWindow(wxMouseEvent& event);
    virtual void OnLButtonDown(wxMouseEvent& event);
    virtual void OnLButtonUp(wxMouseEvent& event);
    virtual void OnLeaveWindow(wxMouseEvent& event);
    virtual void OnRButtonDown(wxMouseEvent& event);
    virtual void OnMouseWheel(wxMouseEvent& event);

    void SendRedraw();
    void SendUpdate();
    void UpdateAutoChange();
private:
    const unsigned int keyboardTimeout;
    bool keyboardWait; ///< true to update value with keyboard
    unsigned int lastKeypressTime;
    int afterDecimalPoint; ///< greater than 0 if entering text after decimal point
    bool isNegative; ///< true while entering a negative number with keyboard

    void ApplyBounds();
};

#endif

