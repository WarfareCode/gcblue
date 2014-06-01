/**  
**  @file tcAreaEditObject.h
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


#ifndef _TCAREAEDITOBJECT_H_
#define _TCAREAEDITOBJECT_H_

#if _MSC_VER > 1000
#pragma once
#endif 

#ifndef WX_PRECOMP
#include "wx/wx.h" 
#endif // WX_PRECOMP

#include "tcMapObject.h"

class tc3DWindow2;
class tcStream;

/** 
* Class for displaying text
*/
class tcAreaEditObject : public tcMapObject
{
public:
    virtual void Draw(tc3DWindow2* host) = 0;

    virtual void MoveToScreenPoint(const wxPoint& pos);
    virtual bool ProcessLButtonDown(const wxPoint& pos);
    virtual bool ProcessKey(int keyCode);

    virtual tcStream& operator<<(tcStream& stream);
    virtual tcStream& operator>>(tcStream& stream);

    tcAreaEditObject();
    virtual ~tcAreaEditObject();

    static void LoadCornerMarker(const std::string& filename_on, const std::string& filename_off);

protected:
    enum {DRAG_ALL = 0, DRAG_POINT = 1};
    int dragMode;
    size_t dragPointIdx;
    wxPoint moveReferencePoint;
    Vec4 lineColor;
    wxString caption;
    unsigned int drawCount;

    std::vector<GeoPoint> geoPoints; // source data
    std::vector<tcPoint> screenPoints; // for drawing

    bool updateWhenDragDone;

    static boost::shared_ptr<tcGeometry> cornerMarkerOn;
    static boost::shared_ptr<tcGeometry> cornerMarkerOff;

    virtual void CalculateDragMode(const tcPoint& pos);

    void UpdateDrawData();
    virtual void UpdateSourceData() = 0;
    bool IsPointWithinArea(float lon_rad, float lat_rad) const;
    bool IsPointNearLine(const wxPoint& pos) const;
    virtual bool IsSourceActive() = 0;


};

#endif

