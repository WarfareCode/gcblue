/**
*  @file tcAuthenticationMessageHandler.cpp
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

#include "network/tcAuthenticationMessageHandler.h"
#include "network/tcMultiplayerInterface.h"
#include "common/tcStream.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_NAMESPACE(network)


/**
* A request for authentication from server to client
*/
void tcAuthenticationMessageHandler::CreateAuthenticationRequest(unsigned& messageSize, unsigned char *data)
{
	int messageCode = AM_REQUEST;

	messageSize = sizeof(messageCode);
	memcpy(data, &messageCode, messageSize);
}

/**
* A username, password hash response from client to server. The plain text password is hashed once (MD5)
* before sending to server. The server hashes it again before comparing to database value.
* Plaintext passwords are not known at the server and are not stored in the database. 
* Obtaining the account database does not allow access to the account.
*/
void tcAuthenticationMessageHandler::CreateAuthenticationResponse(const std::string& username, const std::string& hash, 
		                                     unsigned& messageSize, unsigned char *data)
{
	int messageCode = AM_RESPONSE;

	tcStream stream;
	stream << messageCode;

	stream << username;
	stream << hash;

	messageSize = (unsigned int)stream.size();
	stream.read((char*)data, messageSize);

}


void tcAuthenticationMessageHandler::Handle(int connectionId, unsigned messageSize, const unsigned char *data)
{
    if (messageSize < sizeof(int))
    {
        fprintf(stderr, "Warning - Empty or short control message received by server\n");
        return; 
    }

    /* This constructor makes a copy of the data
    **/
    tcStream stream((const char*)data, messageSize); 

    int messageCode;
    stream >> messageCode;

	// if server, check to ensure control message is valid
    if (isServer) 
    {
		if (messageCode != AM_RESPONSE)
		{
			fprintf(stderr, "Warning - illegal auth message received by server (%d)\n",
				messageCode);
			return; 
		}
    }
	else
	{
		if (messageCode != AM_REQUEST)
		{
			fprintf(stderr, "Warning - illegal auth message received by client (%d)\n",
				messageCode);
			return; 
		}
	}


    switch (messageCode)
    {
    case AM_REQUEST:
        {
			tcMultiplayerInterface::Get()->SendAuthResponse(connectionId);
        }
        break;
    case AM_RESPONSE:
        {
			std::string username;
			stream >> username;

			std::string passwordHash;
			stream >> passwordHash;

			tcMultiplayerInterface::Get()->AuthenticatePlayer(connectionId, username, passwordHash);
        }
        break;
    
    default:
        {
            fprintf(stderr, "Warning - Unrecognized auth message "
                "received (src:%d, id:%d)\n", connectionId, messageCode);
            return; 
        }
    }

    
}

tcAuthenticationMessageHandler::tcAuthenticationMessageHandler()
{
}

tcAuthenticationMessageHandler::~tcAuthenticationMessageHandler()
{
}

END_NAMESPACE

