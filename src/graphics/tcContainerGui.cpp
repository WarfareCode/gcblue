/** 
**  @file tcContainerGui.cpp 
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

#include "tcContainerGui.h"
#include "common/tinyxml.h"
#include "tcGeometry.h"
#include "tcDragStatus.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_EVENT_TABLE(tcContainerGui, tcXmlWindow)
    EVT_COMMAND(86, wxEVT_COMMAND_BUTTON_CLICKED, tcContainerGui::OnCloseCommand)
END_EVENT_TABLE()


void tcContainerSlot::ClearItem()
{
	SetItem(0);
}

boost::shared_ptr<tcGeometry> tcContainerSlot::GetIcon()
{
    if (item == 0)
    {
        boost::shared_ptr<tcGeometry> nullIcon((tcGeometry*)0);
        return nullIcon;
    }
    else if (!useSmallIcon)
    {
        return item->GetIcon();
    }
    else
    {
        return item->GetIconSmall();
    }
}


tcContainerItem* tcContainerSlot::GetItem() const
{
    return item;
}

bool tcContainerSlot::IsEmpty() const 
{
    return item == 0;
}

bool tcContainerSlot::IsMouseOver() const
{
	return isMouseOver;
}

bool tcContainerSlot::IsSelected() const
{
	return isSelected;
}

bool tcContainerSlot::IsUpdated() const
{
    return updated;
}

void tcContainerSlot::SetItem(tcContainerItem* item_)
{
    if (item == item_) return;
    if (item != 0)
    {
        delete item;
    }
    item = item_;
}

void tcContainerSlot::SetMouseOver(bool state)
{
	isMouseOver = state;
}

void tcContainerSlot::SetSelected(bool state)
{
	isSelected = state;
}

void tcContainerSlot::SetUpdated(bool state)
{
    updated = state;
}

void tcContainerSlot::SetUseSmallIcon(bool state)
{
    useSmallIcon = state;
}

tcContainerSlot::tcContainerSlot()
: item(0),
  updated(false),
  isMouseOver(false),
  useSmallIcon(false),
  isSelected(false)
{
}

tcContainerSlot::tcContainerSlot(const tcContainerSlot& src)
: loc(src.loc), 
  item(src.item),
  updated(src.updated),
  isMouseOver(src.isMouseOver),
  useSmallIcon(src.useSmallIcon),
  isSelected(src.isSelected)
{
}

tcContainerSlot::~tcContainerSlot()
{
}

//------------------------------------------------------------------------------

tc3DWindow2* tcContainerGui::parent = 0;
std::list<tcContainerGui*> tcContainerGui::openContainers;


void tcContainerGui::CloseAll()
{	
	for (std::list<tcContainerGui*>::iterator iter = openContainers.begin();
		 iter != openContainers.end(); ++iter)
	{
		(*iter)->DestroyWindow();
	}

}

/**
* Set all slots to not selected
*/
void tcContainerGui::DeselectAllSlots()
{
	size_t nSlots = slots.size();
    for (size_t n=0; n<nSlots; n++)
    {
		slots[n].SetSelected(false);
    }
}

void tcContainerGui::SetParent(tc3DWindow2* win)
{
	parent = win;
}


void tcContainerGui::AddSlot(tcRect& loc, IconSize iconSize)
{
    tcContainerSlot slot;
    slot.loc = loc;
    slot.item = 0;
    slot.updated = false;
    
    if (iconSize == SMALL_ICON_SIZE)
    {
        slot.SetUseSmallIcon(true);
    }

    slots.push_back(slot);    
}

void tcContainerGui::ClearSlots()
{
    size_t nSlots = slots.size();
    for (size_t n=0; n<nSlots; n++)
    {
        if (slots[n].item != 0) delete slots[n].item;
    }
    slots.clear();
}


/**
* Performs linear search for item
* @returns item with matching id or 0 if not found
*/
tcContainerItem* tcContainerGui::GetItem(long id)
{
    wxASSERT(id != 0);
    
    size_t nSlots = slots.size();
    for (size_t n=0; n<nSlots; n++)
    {
        if (tcContainerItem* item = slots[n].GetItem())
        {
            if (item->IdMatches(id)) return item;
        }
    }
    
    return 0;
}

size_t tcContainerGui::GetNumSlots() const
{
    return slots.size();
}

tcContainerItem* tcContainerGui::GetParentItem() const
{
	return parentItem;
}

/**
* @return selected slot indices
*/
const std::vector<size_t>& tcContainerGui::GetSelected() const
{
    static std::vector<size_t> selectedIdx;

    selectedIdx.clear();

    size_t nSlots = slots.size();
    for (size_t n=0; n<nSlots; n++)
    {
        if (slots[n].IsSelected())
        {
            selectedIdx.push_back(n);
        }
    }

    return selectedIdx;
}

void tcContainerGui::Draw() 
{
    StartDraw();

	size_t nSlots = slots.size();
	for (size_t n=0; n<nSlots; n++)
	{
		tcContainerSlot& slot = slots[n];
		DrawRectangleR(slot.loc, Vec4(1, 1, 0, 1), tc3DWindow2::FILL_OFF);
	}

    DrawSelectionBox();

	FinishDraw();
}

void tcContainerGui::DrawSelectionBox()
{    
    if (draggingSelectionBox)
    {
        float w = float(mousePoint.x-selectionBoxStart.x);
        float h = float(mousePoint.y-selectionBoxStart.y);
        DrawRectangleR(float(selectionBoxStart.x), float(selectionBoxStart.y), w, h, 
            Vec4(1, 1, 1, 1), tc3DWindow2::FILL_OFF);
    }
}


/**
* @param slotIdx index of slot that is receiving drop
* @param items vector of pointer to dropped item(s)
* Method for dropping into a container GUI slot
*/
void tcContainerGui::HandleDrop(size_t slotIdx, const std::vector<tcContainerItem*>& items)
{
}

/**
* @param item pointer to dropped item
* Method for dropping into a container GUI window (not over slot)
*/
void tcContainerGui::HandleDropWindow(const std::vector<tcContainerItem*>& items)
{
}

void tcContainerGui::OnChar(wxKeyEvent& event)
{
    long keycode = event.GetKeyCode();

    switch (keycode)
    {
    case WXK_ESCAPE:
        {
            DestroyWindow();
            if (parentItem)
            {
                // clear this gui from parent item so we don't try to delete twice
                parentItem->SetGui(0); 
            }
        }
        break;
    default:
        event.Skip();
    }

}

/**
* Close and destroy window at next safe opportunity
*/
void tcContainerGui::OnCloseCommand(wxCommandEvent& event)
{
    DestroyWindow();
	if (parentItem)
	{
        // clear this gui from parent item so we don't try to delete twice
		parentItem->SetGui(0); 
	}
}


void tcContainerGui::OnLButtonDown(wxMouseEvent& event)
{
	/* check if cursor is over a non-empty slot, if so
	** arm drag with slot idx */
	wxPoint point = event.GetPosition();

    float x = (float)point.x;
    float y = (float)point.y;

    isLButtonDown = true;
    if ((point.y <= 20) || (point.y >= mnHeight))
    {
        windowDragOn = true;
        // position in parent's frame of mouse pointer
        windowDragPoint = wxPoint(mrectWindow.GetLeft() + point.x, mrectWindow.GetBottom() + point.y);

		CaptureMouse();
        return;
    }

    dragIsArmed = false;
    protectDeselectIdx = 999;

    size_t selectedSlot;
	bool foundSlot = SlotContainingPoint(point, selectedSlot);

    if (!foundSlot)
    { // start drag box
        draggingSelectionBox = true;
        selectionBoxStart = point;
        mousePoint = point;
    }

    bool controlDown = event.ControlDown(); // ctrl to select one slot at a time

    if (!controlDown)
    {
        // if we didn't click on a selected slot, clear all previous selections
        if (!foundSlot || !slots[selectedSlot].IsSelected())
        {
            for (size_t k=0; k<slots.size(); k++)
            {
                slots[k].SetSelected(false);
            }
        }
        if (foundSlot && !slots[selectedSlot].IsEmpty())
        {
            slots[selectedSlot].SetSelected(true);
            dragIsArmed = true;
        }
    }
    else // when ctrl down, add slots to selected on left down, remove them on left up
    {
        if (foundSlot && (!slots[selectedSlot].IsEmpty()) && (!slots[selectedSlot].IsSelected()))
        {
            if (!slots[selectedSlot].IsSelected())
            { 
                protectDeselectIdx = selectedSlot;
            }
            slots[selectedSlot].SetSelected(true);
            dragIsArmed = true;
        }
    }

}

void tcContainerGui::OnLButtonDClick(wxMouseEvent& event)
{
	dragIsArmed = false;
    protectDeselectIdx = 999;

    std::vector<size_t> selectedSlots = GetSelected();
    for (size_t n=0; n<selectedSlots.size(); n++)
    {
        slots[selectedSlots[n]].SetSelected(false);
    }
}

void tcContainerGui::OnLButtonUp(wxMouseEvent& event)
{
    isLButtonDown = false;
    windowDragOn = false;
	ReleaseMouse();

	wxPoint point = event.GetPosition();

    if (draggingSelectionBox)
    {
        for (size_t k=0; k<slots.size(); k++)
        {
            slots[k].SetSelected(false);
        }

        std::vector<size_t> selectedSlots = SlotsInDragBox();

        for (size_t k=0; k<selectedSlots.size(); k++)
        {
            slots[selectedSlots[k]].SetSelected(true);
        }

        draggingSelectionBox = false;
        return;
    }



	size_t selectedSlot;
	bool foundSlot = SlotContainingPoint(point, selectedSlot);

	dragIsArmed = false;

	tcDragStatus* dragStatus = tcDragStatus::Get();
    if (dragStatus->IsDragging())
    {
        std::vector<tcContainerItem*> containerItems = dragStatus->GetDraggedItems();
        if (containerItems.size() > 0)
        {
            /* check if cursor is over an empty slot, if so
            ** handle drag (drop) */
            if (foundSlot)
            {
                wxASSERT(selectedSlot < slots.size());

                containerItems[0]->SetQuantity(dragStatus->GetQuantity());
                HandleDrop(selectedSlot, containerItems);
            }
            else
            {
                containerItems[0]->SetQuantity(dragStatus->GetQuantity());
                HandleDropWindow(containerItems);
            }
        }

        // clear drag
        dragStatus->StopDrag();
    }
    else if (event.ControlDown()) // check for de-selecting a slot on left button up with CTRL pressed
    {
        if (foundSlot && (slots[selectedSlot].IsSelected()) && (selectedSlot != protectDeselectIdx))
        {
            slots[selectedSlot].SetSelected(false);
        }    
    }


}

void tcContainerGui::OnLeaveWindow(wxMouseEvent& event)
{
	// clear mouseover state since OnMouseMove sometimes not called before leaving window
	size_t nSlots = slots.size();

	for (size_t n=0; n<nSlots; n++)
	{
	    slots[n].SetMouseOver(false);
	}
}

/**
* Update mouseover status of slots
*/
void tcContainerGui::OnMouseMove(wxMouseEvent& event)
{
    wxPoint point = event.GetPosition();
    mousePoint = point;

	UpdateWindowDrag(point);

    // update mouseover status of all slots
    float x = (float)point.x;
    float y = (float)point.y;

	size_t nSlots = slots.size();
	bool foundSlot = false;
	for (size_t n=0; n<nSlots; n++)
	{
		if (!foundSlot && !draggingSelectionBox)
		{
			slots[n].SetMouseOver(slots[n].loc.ContainsPoint(x, y));
		}
		else
		{
			slots[n].SetMouseOver(false);
		}
	}
	
	// check for start of a drag operation
	if (!dragIsArmed) return;

	// start drag
    std::vector<size_t> selectedSlots = GetSelected();
    std::vector<tcContainerItem*> items;
    for (size_t n=0; n<selectedSlots.size(); n++)
    {
	    tcContainerItem* item = slots[selectedSlots[n]].GetItem();
	    if (item != 0)
        {
            items.push_back(item);
        }
    }
    if (items.size() == 0)
    {
        return;
    }

	tcDragStatus* dragStatus = tcDragStatus::Get();
	dragStatus->StartDrag(this, items);
	dragIsArmed = false;

	tcSound::Get()->PlayEffect("Thuck");

}

void tcContainerGui::RegisterGui()
{
	openContainers.push_back(this);
}


void tcContainerGui::UnregisterGui()
{
	std::list<tcContainerGui*>::iterator iter = 
		find(openContainers.begin(), openContainers.end(), this);

	if (iter != openContainers.end())
	{
		openContainers.erase(iter);
	}
	else
	{
		fprintf(stderr, "tcContainerGui::UnregisterGui - not found in registry %s\n",
			wxWindow::GetName().c_str());
	}
}


void tcContainerGui::UpdateWindowDrag(const wxPoint& pos)
{
    if (!windowDragOn) return;


    // position in parent's frame of mouse pointer
    wxPoint current = wxPoint(mrectWindow.GetLeft() + pos.x, mrectWindow.GetBottom() + pos.y);
    if (current != windowDragPoint)
    {
        wxPoint delta = current - windowDragPoint;
		int xmove = mrectWindow.GetLeft() + delta.x;
		int ymove = mrectWindow.GetTop() + delta.y;
        tc3DWindow2::MoveWindow(xmove, ymove);
        windowDragPoint = current;
    }
}

void tcContainerGui::SetParentItem(tcContainerItem* item)
{
	parentItem = item;
}

/**
* @return true if point <pos> is over a slot
* @param slotIdx set to index of containing slot
*/
bool tcContainerGui::SlotContainingPoint(const wxPoint& point, size_t& slotIdx) const
{
    float x = (float)point.x;
    float y = (float)point.y;

	size_t nSlots = slots.size();
	bool foundSlot = false;

	for (size_t n=0; (n<nSlots)&&(!foundSlot); n++)
	{
		if (slots[n].loc.ContainsPoint(x, y))
		{
			slotIdx = n;
            return true;
        }
    }

    slotIdx = 999;
    return false;
}

/**
* @return true if point <pos> is over a slot
* @param slotIdx set to index of containing slot
*/
const std::vector<size_t>& tcContainerGui::SlotsInDragBox() const
{
    static std::vector<size_t> result;

    result.clear();

    tcRect box;
    box.left = float(std::min(selectionBoxStart.x, mousePoint.x));
    box.right = float(std::max(selectionBoxStart.x, mousePoint.x));
    box.bottom = float(std::min(selectionBoxStart.y, mousePoint.y));
    box.top = float(std::max(selectionBoxStart.y, mousePoint.y));


	size_t nSlots = slots.size();

	for (size_t n=0; n<nSlots; n++)
	{
        if (box.ContainsPoint(slots[n].loc.XCenter(), slots[n].loc.YCenter()))
		{
            result.push_back(n);
        }
    }

    return result;
}


/**
* static method SetParent must be called first
*/
tcContainerGui::tcContainerGui(const wxPoint& pos, const wxString& configFile, const wxString& name) 
                             : tcXmlWindow(parent, pos, wxSize(10, 10), configFile, name, parent),
	drawCount(0),
	dragIsArmed(false),
	parentItem(0),
	isLButtonDown(false),
    windowDragOn(false),
    protectDeselectIdx(999),
    draggingSelectionBox(false)
{

	// put gui window on top
	SetBaseRenderBin(parent->GetBaseRenderBin() + windowLayer*10);
	wxWindow::Raise();

	tc3DWindow2::SetStencilLayer(windowLayer-3); // assumes windowLayer starts at 4

	windowLayer++;

    TiXmlNode* root = config->FirstChild("Window");
    if (!root)
    {
        fprintf(stderr, "tcContainerGui::tcContainerGui - Missing top level <Window> tag\n");
        return;
    }

	TiXmlNode* current = root;

	/*
    TiXmlElement* elt = current->ToElement();
    
	// background image
	std::string imageName = elt->Attribute("BackgroundImage");
	if (imageName.size() > 2)
	{
		LoadBackgroundImage(imageName.c_str());
	}

	// size of window
	
	int xmlWidth, xmlHeight;
	elt->Attribute("Width", &xmlWidth);
	elt->Attribute("Height", &xmlHeight);

	SetSize(pos.x, pos.y, xmlWidth, xmlHeight); // set all size params
	*/

	// add slots
	current = root->FirstChild("Slot");
    while (current)
    {
		int x = 0;
		int y = 0;
		int size = 0;
		TiXmlElement* elt = current->ToElement();
		elt->Attribute("X", &x);
		elt->Attribute("Y", &y);
		elt->Attribute("Size", &size);

		tcRect loc;
		loc.Set(x, x+size, y, y+size);
		AddSlot(loc);

        current = current->NextSibling("Slot");
    }

    SetUseRenderSurface(true);
    SetRenderSurfaceUpdateInterval(4);

	SetActive(true);

	RegisterGui();

#ifdef _DEBUG
	fprintf(stdout, "tcContainerGui::tcContainerGui - %s, %d slots\n", name.c_str(),
		slots.size());
#endif

    SetBorderDraw(true);

}

tcContainerGui::~tcContainerGui() 
{
	if (parentItem)
	{
		parentItem->SetGui(0);
	}

    for (size_t n=0; n<slots.size(); n++)
    {
        if (!slots[n].IsEmpty())
		{
			slots[n].ClearItem();
		}
    } 

	windowLayer--;

	UnregisterGui();

    tcDragStatus* dragStatus = tcDragStatus::Get();
    if (dragStatus->IsDragging() && (dragStatus->GetItemGui() == this))
    {
        dragStatus->StopDrag();
    }
}


