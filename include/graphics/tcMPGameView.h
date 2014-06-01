/** 
**  @file tcMPGameView.h 
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

#ifndef _MPGAMEVIEW_H_
#define _MPGAMEVIEW_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "wx/wx.h" 

#include "tcXmlWindow.h"


class tcEditBox;
class tcConsoleBox;

/**
* User interface window for multiplayer game management.
* This window is displayed after connecting to a server, allowing
* teams and game settings to be defined.
*/
class tcMPGameView : public tcXmlWindow
{
public:
    struct PlayerInfo
    {
        std::string name;
        bool isCommander;
		bool isReady;
        bool inGame; ///< true if player is in the game
        bool endGame; ///< game ends if true for all commanders in the game 
        bool surrenderGame; ///< game ends if true for any commander in game
        unsigned char gameSpeed;
    };

    struct TeamInfo
    {
		unsigned char alliance; ///< alliance id for team
        std::string name;
        std::vector<PlayerInfo> playerList;
    };

    void Draw();

	bool IsEveryoneReady();

    void OnLButtonDown(wxMouseEvent& event);
	void ProcessButtonClick(wxCommandEvent& event);
    void SendChatText(wxCommandEvent& event);

	void SetTeamList(const std::vector<TeamInfo>& tl);
    unsigned int GetTeamSpeed() const;
    unsigned int GetFastestSpeed() const;

    tcMPGameView(wxWindow* parent, 
        const wxPoint& pos, const wxSize& size, 
        const wxString& name = "MPGameView", tc3DWindow2* host = 0);
    virtual ~tcMPGameView();
private:
    tcConsoleBox* chatBox;
    tcEditBox* chatEntry;
	tcButton* standDown;
	tcButton* ready;
	tcButton* startGame;
	tcButton* joinGame;

	float y;

    std::vector<TeamInfo> teamList;
    boost::shared_ptr<tcTexture2D> commanderFlag; ///< for team commanders
	boost::shared_ptr<tcTexture2D> readySymbol; ///< indicates player is ready
	std::vector<tcButton*> teamJoinButtons;

    unsigned teamGameSpeed; ///< game speed request for our team
    unsigned fastestGameSpeed; ///< fastest speed request of all teams
	
	bool allReady;
	bool userReady;

	void DrawScenarioInfo();
	void DrawTeamInfo();
	void UpdateButtonState();
	void UpdateReadyState();
    void UpdateGameSpeedRequests();

    DECLARE_EVENT_TABLE()
};

#endif