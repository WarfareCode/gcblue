/** @file tcNetworkInterface.cpp */
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

#include "network/tcNetworkInterface.h"
#include "network/tcTextMessageHandler.h"
#include "tcTime.h"
#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_NAMESPACE(network)

BEGIN_EVENT_TABLE(tcNetworkInterface, wxEvtHandler)
    EVT_SOCKET(-1, tcNetworkInterface::OnSocketEvent)
END_EVENT_TABLE()


/**
* Creates new connection using <socket>
* A new id is assigned. The new connection is added to the peerMap
* and connectionList.
*/
void tcNetworkInterface::AddConnection(wxSocketBase *socket)
{
    tcConnectionData* cdata = new tcConnectionData;

	cdata->SetSocket(socket);

    wxIPV4address addr;
    if (socket->GetPeer(addr)==false)
    {
        std::cerr << "Error getting peer address" << std::endl;
        cdata->idString = "Err2";
    }
    else
    {
       // cdata->idString = wxString::Format("%s:%d",addr.Hostname().c_str(), addr.Service());
        cdata->idString = wxString::Format("%s",addr.IPAddress().c_str());
    }

    cdata->timestamp = tcTime::Get()->Get30HzCount();
    cdata->id = connectionIndex++;

    socket->SetEventHandler(*this, cdata->id);
    socket->SetNotify(wxSOCKET_INPUT_FLAG | wxSOCKET_CONNECTION_FLAG);
    socket->Notify(TRUE);
    socket->SetFlags(wxSOCKET_NOWAIT);

    connectionData[cdata->id] = cdata;
    
	peerMap[std::string(cdata->idString.c_str())] = cdata->id;

    connectionList.push_back(cdata->id);


    fprintf(stdout, "New connection: %s : %d\n", addr.IPAddress().c_str(), addr.Service());
    connectState = IS_CONNECTED;
}

void tcNetworkInterface::RemoveConnection(int id)
{
    std::map<int, tcConnectionData*>::iterator iter = connectionData.find(id);
    if (iter == connectionData.end())
    {
        fprintf(stderr, "Connection id: %d not found in map\n", id);
        return;
    }
    tcConnectionData* connection = iter->second;
    
    // remove from peerMap
    {
        std::string peerName = connection->idString.c_str();
        std::map<std::string, int>::iterator peerMapIter = peerMap.find(peerName);
        if (peerMapIter != peerMap.end())
        {
            peerMap.erase(peerMapIter);
        }
        else
        {
            fprintf(stderr, "Connection id: %d not found in peerMap\n", id); 
        }
    }
    
    // remove from connectionList
    connectionList.remove(id);
    
    
    // remove from connectionData
    delete connection;
    connectionData.erase(iter);
    
    if (connectionData.size() == 0)
    {
        connectState = NOT_CONNECTED;
    }

	// re-init client sock if client
	if (!isServer)
	{
		clientSock = new wxSocketClient(); // leaks
		// subscribe to no events, use polling
		clientSock->Notify(FALSE);
		InitializeUDP();
	}
    
}

/**
* Destroy all sockets
*/
void tcNetworkInterface::Clear()
{        
    // delete all connections first
    std::map<int, tcConnectionData*>::iterator iter = connectionData.begin();
    for ( ; iter != connectionData.end(); ++iter)
    {
        delete iter->second;
    }
    connectionData.clear();
    peerMap.clear();
	connectionList.clear();
	
    if (clientSock)
    {
        // if connected, clientSock is already deleted in connectionData
        if (connectState == IS_CONNECTING) clientSock->Destroy();
        clientSock = 0;
    }
    
    if (serverSock)
    {
        serverSock->Destroy();
        serverSock = 0;
    }

    ResetMessageBuffer();

    connectState = NOT_CONNECTED;

}

/** 
* Free (return to buffer) all queued messages in connection data
*/
void tcNetworkInterface::ClearConnectionMessages(int id)
{
	tcConnectionData* connection = GetConnection(id);

    wxASSERT(connection);
	if (connection == 0)
	{
        fprintf(stderr, "Error - Bad id (%d) passed to ClearConnectionMessages\n", id);
        return;
	}
	
	connection->ClearAllMessages();
}

/**
* Complement of OpenConnection, used by client to close connection to
* server.
*/
void tcNetworkInterface::CloseConnection()
{
    if (isServer)
    {
        fprintf(stderr, 
            "Error - tcNetworkInterface::CloseConnection called in server mode\n");
        return;
    }
    
    if (connectState == NOT_CONNECTED)
    {
        fprintf(stderr,
            "Error - tcNetworkInterface::CloseConnection called while not connected\n");
        return;
    }
    
    Clear();
}

const std::list<int>& tcNetworkInterface::GetConnectionList() const
{
    wxASSERT(connectionList.size() == connectionData.size());
    return connectionList;
}

/**
* For iterating through connections. (Need this?)
*/
const std::map<int, tcConnectionData*>& tcNetworkInterface::GetConnectionMap()
{
	return connectionData;
}



const std::string& tcNetworkInterface::GetConnectionStatus(int id, int detailLevel)
{
	static std::string s;

    unsigned timeCount = tcTime::Get()->Get30HzCount();

    if (connectState == IS_CONNECTING)
    {
        wxString status = wxString::Format("Connecting to %s ", hostAddress.IPAddress().c_str());

        // display "animated" dots while connecting to indicate something is happening
        unsigned animateCount = timeCount % 40;
        if (animateCount >= 10) status += ". ";
        if (animateCount >= 20) status += ". ";
        if (animateCount >= 30) status += ".";

        s = status.c_str();
		return s;
    }

    //if (connectionIdx >= GetNumConnections()) return "Error";

    tcConnectionData* connData = GetConnection(id);
	wxASSERT(connData);
	if (connData == 0)
	{
		s = "Error";
		return s;
	}
	

    float dt_sec = (1.0f/30.0f)*(float)(timeCount - connData->timestamp);
    
    unsigned int bytesIn = connData->GetReadCountSec();
    unsigned int bytesOut = connData->GetWriteCountSec();
	unsigned int resentCount = connData->GetResentCount(); // num packets resent due to failed acks
    float ping_ms = 1000.0f * connData->GetPingTime();

	if (detailLevel <= 0)
	{
		if (dt_sec < 300.0f)
		{
			wxString status = wxString::Format("(%.0f s) ping %.0f ms", 
				dt_sec, ping_ms);
			s = status.c_str();
		}
		else // show connection time in minutes
		{
			wxString status = wxString::Format("(%.0f m) ping %.0f ms", 
				0.0166667f * dt_sec, ping_ms);
			s = status.c_str();
		}
	}
	else
	{
		wxString status = wxString::Format("(%.0f) %04d %04d %03d %.0f", 
			dt_sec, bytesIn, bytesOut, resentCount, ping_ms);
		s = status.c_str();
	}
	return s;
}



/**
* Obtains message buffer if available.
* @return valid id if message buffer is available, -1 otherwise
*/
int tcNetworkInterface::CheckoutMessage()
{
    if (available.empty()) return -1;
    int idx = (int)available.front();
    available.pop();
    return idx;
}

/**
* @return 0 if id is invalid, pointer to connection data otherwise
*/
tcConnectionData* tcNetworkInterface::GetConnection(int id)
{
    std::map<int, tcConnectionData*>::iterator iter = connectionData.find(id);
    
    if (iter != connectionData.end())
    {
        return iter->second;
    }
    else
    {
        return 0; 
    }
}



/**
* Lookup connection by peerName and return pointer to connection data
* @return 0 if idx is invalid, pointer to connection data otherwise
*/
tcConnectionData* tcNetworkInterface::GetConnection(const std::string& peerName)
{
    std::map<std::string, int>::const_iterator mapIter =
                                    peerMap.find(peerName);
    if (mapIter != peerMap.end()) 
    {
        return GetConnection(mapIter->second);
    }
    else
    {
        return 0;
    }
}



tcMessage* tcNetworkInterface::GetMessage(int id)
{
    if ((id < 0)||(id >= (int)messageBuffer.size())) return 0;
    return &messageBuffer[id];
}

unsigned int tcNetworkInterface::GetNumConnections()
{
    if (isServer)
    {
        return (unsigned int)connectionData.size();
    }
    else
    {
        if (connectState == IS_CONNECTED)
        {
            // client mode has one connection to server if connected
            wxASSERT(connectionData.size() == 1);
            wxASSERT(connectionList.size() == 1);
            return 1;
        }
        else if (connectState == NOT_CONNECTED)
        {
            return 0;
        }
        else if (connectState == IS_CONNECTING)
        {
            return 1; // attempted connection counted
        }
        else
        {
            wxASSERT(false);
            return 0;
        }
    }
}

/**
* Initializes UDP datagram socket
* See google groups post "Problem with RecvFrom in wxDatagramSocket (Windows XP)"
*/
void tcNetworkInterface::InitializeUDP()
{
    if (datagramSock) return; // already initialized

    wxIPV4address addr;
    if (!addr.AnyAddress())
    {
        std::cerr << "Error - error configuring datagram socket." << std::endl;
        return;
    }
    addr.Service(UDP_PORT);

    datagramSock = new wxDatagramSocket(addr, wxSOCKET_NOWAIT);
    //datagramSocket->SetTimeout(1);
    datagramSock->SetEventHandler(*this, UDP_EVENT_ID);
    datagramSock->SetNotify(wxSOCKET_INPUT_FLAG);
    datagramSock->Notify(TRUE);

    datagramSock->GetLocal(addr);
    if (!datagramSock->Ok())
    {
        fprintf(stderr, "Error - Dgram sock cannot listen at port %d\n",
            addr.Service());
        return;
    }

    fprintf(stdout, "Created datagram socket on port %d\n",
        addr.Service());
}


bool tcNetworkInterface::IsConnecting() const
{
    return (connectState == IS_CONNECTING);
}

/**
* @return true if this interface is acting as a server
*/
bool tcNetworkInterface::IsServer() const
{
    return isServer;
}



/**
* Destroy all old sockets and initialize clientSock
*/
void tcNetworkInterface::MakeClient()
{   
    Clear();

    isServer = false;
    
    // create the socket
    clientSock = new wxSocketClient();

    // subscribe to no events, use polling
    clientSock->Notify(FALSE);

    InitializeUDP();
}

void tcNetworkInterface::MakeServer()
{
    Clear();

    isServer = true;

    if (hostAddress.Service(TCPIP_PORT) == FALSE)
    {
        fprintf(stderr, "Error - Invalid port: %d \n", TCPIP_PORT);
        return;
    }

    serverSock = new wxSocketServer(hostAddress);

    // We use Ok() here to see if the server is really listening
    if (!serverSock->Ok())
    {
        fprintf(stderr, "Server could not listen at port %d\n", hostAddress.Service());
        return;
    }
    else
    {
        fprintf(stdout, "Server listening at port %d\n", hostAddress.Service());
    }

    serverSock->SetEventHandler(*this, 27);
    serverSock->SetNotify(wxSOCKET_INPUT_FLAG | wxSOCKET_CONNECTION_FLAG);
    serverSock->Notify(TRUE);
    //serverSock->Notify(FALSE);
    serverSock->SetFlags(wxSOCKET_NOWAIT);

    InitializeUDP();
}

void tcNetworkInterface::OnSocketEvent(wxSocketEvent& event)
{
#ifdef _DEBUG
    // std::cout << "Socket event: ";
#endif

    switch(event.GetSocketEvent())
    {
    case wxSOCKET_INPUT:
        {
            //if (event.m_id == UDP_EVENT_ID) // 2.6.3 code
            if (event.GetId() == UDP_EVENT_ID)
            {
#ifdef _DEBUG
                // std::cout << "wxSOCKET_INPUT - UDP"; 
#endif
                RouteUDP();
            }
            else
            {
#ifdef _DEBUG
                // std::cout << "wxSOCKET_INPUT - TCP"; 
#endif
                int connectionId = event.GetId(); // event.m_id; 2.6.3
                tcConnectionData *conn = GetConnection(connectionId);
                if (conn) 
                {
                    conn->ReadNextMessageTCP();
                }
            }

        }
        break;
    case wxSOCKET_LOST: 
        std::cout << "wxSOCKET_LOST" << std::endl; 
        break;
    case wxSOCKET_CONNECTION: 
        std::cout << "wxSOCKET_CONNECTION" << std::endl; 
        break;
    default: 
        std::cout << "Unexpected event!" << std::endl; 
        break;
    }
}

/**
* Opens connection with server specified by hostName.
* @param hostName server address--can be a host name or an IP-style address in dot notation (a.b.c.d)
*/
void tcNetworkInterface::OpenConnection(wxString hostName)
{
    if (isServer)
    {
        std::cerr << "Error - tcNetworkInterface::OpenConnection called in server mode." << std::endl;
        return;
    }
    if (connectState != NOT_CONNECTED)
    {
        std::cerr << 
            "Error - tcNetworkInterface::OpenConnection called while connected or connecting."
            << std::endl;
        return;
    }
    if (clientSock == NULL)
    {
        std::cerr << 
            "Error - tcNetworkInterface::OpenConnection called with NULL clientSock."
            << std::endl;
        return;
    }

    if (hostAddress.Hostname(hostName)==FALSE)
    {
        fprintf(stderr, "Error - Invalid hostname: %s \n", hostName.c_str());
    }
    if (hostAddress.Service(TCPIP_PORT)==FALSE)
    {
        fprintf(stderr, "Error - Invalid port: %d \n", TCPIP_PORT);
    }

    connectState = IS_CONNECTING;
    connectionStartTime = tcTime::Get()->Get30HzCount();


    clientSock->Connect(hostAddress, FALSE); // non-blocking connection request
    fprintf(stdout, "Connecting to %s : %d\n", 
        hostName.c_str(), TCPIP_PORT);
}


/**
* Remove connections that don't have UDP pings, or have other TBD issues
*/
void tcNetworkInterface::RemoveBadConnections()
{
    std::vector<int> badConnections;

    unsigned timeCount = tcTime::Get()->Get30HzCount();

    std::map<int, tcConnectionData*>::iterator iter = connectionData.begin();
    
    for( ; iter != connectionData.end(); ++iter)
    {
        tcConnectionData* connection = iter->second;
        wxASSERT(connection != 0);

        unsigned tics = timeCount - connection->timestamp;
        
        if ((tics > 90) && (connection->GetPingCount() < 2))
        {
            SendChatText(iter->first, "*** UDP ping failure (router or firewall problem?)");
            badConnections.push_back(iter->first);
        }
    }
    

    

    //size_t nBad = badConnections.size();
    //for (size_t n=0; n<nBad; n++)
    //{
    //    RemoveConnection(badConnections[n]);
    //}
}


/**
* Remove connections that have disconnected from connectionData
*/
void tcNetworkInterface::RemoveDeadConnections()
{
    std::vector<int> deadConnections;

    std::map<int, tcConnectionData*>::iterator iter = connectionData.begin();
    
    for( ; iter != connectionData.end(); ++iter)
    {
        tcConnectionData* connection = iter->second;
        wxASSERT(connection->GetSocket());
        if (!connection->GetSocket()->IsConnected())
        {
            deadConnections.push_back(iter->first);
        }
    }
    
    size_t nDead = deadConnections.size();
    for (size_t n=0; n<nDead; n++)
    {
        RemoveConnection(deadConnections[n]);
    }
}


/**
* Clears and re-initializes messageBuffer. Clears all 
* queued read/write/ack messages.  This should be
* called at least once at startup.
*/
void tcNetworkInterface::ResetMessageBuffer()
{
    std::map<int, tcConnectionData*>::iterator iter = connectionData.begin();
    
    for ( ; iter != connectionData.end(); ++iter)
    {
        iter->second->ClearAllMessages();
    }

    messageBuffer.clear();
    while(!available.empty()) available.pop();

    for(unsigned i=0;i<MESSAGE_BUFFER_SIZE;i++)
    {
        tcMessage message;
        messageBuffer.push_back(message);
        available.push(i); // add index to available fifo
    }

}

/**
* return message idx to available 
*/
void tcNetworkInterface::ReturnMessage(unsigned int idx)
{
    available.push(idx);
    messageBuffer[idx].Reset();
}

void tcNetworkInterface::ReturnMessagesFromQueue(std::queue<unsigned int>& q)
{
    while (!q.empty())
    {
        ReturnMessage(q.front());
        q.pop();
    }
}

/**
* @return pointer to message data, data should be immediately used or copied to store
*/
const unsigned char* tcNetworkInterface::ReceiveMessage(int connectionId, int& messageId, 
                                              unsigned& messageSize, int protocol)
{
    tcConnectionData *conn = GetConnection(connectionId);
    if (conn == 0) return 0;

    std::queue<unsigned int> *messageQueue;

    if (protocol == TCP)
    {
        messageQueue = &conn->readQueueTCP;
    }
    else if (protocol == UDP)
    {
        messageQueue = &conn->readQueueUDP;
    }
    else
    {
        return 0; // only TCP and UDP supported 
    }

    // get next message in queue
    if (messageQueue->empty()) return 0; // no messages
    int bufferIdx = messageQueue->front();
    messageQueue->pop();

    tcMessage *message = GetMessage(bufferIdx);
    if (message == 0)
    {
        fprintf(stderr, "Error - Bad index (%d) passed to GetMessage\n",
            bufferIdx);
        return 0;
    }

    messageId = message->GetId();
    messageSize = message->GetMessageSize();

    /* dangerous, fix this, assumes that caller will immediately use or copy
    ** data, and that ReturnMessage will not alter data */
    ReturnMessage(bufferIdx);
    return message->GetMessageData();
}

void tcNetworkInterface::RouteUDP()
{    
    static unsigned char buff[MAX_UDP_SIZE];
    wxIPV4address peerAddr;
    unsigned int messageSize;

    messageSize = MAX_UDP_SIZE;

    datagramSock->RecvFrom(peerAddr, buff, MAX_UDP_SIZE);
    wxString peerName = peerAddr.IPAddress();
    unsigned readCount = datagramSock->LastCount();

#ifdef _DEBUG
    // fprintf(stdout, " Received UDP from %s, size: %d, data: %s\n",
    //     peerName.c_str(), readCount, (char*)buff);
#endif

    tcConnectionData *conn = GetConnection(peerName.ToStdString());
    if (conn == NULL)
    {
        std::cerr << "Error - RouteUDP() peer name not found"
            << std::endl;
        return;
    }
    conn->ReadNextMessageUDP(readCount, buff);
}

/**
* Normally called from tcMultiplayerInterface, here to allow special disconnect messages
* to be sent to client before disconnect
*/
void tcNetworkInterface::SendChatText(int destination, const std::string& message)
{
    char buff[256];
    unsigned messageLength;

    int protocol = tcNetworkInterface::TCP;

    tcTextMessageHandler::CreateMessage(messageLength, (unsigned char*)buff, message, 255);
   
    // MSG_CHATTEXT == 1
    SendMessage(destination, 1, 
        messageLength, (unsigned char*)buff, protocol);
}


bool tcNetworkInterface::SendMessage(int connectionId, int messageId, unsigned messageSize, 
                                     const unsigned char *data, int protocol)
{
    wxASSERT((protocol == TCP)||(protocol == UDP)||(protocol == UDP_ACK));

	tcConnectionData* connection = GetConnection(connectionId);

    if (connection == 0)
    {
        std::cerr << "Error - Connection id not found." << std::endl;
        return false;
    }

    // checkout new message
    int bufferIdx = CheckoutMessage();
    tcMessage *message = GetMessage(bufferIdx);
    if (message == NULL) return false;

    // populate message
    unsigned int doAck = (protocol == UDP_ACK) ? 1 : 0;

    message->PopulateMessage(connectionId, messageId, (unsigned int)bufferIdx,
        doAck, messageSize, data);


    if (protocol == TCP)
    {
        connection->SendTCP(bufferIdx);
    }
    else if ((protocol == UDP) || (protocol == UDP_ACK))
    {
        connection->SendUDP(bufferIdx);
    }
    else
    {
        wxASSERT(false);
        fprintf(stderr, "tcNetworkInterface::SendMessage - bad protocol\n");
        ReturnMessage(bufferIdx);
    }


    return true;
}

/**
* Sets ping time associated with connection
*/
void tcNetworkInterface::SetPingTime(int connectionId, float ping_s)
{
    if (tcConnectionData* conn = GetConnection(connectionId))
    {
        conn->SetPingTime(ping_s);
    }
}


/** 
* Called regularly to poll socket methods. This is done this 
* way to avoid dependencies on the wxWindows event system to 
* make integration easier with non-wxWindows software.
*/
void tcNetworkInterface::Update()
{
    /*
    static unsigned lastUpdate = tcTime::Get()->Get30HzCount();

    if ((tcTime::Get()->Get30HzCount() - lastUpdate) < 15) return;
    lastUpdate = tcTime::Get()->Get30HzCount();
    */
    if (isServer)
    {
        UpdateServer();
    }
    else
    {
        UpdateClient();
    }
}

void tcNetworkInterface::UpdateClient()
{
    if (connectState == NOT_CONNECTED)
    {
        return;
    }
    if (connectState == IS_CONNECTING)
    {
        UpdateClientConnection();
        return;
    }
    
    RemoveDeadConnections();

    UpdateConnections();

}

void tcNetworkInterface::UpdateClientConnection()
{
    wxASSERT (connectState == IS_CONNECTING);
    bool timedOut = tcTime::Get()->GetUpdated30HzCount() - connectionStartTime > 30*5;
    if (timedOut)
    {
        connectState = NOT_CONNECTED;
        std::cerr << "Error - Connection timed out." << std::endl;
        return;
    }
    if (clientSock->WaitOnConnect(0, 10) == FALSE) return; // still trying
    if (clientSock->IsConnected())
    {
        connectState = IS_CONNECTED; // success
        AddConnection(clientSock);
        return;
    }
    else
    {
        connectState = NOT_CONNECTED;

        fprintf(stderr, "Error - Connection with %s refused.\n",
            hostAddress.IPAddress());
        return;
    }
}

void tcNetworkInterface::UpdateConnections()
{
    std::map<int, tcConnectionData*>::iterator iter = connectionData.begin();
    
    for ( ; iter != connectionData.end(); ++iter)
    {
        iter->second->Update(); 
    }
}



void tcNetworkInterface::UpdateServer()
{
	static unsigned lastBadCheck = 0;
    
    unsigned t = tcTime::Get()->Get30HzCount();

    RemoveDeadConnections();

    if (t - lastBadCheck > 150)
    {
        RemoveBadConnections();
        lastBadCheck = t;
    }

	//unsigned t1 = tcTime::Get()->GetUpdated30HzCount();

    // check for new connections
    wxSocketBase *socket = serverSock->Accept(FALSE);

	//unsigned t2 = tcTime::Get()->GetUpdated30HzCount();

    if (socket)
    {
        AddConnection(socket);
    }

	//unsigned t3 = tcTime::Get()->GetUpdated30HzCount();

    UpdateConnections();

	//unsigned t4 = tcTime::Get()->GetUpdated30HzCount();


}


tcNetworkInterface::tcNetworkInterface()
: connectionIndex(1),
  isServer(false),
  connectionStartTime(0),
  clientSock(0),
  serverSock(0),
  datagramSock(0)
{
    tcConnectionData::networkInterface = this;
    connectState = NOT_CONNECTED;
    ResetMessageBuffer();
}

tcNetworkInterface::~tcNetworkInterface()
{
//	if (clientSock) {clientSock->Destroy();}
//	if (serverSock) {serverSock->Destroy();} // crashes in debug
//	if (datagramSock) {datagramSock->Destroy();}

}

END_NAMESPACE

