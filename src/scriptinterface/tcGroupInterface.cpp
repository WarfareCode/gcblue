/**  
**  @file  tcGroupInterface.cpp
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
#endif // WIN32
#endif

#include "tcGroupInterface.h"
#include "tcPlatformInterface.h"
#include "tcWeaponInterface.h"
#include "tcSimState.h"
#include "network/tcMultiplayerInterface.h"
#include "tcCommandQueue.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif 

namespace scriptinterface 
{
	tcSimState* tcGroupInterface::simState = NULL;
    tcCommandQueue* tcGroupInterface::mpCommandQueue = 0;
    tcScenarioInterface* tcGroupInterface::scenarioInterface = 0;

	/**
	* @return tcPlatformInterface object for group member <idx>
	*/
	tcPlatformInterface tcGroupInterface::GetPlatformInterface(int idx)
	{
		long id = GetUnitId(idx);

		tcGameObject* gameObj = simState->GetObject(id);
		if (tcPlatformObject* platformObj = dynamic_cast<tcPlatformObject*>(gameObj))
		{
			return tcPlatformInterface(platformObj);
		}
		else
		{
			fprintf(stderr, "tcGroupInterface::GetPlatformInterface - "
				"returned NULL or non-platform obj\n");
			return tcPlatformInterface();
		}
	}

	/**
	* @return tcWeaponInterface object for group member <idx>
	*/
	tcWeaponInterface tcGroupInterface::GetWeaponInterface(int idx)
	{
		long id = GetUnitId(idx);

		tcGameObject* gameObj = simState->GetObject(id);
		if (tcWeaponObject* weaponObj = dynamic_cast<tcWeaponObject*>(gameObj))
		{
			return tcWeaponInterface(weaponObj);
		}
		else
		{
			fprintf(stderr, "tcGroupInterface::GetWeaponInterface - "
				"returned NULL or non-weapon obj\n");
			return tcWeaponInterface();
		}
	}

    tcScenarioInterface tcGroupInterface::GetScenarioInterface()
    {
        if (tcGameObject::IsEditMode())
        {
            return *scenarioInterface;
        }
        else
        {
            wxMessageBox("Access to ScenarioInterface blocked not allowed game play. Corrupt script file?", "Warning");
            return *scenarioInterface;
        }
    }

    tcStringArray tcGroupInterface::GetTankerList()
    {
        tcStringArray result;

        for (size_t n=0; n<groupUnits.size(); n++)
        {
            long id_n = groupUnits[n];
            tcAirObject* air = dynamic_cast<tcAirObject*>(simState->GetObject(id_n));
            if ((air != 0) && (air->IsTanker()))
            {
                result.AddString(air->mzUnit.c_str());
            }
        }

        return result;
    }

	/**
	*
	*/
	int tcGroupInterface::GetUnitCount()
	{
		return (int)groupUnits.size();
	}
	/**
	*
	*/
	long tcGroupInterface::GetUnitId(int idx) const
	{
		if ((size_t)idx >= groupUnits.size())
		{
			return -1;
		}
		else
		{
			return groupUnits[idx];
		}
    }

    bool tcGroupInterface::IsPlatform(int idx) const
    {
        long id = GetUnitId(idx);
		const tcGameObject* gameObj = simState->GetObject(id);
        const tcPlatformObject* platformObj = dynamic_cast<const tcPlatformObject*>(gameObj);
        return (platformObj != 0);
    }

    bool tcGroupInterface::IsWeapon(int idx) const
    {
        long id = GetUnitId(idx);
		const tcGameObject* gameObj = simState->GetObject(id);
        const tcWeaponObject* weaponObj = dynamic_cast<const tcWeaponObject*>(gameObj);
        return (weaponObj != 0);
    }

    /**
    *
    */
    std::vector<long>& tcGroupInterface::GetUnits()
    {
        return groupUnits;
    }

    /**
    * Request user input. Python callback function is called after input is 
    * obtained 
    */
    void tcGroupInterface::GetUserInput(std::string callback, std::string uitype)
    {
        if (mpCommandQueue == 0) return;
        mpCommandQueue->GetUserInput(callback.c_str(), uitype.c_str(), -1, "");
    }

    long tcGroupInterface::LookupUnit(const std::string& name)
    {
        for (size_t n=0; n<groupUnits.size(); n++)
        {
            long id_n = groupUnits[n];
            tcGameObject* gameObj = simState->GetObject(id_n);
            if ((gameObj != 0) && (name == gameObj->mzUnit.c_str()))
            {
                return id_n;
            }
        }

        return -1;
    }

    int tcGroupInterface::LookupUnitIdx(const std::string& name)
    {
        for (size_t n=0; n<groupUnits.size(); n++)
        {
            long id_n = groupUnits[n];
            tcGameObject* gameObj = simState->GetObject(id_n);
            if ((gameObj != 0) && (name == gameObj->mzUnit.c_str()))
            {
                return int(n);
            }
        }

        return -1;
    }

    /**
    * Call to remove destroyed unit from group selection
    */
    void tcGroupInterface::RemoveUnit(long unit)
    {
        std::vector<long> remainingUnits;

        for (size_t n=0; n<groupUnits.size(); n++)
        {
            if (groupUnits[n] != unit) remainingUnits.push_back(groupUnits[n]);
        }

        groupUnits = remainingUnits;
    }

    /**
    *
    */
	void tcGroupInterface::SetUnit(long unit)
    {
        groupUnits.clear();
        groupUnits.push_back(unit);
    }

	/**
	*
	*/
	void tcGroupInterface::SetUnits(const std::vector<long>& units)
	{
		groupUnits = units;
	}


	void tcGroupInterface::ReleaseControl()
	{
        if (groupUnits.size() == 0) return;

		using network::tcMultiplayerInterface;

        std::vector<long> controlledIds;

        for (size_t k=0; k<groupUnits.size(); k++)
        {
            tcGameObject* gameObj = simState->GetObject(groupUnits[k]);
            if ((gameObj != 0) && (gameObj->IsControlled()))
            {
                controlledIds.push_back(groupUnits[k]);
            }
        }

        tcMultiplayerInterface::Get()->SendControlRelease(controlledIds);
	}


	void tcGroupInterface::TakeControl()
	{
        if (groupUnits.size() == 0) return;

		using network::tcMultiplayerInterface;

        std::vector<long> availableIds;

        for (size_t k=0; k<groupUnits.size(); k++)
        {
            tcGameObject* gameObj = simState->GetObject(groupUnits[k]);
            if ((gameObj != 0) && (gameObj->IsAvailable()))
            {
                availableIds.push_back(groupUnits[k]);
            }
        }

        tcMultiplayerInterface::Get()->SendControlRequest(availableIds);
	}





	/**
	*
	*/
	tcGroupInterface::tcGroupInterface()
	{
		if (!simState)
		{
			simState = tcSimState::Get();
		}
		groupUnits.clear();
	}

	tcGroupInterface::~tcGroupInterface()
	{
	}
}

