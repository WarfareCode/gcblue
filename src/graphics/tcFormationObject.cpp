/**  
**  @file tcFormationObject.cpp
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

#include "tcFormationObject.h"
#include "tcSimState.h"
#include "tcGameObject.h"
#include "tcPlatformObject.h"
#include "common/tcStream.h"
#include "tc3DWindow2.h"
#include "tcMapView.h"
#include "tcGeometry.h"
#include "tcTexture2D.h"
#include "tcUnits.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif 


boost::shared_ptr<tcGeometry> tcFormationObject::cornerMarkerOn;
boost::shared_ptr<tcGeometry> tcFormationObject::cornerMarkerOff;
boost::shared_ptr<tcGeometry> tcFormationObject::cornerMarkerOff2;

void tcFormationObject::LoadCornerMarker(const std::string& filename_on, const std::string& filename_off, const std::string& filename_off2)
{
    float w = 8.0f;
	
    cornerMarkerOn = boost::shared_ptr<tcGeometry>(new tcGeometry);
    tcTexture2D* texOn = new tcTexture2D(filename_on);
    cornerMarkerOn->MakeTexturedSymbol(boost::shared_ptr<tcTexture2D>(texOn), w);

    cornerMarkerOff = boost::shared_ptr<tcGeometry>(new tcGeometry);
    tcTexture2D* texOff = new tcTexture2D(filename_off);
    cornerMarkerOff->MakeTexturedSymbol(boost::shared_ptr<tcTexture2D>(texOff), w);

    cornerMarkerOff2 = boost::shared_ptr<tcGeometry>(new tcGeometry);
    tcTexture2D* texOff2 = new tcTexture2D(filename_off2);
    cornerMarkerOff->MakeTexturedSymbol(boost::shared_ptr<tcTexture2D>(texOff2), w);
}



/**
* Loads state from stream
*/
tcStream& tcFormationObject::operator<<(tcStream& stream)
{
    return tcMapObject::operator<<(stream);
}


/**
* Saves state to stream
*/
tcStream& tcFormationObject::operator>>(tcStream& stream)
{
    return tcMapObject::operator>>(stream);
}


/**
* @param mousePoint screen coords of mouse click point
*/
int tcFormationObject::CalculateDragMode(const tcPoint& pos)
{
    float diagonalDistance = sectorBL.DistanceTo(sectorTR);
    if (diagonalDistance < 32.0)
    {
        return 0;
    }
    
    const float dragDist = 8.0f;

    float distBL = pos.DistanceTo(sectorBL);
    float distBR = pos.DistanceTo(sectorBR);
    float distTL = pos.DistanceTo(sectorTL); 
    float distTR = pos.DistanceTo(sectorTR);

    if (distBL < dragDist) return DRAG_BL;
    else if (distBR < dragDist) return DRAG_BR;
    else if (distTL < dragDist) return DRAG_TL;
    else if (distTR < dragDist) return DRAG_TR;
    else return DRAG_ALL;

}


void tcFormationObject::Draw(tc3DWindow2* host)
{
    if (!IsDragActive() && markFormationWhenDragDone)
    {
        MarkFormationUpdated();
        markFormationWhenDragDone = false;
    }

    if (!isActive) return;

    if (CloseRequested())
    {
        FlagForDelete();
        return;
    }

    bool valid = UpdateDrawData();
    if (!valid)
    {
        FlagForDelete();
        return;
    }

    if (isLeader)
    {
        DrawLeader(host);
        return;
    }

    bool showSecondaryColor = (formationMode == tcFormation::SPRINTDRIFT) && (!isLeader);

    Vec4 color;
    if (IsDragActive())
    {
        if (showSecondaryColor)
        {
            color.set(1.0f, 1.0f, 0.6f, 0.8f);
        }
        else
        {
            color.set(0.4f, 1, 0.5f, 0.7f);
        }
    }
    else
    {
        if (showSecondaryColor)
        {
            color.set(1.0f, 1.0f, 0.5f, 0.5f);
        }
        else
        {
            color.set(0, 1, 0.1f, 0.3f);
        }
    }


    //host->DrawLineR(leaderPoint.x, leaderPoint.y, ownPoint.x, ownPoint.y, color);

    host->DrawLineR(leaderPoint.x, leaderPoint.y, sectorCenter.x, sectorCenter.y, color);

    // if sector is big enough on screen, then draw it, otherwise just draw line
    float diagonalDistance = sectorBL.DistanceTo(sectorTR);
    if (diagonalDistance > 8.0)
    {

        host->DrawPieSection(leaderPoint.x, leaderPoint.y, rx1, -ry1, rx2, -ry2,
            start_angle_rad, stop_angle_rad, color, tc3DWindow2::FILL_OFF);

        if (IsDragActive() && (dragMode != DRAG_ALL))
        {
            host->DrawGeometryR(cornerMarkerOn.get(), sectorBL.x, sectorBL.y);
            host->DrawGeometryR(cornerMarkerOn.get(), sectorBR.x, sectorBR.y);
            host->DrawGeometryR(cornerMarkerOn.get(), sectorTL.x, sectorTL.y);
            host->DrawGeometryR(cornerMarkerOn.get(), sectorTR.x, sectorTR.y);
        }
        else if (showSecondaryColor)
        {
            host->DrawGeometryR(cornerMarkerOff.get(), sectorBL.x, sectorBL.y);
            host->DrawGeometryR(cornerMarkerOff.get(), sectorBR.x, sectorBR.y);
            host->DrawGeometryR(cornerMarkerOff.get(), sectorTL.x, sectorTL.y);
            host->DrawGeometryR(cornerMarkerOff.get(), sectorTR.x, sectorTR.y);
        }
        else
        {
            host->DrawGeometryR(cornerMarkerOff2.get(), sectorBL.x, sectorBL.y);
            host->DrawGeometryR(cornerMarkerOff2.get(), sectorBR.x, sectorBR.y);
            host->DrawGeometryR(cornerMarkerOff2.get(), sectorTL.x, sectorTL.y);
            host->DrawGeometryR(cornerMarkerOff2.get(), sectorTR.x, sectorTR.y);
        }
    }

    // drag range, bearing to sector center if drag is active
    if (IsDragActive())
    {
        tcUnits* units = tcUnits::Get();
        wxString s;
        s.Printf("%s, %03.0f deg", units->GetUserDistanceString(1000.0f*range_km),
            C_RADTODEG*bearing_center_rad);

        float x = 0.5f*(leaderPoint.x + sectorCenter.x);
        float y = 0.5f*(leaderPoint.y + sectorCenter.y);

        host->DrawTextR(s.c_str(), x, y, host->GetDefaultFont(), 
            Vec4(1, 1, 1, 1), 10.0f, tc3DWindow2::LEFT_CENTER);
    }

    host->DrawRectangleR(bearingModeSelect, color, tc3DWindow2::FILL_ON);
    if (useNorthBearing)
    {
        host->DrawTextInRectR("N", bearingModeSelect, host->GetDefaultFont(), Vec4(1, 1, 1, 1),
            10.0f, tc3DWindow2::CENTER_CENTER);
    }
    else
    {
        host->DrawTextInRectR("R", bearingModeSelect, host->GetDefaultFont(), Vec4(1, 1, 1, 1),
            10.0f, tc3DWindow2::CENTER_CENTER);
    }

}


/**
* Version for leader object
*/
void tcFormationObject::DrawLeader(tc3DWindow2* host)
{    
    tcSimState* simState = tcSimState::Get();
    tcPlatformObject* leader = dynamic_cast<tcPlatformObject*>(simState->GetObject(platformId));
    if (leader == 0)
    {
        wxASSERT(false);
        return;
    }
    
    Vec4 color(0, 1, 0.1f, 0.3f);

    // draw line from leader to each of followers
    for (size_t k=0; k<leader->formation.followers.size(); k++)
    {
        long followerId = leader->formation.followers[k];
        tcGameObject* follower = simState->GetObject(followerId);
        if (follower != 0)
        {
            tcPoint p = mapView->GeoToScreen(follower->mcKin.mfLon_rad, follower->mcKin.mfLat_rad);
            host->DrawLineR(ownPoint.x, ownPoint.y, p.x, p.y, color);
        }
        else
        {
            wxASSERT(false);
        }
    }
}


void tcFormationObject::MarkFormationUpdated()
{
    tcSimState* simState = tcSimState::Get();

    tcPlatformObject* platform = 
        dynamic_cast<tcPlatformObject*>(simState->GetObject(platformId));

    if (platform == 0) return;

    platform->MarkFormationUpdated();
}


void tcFormationObject::MoveToScreenPoint(const wxPoint& pos)
{
    if (!IsDragActive()) return;
    tcSimState* simState = tcSimState::Get();

    tcPlatformObject* platform = 
        dynamic_cast<tcPlatformObject*>(simState->GetObject(platformId));

    if (platform == 0) return;

    tcFormation& formation = platform->formation;
    if (!formation.isActive) return;


    tcPlatformObject* leader = dynamic_cast<tcPlatformObject*>(simState->GetObject(formation.leaderId));

    tcPoint geo = mapView->ScreenToGeo(pos);

    // calculate bearing and range
    float bearing_rad = leader->mcKin.HeadingToGeoRad(geo.x, geo.y);
    float range_km = leader->mcKin.RangeToKm(geo.x, geo.y);

    if (dragMode == DRAG_ALL)
    {
        bearing_rad -= deltaBearing_rad;
        range_km -= deltaRange_km;
    }

    float range_error_km = range_km - formation.range_center_km;

    // bearing of sector center wrt North
    float effectiveBearing = formation.useNorthBearing ? 
        formation.bearing_center_rad : formation.bearing_center_rad + leader->mcKin.mfHeading_rad;
    if (effectiveBearing < -C_PI) effectiveBearing += C_TWOPI;
    else if (effectiveBearing >= C_PI) effectiveBearing -= C_TWOPI;

    float bearing_error_rad = bearing_rad - effectiveBearing;

    if (bearing_error_rad < -C_PI) bearing_error_rad += C_TWOPI;
    else if (bearing_error_rad >= C_PI) bearing_error_rad -= C_TWOPI;


    switch (dragMode)
    {
    case DRAG_ALL:
        // move formation sector
        if (formation.useNorthBearing)
        {
            formation.bearing_center_rad = bearing_rad;
        }
        else
        {
            formation.bearing_center_rad = bearing_rad - leader->mcKin.mfHeading_rad;
            if (formation.bearing_center_rad < -C_PI) formation.bearing_center_rad += C_TWOPI;
        }            
        formation.range_center_km = range_km;
        break;
    default:
        formation.bearing_span_rad = 2.05f * fabsf(bearing_error_rad);
        formation.range_span_km = 2.05f * fabsf(range_error_km);
        if (formation.bearing_span_rad > C_TWOPI) formation.bearing_span_rad = C_TWOPI;

        break;
    }
}


bool tcFormationObject::ProcessLButtonDown(const wxPoint& pos)
{
    tcSimState* simState = tcSimState::Get();

    tcPlatformObject* platform = 
        dynamic_cast<tcPlatformObject*>(simState->GetObject(platformId));

    if (platform == 0) return false;

    tcFormation& formation = platform->formation;

    if (formation.IsLeader()) return false; // no interaction with leader graphics
    if (!formation.isActive) return false;


    tcPlatformObject* leader = dynamic_cast<tcPlatformObject*>(simState->GetObject(formation.leaderId));

    tcPoint geo = mapView->ScreenToGeo(pos);

    // calculate bearing and range
    float bearing_rad = leader->mcKin.HeadingToGeoRad(geo.x, geo.y);
    float range_km = leader->mcKin.RangeToKm(geo.x, geo.y);

    bool pointWithinSector = formation.IsInPositionLoose2(platform, bearing_rad, range_km, deltaBearing_rad, deltaRange_km);

    if (pointWithinSector)
    {
        dragMode = CalculateDragMode(tcPoint(pos.x, pos.y));
        SetDragActive(true);
        markFormationWhenDragDone = true;
        return true;
    }
    else if (bearingModeSelect.ContainsPoint(pos.x, pos.y))
    {
        ToggleBearingMode();
        return true;
    }
    else
    {
        return false;
    }
}


void tcFormationObject::ToggleBearingMode()
{
    tcSimState* simState = tcSimState::Get();

    tcPlatformObject* platform = 
        dynamic_cast<tcPlatformObject*>(simState->GetObject(platformId));

    if (platform == 0) return;

    tcFormation& formation = platform->formation;
    if (!formation.isActive) return;

    tcPlatformObject* leader = dynamic_cast<tcPlatformObject*>(simState->GetObject(formation.leaderId));
    if (leader == 0) return;

    if (formation.useNorthBearing)
    {
        formation.useNorthBearing = false; // switch to relative bearing
        formation.bearing_center_rad -= leader->mcKin.mfHeading_rad;
        if (formation.bearing_center_rad < -C_PI) formation.bearing_center_rad += C_TWOPI;
    }
    else
    {
        formation.useNorthBearing = true; // switch to north bearing
        formation.bearing_center_rad += leader->mcKin.mfHeading_rad;
        if (formation.bearing_center_rad >= C_PI) formation.bearing_center_rad -= C_TWOPI;
    }

    platform->MarkFormationUpdated();
}

/**
* @return true if formation is valid, false if invalid (should delete if invalid)
*/
bool tcFormationObject::UpdateDrawData()
{
    tcSimState* simState = tcSimState::Get();

    tcPlatformObject* platform = 
        dynamic_cast<tcPlatformObject*>(simState->GetObject(platformId));

    if ((platform == 0) || (!platform->IsOwnAlliance())) return false; // delete if not player alliance for cases where we toggle alliance in game

    tcFormation& formation = platform->formation;
    if (!formation.isActive) return false;

    isLeader = formation.IsLeader();
    if (isLeader) 
    {
        ownPoint = mapView->GeoToScreen(platform->mcKin.mfLon_rad, platform->mcKin.mfLat_rad);
        return true;
    }

    tcPlatformObject* leader = dynamic_cast<tcPlatformObject*>(simState->GetObject(formation.leaderId));
    if (leader == 0) return false;

    formationMode = (int)formation.formationMode;
    range_km = formation.range_center_km;
    min_range_km = formation.range_center_km - 0.5f*formation.range_span_km;
    max_range_km = formation.range_center_km + 0.5f*formation.range_span_km;

    float min_lat = leader->mcKin.mfLat_rad + C_KMTORAD*min_range_km;
    float max_lat = leader->mcKin.mfLat_rad + C_KMTORAD*max_range_km;

    ownPoint = mapView->GeoToScreen(platform->mcKin.mfLon_rad, platform->mcKin.mfLat_rad);
    leaderPoint = mapView->GeoToScreen(leader->mcKin.mfLon_rad, leader->mcKin.mfLat_rad);

    tcPoint minNorthPoint = mapView->GeoToScreen((float)leader->mcKin.mfLon_rad, min_lat);
    tcPoint maxNorthPoint = mapView->GeoToScreen((float)leader->mcKin.mfLon_rad, max_lat);

    ry1 = leaderPoint.y - minNorthPoint.y;
    ry2 = leaderPoint.y - maxNorthPoint.y;

    float lon_scale = mapView->LonToLatScale() / cosf(leader->mcKin.mfLat_rad);
    rx1 = lon_scale * ry1;
    rx2 = lon_scale * ry2;

    float effectiveBearing_rad = 
        formation.useNorthBearing ? formation.bearing_center_rad : formation.bearing_center_rad + leader->mcKin.mfHeading_rad;
    if (effectiveBearing_rad < -C_PI) effectiveBearing_rad += C_TWOPI;
    else if (effectiveBearing_rad >= C_PI) effectiveBearing_rad -= C_TWOPI;

    angle_rad = effectiveBearing_rad;
    start_angle_rad = effectiveBearing_rad - 0.5f*formation.bearing_span_rad;
    stop_angle_rad = effectiveBearing_rad + 0.5f*formation.bearing_span_rad;
    bearing_center_rad = formation.bearing_center_rad;

    tcTrack formCenter;
    formCenter.mfLat_rad = leader->mcKin.mfLat_rad;
    formCenter.mfLon_rad = leader->mcKin.mfLon_rad;
    formCenter.Offset(formation.range_center_km, effectiveBearing_rad);
    sectorCenter = mapView->GeoToScreen(formCenter.mfLon_rad, formCenter.mfLat_rad);

    tcTrack formBL;
    formBL.mfLat_rad = leader->mcKin.mfLat_rad;
    formBL.mfLon_rad = leader->mcKin.mfLon_rad;
    formBL.Offset(min_range_km, start_angle_rad);
    sectorBL = mapView->GeoToScreen(formBL.mfLon_rad, formBL.mfLat_rad);

    tcTrack formBR;
    formBR.mfLat_rad = leader->mcKin.mfLat_rad;
    formBR.mfLon_rad = leader->mcKin.mfLon_rad;
    formBR.Offset(min_range_km, stop_angle_rad);
    sectorBR = mapView->GeoToScreen(formBR.mfLon_rad, formBR.mfLat_rad);

    tcTrack formTL;
    formTL.mfLat_rad = leader->mcKin.mfLat_rad;
    formTL.mfLon_rad = leader->mcKin.mfLon_rad;
    formTL.Offset(max_range_km, start_angle_rad);
    sectorTL = mapView->GeoToScreen(formTL.mfLon_rad, formTL.mfLat_rad);

    tcTrack formTR;
    formTR.mfLat_rad = leader->mcKin.mfLat_rad;
    formTR.mfLon_rad = leader->mcKin.mfLon_rad;
    formTR.Offset(max_range_km, stop_angle_rad);
    sectorTR = mapView->GeoToScreen(formTR.mfLon_rad, formTR.mfLat_rad);

    tcTrack bearingSelect;
    bearingSelect.mfLat_rad = leader->mcKin.mfLat_rad;
    bearingSelect.mfLon_rad = leader->mcKin.mfLon_rad;
    bearingSelect.Offset(max_range_km, angle_rad);
    tcPoint pb = mapView->GeoToScreen(bearingSelect.mfLon_rad, bearingSelect.mfLat_rad);
    pb.y = -pb.y;
    pb.Offset(15.0f, angle_rad);
    pb.y = -pb.y;
    bearingModeSelect.Set(pb.x, pb.x, pb.y, pb.y);
    bearingModeSelect.Expand(8.0f, 8.0f);

    useNorthBearing = formation.useNorthBearing;

    return true;
}


tcFormationObject::tcFormationObject(long id)
: platformId(id),
  dragMode(DRAG_ALL),
  markFormationWhenDragDone(false),
  formationMode(0)
{
    SetComplexInteractive(true);

    if (cornerMarkerOn.get() == 0)
    {
        LoadCornerMarker("images\\white_marker.png", "images\\green_marker.png", "images\\yellow_marker.png");
    }
}


tcFormationObject::~tcFormationObject()
{
    if (markFormationWhenDragDone)
    {
        MarkFormationUpdated();
    }
}

