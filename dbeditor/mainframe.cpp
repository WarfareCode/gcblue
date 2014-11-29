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

#include "DatabaseExport.h"
#include "tcToolbar.h"
#include "DatabaseManager.h"
#include "ToolPanel.h"
#include "BaseViewer.h"
#include "GridPanel.h"
#include "GameEngineInit.h"
#include "SonarCalculationControl.h"
#include "MissileCalculationControl.h"
#include "ECMEvaluationDialog.h"

#include "wx/wx.h"
#include "wx/dir.h"
#include "wx/file.h"
#include "wx/filepicker.h"
#include "wx/stattext.h"
#include "wx/notebook.h"
#include "wx/xml/xml.h"
#include "wx/filedlg.h"
#include "wx/textctrl.h"



class MyApp: public wxApp
{
    wxFrame* mainFrame;

    virtual bool OnInit();
};

class MyFrame: public wxFrame
{
public:

    wxNotebook* notebook;

    wxXmlDocument config;

    wxString lastDatabasePath;
    wxString lastDatabaseFile;
    wxString lastCSVPath;

    tcToolPanel* toolPanel;

    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
    virtual ~MyFrame();

    void OnQuit(wxCommandEvent& event);
    void OnCheckSetups(wxCommandEvent& event);
    void OnCheckForErrors(wxCommandEvent& event);
    void OnECMEvaluation(wxCommandEvent& event);
    void OnClose(wxCloseEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnTest(wxCommandEvent& event);
    void OnOpenDatabase(wxCommandEvent& event);
    void OnPageChanged(wxBookCtrlEvent& event);
    void OnPageChanging(wxBookCtrlEvent& event);
    void OnSaveDatabase(wxCommandEvent& event);
    void OnCreateIndices(wxCommandEvent& event);
    void OnJumpTo(wxCommandEvent& event);

    void LoadConfigFromFile();
    void SaveConfigToFile();

    void Shutdown();

    void UpdatePages();
	tcBaseViewer* FindViewerForTable(const wxString& table);

    enum {NOTEBOOK_ID = 345};

    DECLARE_EVENT_TABLE()
};

enum
{
    ID_Quit = 1,
    ID_About,
    ID_Test,
    ID_OpenDatabase,
    ID_SaveDatabase,
    ID_CheckSetups,
    ID_CheckForErrors,
    ID_ECMEvaluation
};

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_CLOSE(MyFrame::OnClose)
    EVT_MENU(ID_Quit, MyFrame::OnQuit)
    EVT_MENU(ID_About, MyFrame::OnAbout)
    EVT_MENU(ID_Test, MyFrame::OnTest)
    EVT_MENU(ID_OpenDatabase, MyFrame::OnOpenDatabase)
    EVT_MENU(ID_SaveDatabase, MyFrame::OnSaveDatabase)
    EVT_MENU(ID_CheckSetups, MyFrame::OnCheckSetups)
    EVT_MENU(ID_CheckForErrors, MyFrame::OnCheckForErrors)
    EVT_MENU(ID_ECMEvaluation, MyFrame::OnECMEvaluation)
    EVT_NOTEBOOK_PAGE_CHANGED(NOTEBOOK_ID, MyFrame::OnPageChanged)
    EVT_NOTEBOOK_PAGE_CHANGING(NOTEBOOK_ID, MyFrame::OnPageChanging)
    EVT_BUTTON(tcGridPanel::JUMP_TO, MyFrame::OnJumpTo)
END_EVENT_TABLE()

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{   
	wxSetWorkingDirectory("../."); // one directory above bin

    mainFrame = new MyFrame( _T("GCB2 DB EDITOR"), wxPoint(50,50), wxSize(1200,820) );
    mainFrame->Show(TRUE);
    SetTopWindow(mainFrame);
    return TRUE;
} 



MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
: wxFrame((wxFrame *)NULL, -1, title, pos, size)
{
	tcGameEngineInit::Init(this);

    SetBackgroundColour(wxColour("white"));

    wxMenu *menuFile = new wxMenu;

    menuFile->Append(ID_OpenDatabase, _T("&Open database"));
    menuFile->Append(ID_SaveDatabase, _T("&Save database"));
    menuFile->AppendSeparator();
    menuFile->Append(ID_About, _T("&About..."));
    menuFile->AppendSeparator();
    menuFile->Append(ID_Quit, _T("E&xit") );

    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append( menuFile, _T("&File") );


    wxMenu* menuTools = new wxMenu;
    menuTools->Append(ID_CheckForErrors, _T("&Check for errors"));
    menuTools->Append(ID_CheckSetups, _T("Check platform &setups"));
    menuTools->Append(ID_ECMEvaluation, _T("&ECM evaluation"));
    menuBar->Append(menuTools, _T("&Tools"));

    SetMenuBar( menuBar );

    CreateStatusBar();
    SetStatusText( _T("GCB2 dbeditor started") );


    notebook = new wxNotebook(this, NOTEBOOK_ID, wxDefaultPosition, wxDefaultSize, wxNB_TOP | wxNB_MULTILINE, "MainNotebook");


    tcBaseViewer* subViewer = new tcBaseViewer(notebook, "sub", "SubViewer");
    subViewer->AddPage("Sub", "config/sub_form.xml");
    subViewer->AddGridPage("Launchers", "config/platform_launcher_grid.xml");
    subViewer->AddGridPage("Sensors", "config/platform_sensor_grid.xml");
    subViewer->AddGridPage("Magazines", "config/platform_magazine_grid.xml");
    subViewer->AddSetupPanel("Setup");
    subViewer->AddGridPage("Names", "config/platform_names_grid.xml");
    notebook->AddPage(subViewer, "Sub", true);

    tcBaseViewer* shipViewer = new tcBaseViewer(notebook, "ship", "ShipViewer");
    shipViewer->AddPage("Ship", "config/ship_form.xml");
    shipViewer->AddGridPage("Launchers", "config/platform_launcher_grid.xml");
    shipViewer->AddGridPage("Sensors", "config/platform_sensor_grid.xml");
    shipViewer->AddGridPage("Magazines", "config/platform_magazine_grid.xml");
    shipViewer->AddSetupPanel("Setup");
    shipViewer->AddGridPage("Names", "config/platform_names_grid.xml");
    notebook->AddPage(shipViewer, "Ship", true);

    tcBaseViewer* groundViewer = new tcBaseViewer(notebook, "ground", "GroundViewer");
    groundViewer->AddPage("Ground", "config/ground_form.xml");
    groundViewer->AddGridPage("Launchers", "config/platform_launcher_grid.xml");
    groundViewer->AddGridPage("Sensors", "config/platform_sensor_grid.xml");
    groundViewer->AddGridPage("Magazines", "config/platform_magazine_grid.xml");
    groundViewer->AddSetupPanel("Setup");
    groundViewer->AddGridPage("Names", "config/platform_names_grid.xml");
    notebook->AddPage(groundViewer, "Ground", true);

    tcBaseViewer* airViewer = new tcBaseViewer(notebook, "air", "AirViewer");
    airViewer->AddPage("Air", "config/air_form.xml");
    airViewer->AddPage("Tables", "config/airtable_form.xml");
    airViewer->AddGridPage("Launchers", "config/platform_launcher_grid.xml");
    airViewer->AddGridPage("Sensors", "config/platform_sensor_grid.xml");
    airViewer->AddGridPage("Magazines", "config/platform_magazine_grid.xml");
    airViewer->AddSetupPanel("Setup");
    notebook->AddPage(airViewer, "Air", true);

    tcBaseViewer* simpleairViewer = new tcBaseViewer(notebook, "simpleair", "SimpleAirViewer");
    simpleairViewer->AddPage("SimpleAir", "config/simpleair_form.xml");
    simpleairViewer->AddGridPage("Launchers", "config/platform_launcher_grid.xml");
    simpleairViewer->AddGridPage("Sensors", "config/platform_sensor_grid.xml");
    simpleairViewer->AddGridPage("Magazines", "config/platform_magazine_grid.xml");
    simpleairViewer->AddSetupPanel("Setup");
    notebook->AddPage(simpleairViewer, "SimpleAir", true);

    tcBaseViewer* radarViewer = new tcBaseViewer(notebook, "radar", "RadarViewer");
    radarViewer->AddPage("radar", "config/radar_form.xml");
    notebook->AddPage(radarViewer, "Radar", false);

    tcBaseViewer* sonarViewer = new tcBaseViewer(notebook, "sonar", "SonarViewer");
    sonarViewer->AddPage("sonar", "config/sonar_form.xml");
	sonarViewer->AddPage("range calc", "config/sonar_calc_form.xml");
    notebook->AddPage(sonarViewer, "Sonar", false);

    tcBaseViewer* esmViewer = new tcBaseViewer(notebook, "esm", "ESMViewer");
    esmViewer->AddPage("esm", "config/esm_form.xml");
    notebook->AddPage(esmViewer, "ESM", false);

    tcBaseViewer* ecmViewer = new tcBaseViewer(notebook, "ecm", "ECMViewer");
    ecmViewer->AddPage("ecm", "config/ecm_form.xml");
    notebook->AddPage(ecmViewer, "ECM", false);

    tcBaseViewer* optical = new tcBaseViewer(notebook, "optical", "OpticalViewer");
    optical->AddPage("optical", "config/optical_form.xml");
    notebook->AddPage(optical, "Optical", false);

    tcBaseViewer* torpedo = new tcBaseViewer(notebook, "torpedo", "TorpedoViewer");
    torpedo->AddPage("torpedo", "config/torpedo_form.xml");
    notebook->AddPage(torpedo, "Torpedo", false);

    tcBaseViewer* missile = new tcBaseViewer(notebook, "missile", "MissileViewer");
    missile->AddPage("missile", "config/missile_form.xml");
    missile->AddPage("profile", "config/missile_profile_form.xml");
	missile->AddPage("calc", "config/missile_calc_form.xml");
    notebook->AddPage(missile, "Missile", false);

    tcBaseViewer* bmissile = new tcBaseViewer(notebook, "ballistic_missile", "BMissileViewer");
    bmissile->AddPage("ballistic missile", "config/ballisticmissile_form.xml");
    notebook->AddPage(bmissile, "Ballistic Missile", false);

    tcBaseViewer* ballistic = new tcBaseViewer(notebook, "ballistic", "BallisticViewer");
    ballistic->AddPage("ballistic", "config/ballistic_form.xml");
    notebook->AddPage(ballistic, "Ballistic", false);

    tcBaseViewer* launcherConfig = new tcBaseViewer(notebook, "launcher_configuration", "LauncherConfigViewer");
    launcherConfig->AddGridPage("launcher_config", "config/launcher_config_grid.xml");
    notebook->AddPage(launcherConfig, "Launcher Config", false);

    tcBaseViewer* stores = new tcBaseViewer(notebook, "stores", "StoresViewer");
    stores->AddPage("stores", "config/stores_form.xml");
    notebook->AddPage(stores, "Stores", false);

    tcBaseViewer* magazineLoadout = new tcBaseViewer(notebook, "magazine_loadout", "MagazineLoadoutViewer");
    magazineLoadout->AddGridPage("magazine_loadout", "config/magazine_loadout_grid.xml");
    notebook->AddPage(magazineLoadout, "Magazine Loadouts", false);

    tcBaseViewer* airComplement = new tcBaseViewer(notebook, "air_complement", "AirComplementViewer");
    airComplement->AddGridPage("air_complement", "config/air_complement_grid.xml");
    notebook->AddPage(airComplement, "Air Complements", false);

    tcBaseViewer* cm = new tcBaseViewer(notebook, "cm", "CMViewer");
    cm->AddPage("cm", "config/cm_form.xml");
    notebook->AddPage(cm, "CM", false);

    tcBaseViewer* flightport = new tcBaseViewer(notebook, "flightport", "FlightportViewer");
    flightport->AddPage("flightport", "config/flightport_form.xml");
    notebook->AddPage(flightport, "Flightport", false);

    tcBaseViewer* sonobuoy = new tcBaseViewer(notebook, "sonobuoy", "SonobuoyViewer");
    sonobuoy->AddPage("sonobuoy", "config/sonobuoy_form.xml");
    sonobuoy->AddGridPage("Sensors", "config/platform_sensor_grid.xml");
    notebook->AddPage(sonobuoy, "Sonobuoy", false);

    toolPanel = new tcToolPanel(notebook);
    notebook->AddPage(toolPanel, "Import/Export", false);

    LoadConfigFromFile();


    wxString autoOpenPath = lastDatabasePath + wxString("\\") + lastDatabaseFile;
    if (autoOpenPath.size() > 3)
    {
        try
        {
            tcDatabaseManager::Get()->Open(autoOpenPath.ToStdString());
            UpdatePages();
            wxString msg = wxString("Editing ") + autoOpenPath;
            SetStatusText(msg);
        }
        catch (...)
        {
        }
    }

    tcGridPanel::eventFrame = this;

	//wxWindow::bypassEraseBkgnd = false;
}

MyFrame::~MyFrame()
{
    SaveConfigToFile();
}

void MyFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    wxMessageBox(_T("GCB2 Database Editor v1.5"),
        _T("About dbeditor"), wxOK | wxICON_INFORMATION, this);
}

void MyFrame::OnCheckForErrors(wxCommandEvent& WXUNUSED(event))
{
    tcDatabaseManager* databaseManager = tcDatabaseManager::Get();

    databaseManager->CheckForErrors("database_errors.txt");
}

void MyFrame::OnCheckSetups(wxCommandEvent& WXUNUSED(event))
{
    tcDatabaseManager* databaseManager = tcDatabaseManager::Get();

    databaseManager->CheckAllSetups();
}


void MyFrame::OnECMEvaluation(wxCommandEvent& WXUNUSED(event))
{
    tcECMEvaluationDialog dlg(this, "ECM Evaluation");

    dlg.ShowModal();
}

void MyFrame::OnClose(wxCloseEvent& event)
{
    tcDatabaseManager* databaseManager = tcDatabaseManager::Get();
    if (databaseManager->AreChangesPending())
    {
        wxMessageDialog dialog(this, "Save changes before closing?", "Save?", wxYES | wxNO | wxCANCEL, wxDefaultPosition);
        int response = dialog.ShowModal();
        if (response == wxID_YES)
        {
            databaseManager->Commit(false);
            wxWindow::Destroy();
        }
        else if (response == wxID_CANCEL)
        {
            if (event.CanVeto())
            {
                event.Veto();
            }
            else
            {
                Shutdown();
            }
        }
        else
        {
            Shutdown();
        }
    }
    else
    {
        Shutdown();
    }
}

void MyFrame::OnOpenDatabase(wxCommandEvent& WXUNUSED(event))
{


    wxString defaultDir("");
    wxString defaultFile("");

    if (lastDatabasePath.size() > 0) defaultDir = lastDatabasePath;
    if (lastDatabaseFile.size() > 0) defaultFile = lastDatabaseFile;


    wxFileDialog dialog(this, "Choose database file", defaultDir, defaultFile, "*.db", wxFD_OPEN | wxFD_FILE_MUST_EXIST, wxDefaultPosition, wxDefaultSize, "filedlg");

    if (dialog.ShowModal() == wxID_OK)
    {    
        if (tcDatabaseManager::Get()->IsOpen())
        {
            tcDatabaseManager::Get()->Close();
            SetStatusText("Closed database");
        }

        std::string databaseFileName;
        databaseFileName = dialog.GetPath().c_str();

        if (tcDatabaseManager::Get()->Open(databaseFileName))
        {
            UpdatePages();

            wxString fullPath = dialog.GetPath();

            lastDatabasePath = fullPath.BeforeLast('\\');
            lastDatabaseFile = fullPath.AfterLast('\\');


            wxString msg = wxString("Editing ") + fullPath;
            SetStatusText(msg);
        }
        else
        {
            wxMessageBox("Open failed");
        }
    }

}

void MyFrame::OnJumpTo(wxCommandEvent& event)
{
    wxString s = event.GetString();
    wxString databaseClass = s.BeforeFirst(',');
    wxString table = s.AfterFirst(',');

    size_t nPages = notebook->GetPageCount();
    for (size_t n=0; n<nPages; n++)
    {
        wxNotebookPage* notebookPage = notebook->GetPage(n);
        if (tcBaseViewer* viewer = dynamic_cast<tcBaseViewer*>(notebookPage))
        {
            if (viewer->GetTable() == table)
            {
                notebook->SetSelection(n);
                viewer->SetDatabaseClass(databaseClass);
                return;
            }
        }
    }

}

void MyFrame::OnPageChanged(wxBookCtrlEvent& event)
{
    int page = event.GetSelection();
    if (page >= 0)
    {
        wxNotebookPage* notebookPage = notebook->GetPage(size_t(page));
        if (tcEditorMainPage* editorPage = dynamic_cast<tcEditorMainPage*>(notebookPage))
        {
            editorPage->UpdatePage();
        }
    }
    else
    {
        wxASSERT(false); // should not happen
    }

}

/**
* Apply edits to page that's changing
*/
void MyFrame::OnPageChanging(wxBookCtrlEvent& event)
{
    int page = event.GetSelection();
    if (page >= 0)
    {
        wxNotebookPage* notebookPage = notebook->GetPage(size_t(page));
        if (tcBaseViewer* viewer = dynamic_cast<tcBaseViewer*>(notebookPage))
        {
            viewer->Save();
        }
    }
    else
    {
        wxASSERT(false); // should not happen
    }

}

void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    Close(TRUE);
}

void MyFrame::OnSaveDatabase(wxCommandEvent& WXUNUSED(event))
{
    tcDatabaseManager* databaseManager = tcDatabaseManager::Get();
    if (databaseManager->AreChangesPending())
    {
        databaseManager->Commit(true);
    }
}



void MyFrame::OnTest(wxCommandEvent& WXUNUSED(event))
{
    tcDatabaseTranslator databaseExport;

    databaseExport.Test();

} 


void MyFrame::LoadConfigFromFile()
{
    if (wxFile::Exists("config/config.xml"))
    {
        bool success = config.Load("config/config.xml");
    }

    wxXmlNode* root = config.GetRoot();
    if (root == 0)
    {
        config.SetRoot(new wxXmlNode(NULL, wxXML_ELEMENT_NODE, "Root"));
        root = config.GetRoot();
    }

    wxXmlNode* child = root->GetChildren();
    if (child == 0)
    {
        wxXmlNode* pathInfo = new wxXmlNode(NULL, wxXML_ELEMENT_NODE, "LastPath");
        pathInfo->AddProperty("LastDatabasePath", "");
        pathInfo->AddProperty("LastDatabaseFile", "");
        pathInfo->AddProperty("LastCSVPath", "");
        root->AddChild(pathInfo);
    }
    else
    {
        lastDatabasePath = child->GetPropVal("LastDatabasePath", "");
        lastDatabaseFile = child->GetPropVal("LastDatabaseFile", "");
        lastCSVPath = child->GetPropVal("LastCSVPath", "");

        toolPanel->SetCSVPath(lastCSVPath);
    }

	if (child != 0) child = child->GetNext();
	if (child == 0)
	{
		wxXmlNode* pageState = new wxXmlNode(NULL, wxXML_ELEMENT_NODE, "PageState");
		root->AddChild(pageState);
	}
	else
	{
		wxXmlNode* nextPage = child->GetChildren();
		while (nextPage != 0)
		{
			wxString table = nextPage->GetPropVal("Table", "");
			wxString itemName = nextPage->GetPropVal("ItemName", "");
			if (tcBaseViewer* viewer = FindViewerForTable(table))
			{
				viewer->InitializeDatabaseClass(itemName);
			}


			nextPage = nextPage->GetNext();
		}
	}

	// sonar calculation
	if (child != 0) child = child->GetNext();
	if (child == 0)
	{
		wxXmlNode* sonarConfig = new wxXmlNode(NULL, wxXML_ELEMENT_NODE, "SonarCalculation");
		root->AddChild(sonarConfig);
	}
	else
	{
		wxXmlNode* sonarConfig = child;
		tcSonarCalculationControl::Get()->LoadXmlConfig(sonarConfig);
	}

	// missile calculation
	if (child != 0) child = child->GetNext();
	if (child == 0)
	{
		wxXmlNode* missileConfig = new wxXmlNode(NULL, wxXML_ELEMENT_NODE, "MissileCalculation");
		root->AddChild(missileConfig);
	}
	else
	{
		wxXmlNode* missileConfig = child;
		tcMissileCalculationControl::Get()->LoadXmlConfig(missileConfig);
	}

}

void MyFrame::SaveConfigToFile()
{
    wxXmlNode* root = config.GetRoot();
    wxXmlNode* child = root->GetChildren();

    lastCSVPath = toolPanel->GetLastCSVPath();

    if (child != 0)
    {
        child->DeleteProperty("LastDatabasePath");
        child->DeleteProperty("LastDatabaseFile");
        child->DeleteProperty("LastCSVPath");

        child->AddProperty("LastDatabasePath", lastDatabasePath);
        child->AddProperty("LastDatabaseFile", lastDatabaseFile);
        child->AddProperty("LastCSVPath", lastCSVPath);

        
    }
    else
    {
        wxASSERT(false);
		return;
    }

	// save page state
	wxXmlNode* pageState = child->GetNext();
	if (pageState == 0)
	{
		wxASSERT(false);
		return;
	}

	wxXmlNode* pageChild = pageState->GetChildren();
	while (pageChild != 0)
	{
		wxXmlNode* nextChild = pageChild->GetNext();
		pageState->RemoveChild(pageChild);
		pageChild = nextChild;
	}

    size_t nPages = notebook->GetPageCount();
    for (size_t n=0; n<nPages; n++)
    {
        wxNotebookPage* notebookPage = notebook->GetPage(n);
        if (tcBaseViewer* viewer = dynamic_cast<tcBaseViewer*>(notebookPage))
        {
			wxXmlNode* page = new wxXmlNode(NULL, wxXML_ELEMENT_NODE, "Page");
			page->AddProperty("Table", viewer->GetTable());
			page->AddProperty("ItemName", viewer->GetPlatformName());

			pageState->AddChild(page);
        }
    }

	// sonar calculation
	wxXmlNode* sonarConfig = pageState->GetNext();
	if (sonarConfig == 0)
	{
		wxASSERT(false);
		return;
	}
	tcSonarCalculationControl::Get()->SaveXmlConfig(sonarConfig);
	
	// missile calculation
	wxXmlNode* missileConfig = pageState->GetNext();
	if (missileConfig == 0)
	{
		wxASSERT(false);
		return;
	}
	tcMissileCalculationControl::Get()->SaveXmlConfig(missileConfig);

	config.Save("config/config.xml", 4);

}

void MyFrame::Shutdown()
{
    size_t nPages = notebook->GetPageCount();
    for (size_t n=0; n<nPages; n++)
    {
        wxNotebookPage* notebookPage = notebook->GetPage(n);
        if (tcEditorMainPage* editorPage = dynamic_cast<tcEditorMainPage*>(notebookPage))
        {
            editorPage->UpdatePage();
        }
    }

    wxFrame::Destroy();
}


void MyFrame::UpdatePages()
{
    size_t nPages = notebook->GetPageCount();
    for (size_t n=0; n<nPages; n++)
    {
        wxNotebookPage* notebookPage = notebook->GetPage(n);
        try
        {
            if (tcEditorMainPage* editorPage = dynamic_cast<tcEditorMainPage*>(notebookPage))
            {
                editorPage->UpdatePage();
            }
        }
        catch (...)
        {
            wxString msg("Error updating page: ");
            msg += notebookPage->GetName();
            wxMessageBox(msg);
        }
    }
}

tcBaseViewer* MyFrame::FindViewerForTable(const wxString& table)
{
    size_t nPages = notebook->GetPageCount();
    for (size_t n=0; n<nPages; n++)
    {
        wxNotebookPage* notebookPage = notebook->GetPage(n);
        if (tcBaseViewer* viewer = dynamic_cast<tcBaseViewer*>(notebookPage))
        {
            if (viewer->GetTable() == table) return viewer;
        }
    }

	return 0;
}