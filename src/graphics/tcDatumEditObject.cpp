/**  
**  @file tcDatumEditObject.cpp
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

#include "tcDatumEditObject.h"
#include "tcSimState.h"
#include "tcGameObject.h"
#include "common/tcStream.h"
#include "tc3DWindow2.h"
#include "tcMapView.h"
#include "tcGeometry.h"
#include "tcTexture2D.h"
#include "tcUnits.h"
#include "tcAllianceInfo.h"
#include "ai/Brain.h"
#include "ai/BlackboardInterface.h"
#include "ai/tcAttackMission.h"
#include "ai/tcMissionManager.h"
#include "tcCommandQueue.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif 




/**
* Loads state from stream
*/
tcStream& tcDatumEditObject::operator<<(tcStream& stream)
{
    return tcAreaEditObject::operator<<(stream);
}


/**
* Saves state to stream
*/
tcStream& tcDatumEditObject::operator>>(tcStream& stream)
{
    return tcAreaEditObject::operator>>(stream);
}



void tcDatumEditObject::ClearDatum()
{
    geoPoints.clear();
    screenPoints.clear();
    datum.Set(0, 0);

    UpdateSourceData();
}

void tcDatumEditObject::Draw(tc3DWindow2* host)
{
    drawCount++;

    if (!IsDragActive())
    {
        if (updateWhenDragDone)
        {
            UpdateSourceData();
            updateWhenDragDone = false;
        }

        // periodically synch with source data when drag is not active
        if ((drawCount & 0x1F) == 1)
        {
            LoadGeoPointsFromPlatform();
        }
    }

    if (!isActive) return;

    if (CloseRequested())
    {
        FlagForDelete();
        return;
    }

    if (!IsSourceActive())
    {
        FlagForDelete();
        return;
    }
    
    UpdateDrawData();

    Vec4 color = lineColor;

    if (IsDragActive())
    {
        
    }
    else if (missionId == -1)
    {
        color *= 0.5f;
    }
    else
    {
        color *= 0.75f;
    }

    float h = 4.0f;
    host->DrawThickLineR(screenDatum.x-h, screenDatum.y-h, screenDatum.x+h, screenDatum.y+h, 1.41*h, color);


    host->DrawTextR(caption.c_str(), screenDatum.x, screenDatum.y + 4*h, 
        host->GetDefaultFont(), lineColor, 12.0f, tc3DWindow2::CENTER_CENTER);



}



bool tcDatumEditObject::IsSourceActive()
{
    tcSimState* simState = tcSimState::Get();
    tcGameObject* gameObj = simState->GetObject(platformId);
    tcPlatformObject* platform = dynamic_cast<tcPlatformObject*>(gameObj);
    if (platform == 0) return false;

    if (missionId == -1)
    {
        ai::BlackboardInterface bb = platform->GetBrain()->GetBlackboardInterface();
        return (bb.KeyExists("DatumLongitude") && bb.KeyExists("DatumLatitude"));
    }
    else
    {
        tcFlightOpsObject* flightOps = dynamic_cast<tcFlightOpsObject*>(gameObj);
        tcFlightPort* flightPort = flightOps->GetFlightPort();
        if (flightPort == 0) return false;

        ai::tcMissionManager* missionManager = flightPort->GetMissionManager();
        if (missionManager == 0) return false;

        ai::tcAttackMission* mission = dynamic_cast<ai::tcAttackMission*>(missionManager->GetMission(missionId));
        if (mission == 0) return false;

        return mission->HasTargetDatum();
    }


}

void tcDatumEditObject::LoadGeoPointsFromPlatform()
{
    geoPoints.clear();

    tcSimState* simState = tcSimState::Get();
    tcGameObject* gameObj = simState->GetObject(platformId);
    tcPlatformObject* platform = dynamic_cast<tcPlatformObject*>(gameObj);
    if (platform == 0) return;

    if (missionId == -1)
    {
        ai::BlackboardInterface bb = platform->GetBrain()->GetBlackboardInterface();
        if (!bb.KeyExists("DatumLongitude") || !bb.KeyExists("DatumLatitude")) return;

        wxString lonString(bb.ReadMessage("DatumLongitude").c_str());
        wxString latString(bb.ReadMessage("DatumLatitude").c_str());

        double lon_rad = 0;
        double lat_rad = 0;
        lonString.ToDouble(&lon_rad);
        latString.ToDouble(&lat_rad);

        datum.Set(lon_rad, lat_rad);
    }
    else
    {
        tcFlightOpsObject* flightOps = dynamic_cast<tcFlightOpsObject*>(gameObj);
        tcFlightPort* flightPort = flightOps->GetFlightPort();
        if (flightPort == 0) return;

        ai::tcMissionManager* missionManager = flightPort->GetMissionManager();
        if (missionManager == 0) return;

        ai::tcAttackMission* mission = dynamic_cast<ai::tcAttackMission*>(missionManager->GetMission(missionId));
        if (mission != 0)
        {
            datum.Set(mission->GetTargetLon(), mission->GetTargetLat());
        }
    }

    caption = "Target";
}



void tcDatumEditObject::MoveToScreenPoint(const wxPoint& pos)
{
    if (!IsDragActive()) return;
    
    wxPoint deltaPos = pos - moveReferencePoint;
    moveReferencePoint = pos;

    screenDatum.x += deltaPos.x;
    screenDatum.y += deltaPos.y;

    tcPoint updatedDatum = mapView->ScreenToGeo(screenDatum.x, screenDatum.y);
    datum.Set(updatedDatum.x, updatedDatum.y);
}

/**
* @return false if keyCode is valid command for this object
*/
bool tcDatumEditObject::ProcessKey(int keyCode)
{
    switch (keyCode)
    {
    case WXK_DELETE:
        ClearDatum();
        break;
    }

    return tcAreaEditObject::ProcessKey(keyCode);
}


bool tcDatumEditObject::ProcessLButtonDown(const wxPoint& pos)
{
    if (IsPointNearLine(pos))
    {
        dragMode = DRAG_ALL;
        SetDragActive(true);
        updateWhenDragDone = true;
        moveReferencePoint = pos;
        return true;
    }

    return false;
}


/**
* Updates screenPoints with geoPoints data
*/
void tcDatumEditObject::UpdateDrawData()
{
    screenPoints.clear();

    screenDatum = mapView->GeoToScreen(datum.mfLon_rad, datum.mfLat_rad);

    const float h = 8.0f;

    tcPoint p(screenDatum);
    p.x += h;
    screenPoints.push_back(p);

    p.x -= 2*h;
    screenPoints.push_back(p);

    p.x += h;
    p.y += h;
    screenPoints.push_back(p);

    p.y -= 2*h;
    screenPoints.push_back(p);

    if (missionId == -1)
    {
        lineColor.set(0.9f, 1, 0.9f, 0.8f);
    }
    else
    {
        lineColor.set(0.8f, 0.3f, 0.2f, 0.8f);
    }
}


/**
* Updates source data with geoPoints data
*/
void tcDatumEditObject::UpdateSourceData()
{
    tcSimState* simState = tcSimState::Get();
    tcGameObject* gameObj = simState->GetObject(platformId);
    tcPlatformObject* platform = dynamic_cast<tcPlatformObject*>(gameObj);
    if (platform == 0) return;

    if (missionId == -1)
    {
        //ai::BlackboardInterface bb = platform->GetBrain()->GetBlackboardInterface();

        //wxString lonString = wxString::Format("%.7f", datum.mfLon_rad);
        //wxString latString = wxString::Format("%.7f", datum.mfLat_rad);

        //bb.Write("DatumLongitude", lonString.c_str());
        //bb.Write("DatumLatitude", latString.c_str());

        std::vector<long> commandId;
        commandId.push_back(platformId);

        if ((datum.mfLon_rad != 0) || (datum.mfLat_rad != 0))
        {
            wxString args = wxString::Format(",%.7f,%.7f", datum.mfLon_rad, datum.mfLat_rad);
            commandInterface->AddPythonCommandGeneral("SetTargetDatum", args.ToStdString(), commandId);
        }
        else
        {
            commandInterface->AddPythonCommandGeneral("ClearTargetDatum", "", commandId);
        }
    }
    else
    {
        tcFlightOpsObject* flightOps = dynamic_cast<tcFlightOpsObject*>(gameObj);
        tcFlightPort* flightPort = flightOps->GetFlightPort();
        if (flightPort == 0) return;

        ai::tcMissionManager* missionManager = flightPort->GetMissionManager();
        if (missionManager == 0) return;

        ai::tcAttackMission* mission = dynamic_cast<ai::tcAttackMission*>(missionManager->GetMission(missionId));
        if (mission == 0) return;

        wxString args = wxString::Format(",%.7f,%.7f,%d", datum.mfLon_rad, datum.mfLat_rad, missionId);

        std::vector<long> commandId;
        commandId.push_back(platformId);
        commandInterface->AddPythonCommandGeneral("SetMissionDatum", args.ToStdString(), commandId);
    }

}


tcDatumEditObject::tcDatumEditObject(long platformId_, long missionId_)
: platformId(platformId_), missionId(missionId_)
{
    LoadGeoPointsFromPlatform();
}


tcDatumEditObject::~tcDatumEditObject()
{

}

