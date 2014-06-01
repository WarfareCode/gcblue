/**  
**  @file tcMapData.cpp
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
#endif

#include "tcMapData.h"
#include "aerror.h"
#include "math.h"
#include "tcFile.h"
#include "tcString.h"
#include "tcDemTileReader.h"
#include "tcTexture2D.h"
#include "tcTVEngine.h"
#include "tcTime.h"
#include "nsNav.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using std::max;
using std::min;

tcMapData* tcMapData::Get()
{
	static tcMapData instance;

	return &instance;
}

/**
* gets size of low res and high res map data arrays 
*/
void tcMapData::GetMapDataInfo(tsMapDataInfo *pMDI) 
{
	pMDI->mnLowResHeight = M_LOWRES;
	pMDI->mnLowResWidth = N_LOWRES;
	pMDI->mnHighResHeight = M_HIGHRES;
	pMDI->mnHighResWidth = N_HIGHRES;
}

/**
* returns coordinate near (lon,lat) within altitude range. If
* a random point cannot be found within the altitude range after
* the max number of attempts, the last point with an invalid altitude
* is returned.
* @param lon reference longitude in degrees
* @param lat ref latitude in deg
* @param r peak-to-peak random variation in deg for lon and lat
* @param minAlt minimum altitude in meters
* @param maxAlt maximum altitude in meters
*/
GeoPoint tcMapData::GetRandomPointNear(float lon, float lat, 
										 float r, float minAlt, float maxAlt)
{
	enum {MAX_TRIALS = 100};
	GeoPoint p;

	int trial = 0;
	float randomLon = 0;
	float randomLat = 0;
	float alt = 0;
	while (trial++ < MAX_TRIALS)
	{
		randomLon = lon + randfc(r);
		randomLat = lat + randfc(r);
		alt = GetTerrainHeight(randomLon, randomLat, 0);
		if ((alt >= minAlt)&&(alt <= maxAlt))
		{
			p.mfAlt_m = alt;
			p.mfLon_rad = C_PIOVER180*randomLon;
			p.mfLat_rad = C_PIOVER180*randomLat;
			return p;
		}
	}
	fprintf(stderr, "GetRandomPointNear couldn't find valid point. (%.2f,%.2f) [%.0f,%.0f] %f\n",
		lon,lat,minAlt,maxAlt,r);
	p.mfAlt_m = alt;
	p.mfLon_rad = C_PIOVER180*randomLon;
	p.mfLat_rad = C_PIOVER180*randomLat;
	return p;
}

/********************************************************************/
/**
* setup rectangles to blt low resolution world map to view surface
*/
int tcMapData::GetLowResBltList(tcRect view, int anWidth, int anHeight, RECT *aaSource, RECT *aaDest) {
	RECT rSource;
	float fLonSpan_deg, fLatSpan_deg, fLonScale, fLatScale;
	float fViewTopOffset, fViewLeftOffset, fUnwrapped;
	int n;
	int bJitterPatch = 1;

	//if (view.left < -180.0f) {view.left += 360.0f;}
	//if (view.left >= 180.0f) {view.left -= 360.0f;}
	//if (view.right < -180.0f) {view.right += 360.0f;}
	//if (view.right >= 180.0f) {view.right -= 360.0f;}


	rSource.top = ((int)floorf((90.0f - view.top)*SCALE_LOWRES));
	rSource.left = ((int)floorf((view.left + 180.0f)*SCALE_LOWRES)-1);
	rSource.bottom = ((int)floorf((90.0f - view.bottom)*SCALE_LOWRES));
	rSource.right = ((int)floorf((view.right + 180.0f)*SCALE_LOWRES)+1);
	if (rSource.top != 0) {rSource.top--;}
	if (rSource.bottom < (M_LOWRES - 1)) {rSource.bottom++;}
	if (bJitterPatch) {if (rSource.left % 16 ==0) {rSource.left--;rSource.right--;}}

	rSource.top %= M_LOWRES; // mod negative for negative numbers!?
	if (rSource.top < 0) {rSource.top += M_LOWRES;}
	rSource.bottom %= M_LOWRES;
	if (rSource.bottom < 0) {rSource.bottom += M_LOWRES;}
	rSource.left %= N_LOWRES;
	if (rSource.left < 0) {rSource.left += N_LOWRES;}
	rSource.right %= N_LOWRES;
	if (rSource.right < 0) {rSource.right += N_LOWRES;}

	aaSource[0].left = rSource.left;
	aaSource[0].right = (rSource.right >= rSource.left) ? rSource.right : N_LOWRES;
	aaSource[0].bottom = rSource.bottom;
	aaSource[0].top = (rSource.bottom >= rSource.top) ? rSource.top : 0;

	aaSource[1].left = (rSource.right >= rSource.left) ? rSource.left : 0;
	aaSource[1].right = rSource.right;
	aaSource[1].bottom = (rSource.bottom >= rSource.top) ? rSource.bottom : M_LOWRES;
	aaSource[1].top =  rSource.top;

	fLonSpan_deg = view.Width();
	fLatSpan_deg = view.Height();
	if (fLonSpan_deg < 0) {fLonSpan_deg += 360.0f;}
	if (fLatSpan_deg < 0) {fLatSpan_deg += 360.0f;}
	fLatScale = (float)anHeight/fLatSpan_deg;
	fLonScale = (float)anWidth/fLonSpan_deg;
	fViewTopOffset = (view.top - 90.0f)*fLatScale;
	fViewLeftOffset = (view.left + 180.0f)*fLonScale;

	for(n=0;n<2;n++) {
		aaDest[n].top = (int)(fViewTopOffset + (float)aaSource[n].top*RESLOW_DEG*fLatScale);
		aaDest[n].bottom = (int)(fViewTopOffset + (float)aaSource[n].bottom*RESLOW_DEG*fLatScale);
		fUnwrapped = (float)aaSource[n].left*RESLOW_DEG;
		if (fUnwrapped < view.left+160.0f) {fUnwrapped += 360.0f;}
		aaDest[n].left = (int)(fUnwrapped*fLonScale - fViewLeftOffset);
		if (bJitterPatch) {if (aaDest[n].left<0) aaDest[n].left = 0;}
		fUnwrapped = (float)aaSource[n].right*RESLOW_DEG;
		if (fUnwrapped < view.left+160.0f) {fUnwrapped += 360.0f;}
		aaDest[n].right = (int)(fUnwrapped*fLonScale - fViewLeftOffset);
	}
	if (rSource.right >= rSource.left) {
		return 1;
	}
	else {
		return 2;
	}
}

/********************************************************************/
/**
* setup rectangles to blt high resolution world map to view surface
*/
int tcMapData::GetHighResBltList(tcRect view, int anWidth, int anHeight, RECT *aaSource, RECT *aaDest) {
    wxASSERT(false); // obsolete
    return 0;
#if 0
	RECT rSource;
	float fLonSpan_deg, fLatSpan_deg, fLonScale, fLatScale;
	float fViewTopOffset, fViewLeftOffset, fUnwrapped;
	int n;
	int bJitterPatch = 1;

	//if (view.left < -180.0f) {view.left += 360.0f;}
	//if (view.left >= 180.0f) {view.left -= 360.0f;}
	//if (view.right < -180.0f) {view.right += 360.0f;}
	//if (view.right >= 180.0f) {view.right -= 360.0f;}

	if (mrTheaterView.left <= mrTheaterView.right) {
		if ((view.left > mrTheaterView.right)||(view.right < mrTheaterView.left)||
			(view.top < mrTheaterView.bottom)||(view.bottom > mrTheaterView.top)) {
				return 0;
			}
	}
	else {
		return 0; // add later
	}

	rSource.top = ((int)floorf((mrTheaterView.top - view.top)*SCALE_HIGHRES));
	rSource.left = ((int)floorf((view.left - mrTheaterView.left)*SCALE_HIGHRES)-1);
	rSource.bottom = ((int)floorf((mrTheaterView.top - view.bottom)*SCALE_HIGHRES));
	rSource.right = ((int)floorf((view.right - mrTheaterView.left)*SCALE_HIGHRES)+1);
	if (rSource.top != 0) {rSource.top--;}
	if (rSource.bottom < (M_HIGHRES - 1)) {rSource.bottom++;}
	rSource.top = max((int)rSource.top,0);
	rSource.bottom = min((int)rSource.bottom,M_HIGHRES);
	rSource.left = max((int)rSource.left,0);
	rSource.right = min((int)rSource.right,N_HIGHRES);

	if (bJitterPatch) {if ((rSource.left % 16 ==0)&&(rSource.left>0)) {rSource.left--;rSource.right--;}}

	aaSource[0].left = rSource.left;
	aaSource[0].right = (rSource.right >= rSource.left) ? rSource.right : N_HIGHRES;
	aaSource[0].bottom = rSource.bottom;
	aaSource[0].top = (rSource.bottom >= rSource.top) ? rSource.top : 0;

	fLonSpan_deg = view.Width();
	fLatSpan_deg = view.Height();
	if (fLonSpan_deg < 0) {fLonSpan_deg += 360.0f;}
	if (fLatSpan_deg < 0) {fLatSpan_deg += 360.0f;}
	fLatScale = (float)anHeight/fLatSpan_deg;
	fLonScale = (float)anWidth/fLonSpan_deg;
	fViewTopOffset = (view.top - mrTheaterView.top)*fLatScale;
	fViewLeftOffset = (view.left - mrTheaterView.left)*fLonScale;

	for(n=0;n<1;n++) {
		aaDest[n].top = (int)(fViewTopOffset + (float)aaSource[n].top*RESHIGH_DEG*fLatScale);
		aaDest[n].bottom = (int)(fViewTopOffset + (float)aaSource[n].bottom*RESHIGH_DEG*fLatScale);
		fUnwrapped = (float)aaSource[n].left*RESHIGH_DEG;

		aaDest[n].left = (int)(fUnwrapped*fLonScale - fViewLeftOffset);
		if (bJitterPatch) {if (aaDest[n].left<0) aaDest[n].left = 0;}
		fUnwrapped = (float)aaSource[n].right*RESHIGH_DEG;

		aaDest[n].right = (int)(fUnwrapped*fLonScale - fViewLeftOffset);
	}
    return 1;
#endif
}


size_t tcMapData::GetHighResRowCount() const
{
    return M_HIGHRES;
}

size_t tcMapData::GetHighResColCount() const
{
    return N_HIGHRES;
}

int tcMapData::GetLowResDecimation() const
{
    return lowResDecimation;
}

int tcMapData:: GetMedResDecimation() const
{
    return medResDecimation;
}

int tcMapData::GetHighResDecimation() const
{
    return highResDecimation;
}

bool tcMapData::IsTheaterDecimationValid(int dec) const
{
    return (dec == highResDecimation) || (dec == medResDecimation) || (dec == lowResDecimation);
}

/**
*
*/
void tcMapData::CreatePalettes() 
{
	unsigned int nRed,nGreen,nBlue;

	unsigned int alpha_val = 0xFF000000;

	for (int k=0; k<40; k++) 
	{
		nRed = 10;
		nGreen = 10;
		nBlue = 50;
        maPalette1[k] = alpha_val + nBlue + (nGreen << 8) + (nRed << 16);
	}
	for (int k=40; k<80; k++) 
	{
		nRed = 10;
		nGreen = 10;
		nBlue = 50 + (k-40);
        maPalette1[k] = alpha_val + nBlue + (nGreen << 8) + (nRed << 16);
	}
    for (int k=80; k<100; k++) 
	{
		nRed = 10 + 1*(k-80)/2;
		nGreen = 10 + 1*(k-80);
		nBlue = 90 + (k-80)/2;
        maPalette1[k] = alpha_val + nBlue + (nGreen << 8) + (nRed << 16);
	}
	for (int k=100; k<200; k++) 
	{
		nRed =(k-100) + 80;
		nGreen =(k-100) + 80;
		nBlue = ((k-100)*8/10) + 60;

		nRed =  min((unsigned int)255, nRed);
		nGreen =  min((unsigned int)255, nGreen);
		nBlue =  min((unsigned int)255, nBlue);

        maPalette1[k] = alpha_val + nBlue + (nGreen << 8) + (nRed << 16);
	}
	for (int k=200; k<1024; k++) 
	{
		nRed = ((k-200)/2) + 180;
		nGreen = ((k-200)/2) + 180;
		nBlue = ((k-200)*4/10) + 140;

		nRed =  min((unsigned int)255, nRed);
		nGreen =  min((unsigned int)255, nGreen);
		nBlue =  min((unsigned int)255, nBlue);

        maPalette1[k] = alpha_val + nBlue + (nGreen << 8) + (nRed << 16);
	}

}

bool tcMapData::GetFarthestClearPoint(float lon1_rad, float lat1_rad, float lon2_rad, float lat2_rad, float maxTerrain_m,
        double& lon_rad, double& lat_rad)
{
    float lonb_rad;
    float latb_rad;

    bool result = GetFarthestClearPoint(lon1_rad, lat1_rad, lon2_rad, lat2_rad, maxTerrain_m, lonb_rad, latb_rad);
    lon_rad = (double)lonb_rad;
    lat_rad = (double)latb_rad;
    return result;
}

/**
* Get farthest point (lon,lat) along path from (lon1,lat1) to (lon2,lat2) such that path up to point has
* terrain less than maxTerrain_m at all points up to (lon,lat).
* Used for path finding
* @return true if clear along entire path
*/
bool tcMapData::GetFarthestClearPoint(float lon1_rad, float lat1_rad, float lon2_rad, float lat2_rad, float maxTerrain_m,
        float& lon_rad, float& lat_rad)
{
    GeoPoint p1(lon1_rad, lat1_rad, 0);
    GeoPoint p2(lon2_rad, lat2_rad, 0);

    //float heading_rad = nsNav::GCHeadingApprox_rad(p1, p2);
    float dist_km = C_RADTOKM * nsNav::GCDistanceApprox_rad(p1, p2);

    size_t nSteps = size_t(ceilf(0.5f * dist_km));
    if (nSteps == 0)
    {
        lon_rad = lon2_rad;
        lat_rad = lat2_rad;
        return false;
    }
    
    float inv_nsteps = 1.0f / float(nSteps);

    float dlon_rad = lon2_rad - lon1_rad;
    if (dlon_rad > C_PI) dlon_rad -= C_TWOPI;
    if (dlon_rad < -C_PI) dlon_rad += C_TWOPI;
 
    float dlat_rad = lat2_rad - lat1_rad;


    float dlonCoarse_rad = dlon_rad * inv_nsteps;   
    float dlatCoarse_rad = dlat_rad * inv_nsteps;

    float dlonFine_rad = 0.125f * dlonCoarse_rad;
    float dlatFine_rad = 0.125f * dlatCoarse_rad;

    lon_rad = lon1_rad;
    lat_rad = lat1_rad;
    float lonTest_rad = lon_rad;
    float latTest_rad = lat_rad;

    float lonStep_rad = dlonFine_rad;
    float latStep_rad = dlatFine_rad;

    bool searching = true;
    unsigned int iterations = 0;
    while (searching && (iterations++ < 100000))
    {
        float terrain_m = GetTerrainHeightHighRes(C_180OVERPI*lonTest_rad, C_180OVERPI*latTest_rad);

        if (terrain_m < maxTerrain_m)
        {
            lon_rad = lonTest_rad;
            lat_rad = latTest_rad;
        }
        else
        {
            return false;
        }

        // set adaptive step size
        if (terrain_m < (maxTerrain_m - 15.0f))
        {
            lonStep_rad = dlonCoarse_rad;
            latStep_rad = dlatCoarse_rad;
        }
        else
        {
            lonStep_rad = dlonFine_rad;
            latStep_rad = dlatFine_rad;
        }

        lonTest_rad = lon_rad + lonStep_rad;
        latTest_rad = lat_rad + latStep_rad;

        if (lonStep_rad >= 0)
        {
            lonTest_rad = std::min(lonTest_rad, lon2_rad);
        }
        else
        {
            lonTest_rad = std::max(lonTest_rad, lon2_rad);
        }

        if (latStep_rad >= 0)
        {
            latTest_rad = std::min(latTest_rad, lat2_rad);
        }
        else
        {
            latTest_rad = std::max(latTest_rad, lat2_rad);
        }


        searching = (lon_rad != lon2_rad) && (lat_rad != lat2_rad);

    }

    // entire path is clear
    return true;
}


/**
* Darkens areas of low-res map image for which 10 x 10 DEM
* tiles are unavailable
* @param image pointer to low res image data, dimensions
* @param image must be M_LOWRES x N_LOWRES x UINT32 for this to be
* @param safe. Assumes image is locked
*/
void tcMapData::DarkenLowResUnavailable(boost::shared_ptr<tcTexture2D> image)
{
    // create map image using map data
    CTVTextureFactory* texFactory = tcTVEngine::Get()->GetTextureFactory();
    long id = image->GetId();


	int M, N;
	UINT32 nAlphaOffset = 0xFE000000;
	M = M_LOWRES;
	N = N_LOWRES;
	int lowResScale = int(SCALE_LOWRES);
    int lowResDemTileWidth = demTileReader->GetTileWidth(tcDemTileReader::HIGH_RES) / K_DEC_LOWRES;
	int lowResDemTileHeight = demTileReader->GetTileHeight(tcDemTileReader::HIGH_RES) / K_DEC_LOWRES;


	for (int lat = -80; lat <= 90; lat += 10)
	{
		for (int lon = -180; lon <=170; lon += 10)
		{
			/* if tile is not available, darken corresponding area
			** of low res map
			*/
			if (!demTileReader->IsTileAvailable(lat, lon, tcDemTileReader::HIGH_RES))
			{
				int mstart = (90-lat) * lowResScale;
				int nstart = (180+lon) * lowResScale;
				for (int m = mstart; m < mstart + lowResDemTileHeight; m++)
				{
					for (int n = nstart; n < nstart + lowResDemTileWidth; n++)
					{
						//unsigned long idx = (M-1-m)*N + n;
                        unsigned long imageData = texFactory->GetPixel(id, n, m);

						unsigned long red = ((imageData & 0x000000FF) / 4) 
												& 0x000000FF;
						unsigned long green = ((imageData & 0x0000FF00) / 4) 
							                    & 0x0000FF00;
						unsigned long blue = ((imageData & 0x00FF0000) / 4) 
							                    & 0x00FF0000;
						unsigned long darkened = nAlphaOffset + red + green + blue;

						texFactory->SetPixel(id, n, m, darkened);
					}
				}
			}
            else // draw tile boundary in gray for now
            {
                int mstart = (90-lat) * lowResScale;
				int nstart = (180+lon) * lowResScale;
                
				for (int m = mstart; m < mstart + lowResDemTileHeight; m+=(lowResDemTileHeight-1))
				{
					for (int n = nstart; n < nstart + lowResDemTileWidth; n++)
					{
						//unsigned long idx = (M-1-m)*N + n;

                        unsigned long imageData = texFactory->GetPixel(id, n, m);

						unsigned long color = (imageData & ~0x000000FF) + 0x00000080;

						texFactory->SetPixel(id, n, m, color);
					}
				}

                for (int n = nstart; n < nstart + lowResDemTileWidth; n+=(lowResDemTileWidth-1))
                {
                    for (int m = mstart; m < mstart + lowResDemTileHeight; m++)
                    {
                        //unsigned long idx = (M-1-m)*N + n;

                        unsigned long imageData = texFactory->GetPixel(id, n, m);

						unsigned long color = (imageData & ~0x000000FF) + 0x00000080;

                        texFactory->SetPixel(id, n, m, color);
                    }
                }

            }
		}
		
	}
	
	fprintf(stdout, "tcMapData - Darkened unavailable tiles\n");
}

/********************************************************************/
int tcMapData::LoadLowRes() 
{
	tcFile file;
	int m,nReadCount;

    CreateMapArrayLowRes();


	if (file.Open("maps\\lowres02f2.dat",tcFile::modeRead)==0) 
	{
		WTL("Error - tcMapData - LoadLowRes - failed to open file");
		return false;
	}

	// data stored in row-major order
    size_t idx = 0;
	for(m=0;m<M_LOWRES;m++) 
	{
		nReadCount = file.Read((void*)&maGlobal[idx], N_LOWRES*sizeof(short));
        idx += N_LOWRES;

		if (nReadCount != N_LOWRES*sizeof(short)) 
		{
			WTL("Error - tcMapData - LoadLowRes - bad lowres map file");
			file.Close();
			return false;
		}
	}

	mrWorldView.Set(-C_PI,C_PIM,-C_PIOVER2,C_PIOVER2);

	WTL("tcMapData - LoadLowRes - success");
	file.Close();
	return true;
}
/********************************************************************/
void tcMapData::LabelLowRes() {
	return;
#if 0
	HRESULT hr;
	HDC hdc;
	DDSURFACEDESC ddsd;  
	int nWidth,nHeight;
	// TODO: fix

	ddsd.dwSize = sizeof(DDSURFACEDESC);

	mpDDS_LowRes->GetSurfaceDesc(&ddsd);
	nWidth = ddsd.dwWidth;
	nHeight = ddsd.dwHeight;
	hr = mpDDS_LowRes->GetDC(&hdc);
	if (hr!=DD_OK) {WTL("Error - tcMapData - LabelLowRes - Failed to get DC");return;}     

	HFONT hFontOld = (HFONT)SelectObject(hdc,mhFontCountry);
	SetBkColor(hdc, RGB(0, 0, 0));
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(255, 255, 255));

	tcString sText;   
	sText.Format("UNITED STATES");
	TextOut(hdc,280, 190, sText, sText.GetLength());

	mpDDS_LowRes->ReleaseDC(hdc);
#endif
}
/********************************************************************/
void tcMapData::SetDemInfo() 
{
	for (int i=0;i<16;i++)
	{
		maDemInfo[i].mzFileName = "C:\\PROJECTS\\GLOBE\\DEM\\"; // prepend file path
	}
	maDemInfo[0].mzFileName += "a11g";
	maDemInfo[0].mfLatMin = 50.0f;maDemInfo[0].mfLatMax = 90.0f;
	maDemInfo[0].mfLonMin = -180.0f;maDemInfo[0].mfLonMax = -90.0f;
	maDemInfo[1].mzFileName += "b10g";
	maDemInfo[1].mfLatMin = 50.0f;maDemInfo[1].mfLatMax = 90.0f;
	maDemInfo[1].mfLonMin = -90.0f;maDemInfo[1].mfLonMax = 0;
	maDemInfo[2].mzFileName += "c10g";
	maDemInfo[2].mfLatMin = 50.0f;maDemInfo[2].mfLatMax = 90.0f;
	maDemInfo[2].mfLonMin = 0;maDemInfo[2].mfLonMax = 90.0f;
	maDemInfo[3].mzFileName += "d10g";
	maDemInfo[3].mfLatMin = 50.0f;maDemInfo[3].mfLatMax = 90.0f;
	maDemInfo[3].mfLonMin = 90.0f;maDemInfo[3].mfLonMax = 180.0f;

	maDemInfo[4].mzFileName += "e10g";
	maDemInfo[4].mfLatMin = 0;maDemInfo[4].mfLatMax = 50.0f;
	maDemInfo[4].mfLonMin = -180.0f;maDemInfo[4].mfLonMax = -90.0f;
	maDemInfo[5].mzFileName += "f10g";
	maDemInfo[5].mfLatMin = 0;maDemInfo[5].mfLatMax = 50.0f;
	maDemInfo[5].mfLonMin = -90.0f;maDemInfo[5].mfLonMax = 0;
	maDemInfo[6].mzFileName += "g10g";
	maDemInfo[6].mfLatMin = 0;maDemInfo[6].mfLatMax = 50.0f;
	maDemInfo[6].mfLonMin = 0;maDemInfo[6].mfLonMax = 90.0f;
	maDemInfo[7].mzFileName += "h10g";
	maDemInfo[7].mfLatMin = 0;maDemInfo[7].mfLatMax = 50.0f;
	maDemInfo[7].mfLonMin = 90.0f;maDemInfo[7].mfLonMax = 180.0f;

	maDemInfo[8].mzFileName += "i10g";
	maDemInfo[8].mfLatMin = -50.0f;maDemInfo[8].mfLatMax = 0;
	maDemInfo[8].mfLonMin = -180.0f;maDemInfo[8].mfLonMax = -90.0f;
	maDemInfo[9].mzFileName += "j10g";
	maDemInfo[9].mfLatMin = -50.0f;maDemInfo[9].mfLatMax = 0;
	maDemInfo[9].mfLonMin = -90.0f;maDemInfo[9].mfLonMax = 0;
	maDemInfo[10].mzFileName += "k10g";
	maDemInfo[10].mfLatMin = -50.0f;maDemInfo[10].mfLatMax = 0;
	maDemInfo[10].mfLonMin = 0;maDemInfo[10].mfLonMax = 90.0f;
	maDemInfo[11].mzFileName += "l10g";
	maDemInfo[11].mfLatMin = -50.0f;maDemInfo[11].mfLatMax = 0;
	maDemInfo[11].mfLonMin = 90.0f;maDemInfo[11].mfLonMax = 180.0f;

	maDemInfo[12].mzFileName += "m10g";
	maDemInfo[12].mfLatMin = -90.0f;maDemInfo[12].mfLatMax = -50.0f;
	maDemInfo[12].mfLonMin = -180.0f;maDemInfo[12].mfLonMax = -90.0f;
	maDemInfo[13].mzFileName += "n10g";
	maDemInfo[13].mfLatMin = -90.0f;maDemInfo[13].mfLatMax = -50.0f;
	maDemInfo[13].mfLonMin = -90.0f;maDemInfo[13].mfLonMax = 0;
	maDemInfo[14].mzFileName += "o10g";
	maDemInfo[14].mfLatMin = -90.0f;maDemInfo[14].mfLatMax = -50.0f;
	maDemInfo[14].mfLonMin = 0;maDemInfo[14].mfLonMax = 90.0f;
	maDemInfo[15].mzFileName += "p10g";
	maDemInfo[15].mfLatMin = -90.0f;maDemInfo[15].mfLatMax = -50.0f;
	maDemInfo[15].mfLonMin = 90.0f;maDemInfo[15].mfLonMax = 180.0f;
}

/**
* Added for tcGameSerializer
*/
void tcMapData::SetTheaterDecimation(int val)
{
    theaterDecimation = val;
}

/**
* Fills regions with invalid tcFile data with 0x8181
*/
void tcMapData::FillInvalidHighResData(size_t M, size_t N, size_t mstart, size_t nstart,
									   tcFile *pMain, tcFile *pEast, tcFile *pSouth, tcFile *pSouthEast)
{
	size_t m, msource, neast;

	bool fillMain = !pMain->IsOpen();
	bool fillEast = !pEast->IsOpen();
	bool fillSouth = !pSouth->IsOpen();
	bool fillSouthEast = !pSouthEast->IsOpen();

	/**** PASS 1 (western files) ****/
	msource = mstart; // row index for source data
	m = 0; // row index for dest data
    size_t idx = 0;
	while (m < M_HIGHRES)
	{
		if ((msource < M) && fillMain)
		{
			if ((nstart+N_HIGHRES) <= N) 
			{
				memset((void*)&maTheater[idx], 0x81, N_HIGHRES*sizeof(short));
			}
			else 
			{
				memset((void*)&maTheater[idx], 0x81, (N-nstart)*sizeof(short));
			}
		}
		else if ((msource >= M) && fillSouth)
		{
			if ((nstart+N_HIGHRES) <= N) 
			{
				memset((void*)&maTheater[idx], 0x81, N_HIGHRES*sizeof(short));
			}
			else 
			{
				memset((void*)&maTheater[idx], 0x81, (N-nstart)*sizeof(short));
			}
		}
		m = m + 1;
		msource = msource + 1;
        idx += N_HIGHRES;
	}            

	/**** PASS 2 (eastern files) ****/
	msource = mstart; // row index for source data
	m = 0; // row index for dest data
    idx = 0;
	while (m < M_HIGHRES) 
	{
		if ((msource < M)  && fillEast)
		{
			if ((nstart+N_HIGHRES) <= N) 
			{
			}
			else
			{
				neast = N_HIGHRES - (N-nstart);
				memset((void*)&maTheater[idx+N-nstart], 0x81, neast*sizeof(short));
			}

		}
		else if ((msource >= M) && fillSouthEast)
		{
			if ((nstart+N_HIGHRES) <= N)
			{
				neast = 0;
			}
			else 
			{
				neast = N_HIGHRES - (N-nstart);
				memset((void*)&maTheater[idx+N-nstart], 0x81, neast*sizeof(short));
			}
		}
		m = m + 1;
		msource = msource + 1;
        idx += N_HIGHRES;
	}            
}

/**
* More general version written to support case where maTheater spans more than 2 tiles across
* @param M_tile number of rows in tile
* @param N_tile number of cols in tile
* @param mSource row offset for source data
* @param nSource col offset for source data
* @param mDest row offset for dest data
* @param nDest col offset for dest data
*/
int tcMapData::ReadHighResDataChunk(tcFile* tile, 
                                    int M_tile, int N_tile, 
                                    int mSource, int nSource, 
                                    int mDest, int nDest)
{
    // read as much as possible from source tile, limited by size of destination
    int source_rows = M_tile - mSource;
    int source_cols = N_tile - nSource;
    int dest_rows = M_HIGHRES - mDest;
    int dest_cols = N_HIGHRES - nDest;

    int read_rows = std::min(source_rows, dest_rows);
    int read_cols = std::min(source_cols, dest_cols);

    if ((read_rows <= 0) || (read_cols <= 0))
    {
        wxASSERT(read_rows > 0);
        wxASSERT(read_cols > 0);
        return false;
    }

    short* pMap = maTheater;
    int dest_idx = mDest*N_HIGHRES + nDest; // idx of first row, first col of dest

	tile->Seek((mSource*N_tile + nSource)*sizeof(short), tcFile::current); // seek to first row, first col of src

    for (int row=0; row<read_rows; row++)
    {
		tile->Read((void*)(pMap + dest_idx), read_cols*sizeof(short)); 

        dest_idx += N_HIGHRES; // advance to next row of dest

		tile->Seek((N_tile-read_cols)*sizeof(short), tcFile::current); // advance to next row of source
    }
         
	return true;
}

/**
* Call this to fill map data with default for missile tile case
*/
int tcMapData::ReadHighResDataChunkNull(int M_tile, int N_tile, 
                                    int mSource, int nSource, 
                                    int mDest, int nDest)
{
    // read as much as possible from source tile, limited by size of destination
    int source_rows = M_tile - mSource;
    int source_cols = N_tile - nSource;
    int dest_rows = M_HIGHRES - mDest;
    int dest_cols = N_HIGHRES - nDest;

    int read_rows = std::min(source_rows, dest_rows);
    int read_cols = std::min(source_cols, dest_cols);

    if ((read_rows <= 0) || (read_cols <= 0))
    {
        //return true; // normal case?? for 2048x2048 map size at max zoom out
        wxASSERT(read_rows > 0);
        wxASSERT(read_cols > 0);
        return false;
    }
   
    short* pMap = maTheater;
    int dest_idx = mDest*N_HIGHRES + nDest; // idx of first row, first col of dest

    for (int row=0; row<read_rows; row++)
    {
        memset((void*)(pMap + dest_idx), 0x81, read_cols*sizeof(short));

        dest_idx += N_HIGHRES; // advance to next row of dest
    }
         
	return true;
}



void tcMapData::CreateDefaultMap(float afStartLat_deg, float afStartLon_deg, 
								 unsigned anWidth, unsigned anHeight) 
{
	float fLat_deg, fLon_deg;
	tcFile fMain;

	if (fMain.Open("maps\\defaultmap.dat",tcFile::modeCreate|tcFile::modeWrite)==0) {
		WTL("Error - tcMapData - CreateDefaultMap - failed to open file");
		return;
	}

	anWidth = anWidth - (anWidth % N_TILE);
	anHeight = anHeight - (anHeight % N_TILE); // so that LoadTile doesn't straddle boundary

	tsDefaultMapInfo sDMI;
	sDMI.mfLat_deg = afStartLat_deg;
	sDMI.mfLon_deg = afStartLon_deg;
	sDMI.mnWidth = anWidth;
	sDMI.mnHeight = anHeight;

	fMain.Write(&sDMI, sizeof(tsDefaultMapInfo));
	for (unsigned m=0;m<anHeight;m++) {
		fLat_deg = afStartLat_deg - (float)m*RESHIGH_DEG;
		for (unsigned n=0;n<anWidth;n++) {
			fLon_deg = afStartLon_deg + (float)n*RESHIGH_DEG;
			float fHeight = GetTerrainHeight(fLon_deg, fLat_deg, -100.0f);
			INT16 nHeight = (INT16)(fHeight);
			fMain.Write(&nHeight,sizeof(nHeight));
		}
		AgeOutTiles(0);
	}

	fMain.Close();
	WTL("Created default map file");
}


/**
* Loads high res data (theater area) specified by northwest corner
* point (startLon_deg, startLat_deg)
* Uses 10 x 10 deg DEM tile system
* @param dec decimation factor, either 1 or 4, other numbers not valid
*
* Updated to handle case where map straddles arbitrary number of tiles
* (used to only handle 2)
*/
void tcMapData::LoadHighResC(float centerLon_deg, float centerLat_deg, int dec)
{
    if ((dec != lowResDecimation) && (dec != medResDecimation) && (dec != highResDecimation))
    {
        fprintf(stderr, "LoadHighResC, invalid decimation factor (%d)\n", dec);
        wxASSERT(false);
        return;
    }

    CreateMapArrayHighRes();

    float startLat_deg = centerLat_deg + 0.5f * (M_HIGHRES * RESHIGH_DEG * float(dec));
    float startLon_deg = centerLon_deg - 0.5f * (N_HIGHRES * RESHIGH_DEG * float(dec));


    scaleHighRes = SCALE_HIGHRES / float(dec);
    theaterDecimation = dec;

	ConformLonLatDeg(startLon_deg, startLat_deg);


	float minLat_deg = -90.0f + M_HIGHRES * RESHIGH_DEG * dec;
	if (startLat_deg < minLat_deg) startLat_deg = minLat_deg;

    wxASSERT(startLat_deg <= 90.0f);
    const float quant_deg = 0.5f;

	// quantize starting position so it's an even number of samples for all resolutions
	float startLatQuant = floorf(startLat_deg / quant_deg);
	float startLonQuant = floorf(startLon_deg / quant_deg);

	startLat_deg = quant_deg * startLatQuant;
	startLon_deg = quant_deg * startLonQuant;

    float stopLat_deg = startLat_deg - (M_HIGHRES-1) * RESHIGH_DEG * dec;
    float stopLon_deg = startLon_deg + (N_HIGHRES-1) * RESHIGH_DEG * dec;
	if (stopLon_deg < -180.0f) stopLon_deg += 360.0f;

	int northLat = 10 * (int)ceilf(startLat_deg * 0.1f);
	int southLat = 10 * (int)ceilf(stopLat_deg * 0.1f);

	int westLon = 10 * (int)floorf(startLon_deg * 0.1f);
    int eastLon = 10 * (int)floorf(stopLon_deg * 0.1f);

    wxASSERT(eastLon >= -180);

    // calculate start offset into tiles
    // increasing lat row is south, increasing lon col is east
    const int tileSizeQuant = 20; // 10 deg tile is 20, 0.5 deg quanta
    int quantRes = 60 / dec; // each 0.5 deg step is 60 pixels on a high res tile, or 15 on a low res

    int lat_offset = ((180 - int(startLatQuant)) % tileSizeQuant) * quantRes;
    int lon_offset = ((int(startLonQuant) + 360) % tileSizeQuant) * quantRes;

	//int lat_offset = ((180 - int(n_lat_tiles)) % 20) * 60; // old code for high res only
	//int lon_offset = ((int(n_lon_tiles) + 360) % 20) * 60;

    int resolution = 0;

    switch (dec)
    {
    case 1: resolution = tcDemTileReader::HIGH_RES; break;
    case 4: resolution = tcDemTileReader::MEDIUM_RES; break;
    case 10: resolution = tcDemTileReader::LOW10_RES; break;
    case 12: resolution = tcDemTileReader::LOW_RES; break;
    default: 
        {
            fprintf(stderr, "Invalid decimation factor (%d)\n", dec);
            wxASSERT(false);
            return;
        }
        break;
    };


	fprintf(stdout, "LoadHighResC - (%.1f x %.1f) -> N (%d) S (%d) W (%d) E(%d)\n",
		startLat_deg, startLon_deg, northLat, southLat, westLon, eastLon);

    int nLatTiles = (northLat - southLat)/10 + 1; // number of tiles in latitude
    
    int dlon = eastLon - westLon;
    if (dlon < 0) dlon += 360;
    int nLonTiles = (dlon/10 + 1);

    int tileHeight = demTileReader->GetTileHeight(resolution);
    int tileWidth = demTileReader->GetTileWidth(resolution);

    wxASSERT((nLatTiles > 0) && (nLonTiles > 0));

    //int rows_to_read = M_HIGHRES;
    //int cols_to_read = N_HIGHRES;

    int mSource = lat_offset;
    int mDest = 0;

    for (int kLat=0; kLat<nLatTiles; kLat++)
    {
        int latTile = northLat - kLat*10;
        int rowsAvailable = tileHeight - mSource;

        int nSource = lon_offset;
        int nDest = 0;

        for (int kLon=0; kLon<nLonTiles; kLon++)
        {
            int lonTile = westLon + kLon*10;
            if (lonTile >= 180) lonTile -= 360;

            int colsAvailable = tileWidth - nSource;

            tcFile tile;
            demTileReader->LoadDemTile(tile, latTile, lonTile, resolution);
            if (tile.IsOpen())
            {
                ReadHighResDataChunk(&tile, tileHeight, tileWidth,
                                    mSource, nSource, mDest, nDest);

                tile.Close();

                // check data read for any zeros (debug only)                   
                //for (unsigned int n=nDest; (n<(nDest+colsAvailable)) && (n < N_HIGHRES); n++)
                //{
                //    unsigned zeroCount = 0;
                //    for (int m=mDest; (m<(mDest+rowsAvailable)) && (m < M_HIGHRES); m++)
                //    {
                //        if (maTheater[m*N_HIGHRES + n] == 0)
                //        {
                //            zeroCount++;
                //        }
                //    }
                //    wxASSERT(zeroCount < rowsAvailable);
                //}
            }
            else
            {
                ReadHighResDataChunkNull(tileHeight, tileWidth,
                                    mSource, nSource, mDest, nDest);
            }

            nSource = 0; // always start at left of tile after first col
            nDest += colsAvailable;
        }

        mSource = 0; // always start at top of tile after first row
        mDest += rowsAvailable;
    }


	mrTheaterView.Set(C_PIOVER180*startLon_deg, C_PIOVER180*stopLon_deg,
		C_PIOVER180*stopLat_deg, C_PIOVER180*startLat_deg);

	theaterViewDeg.Set(startLon_deg, stopLon_deg,
		 stopLat_deg, startLat_deg);

	fprintf(stdout, "tcMapData - LoadHighResC(lon %.1f, lat %.1f) - success\n",
		startLon_deg, startLat_deg);
    
    wxASSERT(mrTheaterView.left >= -C_PI);
    wxASSERT(mrTheaterView.right < C_PI);

}


/**
* Loads high res data (theater area) specified by northwest corner
* point (startLon_deg, startLat_deg)
* Uses newer 10 x 10 deg DEM tile system
* TODO: there is a bug with this where areas near or straddling an untiled area
*       are not loaded correctly. The map shows all black in these cases.
*/
void tcMapData::LoadHighResB(float startLon_deg, float startLat_deg)
{
    wxASSERT(false); // OBSOLETE
    return;

	//ConformLonLatDeg(startLon_deg, startLat_deg);

	//float minLat_deg = -90.0f + M_HIGHRES * RESHIGH_DEG;
	//if (startLat_deg < minLat_deg) startLat_deg = minLat_deg;

	//// truncate to 0.5 deg multiple
	//float n_lat_tiles = floorf(startLat_deg / 0.5f);
	//float n_lon_tiles = floorf(startLon_deg / 0.5f);

	//startLat_deg = 0.5f * n_lat_tiles;
	//startLon_deg = 0.5f * n_lon_tiles;

	//int northLat = 10 * (int)ceilf(startLat_deg / 10.0f);
	//int southLat = northLat - 10;
	//int westLon = 10 * (int)floorf(startLon_deg / 10.0f);
	//int eastLon = westLon + 10;
	//if (eastLon >= 180) eastLon -= 360;

	//int lat_offset = ((180 - int(n_lat_tiles)) % 20) * 60;
	//int lon_offset = ((int(n_lon_tiles) + 360) % 20) * 60;

	//fprintf(stdout, "LoadHighResB - (%.1f x %.1f) -> N (%d) S (%d) W (%d) E(%d)\n",
	//	startLat_deg, startLon_deg, northLat, southLat, westLon, eastLon);

	//// load DEM tile files
	//tcFile tileNW, tileSW, tileNE, tileSE;

	//demTileReader->LoadDemTile(tileNW, northLat, westLon);
	//demTileReader->LoadDemTile(tileSW, southLat, westLon);
	//demTileReader->LoadDemTile(tileNE, northLat, eastLon);
	//demTileReader->LoadDemTile(tileSE, southLat, eastLon);

	//ReadHighResData2(demTileReader->GetTileHeight(), demTileReader->GetTileWidth(), 
	//	lat_offset, lon_offset,
	//	&tileNW, &tileNE, &tileSW, &tileSE);

	//if ((!tileNW.IsOpen()) ||
	//	(!tileSW.IsOpen()) ||
	//	(!tileNE.IsOpen()) ||
	//	(!tileSE.IsOpen()))
	//{
	//	FillInvalidHighResData(demTileReader->GetTileHeight(), 
	//		demTileReader->GetTileWidth(), 
	//		lat_offset, lon_offset,
	//		&tileNW, &tileNE, &tileSW, &tileSE);
	//}


	//tileNW.Close();
	//tileSW.Close();
	//tileNE.Close();
	//tileSE.Close();

	//mrTheaterView.Set(C_PIOVER180*startLon_deg, 
	//	C_PIOVER180*(startLon_deg + RESHIGH_DEG*N_HIGHRES),
	//	C_PIOVER180*(startLat_deg - RESHIGH_DEG*M_HIGHRES), 
	//	C_PIOVER180*(startLat_deg));

	//theaterViewDeg.Set(startLon_deg, 
	//	(startLon_deg + RESHIGH_DEG*N_HIGHRES),
	//	 (startLat_deg - RESHIGH_DEG*M_HIGHRES), 
	//	 startLat_deg);

	//fprintf(stdout, "tcMapData - LoadHighResB(lon %.1f, lat %.1f) - success\n",
	//	startLon_deg, startLat_deg);

}


UINT32 tcMapData::BlackBlueMap(long pval) const
{
	bool subZero = (pval < 0);
	bool missingData = pval == MISSING_DATA_VAL;
	
	
	if (subZero && (!missingData))
	{
		return 0xFF1020BF;
	}
	else if (subZero && missingData)
	{
		return 0xFF000040; // set missing data to red
	}
	else 
	{
		return 0xFF000000;
	}
}

UINT32 tcMapData::CopperBlueMap(long pval) const
{
	if (pval > 1000) pval = 1000;

	if (pval <= 0) 
	{
		if (pval != MISSING_DATA_VAL)
		{
			return 0xFF700000;
		}
		else
		{
			return 0xFF000000;
		}
	}
	else 
	{
		pval = pval/20;
		if (pval > 115) 
		{
			pval = 115;
		}
		//return 0x010102*pval + 0xFF252515;
		return 0x020101*pval + 0x152525FF;
	}
}

UINT32 tcMapData::YellowBlueMap(long pval) const
{
	int nPaletteIndex = (pval/12) + 100;

    int waterAdjust = (pval < 0) ? -1 : 0;
    nPaletteIndex += waterAdjust; // for case where pval is between -12 and 0 

	//if (nPaletteIndex > 247) // TODO bug here that needs fixing, higher values distort on texture
	//{
	//	nPaletteIndex = 247;
	//}
	//else if (nPaletteIndex < 0) 
	//{
	//	nPaletteIndex = 0;
	//}

	if (nPaletteIndex < 0) 
	{
		nPaletteIndex = 0;
	}

	if (pval != MISSING_DATA_VAL)
	{
		return maPalette1[nPaletteIndex];
	}
	else
	{
		return 0x000000FF;
	}
}



void tcMapData::CreateMapArrayHighRes()
{
    CleanupMapArrayHighRes();

    // default decimation values for low, medium, high res maps
    lowResDecimation = 12;
    medResDecimation = 4;
    highResDecimation = 1;

    switch (tcOptions::Get()->mapSize)
    {
    case 0:
        M_HIGHRES = 512;
        N_HIGHRES = 512;
        break;
    case 1:
        M_HIGHRES = 1024;
        N_HIGHRES = 1024;
        break;
    case 2:
        M_HIGHRES = 2048;
        N_HIGHRES = 2048;
        lowResDecimation = 10;
        break;
    case 3:
        M_HIGHRES = 2048;
        N_HIGHRES = 4096;
        lowResDecimation = 10;
        break;
    default:
        fprintf(stderr, "tcMapData::CreateMapArrayHighRes - bad mapSize, using 1024x1024\n");
        M_HIGHRES = 1024;
        N_HIGHRES = 1024;
        break;
    }

    maTheater = new short[M_HIGHRES*N_HIGHRES];

    memset(maTheater, 0, M_HIGHRES*N_HIGHRES*sizeof(short));
}

void tcMapData::CreateMapArrayLowRes()
{
    CleanupMapArrayLowRes();

    maGlobal = new short[M_LOWRES*N_LOWRES];

    memset(maGlobal, 0, M_LOWRES*N_LOWRES*sizeof(short));
}

void tcMapData::CleanupMapArrayHighRes()
{
    if (maTheater != 0)
    {
        delete maTheater;
    }
}

void tcMapData::CleanupMapArrayLowRes()
{
    if (maGlobal != 0)
    {
        delete maGlobal;
    }
}

/**
* Use anMapID = 0 for low res, 1 for high res
*/
void tcMapData::CreateMapImage(int anMode, int anMapID, boost::shared_ptr<tcTexture2D> image)
{
	size_t m,n,M,N;
	long pval;

	if (anMapID==0) 
	{
		M = M_LOWRES;
		N = N_LOWRES;
	}
	else 
	{
		M = M_HIGHRES;
		N = N_HIGHRES;
	}

    bool arrayAllocated = ((anMapID == 0)&&(maGlobal != 0)) || ((anMapID == 1)&&(maTheater != 0));

    if (!image->IsLoaded() || !arrayAllocated) return;

	UINT32 (tcMapData::*MapOperator)(long) const = 0;
	switch (anMode)
	{
	case 0: MapOperator = &tcMapData::CopperBlueMap; break;
	case 1: MapOperator = &tcMapData::YellowBlueMap; break;
	case 2: MapOperator = &tcMapData::BlackBlueMap; break;
	default: 
		wxASSERT(false);
		fprintf(stderr, "tcMapData::CreateMapImage -- bad mode (%d)\n", anMode);
		return;
	}
	


	// create map image using map data
    CTVTextureFactory* texFactory = tcTVEngine::Get()->GetTextureFactory();
    image->Lock();
    long id = image->GetId();

    size_t pixel_idx = 0;
	if (anMapID == 0) // global map
	{		
		for(m=0; m<M; m++) 
		{
			for(n=0; n<N; n++) 
			{
				pval = maGlobal[pixel_idx];

                texFactory->SetPixel(id, n, m, (this->*MapOperator)(pval));

                pixel_idx++;
			}
		}
	}
	else // theater map
	{
		for(m=0; m<M; m++) 
		{
			for(n=0; n<N; n++) 
			{
				pval = maTheater[pixel_idx];

                texFactory->SetPixel(id, n, m, (this->*MapOperator)(pval));

                pixel_idx++;
			}
		}
	}

	// for low res map, darken the unavailable tiles
	if (anMapID == 0) 
	{
		DarkenLowResUnavailable(image);
	}

	//LabelLowRes(); // TODO: add country and geopol labels

    image->Unlock();

	fprintf(stdout, "tcMapData - CreateMapImage - success\n");
}

/*
void tcMapData::CreateDefaultTile(unsigned mtile, unsigned ntile) {
tcFile tilefile;

tsTileData* pTile = LoadTile(mtile, ntile);
if (pTile==NULL) {return;}
tsTileData Tile;

Tile = *pTile;


// smooth tile
for (int m=1;m<M_TILE-1;m++) {
for (int n=1;n<N_TILE-1;n++) {
Tile.maMapData[m][n] = pTile->maMapData[m-1][n-1] + pTile->maMapData[m-1][n] + pTile->maMapData[m-1][n+1];
Tile.maMapData[m][n] += pTile->maMapData[m][n-1] + pTile->maMapData[m][n] + pTile->maMapData[m][n+1];
Tile.maMapData[m][n] += pTile->maMapData[m+1][n-1] + pTile->maMapData[m+1][n] + pTile->maMapData[m+1][n+1];
Tile.maMapData[m][n] /= 9;
}
}   


// adjust tile
for (int n= 50 ;n<60;n++) {
for (int m=25;m<55;m++) {
if (Tile.maMapData[m][n] > 0) {
Tile.maMapData[m][n] /= 50;
}
if (Tile.maMapData[m][n] < 2) {
Tile.maMapData[m][n] =-(3*n);
}
if (n > 58) {
Tile.maMapData[m][n] -= 25;
}
}
}

Tile.maMapData[30][4] = 1500;
Tile.maMapData[30][2] = 1500;
Tile.maMapData[30][55] = 1500;

// add occasional hills
for (int m=1;m<M_TILE-1;m++) {
for (int n=1;n<N_TILE-1;n++) {
if ((rand() % 32)==0) {
Tile.maMapData[m][n] += (rand() % 400);
}

}
}

// smooth tile
for (int m=1;m<M_TILE-1;m++) {
for (int n=1;n<N_TILE-1;n++) {
Tile.maMapData[m][n] += Tile.maMapData[m-1][n-1] + Tile.maMapData[m-1][n] + Tile.maMapData[m-1][n+1];
Tile.maMapData[m][n] += Tile.maMapData[m][n-1]  + Tile.maMapData[m][n+1];
Tile.maMapData[m][n] += Tile.maMapData[m+1][n-1] + Tile.maMapData[m+1][n] + Tile.maMapData[m+1][n+1];
Tile.maMapData[m][n] /= 9;
}
}

// add noise
for (int m=0;m<M_TILE;m++) {
for (int n=0;n<N_TILE;n++) {
Tile.maMapData[m][n] += (rand() % 10) - 5;
}
}

if (tilefile.Open(DEFAULT_TILE_NAME,tcFile::modeCreate|tcFile::modeWrite,NULL)==0) {
WTL("tcMapData::CreateDefaultTile - failed to create default tile");
return;
}
tilefile.Write(Tile.maMapData,M_TILE*N_TILE*sizeof(short));
tilefile.Close();
WTL("tcMapData::CreateDefaultTile - success");

}
*/

/**
* assumes apData is M_HIGHRES x N_HIGHRES UINT32 array
* Why is this used instead of CreateMapImage?
* @see tcMapData::CreateMapImage
*/
void tcMapData::CreateHighResMapImage(int anMode, UINT32 *apData) {
	size_t m,n,M,N;
	long pval;
	UINT32 nAlphaOffset = 0xFF000000;

	M = M_HIGHRES;
	N = N_HIGHRES;

	if (apData == NULL) {return;}

    size_t pixel_idx = 0;

	// create map image using map data
	switch (anMode) 
	{
	case 0:
		for(m=0;m<M;m++) 
		{
			for(n=0;n<N;n++) 
			{
				pval = maTheater[pixel_idx];
				if (pval <= 0) 
				{
					if (pval == MISSING_DATA_VAL)
					{
						pval = 0x000000;
					}
					else
					{
						pval = 0x700000;
					}
				}
				else 
				{
					pval = pval/20;
					if (pval > 115) 
					{
						pval = 115;
					}
					pval = 0x010102*pval + 0x252515;
				}
				apData[(M-1-m)*N + n] = pval + nAlphaOffset;

                pixel_idx++;
			}
		}
		break;
	case 1:
		int nPaletteIndex;
		for(m=0;m<M;m++) 
		{
			for(n=0;n<N;n++) 
			{
				pval = maTheater[pixel_idx];
				nPaletteIndex = (pval/10) + 100;
				if (nPaletteIndex > 1023) {nPaletteIndex = 1023;}
				if (nPaletteIndex < 0) {nPaletteIndex = 0;}
				if (pval == MISSING_DATA_VAL)
				{
					apData[(M-1-m)*N + n] = 0x00000000 + nAlphaOffset;
				}
				else
				{
					pval = maPalette1[nPaletteIndex];
					apData[(M-1-m)*N + n] = pval + nAlphaOffset;
				}
                pixel_idx++;
			}
		}
		break;
	case 2:
		for(m=0;m<M;m++) 
		{
			for(n=0;n<N;n++)
			{
				pval = maTheater[pixel_idx];
				if (pval < 0) 
				{
					if (pval == MISSING_DATA_VAL) // set missing data to red
					{
						apData[(M-1-m)*N + n] = 0x00000040 + nAlphaOffset;
					}
					else
					{
						apData[(M-1-m)*N + n] = 0x00BF2010 + nAlphaOffset;
					}
				}
				else 
				{
					apData[(M-1-m)*N + n] = 0x00000000 + nAlphaOffset;
				}
                pixel_idx++;
			}
		}
		break;
	default:
		break;
	}

	/*
	// draw longitude and latitude points for debug
	for(m=0;m<M;m+=(M/18)) {
	for(n=0;n<N;n+=(N/36)) {
	apWindow->SetPixel(n,m,pval + 0xFE00FF00);
	}
	}
	*/

	WTL("tcMapData - CreateHighResMapImage - success");
}

/**
* Uses the high res map to get the terrain height. This does
* not use the 0.5 x 0.5 tiles and will not load tiles to cache
* map data.
* @see tcMapData::GetTerrainHeight
* @see tcMapData::GetTerrainHeightLowRes
*
* @return terrain height based on high resolution world map
*/
float tcMapData::GetTerrainHeightHighRes(double afLon_deg, double afLat_deg) 
{
	double fm,fn,fmfloor,fnfloor,fmrem,fnrem;

	ConformLonLatDeg(afLon_deg, afLat_deg);

	if (!mrTheaterView.ContainsPoint(C_PIOVER180*afLon_deg, 
		C_PIOVER180*afLat_deg))
	{
		static unsigned errCount = 0;
		if (errCount++ < 16)
		{
			fprintf(stderr, "GetTerrainHeightHighRes - "
				"point out of theater\n");
		}
		return -999.0f;
	}

	double theaterWestLon_deg = theaterViewDeg.left;
	double theaterNorthLat_deg = theaterViewDeg.top;

    double dlon_deg = afLon_deg-theaterWestLon_deg;
    dlon_deg += 360.0*(dlon_deg < 0);

	fm = (theaterNorthLat_deg-afLat_deg)*scaleHighRes;
	fn = dlon_deg * scaleHighRes;
    fmfloor = std::max(floor(fm), 0.0);
	fnfloor = floor(fn);
	fmrem = fm - fmfloor;
	fnrem = fn - fnfloor;

	int m1 = fmfloor;
	int n1 = fnfloor;
	int m2 = (m1+1);

    m1 %= M_HIGHRES; // just in case to avoid out of bounds indices
	m2 %= M_HIGHRES;

	int n2 = (n1+1);
    n1 %= N_HIGHRES;
	n2 %= N_HIGHRES;


    return ((1.0-fmrem)*(1.0-fnrem)*(float)maTheater[m1*N_HIGHRES+n1]) + 
        ((1.0-fmrem)*(fnrem)*    (float)maTheater[m1*N_HIGHRES+n2]) + 
        ((fmrem)*(1.0-fnrem)*    (float)maTheater[m2*N_HIGHRES+n1]) + 
        ((fmrem)*(fnrem)*        (float)maTheater[m2*N_HIGHRES+n2]);
}


/**
* @return terrain height based on low resolution world map
*/
float tcMapData::GetTerrainHeightLowRes(float afLon_deg, float afLat_deg) 
{
	float fm,fn,fmfloor,fnfloor,fmrem,fnrem;
	size_t m1,n1,m2,n2;

	ConformLonLatDeg(afLon_deg, afLat_deg);
	fm = (90.0f-afLat_deg)*SCALE_LOWRES;
	fn = (afLon_deg+180.0f)*SCALE_LOWRES;
	fmfloor = floorf(fm);
	fnfloor = floorf(fn);
	fmrem = fm - fmfloor;
	fnrem = fn - fnfloor;

	m1 = (size_t)fmfloor;
	n1 = (size_t)fnfloor;
	m2 = (m1+1);
	m2 %= M_LOWRES;
	n2 = (n1+1);
	n2 %= N_LOWRES;

	return ((1.0f-fmrem)*(1.0f-fnrem)*(float)maGlobal[m1*N_LOWRES+n1]) + 
		((1.0f-fmrem)*(fnrem)*        (float)maGlobal[m1*N_LOWRES+n2]) + 
		((fmrem)*(1.0f-fnrem)*        (float)maGlobal[m2*N_LOWRES+n1]) + 
		((fmrem)*(fnrem)*             (float)maGlobal[m2*N_LOWRES+n2]);
}

/**
* Gets high resolution terrain height based on 30 arc-sec DEM
* data. If high res data is not available, the low resolution map
* is used instead.
* This will call GetTile which first checks a cache of 0.5 x 0.5 deg
* map "tiles". 
* TODO: consider changing this to use tiles that overlap (1 point border) 
* to simplify the edge case
* @see tcMapData:GetTile
*/
float tcMapData::GetTerrainHeight(double afLon_deg, double afLat_deg, double afStatusTime) 
{
	double fm,fn,fmfloor,fnfloor,fmrem,fnrem;
	float h11=0,h12=0,h21=0,h22=0;
	long m1,n1,m2,n2,mtile,ntile;
	tsTileData *pTile, *pTileE, *pTileS, *pTileSE;
	enum _bcasetype 
	{
		NORMAL,
		EAST_WEST,
		NORTH_SOUTH,
		ALL_FOUR
	} eeBorderCase;

	eeBorderCase = NORMAL;
	ConformLonLatDeg(afLon_deg, afLat_deg);

    if (fabsf(afLat_deg) > 85.0f)
    {
        if (afLat_deg > 0)
        {
            return -3000.0; // artic ocean use -30000
        }
        else 
        {
            return 3000.0f; // south pole use 3000 m elevation
        }
    }

	fm = (90.0-afLat_deg)*SCALE_HIGHRES;
	fn = (afLon_deg+180.0)*SCALE_HIGHRES;

	m1 = long(fm);
	n1 = long(fn);

	fmfloor = double(m1);
	fnfloor = double(n1);

	fmrem = fm - fmfloor;
	fnrem = fn - fnfloor;




	mtile = m1/M_TILE;
	ntile = n1/N_TILE;
	m1 -= mtile*M_TILE;
	n1 -= ntile*N_TILE;
	m2 = (m1+1);
	if (m2==M_TILE) 
	{
		m2=0;
		eeBorderCase = NORTH_SOUTH;
	}
	n2 = (n1+1);
	if (n2==N_TILE) 
	{
		n2=0;
		eeBorderCase = (eeBorderCase==NORMAL) ? EAST_WEST : ALL_FOUR;
	}

	pTile = GetTile(mtile,ntile,afStatusTime);
	if (pTile==NULL) 
	{
		ReportMapDataError(ME_GENERIC);
		return GetTerrainHeightLowRes(afLon_deg, afLat_deg);
	}
	if (eeBorderCase != NORMAL) 
	{
		h11 = (float)pTile->maMapData[m1][n1];
		if (eeBorderCase == NORTH_SOUTH) 
		{
			pTileS = GetTile(mtile+1,ntile,afStatusTime);
			if (pTileS == NULL) 
			{
				ReportMapDataError(ME_GENERIC);
				return GetTerrainHeightLowRes(afLon_deg, afLat_deg);
			}
			h12 = (float)pTile->maMapData[m1][n2];
			h21 = (float)pTileS->maMapData[m2][n1];
			h22 = (float)pTileS->maMapData[m2][n2];
		}
		if (eeBorderCase == EAST_WEST) 
		{
			pTileE = GetTile(mtile,ntile+1,afStatusTime);
			if (pTileE == NULL) 
			{
				ReportMapDataError(ME_GENERIC);
				return GetTerrainHeightLowRes(afLon_deg, afLat_deg);
			}
			h12 = (float)pTileE->maMapData[m1][n2];
			h21 = (float)pTile->maMapData[m2][n1];
			h22 = (float)pTileE->maMapData[m2][n2];
		}
		if (eeBorderCase == ALL_FOUR) 
		{
			pTileSE = GetTile(mtile+1,ntile+1,afStatusTime);
			if (pTileSE == NULL) 
			{
				ReportMapDataError(ME_GENERIC);
				return GetTerrainHeightLowRes(afLon_deg, afLat_deg);
			}
			pTileS = GetTile(mtile+1,ntile,afStatusTime);
			if (pTileS == NULL) 
			{
				ReportMapDataError(ME_GENERIC);
				return GetTerrainHeightLowRes(afLon_deg, afLat_deg);
			}
			pTileE = GetTile(mtile,ntile+1,afStatusTime);
			if (pTileE == NULL)
			{
				ReportMapDataError(ME_GENERIC);
				return GetTerrainHeightLowRes(afLon_deg, afLat_deg);
			}
			h12 = (float)pTileE->maMapData[m1][n2];
			h21 = (float)pTileS->maMapData[m2][n1];
			h22 = (float)pTileSE->maMapData[m2][n2];
		}
	}
	else 
	{
		h11 = (float)pTile->maMapData[m1][n1];
		h12 = (float)pTile->maMapData[m1][n2];
		h21 = (float)pTile->maMapData[m2][n1];
		h22 = (float)pTile->maMapData[m2][n2];
	}

	//tcString s;
	//s.Format("h11:%f h12:%f h21:%f h22:%f",h11,h12,h21,h22);
	//WTL(s.GetBuffer());

	float fHeight = ((1.0-fmrem)*(1.0-fnrem)*h11) + 
		((1.0-fmrem)*(fnrem)*h12) + 
		((fmrem)*(1.0-fnrem)*h21) + 
		((fmrem)*(fnrem)*h22);
	//if (fHeight > -20.0f) {fHeight += 20.0f*sinf(100.0f*fnrem);} // test roughness function?

	if (fHeight == 0)
	{
		ReportMapDataError(ME_GENERIC);
	}
	return fHeight;
}

void tcMapData::GetTheaterData(short*& rpData, unsigned& anM, unsigned& anN) 
{
    rpData = maTheater;
    anM = M_HIGHRES;
    anN = N_HIGHRES;
}

int tcMapData::GetTheaterDecimation() const
{
    return theaterDecimation;
}

float tcMapData::GetTheaterHeightDeg() const
{
	return RESHIGH_DEG * M_HIGHRES;
}

float tcMapData::GetTheaterWidthDeg() const
{
	return RESHIGH_DEG * N_HIGHRES;
}


/********************************************************************/
tsTileData* tcMapData::GetTile(unsigned mtile, unsigned ntile, double afStatusTime) 
{
	unsigned short nTileIndex;
	tsTileData *pTileData;

	if ((mtile >= M_TILE_LOOKUP)||(ntile >= N_TILE_LOOKUP)) 
	{
		return NULL;
	}

	nTileIndex = maTileLookup[mtile][ntile];
	if (nTileIndex == NULL_TILE) 
	{
		pTileData = LoadTileB(mtile,ntile);
	}
	else 
	{
		pTileData = &maTile[nTileIndex];
	}
	if (pTileData != NULL) 
	{
		pTileData->mfLastAccessTime = afStatusTime;
	}

	return pTileData;
}

unsigned short tcMapData::GetTilesUsedCount() const
{
    return mnTilesUsed;
}

/********************************************************************/
void tcMapData::AgeOutTiles(double afStatusTime) 
{
	if (mnTilesUsed < (MAX_TILES - 70)) 
    {
		return; // leave the stale tiles if underutilized
	}
	for(int k=0;k<MAX_TILES;k++) 
    {
		if (maTile[k].mbActive) 
        {
			if ((afStatusTime-maTile[k].mfLastAccessTime) >= TILE_AGEOUT) 
            {
				maAvailableTiles[mnReturnIndex++] = k;
				if (mnReturnIndex>=MAX_TILES) {mnReturnIndex=0;}
				maTile[k].mbActive = 0;
				maTileLookup[maTile[k].m_lat][maTile[k].n_lon] = NULL_TILE;
				mnTilesUsed--;
				tcString s;
				s.Format("Returned tile %d (%d tiles in use)",k,mnTilesUsed);
				WTL(s.GetBuffer());
			}
		}
	}
}
/********************************************************************/
void tcMapData::InitTiles() 
{
	unsigned int m,n,k;

	for(m=0;m<M_TILE_LOOKUP;m++) 
	{
		for(n=0;n<N_TILE_LOOKUP;n++) 
		{
			maTileLookup[m][n] = NULL_TILE;
		}
	}
	for(k=0;k<MAX_TILES;k++) 
	{
		maTile[k].m_lat = 0;
		maTile[k].n_lon = 0;
		maTile[k].mbActive = 0;
		maTile[k].mfLastAccessTime = 0;
		maAvailableTiles[k] = k;
	}
	mnCheckoutIndex = 0;
	mnReturnIndex = 0;
	mnTilesUsed = 0;
}


/**
* Loads 0.5 x 0.5 deg (default) tile from larger DEM tiles
* DEPRECATED, use LoadTileB
* @return populated tsTileData* or NULL if missing DEM data
* @see tcMapData::LoadTileB
*/
tsTileData* tcMapData::LoadTile(unsigned mtile, unsigned ntile) 
{
	int nMainTile=-1;
	int bFound=0;
	int k,M,N;   
	int m,mstart,nstart,msource;
	tcFile fMain;
	float fStartLat_deg, fStartLon_deg;
	unsigned int nNewIndex;

	wxASSERT(false); // deprecated

	fStartLat_deg = 90.0f - (float)mtile*SCALE_LOOKUP;
	fStartLon_deg = (float)ntile*SCALE_LOOKUP - 180.0f;

	for (k=0;(k<N_DEMFILES)&&(!bFound);k++) 
	{
		if ((fStartLat_deg > maDemInfo[k].mfLatMin)&&
			(fStartLat_deg <= maDemInfo[k].mfLatMax)&&
			(fStartLon_deg >= maDemInfo[k].mfLonMin)&&
			(fStartLon_deg < maDemInfo[k].mfLonMax)) 
		{
			nMainTile = k;
			bFound = 1;
		}
	}
	if (!bFound) {return NULL;}

	/*
	if (!mbUseDefaultMap) 
	{
	if (fMain.Open(maDemInfo[nMainTile].mzFileName,tcFile::modeRead)==0) 
	{
	static bool bReported = false;
	if (!bReported) {
	WTL("Using default map data");
	bReported = true;
	}
	mbUseDefaultMap = true;
	}
	}
	*/

	// checkout new tile
	if (mnTilesUsed >= MAX_TILES) {return NULL;}
	nNewIndex = maAvailableTiles[mnCheckoutIndex++];
	if (mnCheckoutIndex>=MAX_TILES) {mnCheckoutIndex = 0;}
	maTileLookup[mtile][ntile] = nNewIndex;
	mnTilesUsed++;
	tsTileData *pTileData = &maTile[nNewIndex];
	pTileData->m_lat = mtile;
	pTileData->n_lon = ntile;
	pTileData->mbActive = 1;
	// end checkout new tile

	// default map feature
	/*
	tsDefaultMapInfo sDMI;
	if (mbUseDefaultMap) {
	static bool bReported = false;

	if (fMain.Open("maps\\defaultmap.dat",tcFile::modeRead)==0) {
	if (!bReported) {
	WTLC("Error - missing default map file (defaultmap.dat)");
	bReported = true;
	}
	return NULL;
	}
	fMain.Read(&sDMI,sizeof(sDMI));
	mstart = (int)floorf((sDMI.mfLat_deg - fStartLat_deg)*SCALE_HIGHRES);
	nstart = (int)floorf((fStartLon_deg - sDMI.mfLon_deg)*SCALE_HIGHRES);
	M = sDMI.mnHeight;
	N = sDMI.mnWidth;
	}
	else { // normal world map operation
	*/
	mstart = (int)floorf((maDemInfo[nMainTile].mfLatMax - fStartLat_deg)*SCALE_HIGHRES);
	nstart = (int)floorf((fStartLon_deg - maDemInfo[nMainTile].mfLonMin)*SCALE_HIGHRES);
	M = (int)((maDemInfo[k].mfLatMax - maDemInfo[k].mfLatMin)*SCALE_HIGHRES);
	N = (int)((maDemInfo[k].mfLonMax - maDemInfo[k].mfLonMin)*SCALE_HIGHRES);
	//}

	if ((mstart >= M)||(nstart >= N)) {
		memset(pTileData->maMapData,0,M_TILE*N_TILE*sizeof(short));
		tcString s;
		s.Format("tcMapData - LoadTile (lon %.1f,lat %.1f) (m %d n %d) idx:%d - out of bounds tile",
			fStartLon_deg,fStartLat_deg,mtile,ntile,nNewIndex);
		WTL(s.GetBuffer());
		return pTileData;
	}

	fMain.Seek(mstart*N*sizeof(short),tcFile::current); // seek to first row of data, main tile

	msource = mstart; // row index for source data
	m = 0; // row index for dest data
	while (m < M_TILE) {
		if (msource < M) {
			fMain.Seek(nstart*sizeof(short),tcFile::current); // seek to first column of data
			if ((nstart+N_TILE)<=N) {
				fMain.Read((void*)pTileData->maMapData[m],N_TILE*sizeof(short)); 
				fMain.Seek((N-N_TILE-nstart)*sizeof(short),tcFile::current); // seek to first column of data
			}
			else {
				ME(ME_TILE_STRUCTURE)
			}
		}
		else {
			ME(ME_TILE_STRUCTURE)
		}
		m = m + 1;
		msource = msource + 1;
	}
	fMain.Close();

	//tcString s;
	//s.Format("tcMapData - LoadTile (lon %.1f,lat %.1f) (m %d n %d) idx:%d - success",
	//	fStartLon_deg,fStartLat_deg,mtile,ntile,nNewIndex);
	//WTL(s.GetBuffer());

	if ((pTileData->maMapData[0][0] == 0)&&(pTileData->maMapData[10][10]==0)) 
	{
		WTLC("Error: bad tile data");
	}

	return pTileData;
}

/**
* Loads 0.5 x 0.5 deg (default) tile from 10 x 10 DEM tiles
* This is the newer version that uses smaller DEM tiles to allow
* the user to play without downloading the full earth map data.
*
* If 10 x 10 DEM tile is not available, use the low resolution
* world map to create the 0.5 x 0.5 deg tile.
*
* @return populated tsTileData* or NULL if missing DEM data
*/
tsTileData* tcMapData::LoadTileB(unsigned mtile, unsigned ntile) 
{
	static int errorReports = 0;
	tcFile demTile;

	int lat_val = 90 - 10 * (mtile / 20);
	int lon_val = -180 + 10 * (ntile / 20);
	int lat_offset = (mtile % 20) * M_TILE; // offsets into DEM tile for this tile
	int lon_offset = (ntile % 20) * N_TILE; 

	wxASSERT(lat_val > -90);
	wxASSERT(lat_val <= 90);
	wxASSERT(lon_val >= -180);
	wxASSERT(lon_val < 180);

	float fStartLat_deg = 90.0f - (float)mtile*SCALE_LOOKUP;
	float fStartLon_deg = (float)ntile*SCALE_LOOKUP - 180.0f;

    int tileResolution = tcDemTileReader::HIGH_RES;
    int tileWidth = demTileReader->GetTileWidth(tileResolution);
    int tileHeight = demTileReader->GetTileHeight(tileResolution);


	if (!demTileReader->IsTileAvailable(lat_val, lon_val, tileResolution))
	{
		return LoadTileFromLowRes(mtile, ntile);
	}

	demTileReader->LoadDemTile(demTile, lat_val, lon_val, tileResolution);
	if (!demTile.IsOpen())
	{
		fprintf(stderr, "Error - LoadTileB - "
			"Could not open available file.\n");
		return NULL;
	}

	// checkout new tile, TODO modularize this
	if (mnTilesUsed >= MAX_TILES) 
    {
        wxASSERT(false);
        fprintf(stderr, "tcMapData::LoadTileB - out of tiles\n");
        return 0;
    }

	unsigned int nNewIndex = maAvailableTiles[mnCheckoutIndex++];
	if (mnCheckoutIndex >= MAX_TILES) {mnCheckoutIndex = 0;}
	maTileLookup[mtile][ntile] = nNewIndex;
	mnTilesUsed++;
	tsTileData* pTileData = &maTile[nNewIndex];
	pTileData->m_lat = mtile;
	pTileData->n_lon = ntile;
	pTileData->mbActive = 1;
	// end checkout new tile

	// copy appropriate section of 10 x 10 DEM tile to 0.5 x 0.5 tsTileData

	if ((lat_offset >= tileHeight) || (lon_offset >= tileWidth)) 
	{
		memset(pTileData->maMapData, 0, M_TILE*N_TILE*sizeof(short));
		tcString s;
		s.Format("tcMapData - LoadTile (lon %.1f,lat %.1f) (m %d n %d) "
			"idx:%d - out of bounds tile",
			fStartLon_deg, fStartLat_deg, mtile, ntile, nNewIndex);
		fprintf(stderr,"%s\n", s.GetBuffer());
		return pTileData;
	}


	// seek to first row of data in DEM tile
	demTile.Seek(lat_offset * tileWidth * sizeof(short), tcFile::current); 

	if ((lon_offset + N_TILE) > tileWidth) 
	{
		ME(ME_TILE_STRUCTURE)
	}

	int m_src = lat_offset; // row index for source data
	int m_dest = 0; // row index for destination data

	int pre_read_offset = lon_offset * sizeof(short);
	int read_count = N_TILE*sizeof(short);
	int post_read_offset = (tileWidth-N_TILE-lon_offset)*sizeof(short);

	while (m_dest < M_TILE) 
	{
		if (m_src < tileHeight)
		{
			// seek to first column of data
			demTile.Seek(pre_read_offset, tcFile::current); 

			demTile.Read((void*)pTileData->maMapData[m_dest], read_count); 

			// seek to first column of next row of data
			demTile.Seek(post_read_offset, tcFile::current); 
		}
		else 
		{
			ME(ME_TILE_STRUCTURE)
		}
		m_src++;
		m_dest++;
	}
	demTile.Close();

	//tcString s;
	//s.Format("tcMapData - LoadTile (lon %.1f,lat %.1f) (m %d n %d) idx:%d - success",
	//	fStartLon_deg, fStartLat_deg, mtile, ntile, nNewIndex);
	//WTL(s.GetBuffer());

	if ((pTileData->maMapData[0][0] == 0)&&(pTileData->maMapData[10][10]==0)) 
	{
		WTLC("Error: bad tile data");
	}

	return pTileData;
}

/**
* Uses the low resolution world map to create 
* the 0.5 x 0.5 deg tile. Normally used when a 10 x 10 DEM
* tile is not available.
*/
tsTileData* tcMapData::LoadTileFromLowRes(unsigned mtile, unsigned ntile)
{
	// checkout new tile, TODO modularize this
	if (mnTilesUsed >= MAX_TILES) {return 0;}
	unsigned int nNewIndex = maAvailableTiles[mnCheckoutIndex++];
	if (mnCheckoutIndex >= MAX_TILES) {mnCheckoutIndex = 0;}
	maTileLookup[mtile][ntile] = nNewIndex;
	mnTilesUsed++;
	tsTileData* pTileData = &maTile[nNewIndex];
	pTileData->m_lat = mtile;
	pTileData->n_lon = ntile;
	pTileData->mbActive = 1;
	// end checkout new tile

	float fStartLat_deg = 90.0f - (float)mtile * SCALE_LOOKUP;
	float fStartLon_deg = (float)ntile * SCALE_LOOKUP - 180.0f;
	float lat_deg = fStartLat_deg;

	for(int lat_idx = 0; lat_idx < M_TILE; lat_idx++)
	{
		float lon_deg = fStartLon_deg;
		for(int lon_idx = 0; lon_idx < N_TILE; lon_idx++)
		{
			float height_m = GetTerrainHeightLowRes(lon_deg, lat_deg);
			pTileData->maMapData[lat_idx][lon_idx] = short(height_m);
			lon_deg += RESHIGH_DEG;
			if (lon_deg >= 180.0f) lon_deg -= 360.0f;
		}
		lat_deg -= RESHIGH_DEG;
	}

	wxString s = wxString::Format("tcMapData - LoadTileFromLowRes "
		"(lon %.1f,lat %.1f) (m %d n %d) idx:%d - success",
		fStartLon_deg, fStartLat_deg, mtile, ntile, nNewIndex);
	fprintf(stdout, "%s\n", s.GetData());

	return pTileData;
}

/********************************************************************/
void tcMapData::ReportMapDataError(UINT32 anError) 
{

	switch (anError) 
	{
	case ME_TILE_STRUCTURE:
		{
			static bool bReported = false;
			if (!bReported) 
			{
				fprintf(stderr, "MapData error: bad tile structure");
				bReported = true;
			}
		}
		break;
	case ME_GENERIC:
	default:
		{
			static bool bReported = false;
			if (!bReported) 
			{
				fprintf(stderr, "MapData error: generic");
				bReported = true;
			}
		}
		break;
	}
}

/********************************************************************/
tcMapData::tcMapData() 
: scaleHighRes(0),
  theaterDecimation(0),
  maGlobal(0),
  maTheater(0),
  M_HIGHRES(1024),
  N_HIGHRES(2048),
  lowResDecimation(12),
  medResDecimation(4),
  highResDecimation(1)
{
	demTileReader = new tcDemTileReader();
	//    mbUseDefaultMap = false;
	SetDemInfo();
	CreatePalettes();

#if 0
	mhFontDefault = CreateFont(30,0,0,0,FW_NORMAL,FALSE,FALSE,FALSE,
		ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
		DEFAULT_PITCH|FF_MODERN,"Arial");
	if (mhFontDefault == NULL) 
	{
		WTL("mhFontDefault creation failed\n");
	}

	mhFontCountry = CreateFont(12,0,0,0,FW_BOLD,TRUE,FALSE,FALSE,
		ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,PROOF_QUALITY,
		DEFAULT_PITCH|FF_MODERN,"Arial");
	if (mhFontCountry == NULL) 
	{
		WTL("mhFontCountry creation failed\n");
	}

	mhPenBox = CreatePen(PS_SOLID,1,RGB(255,255,255));
	if (mhPenBox == NULL) 
	{
		WTL("mhPenBox creation failed\n");
	}   
#endif


	mpOptions = NULL;
	InitTiles();

	tcString s;
	s.Format("tcMapData size: %d kB",sizeof(tcMapData)/1024);
	WTL(s.GetBuffer());

	//LoadHighResB(-1.0f, 12.0f);
	//LoadHighResB(-89.0f, 175.0f);

}
/********************************************************************/
tcMapData::~tcMapData() 
{
    CleanupMapArrayHighRes();
    CleanupMapArrayLowRes();

	delete demTileReader;
}
/********************************************************************/