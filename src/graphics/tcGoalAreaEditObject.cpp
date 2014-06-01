/**  
**  @file tcGoalAreaEditObject.cpp
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

#include "tcGoalAreaEditObject.h"
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





/**
* Loads state from stream
*/
tcStream& tcGoalAreaEditObject::operator<<(tcStream& stream)
{
    return tcAreaEditObject::operator<<(stream);
}


/**
* Saves state to stream
*/
tcStream& tcGoalAreaEditObject::operator>>(tcStream& stream)
{
    return tcAreaEditObject::operator>>(stream);
}



void tcGoalAreaEditObject::Draw(tc3DWindow2* host)
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
        if ((drawCount & 0xF) == 1)
        {
            LoadGeoPointsFromGoal();
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
    else
    {
        color *= 0.5f;
    }

    size_t dragPoint = ((dragMode == DRAG_POINT) && IsDragActive()) ? dragPointIdx : 99999;


    float ymax = -9999.0f;
    float xmin = 9999.0f;
    float xmax = -9999.0f;
    for (size_t n=0; n<screenPoints.size(); n++)
    {
        size_t n1 = n;
        size_t n2 = (n + 1) % screenPoints.size();
       // host->DrawLineR(screenPoints[n1].x, screenPoints[n1].y, screenPoints[n2].x, screenPoints[n2].y, color);
        host->DrawThickLineR(screenPoints[n1].x, screenPoints[n1].y, screenPoints[n2].x, screenPoints[n2].y, 3.0f, color);

        ymax = std::max(screenPoints[n1].y, ymax);
        xmax = std::max(screenPoints[n1].x, xmax);
        xmin = std::min(screenPoints[n1].x, xmin);
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
        host->DrawTextR(caption.c_str(), 0.5f*(xmin+xmax), ymax+10.0f, 
            host->GetDefaultFont(), lineColor, 12.0f, tc3DWindow2::CENTER_CENTER);
    }

}




bool tcGoalAreaEditObject::IsSourceActive()
{
    tcGoalTracker* goalTracker = tcGoalTracker::Get();

    tcAreaGoal* goal = dynamic_cast<tcAreaGoal*>(goalTracker->LookupGoalById(goalId));

    return (goal != 0);
}

void tcGoalAreaEditObject::LoadGeoPointsFromGoal()
{
    geoPoints.clear();

    tcGoalTracker* goalTracker = tcGoalTracker::Get();

    tcAreaGoal* goal = dynamic_cast<tcAreaGoal*>(goalTracker->LookupGoalById(goalId));

    if (goal == 0) return;

    geoPoints = goal->areaBounds;

    wxString allianceText("ALL?");
    unsigned int alliance = goal->GetAlliance();
    if (alliance != 0)
    {
        tcAllianceInfo* allianceInfo = tcAllianceInfo::Get();
        allianceText = allianceInfo->GetAllianceDefaultCountry(alliance);
    }

    wxString logicType = goal->GetQuantityDescription();
	float timeObjective_min = (1.0/60.0) * goal->GetTimeObjective();
	wxString timeDelayString = (timeObjective_min <= 0) ? "" : wxString::Format(" %.0f minutes", timeObjective_min);

    if (goal->isEnterGoal)
    {
        areaType = 1;
		caption.Printf("%s %s ENTER GOAL%s: %s", allianceText.c_str(), logicType.c_str(), 
			timeDelayString.c_str(), goal->GetTargetListAsString().c_str());
    }
    else
    {
        areaType = 0;
		caption.Printf("%s %s AVOID GOAL%s: %s", allianceText.c_str(), logicType.c_str(),
			timeDelayString.c_str(), goal->GetTargetListAsString().c_str());
    }

    
}

/**
* @return false if keyCode is valid command for this object
*/
bool tcGoalAreaEditObject::ProcessKey(int keyCode)
{
    switch (keyCode)
    {
    case 't':
        ToggleAreaType();
        break;
    default:
        return tcAreaEditObject::ProcessKey(keyCode);
    }

    return false;
}

void tcGoalAreaEditObject::ToggleAreaType()
{
    areaType = (areaType == 0) ? 1 : 0;

    UpdateSourceData();
}

/**
* Updates screenPoints with geoPoints data
*/
void tcGoalAreaEditObject::UpdateDrawData()
{
    tcAreaEditObject::UpdateDrawData();

    if (areaType == 1)
    {
        lineColor.set(0.2f, 0.9f, 0.2f, 1.0);
    }
    else
    {
        lineColor.set(0.9f, 0.2f, 0.2f, 1.0);
    }

}


/**
* Updates source data with geoPoints data
*/
void tcGoalAreaEditObject::UpdateSourceData()
{
    tcGoalTracker* goalTracker = tcGoalTracker::Get();

    tcAreaGoal* goal = dynamic_cast<tcAreaGoal*>(goalTracker->LookupGoalById(goalId));

    if (goal == 0) return;

    goal->areaBounds = geoPoints;

    goal->isEnterGoal = (areaType != 0);
}


tcGoalAreaEditObject::tcGoalAreaEditObject(long id)
: goalId(id)
{
    LoadGeoPointsFromGoal();
}


tcGoalAreaEditObject::~tcGoalAreaEditObject()
{
    //if (updateWhenDragDone)
    //{
    //    MarkFormationUpdated();
    //}
}

