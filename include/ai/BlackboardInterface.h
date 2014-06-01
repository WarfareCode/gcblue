/**
**  @file BlackboardInterface.h
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

#ifndef _BLACKBOARDINTERFACE_H_
#define _BLACKBOARDINTERFACE_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include <map>
#include <string>
#include <vector>

class tcGameStream;

namespace ai
{

class Blackboard;
class BlackboardItem;

/**
* Class to interface with blackboard. Handles priority and
* author aspects.
*/
class BlackboardInterface
{
public:
    void SetPriority(double priority_);

    BlackboardInterface GetBlackboardInterface();
    long GetAuthor() const;
    double GetPriority() const;

    /// blackboard interface
    void Erase(const std::string& key);
    bool KeyExists(const std::string& key) const;
    BlackboardItem Read(const std::string& key);
    long ReadAuthor(const std::string& key);
    const std::string ReadMessage(const std::string& key);
    double ReadPriority(const std::string& key);
    bool Write(const std::string& key, const std::string& message);
    bool WriteGlobal(const std::string& key, const std::string& message);

    virtual tcGameStream& operator<<(tcGameStream& stream);
	virtual tcGameStream& operator>>(tcGameStream& stream);

    BlackboardInterface();
    BlackboardInterface(const BlackboardInterface& source);
    BlackboardInterface(Blackboard* bb, long author_, 
        double priority_);
    ~BlackboardInterface();
    
protected:
    Blackboard* const board;
    const long author;
    double priority;
    
    static bool pythonInitialized;
    static void InitPython();
};



}

#endif