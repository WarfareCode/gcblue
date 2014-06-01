/**
**  @file tcDragStatus.h 
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


#ifndef _DRAGSTATUS_H_
#define _DRAGSTATUS_H_

#if _MSC_VER > 1000
#pragma once
#endif 

#include <wx/wx.h> 
#include <boost/shared_ptr.hpp>
#include <vector>

class tcContainerGui;
class tcContainerItem;
class tcGeometry;

/**
* Singleton class to support drag and drop of icons across multiple windows.
* Acts as a global object for windows to interact with to get 
* mouse pointer status.
*/
class tcDragStatus
{
public:
    const std::vector<tcContainerItem*>& GetDraggedItems() const;
    size_t GetDraggedItemCount() const;
    tcContainerItem* GetDraggedFirstItem() const;
    tcContainerGui* GetItemGui() const;
    tcGeometry* GetIcon();
    unsigned int GetQuantity() const;
    bool IsDragging() const; ///< true if drag is in progress
    bool IsDraggingItem(tcContainerItem* item) const;
    void SetIcon(boost::shared_ptr<tcGeometry> icon_);
    void SetQuantity(unsigned int n);
    void StartDrag(tcContainerGui* gui, const std::vector<tcContainerItem*> items);
    void StopDrag();
    float CurrentDragDistance() const;
    
	static tcDragStatus* Get();

private:
    tcContainerGui* itemGui;
    std::vector<unsigned int> itemId;
    unsigned int quantity; ///< if > 0, then draw quantity label while dragging
    boost::shared_ptr<tcGeometry> icon;
    wxPoint dragStartPos;
    
	tcDragStatus();
    ~tcDragStatus();
};

#endif

