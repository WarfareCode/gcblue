/**  
**  @file tcDirectorEvent.h header for tcDirectorEvent and derived classes 
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

#ifndef _TCDIRECTOREVENT_H_
#define _TCDIRECTOREVENT_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "wx/wx.h"

#include "tv_types.h"
#include <string>
//#include <osg/ref_ptr>


class tcMapObject;

class tcTacticalMapView;
class tcWorldMapView;

class tcConsoleBox;
class tc3DViewer;


namespace osgText
{
    class Text;
}

/**
* Base class for time-tagged camera or game events to support cut scenes and
* dramatic briefings.
*/
class tcDirectorEvent
{
public:
    std::string eventName; ///< optional name for event
    double eventStart; ///< time in seconds relative to start of director control, start of event
    double eventStop;  ///< time in seconds relative to start of director control, end of event

    static void AttachEventHandler(wxWindow *win) {eventHandler = win;}
    bool EventStarted(double t) {return t >= eventStart;}
    bool EventFinished(double t) {return t >= eventStop;}
    virtual void Update(double t);
    tcDirectorEvent();
    tcDirectorEvent(double start, double stop);
    virtual ~tcDirectorEvent();
protected:
    bool triggered; ///< set true when effect has been triggered, used for one-shot effects mainly
    static wxWindow *eventHandler; ///< window to post events to
};

/**
* Base class for events that affect tcMapView such as 
* animated map symbols.
*/
class tcMapEvent
{
public:
	static void AttachMapViews(tcTacticalMapView* tmv, tcWorldMapView* wmv);

    tcMapEvent(tcMapObject *obj);
    virtual ~tcMapEvent();
protected:
    bool addedToMap; ///< true if mapObject has been added to map
    tcMapObject *mapObject;

	static tcTacticalMapView* tacticalMapView;
	static tcWorldMapView* worldMapView;
};


/**
* Displays text on map window, updates text properties
*/
class tcMapTextEvent : public tcDirectorEvent, public tcMapEvent
{
public:
	enum {FADE_MASK = 0x01, RELATIVE_COORD_MASK = 0x02, MARKER_DISABLE_MASK = 0x04};
    int effectCode;

    void SetTextColor(const Vec4& color);
    void SetTextSize(float fontSize);
    void SetTextAlignment(int mode);

    virtual void Update(double t);

    tcMapTextEvent(std::string text, double startTime, double endTime, 
        double lon_deg, double lat_deg, int effect);
    virtual ~tcMapTextEvent();
};

/**
* Changes map center or zoom
*/
class tcMapViewEvent : public tcDirectorEvent, public tcMapEvent
{
public:
    double lon_rad;
    double lat_rad;
    double lonSpan_rad;
    bool setTacticalMap; ///< true for tactical, false for world map view

    virtual void Update(double t);

    tcMapViewEvent(double t, double lon_deg, double lat_deg, double lonSpan_deg, bool tacticalMap);
    virtual ~tcMapViewEvent();
};

/**
* Sound event 
*/
class tcSoundEvent : public tcDirectorEvent
{
public:
    virtual void Update(double t);

    tcSoundEvent(double start, double stop);
    virtual ~tcSoundEvent();
};

class tcSoundEffectEvent : public tcSoundEvent
{
public:
    std::string effectCode;
    
    virtual void Update(double t);

    tcSoundEffectEvent(double t, const std::string& effect);
    virtual ~tcSoundEffectEvent();
};

class tcMusicEvent : public tcSoundEvent
{
public:
    std::string song; ///< song file name
    std::string command; ///< string command for event
    double param;     

    virtual void Update(double t);

    tcMusicEvent(std::string aSong, std::string aCommand, double aParam, double start, double stop);
    virtual ~tcMusicEvent();
};

/**
* Event to send text to message channel
* (used to be to a text console)
*/
class tcMessageTextEvent : public tcDirectorEvent
{
public:
    std::string message;
    std::string channel;
    unsigned int alliance;

    virtual void Update(double t);

    tcMessageTextEvent(const std::string& message_, const std::string& channel_, unsigned int alliance_, double t);
    virtual ~tcMessageTextEvent();
};

/**
* Event to send game command
*/
class tcGameCommandEvent : public tcDirectorEvent
{
public:
    long commandId;
    long param; ///< a generic parameter used by the command

    virtual void Update(double t);

    tcGameCommandEvent(long id, double t, long val);
    virtual ~tcGameCommandEvent();
};



/**
* An event that manipulates the camera in the 3D viewer
*/
class tcCameraEvent : public tcDirectorEvent
{
public:
//    static tc3DViewer *viewer;
    long targetID;
    bool moveWithTarget;
    bool lookAtTarget;

//    static void AttachViewer(tc3DViewer *v) {viewer = v;}
    virtual void Update(double t);

    tcCameraEvent(double tStart, double tStop);
    virtual ~tcCameraEvent();
};

/**
* A camera that is locked to a target with az/el/range that
* can change over the camera move. Name is not the best.
*/
class tcFlybyCameraEvent : public tcCameraEvent
{
public:
    float startAz;
    float startEl;
    float startRange;
    float stopAz;
    float stopEl;
    float stopRange;

    virtual void Update(double t);

    tcFlybyCameraEvent(double tStart, double tStop, long targID, 
        float az1, float az2, float el1, float el2, float r1, float r2);
    virtual ~tcFlybyCameraEvent();
};

/**
* Camera that moves in (x,y,z) relative to target. Same as
* FlybyCamera otherwise.
*/
class tcTrackCameraEvent : public tcCameraEvent
{
public:
    float startX;
    float startY;
    float startZ;
    float stopX;
    float stopY;
    float stopZ;

    virtual void Update(double t);

    tcTrackCameraEvent(double tStart, double tStop, long targID, 
        float x1, float x2, float y1, float y2, float z1, float z2 );
    virtual ~tcTrackCameraEvent();
};

/**
* Adds to viewer and maintains an osgText::Text object to 
* display 3D text effects for briefing.
*/
class tc3DTextEvent : public tcCameraEvent
{
public:
    std::string theText;
    float fontSize;
    float textx, texty; ///< normalized text coordinates
    int effectCode;

    virtual void Update(double t);

    tc3DTextEvent(std::string text, double startTime, double endTime, 
        float x, float y, float size, int effect);
    virtual ~tc3DTextEvent();

protected:
    //osg::ref_ptr<osgText::Text> viewerText; 
};

#endif