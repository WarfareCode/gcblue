/**
**  @file tcCommandQueue.cpp
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


#include "stdwx.h"

#ifndef WX_PRECOMP
#include "wx/wx.h" 
#endif

#include "tcCommandQueue.h"
#include "tcGameStream.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


/**
*
*/
tcCommandQueue* tcCommandQueue::Get()
{
    static tcCommandQueue instance;

    return &instance;
}

/**
* Save
*/
tcGameStream& tcCommandQueue::operator>>(tcGameStream& stream)
{
    stream << mnCount;

    for (unsigned int k=0; k<mnCount; k++)
    {
        int commandType = (int)maCommand[k].commandType;
        stream << commandType;

        int cmd = (int)maCommand[k].meCmd;
        stream << cmd;

        stream << maCommand[k].mfData;
        stream << maCommand[k].mnData;
        stream << maCommand[k].mnData2;

        for (int n=0; n<tsCommandInfo::MZ_STRING_SIZE; n++)
        {
            stream << maCommand[k].mzString[n];
        }

        for (int n=0; n<tsCommandInfo::MZ_USER_INPUT_SIZE; n++)
        {
            stream << maCommand[k].mzUserInput[n];
        }

        unsigned int nId = (unsigned int)maCommand[k].platformID.size();
        stream << nId;
        for (unsigned int n=0; n<nId; n++)
        {
            stream << maCommand[k].platformID[n];
        }

        stream << maCommand[k].textParam;
    }

    stream.WriteCheckValue(8332);

    return stream;
}

/**
* Load
*/
tcGameStream& tcCommandQueue::operator<<(tcGameStream& stream)
{
    stream >> mnCount;

    for (unsigned int k=0; k<mnCount; k++)
    {
        int commandType;
        stream >> commandType;
        maCommand[k].commandType = (CommandType)commandType;

        int cmd;
        stream >> cmd;
        maCommand[k].meCmd =(teGameCommand)cmd;


        stream >> maCommand[k].mfData;
        stream >> maCommand[k].mnData;
        stream >> maCommand[k].mnData2;

        for (int n=0; n<tsCommandInfo::MZ_STRING_SIZE; n++)
        {
            stream >> maCommand[k].mzString[n];
        }

        for (int n=0; n<tsCommandInfo::MZ_USER_INPUT_SIZE; n++)
        {
            stream >> maCommand[k].mzUserInput[n];
        }

        maCommand[k].platformID.clear();
        unsigned int nId;
        stream >> nId;
        for (unsigned int n=0; n<nId; n++)
        {
            long val;
            stream >> val;
            maCommand[k].platformID.push_back(val);
        }

        stream >> maCommand[k].textParam;
    }

    stream.ReadCheckValue(8332);

    return stream;
}

/**
* 
*/
void tcCommandQueue::AddCommand(const tsCommandInfo& newcmd) 
{
    if (mnCount < MAX_QUEUED_COMMANDS)
    {
        maCommand[mnCount++] = newcmd;
    }
}

/**
* Adds game command (old style command from enumerated list)
*/
void tcCommandQueue::AddCommand(teGameCommand aeCmd, float afData, long anData, int anData2) 
{
    tsCommandInfo newcmd;

	newcmd.commandType = GAME_COMMAND;
    newcmd.meCmd = aeCmd;
    newcmd.mfData = afData;
    newcmd.mnData = anData;
    newcmd.mnData2 = anData2;
    newcmd.platformID.clear();
    if (mnCount < MAX_QUEUED_COMMANDS) 
    {
        maCommand[mnCount++] = newcmd;
    }
}

/**
* For old style string commands
*/ 
void tcCommandQueue::AddCommand(const char *azCommand, int param) 
{
    tsCommandInfo newcmd;

	newcmd.commandType = GAME_COMMAND;
    newcmd.meCmd = GC_TEXTCOMMAND;
    newcmd.mnData = param;
    strcpy(newcmd.mzString , azCommand);
    strcpy(newcmd.mzUserInput, "");
    newcmd.platformID.clear();
    if (mnCount < MAX_QUEUED_COMMANDS) 
    {
        maCommand[mnCount++] = newcmd;
    }
}
/**
* Version without user input and callback
*/
void tcCommandQueue::AddPythonCommand(const char *azCommand, int param) 
{
    tsCommandInfo newcmd;

	newcmd.commandType = PYTHON_COMMAND_TEXT;
    newcmd.meCmd = (teGameCommand)0;
    newcmd.mnData = param; // int param
    newcmd.textParam = ""; // text param
    strcpy(newcmd.mzString , azCommand);
    strcpy(newcmd.mzUserInput, "");
    newcmd.platformID.clear();
    if (mnCount < MAX_QUEUED_COMMANDS)
    {
        maCommand[mnCount++] = newcmd;
    }
}

/**
* Version without user input and callback
*/
void tcCommandQueue::AddPythonCommand(const char *azCommand, const std::string& textParam) 
{
    tsCommandInfo newcmd;

	newcmd.commandType = PYTHON_COMMAND_TEXT;
    newcmd.meCmd = (teGameCommand)0;
    newcmd.mnData = -1; // int param
    newcmd.textParam = textParam;
    strcpy(newcmd.mzString , azCommand);
    strcpy(newcmd.mzUserInput, "");
    newcmd.platformID.clear();
    if (mnCount < MAX_QUEUED_COMMANDS) 
    {
        maCommand[mnCount++] = newcmd;
    }
}

void tcCommandQueue::AddPythonCommandGeneral(const std::string& command, const std::string& args, 
											 const std::vector<long>& platformID)
{
    tsCommandInfo newcmd;

	newcmd.commandType = PYTHON_COMMAND_GENERAL;
    newcmd.meCmd = (teGameCommand)0;
    newcmd.mnData = -1; // int param
    
	strcpy(newcmd.mzString , command.c_str());
    newcmd.textParam = args;
    strcpy(newcmd.mzUserInput, "");
    newcmd.platformID = platformID;
    if (mnCount < MAX_QUEUED_COMMANDS) 
    {
        maCommand[mnCount++] = newcmd;
    }
}


/**
* GetUserInput is called to add a command to get user input data.
* Once the user input is complete, the callback function is called though
* AddPythonCallback. Data that describes the user input is passed to the 
* callback function along with an optional parameter. 
*/
void tcCommandQueue::GetUserInput(const char *azCallback, const char *azUserInput, 
								  int param, const std::string& textParam) 
{
    tsCommandInfo newcmd;

	newcmd.commandType = PYTHON_USERINPUT;
    newcmd.meCmd = (teGameCommand)0;
    newcmd.mnData = param;
    newcmd.textParam = textParam;
    strcpy(newcmd.mzString , azCallback);
    strcpy(newcmd.mzUserInput, azUserInput);
    newcmd.platformID.clear();
    if (mnCount < MAX_QUEUED_COMMANDS) 
    {
        maCommand[mnCount++] = newcmd;
    }
}

/**
* This version accepts a platformID parameter vs. defaulting to hooked platform
*
* GetUserInput is called to add a command to get user input data.
* Once the user input is complete, the callback function is called though
* AddPythonCallback. Data that describes the user input is passed to the 
* callback function along with an optional parameter. 
*/
void tcCommandQueue::GetUserInputForID(const char *azCallback, const char *azUserInput,
                       std::vector<long>& platformID, int param)
{
    tsCommandInfo newcmd;

	newcmd.commandType = PYTHON_USERINPUT;
    newcmd.meCmd = (teGameCommand)0;
    newcmd.mnData = param;
    newcmd.textParam = "";
    strcpy(newcmd.mzString , azCallback);
    strcpy(newcmd.mzUserInput, azUserInput);
    newcmd.platformID = platformID;
    if (mnCount < MAX_QUEUED_COMMANDS) 
    {
        maCommand[mnCount++] = newcmd;
    }
}

/**
* Version with text arguments instead of just one integer parameter
*/
void tcCommandQueue::GetUserInputForID(const char *azCallback, const char *azUserInput,
                                       std::vector<long>& platformID, const std::string& args)
{
    tsCommandInfo newcmd;

	newcmd.commandType = PYTHON_USERINPUT;
    newcmd.meCmd = (teGameCommand)0;
    newcmd.mnData = -1;
    newcmd.textParam = args;
    strcpy(newcmd.mzString , azCallback);
    strcpy(newcmd.mzUserInput, azUserInput);
    newcmd.platformID = platformID;
    if (mnCount < MAX_QUEUED_COMMANDS) 
    {
        maCommand[mnCount++] = newcmd;
    }
}


/**
* version for callback
* Always applies to current hooked platform
*/
void tcCommandQueue::AddPythonCallback(const char *azCallback, const char *azUserInput, 
                                       int param) 
{
    tsCommandInfo newcmd;

	newcmd.commandType = PYTHON_CALLBACK;
    newcmd.meCmd = (teGameCommand)0;
    newcmd.mnData = param;
    newcmd.textParam = "";
    strcpy(newcmd.mzString , azCallback);
    strcpy(newcmd.mzUserInput, azUserInput);
    newcmd.platformID.clear();
    if (mnCount < MAX_QUEUED_COMMANDS) 
    {
        maCommand[mnCount++] = newcmd;
    }
}

/**
* Version for specific platform ID vs. defaulting to hooked platform
*/
void tcCommandQueue::AddPythonCallbackForID(const char *azCallback, const char *azUserInput, 
											std::vector<long>& platformID, int param, const std::string& textParam)
{
    tsCommandInfo newcmd;

	newcmd.commandType = PYTHON_CALLBACK;
    newcmd.meCmd = (teGameCommand)0;
    newcmd.mnData = param;
    newcmd.textParam = textParam;
    strcpy(newcmd.mzString , azCallback);
    strcpy(newcmd.mzUserInput, azUserInput);
    newcmd.platformID = platformID;
    if (mnCount < MAX_QUEUED_COMMANDS) 
    {
        maCommand[mnCount++] = newcmd;
    }
}


/**
* For sending messages to info console
*/
void tcCommandQueue::DisplayInfoMessage(const char *azString)
{
    tsCommandInfo newcmd;

	newcmd.commandType = GAME_COMMAND;
    newcmd.meCmd = GC_DISPLAYMESSAGE;
    strcpy(newcmd.mzString, azString);
    newcmd.platformID.clear();
    if (mnCount < MAX_QUEUED_COMMANDS) 
    {
        maCommand[mnCount++] = newcmd;
    }
}

/**
*
*/
bool tcCommandQueue::GetCommand(tsCommandInfo& newcmd) 
{
    if (mnCount == 0)
    {
        newcmd.meCmd = GC_NULL;
        return false;
    }
    else 
    {
        newcmd = maCommand[--mnCount];
        return true;
    }
}

/**
*
*/
tcCommandQueue::tcCommandQueue() 
{
    mnCount = 0;
}

/**
*
*/
tcCommandQueue::~tcCommandQueue() 
{
}


