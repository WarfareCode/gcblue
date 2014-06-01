/** 
**  @file tcMultiplayerInterface.cpp 
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

#include "wx/ffile.h"
#include "network/tcNetworkInterface.h"
#include "network/tcMultiplayerInterface.h"
#include "network/tcMessageHandler.h"
#include "network/tcConnectionData.h"
#include "network/tcAuthenticationMessageHandler.h"
#include "network/tcTextMessageHandler.h"
#include "network/tcControlMessageHandler.h"
#include "network/tcUpdateMessageHandler.h"
#include "common/tcStream.h"
#include "common/tcObjStream.h"
#include <iostream>
#include <queue>
#include "tcSound.h"
#include "tcTime.h"
#include "tcSimState.h"
#include "tcGameObjIterator.h"
#include "tcConsoleBox.h"
#include "tcAccountDatabase.h"
#include "tcUserInfo.h"
#include "scriptinterface/tcSimPythonInterface.h"
#include "scriptinterface/tcScenarioInterface.h"
#include "tcScenarioSelectView.h"
#include "wxcommands.h"
#include "ai/tcMissionManager.h"
#include "database/tcDatabaseIterator.h"
#include "tcAllianceSensorMap.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_NAMESPACE(network)


/**
* Erases map entry for id. Used to force server to resend
* create message for id.
*/
void tcPlayerStatus::EraseEntry(long id)
{
    std::map<long, UpdateInfo>::iterator iter;

    if (id == -1) return;

    iter = lastUpdate.find(id);
    if (iter == lastUpdate.end()) 
    {
        return;
    }
    lastUpdate.erase(iter); // erase entry
}

unsigned char tcPlayerStatus::GetAlliance() const
{
	return alliance;
}

int tcPlayerStatus::GetConnectionId() const
{
    return connectionId;
}

unsigned char tcPlayerStatus::GetGameSpeed() const
{
    return requestedGameSpeed;
}

/**
* Gets time of last update to player for a game object
* @param updateTime [30 Hz tics] set to last updateTime for obj id
* @return true if id exists in update map, false otherwise
*/
bool tcPlayerStatus::GetLastUpdate(long id, unsigned int& updateTime, unsigned int& detailedUpdateTime)
{
    std::map<long, UpdateInfo>::iterator mapIter;

    if (id == -1) return false;

    mapIter = lastUpdate.find(id);
    if (mapIter == lastUpdate.end()) 
    {
        return false;
    }

    updateTime = mapIter->second.updateTime;
    detailedUpdateTime = mapIter->second.detailedUpdateTime;

    return true;
}


const std::string& tcPlayerStatus::GetName() const
{
	return name;
}

const std::string& tcPlayerStatus::GetNameWithRank() const
{
	return nameWithRank;
}

unsigned char tcPlayerStatus::GetRank() const
{
	return rank;
}

bool tcPlayerStatus::IsXmlObserver() const
{
    return isXmlObserver;
}

bool tcPlayerStatus::IsCommander() const
{
    return isCommander;
}

bool tcPlayerStatus::IsGM() const
{
    return (GetRank() == tcUserInfo::RANK_GM);
}

bool tcPlayerStatus::IsInGame() const
{
    return isInGame;
}

bool tcPlayerStatus::IsReady() const
{
	return isReady;
}

void tcPlayerStatus::SetAlliance(unsigned char val)
{
	alliance = val;
}

void tcPlayerStatus::SetConnectionId(int id)
{
    connectionId = id;
}

void tcPlayerStatus::SetGameEnd(bool state)
{
    wantsGameEnd = state;
}

void tcPlayerStatus::SetGameSpeed(unsigned char val)
{
    requestedGameSpeed = val;
}

void tcPlayerStatus::SetInGame(bool state)
{
    isInGame = state;
}

void tcPlayerStatus::SetName(const std::string& s)
{
	name = s;
}

void tcPlayerStatus::SetNameWithRank(const std::string& s)
{
	nameWithRank = s;
}

void tcPlayerStatus::SetRank(unsigned char val)
{
	rank = val;
}

void tcPlayerStatus::SetReady(bool state)
{
	isReady = state;
}

void tcPlayerStatus::SetSurrender(bool state)
{
    wantsSurrender = state;
}

/**
* Updates lastUpdate time. 
* A new map entry is created if this is the first update.
*/
void tcPlayerStatus::SetUpdate(long id, unsigned int updateTime)
{
    if (id == -1) return; // return and do nothing if null idx passed

    lastUpdate[id].updateTime = updateTime;
}

void tcPlayerStatus::SetXmlObserver(bool state)
{
    isXmlObserver = state;
}

/**
* Updates lastUpdate detailed update time. 
* A new map entry is created if this is the first update.
*/
void tcPlayerStatus::SetDetailedUpdate(long id, unsigned int detailedUpdateTime)
{
    if (id == -1) return; // return and do nothing if null idx passed

    lastUpdate[id].detailedUpdateTime = detailedUpdateTime;
}

bool tcPlayerStatus::WantsGameEnd() const
{
    return wantsGameEnd;
}

bool tcPlayerStatus::WantsSurrender() const
{
    return wantsSurrender;
}


/** 
* @return singleton instance 
*/
tcMultiplayerInterface* tcMultiplayerInterface::Get()
{
    static tcMultiplayerInterface instance;
    return &instance;
}

/**
* @return true if entityUpdateReceived flag was set
* clear flag if true
* Used to update simstate when entity update occurs to avoid position glitches
*/
bool tcMultiplayerInterface::EntityUpdateReceived()
{
    return tcUpdateMessageHandler::EntityUpdateReceived();
}

/**
* Adds tcConsoleBox to chat subscriber vector. Chat text will be printed
* to the tcConsoleBox when new text arrives.
*/
void tcMultiplayerInterface::AddChatSubscriber(tcConsoleBox* subscriber)
{
    chatSubscribers.push_back(subscriber);
}

/**
* Removes tcConsoleBox from chat subscriber list
*/
void tcMultiplayerInterface::RemoveChatSubscriber(tcConsoleBox* subscriber)
{

    for(std::vector<tcConsoleBox*>::iterator iter = chatSubscribers.begin()
        ; iter != chatSubscribers.end(); ++iter)
    {
        if ((*iter) == subscriber)
        {
            chatSubscribers.erase(iter);
            return;
        }
    }
    fprintf(stderr, "Error - RemoveChatSubscriber - Not found\n");
}

/**
* Adds message handler for message with messageId.
* tcMessageHandler::Handle method will be called for any matching messages received 
* Currently tcMultiplayerInterface deletes the message handlers--may want to change 
* this such that creator deletes or use shared pointer.
*/
void tcMultiplayerInterface::AddMessageHandler(int messageId, tcMessageHandler* handler)
{
    std::map<int, std::vector<tcMessageHandler*> >::iterator mapIter;

    mapIter = messageMap.find(messageId);
    if (mapIter == messageMap.end()) 
    {
        // create new map pair
        std::vector<tcMessageHandler*> mm;
        mm.push_back(handler);
        messageMap[messageId] = mm; 
    }
    else
    {
        // add handler to existing map pair
        mapIter->second.push_back(handler);
		wxASSERT(false); // duplicate handler
    }
}

/**
* @return true if alliance has commander
*/
bool tcMultiplayerInterface::AllianceHasCommander(unsigned char alliance)
{
	if (alliance == 0) return true; // observers don't count, not sure if default should be true

	const std::list<int>& connectionList = networkInterface->GetConnectionList();
    std::list<int>::const_iterator iter = connectionList.begin();

    for( ; iter != connectionList.end(); ++iter)
    {
        int destination = *iter;    
		
        const tcPlayerStatus& player = GetPlayerStatus(destination);
		if ((player.GetAlliance() == alliance) && (player.IsCommander()))
        {
		    return true;
        }
	}

	return false;
}

/**
* Assign first member of alliance as commander
* should call only when alliance has no commander
*/
void tcMultiplayerInterface::AssignNewCommander(unsigned char alliance)
{
	if (alliance == 0) return; // observers don't count

	const std::list<int>& connectionList = networkInterface->GetConnectionList();
    std::list<int>::const_iterator iter = connectionList.begin();

    for( ; iter != connectionList.end(); ++iter)
    {
        int destination = *iter;    
		
        tcPlayerStatus& player = GetPlayerStatus(destination);
		if (player.GetAlliance() == alliance)
        {
			player.isCommander = true;
		    return;
        }
	}

	// no players found for alliance
}


void tcMultiplayerInterface::AttachMPGameView(tcMPGameView* gv)
{
	mpGameView = gv;
	wxASSERT(mpGameView != 0);
}

void tcMultiplayerInterface::AttachScenarioSelectView(tcScenarioSelectView* ssv)
{
	scenarioSelectView = ssv;
	wxASSERT(scenarioSelectView != 0);
}


/**
* Authenticate (username, passwordHash pair) for connection. 
* If successful set isAuthenticated of player to true, otherwise
* terminate the connection
*/
void tcMultiplayerInterface::AuthenticatePlayer(int connectionId, const std::string& username,
												const std::string& passwordHash)
{
	
	tcPlayerStatus& playerStatus = GetPlayerStatus(connectionId);

	if (playerStatus.name == "error")
	{
		fprintf(stderr, "tcMultiplayerInterface::AuthenticatePlayer -- Bad connection id\n");
		return;
	}

    // first check for valid username
    if ((username.length() < 3) || (username == "NoName"))
    {
        wxString s = wxString::Format("Invalid or missing username (%s)", username.c_str());
        SendChatText(connectionId, s.ToStdString());
        return;
    }

    if (GetPlayerConnectionId(username) != -1)
    {
        wxString s = wxString::Format("A player with your username is already logged in (%s)", username.c_str());
        SendChatText(connectionId, s.ToStdString());
        return;
    }


	int status = tcAccountDatabase::Get()->AuthenticateUser(username, passwordHash);

	wxString msg;
	if (status == tcAccountDatabase::SUCCESS)
	{
		playerStatus.name = username;
		
		int loginStatus = LogInPlayer(username, connectionId, playerStatus, msg);

		if (loginStatus == tcAccountDatabase::SUCCESS)
		{
			playerStatus.isAuthenticated = true;
			SendSoundEffect(connectionId, "Welcome");

			std::vector<int> connectionList;
			connectionList.push_back(connectionId);
			SendScenarioInfo(connectionList);

            SendDatabaseInfo(connectionId);

			wxString s = wxString::Format("*** %s has entered the game", playerStatus.GetNameWithRank().c_str());
			BroadcastChatText(s.ToStdString());
		}
		else if (loginStatus == tcAccountDatabase::DUPLICATE_LOGIN)
		{
			playerStatus.name += "_DUP";
		}
    
	}
	else if (status == tcAccountDatabase::USER_NOT_FOUND)
	{
		// if acceptAllClients then add this user to the database and login
		if (acceptAllClients)
		{
			int status = tcAccountDatabase::Get()->AddUser(username, passwordHash, "unk");
			if (status == tcAccountDatabase::SUCCESS)
			{
				msg.Printf("*** Added account for %s", username.c_str());
				playerStatus.name = username;

				int loginStatus = LogInPlayer(username, connectionId, playerStatus, msg);

				if (loginStatus == tcAccountDatabase::SUCCESS)
				{
					playerStatus.isAuthenticated = true;
					SendSoundEffect(connectionId, "Welcome");

					std::vector<int> connectionList;
					connectionList.push_back(connectionId);
					SendScenarioInfo(connectionList);

                    SendDatabaseInfo(connectionId);

					wxString s = wxString::Format("*** %s has entered the game (new player)", playerStatus.GetNameWithRank().c_str());
					BroadcastChatText(s.ToStdString());
					SendChatText(connectionId, "A new account has been created for you.\n");
					SendChatText(connectionId, "Please choose your alliance with the '/alliance <#>' command");
				}
				else if (loginStatus == tcAccountDatabase::DUPLICATE_LOGIN)
				{
					playerStatus.name += "_DUP";
				}


			}
			else
			{
				msg.Printf("*** Error adding account %s (%d)", username.c_str(), status);
			}
		}
		else
		{
			msg = wxString::Format("Username, %s, is not registered\n", username.c_str());
		}
	}
	else if (status == tcAccountDatabase::PASSWORD_INVALID)
	{
		msg = wxString::Format("Invalid password for username, %s\n", username.c_str());
	}
	else
	{
		msg = "Unknown login error.";
	}

	SendChatText(connectionId, msg.ToStdString());

}

/**
* Logs player in after username/password has been authenticated. Checks for duplicate
* logins, etc.
* @return tcAccountDatabase::SUCCESS if successful
*/
int tcMultiplayerInterface::LogInPlayer(const std::string& username, int connectionId, 
										tcPlayerStatus& playerStatus, wxString& msg)
{
	tcConnectionData* connection = networkInterface->GetConnection(connectionId);
	tcSimState* simState = tcSimState::Get();

	std::string ipAddress = connection->GetIdString();

	int loginStatus = tcAccountDatabase::Get()->LogIn(username, ipAddress);

	if (loginStatus == tcAccountDatabase::SUCCESS)
	{
		tcAccountDatabase::UserData userData;
		tcAccountDatabase::Get()->GetUserData(username, userData);
		
		playerStatus.data = userData;

		playerStatus.SetAlliance(userData.alliance);
		if (simState->GetTime() <= 0) // if game hasn't started yet
		{
			playerStatus.SetAlliance(0); // assign to Observers to start
            playerStatus.SetGameSpeed(1);

            tcAccountDatabase::Get()->SetUserAlliance(username, 0);
		}
		else
		{
			playerStatus.SetReady(true); // always ready if game is in progress
            playerStatus.SetGameSpeed(unsigned char(simState->GetTimeAcceleration()));
		}

        playerStatus.SetXmlObserver(false);
        playerStatus.SetInGame(false);
        playerStatus.SetGameEnd(false);
        playerStatus.SetSurrender(false);


		SendControlMessage(connectionId, tcControlMessageHandler::CM_ALLIANCE, userData.alliance);

		if (playerStatus.alliance != 0)
		{
			SendBriefingText(connectionId, playerStatus.alliance);
		}

		unsigned char rank = tcUserInfo::Get()->ScoreToRank(userData.score);
		playerStatus.SetRank(rank);
		std::string rankString = tcUserInfo::Get()->RankToString(rank);
		rankString += " ";
		rankString += username;
		playerStatus.SetNameWithRank(rankString);
		
		playerStatus.SetConnectionId(connectionId);
		playerToConnection[username] = connectionId;

		// if player's alliance has no commander then make this player commander
		if (!AllianceHasCommander(playerStatus.GetAlliance()))
		{
			playerStatus.isCommander = true;
		}

		msg = wxString::Format("Welcome %s (Alliance %d)\n", playerStatus.GetNameWithRank().c_str(), 
			playerStatus.GetAlliance());

        wxString eventString = wxString::Format("%s logged on (%s)", playerStatus.GetName().c_str(),
            wxDateTime::Now().FormatISOTime().c_str());
        recentEvents.push_back(eventString);
	}
	else if (loginStatus == tcAccountDatabase::DUPLICATE_LOGIN)
	{
		msg = wxString::Format("Username, %s, is already logged in\n", username.c_str());
	}
	else
	{
		msg = wxString::Format("Unknown login error for username, %s\n", username.c_str());
	}

	return loginStatus;
}

/**
* Log out all players that are logged in. Call before shutting down server.
*/
void tcMultiplayerInterface::LogOutAllPlayers()
{
	if (!IsServer()) return;

	for (std::map<int,tcPlayerStatus>::iterator iter = playerInfo.begin();
        iter != playerInfo.end(); ++iter) 
    {
		if (iter->second.isAuthenticated)
		{
			LogOutPlayer(iter->second.name);
			iter->second.isAuthenticated = false;
		}
    }

}

void tcMultiplayerInterface::LogOutPlayer(const std::string& username)
{
	std::map<std::string, int>::iterator iter = 
		playerToConnection.find(username);

	if (iter == playerToConnection.end())
	{
		fprintf(stderr, "tcMultiplayerInterface::LogOutPlayer - %s not found in playerToConnection map\n",
            username.c_str());
		return;
	}

	tcPlayerStatus playerStatus = GetPlayerStatus(iter->second);
	bool playerWasCommander = playerStatus.IsCommander();
	unsigned char playerAlliance = playerStatus.GetAlliance();

    wxString eventString = wxString::Format("%s logged off (%s)", playerStatus.GetName().c_str(),
        wxDateTime::Now().FormatISOTime().c_str());
    recentEvents.push_back(eventString);


	playerToConnection.erase(iter);
	tcAccountDatabase::Get()->LogOut(username);

	// iterate through objects and release control of objects controller by player
	tcGameObjIterator objIter;
//    unsigned updateCount = 0;
    for (objIter.First(); objIter.NotDone(); objIter.Next())
    {
        tcGameObject* obj = objIter.Get();
		if (obj->GetController() == username)
		{
			obj->SetController("");
            obj->SetAccessLevel(0);
		}
	}

	// if departing player was commander, then assign a new commander
	if (playerWasCommander)
	{
		AssignNewCommander(playerAlliance);
	}

}

/**
* Broadcast chat text to all connected clients
* @param alliance 0 to broadcast to all players, otherwise only send to players matching alliance
*/
void tcMultiplayerInterface::BroadcastChatText(const std::string& message, unsigned char alliance)
{
    char buff[256];
    unsigned messageLength;

    int protocol = tcpChat ? tcNetworkInterface::TCP : tcNetworkInterface::UDP;

    tcTextMessageHandler::CreateMessage(messageLength, (unsigned char*)buff, message, 255);
   
	const std::list<int>& connectionList = networkInterface->GetConnectionList();
    std::list<int>::const_iterator iter = connectionList.begin();

    for( ; iter != connectionList.end(); ++iter)
    {
        int destination = *iter;    
		
        tcPlayerStatus& player = GetPlayerStatus(destination);
        if ((alliance == 0) || (player.GetAlliance() == alliance))
        {
		    networkInterface->SendMessage(destination, MSG_CHATTEXT, 
                messageLength, (unsigned char*)buff, protocol);
        }
	}

	if (IsServer())
	{
		chatText.push(message); // echo text here for server so that all chat subscribers receive new text


        // save for html status log (don't save alliance-only chat)
        if (alliance == 0)
        {
            wxString message2 = message;
            message2.Replace("<", "&lt;");
            message2.Replace(">", "&gt;");

            wxString s;
            s.Printf("%s (%s)", message2.c_str(), wxDateTime::Now().FormatISOTime().c_str());
            recentChat.push_back(s);
        }
	}
}

/**
* Broadcast control message to all connected clients
*/
void tcMultiplayerInterface::BroadcastControlMessage(int messageCode)
{
    unsigned char data[64];
    unsigned messageSize;

    tcControlMessageHandler::CreateControlMessage(messageCode, messageSize, data);


	const std::list<int>& connectionList = networkInterface->GetConnectionList();
    std::list<int>::const_iterator iter = connectionList.begin();

    for( ; iter != connectionList.end(); ++iter)
    {
        int id = *iter;

        networkInterface->SendMessage(id, MSG_CONTROL, 
            (messageSize+1), data, 
            tcNetworkInterface::TCP);
	}

}

/**
* Broadcasts database info to all clients
* Should be used when scenario is changed
*/
void tcMultiplayerInterface::BroadcastDatabaseInfo()
{
	const std::vector<int>& destinations = GetConnectionVector();

	SendDatabaseInfo(destinations);
}

/**
* Broadcasts scenario info to all clients
* Should be used when scenario is changed
*/
void tcMultiplayerInterface::BroadcastScenarioInfo()
{
	const std::vector<int>& destinations = GetConnectionVector();

	SendScenarioInfo(destinations);
}


/**
* Clears messageMap, deleting all message handlers
*/
void tcMultiplayerInterface::ClearMessageMap()
{
    std::map<int, std::vector<tcMessageHandler*> >::iterator mapIter;

    mapIter = messageMap.begin();

    for (mapIter = messageMap.begin(); mapIter != messageMap.end();
        ++mapIter)
    {
        std::vector<tcMessageHandler*>& mm = mapIter->second;
        size_t nHandlers = mm.size();
        for (size_t n = 0; n < nHandlers; n++)
        {
            wxASSERT(mm[n]);
            delete mm[n];
        }
        mm.clear();
    }
    messageMap.clear();
}

/*
std::string tcMultiplayerInterface::GetChatText()
{
    if (chatText.empty()) return "ERROR";
    std::string text = chatText.front();
    chatText.pop();
    return text;
}
*/

bool tcMultiplayerInterface::GetAcceptAllClients() const
{
	return acceptAllClients;
}

const std::list<int>& tcMultiplayerInterface::GetConnectionList() const
{
	return networkInterface->GetConnectionList();
}


const std::string& tcMultiplayerInterface::GetConnectionStatus(int connectionId)
{
	static std::string s;

	if (!IsConnecting())
	{
		const tcPlayerStatus& status = GetPlayerStatus(connectionId);

		wxString s2 = wxString::Format("%s (%d) ", status.GetName().c_str(), 
			status.GetAlliance());

		s = s2.c_str();
	}
	else
	{
		s = "";
	}

	s += networkInterface->GetConnectionStatus(connectionId).c_str();
	
    return s;
}

/**
* Version that returns list of connection ids as vector (more expensive)
*/
const std::vector<int>& tcMultiplayerInterface::GetConnectionVector() const
{
	static std::vector<int> connectionVector;

	connectionVector.clear();
	const std::list<int>& connectionList = GetConnectionList();
	for (std::list<int>::const_iterator k=connectionList.begin();
		 k != connectionList.end(); ++k)
	{
		connectionVector.push_back(*k);
	}

	return connectionVector;
}

wxEvtHandler* tcMultiplayerInterface::GetEvtHandler() const
{
    wxASSERT(evtHandler);
    return evtHandler;
}

/**
* @return identification name string for player using this interface
*/
const std::string& tcMultiplayerInterface::GetName() const
{
    return myName;
}

unsigned int tcMultiplayerInterface::GetNumConnections()
{
    return networkInterface->GetNumConnections();
}

/**
* @return hashed password string for player using this interface
*/
const std::string& tcMultiplayerInterface::GetPassword() const
{
    return passwordHash;
}

/**
* @return -1 if not found
*/
int tcMultiplayerInterface::GetPlayerConnectionId(const std::string& playerName)
{
	std::map<std::string, int>::const_iterator iter = 
		playerToConnection.find(playerName);

	if (iter != playerToConnection.end())
	{
		return iter->second;
	}
	else
	{
		return -1;
	}
}

const std::string& tcMultiplayerInterface::GetPlayerName(int connectionId)
{
	return GetPlayerStatus(connectionId).GetName();
}

/**
* @return tcPlayerStatus object associated with connectionId
* @see tcPlayerStatus
*/
tcPlayerStatus& tcMultiplayerInterface::GetPlayerStatus(int connectionId)
{
    std::map<int,tcPlayerStatus>::iterator mapIter;

    mapIter = playerInfo.find(connectionId);
    if (mapIter == playerInfo.end()) 
    {
        fprintf(stderr, "Error - tcMultiplayerInterface::GetPlayerStatus  - "
            "conn id: %d not found\n", connectionId);
        return errorPlayerStatus;
    }

    return mapIter->second;
}


unsigned tcMultiplayerInterface::GetTeamGameSpeed() const
{
    wxASSERT(mpGameView != 0);

    return mpGameView->GetTeamSpeed();
}

unsigned tcMultiplayerInterface::GetFastestGameSpeed() const
{
    wxASSERT(mpGameView != 0);

    return mpGameView->GetFastestSpeed();
}


/**
* Clear message map and (re)initialize based on 
* multiplayer mode.
*/
void tcMultiplayerInterface::InitMessageHandlers()
{
    ClearMessageMap();

    // common handlers
    // register chat text message handler
    AddMessageHandler(MSG_CHATTEXT, new tcTextMessageHandler(chatText));
    AddMessageHandler(MSG_CONTROL, new tcControlMessageHandler());
	AddMessageHandler(MSG_AUTHENTICATION, new tcAuthenticationMessageHandler());

    if (IsServer())
    { // server-specific handlers
        // server needs update msg handler to handle command updates from client
        AddMessageHandler(MSG_UPDATE, new tcUpdateMessageHandler());
    }
    else
    { // client-specific handlers
        AddMessageHandler(MSG_UPDATE, new tcUpdateMessageHandler());
    }
}

bool tcMultiplayerInterface::IsChatTextAvail()
{
    return !chatText.empty();
}

/**
* Tests if text is a command. Commands start with a
* forward slash '/'
* @return true if text is a (server) command
*/
bool tcMultiplayerInterface::IsCommand(const std::string& text)
{
    wxString candidate(text.c_str());
    return ((candidate.find('/') == 0));
}

bool tcMultiplayerInterface::IsConnecting() const
{
	if (IsServer()) return false;

	return (networkInterface->IsConnecting());
}

/**
* Check for mutually agreed end of game, or surrender of one team
*/
bool tcMultiplayerInterface::IsGameOver(wxString& message) const
{
    message.clear();

    std::vector<tcMPGameView::TeamInfo>& teamList = tcUpdateMessageHandler::GetLatestTeamList();

	size_t nTeams = teamList.size();

    bool anyPlayersInGame = false;
    bool allPlayersEndGame = true;
    bool anyPlayerSurrender = false;
    unsigned char surrenderAlliance;
    std::string surrenderName;

	for (size_t n=0; n<nTeams; n++)
	{
		tcMPGameView::TeamInfo& teamInfo = teamList[n];

		size_t nPlayers = teamList[n].playerList.size();
		
		for (size_t k=0; k<nPlayers; k++)
		{
            anyPlayersInGame = true;
            allPlayersEndGame = allPlayersEndGame && teamList[n].playerList[k].endGame;
            
            if (teamList[n].playerList[k].surrenderGame)
            {
                anyPlayerSurrender = true;
                surrenderAlliance = teamInfo.alliance;
                surrenderName = teamInfo.name;
            }
		}
    }

    tcSimState* simState = tcSimState::Get();
    bool noplayerTimeout = (!anyPlayersInGame) && (simState->GetTime() > 60.0);

    bool gameOver = noplayerTimeout || 
        (anyPlayersInGame && (allPlayersEndGame || anyPlayerSurrender));

    if (gameOver)
    {
        if (noplayerTimeout)
        {
            message.Printf("Game ended, no players remaining");
        }
        else if (allPlayersEndGame)
        {
            message.Printf("Game ended by agreement between players");
        }
        else
        {
            message.Printf("Game ended when %s surrendered", surrenderName.c_str());
        }
        return true;
    }
    else
    {
        return false;
    }
}

bool tcMultiplayerInterface::IsNewPlayer(int id)
{
    std::map<int,tcPlayerStatus>::const_iterator mapIter;

    mapIter = playerInfo.find(id);
    if (mapIter == playerInfo.end()) 
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
* @return true if acting as a server
*/
bool tcMultiplayerInterface::IsServer() const
{
    return networkInterface->IsServer();
}

void tcMultiplayerInterface::MakeClient()
{
	if (IsServer()) LogOutAllPlayers();

    networkInterface->MakeClient();
    tcMessageHandler::SetAsClient();
    InitMessageHandlers();
}


void tcMultiplayerInterface::MakeServer()
{
    networkInterface->MakeServer();
    tcMessageHandler::SetAsServer();
    InitMessageHandlers();

	myName = "SERVER";

    logFilePath = tcOptions::Get()->GetOptionString("ServerLogFile");
}

/**
* Resets network interface to initial client state.
* This will close all open connections.
* (Same implementation as MakeClient())
*/
void tcMultiplayerInterface::Reset()
{
	MakeClient();
}


/**
* Call when new scenario is loaded. Resets all players to observer team.
*/
void tcMultiplayerInterface::ResetGame()
{
	const std::list<int>& connectionList = networkInterface->GetConnectionList();
    std::list<int>::const_iterator iter;

    for(iter = connectionList.begin() ; iter != connectionList.end(); ++iter)
    {
        int id = *iter;

		tcPlayerStatus& player = GetPlayerStatus(id);

		player.SetAlliance(0);
		player.isCommander = false;
        player.isInGame = false;
        player.wantsGameEnd = false;
        player.wantsSurrender = false;
	}

    wxString eventString = wxString::Format("Game reset (%s)", wxDateTime::Now().FormatISOTime().c_str());
    recentEvents.push_back(eventString);

    BroadcastScenarioInfo();

    lastOptionsUpdate = tcTime::Get()->GetUpdated30HzCount() - 60;
}


/**
* Call at client when lost connection to server
*/
void tcMultiplayerInterface::OnLostServer()
{
    chatText.push(std::string("Lost connection to server"));
    wxMessageBox("Lost connection to server", "Network", wxICON_WARNING);

    MakeClient();
}


void tcMultiplayerInterface::OpenConnection(const std::string& hostName)
{
    networkInterface->OpenConnection(hostName.c_str());
}


/**
* Send queued chat text to subscribers. This should be periodically called
* as part of the update method
*/
void tcMultiplayerInterface::DistributeChatText()
{
    while (!chatText.empty())
    {
        std::string text = chatText.front();
        chatText.pop();

        for(std::vector<tcConsoleBox*>::iterator iter = chatSubscribers.begin()
            ; iter != chatSubscribers.end(); ++iter)
        {
            (*iter)->Print(text.c_str());
        }
    }

}

/**
* Process command to change alliance of player
*/
void tcMultiplayerInterface::ProcessAllianceCommand(tcPlayerStatus& player, const wxString& args)
{
    wxString msg;
    
    int connectionId = player.GetConnectionId();
    
	tcSimState* simState = tcSimState::Get();
    bool changeAllowed = player.data.CanSwitchAlliance() || 
                         simState->IsMultiplayerGameStarted() || 
                         allowAllTeamChanges;

    if (changeAllowed)
    {
    	wxString allianceText = args; 
    	long alliance;
    	if (allianceText.ToLong(&alliance))
    	{
    		player.alliance = alliance;
    		tcAccountDatabase::Get()->SetUserAlliance(player.GetName(), player.alliance);
    
			SendControlMessage(connectionId, tcControlMessageHandler::CM_ALLIANCE, alliance);
			msg = wxString::Format("*** Success - alliance set to %d", alliance);

			// update briefing text for new alliance
			if (alliance != 0)
			{
				SendBriefingText(connectionId, alliance);
				SendScenarioInfo(connectionId);

				// if player's new alliance has no commander then make this player commander
				if (!AllianceHasCommander(player.GetAlliance()))
				{
					player.isCommander = true;
				}
			}
            else
            {
                player.isCommander = false;
            }

            player.SetReady(false); // clear ready status on side change
		}
    	else
    	{
            msg = wxString::Format("*** Error - bad alliance change argument (%s)",
                      allianceText.c_str());
    	}
    }
    else
    {
        msg = "*** Team change not allowed while game in progress";
    } 
    
    SendChatText(connectionId, msg.ToStdString());
}


/**
*
*/
void tcMultiplayerInterface::ProcessChangeCommander(tcPlayerStatus& player, const wxString& args)
{
	wxString msg;
    
    int connectionId = player.GetConnectionId();

	unsigned char alliance = player.GetAlliance();

	if (alliance == 0)
	{
		msg = "*** Cannot change commander while on Observer team";
		SendChatText(connectionId, msg.ToStdString());
		return;
	}

	if (player.IsCommander() || (!AllianceHasCommander(alliance)))
	{
		int newCommanderId = GetPlayerConnectionId(args.ToStdString());
		if (newCommanderId != -1)
		{
			tcPlayerStatus& pstatus = GetPlayerStatus(newCommanderId);
			player.isCommander = false;
			pstatus.isCommander = true;
			
			msg.Printf("*** %s is now team commander", pstatus.GetNameWithRank().c_str());
			BroadcastChatText(msg.ToStdString());
			return;
		}
		else
		{
			msg.Printf("*** player %s not found", args.ToAscii());
		}

	}
	else
	{
		msg = "*** Failed. Ask team commander to change commander";
	}

	SendChatText(connectionId, msg.ToStdString());
}



/**
*
*/
void tcMultiplayerInterface::ProcessChangeReady(tcPlayerStatus& player, const wxString& args)
{
	wxString msg;
    
    int connectionId = player.GetConnectionId();


	if (args != "0")
	{
		if (!player.IsReady())
		{
			player.SetReady(true);
			msg = "*** Your status is now READY";
		}
		else
		{
			msg = "*** Status already is ready";
		}
	}
	else
	{
		if (player.IsReady())
		{
			player.SetReady(false);
			msg = "*** Your status is now STAND DOWN";
		}
		else
		{
			msg = "*** Status already is stand down";
		}
	}

	SendChatText(connectionId, msg.ToStdString());
}


/**
* Process game master commands from player
*/
void tcMultiplayerInterface::ProcessGameMasterCommand(tcPlayerStatus& player, const wxString& args)
{
    wxASSERT(IsServer());
    
    using scriptinterface::tcScenarioInterface;
    tcScenarioInterface* scenarioInterface = tcSimPythonInterface::Get()->GetScenarioInterface();
    wxASSERT(scenarioInterface);
    tcSimState* simState = tcSimState::Get();
    
    int connectionId = player.GetConnectionId();

    bool syntaxError = true;
    wxString msg;
    
    if (player.IsGM())
    {
        wxString command = args.BeforeFirst(' ');
        wxString params = args.AfterFirst(' '); 
 
        if ((command == "help") || (command == ""))
        {
            syntaxError = false;
            SendChatText(connectionId, "*** /gm help ***");
            SendChatText(connectionId, "    /gm help - print GM command list");
            SendChatText(connectionId, "    /gm addaccount '<username>' '<email>'");
         //   SendChatText(connectionId, "    /gm getaccountdata '<username>' '<param>'");
         //   SendChatText(connectionId, "    /gm setaccountdata '<username>' '<param>' <value>");
            SendChatText(connectionId, "    /gm create '<class>' '<unitname>' <alliance> <lat_deg> <lon_deg> (<alt_m>)");
            SendChatText(connectionId, "    /gm destroy <id>");
            SendChatText(connectionId, "    /gm kick '<playername>'");
            SendChatText(connectionId, "    /gm move <id> <lat_deg> <lon_deg> (<alt_m>)");
         //   SendChatText(connectionId, "    /gm reload <id>");
            SendChatText(connectionId, "    /gm repair <id>");
         //   SendChatText(connectionId, "    /gm setalliance <id> <alliance>");
            SendChatText(connectionId, "    /gm setcontroller <id> '<player>'");
            SendChatText(connectionId, "    /gm setteamchanges <0 or 1>");
        }
		else if (command == "addaccount")
		{
			syntaxError = false;

			ProcessGMAddAccount(args, msg);
		}
        else if (command == "create")
        {
            syntaxError = false;
            
            ProcessGMCreate(args, msg);
        }
        else if (command == "destroy")
        {
    	    long id;
    	    if (params.ToLong(&id))
    	    {
                syntaxError = false;
                simState->DeleteObject(id);
                msg = wxString::Format("*** Entity %d destroyed", id);
            }
        }
        else if (command == "kick")
        {
            syntaxError = false;

    	    ProcessGMKick(args, msg);
        }
        else if (command == "move")
        {
            syntaxError = false;
            
            ProcessGMMove(args, msg);
        }
        else if (command == "repair")
        {
            long id;
    	    if (params.ToLong(&id))
    	    {
                syntaxError = false;
                if (tcGameObject* obj = simState->GetObject(id))
                {
                    obj->ApplyRepairs(2.0f);
                    msg = wxString::Format("*** Entity %d repaired", id);
                }
                else
                {
                    msg = wxString::Format("*** Entity %d not found", id);
                }
            }
        }
        else if (command == "setcontroller")
        {
            syntaxError = false;
            ProcessGMSetController(args, msg);
        }
        else if (command == "setteamchanges")
        {
            syntaxError = false;
            ProcessGMSetTeamChanges(args, msg);
        }
    }
    else
    {
        syntaxError = false;
        msg = "*** Denied - insufficient permissions for /gm commands";
    }
    
    if (syntaxError)
    {
        msg = wxString::Format("*** Syntax error (%s)", args.c_str());
    }
    
    SendChatText(connectionId, msg.ToStdString());
}

void tcMultiplayerInterface::ProcessGameSpeed(tcPlayerStatus& player, const wxString& args)
{
    int connectionId = player.GetConnectionId();
   
	//tcSimState* simState = tcSimState::Get();

    long val;
    if (!args.ToLong(&val) || (val < 0) || (val > 32))
    {
        wxString msg = wxString::Format("*** Error - bad game speed argument (%s)",
                      args.c_str());
        SendChatText(connectionId, msg.ToStdString());
        return;
    }

    //wxString msg = wxString::Format("*** Updated game speed request from %dX to %dX",
    //        player.GetGameSpeed(), val);

    player.SetGameSpeed(unsigned char(val));

    //SendChatText(connectionId, msg.c_str());
}


/**
* Adds new player account to database
* /gm addaccount '<username>' '<email>'
* @param args argument string
* @param msg message text to be returned
*/
void tcMultiplayerInterface::ProcessGMAddAccount(const wxString& args, wxString& msg)
{

    const char delim = '\'';
    wxString s1 = args.AfterFirst(delim);
	std::string username = s1.BeforeFirst(delim).c_str();
    s1 = s1.AfterFirst(delim);
    s1 = s1.AfterFirst(delim);
	std::string email = s1.BeforeFirst(delim).c_str();
 
	if (username.size() < 3)
	{
		msg.Printf("*** Username too short (%s)", username.c_str());
		return;
	}

	int status = tcAccountDatabase::Get()->AddUser(username, "", email);
	if (status == tcAccountDatabase::SUCCESS)
	{
		msg.Printf("*** Added account for %s", username.c_str());
	}
	else
	{
		msg.Printf("*** Error adding account %s (%d)", username.c_str(), status);
	}
}


/**
* Creates a new game entity
* /gm create '<class>' '<unitname>' <alliance>
* @param args argument string
* @param msg message text to be returned
*/
void tcMultiplayerInterface::ProcessGMCreate(const wxString& args, wxString& msg)
{
    const char delim = '\'';
    wxString params = args.AfterFirst(delim);
    wxString unitClass = params.BeforeFirst(delim);
    params = params.AfterFirst(delim);
    params = params.AfterFirst(delim);
    wxString unitName = params.BeforeFirst(delim);
    params = params.AfterFirst(delim);
    
	
	params = params.AfterFirst(' ');
	wxString s1 = params.BeforeFirst(' ');

    long alliance = 0;
    if ((!s1.ToLong(&alliance)) || (alliance < 0))
    {
        msg = wxString::Format("*** Bad alliance value for create, class '%s', unit '%s'",
           unitClass.c_str(), unitName.c_str());   
        return;
    }

    double lat_deg = 0;
    params = params.AfterFirst(' ');
    s1 = params.BeforeFirst(' ');
    if (!s1.ToDouble(&lat_deg))
    {
        msg = wxString::Format("*** Bad latitude for /gm create");
        return;  
    }
    
    double lon_deg = 0;
    params = params.AfterFirst(' ');
    s1 = params.BeforeFirst(' ');
    if (!s1.ToDouble(&lon_deg))
    {
        msg = wxString::Format("*** Bad longitude for /gm create");
        return;  
    }
    
    double alt_m = 0;
    params = params.AfterFirst(' ');
    s1 = params.BeforeFirst(' ');
    if (!s1.ToDouble(&alt_m))
    {
        alt_m = 0;
    }




    tcScenarioInterface* scenarioInterface = tcSimPythonInterface::Get()->GetScenarioInterface();
    wxASSERT(scenarioInterface);
    
    tcScenarioUnit unit;
    
    unit.className = unitClass.c_str();
    unit.unitName = unitName.c_str();
    unit.lat = lat_deg;
    unit.lon = lon_deg;
    unit.alt = alt_m;
    unit.heading = 0;
    unit.speed = 0;
    unit.throttle = 1.0;
    
    if (scenarioInterface->AddUnitToAlliance(unit, alliance))
    {
        tcGameObject* obj = scenarioInterface->GetLastObjectAdded();
        wxASSERT(obj);
        long id = obj->mnID;
        
        msg = wxString::Format("*** Created %d, class '%s', unit '%s' alliance %d",
            id, unitClass.c_str(), unitName.c_str(), alliance);    
    }
    else
    {
        msg = wxString::Format("*** Create FAILED, class '%s', unit '%s' alliance %d",
            unitClass.c_str(), unitName.c_str(), alliance);   
    }

}

/**
* Kick player from game
* /gm kick '<playername>'
* @param args argument string
* @param msg message text to be returned
*/
void tcMultiplayerInterface::ProcessGMKick(const wxString& args, wxString& msg)
{
    const char delim = '\'';
    wxString s1 = args.AfterFirst(delim);
	std::string playername = s1.BeforeFirst(delim).c_str();
    
    int playerId = GetPlayerConnectionId(playername);
    if (playerId == -1) return;

    SendChatText(playerId, "You have been kicked from the game");

    LogOutPlayer(playername);

    playerInfo.erase(playerId);
    networkInterface->RemoveConnection(playerId);
}


/**
* Moves a game entity
* move <id> <lat_deg> <lon_deg> (<alt>)
* use "move <id> 0 0 <alt>" to only change altitude
* @param args argument string
* @param msg message text to be returned
*/
void tcMultiplayerInterface::ProcessGMMove(const wxString& args, wxString& msg)
{
    wxString params = args.AfterFirst(' ');
    wxString s1 = params.BeforeFirst(' ');
    
    long id = -1;
    if (!s1.ToLong(&id))
    {
        msg = wxString::Format("*** Syntax error for /gm move");
        return;
    }
    
    double lat_deg = 0;
    params = params.AfterFirst(' ');
    s1 = params.BeforeFirst(' ');
    if (!s1.ToDouble(&lat_deg))
    {
        msg = wxString::Format("*** Syntax error for /gm move");
        return;  
    }
    
    double lon_deg = 0;
    params = params.AfterFirst(' ');
    s1 = params.BeforeFirst(' ');
    if (!s1.ToDouble(&lon_deg))
    {
        msg = wxString::Format("*** Syntax error for /gm move");
        return;  
    }
    
    bool changeLatLon = (lat_deg != 0) || (lon_deg != 0);
    
    double alt_m = 0;
    bool changeAlt = true;
    params = params.AfterFirst(' ');
    s1 = params.BeforeFirst(' ');
    if (!s1.ToDouble(&alt_m))
    {
        changeAlt = false;
    }
    
    tcSimState* simState = tcSimState::Get();
    
    if (tcGameObject* obj = simState->GetObject(id))
    {
        if (changeLatLon)
        {
            obj->mcKin.mfLat_rad = C_PIOVER180 * lat_deg;
            obj->mcKin.mfLon_rad = C_PIOVER180 * lon_deg;
        }
        if (changeAlt)
        {
            obj->mcKin.mfAlt_m = (float)alt_m;
        }
    
        msg = wxString::Format("*** Entity %d moved", id);
    }
    else
    {
        msg = wxString::Format("*** Entity %d not found", id);
    }    
    
}

/**
* Changes controlling player of a game entity
* setcontroller <id> '<player>'
* use setcontroller <id> '' to clear controller of entity
* @param args argument string
* @param msg message text to be returned
*/
void tcMultiplayerInterface::ProcessGMSetController(const wxString& args, wxString& msg)
{
    wxString params = args.AfterFirst(' ');
    wxString s1 = params.BeforeFirst(' ');
    
    long id = -1;
    if (!s1.ToLong(&id))
    {
        msg = wxString::Format("*** Syntax error for /gm setcontroller, bad id");
        return;
    }

    tcSimState* simState = tcSimState::Get();
    tcGameObject* obj = simState->GetObject(id);
    if (obj == 0)
    {
        msg = wxString::Format("*** entity not found (%d)", id);
        return;
    }
    

    params = params.AfterFirst('\'');
    std::string playername = params.BeforeFirst('\'').c_str(); // player name

    if (playername.size() > 0)
    {
        int playerId = GetPlayerConnectionId(playername);
        if (playerId == -1)
        {
            msg = wxString::Format("*** player not found (%s)",
                playername.c_str());
            return;
        }
        else
        {
            obj->SetController(playername);
            msg = wxString::Format("*** entity %d controller is now %s",
                id, playername.c_str());
            return;
        }

    }
    else
    {
        obj->SetController("");
        msg = wxString::Format("*** entity %d controller cleared", id);
        return;
    }


}

void tcMultiplayerInterface::ProcessGMSetTeamChanges(const wxString& args, wxString& msg)
{
    wxString s1 = args.BeforeFirst(' ');
    
    long id = -1;
    if (!s1.ToLong(&id))
    {
        msg = wxString::Format("*** Syntax error for /gm setteamchanges, parameter should be 0 or 1");
        return;
    }

    if (id != 0)
    {
        allowAllTeamChanges = true;
        msg = "*** Server now allowing all team changes";
    }
    else
    {
        allowAllTeamChanges = false;
        msg = "*** Server now restricting team changes";
    }
}


/**
* Process command from client (after command is received at server)
* text commands start with a forward slash '/'
* @return string to send back to client
*/
void tcMultiplayerInterface::ProcessCommandClient(int connectionId, 
                                               const std::string& text)
{        
    tcPlayerStatus& pstatus = GetPlayerStatus(connectionId);
    
    if (!pstatus.isAuthenticated)
    {
        SendChatText(connectionId, "*** command rejected, client not authenticated");
        return;
    }
    
    wxString candidate(text.c_str());

    wxString commandLine = candidate.AfterFirst('/');
    wxString command = commandLine.BeforeFirst(' ');
    wxString args = commandLine.AfterFirst(' ');

	// check for double slash command. These are silent with no echo back
	if (command.find('/') != 0)
	{
		SendChatText(connectionId, text);
	}
	else
	{		
		command.Remove(0, 1); // remove leading slash
	}

    // replace this with map lookup if it grows too large
    if (command == "help")
    {
        SendChatText(connectionId, "*** Help ***");
        SendChatText(connectionId, "    /alliance <int> - choose alliance");
		SendChatText(connectionId, "    /commander <name> - change or take team command");
        SendChatText(connectionId, "    /gamespeed <uint> - request game speed change");
        SendChatText(connectionId, "    /endgame - end game (commanders only)");
        SendChatText(connectionId, "    /surrender - surrender (commanders only)");

        if (pstatus.IsGM())
        {
            SendChatText(connectionId, "    /gm - game master commands");
        }
        SendChatText(connectionId, "    /help - print command list");
		SendChatText(connectionId, "    /scenario <name> - change scenario");
        SendChatText(connectionId, "    /who - list players");
    }
    else if (command == "alliance")
	{
        ProcessAllianceCommand(pstatus, args);
    }
    else if (command == "gm")
    {
        ProcessGameMasterCommand(pstatus, args);
    }
	else if (command == "scenario")
	{
		ProcessScenarioCommand(pstatus, args);
	}
    else if (command == "team")
    {
        ProcessTeamChat(pstatus, args);
    }
	else if (command == "commander")
	{
		ProcessChangeCommander(pstatus, args);
	}
	else if (command == "ready")
	{
		ProcessChangeReady(pstatus, args);
	}
	else if (command == "startgame")
	{
		ProcessStartGame(pstatus, args);
	}
	else if (command == "who")
	{
		ProcessWho(pstatus, args);
	}
    else if (command == "gamespeed")
    {
        ProcessGameSpeed(pstatus, args);
    }
    else if (command == "endgame")
    {
        ProcessEndGame(pstatus, args);
    }
    else if (command == "surrender")
    {
        ProcessSurrender(pstatus, args);
    }
    else
    {
        wxString msg = wxString::Format("*** Unrecognized command (%s)", command.c_str());
        SendChatText(connectionId, msg.ToStdString());
    } 
}

/**
* Process server command
* text commands start with a forward slash '/'
*/
void tcMultiplayerInterface::ProcessCommandServer(const std::string& text)
{
    wxASSERT(IsServer());
    wxString candidate(text.c_str());

    wxString commandLine = candidate.AfterFirst('/');
    wxString command = commandLine.BeforeFirst(' ');
    wxString args = commandLine.AfterFirst(' ');

    /* replace this with a std::map<std::string, handle> registry system
    ** when it outgrows this switch */
    
    if (command == "help")
    {
        chatText.push(std::string("*** Help ***"));
        chatText.push(std::string("    /gm <argument list> - GM commands"));
        chatText.push(std::string("    /help - print command list"));
    }
    else if (command == "gm")
    {
        ProcessGameMasterCommand(serverPlayerStatus, args);
    }
	else if (command == "scenario")
	{
		ProcessScenarioCommand(serverPlayerStatus, args);
	}
    else
    {
        chatText.push(std::string("*** unrecognized command ***"));
        tcSound::Get()->PlayEffect("intercom");
    }
    
}


void tcMultiplayerInterface::ProcessEndGame(tcPlayerStatus& player, const wxString& args)
{
	wxASSERT(IsServer());

    wxString msg;
    
    int connectionId = player.GetConnectionId();
    
    if (player.IsCommander() || player.IsGM())
    {
        player.SetGameEnd(true);
        msg = "*** End game requested";
    }
    else
    {
        msg = "*** Only team commander or GM can end game";
    } 
    
    SendChatText(connectionId, msg.ToStdString());
}

/**
* Process single receive message for connection associated with connectionId
*/
void tcMultiplayerInterface::ProcessMessage(int messageId, int connectionId,
                                unsigned messageSize, const unsigned char *data)
{

    std::map<int, std::vector<tcMessageHandler*> >::iterator mapIter;

    mapIter = messageMap.find(messageId);
    if (mapIter == messageMap.end()) 
    {
        fprintf(stderr, 
            "Warning - tcMultiplayerInterface::ProcessMessage unrecognized message ID (%d)\n", 
            messageId);
        return;
    }

    // call all registered message handlers for this message
    std::vector<tcMessageHandler*>& mm = mapIter->second;
    size_t nHandlers = mm.size();
    for (size_t n = 0; n < nHandlers; n++)
    {
        wxASSERT(mm[n]);
        mm[n]->Handle(connectionId, messageSize, data);
    }
}

/**
*
*/
void tcMultiplayerInterface::ProcessReceiveMessages()
{
    int messageId;
    unsigned messageSize;

	const std::list<int>& connectionList = networkInterface->GetConnectionList();
    std::list<int>::const_iterator iter = connectionList.begin();

    for( ; iter != connectionList.end(); ++iter)
    {
        int connId = *iter;
        const unsigned char *tcp_data = networkInterface->ReceiveMessage(connId, messageId, 
            messageSize, tcNetworkInterface::TCP);
        if (tcp_data != NULL)
        {
            ProcessMessage(messageId, connId, messageSize, tcp_data);
        }

        const unsigned char *udp_data = networkInterface->ReceiveMessage(connId, messageId, 
            messageSize, tcNetworkInterface::UDP);
        if (udp_data != NULL)
        {
            ProcessMessage(messageId, connId, messageSize, udp_data);
        }
    }
}


/**
* Process command to change scenario
*/
void tcMultiplayerInterface::ProcessScenarioCommand(tcPlayerStatus& player, const wxString& args)
{
	wxASSERT(IsServer());

    wxString msg;
    
    int connectionId = player.GetConnectionId();
    
    tcSimState* simState = tcSimState::Get();
    if (simState->IsScenarioLoaded() && (simState->GetTime() > 0))
    {
        msg = "*** Cannot change scenario after game started";
		SendChatText(connectionId, msg.ToStdString());
        return;
    }

	if (true) // allow any player for now, used to be: player.IsCommander())
    {
    	wxString scenario = args;
		if (scenario.Find('"') > -1) // isolate text between quotes
		{
			scenario = scenario.AfterFirst('"');
			scenario = scenario.BeforeFirst('"');
		}

		bool success = scenarioSelectView->LoadScenarioByName(scenario.ToStdString(), false);
		if (success)
		{
			msg.Printf("*** Change scenario success: %s", scenario.c_str());
			SendChatText(connectionId, msg.ToStdString());

			msg.Printf("*** %s changed scenario to %s", player.GetNameWithRank().c_str(), scenario.c_str());
			BroadcastChatText(msg.ToStdString());

		}
		else
		{
			msg.Printf("*** Change scenario failed, did not find scenario: %s", scenario.c_str());
			SendChatText(connectionId, msg.ToStdString());
		}
    }
    else
    {
        msg = "*** Only team commander can change scenario";
		SendChatText(connectionId, msg.ToStdString());
    } 
    
    
}



/**
* Process command to start game
*/
void tcMultiplayerInterface::ProcessStartGame(tcPlayerStatus& player, const wxString& args)
{
	wxASSERT(IsServer());

    wxString msg;
    
    int connectionId = player.GetConnectionId();
    
	if (player.IsCommander())
    {
		bool allReady = mpGameView->IsEveryoneReady();

		if (allReady)
		{
			// post start game event
			wxEvtHandler* evtHandler = this->GetEvtHandler();
			wxCommandEvent command(wxEVT_COMMAND_BUTTON_CLICKED, ID_STARTGAME);    
			evtHandler->AddPendingEvent(command);

			msg.Printf("*** %s started game", player.GetNameWithRank().c_str());
			BroadcastChatText(msg.ToStdString());

            wxString eventString = wxString::Format("Game start (%s)", wxDateTime::Now().FormatISOTime().c_str());
            recentEvents.push_back(eventString);
        }
		else
		{
			msg.Printf("*** Start game failed. All players are not ready.");
			SendChatText(connectionId, msg.ToStdString());
		}
    }
    else
    {
        msg = "*** Only team commander can start game";
		SendChatText(connectionId, msg.ToStdString());
    } 
    
    
}

void tcMultiplayerInterface::ProcessSurrender(tcPlayerStatus& player, const wxString& args)
{
	wxASSERT(IsServer());

    wxString msg;
    
    int connectionId = player.GetConnectionId();
    
	if (player.IsCommander())
    {
        player.SetSurrender(true);
        msg = "*** Surrender requested";
    }
    else
    {
        msg = "*** Only team commander can surrender game";
    } 
    
    SendChatText(connectionId, msg.ToStdString());
}


/**
* Send chat text to all players with matching alliance
*/
void tcMultiplayerInterface::ProcessTeamChat(const tcPlayerStatus& player, const wxString& msg)
{
    // create string with name prepended to text to identify source
    std::string namedText = std::string("[TEAM] <") + player.GetNameWithRank() + std::string("> ") + 
        std::string(msg.c_str());

    BroadcastChatText(namedText, player.GetAlliance());
}


/**
* Send list of players currently in game back to client
*/
void tcMultiplayerInterface::ProcessWho(tcPlayerStatus& player, const wxString& args)
{
	const std::list<int>& connectionList = networkInterface->GetConnectionList();
    std::list<int>::const_iterator iter = connectionList.begin();

    SendChatText(player.connectionId, "");
	SendChatText(player.connectionId, "Players currently in game:");
    for( ; iter != connectionList.end(); ++iter)
    {
		tcPlayerStatus& playerInfo = GetPlayerStatus(*iter);
		const std::string& connectionStatus = networkInterface->GetConnectionStatus(*iter, 0);

		wxString s = wxString::Format("%s [%d] %s", playerInfo.GetNameWithRank().c_str(),
			playerInfo.GetAlliance(), connectionStatus.c_str());

		SendChatText(player.connectionId, s.ToStdString());
    }
}


void tcMultiplayerInterface::SendAuthRequest(int destination)
{
	unsigned char buff[16];
	unsigned messageSize;

	tcAuthenticationMessageHandler::CreateAuthenticationRequest(messageSize, buff);

	networkInterface->SendMessage(destination, MSG_AUTHENTICATION, 
		messageSize, buff, tcNetworkInterface::TCP);
}

void tcMultiplayerInterface::SendAuthResponse(int destination)
{
	unsigned char buff[256];
	unsigned messageSize;

	tcAuthenticationMessageHandler::CreateAuthenticationResponse(myName, passwordHash, 
		messageSize, buff);

	networkInterface->SendMessage(destination, MSG_AUTHENTICATION, 
		messageSize, buff, tcNetworkInterface::TCP);

}

/**
* Sends simple briefing text to client for indicated alliance
* This is the only way of getting briefing info in multiplayer
*/
void tcMultiplayerInterface::SendBriefingText(int destination, int alliance)
{
	tcUpdateStream stream;
	tcUpdateMessageHandler::InitializeMessage(tcUpdateMessageHandler::BRIEFING_TEXT, stream);
	tcUpdateMessageHandler::AddBriefingText(alliance, stream);

	SendUpdateMessageTCP(destination, stream);
}

/**
* Sends a test message of text to destination
*/
void tcMultiplayerInterface::SendChatText(int destination, const std::string& message)
{
    // first check for local message
    if (destination == 0)
    {
        chatText.push(message);
        return;
    }
    
    char buff[256];
    unsigned messageLength;

    int protocol = tcpChat ? tcNetworkInterface::TCP : tcNetworkInterface::UDP;

    tcTextMessageHandler::CreateMessage(messageLength, (unsigned char*)buff, message, 255);
   
    networkInterface->SendMessage(destination, MSG_CHATTEXT, 
        messageLength, (unsigned char*)buff, protocol);
}

/** 
* Send control message to destination using TCP
*/
void tcMultiplayerInterface::SendControlMessage(int destination, int messageCode, int param)
{
    unsigned char data[64];
    unsigned messageSize;

    tcControlMessageHandler::CreateControlMessage(messageCode, messageSize, data, param);
    networkInterface->SendMessage(destination, MSG_CONTROL, 
        messageSize , data, 
        tcNetworkInterface::TCP);
}

/** 
* Send control message to destination using UDP
*/
void tcMultiplayerInterface::SendControlMessageUDP(int destination, int messageCode, int param)
{
    unsigned char data[64];
    unsigned messageSize;

    tcControlMessageHandler::CreateControlMessage(messageCode, messageSize, data, param);
    networkInterface->SendMessage(destination, MSG_CONTROL, 
        messageSize , data, 
        tcNetworkInterface::UDP);
}

/**
* Merge these send methods into common
*/
void tcMultiplayerInterface::SendControlMessageUDPAck(int destination, int messageCode, int param)
{
    unsigned char data[64];
    unsigned messageSize;

    tcControlMessageHandler::CreateControlMessage(messageCode, messageSize, data, param);
    networkInterface->SendMessage(destination, MSG_CONTROL, 
        messageSize , data, 
        tcNetworkInterface::UDP_ACK);
}

/**
* Sends control request message to server requesting control of object id by player
*/
void tcMultiplayerInterface::SendControlRelease(long id)
{
    static std::vector<long> id_list;

    id_list.clear();
    id_list.push_back(id);

    SendControlRelease(id_list);
}


/**
* Sends control request message to server requesting release of control of object id by player
*/
void tcMultiplayerInterface::SendControlRelease(const std::vector<long>& id)
{
	if (IsServer())
	{
		fprintf(stderr, "tcMultiplayerInterface::SendControlRelease - called by server\n");
		wxASSERT(false);
		return;
	}

    if (id.size() == 0)
    {
        wxASSERT(false);
        return;
    }

	// server should be only connection
	const std::list<int>& connectionList = networkInterface->GetConnectionList();
	if (connectionList.size() == 0)
	{
		fprintf(stderr, "tcMultiplayerInterface::SendControlRelease - no connections\n");
		wxASSERT(false);
		return;
	}

    std::list<int>::const_iterator iter = connectionList.begin();
	int destination = *iter; 

	tcStream stream;
	tcUpdateMessageHandler::InitializeMessage(tcUpdateMessageHandler::CONTROL_REQUEST, stream);

    for (size_t k=0; k<id.size(); k++)
    {
	    tcUpdateMessageHandler::AddControlRelease(id[k], stream);
    }

	SendUpdateMessageAck(destination, stream);
}


/**
* Sends control request message to server requesting control of object id by player
*/
void tcMultiplayerInterface::SendControlRequest(long id)
{
    static std::vector<long> id_list;

    id_list.clear();
    id_list.push_back(id);

    SendControlRequest(id_list);
}


/**
* Sends control request message to server requesting control of object id by player
*/
void tcMultiplayerInterface::SendControlRequest(const std::vector<long>& id)
{
	if (IsServer())
	{
		fprintf(stderr, "tcMultiplayerInterface::SendControlRequest - called by server\n");
		wxASSERT(false);
		return;
	}

    if (id.size() == 0)
    {
        wxASSERT(false);
        return;
    }

	// server should be only connection
	const std::list<int>& connectionList = networkInterface->GetConnectionList();
	if (connectionList.size() == 0)
	{
		fprintf(stderr, "tcMultiplayerInterface::SendControlRequest - no connections\n");
		wxASSERT(false);
		return;
	}

    std::list<int>::const_iterator iter = connectionList.begin();
	int destination = *iter; 

	tcStream stream;
	tcUpdateMessageHandler::InitializeMessage(tcUpdateMessageHandler::CONTROL_REQUEST, stream);

    for (size_t k=0; k<id.size(); k++)
    {
	    tcUpdateMessageHandler::AddControlRequest(id[k], stream);
    }

	SendUpdateMessageAck(destination, stream);
}

void tcMultiplayerInterface::SendScenarioInfo(const std::vector<int>& destinations)
{
	tcUpdateStream stream;
	tcUpdateMessageHandler::InitializeMessage(tcUpdateMessageHandler::SCENARIO_INFO, stream);
	tcUpdateMessageHandler::AddScenarioInfo(stream);

	for (unsigned n=0; n<destinations.size(); n++)
	{
		int connectionId = destinations[n];

		tcPlayerStatus& player = GetPlayerStatus(connectionId);

		tcUpdateStream destStream(stream);
		SendUpdateMessageTCP(destinations[n], destStream);


		SendBriefingText(destinations[n], player.alliance);
	}
	
}


/**
* Version to send to one destination. Does not send briefing text
*/
void tcMultiplayerInterface::SendScenarioInfo(int destination)
{
	tcUpdateStream stream;
	tcUpdateMessageHandler::InitializeMessage(tcUpdateMessageHandler::SCENARIO_INFO, stream);
	tcUpdateMessageHandler::AddScenarioInfo(stream);


//	tcPlayerStatus& player = GetPlayerStatus(destination);

	SendUpdateMessageTCP(destination, stream);
}

void tcMultiplayerInterface::SendDatabaseInfo(const std::vector<int>& destinations)
{
	for (unsigned n=0; n<destinations.size(); n++)
	{
		int connectionId = destinations[n];
        SendDatabaseInfo(connectionId);
    }
}


/**
* Sends database classname, id pairs to synchronize client database with server database
* Version to send to one destination.
*/
void tcMultiplayerInterface::SendDatabaseInfo(int destination)
{
    wxASSERT(IsServer());

    tcDatabaseIterator iter(0); // 0 is pass all

	tcUpdateStream stream;
	tcUpdateMessageHandler::InitializeMessage(tcUpdateMessageHandler::DATABASE_INFO, stream);
    size_t nInfo = 0;

    stream << long(-1); // -1 is signal to clear database on receipt of this message

    for (iter.First(); !iter.IsDone(); iter.Next())
    {
        tcDatabaseObject* obj = iter.Get();

        wxASSERT(obj != 0);
        wxASSERT(obj->mnKey != -1);

        stream << obj->mnKey;
        stream << std::string(obj->mzClass.c_str());
        nInfo++;

        if (stream.size() > (stream.GetMaxSize() - 256))
        {
            SendUpdateMessageTCP(destination, stream);
            stream.clear();
            tcUpdateMessageHandler::InitializeMessage(tcUpdateMessageHandler::DATABASE_INFO, stream);
            nInfo = 0;
        }
    }

    if (nInfo > 0)
    {
        SendUpdateMessageTCP(destination, stream);
    }

}


void tcMultiplayerInterface::SendSoundEffect(const std::string& player, const std::string& effect, long id)
{
	int connectionId = GetPlayerConnectionId(player);

	if (connectionId != -1)
	{
		SendSoundEffect(connectionId, effect, id);
	}
}

void tcMultiplayerInterface::SendSoundEffect(int destination, const std::string& effect, long id)
{
	tcStream stream;
	tcUpdateMessageHandler::InitializeMessage(tcUpdateMessageHandler::SOUND_EFFECT, stream);

	tcUpdateMessageHandler::AddSoundEffect(id, effect, stream);

	SendUpdateMessage(destination, stream);

}

void tcMultiplayerInterface::SendTestUDP(int destination, const std::string& message)
{
	size_t messageLength = message.length();
	if (messageLength > 255) messageLength = 255;
	networkInterface->SendMessage(
		destination, MSG_CHATTEXT, 
		(unsigned)(messageLength+1), (unsigned char*)message.c_str(),
		tcNetworkInterface::UDP);
}

void tcMultiplayerInterface::SendUpdateMessage(int destination, tcStream& stream)
{
    size_t streamSize = stream.size();
    char* buffer = new char[streamSize];
    stream.read(buffer, streamSize);

    networkInterface->SendMessage(destination, MSG_UPDATE, streamSize, (unsigned char*)buffer,
        tcNetworkInterface::UDP);

    delete[] buffer;
}

void tcMultiplayerInterface::SendUpdateMessageAck(int destination, tcStream& stream)
{
    size_t streamSize = stream.size();
    char* buffer = new char[streamSize];
    stream.read(buffer, streamSize);

    networkInterface->SendMessage(destination, MSG_UPDATE, streamSize, (unsigned char*)buffer,
        tcNetworkInterface::UDP_ACK);

    delete[] buffer; 
}

void tcMultiplayerInterface::SendUpdateMessageTCP(int destination, tcStream& stream)
{
    size_t streamSize = stream.size();
    char* buffer = new char[streamSize];
    stream.read(buffer, streamSize);

    networkInterface->SendMessage(destination, MSG_UPDATE, streamSize, (unsigned char*)buffer,
		tcNetworkInterface::TCP);

    delete[] buffer; 
}

void tcMultiplayerInterface::SetAcceptAllClients(bool state)
{
	acceptAllClients = state;
}


void tcMultiplayerInterface::SetAllEndGameState(bool state)
{
    if (!IsServer())
    {
        wxASSERT(false);
        return;
    }

    std::map<int, tcPlayerStatus>::iterator iter = playerInfo.begin();

    for( ; iter != playerInfo.end(); ++iter)
    {
        tcPlayerStatus& player = iter->second;

        player.SetGameEnd(state);
    }
}

/**
* Set or clear ready state for all players
*/
void tcMultiplayerInterface::SetAllReadyState(bool state)
{
    if (!IsServer())
    {
        wxASSERT(false);
        return;
    }

    const std::list<int>& connectionList = networkInterface->GetConnectionList();
    std::list<int>::const_iterator iter = connectionList.begin();

    for( ; iter != connectionList.end(); ++iter)
    {
        int destination = *iter;    
		
        tcPlayerStatus& player = GetPlayerStatus(destination);
        player.SetReady(state);
	}
}


/**
* 0 - UDP, otherwise - TCP
*/
void tcMultiplayerInterface::SetChatProtocol(int code)
{
	if (code)
	{
		tcpChat = true;
	}
	else
	{
		tcpChat = false; // use UDP
	}
}

/**
* Sets wxWidgets event handler for posting messages to application.
*/
void tcMultiplayerInterface::SetEvtHandler(wxEvtHandler *eh)
{
    evtHandler = eh;
}

/**
* Sets identification name string for player using this interface
*/
void tcMultiplayerInterface::SetName(const std::string& name)
{
	if (IsServer()) return; // don't allow server to change name

    myName = name;

	// limit size of name
	if (myName.size() >= 24)
	{
		myName = myName.substr(0, 23);
	}
}

void tcMultiplayerInterface::SetPassword(const std::string& plainText)
{
	passwordHash = tcAccountDatabase::Get()->GetMD5digest(plainText);
}

/**
* Sets ping time associated with connection
*/
void tcMultiplayerInterface::SetPingTime(int connectionId, float ping_s)
{
    networkInterface->SetPingTime(connectionId, ping_s);
}

void tcMultiplayerInterface::SetVersionString(const char* s)
{
    versionString = s;
}

/**
* This must be called regularly to perform network functions.
* (avoids need for multithreadeding)
* Need to clean this up to better isolate server vs. client processing
*/
void tcMultiplayerInterface::Update()
{
	bool gameStarted = true; //(simState->GetTime() > 0);

	unsigned startCount = tcTime::Get()->GetUpdated30HzCount();

    networkInterface->Update();

	unsigned endCount = tcTime::Get()->GetUpdated30HzCount();

	unsigned elapsed = endCount - startCount;
	if ((elapsed > updateCount) || ((endCount >> 3) % 5 == 0))
	{
		updateCount = elapsed;
	}

    // process receive messages
    ProcessReceiveMessages();

    // distribute chat text
    DistributeChatText();

    // update player information
    UpdatePlayerInfo();

    // periodically update parameters for tcOptions changes by user
    UpdateOptions();

    // state update for entities (game objects)
    if (gameStarted) UpdateEntities();

    if (IsServer())
    {
        if (gameStarted) 
        {
            UpdateSensorMaps();
            UpdateMissions();
        }

		UpdateGoalStatus();

		UpdateTeamStatus();

        UpdateServerStatus();
    }

    /* update time when paused only. This is redundant
    ** with obj state update which also has time info, but is 
    ** included as a heartbeat message.
    **
    ** Modified to always update to accomodate game speed requests
    **/
    if (IsServer())
    {
        UpdateTime();
    }
    
    UpdatePing();

}


/**
* Server only -- send updates for destroyed objects to client
* @param connIdx connection index of client to update
*/
void tcMultiplayerInterface::UpdateDestroyedEntities(tcPlayerStatus& pstatus)
{
    int connId = pstatus.connectionId;

    tcSimState* simState = tcSimState::Get();
    wxASSERT(simState);

    /* iterate through all pstatus objects and add to destroy stream if
    ** the object no longer exists
    */
    tcStream stream;
    tcUpdateMessageHandler::InitializeMessage(tcUpdateMessageHandler::DESTROY, stream);

    unsigned destroyCount = 0;
    for (std::map<long, tcPlayerStatus::UpdateInfo>::iterator iter = pstatus.lastUpdate.begin();
        iter != pstatus.lastUpdate.end(); ) 
    {
        long id = iter->first;
        if (simState->GetObject(id))
        {
            ++iter;
        }
        else
        {
            tcUpdateMessageHandler::AddDestroy(id, stream);
            pstatus.lastUpdate.erase(iter++);
            destroyCount++;
        }
    }

    if (destroyCount)
    {
        SendUpdateMessage(connId, stream);
#ifdef _DEBUG
        double t = simState->GetTime();
        fprintf(stdout, "Sent obj destroy msg, time: %.1f\n", t);
#endif
    }
    
}

void tcMultiplayerInterface::UpdateEntityCommands(tcPlayerStatus& pstatus, bool clearNewCmdFlag)
{
    int connId = pstatus.connectionId;

    tcSimState* simState = tcSimState::Get();
    wxASSERT(simState);

#ifdef _DEBUG
    double t = simState->GetTime();
#endif

    // iterate through all game objects and build command update stream
    tcCommandStream commandStream;
    tcUpdateMessageHandler::InitializeMessage(tcUpdateMessageHandler::COMMAND_UPDATE, commandStream);

    tcGameObjIterator iter;
    unsigned updateCount = 0;
    for (iter.First();iter.NotDone();iter.Next())
	{
		tcGameObject* obj = iter.Get();
		if (obj->HasNewCommand())
		{
			if ((pstatus.alliance == obj->GetAlliance()) || !IsServer())
			{
				tcUpdateMessageHandler::AddCommandUpdate(obj, commandStream);
				
				updateCount++;
#ifdef _DEBUG
				fprintf(stdout, "%d ", obj->mnID);
#endif
			}

			// extremely important! not clearing command will flood network
			if (clearNewCmdFlag) obj->ClearNewCommand();
		}

        // create new message if updateCount gets too large
        if (updateCount >= 4)
        {
            SendUpdateMessage(connId, commandStream);
#ifdef _DEBUG
            fprintf(stdout, "Sent obj command update, time: %.1f\n", t);
#endif
            commandStream.clear();
            tcUpdateMessageHandler::InitializeMessage(tcUpdateMessageHandler::COMMAND_UPDATE, commandStream);
            updateCount = 0;
        }
    }

    if (updateCount)
    {
        SendUpdateMessage(connId, commandStream);
#ifdef _DEBUG
        fprintf(stdout, "Sent obj command update, time: %.1f\n", t);
#endif
    }
}

void tcMultiplayerInterface::UpdateEntitiesXml(tcPlayerStatus& pstatus)
{
    if (!pstatus.IsXmlObserver())
    {
        wxASSERT(false);
        return;
    }
}


/**
* Periodically sends goal status (win/loss) to all clients
*/
void tcMultiplayerInterface::UpdateGoalStatus()
{
	static unsigned int lastUpdate = 0;

	wxASSERT(IsServer());

	unsigned t = tcTime::Get()->Get30HzCount();
	if (t - lastUpdate < goalUpdateInterval) return;
	lastUpdate = t;

	const std::list<int>& connectionList = networkInterface->GetConnectionList();

	std::list<int>::const_iterator iter = connectionList.begin();
//	unsigned n = 0;
	for( ; iter != connectionList.end(); ++iter)
	{
		int connectionId = *iter;

		tcPlayerStatus& player = GetPlayerStatus(connectionId);

		if ((player.isAuthenticated) && (player.GetAlliance() != 0))
		{
			tcUpdateStream updateStream;

			tcUpdateMessageHandler::InitializeMessage(tcUpdateMessageHandler::GOAL_STATUS, updateStream);
			tcUpdateMessageHandler::AddGoalStatus(player.GetAlliance(), updateStream);

			SendUpdateMessageAck(connectionId, updateStream);

			fprintf(stdout, "Performed goal status update, conn %d, t: %d\n", 
				connectionId, t);
		}
	}

}


/**
* Send script command messages to server
*/
void tcMultiplayerInterface::UpdateScriptCommands(int connectionId)
{
	wxASSERT(!IsServer());

	tcSimPythonInterface* pythonInterface = tcSimPythonInterface::Get();

	if (!pythonInterface->HasNewCommand()) return;

	tcCommandStream commandStream;
	tcUpdateMessageHandler::InitializeMessage(tcUpdateMessageHandler::SCRIPT_COMMANDS, commandStream);

	pythonInterface->operator>>(commandStream);

	pythonInterface->ClearNewCommand();

	SendUpdateMessage(connectionId, commandStream);
#ifdef _DEBUG
	fprintf(stdout, "Sent script commands\n");
#endif

}

void tcMultiplayerInterface::GetUpdatePeriod(const tcGameObject* obj, const std::string& playerName,
                                                     unsigned int& updatePeriod, unsigned int& detailedUpdatePeriod) const
{
    bool playerControlled = obj->IsControlledBy(playerName);

    detailedUpdatePeriod = playerControlled ? 300 : 900;

    const tcFlightOpsObject* flightOps = dynamic_cast<const tcFlightOpsObject*>(obj);
    bool largeFlightOps = (flightOps == 0) ? false : (flightOps->CurrentAirComplementSize() > 8);
    
    if (!playerControlled)
    {
        if (!largeFlightOps)
        {
            updatePeriod = 90;
        }
        else
        {
            updatePeriod = 90;
        }
    }
    else
    {
        if (!largeFlightOps)
        {
            updatePeriod = 25;
        }
        else
        {
            updatePeriod = 60;
        }
    }
}

/**
* Server only -- send create updates for new entities to client
*/
void tcMultiplayerInterface::UpdateNewAndExistingEntities(tcPlayerStatus& pstatus)
{
    int connId = pstatus.connectionId;

    unsigned int t = tcTime::Get()->Get30HzCount();
    
	const std::string& playerName = pstatus.GetName();

    // create stream for new entities
    tcCreateStream createStream;
    tcUpdateMessageHandler::InitializeMessage(tcUpdateMessageHandler::CREATE, createStream);

    // update stream for existing entities
    tcUpdateStream updateStream;
    tcUpdateMessageHandler::InitializeMessage(tcUpdateMessageHandler::UPDATE, updateStream);


    tcGameObjIterator iter;
    unsigned createCount = 0;
    unsigned updateCount = 0;
	//const unsigned int maxMessageSize = tcMessage::GetMaxMessageSize();
        
    bool isObserver = pstatus.alliance == 0;

    for (iter.First(); iter.NotDone(); iter.Next())
    {
        tcGameObject* obj = iter.Get();
        if (isObserver || (pstatus.alliance == obj->GetAlliance()))
        {
            unsigned int lastUpdate, lastDetailedUpdate;
            if (pstatus.GetLastUpdate(obj->mnID, lastUpdate, lastDetailedUpdate))
            {
				unsigned int dt = t - lastUpdate;
                unsigned int updatePeriod, detailedUpdatePeriod;
                GetUpdatePeriod(obj, playerName, updatePeriod, detailedUpdatePeriod);

                bool doUpdate = (dt >= updatePeriod);

				if (doUpdate)
				{
                    unsigned int dt_detailed = t - lastDetailedUpdate;
                    bool detailUpdate = (dt_detailed >= detailedUpdatePeriod);
                    if (!detailUpdate)
                    {
                        updateStream.SetDetailLevel(0);
                    }
                    else
                    {
                        updateStream.SetDetailLevel(1);
                    }

                    bool updateAdded = tcUpdateMessageHandler::AddUpdate(obj, updateStream);
                    
                    if (updateAdded)
                    {
                        updateCount++;
                    }
                    else
                    {
                        bool updating = true;
                        unsigned messageCount = 0;
                        while (updating && (messageCount < 8))
                        {
                            SendUpdateMessage(connId, updateStream);
#ifdef _DEBUG
                            fprintf(stdout, "Sent obj state update, time: %d\n", t);
#endif
                            updateStream.clear();
                            tcUpdateMessageHandler::InitializeMessage(tcUpdateMessageHandler::UPDATE, 
                                updateStream);

                            updating = !tcUpdateMessageHandler::AddUpdate(obj, updateStream);
                            messageCount++;
                        }

                        if (messageCount >= 8)
                        {
                            fprintf(stderr, "tcMultiplayerInterface::UpdateNewAndExistingEntities - "
                                "exceeded partial update msg limit (%s)\n", obj->mzUnit.c_str());
                        }
                        else
                        {
#ifdef _DEBUG
                        fprintf(stdout, "   partial update msg count: %d\n", messageCount);
#endif
                        }
                        updateCount = 1;
                    }

					pstatus.SetUpdate(obj->mnID, t);
                    if (detailUpdate) pstatus.SetDetailedUpdate(obj->mnID, t);
				}

                
                // create new message if updateCount gets too large
				if (updateCount >= 6)
                {
                    SendUpdateMessage(connId, updateStream);
        #ifdef _DEBUG
                    fprintf(stdout, "Sent obj state update, time: %d\n", t);
        #endif
                    updateStream.clear();
                    tcUpdateMessageHandler::InitializeMessage(tcUpdateMessageHandler::UPDATE, 
                        updateStream);
                    updateCount = 0;
                }
            }
            else
            {
                bool createAdded = tcUpdateMessageHandler::AddCreate(obj, createStream);
                
                if (createAdded)
                {
                    createCount++;
                }
                else
                {
                    bool updating = true;
                    unsigned messageCount = 0;
                    while (updating && (messageCount < 8))
                    {
                        SendUpdateMessage(connId, createStream);
#ifdef _DEBUG
                        fprintf(stdout, "Sent obj create msg, time: %d\n", t);
#endif
                        createStream.clear();
                        tcUpdateMessageHandler::InitializeMessage(tcUpdateMessageHandler::CREATE, 
                            createStream);

                        updating = !tcUpdateMessageHandler::AddCreate(obj, createStream);
                        messageCount++;
                    }

                    if (messageCount >= 8)
                    {
                        fprintf(stderr, "tcMultiplayerInterface::UpdateNewAndExistingEntities - "
                            "exceeded partial create msg limit (%s)\n", obj->mzUnit.c_str());
                    }
                    else
                    {
#ifdef _DEBUG
                        fprintf(stdout, "   partial create msg count: %d\n", messageCount);
#endif
                    }

                    createCount = 1;
                }

                // set time to force update at next opportunity
                pstatus.SetUpdate(obj->mnID, (unsigned int)(t-200));
                pstatus.SetDetailedUpdate(obj->mnID, (unsigned int)(t-200));
#ifdef _DEBUG
                fprintf(stdout, "C%d ", obj->mnID);
#endif

				if (createCount >= 8)
                {
                    SendUpdateMessage(connId, createStream);
        #ifdef _DEBUG
                    fprintf(stdout, "Sent obj create msg, time: %d\n", t);
        #endif
                    createStream.clear();
                    tcUpdateMessageHandler::InitializeMessage(tcUpdateMessageHandler::CREATE, 
                        createStream);
                    createCount = 0;
                }

            }
            
            
        }
    }

    if (createCount)
    {
        SendUpdateMessage(connId, createStream);
#ifdef _DEBUG
        fprintf(stdout, " -- object create msg sent\n");
#endif
    }
    
    if (updateCount)
    {
        SendUpdateMessage(connId, updateStream);
#ifdef _DEBUG
        fprintf(stdout, "Sent obj state update, time: %d\n", t);
#endif
    }   
    
}


/**
* Update air missions for flightops
*/
void tcMultiplayerInterface::UpdateMissions()
{   
    static unsigned lastUpdate = 0;

    unsigned currentTime = tcTime::Get()->Get30HzCount();
    if (currentTime - lastUpdate < missionUpdateInterval) return;
    lastUpdate = currentTime;


    // build list of authenticated players
    std::vector<int> validPlayers;
    const std::list<int>& connectionList = networkInterface->GetConnectionList();

    std::list<int>::const_iterator iter = connectionList.begin();
    for( ; iter != connectionList.end(); ++iter)
    {
        int id = *iter;
        
        tcPlayerStatus& player = GetPlayerStatus(id);
        if (player.isAuthenticated && !player.IsXmlObserver())
        {
            validPlayers.push_back(id);
        }
    }

    // for each player, add flight ops missions to update message
    // send to player if there is at least one update
    for (size_t k=0; k<validPlayers.size(); k++)
    {
        int id = validPlayers[k];
        tcPlayerStatus& player = GetPlayerStatus(id);

        tcUpdateStream updateStream;
        tcUpdateMessageHandler::InitializeMessage(tcUpdateMessageHandler::AUTO_MISSIONS, updateStream);
        unsigned nUpdates = 0;

        tcGameObjIterator iter;

        for (iter.First(); iter.NotDone(); iter.Next())
        {
            tcGameObject* obj = iter.Get();
            tcFlightOpsObject* flightOps = dynamic_cast<tcFlightOpsObject*>(obj);
            if ((flightOps != 0) && (obj->IsControlledBy(player.GetName())))
            {
                ai::tcMissionManager* missionManager = flightOps->GetFlightPort()->GetMissionManager();
                if ((missionManager != 0) && (missionManager->GetMissionCount() > 0))
                {
                    tcUpdateMessageHandler::AddAirMissionUpdate(flightOps, updateStream);
                    nUpdates++;
                }
            }
        }
        
        SendUpdateMessage(id, updateStream); // always send so that deletes get performed correctly at client

    }



}


/**
* Send state updates on objects to clients (command info in both directions)
*/
void tcMultiplayerInterface::UpdateEntities()
{
    unsigned int t = tcTime::Get()->Get30HzCount();

    std::map<int, tcPlayerStatus>::iterator iter = playerInfo.begin();

    unsigned nPlayers = playerInfo.size();

    unsigned n = 0;
    for( ; iter != playerInfo.end(); ++iter)
    {
        int id = iter->first;
        tcPlayerStatus& player = iter->second;

		// always do script command update at client
		if (!IsServer())
		{
			UpdateScriptCommands(id);
		}

        /* always do new cmd update, clear flag on last only.
		** New commands need to be send to all clients at once with
		** this system */
        bool clearNewCmdFlag = (n++ == (nPlayers - 1));
        UpdateEntityCommands(player, clearNewCmdFlag); 
        
        unsigned int dt = t - player.entityUpdateTime;
		
        if ((dt > entityUpdateInterval) && (player.isAuthenticated) && IsServer())
		{
			player.entityUpdateTime = t;

            if (!player.IsXmlObserver())
            {

                if (player.isInGame)
                {
                    UpdateDestroyedEntities(player);
                    UpdateNewAndExistingEntities(player);
                }
                else
                {
                    SendControlMessage(player.connectionId, network::tcControlMessageHandler::CM_TIME);
                }

                //fprintf(stdout, "Performed entity state update, conn %d, t: %d\n", 
                //	id, t);
            }
            else
            {
                UpdateEntitiesXml(player);
            }
		}


    }


}


/**
* Periodically update multiplayer parameters based on tcOptions state, allows
* options to be changed "on the fly"
*/
void tcMultiplayerInterface::UpdateOptions()
{
    unsigned int t = tcTime::Get()->Get30HzCount();
    const unsigned int updateInterval = 60; // 30 Hz tics to update options
    if ((t - lastOptionsUpdate) < updateInterval) return;

    lastOptionsUpdate = t;
    if (!IsServer()) return; // only applies to server for now

    tcOptions* options = tcOptions::Get();

    sendDetailedTrackInfo = (options->sendTrackDetails != 0);
    tcSensorMapTrack::sendDetailedTrackInfo = sendDetailedTrackInfo;

    switch (options->sensorUpdateRate)
    {
        case 0:  sensorUpdateInterval = 90; break;
        case 1:  sensorUpdateInterval = 60; break;
        case 2:  sensorUpdateInterval = 30; break;
        case 3:  sensorUpdateInterval = 15; break;
        default: sensorUpdateInterval = 30; break;
    }
}



/**
*
*/
void tcMultiplayerInterface::UpdatePing()
{
    static unsigned lastUpdate = 0;
    unsigned currentTime = tcTime::Get()->Get30HzCount();
    if (currentTime - lastUpdate < 30) return;
    
    lastUpdate = currentTime;

    const std::list<int>& connectionList = networkInterface->GetConnectionList();
    std::list<int>::const_iterator iter = connectionList.begin();

    for( ; iter != connectionList.end(); ++iter)
    {
        int id = *iter;

        SendControlMessageUDPAck(id, tcControlMessageHandler::CM_PING, 0);
    }
}

/**
*
*/
void tcMultiplayerInterface::UpdatePlayerInfo()
{
    static unsigned lastUpdate = 0;
    unsigned currentTime = tcTime::Get()->Get30HzCount();
    if (currentTime - lastUpdate < 5) return;
    
    lastUpdate = currentTime;

    // add new connections
    const std::list<int>& connectionList = networkInterface->GetConnectionList();
    std::list<int>::const_iterator iter = connectionList.begin();

    for( ; iter != connectionList.end(); ++iter)
    {
        int connId = *iter;

        if (IsNewPlayer(connId))
        {
            tcPlayerStatus stat;
            stat.ping_s = 0;
			stat.startTime = tcTime::Get()->Get30HzCount();
            stat.timestamp = stat.startTime;
			stat.entityUpdateTime = 0;
			stat.sensorUpdateTime = 0;
            stat.name = "Anonymous";
            stat.isXmlObserver = false;
            stat.isCommander = false;
			stat.isReady = false;
			stat.isAuthenticated = false;
            stat.connectionId = connId;

			if (IsServer())
			{
				SendAuthRequest(connId);
			}
			else
			{
				stat.name = "SERVER";
			}           
			
			playerInfo[connId] = stat;
            tcSound::Get()->PlayEffect("intercom");
        }
        else
        {
            playerInfo[connId].timestamp = tcTime::Get()->Get30HzCount();
        }
    }


    std::queue<int> eraseKeys;

    for (std::map<int,tcPlayerStatus>::iterator iter = playerInfo.begin();
        iter != playerInfo.end(); ++iter) 
    {
        unsigned t = iter->second.timestamp;
        // key is in iter->first, value in iter->second

		if (IsServer() && !iter->second.isAuthenticated && 
              (currentTime - iter->second.startTime > 240))
		{
            eraseKeys.push(iter->first);
            tcSound::Get()->PlayEffect("fslide");
		}
        else if (currentTime - t > 15)
        {
            eraseKeys.push(iter->first);
            tcSound::Get()->PlayEffect("fslide");
			LogOutPlayer(iter->second.name);

			if (IsServer())
			{
				wxString msg = wxString::Format("*** %s has left the game", 
					iter->second.GetNameWithRank().c_str());
				BroadcastChatText(msg.ToStdString());
			}
			else
			{
                OnLostServer();
			}
        }

    }

    while (!eraseKeys.empty())
    {
        int id = eraseKeys.front();
        playerInfo.erase(id);
        networkInterface->RemoveConnection(id);
        eraseKeys.pop();
    }
}

/**
* Send sensor map update for player at connIdx
*/
void tcMultiplayerInterface::UpdateSensorMap(tcPlayerStatus& pstatus)
{
    int connId = pstatus.connectionId;
    int alliance = pstatus.alliance;

    tcSimState* simState = tcSimState::Get();
    wxASSERT(simState);

    tcSensorMap* sensorMap = simState->GetSensorMap();
    tcAllianceSensorMap* allianceSensorMap = sensorMap->GetMap(alliance);
	if (allianceSensorMap == 0) return;
	

    tcUpdateStream stream;
    tcUpdateMessageHandler::InitializeMessage(tcUpdateMessageHandler::SENSOR_UPDATE, stream);
    stream.SetDoneFlag(false);


    unsigned int nMessages = 0;
	const unsigned int maxMessages = 4;
    bool doneWriting = false;

    while (!doneWriting && (nMessages++ < maxMessages))
    {    
        tcUpdateMessageHandler::AddSensorUpdateHeader(alliance, stream);
        size_t initialStreamSize = stream.size();

        *allianceSensorMap >> stream;
        doneWriting = stream.GetDoneFlag();

        if (stream.size() > initialStreamSize)
        {
            SendUpdateMessage(connId, stream);
            fprintf(stdout, ">> sensormap update msg sent, connId (%d) size (%d) msg (%d)\n",
                connId, stream.size(), nMessages);
        }

        if (!doneWriting)
        {
            stream.clear();
            tcUpdateMessageHandler::InitializeMessage(tcUpdateMessageHandler::SENSOR_UPDATE, stream);
            stream.SetDoneFlag(false);
        }
    }

    if (nMessages >= maxMessages)
    {
        fprintf(stderr, "tcMultiplayerInterface::UpdateSensorMap - exceeded max messages\n");
    }
}

/**
* Periodically send sensor updates to clients
*/
void tcMultiplayerInterface::UpdateSensorMaps()
{
    wxASSERT(IsServer());

    unsigned int t = tcTime::Get()->Get30HzCount();

    std::map<int, tcPlayerStatus>::iterator iter = playerInfo.begin();

    for( ; iter != playerInfo.end(); ++iter)
    {
        tcPlayerStatus& player = iter->second;
        unsigned int dt = t - player.sensorUpdateTime;
        if ((dt > sensorUpdateInterval) && (player.isAuthenticated) && (player.isInGame))
        {
            player.sensorUpdateTime = t;
            
            UpdateSensorMap(player);
        }
    }

}


/**
*
*/
void tcMultiplayerInterface::UpdateServerStatus()
{
    static unsigned lastUpdate = 0;
    unsigned currentTime = tcTime::Get()->Get30HzCount();
    if (currentTime - lastUpdate < 150) return;
    
    lastUpdate = currentTime;

    WriteHtmlStatus(logFilePath);
}


void tcMultiplayerInterface::UpdateTeamStatus()
{
	wxASSERT(IsServer());

	unsigned int updateInterval = teamUpdateInterval;

	tcSimState* simState = tcSimState::Get();
    if (simState->IsMultiplayerGameStarted())
	{
		updateInterval = 19; // faster update before game starts
	}

	static unsigned lastUpdate = 0;
    unsigned currentTime = tcTime::Get()->Get30HzCount();
    if (currentTime - lastUpdate < updateInterval) return;
    
    lastUpdate = currentTime;

	tcUpdateStream stream;
	tcUpdateMessageHandler::InitializeMessage(tcUpdateMessageHandler::TEAM_STATUS, stream);
	tcUpdateMessageHandler::AddTeamStatus(stream);


	const std::list<int>& connectionList = networkInterface->GetConnectionList();
    std::list<int>::const_iterator iter = connectionList.begin();

    for( ; iter != connectionList.end(); ++iter)
    {
        int id = *iter;

		tcUpdateStream connStream(stream);

        SendUpdateMessageTCP(id, connStream);
	}

	mpGameView->SetTeamList(tcUpdateMessageHandler::GetLatestTeamList());
}


/**
* Periodically broadcasts time update to all clients
* Set time acceleration based on game speed requests of commanders
*/
void tcMultiplayerInterface::UpdateTime()
{
    static unsigned lastUpdate = 0;    
    static long lastAccel = 0;
    
    // send time update if acceleration has changed
    tcSimState* simState = tcSimState::Get();
    long currentAccel = simState->GetTimeAcceleration();
    if (currentAccel != lastAccel)
    {
        BroadcastControlMessage(tcControlMessageHandler::CM_TIME);
    }
    lastAccel = currentAccel;


    unsigned currentTime = tcTime::Get()->Get30HzCount();
    if (currentTime - lastUpdate < 30) return;
    lastUpdate = currentTime;

    // update time acceleration
    const std::list<int>& connectionList = networkInterface->GetConnectionList();
    std::list<int>::const_iterator iter = connectionList.begin();
    long minVal = 999;
    long maxVal = -1;

    for( ; iter != connectionList.end(); ++iter)
    {
        int destination = *iter;    
		
        tcPlayerStatus& player = GetPlayerStatus(destination);
        
        if (player.IsCommander())
        {
            long requestedSpeed = (long)player.GetGameSpeed();
            minVal = std::min(minVal, requestedSpeed);
            maxVal = std::max(maxVal, requestedSpeed);
        }
    }
    
    // any commander can slow down time accel
    // commanders must agree to speed up time
    bool legalChange = (minVal < currentAccel) || 
        ((minVal > currentAccel) && (minVal == maxVal));
    if ((maxVal != -1) && legalChange)
    {
        wxEvtHandler* evtHandler = this->GetEvtHandler();
		wxCommandEvent command(wxEVT_COMMAND_BUTTON_CLICKED, ID_SETTIMEACCEL);
        //command.m_extraLong = minVal; // 2.6.3 code
        command.SetExtraLong(minVal);
		evtHandler->AddPendingEvent(command);
    }
    

    // send time message to all clients if game is paused
    if (currentAccel == 0)
    {
        BroadcastControlMessage(tcControlMessageHandler::CM_TIME);
    }
}

void tcMultiplayerInterface::WriteHtmlStatus(const std::string& filePath)
{
    wxASSERT(IsServer());

    wxFFile outFile(filePath.c_str(), "w");
    if (!outFile.IsOpened()) return;

    // trim length of recentEvents if necessary
    if (recentEvents.size() > 16)
    {
        recentEvents.RemoveAt(0, recentEvents.size() - 16);
    }

    if (recentChat.size() > 16)
    {
        recentChat.RemoveAt(0, recentChat.size() - 16);
    }


    wxDateTime dateTime = wxDateTime::Now();
    wxDateTime dateTimeUTC = dateTime;
    dateTimeUTC.MakeTimezone(wxDateTime::UTC);

    wxString timeStamp;
    timeStamp.Printf("<P>%s %sZ %sL\n%s</P>\n", dateTimeUTC.FormatISODate().c_str(), dateTimeUTC.FormatISOTime().c_str(),
        dateTime.FormatISOTime().c_str(), versionString.c_str());
 
    outFile.Write("<html>\n");
    outFile.Write("<H2>GCB2 Server Status (gcblue.servegame.com)</H2>\n");    
    outFile.Write(timeStamp.c_str());
    
    wxString s; 
    // scenario
    double simTime = 0.016667 * tcSimState::Get()->GetTime();
    if (simTime > 0)
    {
        s.Printf("<H3>Current Scenario: %s (%.0f min)</H3>\n", tcSimState::Get()->GetScenarioName(),
            simTime);
    }
    else
    {
        s.Printf("<H3>Current Scenario: %s (not started)</H3>\n", tcSimState::Get()->GetScenarioName());
    }
    outFile.Write(s);

    s.Printf("<P>%s</P><BR>\n", tcSimState::Get()->GetScenarioDescription());
    outFile.Write(s);

    // players in game
    tcAllianceInfo* allianceInfo = tcAllianceInfo::Get();
    outFile.Write("<H3>Current Players</H3>\n");
    s = "<P>\n";
    std::map<int, tcPlayerStatus>::iterator iter = playerInfo.begin();

    for( ; iter != playerInfo.end(); ++iter)
    {
        tcPlayerStatus& player = iter->second;
        s += "<B>";
        s += player.GetName();
        s += "</B> (";
        unsigned char alliance =  player.GetAlliance();
        if (alliance != 0)
        {
            s += allianceInfo->GetAllianceName(alliance);
        }
        else
        {
            s += "Observers";
        }
        s += wxString::Format(") Ping: %4.0f ms\n", 1000.0f*player.ping_s);

    }
    s += "</P><BR>\n";
    outFile.Write(s);


    // recent log ins / log outs
    outFile.Write("<H3>Recent Events</H3>\n");
    s = "<P>";
    for (size_t k=0; k<recentEvents.size(); k++)
    {
        s += recentEvents[k];
        s += "<BR>\n";
        
    }
    s += "</P>\n";
    outFile.Write(s);

    // recent chat text
    outFile.Write("<H3>Recent Chat</H3>\n");
    s = "<P>";
    for (size_t k=0; k<recentChat.size(); k++)
    {
        s += recentChat[k];
        s += "<BR>\n";
        
    }
    s += "</P>\n";
    outFile.Write(s);


    outFile.Write("</html>\n");
}


tcMultiplayerInterface::tcMultiplayerInterface()
:   tcpChat(true), 
    myName("NoName"), 
    evtHandler(0), 
    entityUpdateInterval(0),
    sensorUpdateInterval(30),
	goalUpdateInterval(600),
	teamUpdateInterval(39),
    missionUpdateInterval(87),
    lastOptionsUpdate(0),
    sendDetailedTrackInfo(false),
	acceptAllClients(true),
    allowAllTeamChanges(true),
	mpGameView(0),
	scenarioSelectView(0)
{
    networkInterface = new tcNetworkInterface();
    wxASSERT(networkInterface);

    errorPlayerStatus.name = "error";
    errorPlayerStatus.timestamp = 0;
    
    serverPlayerStatus.SetName("SERVER");
    serverPlayerStatus.SetNameWithRank("SERVER");
    serverPlayerStatus.SetAlliance(0);
	serverPlayerStatus.isCommander = true;
	serverPlayerStatus.SetRank(tcUserInfo::RANK_GM);
    serverPlayerStatus.timestamp = 0;
    serverPlayerStatus.isAuthenticated = true;
    serverPlayerStatus.data.flags = 0xFFFF;
    serverPlayerStatus.SetConnectionId(0);
 
	updateCount = 0;
}

/**
* Copy constructor not allowed for this singleton class
*/
tcMultiplayerInterface::tcMultiplayerInterface(const tcMultiplayerInterface& source)
:   entityUpdateInterval(source.entityUpdateInterval),
    sensorUpdateInterval(source.sensorUpdateInterval),
	goalUpdateInterval(source.goalUpdateInterval),
	teamUpdateInterval(source.teamUpdateInterval),
    missionUpdateInterval(source.missionUpdateInterval)
{
    wxASSERT(false);
}

tcMultiplayerInterface::~tcMultiplayerInterface()
{
    ClearMessageMap();

    if (networkInterface)
	{
		delete networkInterface;
	}
}

END_NAMESPACE

