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
#ifndef _DATEPICKERDIALOG_H_
#define _DATEPICKERDIALOG_H_

#include "wx/dialog.h"
#include "wx/calctrl.h"


/**
* Dialog to select one record from set of tables
* Table (if more than one) is selected with radio button
*/
class tcDatePickerDialog : public wxDialog
{
public:
    void SetConstraint(const wxString& s);
    void UpdateListWithTable(const wxString& table);

    tcDatePickerDialog(wxWindow* parent, const wxString& title, double& yearVal);
    virtual ~tcDatePickerDialog();

private:
    double& selection;

    wxCalendarCtrl* calendarControl;

    void OnOK(wxCommandEvent& event);
    void OnCancel(wxCommandEvent& event);
    void OnListDClick(wxCommandEvent& event);
    void OnRadioBoxClick(wxCommandEvent& event);



    DECLARE_EVENT_TABLE()
};



#endif