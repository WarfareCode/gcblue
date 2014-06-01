/**  
**  @file tcFormationObject.h
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


#ifndef _TCFORMATIONOBJECT_H_
#define _TCFORMATIONOBJECT_H_

#if _MSC_VER > 1000
#pragma once
#endif 

#ifndef WX_PRECOMP
#include "wx/wx.h" 
#endif // WX_PRECOMP

#include "tcMapObject.h"


class tc3DWindow2;
class tcStream;
class tcFormation;

/** 
* Class for displaying text
*/
class tcFormationObject : public tcMapObject
{
public:
    virtual void Draw(tc3DWindow2* host);

    virtual void MoveToScreenPoint(const wxPoint& pos);
    virtual bool ProcessLButtonDown(const wxPoint& pos);

    virtual tcStream& operator<<(tcStream& stream);
    virtual tcStream& operator>>(tcStream& stream);

    tcFormationObject();
    tcFormationObject(long id);
    virtual ~tcFormationObject();

    static void LoadCornerMarker(const std::string& filename_on, const std::string& filename_off, const std::string& filename_off2);

private:
    enum {DRAG_ALL = 0, DRAG_BL = 1, DRAG_BR = 2, DRAG_TL = 3, DRAG_TR = 4};
    long platformId;
    int dragMode;

    float range_km, min_range_km, max_range_km;
    float angle_rad, start_angle_rad, stop_angle_rad, bearing_center_rad;
    float rx1, rx2, ry1, ry2;
    float deltaRange_km, deltaBearing_rad; // for drag mode to keep track of offset from center to drag point

    tcPoint ownPoint;
    tcPoint leaderPoint;
    tcPoint sectorCenter;
    tcPoint sectorBL;
    tcPoint sectorBR;
    tcPoint sectorTL;
    tcPoint sectorTR;
    tcRect bearingModeSelect; ///< box to change bearing mode
    bool useNorthBearing;
    bool isLeader;
    bool markFormationWhenDragDone;
    int formationMode;

    static boost::shared_ptr<tcGeometry> cornerMarkerOn;
    static boost::shared_ptr<tcGeometry> cornerMarkerOff;
    static boost::shared_ptr<tcGeometry> cornerMarkerOff2;

    int CalculateDragMode(const tcPoint& pos);
    void ToggleBearingMode();
    bool UpdateDrawData();
    void DrawLeader(tc3DWindow2* host);
    void MarkFormationUpdated();
};

#endif

