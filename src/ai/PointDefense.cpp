/**
**  @file PointDefense.cpp
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

#include "ai/PointDefense.h"
#include "ai/Brain.h"
#include "scriptinterface/tcPlatformInterface.h"
#include "simmath.h"
#include "tcSensorMapTrack.h"
#include "tcWeaponDBObject.h"
#include "tcLauncher.h"

#include "common/tcStream.h"
#include "common/tcObjStream.h"
#include "common/tcGameStream.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif 

using namespace ai;
using scriptinterface::tcPlatformInterface;
using scriptinterface::tcTrackList;

/**
* Saves state to command stream
*/
tcCommandStream& PointDefense::operator>>(tcCommandStream& stream)
{
    return stream;
}

/**
* Loads state to command stream
*/
tcCommandStream& PointDefense::operator<<(tcCommandStream& stream)
{
    return stream;
}



/**
* Read from stream
*/
tcGameStream& PointDefense::operator<<(tcGameStream& stream)
{
    Task::operator<<(stream);
    
    return stream;
}

/**
* Write to stream
*/
tcGameStream& PointDefense::operator>>(tcGameStream& stream)
{
    Task::operator>>(stream);

    return stream; 
}

void PointDefense::GetPointDefenseLaunchers(std::vector<unsigned int>& launchers)
{
    wxASSERT(platform != 0);

    unsigned int nLaunchers = platform->GetLauncherCount();
    for (unsigned int n=0; n<nLaunchers; n++)
    {
        tcLauncher* launcher = platform->GetLauncher(n);
        tcWeaponDBObject* weaponData = dynamic_cast<tcWeaponDBObject*>(launcher->mpChildDBObj);

        unsigned char launcherStatus = launcher->GetStatus(); // doesn't update, returns last status
        bool statusOkay = true;
        switch (launcherStatus)
        {
        case tcLauncher::BAD_LAUNCHER:
        case tcLauncher::LAUNCHER_EMPTY:
        case tcLauncher::LAUNCHER_BUSY:
        case tcLauncher::LAUNCHER_ERROR:
        case tcLauncher::LAUNCHER_INACTIVE:
        case tcLauncher::NO_FIRECONTROL:
        case tcLauncher::DAMAGED:
        case tcLauncher::LAUNCHER_LOADING:
        case tcLauncher::LAUNCHER_UNLOADING:
        case tcLauncher::LAUNCHER_EMPTY_AUTORELOAD:
            statusOkay = false;
            break;
        default:
            statusOkay = true;
            break;
        }

        if (((launcher->mnTargetFlags & 0x0008) != 0) && (weaponData != 0) && (weaponData->minRange_km < 1.0f) &&
            statusOkay)
        {
            launchers.push_back(n);
        }
    }
}


void PointDefense::GetPointDefenseTargets(std::vector<tcSensorMapTrack>& targets, tcPlatformInterface& platformInterface)
{
    const float maxRange_km = 12.0f;
    tcTrackList trackList = platformInterface.GetTrackListValidROE(0x0060, maxRange_km);
    for (size_t n=0; n<trackList.track.size(); n++)
    {
        tcSensorMapTrack& track = trackList.track[n];
        double staleness_s = track.mfTimestamp - track.GetLastReportTime();
        bool valid = (!track.IsDestroyed()) && (staleness_s < 15.0f);
        if (valid)
        {
            targets.push_back(track);
        }
    }
}

void PointDefense::Update(double t)
{
    if (!IsReadyForUpdate(t)) return;


    // return if conn is locked by another higher priority task
    //if (!Write("ConnLock", "")) return; 

    if (platform == 0)
    {
        wxASSERT(false);
        return;
    }
    tcPlatformInterface platformInterface = GetPlatformInterface();

    std::vector<tcSensorMapTrack> targets;
    GetPointDefenseTargets(targets, platformInterface);

    if (targets.size() == 0)
    {
        SetUpdateInterval(10.0f);
        return;
    }
    else
    {
        SetUpdateInterval(2.0f);
    }

    std::vector<unsigned int> launchers;
    GetPointDefenseLaunchers(launchers);

    for (size_t n=0; n<launchers.size(); n++)
    {
        unsigned int launcher_idx = launchers[n];

        size_t nTargets = targets.size();
        size_t random_offset = rand() % nTargets;
        bool lookingForTarget = true;
        for (size_t k=0; (k<nTargets) && lookingForTarget; k++)
        {
            size_t target_idx = (k + random_offset) % nTargets;
            long targetId = targets[target_idx].mnID;
            platform->DesignateLauncherTarget(targetId, launcher_idx);

            GeoPoint p(targets[target_idx].mfLon_rad, targets[target_idx].mfLat_rad, targets[target_idx].mfAlt_m);
            platform->DesignateLauncherDatum(p, launcher_idx);

            tcLauncher* launcher = platform->GetLauncher(launcher_idx);
            launcher->UpdateStatus();
            unsigned char launcherStatus = launcher->GetStatus();
            if (launcherStatus == tcLauncher::LAUNCHER_READY)
            {
                lookingForTarget = false;
                platform->SetLaunch(launcher_idx, 8);
            }
        }
    }

    FinishUpdate(t);
}

PointDefense::PointDefense(tcPlatformObject* platform_, Blackboard* bb, 
                                   long id_, double priority_, int attributes_, const std::string& taskName_)
: Task(platform_, bb, id_, priority_, attributes_, taskName_)
{
    wxASSERT(platform);
}



PointDefense::~PointDefense()
{
}



