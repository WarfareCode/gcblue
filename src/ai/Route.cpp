/**
**  @file Route.cpp
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

#include "ai/Route.h"

#include "simmath.h"
#include "tcSimState.h"
#include "wx/string.h"

#include "common/tcStream.h"
#include "common/tcObjStream.h"
#include "common/tcGameStream.h"
#include "nsNav.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif 

using namespace ai;


/**
* Saves state to command stream
* Used to save waypoints for client to display
*/
tcCommandStream& Route::operator>>(tcCommandStream& stream)
{
	unsigned char nWaypoints = (unsigned char)waypoints.size();
	stream << nWaypoints;

	for (unsigned char n=0; n<nWaypoints; n++)
	{
        float lon_rad = float(waypoints[n].waypoint.mfLon_rad);
        float lat_rad = float(waypoints[n].waypoint.mfLat_rad);
        float alt_m = waypoints[n].waypoint.mfAlt_m;

		stream << lon_rad;
		stream << lat_rad;
		stream << alt_m;
        stream << waypoints[n].speed_kts;

        unsigned char nTasks = waypoints[n].tasks.size();
        stream << nTasks;
        for (unsigned char k=0; k<nTasks; k++)
        {
            stream << waypoints[n].tasks[k];
        }

        stream << waypoints[n].referenceMode;
        if (waypoints[n].referenceMode != 0)
        {
            stream << waypoints[n].referencePlatform;
            stream << waypoints[n].bearing_rad;
            stream << waypoints[n].range_km;
        }

	}

	return stream;
}

/**
* Loads state to command stream
* Used to load waypoints for client to display
*/
tcCommandStream& Route::operator<<(tcCommandStream& stream)
{
	waypoints.clear();

	unsigned char nWaypoints;
	stream >> nWaypoints;

	for (unsigned char n=0; n<nWaypoints; n++)
	{
		float lon_rad, lat_rad, alt_m, speed_kts;

		stream >> lon_rad;
		stream >> lat_rad;
		stream >> alt_m;
        stream >> speed_kts;

        std::vector<std::string> tasklist;
        unsigned char nTasks;
        stream >> nTasks;
        for (unsigned char k=0; k<nTasks; k++)
        {
            std::string s;
            stream >> s;
            tasklist.push_back(s);
        }

        WaypointData waypointData;
		waypointData.waypoint.Set(lon_rad, lat_rad, alt_m);
        waypointData.speed_kts = speed_kts;
        waypointData.tasks = tasklist;

        stream >> waypointData.referenceMode;
        if (waypointData.referenceMode != 0)
        {
            stream >> waypointData.referencePlatform;
            stream >> waypointData.bearing_rad;
            stream >> waypointData.range_km;
        }

		waypoints.push_back(waypointData);
	}

	return stream;
}



/**
* Read from stream
*/
tcGameStream& Route::operator<<(tcGameStream& stream)
{
    stream >> currentWaypoint;
	stream >> loop;
    stream >> maxPathAltitude_m;
    stream >> platformId;

    waypoints.clear();
	unsigned char nWaypoints;
	stream >> nWaypoints;

	for (unsigned char n=0; n<nWaypoints; n++)
	{
		float lon_rad, lat_rad, alt_m, speed_kts;

		stream >> lon_rad;
		stream >> lat_rad;
		stream >> alt_m;
        stream >> speed_kts;

        std::vector<std::string> tasklist;
        unsigned char nTasks;
        stream >> nTasks;
        for (unsigned char k=0; k<nTasks; k++)
        {
            std::string s;
            stream >> s;
            tasklist.push_back(s);
        }

		WaypointData waypointData;
		waypointData.waypoint.Set(lon_rad, lat_rad, alt_m);
        waypointData.speed_kts = speed_kts;
        waypointData.tasks = tasklist;

        stream >> waypointData.referenceMode;
        stream >> waypointData.referencePlatform;
        stream >> waypointData.bearing_rad;
        stream >> waypointData.range_km;

		waypoints.push_back(waypointData);
	}

    return stream;
}

/**
* Write to stream
*/
tcGameStream& Route::operator>>(tcGameStream& stream)
{
    stream << currentWaypoint;
	stream << loop;
    stream << maxPathAltitude_m;
    stream << platformId;

    unsigned char nWaypoints = (unsigned char)waypoints.size();
	stream << nWaypoints;

	for (unsigned char n=0; n<nWaypoints; n++)
	{
        float lon_rad = float(waypoints[n].waypoint.mfLon_rad);
        float lat_rad = float(waypoints[n].waypoint.mfLat_rad);

		stream << lon_rad;
		stream << lat_rad;
		stream << waypoints[n].waypoint.mfAlt_m;
        stream << waypoints[n].speed_kts;

        unsigned char nTasks = waypoints[n].tasks.size();
        stream << nTasks;
        for (unsigned char k=0; k<nTasks; k++)
        {
            stream << waypoints[n].tasks[k];
        }

        stream << waypoints[n].referenceMode;
        stream << waypoints[n].referencePlatform;
        stream << waypoints[n].bearing_rad;
        stream << waypoints[n].range_km;
	}

    return stream; 
}




void Route::AddWaypoint(double lon_rad, double lat_rad, float alt_m, float speed_kts)
{
    WaypointData waypointData;
    waypointData.waypoint.Set(lon_rad, lat_rad, alt_m);
    waypointData.speed_kts = speed_kts;

    waypointData.referenceMode = 0;
    waypointData.referencePlatform = -1;
    waypointData.bearing_rad = 0;
    waypointData.range_km = 0;

    if (IsPathfindingActive())
    {
        std::vector<WaypointData> newPoints;
        bool success = GetBestPath(waypointData, newPoints);
        waypoints.insert(waypoints.end(), newPoints.begin(), newPoints.end());
    }
    else
    {
        waypoints.push_back(waypointData);
    }
}

void Route::ClearWaypoints()
{
    waypoints.clear();
}

void Route::DeleteWaypoint(size_t idx)
{
    if (idx < waypoints.size())
    {
        waypoints.erase(waypoints.begin() + idx);
    }
}

void Route::EditWaypoint(size_t idx, double lon_rad, double lat_rad, float alt_m, float speed_kts)
{
	if (idx < waypoints.size())
	{
		WaypointData& waypointData = waypoints[idx];
		waypointData.waypoint.mfLon_rad = lon_rad;
		waypointData.waypoint.mfLat_rad = lat_rad;

		if (alt_m != 0) waypointData.waypoint.mfAlt_m = alt_m; // allow negative for submarines
        if (speed_kts > 0) waypointData.speed_kts = speed_kts;

        if (waypointData.referenceMode != 0)
        {
            UpdateRelativeWaypointOffset(idx);
        }
	}
	else
	{
        fprintf(stderr, "Route::EditWaypoint - bad idx\n");
        wxASSERT(false);
    }
}

void Route::EditWaypointReference(size_t idx, unsigned char referenceMode, long referencePlatform)
{
    if (idx < waypoints.size())
    {
        waypoints[idx].referenceMode = referenceMode;
        waypoints[idx].referencePlatform = referencePlatform;

        UpdateRelativeWaypointOffset(idx);
    }
    else
    {
        wxASSERT(false);
    }
}

unsigned Route::GetCurrentWaypoint() const
{
    return currentWaypoint;
}

bool Route::GetLoopState() const
{
	return loop;
}

/**
* @return waypoint vector of GeoPoint
*/
const std::vector<Route::WaypointData>& Route::GetWaypoints() const
{
    return waypoints;
}

size_t Route::GetWaypointCount() const
{
    return waypoints.size();
}

std::vector<Route::WaypointData>& Route::GetWaypointsMutable()
{
    return waypoints;
}

/**
* Inserts waypoint before idx
*/
void Route::InsertWaypoint(size_t idx, double lon_rad, double lat_rad, float alt_m, float speed_kts)
{
	if (idx < waypoints.size())
	{
        WaypointData waypointData;
        waypointData.waypoint.Set(lon_rad, lat_rad, alt_m);
        waypointData.speed_kts = speed_kts;
        waypointData.referenceMode = 0;
        waypointData.referencePlatform = -1;

        waypoints.insert(waypoints.begin() + idx, waypointData);
	}
	else
	{
		fprintf(stderr, "Route::InsertWaypoint - bad idx\n");
	}

}

void Route::SetCurrentWaypoint(unsigned int idx)
{
    if (idx < waypoints.size())
    {
        currentWaypoint = idx;
    }
}

void Route::SetLoopState(bool state)
{
    loop = state;
}


void Route::SetWaypointTasklist(size_t idx, const std::string& tasklist)
{
    if (idx < waypoints.size())
    {
        waypoints[idx].tasks.clear();

        wxString s(tasklist.c_str());
        wxString taskName = s.BeforeFirst(',');
        s = s.AfterFirst(',');
        while (taskName.size() > 0)
        {
            waypoints[idx].tasks.push_back(taskName.ToStdString());

            taskName = s.BeforeFirst(',');
            s = s.AfterFirst(',');
        }

    }
    else
    {
        fprintf(stderr, "Route::SetWaypointTasklist - bad idx\n");
    }
}

const std::vector<std::string>& Route::GetWaypointTasklist(size_t idx) const
{
    static std::vector<std::string> error;

    if (idx < waypoints.size())
    {
        return waypoints[idx].tasks;
    }
    else
    {
        fprintf(stderr, "Route::GetWaypointTasklist - bad idx\n");
        return error;
    }
}

const char* Route::GetWaypointTasklistString(size_t idx) const
{
    static wxString result;

    if (idx < waypoints.size())
    {
        result = "";
        for (size_t n=0; n<waypoints[idx].tasks.size(); n++)
        {
            result += waypoints[idx].tasks[n].c_str();
            if ((n + 1) < waypoints[idx].tasks.size())
            {
                result += ",";
            }
        }
        return result.c_str();
    }
    else
    {
        fprintf(stderr, "Route::GetWaypointTasklist - bad idx\n");
        result = "";
        return result.c_str();
    }
}

void Route::AddWaypointTask(size_t idx, const std::string& task)
{
    if (idx < waypoints.size())
    {
        // verify task isn't already in list
        for (size_t n=0; n<waypoints[idx].tasks.size(); n++)
        {
            if (waypoints[idx].tasks[n] == task) return;
        }
        
        waypoints[idx].tasks.push_back(task);
    }
    else
    {
        fprintf(stderr, "Route::AddWaypointTask - bad idx\n");
    }
}

void Route::RemoveWaypointTask(size_t idx, const std::string& task)
{
    if (idx < waypoints.size())
    {
        std::vector<std::string> temp;
        for (size_t n=0; n<waypoints[idx].tasks.size(); n++)
        {
            if (waypoints[idx].tasks[n] != task)
            {
                temp.push_back(waypoints[idx].tasks[n]);
            }
        }
        waypoints[idx].tasks = temp;
    }
    else
    {
        fprintf(stderr, "Route::RemoveWaypointTask - bad idx\n");
    }
}

/**
* Update lat/lon based on relative offsets and current reference platform
* position
*/
void Route::UpdateRelativeWaypointCoordinate(size_t idx)
{
    if ((idx < waypoints.size()) && (waypoints[idx].referenceMode != 0))
    {
        tcSimState* simState = tcSimState::Get();

        tcGameObject* refObj = simState->GetObject(waypoints[idx].referencePlatform);
        if (refObj == 0) // ref platform doesn't exist
        {
            EditWaypointReference(idx, 0, -1);
            return;
        }

        float bearing_rad = (waypoints[idx].referenceMode == 2) ? refObj->mcKin.mfHeading_rad + waypoints[idx].bearing_rad :
                waypoints[idx].bearing_rad;
        refObj->mcKin.SetRelativeGeo(waypoints[idx].waypoint, bearing_rad, waypoints[idx].range_km);
    }
}

/**
* Update relative offsets based on lat/lon and ref platform position
*/
void Route::UpdateRelativeWaypointOffset(size_t idx)
{
    if ((idx < waypoints.size()) && (waypoints[idx].referenceMode != 0))
    {
        tcSimState* simState = tcSimState::Get();

        tcGameObject* refObj = simState->GetObject(waypoints[idx].referencePlatform);
        if (refObj == 0) // ref platform doesn't exist
        {
            EditWaypointReference(idx, 0, -1);
            return;
        }

        waypoints[idx].bearing_rad = refObj->mcKin.HeadingToGeoRad(&waypoints[idx].waypoint);
        waypoints[idx].range_km = refObj->mcKin.RangeToKm(&waypoints[idx].waypoint);

        if (waypoints[idx].referenceMode == 2)
        {
            waypoints[idx].bearing_rad -= refObj->mcKin.mfHeading_rad;
        }
    }
}

void Route::SetMaxPathAltitude_m(float alt_m)
{
    maxPathAltitude_m = alt_m;
}

float Route::GetMaxPathAltitude_m() const
{
    return maxPathAltitude_m;
}

bool Route::IsPathfindingActive() const
{
    return false; //(maxPathAltitude_m < 10000.0f);
}

void Route::SetPlatformId(long id)
{
    platformId = id;
}

/**
* @return true if path found, false if no path found
* Do pathfinding from last current waypoint (or present position if no waypoints) to destination
*/
bool Route::GetBestPath(const WaypointData& destination, std::vector<WaypointData>& newPoints)
{
    newPoints.clear();
    tcSimState* simState = tcSimState::Get();
    tcMapData* mapData = tcMapData::Get();

    GeoPoint p(0,0,0);
    if (waypoints.size() > 0)
    {
        p.mfLon_rad = waypoints.back().waypoint.mfLon_rad;
        p.mfLat_rad = waypoints.back().waypoint.mfLat_rad;
    }
    else
    {
        tcGameObject* obj = simState->GetObject(platformId);
        if (obj != 0)
        {
            p.mfLon_rad = obj->mcKin.mfLon_rad;
            p.mfLat_rad = obj->mcKin.mfLat_rad;
        }
        else
        {
            wxASSERT(false);
            newPoints.push_back(destination);
            return false;
        }
    }



    std::vector<float> offsetVect_rad; // vector of bearing offsets to try while searching
    for (float x_deg=15.0f; x_deg<=180.0f; x_deg+=15.0f)
    {
        offsetVect_rad.push_back(C_PIOVER180 * x_deg);
        offsetVect_rad.push_back(-C_PIOVER180 * x_deg);
    }


    std::vector<GeoPoint> path;
    
    GeoPoint dest(destination.waypoint.mfLon_rad, destination.waypoint.mfLat_rad, 0);

    unsigned int nIterations = 0;
    bool searching = true;
    while (searching && (nIterations++ < 2000))
    {    
        // try straight route
        GeoPoint pclear(p);
        bool isClear = mapData->GetFarthestClearPoint(p.mfLon_rad, p.mfLat_rad, 
            destination.waypoint.mfLon_rad, destination.waypoint.mfLat_rad, 
            maxPathAltitude_m,
            pclear.mfLon_rad, pclear.mfLat_rad);
        if (isClear)
        {
            path.push_back(GeoPoint(destination.waypoint.mfLon_rad, destination.waypoint.mfLat_rad, destination.waypoint.mfAlt_m));
            searching = false;
        }
        else
        {
            path.push_back(pclear); // add farthest obstructed point to path
            p = pclear;
        }

        if (searching)
        {
            // find next clear point close to direction of goal
            float destBearing_rad = nsNav::GCHeadingApprox_rad(p, dest);
            float range_km = C_RADTOKM * nsNav::GCDistanceApprox_rad(p, dest);

            bool checkingOffsets = true;
            const float d_km = 5.0f;
            for (size_t n=0; (n<offsetVect_rad.size()) && checkingOffsets; n++)
            {
                GeoPoint p2(p);
                GeoPoint pclear(p);
                p2.Offset(d_km, destBearing_rad + offsetVect_rad[n]);
                isClear = mapData->GetFarthestClearPoint(p.mfLon_rad, p.mfLat_rad, 
                    p2.mfLon_rad, p2.mfLat_rad, maxPathAltitude_m,
                    pclear.mfLon_rad, pclear.mfLat_rad);
                if (isClear)
                {
                    path.push_back(p2);
                    p = p2;
                    checkingOffsets = false;
                }
            }
        }

    }

    // create waypoints

    WaypointData temp(destination);
    for (size_t n=0; n<path.size(); n++)
    {
        temp.waypoint = path[n];
        newPoints.push_back(temp);
    }

    return true;
}



Route& Route::operator=(const Route& rhs)
{
    waypoints = rhs.waypoints;
    currentWaypoint = rhs.currentWaypoint;
    loop = rhs.loop;
    maxPathAltitude_m = rhs.maxPathAltitude_m;
    platformId = rhs.platformId;

    return *this;
}

Route::Route(const Route& src)
: waypoints(src.waypoints),
  currentWaypoint(src.currentWaypoint),
  loop(src.loop),
  maxPathAltitude_m(src.maxPathAltitude_m),
  platformId(src.platformId)
{
}

Route::Route()
:   currentWaypoint(0),
	loop(false),
    maxPathAltitude_m(99999.0f),
    platformId(-1)
{
}



Route::~Route()
{
}



