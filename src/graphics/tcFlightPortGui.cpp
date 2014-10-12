/** 
**  @file tcFlightPortGui.cpp 
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

#include "tcFlightPortGui.h"
#include "tcFlightPort.h"
#include "tcFlightportDBObject.h"
#include "tcAirDBObject.h"
#include "common/tinyxml.h"
#include "tcTime.h"
#include "tcDragStatus.h"
#include "tcGameObject.h"
#include "tcPlatformGui.h"
#include "tcPlatformObject.h"
#include "tcSimState.h"
#include "tcStores.h"
#include "tcStoresGui.h"
#include "tcMissionGui.h"
#include "tcGeometry.h"
#include "ai/tcMissionManager.h"
#include "tcEntityContainerItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma warning (disable : 4311) // pointer truncation


tcFlightPortGui* tcFlightPortGui::GetExistingGui(long id)
{
    std::list<tcContainerGui*>::iterator iter = 
        openContainers.begin();

    for (iter=openContainers.begin(); iter!=openContainers.end(); ++iter)
    {
        if (tcFlightPortGui* flightPortGui = dynamic_cast<tcFlightPortGui*>(*iter))
        {
            if (flightPortGui->GetPlatformId() == id)
            {
                return flightPortGui;
            }
        }

    }
    return 0;
}



/**
* If slot has tcEntityContainerItem then update it, otherwise create
* a new item for slot.
*/
void tcFlightPortGui::AddOrUpdateItem(tcContainerSlot& slot, tcAirState* airState)
{
    tcEntityContainerItem* item = dynamic_cast<tcEntityContainerItem*>(slot.GetItem());
   
    if (item == 0)
    {
        item = new tcEntityContainerItem();    
		slot.SetItem(item);
    }
 
    boost::shared_ptr<tcGeometry> icon = airState->obj->mpDBObject->GetIcon();

    wxString s = wxString::Format("%s (%s)", airState->obj->mzClass.c_str(), airState->obj->mzUnit.c_str());

    tcFlightPort* flightPort = GetFlightPort();

    wxString readyTimeString = flightPort->GetTimeToDestinationString(airState);
     
    s += readyTimeString;
	    
    
    item->SetDescription(s.c_str());

	item->SetEntity(airState->obj->mnID, platformId);
	item->SetIcon(icon);
	item->SetId(reinterpret_cast<unsigned int>(airState));
    item->SetQuantity(0);
    
	if (airState->inTransit)
	{
        if (airState->current_location != PRETAKEOFF)
        {
		    item->SetDrawState(tcContainerItem::BLINK);
        }
        else
        {
            item->SetDrawState(tcContainerItem::BLINK2);
        }
	}
	else
	{
		item->SetDrawState(tcContainerItem::NORMAL);
	}
}

void tcFlightPortGui::CloseAllPlatformGuis()
{
//	size_t nSlots = slots.size();
	for (size_t n=readyOffset; n<missionIdx; n++)
	{
		tcContainerSlot& slot = slots[n];
		if (tcContainerItem* item = slot.GetItem())
		{
			if (item->GetGui() != 0)
			{				
				item->GetGui()->DestroyWindow();
				item->SetGui(0);
			}
		}
	}
}

/**
* Scenario edit mode only
* Delete unit from slot that mouse is currently over
*/
void tcFlightPortGui::DeleteFromMouseOverSlot()
{
    if (!tcGameObject::IsEditMode()) return;

	size_t nSlots = slots.size();
	for (size_t n=0; n<nSlots; n++)
	{
		tcContainerSlot& slot = slots[n];
        tcContainerItem* item = slot.GetItem();
		tcEntityContainerItem* entityItem = dynamic_cast<tcEntityContainerItem*>(item);
		
		bool isMouseOver = slot.IsMouseOver();
        if (isMouseOver && (entityItem != 0))
        {
            tcFlightPort* flightPort = GetFlightPort();
            if ((flightPort == 0) || (flightPort->parent == 0))
            {
                wxASSERT(false); // invalid flightport
                return;
            }

            if (tcGameObject* obj = entityItem->GetEntity())
            {
                obj->SelfDestruct();
            }

            //flightPort->

        }
    }
}

void tcFlightPortGui::Draw() 
{
	tcFlightPort* flightPort = GetFlightPort();
	if ((flightPort == 0) || (flightPort->parent == 0))
    {
        DestroyWindow();
        return;
    }

    //if (drawCount++ % 4 != 0) return; // update draw every 4th frame

    StartDraw();

	UpdateGui();

    unsigned int timeCount = tcTime::Get()->Get30HzCount();
	bool blinkOn = (timeCount & 0x001F) < 16;
    bool blink2On = ((timeCount & 0x000F) < 5) || ((timeCount & 0x000F) > 10);

    // draw caption
	const Vec4 captionColor(1.0f, 1.0f, 1.0f, 1.0f);
	const char* unitName = flightPort->parent->mzUnit.c_str();
	wxString captionText = wxString::Format("%s Air Operations", unitName);
	DrawTextR(captionText.c_str(), 10.0f, 20.0f, defaultFont.get(),
        captionColor, 18.0f, LEFT_BASE_LINE);

	// create draw order vector with mouse over slot last
	std::vector<size_t> drawList;
	size_t nSlots = slots.size();
	for (size_t n=0; n<nSlots; n++)
	{
		tcContainerSlot& slot = slots[n];
		bool isMouseOver = slot.IsMouseOver();
		if (!isMouseOver)
		{
			drawList.push_back(n);
		}
	}
	for (size_t n=0; n<nSlots; n++)
	{
		tcContainerSlot& slot = slots[n];
		bool isMouseOver = slot.IsMouseOver();
		if (isMouseOver)
		{
			drawList.push_back(n);
		}
	}
	
    // draw slots and items
	nSlots = drawList.size();
	for (size_t idx=0; idx<nSlots; idx++)
	{
		size_t n = drawList[idx];

		tcContainerSlot& slot = slots[n];
        tcContainerItem* item = slot.GetItem();
		tcEntityContainerItem* entityItem = dynamic_cast<tcEntityContainerItem*>(item);
		
		bool isMouseOver = slot.IsMouseOver();
		bool unitQueuedForTakeoff = false;

        Vec4 itemColor(1, 1, 1, 1);
        std::string caption;

		if (entityItem != 0)
		{
            int drawState = item->GetDrawState();

            // this is getting a little nuts, BLINK is slow on/off blink, BLINK2 is double on, then off
            bool drawBlink = (blinkOn && (drawState == tcContainerItem::BLINK)) ||
                (blinkOn && blink2On && (drawState == tcContainerItem::BLINK2));

			/* Determine entityItem color (color mixed with image color)
			**    Damaged - red
			**    Not fully equipped and refueled - yellow
			**    Repositioning - blink blue
			**    Reserved for mission - darken 50%
			*/
			tcAirObject* air = dynamic_cast<tcAirObject*>(entityItem->GetEntity());
			if (air != 0)
			{
				if (air->GetDamageLevel() > 0)
				{
					itemColor.set(1, 0, 0, 1);
				}
                else if (air->MaintenanceHold())
                {
                    itemColor.set(0.8, 0.8, 0.8, 1);
                }
				else if (!air->IsReadyForLaunch())
				{
					itemColor.set(1, 1, 0.5, 1);
				}
				else if (drawBlink) // ((drawState == tcContainerItem::BLINK) && !blinkOn)
				{
					itemColor.set(0.5, 0.5, 1, 1);
				}

				if (flightPort->GetOrCreateMissionManager()->IsAircraftReserved(air->mnID))
				{
					itemColor = itemColor * 0.7f;
				}

				unitQueuedForTakeoff = flightPort->IsQueuedForTakeoff(air->mnID);
			}			

			// draw description caption if mouse is over slot
			if (!isMouseOver)
            {
                caption = air->GetLoadoutTag();
                if (caption.size() == 0)
                {
                    air->UpdateLoadoutTag();
					caption = air->GetLoadoutTag();
                }

				if (n < hangarOffset)
				{					
					wxString s2(caption.c_str());
                    s2 = s2.Left(4);
                    caption = s2.c_str();
				}
                // only display first 3 chars for small hangar icons
                else if ((n >= hangarOffset) && (n < magazineIdx))
                {
                    wxString s2(caption.c_str());
                    s2 = s2.Left(3);
                    caption = s2.c_str();
                }
            }
            else
			{
                caption = entityItem->GetDescription();
			}
        }

        if (item != 0)
        {
//			int drawState = item->GetDrawState();
			
            boost::shared_ptr<tcGeometry> icon = slot.GetIcon();	

//			osg::Vec4Array* colorArray = dynamic_cast<osg::Vec4Array*>(icon->getColorArray()); // assumes color array already created
//			colorArray->back() = itemColor;

            icon->SetColor(itemColor);


            if (!isMouseOver)
            {
				DrawGeometryR(icon.get(), slot.loc.XCenter(), slot.loc.YCenter());
                if (caption.size() > 0)
                {
                    const Vec4 color(1.0f, 1.0f, 1.0f, 1.0f);
                    DrawTextR(caption.c_str(), slot.loc.XCenter(), slot.loc.GetTop() + 8.0f, defaultFont.get(),
                        color, 10.0f, CENTER_CENTER);
                }
            }
            else
            {
				DrawGeometryZoomR(icon.get(), slot.loc.XCenter(), slot.loc.YCenter(), 1.5f);
                if (caption.size() == 0)
                {
                    caption = item->GetItemName().c_str();
                }

				const Vec4 color(1.0f, 1.0f, 1.0f, 1.0f);
				DrawTextR(caption.c_str(), slot.loc.GetLeft(), slot.loc.GetTop() + 18.0f + 5.0f, defaultFont.get(),
			        color, 12.0f, LEFT_BASE_LINE);
            }


        }


        // draw expanded rectangle for slot border
		tcRect r = slot.loc;
		r.Expand(1.0, 1.0);
		Vec4 borderColor;

		if (isMouseOver || (item && item->ItemGuiIsActive()))
		{
			borderColor.set(1, 1, 1, 1);
		}
		else if (unitQueuedForTakeoff)
		{
			borderColor.set(0.8f, 1.0f, 0.8f, 1.0f);
		}
		else
		{
			borderColor.set(0.5f, 0.5f, 0.5f, 1.0f);
		}

		if (!isMouseOver || (item == 0))
		{
			DrawRectangleR(r, borderColor, tc3DWindow2::FILL_OFF);

			if ((entityItem != 0) && (slot.IsSelected()))
			{
				DrawThickRectangleR(r, 2.0f, Vec4(1.0f, 1.0f, 0.6f, 0.95f));
			}
		}

		// draw short lines if this is a launch spot
		if (n < readyOffset)
		{
			float ycenter = r.YCenter();
			float xleft = r.GetLeft();
			float xright = r.GetRight();
			const float dx = 5.0f;
			DrawLineR(xleft-dx, ycenter, xleft, ycenter, borderColor);
			DrawLineR(xright, ycenter, xright+dx, ycenter, borderColor);
		}
        
	}

    DrawSelectionBox();

	FinishDraw();
}

tcFlightPort* tcFlightPortGui::GetFlightPort()
{
	tcFlightOpsObject* flightOps = 
             dynamic_cast<tcFlightOpsObject*>(tcSimState::Get()->GetObject(platformId));
	if (flightOps == 0) return 0;

	return flightOps->GetFlightPort();
}

long tcFlightPortGui::GetPlatformId() const
{
    return platformId;
}


void tcFlightPortGui::HandleDrop(size_t slotIdx, const std::vector<tcContainerItem*>& items)
{	
    tcFlightPort* flightPort = GetFlightPort();
	if (flightPort == 0) return;


    std::vector<tcGameObject*> entities;
    for (size_t n=0; n<items.size(); n++)
    {
        tcContainerItem* item = items[n];
        tcEntityContainerItem* entityItem = dynamic_cast<tcEntityContainerItem*>(item);
        tcGameObject* entity = (entityItem != 0) ? entityItem->GetEntity() : 0;
        if (entity != 0)
        {
            entities.push_back(entity);
        }
    }

    for (size_t n=0; n<entities.size(); n++)
    {
        tcGameObject* entity = entities[n];
        int unitIdx = flightPort->FindAirState(entity);
        if (unitIdx >= 0)
        {
            if (slotIdx < readyOffset)
            {
                flightPort->SetObjectDestination((unsigned)unitIdx, ALERT5, slotIdx - launchOffset);
            }
            else if (slotIdx < hangarOffset)
            {
                flightPort->SetObjectDestination((unsigned)unitIdx, ALERT15, slotIdx - readyOffset);
            }
            else
            {
                flightPort->SetObjectDestination((unsigned)unitIdx, HANGAR, slotIdx - hangarOffset);
            }
        }
    }


	tcSound::Get()->PlayEffect("Thuck");
}

void tcFlightPortGui::InitializeGui()
{
	tcFlightPort* flightPort = GetFlightPort();
    wxASSERT(flightPort);
	if (flightPort == 0) return;

    tcFlightportDBObject* databaseObj = flightPort->GetDatabaseObject();
    wxASSERT(databaseObj);
    if (databaseObj == 0) return;
    
    size_t nSpots = databaseObj->spotInfo.size();
    
    // add launch slots
    launchOffset = 0;
    tcRect slotLoc(launchLoc.x, launchLoc.x + slotSize,
                   launchLoc.y, launchLoc.y + slotSize);
    for (size_t n=0; n<nSpots; n++)
    {
        tcFlightportDBObject::spotDBInfo& spotInfo = databaseObj->spotInfo[n];
        if (spotInfo.isLaunch)
        {
		    AddSlot(slotLoc);
		    slotLoc.Offset(launchHorizontalSpacing, 0);
        }
    }
    
    // add ready slots
    readyOffset = GetNumSlots();
    slotLoc.Set(readyLoc.x, readyLoc.x + slotSize,
                   readyLoc.y, readyLoc.y + slotSize);
    for (size_t n=0; n<nSpots; n++)
    {
        tcFlightportDBObject::spotDBInfo& spotInfo = databaseObj->spotInfo[n];
        if (!spotInfo.isLaunch)
        {
		    AddSlot(slotLoc);
		    slotLoc.Offset(readyHorizontalSpacing, 0);
        }
    }
    
    // add hangar slots
    hangarOffset = GetNumSlots();
    slotLoc.Set(hangarLoc.x, hangarLoc.x + hangarSlotSize,
               hangarLoc.y, hangarLoc.y + hangarSlotSize);
    size_t nRow = 0;
    tcContainerGui::IconSize hangarIconSize = useSmallHangarSlots ? tcContainerGui::SMALL_ICON_SIZE : tcContainerGui::NORMAL_ICON_SIZE;
    for (size_t n=0; n<databaseObj->hangarCapacity; n++)
    {
        AddSlot(slotLoc, hangarIconSize);
	    slotLoc.Offset(hangarHorizontalSpacing, 0);
	    nRow++;
	    if (nRow >= hangarRowSize)
	    {
			slotLoc.Offset(hangarLoc.x - slotLoc.GetLeft(), hangarVerticalSpacing);
            nRow = 0;
        }
    }

    // add mission plan slot
    missionIdx = GetNumSlots();
    slotLoc.Set(magazineLoc.x, magazineLoc.x + slotSize,
                magazineLoc.y, magazineLoc.y + slotSize);
    AddSlot(slotLoc);

    // add magazine slots
    magazineIdx = GetNumSlots();
    tcPlatformObject* platform = dynamic_cast<tcPlatformObject*>(tcSimState::Get()->GetObject(platformId));
    if (platform == 0)
    {
        wxASSERT(false);
        return;
    }

    slotLoc.Offset(magazineOffset.x + 0.0f, magazineOffset.y);

    nMagazines = platform->GetMagazineCount();
    for (size_t n=0; n<nMagazines; n++)
    {
        AddSlot(slotLoc);
        
        slotLoc.Offset(magazineOffset.x, magazineOffset.y);
    }

	// load icons
    magazineIcon = tc3DWindow2::CreateTexturedSymbol("icons\\magazine.jpg", slotSize);
    missionIcon = tc3DWindow2::CreateTexturedSymbol("icons\\mission.jpg", slotSize);
}


void tcFlightPortGui::OnChar(wxKeyEvent& event)
{
    long keycode = event.GetKeyCode();

    switch (keycode)
    {
    case WXK_DELETE:
        {
            DeleteFromMouseOverSlot();
        }
        break;
    default:
        event.Skip();
    }

}

/**
* Launch clicked entity if in launch spot
*/
void tcFlightPortGui::OnLButtonDClick(wxMouseEvent& event)
{
	tcContainerGui::OnLButtonDClick(event);

	tcFlightPort* flightPort = GetFlightPort();
	if (flightPort == 0) return;

    wxPoint point = event.GetPosition();

    float x = (float)point.x;
    float y = (float)point.y;

	//size_t nSlots = slots.size();

	for (size_t n=launchOffset; n<readyOffset; n++)
	{
		if (slots[n].loc.ContainsPoint(x, y))
		{
			flightPort->LaunchRunway(n - launchOffset);
			return;
		}
	}

	// search all slots and schedule launch (will be queued if necessary)
	for (size_t n=0; n<missionIdx; n++)
	{
		if (slots[n].loc.ContainsPoint(x, y))
		{
			tcEntityContainerItem* entityItem = dynamic_cast<tcEntityContainerItem*>(slots[n].GetItem());
			if (entityItem != 0)
			{
				flightPort->LaunchID(entityItem->GetPlatformId());
			}
			return;
		}
	}

    // check if cursor is over mission plan slot
    {
        tcContainerSlot& slot = slots[missionIdx];
        
		if (slot.loc.ContainsPoint(x, y))
		{
			tcContainerItem* item = slot.GetItem();
			wxASSERT(item);
            if (item == 0) return;

			tcContainerGui* gui = item->GetGui();

			// toggle gui
			if (gui == 0)
			{
				OpenMissionGui(item);
			}
			else
			{
				gui->DestroyWindow();
				item->SetGui(0);
			}
			return;
		}
    }

    // check if cursor is over a magazine slot
    for (size_t n=magazineIdx; n<magazineIdx+nMagazines; n++)
    {
        tcContainerSlot& slot = slots[n];
        
		if (slot.loc.ContainsPoint(x, y))
		{
			tcContainerItem* item = slot.GetItem();
			wxASSERT(item);
            if (item == 0) return;

			tcContainerGui* gui = item->GetGui();

			// toggle gui
			if (gui == 0)
			{
				OpenMagazineGui(n - magazineIdx, item);
			}
			else
			{
				gui->DestroyWindow();
				item->SetGui(0);
			}
			return;
		}
    }

}

/**
* Open a platform gui for the clicked entity
*/
void tcFlightPortGui::OnRButtonDown(wxMouseEvent& event)
{
	tcFlightPort* flightPort = GetFlightPort();
	if (flightPort == 0) return;

    wxPoint point = event.GetPosition();

    float x = (float)point.x;
    float y = (float)point.y;

//	size_t nSlots = slots.size();

	for (size_t n=launchOffset; n<missionIdx; n++)
	{
		tcContainerSlot& slot = slots[n];
		if (!slot.IsEmpty() && slot.loc.ContainsPoint(x, y))
		{
			tcContainerItem* item = slot.GetItem();
			if (item->GetGui() == 0)
			{
				CloseAllPlatformGuis();
				OpenPlatformGui(slot.GetItem());
			}
			else
			{
				item->GetGui()->DestroyWindow();
				item->SetGui(0);
			}
			return;
		}
	}

    // check if cursor is over mission plan slot
    {
        tcContainerSlot& slot = slots[missionIdx];
        
		if (slot.loc.ContainsPoint(x, y))
		{
			tcContainerItem* item = slot.GetItem();
			wxASSERT(item);
            if (item == 0) return;

			tcContainerGui* gui = item->GetGui();

			// toggle gui
			if (gui == 0)
			{
				OpenMissionGui(item);
			}
			else
			{
				gui->DestroyWindow();
				item->SetGui(0);
			}
			return;
		}
    }

    // check if cursor is over a magazine slot
    for (size_t n=magazineIdx; n<magazineIdx+nMagazines; n++)
    {
        tcContainerSlot& slot = slots[n];
        
		if (slot.loc.ContainsPoint(x, y))
		{
			tcContainerItem* item = slot.GetItem();
			wxASSERT(item);
            if (item == 0) return;

			tcContainerGui* gui = item->GetGui();

			// toggle gui
			if (gui == 0)
			{
				OpenMagazineGui(n - magazineIdx, item);
			}
			else
			{
				gui->DestroyWindow();
				item->SetGui(0);
			}
			return;
		}
    }



}

/**
* Open magazine gui
* Copied from tcPlatformGui, needs refactoring
*/
void tcFlightPortGui::OpenMagazineGui(unsigned int idx, tcContainerItem* item)
{
    tcPlatformObject* platform = dynamic_cast<tcPlatformObject*>(tcSimState::Get()->GetObject(platformId));
	if (platform == 0) return;

	tcStores* magazine = platform->GetMagazine(idx);
	if (magazine)
	{
		wxPoint pos = wxWindow::GetPosition();
		wxSize size = wxWindow::GetSize();
		tcStoresGui* gui = new tcStoresGui(platformId, -1, idx, wxPoint(pos.x + size.GetWidth() + 10, pos.y), 
			                       "xml/stores_gui_table.xml");
		wxASSERT(item);
		item->SetGui(gui);
		gui->SetParentItem(item);
	}
}

/**
* Open mission gui
*/
void tcFlightPortGui::OpenMissionGui(tcContainerItem* item)
{
	tcFlightPort* flightPort = GetFlightPort();
	if ((flightPort == 0) || (flightPort->parent == 0))
    {
        return;
    }

    wxWindow::Freeze();

    wxPoint pos = wxWindow::GetPosition();
    wxSize size = wxWindow::GetSize();
    tcMissionGui* gui = new tcMissionGui(platformId, 0, wxPoint(pos.x + size.GetWidth() + 10, pos.y), 
        "xml/mission_gui_default.xml");
    wxASSERT(item);
    item->SetGui(gui);
    gui->SetParentItem(item);

    wxWindow::Thaw();
}

void tcFlightPortGui::OpenPlatformGui(tcContainerItem* item)
{
	tcEntityContainerItem* entityItem = dynamic_cast<tcEntityContainerItem*>(item);
	wxASSERT(entityItem);

	tcPlatformObject* platform = dynamic_cast<tcPlatformObject*>(entityItem->GetEntity());
	if (platform == 0) return;

	wxPoint pos = wxWindow::GetPosition();
	wxSize size = wxWindow::GetSize();

	wxString xmlFile;
	if (tcAirObject* air = dynamic_cast<tcAirObject*>(platform))
	{
		xmlFile = "xml/platform_gui_air.xml";
	}
	else
	{
		xmlFile = "xml/platform_gui_default.xml";
	}

	tcPlatformGui* gui = new tcPlatformGui(platform->mnID, platformId, wxPoint(pos.x, pos.y + size.GetHeight() + 10), 
		xmlFile.c_str());
	wxASSERT(item);
	item->SetGui(gui);
	gui->SetParentItem(item);

    // group selection mode, add all selected platforms of the same database class as the main platform
	std::vector<size_t> selectedIdx = GetSelected();
	if (selectedIdx.size() <= 1) 
	{
		gui->UpdateLoadoutList();
		return;
	}

    bool selectionContainsPlatform = false; // check if group selection includes selected platform for platform GUI
    std::vector<long> groupId;
	std::vector<size_t> groupSlotIndices;
    for (size_t n=0; n<selectedIdx.size(); n++)
    {
        tcEntityContainerItem* entityItem_n = dynamic_cast<tcEntityContainerItem*>(slots[selectedIdx[n]].GetItem());
        tcPlatformObject* platform_n = (entityItem_n != 0) ? dynamic_cast<tcPlatformObject*>(entityItem_n->GetEntity()) : 0;

        if ((platform_n != 0) && (platform_n->mpDBObject == platform->mpDBObject))
        {
            groupId.push_back(platform_n->mnID);
			groupSlotIndices.push_back(selectedIdx[n]);
        }

        if (platform_n == platform) selectionContainsPlatform = true;
    }
    if (!selectionContainsPlatform) return;

	// update container gui highlighted slots to match this group
	tcContainerGui::DeselectAllSlots();
	for (size_t n=0; n<groupSlotIndices.size(); n++)
	{
		slots[groupSlotIndices[n]].SetSelected(true);
	}

    gui->SetGroupPlatforms(groupId);

	gui->UpdateLoadoutList(); // For groups, updated here to have list account for group size
}

void tcFlightPortGui::ReadGuiParameters()
{
    TiXmlNode* root = config->FirstChild("Window");
    if (!root)
    {
        fprintf(stderr, "tcFlightPortGui::ReadGuiParameters - Missing top level <Window> tag\n");
        return;
    }

	TiXmlNode* current = root->FirstChild("FlightPort");
    if (!current)
    {
        fprintf(stderr, "tcFlightPortGui::ReadGuiParameters - Missing <FlightPort> tag\n");
        return;
    }
	
    TiXmlElement* elt = current->ToElement();    
    
    double slotSizeXml = 32.0;
    double launchX = 0;
    double launchY = 0;
    double launchSpacing = 10.0;
    double readyX = 0;
    double readyY = 20.0;
    double readySpacing = 10.0;
    double hangarX = 0;
    double hangarY = 50.0;
    double hangarSpacingH = 10.0;
    double hangarSpacingV = 10.0;
    int hangarRowSizeXml = 10;
    double hangarSlotSizeXml = 0;
    
    double magazineLocX = 0;
    double magazineLocY = 0;
    double magazineOffsetX = 0;
    double magazineOffsetY = 0;  

    elt->Attribute("SlotSize", &slotSizeXml);
    elt->Attribute("LaunchX", &launchX);
    elt->Attribute("LaunchY", &launchY);
    elt->Attribute("LaunchSpacing", &launchSpacing);
    elt->Attribute("ReadyX", &readyX);
    elt->Attribute("ReadyY", &readyY);
    elt->Attribute("ReadySpacing", &readySpacing);
    elt->Attribute("HangarX", &hangarX);
    elt->Attribute("HangarY", &hangarY);
    elt->Attribute("HangarSlotSize", &hangarSlotSizeXml);
    elt->Attribute("HangarSpacingH", &hangarSpacingH);
    elt->Attribute("HangarSpacingV", &hangarSpacingV);
    elt->Attribute("HangarRowSize", &hangarRowSizeXml);
    
    elt->Attribute("MagazineLocX", &magazineLocX);
    elt->Attribute("MagazineLocY", &magazineLocY);
    elt->Attribute("MagazineOffsetX", &magazineOffsetX);
    elt->Attribute("MagazineOffsetY", &magazineOffsetY); 


    slotSize = slotSizeXml;
    
    launchLoc.x = launchX;
    launchLoc.y = launchY;
    launchHorizontalSpacing = launchSpacing;
    
    readyLoc.x = readyX;
    readyLoc.y = readyY;
    readyHorizontalSpacing = readySpacing;
    
    hangarLoc.x = hangarX;
    hangarLoc.y = hangarY;
    hangarHorizontalSpacing = hangarSpacingH;
    hangarVerticalSpacing = hangarSpacingV; 
    hangarRowSize = hangarRowSizeXml;
    hangarSlotSize = hangarSlotSizeXml;
    useSmallHangarSlots = ((hangarSlotSize < 32.0) && (hangarSlotSize > 0));
    if (hangarSlotSize <= 0) hangarSlotSize = slotSize;

    magazineLoc.x = magazineLocX;
    magazineLoc.y = magazineLocY;
    magazineOffset.x = magazineOffsetX;
    magazineOffset.y = magazineOffsetY;
}


/**
* Update slot items based on flightPort state
*/
void tcFlightPortGui::UpdateGui()
{
	tcFlightPort* flightPort = GetFlightPort();
	if (flightPort == 0) return;

    // mark all slots not updated
    for (size_t n=0; n<slots.size(); n++)
    {
        slots[n].SetUpdated(false);
    }
    
    size_t nextHangarIdx = hangarOffset; // slot idx for next hangar unit
	
    size_t nUnits = flightPort->GetCount();
    for (size_t n=0; n<nUnits; n++)
    {
        tcAirState* airState = flightPort->GetAirState(n);

		int loc;
	    unsigned spotPos;
		if (airState->inTransit)
		{
			loc = airState->current_location;
			spotPos = (unsigned)airState->current_spot;
		}
		else
		{
			loc = airState->current_location;
			spotPos = (unsigned)airState->current_spot;
		}

		if ((loc == ALERT5)||(loc == PRETAKEOFF))
        {
            if (spotPos < readyOffset - launchOffset)
            {
                tcContainerSlot& slot = slots[spotPos + launchOffset];
				AddOrUpdateItem(slot, airState);
				slot.SetUpdated(true);
            }
            else
            {
                wxASSERT(false);
            }
        }
		else if (loc == ALERT15)
		{
            if (spotPos < hangarOffset - readyOffset)
            {
                tcContainerSlot& slot = slots[spotPos + readyOffset];
				AddOrUpdateItem(slot, airState);
				slot.SetUpdated(true);
            }
            else
            {
                wxASSERT(false);
            }

		}
		else if (loc == HANGAR)
		{
			if (nextHangarIdx < slots.size())
			{
				tcContainerSlot& slot = slots[nextHangarIdx++];
				AddOrUpdateItem(slot, airState);
				slot.SetUpdated(true);
			}
			else
			{
				wxASSERT(false);
			}
		}
    }


    // update mission plan slot (add item if not added yet)
    {
        tcContainerSlot& slot = slots[missionIdx];

        tcContainerItem* item = slot.GetItem();
        if (item == 0)
        {
            const std::string& itemName("Mission plan");
            item = new tcContainerItem();    
            slot.SetItem(item);
            item->SetIcon(missionIcon);
            item->SetItemName(itemName);
        }
        slot.SetUpdated(true);
    }

    // update magazine slots (add item if not added yet)
    tcPlatformObject* platform = dynamic_cast<tcPlatformObject*>(tcSimState::Get()->GetObject(platformId));
    if (platform != 0)
    {
        for (size_t n=magazineIdx; n<magazineIdx+nMagazines; n++)
        {
            tcContainerSlot& slot = slots[n];

            tcContainerItem* item = slot.GetItem();
            if (item == 0)
            {
                tcStores* magazine = platform->GetMagazine(n - magazineIdx);
                const std::string& magazineName = magazine->GetDisplayName();
                item = new tcContainerItem();    
                slot.SetItem(item);
                item->SetIcon(magazineIcon);
                item->SetItemName(magazineName);
            }
            slot.SetUpdated(true);
        }  
    }


	// delete items that were not updated
	for (size_t n=0; n<slots.size(); n++)
	{
		if (!slots[n].IsUpdated())
		{
			slots[n].ClearItem();
		}
	}
        
}

/**
*
*/
tcFlightPortGui::tcFlightPortGui(long id, const wxPoint& pos, 
     const wxString& configFile) 
     : tcContainerGui(pos, configFile, "FlightPortGui"), 
	   platformId(id)
{
    ReadGuiParameters();

    InitializeGui();

	SetActive(true);

#ifdef _DEBUG
	fprintf(stdout, "tcFlightPortGui::tcFlightPortGui - %s, %d slots\n", configFile.c_str(),
		slots.size());
#endif

}

tcFlightPortGui::~tcFlightPortGui() 
{

}


