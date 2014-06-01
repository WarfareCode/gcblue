/**  
**  @file tcContainerItem.h
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



#ifndef _TCCONTAINERITEM_H_
#define _TCCONTAINERITEM_H_

#if _MSC_VER > 1000
#pragma once
#endif 

#include <boost/shared_ptr.hpp>
#include <string>

class tcGeometry;
class tcContainerGui;

/**
* Item for container gui
*/
class tcContainerItem
{
public:
	enum
	{
		NORMAL = 0, 
        BLINK = 1, 
        DRAGGING = 2, ///< item is being dragged by user
        BLINK2 = 3 ///< another blink state
	};

	boost::shared_ptr<tcGeometry> icon;
    boost::shared_ptr<tcGeometry> iconSmall;
	int drawState;

	int GetDrawState() const;
	tcContainerGui* GetGui() const;
	boost::shared_ptr<tcGeometry> GetIcon();
    boost::shared_ptr<tcGeometry> GetIconSmall(); ///< half sized icon
	unsigned int GetId() const;
	const std::string& GetItemName() const;
	unsigned int GetQuantity() const;
    const char* GetQuantityLabel() const;
	bool IdMatches(unsigned int val) const;
	bool ItemGuiIsActive() const;
	void SetDrawState(int state);
	void SetGui(tcContainerGui* gui_);
    void SetIcon(boost::shared_ptr<tcGeometry> icon_);
	void SetId(unsigned int val);
	void SetItemName(const std::string& s);
	void SetQuantity(unsigned int n);
	
	tcContainerItem();
	virtual ~tcContainerItem();
protected:
    unsigned int id; ///< identifier for item
	std::string itemName;
    unsigned int quantity; ///< quantity associated with this item
    tcContainerGui* gui; ///< for items that pop up an associated gui to allow gui to be closed or moved
};


#endif

