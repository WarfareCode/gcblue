/**  
**  @file tcGoal.h
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


#ifndef _TCGOAL_H_
#define _TCGOAL_H_

#ifdef WIN32
#pragma once
#endif

#include <vector>
#include <boost/python.hpp>
#include "simmath.h"

class tcSimState;
class tcGameStream;
class tcMapOverlay;

namespace boost
{
    namespace python
    {
        class dict;
    }
}
namespace scriptinterface
{
	class tcScenarioLogger;
}

void InitGoalPython();

class tcGoalWrap;

class tcGoal
{
public:
    enum
    {
        UNRESOLVED = 0,
        FAILED = 1,
        PASSED = 2,
    };
    enum
    {
        GOAL = 0, // should not have leaf of tcGoal
        COMPOUND = 1,
        TIME = 2,
        DESTROY = 3,
        PROTECT = 4,
        AREA = 5
    };
    int goalState;

    static tcSimState *simState;
    
    static void AttachSimState(tcSimState *ss) {simState = ss;}
    static tcGoal* CreateByType(int goalType); ///< factory method

	std::string GoalStateToString(int goalState);
    bool IsFailed() {return goalState == FAILED;}
    bool IsPassed() {return goalState == PASSED;}
    bool IsUnresolved() {return goalState == UNRESOLVED;}
    virtual void Update(); ///< updates goal state using on simState
	virtual void WriteStatus(std::stringstream& stream, unsigned int level = 0);
    virtual void WriteStatusB(std::stringstream& stream);

	virtual void WriteStatus(wxArrayString& arrayString, unsigned int level = 0);
    virtual void WriteStatusB(wxArrayString& arrayString);

	virtual void SaveToPython(scriptinterface::tcScenarioLogger& logger);
    virtual float GetNetScore() const;
    void SetScores(float fail, float pass);

    virtual void SetAlliance(unsigned int alliance_);
    unsigned int GetAlliance() const;

    virtual void RenameTarget(const std::string& oldName, const std::string& newName);

    virtual tcGoal* Clone();
    virtual int GetType() const;
    virtual std::string GetTypeString() const;
    unsigned long GetId() const;

    virtual tcGameStream& operator>>(tcGameStream& stream);
    virtual tcGameStream& operator<<(tcGameStream& stream);

    static void AttachMapOverlay(tcMapOverlay* overlay);

    tcGoal();
    tcGoal(const tcGoal& goal);
    virtual ~tcGoal();
protected:
    static unsigned long nextId;
    static tcMapOverlay* mapOverlay;

	const std::string indentString;
    float failScore;
    float passScore;
    unsigned long id; // id for each goal
    long mapObjectId; ///< tcRegistered window id for goals with active GUI object
    unsigned int alliance;

    void CloseMapObject();
};


/**
* goal to hold group of goals
*/
class tcCompoundGoal : public tcGoal
{
public:
    enum
    {
        AND = 0,
        OR = 1
    };
    int logicType; ///< AND or OR
    std::vector<tcGoal*> children;

    void AddGoal(tcGoal& newGoal);
    void AddGoalByPtr(tcGoal* newGoal);
    void RemoveGoal(int idx) {children.erase(children.begin() + idx);}
    void SetLogic(int logic) {logicType = logic;}
    virtual float GetNetScore() const;

    virtual void Update(); ///< updates goal state using on simState
	virtual void WriteStatus(std::stringstream& stream, unsigned int level = 0);
    virtual void WriteStatusB(std::stringstream& stream);
	virtual void WriteStatus(wxArrayString& arrayString, unsigned int level = 0);
    virtual void WriteStatusB(wxArrayString& arrayString);

	virtual void SaveToPython(scriptinterface::tcScenarioLogger& logger);

    unsigned int GetSubGoalCount() const;
    tcGoalWrap GetSubGoal(unsigned int idx);

    virtual void RenameTarget(const std::string& oldName, const std::string& newName);
    virtual void SetAlliance(unsigned int alliance_);

    virtual tcGoal* Clone();
    virtual int GetType() const;
    virtual std::string GetTypeString() const;

    virtual tcGameStream& operator>>(tcGameStream& stream);
    virtual tcGameStream& operator<<(tcGameStream& stream);

    tcCompoundGoal(int type = AND);
    tcCompoundGoal(const tcCompoundGoal& goal);
    virtual ~tcCompoundGoal();

protected:
	static unsigned pythonWriteCount; ///< used to handle nested compound goals in SaveToPython
};

/**
* goal for pass/fail timeout
*/
class tcTimeGoal : public tcGoal
{
public:
    double failTimeout; ///< value in elapsed seconds
    double passTimeout;

    const double disabledTime_s;

    void SetFailTimeout(double t);
    void SetPassTimeout(double t);
    virtual void Update(); ///< updates goal state using on simState
	virtual void WriteStatus(std::stringstream& stream, unsigned int level = 0);
    virtual void WriteStatusB(std::stringstream& stream);

	virtual void WriteStatus(wxArrayString& arrayString, unsigned int level = 0);
    virtual void WriteStatusB(wxArrayString& arrayString);

	virtual void SaveToPython(scriptinterface::tcScenarioLogger& logger);

    virtual tcGoal* Clone();
    virtual int GetType() const;
    virtual std::string GetTypeString() const;

    virtual tcGameStream& operator>>(tcGameStream& stream);
    virtual tcGameStream& operator<<(tcGameStream& stream);

    tcTimeGoal();
    tcTimeGoal(const tcTimeGoal& goal);
    virtual ~tcTimeGoal();
};

/**
* goal to destroy specific unit or set of units
*/
class tcDestroyGoal : public tcGoal
{
public:
    std::vector<std::string> targetList;
    unsigned int quantity; // number of targets required to satisfy goal

    virtual void Update();

	virtual void WriteStatus(std::stringstream& stream, unsigned int level = 0);
    virtual void WriteStatusB(std::stringstream& stream);
	virtual void WriteStatus(wxArrayString& arrayString, unsigned int level = 0);
    virtual void WriteStatusB(wxArrayString& arrayString);

	virtual void SaveToPython(scriptinterface::tcScenarioLogger& logger);

    virtual void RenameTarget(const std::string& oldName, const std::string& newName);

    virtual void AddTarget(const std::string& s);
    virtual void RemoveTarget(const std::string& s);

    virtual void SetQuantity(unsigned int val);
    virtual unsigned int GetQuantity() const;

    virtual const wxString& GetTargetDescription() const;

    unsigned int GetTargetCount() const;
    std::string GetTargetName(unsigned int index);

    virtual tcGoal* Clone();
    virtual int GetType() const;
    virtual std::string GetTypeString() const;

    virtual tcGameStream& operator>>(tcGameStream& stream);
    virtual tcGameStream& operator<<(tcGameStream& stream);

    tcDestroyGoal() {};
    tcDestroyGoal(const tcDestroyGoal& goal);
    tcDestroyGoal(const std::string& s);
};

/**
* goal to protect specific unit or set of units
*/
class tcProtectGoal : public tcGoal
{
public:
    std::vector<std::string> targetList;
    unsigned int quantity; // number of targets required to satisfy goal

    virtual void Update();

	virtual void WriteStatus(std::stringstream& stream, unsigned int level = 0);
    virtual void WriteStatusB(std::stringstream& stream);
	virtual void WriteStatus(wxArrayString& arrayString, unsigned int level = 0);
    virtual void WriteStatusB(wxArrayString& arrayString);

	virtual void SaveToPython(scriptinterface::tcScenarioLogger& logger);

    virtual void RenameTarget(const std::string& oldName, const std::string& newName);

    virtual void AddTarget(const std::string& s);
    virtual void RemoveTarget(const std::string& s);

    virtual void SetQuantity(unsigned int val);
    virtual unsigned int GetQuantity() const;

    virtual const wxString& GetTargetDescription() const;

    unsigned int GetTargetCount() const;
    std::string GetTargetName(unsigned int index);

    virtual tcGoal* Clone();
    virtual int GetType() const;
    virtual std::string GetTypeString() const;

    virtual tcGameStream& operator>>(tcGameStream& stream);
    virtual tcGameStream& operator<<(tcGameStream& stream);

    tcProtectGoal() {};
    tcProtectGoal(const tcProtectGoal& goal);
    tcProtectGoal(const std::string& s);
};

/**
* Goal to enter or avoid a geographical area
*/
class tcAreaGoal : public tcGoal
{
public:
    wxArrayString targetList; ///< OR logic, so any one of these will trigger goal
    unsigned int quantity; // number of targets required to satisfy goal
	float timeObjective_s; ///< goal must be achieved for this amount of time to activate
    double startTime_s; ///< time started progress toward timeObjective_s
	bool isOR; ///< true for "OR" logic for targets in targetList
    std::vector<GeoPoint> areaBounds;
    bool isEnterGoal; ///< true if goal to enter area, false to avoid
    unsigned int alliance;

    void Clear();
    void AddPoint(float lon_rad, float lat_rad);
    void AddPointDeg(float lon_deg, float lat_deg);
    
    virtual void Update();
	
    virtual void WriteStatus(std::stringstream& stream, unsigned int level = 0);
    virtual void WriteStatusB(std::stringstream& stream);
	virtual void WriteStatus(wxArrayString& arrayString, unsigned int level = 0);
    virtual void WriteStatusB(wxArrayString& arrayString);

	virtual void SaveToPython(scriptinterface::tcScenarioLogger& logger);

    virtual void RenameTarget(const std::string& oldName, const std::string& newName);
    void SetEnterGoal(bool state);
    
    void SetTargetList(const std::string& targets);
    void AddToTargetList(const std::string& s);
    std::string GetTargetListAsString() const;

    virtual void SetQuantity(unsigned int val);
    virtual unsigned int GetQuantity() const;

	void SetTimeObjective(float t_s);
	float GetTimeObjective() const;

	void SetLogicAny(bool state);
	bool IsLogicAny() const;

    bool IsObjectWithinArea(const tcGameObject* obj) const;
    static bool IsPointWithinArea(const std::vector<GeoPoint>& area, float lon_rad, float lat_rad);
    static GeoPoint GetRandomPointWithinArea(const std::vector<GeoPoint>& area);

    void UpdateMapObject();

    virtual tcGoal* Clone();
    virtual int GetType() const;
    virtual std::string GetTypeString() const;
    const char* GetQuantityDescription() const;

    virtual tcGameStream& operator>>(tcGameStream& stream);
    virtual tcGameStream& operator<<(tcGameStream& stream);

    tcAreaGoal(const tcAreaGoal& goal);
    tcAreaGoal();
};




class tcCompoundGoalWrap
{
public:
    int GetLogicType() const;
    void SetLogicType(int val);
    void AddGoal(tcGoal& newGoal);
    unsigned int GetSubGoalCount() const;
    tcGoalWrap GetSubGoal(unsigned int idx);
    unsigned long GetId() const;

    tcCompoundGoalWrap(tcCompoundGoal* g);    
    tcCompoundGoalWrap();
    virtual ~tcCompoundGoalWrap();
private:
    tcCompoundGoal* compoundGoal;
};

class tcTimeGoalWrap
{
public:
    double GetFailTimeout() const;
    void SetFailTimeout(double t);
    double GetPassTimeout() const;
    void SetPassTimeout(double t);
    unsigned long GetId() const;

    tcTimeGoalWrap(tcTimeGoal* g);    
    tcTimeGoalWrap();
    virtual ~tcTimeGoalWrap();
private:
    tcTimeGoal* timeGoal;
};

class tcDestroyGoalWrap
{
public:
    void AddTarget(const std::string& s);
    void RemoveTarget(const std::string& s);
    void SetQuantity(unsigned int val);
    unsigned int GetQuantity() const;
    unsigned int GetTargetCount() const;
    std::string GetTargetName(unsigned int index);
    unsigned long GetId() const;

    tcDestroyGoalWrap(tcDestroyGoal* g);    
    tcDestroyGoalWrap();
    virtual ~tcDestroyGoalWrap();
private:
    tcDestroyGoal* destroyGoal;
};

class tcProtectGoalWrap
{
public:
    void AddTarget(const std::string& s);
    void RemoveTarget(const std::string& s);
    void SetQuantity(unsigned int val);
    unsigned int GetQuantity() const;
    unsigned int GetTargetCount() const;
    std::string GetTargetName(unsigned int index);
    unsigned long GetId() const;

    tcProtectGoalWrap(tcProtectGoal* g);    
    tcProtectGoalWrap();
    virtual ~tcProtectGoalWrap();
private:
    tcProtectGoal* protectGoal;
};

class tcAreaGoalWrap
{
public:
    std::string GetTargetString() const;
    void SetTargetList(const std::string& s);
    void AddToTargetList(const std::string& s);
    void Clear();
    void AddPoint(float lon_rad, float lat_rad);
    void AddPointDeg(float lon_deg, float lat_deg);
    void SetEnterGoal(bool state);
    bool GetEnterGoal() const;
	void SetTimeObjective(float t_s);
	float GetTimeObjective() const;
	void SetLogicAny(bool state);
	bool IsLogicAny() const;
    void SetQuantity(unsigned int val);
    unsigned int GetQuantity() const;

    unsigned long GetId() const;

    tcAreaGoalWrap(tcAreaGoal* g);    
    tcAreaGoalWrap();
    virtual ~tcAreaGoalWrap();
private:
    tcAreaGoal* areaGoal;
};



class tcGoalWrap
{
public:
    unsigned long GetId() const;
    std::string GetTypeString() const;
    tcCompoundGoalWrap AsCompoundGoal();
    tcTimeGoalWrap AsTimeGoal();
    tcDestroyGoalWrap AsDestroyGoal();
    tcProtectGoalWrap AsProtectGoal();
    tcAreaGoalWrap AsAreaGoal();

    tcGoalWrap(tcGoal* g);    
    tcGoalWrap();
    virtual ~tcGoalWrap();
private:
    tcGoal* goal;
};


#endif