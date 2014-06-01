/**  
**  @file tcPanel.h
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

#ifndef _TCPANEL_H_
#define _TCPANEL_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "wx/wx.h" 

#include "simmath.h"
#include "tc3DWindow2.h"
#include <string>
#include <vector>


struct tsItemData 
{
    std::string caption;
    std::string command;
    std::string userInput;
    int cmd;
    bool isSelected;
    bool isBold;
    tcRect rect;   

    void Clear() 
    {
        caption="";command="";userInput="";
        cmd = 0;isSelected=0;isBold=0;
    }
};

/**
* note: this class mixes view/display with data, may have to be separated later
* Needs refactoring to update to coherent system just like tcMenu
* @see tcMenu
*/
class tcPanel 
{
public:
    void AddItem(std::string caption, std::string command, 
                    float x, float y, float width, float height, int param = -1);
    void AddItem(std::string caption, int cmd, float x, float y, float width, float height);
    void AddItemUI(std::string caption, std::string callback, std::string input, 
                    float x, float y, float width, float height, int param = -1);
    void BoldLastItem();
    void Clear();
    void ClearSelected();
    void Draw();
    virtual void DrawItem(tsItemData *item);
    void InitWithDefaults();
    tsItemData* ItemContainingPoint(const wxRealPoint& point);
    bool UpdateSelection(const wxRealPoint& point);
    static void ReleaseGdi();
    void SetAnchor(const wxRealPoint& p) {anchor = p;}
    void SetTitle(std::string new_title) {title = new_title;}
    void UpdateBox();

	static void SetParentWindow(tc3DWindow2* win) {parentWindow = win;}

	static tc3DWindow2* parentWindow; ///< workaround to make this work with 3D window system

    tcPanel();
    tcPanel(tcPanel* apParent);
    virtual ~tcPanel();
private:
    std::string title;
    std::vector<tsItemData> panelItems;   
    wxRealPoint anchor; ///< reference point (upper left) for drawing menu
    float mfItemWidth, mfItemHeight;
    tcRect boundingBox; ///< rectangle encompassing entire control
    tcRect titleBox; ///< rectangle for title
    bool mbUpdateRegions;
    float border_width;
    const float fontSize;
};

#endif

