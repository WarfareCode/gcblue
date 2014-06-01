/**  
**  @file tcMapData.h
*/
/*  Header for the tcMapData class.
**  Documentation http://www.ngdc.noaa.gov/seg/topo/report/
**  Georeferencing info: http://www.ngdc.noaa.gov/seg/topo/report/s5/s5Biii.html 
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


#ifndef _TCMAPDATA_H_
#define _TCMAPDATA_H_

#include "wx/wx.h"

#ifdef WIN32
#include "wx/msw/private.h" //for MS Windows specific definitions
#endif

#include "simmath.h"
#include "tcOptions.h"
#include "tcString.h"
#include <boost/shared_ptr.hpp>

#define K_DEC_LOWRES (int)30
#define SCALE_LOWRES (float)120/(float)K_DEC_LOWRES
#define SCALE_HIGHRES (float)120.0f
#define SCALE_LOOKUP (float)0.5f
#define RESLOW_DEG (float)K_DEC_LOWRES/120.0f
#define RESHIGH_DEG (float)1.0f/120.0f
#define M_LOWRES (int)180*120/K_DEC_LOWRES // latitude cells for low res global map
#define N_LOWRES (int)360*120/K_DEC_LOWRES // longitude
//#define M_HIGHRES 1024
//#define N_HIGHRES 2048
#define N_DEMFILES 16
#define MAX_TILES 512 // maximum number of tiles available to hold high res map data
#define M_TILE_LOOKUP 360
#define N_TILE_LOOKUP 720
#define M_TILE 60
#define N_TILE 60
#define NULL_TILE 0xFFFF
#define TILE_AGEOUT (double)30.0

#define ME_GENERIC 0x0000
#define ME_TILE_STRUCTURE 0x0001
#define ME(x) ReportMapDataError(x);

class tcDemTileReader;
class tcTexture2D;

struct tsDemInfo 
{
    tcString mzFileName;
    float mfLonMin,mfLonMax;
    float mfLatMin,mfLatMax;
};

struct tsTileData
{
    bool mbActive;
    unsigned int m_lat; ///< index into lookup table
    unsigned int n_lon;
    double mfLastAccessTime;
    short maMapData[M_TILE][N_TILE];  ///< 7k tile 30 sec DEM data
};

struct tsMapDataInfo
{
    int mnLowResHeight;
    int mnLowResWidth;
    int mnHighResHeight;
    int mnHighResWidth;
};

struct tsDefaultMapInfo
{
    float mfLat_deg;
    float mfLon_deg;
    unsigned mnWidth;
    unsigned mnHeight;
};

#define DEFAULT_TILE_NAME "defaulttile.dat"

/**
* This class interfaces to 30 arc-sec DEM map data.
* A cache of 0.5 x 0.5 deg tiles is used. Methods are provided
* to create images for map terrain view display. Several different
* generations of code are jumbled together here. This sorely
* needs refactoring.
*
* Converted into singleton class.
*/
class tcMapData  
{
public:
	enum
	{
		MISSING_DATA_VAL = -32383
	};
    void AgeOutTiles(double afStatusTime);
    void AttachOptions(tcOptions *pOptions) {mpOptions=pOptions;mnCurrentMapMode=pOptions->mnMapMode;}
    void CreateHighResMapImage(int anMode, UINT32 *apData);
    void CreateMapImage(int anMode, int anMapID, boost::shared_ptr<tcTexture2D> image);
    float GetHRLatSpan() {return 0.5f*mrTheaterView.Height();}
    float GetHRLonSpan() {return 0.5f*mrTheaterView.Width();}
    void GetMapDataInfo(tsMapDataInfo *pMDI);
    GeoPoint GetRandomPointNear(float lon, float lat, float r, 
        float minAlt = -16000.0f, float maxAlt = 16000.0f);
    float GetTerrainHeight(double afLon_deg, double afLat_deg, double afStatusTime);
	float GetTerrainHeightHighRes(double afLon_deg, double afLat_deg); 
    float GetTerrainHeightLowRes(float afLon_deg, float afLat_deg);
    void GetTheaterArea(tcGeoRect& r) {r = mrTheaterView;}
	float GetTheaterHeightDeg() const;
	float GetTheaterWidthDeg() const;
    int GetTheaterDecimation() const;
    void SetTheaterDecimation(int val);

    int GetLowResDecimation() const;
    int GetMedResDecimation() const;
    int GetHighResDecimation() const;
    bool IsTheaterDecimationValid(int dec) const;

    size_t GetHighResRowCount() const;
    size_t GetHighResColCount() const;

    unsigned short GetTilesUsedCount() const;

    void GetWorldArea(tcGeoRect& r) {r = mrWorldView;}
    void GetTheaterData(short*& rpData, unsigned& anM, unsigned& anN);
	void LoadHighResB(float startLon_deg, float startLat_deg);
    void LoadHighResC(float centerLon_deg, float centerLat_deg, int dec);
    int LoadLowRes();
    void CreateDefaultMap(float afStartLat_deg, float afStartLon_deg, 
        unsigned anWidth, unsigned anHeight);

    bool GetFarthestClearPoint(float lon1_rad, float lat1_rad, float lon2_rad, float lat2_rad, float maxTerrain_m,
        float& lon_rad, float& lat_rad);
    bool GetFarthestClearPoint(float lon1_rad, float lat1_rad, float lon2_rad, float lat2_rad, float maxTerrain_m,
        double& lon_rad, double& lat_rad);

	static tcMapData* Get(); ///< singleton accessor
private:
    tcMapData();
    ~tcMapData();

    tcOptions *mpOptions;
    tsDemInfo maDemInfo[N_DEMFILES];

    int GetLowResBltList(tcRect view, int anWidth, int anHeight, RECT *aaSource, RECT *aaDest);
    int GetHighResBltList(tcRect view, int anWidth, int anHeight, RECT *aaSource, RECT *aaDest);
    HFONT mhFontDefault;
    HFONT mhFontCountry;
    size_t M_HIGHRES; ///< dynamic # rows of theater data
    size_t N_HIGHRES; ///< dynamic # cols of theater data
    int lowResDecimation; ///< lowest resolution decimation factor
    int medResDecimation; ///< medium resolution decimation factor
    int highResDecimation; ///< highest resolution decimation factor, normally 1

    short* maGlobal;
    short* maTheater;
    float scaleHighRes; ///< pixels per degrees of theater map
    int theaterDecimation;

    tcGeoRect mrTheaterView;  ///< geo bounds of loaded theater (high res) map
	tcRect theaterViewDeg; ///< theater boundaries in degrees
    tcGeoRect mrWorldView; ///<  bounds of loaded world (low res) map
    HPEN mhPenBox;
    long maPalette1[1024];
    int mnCurrentMapMode; ///<  versus requested map mode in options

	tcDemTileReader* demTileReader;

    unsigned short maTileLookup[M_TILE_LOOKUP][N_TILE_LOOKUP];  // 506k lookup table, 0.5 deg tiles
    tsTileData maTile[MAX_TILES]; ///<  statically allocated array of tiles
    unsigned short mnTilesUsed; ///<  current number of tiles in use
    unsigned short maAvailableTiles[MAX_TILES]; // array of free indices (FIFO)
    unsigned short mnCheckoutIndex; ///<  maAvailableTiles index for allocation
    unsigned short mnReturnIndex; ///<  maAvailableTiles index for deallocation
    tsTileData* GetTile(unsigned mtile, unsigned ntile, double afStatusTime);

    tsTileData* LoadTile(unsigned mtile, unsigned ntile);
	tsTileData* LoadTileB(unsigned mtile, unsigned ntile);
	tsTileData* LoadTileFromLowRes(unsigned mtile, unsigned ntile);
	

    void CreatePalettes();
    void DarkenLowResUnavailable(boost::shared_ptr<tcTexture2D> image);
    void LabelLowRes();
	UINT32 BlackBlueMap(long pval) const;
	UINT32 CopperBlueMap(long pval) const;
	UINT32 YellowBlueMap(long pval) const;

    void FillInvalidHighResData(size_t M, size_t N, size_t mstart, size_t nstart,
        tcFile *pMain, tcFile *pEast, tcFile *pSouth, tcFile *pSouthEast);

    int ReadHighResDataChunk(tcFile* tile, int M_tile, int N_tile, int mSource, int nSource, 
                                    int mDest, int nDest);
    int ReadHighResDataChunkNull(int M_tile, int N_tile, 
                                    int mSource, int nSource, 
                                    int mDest, int nDest);

    void ReportMapDataError(UINT32 anError);
    void SetDemInfo();
    void InitTiles();
    void CreateMapArrayHighRes();
    void CreateMapArrayLowRes();
    void CleanupMapArrayHighRes();
    void CleanupMapArrayLowRes();
};

#endif 
