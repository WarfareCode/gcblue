/**
**  @file tcUserInfo.cpp
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

#include "tcUserInfo.h"
#include "common/tcGameStream.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

tcAllianceInfo* tcUserInfo::allianceInfo = 0;

tcUserInfo* tcUserInfo::Get()
{
	static tcUserInfo instance;

	return &instance;
}

void tcUserInfo::AttachAllianceInfo()
{
    allianceInfo = tcAllianceInfo::Get();
}


/**
* Save state to stream
*/
tcGameStream& tcUserInfo::operator>>(tcGameStream& stream)
{
    stream << mnOwnAlliance;
    
    return stream;
}

/**
* Load state from stream
*/
tcGameStream& tcUserInfo::operator<<(tcGameStream& stream)
{
    stream >> mnOwnAlliance;

    return stream;
}



tcAllianceInfo::Affiliation tcUserInfo::GetAffiliationWith(unsigned char otherAlliance) const
{
    return allianceInfo->GetAffiliation(mnOwnAlliance, otherAlliance);
}

unsigned char tcUserInfo::GetOwnAlliance() const
{
   return mnOwnAlliance;
}

unsigned char tcUserInfo::GetRank() const
{
	return rank;
}

float tcUserInfo::GetScore() const
{
	return score;
}

const std::string& tcUserInfo::GetUsername() const
{
	return username;
}

const std::string& tcUserInfo::GetUsernameWithRank()
{
    static std::string s;

    s = RankToString(rank) + " " + username;

	return s;
}


bool tcUserInfo::IsOwnAlliance(unsigned char anAlliance) const
{
   return (anAlliance == mnOwnAlliance);
}

const std::string tcUserInfo::RankToString(unsigned char rank)
{
	static std::string s;

	if (rank == 0) s = "CDT";
	else if (rank == 1) s = "LTJG";
	else if (rank == 2) s = "LT";
	else if (rank == 3) s = "LCDR";
	else if (rank == 4) s = "CDR";
	else if (rank == 5) s = "CAPT";
	else if (rank == 6) s = "ADM";
	else if (rank == 7) s = "ADM";
	else if (rank == 8) s = "GM";
	else s = "???";

	return s;

}

unsigned char tcUserInfo::ScoreToRank(float score)
{
	if (score < 100.0f) return 0; 
	else if (score < 500.0f) return 1;
	else if (score < 1000.0f) return 2;
	else if (score < 2000.0f) return 3;
	else if (score < 5000.0f) return 4;
	else if (score < 10000.0f) return 5;
	else if (score < 20000.0f) return 6;
	else if (score < 500000.0f) return 7;
	else return 8;

}

void tcUserInfo::SetOwnAlliance(unsigned char alliance) 
{
	mnOwnAlliance = alliance;
}


void tcUserInfo::SetScore(float x)
{
	score = x;

	rank = ScoreToRank(score);
}


void tcUserInfo::SetUsername(const std::string& s)
{
	username = s;
}

tcUserInfo::tcUserInfo()
: mnOwnAlliance(1), score(0), rank(0)
{
   
}

tcUserInfo::~tcUserInfo() 
{
}

