/**
**  @file tcWeaponDBObject.h
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

#ifndef _WEAPONDBOBJECT_H_
#define _WEAPONDBOBJECT_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "tcDatabaseObject.h"

class TiXmlElement;

namespace database
{

#define SURFACE_TARGET 0x0001
#define AIR_TARGET 0x0002
#define LAND_TARGET 0x0004
#define MISSILE_TARGET 0x0008
#define SUBSURFACE_TARGET 0x0010
#define AEW_TARGET 0x1000 ///< virtual "target" for AEW mission type

	class tcSqlReader;

	class tcWeaponDBObject : public tcDatabaseObject 
	{
	public:
		float mfDamage;
        std::string damageModel;    ///< advanced damage model for dealing damage
        std::string damageEffect;   ///< advanced damage model for receiving damage
		float launchSpeed_mps;      ///< initial speed at launch, use zero to use plat speed
        int targetFlags;            ///< 0x01 surf, 0x02 air, 0x04 land, 0x08 missile, 0x10 sub
	    float minLaunchAlt_m;       ///< minimum altitude (negative is depth) at which missile can be launched [m]
	    float maxLaunchAlt_m;       ///< maximum altitude at which missile can be launched [m]
        float minRange_km;          ///< minimum standoff range from target
        float maxRange_km;          ///< maximum standoff range (what AI and range circle will use)
        float probNoFaults;         ///< probability that weapon will operate successfully to reach target area
        std::string payloadClass;   ///< payload to deploy (weapon shuts down after payload deployed)
		unsigned int payloadQuantity; ////< number of payload types to deploy
        float datalinkRange_km;     ///< range for datalink to weapon from launching platform
        bool acceptsUserCommands;   ///< true if user midcourse guidance accepted through datalink
        float detonationRange_m;    ///< detonate when this close to target, 0 means on impact

		virtual const char* GetClassName() const {return "Weapon";} ///< returns class name of database object
		virtual void PrintToFile(tcFile& file);

		static void AddSqlColumns(std::string& columnString);
		void ReadSql(tcSqlReader& entry);
		void WriteSql(std::string& valueString);

        bool IsNuclear() const;

	protected:
		tcWeaponDBObject();
		tcWeaponDBObject(const tcWeaponDBObject& obj); ///< copy constructor
		virtual ~tcWeaponDBObject();
	};

} // namespace database

#endif

