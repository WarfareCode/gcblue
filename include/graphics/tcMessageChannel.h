/**
**  @file tcMessageChannel.h 
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


#ifndef _MESSAGECHANNEL_H_
#define _MESSAGECHANNEL_H_

#if _MSC_VER > 1000
#pragma once
#endif 

#include "wx/wx.h" 
#include "wx/string.h"
#include <queue>
#include "tv_types.h"
#include "tcRect.h"

class tc3DWindow2;
class tcMapOverlay;

/**
*
*/
class tcMessageChannel
{
public:
    struct Msg
    {
        std::string text;
        Vec4 color;
        unsigned int alliance; ///< for filtering display by alliance
    };

    std::string channelName;
    std::deque<Msg> messages; ///< chat text to display

    void AddMessage(const std::string& text, unsigned int alliance = 0, const Vec4& color = Vec4(1, 1, 1, 1));
	void Clear();
    void Draw(tc3DWindow2* graphics, unsigned int allianceMask);
    const std::string& GetName() const;
    bool IsActive() const;
    bool IsPointInActivationRect(const wxPoint& p) const;
    void SetActivationRect(tcRect r);
    void SetActive(bool state);
    void SetMouseOver(bool state);
    void SetTextRect(tcRect r);

    tcMessageChannel(const std::string& name);
    virtual ~tcMessageChannel();

    static void AttachMapOverlay(tcMapOverlay* mo);

private:
    static tcMapOverlay* mapOverlay;

    float fontSize; 
    float buttonFontSize;
    tcRect activationRect; ///< rectangle for activation button
    tcRect textRect; ///< rectangle for text message display
    bool isActive;
    bool isMouseOver;

    void DrawActivationButton(tc3DWindow2* graphics);
    void DrawMessageText(tc3DWindow2* graphics, unsigned int allianceMask);
    void HandleSpecialMessage(const std::string& text);
};


#endif

