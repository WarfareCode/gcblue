/*  
**  tcTrackInterface.cpp
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
#ifdef WIN32
#include "wx/msw/private.h" // for MS Windows specific definitions
#endif // WIN32
#endif

#include "tcTrackInterface.h"
#include "tcSensorMap.h"
#include "tcAllianceSensorMap.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif 


namespace scriptinterface {

   tcAllianceSensorMap* tcTrackInterface::mpSensorMap = NULL;
   long tcTrackInterface::mnTrackID = -1;


   void tcTrackInterface::SetSensorMap(tcAllianceSensorMap *apSM) 
   {
	   wxASSERT(apSM);

	   mpSensorMap = apSM;
#ifdef _DEBUG
       fprintf(stdout, "tcTrackInterface - Attaching sensor map for alliance: %d\n",
           mpSensorMap->GetAlliance());
#endif
   }

   tcAllianceSensorMap* tcTrackInterface::GetSensorMap()
   {
       return mpSensorMap;
   }

   void tcTrackInterface::DropTrack() 
   {
	   if (mpSensorMap == NULL) {return;}
	   mpSensorMap->DropTrack(mnTrackID);
   }

   tcSensorMapTrack* tcTrackInterface::GetTrack()
   {
	   wxASSERT(mpSensorMap);
	   if (mpSensorMap == 0) return 0;
	   if (mnTrackID == -1) return 0;
	   tcSensorMapTrack* track = mpSensorMap->GetSensorMapTrack(mnTrackID);
	   if (track == NULL) 
	   {
		   fprintf(stderr, "Warning - tcTrackInterface::GetTrack - "
			   "couldn't find track id: %d, alliance: %d\n",
			   mnTrackID, mpSensorMap->GetAlliance());
	   }	
	   return track;
   }

   void tcTrackInterface::SetAffiliation(UINT8 anAffil) 
   {
      if (mpSensorMap == NULL) {return;}
      if (mnTrackID == 0xFFFFFFFF) {return;}
      tcSensorMapTrack *pSMTrack = mpSensorMap->GetSensorMapTrack(mnTrackID);
      if (pSMTrack == NULL) 
	  {
		  fprintf(stderr, "Warning - tcTrackInterface::SetAffiliation - "
			  "couldn't find track id: %d, alliance: %d\n",
			  mnTrackID, mpSensorMap->GetAlliance());
		  return;
	  }
      pSMTrack->mnAffiliation = anAffil;
   }

   void tcTrackInterface::DeclareFriendly() 
   {
      SetAffiliation((UINT8)tcAllianceInfo::FRIENDLY);
   }
   void tcTrackInterface::DeclareNeutral() 
   {
      SetAffiliation((UINT8)tcAllianceInfo::NEUTRAL);
   }

   void tcTrackInterface::DeclareHostile()
   {
      SetAffiliation((UINT8)tcAllianceInfo::HOSTILE);
   }

   void tcTrackInterface::UpdateAmbiguityList()
   {
	   tcSensorMapTrack* track = GetTrack();
	   if (track)
	   {
		   track->UpdateAmbiguityList();
	   }
   }

   tcTrackInterface::tcTrackInterface()
   {
   }

   tcTrackInterface::~tcTrackInterface()
   {
   }

}



