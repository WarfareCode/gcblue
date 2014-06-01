/**
**  @file tcListBox.h
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


#ifndef _LISTBOX_H_
#define _LISTBOX_H_

#if _MSC_VER > 1000
#pragma once
#endif 

#include "tc3DWindow2.h"
#include <boost/shared_ptr.hpp>
#include "tv_types.h"


class tcScrollBar;
class tcTexture2D;

/**
*
*/
class tcListBox : public tc3DWindow2
{
public:
    struct ItemInfo
    {
        std::string itemName;
        std::string popupText;
    };
    virtual void Draw();

    void Clear();

    void AddItem(const std::string& s, const std::string& popupText="");
    void RemoveItem(const std::string& s);

    void SetCommand(long cmd);
    const std::string& GetCaption() const;
    void SetCaption(const std::string& s);
    void SelectItem(const std::string& s);
    void SelectItemByIndex(int idx);

    void SetBlinkCurrent(bool state);
    bool GetShowList() const;
    void CloseList();
    void SetMaxShow(size_t n);
    void SetForceShow(bool state);
    void LinkValue(int* pVal);

    /// these for debugging
    size_t GetScrollOffset() const;
    size_t GetListSize() const;

    void SetColor(Vec4& textColor_, Vec4& textColorOver_,
                  Vec4& borderColor_, Vec4& borderColorOver_,
                  Vec4& backgroundColor_, Vec4& backgroundColorOver_);
    void SetFontSize(float val);


    tcListBox(tc3DWindow2* parent, const wxPoint& pos, const wxSize& size,
        const wxString& name = "ListBox");
    virtual ~tcListBox();
private:
    std::string current;
    bool blinkCurrent;
    std::vector<ItemInfo> listItems;
    bool showList;
    bool forceShow; ///< if true, always show list
    int selectedItem;
    int overItem;
    bool isMouseOver;
    unsigned int overTime; ///< time that mouse was first over current item
    long commandId;
    tcRect mainBox;
    tcRect textBox;
    tcRect dropButton;
    wxSize baseSize; ///< size when not showing list
    wxSize showSize; ///< size when showing list
    Vec4 textColor;
    Vec4 textColorOver;
    Vec4 borderColor;
    Vec4 borderColorOver;
    Vec4 backgroundColor;
    Vec4 backgroundColorOver;
    float fontSize;

    int* linkedValue; ///< update this with selection index when not null
    
    tcScrollBar* scrollBar;
    size_t maxShow; ///< maximum items to show in list, scroll for rest
    size_t scrollOffset; ///< first item to show in list
	boost::shared_ptr<tcTexture2D> arrowDown;
    boost::shared_ptr<tcTexture2D> arrowDownOver;

    virtual void OnChar(wxKeyEvent& event);
    virtual void OnEnterWindow(wxMouseEvent& event);
    virtual void OnKeyDown(wxKeyEvent& event);
    virtual void OnLButtonDown(wxMouseEvent& event);
    virtual void OnLButtonUp(wxMouseEvent& event);
    virtual void OnLeaveWindow(wxMouseEvent& event);
    virtual void OnMouseMove(wxMouseEvent& event);
    virtual void OnMouseWheel(wxMouseEvent& event);
    virtual void OnScrollbarUpdated(wxCommandEvent& event);

    int GetItemContainingPoint(const wxPoint& pos);

    void OpenList();

    void SelectItem(int idx);

    void ScrollDown();
    void ScrollUp();
    void SendUpdateEvent();

    DECLARE_EVENT_TABLE()
};

#endif

