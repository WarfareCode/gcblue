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

#include "SelectFromTablesDialog.h"
#include "DatabaseManager.h"

#include "wx/listbox.h"
#include "wx/radiobox.h"
#include "wx/sizer.h"

BEGIN_EVENT_TABLE(tcSelectFromTablesDialog, wxDialog)
    EVT_BUTTON(wxID_OK, tcSelectFromTablesDialog::OnOK)
    EVT_BUTTON(wxID_CANCEL, tcSelectFromTablesDialog::OnCancel)
    EVT_LISTBOX_DCLICK(-1, tcSelectFromTablesDialog::OnListDClick)
    EVT_RADIOBOX(-1, tcSelectFromTablesDialog::OnRadioBoxClick)
END_EVENT_TABLE()



const wxString& tcSelectFromTablesDialog::GetActiveTable() const
{
	return activeTable;
}


void tcSelectFromTablesDialog::OnCancel(wxCommandEvent& event)
{
    EndModal(wxID_CANCEL);
}

void tcSelectFromTablesDialog::OnListDClick(wxCommandEvent& event)
{
    int returnCode = wxID_CANCEL;

    wxArrayInt selections;
    if (listBox->GetSelections(selections) > 0)
    {
        selection = listBox->GetStringSelection();
        returnCode = wxID_OK;
    }

    EndModal(returnCode);
}

void tcSelectFromTablesDialog::OnOK(wxCommandEvent& event)
{
    int returnCode = wxID_CANCEL;

    wxArrayInt selections;
    if (listBox->GetSelections(selections) > 0)
    {
        selection = listBox->GetStringSelection();
        returnCode = wxID_OK;
    }

    EndModal(returnCode);
}

void tcSelectFromTablesDialog::OnRadioBoxClick(wxCommandEvent& event)
{
    wxString radioString(event.GetString());

	activeTable = radioString;

    UpdateListWithTable(activeTable);
}

void tcSelectFromTablesDialog::SetConstraint(const wxString& s)
{
    constraint = s;
}

void tcSelectFromTablesDialog::UpdateListWithTable(const wxString& table)
{
    tcDatabaseManager* databaseManager = tcDatabaseManager::Get();

    wxArrayString selectionList = databaseManager->GetPlatformList(table, constraint);

    listBox->Set(selectionList);
}

tcSelectFromTablesDialog::tcSelectFromTablesDialog(wxWindow* parent, const wxString& title, const wxArrayString& tableList_, wxString& selection_)
: wxDialog(parent, wxID_ANY, title, wxDefaultPosition, wxSize(250, 500), wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER, "SelectFromTablesDialogBox"),
  tableList(tableList_),
  selection(selection_),
  constraint("")
{
    listBox = new wxListBox(this, wxID_ANY, wxDefaultPosition, wxSize(GetSize().GetWidth(), 300), 0, NULL, wxLB_SINGLE, wxDefaultValidator, "ListBoxSelectDlg");

    radioBox = new wxRadioBox(this, wxID_ANY, "TABLE", wxDefaultPosition, wxSize(GetSize().GetWidth(), -1), 
        tableList, 3, wxHORIZONTAL, wxDefaultValidator, "RadioBox");

	activeTable = radioBox->GetStringSelection();
    UpdateListWithTable(activeTable);

    wxBoxSizer* sizerTop = new wxBoxSizer(wxVERTICAL);
    sizerTop->Add(listBox, 2, wxALL, 5);
    sizerTop->Add(radioBox, 0, wxALL, 5);
    sizerTop->Add(wxDialog::CreateButtonSizer(wxOK|wxCANCEL), 0, wxALL, 5);

    SetSizer(sizerTop);

    sizerTop->SetSizeHints(this);
    sizerTop->Fit(this); 

}

tcSelectFromTablesDialog::~tcSelectFromTablesDialog()
{
}