/**  
**  @file  tcScenarioLogger.cpp
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

#include "tcScenarioLogger.h"
#include "tcSimPythonInterface.h"
#include "tcMessageInterface.h"
#include "tcDateTime.h"
#include "tcSimState.h"
#include "tcGameObjIterator.h"
#include "tcGoalTracker.h"
#include "tcSimPythonInterface.h"
#include "tcAllianceInfo.h"
#include "tcMapOverlay.h"
#include "tcMapObject.h"
#include "tcScenarioRandomizer.h"
#include "tcSonarEnvironment.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif 

namespace scriptinterface 
{
	void tcScenarioLogger::AddScenarioText(const char* s)
	{
        for (unsigned int n=0; n<indentLevel; n++)
        {
		    scenarioText << "    ";
        }
		scenarioText << s;
		scenarioText << "\n";
	}

	void tcScenarioLogger::AddScenarioText(const std::string& s)
	{
        AddScenarioText(s.c_str());
	}

	void tcScenarioLogger::AddScenarioText(const wxString& s)
	{
		AddScenarioText(s.ToStdString().c_str());
	}

    void tcScenarioLogger::BuildScenarioFile()
    {
        wxString s;

        std::vector<unsigned> alliances;

        // add CreateAlliance commands for alliances that exist in sensor map
        for (unsigned alliance = 1; alliance <= 15; alliance++)
        {
            if (simState->mcSensorMap.MapExists(alliance))
            {
                alliances.push_back(alliance);

                s.Printf("SM.CreateAlliance(%d, '%s')", alliance, allianceInfo->GetAllianceName(alliance).c_str());
                AddScenarioText(s);

                s.Printf("SM.SetAllianceDefaultCountry(%d, '%s')", alliance, allianceInfo->GetAllianceDefaultCountry(alliance).c_str());
                AddScenarioText(s);

                s.Printf("SM.SetAlliancePlayable(%d, %d)", alliance, allianceInfo->IsAlliancePlayable(alliance));
                AddScenarioText(s);
            }
        }

        // add alliance relationships
        for (size_t m=0; m<alliances.size(); m++)
        {
            unsigned char alliance_m = alliances[m];
            for (size_t n=0; n<alliances.size(); n++)
            {
                unsigned char alliance_n = alliances[n];
                if (alliance_n > alliance_m)
                {
                    tcAllianceInfo::Affiliation affil = allianceInfo->GetAffiliation(alliance_m, alliance_n);
                    switch (affil)
                    {
                    case tcAllianceInfo::NEUTRAL:
                        s.Printf("SM.SetAllianceRelationship(%d, %d, 'Neutral')", alliance_m, alliance_n);
                        AddScenarioText(s);
                        break;
                    case tcAllianceInfo::FRIENDLY:
                        s.Printf("SM.SetAllianceRelationship(%d, %d, 'Friendly')", alliance_m, alliance_n);
                        AddScenarioText(s);
                        break;
                    default: // default is hostile
                        break;
                    }
                }
            }
        }

        s.Printf("SM.SetUserAlliance(%d)\n", userInfo->GetOwnAlliance());
        AddScenarioText(s);

        // time and date, offset previous scenario with sim time
        tcDateTime& dateTime = simState->dateTime;
        s.Printf("SM.SetDateTime(%d,%d,%d,%d,%d,%d)", dateTime.GetYear(), dateTime.GetMonth(),
            dateTime.GetDay(), dateTime.GetHour(), dateTime.GetMinute(), dateTime.GetSecond());
        AddScenarioText(s);

        tcGeoRect theater;
        simState->mpMapData->GetTheaterArea(theater);
        float lon_deg = C_180OVERPI * theater.XCenter();
        float lat_deg = C_180OVERPI * theater.YCenter();
        s.Printf("SM.SetStartTheater(%f, %f) # (lon, lat) in degrees, negative is West or South",
            lon_deg, lat_deg);
        AddScenarioText(s);
        AddScenarioText("SM.SetScenarioLoaded(1)\n");

        // sonar environment
        s.Printf("SM.SetSeaState(%d)\n", tcSonarEnvironment::Get()->GetSeaState());
        AddScenarioText(s);

        s.Printf("SM.SetSVP('%s')\n", tcSonarEnvironment::Get()->GetSVPString().ToAscii());
        AddScenarioText(s);

        SaveAllianceBriefings(alliances);
    
        SaveEntities(alliances);
        
        SaveGoals(alliances);

        SaveMapGraphics();

        SaveRandomizationInfo();

		wxString msg = wxString::Format("Saved %s", scenarioName.c_str());
		tcMessageInterface::Get()->ConsoleMessage(msg.ToStdString());
        
    }

	void tcScenarioLogger::CreateHeaderText()
	{
		wxString dateTimeStamp = wxDateTime::Now().Format();

		headerText.clear();
		headerText << std::string("# Created on ") + std::string(dateTimeStamp.c_str()) + "\n";
		headerText << "from math import *\n";
		headerText << "from random import *\n";
		headerText << "from UnitCommands import *\n\n";
	}

    void tcScenarioLogger::EscapeBackslashes(wxString& s)
    {
        wxString escaped;
        for (size_t n=0; n<s.size(); n++)
        {
            if (s[n] == '\n')
            {
                escaped += "\\n";
            }
            else
            {
                escaped.Append(s[n]);
            }
        }

        //escaped.Replace("'", ""); // get rid of single quotes

        s = escaped;
    }

	void tcScenarioLogger::InitScenarioText()
	{
        wxString s;

		scenarioText.clear();
        scenarioText << "def CreateScenario(SM):\n\n";

        wxString scenarioDescription(simState->GetScenarioDescription());
        EscapeBackslashes(scenarioDescription);

        s.Printf("    SM.SetScenarioDescription(\"\"\"%s\"\"\")\n", scenarioDescription.ToAscii());
        scenarioText << s;

        s.Printf("    SM.SetScenarioName(\"\"\"%s\"\"\")\n", simState->GetScenarioName());
        scenarioText << s;

        SetIndentLevel(1);
    }

    /**
    * 
    */
    void tcScenarioLogger::SaveAllianceBriefings(const std::vector<unsigned>& alliances)
    {
        wxString s;

        for (size_t k=0; k<alliances.size(); k++)
        {
            unsigned alliance_k = alliances[k];
            wxString briefing(scenarioInterface->GetSimpleBriefing(alliance_k).c_str());
            EscapeBackslashes(briefing);

            s.Printf("    ####################\n");
            scenarioText << s;
            s.Printf("    SM.SetSimpleBriefing(%d, \"\"\"%s\"\"\")\n\n", alliance_k, briefing.ToAscii());
            scenarioText << s;
        }
    }


    /**
    * Save all entities to file, grouped by alliance
    */
    void tcScenarioLogger::SaveEntities(const std::vector<unsigned>& alliances)
    {
        tcScenarioRandomizer* randomizer = tcScenarioRandomizer::Get();
        wxString s;

        for (size_t k=0; k<alliances.size(); k++)
        {
            tcGameObjIterator iter;
            iter.SetAllianceFilter(alliances[k]);

            AddScenarioText("##############################");
            s.Printf("### Alliance %d units", alliances[k]);
            AddScenarioText(s);
            AddScenarioText("##############################\n");

            // save the platforms that aren't followers in formation (or not platform objs)
            for (iter.First();iter.NotDone();iter.Next())
            {
                tcGameObject *obj = iter.Get();
                tcPlatformObject* platform = dynamic_cast<tcPlatformObject*>(obj);

                if ((platform==0) || (!platform->formation.IsFollower()))
                {
                    float includeProbability = randomizer->GetIncludeProbability(obj->mzUnit.c_str());
                    includeProbability = std::max(includeProbability, 0.0f);

                    if (includeProbability < 1.0f)
                    {
                        s.Printf("if (SM.IncludeUnit(%f)):", includeProbability);
                        AddScenarioText(s);
                        SetIndentLevel(2);
                    }

                    obj->SaveToPython(*this);

                    SetIndentLevel(1);
                    AddScenarioText("");
                }
            }

            // save platforms that are followers, use same distance offset from leader, don't add if
            // leader doesnt exist
            for (iter.First();iter.NotDone();iter.Next())
            {
                tcGameObject *obj = iter.Get();
                tcPlatformObject* platform = dynamic_cast<tcPlatformObject*>(obj);

                if ((platform != 0) && (platform->formation.IsFollower()))
                {
                    float includeProbability = randomizer->GetIncludeProbability(obj->mzUnit.c_str());
                    includeProbability = std::max(includeProbability, 0.0f);

                    if (includeProbability < 1.0f)
                    {
                        s.Printf("if (SM.IncludeUnit(%f)):", includeProbability);
                        AddScenarioText(s);
                        SetIndentLevel(2);
                    }

                    obj->SaveToPython(*this);

                    SetIndentLevel(1);
                    AddScenarioText("");
                }
            }

        }
    }

    void tcScenarioLogger::SaveGoals(const std::vector<unsigned>& alliances)
    {
        wxString s;

        for (size_t k=0; k<alliances.size(); k++)
        {
            unsigned alliance = alliances[k];

            AddScenarioText("##############################");
            s.Printf("### Alliance %d goals", alliance);
            AddScenarioText(s);
            AddScenarioText("##############################\n");

            tcGoal* allianceGoal = simState->goalTracker->GetAllianceGoal((int)alliance);
            if (allianceGoal)
            {
                allianceGoal->SaveToPython(*this);

                s.Printf("SM.SetAllianceGoal(%d, goal_temp)\n", alliance);
                AddScenarioText(s);

				tcGoalTracker::ROEStatus roeStatus = simState->goalTracker->GetAllianceROE((int)alliance);
                s.Printf("SM.SetAllianceROEByType(%d, %d, %d, %d, %d)\n", alliance,
					roeStatus.airMode, roeStatus.surfMode, roeStatus.subMode, roeStatus.landMode);
                AddScenarioText(s);
            }
        }
    }

    /**
    * Saves map graphics from map overlay
    */
    void tcScenarioLogger::SaveMapGraphics()
    {
        AddScenarioText("##############################");
        AddScenarioText("### Overlay Graphics");
        AddScenarioText("##############################");

        for (size_t n=0; n < mapOverlay->overlayObjects.size(); n++)
        {
            if (tcMapTextObject* obj = dynamic_cast<tcMapTextObject*>(mapOverlay->overlayObjects[n]))
            {
                float lon_deg = C_180OVERPI * obj->_x;
                float lat_deg = C_180OVERPI * obj->_y;
                wxString color = obj->GetColorString();
                wxString s = wxString::Format("SM.OverlayText('%s', %.4f, %.4f, '%s')",
                    obj->caption.c_str(), lon_deg, lat_deg, color.c_str());
                AddScenarioText(s);
            }
        }

    }

    void tcScenarioLogger::SaveRandomizationInfo()
    {
        AddScenarioText("##############################");
        AddScenarioText("### Randomization Info");
        AddScenarioText("##############################");

        tcScenarioRandomizer::Get()->SaveToPython(*this);
    }


    void tcScenarioLogger::SetIndentLevel(unsigned int n)
    {
        indentLevel = n;
    }

	void tcScenarioLogger::WriteAll()
	{
		scenario.WriteString(headerText.str().c_str());

		scenario.WriteString(scenarioText.str().c_str());

		scenario.Close();

		/* if we are overwriting an existing scenario (based on existence of
		** .pyc file) python will use old scenario file until game is restarted.
		** Need feature here to re-import scenario */
		wxString compiledFileName = wxString(scenarioName.c_str()) + ".pyc";
		if (wxFileExists(compiledFileName))
		{
			/*wxString s;
			s.Printf("Saved %s over old file, restart game before loading\n",
				scenarioName.c_str());
			tcMessageInterface::Get()->ConsoleMessage(s.c_str());*/

            bool result = wxRemoveFile(compiledFileName);
            wxASSERT(result);

			//wxString s;
			//s.Printf("import Saved\n", scenarioName.c_str());
			//tcSimPythonInterface::Get()->CallPython(s.c_str(), "Error re-importing saved scenario");
		}

        
	}


	tcScenarioLogger::tcScenarioLogger(const std::string& fileName)
		: scenario(fileName + ".py"),
		  scenarioName(fileName),
          scenarioInterface(0),
          simState(0),
          userInfo(0),
          allianceInfo(0),
          indentLevel(0)
	{
        scenarioInterface = tcSimPythonInterface::Get()->GetScenarioInterface();
        simState = tcSimState::Get();
        userInfo = tcUserInfo::Get();
        allianceInfo = tcAllianceInfo::Get();
        mapOverlay = scenarioInterface->GetMapOverlay();

		CreateHeaderText();
		InitScenarioText();
	}

	tcScenarioLogger::~tcScenarioLogger()
	{
	}
}


