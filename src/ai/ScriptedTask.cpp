/**
**  @file ScriptedTask.cpp
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

#include "ai/ScriptedTask.h"
#include "scriptinterface/tcSimPythonInterface.h"
#include "tcGameStream.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif 

using namespace ai;
using scriptinterface::tcSimPythonInterface;


/**
* Read from stream
*/
tcGameStream& ScriptedTask::operator<<(tcGameStream& stream)
{
    Task::operator<<(stream);

    stream >> commandString;

    {
        textMemory.clear();
        unsigned int nTextMemory;
        stream >> nTextMemory;
        for (unsigned int n=0; n<nTextMemory; n++)
        {
            std::string s1;
            std::string s2;

            stream >> s1;
            stream >> s2;
            textMemory[s1] = s2;
        }

        stream.ReadCheckValue(8961);
    }
 
    {
        numberMemory.clear();
        unsigned int nNumberMemory;
        stream >> nNumberMemory;
        for (unsigned int n=0; n<nNumberMemory; n++)
        {
            int val_int;
            double val_double;
            stream >> val_int;
            stream >> val_double;

            numberMemory[val_int] = val_double;
        }

        stream.ReadCheckValue(1530);
    }

    return stream;
}

/**
* Write to stream
*/
tcGameStream& ScriptedTask::operator>>(tcGameStream& stream)
{
    Task::operator>>(stream);

    stream << commandString;

    {
        unsigned int nTextMemory = textMemory.size();
        stream << nTextMemory;
        for (std::map<std::string, std::string>::iterator iter = textMemory.begin();
            iter != textMemory.end(); ++iter)
        {
            stream << iter->first;
            stream << iter->second;
        }

        stream.WriteCheckValue(8961);
    }

    {
        unsigned int nNumberMemory = numberMemory.size();
        stream << nNumberMemory;
        for (std::map<int, double>::iterator iter = numberMemory.begin();
            iter != numberMemory.end(); ++iter)
        {
            stream << (int)iter->first;
            stream << (double)iter->second;
        }

        stream.WriteCheckValue(1530);
    }

    return stream; 
}



/**
* @return "" if no key exists
*/
const std::string& ScriptedTask::GetMemoryText(const std::string& key)
{
    // returned if key not found 
    static const std::string emptyString(""); 
     
    std::map<std::string, std::string>::const_iterator iter =
        textMemory.find(key);
    
    if (iter != textMemory.end())
    {
        return iter->second;
    }
    else
    {
        return emptyString;
    }
}

void ScriptedTask::SetMemoryText(const std::string& key, const std::string& text)
{
    textMemory[key] = text;
}
    
/**
* @return 0 if no key exists
*/
double ScriptedTask::GetMemoryValue(int key)
{
    std::map<int, double>::const_iterator iter =
        numberMemory.find(key);
    
    if (iter != numberMemory.end())
    {
        return iter->second;
    }
    else
    {
        return 0;
    }    
}

void ScriptedTask::SetMemoryValue(int key, double value)
{
    numberMemory[key] = value;
}



const char* ScriptedTask::GetCommandString()
{
    if (commandString.size())
    {
        return commandString.c_str();
    }
    else
    {
        commandString = wxString::Format("AI.%s(TaskInterface)\n", taskName.c_str());
        return commandString.c_str();
    }
}

void ScriptedTask::Update(double t)
{
     if (IsReadyForUpdate(t))
     {
         bool success = tcSimPythonInterface::Get()->CallTaskScript(this, GetCommandString());

         FinishUpdate(t);

         if (!success)
         {
             fprintf(stderr, "Deleting task that errored (%s)\n", GetTaskName().c_str());
             EndTask();
         }
     }
}

ScriptedTask::ScriptedTask(tcPlatformObject* platform_, Blackboard* bb, 
        long id_, double priority_, int attributes_, const std::string& scriptName)
: Task(platform_, bb, id_, priority_, attributes_, scriptName)
{

}



ScriptedTask::~ScriptedTask()
{
}



