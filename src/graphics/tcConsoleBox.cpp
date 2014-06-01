/** 
**  @file tcConsoleBox.cpp 
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

#include "tcConsoleBox.h"
#include "AError.h"
#include "common/tinyxml.h"
#include "tcScrollBar.h"
#include "wxcommands.h"
#include <stdio.h>
#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif 


BEGIN_EVENT_TABLE(tcConsoleBox, tc3DWindow2)
    EVT_COMMAND(-1, wxEVT_COMMAND_SCROLLBAR_UPDATED, tcConsoleBox::OnScrollbarUpdated)
	EVT_COMMAND(ID_BUTTONREDRAW, wxEVT_COMMAND_BUTTON_CLICKED, tcConsoleBox::OnChildRedraw) 
END_EVENT_TABLE()

using std::min;
using std::max;



void tcConsoleBox::OnChildRedraw(wxCommandEvent& event)
{
	forceRedraw = true;
}

/**
* Catch key events to scroll buffer
*/
void tcConsoleBox::OnKeyDown(wxKeyEvent& event) 
{
	int nChar = event.GetKeyCode();
	

	if (nChar == WXK_PAGEDOWN)
	{
        ScrollBuffer(-SCROLL_LINES);
    }
    else if (nChar == WXK_PAGEUP)
    {
        ScrollBuffer(SCROLL_LINES);
    }
    else
    {
        event.Skip();
    }
}


void tcConsoleBox::OnSize(wxSizeEvent& event)
{
	wxSize s = event.GetSize();
	nyzero = s.GetHeight() - 20;

	tc3DWindow2::OnSize(event);
}

/**
* Prints line, adding wrapped lines if necessary
* don't use a trailing "\n"
*/
int tcConsoleBox::Print(const char* line) 
{
    char zBuff[256];

    int nLen = (int)strlen(line);
    wxASSERT(nwrapcol < 254);

    if (nLen < nwrapcol) 
    {
        return Print(line, nLen+1);
    }

    int nStart = 0;

    while (nStart < nLen) 
    {
        int nWrapLen = nwrapcol;
        bool bSearching = true;
        // search for space to wrap at
        while ((bSearching)&&(nStart+nWrapLen < nLen)) 
        {
            char c = line[nStart+nWrapLen];
            if ((c == ' ')||(nWrapLen > nwrapcol + 8))
            {
                bSearching = false;
            }
           
            if (nWrapLen >= nwrapcol + nwrapbuff) 
            {
                bSearching = false;
            }
            else
            {
                nWrapLen++;
            }
        }
        if (nStart > 0) 
        {
            strcpy(zBuff,"   "); // preprend spaces for wrapped lines
        }
        else {
            strcpy(zBuff,"");
        }
        strncat(zBuff,line+nStart, nWrapLen);
        strcat(zBuff," ");
        Print(zBuff, (int)strlen(zBuff)+1);
        nStart += nWrapLen;
    }
    return 0;
}

int tcConsoleBox::Print(const char* line, int n) 
{
	if (n == 1)
	{
		textArray.Add(" ");
	}
	else
	{
		wxString stemp(line);
		stemp = stemp.BeforeFirst('\n');
		textArray.Add(stemp);
	}

    // restrict buffer size to MAX_LINES
    if (textArray.GetCount() > MAX_LINES)
    {
        textArray.RemoveAt(0, REMOVE_LINES);
        cursorLine -= REMOVE_LINES;
        if (cursorLine < 1) cursorLine = 1;
    }

    redraw = true;

	// update scroll bar parameters
	size_t nLines = textArray.GetCount();
	float barFraction = 123.4f;

	if (nLines > 0)
	{
		barFraction = float(mnHeight - 35) / float(nlinespace*nLines);
	}

	scrollBar->SetBarFraction(barFraction);

    return 0;
}

/**
* Clears the text buffer
*/
void tcConsoleBox::Clear()
{
	textArray.Clear();
	cursorLine = 0;
	cursorCol = 0;
	redraw = true;
}


/**
*
*/
void tcConsoleBox::Draw()
{
    int ind, y;
    static int tcount = 0;

    StartDraw();

    UpdateCursor(); // update cursor position for delayed draw effect

	//if (!redraw && !forceRedraw) return;
    
//	DrawRectangleR(0, 0, mnWidth, mnHeight, Vec4(1, 1, 1, 1));

    size_t nLines = textArray.GetCount(); // number of lines in textArray buffer
    if ((size_t)cursorLine < nLines)
    {
        nLines = (size_t)cursorLine;
    }
    
    if (lineOffset + MIN_LINES_DISPLAY > nLines)
    {
        nLines = min(nLines, (unsigned int)MIN_LINES_DISPLAY);
    }
    else
    {
        nLines -= lineOffset;
    }

    for(size_t i=0;i<nLines;i++) 
    {
        ind = (int)nLines-(int)i-1; // most recent lines are at the end of the buffer
            
        y = nyzero-(int)i*nlinespace;
        if (y<15) break;


        wxString line = textArray[ind];
        if (i==0)
        {
            line = line.Left(cursorCol); // draw up to cursorCol for cursorLine, else draw whole line
        }
        
		DrawTextR(line.c_str(), 8.0f, float(y), defaultFont.get(),
			fontColor, fontSize, LEFT_BASE_LINE, 0);
	}

    forceRedraw = false;
	redraw = false;

	FinishDraw();

}

unsigned int tcConsoleBox::GetLineOffset() const
{
    return lineOffset;
}

void tcConsoleBox::InitFromXml(TiXmlNode* config)
{
    if (!config)
    {
        std::cout << "Using default xml config for ConsoleBox" << std::endl;
        fontSize = 10.0f;
		fontColor = Vec4(0.392f, 1.0f, 0.392f, 1.0f);
		nyzero = mnHeight - 10;
        return;
    }

    /* some of code below could be moved to a parent class so it isn't
    *  repeated so much
    */
    TiXmlElement* current = config->ToElement();
    wxASSERT(current);
    if (current == NULL) return;

    // read window dimensions from XML
    int x;
	int y;
    int width;
    int height;
    int wrap = 50;
	int borderState;

    current->Attribute("X", &x);
    current->Attribute("Y", &y);
    current->Attribute("Width", &width);
    current->Attribute("Height", &height);
    current->Attribute("Wrap", &wrap);
    current->Attribute("DrawBorder", &borderState);
	
	if (width == 0) width = mnWidth;
	if (height == 0) height = mnHeight;

    SetSize(x, y, width, height); // set all size params

    if (wrap < 10) wrap = 50;
    SetWrap(wrap);

	drawBorder = borderState != 0;

	double xmlFontSize;
    current->Attribute("FontSize", &xmlFontSize);
	fontSize = xmlFontSize;
    if (fontSize == 0) fontSize = 10.0f;
	fontColor = Vec4(0.392f, 1, 0.392f, 1);
}


/**
* @return true if current line is empty
*/
bool tcConsoleBox::IsCurrentLineEmpty()
{
    if (textArray.GetCount())
    {
        return (textArray.Last().Length() == 0);
    }
    else
    {
        return true; // no lines in textArray buffer yet
    }
}


void tcConsoleBox::OnScrollbarUpdated(wxCommandEvent& event)
{
	yOffset = 0.25 * float(event.GetExtraLong());

	float maxLines = float(mnHeight) / float(nlinespace);
	unsigned int offset = floorf(yOffset / maxLines);
	SetLineOffset(offset);
}

/**
* Scroll displayed lines of buffer history
*/
void tcConsoleBox::ScrollBuffer(int delta)
{
    int offset = (int)lineOffset + delta;
    if (offset < 0)
    {
        offset = 0;
    }
    else if (offset > (int)textArray.GetCount())
    {
        offset = textArray.GetCount();
    }
    SetLineOffset((unsigned int)offset);
}


void tcConsoleBox::SetLineOffset(unsigned int offset)
{
    lineOffset = offset;
	ForceRedraw();
}

/**
* Updates position of most recent text to draw. This is
* used for the delayed draw effect. If this effect is not
* active, updates cursor to be at end of the most recent
* line.
*/
void tcConsoleBox::UpdateCursor()
{
    if (!useDelayedTextEffect)
    {
        if (cursorLine == (int)textArray.GetCount())
        {
            redraw = false;
            return;
        }
        else
        {
            /* if viewing buffer history (lineOffset > 0), adjust
            ** lineOffset so that view doesn't change as new lines
            ** are added */
            int newLines = (int)textArray.GetCount() - cursorLine;
            if (lineOffset != 0)
            {
                lineOffset += newLines;
            }
            
            if ((cursorLine = (int)textArray.GetCount()) > 0)
            {
                cursorCol = (int)textArray.Last().Length();
            }
            else
            {
                cursorCol = 0;
            }
            redraw = true;
            return;
        }
    }
    if (textArray.GetCount()==0)
    {
        cursorLine = 0;
        cursorCol = 0;
        return;
    }
    bool EOL = cursorCol >= (int)textArray.Last().Length();
    if ((cursorLine == (int)textArray.GetCount()) && EOL)
    {
        redraw = false;
        return; // do nothing, cursor has caught up to buffer
    }
    if (EOL) // advance to next line
    {
        cursorLine++;
        cursorCol = 0;
    }
    else  // advance to next character
    {
        cursorCol++;
    }
    redraw = true;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/**
*
*/
tcConsoleBox::tcConsoleBox(tc3DWindow2 *parent, TiXmlNode *config)
            : tc3DWindow2(parent, parent->GetPosition(), parent->GetSize(), "XMLConsoleBox", parent),
    cursorLine(0),
    cursorCol(0),
    nwrapcol(80),
    useDelayedTextEffect(false),
    redraw(true),
    forceRedraw(true),
    nlinespace(18),
    isMouseOver(false),
    isFocused(false),
	lineOffset(0)
{
	InitFromXml(config);

	const int scrollBarWidth = 12;
	scrollBar = new tcScrollBar(this, wxPoint(mnWidth-scrollBarWidth-3, 4), wxSize(scrollBarWidth, mnHeight - 8));
	scrollBar->SetBackgroundAlpha(0.3f);
	scrollBar->SetSendRedraw(true);
	scrollBar->SetScrollFromBottom(true);
	scrollBar->SetBarFraction(1.0);

    //SetBorderDraw(true);
}

tcConsoleBox::~tcConsoleBox() 
{

}

