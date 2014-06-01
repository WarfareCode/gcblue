/**
**  @file Nav.cpp
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

#include "ai/Nav.h"
#include "ai/Brain.h"
#include "scriptinterface/tcPlatformInterface.h"
#include "simmath.h"

#include "common/tcStream.h"
#include "common/tcObjStream.h"
#include "common/tcGameStream.h"
#include "tcShipDBObject.h"
#include "tcSubDBObject.h"
#include "tcCarrierObject.h"
#include "tcSurfaceObject.h"
#include "tcSubObject.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif 

using namespace ai;
using scriptinterface::tcPlatformInterface;


/**
* Saves state to command stream
* Used to save waypoints for client to display
*/
tcCommandStream& Nav::operator>>(tcCommandStream& stream)
{
    Route::operator>>(stream);
	
	return stream;
}

/**
* Loads state to command stream
* Used to load waypoints for client to display
*/
tcCommandStream& Nav::operator<<(tcCommandStream& stream)
{
    Route::operator<<(stream);

	return stream;
}



/**
* Read from stream
*/
tcGameStream& Nav::operator<<(tcGameStream& stream)
{
    Task::operator<<(stream);

    Route::operator<<(stream);
    
    return stream;
}

/**
* Write to stream
*/
tcGameStream& Nav::operator>>(tcGameStream& stream)
{
    Task::operator>>(stream);

    Route::operator>>(stream);

    return stream; 
}


void Nav::AddTasksForCurrentWaypoint()
{
    if ((platform != 0) && (currentWaypoint < waypoints.size()))
    {
        for (size_t n=0; n<waypoints[currentWaypoint].tasks.size(); n++)
        {
            platform->GetBrain()->AddTask(waypoints[currentWaypoint].tasks[n], 4.0f, 0);
        }
    }
}



void Nav::AddWaypoint(double lon_rad, double lat_rad, float alt_m, float speed_kts)
{
    Route::AddWaypoint(lon_rad, lat_rad, alt_m, speed_kts);

	platform->GetBrain()->SetNewCommand();
}

void Nav::ClearWaypoints()
{
	if (waypoints.size())
	{
	    platform->GetBrain()->SetNewCommand();
	}

    Route::ClearWaypoints();
}

void Nav::DeleteWaypoint(size_t idx)
{
    if (idx < waypoints.size())
	{
        Route::DeleteWaypoint(idx);
		
		platform->GetBrain()->SetNewCommand();
	}
	else
	{
		fprintf(stderr, "Nav::DeleteWaypoint - bad idx\n");
	}
}

void Nav::EditWaypoint(size_t idx, double lon_rad, double lat_rad, float alt_m, float speed_kts)
{
	if (idx < waypoints.size())
	{
        Route::EditWaypoint(idx, lon_rad, lat_rad, alt_m, speed_kts);
		
		platform->GetBrain()->SetNewCommand();
	}
	else
	{
		fprintf(stderr, "Nav::EditWaypoint - bad idx\n");
	}
}

void Nav::EditWaypointReference(size_t idx, unsigned char referenceMode, long referencePlatform)
{
    Route::EditWaypointReference(idx, referenceMode, referencePlatform);

    platform->GetBrain()->SetNewCommand();
}

/**
* Inserts waypoint before waypoint at idx
*/
void Nav::InsertWaypoint(size_t idx, double lon_rad, double lat_rad, float alt_m, float speed_kts)
{
	if (idx < waypoints.size())
	{
        Route::InsertWaypoint(idx, lon_rad, lat_rad, alt_m, speed_kts);
		
		platform->GetBrain()->SetNewCommand();
	}
	else
	{
		fprintf(stderr, "Nav::InsertWaypoint - bad idx\n");
	}
}

void Nav::SetRoute(const Route* route)
{
    Route::operator=(*route);
}


void Nav::Update(double t)
{
    if (!IsReadyForUpdate(t)) return;

    if (currentWaypoint >= waypoints.size())
    {
		if (loop)
		{
			currentWaypoint = 0;
			wxASSERT(waypoints.size() > 0);
		}
		else
		{
			EndTask();
			return;
		}
    }

    // update coordinates for all relative waypoints
    for (size_t n=0; n<waypoints.size(); n++)
    {
        Route::UpdateRelativeWaypointCoordinate(n);
    }

    // return if conn is locked by another higher priority task
    if (!Write("ConnLock", "")) return; 

    if (platform == 0)
    {
        wxASSERT(false);
        return;
    }
    tcPlatformInterface platformInterface = GetPlatformInterface();

    WaypointData& waypointData = waypoints[currentWaypoint];

    double lon_rad = waypointData.waypoint.mfLon_rad;
    double lat_rad = waypointData.waypoint.mfLat_rad;

    float heading_deg = platformInterface.GetHeadingToDatum(lon_rad, lat_rad);
    float range_m = 1000.0f * platformInterface.GetRangeToDatum(lon_rad, lat_rad);
    float speed_mps = C_KTSTOMPS * platformInterface.GetSpeed();
    float eta_s = (speed_mps > 0) ? (range_m / speed_mps) : 9999.0f;

    // apply speed/alt command from previous waypoint
    if (currentWaypoint > 0)
    {
        float alt_m = waypoints[currentWaypoint-1].waypoint.mfAlt_m;
        float speed_kts = waypoints[currentWaypoint-1].speed_kts;
        if (speed_kts > 0) platformInterface.SetSpeed(speed_kts);
        if ((alt_m > 0) || ((alt_m < 0) && platformInterface.IsSub()))
        {
            platformInterface.SetAltitude(alt_m);
        }
    }


    if (eta_s >= 30.0f)
    {
        SetUpdateInterval(20.0f);
    }
    else if (eta_s >= 2.0f)
    {
        SetUpdateInterval(1.0f);
    }
    else
    {
        bool isLastWaypoint = (currentWaypoint == (waypoints.size()-1)) && (!loop);

        SetUpdateInterval(1.0f);

        float alt_m = waypointData.waypoint.mfAlt_m;
        float speed_kts = waypointData.speed_kts;
        if (speed_kts > 0)
        {
            platformInterface.SetSpeed(speed_kts);
        }
        else if (isLastWaypoint && (platformInterface.IsHelo() || (platform->mnModelType == MTYPE_GROUNDVEHICLE)))
        {
            platformInterface.SetSpeed(0); // command helo to hover after reaching last waypoint
        }

        if ((alt_m > 0) || ((alt_m < 0) && platformInterface.IsSub()))
        {
            platformInterface.SetAltitude(alt_m);
        }

        AddTasksForCurrentWaypoint();
        currentWaypoint++;
    }

    platformInterface.SetHeading(heading_deg);

    FinishUpdate(t);
}

Nav::Nav(tcPlatformObject* platform_, Blackboard* bb, 
                                   long id_, double priority_, int attributes_, const std::string& taskName_)
: Task(platform_, bb, id_, priority_, attributes_, taskName_),
  Route()
{
    wxASSERT(platform);
    Route::SetPlatformId(platform->mnID);

    // set up automatic path finding
    if ((typeid(*platform) == typeid(tcCarrierObject)) ||
        (typeid(*platform) == typeid(tcSurfaceObject)))
    {
        if (tcShipDBObject* shipData = dynamic_cast<tcShipDBObject*>(platform->mpDBObject))
        {
            SetMaxPathAltitude_m(-(shipData->draft_m + 3.0f));
        }
    }


    if (typeid(*platform) == typeid(tcSubObject))
    {
        SetMaxPathAltitude_m(-18.0f);
    }
}



Nav::~Nav()
{
}



