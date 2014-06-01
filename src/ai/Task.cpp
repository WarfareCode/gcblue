/**
**  @file Task.cpp
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

#include "ai/Task.h"
#include "scriptinterface/tcPlatformInterface.h"
#include "tcGameStream.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif 

using namespace ai;
using scriptinterface::tcPlatformInterface;

/**
* Read from stream
*/
tcGameStream& Task::operator<<(tcGameStream& stream)
{
    stream >> lastUpdateTime;
    stream >> updateInterval;
    stream >> isRunning;

    // remainder handled through contructor at higher level

    return stream;
}

/**
* Write to stream
*/
tcGameStream& Task::operator>>(tcGameStream& stream)
{
    stream << lastUpdateTime;
    stream << updateInterval;
    stream << isRunning;

    return stream;
}



void Task::EndTask()
{
    GetPlatformInterface().DeleteTask(taskName);
}

/**
* Call at the end of every update
*/
void Task::FinishUpdate(double t)
{
    lastUpdateTime = t;
}

int Task::GetAttributes() const
{
	return attributes;
}

tcPlatformInterface Task::GetPlatformInterface()
{
    return tcPlatformInterface(platform);
}

const std::string& Task::GetTaskName() const
{
    return taskName;
}

bool Task::IsHidden() const
{
	return (attributes & HIDDEN) != 0;
}

bool Task::IsPermanent() const
{
	return (attributes & PERMANENT) != 0;
}

bool Task::IsReadyForUpdate(double t) const
{
     return ((t - lastUpdateTime) >= updateInterval);
}

bool Task::IsRunning() const
{
    return isRunning;
}

void Task::SetAttributes(int attributes_)
{
	attributes = attributes_;
}

void Task::SetRunState(bool state)
{
    isRunning = state;
}


void Task::SetUpdateInterval(float interval)
{
    updateInterval = interval;
}

void Task::Update(double t)
{
}

Task::Task(tcPlatformObject* platform_, Blackboard* bb, 
        long id_, double priority_, int attributes_, const std::string& taskName_)
: BlackboardInterface(bb, id_, priority_),
  platform(platform_),
  taskName(taskName_),
  attributes(attributes_),
  lastUpdateTime(0),
  updateInterval(4.0f),
  isRunning(true)
{
    wxASSERT(platform);
}



Task::~Task()
{
}



