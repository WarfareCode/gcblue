/**
**  @file tcAltitudeBarControl.cpp 
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


#include "stdwx.h" // precompiled header file

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "tcAltitudeBarControl.h"
#include "tc3DWindow2.h"
#include "tcAirObject.h"
#include "tcGameObject.h"
#include "tcPlatformObject.h"
#include "tcSubObject.h"
#include "tcAirDBObject.h"
#include "tcPlatformDBObject.h"
#include "tcSubDBObject.h"
#include "tcTorpedoObject.h"
#include "tcTexture2D.h"
#include "tcUnits.h"
#include "tcTorpedoDBObject.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif 

tcUnits* tcAltitudeBarControl::units = 0;



/**
*
*/
void tcAltitudeBarControl::Draw(tc3DWindow2* graphics)
{
    wxASSERT(graphics);
    if (!IsActive()) return;
    if (!obj) return;

    UpdateDrawParameters();


    tcFont* font = graphics->GetDefaultFont();

    // draw main altitude / depth text
    float x = barRect.GetRight() + 28.0f;
    float y = barRect.YCenter() + 5.0f;
    wxString s = wxString::Format("%s", units->GetUserAltitudeString(currentValue));
    graphics->DrawText(s.c_str(), x, y, 
        font, color, fontSizeLarge, tc3DWindow2::CENTER_CENTER);

    // draw scale text
    x = barRect.XCenter();
    y = isDepth ? barRect.bottom - 7 : barRect.top + 7;
    s = wxString::Format("%.0f", units->UserAltitudeUnits(currentScale));
    graphics->DrawText(s.c_str(), x, y, 
        font, color, fontSize, tc3DWindow2::CENTER_CENTER);

    graphics->DrawRectangle(currentRect, color, tc3DWindow2::FILL_ON);

    if (mouseOverBar)
    {
        graphics->DrawRectangle(overRect, overColor, tc3DWindow2::FILL_ON);

        // draw command value text corresponding to current position
        wxString s = wxString::Format("%s", units->GetUserAltitudeString(mouseOverValue));
        graphics->DrawText(s.c_str(), x, yMouse, 
            font, overColor, fontSizeLarge, tc3DWindow2::CENTER_CENTER);
    }

    graphics->DrawRectangle(barRect, colorDim, tc3DWindow2::FILL_OFF);



    float x1 = barRect.GetLeft() - 2.0;
    float x2 = barRect.GetRight() + 2.0;

    graphics->DrawLine(x1, yGoal, x2, yGoal, neutralColor); // goal line
    graphics->DrawLine(x1, yTerrain, x2, yTerrain, dangerColor); // terrain line
    graphics->DrawLine(x1, yLimit, x2, yLimit, warnColor); // max alt or depth line



    tcTexture2D* upTex = mouseOverUp ? upOverIcon.get() : upIcon.get();
    tcTexture2D* downTex = mouseOverDown ? downOverIcon.get() : downIcon.get();

    graphics->DrawImage(upTex, upRect.left, upRect.bottom, 
        upRect.Width(), upRect.Height());
    graphics->DrawImage(downTex, downRect.left, downRect.bottom, 
        downRect.Width(), downRect.Height());

}

/**
*
*/
void tcAltitudeBarControl::LoadIcons()
{
    upIcon = tc3DWindow2::LoadTexture("arrow_up.jpg");
    upOverIcon = tc3DWindow2::LoadTexture("arrow_up_over.jpg");
    downIcon = tc3DWindow2::LoadTexture("arrow_down.jpg");
    downOverIcon = tc3DWindow2::LoadTexture("arrow_down_over.jpg");
}

/**
*
*/
void tcAltitudeBarControl::OnLButtonDown(wxMouseEvent& event)
{
    wxPoint pos = event.GetPosition();
    
    float x = float(pos.x);
    float y = float(pos.y);

    float commandValue = 0;
    wxASSERT(obj);

    if (barRect.ContainsPoint(x, y))
    {
        if (isDepth)
        {
            // negative val for depth
            commandValue = (y - barRect.top) * currentScale / barRect.Height(); 
        }
        else
        {
            commandValue = (y - barRect.bottom) * currentScale / barRect.Height();
        }
    }
    else if (upRect.ContainsPoint(x, y))
    {
        commandValue = isDepth? -currentGoal + 5 : currentGoal + 30;
    }
    else if (downRect.ContainsPoint(x, y))
    {
        commandValue = isDepth? -currentGoal - 5 : currentGoal - 30;
    }
    else
    {
        return;
    }



    if (tcAirObject *air = dynamic_cast<tcAirObject*>(obj))
    {
        if (commandValue < 3) commandValue = 3;
		air->SetAltitude(commandValue);
        air->SetPitchLimit(1.5f); // set pitch limit back to default just in case something else has restricted it
    }
    else if (tcSubObject* sub = dynamic_cast<tcSubObject*>(obj))
    {
        if (commandValue > 0) commandValue = 0;
        sub->SetAltitude(commandValue);
    }
    else if (tcTorpedoObject* torpedo = dynamic_cast<tcTorpedoObject*>(obj))
    {
        if (commandValue > -2) commandValue = -2;
        torpedo->SetAltitude(commandValue);
    }
}

/**
*
*/
void tcAltitudeBarControl::OnLButtonUp(wxMouseEvent& event)
{
}

/**
*
*/
void tcAltitudeBarControl::OnMouseMove(wxMouseEvent& event)
{
    wxPoint pos = event.GetPosition();
    
    float x = float(pos.x);
    float y = float(pos.y);

    xMouse = x;
    yMouse = y;

    mouseOverBar = false;
    mouseOverUp = false;
    mouseOverDown = false;
    mouseOverValue = 0;

    if (barRect.ContainsPoint(x, y))
    {
        mouseOverBar = true;
        mousePosition = pos;

        // update mouse over command value for text display 
        // (removes some of the guesswork in setting altitude/depth)
        if (isDepth)
        {
            // negative val for depth
            mouseOverValue = (y - barRect.top) * currentScale / barRect.Height(); 
        }
        else
        {
            mouseOverValue = (y - barRect.bottom) * currentScale / barRect.Height();
        }
    }
    else if (upRect.ContainsPoint(x, y))
    {
        mouseOverUp = true;
    }
    else if (downRect.ContainsPoint(x, y))
    {
        mouseOverDown = true;
    }

}

/**
*
*/    
void tcAltitudeBarControl::UpdateDrawParameters()
{
    tcAirObject* air = dynamic_cast<tcAirObject*>(obj);
    tcSubObject* sub = dynamic_cast<tcSubObject*>(obj);
    tcTorpedoObject* torpedo = dynamic_cast<tcTorpedoObject*>(obj);

    if ((air == 0) && (sub == 0) && (torpedo == 0))
    {
        currentValue = 0;
        currentGoal = 0;
        return;
    }

    isDepth = (sub != 0) || (torpedo != 0);

    float limit, terrain;

    if (isDepth) 
    {
        if (sub != 0)
        {
            currentValue = -sub->mcKin.mfAlt_m;
            limit = sub->mpDBObject->mfMaxDepth_m;
            terrain = -sub->mcTerrain.mfHeight_m;
            currentGoal = -sub->mcGS.mfGoalAltitude_m;
        }
        else
        {
            currentValue = -torpedo->mcKin.mfAlt_m;
            limit = torpedo->mpDBObject->maxDepth_m;
            terrain = -torpedo->mcTerrain.mfHeight_m;
            currentGoal = torpedo->goalDepth_m;
        }
    }
    else
    {
        currentValue = air->mcKin.mfAlt_m;
        limit = air->mpDBObject->maxAltitude_m;
        terrain = air->mcTerrain.mfHeight_m;
        currentGoal = air->mcGS.mfGoalAltitude_m;
        if (terrain < 0) terrain = 0;
    }
    if (currentGoal > limit) currentGoal = limit;
    else if (currentGoal < 0) currentGoal = 0;

    // update scale
    while ((currentScale*increaseScaleThresh < currentGoal) && (currentScale < 40000))
    {
        currentScale *= 2.0;
    }
    while ((currentScale*decreaseScaleThresh > currentGoal) && (currentScale > 100))
    {
        currentScale *= 0.5;
    }
    
    if (limit > currentScale) limit = currentScale;
    if (terrain > currentScale) terrain = currentScale;

    float k = barRect.Height() / currentScale;


    if (isDepth)
    {
        currentRect.top = barRect.top;
        currentRect.bottom = currentRect.top - k * currentValue;
        if (currentRect.bottom < barRect.bottom) currentRect.bottom = barRect.bottom;
        yGoal = currentRect.top - k * currentGoal;
        yTerrain = currentRect.top - k * terrain;
        yLimit = currentRect.top - k * limit;
    }
    else
    {
        currentRect.bottom = barRect.bottom;
        currentRect.top = currentRect.bottom + k * currentValue;
        if (currentRect.top > barRect.top) currentRect.top = barRect.top;
        yGoal = currentRect.bottom + k * currentGoal;
        yTerrain = currentRect.bottom + k * terrain;
        yLimit = currentRect.bottom + k * limit;
    }

    currentRect.left = barRect.left;
    currentRect.right = barRect.right;

    if (mouseOverBar)
    {
        overRect.left = barRect.left;
        overRect.right = barRect.right;
        if (isDepth)
        {
            overRect.top = barRect.top;
            overRect.bottom = mousePosition.y;
        }
        else
        {
            overRect.top = mousePosition.y;
            overRect.bottom = barRect.bottom;
        }
    }

    /*
    tcRect overRect; ///< filled semi-transparent rect for mouse over position
    */
}




/**
*
*/
tcAltitudeBarControl::tcAltitudeBarControl(float x, float y, float width, float height)
:   barRect(x, x+width, y, y+height),
    fontSize(10.0f),
    fontSizeLarge(14.0f),
    increaseScaleThresh(0.5f),
    decreaseScaleThresh(0.25f),
    mouseOverBar(false),
    mouseOverUp(false),
    mouseOverDown(false),
    currentScale(800),
    color(0.4f, 1, 0.4f, 1),
    colorDim(0.2f, 0.5f, 0.2f, 1),
    neutralColor(0.8f, 0.8f, 0.8f, 1),
    dangerColor(0.8f, 0.3f, 0.3f, 1),
    warnColor(0.8f, 0.8f, 0.3f, 1),
    overColor(1, 1, 1, 0.5f)
{
    float iconSize = 12;
    upRect.Set(barRect.GetRight() + 20, barRect.GetRight() + 20 + iconSize, 
        barRect.YCenter(), barRect.YCenter() + iconSize);
    upRect.Offset(-0.5*iconSize, 0);
    downRect = upRect;

    upRect.Offset(0, 0.35*(barRect.Height()-iconSize));
    downRect.Offset(0, -0.35*(barRect.Height()-iconSize));

    LoadIcons();

    if (units == 0) // lazy init units
    {
        units = tcUnits::Get();
    }
}

/**
*
*/
tcAltitudeBarControl::~tcAltitudeBarControl()
{
}


