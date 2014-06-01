/** 
**  @file tcTextEntryBox.h 
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

#ifndef _TEXTENTRYBOX_H_
#define _TEXTENTRYBOX_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "wx/wx.h" 

#include "tcXmlWindow.h"
#include "commandlist.h"

class tcEditBox;
class tcButton;

/**
* User interface window for simple text entry.
* Pops up, user types text, on enter appropriate command message
* with user text is sent and box destroys itself.
* (Similar to tcChatBox, @see tcChatBox)
*/
class tcTextEntryBox : public tcXmlWindow 
{
public:
    void Draw();

    void OnLButtonDown(wxMouseEvent& event);
	void OnChar(wxKeyEvent& event);
	void OnKeyDown(wxKeyEvent& event);


	void SetCaption(const std::string& s);
	void SetCommand(const tsCommandInfo& cmd);
    void SendText(wxCommandEvent& event);

    static void SetParent(tc3DWindow2* par);

    tcTextEntryBox(const wxPoint& pos, const wxSize& size, 
        const wxString& name = "TextEntryBox",
        const wxString& configFile = "xml/text_entry_box.xml");
    virtual ~tcTextEntryBox();
private:
	enum {CLOSE_BUTTON = 386};
    tcEditBox* textEntry;
	tcButton* closeButton;
	std::string caption;
	tsCommandInfo command;
	bool destroyMe;

    static tc3DWindow2* parent;

	virtual void OnCloseCommand(wxCommandEvent& event);


    DECLARE_EVENT_TABLE()
};

#endif
