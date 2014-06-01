/** 
**  @file tcStoresGui.cpp 
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

#include "tcStoresGui.h"
#include "tcStores.h"
#include "tcPlatformGui.h"

#include "common/tinyxml.h"
#include "tcTime.h"
#include "tcDragStatus.h"
#include "tcGameObject.h"
#include "tcLauncherContainerItem.h"
#include "tcLauncher.h"
#include "tcSimState.h"
#include "tcGeometry.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif




tcStoresGui* tcStoresGui::GetExistingGui(long id, long host)
{
    std::list<tcContainerGui*>::iterator iter = 
        openContainers.begin();

    for (iter=openContainers.begin(); iter!=openContainers.end(); ++iter)
    {
        if (tcStoresGui* storesGui = dynamic_cast<tcStoresGui*>(*iter))
        {
            if ((storesGui->GetPlatformId() == id) && (storesGui->GetHostId() == host))
            {
                return storesGui;
            }
        }

    }
    return 0;
}



/**
* If slot has tcStoresContainerItem then update it, otherwise create
* a new item for slot.
*/
void tcStoresGui::AddOrUpdateItem(tcContainerSlot& slot, const std::string& itemName,
                      unsigned int quantity, bool isMoving, unsigned int itemId, tcStores* stores)
{
	wxASSERT(stores);

    tcStoresContainerItem* item = dynamic_cast<tcStoresContainerItem*>(slot.GetItem());
   
    if (item == 0)
    {
        item = new tcStoresContainerItem();    
		slot.SetItem(item);
    }
 
    tcDatabaseObject* databaseObject = 0;
    if (!isMoving)
    {
        databaseObject = stores->GetDatabaseObjectForItem(itemName);
    }
    else
    {
        databaseObject = tcDatabase::Get()->GetObject(itemName);
    }
    
    
    if (databaseObject)
    {
	    boost::shared_ptr<tcGeometry> icon = databaseObject->GetIcon();
        item->SetIcon(icon);
		item->SetId(itemId);
	    item->SetItemName(itemName);
	    item->SetQuantity(quantity);
		item->SetStores(platformId, hostId, storesIdx);        
        item->SetMoving(isMoving);
        item->SetOpId(itemId);
        item->SetGui(this); // be careful with this! see ~tcContainerItem APR2009 was wiping out parentItem reference
        if (isMoving) item->SetDrawState(tcContainerItem::BLINK);
        else item->SetDrawState(tcContainerItem::NORMAL);
    }
    else
    {
        boost::shared_ptr<tcGeometry> nullIcon((tcGeometry*)0);
        item->SetIcon(nullIcon);
        wxASSERT(false);
    }

}


void tcStoresGui::Draw() 
{
	tcStores* stores = GetStores();
	if (stores == 0) DestroyWindow();

    //if (drawCount++ % 4 != 0) return; // update draw every 4th frame

    StartDraw();

	UpdateGui();

	bool blinkOn = tcTime::Get()->Get30HzCount() % 30 < 15;
    
    // draw caption
    tcGameObject* parent = stores->GetParent();
	const Vec4 captionColor(1.0f, 1.0f, 1.0f, 1.0f);
	const char* unitName = parent->mzUnit.c_str();
	const std::string& storesDisplayName = stores->GetDisplayName();
	float guiWidth = float(mnWidth);

	wxString captionText = wxString::Format("%s\n%s", unitName, storesDisplayName.c_str());
	DrawTextR(captionText.c_str(), 10.0f, 2.0f, defaultFont.get(),
        captionColor, 16.0f, LEFT_TOP, guiWidth - 20.0f);

    // draw weight/volume/count capacity status
    wxString fillStatus = stores->GetFilledStatusString();
    DrawTextR(fillStatus.c_str(), 10.0f, float(mnHeight) - 10.0f, defaultFont.get(),
        captionColor, 10.0f, LEFT_CENTER, guiWidth - 10.0f);

    // calculate slots to draw based on page info
    size_t startIdx = currentPage * slotsPerPage;
    size_t stopIdx = startIdx + slotsPerPage;
    size_t nSlots = slots.size();
    if (stopIdx > nSlots) stopIdx = nSlots;
    if ((startIdx+1) > nSlots) startIdx = nSlots - 1; // won't draw anyway if nSlots==0


    // draw slots and items
	
	for (size_t n=startIdx; n<stopIdx; n++)
	{
		tcContainerSlot& slot = slots[n];
		tcStoresContainerItem* item = dynamic_cast<tcStoresContainerItem*>(slot.GetItem());
		
		bool isMouseOver = slot.IsMouseOver();

		if (item)
		{
            int drawState = item->GetDrawState();
            bool doDraw = (drawState == tcContainerItem::NORMAL) ||
                ((drawState == tcContainerItem::BLINK) && blinkOn);

            boost::shared_ptr<tcGeometry> icon = slot.GetIcon();
            DrawGeometryR(icon.get(), slot.loc.XCenter(), slot.loc.YCenter());

            Vec4 color;
            if (!isMouseOver) color.set(0.6f, 0.6f, 0.6f, 1.0f);
            else color.set(1.0f, 1.0f, 1.0f, 1.0f);

            if (doDraw)
            {
                // draw quantity label
                DrawTextR(item->GetQuantityLabel(), slot.loc.GetRight() + 5.0f, slot.loc.GetTop() - 0.0f, 
                    defaultFont.get(), color, 12.0f, LEFT_BASE_LINE);

                // draw item name
                float left = slot.loc.GetRight() + 36.0f;
                float maxWidth = guiWidth - left - 10.0f;

                DrawTextR(item->GetItemName().c_str(), left, slot.loc.GetTop() - 0.0f, defaultFont.get(),
                    color, 14.0f, LEFT_BASE_LINE, maxWidth);
            }

            // draw description caption if mouse is over slot
            //if (isMouseOver)
            //{
            //	const Vec4 color(1.0f, 1.0f, 1.0f, 1.0f);
            //	float left = slot.loc.GetLeft();
            //	float maxWidth = guiWidth - left - 10.0f;

            //	DrawTextR(item->GetItemName().c_str(), left, slot.loc.GetTop() + 15.0f, defaultFont.get(),
            //        color, 14.0f, LEFT_BASE_LINE, maxWidth);
            //}

            // draw expanded rectangle for slot border
            tcRect r = slot.loc;
            r.Expand(1.0, 1.0);
            if (isMouseOver)
            {
                DrawRectangleR(r, Vec4(1, 1, 1, 1), tc3DWindow2::FILL_OFF);
            }
            else
            {
                DrawRectangleR(r, Vec4(0.5, 0.5, 0.5, 1), tc3DWindow2::FILL_OFF);
            }

        }

	}

    // draw page boxes
    for (size_t n=0; n<pageBoxes.size(); n++)
    {   
        int fillMode = (n == currentPage) ? tc3DWindow2::FILL_ON : tc3DWindow2::FILL_OFF;
        Vec4 color(0.5, 0.5, 0.5, 0.5);
        if (n == mouseOverPage) color.set(1, 1, 1, 1);

        DrawRectangleR(pageBoxes[n], color, fillMode);
    }

	FinishDraw();
}

long tcStoresGui::GetPlatformId() const
{
    return platformId;
}

long tcStoresGui::GetHostId() const
{
    return hostId;
}

/**
* @return pointer to platform that holds this stores obj
*/
tcPlatformObject* tcStoresGui::GetPlatform() const
{
	tcPlatformObject* platform = 0;

	if (hostId == -1)
	{
		platform = dynamic_cast<tcPlatformObject*>
			(tcSimState::Get()->GetObject(platformId));
	}
	else
	{
		tcGameObject* parent = tcSimState::Get()->GetObject(hostId);
		if (parent == 0) return 0;
	    platform = dynamic_cast<tcPlatformObject*>(parent->GetChildById(platformId));
	}

	return platform;
}


/**
* @return pointer to stores object
* This is done dynamically to handle case where object is deleted
*/
tcStores* tcStoresGui::GetStores()
{
	tcPlatformObject* platform = 0;

	if (hostId == -1)
	{
		platform = dynamic_cast<tcPlatformObject*>
			(tcSimState::Get()->GetObject(platformId));
	}
	else
	{
		tcGameObject* parent = tcSimState::Get()->GetObject(hostId);
		if (parent == 0) return 0;
	    platform = dynamic_cast<tcPlatformObject*>(parent->GetChildById(platformId));
	}

	if (platform == 0) return 0;

	return platform->GetMagazine(storesIdx);
}

/**
* Handles two cases:
* - Transfer of item from one tcStores to this tcStores
* - Unload of launcher to this tcStores
*/
void tcStoresGui::HandleDrop(size_t slotIdx, const std::vector<tcContainerItem*>& items)
{
    tcContainerItem* item = (items.size() > 0) ? items[0] : 0;

	tcStores* stores = GetStores();
	if (stores == 0) return;

	tcStoresContainerItem* storesItem = dynamic_cast<tcStoresContainerItem*>(item);
	if (storesItem)
	{
        bool ownDrop = (storesItem->GetGui() == this);
        float currentDragDistance = tcDragStatus::Get()->CurrentDragDistance();

        if (tcGameObject::IsEditMode())
        {
            if (ownDrop && (currentDragDistance > 50.0f))
            {
                stores->RemoveItems(storesItem->GetItemName(), storesItem->GetQuantity());
            }

            // Transfer of item from one tcStores to this tcStores
            if (!ownDrop)
            {
                tcStoresGui* sourceGui = dynamic_cast<tcStoresGui*>(storesItem->GetGui());
                if ((sourceGui != 0) && (sourceGui->GetStores() != 0))
                {
                    tcStores* sourceStores = sourceGui->GetStores();

                    std::string itemName(item->GetItemName());
                    if (stores->IsCompatible(itemName))
                    {
                        tcDatabaseObject* itemData = tcDatabase::Get()->GetObject(itemName);

                        if (itemData == 0)
                        {
                            fprintf(stderr, "tcStoresGui::HandleDrop -- item not found in database (%s)\n", itemName.c_str());
                            wxASSERT(false);
                            return; // not found in database
                        }

                        unsigned long freeCapacity = stores->GetFreeCapacityForItem(itemData->weight_kg, itemData->volume_m3);        
                        unsigned int moveQuantity = (unsigned int)std::min((unsigned long)storesItem->GetQuantity(), freeCapacity);

                        sourceStores->RemoveItems(itemName, moveQuantity);
                        stores->AddItems(itemName, moveQuantity);
                    }
                }
            }
        }
        else
        {               
            if (storesItem->IsMoving())
            {
                // cancel move
                tcStoresGui* sourceGui = dynamic_cast<tcStoresGui*>(storesItem->GetGui());

                if (sourceGui != 0)
                {
                    tcStores* sourceStores = sourceGui->GetStores();
                    if (sourceStores != 0)
                    {
                        sourceStores->CancelOperation(storesItem->GetOpId());
                    }
                }
                return;
            }

            bool ownDrop = (storesItem->GetGui() == this);

            if (ownDrop)
            {
                return;
            }
            
            tcPlatformObject* destination = GetPlatform();
            tcStoresGui* sourceGui = dynamic_cast<tcStoresGui*>(storesItem->GetGui());
            
            if (sourceGui != 0)
            {
                tcStores* sourceStores = sourceGui->GetStores();
                if (sourceStores != 0)
                {
                    unsigned int quantity = sourceStores->MoveStores(storesItem->GetItemName(), storesItem->GetQuantity(), destination, storesIdx);
                }
            }

        }

		return;
	}

	tcLauncherContainerItem* launcherItem = dynamic_cast<tcLauncherContainerItem*>(item);
	if (launcherItem == 0) return;

	tcLauncher* launcher = launcherItem->GetLauncher();
	wxASSERT(launcher);

	unsigned int launcherIdx = launcherItem->GetLauncherIndex();

    tcPlatformGui* platformGui = dynamic_cast<tcPlatformGui*>(launcherItem->GetGui());
    if (platformGui != 0)
    {
        std::vector<tcPlatformObject*> platformList;
        platformGui->GetPlatformList(platformList);
        for (size_t n=0; n<platformList.size(); n++)
        {
            stores->UnloadLauncher(launcherIdx, platformList[n]);
        }
    }
    else
    { // old way assuming no group selection
	    stores->UnloadLauncher(launcherIdx, launcher->GetParent());
    }

	tcSound::Get()->PlayEffect("Thuck");
}

/**
* 
*/
void tcStoresGui::HandleDropWindow(const std::vector<tcContainerItem*>& items)
{
    tcContainerItem* item = (items.size() > 0) ? items[0] : 0;

    if (item == 0) return;

    tcStoresGui::HandleDrop(999, items); // since slot doesn't matter anyway
}

void tcStoresGui::IncrementPage(int dir)
{
    size_t nPages = pageBoxes.size();
    if (nPages == 0) return;
    
    if ((dir > 0) && (currentPage < (nPages-1)))
    {
        SetCurrentPage(currentPage+1);
    }
    else if ((dir < 0) && (currentPage > 0))
    {
        SetCurrentPage(currentPage-1);
    }
}

void tcStoresGui::InitializeGui()
{
	tcStores* stores = GetStores();
    wxASSERT(stores);
    if (stores == 0) return;

//	tcStoresDBObject* storesData = stores->GetDatabaseObject();
//    wxASSERT(storesData);

    for (size_t n=0; n<maxSlots; n++)
    {    
        tcRect slotLoc(upperLeft.x, upperLeft.x + slotSize,
                   upperLeft.y, upperLeft.y + slotSize + float(n%slotsPerPage)*verticalSpacing);

        AddSlot(slotLoc, tcContainerGui::SMALL_ICON_SIZE);
    }

    SetCurrentPage(0);
}

/**
* Stole most of this from tcNumberWidget
*/
void tcStoresGui::OnChar(wxKeyEvent& event)
{
    const unsigned int keyboardTimeout = 30;

    int nChar = event.GetKeyCode();

    tcDragStatus* dragStatus = tcDragStatus::Get();
    if (!dragStatus->IsDragging())
    {  
        switch (nChar)
        {
        case WXK_PAGEDOWN:
            IncrementPage(1);
            break;
        case WXK_PAGEUP:
            IncrementPage(-1);
            break;
        }
        return;
    }

    tcStoresContainerItem* storesItem = dynamic_cast<tcStoresContainerItem*>(dragStatus->GetDraggedFirstItem());
    if (storesItem == 0) return;

    unsigned int t = tcTime::Get()->Get30HzCount();
    unsigned int dt = t - lastKeypressTime;

    bool addDigit = (keyboardWait && (dt < keyboardTimeout));
    keyboardWait = true;
    lastKeypressTime = t;


    unsigned int val = dragStatus->GetQuantity();

    const int val0 = '0';
    const int val9 = '9';
    

    if ((nChar >= val0) && (nChar <= val9))
    {
        if (addDigit)
        {
            val = 10 * val + (nChar - val0);
        }
        else
        {
            val = (nChar - val0);
        }
        tcSound::Get()->PlayEffect("MutedBeep");
    }   
    else if ((nChar == WXK_BACK) && addDigit)
    {
        val = val / 10;
    }
    else
    {
        event.Skip();
    }

    val = std::min(storesItem->GetQuantity(), val);
    dragStatus->SetQuantity(val);
}

/**
* Change page if click in page box
*/
void tcStoresGui::OnLButtonDown(wxMouseEvent& event)
{
    wxPoint pos = event.GetPosition();

    size_t nPages = pageBoxes.size();
    for (size_t n=0; n<nPages; n++)
    {
        if (pageBoxes[n].ContainsPoint(float(pos.x), float(pos.y)))
        {
            if (n != currentPage) SetCurrentPage(n);
            return;
        }
    }

    tcContainerGui::OnLButtonDown(event);
}

void tcStoresGui::OnLButtonDClick(wxMouseEvent& event)
{
    OnRButtonDown(event);
}

/**
* Update mouseOverPage
*/
void tcStoresGui::OnMouseMove(wxMouseEvent& event)
{
    wxPoint pos = event.GetPosition();

    mouseOverPage = 9999;

    size_t nPages = pageBoxes.size();
    for (size_t n=0; n<nPages; n++)
    {
        if (pageBoxes[n].ContainsPoint(float(pos.x), float(pos.y)))
        {
            mouseOverPage = n;
            return;
        }
    }

    tcContainerGui::OnMouseMove(event);
}

/**
* If right button is clicked on launch spot, launch the entity item in spot
*/
void tcStoresGui::OnRButtonDown(wxMouseEvent& event)
{
    wxPoint point = event.GetPosition();

    float x = (float)point.x;
    float y = (float)point.y;

    for (size_t n=0; n<slots.size(); n++)
    {
        tcContainerSlot& slot = slots[n];

        if (slot.loc.ContainsPoint(x, y))
        {
            if (tcStoresContainerItem* item = dynamic_cast<tcStoresContainerItem*>(slot.GetItem()))
            {
                if (item->IsMoving())
                {
                    tcStores* stores = GetStores();
                    stores->CancelOperation(item->GetId());
                }
            }
            return;
        }
    }
}

void tcStoresGui::ReadGuiParameters()
{
    TiXmlNode* root = config->FirstChild("Window");
    if (!root)
    {
        fprintf(stderr, "tcStoresGui::ReadGuiParameters - Missing top level <Window> tag\n");
        return;
    }

	TiXmlNode* current = root->FirstChild("Stores");
    if (!current)
    {
        fprintf(stderr, "tcStoresGui::ReadGuiParameters - Missing <Stores> tag\n");
        return;
    }
	
    TiXmlElement* elt = current->ToElement();    
    
    double slotSizeXml = 16.0;
    double upperLeftX = 0;
    double upperLeftY = 0;
    double horizontalSpacingXml = 50.0;
	double verticalSpacingXml = 50.0;
    int rowSizeXml = 8;
    
    elt->Attribute("SlotSize", &slotSizeXml);
    elt->Attribute("UpperLeftX", &upperLeftX);
    elt->Attribute("UpperLeftY", &upperLeftY);
    elt->Attribute("HorizontalSpacing", &horizontalSpacingXml);
    elt->Attribute("VerticalSpacing", &verticalSpacingXml);
    elt->Attribute("RowSize", &rowSizeXml);
    
    slotSize = slotSizeXml;
    upperLeft.x = upperLeftX;
    upperLeft.y = upperLeftY;
    horizontalSpacing = horizontalSpacingXml;
	verticalSpacing = verticalSpacingXml;
    rowSize = rowSizeXml;
    
}

void tcStoresGui::SetCurrentPage(size_t page)
{
    if (page >= nPages) return;

    currentPage = page;

	size_t startIdx = slotsPerPage * currentPage;
    size_t stopIdx = startIdx + slotsPerPage;

    for (size_t n=0; n<maxSlots; n++)
    {   
        if ((n >= startIdx) && (n < stopIdx))
        {
            float yOffset = float(n%slotsPerPage)*verticalSpacing;

            slots[n].loc.Set(upperLeft.x, upperLeft.x + slotSize,
                upperLeft.y + yOffset, upperLeft.y + slotSize + yOffset);
        }
        else
        {
            slots[n].loc.Set(0, 0, -10.0, -10.0);
        }

    }

}

/**
* Update slot items based on tcStores state
*/
void tcStoresGui::UpdateGui()
{
	tcStores* stores = GetStores();
	if (stores == 0) return;

    // mark all slots not updated
    for (size_t n=0; n<slots.size(); n++)
    {
        slots[n].SetUpdated(false);
    }
    
    std::string s;
	size_t nTypes = stores->GetNumberItemTypes();
	for (size_t n=0; (n<nTypes)&&(n<slots.size()); n++)
	{
		tcContainerSlot& slot = slots[n];

        const tcStores::StoreItemInfo& itemInfo = stores->GetItemInfo(n);
        const std::string& itemName = itemInfo.className;
        unsigned int itemQuantity = itemInfo.quantity;
        unsigned int itemId = itemInfo.id;

		AddOrUpdateItem(slot, itemName, itemQuantity, false, itemId, stores);
		slot.SetUpdated(true);
	}

    // add items that are on-the-move
    const std::vector<tcStores::StoreItemInfo>& moveSummary = stores->GetMoveSummary();
    size_t nMoves = moveSummary.size();
	for (size_t n=0; (n<nMoves)&&((n+nTypes)<slots.size()); n++)
	{
		tcContainerSlot& slot = slots[n+nTypes];

        const std::string& itemName = moveSummary[n].className;
        unsigned long itemQuantity = moveSummary[n].quantity;

		AddOrUpdateItem(slot, itemName, itemQuantity, true, moveSummary[n].id, stores);
		slot.SetUpdated(true);
	}


	// delete items that were not updated
	for (size_t n=0; n<slots.size(); n++)
	{
		if (!slots[n].IsUpdated())
		{
			slots[n].ClearItem();
		}
	}

    nPages = ((slotsPerPage - 1 + stores->GetNumberItemTypes()) / slotsPerPage);
    size_t maxPages = (maxSlots - 1 + slotsPerPage) / slotsPerPage;
    if (nPages > maxPages) nPages = maxPages;

    // update page boxes
    pageBoxes.clear();
    if (nPages > 1) // don't bother showing icon for single page
    {
        float xPageBox = float(mnWidth) - 10.0f;
        float yPageBox = 30.0f;
        float wPageBox = 7.0f;


        for (size_t n=0; n<nPages; n++)
        {
//            float yOffset = float(n)*wPageBox;
            pageBoxes.push_back(tcRect(xPageBox, xPageBox + wPageBox, yPageBox, yPageBox + wPageBox));
            yPageBox += wPageBox + 2.0f;
        }
    }
}

/**
*
*/
tcStoresGui::tcStoresGui(long id, long host, unsigned int idx, const wxPoint& pos, 
     const wxString& configFile) 
     : tcContainerGui(pos, configFile, "StoresGui"), 
	   platformId(id), 
	   hostId(host),
	   storesIdx(idx),
       slotsPerPage(8),
       nPages(1),
       currentPage(0),
       maxSlots(100),
       mouseOverPage(9999),
       lastKeypressTime(0),
       keyboardWait(false)
{
    ReadGuiParameters();
   
    InitializeGui();

	SetActive(true);

#ifdef _DEBUG
	fprintf(stdout, "tcStoresGui::tcStoresGui - %s, %d slots\n", configFile.c_str(),
		slots.size());
#endif



}

tcStoresGui::~tcStoresGui() 
{

}


