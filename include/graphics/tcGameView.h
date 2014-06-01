/**  
**  @file tcGameView.h
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


#ifndef _GAMEVIEW_H_
#define _GAMEVIEW_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "wx/wx.h"
#ifdef WIN32
#include "wx/msw/private.h" // for MS Windows specific definitions
#endif

#include "tcAllianceInfo.h"
#include "simmath.h"
#include <vector>
#include "ai/Nav.h"
#include "tcTacticalMapView.h"

class tcSimState;
class tcUserInfo;
class tcOptions;
class tcObjectControl;
class tc3DScene;
class tcGameObject;
class tcPlatformObject;
class tcWorldMapView;
enum teSymbol;


#ifndef tsSceneObjectInfo
   struct tsSceneObjectInfo;
#endif


/**
* This class used to manage object/camera placement in the 3D scene. This
* functionality is commented out for now. Some of it needs to be incorporated
* into the ported version of the game with OSG e.g. displaying unknown objects.
* Class has lots of old code that likely needs refactoring.
*/
class tcGameView  
{
   struct ts3DObjectInfo
   {
      UINT32 mnSceneObjIdx; ///< idx of obj in scene obj array
      long mnID; ///< simstate obj key
   };
   
public:
   tcSimState *mpSS;
   tcOptions *mpOptions;
   tcTacticalMapView *mpMapView;
   tcWorldMapView *mpWorldMapView;
   tcUserInfo *mpUserInfo;
   tcObjectControl *mpObjectControl;
   tc3DScene *mpScene;

   float mfCamRange_m; ///< range of camera from hooked obj
   float mfCamAz_deg;
   float mfCamEl_deg;
   bool mbMouseLook; ///< for 3D window camera mouse look feature
   bool mbMouseZoom; ///< for 3D window cam mouse zoom
   wxPoint clickpoint;
   float mfAzStart_deg;
   float mfElStart_deg;
   float mfRangeStart_m;

   int mbDisplayTracks; ///< displays symbols for tracks of hooked platform

   void AttachMapView(tcTacticalMapView *apMapView) {mpMapView=apMapView;}
   void AttachObjectControl(tcObjectControl *apObjectControl) {mpObjectControl=apObjectControl;}
   void AttachOptions(tcOptions *pOptions) {mpOptions = pOptions;}   
   // void AttachScene(tc3DScene *apScene) {mpScene = apScene;}
   void AttachSimState(tcSimState *pSS) {mpSS=pSS;}
   void AttachUserInfo(tcUserInfo *pUserInfo) {mpUserInfo=pUserInfo;}
   void AttachWorldMapView(tcWorldMapView *apMapView) {mpWorldMapView=apMapView;}

   void Update(double afStatusTime);
   void UpdateScene(void);
   void Update3DObjects(void);
   void UpdateNavPoints(void);
   void UpdateHookInfo(void);


   void AddTruthTracks(unsigned int anAlliance, int& rnIndex, int& rnWorldIdx, tcAllianceInfo::Affiliation aeAffiliation);
   void AddSensorTracks(unsigned int anAlliance, int& rnIndex, int& rnWorldIdx, double afStatusTime);
   teSymbol GetMapSymbolByClassification(int anClassification, bool isGroup=false); 
   void OnMouseMove3D(UINT nFlags, wxPoint point);
   int OnMouseWheel3D(UINT nFlags, short zDelta, wxPoint point);
   void OnLButtonDown3D(UINT nFlags, wxPoint point);
   void OnLButtonUp3D(UINT nFlags, wxPoint point);

   tcGameView();
   virtual ~tcGameView();
private: 
   enum {MAX_3D_OBJECTS = 16}; 
   ts3DObjectInfo ma3DObjList[MAX_3D_OBJECTS];
   unsigned mn3DObjCount;
   long mnHookID;
   tcGameObject *mpHookedObj;
   std::vector<std::vector<tcTacticalMapView::NavPointInfo>> friendlyNavPoints;

   /*
   tc3DObject *mpDefaultObject;
   tc3DObject *unknown_all_model; ///< generic unknown model
   tc3DObject *unknown_air_model; ///< air 3D model for unknown units
   tc3DObject *unknown_lsurf_model; ///< large surface 3D model for unknown units
   tc3DObject *unknown_ssurf_model;///< small surface 3D model for unknown units
   tc3DObject *unknown_missile_model; ///< unknown missile model
   tc3DObject* GetUnknownModel(unsigned int classification);
   void SetSceneObjectInfo(tsSceneObjectInfo *pSOI, const tcGameObject *apGameObj);
   void Update3DObjectList(void);
   void Update3DObjectParameters(void);
   */

    tcAllianceInfo::Affiliation GetMapSymbolAffiliation(UINT8 anAffiliation);

    void CreateNavPoints(std::vector<tcTacticalMapView::NavPointInfo>& navPoints, 
                                 const std::vector<ai::Nav::WaypointData>& waypoints, tcPlatformObject* obj);
    void AddNavPoints(std::vector<std::vector<tcTacticalMapView::NavPointInfo>>& navPointsOther, tcPlatformObject* obj); 
};

#endif
