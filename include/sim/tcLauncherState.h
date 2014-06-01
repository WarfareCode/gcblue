/** 
**  @file tcLauncherState.h
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

#ifndef _TCLAUNCHERSTATE_H_
#define _TCLAUNCHERSTATE_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "simmath.h"
#include "AError.h"
#include "tcCommandObject.h"
#include <vector>

namespace database
{
    class tcDatabase;
    class tcLauncherDBObject;
    class tcDatabaseObject;
    enum teWeaponLaunchMode;
}

using namespace database;

class tcGameObject;
class tcPlatformObject;
class tcSimState;
class tcSensorState;
class tcStream;
class tcCommandStream;
class tcCreateStream;
class tcUpdateStream;
class tcGameStream;
class tcLauncher;


/**
 * Holds the state for all launchers on a platform.
 */
class tcLauncherState 
{
public:
    tcPlatformObject* parent;
    int mnCount;

    static tcDatabase *mpDatabase;

    static void AttachSimState(tcSimState* ss) {simState = ss;}

    void AddFullLauncher(long anKey, float azimuth_rad, float elevation_rad, float fov_deg,
		const std::string& displayName, bool isReloadable);
	float EstimateInterceptTimeForLauncher(unsigned nLauncher, tcTrack& track);
	tcLauncher* GetLauncher(unsigned int nLauncher);
    const tcLauncher* GetLauncher(unsigned nLauncher) const;
    std::string GetLauncherChildClass(unsigned nLauncher) const;
    unsigned int GetLauncherCount() const;
    int GetLauncherQuantity(unsigned anLauncher) const;
    int GetLauncherStatus(unsigned nLauncher);
    std::string GetLaunchMode(unsigned anLauncher);
    bool IsDatumLaunch(unsigned anLauncher);
    bool IsSeekerLaunch(unsigned anLauncher);

    void Launch(long& key, unsigned& nLauncher); ///< needs to be reworked

    tcCommandStream& operator<<(tcCommandStream& stream);
    tcUpdateStream& operator<<(tcUpdateStream& stream);
    tcGameStream& operator<<(tcGameStream& stream);

    tcCommandStream& operator>>(tcCommandStream& stream);
    tcUpdateStream& operator>>(tcUpdateStream& stream);
    tcGameStream& operator>>(tcGameStream& stream);

    void ClearNewCommand();
    bool HasNewCommand() const;

    void Serialize(tcFile& file, bool abLoad);
    void SetFireControlSensor(unsigned nLauncher, tcSensorState* sensor, unsigned sensorIdx);
    int SetLaunch(int nLauncher, int quantity);
    bool SetLauncherDatum(unsigned nLauncher, 
		double lon_rad, double lat_rad, float alt_m);
    bool SetLauncherTarget(unsigned nLauncher, long targetID);
    void SetParent(tcPlatformObject *obj) {parent = obj;}
    static std::string TranslateLauncherStatus(int status);
    void Update(float dt_s);

    tcLauncherState();
    tcLauncherState(tcPlatformObject* parentObj);
    tcLauncherState(tcLauncherState&);
    ~tcLauncherState();

private:
    std::vector<tcLauncher*> launchers; ///< vector of launcher state info
    tcCommandObject commandObj; 
    static tcSimState *simState;

    int GetLauncherFlag(int nLauncher) const {return 0x01 << nLauncher;}
};
#endif