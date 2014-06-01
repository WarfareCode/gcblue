/**
**  @file tcEditBox.cpp 
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

#include "tcEditBox.h"
#include "tcTime.h"
#include "common/tinyxml.h"
#include "tcSound.h"
#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif 

/*
BEGIN_EVENT_TABLE(tcEditBox, tcWindow)
   EVT_COMMAND(-1, wxEVT_COMMAND_BUTTON_CLICKED , tcRadioButton::OnButtonCommand)
END_EVENT_TABLE()
*/

unsigned tcEditBox::ref_count = 0;


void tcEditBox::Draw()
{
    wxString s;

    if (!mbActive) {return;}   

    StartDraw();

    if (drawBackground)
    {
        if (!IsBackgroundEnabled()) 
        {
            // erase
			DrawRectangleR(0, 0, mnWidth, mnHeight, Vec4(0.2f, 0.2f, 0.2f, 1.0f), 
				FILL_ON);
        }
    }

    if (isFocused)
	{
		DrawRectangleR(0, 0, mnWidth, mnHeight, Vec4(0.6f, 0.6f, 0.6f, 1.0f), 
			FILL_OFF);
	}

    // erase text box
	DrawRectangleR(mrectTextBar, boxColor, 
		FILL_ON);

    // draw text
	char* drawText = (starText == true) ? mzBufferHide : mzBuffer;


	DrawTextInRect(drawText, mrectTextBar, defaultFont.get(), 
		textColor, fontSize, LEFT_BASE_LINE);
	

    // draw caption
    DrawTextInRectR(mzCaption, mrectTextCaption, defaultFont.get(), 
		Vec4(1, 1, 1, 1), captionFontSize, captionAlignment);

    // draw cursor
	wxString textToCursor = wxString(drawText).Truncate(cursorPosition);
    wxSize size;
    //MeasureText(defaultFont.get(), fontSize, drawText, size);
	MeasureText(defaultFont.get(), fontSize, textToCursor.c_str(), size);

	Vec4 cursorColor(0, 0, 0, 1);
    if (tcTime::Get()->Get30HzCount() % 30 >= 15)
    {
        cursorColor.set(1, 1, 1, 1);
    }

    if (isFocused)
    {
        float xcursor = mrectTextBar.left + size.GetWidth() + 1.0f;
		float xcursorMax = mrectTextBar.right - 2.0f;

        if (xcursor > xcursorMax) xcursor = xcursorMax;
		DrawLineR(xcursor, mrectTextBar.top - 1.0f, 
            xcursor, mrectTextBar.bottom + 1.0f, cursorColor);
    }

	FinishDraw();
}



void tcEditBox::GetBuffer(char* azDest) 
{
	strncpy(azDest, mzBuffer, MAX_EDITBOX_CHAR-1);
}


const char* tcEditBox::GetBuffer() const
{
    return mzBuffer;
}

/**
* If clearOnReturn is true, a text updated event will be posted
* and the text will be cleared when the return key is pressed.
*/
void tcEditBox::OnKeyDown(wxKeyEvent& event) 
{
    long keycode = event.GetKeyCode();
    int nLength = (int)strlen(mzBuffer);

    if ((keycode == WXK_RETURN) || (keycode == WXK_TAB))
    {
        if (textChanged)
        {
            wxCommandEvent command(wxEVT_COMMAND_TEXT_UPDATED, command) ;    
            command.SetEventObject(this);
            command.SetString(mzBuffer);
            AddPendingEvent(command); // TODO add handler added in tcGame for this event

			textChanged = false;
			if (clearOnReturn)
			{
				lastBuffer = mzBuffer;
				strcpy(mzBuffer, "");
				strcpy(mzBufferHide, "");
				cursorPosition = 0;
				textChanged = true;
			}
        }

		//ReleaseMouse();
    }
    else if (keycode == WXK_BACK)
    {
        if (cursorPosition == 0) return;
		cursorPosition--;
		for (unsigned n=cursorPosition; n<(unsigned)nLength-1; n++)
		{
			mzBuffer[n] = mzBuffer[n+1];
			mzBufferHide[n] = mzBufferHide[n+1];
		}
		nLength--;
        mzBuffer[nLength] = 0;
		mzBufferHide[nLength] = 0;
        textChanged = true;
    }
	else if (keycode == WXK_UP)
	{
		SetBuffer(lastBuffer.c_str());
	}
	else if (keycode == WXK_LEFT)
	{
		if (cursorPosition > 0) cursorPosition--;
	}
	else if (keycode == WXK_RIGHT)
	{
		if (cursorPosition < (unsigned)nLength) cursorPosition++;
	}
    else if (keycode == WXK_ESCAPE)
    {
		ReleaseMouse();

        wxASSERT(GetParent());
        GetParent()->SetFocus();
    }
    else 
    {
        event.Skip(); // OnChar will be called
    }
}

void tcEditBox::OnChar(wxKeyEvent& event) 
{
    long keycode = event.GetKeyCode();
    unsigned int nLength = (unsigned int)strlen(mzBuffer);

	nLength++;

    if (nLength >= MAX_EDITBOX_CHAR-1) {return;}

	for (unsigned n=nLength-1; n>cursorPosition; n--)
	{
		mzBuffer[n] = mzBuffer[n-1];
		mzBufferHide[n] = mzBuffer[n-1];
	}

    mzBuffer[cursorPosition] = (char)keycode;
	mzBufferHide[cursorPosition] = '*';


	mzBuffer[nLength] = 0;
	mzBufferHide[nLength] = 0;
    textChanged = true;

	cursorPosition++;
	if (cursorPosition > (unsigned)nLength) cursorPosition = (unsigned)nLength;

}

void tcEditBox::OnEnterWindow(wxMouseEvent& event)
{
    isMouseOver = true;

	//SetFocus();
}

void tcEditBox::OnLButtonDown(wxMouseEvent& event)
{
	wxPoint pos = event.GetPosition();

	wxRect bounds(0, 0, mnWidth, mnHeight);
	bool clickedInWindow = bounds.Contains(pos);

	if (clickedInWindow)
	{
		if (!wxWindow::HasCapture())
		{
			SetFocus();
			CaptureMouse();
		}
	}
	else
	{
		ReleaseMouse();
	}
}

void tcEditBox::OnLButtonUp(wxMouseEvent& event)
{
    event.Skip();
}

void tcEditBox::OnLeaveWindow(wxMouseEvent& event)
{
    isMouseOver = false;
}

void tcEditBox::OnMouseWheel(wxMouseEvent& event)
{
    if (!enableMouseWheelEvents) return;

    long commandValue = (event.GetWheelRotation() > 0) ? mouseWheelUpCommand : mouseWheelDownCommand;
    wxCommandEvent command(wxEVT_COMMAND_TEXT_UPDATED, commandValue) ;    
    command.SetEventObject(this);
    command.SetString(mzBuffer);
    AddPendingEvent(command);
}

void tcEditBox::OnSetFocus(wxFocusEvent& event)
{
    isFocused = true;
}

/**
* If clearOnReturn is false, a text updated event will be posted
* when the focus is lost.
*/
void tcEditBox::OnKillFocus(wxFocusEvent& event)
{
    if ((textChanged)&&(!clearOnReturn))
    {
        wxCommandEvent command(wxEVT_COMMAND_TEXT_UPDATED, command) ;    
        command.SetEventObject(this);
        command.SetString(mzBuffer);
        AddPendingEvent(command); // TODO add handler added in tcGame for this event
        textChanged = false;
    }
    isFocused = false;
}

void tcEditBox::SetBoxColor(const Vec4& c)
{
    boxColor = c;
}

void tcEditBox::SetBuffer(const char *azBuffer) 
{
    strncpy(mzBuffer,azBuffer,MAX_EDITBOX_CHAR-1);
	
	for (size_t n=0; (n<strlen(azBuffer)) && (n<MAX_EDITBOX_CHAR-1); n++)
	{
		mzBufferHide[n] = '*';
	}

    mzBuffer[MAX_EDITBOX_CHAR-1] = 0;
	mzBufferHide[MAX_EDITBOX_CHAR-1] = 0;
    textChanged = true;

	cursorPosition = (unsigned int)strlen(mzBuffer);
}

void tcEditBox::SetCaption(const char *azCaption) 
{
    strncpy(mzCaption,azCaption,MAX_EDITBOX_CHAR-1);
    mzCaption[MAX_EDITBOX_CHAR-1] = 0;
}

void tcEditBox::SetCaptionAlignment(int type)
{
    captionAlignment = tc3DWindow2::AlignmentType(type);
}

void tcEditBox::SetCaptionFontSize(float val)
{
    captionFontSize = val;
}

void tcEditBox::SetClearOnReturn(bool state) 
{
	clearOnReturn = state;
}

void tcEditBox::SetCommand(long cmd) 
{
	command = cmd;
}

void tcEditBox::SetMouseWheelParameters(long upCommand, long downCommand, bool enable)
{
    mouseWheelUpCommand = upCommand;
    mouseWheelDownCommand = downCommand;
    enableMouseWheelEvents = enable;
}

void tcEditBox::SetTextColor(const Vec4& c)
{
    textColor = c;
}

tcEditBox::tcEditBox(tc3DWindow2 *parent, TiXmlNode *config)
            : tc3DWindow2(parent, wxPoint(0,0), wxSize(10,10), "XMLEditBox", parent),
            isMouseOver(false),
            isFocused(false),
            textChanged(true),
            drawBackground(true),
            boxColor(1, 1, 1, 1),
            textColor(0, 0, 0, 1),
            clearOnReturn(false),
            command(0),
			starText(false),
			cursorPosition(0),
            captionFontSize(fontSize),
            captionAlignment(CENTER_CENTER),
            mouseWheelUpCommand(2),
            mouseWheelDownCommand(1),
            enableMouseWheelEvents(false)
{
    ref_count++;


    strcpy(mzBuffer, "");
	strcpy(mzBufferHide, "");
    strcpy(mzCaption,"Default caption");
    mrectTextBar.left = 5.0f;
	mrectTextBar.bottom = 20.0f;
	mrectTextBar.right = mrectTextBar.left + 160.0f;
    mrectTextBar.top = mrectTextBar.bottom + 14.0f;
    mrectTextCaption = mrectTextBar;
    mrectTextCaption.Offset(-2,-mrectTextBar.Height()-2);

    if (!config) 
    {
        std::cerr << "Error - tcEditBox::tcEditBox - Bad xml node\n";
        return;
    }

    TiXmlElement* current = config->ToElement();
    wxASSERT(current);
    if (current == NULL) return;

    // read window dimensions from XML
    int x;
    int y;
    int width;
    int height;

    current->Attribute("X", &x);
    current->Attribute("Y", &y);
    current->Attribute("Width", &width);
    current->Attribute("Height", &height);

    SetSize(x, y, width, height); // set all size params

    std::string caption = current->Attribute("Caption");
    strcpy(mzCaption, caption.c_str());

    // read text edit bar dimensions from XML
    double barx;
    double bary;
    double barwidth;
    double barheight;
       
    current->Attribute("BarX", &barx);
    current->Attribute("BarY", &bary);
    current->Attribute("BarWidth", &barwidth);
    current->Attribute("BarHeight", &barheight);

    tcRect textBar;
	textBar.Set(barx, barx + barwidth,
		bary, bary + barheight);
    mrectTextBar = textBar;

    mrectTextCaption = mrectTextBar;
    mrectTextCaption.Offset(-2,-mrectTextBar.Height()-2);

    drawBackground = (mrectTextBar.Width() < (float)width);

	double xmlFontSize = 0;
	current->Attribute("FontSize", &xmlFontSize);
	if (xmlFontSize > 0) fontSize = xmlFontSize;

	int passwordMode = 0;
	current->Attribute("PasswordMode", &passwordMode);
	if (passwordMode != 0) starText = true;
}

tcEditBox::~tcEditBox()
{
    wxASSERT(ref_count); 

    ref_count--;
}
