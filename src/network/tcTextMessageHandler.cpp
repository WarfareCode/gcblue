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
/** @file tcTextMessageHandler.cpp */

#include "network/tcTextMessageHandler.h"
#include "network/tcMultiplayerInterface.h"
#include "tcMessageInterface.h"

BEGIN_NAMESPACE(network)

/**
* Creates text message.
* @param maxSize maximum size of string to send not including terminating null
*/
void tcTextMessageHandler::CreateMessage(unsigned& messageSize, unsigned char *data, 
        std::string text, unsigned maxSize)
{
    messageSize = (unsigned int)text.length(); 
    if (messageSize > maxSize) messageSize = maxSize;

    //strncpy((char*)data, text.c_str(), messageSize);
    strncpy_s((char*)data, maxSize, text.c_str(), messageSize);

    data[messageSize++] = 0; // append terminating null
}


void tcTextMessageHandler::Handle(int connectionId, unsigned messageSize, const unsigned char *data)
{
    std::string text((char*)data);

    tcMultiplayerInterface* multiplayerInterface = tcMultiplayerInterface::Get();
    if (multiplayerInterface->IsServer())
    {
        // create string with name prepended to text to identify source
        tcPlayerStatus pstatus = multiplayerInterface->GetPlayerStatus(connectionId);
		std::string namedText = std::string("<") + pstatus.GetNameWithRank() + std::string("> ") + text;

        // check if this is a text command
        if (multiplayerInterface->IsCommand(text))
        {
            multiplayerInterface->ProcessCommandClient(connectionId, text);
        }
        else
        {
            // broadcast chat text to all clients
            multiplayerInterface->BroadcastChatText(namedText);
        }
        text = namedText;
    }
	else
	{
		// send to tcMessageInterface in client mode (mode based popups of chat text)
		tcMessageInterface::Get()->PostChatText(text);
		chatText.push(text);
	}

}

tcTextMessageHandler::tcTextMessageHandler(std::queue<std::string>& _chatText)
: chatText(_chatText)
{
}

tcTextMessageHandler::~tcTextMessageHandler()
{
}

END_NAMESPACE

