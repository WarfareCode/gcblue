/**  
**  @file tcWorldMapView.cpp
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

#include "tcWorldMapView.h"

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
#include "tcButton.h"

#include <math.h>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif 


BEGIN_EVENT_TABLE(tcWorldMapView, tc3DWindow2)
    EVT_COMMAND(11, wxEVT_COMMAND_BUTTON_CLICKED, tcWorldMapView::OnMinimizeCommand)
END_EVENT_TABLE()


/**
* Posts message to change tactical map theater
*/
void tcWorldMapView::ChangeTheater(float lon_deg, float lat_deg)
{
	// center on requested location
	//const float c1 = 0.5f * C_180OVERPI;
	//lon_deg -= c1 * mrectTheater.Width(); 
	//lat_deg += c1 * mrectTheater.Height();

    theaterCenter_deg.x = lon_deg;
    theaterCenter_deg.y = lat_deg;

	//lon_deg -= 0.5f * mpMapData->GetTheaterWidthDeg(); 
	//lat_deg += 0.5f * mpMapData->GetTheaterHeightDeg();

    if (lon_deg < -180.0f) lon_deg += 360.0f;
    if (lon_deg >= 180.0f) lon_deg -= 360.0f;

    if (lat_deg > 90.0f) lat_deg = 90.0f;
    if (lat_deg <-85.0f) lat_deg = -85.0f;

    if ((lon_deg < -180.0f) || (lon_deg >= 180.0f) || (lat_deg < -90.0f) || (lat_deg > 90.0f))
    {
        fprintf(stderr, "tcWorldMapView::ChangeTheater - out of bounds (lat %f deg, lon %f deg)",
            lat_deg, lon_deg);
        wxASSERT(false);
        return;
    }


	wxCommandEvent command(wxEVT_COMMAND_BUTTON_CLICKED, ID_SETTHEATER) ;    
	command.SetEventObject(this);

    long lon = (lon_deg > 0) ? long(8.0f*lon_deg + 0.5f) : long(8.0f*lon_deg - 0.5f);
    long lat = (lat_deg > 0) ? long(8.0f*lat_deg + 0.5f) : long(8.0f*lat_deg - 0.5f);

	long coordField = (lat << 16) + (lon & 0xFFFF);
	command.SetExtraLong(coordField); // 2.6.3 m_extraLong = coordField;
	AddPendingEvent(command);
}

/**
* Immediately applies theater change (used for load from dat file)
*/
void tcWorldMapView::ChangeTheaterNow(float lon_deg, float lat_deg)
{
    theaterCenter_deg.x = lon_deg;
    theaterCenter_deg.y = lat_deg;

    if (lon_deg < -180.0f) lon_deg += 360.0f;
    if (lon_deg >= 180.0f) lon_deg -= 360.0f;

    if (lat_deg > 90.0f) lat_deg = 90.0f;
    if (lat_deg <-85.0f) lat_deg = -85.0f;

    if ((lon_deg < -180.0f) || (lon_deg >= 180.0f) || (lat_deg < -90.0f) || (lat_deg > 90.0f))
    {
        fprintf(stderr, "tcWorldMapView::ChangeTheater - out of bounds (lat %f deg, lon %f deg)",
            lat_deg, lon_deg);
        wxASSERT(false);
        return;
    }

    // attempt to match rounding system used with ChangeTheater posted to tcGame
    float roundedLon_deg = 0.125f * float((lon_deg > 0) ? long(8.0f*lon_deg + 0.5f) : long(8.0f*lon_deg - 0.5f));
    float roundedLat_deg = 0.125f * float((lat_deg > 0) ? long(8.0f*lat_deg + 0.5f) : long(8.0f*lat_deg - 0.5f));

    tcMapData* mapData = tcMapData::Get();
    int theaterDecimation = mapData->GetTheaterDecimation();
    if ((theaterDecimation != 1) || (theaterDecimation != 4))
    {
        theaterDecimation = 1;
    }

	mapData->LoadHighResC(roundedLon_deg, roundedLat_deg, theaterDecimation);
}


/**
* Change the view center on the tactical map
*/
void tcWorldMapView::ChangeTacticalMapView(float lon_deg, float lat_deg)
{
    wxCommandEvent command(wxEVT_COMMAND_BUTTON_CLICKED, ID_SETTACTICALVIEW);
	command.SetEventObject(this);

    if (lon_deg > 180) lon_deg -= 360.0f; // map to -180 to 180

    long lon = (lon_deg > 0) ? long(100.0f*lon_deg + 0.5f) : long(100.0f*lon_deg - 0.5f);
    long lat = (lat_deg > 0) ? long(100.0f*lat_deg + 0.5f) : long(100.0f*lat_deg - 0.5f);

	long coordField = (lat << 16) + (lon & 0xFFFF);
	command.SetExtraLong(coordField);
	AddPendingEvent(command);
}

void tcWorldMapView::ClearMapObjects() 
{
    for(int i=0;i<MAXWORLDMAPOBJ;i++) 
    {
        maMapObj[i].Clear();
    }
    mnObjCount = 0;
}


int tcWorldMapView::CreateSurfaces(tcGraphicsInfo* apGraphicsEngine) 
{
    wxASSERT(false); // obsolete
#if 0
    // set terrain to low res
    terrainView->mbHighRes = false;
    if (mpMapData == NULL) 
    {
        wxMessageBox("Error - tcWorldMapView - CreateSurfaces called before attaching tcMapData obj");
    }
    else 
    {
        if (terrainView->CreateSurfaces(apGraphicsEngine) == false) {return false;}
    }
    return tcWindow::CreateSurfaces(apGraphicsEngine);  // MapView on top of TerrainView
#endif
	return true;
}


/**
*
*/
void tcWorldMapView::Draw() 
{
    int i;

    StartDraw();

	mpMapData->GetTheaterArea(mrectTheater); // update box to indicate theater area

    // done here to avoid artifacts from terrainview being out of sync with mapview
    terrainView->SetView(mrectCurrentView); 

    terrainView->Draw();

	if (mnWidth == iconSize)
	{
		//DrawIcon();

		FinishDraw();
		return;
	}

    /*** Draw grid ***/
    //DrawGrid();


    for(i=0;(i<(int)mnObjCount)&&(i<MAXWORLDMAPOBJ);i++) 
	{
        if (maMapObj[i].mbExists) 
		{
            DrawSymbol(&maMapObj[i]);
        }
    }

    DrawTheaterBox();

    if (showTacticalMapView) DrawTacticalMapView();

	FinishDraw();
}


/**
*
*/
void tcWorldMapView::DrawGrid() 
{
    float lat,lon;
    tcPoint pgeo,pscreen;

    if (mfGridSize_rad == 0) {return;}

	Vec4 color(0.69f, 0.69f, 0.69f, 1.0f);

    // change this to set range based on what will cover the screen as well
    for(lon=mfGridBaseLon_rad; lon<=mrectCurrentView.right; lon+=mfGridSize_rad)
	{
        pgeo.x = lon; pgeo.y = 0;
        pscreen = GeoToScreen(pgeo);
        DrawLineR(pscreen.x, 0, pscreen.x, mnHeight, color);
    }
    for(lat=mfGridBaseLat_rad; lat<=mrectCurrentView.top; lat+=mfGridSize_rad)
	{
        pgeo.y = lat; pgeo.x = 0;
        pscreen = GeoToScreen(pgeo);
        DrawLineR(0, pscreen.y, mnWidth, pscreen.y, color);
    }
}

void tcWorldMapView::DrawTacticalMapView() 
{
    tcPoint p1, p2;

    p1.x = tacticalMapView.left;
    p1.y = tacticalMapView.bottom;
    p2.x = tacticalMapView.right;
    p2.y = tacticalMapView.top;
    p1 = GeoToScreen(p1);
    p2 = GeoToScreen(p2);

	float fWidth = (float)mnWidth;
	float fHeight = (float)mnHeight;

	if ((p1.x > fWidth) || (p2.x < 0) ||
		(p2.y > fHeight) || (p1.y < 0))
	{
		return;
	}


	if (p1.x < 0) p1.x = 0;
	if (p2.y < 0) p2.y = 0;
	if (p2.x > fWidth) p2.x = fWidth;
	if (p1.y > fHeight) p1.y = fHeight;


    float width = p2.x - p1.x;
    float height = p1.y - p2.y;

	Vec4 color(0.6f, 0.6f, 1.0f, 0.2f);

    DrawRectangleR(p1.x, p2.y, width, height, color, tc3DWindow2::FILL_ON);
}


/**
*
*/
void tcWorldMapView::DrawTheaterBox() 
{
    float width,height;
    tcPoint p1, p2;


    mpMapData->GetTheaterArea(mrectTheater); // for box to indicate theater area

    p1.x = mrectTheater.left;
    p1.y = mrectTheater.bottom;
    p2.x = mrectTheater.right;
    p2.y = mrectTheater.top;
    p1 = GeoToScreen(p1);
    p2 = GeoToScreen(p2);

	float fWidth = (float)mnWidth;
	float fHeight = (float)mnHeight;

	if ((p1.x > fWidth) || (p2.x < 0) ||
		(p2.y > fHeight) || (p1.y < 0))
	{
		return;
	}


	if (p1.x < 0) p1.x = 0;
	if (p2.y < 0) p2.y = 0;
	if (p2.x > fWidth) p2.x = fWidth;
	if (p1.y > fHeight) p1.y = fHeight;

    if (p1.x > p2.x)
    {
        return; // this needs to draw two boxes, just don't draw anything and return for now
    }

    width = p2.x - p1.x;
    height = p1.y - p2.y;

	Vec4 color(1, 1, 1, 1);

	DrawRectangleR(p1.x, p2.y, width, height, color);
}

/**
*
*/
void tcWorldMapView::DrawSymbol(tsWorldMapObj *pMO) 
{
    tcPoint pscreen;
    tcRect rclipbounds;
    float x,y;

    // int type = pMO->mnSymbol;

	Vec4 symbolColor;// = ConvertColor(pMO->mnColor);

	if (pMO->mnColor)
	{
		symbolColor = ConvertColor(pMO->mnColor); 
		symbolColor.w = 1.0f; // override alpha for now
	}
	else
	{
		symbolColor = GetAffiliationColor(pMO->meAffiliation);
	}

    pscreen = GeoToScreen(pMO->mfLon, pMO->mfLat);
    x = pscreen.x;
    y = pscreen.y;

    // draw dots instead of symbols for world view
    //apGraphics->DrawPie(mpPen,rect,0,360);
	DrawRectangleR(x-1.0f, y-1.0f, 2.0f, 3.0f, symbolColor, FILL_ON);
}


const tcPoint& tcWorldMapView::GetTheaterCenter() const
{
    return theaterCenter_deg;
}

void tcWorldMapView::Init() 
{
    tcPoint p;

    ClearMapObjects();
    p.x = C_PIOVER180*0;
    p.y = C_PIOVER180*0;

    mpMapData->GetWorldArea(mrectViewBounds); // restrict view to theater area
    mpMapData->GetTheaterArea(mrectTheater); // for box to indicate theater area
    SetView(p, C_PIOVER180*340.0f);
}


void tcWorldMapView::OnChar(wxKeyEvent& event)
{
	int nChar = event.GetKeyCode();

	switch (nChar)
	{
	case WXK_UP:
		ScrollMap(0);
		return;
		break;
	case WXK_DOWN:
		ScrollMap(180);
		return;
		break;
	case WXK_LEFT:
		ScrollMap(270);
		return;
		break;
	case WXK_RIGHT:
		ScrollMap(90);
		return;
		break;
	}

	event.Skip();
}

void tcWorldMapView::OnLeaveWindow(wxMouseEvent& event)
{
    event.Skip();
    event.ResumePropagation(28); // so edge map scroll works
}


void tcWorldMapView::OnMinimizeCommand(wxCommandEvent& event)
{
	if (!IsWindowMinimized())
	{
		Minimize();
		terrainView->Minimize();
		minimizeButton->SetActive(false);
	}
}

void tcWorldMapView::OnLButtonDClick(wxMouseEvent& event)
{
    wxPoint point = event.GetPosition();

    tcSound::Get()->PlayEffect("MutedBeep");
    tcPoint geoPoint = ScreenToGeo(point); // geopoint (lon,lat) in radians

    ChangeTheater(C_180OVERPI * geoPoint.x, C_180OVERPI * geoPoint.y);

    tcSound::Get()->PlayEffect("MutedBeep");
}


void tcWorldMapView::OnLButtonDown(wxMouseEvent& event) 
{
    wxPoint point = event.GetPosition();
	if (event.AltDown())
	{
		tcSound::Get()->PlayEffect("MutedBeep");
		tcPoint geoPoint = ScreenToGeo(point); // geopoint (lon,lat) in radians
		
		ChangeTheater(C_180OVERPI * geoPoint.x, C_180OVERPI * geoPoint.y);

		tcSound::Get()->PlayEffect("MutedBeep");
	}
    else if (event.ControlDown()) 
    {
        if (mfLonWidth > 30.0f*C_PIOVER180) 
        {
            SetViewCenterZoom(point,2.0f);
            tcSound::Get()->PlayEffect("MutedBeep");
        }
    }
    else if (event.ShiftDown()) 
    {
        SetViewCenterZoom(point,1.0f);
        tcSound::Get()->PlayEffect("MutedBeep");
    }
    else 
    {
		if (IsWindowMinimized()) ToggleMapSize(); // so maximize only on general left click
    }
}


void tcWorldMapView::OnLButtonUp(wxMouseEvent& event)
{
    if (event.ShiftDown() || event.ControlDown() || event.AltDown()) return;

    wxPoint point = event.GetPosition();

    tcPoint geoPoint = ScreenToGeo(point); // geopoint (lon,lat) in radians

    ChangeTacticalMapView(C_180OVERPI * geoPoint.x, C_180OVERPI * geoPoint.y);
}


void tcWorldMapView::OnRButtonDown(wxMouseEvent& event) 
{
    wxPoint point = event.GetPosition();
    if (event.ControlDown()) 
    {
        SetViewCenterZoom(point,0.5f);
        tcSound::Get()->PlayEffect("MutedBeep");
    }
}


void tcWorldMapView::OnMouseMove(wxMouseEvent& event) 
{
    wxPoint point = event.GetPosition();
    mpointMouse = point; // TranslatePoint(point);

	event.Skip();
}


void tcWorldMapView::OnMouseWheel(wxMouseEvent& event)
{
    // zoom on center
    wxPoint zoomPoint;

	zoomPoint.x = mnXCenter;
	zoomPoint.y = mnYCenter;

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


/**
*
*/
void tcWorldMapView::ScrollMap(float direction_deg) 
{
    float dx,dy;
    float direction_rad = (float)C_PIOVER180*direction_deg;
    float dr = mfScaleX_radppel*16.0f; 

    dx = sinf(direction_rad)*dr;
    dy = cosf(direction_rad)*dr;

    tcPoint p;
    p.x = mrectCurrentView.XCenter() + dx;
    p.y = mrectCurrentView.YCenter() + dy;

    SetView(p, mrectCurrentView.Width());
}


/**
*
*/
void tcWorldMapView::SetActive(bool abActive)
{
	if (!IsActive()) wxWindow::Raise();
	tcMapView::SetActive(abActive);
}

void tcWorldMapView::SetShowTacticalMapView(bool state)
{
    showTacticalMapView = state;
}

void tcWorldMapView::SetTacticalMapView(const tcGeoRect& view)
{
    tacticalMapView = view;
}

void tcWorldMapView::SetTheater(tcGeoRect r)
{
    mrectTheater = r;
}

void tcWorldMapView::SetTheaterCenter(float lon_deg, float lat_deg)
{
    theaterCenter_deg.x = lon_deg;
    theaterCenter_deg.y = lat_deg;
}

/**
*
*/
void tcWorldMapView::ToggleMapSize()
{
	if (IsWindowMinimized())
	{
		Maximize();
		terrainView->Maximize();
		minimizeButton->SetActive(true);
	}
	else
	{
		Minimize();
		terrainView->Minimize();
		minimizeButton->SetActive(false);
	}
}

tcWorldMapView::tcWorldMapView(wxWindow *parent, 
                               const wxPoint& pos, const wxSize& size, 
							   tc3DWindow2* graphicsHost,
                               const wxString& name) :
    tcMapView(parent, pos, size, graphicsHost, name),
    theaterCenter_deg(0, 0),
    showTacticalMapView(false)
{
    terrainView = new tcTerrainView(parent, pos, size, false);
    if (!terrainView) {wxMessageBox("terrainView init failed\n");}

	MoveToTop(); // so that color elevation map is underneath
    mnCounter = 0;
    ClearMapObjects();

    SetBorderDraw(true);

	int buttonWidth = 16;
	minimizeButton = new tcButton(this, wxPoint(mnWidth-buttonWidth-4, 3),
		wxSize(buttonWidth, buttonWidth), "MinimizeButton");
	minimizeButton->SetCaption("");
	minimizeButton->LoadImages("minimize.jpg", "minimize.jpg", "minimize_over.jpg", 
		"minimize_over.jpg");
	minimizeButton->SetCommand(11);
}

tcWorldMapView::~tcWorldMapView() 
{

}



