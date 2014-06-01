/** @file tcMessage.cpp */
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

#include "network/tcMessage.h"
#include "tcTime.h"
#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_NAMESPACE(network)

/**
* @returns maximum UDP message size in bytes (payload size)
*/
unsigned int tcMessage::GetMaxMessageSize()
{
	return MESSAGE_SIZE;
}


void tcMessage::ClearRider()
{
    wxASSERT(data.header.messageSize > data.header.riderSize);
    
    data.header.messageSize -= data.header.riderSize;
    data.header.riderSize = 0;
}

bool tcMessage::GetAck() const
{
	return data.header.ackFlag != 0;
}



unsigned int tcMessage::GetAckId() const
{
	return data.header.msgId;
}

/**
* @return pointer to start of message data portion of message (follows header)
*/
unsigned char * tcMessage::GetMessageData()
{
    return (data.buffer + HEADER_SIZE);
}



/**
* @return message id from message header
*/
int tcMessage::GetId() const
{
    return data.header.id;
}

/**
* @return size of message in bytes not including header
*/
unsigned int tcMessage::GetMessageSize() const
{
    if (data.header.messageSize >= HEADER_SIZE)
    {
        return data.header.messageSize - HEADER_SIZE;
    }
    else
    {
        wxASSERT(data.header.messageSize >= HEADER_SIZE);
        return 0;
    }
}

/**
*
*/
unsigned int tcMessage::GetMessageTimestamp() const
{
    return timestamp;
}

/**
* @param sourceId connection id of source of message (necessary?)
* @param messageType type code for message
* @param messageId unique identifier for message (short term) for acks
* @param ack 0: no ack requested, 1: send ack
* @param messageSize size of data without any header info
* @param data pointer to messageSize bytes of message data
*/
void tcMessage::PopulateMessage(int sourceId, int messageType, unsigned messageId,
        unsigned int ack, unsigned int messageSize, 
        const unsigned char *messageData)     
{
    if (messageSize > tcMessage::MESSAGE_SIZE)
    {
        wxString text;
        text.Printf("Error - Attempted to send oversized message (%d/%d), truncating.\n", 
            messageSize, tcMessage::MESSAGE_SIZE);
        fprintf(stderr, text.c_str());
        wxMessageBox(text);
        messageSize = tcMessage::MESSAGE_SIZE;
    }
    bufferIdx = 0;    
    timestamp = tcTime::Get()->Get30HzCount();

    data.header.messageSize = messageSize + HEADER_SIZE;
    data.header.sourceId = sourceId;
    data.header.id = messageType;
    data.header.msgId = messageId;
    data.header.ackFlag = ack;
    data.header.riderSize = 0;

    memcpy(data.buffer + HEADER_SIZE, messageData, messageSize);


}

/**
* Reset message state to default / uninitialized
*/
void tcMessage::Reset()
{        
    timestamp = 0;
    bufferIdx = 0;
    resendCount = 0;
    data.header.messageSize = 0;
    data.header.riderSize = 0;
    data.header.id = -1;
    data.header.sourceId = -1;
    data.header.ackFlag = 0;
    data.header.msgId = unsigned int(-1);
}

/**
* Used to set or clear the ack request flag of this message
*/
void tcMessage::SetAck(bool state)
{
	data.header.ackFlag = state ? 1 : 0;
}

/**
* Sets timestamp using current time
*/
void tcMessage::StampTime()
{
    timestamp = tcTime::Get()->Get30HzCount();
}

/**
* tcMessage default constructor
*/
tcMessage::tcMessage()
{
    Reset();
}

/**
* copy constructor
*/
tcMessage::tcMessage(const tcMessage& source)
{
    timestamp = source.timestamp;
    bufferIdx = source.bufferIdx;

    data.header.sourceId = source.data.header.sourceId;
    data.header.messageSize = source.data.header.messageSize;
    wxASSERT(data.header.messageSize <= BUFFER_SIZE);
    if (data.header.messageSize > BUFFER_SIZE) data.header.messageSize = BUFFER_SIZE;
    memcpy(data.buffer, source.data.buffer, data.header.messageSize);
}

/**
* Assignment operator
*/
const tcMessage& tcMessage::operator=(const tcMessage& rhs)
{
    timestamp = rhs.timestamp;
    bufferIdx = rhs.bufferIdx;

    data.header.id = rhs.data.header.id;;

    data.header.sourceId = rhs.data.header.sourceId;

    data.header.messageSize = rhs.data.header.messageSize;
    wxASSERT(data.header.messageSize <= BUFFER_SIZE);
    if (data.header.messageSize > BUFFER_SIZE) data.header.messageSize = BUFFER_SIZE;
    memcpy(data.buffer, rhs.data.buffer, data.header.messageSize);

    return *this;
}

END_NAMESPACE

