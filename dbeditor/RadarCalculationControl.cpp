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

#include "RadarCalculationControl.h"
#include "DatabaseManager.h"

#include "wx/textctrl.h"
#include "wx/valtext.h"
#include "wx/sizer.h"
#include "wx/stattext.h"

#include "tcDatabase.h"
#include "tcRadarDBObject.h"


BEGIN_EVENT_TABLE(tcRadarCalculationControl, tcEditControl)
    EVT_TEXT(TEXT_CTRL, tcRadarCalculationControl::OnTextUpdated)
END_EVENT_TABLE()

using namespace database;

void tcRadarCalculationControl::IndicateChanges()
{

}

bool tcRadarCalculationControl::IsEdited() const
{
    return false;
}


void tcRadarCalculationControl::OnTextUpdated(wxCommandEvent& event)
{
    wxString s = textCtrl->GetValue();
    
    editValue = s;

    IndicateChanges();
}



void tcRadarCalculationControl::SetValue(const wxString& s)
{
    tcEditControl::SetValue(s);

    textCtrl->SetLabel(editValue);

    IndicateChanges();

    CheckReferences();
}

/**
* Set list of cross-reference tables to check this field against
*/
void tcRadarCalculationControl::SetCrossReference(const wxArrayString& ref)
{
    crossReferenceTables = ref;
}


void tcRadarCalculationControl::CreateControls(int textCtrlStyle, int textCtrlSizerFlags, int labelTextStyle, int labelTextSizerFlags)
{
    textCtrl = new wxTextCtrl(this, TEXT_CTRL, "", wxDefaultPosition, wxSize(controlWidth, 20), textCtrlStyle, wxDefaultValidator);

    labelText = new wxStaticText(this, wxID_ANY, label, wxDefaultPosition, wxSize(labelWidth, 20), labelTextStyle);

    wxBoxSizer* sizerTop = new wxBoxSizer(wxHORIZONTAL);
  
    int border = 3;

    sizerTop->Add(labelText, 0, labelTextSizerFlags, border);
    sizerTop->Add(textCtrl, 1, textCtrlSizerFlags, border);
    
    SetSizer(sizerTop);

    textCtrl->SetEditable(false);

    //sizerTop->Fit(this); 
}

void tcRadarCalculationControl::CheckReferences()
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

void tcRadarCalculationControl::SetCalculationType(const wxString& s)
{
    calculationType = s;
}

void tcRadarCalculationControl::SetDatabaseClass(const wxString& s)
{
    tcEditControl::SetDatabaseClass(s);
}

void tcRadarCalculationControl::UpdateCalculation()
{
    tcDatabase* database = tcDatabase::Get();
	
	tcDatabaseManager* databaseManager = tcDatabaseManager::Get();
	sqlite3x::sqlite3_connection& sqlConnection = databaseManager->GetConnection();

	tcDatabaseObject* radarData1 = database->GetObject(databaseClass.ToStdString());
	tcRadarDBObject* radarData = dynamic_cast<tcRadarDBObject*>(radarData1);

    // new entry, not saved??
    if (radarData == 0)
    {
        textCtrl->SetLabel("Not Available");
        return;
    }

    if (calculationType == "gain")
    {
        labelText->SetLabel("Antenna Gain (dBi)");
        textCtrl->SetLabel(wxString::Format("%.1f", radarData->antennaGain_dBi));

        if ((radarData->antennaGain_dBi >= 10.0f) && (radarData->antennaGain_dBi <= 60.0f))
        {
            textCtrl->SetBackgroundColour(wxColour(180, 255, 180));
        }
        else
        {
            textCtrl->SetBackgroundColour(wxColour(255, 255, 180));
            textCtrl->SetToolTip("Gain is out of normal range: 10 to 60 dBi");
        }
    }
    else if (calculationType == "erpavg")
    {
        labelText->SetLabel("ERP Avg Min (dBW)");
        const float c_4pi = 12.56637;
        const float kTFL = 1.38e-23 * 300 * 10;
        float lambda_m = 299792458.0 / radarData->averageFrequency_Hz;
        float erpMin_W = powf(1000.0f*radarData->mfRefRange_km, 4.0f) * powf(c_4pi, 3.0f) * kTFL /
            (radarData->antennaGain * lambda_m * lambda_m * radarData->cpi_s);
        float erpMin_dBW = 10*log10f(erpMin_W);
        textCtrl->SetLabel(wxString::Format("%.1f", erpMin_dBW));

        if (radarData->ERPaverage_dBW > (erpMin_dBW + 15.0f))
        {
            textCtrl->SetBackgroundColour(wxColour(180, 180, 255));
            textCtrl->SetToolTip("Average power is too high based on range equation and other parameters");
        }
        else if (radarData->ERPaverage_dBW < erpMin_dBW)
        {
            textCtrl->SetBackgroundColour(wxColour(255, 180, 180));
            textCtrl->SetToolTip("Average power is too low based on range equation and other parameters");
        }
        else
        {
            textCtrl->SetBackgroundColour(wxColour(180, 255, 180));
        }
    }
    else if (calculationType == "losses")
    {
        labelText->SetLabel("Noise+Losses (dB)");
        float lambda2 = 0;
        float FL_dB = radarData->CalculateFL(lambda2);
        textCtrl->SetLabel(wxString::Format("%.1f", FL_dB));
        
        if (FL_dB > 22.0f)
        {
            textCtrl->SetBackgroundColour(wxColour(180, 180, 255));
            textCtrl->SetToolTip("Noise figure and losses too high based on range equation and other parameters");
        }
        else if (FL_dB < 8.0f)
        {
            textCtrl->SetBackgroundColour(wxColour(255, 180, 180));
            textCtrl->SetToolTip("Noise figure and losses too low based on range equation and other parameters");
        }
        else
        {
            textCtrl->SetBackgroundColour(wxColour(180, 255, 180));
        }
    }
}

void tcRadarCalculationControl::UpdateControl()
{
    UpdateCalculation();
}


tcRadarCalculationControl::tcRadarCalculationControl(wxWindow* parent, const wxSize& size, 
                                   const wxString& fieldName_, const wxString& label_) 
: tcEditControl(parent, size, fieldName_, label_),
  calculationType("gain")
{
    int textCtrlStyle = 0;
    int textCtrlSizerFlags = wxALL | wxEXPAND;
    int labelTextStyle = 0;
    int labelTextSizerFlags = wxALL;

    CreateControls(textCtrlStyle, textCtrlSizerFlags, labelTextStyle, labelTextSizerFlags);

    SetInfoOnly(true);
}

tcRadarCalculationControl::tcRadarCalculationControl(wxWindow* parent, const wxSize& size, 
                                   const wxString& fieldName_, const wxString& label_, 
                                   int textCtrlStyle, int textCtrlSizerFlags, int labelTextStyle, int labelTextSizerFlags) 
: tcEditControl(parent, size, fieldName_, label_),
  calculationType("gain")
{
    CreateControls(textCtrlStyle, textCtrlSizerFlags, labelTextStyle, labelTextSizerFlags);

    SetInfoOnly(true);
}

tcRadarCalculationControl::~tcRadarCalculationControl()
{
}