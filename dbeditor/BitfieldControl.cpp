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

#include "BitfieldControl.h"

#include "wx/checkbox.h"
#include "wx/valtext.h"
#include "wx/sizer.h"
#include "wx/stattext.h"



BEGIN_EVENT_TABLE(tcBitfieldControl, tcEditControl)
    EVT_CHECKBOX(-1, tcBitfieldControl::OnCheckUpdated)
END_EVENT_TABLE()





void tcBitfieldControl::OnCheckUpdated(wxCommandEvent& event)
{
    wxASSERT(checkBoxes.size() == checkValues.size());

    int value = 0;
    for (size_t n=0; n<checkBoxes.size(); n++)
    {
        if (checkBoxes[n]->GetValue())
        {
            value += checkValues[n];
        }
        checkBoxes[n]->Refresh();
    }

    editValue.Printf("%d", value);
}





void tcBitfieldControl::SetValue(const wxString& s)
{
    long val = 0;
    if (s.ToLong(&val))
    {
        for (size_t n=0; n<checkBoxes.size(); n++)
        {
            bool state_n = (val & checkValues[n]) != 0;
            checkBoxes[n]->SetValue(state_n);
            checkBoxes[n]->Refresh();
        }

        tcEditControl::SetValue(s);
    }
    else
    {
        wxASSERT(false); // not an integer
        for (size_t n=0; n<checkBoxes.size(); n++)
        {
            checkBoxes[n]->SetValue(false);
            checkBoxes[n]->Refresh();
        }
        tcEditControl::SetValue("0");
    }

}



tcBitfieldControl::tcBitfieldControl(wxWindow* parent, const wxSize& size, const wxString& fieldName_, const wxString& label_ ,
        const wxArrayString& checkLabels_, const std::vector<int>& checkValues_)
: tcEditControl(parent, size, fieldName_, "bitfield"),
  checkValues(checkValues_)
{
    wxSize checkSize(35, 16);
    wxSize checkSpacing(40, 0);
    wxPoint pos(0, 0);

    wxBoxSizer* sizerTop = new wxBoxSizer(wxHORIZONTAL);
    int checkStyle = 0;
    int checkSizerStyle = wxRIGHT ;
    int border = 5;
    int checkBorder = 5;

    int labelTextStyle = 0;
    int labelTextSizerStyle = wxALL;
    labelText = new wxStaticText(this, wxID_ANY, label_, wxDefaultPosition, wxSize(labelWidth, 20), labelTextStyle);

    sizerTop->Add(labelText, 0, labelTextSizerStyle, border);

    for (size_t n=0; n<checkLabels_.size(); n++)
    {
        wxCheckBox* checkn = new wxCheckBox(this, n, checkLabels_[n], pos, checkSize, checkStyle, wxDefaultValidator);
        checkn->Fit();
        checkBoxes.push_back(checkn);
        sizerTop->Add(checkn, 0, checkSizerStyle, checkBorder);

        pos += wxSize(checkn->GetSize().GetWidth(), 0);
    }

    SetSizer(sizerTop);

    sizerTop->SetSizeHints(this);
    sizerTop->Fit(this); 

}



tcBitfieldControl::~tcBitfieldControl()
{
}