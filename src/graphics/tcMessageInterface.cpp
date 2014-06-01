/** 
**  @file tcMessageInterface.cpp 
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

#include "tcMessageInterface.h"
#include "tcMessageCenter.h"

#include <stdio.h>
#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif 

tcMessageCenter* tcMessageInterface::messageCenter = 0;

/**
*
*/
void tcMessageInterface::ChannelMessage(const std::string& channelName, 
                                               const std::string& msg, unsigned int alliance, const Vec4& color)
{
    wxASSERT(messageCenter);

    messageCenter->AddMessage(channelName, msg, alliance, color);
}

/**
* Clears contents of indicated message channel
*/
void tcMessageInterface::ClearChannel(const std::string& channelName)
{
    wxASSERT(messageCenter);

	messageCenter->ClearChannel(channelName);
}

void tcMessageInterface::ConsoleMessage(const std::string& msg)
{
    wxASSERT(messageCenter);

    messageCenter->ConsoleMessage(msg);
}

/**
*
*/
tcMessageInterface* tcMessageInterface::Get()
{
    static tcMessageInterface instance;

    return &instance;
}

/**
*
*/
void tcMessageInterface::PopupMessage(const std::string& msg, long associatedId)
{
    wxASSERT(messageCenter);

	if (popupsEnabled)
	{
		messageCenter->PopupMessage(msg, associatedId);
	}
}

void tcMessageInterface::PostChatText(const std::string& msg)
{
    wxASSERT(messageCenter);

	messageCenter->PostChatText(msg);
}

void tcMessageInterface::SetPopupChatText(bool state)
{
    wxASSERT(messageCenter);

	messageCenter->SetPopupChatText(state);
}

void tcMessageInterface::SetPopupState(bool state)
{
	popupsEnabled = state;
}

/**
* Must be called before using DisplayChannelMessage
*/
void tcMessageInterface::SetMessageCenter(tcMessageCenter* mc)
{
    messageCenter = mc;
}


/**
*
*/
tcMessageInterface::tcMessageInterface()
: popupsEnabled(true)
{

}

tcMessageInterface::~tcMessageInterface() 
{

}

