/** 
** @file tcUpdateMessageHandler.h
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


#ifndef _UPDATEMESSAGEHANDLER_H_
#define _UPDATEMESSAGEHANDLER_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include <queue>
#include <string>

#include "network/tcMessageHandler.h"
#include "tcMPGameView.h"

class tcGameObject;
class tcFlightOpsObject;
class tcStream;
class tcCommandStream;
class tcCreateStream;
class tcUpdateStream;

class tcMPGameView;

#define BEGIN_NAMESPACE(x) namespace x {
#define END_NAMESPACE }

BEGIN_NAMESPACE(network)

/**
* Game object update handler
*/
class tcUpdateMessageHandler : public tcMessageHandler
{
public:
    enum
    {
        CREATE = 0, ///< creates a game obj
        CREATE_REQUEST = 1, ///< request create message for unknown obj
        UPDATE = 2, ///< routine update of a game obj
        COMMAND_UPDATE = 3, ///< command-related update
        COMMAND_ACK = 4, ///< ack of command-related update
        DESTROY = 5, ///< destroys game obj
        SENSOR_UPDATE = 6, ///< update of sensor map tracks
		CONTROL_REQUEST = 7, ///< request to take control of obj
		SOUND_EFFECT = 8, ///< play sound effect for object
		SCRIPT_COMMANDS = 9, ///< script commands to execute on server
		SCENARIO_INFO = 10, ///< info on scenario
		GOAL_STATUS = 11, ///< goal status for client
		BRIEFING_TEXT = 12, ///< briefing text for client
		TEAM_STATUS = 13, ///< summary of team and player state
        AUTO_MISSIONS = 14, ///< update of air-automation mission data
        DATABASE_INFO = 15 ///< database name, key pairs to synch client and server db

    };

	static tcMPGameView* mpGameView;

	static void AddBriefingText(long alliance, tcStream& stream);
    static void AddCommandAck(tcGameObject* obj, tcCommandStream& stream);
    static void AddCommandUpdate(tcGameObject* obj, tcCommandStream& stream);
	static void AddControlRelease(long id, tcStream& stream);
	static void AddControlRequest(long id, tcStream& stream);
    static bool AddCreate(tcGameObject* obj, tcCreateStream& stream);
    static void AddCreateRequest(long id, tcStream& stream);
    static void AddDestroy(long id, tcStream& stream);
	static void AddGoalStatus(long alliance, tcUpdateStream& stream);
	static void AddScenarioInfo(tcUpdateStream& stream);
    static void AddSensorUpdateHeader(long alliance, tcStream& stream);
	static void AddSoundEffect(long id, const std::string& effect, tcStream& stream);
	static void AddTeamStatus(tcStream& stream);
    static bool AddUpdate(tcGameObject* obj, tcUpdateStream& stream);
    static void AddAirMissionUpdate(tcFlightOpsObject* obj, tcUpdateStream& stream);

	static void AttachMPGameView(tcMPGameView* p);

    static void InitializeMessage(int messageType, tcStream& stream);

    virtual void Handle(int connectionId, unsigned messageSize, const unsigned char *data);
    void HandleAirMissionUpdate(tcUpdateStream& stream);
	void HandleBriefingText(tcStream& stream);
    void HandleCommandAck(tcCommandStream& stream); ///< command ack
    void HandleCommandUpdate(tcCommandStream& stream, int connectionId); ///< command update
    void HandleControlRequest(tcStream& stream, int connectionId);
    void HandleCreate(tcCreateStream& stream);
    void HandleCreateRequest(tcStream& stream, int connectionId);
    void HandleDatabaseInfo(tcStream& stream);
    void HandleDestroy(tcStream& stream);
	void HandleGoalStatus(tcUpdateStream& stream);
	void HandleScenarioInfo(tcUpdateStream& stream);
	void HandleScriptCommands(tcStream& stream, int connectionId);
    void HandleSensorUpdate(tcUpdateStream& stream);
	void HandleSoundEffect(tcStream& stream);
	void HandleTeamStatus(tcStream& stream);
    void HandleUpdate(tcUpdateStream& stream, int connectionId);

	static std::vector<tcMPGameView::TeamInfo>& GetLatestTeamList();
    static bool EntityUpdateReceived();

    tcUpdateMessageHandler();
    virtual ~tcUpdateMessageHandler();

private:
	static std::vector<tcMPGameView::TeamInfo> latestTeamList; ///< got to be a better place to do this!
    static bool entityUpdateReceived; ///< set true when entity update received

	static void UpdateTeamList(std::vector<tcMPGameView::TeamInfo>& teamList);

};

END_NAMESPACE

#endif

