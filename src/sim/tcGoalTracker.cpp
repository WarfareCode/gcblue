/**  
**  @file tcGoalTracker.cpp
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

#include <sstream>
#include <fstream>
#include "tcGoalTracker.h"
#include "tcGoal.h"
#include "tcSimState.h"
#include "tcUserInfo.h"
#include "common/tcStream.h"
#include "common/tcObjStream.h"
#include "tcGameStream.h"
#include "tcAllianceInfo.h"
#include "tcGameObject.h"
#include "wx/xml/xml.h"
#include "tcSensorTrackIterator.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif 

/**
* Singleton accessor
*/
tcGoalTracker* tcGoalTracker::Get()
{
	static tcGoalTracker instance;

	return &instance;
}

/**
* Loads state from update stream
*/
tcUpdateStream& tcGoalTracker::operator<<(tcUpdateStream& stream)
{
	bool allianceFailedPrev = allianceFailed;
	bool allianceSucceededPrev = allianceSucceeded;

	stream >> allianceFailed;
	stream >> allianceSucceeded;
	stream >> goalStatusDescription;

	statusChanged = (allianceFailed != allianceFailedPrev) ||
		            (allianceSucceeded != allianceSucceededPrev);

    return stream;
}

/**
* Saves state to update stream
* alliance value must be stored with stream.SetDetailLevel
*/
tcUpdateStream& tcGoalTracker::operator>>(tcUpdateStream& stream)
{
	int alliance = stream.GetDetailLevel(); // a hack, really should not do this
	
	allianceFailed = HasAllianceFailed(alliance);
	allianceSucceeded = HasAllianceSucceeded(alliance);
	goalStatusDescription = GetAllianceGoalStatusDescription(alliance);

	stream << allianceFailed;
	stream << allianceSucceeded;
	stream << goalStatusDescription;

    return stream;
}

/**
* Load
*/
tcGameStream& tcGoalTracker::operator<<(tcGameStream& stream)
{
    Clear();

    stream >> lastUpdateTime;
    stream >> perfectScore;

    unsigned int nGoals;
    stream >> nGoals;

    for (unsigned int k=0; k<nGoals; k++)
    {
        bool isValid;
        stream >> isValid;

        if (isValid)
        {
            int alliance;
            stream >> alliance;

            float scoreOffset;
            stream >> scoreOffset;

            ROEStatus allianceROE;
			int val;
			stream >> val;
			allianceROE.airMode = (ROEMode)val;
			stream >> val;
			allianceROE.surfMode = (ROEMode)val;
			stream >> val;
			allianceROE.subMode = (ROEMode)val;
			stream >> val;
			allianceROE.landMode = (ROEMode)val;
			stream >> allianceROE.roeViolations;


            int goalType;
            stream >> goalType;

            if (goalType == 0)
            { // WORKAROUND, should be able to eliminate this eventually
                //stream >> goalState; // int, skip this since goalType read was this value, coincidentally always 0 for tcGoal type
                float tempFloat;
                unsigned long tempULong;
                unsigned int tempUInt;
                stream >> tempFloat; // failScore
                stream >> tempFloat; // passScore
                stream >> tempULong; // id
                stream >> tempUInt; // alliance
            }
            else
            {
                tcGoal* goal = tcGoal::CreateByType(goalType);
                if (goal != 0)
                {
                    *goal << stream;

                    SetAllianceGoal(alliance, goal);
                    AdjustAllianceScore(alliance, scoreOffset);
                    SetAllianceROE(alliance, allianceROE);
                }
                else
                {
                    wxASSERT(false);
                    throw "Invalid goal in scenario file";
                }
            }
        }
    }

    // load damageLog
    unsigned int nLog;
    stream >> nLog;

    for (unsigned int n=0; n<nLog; n++)
    {
        std::string unitName;
        stream >> unitName;

        DamageReport report;
        report.unitName = unitName;
        stream >> report.alliance;
        stream >> report.databaseClass;
        stream >> report.classification;
        stream >> report.time;
        stream >> report.damageFraction;
        stream >> report.landed;

        stream >> report.damagerClass;
        stream >> report.damagerQuantity;

        damageLog[unitName] = report;
    }



    return stream;
}

/**
* Save
*/
tcGameStream& tcGoalTracker::operator>>(tcGameStream& stream)
{
    stream << lastUpdateTime;
    stream << perfectScore;

    unsigned int nGoals = (unsigned int)allianceGoals.size();
    stream << nGoals;

    std::map<int, tcGoal*>::iterator iter = allianceGoals.begin();

    for (; iter != allianceGoals.end(); ++iter)
    {
        int alliance = iter->first;
        tcGoal* allianceGoal = iter->second;
        bool isValid = (allianceGoal != 0) && (allianceGoal->GetType() != 0); // 7 APR 2012, fixed so we don't save default tcGoals

        stream << isValid;

        if (isValid)
        {
            float scoreOffset = GetAllianceOffset(alliance);
            ROEStatus allianceROE = GetAllianceROE(alliance);

            stream << alliance;
            stream << scoreOffset;
			stream << allianceROE.airMode;
			stream << allianceROE.surfMode;
			stream << allianceROE.subMode;
			stream << allianceROE.landMode;
			stream << allianceROE.roeViolations;

            *allianceGoal >> stream; // all goals save their type as first field
        }
    }

    // save damageLog
    unsigned int nLog = damageLog.size();
    stream << nLog;
    std::map<std::string, DamageReport>::const_iterator logIter =
        damageLog.begin();
    for (; logIter != damageLog.end(); ++logIter)
    {
        stream << logIter->first;

        DamageReport report = logIter->second;
        stream << report.alliance;
        stream << report.databaseClass;
        stream << report.classification;
        stream << report.time;
        stream << report.damageFraction;
        stream << report.landed;

        stream << report.damagerClass;
        stream << report.damagerQuantity;
    }

    return stream;
}

/**
* Add or update damage report
*/
void tcGoalTracker::AddDamageReport(const std::string& unitName, const DamageReport& report)
{
    std::map<std::string, DamageReport>::iterator iter =
        damageLog.find(unitName);

    if (iter == damageLog.end())
    {
        damageLog[unitName] = report;
        return;
    }

    DamageReport& logData = iter->second;

    wxASSERT(report.unitName == unitName);
    wxASSERT(report.alliance == logData.alliance);
    wxASSERT(report.databaseClass == logData.databaseClass);
    wxASSERT(report.classification == logData.classification);
    wxASSERT(report.time >= logData.time);
    wxASSERT(logData.damagerClass.size() == logData.damagerQuantity.size());
    wxASSERT(report.damagerClass.size() <= 1);

    logData.time = report.time;
    logData.damageFraction = report.damageFraction;
    logData.landed = report.landed;

    if (report.damagerClass.size() == 0) return; // crash damage, populate with "crash" type?

    // search for matching damagerClass and increment quantity if found
    for (size_t n=0; n<logData.damagerClass.size(); n++)
    {
        if (report.damagerClass[0] == logData.damagerClass[n])
        {
            logData.damagerQuantity[n]++;
            return;
        }
    }

    const size_t MAX_DAMAGERS = 4;
    if (logData.damagerClass.size() >= MAX_DAMAGERS)
    {
        for (size_t k=1; k<logData.damagerClass.size(); k++)
        {
            logData.damagerClass[k-1] = logData.damagerClass[k];
            logData.damagerQuantity[k-1] = logData.damagerQuantity[k];
        }
        logData.damagerClass.pop_back();
        logData.damagerQuantity.pop_back();
    }

    logData.damagerClass.push_back(report.damagerClass[0]);
    logData.damagerQuantity.push_back(1);
    wxASSERT(report.damagerQuantity[0] == 1);
}

/**
* Clears all alliance goals.
*/
void tcGoalTracker::Clear()
{
    for(int i=0;i<MAX_ALLIANCES;i++)
    {
        if (allianceGoals[i])
        {
            delete allianceGoals[i];
            allianceGoals[i] = new tcGoal(); // set default goal (always unresolved) (leaks memory)
			previousGoalStatus[i] = tcGoal::UNRESOLVED;
        }
    }

	allianceFailed = false;
	allianceSucceeded = false;
	statusChanged = false;
	goalStatusDescription.clear();
    allianceScoreOffset.clear();
    reportedNoGoals = false;
    lastUpdateTime = -updateInterval; // so first update happens immediately after game start

    damageLog.clear();
}


const std::string& tcGoalTracker::GetAllianceGoalStatusDescription(int alliance)
{
	static std::string resultString;

	if (tcSimState::Get()->IsMultiplayerClient())
	{
		if (tcUserInfo::Get()->IsOwnAlliance(alliance))
		{
			return goalStatusDescription;
		}
		else
		{
			resultString = "Error";
			return resultString;
		}
	}

	std::stringstream statusStream;

	WriteStatus(statusStream, alliance);
		
	resultString = statusStream.str();
	return resultString;
}

void tcGoalTracker::GetAllianceGoalStatusDescription(int alliance, wxArrayString& arrayString)
{
    arrayString.clear();

	if (tcSimState::Get()->IsMultiplayerClient())
	{
        wxASSERT(false);
        return;
	}

	WriteStatus(arrayString, alliance);
}


/**
* @return score offset for alliance, normally enemy damages - alliance damages in thousands of dollars
*/
float tcGoalTracker::GetAllianceOffset(int alliance)
{
    std::map<int, float>::const_iterator iter = allianceScoreOffset.find(alliance);

    float scoreOffset = 0;
    if (iter != allianceScoreOffset.end())
    {
        scoreOffset = iter->second;
    }
    
    return scoreOffset;
}

/**
* @return current ROE info for alliance
*/
tcGoalTracker::ROEStatus tcGoalTracker::GetAllianceROE(int alliance) const
{
    std::map<int, ROEStatus>::const_iterator iter = allianceROE.find(alliance);

	ROEStatus roeStatus;
	roeStatus.airMode = WEAPONS_FREE; // default to weapons free
	roeStatus.surfMode = WEAPONS_FREE; // default to weapons free
	roeStatus.subMode = WEAPONS_FREE; // default to weapons free
	roeStatus.landMode = WEAPONS_FREE; // default to weapons free
	roeStatus.roeViolations = 0;

    if (iter != allianceROE.end())
    {
        roeStatus = iter->second;
    }
    
    return roeStatus;
}


float tcGoalTracker::GetAllianceScore(int alliance)
{
    const tcGoal* goal = GetAllianceGoal(alliance);

    float scoreOffset = GetAllianceOffset(alliance);
    
    if (goal != 0)
    {
        return scoreOffset + goal->GetNetScore();
    }
    else
    {
        fprintf(stderr, "tcGoalTracker::GetAllianceScore - alliance not found\n");
        return -999.0f;
    }
}


bool EquipmentSortPredicate(const tcGoalTracker::EquipmentReport& a, const tcGoalTracker::EquipmentReport& b)
{
    return (a.databaseClass.compare(b.databaseClass) > 0);
}


void tcGoalTracker::GetDamageReportSummary(unsigned int alliance, std::vector<DamageReport>& damageSummary) const
{
    damageSummary.clear();

    std::map<std::string, DamageReport>::const_iterator iter =
        damageLog.begin();

    for (; iter!=damageLog.end(); ++iter)
    {
        //const std::string& unitName = iter->first;
        const DamageReport& logData = iter->second;

        bool includeInReport = false;
        switch (logData.classification)
        {
        case PTYPE_SMALLSURFACE:
        case PTYPE_LARGESURFACE:
        case PTYPE_CARRIER:
        case PTYPE_FIXEDWING:
        case PTYPE_HELO:
        case PTYPE_SUBMARINE:
        case PTYPE_GROUND:
        case PTYPE_AIRFIELD:
            includeInReport = true;
            break;
        default:
            includeInReport = false;
        }

        if (includeInReport && (logData.alliance == alliance))
        {
            damageSummary.push_back(logData);
        }
    }

}


void tcGoalTracker::GetExpendedEquipmentSummary(unsigned int alliance, std::vector<EquipmentReport>& equipmentSummary) const
{
    equipmentSummary.clear();

    // first build unsorted equipment report for <alliance>
    std::vector<EquipmentReport> equipment;

    std::map<std::string, DamageReport>::const_iterator iter =
        damageLog.begin();

    for (; iter!=damageLog.end(); ++iter)
    {
        //const std::string& unitName = iter->first;
        const DamageReport& logData = iter->second;

        bool includeInReport = false;
        switch (logData.classification)
        {
        case PTYPE_AIRCM:
        case PTYPE_MISSILE:
        case PTYPE_TORPEDO:
        case PTYPE_SONOBUOY:
        case PTYPE_WATERCM:
        case PTYPE_WATERMINE:
        case PTYPE_BALLISTIC:
            includeInReport = true;
            break;
        default:
            includeInReport = false;
        }

        if (includeInReport && (logData.alliance == alliance))
        {
            EquipmentReport report;
            report.databaseClass = logData.databaseClass;
            report.quantity = 1;

            equipment.push_back(report);
        }
    }

    if (equipment.size() == 0)
    {
        return;
    }

    // sort by class name
    std::sort(equipment.begin(), equipment.end(), EquipmentSortPredicate);

    // combine matching databaseClass into one report per equipment databaseClass
    EquipmentReport mergedReport = equipment[0];
    for (size_t k=1; k<equipment.size(); k++)
    {
        if (equipment[k].databaseClass == mergedReport.databaseClass)
        {
            mergedReport.quantity++;
        }
        else
        {
            equipmentSummary.push_back(mergedReport);
            mergedReport = equipment[k];
        }
    }
    equipmentSummary.push_back(mergedReport);

}

/**
* Adds offset to alliance score for non-goal score adjustments (e.g. loss of equipment or
* destruction of enemy equipment)
*/
void tcGoalTracker::AdjustAllianceScore(int alliance, float offset)
{
    std::map<int, float>::iterator iter = allianceScoreOffset.find(alliance);

    if (iter != allianceScoreOffset.end())
    {
        iter->second += offset;
    }
    else
    {
        allianceScoreOffset[alliance] = offset;
    }
}

void tcGoalTracker::SetPerfectScore(float score)
{
    perfectScore = score;
}


/**
* @return true if alliance has failed.
*/
bool tcGoalTracker::HasAllianceFailed(int alliance)
{
    if ((alliance < 0)||(alliance >= MAX_ALLIANCES))
    {
        wxMessageBox("Alliance out of range in tcGoalTracker::HasAllianceFailed");
        return false;
    }
    tcGoal *goal = allianceGoals[alliance];
    if (goal == NULL)
    {
        ReportNoGoals(alliance);
        return false;
    }
    else
    {
        return goal->IsFailed();
    }
}

/**
* @return true if alliance has succeeded.
*/
bool tcGoalTracker::HasAllianceSucceeded(int alliance)
{
    if ((alliance < 0)||(alliance >= MAX_ALLIANCES))
    {
        wxMessageBox("Alliance out of range in tcGoalTracker::HasAllianceSucceeded");
        return false;
    }
    tcGoal *goal = allianceGoals[alliance];
    if (goal == NULL)
    {
        ReportNoGoals(alliance);
        return false;
    }
    else
    {
        return goal->IsPassed();
    }
}

/**
* @return true if goalState for alliance changed during last update
*/
bool tcGoalTracker::HasStatusChanged(int alliance)
{
	if (tcSimState::Get()->IsMultiplayerClient())
	{
		if (statusChanged)
		{
			// set false so that HasStatusChanged returns true only once per change
			statusChanged = false; 
			return true;
		}
		return false;
	}

	tcGoal* allianceGoal = allianceGoals[alliance];
    if (!allianceGoal) return false;

	bool result = (allianceGoal && 
		(allianceGoal->goalState != previousGoalStatus[alliance]));

    previousGoalStatus[alliance] = allianceGoal->goalState;

    return result;
}

bool tcGoalTracker::IsTargetLegal(tcGameObject* attacker, tcSensorMapTrack* targetTrack) const
{
    wxASSERT(attacker != 0);
	
	if (targetTrack == 0) return false;

    unsigned int attackerAlliance = attacker->GetAlliance();
    ROEStatus roeStatus = GetAllianceROE(int(attackerAlliance));


	bool isWeapon = (targetTrack->IsMissile() || targetTrack->IsTorpedo()) && (targetTrack->mnAffiliation != tcAllianceInfo::FRIENDLY);
	bool isHostile = targetTrack->IsIdentified() && (targetTrack->mnAffiliation == tcAllianceInfo::HOSTILE);
	bool isNeutralOrFriendly = (targetTrack->mnAffiliation == tcAllianceInfo::NEUTRAL) ||
							   (targetTrack->mnAffiliation == tcAllianceInfo::FRIENDLY);

	ROEMode roeMode = WEAPONS_HOLD;
	switch (targetTrack->mnClassification)
	{
	case PTYPE_AIR:
	case PTYPE_FIXEDWING:
	case PTYPE_HELO:
	case PTYPE_AIRCM:
	case PTYPE_MISSILE:
	case PTYPE_BALLISTIC:
		roeMode = roeStatus.airMode;
		break;

	case PTYPE_SURFACE:
	case PTYPE_SMALLSURFACE:
	case PTYPE_LARGESURFACE:
	case PTYPE_CARRIER:
		roeMode = roeStatus.surfMode;
		break;

	case PTYPE_SUBSURFACE:
	case PTYPE_SUBMARINE:
	case PTYPE_TORPEDO:
	case PTYPE_SONOBUOY:
	case PTYPE_WATERCM:
    case PTYPE_WATERMINE:
		roeMode = roeStatus.subMode;
		break;

	case PTYPE_GROUND:
	case PTYPE_AIRFIELD:
	case PTYPE_GROUNDVEHICLE:
		roeMode = roeStatus.landMode;
		break;

	case PTYPE_UNKNOWN:
		return false;
		break;
	}


	switch (roeMode)
	{
	case WEAPONS_FREE:
		return !isNeutralOrFriendly || isWeapon;
	case WEAPONS_TIGHT:
		return isWeapon || isHostile;
	case WEAPONS_HOLD:
		return isWeapon;
	default:
		return false;
	}

}

bool tcGoalTracker::IsTargetLegal(tcGameObject* attacker, long targetTrackId) const
{
    wxASSERT(attacker != 0);

    unsigned int attackerAlliance = attacker->GetAlliance();

    tcSensorMapTrack targetTrack;
    if (tcSimState::Get()->GetTrack(targetTrackId, attackerAlliance, targetTrack))
    {
		return IsTargetLegal(attacker, &targetTrack);
    }
    else
    {
        return false; // target not found in sensor map
    }

}

bool tcGoalTracker::IsTargetLegal(tcGameObject* attacker, float lon_rad, float lat_rad) const
{
    wxASSERT(attacker != 0);

    unsigned int attackerAlliance = attacker->GetAlliance();
   

    const float searchRange_km = 10.0f;
    GeoPoint p1(lon_rad, lat_rad, 0);
    GeoPoint p2 = p1;

    p1.Offset(searchRange_km, C_PIOVER180 * 225.0f);
    p2.Offset(searchRange_km, C_PIOVER180 * 45.0f);

    
    tcGeoRect region;
    region.Set(p1.mfLon_rad, p2.mfLon_rad, p1.mfLat_rad, p2.mfLat_rad);

    tcSensorTrackIterator iter(attackerAlliance, 0xFFFF, region);

    for (iter.First();iter.NotDone();iter.Next())
    {
        tcSensorMapTrack* targetTrack = iter.Get();

		bool isLegal = IsTargetLegal(attacker, targetTrack);

        if (isLegal)
        {
            return true; // legal target found
        }
    }

    return false; // no legal targets found
}


/**
* Version that writes damageLog to csv file
*/
void tcGoalTracker::LogAllDamageReports(const std::string& fileName)
{
    tcFile logFile;

    logFile.Open(fileName.c_str(),  tcFile::modeWrite | tcFile::modeText);

    wxString line;
    line.Printf("Unit Name, Unit Class, Alliance, Classification, Time, Damage, WasLanded, DClass1, DQty1, DClass2, DQty2, DClass3, DQty3\n");
    logFile.WriteString(line.c_str());

    std::map<std::string, DamageReport>::iterator iter =
        damageLog.begin();

    for (; iter!=damageLog.end(); ++iter)
    {
        const std::string& unitName = iter->first;
        DamageReport& logData = iter->second;

        bool includeInReport = false;
        switch (logData.classification)
        {
        case PTYPE_SMALLSURFACE:
        case PTYPE_LARGESURFACE:
        case PTYPE_CARRIER:
        case PTYPE_FIXEDWING:
        case PTYPE_HELO:
        case PTYPE_SUBMARINE:
        case PTYPE_GROUND:
        case PTYPE_AIRFIELD:
            includeInReport = true;
            break;
        default:
            includeInReport = false;
        }

        if (includeInReport)
        {
            wxString line;
            line.Printf("%s, %s, %d, %d, %f, %f, %d",
                unitName.c_str(), logData.databaseClass.c_str(), logData.alliance, logData.classification, logData.time, logData.damageFraction, logData.landed);

            for (size_t k=0; k<logData.damagerClass.size(); k++)
            {
                wxString str = wxString::Format(",%s,%d", logData.damagerClass[k].c_str(), logData.damagerQuantity[k]);
                line += str;
            }
            for (size_t k=logData.damagerClass.size(); k<3; k++)
            {
                wxString str = ",,";
                line += str;
            }

            line += "\n";

            logFile.WriteString(line.c_str());
        }
    }


    logFile.Close();
}


/**
* Writes goal status out to file <fileName>. This should
* be called at least once at the end of the game.
*/
void tcGoalTracker::LogAllianceGoalStatus(std::string fileName, int alliance)
{
	std::stringstream statusStream;

	WriteStatus(statusStream, alliance);


	std::ofstream logFile;
	
	logFile.open(fileName.c_str());
		
	logFile << statusStream.str();

	logFile.close();
}



tcGoal* tcGoalTracker::GetAllianceGoal(int alliance)
{
    std::map<int, tcGoal*>::const_iterator iter = allianceGoals.find(alliance);

    if (iter != allianceGoals.end())
    {
        return iter->second;
    }
    else
    {
        fprintf(stderr, "tcGoalTracker::GetAllianceGoal - Alliance not found (%d)\n", alliance);
        return 0;
    }
}

/**
* Updates name for destroy and protect targets
*/
void tcGoalTracker::RenameTarget(const std::string& oldName, const std::string& newName)
{
    for(int i=0;i<MAX_ALLIANCES;i++)
    {
        tcGoal* allianceGoal = allianceGoals[i];
        if (allianceGoal)
		{
			allianceGoal->RenameTarget(oldName, newName);
		}
    }
}

void tcGoalTracker::ReportNoGoals(unsigned alliance)
{
    if (reportedNoGoals) return;


    tcAllianceInfo* allianceInfo = tcAllianceInfo::Get();
    if (allianceInfo->IsAllianceNeutral((unsigned char)alliance))
    {
        return; // okay if neutral alliance has no goals
    }

    reportedNoGoals = true;
    wxString s;
    s.Printf("Alliance (%s) has no goals", allianceInfo->GetAllianceDefaultCountry(alliance).c_str());
#ifdef _DEBUG
    wxMessageBox(s);
#else
    fprintf(stderr, "%s\n", s.c_str());
#endif
}

void tcGoalTracker::SetAllianceGoal(int alliance, tcGoal* goal)
{
    if ((alliance < 0)||(alliance >= MAX_ALLIANCES))
    {
        fprintf(stderr, "Alliance out of range in tcGoalTracker::AddGoal (%d)\n", alliance);
        return;
    }
    if (allianceGoals[alliance] != NULL) delete allianceGoals[alliance];

    if (goal != 0)
    {
        allianceGoals[alliance] = goal;
        goal->SetAlliance(unsigned int(alliance));
        SetAllianceROE(alliance, WEAPONS_FREE, WEAPONS_FREE, WEAPONS_FREE, WEAPONS_FREE); // default ROE
    }
}

void tcGoalTracker::AddChildGoalToId(unsigned long id, tcGoal* goal)
{
    tcGoal* parentGoal = LookupGoalById(id);
    tcCompoundGoal* compound = dynamic_cast<tcCompoundGoal*>(parentGoal);
    if (compound != 0)
    {
        compound->AddGoalByPtr(goal);
    }
}

void tcGoalTracker::DeleteGoalById(unsigned long id)
{
    std::map<int, tcGoal*>::iterator iter = allianceGoals.begin();
    for (;iter != allianceGoals.end(); ++iter)
    {
        // first check if top level goal is to be deleted
        if ((iter->second != 0) && (iter->second->GetId() == id))
        {
            delete iter->second;
            allianceGoals.erase(iter);
            return;
        }

        // next search for child of top level to be deleted if it's a compound goal
        if (tcCompoundGoal* compound = dynamic_cast<tcCompoundGoal*>(iter->second))
        {
            if (tcCompoundGoal* parent = FindParentGoalForId(id, compound))
            {
                std::vector<tcGoal*> temp;
                for (size_t n=0; n<parent->children.size(); n++)
                {
                    if (parent->children[n]->GetId() != id)
                    {
                        temp.push_back(parent->children[n]);
                    }
                    else
                    {
                        delete parent->children[n];
                    }
                }
                parent->children = temp;
                return;
            }

        }

    }
}

tcGoal* tcGoalTracker::LookupGoalById(unsigned long id)
{
    std::map<int, tcGoal*>::iterator iter = allianceGoals.begin();
    for (;iter != allianceGoals.end(); ++iter)
    {
        tcGoal* result = SearchGoalForId(id, iter->second);
        if (result != 0) return result;
    }

    return 0;
}

tcGoal* tcGoalTracker::SearchGoalForId(unsigned long id, tcGoal* goal)
{
    if (goal == 0) return 0;

    if (goal->GetId() == id) return goal;

    if (tcCompoundGoal* compound = dynamic_cast<tcCompoundGoal*>(goal))
    {
        for (size_t n=0; n<compound->children.size(); n++)
        {
            tcGoal* result = SearchGoalForId(id, compound->children[n]);
            if (result != 0) return result;
        }
    }

    return 0;
}

tcCompoundGoal* tcGoalTracker::FindParentGoalForId(unsigned long id, tcCompoundGoal* compound)
{
    if (compound == 0) 
    {
        wxASSERT(false);
        return 0;
    }

    if (compound->GetId() == id)
    {
        wxASSERT(false); // this shouldn't happen
        return 0;
    }


    for (size_t n=0; n<compound->children.size(); n++)
    {
        tcGoal* child = compound->children[n];
        
        if (child->GetId() == id)
        {
            return compound;
        }
        else if (tcCompoundGoal* compoundChild = dynamic_cast<tcCompoundGoal*>(child))
        {
            return FindParentGoalForId(id, compoundChild);
        }
    }

    return 0;
}

void tcGoalTracker::Update(double currentTime)
{
    bool isEditMode = tcGameObject::IsEditMode();
    if ((currentTime - lastUpdateTime < updateInterval) && (!isEditMode)) return;

    if (!isEditMode) lastUpdateTime = currentTime;

	if (tcSimState::Get()->IsMultiplayerClient()) return;

    for(int i=0;i<MAX_ALLIANCES;i++)
    {
        tcGoal* allianceGoal = allianceGoals[i];
        if (allianceGoal)
		{
			//previousGoalStatus[i] = allianceGoal->goalState;
			allianceGoal->Update();
		}
    }
}


bool tcGoalTracker::ReadAAR(AARSummary& summary, const std::string& fileName) const
{
    summary.alliances.clear();
    summary.allianceNames.clear();
    summary.damageSummary.clear();
    summary.equipmentSummary.clear();
    summary.playerGoalStatus.clear();

    wxXmlDocument doc(fileName);
    if (!doc.IsOk()) return false;

    wxXmlNode* root = doc.GetRoot();
    if (root == 0) return false;

    wxXmlNode* child = root->GetChildren();

    while (child != 0)
    {
        if (child->GetName() == "scenario")
        {
            summary.scenarioName = child->GetPropVal("name", "");
            
            unsigned long val = 0;
            child->GetPropVal("player_alliance", "0").ToULong(&val);
            summary.playerAlliance = (unsigned int)val;

            summary.completedTime = child->GetPropVal("stopped_on", "UNK");
        }
        else if (child->GetName() == "alliance")
        {
            unsigned long allianceId = 0;
            child->GetPropVal("id", "999").ToULong(&allianceId);
            summary.alliances.push_back(unsigned int(allianceId));

            summary.allianceNames.push_back(child->GetPropVal("name", "UNK"));

            std::vector<DamageReport2> damage;
            std::vector<EquipmentReport2> equipment;
            wxArrayString goalStatus;
            ReadAARAllianceNode(unsigned int(allianceId), child, damage, equipment, goalStatus);

            summary.damageSummary.push_back(damage);
            summary.equipmentSummary.push_back(equipment);

            if (summary.playerAlliance == unsigned int(allianceId))
            {
                summary.playerGoalStatus = goalStatus;
            }
        }


        child = child->GetNext();
    }

    return true;
}

bool tcGoalTracker::ReadAARAllianceNode(unsigned int alliance, wxXmlNode* node, std::vector<DamageReport2>& damage, std::vector<EquipmentReport2>& equipment, wxArrayString& goalStatus) const
{
    wxXmlNode* child = node->GetChildren();

    while (child != 0)
    {
        if (child->GetName() == "damage_report")
        {
            wxXmlNode* child2 = child->GetChildren();
            while (child2 != 0)
            {
                if (child2->GetName() == "damage")
                {
                    DamageReport2 dr;
         
                    dr.unitName = child2->GetPropVal("unit", "");
                    dr.databaseClass = child2->GetPropVal("db", "");
                    dr.damagerString = child2->GetPropVal("damager", "");

                    unsigned long classId = 0;
                    child2->GetPropVal("class", "0").ToULong(&classId);
                    dr.classification = unsigned int(classId);

                    double damageFraction = 0;
                    child2->GetPropVal("damage", "0").ToDouble(&damageFraction);
                    dr.damageFraction = float(damageFraction);

                    child2->GetPropVal("time", "0").ToDouble(&dr.time);

                    unsigned long landed = 0;
                    child2->GetPropVal("landed", "0").ToULong(&landed);
                    dr.landed = (landed != 0);

                    damage.push_back(dr);
                }

                child2 = child2->GetNext();
            }
        }
        else if (child->GetName() == "equipment_report")
        {
            wxXmlNode* child2 = child->GetChildren();
            while (child2 != 0)
            {
                if (child2->GetName() == "equipment")
                {
                    EquipmentReport2 er;

                    er.databaseClass = child2->GetPropVal("db", "");

                    unsigned long qty = 0;
                    child2->GetPropVal("quantity", "0").ToULong(&qty);
                    er.quantity = unsigned int(qty);

                    equipment.push_back(er);
                }

                child2 = child2->GetNext();
            }
        }
        else if (child->GetName() == "goal_summary")
        {
            wxXmlNode* child2 = child->GetChildren();
            while (child2 != 0)
            {
                if (child2->GetName() == "line")
                {
                    wxXmlNode* child3 = child2->GetChildren();
                    wxString lineText = (child3 != 0) ? child3->GetContent() : "";
                    goalStatus.push_back(lineText);
                }

                child2 = child2->GetNext();
            }
        }

        child = child->GetNext();
    }

    return true;
}

bool tcGoalTracker::ReadAARInfo(AARInfo& info, const std::string& fileName) const
{
    wxXmlDocument doc(fileName);
    if (!doc.IsOk()) return false;

    wxXmlNode* root = doc.GetRoot();
    if (root == 0) return false;

    wxXmlNode* child = root->GetChildren();

    while (child != 0)
    {
        if (child->GetName() == "scenario")
        {
            info.scenarioName = child->GetPropVal("name", "");
            
            unsigned long val = 0;
            child->GetPropVal("player_alliance", "0").ToULong(&val);
            info.playerAlliance = (unsigned int)val;

            info.completedTime = child->GetPropVal("stopped_on", "UNK");
            return true;
        }

        child = child->GetNext();
    }

    return false;
}


void tcGoalTracker::SetAllianceROE(int alliance, ROEMode air, ROEMode surf, ROEMode sub, ROEMode land)
{
    if ((alliance < 0)||(alliance >= MAX_ALLIANCES))
    {
        fprintf(stderr, "Alliance out of range in tcGoalTracker::SetAllianceROE (%d)\n", alliance);
        return;
    }

    wxASSERT((air != ROE_ERROR) && (surf != ROE_ERROR) && (sub != ROE_ERROR) && (land != ROE_ERROR));

    ROEStatus newStatus;
	newStatus.airMode = air;
	newStatus.surfMode = surf;
	newStatus.subMode = sub;
	newStatus.landMode = land;

    newStatus.roeViolations = 0;

    allianceROE[alliance] = newStatus;
}

void tcGoalTracker::SetAllianceROE(int alliance, ROEStatus roeStatus)
{
    if ((alliance < 0)||(alliance >= MAX_ALLIANCES))
    {
        fprintf(stderr, "Alliance out of range in tcGoalTracker::SetAllianceROE (%d)\n", alliance);
        return;
    }

    allianceROE[alliance] = roeStatus;
}


/**
* Writes damageLog and other AAR info to xml file
*/
void tcGoalTracker::WriteAAR(const std::string& fileName)
{
    wxXmlDocument doc;

    wxXmlNode* root = new wxXmlNode(wxXML_ELEMENT_NODE, "AAR");
   
    doc.SetRoot(root);

    std::vector<unsigned char> allianceList = tcAllianceInfo::Get()->GetAllianceList();

    for (unsigned char n=0; n<allianceList.size(); n++)
    {
        wxXmlNode* alliance_n = new wxXmlNode(root, wxXML_ELEMENT_NODE, "alliance");
        alliance_n->AddProperty("id", wxString::Format("%d", allianceList[n]));
        alliance_n->AddProperty("name", wxString(tcAllianceInfo::Get()->GetAllianceName(allianceList[n]).c_str()));

        // write goal summary
        wxXmlNode* goalSummaryNode = new wxXmlNode(alliance_n, wxXML_ELEMENT_NODE, "goal_summary");
        wxArrayString goalSummary;
        GetAllianceGoalStatusDescription(allianceList[n], goalSummary);
        for (size_t line_idx=0; line_idx<goalSummary.size(); line_idx++)
        {
            wxXmlNode* lineNode = new wxXmlNode(goalSummaryNode, wxXML_ELEMENT_NODE, "line");
            wxXmlNode* textNode = new wxXmlNode(lineNode, wxXML_TEXT_NODE, "");
            textNode->SetContent(goalSummary[goalSummary.size()-line_idx-1]); // to get order correct
        }

        // write damage report
        wxXmlNode* damage_report = new wxXmlNode(alliance_n, wxXML_ELEMENT_NODE, "damage_report");

        std::vector<DamageReport> damageSummary;
        GetDamageReportSummary(allianceList[n], damageSummary);

        for (size_t k=0; k<damageSummary.size(); k++)
        {
            wxXmlNode* nodek = new wxXmlNode(damage_report, wxXML_ELEMENT_NODE, "damage");

            nodek->AddProperty("unit", wxString(damageSummary[k].unitName.c_str()));
            nodek->AddProperty("db", wxString(damageSummary[k].databaseClass.c_str()));
            nodek->AddProperty("class", wxString::Format("%d", damageSummary[k].classification));
            nodek->AddProperty("damage", wxString::Format("%f", damageSummary[k].damageFraction));
            nodek->AddProperty("time", wxString::Format("%f", damageSummary[k].time));
            nodek->AddProperty("landed", wxString::Format("%d", damageSummary[k].landed));
            wxString damagerInfo;
            for (size_t idx=0; idx<damageSummary[k].damagerClass.size(); idx++)
            {
                damagerInfo += wxString::Format("%s (%d) ", 
                    damageSummary[k].damagerClass[idx].c_str(), damageSummary[k].damagerQuantity[idx]);
            }
            nodek->AddProperty("damager", damagerInfo);
        }

        // write expended equipment report
        wxXmlNode* equipment_report = new wxXmlNode(alliance_n, wxXML_ELEMENT_NODE, "equipment_report");
        std::vector<EquipmentReport> equipmentSummary;
        GetExpendedEquipmentSummary(allianceList[n], equipmentSummary);
        
        for (size_t k=0; k<equipmentSummary.size(); k++)
        {
            wxXmlNode* nodek = new wxXmlNode(equipment_report, wxXML_ELEMENT_NODE, "equipment");

            nodek->AddProperty("db", equipmentSummary[k].databaseClass);
            nodek->AddProperty("quantity", wxString::Format("%d", equipmentSummary[k].quantity));
        }

    }


    // add general scenario information
    tcSimState* simState = tcSimState::Get();
    tcUserInfo* userInfo = tcUserInfo::Get();

    wxXmlNode* scenario = new wxXmlNode(root, wxXML_ELEMENT_NODE, "scenario");
    scenario->AddProperty("name", wxString(simState->GetScenarioName()));
    scenario->AddProperty("player_alliance", wxString::Format("%d", userInfo->GetOwnAlliance()));

    wxDateTime now = wxDateTime::Now();
    wxString nowString = now.Format("%Y-%m-%d %H:%M");
    scenario->AddProperty("stopped_on", nowString);


    doc.Save(fileName, 1);
}


void tcGoalTracker::WriteStatus(std::stringstream& stream, int alliance)
{
    tcAllianceInfo* allianceInfo = tcAllianceInfo::Get();
    bool allianceNeutral = allianceInfo->IsAllianceNeutral(alliance);

	if (tcGoal* allianceGoal = allianceGoals[alliance])
	{
        const char* offsetString = tcDatabaseObject::CostToString(GetAllianceOffset(alliance));

        float score = GetAllianceScore(alliance) * (100.0 / perfectScore);
        if (score > 100.0f) score = 100.0f;
        else if (score < -100.0f) score = -100.0f;
        wxString scoreString;
        scoreString.Printf("SCORE: %.0f\nRELATIVE DAMAGE: %s\n\n", score, offsetString);
        stream << scoreString.c_str();

        stream << "GOAL SUMMARY:\n\n";
        allianceGoal->WriteStatusB(stream);

        stream << "\n\n\nGOAL SUMMARY DETAILS:\n";
		allianceGoal->WriteStatus(stream);
        stream << "\n\n";
	}
	else if (!allianceNeutral)
	{
		fprintf(stderr, "tcGoalTracker::WriteStatus - null alliance goal\n");
	}
}

void tcGoalTracker::WriteStatus(wxArrayString& arrayString, int alliance)
{
    tcAllianceInfo* allianceInfo = tcAllianceInfo::Get();
    bool allianceNeutral = allianceInfo->IsAllianceNeutral(alliance);

	if (tcGoal* allianceGoal = allianceGoals[alliance])
	{
        if (HasAllianceSucceeded(alliance))
        {
            arrayString.push_back("VICTORY");
        }
        else if (HasAllianceFailed(alliance))
        {
            arrayString.push_back("DEFEAT");
        }
        else
        {
            arrayString.push_back("SCENARIO UNRESOLVED");
        }
        arrayString.push_back("");

        float score = GetAllianceScore(alliance) * (100.0 / perfectScore);
        if (score > 100.0f) score = 100.0f;
        else if (score < -100.0f) score = -100.0f;
        wxString scoreString;

        scoreString.Printf("SCORE: %.0f", score);


        arrayString.push_back(scoreString);
        arrayString.push_back("");

        arrayString.push_back("GOAL STATUS:");
        
        allianceGoal->WriteStatusB(arrayString);

        arrayString.push_back("");

        arrayString.push_back("GOAL DETAILS:");

		allianceGoal->WriteStatus(arrayString);
	}
	else if (!allianceNeutral)
	{
		fprintf(stderr, "tcGoalTracker::WriteStatus - null alliance goal\n");
	}
}



tcGoalTracker::tcGoalTracker()
: updateInterval(9.01),
   allianceFailed(false),
   allianceSucceeded(false),
   statusChanged(false),
   perfectScore(1e9),
   reportedNoGoals(false),
   lastUpdateTime(-10.0f)
{
    
    for(int i=0;i<MAX_ALLIANCES;i++)
    {
        allianceGoals[i] = NULL; 
    }
    Clear();

    wxASSERT(MAX_ALLIANCES == tcAllianceInfo::MAX_ALLIANCES); // these should match
}

tcGoalTracker::~tcGoalTracker()
{
	// should use map iterator here
	for(int i=0;i<MAX_ALLIANCES;i++)
	{
		if (allianceGoals[i])
		{
			delete allianceGoals[i];
		}
	}

}