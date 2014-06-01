/**
**  @file tcAllianceInfo.h
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

#ifndef _TCALLIANCEINFO_H_
#define _TCALLIANCEINFO_H_

#include <vector>
#include <string>

class tcGameStream;
class tcUpdateStream;

/**
* Singleton class to hold info on alliance inter-affiliations
*/
class tcAllianceInfo
{
public:
    enum Affiliation {UNKNOWN = 0, FRIENDLY = 1, NEUTRAL = 2, HOSTILE = 3};
    enum {MAX_ALLIANCES = 16};

    static tcAllianceInfo* Get();
    
    const std::string& GetAllianceName(unsigned char alliance) const;
    const std::string& GetAllianceDefaultCountry(unsigned char alliance) const;
    Affiliation GetAffiliation(unsigned char alliance_a, unsigned char alliance_b) const;
    const std::vector<unsigned char>& GetAllianceList() const;

    void AddAlliance(unsigned char alliance);
    void SetAllianceName(unsigned char alliance, const std::string& s);
    void SetAllianceDefaultCountry(unsigned char alliance, const std::string& s);
    void SetAlliancePlayable(unsigned char alliance, bool state);
    bool IsAllianceActive(unsigned char alliance) const;
    bool IsAlliancePlayable(unsigned char alliance) const;
    void SetRelationship(unsigned char alliance_a, unsigned char alliance_b, Affiliation affil);
    bool IsAllianceNeutral(unsigned char alliance) const;

    void Clear();

    tcGameStream& operator>>(tcGameStream& stream);
    tcGameStream& operator<<(tcGameStream& stream);

    tcUpdateStream& operator>>(tcUpdateStream& stream);
    tcUpdateStream& operator<<(tcUpdateStream& stream);

private:
    struct AllianceData
    {
        std::string name;
        std::string country; ///< default country for alliance
        bool isPlayable; ///< true if alliance can be selected by player
        void Clear() {name.clear(); country.clear(); isPlayable=true;}
    };
    unsigned char relationships[MAX_ALLIANCES][MAX_ALLIANCES]; ///< matrix of relationships
    AllianceData allianceData[MAX_ALLIANCES];

    std::vector<unsigned char> allianceList;

    const unsigned char indexMask; ///< needs to match MAX_ALLIANCES


    tcAllianceInfo();
    ~tcAllianceInfo();
};






#endif

