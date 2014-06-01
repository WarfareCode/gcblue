/**
**  @file Route.h
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

#ifndef _ROUTE_H_
#define _ROUTE_H_

#if _MSC_VER > 1000
#pragma once
#endif


#include <vector>
#include "simmath.h"


class GeoPoint;

class tcStream;
class tcCommandStream;
class tcCreateStream;
class tcUpdateStream;
class tcGameStream;

namespace ai
{

/**
* Basic navigation with waypoints
*/
class Route
{
public:
    struct WaypointData
    {
        GeoPoint waypoint;
        float speed_kts; ///< <=0 means don't adjust speed
        std::vector<std::string> tasks; ///< list of task scripts to start when waypoint is reached
        unsigned char referenceMode; ///< 0 - absolute, 1 - platform, 2 - platform with heading
        long referencePlatform; ///< for referenced waypoints, -1 if absolute pos
        float bearing_rad;
        float range_km;
    };
    void AddWaypoint(double lon_rad, double lat_rad, float alt_m, float speed_kts);
    void ClearWaypoints();
    void DeleteWaypoint(size_t idx);
	void EditWaypoint(size_t idx, double lon_rad, double lat_rad, float alt_m, float speed_kts);
    void InsertWaypoint(size_t idx, double lon_rad, double lat_rad, float alt_m, float speed_kts);
    size_t GetWaypointCount() const;

    void SetWaypointTasklist(size_t idx, const std::string& tasklist);
    const std::vector<std::string>& GetWaypointTasklist(size_t idx) const;
    const char* GetWaypointTasklistString(size_t idx) const;
    void AddWaypointTask(size_t idx, const std::string& task);
    void RemoveWaypointTask(size_t idx, const std::string& task);

	unsigned GetCurrentWaypoint() const;
    void SetCurrentWaypoint(unsigned int idx);
	bool GetLoopState() const;
    const std::vector<WaypointData>& GetWaypoints() const;
    std::vector<WaypointData>& GetWaypointsMutable();
	void SetLoopState(bool state);
    
    void EditWaypointReference(size_t idx, unsigned char referenceMode, long referencePlatform);
    void UpdateRelativeWaypointCoordinate(size_t idx);
    void UpdateRelativeWaypointOffset(size_t idx);

    void SetMaxPathAltitude_m(float alt_m);
    float GetMaxPathAltitude_m() const;
    bool IsPathfindingActive() const;
    void SetPlatformId(long id);

    tcCommandStream& operator<<(tcCommandStream& stream);
    tcCommandStream& operator>>(tcCommandStream& stream);

    tcGameStream& operator<<(tcGameStream& stream);
	tcGameStream& operator>>(tcGameStream& stream);

    Route& operator=(const Route& rhs);

    Route(const Route& src);
    Route();
    virtual ~Route();
    
protected:
    std::vector<WaypointData> waypoints;
    unsigned currentWaypoint;
	bool loop; ///< true to loop back to first waypoint
    float maxPathAltitude_m;
    long platformId; ///< for getting current position, pathfinding with first waypoint

    bool GetBestPath(const WaypointData& destination, std::vector<WaypointData>& newPoints);
};



}

#endif