/**
**  @file tcGoal.cpp
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

#include "stdwx.h" // precompiled header file

#ifndef WX_PRECOMP
#include "wx/wx.h" 
#endif

#include "tcGoal.h"
#include "tcSimState.h"
#include "tcScenarioLogger.h"
#include "tcGameStream.h"
#include "tcGameObject.h"
#include "tcRegistered.h"
#include "tcMapOverlay.h"
#include "tcGoalAreaEditObject.h"
#include "tcGameObjIterator.h"

/***** expose classes to boost python *****/

#include <boost/python.hpp>
using namespace boost::python;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
/**
* Not sure how to best package this.
* This has to be called after python initialization.
* Initializes classes and adds class types to dictionary.
*/
void InitGoalPython()
{
    static object GoalType =
        class_<tcGoal>("Goal")
        .def_readwrite("goalState",&tcGoal::goalState)
        .def("SetScores",&tcGoal::SetScores)
        .def("GetId", &tcGoal::GetId)
        ;

    //PyDict_SetItemString(dictionary->ptr(), "goalx", GoalType.ptr());  // does not work right

    static object CompoundGoalType = 
        class_<tcCompoundGoal, bases<tcGoal> >("CompoundGoal", init<int>())
        .def_readwrite("logicType", &tcCompoundGoal::logicType)
        .def("AddGoal",&tcCompoundGoal::AddGoal)
        .def("RemoveGoal",&tcCompoundGoal::RemoveGoal)
        .def("SetLogic",&tcCompoundGoal::SetLogic)
        .def("GetSubGoalCount", &tcCompoundGoal::GetSubGoalCount)
        .def("GetSubGoal", &tcCompoundGoal::GetSubGoal)
        ;

    object TimeGoalType = 
        class_<tcTimeGoal, bases<tcGoal> >("TimeGoal")
        .def_readwrite("failTimeout", &tcTimeGoal::failTimeout)
        .def_readwrite("passTimeout", &tcTimeGoal::passTimeout)
        .def("SetFailTimeout",&tcTimeGoal::SetFailTimeout)
        .def("SetPassTimeout",&tcTimeGoal::SetPassTimeout)
        ;

    object DestroyGoalType = 
        class_<tcDestroyGoal, bases<tcGoal> >("DestroyGoal", init<std::string>())
        .def("GetTargetCount", &tcDestroyGoal::GetTargetCount)
        .def("GetTargetName", &tcDestroyGoal::GetTargetName)
        .def("GetQuantity", &tcDestroyGoal::GetQuantity)
        .def("SetQuantity", &tcDestroyGoal::SetQuantity)
        .def("AddTarget", &tcDestroyGoal::AddTarget)
        .def("RemoveTarget", &tcDestroyGoal::RemoveTarget)
        ;

	object ProtectGoalType = 
        class_<tcProtectGoal, bases<tcGoal> >("ProtectGoal", init<std::string>())
        .def("GetTargetCount", &tcProtectGoal::GetTargetCount)
        .def("GetTargetName", &tcProtectGoal::GetTargetName)
        .def("GetQuantity", &tcProtectGoal::GetQuantity)
        .def("SetQuantity", &tcProtectGoal::SetQuantity)
        .def("AddTarget", &tcProtectGoal::AddTarget)
        .def("RemoveTarget", &tcProtectGoal::RemoveTarget)
        ;

    object AreaGoalType = 
        class_<tcAreaGoal, bases<tcGoal> >("AreaGoal")
        .def("AddPoint", &tcAreaGoal::AddPoint)
        .def("AddPointDeg", &tcAreaGoal::AddPointDeg)
        .def("SetEnterGoal", &tcAreaGoal::SetEnterGoal)
        .def("SetTargetList", &tcAreaGoal::SetTargetList)
        .def("AddToTargetList", &tcAreaGoal::AddToTargetList)
        .def("SetQuantity", &tcAreaGoal::SetQuantity)
        .def("GetQuantity", &tcAreaGoal::GetQuantity)
		.def("SetTimeObjective", &tcAreaGoal::SetTimeObjective)
		.def("GetTimeObjective", &tcAreaGoal::GetTimeObjective)
		.def("SetLogicAny", &tcAreaGoal::SetLogicAny)
		.def("IsLogicAny", &tcAreaGoal::IsLogicAny)
        ;

    object GoalWrapType = 
        class_<tcGoalWrap>("GoalWrap")
        .def("GetId", &tcGoalWrap::GetId)
        .def("GetTypeString", &tcGoalWrap::GetTypeString)
        .def("AsCompoundGoal", &tcGoalWrap::AsCompoundGoal)
        .def("AsTimeGoal", &tcGoalWrap::AsTimeGoal)
        .def("AsDestroyGoal", &tcGoalWrap::AsDestroyGoal)
        .def("AsProtectGoal", &tcGoalWrap::AsProtectGoal)
        .def("AsAreaGoal", &tcGoalWrap::AsAreaGoal)
        ;

    object CompoundGoalWrapType = 
        class_<tcCompoundGoalWrap>("CompoundGoalWrap")
        .def("AddGoal", &tcCompoundGoalWrap::AddGoal)
        .def("GetLogicType", &tcCompoundGoalWrap::GetLogicType)
        .def("SetLogicType", &tcCompoundGoalWrap::SetLogicType)
        .def("GetSubGoalCount", &tcCompoundGoalWrap::GetSubGoalCount)
        .def("GetSubGoal", &tcCompoundGoalWrap::GetSubGoal)
        .def("GetId", &tcCompoundGoalWrap::GetId)
        ;

    object TimeGoalWrapType = 
        class_<tcTimeGoalWrap>("TimeGoalWrap")
        .def("GetFailTimeout", &tcTimeGoalWrap::GetFailTimeout)
        .def("SetFailTimeout", &tcTimeGoalWrap::SetFailTimeout)
        .def("GetPassTimeout", &tcTimeGoalWrap::GetPassTimeout)
        .def("SetPassTimeout", &tcTimeGoalWrap::SetPassTimeout)
        .def("GetId", &tcTimeGoalWrap::GetId)
        ;

    object DestroyGoalWrapType = 
        class_<tcDestroyGoalWrap>("DestroyGoalWrap")
        .def("AddTarget", &tcDestroyGoalWrap::AddTarget)
        .def("RemoveTarget", &tcDestroyGoalWrap::RemoveTarget)
        .def("SetQuantity", &tcDestroyGoalWrap::SetQuantity)
        .def("GetQuantity", &tcDestroyGoalWrap::GetQuantity)
        .def("GetTargetCount", &tcDestroyGoalWrap::GetTargetCount)
        .def("GetTargetName", &tcDestroyGoalWrap::GetTargetName)
        .def("GetId", &tcDestroyGoalWrap::GetId)
        ;

    object ProtectGoalWrapType = 
        class_<tcProtectGoalWrap>("ProtectGoalWrap")
        .def("AddTarget", &tcProtectGoalWrap::AddTarget)
        .def("RemoveTarget", &tcProtectGoalWrap::RemoveTarget)
        .def("SetQuantity", &tcProtectGoalWrap::SetQuantity)
        .def("GetQuantity", &tcProtectGoalWrap::GetQuantity)
        .def("GetTargetCount", &tcProtectGoalWrap::GetTargetCount)
        .def("GetTargetName", &tcProtectGoalWrap::GetTargetName)
        .def("GetId", &tcProtectGoalWrap::GetId)
        ;

    object AreaGoalWrapType = 
        class_<tcAreaGoalWrap>("AreaGoalWrap")
        .def("GetTargetString", &tcAreaGoalWrap::GetTargetString)
        .def("SetTargetList", &tcAreaGoalWrap::SetTargetList)
        .def("AddToTargetList", &tcAreaGoalWrap::AddToTargetList)
        .def("SetQuantity", &tcAreaGoalWrap::SetQuantity)
        .def("GetQuantity", &tcAreaGoalWrap::GetQuantity)
        .def("GetId", &tcAreaGoalWrap::GetId)
        .def("Clear", &tcAreaGoalWrap::Clear)
        .def("AddPoint", &tcAreaGoalWrap::AddPoint)
        .def("AddPointDeg", &tcAreaGoalWrap::AddPointDeg)
        .def("SetEnterGoal", &tcAreaGoalWrap::SetEnterGoal)
        .def("GetEnterGoal", &tcAreaGoalWrap::GetEnterGoal)
		.def("SetTimeObjective", &tcAreaGoalWrap::SetTimeObjective)
		.def("GetTimeObjective", &tcAreaGoalWrap::GetTimeObjective)
		.def("SetLogicAny", &tcAreaGoalWrap::SetLogicAny)
		.def("IsLogicAny", &tcAreaGoalWrap::IsLogicAny)
        ;
}



/*******************************************************/


#ifdef _DEBUG
#define new DEBUG_NEW
#endif 


tcSimState* tcGoal::simState = 0;
tcMapOverlay* tcGoal::mapOverlay = 0;
unsigned long tcGoal::nextId = 100;

/*** tcGoal ***/

void tcGoal::AttachMapOverlay(tcMapOverlay* overlay)
{
    mapOverlay = overlay;
}

tcGoal* tcGoal::CreateByType(int goalType)
{
    switch (goalType)
    {
    case GOAL:
        wxASSERT(false); ///< 7 APR 2012 added fix so this should never happen with any new scenario saves, may happen with old
        return new tcGoal();
        break;
    case COMPOUND:
        return new tcCompoundGoal();
        break;
    case TIME:
        return new tcTimeGoal();
        break;
    case DESTROY:
        return new tcDestroyGoal("");
        break;
    case PROTECT:
        return new tcProtectGoal("");
        break;
    case AREA:
        return new tcAreaGoal();
        break;
    default:
        wxASSERT(false);
        fprintf(stderr, "tcGoal::CreateByType - Illegal goalType (%d)\n",
            goalType);
        return 0;
    }
}

/**
* Save
*/
tcGameStream& tcGoal::operator>>(tcGameStream& stream)
{
    stream << goalState;
    stream << failScore;
    stream << passScore;
    stream << id;
    stream << alliance;

    return stream;
}

/**
* Load
*/
tcGameStream& tcGoal::operator<<(tcGameStream& stream)
{
    stream >> goalState;
    stream >> failScore;
    stream >> passScore;
    stream >> id;
    stream >> alliance;

    nextId = std::max(nextId, id+1);

    return stream;
}

/**
* @return goalState as a string
*/
std::string tcGoal::GoalStateToString(int goalState)
{
	if (goalState == UNRESOLVED)
	{
		return std::string("UNRESOLVED");
	}
	else if (goalState == FAILED)
	{
		return std::string("FAILED");
	}
	else
	{
		return std::string("PASSED");
	}

}

tcGoal* tcGoal::Clone()
{
    tcGoal *goal = new tcGoal(*this);
    return goal;
}

void tcGoal::CloseMapObject()
{
    if (mapObjectId != -1)
    {
        tcRegistered::ForceClose(mapObjectId);
        mapObjectId = -1;
    }
}


unsigned int tcGoal::GetAlliance() const
{
    return alliance;
}

unsigned long tcGoal::GetId() const
{
    return id;
}

float tcGoal::GetNetScore() const
{
	if (goalState == UNRESOLVED)
	{
		return 0;
	}
	else if (goalState == FAILED)
	{
		return failScore;
	}
	else
	{
		return passScore;
	}
}

int tcGoal::GetType() const
{
    return GOAL;
}

std::string tcGoal::GetTypeString() const
{
    return std::string("Goal");
}

void tcGoal::RenameTarget(const std::string& oldName, const std::string& newName)
{
    // do nothing at base class level
}

void tcGoal::SaveToPython(scriptinterface::tcScenarioLogger& logger)
{
}

void tcGoal::SetAlliance(unsigned int alliance_)
{
    alliance = alliance_;
}

void tcGoal::SetScores(float fail, float pass)
{
    failScore = fail;
    passScore = pass;
}

/**
* Checks to see if pass or fail timeouts have been
* triggered, and updates goalState.
*/
void tcGoal::Update()
{
}

/**
* Writes status summary of goal condition to file
*/
void tcGoal::WriteStatus(std::stringstream& stream, unsigned int level)
{
	for (unsigned int n=0; n<level; n++)
	{
		stream << indentString;
	}

	stream << "* Generic goal " << GoalStateToString(goalState) << "\n";
}


void tcGoal::WriteStatus(wxArrayString& arrayString, unsigned int level)
{
    wxString line;
	for (unsigned int n=0; n<level; n++)
	{
		line += indentString.c_str();
	}

    line += "* Generic goal ";
    line += GoalStateToString(goalState).c_str();

    arrayString.push_back(line);
}


/**
* Writes status summary of goal condition to file (no indenting or compound goal status)
*/
void tcGoal::WriteStatusB(std::stringstream& stream)
{
	stream << "* Generic goal " << GoalStateToString(goalState) << "\n";
}

void tcGoal::WriteStatusB(wxArrayString& arrayString)
{
    wxString line;

    line += "* Generic goal ";
    line += GoalStateToString(goalState).c_str();
	
    arrayString.push_back(line);
}



tcGoal::tcGoal()
: indentString("    "),
  failScore(-100.0f),
  passScore(100.0f),
  id(nextId++),
  mapObjectId(-1),
  alliance(0)
{
    goalState = UNRESOLVED;
}

tcGoal::tcGoal(const tcGoal& goal)
: indentString(goal.indentString),
  failScore(goal.failScore),
  passScore(goal.passScore),
  id(goal.id),
  mapObjectId(goal.mapObjectId),
  alliance(goal.alliance)
{
    goalState = goal.goalState;
}

tcGoal::~tcGoal()
{
    CloseMapObject();
}

/*** tcGoalWrap ***/
/**
* @returns copy of this goal as tcCompoundGoal or
* empty tcCompoundGoal if not a tcCompoundGoal
*/
tcCompoundGoalWrap tcGoalWrap::AsCompoundGoal()
{
    if (tcCompoundGoal* compound = dynamic_cast<tcCompoundGoal*>(goal))
    {
        return tcCompoundGoalWrap(compound);
    }
    else
    {
        return tcCompoundGoalWrap();
    }
}

tcTimeGoalWrap tcGoalWrap::AsTimeGoal()
{
    if (tcTimeGoal* time = dynamic_cast<tcTimeGoal*>(goal))
    {
        return tcTimeGoalWrap(time);
    }
    else
    {
        return tcTimeGoalWrap();
    }
}

tcDestroyGoalWrap tcGoalWrap::AsDestroyGoal()
{
    if (tcDestroyGoal* destroy = dynamic_cast<tcDestroyGoal*>(goal))
    {
        return tcDestroyGoalWrap(destroy);
    }
    else
    {
        return tcDestroyGoalWrap();
    }
}

tcProtectGoalWrap tcGoalWrap::AsProtectGoal()
{
    if (tcProtectGoal* protect = dynamic_cast<tcProtectGoal*>(goal))
    {
        return tcProtectGoalWrap(protect);
    }
    else
    {
        return tcProtectGoalWrap();
    }
}

tcAreaGoalWrap tcGoalWrap::AsAreaGoal()
{
    if (tcAreaGoal* area = dynamic_cast<tcAreaGoal*>(goal))
    {
        return tcAreaGoalWrap(area);
    }
    else
    {
        return tcAreaGoalWrap();
    }
}


std::string tcGoalWrap::GetTypeString() const
{
    if (goal != 0)
    {
        return goal->GetTypeString();
    }
    else
    {
        return std::string("Error");
    }
}

unsigned long tcGoalWrap::GetId() const
{
    if (goal != 0)
    {
        return goal->GetId();
    }
    else
    {
        return 99999;
    }
}

tcGoalWrap::tcGoalWrap(tcGoal* g)
: goal(g)
{
}

tcGoalWrap::tcGoalWrap()
: goal(0)
{
}

tcGoalWrap::~tcGoalWrap()
{
}


void tcCompoundGoalWrap::AddGoal(tcGoal& newGoal)
{
    if (compoundGoal != 0)
    {
        compoundGoal->AddGoal(newGoal);
    }
}

int tcCompoundGoalWrap::GetLogicType() const
{
    if (compoundGoal != 0)
    {
        return compoundGoal->logicType;
    }
    else
    {
        return -1;
    }
}

unsigned int tcCompoundGoalWrap::GetSubGoalCount() const
{
    if (compoundGoal != 0)
    {
        return compoundGoal->GetSubGoalCount();
    }
    else
    {
        return 0;
    }
}

tcGoalWrap tcCompoundGoalWrap::GetSubGoal(unsigned int idx)
{
    if (compoundGoal != 0)
    {
        return compoundGoal->GetSubGoal(idx);
    }
    else
    {
        return tcGoalWrap();
    }
}

unsigned long tcCompoundGoalWrap::GetId() const
{
    if (compoundGoal != 0)
    {
        return compoundGoal->GetId();
    }
    else
    {
        return 99999;
    }
}

void tcCompoundGoalWrap::SetLogicType(int val)
{
    if (compoundGoal != 0)
    {
        compoundGoal->logicType = int(val != 0);
    }
}


tcCompoundGoalWrap::tcCompoundGoalWrap(tcCompoundGoal* g)
: compoundGoal(g)
{
}

tcCompoundGoalWrap::tcCompoundGoalWrap()
: compoundGoal(0)
{
}

tcCompoundGoalWrap::~tcCompoundGoalWrap()
{
}




double tcTimeGoalWrap::GetFailTimeout() const
{
    if (timeGoal != 0)
    {
        return timeGoal->failTimeout;
    }
    else
    {
        return 999.9;
    }
}

void tcTimeGoalWrap::SetFailTimeout(double t)
{
    if (timeGoal != 0)
    {
        timeGoal->SetFailTimeout(t);
    }
}

double tcTimeGoalWrap::GetPassTimeout() const
{
    if (timeGoal != 0)
    {
        return timeGoal->passTimeout;
    }
    else
    {
        return 999.9;
    }
}

void tcTimeGoalWrap::SetPassTimeout(double t)
{
    if (timeGoal != 0)
    {
        timeGoal->SetPassTimeout(t);
    }
}

unsigned long tcTimeGoalWrap::GetId() const
{
    if (timeGoal != 0)
    {
        return timeGoal->GetId();
    }
    else
    {
        return 99999;
    }
}

tcTimeGoalWrap::tcTimeGoalWrap(tcTimeGoal* g)
: timeGoal(g)
{
}

tcTimeGoalWrap::tcTimeGoalWrap()
: timeGoal(0)
{
}

tcTimeGoalWrap::~tcTimeGoalWrap()
{
}


void tcDestroyGoalWrap::AddTarget(const std::string& s)
{
    if (destroyGoal != 0)
    {
        destroyGoal->AddTarget(s);
    }
    else
    {
    }
}

void tcDestroyGoalWrap::RemoveTarget(const std::string& s)
{
    if (destroyGoal != 0)
    {
        destroyGoal->RemoveTarget(s);
    }
    else
    {
    }
}

void tcDestroyGoalWrap::SetQuantity(unsigned int val)
{
    if (destroyGoal != 0)
    {
        destroyGoal->SetQuantity(val);
    }
    else
    {
    }
}

unsigned int tcDestroyGoalWrap::GetQuantity() const
{
    if (destroyGoal != 0)
    {
        return destroyGoal->GetQuantity();
    }
    else
    {
        return 0;
    }
}

unsigned int tcDestroyGoalWrap::GetTargetCount() const
{
    if (destroyGoal != 0)
    {
        return destroyGoal->GetTargetCount();
    }
    else
    {
        return 0;
    }
}

std::string tcDestroyGoalWrap::GetTargetName(unsigned int index)
{
    if (destroyGoal != 0)
    {
        return destroyGoal->GetTargetName(index);
    }
    else
    {
        return std::string("Error");
    }
}



unsigned long tcDestroyGoalWrap::GetId() const
{
    if (destroyGoal != 0)
    {
        return destroyGoal->GetId();
    }
    else
    {
        return 99999;
    }
}


tcDestroyGoalWrap::tcDestroyGoalWrap(tcDestroyGoal* g)
: destroyGoal(g)
{
}

tcDestroyGoalWrap::tcDestroyGoalWrap()
: destroyGoal(0)
{
}

tcDestroyGoalWrap::~tcDestroyGoalWrap()
{
}


void tcProtectGoalWrap::AddTarget(const std::string& s)
{
    if (protectGoal != 0)
    {
        protectGoal->AddTarget(s);
    }
    else
    {
    }
}

void tcProtectGoalWrap::RemoveTarget(const std::string& s)
{
    if (protectGoal != 0)
    {
        protectGoal->RemoveTarget(s);
    }
    else
    {
    }
}

void tcProtectGoalWrap::SetQuantity(unsigned int val)
{
    if (protectGoal != 0)
    {
        protectGoal->SetQuantity(val);
    }
    else
    {
    }
}

unsigned int tcProtectGoalWrap::GetQuantity() const
{
    if (protectGoal != 0)
    {
        return protectGoal->GetQuantity();
    }
    else
    {
        return 0;
    }
}

unsigned int tcProtectGoalWrap::GetTargetCount() const
{
    if (protectGoal != 0)
    {
        return protectGoal->GetTargetCount();
    }
    else
    {
        return 0;
    }
}

std::string tcProtectGoalWrap::GetTargetName(unsigned int index)
{
    if (protectGoal != 0)
    {
        return protectGoal->GetTargetName(index);
    }
    else
    {
        return std::string("Error");
    }
}

unsigned long tcProtectGoalWrap::GetId() const
{
    if (protectGoal != 0)
    {
        return protectGoal->GetId();
    }
    else
    {
        return 99999;
    }
}


tcProtectGoalWrap::tcProtectGoalWrap(tcProtectGoal* g)
: protectGoal(g)
{
}

tcProtectGoalWrap::tcProtectGoalWrap()
: protectGoal(0)
{
}

tcProtectGoalWrap::~tcProtectGoalWrap()
{
}


void tcAreaGoalWrap::AddToTargetList(const std::string& s)
{
    if (areaGoal != 0)
    {
        areaGoal->AddToTargetList(s);
    }
}

std::string tcAreaGoalWrap::GetTargetString() const
{
    if (areaGoal != 0)
    {
        return areaGoal->GetTargetListAsString();
    }
    else
    {
        return std::string("Error");
    }
}

void tcAreaGoalWrap::SetTargetList(const std::string& s)
{
    if (areaGoal != 0)
    {
        areaGoal->SetTargetList(s);
    }
}



void tcAreaGoalWrap::Clear()
{
    if (areaGoal != 0)
    {
        areaGoal->Clear();
    }
}

void tcAreaGoalWrap::AddPoint(float lon_rad, float lat_rad)
{
    if (areaGoal != 0)
    {
        areaGoal->AddPoint(lon_rad, lat_rad);
    }
}

void tcAreaGoalWrap::AddPointDeg(float lon_deg, float lat_deg)
{
    if (areaGoal != 0)
    {
        areaGoal->AddPointDeg(lon_deg, lat_deg);
    }
}

void tcAreaGoalWrap::SetEnterGoal(bool state)
{
    if (areaGoal != 0)
    {
        areaGoal->SetEnterGoal(state);
    }
}

bool tcAreaGoalWrap::GetEnterGoal() const
{
    if (areaGoal != 0)
    {
        return areaGoal->isEnterGoal;
    }
    else
    {
        return 0;
    }
}

void tcAreaGoalWrap::SetTimeObjective(float t_s)
{
	if (areaGoal != 0)
	{
		areaGoal->SetTimeObjective(t_s);
	}
}

float tcAreaGoalWrap::GetTimeObjective() const
{
	if (areaGoal != 0)
	{
		return areaGoal->timeObjective_s;
	}
	else
	{
		return 0;
	}
}

void tcAreaGoalWrap::SetLogicAny(bool state)
{
	if (areaGoal != 0)
	{
		areaGoal->SetLogicAny(state);
	}
}

bool tcAreaGoalWrap::IsLogicAny() const
{
	if (areaGoal != 0)
	{
		return areaGoal->IsLogicAny();
	}
	else
	{
		wxASSERT(false); // not sure if this is normal path or not, 30JAN2011
		return false;
	}
}

void tcAreaGoalWrap::SetQuantity(unsigned int val)
{
	if (areaGoal != 0)
	{
		areaGoal->SetQuantity(val);
	}
}

unsigned int tcAreaGoalWrap::GetQuantity() const
{
	if (areaGoal != 0)
	{
		return areaGoal->GetQuantity();
	}
	else
	{
		wxASSERT(false); // not sure if this is normal path or not, 30JAN2011
		return 0;
	}
}



unsigned long tcAreaGoalWrap::GetId() const
{
    if (areaGoal != 0)
    {
        return areaGoal->GetId();
    }
    else
    {
        return 99999;
    }
}


tcAreaGoalWrap::tcAreaGoalWrap(tcAreaGoal* g)
: areaGoal(g)
{
}

tcAreaGoalWrap::tcAreaGoalWrap()
: areaGoal(0)
{
}

tcAreaGoalWrap::~tcAreaGoalWrap()
{
}




/*** tcCompoundGoal ***/

unsigned tcCompoundGoal::pythonWriteCount = 0;

/**
* Save
*/
tcGameStream& tcCompoundGoal::operator>>(tcGameStream& stream)
{
    int goalType = GetType();
    stream << goalType;

    tcGoal::operator>>(stream);

    stream << logicType;

    unsigned int nChildren = children.size();
    stream << nChildren;
    for (unsigned int k=0; k<nChildren; k++)
    {
        children[k]->operator>>(stream);
    }

    stream.WriteCheckValue(442);

    return stream;
}

/**
* Load
*/
tcGameStream& tcCompoundGoal::operator<<(tcGameStream& stream)
{
    tcGoal::operator<<(stream);

    stream >> logicType;

    unsigned int nChildren;
    stream >> nChildren;
    for (unsigned int k=0; k<nChildren; k++)
    {
        int goalType;
        stream >> goalType;
        tcGoal* childGoal = tcGoal::CreateByType(goalType);
        *childGoal << stream;

        children.push_back(childGoal);
    }

    stream.ReadCheckValue(442);

    return stream;
}


/**
* Copies and adds newGoal.
*/
void tcCompoundGoal::AddGoal(tcGoal& newGoal) 
{
    tcGoal *goal = newGoal.Clone();
    children.push_back(goal);
}

void tcCompoundGoal::AddGoalByPtr(tcGoal* newGoal)
{
    wxASSERT(newGoal != 0);

    tcGoal* goal = newGoal->Clone();
    children.push_back(goal);
}

tcGoal* tcCompoundGoal::Clone()
{
    tcGoal *goal = new tcCompoundGoal(*this);
    return goal;
}

float tcCompoundGoal::GetNetScore() const
{

    float netScore = 0;
    if (goalState == PASSED)
    {
        netScore = passScore;
    }
    else if (goalState == FAILED)
    {
        netScore = failScore;
    }


	for (size_t k=0; k<children.size(); k++)
	{
		netScore += children[k]->GetNetScore();
	}

    return netScore;
}

unsigned int tcCompoundGoal::GetSubGoalCount() const
{
    return (unsigned int)children.size();
}

tcGoalWrap tcCompoundGoal::GetSubGoal(unsigned int idx)
{
    if (idx < (unsigned int)children.size())
    {
        return tcGoalWrap(children[idx]);
    }
    else
    {
        return tcGoalWrap();
    }
}

int tcCompoundGoal::GetType() const
{
    return COMPOUND;
}


std::string tcCompoundGoal::GetTypeString() const
{
    return std::string("Compound");
}

void tcCompoundGoal::RenameTarget(const std::string& oldName, const std::string& newName)
{
    for (size_t k=0; k<children.size(); k++)
	{
		children[k]->RenameTarget(oldName, newName);
    }
}


void tcCompoundGoal::SaveToPython(scriptinterface::tcScenarioLogger& logger)
{
	wxString s;

	unsigned sequenceId = pythonWriteCount++;

	for (size_t k=0; k<children.size(); k++)
	{
		children[k]->SaveToPython(logger);
		s.Printf("goal_%d_%d = goal_temp\n", sequenceId, k);
		logger.AddScenarioText(s);
	}

	s.Printf("goal_temp = SM.CompoundGoal(%d)", logicType);
	logger.AddScenarioText(s);

	for (size_t k=0; k<children.size(); k++)
	{
		s.Printf("goal_temp.AddGoal(goal_%d_%d)", sequenceId, k);
		logger.AddScenarioText(s);
	}
	logger.AddScenarioText("");
}

void tcCompoundGoal::SetAlliance(unsigned int alliance_)
{
    tcGoal::SetAlliance(alliance_);

    size_t nChildren = children.size();
    for (size_t n=0; n<nChildren; n++)
    {
        tcGoal* childGoal = children[n];
        childGoal->SetAlliance(alliance_);
    }
}


void tcCompoundGoal::Update()
{
    wxASSERT(simState);

    // use children to determine pass/fail
    int nChildren = (int)children.size();
    wxASSERT(nChildren); // compound goal should have at least one child
    if (nChildren == 0) return;
   
    bool anyPassed = false;
    bool anyFailed = false;
    bool anyUnresolved = false;
    for (int n=0;n<nChildren;n++)
    {
        tcGoal* childGoal = children.at(n);
        childGoal->Update();
        if (childGoal->IsFailed()) anyFailed = true;
        else if (childGoal->IsPassed()) anyPassed = true;
        else anyUnresolved = true;
    }
    if (logicType == OR)
    {
        if (anyPassed) goalState = PASSED;
        else if (!anyUnresolved) goalState = FAILED;
    }
    else // logicType == AND
    {
        if (anyFailed) goalState = FAILED;
        else if (!anyUnresolved) goalState = PASSED;
    }
}
void tcCompoundGoal::WriteStatus(std::stringstream& stream, unsigned int level)
{
	for (unsigned int n=0; n<level; n++)
	{
		stream << indentString;
	}

	std::string typeString;

	if (logicType == AND)
	{
		typeString = "ALL";
	}
	else
	{
		typeString = "ANY";
	}

    stream << "* Compound Goal -- "
			"Mission to achieve " << typeString << " of the following subgoals ";

	if (goalState == PASSED)
	{
		stream << "ACCOMPLISHED:\n";
	}
	else if (goalState == FAILED)
	{
		stream << "FAILED:\n";
	}
	else
	{
		stream << "NOT ACCOMPLISHED:\n";
	}


	size_t nChildren = children.size();

	for (size_t n=0; n<nChildren; n++)
	{
		tcGoal* childGoal = children.at(n);
		childGoal->WriteStatus(stream, level + 1);
	}
}

void tcCompoundGoal::WriteStatus(wxArrayString& arrayString, unsigned int level)
{
    wxString line;
	for (unsigned int n=0; n<level; n++)
	{
		line += indentString.c_str();
	}

	wxString typeString;

	if (logicType == AND)
	{
		typeString = "ALL";
	}
	else
	{
		typeString = "ANY";
	}

    line += "* Compound Goal -- Mission to achieve ";
    line += typeString;
    line += " of the following subgoals ";

	if (goalState == PASSED)
	{
		line += "ACCOMPLISHED:";
	}
	else if (goalState == FAILED)
	{
		line += "FAILED:";
	}
	else
	{
		line += "NOT ACCOMPLISHED:";
	}

    arrayString.push_back(line);


	size_t nChildren = children.size();

	for (size_t n=0; n<nChildren; n++)
	{
		tcGoal* childGoal = children.at(n);
		childGoal->WriteStatus(arrayString, level + 1);
	}
}


/**
* Writes status summary of goal condition to file (no indenting or compound goal status)
*/
void tcCompoundGoal::WriteStatusB(std::stringstream& stream)
{
    // write nothing for compound goal itself

    size_t nChildren = children.size();

	for (size_t n=0; n<nChildren; n++)
	{
		tcGoal* childGoal = children.at(n);
		childGoal->WriteStatusB(stream);
	}
}

/**
* Writes status summary of goal condition to file (no indenting or compound goal status)
*/
void tcCompoundGoal::WriteStatusB(wxArrayString& arrayString)
{
    // write nothing for compound goal itself

    size_t nChildren = children.size();

	for (size_t n=0; n<nChildren; n++)
	{
		tcGoal* childGoal = children.at(n);
		childGoal->WriteStatusB(arrayString);
	}
}


tcCompoundGoal::tcCompoundGoal(int type) 
: logicType(type) 
{
    children.clear();
}

tcCompoundGoal::tcCompoundGoal(const tcCompoundGoal& goal)
: tcGoal(goal), logicType(goal.logicType)
{
    children.clear();
    size_t nChildren = goal.children.size();
    for(size_t n=0; n<nChildren; n++)
    {
        tcGoal *child = goal.children[n]->Clone();
        children.push_back(child);
    }
}

tcCompoundGoal::~tcCompoundGoal() 
{
    size_t nChildren = children.size();
    for(size_t n=0; n<nChildren; n++)
    {
        tcGoal *goal = children[n];
        if (goal) delete goal;
    }
    children.clear();
}

/*** tcTimeGoal ***/

/**
* Save
*/
tcGameStream& tcTimeGoal::operator>>(tcGameStream& stream)
{
    int goalType = GetType();
    stream << goalType;

    tcGoal::operator>>(stream);

    stream << failTimeout;
    stream << passTimeout;

    return stream;
}

/**
* Load
*/
tcGameStream& tcTimeGoal::operator<<(tcGameStream& stream)
{
    tcGoal::operator<<(stream);

    stream >> failTimeout;
    stream >> passTimeout;

    return stream;
}

tcGoal* tcTimeGoal::Clone()
{
    tcGoal *goal = new tcTimeGoal(*this);
    return goal;
}

int tcTimeGoal::GetType() const
{
    return TIME;
}


std::string tcTimeGoal::GetTypeString() const
{
    return std::string("Time");
}

void tcTimeGoal::SaveToPython(scriptinterface::tcScenarioLogger& logger)
{
	wxString s;

	logger.AddScenarioText("goal_temp = SM.TimeGoal()");

	if (passTimeout != DBL_MAX)
	{
		s.Printf("goal_temp.SetPassTimeout(%.1f)", passTimeout);
		logger.AddScenarioText(s);
	}

	if (failTimeout != DBL_MAX)
	{
		s.Printf("goal_temp.SetFailTimeout(%.1f)", failTimeout);
		logger.AddScenarioText(s);
	}

}

void tcTimeGoal::SetFailTimeout(double t)
{
    failTimeout = t;
}

void tcTimeGoal::SetPassTimeout(double t) 
{
    passTimeout = t;
}


void tcTimeGoal::Update()
{
    wxASSERT(simState);
    if (goalState != UNRESOLVED) return; // resolved, return immediately

    if (simState->GetTime() >= passTimeout)
    {
        goalState = PASSED;
    }
    else if (simState->GetTime() >= failTimeout)
    {
        goalState = FAILED;
    }
}

void tcTimeGoal::WriteStatus(std::stringstream& stream, unsigned int level)
{
	for (unsigned int n=0; n<level; n++)
	{
		stream << indentString;
	}

    wxString s = "* Time Goal -- ";

    if (simState->GetTime() >= passTimeout)
    {
        s += wxString::Format("Orders were satisfied for %.0f min, goal SUCCESS.\n",
            (1.0/60.0f)*passTimeout);
        stream << s.c_str();
    }
    else if (simState->GetTime() >= failTimeout)
    {
        s += wxString::Format("The mission time limit of %.0f min was exceeded, goal FAILED.\n",
            (1.0/60.0f)*failTimeout);
        stream << s.c_str();
    }	    
	else if (failTimeout < passTimeout)
	{
        s += wxString::Format("Time limit of %.0f min not exceeded, goal UNRESOLVED.\n",
            (1.0/60.0f)*failTimeout);
        stream << s.c_str();
	}
	else
	{
        s += wxString::Format("Time goal of %.0f min not yet elapsed, goal NOT ACHIEVED.\n",
            (1.0/60.0f)*passTimeout);
        stream << s.c_str();
	}
}

void tcTimeGoal::WriteStatus(wxArrayString& arrayString, unsigned int level)
{
    wxString line;
	for (unsigned int n=0; n<level; n++)
	{
		line += indentString.c_str();
	}

    wxString s = "* Time Goal -- ";

    if (simState->GetTime() >= passTimeout)
    {
        s += wxString::Format("Orders were satisfied for %.0f min, goal SUCCESS",
            (1.0/60.0f)*passTimeout);
    }
    else if (simState->GetTime() >= failTimeout)
    {
        s += wxString::Format("The mission time limit of %.0f min was exceeded, goal FAILED",
            (1.0/60.0f)*failTimeout);
    }	    
	else if (failTimeout < passTimeout)
	{
        s += wxString::Format("Time limit of %.0f min not exceeded, goal UNRESOLVED",
            (1.0/60.0f)*failTimeout);
	}
	else
	{
        s += wxString::Format("Time goal of %.0f min not yet elapsed, goal NOT ACHIEVED",
            (1.0/60.0f)*passTimeout);
	}

    line += s;

    arrayString.push_back(line);
}


void tcTimeGoal::WriteStatusB(std::stringstream& stream)
{
    if (simState->GetTime() >= passTimeout)
    {
        stream << "* "
			"Orders were satisfied for specified time, goal SUCCESS.\n";
    }
    else if (simState->GetTime() >= failTimeout)
    {
        stream << "* "
			"The mission time limit was exceeded, goal FAILED.\n";
    }	    
	else if (failTimeout < passTimeout)
	{
		stream << "* "
			"Time limit not exceeded, goal UNRESOLVED.\n";
	}
	else
	{
		stream << "* "
			"Time goal not satisfied, goal NOT ACHIEVED.\n";
	}
}

void tcTimeGoal::WriteStatusB(wxArrayString& arrayString)
{
    wxString line;
    if (simState->GetTime() >= passTimeout)
    {
        line = "* Orders were satisfied for specified time, goal SUCCESS";
    }
    else if (simState->GetTime() >= failTimeout)
    {
        line = "* The mission time limit was exceeded, goal FAILED";
    }	    
	else if (failTimeout < passTimeout)
	{
		line = "* Time limit not exceeded, goal UNRESOLVED";
	}
	else
	{
		line = "* Time goal not satisfied, goal NOT ACHIEVED";
	}

    arrayString.push_back(line);
}


tcTimeGoal::tcTimeGoal()
: disabledTime_s(31556926.0)
{
    failTimeout = DBL_MAX;
    passTimeout = DBL_MAX;
}

tcTimeGoal::tcTimeGoal(const tcTimeGoal& goal)
: disabledTime_s(31556926.0), tcGoal(goal)
{
    failTimeout = goal.failTimeout;
    passTimeout = goal.passTimeout;
}

tcTimeGoal::~tcTimeGoal()
{
}

/*** tcDestroyGoal ***/

/**
* Save
*/
tcGameStream& tcDestroyGoal::operator>>(tcGameStream& stream)
{
    int goalType = GetType();
    stream << goalType;

    tcGoal::operator>>(stream);

    unsigned int nTargets = (unsigned int)targetList.size();
    stream << nTargets;
    for (unsigned int n=0; n<nTargets; n++)
    {
        std::string targetString = targetList[n];
        stream << targetString;
    }
    stream << quantity;

    return stream;
}

/**
* Load
*/
tcGameStream& tcDestroyGoal::operator<<(tcGameStream& stream)
{
    tcGoal::operator<<(stream);

    targetList.clear();
    unsigned int nTargets;
    stream >> nTargets;
    for (unsigned int n=0; n<nTargets; n++)
    {
        std::string targetString;
        stream >> targetString;
        targetList.push_back(targetString);
    }
    stream >> quantity;

    return stream;
}

tcGoal* tcDestroyGoal::Clone()
{
    tcGoal *goal = new tcDestroyGoal(*this);
    return goal;
}

int tcDestroyGoal::GetType() const
{
    return DESTROY;
}


std::string tcDestroyGoal::GetTypeString() const
{
    return std::string("Destroy");
}

unsigned int tcDestroyGoal::GetTargetCount() const
{
    return targetList.size();
}

std::string tcDestroyGoal::GetTargetName(unsigned int index)
{
    return targetList[index];
}

void tcDestroyGoal::AddTarget(const std::string& s)
{
    for (size_t n=0; n<targetList.size(); n++)
    {
        if (targetList[n] == s) return; // target already in list
    }
    targetList.push_back(s);
}

void tcDestroyGoal::RemoveTarget(const std::string& s)
{
    std::vector<std::string> targetListRemoved;

    for (size_t n=0; n<targetList.size(); n++)
    {
        if (targetList[n] != s)
        {
            targetListRemoved.push_back(targetList[n]);
        }
    }

    targetList = targetListRemoved;
}

void tcDestroyGoal::SetQuantity(unsigned int val)
{
    quantity = val;
}

unsigned int tcDestroyGoal::GetQuantity() const
{
    return quantity;
}


void tcDestroyGoal::RenameTarget(const std::string& oldName, const std::string& newName)
{
    std::vector<std::string> targetListRenamed;
    for (size_t n=0; n<targetList.size(); n++)
    {
        std::string targetString = targetList[n];
        if (targetString != oldName)
        {
            targetListRenamed.push_back(targetString);
        }
        else
        {
            targetListRenamed.push_back(newName);
        }
    }
    targetList = targetListRenamed;
}

void tcDestroyGoal::SaveToPython(scriptinterface::tcScenarioLogger& logger)
{
	wxString s;

	s = "goal_temp = SM.DestroyGoal('')";
	logger.AddScenarioText(s);

    for (size_t n=0; n<targetList.size(); n++)
    {
        s.Printf("goal_temp.AddTarget('%s')", targetList[n].c_str());
        logger.AddScenarioText(s);
    }

    s.Printf("goal_temp.SetQuantity(%d)", quantity);
    logger.AddScenarioText(s);
}

void tcDestroyGoal::Update()
{
    wxASSERT(simState);
    if (goalState != UNRESOLVED) return; // resolved, return immediately

    unsigned int quantityDestroyed = 0;

    for (size_t n=0; n<targetList.size(); n++)
    {
	    tcGameObject* obj = simState->GetObjectByName(targetList[n]);
        if (obj == 0) quantityDestroyed++;
    }

	if (quantityDestroyed >= quantity)
	{
		goalState = PASSED;
	}

}

const wxString& tcDestroyGoal::GetTargetDescription() const
{
    static wxString targetDescription;
    targetDescription.clear();

    if (targetList.size() == 1)
    {
        targetDescription = targetList[0].c_str();
    }
    else
    {
        size_t n = 0;
        for (n=0; (n<targetList.size()) && (n < 3); n++)
        {
            targetDescription += targetList[n].c_str();
            targetDescription += " ";
        }
        if (n < targetList.size())
        {
            targetDescription += "... ";
        }
        targetDescription += wxString::Format("(%d/%d units)", quantity, targetList.size());
    }

    return targetDescription;
}

void tcDestroyGoal::WriteStatus(std::stringstream& stream, unsigned int level)
{
	for (unsigned int n=0; n<level; n++)
	{
		stream << indentString;
	}

    wxString targetDescription = GetTargetDescription();
    
	stream << "* Destroy Goal -- " << targetDescription;

	if (goalState == PASSED)
	{
		stream << " was DESTROYED.\n";
	}
	else
	{
        stream << " NOT DESTROYED.\n";
	}
}

void tcDestroyGoal::WriteStatus(wxArrayString& arrayString, unsigned int level)
{
    wxString targetDescription = GetTargetDescription();

    wxString line;
	for (unsigned int n=0; n<level; n++)
	{
		line += indentString.c_str();
	}

	line += "* Destroy Goal -- " + targetDescription;

	if (goalState == PASSED)
	{
		line += " was DESTROYED";
	}
	else
	{
		line += " NOT DESTROYED";
	}

    arrayString.push_back(line);
}


void tcDestroyGoal::WriteStatusB(std::stringstream& stream)
{
    wxString targetDescription = GetTargetDescription();

    stream << "* " << targetDescription.c_str();

	if (goalState == PASSED)
	{
		stream << " was DESTROYED.\n";
	}
	else
	{
		stream << " NOT DESTROYED.\n";
	}
}

void tcDestroyGoal::WriteStatusB(wxArrayString& arrayString)
{
    wxString line = "* " + GetTargetDescription();
	
	if (goalState == PASSED)
	{
		line += " was DESTROYED";
	}
	else
	{
		line += " NOT DESTROYED";
	}

    arrayString.push_back(line);
}


tcDestroyGoal::tcDestroyGoal(const tcDestroyGoal& goal)
: tcGoal(goal),
  targetList(goal.targetList),
  quantity(goal.quantity)
{

}

tcDestroyGoal::tcDestroyGoal(const std::string& s)
: quantity(1)
{
    if (s.size() > 0)
    {
        targetList.push_back(s);
    }

}

/*** tcProtectGoal ***/

/**
* Save
*/
tcGameStream& tcProtectGoal::operator>>(tcGameStream& stream)
{
    int goalType = GetType();
    stream << goalType;

    tcGoal::operator>>(stream);

    unsigned int nTargets = (unsigned int)targetList.size();
    stream << nTargets;
    for (unsigned int n=0; n<nTargets; n++)
    {
        std::string targetString = targetList[n];
        stream << targetString;
    }
    stream << quantity;

    return stream;
}

/**
* Load
*/
tcGameStream& tcProtectGoal::operator<<(tcGameStream& stream)
{
    tcGoal::operator<<(stream);

    targetList.clear();
    unsigned int nTargets;
    stream >> nTargets;
    for (unsigned int n=0; n<nTargets; n++)
    {
        std::string targetString;
        stream >> targetString;
        targetList.push_back(targetString);
    }
    stream >> quantity;

    return stream;
}

tcGoal* tcProtectGoal::Clone()
{
    tcGoal *goal = new tcProtectGoal(*this);
    return goal;
}

int tcProtectGoal::GetType() const
{
    return PROTECT;
}


std::string tcProtectGoal::GetTypeString() const
{
    return std::string("Protect");
}


unsigned int tcProtectGoal::GetTargetCount() const
{
    return targetList.size();
}

std::string tcProtectGoal::GetTargetName(unsigned int index)
{
    return targetList[index];
}

void tcProtectGoal::AddTarget(const std::string& s)
{
    for (size_t n=0; n<targetList.size(); n++)
    {
        if (targetList[n] == s) return; // target already in list
    }
    targetList.push_back(s);
}

void tcProtectGoal::RemoveTarget(const std::string& s)
{
    std::vector<std::string> targetListRemoved;

    for (size_t n=0; n<targetList.size(); n++)
    {
        if (targetList[n] != s)
        {
            targetListRemoved.push_back(targetList[n]);
        }
    }

    targetList = targetListRemoved;
}

void tcProtectGoal::SetQuantity(unsigned int val)
{
    quantity = val;
    quantity = std::min(quantity, (unsigned int)targetList.size());
    quantity = std::max(quantity, (unsigned int)1);
}

unsigned int tcProtectGoal::GetQuantity() const
{
    return quantity;
}


void tcProtectGoal::RenameTarget(const std::string& oldName, const std::string& newName)
{
    std::vector<std::string> targetListRenamed;
    for (size_t n=0; n<targetList.size(); n++)
    {
        std::string targetString = targetList[n];
        if (targetString != oldName)
        {
            targetListRenamed.push_back(targetString);
        }
        else
        {
            targetListRenamed.push_back(newName);
        }
    }
    targetList = targetListRenamed;
}

const wxString& tcProtectGoal::GetTargetDescription() const
{
    static wxString targetDescription;
    targetDescription.clear();

    if (targetList.size() == 1)
    {
        targetDescription = targetList[0].c_str();
    }
    else
    {
        size_t n = 0;
        for (n=0; (n<targetList.size()) && (n < 3); n++)
        {
            targetDescription += targetList[n].c_str();
            targetDescription += " ";
        }
        if (n < targetList.size())
        {
            targetDescription += "... ";
        }
        targetDescription += wxString::Format("(%d/%d units)", quantity, targetList.size());
    }

    return targetDescription;
}

void tcProtectGoal::SaveToPython(scriptinterface::tcScenarioLogger& logger)
{
	wxString s;

	s = "goal_temp = SM.ProtectGoal('')";
	logger.AddScenarioText(s);

    for (size_t n=0; n<targetList.size(); n++)
    {
        s.Printf("goal_temp.AddTarget('%s')", targetList[n].c_str());
        logger.AddScenarioText(s);
    }

    s.Printf("goal_temp.SetQuantity(%d)", quantity);
    logger.AddScenarioText(s);

}


void tcProtectGoal::Update()
{
    wxASSERT(simState != 0);

    unsigned int quantitySurviving = 0;

    for (size_t n=0; n<targetList.size(); n++)
    {
	    tcGameObject* obj = simState->GetObjectByName(targetList[n]);
        if (obj != 0)
        {
            if (obj->GetDamageLevel() < 1.0)
            {
                quantitySurviving++;
            }
        }
    }

	if (quantitySurviving >= quantity)
	{
		goalState = PASSED;
	}
    else
    {
        goalState = FAILED;
    }
}

void tcProtectGoal::WriteStatus(std::stringstream& stream, unsigned int level)
{
	for (unsigned int n=0; n<level; n++)
	{
		stream << indentString;
	}

    wxString targetDescription = GetTargetDescription();

    stream << "* Protect Goal -- " << targetDescription.c_str();

	if (goalState == FAILED)
	{
		stream << " DID NOT SURVIVE.\n";
	}
	else
	{
		stream << " REMAINS SAFE.\n";
	}
}

void tcProtectGoal::WriteStatus(wxArrayString& arrayString, unsigned int level)
{
    wxString targetDescription = GetTargetDescription();

    wxString line;
	for (unsigned int n=0; n<level; n++)
	{
		line += indentString.c_str();
	}

	line += "* Protect Goal -- " + targetDescription;

	if (goalState == FAILED)
	{
		line += " DID NOT SURVIVE";
	}
	else
	{
		line += " REMAINS SAFE";
	}

    arrayString.push_back(line);
}


void tcProtectGoal::WriteStatusB(std::stringstream& stream)
{
    wxString targetDescription = GetTargetDescription();

	stream << "* " << targetDescription.c_str();

	if (goalState == FAILED)
	{
		stream << " DID NOT SURVIVE.\n";
	}
	else
	{
		stream << " REMAINS SAFE.\n";
	}
}

void tcProtectGoal::WriteStatusB(wxArrayString& arrayString)
{
    wxString targetDescription = GetTargetDescription();

    wxString line = wxString("* ") + targetDescription;

	if (goalState == FAILED)
	{
		line += " DID NOT SURVIVE";
	}
	else
	{
		line += " REMAINS SAFE";
	}

    arrayString.push_back(line);
}


tcProtectGoal::tcProtectGoal(const tcProtectGoal& goal)
: tcGoal(goal),
  targetList(goal.targetList),
  quantity(goal.quantity)
{

}

tcProtectGoal::tcProtectGoal(const std::string &s)
: quantity(1)
{
    if (s.size() > 0)
    {
        targetList.push_back(s);
    }
}

/*** tcAreaGoal ***/

/**
* Save
*/
tcGameStream& tcAreaGoal::operator>>(tcGameStream& stream)
{
    int goalType = GetType();
    stream << goalType;

    tcGoal::operator>>(stream);

	stream << timeObjective_s;
	stream << startTime_s;
	stream << isOR;

    unsigned int nTargets = targetList.size();
    stream << nTargets;
    for (unsigned int m=0; m<nTargets; m++)
    {
        std::string s(targetList[m].c_str());
        stream << s;
    }

    unsigned int nPoints = areaBounds.size();
    stream << nPoints;

    for (unsigned int n=0; n<nPoints; n++)
    {
        areaBounds[n] >> stream;
    }

    return stream;
}

/**
* Load
*/
tcGameStream& tcAreaGoal::operator<<(tcGameStream& stream)
{
    tcGoal::operator<<(stream);

	stream >> timeObjective_s;
	stream >> startTime_s;
	stream >> isOR;

    targetList.clear();
    unsigned int nTargets;
    stream >> nTargets;
    for (unsigned int m=0; m<nTargets; m++)
    {
        std::string s;
        stream >> s;
        targetList.push_back(s.c_str());
    }


    areaBounds.clear();
    unsigned int nPoints;
    stream >> nPoints;

    for (unsigned int n=0; n<nPoints; n++)
    {
        GeoPoint p;
        p << stream;
        areaBounds.push_back(p);
    }

    return stream;
}


void tcAreaGoal::Clear()
{
    areaBounds.clear();
    targetList.clear();
	isOR = true;
	timeObjective_s = 0;
}

void tcAreaGoal::AddPoint(float lon_rad, float lat_rad)
{
    GeoPoint p;
    p.Set(lon_rad, lat_rad, 0);

    areaBounds.push_back(p);
}

void tcAreaGoal::AddPointDeg(float lon_deg, float lat_deg)
{
    AddPoint(C_PIOVER180*lon_deg, C_PIOVER180*lat_deg);
}

tcGoal* tcAreaGoal::Clone()
{
    tcGoal *goal = new tcAreaGoal(*this);
    return goal;
}


unsigned int tcAreaGoal::GetQuantity() const
{
    return quantity;
}

const char* tcAreaGoal::GetQuantityDescription() const
{
    static wxString s;

    if (isOR)
    {
        s.Printf("ANY %d/", quantity);
    }
    else
    {
        s = "ALL ";
    }

    if (targetList.size() == 0) return s.c_str();

    if (targetList[0] == "All")
    {
        s += "#";
    }
    else if (targetList[0] == "Air")
    {
        s += "#";
    }
    else if (targetList[0] == "Surface")
    {
        s += "#";
    }
    else if (targetList[0] == "Sub")
    {
        s += "#";
    }
    else if (targetList[0] == "Ground")
    {
        s += "#";
    }
    else if (isOR)
    {
        s += wxString::Format("%d ", targetList.size());
    }


    return s.c_str();
}

/**
* @return target list as comma-delimited string
*/
std::string tcAreaGoal::GetTargetListAsString() const
{
    std::string s;

    for (size_t n=0; n<targetList.size(); n++)
    {
        s += targetList[n].c_str();
        if (n < (targetList.size() - 1))
        {
            s += std::string(", ");
        }
    }

    return s;
}

float tcAreaGoal::GetTimeObjective() const
{
	return timeObjective_s;
}

int tcAreaGoal::GetType() const
{
    return AREA;
}


std::string tcAreaGoal::GetTypeString() const
{
    return std::string("Area");
}

/**
* Has nothing to do with tcAreaGoal, but since other area calcs are here this
* is stuffed in with them
*/
GeoPoint tcAreaGoal::GetRandomPointWithinArea(const std::vector<GeoPoint>& area)
{
    GeoPoint result;
    result.Set(0, 0, 0);

    if (area.size() < 3) return result;

    float lon_min = 999.9f;
    float lon_max = -999.9f;
    float lat_min = 999.9f;
    float lat_max = -999.9f;

    for (size_t n=0; n<area.size(); n++)
    {
        lon_min = std::min(lon_min, (float)area[n].mfLon_rad);
        lat_min = std::min(lat_min, (float)area[n].mfLat_rad);
        lon_max = std::max(lon_max, (float)area[n].mfLon_rad);
        lat_max = std::max(lat_max, (float)area[n].mfLat_rad);
    }

    float dlon = lon_max - lon_min;
    float dlat = lat_max - lat_min;
    wxASSERT(dlon < C_PI); // could be wrapped if not

    const unsigned int maxAttempts = 15;
    unsigned int attempt = 0;
    while (attempt++ < maxAttempts)
    {
        float lon = lon_min + randf(dlon);
        float lat = lat_min + randf(dlat);

        if (IsPointWithinArea(area, lon, lat))
        {
            result.Set(lon, lat);
            return result;
        }
    }

    // pick two neighboring vertices and return point along line
    size_t n1 = floorf(randf(float(area.size())));
    size_t n2 = (n1 + 1) % area.size();
    float alpha = randf();
    float lon = alpha * area[n1].mfLon_rad + (1-alpha) * area[n2].mfLon_rad;
    float lat = alpha * area[n1].mfLat_rad + (1-alpha) * area[n2].mfLat_rad;

    result.Set(lon, lat);
    return result;
}

bool tcAreaGoal::IsLogicAny() const
{
	return isOR;
}

bool tcAreaGoal::IsPointWithinArea(const std::vector<GeoPoint>& area, float lon_rad, float lat_rad)
{
    // PNPOLY - Point Inclusion in Polygon Test
    // W. Randolph Franklin (WRF) 

    if (area.size() < 3) return false;

    float lon_min = 999.9f;
    float lon_max = -999.9f;
    float lat_min = 999.9f;
    float lat_max = -999.9f;

    for (size_t n=0; n<area.size(); n++)
    {
        lon_min = std::min(lon_min, (float)area[n].mfLon_rad);
        lat_min = std::min(lat_min, (float)area[n].mfLat_rad);
        lon_max = std::max(lon_max, (float)area[n].mfLon_rad);
        lat_max = std::max(lat_max, (float)area[n].mfLat_rad);
    }

    if ((lat_rad > lat_max) || (lat_rad < lat_min)) return false;

    std::vector<GeoPoint> vert = area;

    // unwrap polygon points if wrapped about +/180 deg
    if ((lon_max - lon_min) > C_PI)
    {
        for (size_t n=0; n<vert.size(); n++)
        {
            if (vert[n].mfLon_rad < 0) vert[n].mfLon_rad += C_TWOPI;
        }

        if (lon_rad < 0) lon_rad += C_TWOPI;

        if (lon_min < 0) lon_min += C_TWOPI;
        wxASSERT(lon_max >= 0);
    }

    if ((lon_rad > lon_max) || (lon_rad < lon_min)) return false;


    int i, j, c = 0;
    int nvert = int(area.size());

    for (i = 0, j = nvert-1; i < nvert; j = i++) 
    {
        float vertyi = (float)vert[i].mfLat_rad;
        float vertxi = (float)vert[i].mfLon_rad;
        float vertyj = (float)vert[j].mfLat_rad;
        float vertxj = (float)vert[j].mfLon_rad;

        if ( ((vertyi > lat_rad) != (vertyj > lat_rad)) &&
            (lon_rad < (vertxj-vertxi) * (lat_rad-vertyi) / (vertyj-vertyi) + vertxi) )
        {
            c = !c;
        }
    }

    return (c != 0);
}

bool tcAreaGoal::IsObjectWithinArea(const tcGameObject* obj) const
{
    if (obj == 0) return false;
    
    float lon_rad = float(obj->mcKin.mfLon_rad);
    float lat_rad = float(obj->mcKin.mfLat_rad);

    return IsPointWithinArea(areaBounds, lon_rad, lat_rad);

    
}

void tcAreaGoal::RenameTarget(const std::string& oldName, const std::string& newName)
{
    wxArrayString temp;

    for (size_t n=0; n<targetList.size(); n++)
    {
        if (targetList[n] != oldName.c_str())
        {
            temp.push_back(targetList[n]);
        }
        else
        {
            temp.push_back(wxString(newName.c_str()));
        }
    }

    targetList = temp;
}

void tcAreaGoal::SaveToPython(scriptinterface::tcScenarioLogger& logger)
{
	wxString s;

	s.Printf("goal_temp = SM.AreaGoal()");
	logger.AddScenarioText(s);

    std::string target_string = GetTargetListAsString();
    s.Printf("goal_temp.SetTargetList('%s')", target_string.c_str());
	logger.AddScenarioText(s);

	s.Printf("goal_temp.SetTimeObjective(%f)", timeObjective_s);
	logger.AddScenarioText(s);

	s.Printf("goal_temp.SetLogicAny(%d)", int(isOR));
	logger.AddScenarioText(s);

	s.Printf("goal_temp.SetQuantity(%d)", quantity);
	logger.AddScenarioText(s);

    unsigned int nPoints = areaBounds.size();

    for (unsigned int n=0; n<nPoints; n++)
    {
        s.Printf("goal_temp.AddPointDeg(%.5f, %.5f)",
            C_180OVERPI*areaBounds[n].mfLon_rad, C_180OVERPI*areaBounds[n].mfLat_rad);
	    logger.AddScenarioText(s);
    }

    if (!isEnterGoal)
    {
        s.Printf("goal_temp.SetEnterGoal(0)");
	    logger.AddScenarioText(s);
    }
}

void tcAreaGoal::SetEnterGoal(bool state)
{
    isEnterGoal = state;
}

void tcAreaGoal::SetLogicAny(bool state)
{
	isOR = state;
}

void tcAreaGoal::SetQuantity(unsigned int val)
{
    quantity = val;
}

void tcAreaGoal::AddToTargetList(const std::string& targets)
{
    wxString s(targets.c_str());

    wxString tgt = s.BeforeFirst(',');
    s = s.AfterFirst(',');

    // remove whitespace from right and left
    tgt.Trim(true); // right
    tgt.Trim(false); // left

    while (tgt.size() > 1)
    {
        targetList.push_back(tgt);

        tgt = s.BeforeFirst(',');
        s = s.AfterFirst(',');

        // remove whitespace from right and left
        tgt.Trim(true); // right
        tgt.Trim(false); // left
    }
}

/**
* Parses and sets comma delimited target list
*/
void tcAreaGoal::SetTargetList(const std::string& targets)
{
    targetList.clear();

    AddToTargetList(targets);
}

void tcAreaGoal::SetTimeObjective(float t_s)
{
	timeObjective_s = t_s;
}

void tcAreaGoal::Update()
{
    UpdateMapObject();

    size_t nTargets = targetList.size(); // # of objs or type classes that apply to goal

    // build list of named units and update classification mask
    wxArrayString namedUnits;
    unsigned int classMask = 0;
    for (size_t n=0; n<nTargets; n++)
    {
        if (targetList[n] == "All")
        {
            classMask = 0xFFFF;
        }
        else if (targetList[n] == "Air")
        {
            classMask = classMask | PTYPE_AIR;
        }
        else if (targetList[n] == "Surface")
        {
            classMask = classMask | PTYPE_SURFACE;
        }
        else if (targetList[n] == "Sub")
        {
            classMask = classMask | PTYPE_SUBSURFACE;
        }
        else if (targetList[n] == "Ground")
        {
            classMask = classMask | PTYPE_GROUND;
        }
        else // assume named unit
        {
            namedUnits.push_back(targetList[n]); 
        }
    }

    // if classification mask isn't zero, then add to list of named units
    if (classMask != 0)
    {
        tcGameObjIterator iter;
        iter.SetAllianceFilter(alliance);

        for (iter.First();iter.NotDone();iter.Next())
        {
            tcGameObject* obj = iter.Get();
            if ((obj != 0) && ((obj->mpDBObject->mnType & classMask) != 0))
            {
                namedUnits.push_back(obj->mzUnit.c_str());
            }
        }
    }

    wxASSERT(simState);

	if (isOR)
	{
        unsigned int numberWithinArea = 0;
        unsigned int numberThatExist = 0;


		for (size_t n=0; n<namedUnits.size(); n++)
		{
			std::string targetString(namedUnits[n].c_str());

			tcGameObject* obj = simState->GetObjectByName(targetString);
			if (obj != 0)
            {
                numberThatExist++;
                if (IsObjectWithinArea(obj))
                {
                    numberWithinArea++;
                }
            }
        }

        if (numberWithinArea >= quantity)
        {
            double t = simState->GetTime();

            if (startTime_s == 0) // assume 0 means is just being triggered
            {
                startTime_s = t;
            }

            if ((t - startTime_s) >= timeObjective_s)
            {
                goalState = isEnterGoal ? PASSED : FAILED;
            }
            return;
        }
        else
        {
            // quantity objects NOT within area, reset startTime_s
            startTime_s = 0;
            if (numberThatExist < quantity)
            {   // impossible to have quantity objects within area, so resolve goal
                goalState = isEnterGoal ? FAILED : PASSED;
            }
        }
	}
	else // AND behavior
	{
		for (size_t n=0; n<namedUnits.size(); n++)
		{
			std::string targetString(namedUnits[n].c_str());

			tcGameObject* obj = simState->GetObjectByName(targetString);

			if (obj == 0)
			{
				// obj doesn't exist, finalize goal status based on isEnterGoal type
				goalState = isEnterGoal ? FAILED : PASSED;
				return;
			}

			bool objectWithinArea = IsObjectWithinArea(obj);

			if (!objectWithinArea)
			{
				// at least one not in area, reset startTime_s and return
				startTime_s = 0; 
				return;
			}
		}

		// all objects are within area, check time for goal pass/fail
		double t = simState->GetTime();

		if (startTime_s == 0) // assume 0 means is just being triggered
		{
			startTime_s = t;
		}

		if ((t - startTime_s) >= timeObjective_s)
		{
			goalState = isEnterGoal ? PASSED : FAILED;
		}

	}
}

/**
* Open map object for this goal in edit mode. If map obj
* is open in non edit mode, then close it
*/
void tcAreaGoal::UpdateMapObject()
{
    bool isEditMode = tcGameObject::IsEditMode();

    if (isEditMode)
    {
        if (mapObjectId == -1)
        {
            tcGoalAreaEditObject* mapObject = new tcGoalAreaEditObject(tcGoal::GetId());
            mapObjectId = mapObject->GetKey();
            mapOverlay->AddMapObject(mapObject);
        }
    }
    else 
    {
        CloseMapObject();
    }
}

void tcAreaGoal::WriteStatus(std::stringstream& stream, unsigned int level)
{
	for (unsigned int n=0; n<level; n++)
	{
		stream << indentString;
	}

    std::string targetString = GetTargetListAsString();

	std::string logicType = GetQuantityDescription();

    if (isEnterGoal)
    {
        stream << "* Destination Goal -- " << logicType << targetString;	
        if (goalState == PASSED)
        {
            stream << " ACHIEVED.\n";
        }
        else
        {
            stream << " NOT ACHIEVED.\n";
        }
    }
    else
    {
        stream << "* Avoid Area Goal -- " << logicType << targetString;
        if (goalState == FAILED)
        {
            stream << " FAILED.\n";
        }
        else
        {
            stream << " SATISFIED.\n";
        }
    }
}

void tcAreaGoal::WriteStatus(wxArrayString& arrayString, unsigned int level)
{
    wxString line;
	for (unsigned int n=0; n<level; n++)
	{
		line += indentString.c_str();
	}

    wxString targetString = GetTargetListAsString();

	wxString elapsedTimeString;
	if ((startTime_s > 0) && (simState->GetTime() > 0))
	{
		float timeLeft_min = (1.0/60.0) * (timeObjective_s - float(simState->GetTime() - startTime_s));
		elapsedTimeString.Printf(" %.0f min remaining", timeLeft_min);
	}

    wxString logicType = GetQuantityDescription();

    if (isEnterGoal)
    {
        line += "* Destination Goal -- " + logicType + targetString;	
        if (goalState == PASSED)
        {
            line += " ACHIEVED";
        }
        else
        {
            line += " NOT ACHIEVED";
			line += elapsedTimeString;
        }
    }
    else
    {
        line += "* Avoid Area Goal -- " + logicType + targetString;
        if (goalState == FAILED)
        {
            line += " FAILED";
        }
        else
        {
            line += " SATISFIED";
			line += elapsedTimeString;
        }
    }

    arrayString.push_back(line);
}


void tcAreaGoal::WriteStatusB(std::stringstream& stream)
{
    std::string targetString = GetTargetListAsString();

    std::string logicType = GetQuantityDescription();


	logicType = logicType + (isEnterGoal ? "ENTER " : "AVOID ");

	stream << "* " << logicType << targetString;

	wxString elapsedTimeString;
	if ((startTime_s > 0) && (simState->GetTime() > 0))
	{
		float timeLeft_min = (1.0/60.0) * (timeObjective_s - float(simState->GetTime() - startTime_s));
		elapsedTimeString.Printf(" %.0f min remaining", timeLeft_min);
	}

    if (isEnterGoal)
    {
        if (goalState == PASSED)
        {
            stream << " ACHIEVED.\n";
        }
        else
        {
			stream << wxString::Format(" NOT ACHIEVED%s.\n", elapsedTimeString.c_str());
        }
    }
    else
    {
        if (goalState == FAILED)
        {
            stream << " FAILED.\n";
        }
        else
        {
			stream << wxString::Format(" SATISFIED%s.\n", elapsedTimeString.c_str());
        }
    }
}

void tcAreaGoal::WriteStatusB(wxArrayString& arrayString)
{
    wxString targetString = GetTargetListAsString();

    wxString logicType = GetQuantityDescription();
    
	wxString line("* " + logicType + targetString);

    if (isEnterGoal)
    {
        if (goalState == PASSED)
        {
            line += " ACHIEVED";
        }
        else
        {
            line += " NOT ACHIEVED";
        }
    }
    else
    {
        if (goalState == FAILED)
        {
            line += " FAILED";
        }
        else
        {
            line += " SATISFIED";
        }
    }

    arrayString.push_back(line);
}


tcAreaGoal::tcAreaGoal()
: isEnterGoal(true),
  alliance(0),
  timeObjective_s(0),
  startTime_s(0),
  isOR(true),
  quantity(1)
{
}

tcAreaGoal::tcAreaGoal(const tcAreaGoal& goal)
: tcGoal(goal),
  targetList(goal.targetList),
  isEnterGoal(goal.isEnterGoal),
  areaBounds(goal.areaBounds),
  alliance(goal.alliance),
  timeObjective_s(goal.timeObjective_s),
  startTime_s(goal.startTime_s),
  isOR(goal.isOR),
  quantity(goal.quantity)
{

}