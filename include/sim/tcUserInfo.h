/**  
**  @file tcUserInfo.h
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


#if !defined _USERINFO_H_
#define _USERINFO_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wx/wx.h" 

#include <string>
#include "tcAllianceInfo.h"

class tcGameStream;

/**
* Singleton class with info on single-player player or multiplayer client
* player.
*/
class tcUserInfo 
{
public:
    enum
    {
	    RANK_GM = 8
    };
    unsigned char mnOwnAlliance; 


    bool IsOwnAlliance(unsigned char anAlliance) const;
    unsigned char GetOwnAlliance() const;
    void SetOwnAlliance(unsigned char alliance);
    tcAllianceInfo::Affiliation GetAffiliationWith(unsigned char otherAlliance) const;

	const std::string& GetUsername() const;
    const std::string& GetUsernameWithRank();
	void SetUsername(const std::string& s);

	float GetScore() const;
	void SetScore(float x);


	unsigned char GetRank() const;
	const std::string RankToString(unsigned char rank);
	unsigned char ScoreToRank(float score);

    tcGameStream& operator>>(tcGameStream& stream);
    tcGameStream& operator<<(tcGameStream& stream);

	static tcUserInfo* Get(); ///< singleton accessor
    static void AttachAllianceInfo();
private:
    static tcAllianceInfo* allianceInfo;

	std::string username; ///< (client) username of player for multiplayer
	float score; ///< (client) score for user for info only, true score is maintained by server
	unsigned char rank;

    tcUserInfo();
    ~tcUserInfo();
};

#endif 
