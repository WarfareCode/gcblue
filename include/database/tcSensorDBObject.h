/**
**  @file tcSensorDBObject.h
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

#ifndef _SENSORDBOBJECT_H_
#define _SENSORDBOBJECT_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "tcDatabaseObject.h"

class TiXmlElement;
class tcSensorState;
class tcGameObject;

namespace database
{
	class tcSqlReader;

	class tcSensorDBObject : public tcDatabaseObject 
	{
	public:
		float mfMaxRange_km;       ///< [km] max range regardless of theoretical detectability
		float mfRefRange_km;       ///< [km] range vs. 0 dBsm target or 0 dBW emitter
		float mfFieldOfView_deg;   ///< [degrees] 360 is max
        float minElevation_deg;    ///< [degrees] minimum elevation coverage
        float maxElevation_deg;    ///< [degrees] maximum elevation coverage
		float mfScanPeriod_s;      ///< [s]
        std::string damageEffect;  ///< damage susceptibility model
        float rangeError;          ///< fractional range error, 0 (perfect) to 1 (no range info)
        float angleError_deg;      ///< angular error in deg
        float elevationError_deg;  ///< elevation error in deg, use gte 90 for no height measurement
        float minFrequency_Hz;     ///< lowest operating or coverage frequency
        float maxFrequency_Hz;     ///< highest operating or coverage frequency
        float idThreshold_dB;      ///< excess SNR required for ID, use 99 for never
        float counterMeasureFactor;///< susceptibility factor for resisting CM, 0 best, high worst, 1.0 default
        bool isSurveillance;       ///< true if this sensor contributes reports to alliance map
	
        // calculated parameters
        float angleError_rad;
        float elevationError_rad;
        float minElevation_rad;
        float maxElevation_rad;
        float averageFrequency_Hz;

		virtual tcSensorState* CreateSensor(tcGameObject* parent); ///< factory method
		virtual const char* GetClassName() const {return "Sensor";} ///< returns class name of database object
		virtual void PrintToFile(tcFile& file);
        virtual const char* GetTypeDescription() const;

		static void AddSqlColumns(std::string& columnString);
		void ReadSql(tcSqlReader& entry);
		void WriteSql(std::string& valueString);


	protected:
        void CalculateParams();

		tcSensorDBObject();
		tcSensorDBObject(const tcSensorDBObject& obj); ///< copy constructor
		virtual ~tcSensorDBObject();
	};

} // namespace database

#endif

