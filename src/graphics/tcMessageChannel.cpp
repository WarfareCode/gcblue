/** 
**  @file tcMessageChannel.cpp 
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

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "wx/string.h"

#include "tcMessageChannel.h"
#include "tc3DWindow2.h"

#include <stdio.h>
#include <iostream>
#include "tcTime.h"
#include "tcUserInfo.h"
#include "tcMapOverlay.h"
#include "tcMapAlertObject.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif 

tcMapOverlay* tcMessageChannel::mapOverlay = 0;

void tcMessageChannel::AttachMapOverlay(tcMapOverlay* mo)
{
    mapOverlay = mo;
}


/**
*
*/
void tcMessageChannel::AddMessage(const std::string& text, unsigned int alliance, const Vec4& color)
{
    Msg temp;
    temp.text = text;
    temp.color = color;
    temp.alliance = alliance;

    messages.push_back(temp);

    if ((alliance == 0) || tcUserInfo::Get()->IsOwnAlliance(alliance))
    {
        HandleSpecialMessage(text);
    }
}

/**
* Clears all messages from channel
*/
void tcMessageChannel::Clear()
{
	messages.clear();
}

/**
* @param allianceMask use 0 to draw everything
*/
void tcMessageChannel::Draw(tc3DWindow2* graphics, unsigned int allianceMask)
{
    wxASSERT(graphics);

    DrawActivationButton(graphics);

    if (!isActive) return;

    DrawMessageText(graphics, allianceMask);
   
}

/**
*
*/
void tcMessageChannel::DrawActivationButton(tc3DWindow2* graphics)
{
    wxASSERT(graphics);

    // draw title button
    Vec4 buttonColor(0, 0, 0.2f, 1);
    Vec4 buttonTextColor(1, 1, 1, 1);
    tcFont* font = graphics->GetDefaultFont();
    if (isActive)
    {
        buttonColor.set(1, 1, 1, 1);
        buttonTextColor.set(0, 0, 0, 1);
    }
    else if (isMouseOver)
    {
        buttonColor.set(0.1f, 0.1f, 0.5f, 1.0f);
        buttonTextColor.set(1, 1, 1, 1);
    }

    tcRect borderRect = activationRect;
    borderRect.Expand(1.0, 1.0);

    graphics->DrawRectangleR(borderRect, buttonTextColor, tc3DWindow2::FILL_OFF);
    graphics->DrawRectangleR(activationRect, buttonColor, tc3DWindow2::FILL_ON);
    graphics->DrawTextR(channelName.c_str(), activationRect.XCenter(), activationRect.YCenter(),
        font, buttonTextColor, buttonFontSize, tc3DWindow2::CENTER_CENTER);

}

/**
*
*/
void tcMessageChannel::DrawMessageText(tc3DWindow2* graphics, unsigned int allianceMask)
{
    wxASSERT(graphics);

    Vec4 borderColor(1, 1, 1, 1);
    tcFont* font = graphics->GetDefaultFont();

    std::deque<Msg>::reverse_iterator iter;
    float x = textRect.left + 10.0;
    float y = textRect.top - 5.0f;

    //wxSize size;
    //graphics->MeasureText(font, fontSize, "Tg", size);
    //float lineSpacing = float(size.GetHeight()) + 2.0;

    for (iter = messages.rbegin(); iter != messages.rend(); ++iter)
    {
        if ((iter->alliance == allianceMask) || (allianceMask == 0) || (iter->alliance == 0))
        {
            wxSize size;
            graphics->MeasureText(font, fontSize, iter->text.c_str(), size);
            float lineSpacing = float(size.GetHeight()) + 2.0;

            y -= lineSpacing;
            if (y >= textRect.bottom + 10)
            {
                graphics->DrawTextR(iter->text.c_str(), x, y,
                    font, iter->color, fontSize, tc3DWindow2::LEFT_TOP);
            }
        }
    }
    
    //graphics->DrawRectangleR(textRect, borderColor, tc3DWindow2::FILL_OFF);
}


/**
*
*/
const std::string& tcMessageChannel::GetName() const
{
    return channelName;
}


/**
* Call when new message is received to check for special message type
* to create alert graphics for user
*/
void tcMessageChannel::HandleSpecialMessage(const std::string& text)
{
    if (channelName != "MapAlert") return;
    
    wxString s(text);

    //"FLASH3 %2.3f %2.3f High yield detonation detected"
    wxString x = s.BeforeFirst(' ');
    s = s.AfterFirst(' ');

    if (x == "FLASH3")
    {
        x = s.BeforeFirst(' ');
        s = s.AfterFirst(' ');

        double lat_deg = 0;
        double lon_deg = 0;
        bool result = x.ToDouble(&lat_deg);

        x = s.BeforeFirst(' ');
        s = s.AfterFirst(' ');
        result = x.ToDouble(&lon_deg) || result;

        tcMapAlertObject* obj = new tcMapAlertObject(s.ToStdString(), lon_deg, lat_deg);
        obj->LoadIcon("images\\nuke2525.png");
        obj->SetAlignBottom(true); // draw mushroom root at center
        wxASSERT(mapOverlay != 0);
        mapOverlay->AddMapObject(obj);

    }
    
}

/**
*
*/
bool tcMessageChannel::IsActive() const
{
    return isActive;
}


/**
*
*/
bool tcMessageChannel::IsPointInActivationRect(const wxPoint& p) const
{
    return activationRect.ContainsPoint(float(p.x), float(p.y));
}

/**
*
*/
void tcMessageChannel::SetActivationRect(tcRect r)
{
    activationRect = r;
}

/**
*
*/
void tcMessageChannel::SetActive(bool state)
{
    isActive = state;
}

/**
*
*/
void tcMessageChannel::SetMouseOver(bool state)
{
    isMouseOver = state;
}

/**
*
*/
void tcMessageChannel::SetTextRect(tcRect r)
{
    textRect = r;
}

/**
*
*/
tcMessageChannel::tcMessageChannel(const std::string& name)
: channelName(name),
  isActive(false),
  isMouseOver(false),
  fontSize(16),
  buttonFontSize(12),
  activationRect(20, 80, 20, 40),
  textRect(50, 700, 50, 500)
{

}

/**
*
*/
tcMessageChannel::~tcMessageChannel()
{
}
