/** 
**  @file tcDragStatus.cpp 
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

#include "tcDragStatus.h"
#include "tcContainerGui.h"
#include "tcContainerItem.h"
#include "tcGeometry.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/**
* Accessor for singleton instance
*/
tcDragStatus* tcDragStatus::Get()
{
    static tcDragStatus instance;
    
    return &instance;
}

/**
* Calculates distance between drag start mouse pos and
* current mouse pos. Returns 0 if drag is not in progress.
*/
float tcDragStatus::CurrentDragDistance() const
{
    if (IsDragging())
    {
        wxPoint pos = wxGetMousePosition();
        wxPoint delta = pos - dragStartPos;

        float dx = float(delta.x);
        float dy = float(delta.y);
            
        return sqrtf(dx*dx + dy*dy);
    }
    else
    {
        return 0;
    }
}

tcContainerItem* tcDragStatus::GetDraggedFirstItem() const
{
    if (itemId.size() > 0)
    {
        return itemGui->GetItem(itemId[0]);
    }
    else
    {
        return 0;
    }
}

/**
* @return dragged item or 0 if not found or invalid
*/
const std::vector<tcContainerItem*>& tcDragStatus::GetDraggedItems() const
{
    static std::vector<tcContainerItem*> items;

    items.clear();

    if ((itemId.size() == 0) || (itemGui == 0)) return items;
    
    for (size_t n=0; n<itemId.size(); n++)
    {
        items.push_back(itemGui->GetItem(itemId[n]));
    }

    return items;
}

size_t tcDragStatus::GetDraggedItemCount() const
{
    return itemId.size();
}

tcGeometry* tcDragStatus::GetIcon()
{
    return icon.get();
}

tcContainerGui* tcDragStatus::GetItemGui() const
{
    return itemGui;
}

unsigned int tcDragStatus::GetQuantity() const
{
    return quantity;
}

bool tcDragStatus::IsDragging() const
{
    return (itemId.size() > 0) && (itemId[0] != 0);
}

/**
* Only checks first item for group drag
*/
bool tcDragStatus::IsDraggingItem(tcContainerItem* item) const
{
    wxASSERT(item != 0);
    
    return (itemId.size() > 0) && (item->IdMatches(itemId[0]));
}

void tcDragStatus::SetIcon(boost::shared_ptr<tcGeometry> icon_)
{
    icon = icon_;
}

void tcDragStatus::SetQuantity(unsigned int n)
{
    quantity = n;
}

void tcDragStatus::StartDrag(tcContainerGui* gui, const std::vector<tcContainerItem*> items)
{
    if ((items.size() == 0) || (items[0] == 0))
    {
        wxASSERT(false);
        return;
    }

	wxASSERT(itemId.size() == 0);

	itemGui = gui;

    itemId.clear();
    for (size_t n=0; n<items.size(); n++)
    {
        itemId.push_back(items[n]->GetId());
    }


    icon = items[0]->GetIcon();
	quantity = items[0]->GetQuantity();

    dragStartPos = wxGetMousePosition();
}

void tcDragStatus::StopDrag()
{
    itemGui = 0;
    itemId.clear();
    quantity = 0;
    dragStartPos.x = -999;
    dragStartPos.y = -999;
}
    

tcDragStatus::tcDragStatus()
: itemGui(0), quantity(0), dragStartPos(0, 0)
{
}

tcDragStatus::~tcDragStatus()
{
}


