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
#ifndef _CHECKBOXCONTROL_H_
#define _CHECKBOXCONTROL_H_

#include "EditControl.h"

#include "wx/panel.h"

class wxCheckBox;
class wxStaticText;

/**
* Class for updating a single field of database record
*/
class tcCheckBoxControl : public tcEditControl
{
public:

    virtual void SetValue(const wxString& s);

    void SetLabelWidth(int val);
    void SetControlWidth(int val);

    tcCheckBoxControl(wxWindow* parent, const wxSize& size, const wxString& fieldName_, const wxString& label_);
    tcCheckBoxControl(wxWindow* parent, const wxSize& size, const wxString& fieldName_, const wxString& label_, 
                      int textCtrlStyle, int textCtrlSizerFlags, int labelTextStyle, int labelTextSizerFlags);
    virtual ~tcCheckBoxControl();

private:
    enum {CHECKBOX_CTRL};
    wxCheckBox* checkBox;
    wxStaticText* labelText;


    void OnCheckUpdated(wxCommandEvent& event);
    void CreateControls(int textCtrlStyle, int textCtrlSizerFlags, int labelTextStyle, int labelTextSizerFlags);

    DECLARE_EVENT_TABLE()
};

#endif