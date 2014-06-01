/**  
**  @file tcAARViewer.h
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

#ifndef _AARVIEWER_H_
#define _AARVIEWER_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "wx/wx.h" 
#include "wx/dir.h"


#include "tcXmlWindow.h"
#include "tcSound.h"

class tcAARInfoWindow;
class tc3DViewer;
class tcButton;
class tcAARBrowsePanel;

namespace osg
{
	class Texture2D;
}

/** 
* Class to browse and view AARs from past scenarios
*/
class tcAARViewer : public tcXmlWindow 
{
	struct BrowseItem
	{
		std::string className; ///< dir name or filename without the .py extension
		struct
		{
			float x;
			float y;
			float width;
			float height;
		} drawBox;          ///< location to draw to screen
        Vec4 color;
		enum {OFF = 0, OVER = 1, ON = 2} drawState;
	};
public:    
    void BuildBrowseInfo();
	void Draw();
    void OnChar(wxKeyEvent& event);
    void OnKeyDown(wxKeyEvent& event);
	void OnLButtonDown(wxMouseEvent& event);
    void OnMouseMove(wxMouseEvent& event);
    void OnSize(wxSizeEvent& event);
    const wxString& GetDisplayFileName() const;
    void SelectDisplayFileName(const wxString& fileName);
    void SelectDisplayFileName(wxCommandEvent& event);

    tcAARViewer(wxWindow* parent,
        const wxPoint& pos, const wxSize& size, 
        const wxString& name = "AARViewer", tc3DWindow2* graphicsHost = 0);

	virtual ~tcAARViewer();


private:
    wxString displayFileName; ///< file name of AAR displayed
	tcAARBrowsePanel* browsePanel;
    tcAARInfoWindow* infoWindow;

    std::vector<tcButton*> buttons;

	const wxRealPoint basePosition;
	wxPoint mousePosition;

    void InitializeButtons();
    void InitializeInfoWindow();
	void InitializeBrowsePanel();
    void SetButtonOn(size_t idx);

    DECLARE_EVENT_TABLE()
};




#endif