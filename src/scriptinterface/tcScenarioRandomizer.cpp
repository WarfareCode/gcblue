/**  
**  @file tcScenarioRandomizer.cpp
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

#include "tcScenarioRandomizer.h"
#include "tcScenarioLogger.h"
#include "math_constants.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif 

namespace scriptinterface
{
    
    tcScenarioRandomizer* tcScenarioRandomizer::Get()
    {
        static tcScenarioRandomizer instance;

        return &instance;
    }

    float tcScenarioRandomizer::GetIncludeProbability(const std::string& unit) const
    {
        std::map<std::string, RandInfo>::const_iterator iter = 
            randomInfo.find(unit);
        if (iter != randomInfo.end())
        {
            return iter->second.includeProbability;
        }
        else
        {
            return 1.0f;
        }
    }

    void tcScenarioRandomizer::AddRandomBox(const std::string& unit, const tcRect& box)
    {
        std::map<std::string, RandInfo>::iterator iter = 
            randomInfo.find(unit);
        if (iter != randomInfo.end())
        {
            iter->second.randomLocationMode = tcScenarioRandomizer::RandInfo::BOX;
            iter->second.randomBox.push_back(box);
        }
        else
        {
            RandInfo info;
            info.includeProbability = 1.0f;
            info.randomLocationMode = tcScenarioRandomizer::RandInfo::BOX;
            info.randomBox.push_back(box);
            randomInfo[unit] = info;
        }
    }

    void tcScenarioRandomizer::UpdateRandomBox(const std::string& unit, const tcRect& boxPrev, const tcRect& boxNew)
    {
        std::map<std::string, RandInfo>::iterator iter = 
            randomInfo.find(unit);
        if (iter != randomInfo.end())
        {
            size_t nBoxes = iter->second.randomBox.size();
            for (size_t n=0; n<nBoxes; n++)
            {
                if (iter->second.randomBox[n] == boxPrev)
                {
                    iter->second.randomBox[n] = boxNew;
                    return;
                }
            }
        }
        else
        {
            // unit not found
        }
    }

    void tcScenarioRandomizer::Clear()
    {
        randomInfo.clear();
    }

    void tcScenarioRandomizer::DeleteRandomBox(const std::string& unit, const tcRect& box)
    {
        std::map<std::string, RandInfo>::iterator iter = 
            randomInfo.find(unit);
        if (iter != randomInfo.end())
        {
            std::vector<tcRect> temp;
            size_t nBoxes = iter->second.randomBox.size();
            for (size_t n=0; n<nBoxes; n++)
            {
                if (iter->second.randomBox[n] != box)
                {
                    temp.push_back(iter->second.randomBox[n]);
                }
            }
            iter->second.randomBox = temp;
        }
        else
        {
            // unit not found
        }
    }

    void tcScenarioRandomizer::DeleteAllRandomBoxes(const std::string& unit)
    {
        std::map<std::string, RandInfo>::iterator iter = 
            randomInfo.find(unit);
        if (iter != randomInfo.end())
        {
            iter->second.randomBox.clear();
        }
        else
        {
            // unit not found
        }
    }


    void tcScenarioRandomizer::DeleteUnit(const std::string& unit)
    {
        std::map<std::string, RandInfo>::iterator iter = 
            randomInfo.find(unit);

        if (iter != randomInfo.end())
        {
            randomInfo.erase(iter);
        }
    }


    std::vector<tcRect> tcScenarioRandomizer::GetRandomBoxes(const std::string& unit) const
    {
        std::map<std::string, RandInfo>::const_iterator iter = 
            randomInfo.find(unit);
        if (iter != randomInfo.end())
        {
            return iter->second.randomBox;
        }
        else
        {
            std::vector<tcRect> empty;
            return empty;
        }
    }

    bool tcScenarioRandomizer::RandomBoxExists(const std::string& unit, const tcRect& box) const
    {
        std::map<std::string, RandInfo>::const_iterator iter = 
            randomInfo.find(unit);
        if (iter != randomInfo.end())
        {
            size_t nBoxes = iter->second.randomBox.size();
            for (size_t n=0; n<nBoxes; n++)
            {
                if (iter->second.randomBox[n] == box)
                {
                    return true;
                }
            }
        }

        return false;
    }

    void tcScenarioRandomizer::RenameUnit(const std::string& nameOld, const std::string& nameNew)
    {
        std::map<std::string, RandInfo>::iterator iter = 
            randomInfo.find(nameOld);

        if (iter != randomInfo.end())
        {
            RandInfo temp = iter->second;
            randomInfo.erase(iter);
            randomInfo[nameNew] = temp;
            return;
        }
    }

    void tcScenarioRandomizer::SaveToPython(tcScenarioLogger& logger)
    {
        std::map<std::string, RandInfo>::iterator iter = 
            randomInfo.begin();

        for ( ;iter != randomInfo.end(); ++iter)
        {
            wxString s;
            s.Printf("SM.SetIncludeProbability('%s', %f)", 
                iter->first.c_str(), iter->second.includeProbability);
            logger.AddScenarioText(s);

            for (size_t k=0; k<iter->second.randomBox.size(); k++)
            {
                s.Printf("SM.AddRandomBox('%s', %.4f, %.4f, %.4f, %.4f)",
                    iter->first.c_str(),
                    C_180OVERPI * iter->second.randomBox[k].left,
                    C_180OVERPI * iter->second.randomBox[k].right,
                    C_180OVERPI * iter->second.randomBox[k].bottom,
                    C_180OVERPI * iter->second.randomBox[k].top);
                logger.AddScenarioText(s);
            }
        }
    }

    void tcScenarioRandomizer::SetIncludeProbability(const std::string& unit, float prob)
    {
        std::map<std::string, RandInfo>::iterator iter = 
            randomInfo.find(unit);
        if (iter != randomInfo.end())
        {
            iter->second.includeProbability = prob;
        }
        else
        {
            RandInfo info;
            info.includeProbability = prob;
            info.randomLocationMode = tcScenarioRandomizer::RandInfo::NONE;
            randomInfo[unit] = info;
        }
    }

	tcScenarioRandomizer::tcScenarioRandomizer()
	{
	}

	tcScenarioRandomizer::~tcScenarioRandomizer()
	{
	}


}

