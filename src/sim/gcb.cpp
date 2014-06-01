/**
** @file gcb.cpp
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

#include "stdwx.h" // precompiled header file


#ifndef WX_PRECOMP
#include "wx/wx.h"
#ifdef WIN32
#include "wx/msw/private.h" // for MS Windows specific definitions
#endif
#endif

#include "wx/dir.h"
#include "wx/evtloop.h"
#include "wx/stdpaths.h"

#include "gcb.h"
#include "Game.h"
#include "tcDisplayModes.h"


IMPLEMENT_APP(GcbApp)

BEGIN_EVENT_TABLE(GcbApp, wxApp)
    //EVT_KEY_DOWN(GcbApp::OnKeyDown)  ///< any key has been pressed
    //EVT_CHAR(GcbApp::OnChar)
	//EVT_LEAVE_WINDOW(GcbApp::OnLeaveWindow)
	//EVT_LEFT_DOWN(GcbApp::OnLButtonDown)
	//EVT_MOTION(GcbApp::OnMouseMove)
	//EVT_RIGHT_DOWN(GcbApp::OnRButtonDown)
	EVT_ERASE_BACKGROUND(GcbApp::OnEraseBackground)
END_EVENT_TABLE()

FILE *errStream, *outStream; ///< for redirecting stderr, stdout

#ifdef _DEBUG
#define new DEBUG_NEW
#endif 


void GcbApp::CheckDirectories()
{
	wxArrayString requiredDir;

	requiredDir.push_back("3d");
	requiredDir.push_back("bin");
	requiredDir.push_back("database");
	requiredDir.push_back("images");
	requiredDir.push_back("maps");
	requiredDir.push_back("scenarios");
	requiredDir.push_back("scripts");
	requiredDir.push_back("sound");
	requiredDir.push_back("xml");

	for (size_t n=0; n<requiredDir.size(); n++)
	{
		wxString dirToCheck = requiredDir[n];
		if (!wxDir::Exists(dirToCheck))
		{
			wxMessageBox(wxString::Format("Missing required directory (%s), please repair or reinstall application", dirToCheck.c_str()));
			throw "missing directory";
		}
	}

	if (!wxDir::Exists("log"))
	{
		wxMkdir("log");
	}
	if (!wxDir::Exists("aar"))
	{
		wxMkdir("aar");
	}
}

/**
 * tcGame seems to be skipped for key events, this is a workaround
 * to call tcGame::OnChar with the event.
 */
void GcbApp::OnChar(wxKeyEvent& event)
{
    event.Skip();
    gameFrame->OnChar(event); // bad, but don't know how to make it work otherwise
}

/**
 * Erase Background event handler.
 *
 * Skip this event.
 *
 * @param event  wxEraseEvent object.
 */
void GcbApp::OnEraseBackground(wxEraseEvent& event)
{
    event.Skip();
}

/**
 * Key down event handler.
 * Route to gameFrame
 *
 * @param event  wxKeyEvent object.
 */
void GcbApp::OnKeyDown(wxKeyEvent& event)
{
    event.Skip();
    gameFrame->OnKeyDown(event);
}

/**
 * Passes the left mouse button down event to gameFrame.
 *
 * @param event  wxMouseEvent object.
 */
void GcbApp::OnLButtonDown(wxMouseEvent& event)
{
    event.Skip();
    gameFrame->OnLButtonDown(event);
}

void GcbApp::OnLeaveWindow(wxMouseEvent& event)
{
    event.Skip();
	gameFrame->OnLeaveWindow(event);
}

void GcbApp::OnMouseMove(wxMouseEvent& event)
{
    event.Skip();
	gameFrame->OnMouseMove(event);
}


/**
 * Passes the right mouse button down event to gameFrame.
 *
 * @param event  wxMouseEvent object.
 */
void GcbApp::OnRButtonDown(wxMouseEvent& event)
{
    event.Skip();
    gameFrame->OnRButtonDown(event);
}


/**
 * Provide gcBlue's main loop.
 *
 * Called by wxWindows on creation of the application.
 *
 * @return ??
 */
int GcbApp::MainLoop()
{
    bool m_keepGoing = TRUE;

    while (m_keepGoing)
    {

    #if wxUSE_THREADS
        wxMutexGuiLeaveOrEnter();
    #endif

        while (Pending())
        {
            Dispatch();
        }

        ProcessIdle();

        if (!closeApp)
        {
            if (gameFrame->UpdateFrame())  // called until it returns true
            {
                closeApp = TRUE;
                m_keepGoing = FALSE;
            }
        }
    }

    return 0; // ((MSG*)current_msg)->wParam;
}

/**
 * Initializes the application.
 *
 * Called upon startup and initializes the program by creating the main window.
 *
 * @return TRUE indicates a successful intialization
 */
bool GcbApp::OnInit()
{
	bool success = true;

	closeApp = false;

	try
	{
		SetWorkingDirectory();

		//wxString userDataPath = wxStandardPaths::Get().GetUserDataDir();

		CheckDirectories();

	    // Reassign stderr and stdout
		errStream = freopen( "log\\stderr.txt", "w", stderr );
		outStream = freopen( "log\\stdout.txt", "w", stdout );

		InitializeGameFrame();

		gameFrame->Show(true);
		SetTopWindow(gameFrame);

		eventLoop = new wxEventLoop();
        wxEventLoop::SetActive(eventLoop);

	}
	catch (...)
	{
		success = false;
	}

    return success;
}

/**
 * Cleans up upon application exiting.
 *
 * This handles application level shut down only. The gameFrame
 * destructor and all window destructors are automatically called
 * by wxWindows after falling out of MainLoop().
 *
 * @return An integer representing the status of wxApp::OnExit().
 */
int GcbApp::OnExit()
{
    if (errStream != NULL)
	{
		fclose(errStream);
	}

    if (outStream != NULL)
	{
		fclose(outStream);
	}

    WTL("FCLOSE"); // special string to close file

	delete eventLoop;
	eventLoop = 0;

    return wxApp::OnExit();
}

/**
 * Sets the working directory of the application.
 *
 * Makes the working directory the root directory of installation and makes
 * sure there is a bin directory.
 */
void GcbApp::SetWorkingDirectory()
{
    wxString cwd = wxGetCwd();

    if (cwd.Find("bin") >= 0)
    {
        if (!wxSetWorkingDirectory(".."))
		{
			wxMessageBox("Failed to set working directory.");
			WTL("Failed to set working directory.");

			throw std::exception();
		}
		else {}
    }
	else {}

	if (!wxDir::Exists("bin"))
	{
		wxMessageBox("The bin directory does not exist.");
		WTL("The bin directory does not exist.");

		throw std::exception();
	}
	else {}
}


/**
 * Initializes the main game frame.
 */
void GcbApp::InitializeGameFrame()
{
    try
    {
		tcDisplayModes::Get()->LoadModeFromOptions();

        int windowedMode = tcOptions::Get()->windowedMode;
        if (windowedMode)
        {
            int x, y;
            wxSize size;
            wxClientDisplayRect(&x, &y, &size.x, &size.y); // account for task bar size
            
            long frameStyle = wxDEFAULT_FRAME_STYLE;
            gameFrame = new tcGame(wxPoint(0,0), size, frameStyle);
        }
        else
        {
            long frameStyle = wxNO_FULL_REPAINT_ON_RESIZE;
            gameFrame = new tcGame(wxPoint(0,0), wxGetDisplaySize(), frameStyle);
        }
        gameFrame->Init();
    }
    catch(...)
    {
        wxMessageBox("The game frame failed to initialize.");
        WTL("The game frame failed to initialize.");

		throw std::exception();
    }

}