/**  
**  @file tcMissionGui.h
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



#ifndef _TCMISSIONGUI_H_
#define _TCMISSIONGUI_H_

#if _MSC_VER > 1000
#pragma once
#endif 

#include "tcContainerGui.h"

class tcGameObject;
class tcAirState;
class tcFlightPort;
class tcListBox;
class tcEditBox;
class tcCommandQueue;
template <class T> class tcNumberWidget;

namespace ai
{
    class tcMission;
    class tcMissionManager;
}

/**
* GUI class for mission editing (drag aircraft from flightport to mission)
*/
class tcMissionGui : public tcContainerGui
{
public:
    static tcMissionGui* GetExistingGui(long id);

    long GetPlatformId() const;

    virtual void Draw();

    virtual void OnLButtonDown(wxMouseEvent& event);
	virtual void OnLButtonDClick(wxMouseEvent& event);
    virtual void OnRButtonDown(wxMouseEvent& event);
  

    tcMissionGui(long id, unsigned int missionId_, const wxPoint& pos, 
		const wxString& configFile);

    virtual ~tcMissionGui();
protected:
    virtual void HandleDrop(size_t slotIdx, const std::vector<tcContainerItem*>& items);
    virtual void HandleDropWindow(const std::vector<tcContainerItem*>& items);
private:
    static tcCommandQueue* commandInterface;
    enum {STRIKE_SPOTS=24, AREA_PATROL=1000, BARRIER_PATROL=1001, FERRY_MISSION=1002, STRIKE_MISSION=1003, SET_LANDTARGET=1004};
	const long platformId; ///< id of platform that holds flightport
    unsigned int missionId; ///< id of active mission being edited

    size_t strikeOffset; ///< slot index of first strike spot (normally 0)
    
    float slotSize; ///< dimension of (square) slot
   
    wxRealPoint strikeLoc; ///< upper-left of first launch spot
    float strikeHorizontalSpacing;

    tcListBox* missionSelectBox;
    tcListBox* missionTypeBox; // for selecting type of mission
    tcEditBox* timeEntry; // start time for mission
    tcNumberWidget<float>* waveEdit; ///< number of aircraft to launch in each wave (default to all)
    float waveQuantity;

    tcButton* areaPatrol; // button to create/clear area patrol mission
    tcButton* barrierPatrol; // button to create/clear barrier patrol mission
    tcButton* ferryMission; // button to create ferry mission
    tcButton* strikeMission; // button to create strike mission

    static wxArrayString missionTypes; ///< list of mission type strings

    bool AddOrUpdateItem(tcContainerSlot& slot, tcAirState* airState, const std::string& unitName);
	void CloseAllPlatformGuis();
	tcFlightPort* GetFlightPort();
    void InitializeGui();

    ai::tcMission* GetMission();
    ai::tcMissionManager* GetMissionManager();

	void OpenPlatformGui(tcContainerItem* item);
    void ReadGuiParameters();
    void UpdateGui();
    void OnMissionSelectCommand(wxCommandEvent& event);
    void OnMissionTypeCommand(wxCommandEvent& event);
    void OnStartTimeUpdate(wxCommandEvent& event);

    void OnAreaPatrolCommand(wxCommandEvent& event);
    void OnBarrierPatrolCommand(wxCommandEvent& event);
    void OnFerryMissionCommand(wxCommandEvent& event);
    void OnStrikeMissionCommand(wxCommandEvent& event);
    void OnSetLandTargetCommand(wxCommandEvent& event);

    void OnTimeEntryWheelDown(wxCommandEvent& event);
    void OnTimeEntryWheelUp(wxCommandEvent& event);
    void OnWaveCountUpdate(wxCommandEvent& event);
    void IncrementMissionTime(float dt_s);

    void UpdateMissionList();
    void UpdateMissionTypeList();

    void SetActiveMission(unsigned int id);
    void EnableMissionGraphics(bool state);

    DECLARE_EVENT_TABLE()
};

#endif

