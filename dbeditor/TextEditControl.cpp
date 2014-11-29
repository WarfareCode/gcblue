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

#include "TextEditControl.h"
#include "DatabaseManager.h"

#include "wx/textctrl.h"
#include "wx/valtext.h"
#include "wx/sizer.h"
#include "wx/stattext.h"



BEGIN_EVENT_TABLE(tcTextEditControl, tcEditControl)
    EVT_TEXT(TEXT_CTRL, tcTextEditControl::OnTextUpdated)
	EVT_TEXT_ENTER(TEXT_CTRL, tcTextEditControl::OnTextEnter)
END_EVENT_TABLE()



void tcTextEditControl::IndicateChanges()
{
    if (!IsEdited())
    {
        textCtrl->SetBackgroundColour(wxColour(0xFFFFFF));
    }
    else
    {
        textCtrl->SetBackgroundColour(wxColour(0xE0FFE0));
    }
    textCtrl->Refresh();
}


void tcTextEditControl::OnTextUpdated(wxCommandEvent& event)
{
    wxString s = textCtrl->GetValue();
    
    editValue = s;

    IndicateChanges();
}

void tcTextEditControl::OnTextEnter(wxCommandEvent& event)
{
	// do nothing, this was being passed upwards and triggering the application to close
}


void tcTextEditControl::SetValue(const wxString& s)
{
    tcEditControl::SetValue(s);

    textCtrl->SetLabel(editValue);

    textCtrl->SetToolTip(tooltip);

    IndicateChanges();

    CheckReferences();
}

/**
* Set list of cross-reference tables to check this field against
*/
void tcTextEditControl::SetCrossReference(const wxArrayString& ref)
{
    crossReferenceTables = ref;
}


void tcTextEditControl::CreateControls(int textCtrlStyle, int textCtrlSizerFlags, int labelTextStyle, int labelTextSizerFlags)
{
    textCtrl = new wxTextCtrl(this, TEXT_CTRL, "", wxDefaultPosition, wxSize(controlWidth, 20), textCtrlStyle, wxDefaultValidator);

    labelText = new wxStaticText(this, wxID_ANY, label, wxDefaultPosition, wxSize(labelWidth, 20), labelTextStyle);

    wxBoxSizer* sizerTop = new wxBoxSizer(wxHORIZONTAL);
  
    int border = 3;

    sizerTop->Add(labelText, 0, labelTextSizerFlags, border);
    sizerTop->Add(textCtrl, 1, textCtrlSizerFlags, border);
    
    SetSizer(sizerTop);

    //sizerTop->Fit(this); 
}

void tcTextEditControl::CheckReferences()
{
    if (crossReferenceTables.size() == 0) return;

    tcDatabaseManager* databaseManager = tcDatabaseManager::Get();

    wxString matchingTable;
    bool referenceFound = databaseManager->PlatformExistsInTableList(crossReferenceTables, editValue, matchingTable);
    if (referenceFound)
    {
        textCtrl->SetForegroundColour(wxColour(0, 0, 0));
        textCtrl->SetFont(normalFont);
    }
    else
    {
        textCtrl->SetForegroundColour(wxColour(120, 0, 0));
        textCtrl->SetFont(errorFont);
    }
}


void tcTextEditControl::UpdateControl()
{
    tcEditControl::UpdateControl();
}


tcTextEditControl::tcTextEditControl(wxWindow* parent, const wxSize& size, 
                                   const wxString& fieldName_, const wxString& label_) 
: tcEditControl(parent, size, fieldName_, label_) 
{
    int textCtrlStyle = wxTE_PROCESS_ENTER;
    int textCtrlSizerFlags = wxALL | wxEXPAND;
    int labelTextStyle = 0;
    int labelTextSizerFlags = wxALL;

    CreateControls(textCtrlStyle, textCtrlSizerFlags, labelTextStyle, labelTextSizerFlags);
}

tcTextEditControl::tcTextEditControl(wxWindow* parent, const wxSize& size, 
                                   const wxString& fieldName_, const wxString& label_, 
                                   int textCtrlStyle, int textCtrlSizerFlags, int labelTextStyle, int labelTextSizerFlags) 
: tcEditControl(parent, size, fieldName_, label_) 
{
    CreateControls(textCtrlStyle, textCtrlSizerFlags, labelTextStyle, labelTextSizerFlags);
}

tcTextEditControl::~tcTextEditControl()
{
}