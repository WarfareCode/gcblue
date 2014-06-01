/**  
**  @file tcContainerGui.h
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



#ifndef _TCCONTAINERGUI_H_
#define _TCCONTAINERGUI_H_

#if _MSC_VER > 1000
#pragma once
#endif 

#include "tcXmlWindow.h"
#include "tcContainerItem.h"
#include <list>
#include <vector>


class tcContainerSlot
{
public:
	tcRect loc; ///< location of slot within gui window
	tcContainerItem* item; ///< 0 if slot is empty
    bool updated;
	bool isMouseOver; ///< true if mouse is over slot
    bool useSmallIcon;
    bool isSelected; ///< true if this item is part of group selection

	void ClearItem();
    boost::shared_ptr<tcGeometry> GetIcon();
    tcContainerItem* GetItem() const;
	bool IsEmpty() const;
	bool IsMouseOver() const;
    bool IsSelected() const;
	bool IsUpdated() const;
    void SetUseSmallIcon(bool state);
	void SetItem(tcContainerItem* item_);
	void SetMouseOver(bool state);
    void SetSelected(bool state);
	void SetUpdated(bool state);

	tcContainerSlot();
	tcContainerSlot(const tcContainerSlot& src);
	~tcContainerSlot();
};




/**
* GUI class to drag and drop and do simple operations on iconified objects
*/
class tcContainerGui : public tcXmlWindow
{
public:
    enum IconSize
    {
        NORMAL_ICON_SIZE = 1,
        SMALL_ICON_SIZE = 2
    };
    void AddSlot(tcRect& loc, IconSize iconSize = NORMAL_ICON_SIZE);
    void ClearSlots();
	void DeselectAllSlots();
    size_t GetNumSlots() const;
    
    virtual void Draw();

    virtual void OnChar(wxKeyEvent& event);
	virtual void OnCloseCommand(wxCommandEvent& event);
    //virtual void OnEnterWindow(wxMouseEvent& event);
    virtual void OnLButtonDown(wxMouseEvent& event);
	virtual void OnLButtonDClick(wxMouseEvent& event);
    virtual void OnLButtonUp(wxMouseEvent& event);
    virtual void OnLeaveWindow(wxMouseEvent& event);
	virtual void OnMouseMove(wxMouseEvent& event);
    //virtual void OnRButtonDown(wxMouseEvent& event);

    virtual tcContainerItem* GetItem(long id);

	tcContainerItem* GetParentItem() const;
	void SetParentItem(tcContainerItem* item);

	static void CloseAll(); ///< close all open tcContainerGui windows
	static void SetParent(tc3DWindow2* win);
	
    tcContainerGui(const wxPoint& pos, 
		const wxString& configFile,
        const wxString& name = "ContainerGui");

    virtual ~tcContainerGui();
    
protected:	
    std::vector<tcContainerSlot> slots;
    unsigned int drawCount;
	bool dragIsArmed; ///< true to start drag when mouse is moved
    size_t protectDeselectIdx; ///< used to not immediately deselect a ctrl-selected slot on left mouse button up
    
    bool draggingSelectionBox; ///< true when left mouse button down and dragging a selection box
    wxPoint selectionBoxStart;
    wxPoint mousePoint;

	// params for window drag (move this function to base class?)
    bool isLButtonDown;
    bool windowDragOn;
	wxPoint windowDragPoint;

    virtual void HandleDrop(size_t slotIdx, const std::vector<tcContainerItem*>& items);
    virtual void HandleDropWindow(const std::vector<tcContainerItem*>& items);
    void UpdateWindowDrag(const wxPoint& pos);
    bool SlotContainingPoint(const wxPoint& point, size_t& slotIdx) const;
    const std::vector<size_t>& tcContainerGui::SlotsInDragBox() const;
    const std::vector<size_t>& GetSelected() const;
    virtual void DrawSelectionBox();

	static std::list<tcContainerGui*> openContainers; ///< to allow closing all open GUIs

private:
	tcContainerItem* parentItem; ///< item that was clicked to popup this gui (if applicable)
	static tc3DWindow2* parent;


	void RegisterGui();
	void UnregisterGui();

    DECLARE_EVENT_TABLE()
};

#endif

