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

#include "RenamePlatformDialog.h"
#include "DatabaseManager.h"

#include "wx/stattext.h"
#include "wx/textctrl.h"
#include "wx/sizer.h"

BEGIN_EVENT_TABLE(tcRenamePlatformDialog, wxDialog)
    EVT_TEXT(EDIT_CONTROL, tcRenamePlatformDialog::OnTextUpdated)
    //EVT_TEXT_ENTER(EDIT_CONTROL, tcRenamePlatformDialog::OnTextUpdated)
    EVT_BUTTON(wxID_OK, tcRenamePlatformDialog::OnOK)
    EVT_BUTTON(wxID_CANCEL, tcRenamePlatformDialog::OnCancel)
END_EVENT_TABLE()


void tcRenamePlatformDialog::Init()
{
    // tables to check for name conflict with rename target
    duplicateNameCheckTables.clear();
    duplicateNameCheckTables.push_back("air");
    duplicateNameCheckTables.push_back("ballistic");
    duplicateNameCheckTables.push_back("cm");
    duplicateNameCheckTables.push_back("ecm");
    duplicateNameCheckTables.push_back("esm");
    duplicateNameCheckTables.push_back("flightport");
    duplicateNameCheckTables.push_back("fueltank");
    duplicateNameCheckTables.push_back("ground");
    duplicateNameCheckTables.push_back("item");
    duplicateNameCheckTables.push_back("missile");
    duplicateNameCheckTables.push_back("optical");
    duplicateNameCheckTables.push_back("radar");
    duplicateNameCheckTables.push_back("ship");
    duplicateNameCheckTables.push_back("simpleair");
    duplicateNameCheckTables.push_back("sonar");
    duplicateNameCheckTables.push_back("sonobuoy");
    duplicateNameCheckTables.push_back("stores");
    duplicateNameCheckTables.push_back("sub");
    duplicateNameCheckTables.push_back("torpedo");

}


void tcRenamePlatformDialog::OnCancel(wxCommandEvent& event)
{
    EndModal(-1);
}

void tcRenamePlatformDialog::OnOK(wxCommandEvent& event)
{
    bool success = false;

    tcDatabaseManager* databaseManager = tcDatabaseManager::Get();
    if (newNameValid && databaseManager->IsOpen())
    {
        if (makeCopy)
        {
            success = databaseManager->DuplicateRecord(platformTable, platformName, newName);
        }
        else
        {
            success = databaseManager->RenameRecord(platformTable, platformName, newName);
        }
    }

    if (success)
    {
        EndModal(1);
    }
    else
    {
        EndModal(0);
    }
}

void tcRenamePlatformDialog::OnTextUpdated(wxCommandEvent& event)
{
    newName = renameEditCtrl->GetValue();
    newName.Trim(true);
    newName.Trim(false);

    tcDatabaseManager* databaseManager = tcDatabaseManager::Get();
    if (!databaseManager->IsOpen())
    {
        newName.clear();
        newNameValid = false;
        return;
    }

    wxString matchingTable;

    if (!databaseManager->PlatformExistsInTableList(duplicateNameCheckTables, newName, matchingTable))
    {
        renameEditCtrl->SetBackgroundColour(wxColour(0xD0FFD0));
        newNameValid = true;
    }
    else
    {
        renameEditCtrl->SetBackgroundColour(wxColour(0xD0D0FF));
        newNameValid = false;
    }

    renameEditCtrl->Refresh(); // otherwise color doesn't get updated until next char is typed
}

/**
* @return true if platform exists in database
*/
bool tcRenamePlatformDialog::PlatformExists() const
{
    tcDatabaseManager* databaseManager = tcDatabaseManager::Get();
    if (!databaseManager->IsOpen()) return false;

    return databaseManager->PlatformExistsInTable(platformTable, platformName);
}


tcRenamePlatformDialog::tcRenamePlatformDialog(wxWindow* parent, bool makeCopy_, const wxString& title, const wxString& table, const wxString& originalName, wxString& newName_)
: wxDialog(parent, wxID_ANY, title, wxDefaultPosition, wxSize(250, 500), wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER, "RenamePlatformDialogBox"),
  makeCopy(makeCopy_),  
  platformTable(table), 
  platformName(originalName), 
  newName(newName_), 
  newNameValid(false)
{

    originalNameText = new wxStaticText(this, wxID_ANY, originalName, wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER, "OriginalText");
    renameEditCtrl = new wxTextCtrl(this, EDIT_CONTROL, "", wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, "NewName");
    wxStaticText* editLabel = new wxStaticText(this, wxID_ANY, "Enter New Name", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);

    wxBoxSizer* sizerTop = new wxBoxSizer(wxVERTICAL);
    
    sizerTop->Add(originalNameText, 0, wxALL, 5);
    sizerTop->Add(renameEditCtrl, 0, wxALL, 5);
    sizerTop->Add(editLabel, 0, wxALL, 5);

    if (PlatformExists())
    {
        sizerTop->Add(CreateSeparatedButtonSizer(wxOK|wxCANCEL), 0, wxALL, 5);
    }
    else
    {
        sizerTop->Add(CreateSeparatedButtonSizer(wxCANCEL), 0, wxALL, 5);
    }

    SetSizer(sizerTop);

    sizerTop->SetSizeHints(this);
    sizerTop->Fit(this); 

    Init();

}

tcRenamePlatformDialog::~tcRenamePlatformDialog()
{
}