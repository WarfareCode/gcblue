/**  
**  @file tcPanel.cpp
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

#include "stdwx.h"

#ifndef WX_PRECOMP
#include "wx/wx.h" 
#endif

#include "tcPanel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif 

tc3DWindow2* tcPanel::parentWindow = 0;


void tcPanel::AddItem(std::string caption, int cmd, float x, float y, float width, float height)
{
    tsItemData item;

    item.Clear();
    item.caption = caption;
    item.command = "";
    item.userInput = "";
    item.cmd = cmd;
    item.rect.left = x;
    item.rect.bottom = y;
    item.rect.right = x + width;
    item.rect.top = y + height;

    panelItems.push_back(item);
}

void tcPanel::AddItem(std::string caption, std::string command, 
					  float x, float y, float width, float height, int param)
{

    tsItemData item;

    item.Clear();
    item.caption = caption;
    item.command = command;
    item.userInput = "";
    item.cmd = param;
    item.rect.left = x;
    item.rect.bottom = y;
    item.rect.right = x + width;
    item.rect.top = y + height;

    panelItems.push_back(item);
}

/**
* version for user input with callback
*/
void tcPanel::AddItemUI(std::string caption, std::string callback, std::string input,
                        float x, float y, float width, float height, int param) 
{
    tsItemData item;

    item.Clear();
    item.caption = caption;
    item.command = callback;
    item.userInput = input;
    item.cmd = param;  // used as parameter to pass to python callback function
    item.rect.left = x;
    item.rect.bottom = y;
    item.rect.right = x + width;
    item.rect.top = y + height;

    panelItems.push_back(item);
}

/**
* sets isBold to true for last item added to panel
*/
void tcPanel::BoldLastItem()
{
    tsItemData& item = panelItems.back();
    item.isBold = true;
}

void tcPanel::ClearSelected() 
{
    int nItems = (int)panelItems.size();  

    for(int i=0; i<nItems; i++) 
	{
        tsItemData *item = &panelItems[i];
        item->isSelected = false;
    }
}

void tcPanel::Clear() 
{
//    int nItems = (int)panelItems.size();  

    panelItems.clear();
    mbUpdateRegions = true;
}

void tcPanel::Draw() 
{
	wxASSERT(parentWindow);

    if (mbUpdateRegions) 
    {
        UpdateBox();
        mbUpdateRegions = false;
    }

	Vec4 color(0, 0, 0, 1);

	color.set(0.8f, 0.8f, 0.6f, 0.8f);

	//parentWindow->DrawRectangleR(boundingBox, color, tc3DWindow::FILL_OFF);

    // draw title caption
    color.set(1.0f, 1.0f, 1.0f, 1.0f);

	parentWindow->DrawTextInRectR(title.c_str(), titleBox, parentWindow->GetDefaultFont(),
        color, fontSize, tc3DWindow2::CENTER_CENTER);


    int nItems = (int)panelItems.size();  // number of panelItems in menu

    for (int i=0; i<nItems; i++) 
    {
        tsItemData *item = &panelItems[i];
        DrawItem(item);
    }
}

void tcPanel::DrawItem(tsItemData *item) 
{
	Vec4 color;
	float alpha = 0.8f;


    //if the menu item is selected
    if (item->isSelected)
	{
		color.set(0, 0.04f, 0.21f, alpha);
    }
    else 
	{ 
		color.set(0.8f, 0.8f, 0.84f, alpha);
    }

    tcRect item_rect = item->rect;
    item_rect.Offset(anchor.x, anchor.y);
    
	parentWindow->DrawRectangleR(item_rect, color, tc3DWindow2::FILL_ON);

    if (item->isSelected) 
	{
		color.set(1, 1, 1, alpha);
    }
    else 
	{ 
        color.set(0, 0, 0, alpha);
    }

    wxRealPoint pointf(item->rect.GetLeft() + border_width, item->rect.GetTop());  
    pointf = pointf + anchor;

    //Font *font = (item->isBold) ? mpBoldFont : mpFont;

	//parentWindow->DrawTextInRectR(item->caption.c_str(), item_rect, parentWindow->GetDefaultFont(),
	//	color, fontSize, LEFT_CENTER);
	parentWindow->DrawTextR(item->caption.c_str(), item_rect.left, item_rect.top, 
		parentWindow->GetDefaultFont(), color, fontSize, tc3DWindow2::LEFT_BASE_LINE);
}



void tcPanel::InitWithDefaults()
{
    for (int i=0; i<6; i++)
    {
        char buff[64];
        float x = 10.0f + (float)i * 50.0f;
        float y = 30.0f;
        sprintf(buff, "", i);
        AddItem(buff, -1, x, y, 40.0f, 15.0f);
    }
    title = "No data available.";
}

/**
* @return pointer to item (NULL for none) containing point 
*/
tsItemData* tcPanel::ItemContainingPoint(const wxRealPoint& point) 
{
    int nItems = (int)panelItems.size();  

    wxRealPoint local_point = point - anchor; // adjust for anchor

    for(int i=0; i<nItems; i++) 
	{
        tsItemData *item = &panelItems[i];
        if (item->rect.ContainsPoint(local_point.x, local_point.y)) 
		{
            return item;
        }
    }
    return NULL; // not found
}

/**
* select menu item and all parent panelItems containing point 
*/
bool tcPanel::UpdateSelection(const wxRealPoint& point) 
{
    int nItems = (int)panelItems.size();  

    wxRealPoint local_point = point - anchor; // adjust for anchor

    bool bResult = false;
    for(int i=0; i<nItems; i++) 
	{
        tsItemData *item = &panelItems[i];
        if (item->rect.ContainsPoint(local_point.x, local_point.y)) 
        {
            bool hasCommand = (item->cmd != -1) || (item->command.length() > 0);
            item->isSelected = hasCommand;
        }
        else 
        {
            item->isSelected = false;
        }
    }
    return bResult; // not found
}

void tcPanel::UpdateBox()
{
    int nItems = (int)panelItems.size();  

	boundingBox.Set(0, 0, 0, 0);

    for(int i=0; i<nItems; i++) 
	{
        tsItemData *item = &panelItems[i];
        float right = item->rect.GetRight();
        float bottom = item->rect.GetBottom();
        boundingBox.right = (right > boundingBox.right) ? right : boundingBox.right;
        boundingBox.top = (bottom > boundingBox.top) ? bottom : boundingBox.top;
    }
    boundingBox.right += border_width + 10.0f;
    boundingBox.top += border_width + 10.0f;
    
    titleBox = boundingBox;
    titleBox.top = titleBox.bottom + border_width;
}

tcPanel::tcPanel() 
: fontSize(12.0)
{
    title = "";
    panelItems.clear();
    mbUpdateRegions = true;
    border_width = 0*12.0f;
}

tcPanel::tcPanel(tcPanel* apParent) 
: fontSize(12.0)
{
    panelItems.clear();
    mbUpdateRegions = true;
}



tcPanel::~tcPanel()
{
    Clear();
}
