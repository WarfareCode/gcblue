/** 
**  @file tcHookInfo.cpp
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

#include "stdwx.h"

#ifndef WX_PRECOMP
#include "wx/wx.h" 
#endif

#include <wx/string.h>

#include "tcHookInfo.h"
#include "aerror.h"
#include "math.h"
#include "tcSimState.h"
#include "tcOptions.h"
#include "tcUserInfo.h"
#include "commandlist.h"
#include "simmath.h"
#include "tcDatabase.h"
#include "tcTime.h"
#include "tcMissileObject.h"
#include "tv_types.h"
#include "tcUnits.h"
#include "ai/Brain.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif 


void tcHookInfo::OnLButtonDown(wxMouseEvent& event) 
{

}

void tcHookInfo::OnLeaveWindow(wxMouseEvent& event)
{
    event.Skip();
    event.ResumePropagation(2); // so edge map scroll works
}

/**
* Draw hook info display when track is hooked (vs. own-alliance platform)
*/
// This method needs to be broken up
void tcHookInfo::DrawTrack(long anID) 
{
    std::string s;
    char zBuff[128];
    float ftextx = 10.0f;
    float ftexty = 22.0f;
    UINT8 nOwnAlliance = mpUserInfo->GetOwnAlliance();
	Vec4 color;

    tcSensorMapTrack* pSMTrack = mpSS->mcSensorMap.GetSensorMapTrack(anID, nOwnAlliance);
    if (pSMTrack == 0) return;

    const tcTrack *pTrack = pSMTrack->GetTrack();
    // classification
    ClassificationToString(pTrack->mnClassification, zBuff);
	strcat(zBuff, " track");
	color.set(0.4f, 1.0f, 0.4f, 1.0f);
    
	if (!pSMTrack->IsIdentified())
	{
		DrawTextR(zBuff, ftextx-2.0f, ftexty, defaultFont.get(), 
			color, fontSizeLarge, LEFT_BASE_LINE);
		ftexty += 20.0f;
	}
	else // track is identified, look up class name
	{
		if (tcDatabaseObject* databaseObj = database->GetObject(pSMTrack->GetDatabaseId()))
		{
            s = databaseObj->GetDisplayName();
		}
		else // error, not found in database
		{
			s = "Error";
		}

		DrawTextR(s.c_str(), ftextx-2.0f, ftexty, 
			defaultFont.get(), color, fontSizeLarge, LEFT_BASE_LINE);
		ftexty += 15.0f;

		DrawTextR(zBuff, ftextx, ftexty, 
			defaultFont.get(), color, fontSize, LEFT_BASE_LINE);
		ftexty += 20.0f;
	}


    // speed, heading, altitude, terrain info
    s = "";
    if (pTrack->mnFlags & TRACK_HEADING_VALID) 
    {

        //if (heading_deg < 0) heading_deg += 360;

        if (pTrack->mnFlags & TRACK_BEARING_ONLY) 
        {
            int bearing_deg(C_180OVERPI*pTrack->bearing_rad + 0.5f);
            bearing_deg = bearing_deg + int(bearing_deg < 0)*360;
            sprintf(zBuff,"BRG %03d ", bearing_deg);
        }
        else 
        {       
            int heading_deg(C_180OVERPI*pTrack->mfHeading_rad + 0.5f);
            heading_deg = heading_deg + int(heading_deg < 0)*360;
            sprintf(zBuff,"HDG %03d ", heading_deg);
        }
        s += zBuff;
    }
    if (pTrack->mnFlags & TRACK_SPEED_VALID) 
    {
        sprintf(zBuff," SPD %s ", units->GetUserSpeedString(pTrack->mfSpeed_kts));
        s += zBuff;
    }
    if ((pTrack->mnClassification & (PTYPE_AIR | PTYPE_MISSILE))
        &&(pTrack->mnFlags & TRACK_ALT_VALID)) 
    {
        sprintf(zBuff," ALT %s", units->GetUserAltitudeString(pTrack->mfAlt_m));
        s += zBuff;
    }

	DrawTextR(s.c_str(), ftextx, ftexty, defaultFont.get(), color, fontSize, LEFT_BASE_LINE);
    ftexty += 15;

    // Draw reporting platform info
    size_t nContributors = pSMTrack->GetContributorCount();
    s = "Detected by: ";
    for (size_t k=0; k<nContributors; k++)
    {
        s += std::string(pSMTrack->GetContributorName(k));
        if (k < nContributors-1) s += ",";
    }
	if (s.size() > 35)
	{
		s = s.substr(0, 35);
	}

    DrawTextR(s.c_str(), ftextx, ftexty, defaultFont.get(), color, fontSize, LEFT_BASE_LINE);
    ftexty += 15;

    // Draw contact update time
    double t = mpSS->GetTime();
    float dt_s = float(t - pSMTrack->GetLastReportTime());
    int mm = int(floor((1.0/60.0)*dt_s));
    int ss = int(floor(dt_s - 60.0f*float(mm)));
    mm = std::min(mm, 99); // max at 99 for display
    tcDateTime dateTime = mpSS->GetDateTime();
    dateTime.AdjustTimeSeconds(-dt_s);
    wxString s2;
    s2.Printf("%s (-%02d:%02d)", dateTime.asStringTOD(), mm, ss);
    DrawTextR(s2.c_str(), ftextx, ftexty, defaultFont.get(), color, fontSize, LEFT_BASE_LINE);
    ftexty += 15;

    // Draw emitter info
    int nEmitters = pSMTrack->GetEmitterCount();
    if (nEmitters) 
    {
		DrawTextR("Emitters:", ftextx, ftexty, defaultFont.get(), color, fontSize, LEFT_BASE_LINE);
        ftexty+=15;
    }
    else 
    {
		DrawTextR("No emitters detected", ftextx, ftexty, defaultFont.get(), 
			color, fontSize, LEFT_BASE_LINE);
        ftexty += 15;
    }

    for (int n=0; n<nEmitters; n++) 
    {
        const EmitterInfo *pEmitterInfo = pSMTrack->GetEmitter(n);
        long nEmitterID = pEmitterInfo->mnEmitterID;
        tcDatabaseObject *pDBObj = mpSS->mpDatabase->GetObject(nEmitterID);
        if (pDBObj != NULL) 
        {
            strncpy(zBuff, pDBObj->mzClass.c_str(), 127);
        }
        else 
        {
            strcpy(zBuff,"Error");
        }
		DrawTextR(zBuff, ftextx + 3.0f, ftexty, defaultFont.get(), color, fontSize, LEFT_BASE_LINE);

        ftexty += 15;
    }

	ftexty += 5;

	/* Platform ambiguity list, update if at least one emitter
	** is detected, and detailed identification is not 
	** available */
	if ((nEmitters > 0) && (!pSMTrack->IsIdentified()))
	{
		unsigned nCandidates = pSMTrack->ambiguityList.size();
		if (nCandidates) 
		{
			sprintf(zBuff, "Ambiguity list (%d):", nCandidates);
			DrawTextR(zBuff, ftextx, ftexty, defaultFont.get(), color, fontSize, LEFT_BASE_LINE);
			ftexty+=15;
		}
		else 
		{
			DrawTextR("Ambiguity list not available", ftextx, ftexty, defaultFont.get(), 
				color, fontSize, LEFT_BASE_LINE);
			ftexty += 15;
		}

		unsigned int currentCount = tcTime::Get()->Get30HzCount();
		if (currentCount - lastCycleCount > 75) // 2.5 seconds
		{
			lastCycleCount = currentCount;
			if (nCandidates > 4)
			{
				ambiguityIdx += 4;
			}
		}
		if (ambiguityIdx >= nCandidates) ambiguityIdx = 0;

		for (unsigned int n=ambiguityIdx; (n < ambiguityIdx+4) && (n < nCandidates); n++) 
		{
			long candidateID = pSMTrack->ambiguityList[n];
			tcDatabaseObject* dbObj = mpSS->mpDatabase->GetObject(candidateID);
			if (dbObj) 
			{
				strncpy(zBuff, dbObj->mzClass.c_str(), 127);
			}
			else 
			{
				strcpy(zBuff, "Error");
			}
			DrawTextR(zBuff, ftextx + 3.0f, ftexty, defaultFont.get(), color, fontSize, LEFT_BASE_LINE);

			ftexty += 10;
		}

	}








    //*********** draw engagement info **************
    DrawTrackEngaged(pSMTrack, ftextx, ftexty);

}

/** 
* Draws list of weapons that have engaged track.
* For drawEngageMode = 0 draws a list of IDs, 
* for drawEngageMode = 1 draws class name and quantity
* x and y are start coordinates of drawing text. 
* x and y are modified by this method so that other 
* drawing methods can draw underneath.
*/
void tcHookInfo::DrawTrackEngaged(const tcSensorMapTrack *smtrack, float& x, float& y)
{
    wxSize textSize;
	Vec4 color(1, 0, 0, 1);

    int nEngaged = (int)smtrack->GetEngagedCount();
    if (nEngaged) 
    {
		DrawTextR("Engaged with:   ", x, y, defaultFont.get(), color, fontSize, LEFT_BASE_LINE);
        MeasureText(defaultFont.get(), fontSize, "Engaged with:   ", textSize);
    }

    if (drawEngagedMode == 0)
    {        
        x += float(textSize.GetWidth()) + 3.0f;
		wxString zBuff;
        for (int nE=0; nE<nEngaged; nE++)
        {
			zBuff += wxString::Format("%d ", smtrack->engaged[nE]);
			DrawTextR(zBuff.c_str(), x, y, defaultFont.get(), color, fontSize, LEFT_BASE_LINE);
			MeasureText(defaultFont.get(), fontSize, zBuff, textSize);
           
            x += float(textSize.GetWidth()) + 2.0f;
            if (x > (float) mnWidth - 10.0f)
            {
                x = 20.0f;
                y += 15;
            }
        }
        y+=15;
        return;
    }

    std::vector<long> classID;
    std::vector<unsigned> quantity;
    wxArrayString className;

    for (int nE=0;nE<nEngaged;nE++)
    {
        long id;
        wxString name;

        if (tcGameObject *obj = mpSS->GetObject(smtrack->engaged[nE]))
        {
            id = obj->mnDBKey;
            name = obj->mpDBObject->mzClass.c_str();

            bool matches = false;
            for(unsigned k=0;(k<classID.size())&&(!matches);k++)
            {
                if (classID[k] == id)
                {
                    matches = true;
                    quantity[k]++;
                }
            }
            if (!matches)
            {
                classID.push_back(id);
                quantity.push_back(1);
                className.Add(name);
            }
        }
        else
        {   
        }
       
    }

    y += 15;
    for (unsigned k=0; k<classID.size(); k++)
    {
		wxString zBuff;
		zBuff.Printf("   %s (%d)", className[k].ToAscii(), quantity[k]);
		DrawTextR(zBuff.c_str(), x, y, defaultFont.get(), color, fontSize, LEFT_BASE_LINE);
		MeasureText(defaultFont.get(), fontSize, zBuff, textSize);

        y += float(textSize.GetHeight()) + 2.0f;
    }

}

void tcHookInfo::DrawOwn(tcGameObject *pHookedObj) 
{

    std::string s;
    char zBuff[128];
    float ftextx = 10.0f;
    float ftexty = 22.0f;
	Vec4 color;

    if (pHookedObj == NULL) {return;}


    s = pHookedObj->mzUnit.c_str();
	color.set(0.4f, 1.0f, 0.4f, 1.0f);
	DrawTextR(s.c_str(), ftextx-2.0f, ftexty, defaultFont.get(), color, fontSizeLarge, LEFT_BASE_LINE,
        180.0f);
    ftexty += 20.0f;

    sprintf(zBuff, "%s (id %d)", pHookedObj->GetDisplayClassName(), pHookedObj->mnID);
    s = zBuff;
	DrawTextR(s.c_str(), ftextx, ftexty, defaultFont.get(), color, fontSize, LEFT_BASE_LINE);
    ftexty += 20.0f;

    /*** mnClassID, mnModelType, mnType (classification) ***/
    GetObjectInfo(s, pHookedObj->mpDBObject, pHookedObj);
	DrawTextR(s.c_str(), ftextx, ftexty, defaultFont.get(), color, fontSize, LEFT_BASE_LINE);
    ftexty += 15.0f;

    // speed, heading, altitude, terrain info
    tcKinematics *pkin = &pHookedObj->mcKin;
    
    int heading_deg = int(C_180OVERPI*pkin->mfHeading_rad + 0.5f);
    heading_deg = heading_deg + (int(heading_deg < 0) - int(heading_deg >= 360))*360;

    sprintf(zBuff,"%s, hdg %03d, alt %s",
        units->GetUserSpeedString(pkin->mfSpeed_kts), heading_deg, 
        units->GetUserAltitudeString(pkin->mfAlt_m));

    s = zBuff;
	DrawTextR(s.c_str(), ftextx, ftexty, defaultFont.get(), color, fontSize, LEFT_BASE_LINE);
    ftexty += 15;

    sprintf(zBuff, "Terrain %s", units->GetUserAltitudeString(pHookedObj->mcTerrain.mfHeight_m));
    s = zBuff;
	DrawTextR(s.c_str(), ftextx, ftexty, defaultFont.get(), color, fontSize, LEFT_BASE_LINE);
    ftexty+=15;

    // lat, lon
    LonLatToStringB(C_180OVERPI*(float)pkin->mfLon_rad,C_180OVERPI*(float)pkin->mfLat_rad,s);
	DrawTextR(s.c_str(), ftextx, ftexty, defaultFont.get(), color, fontSize, LEFT_BASE_LINE);
    ftexty += 15;

    /*** damage ***/
	float damageLevelPercent = 100.0f * pHookedObj->GetDamageLevel();
	if (damageLevelPercent > 100.0f) damageLevelPercent = 100.0f;

    if (damageLevelPercent == 0) 
    {
        strcpy(zBuff,"Damage: none");
    }
    else if (damageLevelPercent >= 50.0f) 
    {   
		color.set(1.0f, 0.4f, 0.4f, 1.0f);
        sprintf(zBuff, "Damage: %2.0f%%", damageLevelPercent);
    }
    else 
	{
		color.set(1.0f, 1.0f, 0.4f, 1.0f);
        sprintf(zBuff, "Damage: %2.0f%%", damageLevelPercent);
    }
    s = zBuff;
	DrawTextR(s.c_str(), ftextx, ftexty, defaultFont.get(), color, fontSize, LEFT_BASE_LINE);
    ftexty += 15;
	color.set(0.4f, 1.0f, 0.4f, 1.0f);


	// multiplayer info
	if (mpSS->IsMultiplayerActive())
	{
		const std::string& controller = pHookedObj->GetController();

		if (controller.size())
		{
			s = "Controlled by ";
			s += controller;
		}
		else
		{
			s = "No controller";
		}

		DrawTextR(s.c_str(), ftextx, ftexty, defaultFont.get(), color, fontSize, LEFT_BASE_LINE);
		ftexty += 15;
		color.set(0.4f, 1.0f, 0.4f, 1.0f);
	}
	

    // AI action text for platform objects
    tcPlatformObject* pPlatformObj = dynamic_cast<tcPlatformObject*>(pHookedObj);
    if (pPlatformObj != NULL) 
    {
        std::string text = pPlatformObj->GetBrain()->GetActionText();
        s = "Action: ";
        s += text;
		DrawTextR(s.c_str(), ftextx, ftexty, defaultFont.get(), color, fontSize, LEFT_BASE_LINE);
        ftexty += 15;
    }
    if (tcMissileObject* missile = dynamic_cast<tcMissileObject*>(pHookedObj))
    {
        sprintf(zBuff, "Runtime: %.1f", missile->RuntimeRemaining());

		DrawTextR(zBuff, ftextx, ftexty, defaultFont.get(), color, fontSize, LEFT_BASE_LINE);
        ftexty += 15;

        sprintf(zBuff, "Distance: %s", units->GetUserDistanceString(missile->GetDistanceFromLaunch()));

		DrawTextR(zBuff, ftextx, ftexty, defaultFont.get(), color, fontSize, LEFT_BASE_LINE);
        ftexty += 15;
        
    }

}

void tcHookInfo::Draw()
{
    static int nFrameCount = 0;

    wxASSERT(mpSS);

    //if ((nFrameCount++ % 4) != 0) return; // use to skip draw updates

    StartDraw();

    tcGameObject* pHookedObj;
    mpSS->GetPlatformState(mnHookID, pHookedObj);   

	bool drawTruth = (pHookedObj != 0) && (pHookedObj->IsOwnAlliance() || pHookedObj->IsEditMode());
    if (drawTruth)
	{
        DrawOwn(pHookedObj);
    }
    else 
	{
        // attempt to draw track if either null pHookedObj or different alliance
        DrawTrack(mnHookID); 
    }

	FinishDraw();
}


/**
* used for non-alliance track display
*/
void tcHookInfo::GetFunctionalName(std::string& s, tcDatabaseObject *apDBObject, tcGameObject *apGameObject)
{
    char zType[48];
    if (apDBObject == NULL) 
    {
        s = "NULL DBObject";
        return;
    }
    if (apGameObject == NULL) 
    {
        s = "NULL GameObject";
        return;
    }

    ClassificationToString(apDBObject->mnType,zType);

    s = zType;
}

/**
* TODO: This code duplicates similar code in tcObjectControl. Needs to be merged.
*/
void tcHookInfo::GetObjectInfo(std::string& s, tcDatabaseObject *apDBObject, tcGameObject *apGameObject) 
{
    char zClass[24], zModel[8], zType[8];
    if (apDBObject == NULL) 
    {
        s = "NULL DBObject";
        return;
    }
    if (apGameObject == NULL) 
    {
        s = "NULL GameObject";
        return;
    }

    std::string databaseClass = apDBObject->GetClassName();

    strcpy_s(zClass, 24, databaseClass.c_str());

	switch (apGameObject->mnModelType) 
	{
	case MTYPE_SURFACE:
		strcpy(zModel,"SUR");
		break;
	case MTYPE_CARRIER:
		strcpy(zModel,"CV");
		break;
	case MTYPE_MISSILE:
		strcpy(zModel,"MIS");
		break;
	case MTYPE_OBJECT:
		strcpy(zModel,"OBJ");
		break;
	case MTYPE_AIR:
		strcpy(zModel,"AIR");
		break;
	case MTYPE_FIXEDWING:
		strcpy(zModel,"FWAIR");
		break;
	case MTYPE_FIXEDWINGX:
		strcpy(zModel,"FXAIR");
		break;
	case MTYPE_HELO:
		strcpy(zModel,"HELO");
		break;
	case MTYPE_BALLISTIC:
		strcpy(zModel,"BAL");
		break;
	case MTYPE_AIRFIELD:
		strcpy(zModel,"FIELD");
		break;
	case MTYPE_SUBMARINE:
		strcpy(zModel,"SUB");
		break;
	case MTYPE_TORPEDO:
		strcpy(zModel, "TOR");
		break;
	case MTYPE_FIXED:
		strcpy(zModel, "GND");
		break;
	default:
		strcpy(zModel,"UNK");
		break;
	}

	switch (apDBObject->mnType) // classification type
	{ 
	case PTYPE_UNKNOWN:
		strcpy(zType,"UNK");
		break;
	case PTYPE_SURFACE:
		strcpy(zType,"USURF");
		break;
	case PTYPE_SMALLSURFACE:
		strcpy(zType,"SSURF");
		break;
	case PTYPE_LARGESURFACE:
		strcpy(zType,"LSURF");
		break;
	case PTYPE_CARRIER:
		strcpy(zType,"CV");
		break;
	case PTYPE_AIR:
		strcpy(zType,"UAIR");
		break;
	case PTYPE_FIXEDWING:
		strcpy(zType,"FWAIR");
		break;
	case PTYPE_MISSILE:
		strcpy(zType,"MIS");
		break;
	case PTYPE_HELO:
		strcpy(zType,"HELO");
		break;
	case PTYPE_SUBSURFACE:
		strcpy(zType,"USUB");
		break;
	case PTYPE_SUBMARINE:
		strcpy(zType,"SUB");
		break;
	case PTYPE_TORPEDO:
		strcpy(zType,"TORP");
		break;
	case PTYPE_GROUND:
		strcpy(zType,"LAND");
		break;
	case PTYPE_BALLISTIC:
		strcpy(zType,"BAL");
		break;
	default:
		strcpy(zType,"ERR");
		break;
	}

	char zBuff[128];
	sprintf(zBuff,"%s %s %s",zClass,zModel,zType);
	s = zBuff;
}




//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

tcHookInfo::tcHookInfo(wxWindow *parent, 
                       const wxPoint& pos, const wxSize& size, 
                       const wxString& name,
					   tc3DWindow2* graphicsHost) :
	tc3DWindow2(parent, pos, size, name, graphicsHost),
    mnHookID(NULL_INDEX),
    mpSS(0),
    mpOptions(0),
	database(tcDatabase::Get()),
    mpUserInfo(0),
    drawEngagedMode(1),
	ambiguityIdx(0),
	lastCycleCount(0),
    units(tcUnits::Get())
{
    SetBorderDraw(true);
}
/***********************************************************************************/
tcHookInfo::~tcHookInfo() 
{

}
