/**
**  @file tcMissileDBObject.h
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

#ifndef _MISSILEDBOBJECT_H_
#define _MISSILEDBOBJECT_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "tcWeaponDBObject.h"
#include "tcAirDetectionDBObject.h"
#include <vector>

class TiXmlElement;

namespace database
{
   class tcSqlReader;

   /**
   * This isn't used currently. Notionally there will be different
   * damage types that have varying effectiveness vs. different
   * target types.
   */
   enum teDamageType 
   {
      DT_GENERIC
   };

   /**
   * teAltitudeMode determines how altitude is controlled for flight segment.
   */
   enum teAltitudeMode 
   {
	   /// sea level reference
	   AM_ASL = 0, 
	   /// terrain reference (altimeter)
	   AM_AGL = 1,  
	   /// set altitude to intercept if seeker has track, otherwise maintain altitude
	   AM_INTERCEPT = 2,
	   /// set altitude to impact datum
	   AM_DATUM = 3,
	   /// Intercept if higher, otherwise maintain altitude
	   AM_INTERCEPT_HIGH = 4,
	   /// Same as AM_ASL but limit max pitch
	   AM_ASL_LOFT = 5
   };

   /**
   * teGuidanceMode determines guidance type that is used flight segment.
   */
   enum teGuidanceMode 
   {
       GM_COMMAND = 0,  ///< command guidance
       GM_NAV = 1,  ///< inertial, GPS
       GM_SENSOR1 = 2, ///< use seeker
       GM_DEPLOY = 3 ///< deploy payload at start of this segment
   };

   /**
   * Info that controls missile behavior for flight segment.
   */
   struct tsMissileFlightSegment 
   {
      float mfRange_km;    ///< min range for this segment
      float mfAltitude_m;  ///< altitude for segment
      teAltitudeMode meAltitudeMode;   ///< altitude mode 
      teGuidanceMode meGuidanceMode;   ///< guidance mode 
   };

#define MAX_MISSILE_FLIGHT_SEGMENTS 8


   class tcMissileDBObject : public tcWeaponDBObject, public tcAirDetectionDBObject
   {
   public:
      // flight model parameters
      float mfDragArea_sm;                ///< area for parasitic drag
      float mfGmax;                       ///< max Gs
      float mfMaxTurnRate_degps;          ///< max (slow speed) turn rate
      float mfCdpsub;                     ///< parasitic drag coeff, subsonic
      float mfCdptran;                    ///< transonic
      float mfCdpsup;                     ///< supersonic
      float mfMcm;                        ///< critical mach number
      float mfMsupm;                      ///< supersonic mach number
      float mfBoostThrust_N;              ///< boost thrust [N]
      float mfBoostTime_s;                ///< boost time [s]
      float mfSustThrust_N;               ///< sustainer thrust [N]
      float mfSustTime_s;                 ///< sustainer time [s]
      float mfShutdownSpeed_mps;          ///< self destructs below this speed after flameout

      // other parameters
      //float mfDamage;                   ///< damage value
      //teDamageType meDamageType;        ///< damage type enumeration
      //float mfRange_km;                   ///< [km] nominal range (replaced with maxRange_km in tcWeaponDBObject
    
      // sensor info
      tcDBString maSensorClass;           ///< seeker database class name
      long sensorKey;                     ///< key for fast access of primary seeker
	  bool needsFireControl;              ///< true if seeker depends on a fire control sensor for guidance
      bool acceptsWaypoints;              ///< true if missile can accept preplan (or datalink) waypoints

	  int fireAndForget;				  ///< -1 not initialized, 0 not FF, 1 FF
      int isARM;                          ///< -1 not initialized, 0 not ARM, 1 ARM

      float seekerFOV_rad;                ///< for fast lookup of seeker field of view
      float aczConstant_kts;
      float invMass_kg;                   ///< 1/mass_kg to avoid divide

      /// flight profile, array of flight segment info
      unsigned mnNumSegments;
      tsMissileFlightSegment maFlightProfile[MAX_MISSILE_FLIGHT_SEGMENTS];   

      virtual const char* GetClassName() const {return "Missile";} ///< returns class name of database object
      teWeaponLaunchMode GetLaunchMode() const;
      long GetSensorKey();
      float GetSeekerFOV(); ///< @returns FOV in radians
	  bool HasAllEmitters(std::vector<long>& emitters);
	  bool IsFireAndForget();
      bool IsCommandLaunched() const;
      bool IsARM();
	  bool NeedsFireControl() const;
      bool AcceptsWaypoints() const;
      float EstimateSpeed_mps() const;
      virtual void PrintToFile(tcFile& file);

	  static void AddSqlColumns(std::string& columnString);
	  void ReadSql(tcSqlReader& entry);
	  void WriteSql(std::string& valueString);

      void CalculateParams();

      tcMissileDBObject();
      tcMissileDBObject(const tcMissileDBObject& obj); ///< copy constructor
      virtual ~tcMissileDBObject();
   };

}

#endif

