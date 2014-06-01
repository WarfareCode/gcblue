/**  
**  @file tcMapMissionObject.cpp
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



#include "stdwx.h" // precompiled header file

#ifndef WX_PRECOMP
#include "wx/wx.h" 
#endif // WX_PRECOMP

#include "tcMapMissionObject.h"
#include "tcMapView.h"
#include "tcTacticalMapView.h"
#include "tcWorldMapView.h"
#include "math_constants.h"
#include "simmath.h"
#include "tcSimState.h"

#include "common/tcStream.h"
#include "common/tcObjStream.h"

#include "ai/tcMission.h"
#include "ai/tcAttackMission.h"
#include "ai/tcMissionManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif 



/**
* Loads state from stream
*/
tcUpdateStream& tcMapMissionObject::operator<<(tcUpdateStream& stream)
{
	tcMapObject::operator<<(stream);

	stream >> caption;

	return stream;
}


/**
* Saves state to stream
*/
tcUpdateStream& tcMapMissionObject::operator>>(tcUpdateStream& stream)
{
	tcMapObject::operator>>(stream);

	stream << caption;

	return stream;
}


void tcMapMissionObject::Draw(tc3DWindow2* host)
{
    if (!isActive) return;

    if (updateCounter++ % 4 == 0) Update();

    tcPoint pscreen = GetScreenPoint();
    float x = pscreen.x;
    float y = pscreen.y;

    const Vec4 drawColor(1, 1, 1, 1); // override color;


    host->DrawTextR(caption.c_str(), x+5.0f, y, 
        mapView->GetDefaultFont(), drawColor, 12.0, tc3DWindow2::LEFT_BASE_LINE);

	if (markerEnabled) // avoids parent draw overhead this way
	{
        const float a = 4.0f;
		host->DrawLineR(x, y-a, x, y+a, drawColor);
		host->DrawLineR(x-a, y, x+a, y, drawColor);
	}

    if (isHooked)
    {
        const Vec4 hookColor(1, 1, 1, 1);
        const float a = 10.0f;

		host->DrawLineR(x-a, y-a, x+a, y-a, hookColor);
		host->DrawLineR(x-a, y+a, x+a, y+a, hookColor);
		host->DrawLineR(x-a, y-a, x-a, y+a, hookColor);
		host->DrawLineR(x+a, y-a, x+a, y+a, hookColor);
    }

}


ai::tcMission* tcMapMissionObject::GetMission()
{
    ai::tcMissionManager* missionManager = GetMissionManager();
    if (missionManager == 0)
    {
        return 0;
    }

    ai::tcMission* mission = missionManager->GetMission(missionId);
    return mission;
}


ai::tcMissionManager* tcMapMissionObject::GetMissionManager()
{
    tcGameObject* obj = tcSimState::Get()->GetObject(platformId);
    tcFlightOpsObject* host = dynamic_cast<tcFlightOpsObject*>(obj);
    if (host == 0)
    {
        return 0;
    }
    
    return host->GetFlightPort()->GetMissionManager();
}



unsigned int tcMapMissionObject::GetMissionId() const
{
    return missionId;
}


void tcMapMissionObject::MoveToScreenPoint(const wxPoint& pos)
{
    tcMapObject::MoveToScreenPoint(pos);

    if (dragActive) return; // don't update during drag

    tcSimState* simState = tcSimState::Get();
    if (!simState->IsMultiplayerClient())
    {
        ai::tcMission* mission = GetMission();

        if (ai::tcAttackMission* patrol = dynamic_cast<ai::tcAttackMission*>(mission))
        {
			patrol->RecenterArea(_x, _y);
			patrol->UpdateInFlightAircraft();
        }
    }
    else
    {
        SendMultiplayerMoveCommand();
    }
}


void tcMapMissionObject::SendMultiplayerMoveCommand()
{

    ai::tcMissionManager* missionManager = GetMissionManager();
    if (missionManager == 0)
    {
        wxASSERT(false);
        return;
    }

    ai::tcMissionManager::CommandInfo cmd;
    cmd.id = missionId;
    cmd.op = 1;
    cmd.val_a = _x;
    cmd.val_b = _y;

    missionManager->AddCommand(cmd);

}



void tcMapMissionObject::SendMultiplayerDeleteCommand()
{
    ai::tcMissionManager* missionManager = GetMissionManager();
    if (missionManager == 0)
    {
        wxASSERT(false);
        return;
    }

    ai::tcMissionManager::CommandInfo cmd;
    cmd.id = missionId;
    cmd.op = ai::tcMissionManager::CommandInfo::DELETE_MISSION;
    cmd.val_a = 0;
    cmd.val_b = 0;

    missionManager->AddCommand(cmd);

}




/**
* @return false if keyCode is valid command for this object
*/
bool tcMapMissionObject::ProcessKey(int keyCode)
{
    if (keyCode == WXK_DELETE)
    {
        ai::tcMission* mission = GetMission();
        if (mission)
        {
            if (!tcSimState::Get()->IsMultiplayerClient())
            {
                mission->EndMission();
            }
            else
            {
                SendMultiplayerDeleteCommand();
            }
        }
        return true;
    }
    else
    {
        return false;
    }
}

void tcMapMissionObject::SetDragActive(bool state)
{
    if (state == dragActive) return; // no change, return

    if (state == false) // drag stopped
    {
        tcSimState* simState = tcSimState::Get();

        ai::tcMission* mission = GetMission();
        if (ai::tcAttackMission* patrol = dynamic_cast<ai::tcAttackMission*>(mission))
        {
            if (!simState->IsMultiplayerClient())
            {
				patrol->RecenterArea(_x, _y);
				patrol->UpdateInFlightAircraft();
            }
            else
            {
                SendMultiplayerMoveCommand();
            }

        }

    }

    dragActive = state;
}


void tcMapMissionObject::Update()
{
    tcGameObject* obj = tcSimState::Get()->GetObject(platformId);
    if (obj == 0)
    {
        FlagForDelete();
        return;
    }

    if (dragActive) return; // no updates during drag

    ai::tcMission* mission = GetMission();

    if (ai::tcAttackMission* generalMission = dynamic_cast<ai::tcAttackMission*>(mission))
    {
		std::vector<GeoPoint> patrolArea = generalMission->GetArea();
		if (patrolArea.size() > 0)
		{
			generalMission->GetAreaCenter(_x, _y);
			int targetType = generalMission->GetTargetType();
			switch (targetType)
			{
			case AIR_TARGET:
				{
					if (generalMission->GetRepeatIntervalHours() > 0) caption = "CAP";
					else caption = "Air Attack";
				}
				break;
			case SURFACE_TARGET: caption = "Surface Attack"; break;
			case SUBSURFACE_TARGET: caption = "ASW Patrol"; break;
			case LAND_TARGET: caption = "Ground Attack"; break;
            case AEW_TARGET: caption = "AEW"; break;
			default: caption = "Patrol";
			}

		}
		else
		{
			FlagForDelete();
			return;
		}

    }
    else
    {
        FlagForDelete();
        return;
    }

}



tcMapMissionObject::tcMapMissionObject(long platformId_, unsigned int missionId_)
: tcMapObject(),
  platformId(platformId_),
  missionId(missionId_),
  updateCounter(0)
{

}


tcMapMissionObject::~tcMapMissionObject()
{
}

