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

#include "ECMEvaluationDialog.h"
#include "DatabaseManager.h"
#include "tcECMDBObject.h"
#include "tcRadarDBObject.h"
#include "tcRadar.h"
#include "tcDatabase.h"
#include "tcGameObject.h"
#include "tcECM.h"

#include "wx/listbox.h"
#include "wx/radiobox.h"
#include "wx/sizer.h"

BEGIN_EVENT_TABLE(tcECMEvaluationDialog, wxDialog)
    EVT_BUTTON(wxID_OK, tcECMEvaluationDialog::OnOK)
    EVT_COMBOBOX(-1, tcECMEvaluationDialog::OnParameterChange)
END_EVENT_TABLE()

using namespace database;

void tcECMEvaluationDialog::OnParameterChange(wxCommandEvent& event)
{
    UpdateCalculations();
}

void tcECMEvaluationDialog::UpdateCalculations()
{
    wxString ecmClass = ecmType->GetValue();
    wxString radarClass = radarType->GetValue();

    tcDatabase* database = tcDatabase::Get();

    tcRadarDBObject* radarData = dynamic_cast<tcRadarDBObject*>(database->GetObject(radarClass.ToStdString()));
    tcECMDBObject* ecmData = dynamic_cast<tcECMDBObject*>(database->GetObject(ecmClass.ToStdString()));

    if ((radarData == 0) || (ecmData == 0)) return;

    tcRadar testRadar(radarData);

    tcGameObject radarPlatform;
    radarPlatform.mcKin.Clear();
    radarPlatform.mcKin.mfAlt_m = 3000.0f;

    tcGameObject ecmPlatform;
    ecmPlatform.mcKin.Clear();
    ecmPlatform.mcKin.mfAlt_m = 3000.0f;
    ecmPlatform.mcKin.mfLat_rad = C_KMTORAD * 50.0f;

    testRadar.SetParent(&radarPlatform);
    testRadar.SetMountAz(0);

    tcECM testECM(ecmData);
    testECM.SetParent(&ecmPlatform);
    testECM.SetMountAz(C_PI);

    

    std::vector<float> mainlobeDegradation_dB;
    std::vector<float> sidelobeDegradation_dB;
    std::vector<float> range_km;

    float step_km = radarData->isSurveillance ? 10.0f : 1.0f;
    
    for (float r_km=step_km; r_km<30*step_km; r_km+=step_km)
    {
        range_km.push_back(r_km);
    }

    for (float r_km=30*step_km; r_km<=(50*step_km); r_km+=(5*step_km))
    {
        range_km.push_back(r_km);
    }

    for (size_t n=0; n<range_km.size(); n++)
    {
        float r_km = range_km[n];

        // mainlobe case
        ecmPlatform.mcKin.mfLat_rad = C_KMTORAD * r_km;
        testECM.SetMountAz(C_PI);

        testRadar.jamMap.clear();
        testECM.UpdateBarrageTargetRadar(&testRadar, 1);

        mainlobeDegradation_dB.push_back(testRadar.CalculateJammingDegradation2(0, 0));

        // sidelobe case (behind radar)
        ecmPlatform.mcKin.mfLat_rad = -C_KMTORAD * r_km;
        testECM.SetMountAz(0);

        testRadar.jamMap.clear();
        testECM.UpdateBarrageTargetRadar(&testRadar, 1);

        sidelobeDegradation_dB.push_back(testRadar.CalculateJammingDegradation2(0, 0));
    }

    resultsText->Clear();
    resultsText->AppendText("                 (J+N)/N\n");
    resultsText->AppendText("Range  Mainlobe Sidelobe \n");
    for (size_t n=0; n<range_km.size(); n++)
    {
        resultsText->AppendText(wxString::Format("%03.0f km %02.1f dB %02.1f dB\n", 
            range_km[n], mainlobeDegradation_dB[n], sidelobeDegradation_dB[n]));
    }

    Fit();

}



void tcECMEvaluationDialog::OnOK(wxCommandEvent& event)
{
    int returnCode = wxID_OK;

    EndModal(returnCode);
}



tcECMEvaluationDialog::tcECMEvaluationDialog(wxWindow* parent, const wxString& title)
: wxDialog(parent, wxID_ANY, title, wxDefaultPosition, wxSize(300, 600), wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER, "ECMEvaluationDialogBox")
{
    tcDatabaseManager* databaseManager = tcDatabaseManager::Get();

    wxArrayString ecmList = databaseManager->GetPlatformList("ecm");
    wxArrayString radarList = databaseManager->GetPlatformList("radar");

    ecmType = new wxComboBox(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, ecmList, wxCB_READONLY);
    radarType = new wxComboBox(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, radarList, wxCB_READONLY);
    resultsText = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(200, 500), wxTE_MULTILINE | wxTE_READONLY);



    wxBoxSizer* sizerTop = new wxBoxSizer(wxVERTICAL);
    sizerTop->Add(new wxStaticText(this, wxID_ANY, "ECM Type"), 0, wxALL, 3);
    sizerTop->Add(ecmType, 0, wxALL, 3);
    sizerTop->Add(new wxStaticText(this, wxID_ANY, "Radar Type"), 0, wxALL, 3);
    sizerTop->Add(radarType, 0, wxALL, 3);
    sizerTop->Add(resultsText, 1, wxALL | wxEXPAND, 3);
    sizerTop->Add(wxDialog::CreateButtonSizer(wxOK), 0, wxALL, 5);

    SetSizer(sizerTop);

    //sizerTop->SetSizeHints(this);
    sizerTop->Fit(this); 

}

tcECMEvaluationDialog::~tcECMEvaluationDialog()
{
}