/**
**  @file commandlist.h
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


#ifndef _COMMANDLIST_H_
#define _COMMANDLIST_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include <string>
#include <vector>

/**
*
*/
enum teGameCommand 
{
   GC_NULL,
   GC_QUIT,
   GC_QUITTODESKTOP,
   GC_RESETMAP,
   GC_ADDRANDPLAT,
   GC_SAVESCEN,
   GC_LOADSCEN,
   GC_TOGGLEEDIT,
   GC_DISPLAYMESSAGE,
   GC_TEXTCOMMAND,
   GC_SHOWBRIEFING,
   GC_SHOWMISSIONSTATUS,
   GC_SAVEGAME,
   PC_GETNEWHEADING,
   PC_CHANGEHEADING,
   PC_HALFSPEED,
   PC_FULLSPEED,
   PC_GETNEWLOCATION,
   PC_GETNEWTARGET,
   PC_GETLAUNCHERTARGET,
   PC_DESIGNATETARGET,
   PC_GETDATUM,
   PC_GETLAUNCHERDATUM,
   PC_DATUMSET,
   PC_LAUNCH,
   PC_DELETE
};

/**
*
*/
enum CommandType
{
	GAME_COMMAND = 0,
	PYTHON_CALLBACK = 1, // replaces mbUsePython && mbCallback
	PYTHON_USERINPUT = 2, // replaces mbUsePython && mbGetUserInput
	PYTHON_COMMAND_TEXT = 3, ///< command with single text parameter
	PYTHON_COMMAND_GENERAL = 4 ///< command with general parameter string
};

/**
*
*/
struct tsCommandInfo 
{
    enum {MZ_STRING_SIZE = 256, MZ_USER_INPUT_SIZE = 64};
    CommandType commandType;
    teGameCommand meCmd;
    float mfData;
    long mnData;
    int mnData2;
    char mzString[MZ_STRING_SIZE];
    char mzUserInput[MZ_USER_INPUT_SIZE]; ///< Heading, Target, Datum
    std::string textParam; ///< string parameter for python
    std::vector<long> platformID; ///< -1 or empty to use current hooked
};



















#endif