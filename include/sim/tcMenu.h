/** 
**  @file tcMenu.h
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


#if _MSC_VER > 1000
#pragma once
#endif

#ifndef _TCMENU_H_
#define _TCMENU_H_

#include "wx/wx.h" 
#include "simmath.h"
#include "tc3DWindow2.h"

#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>

class tcGeometry;
class tcMenu;

struct tsMenuData
{
    std::string mzCaption;
    std::string mzCommand;
    std::string mzUserInput;
    std::string textParam;
    int mnCommand;
    bool mbSelected;
    bool mbTop;
    bool mbBottom;
    tcRect mrect;   
    tcMenu *mpSubMenu;
    bool closePopup; ///< true (default) to close popup after command

    void Clear() 
    {
        mzCaption="";mzCommand="";mzUserInput="";textParam="";
        mnCommand=0;mbSelected=0;mbTop=0;mbBottom=0;mpSubMenu=NULL;
        closePopup=true;
    }
};

/**
* Note: this class mixes view/display with data, may have to be separated later
* This class should be converted to a tc3DWindow (or something more logical).
* The current code is a hack to get this to work with new 3D window system.
*/
class tcMenu 
{
public:
    static float yOffset; // added to allow margin for menu to draw above popup point when near bottom of screen

    void AddItem(const std::string& caption, int command);
    void AddItem(const std::string& caption, const std::string& command, int param = -1);
    void AddItem(const std::string& caption, const std::string& command, 
		const std::string& textParam);
    void AddItemUI(const std::string& caption, const std::string& callback, 
		const std::string& input, int param = -1);
	void AddItemUI(const std::string& caption, const std::string& callback, 
		const std::string& input, const std::string& textParam);
    void BeginSubMenu();
    void Clear();
    void ClearSelected();
    void Draw();
    virtual void DrawItem(tsMenuData* apMD);
    void EndSubMenu();

    tsMenuData* ItemContainingPoint(const wxRealPoint& point);
    bool UpdateSelection(const wxRealPoint& point);

    void SetAnchor(const wxRealPoint& p) {anchor = p;}
    void UpdateRegions();

    void GetCurrentSelections(std::vector<unsigned int>& selection) const;
    void SetCurrentSelections(const std::vector<unsigned int>& selection);

	static void SetParentWindow(tc3DWindow2* win) {parentWindow = win;}
	static void SetSubmenuIconRenderBin(int bin);
    static void SetStayOpen(bool state);

	static tc3DWindow2* parentWindow; ///< workaround to make this work with 3D window system

    tcMenu();
    tcMenu(tcMenu* apParent);
    virtual ~tcMenu();

private:
    std::vector<tsMenuData> maMenuData;
    tcMenu *mpParent;
    tcMenu *mpCurrent; // current menu level to add items to
    wxRealPoint anchor; // reference point (upper left) for drawing menu
    float mfItemWidth, mfItemHeight;
	const float fontSize;
    tcRect menubox; // rectangle encompassing entire menu
    bool mbUpdateRegions;

    static boost::shared_ptr<tcGeometry> submenuIcon;
    static boost::shared_ptr<tcGeometry> stayOpenIcon; ///< for menu items that don't close the menu after a command
    static bool newItemsStayOpen;

	static void InitSubmenuIcon();
};


#endif