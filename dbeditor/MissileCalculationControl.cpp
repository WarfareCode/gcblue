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

#include "MissileCalculationControl.h"

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
#include "tcPlatformDBObject.h"
#include "tcMissileDBObject.h"
#include "tcPlatformObject.h"
#include "tcMissileObject.h"
#include "DatabaseManager.h"
#include "tcDatabase.h"
#include "tcSimState.h"
#include "SelectFromTablesDialog.h"


using namespace database;

BEGIN_EVENT_TABLE(tcMissileCalculationControl, tcEditControl)
	EVT_BUTTON(UPDATE_CALCULATION, tcMissileCalculationControl::OnUpdateCalculation)
END_EVENT_TABLE()


tcMissileCalculationControl* tcMissileCalculationControl::instance = 0;

tcMissileCalculationControl* tcMissileCalculationControl::Get()
{
	return instance;
}

void tcMissileCalculationControl::LoadXmlConfig(wxXmlNode* config)
{
	if (config == 0)
	{
		wxASSERT(false);
		return;
	}

	launchHeading->SetValue(config->GetPropVal("LaunchHeading", "0"));
	launchElevation->SetValue(config->GetPropVal("LaunchElevation", "0"));
	launchSpeed->SetValue(config->GetPropVal("LaunchSpeed", "5"));
	launchAltitude->SetValue(config->GetPropVal("LaunchAltitude", "5"));

	targetHeading->SetValue(config->GetPropVal("TargetHeading", "0"));
	targetSpeed->SetValue(config->GetPropVal("TargetSpeed", "0"));
	targetAltitude->SetValue(config->GetPropVal("TargetAltitude", "5"));
	targetAltitude->SetValue(config->GetPropVal("TargetRange", "50"));
}

void tcMissileCalculationControl::SaveXmlConfig(wxXmlNode* config)
{
	if (config != 0)
    {
        config->DeleteProperty("LaunchHeading");
		config->DeleteProperty("LaunchElevation");
		config->DeleteProperty("LaunchSpeed");
		config->DeleteProperty("LaunchAltitude");

        config->DeleteProperty("TargetHeading");
		config->DeleteProperty("TargetSpeed");
		config->DeleteProperty("TargetAltitude");
		config->DeleteProperty("TargetRange");

        config->AddProperty("LaunchHeading", launchHeading->GetValue());
		config->AddProperty("LaunchElevation", launchElevation->GetValue());
		config->AddProperty("LaunchSpeed", launchSpeed->GetValue());
		config->AddProperty("LaunchAltitude", launchAltitude->GetValue());

        config->AddProperty("TargetHeading", targetHeading->GetValue());
		config->AddProperty("TargetSpeed", targetSpeed->GetValue());
		config->AddProperty("TargetAltitude", targetAltitude->GetValue());
		config->AddProperty("TargetRange", targetRange->GetValue());
    }
    else
    {
        wxASSERT(false);
		return;
    }
}

void tcMissileCalculationControl::OnUpdateCalculation(wxCommandEvent& event)
{
	UpdateCalculation();
}

void tcMissileCalculationControl::SetControlWidth(int val) 
{

}



void tcMissileCalculationControl::SetLabelWidth(int val) 
{

}



void tcMissileCalculationControl::SetValue(const wxString& s)
{

}



void tcMissileCalculationControl::UpdateControl()
{
	UpdateCalculation();
}

void tcMissileCalculationControl::UpdateCalculation()
{
	tcDatabase* database = tcDatabase::Get();
	
	tcDatabaseManager* databaseManager = tcDatabaseManager::Get();
	sqlite3x::sqlite3_connection& sqlConnection = databaseManager->GetConnection();

	tcDatabaseObject* missileDataTemp = database->GetObject(databaseClass.ToStdString());
	tcMissileDBObject* missileData = dynamic_cast<tcMissileDBObject*>(missileDataTemp);

	if (missileData == 0)
	{
		return;
	}


	// update launch and target parameters from GUI boxes
	double launchHeading_deg = 0.0;
	double launchElevation_deg = 0.0;
	double launchSpeed_kts = 0.0;
	double launchAltitude_m = 5.0;

	launchHeading->GetValue().ToDouble(&launchHeading_deg);
	launchElevation->GetValue().ToDouble(&launchElevation_deg);
	launchSpeed->GetValue().ToDouble(&launchSpeed_kts);
	launchAltitude->GetValue().ToDouble(&launchAltitude_m);

	double targetHeading_deg = 0.0;
	double targetSpeed_kts = 5.0;
	double targetAltitude_m = 5.0;
	double targetRange_km = 50.0;

	targetHeading->GetValue().ToDouble(&targetHeading_deg);
	targetSpeed->GetValue().ToDouble(&targetSpeed_kts);
	targetAltitude->GetValue().ToDouble(&targetAltitude_m);
	targetRange->GetValue().ToDouble(&targetRange_km);


	tcKinematics missileKin;

    missileKin.mfSpeed_kts = launchSpeed_kts;
    missileKin.mfAlt_m = launchAltitude_m;
    missileKin.mfLon_rad = 0;
    missileKin.mfLat_rad = 0;
    missileKin.mfHeading_rad = C_PIOVER180 * launchHeading_deg;
    missileKin.mfClimbAngle_rad = C_PIOVER180 * launchElevation_deg;
    missileKin.mfPitch_rad = C_PIOVER180 * launchElevation_deg;
    missileKin.mfRoll_rad = 0;

    tcTrack targetTrack;
    targetTrack.mfAlt_m = targetAltitude_m;
    targetTrack.mfLon_rad = missileKin.mfLon_rad;
    targetTrack.mfLat_rad = missileKin.mfLat_rad;
    targetTrack.mfSpeed_kts = targetSpeed_kts;

 
    tcTrack targetEval = targetTrack;
    targetEval.Offset(targetRange_km, 0); // assumes target to north of launching platform

	tcMissileObject::MissileTrajectory trajectory;
    tcKinematics missileKinEval(missileKin); // missileKin param is modified by EvaluateTarget
	bool hit = tcMissileObject::EvaluateTarget(missileKinEval, targetEval, missileData, &trajectory);

	std::vector<double> time_s;
	std::vector<double> range_km;
	std::vector<double> speed_kts;
	std::vector<double> altitude_m;

	size_t nPoints = trajectory.time_s.size();
	for (size_t n=0; n<nPoints; n++)
	{
		time_s.push_back(trajectory.time_s[n]);
		range_km.push_back(0.001 * trajectory.range_m[n]);
		speed_kts.push_back(C_MPSTOKTS * trajectory.speed_mps[n]);
		altitude_m.push_back(trajectory.altitude_m[n]);
	}

	xyVectorSpeed->SetData(time_s, speed_kts);
	xyVectorAltitude->SetData(time_s, altitude_m);

	double endRange_km = 0;
	if (nPoints > 0)
	{
		endRange_km = range_km[nPoints-1];
	}

	if (hit)
	{
		titleText->SetName(wxString::Format("%s end range: %.1f km (in range)", databaseClass.c_str(), endRange_km));
	}
	else
	{
		titleText->SetName(wxString::Format("%s end range: %.1f km (out of range)", databaseClass.c_str(), endRange_km));
	}
	plotWindow->Fit();
}


void tcMissileCalculationControl::CreateControls(int textCtrlStyle, int textCtrlSizerFlags, int labelTextStyle, int labelTextSizerFlags)
{
	updateCalculation = new wxButton(this, UPDATE_CALCULATION, "Update Calculation", wxDefaultPosition, wxSize(150, 25));

	long style = wxCB_DROPDOWN | wxCB_READONLY;

	launchHeading = new wxTextCtrl(this, wxID_ANY, "0");
	launchElevation = new wxTextCtrl(this, wxID_ANY, "0");
	launchSpeed = new wxTextCtrl(this, wxID_ANY, "0");
	launchAltitude = new wxTextCtrl(this, wxID_ANY, "0");

	targetHeading = new wxTextCtrl(this, wxID_ANY, "0");
	targetSpeed = new wxTextCtrl(this, wxID_ANY, "0");
	targetAltitude = new wxTextCtrl(this, wxID_ANY, "0");
	targetRange = new wxTextCtrl(this, wxID_ANY, "50");


	plotWindow = new mpWindow( this, -1, wxPoint(10,10), wxSize(400, 600), wxSUNKEN_BORDER );
	plotWindow->EnableDoubleBuffer(true);

	wxFont graphFont(11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);

	bool drawTicks = false; // false for grid
    mpScaleX* xaxis = new mpScaleX(wxT("Time (s)"), mpALIGN_BOTTOM, drawTicks, mpX_NORMAL);
    mpScaleY* yaxis = new mpScaleY(wxT(""), mpALIGN_LEFT, drawTicks);


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


    xyVectorSpeed = new mpFXYVector;
	xyVectorSpeed->SetContinuity(true);
	pen.SetColour(wxColour(255, 0, 0));
	xyVectorSpeed->SetPen(pen);
	xyVectorSpeed->SetName("Speed (kts)");
	xyVectorSpeed->ShowName(false);
	xyVectorSpeed->SetDrawOutsideMargins(false);


    xyVectorAltitude = new mpFXYVector;
	xyVectorAltitude->SetContinuity(true);
	pen.SetColour(wxColour(0, 0, 255));
	xyVectorAltitude->SetPen(pen);
	xyVectorAltitude->SetName("Altitude (m)");
	xyVectorAltitude->ShowName(false);
	xyVectorAltitude->SetDrawOutsideMargins(false);


	plotWindow->AddLayer(xyVectorSpeed);
	plotWindow->AddLayer(xyVectorAltitude);
  

	// sizers
    int border = 3;

	wxBoxSizer* calculationParams = new wxBoxSizer(wxHORIZONTAL);
	calculationParams->Add(updateCalculation);


	wxBoxSizer* objectParams = new wxBoxSizer(wxHORIZONTAL);

	
	wxBoxSizer* col1 = new wxBoxSizer(wxVERTICAL);	
	col1->Add(new wxStaticText(this, wxID_ANY, "Launch Parameters"));
	col1->Add(new wxStaticText(this, wxID_ANY, "Heading (deg)"));
	col1->Add(launchHeading);
	col1->Add(new wxStaticText(this, wxID_ANY, "Elevation (deg)"));
	col1->Add(launchElevation);
	col1->Add(new wxStaticText(this, wxID_ANY, "Speed (kts)"));
	col1->Add(launchSpeed);
	col1->Add(new wxStaticText(this, wxID_ANY, "Altitude (m)"));
	col1->Add(launchAltitude);

	wxBoxSizer* col2 = new wxBoxSizer(wxVERTICAL);	
	col2->Add(new wxStaticText(this, wxID_ANY, "Target Parameters"));
	col2->Add(new wxStaticText(this, wxID_ANY, "Heading (deg)"));
	col2->Add(targetHeading);
	col2->Add(new wxStaticText(this, wxID_ANY, "Speed (kts)"));
	col2->Add(targetSpeed);
	col2->Add(new wxStaticText(this, wxID_ANY, "Altitude (m)"));
	col2->Add(targetAltitude);
	col2->Add(new wxStaticText(this, wxID_ANY, "Range (km)"));
	col2->Add(targetRange);


	objectParams->Add(col1);
	objectParams->Add(col2);



    wxBoxSizer* sizerTop = new wxBoxSizer(wxVERTICAL);
	sizerTop->SetMinSize(800, 600);

	sizerTop->Add(calculationParams, 0, labelTextSizerFlags, border);
    sizerTop->Add(objectParams, 0, labelTextSizerFlags, border);
	sizerTop->Add(plotWindow, 5, wxALL | wxEXPAND, border);
	sizerTop->AddSpacer(1);

	SetAutoLayout(true);
    SetSizer(sizerTop);

    sizerTop->SetSizeHints(this);
    sizerTop->Fit(this); 

}



tcMissileCalculationControl::tcMissileCalculationControl(wxWindow* parent, const wxSize& size, 
                                   const wxString& label_) 
: tcEditControl(parent, size, "NOFIELD", label_) 
{
    int textCtrlStyle = 0;
    int textCtrlSizerFlags = wxALL | wxEXPAND;
    int labelTextStyle = 0;
    int labelTextSizerFlags = wxALL;

    CreateControls(textCtrlStyle, textCtrlSizerFlags, labelTextStyle, labelTextSizerFlags);
}

tcMissileCalculationControl::tcMissileCalculationControl(wxWindow* parent, const wxSize& size, 
                                   const wxString& label_, 
                                   int textCtrlStyle, int textCtrlSizerFlags, int labelTextStyle, int labelTextSizerFlags) 
: tcEditControl(parent, size, "NOFIELD", label_) 
{
    CreateControls(textCtrlStyle, textCtrlSizerFlags, labelTextStyle, labelTextSizerFlags);

	SetInfoOnly(true);

	wxASSERT(instance == 0);
	instance = this;
}

tcMissileCalculationControl::~tcMissileCalculationControl()
{
}