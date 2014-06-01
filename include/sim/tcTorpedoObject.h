/**
**  @file tcTorpedoObject.h
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

#if _MSC_VER > 1000
#pragma once
#endif

#ifndef _TCTORPEDOOBJECT_H_
#define _TCTORPEDOOBJECT_H_

#include "tcSensorPlatform.h"
#include "tcWeaponObject.h"
#include "tcGuidanceState.h"
#include "tcSonar.h"

class tcUpdateStream;
class tcGameStream;

namespace database
{
    class tcTorpedoDBObject;
}

/**
* A class that models a torpedo.
*
* @see tcGameObject
*/
class tcTorpedoObject : public tcWeaponObject, public tcSensorPlatform
{
public:
    /**
    * Search mode code for torpedo
    */
    enum TorpedoSearchMode
    {
        SEARCH_STRAIGHT = 0,
        SEARCH_SNAKE = 1,
        SEARCH_LEFTCIRCLE = 2, 
        SEARCH_RIGHTCIRCLE = 3
    };
    float goalDepth_m;
    float goalHeading_rad;
    float goalPitch_rad;
    float goalSpeed_kts; 
    double interceptTime;
    float runTime; ///< [s] time elapsed since launch
	float searchStartTime; ///< [s] run time that search started, used for heading guidance


	// are all 3 of these necessary? needs refactoring
    double lastGuidanceUpdate;
    float guidanceUpdateInterval;

    GeoPoint waypoint;   // nav datum
    float runToEnable_m;   
    float ceiling_m; // min depth
    float floor_m; // max depth
    bool isWireActive; // true if wire is available to receive remote commands
    bool autoWireUpdates; ///< true to automatically update guidance based on intended target and sensor map

    tcSonar* seeker;

    float battery_kJ;  ///< current battery charge
    float searchHeading_rad; ///< center of "S" sector to search
    int searchMode;

    tcTorpedoDBObject *mpDBObject; // pointer to valid database obj

    void Clear();
	virtual void LaunchFrom(tcGameObject* obj, unsigned nLauncher);
    void RandInitNear(float afLon_deg, float afLat_deg);

    virtual void Update(double afStatusTime);
    virtual void UpdateEffects();
    virtual void UpdateGuidance(double t);

    void SetAltitude(float alt_m);
    virtual void SetHeading(float newHeading);
    virtual void SetSpeed(float newSpeed);
    virtual tcSonar* GetSensorState();
	virtual float GetSonarSourceLevel(float az_deg) const;
    virtual void DesignateTarget(long anID);
    virtual int GetGuidanceParameters(tsGuidanceParameters& gp);
    float RuntimeRemaining();
    void PrintToFile(tcFile&);
    void SaveToFile(tcFile& file);
    void LoadFromFile(tcFile& file);
    virtual void Serialize(tcFile& file, bool mbLoad);

    virtual tcUpdateStream& operator<<(tcUpdateStream& stream);
    virtual tcUpdateStream& operator>>(tcUpdateStream& stream);
    virtual tcGameStream& operator<<(tcGameStream& stream);
    virtual tcGameStream& operator>>(tcGameStream& stream);

    tcTorpedoObject();
    tcTorpedoObject(tcTorpedoObject&);
    tcTorpedoObject(tcTorpedoDBObject *obj);
    ~tcTorpedoObject();
protected:
    virtual void UpdateDrop(float dt_s);
    virtual void UpdateSpeedSimple(float dt_s);
    void UpdateDetonation();
	void UpdateDetonationUnguided();
    void UpdateDepthCharge(float dt_s);
	void UpdateDepthChargeDetonation();
    void UpdateBottomMine(float dt_s);
    void UpdateBottomMineTrigger(double t);
    void UpdateAutoWireGuidance();

};
#endif