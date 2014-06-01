/**
**  @file Nav.h
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

#ifndef _NAV_H_
#define _NAV_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "ai/Task.h"
#include "ai/Route.h"

#include <map>
#include <string>
#include <vector>
#include "simmath.h"



class tcPlatformObject;
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
class Nav : public Task, public Route
{
public:
    void AddWaypoint(double lon_rad, double lat_rad, float alt_m, float speed_kts);
    void ClearWaypoints();
    void DeleteWaypoint(size_t idx);
	void EditWaypoint(size_t idx, double lon_rad, double lat_rad, float alt_m, float speed_kts);
    void EditWaypointReference(size_t idx, unsigned char referenceMode, long referencePlatform);
    void InsertWaypoint(size_t idx, double lon_rad, double lat_rad, float alt_m, float speed_kts);
    
    void SetRoute(const Route* route); ///< set to match another route

    void AddTasksForCurrentWaypoint();

    void Update(double t);

    virtual tcCommandStream& operator<<(tcCommandStream& stream);
    virtual tcCommandStream& operator>>(tcCommandStream& stream);

    virtual tcGameStream& operator<<(tcGameStream& stream);
	virtual tcGameStream& operator>>(tcGameStream& stream);

    Nav(tcPlatformObject* platform_, Blackboard* bb, 
        long id_, double priority_, int attributes_, const std::string& taskName_);
    ~Nav();
    
private:
    
};



}

#endif