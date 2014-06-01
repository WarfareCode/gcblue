/**
**  @file tcListBox.cpp 
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

#include "tcListBox.h"
#include "tcTime.h"
#include "common/tinyxml.h"
#include "tcSound.h"
#include "tcScrollBar.h"
#include "tcTexture2D.h"
#include <iostream>
#include "tcTime.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif 


BEGIN_EVENT_TABLE(tcListBox, tc3DWindow2)
    EVT_COMMAND(-1, wxEVT_COMMAND_SCROLLBAR_UPDATED, tcListBox::OnScrollbarUpdated)
END_EVENT_TABLE()


void tcListBox::AddItem(const std::string& s, const std::string& popupText)
{
    ItemInfo itemToAdd;
    itemToAdd.itemName = s;
    itemToAdd.popupText = popupText;

    listItems.push_back(itemToAdd);

    size_t showItems = std::min(maxShow, listItems.size());

    showSize.Set(mnWidth, (1+showItems)*baseSize.GetHeight());

    if (showList)
    {
        OpenList();
    }
}

void tcListBox::Clear()
{
    listItems.clear();
    current = "";
    selectedItem = -1;
    overItem = -1;
    scrollOffset = 0;
    blinkCurrent = false;

    if (showList)
    {
        OpenList();
    }

}

void tcListBox::CloseList()
{
    if (forceShow) return;

    wxWindow::SetSize(baseSize);
    showList = false;

    scrollBar->SetActive(false);
}

void tcListBox::Draw()
{
    wxString s;

    if (!mbActive) {return;}   

    if (linkedValue != 0)
    {
        SelectItemByIndex(*linkedValue);
    }

    StartDraw();

    unsigned int t = tcTime::Get()->Get30HzCount();
    bool blinkOn = (t % 30) < 15;


    if (!blinkCurrent || blinkOn)
    {
        DrawTextInRectR(current.c_str(), textBox, defaultFont.get(), textColor, 
            fontSize, LEFT_CENTER);
    }


    DrawRectangleR(mainBox, backgroundColor, FILL_ON);
    DrawRectangleR(mainBox, borderColor, FILL_OFF);

    if (!isMouseOver)
    {
        DrawImageR(arrowDown.get(), dropButton.GetLeft(), dropButton.GetBottom(), dropButton.Width(), dropButton.Height());
    }
    else
    {
        DrawImageR(arrowDownOver.get(), dropButton.GetLeft(), dropButton.GetBottom(), dropButton.Width(), dropButton.Height());

    }

    if (showList)
    {
        int leftOffset = 0; // to be able to show the longer loadout names

        tcRect itemBox = textBox;
        itemBox.left -= leftOffset;
        float dy = float(itemBox.Height());
        size_t nShow = std::min(listItems.size(), maxShow);

        tcRect showBox(mainBox.left-leftOffset, mainBox.right, dy, dy*(float(nShow + 1)));
        DrawRectangleR(showBox, backgroundColor, FILL_ON);
        DrawRectangleR(showBox, borderColor, FILL_OFF);

        for (size_t n=0; n<nShow; n++)
        {
            itemBox.Offset(0, dy);
            if (int(n) != overItem)
            {
                //DrawRectangleR(itemBox, backgroundColor, FILL_ON);
                //DrawRectangleR(itemBox, borderColor, FILL_OFF);

                DrawTextInRectR(listItems[n+scrollOffset].itemName.c_str(), itemBox, defaultFont.get(), textColor,
                    fontSize, LEFT_CENTER);
            }
            else
            {
                //DrawRectangleR(itemBox, borderColorOver, FILL_OFF);
                //DrawRectangleR(itemBox, backgroundColorOver, FILL_ON);
                DrawTextInRectR(listItems[n+scrollOffset].itemName.c_str(), itemBox, defaultFont.get(), textColorOver,
                    fontSize, LEFT_CENTER);

                if (((t - overTime) > 30) && (listItems[n+scrollOffset].popupText.size() > 0))
                {
                    wxSize size;
                    MeasureText(defaultFont.get(), fontSize, listItems[n+scrollOffset].popupText.c_str(), size);
                    tcRect popupBox(-180, -180+size.GetWidth()+5, 65, 65+size.GetHeight());

                    //DrawRectangleR(popupBox, Vec4(0.5, 0.5, 0.5, 0.5), FILL_ON);
                    DrawTextInRectR(listItems[n+scrollOffset].popupText.c_str(), popupBox, defaultFont.get(), Vec4(1,1,1,1),
                        fontSize, LEFT_CENTER);
                }
            }
        }
    }

	FinishDraw();
}

const std::string& tcListBox::GetCaption() const
{
    return current;
}


int tcListBox::GetItemContainingPoint(const wxPoint& pos)
{
    // find box we're in and highlight
    tcRect itemBox = mainBox;
    float dy = float(itemBox.Height());
    for (size_t n=0; n<listItems.size(); n++)
    {
        itemBox.Offset(0, dy);
        if (itemBox.ContainsPoint(pos.x, pos.y))
        {
            return int(n);
        }
    }

    return -1;
}

size_t tcListBox::GetListSize() const
{
    return listItems.size();
}

size_t tcListBox::GetScrollOffset() const
{
    return scrollOffset;
}



bool tcListBox::GetShowList() const
{
    return showList;
}


void tcListBox::LinkValue(int* pVal)
{
    linkedValue = pVal;
}

/**
*
*/
void tcListBox::OnKeyDown(wxKeyEvent& event) 
{
    long keycode = event.GetKeyCode();

    if (keycode == WXK_BACK)
    {
        
    }
	else if (keycode == WXK_UP)
	{
        ScrollUp();
	}
    else if (keycode == WXK_DOWN)
    {
        ScrollDown();
    }
	else if (keycode == WXK_LEFT)
	{

	}
	else if (keycode == WXK_RIGHT)
	{

	}
    else if (keycode == WXK_ESCAPE)
    {
    }
    else 
    {
        event.Skip(); // OnChar will be called
    }
}

void tcListBox::OnChar(wxKeyEvent& event) 
{
//    long keycode = event.KeyCode();
 
    event.Skip();
}


void tcListBox::OnEnterWindow(wxMouseEvent& event)
{
    isMouseOver = true;
    SetFocus();
}

void tcListBox::OnLButtonDown(wxMouseEvent& event)
{
	wxPoint pos = event.GetPosition();

	if (!dropButton.ContainsPoint(pos.x, pos.y) && !textBox.ContainsPoint(pos.x, pos.y))
    {
        event.Skip();
        return;
    }

    if (showList)
    {
        CloseList();
    }
    else
    {
        OpenList();
    }
}

void tcListBox::OnLButtonUp(wxMouseEvent& event)
{
    if (!showList) return;

    wxPoint pos = event.GetPosition();

    int upBoxIdx = GetItemContainingPoint(pos);

    if (upBoxIdx != -1)
    {
        SelectItem(upBoxIdx);
        CloseList();
    }

}

void tcListBox::OnLeaveWindow(wxMouseEvent& event)
{
    isMouseOver = false;
}

void tcListBox::OnMouseMove(wxMouseEvent& event)
{
    wxPoint pos = event.GetPosition();

    if (!showList) return;

    int previousItem = overItem;
    overItem = GetItemContainingPoint(pos);
    if (overItem != previousItem)
    {
        overTime = tcTime::Get()->Get30HzCount();
    }
}

void tcListBox::OnMouseWheel(wxMouseEvent& event)
{
    int zDelta = event.GetWheelRotation();
    
    if (zDelta > 0) 
    {
        ScrollUp();
    }
    else if (zDelta < 0) 
    {
        ScrollDown();
    }
}

void tcListBox::OnScrollbarUpdated(wxCommandEvent& event)
{
    if (maxShow < listItems.size())
    {
        float yOffset = 0.25 * float(event.GetExtraLong());

        float barFract = float(maxShow) / float(listItems.size());
        float hScroll = float(scrollBar->GetSize().GetHeight());
        scrollOffset = float(listItems.size()) * (yOffset / hScroll) * barFract / (1.0f - barFract);

        //scrollOffset = size_t(floorf(yOffset / float(maxShow)));
        if (scrollOffset > (listItems.size() - maxShow))
        {
            scrollOffset = listItems.size() - maxShow;
        }
    }
    
}

void tcListBox::OpenList()
{
    wxWindow::SetSize(showSize);
    showList = true;

    wxSize scrollBarSize(baseSize.GetHeight(), showSize.GetHeight()-baseSize.GetHeight());

    scrollBar->SetSize(baseSize.GetWidth()-baseSize.GetHeight(), baseSize.GetHeight(), 
        scrollBarSize.GetWidth(), scrollBarSize.GetHeight());

    if (listItems.size() > maxShow)
    {
        scrollBar->SetActive(true);
        scrollBar->SetBarFraction(float(maxShow) / float(listItems.size()));
    }
    else
    {
        scrollBar->SetActive(false);
    }

    Raise();
}

void tcListBox::RemoveItem(const std::string& s)
{
    std::vector<ItemInfo> temp;

    for (size_t n=0; n<listItems.size(); n++)
    {
        if (listItems[n].itemName != s)
        {
            temp.push_back(listItems[n]);
        }
    }

    listItems = temp;

    size_t showItems = std::min(maxShow, listItems.size());

    showSize.Set(mnWidth, (1+showItems)*baseSize.GetHeight());

    if (current == s)
    {
        SetCaption("");
        SelectItem(0);
    }
}

void tcListBox::SelectItem(const std::string& s)
{
    if (current == s) return;

    for (size_t n=0; n<listItems.size(); n++)
    {
        if (listItems[n].itemName == s)
        {
            SelectItem(int(n) - int(scrollOffset));
            return;
        }
    }
}

/**
* Select item by index of 0 to maxItems-1 (isn't relative to scroll page unlike SelectItem)
*/
void tcListBox::SelectItemByIndex(int idx)
{
    if ((idx < 0) || (idx >= listItems.size())) return;

    int newItem = idx;
    if (newItem == selectedItem) return;

    selectedItem = newItem;
    current = listItems[size_t(idx) + scrollOffset].itemName;

    if (linkedValue != 0)
    {
        *linkedValue = newItem;
    }

    SendUpdateEvent();
}


void tcListBox::SelectItem(int idx)
{
    if (idx < 0) return;
    if (scrollOffset + size_t(idx) >= listItems.size())
    {
        wxASSERT(false);
        return;
    }

    int newItem = idx + int(scrollOffset);

    if (newItem == selectedItem) return;

    selectedItem = newItem;
    current = listItems[size_t(idx) + scrollOffset].itemName;

    if (linkedValue != 0)
    {
        *linkedValue = newItem;
    }

    SendUpdateEvent();

}

void tcListBox::SendUpdateEvent()
{
    wxCommandEvent command(wxEVT_COMMAND_TEXT_UPDATED, commandId);    
    command.SetEventObject(this);
    command.SetString(current.c_str());
    AddPendingEvent(command); // TODO add handler added in tcGame for this event
}


void tcListBox::SetCommand(long cmd) 
{
    commandId = cmd;
}

void tcListBox::SetForceShow(bool state)
{
    forceShow = state;
    OpenList();
}

/**
* Sets maximum number of items to show at once
*/
void tcListBox::SetMaxShow(size_t n)
{
    maxShow = n;

    size_t showItems = std::min(maxShow, listItems.size());
    showSize.Set(mnWidth, (1+showItems)*baseSize.GetHeight());
}

void tcListBox::ScrollDown()
{
    if (maxShow < listItems.size())
    {
        scrollOffset++;

        if (scrollOffset > (listItems.size() - maxShow))
        {
            scrollOffset = listItems.size() - maxShow;
        }

        scrollBar->SetBarPosition(float(scrollOffset), float(maxShow));
    }
    else
    {
        scrollOffset = 0;
    }
}

void tcListBox::ScrollUp()
{
    if ((maxShow < listItems.size()) && (scrollOffset > 0))
    {
        scrollOffset--;

        scrollBar->SetBarPosition(float(scrollOffset), float(maxShow));
    }
    else
    {
        scrollOffset = 0;
    }
}

void tcListBox::SetBlinkCurrent(bool state)
{
    blinkCurrent = state;
}

void tcListBox::SetCaption(const std::string& s)
{
    current = s;
}

void tcListBox::SetColor(Vec4& textColor_, Vec4& textColorOver_,
                         Vec4& borderColor_, Vec4& borderColorOver_,
                         Vec4& backgroundColor_, Vec4& backgroundColorOver_)
{
    textColor = textColor_;
    textColorOver = textColorOver_;
    borderColor = borderColor_;
    borderColorOver = borderColorOver_;
    backgroundColor = backgroundColor_;
    backgroundColorOver = backgroundColorOver_;
}

void tcListBox::SetFontSize(float val)
{
    fontSize = val;
}

tcListBox::tcListBox(tc3DWindow2* parent, const wxPoint& pos, const wxSize& size, const wxString& name)
            : tc3DWindow2(parent, pos, size, name, parent),
            showList(false),
            forceShow(false),
            selectedItem(-1),
            overItem(-1),
            isMouseOver(false),
            commandId(0),
            maxShow(6),
            scrollOffset(0),
            blinkCurrent(false),
            textColor(0.2f, 0.2f, 0.3f, 1.0f),
            textColorOver(0.3f, 0.3f, 0.5f, 1.0f),
            borderColor(0.5, 0.5, 0.5, 0.5),
            borderColorOver(0.9f, 0.9f, 0.9f, 0.9f),
            backgroundColor(0.7f, 0.7f, 0.7f, 0.8f),
            backgroundColorOver(0.9f, 0.9f, 0.9f, 0.9f),
            fontSize(11.0f),
            linkedValue(0)
{
    
    int scrollBarWidth = 12.0f;
    
    int xDropButton = size.GetWidth() - scrollBarWidth - 1;
    int yDropButton = (size.GetHeight() - scrollBarWidth)/2;

    mainBox.Set(0, size.GetWidth(), 0, size.GetHeight());
    textBox.Set(5.0f, size.GetWidth(), 0, size.GetHeight());

    dropButton.Set(xDropButton, xDropButton+scrollBarWidth, yDropButton, yDropButton+scrollBarWidth);

    baseSize = size;
    showSize = size;

    scrollBar = new tcScrollBar(this, wxPoint(size.GetWidth()-scrollBarWidth, 0), wxSize(scrollBarWidth, scrollBarWidth));
    arrowDown = boost::shared_ptr<tcTexture2D>(tc3DWindow2::LoadTexture("arrow_down2.png"));
    arrowDownOver = boost::shared_ptr<tcTexture2D>(tc3DWindow2::LoadTexture("arrow_down_over2.png"));
}

tcListBox::~tcListBox()
{

}
