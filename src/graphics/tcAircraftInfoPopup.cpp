/** 
**  @file tcAircraftInfoPopup.cpp 
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

#include "tcAircraftInfoPopup.h"

#include <stdio.h>
#include <iostream>
#include "tcTime.h"
#include "tcSimState.h"
#include "tcAeroAirObject.h"
#include "tcUnits.h"
#include "tcJetDBObject.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif 

tc3DWindow2* tcAircraftInfoPopup::parent = 0;

/**
*
*/
void tcAircraftInfoPopup::SetParent(tc3DWindow2* par)
{
    parent = par;
}




/**
* Clears the text buffer
*/
void tcAircraftInfoPopup::Clear()
{
	messageText = "";
}

/**
*
*/
void tcAircraftInfoPopup::Draw()
{
    //unsigned currentCount = tcTime::Get()->Get30HzCount();

    //unsigned age = currentCount - birthCount;
    
    Update();

    StartDraw();

    Vec4 color(1, 1, 1, 1);

    //float x = 0.5f * float(mnWidth);
    float y = 0.5f * float(mnHeight);


    DrawRectangleR(0, 0, float(mnWidth), float(mnHeight), 
        Vec4(0, 0, 0, 0.5f), FILL_ON);


    DrawTextR(infoText.c_str(), 5.0f, y, monospacedFont.get(),
        color, fontSize, LEFT_CENTER, float(mnWidth)-10.0f);


	FinishDraw();

}



void tcAircraftInfoPopup::OnLButtonDown(wxMouseEvent& event)
{
    DestroyWindow();
}

void tcAircraftInfoPopup::Update()
{
    infoText.clear();

    tcSimState* simState = tcSimState::Get();

    tcAeroAirObject* air = dynamic_cast<tcAeroAirObject*>(simState->GetObject(id));
    if (air == 0)
    {
        infoText = "Jets only";
        DestroyWindow();
        return;
    }

    tcUnits* units = tcUnits::Get();

    float startAltitude_m;
    float stopAltitude_m;
    float step_m;
    if (strcmp(units->GetAltitudeUnitLabel(0), "ft") == 0)
    {
        startAltitude_m = C_FTTOM * 0;
        stopAltitude_m = C_FTTOM * 40000;
        step_m = C_FTTOM * 5000;
    }
    else // assume meters
    {
        startAltitude_m = 0;
        stopAltitude_m = 25000;
        step_m = 1000;
    }

    stopAltitude_m = std::min(air->mpDBObject->maxAltitude_m, stopAltitude_m);

    wxString s;
    s.Printf("SPEED ALT RANGE Table for %s (%s)\n", air->mzUnit.c_str(), air->mzClass.c_str());
    infoText += s;
    s.Printf("Click window to dismiss\n\n");
    infoText += s;

    s.Printf("   Alt      Vmil     Vab     Vcruise  Rcruise[km]\n");
    infoText += s;

    for (float altitude_m = startAltitude_m; altitude_m < stopAltitude_m; altitude_m += step_m)
    {
        wxString s;

        float maxSpeedMil_mps;
        float fuelRateMil_kgps;
        air->CalculateSpeedParams(altitude_m, 1.0f, maxSpeedMil_mps, fuelRateMil_kgps, air->GetDamageLevel(), air->mpDBObject);

        float maxSpeedAB_mps;
        float fuelRateAB_kgps;
        air->CalculateSpeedParams(altitude_m, 2.0f, maxSpeedAB_mps, fuelRateAB_kgps, air->GetDamageLevel(), air->mpDBObject);
        
        maxSpeedMil_mps = std::min(maxSpeedMil_mps, air->mpDBObject->mfMaxSpeed_kts*C_KTSTOMPS);
        maxSpeedAB_mps = std::min(maxSpeedAB_mps, air->mpDBObject->mfMaxSpeed_kts*C_KTSTOMPS);

        float cruise_kts = air->GetCruiseSpeedForAltitude(altitude_m);
        float range_km = air->GetCruiseRangeKm(altitude_m);

        std::string speedMil(units->GetUserSpeedString(maxSpeedMil_mps*C_MPSTOKTS));
        std::string speedAB(units->GetUserSpeedString(maxSpeedAB_mps*C_MPSTOKTS));
        std::string speedCruise(units->GetUserSpeedString(cruise_kts));
        wxString cruiseRange = wxString::Format("%.0f km", range_km);

        s.Printf("%05.0f %4s  %8s  %8s  %8s  %8s\n", units->UserAltitudeUnits(altitude_m), units->GetAltitudeUnitLabel(altitude_m),
            speedMil.c_str(),
            speedAB.c_str(),
            speedCruise.c_str(),
            cruiseRange.c_str());


        infoText += s;
    }

   
  


}



/**
*
*/
tcAircraftInfoPopup::tcAircraftInfoPopup(long platformId, const wxPoint& pos, const wxSize& size)
            : tc3DWindow2(parent, pos, size, "AircraftInfo", parent),
              id(platformId)
{
    SetBaseRenderBin(parent->GetBaseRenderBin() + 10);
    Raise();
    birthCount = tcTime::Get()->Get30HzCount();

    SetBorderDraw(true);
}

tcAircraftInfoPopup::~tcAircraftInfoPopup() 
{

}

