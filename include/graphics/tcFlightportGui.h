/**  
**  @file tcFlightPortGui.h
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



#ifndef _TCFLIGHTPORTGUI_H_
#define _TCFLIGHTPORTGUI_H_

#if _MSC_VER > 1000
#pragma once
#endif 

#include "tcContainerGui.h"

class tcGameObject;


class tcAirState;
class tcFlightPort;

/**
* GUI class for flightport operations
*/
class tcFlightPortGui : public tcContainerGui
{
public:
    static tcFlightPortGui* GetExistingGui(long id);

    long GetPlatformId() const;

    virtual void Draw();

    virtual void OnChar(wxKeyEvent& event);
    //virtual void OnEnterWindow(wxMouseEvent& event);
    //virtual void OnLButtonDown(wxMouseEvent& event);
    //virtual void OnLButtonUp(wxMouseEvent& event);
    //virtual void OnLeaveWindow(wxMouseEvent& event);
	//virtual void OnMouseMove(wxMouseEvent& event);
	virtual void OnLButtonDClick(wxMouseEvent& event);
    virtual void OnRButtonDown(wxMouseEvent& event);


    tcFlightPortGui(long id, const wxPoint& pos, 
		const wxString& configFile);

    virtual ~tcFlightPortGui();
protected:
    virtual void HandleDrop(size_t slotIdx, const std::vector<tcContainerItem*>& items);
    
private:
	const long platformId; ///< id of platform that holds flightport

    size_t launchOffset; ///< slot index of first launch spot (normally 0)
    size_t readyOffset; ///< slot index of first ready spot
    size_t hangarOffset; ///< slot index of first hangar spot
    size_t magazineIdx; ///< slot index of first magazine slot
    size_t nMagazines; ///< number of magazines
    size_t missionIdx; ///< slot index of mission plan slot

    float slotSize; ///< dimension of (square) slot
    float hangarSlotSize; ///< for hangar slots
    wxRealPoint launchLoc; ///< upper-left of first launch spot
    float launchHorizontalSpacing;
    wxRealPoint readyLoc;
    float readyHorizontalSpacing;
    wxRealPoint hangarLoc;
    float hangarHorizontalSpacing;
    float hangarVerticalSpacing; ///< spacing between rows
    unsigned int hangarRowSize; ///< number of hangar spots across
    bool useSmallHangarSlots;
    wxRealPoint magazineLoc; ///< upper-left of first magazine
    wxRealPoint magazineOffset; ///< (x, y) offset between magazines
    boost::shared_ptr<tcGeometry> magazineIcon;
    boost::shared_ptr<tcGeometry> missionIcon;

    void AddOrUpdateItem(tcContainerSlot& slot, tcAirState* airState);
	void CloseAllPlatformGuis();
	tcFlightPort* GetFlightPort();
    void InitializeGui();
    void OpenMagazineGui(unsigned int idx, tcContainerItem* item);
    void OpenMissionGui(tcContainerItem* item);
	void OpenPlatformGui(tcContainerItem* item);
    void ReadGuiParameters();
    void UpdateGui();

    void DeleteFromMouseOverSlot();
};

#endif

