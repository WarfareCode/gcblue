/** @file tcMessage.h*/
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

#ifndef _TCMESSAGE_H_
#define _TCMESSAGE_H_

#if _MSC_VER > 1000
#pragma once
#endif

#define BEGIN_NAMESPACE(x) namespace x {
#define END_NAMESPACE }

BEGIN_NAMESPACE(network)

class tcMessage
{
public:
    enum
    {
        BUFFER_SIZE = 2048, /// < max size in bytes of total message including header 
        HEADER_SIZE = 8,
        SIZE_SIZE = 2, ///< size of messageSize field (first field in header)
        MESSAGE_SIZE = BUFFER_SIZE - HEADER_SIZE
    };
    unsigned int timestamp; ///< time in 30 Hz tics when message was created (not sent)
    unsigned short bufferIdx;
    unsigned short resendCount; ///< number of times message has been resent
    union DATA_UNION
    {
        struct HEADER
        {
            unsigned int messageSize : 16; ///< size of message in bytes (including all header fields)
            int sourceId : 16; ///< connection id of source of message
            unsigned int ackFlag : 1; ///< ack msg if 1 (UDP only)
            unsigned int msgId : 15; ///< id of message for ack
            unsigned int riderSize : 10; ///< size in bytes of "rider" message at end
            int id : 6; ///< functional id of message, message type
        } header;
        unsigned char buffer[BUFFER_SIZE]; 
    } data;

    void ClearRider();
	bool GetAck() const;
	unsigned int GetAckId() const;
	
    unsigned char* GetMessageData();
    int GetId() const;
    unsigned int GetMessageSize() const;
    unsigned int GetMessageTimestamp() const;
    void PopulateMessage(int sourceId, int messageType, unsigned messageId,
        unsigned int ack, unsigned int messageSize, 
        const unsigned char *messageData);
    void Reset();
	void SetAck(bool state);
    void StampTime();

	static unsigned int GetMaxMessageSize();

    tcMessage();
    tcMessage(const tcMessage& source);
    const tcMessage& operator=(const tcMessage& rhs);
};

END_NAMESPACE

#endif

