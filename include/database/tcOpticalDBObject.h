/**
**  @file tcOpticalDBObject.h
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

#ifndef _OPTICALDBOBJECT_H_
#define _OPTICALDBOBJECT_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "tcSensorDBObject.h"

class TiXmlElement;

namespace database
{
	class tcSqlReader;

	class tcOpticalDBObject : public tcSensorDBObject 
	{
	public:
        unsigned int maxFireControlTracks; ///< max number of simultaneous fire control tracks
		bool isSemiactive;         ///< set true if this is semiactive / needs a designator on
        bool isDesignator;         ///< true if this is a laser designator
        bool mbDetectsSurface;     ///< set true if detects surface targets
		bool mbDetectsAir;         ///< set true if detects airborne targets
		bool mbDetectsMissile;     ///< set true if detects airborne missile targets
		bool mbDetectsGround;      ///< set true if detects ground targets
		bool isIR;					///< set true if detects infrared targets
		float nightFactor;		   ///< peak darkness range reduction factor

	    virtual tcSensorState* CreateSensor(tcGameObject* parent); ///< factory method
		virtual const char* GetClassName() const {return "Optical";} ///< returns class name of database object
		virtual void PrintToFile(tcFile& file);

		static void AddSqlColumns(std::string& columnString);
		void ReadSql(tcSqlReader& entry);
		void WriteSql(std::string& valueString);

		float EstimateDetectionRange(float signature_dB, bool isNight) const;
        virtual const char* GetTypeDescription() const;

		tcOpticalDBObject();
		tcOpticalDBObject(const tcOpticalDBObject& obj); ///< copy constructor
		virtual ~tcOpticalDBObject();
	};

} // namespace database

#endif

