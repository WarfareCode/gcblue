/** 
**  @file tcGoalTracker.h
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
#ifdef WIN32
#pragma once
#endif

#ifndef _GOALTRACKER_H_
#define _GOALTRACKER_H_

#include <map>
#include <sstream>
#include <vector>

class tcStream;
class tcCommandStream;
class tcCreateStream;
class tcUpdateStream;
class tcGameStream;
class tcGoal;
class tcCompoundGoal;
class wxXmlNode;
class tcGameObject;
class tcSensorMapTrack;

class tcGoalTracker
{
public:
    enum
    {
        MAX_ALLIANCES = 16   ///< goaltracker supports alliances from 0 to MAX_ALLIANCES-1
    };
    struct DamageReport
    {
        std::string unitName; ///< unit name (for report, same as primary key in damageLog)
        unsigned int alliance; ///< alliance of damaged unit
        std::string databaseClass; ///< db class of damaged unit
        unsigned int classification; ///< classification of damaged unit (tcDatabaseObject::mnType)
        double time; ///< time of last update
        std::vector<std::string> damagerClass;
        std::vector<unsigned int> damagerQuantity;
        float damageFraction;
        bool landed; ///< true for aircraft that receive damage while landed on base or carrier
    };
    struct DamageReport2
    {
        wxString unitName;
        wxString databaseClass;
        wxString damagerString;
        unsigned int classification;
        double time;
        float damageFraction;
        bool landed;
    };
    struct EquipmentReport
    {
        std::string databaseClass;
        unsigned int quantity;
    };
    struct EquipmentReport2
    {
        wxString databaseClass;
        unsigned int quantity;
    };
    struct AARInfo
    {
        wxString scenarioName;
        wxString completedTime;
        unsigned int playerAlliance;
    };
    struct AARSummary
    {
        wxString scenarioName;
        wxString completedTime;
        unsigned int playerAlliance;
        wxArrayString playerGoalStatus; ///< goal status text lines, player only

        std::vector<unsigned int> alliances;
        std::vector<wxString> allianceNames;
        std::vector<std::vector<DamageReport2>> damageSummary;
        std::vector<std::vector<EquipmentReport2>> equipmentSummary;
    };
    enum ROEMode
    {
        WEAPONS_HOLD = 0,
        WEAPONS_TIGHT = 1,
        WEAPONS_FREE = 2,
        ROE_ERROR = 99
    };
    struct ROEStatus
    {
        ROEMode airMode; ///< current ROE for alliance
		ROEMode surfMode;
		ROEMode subMode;
		ROEMode landMode;
        unsigned int roeViolations;
    };

    std::map<int, tcGoal*> allianceGoals; ///< map of victory goal trees, indexed by alliance
    std::map<int, float> allianceScoreOffset; ///< score offset for alliance not including goal net score
    std::map<int, ROEStatus> allianceROE; ///< ROE mode for each alliance

    void Clear();
	const std::string& GetAllianceGoalStatusDescription(int alliance);
    void GetAllianceGoalStatusDescription(int alliance, wxArrayString& arrayString);

    bool HasAllianceFailed(int alliance);
    bool HasAllianceSucceeded(int alliance);
	bool HasStatusChanged(int alliance);
	void LogAllianceGoalStatus(std::string fileName, int alliance);

	tcGoal* GetAllianceGoal(int alliance);
    void SetAllianceGoal(int alliance, tcGoal* goal);

    void AddChildGoalToId(unsigned long id, tcGoal* goal);
    void DeleteGoalById(unsigned long id);
    tcGoal* LookupGoalById(unsigned long id);
    tcGoal* SearchGoalForId(unsigned long id, tcGoal* goal);
    tcCompoundGoal* FindParentGoalForId(unsigned long id, tcCompoundGoal* compound);

    float GetAllianceOffset(int alliance);
    float GetAllianceScore(int alliance);
    void AdjustAllianceScore(int alliance, float offset);
    void SetPerfectScore(float score);
    
    ROEStatus GetAllianceROE(int alliance) const;
    void SetAllianceROE(int alliance, ROEMode air, ROEMode surf, ROEMode sub, ROEMode land);
	void SetAllianceROE(int alliance, ROEStatus roeStatus);
	bool IsTargetLegal(tcGameObject* attacker, tcSensorMapTrack* targetTrack) const;
    bool IsTargetLegal(tcGameObject* attacker, long targetTrackId) const;
    bool IsTargetLegal(tcGameObject* attacker, float lon_rad, float lat_rad) const;

    void Update(double currentTime);
	void WriteStatus(std::stringstream& stream, int alliance);
    void WriteStatus(wxArrayString& arrayString, int alliance);

    void RenameTarget(const std::string& oldName, const std::string& newName);

    void AddDamageReport(const std::string& unitName, const DamageReport& report);

    void GetDamageReportSummary(unsigned int alliance, std::vector<DamageReport>& damageSummary) const;
    void GetExpendedEquipmentSummary(unsigned int alliance, std::vector<EquipmentReport>& equipmentSummary) const;

    void LogAllDamageReports(const std::string& fileName);
    void WriteAAR(const std::string& fileName);

    bool ReadAARInfo(AARInfo& info, const std::string& fileName) const;
    bool ReadAAR(AARSummary& summary, const std::string& fileName) const;
    bool ReadAARAllianceNode(unsigned int alliance, wxXmlNode* node, std::vector<DamageReport2>& damage, std::vector<EquipmentReport2>& equipment, wxArrayString& goalStatus) const;

    tcUpdateStream& operator<<(tcUpdateStream& stream);
    tcUpdateStream& operator>>(tcUpdateStream& stream);
    tcGameStream& operator<<(tcGameStream& stream);
    tcGameStream& operator>>(tcGameStream& stream);

	static tcGoalTracker* Get();

private:
    double lastUpdateTime;
    const double updateInterval; ///< game time between updates
	std::map<int, int> previousGoalStatus; ///< status at last update
    float perfectScore; ///< score for 100 points

    std::map<std::string, DamageReport> damageLog; /// map of <unit name, damage report info> for AAR

	// variables for multiplayer client
	std::string goalStatusDescription; ///< for client alliance only
	bool allianceFailed; ///< true if client alliance has failed
	bool allianceSucceeded; ///< true if client alliance has succeeded
	bool statusChanged; ///< true if allianceFailed or allianceSucceeded has changed
    bool reportedNoGoals; ///< to suppress constant popup messages    
    
    
    tcGoalTracker();
    ~tcGoalTracker();
    void ReportNoGoals(unsigned alliance);
};






#endif