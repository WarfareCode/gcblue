/**
**  @file wxcommands.h
**  IDs for commands processed via wxWindows event handler.
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


#if !defined _WXCOMMANDS_H_
#define _WXCOMMANDS_H_

/**
* IDs for commands processed via wxWindows event handler.
*/
enum
{ 
    ID_STARTVIEW = 10, ///< switch to start view
    ID_CREDITVIEW = 20,  ///< switch to credits view
    ID_DATABASEVIEW = 30,  ///< switch to database view (not implemented yet)
    ID_OPTIONSVIEW = 40, ///< switch to options view
	ID_DISPLAYSETTINGS = 42, ///< switch to display settings view
    ID_SCENARIOSELECTVIEW = 50, ///< switch to scenario select view
    ID_MULTIPLAYERVIEW = 60, ///< switch to multiplayer view (view before connection established)
    ID_MPGAMEVIEW = 62, ///< switch to multiplayer game view (view after connection established)
	ID_BRIEFINGVIEW = 65, ///< switch to simple briefing view
    ID_STARTGAME = 70, ///< start game
    ID_EDITGAME = 71, ///< start game in scenario editor mode
	ID_ENDGAME = 72, ///< end game
    ID_QUITGAME = 73, ///< quit to desktop
    ID_RELOADGAME = 74,
    ID_CREATESCEN = 75, ///< create new scenario and start in edit mode
    ID_TABCLICKED = 77,
    ID_NEWHOOK = 80,  ///< new platform has been hooked by user
	ID_GROUPHOOK = 82, ///< new group of platforms has been hooked by user
	ID_DCLICKHOOK = 85, ///< hooked object has been double clicked by user
    ID_SETBRIEFING = 90, ///< enable/disable briefing mode
    ID_SETPAUSE = 100, ///< enable/disable game pause
    ID_SETTIMEACCEL = 102, ///< more general version of ID_SETPAUSE
    ID_SETMAXTIMEACCEL = 105, ///< limit current time acceleration to maximum value
    ID_SETTACTICALVIEW = 888, ///< set center and zoom for tactical map view
	ID_SETTHEATER = 908, ///< change theater view area for tactical map
    ID_HIGHRESTHEATER = 900, ///< change theater view to high res
    ID_MEDRESTHEATER = 901, ///< change theater view to medium res
    ID_LOWRESTHEATER = 902, ///< change theater view to low res
    ID_SET3D = 110, ///< set 3D window size
	ID_MINIMIZE3D = 111, ///< make 3D window size smaller
	ID_MAXIMIZE3D = 112, ///< make 3D window size bigger
    ID_SKIPBRIEFING = 120, ///< skip tactical briefing
    ID_BUTTONREDRAW = 130, ///< posted by button to force parent to redraw
    ID_SECONDARYHOOK = 140, ///< used for quick targeting and possibly other functions
    ID_MULTIPLAYERMODE = 150, ///< 0 - none, 1 - client, 2 - server
    ID_CONNECT = 160,
    ID_JOINGAME = 170,
    ID_CHATPROTOCOL = 180,
	ID_LOGINMODE = 190,
	ID_REFRESHMAPS = 200
};


#endif

