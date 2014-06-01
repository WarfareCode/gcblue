/**
**  @file tcPositionRegistry.cpp
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

#include "tcPositionRegistry.h"
#include "math_constants.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


/**
* Adds contents of bin <bin> to back of vector <v>. If the bin is empty
* nothing is added
*/
void tcPositionRegistry::AppendBinContents(std::vector<long>& v, long bin)
{
    std::map<long, std::map<long, bool> >::const_iterator iter = 
        positionMap.find(bin);
    
    if (iter == positionMap.end()) return;
    
    std::map<long, bool>::const_iterator binIter = iter->second.begin();
    while (binIter != iter->second.end())
    {
        v.push_back(binIter->first);
        ++binIter;
    }
}

void tcPositionRegistry::ConformLonLat(double& lon_west, double& lon_east, 
        double& lat_south, double& lat_north)
{
    // put lon into [-pi, pi) and saturate lat to [-pi/2, pi/2]
    wxASSERT((lat_south >= -piovertwo) && (lat_south <= piovertwo));
    wxASSERT((lat_north >= -piovertwo) && (lat_north <= piovertwo));
    wxASSERT((lon_west >= -twopi) && (lon_west <= twopi));
    wxASSERT((lon_east >= -twopi) && (lon_east <= twopi));
    
    if (lon_west < -pi) lon_west += twopi;
    else if (lon_west >= pi) lon_west -= twopi;
    
    if (lon_east < -pi) lon_east += twopi;
    else if (lon_east >= pi) lon_east -= twopi;    
    
    if (lat_south < -piovertwo) lat_south = -piovertwo;
    else if (lat_south > piovertwo) lat_south = piovertwo;
    
    if (lat_north < -piovertwo) lat_north = -piovertwo;
    else if (lat_north > piovertwo) lat_north = piovertwo;    
}

std::vector<long>& tcPositionRegistry::GetAllWithinRegion(double lon_west, double lon_east, 
                                                          double lat_south, double lat_north)
{
    static std::vector<long> idVect;
    
    idVect.clear();
    
    wxASSERT(lat_north >= lat_south);
    ConformLonLat(lon_west, lon_east, lat_south, lat_north);
    
    long lat_south_idx = LatToIndex(lat_south);
    long lat_north_idx = LatToIndex(lat_north);
    long lon_west_idx = LonToIndex(lon_west);
    long lon_east_idx = LonToIndex(lon_east);
    
    for (long lat_idx = lat_south_idx; lat_idx <= lat_north_idx; lat_idx++)
    {
        long lat_offset = nLatBins * lat_idx;
        for (long lon_idx = lon_west_idx; lon_idx <= lon_east_idx; lon_idx++)
        {
            long bin = lat_offset + lon_idx;
            
            AppendBinContents(idVect, bin);
        }
    }
    
    return idVect;
}

void tcPositionRegistry::AddIdToBin(long id, long bin)
{
    positionMap[bin][id] = true;
}

void tcPositionRegistry::RemoveAll()
{
    //fprintf(stdout, "removing all (%d)\n", entryLookup.size());
    positionMap.clear();
    
    entryLookup.clear();
}

void tcPositionRegistry::RemoveIdFromBin(long id, long bin)
{
    std::map<long, std::map<long, bool> >::iterator posIter = 
            positionMap.find(bin);
    if (posIter == positionMap.end())
    {
#ifdef _DEBUG
        fprintf(stderr, "tcPositionRegistry::RemoveIdFromBin - "
            "bin not found in positionMap (%d)\n", bin);   
#endif
        return;
    }   
    
    std::map<long, bool>::iterator binIter = 
        posIter->second.find(id);
    if (binIter == posIter->second.end())
    {
#ifdef _DEBUG
        fprintf(stderr, "tcPositionRegistry::RemoveIdFromBin - "
            "id not found in bin map (%d, %d)\n", bin, id);   
#endif
        return;    
    }
    
    // remove id from bin map
    posIter->second.erase(binIter); 
    
    // if bin map is now empty, remove this bin from positionMap
    if (posIter->second.size() == 0)
    {
        positionMap.erase(posIter);
    }
    
}


void tcPositionRegistry::RemoveId(long id)
{
    // check if id exists in entryLookup
    std::map<long, long>::iterator entryIter = entryLookup.find(id);
    
    if (entryIter == entryLookup.end())
    {
        fprintf(stderr, "tcPositionRegistry::RemoveId - "
            "id not found in entryLoookup (%d)\n", id);
        return;
    }   
    
    long bin = entryIter->second;
    entryLookup.erase(entryIter);
    
    //fprintf(stdout, "removing id %d from bin %d\n", id, bin);
    RemoveIdFromBin(id, bin);
}

void tcPositionRegistry::UpdatePosition(long id, double lon, double lat)
{
    wxASSERT(id != -1);
    wxASSERT((lon >= -pi) && (lon < pi));
    wxASSERT((lat >= -piovertwo) && (lat < piovertwo));
    
    long bin = LonLatToBinLocation(lon, lat);
    
    // check if id exists in entryLookup
    std::map<long, long>::iterator entryIter = entryLookup.find(id);
    if (entryIter == entryLookup.end())
    {
        entryLookup[id] = bin; // add for first time
        AddIdToBin(id, bin);
        //fprintf(stdout, "new add, id %d to bin %d\n", id, bin);
        return;
    }   
    
    long previousBin = entryIter->second;
    if (previousBin == bin) return; // no change, return
    
    RemoveIdFromBin(id, previousBin);
    AddIdToBin(id, bin);
    //fprintf(stdout, "transfering id %d from bin %d to %d\n", id, previousBin, bin);
    
    entryLookup[id] = bin; // update bin for id
}


long tcPositionRegistry::LatToIndex(double lat)
{
    wxASSERT(lat > -C_PIOVER2);

    long idx = long((lat + piovertwo) * invBinWidth);
    
    return idx;          
}

long tcPositionRegistry::LonToIndex(double lon)
{
    wxASSERT(lon > -C_PI);

    long idx = long((lon + pi) * invBinWidth);
    
    return idx;           
}


long tcPositionRegistry::LonLatToBinLocation(double lon, double lat)
{
    double bin = (nLatBins * LatToIndex(lat)) + LonToIndex(lon);
    long nBin = long(bin);
    
    return nBin;           
}


/**
*
*/
tcPositionRegistry::tcPositionRegistry() 
:  pi(3.141592653589793),
   twopi(6.283185307179586),
   piovertwo(1.570796326794897),
   binWidth(0.2 * 0.017453293) // 0.2 degrees lon/lat
{
    invBinWidth = 1.0 / binWidth;
    nLatBins = ceil(pi * invBinWidth);

}

/**
*
*/
tcPositionRegistry::~tcPositionRegistry() 
{
}


