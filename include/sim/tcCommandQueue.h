/**
**  @file tcCommandQueue.h
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


#ifndef _COMMANDQUEUE_H_
#define _COMMANDQUEUE_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "commandlist.h"

class tcGameStream;

/**
* Converted into singleton class
* Holdover from old code, needs cleaning
*/
class tcCommandQueue
{
public:
    enum {MAX_QUEUED_COMMANDS = 32};
    tsCommandInfo maCommand[MAX_QUEUED_COMMANDS];
    unsigned int mnCount;

    void AddCommand(const tsCommandInfo& newcmd);

    void AddCommand(teGameCommand aeCmd, float afData, long anData, int anData2 = 0);
    
    void AddCommand(const char *azCommand, int param = -1);
 
    void AddPythonCommand(const char *azCommand, int param = -1);
   
    void AddPythonCommand(const char *azCommand, const std::string& textParam);

	void AddPythonCommandGeneral(const std::string& command, const std::string& args, const std::vector<long>& platformID);

	void GetUserInput(const char *azCallback, const char *azUserInput, int param, const std::string& textParam);

    void GetUserInputForID(const char *azCallback, const char *azUserInput,
        std::vector<long>& platformID, int param = -1);

    void GetUserInputForID(const char *azCallback, const char *azUserInput,
        std::vector<long>& platformID, const std::string& args);

    void AddPythonCallback(const char *azCallback, const char *azUserInput, int param = -1);
    
    void AddPythonCallbackForID(const char *azCallback, const char *azUserInput, 
		std::vector<long>& platformID, int param, const std::string& textParam);

    void DisplayInfoMessage(const char *azString);

    bool GetCommand(tsCommandInfo& newcmd);

    tcGameStream& operator>>(tcGameStream& stream);
    tcGameStream& operator<<(tcGameStream& stream);


    static tcCommandQueue* Get(); ///< singleton accessor

private:

    tcCommandQueue();
    ~tcCommandQueue();
};





#endif

