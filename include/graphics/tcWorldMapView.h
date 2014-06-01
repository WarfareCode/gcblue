/**  
**  @file tcWorldMapView.h
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

#ifndef _WORLDMAPVIEW_H_
#define _WORLDMAPVIEW_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "wx/wx.h" 

#include "tcMapView.h"

class tcGameSerializer;
class tcButton;

/**
* 
*/
class tcWorldMapView : public tcMapView 
{
    friend tcGameSerializer; // hack to allow serializer private access
public:
	tsWorldMapObj maMapObj[MAXWORLDMAPOBJ];
	UINT32 mnObjCount;
	int mnCounter;

	void ChangeTheater(float lon_deg, float lat_deg);
    void ChangeTheaterNow(float lon_deg, float lat_deg);
    void ChangeTacticalMapView(float lon_deg, float lat_deg);

	int CreateSurfaces(tcGraphicsInfo* apGraphicsEngine);
	void Draw();
	void DrawGrid();
	void DrawTheaterBox();
    const tcPoint& GetTheaterCenter() const;
    void SetTheaterCenter(float lon_deg, float lat_deg);

	virtual void OnChar(wxKeyEvent& event);
	virtual void OnMinimizeCommand(wxCommandEvent& event);
	virtual void OnLButtonDown(wxMouseEvent& event);
    virtual void OnLButtonUp(wxMouseEvent& event);
    virtual void OnLButtonDClick(wxMouseEvent& event);
    virtual void OnLeaveWindow(wxMouseEvent& event);

	virtual void OnMouseMove(wxMouseEvent& event);
	virtual void OnMouseWheel(wxMouseEvent& event);
	virtual void OnRButtonDown(wxMouseEvent& event);

	void ClearMapObjects();
	void Init();
	virtual void SetActive(bool abActive);
	void SetTheater(tcGeoRect r);
    void SetShowTacticalMapView(bool state);
    void SetTacticalMapView(const tcGeoRect& view);
	void ToggleMapSize();

	tcWorldMapView(wxWindow *parent, 
		const wxPoint& pos, const wxSize& size,
		tc3DWindow2* graphicsHost,
		const wxString& name = "WorldMapView");
	virtual ~tcWorldMapView();

private:
	WCHAR mzwchar[255]; 
	wxPoint mpointMouse;
	tcGeoRect mrectTheater; ///< active theater view region
    tcPoint theaterCenter_deg; ///< last coords (lon,lat) from ChangeTheater
	tcButton* minimizeButton;

    bool showTacticalMapView;
    tcGeoRect tacticalMapView; ///< active tactical map view

	void DrawSymbol(tsWorldMapObj *pMO);
    void DrawTacticalMapView();
	void ScrollMap(float direction_deg);

	DECLARE_EVENT_TABLE()
};

#endif 
