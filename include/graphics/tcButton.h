/**  
**  @file tcButton.h
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


#ifndef _TCBUTTON_H_
#define _TCBUTTON_H_

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
class tcButton : public tc3DWindow2
{
public:
    virtual void Draw();
    const std::string& GetCaption() const {return caption;}
    long GetCommand() const {return command;}
	bool GetInteractive() const {return isInteractive;}
    bool IsOn() {return isButtonOn;}

    void LoadImages(const std::string& offImageName, const std::string& onImageName,
        const std::string& overOffImageName, const std::string& overOnImageName);
    void LoadImages(boost::shared_ptr<tcTexture2D> offImage_, boost::shared_ptr<tcTexture2D> onImage_,
        boost::shared_ptr<tcTexture2D> overOffImage_, boost::shared_ptr<tcTexture2D> overOnImage_);

    virtual void SetActive(bool abActive);
    void SetBackgroundAlpha(float val);
    void SetCaption(const std::string& s) {caption = s;}
    void SetShowCaptionWhenOn(bool state);
    void SetCommand(long cmd) {command = cmd;}   
    void SetFillColors(const Vec4& off_color, const Vec4& over_color,
        const Vec4& on_color);
	void SetOffColor(const Vec4& off_color);
	void SetOnColor(const Vec4& on_color);
	void SetOverColor(const Vec4& over_color);
    void SetApplyColorToImage(bool state);

    void SetFontSize(float val);
    void SetForceDisable(bool state);
	void SetInteractive(bool state);
    void SetMouseOverCaption(const std::string& s);
    void SetMouseOverCaptionPosition(const wxPoint& pos);
    void SetMouseOverCaptionFontSize(float val);
    void SetMouseOverCaptionAlignment(int val);
	void SetMouseOverCaptionColor(const Vec4& color);
	void SetMouseOverCaptionFont(tcFont* font_);

    void SetOn(bool state) {isButtonOn = state;}
    void SetSendRedraw(bool state) {sendRedraw = state;}
    void SetSoundEffect(const std::string& effect) {soundEffect = effect;}

    void ReapplyConfig(TiXmlNode* config);

    tcButton(tc3DWindow2 *parent, const wxPoint& pos, const wxSize& size,
            const wxString& name = "PushButton");
    tcButton(tc3DWindow2 *parent, TiXmlNode *config);
    virtual ~tcButton();

protected:
    std::string caption;
    long command;
    bool isButtonOn;
	bool isInteractive; ///< false to ignore mouseover and click events
    bool isMouseOver;
    std::string soundEffect;
    float fontSize;
    bool sendRedraw; ///< true to send redraw message to parent on button state change
    float backgroundAlpha;  ///< transparency value for solid color background
    bool forceDisable; ///< if true then do not enable button
    std::string mouseOverCaption; ///< additional caption to draw when mouse is over button
    wxPoint mouseOverCaptionPosition; ///< location to draw mouse over caption at
    float mouseOverCaptionFontSize;
    int mouseOverCaptionAlignment;
	Vec4 mouseOverCaptionColor;
	tcFont* mouseOverCaptionFont;

    bool applyColorToImage; ///< true to apply fill colors when using image option (to fade or alter image)
    bool showCaptionWhenOn; ///< draw caption when on (vs. just on mouse over)

    Vec4 offColor;
    Vec4 overColor;
    Vec4 onColor;
	

    boost::shared_ptr<tcTexture2D> offImage;
    boost::shared_ptr<tcTexture2D> overOffImage;
    boost::shared_ptr<tcTexture2D> onImage;
    boost::shared_ptr<tcTexture2D> overOnImage;

	/*
    static Gdiplus::Pen *pen;
    static Gdiplus::SolidBrush *brush;
    static Gdiplus::Font *font;
	*/
    static unsigned ref_count;

    void DrawMouseOverCaption();
    virtual void OnEnterWindow(wxMouseEvent& event);
    virtual void OnLButtonDown(wxMouseEvent& event);
    virtual void OnLButtonDClick(wxMouseEvent& event);
    virtual void OnLButtonUp(wxMouseEvent& event);
    virtual void OnLeaveWindow(wxMouseEvent& event);
};

#endif

