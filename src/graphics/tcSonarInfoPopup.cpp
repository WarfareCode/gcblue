/** 
**  @file tcSonarInfoPopup.cpp 
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

#include "tcSonarInfoPopup.h"

#include <stdio.h>
#include <iostream>
#include "tcTime.h"
#include "tcSimState.h"
#include "ai/Brain.h"
#include "tcOpticalSensor.h"
#include "tcLOS.h"
#include "tcSonar.h"
#include "tcSonarEnvironment.h"
#include "tcSonarRay.h"
#include "tcButton.h"
#include "tcGeometry.h"
#include "tcTexture2D.h"
#include "tcPlatformInterface.h" // for IsDeveloperModeStatic
#include "tcGameObject.h" // for IsEditMode()

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_EVENT_TABLE(tcSonarInfoPopup, tc3DWindow2)
    EVT_COMMAND(LP_CLOSE, wxEVT_COMMAND_BUTTON_CLICKED, tcSonarInfoPopup::OnCloseCommand)
END_EVENT_TABLE()



tc3DWindow2* tcSonarInfoPopup::parent = 0;

/**
*
*/
void tcSonarInfoPopup::SetParent(tc3DWindow2* par)
{
    parent = par;
}



void tcSonarInfoPopup::AdjustMaxRange_m(float delta_m)
{
    rayBounds.right += delta_m;
    lossBounds.right += delta_m;

    rayBounds.right = std::max(rayBounds.right, 10e3f);
    lossBounds.right = std::max(lossBounds.right, 10e3f);

    updateRequired = true;
}

void tcSonarInfoPopup::AdjustMaxDepth_m(float delta_m)
{
    svpBounds.top += delta_m;
    rayBounds.top += delta_m;

    svpBounds.top = std::max(svpBounds.top, 100.0f);
    rayBounds.top = std::max(rayBounds.top, 100.0f);

    updateRequired = true;
}

/**
* Clears the text buffer
*/
void tcSonarInfoPopup::Clear()
{
	messageText = "";
}

/**
*
*/
void tcSonarInfoPopup::Draw()
{
    //unsigned currentCount = tcTime::Get()->Get30HzCount();

    //unsigned age = currentCount - birthCount;

	int currentTemplateId = tcSonarEnvironment::Get()->GetTemplate();
	if (sonarTemplateId != currentTemplateId)
	{
		sonarTemplateId = currentTemplateId;
		updateRequired = true;
	}
    Update();

    //unsigned int count = 0;
    //if (count++ % 10 != 0) return;

    StartDraw();

    Vec4 color(1, 1, 1, 1);

    //float x = 0.5f * float(mnWidth);
    float y = 0.5f * float(mnHeight);

    Vec4 gridLineColor(0.1f, 0.1f, 0.5f, 0.5f);

    // draw grid lines for SVP
    for (size_t n=0; n<yDepthTics.size(); n++)
    {
        DrawLineR(svpRect.left, yDepthTics[n], svpRect.right, yDepthTics[n], gridLineColor);        
       
        DrawTextR(depthTicsLabels[n].c_str(), svpRect.left-5.0f, yDepthTics[n], defaultFont.get(),
            color, fontSize, RIGHT_CENTER);
    }
    for (size_t n=0; n<xSpeedTics.size(); n++)
    {
        DrawLineR(xSpeedTics[n], svpRect.bottom, xSpeedTics[n], svpRect.top, gridLineColor);        
        
        DrawTextR(speedTicsLabels[n].c_str(), xSpeedTics[n], svpRect.top+10.0f, defaultFont.get(),
            color, fontSize, CENTER_CENTER);
    }


    // draw grid lines for TL
    for (size_t n=0; n<xRangeTics.size(); n++)
    {
        DrawLineR(xRangeTics[n], lossRect.bottom, xRangeTics[n], lossRect.top, gridLineColor);        
        
        DrawLineR(xRangeTics[n], rayRect.bottom, xRangeTics[n], rayRect.top, gridLineColor);       
       
        DrawTextR(rangeTicsLabels[n].c_str(), xRangeTics[n], lossRect.top+10.0f, defaultFont.get(),
            color, fontSize, CENTER_CENTER);
    }
    for (size_t n=0; n<yLossTics.size(); n++)
    {
        DrawLineR(lossRect.left, yLossTics[n], lossRect.right, yLossTics[n], gridLineColor);        
       
        DrawTextR(lossTicsLabels[n].c_str(), lossRect.left-5.0f, yLossTics[n], defaultFont.get(),
            color, fontSize, RIGHT_CENTER);
    }


    // draw SVP line segments
    for (size_t n=0; n<svpSegments.size(); n++)
    {
        DrawLineR(svpSegments[n].start.x, svpSegments[n].start.y, svpSegments[n].stop.x, svpSegments[n].stop.y, svpSegments[n].color);
    }

    // draw SVP points
    for (size_t n=0; n<svpPoints.size(); n++)
    {
        if (svpRect.ContainsPointInclusive(svpPoints[n].x, svpPoints[n].y))
        {
            if (!draggingSVP || (svpEditIdx != n))
            {
                DrawGeometryR(svpPointOff.get(), svpPoints[n].x, svpPoints[n].y);
            }
            else
            {
                DrawGeometryR(svpPointOn.get(), svpPoints[n].x, svpPoints[n].y);
            }
        }
    }

    // SVP box border
    DrawRectangleR(svpRect, Vec4(0.5f, 0.5f, 0.5f, 1.0f));

    // draw ray segments
    for (size_t n=0; n<raySegments.size(); n++)
    {
        DrawLineR(raySegments[n].start.x, raySegments[n].start.y, raySegments[n].stop.x, raySegments[n].stop.y, raySegments[n].color);
    }

    // draw target depth line
    if ((yTargetDepth >= rayRect.bottom) && (yTargetDepth <= rayRect.top))
    {
        DrawThickLineR(rayRect.left, yTargetDepth, rayRect.right, yTargetDepth, 2.0f, Vec4(0.7f, 0, 0, 0.7f));
    }

    // draw bottom depth line
    if ((yBottomDepth >= svpRect.bottom) && (yBottomDepth <= svpRect.top))
    {
        DrawThickLineR(svpRect.left, yBottomDepth, svpRect.right, yBottomDepth, 2.0f, Vec4(0.7f, 0.5f, 0.4, 0.7f));
        DrawThickLineR(rayRect.left, yBottomDepth, rayRect.right, yBottomDepth, 2.0f, Vec4(0.7f, 0.5f, 0.4, 0.7f));
    }

    // ray box border
    DrawRectangleR(rayRect, Vec4(0.5f, 0.5f, 0.5f, 1.0f));

    // draw loss segments
    for (size_t n=0; n<lossSegments.size(); n++)
    {
        DrawLineR(lossSegments[n].start.x, lossSegments[n].start.y, lossSegments[n].stop.x, lossSegments[n].stop.y, lossSegments[n].color);
    }

    // loss box border
    DrawRectangleR(lossRect, Vec4(0.5f, 0.5f, 0.5f, 1.0f));

    //DrawRectangleR(0, 0, float(mnWidth), float(mnHeight), 
    //    Vec4(0, 0, 0, 0.5f), FILL_ON);


    



	FinishDraw();

}

void tcSonarInfoPopup::ForceTargetId(long id_)
{
    forceId = id_;
}

float tcSonarInfoPopup::GoodGridSpacing(float range) const
{
    float log_range = log10f(range);
    
    float base = floorf(log_range);
    float fract = powf(10.0, log_range - base);

    float step = 1.0f;
    if (fract <= 2.0f) step = 0.25f;
    else if (fract <= 4.0f) step = 0.5f;
    else if (fract <= 1.0f) step = 1.0f;

    return step * powf(10.0f, base);

}

void tcSonarInfoPopup::Init()
{
    float width = float(mnWidth);
    float height = float(mnHeight);

    svpRect.Set(25.0f, 100.0f, 25.0f, 0.6*height);
    svpBounds.Set(1450.0f, 1550.0f, 0.0f, 500.0f);

    rayRect.Set(svpRect.right + 20.0f, width-25.0f, svpRect.bottom, svpRect.top);
    rayBounds.Set(0, 50000.0f, svpBounds.bottom, svpBounds.top);

    lossRect.Set(rayRect.left, rayRect.right, svpRect.top+10.0f, height-20.0f);
    lossBounds.Set(rayBounds.left, rayBounds.right, 60.0f, 120.0f);

    startDepth_m = 200.0f;
    bottomDepth_m = 1000.0f;
    targetDepth_m = 150.0f;

	sonarTemplateId = tcSonarEnvironment::Get()->GetTemplate();
}


void tcSonarInfoPopup::OnChar(wxKeyEvent& event)
{
	int nChar = event.GetKeyCode();
	//bool controlDown = event.ControlDown();
	//bool altDown = event.AltDown();

    switch (nChar)
    {
    case 'F':
        if (forceId == -1)
        {
            forceId = 0;
        }
        else
        {
            forceId = -1;
        }
        break;
    case ']':
        {
            float step_rad = tcSonarEnvironment::Get()->angleStep_rad;
            tcSonarEnvironment::Get()->SetRayCoverage(-0.295f, 0.295f, 0.5f*step_rad);
            updateRequired = true;
        }
        break;
    case '[':
        {
            float step_rad = tcSonarEnvironment::Get()->angleStep_rad;
            tcSonarEnvironment::Get()->SetRayCoverage(-0.295f, 0.295f, 2.0f*step_rad);
            updateRequired = true;
        }
        break;
    case WXK_ESCAPE:
        DestroyWindow();
        break;
    case WXK_LEFT:
        AdjustMaxRange_m(-10e3f);
        break;
    case WXK_RIGHT:
        AdjustMaxRange_m(10e3f);
        break;
    case WXK_DOWN:
        AdjustMaxDepth_m(100.0f);
        break;
    case WXK_UP:
        AdjustMaxDepth_m(-100.0f);
        break;
    }
}


/**
* Close and destroy popup
*/
void tcSonarInfoPopup::OnCloseCommand(wxCommandEvent& event)
{
    DestroyWindow();
}

void tcSonarInfoPopup::OnLButtonDown(wxMouseEvent& event)
{
    wxPoint pos = event.GetPosition();

    tcRect expandedSvpRect(svpRect);
    expandedSvpRect.bottom -= 10.0f;

    if (rayRect.ContainsPoint(pos.x, pos.y))
    {
        float clickDepth_m = TransformY(float(pos.y), rayRect, rayBounds);
        if ((pos.x - rayRect.left) < 15.0f)
        {
            startDepth_m = clickDepth_m;
            updateRequired = true;
        }
        else
        {
            targetDepth_m = clickDepth_m;
            updateRequired = true;
        }
    }
    else if (expandedSvpRect.ContainsPoint(pos.x, pos.y))
    {
        // check if clicking near one of SVP points
        if (allowEditSVP)
        {
            for (size_t n=0; n<svpPoints.size(); n++)
            {
                if (svpPoints[n].DistanceTo(tcPoint(pos.x, pos.y)) < 10.0f)
                {
                    draggingSVP = true;
                    svpEditIdx = n;
                    return;
                }
            }
        }

        float clickDepth_m = TransformY(float(pos.y), svpRect, svpBounds);
        if ((pos.x - svpRect.left) < 15.0f)
        {
            bottomDepth_m = std::max(clickDepth_m, 15.0f);
            updateRequired = true;
        }
    }

}


void tcSonarInfoPopup::OnLButtonUp(wxMouseEvent& event)
{
    wxPoint pos = event.GetPosition();

    tcRect expandedSvpRect(svpRect);
    expandedSvpRect.bottom -= 10.0f;

    if (expandedSvpRect.ContainsPoint(pos.x, pos.y) && (draggingSVP))
    {
        if (allowEditSVP)
        {
            tcPoint pscreen(pos.x, pos.y);
            tcPoint pSVP = TransformPoint(pscreen, svpRect, svpBounds);
            tcSonarEnvironment* sonarEnvironment = tcSonarEnvironment::Get();
            sonarEnvironment->EditSVPPoint(svpEditIdx, pSVP.y, pSVP.x);

            draggingSVP = false;
            svpEditIdx = 0;
            updateRequired = true; // to put point back where it belongs
        }

    }

}


void tcSonarInfoPopup::OnMouseMove(wxMouseEvent& event)
{
    wxPoint pos = event.GetPosition();

    if (draggingSVP)
    {
        tcRect expandedSvpRect(svpRect);
        expandedSvpRect.bottom -= 10.0f;

        if ((expandedSvpRect.ContainsPoint(pos.x, pos.y)) && (svpEditIdx < svpPoints.size()))
        {
            svpPoints[svpEditIdx].x = pos.x;
            if (svpEditIdx > 0) svpPoints[svpEditIdx].y = pos.y; // don't change depth of surface point
        }
        else
        {
            draggingSVP = false;
            svpEditIdx = 0;
            updateRequired = true; // to put point back where it belongs
        }
    }
}

/**
* @return true if any part of line is within draw bounds (b_bounds)
* transforms values "a" into draw coordinates "b"
* b1 and b2 are start and stop points of line segment in draw coordinates
*/
bool tcSonarInfoPopup::TransformLineSegment(const tcPoint& a1, const tcPoint& a2, const tcRect& a_bounds, tcPoint& b1, tcPoint& b2, const tcRect& b_bounds)
{
    float mx = (b_bounds.Width() / a_bounds.Width());
    float my = (b_bounds.Height() / a_bounds.Height());

    b1.x = mx*(a1.x - a_bounds.left) + b_bounds.left;
    b1.y = my*(a1.y - a_bounds.bottom) + b_bounds.bottom;

    b2.x = mx*(a2.x - a_bounds.left) + b_bounds.left;
    b2.y = my*(a2.y - a_bounds.bottom) + b_bounds.bottom;

    bool in_1 = b_bounds.ContainsPointInclusive(b1.x, b1.y);
    bool in_2 = b_bounds.ContainsPointInclusive(b2.x, b2.y);

    if (in_1 && in_2)
    {
        return true;
    }

    if (b1.x > b2.x)
    {
        tcPoint temp(b1);
        b1 = b2;
        b2 = temp;
    }

    if ((b1.x < b_bounds.left) && (b2.x > b_bounds.left))
    {
        float dydx = (b2.y-b1.y)/(b2.x-b1.x);
        b1.y += dydx * (b_bounds.left - b1.x);
        b1.x = b_bounds.left;
    }
    if ((b1.x < b_bounds.right) && (b2.x > b_bounds.right))
    {
        float dydx = (b2.y-b1.y)/(b2.x-b1.x);
        b2.y -= dydx * (b2.x - b_bounds.right);
        b2.x = b_bounds.right;
    }

    if (b1.y > b2.y)
    {
        tcPoint temp(b1);
        b1 = b2;
        b2 = temp;
    }

    if ((b1.y < b_bounds.bottom) && (b2.y > b_bounds.bottom))
    {
        float dxdy = (b2.x-b1.x)/(b2.y-b1.y);
        b1.x += dxdy * (b_bounds.bottom - b1.y);
        b1.y = b_bounds.bottom;
    }
    if ((b1.y < b_bounds.top) && (b2.y > b_bounds.top))
    {
        float dxdy = (b2.x-b1.x)/(b2.y-b1.y);
        b2.x -= dxdy * (b2.y - b_bounds.top);
        b2.y = b_bounds.top;
    }

    in_1 = b_bounds.ContainsPointInclusive(b1.x, b1.y);
    in_2 = b_bounds.ContainsPointInclusive(b2.x, b2.y);

    return (in_1 && in_2);
}


float tcSonarInfoPopup::TransformX(float xa, const tcRect& a_bounds, const tcRect& b_bounds) const
{
    float xb = (xa - a_bounds.left) * (b_bounds.Width() / a_bounds.Width()) + b_bounds.left;

    return xb;
}

float tcSonarInfoPopup::TransformY(float ya, const tcRect& a_bounds, const tcRect& b_bounds) const
{
    float yb = (ya - a_bounds.bottom) * (b_bounds.Height() / a_bounds.Height()) + b_bounds.bottom;

    return yb;
}

tcPoint tcSonarInfoPopup::TransformPoint(const tcPoint& p, const tcRect& a_bounds, const tcRect& b_bounds) const
{
    tcPoint pt;

    pt.x = TransformX(p.x, a_bounds, b_bounds);
    pt.y = TransformY(p.y, a_bounds, b_bounds);

    return pt;
}


void tcSonarInfoPopup::Update()
{
    if (!updateRequired) return;
    updateRequired = false;

    // Update SVP
    svpSegments.clear();
    svpPoints.clear();

    tcSonarEnvironment* sonarEnvironment = tcSonarEnvironment::Get();
    const std::vector<tcSonarEnvironment::SVPData>& svpData = sonarEnvironment->GetSVP();
  
    for (size_t n=0; n<svpData.size(); n++)
    {
        tcPoint p(svpData[n].v_mps, svpData[n].depth_m);
        svpPoints.push_back(TransformPoint(p, svpBounds, svpRect));
    }
    
    for (size_t n=0; n<svpData.size()-1; n++)
    {
        tcPoint a1(svpData[n].v_mps, svpData[n].depth_m);
        tcPoint a2(svpData[n+1].v_mps, svpData[n+1].depth_m);

        tcPoint b1;
        tcPoint b2;

        if (TransformLineSegment(a1, a2, svpBounds, b1, b2, svpRect))
        {
            LineSegment seg;
            seg.start = b1;
            seg.stop = b2;
            seg.color = Vec4(1.0f, 1.0f, 1.0f, 1.0f);

            svpSegments.push_back(seg);
        }
    }

    // Update ray diagram
    raySegments.clear();
    std::vector<float> range_m;
    float dr = 0.01f * rayBounds.Width();
    for (float r=rayBounds.left; r<rayBounds.right; r+=dr)
    {
        range_m.push_back(r);
    }

    std::vector<tcSonarRay> beam;
    sonarEnvironment->UpdateBeam(beam, startDepth_m, bottomDepth_m);
    for (size_t ray=0; ray<beam.size(); ray+=2)
    {
        float reflectionLossFactor = 1.0f;
        float depthPrev_m = beam[ray].CalculateDepth(range_m[0], reflectionLossFactor);

        for (size_t n=1; n<range_m.size(); n++)
        {
            float depth_m = beam[ray].CalculateDepth(range_m[n], reflectionLossFactor);

            tcPoint a1(range_m[n-1], depthPrev_m);
            tcPoint a2(range_m[n], depth_m);
            tcPoint p1;
            tcPoint p2;
            if ((depth_m >= 0) && (depthPrev_m >= 0) && TransformLineSegment(a1, a2, rayBounds, p1, p2, rayRect))
            {
                LineSegment seg;
                seg.start = p1;
                seg.stop = p2;
                seg.color = Vec4(1.0f, 1.0f, 1.0f, sqrtf(reflectionLossFactor));
                raySegments.push_back(seg);
            }

            depthPrev_m = depth_m;
        }
    }

    // Update TL diagram
    lossSegments.clear();
    float TL_prev = sonarEnvironment->CalculateTL(beam, range_m[1], targetDepth_m);
    for (size_t n=2; n<range_m.size(); n++)
    {
        float TL_dB = sonarEnvironment->CalculateTL(beam, range_m[n], targetDepth_m);

        tcPoint a1(range_m[n-1], TL_prev);
        tcPoint a2(range_m[n], TL_dB);
        tcPoint p1;
        tcPoint p2;
        if (TransformLineSegment(a1, a2, lossBounds, p1, p2, lossRect))
        {
            LineSegment seg;
            seg.start = p1;
            seg.stop = p2;
            seg.color = Vec4(1.0f, 1.0f, 1.0f, 1.0f);
            lossSegments.push_back(seg);
        }

        TL_prev = TL_dB;
    }


    // update depth grid spacing and tic values
    depthTicsLabels.clear();
    yDepthTics.clear();

    float depthRange_m = svpBounds.Height();
    float depthGridSpacing_m = GoodGridSpacing(depthRange_m);
    float invDepthGridSpacing = 1.0f / depthGridSpacing_m;

    float depthGridStart_m = depthGridSpacing_m * ceilf(invDepthGridSpacing*svpBounds.bottom);
    float depthGridStop_m = depthGridSpacing_m * floorf(invDepthGridSpacing*svpBounds.top);

    for (float y=depthGridStart_m; y<=depthGridStop_m; y+=depthGridSpacing_m)
    {
        wxString s;
        s.Printf("%.0f", y);
        depthTicsLabels.push_back(s);
        
        yDepthTics.push_back(TransformY(y, svpBounds, svpRect));
    }

    // update range grid spacing and tic values
    rangeTicsLabels.clear();
    xRangeTics.clear();

    float rangeRange_m = rayBounds.Width();
    float rangeGridSpacing_m = GoodGridSpacing(rangeRange_m);
    float invRangeGridSpacing = 1.0f / rangeGridSpacing_m;

    float rangeGridStart_m = rangeGridSpacing_m * ceilf(invRangeGridSpacing*rayBounds.left);
    float rangeGridStop_m = rangeGridSpacing_m * floorf(invRangeGridSpacing*rayBounds.right);

    for (float x=rangeGridStart_m; x<=rangeGridStop_m; x+=rangeGridSpacing_m)
    {
        wxString s;
        s.Printf("%.1f", 0.001f*x);
        rangeTicsLabels.push_back(s);
        
        xRangeTics.push_back(TransformX(x, rayBounds, rayRect));
    }

    // update SVP speed grid spacing and tic values
    speedTicsLabels.clear();
    xSpeedTics.clear();

    float speedRange = svpBounds.Width();
    float speedGridSpacing = GoodGridSpacing(speedRange);
    float invSpeedGridSpacing = 1.0f / speedGridSpacing;

    float speedGridStart = speedGridSpacing * ceilf(invSpeedGridSpacing*svpBounds.left);
    float speedGridStop = speedGridSpacing * floorf(invSpeedGridSpacing*svpBounds.right);

    for (float x=speedGridStart; x<=speedGridStop; x+=3*speedGridSpacing)
    {
        wxString s;
        s.Printf("%.0f", x);
        speedTicsLabels.push_back(s);
        
        xSpeedTics.push_back(TransformX(x, svpBounds, svpRect));
    }


    // update loss grid y spacing and tic values
    lossTicsLabels.clear();
    yLossTics.clear();

    float lossRange = lossBounds.Height();
    float lossGridSpacing = GoodGridSpacing(lossRange);
    float invLossGridSpacing = 1.0f / lossGridSpacing;

    float lossGridStart = lossGridSpacing * ceilf(invLossGridSpacing*lossBounds.bottom);
    float lossGridStop = lossGridSpacing * floorf(invLossGridSpacing*lossBounds.top);

    for (float y=lossGridStart; y<=lossGridStop; y+=2.0f*lossGridSpacing)
    {
        wxString s;
        s.Printf("%.0f", y);
        lossTicsLabels.push_back(s);
        
        yLossTics.push_back(TransformY(y, lossBounds, lossRect));
    }


    // update target depth line
    yTargetDepth = TransformY(targetDepth_m, rayBounds, rayRect);

    // update bottom depth line
    yBottomDepth = TransformY(bottomDepth_m, svpBounds, svpRect);


}



/**
*
*/
tcSonarInfoPopup::tcSonarInfoPopup(const wxPoint& pos, const wxSize& size)
            : tc3DWindow2(parent, pos, size, "SonarInfo", parent),
              forceId(-1),
              updateRequired(true),
              draggingSVP(false),
              svpEditIdx(0),
              allowEditSVP(false),
			  sonarTemplateId(-1)
{
    SetBaseRenderBin(parent->GetBaseRenderBin() + 10);
    Raise();
    birthCount = tcTime::Get()->Get30HzCount();

    SetBorderDraw(true);
    SetBackgroundColor(Vec4(0, 0, 0, 0.8f));

    const int closeButtonSize = 12;
    closeButton = new tcButton(this, wxPoint(mnWidth - closeButtonSize - 2, 1), 
        wxSize(closeButtonSize, closeButtonSize));
    closeButton->SetActive(true);
    closeButton->SetBackgroundAlpha(1.0);
    closeButton->SetCaption("");
    closeButton->SetCommand(LP_CLOSE);
    closeButton->LoadImages("close.png", "close.png", "close.png", "close.png");
    closeButton->SetSendRedraw(true);

    float w = 12.0f;
    svpPointOn = boost::shared_ptr<tcGeometry>(new tcGeometry);
    tcTexture2D* texOn = new tcTexture2D("images\\white_marker.png");
    svpPointOn->MakeTexturedSymbol(boost::shared_ptr<tcTexture2D>(texOn), w);

    svpPointOff = boost::shared_ptr<tcGeometry>(new tcGeometry);
    tcTexture2D* texOff = new tcTexture2D("images\\gray_marker.png");
    svpPointOff->MakeTexturedSymbol(boost::shared_ptr<tcTexture2D>(texOff), w);


    Init();


    allowEditSVP = tcPlatformInterface::IsDeveloperModeStatic() || tcGameObject::IsEditMode();

}

tcSonarInfoPopup::~tcSonarInfoPopup() 
{

}

