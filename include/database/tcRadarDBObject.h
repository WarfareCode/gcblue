/**
**  @file tcRadarDBObject.h
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

#ifndef _RADARDBOBJECT_H_
#define _RADARDBOBJECT_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "tcSensorDBObject.h"

class TiXmlElement;

namespace database
{
    class tcSqlReader;

    class tcRadarDBObject : public tcSensorDBObject 
    {
    public:
		float ERPpeak_dBW;         ///< [dBW] effective radiated power, peak
        float ERPaverage_dBW;      ///< average ERP
		unsigned int maxFireControlTracks; ///< max number of simultaneous fire control tracks
		bool isSemiactive;         ///< set true if this is a semiactive radar
        float blindSpeed_mps;      ///< targets under this radial speed suffer large detection penalty, 0 for no blind speed
        float lookdownWater_dB;    ///< adjustment for look-down performance over water, negative is penalty
        float lookdownLand_dB;     ///< adjustment for look-down performance over land, negative is penalty
        float bandwidth_Hz;        ///< instantaneous bandwidth used for jamming calculations
        float azimuthBeamwidth_deg;
        float elevationBeamwidth_deg;   ///< beamwidth in elevation used for lookdown calculations, gain calcs
        float effectiveSidelobes_dB;    ///< effective SLL considering adaptive cancellation, relative to peak, always negative
		bool mbDetectsSurface;     ///< set true if detects surface targets
		bool mbDetectsAir;         ///< set true if detects airborne targets
		bool mbDetectsMissile;	   ///< set true if detects missiles
		bool mbDetectsGround;      ///< set true if detects ground targets

        /// calculated parameters
        float invBlindSpeed_mps;    ///< 1.0f / blindSpeed_mps;
        float antennaGain;          ///< calculated from az and el beamwidth
        float antennaGain_dBi;      ///< calculated from az and el beamwidth
        float invAzBeamwidth_deg;   ///< 1.0f / azimuthBeamwidth_deg
        float invElBeamwidth_deg;   ///< 1.0f / elevationBeamwidth_deg
        float cpi_s;                ///< CPI or dwell time calculated based on coverage angle and revisit period
        float jamConstant_dB;       ///< convert dB-W/m2 jam power density to J/N, assuming matched bandwidth and mainlobe

        virtual tcSensorState* CreateSensor(tcGameObject* parent); ///< factory method
        virtual const char* GetClassName() const {return "Radar";} ///< returns class name of database object
        virtual void PrintToFile(tcFile& file);
        
        static void AddSqlColumns(std::string& columnString);
        void ReadSql(tcSqlReader& entry);
        void WriteSql(std::string& valueString);

		float EstimateDetectionRange(float rcs_dBsm, bool overWater, bool overLand) const;
        virtual const char* GetTypeDescription() const;
        float CalculateFL(float& lambda2);

        tcRadarDBObject();
        tcRadarDBObject(const tcRadarDBObject& obj); ///< copy constructor
        virtual ~tcRadarDBObject();

    private:
        void CalculateParams();
    };

} // namespace database

#endif

