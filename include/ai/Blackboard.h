/**
**  @file Blackboard.h
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

#ifndef _BLACKBOARD_H_
#define _BLACKBOARD_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include <map>
#include <string>

class tcStream;
class tcCommandStream;
class tcGameStream;

namespace scriptinterface
{
	class tcScenarioLogger;
}

namespace ai
{

    class BlackboardItem;

    class Blackboard
    {
    public:
		static bool GetMultiplayerClientMode();
		static void SetMultiplayerClientMode(bool state);

        void Erase(const std::string& key, double priority);
        void EraseAll(); 
        void EraseAllFromAuthor(long author);
        
        bool KeyExists(const std::string& key) const;
        BlackboardItem Read(const std::string& key);
        long ReadAuthor(const std::string& key);
        const std::string ReadMessage(const std::string& key) const;        
        double ReadPriority(const std::string& key);
		void SaveToPython(scriptinterface::tcScenarioLogger& logger);
        bool Write(const std::string& key, const BlackboardItem& item);
        bool Write(const std::string& key, long author, double priority, const std::string& message);

		tcCommandStream& operator<<(tcCommandStream& stream);
		tcCommandStream& operator>>(tcCommandStream& stream);

        tcGameStream& operator<<(tcGameStream& stream);
		tcGameStream& operator>>(tcGameStream& stream);
        
        void ClearNewCommand();
		bool HasNewCommand() const;

		Blackboard();
        ~Blackboard();
    private:
        std::map<std::string, BlackboardItem> content;

		std::map<std::string, BlackboardItem> clientContent; // for multiplayer client
		bool hasNewCommand; ///< for multiplayer, true if task or bb state has been changed
		static bool multiplayerClientMode; ///< true to use multiplayer client mode
    };
}

#endif