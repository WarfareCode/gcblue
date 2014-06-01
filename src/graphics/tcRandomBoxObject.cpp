/**  
**  @file tcRandomBoxObject.cpp
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

#include "tcRandomBoxObject.h"
#include "tc3DWindow2.h"
#include "tcMapView.h"
#include "tcGeometry.h"
#include "tcTexture2D.h"
#include "tcSimState.h"
#include "tcScenarioRandomizer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif 


boost::shared_ptr<tcGeometry> tcRandomBoxObject::cornerMarkerOn;
boost::shared_ptr<tcGeometry> tcRandomBoxObject::cornerMarkerOff;

void tcRandomBoxObject::LoadCornerMarker(const std::string& filename_on, const std::string& filename_off)
{
    float w = 8.0f;
	
    cornerMarkerOn = boost::shared_ptr<tcGeometry>(new tcGeometry);
    tcTexture2D* texOn = new tcTexture2D(filename_on);
    cornerMarkerOn->MakeTexturedSymbol(boost::shared_ptr<tcTexture2D>(texOn), w);

    cornerMarkerOff = boost::shared_ptr<tcGeometry>(new tcGeometry);
    tcTexture2D* texOff = new tcTexture2D(filename_off);
    cornerMarkerOff->MakeTexturedSymbol(boost::shared_ptr<tcTexture2D>(texOff), w);
}



/**
* @param mousePoint screen coords of mouse click point
*/
int tcRandomBoxObject::CalculateDragMode(const tcPoint& pos)
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


void tcRandomBoxObject::Draw(tc3DWindow2* host)
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

    Vec4 color;
    if (IsDragActive())
    {
        color.set(0.4f, 1, 0.5f, 0.6f);
    }
    else
    {
        color.set(0, 1, 0.1f, 0.3f);
    }

    // if sector is big enough on screen, then draw it, otherwise just draw line
    float diagonalDistance = sectorBL.DistanceTo(sectorTR);
    if (diagonalDistance > 8.0)
    {
        float w = sectorBR.x - sectorBL.x;
        float h = sectorTL.y - sectorBL.y;
        host->DrawRectangleR(sectorBL.x, sectorBL.y, w, h, color, tc3DWindow2::FILL_OFF);

        
        if (IsDragActive() && (dragMode != DRAG_ALL))
        {
            host->DrawGeometryR(cornerMarkerOn.get(), sectorBL.x, sectorBL.y);
            host->DrawGeometryR(cornerMarkerOn.get(), sectorBR.x, sectorBR.y);
            host->DrawGeometryR(cornerMarkerOn.get(), sectorTL.x, sectorTL.y);
            host->DrawGeometryR(cornerMarkerOn.get(), sectorTR.x, sectorTR.y);
        }
        else
        {
            host->DrawGeometryR(cornerMarkerOff.get(), sectorBL.x, sectorBL.y);
            host->DrawGeometryR(cornerMarkerOff.get(), sectorBR.x, sectorBR.y);
            host->DrawGeometryR(cornerMarkerOff.get(), sectorTL.x, sectorTL.y);
            host->DrawGeometryR(cornerMarkerOff.get(), sectorTR.x, sectorTR.y);
        }
    }

   

}




void tcRandomBoxObject::MarkFormationUpdated()
{
    tcSimState* simState = tcSimState::Get();
    
    tcPlatformObject* platform = 
        dynamic_cast<tcPlatformObject*>(simState->GetObject(platformId));
    if (platform == 0) return;
    
    
    tcScenarioRandomizer* randomizer = tcScenarioRandomizer::Get();

    randomizer->UpdateRandomBox(platform->mzUnit.c_str(), startBox, box);
    startBox = box;

}


void tcRandomBoxObject::MoveToScreenPoint(const wxPoint& pos)
{
    if (!IsDragActive()) return;
    tcSimState* simState = tcSimState::Get();

    tcPlatformObject* platform = 
        dynamic_cast<tcPlatformObject*>(simState->GetObject(platformId));

    if (platform == 0) return;
   
    tcPoint geo = mapView->ScreenToGeo(pos);

    switch (dragMode)
    {
    case DRAG_ALL:
        {
        // move formation sector
        float dx = geo.x - box.left - blOffset.x;
        float dy = geo.y - box.bottom - blOffset.y;

        box.Offset(dx, dy);
        }
        break;
    case DRAG_BL:
        box.left = geo.x;
        box.bottom = geo.y;
        break;
    case DRAG_BR:
        box.right = geo.x;
        box.bottom = geo.y;
        break;
    case DRAG_TL:
        box.left = geo.x;
        box.top = geo.y;
        break;
    case DRAG_TR:
        box.right = geo.x;
        box.top = geo.y;
        break;
    default:
        break;
    }

    float d = 0.007f * mapView->GetLonSpan();

    if (box.bottom >( box.top - d)) box.bottom = box.top - d;
    if (box.left > (box.right - d)) box.left = box.right - d;


}

/**
* @return false if keyCode is valid command for this object
*/
bool tcRandomBoxObject::ProcessKey(int keyCode)
{
    switch (keyCode)
    {
    case WXK_DELETE:
        {
            tcSimState* simState = tcSimState::Get();
            tcPlatformObject* platform = 
                dynamic_cast<tcPlatformObject*>(simState->GetObject(platformId));
            if (platform == 0) return false;

            tcScenarioRandomizer* randomizer = tcScenarioRandomizer::Get();
            randomizer->DeleteRandomBox(platform->mzUnit.c_str(), startBox);
            FlagForDelete();
        }
        break;
    default:
        break;
    }
    return false;
}


bool tcRandomBoxObject::ProcessLButtonDown(const wxPoint& pos)
{
    tcSimState* simState = tcSimState::Get();

    tcPlatformObject* platform = 
        dynamic_cast<tcPlatformObject*>(simState->GetObject(platformId));

    if (platform == 0) return false;


    tcPoint geo = mapView->ScreenToGeo(pos);

    float margin = 0.005f*mapView->GetLonSpan();
    tcRect expandedBox = box;
    expandedBox.Expand(margin, margin);

    bool pointWithinBox = expandedBox.ContainsPoint(geo.x, geo.y);

    if (pointWithinBox)
    {
        dragMode = CalculateDragMode(tcPoint(pos.x, pos.y));
        SetDragActive(true);
        markFormationWhenDragDone = true;
        blOffset.x = geo.x - box.left;
        blOffset.y = geo.y - box.bottom;
        return true;
    }

    return false;

    //else if (bearingModeSelect.ContainsPoint(pos.x, pos.y))
    //{
    //    ToggleBearingMode();
    //    return true;
    //}
    //else
    //{
    //    return false;
    //}
}

/**
* Used to initialize box, coords in radian lon/lat
*/
void tcRandomBoxObject::SetBox(const tcRect& r)
{
    box = r;
    startBox = r;
}


/**
* @return true if formation is valid, false if invalid (should delete if invalid)
*/
bool tcRandomBoxObject::UpdateDrawData()
{
    tcSimState* simState = tcSimState::Get();

    tcPlatformObject* platform = 
        dynamic_cast<tcPlatformObject*>(simState->GetObject(platformId));

    if ((platform == 0) || (!tcGameObject::IsEditMode())) return false;

    tcScenarioRandomizer* randomizer = tcScenarioRandomizer::Get();
    if (!randomizer->RandomBoxExists(platform->mzUnit.c_str(), startBox)) return false;



    ownPoint = mapView->GeoToScreen(platform->mcKin.mfLon_rad, platform->mcKin.mfLat_rad);

    sectorBL = mapView->GeoToScreen(box.left, box.bottom);
    sectorBR = mapView->GeoToScreen(box.right, box.bottom);
    sectorTL = mapView->GeoToScreen(box.left, box.top);
    sectorTR = mapView->GeoToScreen(box.right, box.top);

    return true;
}


tcRandomBoxObject::tcRandomBoxObject(long id)
: platformId(id),
  dragMode(DRAG_ALL),
  markFormationWhenDragDone(false),
  blOffset(0, 0)

{
    SetComplexInteractive(true);

    if (cornerMarkerOn.get() == 0)
    {
        LoadCornerMarker("images\\white_marker.png", "images\\green_marker.png");
    }
}


tcRandomBoxObject::~tcRandomBoxObject()
{
    if (markFormationWhenDragDone)
    {
        MarkFormationUpdated();
    }
}

