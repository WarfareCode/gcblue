/** 
**  @file tcControllableObject.cpp
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

#include "tcControllableObject.h"
#include "tcUserInfo.h"
#include "tcDatabase.h"
#include "tcAllianceInfo.h"
#include "common/tcStream.h"
#include "common/tcObjStream.h"
#include "tcGameStream.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

bool tcControllableObject::bypassControlCheck = true;

tcUserInfo* tcControllableObject::userInfo = 0;

tcAllianceInfo* tcControllableObject::allianceInfo = 0;

database::tcDatabase* tcControllableObject::database = 0;


void tcControllableObject::AttachAllianceInfo()
{
    allianceInfo = tcAllianceInfo::Get();
}

void tcControllableObject::AttachDatabase()
{
    database = database::tcDatabase::Get();
}

void tcControllableObject::AttachUserInfo()
{
	userInfo = tcUserInfo::Get();
}

tcAllianceInfo::Affiliation tcControllableObject::GetAffiliationWith(unsigned char otherAlliance) const
{
    return allianceInfo->GetAffiliation(alliance, otherAlliance);
}

tcAllianceInfo::Affiliation tcControllableObject::GetAffiliationWith(const tcControllableObject* other) const
{
    wxASSERT(other != 0);
    return allianceInfo->GetAffiliation(alliance, other->GetAlliance());
}

void tcControllableObject::SetBypassControlCheck(bool state)
{
	bypassControlCheck = state;
}

/**
* Loads state from create stream
*/
tcCreateStream& tcControllableObject::operator<<(tcCreateStream& stream)
{
    stream >> alliance;

    country = tcAllianceInfo::Get()->GetAllianceDefaultCountry(alliance);

    return stream;
}

/**
* Saves state to create stream
*/
tcCreateStream& tcControllableObject::operator>>(tcCreateStream& stream)
{
    stream << alliance;

    return stream;
}

/**
* Loads state from update stream
*/
tcUpdateStream& tcControllableObject::operator<<(tcUpdateStream& stream)
{
	stream >> flags;
	stream >> controller;

    return stream;
}

/**
* Saves state to update stream
*/
tcUpdateStream& tcControllableObject::operator>>(tcUpdateStream& stream)
{
	stream << flags;
	stream << controller;

    return stream;
}


/**
* Loads state from game stream
*/
tcGameStream& tcControllableObject::operator<<(tcGameStream& stream)
{
    stream >> alliance;
	stream >> flags;
	stream >> controller;
    stream >> country;

    return stream;
}

/**
* Saves state to game stream
*/
tcGameStream& tcControllableObject::operator>>(tcGameStream& stream)
{
    stream << alliance;
	stream << flags;
	stream << controller;
    stream << country;

    return stream;
}


unsigned char tcControllableObject::GetAlliance() const
{
	return alliance;
}

void tcControllableObject::SetAlliance(unsigned char val)
{
    if (val < tcAllianceInfo::MAX_ALLIANCES)
    {
	    alliance = val;
        SetCountry(allianceInfo->GetAllianceDefaultCountry(val));
    }
    else
    {
        fprintf(stderr, "tcControllableObject::SetAlliance - alliance out of range (%d)\n",
            val);
        wxASSERT(false);
    }
}

unsigned char tcControllableObject::GetAccessLevel() const
{
	return flags & ACCESS_LEVEL_MASK;
}

void tcControllableObject::SetAccessLevel(unsigned char level)
{
	flags &= ~ACCESS_LEVEL_MASK; // zero out access level
    flags |= level;
}

const std::string& tcControllableObject::GetController() const
{
	return controller;
}

void tcControllableObject::SetController(const std::string& username)
{
	controller = username;

    if (controller.size() == 0)
    {
        flags &= ~ACCESS_LEVEL_MASK; // zero out access level
    }
}

const std::string& tcControllableObject::GetCountry() const
{
    return country;
}

tcTexture2D* tcControllableObject::GetEnsign()
{
    return database->GetEnsign(country);
}

/**
* Use this method to set a custom country for this object. The default 
* country for the alliance will be applied in SetAlliance
*/
void tcControllableObject::SetCountry(const std::string& s)
{
    country = s;
}

/**
* If object does not have controller, obj is available if 
* user rank >= access level, otherwise user rank must be > access level
*/
bool tcControllableObject::IsAvailable() const
{
	return IsAvailable(userInfo->GetOwnAlliance(), userInfo->GetRank());

}

bool tcControllableObject::IsAvailable(unsigned char playerAlliance, unsigned char playerAccessLevel) const
{
	if (playerAlliance != alliance) return false;

	if (controller.size() == 0)
	{
		return playerAccessLevel >= GetAccessLevel();
	}
	else
	{
		return playerAccessLevel >= GetAccessLevel();
	}
}

bool tcControllableObject::IsControlledBy(const std::string& playerName) const
{
	return (controller == playerName);
}

bool tcControllableObject::IsControlled() const
{
	return bypassControlCheck || (controller == userInfo->GetUsername());
}

tcControllableObject::tcControllableObject()
: controller(""), flags(0), alliance(0)
{
}

tcControllableObject::tcControllableObject(const tcControllableObject& src)
: controller(src.controller), flags(src.flags), alliance(src.alliance),
  country(src.country)
{
}

tcControllableObject::~tcControllableObject()
{
}

