/** 
**  @file tcScenarioDialog.cpp 
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

#include "stdwx.h"
#include <wx/textctrl.h>
#include "tcScenarioDialog.h"
#include "tcDatabase.h"
#include "wx/datetime.h"
#include "wx/calctrl.h" // needs wx.._core.lib and wx.._adv.lib

#ifdef _DEBUG
#define new DEBUG_NEW
#endif 


const wxDateTime& tcScenarioDialog::GetScenarioDate() const
{
	static wxDateTime result;

	result = calendar->GetDate();
    return result;
}

wxString tcScenarioDialog::GetScenarioDescriptionText()
{
    wxString s;
    for (int n=0; n<scenarioDescription->GetNumberOfLines(); n++)
    {
        s += scenarioDescription->GetLineText(n);
        s += '\n';
    }

    return s;
}

wxString tcScenarioDialog::GetScenarioNameText()
{
    wxString s = scenarioName->GetValue();

    return s;
}

void tcScenarioDialog::GetSideList(wxArrayString& sideList)
{
    sideList.clear();

    for (size_t n=0; n<countrySelection.size(); n++)
    {
        wxString s = countrySelection[n]->GetValue();
        if (s.size() > 0) sideList.push_back(s);
    }
}


tcScenarioDialog::tcScenarioDialog (wxWindow * parent, wxWindowID id, const wxString & title,
                            const wxString& startText,
                            const wxPoint & position, const wxSize & size, long style)
:  wxDialog( parent, id, title, position, size, style)
{
	wxString dimensions = "", s;
	wxPoint p(10, 10);
	wxSize  sz;
 

    // scenario name
    scenarioName = new wxTextCtrl(this, -1, startText, wxPoint(0, 0), wxSize(200, 20), 0);
    scenarioName->SetValue("Enter scenario name.");

    // side selection
    wxArrayString sideChoices;
    database::tcDatabase* database = database::tcDatabase::Get();
    database->GetCountryList(sideChoices);
    sideChoices.push_back("");

    wxBoxSizer* sideSizer = new wxBoxSizer(wxHORIZONTAL);    

    for (size_t n=0; n<MAX_COUNTRIES; n++)
    {
        wxComboBox* cb = new wxComboBox(this, -1, "", wxPoint(0, 0), wxSize(90, 30), sideChoices, wxCB_READONLY);
        countrySelection.push_back(cb);
        sideSizer->Add(cb, 0, wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL );
    }
    
    size_t nSides = sideChoices.size();
    if ((nSides > 1) && (countrySelection.size() >= 2))
    {
        countrySelection[0]->SetValue(sideChoices[rand() % (nSides - 1)]);
        countrySelection[1]->SetValue(sideChoices[rand() % (nSides - 1)]);
    }
    else
    {
        wxASSERT(false);
    }

    // scenario date
    wxDateTime startTime(13, wxDateTime::Apr, 1990, 8, 0, 0);
    calendar = new wxCalendarCtrl(this, wxID_ANY, startTime, wxDefaultPosition, wxDefaultSize, wxCAL_SHOW_HOLIDAYS, "CalendarScenario");


    // scenario description
	scenarioDescription = new wxTextCtrl(this, -1, "", wxPoint(0, 0), wxSize(20, 20), wxTE_MULTILINE);
    scenarioDescription->SetValue("Enter description of scenario.");

    wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(new wxButton(this, wxID_OK, _("OK"), wxPoint(0, 0), wxDefaultSize));
    buttonSizer->Add(new wxButton(this, wxID_CANCEL, _("Cancel"), wxPoint(0, 0), wxDefaultSize));

    // main sizer
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    
    mainSizer->Add(new wxStaticText(this, wxID_ANY, "Scenario Name"), 0, wxALIGN_CENTER);
    mainSizer->Add(scenarioName, 0, wxALIGN_CENTER);
    mainSizer->AddSpacer(10);
    mainSizer->Add(new wxStaticText(this, wxID_ANY, "Sides"), 0, wxALIGN_CENTER);
    mainSizer->Add(sideSizer, 0, wxALIGN_CENTER);
    mainSizer->AddSpacer(10);
    mainSizer->Add(new wxStaticText(this, wxID_ANY, "Scenario Date"), 0, wxALIGN_CENTER);
    mainSizer->Add(calendar, 0, wxALIGN_CENTER);
    mainSizer->AddSpacer(10);
    mainSizer->Add(scenarioDescription, 1, wxEXPAND);
    mainSizer->AddSpacer(10);
    mainSizer->Add(buttonSizer, 0, wxALIGN_CENTER);

    SetSizer(mainSizer);
}

tcScenarioDialog::~tcScenarioDialog()
{
}