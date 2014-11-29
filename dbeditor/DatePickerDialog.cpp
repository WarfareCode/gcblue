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

#include "DatePickerDialog.h"
#include "DatabaseManager.h"

#include "wx/listbox.h"
#include "wx/radiobox.h"
#include "wx/sizer.h"

BEGIN_EVENT_TABLE(tcDatePickerDialog, wxDialog)
    EVT_BUTTON(wxID_OK, tcDatePickerDialog::OnOK)
    EVT_BUTTON(wxID_CANCEL, tcDatePickerDialog::OnCancel)
END_EVENT_TABLE()



void tcDatePickerDialog::OnCancel(wxCommandEvent& event)
{
    EndModal(wxID_CANCEL);
}


void tcDatePickerDialog::OnOK(wxCommandEvent& event)
{
    int returnCode = wxID_CANCEL;

	wxDateTime selectedDate = calendarControl->GetDate();
	
	// convert back to floating point year
	selection = double(selectedDate.GetYear());
	if (wxDateTime::IsLeapYear(selectedDate.GetYear()))
	{
		selection += (double(selectedDate.GetDayOfYear()) - 0.5) / 366.0;
	}
	else
	{
		selection += (double(selectedDate.GetDayOfYear()) - 0.5) / 365.0;
	}

    returnCode = wxID_OK;

    EndModal(returnCode);
}



tcDatePickerDialog::tcDatePickerDialog(wxWindow* parent, const wxString& title, double& yearVal)
: wxDialog(parent, wxID_ANY, title, wxDefaultPosition, wxSize(250, 500), wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER, "SelectFromTablesDialogBox"),
  selection(yearVal)
{

	double floorYear = floor(selection);
	wxDateTime startDateTime(1, wxDateTime::Jan, int(floorYear), 0, 0, 0, 0);
	double dayOffset = wxDateTime::IsLeapYear(int(floorYear)) ? 366.0 * (selection - floorYear) : 365.0 * (selection - floorYear);
	
	startDateTime.SetToYearDay(1 + int(dayOffset));

	calendarControl = new wxCalendarCtrl(this, wxID_ANY, startDateTime, wxDefaultPosition, wxDefaultSize, wxCAL_SHOW_HOLIDAYS, "CalendarCtrl");

    wxBoxSizer* sizerTop = new wxBoxSizer(wxVERTICAL);
    sizerTop->Add(calendarControl, 2, wxALL, 5);
    sizerTop->Add(wxDialog::CreateButtonSizer(wxOK|wxCANCEL), 0, wxALL, 5);

    SetSizer(sizerTop);

    sizerTop->SetSizeHints(this);
    sizerTop->Fit(this); 

}

tcDatePickerDialog::~tcDatePickerDialog()
{
}