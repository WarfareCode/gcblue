/**  
**  @file tcHookInfo.h
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


#ifndef _HOOKINFO_H_
#define _HOOKINFO_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "wx/wx.h" 
#include "tc3DWindow2.h"


class tcOptions;
class tcUserInfo;
class tcSimState;
class tcGameObject;
class tcSensorMapTrack;
class tcUnits;

namespace database 
{
    class tcDatabaseObject;
}



using namespace database;


class tcHookInfo : public tc3DWindow2 
{
public:
    void Draw();
    void DrawOwn(tcGameObject *pHookedObj);
    void DrawTrack(long anID);
    void AttachSimState(tcSimState *apSS) {mpSS=apSS;}
    void AttachOptions(tcOptions *apOptions) {mpOptions = apOptions;}
    void AttachUserInfo(tcUserInfo *apUserInfo) {mpUserInfo=apUserInfo;}
    void SetEngagedDrawMode(int mode) {drawEngagedMode = mode;}
    void SetHookID(long anID) {mnHookID=anID;}
    void OnLButtonDown(wxMouseEvent& event);
    void OnLeaveWindow(wxMouseEvent& event);

    tcHookInfo(wxWindow *parent, 
        const wxPoint& pos, const wxSize& size, 
        const wxString& name = "HookInfo",
		tc3DWindow2* graphicsHost = 0);
    virtual ~tcHookInfo();
private:
    int drawEngagedMode; ///< = 1 to draw engaged by class name and quantity, 0 for id's
    tcSimState *mpSS;  ///< pointer to SimState object to access hook info, change this
    ///< to a UserSimState reference when ready (state as known by user's side)
    tcOptions *mpOptions;
    tcUserInfo *mpUserInfo;
	tcDatabase* database;
    tcUnits* units;
    long mnHookID;
	unsigned int ambiguityIdx; ///< index to cycle display of large numbers of ambiguous platforms
	unsigned int lastCycleCount; ///< time of last update of cycle display


    void DrawTrackEngaged(const tcSensorMapTrack *smtrack, float& x, float& y);
    void GetFunctionalName(std::string& s, 
		tcDatabaseObject *apDBObject, tcGameObject *apGameObject);
    void GetObjectInfo(std::string& s, 
		tcDatabaseObject *apDBObject, tcGameObject *apGameObject);

};

#endif 
