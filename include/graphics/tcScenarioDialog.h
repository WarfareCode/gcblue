/**
**  @file tcTextDialog.h 
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


#ifndef _SCENARIODIALOG_H_
#define _SCENARIODIALOG_H_

#if _MSC_VER > 1000
#pragma once
#endif 

#include "wx/wx.h" 
#include "wx/dialog.h"
#include "wx/textctrl.h"
#include "wx/listctrl.h"
#include "wx/combobox.h"
#include <vector>

class wxCalendarCtrl;

/**
* Modal dialog with text box for data entry
*/
class tcScenarioDialog  : public wxDialog 
{
public:
    wxTextCtrl* scenarioName;

    std::vector<wxComboBox*> countrySelection;

    wxCalendarCtrl* calendar;

	wxTextCtrl* scenarioDescription;

    const wxDateTime& GetScenarioDate() const;
	wxString GetScenarioDescriptionText();
    wxString GetScenarioNameText();
    void GetSideList(wxArrayString& sideList);


	tcScenarioDialog( wxWindow* parent, wxWindowID id, const wxString& title,
                  const wxString& startText,
	              const wxPoint & pos = wxDefaultPosition,
	              const wxSize & size = wxDefaultSize,
	              long style = wxDEFAULT_DIALOG_STYLE);
    virtual ~tcScenarioDialog();

private:
    enum {MAX_COUNTRIES=3};
 
	void OnOk( wxCommandEvent & event );
};

#endif


