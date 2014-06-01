/**
**  @file tcAcousticModel.h
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

#ifndef _ACOUSTICMODEL_H_
#define _ACOUSTICMODEL_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
#include <vector>


namespace database
{
	class tcSqlReader;

    /**
    * Describes radiated acoustic noise (SL) vs. speed and depth
    */
    class tcAcousticModel
    {
    public:
        std::string databaseClass;
        std::vector<float> xSpeed_kts;
        std::vector<float> ySL_dB;
        float speedMinNL_kts;           ///< min speed for NL calculation
        float NL_min;                   ///< Self noise level for sonar detection at min speed
        float speedMaxNL_kts;           ///< max speed for NL calc
        float NL_max;                   ///< Self noise level for sonar detection at max speed
        float cavitationOffset_kts;     ///< cavitation onset speed at 0 m depth
        float cavitationSlope_ktsperft; ///< kts/ft increase with depth of cavitation onset speed
        float cavitationSL_dB;          ///< source level while cavitating
        float snorkelingSL_dB;          ///< source level while snorkeling
        
        float GetSourceLevel(float speed_kts, float depth_m) const;
        float GetSourceLevelSnorkeling() const;

        float GetCavitationSpeedKts(float depth_m) const;
        float GetCavitationDepth(float speed_kts) const;

        float GetNoiseLevelForSpeed(float speed_mps) const;
        float GetNoiseLevelForSpeedKts(float speed_kts) const;

        const char* GetName() const; ///< returns name of this instance
		static void AddSqlColumns(std::string& columnString);
		void ReadSql(tcSqlReader& entry);
		void WriteSql(std::string& valueString);

        tcAcousticModel();
        tcAcousticModel(const tcAcousticModel& obj); ///< copy constructor
        virtual ~tcAcousticModel();
	private:
        enum {SL_TABLE_SIZE=512};
        const float dv_kts; ///< resolution of lookup table
        const float one_over_dv; ///< 1.0 / resolution
        float SL_dB[SL_TABLE_SIZE]; ///< lookup table for SL

        float cavitationSlope_ktsperm; ///< kts/m version
        float invCavitationSlope_mperkts; ///< inverse m/kts
        float invSpeedRange_kts; ///< 1 / (speedMaxNL_kts-speedMinNL_kts)
        float NL_slope;

        void BuildSLTable();
        float GetVelocitySL(float speed_kts) const;
        

    };

}

#endif

