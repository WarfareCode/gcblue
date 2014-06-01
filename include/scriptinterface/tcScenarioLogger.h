/**  
**  @file tcScenarioLogger.h
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


#ifndef _TCSCENARIOLOGGER_H_
#define _TCSCENARIOLOGGER_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include <sstream>
#include <vector>
#include "tcFile.h"

class tcSimState;
class tcUserInfo;
class tcAllianceInfo;
class tcMapOverlay;

namespace scriptinterface 
{
    class tcScenarioInterface;


	/**
	* Class to assist in writing game state to python-compliant scenario file
	*/
	class tcScenarioLogger
	{
	public:		
        void AddScenarioText(const char* s); ///< add scenario text with correct indent level and trailing '\n'
		void AddScenarioText(const std::string& s);
		void AddScenarioText(const wxString& s);

        void BuildScenarioFile();
		
		void WriteAll(); ///< write all scenario info to file

		tcScenarioLogger(const std::string& fileName);
		~tcScenarioLogger();
	private:
		tcFile scenario;
		const std::string scenarioName;
		std::stringstream headerText;
		std::stringstream scenarioText;
        unsigned int indentLevel;

        tcScenarioInterface* scenarioInterface;
        tcSimState* simState;
        tcUserInfo* userInfo;
        tcAllianceInfo* allianceInfo;
        tcMapOverlay* mapOverlay;

		void CreateHeaderText();
		void InitScenarioText();		
        void EscapeBackslashes(wxString& s);
        void SaveAllianceBriefings(const std::vector<unsigned>& alliances);
        void SaveEntities(const std::vector<unsigned>& alliances);
        void SaveGoals(const std::vector<unsigned>& alliances);
        void SaveMapGraphics();
        void SaveRandomizationInfo();
        void SetIndentLevel(unsigned int n);
	};


}

#endif // _TCSCENARIOLOGGER_H_

