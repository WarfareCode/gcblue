/** 
**  @file tcPlatformDebugPopup.cpp 
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

#include "tcPlatformDebugPopup.h"

#include <stdio.h>
#include <iostream>
#include "tcTime.h"
#include "tcSimState.h"
#include "ai/Brain.h"
#include "tcOpticalSensor.h"
#include "tcLOS.h"
#include "tcSonar.h"
#include "nsNav.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif 

tc3DWindow2* tcPlatformDebugPopup::parent = 0;

/**
*
*/
void tcPlatformDebugPopup::SetParent(tc3DWindow2* par)
{
    parent = par;
}




/**
* Clears the text buffer
*/
void tcPlatformDebugPopup::Clear()
{
	messageText = "";
}

/**
*
*/
void tcPlatformDebugPopup::Draw()
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


    DrawTextR(infoText.c_str(), 5.0f, y, defaultFont.get(),
        color, fontSize, LEFT_CENTER, float(mnWidth)-10.0f);


	FinishDraw();

}

void tcPlatformDebugPopup::ForceTargetId(long id_)
{
    forceId = id_;
}



void tcPlatformDebugPopup::OnChar(wxKeyEvent& event)
{
	int nChar = event.GetKeyCode();
	//bool controlDown = event.ControlDown();
	//bool altDown = event.AltDown();

    switch (nChar)
    {
    case 'F':
        if (forceId == -1)
        {
            forceId = 0;
        }
        else
        {
            forceId = -1;
        }
        break;
    case ']':
        if (forceId > -1) forceId++;
        break;
    case '[':
        if (forceId > 1) forceId--;
        break;
    case '0':
        if (forceId != -1)
        {
            forceId = 10*forceId;
        }
        break;
     case '1':
        if (forceId != -1)
        {
            forceId = 10*forceId + 1;
        }
        break;
    case '2':
        if (forceId != -1)
        {
            forceId = 10*forceId + 2;
        }
        break;
    case '3':
        if (forceId != -1)
        {
            forceId = 10*forceId + 3;
        }
        break;
    case '4':
        if (forceId != -1)
        {
            forceId = 10*forceId + 4;
        }
        break;
    case '5':
        if (forceId != -1)
        {
            forceId = 10*forceId + 5;
        }
        break;
    case '6':
        if (forceId != -1)
        {
            forceId = 10*forceId + 6;
        }
        break;
    case '7':
        if (forceId != -1)
        {
            forceId = 10*forceId + 7;
        }
        break;
    case '8':
        if (forceId != -1)
        {
            forceId = 10*forceId + 8;
        }
        break;
    case '9':
        if (forceId != -1)
        {
            forceId = 10*forceId + 9;
        }
        break;
    case WXK_BACK:
        if (forceId != -1)
        {
            forceId = forceId/10;
        }
        break;
    }
}


void tcPlatformDebugPopup::OnLButtonDown(wxMouseEvent& event)
{
    DestroyWindow();
}

void tcPlatformDebugPopup::Update()
{
    infoText.clear();

    tcSimState* simState = tcSimState::Get();

    tcPlatformObject* platform = dynamic_cast<tcPlatformObject*>(simState->GetObject(id));
    if (platform == 0)
    {
        infoText = "No platform";
        DestroyWindow();
        return;
    }

    wxString s;
    long targetId = platform->GetBrain()->GetTarget();
    if ((targetId == -1) && (forceId != -1))
    {
        targetId = forceId;
    }

    tcGameObject* target = simState->GetObject(targetId);

    if (forceId == -1)
    {
        s = wxString::Format("Platform %d, target %d\n", id, targetId);
    }
    else
    {
        s = wxString::Format("Platform %d, target %d (force %d)\n", id, targetId, forceId);
    }

    infoText += s;

    if (target == 0) return;

    float targetAz_rad = nsNav::GCHeadingApprox_rad(platform->mcKin.mfLat_rad, platform->mcKin.mfLon_rad,
        target->mcKin.mfLat_rad, target->mcKin.mfLon_rad);
    float dalt_m = target->mcKin.mfAlt_m - platform->mcKin.mfAlt_m;
    float targetRange_km = platform->mcKin.RangeToKmAlt(target->mcKin);
    float targetEl_rad = asinf(dalt_m / (1000.0f*targetRange_km)); // flat earth assumption valid for close range




    unsigned nSensors = platform->GetSensorCount();
    for (unsigned k=0; k<nSensors; k++)
    {
        tcSensorState* sensor = platform->GetSensorMutable(k);
      
        if (tcRadar* radar = dynamic_cast<tcRadar*>(sensor))
        {
            float range_km = -9.9f;
            bool detect = radar->CanDetectTarget(target, range_km);
            wxString detectText = detect ? "DET" : "XXX";
            float margin_dB = radar->last_snr_margin_dB; // SNR margin
            float jam_dB = radar->CalculateJammingDegradation2(targetAz_rad, targetEl_rad);
            float rcs_dBsm = radar->lastTargetRCS_dBsm;
            float el_deg = C_180OVERPI * radar->lastTargetElevation_rad;

            if (!radar->IsActive())
            {
                s.Printf("%d R OFF", k);
            }
            else if (jam_dB == 0)
            {
                s.Printf("%d R %.1f km %.1f dBsm %.1f deg %s %.1f dB",
                    k, range_km, rcs_dBsm, el_deg, detectText.c_str(), margin_dB);
            }
            else
            {
                s.Printf("%d R %.1f km %.1f dBsm %.1f deg %s %.1f dB JAM %.1f dB",
                    k, range_km, rcs_dBsm, el_deg, detectText.c_str(), margin_dB, jam_dB);
            }
            infoText += s;

            bool hasLOS = radar->HasLOS(target);
            if (hasLOS)
            {
                infoText += "\n";
            }
            else
            {
                infoText += " NOLOS\n";
            }
        }
        else if (tcOpticalSensor* optical = dynamic_cast<tcOpticalSensor*>(sensor))
        {
            wxString typeTag = optical->mpDBObj->isIR ? "IR" : "EO";

            float range_km = -9.9f;
            bool detect = optical->CanDetectTarget(target, range_km);
            float sig_dB = optical->lastTargetSignature_dB;
            float margin_dB = optical->last_margin_dB;
            wxString detectText = detect ? "DET" : "XXX";

            if (!optical->IsActive())
            {
                s.Printf("%d %s OFF\n", k, typeTag.c_str());
            }
            else
            {
                s.Printf("%d %s %.1f km %.1f dBs %s %.1f dB\n",
                    k, typeTag.c_str(), range_km, sig_dB, detectText.c_str(), margin_dB);
            }
            infoText += s;
        }
        else if (tcESMSensor* esm = dynamic_cast<tcESMSensor*>(sensor))
        {
            float range_km = -9.9f;
            bool detect = esm->CanDetectTarget(target, range_km);
            float ERP_dBW = esm->last_ERP_dBW;
            float margin_dB = esm->last_margin_dB;
            wxString detectText = detect ? "DET" : "XXX";

            if (!esm->IsActive())
            {
                s.Printf("%d ESM OFF\n", k);
            }
            else
            {
                s.Printf("%d ESM %.1f km %.1f dBW %s %.1f dB\n",
                    k, range_km, ERP_dBW, detectText.c_str(), margin_dB);
            }
            infoText += s;
        }
        else if (tcSonar* sonar = dynamic_cast<tcSonar*>(sensor))
        {
            float range_km = -99.9f;
            bool detect = sonar->CanDetectTarget(target, range_km);
            float margin_dB = sonar->last_snr_excess;
            float TL_dB = sonar->last_TL;

            float NL_dB = -66.0f;
            float SLp = -66.0f;
            float simpleDetRange_km = sonar->CalculateSimpleDetectionRange(target, NL_dB, SLp);



            wxString detectText = detect ? "DET" : "XXX";

            if (!sonar->IsActive())
            {
                s.Printf("%d SON OFF\n", k);
            }
            else
            {
                s.Printf("%d SON %.1f km %s %.1f dB TL %.1f dB, NL %.1f, SLp %.1f, SDR %.1f km\n",
                    k, range_km, detectText.c_str(), margin_dB, TL_dB, NL_dB, SLp, simpleDetRange_km);
            }
            infoText += s;

        }
    }

    GeoPoint p1;
    p1.Set(platform->mcKin.mfLon_rad, platform->mcKin.mfLat_rad, platform->mcKin.mfAlt_m);

    GeoPoint p2;
    p2.Set(target->mcKin.mfLon_rad, target->mcKin.mfLat_rad, target->mcKin.mfAlt_m);

    tcLOS* los = tcLOS::Get();
    infoText += los->GetRayTestData(p1, p2);


}



/**
*
*/
tcPlatformDebugPopup::tcPlatformDebugPopup(long platformId, const wxPoint& pos, const wxSize& size)
            : tc3DWindow2(parent, pos, size, "PlatformDebug", parent),
              id(platformId),
              forceId(-1)
{
    SetBaseRenderBin(parent->GetBaseRenderBin() + 10);
    Raise();
    birthCount = tcTime::Get()->Get30HzCount();

    SetBorderDraw(true);
}

tcPlatformDebugPopup::~tcPlatformDebugPopup() 
{

}

