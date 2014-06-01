/** @file tcNetworkInterface.h*/
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

#ifndef _NETWORKINTERFACE_H_
#define _NETWORKINTERFACE_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "wx/wx.h"
#include "wx/socket.h"
#include "wx/event.h"
#include <list>
#include <vector>
#include <queue>
#include <map>
#include <string>
#include "tcConnectionData.h"
#include "tcMessage.h"
#include "gctypes.h"

#define BEGIN_NAMESPACE(x) namespace x {
#define END_NAMESPACE }

BEGIN_NAMESPACE(network)

class tcNetworkInterface : public wxEvtHandler
{
    friend class tcConnectionData;
public:
    enum
    {
        TCP = 1,
        UDP = 2,
        UDP_ACK = 3,
        TCPIP_PORT = 3000, //6320,
        UDP_PORT = 3011, //6331,
        MESSAGE_BUFFER_SIZE = 128,
        UDP_EVENT_ID = -123,
        MAX_UDP_SIZE = 4096
    };


    const std::list<int>& GetConnectionList() const;
	const std::map<int, tcConnectionData*>& GetConnectionMap();

    const std::string& GetConnectionStatus(int id, int detailLevel = 1);
    tcMessage* GetMessage(int id);
    unsigned int GetNumConnections();
	tcConnectionData* GetConnection(int id);
	bool IsConnecting() const;

    void Clear();
    bool IsServer() const;
    void MakeClient();
    void MakeServer();
    
    void OpenConnection(wxString hostName);
    void CloseConnection();
    void RemoveConnection(int id);
    
    const unsigned char* ReceiveMessage(int connectionId, int& messageId, unsigned& messageSize, 
        int protocol = TCP);
    bool SendMessage(int connectionId, int messageId, unsigned messageSize, 
        const unsigned char *data, int protocol = TCP);
        
    void SetPingTime(int connectionId, float ping_s);

    /// must be called regularly 
    void Update(); 

    tcNetworkInterface();
    virtual ~tcNetworkInterface();
private:
    enum
    {
        NOT_CONNECTED,
        IS_CONNECTING,
        IS_CONNECTED
    } connectState;

    int connectionIndex; ///< counter used to assigned connection id
    bool isServer; ///< true if this interface is acting as a server, false if client
    UINT32 connectionStartTime;
    wxIPV4address hostAddress;

    wxSocketClient *clientSock; ///< single socket that will be used in client mode
    wxSocketServer *serverSock; ///< server socket for server mode
    wxDatagramSocket *datagramSock; ///< UDP socket

	/// map of (connection id, connection data), access (and delete) in log time
    std::map<int, tcConnectionData*> connectionData;
    std::list<int> connectionList; ///< list of connections
    
    std::vector<tcMessage> messageBuffer;
    std::queue<unsigned int> available; ///< fifo of free slot indices

    std::map<std::string, int> peerMap; ///< another lookup (peername, connectionData idx)

    void AddConnection(wxSocketBase *socket); // adds new connection using socket


    void ClearConnectionMessages(int id);
    int CheckoutMessage();


    tcConnectionData* GetConnection(const std::string& peerName);
    wxDatagramSocket* GetDatagramSocket() {return datagramSock;}
    void InitializeUDP();

    void OnSocketEvent(wxSocketEvent& event);
    void RemoveDeadConnections();
    void RemoveBadConnections();
    void ResetMessageBuffer();
    void ReturnMessage(unsigned int idx);
    void ReturnMessagesFromQueue(std::queue<unsigned int>& q);
    void RouteUDP();
    void SendChatText(int destination, const std::string& message);
    void UpdateClient();
    void UpdateClientConnection();
    void UpdateConnections();

    void UpdateServer();

    DECLARE_EVENT_TABLE()
};

END_NAMESPACE

#endif

