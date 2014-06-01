/**  
**  @file tcSoundConsole.h
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


#if !defined _SOUNDCONSOLE_H_
#define _SOUNDCONSOLE_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wx/wx.h"
#include "tcXmlWindow.h"

class tcConsoleBox;

class tcSoundConsole : public tcXmlWindow 
{
public:
	void Clear();
    virtual void Draw();
	tcConsoleBox* GetConsoleBox();
    void Print(const char* line);

    void SetDelayedTextEffect(bool effectOn);
    void SetEffect(const std::string& effect) {soundEffect = effect;}
    void SetLineSpacing(int anSpacing);
    void SetWrap(int n);

    tcSoundConsole(wxWindow* parent, 
        const wxPoint& pos, const wxSize& size, 
		const wxString& configFile,
        const wxString& name = "SoundConsole",
		tc3DWindow2* graphicsHost = 0);
    virtual ~tcSoundConsole();
private:
	tcConsoleBox* textBox;
    std::string soundEffect; ///< sound effect to use when printing text
	unsigned int lastEffect; ///< counter value when last sound effect was played
};

#endif 
