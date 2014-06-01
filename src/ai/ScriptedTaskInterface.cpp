/**
**  @file ScriptedTaskInterface.cpp
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

#include "ai/ScriptedTaskInterface.h"
#include "ai/BlackboardInterface.h"
#include "ai/ScriptedTask.h"
#include "scriptinterface/tcPlatformInterface.h"
#include <boost/python.hpp>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif 


using namespace ai;
using namespace boost::python;
using scriptinterface::tcPlatformInterface;

bool ScriptedTaskInterface::pythonInitialized = false;

/**
* static method that should be called once to expose class
* to Python
*/
void ScriptedTaskInterface::InitPython()
{
    if (pythonInitialized) return;
    
    class_<ScriptedTaskInterface>("ScriptedTaskInterface") 
         .def("EndTask", &ScriptedTaskInterface::EndTask)
         .def("GetBlackboardInterface", &ScriptedTaskInterface::GetBlackboardInterface)
         .def("GetPlatformInterface", &ScriptedTaskInterface::GetPlatformInterface)
         .def("SetUpdateInterval", &ScriptedTaskInterface::SetUpdateInterval)
         .def("SetTaskAttributes", &ScriptedTaskInterface::SetTaskAttributes)
         .def("GetMemoryText", &ScriptedTaskInterface::GetMemoryText)
         .def("SetMemoryText", &ScriptedTaskInterface::SetMemoryText)
         .def("GetMemoryValue", &ScriptedTaskInterface::GetMemoryValue)
         .def("SetMemoryValue", &ScriptedTaskInterface::SetMemoryValue)
         ;  
         
    pythonInitialized = false;  
}

/**
* Call to safely end (remove) this task
*/
void ScriptedTaskInterface::EndTask()
{    
    wxASSERT(task);
    if (task->IsPermanent())
    {
        task->SetAttributes(task->GetAttributes() & (~Task::PERMANENT));
    }

    task->EndTask();
}

BlackboardInterface ScriptedTaskInterface::GetBlackboardInterface()
{
    wxASSERT(task);
    return task->GetBlackboardInterface();    
}

const std::string ScriptedTaskInterface::GetMemoryText(const std::string& key)
{
    wxASSERT(task);    
    return task->GetMemoryText(key);
}

double ScriptedTaskInterface::GetMemoryValue(int key)
{
    wxASSERT(task);    
    return task->GetMemoryValue(key);
}


tcPlatformInterface ScriptedTaskInterface::GetPlatformInterface()
{
    wxASSERT(task);
    return task->GetPlatformInterface();
}


void ScriptedTaskInterface::SetMemoryText(const std::string& key, const std::string& text)
{
    wxASSERT(task);    
    task->SetMemoryText(key, text);
}


void ScriptedTaskInterface::SetMemoryValue(int key, double value)
{
    wxASSERT(task);    
    return task->SetMemoryValue(key, value);
}

void ScriptedTaskInterface::SetTask(ScriptedTask* scriptedTask)
{
    task = scriptedTask;
    
    wxASSERT(task);
}

void ScriptedTaskInterface::SetTaskAttributes(int attributes_)
{
    task->SetAttributes(attributes_);
}


void ScriptedTaskInterface::SetUpdateInterval(float interval)
{
    wxASSERT(task);
    
    if (interval < 0.1f) interval = 0.1f; // 10 Hz maximum
    task->SetUpdateInterval(interval);
}

/**
* Default constructor is defined for Python, SetTask needs to be
* called after this constructor
*/
ScriptedTaskInterface::ScriptedTaskInterface()
: task(0)
{
    if (!pythonInitialized) InitPython();   
}

ScriptedTaskInterface::ScriptedTaskInterface(ScriptedTask* scriptedTask)
: task(scriptedTask)
{
    wxASSERT(task);
    
    if (!pythonInitialized) InitPython();
    
}



ScriptedTaskInterface::~ScriptedTaskInterface()
{
}



