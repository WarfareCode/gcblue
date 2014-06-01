/**  
**  @file tcMapView.h
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


#ifndef _MAPVIEW_H_
#define _MAPVIEW_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "wx/wx.h" 

#include "tc3DWindow2.h"
#include "simmath.h"
#include "commandlist.h"
#include "tcTerrainView.h"
#include <vector>
#include "wxcommands.h"

#include <boost/shared_ptr.hpp>
#include "tv_types.h"
#include "tcAllianceInfo.h"

class tcCommandQueue;
class tcMapData;
class tcMapObject;
class tcMapOverlay;
class tcGraphicsInfo;
class tcUnits;


#define MAXMAPOBJ	512
#define MAXWORLDMAPOBJ 1024 
#define NULL_INDEX -1
#define HEADING_UNKNOWN (float)-456.7
#define SCROLL_DELAY 8
#define SYMBOLOGY_PATH "symbology\\"

enum teSymbol
{
	SYMBOL_UNKNOWN = 0,
	SYMBOL_SURFACE = 1,
	SYMBOL_SMALLSURFACE = 2,
	SYMBOL_LARGESURFACE = 3,
	SYMBOL_CARRIER = 4,
    SYMBOL_SURFACEGROUP = 5,
    SYMBOL_CARRIERGROUP = 6,
	SYMBOL_AIR = 7,
	SYMBOL_FIXEDWING = 8,
	SYMBOL_MISSILE = 9,
	SYMBOL_HELO = 10,
	SYMBOL_SUBSURFACE = 11,
	SYMBOL_SUBMARINE = 12,
	SYMBOL_TORPEDO = 13,
	SYMBOL_FIXED = 14,
    SYMBOL_GROUNDVEHICLE = 15,
	SYMBOL_AIRFIELD = 16,
	SYMBOL_MARK = 17,
	SYMBOL_TARGET = 18,
	SYMBOL_PIE = 19,
    SYMBOL_LINE = 20
};

#define MAX_SYMBOL 18

enum teSymbology
{
	NTDS = 0,
	M2525 = 1,
};

class tcMapObj 
{
public:
	UCHAR mbExists;
	UCHAR mbFocus;
	unsigned int mnColor; ///< ARGB (ABGR?) color
	float mfHeading;
	double mfLon,mfLat;
    double mfLon2,mfLat2;
	float speed_kts;
	float alt_m; 
	teSymbol meSymbol;
	tcAllianceInfo::Affiliation meAffiliation;
	long mnID;
	float mfArc_deg; ///< for pie symbol
	float mfLonExtent; ///< for pie
	float mfLatExtent; ///< for pie
	bool isStaleTrack; ///< true for stale track
	bool isDestroyed; ///< true for destroyed track
	bool useAltered; ///< use altered symbol (e.g. for objects not controlled by player in multiplayer mode)    
    std::vector<tcPoint> errorPoly;

	UINT8 mnFlags; // same as tcTrack flags
	void Clear() 
	{
		meAffiliation = tcAllianceInfo::UNKNOWN;
		meSymbol = SYMBOL_UNKNOWN;
		mbExists=0;mbFocus=0;mnColor=0;mfHeading=0;mfLon=0;mfLat=0;mfLon2=0;mfLat2=0;mnID=0;speed_kts=0;alt_m=0;
		mnFlags = 0;
		isStaleTrack = false;
		isDestroyed = false;
		useAltered = false;
        errorPoly.clear();
	}
};

struct tsWorldMapObj
{
	UCHAR mbExists;
	unsigned int mnColor; 
	tcAllianceInfo::Affiliation meAffiliation;
	float mfLon,mfLat;
	unsigned long mnID;
	void Clear() {mbExists=0;mnColor=0;mfLon=0;mfLat=0;mnID=0;}
};


enum teMapCmdType
{
	MC_NONE,
	MC_HEADING,
	MC_TARGET,
	MC_DATUM,
    MC_RANGE, // draw range circle
    MC_BOX,
    MC_LINE
};

/* map symbol types */
/*
#define SYMBOL_UNKNOWN 0
#define SYMBOL_SURFACE 1
#define SYMBOL_SMALLSURFACE 2
#define SYMBOL_LARGESURFACE 3
#define SYMBOL_AIR 4
#define SYMBOL_FIXEDWING 5
#define SYMBOL_MISSILE 6
#define SYMBOL_HELO 7
#define SYMBOL_SUBSURFACE 8
#define SYMBOL_SUBMARINE 9
#define SYMBOL_TORPEDO 10
#define SYMBOL_FIXED 11
#define SYMBOL_SENSOR 30
#define SYMBOL_TARGET 40
#define SYMBOL_PIE 50
*/



/**
* Base class for tactical map and world map views
*/
class tcMapView : public tc3DWindow2 
{
public:
	// view parameters   
	int mnXCenter,mnYCenter; ///< center pixel coords of map window
	tcGeoRect mrectCurrentView;
	tcGeoRect mrectViewBounds; ///< can't view outside of these
	float mfLonCenter,mfLatCenter;	///< coordinates of center of current view
	float mfLonWidth,mfLatWidth; 
	float mfGridSize_rad;
	float mfGridBaseLon_rad,mfGridBaseLat_rad;
	float mfScaleX_pelprad;	///< map scale in X, pixels per radian
	float mfScaleX_radppel;  ///< map scale in X, radians per pixel
	float mfScaleY_pelprad;	///< map scale in Y, pixels per radian
	float mfScaleY_radppel;  ///< map scale in Y, radians per pixel
	std::vector<tcMapObject*> specialGraphics; ///< mission graphics display for now

	void AddMapObject(tcMapObject *obj);
	void ClearSpecialGraphics();

	void AttachMapData(tcMapData *apMapData) 
	{
		mpMapData=apMapData;
		terrainView->AttachMapData(apMapData);
	}
	void AttachOptions(tcOptions *apOptions) 
	{
		mpOptions=apOptions;
	}
	void AttachCommandInterface(tcCommandQueue *apCommandInterface);
	void CalcViewParameters();   
	virtual void Freeze();
	tcPoint GeoToScreen(tcPoint pgeo) const;
	tcPoint GeoToScreen(float afLon, float afLat) const;
	tcPoint GeoToScreen(double afLon, double afLat) const;
	float GeoLonExtentToScreen(float dlon_rad) const;
    float GeoLatExtentToScreen(float dlat_rad) const;
	Vec4 GetAffiliationColor(tcAllianceInfo::Affiliation a);

	int PointInView(tcPoint& p) const;
    int PointInViewMiddle(tcPoint& p, float scale) const;
	void RefreshTerrainView() {terrainView->RefreshSurfaces();}
	tcPoint ScreenToGeo(wxPoint pscreen) const;
	tcPoint ScreenToGeo(float x, float y) const;
    float LonToLatScale() const;
	virtual void SetActive(bool abActive); ///< overrides base class
	virtual void SetBaseRenderBin(int n);
	void SetSize(const wxRect& rect);
	virtual void SetView(tcPoint center, float afLonSpan);
	void SetViewCenterZoom(wxPoint pscreen, float afZoom);
    void SetViewCenterZoomFloat(float x, float y, float afZoom);
	//void SetWindow(RECT& r);
	void SetViewBounds(tcGeoRect& r) {mrectViewBounds = r;}
    float GetLonSpan() const;
    float GetLatSpan() const;

	virtual void Thaw();

	tcMapView(wxWindow *parent, 
		const wxPoint& pos, const wxSize& size, 
		tc3DWindow2* graphicsHost,
		const wxString& name = "MapView");
	virtual ~tcMapView();


protected:
	WCHAR mzwchar[255]; 
	tcCommandQueue *mpCommandInterface;
	tcMapData *mpMapData;
	tcOptions *mpOptions;
	tcTerrainView *terrainView;

	Vec4 ConvertColor(unsigned int nColor);

	virtual void OnSize(wxSizeEvent& event);
};


#endif 
