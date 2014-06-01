/**  
**  @file tcPlatformAreaEditObject.cpp
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

#include "tcPlatformAreaEditObject.h"
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


boost::shared_ptr<tcGeometry> tcPlatformAreaEditObject::anchorOnIcon;
boost::shared_ptr<tcGeometry> tcPlatformAreaEditObject::anchorOffIcon;

void tcPlatformAreaEditObject::LoadAnchorIcons(const std::string& filename_on, const std::string& filename_off)
{
    float w = 16.0f;
	
    anchorOnIcon = boost::shared_ptr<tcGeometry>(new tcGeometry);
    tcTexture2D* texOn = new tcTexture2D(filename_on);
    anchorOnIcon->MakeTexturedSymbol(boost::shared_ptr<tcTexture2D>(texOn), w);

    anchorOffIcon = boost::shared_ptr<tcGeometry>(new tcGeometry);
    tcTexture2D* texOff = new tcTexture2D(filename_off);
    anchorOffIcon->MakeTexturedSymbol(boost::shared_ptr<tcTexture2D>(texOff), w);
}

/**
* Loads state from stream
*/
tcStream& tcPlatformAreaEditObject::operator<<(tcStream& stream)
{
    return tcAreaEditObject::operator<<(stream);
}


/**
* Saves state to stream
*/
tcStream& tcPlatformAreaEditObject::operator>>(tcStream& stream)
{
    return tcAreaEditObject::operator>>(stream);
}


/**
* Erase this patrol area
*/
void tcPlatformAreaEditObject::ClearArea()
{
    geoPoints.clear();
    screenPoints.clear();
    UpdateSourceData();
}


void tcPlatformAreaEditObject::Draw(tc3DWindow2* host)
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

    UpdateVisibility();
    if (!isVisible) return;

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

    color.v[3] = fadeInAlpha;

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

    size_t dragPoint = ((dragMode == DRAG_POINT) && IsDragActive()) ? dragPointIdx : 99999;


    float ymin = 9999.0f;
    float ymax = -9999.0f;
    float xmin = 9999.0f;
    float xmax = -9999.0f;
    for (size_t n=0; n<screenPoints.size(); n++)
    {
        size_t n1 = n;
        size_t n2 = (n + 1) % screenPoints.size();
        //host->DrawLineR(screenPoints[n1].x, screenPoints[n1].y, screenPoints[n2].x, screenPoints[n2].y, color);
        host->DrawThickLineR(screenPoints[n1].x, screenPoints[n1].y, screenPoints[n2].x, screenPoints[n2].y, 2.0f, color);

        ymin = std::min(screenPoints[n1].y, ymin);
        ymax = std::max(screenPoints[n1].y, ymax);
        xmin = std::min(screenPoints[n1].x, xmin);
        xmax = std::max(screenPoints[n1].x, xmax);
    }

    // draw points separately so they are on top
    for (size_t n=0; n<screenPoints.size(); n++)
    {
        size_t n1 = n;
        
        if (n != dragPoint)
        {
            host->DrawGeometryR(cornerMarkerOff.get(), screenPoints[n1].x, screenPoints[n1].y);
        }
        else
        {
            host->DrawGeometryR(cornerMarkerOn.get(), screenPoints[n1].x, screenPoints[n1].y);
        }
    }

    if (screenPoints.size() > 0)
    {
        host->DrawTextR(caption.c_str(), 0.5f*(xmin+xmax),  0.5f*(ymin+ymax), 
            host->GetDefaultFont(), lineColor, 12.0f, tc3DWindow2::CENTER_CENTER);

        float xm = anchorModeSelect.XCenter();
        float ym = anchorModeSelect.YCenter();

        if (anchorMode != 0)
        {
            host->DrawGeometryR(anchorOnIcon.get(), xm, ym);
        }
        else
        {
            host->DrawGeometryR(anchorOffIcon.get(), xm, ym);
        }

        host->DrawRectangleR(anchorModeSelect, lineColor, tc3DWindow2::FILL_OFF);

        if (anchorMode > 0)
        {
            wxString s(anchorUnit);
            if (anchorMode == 1) s += " (North Ref)";
            else if (anchorMode == 2) s += " (Heading Ref)";
            host->DrawTextR(s.c_str(), anchorModeSelect.XCenter(), anchorModeSelect.GetTop() + 20.0f, host->GetDefaultFont(),
                lineColor, 12.0f, tc3DWindow2::CENTER_CENTER);
        }
    }


}


bool tcPlatformAreaEditObject::IsSourceActive()
{
    tcSimState* simState = tcSimState::Get();
    tcGameObject* gameObj = simState->GetObject(platformId);
    tcPlatformObject* platform = dynamic_cast<tcPlatformObject*>(gameObj);

    if (platform == 0) return false;

    if (missionId == -1)
    {
        ai::BlackboardInterface bb = platform->GetBrain()->GetBlackboardInterface();
        return bb.KeyExists("PatrolArea");
    }
    else
    {
        tcFlightOpsObject* flightOps = dynamic_cast<tcFlightOpsObject*>(gameObj);
        tcFlightPort* flightPort = flightOps->GetFlightPort();
        if (flightPort == 0) return false;

        ai::tcMissionManager* missionManager = flightPort->GetMissionManager();
        if (missionManager == 0) return false;

        ai::tcAttackMission* mission = dynamic_cast<ai::tcAttackMission*>(missionManager->GetMission(missionId));
        return (mission != 0);
    }
}

void tcPlatformAreaEditObject::LoadAnchorInfoFromPlatform(ai::BlackboardInterface& bb)
{
    anchorMode = 0;
    anchorUnit.clear();

    // PatrolAnchor: <anchor unitname>,<anchor lon>,<anchor lat>,<anchor mode>
    if (!bb.KeyExists("PatrolAnchor"))
    {
        return;
    }

    wxString anchorString(bb.ReadMessage("PatrolAnchor").c_str());

    anchorUnit = anchorString.BeforeFirst(',');
    wxString smode = anchorString.AfterFirst(',');

    anchorString = anchorString.Trim();

    long val = 0;
    if (smode.ToLong(&val))
    {
        anchorMode = int(val);
    }
    else
    {
        wxASSERT(false); // bad anchor string
        anchorUnit.clear();
    }

}

void tcPlatformAreaEditObject::LoadGeoPointsFromPlatform()
{
    geoPoints.clear();

    tcSimState* simState = tcSimState::Get();
    tcGameObject* gameObj = simState->GetObject(platformId);
    tcPlatformObject* platform = dynamic_cast<tcPlatformObject*>(gameObj);
    if (platform == 0) return;

    if (missionId == -1)
    {

        ai::BlackboardInterface bb = platform->GetBrain()->GetBlackboardInterface();


        if (!bb.KeyExists("PatrolArea")) return;

        LoadAnchorInfoFromPlatform(bb);

        wxString areaString(bb.ReadMessage("PatrolArea").c_str());

        wxString slon = areaString.BeforeFirst(',');
        areaString = areaString.AfterFirst(',');
        wxString slat = areaString.BeforeFirst(',');
        areaString = areaString.AfterFirst(',');

        while (slat.size() > 0)
        {
            double lon_rad = 0;
            double lat_rad = 0;
            slon.ToDouble(&lon_rad);
            slat.ToDouble(&lat_rad);

            GeoPoint p;
            p.Set(lon_rad, lat_rad, 0);
            geoPoints.push_back(p);

            slon = areaString.BeforeFirst(',');
            areaString = areaString.AfterFirst(',');
            slat = areaString.BeforeFirst(',');
            areaString = areaString.AfterFirst(',');
        }
    }
    else
    {
        tcFlightOpsObject* flightOps = dynamic_cast<tcFlightOpsObject*>(gameObj);
        tcFlightPort* flightPort = flightOps->GetFlightPort();
        if (flightPort == 0) return;

        ai::tcMissionManager* missionManager = flightPort->GetMissionManager();
        if (missionManager == 0) return;

        if (ai::tcAttackMission* mission = dynamic_cast<ai::tcAttackMission*>(missionManager->GetMission(missionId)))
        {
            geoPoints = mission->GetArea();
            anchorMode = mission->GetPatrolAnchorMode();
            anchorUnit = mission->GetPatrolAnchorUnit();
        }
    }

    caption = "Patrol Area";
}

void tcPlatformAreaEditObject::MoveToScreenPoint(const wxPoint& pos)
{
    if (!IsDragActive()) return;

    tcAreaEditObject::MoveToScreenPoint(pos);
    
    ai::Brain::TransformPatrolAreaForAnchor(geoPoints, anchorUnit, anchorMode, false);
}


/**
* @return false if keyCode is valid command for this object
*/
bool tcPlatformAreaEditObject::ProcessKey(int keyCode)
{
    if (!isVisible) return false;

    switch (keyCode)
    {
    case WXK_DELETE:
        ClearArea();
        break;
    }

    return tcAreaEditObject::ProcessKey(keyCode);
}


bool tcPlatformAreaEditObject::ProcessLButtonDown(const wxPoint& pos)
{
    if (!isVisible) return false;

    if (anchorModeSelect.ContainsPoint(pos.x, pos.y))
    {
        ToggleAnchorMode();
        return true;
    }
    else
    {
        return tcAreaEditObject::ProcessLButtonDown(pos);
    }
}

void tcPlatformAreaEditObject::ToggleAnchorMode()
{
    std::vector<GeoPoint> worldPoints(geoPoints);
    ai::Brain::TransformPatrolAreaForAnchor(worldPoints, anchorUnit, anchorMode, true);

    anchorMode = (anchorMode == 0) ? 2 : 0; // skip 1 (north ref) for now

    if (anchorMode == 0)
    {
        anchorUnit.clear();
    }
    else if ((anchorUnit.size() == 0) && (missionId != -1))
    {   // use flightport as default anchor
        tcSimState* simState = tcSimState::Get();
        if (tcGameObject* gameObj = simState->GetObject(platformId))
        {
            anchorUnit = gameObj->mzUnit.c_str();
        }
    }
    else if (anchorUnit.size() == 0) // only use platformId as anchor for missions
    {
        anchorMode = 0;
    }

    geoPoints = worldPoints;
    ai::Brain::TransformPatrolAreaForAnchor(geoPoints, anchorUnit, anchorMode, false);
    UpdateSourceData();
}


/**
* Updates screenPoints with geoPoints data
*/
void tcPlatformAreaEditObject::UpdateDrawData()
{
    // if anchorMode isn't zero, calculate screen coordinates based on transformed coordinates
    if (anchorMode == 0)
    {
        tcAreaEditObject::UpdateDrawData();
    }
    else
    {
        std::vector<GeoPoint> transformedPoints(geoPoints);
        ai::Brain::TransformPatrolAreaForAnchor(transformedPoints, anchorUnit, anchorMode, true);

        screenPoints.clear();
        for (size_t n=0; n<transformedPoints.size(); n++)
        {
            tcPoint p = mapView->GeoToScreen(transformedPoints[n].mfLon_rad, transformedPoints[n].mfLat_rad);
            screenPoints.push_back(p);
        }
    }


    if (missionId == -1)
    {
        lineColor.set(0.9f, 1, 0.9f, 0.8f);
    }
    else
    {
        lineColor.set(0.8f, 0.3f, 0.2f, 0.6f);
    }


    if (screenPoints.size() > 0)
    {

        float ymin = 9999.0f;
        float ymax = -9999.0f;
        float xmin = 9999.0f;
        float xmax = -9999.0f;
        for (size_t n=0; n<screenPoints.size(); n++)
        {
            ymin = std::min(screenPoints[n].y, ymin);
            ymax = std::max(screenPoints[n].y, ymax);
            xmin = std::min(screenPoints[n].x, xmin);
            xmax = std::max(screenPoints[n].x, xmax);
        }

        float x = 0.5*(xmin + xmax);
        float y = 0.5*(ymin + ymax) - 15.0f;
        
        const float hw = 8.0f;
        anchorModeSelect.Set(x - hw, x + hw, y - hw, y + hw);
    }
    else
    {
        anchorModeSelect.Set(0, 0, 0, 0);
    }
}

void tcPlatformAreaEditObject::UpdateAnchorSourceData()
{
    wxString s;

    s.Printf("'%s',%d", anchorUnit.c_str(), anchorMode);

    if (missionId == -1)
    {
        wxString args = wxString::Format(",%s", s.c_str());

        std::vector<long> commandId;
        commandId.push_back(platformId);
        commandInterface->AddPythonCommandGeneral("SetPatrolAnchor", args.ToStdString(), commandId);
    }
    else
    {
        tcSimState* simState = tcSimState::Get();
        tcGameObject* gameObj = simState->GetObject(platformId);
        tcFlightOpsObject* flightOps = dynamic_cast<tcFlightOpsObject*>(gameObj);
        tcFlightPort* flightPort = flightOps->GetFlightPort();
        if (flightPort == 0) return;

        ai::tcMissionManager* missionManager = flightPort->GetMissionManager();
        if (missionManager == 0) return;

        ai::tcAttackMission* mission = dynamic_cast<ai::tcAttackMission*>(missionManager->GetMission(missionId));
        if (mission == 0) return;

        wxString args = wxString::Format(",%d,%s", missionId, s.c_str());

        std::vector<long> commandId;
        commandId.push_back(platformId);
        commandInterface->AddPythonCommandGeneral("SetMissionPatrolAnchor", args.ToStdString(), commandId);
    }
}


/**
* Updates source data with geoPoints data
*/
void tcPlatformAreaEditObject::UpdateSourceData()
{
    tcSimState* simState = tcSimState::Get();
    tcGameObject* gameObj = simState->GetObject(platformId);
    tcPlatformObject* platform = dynamic_cast<tcPlatformObject*>(gameObj);
    if (platform == 0) return;

    wxString s("'");
    for (size_t n=0; n<geoPoints.size(); n++)
    {
        s += wxString::Format("%.7f,%.7f,", geoPoints[n].mfLon_rad, geoPoints[n].mfLat_rad);
    }
    s += "'";

    if (missionId == -1)
    {
        wxString args = wxString::Format(",%s", s.c_str());

        std::vector<long> commandId;
        commandId.push_back(platformId);
        commandInterface->AddPythonCommandGeneral("SetPatrolAreaString", args.ToStdString(), commandId);

        //ai::BlackboardInterface bb = platform->GetBrain()->GetBlackboardInterface();
        //bb.Write("PatrolArea", s.c_str());
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

        wxString args = wxString::Format(",%d,%s", missionId, s.c_str());

        std::vector<long> commandId;
        commandId.push_back(platformId);
        commandInterface->AddPythonCommandGeneral("SetMissionPatrolAreaString", args.ToStdString(), commandId);
    }

    UpdateAnchorSourceData();
}


tcPlatformAreaEditObject::tcPlatformAreaEditObject(long platformId_, long missionId_)
: platformId(platformId_), missionId(missionId_), anchorMode(0)
{
    LoadGeoPointsFromPlatform();

    if (anchorOnIcon.get() == 0)
    {
        LoadAnchorIcons("images\\anchor.png", "images\\anchor_off.png");
    }

    if (missionId != -1)
    {
        anchorOnIcon->SetColor(Vec4(0.8f, 0.2f, 0.2f, 0.8f));
        anchorOffIcon->SetColor(Vec4(0.8f, 0.2f, 0.2f, 0.8f));
    }
    else
    {
        anchorOnIcon->SetColor(Vec4(1, 1, 1, 0.8f));
        anchorOffIcon->SetColor(Vec4(1, 1, 1, 0.8f));
    }

}


tcPlatformAreaEditObject::~tcPlatformAreaEditObject()
{

}

