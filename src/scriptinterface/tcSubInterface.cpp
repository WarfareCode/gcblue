/**  
**  @file tcSubInterface.cpp
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
#endif

#include "tcSubInterface.h"
#include "tcSubDBObject.h"
#include "tcMessageInterface.h"
#include "tcPlatformObject.h"
#include "tcSimState.h"
#include "tcSound.h"
#include "tcSubObject.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif 


namespace scriptinterface {

	tcMessageInterface* tcSubInterface::messageInterface = 0;
	tcSound* tcSubInterface::sound = 0;
	tcSimState* tcSubInterface::simState = 0;

	/**
	* @return battery charge fraction, 0 - 1
	*/
	float tcSubInterface::GetBatteryFraction() const
	{
		if (!subObj) return 0;

		if (subObj->IsDieselElectric())
		{
			float batteryCapacity = subObj->mpDBObject->batteryCapacity_kJ;
			if (batteryCapacity > 0)
			{
				return subObj->GetBatteryCharge() / batteryCapacity;
			}
			else
			{
				wxASSERT(false);
				return 1.0f;
			}
		}
		else
		{
			return 1.0f;
		}
	}

    /**
    * @return speed at which cavitation occurs at depth_m
    */
    float tcSubInterface::GetCavitatingSpeed(float depth_m) const
    {
        if (!subObj) return 999.0f;

        return subObj->mpDBObject->GetCavitationSpeedKts(depth_m);
    }

	/**
	* @return maximum depth in meters
	*/
	float tcSubInterface::GetMaxDepth() const
	{
		if (!subObj) return 0;

		return subObj->mpDBObject->mfMaxDepth_m;
	}

	void tcSubInterface::GoToPeriscopeDepth()
	{
		if (subObj)
		{
			subObj->SetAltitude(-subObj->GetPeriscopeDepth() + 0.4f);
		}
	}

	bool tcSubInterface::IsAtPeriscopeDepth() const
	{
		if (!subObj) return false;
		return subObj->IsAtPeriscopeDepth();
	}

	bool tcSubInterface::IsDieselElectric() const
	{
		if (!subObj) return false;
		return subObj->IsDieselElectric();
	}

	bool tcSubInterface::IsPeriscopeRaised() const
	{
		if (!subObj) return false;
		return subObj->GetPeriscopeState();
	}

	bool tcSubInterface::IsRadarMastRaised() const
	{
		if (!subObj) return false;
		return subObj->GetRadarMastState();
	}

	bool tcSubInterface::IsSnorkeling() const
	{
		if (!subObj) return false;
		return subObj->IsSnorkeling();
	}

	/**
	* @return true if interface is valid sub interface
	*/
	bool tcSubInterface::IsValid() const
	{
		return (subObj != 0);
	}

	void tcSubInterface::LowerPeriscope()
	{
		if (subObj)
		{
			if (subObj->GetPeriscopeState())
			{
				subObj->SetPeriscopeState(false);

                if (subObj->IsEditMode()) return;

                wxString s = wxString::Format("%s (%s): lowering scope\n",
                    subObj->mzUnit.c_str(), subObj->mzClass.c_str());
                messageInterface->ChannelMessage("Info", s.ToStdString(), subObj->GetAlliance());

                sound->PlayEffect("LowBeep");
			}
		}
	}

	void tcSubInterface::LowerRadarMast()
	{
		if (subObj)
		{
			if (subObj->GetRadarMastState())
			{
				subObj->SetRadarMastState(false);

                if (subObj->IsEditMode()) return;

                wxString s = wxString::Format("%s (%s): lowering radar mast\n",
                    subObj->mzUnit.c_str(), subObj->mzClass.c_str());
                messageInterface->ChannelMessage("Info", s.ToStdString(), subObj->GetAlliance());

                sound->PlayEffect("LowBeep");
            }
        }
	}

	void tcSubInterface::RaisePeriscope()
	{
		if (subObj)
		{
			if (!subObj->GetPeriscopeState())
            {
                subObj->SetPeriscopeState(true);

                if (subObj->IsEditMode()) return;

                wxString s = wxString::Format("%s (%s): raising scope\n",
                    subObj->mzUnit.c_str(), subObj->mzClass.c_str());
                messageInterface->ChannelMessage("Info", s.ToStdString(), subObj->GetAlliance());

                sound->PlayEffect("LowBeep");
            }
        }
	}

	void tcSubInterface::RaiseRadarMast()
	{
		if (subObj)
		{
			if (!subObj->GetRadarMastState())
			{
                subObj->SetRadarMastState(true);

                if (subObj->IsEditMode()) return;

                wxString s = wxString::Format("%s (%s): raising radar mast\n",
                    subObj->mzUnit.c_str(), subObj->mzClass.c_str());
                messageInterface->ChannelMessage("Info", s.ToStdString(), subObj->GetAlliance());

                sound->PlayEffect("LowBeep");
            }
        }
	}

	void tcSubInterface::SetSnorkelState(bool state)
	{
		if (subObj)
		{
			if (subObj->IsSnorkeling() == state) return; // no change
            subObj->SetSnorkelState(state);

            if (subObj->IsEditMode()) return;

            wxString s;
            if (state)
            {
                s = wxString::Format("%s (%s): started diesels\n",
                    subObj->mzUnit.c_str(), subObj->mzClass.c_str());
            }
            else
            {
                s = wxString::Format("%s (%s): stopped diesels\n",
                    subObj->mzUnit.c_str(), subObj->mzClass.c_str());
            }
            messageInterface->ChannelMessage("Info", s.ToStdString(), subObj->GetAlliance());
		}
	}

	tcSubInterface::tcSubInterface()
		: subObj(0)
	{
	}

	tcSubInterface::tcSubInterface(tcPlatformObject* obj)
	{
		subObj = dynamic_cast<tcSubObject*>(obj);

		if (!sound)
		{
			sound = tcSound::Get();
		}
		if (!simState)
		{
			simState = tcSimState::Get();
		}
		if (!messageInterface)
		{
			messageInterface = tcMessageInterface::Get();
		}
	}

	tcSubInterface::~tcSubInterface()
	{
	}


}



