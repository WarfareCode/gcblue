/** 
**  @file tcPlatformGui.cpp 
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

#include "tcPlatformGui.h"
#include "tcGameObject.h"
#include "tcPlatformObject.h"
#include "tcFlightOpsObject.h"
#include "tcDatabaseObject.h"
#include "tcAirDBObject.h"
#include "tcPlatformDBObject.h"
#include "common/tinyxml.h"
#include "tcTime.h"
#include "tcDragStatus.h"
#include "tcLauncher.h"
#include "tcLauncherContainerItem.h"
#include "tcSimState.h"
#include "tcStoresContainerItem.h"
#include "tcStoresGui.h"
#include "tcStores.h"
#include "tcFlightPortGui.h"
#include "tcButton.h"
#include "tcGeometry.h"
#include "tcListBox.h"
#include "tcUnits.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_EVENT_TABLE(tcPlatformGui, tcXmlWindow)
    EVT_COMMAND(10, wxEVT_COMMAND_BUTTON_CLICKED, tcPlatformGui::OnLoadoutCommand)
    EVT_COMMAND(11, wxEVT_COMMAND_BUTTON_CLICKED, tcPlatformGui::OnLoadoutCommand)
    EVT_COMMAND(12, wxEVT_COMMAND_BUTTON_CLICKED, tcPlatformGui::OnLoadoutCommand)
    EVT_COMMAND(13, wxEVT_COMMAND_BUTTON_CLICKED, tcPlatformGui::OnLoadoutCommand)
    EVT_COMMAND(14, wxEVT_COMMAND_BUTTON_CLICKED, tcPlatformGui::OnLoadoutCommand)
    EVT_COMMAND(15, wxEVT_COMMAND_BUTTON_CLICKED, tcPlatformGui::OnLoadoutCommand)
	EVT_COMMAND(86, wxEVT_COMMAND_BUTTON_CLICKED, tcContainerGui::OnCloseCommand)
    EVT_COMMAND(55, wxEVT_COMMAND_TEXT_UPDATED, tcPlatformGui::OnLoadoutCommand)
END_EVENT_TABLE()



tcPlatformGui* tcPlatformGui::GetExistingGui(long id, long host)
{
    std::list<tcContainerGui*>::iterator iter = 
        openContainers.begin();

    for (iter=openContainers.begin(); iter!=openContainers.end(); ++iter)
    {
        if (tcPlatformGui* platformGui = dynamic_cast<tcPlatformGui*>(*iter))
        {
            if ((platformGui->GetPlatformId() == id) && (platformGui->GetHostId() == host))
            {
                return platformGui;
            }
        }

    }
    return 0;
}

/**
* @return first stores that has at least one compatible item with platform launcher (or 0 if none found)
*/
tcStores* tcPlatformGui::GetLoadoutStores()
{
	tcPlatformObject* platform = GetPlatform();
	tcPlatformObject* host = 0;

	if (hostId != -1)
	{
		host = dynamic_cast<tcPlatformObject*>(tcSimState::Get()->GetObject(hostId));
	}
	else
	{
		host = platform;
	}

	wxASSERT(platform != 0);
	wxASSERT(host != 0);

	size_t nStores = host->GetMagazineCount();
	for (size_t n=0; n<nStores; n++)
	{
		tcStores* mag = host->GetMagazine(n);
		wxASSERT(mag);

		if (mag->HasStoresForThisObject(platform))
		{
			return mag;
		}
	}

	return 0;
}


long tcPlatformGui::GetPlatformId() const
{
    return platformId;
}

/**
* Added to support editing groups of platforms at once
* platformList already excludes NULL platforms
*/
void tcPlatformGui::GetPlatformList(std::vector<tcPlatformObject*>& platformList)
{
    platformList.clear();

    // no group editing for platforms not on host
    if (hostId == -1)
    {
        tcPlatformObject* platform = dynamic_cast<tcPlatformObject*>(tcSimState::Get()->GetObject(platformId));
        if (platform != 0) platformList.push_back(platform);
        return;
    }

    tcGameObject* parent = tcSimState::Get()->GetObject(hostId);
    if (parent == 0) return; // host not found

    for (size_t n=0; n<groupId.size(); n++)
    {
        tcPlatformObject* platform = dynamic_cast<tcPlatformObject*>(parent->GetChildById(groupId[n]));
        if (platform != 0) platformList.push_back(platform);
    }

}

long tcPlatformGui::GetHostId() const
{
    return hostId;
}


void tcPlatformGui::OnLoadoutCommand(wxCommandEvent& event)
{
    if (loadoutBox == 0) return;

    int eventId = event.GetId();
    std::string loadoutType;

    if (eventId == 55)
    {
        loadoutType = event.GetString().c_str();
    }
    else
    {
        switch (eventId)
        {
        case 10: loadoutType = "Empty"; break;
        case 11: loadoutType = "AAW"; break;
        case 12: loadoutType = "ASuW"; break;
        case 13: loadoutType = "ASW"; break;
        case 14: loadoutType = "Strike"; break;
        case 15: loadoutType = "Nuclear"; break;
        default: loadoutType = "Error"; break;
        }
    }

    std::vector<tcPlatformObject*> platformList;
    GetPlatformList(platformList);
    for (size_t n=0; n<platformList.size(); n++)
    {
        wxASSERT(platformList[n] != 0);
        platformList[n]->EquipForTargetType(loadoutType);
    }

	//tcPlatformObject* platform = GetPlatform();
	//if (platform != 0) platform->EquipForTargetType(loadoutType);
	
	/*tcStores* mag = GetLoadoutStores();
	if (mag != 0)
	{
		mag->AddAutomationOp(loadoutType, platform);
	}
	else
	{
		fprintf(stderr, "tcPlatformGui::OnLoadoutCommand -- No compatible magazine found\n");
	}*/
}

/**
* If slot has tcLauncherContainerItem then update it, otherwise create
* a new item for slot.
*/
void tcPlatformGui::AddOrUpdateLauncherItem(tcContainerSlot& slot, tcDatabaseObject* child,
                        tcLauncher* launcher, unsigned int launcherIdx, unsigned int quantity)
{
    tcLauncherContainerItem* item = dynamic_cast<tcLauncherContainerItem*>(slot.GetItem());
   
    if (item == 0)
    {
        item = new tcLauncherContainerItem();    
		slot.SetItem(item);
    }
    
    if (child)
    {
        boost::shared_ptr<tcGeometry> icon = child->GetIcon();
        item->SetIcon(icon);
        
        /* Changed to make id unique within platform gui so that
        ** correct item is unloaded. May have bad side effects.
        */
        unsigned int itemId = unsigned int(child->mnKey << 8) + launcherIdx;
		item->SetId(itemId);
	    
        std::string itemName = child->mzClass.c_str();
        item->SetItemName(itemName);
		item->SetLauncher(platformId, hostId, launcherIdx);
	    item->SetQuantity(quantity);
        item->SetGui(this);

		if (launcher->IsLoading())
		{
			item->SetDrawState(tcContainerItem::BLINK);
		}
		else
		{
			item->SetDrawState(tcContainerItem::NORMAL);
		}
    }
    else
    {
        boost::shared_ptr<tcGeometry> nullIcon((tcGeometry*)0);
        item->SetIcon(nullIcon);
        wxASSERT(false);
    }

}



void tcPlatformGui::Draw() 
{	
	tcPlatformObject* platform = GetPlatform();
	if (platform == 0)
    {
        DestroyWindow();
        return;
    }

	//if (drawCount++ % 4 != 0) return; // update draw every 4th frame

    StartDraw();

	UpdateGui();

    tcUnits* units = tcUnits::Get();


	bool blinkOn = tcTime::Get()->Get30HzCount() % 30 < 15;

    if (loadoutBox != 0)
    {
        DrawTextR("Loadout", 300, 16, defaultFont.get(), Vec4(1, 1, 1, 1), 12, LEFT_CENTER);
        loadoutBox->SetBlinkCurrent(platform->IsLoading());

        //DrawTextR(wxString::Format("%d / %d", loadoutBox->GetScrollOffset(), loadoutBox->GetListSize()).c_str(),
        //        220, 25, defaultFont.get(), Vec4(1, 1, 1, 1), 12, LEFT_CENTER);

        if (drawCount++ % 4 == 0) UpdateCustomLoadout();
    }

    // draw caption
	const Vec4 captionColor(1.0f, 1.0f, 1.0f, 1.0f);
	const char* unitName = platform->mzUnit.c_str();
    wxString captionText;
    if (groupId.size() <= 1)
    {
	    captionText = wxString::Format("%s Platform Control", unitName);
    }
    else // group mode
    {
        captionText = wxString::Format("%s x %d (%s)", platform->mpDBObject->GetDisplayName(), groupId.size(), unitName);
    }


	DrawTextR(captionText.c_str(), 10.0f, 20.0f, defaultFont.get(),
        captionColor, 18.0f, LEFT_BASE_LINE, 400.0f);    
    
    if (tcAirObject* air = dynamic_cast<tcAirObject*>(platform))
    {
        if (air->parent != 0)
        {
            float loadedWeight_kg = air->GetTotalWeight();
            float maxTakeoffWeight_kg = air->mpDBObject->maxTakeoffWeight_kg;
            if (loadedWeight_kg <= maxTakeoffWeight_kg)
            {
                wxString s = wxString::Format("%.0f / %.0f %s", units->UserMassUnits(loadedWeight_kg),
                    units->UserMassUnits(maxTakeoffWeight_kg), units->GetMassUnitLabel());
                DrawTextR(s.c_str(), 10.0f, 85.0f, defaultFont.get(),
                    Vec4(0.4f, 1, 0.4f, 1), 14.0f, LEFT_BASE_LINE, 400.0f);
            }
            else
            {
                wxString s = wxString::Format("OVERWEIGHT %.0f %s", 
                    units->UserMassUnits(loadedWeight_kg-maxTakeoffWeight_kg),
                    units->GetMassUnitLabel());
                DrawTextR(s.c_str(), 10.0f, 85.0f, defaultFont.get(),
                    Vec4(1, 1, 0, 1), 14.0f, LEFT_BASE_LINE, 400.0f);
            }

            // print damage
            float airDamageLevel = air->GetDamageLevel();
            if (airDamageLevel > 0)
            {
                wxString s = wxString::Format("Damage %.0f%%", 100.0f*airDamageLevel);
                DrawTextR(s.c_str(), 10.0f, 105.0f, defaultFont.get(),
                        Vec4(1, 1, 0, 1), 14.0f, LEFT_BASE_LINE, 400.0f);
            }

        }

    }

    


    // draw slots and items
	size_t nSlots = slots.size();
	for (size_t n=0; n<nSlots; n++)
	{
		tcContainerSlot& slot = slots[n];
		tcContainerItem* item = slot.GetItem();
		
		bool isMouseOver = slot.IsMouseOver();

		if (item)
		{
			int drawState = item->GetDrawState();
			bool doDraw = (drawState == tcContainerItem::NORMAL) ||
				((drawState == tcContainerItem::BLINK) && blinkOn);
			if (doDraw)
			{
				boost::shared_ptr<tcGeometry> icon = slot.GetIcon();
				DrawGeometryR(icon.get(), slot.loc.XCenter(), slot.loc.YCenter());
				
				unsigned quantity = item->GetQuantity();
				if (quantity)
				{
    			    // draw quantity label
                    wxString quantityText = wxString::Format("%d", quantity);
                    const Vec4 color(1.0f, 1.0f, 1.0f, 1.0f);
    				DrawTextR(quantityText.c_str(), slot.loc.GetLeft() + 2.0f, slot.loc.GetTop() - 3.0f, 
                        defaultFont.get(), color, 12.0f, LEFT_BASE_LINE);
                }
			}


        }

		/* draw caption if mouse is over slot
		** If slot has item use item name, otherwise if launcher draw launcher
		** compatibility info
		*/
		if (isMouseOver)
		{
			const Vec4 color(1.0f, 1.0f, 1.0f, 1.0f);
			wxString caption;
			if (item)
			{
				caption = item->GetItemName().c_str();
                if (tcLauncher* launcher = platform->GetLauncher(n))
                {
                    if (launcher->IsLoading())
                    {
                        wxString loadTime;
                        float opTime_s = launcher->GetLoadingTime();
                        if (opTime_s < 60.0f)
                        {
                            loadTime.Printf(" (%.0f s)", floorf(opTime_s));
                        }
                        else
                        {
                            loadTime.Printf(" (%.0f min)", floorf(0.01666f*opTime_s + 0.5f));
                        }
                        caption += loadTime;
                    }
                }
			}
			else if (n < nLaunchers)
			{
				GetLauncherCompatibilityCaption(n, caption, platform);
			}
			else
			{
				caption = "";
			}
			
			DrawTextR(caption.c_str(), slot.loc.GetLeft(), slot.loc.GetTop() + 17.0f, defaultFont.get(),
				color, 14.0f, LEFT_BASE_LINE);


		}
        
        // draw expanded rectangle for slot border
		tcRect r = slot.loc;
		r.Expand(1.0, 1.0);
		if (isMouseOver || (item && item->ItemGuiIsActive()))
		{
			DrawRectangleR(r, Vec4(1, 1, 1, 1), tc3DWindow2::FILL_OFF);
		}
		else
		{
			DrawRectangleR(r, Vec4(0.5, 0.5, 0.5, 1), tc3DWindow2::FILL_OFF);
		}
        
	}

	// draw fuel state info under fuel icon if mouse is not over icon
	tcContainerSlot& fuelSlot = slots[fuelIdx];
	if (!fuelSlot.IsMouseOver())
	{
		float x = fuelSlot.loc.GetLeft() - 15.0f;
		float y = fuelSlot.loc.GetTop() + 17.0f;
		float fuelCapacity_kg = platform->GetFuelCapacity();

		wxString caption;
		if (fuelCapacity_kg > 0)
		{
		    caption = wxString::Format("Fuel: %.0f / %.0f %s", 
                units->UserMassUnits(platform->fuel_kg),
			    units->UserMassUnits(fuelCapacity_kg),
                units->GetMassUnitLabel());
		}
		else
		{
			caption = "Fuel: N/A";
		}
		const Vec4 color(1.0f, 1.0f, 1.0f, 1.0f);

		DrawTextR(caption.c_str(), x, y, defaultFont.get(),
				color, 14.0f, LEFT_BASE_LINE);
	}

	FinishDraw();
}

tcFlightOpsObject* tcPlatformGui::GetFlightOps()
{
	if (hostId != -1)
	{
		return 0;
	}
	else
	{
		return dynamic_cast<tcFlightOpsObject*>(tcSimState::Get()->GetObject(platformId));
	}
}

/**
* Creates caption that describes compatible items for launcher
*/
void tcPlatformGui::GetLauncherCompatibilityCaption(unsigned int launcherIdx, wxString& caption, tcPlatformObject* platform)
{
	caption = "";

	tcLauncher* launcher = platform->GetLauncher(launcherIdx);
	wxASSERT(launcher);

	unsigned int nTypes = launcher->GetCompatibleCount();
	for (unsigned int n=0; n<nTypes; n++)
	{
		wxString s = wxString::Format("%s(%d) ", launcher->GetCompatibleName(n).c_str(),
			            launcher->GetCompatibleQuantity(n));
		caption += s;
	}
}

tcPlatformObject* tcPlatformGui::GetPlatform()
{
	if (hostId == -1)
	{
		return dynamic_cast<tcPlatformObject*>(tcSimState::Get()->GetObject(platformId));
	}
	
	tcGameObject* parent = tcSimState::Get()->GetObject(hostId);
	if (parent == 0) return 0;

	return dynamic_cast<tcPlatformObject*>(parent->GetChildById(platformId));
}

void tcPlatformGui::HandleDrop(size_t slotIdx, const std::vector<tcContainerItem*>& items)
{
    tcContainerItem* item = (items.size() > 0) ? items[0] : 0;

	tcStoresContainerItem* storesItem = dynamic_cast<tcStoresContainerItem*>(item);
	if (storesItem == 0) return; // only handle entity items

	if (slotIdx == fuelIdx)
	{
		HandleFuelDrop(storesItem);
		return;
	}
    tcStores* magazine = storesItem->GetStores();
    if (magazine == 0) return;


	tcPlatformObject* platform = GetPlatform();
	if (platform == 0) return;

    if (slotIdx >= nLaunchers) return; // only accept drops to launchers
    
    std::vector<tcPlatformObject*> platformList;
    GetPlatformList(platformList); // already excludes NULL platforms

    bool anyLoaded = false;

    for (size_t n=0; n<platformList.size(); n++)
    {
        tcPlatformObject* platform_n = platformList[n];
        wxASSERT(platform_n != 0);

        int quantity = 0;
        std::string childClass;
        tcLauncher* launcher = platform_n->GetLauncher(slotIdx);
        if (launcher != 0)
        {
            quantity = launcher->mnCurrent;
            childClass = launcher->GetChildClassName();
        }

        if ((quantity == 0) || (item->GetItemName() == childClass))
        {
            magazine->LoadLauncher(slotIdx, storesItem->GetItemName(), platform_n); 
        }
        else
        {
            wxASSERT(false);
        }

        //tcContainerSlot& slot = slots[slotIdx];
        //if (!slot.IsEmpty())
        //{
        //    if (item->GetItemName() != slot.GetItem()->GetItemName())
        //    {
        //        return; // slot must be empty or of same item (top off)
        //    }
        //}
        //magazine->LoadLauncher(slotIdx, storesItem->GetItemName(), platform); 
    }

    if (anyLoaded)
    {
	    tcSound::Get()->PlayEffect("Thuck");
    }
	
}

void tcPlatformGui::HandleFuelDrop(tcStoresContainerItem* item)
{
	wxASSERT(item);
	const std::string& itemName = item->GetItemName();
	if (itemName != "Fuel") return;

	tcStores* stores = item->GetStores();
	if (stores == 0) return;

    std::vector<tcPlatformObject*> platformList;
    GetPlatformList(platformList);

    for (size_t n=0; n<platformList.size(); n++)
    {
	    stores->LoadOther(itemName, 999999, platformList[n]);
    }

	tcSound::Get()->PlayEffect("Thuck");
}

void tcPlatformGui::InitializeGui()
{
	tcPlatformObject* platform = GetPlatform();
    wxASSERT(platform);
	if (platform == 0) return;
    
    // add launcher slots
    tcRect slotLoc(launcherLoc.x, launcherLoc.x + slotSize,
               launcherLoc.y, launcherLoc.y + slotSize);
    nLaunchers = platform->GetLauncherCount();
    for (size_t n=0; n<nLaunchers; n++)
    {
        AddSlot(slotLoc);
        
        slotLoc.Offset(launcherOffset.x, launcherOffset.y);
    }
    
    // add magazine slots
    slotLoc.Set(magazineLoc.x, magazineLoc.x + slotSize,
                magazineLoc.y, magazineLoc.y + slotSize);
    nMagazines = platform->GetMagazineCount();
    magazineIdx = nLaunchers;
    for (size_t n=0; n<nMagazines; n++)
    {
        AddSlot(slotLoc);
        
        slotLoc.Offset(magazineOffset.x, magazineOffset.y);
    }
    
    // add flightport slot if applicable
    tcFlightOpsObject* flightOps = GetFlightOps();
    flightPortIdx = nLaunchers + nMagazines;
    if (flightOps != 0)
    {
        slotLoc.Set(flightPortLoc.x, flightPortLoc.x + slotSize,
                    flightPortLoc.y, flightPortLoc.y + slotSize);
        AddSlot(slotLoc);
		nFlightPorts = 1;
    }
    else
    {
        nFlightPorts = 0;
    }

	// add fuel slot for refueling
	fuelIdx = nLaunchers + nMagazines + nFlightPorts;
	slotLoc.Set(fuelLoc.x, fuelLoc.x + slotSize,
		        fuelLoc.y, fuelLoc.y + slotSize);
	AddSlot(slotLoc);

	// load icons
	magazineIcon = tc3DWindow2::CreateTexturedSymbol("icons\\magazine.jpg", 32.0f);
	flightPortIcon = tc3DWindow2::CreateTexturedSymbol("icons\\flightport.jpg", 32.0f);
	fuelIcon = tc3DWindow2::CreateTexturedSymbol("icons\\refuel.jpg", 32.0f);

    tcAirObject* air = dynamic_cast<tcAirObject*>(platform);
    if ((platform->parent != 0) && (air != 0))
    {
        loadoutBox = new tcListBox(this, wxPoint(350, 6), wxSize(120, 18));
        loadoutBox->SetActive(true);
        loadoutBox->SetCommand(55);
    }
}

void tcPlatformGui::OnLButtonDClick(wxMouseEvent& event)
{
    tcPlatformGui::OnRButtonDown(event);
}

/**
*
*/
void tcPlatformGui::OnRButtonDown(wxMouseEvent& event)
{
    wxPoint point = event.GetPosition();

    float x = (float)point.x;
    float y = (float)point.y;


    // cancel load in progress if over launcher slot that's loading
	tcPlatformObject* platform = GetPlatform();
	if (platform == 0) return;
    for (size_t n=0; n<nLaunchers; n++)
    {
        tcContainerSlot& slot = slots[n];

        if (slot.loc.ContainsPoint(x, y))
        {
            tcLauncher* launcher = platform->GetLauncher(n);
            if (launcher->IsLoading())
            {
                launcher->CancelLoadInProgress();
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

	// check if cursor is over flightport slot
	for (size_t n=flightPortIdx; n<flightPortIdx+nFlightPorts; n++)
	{
		tcContainerSlot& slot = slots[n];

		if (slot.loc.ContainsPoint(x, y))
		{
			tcContainerItem* item = slot.GetItem();
			wxASSERT(item);
			tcContainerGui* gui = item->GetGui();

			// toggle gui (close any other open platform guis before opening this one)
			if (gui)
			{
				gui->DestroyWindow();
				item->SetGui(0);
			}
			else
			{
				OpenFlightPortGui(item);
			}
			return;
		}
	}
	

}

void tcPlatformGui::OpenFlightPortGui(tcContainerItem* item)
{
	tcFlightOpsObject* flightOps = GetFlightOps();
	if (flightOps == 0) return;
	tcFlightPort* flightPort = flightOps->GetFlightPort();
	if (flightPort == 0) return;

	tcPlatformObject* platform = GetPlatform();
	wxASSERT(platform != 0);
	if (platform == 0) return;

	wxPoint pos = wxWindow::GetPosition();
	wxSize size = wxWindow::GetSize();

    std::string xmlFile;
    if (flightPort->GetHangarCapacity() > 20)
    {
        xmlFile = "xml/flightport_gui_large.xml";
    }
    else
    {
        xmlFile = "xml/flightport_gui_default.xml";
    }

	tcFlightPortGui* gui = new tcFlightPortGui(platform->mnID, wxPoint(pos.x, pos.y + size.GetHeight() + 10), 
		                            xmlFile.c_str());
	wxASSERT(item);
	item->SetGui(gui);
	gui->SetParentItem(item);
}

/**
* Open magazine gui
*/
void tcPlatformGui::OpenMagazineGui(unsigned int idx, tcContainerItem* item)
{
	tcPlatformObject* platform = GetPlatform();
	if (platform == 0) return;

	tcStores* magazine = platform->GetMagazine(idx);
	if (magazine)
	{
		wxPoint pos = wxWindow::GetPosition();
		wxSize size = wxWindow::GetSize();
		tcStoresGui* gui = new tcStoresGui(platformId, hostId, idx, wxPoint(pos.x + size.GetWidth() + 10 + float(idx)*50.0f, pos.y + float(idx)*50.0f), 
			                       "xml/stores_gui_table.xml");
		wxASSERT(item);
		item->SetGui(gui);
		gui->SetParentItem(item);
	}
}

void tcPlatformGui::ReadGuiParameters()
{
    TiXmlNode* root = config->FirstChild("Window");
    if (!root)
    {
        fprintf(stderr, "tcPlatformGui::ReadGuiParameters - Missing top level <Window> tag\n");
        return;
    }

	TiXmlNode* current = root->FirstChild("Platform");
    if (!current)
    {
        fprintf(stderr, "tcPlatformGui::ReadGuiParameters - Missing <Platform> tag\n");
        return;
    }
	
    TiXmlElement* elt = current->ToElement();    
    
    double slotSizeXml = 16.0;
    
    double launcherLocX = 0;
    double launcherLocY = 0;
    double launcherOffsetX = 0;
    double launcherOffsetY = 0;   
     
    double magazineLocX = 0;
    double magazineLocY = 0;
    double magazineOffsetX = 0;
    double magazineOffsetY = 0;  
       
    double flightPortLocX = 0;
    double flightPortLocY = 0;

	double fuelLocX = 0;
	double fuelLocY = 0;
    
    elt->Attribute("SlotSize", &slotSizeXml);
    
    elt->Attribute("LauncherLocX", &launcherLocX);
    elt->Attribute("LauncherLocY", &launcherLocY);
    elt->Attribute("LauncherOffsetX", &launcherOffsetX);
    elt->Attribute("LauncherOffsetY", &launcherOffsetY);   
    
    elt->Attribute("MagazineLocX", &magazineLocX);
    elt->Attribute("MagazineLocY", &magazineLocY);
    elt->Attribute("MagazineOffsetX", &magazineOffsetX);
    elt->Attribute("MagazineOffsetY", &magazineOffsetY); 
        
    elt->Attribute("FlightPortLocX", &flightPortLocX);
    elt->Attribute("FlightPortLocY", &flightPortLocY);    
    
    elt->Attribute("FuelLocX", &fuelLocX);
    elt->Attribute("FuelLocY", &fuelLocY);   

    slotSize = slotSizeXml;
    
    launcherLoc.x = launcherLocX;
    launcherLoc.y = launcherLocY;
    launcherOffset.x = launcherOffsetX;
    launcherOffset.y = launcherOffsetY;
    
    magazineLoc.x = magazineLocX;
    magazineLoc.y = magazineLocY;
    magazineOffset.x = magazineOffsetX;
    magazineOffset.y = magazineOffsetY;
    
    flightPortLoc.x = flightPortLocX;
    flightPortLoc.y = flightPortLocY;     

	fuelLoc.x = fuelLocX;
	fuelLoc.y = fuelLocY;
    
}

void tcPlatformGui::SetGroupPlatforms(const std::vector<long>& groupId_)
{
    groupId = groupId_;

#ifdef _DEBUG
    // check that all platforms are of the same database class
    tcPlatformObject* mainPlatform = GetPlatform();
    wxASSERT(mainPlatform != 0);

    std::vector<tcPlatformObject*> platformList;
    GetPlatformList(platformList);
    for (size_t n=0; n<platformList.size(); n++)
    {
        wxASSERT(platformList[n]->mpDBObject == mainPlatform->mpDBObject);
    }
#endif
}

/**
* Update slot items based on tcStores state
*/
void tcPlatformGui::UpdateGui()
{
	tcPlatformObject* platform = GetPlatform();
	if (platform == 0) return;

    // mark all slots not updated
    for (size_t n=0; n<slots.size(); n++)
    {
        slots[n].SetUpdated(false);
    }
    
    // update launcher slots
    for (size_t n=0; n<nLaunchers; n++)
    {
        tcLauncher* launcher = platform->GetLauncher(n);
		bool isLoading = launcher->IsLoading();
		if ((launcher->mnCurrent > 0) || isLoading)
        {
            tcContainerSlot& slot = slots[n];
            
 		    tcDatabaseObject* child = launcher->GetChildDatabaseObject();
		    unsigned int itemQuantity = launcher->mnUncommitted;          
            AddOrUpdateLauncherItem(slot, child, launcher, n, itemQuantity);
            slot.SetUpdated(true);
        }
    }
    
    // update magazine slots (add item if not added yet)
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
    
    // update flightport slots (add item if not added yet)
    for (size_t n=flightPortIdx; n<flightPortIdx+nFlightPorts; n++)
    {
        tcContainerSlot& slot = slots[n];
        
        tcContainerItem* item = slot.GetItem();
        if (item == 0)
        {
            item = new tcContainerItem();    
    		slot.SetItem(item);
    		item->SetIcon(flightPortIcon);
			item->SetItemName("Right click to open");
        }
        slot.SetUpdated(true);
    }

	// update refuel slot (add item if not added yet)
	{
        tcContainerSlot& slot = slots[fuelIdx];
        
        tcContainerItem* item = slot.GetItem();
        if (item == 0)
        {
            item = new tcContainerItem();    
    		slot.SetItem(item);
    		item->SetIcon(fuelIcon);
			item->SetItemName("Drag fuel here to refuel");
        }
		if (platform->IsRefueling())
		{
			item->SetDrawState(tcContainerItem::BLINK);
		}
		else
		{
			item->SetDrawState(tcContainerItem::NORMAL);
		}

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
        
}

/**
* Checks if non auto loadout is in progress and marks loadout
* box as "Custom" if so
*/
void tcPlatformGui::UpdateCustomLoadout()
{
	tcPlatformObject* platform = GetPlatform();
	tcAirObject* air = dynamic_cast<tcAirObject*>(platform);
	if (air == 0) return;

	tcStores* mag = GetLoadoutStores();
	if (mag == 0) return;

    if ((platform->IsLoading()) && (!mag->HasActiveOp(air)) && (loadoutBox != 0))
    {
        loadoutBox->SetCaption("Custom");
    }
}

/**
*
*/
void tcPlatformGui::UpdateLoadoutList()
{
	tcPlatformObject* platform = GetPlatform();
	tcAirObject* air = dynamic_cast<tcAirObject*>(platform);
	if ((air == 0) || (platform->parent == 0)) return;

    loadoutBox->Clear();
    loadoutBox->AddItem("Empty");

	tcStores* mag = GetLoadoutStores(); // assumes all weapons in one magazine
	if (mag == 0) return;

	size_t groupSize = groupId.size();

//	const long cmd_list[4] = {11, 12, 13, 14};
	const int tgt_flags[4] = {AIR_TARGET, SURFACE_TARGET, SUBSURFACE_TARGET, LAND_TARGET};
    std::vector<std::string> typeNames;
    typeNames.push_back("AAW");
    typeNames.push_back("ASuW");
    typeNames.push_back("ASW");
    typeNames.push_back("Strike");

    int availableTargetFlags = mag->GetAvailableTargetFlags(platform);

    for (size_t n=0; n<4; n++)
    {
        bool available = (availableTargetFlags & tgt_flags[n]) != 0;
        if (available)
        {
            std::vector<tcStores::WeaponInfo> bestForLauncher;
            bool success = mag->GetBestGenericLoadout(air, typeNames[n], bestForLauncher);

            if (success)
            {
                std::string loadoutPopup;
                for (size_t launcher_idx=0; launcher_idx<bestForLauncher.size(); launcher_idx++)
                {
                    if (bestForLauncher[launcher_idx].quantity > 0)
                    {
                        size_t loadoutQuantity = std::min(bestForLauncher[launcher_idx].quantity, bestForLauncher[launcher_idx].capacity);
                        wxString desc = wxString::Format("%s (%d)\n", 
                            bestForLauncher[launcher_idx].name.c_str(), loadoutQuantity);
                        loadoutPopup += desc.c_str();
                    }
                }
                loadoutBox->AddItem(typeNames[n], loadoutPopup);
            }

        }
	}    

    if (mag->HasNuclearWeapons())
    {
        std::vector<tcStores::WeaponInfo> bestForLauncher;
        bool success = mag->GetBestGenericLoadout(air, "Nuclear", bestForLauncher);
        if (success)
        {
            std::string loadoutPopup;
            for (size_t launcher_idx=0; launcher_idx<bestForLauncher.size(); launcher_idx++)
            {
                if (bestForLauncher[launcher_idx].quantity > 0)
                {
                    size_t loadoutQuantity = std::min(bestForLauncher[launcher_idx].quantity, bestForLauncher[launcher_idx].capacity);
                    wxString desc = wxString::Format("%s (%d)\n", 
                        bestForLauncher[launcher_idx].name.c_str(), loadoutQuantity);
                    loadoutPopup += desc.c_str();
                }
            }
            loadoutBox->AddItem("Nuclear", loadoutPopup);
        }
    }

    float currentYear = tcSimState::Get()->GetDateTime().GetFractionalYear();

    const std::vector<tcLoadoutData>& loadoutList = air->mpDBObject->GetLoadoutList(currentYear);


    for (size_t n=0; n<loadoutList.size(); n++)
    {
        if (mag->HasStoresForLoadout(loadoutList[n]))
        {
            const std::vector<database::LauncherLoadout>& loadout = loadoutList[n].launcherLoadout;
            std::vector<tcStores::WeaponInfo> bestForLauncher;
            bool success = mag->GetBestLoadout(air, loadout, bestForLauncher, groupSize);
            if (success)
            {
                std::string loadoutPopup;
                for (size_t launcher_idx=0; launcher_idx<bestForLauncher.size(); launcher_idx++)
                {
                    if (bestForLauncher[launcher_idx].quantity > 0)
                    {
                        size_t loadoutQuantity = std::min(bestForLauncher[launcher_idx].quantity, bestForLauncher[launcher_idx].capacity);
                        wxString desc = wxString::Format("%s (%d)\n", 
                            bestForLauncher[launcher_idx].name.c_str(), loadoutQuantity);
                        loadoutPopup += desc.c_str();
                    }
                }

                loadoutBox->AddItem(loadoutList[n].setupName, loadoutPopup);
            }
        }
    }

}


/**
*
*/
tcPlatformGui::tcPlatformGui(long id, long host, const wxPoint& pos, 
     const wxString& configFile) 
     : tcContainerGui(pos, configFile, "PlatformGui"), 
	   platformId(id),
	   hostId(host),
       loadoutBox(0)
{
    groupId.push_back(id);

    ReadGuiParameters();

    InitializeGui();

	SetActive(true);

#ifdef _DEBUG
	fprintf(stdout, "tcPlatformGui::tcPlatformGui - %s, %d slots\n", configFile.c_str(),
		slots.size());
#endif

}

tcPlatformGui::~tcPlatformGui() 
{

}


