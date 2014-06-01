/**  
**  @file tcTacticalMapView.cpp
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

#include "tcTacticalMapView.h"

#include "tcCommandQueue.h"
#include "aerror.h"
#include "mapsymbols.h"
#include "nsNav.h"
#include "simmath.h"
#include "tcSound.h" // this causes tcTacticalMapView to vanish from class browser in some positions !?
#include "tcMapData.h"
#include "tcString.h"
#include "tcMapObject.h"
#include "tcMapOverlay.h"
#include "tcDragStatus.h"
#include "tcSimState.h"
#include "tcTime.h"
#include "tcGeometry.h"
#include "tcUnits.h"
#include "tcTVEngine.h"
#include <math.h>
#include "tcFormationObject.h"
#include "tcRandomBoxObject.h"
#include "tcButton.h"
#include "network/tcMultiplayerInterface.h" // for MP game accel info
#include "tcWorldMapView.h"
#include "tcUserSelectedGroups.h"
#include "tcScenarioRandomizer.h"
#include "tcWaypointPopup.h"
#include "tcPlatformAreaEditObject.h"
#include "tcDatumEditObject.h"
#include "ai/Brain.h"
#include "ai/tcAttackMission.h"
#include "ai/tcMissionManager.h"
#include "tcGoalTracker.h"
#include <wx/dir.h>
#include "tcSimPythonInterface.h"
#include "tcGameSerializer.h"
#include "tcMessageInterface.h"


using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif 


BEGIN_EVENT_TABLE(tcTacticalMapView, tc3DWindow2)
    EVT_COMMAND(265, wxEVT_COMMAND_BUTTON_CLICKED, tcTacticalMapView::OnShow3DCommand)
	EVT_COMMAND(99, wxEVT_COMMAND_BUTTON_CLICKED, tcTacticalMapView::OnDecelerateTimeCommand)
	EVT_COMMAND(100, wxEVT_COMMAND_BUTTON_CLICKED, tcTacticalMapView::OnPauseTimeCommand)
	EVT_COMMAND(101, wxEVT_COMMAND_BUTTON_CLICKED, tcTacticalMapView::OnAccelerateTimeCommand)
    EVT_COMMAND(222, wxEVT_COMMAND_BUTTON_CLICKED, tcTacticalMapView::OnHookViewCommand)
	EVT_COMMAND(AIR_ROE_COMMAND, wxEVT_COMMAND_BUTTON_CLICKED, tcTacticalMapView::OnAirROE)
	EVT_COMMAND(SURF_ROE_COMMAND, wxEVT_COMMAND_BUTTON_CLICKED, tcTacticalMapView::OnSurfROE)
	EVT_COMMAND(SUB_ROE_COMMAND, wxEVT_COMMAND_BUTTON_CLICKED, tcTacticalMapView::OnSubROE)
	EVT_COMMAND(LAND_ROE_COMMAND, wxEVT_COMMAND_BUTTON_CLICKED, tcTacticalMapView::OnLandROE)
	EVT_COMMAND(SAVE_GAME, wxEVT_COMMAND_BUTTON_CLICKED, tcTacticalMapView::OnSaveGameCommand)
    EVT_COMMAND(CHANGE_SIDES, wxEVT_COMMAND_BUTTON_CLICKED, tcTacticalMapView::OnChangeSidesCommand)
    EVT_COMMAND(REVERT, wxEVT_COMMAND_BUTTON_CLICKED, tcTacticalMapView::OnReloadGameCommand)
END_EVENT_TABLE()


void tcTacticalMapView::ActivateMapCommand(teMapCmdType aeCmd) 
{
    mbMapCmdActive = true; 
    meMapCmd = aeCmd;

	mapCommandStartLocation = mpointMouse;

    overlay->SetInteractionBlocked(true);
}

/**
* Hook closest friendly on screen to current hook, moving in east direction
*/
void tcTacticalMapView::CycleHook(bool cycleEast)
{    
    long currentHook = -1;
    double currentLon_rad = 0;
    double currentLat_rad = 0;

    if (hookedId.size() > 0)
    {
        currentHook = hookedId[0];
    }

    long westId = -1;
    double westLon_rad = 99;

    long eastId = -1;
    double eastLon_rad = -99;

    std::vector<double> lon_vect;
    std::vector<double> lat_vect;
    std::vector<long> id_vect;

    for (int i=0; i<MAXMAPOBJ; i++) 
    {
        tcMapObj* pMO = &maMapObj[i];
        if ((pMO->mbExists) && (pMO->mnID != -1) && (pMO->meAffiliation == tcAllianceInfo::FRIENDLY))
        {
            lon_vect.push_back(pMO->mfLon);
            lat_vect.push_back(pMO->mfLat);
            id_vect.push_back(pMO->mnID);
            
            if (pMO->mnID == currentHook)
            {
                currentLon_rad = pMO->mfLon;
                currentLat_rad = pMO->mfLat;
            }

            if (pMO->mfLon < westLon_rad)
            {
                westId = pMO->mnID;
                westLon_rad = pMO->mfLon;
            }
            if (pMO->mfLon > eastLon_rad)
            {
                eastId = pMO->mnID;
                eastLon_rad = pMO->mfLon;
            }
        }
    }

    if (lon_vect.size() <= 1) return;

    if (currentHook == -1)
    {
        SetHookID(cycleEast ? westId : eastId);
        SendGroupHookMessage();
        return;
    }

    double closestOffset = 99.9;
    long closestId = -1;

    // find closest friendly to the east
    for (size_t k=0; k<lon_vect.size(); k++)
    {
        double offset = cycleEast ? (lon_vect[k] - currentLon_rad) : (currentLon_rad - lon_vect[k]);
        if ((offset > 0) && (offset < closestOffset))
        {
            closestOffset = offset;
            closestId = id_vect[k];
        }
    }

    if (closestId != -1)
    {
        SetHookID(closestId);
        SendGroupHookMessage();
    }
    else if (westId != -1)
    {
        wxASSERT(eastId != -1);
        SetHookID(cycleEast ? westId : eastId);
        SendGroupHookMessage();
    }

}

void tcTacticalMapView::DeactivateMapCommand() 
{
    mbMapCmdActive = false; 
    meMapCmd = MC_NONE;

    overlay->SetInteractionBlocked(false);
}

/**
* Send command to delete point currently being edited
* and clear waypoint editing
*/
void tcTacticalMapView::DeleteEditPoint()
{
    if (editPointIdx < 1) return;

    if (navPointsMissionId == -1)
    {
        wxString argString = wxString::Format(",%d", editPointIdx-1);
		mpCommandInterface->AddPythonCommandGeneral("DeleteWaypoint", argString.ToStdString(), hookedId);
    }
    else
    {
        wxString argString = wxString::Format(",%d,%d", navPointsMissionId, editPointIdx-1);
        mpCommandInterface->AddPythonCommandGeneral("DeleteMissionWaypoint", argString.ToStdString(), hookedId);
    }

    editPointIdx = -1;

}

/**
* Draws selection box if left mouse button is down
*/
void tcTacticalMapView::DrawSelectionBox() 
{
    if ((!isLButtonDown) || IsMapCmdActive() || (editPointIdx >= 0)||(insertPointEditIdx >= 0) ) return;

	Vec4 color(1, 1, 1, 1);

    int xLeft = min(buttonDownPoint.x, mpointMouse.x);
    int yTop = min(buttonDownPoint.y, mpointMouse.y);
    int width = abs(mpointMouse.x - buttonDownPoint.x);
    int height = abs(mpointMouse.y - buttonDownPoint.y);

    DrawRectangleR(xLeft, yTop, width, height, color);

}

/**
* Show game speed (time acceleration factor)
* For multiplayer also shows requested game speed and fastest request
*/
void tcTacticalMapView::DrawGameSpeed()
{
    unsigned teamSpeed = 0;
    unsigned fastestSpeed = 0;
    unsigned currentSpeed = 0;

    tcSimState* simState = tcSimState::Get();
    if (!simState->IsMultiplayerActive())
    {
        currentSpeed = unsigned(simState->GetTimeAcceleration());
        teamSpeed = currentSpeed;
        fastestSpeed = currentSpeed;
    }
    else
    {
        network::tcMultiplayerInterface* multiplayerInterface = network::tcMultiplayerInterface::Get();

        if (simState->IsMultiplayerServer())
        {
            teamSpeed = (unsigned)simState->GetTimeAcceleration();
        }
        else
        {
            teamSpeed = multiplayerInterface->GetTeamGameSpeed();
        }

        fastestSpeed = multiplayerInterface->GetFastestGameSpeed();
        currentSpeed = unsigned(simState->GetTimeAcceleration());
    }

    size_t nTeamBars = 0;
    size_t nFastestBars = 0;
    size_t nCurrentBar = 0;

    // to support dev mode allowance for faster than 120, just limit to 7 bars in this case
    teamSpeed = std::min(teamSpeed, (unsigned)120);
    fastestSpeed = std::min(fastestSpeed, (unsigned)120);
    currentSpeed = std::min(currentSpeed, (unsigned)120);

    switch (teamSpeed)
    {
    case 0: nTeamBars = 0; break;
    case 1: nTeamBars = 1; break;
    case 2: nTeamBars = 2; break;
    case 4: nTeamBars = 3; break;
    case 10: nTeamBars = 4; break;
    case 30: nTeamBars = 5; break;
    case 60: nTeamBars = 6; break;
    case 120: nTeamBars = 7; break;
    default: wxASSERT(false); break;
    }

    switch (fastestSpeed)
    {
    case 0: nFastestBars = 0; break;
    case 1: nFastestBars = 1; break;
    case 2: nFastestBars = 2; break;
    case 4: nFastestBars = 3; break;
    case 10: nFastestBars = 4; break;
    case 30: nFastestBars = 5; break;
    case 60: nFastestBars = 6; break;
    case 120: nFastestBars = 7; break;
    default: wxASSERT(false); break;
    }

    switch (currentSpeed)
    {
    case 0: nCurrentBar = 0; break;
    case 1: nCurrentBar = 1; break;
    case 2: nCurrentBar = 2; break;
    case 4: nCurrentBar = 3; break;
    case 10: nCurrentBar = 4; break;
    case 30: nCurrentBar = 5; break;
    case 60: nCurrentBar = 6; break;
    case 120: nCurrentBar = 7; break;
    default: wxASSERT(false); break;
    }

    nFastestBars = std::max(nFastestBars, nTeamBars); // team can't be faster than fastest

    float xbar = 670.0f;
    float ybar = 40.0f;
    float wbar = 8.0f;
    float hbar = 6.0f;

    const Vec4 emptyColor(0.2f, 0.2f, 0.2f, 0.5f);
    const Vec4 teamColor(0.2f, 0.2f, 1, 0.7f);
    const Vec4 fastestColor(1, 0.2f, 0.2f, 0.7f);
    const Vec4 pausedColor(1, 0.2f, 0.2f, 0.7f);

    float x = xbar;
    float y = ybar;

    for (size_t k=0; k<nTeamBars+1; k++)
    {
        if (nCurrentBar > 0)
        {
            DrawRectangleR(x, y, wbar, hbar, teamColor, FILL_ON);
        }
        else
        {
            DrawRectangleR(x, y, wbar, hbar, pausedColor, FILL_ON);
        }

        x += wbar + 2.0f;
    }

    for (size_t k=nTeamBars+1; k<nFastestBars+1; k++)
    {
        DrawRectangleR(x, y, wbar, hbar, fastestColor, FILL_ON);

        x += wbar + 2.0f;
    }

    for (size_t k=nFastestBars+1; k<8; k++)
    {
        DrawRectangleR(x, y, wbar, hbar, emptyColor, FILL_ON);

        x += wbar + 2.0f;
    }

    // draw outline around current speed bar
    x = xbar + float(nCurrentBar)*(wbar + 2.0f);
    DrawRectangleR(x, y, wbar, hbar, Vec4(1, 1, 1, 0.7f), FILL_OFF);




}


/**
* Draws tactical map grid
*/
void tcTacticalMapView::DrawGrid() 
{
    float lat,lon;
    tcPoint pgeo,pscreen;

    if (mfGridSize_rad == 0) {return;}
	Vec4 color(0.69f, 0.69f, 0.69f, 0.5f);
   
    float left_rad = mfGridBaseLon_rad;
    float right_rad = mrectCurrentView.right;
    if (right_rad < left_rad) right_rad += C_TWOPI;

    // change this to set range based on what will cover the screen as well
    for(lon=left_rad; lon<=right_rad; lon+=mfGridSize_rad)
	{
        pgeo.x = lon; pgeo.y = 0;
        pscreen = GeoToScreen(pgeo);
		if ((pscreen.x > 0) && (pscreen.x < mnWidth))
		{
			DrawLineR(pscreen.x, 0, pscreen.x, mnHeight, color);
		}
    }
    for(lat=mfGridBaseLat_rad; lat<=mrectCurrentView.top; lat+=mfGridSize_rad)
	{
        pgeo.y = lat; pgeo.x = 0;
        pscreen = GeoToScreen(pgeo);
		if ((pscreen.y > 0) && (pscreen.y < mnHeight))
		{
			DrawLineR(0, pscreen.y, mnWidth, pscreen.y, color);
		}
    }
}

/**
* Draws tactical map scale bar
*/
void tcTacticalMapView::DrawScaleBar() 
{
    float fKmPerPel;
    int nBarX1, nBarX2;

	// faster, but this only works if only one tcTacticalMapView is instantiated
	// Move to private members
    // ?? not sure what above intends, dewitt JUN2008
	static float lastScaleX = 0;
	static float fKmScale;
	static int nScaleBarWidth;

	if (mfScaleX_radppel != lastScaleX)
	{
		fKmPerPel = mfScaleY_radppel*C_RADTOKM; // since X is really radians of longitude, not radians at equator, just use Y
		// calculate closest power of 10 km dist that corresponds to (about) 100 pixels
		fKmScale = expf(logf(10.0f)*floorf(log10f(fKmPerPel*180.0f)));  
		nScaleBarWidth = (int)(fKmScale*C_KMTORAD*mfScaleY_pelprad);

		lastScaleX = mfScaleX_radppel;
	}




    tcString sText;

    float scaleUserUnits = units->UserDistanceUnits(1000.0f * fKmScale);
    
    if (scaleUserUnits >= 1.0f) 
	{
        sText.Format("%3.0f %s", scaleUserUnits, units->GetDistanceUnitLabel());
    }
    else 
	{
        sText.Format("%1.3f %s", scaleUserUnits, units->GetDistanceUnitLabel());
    }

	Vec4 color(0.784f, 0.784f, 0.784f, 1.0f);

	DrawTextR(sText.GetBuffer(), leftMargin + 50.0, mnHeight - 225.0, 
        defaultFont.get(), color, 16.0, CENTER_CENTER);

    nBarX1 = leftMargin + 120;
    nBarX2 = nBarX1 + nScaleBarWidth;

	color = Vec4(1, 1, 1, 1);

    DrawLineR(nBarX1, mnHeight-215, nBarX2, mnHeight-215, color); // draw horizontal piece
    DrawLineR(nBarX1, mnHeight-215-5, nBarX1, mnHeight-215+5, color); // draw left vertical piece
    DrawLineR(nBarX2, mnHeight-215-5, nBarX2, mnHeight-215+5, color); // draw right vert piece
}

/**
*
*/
void tcTacticalMapView::DrawTerrainText() 
{
    tcPoint p;
    float fTerrainHeight_m;
    tcString sText;

    p = ScreenToGeo(mpointMouse);
    //fTerrainHeight_m = mpMapData->GetTerrainHeightLowRes(C_180OVERPI*p.x,C_180OVERPI*p.y);

	/* replaced with high res lookup, note converted to deg and then back in
	** tcMapData::GetTerrainHeightHighRes
	*/
	fTerrainHeight_m = mpMapData->GetTerrainHeightHighRes(C_180OVERPI*p.x, C_180OVERPI*p.y);

    char ns;
    char ew;
    if (p.y < 0) {ns = 'S';p.y = -p.y;}
    else {ns = 'N';}
    if (p.x < 0) {ew = 'W';p.x = -p.x;}
    else {ew = 'E';}

    float lat_deg = C_180OVERPI*p.y;
    float lon_deg = C_180OVERPI*p.x;
    if (lon_deg < -180.0f) lon_deg += 360.0f;
    else if (lon_deg >= 180.0f) lon_deg -= 360.0f;

	// display more precision if zoomed in close
	if (mfLonWidth > 0.15f)
	{
		sText.Format("(%3.1f%c,%3.1f%c) %s", lat_deg, ns, lon_deg, ew,
			units->GetUserAltitudeString(fTerrainHeight_m));
	}
	else
	{
		sText.Format("(%3.3f%c,%3.3f%c) %s", lat_deg, ns, lon_deg, ew,
			units->GetUserAltitudeString(fTerrainHeight_m));
	}
    
	Vec4 color(1, 1, 1, 1);
	
	DrawTextR(sText.GetBuffer(), leftMargin + 50.0, mnHeight - 250.0, 
        defaultFont.get(), color, 16.0, LEFT_BASE_LINE);
}

/**
*
*/
void tcTacticalMapView::DrawMapCmd(tcMapObj *pMO, teMapCmdType type) 
{
    Vec4 color(1, 1, 1, 1);
    int x = mpointMouse.x;
    int y = mpointMouse.y;

	switch (type) 
	{
	case MC_HEADING:
		{
			if (pMO == NULL) {return;} // error
			tcPoint tcPointStart = GeoToScreen(pMO->mfLon,pMO->mfLat);
			DrawLineR(tcPointStart.x, tcPointStart.y,
				mpointMouse.x, mpointMouse.y, color);
		}
		break;
	case MC_TARGET: 
		DrawLineR(x, y-8, x, y+8, color);
		DrawLineR(x-8, y, x+8, y, color);
		break;
	case MC_DATUM: 
		DrawLineR(x-8, y-8, x+8, y+8, color);
		DrawLineR(x-8, y+8, x+8, y-8, color);
		break;
    case MC_RANGE:
		DrawMapCmdRange();
        break;
    case MC_BOX:
        if (isLButtonDown)
        {
            float x1, x2, y1, y2;
            if (x > buttonDownPoint.x)
            {
                x1 = buttonDownPoint.x;
                x2 = x;
            }
            else
            {
                x2 = buttonDownPoint.x;
                x1 = x;
            }
            if (y > buttonDownPoint.y)
            {
                y1 = buttonDownPoint.y;
                y2 = y;
            }
            else
            {
                y2 = buttonDownPoint.y;
                y1 = y;
            }

            tcRect r(x1, x2, y1, y2);
            DrawThickRectangleR(r, 2.0f, color);
        }
        else
        {
            DrawLineR(x-8, y-8, x+8, y+8, color);
            DrawLineR(x-8, y+8, x+8, y-8, color);
        }
        break;
    case MC_LINE:
        if (isLButtonDown)
        {
            DrawThickLineR(x, y, buttonDownPoint.x, buttonDownPoint.y, 2.0f, color);
        }
        else
        {
            DrawLineR(x-8, y-8, x+8, y+8, color);
            DrawLineR(x-8, y+8, x+8, y-8, color);
        }
        break;
        
	default:
		break;
	}
}

/**
* Draw circle (ellipse on screen) of constant range. If no object is hooked, center is 
* the mouse position when command was activated. Otherwise the center is the location of
* the hooked object. Heading and range are relative to current mouse position.
*/
void tcTacticalMapView::DrawMapCmdRange() 
{
    bool isObjectHooked = hookedId.size() > 0;
    tcPoint pCenter;
    tcPoint screenCenter; // in screen coordinates
    if (isObjectHooked)
    {
        pCenter.x = mfHookLon;
        pCenter.y = mfHookLat;
        screenCenter = GeoToScreen(pCenter);
    }
    else
    {
        pCenter = ScreenToGeo(mapCommandStartLocation);
        screenCenter.x = float(mapCommandStartLocation.x);
        screenCenter.y = float(mapCommandStartLocation.y);
    }

    tcPoint pCurrent = ScreenToGeo(mpointMouse);
    float range_rad = nsNav::GCDistanceApprox_rad(pCenter.y, pCenter.x, pCurrent.y, pCurrent.x);
    float bearing_rad = nsNav::GCHeadingApprox_rad(pCenter.y, pCenter.x, pCurrent.y, pCurrent.x);
    if (bearing_rad < 0) bearing_rad += C_TWOPI; // force 0 - 360 format

    float ellipseHeight = GeoLatExtentToScreen(2.0f * range_rad);
    float ellipseWidth = GeoLonExtentToScreen(2.0f * range_rad / cosf(pCenter.y));
    
    // draw ellipse from center passing through current with latitude based eccentricity
    Vec4 lineColor(1.0f, 1.0f, 1.0f, 0.8f);
    boost::shared_ptr<tcGeometry> rangeCircle = CreatePieGeometry(ellipseWidth, ellipseHeight, -180, 180, lineColor, FILL_OFF);
    DrawGeometryR(rangeCircle.get(), screenCenter.x, screenCenter.y);

    // draw line from center to current
    DrawLineR(screenCenter.x, screenCenter.y, mpointMouse.x, mpointMouse.y, lineColor);

    // draw text with range and bearing info    
    Vec4 fontColor(1.0f, 1.0f, 1.0f, 0.9f);
    float range_m = C_RADTOM * range_rad;
    wxString s;
    s.Printf("%s %.0f deg", units->GetUserDistanceString(range_m), C_180OVERPI * bearing_rad);

    // draw text halfway between center and current mouse pos
    float xtext = 0.5f * (screenCenter.x + float(mpointMouse.x));
    float ytext = 0.5f * (screenCenter.y + float(mpointMouse.y));

    DrawTextR(s.c_str(), xtext, ytext, 
        defaultFont.get(), fontColor, 12.0, CENTER_CENTER);
}

/**
* Draws nav points for hooked platform
*/
void tcTacticalMapView::DrawNavPoints()
{
    UpdateWaypointEditor();

    size_t nPoints = navPointsPrimary.size();
    if (nPoints < 2) return;

	/* if a waypoint is being edited, draw the edit point at the current mouse position
	** by substituting edit point for appropriate point in navpoint array
	*/
	if ((editPointIdx > 0) && ((size_t)editPointIdx < nPoints))
	{
        navPointsPrimary[editPointIdx].screen = tcPoint((float)mpointMouse.x, (float)mpointMouse.y);

		tcPoint editPoint = ScreenToGeo(navPointsPrimary[editPointIdx].screen.x, 
			                            navPointsPrimary[editPointIdx].screen.y);
		navPointsPrimary[editPointIdx].geo.mfLon_rad = editPoint.x;
		navPointsPrimary[editPointIdx].geo.mfLat_rad = editPoint.y;
	}


    // form vector of line segments to draw
    // insert current and insert waypoints into vector

    std::vector<tcPoint> p1;
    std::vector<tcPoint> p2;

    if ((currentPointIdx > 0) && ((currentPointIdx+1) < nPoints))
    {
        // add segments without currentPoint
        for (size_t n=1; (n+1)<nPoints; n++)
        {
            p1.push_back(navPointsPrimary[n].screen);
            p2.push_back(navPointsPrimary[n+1].screen);
        }

        // insert current point
        p2.insert(p2.begin()+currentPointIdx-1, navPointsPrimary[0].screen);
        p1.insert(p1.begin()+currentPointIdx, navPointsPrimary[0].screen);
    }
    else if (currentPointIdx == 0)
    {   // already in order so just add starting with current point
        for (size_t n=0; (n+1)<nPoints; n++)
        {
            p1.push_back(navPointsPrimary[n].screen);
            p2.push_back(navPointsPrimary[n+1].screen);
        }
    }
    else // gone beyond last waypoint !?, ignore current point
    {
        for (size_t n=1; (n+1)<nPoints; n++)
        {
            p1.push_back(navPointsPrimary[n].screen);
            p2.push_back(navPointsPrimary[n+1].screen);
        }
    }

    size_t futureSegmentIdx = currentPointIdx; // first segment that represents future legs (current point to next waypoint)

    // if insert edit is active, insert this waypoint for draw purposes
    if (insertPointEditIdx >= 0)
    {
        tcPoint mousePoint((float)mpointMouse.x, (float)mpointMouse.y);

        // insert current point
        p2.insert(p2.begin()+insertPointEditIdx, mousePoint);
        p1.insert(p1.begin()+insertPointEditIdx+1, mousePoint);
    }

    if (navPointsMissionId != -1)
    { // change up style as cue that user is editing mission route
        DrawNavPointsMission(p1, p2);
        return;
    }

	const Vec4 color(1, 1, 1, 0.5);
    const Vec4 colorCompleted(0.5, 0.5, 1, 0.5);
	const Vec4 editColor(1, 1, 1, 1);
    const Vec4 editLegColor(1, 1, 1, 1);

    // draw completed legs
    //for (size_t n=0; n<futureSegmentIdx; n++)
    //{
    //    DrawLineR(p1[n].x, p1[n].y, p2[n].x, p2[n].y, colorCompleted);
    //}

    // draw future legs
    for (size_t n=futureSegmentIdx; n<p1.size(); n++)
    {
        DrawLineR(p1[n].x, p1[n].y, p2[n].x, p2[n].y, color);
    }

    // draw waypoints
    int nWaypoints = int(nPoints);
    for (int n=currentPointIdx; n<(nWaypoints-1); n++) 
	{
        const tcPoint& p = navPointsPrimary[n+1].screen;

		if ((n != (editPointIdx - 1)) && (n != (detailedEditPointIdx - 1)))
		{
			DrawRectangleR(p.x - 2.0, p.y - 3.0, 4.0, 6.0, color, tc3DWindow2::FILL_ON);
		}
        else
		{
			DrawRectangleR(p.x - 3.0, p.y - 4.0, 6.0, 8.0, editColor, tc3DWindow2::FILL_ON);
		}

        if (navPointsPrimary[n+1].referenceMode > 0)
        {
            if (navPointsPrimary[n+1].referenceMode == 2) // heading reference
            {
                DrawPieSection(p.x, p.y, 8.0f, 8.0f, 8.0f, 8.0f,
                    0, C_TWOPI, color, tc3DWindow2::FILL_OFF);
            }
            else
            {
                DrawRectangleR(p.x-7.0f, p.y-7.0f, 14.0f, 14.0f, color);
            }
        }

        for (size_t k=0; k<navPointsPrimary[n+1].tasks.size(); k++)
        {
            DrawTextR(navPointsPrimary[n+1].tasks[k].c_str(), p.x, p.y + 10.0f + 12.0f*float(k), defaultFont.get(),
                color, 11.0f, LEFT_CENTER);
        }
    }

    // draw insert waypoint
    if (insertPointEditIdx >= 0)
    {
        tcPoint p((float)mpointMouse.x, (float)mpointMouse.y);
        DrawRectangleR(p.x - 3.0, p.y - 4.0, 6.0, 8.0, editColor, tc3DWindow2::FILL_ON);
    }

}


void tcTacticalMapView::DrawNavPointsOther()
{
	const Vec4 color(0.7f, 0.7f, 0.8f, 0.4f);

    size_t nSets = navPointsOther.size();

    for (size_t n=0; n<nSets; n++)
    {
        size_t nPoints = navPointsOther[n].size();
        for (size_t k=1; k<nPoints; k++)
        {
            const tcPoint& p1 = navPointsOther[n][k-1].screen;
            const tcPoint& p2 = navPointsOther[n][k].screen;

            DrawLineR(p1.x, p1.y, p2.x, p2.y, color);
        }
    }
}




/**
* Version for drawing different graphics style for attack mission route
*/
void tcTacticalMapView::DrawNavPointsMission(const std::vector<tcPoint>& p1, const std::vector<tcPoint>& p2) 
{
    size_t futureSegmentIdx = currentPointIdx;

	const Vec4 color(0.8f, 0.3f, 0.2f, 0.6f);
    const Vec4 colorCompleted(1, 0.5, 1, 0.5);
    const Vec4 waypointColor(0, 0, 0, 0.75f);
	const Vec4 editColor(1, 1, 1, 1);
    const float w = 2.0f;
    
    // draw completed legs
    //for (size_t n=0; n<futureSegmentIdx; n++)
    //{
    //    DrawThickLineR(p1[n].x, p1[n].y, p2[n].x, p2[n].y, w, colorCompleted);
    //}

    // draw future legs
    for (size_t n=futureSegmentIdx; n<p1.size(); n++)
    {
        DrawThickLineR(p1[n].x, p1[n].y, p2[n].x, p2[n].y, w, color);
    }

    // draw waypoints
    int nWaypoints = int(navPointsPrimary.size());
    for (int n=currentPointIdx; n<(nWaypoints-1); n++) 
	{
        const tcPoint& p = navPointsPrimary[n+1].screen;

		if ((n != (editPointIdx - 1)) && (n != (detailedEditPointIdx - 1)))
		{
			DrawRectangleR(p.x - 4.0, p.y - 5.0, 7.0, 9.0, waypointColor, tc3DWindow2::FILL_ON);
		}
        else
		{
			DrawRectangleR(p.x - 4.0, p.y - 5.0, 7.0, 9.0, editColor, tc3DWindow2::FILL_ON);
		}

        if (navPointsPrimary[n+1].referenceMode > 0)
        {            
            if (navPointsPrimary[n+1].referenceMode == 2) // heading reference
            {
                DrawPieSection(p.x, p.y, 8.0f, 8.0f, 8.0f, 8.0f,
                    0, C_TWOPI, waypointColor, tc3DWindow2::FILL_OFF);
            }
            else
            {
                DrawRectangleR(p.x-7.0f, p.y-7.0f, 14.0f, 14.0f, waypointColor);
            }
        }


        for (size_t k=0; k<navPointsPrimary[n+1].tasks.size(); k++)
        {
            DrawTextR(navPointsPrimary[n+1].tasks[k].c_str(), p.x, p.y + 10.0f + 12.0f*float(k), defaultFont.get(),
                Vec4(1, 1, 1, 1), 11.0f, LEFT_CENTER);
        }
    }

    // draw insert waypoint
    if (insertPointEditIdx >= 0)
    {
        tcPoint p((float)mpointMouse.x, (float)mpointMouse.y);
        DrawRectangleR(p.x - 3.0, p.y - 4.0, 7.0, 9.0, editColor, tc3DWindow2::FILL_ON);
    }
}

/**
* Draw indicator symbol box at appropriate location, for error indication currently
*/
void tcTacticalMapView::DrawIndicator(int anType) 
{
    return;
    // TODO: update this
    /*
    RECT r;
    int nThickness = 2;

    if (mpDDS_Offscreen==NULL) {return;}

    switch(anType) {
    case 0:   
    bltFX.dwFillColor = 0xC02020; 
    r.top = mnHeight-20;
    r.bottom = mnHeight-10;
    r.left = 10;
    r.right = 20;
    hResult = mpDDS_Offscreen->Blt(&r, NULL, NULL, dwFlags, &bltFX);
    break;
    case 1:
    bltFX.dwFillColor = 0xC0C0C0; 
    r.top = mnHeight-20;
    r.bottom = mnHeight-10;
    r.left = 30;
    r.right = 40;
    hResult = mpDDS_Offscreen->Blt(&r, NULL, NULL, dwFlags, &bltFX);
    break;
    default:
    break;
    }
    */
}

/**
* Iterates through mapGraphics and calls Draw method for objects.
*/
void tcTacticalMapView::DrawSpecial()
{
    int nObjects = (int)specialGraphics.size();
    for(int n=0; n<nObjects; n++)
    {
        tcMapObject* obj = specialGraphics[n];
        obj->Draw(this);
    }
}

/**
* Main graphics update routine
*/
void tcTacticalMapView::Draw() 
{
    StartDraw();

    static int nDraw = 0;

    // periodically update options
    if (((nDraw++) & 0xFF) == 0)
    {
        UpdateOptions();
    }

    UpdateViewCenterOnHooked();

    UpdateButtons();

    tcMapView::Thaw(); // unfreeze every Draw() call, works with Freeze() to stop resize flicker 

	unsigned timeCount = tcTime::Get()->Get30HzCount();

	if (scrollActive && (timeCount - lastScrollTime >= 1))
	{
        ScrollMap(scrollDirection);
		lastScrollTime = timeCount;
    }

    // SetView called here to avoid artifacts from terrainview being out of sync with mapview
    terrainView->SetView(mrectCurrentView); 

    terrainView->Draw();

    tcMapObject::SetMapView(this);
    DrawSpecial();


    /*** Draw nav points ***/
    DrawNavPoints();
    if (drawNavPointsMode > 0) DrawNavPointsOther();

    /*** Draw grid ***/
    DrawGrid(); // disabled until the terrain view graphics are ported to OSG

    /*** Draw scale bar ***/
    DrawScaleBar();

    /*** Draw terrain height text ***/
    DrawTerrainText();

    /*** Draw selection box ***/
	DrawSelectionBox();

    /*** Draw date and time text ***/
	DrawTime();
  
    /*** Draw time acceleration graphics for multiplayer ***/
    DrawGameSpeed();


    /*** Draw map command graphics ***/
    long currentHook;
    if (GetHookCount())
    {
        currentHook = GetHookID();
    }
    else
    {
        currentHook = -1;
    }

    for(int i=0; (i<(int)mnObjCount)&&(i<MAXMAPOBJ); i++) 
    {
        if (maMapObj[i].mbExists)
        {
			DrawSymbol2(&maMapObj[i]);
            if (meMapCmd != MC_NONE) 
			{
                if ((maMapObj[i].mnID == currentHook)&&
                    (meMapCmd == MC_HEADING)) 
                {
                    DrawMapCmd(&maMapObj[i],meMapCmd);
                }
            }
        }
    }

    if ((meMapCmd != MC_NONE) && (meMapCmd != MC_HEADING))
    {
        DrawMapCmd(NULL, meMapCmd);
    }


    if (maMapObj[MAXMAPOBJ-1].mbExists)  {DrawIndicator(0);} // full maMapObj
    if (mnGameMode != GAMEMODE_NORMAL) {DrawIndicator(1);}

    //overlay->Draw();

	FinishDraw();
}

void tcTacticalMapView::DrawTime()
{
	tcString sText;
    tcSimState* simState = tcSimState::Get();

	// draw top info string based on mnGameMode, this function should go elsewhere? strange to have in map
	Vec4 color(1.0, 1.0, 1.0, 1);

	if (mnGameMode == GAMEMODE_NORMAL) 
	{
		if (showFrameCounter)
		{
            tcTVEngine* engine = tcTVEngine::Get();
            const float kB_to_MB = 0.000976563f;

//            float freeMemory_MB = kB_to_MB * float((engine->GetFreeTextureMemory()) >> 10);
            float usedMemory_MB = kB_to_MB * float((engine->GetUsedTextureMemory()) >> 10);
           
			if (mfFrameRate != 0) 
			{
				sText.Format("%s [%3.0f FPS] %.0f MB", dateTime.c_str(), mfFrameRate,
                    usedMemory_MB);   
			}
			else 
			{
				sText.Format("%s [ -- FPS] %.0f MB", dateTime.c_str(), 
                    usedMemory_MB);   
			}
          
            if (simState->IsMultiplayerClient())
            {
                double multiplayerTimeLag_s = simState->GetMultiplayerTimeLag();
                tcString lagText;

                lagText.Format(" %.2f s", multiplayerTimeLag_s);

                sText += lagText.c_str();
            }
		}
		else
		{
			sText.Format("%s", dateTime.c_str());
		}
	}
	else if (mnGameMode == GAMEMODE_PAUSED) 
	{
		sText.Format("%s ",dateTime.c_str()); 
		color = Vec4(1, 0.5, 0.5, 1);
	}
	else 
	{
        sText.Format("%s (EDIT %s)",dateTime.c_str(), simState->GetScenarioName()); 

		color = Vec4(0.8f, 0.8f, 1.0f, 1);
	}

	DrawTextR(sText.GetBuffer(), leftMargin + 40.0, 35.0, 
		defaultFont.get(), color, 16.0, LEFT_BASE_LINE);
}


#if 0
osg::Image* tcTacticalMapView::LoadSymbolImage(const char *azSymbolName) 
{
    char path[64];
    char zBuff[128];

    strcpy(path,SYMBOLOGY_PATH);
    strcpy(zBuff, path);
    strcat(zBuff, azSymbolName);

    return LoadImage(zBuff);
}
#endif



long tcTacticalMapView::GetFormationEditId() const
{
	return formationEditLeaderId;
}


/**
* @return number of hooked objects
*/
size_t tcTacticalMapView::GetHookCount()
{
    return hookedId.size();
}

/**
* @return vector of hooked group indices
*/
std::vector<long>& tcTacticalMapView::GetHookedGroup()
{
    return hookedId;
}

/**
* @return hook ID of hooked unit with index of idx, or -1 if invalid
*/
long tcTacticalMapView::GetHookID(size_t idx)
{
    if (idx < GetHookCount())
    {
        return hookedId[idx];
    }
    else
    {
        return -1;
    }
}

/**
* For variable leader mode, calculate the length in pixels of the
* leader
*/
float tcTacticalMapView::GetLeaderLength(float heading_rad, float speed_kts, int symbol) const
{
    const float fixedLeaderLength = 18.0f;

    float leadTime_s = 0;

    switch (symbol)
    {
    case SYMBOL_UNKNOWN:
	case SYMBOL_SURFACE:
	case SYMBOL_SMALLSURFACE:
	case SYMBOL_LARGESURFACE:
	case SYMBOL_CARRIER:
    case SYMBOL_SURFACEGROUP:
    case SYMBOL_CARRIERGROUP:
    case SYMBOL_SUBSURFACE:
	case SYMBOL_SUBMARINE:
	case SYMBOL_TORPEDO:
	case SYMBOL_FIXED:
    case SYMBOL_AIRFIELD:
	case SYMBOL_GROUNDVEHICLE:
        leadTime_s = surfLeaderTime_s;
        break;

    case SYMBOL_AIR:
    case SYMBOL_FIXEDWING:
    case SYMBOL_MISSILE:
    case SYMBOL_HELO:
	    leadTime_s = airLeaderTime_s;
        break;
    default:
        break;
    }

    if (leadTime_s > 0)
    {
        return leadTime_s * C_KTSTORADPS * speed_kts * mfScaleY_pelprad;
    }
    else
    {
        return fixedLeaderLength;
    }
}

tcMapOverlay* tcTacticalMapView::GetMapOverlay() const
{
    return overlay;
}

/**
* @return true if id matches first element in hookedId vector
*/
bool tcTacticalMapView::IsFirstHook(long id)
{
	if (hookedId.size() == 0) return false;

	return (hookedId[0] == id);
}

/**
* Performs simple search for match by iterating through
* elements of hookedId vector. Could get slow for large sizes.
* @return true if id matches any elements in hookedId vector
*/
bool tcTacticalMapView::IsHooked(long id)
{
    for(std::vector<long>::iterator iter = hookedId.begin()        
        ; iter != hookedId.end(); ++iter)
    {
        if ((*iter) == id) return true;
    }
    return false;
}

bool tcTacticalMapView::IsMapCmdActive() const
{
    return mbMapCmdActive != 0;
}

/**
* Creates default tcGeometry object for symbol
*/
boost::shared_ptr<tcGeometry> tcTacticalMapView::CreateSymbolGeometry()
{
	return boost::shared_ptr<tcGeometry>(new tcGeometry);

#if 0
	osg::Vec4Array* colors = new osg::Vec4Array;
	colors->push_back(Vec4(1.0f, 1.0f, 1.0f, 1.0f));
	symbol->setColorArray(colors);
	symbol->setColorBinding(tcGeometry::BIND_OVERALL);

	symbol->setUseDisplayList(true);

	// set state
	osg::StateSet* stateSet = symbol->getOrCreateStateSet();
	stateSet->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF);
	stateSet->setMode(GL_DEPTH_WRITEMASK, osg::StateAttribute::OFF);
	stateSet->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	stateSet->setMode(GL_BLEND, osg::StateAttribute::ON);

//   osg::LineWidth  *lw = new osg::LineWidth(1.5);
//   stateSet->setAttribute(lw, osg::StateAttribute::ON);

	stateSet->setRenderBinDetails(baseRenderBin + rectRenderBin, "RenderBin");
#endif

}

/**
* Create quad, textured with image specified by <symbolname>
*/
boost::shared_ptr<tcGeometry> tcTacticalMapView::CreateTexturedSymbol(const char* symbolName)
{
    float width = 20.0f;
	
	wxString texturePath = wxString::Format("symbology\\%s", symbolName);

	return tc3DWindow2::CreateTexturedSymbol(texturePath.c_str(), width);
}

#if 0
/**
* Angle of zero is up, angle increases in clockwise direction
* startAngle must be less than stopAngle (can use negative angles)
* @param startAngle in degrees
* @param stopAngle in degrees
*/
void tcTacticalMapView::AddArcPrimitive(tcGeometry* symbol, osg::Vec3Array* vertices, 
										float xc, float yc, float width, float height, 
										float startAngle, float stopAngle, unsigned int nPoints)
{
	unsigned int primitiveBaseIdx = vertices->size();

	wxASSERT(startAngle < stopAngle);
	wxASSERT(nPoints > 1);

	startAngle *= C_PIOVER180;
	stopAngle *= C_PIOVER180;

	float deltaAngle = (stopAngle - startAngle) / float(nPoints - 1);
	float half_width = 0.5f * width;
	float half_height = 0.5f * height;

	float angle = startAngle;
	for (unsigned int n = 0; n < nPoints; n++)
	{
		float x = xc + half_width * sinf(angle);
		float y = yc + half_height * cosf(angle);

		vertices->push_back(osg::Vec3(x, y, 0));
		angle += deltaAngle;
	}

	symbol->addPrimitiveSet(new osg::DrawArrays(GL_LINE_STRIP, primitiveBaseIdx, nPoints));
}
#endif

/**
* Creates tcGeometry object for requested NTDS symbol
*/
boost::shared_ptr<tcGeometry> tcTacticalMapView::DrawNTDSSurface(tcAllianceInfo::Affiliation affil) 
{

//    float w = 8.0f;
	
	return CreateSymbolGeometry();
#if 0
	// set color
	osg::Vec4Array* colors = new osg::Vec4Array;
	colors->push_back(GetAffiliationColor(affil));
	symbol->setColorArray(colors);
	symbol->setColorBinding(tcGeometry::BIND_OVERALL);

	// create vertex array
	osg::Vec3Array* vertices = new osg::Vec3Array;
	symbol->setVertexArray(vertices);

	switch (affil) 
	{
	case FRIENDLY:
	case NEUTRAL:
		{
			AddArcPrimitive(symbol, vertices, 0, 0, 2*w, 2*w, -180, 180, 32);
			break;
		}
	case UNKNOWN:
		{
			float wu = 0.9 * w;

			vertices->push_back(osg::Vec3(-wu, wu, 0));
			vertices->push_back(osg::Vec3(-wu, -wu, 0));
			vertices->push_back(osg::Vec3(wu, -wu, 0));
			vertices->push_back(osg::Vec3(wu, wu, 0));
			symbol->addPrimitiveSet(new osg::DrawArrays(GL_LINE_LOOP,0,4));
			break;
		}
	case HOSTILE:
		{
			vertices->push_back(osg::Vec3(0, w, 0));
			vertices->push_back(osg::Vec3(-w, 0, 0));
			vertices->push_back(osg::Vec3(0, -w, 0));
			vertices->push_back(osg::Vec3(w, 0, 0));
			symbol->addPrimitiveSet(new osg::DrawArrays(GL_LINE_LOOP,0,4));
			break;
		}
	}
#endif

}



/**
* Creates tcGeometry object for requested NTDS symbol
*/
boost::shared_ptr<tcGeometry> tcTacticalMapView::DrawNTDSCarrier(tcAllianceInfo::Affiliation affil) 
{
//    float w = 8.0f;
	
	return CreateSymbolGeometry();
#if 0
	// set color
	osg::Vec4Array* colors = new osg::Vec4Array;
	colors->push_back(GetAffiliationColor(affil));
	symbol->setColorArray(colors);
	symbol->setColorBinding(tcGeometry::BIND_OVERALL);

	// create vertex array
	osg::Vec3Array* vertices = new osg::Vec3Array;
	symbol->setVertexArray(vertices);


	switch (affil) 
	{
	case FRIENDLY:
	case NEUTRAL:
		{
			AddArcPrimitive(symbol, vertices, 0, 0, 2*w, 2*w, -180, 180, 32);

			size_t v_idx = vertices->size();
			vertices->push_back(osg::Vec3(-2, 1-w, 0));
			vertices->push_back(osg::Vec3(-2, w-1, 0));
			vertices->push_back(osg::Vec3(2, 1-w, 0));
			vertices->push_back(osg::Vec3(2, w-1, 0));
			symbol->addPrimitiveSet(new osg::DrawArrays(GL_LINES, v_idx, 4));

			break;
		}
	case UNKNOWN:
		{
			float wu = 0.9 * w;

			vertices->push_back(osg::Vec3(-wu, wu, 0));
			vertices->push_back(osg::Vec3(-wu, -wu, 0));
			vertices->push_back(osg::Vec3(wu, -wu, 0));
			vertices->push_back(osg::Vec3(wu, wu, 0));
			symbol->addPrimitiveSet(new osg::DrawArrays(GL_LINE_LOOP,0,4));

			size_t v_idx = vertices->size();
			vertices->push_back(osg::Vec3(-2, 1-wu, 0));
			vertices->push_back(osg::Vec3(-2, wu-1, 0));
			vertices->push_back(osg::Vec3(2, 1-wu, 0));
			vertices->push_back(osg::Vec3(2, wu-1, 0));
			symbol->addPrimitiveSet(new osg::DrawArrays(GL_LINES, v_idx, 4));


			break;
		}
	case HOSTILE:
		{
			vertices->push_back(osg::Vec3(0, w, 0));
			vertices->push_back(osg::Vec3(-w, 0, 0));
			vertices->push_back(osg::Vec3(0, -w, 0));
			vertices->push_back(osg::Vec3(w, 0, 0));
			symbol->addPrimitiveSet(new osg::DrawArrays(GL_LINE_LOOP,0,4));

			size_t v_idx = vertices->size();
			vertices->push_back(osg::Vec3(-2, 3-w, 0));
			vertices->push_back(osg::Vec3(-2, w-3, 0));
			vertices->push_back(osg::Vec3(2, 3-w, 0));
			vertices->push_back(osg::Vec3(2, w-3, 0));
			symbol->addPrimitiveSet(new osg::DrawArrays(GL_LINES, v_idx, 4));

			break;
		}
	}
#endif

}


/**
* "Mark" symbol is for known objects such as shells and sonobuoys that do
* not have individual symbols, but may be shown on the map in some modes.
*/
boost::shared_ptr<tcGeometry> tcTacticalMapView::DrawDefaultMark(tcAllianceInfo::Affiliation affil)
{
//    float w = 2.0f; // symbol size
//	float h = 2.0f;

	boost::shared_ptr<tcGeometry> symbol = CreateSymbolGeometry();

    symbol->MakeBox(4.0f, 4.0f, Vec4(0.7f, 0.7f, 0.7f, 1.0f));

	return symbol;
}

/**
* NTDS ground is drawn as slightly smaller surface with horizontal bar
* underneath. This isn't a "real" NTDS symbol, but will stand-in until
* some more symbology work is done.
*/
boost::shared_ptr<tcGeometry> tcTacticalMapView::DrawNTDSGround(tcAllianceInfo::Affiliation affil) 
{
//    float w = 6.0f; // symbol size
//	float h = 4.0f;

	return CreateSymbolGeometry();

#if 0
	// set color
	osg::Vec4Array* colors = new osg::Vec4Array;
	colors->push_back(GetAffiliationColor(affil));
	symbol->setColorArray(colors);
	symbol->setColorBinding(tcGeometry::BIND_OVERALL);

	// create vertex array
	osg::Vec3Array* vertices = new osg::Vec3Array;
	symbol->setVertexArray(vertices);


	switch (affil) 
	{
	case FRIENDLY:
	case NEUTRAL:
		{
			AddArcPrimitive(symbol, vertices, 0, 0, 2*w, 2*h, -180, 180, 32);
			break;
		}
	case UNKNOWN:
		{
			vertices->push_back(osg::Vec3(-w, h, 0));
			vertices->push_back(osg::Vec3(-w, -h, 0));
			vertices->push_back(osg::Vec3(w, -h, 0));
			vertices->push_back(osg::Vec3(w, h, 0));
			symbol->addPrimitiveSet(new osg::DrawArrays(GL_LINE_LOOP,0,4));
			break;
		}
	case HOSTILE:
		{
			vertices->push_back(osg::Vec3(0, h, 0));
			vertices->push_back(osg::Vec3(-w, 0, 0));
			vertices->push_back(osg::Vec3(0, -h, 0));
			vertices->push_back(osg::Vec3(w, 0, 0));
			symbol->addPrimitiveSet(new osg::DrawArrays(GL_LINE_LOOP,0,4));
			break;
		}
	}

	size_t v_idx = vertices->size();
	vertices->push_back(osg::Vec3(w, -w, 0));
	vertices->push_back(osg::Vec3(-w, -w, 0));
	symbol->addPrimitiveSet(new osg::DrawArrays(GL_LINES, v_idx, 2));
#endif

}

/**
* Creates tcGeometry object for requested NTDS symbol
*/
boost::shared_ptr<tcGeometry> tcTacticalMapView::DrawNTDSUnknown(tcAllianceInfo::Affiliation affil) 
{
//    float w = 4.0f;
	
	return CreateSymbolGeometry();

#if 0
	// set color
	osg::Vec4Array* colors = new osg::Vec4Array;
	colors->push_back(GetAffiliationColor(affil));
	symbol->setColorArray(colors);
	symbol->setColorBinding(tcGeometry::BIND_OVERALL);

	// create vertex array
	osg::Vec3Array* vertices = new osg::Vec3Array;
	symbol->setVertexArray(vertices);

	vertices->push_back(osg::Vec3(-w, w, 0));
	vertices->push_back(osg::Vec3(-w, -w, 0));
	vertices->push_back(osg::Vec3(w, -w, 0));
	vertices->push_back(osg::Vec3(w, w, 0));

	symbol->addPrimitiveSet(new osg::DrawArrays(GL_LINE_LOOP,0,4));
#endif


}

/**
* Creates tcGeometry object for requested NTDS symbol
*/
boost::shared_ptr<tcGeometry> tcTacticalMapView::DrawNTDSAirFW(tcAllianceInfo::Affiliation affil) 
{
//    float w = 8.0f;
	
	return CreateSymbolGeometry();

#if 0
	// set color
	osg::Vec4Array* colors = new osg::Vec4Array;
	colors->push_back(GetAffiliationColor(affil));
	symbol->setColorArray(colors);
	symbol->setColorBinding(tcGeometry::BIND_OVERALL);

	// create vertex array
	osg::Vec3Array* vertices = new osg::Vec3Array;
	symbol->setVertexArray(vertices);


	switch (affil) 
	{
	case FRIENDLY:
	case NEUTRAL:
		{
			AddArcPrimitive(symbol, vertices, 0, 0, 2*w, 2*w, -90, 90, 32);
			break;
		}
	case UNKNOWN:
		{
			vertices->push_back(osg::Vec3(w, 0, 0));
			vertices->push_back(osg::Vec3(w, w, 0));
			vertices->push_back(osg::Vec3(-w, w, 0));
			vertices->push_back(osg::Vec3(-w, 0, 0));

			symbol->addPrimitiveSet(new osg::DrawArrays(GL_LINE_STRIP,0,4));
			break;
		}
	case HOSTILE:
		{
			vertices->push_back(osg::Vec3(w, 0, 0));
			vertices->push_back(osg::Vec3(0, w, 0));
			vertices->push_back(osg::Vec3(-w, 0, 0));

			symbol->addPrimitiveSet(new osg::DrawArrays(GL_LINE_STRIP,0,3));
			break;
		}
	default:
		{
			fprintf(stderr, "Error - tcTacticalMapView::DrawNTDSAirFW\n");
		}
	}

#endif

}

/**
* Creates tcGeometry object for requested NTDS symbol
*/
boost::shared_ptr<tcGeometry> tcTacticalMapView::DrawNTDSAirRW(tcAllianceInfo::Affiliation affil) 
{
//    float w = 8.0f;
	
	return CreateSymbolGeometry();

#if 0
	// set color
	osg::Vec4Array* colors = new osg::Vec4Array;
	colors->push_back(GetAffiliationColor(affil));
	symbol->setColorArray(colors);
	symbol->setColorBinding(tcGeometry::BIND_OVERALL);

	// create vertex array
	osg::Vec3Array* vertices = new osg::Vec3Array;
	symbol->setVertexArray(vertices);


	switch (affil) 
	{
	case FRIENDLY:
	case NEUTRAL:
		{
			AddArcPrimitive(symbol, vertices, 0, 0, 2*w, 2*w, -90, 90, 32);
			break;
		}
	case UNKNOWN:
		{
			float wu = 0.9f * w;
			vertices->push_back(osg::Vec3(wu, 0, 0));
			vertices->push_back(osg::Vec3(wu, wu, 0));
			vertices->push_back(osg::Vec3(-wu, wu, 0));
			vertices->push_back(osg::Vec3(-wu, 0, 0));
			symbol->addPrimitiveSet(new osg::DrawArrays(GL_LINE_STRIP,0,4));
			break;
		}
	case HOSTILE:
		{
			vertices->push_back(osg::Vec3(w, 0, 0));
			vertices->push_back(osg::Vec3(0, w, 0));
			vertices->push_back(osg::Vec3(-w, 0, 0));
			symbol->addPrimitiveSet(new osg::DrawArrays(GL_LINE_STRIP,0,3));
			break;
		}
	default:
		{
			fprintf(stderr, "Error - tcTacticalMapView::DrawNTDSAirRW\n");
		}
	}

	size_t v_idx = vertices->size();
	vertices->push_back(osg::Vec3(w, w, 0));
	vertices->push_back(osg::Vec3(-w, w, 0));
	symbol->addPrimitiveSet(new osg::DrawArrays(GL_LINES, v_idx, 2));
#endif

}

/**
* Creates tcGeometry object for requested NTDS symbol
*/
boost::shared_ptr<tcGeometry> tcTacticalMapView::DrawNTDSMissile(tcAllianceInfo::Affiliation affil) 
{
//	float w = 8.0f;

	return CreateSymbolGeometry();

#if 0
	// set color
	osg::Vec4Array* colors = new osg::Vec4Array;
	colors->push_back(GetAffiliationColor(affil));
	symbol->setColorArray(colors);
	symbol->setColorBinding(tcGeometry::BIND_OVERALL);

	// create vertex array
	osg::Vec3Array* vertices = new osg::Vec3Array;
	symbol->setVertexArray(vertices);


	switch (affil) 
	{
	case FRIENDLY:
	case NEUTRAL:
		{
			AddArcPrimitive(symbol, vertices, 0, 0, 2*w, 2*w, -90, 90, 32);

			size_t v_idx = vertices->size();
			vertices->push_back(osg::Vec3(-2, 0, 0));
			vertices->push_back(osg::Vec3(-2, w-1, 0));
			vertices->push_back(osg::Vec3(2, 0, 0));
			vertices->push_back(osg::Vec3(2, w-1, 0));
			symbol->addPrimitiveSet(new osg::DrawArrays(GL_LINES, v_idx, 4));
			break;
		}
	case UNKNOWN:
		{
			vertices->push_back(osg::Vec3(w, 0, 0));
			vertices->push_back(osg::Vec3(w, w, 0));
			vertices->push_back(osg::Vec3(-w, w, 0));
			vertices->push_back(osg::Vec3(-w, 0, 0));
			symbol->addPrimitiveSet(new osg::DrawArrays(GL_LINE_STRIP, 0, 4));

			size_t v_idx = vertices->size();
			vertices->push_back(osg::Vec3(-2, 0, 0));
			vertices->push_back(osg::Vec3(-2, w, 0));
			vertices->push_back(osg::Vec3(2, 0, 0));
			vertices->push_back(osg::Vec3(2, w, 0));
			symbol->addPrimitiveSet(new osg::DrawArrays(GL_LINES, v_idx, 4));
			break;
		}
	case HOSTILE:
		{
			vertices->push_back(osg::Vec3(w, 0, 0));
			vertices->push_back(osg::Vec3(0, w, 0));
			vertices->push_back(osg::Vec3(-w, 0, 0));
			symbol->addPrimitiveSet(new osg::DrawArrays(GL_LINE_STRIP,0,3));

			size_t v_idx = vertices->size();
			vertices->push_back(osg::Vec3(-2, 0, 0));
			vertices->push_back(osg::Vec3(-2, w-1, 0));
			vertices->push_back(osg::Vec3(2, 0, 0));
			vertices->push_back(osg::Vec3(2, w-1, 0));
			symbol->addPrimitiveSet(new osg::DrawArrays(GL_LINES, v_idx, 4));
			break;
		}
	default:
		{
			fprintf(stderr, "Error - tcTacticalMapView::DrawNTDSMissile\n");
		}
	}

#endif

}


/**
* Creates tcGeometry object for requested NTDS symbol
*/
boost::shared_ptr<tcGeometry> tcTacticalMapView::DrawNTDSSubsurface(tcAllianceInfo::Affiliation affil) 
{
//    float w = 8.0f;
	
	return CreateSymbolGeometry();

#if 0
	// set color
	osg::Vec4Array* colors = new osg::Vec4Array;
	colors->push_back(GetAffiliationColor(affil));
	symbol->setColorArray(colors);
	symbol->setColorBinding(tcGeometry::BIND_OVERALL);

	// create vertex array
	osg::Vec3Array* vertices = new osg::Vec3Array;
	symbol->setVertexArray(vertices);


	switch (affil) 
	{
	case FRIENDLY:
	case NEUTRAL:
		{
			AddArcPrimitive(symbol, vertices, 0, 0, 2*w, -2*w, -90, 90, 32);
			break;
		}
	case UNKNOWN:
		{
			vertices->push_back(osg::Vec3(w, 0, 0));
			vertices->push_back(osg::Vec3(w, -w, 0));
			vertices->push_back(osg::Vec3(-w, -w, 0));
			vertices->push_back(osg::Vec3(-w, 0, 0));

			symbol->addPrimitiveSet(new osg::DrawArrays(GL_LINE_STRIP,0,4));
			break;
		}
	case HOSTILE:
		{
			vertices->push_back(osg::Vec3(w, 0, 0));
			vertices->push_back(osg::Vec3(0, -w, 0));
			vertices->push_back(osg::Vec3(-w, 0, 0));

			symbol->addPrimitiveSet(new osg::DrawArrays(GL_LINE_STRIP,0,3));
			break;
		}
	default:
		{
			fprintf(stderr, "Error - tcTacticalMapView::DrawNTDSSubsurface\n");
		}
	}
#endif

}

/**
* Creates tcGeometry object for requested NTDS symbol
*/
boost::shared_ptr<tcGeometry>tcTacticalMapView::DrawNTDSTorpedo(tcAllianceInfo::Affiliation affil) 
{
//    float w = 8.0f;
	
	return CreateSymbolGeometry();

#if 0
	// set color
	osg::Vec4Array* colors = new osg::Vec4Array;
	colors->push_back(GetAffiliationColor(affil));
	symbol->setColorArray(colors);
	symbol->setColorBinding(tcGeometry::BIND_OVERALL);

	// create vertex array
	osg::Vec3Array* vertices = new osg::Vec3Array;
	symbol->setVertexArray(vertices);


	switch (affil) 
	{
	case FRIENDLY:
	case NEUTRAL:
		{
			AddArcPrimitive(symbol, vertices, 0, 0, 2*w, -2*w, -90, 90, 32);
			break;
		}
	case UNKNOWN:
		{
			vertices->push_back(osg::Vec3(w, 0, 0));
			vertices->push_back(osg::Vec3(w, -w, 0));
			vertices->push_back(osg::Vec3(-w, -w, 0));
			vertices->push_back(osg::Vec3(-w, 0, 0));

			symbol->addPrimitiveSet(new osg::DrawArrays(GL_LINE_STRIP,0,4));
			break;
		}
	case HOSTILE:
		{
			vertices->push_back(osg::Vec3(w, 0, 0));
			vertices->push_back(osg::Vec3(0, -w, 0));
			vertices->push_back(osg::Vec3(-w, 0, 0));

			symbol->addPrimitiveSet(new osg::DrawArrays(GL_LINE_STRIP,0,3));
			break;
		}
	default:
		{
			fprintf(stderr, "Error - tcTacticalMapView::DrawNTDSSubsurface\n");
		}
	}

    // add "T"
    size_t v_idx = vertices->size();
    vertices->push_back(osg::Vec3(-0.65*w, -0.2*w, 0));
    vertices->push_back(osg::Vec3(0.65*w, -0.2*w, 0));
    vertices->push_back(osg::Vec3(0, -0.2*w, 0));
    vertices->push_back(osg::Vec3(0, -1.1*w, 0));

    symbol->addPrimitiveSet(new osg::DrawArrays(GL_LINES, v_idx, 4));

#endif

}


/**
* Creates tcGeometry objects for NTDS symbol set
*/
void tcTacticalMapView::BuildNTDS() 
{
    return; // obsolete?
#if 0
	boost::shared_ptr<tcGeometry> pSymbol;

	for (int nAffiliation=0; nAffiliation<4; nAffiliation++) 
	{
		// surface symbol
		boost::shared_ptr<tcGeometry> pSurface = DrawNTDSSurface((tcAllianceInfo::Affiliation)nAffiliation);

		// carrier symbol
		boost::shared_ptr<tcGeometry> pCarrier = DrawNTDSCarrier((tcAllianceInfo::Affiliation)nAffiliation);


		// fixed ground symbol
		boost::shared_ptr<tcGeometry> pGround = DrawNTDSGround((tcAllianceInfo::Affiliation)nAffiliation);

		// missile
		boost::shared_ptr<tcGeometry> pMissile = DrawNTDSMissile((tcAllianceInfo::Affiliation)nAffiliation);

		// fixed wing
		boost::shared_ptr<tcGeometry> pAirFW = DrawNTDSAirFW((tcAllianceInfo::Affiliation)nAffiliation);

		// rotary wing
		boost::shared_ptr<tcGeometry> pAirRW = DrawNTDSAirRW((tcAllianceInfo::Affiliation)nAffiliation);

		// sub
		boost::shared_ptr<tcGeometry> pSub = DrawNTDSSubsurface((tcAllianceInfo::Affiliation)nAffiliation);

		// torpedo
		boost::shared_ptr<tcGeometry> pTorpedo = DrawNTDSTorpedo((tcAllianceInfo::Affiliation)nAffiliation);

        // mark symbol
        boost::shared_ptr<tcGeometry> pMark = DrawDefaultMark((tcAllianceInfo::Affiliation)nAffiliation);

		// unknown (small square, not strictly NTDS
		boost::shared_ptr<tcGeometry> pUnknown = DrawNTDSUnknown((tcAllianceInfo::Affiliation)nAffiliation);

		for (int nSymbol=0; nSymbol<MAX_SYMBOL; nSymbol++) 
		{
			switch (nSymbol) 
			{
			case SYMBOL_UNKNOWN:
				pSymbol = pUnknown;
				break;
			case SYMBOL_SMALLSURFACE:
			case SYMBOL_LARGESURFACE:
			case SYMBOL_SURFACE:
				pSymbol = pSurface;
				break;
			case SYMBOL_CARRIER:
				pSymbol = pCarrier;
				break;
			case SYMBOL_MISSILE:
				pSymbol = pMissile;
				break;
			case SYMBOL_HELO:
				pSymbol = pAirRW;
				break;
			case SYMBOL_AIR:
			case SYMBOL_FIXEDWING:
				pSymbol = pAirFW;
				break;
			case SYMBOL_TORPEDO:
                pSymbol = pTorpedo;
                break;
			case SYMBOL_SUBSURFACE:
			case SYMBOL_SUBMARINE:
				pSymbol = pSub;
				break;
			case SYMBOL_FIXED:
			case SYMBOL_AIRFIELD:
				pSymbol = pGround;
				break;
            case SYMBOL_MARK:
                pSymbol = pMark;
                break;
			default:
				pSymbol = pUnknown;
				break;
			}
            maSymbolA[nAffiliation][nSymbol] = pSymbol;
		}

	}
#endif
}


void tcTacticalMapView::Build2525()
{
	BuildImageSymbology(0, "m2525"); 
}

void tcTacticalMapView::BuildNTDSImage()
{
	BuildImageSymbology(1, "ntds"); 
}


/**
* Creates textured tcGeometry objects for symbology described in image files
* @param subdirectory directory within images\symbology to read files from
*
*/
void tcTacticalMapView::BuildImageSymbology(int symbolArray, const std::string& subdirectory) 
{
	const size_t nBuff = 128;
	char zBuff[nBuff];


    boost::shared_ptr<tcGeometry> pSymbol;

	for (int nAffiliation=0; nAffiliation<4; nAffiliation++) 
	{
		char zAffil[32];
		switch(nAffiliation) 
		{
         case tcAllianceInfo::UNKNOWN:
			 strcpy(zAffil,"_unknown.png");
			 break;
		 case tcAllianceInfo::FRIENDLY:
			 strcpy(zAffil,"_friendly.png");
			 break;
		 case tcAllianceInfo::NEUTRAL:
			 strcpy(zAffil,"_neutral.png");
			 break;
		 case tcAllianceInfo::HOSTILE:
			 strcpy(zAffil,"_hostile.png");
			 break;

		}

		_snprintf(zBuff, nBuff, "%s\\seasurface%s", subdirectory.c_str(), zAffil);
		boost::shared_ptr<tcGeometry> pSurface = CreateTexturedSymbol(zBuff);

		_snprintf(zBuff, nBuff, "%s\\seasurfacegroup%s", subdirectory.c_str(), zAffil);
		boost::shared_ptr<tcGeometry> pSurfaceGroup = CreateTexturedSymbol(zBuff);

		_snprintf(zBuff, nBuff, "%s\\carrier%s", subdirectory.c_str(), zAffil);
		boost::shared_ptr<tcGeometry> pCarrier = CreateTexturedSymbol(zBuff);

		_snprintf(zBuff, nBuff, "%s\\carriergroup%s", subdirectory.c_str(), zAffil);
		boost::shared_ptr<tcGeometry> pCarrierGroup = CreateTexturedSymbol(zBuff);

		_snprintf(zBuff, nBuff, "%s\\air_fw%s", subdirectory.c_str(), zAffil);
		boost::shared_ptr<tcGeometry> pAir = CreateTexturedSymbol(zBuff);

		_snprintf(zBuff, nBuff, "%s\\air_rw%s", subdirectory.c_str(), zAffil);
		boost::shared_ptr<tcGeometry> pHelo = CreateTexturedSymbol(zBuff);

		_snprintf(zBuff, nBuff, "%s\\missile%s", subdirectory.c_str(), zAffil);
		boost::shared_ptr<tcGeometry> pMissile = CreateTexturedSymbol(zBuff);

        _snprintf(zBuff, nBuff, "%s\\fixed%s", subdirectory.c_str(), zAffil);
        boost::shared_ptr<tcGeometry> pFixed = CreateTexturedSymbol(zBuff);

        _snprintf(zBuff, nBuff, "%s\\airfield%s", subdirectory.c_str(), zAffil);
        boost::shared_ptr<tcGeometry> pAirfield = CreateTexturedSymbol(zBuff);

        _snprintf(zBuff, nBuff, "%s\\sub%s", subdirectory.c_str(), zAffil);
        boost::shared_ptr<tcGeometry> pSub = CreateTexturedSymbol(zBuff);

        _snprintf(zBuff, nBuff, "%s\\torp%s", subdirectory.c_str(), zAffil);
        boost::shared_ptr<tcGeometry> pTorpedo = CreateTexturedSymbol(zBuff);

        boost::shared_ptr<tcGeometry> pMark = DrawDefaultMark((tcAllianceInfo::Affiliation)nAffiliation);

		_snprintf(zBuff, nBuff,  "%s\\unknown.png", subdirectory.c_str());
		boost::shared_ptr<tcGeometry> pUnknown = CreateTexturedSymbol(zBuff);


		for (int nSymbol=0; nSymbol<MAX_SYMBOL; nSymbol++) 
		{
			switch (nSymbol) 
			{
			case SYMBOL_UNKNOWN:
				pSymbol = pUnknown;
				break;
			case SYMBOL_SMALLSURFACE:
			case SYMBOL_LARGESURFACE:
			case SYMBOL_SURFACE:
				pSymbol = pSurface;
				break;
			case SYMBOL_CARRIER:
				pSymbol = pCarrier;
				break;
            case SYMBOL_SURFACEGROUP:
                pSymbol = pSurfaceGroup;
                break;
            case SYMBOL_CARRIERGROUP:
                pSymbol = pCarrierGroup;
                break;
			case SYMBOL_MISSILE:
				pSymbol = pMissile;
				break;
			case SYMBOL_HELO:
                pSymbol = pHelo;
                break;
			case SYMBOL_AIR:
			case SYMBOL_FIXEDWING:
				pSymbol = pAir;
				break;
			case SYMBOL_TORPEDO:
                pSymbol = pTorpedo;
                break;
			case SYMBOL_SUBSURFACE:
			case SYMBOL_SUBMARINE:
				pSymbol = pSub;
				break;
            case SYMBOL_FIXED:
            case SYMBOL_GROUNDVEHICLE:
                pSymbol = pFixed;
                break;
            case SYMBOL_AIRFIELD:
                pSymbol = pAirfield;
                break;
            case SYMBOL_MARK:
                pSymbol = pMark;
                break;
			default:
				pSymbol = pUnknown;
				break;
			}
			if (symbolArray == 0) // m2525
			{
                maSymbolB[nAffiliation][nSymbol] = pSymbol;
			}
			else // ntds
			{
				maSymbolA[nAffiliation][nSymbol] = pSymbol;
			}
		}
	}


}

/**
* Creates faded copies of symbol tables.
* Call after tables are built.
*/
void tcTacticalMapView::CreateAlternateSymbols()
{
    for (int nAffiliation=0; nAffiliation<4; nAffiliation++) 
	{
		for (int nSymbol=0; nSymbol<MAX_SYMBOL; nSymbol++) 
		{
            {
				tcGeometry* fadeA = new tcGeometry(*maSymbolA[nAffiliation][nSymbol].get());
				fadeA->SetColor(Vec4(0.4f, 0.4f, 0.4f, 1.0f));

				maSymbolA_fade[nAffiliation][nSymbol] = boost::shared_ptr<tcGeometry>(fadeA);

				
            }

            {
				tcGeometry* fadeB = new tcGeometry(*maSymbolB[nAffiliation][nSymbol].get());
				fadeB->SetColor(Vec4(0.4f, 0.4f, 0.4f, 1.0f));

				maSymbolB_fade[nAffiliation][nSymbol] = boost::shared_ptr<tcGeometry>(fadeB);
            }

            {
                tcGeometry* altA = new tcGeometry(*maSymbolA[nAffiliation][nSymbol].get());
				altA->SetColor(Vec4(0.6f, 0.6f, 0.8f, 1.0f));

				maSymbolA_alt[nAffiliation][nSymbol] = boost::shared_ptr<tcGeometry>(altA);
            }

            {
                tcGeometry* altB = new tcGeometry(*maSymbolB[nAffiliation][nSymbol].get());
				altB->SetColor(Vec4(0.6f, 0.6f, 0.8f, 1.0f));

				maSymbolB_alt[nAffiliation][nSymbol] = boost::shared_ptr<tcGeometry>(altB);
            }

		}
	}
}


bool tcTacticalMapView::GetShowFrameCounter() const
{
	return showFrameCounter;
}

/**
* @returns symbol image pointer based on symbology mode
*/
tcGeometry* tcTacticalMapView::GetSymbol(tcAllianceInfo::Affiliation aeAffiliation, teSymbol aeSymbol) 
{
    int nAffilIdx = (int)aeAffiliation;
    int nSymbolIdx = (int)aeSymbol;

    if (meSymbology == NTDS) 
	{
        return maSymbolA[nAffilIdx][nSymbolIdx].get();
    }
    else // (meSymbology == M2525)
	{
        return maSymbolB[nAffilIdx][nSymbolIdx].get();
    }
}


/**
* Altered version of symbols for objects not controlled by player in multiplayer mode
* @returns symbol image pointer based on symbology mode
*/
tcGeometry* tcTacticalMapView::GetSymbolAltered(tcAllianceInfo::Affiliation aeAffiliation, teSymbol aeSymbol) 
{
    int nAffilIdx = (int)aeAffiliation;
    int nSymbolIdx = (int)aeSymbol;

    if (meSymbology == NTDS) 
	{
        return maSymbolA_alt[nAffilIdx][nSymbolIdx].get();
    }
    else // (meSymbology == M2525)
	{
        return maSymbolB_alt[nAffilIdx][nSymbolIdx].get();
    }
}


/**
* Faded version of symbols for stale tracks
* @returns symbol image pointer based on symbology mode
*/
tcGeometry* tcTacticalMapView::GetSymbolFaded(tcAllianceInfo::Affiliation aeAffiliation, teSymbol aeSymbol) 
{
    int nAffilIdx = (int)aeAffiliation;
    int nSymbolIdx = (int)aeSymbol;

    if (meSymbology == NTDS) 
	{
        return maSymbolA_fade[nAffilIdx][nSymbolIdx].get();
    }
    else // (meSymbology == M2525)
	{
        return maSymbolB_fade[nAffilIdx][nSymbolIdx].get();
    }
}



/**
* Version that uses pre-drawn images to draw symbols
* This is a mess, clean this up (draw out of symbol class perhaps)
*/
void tcTacticalMapView::DrawSymbol2(tcMapObj* pMO) 
{
    float symbsize = 15.0f;
    float vectsize = 18.0f; // heading vector length
    float p1x, p2x, p1y, p2y;
    float xv=0, yv=0; // heading vector
    tcPoint pscreen;
    tcRect rclipbounds;
    float x, y;
    float h;
    teSymbol type;
    const float passive_vect_size = 75.0f;
    
    h = pMO->mfHeading;
    int bHeadingValid = pMO->mnFlags & TRACK_HEADING_VALID;

    bool bBearingOnly = ((pMO->mnFlags & TRACK_BEARING_ONLY) != 0) &&
        (pMO->errorPoly.size() <= 2);

    type = pMO->meSymbol;


    pMO->mbFocus = (IsHooked(pMO->mnID));

	if (pMO->mbFocus && IsFirstHook(pMO->mnID))
    {
        mfHookLat = pMO->mfLat; // refactor
        mfHookLon = pMO->mfLon;
    }


    Vec4 penColor = GetAffiliationColor(pMO->meAffiliation);

    switch (type)
    {
    case SYMBOL_TARGET:
        symbsize = 30.0f;
        penColor = Vec4(1, 0, 0, 1);
        break;
    case SYMBOL_MARK:
        symbsize = 8.0f;
        vectsize = 10.0f;
        break;
    default:
        break;
    }


 //   if (type == SYMBOL_SENSOR) 
	//{
 //       symbsize = 8.0f;
 //       vectsize = 10.0f;
 //   }
 //   else if (type == SYMBOL_TARGET)
	//{
 //       symbsize = 30.0f;
 //   }
 //   else if (type == SYMBOL_MARK)
 //   {
 //       symbsize = 8.0f;
 //       vectsize = 10.0f;
 //   }
 //   if (type == SYMBOL_TARGET) 
	//{
 //       penColor = Vec4(1, 0, 0, 1); 
 //   }

    if (bBearingOnly) 
	{
        // use faded (half alpha) color for bearing line tracks
        // symbol is drawn ahead of time so its color remains the same
    //    mnPenColor = (mnPenColor & 0x00FFFFFF) + 0x80000000;
    }


    pscreen = GeoToScreen(pMO->mfLon, pMO->mfLat);
    x = pscreen.x;
    y = pscreen.y;


    // yet ANOTHER exception to the rule, this needs to be cleaned up!!
    float xv_passive=0, yv_passive=0;
    if (bBearingOnly) 
	{
        //h = atan2f(sinf(h),cosf(h)*cosf(pMO->mfLat)); // old projection
        float dx = passive_vect_size*sinf(h);
        float dy = (-passive_vect_size*cosf(h));
        // symbol placed in center of bearing line
        // bearing line from (xv,yv) to (xv_passive,yv_passive)
        xv = x;
        yv = y; 
        x += dx; 
        y += dy;
        xv_passive = x + dx;
        yv_passive = y + dy;
        tcPoint pnewcenter = ScreenToGeo(x, y);
        pMO->mfLon = pnewcenter.x;
        pMO->mfLat = pnewcenter.y;
    }


    // draw dots instead of symbols for zoomed out views
 //   if (mfLonWidth > C_PIOVER180*20.0f)
	//{   
 //       if (pMO->mbFocus)
	//	{
	//		penColor = Vec4(1, 1, 1, 1);
 //       }
 //       //RectF rect(x-2.0f,y-2.0f,4.0f,4.0f);
 //       //graphics->DrawPie(mpPen,rect,0,360);
	//	
	//	//DrawRectangleR(x-2.0f, y-2.0f, 4.0f, 4.0f, penColor, FILL_ON);
 //       return;
 //   }

    if ((type != SYMBOL_PIE) && (type != SYMBOL_LINE) &&(bHeadingValid)&&(!bBearingOnly))
	{
        //h = atan2f(sinf(h),cosf(h)*cosf(pMO->mfLat)); // old projection
        bool speedValid = (pMO->mnFlags & TRACK_SPEED_VALID) != 0;

        if (speedValid)
        {
            vectsize = GetLeaderLength(h, pMO->speed_kts, pMO->meSymbol);
        }
        else
        {
            pMO->speed_kts = 111;
        }
        
        xv = (vectsize*sinf(h)) + x;
        yv = ((-vectsize*cosf(h))) + y; 
    }

    p1x = x - 0.5f*symbsize;
    p2x = p1x + symbsize;
    p1y = y - 0.5f*symbsize;
    p2y = p1y + symbsize;

	Vec4 symbolColor;
	if (pMO->mnColor)
	{
		symbolColor = ConvertColor(pMO->mnColor); 
		symbolColor.w = 1.0f; // override alpha for now
	}
	else
	{
		symbolColor = GetAffiliationColor(pMO->meAffiliation);
	}

    if (type == SYMBOL_TARGET) 
	{

        DrawLineR(x, y-8, x, p1y, penColor);
        DrawLineR(x, y+8, x, p2y, penColor);
        DrawLineR(x-8, y, p1x, y, penColor);
        DrawLineR(x+8, y, p2x, y, penColor);
        h = HEADING_UNKNOWN;
    }
    else if (type == SYMBOL_PIE)
	{
		symbolColor.w = 0.35f;

        float width,height;
        width = GeoLonExtentToScreen(pMO->mfLonExtent);
        height = GeoLatExtentToScreen(pMO->mfLatExtent);

		int fillMode = (mpOptions->mbFillRangeCircles) ? FILL_ON : FILL_OFF;
		
		Vec4 pieColor = symbolColor;
		if (fillMode == FILL_ON)
		{
			pieColor.w *= 0.5f;
		}

        boost::shared_ptr<tcGeometry> rangeCircle;
		if ((pMO->mfArc_deg >= 360.0f) || (pMO->mfArc_deg <= 0))
		{
			rangeCircle = CreatePieGeometry(width, height, -180, 180, 
				symbolColor, fillMode);
		}
		else 
		{
			float halfArc = 0.5f*pMO->mfArc_deg;
			rangeCircle = CreatePieGeometry(width, height, h-halfArc, h+halfArc, 
				symbolColor, fillMode);
		}
		DrawGeometryR(rangeCircle.get(), pscreen.x, pscreen.y);

    }
    else if (type == SYMBOL_LINE)
    {
		symbolColor.w = 0.35f;

        tcPoint pscreen2 = GeoToScreen(pMO->mfLon2, pMO->mfLat2);
        
		DrawLineR(pscreen.x, pscreen.y, pscreen2.x, pscreen2.y, symbolColor);
    }
    else 
	{
        tcGeometry* pSymbol = 0;
		if ((!pMO->isStaleTrack) && (!pMO->useAltered))
        {
		    pSymbol = tcTacticalMapView::GetSymbol(pMO->meAffiliation, pMO->meSymbol);
        }
		else if (pMO->useAltered)
		{
            pSymbol = tcTacticalMapView::GetSymbolAltered(pMO->meAffiliation, pMO->meSymbol);           
			symbolColor.x *= 0.6f;
			symbolColor.y *= 0.6f;
			symbolColor.z *= 0.8f;
		}
		else
        {
            pSymbol = tcTacticalMapView::GetSymbolFaded(pMO->meAffiliation, pMO->meSymbol);           
            symbolColor = symbolColor * 0.5f;
        }

        DrawGeometryR(pSymbol, x, y);

        // draw 'X' if destroyed
        if (pMO->isDestroyed)
        {
            const Vec4 red(1.0, 0, 0, 1.0);
            const float halfWidth = 8.0f;
            DrawLineR(x-halfWidth, y-halfWidth, x+halfWidth, y+halfWidth, red);
            DrawLineR(x-halfWidth, y+halfWidth, x+halfWidth, y-halfWidth, red);
        }

        if (pMO->errorPoly.size() > 2)
        {
            
            tcPoint p1 = GeoToScreen(pMO->errorPoly[0].x, pMO->errorPoly[0].y);
            tcPoint p0 = p1;

            for (size_t k=1; k<pMO->errorPoly.size(); k++)
            {
                tcPoint p2 = GeoToScreen(pMO->errorPoly[k].x, pMO->errorPoly[k].y);
                DrawLineR(p1.x, p1.y, p2.x, p2.y, symbolColor);
                p1 = p2;
            }
            DrawLineR(p0.x, p0.y, p1.x, p1.y, symbolColor); // close the polygon
        }
    }


    // draw heading vector (unless == HEADING_UNKNOWN)
    if (bHeadingValid && (!bBearingOnly)) 
	{
        DrawLineR(x, y, xv, yv, symbolColor);
    }

    bool suppressTrackId = (pMO->mnID == NULL_INDEX) || (type == SYMBOL_UNKNOWN) ||
        (type == SYMBOL_MARK) || ((pMO->meAffiliation == tcAllianceInfo::FRIENDLY) && (type == SYMBOL_MISSILE));


    if ((trackInfoMode != 0) && !suppressTrackId) 
	{
		wxString s;

        if ((trackInfoMode == 1) || (pMO->speed_kts <= 0))
        {
            s = wxString::Format("%04d", pMO->mnID);
        }
        else
        { 
            s = wxString::Format("%04d\n %03.0f", pMO->mnID, units->UserSpeedUnits(pMO->speed_kts));
        }

		//DrawTextR(s.c_str(), x-9.0f, y+16.0f, defaultFont.get(), symbolColor, 11.0, LEFT_TOP);
        DrawTextR(s.c_str(), x+16.0f, y-8.0f, defaultFont.get(), symbolColor, 11.0, LEFT_TOP);
    }

    // draw focus box if applicable
    if ((pMO->mbFocus)&&(pMO->mnID!=NULL_INDEX)) 
	{
		Vec4 color(1, 1, 1, 1);
        const float fFocus = 6.5f;

        DrawLineR(p1x, p1y-fFocus, p1x-fFocus, p1y-fFocus, color);
        DrawLineR(p1x-fFocus, p1y-fFocus, p1x-fFocus, p1y, color);

        DrawLineR(p1x-fFocus, p2y, p1x-fFocus, p2y+fFocus, color);
        DrawLineR(p1x-fFocus, p2y+fFocus, p1x, p2y+fFocus, color);

        DrawLineR(p2x, p2y+fFocus, p2x+fFocus, p2y+fFocus, color);
        DrawLineR(p2x+fFocus, p2y+fFocus, p2x+fFocus, p2y, color);

        DrawLineR(p2x+fFocus, p1y, p2x+fFocus, p1y-fFocus, color);
        DrawLineR(p2x+fFocus, p1y-fFocus, p2x, p1y-fFocus, color);
    }

    // draw bearing line if applicable
    if (bBearingOnly) 
	{
		symbolColor.w = 0.5f;
        DrawLineR(xv, yv, xv_passive, yv_passive, symbolColor);
    }

}

void tcTacticalMapView::ClearHook()
{
	wxCommandEvent command(wxEVT_COMMAND_BUTTON_CLICKED, ID_NEWHOOK) ;    
	command.SetEventObject(this);
    command.SetExtraLong(-1); // 2.6.3 m_extraLong = -1;
	AddPendingEvent(command);

    hookedId.clear();
}

/**
* Single-unit hook.
* Hooks a single object closest to pscreen
* Modified so that hook is not cleared if no object is close to click point
* Use double click or escape key to clear hook
*/
long tcTacticalMapView::Hook(wxPoint pscreen)
{
    long currentHook;

    if (GetHookCount() == 1)
    {
        currentHook = GetHookID();
    }
    else
    {
        currentHook = -1;
    }

    long nMinID = GetClosest(pscreen); 

	if (nMinID == -1)
	{
		return -1;
	}

    if (nMinID != currentHook)
    {
        wxCommandEvent command(wxEVT_COMMAND_BUTTON_CLICKED, ID_NEWHOOK) ;    
        command.SetEventObject(this);
        command.SetExtraLong(nMinID); // 2.6.3 m_extraLong = nMinID;
        AddPendingEvent(command);
    }

    hookedId.clear();
    if (nMinID != -1)
    {
        hookedId.push_back(nMinID);
    }
    return nMinID;
}

/**
* Adds another unit to the hook group or deselects unit in hook group
* The deselect requires at least two members are in the group.
*/
void tcTacticalMapView::HookAnother(wxPoint pscreen)
{
	size_t hookCount = GetHookCount();

	if (hookCount == 0) return;

	// return if closest id is already hooked
    long closestId = GetClosest(pscreen); 
	bool unitWasRemoved = false;

	for (int n = int(hookCount)-1; (n >= 0)&&(!unitWasRemoved); n--)
	{
		if (hookedId[n] == closestId)
		{
			if (hookCount == 1) 
			{
				return;
			}
			else // remove unit from group
			{
				hookedId.erase(hookedId.begin() + n);
				unitWasRemoved = true;
			}
		}
	}

	if (unitWasRemoved)
	{
		hookCount--;
	}
	else // otherwise add to hook group
	{
		hookedId.push_back(closestId);
		hookCount++;
	}

	wxCommandEvent command(wxEVT_COMMAND_BUTTON_CLICKED, ID_GROUPHOOK);    
	command.SetEventObject(this);
    command.SetExtraLong(hookCount); // 2.6.3 m_extraLong = hookCount;
	long* groupList = new long[hookCount];
	for (size_t n = 0; n < hookCount; n++)
	{
		groupList[n] = hookedId[n];
	}
	command.SetClientData(groupList);

	AddPendingEvent(command);

}


/**
* Group hook.
* Selects multiple friendly units. 
* If no units are selected, this clears the hookedId vector.
*/
void tcTacticalMapView::HookGroup(const wxRect& region)
{
    tcMapObj *pMO;
    tcPoint northWest, southEast;

    northWest = ScreenToGeo(region.GetLeft(), region.GetBottom());
    southEast = ScreenToGeo(region.GetRight(), region.GetTop());
    tcGeoRect geoRegion;
    geoRegion.Set(northWest.x, southEast.x, northWest.y, southEast.y);


	std::vector<long> newHooks;

    // add all friendly units within region
    for(int i=0;i<MAXMAPOBJ;i++) 
    {
        pMO = &maMapObj[i];
        if ((pMO->mbExists)&&(pMO->mnID != -1) &&
            (geoRegion.ContainsPoint(pMO->mfLon, pMO->mfLat)) &&
            (pMO->meAffiliation == tcAllianceInfo::FRIENDLY)
            )
        {
            newHooks.push_back(pMO->mnID);
        }
    }

	if (newHooks.size() == 0) return;

	hookedId = newHooks;

    SendGroupHookMessage();
}

/**
*
*/
long tcTacticalMapView::HookSecondary(wxPoint pscreen)
{
    long nMinID;

    if (GetHookCount()==0) return -1;

    long currentHook = GetHookID();

    nMinID = GetClosest(pscreen); 

    if ((nMinID != currentHook) && (nMinID != -1))
    {
        wxCommandEvent command(wxEVT_COMMAND_BUTTON_CLICKED, ID_SECONDARYHOOK) ;    
        command.SetEventObject(this);
        command.SetExtraLong(nMinID); // 2.6.3 m_extraLong = nMinID;
        AddPendingEvent(command);
        return nMinID;
    }
    else
    {
        return -1;
    }
}

bool tcTacticalMapView::GetCenterViewOnHooked() const
{
    return centerViewOnHooked;
}

/**
*
*/
long tcTacticalMapView::GetClosest(const wxPoint& pscreen) const
{
    tcPoint geopoint = ScreenToGeo(pscreen);
	tcPoint geopointi;
    float fHookDistance,fMinDistance,fDistance;
    long nMinID;

    // search for hook
    fHookDistance = mfScaleX_radppel*24.0f; // 24 pixels
    fMinDistance = 1e15f;
    nMinID = NULL_INDEX;
    for(int i=0;i<MAXMAPOBJ;i++) 
    {
        const tcMapObj* pMO = &maMapObj[i];
		if ((pMO->mbExists) && (pMO->mnID != -1))
        {
            geopointi.x = pMO->mfLon;
            geopointi.y = pMO->mfLat;
            fDistance = geopoint.DistanceTo(geopointi);
            if (fDistance < fMinDistance) 
            {
                fMinDistance = fDistance;
                nMinID = pMO->mnID;
            }
        }
    }
    if (fMinDistance <= fHookDistance)
    {
        return nMinID;
    }
    else 
    {
        return NULL_INDEX;
    }
}

/**
*
*/
void tcTacticalMapView::ScrollMap(float afDirection_deg) 
{
    if (centerViewOnHooked) return;

    float dx,dy;
    float fDirection_rad = (float)C_PIOVER180*afDirection_deg;
    float dr = mfScaleX_radppel*16.0f; // 32 pixels

    dx = sinf(fDirection_rad)*dr;
    dy = cosf(fDirection_rad)*dr;

    tcPoint p;
    p.x = mrectCurrentView.XCenter() + dx;
    p.y = mrectCurrentView.YCenter() + dy;

    SetView(p, mrectCurrentView.Width());
}

void tcTacticalMapView::SendGroupHookMessage()
{
    long hookCount = GetHookCount();
	wxCommandEvent command(wxEVT_COMMAND_BUTTON_CLICKED, ID_GROUPHOOK);    
	command.SetEventObject(this);
    command.SetExtraLong(hookCount); // 2.6.3 m_extraLong = hookCount;
	long* groupList = new long[hookCount];
	for (int n=0; n<hookCount; n++)
	{
		groupList[n] = hookedId[n];
	}
	command.SetClientData(groupList);

	AddPendingEvent(command);
}

/**
*
*/
void tcTacticalMapView::ClearMapObjects() 
{
    for(int i=0; i<MAXMAPOBJ; i++) 
	{
        maMapObj[i].Clear();
    }
    mnObjCount = 0;
    ClearSpecialGraphics();
}

/**
*
*/
void tcTacticalMapView::Init() 
{
    tcPoint p;

    ClearMapObjects();
    p.x = C_PIOVER180*3;
    p.y = C_PIOVER180*43;

    mpMapData->GetTheaterArea(mrectViewBounds); // restrict view to theater area
    SetView(p, C_PIOVER180*32.0f);

    // Build symbologies
    //BuildNTDS();
    Build2525();
	BuildNTDSImage();
    CreateAlternateSymbols();

	UpdateMapObjectColors();

    navPointEditLock = false; // not sure if needed here
}

void tcTacticalMapView::InitializeButtons()
{
    int buttonWidth = 32;
	show3DButton = new tcButton(this, wxPoint(mnWidth-buttonWidth-5, 4),
		wxSize(buttonWidth, buttonWidth), "MinimizeButton");
	show3DButton->SetCaption("");
	show3DButton->LoadImages("button3d.jpg", "button3d.jpg", "button3d_over.jpg", 
		"button3d_over.jpg");
	show3DButton->SetCommand(265);
	show3DButton->Raise();

	int xbutton = int(leftMargin) + 470;
	int ybutton = 12;
	buttonWidth = 24;

	decelerateTimeButton = new tcButton(this, wxPoint(xbutton, ybutton),
		wxSize(buttonWidth, buttonWidth), "DecelerateButton");
	decelerateTimeButton->SetCaption("");
	decelerateTimeButton->LoadImages("decel_time.jpg", "decel_time.jpg", "decel_time_over.jpg", 
		"decel_time_over.jpg");
	decelerateTimeButton->SetCommand(99);
	decelerateTimeButton->Raise();

	xbutton += buttonWidth + 3;

	togglePauseButton = new tcButton(this, wxPoint(xbutton, ybutton),
		wxSize(buttonWidth, buttonWidth), "PauseButton");
	togglePauseButton->SetCaption("");
	togglePauseButton->LoadImages("pause_time.jpg", "pause_time.jpg", "pause_time_over.jpg", 
		"pause_time_over.jpg");
	togglePauseButton->SetCommand(100);
	togglePauseButton->Raise();

	xbutton += buttonWidth + 3;

	accelerateTimeButton = new tcButton(this, wxPoint(xbutton, ybutton),
		wxSize(buttonWidth, buttonWidth), "AccelerateButton");
	accelerateTimeButton->SetCaption("");
	accelerateTimeButton->LoadImages("accel_time.jpg", "accel_time.jpg", "accel_time_over.jpg", 
		"accel_time_over.jpg");
	accelerateTimeButton->SetCommand(101);
	accelerateTimeButton->Raise();

    xbutton += buttonWidth + 30;

	followHookedButton = new tcButton(this, wxPoint(xbutton, ybutton),
		wxSize(buttonWidth, buttonWidth), "FollowButton");
	followHookedButton->SetCaption("");
	followHookedButton->LoadImages("hook_view_off.jpg", "hook_view_on.jpg", "hook_view_off_over.jpg", 
		"hook_view_on_over.jpg");
	followHookedButton->SetCommand(222);
	followHookedButton->Raise();

	wxASSERT(airROE.size() == 0);

	std::vector<tcButton*> buttonList; // to set common parameters

	wxArrayString roeTypes;
	roeTypes.push_back("hold");
	roeTypes.push_back("tight");
	roeTypes.push_back("free");

	wxArrayString roeTypesCaps;
	roeTypesCaps.push_back("HOLD");
	roeTypesCaps.push_back("TIGHT");
	roeTypesCaps.push_back("FREE");

	xbutton += buttonWidth + 30;
	for (size_t n=0; n<roeTypes.size(); n++)
	{
		tcButton* airRoeButton = new tcButton(this, wxPoint(xbutton, ybutton),
									wxSize(buttonWidth, buttonWidth), "AirROEButton");
		airRoeButton->SetMouseOverCaption(wxString::Format("AAW WEAPONS %s", roeTypesCaps[n].ToAscii()).ToStdString());
		
		wxString imageName = wxString::Format("roe_air_%s.png", roeTypes[n].c_str());
		airRoeButton->LoadImages(imageName.ToStdString(), imageName.ToStdString(), 
							     imageName.ToStdString(), imageName.ToStdString());
		airRoeButton->SetCommand(AIR_ROE_COMMAND);
		airROE.push_back(airRoeButton);
		buttonList.push_back(airRoeButton);
	}

	xbutton += buttonWidth + 3;
	for (size_t n=0; n<roeTypes.size(); n++)
	{
		tcButton* surfRoeButton = new tcButton(this, wxPoint(xbutton, ybutton),
									wxSize(buttonWidth, buttonWidth), "SurfROEButton");
		surfRoeButton->SetMouseOverCaption(wxString::Format("ASuW WEAPONS %s", roeTypesCaps[n].ToAscii()).ToStdString());

		wxString imageName = wxString::Format("roe_surf_%s.png", roeTypes[n].ToAscii());
		surfRoeButton->LoadImages(imageName.ToStdString(), imageName.ToStdString(), 
							     imageName.ToStdString(), imageName.ToStdString());
		surfRoeButton->SetCommand(SURF_ROE_COMMAND);
		surfROE.push_back(surfRoeButton);
		buttonList.push_back(surfRoeButton);
	}

	xbutton += buttonWidth + 3;
	for (size_t n=0; n<roeTypes.size(); n++)
	{
		tcButton* subRoeButton = new tcButton(this, wxPoint(xbutton, ybutton),
									wxSize(buttonWidth, buttonWidth), "SubROEButton");
		subRoeButton->SetMouseOverCaption(wxString::Format("ASW WEAPONS %s", roeTypesCaps[n].ToAscii()).ToStdString());
		
		wxString imageName = wxString::Format("roe_sub_%s.png", roeTypes[n].ToAscii());
		subRoeButton->LoadImages(imageName.ToStdString(), imageName.ToStdString(), 
							     imageName.ToStdString(), imageName.ToStdString());
		subRoeButton->SetCommand(SUB_ROE_COMMAND);
		subROE.push_back(subRoeButton);
		buttonList.push_back(subRoeButton);
	}

	xbutton += buttonWidth + 3;
	for (size_t n=0; n<roeTypes.size(); n++)
	{
		tcButton* landRoeButton = new tcButton(this, wxPoint(xbutton, ybutton),
									wxSize(buttonWidth, buttonWidth), "LandROEButton");
		landRoeButton->SetMouseOverCaption(wxString::Format("GROUND WEAPONS %s", roeTypesCaps[n].ToAscii()).ToStdString());
		
		wxString imageName = wxString::Format("roe_land_%s.png", roeTypes[n].c_str());
		landRoeButton->LoadImages(imageName.ToStdString(), imageName.ToStdString(), 
							     imageName.ToStdString(), imageName.ToStdString());
		landRoeButton->SetCommand(LAND_ROE_COMMAND);
		landROE.push_back(landRoeButton);
		buttonList.push_back(landRoeButton);
	}

	for (size_t n=0; n<buttonList.size(); n++)
	{
		buttonList[n]->SetCaption("");
		buttonList[n]->SetMouseOverCaptionAlignment(LEFT_TOP);
		buttonList[n]->SetMouseOverCaptionPosition(wxPoint(0, -2));
		buttonList[n]->SetMouseOverCaptionColor(Vec4(1, 1, 1, 1.0f));
		buttonList[n]->SetMouseOverCaptionFontSize(11.0f);
		buttonList[n]->SetMouseOverCaptionFont(boldFont.get());
		buttonList[n]->Raise();
	}

	UpdateROEButtons();

	xbutton += 2*buttonWidth + 3;

	saveButton = new tcButton(this, wxPoint(xbutton, ybutton),
		wxSize(buttonWidth, buttonWidth), "SaveButton");
	saveButton->SetCaption("Save");
	saveButton->SetMouseOverCaption("Save Game");
	saveButton->SetMouseOverCaptionAlignment(LEFT_TOP);
	saveButton->SetMouseOverCaptionPosition(wxPoint(0, -2));
	saveButton->SetMouseOverCaptionColor(Vec4(1, 1, 1, 1.0f));
	saveButton->SetMouseOverCaptionFontSize(11.0f);
	saveButton->SetMouseOverCaptionFont(boldFont.get());
	saveButton->LoadImages("savebutton.jpg", "savebutton.jpg", "savebutton_over.jpg", 
		"savebutton_over.jpg");
	saveButton->SetCommand(SAVE_GAME);
	saveButton->Raise();


	xbutton += buttonWidth + 3;

    revertToSaved = new tcButton(this, wxPoint(xbutton, ybutton),
		wxSize(buttonWidth, buttonWidth), "RevertButton");
	revertToSaved->SetCaption("Revert to saved");
	revertToSaved->SetMouseOverCaption("Revert to Last Save");
	revertToSaved->SetMouseOverCaptionAlignment(LEFT_TOP);
	revertToSaved->SetMouseOverCaptionPosition(wxPoint(0, -2));
	revertToSaved->SetMouseOverCaptionColor(Vec4(1, 1, 1, 1.0f));
	revertToSaved->SetMouseOverCaptionFontSize(11.0f);
	revertToSaved->SetMouseOverCaptionFont(boldFont.get());
	revertToSaved->LoadImages("revertbutton.jpg", "revertbutton.jpg", "revertbutton_over.jpg", 
		"revertbutton_over.jpg");
	revertToSaved->SetCommand(REVERT);
	revertToSaved->Raise();

    xbutton += 2*buttonWidth + 3;


    changeSidesButton = new tcButton(this, wxPoint(xbutton, ybutton),
		wxSize(buttonWidth, buttonWidth), "ChangeSidesButton");
	changeSidesButton->SetCaption("Change Sides");
    changeSidesButton->SetMouseOverCaption("Change Sides");
	changeSidesButton->SetMouseOverCaptionAlignment(LEFT_TOP);
	changeSidesButton->SetMouseOverCaptionPosition(wxPoint(0, -2));
	changeSidesButton->SetMouseOverCaptionColor(Vec4(1, 1, 1, 1.0f));
	changeSidesButton->SetMouseOverCaptionFontSize(11.0f);
	changeSidesButton->SetMouseOverCaptionFont(boldFont.get());
	changeSidesButton->LoadImages("changesides.jpg", "changesides.jpg", "changesides_over.jpg", 
		"changesides_over.jpg");
	changeSidesButton->SetCommand(CHANGE_SIDES);
	changeSidesButton->Raise();



}

/**
* Updates view bounds, sets current view to center, and refreshes (reloads)
* terrain view.
* This should be called after the map data theater area is changed.
*/
void tcTacticalMapView::Refresh()
{
	wxASSERT(mpMapData);

	mpMapData->GetTheaterArea(mrectViewBounds); // restrict view to theater area

    // if new view bounds do not include or clip current view, then update current view
    tcGeoRect previousView = mrectCurrentView;
    mrectViewBounds.ApplyBounds(mrectCurrentView);
    if (mrectCurrentView != previousView)
    {
	    tcPoint center(mrectCurrentView.XCenter(), mrectCurrentView.YCenter());
        tcMapView::SetView(center, C_PIOVER180*10.0f);
    }
    else
    {
        wxASSERT(mfLonWidth == mrectCurrentView.Width());

        tcPoint center(mrectCurrentView.XCenter(), mrectCurrentView.YCenter());
        tcMapView::SetView(center, mfLonWidth);
    }

    overlay->Redraw();

	RefreshTerrainView();
    terrainView->SetView(mrectCurrentView); 

	UpdateMapObjectColors();

    if (worldMap != 0)
    {
        worldMap->SetTheater(mrectViewBounds);
    }
}

/**
* Update color of map objects based on map color mode.
*/
void tcTacticalMapView::UpdateMapObjectColors()
{
	Vec4 color;
	switch (tcOptions::Get()->mnMapMode)
	{
	case 0 : 
		color = Vec4(0, 0, 0, 1); 
		tcMapObject::LoadMarker("black_marker.png");
		break;
	case 1 : 
		color = Vec4(0, 0, 0, 1);
		tcMapObject::LoadMarker("black_marker.png");
		break;
	case 2 : 
		color = Vec4(1, 1, 1, 1);
		tcMapObject::LoadMarker("white_marker.png");
		break;
	default: 
		wxASSERT(false); 
		color = Vec4(1, 0, 0, 1);
		break;
	}

	int nObjects = (int)specialGraphics.size();
	for(int n=0; n<nObjects; n++)
	{
		tcMapObject* obj = specialGraphics[n];
        if (obj->GetAttributes() & (tcMapObject::AUTO_COLOR != 0))
        {
		    obj->SetColor(color);
        }
	}

	if (overlay != 0) overlay->SetColor(color);

}

/**
* Used to block editing of nav waypoints
*/
void tcTacticalMapView::SetNavPointEditLock(bool state)
{
    navPointEditLock = state;
}

/**
* Set the display state of ROE select buttons based on tcGoalTracker info
*/
void tcTacticalMapView::UpdateROEButtons()
{
	unsigned char userAlliance = tcUserInfo::Get()->GetOwnAlliance();

	tcGoalTracker::ROEStatus roeStatus = tcGoalTracker::Get()->GetAllianceROE(int(userAlliance));

	wxASSERT(tcGoalTracker::WEAPONS_HOLD == 0);
    wxASSERT(tcGoalTracker::WEAPONS_TIGHT == 1);
	wxASSERT(tcGoalTracker::WEAPONS_FREE == 2);

	wxASSERT(tcGoalTracker::WEAPONS_HOLD == tcTacticalMapView::WEAPONS_HOLD);
    wxASSERT(tcGoalTracker::WEAPONS_TIGHT == tcTacticalMapView::WEAPONS_TIGHT);
	wxASSERT(tcGoalTracker::WEAPONS_FREE == tcTacticalMapView::WEAPONS_FREE);

	for (size_t n=0; n<airROE.size(); n++)
	{
		airROE[n]->SetActive(false);
		surfROE[n]->SetActive(false);
		subROE[n]->SetActive(false);
		landROE[n]->SetActive(false);
	}

	if ((roeStatus.airMode >= 0) && (roeStatus.airMode <= 2))
	{
		airROE[roeStatus.airMode]->SetActive(true);
		airROE[roeStatus.airMode]->Raise();
	}
	if ((roeStatus.surfMode >= 0) && (roeStatus.surfMode <= 2))
	{
		surfROE[roeStatus.surfMode]->SetActive(true);
		surfROE[roeStatus.surfMode]->Raise();
	}
	if ((roeStatus.subMode >= 0) && (roeStatus.subMode <= 2))
	{
		subROE[roeStatus.subMode]->SetActive(true);
		subROE[roeStatus.subMode]->Raise();
	}
	if ((roeStatus.landMode >= 0) && (roeStatus.landMode <= 2))
	{
		landROE[roeStatus.landMode]->SetActive(true);
		landROE[roeStatus.landMode]->Raise();
	}

}


void tcTacticalMapView::SetShowFrameCounter(bool state)
{
	showFrameCounter = state;
}

/**
*
*/
void tcTacticalMapView::SetTextLeftMargin(float x)
{
    leftMargin = x;
}

void tcTacticalMapView::SetView(tcPoint center, float afLonSpan)
{
    // initial section is duplicated in tcMapView 
    // (doing this to handle out of bounds, auto change theater feature)
    if (center.x < -C_PI) {center.x += C_TWOPI;}
    else if (center.x >= C_PI) {center.x -= C_TWOPI;}
    
	float fMaxLonSpan = 0.9999f * mrectViewBounds.Width(); /// hack to prevent rounding issue with +/- 0.5f* below
    float fMaxLatSpan = mrectViewBounds.Height();

    // automatic change of theater resolution
    int theaterDecimation = mpMapData->GetTheaterDecimation();
    if ((theaterDecimation == 1) && (afLonSpan > 0.75*fMaxLonSpan))
    {
        wxCommandEvent command(wxEVT_COMMAND_BUTTON_CLICKED, ID_MEDRESTHEATER);    
        command.SetEventObject(this);
        AddPendingEvent(command);
        if (tcOptions::Get()->autoScrollTheater == 1) return;
    }

    if (theaterDecimation == mpMapData->GetMedResDecimation())
    {
        if (afLonSpan < 0.15*fMaxLonSpan)
        {
            wxCommandEvent command(wxEVT_COMMAND_BUTTON_CLICKED, ID_HIGHRESTHEATER);    
            command.SetEventObject(this);
            AddPendingEvent(command);
            if (tcOptions::Get()->autoScrollTheater == 1) return;
        }
        else if (afLonSpan > 0.85*fMaxLonSpan)
        {
            wxCommandEvent command(wxEVT_COMMAND_BUTTON_CLICKED, ID_LOWRESTHEATER);    
            command.SetEventObject(this);
            AddPendingEvent(command);
            if (tcOptions::Get()->autoScrollTheater == 1) return;
        }

    }

    if ((theaterDecimation == mpMapData->GetLowResDecimation()) && (afLonSpan < 0.15*fMaxLonSpan))
    {
        wxCommandEvent command(wxEVT_COMMAND_BUTTON_CLICKED, ID_MEDRESTHEATER);    
        command.SetEventObject(this);
        AddPendingEvent(command);
        if (tcOptions::Get()->autoScrollTheater == 1) return;
    }



    if (afLonSpan > fMaxLonSpan) {afLonSpan = fMaxLonSpan;}
    float fLatSpan = afLonSpan*mnHeight/mnWidth;
    if (fLatSpan > fMaxLatSpan) 
    {
        fLatSpan = fMaxLatSpan;
        afLonSpan = fLatSpan*mnWidth/mnHeight;
    }

    float minLatSpan = 100.0f * C_MTORAD; // limit zoom to 100 m over height of view
    if (fLatSpan < minLatSpan)
    {
        fLatSpan = minLatSpan;
        afLonSpan = fLatSpan*mnWidth/mnHeight;
    }

    tcGeoRect newview;
    newview.Set(center.x - 0.5f*afLonSpan, center.x + 0.5f*afLonSpan, // potential rounding issue here
        center.y - 0.5f*fLatSpan,  center.y + 0.5f*fLatSpan);
    // end duplicated section

    if (mrectViewBounds.IsOutOfBounds(newview) && autoScrollTheater)
    {
        float lon_deg = C_180OVERPI * newview.XCenter();
        float lat_deg = C_180OVERPI * newview.YCenter();

        tcGeoRect theaterRect;
        mpMapData->GetTheaterArea(theaterRect);
        float currentLat_deg = C_180OVERPI * theaterRect.YCenter();
        float currentLon_deg = C_180OVERPI * theaterRect.XCenter();

        float dlat_deg = fabsf(lat_deg - currentLat_deg);
        float dlon_deg = fabsf(lon_deg - currentLon_deg);

        if (dlat_deg < 0.05f)
        {
        }
        else if (lat_deg > currentLat_deg)
        {
            lat_deg = std::max(lat_deg, currentLat_deg + 1.0f);
        }
        else if (lat_deg < currentLat_deg)
        {
            lat_deg = std::min(lat_deg, currentLat_deg - 1.0f);
        }


        if (dlon_deg < 0.05f)
        {
        }
        else if (lon_deg > currentLon_deg)
        {
            lon_deg = std::max(lon_deg, currentLon_deg + 1.0f);
        }
        else if (lon_deg < currentLon_deg)
        {
            lon_deg = std::min(lon_deg, currentLon_deg - 1.0f);
        }
        if (lon_deg >= 180.0f) lon_deg -= 360.0f;
        if (lon_deg < -180.0f) lon_deg += 360.0f;

	    //lon_deg -= 0.5f * mpMapData->GetTheaterWidthDeg(); 
	    //lat_deg += 0.5f * mpMapData->GetTheaterHeightDeg();
        //if (lon_deg < -180.0f) lon_deg += 360.0f;
        //if (lon_deg >= 180.0f) lon_deg -= 360.0f;

        if ((lon_deg >= -180.0f) && (lon_deg < 180.0f))
        {
            {
            wxCommandEvent command(wxEVT_COMMAND_BUTTON_CLICKED, ID_SETTHEATER);    
            command.SetEventObject(this);

            long lon = (lon_deg > 0) ? long(8.0f*lon_deg + 0.5f) : long(8.0f*lon_deg - 0.5f);
            long lat = (lat_deg > 0) ? long(8.0f*lat_deg + 0.5f) : long(8.0f*lat_deg - 0.5f);

            long coordField = (lat << 16) + (lon & 0xFFFF);
            command.SetExtraLong(coordField); // 2.6.3 m_extraLong = coordField;
            AddPendingEvent(command);
            }

            {
            // also add an event to reset the view after the theater is changed
            wxCommandEvent command(wxEVT_COMMAND_BUTTON_CLICKED, ID_SETTACTICALVIEW);
            command.SetEventObject(this);

            if (lon_deg > 180) lon_deg -= 360.0f; // map to -180 to 180

            long lon = (lon_deg > 0) ? long(100.0f*lon_deg + 0.5f) : long(100.0f*lon_deg - 0.5f);
            long lat = (lat_deg > 0) ? long(100.0f*lat_deg + 0.5f) : long(100.0f*lat_deg - 0.5f);

            long coordField = (lat << 16) + (lon & 0xFFFF);
            command.SetExtraLong(coordField);
            AddPendingEvent(command);
            }

            return;
        }
        else
        {
            wxASSERT(false);
        }
    }


    tcMapView::SetView(center, afLonSpan);

    if (worldMap != 0) worldMap->SetTacticalMapView(mrectCurrentView);

    overlay->Redraw();
}

void tcTacticalMapView::SetWorldMap(tcWorldMapView* map)
{
    worldMap = map;
}

void tcTacticalMapView::ToggleShowTrackTags() 
{
    trackInfoMode = (trackInfoMode + 1) % 3;
}

/**
* OnLeaveWindow event handler
*/
void tcTacticalMapView::OnLeaveWindow(wxMouseEvent& event)
{
    wxPoint point = event.GetPosition();

	UpdateEdgeScroll(point);

	wxSetCursor(wxNullCursor);

	if (HasCapture())
	{
		ReleaseMouse();
	}
}


void tcTacticalMapView::OnLButtonDownMapCmd(const wxPoint& point) 
{
    tcPoint p;
    long mnID;

    if (mpCommandInterface == 0) return;

    switch (meMapCmd) 
    {
    case MC_HEADING:
        p = ScreenToGeo(point);
		mfMapCmdHeading = atan2f(p.x-mfHookLon,p.y-mfHookLat);

		mpCommandInterface->AddPythonCallbackForID(mzMapCmdCallback, "Heading", 
			callbackPlatformID, callbackParam, callbackTextParam);

        DeactivateMapCommand();

        break;
    case MC_TARGET:
        mnID = GetClosest(mpointMouse);
        if (mnID != NULL_INDEX) 
        {
            DeactivateMapCommand();
            mnMapCmdTarget = mnID;

			mpCommandInterface->AddPythonCallbackForID(mzMapCmdCallback, "Target", 
				callbackPlatformID, callbackParam, callbackTextParam);
		}
        break;
    case MC_DATUM:
        mpointGeoDatum = ScreenToGeo(point);
        DeactivateMapCommand();

		mpCommandInterface->AddPythonCallbackForID(mzMapCmdCallback, "Datum",
			callbackPlatformID, callbackParam, callbackTextParam);
        break;
    case MC_BOX:
        mpointGeoDatum = ScreenToGeo(point);
        isLButtonDown = true;
        // wait for button up to add callback
        break;
    case MC_LINE:
        mpointGeoDatum = ScreenToGeo(point);
        isLButtonDown = true;
        // wait for button up to add callback
        break;
    default:
        DeactivateMapCommand();
        break;
    }
}


void tcTacticalMapView::OnLButtonUpMapCmd(const wxPoint& point) 
{
    tcPoint p;
    long mnID;

    if (mpCommandInterface == 0)
    {
        wxASSERT(false);
        return;
    }

    switch (meMapCmd) 
    {
    case MC_BOX:
        mpointGeoDatum2 = ScreenToGeo(point);
		mpCommandInterface->AddPythonCallbackForID(mzMapCmdCallback, "Box",
			callbackPlatformID, callbackParam, callbackTextParam);
        break;
    case MC_LINE:
        mpointGeoDatum2 = ScreenToGeo(point);
        mpCommandInterface->AddPythonCallbackForID(mzMapCmdCallback, "Line",
            callbackPlatformID, callbackParam, callbackTextParam);
        break;
    default:
        break;
    }
    
    DeactivateMapCommand();
}

void tcTacticalMapView::OnMButtonDown(wxMouseEvent& event)
{
	isMButtonDown = true;
	middleDownPoint = event.GetPosition();
	middleDownGeoPoint = ScreenToGeo(middleDownPoint);
	CaptureMouse();
    wxSetCursor(moveCursor);

}

void tcTacticalMapView::OnMButtonUp(wxMouseEvent& event)
{
	isMButtonDown = false;
	wxSetCursor(wxNullCursor);
	if (HasCapture())
	{
		ReleaseMouse();
	}
}

void tcTacticalMapView::OnDecelerateTimeCommand(wxCommandEvent& event)
{
	wxCommandEvent command(wxEVT_COMMAND_BUTTON_CLICKED, ID_SETTIMEACCEL);
	command.SetEventObject(this);
    command.SetExtraLong(99); // 2.6.3 m_extraLong = 99;
	AddPendingEvent(command);
}

void tcTacticalMapView::OnPauseTimeCommand(wxCommandEvent& event)
{
	wxCommandEvent command(wxEVT_COMMAND_BUTTON_CLICKED, ID_SETTIMEACCEL);
	command.SetEventObject(this);
	command.SetExtraLong(100);
	AddPendingEvent(command);
}

void tcTacticalMapView::OnAccelerateTimeCommand(wxCommandEvent& event)
{
	wxCommandEvent command(wxEVT_COMMAND_BUTTON_CLICKED, ID_SETTIMEACCEL);
	command.SetEventObject(this);
	command.SetExtraLong(101);
	AddPendingEvent(command);
}

/**
* Toggle feature to "hook view" and have view follow hooked object
*/
void tcTacticalMapView::OnHookViewCommand(wxCommandEvent& event)
{
    bool newState = !GetCenterViewOnHooked();
    SetCenterViewOnHooked(newState);
}

void tcTacticalMapView::OnSaveGameCommand(wxCommandEvent& event)
{
	if (tcGameObject::IsEditMode())
	{
		tcOptions* options = tcOptions::Get();
		wxString lastSavePath = options->GetOptionString("ScenarioSavePath"); // full path and file name of scenario
		wxString lastSaveDir = lastSavePath.BeforeLast('/'); // directory to scenario file, with full path prefix
		wxString lastSaveFile = lastSavePath.AfterLast('/'); // just the file name
		if ((lastSaveDir.size() == 0) || (!wxDir::Exists(lastSaveDir)))
		{
			lastSaveDir = "scenarios/EditorSaved";
			lastSaveFile = "";
		}
		wxFileDialog fileDialog(this, "Choose a file", lastSaveDir, lastSaveFile, "*.py", wxFD_SAVE);
		if (fileDialog.ShowModal() == wxID_OK)
		{
			wxString filePath(fileDialog.GetPath());
			for (size_t n=0; n<filePath.size(); n++)
			{
				wxChar cn = filePath[n];
				if (filePath[n] == wxChar('\\'))
				{
					filePath.SetChar(n, '/');
				}
			}

			//23JUN2013 added this to keep name with spaces out of options for re-load
			filePath.Replace(wxT(" "), wxT("_"));
			filePath.Replace(wxT(")"), wxT(""));
			filePath.Replace(wxT("("), wxT(""));

			std::string filePath2(filePath.c_str()); // full path and filename
			options->SetOptionString("ScenarioSavePath", filePath2.c_str());

			tcSimPythonInterface::Get()->GetScenarioInterface()->SaveGame(filePath2);
		}
	}
	else
	{ 
		// this code same as in tcGame, should merge or eliminate other path to get it in one place
		tcSimState* simState = tcSimState::Get();
		
		wxString scenarioName(simState->GetScenarioName());
		scenarioName.Replace(wxT(" "), wxT("_"));

		wxString saveName = wxString::Format("scenarios//Saved//%s.dat",
			scenarioName.ToAscii());
        saveName.Replace(",", "");
        saveName.Replace(":", "");

		tcGameSerializer gameSaver;
		gameSaver.SaveToBinary(saveName.ToAscii()); // will overwrite last save

		wxString msg = wxString::Format("Saved %s", saveName.ToAscii());
		tcMessageInterface::Get()->ConsoleMessage(msg.ToStdString());

		// also save backup
		wxDateTime now = wxDateTime::Now();
		wxString backupSaveName = wxString::Format("scenarios//Saved//backup//%s_%02d_%02d_%02d%02d%02d.dat",
			scenarioName.ToAscii(),
			now.GetMonth()+1, now.GetDay(), now.GetHour(), now.GetMinute(), now.GetSecond());
		::wxCopyFile(saveName.ToAscii(), backupSaveName.ToAscii(), false);
	}

}

void tcTacticalMapView::OnChangeSidesCommand(wxCommandEvent& event)
{
    if (tcGameObject::IsEditMode() || tcPlatformInterface::GetDeveloperMode())
    {
        tcScenarioInterface* scenarioInterface = tcPlatformInterface::GetScenarioInterfaceStatic();

        int userAlliance = scenarioInterface->GetUserAlliance();
        for (int n=userAlliance+1; n<16; n++)
        {
            if (scenarioInterface->AllianceExists(n))
            {
                scenarioInterface->SetUserAlliance(n);
              
                wxString changeSidesCaption = wxString::Format("Change Sides (currently %s)",
                    scenarioInterface->GetAllianceCountry(n).c_str());
                changeSidesButton->SetMouseOverCaption(changeSidesCaption.ToStdString());
                return;
            }
        }
        scenarioInterface->SetUserAlliance(1);
        wxString changeSidesCaption = wxString::Format("Change Sides (currently %s)",
                    scenarioInterface->GetAllianceCountry(1).c_str());
        changeSidesButton->SetMouseOverCaption(changeSidesCaption.ToStdString());
    }
}

void tcTacticalMapView::OnReloadGameCommand(wxCommandEvent& event)
{
	wxString revertFile = mpOptions->GetOptionString("ScenarioSavePath"); // full path and file name of last scenario

    // show dialog to confirm reload
    wxString s;
    s.Printf("Reload scenario (%s)?", revertFile.ToAscii());
    wxMessageDialog confirmQuit(overlay, s.c_str(), "Confirm", wxOK | wxCANCEL, wxDefaultPosition);
    if (confirmQuit.ShowModal() != wxID_OK)
    {
        return;
    }
    wxCommandEvent command(wxEVT_COMMAND_BUTTON_CLICKED, ID_RELOADGAME);    
    command.SetEventObject(this);
    AddPendingEvent(command);
}

void tcTacticalMapView::OnChar(wxKeyEvent& event)
{
	int nChar = event.GetKeyCode();
    bool controlDown = event.ControlDown();
	bool altDown = event.AltDown();
    bool shiftDown = event.ShiftDown();


    /* If control is down and character is a number, set user selected group
    ** If Alt is down, set group hook to user selected group (if group is empty
    ** clear the current hook)
    */
    if (altDown)
    {
        wxString s = wxString::Format("%c", nChar);
        int val = (int)strtol(s.c_str(), 0, 10);
        if ((val >= 1) && (val <= 9))
        {
            tcUserSelectedGroups* groupCtrl = tcUserSelectedGroups::Get();
            if (controlDown)
            {
                groupCtrl->SetGroup(val, hookedId);
            }
            else
            {
                std::vector<long> assignedGroup = groupCtrl->GetGroup(val);
	            hookedId = assignedGroup;
                SendGroupHookMessage();
            }
            return;
        }

        switch (nChar)
        {
        case 'f':
            SetShowFrameCounter(!GetShowFrameCounter());
            return;
            break;
        }

        event.ResumePropagation(2); // pass up to tcGame
        event.Skip();
        return;
    }


    // first check for control key or priority game command key
    switch(nChar)
    {
    case 'r':
        ActivateMapCommand(MC_RANGE);
        return;
    case 'K':
        ToggleShowTrackTags();
        return;
    case 'W': // toggle world map size
        if (worldMap)
        {
            worldMap->ToggleMapSize();
        }
        return;
    case WXK_F12: // toggle blending for tactical map
        SetBlend(!GetBlend());
        return;
    case WXK_LEFT:
        ScrollMap(270.0f);
        return;
    case WXK_RIGHT:
        ScrollMap(90.0f);
        return;
    case WXK_UP:
        ScrollMap(0.0f);
        return;
    case WXK_DOWN:
        ScrollMap(180.0f);
        return;
    case WXK_DELETE:
        if (editPointIdx != -1)
        {
            DeleteEditPoint();
            return;
        }
    case WXK_TAB:
        CycleHook(!shiftDown); // cycle east on tab, west on shift-tab
        return;
    }

	if (nChar == WXK_ESCAPE)
	{
        if (isLButtonDown)
        {
            isLButtonDown = false;
            tcDragStatus::Get()->StopDrag();
            return;
        }

        if (IsMapCmdActive())
        {
            DeactivateMapCommand();
            return;
        }

		if (GetHookCount() > 0)
		{
			ClearHook();
			return;
		}
	}

    event.ResumePropagation(2); // pass up to tcGame
	event.Skip();
}


/**
*
*/
void tcTacticalMapView::OnLButtonDown(wxMouseEvent& event)
{
    bool isShiftDown = event.ShiftDown();
    bool isControlDown = event.ControlDown();
    bool bFlagsSet = (isShiftDown || isControlDown);

    buttonDownPoint = event.GetPosition();

    if (scrollActive)
    {
        CancelScroll();
        return;
    }

    if ((mbMapCmdActive)&&(!bFlagsSet)) 
    {
        OnLButtonDownMapCmd(buttonDownPoint);
        return;
    }

    if (isControlDown) 
    {
        SetViewCenterZoom(buttonDownPoint, 1.5f);
        tcSound::Get()->PlayEffect("MutedBeep");
        return;
    }
    else if (isShiftDown) 
    {
        SetViewCenterZoom(buttonDownPoint, 1.0f);
        tcSound::Get()->PlayEffect("MutedBeep");
        return;
    }

	// check if button is down near a nav waypoint, if so start edit
	CheckForNavPointEdit(buttonDownPoint);

    if (editPointIdx == -1)
    {
        //bool nearLine = 
        IsPointNearNavLine(buttonDownPoint, insertPointEditIdx);
    }

    isLButtonDown = true;

    SkipMouseEvent(event);
    event.ResumePropagation(2); // pass to tcGame
}

/**
* Send double click hook event (for customized command) if dclick on hooked obj
* Otherwise clear the current hook
*/
void tcTacticalMapView::OnLButtonDClick(wxMouseEvent& event)
{
    //if (overlay->IsInteracting())
    //{
    //    overlay->ClearInteraction();
    //    return;
    //}

    if (hookedId.size() == 0)
    {
        event.Skip();
        event.ResumePropagation(2);
        return;
    }

	wxPoint pos = event.GetPosition();

    long closestId = GetClosest(pos); 

	if (closestId == hookedId[0])
	{
		long flags = 0;
		if (event.ShiftDown()) flags += 1;
		if (event.ControlDown()) flags += 2;
		if (event.AltDown()) flags += 4;

        wxCommandEvent command(wxEVT_COMMAND_BUTTON_CLICKED, ID_DCLICKHOOK) ;    
        command.SetEventObject(this);
        command.SetExtraLong(flags);
        AddPendingEvent(command);
        return;
	}
	else
	{
		ClearHook();
        return;
	}
}


void tcTacticalMapView::CancelScroll()
{
    scrollActive = false;
	scrollDirection = 0.0f;
    if (HasCapture() && !isMButtonDown)
    {
        ReleaseMouse();
    }
}

/**
* Check if button is down near a nav waypoint-- if so, start edit
*/
void tcTacticalMapView::CheckForNavPointEdit(const wxPoint& buttonDownPoint)
{
    insertPointEditIdx = -1;

    if (navPointEditLock)
    {
        editPointIdx = -1;
        return;
    }


    // check that a hookable platform isn't underneath, if so then skip navpoint edit
    long nMinID = GetClosest(buttonDownPoint); 
	if (nMinID != -1) return;


	tcPoint buttonDownPointFloat((float)buttonDownPoint.x, (float)buttonDownPoint.y);
	const float editDistance = 4.0f;
    float closestDistance = 9999.0f;

    for (size_t n=size_t(currentPointIdx+1); n<navPointsPrimary.size(); n++)
	{
        const tcPoint& p = navPointsPrimary[n].screen;

		float distance = p.DistanceTo(buttonDownPointFloat);
        closestDistance = std::min(closestDistance, distance);

		if (distance < editDistance)
		{
			editPointIdx = (int)n;
            if (editPointIdx != detailedEditPointIdx)
            {
                detailedEditPointIdx = -1;
            }
			return;
		}
    }

    // check for button down near nav leg

	editPointIdx = -1; // click was not near a waypoint
    detailedEditPointIdx = -1;
}


/**
* Used to check if mouse is near one of the nav waypoint lines
* @param idx point to insert new waypoint BEFORE in route
*/
bool tcTacticalMapView::IsPointNearNavLine(const wxPoint& pos, int& idx) const
{
    idx = -1;
    if ((navPointsPrimary.size() < 1) || (currentPointIdx >= (int(navPointsPrimary.size())-1) ) || (navPointEditLock))
    {
        return false;
    }

    // check that a hookable platform isn't underneath, if so then skip navpoint edit
    long nMinID = GetClosest(pos); 
	if (nMinID != -1) return false;


    const float distanceThreshold = 8.0f;
    
    float x = float(pos.x);
    float y = float(pos.y);

    // form vector of line segment and idx's to test, to take some of the confusion out
    // of the current waypoint cases
    std::vector<tcPoint> p1;
    std::vector<tcPoint> p2;
    std::vector<unsigned int> insertIdx;

    if (currentPointIdx > 0)
    {
        // add segments without currentPoint
        for (size_t n=1; n<(navPointsPrimary.size()-1); n++)
        {
            p1.push_back(navPointsPrimary[n].screen);
            p2.push_back(navPointsPrimary[n+1].screen);
            insertIdx.push_back(n); // insert idx for original waypoint vect (ignores current point)
        }

        // insert current point
        p2.insert(p2.begin()+currentPointIdx-1, navPointsPrimary[0].screen);
        p1.insert(p1.begin()+currentPointIdx, navPointsPrimary[0].screen);
        insertIdx.insert(insertIdx.begin()+currentPointIdx, currentPointIdx);
    }
    else
    {   // already in order so just add starting with current point
        for (size_t n=0; n<(navPointsPrimary.size()-1); n++)
        {
            p1.push_back(navPointsPrimary[n].screen);
            p2.push_back(navPointsPrimary[n+1].screen);
            insertIdx.push_back(n); // insert idx for original waypoint vect (ignores current point)
        }
    }

    size_t futureSegmentIdx = currentPointIdx; // first segment that represents future legs (current point to next waypoint)

    for (size_t n=futureSegmentIdx; n<p1.size(); n++)
    {
        idx = (int)insertIdx[n];

        float dx = p2[n].x - p1[n].x;
        float dy = p2[n].y - p1[n].y;

        if ((dx != 0) || (dy != 0))
        {
            if (fabsf(dx) > fabsf(dy))
            {
                float xmin = std::min(p1[n].x, p2[n].x);
                float xmax = std::max(p1[n].x, p2[n].x);
                float edgeThreshold = 0.25*(xmax-xmin); // allow hit only in center half of segment
                if ((x >= (xmin+edgeThreshold)) && (x <= (xmax-edgeThreshold)))
                {
                    float m = dy / dx;
                    float yline = m*(x-p1[n].x) + p1[n].y;
                    if (fabsf(yline - y) < distanceThreshold) return true;
                }
            }
            else
            {
                float ymin = std::min(p1[n].y, p2[n].y);
                float ymax = std::max(p1[n].y, p2[n].y);
                float edgeThreshold = 0.25*(ymax-ymin);
                if ((y >= (ymin+edgeThreshold)) && (y <= (ymax-edgeThreshold)))
                {
                    float m = dx / dy;
                    float xline = m*(y-p1[n].y) + p1[n].x;
                    if (fabsf(xline - x) < distanceThreshold) return true;
                }
            }
        }
        else
        {
            wxASSERT(false); // duplicate point
        }
    }

    idx = -1;
    return false;
}


/**
* Check if right click is near a nav waypoint-- if so, start "detailed" edit to 
* change waypoint altitude and speed
*/
void tcTacticalMapView::CheckForNavPointDetailedEdit(const wxPoint& buttonDownPoint)
{
	tcPoint buttonDownPointFloat((float)buttonDownPoint.x, (float)buttonDownPoint.y);
	const float editDistance = 5.0f;

    for (size_t n=1; n<navPointsPrimary.size(); n++)
	{
        const tcPoint& p = navPointsPrimary[n].screen;

		float distance = p.DistanceTo(buttonDownPointFloat);
		if (distance < editDistance)
		{
            editPointIdx = -1;
			detailedEditPointIdx = (int)n;
			return;
		}
    }

    detailedEditPointIdx = -1;
	editPointIdx = -1; // click was not near a waypoint
}


/**
* Left mouse button up event handler.
*/
void tcTacticalMapView::OnLButtonUp(wxMouseEvent& event)
{
	// a hack to stop incomplete drags when the user lets go of the mouse button
	tcDragStatus::Get()->StopDrag(); 

    //if (overlay->IsInteracting())
    //{
    //    overlay->OnLButtonUp(event);
    //    return;
    //}

	if (!isLButtonDown) return;


	wxPoint buttonUpPoint = event.GetPosition();

    if (IsMapCmdActive())
    {
        OnLButtonUpMapCmd(buttonUpPoint);
        isLButtonDown = false;
        return;
    }


	if (editPointIdx > 0)
	{
		tcPoint geoPoint = ScreenToGeo(buttonUpPoint);

        if (navPointsMissionId == -1)
        {
		    wxString argString = wxString::Format(",%d,%f,%f", editPointIdx-1, geoPoint.x, geoPoint.y);
		    mpCommandInterface->AddPythonCommandGeneral("EditWaypoint", argString.ToStdString(), hookedId);
        }
        else
        {
            wxString argString = wxString::Format(",%d,%d,%f,%f", navPointsMissionId, editPointIdx-1, geoPoint.x, geoPoint.y);
		    mpCommandInterface->AddPythonCommandGeneral("EditMissionWaypoint", argString.ToStdString(), hookedId);
        }

		editPointIdx = -1;
		isLButtonDown = false;
		return;
	}

	int absDistance = abs(buttonDownPoint.x - buttonUpPoint.x) +
		              abs(buttonDownPoint.y - buttonUpPoint.y);

	bool noDrag = absDistance <= 8;

    if (insertPointEditIdx != -1)
    {
        if (!noDrag)
        {
            tcPoint geoPoint = ScreenToGeo(buttonUpPoint);

            if (navPointsMissionId == -1)
            {
                wxString argString = wxString::Format(",%d,%f,%f", insertPointEditIdx, geoPoint.x, geoPoint.y);
                mpCommandInterface->AddPythonCommandGeneral("InsertWaypoint", argString.ToStdString(), hookedId);
            }
            else
            {
                wxString argString = wxString::Format(",%d,%d,%f,%f", navPointsMissionId, insertPointEditIdx, geoPoint.x, geoPoint.y);
                mpCommandInterface->AddPythonCommandGeneral("InsertMissionWaypoint", argString.ToStdString(), hookedId);
            }
        }
        insertPointEditIdx = -1;
        isLButtonDown = false;
		return;
    }


	bool isAltDown = event.AltDown();


	if (noDrag)
	{
		if (isAltDown)
		{
			HookAnother(buttonUpPoint);
		}
		else
		{
			Hook(buttonUpPoint);
		}
	}
	else
	{
		int xLeft = min(buttonDownPoint.x, buttonUpPoint.x);
		int yTop = min(buttonDownPoint.y, buttonUpPoint.y);
		int width = abs(buttonUpPoint.x - buttonDownPoint.x);
		int height = abs(buttonUpPoint.y - buttonDownPoint.y);
		HookGroup(wxRect(xLeft, yTop, width, height));
	}

	isLButtonDown = false;

}

void tcTacticalMapView::OpenWaypointEditor(const wxPoint& pos)
{
    bool exists = (waypointEditorKey != -1) && (waypointEditor != 0) && (tcRegistered::WindowExists(waypointEditorKey));

    if (exists)
    {
        tcRegistered::ForceClose(waypointEditorKey);
        waypointEditor = 0;
        waypointEditorKey = -1;
    }

    waypointEditor = 
        new tcWaypointPopup(navPointsPlatformId, navPointsMissionId, detailedEditPointIdx-1, pos);
    waypointEditorKey = waypointEditor->GetKey();
}

/**
* Check if waypoint editor is still open, if not clean up references and stop detailed edit
*/
void tcTacticalMapView::UpdateWaypointEditor()
{
    if (waypointEditorKey != -1)
    {    
        if (detailedEditPointIdx == -1)
        {
            tcRegistered::ForceClose(waypointEditorKey);
            waypointEditor = 0;
            waypointEditorKey = -1;
            return;
        }
        else
        {
            if (!tcRegistered::WindowExists(waypointEditorKey))
            { // window was closed, stop detailed edit
                waypointEditor = 0;
                waypointEditorKey = -1;
                detailedEditPointIdx = -1;
            }
        }
    }
    else
    {
        wxASSERT(detailedEditPointIdx == -1);
    }

}


/**
*
*/
void tcTacticalMapView::OnRButtonDown(wxMouseEvent& event) 
{
    wxPoint point = event.GetPosition();
    bool isControlDown = event.ControlDown();
    bool isShiftDown = event.ShiftDown();
    bool bFlagsSet = (isControlDown || isShiftDown);

    if (scrollActive)
    {
        CancelScroll();
        return;
    }

    if ((meMapCmd != MC_NONE)&&(!bFlagsSet)) 
    { 
        DeactivateMapCommand();
        return;
    }
    if (isControlDown) 
    {
        SetViewCenterZoom(point,0.7f);
        tcSound::Get()->PlayEffect("MutedBeep");
        return;
    }

    if ((mpOptions->quickTarget == 1) && isShiftDown)
    {
        HookSecondary(point);
        return;
    }
    else if (HookSecondary(point) != -1)
    {
        return;
    }
    

    if (GetHookCount() == 0)
    {
        SkipMouseEvent(event);
    }
    else
    {
        CheckForNavPointDetailedEdit(point);
        if (detailedEditPointIdx != -1)
        {
            wxPoint p(point);
            p.y += 20;
            OpenWaypointEditor(p);
            return;
        }
        SkipMouseEvent(event);
    }


    event.ResumePropagation(2); // pass to tcGame
}

void tcTacticalMapView::OnShow3DCommand(wxCommandEvent& event)
{
    if (tcOptions::Get()->minimal3D == 0)
    {
        wxCommandEvent command(wxEVT_COMMAND_BUTTON_CLICKED, ID_SET3D);
        command.SetEventObject(this);
        command.SetExtraLong(1);
		AddPendingEvent(command);
	}
}

void tcTacticalMapView::OnAirROE(wxCommandEvent& event)
{
	int userAlliance = int(tcUserInfo::Get()->GetOwnAlliance());

	tcGoalTracker::ROEStatus roeStatus = tcGoalTracker::Get()->GetAllianceROE(userAlliance);

	roeStatus.airMode = tcGoalTracker::ROEMode(((int)roeStatus.airMode + 1) % 3);
	tcGoalTracker::Get()->SetAllianceROE(userAlliance, roeStatus);

	UpdateROEButtons();
}

void tcTacticalMapView::OnSurfROE(wxCommandEvent& event)
{
	int userAlliance = int(tcUserInfo::Get()->GetOwnAlliance());

	tcGoalTracker::ROEStatus roeStatus = tcGoalTracker::Get()->GetAllianceROE(userAlliance);

	roeStatus.surfMode = tcGoalTracker::ROEMode(((int)roeStatus.surfMode + 1) % 3);
	tcGoalTracker::Get()->SetAllianceROE(userAlliance, roeStatus);

	UpdateROEButtons();
}

void tcTacticalMapView::OnSubROE(wxCommandEvent& event)		
{
	int userAlliance = int(tcUserInfo::Get()->GetOwnAlliance());

	tcGoalTracker::ROEStatus roeStatus = tcGoalTracker::Get()->GetAllianceROE(userAlliance);

	roeStatus.subMode = tcGoalTracker::ROEMode(((int)roeStatus.subMode + 1) % 3);
	tcGoalTracker::Get()->SetAllianceROE(userAlliance, roeStatus);

	UpdateROEButtons();
}

void tcTacticalMapView::OnLandROE(wxCommandEvent& event)
{
	int userAlliance = int(tcUserInfo::Get()->GetOwnAlliance());

	tcGoalTracker::ROEStatus roeStatus = tcGoalTracker::Get()->GetAllianceROE(userAlliance);

	roeStatus.landMode = tcGoalTracker::ROEMode(((int)roeStatus.landMode + 1) % 3);
	tcGoalTracker::Get()->SetAllianceROE(userAlliance, roeStatus);

	UpdateROEButtons();
}



void tcTacticalMapView::OnSize(wxSizeEvent& event)
{
    tcMapView::OnSize(event);

    wxSize size = event.GetSize();

    wxASSERT(show3DButton != 0);
    if (show3DButton != 0)
    {
        int buttonWidth = show3DButton->GetSize().GetWidth();
        show3DButton->MoveWindow(mnWidth-buttonWidth-5, 4);
    }
}

/**
* When user clicks on window outside game window, stop and disable mouse scroll
*/
void tcTacticalMapView::OnMouseCaptureLost(wxMouseCaptureLostEvent& event)
{
    CancelScroll();
}

/**
*
*/
void tcTacticalMapView::OnMouseMove(wxMouseEvent& event) 
{
    wxPoint point = event.GetPosition();
    mpointMouse = point;

	if (isMButtonDown)
	{
		wxSetCursor(moveCursor);
		UpdateMiddleButtonDragView(point);
		return;
	}

    if (scrollActive)
    {
        if (event.ControlDown() || event.AltDown() || event.ShiftDown())
        {
            CancelScroll();
        }
        else
        {
            UpdateEdgeScroll(point);
        }
    }

    //if (overlay->IsInteracting())
    //{
    //    overlay->OnMouseMove(event);
    //}
	
}

void tcTacticalMapView::OnMouseWheel(wxMouseEvent& event)
{
    // if object is hooked zoom on that position, otherwise zoom on center
    wxPoint zoomPoint;
    //if (hookedId.size() > 0)
    //{
    //    tcPoint hookScreen = GeoToScreen(mfHookLon, mfHookLat);
    //    zoomPoint.x = int(hookScreen.x);
    //    zoomPoint.y = int(hookScreen.y);
    //}
    //else
    //{
        zoomPoint.x = mnXCenter;
        zoomPoint.y = mnYCenter;
    //}

    int zDelta = event.GetWheelRotation();

    if (zDelta > 0) 
    {
        SetViewCenterZoom(zoomPoint, 1.25f);
        tcSound::Get()->PlayEffect("MutedBeep");
    }
    else if (zDelta < 0) 
    {
        SetViewCenterZoom(zoomPoint, 0.8f);
        tcSound::Get()->PlayEffect("MutedBeep");
    }
}

void tcTacticalMapView::SetActive(bool abActive)
{
    overlay->SetActive(abActive);
    tcMapView::SetActive(abActive);
	show3DButton->SetActive(abActive);

	if (!abActive) CancelScroll();
}

void tcTacticalMapView::SetBaseRenderBin(int n)
{
    tcMapView::SetBaseRenderBin(n);

    wxASSERT(overlay);
    overlay->SetBaseRenderBin(n - 5);
}

void tcTacticalMapView::SetCenterViewOnHooked(bool state)
{
    centerViewOnHooked = state;

    followHookedButton->SetOn(centerViewOnHooked);
}


void tcTacticalMapView::SetFormationEditId(long id)
{
    if (id == formationEditLeaderId) return; // already set

    if (id == -1) // clear formation editing
    {
        // close old objects
        if ((leaderFormationObject != -1) && tcRegistered::WindowExists(leaderFormationObject))
        {
            tcRegistered::ForceClose(leaderFormationObject);
            leaderFormationObject = -1;
        }
        if ((followerFormationObject != -1) && tcRegistered::WindowExists(followerFormationObject))
        {
            tcRegistered::ForceClose(followerFormationObject);
            followerFormationObject = -1;
        }
        formationEditLeaderId = id;
        return;
    }

    // check that new leader is in a formation and matches user alliance
    tcSimState* simState = tcSimState::Get();
    tcPlatformObject* leader = dynamic_cast<tcPlatformObject*>(simState->GetObject(id));
    if (leader == 0) return;
    if (!leader->formation.IsLeader()) return;
    if (leader->GetAlliance() != tcUserInfo::Get()->GetOwnAlliance()) return;

    // close old objects
    if ((leaderFormationObject != -1) && tcRegistered::WindowExists(leaderFormationObject))
    {
        tcRegistered::ForceClose(leaderFormationObject);
        leaderFormationObject = -1;
    }
    if ((followerFormationObject != -1) && tcRegistered::WindowExists(followerFormationObject))
    {
        tcRegistered::ForceClose(followerFormationObject);
        followerFormationObject = -1;
    }

    // add formation map object for viewing and editing formation
    tcFormationObject* formationObj = new tcFormationObject(id);
    leaderFormationObject = formationObj->GetKey();
    overlay->AddMapObject(formationObj);
    formationEditLeaderId = id;
}

void tcTacticalMapView::SetMissionEditId(long id)
{
    if (id == missionEditId) return; // already set


    // close old objects
    for (size_t k=0; k<missionBoxObjects.size(); k++)
    {
        if (tcRegistered::WindowExists(missionBoxObjects[k]))
        {
            tcRegistered::ForceClose(missionBoxObjects[k]);
        }
    }
    missionBoxObjects.clear();
    missionEditId = id;
        
    if (missionEditId == -1) return;
    
    tcSimState* simState = tcSimState::Get();
    tcPlatformObject* platform = dynamic_cast<tcPlatformObject*>(simState->GetObject(missionEditId));
    if (platform == 0)
    {
        missionEditId = -1;
        return;
    }

    // check if new mission edit platform has any random boxes
    tcScenarioRandomizer* randomizer = tcScenarioRandomizer::Get();

    std::vector<tcRect> boxes = randomizer->GetRandomBoxes(platform->mzUnit.c_str());

    // add new box objects for editing
    for (size_t k=0; k<boxes.size(); k++)
    {
        tcRandomBoxObject* box = new tcRandomBoxObject(missionEditId);
        box->SetBox(boxes[k]);
        overlay->AddMapObject(box);
        missionBoxObjects.push_back(box->GetKey());
    }
}


void tcTacticalMapView::SetGroupHook(std::vector<long>& hookedUnits)
{
    hookedId = hookedUnits;

	UpdateViewForHooked();
}

/**
* If id != -1, sets hookedId to have one element equal to id,
* otherwise clears the hookedId vector
*/
void tcTacticalMapView::SetHookID(long id)
{
    hookedId.clear();
    if (id != -1)
    {
        hookedId.push_back(id);
		UpdateViewForHooked();
    }

    UpdateFormationGraphics();
    UpdateMissionEditGraphics();
    UpdatePatrolAreaGraphics();
}

/**
* Sets callback parameters to use when map command is completed
*/
void tcTacticalMapView::SetMapCmdCallback(const char *azCallback, const std::vector<long>& id, int param, 
										  const std::string& textParam) 
{
    strcpy(mzMapCmdCallback,azCallback);
    callbackPlatformID = id;
    callbackParam = param;
	callbackTextParam = textParam;
}


/**
* Update button state for mode changes (e.g. scenario edit vs game mode)
*/
void tcTacticalMapView::UpdateButtons()
{
    if (!tcGameObject::IsEditMode() && !tcPlatformInterface::GetDeveloperMode())
    {
        revertToSaved->SetActive(false);
        changeSidesButton->SetActive(false);
    }
    else
    {
        revertToSaved->SetActive(true);
        changeSidesButton->SetActive(true);
    }
}

/**
* Callback method for tcWaypointPopup to change detailedEditPoint and allow
* tactical map graphics to be adjusted (highlighting edit point)
* @param updatedIdx is 1 higher than waypoint index
*/
void tcTacticalMapView::UpdateDetailedEditPointIndex(int updatedIdx)
{
    detailedEditPointIdx = updatedIdx;
}

/**
* Check if cursor is near edge of window, if so activate scroll
*
* MAR2009 Made some changes for windowed mode. Only allow out of window edge
* scroll if near the center of the side. Otherwise cancel the scroll to
* allow window resizing operations.
* APR2009 Another update, above is annoying, revert back to old behavior, cancel
* scroll when ctrl, alt, or shift down in OnMouseMove()
*/
void tcTacticalMapView::UpdateEdgeScroll(const wxPoint& pos)
{
	const int nScrollBorder = 15;
    
    mpointMouse = pos; 

    if (!enableEdgeScrolling)
    {
        scrollActive = false;
        return;
    }


    //int x1 = (mnWidth >> 3);
    //int x2 = mnWidth - (mnWidth >> 3);
    //bool isXcentered = (mpointMouse.x > x1) && (mpointMouse.x < x2);

    //int y1 = (mnHeight >> 1) - (mnHeight >> 2);
    //int y2 = (mnHeight >> 1) + (mnHeight >> 2);
    //bool isYcentered = (mpointMouse.y > y1) && (mpointMouse.y < y2);

	if ((mpointMouse.x < 0) || (mpointMouse.x > mnWidth) || (mpointMouse.y < 0) || (mpointMouse.y > mnHeight))
	{
		CancelScroll();
	}

    if (mpointMouse.x <= nScrollBorder)
    {
		scrollActive = true;
        scrollDirection = 270.0f;
    }
    else if (mpointMouse.x >= mnWidth - nScrollBorder) 
    {
        scrollActive = true;
        scrollDirection = 90.0f;
    }
    else if (mpointMouse.y <= nScrollBorder) 
    {
        scrollActive = true;
        scrollDirection = 0.0f;
    }
    else if (mpointMouse.y >= mnHeight - nScrollBorder)
    {
        scrollActive = true;
        scrollDirection = 180.0f;
    }
    else 
    {
        CancelScroll();
    }

	if (scrollActive)
	{
		float dx = float(mpointMouse.x - mnWidth/2);
		float dy = -float(mpointMouse.y - mnHeight/2);

		scrollDirection = C_180OVERPI * atan2f(dx, dy);

		if (!HasCapture())
		{
			lastScrollTime = tcTime::Get()->Get30HzCount();
			CaptureMouse();
		}

	}

}

/**
* Update patrol area and target datum edit map objects
*/
void tcTacticalMapView::UpdatePatrolAreaGraphics()
{
    // so we can maintain the same createTime when destroying/recreating patrolAreaObject
    unsigned int createTime = tcTime::Get()->Get30HzCount();
    if ((patrolAreaObject != -1) && tcRegistered::WindowExists(patrolAreaObject))
    {
        tcMapObject* mapObj = overlay->GetObjectByRegisteredId(patrolAreaObject);
        if (mapObj != 0)
        {
            createTime = mapObj->GetCreateTime();
        }
        tcRegistered::ForceClose(patrolAreaObject);
        patrolAreaObject = -1;
    }

    if ((datumEditObject != -1) && tcRegistered::WindowExists(datumEditObject))
    {
        tcMapObject* mapObj = overlay->GetObjectByRegisteredId(patrolAreaObject);
        if (mapObj != 0)
        {
            createTime = mapObj->GetCreateTime();
        }
        tcRegistered::ForceClose(datumEditObject);
        datumEditObject = -1;
    }

    if (hookedId.size() != 1) return;

    long id = hookedId[0];

    tcSimState* simState = tcSimState::Get();
    tcGameObject* gameObj = simState->GetObject(id);
    tcPlatformObject* platform = dynamic_cast<tcPlatformObject*>(gameObj);
    if (platform == 0) return;
    if (platform->GetAlliance() != tcUserInfo::Get()->GetOwnAlliance()) return;

    // check for active mission being edited
    // can't use navPointsMissionId because it isn't updated in time (might be cleaner way to do this)
    long missionId = -1;
    if (tcFlightOpsObject* flightOps = dynamic_cast<tcFlightOpsObject*>(gameObj))
    {
        if (tcFlightPort* flightPort = flightOps->GetFlightPort())
        {

            if (ai::tcMissionManager* missionManager = flightPort->GetMissionManager())
            {
                missionId = missionManager->GetEditMissionId();
            }
        }
    }


    // choose between editing mission or platform
    if (missionId == -1)
    {
        ai::BlackboardInterface bb = platform->GetBrain()->GetBlackboardInterface();
        if (bb.KeyExists("PatrolArea"))
        {
            tcPlatformAreaEditObject* areaEditObject = new tcPlatformAreaEditObject(id, -1);
            areaEditObject->SetCreateTime(createTime);
            patrolAreaObject = areaEditObject->GetKey();
            overlay->AddMapObject(areaEditObject);
        }

        if (bb.KeyExists("DatumLongitude") && bb.KeyExists("DatumLatitude"))
        {
            tcDatumEditObject* editObj = new tcDatumEditObject(id, -1);
            editObj->SetCreateTime(createTime);
            datumEditObject = editObj->GetKey();
            overlay->AddMapObject(editObj);
        }
    }
    else // mission edit for this platform
    {
        tcFlightOpsObject* flightOps = dynamic_cast<tcFlightOpsObject*>(gameObj);
        tcFlightPort* flightPort = flightOps->GetFlightPort();
        if (flightPort == 0) return;

        ai::tcMissionManager* missionManager = flightPort->GetMissionManager();
        if (missionManager == 0) return;

        ai::tcAttackMission* mission = dynamic_cast<ai::tcAttackMission*>(missionManager->GetMission(missionId));
        if (mission == 0) return;
    
        if (mission->GetArea().size() > 2)
        {
            tcPlatformAreaEditObject* areaEditObject = new tcPlatformAreaEditObject(id, missionId);
            areaEditObject->SetCreateTime(createTime - 500); // - 500 to make mission obj display instantly
            patrolAreaObject = areaEditObject->GetKey();
            overlay->AddMapObject(areaEditObject);
        }

        if (mission->HasTargetDatum())
        {
            tcDatumEditObject* editObj = new tcDatumEditObject(id, missionId);
            editObj->SetCreateTime(createTime - 500);
            datumEditObject = editObj->GetKey();
            overlay->AddMapObject(editObj);
        }
        
    }
    
}

/**
* Clear follower formation graphic and create new one for hooked object
* if hooked obj is part of formationEditLeaderId's formation
*/
void tcTacticalMapView::UpdateFormationGraphics()
{        
    if ((followerFormationObject != -1) && tcRegistered::WindowExists(followerFormationObject))
    {
        tcRegistered::ForceClose(followerFormationObject);
        followerFormationObject = -1;
    }

    if (hookedId.size() != 1) return;

    long id = hookedId[0];

    tcSimState* simState = tcSimState::Get();
    tcPlatformObject* platform = dynamic_cast<tcPlatformObject*>(simState->GetObject(id));
    if (platform == 0) return;

    if (platform->GetAlliance() != tcUserInfo::Get()->GetOwnAlliance()) return;

    if (platform->formation.isActive)
    {
        if (platform->formation.IsLeader())
        {
            SetFormationEditId(platform->mnID);
        }
        else
        {
            SetFormationEditId(platform->formation.leaderId);

            wxASSERT(!drawStarted);

            // add formation map object for viewing and editing formation
            tcFormationObject* formationObj = new tcFormationObject(id);
            followerFormationObject = formationObj->GetKey();
            overlay->AddMapObject(formationObj);
        }
    }
    else
    {
        SetFormationEditId(-1);
    }

}

void tcTacticalMapView::UpdateMiddleButtonDragView(const wxPoint& currentPos)
{
	if (!isMButtonDown) return;

	// middleDownPoint - screen coordinates of button down point
	// middleDownGeoPoint - geo coordinates to move to current mouse position

	tcPoint currentGeo = ScreenToGeo(currentPos);
	tcPoint deltaGeo = middleDownGeoPoint - currentGeo;

    tcPoint pCenterGeo;
    pCenterGeo.x = mrectCurrentView.XCenter();
    pCenterGeo.y = mrectCurrentView.YCenter();

	pCenterGeo.x += deltaGeo.x;
	pCenterGeo.y += deltaGeo.y;

    SetView(pCenterGeo, mrectCurrentView.Width());


}

void tcTacticalMapView::UpdateMissionEditGraphics()
{
    bool isMissionEditMode = tcGameObject::IsEditMode();

    if ((hookedId.size() != 1) || (!isMissionEditMode))
    {
        SetMissionEditId(-1);
        return;
    }
    
    SetMissionEditId(hookedId[0]);
}



void tcTacticalMapView::UpdateNavPointsOther(const std::vector<std::vector<NavPointInfo>>& navPoints)
{
    navPointsOther = navPoints;
}

void tcTacticalMapView::UpdateNavPointsPrimary(const std::vector<NavPointInfo>& navPoints, 
                                        int current, long platformId, long missionId) 
{  
    navPointsPrimary = navPoints;
    
    UpdateScreenNavPoints();

    navPointsPlatformId = platformId;

    bool missionIdChanged = (navPointsMissionId != missionId);
    navPointsMissionId = missionId;
    currentPointIdx = current;

    if (missionIdChanged)
    {
        UpdatePatrolAreaGraphics();
    }
}

/**
* Call periodically to update options
*/
void tcTacticalMapView::UpdateOptions()
{
    static bool expirationNeedsToBeChecked = true;

	UpdateROEButtons();

    // update symbology selection
	// 0 - 2525, 1 - NTDS
	if (mpOptions->symbologyType == 0)
	{
		meSymbology = M2525;
	}
	else
	{
		meSymbology = NTDS;
	}

    autoScrollTheater = mpOptions->autoScrollTheater != 0;
    enableEdgeScrolling = mpOptions->edgeScroll != 0;

    switch (mpOptions->surfVelocityLeader)
    {
    case 0: surfLeaderTime_s = 0; break;
    case 1: surfLeaderTime_s = 60.0f; break;
    case 2: surfLeaderTime_s = 120.0f; break;
    case 3: surfLeaderTime_s = 300.0f; break;
    default: surfLeaderTime_s = 0; break;
    }

    switch (mpOptions->airVelocityLeader)
    {
    case 0: airLeaderTime_s = 0; break;
    case 1: airLeaderTime_s = 30.0f; break;
    case 2: airLeaderTime_s = 60.0f; break;
    case 3: airLeaderTime_s = 120.0f; break;
    default: airLeaderTime_s = 0; break;
    }

    drawNavPointsMode = mpOptions->drawNavPointsMode;

    wxString revertCaption = "Revert to Last Save (";
	revertCaption += mpOptions->GetOptionString("ScenarioSavePath"); // full path and file name of last scenario
    revertCaption += ")";
    revertToSaved->SetMouseOverCaption(revertCaption.ToStdString());

    // dump debug text if showFrameCounter
#ifdef _DEBUG
    if (showFrameCounter)
    {
        wxString sText;

        tcTVEngine* engine = tcTVEngine::Get();
        const float kB_to_MB = 0.000976563f;

        float usedMemory_MB = kB_to_MB * float((engine->GetUsedTextureMemory()) >> 10);

        if (mfFrameRate != 0) 
        {
            sText.Printf("%s [%3.0f FPS] %.0f MB", dateTime.c_str(), mfFrameRate,
                usedMemory_MB);   
        }
        else 
        {
            sText.Printf("%s [ -- FPS] %.0f MB", dateTime.c_str(), 
                usedMemory_MB);   
        }


        tcSimState* simState = tcSimState::Get();
        if (simState->IsMultiplayerClient())
        {
            double multiplayerTimeLag_s = simState->GetMultiplayerTimeLag();
            tcString lagText;

            lagText.Format(" %.2f s", multiplayerTimeLag_s);

            sText += lagText.c_str();
        }

        sText += "\n";

        fprintf(stdout, "%s", sText.ToAscii());
    }
#endif

}

void tcTacticalMapView::UpdateScreenNavPoints() 
{
    size_t nPoints = navPointsPrimary.size();

    for (size_t n=0; n<nPoints; n++)
    {
        navPointsPrimary[n].screen = GeoToScreen(navPointsPrimary[n].geo.mfLon_rad, 
                                navPointsPrimary[n].geo.mfLat_rad);
    }

    // do same for navPointsOther
    if (drawNavPointsMode > 0)
    {
        size_t nSets = navPointsOther.size();

        for (size_t n=0; n<nSets; n++)
        {
            size_t nPoints = navPointsOther[n].size();
            for (size_t k=0; k<nPoints; k++)
            {
                navPointsOther[n][k].screen = GeoToScreen(navPointsOther[n][k].geo.mfLon_rad, 
                    navPointsOther[n][k].geo.mfLat_rad);
            }
        }
    }
}

/**
* Check if first hooked object is within the view. If not then
* center view on object.
*/
void tcTacticalMapView::UpdateViewForHooked()
{
	if (hookedId.size() == 0) return;

	tcSensorMapTrack track;
	if (tcSimState::Get()->GetTrack(hookedId[0], tcUserInfo::Get()->GetOwnAlliance(), track))
	{
		tcPoint pos(track.mfLon_rad, track.mfLat_rad);
		if (!PointInViewMiddle(pos, 0.25f)) // recenter if not close enough to screen center
		{
            bool temp = autoScrollTheater;
            autoScrollTheater = true; // temporarily override autoScrollTheater so we always change theater when hook is out of view

			tcPoint screen = GeoToScreen(pos);
			SetViewCenterZoom(wxPoint(screen.x, screen.y), 1.0);

            autoScrollTheater = temp;
		}
	}
	else
	{
		return; // hookedId doesn't exist (friendly) or not found in sensor map (other)
	}
}


/**
* View mode where map is updated every frame to center on hooked obj
*/
void tcTacticalMapView::UpdateViewCenterOnHooked()
{
    if (!centerViewOnHooked) return;

	if (hookedId.size() == 0)
    {
        SetCenterViewOnHooked(false);
        return;
    }

	tcSensorMapTrack track;
	if (tcSimState::Get()->GetTrack(hookedId[0], tcUserInfo::Get()->GetOwnAlliance(), track))
	{
		tcPoint pos(track.mfLon_rad, track.mfLat_rad);
	    tcPoint screen = GeoToScreen(pos);
		//SetViewCenterZoom(wxPoint(screen.x, screen.y), 1.0);
        SetViewCenterZoomFloat(screen.x, screen.y, 1.0f);
		
	}
	else
	{
        SetCenterViewOnHooked(false);
		return; // hookedId doesn't exist (friendly) or not found in sensor map (other)
	}
}



tcTacticalMapView::tcTacticalMapView(wxWindow *parent, 
                                     const wxPoint& pos, const wxSize& size,
									 tc3DWindow2* graphicsHost,
                                     const wxString& name) :
	tcMapView(parent, pos, size, graphicsHost, name),
	scrollActive(false),
	lastScrollTime(0),
	scrollDirection(0.0),
    mfHookLat(0),
    mfHookLon(0),
	showFrameCounter(false),
    units(tcUnits::Get()),
    formationEditLeaderId(-1),
    leaderFormationObject(-1),
    followerFormationObject(-1),
    patrolAreaObject(-1),
    datumEditObject(-1),
    missionEditId(-1),
    trackInfoMode(2),
    drawNavPointsMode(0),
    surfLeaderTime_s(0),
    airLeaderTime_s(0),
    centerViewOnHooked(false),
    worldMap(0),
    autoScrollTheater(false),
    navPointsPlatformId(-1),
    navPointsMissionId(-1),
    editPointIdx(-1),
    detailedEditPointIdx(-1),
    insertPointEditIdx(-1),
    waypointEditor(0),
    waypointEditorKey(-1),
    navPointEditLock(false),
	isMButtonDown(false),
	middleDownPoint(0, 0),
    enableEdgeScrolling(true)
{
    terrainView = new tcTerrainView(parent, pos, size, true);
    if (!terrainView) 
    {
        wxMessageBox("terrainView init failed\n");
    }


    overlay = new tcMapOverlay(this, pos, size);
    overlay->SetBaseRenderBin(5);
    overlay->SetActive(true);

    tc3DWindow2::MoveToTop(); // so that color elevation map is underneath

    overlay->MoveToTop();

    mnCounter = 0;
    dateTime = "INITIALIZING";
    mnGameMode = GAMEMODE_NORMAL;
    hookedId.clear();
    mbMapCmdActive = false;
    meMapCmd = MC_NONE;
    callbackParam = -1;
    mpMapData = NULL;
    mfFrameRate = 0;

    navPointsPrimary.clear();
    meSymbology = NTDS;
    isLButtonDown = false;
    leftMargin = 200.0f;
    mfLonWidth = C_PIOVER180*10.0f;

    ClearMapObjects(); 

#ifdef _DEBUG
	showFrameCounter = true;
#endif

    SetBorderDraw(true);

	InitializeButtons();

    tcWaypointPopup::tacticalMap = this;

	wxImage moveImage("images\\cursor_move.bmp");
	moveCursor = wxCursor(moveImage);
}

tcTacticalMapView::~tcTacticalMapView() 
{

}

