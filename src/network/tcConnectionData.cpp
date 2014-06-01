/** 
**  @file tcConnectionData.cpp
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

#include "network/tcConnectionData.h"
#include "network/tcNetworkInterface.h"
#include "tcTime.h"
#include <iostream>
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_NAMESPACE(network)

tcNetworkInterface* tcConnectionData::networkInterface = NULL;

/**
* Append msgId's of received messages requesting ack. Update
* size parameters of message.
*/
void tcConnectionData::AttachAckRider(tcMessage* message)
{
	if (message->data.header.riderSize > 0) return; // already has rider (resend)

    unsigned int messageSize = message->GetMessageSize(); // not including header
    // max number of acks assuming 2 bytes per ack
    unsigned int maxAcks = (tcMessage::MESSAGE_SIZE - messageSize) / sizeof(unsigned short);
    unsigned int nAcks = (unsigned int)sendAck.size();
    
	unsigned char* data = message->GetMessageData();
	data += messageSize; // advance to end

	unsigned int riderSize = 0;

    for (unsigned int n=0; (n<nAcks) && (n<maxAcks); n++)
    {
		unsigned short ackId = (unsigned short)sendAck.front();
		sendAck.pop_front();
		memcpy(data, &ackId, sizeof(ackId));
		data += sizeof(ackId);
		riderSize += sizeof(ackId);

		//fprintf(stdout, "Attaching rider ack for %d\n", ackId);
    }

	message->data.header.messageSize += riderSize;
	message->data.header.riderSize = riderSize;

	if (sendAck.size())
	{
		//fprintf(stdout, "- sendAck size: %d\n", sendAck.size());
	}

}

/**
* Process appended ack msgId's. Remove waitForAck id's matching ack msgId's.
* Update size parameters of message.
*/
void tcConnectionData::ProcessAckRider(tcMessage* message)
{
	unsigned int riderSizeBytes = message->data.header.riderSize;
	if (riderSizeBytes == 0) return; // no rider
	
	unsigned int messageSize = message->GetMessageSize(); // not including header
	unsigned int nAcks = riderSizeBytes / sizeof(unsigned short);

	unsigned char* data = message->GetMessageData();
	data += (messageSize - riderSizeBytes); // advance to beginning of rider

	for (unsigned int n=0; n<nAcks; n++)
	{
		unsigned short ackId;
		memcpy(&ackId, data, sizeof(ackId));

        std::list<unsigned int>::iterator iter = waitForAck.begin();
        bool found = false;
        while ((iter != waitForAck.end()) && !found)
        {
            if (*iter == ackId)
            {
                iter = waitForAck.erase(iter);
                found = true;
            }
            else
            {
                ++iter;
            }
        }
        
        if (found)
        {
            networkInterface->ReturnMessage(ackId);
		    //fprintf(stdout, "Received ack rider for %d\n", ackId);
        }
        else
        {
            fprintf(stdout, "Received ack rider for %d but not found in waitForAck\n", ackId); 
        }
        
		data += sizeof(ackId);
	}

	// adjust message size to remove rider
	message->data.header.riderSize = 0;
	message->data.header.messageSize -= riderSizeBytes;

	if (waitForAck.size())
	{
		//fprintf(stdout, "- waitForAck size: %d\n", waitForAck.size());
	}
}


void tcConnectionData::ClearAllMessages()
{
    wxASSERT(networkInterface);
    
    networkInterface->ReturnMessagesFromQueue(readQueueTCP);
    networkInterface->ReturnMessagesFromQueue(readQueueUDP); 
    networkInterface->ReturnMessagesFromQueue(writeQueueTCP); 
    networkInterface->ReturnMessagesFromQueue(writeQueueUDP); 
    
    while(!waitForAck.empty())
    {
        networkInterface->ReturnMessage(waitForAck.back());
        waitForAck.pop_back();
    }    
    sendAck.clear();

    recentReceipts.clear();

    socketErrorCount = 0;
}

const char* tcConnectionData::GetIdString() const
{
	return idString.c_str();
}

const wxIPV4address& tcConnectionData::GetPeerAddress() const
{
	return UDPaddress;
}

float tcConnectionData::GetPingTime() const
{
    return pingTime_s;
}

unsigned int tcConnectionData::GetPingCount() const
{
    return pingCount;
}

/**
* @return total number of bytes read from this connection
*/
unsigned long tcConnectionData::GetReadCount() const
{
    return readCount;
}

/**
* @return number of bytes read from this connection during last sec
*/
unsigned int tcConnectionData::GetReadCountSec() const
{
    return readCount_sec;
}

unsigned int tcConnectionData::GetResentCount() const
{
	return resentCount;
}

wxSocketBase* tcConnectionData::GetSocket()
{
	return socket;
}

/**
* @return total number of bytes written to this connection
*/
unsigned long tcConnectionData::GetWriteCount() const
{
    return writeCount;
}

/**
* @return number of bytes written to this connection during last sec
*/
unsigned int tcConnectionData::GetWriteCountSec() const
{
    return writeCount_sec;
}
    
/**
* Attempts to read next whole message. If message is incomplete, the partial
* message is returned to the socket read buffer. This method does not block.
* Uses tempMessage for temporary storage. When the complete message is collected
* the idx is stored in the appropriate receive queue.
*/
void tcConnectionData::ReadNextMessageTCP()
{    
    wxASSERT(socket);

    // read size field first
    if (tempMessage.bufferIdx == 0)
    {
        socket->Read(tempMessage.data.buffer, tcMessage::SIZE_SIZE);
        tempMessage.bufferIdx += socket->LastCount();
    }

    if (tempMessage.bufferIdx == 0)
    {
        std::cerr << "Warning - tcConnectionData::ReadNextMessage() called with empty read buffer"
            << std::endl;
        return;
    }


    // Read message
    socket->Read(tempMessage.data.buffer + tempMessage.bufferIdx, 
        tempMessage.data.header.messageSize - tempMessage.bufferIdx);
    tempMessage.bufferIdx += socket->LastCount();
    
    if (tempMessage.bufferIdx >= tempMessage.data.header.messageSize)
    {
    }
    else
    {
#ifdef _DEBUG
        fprintf(stdout, " Read partial message: %d bytes of data\n", tempMessage.bufferIdx);
#endif
        return;
    }



    std::string testString;
    testString = (const char*)tempMessage.GetMessageData();

    /*
    tempMessage.buffer[256] = 0;
    wxMessageBox(testString.c_str(),"Message",wxOK);
    */

    int bufferIdx = networkInterface->CheckoutMessage();
    tcMessage *message = networkInterface->GetMessage(bufferIdx);
    if (message == NULL) 
    {
        std::cerr << "Error - Message buffer full, receive message lost" << std::endl;
        tempMessage.Reset();
        return;
    }

    *message = tempMessage;
    message->StampTime();

    readQueueTCP.push(bufferIdx);

    readCount += message->GetMessageSize();
#ifdef _DEBUG
    /*
    fprintf(stdout, " Received message, size: %d, id:%d, t:%d data:%s\n",
        message->GetMessageSize(), message->GetMessageId(), 
        message->GetMessageTimestamp(), testString.c_str());
    */
#endif

    tempMessage.Reset();

}

/**
* Read messageSize bytes from buffer, create message
* and add to UDP receive queue.
*/
void tcConnectionData::ReadNextMessageUDP(unsigned int messageSize, 
                                          unsigned char *buffer)
{
    if (messageSize == 0)
    {
        std::cerr << "Error - empty UDP message received" << std::endl;
        return;
    }
    if (messageSize > tcMessage::BUFFER_SIZE)
    {
        std::cerr << "Error - UDP message size too large"
            << std::endl;
        return;
    }

    int bufferIdx = networkInterface->CheckoutMessage();
    tcMessage *message = networkInterface->GetMessage(bufferIdx);
    if (message == 0) 
    {
        std::cerr << "Error - Message buffer full, UDP receive message lost" 
            << std::endl;
        return;
    }

    memcpy(message->data.buffer, buffer, messageSize);

    unsigned int ackId = message->GetAckId();

    if (!WasRecentlyReceived(ackId))
    {
        recentReceipts.push_back(ackId);
        if (recentReceipts.size() > DUPLICATE_HISTORY) recentReceipts.pop_front();
    }
    else
    {
        fprintf(stderr, "Error - duplicate packet, ignoring (%d)\n", ackId);
        networkInterface->ReturnMessage(bufferIdx);
        return;
    }
    
    

	/* to simulate dropped packets
	if (rand() % 100 < 40)
	{
		networkInterface->ReturnMessage(bufferIdx);
		fprintf(stdout, "DROPPED %d\n", bufferIdx);
		return;
	}
	*/

	ProcessAckRider(message);

	if (message->GetAck())
	{
		sendAck.push_back(ackId);
	}

    message->StampTime();

	readQueueUDP.push(bufferIdx);
	readCount += message->GetMessageSize();
	

    /*
    fprintf(stdout, " Received UDP message, size: %d, id:%d, t:%d\n",
    message->GetMessageSize(), message->GetMessageId(), 
    message->GetMessageTimestamp());
    */
    
}

/**
* Resend any messages waiting for ack up to two times, then delete message
*/
void tcConnectionData::ResendFailedAcks()
{
	// calculate ackTimeout based on ping time
    unsigned int ackTimeout;
	float ping_s = GetPingTime();
	ackTimeout = (unsigned int)(floorf(45.0f * ping_s));
	if (ackTimeout < 10) ackTimeout = 10; // 0.33 s minimum
	else if (ackTimeout > 45) ackTimeout = 45; // 1.5 s maximum

    const unsigned int resendLimit_sec = 8;

    const unsigned short maxResends = 1;
    unsigned int t = tcTime::Get()->Get30HzCount();
    std::list<unsigned int>::iterator iter = waitForAck.begin();
    while (iter != waitForAck.end())
    {
        unsigned int bufferId = *iter;
        tcMessage* msg = networkInterface->GetMessage(bufferId);
        wxASSERT(msg);
        if ((msg->GetMessageTimestamp() - t) > ackTimeout)
        {
            if ((msg->resendCount < maxResends) && (resentCount_sec < resendLimit_sec))
            {
                msg->StampTime();
                msg->resendCount++;
            
                SendUDP(bufferId);
                
				resentCount++;
                fprintf(stdout, "* Resending msg %d (%d)\n",
                    bufferId, msg->resendCount);
            }
            else
			{
				if (resentCount_sec < resendLimit_sec)
				{
					fprintf(stdout, "* Max resend of msg %d reached, deleting\n",
						bufferId);
				}
				else
				{
					fprintf(stdout, "*Resend limit reached, deleting msg %d\n",
						bufferId);
				}
				networkInterface->ReturnMessage(bufferId);
			}
			waitForAck.erase(iter++);
        }
        else
        {
            ++iter;
        }
    }
    
}


/**
* Adds message idx to back of TCP send queue
*/
void tcConnectionData::SendTCP(unsigned int idx)
{
    writeQueueTCP.push(idx);
}

/**
* Adds message idx to back of UDP send queue
*/
void tcConnectionData::SendUDP(unsigned int idx)
{
    writeQueueUDP.push(idx);
}

void tcConnectionData::SetPingTime(float ping_s)
{
    pingTime_s = ping_s;

    pingCount++;
}

void tcConnectionData::SetSocket(wxSocketBase* sock)
{
	socket = sock;
	wxASSERT(socket);

	
    socket->GetPeer(UDPaddress);
    UDPaddress.Service(tcNetworkInterface::UDP_PORT);

    peerName = UDPaddress.IPAddress().c_str();
}

/**
*
*/
void tcConnectionData::Update()
{
    wxASSERT(networkInterface);

    //ReadNextMessage();
    WriteQueuedMessages();

    unsigned int t = tcTime::Get()->Get30HzCount();
    
    if (t - lastResendUpdate >= 30)
    {
        lastResendUpdate = t;
        
        ResendFailedAcks();
    }
    
    if (t - lastCountUpdate >= 150) // average over 5 secs
    {
        lastCountUpdate = t;
        
        readCount_sec = (readCount - lastReadCount)/5;
        writeCount_sec = (writeCount - lastWriteCount)/5;
		resentCount_sec = (resentCount - lastResentCount)/5;

        lastReadCount = readCount;
        lastWriteCount = writeCount;
		lastResentCount = resentCount;
    }
}

/**
* Iterate through recentReceipts and check for match with recently
* received messages. Match indicates duplicate packet.
*/
bool tcConnectionData::WasRecentlyReceived(unsigned int id) const
{
    std::deque<unsigned int>::const_iterator iter = recentReceipts.begin();

    for (; iter!=recentReceipts.end(); ++iter)
    {
        if (*iter == id) return true;
    }

    return false;
}


/**
* Writes next queued message to socket. If capacity of write buffer
* is exceeded, writes part of the message only.
*/
void tcConnectionData::WriteQueuedMessages()
{

    WriteTCP();

    WriteUDP();
}

/**
*
*/
void tcConnectionData::WriteTCP()
{
    if (writeQueueTCP.empty()) return;

    int bufferId = writeQueueTCP.front();

    tcMessage *message = networkInterface->GetMessage(bufferId);

    if (message == NULL)
    {
        std::cerr << "Error - bad message buffer idx." << std::endl;
        writeQueueTCP.pop();
        return;
    }

    //socket->SetFlags(wxSOCKET_WAITALL);

    socket->Write(message->data.buffer + message->bufferIdx, 
        message->data.header.messageSize - message->bufferIdx);

    if (socket->Error())
    {
        socketErrorCount++;
        wxSocketError err = socket->LastError();
        fprintf(stderr, "Error - TCP SocketError %d\n", err);

        if ((err == wxSOCKET_WOULDBLOCK) && (socketErrorCount > 32))
        {
            fprintf(stderr, "     socket->Discard(), flushing buffer\n");
            socket->Discard(); // flush buffer
            socketErrorCount = 0;
        }
    }

    message->bufferIdx += socket->LastCount();

    // pop message from queue and return message buffer if entire
    // message has been written
    if (message->bufferIdx >= message->data.header.messageSize)
    {
        //fprintf(stdout,"Sent message, size:%d, id:%d, t:%d\n",
        //    message->GetMessageSize(), message->GetMessageId(), tcTime::Get()->Get30HzCount());
        writeCount += message->GetMessageSize();
        writeQueueTCP.pop();
        networkInterface->ReturnMessage(bufferId);
    }
    else
    {
        fprintf(stdout,"Sent partial message, buff_idx:%d, id:%d, t:%d\n",
            message->bufferIdx, message->GetId(), tcTime::Get()->Get30HzCount());
    }


    //socket->SetFlags(wxSOCKET_NOWAIT);
}

void tcConnectionData::WriteUDP()
{
    if (writeQueueUDP.empty()) return;

    wxASSERT(networkInterface->GetDatagramSocket());

    unsigned int bufferId = writeQueueUDP.front();

    tcMessage *message = networkInterface->GetMessage((int)bufferId);

    if (message == 0)
    {
        std::cerr << "Error - bad message buffer idx." << std::endl;
        writeQueueTCP.pop();
        return;
    }
    
	// cancel ack if maxWaitingForAck has been exceeded
	if (message->GetAck() && (waitForAck.size() > maxWaitingForAck))
	{
		message->SetAck(false);

		static unsigned errorCount = 0;
		if (errorCount++ < 8)
		{
			fprintf(stderr, "tcConnectionData::WriteUDP() - Ack canceled due to overload (id:%d)\n",
				message->GetId());
		}
	}

    // attach rider to message with ids of packets to ack
    AttachAckRider(message);
    
    wxDatagramSocket *datagramSock = networkInterface->GetDatagramSocket();
    if (datagramSock == NULL)
    {
        std::cerr << "Error - NULL datagram socket" << std::endl;
        return;
    }
    datagramSock->SendTo(UDPaddress, message->data.buffer, message->data.header.messageSize);
    if (datagramSock->Error())
    {
        socketErrorCount++;
        wxSocketError err = socket->LastError();
        fprintf(stderr, "Error - UDP SocketError %d\n", err);

        if ((err == wxSOCKET_WOULDBLOCK) && (socketErrorCount > 32))
        {
            fprintf(stderr, "     socket->Discard(), flushing buffer\n");
            socket->Discard(); // flush buffer
            socketErrorCount = 0;
        }
    }

    writeCount += message->GetMessageSize();
    //fprintf(stdout,"Sent UDP packet to %s, size:%d, id:%d, t:%d\n",
    //    peerName.c_str(), message->GetMessageSize(), message->GetMessageId(), tcTime::Get()->Get30HzCount());

    writeQueueUDP.pop();

    if (message->GetAck())
    {
        // if message needs ack, put id in waitForAck
        waitForAck.push_back(bufferId);
    }
    else
    {
        // otherwise return the message buffer
        networkInterface->ReturnMessage(bufferId);
    }

}


tcConnectionData::tcConnectionData()
    :
    socket(0),
    idString("Err"),
    id(-1),
    readCount(0),
    writeCount(0),
    lastReadCount(0),
    lastWriteCount(0),
	lastResentCount(0),
    readCount_sec(0),
    writeCount_sec(0),
	resentCount_sec(0),
    pingTime_s(999.0f),
    pingCount(0),
    lastCountUpdate(0),
    lastResendUpdate(0),
	resentCount(0),
	maxWaitingForAck(16),
    socketErrorCount(0)
{

}

tcConnectionData::~tcConnectionData()
{
    ClearAllMessages();
    
    if (socket)
    {
        delete socket;
    }
}

END_NAMESPACE

