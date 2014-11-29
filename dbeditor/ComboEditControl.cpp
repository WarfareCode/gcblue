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

#include "ComboEditControl.h"
#include "DatabaseManager.h"

#include "wx/combobox.h"
#include "wx/valtext.h"
#include "wx/sizer.h"
#include "wx/stattext.h"



BEGIN_EVENT_TABLE(tcComboEditControl, tcEditControl)
    EVT_TEXT(COMBO_CTRL, tcComboEditControl::OnTextUpdated)
END_EVENT_TABLE()





/**
* Alter graphics if edited value has changed from initial value to
* cue user
*/
void tcComboEditControl::IndicateChanges()
{
    if (!IsEdited() || infoOnly)
    {
        comboCtrl->SetBackgroundColour(wxColour(0xFFFFFF));
    }
    else
    {
        comboCtrl->SetBackgroundColour(wxColour(0xE0FFE0));
    }
    comboCtrl->Refresh();
}

const wxString& tcComboEditControl::LabelToValue(const wxString& s) const
{
    static wxString error("");

    wxASSERT(databaseValues.size() == displayLabels.size());
    wxASSERT(databaseValues.size() > 0);

    for (size_t n=0; n<displayLabels.size(); n++)
    {
        if (displayLabels[n] == s) return databaseValues[n];
    }

    return error;
}


void tcComboEditControl::OnTextUpdated(wxCommandEvent& event)
{
    wxString s = LabelToValue(comboCtrl->GetValue());
    
    editValue = s;

    IndicateChanges();

    if (commandId > 0)
    {
	    wxCommandEvent command(wxEVT_COMMAND_BUTTON_CLICKED, commandId);    
	    command.SetEventObject(this);    
        command.SetString(editValue);
        command.SetId(commandId);
	    AddPendingEvent(command);
    }
}

void tcComboEditControl::SetCommand(long val)
{
    commandId = val;
}

void tcComboEditControl::SetUpdateFromDatabaseReferences(const wxArrayString& tableList, const wxArrayString& fieldList)
{
    updateMode = DATABASE_REFERENCE;

    referenceTables = tableList;
    referenceFields = fieldList;
}


void tcComboEditControl::SetUpdateFromDatabaseTable(const wxString& table)
{
    updateMode = DATABASE_TABLE;

    updateTable = table;
}

void tcComboEditControl::SetValue(const wxString& s)
{
    tcEditControl::SetValue(s);

    comboCtrl->SetValue(ValueToLabel(editValue));

    IndicateChanges();
}

void tcComboEditControl::SetValuesAndLabels(const wxArrayString& values, const wxArrayString& labels)
{
    databaseValues = values;
    displayLabels = labels;

    comboCtrl->Clear();
    comboCtrl->Append(labels);
}

void tcComboEditControl::UpdateControl()
{
    switch (updateMode)
    {
    case NORMAL:
        return;
        break;
    case DATABASE_TABLE:
        {
            comboCtrl->Freeze();

            databaseValues = tcDatabaseManager::Get()->GetPlatformList(updateTable);
            displayLabels = databaseValues;

            comboCtrl->Clear();
            comboCtrl->Append(displayLabels);

            comboCtrl->Thaw();
        }
        break;
    case DATABASE_REFERENCE:
        {
            databaseValues.clear();

            comboCtrl->Freeze();

            tcDatabaseManager* databaseManager = tcDatabaseManager::Get();
            for (size_t n=0; n<referenceTables.size(); n++)
            {
                wxArrayString results = databaseManager->GetReferences(referenceTables[n], referenceFields[n], databaseClass);
                
                if (results.size() > 0)
                {
                    results.Sort();
                    for (size_t k=0; k<results.size(); k++)
                    {
                        databaseValues.push_back(results[k] + wxString::Format(" (%s)", referenceTables[n].c_str()));
                    }
                }
            }

            // remove duplicates from databaseValues
            wxArrayString temp;
            for (size_t k=0; k<databaseValues.size(); k++)
            {
                if ((k == 0) || (databaseValues[k] != databaseValues[k-1]))
                {
                    temp.push_back(databaseValues[k]);
                }
            }
            databaseValues = temp;

            displayLabels = databaseValues;

            comboCtrl->Clear();
            
            wxString summary;
            summary.Printf("%d reference", displayLabels.size());
            if (displayLabels.size() != 1) summary += "s";

            comboCtrl->Append(summary);
            comboCtrl->Append(displayLabels);
            comboCtrl->SetValue(summary);
            comboCtrl->Thaw();
        }
        break;
    default:
        wxASSERT(false);
    }
}


const wxString& tcComboEditControl::ValueToLabel(const wxString& s) const
{
    static wxString error("");

    wxASSERT(databaseValues.size() == displayLabels.size());

    for (size_t n=0; n<databaseValues.size(); n++)
    {
        if (databaseValues[n] == s) return displayLabels[n];
    }

    return error;
}



tcComboEditControl::tcComboEditControl(wxWindow* parent, const wxSize& size, 
                                   const wxString& fieldName_, const wxString& label_, const wxArrayString& values, const wxArrayString& labels) 
: tcEditControl(parent, size, fieldName_, label_),
  databaseValues(values),
  displayLabels(labels),
  updateMode(NORMAL),
  commandId(0)
{
    long style = wxCB_DROPDOWN | wxCB_READONLY;
    
    comboCtrl = new wxComboBox(this, COMBO_CTRL, "", wxDefaultPosition, wxSize(controlWidth, 20), displayLabels, style, wxDefaultValidator, "ComboBox");

    wxStaticText* labelText = new wxStaticText(this, wxID_ANY, label, wxDefaultPosition, wxSize(labelWidth, 20), 0);

    wxBoxSizer* sizerTop = new wxBoxSizer(wxHORIZONTAL);
    
    int labelFlags = (size.GetHeight() < 70) ? wxALL : wxALL | wxALIGN_CENTER_VERTICAL;

    sizerTop->Add(labelText, 0, labelFlags, 3);
    sizerTop->Add(comboCtrl, 1, wxALL , 3);
    
    SetSizer(sizerTop);

    sizerTop->SetSizeHints(this);
    sizerTop->Fit(this); 
}

tcComboEditControl::~tcComboEditControl()
{
}