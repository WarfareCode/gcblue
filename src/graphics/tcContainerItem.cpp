/** 
**  @file tcContainerItem.cpp 
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

#include "tcContainerItem.h"
#include "tcContainerGui.h"

#include "tcGeometry.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



int tcContainerItem::GetDrawState() const
{
	return drawState;
}

tcContainerGui* tcContainerItem::GetGui() const
{
	return gui;
}

boost::shared_ptr<tcGeometry> tcContainerItem::GetIcon()
{
    return icon;
}

boost::shared_ptr<tcGeometry> tcContainerItem::GetIconSmall()
{
    return iconSmall;
}

unsigned int tcContainerItem::GetId() const
{
    return id;
}

const std::string& tcContainerItem::GetItemName() const
{
    return itemName;
}

unsigned int tcContainerItem::GetQuantity() const
{
    return quantity;
}

/**
* @return quantity label, characters k and M are used for thousands and millions
*/
const char* tcContainerItem::GetQuantityLabel() const
{
    static wxString s;

    if (quantity > 99999)
    {
        s.Printf("%.1fM", 1e-6 * float(quantity));
    }
    else if (quantity > 999)
    {
        s.Printf("%.1fk", 1e-3 * float(quantity));
    }
    else
    {
        s.Printf("%d", quantity);
    }

    return s.c_str();
}

/**
* @return true if val matches id of this item AND val != 0
* 0 is used as an invalid id
*/
bool tcContainerItem::IdMatches(unsigned int val) const
{
    return (id == val);
}

bool tcContainerItem::ItemGuiIsActive() const
{
	return gui != 0;
}

void tcContainerItem::SetDrawState(int state)
{
	drawState = state;
}

void tcContainerItem::SetGui(tcContainerGui* gui_)
{
	gui = gui_;
}

void tcContainerItem::SetIcon(boost::shared_ptr<tcGeometry> icon_)
{
    if (icon_.get() == 0) return;

    icon = boost::shared_ptr<tcGeometry>(new tcGeometry(*icon_.get()));

    iconSmall = boost::shared_ptr<tcGeometry>(new tcGeometry(*icon_.get()));

    // scale by 0.625 (32 -> 20)
    iconSmall->SetSize(0.625f * iconSmall->GetSize());
}

void tcContainerItem::SetId(unsigned int val)
{
    id = val;
}

void tcContainerItem::SetItemName(const std::string& s)
{
	itemName = s;
}

void tcContainerItem::SetQuantity(unsigned int n)
{
    quantity = n;
}


tcContainerItem::tcContainerItem()
:   drawState(NORMAL),
    id(0),
    itemName(""),
    quantity(0),
	gui(0)
{
}

tcContainerItem::~tcContainerItem()
{
	if (gui)
	{
        if (gui->GetParentItem() == this)
        {
		    gui->SetParentItem(0);
        }
	}
}



