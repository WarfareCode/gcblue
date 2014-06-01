/**
**  @file BlackboardItem.cpp
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

#include "ai/BlackboardItem.h"
#include <boost/python.hpp>
#include "tcGameStream.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif 

using namespace ai;
using namespace boost::python;

bool BlackboardItem::pythonInitialized = false;

/**
* static method that should be called once to expose class
* to Python
*/
void BlackboardItem::InitPython()
{
    if (pythonInitialized) return;
    
    class_<BlackboardItem>("BlackboardItem") 
        .def_readonly("author", &BlackboardItem::author)
        .def_readonly("priority", &BlackboardItem::priority)
        .def_readonly("message", &BlackboardItem::message)
        
        .def("Valid", &BlackboardItem::Valid)
        ;    
    
    pythonInitialized = true;
}

/**
* Read from stream
*/
tcGameStream& BlackboardItem::operator<<(tcGameStream& stream)
{
    stream >> author;
    stream >> priority;
    stream >> message;

    return stream;
}

/**
* Write to stream
*/
tcGameStream& BlackboardItem::operator>>(tcGameStream& stream)
{
    stream << author;
    stream << priority;
    stream << message;

    return stream;
}

bool BlackboardItem::Valid() const
{
    return author != -1;
}

BlackboardItem& BlackboardItem::operator=(const BlackboardItem& rhs)
{
    author = rhs.author;
    priority = rhs.priority;
    message = rhs.message;

    return *this;
}

BlackboardItem::BlackboardItem(const BlackboardItem& src)
: author(src.author),
  priority(src.priority),
  message(src.message)
{
}

BlackboardItem::BlackboardItem(long author_, double priority_, const std::string& message_)
: author(author_),
  priority(priority_),
  message(message_)
{
}

BlackboardItem::BlackboardItem()
: author(-1),
  priority(-1.0),
  message("")
{
}

BlackboardItem::~BlackboardItem()
{
}

