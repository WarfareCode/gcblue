/**
** @file tcControlMessageHandler.cpp
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
#include "wx/string.h"
#include "wx/event.h"

#include "network/tcControlMessageHandler.h"
#include "network/tcMultiplayerInterface.h"
#include "common/tcStream.h"
#include "tcSimState.h"
#include "tcTime.h"
#include "wxcommands.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_NAMESPACE(network)


/**
* Creates a control message. This method is included in the handler
* class to keep send and receive protocol in the same location.
* @param param -- an optional parameter used for some control messages
*/
void tcControlMessageHandler::CreateControlMessage(int messageCode, 
                                                   unsigned& messageSize, unsigned char *data,
                                                   int param)
{
    switch (messageCode)
    {
    case CM_BEEP:
        {
            messageSize = sizeof(messageCode);
            memcpy(data, &messageCode, messageSize);
            return;
        }
        break;
    case CM_TIME:
        {
            tcStream stream;
            stream << messageCode;
            tcSimState::Get()->SaveTimeToStream(stream);
            messageSize = (unsigned int)stream.size();

            stream.read((char*)data, messageSize); // copy from <messageSize> bytes from stream to data
            return;
        }
        break;
    case CM_ALLIANCE:
        {
            tcStream stream;
            stream << messageCode;
            stream << param; // alliance 

            messageSize = (unsigned int)stream.size();
            stream.read((char*)data, messageSize);
        }
        break;
    case CM_PING:
        {
            tcStream stream;
            stream << messageCode;
            
            unsigned int t = tcTime::Get()->GetUpdated30HzCount();
            stream  << t;
            
            messageSize = (unsigned int)stream.size();
            stream.read((char*)data, messageSize);
        }
        break;
    case CM_PONG:
        {
            tcStream stream;
            stream << messageCode;
            
            unsigned int t = (unsigned int)param;
            stream  << t;
            
            messageSize = (unsigned int)stream.size();
            stream.read((char*)data, messageSize);
        }
        break;
    case CM_INGAME:
        {
	        messageSize = sizeof(messageCode);
	        memcpy(data, &messageCode, messageSize);
        }
        break;
    case CM_OUTGAME:
        {
	        messageSize = sizeof(messageCode);
	        memcpy(data, &messageCode, messageSize);
        }
        break;
    case CM_ENDGAME:
        {
	        messageSize = sizeof(messageCode);
	        memcpy(data, &messageCode, messageSize);
        }
        break;
    case CM_SURRENDER:
        {
	        messageSize = sizeof(messageCode);
	        memcpy(data, &messageCode, messageSize);
        }
        break;
    default:
        {
            fprintf(stderr, 
                "tcControlMessageHandler::CreateControlMessage - unrecognized message code (%d)\n",
                messageCode);
            break;
        }

    }
}

void tcControlMessageHandler::Handle(int connectionId, unsigned messageSize, const unsigned char *data)
{

    int messageCode;

    if (messageSize < sizeof(messageCode))
    {
        fprintf(stderr, "Warning - Empty or short control message received by server\n");
        return; 
    }

    /* This constructor makes a copy of the data
    **/
    tcStream stream((const char*)data, messageSize); 

    stream >> messageCode;

	// if server, check to ensure control message is valid
    if (isServer) 
    {
        switch (messageCode)
        {
        case CM_BEEP:
        case CM_PING:
        case CM_PONG:
        case CM_INGAME:
        case CM_OUTGAME:
        case CM_ENDGAME:
        case CM_SURRENDER:
            break;
        default:
			fprintf(stderr, "Warning - illegal control message received by server (%d)\n",
				messageCode);
			return; 
            break;
        }
    }
    else // client
    {
        switch (messageCode)
        {
        case CM_BEEP:
        case CM_TIME:
        case CM_ALLIANCE:
        case CM_PING:
        case CM_PONG:
            break;
        default:
			fprintf(stderr, "Warning - illegal control message received by client (%d)\n",
				messageCode);
			return; 
            break;
        }
    }


    switch (messageCode)
    {
    case CM_BEEP:
        {
        }
        break;
    case CM_TIME:
        {
            tcSimState* simState = tcSimState::Get();
            simState->LoadTimeFromStream(stream);
            fprintf(stdout, "Received time update message from server\n");
        }
        break;
    case CM_ALLIANCE:
        {
            tcSimState* simState = tcSimState::Get();
            int alliance;
            stream >> alliance;

            std::string scenarioName(simState->GetScenarioName());
            std::string scenarioDescription(simState->GetScenarioDescription());

            simState->Clear();

            simState->mpUserInfo->SetOwnAlliance(alliance);
            
            simState->SetMultiplayerClient(); // a hack to get the sensor map to switch to the new alliance (also clears simState)

           // reset these to avoid gap where no info is displayed to player
            simState->SetScenarioName(scenarioName);
            simState->SetScenarioDescription(scenarioDescription);

            fprintf(stdout, "Received alliance update msg from server (%d)\n",
                alliance);
        }
        break;
    case CM_PING:
        {
            unsigned int t0;
            stream >> t0;
            
            tcMultiplayerInterface::Get()->
                SendControlMessageUDP(connectionId, CM_PONG, int(t0));
        }
        break;
    case CM_PONG:
        {
            unsigned int t0;
            stream >> t0;
            
            unsigned int t = tcTime::Get()->GetUpdated30HzCount();
            unsigned int pingTime = t - t0;  
            float ping_s = (1.0f/30.0f) * float(pingTime);
            tcMultiplayerInterface::Get()->
               SetPingTime(connectionId, ping_s);
        }
        break;
    case CM_INGAME: // notification to server that client wants state updates
        {
            tcPlayerStatus& player = tcMultiplayerInterface::Get()->GetPlayerStatus(connectionId);
            player.SetInGame(true);
        }
        break;
    case CM_OUTGAME: // notification to server that client doesn't need state updates
        {
            tcPlayerStatus& player = tcMultiplayerInterface::Get()->GetPlayerStatus(connectionId);
            player.SetInGame(false);
        }
        break;
    case CM_ENDGAME:
        if (isServer)
        {
            tcPlayerStatus& player = tcMultiplayerInterface::Get()->GetPlayerStatus(connectionId);
            player.SetGameEnd(true);
        }
        break;
    case CM_SURRENDER:
        {
            tcPlayerStatus& player = tcMultiplayerInterface::Get()->GetPlayerStatus(connectionId);
            player.SetSurrender(true);
        }
        break;
    default:
        {
            wxASSERT(false);
            fprintf(stderr, "Warning - Unrecognized control message "
                "received by server or client (src:%d, id:%d)\n", connectionId, messageCode);
            return; 
        }
    }

    /*
    wxMessageBox(wxString::Format("Received control message %d", messageCode),
    "Msg received", wxOK);
    */
    
}

tcControlMessageHandler::tcControlMessageHandler()
{
}

tcControlMessageHandler::~tcControlMessageHandler()
{
}

END_NAMESPACE

