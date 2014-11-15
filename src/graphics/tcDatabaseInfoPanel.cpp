/** 
**  @file tcDatabaseInfoPanel.cpp 
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

#include "tcDatabaseInfoPanel.h"
#include "tcDatabaseObject.h"
#include "tcPlatformDBObject.h"
#include "tcLauncherDBObject.h"
#include "tcMissileDBObject.h"
#include "tcTorpedoDBObject.h"
#include "tcShipDBObject.h"
#include "tcSubDBObject.h"
#include "tcAirDBObject.h"
#include "tcGroundDBObject.h"
#include "tc3DModel.h"
#include "tcSensorMap.h"
#include "tcSimState.h"
#include "common/tinyxml.h"
#include "tcTime.h"
#include "tcScrollBar.h"
#include "tcGeometry.h"
#include "tcUnits.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


BEGIN_EVENT_TABLE(tcDatabaseInfoPanel, tc3DWindow2)
    EVT_COMMAND(-1, wxEVT_COMMAND_SCROLLBAR_UPDATED, tcDatabaseInfoPanel::OnScrollbarUpdated)
END_EVENT_TABLE()



using database::tcDatabaseObject;




void tcDatabaseInfoPanel::Draw() 
{
    StartDraw();

	//if (!IsBackgroundEnabled())
	//{
	//	DrawRectangleR(0, 0, mnWidth, mnHeight, Vec4(0.15, 0.15, 0.15, 1.0f), 
	//		FILL_ON);
	//}

	DrawDatabaseInfo();

	//DrawBorder();

	FinishDraw();
}


void tcDatabaseInfoPanel::DrawDatabaseInfo()
{
	wxString s;

	tcDatabaseObject* databaseObj = GetDatabaseObject();

	if (databaseObj == 0) return;

	const float yStart = 20.0f;
	const float maxSpan = float(mnHeight);

    float textx = 2.0f;
//	float maxWidth = float(mnWidth) - textx - 5.0f;
    float texty = yStart;
	tcRect textBox;

	Vec4 color(0.4f, 1.0f, 0.4f, 1.0f);

	texty -= yOffset;


    PrintText(textx, texty, "Unit cost: %s", databaseObj->GetCostString());

	PrintText(textx, texty, "%s", databaseObj->mzDescription.c_str());


    texty += 5.0f;

    yCurrent = texty; // important to initialize for sub case

    if (tcShipDBObject* shipData = dynamic_cast<tcShipDBObject*>(databaseObj))
    {
        DrawDatabaseInfo(shipData, texty);
    }
    else if (tcAirDBObject* airData = dynamic_cast<tcAirDBObject*>(databaseObj))
    {
        DrawDatabaseInfo(airData, texty);
    }
    else if (tcGroundDBObject* groundData = dynamic_cast<tcGroundDBObject*>(databaseObj))
    {
        DrawDatabaseInfo(groundData, texty);
    }
    else if (tcSubDBObject* subData = dynamic_cast<tcSubDBObject*>(databaseObj))
    {
        DrawDatabaseInfo(subData, texty);
    }
    else if (tcMissileDBObject* missile = dynamic_cast<tcMissileDBObject*>(databaseObj))
    {
        DrawDatabaseInfo(missile, texty);
    }
    else if (tcTorpedoDBObject* torpedo = dynamic_cast<tcTorpedoDBObject*>(databaseObj))
    {
        DrawDatabaseInfo(torpedo, texty);
    }

	// update scroll bar (only need to do this once per database object)
	float ySpan = yCurrent + yOffset - yStart + 25.0f;
	
	scrollBar->SetBarFraction(maxSpan / ySpan);
}


    void DrawDatabaseInfo(database::tcShipDBObject* shipData, float yStart);
    void DrawDatabaseInfo(database::tcAirDBObject* airData, float yStart);
    void DrawDatabaseInfo(database::tcGroundDBObject* groundData, float yStart);


void tcDatabaseInfoPanel::DrawDatabaseInfo(database::tcShipDBObject* shipData, float yStart)
{
    float textx = 10.0f;
//	float maxWidth = float(mnWidth) - textx - 5.0f;
    float texty = yStart;
	tcRect textBox;
	Vec4 color(0.4f, 1.0f, 0.4f, 1.0f);


    PrintText(textx, texty, "Max speed: %s", units->GetUserSpeedString(shipData->mfMaxSpeed_kts));

    if (IsEmbedded())
    {
        PrintText(textx, texty, "Turn rate: %.1f deg/s", shipData->mfTurnRate_degps);
    }

    
    //PrintText(textx, texty, "Survivability: %.0f", shipData->mfToughness);

    PrintText(textx, texty, "RCS %.0f dBsm", shipData->RCS_dBsm);

    if ((shipData->mfFuelRate_kgps > 0) && IsEmbedded())
    {
		float fuelTimeHours = 2.778e-4 * shipData->GetInternalFuelCapacity() / shipData->mfFuelRate_kgps;

        switch (shipData->mnModelType)
        {
        case MTYPE_SURFACE:
        case MTYPE_CARRIER:
            PrintText(textx, texty, "Cruise range %.0f %s", 
                units->UserDistanceUnits(fuelTimeHours * shipData->mfMaxSpeed_kts * C_NMITOM),
                units->GetDistanceUnitLabel());
            break;
        default:
            PrintText(textx, texty, "MODEL TYPE ERROR (%d)", shipData->mnModelType);
            break;
        }
    }

    texty += 10.0f;
    DrawLauncherInfo(shipData, texty);

    texty += 10.0f;
    DrawSensorInfo(shipData, texty);

	yCurrent = texty;
}


void tcDatabaseInfoPanel::DrawDatabaseInfo(database::tcSubDBObject* subData, float yStart)
{
    float textx = 10.0f;
//	float maxWidth = float(mnWidth) - textx - 5.0f;
    float texty = yStart;
	tcRect textBox;
	Vec4 color(0.4f, 1.0f, 0.4f, 1.0f);


    PrintText(textx, texty, "Max speed: %s", units->GetUserSpeedString(subData->mfMaxSpeed_kts));

    texty += 10.0f;
    DrawLauncherInfo(subData, texty);

    texty += 10.0f;
    DrawSensorInfo(subData, texty);

	yCurrent = texty;
}


void tcDatabaseInfoPanel::DrawDatabaseInfo(database::tcAirDBObject* airData, float yStart)
{
    float textx = 10.0f;
//	float maxWidth = float(mnWidth) - textx - 5.0f;
    float texty = yStart;
	tcRect textBox;
	Vec4 color(0.4f, 1.0f, 0.4f, 1.0f);


    PrintText(textx, texty, "Max speed: %s", units->GetUserSpeedString(airData->mfMaxSpeed_kts));

    if (IsEmbedded())
    {
        PrintText(textx, texty, "Turn rate: %.1f deg/s", airData->mfTurnRate_degps);
    }

    
    //PrintText(textx, texty, "Survivability: %.0f", airData->mfToughness);

    PrintText(textx, texty, "RCS %.0f dBsm", airData->RCS_dBsm);

    if ((airData->mfFuelRate_kgps > 0) && IsEmbedded())
    {
		float fuelTimeHours = 2.778e-4 * airData->GetInternalFuelCapacity() / airData->mfFuelRate_kgps;

        switch (airData->mnModelType)
        {
        case MTYPE_AIR:
        case MTYPE_FIXEDWING:
            PrintText(textx, texty, "Cruise range %.0f %s", 
                units->UserDistanceUnits(fuelTimeHours * airData->mfMaxSpeed_kts * C_NMITOM),
                units->GetDistanceUnitLabel());
            break;
        case MTYPE_FIXEDWINGX:
            PrintText(textx, texty, "Internal fuel cap %s", 
                units->GetUserMassString(airData->GetInternalFuelCapacity()));
            break;
        case MTYPE_HELO:
            PrintText(textx, texty, "Endurance %.1f hrs", 2.0f * fuelTimeHours);
            break;
        default:
            PrintText(textx, texty, "MODEL TYPE ERROR (%d)", airData->mnModelType);
            break;
        }
    }

    
    if (airData->outFuelPods > 0)
    {
        PrintText(textx, texty, "In-flight refuel tanker");
    }
    else if (airData->fuelIn_kgps > 0)
    {
        PrintText(textx, texty, "In-flight refuel capable");
    }

    texty += 10.0f;
    DrawLauncherInfo(airData, texty);

    texty += 10.0f;
    DrawSensorInfo(airData, texty);

	yCurrent = texty;
}


void tcDatabaseInfoPanel::DrawDatabaseInfo(database::tcGroundDBObject* groundData, float yStart)
{
    float textx = 10.0f;
//	float maxWidth = float(mnWidth) - textx - 5.0f;
    float texty = yStart;
	tcRect textBox;
	Vec4 color(0.4f, 1.0f, 0.4f, 1.0f);


    if (groundData->mfMaxSpeed_kts > 0)
    {
        PrintText(textx, texty, "Max speed: %s", units->GetUserSpeedString(groundData->mfMaxSpeed_kts));

        if (IsEmbedded())
        {
            PrintText(textx, texty, "Turn rate: %.1f deg/s", groundData->mfTurnRate_degps);
        }
    }

    
    //PrintText(textx, texty, "Survivability: %.0f", groundData->mfToughness);

    PrintText(textx, texty, "RCS %.0f dBsm", groundData->RCS_dBsm);


    texty += 10.0f;
    DrawLauncherInfo(groundData, texty);

    texty += 10.0f;
    DrawSensorInfo(groundData, texty);

	yCurrent = texty;
}


void tcDatabaseInfoPanel::DrawDatabaseInfo(database::tcMissileDBObject* missileData, float yStart)
{
    wxASSERT(missileData);

    float textx = 10.0f;
    float texty = yStart;

    PrintText(textx, texty, "Range %s", units->GetUserDistanceString(1000.0f*missileData->maxRange_km));

    PrintText(textx, texty, "Max speed Mach %.1f", missileData->mfMsupm);

    PrintText(textx, texty, "Warhead %s", units->GetUserMassString(missileData->mfDamage));
    
    PrintText(textx, texty, "Seeker FOV %.0f deg", C_180OVERPI*missileData->GetSeekerFOV());

	yCurrent = texty;
}

void tcDatabaseInfoPanel::DrawDatabaseInfo(database::tcTorpedoDBObject* torpedoData, float yStart)
{
    wxASSERT(torpedoData);

    float textx = 10.0f;
    float texty = yStart;

    if (torpedoData->batteryRate_kW > 0)
    {
        float range_m = 2.778e-4f * C_NMITOM * torpedoData->maxSpeed_kts * torpedoData->battery_kJ / 
            torpedoData->batteryRate_kW;
        PrintText(textx, texty, "Range %s", units->GetUserDistanceString(range_m));
    }
    else
    {
        PrintText(textx, texty, "Nominal range %s", units->GetUserDistanceString(1000.0f*torpedoData->maxRange_km));
    }

    PrintText(textx, texty, "Max speed %s", units->GetUserSpeedString(torpedoData->maxSpeed_kts));

    PrintText(textx, texty, "Warhead %s", units->GetUserMassString(torpedoData->mfDamage));

	yCurrent = texty;
}


void tcDatabaseInfoPanel::DrawLauncherInfo(database::tcPlatformDBObject* genericData, float& y)
{
    wxASSERT(genericData != 0);

    int nLaunchers = genericData->mnNumLaunchers;
    if (nLaunchers <= 0) return;

    PrintText(10.0, y, "MOUNTS");

    database::tcDatabase* database = tcDatabase::Get();

    for (int n=0; n<nLaunchers; n++)
    {
        std::string launcherClass = genericData->maLauncherClass[n];
        database::tcLauncherDBObject* launcherData = 
            dynamic_cast<database::tcLauncherDBObject*>(
            database->GetObject(launcherClass));
        wxString s;
		if (launcherData != 0)
		{
			s = launcherData->GetConfigurationDescription();
		}
		else
		{
			s.Printf("ERROR: Launcher not found (%s)", launcherClass.c_str());
		}

		if (s.size() > 300)
		{
			s = s.SubString(0, 299) + "...";
		}

		std::string s2(s.ToStdString());

		PrintText(20.0, y, "%s", s2.c_str());
    }  
}

void tcDatabaseInfoPanel::DrawSensorInfo(database::tcPlatformDBObject* genericData, float& y)
{
    wxASSERT(genericData != 0);

    int nSensors = genericData->sensorClass.size();
    if (nSensors <= 0) return;

    database::tcDatabase* database = tcDatabase::Get();

    PrintText(10.0, y, "SENSORS");

    for (int n=0; n<nSensors; n++)
    {
        std::string& sensorClass = genericData->sensorClass[n];
        database::tcSensorDBObject* sensorData = dynamic_cast<database::tcSensorDBObject*>(
            database->GetObject(sensorClass));
        if (sensorData != 0)
        {
            //float displayRange = 0;
            //if (radarData->mbDetectsAir) displayRange = 2.0f * radarData->mfRefRange_km; // 12 dBsm assumed
            //else displayRange = 5.66f * radarData->mfRefRange_km; // 30 dBsm assumed

            //PrintText(20.0, y, "%s (%.0f %s)", sensorClass.c_str(), 
            //    units->UserDistanceUnits(1000.0f*displayRange), units->GetDistanceUnitLabel());
            PrintText(20.0, y, "%s (%s)", sensorClass.c_str(), sensorData->GetTypeDescription());

        }
        else
        {
            PrintText(20.0, y, "%s", sensorClass.c_str());
        }
    }   
}

void tcDatabaseInfoPanel::PrintText(float x, float& y, const char* formatString, ...)
{
    enum {STR_LENGTH = 1024};
    static char textBuffer[STR_LENGTH];

    static Vec4 color(0.4f, 1.0f, 0.4f, 1.0f);
    static tcRect textBox;

    const float textFontSize = 12.0f;

    //if (y > float(mnHeight) - 15.0f) return;

    va_list arguments;

    va_start(arguments, formatString);
    _vsnprintf_s(textBuffer, sizeof(textBuffer), _TRUNCATE, formatString, arguments);
    va_end(arguments);

    float maxWidth = float(mnWidth - 20) - x;

    wxString wrappedText;
    wxSize wrappedSize;
    WrapTextToWidth(defaultFont.get(), textFontSize, textBuffer, 
                    maxWidth, wrappedSize, wrappedText); 

    DrawTextR(wrappedText.c_str(), x, y, 
			defaultFont.get(), color, textFontSize, LEFT_TOP, maxWidth, textBox);

    y += textBox.Height() + 2.0f;
    
}

void tcDatabaseInfoPanel::OnEnterWindow(wxMouseEvent& event)
{
    SetFocus(); // to receive mousewheel events
}

void tcDatabaseInfoPanel::OnMouseWheel(wxMouseEvent& event)
{
    wxASSERT(scrollBar != 0);

    scrollBar->OnMouseWheel(event);
}



void tcDatabaseInfoPanel::OnScrollbarUpdated(wxCommandEvent& event)
{
    yOffset = 0.25 * float(event.GetExtraLong());
}


database::tcDatabaseObject* tcDatabaseInfoPanel::GetDatabaseObject()
{
	if (databaseClassName.size() > 1)
	{
		return tcDatabase::Get()->GetObject(databaseClassName);
	}

	tcSimState* simState = tcSimState::Get();
	tcGameObject* obj = simState->GetObject(objId);
	if ((obj != 0) && (obj->IsOwnAlliance()))
	{
		databaseClassName = obj->mpDBObject->mzClass.c_str();
		return obj->mpDBObject;
	}
	else
	{
		tcSensorMap* sensorMap = simState->GetSensorMap();
		wxASSERT(sensorMap != 0);
		tcSensorMapTrack* track = sensorMap->GetSensorMapTrack(objId, tcUserInfo::Get()->GetOwnAlliance());
		if (track)
		{
			return tcDatabase::Get()->GetObject(track->GetDatabaseId());
		}
		else
		{
			return 0;
		}
	}
}


bool tcDatabaseInfoPanel::IsEmbedded() const
{
    return (viewMode == EMBED);
}

bool tcDatabaseInfoPanel::IsPopup() const
{
    return (viewMode == POPUP);
}





void tcDatabaseInfoPanel::SetDatabaseClassName(const std::string& className)
{
    databaseClassName = className;
	yOffset = 0;
}

void tcDatabaseInfoPanel::SetDatabaseObject(long id)
{
	objId = id;
	databaseClassName = "";
	yOffset = 0;
}

void tcDatabaseInfoPanel::SetViewMode(int mode)
{
	viewMode = (ViewMode)mode;
}


/**
* if hostParent argument is not used then static method SetParent must be called first
*/
tcDatabaseInfoPanel::tcDatabaseInfoPanel(wxWindow* parent, const wxPoint& pos, const wxSize& size, 
										 const wxString& name, tc3DWindow2* graphicsHost) 
    : tc3DWindow2(parent, pos, size, name, graphicsHost),
	objId(-1),
	databaseClassName(""),
	viewMode(EMBED),
	yOffset(0),
    units(tcUnits::Get())
{

	wxASSERT(hostParent != 0);

	// put gui window on top
	SetBaseRenderBin(hostParent->GetBaseRenderBin() + 10);
	wxWindow::Raise();

	int scrollBarWidth = 16;

    SetUseRenderSurface(true, scrollBarWidth+1);
	

    SetBackgroundColor(Vec4(0, 0, 0.1f, 0.1f));
    SetBackgroundDraw(true);
	SetActive(true);
	SetStencilLayer(hostParent->GetBaseRenderBin()/ 8);

	scrollBar = new tcScrollBar(this, wxPoint(mnWidth-scrollBarWidth, 0), wxSize(scrollBarWidth, mnHeight));
	scrollBar->SetBackgroundAlpha(0.7f);
    scrollBar->SetUseRenderSurface(true);

}

tcDatabaseInfoPanel::~tcDatabaseInfoPanel() 
{

}


