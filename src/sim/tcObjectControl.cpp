/**
**  @file tcObjectControl.cpp
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

#include "tcObjectControl.h"

#include "ai/Brain.h"
#include "ai/Nav.h"
#include "tcAeroAirObject.h"
#include "tcJetDBObject.h"
#include "tcAltitudeBarControl.h"
#include "tcBallisticDBObject.h"
#include "tcCounterMeasureDBObject.h"
#include "tcCommandQueue.h"
#include "tcControl.h"
#include "tcDatabase.h"
#include "tcLauncher.h"
#include "tcLauncherPopup.h"
#include "tcMessageInterface.h"
#include "tcMissileObject.h"
#include "tcOptions.h"
#include "tcPopupText.h"
#include "tcSimState.h"
#include "tcSound.h"
#include "tcSubObject.h"
#include "tcSubDBObject.h"
#include "tcTime.h"
#include "tcTorpedoDBObject.h"
#include "tcTorpedoObject.h"
#include "tcUserInfo.h"
#include "tcUnits.h"
#include "tcButton.h"
#include "tcGeometry.h"
#include "tcTVEngine.h"
#include "tcPlatformInterface.h" // for GetDeveloperMode call
#include "tcPlatformObject.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


BEGIN_EVENT_TABLE(tcObjectControl, tc3DWindow2)
	EVT_COMMAND(99, wxEVT_COMMAND_BUTTON_CLICKED, tcObjectControl::OnCycleGroupLeftCommand)
	EVT_COMMAND(101, wxEVT_COMMAND_BUTTON_CLICKED, tcObjectControl::OnCycleGroupRightCommand)
END_EVENT_TABLE()


using namespace ai;
using namespace database;



/******************* tcButtonPanel ************************/
#define BPTYPE_WEAPON 0
#define BPTYPE_SENSOR 1

void tcButtonPanel::Init(int anPanelType) 
{
    float fx,fy;
    float fbuttonheight = 15.0f;
    float fbarspacing = 18.0f;
    float fbuttonspacing = 2.0f;
    float afwidth[N_PANELBUTTONS] = {100.0f,22.0f,15.0f,20.0f,48.0f,10.0f,10.0f,10.0f};

    switch (anPanelType) 
    {
    case 0: // weapon control 
        mfxloc = 200.0f;
        mfyloc = panely;
        mnColumns = 3;
        for(int i=0;i<MAX_PANELROWS;i++) 
        {
            mastrCaption[i][2] = "P";
            mastrCaption[i][3] = "FC";
            mastrCaption[i][4] = "L-AUT";
        }
        mstrTitle = "MOUNT STATUS";
        break;
    case 1: // sensor
        mfxloc = 370.0f;
        mfyloc = panely;
        mnColumns = 2;
        mstrTitle = "SENSOR STATUS";
        break;
    default:
        return; // error, bad anPanelType
        break;
    }

    for (int i=0;i<MAX_PANELROWS;i++) 
    {
        fx = mfxloc;
        fy = mfyloc + fbarspacing + (i % MAX_ROWS_PER_PAGE) * fbarspacing;

        for (int j=0;j<N_PANELBUTTONS;j++) 
        {
            tcRect r;
			r.Set(fx, fx + afwidth[j], fy, fy + fbuttonheight);
            mar[i][j] = r;
            fx += afwidth[j] + fbuttonspacing;
        }
    }
}

void tcButtonPanel::Draw(tc3DWindow2* context) 
{
    unsigned int i, j;

	wxASSERT(context);

	Vec4 textColor(0.8f, 1.0f, 0.8f, 1.0f);
	Vec4 lineColor(0.4f, 1.0f, 0.4f, 1.0f);
   
	tcFont* font = context->GetDefaultFont();

	
	context->DrawTextR(mstrTitle.GetBuffer(), mar[0][0].left, mfyloc + 15.0f, 
		font, textColor, fontSize, tc3DWindow2::LEFT_BASE_LINE);


    if (mnRows > 0)
	{
        size_t bottomRowIdx = (mnRows < MAX_ROWS_PER_PAGE) ? mnRows : MAX_ROWS_PER_PAGE;
		float width = mar[0][mnColumns-1].GetRight()- mar[0][0].left + 10.0f;
		float height =  mar[bottomRowIdx-1][0].GetTop()- mfyloc + 5.0f;
		context->DrawRectangleR(mar[0][0].left - 5.0f, mfyloc, width, height, 
			lineColor, tc3DWindow2::FILL_OFF);
    }
    else 
	{
		context->DrawTextR( "--- none available ---", mar[0][0].left, mfyloc + 30.0f, 
			font, textColor, fontSize, tc3DWindow2::LEFT_BASE_LINE);

		float width = mar[0][mnColumns-1].GetRight() - mar[0][0].left + 10.0f;
		float height =  mar[0][0].GetBottom() - mfyloc + 20.0f;
		context->DrawRectangleR(mar[0][0].left - 5.0f, mfyloc, width, height, 
			lineColor, tc3DWindow2::FILL_OFF);
    }

    DrawPageSelect(context);


    unsigned int row_start = currentPage * MAX_ROWS_PER_PAGE;
    unsigned int row_stop = row_start + MAX_ROWS_PER_PAGE;
    if (row_stop > mnRows) row_stop = mnRows;
    wxASSERT(row_start <= row_stop);
    
    for (i=row_start; i<row_stop; i++) 
	{
        for (j=0; j<mnColumns; j++) 
		{
			bool isMouseOver = (i==mouseOverRow) && (j==mouseOverColumn);

            DrawButton(context, mar[i][j], mastrCaption[i][j].GetBuffer(), maButtonState[i][j], isMouseOver);
        }
    }
}

void tcButtonPanel::DrawButton(tc3DWindow2* context, const tcRect& rectf, 
                               const char* azCaption, teButtonState aeState, bool isMouseOver) 
{
    wxSize size;
    float ftextx, ftexty;

	Vec4 textColor;
	Vec4 backgroundColor;
	tcFont* font = context->GetDefaultFont();
    unsigned int blinkCount = tcTime::Get()->Get30HzCount();

	switch (aeState) 
	{
    case BS_READY:
		textColor.set(1, 1, 1, 1);
        backgroundColor.set(0.3f, 0.6f, 0.3f, 1.0f);
        break;
	case BS_ACTIVE:
		textColor.set(1, 1, 1, 1);
        backgroundColor.set(0.2f, 0.44f, 0.2f, 1.0f);
		break;
	case BS_READYING:
        textColor.set(0, 1, 1, 1);
        backgroundColor.set(0.2f, 0.44f, 0.2f, 1.0f);
        break;
    case BS_LOADING:
        textColor.set(1, 1, 1, 1);
        backgroundColor.set(0.44f, 0.5f, 0.4f, 1.0f);
        // blink button if loading
        if (blinkCount % 30 < 15)
        {
            backgroundColor.set(0.5*backgroundColor.x, 0.5*backgroundColor.y, 
                0.5*backgroundColor.z, backgroundColor.w);
        }
        break;
    case BS_DISABLED:
        backgroundColor.set(0.44f, 0.5f, 0.4f, 1.0f);
		textColor.set(0.13f, 0.13f, 0.13f, 1.0f);
		break;
    case BS_WARN:
		textColor.set(1, 1, 1, 1);
        backgroundColor.set(0.5f, 0.6f, 0.3f, 1.0f);
        break;
    case BS_RWRWARN1:
        textColor.set(1, 1, 1, 1);
        backgroundColor.set(0.2f, 0.44f, 0.2f, 1.0f);
        if (blinkCount % 30 < 15)
        {
            backgroundColor.set(0.5f, 0.6f, 0.3f, 1.0f);
        }
        break;
    case BS_RWRWARN2:
        textColor.set(1, 1, 1, 1);
        backgroundColor.set(0.2f, 0.44f, 0.2f, 1.0f);
        if (blinkCount % 30 < 15)
        {
            backgroundColor.set(0.5f, 0.2f, 0.2f, 1.0f);
        }
        break;
    default: // BS_DAMAGED
		textColor.set(0.8f, 0.8f, 0.8f, 1);
        backgroundColor.set(0.44f, 0.2f, 0.2f, 1.0f);
		break;
	}


   

	context->DrawRectangleR(rectf, backgroundColor, tc3DWindow2::FILL_ON);

	if (isMouseOver)
	{
		context->DrawRectangleR(rectf, Vec4(1, 1, 1, 1), tc3DWindow2::FILL_OFF);
	}

    // get size of caption text
	context->MeasureText(font, fontSize, azCaption, size);

	ftextx = 1.0f + rectf.left + 0.5f * (rectf.Width() - float(size.GetWidth()));
    ftexty = rectf.top - 0.5f * (rectf.Height() - float(size.GetHeight()));
	context->DrawTextR(azCaption, ftextx, ftexty, 
			font, textColor, fontSize, tc3DWindow2::LEFT_BASE_LINE);
}

/**
* Draw icons to switch between pages (if panel has multiple pages)
*/
void tcButtonPanel::DrawPageSelect(tc3DWindow2* context)
{
    if (nPages <= 1) return; // don't draw anything for one page

    Vec4 color(0.7f, 0.7f, 0.7f, 0.7f);

    float x = 88.0f + mar[0][0].left;
    float y = mar[0][0].bottom - 13.0f;
    float w = 6.0f;

    pageSelectBoxes.clear();

    for (unsigned int n=0; n<nPages; n++)
    {
        tcRect r(x, x+w, y, y+w);
        pageSelectBoxes.push_back(r);

        int fillMode = (n == currentPage) ? tc3DWindow2::FILL_ON : tc3DWindow2::FILL_OFF;
        context->DrawRectangleR(r, color, fillMode);

        x += w + 2.0f;
    }

}

/**
* For multiple page panel, check if point is within a page select
* box. If so, then switch page.
*/
void tcButtonPanel::UpdatePageSelect(const wxPoint& point)
{
    if (nPages <= 1) return;

    float x = float(point.x);
    float y = float(point.y);

    for (size_t k=0; k<pageSelectBoxes.size(); k++)
    {
        if (pageSelectBoxes[k].ContainsPoint(x, y))
        {
            SetPage(k);
            return;
        }
    }
}

bool tcButtonPanel::ButtonContainingPoint(const wxPoint& point, int& rnRow, int& rnColumn) 
{
    unsigned int i,j;
    tcRect rectPanel;
    tcRect* pr;
    wxRealPoint pointf;

    if ((mnRows == 0) || (mnColumns ==0)) {return false;}

    unsigned int maxRowsShown = std::min(mnRows, (unsigned int)MAX_ROWS_PER_PAGE);

    rectPanel.left = mar[0][0].left;
    rectPanel.bottom = mar[0][0].bottom;
    rectPanel.right = mar[0][mnColumns-1].GetRight();
    rectPanel.top = mar[maxRowsShown-1][0].GetTop();

    pointf.x= (float)point.x;
    pointf.y = (float)point.y;
    if (!rectPanel.ContainsPoint(pointf.x, pointf.y)) {return false;}

    rnRow = 0;
    rnColumn = 0;

    unsigned int row_start = currentPage * MAX_ROWS_PER_PAGE;
    unsigned int row_stop = row_start + MAX_ROWS_PER_PAGE;
    if (row_stop > mnRows) row_stop = mnRows;
    wxASSERT(row_start < row_stop);
    
    for (i=row_start; i<row_stop; i++) 
    {
        for(j=0; j<mnColumns; j++) 
        {
            pr = &mar[i][j];
            if (pr->ContainsPoint(pointf.x, pointf.y)) 
            {
                rnRow = i;
                rnColumn = j;
                return true;
            }
        }
    }
    return false;
}

void tcButtonPanel::GetRect(tcRect& r) 
{
    r.left = mar[0][0].left - 5.0f;
    r.bottom = mfyloc;
	r.right = r.left + mar[0][mnColumns-1].GetRight()- mar[0][0].left + 10.0f;
    if (mnRows > 0) 
    {
		r.top = r.bottom + mar[mnRows-1][0].GetBottom()- mfyloc + 5.0f;
    }
    else 
    {
		r.top = r.bottom + mar[0][0].GetBottom() - mfyloc + 5.0f;
    }
}
/******************************************************************************/
void tcButtonPanel::SetCaption(const char *caption, unsigned row, unsigned button) 
{
    if (row >= mnRows) {return;}
    if (button >= mnColumns) {return;}

    char buff[32];
    strncpy(buff, caption, 31);

    // limit string size
    int nCaptionLength = (int)strlen(caption);
    const int nMaxLength = 16;
    if (nCaptionLength > nMaxLength) 
    {
        buff[nMaxLength-3] = '.';
        buff[nMaxLength-2] = '.';
        buff[nMaxLength-1] = '.';
        buff[nMaxLength] = 0;
    }
    mastrCaption[row][button] = buff;
}

/**
* Version that uses MeasureText for accurate sizing
*/
void tcButtonPanel::SetCaptionB(tc3DWindow2* context, const char* caption, unsigned row, unsigned button) 
{
    if ((row >= mnRows)||(row >= MAX_PANELROWS)) {return;}
    if (button >= mnColumns) {return;}

    wxString s(caption);

    tcFont* font = context->GetDefaultFont();
    wxSize ellipsisSize;
    wxSize size;

    context->MeasureText(font, fontSize, "...", ellipsisSize);


    context->MeasureText(font, fontSize, s.c_str(), size);
    tcRect r = mar[row][button];

    float baseSize = r.Width() - 2.0f;
    size_t nTruncate = 2;
    while (float(size.GetWidth()) >= baseSize)
    {
        s = caption;
        s.RemoveLast(nTruncate);
        s += "...";

        context->MeasureText(font, fontSize, s.c_str(), size);
        nTruncate++;
    }

    mastrCaption[row][button] = s.c_str();
}

void tcButtonPanel::SetMouseOver(int row, int column)
{
	mouseOverRow = row;
	mouseOverColumn = column;
}

void tcButtonPanel::SetNumCols(size_t n)
{
    mnColumns = n;
}

void tcButtonPanel::SetNumRows(size_t n)
{
    mnRows = n;
    if (mnRows > 0)
    {
        /* with MAX_ROWS_PER_PAGE = 8
        ** 1 row = 1 page
        ** 8 rows = 1 page
        ** 9 rows = 2 pages
        ** 16 rows = 2 pages
        */
        nPages = ((mnRows - 1) / MAX_ROWS_PER_PAGE) + 1;
    }
    else
    {
        nPages = 1;
    }
}

void tcButtonPanel::SetPage(unsigned int page)
{
    currentPage = page;
    if (currentPage >= nPages)
    {
        currentPage = nPages - 1;
        wxASSERT(false);
    }
}

/******************************************************************************/
tcButtonPanel::tcButtonPanel()
: currentPage(0),
  nPages(1),
  panely(23.0f),
  mouseOverRow(-1),
  mouseOverColumn(-1)
{
    float fx,fy;
    float fbuttonheight = 15.0f;
    float fbarspacing = 18.0f;
    float fbuttonspacing = 2.0f;
    mfxloc = 50.0f;
    mfyloc = 50.0f;
    mnRows = 0;
    mnColumns = 0;
	fontSize = 11.0f;

    float afwidth[N_PANELBUTTONS] = {10.0f,10.0f,10.0f,10.0f,10.0f,10.0f,10.0f,10.0f};
    fy = mfyloc;
    for (int i=0; i<MAX_PANELROWS; i++) 
	{
        fx = mfxloc;
        for(int j=0; j<N_PANELBUTTONS; j++) 
		{
            tcRect r;
			r.Set(fx, fx + afwidth[j], fy, fy + fbuttonheight);
            mar[i][j] = r;
            maButtonState[i][j] = BS_DISABLED;
            fx += afwidth[j] + fbuttonspacing;
            mastrCaption[i][j] = "X";
        }
        fy += fbarspacing;
    }
}

tcButtonPanel::~tcButtonPanel() 
{

}

/**
* Creates osg::Geometry objects used for heading control
*/
void tcObjectControl::CreateHeadingCircles()
{
	Vec4 opaqueWhite(1, 1, 1, 1);
	Vec4 transparentWhite(1, 1, 1, 0.2f);

    headingCircle = CreatePieGeometry(msHOI.mrectArc.Width(), msHOI.mrectArc.Height(),
		-180, 180, opaqueWhite, FILL_OFF);

	headingCircleLight = CreatePieGeometry(msHOI.mrectArc.Width(), msHOI.mrectArc.Height(),
		-180, 180, transparentWhite, FILL_ON);
}

void tcObjectControl::CycleGroupHook(bool forward)
{
    int groupSize = hookedGroup.size();

    if (groupSize < 2) return;

    long nextId = mnHookID;
    bool searching = true;
    for (int n=0; (n<groupSize) && searching; n++)
    {
        if (hookedGroup[n] == mnHookID)
        {
            int nextIdx = forward ? (n + 1) : (n - 1);

            if (nextIdx >= groupSize) nextIdx = 0;
            else if (nextIdx < 0) nextIdx = groupSize-1;
                
            nextId = hookedGroup[nextIdx];
            searching = false;
        }
    }

    SetHookIDgroup(nextId);
}


void tcObjectControl::Draw() 
{
    static int nFrameCount = 0;

    int bFound;
    tcString s;

    //if (GetUseRenderSurface() && ((nFrameCount++ % 3) != 0)) 
    //{
    //    return;
    //}

    StartDraw();


	wxASSERT(simState);

    if (mnHookID != NULL_INDEX) 
    {
        bFound = simState->GetPlatformState(mnHookID, mpHookedGameObj);   
    }
    else 
    {
        bFound = 0;
        mpHookedGameObj = 0;
    }

    //UpdateSymbolList(); // now called in Game::UpdateFrame loop to avoid out of sync jitter when zoomed way in on tac map
    if ((!bFound) || (mpHookedGameObj==0)) 
    {
        FinishDraw();
        return;
    }

    bool isMultiplayerObserver = (tcUserInfo::Get()->GetOwnAlliance() == 0) || simState->IsMultiplayerServer();

    bool drawObjectControl = mpHookedGameObj->IsOwnAlliance() || 
        ((mpOptions->mnCommandMode == 0) && tcPlatformInterface::GetDeveloperMode()) ||
		mpHookedGameObj->IsEditMode() || isMultiplayerObserver;

    if (!drawObjectControl)
    {
        FinishDraw();
        return;
    }

    // update relevant control object info on hook change
    if (mnHookID != mnPreviousHookID) 
    {
        UpdateControlObjects();
        UpdateSymbolList();
        mnPreviousHookID = mnHookID;
    }



    tcPlatformObject* platformObj = dynamic_cast<tcPlatformObject*>(mpHookedGameObj);
    bool inFormation = false;
    bool isLeader = false;
    if (platformObj != 0)
    {
        inFormation = platformObj->formation.isActive;
        isLeader = platformObj->formation.IsLeader();
    }


    s = mpHookedGameObj->mzUnit.c_str();

    float ftextx = 10.0f;
    float ftexty = 22.0f;

    /*** draw text ***/
	Vec4 color(0.4f, 1.0f, 0.4f, 1.0f);

    DrawTextR(s.GetBuffer(), ftextx, ftexty, 
              defaultFont.get(), color, fontSizeLarge, LEFT_BASE_LINE, 180.0f);
    ftexty += 2;

    // draw country flag
    countryFlagRect.Set(146.0f, 182.0f, 3.0f+ftexty, 27.0f+ftexty);
    DrawImageR(mpHookedGameObj->GetEnsign(), 146.0f, 3.0f+ftexty, 36.0f, 24.0f);




    // if in formation, draw formation flag
    if (inFormation)
    {
        formationFlagRect.Set(146.0f, 182.0f, 30.0f+ftexty, 54.0f+ftexty);
        if (isLeader)
        {
            DrawImageR(leaderFlag.get(), 146.0f, 30.0f+ftexty, 36, 24);
        }
        else
        {
            DrawImageR(followerFlag.get(), 146.0f, 30.0f+ftexty, 36, 24);
        }
    }
    else
    {
        formationFlagRect.Set(0, 0, 0, 0);
    }

	DrawLineR(ftextx, ftexty, ftextx+175.0f, ftexty, color);

    ftexty += 14;

    s.Format("%s", mpHookedGameObj->GetDisplayClassName());
	DrawTextR(s.GetBuffer(), ftextx, ftexty, 
			defaultFont.get(), color, fontSize, LEFT_BASE_LINE);
    ftexty += 10;

    /*** speed, heading, altitude, terrain info  ***/
    tcKinematics *pkin = &mpHookedGameObj->mcKin;

    s.Format("%s, hdg %03.0f, alt %s", units->GetUserSpeedString(pkin->mfSpeed_kts),
        C_180OVERPI*pkin->mfHeading_rad, units->GetUserAltitudeString(pkin->mfAlt_m));



	DrawTextR(s.GetBuffer(), ftextx, ftexty, 
			defaultFont.get(), color, fontSize, LEFT_BASE_LINE);
    ftexty += 12;

    if (mpHookedGameObj->GetDamageLevel() <= 0)
    {
        s.Format("Terrain %s", units->GetUserAltitudeString(mpHookedGameObj->mcTerrain.mfHeight_m));
    }
    else
    {
         s.Format("Terrain %s DMG %.0f%%", units->GetUserAltitudeString(mpHookedGameObj->mcTerrain.mfHeight_m),
             100.0f*mpHookedGameObj->GetDamageLevel());
    }
	DrawTextR(s.GetBuffer(), ftextx, ftexty, 
			defaultFont.get(), color, fontSize, LEFT_BASE_LINE);
    ftexty += 12;

    // lat, lon
    LonLatToString(C_180OVERPI*(float)pkin->mfLon_rad, C_180OVERPI*(float)pkin->mfLat_rad, s);
	DrawTextR(s.GetBuffer(), ftextx, ftexty, 
			defaultFont.get(), color, fontSize, LEFT_BASE_LINE);
    ftexty += 12;



    // goal parameters (guidance) -- does not apply to all object types
    float mfGoalHeading_rad = pkin->mfHeading_rad;
    float mfGoalSpeed_kts = pkin->mfSpeed_kts;
    float mfGoalAlt_m = pkin->mfAlt_m;

    // intercept data for missiles
    if (mpHookedGameObj->mnModelType == MTYPE_MISSILE) 
    {
        tsGuidanceParameters gp;
        tcMissileObject* pMissileObj = dynamic_cast<tcMissileObject*>(mpHookedGameObj);

        if(pMissileObj != NULL) 
        {
            bool bSeekerTrack = (pMissileObj->GetGuidanceParameters(gp) == 1);
            if ((!bSeekerTrack)||(gp.mfInterceptTime > 3600.0f)) {
                s.Format("TTI: ----");
            }
            else {
                s.Format("TTI: %3.1f",gp.mfInterceptTime);
            }
            mfGoalHeading_rad = pMissileObj->goalHeading_rad;

			DrawTextR(s.GetBuffer(), ftextx, ftexty, 
				defaultFont.get(), color, fontSize, LEFT_BASE_LINE);
            ftexty += 12;
        }

        s.Format("Climb angle: %3.2f", mpHookedGameObj->mcKin.mfClimbAngle_rad*C_180OVERPI);

		DrawTextR(s.GetBuffer(), ftextx, ftexty, 
			defaultFont.get(), color, fontSize, LEFT_BASE_LINE);
        ftexty += 12;
    }

#ifdef _DEBUG
    if (tcPlatformObject* platform = dynamic_cast<tcPlatformObject*>(mpHookedGameObj))
    {
        const Brain* platformBrain = platform->GetBrain();
        const Brain* aiBrain = mcAIPanel.GetAIData();
        wxASSERT(platformBrain == aiBrain);
    }
#endif

    mcAIPanel.Draw((tc3DWindow2*)this);


    if (platformObj != 0) 
    {
        mfGoalHeading_rad = platformObj->mcGS.mfGoalHeading_rad;
        if (tcAeroAirObject* aaObj = dynamic_cast<tcAeroAirObject*>(platformObj))
        {
            // TODO fix this, this is a hack to get the throttle fraction to be displayed
            mfGoalSpeed_kts = aaObj->GetThrottleFraction() * aaObj->mpDBObject->mfMaxSpeed_kts; // crashed here
        }
        else
        {
            mfGoalSpeed_kts = platformObj->mcGS.mfGoalSpeed_kts;
        }
        mfGoalAlt_m = platformObj->mcGS.mfGoalAltitude_m;
    }


    DrawHeadingObject(&msHOI, pkin->mfHeading_rad, mfGoalHeading_rad); // object heading

    // test code Nov2008
 //   tcRect testRect(10.0f, 100.0f, 20.0f, 200.0f);
	//Vec4 testColor(0.1f, 0.25f, 0.1f, 1.0f);
 //   DrawRectangleR(testRect, testColor, FILL_OFF);
 //   FinishDraw();
 //   return;
    // end test code Nov2008

    bool mbSurface = (mpHookedGameObj->mnModelType == MTYPE_SURFACE) || 
		(mpHookedGameObj->mnModelType == MTYPE_CARRIER);

    bool mbAir = (mpHookedGameObj->mnModelType == MTYPE_FIXEDWING) || 
		(mpHookedGameObj->mnModelType == MTYPE_FIXEDWINGX) ||
		(mpHookedGameObj->mnModelType == MTYPE_HELO);

    bool isGroundVehicle = mpHookedGameObj->mnModelType == MTYPE_GROUNDVEHICLE;

    //bool isFixed = (mpHookedGameObj->mnModelType == MTYPE_FIXED) || 
    //    (mpHookedGameObj->mnModelType == MTYPE_AIRFIELD);

    tcSubObject* sub = dynamic_cast<tcSubObject*>(platformObj);
	bool isSub = sub != 0;

    bool nonZeroMaxSpeed = (platformObj != 0) && (platformObj->mpDBObject->mfMaxSpeed_kts > 0);

    bool mbDrawSpeed = (mbSurface || mbAir || isSub || isGroundVehicle) && nonZeroMaxSpeed;

//    bool mbDrawEngagement = mbSurface;

    if (mbDrawSpeed) 
    {
        if (sub == 0)
        {
            DrawBarObject(&msSOI, units->UserSpeedUnits(pkin->mfSpeed_kts), units->UserSpeedUnits(mfGoalSpeed_kts), 0);
        }
        else
        {
            float maxQuietSpeed_kts = sub->GetMaxQuietSpeedKts();
            DrawBarObject(&msSOI, units->UserSpeedUnits(pkin->mfSpeed_kts), units->UserSpeedUnits(mfGoalSpeed_kts), maxQuietSpeed_kts);
        }
    } 

    //if (mbDrawEngagement) {DrawEngagementInfo(pGraphics);}

    DrawFireControl();   // draw weapon control interface
    DrawSensorControl();
    DrawLandingInfo();


	bool drawFuel = (sub == 0) || (sub->IsDieselElectric());
    if (drawFuel) // have to update this for DE subs
	{
		DrawFuelInfo();
	}
	
	if (isSub)
	{
		if (sub->mpDBObject->IsCavitatingKts(pkin->mfSpeed_kts, -pkin->mfAlt_m))
		{
			const Vec4 color(1.0f, 0.6f, 0.6f, 1.0f);
			bool blinkOn = (tcTime::Get()->Get30HzCount() % 30 > 15);
			if (blinkOn)
			{
				ftextx = msSOI.mrectbar.GetLeft();
				ftexty = msSOI.mrectbar.GetBottom() - 3.0f;
				DrawTextR("CAVITATING", ftextx, ftexty, 
					defaultFont.get(), color, fontSize, LEFT_BASE_LINE);
			}
		}
	}

	UpdateHint();

    DrawControls();

#ifdef _DEBUG
    if ((mpHookedGameObj != 0) && (mpHookedGameObj->targeters.size() > 0))
    {
        wxString targeterList("Targeted by ");

        for (size_t n=0; n<mpHookedGameObj->targeters.size(); n++)
        {
            targeterList += wxString::Format("%d ", mpHookedGameObj->targeters[n]);
        }
        DrawTextR(targeterList.c_str(), 400.0f, 180.0f, 
					defaultFont.get(), color, fontSize, LEFT_BASE_LINE);

    }
#endif

    FinishDraw();
}



void tcObjectControl::DrawTest() 
{
    StartDraw();

    if (headingCircle.get() == 0)
    {
        CreateHeadingCircles();
    }
    DrawGeometryR(headingCircle.get(), 66.0f, 75.0f);
    DrawGeometryR(headingCircleLight.get(), 67.0f, 80.0f);

    

    float x = sinf(1.0f) + cosf(msHOI.mfradius);
    //float w = 1.5 + x;

    for (size_t k=0; k<200; k++)
    {
        DrawTextR("BLAH", float(k)*0.1f, 55.0f, defaultFont.get(),
			Vec4(1, 1, 1, 1), 14.0f, LEFT_BASE_LINE);
        wxSize sz;
        MeasureText(defaultFont.get(), fontSize, "Baker!", sz);
        DrawLineR(10.0f, 15.0f, 20.0f, 30.0f, Vec4(1, 1, 1, 1));

        tcTVEngine::Get()->GetScreen2D()->Draw_Ellipse(60.0f, 30.0f, 25.0f, 30.0f, 72, -1);
    }

    tcRect testRect(10.0f, 100.0f, 20.0f, 200.0f);
	Vec4 testColor(0.1f, 0.25f, 0.1f, 1.0f);
    DrawRectangleR(testRect, testColor, FILL_OFF);

    FinishDraw();
    return;
}


/**
* Draws fuel state info.
*/
void tcObjectControl::DrawFuelInfo()
{
    wxASSERT(simState);

    tcPlatformObject* obj = dynamic_cast<tcPlatformObject*>(mpHookedGameObj);
    if (obj == 0) return;

	if (obj->mpDBObject->HasInfiniteFuel()) return; // object nuclear powered, don't display

	float fuelFraction = obj->fuel_kg / obj->GetFuelCapacity();

    const float barWidth = 8.0f;
    const float barHeight = 60.0f;
    const float xbar = 135.0f;
    const float ybar = 120.0f; //mnHeight-21-barHeight;

    tcRect barFrame;
	barFrame.Set(xbar, xbar + barWidth, ybar, ybar + barHeight);

    tcRect barFill;
	barFill.Set(xbar, xbar + barWidth, ybar + barHeight*(1-fuelFraction), ybar + barHeight);

	Vec4 color(0.1f, 0.25f, 0.1f, 1.0f);

    DrawRectangleR(barFrame, color, FILL_OFF);

    if (fuelFraction > 0.5f)
    {
		color.set(0.4f, 1.0f, 0.4f, 1.0f);
    }
    else if (fuelFraction > 0.1f)
    {
		color.set(1.0f, 1.0f, 0.4f, 1.0f);
    }
    else
    {
 		color.set(1.0f, 0.4f, 0.4f, 1.0f);
    }

    DrawRectangleR(barFill, color, FILL_ON);

	// for diesel-electric subs, draw battery charge bar next to fuel state
	tcSubObject* sub = dynamic_cast<tcSubObject*>(obj);
	if (sub == 0)
	{    
		wxString fuelText = fuelText.Format("FUEL: %.1f%%",fuelFraction*100.0f);
		DrawTextR(fuelText.c_str(), xbar-8, ybar+barHeight+12, defaultFont.get(),
			color, fontSize, LEFT_BASE_LINE);
		return;
	}

	if (!sub->IsDieselElectric())
	{
		return; 
	}


	float batteryFraction = sub->GetBatteryCharge() / sub->mpDBObject->batteryCapacity_kJ;

	barFrame.Offset(2*barWidth, 0);
	color.set(0.1f, 0.25f, 0.1f, 1.0f);
    DrawRectangleR(barFrame, color, FILL_OFF);

	barFill.Set(xbar, xbar + barWidth, ybar + barHeight*(1-batteryFraction), ybar + barHeight);
	barFill.Offset(2*barWidth, 0);

	if (batteryFraction > 0.5f)
    {
		color.set(0.4f, 1.0f, 0.4f, 1.0f);
    }
    else if (batteryFraction > 0.1f)
    {
		color.set(1.0f, 1.0f, 0.4f, 1.0f);
    }
    else
    {
 		color.set(1.0f, 0.4f, 0.4f, 1.0f);
    }

	DrawRectangleR(barFill, color, FILL_ON);

	wxString fuelText;
	if (sub->IsSnorkeling())
	{
		fuelText = fuelText.Format("FUEL: %.1f%% BATT: %.1f%% (Diesels active)",
			fuelFraction * 100.0f, batteryFraction * 100.0f);
	}
	else
	{
		fuelText = fuelText.Format("FUEL: %.1f%% BATT: %.1f%%",
			fuelFraction * 100.0f, batteryFraction * 100.0f);
	}
	DrawTextR(fuelText.c_str(), xbar-15, ybar+barHeight+12, defaultFont.get(),
		color, fontSize, LEFT_BASE_LINE);

}

/**
* draws launcher control interface
*/
void tcObjectControl::DrawFireControl() 
{

    tcString sText;

    wxASSERT(simState);

    if (simState->GetPlatformState(mnHookID,mpHookedGameObj)==false) 
    {
        mnLaunchers = 0;
        mpHookedGameObj = NULL;
        return; // obj not found
    } 
    teButtonState eLauncherState;
    tcLauncherState *pLauncherState;
    mpHookedGameObj->GetLauncherState(pLauncherState);
    if (pLauncherState == NULL) {return;}
    mnLaunchers = pLauncherState->GetLauncherCount();
    mcWeaponPanel.SetNumRows(mnLaunchers);

    for(int i=0;i<mnLaunchers;i++) 
    {
        tcLauncher* pLauncher = pLauncherState->GetLauncher(i);
        int nLaunchCount = pLauncher->mnCurrent;
        
        std::string displayName = pLauncher->GetLauncherName();
        std::string childClassName = pLauncher->GetChildClassDisplayName();
        std::string caption;
        if (displayName.size())
        {
            caption = displayName;
            caption += " - ";
            caption += childClassName;
        }
        else
        {
            caption = childClassName;
        }
        mcWeaponPanel.SetCaptionB(this, caption.c_str(), i, 0);
        mcWeaponPanel.mastrCaption[i][1].Format("%d", nLaunchCount);

        // hack to display "P" only when launcher has associated preset (torpedoes and water CM)
        mcWeaponPanel.mastrCaption[i][2] = "";
        if (pLauncher)
        {
            tcTorpedoDBObject* torpDBObj = dynamic_cast<tcTorpedoDBObject*>(pLauncher->mpChildDBObj);
            tcCounterMeasureDBObject* cm = dynamic_cast<tcCounterMeasureDBObject*>(pLauncher->mpChildDBObj);

            if ((torpDBObj != 0) || ((cm != 0) && (cm->mnModelType == MTYPE_WATERCM)))
            {
                if (!tcLauncherPopup::WindowExists(mpHookedGameObj->mnID, i))
                {
                    mcWeaponPanel.mastrCaption[i][2] = "P";
                }
                else
                {
                    mcWeaponPanel.mastrCaption[i][2] = "x";
                }
            }
        }

        int statusCode = pLauncher->GetLauncherStatus();
        bool isDamaged = (statusCode == tcLauncher::DAMAGED);

        if (isDamaged)
        {
            eLauncherState = BS_DAMAGED;
        }
        else if (nLaunchCount <= 0) 
        {
            eLauncherState = BS_DISABLED;
        }
        else if (pLauncher->mfTimeToReady <= 0) 
        {
            eLauncherState = BS_ACTIVE;
        }
        else 
        {
            eLauncherState = BS_READYING;
        }


        if ((pLauncher->isLoading) && (!isDamaged))
        {
            eLauncherState = BS_LOADING;
        }

        if ((eLauncherState == BS_ACTIVE) && (statusCode == tcLauncher::LAUNCHER_READY))
        {
            eLauncherState = BS_READY;
        }

        mcWeaponPanel.maButtonState[i][0] = eLauncherState;
        mcWeaponPanel.maButtonState[i][1] = eLauncherState;
        mcWeaponPanel.maButtonState[i][2] = eLauncherState;
    }
    mcWeaponPanel.Draw((tc3DWindow2*)this);

}

/**
* Draws gear down and other misc landing info for air objects.
*/
void tcObjectControl::DrawLandingInfo()
{
    tcAirObject *air = dynamic_cast<tcAirObject*>(mpHookedGameObj);
    if (air == NULL) return;

    if (air->readyForLanding)
    {
        // place next to altitude bar
        float x = 70.0f;
        float y = 95.0f; 
		Vec4 color(0.4f, 1.0f, 0.4f, 1.0f);
        DrawTextR("Landing", x, y, defaultFont.get(),
			color, fontSize, LEFT_BASE_LINE);
    }
}

/**
* draws sensor control interface
*/
void tcObjectControl::DrawSensorControl() 
{

    tcString sText;
    tcDBString zClass;

	wxASSERT(simState);

    if (simState->GetPlatformState(mnHookID,mpHookedGameObj)==false) 
    {
        mnSensors = 0;
        mpHookedGameObj = NULL;
        return; // obj not found
    } 
    tcPlatformObject* pPlatformObj = dynamic_cast<tcPlatformObject*>(mpHookedGameObj);
    if (pPlatformObj != NULL) 
    {
        mnSensors = (int)pPlatformObj->GetSensorCount();
    }
    else 
    {
        mnSensors = 0;
    }

	
	int nHidden = 0;
	for(int i=0; i<mnSensors; i++) 
	{
		const tcSensorState* sensorState = pPlatformObj->GetSensor((unsigned)i);
		if (!sensorState->IsHidden())
		{
			int idx = i - nHidden;

            teButtonState eSensorState;
            if (sensorState->IsDamaged())
            {
                eSensorState = BS_DAMAGED;
			    mcSensorPanel.mastrCaption[idx][1] = "D";
            }
            else if (sensorState->IsActive())
            {
                eSensorState = BS_ACTIVE;
                mcSensorPanel.mastrCaption[idx][1] = "ON";
                if (const tcRadar* radar = dynamic_cast<const tcRadar*>(sensorState))
                {
                    if (radar->IsJammed())
                    {
                        eSensorState = BS_WARN;
                    }
                }
                else if (const tcESMSensor* esm = dynamic_cast<const tcESMSensor*>(sensorState))
                {
                    switch (esm->GetRWRWarningLevel())
                    {
                    case 1: eSensorState = BS_RWRWARN1; break;
                    case 2: eSensorState = BS_RWRWARN2; break;
                    }
                }
            }
            else
            {
                eSensorState = BS_DISABLED;
                mcSensorPanel.mastrCaption[idx][1] = "OFF";
            }
			
			mcSensorPanel.SetCaption(sensorState->mpDBObj->mzClass.c_str(), idx, 0);
			mcSensorPanel.maButtonState[idx][0] = eSensorState;
			mcSensorPanel.maButtonState[idx][1] = eSensorState;
		}
		else
		{
			nHidden++;
		}
	}
    mcSensorPanel.SetNumRows (mnSensors - nHidden);
	mcSensorPanel.Draw((tc3DWindow2*)this);

}


/**
*
*/
void tcObjectControl::DrawHeadingObject(tsHeadingObjectInfo *apHOI, 
                                        float afHeading_rad, float afHeadingGoal_rad) 
{
    float x1, y1, x2, y2;

    if (apHOI == 0) return;

	Vec4 color(0.4f, 1.0f, 0.4f, 1.0f);
    
	if (headingCircle.get() == 0)
	{
		CreateHeadingCircles();
	}

    static unsigned int n = 0;

	DrawGeometryR(headingCircle.get(), apHOI->mrectArc.XCenter(), apHOI->mrectArc.YCenter());

    x1 = apHOI->mfxcenter;
    y1 = apHOI->mfycenter;
    x2 = x1 + apHOI->mfradius * sinf(afHeading_rad);
    y2 = y1 - apHOI->mfradius * cosf(afHeading_rad);
	color.set(0.5f, 0.5f, 1.0f, 1.0f);

    DrawLineR(x1, y1, x2, y2, color);


    // draw current heading text
    tcString s;
    wxSize size;

    int heading_deg = int(C_180OVERPI*afHeading_rad + 0.5f);
    heading_deg = heading_deg + (int(heading_deg < 0) - int(heading_deg >= 360))*360;

    afHeading_rad += float(afHeading_rad < 0) * C_TWOPI;
    s.Format("%03d", heading_deg);

	color.set(0.8f, 0.8f, 1.0f, 1.0f);
    MeasureText(defaultFont.get(), fontSize, s.GetBuffer(), size);
	DrawTextR(s.GetBuffer(), 1.0f+x1-0.5f*float(size.GetWidth()), y1+0.2f*apHOI->mfradius+3.0f,
		defaultFont.get(), color, fontSize, LEFT_BASE_LINE);

    if (!apHOI->canSetHeading) return;

    if (apHOI->mbMouseOver) 
    {
		DrawGeometryR(headingCircleLight.get(), apHOI->mrectArc.XCenter(), apHOI->mrectArc.YCenter());
    }

    // draw goal heading if applicable (if different)
    float fDeltaHeading = afHeading_rad - afHeadingGoal_rad;
    if (fDeltaHeading < -C_PI) {fDeltaHeading += C_TWOPI;}
    if (fDeltaHeading > C_PI) {fDeltaHeading -= C_TWOPI;}
    if (fabsf(fDeltaHeading) > 0.01f) 
    {
        x2 = x1 + apHOI->mfradius * sinf(afHeadingGoal_rad);
        y2 = y1 - apHOI->mfradius * cosf(afHeadingGoal_rad);
		color.set(0.63f, 0.63f, 0.63f, 1.0f);
        DrawLineR(x1, y1, x2, y2, color);
    }

    if (apHOI->mbMouseOver) 
    {
        x2 = x1 + apHOI->mfradius * sinf(apHOI->mfMouseHeading_rad);
        y2 = y1 - apHOI->mfradius * cosf(apHOI->mfMouseHeading_rad);
		color.set(0.81f, 0.81f, 1.0f, 1.0f);
        DrawLineR(x1, y1, x2, y2, color);

        wxString mouseText;
        int heading_deg = int(floorf(0.5f + C_180OVERPI*apHOI->mfMouseHeading_rad));
        if (heading_deg < 0) heading_deg += 360;

        mouseText.Printf("%03d", heading_deg);
        DrawTextR(mouseText.c_str(), apHOI->mfxcenter, apHOI->mfycenter - apHOI->mfradius - 10.0f,
            defaultFont.get(), color, 14.0f, CENTER_CENTER);
    }


}

/**
* Calls Draw method of tcControl objects in controls vector
*/
void tcObjectControl::DrawControls()
{
    size_t nControls = controls.size();
    for (size_t n=0; n<nControls; n++)
    {
        controls[n]->Draw(this);
    }
}

/******************************************************************************/
void tcObjectControl::DrawEngagementInfo() 
{
#if 0
    RectF rborder;
    RectF rectwp;
    SizeF size;
    tcString s;

    if (apGraphics==NULL) {return;}
    mcWeaponPanel.GetRect(rectwp);
    float fX = rectwp.X;
    float fYstart = rectwp.GetBottom() + 15.0f;
    float fY = fYstart;
    float fColumnWidth = 50.0f;
    rborder = rectwp;
    rborder.Y = fY;
    rborder.Height = 50.0f;
    mpPen->SetColor(0xFF164016);
    apGraphics->DrawRectangle(mpPen,rborder);

    tcSurfaceObject *pSurfaceObj = dynamic_cast<tcSurfaceObject*> (mpHookedGameObj);
    if (pSurfaceObj == NULL) {return;}
    tcEngagementData* pED = &pSurfaceObj->mcEngagementData;
    for(unsigned i=0;i<pED->mnCount;i++) 
    {
        s.Format("U%d",pED->maTrackInfo[i].mnID);
        UINT32 nColor = (pED->maTrackInfo[i].mbEngaged) ? 0xFE0000FF : 0xFE64FF64;
        mpBrush->SetColor(Color(nColor));
        DrawText(apGraphics,mpFont,mpBrush,s.GetBuffer(),fX,fY);
        MeasureText(apGraphics,mpFont,s.GetBuffer(),size);
        fY += size.Height;
        if (fY >= (rborder.GetBottom()-10.0f)) 
        {
            fY = fYstart;
            fX += fColumnWidth;
        }
    }
#endif
}

/**
* Currently only used for speed control. Should be refactored like tcAltitudeBarControl
* @param redLineValue draw a red line at this value if > 0
*/
void tcObjectControl::DrawBarObject(tsBarObjectInfo *apBOI, 
                                    float afValue, float afValueGoal, float redLineValue) 
{
    tcString s;
    wxSize size;
    tcRect rcurrent;

    if (apBOI==NULL) {return;}

	Vec4 color;

    if (afValue > apBOI->mfmaxvalue) afValue = apBOI->mfmaxvalue;  // restrict afValue to max

    // hack for afterburners indication
    bool drawOverGoal = false;
    tcRect overRect;
	overRect = apBOI->mrectbar;
    if (afValueGoal > apBOI->mfmaxvalue) 
    {
        afValueGoal = 1.05f * apBOI->mfmaxvalue; 
        drawOverGoal = true;
        if (apBOI->mbVertical)
        {
            overRect.Offset(0, apBOI->mrectbar.Height());
			overRect.right = overRect.left + 0.05f*apBOI->mrectbar.Width();

        }
        else
        {
            overRect.Offset(overRect.Width(), 0);
			overRect.right = overRect.left + 0.05f*apBOI->mrectbar.Width();
        }

        if (tcTime::Get()->snCount_30Hz % 30 > 15) // blink
        {
			color.set(1.0f, 0.4f, 0.4f, 1.0f);
        }
        else
        {
			color.set(0.5f, 0.2f, 0.2f, 1.0f);
        }
        DrawRectangleR(overRect, color, FILL_ON);
    }

	color.set(0.2f, 0.5f, 0.2f, 1.0f);

    DrawRectangleR(apBOI->mrectbar, color, FILL_OFF);

    rcurrent = apBOI->mrectbar;
	color.set(0.2f, 0.5f, 0.2f, 1.0f);
    DrawRectangleR(rcurrent, color, FILL_OFF);

    float valueRange = apBOI->mfmaxvalue - apBOI->mfminvalue;
    float fractionalValue = (afValue - apBOI->mfminvalue) / valueRange;

    if (apBOI->mbVertical) 
    {
        rcurrent.top = apBOI->mrectbar.GetTop();
		rcurrent.bottom = rcurrent.top - (fractionalValue)*(apBOI->mrectbar.Height());
    }
    else 
    {
        rcurrent.right = rcurrent.left + (fractionalValue)*(apBOI->mrectbar.Width());
    }
	color.set(0.4f, 1.0f, 0.4f, 1.0f);

    DrawRectangleR(rcurrent, color, FILL_ON);

    // draw goal line if different enough from value
    float dVal = afValueGoal - afValue;
    if (fabsf(dVal) >= 0.0078125f) 
    {
        float fractionalGoalValue = (afValueGoal - apBOI->mfminvalue) / valueRange;
        float x1,x2,y1,y2;
        if (!apBOI->mbVertical) 
        {
            y1 = rcurrent.GetBottom() - 2.0f;
            y2 = rcurrent.GetTop() + 2.0f;
            x1 = rcurrent.left + (fractionalGoalValue)*(apBOI->mrectbar.Width());
            x2 = x1;
        }
        else 
        {
            x1 = rcurrent.GetLeft() - 2.0f;
            x2 = rcurrent.GetRight() + 2.0f;
            y1 = rcurrent.GetTop() - (fractionalGoalValue)*(apBOI->mrectbar.Height());
            y2 = y1;
        }
		color.set(0.8f, 0.8f, 0.8f, 1.0f);
        DrawLineR(x1, y1, x2, y2, color);
    }

    // draw red line value if greater than zero
    if ((redLineValue > 0) && (redLineValue <= apBOI->mfmaxvalue))
    {
        float fractionalRedLineValue = (redLineValue - apBOI->mfminvalue) / valueRange;
        float x1,x2,y1,y2;
        if (!apBOI->mbVertical) 
        {
            y1 = rcurrent.GetBottom() - 2.0f;
            y2 = rcurrent.GetTop() + 2.0f;
            x1 = rcurrent.left + (fractionalRedLineValue)*(apBOI->mrectbar.Width());
            x2 = x1;
        }
        else 
        {
            x1 = rcurrent.GetLeft() - 2.0f;
            x2 = rcurrent.GetRight() + 2.0f;
            y1 = rcurrent.GetTop() - (fractionalRedLineValue)*(apBOI->mrectbar.Height());
            y2 = y1;
        }
		color.set(0.8f, 0.0f, 0.0f, 1.0f);
        DrawLineR(x1, y1, x2, y2, color);
    }

    if (apBOI->mbMouseOver) 
    {
        float xDraw = apBOI->mfmousevalue;

        if (xDraw > apBOI->mfmaxvalue) {xDraw = apBOI->mfmaxvalue;}
        else if (xDraw < apBOI->mfminvalue) {xDraw = apBOI->mfminvalue;}

        float fractionalMouseValue = (xDraw - apBOI->mfminvalue) / valueRange;

		color.set(1, 1, 1, 0.63f);

        if (apBOI->mbVertical) 
        {
			rcurrent.top = apBOI->mrectbar.GetTop();
			rcurrent.bottom = rcurrent.top - 
				(fractionalMouseValue)*(apBOI->mrectbar.Height());
        }
        else
        {
			rcurrent.right = rcurrent.left + 
				(fractionalMouseValue)*(apBOI->mrectbar.Width());
        }
        DrawRectangleR(rcurrent, color, FILL_ON);

        DrawTextR(apBOI->overText.c_str(), apBOI->xMouse, apBOI->mrectcontrol.top - 20.0f, 
			defaultFont.get(), color, 14.0f, CENTER_CENTER);
    }

	color.set(0.4f, 1.0f, 0.4f, 1.0f);

    s.Format("%.0f",afValue);
    //mpBrush->SetColor(0xFEFF8080);
    //MeasureText(apGraphics,mpFont,s.GetBuffer(),size);
    if (apBOI->mbVertical) 
    {
		DrawTextR(s.GetBuffer(), apBOI->mrectcontrol.left + 12.0f, apBOI->mrectcontrol.top - 10.0f, 
			defaultFont.get(), color, fontSize, LEFT_BASE_LINE);
    }
    else 
	{
		DrawTextR(s.GetBuffer(), apBOI->mrectcontrol.left, apBOI->mrectcontrol.bottom + 8.0f, 
			defaultFont.get(), color, fontSize, LEFT_BASE_LINE);
    }

}
/******************************************************************************/
void tcObjectControl::GetObjectInfo(tcString& s, tcDatabaseObject *apDBObject, tcGameObject *apGameObject)
{
    char zClass[24], zModel[8], zType[8];
    if (apDBObject == NULL) 
    {
        s.Format("NULL DBObject");
        return;
    }
    if (apGameObject == NULL) 
    {
        s.Format("NULL GameObject");
        return;
    }
    
    std::string className = apDBObject->GetClassName();

    strcpy_s(zClass, 24, className.c_str());

    /*switch (apDBObject->mnClassID) 
    {
    case DTYPE_GENERIC:
        strcpy(zClass,"GEN");
        break;
    case DTYPE_MISSILE:
        strcpy(zClass,"MIS");
        break;
    case DTYPE_LAUNCHER:
        strcpy(zClass,"LAU");
        break;
    case DTYPE_AIR:
        strcpy(zClass,"AIR");
        break;
	case DTYPE_BALLISTIC:
        strcpy(zClass,"BAL");
        break;
	case DTYPE_TORPEDO:
		strcpy(zClass, "TOR");
		break;
	case DTYPE_SUBMARINE:
		strcpy(zClass, "SUB");
		break;
    default:
        strcpy(zClass,"UNK");
        break;
    }*/

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
    s.Format("%s %s %s",zClass,zModel,zType); 
}


void tcObjectControl::OnCycleGroupLeftCommand(wxCommandEvent& event)
{
    CycleGroupHook(false);
}

void tcObjectControl::OnCycleGroupRightCommand(wxCommandEvent& event)
{
    CycleGroupHook(true);
}


void tcObjectControl::OnEnterWindow(wxMouseEvent& event)
{
	isMouseOver = true;
}

void tcObjectControl::OnLeaveWindow(wxMouseEvent& event)
{
	isMouseOver = false;

	event.Skip(); // pass up so that event can be passed back to map for edge scroll
    event.ResumePropagation(2);
}

/**
*
*/
void tcObjectControl::OnLButtonDown(wxMouseEvent& event) 
{
    int nLauncher,nSensor,nCol;

	wxASSERT(simState);

    if (mpHookedGameObj == 0) {return;} // no valid hooked obj
    
    if (mpHookedGameObj->IsClientMode() && !mpHookedGameObj->IsControlled())
    {
        tcMessageInterface::Get()->ConsoleMessage("You do not have control of this object");
        return; // client does not have control of this object
    }
    
    wxPoint point = event.GetPosition();

    mcWeaponPanel.UpdatePageSelect(point);
    mcSensorPanel.UpdatePageSelect(point);

    if (mcWeaponPanel.ButtonContainingPoint(point, nLauncher, nCol)) 
    {
        if ((nLauncher >= mnLaunchers)||(nLauncher < 0)||(nCol < 0)) 
        {
            fprintf(stderr, "tcObjectControl::OnLButtonDown (weap panel) error\n");
            return;
        } 
        bool bAccepted = ProcessWeaponPanelButton(nLauncher, nCol);
        if (bAccepted)
        {
            tcSound::Get()->PlayEffect("LowBeep");
        }
    }
    else if (mcSensorPanel.ButtonContainingPoint(point, nSensor, nCol)) 
    {
        if ((nSensor >= mnSensors)||(nSensor < 0)||(nCol < 0)) 
        {
            fprintf(stderr, "tcObjectControl::OnLButtonDown (sensor panel) error\n");
            return;
        }
        ProcessSensorPanelButton(nSensor, nCol);
    } 
    else if (msHOI.mrectArc.ContainsPoint((float)point.x,(float)point.y)) 
    {
		if (tcPlatformObject* plat = dynamic_cast<tcPlatformObject*>(mpHookedGameObj))
        {
            plat->SetHeading(msHOI.mfMouseHeading_rad);
            plat->SetMaxTurnRate(360.0f);
			msHOI.mbMouseOver = false;
            if (ai::Brain* brain = plat->GetBrain())
            {
                ai::Nav* nav = brain->GetNavTask();
                if (nav != 0)
                {
                    nav->ClearWaypoints();
                    nav->EndTask();
                }
                if (brain->TaskExists("AutoLoiter"))
                {
                    brain->RemoveTask("AutoLoiter");
                }
            }
        }
        else if (tcTorpedoObject* torpedo = dynamic_cast<tcTorpedoObject*>(mpHookedGameObj))
        {
            if (torpedo->isWireActive)
            {
                torpedo->SetHeading(msHOI.mfMouseHeading_rad);
                msHOI.mbMouseOver = false;
            }
        }
    }
    else if (msSOI.mrectcontrol.ContainsPoint((float)point.x,(float)point.y)) 
    {
        // Call SetThrottleFraction for AeroAir object instead of SetSpeed
        if (tcAeroAirObject *aeroAirObj = dynamic_cast<tcAeroAirObject*>(mpHookedGameObj))
        {
            msSOI.mfmousevalue = std::max(msSOI.mfmousevalue, msSOI.mfminvalue);

            float fraction = msSOI.mfmousevalue / aeroAirObj->mpDBObject->mfMaxSpeed_kts;
            if (fraction <= 1.0f)
            {
                aeroAirObj->SetThrottleFraction(fraction);
            }
            else if (fraction < 1.01f)
            {
                aeroAirObj->SetThrottleFraction(1.0f);
            }
            else
            {
                aeroAirObj->SetThrottleFraction(2.0f);
            }
        }
        else if (tcPlatformObject* plat = dynamic_cast<tcPlatformObject*>(mpHookedGameObj))
        {
            msSOI.mfmousevalue = std::min(msSOI.mfmousevalue, msSOI.mfmaxvalue);
            msSOI.mfmousevalue = std::max(msSOI.mfmousevalue, msSOI.mfminvalue);

            float requestSpeed_kts = units->UserSpeedToKts(msSOI.mfmousevalue);
            plat->SetSpeed(requestSpeed_kts);

            // automatic limiting to avoid cavitation unless click twice
            //if (tcSubObject* sub = dynamic_cast<tcSubObject*>(plat))
            //{
            //    float maxQuietSpeed_kts = sub->GetMaxQuietSpeedKts();
            //    float goalSpeed_kts = sub->mcGS.mfGoalSpeed_kts;

            //    if ((requestSpeed_kts <= maxQuietSpeed_kts) || (goalSpeed_kts >= maxQuietSpeed_kts))
            //    {
            //        sub->SetSpeed(requestSpeed_kts);
            //    }
            //    else
            //    {
            //        sub->SetSpeed(maxQuietSpeed_kts);
            //    }
            //}
            //else
            //{
            //    plat->SetSpeed(requestSpeed_kts);
            //}
        }
        msSOI.mbMouseOver = false;
    }
    else if (formationFlagRect.ContainsPoint((float)point.x,(float)point.y))
    {
        if (tcPlatformObject* plat = dynamic_cast<tcPlatformObject*>(mpHookedGameObj))
        {
            plat->SetFormationLeader(-1); // leave formation
        }
    }
	else if (mcAIPanel.OnLButtonDown(point))
	{
	}
		


    event.m_y = mnHeight - event.m_y;
    size_t nControls = controls.size();
    for (size_t n=0; n<nControls; n++)
    {
        controls[n]->OnLButtonDown(event);
    }

}

/**
*
*/
bool tcObjectControl::ProcessWeaponPanelButton(int anLauncher, int anButton) 
{
    bool bReadyForLaunch;

    if (mpCommandInterface == NULL) {return false;}

    //bReadyForLaunch = simState->IsLauncherReady(mpHookedGameObj, anLauncher);
    bReadyForLaunch = true; // SetLaunch upgraded to check readiness independently

    switch (anButton) 
    {
    case 0:
        {
            tcLauncher* launcher = mpHookedGameObj->GetLauncher(anLauncher);
            wxASSERT(launcher != 0);

            launcher->ActivateFireControl();

            if (launcher->meLaunchMode == DATUM_ONLY)
            {
                HandoffDatumToLauncher(launcher, anLauncher);
            }

            int statusCode = launcher->GetLauncherStatus();

            if (statusCode == tcLauncher::LAUNCHER_READY) 
            {
                mpHookedGameObj->SetLaunch(anLauncher, 1);
            }
            else
            {
                //std::string statusString = launcher->TranslateStatus(statusCode);
                wxString statusStringWx = launcher->TranslateStatusDetailed(statusCode);
                std::string statusString(statusStringWx.c_str());
                tcMessageInterface::Get()->ConsoleMessage(statusString);
            }
            break;
        }
    case 2: // "P" launcher programming, e.g. torpedo settings
        {
            if (tcLauncher* launcher = mpHookedGameObj->GetLauncher(anLauncher))
            {
                tcTorpedoDBObject* torpDBObj = dynamic_cast<tcTorpedoDBObject*>(launcher->mpChildDBObj);
                tcCounterMeasureDBObject* cm = dynamic_cast<tcCounterMeasureDBObject*>(launcher->mpChildDBObj);

                if ((torpDBObj != 0) || ((cm != 0) && (cm->mnModelType == MTYPE_WATERCM)))
                {
                    if (!tcLauncherPopup::WindowExists(mpHookedGameObj->mnID, anLauncher))
                    {
                        const wxPoint popupPos = tcLauncherPopup::GetUserPosition(anLauncher);

                        tcLauncherPopup* popupControl = 
                            new tcLauncherPopup(mpHookedGameObj->mnID, anLauncher, popupPos);
                    }
                    else // toggle closed
                    {
                        tcLauncherPopup::ForceClose(mpHookedGameObj->mnID, anLauncher);
                    }

                    return true;
                }
            }
        }
        break;
    case 3: // "FC"
        mpCommandInterface->AddCommand(PC_GETLAUNCHERTARGET,0,0,anLauncher);
        return true;
        break;
    case 4: // "LAUNCH"
        wxASSERT(false); // used anymore?
        if (bReadyForLaunch) {mpHookedGameObj->SetLaunch(anLauncher,1);}
        else 
        {
            //tcSound::Get()->PlayEffect("RejectBeep");
        }
        return true;
        break;
    default:
        break;
    }
    return false;
}
/**
* @param row button row on sensor panel
* @param col button column on sensor panel
*/
bool tcObjectControl::ProcessSensorPanelButton(int row, int col) 
{
    tcPlatformObject* pPlatformObj = dynamic_cast<tcPlatformObject*>(mpHookedGameObj);
	if (pPlatformObj == 0)
	{
		fprintf(stderr, "Warning - tcObjectControl::ProcessSensorPanelButton - no valid hooked obj\n");
		return false;
	}
    
	int sensorIdx = GetSensorIndexForRow(row);

    if (sensorIdx < 0) 
    {
		fprintf(stderr, "Warning - tcObjectControl::ProcessSensorPanelButton - bad idx\n");
        return false;
    }

    switch (col) 
    {
    case 1: // toggle sensor on/off
		{
			const tcSensorState* pSensorState = pPlatformObj->GetSensor(sensorIdx);
			pPlatformObj->SetSensorState((unsigned)sensorIdx, !pSensorState->IsActive());
            
            if (pSensorState->IsActive())
            {
                tcSound::Get()->PlayEffect("radar_on");
            }
            else
            {
                tcSound::Get()->PlayEffect("radar_off");
            }
        
			return true;
		}
		break;
    default:
        break;
    }
    return false;
}

void tcObjectControl::SetActive(bool abActive)
{
    tc3DWindow2::SetActive(abActive);

    SetShowCycleGroupButtons(hookedGroup.size() > 1);
}

/**
* Calls SetGameObject method of tcControl objects in controls
* vector.
*/
void tcObjectControl::SetControlGameObject(tcGameObject* obj)
{
    size_t nControls = controls.size();
    for (size_t n=0; n<nControls; n++)
    {
        controls[n]->SetGameObject(obj);
    }
}

void tcObjectControl::SetHookID(long id)
{
    hookedGroup.clear();
    SetShowCycleGroupButtons(false);

    {
        lastWeaponRangeSpeed_kts = -9999.0f;
        lastWeaponRangeAltitude_m = -9999.0f;
    }

	//if (mnHookID == id) return;

	mnHookID = id;
	rowToSensor.clear();
	isRowToSensorUpdated = false;
    mcWeaponPanel.SetPage(0);
    mcSensorPanel.SetPage(0);
    UpdateControlObjects();
}

/**
* Set currently selected group member for group hook
*/
void tcObjectControl::SetHookIDgroup(long id)
{
	if (mnHookID == id) return;

	mnHookID = id;
	rowToSensor.clear();
	isRowToSensorUpdated = false;
    mcWeaponPanel.SetPage(0);
    mcSensorPanel.SetPage(0);
    UpdateControlObjects();
}

void tcObjectControl::SetHookID(const std::vector<long>& id)
{   
    if (id.size() == 1)
    {
        SetHookID(id[0]);
        return;
    }
    else if (id.size() == 0)
    {
        SetHookID(-1); // clear everything
        return;
    }
    else
    {	       
        SetHookIDgroup(id[0]);
        hookedGroup = id;
        SetShowCycleGroupButtons(true);
    }
}

void tcObjectControl::SetShowCycleGroupButtons(bool state)
{
    if (state)
    {
        cycleHookLeft->SetActive(true);
        cycleHookRight->SetActive(true);
    }
    else
    {
        cycleHookLeft->SetActive(false);
        cycleHookRight->SetActive(false);
    }
}

/**
*
*/
void tcObjectControl::OnMouseMove(wxMouseEvent& event) 
{
	event.Skip(); // pass upward to application

	mcWeaponPanel.SetMouseOver(-1,-1);

    wxASSERT(simState);
    if (mpHookedGameObj == NULL) {return;} // no valid hooked obj

    wxPoint point = event.GetPosition();
	if (point != lastMousePos)
	{
		lastMousePos = point;
		lastMoveTime = tcTime::Get()->Get30HzCount();
		hintActive = false;
	}

    // check if point is in heading control
    float fx = (float)point.x;
    float fy = (float)point.y;
    if (msHOI.mrectArc.ContainsPoint(fx, fy)) 
    {
        msHOI.mbMouseOver = true;
        msHOI.mfMouseHeading_rad = atan2f(fx-msHOI.mfxcenter, msHOI.mfycenter-fy);
    }
    else if (msSOI.mrectcontrol.ContainsPoint(fx, fy)) 
    {
        msSOI.mbMouseOver = true;
        // changed to fractional speed to be compatible with throttle fraction
        float valueFraction = (fx-msSOI.mrectbar.left)/(msSOI.mrectbar.Width());
        valueFraction = std::max(valueFraction, 0.0f);

        msSOI.mfmousevalue = valueFraction * (msSOI.mfmaxvalue - msSOI.mfminvalue) + msSOI.mfminvalue;
        msSOI.mfmousevalue = std::max(msSOI.mfmousevalue, msSOI.mfminvalue);

        msSOI.xMouse = fx;

        if (tcAeroAirObject *aeroAirObj = dynamic_cast<tcAeroAirObject*>(mpHookedGameObj))
        {
            wxString s;
            if (valueFraction <= 1.0f)
            {
                s.Printf("%.0f %%", 100.0f*valueFraction);
            }
            else if (valueFraction < 1.01f)
            {
                s = "100 %";
            }
            else
            {
                float throttle = aeroAirObj->GetThrottleFraction();
                if (throttle <= 1.0f)
                {
                    s = "AB";
                }
                else
                {
                    s.Printf("AB-%.0f", 100.0f*(throttle - 1.0f)); // display percentage AB if AB active
                }
            }
            msSOI.overText = s.c_str();
        }
        else
        {
			// DEC2013 bug fix for incorrect mouseover value for units other than kts
			msSOI.mfmousevalue = std::min(msSOI.mfmousevalue, msSOI.mfmaxvalue);

			// speed (mfmousevalue) is already in user units
			wxString s;
			s.Printf("%.0f %s", msSOI.mfmousevalue, units->GetSpeedUnitLabel());
			msSOI.overText = s.c_str();
        }


    }
    else 
    {
        msHOI.mbMouseOver = false;
        msSOI.mbMouseOver = false;
    }

    event.m_y = mnHeight - event.m_y;
    size_t nControls = controls.size();
    for (size_t n=0; n<nControls; n++)
    {
        controls[n]->OnMouseMove(event);
    }

	int row = -1, col = -1;
	bool contains = mcWeaponPanel.ButtonContainingPoint(point, row, col);
	if (contains && (col == 0))
	{
		mcWeaponPanel.SetMouseOver(row, col);
	}

}

const std::vector<MapSymbolInfo>& tcObjectControl::GetMapSymbols() const
{
	return symbolList;
}

/**
* returns sensor index after accounting for hidden sensors
* @return sensor index associated with row of sensor panel or -1 if invalid
*/
int tcObjectControl::GetSensorIndexForRow(unsigned int row)
{
	if (isRowToSensorUpdated)
	{
		if (row >= rowToSensor.size()) return -1;
		else return rowToSensor[row];
	}

    // update map from row number to sensor number, accounting for hidden sensors
    tcPlatformObject* platformObj = dynamic_cast<tcPlatformObject*>(mpHookedGameObj);

	unsigned int nSensors;
    if (platformObj != 0) 
    {
        nSensors = (int)platformObj->GetSensorCount();
    }
    else
    {
        nSensors = 0;
    }

	rowToSensor.clear(); 
	int nHidden = 0;
	for (unsigned int k=0; k<nSensors; k++)
	{
		const tcSensorState* pSensorState = platformObj->GetSensor(k);
		if (pSensorState->IsHidden())
		{
			nHidden++;
		}
		else
		{
			rowToSensor.push_back(k);
		}
	}
	isRowToSensorUpdated = true;

	if (row >= rowToSensor.size()) return -1;
	else return rowToSensor[row];
}

/**
* For DATUM_ONLY launch types, update launcher datum with predicted
* target position at intercept time
*/
void tcObjectControl::HandoffDatumToLauncher(tcLauncher* launcher, int launcherIdx)
{
    tcPlatformObject* platform = dynamic_cast<tcPlatformObject*>(mpHookedGameObj);
    if ((platform == 0) || (launcher == 0) || (launcher->mnTargetID == -1)) return;

    tcPlatformInterface platformInterface(platform);

    tcSensorMapTrack track = platformInterface.GetTargetTrackInfo();
    if (track.mnID == -1) return; // no target?

    float tti_s = platformInterface.GetLauncherInterceptTime(launcherIdx, track);
    tcSensorMapTrack predictedTrack = track.PredictAhead(tti_s);
    launcher->msDatum.mfAlt_m = predictedTrack.mfAlt_m;
    launcher->msDatum.mfLat_rad = predictedTrack.mfLat_rad;
    launcher->msDatum.mfLon_rad = predictedTrack.mfLon_rad;
}

/******************************************************************************/
void tcObjectControl::InitControls() 
{

    mcWeaponPanel.Init(BPTYPE_WEAPON);
    mcSensorPanel.Init(BPTYPE_SENSOR);
	tcRect aiLocation;
	aiLocation.Set(520, 650, panely, 120);
    mcAIPanel.SetLocation(aiLocation);

    // heading object 
    msHOI.mfradius = 20.0f;
    msHOI.mfxcenter = 30.0f;
    msHOI.mfycenter = 150.0f;
    msHOI.mrectArc.left = msHOI.mfxcenter - msHOI.mfradius;
    msHOI.mrectArc.bottom = msHOI.mfycenter - msHOI.mfradius;
    msHOI.mrectArc.right = msHOI.mrectArc.left + 2*msHOI.mfradius;
    msHOI.mrectArc.top = msHOI.mrectArc.bottom + 2*msHOI.mfradius;
    msHOI.mbMouseOver = false;
    msHOI.mfMouseHeading_rad = 0;

    // speed object
    msSOI.mbMouseOver = false;
    msSOI.mrectcontrol.left = 10.0f;
    msSOI.mrectcontrol.bottom = 95.0f;
    msSOI.mrectcontrol.right = msSOI.mrectcontrol.left + 160.0f;
    msSOI.mrectcontrol.top = msSOI.mrectcontrol.bottom + 10.0f;
    msSOI.mrectbar = msSOI.mrectcontrol;
    msSOI.mbVertical = false;
    msSOI.xMouse = 0;

    altitudeControl = new tcAltitudeBarControl(60, 17, 10, 60);
    altitudeControl->SetActive(true);
    controls.push_back(altitudeControl);

    leaderFlag = tc3DWindow2::LoadTexture("ralh.jpg");
    followerFlag = tc3DWindow2::LoadTexture("ralhred.jpg");
}

void tcObjectControl::InitializeGroupButtons()
{
	int xbutton = 190;
	int ybutton = 5;
	int buttonWidth = 12;

    wxASSERT((cycleHookLeft == 0) && (cycleHookRight == 0));

	cycleHookLeft = new tcButton(this, wxPoint(xbutton, ybutton),
		wxSize(buttonWidth, buttonWidth), "HookLeftButton");
	cycleHookLeft->SetCaption("");
	cycleHookLeft->LoadImages("left_green.jpg", "left_green.jpg", "left_green_over.jpg", 
		"left_green_over.jpg");
	cycleHookLeft->SetCommand(99);
	cycleHookLeft->Raise();

	xbutton += buttonWidth + 2;


	cycleHookRight = new tcButton(this, wxPoint(xbutton, ybutton),
		wxSize(buttonWidth, buttonWidth), "HookRightButton");
	cycleHookRight->SetCaption("");
	cycleHookRight->LoadImages("right_green.jpg", "right_green.jpg", "right_green_over.jpg", 
		"right_green_over.jpg");
	cycleHookRight->SetCommand(101);
	cycleHookRight->Raise();

    xbutton += buttonWidth + 30;

    SetShowCycleGroupButtons(false);
}

/**
*
*/
void tcObjectControl::UpdateControlObjects() 
{
    int bFound;

    wxASSERT(simState);

    //if (mnHookID==NULL_INDEX) {mpHookedGameObj=NULL;return;}

    bFound = simState->GetPlatformState(mnHookID, mpHookedGameObj);  

    if (!bFound) // hooked a sensor track in multiplayer client
    {
        mcAIPanel.SetAIData(0);
        return;
    }
    wxASSERT(mnHookID != -1); // should be taken care of above

    SetControlGameObject(mpHookedGameObj);


    tcPlatformObject* platformObj = dynamic_cast<tcPlatformObject*>(mpHookedGameObj);
    if (platformObj) 
    {
        mcAIPanel.SetAIData(platformObj->GetBrain());
    }
    else 
    {
        mcAIPanel.SetAIData(0);
    }



    msHOI.canSetHeading = true;

    bool updateSpeedControl = false;

    switch (mpHookedGameObj->mnModelType) 
    {
    case MTYPE_SURFACE:
    case MTYPE_CARRIER:
    case MTYPE_GROUNDVEHICLE:
        updateSpeedControl = (platformObj != 0) && (platformObj->mpDBObject->mfMaxSpeed_kts > 0);
        altitudeControl->SetActive(false);
        break;
    case MTYPE_AIRFIELD:
    case MTYPE_FIXED:
        updateSpeedControl = false;
        altitudeControl->SetActive(false);
        msHOI.canSetHeading = false;
        break;
    case MTYPE_FIXEDWING:
    case MTYPE_FIXEDWINGX:
    case MTYPE_HELO:
    case MTYPE_SUBMARINE:
        updateSpeedControl = true;
        altitudeControl->SetActive(true);
        break;
    case MTYPE_MISSILE:
        altitudeControl->SetActive(false);
        msHOI.canSetHeading = false;
        break;
    case MTYPE_TORPEDO:
        {
            tcTorpedoObject* torpedo = dynamic_cast<tcTorpedoObject*>(mpHookedGameObj);
            if (torpedo != 0)
            {
                altitudeControl->SetActive(torpedo->isWireActive);
                msHOI.canSetHeading = (torpedo->isWireActive);
            }
            else
            {
                wxASSERT(false);
                msHOI.canSetHeading = false;
                altitudeControl->SetActive(false);
            }
        }
        break;
    default:
        altitudeControl->SetActive(true);
    }

    if (updateSpeedControl)
    {
        //tcSurfaceObject *pSurfaceObj = (tcSurfaceObject*)mpHookedGameObj;
        //tcPlatformObject *pPlatformObj = dynamic_cast<tcPlatformObject*> (mpHookedGameObj);
        if (platformObj == NULL) {return;}
        
        msSOI.mfminvalue = 0;

        tcPlatformDBObject *pGenericData = platformObj->mpDBObject;
        if (pGenericData == NULL) {return;}

        float maxSpeed_kts = pGenericData->mfMaxSpeed_kts;
        if (tcSubObject* sub = dynamic_cast<tcSubObject*>(mpHookedGameObj))
        {
            maxSpeed_kts = std::max(maxSpeed_kts, sub->mpDBObject->surfaceSpeed_kts); // to handle rare case where surfaced speed is greater
        }

        msSOI.mfmaxvalue = units->UserSpeedUnits(maxSpeed_kts);
        
        msSOI.mrectbar = msSOI.mrectcontrol;
        msSOI.mrectbar.left += 25.0f;
        msSOI.mrectbar.right -= 5.0f;  
    }


}

/**
* Using mouse position determine if cursor is over an item that a tooltip
* should be displayed for. If so, then set text and rect for hint display.
*/
void tcObjectControl::UpdateHint()
{
	unsigned int t = tcTime::Get()->Get30HzCount();
	if (((t - lastMoveTime) < hintDelay) || (!isMouseOver))
	{
		hintActive = false;
		hintText = "";
		if (popupHint != 0)
		{
			popupHint->DestroyWindow();
			popupHint = 0;
		}
		return;
	}

	if (hintActive) return; // hint has already been calculated

	hintActive = true;
	wxASSERT(mpHookedGameObj);
	
	hintText = "";
	int xhint = 0;
	int yhint = 0;

	tcPlatformObject* platformObj = dynamic_cast<tcPlatformObject*>(mpHookedGameObj);
	if (platformObj == 0)
	{
		hintText = "Error";
		return;
	}

	// determine if curosr is over launcher or sensor
	int row, col;
	if (mcWeaponPanel.ButtonContainingPoint(lastMousePos, row, col)) 
	{
		if (tcLauncher* launcher = mpHookedGameObj->GetLauncher(row))
		{
			if (launcher->mpChildDBObj)
			{
				hintText = launcher->mpChildDBObj->mzDescription;
			}
			else
			{
				hintText = ""; // nothing loaded in launcher
			}
			xhint = lastMousePos.x + 10;
			yhint = (int)mcWeaponPanel.mar[row][0].GetTop() + 2;

            if (launcher->IsLoading()) // add time left to complete load/unload
            {
                wxString loadTime;
                float opTime_s = launcher->GetLoadingTime();
                if (opTime_s < 60.0f)
                {
                    loadTime.Printf(" (%.0f s)", floorf(opTime_s));
                }
                else
                {
                    loadTime.Printf(" (%.0f min)", floorf(0.01666f*opTime_s + 0.5f));
                }
                hintText += loadTime.c_str();
            }
		} 
		
	}
	else if (mcSensorPanel.ButtonContainingPoint(lastMousePos, row, col))
	{
		unsigned int sensorIdx = (unsigned int)GetSensorIndexForRow(row);
		if (tcSensorState* sensor = platformObj->GetSensorMutable(sensorIdx))
		{
			if (sensor->mpDBObj)
			{
				hintText = sensor->mpDBObj->mzDescription;
			}
			else
			{
				hintText = "Error";
			}
			xhint = lastMousePos.x + 10;
			yhint = (int)mcSensorPanel.mar[row][0].GetTop() + 2;
		}
	} 
    else if (formationFlagRect.ContainsPoint(lastMousePos.x, lastMousePos.y))
    {
        if (platformObj->formation.isActive)
        {
            long leaderId = platformObj->GetFormationLeader();
            if (tcGameObject* leader = simState->GetObject(leaderId))
            {
                if (leader->IsOwnAlliance())
                {
                    hintText = "Leader ";
                    hintText += leader->mzUnit.c_str();
                }
                else
                {
                    hintText = "Target";
                }
                xhint = lastMousePos.x + 10;
                yhint = lastMousePos.y;
            }
        }
    }
    else if (countryFlagRect.ContainsPoint(lastMousePos.x, lastMousePos.y))
    {
        if (mpHookedGameObj->GetEnsign() != 0)
        {
            hintText = mpHookedGameObj->GetCountry();
            xhint = lastMousePos.x + 10;
            yhint = lastMousePos.y;
        }
    }

	if ((hintText.size() > 0) && (popupHint == 0))
	{
		popupHint = new tcPopupText(hintText, wxPoint(xhint, yhint), this);
	}
}

/**
*
*/
void tcObjectControl::UpdateSymbolList() 
{
	symbolList.clear();

    bool bFound = (simState->GetPlatformState(mnHookID, mpHookedGameObj) != 0);  

    if (!bFound) // hooked a sensor track in multiplayer client
    {
        mcAIPanel.SetAIData(0);
        return;
    }

    if (mpHookedGameObj == 0) 
    {
        return; // no valid hooked obj
    } 

    if (!mpUserInfo->IsOwnAlliance(mpHookedGameObj->GetAlliance())) 
    {
        return;
    }

    AddSensorRangeCircles();

    AddWeaponRangeCircles();

    AddFlightRangeCircle();

#ifdef _DEBUG
    AddTrackHistory();
#endif
}

/**
* Updates weapon ranges (dynamic range for missiles)
*/
void tcObjectControl::UpdateWeaponRanges(tcPlatformObject* platform)
{    
    unsigned int t = tcTime::Get()->Get30HzCount();

    unsigned int dt = t - lastWeaponRangeUpdate;

    const float speedThreshold_kts = 10.0f;
    const float altitudeThreshold_m = 50.0f;

    bool doUpdate = (mnHookID != mnPreviousHookID) || 
        ((dt > 45) &&  
         (
         (fabsf(platform->mcKin.mfSpeed_kts - lastWeaponRangeSpeed_kts) > speedThreshold_kts) ||
         (fabsf(platform->mcKin.mfAlt_m - lastWeaponRangeAltitude_m) > altitudeThreshold_m)
        ));

    if (!doUpdate)
    {
        wxASSERT(platform->GetLauncherCount() == launcherRange_km.size());
        return;
    }

    lastWeaponRangeUpdate = t;
    lastWeaponRangeSpeed_kts = platform->mcKin.mfSpeed_kts;
    lastWeaponRangeAltitude_m = platform->mcKin.mfAlt_m;

    unsigned int nLaunchers = platform->GetLauncherCount();

    long targetId = platform->GetBrain()->GetTarget();

    launcherRange_km.clear();
    launcherColor.clear();
    for (unsigned int n=0; n<nLaunchers; n++)
    {
        tcLauncher* launcher = platform->GetLauncher(n);
        if ((launcher->mnCurrent > 0) && !launcher->IsDamaged())
        {
            float range_km = 0;
            float color = 0xFFFFFFFF;

            if (tcMissileDBObject* missileDBObj = 
                dynamic_cast<tcMissileDBObject*>(launcher->mpChildDBObj))
            {
                float minEval_km = 2.0f;
                float maxEval_km = std::min(missileDBObj->maxRange_km, 3000.0f);
                float evalStep_km = std::max(0.01f * maxEval_km, 1.0f);
                float launchSpeed_kts = mpHookedGameObj->mcKin.mfSpeed_kts;
                float launchAlt_m = mpHookedGameObj->mcKin.mfAlt_m;
                float targetAlt_m = 10.0f;
                bool logData = false;

                tcSensorMapTrack targetTrack;
                if (simState->GetTrack(targetId, platform->GetAlliance(),targetTrack))
                {
                    targetAlt_m = targetTrack.mfAlt_m;
                }

                const unsigned int nEvalSteps = 7;
                range_km = tcMissileObject::EstimateRangeFaster(minEval_km, maxEval_km, nEvalSteps, launchSpeed_kts, launchAlt_m, targetAlt_m, missileDBObj);
                color = 0xFFB01010;
            }
            else if (tcBallisticDBObject* ballisticDBObj = 
                dynamic_cast<tcBallisticDBObject*>(launcher->mpChildDBObj))
            {
                range_km = ballisticDBObj->CalculateRangeKm(platform->mcKin.mfAlt_m, C_KTSTOMPS*platform->mcKin.mfSpeed_kts);
                color = 0xFFB04010;
            }
            else if (tcTorpedoDBObject* torpDBObj = 
                dynamic_cast<tcTorpedoDBObject*>(launcher->mpChildDBObj))
            {
                range_km = torpDBObj->maxRange_km;
                color = 0xFF010130;
            }

            launcherRange_km.push_back(range_km);
            launcherColor.push_back(color);
        }
        else
        {
            launcherRange_km.push_back(0);
            launcherColor.push_back(0);
        }
    }

    wxASSERT(launcherRange_km.size() == nLaunchers);
    wxASSERT(launcherColor.size() == nLaunchers);
}


/**
* For aircraft add a circle showing flight range based on 
* current flight conditions (speed, altitude, fuel)
*/
void tcObjectControl::AddFlightRangeCircle()
{
    tcAirObject* air = dynamic_cast<tcAirObject*>(mpHookedGameObj);
    if (air == 0) return;

    tcAeroAirObject* jet = dynamic_cast<tcAeroAirObject*>(mpHookedGameObj);

    float speed_mps = 0;
    float fuelRate_kgps = 0;

    if (jet != 0)
    {
        // for aero model, use the steady-state speed for current conditions
        jet->CalculateSpeedParams(jet->mcKin.mfAlt_m, jet->GetThrottleFraction(),
			speed_mps, fuelRate_kgps, jet->GetDamageLevel(), jet->mpDBObject);
    }
    else
    {
        fuelRate_kgps = air->GetCurrentFuelRate();
        speed_mps = air->mcKin.mfSpeed_kts*C_KTSTOMPS;
    }

	if (fuelRate_kgps == 0) return; // infinite fuel, don't draw range ring
    wxASSERT(fuelRate_kgps > 0);

    if (air->fuel_kg > 0)
    {
        float time_s = air->fuel_kg / fuelRate_kgps;
        float distance_m = speed_mps*time_s;

        MapSymbolInfo symbol;

        symbol.mfLat_rad = air->mcKin.mfLat_rad;
        symbol.mfLon_rad = air->mcKin.mfLon_rad;
        symbol.mfLat2_rad = 0;
        symbol.mfLon2_rad = 0;

        float rangeX_rad = 2.0f*distance_m*C_MTORAD/
            cosf((float)air->mcKin.mfLat_rad);
        float rangeY_rad = 2.0f*distance_m*C_MTORAD;
        symbol.mfLatExtent_rad = rangeY_rad;
        symbol.mfLonExtent_rad = rangeX_rad;
        symbol.mfArcCenter_deg = 0; // wrt North
        symbol.mfArcLength_deg = 360.0f;
        symbol.mnColor = 0x80000000;

        symbolList.push_back(symbol);
    }


}

void tcObjectControl::AddSensorRangeCircles()
{
    tcPlatformObject* platformObj = dynamic_cast<tcPlatformObject*>(mpHookedGameObj);
    if (platformObj == 0) 
    {
        return;
    }

    size_t nSensors = platformObj->GetSensorCount();
    
    for(size_t n=0; n<nSensors; n++) 
    {
        const tcSensorState* pSensorState = platformObj->GetSensor(n);
        const tcRadar* pRadarSS = dynamic_cast<const tcRadar*>(pSensorState);
		wxASSERT(pSensorState);
        bool bActive = pSensorState->IsActive() ? true : false;
        if ((pRadarSS)&&(bActive)) 
        {
			MapSymbolInfo symbol;

            symbol.mfLat_rad = mpHookedGameObj->mcKin.mfLat_rad;
            symbol.mfLon_rad = mpHookedGameObj->mcKin.mfLon_rad;
            symbol.mfLat2_rad = 0;
            symbol.mfLon2_rad = 0;

            float fRangeX_rad = 2.0f*pRadarSS->mpDBObj->mfMaxRange_km*C_KMTORAD/
                cosf((float)mpHookedGameObj->mcKin.mfLat_rad);
            float fRangeY_rad = 2.0f*pRadarSS->mpDBObj->mfMaxRange_km*C_KMTORAD;
            symbol.mfLatExtent_rad = fRangeY_rad;
            symbol.mfLonExtent_rad = fRangeX_rad;

            float sensorAz_deg = (mpHookedGameObj->mcKin.mfHeading_rad + pRadarSS->mountAz_rad) 
                * C_180OVERPI;
            symbol.mfArcCenter_deg = sensorAz_deg; // wrt North
            symbol.mfArcLength_deg = pRadarSS->mpDBObj->mfFieldOfView_deg;
            if (symbol.mfArcLength_deg < 360.0f) 
            {
                symbol.mfArcLength_deg *= 0.95f; // sector distortion issue, lat based?
            }

            bool bDetectsAir = pRadarSS->mpDBObj->mbDetectsAir;
            bool bDetectsPlatform = pRadarSS->mpDBObj->mbDetectsSurface;
            if (bDetectsAir) 
            {
                symbol.mnColor = bDetectsPlatform ?  0x80FFFF88 : 0x808888FF;
            }
            else 
            {
                symbol.mnColor = 0x8088FF88;
            }
            
			symbolList.push_back(symbol);
        }
    }
}

/**
* If object with position history is hooked and option enabled, add track history lines for display
*/
void tcObjectControl::AddTrackHistory()
{
    tcSurfaceObject* surface = dynamic_cast<tcSurfaceObject*>(mpHookedGameObj);
    if (surface == 0) 
    {
        return;
    }

    const std::deque<tcPoint>& positionHistory = surface->GetPositionHistory();

    if (positionHistory.size() == 0) return;

    float x1 = surface->mcKin.mfLon_rad;
    float y1 = surface->mcKin.mfLat_rad;
    for (size_t n=0; n<positionHistory.size(); n++)
    {
        MapSymbolInfo symbol;

        symbol.mfLon_rad = x1;
        symbol.mfLat_rad = y1;
        symbol.mfLon2_rad = positionHistory[n].x;
        symbol.mfLat2_rad = positionHistory[n].y;

        x1 = positionHistory[n].x;
        y1 = positionHistory[n].y;

        symbol.mnColor = 0x80B0B0B0;
        symbolList.push_back(symbol);
    }
}


void tcObjectControl::AddWeaponRangeCircles()
{
    tcPlatformObject* platformObj = dynamic_cast<tcPlatformObject*>(mpHookedGameObj);
    if (platformObj == 0) 
    {
        return;
    }

    UpdateWeaponRanges(platformObj);


	// determine if cursor is over launcher name. If so, highlight range circle 
	unsigned int highlightLauncherIdx = 9999;
	int row, col;
	if (mcWeaponPanel.ButtonContainingPoint(lastMousePos, row, col)) 
	{
		if (tcLauncher* launcher = mpHookedGameObj->GetLauncher(unsigned int(row)))
		{
			if ((launcher->mpChildDBObj != 0) && (col == 0))
			{
				highlightLauncherIdx = (unsigned int)row;
			}
		}
	}


    unsigned int nLaunchers = platformObj->GetLauncherCount();

    for(unsigned int i=0; i<nLaunchers; i++) 
    {
        tcLauncher* launcher = platformObj->GetLauncher(i);
        if ((launcher->mnCurrent > 0) && !launcher->IsDamaged())
        {
			MapSymbolInfo symbol;

            symbol.mfLat_rad = mpHookedGameObj->mcKin.mfLat_rad;
            symbol.mfLon_rad = mpHookedGameObj->mcKin.mfLon_rad;
            symbol.mfLat2_rad = 0;
            symbol.mfLon2_rad = 0;

            float range_km = launcherRange_km[i];
            unsigned int color = launcherColor[i];


            float fRangeX_rad = 2.0f* range_km * C_KMTORAD/
                cosf((float)mpHookedGameObj->mcKin.mfLat_rad);
            float fRangeY_rad = 2.0f* range_km * C_KMTORAD;

            symbol.mfLatExtent_rad = fRangeY_rad;
            symbol.mfLonExtent_rad = fRangeX_rad;

            float az_deg = C_180OVERPI * (launcher->GetSectorCenter() +
                mpHookedGameObj->mcKin.mfHeading_rad);
            float fov_deg = C_180OVERPI * launcher->GetSectorWidth();
            if (fov_deg < 360.0f) 
            {
                fov_deg *= 0.95f; // sector distortion issue, lat based?
            }
            symbol.mfArcCenter_deg = az_deg; // wrt North
            symbol.mfArcLength_deg = fov_deg;

            symbol.mnColor = color;

			if (i == highlightLauncherIdx)
			{
				symbol.mnColor = 0xFFFFFFFF;
			}

            if (range_km > 0)
			{
				symbolList.push_back(symbol);
			}
        }
    }

}


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

tcObjectControl::tcObjectControl(wxWindow *parent, 
                                 const wxPoint& pos, const wxSize& size, 
                                 const wxString& name,
								 tc3DWindow2* graphicsHost) :
    tc3DWindow2(parent, pos, size, name, graphicsHost),
    mnHookID(NULL_INDEX),
    mnPreviousHookID(NULL_INDEX),
    mnLaunchers(0),
    mpHookedGameObj(0),
    mpUserInfo(0),
	isMouseOver(false),
	lastMousePos(0, 0),
	lastMoveTime(0),
	hintActive(false),
	hintDelay(20),
	popupHint(0),
	isRowToSensorUpdated(false),
    units(tcUnits::Get()),
    panely(23.0f),
    countryFlagRect(0, 0, 0, 0),
    cycleHookLeft(0),
    cycleHookRight(0),
    lastWeaponRangeUpdate(0),
    lastWeaponRangeSpeed_kts(-9999.0f),
    lastWeaponRangeAltitude_m(-9999.0f)
{
    simState = tcSimState::Get();
    mpCommandInterface = tcCommandQueue::Get();

	mpOptions = tcOptions::Get();

    InitControls();
    InitializeGroupButtons();

    SetBorderDraw(true);
    if (tcOptions::Get()->renderSurfaceLevel > 1)
    {
        SetUseRenderSurface(true);
        SetRenderSurfaceUpdateInterval(3);
    }

}

tcObjectControl::~tcObjectControl() 
{
    // delete controls
    size_t nControls = controls.size();
    for (size_t n=0; n<nControls; n++)
    {
        delete controls[n];
    }
}
