/**  
**	@file tcOOBView.h
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

#ifndef _OOBVIEW_H_
#define _OOBVIEW_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "wx/wx.h" 

#include "tcXmlWindow.h"
#include "tcPool.h"
#include "tcDatabase.h"

#define MAX_FOLLOWERS 16
#define MAX_OOB_OBJECTS 512


class tcTacticalMapView;

class tcSimState;
class tcScrollBar;

using namespace database;

struct tsOOBInfo
{
    long mnID;
    tcDBString mzName;
    long mnLeaderID;
    std::vector<unsigned> maFollowers;
    bool isLeader;
    bool mbRadiating;
    bool isTasked; ///< to identify units without "orders"
    float mfDamage_fract; ///< damage over toughness
    std::string mzAction;
    tcRect rectf;  ///< draw location (without offset for current scroll)
    tcRect rleader; ///< location for leader icon
    tcRect remcon; ///< location for EMCON icon
    tcRect rdamage; ///< location for damage indicator
    tcRect raction; ///< loc for action string

    tsOOBInfo& operator= (const tsOOBInfo& rhs);
};

/**
* Provides view and interface for OOB (Order Of Battle)
*  - List of all assets under control
*  - Status indication (rad, dmg)
*  - Formation indication (tree view possibly)
* weapons are not displayed
*
* All of the code in this section is out of date and needs refactoring
*/
class tcOOBView : public tcXmlWindow 
{
public:
    struct CategoryInfo
    {
        std::vector<tsOOBInfo>* category;
        std::string caption;
        tcRect toggleIcon;
        bool isActive; ///< state of toggleIcon
    };

    tcSimState* mpSimState; ///< for retrieving platform info
    tcTacticalMapView *mpMapView;

    // own alliance
    std::vector<tsOOBInfo> surfaceObj;
    std::vector<tsOOBInfo> airObj;
	std::vector<tsOOBInfo> carrierObj; ///< carriers
    std::vector<tsOOBInfo> flightopsObj; ///< airfields
    std::vector<tsOOBInfo> heloObj;
    std::vector<tsOOBInfo> subObj;
    std::vector<tsOOBInfo> groundObj; ///< other ground forces

    // tracks
    std::vector<tsOOBInfo> surfaceTracks;
    std::vector<tsOOBInfo> subTracks;
    std::vector<tsOOBInfo> airTracks;
    std::vector<tsOOBInfo> missileTracks;
    std::vector<tsOOBInfo> unknownTracks;

    std::vector<CategoryInfo> ownCategories;
    std::vector<CategoryInfo> trackCategories;

    long mnSelectedKey;
    struct  
    {
        bool mbApply;
        long mnFollowerKey;
        long mnNewLeaderKey;
    } msFormationChangeInfo;

    void AttachMapView(tcTacticalMapView *apMapView) {mpMapView = apMapView;}
    void Update();
    void Draw();
    void OnLButtonDown(wxMouseEvent& event);
    void OnLButtonDClick(wxMouseEvent& event);
    void OnLButtonUp(wxMouseEvent& event);
    void OnLeaveWindow(wxMouseEvent& event);
    void OnMouseMove(wxMouseEvent& event);
	void OnScrollbarUpdated(wxCommandEvent& event);
    void SetDisplayOwn(wxCommandEvent& event); 
    void SetDisplayTrack(wxCommandEvent& event); 
    void SetIPText(wxCommandEvent& event);

    void SetHookID(long id) {mnSelectedKey = id;}

    tcOOBView(wxWindow *parent, 
        const wxPoint& pos, const wxSize& size, 
        const wxString& name = "OOBView",
		tc3DWindow2* graphicsHost = 0);
    ~tcOOBView();   

private:
    /** * */
    enum DisplayMode
    {
        SHOW_OWN = 0,
        SHOW_TRACKS = 1
    };
    bool mbMouseDrag;
    float mfRowSpacing;
    float mfYOffset; ///< offset for Y coord of first item
    float mfXOffset;
    float mfXIndent; ///< indent for formations
    float maxNameWidth;
    int displayMode;
    
    long objKeys[MAX_OOB_OBJECTS];
    boost::shared_ptr<tcTexture2D> leaderIcon; ///< for formation leader
    boost::shared_ptr<tcTexture2D> hideIcon; ///< for category show/hide
    boost::shared_ptr<tcTexture2D> showIcon; ///< for category show/hide

    tcScrollBar* scrollBar;
    float yOffset; // scroll bar offset parameter

    tsOOBInfo* ButtonContainingPoint(wxRealPoint pointf);
    tsOOBInfo* ButtonContainingPointCategory(wxRealPoint pointf, 
        std::vector<tsOOBInfo>& objInfo);
    bool CategoryShowHideClick(wxRealPoint p);

    void BuildCategoryInfo();

    void DrawCategory(std::vector<tsOOBInfo>& objInfo, float stopy);
    void DrawOwn();
    void DrawTracks();

    float GetCategoryY(std::vector<tsOOBInfo>& objInfo);
    void PlaceIcons();
    void PlaceIconsCategory(std::vector<tsOOBInfo>& objInfo);
    void UpdateData();
    void UpdateTrackData();
    void UpdateFormation();
    void UpdateRect(float yStart);
    void UpdateRectCategory(std::vector<tsOOBInfo>& objInfo, float& y, float stopy);

    DECLARE_EVENT_TABLE()
};






#endif



