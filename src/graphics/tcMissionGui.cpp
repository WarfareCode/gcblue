/** 
**  @file tcMissionGui.cpp 
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

#include "tcMissionGui.h"
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
#include "tcGeometry.h"
#include "ai/tcMissionManager.h"
#include "ai/tcMission.h"
#include "ai/tcAttackMission.h"
#include "tcEntityContainerItem.h"
#include "tcListBox.h"
#include "tcEditBox.h"
#include "tcButton.h"
#include "tcCommandQueue.h"
#include "tcNumberWidget.h"
#include "wx/textfile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


BEGIN_EVENT_TABLE(tcMissionGui, tcXmlWindow)
    EVT_COMMAND(86, wxEVT_COMMAND_BUTTON_CLICKED, tcContainerGui::OnCloseCommand)

    EVT_COMMAND(AREA_PATROL, wxEVT_COMMAND_BUTTON_CLICKED, tcMissionGui::OnAreaPatrolCommand)
    EVT_COMMAND(BARRIER_PATROL, wxEVT_COMMAND_BUTTON_CLICKED, tcMissionGui::OnBarrierPatrolCommand)
    EVT_COMMAND(FERRY_MISSION, wxEVT_COMMAND_BUTTON_CLICKED, tcMissionGui::OnFerryMissionCommand)
    EVT_COMMAND(STRIKE_MISSION, wxEVT_COMMAND_BUTTON_CLICKED, tcMissionGui::OnStrikeMissionCommand)
    EVT_COMMAND(SET_LANDTARGET, wxEVT_COMMAND_BUTTON_CLICKED, tcMissionGui::OnSetLandTargetCommand)

    EVT_COMMAND(55, wxEVT_COMMAND_TEXT_UPDATED, tcMissionGui::OnMissionSelectCommand)
    EVT_COMMAND(65, wxEVT_COMMAND_TEXT_UPDATED, tcMissionGui::OnMissionTypeCommand)
    EVT_COMMAND(75, wxEVT_COMMAND_TEXT_UPDATED, tcMissionGui::OnStartTimeUpdate)
    EVT_COMMAND(85, wxEVT_COMMAND_TEXT_UPDATED, tcMissionGui::OnWaveCountUpdate)
    EVT_COMMAND(101, wxEVT_COMMAND_TEXT_UPDATED, tcMissionGui::OnTimeEntryWheelDown)
    EVT_COMMAND(102, wxEVT_COMMAND_TEXT_UPDATED, tcMissionGui::OnTimeEntryWheelUp)
END_EVENT_TABLE()


tcCommandQueue* tcMissionGui::commandInterface = 0;
wxArrayString tcMissionGui::missionTypes;

tcMissionGui* tcMissionGui::GetExistingGui(long id)
{
    std::list<tcContainerGui*>::iterator iter = 
        openContainers.begin();

    for (iter=openContainers.begin(); iter!=openContainers.end(); ++iter)
    {
        if (tcMissionGui* flightPortGui = dynamic_cast<tcMissionGui*>(*iter))
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
* @param unitName when airState == 0, use unitName to configure the slot
* @return false if update failed (couldn't find unit)
*/
bool tcMissionGui::AddOrUpdateItem(tcContainerSlot& slot, tcAirState* airState, const std::string& unitName)
{
    tcEntityContainerItem* item = dynamic_cast<tcEntityContainerItem*>(slot.GetItem());
   
    if (item == 0)
    {
        item = new tcEntityContainerItem();    
		slot.SetItem(item);
    }

    if (airState == 0)
    {
        tcSimState* simState = tcSimState::Get();
        if (tcGameObject* obj = simState->GetObjectByName(unitName))
        {
            wxString s(obj->GetName());
            if (obj->parent == 0)
            {
                s += " (IN FLIGHT)";
            }
            item->SetDescription(s.c_str());
            item->SetEntity(obj->mnID, -1);
            item->SetIcon(obj->mpDBObject->GetIcon());
            item->SetId(0);
            item->SetQuantity(0);
            item->SetDrawState(tcContainerItem::NORMAL);
            return true;
        }
        else // cant find object, probably destroyed
        {
            item->SetDescription("");
            item->SetEntity(-1, -1);
            item->SetId(0);
            item->SetQuantity(0);
            item->SetDrawState(tcContainerItem::NORMAL);
            return false;
        }
    }
 
    boost::shared_ptr<tcGeometry> icon = airState->obj->mpDBObject->GetIcon();

	wxString s = wxString::Format("%s (%s)", airState->obj->mzClass.c_str(), airState->obj->mzUnit.c_str());
	item->SetDescription(s.c_str());
	item->SetEntity(airState->obj->mnID, platformId);
	item->SetIcon(icon);
	item->SetId(reinterpret_cast<long>(airState));
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

    return true;
}

void tcMissionGui::CloseAllPlatformGuis()
{
	size_t nSlots = slots.size();
	for (size_t n=0; n<nSlots; n++)
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

void tcMissionGui::Draw() 
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
	wxString captionText = wxString::Format("%s Mission Edit", unitName);
	DrawTextR(captionText.c_str(), 10.0f, 19.0f, defaultFont.get(),
        captionColor, 18.0f, LEFT_CENTER);

	if (missionId == 0)
    {
        wxString s = wxString::Format("SELECT MISSION");
	    DrawTextR(s.c_str(), float(mnWidth/2), float(mnHeight/2), defaultFont.get(),
            captionColor, 18.0f, CENTER_CENTER);
        FinishDraw();
        return;
    }

    // draw slots and items
	size_t nSlots = slots.size();
	for (size_t n=0; n<nSlots; n++)
	{
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
			if (!isMouseOver && (air != 0))
            {
                caption = air->GetLoadoutTag();
                if (caption.size() == 0)
                {
                    air->UpdateLoadoutTag();
                    caption = air->GetLoadoutTag();
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

			DrawGeometryR(icon.get(), slot.loc.XCenter(), slot.loc.YCenter());


            if (!isMouseOver)
            {
                if (caption.size() > 0)
                {
                    const Vec4 color(1.0f, 1.0f, 1.0f, 1.0f);
                    DrawTextR(caption.c_str(), slot.loc.XCenter(), slot.loc.GetTop() + 8.0f, defaultFont.get(),
                        color, 10.0f, CENTER_CENTER);
                }
            }
            else
            {
                if (caption.size() == 0)
                {
                    caption = item->GetItemName().c_str();
                }

				const Vec4 color(1.0f, 1.0f, 1.0f, 1.0f);
				DrawTextR(caption.c_str(), slot.loc.GetLeft(), slot.loc.GetTop() + 18.0f, defaultFont.get(),
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

		DrawRectangleR(r, borderColor, tc3DWindow2::FILL_OFF);
        
        if ((entityItem != 0) && (slot.IsSelected()))
        {
            DrawThickRectangleR(r, 1.0f, Vec4(1.0f, 1.0f, 0.6f, 0.95f));
        }


	}

    DrawSelectionBox();

	FinishDraw();
}

/**
* To shut off mission graphics when no mission is selected
*/
void tcMissionGui::EnableMissionGraphics(bool state)
{
    areaPatrol->SetActive(state);
    barrierPatrol->SetActive(state);
    ferryMission->SetActive(state);
    strikeMission->SetActive(state);
    missionTypeBox->SetActive(state);

    timeEntry->SetActive(state);
    waveEdit->SetActive(state);
}

tcFlightPort* tcMissionGui::GetFlightPort()
{
	tcFlightOpsObject* flightOps = 
             dynamic_cast<tcFlightOpsObject*>(tcSimState::Get()->GetObject(platformId));
	if (flightOps == 0) return 0;

	return flightOps->GetFlightPort();
}


ai::tcMission* tcMissionGui::GetMission()
{
    ai::tcMissionManager* missionManager = GetMissionManager();
    if (missionManager == 0)
    {
        return 0;
    }

    ai::tcMission* mission = missionManager->GetMission(missionId);
    return mission;
}


ai::tcMissionManager* tcMissionGui::GetMissionManager()
{
    tcGameObject* obj = tcSimState::Get()->GetObject(platformId);
    tcFlightOpsObject* host = dynamic_cast<tcFlightOpsObject*>(obj);
    if (host == 0)
    {
        return 0;
    }
    
    return host->GetFlightPort()->GetMissionManager();
}



long tcMissionGui::GetPlatformId() const
{
    return platformId;
}


void tcMissionGui::HandleDrop(size_t slotIdx, const std::vector<tcContainerItem*>& items)
{
	tcFlightPort* flightPort = GetFlightPort();
    ai::tcMissionManager* missionManager = GetMissionManager();
    ai::tcMission* mission = GetMission();
    if ((slotIdx >= slots.size()) || (flightPort == 0) || (mission == 0) || (missionManager == 0) || mission->IsLocked())
    {
        wxASSERT(slotIdx < slots.size());
        return;
    }

    if (items.size() > 1)
    {
        HandleDropWindow(items);
    }
    else
    {
        tcContainerItem* item = (items.size() > 0) ? items[0] : 0;

        tcContainerSlot& slot = slots[slotIdx];	// target slot

        tcEntityContainerItem* droppedEntityItem = dynamic_cast<tcEntityContainerItem*>(item);
        if (droppedEntityItem == 0) return; // only handle entity items
        tcGameObject* droppedEntity = droppedEntityItem->GetEntity();
        if (droppedEntity == 0) return;

        // check that dropped is either unassigned or on current mission (position swap)
        unsigned int droppedMissionId = missionManager->GetAircraftMissionId(droppedEntity->GetName());
        if ((droppedMissionId != 0) && (droppedMissionId != missionId)) return;

        tcEntityContainerItem* currentEntityItem = 0; // entity item in slot
        tcGameObject* currentEntity = 0;
        if (!slot.IsEmpty())
        {
            currentEntityItem = dynamic_cast<tcEntityContainerItem*>(slot.GetItem());    
            currentEntity = (currentEntityItem != 0) ? currentEntityItem->GetEntity() : 0;
            if (currentEntity != 0)
            {
                mission->SwapMissionAircraft(currentEntity->GetName(), currentEntity->mnID,
                    droppedEntity->GetName(), droppedEntity->mnID);
                tcSound::Get()->PlayEffect("Thuck");
                return;
            }

        }

        int droppedUnitIdx = flightPort->FindAirState(droppedEntity);
        if (droppedUnitIdx < 0) return; // entity not found
        tcAirState* droppedAirState = flightPort->GetAirState(droppedUnitIdx);
        if (droppedAirState == 0) return;

        if (slotIdx < slots.size())
        {
            mission->AddMissionAircraft(droppedEntity->GetName(), "Strike");
        }
        else
        {
            wxASSERT(false);
        }
    }


	tcSound::Get()->PlayEffect("Thuck");
}

void tcMissionGui::HandleDropWindow(const std::vector<tcContainerItem*>& items)
{
    ai::tcMissionManager* missionManager = GetMissionManager();
    ai::tcMission* mission = GetMission();
    if ((missionManager == 0) || (mission == 0))
    {
        return;
    }

    std::vector<tcGameObject*> entityList;
    for (size_t n=0; n<items.size(); n++)
    {
        tcEntityContainerItem* entityItem = dynamic_cast<tcEntityContainerItem*>(items[n]);
        tcGameObject* entity = (entityItem != 0) ? entityItem->GetEntity() : 0;
        if (entity != 0)
        {
            entityList.push_back(entity);
        }
    }

    for (size_t n=0; n<entityList.size(); n++)
    {
        tcGameObject* entity = entityList[n];

        unsigned int aircraftMissionId = missionManager->GetAircraftMissionId(entity->GetName());

        if (aircraftMissionId == 0) // unassigned
        {
            mission->AddMissionAircraft(entity->GetName(), "Strike");
        }
        else if (aircraftMissionId == missionId)
        {
            float currentDragDistance = tcDragStatus::Get()->CurrentDragDistance();
            if (currentDragDistance > 50.0f)
            {
                mission->RemoveMissionAircraft(entity->GetName());
            }
        }
    }
    
}


void tcMissionGui::InitializeGui()
{
	tcFlightPort* flightPort = GetFlightPort();
    wxASSERT(flightPort);
	if (flightPort == 0) return;

    tcFlightportDBObject* databaseObj = flightPort->GetDatabaseObject();
    wxASSERT(databaseObj);
    if (databaseObj == 0) return;
    
    
    // add strike slots
    strikeOffset = 0;
    tcRect slotLoc(strikeLoc.x, strikeLoc.x + slotSize,
                   strikeLoc.y, strikeLoc.y + slotSize);
    for (size_t n=0; n<STRIKE_SPOTS; n++)
    {
        AddSlot(slotLoc);
        slotLoc.Offset(strikeHorizontalSpacing, 0);

        if (n == (STRIKE_SPOTS/2 -1)) // make 2 rows
        {
            slotLoc.Offset(0, strikeHorizontalSpacing+10.0f);
            slotLoc.left = strikeLoc.x;
            slotLoc.right = strikeLoc.x + slotSize;
        }
    }
    

    // add list box to select current mission to edit
    missionSelectBox = new tcListBox(this, wxPoint(300, 10), wxSize(90, 15));
    missionSelectBox->SetActive(true);
    missionSelectBox->SetCommand(55);
    UpdateMissionList();

    // edit box for entering mission start time
    if (config == 0)
    {
        fprintf(stderr, "tcMissionGui::InitializeGui - NULL xml config node\n");
        return;
    }
    TiXmlNode* root = config->FirstChild("Window");
    if (!root)
    {
        fprintf(stderr, "tcMPGameView::tcMPGameView - Missing top level <Window> tag\n");
        return;
    }


    // add start time edit box
    TiXmlNode* current = root->FirstChild("StartTime");
    timeEntry = new tcEditBox(this, current);
    timeEntry->SetActive(true);
    timeEntry->SetCommand(75);
    timeEntry->SetBoxColor(Vec4(0.2f, 0.2f, 0.2f, 0.5f));
    timeEntry->SetTextColor(Vec4(0.8f, 0.8f, 0.8f, 0.8f));
    timeEntry->SetClearOnReturn(false);
    timeEntry->SetBuffer("");
    timeEntry->SetCaption("MISSION START TIME");
    timeEntry->SetCaptionFontSize(10.0f);
    timeEntry->SetCaptionAlignment(LEFT_CENTER);
    timeEntry->SetMouseWheelParameters(102, 101, true);

    // add wave count edit box
    wxPoint wavePos = timeEntry->GetPosition();
    wxSize waveSize = timeEntry->GetSize();
    wavePos += wxSize(waveSize.x + 15, 0);
    waveSize.x = 20;
    waveEdit = new tcNumberWidget<float>(waveQuantity, this, wavePos, waveSize);
    waveEdit->SetActive(true);
    waveEdit->SetFillColor(Vec4(0.2f, 0.2f, 0.2f, 0.5f), Vec4(0.3f, 0.3f, 0.3f, 0.5f), Vec4(0.3f, 0.5f, 0.3f, 0.5f));
    waveEdit->SetTextColor(Vec4(0.8f, 0.8f, 0.8f, 0.8f), Vec4(1, 1, 1, 1));
    waveEdit->SetBorderDraw(false);
    waveEdit->SetCaption("QTY");
    waveEdit->SetCaptionParameters(0, float(waveSize.y + 2), 10.0f, LEFT_BASE_LINE);
    waveEdit->SetFontSize(12.0);
    waveEdit->EnableUpdateMessages(true, 85);
    waveEdit->SetBounds(0, 24.0f);

    // add mission creation buttons
    wxPoint buttonPos(25, 80);

    areaPatrol = new tcButton(this, buttonPos, wxSize(32, 32), "AreaPatrol");
    areaPatrol->LoadImages("area_icon_dark.png", "area_icon_green.png", "area_icon.png", "area_icon.png");
    areaPatrol->SetActive(true);
    areaPatrol->SetOn(false);
    areaPatrol->SetInteractive(true);
    areaPatrol->SetCommand(AREA_PATROL);
    areaPatrol->SetMouseOverCaption("AREA PATROL");
    areaPatrol->SetMouseOverCaptionPosition(wxPoint(16, -10));
    areaPatrol->SetShowCaptionWhenOn(false);
    areaPatrol->SetFontSize(14.0f);

    buttonPos.x += 45;
    barrierPatrol = new tcButton(this, buttonPos, wxSize(32, 32), "BarrierPatrol");
    barrierPatrol->LoadImages("barrier_icon_dark.png", "barrier_icon_green.png", "barrier_icon.png", "barrier_icon.png");
    barrierPatrol->SetActive(true);
    barrierPatrol->SetOn(false);
    barrierPatrol->SetInteractive(true);
    barrierPatrol->SetCommand(BARRIER_PATROL);
    barrierPatrol->SetMouseOverCaption("BARRIER PATROL");
    barrierPatrol->SetMouseOverCaptionPosition(wxPoint(16, -10));
    barrierPatrol->SetShowCaptionWhenOn(false);
    barrierPatrol->SetFontSize(14.0f);

    buttonPos.x += 45;
    ferryMission = new tcButton(this, buttonPos, wxSize(32, 32), "FerryMission");
    ferryMission->LoadImages("airbase_icon_dark.png", "airbase_icon_green.png", "airbase_icon.png", "airbase_icon.png");
    ferryMission->SetActive(true);
    ferryMission->SetOn(false);
    ferryMission->SetInteractive(true);
    ferryMission->SetCommand(FERRY_MISSION);
    ferryMission->SetMouseOverCaption("FERRY");
    ferryMission->SetMouseOverCaptionPosition(wxPoint(16, -10));
    ferryMission->SetShowCaptionWhenOn(false);
    ferryMission->SetFontSize(14.0f);
    
    buttonPos.x += 45;
    strikeMission = new tcButton(this, buttonPos, wxSize(32, 32), "StrikeMission");
    strikeMission->LoadImages("crosshairs_dark.png", "crosshairs_green.png", "crosshairs.png", "crosshairs.png");
    strikeMission->SetActive(true);
    strikeMission->SetOn(false);
    strikeMission->SetInteractive(true);
    strikeMission->SetCommand(STRIKE_MISSION);
    strikeMission->SetMouseOverCaption("STRIKE");
    strikeMission->SetMouseOverCaptionPosition(wxPoint(16, -10));
    strikeMission->SetShowCaptionWhenOn(false);
    strikeMission->SetFontSize(14.0f);

    // add list box for selecting type of mission
    buttonPos.x += 58;
    missionTypeBox = new tcListBox(this, buttonPos, wxSize(120, 15));
    missionTypeBox->SetActive(true); // deactivate for now
    missionTypeBox->SetCommand(65);
    missionTypeBox->SetMaxShow(6);
    UpdateMissionTypeList();

}


void tcMissionGui::OnLButtonDown(wxMouseEvent& event)
{
    tcContainerGui::OnLButtonDown(event);

    if (missionSelectBox->GetShowList())
    {
        missionSelectBox->CloseList();
    }

    if (missionTypeBox->GetShowList())
    {
        missionTypeBox->CloseList();
    }
}

/**
*
*/
void tcMissionGui::OnLButtonDClick(wxMouseEvent& event)
{
	tcContainerGui::OnLButtonDClick(event);

	tcFlightPort* flightPort = GetFlightPort();
	if (flightPort == 0) return;

    wxPoint point = event.GetPosition();

    float x = (float)point.x;
    float y = (float)point.y;

	size_t nSlots = slots.size();

	for (size_t n=strikeOffset; n<nSlots; n++)
	{
		if (slots[n].loc.ContainsPoint(x, y))
		{
			//flightPort->Launch(n - launchOffset);
			return;
		}
	}
}

void tcMissionGui::OnMissionSelectCommand(wxCommandEvent& event)
{
    if (missionSelectBox == 0) return;

    int eventId = event.GetId();
    if (eventId != 55)
    {
        wxASSERT(false);
        return;
    }

    wxString missionIdText = event.GetString().c_str();

    missionSelectBox->SetCaption("");

    if (missionIdText == "NEW")
    {
        ai::tcMissionManager* missionManager = GetMissionManager();
        if (missionManager == 0) return;
		
        ai::tcAttackMission* attack = new ai::tcAttackMission();
		
		missionManager->AddMission(attack);

        unsigned int newMissionId = attack->GetId();
        
        wxString s;
        s.Printf("M%03d", newMissionId);
		missionSelectBox->AddItem(s.ToStdString());

        SetActiveMission(newMissionId);
        missionSelectBox->SelectItem(s.ToStdString());
        missionSelectBox->SetCaption(s.ToStdString());
    }
    else if (missionIdText == "DELETE")
    {
        ai::tcMissionManager* missionManager = GetMissionManager();
        if ((missionManager == 0) || (missionId == 0)) return;

        if (ai::tcMission* mission = missionManager->GetMission(missionId))
        {
            missionManager->DeleteMission(missionId);
           
            wxString s;
            s.Printf("M%03d", missionId);
            missionSelectBox->RemoveItem(s.ToStdString()); 
            
            missionId = 0;
        }
    }
    else
    {
        wxString s = missionIdText.AfterFirst('M');
        unsigned long val = 0;
        if (s.ToULong(&val, 10))
        {
            SetActiveMission(val);
            missionSelectBox->SelectItem(missionIdText.ToStdString());
            missionSelectBox->SetCaption(missionIdText.ToStdString());
        }
    }

}



void tcMissionGui::OnMissionTypeCommand(wxCommandEvent& event)
{
    if (missionTypeBox == 0) return;

    int eventId = event.GetId();
    if (eventId != 65)
    {
        wxASSERT(false);
        return;
    }

    std::vector<long> commandId;
    commandId.push_back(platformId);

   
    wxString missionTypeText = event.GetString().c_str();

    wxString args = wxString::Format(",%d,'%s'", missionId, missionTypeText.ToAscii());
    commandInterface->AddPythonCommandGeneral("SetMissionType", args.ToStdString(), commandId);

    // update mission in case type has changed
    args.Printf(",%d", missionId);
    commandInterface->AddPythonCommandGeneral("RebuildMission", args.ToStdString(), commandId);

}

void tcMissionGui::OnAreaPatrolCommand(wxCommandEvent& event)
{
    std::vector<long> commandId;
    commandId.push_back(platformId);
    commandInterface->GetUserInputForID("SetAreaPatrolMissionBox", "Box", commandId, missionId);
}


void tcMissionGui::OnBarrierPatrolCommand(wxCommandEvent& event)
{
    std::vector<long> commandId;
    commandId.push_back(platformId);
    commandInterface->GetUserInputForID("SetBarrierPatrolMission", "Line", commandId, missionId);
}


void tcMissionGui::OnFerryMissionCommand(wxCommandEvent& event)
{
    std::vector<long> commandId;
    commandId.push_back(platformId);
    commandInterface->GetUserInputForID("SetFerryMission", "Target", commandId, missionId);
}

void tcMissionGui::OnStrikeMissionCommand(wxCommandEvent& event)
{
    std::vector<long> commandId;
    commandId.push_back(platformId);
    commandInterface->GetUserInputForID("SetStrikeMission", "Target", commandId, missionId);
}

//void tcMissionGui::OnSetAreaCommand(wxCommandEvent& event)
//{
//    std::vector<long> commandId;
//    commandId.push_back(platformId);
//    commandInterface->GetUserInputForID("SetMissionPatrolArea", "Datum", commandId, missionId);
//}
//
//void tcMissionGui::OnSetDatumCommand(wxCommandEvent& event)
//{
//    std::vector<long> commandId;
//    commandId.push_back(platformId);
//    commandInterface->GetUserInputForID("SetMissionDatum", "Datum", commandId, missionId);
//}


void tcMissionGui::OnSetLandTargetCommand(wxCommandEvent& event)
{
    std::vector<long> commandId;
    commandId.push_back(platformId);
    commandInterface->GetUserInputForID("SetMissionLandingTarget", "Target", commandId, missionId);
}

/**
* Open a platform gui for the clicked entity
*/
void tcMissionGui::OnRButtonDown(wxMouseEvent& event)
{
	tcFlightPort* flightPort = GetFlightPort();
	if (flightPort == 0) return;

    wxPoint point = event.GetPosition();

    float x = (float)point.x;
    float y = (float)point.y;

	size_t nSlots = slots.size();

	for (size_t n=strikeOffset; n<nSlots; n++)
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
}

void tcMissionGui::OnStartTimeUpdate(wxCommandEvent& event)
{
    int eventId = event.GetId();
    if (eventId != 75)
    {
        wxASSERT(false);
        return;
    }

    ai::tcAttackMission* mission = dynamic_cast<ai::tcAttackMission*>(GetMission());
    if ((mission == 0) || (mission->IsLocked())) return;

    wxString startTimeText = event.GetString().c_str();

    if (!tcGameObject::IsClientMode())
    {
        mission->SetLaunchTimeFromString(startTimeText.c_str());
        timeEntry->SetBuffer(mission->GetLaunchTimeString());
    }
    else
    {
        wxString s = wxString::Format(",%d, %s", missionId, startTimeText.c_str());

        std::vector<long> commandId;
        commandId.push_back(platformId);
        commandInterface->AddPythonCommandGeneral("SetMissionLaunchTime", s.ToStdString(), commandId);
    }
}

void tcMissionGui::OnTimeEntryWheelDown(wxCommandEvent& event)
{
    IncrementMissionTime(-600.0f);
}

void tcMissionGui::OnTimeEntryWheelUp(wxCommandEvent& event)
{
    IncrementMissionTime(600.0f);
}

void tcMissionGui::IncrementMissionTime(float dt_s)
{   
    //timeEntry->SetBuffer(mission->GetLaunchTimeString());
    ai::tcAttackMission* mission = dynamic_cast<ai::tcAttackMission*>(GetMission());
    if ((mission == 0) || (mission->IsLocked())) return;

    tcDateTime launchTime = mission->GetLaunchTime();
    launchTime.AdjustTimeSeconds(dt_s);
    mission->SetLaunchTime(launchTime);

    if (!tcGameObject::IsClientMode())
    {
        timeEntry->SetBuffer(mission->GetLaunchTimeString());
    }
    else
    {
        wxString s = wxString::Format(",%d, %s", missionId,  mission->GetLaunchTimeString());

        std::vector<long> commandId;
        commandId.push_back(platformId);
        commandInterface->AddPythonCommandGeneral("SetMissionLaunchTime", s.ToStdString(), commandId);
    }
}



void tcMissionGui::OnWaveCountUpdate(wxCommandEvent& event)
{
    ai::tcAttackMission* mission = dynamic_cast<ai::tcAttackMission*>(GetMission());
    if ((mission == 0) || (mission->IsLocked())) return;

    unsigned int nWaveQuantity = unsigned int(floorf(waveQuantity));

    if (!tcGameObject::IsClientMode())
    {
        mission->SetWaveQuantity(nWaveQuantity);
    }
    else
    {
        wxString args = wxString::Format(",%d,%d", missionId, nWaveQuantity);

        std::vector<long> commandId;
        commandId.push_back(platformId);
        commandInterface->AddPythonCommandGeneral("SetMissionWaveQuantity", args.ToStdString(), commandId);
    }
}


void tcMissionGui::OpenPlatformGui(tcContainerItem* item)
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
    // this code is same as tcFlightPortGui::OpenPlatformGui, may want to elevate to base class
    std::vector<size_t> selectedIdx = GetSelected();
    if (selectedIdx.size() <= 1) return;

    bool selectionContainsPlatform = false; // check if group selection includes selected platform for platform GUI
    std::vector<long> groupId;
    for (size_t n=0; n<selectedIdx.size(); n++)
    {
        tcEntityContainerItem* entityItem_n = dynamic_cast<tcEntityContainerItem*>(slots[selectedIdx[n]].GetItem());
        tcPlatformObject* platform_n = (entityItem_n != 0) ? dynamic_cast<tcPlatformObject*>(entityItem_n->GetEntity()) : 0;

        if ((platform_n != 0) && (platform_n->mpDBObject == platform->mpDBObject))
        {
            groupId.push_back(platform_n->mnID);
        }

        if (platform_n == platform) selectionContainsPlatform = true;
    }
    if (!selectionContainsPlatform) return;


    gui->SetGroupPlatforms(groupId);

}

void tcMissionGui::ReadGuiParameters()
{
    TiXmlNode* root = config->FirstChild("Window");
    if (!root)
    {
        fprintf(stderr, "tcMissionGui::ReadGuiParameters - Missing top level <Window> tag\n");
        return;
    }

	TiXmlNode* current = root->FirstChild("Mission");
    if (!current)
    {
        fprintf(stderr, "tcMissionGui::ReadGuiParameters - Missing <Mission> tag\n");
        return;
    }
	
    TiXmlElement* elt = current->ToElement();    
    
    double slotSizeXml = 32.0;
    double strikeX = 0;
    double strikeY = 0;
    double strikeSpacing = 10.0;
    
    elt->Attribute("SlotSize", &slotSizeXml);

    elt->Attribute("StrikeX", &strikeX);
    elt->Attribute("StrikeY", &strikeY);
    elt->Attribute("StrikeSpacing", &strikeSpacing);

    slotSize = slotSizeXml;
    
    strikeLoc.x = strikeX;
    strikeLoc.y = strikeY;
    strikeHorizontalSpacing = strikeSpacing;
}

void tcMissionGui::SetActiveMission(unsigned int id)
{
    ai::tcMissionManager* missionManager = GetMissionManager();
    if (missionManager == 0) return;

    ai::tcMission* mission = missionManager->GetMission(id);
    if (mission != 0)
    {
        missionId = id;
        missionManager->SetEditMissionId(missionId);

        ai::tcAttackMission* attack = dynamic_cast<ai::tcAttackMission*>(mission);
        if (attack != 0)
        {
            timeEntry->SetBuffer(attack->GetLaunchTimeString());
        }
    }
    else
    {
        missionId = 0;
        missionSelectBox->SetCaption("");
        missionManager->SetEditMissionId(0);
    }
		
}


/**
* Update slot items based on flightPort state
*/
void tcMissionGui::UpdateGui()
{
    static unsigned int updateCount = 0;
    
    if ((updateCount++ & 0x000F) == 0x0001)
    {
        UpdateMissionList();
    }


    // mark all slots not updated
    for (size_t n=0; n<slots.size(); n++)
    {
        slots[n].SetUpdated(false);
    }

    tcFlightPort* flightPort = GetFlightPort();
    ai::tcMission* mission = GetMission();

    if ((mission != 0) && (flightPort != 0))
    {
        const std::vector<MissionAircraftInfo>& missionAircraft = mission->GetMissionAircraft();

        // iterate through mission aircraft, put all aircraft in strike slots regardless of "Strike" role 
        size_t nextStrikeIdx = strikeOffset;

        for (size_t n=0; n<missionAircraft.size(); n++)
        {
            int airStateIdx = flightPort->GetAirStateIdx(missionAircraft[n].id);
            tcAirState* airState = (airStateIdx != -1) ? flightPort->GetAirState(airStateIdx) : 0;

            if (nextStrikeIdx < slots.size())
            {
                tcContainerSlot& slot = slots[nextStrikeIdx];
                if (AddOrUpdateItem(slot, airState, missionAircraft[n].name))
                {
                    slots[nextStrikeIdx].SetUpdated(true);
                    slots[nextStrikeIdx].SetUseSmallIcon(true);
                    nextStrikeIdx++;
                }
            }

        }
        EnableMissionGraphics(true);
    }
    else
    {
        missionId = 0;
        missionSelectBox->SetCaption("");
        EnableMissionGraphics(false);
    }

	//// delete items that were not updated
	for (size_t n=0; n<slots.size(); n++)
	{
		if (!slots[n].IsUpdated())
		{
			slots[n].ClearItem();
		}
	}


    // update targeting graphics
    ai::tcAttackMission* attack = dynamic_cast<ai::tcAttackMission*>(mission);
    if (attack == 0) return;

    bool hasTarget = attack->HasTarget();
    strikeMission->SetOn(hasTarget);

    areaPatrol->SetOn(attack->GetArea().size() > 2);

    if ((updateCount & 0x000F) == 0x0001)
    {
        wxASSERT(timeEntry != 0);
        long dt_s = attack->GetSecondsToLaunch();
        if (dt_s <= 0)
        {
            timeEntry->SetCaption("MISSION START TIME (IN PROGRESS)");
        }
        else if (dt_s < 3600)
        {
            wxString s;
            long mm = dt_s / 60;
            long ss = dt_s - 60*mm;
            s.Printf("MISSION START TIME (-00:%02d:%02d)", mm, ss);
            timeEntry->SetCaption(s.c_str());
        }
        else if (dt_s < 99*3600)
        {
            wxString s;
            long hh = dt_s / 3600;
            dt_s -= hh*3600;
            long mm = dt_s / 60;
            long ss = dt_s - 60*mm;
            s.Printf("MISSION START TIME (-%02d:%02d:%02d)", hh, mm, ss);
            timeEntry->SetCaption(s.c_str());
        }
        else
        {
            timeEntry->SetCaption("MISSION START TIME");
        }

        if (!waveEdit->EditInProgress())
        {
            waveQuantity = float(attack->GetWaveQuantity());
        }

        missionTypeBox->SetCaption(attack->GetMissionType());


        
        //if (attack->GetLandingTarget().size() > 0)
        //{
        //    wxString s("CHANGE DEST (" );
        //    s += attack->GetLandingTarget().c_str();
        //    s += ")";
        //    
        //    landingDestination->SetMouseOverCaption(s.c_str());
        //}
        //else
        //{
        //    landingDestination->SetMouseOverCaption("SET DEST");
        //}

        if (!attack->IsLocked())
        {
            strikeMission->SetInteractive(true);
        }
        else
        {
            strikeMission->SetInteractive(false);
        }
    }
        
}

void tcMissionGui::UpdateMissionList()
{
    if (missionSelectBox->GetShowList()) return; // don't update while we're showing the list

    // save current caption so we can reload it after refreshing the listbox items
    std::string currentCaption = missionSelectBox->GetCaption();

    missionSelectBox->Clear();

    ai::tcMissionManager* missionManager = GetMissionManager();
    if (missionManager == 0) return;

    missionSelectBox->AddItem("NEW");
    missionSelectBox->AddItem("DELETE");

    wxString firstValidMission("");

    size_t nMissions = missionManager->GetMissionCount();
    for (size_t n=0; n<nMissions; n++)
    {
        ai::tcMission* mission = missionManager->GetMissionByIdx(n);
        wxASSERT(mission != 0);
        wxString s = wxString::Format("M%03d", mission->GetId());
        missionSelectBox->AddItem(s.ToStdString());

        if (n == 0) firstValidMission = s;
    }
    
    if (currentCaption.size() > 0)
    {
        missionSelectBox->SetCaption(currentCaption);
    }
    else if (firstValidMission.size() > 0)
    {
        missionSelectBox->SelectItem(firstValidMission.ToStdString());
        missionSelectBox->SetCaption(firstValidMission.ToStdString());
    }
}



void tcMissionGui::UpdateMissionTypeList()
{
    if (missionTypes.size() == 0)
    {
        wxTextFile inFile;
        inFile.Open("scripts\\mission_types.txt");
        if (!inFile.IsOpened())
        {
            wxASSERT(false); // missing mission_types.txt
            missionTypes.push_back("Default");
            missionTypes.push_back("ASW-Helo");
            missionTypes.push_back("ASW-FW");
            missionTypes.push_back("Standby-AAW");
            missionTypes.push_back("Standby-ASW");
            missionTypes.push_back("Standby-ASuW");
        }
        else
        {
            size_t nLines = inFile.GetLineCount();
            for (size_t n=0; n<nLines; n++)
            {
                wxString s = inFile.GetLine(n);
                s.Trim(true);
                s.Trim(false);
                if (s.size() > 0)
                {
                    missionTypes.push_back(s);
                }
            }
        }
    }

    missionTypeBox->Clear();
    missionTypeBox->AddItem("");
    for (size_t n=0; n<missionTypes.size(); n++)
    {
        missionTypeBox->AddItem(missionTypes[n].ToStdString());
    }

    

}

/**
*
*/
tcMissionGui::tcMissionGui(long id, unsigned int missionId_, const wxPoint& pos, 
     const wxString& configFile) 
     : tcContainerGui(pos, configFile, "MissionGui"), 
	   platformId(id),
       missionId(missionId_),
       missionSelectBox(0),
       missionTypeBox(0)
{
    Freeze();

    commandInterface = tcCommandQueue::Get();

    SetBackgroundColor(Vec4(0, 0, 0, 0.8f));

    ReadGuiParameters();

    InitializeGui();

	SetActive(true);

#ifdef _DEBUG
	fprintf(stdout, "tcMissionGui::tcMissionGui - %s, %d slots\n", configFile.c_str(),
		slots.size());
#endif

    Thaw();

}

tcMissionGui::~tcMissionGui() 
{
    ai::tcMissionManager* missionManager = GetMissionManager();

    if (missionManager != 0)
    {
        missionManager->SetEditMissionId(0);
    }
}


