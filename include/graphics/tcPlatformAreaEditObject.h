/**  
**  @file tcPlatformAreaEditObject.h
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


#ifndef _TCPLATFORMAREAEDITOBJECT_H_
#define _TCPLATFORMAREAEDITOBJECT_H_

#if _MSC_VER > 1000
#pragma once
#endif 

#ifndef WX_PRECOMP
#include "wx/wx.h" 
#endif // WX_PRECOMP

#include "tcAreaEditObject.h"

class tc3DWindow2;
class tcStream;
namespace ai
{
    class BlackboardInterface;
}

/** 
* Class for displaying text
*/
class tcPlatformAreaEditObject : public tcAreaEditObject
{
public:
    virtual void Draw(tc3DWindow2* host);

    virtual void MoveToScreenPoint(const wxPoint& pos);
    virtual bool ProcessKey(int keyCode);
    virtual bool ProcessLButtonDown(const wxPoint& pos);

    virtual tcStream& operator<<(tcStream& stream);
    virtual tcStream& operator>>(tcStream& stream);

    static void LoadAnchorIcons(const std::string& filename_on, const std::string& filename_off);

    tcPlatformAreaEditObject(long platformId_, long missionId_);
    virtual ~tcPlatformAreaEditObject();

private:
    enum {DRAG_ALL = 0, DRAG_POINT = 1};
    long platformId; // platform or host of mission
    long missionId; // mission id or -1 if not a mission

    Vec4 lineColor;
    wxString caption;
    tcRect anchorModeSelect; ///< box to change anchor mode
    int anchorMode; ///< 0 - no anchor, 1 - north relative, 2 - heading relative
    wxString anchorUnit; ///< unit name of anchor platform

    static boost::shared_ptr<tcGeometry> anchorOnIcon;
    static boost::shared_ptr<tcGeometry> anchorOffIcon;

    void ClearArea();
    void LoadGeoPointsFromPlatform();
    void LoadAnchorInfoFromPlatform(ai::BlackboardInterface& bb);
    void UpdateDrawData();
    virtual void UpdateSourceData();
    void UpdateAnchorSourceData();

    virtual bool IsSourceActive();
    void ToggleAnchorMode();


};

#endif

