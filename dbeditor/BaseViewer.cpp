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
#include <wx/bookctrl.h>
#include "BaseViewer.h"
#include "BasePanel.h"
#include "PlatformSelectPanel.h"
#include "RenamePlatformDialog.h"
#include "DatabaseManager.h"
#include "GridPanel.h"
#include "SetupPanel.h"

#include "wx/button.h"



#include "wx/sizer.h"
#include "wx/msgdlg.h"
#include "wx/scrolbar.h"

BEGIN_EVENT_TABLE(tcBaseViewer, tcEditorMainPage)
    EVT_BUTTON(SELECTION_UPDATED, tcBaseViewer::OnPlatformUpdated)
    EVT_BUTTON(UNDO_EDITS, tcBaseViewer::OnUndoEdits)
    EVT_BUTTON(APPLY_EDITS, tcBaseViewer::OnApplyEdits)
    EVT_BUTTON(RENAME_PLATFORM, tcBaseViewer::OnRenamePlatform)
    EVT_BUTTON(DELETE_PLATFORM, tcBaseViewer::OnDeletePlatform)
    EVT_BUTTON(DUPLICATE_PLATFORM, tcBaseViewer::OnDuplicatePlatform)
    EVT_NOTEBOOK_PAGE_CHANGED(-1, tcBaseViewer::OnPageChanged)
    EVT_NOTEBOOK_PAGE_CHANGING(-1, tcBaseViewer::OnPageChanging)
END_EVENT_TABLE()



void tcBaseViewer::AddPage(tcBasePanel* panel, const wxString& pageName)
{
    panelNotebook->AddPage(panel, pageName);
}

void tcBaseViewer::AddPage(const wxString& pageName, const wxString& formPath)
{
    tcBasePanel* panel = new tcBasePanel(panelNotebook, table, "Panel", formPath);

    AddPage(panel, pageName);
}

void tcBaseViewer::AddGridPage(const wxString& pageName, const wxString& xmlPath)
{
    tcGridPanel* panel = new tcGridPanel(panelNotebook, table, "GridPanel", xmlPath);
    
    AddPage(panel, pageName);
}

void tcBaseViewer::AddSetupPanel(const wxString& pageName)
{
    tcSetupPanel* panel = new tcSetupPanel(panelNotebook, table, "SetupPanel");
    
    AddPage(panel, pageName);
}

const wxString& tcBaseViewer::GetPlatformName() const
{
	return platformName;
}

const wxString& tcBaseViewer::GetTable() const
{
    return table;
}


void tcBaseViewer::OnApplyEdits(wxCommandEvent& event)
{
    Save();

    UpdatePage();
}


void tcBaseViewer::OnDeletePlatform(wxCommandEvent& event)
{
    wxString message = wxString::Format("Delete %s?", platformName.c_str());

    wxMessageDialog dialog(this, message, "Confirm Delete", wxOK | wxCANCEL, wxDefaultPosition);
    if (dialog.ShowModal() == wxID_OK)
    {
        if (tcDatabaseManager::Get()->DeleteRecord(table, platformName))
        {
            UpdatePage();
        }
    }
}

void tcBaseViewer::OnDuplicatePlatform(wxCommandEvent& event)
{
    wxString newName;

    tcRenamePlatformDialog* dialog = new tcRenamePlatformDialog(this, true, "Copy Platform", table, platformName, newName);

    int result = dialog->ShowModal();

    if (result == 1)
    {
        UpdatePage();
        platformSelectPanel->SelectPlatform(newName);
    }
}

void tcBaseViewer::OnPageChanged(wxBookCtrlEvent& event)
{
    int page = event.GetSelection();
    if (page >= 0)
    {
        wxNotebookPage* notebookPage = panelNotebook->GetPage(size_t(page));
    }
}

/**
* This picks up page changes for BaseViewer notebook
*/
void tcBaseViewer::OnPageChanging(wxBookCtrlEvent& event)
{
    int page = event.GetSelection();
    if (page >= 0)
    {
        wxNotebookPage* notebookPage = panelNotebook->GetPage(size_t(page));
    }
}


void tcBaseViewer::OnPlatformUpdated(wxCommandEvent& event)
{
    Save();

    UpdatePage();
}

void tcBaseViewer::OnRenamePlatform(wxCommandEvent& event)
{
    wxString newName;

    tcRenamePlatformDialog* dialog = new tcRenamePlatformDialog(this, false, "Rename Platform", table, platformName, newName);

    int result = dialog->ShowModal();

    if (result == 1)
    {
        UpdatePage();
        platformSelectPanel->SelectPlatform(newName);
    }
}


void tcBaseViewer::OnUndoEdits(wxCommandEvent& event)
{
    UpdatePage();
}

void tcBaseViewer::Save()
{
    size_t nPages = panelNotebook->GetPageCount();
    for (size_t n=0; n<nPages; n++)
    {
        tcBasePanel* panel = dynamic_cast<tcBasePanel*>(panelNotebook->GetPage(n));
        if (panel != 0)
        {
            panel->Save();
        }
    }
}

void tcBaseViewer::SetDatabaseClass(const wxString& s)
{
    platformSelectPanel->SelectPlatform(s);
    UpdatePage();
}

/**
* Used to set initial platform to load at startup
*/
void tcBaseViewer::InitializeDatabaseClass(const wxString& s)
{
	platformName = s;
	platformSelectPanel->InitializePlatform(s);
}

void tcBaseViewer::UpdatePage()
{
	if (!tcDatabaseManager::Get()->IsOpen()) return;

    Freeze();

    platformSelectPanel->UpdatePanel();

    platformName = platformSelectPanel->GetPlatform();

    size_t nPages = panelNotebook->GetPageCount();
    for (size_t n=0; n<nPages; n++)
    {
        tcBasePanel* panel = dynamic_cast<tcBasePanel*>(panelNotebook->GetPage(n));
        if (panel != 0)
        {
            panel->SetDatabaseClass(platformName);
        }
    }

    Thaw();
}


tcBaseViewer::tcBaseViewer(wxWindow* parent, const wxString& table_, const wxString& viewerName) 
: tcEditorMainPage(parent, viewerName),
  table(table_)
{
    platformSelectPanel = new tcPlatformSelectPanel(this, table);
    platformSelectPanel->SetSelectionUpdatedId(SELECTION_UPDATED);

    renameButton = new wxButton(this, RENAME_PLATFORM, "RENAME", wxDefaultPosition, wxDefaultSize, 0);
    applyButton = new wxButton(this, APPLY_EDITS, "APPLY EDITS", wxDefaultPosition, wxDefaultSize, 0);
    undoButton = new wxButton(this, UNDO_EDITS, "UNDO EDITS", wxDefaultPosition, wxDefaultSize, 0);
    deleteButton = new wxButton(this, DELETE_PLATFORM, "DELETE", wxDefaultPosition, wxDefaultSize, 0);
    duplicateButton = new wxButton(this, DUPLICATE_PLATFORM, "COPY", wxDefaultPosition, wxDefaultSize, 0);

    wxBoxSizer* sizerButtons = new wxBoxSizer(wxHORIZONTAL);
    sizerButtons->Add(applyButton, 0, wxALL | wxALIGN_LEFT, 5);
    sizerButtons->Add(undoButton, 0, wxALL | wxALIGN_LEFT, 5);
    sizerButtons->Add(renameButton, 0, wxALL | wxALIGN_LEFT, 5);
    sizerButtons->Add(duplicateButton, 0, wxALL | wxALIGN_LEFT, 5);
    sizerButtons->Add(deleteButton, 0, wxALL | wxALIGN_LEFT, 5);


    panelNotebook = new wxNotebook(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNB_BOTTOM, "PanelNotebook");


    wxBoxSizer* sizerTop = new wxBoxSizer(wxVERTICAL);


    int border = 3;
    sizerTop->Add(platformSelectPanel, 0, wxALL | wxALIGN_CENTER | wxEXPAND, border);
    sizerTop->Add(sizerButtons, 0, wxALL | wxALIGN_LEFT, border);
    sizerTop->Add(panelNotebook, 1, wxALL | wxALIGN_CENTER | wxEXPAND, border);

    this->SetSizer(sizerTop);
    //sizerTop->SetSizeHints(this);
}

tcBaseViewer::~tcBaseViewer()
{
}