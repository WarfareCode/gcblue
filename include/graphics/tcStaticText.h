/**  
**  @file tcStaticText.h
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


#ifndef _TCSTATICTEXT_H_
#define _TCSTATICTEXT_H_

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
* Push button class derived from tc3DWindow.
*/
class tcStaticText : public tc3DWindow2
{
public:
    virtual void Draw();
    const std::string& GetCaption() const {return caption;}

    virtual void SetActive(bool abActive);

    void SetCaption(const std::string& s) {caption = s;}
   
    void SetColors(const Vec4& background_, const Vec4& backgroundOver_,
                   const Vec4& text_, const Vec4& textOver_);
    void SetFontSize(float val);
    
    void SetTooltipCaption(const std::string& s);
    void SetTooltipCaptionPosition(const wxPoint& pos);
    void SetTooltipCaptionFontSize(float val);
    void SetTooltipCaptionAlignment(int val);


    tcStaticText(tc3DWindow2 *parent, const wxPoint& pos, const wxSize& size,
            const wxString& name = "StaticText");
    virtual ~tcStaticText();

protected:
    std::string caption;
    
    bool isMouseOver;
    float fontSize;
    
    std::string tooltipCaption; ///< additional caption to draw when mouse is over button
    wxPoint tooltipCaptionPosition; ///< location to draw mouse over caption at
    float tooltipCaptionFontSize;
    int tooltipCaptionAlignment;
   
    Vec4 backgroundColor;
    Vec4 backgroundOverColor;
    Vec4 textColor;
    Vec4 textOverColor;

    void DrawTooltipCaption();
    virtual void OnEnterWindow(wxMouseEvent& event);
    virtual void OnLeaveWindow(wxMouseEvent& event);
};

#endif

