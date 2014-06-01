/**
**  @file tcButton.cpp
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

#include "tcButton.h"

#include "tcTexture2D.h"

#include "wxcommands.h"
#include "common/tinyxml.h"
#include "tcSound.h"
#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif 


unsigned tcButton::ref_count = 0;


/**
* Drawing Graphics object is based on parent's window since
* button is sharing a surface with the parent.
* This also allows the button to draw outside of its wxWindow
* screen area.
*/
void tcButton::Draw()
{
    if (!mbActive) return;

    StartDraw();

    // image based button drawing
	tcTexture2D* image = isButtonOn ? onImage.get() : offImage.get();
    if (isMouseOver && isInteractive)
    {        
        DrawMouseOverCaption();

        if (isButtonOn) 
		{
			image = overOnImage.get();
		}
		else
		{
			image = overOffImage.get();
		}
    }

    if (image)
    {
        if (isButtonOn && !isMouseOver && showCaptionWhenOn)
        {
            DrawMouseOverCaption();
        }

        if (!applyColorToImage)
        {
            tc3DWindow2::DrawImage(image, 0, 0, mnWidth, mnHeight, LEFT_BASE_LINE);
        }
        else
        {
            Vec4 color = (isButtonOn) ? onColor : ((isMouseOver && isInteractive) ? overColor : offColor);
            tc3DWindow2::DrawImageColored(image, 0, 0, mnWidth, mnHeight, color, LEFT_BASE_LINE);
        }

        FinishDraw();
        return;
    }

    // non-image drawing
	Vec4 backgroundColor;
    Vec4 textColor;

    if (isButtonOn)
    {
        backgroundColor = onColor;
        backgroundColor.w = backgroundAlpha;
		textColor = Vec4(0, 0, 0, backgroundAlpha);

        if (showCaptionWhenOn && !isMouseOver)
        {
            DrawMouseOverCaption();
        }
    }
    else if (isMouseOver && isInteractive)
    {
        backgroundColor = overColor;
        backgroundColor.w = backgroundAlpha;
        textColor = Vec4(0, 0, 0, backgroundAlpha);
    }
    else
    {
        backgroundColor = offColor;
        backgroundColor.w = backgroundAlpha;
        textColor = Vec4(1, 1, 1, backgroundAlpha);
    }
    
	DrawRectangle(0, 0, mnWidth, mnHeight, backgroundColor, FILL_ON);
	DrawRectangle(0, 0, mnWidth, mnHeight, Vec4(1, 1, 1, backgroundAlpha), FILL_OFF);


    //tcWindow::DrawTextInRect(graphics, font, brush, caption.c_str(), buttonRect);
    float x = 0.5f * float(mnWidth);
    float y = 0.5f * float(mnHeight);
	DrawText(caption.c_str(), x, y, defaultFont.get(), textColor, fontSize, CENTER_CENTER);

	FinishDraw();
}

void tcButton::DrawMouseOverCaption()
{
    if (mouseOverCaption.size() == 0) return;
	
    float x = (float)mouseOverCaptionPosition.x;
    float y = (float)mouseOverCaptionPosition.y;

    DrawText(mouseOverCaption.c_str(), x, y, mouseOverCaptionFont, mouseOverCaptionColor, 
		mouseOverCaptionFontSize, tc3DWindow2::AlignmentType(mouseOverCaptionAlignment));
}


/**
* Loads images for off, on, over-off, and over-on button states. Button drawing will use
* these images instead of highlighted caption text after
* a successful LoadImages call
*/
void tcButton::LoadImages(const std::string& offImageName, const std::string& onImageName,
        const std::string& overOffImageName, const std::string& overOnImageName)
{
    offImage = boost::shared_ptr<tcTexture2D>(LoadTexture(offImageName.c_str()));
    onImage = boost::shared_ptr<tcTexture2D>(LoadTexture(onImageName.c_str()));

    if (overOffImageName.length() > 3)
    {
        overOffImage = boost::shared_ptr<tcTexture2D>(LoadTexture(overOffImageName.c_str()));
    }
    if (overOnImageName.length() > 3)
    {
        overOnImage = boost::shared_ptr<tcTexture2D>(LoadTexture(overOnImageName.c_str()));
    }
}

void tcButton::LoadImages(boost::shared_ptr<tcTexture2D> offImage_, boost::shared_ptr<tcTexture2D> onImage_,
        boost::shared_ptr<tcTexture2D> overOffImage_, boost::shared_ptr<tcTexture2D> overOnImage_)
{
    offImage = offImage_;
    onImage = onImage_;
    overOffImage = overOffImage_;
    overOnImage = overOnImage_;
}

void tcButton::OnEnterWindow(wxMouseEvent& event)
{
	if (!isInteractive) return;

    isMouseOver = true;

    if (sendRedraw)
    {
        // send ID_BUTTONREDRAW message to force parent redraw
        wxCommandEvent cmd(wxEVT_COMMAND_BUTTON_CLICKED, ID_BUTTONREDRAW) ;    
        cmd.SetEventObject(this);
        AddPendingEvent(cmd);
    }
    if (!isButtonOn && (soundEffect.size() > 0)) tcSound::Get()->PlayEffect(soundEffect);
}

/**
* Treat this like a single click so fast clicks still trigger events
*/
void tcButton::OnLButtonDClick(wxMouseEvent& event)
{
	if (!isInteractive) return;

    // send command event
    wxCommandEvent cmd(wxEVT_COMMAND_BUTTON_CLICKED, command) ;    
    cmd.SetEventObject(this);
	cmd.SetExtraLong(command);
    AddPendingEvent(cmd);
}


void tcButton::OnLButtonDown(wxMouseEvent& event)
{
	if (!isInteractive) return;

    // send command event
    wxCommandEvent cmd(wxEVT_COMMAND_BUTTON_CLICKED, command) ;    
    cmd.SetEventObject(this);
	cmd.SetExtraLong(command);
    AddPendingEvent(cmd);
}

void tcButton::OnLButtonUp(wxMouseEvent& event)
{
    event.Skip();
}

void tcButton::OnLeaveWindow(wxMouseEvent& event)
{
	if (!isInteractive) return;

    isMouseOver = false;

    if (sendRedraw)
    {
        // send ID_BUTTONREDRAW message to force parent redraw
        wxCommandEvent cmd(wxEVT_COMMAND_BUTTON_CLICKED, ID_BUTTONREDRAW) ;    
        cmd.SetEventObject(this);
        AddPendingEvent(cmd);
    }
}

/**
* Normally called after parent window resize to reposition button according to
* xml configuration
*/
void tcButton::ReapplyConfig(TiXmlNode* config)
{
    wxASSERT(config);
    if (config == 0) return;

    TiXmlElement* current = config->ToElement();
    wxASSERT(current);
    if (current == 0) return;
    
    if (hostParent == 0) return;

    int x;
    int y;
    int width;
    int height;
    int ydir = 0;

    current->Attribute("X", &x);
    current->Attribute("Y", &y);
    current->Attribute("Width", &width);
    current->Attribute("Height", &height);
    current->Attribute("YDir", &ydir);

    if (ydir == 1)
    {
        wxSize parSize = hostParent->GetSize();
        y = float(parSize.GetHeight()) - y - height;
    }

    SetSize(x, y, width, height); // set all size params
}


void tcButton::SetActive(bool abActive)
{
    if (forceDisable)
    {
        tc3DWindow2::SetActive(false);
    }
    else
    {
        tc3DWindow2::SetActive(abActive);
    }
}

void tcButton::SetApplyColorToImage(bool state)
{
    applyColorToImage = state;
}


/**
*
*/
void tcButton::SetBackgroundAlpha(float val)
{
    backgroundAlpha = val;
}

/**
*
*/
void tcButton::SetFillColors(const Vec4& off_color, const Vec4& over_color,
                             const Vec4& on_color)
{
    offColor = off_color;
    overColor = over_color;
    onColor = on_color;
}

/**
*
*/
void tcButton::SetFontSize(float val)
{
    fontSize = val;
}

void tcButton::SetForceDisable(bool state)
{
    forceDisable = state;
}

void tcButton::SetInteractive(bool state)
{
    isInteractive = state;
}



void tcButton::SetMouseOverCaption(const std::string& s)
{
    mouseOverCaption = s;
}

void tcButton::SetMouseOverCaptionAlignment(int val)
{
    mouseOverCaptionAlignment = val;
}

void tcButton::SetMouseOverCaptionColor(const Vec4& color)
{
	mouseOverCaptionColor = color;
}

void tcButton::SetMouseOverCaptionFont(tcFont* font_)
{
	mouseOverCaptionFont = font_;
}

void tcButton::SetMouseOverCaptionFontSize(float val)
{
    mouseOverCaptionFontSize = val;
}

void tcButton::SetMouseOverCaptionPosition(const wxPoint& pos)
{
    mouseOverCaptionPosition = pos;
}

void tcButton::SetOffColor(const Vec4& off_color)
{
	offColor = off_color;
}

void tcButton::SetOnColor(const Vec4& on_color)
{
	onColor = on_color;
}

void tcButton::SetOverColor(const Vec4& over_color)
{
	overColor = over_color;
}


void tcButton::SetShowCaptionWhenOn(bool state)
{
    showCaptionWhenOn = state;
}


/**
* version to initialize from XML file
*/
tcButton::tcButton(tc3DWindow2 *parent, TiXmlNode *config)
: tc3DWindow2(parent, wxPoint(0,0), wxSize(10,10), "XMLButton", parent),
    offColor(0, 0, 0, 1),
    overColor(0.4f, 1, 0.4f, 1),
    onColor(1, 1, 1, 1),
    applyColorToImage(false),
    caption("NULL"),
    command(-1),
    isButtonOn(false),
	isInteractive(true),
    isMouseOver(false),
    soundEffect(""),
    fontSize(12.0f),
    sendRedraw(false),
    backgroundAlpha(1.0f),
    forceDisable(false),
    mouseOverCaption(""),
    mouseOverCaptionPosition(0, 0),
    mouseOverCaptionFontSize(10.0f),
    mouseOverCaptionAlignment(CENTER_CENTER),
    showCaptionWhenOn(false)
{

    ref_count++;

    wxASSERT(config);
    if (config == NULL) return;

    TiXmlElement* current = config->ToElement();
    wxASSERT(current);
    if (current == NULL) return;

    int x;
    int y;
    int width;
    int height;
    int command;
    double alpha;

    current->Attribute("X", &x);
    current->Attribute("Y", &y);
    current->Attribute("Width", &width);
    current->Attribute("Height", &height);

    current->Attribute("Command", &command);
    SetCommand(command);

	if (const char* s = current->Attribute("Caption"))
	{
		caption = s;
	}

	SetName(caption.c_str());

    int ydir = 0;
    current->Attribute("YDir", &ydir);

    if (ydir == 1)
    {
        wxSize parSize = parent->GetSize();
        y = float(parSize.GetHeight()) - y - height;
    }

    current->Attribute("Alpha", &alpha);
    if (alpha) backgroundAlpha = alpha;

    double xmlFontSize = fontSize;
    current->Attribute("FontSize", &xmlFontSize);
    if (xmlFontSize) fontSize = xmlFontSize;

    TiXmlNode* childNode = config->FirstChild("Image");
    if (childNode)
    {
        TiXmlElement* imageElement = childNode->ToElement();
        std::string offImageName;
        std::string onImageName;
        std::string overOnImageName;
        std::string overOffImageName;

		if (const char* s = imageElement->Attribute("Off"))
		{
			offImageName = s;
		}

		if (const char* s = imageElement->Attribute("On"))
		{
			onImageName = s;
		}
		else
		{
			onImageName = offImageName;
		}

		if (const char* s = imageElement->Attribute("OverOff"))
		{
			overOffImageName = s;
		}
		else
		{
			overOffImageName = offImageName;
		}

		if (const char* s = imageElement->Attribute("OverOn"))
		{
			overOnImageName = s;
		}
		else
		{
			overOnImageName = onImageName;
		}
		
		if (const char* s = imageElement->Attribute("SoundEffect"))
		{
			soundEffect = s;
		}

        LoadImages(offImageName, onImageName, overOffImageName, overOnImageName);

		/*
        if (offImage.valid())
        {
            width = offImage->getTextureWidth();
            height = offImage->getTextureHeight();
        }
		*/
    }

    SetSize(x, y, width, height); // set all size params

    mouseOverCaptionPosition.x = width / 2;

#ifdef _DEBUG
    fprintf(stdout,"Created button %s, pos (%d,%d), size: (%d,%d)\n",
        caption.c_str(), x, y, width, height);
#endif
}

tcButton::tcButton(tc3DWindow2* parent, const wxPoint& pos, const wxSize& size,
                   const wxString& name) 
: tc3DWindow2(parent, pos, size, name, parent),
    offColor(0, 0, 0, 1),
    overColor(0.4f, 1.0f, 0.4f, 1.0f),
    onColor(1, 1, 1, 1),
    applyColorToImage(false),
    caption("NULL"),
    command(-1),
    isButtonOn(false),
	isInteractive(true),
    isMouseOver(false),
    soundEffect(""),
    fontSize(16.0f),
    sendRedraw(false),
    backgroundAlpha(1.0f),
    forceDisable(false),
    mouseOverCaption(""),
    mouseOverCaptionPosition(size.GetWidth()/2, 0),
    mouseOverCaptionFontSize(10.0f),
    mouseOverCaptionAlignment(CENTER_CENTER),
	mouseOverCaptionColor(1.0f, 1.0f, 1.0f, 1.0f),
	mouseOverCaptionFont(defaultFont.get())
{

    ref_count++;
}

tcButton::~tcButton()
{
    wxASSERT(ref_count); 

    ref_count--;
}



