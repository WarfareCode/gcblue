/**  
**  @file tcStoresGui.h
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



#ifndef _TCSTORESGUI_H_
#define _TCSTORESGUI_H_

#if _MSC_VER > 1000
#pragma once
#endif 

#include "tcContainerGui.h"
#include "tcStoresContainerItem.h"


class tcStores;

/**
* GUI class for stores operations
*/
class tcStoresGui : public tcContainerGui
{
public:
    static tcStoresGui* GetExistingGui(long id, long host);

    virtual void Draw();

    long GetPlatformId() const;
    long GetHostId() const;

    virtual void OnChar(wxKeyEvent& event);
    //virtual void OnEnterWindow(wxMouseEvent& event);
    virtual void OnLButtonDown(wxMouseEvent& event);
    virtual void OnLButtonDClick(wxMouseEvent& event);
    //virtual void OnLButtonUp(wxMouseEvent& event);
    //virtual void OnLeaveWindow(wxMouseEvent& event);
	virtual void OnMouseMove(wxMouseEvent& event);
    virtual void OnRButtonDown(wxMouseEvent& event);


    tcStoresGui(long id, long host, unsigned int idx, const wxPoint& pos, 
		const wxString& configFile);

    virtual ~tcStoresGui();
private:
	const long platformId; ///< id of platform that holds the stores object
	const long hostId; ///< -1 if none, or id of host platform
	const unsigned int storesIdx; ///< idx of stores on platform

    float slotSize; ///< dimension of (square) slot
    wxRealPoint upperLeft; ///< upper-left of first slot
    float horizontalSpacing;
    float verticalSpacing;
    unsigned int rowSize;

    size_t slotsPerPage;
    size_t nPages;
    size_t currentPage;
    size_t mouseOverPage;
    const size_t maxSlots;
    std::vector<tcRect> pageBoxes;
    unsigned int lastKeypressTime;
    bool keyboardWait;
    
    void AddOrUpdateItem(tcContainerSlot& slot, const std::string& itemName,
             unsigned int quantity, bool isMoving, unsigned int itemId, tcStores* stores);
	tcStores* GetStores();
	void HandleDrop(size_t slotIdx, const std::vector<tcContainerItem*>& items);
    void HandleDropWindow(const std::vector<tcContainerItem*>& items);
    void InitializeGui();
    void ReadGuiParameters();
    void SetCurrentPage(size_t page);
    void IncrementPage(int dir);

    void UpdateGui();
    tcPlatformObject* GetPlatform() const;
};

#endif

