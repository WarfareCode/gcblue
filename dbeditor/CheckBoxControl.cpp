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

#include "CheckBoxControl.h"

#include "wx/checkbox.h"
#include "wx/valtext.h"
#include "wx/sizer.h"
#include "wx/stattext.h"



BEGIN_EVENT_TABLE(tcCheckBoxControl, tcEditControl)
    EVT_CHECKBOX(CHECKBOX_CTRL, tcCheckBoxControl::OnCheckUpdated)
END_EVENT_TABLE()





void tcCheckBoxControl::OnCheckUpdated(wxCommandEvent& event)
{
    bool checked = checkBox->GetValue();
    
    editValue = checked ? "1" : "0";

    //if (!IsEdited())
    //{
    //    checkBox->SetBackgroundColour(wxColour(0xFFFFFF));
    //}
    //else
    //{
    //    checkBox->SetBackgroundColour(wxColour(0xE0FFE0));
    //}
    checkBox->Refresh();

}


void tcCheckBoxControl::SetControlWidth(int val) 
{
    wxSize current(checkBox->GetSize());
    checkBox->SetSize(wxSize(val, current.GetHeight()));
}



void tcCheckBoxControl::SetLabelWidth(int val) 
{
    wxSize current(labelText->GetSize());
    labelText->SetSize(wxSize(val, current.GetHeight()));
}



void tcCheckBoxControl::SetValue(const wxString& s)
{
    tcEditControl::SetValue(s);

    bool state = (s != "0");

    checkBox->SetValue(state);
    checkBox->Update();
}

void tcCheckBoxControl::CreateControls(int textCtrlStyle, int textCtrlSizerFlags, int labelTextStyle, int labelTextSizerFlags)
{
    checkBox = new wxCheckBox(this, CHECKBOX_CTRL, "", wxDefaultPosition, wxSize(-1, -1), textCtrlStyle, wxDefaultValidator);

    labelText = new wxStaticText(this, wxID_ANY, label, wxDefaultPosition, wxSize(labelWidth, -1), labelTextStyle);

    wxBoxSizer* sizerTop = new wxBoxSizer(wxHORIZONTAL);
  
    int border = 3;

    sizerTop->Add(labelText, 0, labelTextSizerFlags, border);
    sizerTop->Add(checkBox, 1, textCtrlSizerFlags, border);
    
    SetSizer(sizerTop);

    sizerTop->SetSizeHints(this);
    sizerTop->Fit(this); 
}

tcCheckBoxControl::tcCheckBoxControl(wxWindow* parent, const wxSize& size, 
                                   const wxString& fieldName_, const wxString& label_) 
: tcEditControl(parent, size, fieldName_, label_) 
{
    int textCtrlStyle = 0;
    int textCtrlSizerFlags = wxALL | wxEXPAND;
    int labelTextStyle = 0;
    int labelTextSizerFlags = wxALL;

    CreateControls(textCtrlStyle, textCtrlSizerFlags, labelTextStyle, labelTextSizerFlags);
}

tcCheckBoxControl::tcCheckBoxControl(wxWindow* parent, const wxSize& size, 
                                   const wxString& fieldName_, const wxString& label_, 
                                   int textCtrlStyle, int textCtrlSizerFlags, int labelTextStyle, int labelTextSizerFlags) 
: tcEditControl(parent, size, fieldName_, label_) 
{
    CreateControls(textCtrlStyle, textCtrlSizerFlags, labelTextStyle, labelTextSizerFlags);
}

tcCheckBoxControl::~tcCheckBoxControl()
{
}