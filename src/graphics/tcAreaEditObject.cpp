/**  
**  @file tcAreaEditObject.cpp
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

#include "tcAreaEditObject.h"
#include "tcSimState.h"
#include "tcGameObject.h"
#include "common/tcStream.h"
#include "tc3DWindow2.h"
#include "tcMapView.h"
#include "tcGeometry.h"
#include "tcTexture2D.h"
#include "tcUnits.h"
#include "tcGoalTracker.h"
#include "tcGoal.h"
#include "tcAllianceInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif 


boost::shared_ptr<tcGeometry> tcAreaEditObject::cornerMarkerOn;
boost::shared_ptr<tcGeometry> tcAreaEditObject::cornerMarkerOff;

void tcAreaEditObject::LoadCornerMarker(const std::string& filename_on, const std::string& filename_off)
{
    float w = 16.0f;
	
    cornerMarkerOn = boost::shared_ptr<tcGeometry>(new tcGeometry);
    tcTexture2D* texOn = new tcTexture2D(filename_on);
    cornerMarkerOn->MakeTexturedSymbol(boost::shared_ptr<tcTexture2D>(texOn), w);

    cornerMarkerOff = boost::shared_ptr<tcGeometry>(new tcGeometry);
    tcTexture2D* texOff = new tcTexture2D(filename_off);
    cornerMarkerOff->MakeTexturedSymbol(boost::shared_ptr<tcTexture2D>(texOff), w);
}



/**
* Loads state from stream
*/
tcStream& tcAreaEditObject::operator<<(tcStream& stream)
{
    return tcMapObject::operator<<(stream);
}


/**
* Saves state to stream
*/
tcStream& tcAreaEditObject::operator>>(tcStream& stream)
{
    return tcMapObject::operator>>(stream);
}


/**
* @param mousePoint screen coords of mouse click point
*/
void tcAreaEditObject::CalculateDragMode(const tcPoint& pos)
{
    const float distanceThreshold = 10.0f;

    float x = float(pos.x);
    float y = float(pos.y);

    for (size_t n=0; n<screenPoints.size(); n++)
    {
        float distance = fabsf(screenPoints[n].x - x) + fabsf(screenPoints[n].y - y);
        if (distance < distanceThreshold)
        {
            dragPointIdx = n;
            dragMode = DRAG_POINT;
            return;
        }
    }

    dragMode = DRAG_ALL;
}





void tcAreaEditObject::MoveToScreenPoint(const wxPoint& pos)
{
    if (!IsDragActive()) return;
    
    wxPoint deltaPos = pos - moveReferencePoint;
    moveReferencePoint = pos;

    if (dragMode == DRAG_ALL)
    {
        for (size_t n=0; n<screenPoints.size(); n++)
        {
            screenPoints[n].x += deltaPos.x;
            screenPoints[n].y += deltaPos.y;
        }
    }
    else if (dragPointIdx < screenPoints.size())
    {
        screenPoints[dragPointIdx] = tcPoint(pos.x, pos.y);
    }

    geoPoints.clear();
    for (size_t n=0; n<screenPoints.size(); n++)
    {
        tcPoint p = mapView->ScreenToGeo(screenPoints[n].x, screenPoints[n].y);
        GeoPoint g;
        g.Set(p.x, p.y, 0);
        geoPoints.push_back(g);
    }
    
}


bool tcAreaEditObject::ProcessLButtonDown(const wxPoint& pos)
{
    if (IsPointNearLine(pos))
    {
        CalculateDragMode(tcPoint(pos.x, pos.y));
        SetDragActive(true);
        updateWhenDragDone = true;
        moveReferencePoint = pos;
        return true;
    }

    return false;
}

bool tcAreaEditObject::IsPointWithinArea(float lon_rad, float lat_rad) const
{
    // PNPOLY - Point Inclusion in Polygon Test
    // W. Randolph Franklin (WRF) 

    if (geoPoints.size() < 3) return false;

    float lon_min = 999.9f;
    float lon_max = -999.9f;
    float lat_min = 999.9f;
    float lat_max = -999.9f;

    for (size_t n=0; n<geoPoints.size(); n++)
    {
        lon_min = std::min(lon_min, (float)geoPoints[n].mfLon_rad);
        lat_min = std::min(lat_min, (float)geoPoints[n].mfLat_rad);
        lon_max = std::max(lon_max, (float)geoPoints[n].mfLon_rad);
        lat_max = std::max(lat_max, (float)geoPoints[n].mfLat_rad);
    }

    if ((lat_rad > lat_max) || (lat_rad < lat_min)) return false;

    std::vector<GeoPoint> vert = geoPoints;

    // unwrap polygon points if wrapped about +/180 deg
    if ((lon_max - lon_min) > C_PI)
    {
        for (size_t n=0; n<vert.size(); n++)
        {
            if (vert[n].mfLon_rad < 0) vert[n].mfLon_rad += C_TWOPI;
        }

        if (lon_rad < 0) lon_rad += C_TWOPI;

        if (lon_min < 0) lon_min += C_TWOPI;
        wxASSERT(lon_max >= 0);
    }

    if ((lon_rad > lon_max) || (lon_rad < lon_min)) return false;


    int i, j, c = 0;
    int nvert = int(geoPoints.size());

    for (i = 0, j = nvert-1; i < nvert; j = i++) 
    {
        float vertyi = (float)vert[i].mfLat_rad;
        float vertxi = (float)vert[i].mfLon_rad;
        float vertyj = (float)vert[j].mfLat_rad;
        float vertxj = (float)vert[j].mfLon_rad;

        if ( ((vertyi > lat_rad) != (vertyj > lat_rad)) &&
            (lon_rad < (vertxj-vertxi) * (lat_rad-vertyi) / (vertyj-vertyi) + vertxi) )
        {
            c = !c;
        }
    }

    return (c != 0);
}

/**
* Used to check if mouse is near one of the bounding area lines
*/
bool tcAreaEditObject::IsPointNearLine(const wxPoint& pos) const
{
    if (screenPoints.size() < 3) return false;

    const float distanceThreshold = 10.0f;
    const float edgeThreshold = 2.0f;

    float x = float(pos.x);
    float y = float(pos.y);

    for (size_t n=0; n<screenPoints.size(); n++)
    {
        size_t n1 = n;
        size_t n2 = (n + 1) % screenPoints.size();

        float dx = screenPoints[n2].x - screenPoints[n1].x;
        float dy = screenPoints[n2].y - screenPoints[n1].y;

        if ((dx != 0) || (dy != 0))
        {
            if (fabsf(dx) > fabsf(dy))
            {
                float xmin = std::min(screenPoints[n1].x, screenPoints[n2].x);
                float xmax = std::max(screenPoints[n1].x, screenPoints[n2].x);
                if ((x >= (xmin - edgeThreshold)) && (x <= (xmax + edgeThreshold)))
                {
                    float m = dy / dx;
                    float yline = m*(x-screenPoints[n1].x) + screenPoints[n1].y;
                    if (fabsf(yline - y) < distanceThreshold) return true;
                }
            }
            else
            {
                float ymin = std::min(screenPoints[n1].y, screenPoints[n2].y);
                float ymax = std::max(screenPoints[n1].y, screenPoints[n2].y);
                if ((y >= (ymin - edgeThreshold)) && (y <= (ymax + edgeThreshold)))
                {
                    float m = dx / dy;
                    float xline = m*(y-screenPoints[n1].y) + screenPoints[n1].x;
                    if (fabsf(xline - x) < distanceThreshold) return true;
                }
            }
        }
        else
        {
            return false; // 18 APR 2010, why is this happening with mission GUI open?
            //wxASSERT(false); // duplicate point
        }
    }

    return false;
}



/**
* @return false if keyCode is valid command for this object
*/
bool tcAreaEditObject::ProcessKey(int keyCode)
{
    switch (keyCode)
    {
    case WXK_DELETE:
        FlagForDelete();
        break;
    default:
        break;
    }

    return false;
}


/**
* Updates screenPoints with geoPoints data
*/
void tcAreaEditObject::UpdateDrawData()
{
    screenPoints.clear();

    for (size_t n=0; n<geoPoints.size(); n++)
    {
        tcPoint p = mapView->GeoToScreen(geoPoints[n].mfLon_rad, geoPoints[n].mfLat_rad);
        screenPoints.push_back(p);
    }
}



tcAreaEditObject::tcAreaEditObject()
: dragMode(DRAG_ALL),
  dragPointIdx(0),
  updateWhenDragDone(false),
  drawCount(0)
{
    SetComplexInteractive(true);

    if (cornerMarkerOn.get() == 0)
    {
        LoadCornerMarker("images\\white_marker.png", "images\\black_marker.png");
    }
}


tcAreaEditObject::~tcAreaEditObject()
{
}

