/**  
**  @file tcTacticalMapView.h
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


#ifndef _TACTICALMAPVIEW_H_
#define _TACTICALMAPVIEW_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "wx/wx.h" 

#include "tcMapView.h"

class tcButton;
class tcWorldMapView;
class tcWaypointPopup;

#define GAMEMODE_NORMAL 0
#define GAMEMODE_PAUSED 1
#define GAMEMODE_EDIT 2

/**
* Tactical (theater) map with color elevation map
*/
class tcTacticalMapView  : public tcMapView 
{
public:
    friend class tcGameSerializer;

    struct NavPointInfo
    {
        GeoPoint geo;
        tcPoint screen;
        wxArrayString tasks;
        unsigned char referenceMode;
    };
	enum ROEMode
    {
        WEAPONS_HOLD = 0,
        WEAPONS_TIGHT = 1,
        WEAPONS_FREE = 2,
        ROE_ERROR = 99
    };

	tcMapObj maMapObj[MAXMAPOBJ];

	UINT32 mnObjCount;

	int mnCounter;
	int mnGameMode;
	int trackInfoMode; ///< 0 - none, 1 - id only, 2 - id and speed tag
    int drawNavPointsMode; ///< 0 - hooked only, 1 - all friendly platforms
	float mfFrameRate;

	// auto-scroll params
	bool scrollActive;
	unsigned int lastScrollTime;
	float scrollDirection;

	std::vector<long> hookedId; ///< vector of hooked obj ids

	UINT mnHookAlliance;
	float mfHookLon,mfHookLat;
	int mbMapCmdActive;
	teMapCmdType meMapCmd;
	wxPoint mpointMouse; ///< current location of mouse cursor
	tcPoint mpointGeoDatum; ///< for MC_DATUM map command to store user-selected location
    tcPoint mpointGeoDatum2; ///< for MC_BOX and MC_LINE map commands
    wxPoint mapCommandStartLocation; ///< for MC_RANGE map command, initial position of mouse
	float mfMapCmdHeading;
	long mnMapCmdTarget;
	char mzMapCmdCallback[128];
	int callbackParam;
	std::string callbackTextParam;
	std::vector<long> callbackPlatformID; ///< platform ID vector for callback

    void UpdateNavPointsPrimary(const std::vector<NavPointInfo>& navPoints, 
        int current, long platformId, long missionId);

    void UpdateNavPointsOther(const std::vector<std::vector<NavPointInfo>>& navPoints);

    void SetNavPointEditLock(bool state);

	/// returns id of closest unit to <pscreen> within fixed dist or -1 if none
	long GetClosest(const wxPoint& pscreen) const; 

	void GetMapCmdDatum(tcPoint& p) {p=mpointGeoDatum;}
    void GetMapCmdDatum2(tcPoint& p) {p=mpointGeoDatum2;}
	float GetMapCmdHeading() {return mfMapCmdHeading;}
	long GetMapCmdTarget() {return mnMapCmdTarget;}


	void SetMapCmdCallback(const char *azCallback, const std::vector<long>& id, int param, 
		const std::string& textParam);
	void SetMousePoint(wxPoint point) {mpointMouse = point;} // used to be TranslatePoint(point);
	void SetView(tcPoint center, float afLonSpan);
	void ScrollMap(float afDirection_deg);
	void CancelScroll();
	void ClearHook();
	void Draw();
	void DrawGrid();
	void DrawScaleBar();
	void DrawSelectionBox();
	void DrawTerrainText();
	void DrawTime();
	void DrawMapCmd(tcMapObj *pMO, teMapCmdType type);
    void DrawMapCmdRange();
	void DrawNavPoints();
    void DrawNavPointsOther();
	void DrawIndicator(int anType);
	void DrawSpecial();
    void DrawGameSpeed();

	size_t GetHookCount();
	std::vector<long>& GetHookedGroup();
	long GetHookID(size_t idx = 0);
	tcMapOverlay* GetMapOverlay() const;
	long Hook(wxPoint pscreen);
	void HookAnother(wxPoint pscreen);
	void HookGroup(const wxRect& region);
	long HookSecondary(wxPoint pscreen);
    void CycleHook(bool cycleEast);

	bool IsFirstHook(long id);
	bool IsHooked(long id);
	bool IsMapCmdActive() const;
	virtual void OnChar(wxKeyEvent& event);
	virtual void OnLeaveWindow(wxMouseEvent& event);
	virtual void OnLButtonDown(wxMouseEvent& event);
	virtual void OnLButtonDClick(wxMouseEvent& event);
	virtual void OnLButtonUp(wxMouseEvent& event);
	virtual void OnLButtonDownMapCmd(const wxPoint& point);
    virtual void OnLButtonUpMapCmd(const wxPoint& point);
	virtual void OnMButtonDown(wxMouseEvent& event);
	virtual void OnMButtonUp(wxMouseEvent& event);
	virtual void OnMouseMove(wxMouseEvent& event);
	virtual void OnMouseWheel(wxMouseEvent& event);
	virtual void OnRButtonDown(wxMouseEvent& event);
	virtual void OnSize(wxSizeEvent& event);
	virtual void OnShow3DCommand(wxCommandEvent& event);
	virtual void OnDecelerateTimeCommand(wxCommandEvent& event);
	virtual void OnPauseTimeCommand(wxCommandEvent& event);
	virtual void OnAccelerateTimeCommand(wxCommandEvent& event);
    virtual void OnHookViewCommand(wxCommandEvent& event);
    virtual void OnMouseCaptureLost(wxMouseCaptureLostEvent& event);
	virtual void OnSaveGameCommand(wxCommandEvent& event);
    void OnChangeSidesCommand(wxCommandEvent& event);
    void OnReloadGameCommand(wxCommandEvent& event);

	void OnAirROE(wxCommandEvent& event);
	void OnSurfROE(wxCommandEvent& event);
	void OnSubROE(wxCommandEvent& event);
	void OnLandROE(wxCommandEvent& event);

	void Refresh();
	void UpdateMapObjectColors();
	void ActivateMapCommand(teMapCmdType aeCmd);
	void DeactivateMapCommand();
	void ClearMapObjects();
	void Init();
	void SetActive(bool abActive); ///< overrides base class
	void SetBaseRenderBin(int n);
	void SetDateTime(const std::string& s) {dateTime = s;}
	void SetHookID(long id);
	bool GetShowFrameCounter() const;
	void SetShowFrameCounter(bool state); 
	void SetGroupHook(std::vector<long>& hookedUnits);
	void SetTextLeftMargin(float x);
	void ToggleShowTrackTags();
	void UpdateEdgeScroll(const wxPoint& pos);
	void UpdateViewBounds() {mpMapData->GetTheaterArea(mrectViewBounds);}

    bool GetCenterViewOnHooked() const;
    void SetCenterViewOnHooked(bool state);

    void SetFormationEditId(long id);
	long GetFormationEditId() const;
    void UpdateFormationGraphics();

    void SetMissionEditId(long id);
	long GetMissionEditId() const;

    void UpdatePatrolAreaGraphics();

    void UpdateDetailedEditPointIndex(int updatedIdx);

    void SetWorldMap(tcWorldMapView* map);

	void UpdateROEButtons();

	tcTacticalMapView(wxWindow *parent, 
		const wxPoint& pos, const wxSize& size, 
		tc3DWindow2* graphicsHost,
		const wxString& name = "TacticalMapView");
	virtual ~tcTacticalMapView();

private:
	enum {AIR_ROE_COMMAND = 240, SURF_ROE_COMMAND = 241, SUB_ROE_COMMAND = 242, LAND_ROE_COMMAND = 243,
	      SAVE_GAME = 444, REVERT = 445, CHANGE_SIDES = 446};
	tcMapOverlay* overlay;
    tcUnits* units;
    tcWorldMapView* worldMap;

	std::string dateTime; ///< string with complete date/time
	WCHAR mzwchar[255]; 

    std::vector<NavPointInfo> navPointsPrimary; ///< used to show/edit waypoint info for hooked platform
    std::vector<std::vector<NavPointInfo>> navPointsOther; ///< used to show waypoint info for other units
    long navPointsPlatformId; ///< platform id of current set of points
    long navPointsMissionId; ///< mission id of current set of points (-1 if not mission route)
    int currentPointIdx; ///< index of current point (next destination)
	int editPointIdx; ///< -1 if no point being edited, otherwise idx of edit point (nav waypoints)
    int insertPointEditIdx; ///< index of waypoint to insert before
    int detailedEditPointIdx; ///< -1 if no detailed edit, otherwise idx of edit point
    tcWaypointPopup* waypointEditor;
    long waypointEditorKey; ///< for checking if editor still exists before accessing pointer
    bool navPointEditLock; ///< true to block editing of nav points

    bool centerViewOnHooked;
    bool autoScrollTheater; ///< true to automatically change theater
    bool enableEdgeScrolling; ///< true to enable automatic scrolling when cursor at edge of screen

    long formationEditLeaderId; ///< id of formation leader
    long leaderFormationObject; ///< tcMapObject id of graphics obj for leader
    long followerFormationObject; ///< tcMapObject id of graphics obj for follower
    long patrolAreaObject; ///< tcMapObject id of patrol area obj
    long datumEditObject; ///< tcMapObject id of datum edit obj

    long missionEditId; ///< id of mission edit object
    std::vector<long> missionBoxObjects;

	boost::shared_ptr<tcGeometry> maSymbolA[4][MAX_SYMBOL];
	boost::shared_ptr<tcGeometry> maSymbolB[4][MAX_SYMBOL];

	/// faded versions for stale tracks
	boost::shared_ptr<tcGeometry> maSymbolA_fade[4][MAX_SYMBOL];
	boost::shared_ptr<tcGeometry> maSymbolB_fade[4][MAX_SYMBOL];

	/// altered versions of symbols (e.g. objects not under control of player)
	boost::shared_ptr<tcGeometry> maSymbolA_alt[4][MAX_SYMBOL];
	boost::shared_ptr<tcGeometry> maSymbolB_alt[4][MAX_SYMBOL];

	teSymbology meSymbology;
	float mfSymbolXOffset, mfSymbolYOffset;
	bool isLButtonDown; ///< true if left mouse button is down while in window (dragging)
	wxPoint buttonDownPoint; ///< start point for click-drag operations
	float leftMargin; ///< screen position to use for info text and symbols
	bool showFrameCounter; ///< true to show FPS display
	bool isMButtonDown; ///< true if middle mouse button is down
	wxPoint middleDownPoint; ///< start point for middle button drag
	tcPoint middleDownGeoPoint; ///< start point for middle button drag
	wxCursor moveCursor;

	tcButton* show3DButton; ///< button that is active when 3D is disabled, clicking sends msg to enable
	tcButton* accelerateTimeButton;
	tcButton* decelerateTimeButton;
	tcButton* togglePauseButton;

    tcButton* followHookedButton;

	std::vector<tcButton*> airROE; ///< hold, tight, free
	std::vector<tcButton*> surfROE;
	std::vector<tcButton*> subROE;
	std::vector<tcButton*> landROE;

	tcButton* saveButton;

    tcButton* revertToSaved; ///< for scenario edit mode only
    tcButton* changeSidesButton; ///< for scenario edit mode only

    // parameters for velocity leader
    float surfLeaderTime_s; ///< 0 means use fixed leader length
    float airLeaderTime_s; ///< 0 means use fixed leader length




	void BuildImageSymbology(int symbolArray, const std::string& subdirectory);
	void Build2525();
	void BuildNTDS();
	void BuildNTDSImage();

	tcGeometry* GetSymbol(tcAllianceInfo::Affiliation aeAffiliation, teSymbol aeSymbol);
	tcGeometry* GetSymbolAltered(tcAllianceInfo::Affiliation aeAffiliation, teSymbol aeSymbol);
	tcGeometry* GetSymbolFaded(tcAllianceInfo::Affiliation aeAffiliation, teSymbol aeSymbol);

	void CheckForNavPointEdit(const wxPoint& buttonDownPoint);
    void CheckForNavPointDetailedEdit(const wxPoint& buttonDownPoint);
    void OpenWaypointEditor(const wxPoint& pos);
    void UpdateWaypointEditor();

	void CreateAlternateSymbols();
	boost::shared_ptr<tcGeometry> CreateSymbolGeometry();
	boost::shared_ptr<tcGeometry> CreateTexturedSymbol(const char* symbolName);

	boost::shared_ptr<tcGeometry> DrawDefaultMark(tcAllianceInfo::Affiliation affil);
	boost::shared_ptr<tcGeometry> DrawNTDSSurface(tcAllianceInfo::Affiliation affil);
	boost::shared_ptr<tcGeometry> DrawNTDSGround(tcAllianceInfo::Affiliation affil);
	boost::shared_ptr<tcGeometry> DrawNTDSAirFW(tcAllianceInfo::Affiliation affil);
	boost::shared_ptr<tcGeometry> DrawNTDSAirRW(tcAllianceInfo::Affiliation affil);
	boost::shared_ptr<tcGeometry> DrawNTDSMissile(tcAllianceInfo::Affiliation affil);
	boost::shared_ptr<tcGeometry> DrawNTDSSubsurface(tcAllianceInfo::Affiliation affil);
	boost::shared_ptr<tcGeometry> DrawNTDSCarrier(tcAllianceInfo::Affiliation affil);
	boost::shared_ptr<tcGeometry> DrawNTDSTorpedo(tcAllianceInfo::Affiliation affil);
	boost::shared_ptr<tcGeometry> DrawNTDSUnknown(tcAllianceInfo::Affiliation affil);

	void DrawSymbol2(tcMapObj* pMO);
    float GetLeaderLength(float heading_rad, float speed_kts, int symbol) const;

	void InitializeButtons();
    bool IsPointNearNavLine(const wxPoint& pos, int& idx) const;
    void SendGroupHookMessage();
    
    void UpdateMissionEditGraphics();
	void UpdateScreenNavPoints();
	void UpdateViewForHooked();   
    void UpdateViewCenterOnHooked();
    void UpdateOptions();
	void UpdateMiddleButtonDragView(const wxPoint& currentPos);
    void DrawNavPointsMission(const std::vector<tcPoint>& p1, const std::vector<tcPoint>& p2);
    void DeleteEditPoint();
    void UpdateButtons();

	DECLARE_EVENT_TABLE()
};


#endif 
