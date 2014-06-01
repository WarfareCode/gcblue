/*  
**  @file tcDemTileReader.cpp
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

#ifdef WX_PRECOMP
#include "stdwx.h"
#endif

#include "tcDemTileReader.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif




int tcDemTileReader::GetTileWidth(int resolution) const
{
    switch (resolution)
    {
    case HIGH_RES:
        return N_DEMTILE;
        break;
    case MEDIUM_RES:
        return N_DEMTILE/4;
        break;
    case LOW10_RES:
        return N_DEMTILE/10;
        break;
    case LOW_RES:
        return N_DEMTILE/12;
        break;
    default:
        wxASSERT(false);
        return -1;
    }
}

int tcDemTileReader::GetTileHeight(int resolution) const 
{
    switch (resolution)
    {
    case HIGH_RES:
        return M_DEMTILE;
        break;
    case MEDIUM_RES:
        return M_DEMTILE/4;
        break;
    case LOW10_RES:
        return M_DEMTILE/10;
        break;
    case LOW_RES:
        return M_DEMTILE/12;
        break;
    default:
        wxASSERT(false);
        return -1;
    }
}



/**
* Sets namestring to path + filename of 10 x 10 dem tile for northwest
* point of (lat_deg, lon_deg). lat_deg and lon_deg must be multiples
* of 10 to get a valid file name
*/
void tcDemTileReader::GetTileName(wxString& nameString, int lat_deg, int lon_deg, int resolution)
{
	wxASSERT(lat_deg % 10 == 0);
	wxASSERT(lon_deg % 10 == 0);

    switch (resolution)
    {
    case HIGH_RES:
	    nameString = demPathHigh.GetBuffer();
        break;
    case MEDIUM_RES:
        nameString = demPathMedium.GetBuffer();
        break;
    case LOW_RES:
        nameString = demPathLow.GetBuffer();
        break;
    case LOW10_RES:
        nameString = demPathLow10.GetBuffer();
        break;
    default:
        wxASSERT(false);
        nameString = "Error";
        return;
        break;
    }

	nameString += wxString::Format("%dx%d.dat", lat_deg, lon_deg);
}


bool tcDemTileReader::IsTileAvailable(int lat, int lon, int resolution)
{
    static std::map<long, bool> nullMap;

    std::map<long, bool>& statusMap = nullMap;

    switch (resolution)
    {
    case HIGH_RES:
	    statusMap = tileStatusHigh;
        break;
    case MEDIUM_RES:
        statusMap = tileStatusMedium;
        break;
    case LOW_RES:
        statusMap = tileStatusLow;
        break;
    case LOW10_RES:
        statusMap = tileStatusLow10;
        break;
    default:
        wxASSERT(false);
        return false;
    }

	std::map<long, bool>::const_iterator mapIter;

	long key = LatLonToKey(lat, lon);

    mapIter = statusMap.find(key);
    if (mapIter == statusMap.end())  // not found
    {
		tcFile demTile;
		LoadDemTile(demTile, lat, lon, resolution);
		statusMap[key] = demTile.IsOpen();
		demTile.Close();
		return statusMap[key];
    }
	else
	{
		return statusMap[key];
	}
}

void tcDemTileReader::KeyToLatLon(long key, int& lat, int& lon)
{
	lon = (key / 256) - 180;
	lat = (key % 256) - 90;
}

long tcDemTileReader::LatLonToKey(int lat, int lon)
{
	return (lat + 90) + 256 * (lon + 180);
}

/**
* Loads 10 x 10 deg DEM tile specified by Northwest corner point
* (lat_deg, lon_deg). If tile does not exist no load takes place.
* @param lat_deg latitude of Northwest corner point in deg
* @param lat_deg should be mult of 10 deg between -80 and 90
* @param lon_deg longitude of Northwest corner point in deg
* @param lon_deg should be mult of 10 deg between -180 and 170
*/
void tcDemTileReader::LoadDemTile(tcFile& tileFile, int lat_deg, int lon_deg, int resolution)
{
	//static int errorCount = 0;

	wxString demTileName;
	GetTileName(demTileName, lat_deg, lon_deg, resolution);
	
	if (tileFile.Open(demTileName.c_str(), tcFile::modeRead) ==0)
	{
		/*
		if ((errorCount < 10)||(errorCount++ % 100 == 0))
		{
			fprintf(stderr, "Map tile not found: %s\n", demTileName.c_str());
		}
		*/
	}
}

void tcDemTileReader::MarkTileUnavailable(int lat, int lon, int resolution)
{
    static std::map<long, bool> nullMap;

    std::map<long, bool>& statusMap = nullMap;

    switch (resolution)
    {
    case HIGH_RES:
	    statusMap = tileStatusHigh;
        break;
    case MEDIUM_RES:
        statusMap = tileStatusMedium;
        break;
    case LOW_RES:
        statusMap = tileStatusLow;
        break;
    case LOW10_RES:
        statusMap = tileStatusLow10;
        break;
    default:
        wxASSERT(false);
        return;
    }

	long key = LatLonToKey(lat, lon);
    
	statusMap[key] = false;
}

void tcDemTileReader::ScanTiles()
{
    // high resolution tiles
	int availCount = 0;

	for (int lat = -80; lat <= 90; lat += 10)
	{
		for (int lon = -180; lon <=170; lon += 10)
		{
			availCount += IsTileAvailable(lat, lon, HIGH_RES) ? 1 : 0;
		}
	}
	
	fprintf(stdout, "%d / %d high res map tiles available\n", 
		availCount, 648);

    // medium resolution tiles
	availCount = 0;

	for (int lat = -80; lat <= 90; lat += 10)
	{
		for (int lon = -180; lon <=170; lon += 10)
		{
			availCount += IsTileAvailable(lat, lon, MEDIUM_RES) ? 1 : 0;
		}
	}
	
	fprintf(stdout, "%d / %d medium res map tiles available\n", 
		availCount, 648);

    // low resolution tiles
	availCount = 0;

	for (int lat = -80; lat <= 90; lat += 10)
	{
		for (int lon = -180; lon <=170; lon += 10)
		{
			availCount += IsTileAvailable(lat, lon, LOW_RES) ? 1 : 0;
		}
	}
	
	fprintf(stdout, "%d / %d low res map tiles available\n", 
		availCount, 648);

    // low resolution tiles (10:1 decimation)
	availCount = 0;

	for (int lat = -80; lat <= 90; lat += 10)
	{
		for (int lon = -180; lon <=170; lon += 10)
		{
			availCount += IsTileAvailable(lat, lon, LOW10_RES) ? 1 : 0;
		}
	}
	
    fprintf(stdout, "%d / %d low res (10:1) map tiles available\n", 
		availCount, 648);

}



tcDemTileReader::tcDemTileReader()
{
	demPathHigh = "maps\\tiles\\";
    demPathMedium = "maps\\tiles\\medres\\";
    demPathLow = "maps\\tiles\\lowres\\";
    demPathLow10 = "maps\\tiles\\lowres10\\";

	ScanTiles();
}

tcDemTileReader::~tcDemTileReader()
{
}