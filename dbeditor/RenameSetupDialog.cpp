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

#include "RenameSetupDialog.h"
#include "DatabaseManager.h"

#include "wx/stattext.h"
#include "wx/textctrl.h"
#include "wx/sizer.h"

BEGIN_EVENT_TABLE(tcRenameSetupDialog, wxDialog)
    EVT_TEXT(EDIT_CONTROL, tcRenameSetupDialog::OnTextUpdated)
    //EVT_TEXT_ENTER(EDIT_CONTROL, tcRenameSetupDialog::OnTextUpdated)
    EVT_BUTTON(wxID_OK, tcRenameSetupDialog::OnOK)
    EVT_BUTTON(wxID_CANCEL, tcRenameSetupDialog::OnCancel)
END_EVENT_TABLE()


void tcRenameSetupDialog::Init()
{
    // tables to check for name conflict with rename target
    duplicateNameCheckTables.clear();
}


void tcRenameSetupDialog::OnCancel(wxCommandEvent& event)
{
    EndModal(-1);
}

void tcRenameSetupDialog::OnOK(wxCommandEvent& event)
{
    bool success = false;

    tcDatabaseManager* databaseManager = tcDatabaseManager::Get();
    if (newNameValid && databaseManager->IsOpen())
    {
        wxString constraint = wxString::Format("SetupName=\"%s\"", setupName.c_str());
        std::vector<wxArrayString> setupData = databaseManager->GetPlatformTableData("platform_setup", databaseClass, 
                                                                    setupFields, constraint);

        wxString airComplementName;
        wxString magazineLoadoutName;
        wxString launcherLoadoutName;

        wxString newAirComplementName;
        wxString newMagazineLoadoutName;
        wxString newLauncherLoadoutName;

        if (setupData.size() > 0)
        {       
            airComplementName = setupData[0][3];
            magazineLoadoutName = setupData[0][4];
            launcherLoadoutName = setupData[0][5];

            newAirComplementName = newName + wxString("-A");
            newMagazineLoadoutName = newName + wxString("-M");
            newLauncherLoadoutName = newName + wxString("-L");

            setupData[0][0] = newName;
            setupData[0][3] = newAirComplementName;
            setupData[0][4] = newMagazineLoadoutName;
            setupData[0][5] = newLauncherLoadoutName;


            if (makeCopy)
            {
                constraint = wxString::Format("SetupName=\"%s\"", newName.c_str());
            }
        }
        else
        {
            wxASSERT(false); // nothing to rename or duplicate
            return;
        }

        databaseManager->UpdatePlatformTableData("platform_setup", 
                                    databaseClass, setupFields, setupData, constraint);


        if (makeCopy)
        {
            success = databaseManager->DuplicateRecord("launcher_loadout", launcherLoadoutName, newLauncherLoadoutName);
            success = databaseManager->DuplicateRecord("magazine_loadout", magazineLoadoutName, newMagazineLoadoutName);
            success = databaseManager->DuplicateRecord("air_complement", airComplementName, newAirComplementName);
        }
        else
        {
            success = databaseManager->RenameRecord("launcher_loadout", launcherLoadoutName, newLauncherLoadoutName);
            success = databaseManager->RenameRecord("magazine_loadout", magazineLoadoutName, newMagazineLoadoutName);
            success = databaseManager->RenameRecord("air_complement", airComplementName, newAirComplementName);
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

void tcRenameSetupDialog::OnTextUpdated(wxCommandEvent& event)
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
* @return true if setup exists in database
*/
bool tcRenameSetupDialog::SetupExists() const
{
    tcDatabaseManager* databaseManager = tcDatabaseManager::Get();
    if (!databaseManager->IsOpen()) return false;

    wxString constraint = wxString::Format("SetupName=\"%s\"", setupName.c_str());
    std::vector<wxArrayString> setupData = databaseManager->GetPlatformTableData("platform_setup", databaseClass, 
                                                setupFields, constraint);

    return (setupData.size() > 0);
}


tcRenameSetupDialog::tcRenameSetupDialog(wxWindow* parent, bool makeCopy_, const wxString& title, const wxString& databaseClass_, const wxString& originalName, wxString& newName_)
: wxDialog(parent, wxID_ANY, title, wxDefaultPosition, wxSize(250, 500), wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER, "RenamePlatformDialogBox"),
  makeCopy(makeCopy_),  
  databaseClass(databaseClass_),
  setupName(originalName), 
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


    setupFields.clear();
    setupFields.push_back("SetupName");
    setupFields.push_back("InitialYear");
    setupFields.push_back("FinalYear");
    setupFields.push_back("AirComplement");
    setupFields.push_back("MagazineLoadout");
    setupFields.push_back("LauncherLoadout");

    if (SetupExists())
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

tcRenameSetupDialog::~tcRenameSetupDialog()
{
}