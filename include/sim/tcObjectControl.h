/**  
**  @file tcObjectControl.h
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

#ifndef _OBJECTCONTROL_H_
#define _OBJECTCONTROL_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "wx/wx.h" 
#include "tc3DWindow2.h"
#include "commandlist.h"
#include "aerror.h"
#include "simmath.h"
#include "tcString.h"
#include "tcPool.h"
#include "tcAIPanel.h"
#include <string>



class tcSimState;
class tcOptions;
class tcUserInfo;
class tcGameObject;
class tcPlatformObject;
class tcControl;
class tcCommandQueue;
class tcPopupText;
class tcGeometry;
class tcUnits;
class tcButton;
class tcLauncher;

namespace database
{
    class tcDatabaseObject;
}

namespace ai
{
    class Brain;
}

using ai::Brain;
using database::tcDatabaseObject;


struct tsHeadingObjectInfo 
{
    bool mbMouseOver;
    float mfMouseHeading_rad;
    tcRect mrectArc;
    float mfxcenter;
    float mfycenter;
    float mfradius;
    bool canSetHeading; ///< true if heading can be changed by player
};

struct tsBarObjectInfo
{
    bool mbMouseOver;
    bool mbVertical;
    tcRect mrectcontrol; ///< control area
    tcRect mrectbar;
    float mfmaxvalue;
    float mfminvalue;
    float mfmousevalue;
    float xMouse; ///< position of mouse cursor if mbMouseOver
    std::string overText; ///< current value and units of mouse over position
};

enum teButtonState
{
    BS_DAMAGED, ///< damaged
    BS_DISABLED, ///< out of ammo
    BS_READYING, ///< items loaded, launcher readying
    BS_READY, ///< ready for immediate launch
    BS_ACTIVE, ///<  active but launch conditions not satisfied yet
    BS_LOADING, ///< loading item(s) into launcher
    BS_WARN, ///< used to indicate jamming or warning condition
    BS_RWRWARN1,
    BS_RWRWARN2
};


class tcButtonPanel 
{
public:
    enum
    {
        MAX_PANELROWS = 32,
        MAX_ROWS_PER_PAGE = 8, /// number of rows to display at once
        N_PANELBUTTONS = 8
    };

    float mfxloc, mfyloc; // upper-left coords
    float panely; // value to adjust margin between top of panels and top of window

    tcString mstrTitle;
    tcString mastrCaption[MAX_PANELROWS][N_PANELBUTTONS];
    tcRect mar[MAX_PANELROWS][N_PANELBUTTONS];
    teButtonState maButtonState[MAX_PANELROWS][N_PANELBUTTONS];
    float fontSize;
	int mouseOverRow, mouseOverColumn;

    void Init(int anPanelType);
    void Draw(tc3DWindow2* context);
    void DrawButton(tc3DWindow2* context, const tcRect& rectf, 
        const char* azCaption, teButtonState aeState, bool isMouseOver);
    void DrawPageSelect(tc3DWindow2* context);

    bool ButtonContainingPoint(const wxPoint& point, int& rnRow, int& rnColumn);
    void GetRect(tcRect& r);
    void SetCaption(const char *caption, unsigned row, unsigned button);
    void SetCaptionB(tc3DWindow2* context, const char *caption, unsigned row, unsigned button);
    void SetNumCols(size_t n);
    void SetNumRows(size_t n);
    void SetPage(unsigned int page);
    void UpdatePageSelect(const wxPoint& point);
	void SetMouseOver(int row, int column);

    tcButtonPanel();
    ~tcButtonPanel();
private:
    unsigned int mnRows, mnColumns;
    unsigned int currentPage;
	
    size_t nPages;
    std::vector<tcRect> pageSelectBoxes;

};


/**
* For drawing range circles for weapons and sensors on map
*/
struct MapSymbolInfo
{
	double mfLat_rad;
	double mfLon_rad;
	double mfLat2_rad; ///< for drawing lines
	double mfLon2_rad; ///< for drawing lines
	float mfLatExtent_rad;
	float mfLonExtent_rad;
	float mfArcCenter_deg;
	float mfArcLength_deg;
	UINT32 mnColor;
};


/**
* Old code, needs refactoring
* Second that, really needs it!
*/
class tcObjectControl : public tc3DWindow2
{
public:   
    void Draw();
    void DrawTest();
    void AttachUserInfo(tcUserInfo *apUserInfo) {mpUserInfo=apUserInfo;}
    bool ButtonContainingPoint(wxPoint point, int& rnRow, int& rnColumn);
	const std::vector<MapSymbolInfo>& GetMapSymbols() const;
	void OnEnterWindow(wxMouseEvent& event);
	void OnLeaveWindow(wxMouseEvent& event);
    void OnLButtonDown(wxMouseEvent& event);
    void OnMouseMove(wxMouseEvent& event);
    void SetActive(bool abActive);
    bool ProcessWeaponPanelButton(int anLauncher, int anButton);
    bool ProcessSensorPanelButton(int anSensor, int anButton);
    void SetHookID(long id);
    void SetHookIDgroup(long id);
    void SetHookID(const std::vector<long>& id);
    void UpdateSymbolList();

    tcObjectControl(wxWindow *parent, 
        const wxPoint& pos, const wxSize& size, 
        const wxString& name = "ObjectControl",
		tc3DWindow2* graphicsHost = 0);
    virtual ~tcObjectControl();	
private:   
    tcGameObject *mpHookedGameObj;
    tcSimState* simState;  ///< pointer to SimState object to access hook info, change this
    ///< to a UserSimState reference when ready (state as known by user's side)
    tcOptions *mpOptions;
    tcCommandQueue *mpCommandInterface;
    tcUserInfo *mpUserInfo; ///< info on which alliance user belongs to for truth view/control
    tcUnits* units;
    
    long mnHookID;
    long mnPreviousHookID;
    std::vector<long> hookedGroup; ///< ids of group that is currently hooked for cycling through
    tcButton* cycleHookLeft; ///< for cycling through group members
    tcButton* cycleHookRight;


    tcButtonPanel mcWeaponPanel; 
    tcButtonPanel mcSensorPanel; 
    tcAIPanel mcAIPanel;
    tsHeadingObjectInfo msHOI;
    tsBarObjectInfo msSOI; ///< speed object info
    int mnLaunchers;
    int mnSensors;
	std::vector<MapSymbolInfo> symbolList;
    boost::shared_ptr<tcGeometry> headingCircle;
    boost::shared_ptr<tcGeometry> headingCircleLight;
    boost::shared_ptr<tcTexture2D> leaderFlag; ///< for formation leader
    boost::shared_ptr<tcTexture2D> followerFlag; ///< for formation follower
    tcRect countryFlagRect; ///< to detect mouse over country flag
    tcRect formationFlagRect; ///< to detect mouse click on formation flag
    float panely;

    std::vector<tcControl*> controls;
    tcControl* altitudeControl;
	bool isMouseOver; ///< true if mouse is over window
	wxPoint lastMousePos; ///< last mouse position
	unsigned int lastMoveTime; ///< tcTime time of last mouse move (for timing "tooltip" popup)
	bool hintActive; ///< true to display hint text
	std::string hintText; ///< text to display for popup "tooltip" hint
	const unsigned int hintDelay; ///< time in 30Hz tics to wait to popup hint
	tcPopupText* popupHint;
	std::vector<int> rowToSensor;
	bool isRowToSensorUpdated; ///< true if rowToSensor is valid and doesn't need to be recalculated
    std::vector<float> launcherRange_km;
    std::vector<unsigned int> launcherColor;
    unsigned int lastWeaponRangeUpdate;
    float lastWeaponRangeSpeed_kts;
    float lastWeaponRangeAltitude_m;

    void AddSensorRangeCircles();
    void AddWeaponRangeCircles();
    void AddFlightRangeCircle();
    void AddTrackHistory();

    void CreateHeadingCircles();
    void DrawBarObject(tsBarObjectInfo *apBOI, float afValue, float afValueGoal, float redLineValue);
    void DrawButton(const tcRect& rectf, 
        char* azCaption, teButtonState aeState);
    void DrawControls();
    void DrawEngagementInfo();
    void DrawFireControl();
    void DrawFuelInfo();
    void DrawHeadingObject(tsHeadingObjectInfo *apHOI, 
        float afHeading_rad, float afHeadingGoal_rad);
    void DrawLandingInfo();
    void DrawSensorControl();

	int GetSensorIndexForRow(unsigned int row);
    void InitControls();
    void SetControlGameObject(tcGameObject* obj);
    void UpdateControlObjects();
	void UpdateHint();
    void UpdateWeaponRanges(tcPlatformObject* platform);
    
    void GetObjectInfo(tcString& s, tcDatabaseObject *apDBObject, tcGameObject *apGameObject);
    void InitializeGroupButtons();

	void OnCycleGroupLeftCommand(wxCommandEvent& event);
	void OnCycleGroupRightCommand(wxCommandEvent& event);
    void CycleGroupHook(bool forward);
    void SetShowCycleGroupButtons(bool state);

    void HandoffDatumToLauncher(tcLauncher* launcher, int launcherIdx);

	DECLARE_EVENT_TABLE()
};

#endif
