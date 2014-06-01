/**
**  @file tcDatabaseViewer.cpp
*/
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

#include "stdwx.h"

#ifndef WX_PRECOMP
#include "wx/wx.h" 
#endif

#include "tcDatabaseViewer.h"
#include "tv_types.h"
#include "wxcommands.h"
#include "common/tinyxml.h"
#include "tcTexture2D.h"
#include "tcButton.h"
#include "tcDatabase.h"
#include "tcDatabaseObject.h"
#include "tcDatabaseIterator.h"
#include "tcDatabaseInfoWindow.h"
#include "tcDatabaseBrowsePanel.h"
#include "tcMissileDBObject.h" // for missile envelope test feature
#include "tcMissileObject.h" // for missile envelope test feature
#include "tcJetDBObject.h" // for aero air performance test feature
#include "tcAeroAirObject.h" // for aero air performance test feature
#include "tc3DViewer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif 


BEGIN_EVENT_TABLE(tcDatabaseViewer, tcXmlWindow)
    EVT_COMMAND(101, wxEVT_COMMAND_BUTTON_CLICKED, tcDatabaseViewer::BrowseSurface)
    EVT_COMMAND(102, wxEVT_COMMAND_BUTTON_CLICKED, tcDatabaseViewer::BrowseSub)
    EVT_COMMAND(103, wxEVT_COMMAND_BUTTON_CLICKED, tcDatabaseViewer::BrowseAir)
    EVT_COMMAND(104, wxEVT_COMMAND_BUTTON_CLICKED, tcDatabaseViewer::BrowseHelo)
    EVT_COMMAND(105, wxEVT_COMMAND_BUTTON_CLICKED, tcDatabaseViewer::BrowseLand)
    EVT_COMMAND(106, wxEVT_COMMAND_BUTTON_CLICKED, tcDatabaseViewer::BrowseMissile)
    EVT_COMMAND(107, wxEVT_COMMAND_BUTTON_CLICKED, tcDatabaseViewer::BrowseTorpedo)
    EVT_COMMAND(108, wxEVT_COMMAND_BUTTON_CLICKED, tcDatabaseViewer::BrowseBallistic)
	EVT_COMMAND(-1, wxEVT_COMMAND_TEXT_UPDATED, tcDatabaseViewer::SelectDisplayClass)
END_EVENT_TABLE()


void tcDatabaseViewer::BrowseSurface(wxCommandEvent& event)
{
    SetClassificationMask(PTYPE_SURFACE);
    SetButtonOn(0);
}

void tcDatabaseViewer::BrowseSub(wxCommandEvent& event)
{
    SetClassificationMask(PTYPE_SUBMARINE);
    SetButtonOn(1);
}

void tcDatabaseViewer::BrowseAir(wxCommandEvent& event)
{
    SetClassificationMask(PTYPE_FIXEDWING);
    SetButtonOn(2);
}

void tcDatabaseViewer::BrowseHelo(wxCommandEvent& event)
{
    SetClassificationMask(PTYPE_HELO);
    SetButtonOn(3);
}

void tcDatabaseViewer::BrowseLand(wxCommandEvent& event)
{
    SetClassificationMask(PTYPE_GROUND);
    SetButtonOn(4);
}

void tcDatabaseViewer::BrowseMissile(wxCommandEvent& event)
{
    SetClassificationMask(PTYPE_MISSILE);
    SetButtonOn(5);
}

void tcDatabaseViewer::BrowseTorpedo(wxCommandEvent& event)
{
    SetClassificationMask(PTYPE_TORPEDO);
    SetButtonOn(6);
}

void tcDatabaseViewer::BrowseBallistic(wxCommandEvent& event)
{
    SetClassificationMask(PTYPE_BALLISTIC);
    SetButtonOn(7);
}




const std::string& tcDatabaseViewer::GetDisplayClass() const
{
    return displayClassName;
}



void tcDatabaseViewer::SetClassificationMask(unsigned int mask)
{
    if (mask == classificationMask) return;

    classificationMask = mask;

	browsePanel->SetClassificationMask(mask);
}


/**
 *
 */
void tcDatabaseViewer::Draw()
{
    StartDraw();

    // draw border here to work around scroll bar border issues (for browse/select box on left)
    wxSize browseSize = browsePanel->GetSize();
    DrawRectangleR(50, 151, float(browseSize.GetWidth()), float(browseSize.GetHeight()), 
        Vec4(0.5, 0.5, 0.5, 0.5));

	FinishDraw();
}


void tcDatabaseViewer::InitializeButtons()
{
    size_t nButtons = 8;
    float x = 50.0f;
    float y = 50.0f;
    float width = 64.0f;

    wxASSERT(buttons.size() == 0);
    buttons.clear();

    for (size_t n=0; n<nButtons; n++)
    {
        tcButton* button = new tcButton(this, wxPoint(x, y), wxSize(width, width));
        buttons.push_back(button);

        button->SetActive(true);
        button->SetCommand(101 + (long)n);
        
        x += width + 16.0f;

        std::string caption;

        switch (n)
        {
        case 0: 
            caption = "Surface naval"; 
            button->LoadImages("dbviewer\\surface_off.png", "dbviewer\\surface_on.png", 
                "dbviewer\\surface_over.png", "dbviewer\\surface_on.png");
            break;
        case 1: 
            caption = "Submarine"; 
            button->LoadImages("dbviewer\\sub_off.png", "dbviewer\\sub_on.png", 
                "dbviewer\\sub_over.png", "dbviewer\\sub_on.png");
            break;
        case 2: 
            caption = "Air, fixed wing"; 
            button->LoadImages("dbviewer\\air_off.png", "dbviewer\\air_on.png", 
                "dbviewer\\air_over.png", "dbviewer\\air_on.png");
            break;
        case 3: 
            caption = "Air, rotary wing"; 
            button->LoadImages("dbviewer\\helo_off.png", "dbviewer\\helo_on.png", 
                "dbviewer\\helo_over.png", "dbviewer\\helo_on.png");
            break;
        case 4: 
            caption = "Land";
            button->LoadImages("dbviewer\\land_off.png", "dbviewer\\land_on.png", 
                "dbviewer\\land_over.png", "dbviewer\\land_on.png");
            break;
        case 5: 
            caption = "Missile";
            button->LoadImages("dbviewer\\missile_off.png", "dbviewer\\missile_on.png", 
                "dbviewer\\missile_over.png", "dbviewer\\missile_on.png");
            break;
        case 6: 
            caption = "Torpedo";
            button->LoadImages("dbviewer\\torpedo_off.png", "dbviewer\\torpedo_on.png", 
                "dbviewer\\torpedo_over.png", "dbviewer\\torpedo_on.png");
            break;
        case 7: 
            caption = "Ballistic";
            button->LoadImages("dbviewer\\ballistic_off.png", "dbviewer\\ballistic_on.png", 
                "dbviewer\\ballistic_over.png", "dbviewer\\ballistic_on.png");
            break;
        default: 
            caption = "Error";
            button->LoadImages("dbviewer\\test_button_off.png", "dbviewer\\test_button_on.png", 
                "dbviewer\\test_button_on.png", "dbviewer\\test_button_on.png");
            break;
        }

        button->SetMouseOverCaption(caption);
        button->SetShowCaptionWhenOn(true);
    }

		
}

void tcDatabaseViewer::InitializeBrowsePanel()
{
	browsePanel = new tcDatabaseBrowsePanel(this, wxPoint(50, 150), wxSize(220, mnHeight-200), "BrowsePanel", this);
}


void tcDatabaseViewer::InitializeDatabaseInfoWindow()
{
	databaseInfoWindow = new tcDatabaseInfoWindow(wxPoint(300, 150), "xml/database_info.xml", "DBViewInfo", this);
    wxASSERT(databaseInfoWindow != 0);

    databaseInfoWindow->SetBackgroundColor(Vec4(0.1f, 0.1f, 0.1f, 0.2f));
    databaseInfoWindow->SetButtonDisable(86, true); // disable the close button
    databaseInfoWindow->SetDragable(false);
    //databaseInfoWindow->SetUseRenderSurface(true);
}


void tcDatabaseViewer::OnChar(wxKeyEvent& event)
{
    int nChar = event.GetKeyCode();

    switch (nChar)
    {
    case '?':
        {
            wxString msg;
            msg += "Key commands:\n";
            msg += "    ? - Show key commands\n";
            msg += "    A - Write aircraft model info to csv file for selected aircraft (aero model only)\n";
            msg += "    E - Evaluate missile range\n";
            

            wxMessageBox(msg, "Key Commands");
        }
        break;
    case 'A':
        {
            database::tcDatabaseObject* databaseObject = databaseInfoWindow->GetDatabaseObject();
            database::tcJetDBObject* airData = dynamic_cast<database::tcJetDBObject*>(databaseObject);
            if (airData == 0) return;
            tcAeroAirObject* air = new tcAeroAirObject(airData);
            if (air == 0) return;

            wxString fileName = wxString::Format("log/%s-performance.csv", airData->mzClass.c_str());
            tcFile logFile(fileName.ToStdString());
            logFile.Printf("Alt [m],Speed-MIL [kts],Speed-AB [kts],Speed-Cruise [kts],Range-MIL [km],Range-AB [km],Range-Cruise [km]\n");

            for (float alt_m=0; alt_m<=airData->maxAltitude_m; alt_m+=1000.0f)
            {
                float speedMil_mps;
                float fuelRateMil_kgps;
                air->CalculateSpeedParams(alt_m, 1.0f, speedMil_mps, fuelRateMil_kgps, air->GetDamageLevel(), air->mpDBObject);
                float rangeMil_km = 0.001f * speedMil_mps * (airData->mfFuelCapacity_kg / fuelRateMil_kgps);

                float speedAB_mps;
                float fuelRateAB_kgps;
                air->CalculateSpeedParams(alt_m, 2.0f, speedAB_mps, fuelRateAB_kgps, air->GetDamageLevel(), air->mpDBObject);
                float rangeAB_km = 0.001f * speedAB_mps * (airData->mfFuelCapacity_kg / fuelRateAB_kgps);

                float speedCruise_mps = air->GetCruiseSpeedForAltitude(alt_m);
                float rangeCruise_km = air->GetCruiseRangeKm(alt_m);

                logFile.Printf("%f,%f,%f,%f,%f,%f,%f\n", alt_m, speedMil_mps*C_MPSTOKTS, speedAB_mps*C_MPSTOKTS, speedCruise_mps*C_MPSTOKTS,
                    rangeMil_km, rangeAB_km, rangeCruise_km);
            }


        }
        break;

    case 'E':
        {
            wxASSERT(databaseInfoWindow != 0);
            database::tcDatabaseObject* databaseObject = databaseInfoWindow->GetDatabaseObject();
            database::tcMissileDBObject* missileData = dynamic_cast<database::tcMissileDBObject*>(databaseObject);
            if (missileData != 0)
            {
                wxTextEntryDialog dlg(this, "Enter <min range km>, <max range km>, <step size km>, launch speed [kts], launch alt [m], target alt [m]", "Missile Range Evaluation");
                wxString defaultText = wxString::Format("%.1f, %.1f, %.1f, %.0f, %.0f, %.0f", missileData->minRange_km, missileData->maxRange_km, 1.0f, 0.0f, 3000.0f, 1000.0f);
                dlg.SetValue(defaultText);

                if (dlg.ShowModal() == wxID_OK)
                {
                    double minEval_km = missileData->minRange_km;
                    double maxEval_km = missileData->maxRange_km;
                    double evalStep_km = 1.0;
                    double launchSpeed_kts = 0;
                    double launchAlt_m = 3000.0;
                    double targetAlt_m = 1000.0;

                    wxString s = dlg.GetValue();

                    s.BeforeFirst(',').ToDouble(&minEval_km);
                    s = s.AfterFirst(',');
                    s.BeforeFirst(',').ToDouble(&maxEval_km);
                    s = s.AfterFirst(',');
                    s.BeforeFirst(',').ToDouble(&evalStep_km);
                    s = s.AfterFirst(',');
                    s.BeforeFirst(',').ToDouble(&launchSpeed_kts);
                    s = s.AfterFirst(',');
                    s.BeforeFirst(',').ToDouble(&launchAlt_m);
                    s = s.AfterFirst(',');
                    s.BeforeFirst(',').ToDouble(&targetAlt_m);

                    float maxRange_km = tcMissileObject::EstimateRangeKm(minEval_km, maxEval_km, evalStep_km, launchSpeed_kts, launchAlt_m, targetAlt_m, missileData);
                    float maxRange2_km = tcMissileObject::EstimateRangeFaster(minEval_km, maxEval_km, 7, launchSpeed_kts, launchAlt_m, targetAlt_m, missileData);

                    wxString msg = wxString::Format("Max Range: %.0f km (%.0f km) for missile %s", maxRange_km, maxRange2_km, missileData->mzClass.c_str());
                    wxMessageBox(msg, "Message");
                }
            }
        }
        break;
    default:
        break;
    }
}

/**
 *
 */
void tcDatabaseViewer::OnMouseMove(wxMouseEvent& event) 
{
	mousePosition = event.GetPosition();
}

/**
 *
 */
void tcDatabaseViewer::OnLButtonDown(wxMouseEvent& event) 
{
    if (!mbActive) 
    {
        event.Skip();
        return;
    }

    mousePosition = event.GetPosition();
}

void tcDatabaseViewer::OnSize(wxSizeEvent& event)
{
    tcXmlWindow::OnSize(event);

    wxSize size = event.GetSize();

    if (browsePanel != 0)
    {
        browsePanel->SetSize(50, 150, 220, mnHeight - 200);
    }
}

void tcDatabaseViewer::SetButtonOn(size_t idx)
{
    wxASSERT(buttons.size() == 8);

    // first set all buttons off
    for (size_t n=0; n<buttons.size(); n++)
    {
        buttons[n]->SetOn(false);
    }

    // set indicated button on
    if (idx < buttons.size())
    {
        buttons[idx]->SetOn(true);
    }
    else
    {
        wxASSERT(false);
    }

}

void tcDatabaseViewer::SelectDisplayClass(wxCommandEvent& event)
{
	std::string className = event.GetString().c_str();

	SelectDisplayClass(className);
}

void tcDatabaseViewer::SelectDisplayClass(const std::string& className)
{
    displayClassName = className;
    databaseInfoWindow->SetDatabaseClassName(className);
    if (viewer)
    {
        viewer->SetDatabaseViewClass(className);
    }
}


void tcDatabaseViewer::Set3DViewer(tc3DViewer* viewer_)
{
    viewer = viewer_;
}

/**
*
*/
tcDatabaseViewer::tcDatabaseViewer(wxWindow *parent, 
                             const wxPoint& pos, const wxSize& size, const wxString& name) 
                             : 
    tcXmlWindow(parent, pos, size, "xml/database_viewer.xml", name),
	basePosition(20, 50),
    classificationMask(0),
    displayClassName(""),
    viewer(0)
{

	LoadBackgroundImage("start_background_plain.jpg");

    if (!config)
    {
        fprintf(stderr, "tcDatabaseViewer::tcDatabaseViewer - NULL xml config node\n");
        return;
    }

    TiXmlNode* root = config->FirstChild("Window");
    if (!root)
    {
        fprintf(stderr, "tcDatabaseViewer::tcDatabaseViewer - "
			"Missing top level <Window> tag\n");
        return;
    }

    InitializeButtons();
	InitializeBrowsePanel();
    InitializeDatabaseInfoWindow();
	
    
    SetClassificationMask(PTYPE_SURFACE);
    SetButtonOn(0);

    SetBorderDraw(true);
}

/**
* Embedded window version of constructor
*/
tcDatabaseViewer::tcDatabaseViewer(tc3DWindow2* parent, 
                             const wxPoint& pos, const wxSize& size, const wxString& name) 
                             : 
    tcXmlWindow(parent, pos, size, "xml/database_viewer.xml", name, parent),
	basePosition(20, 50),
    classificationMask(0),
    displayClassName(""),
    viewer(0)
{
	//LoadBackgroundImage("start_background_plain.jpg");

    if (!config)
    {
        fprintf(stderr, "tcDatabaseViewer::tcDatabaseViewer - NULL xml config node\n");
        return;
    }

    TiXmlNode* root = config->FirstChild("Window");
    if (!root)
    {
        fprintf(stderr, "tcDatabaseViewer::tcDatabaseViewer - "
			"Missing top level <Window> tag\n");
        return;
    }

    InitializeButtons();
	InitializeBrowsePanel();
    InitializeDatabaseInfoWindow();
	
    
    SetClassificationMask(PTYPE_SURFACE);
    SetButtonOn(0);

    SetBorderDraw(true);
}

tcDatabaseViewer::~tcDatabaseViewer() 
{
}


