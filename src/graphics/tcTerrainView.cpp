/*  
**  tcTerrainView.cpp
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

#include "stdwx.h"

#ifndef WX_PRECOMP
#include "wx/wx.h" 
#ifdef WIN32
#include "wx/msw/private.h" // for MS Windows specific definitions
#endif
#endif

#include "tcTerrainView.h"
#include "tcOptions.h"
#include "tcTexture2D.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif 



void tcTerrainView::Draw()
{
	//if (!redraw) return;

    StartDraw();

	// if displayRegion is wrapped, draw two images

	if (!isWrapped)
	{
		DrawZoomedImage(mapImage.get(), 0, 0, (float)mnWidth, (float)mnHeight,
			displayRegion, ALIGN_BOTTOM_LEFT);

        //wxString s;
        //s.Printf("L:%f R:%f B:%f T:%f", displayRegion.left, displayRegion.right,
        //    displayRegion.bottom, displayRegion.top);
        //DrawText(s.c_str(), 400, 400, defaultFont.get(), Vec4(1, 1, 1, 1), 12.0f, CENTER_CENTER);
	}
	else
	{
		DrawZoomedImage(mapImage.get(), 0, 0, wrapWidth*(float)mnWidth, (float)mnHeight,
			displayRegion, ALIGN_BOTTOM_LEFT);
		DrawZoomedImage(mapImage.get(), wrapWidth*(float)mnWidth, 0, (1.0f-wrapWidth)*(float)mnWidth, (float)mnHeight,
			displayRegionWrapped, ALIGN_BOTTOM_LEFT);
	}

	FinishDraw();
	redraw = false;
}

void tcTerrainView::GetViewParameters(tsTerrainViewParameters& vp) 
{
	vp.mnSurfaceWidth = mnWidth;
	vp.mnSurfaceHeight = mnHeight;
	vp.mrectDisplay = mrectDisplay;
	vp.mrectGeo = mrectCurrentView;
}

/**
* If the terrain view is minimized always force
* abActive to false
*/
void tcTerrainView::SetActive(bool abActive)
{
	if (IsWindowMinimized())
	{
		tc3DWindow2::SetActive(false);
	}
	tc3DWindow2::SetActive(abActive);
}

/**
*
*/
void tcTerrainView::SetDisplayRegion(tcRect& r)
{
	displayRegion = r;
}

/**
* Sets new view, updating display region of map quad
*/
void tcTerrainView::SetView(tcGeoRect r) 
{
	if (mrectCurrentView == r) return; // no change, so return
	mrectCurrentView = r;

	isWrapped = r.left > r.right;

    if (isWrapped && highRes)
    {
        r.right += C_TWOPI;
        isWrapped = false;
    }

	if (!isWrapped)
	{
        float xLeft = (r.left - mrectMap.left);
        if (xLeft < 0) xLeft += C_TWOPI;

        float xRight = (r.right - mrectMap.left);
        if (xRight < 0) xRight += C_TWOPI;

		// assumes longitude is within [-pi,pi) and lat within [-pi/2,pi/2]
		displayRegion.left = xLeft/mrectMap.Width();
		displayRegion.right = xRight/mrectMap.Width();
		displayRegion.bottom = (r.bottom - mrectMap.bottom)/mrectMap.Height();
		displayRegion.top = (r.top - mrectMap.bottom)/mrectMap.Height();

		wrapWidth = 1.0f;
	}
	else
	{
		displayRegion.left = (r.left - mrectMap.left)/mrectMap.Width();
		displayRegion.right = 1.0f;
		displayRegion.bottom = (r.bottom - mrectMap.bottom)/mrectMap.Height();
		displayRegion.top = (r.top - mrectMap.bottom)/mrectMap.Height();

		displayRegionWrapped.left = 0;
		displayRegionWrapped.right = (r.right - mrectMap.left)/mrectMap.Width();
		displayRegionWrapped.bottom = (r.bottom - mrectMap.bottom)/mrectMap.Height();
		displayRegionWrapped.top = (r.top - mrectMap.bottom)/mrectMap.Height();

		wrapWidth = (1.0f - displayRegion.left) / (1.0f - displayRegion.left + displayRegionWrapped.right);
	}

	int texWidth = mapImage->Width();
	int texHeight = mapImage->Height();
	int requestedWidth = 0;
    int requestedHeight = 0;
	if (highRes)
	{
        requestedWidth = mpMapData->GetHighResColCount(); // N_HIGHRES;
        requestedHeight = mpMapData->GetHighResRowCount(); // M_HIGHRES
	}
	else
	{
		requestedWidth = N_LOWRES;
		requestedHeight = M_LOWRES;
	}

	if ((texWidth != requestedWidth) || (texHeight != requestedHeight))
	{
		float xscale = float(requestedWidth) / float(texWidth);
		float yscale = float(requestedHeight) / float(texHeight);

		displayRegion.left *= xscale;
		displayRegion.right *= xscale;
		displayRegion.top = 1 - (1-displayRegion.top)*yscale;
		displayRegion.bottom = 1 - (1-displayRegion.bottom)*yscale;

		displayRegionWrapped.left *= xscale;
		displayRegionWrapped.right *= xscale;
		displayRegionWrapped.bottom = 1 - (1-displayRegionWrapped.bottom)*yscale;
		displayRegionWrapped.top = 1 - (1-displayRegionWrapped.top)*yscale;
	}


	redraw = true;
}



int tcTerrainView::LoadLowResSurface() 
{
	tsMapDataInfo sMDI;

	mpMapData->GetMapDataInfo(&sMDI); // get size of map data arrays 

	int width = sMDI.mnLowResWidth;
	int height = sMDI.mnLowResHeight;
    
    mapImage->Create(width, height, false, "LowResMap");

	mpMapData->GetWorldArea(mrectMap);

	mpMapData->CreateMapImage(mpOptions->mnMapMode, 0, mapImage); // 1 for high res

	redraw = true;

	return true;
#if 0
	tsMapDataInfo sMDI;

	mpMapData->GetMapDataInfo(&sMDI); // get size of map data arrays 

	/*** Refresh low resolution map surface ***/
	int width = sMDI.mnLowResWidth;
	int height = sMDI.mnLowResHeight;

	osg::Image* image = mapImage->getImage();
	if (!image)
	{
		image = new osg::Image();
		mapImage->setImage(image);
	}
	image->allocateImage(width, height, 1, GL_RGBA, GL_UNSIGNED_BYTE, 1);

	mpMapData->GetWorldArea(mrectMap);


	unsigned int* pBits = (unsigned int*) image->data();

	wxASSERT(pBits != NULL);

	if (mpOptions != NULL) 
	{
		mpMapData->CreateMapImage(mpOptions->mnMapMode, 0, pBits);
	}
	else 
	{
		fprintf(stderr, "tcTerrainView::LoadLowResSurface - "
			"called without attached options, using default\n");
		mpMapData->CreateMapImage(1, 0, pBits);
	}

	redraw = true;
#endif

}

int tcTerrainView::LoadHighResSurface() 
{
	tsMapDataInfo sMDI;

	mpMapData->GetMapDataInfo(&sMDI); // get size of map data arrays 

	int width = sMDI.mnHighResWidth;
	int height = sMDI.mnHighResHeight;
    
    mapImage->Create(width, height, false, "HighResMap");

	mpMapData->GetTheaterArea(mrectMap);

	mpMapData->CreateMapImage(mpOptions->mnMapMode, 1, mapImage); // 1 for high res

	redraw = true;

	return true;
}

/**
* 
*/
void tcTerrainView::Maximize()
{
	tc3DWindow2::Maximize();
	redraw = true;
}


/**
* 
*/
void tcTerrainView::Minimize()
{
	// tc3DWindow2::SetActive(false);
	tc3DWindow2::Minimize();
	redraw = true;
}

int tcTerrainView::RefreshSurfaces() 
{
	if (mpMapData == NULL) 
	{
		wxMessageBox("tcTerrainView - RefreshSurfaces called with NULL mpMapData");
		return false;
	}

    int result = -1;

    tcGeoRect viewTemp = mrectCurrentView;

    mrectCurrentView.Set(0, 0, 0, 0); // just to trick SetView into working

	if (highRes) 
	{
		result =  LoadHighResSurface();
	}
	else 
	{
		result = LoadLowResSurface();
	}

    SetView(viewTemp);

    return result;
}


/**
*  
*/
int tcTerrainView::CreateSurfaces() 
{
    wxASSERT(false); // obsolete
	if (mpMapData == NULL) 
	{
		wxMessageBox("tcTerrainView - CreateSurfaces called with NULL mpMapData");
		return false;
	}

	if (highRes) 
	{
		return LoadHighResSurface();
	}
	else 
	{
		return LoadLowResSurface();
	}
}



tcTerrainView::tcTerrainView(wxWindow *parent, 
							 const wxPoint& pos, const wxSize& size, 
							 bool isHighRes, const wxString& name) 
							 :
tc3DWindow2(parent, pos, size, name, 0),
highRes(isHighRes),
displayRegion(0, 1, 0, 1),
redraw(true),
mapImage(new tcTexture2D)
{
	mpMapData = NULL;
	mpOptions = tcOptions::Get();
	SetResizeable2D(false); // do not resize 2D surface on resize 
	//mapImage = new osg::Texture2D();
	//     mapImage->setUseHardwareMipMapGeneration(true);
	//     mapImage->setInternalFormatMode(osg::Texture::USE_IMAGE_DATA_FORMAT);

	SetBlend(false);
}

tcTerrainView::~tcTerrainView() 
{

}

