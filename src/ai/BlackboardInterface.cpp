/**
**  @file BlackboardInterface.cpp
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

#include "ai/BlackboardInterface.h"
#include "ai/Blackboard.h"
#include "ai/BlackboardItem.h"
#include <boost/python.hpp>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif 

using namespace ai;
using namespace boost::python;

bool BlackboardInterface::pythonInitialized = false;

/**
* static method that should be called once to expose class
* to Python
*/
void BlackboardInterface::InitPython()
{
    if (pythonInitialized) return;
    
    class_<BlackboardInterface>("BlackboardInterface") 
        .def_readonly("author", &BlackboardInterface::author)
        .def_readonly("priority", &BlackboardInterface::priority)
        .def("Erase", &BlackboardInterface::Erase)
        .def("KeyExists", &BlackboardInterface::KeyExists)
        .def("Read", &BlackboardInterface::Read) 
        .def("ReadAuthor", &BlackboardInterface::ReadAuthor)      
        .def("ReadMessage", &BlackboardInterface::ReadMessage)         
        .def("ReadPriority", &BlackboardInterface::ReadPriority)
        .def("Write", &BlackboardInterface::Write)
		.def("WriteGlobal", &BlackboardInterface::WriteGlobal)
        ;    
    
    pythonInitialized = true;
    
    BlackboardItem::InitPython();
}

/**
* Read from stream
*/
tcGameStream& BlackboardInterface::operator<<(tcGameStream& stream)
{
    return stream;
}

/**
* Write to stream
*/
tcGameStream& BlackboardInterface::operator>>(tcGameStream& stream)
{
    // everything should be handled with contructor for this object
    return stream;
}

/**
* Used to create a BlackboardInterface object in Python
*/
BlackboardInterface BlackboardInterface::GetBlackboardInterface()
{
    return BlackboardInterface(*this);
}

long BlackboardInterface::GetAuthor() const
{
    return author;
}

double BlackboardInterface::GetPriority() const
{
    return priority;
}


void BlackboardInterface::SetPriority(double priority_)
{
    priority = priority_;
}

void BlackboardInterface::Erase(const std::string& key)
{
    board->Erase(key, priority);
}

bool BlackboardInterface::KeyExists(const std::string& key) const
{
    return board->KeyExists(key);
}

BlackboardItem BlackboardInterface::Read(const std::string& key)
{
    return board->Read(key);
}

long BlackboardInterface::ReadAuthor(const std::string& key)
{
    return board->ReadAuthor(key);
}

const std::string BlackboardInterface::ReadMessage(const std::string& key)
{
    return board->ReadMessage(key);
}
    

double BlackboardInterface::ReadPriority(const std::string& key)
{
    return board->ReadPriority(key);
}

/**
* @return true if write successful, false if blocked
*/
bool BlackboardInterface::Write(const std::string& key, const std::string& message)
{
    return board->Write(key, author, priority, message);
}

/**
* Write overriding author to use 0 for global message, use for messages that should persist after
* task ends
* @return true if write successful, false if blocked
*/
bool BlackboardInterface::WriteGlobal(const std::string& key, const std::string& message)
{
    return board->Write(key, 0, priority, message);
}



/**
* Default constructor should never be used
*/
BlackboardInterface::BlackboardInterface()
: board(0),
  author(-1),
  priority(0)
{
    wxASSERT(false);
    
    if (!pythonInitialized) InitPython();
}

BlackboardInterface::BlackboardInterface(const BlackboardInterface& source)
: board(source.board),
  author(source.author),
  priority(source.priority)
{
    wxASSERT(board); 
    
    if (!pythonInitialized) InitPython();
}

BlackboardInterface::BlackboardInterface(Blackboard* bb, 
        long author_, double priority_)
: board(bb),
  author(author_),
  priority(priority_)
{
    wxASSERT(board);
    
    if (!pythonInitialized) InitPython();
}



BlackboardInterface::~BlackboardInterface()
{
}



