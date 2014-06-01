/**
**  @file tcMessageCenter.h 
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


#ifndef _MESSAGECENTER_H_
#define _MESSAGECENTER_H_

#if _MSC_VER > 1000
#pragma once
#endif 

#include "wx/wx.h" 
#include "wx/string.h"
#include <map>
#include "tv_types.h"
#include "tc3DWindow2.h"

class tcButton;
class tcMessageChannel;
class tcSoundConsole;
/**
* 
*/
class tcMessageCenter  : public tc3DWindow2
{
public:
	void ActivateChannel(const std::string& channelName);
    void AddMessage(const std::string& channelName, const std::string& msg, unsigned int alliance, const Vec4& color=Vec4(1, 1, 1, 1));
	void ClearChannel(const std::string& channelName);
    void ConsoleMessage(const std::string& msg);
    void PopupMessage(const std::string& msg, long associatedId = -1);

	/// chat text messages to popup (if enabled)
	void PostChatText(const std::string& msg);

	bool GetPopupChatText() const;
	void SetPopupChatText(bool state);

    static tcMessageCenter* Get();

    void Clear();
    virtual void Draw();
    void AttachConsole(tcSoundConsole* console_);

	tcMessageCenter(wxWindow *parent,
		const wxPoint& pos, const wxSize& size, 
		const wxString& name = "MessageCenter", tc3DWindow2* host = 0);
    virtual ~tcMessageCenter();

private:
    std::map<std::string, tcMessageChannel*> channelMap;
    std::string activeChannelName; ///< name of active channel
    tcRect channelTab; ///< rectangle for next new channel selection button
    tcRect defaultTextRect; ///< text box rectangle for channels
    wxPoint popupBase;
    unsigned int popupCount;
    tcSoundConsole* console;
	bool popupChatText;
	//tcButton* closeButton; ///< button to close this window

    static tcMessageCenter* instance; // pointer to last message center that was created

    tcMessageChannel* GetChannel(const std::string& channelName);
    tcMessageChannel* GetOrCreateChannel(const std::string& channelName);
    virtual void OnLButtonDown(wxMouseEvent& event);
    virtual void OnMouseMove(wxMouseEvent& event);

};

#endif

