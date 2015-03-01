/**  
**  @file tcPlatformGui.h
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



#ifndef _TCPLATFORMGUI_H_
#define _TCPLATFORMGUI_H_

#if _MSC_VER > 1000
#pragma once
#endif 

#include "tcContainerGui.h"
#include <boost/shared_ptr.hpp>

class tcGeometry;


namespace database
{
    class tcDatabaseObject;
};
using database::tcDatabaseObject;

class tcPlatformObject;
class tcFlightOpsObject;
class tcLauncher;
class tcStoresContainerItem;
class tcStores;
class tcListBox;

/**
* GUI class for platform operations
* Functions:
*     Open magazine and flightport guis
*     Support drag between launchers and magazines (load/unload launchers)
*/
class tcPlatformGui : public tcContainerGui
{
public:
    static tcPlatformGui* GetExistingGui(long id, long host);

    virtual void Draw();

    long GetPlatformId() const;
    long GetHostId() const;
    void GetPlatformList(std::vector<tcPlatformObject*>& platformList);

    //virtual void OnChar(wxKeyEvent& event);
    //virtual void OnEnterWindow(wxMouseEvent& event);
    //virtual void OnLButtonDown(wxMouseEvent& event);
    //virtual void OnLButtonUp(wxMouseEvent& event);
    //virtual void OnLeaveWindow(wxMouseEvent& event);
	//virtual void OnMouseMove(wxMouseEvent& event);
    virtual void OnLButtonDClick(wxMouseEvent& event);
    virtual void OnRButtonDown(wxMouseEvent& event);

    void SetGroupPlatforms(const std::vector<long>& groupId_); // for group mode editing
	void UpdateLoadoutList();

    tcPlatformGui(long id, long host, const wxPoint& pos, 
		const wxString& configFile);

    virtual ~tcPlatformGui();	


private:
	const long platformId;
	const long hostId; ///< -1 for none, or id of parent that is holding this platform, e.g. flightport
    std::vector<long> groupId;

    boost::shared_ptr<tcGeometry> magazineIcon;
    boost::shared_ptr<tcGeometry> flightPortIcon;
	boost::shared_ptr<tcGeometry> fuelIcon;
    tcListBox* loadoutBox;

    size_t nLaunchers; ///< number of launchers (first idx = 0)
    size_t magazineIdx; ///< slot index of first magazine slot
    size_t nMagazines; ///< number of magazines
    size_t flightPortIdx; ///< slot index of first flightport
    size_t nFlightPorts; ///< number of flightports (normally 0 or 1)
	size_t fuelIdx; ///< slot index of fuel slot

    float slotSize; ///< dimension of (square) slot
    wxRealPoint launcherLoc; ///< upper-left of first launcher
    wxRealPoint launcherOffset; ///< (x, y) offset between launchers
    wxRealPoint magazineLoc; ///< upper-left of first magazine
    wxRealPoint magazineOffset; ///< (x, y) offset between magazines
    wxRealPoint flightPortLoc; ///< upper-left of flightport
	wxRealPoint fuelLoc; ///< upper-left of fuel icon
    
    
    void AddOrUpdateLauncherItem(tcContainerSlot& slot, tcDatabaseObject* child,
             tcLauncher* launcher, unsigned int launcherIdx, unsigned int quantity);
	int GetLauncherCompatibilityCaption(unsigned int launcherIdx, wxString& caption, tcPlatformObject* platform);
	tcFlightOpsObject* GetFlightOps();
	tcPlatformObject* GetPlatform();

	void HandleDrop(size_t slotIdx, const std::vector<tcContainerItem*>& items);
	void HandleFuelDrop(tcStoresContainerItem* item);
    void InitializeGui();
	void OpenFlightPortGui(tcContainerItem* item);
	void OpenMagazineGui(unsigned int idx, tcContainerItem* item);
    void ReadGuiParameters();
    void UpdateGui();

	void OnLoadoutCommand(wxCommandEvent& event);
	tcStores* GetLoadoutStores();

    void UpdateCustomLoadout();

    DECLARE_EVENT_TABLE()
};

#endif

