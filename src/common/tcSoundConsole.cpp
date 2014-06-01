/** 
** @file tcSoundConsole.cpp
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

#include "tcSoundConsole.h"
#include "tcConsoleBox.h"
#include "tcSound.h"
#include "tcTime.h"
#include "common/tinyxml.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void tcSoundConsole::Clear()
{
	wxASSERT(textBox);

	textBox->Clear();
}

/**
*
*/
void tcSoundConsole::Draw() 
{
    StartDraw();

    if (textBox->Redraw())
    {
		unsigned int counter = tcTime::Get()->Get30HzCount();
		if (counter - lastEffect > 4)
		{
			tcSound::Get()->PlayEffect(soundEffect);
			lastEffect = counter;
		}
    }

    if (!IsBackgroundEnabled())
    {
        DrawRectangleR(0, 0, mnWidth, mnHeight, Vec4(0, 0, 0, 0.5f), FILL_ON);
    }

	FinishDraw();	
}

tcConsoleBox* tcSoundConsole::GetConsoleBox()
{
	wxASSERT(textBox);

	return textBox;
}

void tcSoundConsole::Print(const char* line) 
{
   tcSound::Get()->PlayEffect(soundEffect);
   
   textBox->Print(line);
}

void tcSoundConsole::SetDelayedTextEffect(bool effectOn)
{
	wxASSERT(textBox);

	textBox->SetDelayedTextEffect(effectOn);
}

void tcSoundConsole::SetLineSpacing(int anSpacing)	
{
	wxASSERT(textBox);

	textBox->SetLineSpacing(anSpacing);
}

void tcSoundConsole::SetWrap(int n)	
{
	wxASSERT(textBox);

	textBox->SetWrap(n);

}


tcSoundConsole::tcSoundConsole(wxWindow *parent, 
                         const wxPoint& pos, const wxSize& size, 
						 const wxString& configFile,
                         const wxString& name,
						 tc3DWindow2* graphicsHost) :
    tcXmlWindow(parent, pos, size, configFile, name, graphicsHost),
    soundEffect("consolebeep"),
	lastEffect(0)
{

	if (!config)
	{
		fprintf(stderr, "tcSoundConsole::tcSoundConsole - Missing xml config\n");
        return;
	}

    TiXmlNode* root = config->FirstChild("Window");
    if (!root)
    {
        fprintf(stderr, "tcSoundConsole::tcSoundConsole - Missing top level <Window> tag\n");
        return;
    }

	TiXmlNode* current = root->FirstChild("TextBox");
	
	int topMargin = 0;
	int bottomMargin = 0;
	int wrap = 30;
	if (current)
	{
		TiXmlElement* elt = current->ToElement();
		elt->Attribute("TopMargin", &topMargin);
		elt->Attribute("BottomMargin", &bottomMargin);
		elt->Attribute("Wrap", &wrap);
	}

	textBox = new tcConsoleBox(this, current);
	textBox->SetActive(true);
	textBox->SetSize(0, topMargin, 
		size.GetWidth(), size.GetHeight()  - (topMargin + bottomMargin));

	SetWrap(wrap);
    SetBorderDraw(true);

}

tcSoundConsole::~tcSoundConsole() 
{

}
