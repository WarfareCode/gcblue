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

#include "ListSelectDialog.h"
#include "wx/listbox.h"
#include "wx/sizer.h"

BEGIN_EVENT_TABLE(tcListSelectDialog, wxDialog)
    EVT_BUTTON(wxID_OK, tcListSelectDialog::OnOK)
    EVT_BUTTON(wxID_CANCEL, tcListSelectDialog::OnCancel)
    EVT_LISTBOX_DCLICK(-1, tcListSelectDialog::OnListDClick)
END_EVENT_TABLE()



void tcListSelectDialog::OnCancel(wxCommandEvent& event)
{
    EndModal(-1);
}

void tcListSelectDialog::OnListDClick(wxCommandEvent& event)
{
    int returnCode = -1;

    wxArrayInt selections;
    if (listBox->GetSelections(selections) > 0)
    {
        returnCode = selections[0];
    }

    EndModal(returnCode);
}

void tcListSelectDialog::OnOK(wxCommandEvent& event)
{
    int returnCode = -1;

    wxArrayInt selections;
    if (listBox->GetSelections(selections) > 0)
    {
        returnCode = selections[0];
    }

    EndModal(returnCode);
}


tcListSelectDialog::tcListSelectDialog(wxWindow* parent, const wxString& title, const wxArrayString& selectionList_)
: wxDialog(parent, wxID_ANY, title, wxDefaultPosition, wxSize(250, 500), wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER, "ListDialogBox"),
  selectionList(selectionList_)
{
    listBox = new wxListBox(this, wxID_ANY, wxDefaultPosition, wxSize(GetSize().GetWidth(), -1), selectionList, 0, wxDefaultValidator, "ListBoxSelectDlg");


    wxBoxSizer* sizerTop = new wxBoxSizer(wxVERTICAL);
    sizerTop->Add(listBox, 1, wxALL, 5);
    sizerTop->Add(CreateSeparatedButtonSizer(wxOK|wxCANCEL), 0, wxALL, 5);

    SetSizer(sizerTop);

    sizerTop->SetSizeHints(this);
    sizerTop->Fit(this); 

}

tcListSelectDialog::~tcListSelectDialog()
{
}