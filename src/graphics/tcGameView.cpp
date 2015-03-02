/*  
**  @file tcGameView.cpp
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
#endif
#endif

#include "tcGameView.h"
#include "tcSimState.h"
#include "tcTacticalMapView.h"
#include "tcWorldMapView.h"
#include "tcUserInfo.h"
#include "tcOptions.h"
#include "tcObjectControl.h" // to pass range circle, etc. symbols to map
#include "tcMissileObject.h"
#include "tcFlightOpsObject.h"
#include "ai/Brain.h"
#include "ai/Nav.h"
#include "ai/Route.h"
#include "ai/tcMissionManager.h"
#include "ai/tcMission.h"
#include "tcPlatformInterface.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif 
//* #include "tc3DScene.h"


using namespace std;


tcAllianceInfo::Affiliation tcGameView::GetMapSymbolAffiliation(UINT8 anAffiliation) 
{
    if (anAffiliation == 0) {
        return tcAllianceInfo::UNKNOWN;
    }
    else if (anAffiliation == 1) {
        return tcAllianceInfo::FRIENDLY;
    }
    else if (anAffiliation == 2) {
        return tcAllianceInfo::NEUTRAL;
    }
    else if (anAffiliation == 3) {
        return tcAllianceInfo::HOSTILE;
    }
    else {
        return tcAllianceInfo::UNKNOWN;
    }
}

teSymbol tcGameView::GetMapSymbolByClassification(int anClassification, bool isGroup)
{
    switch (anClassification) 
    {
    case PTYPE_UNKNOWN:
        return SYMBOL_UNKNOWN;
        break;
    case PTYPE_SURFACE:
        return isGroup ? SYMBOL_SURFACEGROUP : SYMBOL_SURFACE;
        break;
    case PTYPE_SMALLSURFACE:
        return isGroup ? SYMBOL_SURFACEGROUP : SYMBOL_SMALLSURFACE;
        break;
    case PTYPE_LARGESURFACE:
        return isGroup ? SYMBOL_SURFACEGROUP : SYMBOL_LARGESURFACE;
        break;
    case PTYPE_CARRIER:
        return isGroup ? SYMBOL_CARRIERGROUP : SYMBOL_CARRIER;
        break;
    case PTYPE_AIR:
        return SYMBOL_AIR;
        break;
    case PTYPE_FIXEDWING:
        return SYMBOL_FIXEDWING;
        break;
    case PTYPE_MISSILE:
        return SYMBOL_MISSILE;
        break;
    case PTYPE_HELO:
        return SYMBOL_HELO;
        break;
    case PTYPE_SUBSURFACE:
        return SYMBOL_SUBSURFACE;
        break;
    case PTYPE_SUBMARINE:
        return SYMBOL_SUBMARINE;
        break;
    case PTYPE_TORPEDO:
        return SYMBOL_TORPEDO;
        break;
    case PTYPE_BALLISTIC:
    case PTYPE_SONOBUOY:
    case PTYPE_AIRCM:
    case PTYPE_WATERCM:
    case PTYPE_WATERMINE:
        return SYMBOL_MARK;
        break;
    case PTYPE_GROUND:
        return SYMBOL_FIXED;
        break;
    case PTYPE_AIRFIELD:
        return SYMBOL_AIRFIELD;
        break;
    case PTYPE_GROUNDVEHICLE:
        return SYMBOL_GROUNDVEHICLE;
        break;
    default:
        return SYMBOL_UNKNOWN;
        break;
    }
}



void tcGameView::UpdateHookInfo() 
{
    // returns -1 if no hooks, first hooked unit otherwise
    mnHookID = mpMapView->GetHookID(); 
    if (mnHookID == NULL_INDEX) 
    {
        mpHookedObj = NULL;
    }
    else 
    {
        mpHookedObj = mpSS->GetObject(mnHookID);
    }
}

void tcGameView::UpdateNavPoints() 
{
    std::vector<tcTacticalMapView::NavPointInfo> navPoints;
    //std::vector<GeoPoint> navpoints;
    //std::vector<wxArrayString> tasks; // tasks for each waypoint

    long platformId = -1;
    long missionId = -1;
    unsigned int currentIdx = 0;
    bool navPointEditBlock = false;

    tcPlatformObject* platformObj = dynamic_cast<tcPlatformObject*>(mpHookedObj);

    if (platformObj && mpHookedObj->IsOwnAlliance())
    {
        // check if this is a flight ops object with an active edit mission
        tcFlightOpsObject* flightOps = dynamic_cast<tcFlightOpsObject*>(platformObj);
        
        ai::Route* route = 0;

        if (flightOps != 0)
        {
            ai::tcMissionManager* missionManager = flightOps->GetFlightPort()->GetMissionManager();
            if ((missionManager != 0) && (missionManager->GetEditMissionId() != 0))
            {
                ai::tcMission* mission = missionManager->GetMission(missionManager->GetEditMissionId());
                if (mission != 0)
                {
                    route = mission->GetRoute();
                    missionId = missionManager->GetEditMissionId();
                    if (mission->IsLocked()) navPointEditBlock = true;
                }
            }
        }

        if (route == 0)
        {
            if (ai::Nav* nav = platformObj->GetBrain()->GetNavTask())
            {
                route = nav;
            }
        }

        if (route != 0)
        {
            const vector<ai::Nav::WaypointData>& waypoints = route->GetWaypoints();

            CreateNavPoints(navPoints, waypoints, platformObj);
            platformId = platformObj->mnID;
            currentIdx = route->GetCurrentWaypoint();
        }
        
    }
    
    mpMapView->UpdateNavPointsPrimary(navPoints, currentIdx, platformId, missionId);
    mpMapView->SetNavPointEditLock(navPointEditBlock);
}

/**
* Adds waypoints for one platform
*/
void tcGameView::AddNavPoints(std::vector<std::vector<tcTacticalMapView::NavPointInfo>>& navPointsOther, tcPlatformObject* obj)
{
    wxASSERT(obj != 0);

    ai::Nav* nav = obj->GetBrain()->GetNavTask();
    if (nav == 0) return;

    const vector<ai::Nav::WaypointData>& waypoints = nav->GetWaypoints();
    size_t currentIdx = size_t(nav->GetCurrentWaypoint());
    if (currentIdx >= waypoints.size()) return;

    std::vector<tcTacticalMapView::NavPointInfo> platformWaypoints;

    tcTacticalMapView::NavPointInfo info;
    
    // add current location as first point
    info.geo.mfLon_rad = obj->mcKin.mfLon_rad;
    info.geo.mfLat_rad = obj->mcKin.mfLat_rad;
    info.geo.mfAlt_m = obj->mcKin.mfAlt_m;
    info.referenceMode = 0;
    
    platformWaypoints.push_back(info);

    for (size_t n=currentIdx; n<waypoints.size(); n++)
    {
        info.geo = waypoints[n].waypoint;
        platformWaypoints.push_back(info);
    }


    navPointsOther.push_back(platformWaypoints);
}

void tcGameView::CreateNavPoints(std::vector<tcTacticalMapView::NavPointInfo>& navPoints,
                                 const vector<ai::Nav::WaypointData>& waypoints, tcPlatformObject* obj)
{
    if (waypoints.size())
    {   // use current position as first point
        tcTacticalMapView::NavPointInfo info;

        info.geo.mfLon_rad = obj->mcKin.mfLon_rad;
        info.geo.mfLat_rad = obj->mcKin.mfLat_rad;
        info.geo.mfAlt_m = obj->mcKin.mfAlt_m;
        info.referenceMode = 0;

        navPoints.push_back(info);
    }

    // add copy of all waypoints
    for (size_t k=0; k<waypoints.size(); k++)
    {
        tcTacticalMapView::NavPointInfo info;

        info.geo = waypoints[k].waypoint;
        for (size_t m=0; m<waypoints[k].tasks.size(); m++)
        {
            info.tasks.push_back(waypoints[k].tasks[m].c_str());
        }
        info.referenceMode = waypoints[k].referenceMode;
        
        navPoints.push_back(info);
    }
}

#if 0

/**
* Returns the appropriate unknown model based on functional
* classification. Only supports small, large, and air for now.
* @param classification 16-bit functional classification defined in tcDatabase.h
* @return pointer to 3D model, unknown air model is returned if nothing else matches.
*/
tc3DObject* tcGameView::GetUnknownModel(unsigned int classification)
{
    if (classification & PTYPE_SURFACE)
    {
        if (classification & PTYPE_SMALLSURFACE)
        {
            return unknown_ssurf_model;
        }
        else
        {
            return unknown_lsurf_model;
        }
    }
    else if (classification & PTYPE_AIR)
    {
        return unknown_air_model;
    }
    else if (classification & PTYPE_MISSILE)
    {
        return unknown_missile_model;
    }
    else
    {
        return unknown_all_model;   // need generic unknown model for here
    }
}


/*****************************************************************************/
void tcGameView::OnMouseMove3D(UINT nFlags, wxPoint point) 
{
    // point.y = mnHeight - point.y; // 0 is bottom of screen

    if (mbMouseLook) 
    {
        float dAz = 1.0f*(float)(point.x - clickpoint.x);
        float dEl = 1.0f*(float)(point.y - clickpoint.y);

        // update mouselook scene panning
        mfCamAz_deg = dAz + mfAzStart_deg;
        mfCamEl_deg = dEl + mfElStart_deg;
        if ( mfCamAz_deg < 0) { mfCamAz_deg += 360.0f;}
        else if ( mfCamAz_deg > 360.0f) {mfCamAz_deg -= 360.0f;}
        if (mfCamEl_deg < -89.0f) {mfCamEl_deg = -89.0f;}
        else if (mfCamEl_deg > 89.0f) {mfCamEl_deg = 89.0f;}
    }
    else if (mbMouseZoom) 
    {
        float dRange = 1.0f*(float)(point.y - clickpoint.y);
        mfCamRange_m = dRange + mfRangeStart_m;
        if (mfCamRange_m < 50.0f) {mfCamRange_m = 50.0f;}
    }

}
/*****************************************************************************/
int tcGameView::OnMouseWheel3D(UINT nFlags, short zDelta, wxPoint point)
{
    if (mbMouseZoom) return 0; // wheel ignored if mouse zoom active

    float rangeFactor = (zDelta > 0) ? 0.96f : 1.04f;
    mfCamRange_m *= rangeFactor;
    if (mfCamRange_m < 50.0f) {mfCamRange_m = 50.0f;}
    return 0;
}
/*****************************************************************************/
void tcGameView::OnLButtonDown3D(UINT nFlags, wxPoint point) 
{

    if (mpScene == NULL) {return;}
    if (nFlags & MK_CONTROL) 
    {
        mbMouseZoom = true;
    }
    else {
        mbMouseLook = true;
    }

    //point.y = mnHeight - point.y; // 0 is bottom of screen

    clickpoint = point;
    mfAzStart_deg = mfCamAz_deg;
    mfElStart_deg = mfCamEl_deg;
    mfRangeStart_m = mfCamRange_m;
}
/*****************************************************************************/
void tcGameView::OnLButtonUp3D(UINT nFlags, wxPoint point) 
{
    mbMouseLook = false;
    mbMouseZoom = false;
}


/**
* Fills in the 3D model info for a given game object.
* Recursively sets info for child objects unless the object
* only has a functional classification. 
* Needs work to properly handle unknown classfication and
* sensor track objects.
*/
void tcGameView::SetSceneObjectInfo(tsSceneObjectInfo *pSOI, const tcGameObject *apGameObj) 
{
    pSOI->mnID = apGameObj->mnID;
    pSOI->dpitch = 0;
    pSOI->droll = 0;

    bool useTrue = ((mpUserInfo->IsOwnAlliance(apGameObj->GetAlliance()))||(mpOptions->mnViewMode < 2));
    if (useTrue)
        pSOI->mpObj = apGameObj->mpDBObject->mp3DObj;
    else
        pSOI->mpObj = GetUnknownModel(apGameObj->mpDBObject->mnType);


    if (apGameObj->parent == NULL) 
    {
        pSOI->y = apGameObj->mcKin.mfAlt_m;
        pSOI->mfYaw = -apGameObj->mcKin.mfHeading_rad*C_180OVERPI;
        pSOI->mfPitch = apGameObj->mcKin.mfPitch_rad*C_180OVERPI;
        pSOI->mfRoll = apGameObj->mcKin.mfRoll_rad*C_180OVERPI;

        double fLat_deg = (double)apGameObj->mcKin.mfLat_rad*C_180OVERPI;
        double fLon_deg = (double)apGameObj->mcKin.mfLon_rad*C_180OVERPI;
        pSOI->x = mpScene->LonToX(fLon_deg);
        pSOI->z = mpScene->LatToZ(fLat_deg);
    }
    else 
    {
        pSOI->x = apGameObj->rel_pos.dx;
        pSOI->y = apGameObj->rel_pos.dy;
        pSOI->z = apGameObj->rel_pos.dz;
        pSOI->mfYaw = -apGameObj->rel_pos.yaw*C_180OVERPI;
        pSOI->mfPitch = apGameObj->rel_pos.pitch*C_180OVERPI;
        pSOI->mfRoll = apGameObj->rel_pos.roll*C_180OVERPI;
    }

    // if !useTrue, add child objects recursively, else return
    if (!useTrue) return;
    pSOI->children.clear();
    size_t count = apGameObj->children.size();
    for (size_t n=0;n<count;n++)
    {
        tsSceneObjectInfo objectInfo;
        tcGameObject *child = apGameObj->children.at(n);
        if (child->rel_pos.isVisible) {
            SetSceneObjectInfo(&objectInfo, child);
            pSOI->children.push_back(objectInfo);
        }
    }
}

// remove objects that are out of range
// add objects that have entered range
void tcGameView::Update3DObjectList() 
{
    tsSceneObjectInfo soi;

    // clear current list
    mn3DObjCount = 0;
    mpScene->RemoveAllObjects();

    // add hooked obj first
    tcGameObject *pGameObj;
    long nHookId = mpMapView->mnHookID;
    if (nHookId != NULL_INDEX) {
        if (mpSS->maPlatformState.Lookup(nHookId, pGameObj)==true) {
            SetSceneObjectInfo(&soi, pGameObj);
            if (mpScene->AddObject(soi)) {
            }
        }
    }

    // search through objects and add all other objects within range
    unsigned nSize = mpSS->maPlatformState.GetCount();
    long poolpos = mpSS->maPlatformState.GetStartPosition();
    long nKey;
    unsigned n = 0;
    bool bSceneFull = false;
    const float fRenderRange_km = 15.0f;
    tsSceneCameraInfo sci;
    tcKinematics refKin;

    mpScene->GetCameraInfo(sci);
    refKin.mfLat_rad = sci.mfLat_deg*C_PIOVER180;
    refKin.mfLon_rad = sci.mfLon_deg*C_PIOVER180;
    refKin.mfAlt_m = sci.mfAlt_m;

    // loop through all game objects and display those matching anAlliance
    while ((n++<nSize)&&(!bSceneFull)) {
        mpSS->maPlatformState.GetNextAssoc(poolpos,nKey,pGameObj);
        float fRange_km = pGameObj->mcKin.RangeToKmAlt(refKin);
        if (fRange_km <= fRenderRange_km) {
            SetSceneObjectInfo(&soi, pGameObj);
            bSceneFull = !mpScene->AddObject(soi);
        }
    }
}

// update parameters of objects in list
void tcGameView::Update3DObjectParameters() 
{
    tsSceneObjectInfo* aSOI;
    tcGameObject* pGameObj;

    unsigned nObjects = mpScene->GetObjectInfoArray(aSOI);  
    for(unsigned n=0;n<nObjects;n++) {
        long nID = aSOI[n].mnID;
        if (mpSS->maPlatformState.Lookup(nID, pGameObj)) {
            SetSceneObjectInfo(&aSOI[n], pGameObj);
        }
    }
}

void tcGameView::Update3DObjects() 
{
    static unsigned snCounter = 0;

    if (snCounter++ % 1 == 0) {
        Update3DObjectList();
    }
    else {
        Update3DObjectParameters();
    }
}

void tcGameView::UpdateScene() 
{
    tcGameObject *pGameObj;
    tsSceneCameraInfo sci;
    static snLastHookId = 0;
    bool bNewHook;

    if (mpScene == NULL) {return;}

    // get hooked object info
    UpdateHookInfo();
    long nHookId = mnHookID;
    if (nHookId == NULL_INDEX) {return;}
    pGameObj = mpHookedObj;
    if (pGameObj == NULL) {return;}

    // set initial camera params if new hook
    bNewHook = (nHookId != snLastHookId);
    snLastHookId = nHookId;
    if (bNewHook) 
    {
        // move this to its own function
        tc3DObject *p3DObj;
        bool useTrue = ((mpUserInfo->IsOwnAlliance(pGameObj->mnAlliance))||(mpOptions->mnViewMode < 2));
        if (useTrue)
            p3DObj = pGameObj->mpDBObject->mp3DObj;
        else
            p3DObj = GetUnknownModel(pGameObj->mpDBObject->mnType);

        if (p3DObj != NULL) {
            mfCamRange_m = p3DObj->mfDimension*1.0f;
        }
        mfCamAz_deg = 10.0f + pGameObj->mcKin.mfHeading_rad*C_180OVERPI;
        if (mfCamAz_deg > 360.0f) {mfCamAz_deg -= 360.0f;}
        mfCamEl_deg = (pGameObj->mcKin.mfAlt_m > 100.0f) ? -20.0f : -20.0f;
    }

    // update scene camera based on obj params
    double fLat_deg = pGameObj->mcKin.mfLat_rad*C_180OVERPI;
    double fLon_deg = pGameObj->mcKin.mfLon_rad*C_180OVERPI;
    float fAlt_m = pGameObj->mcKin.mfAlt_m;
    //float fAz = pGameObj->mcKin.mfHeading_rad;


    mpScene->GetCameraInfo(sci);
    float fCamEl_rad = mfCamEl_deg*C_PIOVER180;
    float fCamAz_rad = mfCamAz_deg*C_PIOVER180;
    float fOffset_deg = mfCamRange_m*C_MTODEG;
    float fOffsetxz_deg = cosf(fCamEl_rad)*fOffset_deg;
    float fOffsety_m = sinf(fCamEl_rad)*mfCamRange_m;

    sci.mfLookAz_rad = fCamAz_rad;
    sci.mfLookEl_rad = fCamEl_rad;
    sci.mfLon_deg = fLon_deg - fOffsetxz_deg*sinf(fCamAz_rad)/
        cosf((float)pGameObj->mcKin.mfLat_rad);
    sci.mfLat_deg = fLat_deg - fOffsetxz_deg*cosf(fCamAz_rad);
    sci.mfAlt_m = fAlt_m - fOffsety_m;
    if (sci.mfAlt_m < 25.0f) {sci.mfAlt_m = 25.0f;}

    mpScene->SetCameraInfo(sci);
}
#endif

/**
* This method adds populated tcMapObj objects to the tactical and
* world map views. This is called once per frame. Needs refactoring.
*/
void tcGameView::Update(double afStatusTime)
{
//    long cmappos = mpSS->maPlatformState.GetStartPosition();
//    int nSize = mpSS->maPlatformState.GetCount();
    int nMapObj = 0;
    int nWorldMapObj = 0;
    int nViewMode = mpOptions->mnViewMode;

    if ((mpMapView==NULL)|(mpSS==NULL)) {return;}

    UpdateHookInfo();

    UINT8 ownAlliance = mpUserInfo->GetOwnAlliance();

    tcAllianceInfo* allianceInfo = tcAllianceInfo::Get();
    const std::vector<unsigned char>& allianceList = allianceInfo->GetAllianceList();

    bool isMultiplayerServer = mpSS->IsMultiplayerServer();

    bool drawAllTruth = ((nViewMode < 2) && tcPlatformInterface::GetDeveloperMode()) || tcGameObject::IsEditMode() || 
         isMultiplayerServer || (ownAlliance == 0);

    friendlyNavPoints.clear();

    for (size_t k=0; k<allianceList.size(); k++)
    {
        unsigned char alliance_k = allianceList[k];
        tcAllianceInfo::Affiliation affil = allianceInfo->GetAffiliation(ownAlliance, alliance_k);
        if ((ownAlliance == alliance_k) || drawAllTruth)
        {
            AddTruthTracks(alliance_k, nMapObj, nWorldMapObj, affil);
        }
    }

    if (mpOptions->drawNavPointsMode > 0)
    {
        mpMapView->UpdateNavPointsOther(friendlyNavPoints);
    }


    if ((nViewMode != 1) && !isMultiplayerServer)
	{
        AddSensorTracks(ownAlliance, nMapObj, nWorldMapObj, afStatusTime);
    }



    // display target if applicable
    bool bShowTarget = false;
    tcTrack track;
    tcPlatformObject *pPlatformObj = dynamic_cast<tcPlatformObject*>(mpHookedObj);
    tcMissileObject *pMissileObj = dynamic_cast<tcMissileObject*>(mpHookedObj);
    if (pPlatformObj != NULL) 
	{
        long nTarget = pPlatformObj->GetBrain()->GetTarget();
        if (nTarget != NULL_INDEX) 
		{
            bShowTarget = mpSS->mcSensorMap.GetTrack(nTarget, track, ownAlliance);
        }
    }
    else if ((pMissileObj != 0)&&(pMissileObj->GetAlliance() == ownAlliance)) 
	{
		tcSensorState* sensor = pMissileObj->GetSeekerSensor();
		if (sensor != 0)
		{
			bShowTarget = sensor->GetTrack(track);
		}
    }


    if (bShowTarget) 
	{
        tcTrack predictedtrack;
        track.GetPrediction(predictedtrack,afStatusTime);
        mpMapView->maMapObj[nMapObj].mbExists = 1;
        mpMapView->maMapObj[nMapObj].mbFocus = 0;
        mpMapView->maMapObj[nMapObj].mfHeading = 0;
        mpMapView->maMapObj[nMapObj].mnFlags = 0;
        mpMapView->maMapObj[nMapObj].meSymbol = SYMBOL_TARGET;
        mpMapView->maMapObj[nMapObj].mnColor = 0xFFFF0000;
        mpMapView->maMapObj[nMapObj].mfLon = predictedtrack.mfLon_rad;
        mpMapView->maMapObj[nMapObj].mfLat = predictedtrack.mfLat_rad;
        mpMapView->maMapObj[nMapObj].mnID = NULL_INDEX;


        nMapObj++;
    }


    // display range indication graphics from user selection in mpObjectControl
    if (mpObjectControl != 0) 
    {
        const std::vector<MapSymbolInfo>& symbolList = mpObjectControl->GetMapSymbols();
		size_t nMapSymbols = symbolList.size();

        for(unsigned i=0;
			(i<nMapSymbols)&&(nMapObj<MAXMAPOBJ);
			i++) 
        {
			const MapSymbolInfo& symbol = symbolList[i];
            tcMapObj* pMO = &mpMapView->maMapObj[nMapObj++];
            //*pMO = mpMapView->maMapObj[0];
            pMO->mbFocus = false;
            pMO->mbExists = true;
            pMO->mfLat = symbol.mfLat_rad;
            pMO->mfLon = symbol.mfLon_rad;
            pMO->mfLat2 = symbol.mfLat2_rad;
            pMO->mfLon2 = symbol.mfLon2_rad;
            pMO->mfLatExtent = symbol.mfLatExtent_rad;
            pMO->mfLonExtent = symbol.mfLonExtent_rad;
            pMO->mfHeading = symbol.mfArcCenter_deg; // fix this rad/deg double use
            pMO->mfArc_deg = symbol.mfArcLength_deg;
            pMO->meSymbol = (symbol.mfLat2_rad == 0) ? SYMBOL_PIE : SYMBOL_LINE;
            pMO->mnFlags = 0;
            pMO->mnColor = symbol.mnColor;
            pMO->mnID = NULL_INDEX;
            pMO->errorPoly.clear();
        }
    }

    mpMapView->mnObjCount = nMapObj;
    mpWorldMapView->mnObjCount = nWorldMapObj;

    // ---------------
    UpdateNavPoints();
    /*
    // clear remainder of symbols
    for(int i=nMapObj;i<MAXMAPOBJ;i++) {
    mpMapView->maMapObj[i].mbExists = 0;
    }
    */
    //UpdateScene(); // called later in the main loop to avoid issue with objects not shifting with terrain

}

/**
* add truth data to view for objects matching anAlliance
*/
void tcGameView::AddTruthTracks(unsigned int anAlliance,  
                                int& rnIndex, int& rnWorldIdx, tcAllianceInfo::Affiliation aeAffiliation) 
{
    tcGameObject *po;
    tcPoint point;
    unsigned int nSize = mpSS->maPlatformState.GetCount();
    long poolpos = mpSS->maPlatformState.GetStartPosition();
    long nKey;
    unsigned int i = 0;
    unsigned int nColor;

	nColor = 0; // use zero to let mapview pick color

    // show faded unless a multiplayer observer
    unsigned char ownAlliance = mpUserInfo->GetOwnAlliance();
    bool showFadedSymbols = ownAlliance != 0;
	bool showAllSmall = mpMapView->GetLonSpan() < 0.10472; // show if zoomed in more than about 6 deg lon span (360 NMI at equator)

    // loop through all game objects and display those matching anAlliance
    while (i++ < nSize) 
	{
        mpSS->maPlatformState.GetNextAssoc(poolpos,nKey,po);
		tcDatabaseObject* pdata = po->mpDBObject;

        point.x = (float)po->mcKin.mfLon_rad;
        point.y = (float)po->mcKin.mfLat_rad;
        int bAllianceMatch = (po->GetAlliance() == anAlliance);
		bool showSmallCheck = showAllSmall ||				(
			(po->mpDBObject->mnType != PTYPE_AIRCM) &&
			(po->mpDBObject->mnType != PTYPE_WATERCM) &&
			(po->mpDBObject->mnType != PTYPE_SONOBUOY) &&
            (po->mpDBObject->mnType != PTYPE_WATERMINE) &&
			(po->mpDBObject->mnType != PTYPE_BALLISTIC)		);

        if (bAllianceMatch && (mpMapView->PointInView(point)) && showSmallCheck && (rnIndex < MAXMAPOBJ)) 
		{
            tcPlatformObject* platform = dynamic_cast<tcPlatformObject*>(po);
            bool formationLeader = (platform != 0) && (platform->formation.IsLeader());
 

			
            mpMapView->maMapObj[rnIndex].mbExists = 1;
            mpMapView->maMapObj[rnIndex].mbFocus = 0;
			mpMapView->maMapObj[rnIndex].meSymbol = GetMapSymbolByClassification(pdata->mnType, formationLeader);
			mpMapView->maMapObj[rnIndex].meAffiliation = aeAffiliation;
			mpMapView->maMapObj[rnIndex].mfLon = po->mcKin.mfLon_rad;
			mpMapView->maMapObj[rnIndex].mfLat = po->mcKin.mfLat_rad;
			mpMapView->maMapObj[rnIndex].speed_kts = po->mcKin.mfSpeed_kts * cosf(po->mcKin.mfClimbAngle_rad);
			mpMapView->maMapObj[rnIndex].alt_m = po->mcKin.mfAlt_m;
			mpMapView->maMapObj[rnIndex].mnID = po->mnID;
			mpMapView->maMapObj[rnIndex].mnColor = 0;
            mpMapView->maMapObj[rnIndex].isStaleTrack = false;
            mpMapView->maMapObj[rnIndex].isDestroyed = false;
			mpMapView->maMapObj[rnIndex].useAltered = (!po->IsControlled()) && showFadedSymbols;
            mpMapView->maMapObj[rnIndex].errorPoly.clear();

            // dont show heading if in a steep dive (? this doesnt do this, 20080720)
			if ((mpMapView->maMapObj[rnIndex].meSymbol != SYMBOL_FIXED) &&
                (po->mcKin.mfSpeed_kts != 0))  //should enable negative speeds now?
			{
				mpMapView->maMapObj[rnIndex].mfHeading = po->mcKin.mfHeading_rad;
				mpMapView->maMapObj[rnIndex].mnFlags = TRACK_ALLVALID;
			}
			else
			{
				mpMapView->maMapObj[rnIndex].mnFlags = TRACK_ALLVALIDEXCEPTHEADING;
			}

            if ((mpOptions->drawNavPointsMode > 0) && (platform != 0) && (platform != mpHookedObj) && (platform->GetAlliance() == ownAlliance))
            {
                AddNavPoints(friendlyNavPoints, platform);
            }

            rnIndex++;
        }


		bool updateWorldMap = mpWorldMapView && mpWorldMapView->IsActive() && 
			mpWorldMapView->PointInView(point);
        if (updateWorldMap && bAllianceMatch && (rnWorldIdx < MAXWORLDMAPOBJ)) 
		{
            mpSS->mpDatabase->mcObjectData.Lookup(po->mnDBKey,pdata);
            mpWorldMapView->maMapObj[rnWorldIdx].mbExists = 1;
            mpWorldMapView->maMapObj[rnWorldIdx].mnColor = nColor;
            mpWorldMapView->maMapObj[rnWorldIdx].mfLon = po->mcKin.mfLon_rad;
            mpWorldMapView->maMapObj[rnWorldIdx].mfLat = po->mcKin.mfLat_rad;
            mpWorldMapView->maMapObj[rnWorldIdx].mnID = po->mnID;
			mpWorldMapView->maMapObj[rnWorldIdx].meAffiliation = aeAffiliation;
            rnWorldIdx++;
        }

    }

}

/**
* add mnAlliance's sensor data to view
*/
void tcGameView::AddSensorTracks(unsigned int anAlliance, int& rnIndex, int& rnWorldIdx, 
                                 double afStatusTime) 
{
    int nSize = mpSS->mcSensorMap.GetTrackCount(anAlliance);
    long poolpos = mpSS->mcSensorMap.GetStartTrackPosition(anAlliance);
    tcTrack *pTrack;
    tcTrack track;
    tcSensorMapTrack *pSMTrack;
    int i = 0;
    unsigned int nColor;

    // lon and lat extent thresholds for deciding whether or not to display errorPoly
    float lonThreshold = 0.02f * mpMapView->GetLonSpan();
    float latThreshold = 0.02f * mpMapView->GetLatSpan();

    while((i++<nSize)&&(rnIndex < MAXMAPOBJ))  
    {
        std::vector<tcPoint> errorPoly;

        mpSS->mcSensorMap.GetNextTrack(poolpos, pSMTrack, anAlliance);
        pTrack = (tcTrack*)pSMTrack;

        if ((pSMTrack->errorPoly.size() > 0) && ((pSMTrack->errorPolyLonWidth_rad >= lonThreshold) ||
            pSMTrack->errorPolyLatWidth_rad >= latThreshold))
        {
            errorPoly = pSMTrack->errorPoly;
        }

        if ((pTrack->mnFlags & (TRACK_BEARING_ONLY | TRACK_TRIANGULATED)) == 0) // normal case as of 2 SEP 2011
        {
            pTrack->GetPrediction(track, afStatusTime);
            mpMapView->maMapObj[rnIndex].mfHeading = track.mfHeading_rad;

            // adjust errorPoly for prediction as well
            float dlon_rad = track.mfLon_rad - pTrack->mfLon_rad;
            float dlat_rad = track.mfLat_rad - pTrack->mfLat_rad;
            size_t nPolyPoints = errorPoly.size();
            for (size_t n=0; n<nPolyPoints; n++)
            {
                errorPoly[n].x += dlon_rad;
                errorPoly[n].y += dlat_rad;
            }
        }
        else // never occurs any more ?
        {            
            track = *pTrack;
            //tcGameObject *pGameObj = 0; //mpSS->GetObject(pTrack->mnPassivePlatformID);
            //if (pGameObj != NULL) 
            //{
            //    track.mfLat_rad = (float)pGameObj->mcKin.mfLat_rad;
            //    track.mfLon_rad = (float)pGameObj->mcKin.mfLon_rad;
            //}
            mpMapView->maMapObj[rnIndex].mfHeading = track.mfHeading_rad; //(errorPoly.size() > 0) ? track.mfHeading_rad : track.bearing_rad;
        }

        mpMapView->maMapObj[rnIndex].mbExists = 1;
        mpMapView->maMapObj[rnIndex].mbFocus = 0;
        mpMapView->maMapObj[rnIndex].mnFlags = track.mnFlags;
        mpMapView->maMapObj[rnIndex].meSymbol 
            = GetMapSymbolByClassification(track.mnClassification);

		// don't show heading for tracks with zero speed (e.g. fixed ground)
        if (track.mfSpeed_kts == 0) 
		{
			mpMapView->maMapObj[rnIndex].mnFlags &= ~TRACK_HEADING_VALID;
		}

        tcAllianceInfo::Affiliation affil = GetMapSymbolAffiliation(track.mnAffiliation);

        mpMapView->maMapObj[rnIndex].meAffiliation = affil;
        mpMapView->maMapObj[rnIndex].mfLon = track.mfLon_rad;
        mpMapView->maMapObj[rnIndex].mfLat = track.mfLat_rad;
        mpMapView->maMapObj[rnIndex].mnID = track.mnID;
        mpMapView->maMapObj[rnIndex].speed_kts = track.mfSpeed_kts;
		mpMapView->maMapObj[rnIndex].mnColor = 0;
        mpMapView->maMapObj[rnIndex].isStaleTrack = pSMTrack->IsStale();
        mpMapView->maMapObj[rnIndex].isDestroyed = pSMTrack->IsDestroyed();
		mpMapView->maMapObj[rnIndex].useAltered = false;
        mpMapView->maMapObj[rnIndex].errorPoly = errorPoly;


		tcPoint point(track.mfLon_rad, track.mfLat_rad);

		bool updateWorldMap = mpWorldMapView && mpWorldMapView->IsActive() && 
			mpWorldMapView->PointInView(point);
        if (updateWorldMap && (rnWorldIdx < MAXWORLDMAPOBJ)) 
		{
			/*
			switch (affil) 
			{
			case UNKNOWN:
				nColor = 0xFFFFFF7F;
				break;
			case FRIENDLY:
				nColor = 0xFF7DDDFF;
				break;
			case NEUTRAL:
				nColor = 0xFFAAFFAA;
				break;
			case HOSTILE:
				nColor = 0xFFFF8080;
				break;
			}
			*/
			nColor = 0; // use zero to let mapview pick color

            mpWorldMapView->maMapObj[rnWorldIdx].mbExists = 1;
            mpWorldMapView->maMapObj[rnWorldIdx].mnColor = nColor;
            mpWorldMapView->maMapObj[rnWorldIdx].mfLon = track.mfLon_rad;
            mpWorldMapView->maMapObj[rnWorldIdx].mfLat = track.mfLat_rad;
            mpWorldMapView->maMapObj[rnWorldIdx].mnID = track.mnID;
			mpWorldMapView->maMapObj[rnWorldIdx].meAffiliation = affil;
            rnWorldIdx++;
        }

        rnIndex++;
    }
}

/******************************************************************************/
tcGameView::tcGameView() 
{
    mpSS = NULL;
    mpOptions = NULL;
    mpMapView = NULL;
    mpWorldMapView = NULL;
    mpObjectControl = NULL;
    mpScene = NULL;
    mbDisplayTracks = true;
    for(unsigned n=0;n<MAX_3D_OBJECTS;n++) {
        ma3DObjList[n].mnID = NULL_INDEX;
        ma3DObjList[n].mnSceneObjIdx = 0xFFFFFFFF;
    }
    mn3DObjCount = 0;

    /*
    mpDefaultObject = new tc3DObject;
    unknown_all_model = new tc3DObject;
    unknown_air_model = new tc3DObject;
    unknown_lsurf_model = new tc3DObject;
    unknown_ssurf_model = new tc3DObject;
    unknown_missile_model = new tc3DObject;

    mpDefaultObject->Load("3d\\type45edit.gc3");
    unknown_all_model->Load("3d\\unk_all.gc3");
    unknown_air_model->Load("3d\\air_small.gc3");
    unknown_lsurf_model->Load("3d\\surf_med.gc3");
    unknown_ssurf_model->Load("3d\\surf_small.gc3");
    unknown_missile_model->Load("3d\\unk_missile.gc3");
    */

    mfCamRange_m = 1000.0f;
    mfCamAz_deg = 0.0f;
    mfCamEl_deg = -30.0f;
    mbMouseLook = false;
    mbMouseZoom = false;

}
/******************************************************************************/
tcGameView::~tcGameView() 
{
#if 0
    if (mpDefaultObject != NULL) delete mpDefaultObject;
    if (unknown_all_model != NULL) delete unknown_all_model;
    if (unknown_air_model != NULL) delete unknown_air_model;
    if (unknown_lsurf_model != NULL) delete unknown_lsurf_model;
    if (unknown_ssurf_model != NULL) delete unknown_ssurf_model;
    if (unknown_missile_model != NULL) delete unknown_missile_model;
#endif
}
