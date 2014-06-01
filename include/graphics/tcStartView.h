/** 
**  @file tcStartView.h
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

#ifndef _STARTVIEW_H_
#define _STARTVIEW_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "wx/wx.h" 

#include "tc3DWindow2.h"
#include "AError.h"
#include "tcString.h"
#include <boost/shared_ptr.hpp>
#include "tv_types.h"

class tcTexture2D;
class tcOptions;
class tc3DViewer;
class tcTabHeader;
class tcScenarioSelectView;
class tcNetworkView;
class tcMPGameView;
class tcDatabaseViewer;

class tcStartView : public tc3DWindow2
{
public:
    /**
    * placement info for GUI buttons, text, etc.
    */
    struct tsButtonInfo
    {
        enum {OFF = 0, OVER = 1, ON = 2};
        std::string altText;
        tcString mzCaption;
        int mnButtonX;
        int mnButtonY;
        int mnTextX;
        int mnTextY;   
        int mnButtonWidth;
        int mnButtonHeight;
        boost::shared_ptr<tcTexture2D> mpiButtonOn;
        boost::shared_ptr<tcTexture2D> mpiButtonOver;
        boost::shared_ptr<tcTexture2D> mpiButtonOff;
        unsigned timeStamp; ///< for fading in/out
        int mnState; ///< 0 - off, 1 - over off, 2 - on
        tc3DWindow2* subWindow; ///< window for this submenu
        std::string paneName;
    };

public:
    int mnActiveButton;

    void AttachOptions(tcOptions *apOptions) {mpOptions=apOptions;}
    bool Init();
    void Draw();
    void DrawButton(int anButton);
    void DrawButtonLine(int anButton);
    int GetActiveButton() const {return mnActiveButton;}
    void OnChar(wxKeyEvent& event);
    void OnKeyDown(wxKeyEvent& event);
    void OnLButtonDown(wxMouseEvent& event);
    void OnMouseMove(wxMouseEvent& event);
    void OnSize(wxSizeEvent& event);
    void OnTab(wxCommandEvent& event);
    void PlaceButtons();
    bool ButtonContainingPoint(wxPoint point, int& rnButton);
    const std::string& GetPane() const;
    void SetPane(const std::string& s);
    void SetPane(size_t n);
    void Set3DViewer(tc3DViewer* v);
    void SetPlayEnabled(bool state);
    void SetGameStarted(bool state);
    void SetVersionString(const std::string& s);

    tcNetworkView* GetNetworkView() const;
    tcMPGameView* GetMPGameView() const;
    tcScenarioSelectView* GetScenarioSelectView() const;
    tcDatabaseViewer* GetDatabaseViewer() const;

    virtual void SetActive(bool abActive);

    tcStartView(wxWindow *parent, 
        const wxPoint& pos, const wxSize& size, const wxString& name = "tc3DWindow");
    virtual ~tcStartView();

private:
    enum {N_START_BUTTONS = 9};
    tcOptions* mpOptions;
    tc3DWindow2* rightPane;
    tcTabHeader* tabHeader;
    tcScenarioSelectView* scenarioSelectView;
    tcNetworkView* networkView;
    tc3DViewer* viewer;
    tcDatabaseViewer* databaseViewer;

    bool mbPlayEnabled;
    bool gameStarted;

    tsButtonInfo maButton[N_START_BUTTONS];
    int mnXStart;
    int mnYStart;
    const int buttonSize;
    const unsigned int buttonFadeTime;
    wxPoint panePosition;
    wxSize paneSize;
    wxPoint tabPosition;
    wxSize tabSize;
    std::string versionString; ///< for displaying version on start screen

    DECLARE_EVENT_TABLE()
};
#endif