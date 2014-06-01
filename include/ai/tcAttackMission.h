/**
**  @file tcAttackMission.h
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

#ifndef _TCATTACKMISSION_H_
#define _TCATTACKMISSION_H_

#include "ai/tcMission.h"
#include "simmath.h"
#include "tcDateTime.h"

class tcFlightPort;
class tcPoint;
class tcStream;
class tcGameStream;
class tcAirObject;

namespace scriptinterface
{
    class tcScenarioLogger;
}

namespace ai {

class BlackboardInterface;

/**
* Modified starting FEB 2009 to make this handle a variety of mission types
*/
class tcAttackMission : public tcMission
{
public:
	enum {NO_ANCHOR=0, NORTH_ANCHOR=1, HEADING_ANCHOR=2};
	void SetTargetDatum(float lon_rad, float lat_rad); // target for bombing or general area to search
    float GetTargetLon() const;
    float GetTargetLat() const;
    bool HasTarget() const;
    bool HasTargetDatum() const;

    void SetLaunchTime(const tcDateTime& dateTime);
    const tcDateTime& GetLaunchTime() const;
    void AdjustLaunchTimeHours(double offset_hr);

    void SetRandomLaunchTime(const tcDateTime& earliest, float window_min);
    const char* GetLaunchTimeString() const;
    void SetLaunchTimeFromString(const char* s);

    long GetSecondsToLaunch() const;

    unsigned int GetAirborneAircraftCount() const;

    void SetLandingTarget(const std::string& s);
    const std::string& GetLandingTarget() const;

    void SetArea(const std::vector<GeoPoint>& area);
    void SetAreaByString(const std::string& s);
    const char* GetAreaString() const;
    const std::vector<GeoPoint>& GetArea() const;
	void GetAreaCenter(double& lon_rad, double& lat_rad);
	void RecenterArea(double lon_rad, double lat_rad);
	void UpdateInFlightAircraft();

    void SetPatrolAnchor(const std::string& unitName, int mode);
    const std::string& GetPatrolAnchorUnit() const;
    int GetPatrolAnchorMode() const;
    void TransformToRelativePatrolArea();
    void TransformToAbsolutePatrolArea();

    unsigned int GetWaveQuantity() const;
    void SetWaveQuantity(unsigned int val);

    void SetMissionType(const std::string& s);
    const char* GetMissionType() const;

	void SetTargetType(int val);
	int GetTargetType() const;

	void SetAutoAdd(bool state);
	bool GetAutoAdd() const;

	void SetRepeatIntervalHours(float val);
	float GetRepeatIntervalHours() const;

	virtual void Update(double t);

    void UpdateRelativePosition();

    void SaveToPython(scriptinterface::tcScenarioLogger& logger);

    virtual tcGameStream& operator<<(tcGameStream& stream);
    virtual tcGameStream& operator>>(tcGameStream& stream);

	const tcAttackMission& operator=(const tcAttackMission& src);
	tcAttackMission(const tcAttackMission& src);
    tcAttackMission(unsigned int id_, tcMissionManager* mm);
	tcAttackMission();
	virtual ~tcAttackMission();

protected:
    tcDateTime earliestLaunchTime; ///< earliest time for random launch
    float launchWindow_min; ///< randomly pick a time between earliest and earliest + launchWindow
    tcDateTime launchTime; // actual time to start launching mission aircraft
    float repeatInterval_hr; ///< 0 for no repeat, number of hours after launch to re-launch mission

	unsigned int quantity; // number aircraft for mission
    int targetType; ///< derived
	bool autoAdd; ///< automatically add aircraft based on target type

    float targetLon_rad;
    float targetLat_rad;
    std::string landingTarget; ///< unit to land on
    std::vector<GeoPoint> patrolArea; ///< patrol area
    std::string patrolAnchorUnit;
    int patrolAnchorMode; ///< enum {NO_ANCHOR=0, NORTH_ANCHOR=1, HEADING_ANCHOR=2};
    std::string missionType; // type string to pass info to script mission planner template

    // keep route relative to host platform if patrolAnchorMode != 0
    GeoPoint referencePosition;
    float referenceHeading_rad;

    virtual void AddMissionAircraft(const std::string& name, const std::string& role);
    virtual void RemoveMissionAircraft(const std::string& name);

    void UpdateTargetInfo();
    void RemoveInactiveAircraft();
	void MonitorMissionInProgress();
    void InitializeLaunchTime();
	void UploadUnitMissionInfo(tcAirObject* air);
    void UploadUnitPatrolInfo(ai::BlackboardInterface& bb);
    void GetReadyAircraft(std::vector<unsigned int>& readyAircraft);
    void GetAircraftToLoad(std::vector<unsigned int>& loadTheseAircraft);
    void UpdateActiveAircraft(unsigned int& nActive);
    void ReadyAllAircraft();
    void ReadyOverweightAircraft();
    
    void GetAreaBounds(tcGeoRect& r);
    bool MissionTypeIsReady();
    

};

} // namespace


#endif