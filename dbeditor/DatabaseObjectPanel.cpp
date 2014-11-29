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
#include "DatabaseObjectPanel.h"
#include "TextEditControl.h"
#include "ComboEditControl.h"
#include "DatabaseManager.h"

#include "wx/sizer.h"
#include "wx/textctrl.h"

BEGIN_EVENT_TABLE(tcDatabaseObjectPanel, tcBasePanel)
END_EVENT_TABLE()

    
/**
* Set up label--value pairs for combo boxes to decode integer fields
*/
void tcDatabaseObjectPanel::InitializeComboTables()
{
    LoadLabelValueData("config/classification.txt", classificationLabels, classificationValues);

    LoadLabelValueData("config/modeltype.txt", modelTypeLabels, modelTypeValues);
}

void tcDatabaseObjectPanel::InitializeControls()
{
    wxASSERT(controls.size() == 0);
    wxASSERT(fieldList.size() == 0);

    
    tcTextEditControl* ctrl_natoClass = new tcTextEditControl(this, wxSize(100, -1), "NATO_ASCC", "NATO/ASCC Name");
    AddControl(ctrl_natoClass);

    tcComboEditControl* ctrl_mnModelType = new tcComboEditControl(this, wxSize(100, -1), "ModelClassId", "Sim Type", modelTypeValues, modelTypeLabels);
    AddControl(ctrl_mnModelType);

    tcComboEditControl* ctrl_mnType = new tcComboEditControl(this, wxSize(100, -1), "ClassificationId", "Classification", classificationValues, classificationLabels);
    AddControl(ctrl_mnType);

    tcTextEditControl* ctrl_cost = new tcTextEditControl(this, wxSize(100, -1), "Cost", "Cost");
    AddControl(ctrl_cost);

    tcTextEditControl* ctrl_weight = new tcTextEditControl(this, wxSize(100, -1), "Weight_kg", "Weight [kg]");
    AddControl(ctrl_weight);

    tcTextEditControl* ctrl_volume = new tcTextEditControl(this, wxSize(100, -1), "Volume_m3", "Volume [m3]");
    AddControl(ctrl_volume);

    tcTextEditControl* ctrl_images = new tcTextEditControl(this, wxSize(100, -1), "ImageList", "Image List");
    AddControl(ctrl_images);

    tcTextEditControl* ctrl_icon = new tcTextEditControl(this, wxSize(-1, 200), "IconFileName", "Icon Filename");
    AddControl(ctrl_icon);

    tcTextEditControl* ctrl_modelfile = new tcTextEditControl(this, wxSize(100, -1), "ModelFileName", "3D Model");
    AddControl(ctrl_modelfile);

    tcTextEditControl* ctrl_description = new tcTextEditControl(this, wxSize(100, -1), "Description", "Description");
    AddControl(ctrl_description);


    int border = 1;
    wxBoxSizer* sizerLeft = new wxBoxSizer(wxVERTICAL);
    sizerLeft->Add(ctrl_natoClass, 0, wxALL | wxALIGN_CENTER | wxEXPAND, border);
    sizerLeft->Add(ctrl_mnModelType, 0, wxALL | wxALIGN_CENTER | wxEXPAND, border);
    sizerLeft->Add(ctrl_mnType, 0, wxALL | wxALIGN_CENTER | wxEXPAND, border);
    sizerLeft->Add(ctrl_cost, 0, wxALL | wxALIGN_CENTER | wxEXPAND, border);
    sizerLeft->Add(ctrl_weight, 0, wxALL | wxALIGN_CENTER | wxEXPAND, border);
    sizerLeft->Add(ctrl_volume, 0, wxALL | wxALIGN_CENTER | wxEXPAND, border);
    sizerLeft->Add(ctrl_images, 0, wxALL | wxALIGN_CENTER | wxEXPAND, border);
    sizerLeft->Add(ctrl_icon, 0, wxALL | wxALIGN_CENTER | wxEXPAND, border);
    sizerLeft->Add(ctrl_modelfile, 0, wxALL | wxALIGN_CENTER | wxEXPAND, border);


    wxBoxSizer* sizerTop = new wxBoxSizer(wxHORIZONTAL);


    sizerTop->Add(sizerLeft, 0, wxALL | wxALIGN_CENTER | wxEXPAND, border);
    sizerTop->Add(ctrl_description, 2, wxALL | wxALIGN_CENTER | wxEXPAND, border);
   
    this->SetSizer(sizerTop);
    sizerTop->SetSizeHints(this);

}





tcDatabaseObjectPanel::tcDatabaseObjectPanel(wxWindow* parent, const wxString& table_) 
: tcBasePanel(parent, table_, "DatabaseObjectPanel")
{
    InitializeComboTables();

    InitializeControls();
}

tcDatabaseObjectPanel::~tcDatabaseObjectPanel()
{
}