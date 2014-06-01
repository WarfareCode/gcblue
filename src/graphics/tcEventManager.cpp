/**
**  @file tcEventManager.cpp
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

#include "tcEventManager.h"
#include "tcSensorMapTrack.h"
#include "tcUserInfo.h"
#include "tcOptions.h"
#include "wxcommands.h"


tcUserInfo* tcEventManager::userInfo = 0;
tcOptions* tcEventManager::options = 0;
wxWindow* tcEventManager::eventObject = 0; // for passing time acceleration limit events

tcEventManager* tcEventManager::Get()
{
    static tcEventManager instance;

    return &instance;
}

/**
* @return accel limit in X:1 format based on accelLimitCode
* @param accelLimitCode 0 - pause, 1 - 1:1, 2 - 2:1, 3 - 4:1, 4 - 10:1, 5 - 30:1, 6: - no limit
*/
int tcEventManager::ConvertCodeToAccelLimit(int accelLimitCode) const
{
    int accelLimit = 120;
    switch (accelLimitCode)
    {
        case 0: accelLimit = 0; break;
        case 1: accelLimit = 1; break;
        case 2: accelLimit = 2; break;
        case 3: accelLimit = 4; break;
        case 4: accelLimit = 10; break;
        case 5: accelLimit = 30; break;
        case 6: accelLimit = 120; break;
        default: accelLimit = 120; break;
    }

    return accelLimit;
}

/**
* @return time acceleration limit based on contact classification as defined by user in events options
* @return  
*/
int tcEventManager::GetAccelLimit(unsigned int classification) const
{
    /// option limit codes
    /// 0 - pause, 1 - 1:1, 2 - 2:1, 3 - 4:1, 4 - 10:1, 5 - 30:1, 6: - no limit
    int accelLimitCode = 6;

    switch (classification)
    {
        case PTYPE_SURFACE:
        case PTYPE_SMALLSURFACE:
        case PTYPE_LARGESURFACE:
        case PTYPE_CARRIER:
            accelLimitCode = options->eventContactSurface;
            break;

        case PTYPE_AIR:
        case PTYPE_FIXEDWING:
        case PTYPE_HELO:
            accelLimitCode = options->eventContactAir;
            break;

        case PTYPE_MISSILE:
            accelLimitCode = options->eventContactMissile;
            break;

        case PTYPE_SUBSURFACE:
        case PTYPE_SUBMARINE:
            accelLimitCode = options->eventContactSubmarine;
            break;

        case PTYPE_TORPEDO:
            accelLimitCode = options->eventContactTorpedo;
            break;

        case PTYPE_GROUND:
        case PTYPE_AIRFIELD:
            accelLimitCode = options->eventContactGround;
            break;

        case PTYPE_UNKNOWN:
        case PTYPE_SONOBUOY:
        case PTYPE_WATERCM:
        case PTYPE_WATERMINE:
        case PTYPE_AIRCM:
        default:
            accelLimitCode = options->eventContactAny;
            break;
    }

    return ConvertCodeToAccelLimit(accelLimitCode);
}

/**
* Called when sensor track classification is updated
* @param alliance alliance that is reporting this track
*/
void tcEventManager::UpdatedContact(unsigned char alliance, tcSensorMapTrack* track)
{
    if (!userInfo->IsOwnAlliance(alliance)) return;
    
    unsigned int classification = track->mnClassification;
    int accelLimit = GetAccelLimit(classification);

    SendAccelLimitEvent(accelLimit);
}

/**
* Called when new track is formed
* @param alliance alliance that is reporting this track
*/
void tcEventManager::NewContact(unsigned char alliance, tcSensorMapTrack* track)
{
    if (!userInfo->IsOwnAlliance(alliance)) return;

    unsigned int classification = track->mnClassification;
    int accelLimit = GetAccelLimit(classification);

    SendAccelLimitEvent(accelLimit);
    
}

/**
* Called when damage is received by alliance
* @param alliance alliance that is reporting the damage
*/
void tcEventManager::DamageReceived(unsigned char alliance)
{
    if (!userInfo->IsOwnAlliance(alliance)) return;

    int accelLimitCode = options->eventDamage;

    int accelLimit = ConvertCodeToAccelLimit(accelLimitCode);

    SendAccelLimitEvent(accelLimit);
}

void tcEventManager::IdlePlatform(unsigned char alliance)
{
    if (!userInfo->IsOwnAlliance(alliance)) return;

    int accelLimitCode = options->eventIdlePlatform;

    int accelLimit = ConvertCodeToAccelLimit(accelLimitCode);

    SendAccelLimitEvent(accelLimit);
}


void tcEventManager::WeaponLaunched(unsigned char alliance)
{
    if (!userInfo->IsOwnAlliance(alliance)) return;

    int accelLimitCode = options->eventLaunchWeapon;

    int accelLimit = ConvertCodeToAccelLimit(accelLimitCode);

    SendAccelLimitEvent(accelLimit);
}


void tcEventManager::SendAccelLimitEvent(int accelLimit)
{
	wxCommandEvent command(wxEVT_COMMAND_BUTTON_CLICKED, ID_SETMAXTIMEACCEL);
	command.SetEventObject(eventObject);
	command.SetExtraLong(accelLimit);
	eventObject->GetEventHandler()->AddPendingEvent(command);
}


tcEventManager::tcEventManager()
{
    userInfo = tcUserInfo::Get();
    options = tcOptions::Get();
}

tcEventManager::~tcEventManager()
{
}


