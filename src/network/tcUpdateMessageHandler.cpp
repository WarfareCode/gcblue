/**
** @file tcUpdateMessageHandler.cpp
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

#include "network/tcUpdateMessageHandler.h"
#include "network/tcMultiplayerInterface.h"
#include "network/tcMessage.h"
#include "tcSimState.h"
#include "wxcommands.h"
#include "common/tcStream.h"
#include "common/tcObjStream.h"
#include "tcGoalTracker.h"
#include "tcSimPythonInterface.h"
#include "tcScenarioInterface.h"
#include "tcMapOverlay.h"
#include "tcMessageInterface.h"
#include "tcMPGameView.h"
#include "tcFlightOpsObject.h"
#include "ai/tcMissionManager.h"
#include "tcGameObjIterator.h"
#include "tcAllianceSensorMap.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_NAMESPACE(network)


tcMPGameView* tcUpdateMessageHandler::mpGameView = 0;
std::vector<tcMPGameView::TeamInfo> tcUpdateMessageHandler::latestTeamList;
bool tcUpdateMessageHandler::entityUpdateReceived = false;





void tcUpdateMessageHandler::AttachMPGameView(tcMPGameView* p)
{
	mpGameView = p;
}


/**
* Only call on objects with active missions
*/
void tcUpdateMessageHandler::AddAirMissionUpdate(tcFlightOpsObject* obj, tcUpdateStream& stream)
{
    wxASSERT(obj != 0);

    tcFlightPort* flightPort = obj->GetFlightPort();
    wxASSERT(flightPort != 0);

    long platformId = obj->GetParentId();
    stream << platformId;

    tcMissionManager* missionManager = flightPort->GetMissionManager();
    wxASSERT(missionManager != 0);

    missionManager->operator>>(stream);
}


void tcUpdateMessageHandler::AddBriefingText(long alliance, tcStream& stream)
{

	tcScenarioInterface* scenarioInterface = tcSimPythonInterface::Get()->GetScenarioInterface();
	wxASSERT(scenarioInterface);

	const std::string& briefingText = scenarioInterface->GetSimpleBriefing(alliance);

	stream << alliance;
	stream << briefingText;
}

/**
* stream must have SetAck(true) called first
*/
void tcUpdateMessageHandler::AddCommandAck(tcGameObject* obj, tcCommandStream& stream)
{
	wxASSERT(false);

}

/**
*
*/
void tcUpdateMessageHandler::AddCommandUpdate(tcGameObject* obj, tcCommandStream& stream)
{
    stream << obj->mnID; // write id

    /** 
    * A temporary stream is created so that the size of the 
    * obj update can be written before the data to allow 
    * skipping over when the client doesn't have the obj created 
    * yet. There may be a way to write a temp value for
    * size, keep a reference to the pos in the stream, and update
    * the value. This would avoid copying the entire update.
    */
    tcCommandStream temp;

    *obj >> temp;

    unsigned int updateSize = (unsigned int)temp.size();

    stream << updateSize;

    stream << temp;
}

void tcUpdateMessageHandler::AddControlRelease(long id, tcStream& stream)
{
	bool releaseControl = true;

	stream << releaseControl;
	stream << id;
}

void tcUpdateMessageHandler::AddControlRequest(long id, tcStream& stream)
{
	bool releaseControl = false;

	stream << releaseControl;
	stream << id;
}

/**
* Saves data to create obj to stream. 
*
* @return true if create was added, false if a size limit was hit and needs to be added again
*/
bool tcUpdateMessageHandler::AddCreate(tcGameObject* obj, tcCreateStream& stream)
{
    long freeSpace = (long)stream.GetMaxSize() - (long)stream.size();
    if (freeSpace < 1) return false;

    // temporary stream for command data
    tcCommandStream tempCommand;
    tempCommand.SetDetailLevel(tcStream::WRITE_ALL);
    *obj >> tempCommand;
    freeSpace -= (long)tempCommand.size();
    if (freeSpace < 1) return false;

    // temporary create stream
    tcCreateStream temp;
    temp.SetMaxSize(size_t(freeSpace));
    temp.SetDoneFlag(true);

    temp << obj->mnID;
    //temp << obj->mnDBKey;
    temp << std::string(obj->mzClass.c_str()); // 20SEP2009, databases don't have same names,keys anymore

    *obj >> temp;

    if (temp.size() > temp.GetMaxSize()) return false; // too big, don't add

    stream << temp;
    stream << tempCommand;
    
    return temp.GetDoneFlag();
}

/**
* 
*/
void tcUpdateMessageHandler::AddCreateRequest(long id, tcStream& stream)
{
    stream << id;
}

/**
* Saves destroy information to stream to destroy object with id
*/
void tcUpdateMessageHandler::AddDestroy(long id, tcStream& stream)
{
    stream << id;
}

void tcUpdateMessageHandler::AddGoalStatus(long alliance, tcUpdateStream& stream)
{
	stream.SetDetailLevel(alliance);

	tcGoalTracker* goalTracker = tcGoalTracker::Get();

	goalTracker->operator>>(stream);
}

void tcUpdateMessageHandler::AddScenarioInfo(tcUpdateStream& stream)
{
	tcSimState* simState = tcSimState::Get();
	tcSimPythonInterface* pythonInterface = tcSimPythonInterface::Get();
	tcScenarioInterface* scenarioInterface = pythonInterface->GetScenarioInterface();
	tcMapOverlay* overlay = scenarioInterface->GetMapOverlay();
	tcAllianceInfo* allianceInfo = tcAllianceInfo::Get();

	std::string scenarioName = simState->GetScenarioName();
	stream << scenarioName;

	std::string scenarioDescription = simState->GetScenarioDescription();
	stream << scenarioDescription;

	double theater_lon;
	double theater_lat;
	scenarioInterface->GetStartTheater(theater_lon, theater_lat);
	stream << theater_lon;
	stream << theater_lat;

	overlay->operator>>(stream);

	allianceInfo->operator>>(stream);

}

/**
* Adds header information to sensor update stream
* Currently this is just an alliance field
*/
void tcUpdateMessageHandler::AddSensorUpdateHeader(long alliance, tcStream& stream)
{
    stream << alliance;
}

/**
* Adds sound effect info to stream
* @param id entity id that sound effect is associated with
*/
void tcUpdateMessageHandler::AddSoundEffect(long id, const std::string& effect, tcStream& stream)
{
	stream << id;
	stream << effect;
}

void tcUpdateMessageHandler::AddTeamStatus(tcStream& stream)
{
//	tcMultiplayerInterface* multiplayerInterface = tcMultiplayerInterface::Get();
//	tcAllianceInfo* allianceInfo = tcAllianceInfo::Get();

	UpdateTeamList(latestTeamList);

	std::vector<tcMPGameView::TeamInfo>& teamList = latestTeamList;


	size_t nTeams = teamList.size();
	stream << nTeams;

	for (size_t n=0; n<nTeams; n++)
	{
		tcMPGameView::TeamInfo& teamInfo = teamList[n];

		stream << teamInfo.alliance;
		stream << teamInfo.name;

		size_t nPlayers = teamList[n].playerList.size();
		stream << nPlayers;
		for (size_t k=0; k<nPlayers; k++)
		{
			stream << teamList[n].playerList[k].isCommander;
			stream << teamList[n].playerList[k].isReady;
            stream << teamList[n].playerList[k].gameSpeed;
			stream << teamList[n].playerList[k].name;
            stream << teamList[n].playerList[k].inGame; 
            stream << teamList[n].playerList[k].endGame;
            stream << teamList[n].playerList[k].surrenderGame;
		}
	}


	//const std::list<int>& connList = multiplayerInterface->GetConnectionList();
	//const tcPlayerStatus& playerInfo = multiplayerInterface->GetPlayerStatus(connectionId);

	//const std::string& playerName = playerInfo.GetName();
	//const unsigned char playerRank = playerInfo.GetRank();
	//const unsigned char playerAlliance = playerInfo.GetAlliance();


    //struct PlayerInfo
    //{
    //    std::string name;
    //    bool isCommander;
    //};

    //struct TeamInfo
    //{
    //    std::string name;
    //    std::vector<PlayerInfo> playerList;
    //};

}


/**
* Saves update data for obj to stream. Obj must be 
* created first for this data to be applied.
* @return true if update was added, false if a size limit was hit and needs to be added again
*
* @see tcUpdateMessageHandler::AddCreate
*/
bool tcUpdateMessageHandler::AddUpdate(tcGameObject* obj, tcUpdateStream& stream)
{
    long freeSpace = (long)stream.GetMaxSize() - (long)stream.size() - sizeof(long) - sizeof(unsigned int);
    if (freeSpace < 1) return false;

    /** 
    * A temporary stream is created so that the size of the 
    * obj update can be written before the data to allow 
    * skipping over when the client doesn't have the obj created 
    * yet. There may be a way to write a temp value for
    * size, keep a reference to the pos in the stream, and update
    * the value. This would avoid copying the entire update.
    */
    tcUpdateStream temp;
    temp.SetMaxSize(size_t(freeSpace));
    temp.SetDoneFlag(true);
    temp.SetDetailLevel(stream.GetDetailLevel());

    *obj >> temp;

    if (temp.size() > temp.GetMaxSize()) return false; // too big, don't add

    stream << obj->mnID; // write id

    unsigned int updateSize = (unsigned int)temp.size();

    stream << updateSize;

    stream << temp;

    return temp.GetDoneFlag();
}

/**
* @return true if entityUpdateReceived flag was set
* clear flag if true
* Used to update simstate when entity update occurs to avoid position glitches
*/
bool tcUpdateMessageHandler::EntityUpdateReceived()
{
    bool result = entityUpdateReceived;
    entityUpdateReceived = false;

    return result;
}

std::vector<tcMPGameView::TeamInfo>& tcUpdateMessageHandler::GetLatestTeamList()
{
	return latestTeamList;
}


/** 
* Initializes message based on update message type
*/
void tcUpdateMessageHandler::InitializeMessage(int messageType, tcStream& stream)
{
    stream << messageType;

    switch (messageType)
    {
    case CREATE:
        break;
    case CREATE_REQUEST:
        break;
    case UPDATE:
        // update messages start with time and time acceleration info
        tcSimState::Get()->SaveTimeToStream(stream);
        break;
    case COMMAND_UPDATE:
        break;
    case COMMAND_ACK:
        break;
    case DESTROY:
        break;
    case SENSOR_UPDATE:
        break;
    case CONTROL_REQUEST:
        break;
	case SOUND_EFFECT:
		break;
	case SCRIPT_COMMANDS:
		break;
	case SCENARIO_INFO:
		break;
	case GOAL_STATUS:
		break;
	case BRIEFING_TEXT:
		break;
	case TEAM_STATUS:
		break;
    case AUTO_MISSIONS:
        break;
    case DATABASE_INFO:
        break;
    default:
        fprintf(stderr, "tcUpdateMessageHandler::InitializeMessage - bad message type (%d)\n",
            messageType);
        break;
    }

    size_t maxSize = tcMessage::MESSAGE_SIZE - stream.size();
    stream.SetMaxSize(maxSize);

}



void tcUpdateMessageHandler::Handle(int connectionId, unsigned messageSize, const unsigned char *data)
{
    //tcSimState* simState = tcSimState::Get();
    //wxASSERT(simState);

    // end up creating stream twice. could split to use multiple handlers to avoid this
    tcStream stream((const char*)data, messageSize);

    int messageType;
    stream >> messageType;

    if (isServer)
    {
        switch (messageType)
        {
        case CREATE:
        case UPDATE:        
        case DESTROY:
        case SENSOR_UPDATE:
            fprintf(stderr, "tcUpdateMessageHandler::Handle - "
                "illegal msg type for server (%d)\n", messageType);
            return;
        case COMMAND_UPDATE:
            {
                tcCommandStream stream((const char*)data, messageSize);
                stream >> messageType;
                HandleCommandUpdate(stream, connectionId);
            }
            break;
        case COMMAND_ACK:
            {
                tcCommandStream stream((const char*)data, messageSize);
                stream >> messageType;
                HandleCommandAck(stream);
            }
            break;
		case CONTROL_REQUEST:
			{
				HandleControlRequest(stream, connectionId);
			}
			break;
		case CREATE_REQUEST:
			{
				HandleCreateRequest(stream, connectionId);
			}
			break;
		case SCRIPT_COMMANDS:
			{
				HandleScriptCommands(stream, connectionId);
			}
			break;
        default:
            fprintf(stderr, "tcUpdateMessageHandler::Handle - unknown msg type for server\n");
            break;
        }
    }
    else
    {
        switch (messageType)
        {
        case CREATE:
            {
                tcCreateStream stream((const char*)data, messageSize);
                stream >> messageType;
                HandleCreate(stream);
            }
            break;
        case UPDATE:
            {
                tcUpdateStream stream((const char*)data, messageSize);
                stream >> messageType;
                HandleUpdate(stream, connectionId);
            }
            break;
        case COMMAND_UPDATE:
            {
                tcCommandStream stream((const char*)data, messageSize);
                stream >> messageType;
                HandleCommandUpdate(stream, connectionId);
            }
            break;
        case COMMAND_ACK:
            {
                tcCommandStream stream((const char*)data, messageSize);
                stream >> messageType;
                HandleCommandAck(stream);
            }
            break;
        case DESTROY:
            {
                tcStream stream((const char*)data, messageSize);
                stream >> messageType;
                HandleDestroy(stream);
            }
            break;
        case SENSOR_UPDATE:
            {
                tcUpdateStream stream((const char*)data, messageSize);
                stream >> messageType;
                HandleSensorUpdate(stream);
            }
            break;
		case SOUND_EFFECT:
			{
				HandleSoundEffect(stream);
			}
			break;
		case SCENARIO_INFO:
			{
                tcUpdateStream stream((const char*)data, messageSize);
                stream >> messageType;
				HandleScenarioInfo(stream);
			}
			break;
		case GOAL_STATUS:
			{
                tcUpdateStream stream((const char*)data, messageSize);
                stream >> messageType;
				HandleGoalStatus(stream);
			}
			break;
		case BRIEFING_TEXT:
			{
				tcStream stream((const char*)data, messageSize);
                stream >> messageType;
                HandleBriefingText(stream);
			}
			break;
		case TEAM_STATUS:
			{
				tcStream stream((const char*)data, messageSize);
                stream >> messageType;
				HandleTeamStatus(stream);
			}
			break;
        case AUTO_MISSIONS:
            {
                tcUpdateStream stream((const char*)data, messageSize);
                stream >> messageType;
				HandleAirMissionUpdate(stream);
            }
            break;
        case DATABASE_INFO:
            {
                tcUpdateStream stream((const char*)data, messageSize);
                stream >> messageType;
				HandleDatabaseInfo(stream);
            }
        default:
            fprintf(stderr, "tcUpdateMessageHandler::Handle - "
                "unknown msg type for client (%d)\n", messageType);
            break;
        }
    }

}


void tcUpdateMessageHandler::HandleAirMissionUpdate(tcUpdateStream& stream)
{        
    tcSimState* simState = tcSimState::Get();
    wxASSERT(simState);

    // since updates are complete, clear all missions on non-updated platforms
    std::map<long, bool> updatedPlatforms;

    size_t nUpdates = 0;

    long platformId;

    while (((stream >> platformId).eof() == false) && (nUpdates++ < 32))
    {
        tcGameObject* gameObj = simState->GetObject(platformId);
        if (gameObj == 0)
        {
            wxASSERT(false);
            fprintf(stderr, "tcUpdateMessageHandler::HandleAirMissionUpdate - "
                "game obj not found (%d)\n", platformId);
            return;
        }

        updatedPlatforms[platformId] = true;

        if (tcFlightOpsObject* obj = dynamic_cast<tcFlightOpsObject*>(gameObj))
        {
            tcFlightPort* flightPort = obj->GetFlightPort();
            wxASSERT(flightPort != 0);


            tcMissionManager* missionManager = flightPort->GetOrCreateMissionManager();
            wxASSERT(missionManager != 0);

            missionManager->operator<<(stream);
        }
        else
        {
            wxASSERT(false);
            fprintf(stderr, "tcUpdateMessageHandler::HandleAirMissionUpdate - "
                "obj not flight ops (%d)\n", platformId);
            return;
        }
    }

    // clear missions on flightsopsobj that were not updated
    tcGameObjIterator iter;

    for (iter.First();iter.NotDone();iter.Next())
	{
		tcGameObject* gameObj = iter.Get();
        wxASSERT(gameObj != 0);


        if (tcFlightOpsObject* obj = dynamic_cast<tcFlightOpsObject*>(gameObj))
        {
            tcFlightPort* flightPort = obj->GetFlightPort();
            wxASSERT(flightPort != 0);

            tcMissionManager* missionManager = flightPort->GetMissionManager();

            std::map<long, bool>::const_iterator iter = 
                updatedPlatforms.find(gameObj->mnID);

            if ((iter == updatedPlatforms.end()) && (missionManager != 0))
            {
                missionManager->Clear();
            }

        }
    }

}


void tcUpdateMessageHandler::HandleBriefingText(tcStream& stream)
{
	long alliance;
	std::string briefingText;

	stream >> alliance;
	stream >> briefingText;

	tcScenarioInterface* scenarioInterface = tcSimPythonInterface::Get()->GetScenarioInterface();

	scenarioInterface->SetSimpleBriefing(alliance, briefingText);

	tcMessageInterface::Get()->ClearChannel("Briefing");
	tcMessageInterface::Get()->ChannelMessage("Briefing", briefingText, unsigned int(alliance));
}


/**
* Handle COMMAND_ACK
*/
void tcUpdateMessageHandler::HandleCommandAck(tcCommandStream& stream)
{
	wxASSERT(false);

    tcSimState* simState = tcSimState::Get();
    wxASSERT(simState);

    fprintf(stdout, "<< Received obj cmd acks, time %.1f: ", simState->GetTime());

    long id;

    while ((stream >> id).eof() == false)
    {
        // lookup obj
        tcGameObject* obj = simState->GetObject(id);

        // update obj if it exists, otherwise create object
        if (obj)
        {
            *obj << stream;
            fprintf(stdout, "%d ", id);
        }
        else
        {
            fprintf(stderr, "Error - HandleCommandAck - obj %d not found\n", id);
            fprintf(stdout, "\n");
            return;
        }
    }
    fprintf(stdout, "\n");

}

/**
* Handle COMMAND_UPDATE
*/
void tcUpdateMessageHandler::HandleCommandUpdate(tcCommandStream& stream, int connectionId)
{
    tcSimState* simState = tcSimState::Get();
    wxASSERT(simState);


    unsigned nUnknowns = 0;

    fprintf(stdout, "<< Received obj cmds, time %.1f: ", simState->GetTime());

    long id;
    
	const bool isServer = tcMultiplayerInterface::Get()->IsServer();
	const std::string& playerName = tcMultiplayerInterface::Get()->GetPlayerName(connectionId);

    while (((stream >> id).eof() == false) && (nUnknowns < 32))
    {
        unsigned int updateSize;
        stream >> updateSize;

        // lookup obj
        tcGameObject* obj = simState->GetObject(id);

        // update obj if it exists, otherwise skip
        if (obj)
        {
			// validate control rights at server
			if (isServer)
			{
				if (obj->IsControlledBy(playerName))
				{
					*obj << stream;
					fprintf(stdout, "%d ", id);
				}
				else
				{
					stream.skip_read(updateSize);
					fprintf(stdout, "E%d ", id);
				}
			}
			else
			{
				*obj << stream;
				fprintf(stdout, "%d ", id);
			}

            
        }
        else
        {
            stream.skip_read(updateSize);
            nUnknowns++;
            fprintf(stdout, "%d(X%d) ", id, nUnknowns); 
        }
    }
    fprintf(stdout, "\n");
}

void tcUpdateMessageHandler::HandleControlRequest(tcStream& stream, int connectionId)
{
	tcMultiplayerInterface* multiplayerInterface = tcMultiplayerInterface::Get();

	const tcPlayerStatus& playerInfo = multiplayerInterface->GetPlayerStatus(connectionId);

	const std::string& playerName = playerInfo.GetName();
	const unsigned char playerRank = playerInfo.IsCommander() ? 5 : 0; // use commander status instead for now
	const unsigned char playerAlliance = playerInfo.GetAlliance();

	if (!multiplayerInterface->IsServer())
	{
		fprintf(stderr, "Control request received at client\n");
		return;
	}

	tcSimState* simState = tcSimState::Get();
	wxASSERT(simState);

    fprintf(stdout, "<< Received obj control req msg, time %.1f: ", simState->GetTime());

	bool releaseControl;
	long id;
    
    while ((stream >> releaseControl).eof() == false)
    {
		stream >> id;

        // lookup obj
        if (tcGameObject* obj = simState->GetObject(id))
		{
			if (releaseControl)
			{
				 if (obj->GetController() == playerName)
				 {
					 obj->SetController("");
					 obj->SetAccessLevel(0);
				 }
				 else
				 {
					 fprintf(stdout, "N%d ", obj->mnID);
				 }
			}
			else if (obj->IsAvailable(playerAlliance, playerRank))
			{
				obj->SetController(playerName);
				obj->SetAccessLevel(playerRank);
				fprintf(stdout, "%d ", obj->mnID);
			}
			else
			{
				fprintf(stdout, "E%d ", obj->mnID);
			}
		}
		else
		{
			fprintf(stdout, "X%d ", obj->mnID);
		}
	}

	fprintf(stdout, "\n");
}

/**
* Handle CREATE update message
*/
void tcUpdateMessageHandler::HandleCreate(tcCreateStream& stream)
{
    tcSimState* simState = tcSimState::Get();
    wxASSERT(simState);
    tcDatabase* database = simState->mpDatabase; // convert database to singleton eventually

    // command stream update is located after each create update to initialize command params
	tcCommandStream& commandStream = stream.AsCommandStream();

    fprintf(stdout, "<< Received obj create msg, time %.1f: ", simState->GetTime());

    long id;
    
    while ((stream >> id).eof() == false)
    {
        std::string databaseClass;
        stream >> databaseClass;

        // lookup obj
        tcGameObject* obj = simState->GetObject(id);

        // update obj (re-create) if it exists, otherwise create object
        if (obj)
        {
            if (databaseClass == obj->mzClass.c_str())
			{
				*obj << stream;
				*obj << commandStream;
				fprintf(stdout, "%d(R) (%d)", id, obj->GetAlliance());
			}
			else
			{
                wxASSERT(false);
				fprintf(stderr, "Error - HandleCreate - obj %d already exists with different db class\n", id);
				fprintf(stdout, "\n");
				return;
			}
            
        }
		else
		{
			tcDatabaseObject* dbObj = database->GetObject(databaseClass);
			if (dbObj)
			{
				obj = simState->CreateGameObject(dbObj);
				*obj << stream;
				simState->AddPlatformWithKey(obj, id);
				fprintf(stdout, "%d (%d)", id, obj->GetAlliance());

				*obj << commandStream;
			}
			else
			{
                wxASSERT(false);
                fprintf(stderr, "Bad update, database entry %s not found\n", databaseClass.c_str());
				fprintf(stdout, "\n");
				return;
			}
		}

    }
    fprintf(stdout, "\n");
}

/**
* Handle CREATE_REQUEST message (server only)
*/
void tcUpdateMessageHandler::HandleCreateRequest(tcStream& stream, int connectionId)
{
    wxASSERT(isServer);

    tcPlayerStatus& pstatus = 
        tcMultiplayerInterface::Get()->GetPlayerStatus(connectionId);

    long id;

    fprintf(stdout, "<< Received create req for objs: ");

    while ((stream >> id).eof() == false)
    {
        pstatus.EraseEntry(id);
        fprintf(stdout, "%d ", id);
    }

    fprintf(stdout, "\n");
}

/**
* Handle DATABASE_INFO update message (client only)
* Normally this is sent once after scenario is loaded or client connects
*/
void tcUpdateMessageHandler::HandleDatabaseInfo(tcStream& stream)
{
    tcDatabase* database = tcDatabase::Get();
    wxASSERT(!isServer);

    size_t nInfo = 0;

    long databaseKey;

    std::vector<long> loadedKeys;

    while (((stream >> databaseKey).eof() == false) && (nInfo++ < 512))
    {
        // if first long is -1 then ignore this record and clear database (signals start of new db info)
        bool clearDatabase = (databaseKey == -1) && (nInfo == 1); 

        if (!clearDatabase)
        {
            std::string databaseClass;
            stream >> databaseClass;

            bool success = database->LoadRecordSqlForceKey(databaseClass.c_str(), databaseKey);
            if (success)
            {
                loadedKeys.push_back(databaseKey);
            }
        }
        else
        {
            database->ClearForNewScenario();
        }
    }

    for (size_t n=0; n<loadedKeys.size(); n++)
    {
        database->LoadRecordOtherTables(loadedKeys[n]); // load other tables associated with db objects, this needs to be done with LoadRecordSqlForceKey method
    }
}

/**
* Handle DESTROY update message (client only)
*/
void tcUpdateMessageHandler::HandleDestroy(tcStream& stream)
{
    tcSimState* simState = tcSimState::Get();
    wxASSERT(simState);

    fprintf(stdout, "<< Received destroy objs msg, time %.1f: ", simState->GetTime());

    long id;
    
    while ((stream >> id).eof() == false)
    {
        // lookup obj
        tcGameObject* obj = simState->GetObject(id);

        // update obj if it exists, otherwise create object
        if (obj)
        {
            simState->DeleteObject(id);
            fprintf(stdout, "%d ", id);
        }
        else
        {
            fprintf(stderr, "Error - HandleDestroy - obj %d not found\n", id);
            fprintf(stdout, "%d(ERR) ", id);
        }
    }
    fprintf(stdout, "\n");

}

/**
* Handle message from server to client updating goal status
*/
void tcUpdateMessageHandler::HandleGoalStatus(tcUpdateStream& stream)
{
	wxASSERT(tcSimState::Get()->IsMultiplayerClient());

	tcGoalTracker* goalTracker = tcGoalTracker::Get();

	goalTracker->operator<<(stream);
}


void tcUpdateMessageHandler::HandleScenarioInfo(tcUpdateStream& stream)
{
	tcSimState* simState = tcSimState::Get();
	tcSimPythonInterface* pythonInterface = tcSimPythonInterface::Get();
	tcScenarioInterface* scenarioInterface = pythonInterface->GetScenarioInterface();
	tcMapOverlay* overlay = scenarioInterface->GetMapOverlay();
	tcAllianceInfo* allianceInfo = tcAllianceInfo::Get();

	wxASSERT(simState->IsMultiplayerClient());

	// clear previous scenario info
	pythonInterface->SetMenuPlatform(-1);
	simState->Clear();

	std::string scenarioName;
	stream >> scenarioName;
	simState->SetScenarioName(scenarioName);

	std::string scenarioDescription;
	stream >> scenarioDescription;
	simState->SetScenarioDescription(scenarioDescription);

	simState->SetScenarioLoaded(true);

	double theater_lon;
	double theater_lat;
	stream >> theater_lon;
	stream >> theater_lat;
	if ((theater_lon != 0) && (theater_lat != 0))
	{
		scenarioInterface->ChangeMapTheater(theater_lon, theater_lat);
	}

	overlay->operator<<(stream);

    allianceInfo->operator<<(stream);
}

/**
* Handle SCRIPT_COMMANDS message (server only)
*/
void tcUpdateMessageHandler::HandleScriptCommands(tcStream& stream, int connectionId)
{
    wxASSERT(isServer);

    tcPlayerStatus& pstatus = 
        tcMultiplayerInterface::Get()->GetPlayerStatus(connectionId);

    fprintf(stdout, "<< Received script commands for connection %d\n", connectionId);

	stream.SetMetaString(pstatus.GetName());
	
	tcCommandStream& commandStream = (tcCommandStream&)stream;

	tcSimPythonInterface::Get()->operator<<(commandStream);

}

/**
* Handle SENSOR_UPDATE update message (client only)
*/
void tcUpdateMessageHandler::HandleSensorUpdate(tcUpdateStream& stream)
{
    tcSimState* simState = tcSimState::Get();
    wxASSERT(simState);

    long alliance;
    stream >> alliance;
    if ((alliance < 0) || (alliance > 255))
    {
        fprintf(stderr, "Error - HandleSensorUpdate - Alliance out of range (%d)\n",
            alliance);
        return;
    }
    fprintf(stdout, "<< Received sensor update msg, time %.1f, alliance %d\n", 
        simState->GetTime(), alliance);

    tcSensorMap* sensorMap = simState->GetSensorMap();
    tcAllianceSensorMap* allianceSensorMap = sensorMap->GetOrCreateMap(alliance);

    if (allianceSensorMap)
    {
        *allianceSensorMap << stream;
    }
    else
    {
        fprintf(stderr, "Error - HandleSensorUpdate - NULL alliance sensor map\n");
    }
}

/**
* Handle SOUND_EFFECT message (client only)
*/
void tcUpdateMessageHandler::HandleSoundEffect(tcStream& stream)
{
	wxASSERT(!isServer);

	long id;
	unsigned int nEffects = 0;
	while (((stream >> id).eof() == false) && (nEffects++ < 8))
    {
		std::string effect;

		stream >> effect;

		tcSound::Get()->PlayEffect(effect);
	}
    
}

/**
* Handle TEAM_STATUS message (client only)
*/
void tcUpdateMessageHandler::HandleTeamStatus(tcStream& stream)
{
//	tcMultiplayerInterface* multiplayerInterface = tcMultiplayerInterface::Get();

	// data structure with description of each team, first team is always "observers" (unassigned)
	std::vector<tcMPGameView::TeamInfo> teamList;

	size_t nTeams;
	stream >> nTeams;

	for (size_t n=0; n<nTeams; n++)
	{
		tcMPGameView::TeamInfo teamInfo;

		stream >> teamInfo.alliance;
		stream >> teamInfo.name;
		teamInfo.playerList.clear();

		size_t nPlayers;
		stream >> nPlayers;
		for (size_t k=0; k<nPlayers; k++)
		{
			tcMPGameView::PlayerInfo pi;
			
			stream >> pi.isCommander;
			stream >> pi.isReady;
            stream >> pi.gameSpeed;
			stream >> pi.name;
            stream >> pi.inGame; 
            stream >> pi.endGame;
            stream >> pi.surrenderGame;

			teamInfo.playerList.push_back(pi);
		}

		teamList.push_back(teamInfo);
	}


	if (mpGameView == 0)
	{
		wxASSERT(false);
		return;
	}

	mpGameView->SetTeamList(teamList);
}

/**
* Handle UPDATE update message (client only)
*/
void tcUpdateMessageHandler::HandleUpdate(tcUpdateStream& stream, int connectionId)
{
    //wxASSERT(false);
    //return; // DISABLED for current free version

    wxASSERT(!isServer);

    tcSimState* simState = tcSimState::Get();
    wxASSERT(simState);


    std::queue<long> missingIds;    // queue to keep track of ids that are missing locally


    // Load time info from stream
    tcSimState::Get()->LoadTimeFromStream(stream);


    //fprintf(stdout, "<< Received obj update msg, time %.1f: ", simState->GetTime());


    unsigned nUnknowns = 0;
    long id;
    
    while (((stream >> id).eof() == false) && (nUnknowns < 64))
    {
        unsigned int updateSize;
        stream >> updateSize;

        // lookup obj
        tcGameObject* obj = simState->GetObject(id);

        // update obj if it exists, otherwise create object
        if (obj)
        {
            *obj << stream;

			if (!obj->GetRecreate())
			{
				//fprintf(stdout, "%d ", id);
			}
			else
			{
				missingIds.push(id);
				obj->SetRecreate(false); // clear flag
				//fprintf(stdout, "%d(R) ", id);
			}
        }
        else
        {
            missingIds.push(id);
            nUnknowns++;
            //fprintf(stdout, "%d(X) ", id);
            stream.skip_read(updateSize);
        }
    }
    //fprintf(stdout, "\n");

    /**
    ** if any missing ids occurred, send a create request message back to the server
    **/
    if (!missingIds.empty())
    {
        // Init ack message
        tcStream createReqStream;
        tcUpdateMessageHandler::InitializeMessage(
            tcUpdateMessageHandler::CREATE_REQUEST, createReqStream);
        fprintf(stdout, ">> Sending create request msg, time %.1f, ids: ", simState->GetTime());
        while (!missingIds.empty())
        {
            long id = missingIds.front();
            missingIds.pop();
            tcUpdateMessageHandler::AddCreateRequest(id, createReqStream);
            fprintf(stdout, "%d ", id);
        }
        tcMultiplayerInterface::Get()->SendUpdateMessage(connectionId, createReqStream);
        fprintf(stdout, "\n");
    }

    entityUpdateReceived = true;
}



void tcUpdateMessageHandler::UpdateTeamList(std::vector<tcMPGameView::TeamInfo>& teamList)
{
	teamList.clear();

	tcMultiplayerInterface* multiplayerInterface = tcMultiplayerInterface::Get();
	tcAllianceInfo* allianceInfo = tcAllianceInfo::Get();
	const std::vector<unsigned char>& allianceList = allianceInfo->GetAllianceList();

	// add base info for observers team
	tcMPGameView::TeamInfo observers;
	observers.alliance = 0;
	observers.name = "Observers";
	observers.playerList.clear();
	teamList.push_back(observers);

	// add each alliance reported by allianceInfo
	for (size_t n=0; n<allianceList.size(); n++)
	{
		tcMPGameView::TeamInfo teamInfo;
		teamInfo.alliance = allianceList[n];
		teamInfo.name = allianceInfo->GetAllianceName(allianceList[n]);
		teamInfo.playerList.clear();

		teamList.push_back(teamInfo);
	}


	// loop through connected players and add info to playerList for relevant team
	const std::list<int>& connectionList = multiplayerInterface->GetConnectionList();
    std::list<int>::const_iterator iter = connectionList.begin();

    for( ; iter != connectionList.end(); ++iter)
    {
		tcPlayerStatus& playerInfo = multiplayerInterface->GetPlayerStatus(*iter);
		const std::string& nameWithRank = playerInfo.GetNameWithRank();
		unsigned char alliance = playerInfo.GetAlliance();
		
		bool searching = true;
		for (size_t n=0; (n<teamList.size())&&searching; n++)
		{
			if (teamList[n].alliance == alliance)
			{
				tcMPGameView::PlayerInfo pi;
				pi.isCommander = playerInfo.IsCommander();
				pi.isReady = playerInfo.IsReady();
                pi.gameSpeed = playerInfo.GetGameSpeed();
				pi.name = nameWithRank;
                pi.inGame = playerInfo.IsInGame();
                pi.endGame = playerInfo.WantsGameEnd();
                pi.surrenderGame = playerInfo.WantsSurrender();

				teamList[n].playerList.push_back(pi);
				searching = false;
			}
		}

    }
}



tcUpdateMessageHandler::tcUpdateMessageHandler()
{
}

tcUpdateMessageHandler::~tcUpdateMessageHandler()
{
}

END_NAMESPACE

