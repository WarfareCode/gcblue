/**  
**  @file tcMissionInterface.cpp
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
#ifdef WIN32
#include "wx/msw/private.h" // for MS Windows specific definitions
#endif
#endif

#include "tcMissionInterface.h"
#include "tcSimState.h"
#include "ai/tcMissionManager.h"
#include "ai/tcAttackMission.h"
#include "ai/Brain.h"
#include "ai/Nav.h"
#include "tcPlatformObject.h"

#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif 

using namespace boost::python;

namespace scriptinterface 
{

    object tcMissionInterface::GetInterface() 
    {
        object InterfaceType = class_<tcMissionInterface>("MissionInterface")
            .def("IsValid", &tcMissionInterface::IsValid)
            .def("GetAirborneAircraftCount", &tcMissionInterface::GetAirborneAircraftCount)
			.def("GetAirborneAircraftId", &tcMissionInterface::GetAirborneAircraftId)
            .def("GetMissionAircraftCount", &tcMissionInterface::GetMissionAircraftCount)
            .def("GetSmallestWaypointIndex", &tcMissionInterface::GetSmallestWaypointIndex)
            .def("GetLocalObj", &tcMissionInterface::GetLocalObj)
            ; 
        return InterfaceType;
    }

    void tcMissionInterface::SetObj(ai::tcAttackMission* mission_)
    {
        static_mission = mission_;
    }

    ai::tcAttackMission* tcMissionInterface::static_mission = 0;

    void tcMissionInterface::GetLocalObj() 
    {
        mission = static_mission;
    }

    unsigned int tcMissionInterface::GetAirborneAircraftCount() const
    {
        if (mission != 0)
        {
            return mission->GetAirborneAircraftCount();
        }
        else
        {
            wxASSERT(false);
            return 0;
        }
    }

	long tcMissionInterface::GetAirborneAircraftId(unsigned int idx) const
	{
        if (mission != 0)
        {

			const std::vector<MissionAircraftInfo>& airborneAircraft = mission->GetAirborneMissionAircraft();
			if (idx < airborneAircraft.size())
			{
				return airborneAircraft[idx].id;
			}
			else
			{
				wxASSERT(false);
				return -1;
			}
            
        }
        else
        {
            wxASSERT(false);
            return -1;
        }
	}

    /**
    * @return total number of aircraft in mission
    */
    unsigned int tcMissionInterface::GetMissionAircraftCount() const
    {
        if (mission != 0)
        {
            return int(mission->GetMissionAircraft().size());
        }
        else
        {
            wxASSERT(false);
            return 0;
        }
    }


    /**
    * Used to check nav progress of group (e.g. for waiting for group members to catch up)
    */
    unsigned int tcMissionInterface::GetSmallestWaypointIndex() const
    {
        if (mission == 0) return 0;

        unsigned int result = 99;
        bool updated = false;

        tcSimState* simState = tcSimState::Get();
        const std::vector<MissionAircraftInfo>& missionAircraft = mission->GetMissionAircraft();
        
        for (size_t n=0; n<missionAircraft.size(); n++)
        {
            tcPlatformObject* platform = 
                dynamic_cast<tcPlatformObject*>(simState->GetObjectByName(missionAircraft[n].name));
            if ((platform != 0) && (platform->parent == 0))
            {
                if (ai::Nav* nav = platform->GetBrain()->GetNavTask())
                {
                    result = std::min(result, nav->GetCurrentWaypoint());
                    updated = true;
                }
            }
        }

        return updated ? result : 0;
    }


    /** 
    * method to directly set local flightport
    */
    void tcMissionInterface::SetMission(ai::tcAttackMission* mission_) 
    {
        mission = mission_;
    }


    bool tcMissionInterface::IsValid()
    {
        return (mission != 0);
    }


    tcMissionInterface::tcMissionInterface()
    : mission(0)
    {
    }
    
    tcMissionInterface::~tcMissionInterface()
    {
    }


}


