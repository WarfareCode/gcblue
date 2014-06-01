/**
**  @file tcTrackInterface.h
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


#ifndef __tcTrackInterface_h__
#define __tcTrackInterface_h__

#if _MSC_VER > 1000
#pragma once
#endif

#include "gctypes.h"


class tcAllianceSensorMap;
class tcSensorMapTrack;

namespace scriptinterface {

   class tcTrackInterface
   {
      // holds static reference to track ID of interest
   public:
      // platform info
      /// Sets affiliation of track, see @see Affiliation
      void SetAffiliation(UINT8 anAffil);
      void DeclareFriendly();
      void DeclareNeutral();
      void DeclareHostile();
      void DropTrack();
      /// Updates the ambiguity list for this track based on ESM intercepts
	  void UpdateAmbiguityList();

      static void SetTrack(long anID) {mnTrackID = anID;}
      static void SetSensorMap(tcAllianceSensorMap *apSM);
      static tcAllianceSensorMap* GetSensorMap();

      tcTrackInterface();
      virtual ~tcTrackInterface();   
   private:
      static long mnTrackID;
      static tcAllianceSensorMap *mpSensorMap;

	  tcSensorMapTrack* GetTrack();
   };

}

#endif // __tcTrackInterface_h__

