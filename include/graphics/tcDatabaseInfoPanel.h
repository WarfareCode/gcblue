/**  
**  @file tcDatabaseInfoPanel.h
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



#ifndef _tcDatabaseInfoPanel_H_
#define _tcDatabaseInfoPanel_H_

#if _MSC_VER > 1000
#pragma once
#endif 

#include "tc3DWindow2.h"
#include <stdarg.h>

namespace database
{
	class tcDatabaseObject;
    class tcPlatformDBObject;
    class tcMissileDBObject;
    class tcTorpedoDBObject;
    class tcShipDBObject;
	class tcSubDBObject;
    class tcAirDBObject;
    class tcGroundDBObject;
}

class tcScrollBar;
class tcUnits;

/**
* Window class for subpanel for display info for database object
*/
class tcDatabaseInfoPanel : public tc3DWindow2
{
public:
    virtual void Draw();



    /// set database class name to display info for
    void SetDatabaseClassName(const std::string& className);

    /// set id of game object to display info for (must be classified if track)
	void SetDatabaseObject(long id);
	void SetViewMode(int mode);

    tcDatabaseInfoPanel(wxWindow* parent, 
        const wxPoint& pos, const wxSize& size, 
        const wxString& name = "DBpanel", tc3DWindow2* graphicsHost = 0);

    virtual ~tcDatabaseInfoPanel();
    
private:
    enum ViewMode
    {
        POPUP = 0, ///< compact view for popups
        EMBED = 1 ///< mode for database viewer screen
    } viewMode;  ///< mode automatically selected based on hostParent argument to constructor


    long objId; ///< id of obj or track to display info for
	std::string databaseClassName; ///< class name of database object, empty if not looked up yet
    tcUnits* units;

	tcScrollBar* scrollBar;
	float yOffset; ///< offset for scrolling
	float yCurrent; ///< used to track how much space the text needs for scrolling

	void DrawDatabaseInfo();
    void DrawDatabaseInfo(database::tcShipDBObject* shipData, float yStart);
    void DrawDatabaseInfo(database::tcSubDBObject* subData, float yStart);
    void DrawDatabaseInfo(database::tcAirDBObject* airData, float yStart);
    void DrawDatabaseInfo(database::tcGroundDBObject* groundData, float yStart);
    void DrawDatabaseInfo(database::tcMissileDBObject* missileData, float yStart);
    void DrawDatabaseInfo(database::tcTorpedoDBObject* torpedoData, float yStart);

    void DrawLauncherInfo(database::tcPlatformDBObject* genericData, float& y);
    void DrawSensorInfo(database::tcPlatformDBObject* genericData, float& y);
    void PrintText(float x, float& y, const char* formatString, ...);

	database::tcDatabaseObject* GetDatabaseObject();
    void LoadImageList();
    bool IsEmbedded() const;
    bool IsPopup() const;

    void OnEnterWindow(wxMouseEvent& event);
    void OnMouseWheel(wxMouseEvent& event);
	void OnScrollbarUpdated(wxCommandEvent& event);

    DECLARE_EVENT_TABLE()
};

#endif

