/**
**  @file tcSonarInfoPopup.h 
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


#ifndef _SONARINFOPOPUP_H_
#define _SONARINFOPOPUP_H_

#if _MSC_VER > 1000
#pragma once
#endif 

#include "wx/wx.h" 
#include "wx/string.h"
#include <vector>

#include "tc3DWindow2.h"

class tcButton;


/**
* Class based on tcConsole modified to use 3D window graphics
*/
class tcSonarInfoPopup  : public tc3DWindow2 
{
public:    
    struct LineSegment
    {
        tcPoint start;
        tcPoint stop;
        Vec4 color;
    };

    std::string messageText;
    

	void Clear();
    virtual void Draw();

    void ForceTargetId(long id_);

    void Init();

    void SetMessageText(const std::string& text);
    
    static void SetParent(tc3DWindow2* par);

    tcSonarInfoPopup(const wxPoint& pos, const wxSize& size); 
    virtual ~tcSonarInfoPopup();

protected:
    enum {LP_CLOSE = 0};

    static tc3DWindow2* parent;

    long forceId;
    unsigned int birthCount;
	int sonarTemplateId; // to check if template has changed and update window if necessary

    tcRect svpRect;
    tcRect svpBounds; // x:speed_mps, y:depth_m

    tcRect rayRect;
    tcRect rayBounds; // x:range_m, y:depth_m

    tcRect lossRect;
    tcRect lossBounds;

    float startDepth_m;
    float bottomDepth_m;
    float targetDepth_m;

    std::vector<LineSegment> svpSegments;
    std::vector<LineSegment> raySegments;
    std::vector<LineSegment> lossSegments;
    std::vector<tcPoint> svpPoints;

    std::vector<wxString> depthTicsLabels;
    std::vector<float> yDepthTics;

    std::vector<wxString> rangeTicsLabels;
    std::vector<float> xRangeTics;

    std::vector<wxString> lossTicsLabels;
    std::vector<float> yLossTics;

    std::vector<wxString> speedTicsLabels;
    std::vector<float> xSpeedTics;

    float yTargetDepth; // y value of target depth line to draw in ray window
    float yBottomDepth; // y value of bottom depth line to draw in SVP window

    bool updateRequired;

    bool allowEditSVP; ///< true to allow real-time editing of SVP
    bool draggingSVP; ///< true when dragging an SVP point to edit
    size_t svpEditIdx;
    boost::shared_ptr<tcGeometry> svpPointOn;
    boost::shared_ptr<tcGeometry> svpPointOff;

    tcButton* closeButton;


    virtual void OnChar(wxKeyEvent& event);
    virtual void OnCloseCommand(wxCommandEvent& event);
    virtual void OnLButtonDown(wxMouseEvent& event);
    virtual void OnLButtonUp(wxMouseEvent& event);
    virtual void OnMouseMove(wxMouseEvent& event);

    void Update();

    bool TransformLineSegment(const tcPoint& a1, const tcPoint& a2, const tcRect& a_bounds, tcPoint& b1, tcPoint& b2, const tcRect& b_bounds);
    float TransformX(float xa, const tcRect& a_bounds, const tcRect& b_bounds) const;
    float TransformY(float ya, const tcRect& a_bounds, const tcRect& b_bounds) const;
    tcPoint TransformPoint(const tcPoint& p, const tcRect& a_bounds, const tcRect& b_bounds) const;
    float GoodGridSpacing(float range) const;

    void AdjustMaxRange_m(float delta_m);
    void AdjustMaxDepth_m(float delta_m);

    DECLARE_EVENT_TABLE()
};

#endif

