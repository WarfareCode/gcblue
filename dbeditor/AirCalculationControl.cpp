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

#include "AirCalculationControl.h"

#include "wx/valtext.h"
#include "wx/sizer.h"
#include "wx/stattext.h"

#include "simmath.h"
#include "tcDBObjSerializerSql.h"
#include "tcPool.h"
#include "tcJetDBObject.h"
#include "tcAeroAirObject.h"
#include "DatabaseManager.h"
#include "tcDatabase.h"

using namespace database;

BEGIN_EVENT_TABLE(tcAirCalculationControl, tcEditControl)

END_EVENT_TABLE()






void tcAirCalculationControl::SetControlWidth(int val) 
{

}



void tcAirCalculationControl::SetLabelWidth(int val) 
{
    wxSize current(labelText->GetSize());
    labelText->SetSize(wxSize(val, current.GetHeight()));
}



void tcAirCalculationControl::SetValue(const wxString& s)
{

}

void tcAirCalculationControl::UpdateControl()
{

	tcDatabaseManager* databaseManager = tcDatabaseManager::Get();
	sqlite3x::sqlite3_connection& sqlConnection = databaseManager->GetConnection();

	tcDatabase* database = tcDatabase::Get();


	tcDBObjSerializerSql<tcJetDBObject> serializer(database, sqlConnection, "air");

	tcJetDBObject* airData = serializer.LoadRecordTemporary(databaseClass.c_str());
    if (airData == 0) return;

	std::vector<double> altVect_m;
	std::vector<double> speedVectMil_mps;
	std::vector<double> speedVectAB_mps;
	std::vector<double> speedVectStall_mps;
	std::vector<double> speedVectCruise_mps;
	std::vector<double> rangeVectMil_km;
	std::vector<double> rangeVectCruise_km;

	// create vector of altitudes to evaluate, allows variable spacing
	std::vector<double> altEval_m;
	double alt_m = 0;
	for (; alt_m<15000.0; alt_m+=250.0)
	{
		altEval_m.push_back(alt_m);
	}
	for (; alt_m<=20000.0; alt_m+=500.0)
	{
		altEval_m.push_back(alt_m);
	}
	for (; alt_m<=30000.0; alt_m+=1000.0)
	{
		altEval_m.push_back(alt_m);
	}

	for (size_t n=0; n<altEval_m.size(); n++)
	{
		alt_m = altEval_m[n];

		altVect_m.push_back(alt_m);

		float damageLevel = 0;
		float maxSpeed_mps;
		float fuelRate_kgps;
        
		tcAeroAirObject::CalculateSpeedParams(alt_m, 1.0, maxSpeed_mps, fuelRate_kgps, damageLevel, airData);
		speedVectMil_mps.push_back(maxSpeed_mps);

		float rangeMil_km = 0.001 * maxSpeed_mps * (airData->GetInternalFuelCapacity() / fuelRate_kgps);

		tcAeroAirObject::CalculateSpeedParams(alt_m, 2.0, maxSpeed_mps, fuelRate_kgps, damageLevel, airData);
		speedVectAB_mps.push_back(maxSpeed_mps);

		float stall_mps = airData->GetStallSpeedForAltitude(alt_m);
		speedVectStall_mps.push_back(stall_mps);

		float cruise_mps = 0;
		float cruise_km = tcAeroAirObject::GetAeroCruiseRangeKm(alt_m, airData->GetInternalFuelCapacity(), 0, airData, cruise_mps);
		speedVectCruise_mps.push_back(cruise_mps);

		rangeVectMil_km.push_back(rangeMil_km);
		rangeVectCruise_km.push_back(cruise_km);
	}

	delete airData;

	wxString text = wxString::Format("Spd %f", 999.0);
	resultText->SetLabel(text);

	xyVectorMil->SetData(altVect_m, speedVectMil_mps);
	xyVectorAB->SetData(altVect_m, speedVectAB_mps);
	xyVectorCruise->SetData(altVect_m, speedVectCruise_mps);
	xyVectorStall->SetData(altVect_m, speedVectStall_mps);
	xyVectorRangeCruise->SetData(altVect_m, rangeVectCruise_km);
	xyVectorRangeMil->SetData(altVect_m, rangeVectMil_km);

	plotWindow->Fit(0, 15000, 0, 800);

}

void tcAirCalculationControl::CreateControls(int textCtrlStyle, int textCtrlSizerFlags, int labelTextStyle, int labelTextSizerFlags)
{

    labelText = new wxStaticText(this, wxID_ANY, label, wxDefaultPosition, wxSize(labelWidth, -1), labelTextStyle);
	resultText = new wxStaticText(this, wxID_ANY, "123", wxDefaultPosition, wxSize(3*labelWidth, -1), labelTextStyle);


	plotWindow = new mpWindow( this, -1, wxPoint(10,10), wxSize(800, 800), wxSUNKEN_BORDER );
	plotWindow->EnableDoubleBuffer(true);

	wxFont graphFont(11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);

	bool drawTicks = false; // false for grid
    mpScaleX* xaxis = new mpScaleX(wxT("Altitude [m]"), mpALIGN_BOTTOM, drawTicks, mpX_NORMAL);
    mpScaleY* yaxis = new mpScaleY(wxT("Speed [m/s] or Range [km]"), mpALIGN_LEFT, drawTicks);


    xaxis->SetFont(graphFont);
    yaxis->SetFont(graphFont);

	xaxis->SetLabelFormat(wxT("%.0f"));
	yaxis->SetLabelFormat(wxT("%.0f"));

    xaxis->SetDrawOutsideMargins(false);
    yaxis->SetDrawOutsideMargins(false);



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
	

	wxPen pen;
	pen.SetWidth(2);

	xyVectorMil = new mpFXYVector;
	xyVectorMil->SetContinuity(true);
	pen.SetColour(wxColour(0, 0, 255));
	xyVectorMil->SetPen(pen);
	xyVectorMil->SetName("Mil Speed");
	xyVectorMil->ShowName(false);
	xyVectorMil->SetDrawOutsideMargins(false);

	xyVectorAB = new mpFXYVector;
	xyVectorAB->SetContinuity(true);
	pen.SetColour(wxColour(255, 0, 0));
	xyVectorAB->SetPen(pen);
	xyVectorAB->SetName("AB Speed [m/s]");
	xyVectorAB->ShowName(false);
	xyVectorAB->SetDrawOutsideMargins(false);

	xyVectorStall = new mpFXYVector;
	xyVectorStall->SetContinuity(true);
	pen.SetColour(wxColour(255, 0, 0));
	pen.SetStyle(wxSHORT_DASH);
	xyVectorStall->SetPen(pen);
	xyVectorStall->SetName("Stall Speed [m/s]");
	xyVectorStall->ShowName(false);
	xyVectorStall->SetDrawOutsideMargins(false);

	xyVectorCruise = new mpFXYVector;
	xyVectorCruise->SetContinuity(true);
	pen.SetColour(wxColour(0, 0, 255));
	pen.SetStyle(wxSHORT_DASH);
	xyVectorCruise->SetPen(pen);
	xyVectorCruise->SetName("Cruise Speed [m/s]");
	xyVectorCruise->ShowName(false);
	xyVectorCruise->SetDrawOutsideMargins(false);

	xyVectorRangeCruise = new mpFXYVector;
	xyVectorRangeCruise->SetContinuity(true);
	pen.SetColour(wxColour(0, 0, 0));
	pen.SetStyle(wxSOLID);
	xyVectorRangeCruise->SetPen(pen);
	xyVectorRangeCruise->SetName("Cruise Range [km]");
	xyVectorRangeCruise->ShowName(false);
	xyVectorRangeCruise->SetDrawOutsideMargins(false);

	xyVectorRangeMil = new mpFXYVector;
	xyVectorRangeMil->SetContinuity(true);
	pen.SetColour(wxColour(0, 0, 0));
	pen.SetStyle(wxSHORT_DASH);
	xyVectorRangeMil->SetPen(pen);
	xyVectorRangeMil->SetName("Mil Range [km]");
	xyVectorRangeMil->ShowName(false);
	xyVectorRangeMil->SetDrawOutsideMargins(false);



	plotWindow->AddLayer(xyVectorMil);
	plotWindow->AddLayer(xyVectorAB);
	plotWindow->AddLayer(xyVectorStall);
	plotWindow->AddLayer(xyVectorCruise);
	plotWindow->AddLayer(xyVectorRangeCruise);
	plotWindow->AddLayer(xyVectorRangeMil);
  
	

    int border = 3;

	wxBoxSizer* sizerLabel = new wxBoxSizer(wxHORIZONTAL);
	sizerLabel->Add(labelText, 0, labelTextSizerFlags, border);
	sizerLabel->Add(resultText, 0, labelTextSizerFlags, border);

    wxBoxSizer* sizerTop = new wxBoxSizer(wxVERTICAL);
	sizerTop->SetMinSize(800, 600);

	wxBoxSizer* sizerSpacer = new wxBoxSizer(wxVERTICAL);


    sizerTop->Add(sizerLabel, 0, labelTextSizerFlags, border);
	sizerTop->Add(plotWindow, 3, wxALL | wxEXPAND, border);
	sizerTop->Add(sizerSpacer, 1, wxALL | wxEXPAND, border);

	SetAutoLayout(true);
    SetSizer(sizerTop);

    sizerTop->SetSizeHints(this);
    sizerTop->Fit(this); 

}

tcAirCalculationControl::tcAirCalculationControl(wxWindow* parent, const wxSize& size, 
                                   const wxString& label_) 
: tcEditControl(parent, size, "NOFIELD", label_) 
{
    int textCtrlStyle = 0;
    int textCtrlSizerFlags = wxALL | wxEXPAND;
    int labelTextStyle = 0;
    int labelTextSizerFlags = wxALL;

    CreateControls(textCtrlStyle, textCtrlSizerFlags, labelTextStyle, labelTextSizerFlags);
}

tcAirCalculationControl::tcAirCalculationControl(wxWindow* parent, const wxSize& size, 
                                   const wxString& label_, 
                                   int textCtrlStyle, int textCtrlSizerFlags, int labelTextStyle, int labelTextSizerFlags) 
: tcEditControl(parent, size, "NOFIELD", label_) 
{
    CreateControls(textCtrlStyle, textCtrlSizerFlags, labelTextStyle, labelTextSizerFlags);

	SetInfoOnly(true);
}

tcAirCalculationControl::~tcAirCalculationControl()
{
}