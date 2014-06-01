/** 
**  @file tcControllableObject.h
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

#ifndef _TCCONTROLLABLEOBJECT_H_
#define _TCCONTROLLABLEOBJECT_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
#include "tcAllianceInfo.h"

class tcUserInfo;
class tcStream;
class tcCommandStream;
class tcCreateStream;
class tcUpdateStream;
class tcGameStream;
class tcTexture2D;

namespace database
{
    class tcDatabase;
}

/**
* Base class for multiplayer client control of game objects
*/
class tcControllableObject  
{
public:
	enum
	{
		ACCESS_LEVEL_MASK = 0x00FF
	};

	unsigned char GetAlliance() const;
	void SetAlliance(unsigned char val);

    tcAllianceInfo::Affiliation GetAffiliationWith(unsigned char otherAlliance) const;
    tcAllianceInfo::Affiliation GetAffiliationWith(const tcControllableObject* other) const;

	unsigned char GetAccessLevel() const;
	void SetAccessLevel(unsigned char level);
    
	const std::string& GetController() const;
	virtual void SetController(const std::string& username);

    const std::string& GetCountry() const;
    void SetCountry(const std::string& s);
    tcTexture2D* GetEnsign();

	bool IsAvailable() const;
	bool IsAvailable(unsigned char playerAlliance, unsigned char playerAccessLevel) const;

	/// @return true if controlled by player
	bool IsControlledBy(const std::string& playerName) const;

	/// @return true if controlled by client player (client only, uses local userInfo for playerName)
	bool IsControlled() const;


    tcCreateStream& operator<<(tcCreateStream& stream);
    tcUpdateStream& operator<<(tcUpdateStream& stream);
    tcGameStream& operator<<(tcGameStream& stream);

    tcCreateStream& operator>>(tcCreateStream& stream);
    tcUpdateStream& operator>>(tcUpdateStream& stream);
    tcGameStream& operator>>(tcGameStream& stream);

    static void AttachAllianceInfo();
    static void AttachDatabase();
	static void AttachUserInfo();
	static void SetBypassControlCheck(bool state);

    tcControllableObject();
    tcControllableObject(const tcControllableObject& src);
    ~tcControllableObject();
private:
    unsigned char alliance;
	unsigned short flags; ///< flags governing control permission
	std::string controller; ///< username of player controlling object
    std::string country; ///< country that this object belongs to

	static tcUserInfo* userInfo;
    static tcAllianceInfo* allianceInfo;
    static database::tcDatabase* database;
	static bool bypassControlCheck; ///< bypass control check in single play or multiplayerServer
};
#endif
