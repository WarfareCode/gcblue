/** 
**  @file tcMessageCenter.cpp 
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

#include "tcMessageCenter.h"
#include "tcMessageChannel.h"
#include "tcPopupMessage.h"
#include "tcSoundConsole.h"
#include "tcButton.h"
#include "tcTime.h"
#include "common/wxcommands.h"
#include "tcUserInfo.h"

#include <stdio.h>
#include <iostream>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif 


tcMessageCenter* tcMessageCenter::instance = 0;

/**
* Set indicated channel active if it exists, otherwise do nothing
*/
void tcMessageCenter::ActivateChannel(const std::string& channelName)
{
	if (channelName == activeChannelName) return; // already active

    tcMessageChannel* activeChannel = GetChannel(activeChannelName);

    std::map<std::string, tcMessageChannel*>::iterator iter;  
    for (iter = channelMap.begin(); iter != channelMap.end(); ++iter)
    {
        tcMessageChannel* channel = iter->second;
		if (channel->GetName() == channelName)
		{
			channel->SetActive(true);
			if (activeChannel)
			{
				activeChannel->SetActive(false);
			}
			activeChannelName = channelName;
			return;
		}
	}

}

/**
*
*/
void tcMessageCenter::AddMessage(const std::string& channelName, const std::string& msg, unsigned int alliance, const Vec4& color)
{
    tcMessageChannel* channel = GetOrCreateChannel(channelName);
    channel->AddMessage(msg, alliance, color);
}

void tcMessageCenter::AttachConsole(tcSoundConsole* console_)
{
    console = console_;
}

/**
* Removes and deletes all channels
*/
void tcMessageCenter::Clear()
{
    std::map<std::string, tcMessageChannel*>::iterator iter;  
    for (iter = channelMap.begin(); iter != channelMap.end(); ++iter)
    {
        tcMessageChannel* channel = iter->second;
        delete channel;
    }

    channelMap.clear();
    channelTab.Set(10, 80, 10, 30);
}

void tcMessageCenter::ClearChannel(const std::string& channelName)
{
	tcMessageChannel* channel = GetOrCreateChannel(channelName);

	channel->Clear();
}

/**
* Writes a message to the text console
*/
void tcMessageCenter::ConsoleMessage(const std::string& msg)
{
    if (console != 0)
    {
        console->Print(msg.c_str());
    }
    else
    {
        wxASSERT(false);
    }
}

/**
*
*/
void tcMessageCenter::Draw()
{
    tcUserInfo* userInfo = tcUserInfo::Get();
    unsigned int allianceMask = unsigned int(userInfo->GetOwnAlliance());

    StartDraw();

    std::map<std::string, tcMessageChannel*>::iterator iter;  
    for (iter = channelMap.begin(); iter != channelMap.end(); ++iter)
    {
        tcMessageChannel* channel = iter->second;
        channel->Draw(this, allianceMask);
    }

   // DrawLineR(10.0f, 40.0f, float(mnWidth)-10.0f, 40.0f, Vec4(1, 1, 1, 1));
    
    FinishDraw();
}

/**
*
*/
tcMessageChannel* tcMessageCenter::GetChannel(const std::string& channelName)
{
    std::map<std::string, tcMessageChannel*>::iterator iter;
    iter = channelMap.find(channelName);
    if (iter == channelMap.end()) 
    {
        return 0;
    }
    else
    {
        return iter->second;
    }

}

/**
*
*/
tcMessageChannel* tcMessageCenter::GetOrCreateChannel(const std::string& channelName)
{
    tcMessageChannel* channel = 0;
    if (channel = GetChannel(channelName))
    {
        return channel;
    }
    else // create
    {
        channel = new tcMessageChannel(channelName);

        channel->SetActivationRect(channelTab);
        channel->SetTextRect(defaultTextRect);

        // move channelTab to next position
        channelTab.Offset(channelTab.Width() + 4.0, 0);

        channelMap[channelName] = channel;
        return channelMap[channelName];
    }
}

bool tcMessageCenter::GetPopupChatText() const
{
	return popupChatText;
}

/**
*
*/
void tcMessageCenter::OnLButtonDown(wxMouseEvent& event)
{
    wxPoint pos = event.GetPosition();

    tcMessageChannel* clickedChannel = 0;
    tcMessageChannel* activeChannel = GetChannel(activeChannelName);

    std::map<std::string, tcMessageChannel*>::iterator iter;  
    for (iter = channelMap.begin(); iter != channelMap.end(); ++iter)
    {
        tcMessageChannel* channel = iter->second;
        if (channel->IsPointInActivationRect(pos))
        {
            clickedChannel = channel;
        }
    }

    if (clickedChannel == 0) return; // none of the activation buttons were clicked
    if (clickedChannel == activeChannel) return;

    clickedChannel->SetActive(true);
    if (activeChannel)
    {
        activeChannel->SetActive(false);
    }
    activeChannelName = clickedChannel->GetName();
}

/**
*
*/
void tcMessageCenter::OnMouseMove(wxMouseEvent& event)
{
    wxPoint pos = event.GetPosition();

    std::map<std::string, tcMessageChannel*>::iterator iter;  
    for (iter = channelMap.begin(); iter != channelMap.end(); ++iter)
    {
        tcMessageChannel* channel = iter->second;
        if (channel->IsPointInActivationRect(pos))
        {
            channel->SetMouseOver(true);
        }
        else
        {
            channel->SetMouseOver(false);
        }
    }
}

/**
* Pops up a message for the user to see. Manages placement of
* popup to allow multiple popups to be displayed simultaneously.
*
* @param associatedId id of platform or track for "auto hook" feature
*/
void tcMessageCenter::PopupMessage(const std::string& msg, long associatedId)
{
    wxPoint pos = popupBase;
    pos.y += popupCount * 25;


    tcPopupMessage* popup = new tcPopupMessage(msg, pos, 200);
    popup->SetActive(true);
    popup->SetAssociatedId(associatedId);

    popupCount = (popupCount + 1) % 4;
}


void tcMessageCenter::PostChatText(const std::string& msg)
{
	if (popupChatText)
	{
		PopupMessage(msg);
	}
}


void tcMessageCenter::SetPopupChatText(bool state)
{
	popupChatText = state;
}

tcMessageCenter* tcMessageCenter::Get()
{
    return instance;
}

/**
*
*/
tcMessageCenter::tcMessageCenter(wxWindow* parent, const wxPoint& pos, 
							 const wxSize& size, const wxString& name, tc3DWindow2* host)
            : tc3DWindow2(parent, pos, size, name, host),
            activeChannelName(""),
            popupBase(205, 70),
            popupCount(0),
            console(0),
			popupChatText(false)
{
    channelTab.Set(10, 140, 10, 30);
    defaultTextRect.Set(10, size.GetWidth()-100, 50, size.GetHeight()-50);

    //LoadBackgroundImage("background.jpg");

	//const int closeButtonSize = 16;
 //   closeButton = new tcButton(this, wxPoint(mnWidth - closeButtonSize - 1, 1), 
 //       wxSize(closeButtonSize, closeButtonSize));
 //   closeButton->SetActive(true);
 //   closeButton->SetBackgroundAlpha(1.0);
 //   closeButton->SetCaption("");
 //   closeButton->SetCommand(ID_STARTVIEW);
 //   closeButton->LoadImages("close.png", "close.png", "close.png", "close.png");
 //   closeButton->SetSendRedraw(true);

    SetBorderDraw(false);

    instance = this;
}

tcMessageCenter::~tcMessageCenter() 
{
    std::map<std::string, tcMessageChannel*>::iterator iter;  
    for (iter = channelMap.begin(); iter != channelMap.end(); ++iter)
    {
        tcMessageChannel* channel = iter->second;
        delete channel;
    }

    instance = 0;

}

