/**
**  @file Blackboard.cpp
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

#include "ai/Blackboard.h"
#include "ai/BlackboardItem.h"
#include "tcScenarioLogger.h"
#include "common/tcStream.h"
#include "common/tcObjStream.h"
#include "common/tcGameStream.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif 

using namespace ai;


bool Blackboard::multiplayerClientMode = false;

bool Blackboard::GetMultiplayerClientMode()
{
	return multiplayerClientMode;
}

void Blackboard::SetMultiplayerClientMode(bool state)
{
	multiplayerClientMode = state;
}



/**
* Loads state from command stream
*/
tcCommandStream& Blackboard::operator<<(tcCommandStream& stream)
{
	unsigned char nItems;
	stream >> nItems;

	if (multiplayerClientMode)
	{
		content.clear();
	}

	// add items to blackboard
	for (unsigned char n=0; n<nItems; n++)
	{
		bool valid;
		stream >> valid;
		if (valid)
		{
			std::string key;
			std::string message;
			float priority;

			stream >> key;
			stream >> message;
			stream >> priority;

			if (multiplayerClientMode)
			{
				//fprintf(stdout, "CLIENT BB wrote (%s, %s)\n", key.c_str(), message.c_str());
				content[key] = BlackboardItem(0, priority, message);
			}
			else
			{
				//fprintf(stdout, "SERVER BB wrote (%s, %s)\n", key.c_str(), message.c_str());
				Write(key, 0, priority, message);
			}
		}
	}

    return stream;
}

/**
* Saves state to command stream
* Only saves top level (author 0) blackboard items
*/
tcCommandStream& Blackboard::operator>>(tcCommandStream& stream)
{
	std::map<std::string, BlackboardItem>* map = 0;

	if (multiplayerClientMode)
	{
		map = &clientContent;
	}
	else
	{
		map = &content;
	}

	unsigned char nItems = (unsigned char)map->size();
	wxASSERT(map->size() <= 255);

	stream << nItems;

	// iterate through clientContent
    std::map<std::string, BlackboardItem>::iterator iter = map->begin();
    std::map<std::string, BlackboardItem>::iterator done = map->end(); 
    for (;iter != done; ++iter)
    {
		BlackboardItem item = iter->second;
		
		// only send items written at top level (author = 0)
		bool sendItem = (item.author == 0);
		stream << sendItem;

		if (sendItem)
		{
			stream << iter->first;
			stream << item.message;
			float priority = float(item.priority);
			stream << priority;

			//fprintf(stdout, "BB sent (%s, %s)\n", iter->first.c_str(), item.message.c_str());
		}
		else
		{
			//fprintf(stdout, "BB skipped (%s, %s, %d)\n", iter->first.c_str(), item.message.c_str(), item.author);
		}
    }

    return stream;
}


/**
* Loads state from game stream
*/
tcGameStream& Blackboard::operator<<(tcGameStream& stream)
{
    content.clear();
    unsigned int nContent;
    stream >> nContent;

    for (unsigned int n=0; n<nContent; n++)
    {
        std::string key;
        stream >> key;

        BlackboardItem item;
        item << stream;

        content[key] = item;
    }

    return stream;
}

/**
* Saves state to game stream
*/
tcGameStream& Blackboard::operator>>(tcGameStream& stream)
{
    unsigned int nContent = content.size();
    stream << nContent;

    for (std::map<std::string, BlackboardItem>::iterator iter = content.begin();
        iter != content.end(); ++iter)
    {
        stream << iter->first;
        iter->second >> stream;
    }

    return stream;
}


void Blackboard::ClearNewCommand()
{
	clientContent.clear();
	hasNewCommand = false;
}

bool Blackboard::HasNewCommand() const
{
	return hasNewCommand;
}




void Blackboard::Erase(const std::string& key, double priority)
{
    std::map<std::string, BlackboardItem>::iterator iter = 
        content.find(key);

    if (iter != content.end())
    {
        if (iter->second.priority <= priority)
        {
            content.erase(iter);
        }
    }
}

void Blackboard::EraseAll()
{
    content.clear();
}

void Blackboard::EraseAllFromAuthor(long author)
{
    if (author == -1)
    {
        fprintf(stderr, "Blackboard::EraseAllFromAuthor - invalid author (-1)\n");
        return;
    }
    
    
                   
    for (std::map<std::string, BlackboardItem>::iterator iter = 
        content.begin(); iter != content.end(); )
    { 
        if (iter->second.author == author) 
        { 
            content.erase(iter++); 
        } 
        else 
        { 
            ++iter; 
        } 
    }    
        
}

bool Blackboard::KeyExists(const std::string& key) const
{
    std::map<std::string, BlackboardItem>::const_iterator iter = 
        content.find(key);

    return (iter != content.end());
}

BlackboardItem Blackboard::Read(const std::string& key)
{
    std::map<std::string, BlackboardItem>::const_iterator iter = 
        content.find(key);

    if (iter == content.end())
    {
        return BlackboardItem();
    }
    else
    {
        return BlackboardItem(iter->second);
    }

}

/**
* @return -1 if key not found
*/
long Blackboard::ReadAuthor(const std::string& key)
{
    std::map<std::string, BlackboardItem>::const_iterator iter = 
        content.find(key);
    if (iter == content.end())
    {
        return -1;
    }
    else
    {
        return iter->second.author;
    }       
}

/**
* @return "" if key not found
*/
const std::string Blackboard::ReadMessage(const std::string& key) const
{
    // message to return if key not found
    static const std::string emptyMessage("");
    
    std::map<std::string, BlackboardItem>::const_iterator iter = 
        content.find(key);
    if (iter == content.end())
    {
        return emptyMessage;
    }
    else
    {
        return iter->second.message;
    }    
}

/**
* @return -1.0 if key not found
*/
double Blackboard::ReadPriority(const std::string& key)    
{
    std::map<std::string, BlackboardItem>::const_iterator iter = 
        content.find(key);
    if (iter == content.end())
    {
        return -1.0;
    }
    else
    {
        return iter->second.priority;
    }
}

/**
* Assumes a blackboard interface object, "BB", has been created
* on previous line. Board contents written by tasks will not be saved. 
* Items with author != 0 are ignored.
* Note tasks sensitive to sim time will not be saved correctly unless
* capbility to start game with arbitrary (non-zero) sim time is added.
*/
void Blackboard::SaveToPython(scriptinterface::tcScenarioLogger& logger)
{
	wxString s;

    for (std::map<std::string, BlackboardItem>::iterator iter = 
        content.begin(); iter != content.end(); ++iter)
    { 
		if (iter->second.author == 0)
		{
			s.Printf("BB.Write('%s', '%s')", iter->first.c_str(),
				iter->second.message.c_str());
			logger.AddScenarioText(s);
		}
    }  
}

/**
* @return true if write successful, false if blocked
*/
bool Blackboard::Write(const std::string& key, const BlackboardItem& item)    
{
    std::map<std::string, BlackboardItem>::iterator iter = 
        content.find(key);

    // if the item already exists check that the author matches or priority is greater to write
    if (iter != content.end())
    {
        if ((iter->second.priority > item.priority) && (iter->second.author != item.author))
        {
            return false;
        }
        iter->second = item;
    }
    else
    {
        content[key] = item;
    }

    if (multiplayerClientMode)
	{
		clientContent[key] = item;
	}
	hasNewCommand = true;

    return true;
}

/**
* @return true if write successful, false if blocked
*/
bool Blackboard::Write(const std::string& key, long author, double priority, const std::string& message)
{
    std::map<std::string, BlackboardItem>::iterator iter = 
        content.find(key);

    // if the item already exists check that the author matches or priority is greater to write
    if (iter != content.end())
    {
        if ((iter->second.priority > priority) && (iter->second.author != author))
        {
            return false;
        }
        iter->second.author = author;
        iter->second.priority = priority;
        iter->second.message = message;
    }
    else
    {
        content[key] = BlackboardItem(author, priority, message);
    }
    
	if (multiplayerClientMode)
	{
		clientContent[key] = BlackboardItem(author, priority, message);
	}
	hasNewCommand = true;

    return true;
}

Blackboard::Blackboard()
: hasNewCommand(false)
{
}

Blackboard::~Blackboard()
{
}



