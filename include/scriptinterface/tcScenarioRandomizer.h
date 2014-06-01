/**  
**  @file tcScenarioRandomizer.h
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

#ifndef _SCENARIORANDOMIZER_H_
#define _SCENARIORANDOMIZER_H_

#ifdef WIN32
#pragma once
#endif

#include <map>
#include <string>
#include <vector>
#include "tcRect.h"

/**
*
*/
namespace scriptinterface 
{
    class tcScenarioLogger;

    /**
    * Singleton class that holds scenario randomization data
    */
    class tcScenarioRandomizer 
    {
    public:
        struct RandInfo
        {
            enum
            {
                NONE = 0,
                BOX = 1
            };
            int randomLocationMode;
            float includeProbability; ///< 0-1 probability of creating unit
            std::vector<tcRect> randomBox; ///< vect of boxes to randomly place unit
        };
       
        static tcScenarioRandomizer* Get();

        float GetIncludeProbability(const std::string& unit) const;
        void SetIncludeProbability(const std::string& unit, float prob);

        std::vector<tcRect> GetRandomBoxes(const std::string& unit) const;
        void AddRandomBox(const std::string& unit, const tcRect& box);
        void UpdateRandomBox(const std::string& unit, const tcRect& boxPrev, const tcRect& boxNew);
        void DeleteRandomBox(const std::string& unit, const tcRect& box);
        void DeleteAllRandomBoxes(const std::string& unit);
        bool RandomBoxExists(const std::string& unit, const tcRect& box) const;

        void RenameUnit(const std::string& nameOld, const std::string& nameNew);
        void DeleteUnit(const std::string& unit);

        void Clear();
        
        void SaveToPython(scriptinterface::tcScenarioLogger& logger);

    private:
		tcScenarioRandomizer();
		~tcScenarioRandomizer();

        std::map<std::string, RandInfo> randomInfo;

    };

}

#endif

