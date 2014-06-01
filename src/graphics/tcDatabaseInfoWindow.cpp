/** 
**  @file tcDatabaseInfoWindow.cpp 
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

#include "tcDatabaseInfoWindow.h"
#include "tcDatabaseObject.h"
#include "tcPlatformDBObject.h"
#include "tcLauncherDBObject.h"
#include "tcMissileDBObject.h"
#include "tcTorpedoDBObject.h"
#include "tc3DModel.h"
#include "tcSensorMap.h"
#include "tcSimState.h"
#include "common/tinyxml.h"
#include "tcTime.h"
#include "tcDatabaseInfoPanel.h"
#include "tcTexture2D.h"
#include "tcGeometry.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_EVENT_TABLE(tcDatabaseInfoWindow, tcXmlWindow)
    EVT_COMMAND(86, wxEVT_COMMAND_BUTTON_CLICKED, tcDatabaseInfoWindow::OnCloseCommand)
END_EVENT_TABLE()


using database::tcDatabaseObject;


tc3DWindow2* tcDatabaseInfoWindow::parent = 0;


void tcDatabaseInfoWindow::SetParent(tc3DWindow2* win)
{
	parent = win;
}


void tcDatabaseInfoWindow::Draw() 
{
    if (IsPopup())
    {
        if (CloseRequested())
        {
            DestroyWindow();
            return;
        }
    }
 //   if (drawCount++ % 2 != 0) return;

    StartDraw();

	//if (!IsBackgroundEnabled())
	//{
	//	DrawRectangleR(0, 0, mnWidth, mnHeight, Vec4(0.15, 0.15, 0.15, 1.0f), 
	//		FILL_ON);
	//}

	DrawDatabaseInfo();

	FinishDraw();
}


void tcDatabaseInfoWindow::DrawDatabaseInfo()
{
	wxString s;

	tcDatabaseObject* databaseObj = GetDatabaseObject();

	if (databaseObj != 0)
	{
        s.Printf("%s", databaseObj->GetDisplayName());
	}
	else
	{
        if (IsPopup())
        {
		    s.Printf("No info available");
        }
        else
        {
            s.Printf("");
        }
	}

    float textx = 10.0f;
	float maxWidth = float(mnWidth) - textx - 5.0f;
    float texty = 23.0f;
	tcRect textBox;

	Vec4 color(0.4f, 1.0f, 0.4f, 1.0f);

	DrawTextR(s.c_str(), textx, texty, 
			boldFont.get(), color, fontSizeLarge, LEFT_BASE_LINE, maxWidth, textBox);

    texty += textBox.Height() + 5.0f;

	if (databaseObj == 0) return;

    DrawDatabaseImages();

    textx = xImage + 10.0f;
    texty = float(mnHeight) - 15.0f;
    const std::string artists(databaseObj->Get3DModel()->GetAuthor());
    if ((artists.size() > 0) && IsEmbedded())
    {
        PrintText(textx, texty, "3D Artist(s): %s", artists.c_str());
    }

}



void tcDatabaseInfoWindow::PrintText(float x, float& y, const char* formatString, ...)
{
    enum {STR_LENGTH = 1024};
    static char textBuffer[STR_LENGTH];
    static Vec4 color(0.4f, 1.0f, 0.4f, 1.0f);
    static tcRect textBox;

    const float textFontSize = 12.0f;

    if (y > float(mnHeight) - 15.0f) return;

    va_list arguments;

    va_start(arguments, formatString);
    _vsnprintf_s(textBuffer, sizeof(textBuffer), _TRUNCATE, formatString, arguments);
    va_end(arguments);

    float maxWidth = (y < yImage) ? xImage - x : float(mnWidth) - x;

    DrawTextR(textBuffer, x, y, 
			defaultFont.get(), color, textFontSize, LEFT_CENTER, maxWidth, textBox);

    y += textBox.Height() + 2.0f;
    
}

void tcDatabaseInfoWindow::DrawDatabaseImages()
{    
    float imageWidth = 150.0f;
    float imageHeight = 100.0f;
    float imagex = float(mnWidth) - imageWidth - 10.0f;
    float imagey = 25.0f;

    if (IsEmbedded())
    {
        imageWidth = 300.0f;
        imageHeight = 200.0f;
        imagex = float(mnWidth) - imageWidth - 10.0f;
        imagey = 25.0f;
    }

    xImage = imagex - 5.0f;
    yImage = imagey + imageHeight;


    size_t nImages = imageList.size();
    if (nImages > 0)
    {
        DrawImageR(imageList[currentImageIdx].get(), imagex, imagey, imageWidth, imageHeight, ALIGN_BOTTOM_LEFT);
        DrawRectangleR(imagex, imagey, imageWidth, imageHeight, Vec4(1, 1, 1, 0.5));

        // cycle through images if embedded, otherwise just show the first one
        if (IsEmbedded())
        {
            unsigned int t = tcTime::Get()->Get30HzCount();
            if (t - imageTime > 90)
            {
                currentImageIdx = (currentImageIdx + 1) % nImages;
                imageTime = t;
                tcSound::Get()->PlayEffect("MutedBeep");
            }
        }
    }
}




database::tcDatabaseObject* tcDatabaseInfoWindow::GetDatabaseObject()
{
	if (databaseClassName.size() > 1)
	{
		return tcDatabase::Get()->GetObject(databaseClassName);
	}

	tcSimState* simState = tcSimState::Get();
	tcGameObject* obj = simState->GetObject(objId);
	if ((obj != 0) && (obj->IsOwnAlliance()))
	{
		databaseClassName = obj->mpDBObject->mzClass.c_str();
		return obj->mpDBObject;
	}
	else
	{
		tcSensorMap* sensorMap = simState->GetSensorMap();
		wxASSERT(sensorMap != 0);
		tcSensorMapTrack* track = sensorMap->GetSensorMapTrack(objId, tcUserInfo::Get()->GetOwnAlliance());
		if (track)
		{
			return tcDatabase::Get()->GetObject(track->GetDatabaseId());
		}
		else
		{
			return 0;
		}
	}
}


bool tcDatabaseInfoWindow::IsEmbedded() const
{
    return (viewMode == EMBED);
}

bool tcDatabaseInfoWindow::IsPopup() const
{
    return (viewMode == POPUP);
}


void tcDatabaseInfoWindow::LoadImageList()
{
    imageList.clear();

    database::tcDatabaseObject* databaseObject = GetDatabaseObject();
    if (databaseObject == 0) return;

    wxArrayString parsedImageList = databaseObject->GetParsedImageList();
    for (size_t n=0; n<parsedImageList.size(); n++)
    {
        wxString& fileName = parsedImageList[n];
        boost::shared_ptr<tcTexture2D> tex(tc3DWindow2::LoadTexture(fileName.c_str()));
        if (tex.get() != 0) imageList.push_back(tex);
    }

    currentImageIdx = 0;
}


/**
* Close and destroy window at next safe opportunity
*/
void tcDatabaseInfoWindow::OnCloseCommand(wxCommandEvent& event)
{
    DestroyWindow();
}


void tcDatabaseInfoWindow::OnLButtonDown(wxMouseEvent& event)
{
    tcXmlWindow::OnLButtonDown(event);
}



void tcDatabaseInfoWindow::OnLButtonUp(wxMouseEvent& event)
{
    tcXmlWindow::OnLButtonUp(event);
}

void tcDatabaseInfoWindow::OnLeaveWindow(wxMouseEvent& event)
{

}

/**
* Update mouseover status of slots
*/
void tcDatabaseInfoWindow::OnMouseMove(wxMouseEvent& event)
{
    tcXmlWindow::OnMouseMove(event);
}


void tcDatabaseInfoWindow::SetDatabaseClassName(const std::string& className)
{
    databaseClassName = className;
    LoadImageList();

	infoPanel->SetDatabaseClassName(className);
}

void tcDatabaseInfoWindow::SetDatabaseObject(long id)
{
	objId = id;
	databaseClassName = "";

    currentImageIdx = 0;
    imageTime = tcTime::Get()->Get30HzCount();

    LoadImageList();

	infoPanel->SetDatabaseObject(id);
}



/**
* if hostParent argument is not used then static method SetParent must be called first
*/
tcDatabaseInfoWindow::tcDatabaseInfoWindow(const wxPoint& pos, const wxString& configFile, const wxString& name, tc3DWindow2* hostParent) 
                             : tcXmlWindow(hostParent, pos, wxSize(10, 10), configFile, name, hostParent),
	drawCount(0),
	objId(-1),
	databaseClassName(""),
    currentImageIdx(0),
    imageTime(0),
    xImage(0),
    yImage(0)
{

	wxASSERT(hostParent != 0);

    viewMode = (hostParent == parent) ? POPUP : EMBED;

	// put gui window on top
	SetBaseRenderBin(hostParent->GetBaseRenderBin() + windowLayer*10);
	wxWindow::Raise();

	windowLayer++;

    TiXmlNode* root = config->FirstChild("Window");
    if (!root)
    {
        fprintf(stderr, "tcDatabaseInfoWindow::tcDatabaseInfoWindow - Missing top level <Window> tag\n");
        return;
    }

//	TiXmlNode* current = root;


    if (viewMode == EMBED)
    {
	    SetSize(pos.x, pos.y, 600.0f, 400.0f); // set all size params
    }
    else
    {
        SetDragable(true); // enable window drag for popup
    }
	

    SetBackgroundColor(Vec4(0.2f, 0.2f, 0.2f, 0.5f));
    SetBackgroundDraw(true);
	SetActive(true);



	int panelWidth = mnWidth - 175;
	int panely = 25;
	int panelHeight = mnHeight - panely - 10.0f;

	if (viewMode == EMBED)
	{
		panelWidth = mnWidth - 330;
	}

	infoPanel = new tcDatabaseInfoPanel(this, wxPoint(10, panely), wxSize(panelWidth, panelHeight), "DBpanel", this);

    SetBorderDraw(true);
    SetBorderColor(Vec4(0.5, 0.5, 0.5, 0.5));

}

tcDatabaseInfoWindow::~tcDatabaseInfoWindow() 
{
	windowLayer--;
}


