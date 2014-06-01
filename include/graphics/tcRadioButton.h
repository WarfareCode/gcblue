/**
**  @file tcRadioButton.h
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



#ifndef _TCRADIOBUTTON_H_
#define _TCRADIOBUTTON_H_

#if _MSC_VER > 1000
#pragma once
#endif 

#include "tc3DWindow2.h"
#include <string>

class TiXmlNode;
class tcButton;

/**
* Radio button class derived from tc3DWindow2.
* XML configuration is required for this control
*/
class tcRadioButton : public tc3DWindow2
{
public:
	void ActivateButton(long buttonCommand);
    virtual void Draw();
    std::string GetCaption() const {return caption;}
	long GetCommand() const {return command;}
    void SetCaption(std::string s) {caption = s;}
    void SetCommand(long cmd) {command = cmd;}
    void SetSoundEffect(int effect) {soundEffect = effect;}
	/// XML configuration required for this control
    tcRadioButton(tc3DWindow2 *parent, TiXmlNode *config);
    virtual ~tcRadioButton();

protected:
    std::vector<tcButton*> buttons; ///< buttons within the radio button control
    std::string caption; ///< title caption for radio button
    long command; ///< command for radio button event
    bool isMouseOver;
    int soundEffect;
    float fontSize;

    static unsigned ref_count;

    virtual void OnButtonCommand(wxCommandEvent& event);
    virtual void OnEnterWindow(wxMouseEvent& event);
    virtual void OnLButtonDown(wxMouseEvent& event);
    virtual void OnLButtonUp(wxMouseEvent& event);
    virtual void OnLeaveWindow(wxMouseEvent& event);

    DECLARE_EVENT_TABLE()
};

#endif

