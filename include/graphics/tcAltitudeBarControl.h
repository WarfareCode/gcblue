/**
**  @file tcAltitudeBarControl.h 
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


#ifndef _TCALTITUDEBARCONTROL_H_
#define _TCALTITUDEBARCONTROL_H_

#if _MSC_VER > 1000
#pragma once
#endif 

#include "tcRect.h"
#include "tcControl.h"
#include <boost/shared_ptr.hpp>
#include "tv_types.h"

class tcGameObject;
class tc3DWindow2;
class tcTexture2D;
class tcUnits;

/**
* Altitude bar control
*/
class tcAltitudeBarControl : public tcControl
{
public:
    virtual void Draw(tc3DWindow2* graphics);
    virtual void OnLButtonDown(wxMouseEvent& event);
    virtual void OnLButtonUp(wxMouseEvent& event);
    virtual void OnMouseMove(wxMouseEvent& event);

    tcAltitudeBarControl(float x, float y, float width, float height);
    virtual ~tcAltitudeBarControl();

protected:
    tcRect barRect;
    tcRect upRect; ///< region for up icon
    tcRect downRect; ///< region for down icon
    float fontSize;
    float fontSizeLarge; ///< for main altitude display
    float increaseScaleThresh; ///< increase if current is > (maxscale * increaseScaleThresh)
    float decreaseScaleThresh; ///< decrease if current is < (maxscale * decreaseScaleThresh)

    bool mouseOverBar;
    bool mouseOverUp;
    bool mouseOverDown;    
    wxPoint mousePosition;

    boost::shared_ptr<tcTexture2D> upIcon;
    boost::shared_ptr<tcTexture2D> upOverIcon;
    boost::shared_ptr<tcTexture2D> downIcon;
    boost::shared_ptr<tcTexture2D> downOverIcon;

    Vec4 color;
    Vec4 colorDim;
    Vec4 neutralColor;
    Vec4 dangerColor;
    Vec4 warnColor;
    Vec4 overColor;

    tcRect currentRect; ///< filled rect with current altitude or depth
    tcRect overRect; ///< filled semi-transparent rect for mouse over position
    float yGoal; ///< y position of goal altitude or depth
    float yTerrain; ///< y position of ground or ocean bottom
    float yLimit; ///< y pos of max altitude or depth
    float currentGoal; /// current goal altitude or depth
    float currentValue; ///< current altitude or depth
    float currentScale; ///< altitude or depth of current max scale
    bool isDepth; ///< true if depth control (submarine)
    float mouseOverValue; ///< command value of current mouse position
    float xMouse; ///< coordinates of mouse cursor in window
    float yMouse;

    void LoadIcons();
    void UpdateDrawParameters(); 
    static tcUnits* units;
    
};

#endif