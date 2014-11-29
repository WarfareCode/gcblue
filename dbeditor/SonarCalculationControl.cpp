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

#include "SonarCalculationControl.h"

#include "wx/valtext.h"
#include "wx/sizer.h"
#include "wx/stattext.h"
#include "wx/combobox.h"
#include "wx/button.h"
#include "wx/listbox.h"
#include "wx/xml/xml.h"

#include "simmath.h"
#include "tcDBObjSerializerSql.h"
#include "tcPool.h"
#include "tcSonarDBObject.h"
#include "tcShipDBObject.h"
#include "tcPlatformDBObject.h"
#include "tcTorpedoDBObject.h"
#include "tcPlatformObject.h"
#include "DatabaseManager.h"
#include "tcDatabase.h"
#include "tcSonar.h"
#include "tcSimState.h"
#include "tcSonarEnvironment.h"
#include "SelectFromTablesDialog.h"


using namespace database;

BEGIN_EVENT_TABLE(tcSonarCalculationControl, tcEditControl)
	EVT_BUTTON(UPDATE_CALCULATION, tcSonarCalculationControl::OnUpdateCalculation)
	EVT_BUTTON(PLATFORM_SELECT, tcSonarCalculationControl::OnSelectPlatform)
	EVT_BUTTON(TARGET_SELECT, tcSonarCalculationControl::OnSelectTarget)
END_EVENT_TABLE()


tcSonarCalculationControl* tcSonarCalculationControl::instance = 0;

tcSonarCalculationControl* tcSonarCalculationControl::Get()
{
	return instance;
}

void tcSonarCalculationControl::LoadXmlConfig(wxXmlNode* sonarConfig)
{
	if (sonarConfig == 0)
	{
		wxASSERT(false);
		return;
	}

	autoUpdate->SetValue(sonarConfig->GetPropVal("AutoUpdate", "0") != "0");

	platformClass->SetLabel(sonarConfig->GetPropVal("PlatformClass", "Boat"));
	platformHeading->SetValue(sonarConfig->GetPropVal("PlatformHeading", "0"));
	platformSpeed->SetValue(sonarConfig->GetPropVal("PlatformSpeed", "5"));
	platformDepth->SetValue(sonarConfig->GetPropVal("PlatformDepth", "5"));

	targetClass->SetLabel(sonarConfig->GetPropVal("TargetClass", "Boat"));
	targetHeading->SetValue(sonarConfig->GetPropVal("TargetHeading", "0"));
	targetSpeed->SetValue(sonarConfig->GetPropVal("TargetSpeed", "5"));
	targetDepth->SetValue(sonarConfig->GetPropVal("TargetDepth", "5"));

	seaStateCtrl->SetValue(sonarConfig->GetPropVal("SeaState", "3"));
	bottomDepthCtrl->SetValue(sonarConfig->GetPropVal("BottomDepth", "500"));
	svpCtrl->SetValue(sonarConfig->GetPropVal("EnvironmentTemplate", "Simple"));


}

void tcSonarCalculationControl::SaveXmlConfig(wxXmlNode* sonarConfig)
{
	if (sonarConfig != 0)
    {
        sonarConfig->DeleteProperty("AutoUpdate");
        sonarConfig->DeleteProperty("PlatformClass");
        sonarConfig->DeleteProperty("PlatformHeading");
		sonarConfig->DeleteProperty("PlatformSpeed");
		sonarConfig->DeleteProperty("PlatformDepth");

        sonarConfig->DeleteProperty("TargetClass");
        sonarConfig->DeleteProperty("TargetHeading");
		sonarConfig->DeleteProperty("TargetSpeed");
		sonarConfig->DeleteProperty("TargetDepth");

		sonarConfig->DeleteProperty("SeaState");
		sonarConfig->DeleteProperty("BottomDepth");
		sonarConfig->DeleteProperty("EnvironmentTemplate");


		sonarConfig->AddProperty("AutoUpdate", wxString::Format("%d", autoUpdate->GetValue()));
        sonarConfig->AddProperty("PlatformClass", platformClass->GetLabel());
        sonarConfig->AddProperty("PlatformHeading", platformHeading->GetValue());
		sonarConfig->AddProperty("PlatformSpeed", platformSpeed->GetValue());
		sonarConfig->AddProperty("PlatformDepth", platformDepth->GetValue());

	    sonarConfig->AddProperty("TargetClass", targetClass->GetLabel());
        sonarConfig->AddProperty("TargetHeading", targetHeading->GetValue());
		sonarConfig->AddProperty("TargetSpeed", targetSpeed->GetValue());
		sonarConfig->AddProperty("TargetDepth", targetDepth->GetValue());

		sonarConfig->AddProperty("SeaState", seaStateCtrl->GetValue());
		sonarConfig->AddProperty("BottomDepth", bottomDepthCtrl->GetValue());
		sonarConfig->AddProperty("EnvironmentTemplate", svpCtrl->GetValue());
    }
    else
    {
        wxASSERT(false);
		return;
    }
}


void tcSonarCalculationControl::OnSelectPlatform(wxCommandEvent& event)
{
	wxArrayString tables;
	tables.push_back("ship");
	tables.push_back("sub");
	tables.push_back("torpedo");
	tables.push_back("sonobuoy");

	wxString selection;

	tcSelectFromTablesDialog* dialog = new tcSelectFromTablesDialog(this, "Select Sonar Platform", tables, selection);
	int result = dialog->ShowModal();
    if (result == wxID_OK)
    {
		platformTable = dialog->GetActiveTable();
		platformClass->SetLabel(selection);
	}
	delete dialog;
}

void tcSonarCalculationControl::OnSelectTarget(wxCommandEvent& event)
{
	wxArrayString tables;
	tables.push_back("ship");
	tables.push_back("sub");
	tables.push_back("torpedo");

	wxString selection;

	tcSelectFromTablesDialog* dialog = new tcSelectFromTablesDialog(this, "Select Sonar Target", tables, selection);
	int result = dialog->ShowModal();
    if (result == wxID_OK)
    {
		targetTable = dialog->GetActiveTable();
		targetClass->SetLabel(selection);
	}
	delete dialog;
}


void tcSonarCalculationControl::SetControlWidth(int val) 
{

}



void tcSonarCalculationControl::SetLabelWidth(int val) 
{

}



void tcSonarCalculationControl::SetValue(const wxString& s)
{

}

void tcSonarCalculationControl::OnUpdateCalculation(wxCommandEvent& event)
{
	UpdateCalculation();
}

void tcSonarCalculationControl::UpdateControl()
{
	if (autoUpdate->IsChecked())
	{
		UpdateCalculation();
	}
}

void tcSonarCalculationControl::UpdateCalculation()
{
	tcDatabase* database = tcDatabase::Get();
	
	tcDatabaseManager* databaseManager = tcDatabaseManager::Get();
	sqlite3x::sqlite3_connection& sqlConnection = databaseManager->GetConnection();

	tcDatabaseObject* sonarData1 = database->GetObject(databaseClass.ToStdString());
	tcSonarDBObject* sonarData = dynamic_cast<tcSonarDBObject*>(sonarData1);

	wxString platformClassName = platformClass->GetLabel();
	tcDatabaseObject* platformData = database->GetObject(platformClassName.ToStdString());
	
	wxString targetClassName = platformClass->GetLabel();
	tcDatabaseObject* targetData = database->GetObject(targetClassName.ToStdString());
	
	tcSimState* simState = tcSimState::Get();
	tcGameObject* sensorPlatform = simState->CreateGameObject(platformData);
	tcGameObject* targetPlatform = simState->CreateGameObject(targetData);
	
	if ((sensorPlatform == 0) || (targetPlatform == 0) || (sonarData == 0))
	{
		return;
	}

	sensorPlatform->mcKin.Clear();
	targetPlatform->mcKin.Clear();


	// update platform and target parameters from GUI boxes
	
	double bottomDepth_m = 500.0f;
	long seaState = 3;
	wxString svpTypeString;
	int svpType = 0;

	seaStateCtrl->GetValue().ToLong(&seaState);
	bottomDepthCtrl->GetValue().ToDouble(&bottomDepth_m);
	svpTypeString = svpCtrl->GetValue();

	if (svpTypeString == "Simple") svpType = 0;
	else if (svpTypeString == "NA-Winter") svpType = 1;
	else if (svpTypeString == "NA-Spring") svpType = 2;
	else if (svpTypeString == "NA-Summer") svpType = 3;
	else if (svpTypeString == "NA-Autumn") svpType = 4;
	else wxASSERT(false);

	tcSonarEnvironment* sonarEnvironment = tcSonarEnvironment::Get();
	sonarEnvironment->SetSeaState(unsigned int(seaState));

	if (svpType > 0)
	{
		tcOptions::Get()->useRayTracingSonar = 1;
		sonarEnvironment->SetTemplate(svpType); // sets surface and bottom loss as well
	}
	else
	{
		tcOptions::Get()->useRayTracingSonar = 0;
	}



	double platformHeading_deg = 90.0;
	double platformSpeed_kts = 5.0;
	double platformDepth_m = 5.0;

	platformHeading->GetValue().ToDouble(&platformHeading_deg);
	platformSpeed->GetValue().ToDouble(&platformSpeed_kts);
	platformDepth->GetValue().ToDouble(&platformDepth_m);

	sensorPlatform->mcKin.mfHeading_rad = C_PIOVER180 * platformHeading_deg;
	sensorPlatform->mcKin.mfSpeed_kts = platformSpeed_kts;
	sensorPlatform->mcKin.mfAlt_m = -platformDepth_m;
	sensorPlatform->mcTerrain.mfHeight_m = float(-bottomDepth_m);

	double targetHeading_deg = 0.0;
	double targetSpeed_kts = 5.0;
	double targetDepth_m = 5.0;

	targetHeading->GetValue().ToDouble(&targetHeading_deg);
	targetSpeed->GetValue().ToDouble(&targetSpeed_kts);
	targetDepth->GetValue().ToDouble(&targetDepth_m);

	targetPlatform->mcKin.mfLat_rad = 0.0001;
	targetPlatform->mcKin.mfHeading_rad = C_PIOVER180 * targetHeading_deg;
	targetPlatform->mcKin.mfSpeed_kts = targetSpeed_kts;
	targetPlatform->mcKin.mfAlt_m = -targetDepth_m;
	targetPlatform->mcTerrain.mfHeight_m = float(-bottomDepth_m);

	

	tcSonar sonar(sonarData);
	sonar.SetParent(sensorPlatform);
	sonar.ForceScope(99999.0f);

	float NL, SLp;
	

	//platformSelect = new wxComboBox(this, COMBO_CTRL, "", wxDefaultPosition, wxSize(controlWidth, 20), 
	//	emptyChoices, style, wxDefaultValidator, "ComboBox");



	std::vector<double> targetSpeedRange_kts;
	std::vector<double> detectionRangeSS1_m;
	std::vector<double> detectionRangeSS3_m;
	std::vector<double> detectionRangeSS5_m;

	float xmin = 0.0;
	float xmax = 30.0;
	if (tcPlatformDBObject* platformData = dynamic_cast<tcPlatformDBObject*>(targetData))
	{
		xmin = 0.0;
		xmax = ceil(platformData->mfMaxSpeed_kts);
	}
	else if (tcTorpedoDBObject* torpedoData = dynamic_cast<tcTorpedoDBObject*>(targetData))
	{
		xmin = floor(0.5f*torpedoData->maxSpeed_kts);
		xmax = ceil(torpedoData->maxSpeed_kts);
	}
	
	for (double x=xmin; x<xmax; x+=1.0)
	{
		targetSpeedRange_kts.push_back(x);
	}

	for (size_t n=0; n<targetSpeedRange_kts.size(); n++)
	{
		double tgtSpeed_kts = targetSpeedRange_kts[n];
		
		targetPlatform->mcKin.mfSpeed_kts = tgtSpeed_kts;

		sonarEnvironment->SetSeaState(1);
		float range_m = 1000*sonar.CalculateSimpleDetectionRange(targetPlatform, NL, SLp);
		detectionRangeSS1_m.push_back(range_m);

		sonarEnvironment->SetSeaState(3);
		range_m = 1000*sonar.CalculateSimpleDetectionRange(targetPlatform, NL, SLp);
		detectionRangeSS3_m.push_back(range_m);

		sonarEnvironment->SetSeaState(5);
		range_m = 1000*sonar.CalculateSimpleDetectionRange(targetPlatform, NL, SLp);
		detectionRangeSS5_m.push_back(range_m);

	}




	xyVectorRangeSS1->SetData(targetSpeedRange_kts, detectionRangeSS1_m);
	xyVectorRangeSS3->SetData(targetSpeedRange_kts, detectionRangeSS3_m);
	xyVectorRangeSS5->SetData(targetSpeedRange_kts, detectionRangeSS5_m);

	titleText->SetName(wxString::Format("%s", databaseClass.c_str()));
	plotWindow->Fit();

	// next do SNR calculation for detailedPlot

	// reset object params
	seaStateCtrl->GetValue().ToLong(&seaState);
	bottomDepthCtrl->GetValue().ToDouble(&bottomDepth_m);
	svpTypeString = svpCtrl->GetValue();

	if (svpTypeString == "Simple") svpType = 0;
	else if (svpTypeString == "NA-Winter") svpType = 1;
	else if (svpTypeString == "NA-Spring") svpType = 2;
	else if (svpTypeString == "NA-Summer") svpType = 3;
	else if (svpTypeString == "NA-Autumn") svpType = 4;
	else wxASSERT(false);

	sonarEnvironment->SetSeaState(unsigned int(seaState));

	if (svpType > 0)
	{
		tcOptions::Get()->useRayTracingSonar = 1;
		sonarEnvironment->SetTemplate(svpType); // sets surface and bottom loss as well
	}
	else
	{
		tcOptions::Get()->useRayTracingSonar = 0;
	}

	sensorPlatform->mcKin.mfHeading_rad = C_PIOVER180 * platformHeading_deg;
	sensorPlatform->mcKin.mfSpeed_kts = platformSpeed_kts;
	sensorPlatform->mcKin.mfAlt_m = -platformDepth_m;
	sensorPlatform->mcTerrain.mfHeight_m = float(-bottomDepth_m);

	targetPlatform->mcKin.mfHeading_rad = C_PIOVER180 * targetHeading_deg;
	targetPlatform->mcKin.mfSpeed_kts = targetSpeed_kts;
	targetPlatform->mcKin.mfAlt_m = -targetDepth_m;
	targetPlatform->mcTerrain.mfHeight_m = float(-bottomDepth_m);


	std::vector<double> rangeVector_m;
	std::vector<double> SNRVector_dB;

	for (double r_m=500.0; r_m<80000.0; r_m+=500.0)
	{
		rangeVector_m.push_back(r_m);

		targetPlatform->mcKin.mfLat_rad = C_MTORAD * r_m;

		float actualRange_km = 0;
		bool useRandom = false;
		sonar.CanDetectTarget(targetPlatform, actualRange_km, useRandom);
		float SNR_dB = sonar.GetLastSNRExcess();

		SNRVector_dB.push_back(SNR_dB);
	}

	plot1->SetData(rangeVector_m, SNRVector_dB);
	detailedPlot->Fit();	
	
	// clean  up
	
	delete targetPlatform;
	delete sensorPlatform;

}


void tcSonarCalculationControl::CreateControls(int textCtrlStyle, int textCtrlSizerFlags, int labelTextStyle, int labelTextSizerFlags)
{
	wxArrayString emptyChoices;


	autoUpdate = new wxCheckBox(this, wxID_ANY, "Auto Update", wxDefaultPosition, wxDefaultSize);
	autoUpdate->SetValue(false);

	updateCalculation = new wxButton(this, UPDATE_CALCULATION, "Update Calculation", wxDefaultPosition, wxSize(150, 25));


	long style = wxCB_DROPDOWN | wxCB_READONLY;

	platformClass = new wxButton(this, PLATFORM_SELECT, "", wxDefaultPosition, wxSize(150, 25), wxBU_LEFT);
	platformClass->SetToolTip("Sonar Host-Platform Class");


	platformHeading = new wxTextCtrl(this, wxID_ANY, "0");
	platformSpeed = new wxTextCtrl(this, wxID_ANY, "0");
	platformDepth = new wxTextCtrl(this, wxID_ANY, "0");


	targetClass = new wxButton(this, TARGET_SELECT, "", wxDefaultPosition, wxSize(150, 25), wxBU_LEFT);
    targetClass->SetToolTip("Sonar Target Class");

	targetHeading = new wxTextCtrl(this, wxID_ANY, "0");
	targetSpeed = new wxTextCtrl(this, wxID_ANY, "5");
	targetDepth = new wxTextCtrl(this, wxID_ANY, "0");

	seaStateCtrl = new wxTextCtrl(this, wxID_ANY, "3");
	bottomDepthCtrl = new wxTextCtrl(this, wxID_ANY, "500");

	wxArrayString svpChoices;
	svpChoices.push_back("Simple");
	svpChoices.push_back("NA-Winter");
	svpChoices.push_back("NA-Spring");
	svpChoices.push_back("NA-Summer");
	svpChoices.push_back("NA-Autumn");
	svpCtrl = new wxComboBox(this, wxID_ANY, "Simple", wxDefaultPosition, wxDefaultSize, svpChoices, wxCB_READONLY | wxCB_DROPDOWN);



	plotWindow = new mpWindow( this, -1, wxPoint(10,10), wxSize(400, 600), wxSUNKEN_BORDER );
	plotWindow->EnableDoubleBuffer(true);

	wxFont graphFont(11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);

	bool drawTicks = false; // false for grid
    mpScaleX* xaxis = new mpScaleX(wxT("Target Speed (kts)"), mpALIGN_BOTTOM, drawTicks, mpX_NORMAL);
    mpScaleY* yaxis = new mpScaleY(wxT("Detection Range (m)"), mpALIGN_LEFT, drawTicks);


    xaxis->SetFont(graphFont);
    yaxis->SetFont(graphFont);

	xaxis->SetLabelFormat(wxT("%.0f"));
	yaxis->SetLabelFormat(wxT("%.0f"));

    xaxis->SetDrawOutsideMargins(false);
    yaxis->SetDrawOutsideMargins(false);

	titleText = new mpText("Title", 400, 5);
	titleText->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

	mpInfoCoords *nfo;
    plotWindow->AddLayer( nfo = new mpInfoCoords(wxRect(100,30,20,20), wxTRANSPARENT_BRUSH));
    nfo->SetVisible(true);

    wxBrush hatch2(wxColour(163,208,212), wxSOLID);
    mpInfoLegend* leg;
    plotWindow->AddLayer( leg = new mpInfoLegend(wxRect(100,80,60,40), &hatch2));
    leg->SetVisible(true);



	// Fake axes formatting to test arbitrary format string
	// xaxis->SetLabelFormat(wxT("%.2f €"));
	// yaxis->SetLabelFormat(wxT("%p"));
    plotWindow->SetMargins(30, 30, 40, 90); // (int top, int right, int bottom, int left);
    plotWindow->AddLayer(xaxis);
    plotWindow->AddLayer(yaxis);
	plotWindow->AddLayer(titleText);

	wxPen pen;
	pen.SetWidth(2);


	xyVectorRangeSS1 = new mpFXYVector;
	xyVectorRangeSS1->SetContinuity(true);
	pen.SetColour(wxColour(0, 0, 255));
	xyVectorRangeSS1->SetPen(pen);
	xyVectorRangeSS1->SetName("Sea State 1");
	xyVectorRangeSS1->ShowName(false);
	xyVectorRangeSS1->SetDrawOutsideMargins(false);


	xyVectorRangeSS3 = new mpFXYVector;
	xyVectorRangeSS3->SetContinuity(true);
	pen.SetColour(wxColour(0, 255, 255));
	xyVectorRangeSS3->SetPen(pen);
	xyVectorRangeSS3->SetName("Sea State 3");
	xyVectorRangeSS3->ShowName(false);
	xyVectorRangeSS3->SetDrawOutsideMargins(false);


	xyVectorRangeSS5 = new mpFXYVector;
	xyVectorRangeSS5->SetContinuity(true);
	pen.SetColour(wxColour(255, 0, 255));
	xyVectorRangeSS5->SetPen(pen);
	xyVectorRangeSS5->SetName("Sea State 5");
	xyVectorRangeSS5->ShowName(false);
	xyVectorRangeSS5->SetDrawOutsideMargins(false);


	plotWindow->AddLayer(xyVectorRangeSS1);
	plotWindow->AddLayer(xyVectorRangeSS3);
	plotWindow->AddLayer(xyVectorRangeSS5);
  
	// detailed plot
	CreateDetailedPlot();
	

	// sizers
    int border = 3;

	wxBoxSizer* calculationParams = new wxBoxSizer(wxHORIZONTAL);
	calculationParams->Add(autoUpdate, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);
	calculationParams->Add(updateCalculation);



	wxBoxSizer* objectParams = new wxBoxSizer(wxHORIZONTAL);

	
	wxBoxSizer* col1 = new wxBoxSizer(wxVERTICAL);	
	col1->Add(new wxStaticText(this, wxID_ANY, "Platform"));
	col1->Add(platformClass);
	col1->Add(new wxStaticText(this, wxID_ANY, "Heading (deg)"));
	col1->Add(platformHeading);
	col1->Add(new wxStaticText(this, wxID_ANY, "Speed (kts)"));
	col1->Add(platformSpeed);
	col1->Add(new wxStaticText(this, wxID_ANY, "Depth (m)"));
	col1->Add(platformDepth);

	wxBoxSizer* col2 = new wxBoxSizer(wxVERTICAL);	
	col2->Add(new wxStaticText(this, wxID_ANY, "Target"));
	col2->Add(targetClass);
	col2->Add(new wxStaticText(this, wxID_ANY, "Heading (deg)"));
	col2->Add(targetHeading);
	col2->Add(new wxStaticText(this, wxID_ANY, "Speed (kts)"));
	col2->Add(targetSpeed);
	col2->Add(new wxStaticText(this, wxID_ANY, "Depth (m)"));
	col2->Add(targetDepth);

	wxBoxSizer* col3 = new wxBoxSizer(wxVERTICAL);	
	col3->Add(new wxStaticText(this, wxID_ANY, "Sea State"));
	col3->Add(seaStateCtrl);
	col3->Add(new wxStaticText(this, wxID_ANY, "Bottom Depth (m)"));
	col3->Add(bottomDepthCtrl);
	col3->Add(new wxStaticText(this, wxID_ANY, "SVP Type"));
	col3->Add(svpCtrl);


	objectParams->Add(col1);
	objectParams->Add(col2);
	objectParams->Add(col3);


    wxBoxSizer* sizerTop = new wxBoxSizer(wxVERTICAL);
	sizerTop->SetMinSize(800, 600);

	sizerTop->Add(calculationParams, 0, labelTextSizerFlags, border);
    sizerTop->Add(objectParams, 0, labelTextSizerFlags, border);
	sizerTop->Add(plotWindow, 5, wxALL | wxEXPAND, border);
	sizerTop->AddSpacer(1);
	sizerTop->Add(detailedPlot, 5, wxALL | wxEXPAND, border);
	sizerTop->AddSpacer(1);

	SetAutoLayout(true);
    SetSizer(sizerTop);

    sizerTop->SetSizeHints(this);
    sizerTop->Fit(this); 

}


void tcSonarCalculationControl::CreateDetailedPlot()
{
	detailedPlot = new mpWindow(this, -1, wxPoint(10,10), wxSize(400, 600), wxSUNKEN_BORDER );
	detailedPlot->EnableDoubleBuffer(true);

	bool drawTicks = false; // false for grid
    mpScaleX* xaxis = new mpScaleX(wxT("Range (m)"), mpALIGN_BOTTOM, drawTicks, mpX_NORMAL);
    mpScaleY* yaxis = new mpScaleY(wxT("SNR (dB)"), mpALIGN_LEFT, drawTicks);

	wxFont graphFont(11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    xaxis->SetFont(graphFont);
    yaxis->SetFont(graphFont);

	xaxis->SetLabelFormat(wxT("%.0f"));
	yaxis->SetLabelFormat(wxT("%.0f"));

    xaxis->SetDrawOutsideMargins(false);
    yaxis->SetDrawOutsideMargins(false);

	detailedPlot->SetMargins(30, 30, 40, 90); // (int top, int right, int bottom, int left);
	detailedPlot->AddLayer(xaxis);
	detailedPlot->AddLayer(yaxis);


	mpInfoCoords *nfo;
    detailedPlot->AddLayer( nfo = new mpInfoCoords(wxRect(100,30,20,20), wxTRANSPARENT_BRUSH));
    nfo->SetVisible(true);

	wxPen pen;
	pen.SetWidth(2);

	plot1 = new mpFXYVector;
	plot1->SetContinuity(true);
	pen.SetColour(wxColour(0, 0, 255));
	plot1->SetPen(pen);
	plot1->SetName("Plot 1");
	plot1->ShowName(false);
	plot1->SetDrawOutsideMargins(false);

	detailedPlot->AddLayer(plot1);
}


tcSonarCalculationControl::tcSonarCalculationControl(wxWindow* parent, const wxSize& size, 
                                   const wxString& label_) 
: tcEditControl(parent, size, "NOFIELD", label_) 
{
    int textCtrlStyle = 0;
    int textCtrlSizerFlags = wxALL | wxEXPAND;
    int labelTextStyle = 0;
    int labelTextSizerFlags = wxALL;

    CreateControls(textCtrlStyle, textCtrlSizerFlags, labelTextStyle, labelTextSizerFlags);
}

tcSonarCalculationControl::tcSonarCalculationControl(wxWindow* parent, const wxSize& size, 
                                   const wxString& label_, 
                                   int textCtrlStyle, int textCtrlSizerFlags, int labelTextStyle, int labelTextSizerFlags) 
: tcEditControl(parent, size, "NOFIELD", label_) 
{
    CreateControls(textCtrlStyle, textCtrlSizerFlags, labelTextStyle, labelTextSizerFlags);

	SetInfoOnly(true);

	wxASSERT(instance == 0);
	instance = this;
}

tcSonarCalculationControl::~tcSonarCalculationControl()
{
}