/**  
**  @file tcDatabaseInfoWindow.h
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



#ifndef _TCDATABASEINFOWINDOW_H_
#define _TCDATABASEINFOWINDOW_H_

#if _MSC_VER > 1000
#pragma once
#endif 

#include "tcXmlWindow.h"
#include "tcRegistered.h"
#include <stdarg.h>

namespace database
{
	class tcDatabaseObject;
    class tcPlatformDBObject;
    class tcMissileDBObject;
    class tcTorpedoDBObject;
}

class tcDatabaseInfoPanel;


/**
* Window class to display info for database object
*/
class tcDatabaseInfoWindow : public tcXmlWindow, public tcRegistered
{
public:
    virtual void Draw();

	virtual void OnCloseCommand(wxCommandEvent& event);
    //virtual void OnEnterWindow(wxMouseEvent& event);
    virtual void OnLButtonDown(wxMouseEvent& event);
    virtual void OnLButtonUp(wxMouseEvent& event);
    virtual void OnLeaveWindow(wxMouseEvent& event);
	virtual void OnMouseMove(wxMouseEvent& event);
    //virtual void OnRButtonDown(wxMouseEvent& event);

    /// set database class name to display info for
    void SetDatabaseClassName(const std::string& className);

    /// set id of game object to display info for (must be classified if track)
	void SetDatabaseObject(long id);

	database::tcDatabaseObject* GetDatabaseObject();

	static void SetParent(tc3DWindow2* win);
	

    tcDatabaseInfoWindow(const wxPoint& pos,
		const wxString& configFile = "xml/database_info.xml",
        const wxString& name = "DatabaseInfo",
        tc3DWindow2* hostParent = parent);

    virtual ~tcDatabaseInfoWindow();
    
protected:	
    unsigned int drawCount;

private:
    enum ViewMode
    {
        POPUP = 0, ///< compact view for popups
        EMBED = 1 ///< mode for database viewer screen
    } viewMode;  ///< mode automatically selected based on hostParent argument to constructor


    long objId; ///< id of obj or track to display info for
	std::string databaseClassName; ///< class name of database object, empty if not looked up yet
    std::vector<boost::shared_ptr<tcTexture2D> > imageList; ///< images for this db object, loaded as textures
    size_t currentImageIdx; ///< index of current image displayed (to cycle through available images)
    unsigned int imageTime; ///< time at which current image was first displayed
    float xImage; ///< x coordinate of image
    float yImage; ///< y coordinate of image
	tcDatabaseInfoPanel* infoPanel;

	static tc3DWindow2* parent;

	void DrawDatabaseInfo();
    void DrawDatabaseImages();
    void PrintText(float x, float& y, const char* formatString, ...);


    void LoadImageList();
    bool IsEmbedded() const;
    bool IsPopup() const;
    

    DECLARE_EVENT_TABLE()
};

#endif

