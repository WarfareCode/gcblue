/**  
**  @file tcCreditView.cpp
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


#include "tcCreditView.h"
#include "aerror.h"
#include "tcString.h"
#include "wxcommands.h"
#include "tcTime.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif 

void tcCreditView::AddCredit(const tcString& s, float afTrailSpace, int effect) 
{
    if (mnCredits >= MAX_CREDITS) {return;}
    maCredit[mnCredits].mfTrailSpace = afTrailSpace;
    maCredit[mnCredits].mnEffect = effect;
    maCredit[mnCredits++].mzCaption = s;
}
/*******************************************************************************/
void tcCreditView::Init()
{

    tcString s;

    s = "- - - C R E D I T S - - -";
    AddCredit(s, 60.0f, 1);


    s = "Dewitt";
    AddCredit(s, 25.0f, 1);

    s = "Lead Developer\n";
    AddCredit(s, 40.0f, 0);

    s = "Amram";
    AddCredit(s, 25.0f, 1);

    s = "Assistant Meddler\n";
    AddCredit(s, 80.0f, 0);

    s = "- - - 3D art - - -"; 
    AddCredit(s, 25.0f, 1);

    s = "Beldon"; 
    AddCredit(s, 25.0f, 1);

    s = "Gabriel Toma";
    AddCredit(s, 25.0f, 1);

    s = "Guido Militello"; 
    AddCredit(s, 25.0f, 1);

    s = "GulfKnight"; 
    AddCredit(s, 25.0f, 1);

    s = "Jason Simpson"; 
    AddCredit(s, 25.0f, 1);

    s = "Marcelo Caceres (op4_delta)"; 
    AddCredit(s, 25.0f, 1);

    s = "Pere"; 
    AddCredit(s, 25.0f, 1);

    s = "Raven"; 
    AddCredit(s, 25.0f, 1);

    s = "Ryan Crierie"; 
    AddCredit(s, 25.0f, 1);

    s = "TLAM Strike"; 
    AddCredit(s, 25.0f, 1);

    s = "Urwumpe"; 
    AddCredit(s, 25.0f, 1);

    s = "ClockMaster"; 
    AddCredit(s, 60.0f, 1);


    s = "- - - Database - - -"; 
    AddCredit(s, 25.0f, 1);

    s = "Amram"; 
    AddCredit(s, 60.0f, 1);


    s = "- - - Python Scripts - - -"; 
    AddCredit(s, 25.0f, 1);

    s = "Dewitt"; 
    AddCredit(s, 25.0f, 1);

    s = "Amram"; 
    AddCredit(s, 60.0f, 1);

    s = "- - - Scenarios - - -"; 
    AddCredit(s, 25.0f, 1);

    s = "Ralf Koelbach";
    AddCredit(s, 60.0f, 1);

    s = "- - - Past GCB Contributors - - -";
    AddCredit(s, 25.0f, 1);

    s = "Dewitt, Guido Militello, Amram, Pit, Raven58, Dust";
    AddCredit(s, 15.0f, 0);
	
    s = "Ryan Crierie, Havoc, Stryker, Suresh, Leigh, Buffie, GoodBeer";
    AddCredit(s, 15.0f, 0);

    s = "Urwumpe, Marcelo, Greengills, TLAM Strike, GulfKnight, Jason Simpson";
    AddCredit(s, 15.0f, 0);

    s = "Grahame Flint, Xavi Rubio, Harpy, Marco Belli, Jason Morris";
    AddCredit(s, 15.0f, 0);

    s = "Paul Daly, Andrew Platfoot, Justin Priestman, Gregg Smith";
    AddCredit(s, 15.0f, 0);


    AddCredit(tcString(""), 50.0f, 2);



    s = "Some 2D art courtesy of U.S. Navy, www.news.navy.mil/view_galleries.asp \n";
    AddCredit(s, 25.0f, 0);

    s = "Some sound effects courtesy of A1 Sound Effects, www.a1freesoundeffects.com\n";
    AddCredit(s, 35.0f, 0);


    s = "Map data based on GTOPO30 archive distributed by the \nLand Processes Distributed Active Archive Center (LP DAAC)\nlpdaac.usgs.gov \n";
    AddCredit(s, 100.0f, 0);

    s = "Thanks to the developers of these software libraries:\n";
    AddCredit(s, 30.0f, 0);

    s = "wxWidgets\n";
    AddCredit(s, 20.0f, 0);
    s =  "www.wxwidgets.org\n";
    AddCredit(s, 30.0f, 0);

    s = "Python\n";
    AddCredit(s, 20.0f, 0);
    s =  "www.python.org\n";
    AddCredit(s, 30.0f, 0);

    s = "Boost Python\n";
    AddCredit(s, 20.0f, 0);
    s =  "www.boost.org\n";
    AddCredit(s, 30.0f, 0);

    s = "SQLite\n";
    AddCredit(s, 20.0f, 0);
    s =  "www.sqlite.org\n";
    AddCredit(s, 30.0f, 0);

    s = "Truevision3D\n";
    AddCredit(s, 20.0f, 0);
    s =  "www.truevision3d.com\n";
    AddCredit(s, 30.0f, 0);

    s = "Special thanks to:";
    AddCredit(s, 30.0f, 0);

    s = "WarfareSims.com\n";
    AddCredit(s, 30.0f, 0);

    s = "Subsim, www.subsim.com\n";
    AddCredit(s, 30.0f, 0);

    s = "and\n"; 
    AddCredit(s, 30.0f, 0);

    s = "To those who provided feedback and suggestions through e-mail and \nthe GCB discussion forums";
    AddCredit(s, 120.0f, 0);


    s = "GCBLUE II";
    AddCredit(s, 20.0f, 0);

    s = "www.gcblue.com";
    AddCredit(s, 30.0f, 0);

    s = "Copyright (C) 2003-2012\n";
    AddCredit(s, 60.0f, 0);

    Rewind();
}

/*******************************************************************************/
void tcCreditView::Draw() 
{
    StartDraw();

    //static WCHAR szwchar[256];
    unsigned int nDeltaTime = tcTime::Get()->Get30HzCount() - mnStartTime;

	const float height = float(mnHeight);
    float fY = 2*0.35f*(float)nDeltaTime;
    float fX = 0.5f*(float)mnWidth;

    //const UINT32 nColorFade = 0x8E328032;
    //const UINT32 nColorBright = 0xFE64FF64;
	const Vec4 nColorFade(0.2f, 0.5f, 0.2f, 0.5f);
	const Vec4 nColorBright(0.4f, 1.0f, 0.4f, 1.0f);

    //mpBrush->SetColor(Color(nColorBright)); // font color
    //DrawTextCentered(pGraphics, mpFont, mpBrush, crawlstring.GetBuffer(), fX,fY);
    static int nFlashId = -1;
    static bool bFlash = false;
    static unsigned int snFocusTime;
    static tcString szFocus;

    // reset static variables if rewind occurred
    if (mbDrawRewind) 
    { 
        nFlashId = -1;
        bFlash = false;
        mbDrawRewind = false;
    }

    if (bFlash) 
    {
        if (nFlashId >= 0) {szFocus = maCredit[nFlashId].mzCaption;}
        snFocusTime = tcTime::Get()->Get30HzCount();
        //mpBrush->SetColor(Color(255,255,255,255));
        //pGraphics->FillRectangle(mpBrush,0,0,mnWidth,mnHeight);
        //tcSound::Get()->PlayEffect("Explosion2");
    }
    if (nFlashId >= 0) 
    {
//        unsigned int nDeltaFocusTime = (tcTime::Get()->Get30HzCount() - snFocusTime);
    }
    for (int n=0;n<(int)mnCredits;n++) 
    {
        tcString s = maCredit[n].mzCaption;
        const float fEffectZone = 10.0f;
        float dyeffect = fEffectZone - fY;
        if ((dyeffect >= 0)&&(dyeffect <= fEffectZone)) 
		{ 
			for (float dx = 20.0f; dx <= 40.0f; dx += 10.0f)
			{
				DrawText(s.GetBuffer(), fX + dx*dyeffect, fY, defaultFont.get(), 
					nColorFade, 12.0f, CENTER_CENTER);
				DrawText(s.GetBuffer(), fX - dx*dyeffect, fY, defaultFont.get(), 
					nColorFade, 12.0f, CENTER_CENTER);
			}
        }
        else if ((fY >= 0) && (fY <= height))
        { 
            if ((n > nFlashId)&&(maCredit[n].mnEffect == 1))
            {
                nFlashId = n;
                bFlash = true;
            }
            else 
            {
                bFlash = false;
            }
            
			float fontSize = 12.0;
            if (maCredit[n].mnEffect == 1)
            {
                fontSize = 18.0f; //pFont = mpFontLarge;
            }
            else if (maCredit[n].mnEffect == 2)
            {
                fontSize = 12.0f; //pFont = mpFontSmall;
            }

			DrawText(s.GetBuffer(), fX + 1.0f, fY + 1.0f, defaultFont.get(), 
				nColorFade, fontSize, CENTER_CENTER);

			DrawText(s.GetBuffer(), fX, fY, defaultFont.get(), 
				nColorBright, fontSize, CENTER_CENTER);
        }
        fY -= maCredit[n].mfTrailSpace;
    }

#ifdef _DEBUG
	static unsigned int frameCount = 0;
	wxString infoString = wxString::Format("%d Y:%f\n", frameCount, fY);
	frameCount++;
	DrawText(infoString.c_str(), 10.0, 20.0, defaultFont.get(), 
				nColorBright, 16.0f, LEFT_BASE_LINE);
#endif


    // rewind after credits are done crawling
    if (fY > height + 100.0f)
    {
        Rewind();
    }

	FinishDraw();
}

/**
* return to start view on left mouse click.
*/
void tcCreditView::OnLButtonDown(wxMouseEvent& event)
{
    wxCommandEvent command(wxEVT_COMMAND_BUTTON_CLICKED, ID_STARTVIEW) ;    
    command.SetEventObject(this);
    AddPendingEvent(command);
}

void tcCreditView::OnSize(wxSizeEvent& event)
{
    tc3DWindow2::OnSize(event);

    wxSize size = event.GetSize();
}

void tcCreditView::Rewind() 
{
    mnStartTime = tcTime::Get()->Get30HzCount();
    mbDrawRewind = true;
}



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

tcCreditView::tcCreditView(wxWindow *parent, 
                           const wxPoint& pos, const wxSize& size, 
                           const wxString& name) 
                           : tc3DWindow2(parent, pos, size, name) 
{
    mnCredits = 0;
    mbDrawRewind = false;

    SetBorderDraw(true);

    Init();
}

tcCreditView::tcCreditView(tc3DWindow2 *parent, 
                           const wxPoint& pos, const wxSize& size, 
                           const wxString& name) 
                           : tc3DWindow2(parent, pos, size, name, parent) 
{
    mnCredits = 0;
    mbDrawRewind = false;

    SetBorderDraw(true);

    Init();
}

tcCreditView::~tcCreditView() 
{

}


