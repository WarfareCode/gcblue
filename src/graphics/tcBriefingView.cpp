/** 
**  @file tcBriefingView.cpp 
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

#include "tcBriefingView.h"
#include "tcSimPythonInterface.h"
#include "tcScenarioInterface.h"
#include "common/tinyxml.h"
#include "tcUserInfo.h"


BEGIN_EVENT_TABLE(tcBriefingView, tcXmlWindow)

END_EVENT_TABLE()

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using scriptinterface::tcSimPythonInterface;
using scriptinterface::tcScenarioInterface;

void tcBriefingView::Draw() 
{
    StartDraw();

	tcScenarioInterface* scenarioInterface = tcSimPythonInterface::Get()->GetScenarioInterface();
	wxASSERT(scenarioInterface);

	Vec4 color(0.6f, 1, 0.6f, 1);

	int userAlliance = tcUserInfo::Get()->GetOwnAlliance();

	const std::string& briefingText = scenarioInterface->GetSimpleBriefing(userAlliance);

    float x = 65.0f;
    float y = 50.0f;
	float fontSize;
    if (mnWidth > 1200)
	{
		fontSize = 18.0f;
	}
	else if (mnWidth > 1000)
	{
		fontSize = 16.0f;
	}
	else
	{
		fontSize = 14.0f;
	}

	DrawTextR(briefingText.c_str(), x, y, defaultFont.get(), color, fontSize,
		LEFT_TOP, 0);

	FinishDraw();    

}


/**
* @param surfaceHost tcWindow to share surface of
*/
tcBriefingView::tcBriefingView(wxWindow *parent, 
                             const wxPoint& pos, const wxSize& size, const wxString& name, tc3DWindow2* host) 
                             : tcXmlWindow(parent, pos, size, "xml/briefing_view.xml", name, host)
{
    if (config == 0)
    {
        fprintf(stderr, "tcBriefingView::tcBriefingView - NULL xml config node\n");
        return;
    }

	/*
    TiXmlNode* root = config->FirstChild("Window");
    if (!root)
    {
        std::cerr << "tcBriefingView::tcBriefingView - Missing top level <Window> tag\n";
        return;
    }
	*/

}

tcBriefingView::~tcBriefingView() 
{
}


