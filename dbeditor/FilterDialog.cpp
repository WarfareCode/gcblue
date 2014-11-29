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

#include "FilterDialog.h"
#include "wx/listbox.h"
#include "wx/sizer.h"
#include "DatabaseManager.h"

BEGIN_EVENT_TABLE(tcFilterDialog, wxDialog)
    EVT_BUTTON(wxID_OK, tcFilterDialog::OnOK)
    EVT_BUTTON(wxID_CANCEL, tcFilterDialog::OnCancel)
	EVT_BUTTON(CLEAR_FILTER, tcFilterDialog::OnClearFilter)
    EVT_LISTBOX_DCLICK(-1, tcFilterDialog::OnListDClick)
END_EVENT_TABLE()


void tcFilterDialog::Init()
{
	wxASSERT(listBox != 0);

	tcDatabaseManager* databaseManager = tcDatabaseManager::Get();

	wxArrayString allCountryList = databaseManager->GetGeneralList("country_data", "CountryName");

	listBox->InsertItems(allCountryList, 0);

	// countryList is initialized with currently selected countries, start with selecting these in list box
	for (size_t n=0; n<allCountryList.size(); n++)
	{
		if (countryList.Index(allCountryList[n]) >= 0)
		{
			listBox->Select(n);
		}
	}

	startDate->SetValue(startFilterDate);
	endDate->SetValue(endFilterDate);
	
}


void tcFilterDialog::OnCancel(wxCommandEvent& event)
{
    EndModal(-1);
}

void tcFilterDialog::OnClearFilter(wxCommandEvent& event)
{
	countryList.clear();
	wxArrayInt selectionIndex;
	listBox->GetSelections(selectionIndex);
	for (size_t n=0; n<selectionIndex.size(); n++)
	{
		listBox->Deselect(selectionIndex[n]);
	}

	startFilterDate = wxDateTime(1, wxDateTime::Jan, 1900, 0, 0, 0, 0);
	endFilterDate = wxDateTime(1, wxDateTime::Jan, 2999, 0, 0, 0, 0);

	startDate->SetValue(startFilterDate);
	endDate->SetValue(endFilterDate);
}

void tcFilterDialog::OnListDClick(wxCommandEvent& event)
{
    wxArrayInt selections;
    listBox->GetSelections(selections);

	countryList.clear();
	for (size_t n=0; n<selections.size(); n++)
	{
		wxString s = listBox->GetString((unsigned int)selections[n]);
		countryList.push_back(s);
	}

	startFilterDate = startDate->GetValue();
	endFilterDate = endDate->GetValue();

    EndModal(wxOK);
}

void tcFilterDialog::OnOK(wxCommandEvent& event)
{
    wxArrayInt selections;
    listBox->GetSelections(selections);

	countryList.clear();
	for (size_t n=0; n<selections.size(); n++)
	{
		wxString s = listBox->GetString((unsigned int)selections[n]);
		countryList.push_back(s);
	}

	startFilterDate = startDate->GetValue();
	endFilterDate = endDate->GetValue();

    EndModal(wxOK);
}


tcFilterDialog::tcFilterDialog(wxWindow* parent, const wxString& title, wxArrayString& countryList_, wxDateTime& startFilterDate_, wxDateTime& endFilterDate_)
: wxDialog(parent, wxID_ANY, title, wxDefaultPosition, wxSize(250, 700), wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER, "ListDialogBox"),
  countryList(countryList_), startFilterDate(startFilterDate_), endFilterDate(endFilterDate_)
{
    listBox = new wxListBox(this, wxID_ANY, wxDefaultPosition, wxSize(GetSize().GetWidth(), -1), countryList, wxLB_MULTIPLE, wxDefaultValidator, "ListBoxSelectDlg");



	clearFilters = new wxButton(this, CLEAR_FILTER, "Clear Filter", wxDefaultPosition, wxDefaultSize, 0);

	wxDateTime startDateTime(1, wxDateTime::Jan, 1900);
	wxDateTime endDateTime(1, wxDateTime::Jan, 2999);

	startDate = new wxDatePickerCtrl(this, START_DATE, startDateTime, wxDefaultPosition, wxDefaultSize, wxDP_DEFAULT | wxDP_SHOWCENTURY);
	endDate = new wxDatePickerCtrl(this, END_DATE, endDateTime, wxDefaultPosition, wxDefaultSize, wxDP_DEFAULT | wxDP_SHOWCENTURY);

	wxBoxSizer* dates = new wxBoxSizer(wxHORIZONTAL);
	dates->Add(startDate);
	dates->Add(endDate);


    wxBoxSizer* sizerTop = new wxBoxSizer(wxVERTICAL);
	sizerTop->Add(clearFilters, 0, wxALIGN_CENTER);
	sizerTop->Add(dates, 0, wxALIGN_CENTER);
	
    sizerTop->Add(listBox, 1, wxALL, 5);
    sizerTop->Add(CreateSeparatedButtonSizer(wxOK|wxCANCEL), 0, wxALL, 5);

    SetSizer(sizerTop);

    sizerTop->SetSizeHints(this);
    sizerTop->Fit(this); 

	Init();

	//wxWindow::bypassEraseBkgnd = false;

}

tcFilterDialog::~tcFilterDialog()
{
}