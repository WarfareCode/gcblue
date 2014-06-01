/** 
**  @file tcAllianceInfo.cpp 
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

#include "tcAllianceInfo.h"
#include "common/tcGameStream.h"
#include "common/tcObjStream.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


/**
* Save state to stream
*/
tcGameStream& tcAllianceInfo::operator>>(tcGameStream& stream)
{
    // save relationship matrix and allianceNames
    for (int m=0; m<MAX_ALLIANCES; m++)
    {
        for (int n=0; n<MAX_ALLIANCES; n++)
        {
            stream << relationships[m][n];
        }

        stream << allianceData[m].name;
        stream << allianceData[m].country;
        stream << allianceData[m].isPlayable;
    }

    // save allianceList
    unsigned int nAlliances = (unsigned int)allianceList.size();
    stream << nAlliances;
    for (size_t k=0; k<allianceList.size(); k++)
    {
        stream << allianceList[k];
    }

    
    return stream;
}

/**
* Load state from stream
*/
tcGameStream& tcAllianceInfo::operator<<(tcGameStream& stream)
{
    Clear();

    // load relationship matrix and allianceNames
    for (int m=0; m<MAX_ALLIANCES; m++)
    {
        for (int n=0; n<MAX_ALLIANCES; n++)
        {
            stream >> relationships[m][n];
        }

        stream >> allianceData[m].name;
        stream >> allianceData[m].country;
        stream >> allianceData[m].isPlayable;
    }

    // load allianceList
    unsigned int nAlliances;
    stream >> nAlliances;
    for (size_t k=0; k<nAlliances; k++)
    {
        unsigned char alliance;
        stream >> alliance;
        allianceList.push_back(alliance);
    }

    return stream;
}


/**
* Save state to stream
*/
tcUpdateStream& tcAllianceInfo::operator>>(tcUpdateStream& stream)
{
    // save relationship matrix and allianceNames
    for (int m=0; m<MAX_ALLIANCES; m++)
    {
        for (int n=0; n<MAX_ALLIANCES; n++)
        {
            stream << relationships[m][n];
        }

        stream << allianceData[m].name;
        stream << allianceData[m].country;
        stream << allianceData[m].isPlayable;
    }

    // save allianceList
    unsigned int nAlliances = (unsigned int)allianceList.size();
    stream << nAlliances;
    for (size_t k=0; k<allianceList.size(); k++)
    {
        stream << allianceList[k];
    }

    
    return stream;
}

/**
* Load state from stream
*/
tcUpdateStream& tcAllianceInfo::operator<<(tcUpdateStream& stream)
{
    Clear();

    // load relationship matrix and allianceNames
    for (int m=0; m<MAX_ALLIANCES; m++)
    {
        for (int n=0; n<MAX_ALLIANCES; n++)
        {
            stream >> relationships[m][n];
        }

        stream >> allianceData[m].name;
        stream >> allianceData[m].country;
        stream >> allianceData[m].isPlayable;
    }

    // load allianceList
    unsigned int nAlliances;
    stream >> nAlliances;
    for (size_t k=0; k<nAlliances; k++)
    {
        unsigned char alliance;
        stream >> alliance;
        allianceList.push_back(alliance);
    }

    return stream;
}



tcAllianceInfo* tcAllianceInfo::Get()
{
    static tcAllianceInfo instance;

    return &instance;
}

void tcAllianceInfo::Clear()
{
    for (int m=0; m<MAX_ALLIANCES; m++)
    {
        for (int n=0; n<MAX_ALLIANCES; n++)
        {
            relationships[m][n] = (m != n) ? HOSTILE : FRIENDLY; // default all to HOSTILE
        }

        allianceData[m].Clear();
    }

    // to support multiplayer observer mode (alliance 0), alternate through the 3 affiliations
    for (int m=1; m<MAX_ALLIANCES; m+=3)
    {
        relationships[0][m] = FRIENDLY;
        relationships[m][0] = FRIENDLY;
    }
    for (int m=2; m<MAX_ALLIANCES; m+=3)
    {
        relationships[0][m] = HOSTILE;
        relationships[m][0] = HOSTILE;
    }
    for (int m=3; m<MAX_ALLIANCES; m+=3)
    {
        relationships[0][m] = NEUTRAL;
        relationships[m][0] = NEUTRAL;
    }

    allianceList.clear();
}

void tcAllianceInfo::AddAlliance(unsigned char alliance)
{
    if (alliance < MAX_ALLIANCES)
    {
        for (size_t n=0; n<allianceList.size(); n++)
        {
            if (allianceList[n] == alliance)
            {
                fprintf(stderr, "tcAllianceInfo::AddAlliance - alliance already exists, ignoring (%d)\n",
                    alliance);
                wxASSERT(false);
                return;
            }
        }

        allianceList.push_back(alliance);
    }
    else
    {
        fprintf(stderr, "tcAllianceInfo::AddAlliance - alliance out of range (%d)\n",
            alliance);
        wxASSERT(false);
    }
}


const std::vector<unsigned char>& tcAllianceInfo::GetAllianceList() const
{
    return allianceList;
}

const std::string& tcAllianceInfo::GetAllianceDefaultCountry(unsigned char alliance) const
{
    return allianceData[alliance & indexMask].country;
}


const std::string& tcAllianceInfo::GetAllianceName(unsigned char alliance) const
{
    return allianceData[alliance & indexMask].name;
}

tcAllianceInfo::Affiliation tcAllianceInfo::GetAffiliation(unsigned char alliance_a, unsigned char alliance_b) const
{
    return tcAllianceInfo::Affiliation(relationships[alliance_a & indexMask][alliance_b & indexMask]);
}

/**
* @return true if alliance exists in allianceList
*/
bool tcAllianceInfo::IsAllianceActive(unsigned char alliance) const
{
    for (size_t n=0; n<allianceList.size(); n++)
    {
        if (allianceList[n] == alliance) return true;
    }

    return false;
}

/**
* @return true if alliance doesn't have FRIENDLY or HOSTILE relationship with any other alliance
*/
bool tcAllianceInfo::IsAllianceNeutral(unsigned char alliance) const
{
    for (size_t n=0; n<allianceList.size(); n++)
    {
        if (allianceList[n] != alliance)
        {
            Affiliation affil = GetAffiliation(alliance, allianceList[n]);
            if ((affil == FRIENDLY) || (affil == HOSTILE)) return false;
        }
    }

    return true;
}

bool tcAllianceInfo::IsAlliancePlayable(unsigned char alliance) const
{
    if (IsAllianceActive(alliance))
    {
        return allianceData[alliance & indexMask].isPlayable;
    }
    else
    {
        return false;
    }
}


void tcAllianceInfo::SetAlliancePlayable(unsigned char alliance, bool state)
{
    if (IsAllianceActive(alliance))
    {
        allianceData[alliance & indexMask].isPlayable = state;
    }
    else
    {
    }
}


void tcAllianceInfo::SetAllianceDefaultCountry(unsigned char alliance, const std::string& s)
{
    if (alliance >= MAX_ALLIANCES)
    {
        fprintf(stderr, "tcAllianceInfo::SetAllianceDefaultCountry - Bad alliance value (%d)\n",
            alliance);
        wxASSERT(false);
        return;
    }

    allianceData[alliance].country = s;
}

void tcAllianceInfo::SetAllianceName(unsigned char alliance, const std::string& s)
{
    if (alliance >= MAX_ALLIANCES)
    {
        fprintf(stderr, "tcAllianceInfo::SetAllianceName - Bad alliance value (%d)\n",
            alliance);
        wxASSERT(false);
        return;
    }

    allianceData[alliance].name = s;
}

void tcAllianceInfo::SetRelationship(unsigned char alliance_a, unsigned char alliance_b, Affiliation affil)
{
    if ((alliance_a >= MAX_ALLIANCES) || (alliance_b >= MAX_ALLIANCES) || (alliance_a == alliance_b))
    {
        fprintf(stderr, "tcAllianceInfo::SetRelationship - Bad alliance value(s) (%d, %d)\n",
            alliance_a, alliance_b);
        wxASSERT(false);
        return;
    }

    relationships[alliance_a][alliance_b] = affil;
    relationships[alliance_b][alliance_a] = affil;
}


tcAllianceInfo::tcAllianceInfo()
: indexMask(0x0F)
{
    Clear();

    if (((MAX_ALLIANCES-1) & indexMask) != (MAX_ALLIANCES-1))
    {
        wxASSERT(false); ///< update indexMask
    }
}

tcAllianceInfo::~tcAllianceInfo()
{
}