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
#include "SubPanel.h"
#include "TextEditControl.h"

#include "wx/sizer.h"


BEGIN_EVENT_TABLE(tcSubPanel, tcBasePanel)

END_EVENT_TABLE()

    
    

void tcSubPanel::InitializeControls()
{
    tcTextEditControl* ctrl_depth = new tcTextEditControl(this, wxSize(100, -1), "MaxDepth_m", "Max Depth [m]");
    AddControl(ctrl_depth);

    tcTextEditControl* ctrl_cavitation = new tcTextEditControl(this, wxSize(100, -1), "CavitationSlope", "Cavitation Slope");
    AddControl(ctrl_cavitation);

    tcTextEditControl* ctrl_de = new tcTextEditControl(this, wxSize(100, -1), "IsDieselElectric", "Diesel-Electric?");
    AddControl(ctrl_de);

    tcTextEditControl* ctrl_batcap = new tcTextEditControl(this, wxSize(100, -1), "BatteryCapacity_kWhr", "Battery Energy [kWhr]");
    AddControl(ctrl_batcap);

    tcTextEditControl* ctrl_batdrain = new tcTextEditControl(this, wxSize(100, -1), "BatteryRate_kW", "Battery Drain [kW]");
    AddControl(ctrl_batdrain);

    tcTextEditControl* ctrl_batcharge = new tcTextEditControl(this, wxSize(100, -1), "BatteryCharge_kW", "Battery Charge [kW]");
    AddControl(ctrl_batcharge);


    wxBoxSizer* sizerTop = new wxBoxSizer(wxHORIZONTAL);

    wxBoxSizer* sizerLeft = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer* sizerRight = new wxBoxSizer(wxVERTICAL);

    int border = 3;
    int style = wxALL | wxALIGN_CENTER | wxEXPAND;
    sizerLeft->Add(ctrl_depth, 0, style, border);
    sizerLeft->Add(ctrl_cavitation, 0, style, border);
    sizerLeft->Add(ctrl_de, 0, style, border);
    sizerLeft->Add(ctrl_batcap, 0, style, border);
    sizerLeft->Add(ctrl_batdrain, 0, style, border);
    sizerLeft->Add(ctrl_batcharge, 0, style, border);

    sizerTop->Add(sizerLeft, 1, style, border);
    sizerTop->Add(sizerRight, 1, style, border);

    this->SetSizer(sizerTop);
    sizerTop->SetSizeHints(this);

}





tcSubPanel::tcSubPanel(wxWindow* parent, const wxString& table_) 
: tcBasePanel(parent, table_, "SubPanel")
{
    InitializeControls();
}

tcSubPanel::~tcSubPanel()
{
}