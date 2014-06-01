/**
**  @file Brain.h
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

#ifndef _BRAIN_H_
#define _BRAIN_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include <map>
#include <queue>
#include <string>
#include <vector>

#include "ai/Blackboard.h"

namespace scriptinterface
{
	class tcScenarioLogger;
}

class tcPlatformObject;
class tcStream;
class tcCommandStream;
class tcGameStream;
class GeoPoint;

namespace ai
{


class Blackboard;
class BlackboardInterface;
class Task;
class Nav;



/**
* Holds tasks for "ai"
*/
class Brain 
{
public:
    /** task codes for C++ tasks */
    enum
    {
        TEST_TASK = 0,
        NAV_TASK = 1,
        POINTDEFENSE_TASK = 2
    };

	struct TaskInfo
	{
		std::string taskName;
		float priority;
		bool isHidden;
		bool isPermanent;
	};

	void AddTask(const std::string& taskName, double priority_, int attributes_ = 0);
	void AddTaskDirectly(const std::string& taskName, double priority_, int attributes_);
    /// gets a low priority, anonymous interface to board
    BlackboardInterface GetBlackboardInterface(); 
    Nav* GetNavTask();
    Task* GetTask(const std::string& taskName);
    
    bool IsTasked() const;
    std::vector<std::string> GetTaskList();
	std::vector<TaskInfo> GetTaskListInfo();
    double GetTaskPriority(const std::string& taskName) const;
    void RemoveAllTasks();
    void RemoveTask(const std::string& taskName);
    bool TaskExists(const std::string& taskName);

    long GetTarget() const;
    void SetTarget(long target_);

    const std::string& GetActionText() const;
    void SetActionText(const std::string& s);

    bool GetPatrolArea(std::vector<GeoPoint>& patrolArea) const;
    static void TransformPatrolAreaForAnchor(std::vector<GeoPoint>& patrolArea, const wxString& anchorUnit, int anchorMode, bool read);
    bool GetAnchorInfo(wxString& anchorUnit, int& anchorMode) const;

    void Update(double t);
       

    tcCommandStream& operator<<(tcCommandStream& stream);
    tcCommandStream& operator>>(tcCommandStream& stream);
    tcGameStream& operator<<(tcGameStream& stream);
    tcGameStream& operator>>(tcGameStream& stream);

    void ClearNewCommand();
    bool HasNewCommand() const;
	void SetNewCommand();
	virtual void SaveToPython(scriptinterface::tcScenarioLogger& logger);
    static void InitTaskNameLookup(); // call once at startup

	Brain(tcPlatformObject* platform_);
	~Brain();
private:
	struct TaskCommand
	{
		std::string taskName;
        bool removeTask; ///< if true then remove task, otherwise add
		float priority;
		int attributes;
	};

    tcPlatformObject* const platform;
    const float updateInterval;
    long nextId; ///< id assigned to next task
    double lastUpdateTime; ///< last time tasks were updated
    long target; ///< id of target (may be more general way to handle this)
    bool updating; ///< true if in the middle of Update
	bool hasNewCommand; ///< for multiplayer, true if task or bb state has been changed
	Blackboard board; ///< for inter-task communication
	std::map<std::string, Task*> taskMap;
    std::queue<std::string> removeList; ///< list of tasks to remove at next update
	std::vector<TaskCommand> clientTasks;
    std::string actionText;
    bool isTasked;

    static std::map<std::string, int> taskNameLookup;

    void RemovePending();
    void RemoveTaskNow(const std::string& taskName);
    void UpdateIsTasked();
};

}

#endif