/** 
**  @file tcMultiplayerInterface.h
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

#ifndef _MULTIPLAYERINTERFACE_H_
#define _MULTIPLAYERINTERFACE_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "wx/wx.h"

#include <list>
#include <map>
#include <queue>
#include <string>
#include <vector>
#include "tcAccountDatabase.h"

#define BEGIN_NAMESPACE(x) namespace x {
#define END_NAMESPACE }

class wxEvtHandler;
class tcStream;
class tcConsoleBox;
class tcGameObject;
class tcMPGameView;
class tcScenarioSelectView;

/**
* Multiplayer network code.
*/
namespace network
{
}

BEGIN_NAMESPACE(network)

class tcNetworkInterface;
class tcMessageHandler;

class tcPlayerStatus
{
public:
    struct UpdateInfo
    {
        unsigned int updateTime;
        unsigned int detailedUpdateTime;
    };

    std::string name; ///< username of player
	std::string nameWithRank; ///< name with rank title
	bool isAuthenticated; ///< true if password has been verified
    unsigned char alliance; ///< player's alliance for current game, or 0 if not selected
	unsigned char rank; ///< player's rank
    bool isXmlObserver; ///< true for passive listener of XML game state updates
    bool isCommander; ///< true if player is commander for alliance
	bool isReady; ///< true if player has indicated ready (pre-game)
    bool isInGame; ///< true if player is "in the game" and should receive unit updates
    bool wantsGameEnd; ///< true if player requests end to game
    bool wantsSurrender; ///< true if player surrenders

    unsigned char requestedGameSpeed; ///< 0 - pause, 1 - normal, 2 - 2x, etc.
    unsigned int timestamp; ///< time of last network update (30 Hz tics)
	unsigned int startTime; ///< time connection started (30 Hz tics)
	unsigned int entityUpdateTime; ///< time of last entity update (30 Hz tics)
	unsigned int sensorUpdateTime; ///< time of last sensor update (30 Hz tics)
    float ping_s; ///< value of last ping
    std::map<long, UpdateInfo> lastUpdate; ///< map of (obj id, update time (30Hz tics))
	tcAccountDatabase::UserData data; ///< local copy of account database entry (messy, merge or otherwise fix this)
    int connectionId;

    void EraseEntry(long id);
	unsigned char GetAlliance() const;
	int GetConnectionId() const;
    unsigned char GetGameSpeed() const;
    bool GetLastUpdate(long id, unsigned int& updateTime, unsigned int& detailedUpdateTime);
	const std::string& GetName() const;
	const std::string& GetNameWithRank() const;
	unsigned char GetRank() const;
    bool IsInGame() const;
    bool WantsGameEnd() const;
    bool WantsSurrender() const;
    bool IsXmlObserver() const;
    bool IsCommander() const;
	bool IsReady() const;
	bool IsGM() const;
	void SetAlliance(unsigned char val);
	void SetConnectionId(int id);
    void SetGameSpeed(unsigned char val);
    void SetInGame(bool state);
    void SetGameEnd(bool state);
    void SetSurrender(bool state);
	void SetName(const std::string& s);
	void SetNameWithRank(const std::string& s);
	void SetRank(unsigned char val);
    void SetXmlObserver(bool state);
	void SetReady(bool state);
    void SetUpdate(long id, unsigned int updateTime);
    void SetDetailedUpdate(long id, unsigned int detailedUpdateTime);
};

/**
* Singleton multiplayer interface class to manage connections,
* send and receive messages, and report connection status.
* This class interfaces with tcNetworkInterface
* in a manner that avoids wxWidgets header dependencies. Could
* also try this as an abstract base class, but application level
* methods exist in this class as well.
*
*/
class tcMultiplayerInterface
{
public:
    enum
    {
        MSG_CHATTEXT = 1,
        MSG_CONTROL = 2,
        MSG_AUTHENTICATION = 3,
        MSG_UPDATE = 4
    };
    static tcMultiplayerInterface* Get();
    static bool EntityUpdateReceived();


    void AddChatSubscriber(tcConsoleBox* subscriber);
	void AttachMPGameView(tcMPGameView* gv);
	void AttachScenarioSelectView(tcScenarioSelectView* ssv);

    void AddMessageHandler(int messageId, tcMessageHandler* handler);
	void AuthenticatePlayer(int connectionId, const std::string& username,
		const std::string& passwordHash);
	void BroadcastChatText(const std::string& message, unsigned char alliance = 0);
    void BroadcastControlMessage(int messageCode);
	void BroadcastScenarioInfo();
    void BroadcastDatabaseInfo();
    //std::string GetChatText();

	bool GetAcceptAllClients() const;
	const std::list<int>& GetConnectionList() const;
	const std::vector<int>& GetConnectionVector() const;
    const std::string& GetConnectionStatus(int connectionId);

    wxEvtHandler* GetEvtHandler() const;
    const std::string& GetName() const;
    unsigned int GetNumConnections();
	const std::string& GetPassword() const;

	int GetPlayerConnectionId(const std::string& playerName);
    tcPlayerStatus& GetPlayerStatus(int connectionId); ///< redundant with GetConnectionStatus?
	const std::string& GetPlayerName(int connectionId);
    void InitMessageHandlers();
    bool IsChatTextAvail(); 
    bool IsCommand(const std::string& text);
	bool IsConnecting() const;
    bool IsServer() const;
	int LogInPlayer(const std::string& username, int connectionId, 
		   tcPlayerStatus& playerStatus, wxString& msg);
	void LogOutPlayer(const std::string& username);
	void LogOutAllPlayers();
    void SetAllReadyState(bool state);
    void SetAllEndGameState(bool state);

    unsigned GetTeamGameSpeed() const;
    unsigned GetFastestGameSpeed() const;

    bool IsGameOver(wxString& message) const;

    void MakeClient();
    void MakeServer();
    void OpenConnection(const std::string& hostName);
    void ProcessCommandClient(int connectionId, const std::string& text);
    void ProcessCommandServer(const std::string& text);
    void RemoveChatSubscriber(tcConsoleBox* subscriber);
	void Reset();
	void ResetGame();
	void SendAuthRequest(int destination);
	void SendAuthResponse(int destination);
	void SendBriefingText(int destination, int alliance);
    void SendChatText(int destination, const std::string& message);
    void SendControlMessage(int destination, int messageCode, int param = 0);
    void SendControlMessageUDP(int destination, int messageCode, int param = 0);
    void SendControlMessageUDPAck(int destination, int messageCode, int param = 0);
	void SendControlRelease(long id);
    void SendControlRelease(const std::vector<long>& id);
	void SendControlRequest(long id);
    void SendControlRequest(const std::vector<long>& id);
    void SendDatabaseInfo(const std::vector<int>& destinations);
    void SendDatabaseInfo(int destination);
	void SendScenarioInfo(const std::vector<int>& destinations);
	void SendScenarioInfo(int destination);
	void SendSoundEffect(const std::string& player, const std::string& effect, long id = -1);
	void SendSoundEffect(int destination, const std::string& effect, long id = -1);
    void SendTestUDP(int destination, const std::string& message);
    void SendUpdateMessage(int destination, tcStream& stream);
	void SendUpdateMessageAck(int destination, tcStream& stream);
	void SendUpdateMessageTCP(int destination, tcStream& stream);
	void SetAcceptAllClients(bool state);
    void SetChatProtocol(int code); 
    void SetEvtHandler(wxEvtHandler *eh);
    void SetName(const std::string& name);
	void SetPassword(const std::string& plainText);
	void SetPingTime(int connectionId, float ping_s);
    void SetVersionString(const char* s);

    void Update(); 

	unsigned updateCount; ///< elapsed time for last update

private:
    tcNetworkInterface *networkInterface;
    std::queue<std::string> chatText; ///< chat text to display
    std::vector<tcConsoleBox*> chatSubscribers;
	tcMPGameView* mpGameView; ///< to populate team list on server
	tcScenarioSelectView* scenarioSelectView; ///< for scenario selection commands

    std::string myName; ///< name to identify player (username)
	std::string passwordHash; ///< hashed password
    std::map<int, tcPlayerStatus> playerInfo; ///< map of (connection id, tcPlayerStatus) pairs
	std::map<std::string, int> playerToConnection; ///< map of (player name, connection id)
    std::map<int, std::vector<tcMessageHandler*> > messageMap; ///< map of (message id, message handler vector) pairs
    bool tcpChat; ///< true to use TCP for chat protocol, otherwise UDP
	bool acceptAllClients; ///< true to accept all client logins, adding to accounts db if necessary
    bool allowAllTeamChanges; ///< true to always allow team changes
    tcPlayerStatus errorPlayerStatus; ///< status to return if player not found
    tcPlayerStatus serverPlayerStatus; ///< status to use for server actions
    wxEvtHandler* evtHandler; ///< wxWidgets event handler for posting messages to application

    // data for html status log
    std::string logFilePath;
    wxArrayString recentEvents;
    wxArrayString recentChat;
    std::string versionString; // for reporting server version

    const unsigned int entityUpdateInterval; ///< 30 Hz tics
    unsigned int sensorUpdateInterval; ///< 30 Hz tics
	const unsigned int goalUpdateInterval; ///< 30 Hz tics
	const unsigned int teamUpdateInterval;
    const unsigned int missionUpdateInterval; ///< 30 Hz tics
    bool sendDetailedTrackInfo; ///< true to send emitter and contributor details to client

    unsigned int lastOptionsUpdate; ///< 30 Hz tics, last update count


    void ClearMessageMap();
    void DistributeChatText();
    void GetUpdatePeriod(const tcGameObject* obj, const std::string& playerName,
        unsigned int& updatePeriod, unsigned int& detailedUpdatePeriod) const;
    bool IsNewPlayer(int id);

    void ProcessAllianceCommand(tcPlayerStatus& player, const wxString& args);
	void ProcessChangeCommander(tcPlayerStatus& player, const wxString& args);
	void ProcessChangeReady(tcPlayerStatus& player, const wxString& args);
    void ProcessEndGame(tcPlayerStatus& player, const wxString& args);
    void ProcessGameSpeed(tcPlayerStatus& player, const wxString& args);
    void ProcessGameMasterCommand(tcPlayerStatus& player, const wxString& args);    
	void ProcessGMAddAccount(const wxString& args, wxString& msg);
	void ProcessGMCreate(const wxString& args, wxString& msg);
	void ProcessGMKick(const wxString& args, wxString& msg);
	void ProcessGMMove(const wxString& args, wxString& msg);
    void ProcessGMSetController(const wxString& args, wxString& msg);
    void ProcessGMSetTeamChanges(const wxString& args, wxString& msg);
    void ProcessMessage(int messageId, int connectionId, 
                    unsigned messageSize, const unsigned char *data);

    void ProcessReceiveMessages();
	void ProcessScenarioCommand(tcPlayerStatus& player, const wxString& args);
	void ProcessStartGame(tcPlayerStatus& player, const wxString& args);
    void ProcessSurrender(tcPlayerStatus& player, const wxString& args);
	void ProcessTeamChat(const tcPlayerStatus& player, const wxString& msg);
	void ProcessWho(tcPlayerStatus& player, const wxString& args);
    void UpdateDestroyedEntities(tcPlayerStatus& pstatus);
    void UpdateNewAndExistingEntities(tcPlayerStatus& pstatus);
    void UpdateEntitiesXml(tcPlayerStatus& pstatus);
    void UpdateEntityCommands(tcPlayerStatus& pstatus, bool clearNewCmdFlag);
    void UpdateEntities();
	void UpdateGoalStatus();
    void UpdateMissions();
    void UpdateOptions();
    void UpdatePing();
    void UpdatePlayerInfo();
	void UpdateScriptCommands(int connectionId);
    void UpdateSensorMaps();
    void UpdateSensorMap(tcPlayerStatus& pstatus);
    void UpdateTime();
	void UpdateTeamStatus();
    void UpdateServerStatus();

    void OnLostServer();

	bool AllianceHasCommander(unsigned char alliance);
	void AssignNewCommander(unsigned char alliance);

    void WriteHtmlStatus(const std::string& filePath);

    tcMultiplayerInterface();
    tcMultiplayerInterface(const tcMultiplayerInterface& source);
    virtual ~tcMultiplayerInterface();
};

END_NAMESPACE

#endif

