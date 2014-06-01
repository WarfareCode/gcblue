/**
**  @file tcNumberWidget.cpp
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

#include "tcNumberWidget.h"

#include "tv_types.h"
#include "tcTexture2D.h"

#include "wxcommands.h"
#include "tcSound.h"
#include "tcTime.h"
#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif 

template <class T>
void tcNumberWidget<T>::ApplyBounds()
{
    if (val < minVal) val = minVal;
    if (val > maxVal) val = maxVal;
}

/**
* Drawing Graphics object is based on parent's window since
* button is sharing a surface with the parent.
* This also allows the button to draw outside of its wxWindow
* screen area.
*/
template <class T>
void tcNumberWidget<T>::Draw()
{
    if (!mbActive) return;

    StartDraw();

    UpdateAutoChange();

    // clear keyboardWait if timeout reached
    if (keyboardWait)
    {
        unsigned t = tcTime::Get()->Get30HzCount();
        unsigned dt = t - lastKeypressTime;
        if (dt >= keyboardTimeout)
        {
            keyboardWait = false;
            afterDecimalPoint = 0;
            isNegative = false;
            SendUpdate();
        }
    }

    // non-image drawing
	Vec4 backgroundColor;
    Vec4 textColor;

    if (keyboardWait)
    {
        backgroundColor = keyboardWaitColor;
        textColor = activeTextColor;
    }
    else if (isMouseOver)
    {
        backgroundColor = mouseOverColor;
        textColor = activeTextColor;
    }
    else
    {
        backgroundColor = restingColor;
        textColor = restingTextColor;
    }
    
	DrawRectangle(0, 0, mnWidth, mnHeight, backgroundColor, FILL_ON);
	//DrawRectangle(0, 0, mnWidth, mnHeight, Vec4(1, 1, 1, backgroundAlpha), FILL_OFF);

    float x = float(mnWidth) - 3.0f;
    float y = 0.0f; //0.5f * float(mnHeight);

    // draw caption to the left of the window area
    DrawText(caption.c_str(), xcaption, ycaption, defaultFont.get(), activeTextColor,
        captionFontSize, tc3DWindow2::AlignmentType(captionAlignment));

    wxString modifiedFormatString(formatString);
    if (keyboardWait)
    {
        if (afterDecimalPoint <= 1)
        {
            modifiedFormatString = "%.0f";
        }
        else
        {
            modifiedFormatString = wxString::Format("%%.%df", afterDecimalPoint-1);
        }
    }
    wxString s = wxString::Format(modifiedFormatString.c_str(), val);

	DrawText(s.c_str(), x, y, defaultFont.get(), textColor, fontSize, RIGHT_BASE_LINE);

	FinishDraw();
}

template <class T>
bool tcNumberWidget<T>::EditInProgress() const
{
    return keyboardWait || autoChange;
}

template <class T>
void tcNumberWidget<T>::EnableUpdateMessages(bool state, long cmd)
{
    sendUpdateMessages = state;
    updateCommand = cmd;
}


template <class T>
void tcNumberWidget<T>::OnChar(wxKeyEvent& event)
{
    int nChar = event.GetKeyCode();

    unsigned t = tcTime::Get()->Get30HzCount();
    unsigned dt = t - lastKeypressTime;

    bool addDigit = (keyboardWait && (dt < keyboardTimeout));
    keyboardWait = true;
    lastKeypressTime = t;


    const int val0 = '0';
    const int val9 = '9';
    
    if (nChar == WXK_RETURN)
    {
        keyboardWait = false;
        afterDecimalPoint = 0;
        isNegative = false;
        tcSound::Get()->PlayEffect("MutedBeep");
    }
    else if ((nChar >= val0) && (nChar <= val9))
    {
        if (addDigit)
        {
            if (afterDecimalPoint == 0)
            {
                val = isNegative ? (10.0f * val - (nChar - val0)) : (10.0f * val + (nChar - val0));
            }
            else if (pow(10.0, -double(afterDecimalPoint)) >= double(smallestIncrement))
            {
                T dv =  T((nChar - val0)) * pow(10.0, -double(afterDecimalPoint));
                val += isNegative ? -dv : dv;
                afterDecimalPoint++;
            }
        }
        else
        {
            val = (nChar - val0);
        }
        tcSound::Get()->PlayEffect("MutedBeep");
    }
    else if ((nChar == '-') && (minVal < 0))
    {
        if (!addDigit)
        {
            isNegative = true;
            val = 0;
        }
        else
        {
            // ignore negative in middle of entry
        }
    }
    else if ((nChar == '.') && (double(smallestIncrement) < 1.0))
    {
        afterDecimalPoint = 1;
    }
    else
    {
        event.Skip();
    }

    ApplyBounds();
}

/**
*
*/
template <class T>
void tcNumberWidget<T>::OnEnterWindow(wxMouseEvent& event)
{
    if (!isMouseOver)
    {
        tcSound::Get()->PlayEffect(soundEffect);
    }

    isMouseOver = true;

    if (sendRedraw)
    {
        SendRedraw();
    }

    wxWindow::SetFocus();
}

/**
*
*/
template <class T>
void tcNumberWidget<T>::OnLButtonDown(wxMouseEvent& event)
{
    wxPoint pos = event.GetPosition();
    leftButtonDown = true;
    
    buttonDownTime = tcTime::Get()->Get30HzCount();
    lastAutoChange = 0;

    bool upper = pos.y < mnHeight / 2;

    // measure could be done once per font size change instead
    wxSize numberSize;
    MeasureText(defaultFont.get(), 1.1f * fontSize, "8", numberSize);

    float maxDigit = floorf(log10f(double(maxVal) / double(smallestIncrement))) - 1.0f;

    float digitIdx = floorf(float(mnWidth - pos.x - 2.0f) / float(numberSize.GetWidth()));
    if (digitIdx < 0) digitIdx = 0;
    else if (digitIdx > maxDigit) digitIdx = maxDigit;

    T increment = smallestIncrement * T(powf(10.0f, digitIdx));

    

    if (upper)
    {
        changeIncrement = increment;
    }
    else
    {
        changeIncrement = -increment;
    }

    SendRedraw();

    tcSound::Get()->PlayEffect("MutedBeep");
}

/**
*
*/
template <class T>
void tcNumberWidget<T>::OnLButtonUp(wxMouseEvent& event)
{
    // implement change for simple click on release of mouse
    if (!autoChange)
    {
        val += changeIncrement;
        SendUpdate();
    }

    if (autoChange)
    {
        SendUpdate();
    }
    autoChange = false;
    changeIncrement = 0;
    leftButtonDown = false;

    SendRedraw();
}

/**
*
*/
template <class T>
void tcNumberWidget<T>::OnLeaveWindow(wxMouseEvent& event)
{
    isMouseOver = false;
    leftButtonDown = false;

    if (sendRedraw)
    {
        SendRedraw();
    }
}

template <class T>
void tcNumberWidget<T>::OnMouseWheel(wxMouseEvent& event)
{
    bool mouseWheelUp = (event.GetWheelRotation() > 0);

    if (mouseWheelUp)
    {
        val += 1;
    }
    else
    {
        val -= 1;
    }
    SendUpdate();
}


/**
*
*/
template <class T>
void tcNumberWidget<T>::OnRButtonDown(wxMouseEvent& event)
{
}

template <class T>
void tcNumberWidget<T>::SetActive(bool abActive)
{
    tc3DWindow2::SetActive(abActive);

    if (!abActive)
    {
        autoChange = false;
        leftButtonDown = false;
        keyboardWait = false;
        afterDecimalPoint = 0;
        isNegative = false;
    }
}

/**
* Send ID_BUTTONREDRAW message to force parent redraw
*/
template <class T>
void tcNumberWidget<T>::SendRedraw()
{
    wxCommandEvent cmd(wxEVT_COMMAND_BUTTON_CLICKED, ID_BUTTONREDRAW) ;    
    cmd.SetEventObject(this);
    AddPendingEvent(cmd);
}

/**
* Notification to parent that value has changed
*/
template <class T>
void tcNumberWidget<T>::SendUpdate()
{
    if (sendUpdateMessages)
    {
        wxCommandEvent cmd(wxEVT_COMMAND_TEXT_UPDATED, updateCommand);    
        cmd.SetEventObject(this);
        AddPendingEvent(cmd);
    }
}

template <class T>
void tcNumberWidget<T>::SetCaptionParameters(float x, float y, float captionFontSize_, int alignment)
{
    xcaption = x;
    ycaption = y;
    captionFontSize = captionFontSize_;
    captionAlignment = alignment;
}

template <class T>
void tcNumberWidget<T>::SetFillColor(const Vec4& resting, const Vec4& mouseOver, const Vec4& keyboardWait)
{
    restingColor = resting;
    mouseOverColor = mouseOver;
    keyboardWaitColor = keyboardWait;
}

/**
*
*/
template <class T>
void tcNumberWidget<T>::SetFontSize(float size)
{
    fontSize = size;
}

template <class T>
void tcNumberWidget<T>::SetBounds(T minVal_, T maxVal_)
{
    minVal = minVal_;
    maxVal = maxVal_;
}

template <class T>
void tcNumberWidget<T>::SetFormatString(const wxString& s)
{
    formatString = s;
}

template <class T>
void tcNumberWidget<T>::SetSendRedraw(bool state)
{
    sendRedraw = state;
}

template <class T>
void tcNumberWidget<T>::SetSmallestIncrement(T x)
{
    smallestIncrement = x;
}

template <class T>
void tcNumberWidget<T>::SetTextColor(const Vec4& resting, const Vec4& active)
{
    restingTextColor = resting;
    activeTextColor = active;
}


/**
* Check if mouse button down long enough and
* periodically increment / decrement val if so
* Allows user to change value quickly by holding mouse
* button down.
*/
template <class T>
void tcNumberWidget<T>::UpdateAutoChange()
{
    if (!leftButtonDown)
    {
        autoChange = false;
        return;
    }

    unsigned currentTime = tcTime::Get()->Get30HzCount();

    if (currentTime - buttonDownTime > 20)
    {
        autoChange = true;
    }

    if (autoChange && (currentTime > (lastAutoChange + 1)))
    {
        val += changeIncrement;
        lastAutoChange = currentTime;
    }

    ApplyBounds();
}

/**
*
*/
template <class T>
tcNumberWidget<T>::tcNumberWidget(T& param, tc3DWindow2 *parent, const wxPoint& pos, const wxSize& size,
                   const wxString& name) :
    tc3DWindow2(parent, pos, size, name, parent),
    val(param),
    formatString("%.0f"),
    sendRedraw(false),
    autoChange(false),
    keyboardWait(false),
    changeIncrement(0),
    leftButtonDown(false),
    buttonDownTime(0),
    lastAutoChange(0),
    keyboardTimeout(60),
    afterDecimalPoint(0),
    isNegative(false),
    minVal(0),
    maxVal(99999.0f),
    smallestIncrement(1),
    restingColor(0, 0, 0, 1),
    mouseOverColor(0.1f, 0.1f, 0.1f, 1.0f),
    keyboardWaitColor(0.1f, 0.5f, 0.1f, 1.0f),
    restingTextColor(1.0f, 1.0f, 1.0f, 1.0f),
    activeTextColor(1.0f, 1.0f, 1.0f, 1.0f),
    xcaption(-5.0f),
    ycaption(1.0f),
    captionFontSize(10.0f),
    captionAlignment(RIGHT_BASE_LINE),
    updateCommand(-1),
    sendUpdateMessages(false)
{
    
    caption = "NULL";
    isMouseOver = false;
    soundEffect = "";
    fontSize = 9.0f;
	
}

template <class T>
tcNumberWidget<T>::~tcNumberWidget()
{
#ifdef _DEBUG
    fprintf(stdout, "Destroying number widget\n");
#endif
}



template class tcNumberWidget<float>;
template class tcNumberWidget<double>;