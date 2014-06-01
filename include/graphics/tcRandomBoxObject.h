/**  
**  @file tcRandomBoxObject.h
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


#ifndef _TCRANDOMBOXOBJECT_H_
#define _TCRANDOMBOXOBJECT_H_

#if _MSC_VER > 1000
#pragma once
#endif 

#ifndef WX_PRECOMP
#include "wx/wx.h" 
#endif // WX_PRECOMP

#include "tcMapObject.h"
#include "tcRegistered.h"
#include "tcRect.h"

class tc3DWindow2;

/** 
* Class for displaying and editing random position box for scenario edit mode
*/
class tcRandomBoxObject : public tcMapObject
{
public:
    virtual void Draw(tc3DWindow2* host);

    virtual void MoveToScreenPoint(const wxPoint& pos);
    virtual bool ProcessLButtonDown(const wxPoint& pos);
    virtual bool ProcessKey(int keyCode);
    void SetBox(const tcRect& r);

    tcRandomBoxObject();
    tcRandomBoxObject(long id);
    virtual ~tcRandomBoxObject();

    static void LoadCornerMarker(const std::string& filename_on, const std::string& filename_off);

private:
    enum {DRAG_ALL = 0, DRAG_BL = 1, DRAG_BR = 2, DRAG_TL = 3, DRAG_TR = 4};
    long platformId;
    int dragMode;
    tcPoint blOffset; ///< offset from bottom left when drag started

    tcRect box;
    tcRect startBox; ///< box before update
    
    tcPoint ownPoint;
    tcPoint sectorBL;
    tcPoint sectorBR;
    tcPoint sectorTL;
    tcPoint sectorTR;

    bool markFormationWhenDragDone;

    static boost::shared_ptr<tcGeometry> cornerMarkerOn;
    static boost::shared_ptr<tcGeometry> cornerMarkerOff;

    int CalculateDragMode(const tcPoint& pos);

    bool UpdateDrawData();

    void MarkFormationUpdated();
};

#endif

