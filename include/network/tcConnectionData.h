/** 
**  @file tcConnectionData.h 
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

#ifndef _CONNECTIONDATA_H_
#define _CONNECTIONDATA_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "wx/wx.h"
#include "wx/socket.h"

#include <deque>
#include <list>
#include <queue>
#include <vector>

#include "network/tcMessage.h"

#define BEGIN_NAMESPACE(x) namespace x {
#define END_NAMESPACE }

BEGIN_NAMESPACE(network)


class tcNetworkInterface;

class tcConnectionData 
{
public:
    static tcNetworkInterface *networkInterface; ///< pointer to network interface

    wxString idString; ///< identifier string for source of message
    unsigned int timestamp; ///< start time (tcTime 30 Hz counter) for connection
    int id; ///< identifier number for source of message, -1 for not assigned
    std::queue<unsigned int> readQueueTCP; ///< fifo of TCP received message indices
    std::queue<unsigned int> readQueueUDP; ///< fifo of UDP received message indices
    std::queue<unsigned int> writeQueueTCP; ///< fifo of message indices waiting for TCP transmit
    std::queue<unsigned int> writeQueueUDP; ///< fifo of message indices waiting for UDP transmit
    std::list<unsigned int> waitForAck; ///< vector of transmitted messages waiting for ack
    std::deque<unsigned int> sendAck; ///< dequeue of received messages to send acks for
    std::deque<unsigned int> recentReceipts; ///< duplicate checking, message indices recently received and processed

    unsigned long readCount; ///< number of bytes read from this connection
    unsigned long writeCount; ///< number of bytes written to this connection

    // free all queued messages
    void ClearAllMessages();
	const char* GetIdString() const;
	const wxIPV4address& GetPeerAddress() const;
    unsigned long GetReadCount() const;
	unsigned int GetResentCount() const;
	wxSocketBase* GetSocket();
    unsigned long GetWriteCount() const;
    unsigned int GetReadCountSec() const;
    unsigned int GetWriteCountSec() const; 
    float GetPingTime() const;
    unsigned int GetPingCount() const;
    
    void ReadNextMessageTCP();
    void ReadNextMessageUDP(unsigned int messageSize, unsigned char *buffer);
    void SendTCP(unsigned int idx);
    void SendUDP(unsigned int idx);
    void SetPingTime(float ping_s);
    void SetSocket(wxSocketBase* sock);

    void Update(); ///< read and write data from socket
    void WriteQueuedMessages();

    tcConnectionData();
    ~tcConnectionData();
    
private:
    enum {DUPLICATE_HISTORY = 16}; ///< number of UDP packets to keep history for duplicate checking

    wxSocketBase *socket;   ///< socket associated with this connection
    tcMessage tempMessage; ///< message to use for temporary storage
    unsigned long lastReadCount; ///< read count at last second mark
    unsigned long lastWriteCount; ///< write count at last second mark
	unsigned long lastResentCount; ///< resent count at last second mark

    unsigned int readCount_sec; ///< bytes read over last full second
    unsigned int writeCount_sec; ///< bytes written over last full second
	unsigned int resentCount_sec; ///< bytes resent over last full second
    float pingTime_s; ///< last ping time for this connection
    unsigned int pingCount; ///< number of times ping has been updated
    wxIPV4address UDPaddress;
	wxString peerName;
	unsigned int lastCountUpdate;
	unsigned int lastResendUpdate;
	unsigned long resentCount; ///< number of packets resent because of ack timeout
    unsigned int socketErrorCount; ///< count of socket errors

    /** max number of packets that will be held waiting for ack. If this is exceeded
	 ** UDP packets will be sent without ack request
	 */
    const unsigned int maxWaitingForAck; 

    void AttachAckRider(tcMessage* message);
    void ProcessAckRider(tcMessage* message);
    void ResendFailedAcks();
    bool WasRecentlyReceived(unsigned int id) const;
    void WriteTCP();
    void WriteUDP();
};


END_NAMESPACE

#endif


