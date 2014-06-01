/**  
**  @file tcMapObject.h
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


#ifndef _TCMAPOBJECT_H_
#define _TCMAPOBJECT_H_

#if _MSC_VER > 1000
#pragma once
#endif 

#ifndef WX_PRECOMP
#include "wx/wx.h" 
#endif // WX_PRECOMP

#include "simmath.h"
#include <boost/shared_ptr.hpp>
#include "tv_types.h"
#include "tcRegistered.h"

class tc3DWindow2;

class tcStream;

class tcMapView;
class tcGeometry;
class tcCommandQueue;

namespace scriptinterface
{
    class tcScenarioLogger;
}


/** 
* This class should eventually replace tcMapObj. Class will provide
* draw methods to allow map symbol drawing to be delegated to the
* low level objects. This should clean up the messy draw method in
* tcMapView and related.
* Initially this will be used for mission briefing graphics like
* text captions, arrows, etc.
*/
class tcMapObject: public tcRegistered
{
public:
    friend class scriptinterface::tcScenarioLogger;

    enum {NO_FLAGS = 0, AUTO_COLOR = 1};

	Vec4 color;
    bool isActive;
    int attributes;
    float fontSize;

    virtual void Draw(tc3DWindow2* host);
	Vec4 GetColor() const {return color;}
    void SetActive(bool active) {isActive = active;}
	void SetColor(const Vec4& c);
    void SetFontSize(float fontSize_);

	void SetMarkerActive(bool active) {markerEnabled = active;}
	void SetUseScreenCoords(bool active) {useRelativeCoords = active;}   
    
    bool IsInteractive() const;
    void SetInteractive(bool state);

    bool IsComplexInteractive() const;
    void SetComplexInteractive(bool state);

    void FlagForDelete();
    bool IsFlaggedForDelete() const;

    float GetScreenDistanceFrom(const wxPoint& pos);
    void SetIsHooked(bool state);

    void SetAttributes(int val);
    int GetAttributes() const;

    void ConfigureWithString(const std::string& str);
    wxString GetColorString() const;

    virtual void MoveToScreenPoint(const wxPoint& pos);
    bool IsDragActive() const;
    virtual void SetDragActive(bool state);
    virtual bool ProcessKey(int keyCode);
    virtual bool ProcessLButtonDown(const wxPoint& pos);

    unsigned int GetCreateTime() const;
    void SetCreateTime(unsigned int n);

    static void SetMapView(tcMapView *mv);
    static void SetCommandInterface(tcCommandQueue* ci);
    static void LoadMarker(const std::string& filename);
    
    virtual tcStream& operator<<(tcStream& stream);
    virtual tcStream& operator>>(tcStream& stream);

    tcMapObject();
    tcMapObject(double x, double y, bool useRel = false);
    virtual ~tcMapObject();
protected:
	bool markerEnabled; ///< true to draw X marker with text
    bool isInteractive; ///< true if object can be hooked on map
    bool isComplexInteractive; ///< true if object is complex draggable like formation object
    bool isHooked; ///< true if obj is hooked
    bool flaggedForDelete; ///< true to safely delete (in overlay)
    bool dragActive;

    unsigned int createTime; ///< for auto show/no show and fade in of graphics
    const unsigned int showDelay; ///< tics to delay showing of graphics
    const unsigned int fadeInTime; ///< tics for fade-in effect
    bool isVisible; ///< true if drawing and interacting with object
    float fadeInAlpha;

	bool useRelativeCoords; ///< interpret lat_rad and lon_rad as rel screen coords [0-1]
    double _x; ///< radian latitude or relative screen x coord
    double _y; ///< radian longitude or relative screen y coord

    tcPoint GetScreenPoint() const;
    void UpdateVisibility();

    static boost::shared_ptr<tcGeometry> marker;
    static tcMapView* mapView; ///< used to translate lat/lon coords into screen coords
    static tcCommandQueue* commandInterface;

private:
};

/** 
* Class for displaying text
*/
class tcMapTextObject : public tcMapObject
{
public:
    std::string caption; ///< text to display

    void SetTextAlignment(int mode);

    virtual void Draw(tc3DWindow2* host);

    virtual bool ProcessKey(int keyCode);

    virtual tcStream& operator<<(tcStream& stream);
    virtual tcStream& operator>>(tcStream& stream);

    tcMapTextObject();
    tcMapTextObject(const std::string& text, double x, double y, bool useRel = false);
    virtual ~tcMapTextObject();

protected:
    int textAlignment;

};

#endif

