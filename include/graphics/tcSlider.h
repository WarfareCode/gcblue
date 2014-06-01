/**  
**  @file tcSlider.h
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


#ifndef _TCSLIDER_H_
#define _TCSLIDER_H_

#if _MSC_VER > 1000
#pragma once
#endif 

#include "tc3DWindow2.h"
#include <string>

#include <boost/shared_ptr.hpp>
#include "tv_types.h"

class tcTexture2D;


class TiXmlNode;

/**
* Start of slider class. Nothing done yet to make this work, since 
* tcOptionsView is using widgets draw by itself vs. button style independent
* windows like tcButton
*/
class tcSlider : public tc3DWindow2
{
public:
    virtual void Draw();

    long GetCommand() const;
    void SetCommand(long cmd);
    void SetFontSize(float val);
    
    void SetValidRange(float minVal, float maxVal);
    void LinkValue(float* pVal);


    virtual void SetActive(bool abActive);

    tcSlider(tc3DWindow2 *parent, const wxPoint& pos, const wxSize& size,
            const wxString& name = "Slider");
    virtual ~tcSlider();

protected:
    float sliderValue; ///< current value of slider
    float sliderMin; ///< value when sliderFraction == 0
    float sliderMax; ///< value when sliderFraction == 1

    float sliderBarWidth;
    float sliderMarginLeft; ///< x margin between window and left edge of bar
    float sliderMarginRight; ///< x margin between window and right edge of bar
    float sliderBarHeight;
    float thumbWidth;
    float thumbHeight;
    tcRect thumbRect;

    bool sliderDragActive;
    wxPoint buttonDownPoint;
    float buttonDownSliderValue;

    long commandId;
    float fontSize;

    float* linkedValue;


    void DrawMouseOverCaption();
    virtual void OnEnterWindow(wxMouseEvent& event);
    virtual void OnLButtonDown(wxMouseEvent& event);
    virtual void OnLButtonUp(wxMouseEvent& event);
    virtual void OnLeaveWindow(wxMouseEvent& event);
    virtual void OnMouseMove(wxMouseEvent& event);
    void SendUpdateEvent();
    void UpdateThumb();
};

#endif

