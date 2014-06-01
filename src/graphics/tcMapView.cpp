/**  
**  @file tcMapView.cpp
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

#include "tcMapView.h"
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


using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif 


void tcMapView::AttachCommandInterface(tcCommandQueue* apCommandInterface) 
{
    tcMapObject::SetCommandInterface(apCommandInterface);
    mpCommandInterface = apCommandInterface;
}


/**
* Add obj to specialGraphics vector. Calling entity is
* responsible for creating and deleting the object.
*/
void tcMapView::AddMapObject(tcMapObject *obj)
{
    specialGraphics.push_back(obj);
}


/**
* Clears specialGraphics vector. tcMapView does not delete
* the objects on clear. May need a cleaner system for this
* with managed/reference pointers.
*/
void tcMapView::ClearSpecialGraphics()
{
    specialGraphics.clear();
}


/**
* called for change of view, may want to rename or make a change view function
*/
void tcMapView::CalcViewParameters() 
{
	mnWidth = mrectWindow.GetWidth();
    mnHeight = mrectWindow.GetHeight();
    mnXCenter = mnWidth/2;  // assume drawing surface upper left corner at (0,0)
    mnYCenter = mnHeight/2;
    mfLonWidth = mrectCurrentView.Width();
    mfLatWidth = mrectCurrentView.Height();
    mfLonCenter = mrectCurrentView.XCenter();
    mfLatCenter = mrectCurrentView.YCenter();
    if (mfLonWidth < C_PIOVER180*1.5f) 
	{
        mfGridSize_rad = C_PIOVER180*(10.0f/60.0f);  // 10 nmi
    }
    else if (mfLonWidth < C_PIOVER180*10.0f)
	{
        mfGridSize_rad = C_PIOVER180*1.0f; // 1 deg, 60 nmi
    }
    else if (mfLonWidth < C_PIOVER180*50.0f) 
	{
        mfGridSize_rad = C_PIOVER180*2.0f; // 2 deg
    }
    else if (mfLonWidth < C_PIOVER180*100.0f) 
	{
        mfGridSize_rad = C_PIOVER180*10.0f; // 10 deg, 600 nmi
    }
    else 
	{
        mfGridSize_rad = C_PIOVER180*45.0f;
    }

    mfGridBaseLon_rad = mfGridSize_rad*floorf(mrectCurrentView.left/mfGridSize_rad);
    mfGridBaseLat_rad = mfGridSize_rad*floorf(mrectCurrentView.bottom/mfGridSize_rad);
    mfScaleX_pelprad = mnWidth/mfLonWidth;
    mfScaleX_radppel = 1/mfScaleX_pelprad;
    mfScaleY_pelprad = mnHeight/mfLatWidth;
    mfScaleY_radppel = 1/mfScaleY_pelprad;

    /*
    fprintf(stdout, "*** setting map view to L:%f R:%f T:%f B:%f\n", 
    mrectCurrentView.left, mrectCurrentView.right, 
    mrectCurrentView.top, mrectCurrentView.bottom);
    fprintf(stdout, "        map window L:%d R:%d T:%d B:%d\n", 
    mrectWindow.left, mrectWindow.right, mrectWindow.top, mrectWindow.bottom);
    tcPoint testPoint = GeoToScreen(mfGridBaseLon_rad, mfGridBaseLat_rad);
    fprintf(stdout, "        base geo (%f,%f) screen(%f, %f)\n", 
    mfGridBaseLon_rad,mfGridBaseLat_rad,
    testPoint.x, testPoint.y);
    */

}


/**
* converts ARGB integer color to Vec4 float format
*/
Vec4 tcMapView::ConvertColor(unsigned int nColor)
{
	float alpha = (nColor & 0xFF000000) >> 24;
	float red = (nColor & 0x00FF0000) >> 16;
	float green = (nColor & 0x0000FF00) >> 8;
	float blue = (nColor & 0x000000FF);

	const float k = 1.0f / 255.0f;
	alpha *= k;
	red *= k;
	green *= k;
	blue *= k;

	return Vec4(red, green, blue, alpha);
}


/**
* Works with Thaw to prevent flicker on resize
* @see tcMapView::Thaw
* @see tcWindow::Thaw
*/
void tcMapView::Freeze()
{
	tc3DWindow2::Freeze();
    terrainView->Freeze();
}


tcPoint tcMapView::GeoToScreen(tcPoint pgeo) const
{
    tcPoint pscreen;

    float dx_rad = pgeo.x - mfLonCenter;
    dx_rad += float(dx_rad < -C_PI)*C_TWOPI - float(dx_rad > C_PI)*C_TWOPI;
    //pscreen.x = (pgeo.x - mfLonCenter)*mfScaleX_pelprad + mnXCenter;

    pscreen.x = dx_rad*mfScaleX_pelprad + mnXCenter;
    pscreen.y = (-pgeo.y + mfLatCenter)*mfScaleY_pelprad + mnYCenter; 
    return pscreen;
}


tcPoint tcMapView::GeoToScreen(float afLon, float afLat) const
{
    tcPoint pscreen;

    float dLon_rad = afLon - mfLonCenter;
    dLon_rad += float(dLon_rad < -C_PI)*C_TWOPI - float(dLon_rad > C_PI)*C_TWOPI;

    pscreen.x = (dLon_rad)*mfScaleX_pelprad + mnXCenter;
    pscreen.y = (-afLat + mfLatCenter)*mfScaleY_pelprad + mnYCenter; 
    return pscreen;
}


tcPoint tcMapView::GeoToScreen(double afLon, double afLat) const
{
    tcPoint pscreen;

    double dLon_rad = afLon - (double)mfLonCenter;
    dLon_rad += double(dLon_rad < -C_PI)*C_TWOPI - double(dLon_rad > C_PI)*C_TWOPI;
    
    pscreen.x = (dLon_rad)*mfScaleX_pelprad + mnXCenter;
    pscreen.y = (-afLat + (double)mfLatCenter)*mfScaleY_pelprad + mnYCenter; 
    return pscreen;
}


float tcMapView::GeoLonExtentToScreen(float dlon_rad) const
{
    return dlon_rad*mfScaleX_pelprad; 
}

float tcMapView::GeoLatExtentToScreen(float dlat_rad) const
{
    return dlat_rad*mfScaleY_pelprad; 
}

/**
* @return lon scale factor relative to latitude (left/right relative to up/down)
*/
float tcMapView::LonToLatScale() const
{
    return mfScaleX_pelprad * mfScaleY_radppel;
}


Vec4 tcMapView::GetAffiliationColor(tcAllianceInfo::Affiliation a) 
{

    switch (a) 
	{
      case tcAllianceInfo::UNKNOWN:
          //return 0xFFFFFF7F;
		  return Vec4(1.0f, 1.0f, 0.5f, 1.0f);
      case tcAllianceInfo::FRIENDLY:
          //return 0xFF77DDFF;
		  return Vec4(0.467f, 0.867f, 1.0f, 1.0f);
      case tcAllianceInfo::NEUTRAL:
          //return 0xFF88FF88;
		  return Vec4(0.533f, 1.0f, 0.533f, 1.0f);
      case tcAllianceInfo::HOSTILE:
          //return 0xFFFF5035;
		  return Vec4(0.9f, 0.3f, 0.2f, 1.0f);
          break;
      default:
          //return 0xFFFFFFFF;
		  return Vec4(1, 1, 1, 1);
          break;
    }
}

float tcMapView::GetLonSpan() const
{
    return mfLonWidth;
}

float tcMapView::GetLatSpan() const
{
    return mfLatWidth;
}

tcPoint tcMapView::ScreenToGeo(wxPoint pscreen) const
{
    tcPoint pgeo;
    pgeo.x = ((float)pscreen.x - mnXCenter)*mfScaleX_radppel + mfLonCenter;
    pgeo.y = ((float)-pscreen.y + mnYCenter)*mfScaleY_radppel + mfLatCenter;
    return pgeo;
}


tcPoint tcMapView::ScreenToGeo(float x, float y) const
{
    tcPoint pgeo;
    pgeo.x = (x - mnXCenter)*mfScaleX_radppel + mfLonCenter;
    pgeo.y = (-y + mnYCenter)*mfScaleY_radppel + mfLatCenter;
    return pgeo;
}


/**
* Works with Freeze to prevent flicker on resize
*/
void tcMapView::Thaw()
{
	tc3DWindow2::Thaw();
    terrainView->Thaw();
}


/**
* Call OnSize for base class and for terrainView
*/
void tcMapView::OnSize(wxSizeEvent& event)
{
    tc3DWindow2::OnSize(event);
    wxPoint pos = wxWindow::GetPosition();
    // mnWidth and mnHeight updated by tcWindow::OnSize
    CalcViewParameters();
}


/**
* assumes radian coordinates
*/
int tcMapView::PointInView(tcPoint& p) const
{
    bool yPass = (p.y >= mrectCurrentView.bottom)&&(p.y <= mrectCurrentView.top);

    bool isWrapped = mrectCurrentView.right < mrectCurrentView.left;

    bool xPass = isWrapped ? (p.x >= mrectCurrentView.left) || (p.x <= mrectCurrentView.right) :
                             (p.x >= mrectCurrentView.left) && (p.x <= mrectCurrentView.right);

    return yPass && xPass;
}

/**
* assumes radian coordinates
* @param scale 0-1 factor for how close to center point must be to be "in view"
* 0 is same as PointInView, 0.5 would be center 50% of view
*/
int tcMapView::PointInViewMiddle(tcPoint& p, float scale) const
{
    float ymargin = 0.5f*scale*(mrectCurrentView.top - mrectCurrentView.bottom);
    bool yPass = (p.y >= (mrectCurrentView.bottom+ymargin))&&(p.y <= (mrectCurrentView.top-ymargin));

    bool isWrapped = mrectCurrentView.right < mrectCurrentView.left;

    if (isWrapped)
    {
        float x1 = mrectCurrentView.left;
        float x2 = mrectCurrentView.right + C_TWOPI;
        float xp = p.x;
        if (xp < 0) xp += C_TWOPI;
        float xmargin = 0.5f*scale*(x2 - x1);
        bool xPass = (xp >= (x1+xmargin)) || (xp <= (x2-xmargin));
        return yPass && xPass;
    }
    else
    {
        float xmargin = 0.5f*scale*(mrectCurrentView.right - mrectCurrentView.left);
        bool xPass = (p.x >= (mrectCurrentView.left+xmargin)) && (p.x <= (mrectCurrentView.right-xmargin));
        return yPass && xPass;
    }
}


/**
* override of wxWindow::SetSize so that terrainView->SetSize is called as well
*/
void tcMapView::SetSize(const wxRect& rect)
{
    terrainView->SetSize(rect);
    wxWindow::SetSize(rect);
}


/**
*
*/
void tcMapView::SetViewCenterZoom(wxPoint pscreen, float afZoom) 
{
    SetView(ScreenToGeo(pscreen), mfLonWidth/afZoom);
}

/**
* Version with floating point arguments for screen coords
*/
void tcMapView::SetViewCenterZoomFloat(float x, float y, float afZoom) 
{
    SetView(ScreenToGeo(x, y), mfLonWidth/afZoom);
}


/**
*
*/
void tcMapView::SetView(tcPoint center, float afLonSpan) 
{
    if (center.x < -C_PI) {center.x += C_TWOPI;}
    else if (center.x >= C_PI) {center.x -= C_TWOPI;}

    // equirectangular projection stretch factor, to roughly equalize map projection
    float lat_factor = std::max(cosf(center.y), 0.5f);
    float aspect_ratio = float(mnWidth) / (float(mnHeight) * lat_factor); // lon to lat aspect ratio

    float fMaxLonSpan = mrectViewBounds.Width();
    float fMaxLatSpan = mrectViewBounds.Height();
    if (afLonSpan > fMaxLonSpan) {afLonSpan = fMaxLonSpan;}
    float fLatSpan = afLonSpan / aspect_ratio;
    if (fLatSpan > fMaxLatSpan) 
    {
        fLatSpan = fMaxLatSpan;
        afLonSpan = fLatSpan * aspect_ratio;
    }
    
    float minLatSpan = 100.0f * C_MTORAD; // limit zoom to 100 m over height of view
    if (fLatSpan < minLatSpan)
    {
        fLatSpan = minLatSpan;
        afLonSpan = fLatSpan * aspect_ratio;
    }

    tcGeoRect newview;
    newview.Set(center.x - 0.5f*afLonSpan, center.x + 0.5f*afLonSpan,
        center.y - 0.5f*fLatSpan,  center.y + 0.5f*fLatSpan);


    mrectViewBounds.ApplyBounds(newview);

    mrectCurrentView = newview;
    if (newview.left > newview.right) 
    {
        //WTLC("wrap error");
        //wxASSERT(false);
    }
    CalcViewParameters();

}


/**
*
*/
void tcMapView::SetActive(bool abActive) 
{
	tc3DWindow2::SetActive(abActive);
    terrainView->SetActive(abActive);
}


void tcMapView::SetBaseRenderBin(int n)
{
    tc3DWindow2::SetBaseRenderBin(n);
    terrainView->SetBaseRenderBin(n - 10);
}


tcMapView::tcMapView(wxWindow *parent, 
                     const wxPoint& pos, const wxSize& size, 
					 tc3DWindow2* graphicsHost,
                     const wxString& name) :
tc3DWindow2(parent, pos, size, name, graphicsHost),
terrainView(NULL)
{

    mpCommandInterface = NULL;
    mpMapData = NULL;
    mpOptions = NULL;

    mnXCenter = 0;
    mnYCenter = 0;
    mrectCurrentView.Set(0,0,0,0);
    mrectViewBounds.Set(0,0,0,0);

    specialGraphics.clear();
}


tcMapView::~tcMapView() 
{

}
