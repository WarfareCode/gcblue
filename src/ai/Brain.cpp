/**
**  @file Brain.cpp
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

#include "ai/Brain.h"
#include "ai/BlackboardInterface.h"
#include "ai/Task.h"
#include "ai/Nav.h"
#include "ai/PointDefense.h"
#include "ai/ScriptedTask.h"
#include "ai/SelfPreservation.h"
#include "sim/tcPlatformObject.h"
#include "common/tcStream.h"
#include "common/tcObjStream.h"
#include "common/tcGameStream.h"
#include "tcScenarioLogger.h"
#include "tcSimState.h"
#include "simmath.h"
#include "tcEventManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif 

using namespace ai;


std::map<std::string, int> Brain::taskNameLookup;

void Brain::InitTaskNameLookup()
{
    if (taskNameLookup.find("Test") != taskNameLookup.end())
    {
        return; // already initialized
    }
    taskNameLookup["Test"] = TEST_TASK;
    taskNameLookup["Nav"] = NAV_TASK;
    taskNameLookup["PointDefense"] = POINTDEFENSE_TASK;
}



/**
* Loads state from command stream
*/
tcCommandStream& Brain::operator<<(tcCommandStream& stream)
{
	// client update
	if (platform->IsClientMode())
	{
        stream >> target; // server sends target ID to client

		unsigned char nTasks;
		stream >> nTasks;

		RemoveAllTasks();

		for (unsigned char n=0; n<nTasks; n++)
		{
			std::string taskName;
			stream >> taskName;

            bool removeTask;
            stream >> removeTask;
            wxASSERT(removeTask == false);

			float priority;
			stream >> priority;

			int attributes;
			stream >> attributes;

			AddTaskDirectly(taskName, (double)priority, attributes);
		}

		// update waypoints if nav task exists
		if (ai::Nav* nav = GetNavTask())
		{
			nav->operator<<(stream);
		}

		//fprintf(stdout, "CLIENT loading board cmds (%s)\n", platform->mzUnit.c_str());
		board.operator<<(stream);
	}
	// server update
	else
	{
		clientTasks.clear();

		unsigned char nTasks;
		stream >> nTasks;

		for (unsigned char n=0; n<nTasks; n++)
		{
			TaskCommand cmd;

			stream >> cmd.taskName;
            stream >> cmd.removeTask;
			stream >> cmd.priority;
			stream >> cmd.attributes;
			
			clientTasks.push_back(cmd); // queue for add in next update
		}

		//fprintf(stdout, "SERVER loading board cmds (%s)\n", platform->mzUnit.c_str());
		board.operator<<(stream);
	}

    return stream;
}

/**
* Saves state to command stream
*/
tcCommandStream& Brain::operator>>(tcCommandStream& stream)
{
	if (!platform->IsClientMode())
	{
        stream << target; // server sends target ID to client

		unsigned char nTasks = (unsigned char)taskMap.size();
		stream << nTasks;

		// iterate through task map and update tasks
		std::map<std::string, Task*>::iterator iter = taskMap.begin();
		std::map<std::string, Task*>::iterator done = taskMap.end(); 
		for (;iter != done; ++iter)
		{
			Task* task = iter->second;
			wxASSERT(task);

			stream << task->GetTaskName();

            bool removeTask = false;
            stream << removeTask; // never need to remove this way, since client always clears tasks before each update

			float priority = (float)task->GetPriority();
			stream << priority;

			int attributes = task->GetAttributes();
			stream << attributes;
		}

		// update waypoints if nav task exists
		if (ai::Nav* nav = GetNavTask())
		{
			nav->operator>>(stream);
		}

		//fprintf(stdout, "SERVER writing board cmds (%s)\n", platform->mzUnit.c_str());
		board.operator>>(stream);
	}
	else
	{
		unsigned char nTasks = (unsigned char)clientTasks.size();
		wxASSERT(clientTasks.size() <= 255);

		stream << nTasks;
		for (unsigned char n=0; n<nTasks; n++)
		{
			stream << clientTasks[n].taskName;
            stream << clientTasks[n].removeTask;
			stream << clientTasks[n].priority;
			stream << clientTasks[n].attributes;
		}


		//fprintf(stdout, "CLIENT writing board cmds (%s)\n", platform->mzUnit.c_str());
		board.operator>>(stream);
	}

    return stream;
}

/**
* Read from stream
*/
tcGameStream& Brain::operator<<(tcGameStream& stream)
{
    stream >> nextId;
    stream >> lastUpdateTime;
    stream >> target;
    stream >> updating;
    stream >> actionText;

	board << stream;

    taskMap.clear();
    unsigned int nTasks;
    stream >> nTasks;
    for (unsigned int n=0; n<nTasks; n++)
    {
        std::string taskName;
        stream >> taskName;

       
        long id;
        double priority;
        int attributes;

        stream >> id;
        stream >> priority;
        stream >> attributes;

        if (taskName == "Nav")
        {
            Nav* nav = new Nav(platform, &board, 
                id, priority, attributes, taskName);
            taskMap[taskName] = nav;
            nav->operator<<(stream);
        }
        else if (taskName == "PointDefense")
        {
            PointDefense* pd = new PointDefense(platform, &board, 
                id, priority, attributes, taskName);
            taskMap[taskName] = pd;
            pd->operator<<(stream);
        }
        else
        {
            ScriptedTask* scriptedTask = new ScriptedTask(platform, &board, 
                id, priority, attributes, taskName);
            taskMap[taskName] = scriptedTask;
            scriptedTask->operator<<(stream);
        }
    }

    stream.ReadCheckValue(3245);

    return stream;
}

/**
* Write to stream
*/
tcGameStream& Brain::operator>>(tcGameStream& stream)
{
    stream << nextId;
    stream << lastUpdateTime;
    stream << target;
    stream << updating;
    stream << actionText;

    board >> stream;

    unsigned int nTasks = (unsigned int)taskMap.size();
    stream << nTasks;
    for (std::map<std::string, Task*>::iterator iter = taskMap.begin();
        iter != taskMap.end(); ++iter)
    {
        std::string taskName = iter->first;
        stream << taskName;

        Task* task = iter->second;
        long id = task->GetAuthor();
        double priority = task->GetPriority();
        int attributes = task->GetAttributes();

        stream << id;
        stream << priority;
        stream << attributes;

        task->operator>>(stream);
    }

    stream.WriteCheckValue(3245);

    return stream; 
}


void Brain::ClearNewCommand()
{
	hasNewCommand = false;

	if (platform->IsClientMode())
	{
		clientTasks.clear();
	}

	board.ClearNewCommand();
}

bool Brain::HasNewCommand() const
{
	return hasNewCommand || board.HasNewCommand();
}



const std::string& Brain::GetActionText() const
{
    return actionText;
}


/**
* gets a low priority, anonymous interface to board
*/
BlackboardInterface Brain::GetBlackboardInterface()
{
    return BlackboardInterface(&board, 0, 0.0);  
}

/**
* @return pointer to Nav task or 0 if none exists
*/
Nav* Brain::GetNavTask()
{
    std::map<std::string, Task*>::iterator iter = taskMap.find("Nav");
    if (iter != taskMap.end())
    {
        wxASSERT(iter->second);
        return dynamic_cast<Nav*>(iter->second);
    }
    else
    {
        return 0;
    }
}

/**
* @return point to task of 0 if not found
*/
Task* Brain::GetTask(const std::string& taskName)
{
    std::map<std::string, Task*>::iterator iter = taskMap.find(taskName);
    if (iter != taskMap.end())
    {
        wxASSERT(iter->second);
        return dynamic_cast<Nav*>(iter->second);
    }
    else
    {
        return 0;
    }
}

/**
* @return target id for platform
*/
long Brain::GetTarget() const
{
    return target;
}


bool Brain::IsTasked() const
{
    return isTasked;
}


void Brain::UpdateIsTasked()
{
    isTasked = false;

    // iterate through task map and update tasks
    std::map<std::string, Task*>::const_iterator iter = taskMap.begin();
    std::map<std::string, Task*>::const_iterator done = taskMap.end(); 
    for (;iter != done; ++iter)
    {
        isTasked |= !iter->second->IsHidden();
    }
    
    isTasked |= platform->formation.IsFollower(); // declare all followers as "tasked"
}

void Brain::SaveToPython(scriptinterface::tcScenarioLogger& logger)
{
	wxString s;

    std::map<std::string, Task*>::iterator iter = taskMap.begin();
    std::map<std::string, Task*>::iterator done = taskMap.end(); 
    for (;iter != done; ++iter)
    {
		Task* task = iter->second;
        wxASSERT(task);
        
		const std::string& taskName = task->GetTaskName();

        s.Printf("UI.AddTask('%s', %f, %d)", taskName.c_str(), task->GetPriority(), task->GetAttributes());
		logger.AddScenarioText(s);

		if (Nav* nav = dynamic_cast<Nav*>(task))
		{
            const std::vector<Nav::WaypointData>& waypoints =  nav->GetWaypoints();
			for (size_t k=0; k<waypoints.size(); k++)
			{
				s.Printf("UI.AddNavWaypointAdvanced(%f, %f, %f, %f)", waypoints[k].waypoint.mfLon_rad,
                    waypoints[k].waypoint.mfLat_rad, waypoints[k].waypoint.mfAlt_m, waypoints[k].speed_kts);
                logger.AddScenarioText(s);

                if (waypoints[k].tasks.size() > 0)
                {
                    s.Printf("UI.SetNavWaypointTasks(%d, '%s')", k, nav->GetWaypointTasklistString(k));
                    logger.AddScenarioText(s);
                }
            }
            if (nav->GetLoopState() == true)
            {
                s.Printf("UI.SetNavLoopState(1)");
				logger.AddScenarioText(s);
            }
		}
    }

	// write blackboard contents
    logger.AddScenarioText("BB = UI.GetBlackboardInterface()");
    board.SaveToPython(logger);

    
}


void Brain::SetActionText(const std::string& s)
{
    actionText = s;
}

/**
* For multiplayer, call when task is added or deleted, or nav task waypoints have changed
*/
void Brain::SetNewCommand()
{
	hasNewCommand = true;
}

/**
* Set target id for platform
*/
void Brain::SetTarget(long target_)
{
    if (target == target_) return;

    if (!platform->IsClientMode())
    {
        tcSimState* simState = tcSimState::Get();

        if (tcGameObject* oldTargetObj = simState->GetObject(target))
        {
            oldTargetObj->RemoveTargeter(platform->mnID);
        }

        if (tcGameObject* newTargetObj = simState->GetObject(target_))
        {
            newTargetObj->AddTargeter(platform->mnID);
        }
    }

    target = target_;

    hasNewCommand = true;
}

/**
* Assumed that this is used for display purposes so hidden tasks are NOT
* returned in this list.
* @return list of task names
*/
std::vector<std::string> Brain::GetTaskList()
{
    std::vector<std::string> taskList;

    std::map<std::string, Task*>::const_iterator iter = taskMap.begin();
    std::map<std::string, Task*>::const_iterator done = taskMap.end(); 
    for (;iter != done; ++iter)
    {
		if (!iter->second->IsHidden())
		{
			taskList.push_back(iter->first);
		}
    }

    return taskList;
}

/**
* Version that returns info on all tasks, including hidden
*/
std::vector<Brain::TaskInfo> Brain::GetTaskListInfo()
{
	std::vector<Brain::TaskInfo> taskInfo;

    std::map<std::string, Task*>::const_iterator iter = taskMap.begin();
    std::map<std::string, Task*>::const_iterator done = taskMap.end(); 
    for (;iter != done; ++iter)
    {
		TaskInfo info;
		info.taskName = iter->first;
		info.isHidden = iter->second->IsHidden();
		info.isPermanent = iter->second->IsPermanent();
		info.priority = (float)iter->second->GetPriority();
		
		taskInfo.push_back(info);
    }

    return taskInfo;
}

/**
* @return priority of task or -1.0 if not found
*/
double Brain::GetTaskPriority(const std::string& taskName) const
{
    std::map<std::string, Task*>::const_iterator iter = taskMap.find(taskName);
    if (iter != taskMap.end())
    {
        wxASSERT(iter->second);
        return iter->second->GetPriority();
    }
    else
    {
        return -1.0;
    }
}

/**
* Version that pushes task to command list and marks new command for multiplayer
*/
void Brain::AddTask(const std::string& taskName, double priority_, int attributes_)
{
	if (platform->IsClientMode())
	{
		TaskCommand cmd;
		cmd.taskName = taskName;
        cmd.removeTask = false;
		cmd.priority = float(priority_);
		cmd.attributes = attributes_;

		clientTasks.push_back(cmd);

		SetNewCommand();
		return;
	}

	hasNewCommand = true;

	AddTaskDirectly(taskName, priority_, attributes_);
}

/**
* Adds task without any multiplayer operations
*/
void Brain::AddTaskDirectly(const std::string& taskName, double priority_, int attributes_)
{
    if (TaskExists("AutoLoiter"))
    {
        RemoveTask("AutoLoiter"); // clear auto-loiter when any new task is added
    }

    // if task already exists, update priority and attributes
    std::map<std::string, Task*>::iterator tm_iter = taskMap.find(taskName);
    if (tm_iter != taskMap.end())
    {
        tm_iter->second->SetPriority(priority_);
		tm_iter->second->SetAttributes(attributes_);
#ifdef _DEBUG
        fprintf(stderr, "Warning - Brain::AddTask - task already exists, "
			"updating priority and attributes (%s)\n", taskName.c_str());
#endif
        return;
    }

    // check taskNameMap for C++ task, otherwise assume python script task
    std::map<std::string, int>::iterator iter = taskNameLookup.find(taskName);
    if (iter == taskNameLookup.end())
    {
        taskMap[taskName] = new ScriptedTask(platform, &board, 
            nextId++, priority_, attributes_, taskName);
    }
    else
    {
        int taskCode = iter->second;
        // add switch for C++ task addition
        switch (taskCode)
        {
        case TEST_TASK:
            fprintf(stdout, "Test task called with priority %.1f\n", priority_);
            break;
        case NAV_TASK:
            taskMap[taskName] = new Nav(platform, &board, 
                nextId++, priority_, attributes_, taskName);
            break;
        case POINTDEFENSE_TASK:
            taskMap[taskName] = new PointDefense(platform, &board, 
                nextId++, priority_, attributes_, taskName);
            break;
        default:
            fprintf(stderr, "Unrecognized C++ taskname (%s)\n", taskName.c_str());
			hasNewCommand = false;
            break;
        }

    }
}


/**
* Removes all tasks. Cannot be called in the middle of an
* update (i.e. can't be called by task)
*/
void Brain::RemoveAllTasks()
{
    if (updating) return;
    
	if (taskMap.size() > 0) hasNewCommand = true;

	// additional test to avoid infinite loop due to permanent task
	size_t nTasks = taskMap.size();
	size_t nChecked = 0;

    std::map<std::string, Task*>::iterator iter = taskMap.begin();
    while ((iter != taskMap.end()) && (nChecked++ < nTasks))
    {
		if (!iter->second->IsPermanent())
		{
            board.EraseAllFromAuthor(iter->second->GetAuthor());
			delete iter->second;
			taskMap.erase(iter++);
		}
        else
        {
            ++iter;
        }
    }

    SetActionText("");
}

/**
* Removes tasks in removeList. This allows a task to safely delete itself.
*/
void Brain::RemovePending()
{
    unsigned int nRemoved = 0;
    bool wasTasked = IsTasked();

    while (!removeList.empty())
    {
        std::string taskName = removeList.front();
        removeList.pop();

        RemoveTaskNow(taskName);
        nRemoved++;
    }

    // if no longer tasked after remove, add a loiter task to keep unit from
    // flying/sailing off the map
    if ((nRemoved == 0) || !wasTasked) return;

    UpdateIsTasked();
    if (!IsTasked())
    {
        if ((platform != 0) && (platform->mnModelType != MTYPE_GROUNDVEHICLE))
        {
            AddTask("AutoLoiter", 2.0, ai::Task::HIDDEN);
            tcEventManager::Get()->IdlePlatform(platform->GetAlliance());
        }
    }

}

/**
* Adds task to removeList for removal during next update.
*/
void Brain::RemoveTask(const std::string& taskName)
{
    if (platform->IsClientMode())
	{
		TaskCommand cmd;
		cmd.taskName = taskName;
        cmd.removeTask = true;
		cmd.priority = 0;
		cmd.attributes = 0;

		clientTasks.push_back(cmd);

		SetNewCommand();
		return;
	}

    removeList.push(taskName);
}

/**
* Immediately removes task
*/
void Brain::RemoveTaskNow(const std::string& taskName)
{
    std::map<std::string, Task*>::iterator iter = taskMap.find(taskName);
    if (iter != taskMap.end())
    {
		if (iter->second->IsPermanent())
		{
			return; // ignore request
		}

        // remove all blackboard entries from the author being erased
        board.EraseAllFromAuthor(iter->second->GetAuthor());
        delete iter->second;
        taskMap.erase(iter);

		hasNewCommand = true;

        SetActionText(""); // clear action text anytime a task is erased since no way to track which task wrote
    }
}

bool Brain::TaskExists(const std::string& taskName)
{
    return (taskMap.find(taskName) != taskMap.end());
}

void Brain::Update(double t)
{
    if (((t - lastUpdateTime) < updateInterval) && (!tcGameObject::IsEditMode()))
    {
        return;
    }

    if (platform->IsClientMode())
    {
        // update isTasked variable
        std::map<std::string, Task*>::iterator iter = taskMap.begin();
        std::map<std::string, Task*>::iterator done = taskMap.end(); 
        for (;iter != done; ++iter)
        {
            wxASSERT(iter->second);

            // iter->second->Update(t); // commented out, why was this here? 19SEP2008

            isTasked |= !iter->second->IsHidden();
        }

        isTasked |= platform->formation.IsFollower(); // declare all followers as "tasked"

        return; // server updates only in multiplayer mode
    }

    RemovePending();
    
	// in multiplayer, add pending client tasks
	size_t nPendingClientTasks = clientTasks.size();
	if (nPendingClientTasks > 0)
	{
		for (size_t n=0; n<nPendingClientTasks; n++)
		{
            if (clientTasks[n].removeTask == false)
            {
			    AddTask(clientTasks[n].taskName, clientTasks[n].priority, clientTasks[n].attributes);
            }
            else
            {
                RemoveTask(clientTasks[n].taskName);
            }
		}
		clientTasks.clear();

        RemovePending();
	}

    updating = true;
    
    isTasked = false;

    // iterate through task map and update tasks
    std::map<std::string, Task*>::iterator iter = taskMap.begin();
    std::map<std::string, Task*>::iterator done = taskMap.end(); 
    for (;iter != done; ++iter)
    {
        wxASSERT(iter->second);
        
        iter->second->Update(t);

        isTasked |= !iter->second->IsHidden();
    }
    
    isTasked |= platform->formation.IsFollower(); // declare all followers as "tasked"

    lastUpdateTime = t;
    
    updating = false;
}



/**
* @return true if patrol area exists
* @patrolArea set to points of patrol area, adjusted for anchor mode
*/
bool Brain::GetPatrolArea(std::vector<GeoPoint>& patrolArea) const
{
    patrolArea.clear();

    if (!board.KeyExists("PatrolArea")) return false;

    wxString areaString(board.ReadMessage("PatrolArea").c_str());

    wxString slon = areaString.BeforeFirst(',');
    areaString = areaString.AfterFirst(',');
    wxString slat = areaString.BeforeFirst(',');
    areaString = areaString.AfterFirst(',');

    unsigned int iterations = 0;
    while ((slat.size() > 0) && (iterations++ < 256))
    {
        double lon_rad = 0;
        double lat_rad = 0;
        slon.ToDouble(&lon_rad);
        slat.ToDouble(&lat_rad);

        GeoPoint p;
        p.Set(lon_rad, lat_rad, 0);
        patrolArea.push_back(p);

        slon = areaString.BeforeFirst(',');
        areaString = areaString.AfterFirst(',');
        slat = areaString.BeforeFirst(',');
        areaString = areaString.AfterFirst(',');
    }

    // if "PatrolAnchor" exists then adjust patrol area based on anchor platform
    wxString anchorUnit;
    int anchorMode;

    bool hasAnchorInfo = GetAnchorInfo(anchorUnit, anchorMode);
    if (!hasAnchorInfo || (anchorMode == 0)) return true;

    TransformPatrolAreaForAnchor(patrolArea, anchorUnit, anchorMode, true);

    return true;
}

/**
* @param read true to transform from relative anchor coords to world coords, false for reverse
*/
void Brain::TransformPatrolAreaForAnchor(std::vector<GeoPoint>& patrolArea, const wxString& anchorUnit, int anchorMode, bool read)
{
    tcSimState* simState = tcSimState::Get();
    tcGameObject* obj = simState->GetObjectByName(anchorUnit.ToStdString());
    if (obj == 0) return;

    float lon_rad = obj->mcKin.mfLon_rad;
    float lat_rad = obj->mcKin.mfLat_rad;
    float hdg_rad = obj->mcKin.mfHeading_rad;

    switch (anchorMode)
    {
    case 0:
        break;
    case 1: // north-relative
        {
            if (read)
            {
                for (size_t n=0; n<patrolArea.size(); n++)
                {
                    patrolArea[n].mfLon_rad += lon_rad;
                    patrolArea[n].mfLat_rad += lat_rad;
                }
            }
            else
            {
                for (size_t n=0; n<patrolArea.size(); n++)
                {
                    patrolArea[n].mfLon_rad -= lon_rad;
                    patrolArea[n].mfLat_rad -= lat_rad;
                }
            }
        }
        break;
    case 2: // heading relative
        {
            float sin_hdg = sinf(hdg_rad);
            float cos_hdg = cosf(hdg_rad);
            float cos_lat = cosf(lat_rad);
            float sec_lat = 1.0/cos_lat;

            if (read)
            {
                for (size_t n=0; n<patrolArea.size(); n++)
                {
                    float dx_rad = patrolArea[n].mfLon_rad; // cross-track
                    float dy_rad = patrolArea[n].mfLat_rad; // along-track

                    patrolArea[n].mfLon_rad = lon_rad + sec_lat*(cos_hdg*dx_rad + sin_hdg*dy_rad);
                    patrolArea[n].mfLat_rad = lat_rad - sin_hdg*dx_rad + cos_hdg*dy_rad;
                }
            }
            else
            {

                for (size_t n=0; n<patrolArea.size(); n++)
                {
                    float term1 = cos_lat*(patrolArea[n].mfLon_rad - lon_rad);
                    float term2 = patrolArea[n].mfLat_rad - lat_rad;
                    patrolArea[n].mfLon_rad = cos_hdg*term1 - sin_hdg*term2;
                    patrolArea[n].mfLat_rad = sin_hdg*term1 + cos_hdg*term2;
                }
            }
        }
        break;
    default:
        wxASSERT(false);
        break;
    }


}

/**
* @return true if anchor info exists (area is anchor mode)
*/
bool Brain::GetAnchorInfo(wxString& anchorUnit, int& anchorMode) const
{
    anchorUnit.clear();
    anchorMode = 0;

    wxString anchorString(board.ReadMessage("PatrolAnchor").c_str());
    if (anchorString.size() == 0) return false;

    // PatrolAnchor: <anchor unitname>, <anchor mode>

    anchorUnit = anchorString.BeforeFirst(',');
    wxString modeString = anchorString.AfterFirst(',');

    long val = 0;
    if (modeString.ToLong(&val))
    {
        anchorMode = int(val);
        
        return true;
    }
    else
    {
        anchorUnit.clear();
        return false;
    }

}


Brain::Brain(tcPlatformObject* platform_)
: platform(platform_),
  updateInterval(0.125f),
  nextId(1),
  target(-1),
  updating(false),
  hasNewCommand(false),
  isTasked(false)
{
    wxASSERT(platform);
    
    //InitTaskNameLookup(); // changed to have separate call in app init for this

    lastUpdateTime = randf(updateInterval); // randomize update phase
}

Brain::~Brain()
{
    for (std::map<std::string, Task*>::iterator iter = 
        taskMap.begin(); iter != taskMap.end(); )
    { 
        delete iter->second;
        taskMap.erase(iter++); 
    }   
    taskMap.clear();
}



