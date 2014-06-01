/**
**  @file tcLOS.cpp
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

#include "tcLOS.h"
#include "tcOptions.h"
#include "tcMapData.h"
#include "nsNav.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


tcLOS* tcLOS::Get()
{
    static tcLOS instance;
    return &instance;
}




void tcLOS::Clear()
{
    rayCache.clear();

    lastUpdateTime = 0;
}

size_t tcLOS::GetRayCount() const
{
    return rayCache.size();
}


const wxString& tcLOS::GetRayTestData(const GeoPoint& p1, const GeoPoint& p2)
{
    static wxString s;

    s.clear();

    wxString text = wxString::Format("p1: lat %.4f, lon %.4f, alt %.0f m\n", 
        C_180OVERPI*p1.mfLat_rad, C_180OVERPI*p1.mfLon_rad, p1.mfAlt_m);
    text += wxString::Format("p2: lat %.4f, lon %.4f, alt %.0f m\n", 
        C_180OVERPI*p2.mfLat_rad, C_180OVERPI*p2.mfLon_rad, p2.mfAlt_m);

    RayData testRay;
    testRay.p1 = p1;
    testRay.p2 = p2;
    testRay.t_update = 0;
    testRay.terrainClearance_m = 98765.0f;

    UpdateRay(testRay);

    text += wxString::Format("   min LOS clearance: %.0f m (%d rays in cache, %d map tiles)\n", testRay.terrainClearance_m,
        GetRayCount(), mapData->GetTilesUsedCount());

    s = text;

    return s;
}

/**
* @return true if unobstructed path exists along line-of-sight between p1 and p2
*/
bool tcLOS::HasLOS(long key, double t, const GeoPoint& p1, const GeoPoint& p2)
{
    if (tcOptions::Get()->calcLineOfSight == 0)
    {
        return HasLOSSimple(key, t, p1, p2);
    }

    std::map<long, RayData>::iterator iter = rayCache.find(key);
    if (iter == rayCache.end())
    {
        RayData rayData;
    
        rayData.t_update = t;
        rayData.terrainClearance_m = 0;

        rayCache[key] = rayData;
        iter = rayCache.find(key);
    }

    wxASSERT(iter != rayCache.end());

    RayData& ray = iter->second;

    // coarse distance traveled measure to determine when to update ray, linear north dist + east dist at equator
    // + 2 x alt change
    float d1 = C_RADTOM*(fabsf(ray.p1.mfLat_rad - p1.mfLat_rad) + fabsf(ray.p1.mfLon_rad - p1.mfLon_rad)) +
        2.0*fabsf(ray.p1.mfAlt_m - p1.mfAlt_m);
    float d2 = C_RADTOM*(fabsf(ray.p1.mfLat_rad - p1.mfLat_rad) + fabsf(ray.p1.mfLon_rad - p1.mfLon_rad)) +
        2.0*fabsf(ray.p1.mfAlt_m - p1.mfAlt_m);

    if ((d1 + d2) > 200.0f)
    {
        ray.p1 = p1;
        ray.p2 = p2;
        ray.t_update = t;
        
        UpdateRay(ray);
    }

    if (ray.terrainClearance_m >= 0)
    {
        return true;
    }
    else
    {
        return false;
    }
 
}

bool tcLOS::HasLOSSimple(long key, double t, const GeoPoint& p1, const GeoPoint& p2)
{
    return true;
}


/**
* Remove stale rays from rayCache
*/
void tcLOS::Update(double t)
{
    if (t - lastUpdateTime < 31.0) return;
    lastUpdateTime = t;

    std::map<long, RayData> temp;

    std::map<long, RayData>::iterator iter = rayCache.begin();
    for (;iter != rayCache.end(); ++iter)
    {
        if ((t - iter->second.t_update) < 60.0)
        {
            temp.insert(*iter);
        }
    }

    rayCache = temp;
}


/**
* This has some fundamental issues with using a curved earth approx for radar horizon
* calculations, and then assuming the earth is a flat plate for terrain masking, but it's
* better than nothing
*/
void tcLOS::UpdateRay(RayData& ray)
{
    // calculate separation in longitude, latitude, and altitude between the two points
    float dLon_deg = C_180OVERPI*(ray.p2.mfLon_rad - ray.p1.mfLon_rad);
    dLon_deg = dLon_deg + 360*(dLon_deg < -180) - 360*(dLon_deg >= 180);

    float dLat_deg = C_180OVERPI*(ray.p2.mfLat_rad - ray.p1.mfLat_rad);
    float dAlt_m = ray.p2.mfAlt_m - ray.p1.mfAlt_m;

    float range_km = C_RADTOKM * nsNav::GCDistanceApprox_rad(ray.p1, ray.p2);

    unsigned int nPoints = (unsigned int)ceilf(range_km * 0.25);


    nPoints = std::max(nPoints, (unsigned int)3);
    float step_scale = 1.0f / float(nPoints + 1);

    float lon_step = dLon_deg * step_scale;
    float lat_step = dLat_deg * step_scale;
    float alt_step = dAlt_m * step_scale;

    float lon_n = C_180OVERPI * ray.p1.mfLon_rad;
    float lat_n = C_180OVERPI * ray.p1.mfLat_rad;
    float alt_n = ray.p1.mfAlt_m;

    float minimumClearance_m = 99999.9f;
    unsigned int minIdx = 1; // not sure what else to use

    for (unsigned int n=0; n<nPoints; n++)
    {        
        lon_n += lon_step;
        lat_n += lat_step;
        alt_n += alt_step;

        lon_n = lon_n + 360*(lon_n < -180) - 360*(lon_n >= 180);

        float terrain_m = mapData->GetTerrainHeight(lon_n, lat_n, ray.t_update);

        float clearance_m = alt_n - terrain_m;
        if (clearance_m < minimumClearance_m)
        {
            minimumClearance_m = clearance_m;
            minIdx = n;
        }
    }

    // do fine search near minimum
    lon_n = C_180OVERPI * ray.p1.mfLon_rad;
    lat_n = C_180OVERPI * ray.p1.mfLat_rad;
    alt_n = ray.p1.mfAlt_m;

    float startOffset = float(minIdx+1) - 0.75f;
    lon_n += lon_step * startOffset;
    lat_n += lat_step * startOffset;
    alt_n += alt_step * startOffset;

    for (unsigned int n=0; n<7; n++)
    {
        lon_n = lon_n + 360*(lon_n < -180) - 360*(lon_n >= 180);

        float terrain_m = mapData->GetTerrainHeight(lon_n, lat_n, ray.t_update);

        float clearance_m = alt_n - terrain_m;
        if (clearance_m < minimumClearance_m)
        {
            minimumClearance_m = clearance_m;
        }

        lon_n += 0.25f * lon_step;
        lat_n += 0.25f * lat_step;
        alt_n += 0.25f * alt_step;
    }


    ray.terrainClearance_m = minimumClearance_m;

}


/**
*
*/
tcLOS::tcLOS()
: lastUpdateTime(0)
{
    mapData = tcMapData::Get();
}


/**
*
*/
tcLOS::~tcLOS() 
{
}