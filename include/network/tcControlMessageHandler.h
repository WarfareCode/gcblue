/** 
**  @file tcControlMessageHandler.h
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


#ifndef _CONTROLMESSAGEHANDLER_H_
#define _CONTROLMESSAGEHANDLER_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include <queue>
#include <string>

#include "network/tcMessageHandler.h"

#define BEGIN_NAMESPACE(x) namespace x {
#define END_NAMESPACE }

BEGIN_NAMESPACE(network)

/**
* Control message received handler.
* Control messages are used to do things like start and pause the game
*/
class tcControlMessageHandler : public tcMessageHandler
{
public:
    enum
    {
        CM_BEEP = 1,
        CM_TIME = 3, ///< time message also includes time acceleratin/pause state
        CM_ALLIANCE = 4,
        CM_PING = 5,
        CM_PONG = 6, ///< reply to ping
        CM_INGAME = 7,
        CM_OUTGAME = 8,
        CM_ENDGAME = 9,
        CM_SURRENDER = 10
    };


    static void CreateControlMessage(int messageCode, unsigned& messageSize, unsigned char *data,
        int param = 0);

    virtual void Handle(int connectionId, unsigned messageSize, const unsigned char *data);

    tcControlMessageHandler();
    virtual ~tcControlMessageHandler();
};

END_NAMESPACE

#endif

