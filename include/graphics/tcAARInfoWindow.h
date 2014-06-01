/**  
**  @file tcAARInfoWindow.h
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


#ifndef _TCAARINFOWINDOW_H_
#define _TCAARINFOWINDOW_H_

#if _MSC_VER > 1000
#pragma once
#endif 

#include "tcXmlWindow.h"
#include "tcRegistered.h"
#include <stdarg.h>
#include "tcGoalTracker.h"

class tcScrollBar;

/**
* Window class to display info for database object
*/
class tcAARInfoWindow : public tcXmlWindow, public tcRegistered
{
public:
    virtual void Draw();

    virtual void OnChar(wxKeyEvent& event);
	virtual void OnCloseCommand(wxCommandEvent& event);
    virtual void OnEnterWindow(wxMouseEvent& event);
    virtual void OnLButtonDown(wxMouseEvent& event);
    virtual void OnLButtonUp(wxMouseEvent& event);
    virtual void OnLeaveWindow(wxMouseEvent& event);
	virtual void OnMouseMove(wxMouseEvent& event);
    virtual void OnMouseWheel(wxMouseEvent& event);
    virtual void OnKeyDown(wxKeyEvent& event);

    //virtual void OnRButtonDown(wxMouseEvent& event);
	void OnScrollbarUpdated(wxCommandEvent& event);

    /// set AAR file name to display
    void SetAARFileName(const wxString& fileName);

	static void SetParent(tc3DWindow2* win);
	

    tcAARInfoWindow(const wxPoint& pos,
		const wxString& configFile = "xml/aar_info.xml",
        const wxString& name = "AARInfo",
        tc3DWindow2* hostParent = parent);

    virtual ~tcAARInfoWindow();
    
protected:	
    unsigned int drawCount;

private:
	wxPoint mousePosition;
	bool mouseOver;
	tcScrollBar* scrollBar;
	float yOffset;	
    
    
    std::string displayFileName; ///< file name of AAR
    tcGoalTracker::AARSummary aar;


	static tc3DWindow2* parent;

	void DrawAARInfo();

    void PrintText(float xleft, float& x, float& y, const Vec4& color, bool newLine, const char* formatString, ...);


    DECLARE_EVENT_TABLE()
};

#endif

