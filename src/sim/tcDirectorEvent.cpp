/**  
**  @file tcDirectorEvent.cpp
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
/// @file tcDirectorEvent.cpp source file for tcDirectorEvent class and derived classes


#include "stdwx.h" // precompiled header file

#ifndef WX_PRECOMP
#include "wx/wx.h" 
#endif

#include "tcDirectorEvent.h"
#include "tcMapObject.h"
#include "tcTacticalMapView.h"
#include "tcWorldMapView.h"
#include "tcSound.h"
#include "tcConsoleBox.h"
#include "tc3DViewer.h"
#include "math_constants.h"
#include "tcMessageInterface.h"

//#include <osgText/Text>
//#include <osg/Vec3> // tc3DTextEvent

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


/********** tcDirectorEvent ****************/
wxWindow* tcDirectorEvent::eventHandler = NULL;

void tcDirectorEvent::Update(double t)
{
}

tcDirectorEvent::tcDirectorEvent(double start, double stop)
{
    eventName = "Undefined";
    eventStart = start;
    eventStop = stop;
    triggered = false;
}

tcDirectorEvent::tcDirectorEvent() 
: eventStart(1e15), eventStop(2e15), triggered(false)
{
}

tcDirectorEvent::~tcDirectorEvent()
{
}

/********** tcMapEvent ****************/

tcTacticalMapView* tcMapEvent::tacticalMapView = 0;
tcWorldMapView* tcMapEvent::worldMapView = 0;

void tcMapEvent::AttachMapViews(tcTacticalMapView* tmv, tcWorldMapView* wmv)
{
	tacticalMapView = tmv;
	worldMapView = wmv;
}

/**
* static method tcMapEvent::AttachMapViews must be called first
*
* @see tcMapEvent::AttachMapViews
* @param obj pointer to tcMapObject graphical map object
*/
tcMapEvent::tcMapEvent(tcMapObject *obj) 
: mapObject(obj), addedToMap(false)
{
	wxASSERT(tacticalMapView);
	wxASSERT(worldMapView);
}

tcMapEvent::~tcMapEvent()
{
	if (mapObject) delete mapObject;
}






/********** tcMapTextEvent ****************/

void tcMapTextEvent::SetTextAlignment(int mode)
{
    tcMapTextObject* mapTextObject = dynamic_cast<tcMapTextObject*>(mapObject);
    if (mapTextObject != 0)
    {
        mapTextObject->SetTextAlignment(mode);
    }
    else
    {
        wxASSERT(false);
        return;
    }
}

void tcMapTextEvent::SetTextColor(const Vec4& color)
{
    if (mapObject == 0)
    {
        wxASSERT(false);
        return;
    }

    mapObject->SetColor(color);
}

void tcMapTextEvent::SetTextSize(float fontSize)
{
    if (mapObject == 0)
    {
        wxASSERT(false);
        return;
    }

    mapObject->SetFontSize(fontSize);
}

void tcMapTextEvent::Update(double t)
{
    if (t < eventStart) return;
    if (!addedToMap)
    {
        wxASSERT(mapObject);
        tacticalMapView->AddMapObject(mapObject);
        addedToMap = true;
    }
    if (t > eventStop)
    {
        mapObject->SetActive(false);
        return;
    }
    if (effectCode & FADE_MASK) // alpha blend
    {
        double tspan = eventStop - eventStart;
        double dt = t - eventStart;
        double tfract = dt/tspan; // fraction of active time span
        double alpha;
        if (tfract < 0.1)
        {
            alpha = 10*tfract;
        }
        else if (tfract > 0.9f)
        {
            alpha = 10*(1-tfract);
        }
        else
        {
            alpha = 1.0;
        }
       
		Vec4 currentColor = mapObject->GetColor();
		currentColor.w = alpha;
        mapObject->SetColor(currentColor);
    }
}


/**
* effect - bit pos 0, fade in & out enabled
* effect - bit pos 1, enabled - use relative screen coords, disabled - use geo lat/lon
* effect - bit pos 2, disable marker
*/
tcMapTextEvent::tcMapTextEvent(std::string text, double startTime, double endTime, 
                               double lon_deg, double lat_deg, int effect)
 :  tcMapEvent(new tcMapTextObject(text, lon_deg, lat_deg, 
                              (effect & RELATIVE_COORD_MASK) != 0)) 
   , tcDirectorEvent(startTime, endTime)
{
    effectCode = effect;
	mapObject->SetMarkerActive((effect & MARKER_DISABLE_MASK) == 0);
}

tcMapTextEvent::~tcMapTextEvent()
{
}

/********************** tcSoundEvent ***************************/

void tcSoundEvent::Update(double t)
{
}

tcSoundEvent::tcSoundEvent(double start, double stop) 
: tcDirectorEvent(start, stop)
{
}

tcSoundEvent::~tcSoundEvent()
{
}

/********************** tcSoundEffectEvent ***************************/


void tcSoundEffectEvent::Update(double t)
{
    if (t < eventStart)
    {
        triggered = false;
        return;
    }
    if (triggered) return;
    tcSound::Get()->PlayEffect(effectCode);
    triggered = true;
}

tcSoundEffectEvent::tcSoundEffectEvent(double t, const std::string& effect)
: tcSoundEvent(t,t), effectCode(effect) 
{
}

tcSoundEffectEvent::~tcSoundEffectEvent()
{
}


/*************** tcMusicEvent ****************************/


void tcMusicEvent::Update(double t)
{
    if (t < eventStart) return;
    if (triggered) return;
    if (command == "play")
    {
        tcSound::Get()->PlayMusic(song);
        tcSound::Get()->SeekMusic(param);
    }
    else if (command == "pause")
    {
        tcSound::Get()->SetMusicPause(true);
    }
    else if (command == "unpause")
    {
        tcSound::Get()->SetMusicPause(false);
    }
    else if (command == "seek")
    {
        tcSound::Get()->SeekMusic(param);
    }
    else if (command == "volume")
    {
        tcSound::Get()->SetMusicVolume(param);
    }
    triggered = true;
}

tcMusicEvent::tcMusicEvent(std::string aSong, std::string aCommand, double aParam, 
                           double start, double stop)
: tcSoundEvent(start, stop)
{
    song = aSong;
    command = aCommand;
    param = aParam;
}

tcMusicEvent::~tcMusicEvent()
{
}

/***************** tcMessageTextEvent *******************/

void tcMessageTextEvent::Update(double t)
{
    if (t < eventStart) return;
    if (triggered) return;

    tcMessageInterface::Get()->ChannelMessage(channel, message, alliance);

    triggered = true;
}

tcMessageTextEvent::tcMessageTextEvent(const std::string& message_, const std::string& channel_, unsigned int alliance_, double t)
: tcDirectorEvent(t, t),
  message(message_),
  channel(channel_),
  alliance(alliance_)
{

}

tcMessageTextEvent::~tcMessageTextEvent()
{
}

/**************** tcGameCommandEvent ********************/
/**
* Event to send game command
*/


void tcGameCommandEvent::Update(double t)
{
    if (t < eventStart) return;
    if (triggered) return;

    wxASSERT(eventHandler);
    wxCommandEvent command(wxEVT_COMMAND_BUTTON_CLICKED, commandId) ;    
    command.SetEventObject(eventHandler);
    // command.m_extraLong = param; // 2.6.3 code
    command.SetExtraLong(param);
    eventHandler->GetEventHandler()->AddPendingEvent(command);    
    
    triggered = true;
}

tcGameCommandEvent::tcGameCommandEvent(long id, double t, long val)
: tcDirectorEvent(t,t)
{
    commandId = id;
    param = val;
}

tcGameCommandEvent::~tcGameCommandEvent()
{
}

/*************** tcMapViewEvent ***************/
/**
* For lonSpan_rad = 0 theater view is changed
* via the world map
* For lonSpan_rad > 0 the tactical map view is
* changed.
* 
* @see tcTacticalMapView::SetView
* @see tcWorldMapView::ChangeTheater
*/
void tcMapViewEvent::Update(double t)
{
    if (t < eventStart) return;
    if (triggered) return;

    wxASSERT(tacticalMapView);
	wxASSERT(worldMapView);

    tcPoint pCenter;
    pCenter.x = lon_rad;
    pCenter.y = lat_rad;

	if (lonSpan_rad > 0)
	{
        if (setTacticalMap)
        {
		    tacticalMapView->SetView(pCenter, lonSpan_rad);
        }
        else
        {
            worldMapView->SetView(pCenter, lonSpan_rad);
        }
	}
	else
	{
		worldMapView->ChangeTheater(C_180OVERPI*lon_rad, C_180OVERPI*lat_rad);
        worldMapView->SetView(pCenter, C_PIOVER180*120.0f);
	}

    triggered = true;
}

tcMapViewEvent::tcMapViewEvent(double t, 
                               double lon_deg, double lat_deg, double lonSpan_deg, bool tacticalMap)
                               : tcMapEvent(NULL) , tcDirectorEvent(t, t)
{
    lon_rad = C_PIOVER180 * lon_deg;
    lat_rad = C_PIOVER180 * lat_deg;
    lonSpan_rad = C_PIOVER180 * lonSpan_deg;
    setTacticalMap = tacticalMap;
}

tcMapViewEvent::~tcMapViewEvent()
{
}


/********** tcCameraEvent ****************/

//tc3DViewer* tcCameraEvent::viewer = NULL;

void tcCameraEvent::Update(double t)
{
    if (t < eventStart) return;
    if (triggered) return;

//    viewer->SetCameraMode(lookAtTarget, moveWithTarget);
//    viewer->SetHookID(targetID);

    triggered = true;
}

tcCameraEvent::tcCameraEvent(double tStart, double tStop)
: tcDirectorEvent(tStart, tStop)
{
}

tcCameraEvent::~tcCameraEvent()
{
}

/********** tcFlybyCameraEvent *****************/
void tcFlybyCameraEvent::Update(double t)
{
    tcCameraEvent::Update(t);

    if (!triggered) return;
    if (t > eventStop) return;

    //float k = (eventStart == eventStop) ? 0 : (t - eventStart)/(eventStop - eventStart);
    float daz = stopAz - startAz;
    if (daz < -C_PI) daz += C_TWOPI;
    else if (daz > C_PI) daz -= C_TWOPI;
//    float az = startAz + k*daz;

    float del = stopEl - startEl;
    if (del < -C_PI) del += C_TWOPI;
    else if (del > C_PI) del -= C_TWOPI;
//    float el = startEl + k*del;

//    float range = startRange + k*(stopRange - startRange);

    //viewer->SetPolarOffset(az, el, range);
}

tcFlybyCameraEvent::tcFlybyCameraEvent(double tStart, double tStop, long targID, 
                             float az1, float az2, float el1, float el2, 
                             float r1, float r2)
: tcCameraEvent(tStart,tStop)
{
    targetID = targID;
    moveWithTarget = true;
    lookAtTarget = true;

    startAz = az1;
    startEl = el1;
    startRange = r1;
    stopAz = az2;
    stopEl = el2;
    stopRange = r2;
}

tcFlybyCameraEvent::~tcFlybyCameraEvent()
{
}

/********** tcTrackCameraEvent *****************/
void tcTrackCameraEvent::Update(double t)
{
    tcCameraEvent::Update(t);

    if (!triggered) return;
    if (t > eventStop) return;

    //float k = (eventStart == eventStop) ? 0 : (t - eventStart)/(eventStop - eventStart);
//    float x = startX + k*(stopX - startX);
//    float y = startY + k*(stopY - startY);
//    float z = startZ + k*(stopZ - startZ);

    //viewer->SetCartesianOffset(x, y, z);
}

tcTrackCameraEvent::tcTrackCameraEvent(double tStart, double tStop, long targID, 
                   float x1, float x2, float y1, float y2, float z1, float z2 )
: tcCameraEvent(tStart,tStop)
{
    targetID = targID;
    moveWithTarget = true;
    lookAtTarget = true;

    startX = x1;
    startY = y1;
    startZ = z1;
    stopX = x2;
    stopY = y2;
    stopZ = z2;
}

tcTrackCameraEvent::~tcTrackCameraEvent()
{
}

/******** tc3DTextEvent *************/

void tc3DTextEvent::Update(double t)
{
#if 0
    if (t >= eventStop)
    {
        if (unsigned nParents = viewerText->getNumParents())
        {
            wxASSERT(nParents == 1);
            viewer->RemoveText(viewerText.get());
        }
        return;
    }
    else if (t >= eventStart)
    {
        if (viewerText->getNumParents() == 0)
        {        
            viewer->AddText(viewerText.get());
        }
        
        wxSize viewerSize = viewer->GetSize();
        float x = textx * (float)viewerSize.GetWidth();
        float y = texty * (float)viewerSize.GetHeight();
        viewerText->setPosition(osg::Vec3(x,y,0.0f));

        if (effectCode == 1) // alpha blend
        {
            double tspan = eventStop - eventStart;
            double dt = t - eventStart;
            double tfract = (tspan != 0) ? dt/tspan : 1.0f; // fraction of active time span
            double alpha;
            
            const float a = 0.2;
            const float ainv = 1.0/a;

            if (tfract < a)
                alpha = ainv*tfract;
            else if (tfract > (1.0f-a))
                alpha = ainv*(1-tfract);
            else
                alpha = 1.0;

            viewerText->setColor(Vec4(1.0f,1.0f,1.0f,alpha));
        }

    }
#endif
}

/**
* x and y are normalized to screen width and height, e.g. 0.5, 0.5 is center of 
* screen.
*/
tc3DTextEvent::tc3DTextEvent(std::string text, double startTime, double endTime, 
                             float x, float y, float size, int effect)
                             : tcCameraEvent(startTime, endTime)
{
    theText = text;
    fontSize = size;
    textx = x;
    texty = y;
    effectCode = effect;

    //viewerText = new osgText::Text;
    //osgText::Font* font = osgText::readFontFile("fonts/arial.ttf");
    //Vec4 layoutColor(1.0f,1.0f,1.0f,1.0f); 

    //viewerText->setFont(font);
    //viewerText->setColor(layoutColor);
    //viewerText->setCharacterSize(fontSize, 1.2f); // font height, aspect ratio
    //viewerText->setPosition(osg::Vec3(40,40,0.0f));
    //viewerText->setLayout(osgText::Text::LEFT_TO_RIGHT);
    //viewerText->setFontResolution(32,32);
    //viewerText->setText(theText.c_str());
}

/**
* viewerText automatically deleted via ref_ptr
*/
tc3DTextEvent::~tc3DTextEvent()
{
}

