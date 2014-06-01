/**  
**  @file tcDemTileReader.h
**
**  Header for the tcDemTileReader.h class.
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


#if !defined _TCDEMTILEREADER_H_
#define _TCDEMTILEREADER_H_

#include "wx/wx.h"
#ifdef WIN32
#include "wx/msw/private.h" // for MS Windows specific definitions
#endif

#include "tcFile.h"
#include <map>
/**
* Class to read and keep track of which DEM tiles are available
*/
class tcDemTileReader
{
public:
    enum
    {
        HIGH_RES = 1,
        MEDIUM_RES = 2,
        LOW_RES = 3,
        LOW10_RES = 4
    };
	enum
	{
		M_DEMTILE = 1200,
		N_DEMTILE = 1200,
	};
	int GetTileWidth(int resolution) const;
	int GetTileHeight(int resolution) const;


	bool IsTileAvailable(int lat, int lon, int resolution);
	void LoadDemTile(tcFile& tileFile, int lat_deg, int lon_deg, int resolution);

	tcDemTileReader();
	~tcDemTileReader();
private:
	tcString demPathHigh;
    tcString demPathMedium;
    tcString demPathLow;
    tcString demPathLow10;
	std::map<long, bool> tileStatusHigh;
    std::map<long, bool> tileStatusMedium;
	std::map<long, bool> tileStatusLow;
	std::map<long, bool> tileStatusLow10;

	void GetTileName(wxString& nameString, int lat_deg, int lon_deg, int resolution);
	void KeyToLatLon(long key, int& lat, int& lon);
	long LatLonToKey(int lat, int lon);
	void MarkTileUnavailable(int lat, int lon, int resolution);
	void ScanTiles();
};


#endif 
