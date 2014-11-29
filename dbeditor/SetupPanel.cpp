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
#include "SetupPanel.h"
#include "TextEditControl.h"
#include "ComboEditControl.h"
#include "DatabaseManager.h"
#include "SelectFromTablesDialog.h"
#include "RenameSetupDialog.h"

#include "wx/grid.h"
#include "wx/sizer.h"
#include "wx/textfile.h"
#include "wx/xml/xml.h"
#include "wx/msgdlg.h"
#include "wx/choicdlg.h"
#include "wx/frame.h"
#include "wx/button.h"
#include "wx/stattext.h"

BEGIN_EVENT_TABLE(tcSetupPanel, tcBasePanel)
    EVT_GRID_CELL_CHANGE(tcSetupPanel::OnGridCellChange)
    EVT_GRID_CELL_LEFT_DCLICK(tcSetupPanel::OnGridLeftDClick)
    EVT_GRID_CELL_RIGHT_CLICK(tcSetupPanel::OnGridRightClick)
    EVT_GRID_CMD_LABEL_RIGHT_CLICK(wxID_ANY, tcSetupPanel::OnGridLabelRClick)
    EVT_BUTTON(SETUP_SELECT, tcSetupPanel::OnTextUpdated)
    EVT_BUTTON(NEW_SETUP, tcSetupPanel::OnNewSetup)
    EVT_BUTTON(RENAME_SETUP, tcSetupPanel::OnRenameSetup)
    EVT_BUTTON(DUPLICATE_SETUP, tcSetupPanel::OnDuplicateSetup)
    EVT_BUTTON(DELETE_SETUP, tcSetupPanel::OnDeleteSetup)
END_EVENT_TABLE()



//DECLARE_EVENT_TYPE(JUMP_TO, -1)
//DEFINE_EVENT_TYPE(JUMP_TO)



wxFrame* tcSetupPanel::eventFrame = 0;


int DescendingSort2(int* first, int* second)
{
    if (*first < *second)
    {
        return 1;
    }
    else if (*first > *second)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

void tcSetupPanel::AddDefaultLauncherLoadout(const wxString& loadoutName)
{
    tcDatabaseManager* databaseManager = tcDatabaseManager::Get();

    wxArrayString fields;

    fields.push_back("LauncherId");
    fields.push_back("Item");
    fields.push_back("Quantity");

    std::vector<wxArrayString> newData;
    std::vector<int> launcherIdList = GetLauncherIdList();
    for (size_t n=0; n<launcherIdList.size(); n++)
    {
        wxString query = wxString::Format("select LauncherClass from platform_launcher where DatabaseClass=\"%s\" and LauncherId=%d",
            databaseClass.c_str(), launcherIdList[n]);
        wxArrayString launcherClassArray = databaseManager->ExecuteQuery(query);
        wxString launcherClass = (launcherClassArray.size() > 0) ? launcherClassArray[0] : "";

        query.Printf("select ChildClass from launcher_configuration where DatabaseClass=\"%s\"", launcherClass.c_str());
        wxArrayString itemArray = databaseManager->ExecuteQuery(query);
        wxString item = (itemArray.size() > 0) ? itemArray[0] : "";

        query.Printf("select ChildCapacity from launcher_configuration where DatabaseClass=\"%s\" and ChildClass=\"%s\"",
                launcherClass.c_str(), item.c_str());
        wxArrayString quantityArray = databaseManager->ExecuteQuery(query);
        wxString quantity = (quantityArray.size() > 0) ? quantityArray[0] : "";

        wxArrayString newEntry;
        newEntry.push_back(wxString::Format("%d", launcherIdList[n]));
        newEntry.push_back(item);
        newEntry.push_back(quantity);
        newData.push_back(newEntry);
    }

    databaseManager->UpdatePlatformTableData("launcher_loadout", 
        loadoutName, fields, newData, "");
}

/**
* Checks that cells in <col> have a reference in one of the tables listed in <referenceTables_>
*/
void tcSetupPanel::CheckTableReferences(wxGrid* grid, int col, const wxArrayString& referenceTables_)
{
    wxASSERT(grid != 0);

    int nRows = grid->GetNumberRows();
    int nCols = grid->GetNumberCols();

    tcDatabaseManager* databaseManager = tcDatabaseManager::Get();

    for (int row=0; row<nRows; row++)
    {
        wxString matchingTable;
        wxString databaseClass = grid->GetCellValue(row, col);
        bool referenceFound = databaseManager->PlatformExistsInTableList(referenceTables_, databaseClass, matchingTable);
        if (referenceFound)
        {
            grid->SetCellFont(row, 0, *wxNORMAL_FONT);
            grid->SetCellTextColour(row, 0, wxColour(0, 0, 0));
        }
        else
        {
            grid->SetCellFont(row, 0, errorFont);
            grid->SetCellTextColour(row, 0, wxColour(120, 0, 0));
        }
    }
}

void tcSetupPanel::DeleteSelectedRows()
{
    wxGrid* tableCtrl = launcherLoadout;

    wxArrayInt selectedRows = tableCtrl->GetSelectedRows();
    if (selectedRows.size() == 0) return;

    selectedRows.Sort(DescendingSort2);

    for (size_t n=0; n<selectedRows.size(); n++)
    {
        tableCtrl->DeleteRows(selectedRows[n]);
    }

}

void tcSetupPanel::InsertRowAbove()
{
    wxGrid* tableCtrl = launcherLoadout;

    wxArrayInt selectedRows = tableCtrl->GetSelectedRows();
    if (selectedRows.size() == 0) return;

    tableCtrl->InsertRows(selectedRows[0]);
}

int tcSetupPanel::GetCurrentSetupIndex()
{
    for (size_t n=0; n<setupNames.size(); n++)
    {
        if (setupNames[n] == currentSetup) return int(n);
    }

    return -1;
}

/**
* @return vector of magazine id's used by currently selected database class
*/
const std::vector<int> tcSetupPanel::GetMagazineIdList()
{
    return tcDatabaseManager::Get()->GetIdList("platform_magazine", databaseClass, "MagazineId");
}

/**
* @return vector of MagazineClass names
*/
const wxArrayString& tcSetupPanel::GetMagazineNameList()
{
    static wxArrayString nameList;

    nameList.clear();

    wxArrayString fields;
    fields.push_back("MagazineClass");

    std::vector<wxArrayString> data = tcDatabaseManager::Get()->GetPlatformTableData("platform_magazine", databaseClass, fields);

    for (size_t n=0; n<data.size(); n++)
    {
        nameList.push_back(data[n][0]);
    }

    return nameList;
}


const wxString& tcSetupPanel::GetLauncherSummary(const std::vector<wxArrayString>& data)
{
    static wxString summary;
    summary.clear();

	tcDatabaseManager* databaseManager = tcDatabaseManager::Get();
	wxString matchingTable;
	double fuel_kg = 0;
	double maxTakeoffWeight_kg = 0;
	double weight_kg = 0;
	double dryWeight_kg = 0;
	wxArrayString aircraftFields;
	aircraftFields.push_back("FuelCapacity_kg");
	aircraftFields.push_back("MaxTakeoffWeight_kg");
	aircraftFields.push_back("Weight_kg");

	if (databaseManager->PlatformExistsInTableList(aircraftTables, databaseClass, matchingTable))
	{
		std::vector<wxArrayString> aircraftData = databaseManager->GetPlatformTableData(matchingTable, databaseClass, aircraftFields);
		if (aircraftData.size() > 0)
		{
			aircraftData[0][0].ToDouble(&fuel_kg);
			aircraftData[0][1].ToDouble(&maxTakeoffWeight_kg);
			aircraftData[0][2].ToDouble(&dryWeight_kg);
		}
		else
		{
			wxASSERT(false);
		}
	}
	else
	{
		return summary;
	}

	weight_kg = dryWeight_kg;

	wxArrayString itemFields;
	itemFields.push_back("Weight_kg");

	wxArrayString fueltankFields;
	fueltankFields.push_back("FuelCapacity_kg");

	// iterate through each item in data and update quantity, volume, and weight
	for (size_t n=0; n<data.size(); n++)
	{
		wxString item = data[n][0];
		long quantity_n = 0;
		data[n][1].ToLong(&quantity_n);

		wxString matchingTable;
		if (databaseManager->PlatformExistsInTableList(launcherEquipmentTables, item, matchingTable))
		{
			std::vector<wxArrayString> itemData = databaseManager->GetPlatformTableData(matchingTable, item, itemFields);
			if (itemData.size() > 0)
			{
				double itemWeight_kg = 0;
				itemData[0][0].ToDouble(&itemWeight_kg);

				weight_kg += double(quantity_n) * itemWeight_kg;
			}
			if (matchingTable == "fueltank")
			{
				std::vector<wxArrayString> tankData = databaseManager->GetPlatformTableData(matchingTable, item, fueltankFields);
				if (tankData.size() > 0)
				{
					double fueltankFuel_kg = 0;
					tankData[0][0].ToDouble(&fueltankFuel_kg);
					weight_kg += double(quantity_n) * fueltankFuel_kg;
				}
			}
		}
	}
    


	summary.Printf("TOW: %.0f/%.0f kg",
        weight_kg + fuel_kg, maxTakeoffWeight_kg);
    return summary;
}



const wxString& tcSetupPanel::GetMagazineSummary(const wxString& magazineClass, const std::vector<wxArrayString>& data, bool& isOkay)
{
    static wxString summary;
    summary.clear();

    tcDatabaseManager* databaseManager = tcDatabaseManager::Get();

    // get magazine capacity
    wxArrayString storesFields;
    storesFields.push_back("Capacity");
    storesFields.push_back("MaxVolume_m3");
    storesFields.push_back("MaxWeight_kg");

    long maxQuantity = 0;
    double maxVol_m3 = 0;
    double maxWeight_kg = 0;
    std::vector<wxArrayString> magData = databaseManager->GetPlatformTableData("stores", magazineClass, storesFields);
    if (magData.size() > 0)
    {
        magData[0][0].ToLong(&maxQuantity);
        magData[0][1].ToDouble(&maxVol_m3);
        magData[0][2].ToDouble(&maxWeight_kg);
    }

    long quantity = 0;
    float vol_m3 = 0;
    float weight_kg = 0;

    wxArrayString itemFields;
    itemFields.push_back("Weight_kg");
    itemFields.push_back("Volume_m3");
    // iterate through each item in data and update quantity, volume, and weight
    for (size_t n=0; n<data.size(); n++)
    {
        wxString item = data[n][0];
        long quantity_n = 0;
        data[n][1].ToLong(&quantity_n);

        wxString matchingTable;
        if (databaseManager->PlatformExistsInTableList(storesEquipmentTables, item, matchingTable))
        {
            std::vector<wxArrayString> itemData = databaseManager->GetPlatformTableData(matchingTable, item, itemFields);
            if (itemData.size() > 0)
            {
                double itemWeight_kg = 0;
                double itemVolume_m3 = 0;
                itemData[0][0].ToDouble(&itemWeight_kg);
                itemData[0][1].ToDouble(&itemVolume_m3);
                quantity += quantity_n;
                weight_kg += float(quantity_n) * float(itemWeight_kg);
                vol_m3 += float(quantity_n) * float(itemVolume_m3);
            }
        }
    }

    summary.Printf("%d/%d, %.0f/%.0f kg, %.0f/%.0f m3", 
        quantity, maxQuantity, weight_kg, float(maxWeight_kg), vol_m3, float(maxVol_m3));

	isOkay = ((maxQuantity == 0) || (quantity <= maxQuantity)) &&
			 ((maxWeight_kg == 0) || (weight_kg <= float(maxWeight_kg))) &&
			 ((maxVol_m3 == 0) || (vol_m3 <= float(maxVol_m3)));

    return summary;
}


/**
* @return vector of launcher id's used by currently selected database class
*/
const std::vector<int> tcSetupPanel::GetLauncherIdList()
{
    return tcDatabaseManager::Get()->GetIdList("platform_launcher", databaseClass, "LauncherId");
}


/**
* Find a new setup name of the form <databaseclass>-<integer>
*/
const wxString& tcSetupPanel::GetNewSetupName()
{
    static wxString candidateName;
    wxArrayString fieldList;
    fieldList.push_back("SetupName");

    int suffix = 1;
    for (int suffix=1; suffix<100; suffix++)
    {
        candidateName = databaseClass + wxString::Format("-%d", suffix);
        wxString additionalConstraint = wxString::Format("SetupName=\"%s\"", candidateName.c_str());
        std::vector<wxArrayString> data = 
            tcDatabaseManager::Get()->GetPlatformTableData("platform_setup", databaseClass, fieldList, additionalConstraint);
        if (data.size() == 0) return candidateName;
    }

    wxASSERT(false); // couldn't find a new name
    candidateName = databaseClass + wxString("Error");
    return candidateName;
}

/**
* @return true if current selected database class has launchers
*/
bool tcSetupPanel::HasLaunchers()
{
    wxArrayString fieldList;
    fieldList.push_back("LauncherClass");

    std::vector<wxArrayString> data = 
        tcDatabaseManager::Get()->GetPlatformTableData("platform_launcher", databaseClass, fieldList, "");
    return (data.size() > 0);
}

bool tcSetupPanel::HasMagazines()
{
    wxArrayString fieldList;
    fieldList.push_back("MagazineClass");

    std::vector<wxArrayString> data = 
        tcDatabaseManager::Get()->GetPlatformTableData("platform_magazine", databaseClass, fieldList, "");
    return (data.size() > 0);
}

bool tcSetupPanel::HasAirComplement()
{
    if ((table != "ship") && (table != "ground")) return false;

    wxArrayString fieldList;
    fieldList.push_back("FlightportClass");

    std::vector<wxArrayString> data = 
        tcDatabaseManager::Get()->GetPlatformTableData(table, databaseClass, fieldList, "");
    if (data.size() > 0)
    {
        return (data[0].size() > 0);
    }
    return false;
}

void tcSetupPanel::UpdateSetupData()
{
    setupData =
        tcDatabaseManager::Get()->GetPlatformTableData("platform_setup", databaseClass, setupFields);

    setupNames.clear();
    for (size_t n=0; n<setupData.size(); n++)
    {
        setupNames.push_back(setupData[n][0]);
    }

    setupComboBox->SetValuesAndLabels(setupNames, setupNames);
}


void tcSetupPanel::InitializePanel()
{
    // create sizer
    wxBoxSizer* sizerTop;
    wxBoxSizer* sizerRow1;
    wxBoxSizer* sizerRow2;

    sizerTop = new wxBoxSizer(wxVERTICAL);
    sizerRow1 = new wxBoxSizer(wxHORIZONTAL);
    sizerRow2 = new wxBoxSizer(wxHORIZONTAL);

    long gridStyle = wxWANTS_CHARS; //|wxFULL_REPAINT_ON_RESIZE|wxHSCROLL|wxVSCROLL;
    int border = 15;

    // add buttons
    wxButton* newButton = new wxButton(this, NEW_SETUP, "NEW", wxDefaultPosition, wxDefaultSize, 0);
    wxButton* renameButton = new wxButton(this, RENAME_SETUP, "RENAME", wxDefaultPosition, wxDefaultSize, 0);
    wxButton* duplicateButton = new wxButton(this, DUPLICATE_SETUP, "COPY", wxDefaultPosition, wxDefaultSize, 0);
    wxButton* deleteButton = new wxButton(this, DELETE_SETUP, "DELETE", wxDefaultPosition, wxDefaultSize, 0);

    sizerRow1->Add(newButton, 0, wxALL | wxALIGN_LEFT, 5);
    sizerRow1->Add(renameButton, 0, wxALL | wxALIGN_LEFT, 5);
    sizerRow1->Add(duplicateButton, 0, wxALL | wxALIGN_LEFT, 5);
    sizerRow1->Add(deleteButton, 0, wxALL | wxALIGN_LEFT, 5);

    // add name select combobox
    wxArrayString comboValues;
    wxArrayString comboLabels;
    wxString value;
    wxString label;

    tcEditControl::labelWidth = 70;
    tcEditControl::controlWidth = 200;

    setupComboBox = new tcComboEditControl(this, wxSize(100, -1), value, label, comboValues, comboLabels);
    //setupComboBox->SetUpdateFromDatabaseReferences(referenceTables, referenceFields);
    setupComboBox->SetInfoOnly(true);
    setupComboBox->SetCommand(SETUP_SELECT);
    
    sizerRow1->Add(setupComboBox, 0, wxALL | wxALIGN_LEFT, 5);
    //

    // add text edit fields
    tcEditControl::labelWidth = 70;
    tcEditControl::controlWidth = 100;
    int textCtrlStyle = 0;
    int textCtrlSizerFlags = wxALL;
    int labelTextStyle = 0;
    int labelTextSizerFlags = wxALL;
    initialYear = new tcTextEditControl(this, wxSize(100, -1), "InitialYear", "InitialYear", 
        textCtrlStyle, textCtrlSizerFlags, labelTextStyle, labelTextSizerFlags);
    sizerRow1->Add(initialYear, 1, wxALL, 5);

    finalYear = new tcTextEditControl(this, wxSize(100, -1), "FinalYear", "FinalYear", 
        textCtrlStyle, textCtrlSizerFlags, labelTextStyle, labelTextSizerFlags);
    sizerRow1->Add(finalYear, 1, wxALL, 5);

    setupFields.push_back("SetupName");
    setupFields.push_back("InitialYear");
    setupFields.push_back("FinalYear");
    setupFields.push_back("AirComplement");
    setupFields.push_back("MagazineLoadout");
    setupFields.push_back("LauncherLoadout");


    // launcher table
    wxBoxSizer* launcherSizer = new wxBoxSizer(wxVERTICAL);


    launcherLabels.push_back("Item");
    launcherLabels.push_back("Quantity");
    launcherLabels.push_back("LauncherId");

    launcherFields.push_back("Item");
    launcherFields.push_back("Quantity");
    launcherFields.push_back("LauncherId");

    launcherLoadout = new wxGrid(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, gridStyle, "LauncherLoadout");
    launcherLoadout->CreateGrid(2, launcherLabels.size(), wxGrid::wxGridSelectCells);
    InitializeTableControl(launcherLoadout, launcherLabels);

    launcherTitle = new wxStaticText(this, wxID_ANY, "Launcher Loadout", wxDefaultPosition, wxDefaultSize);
    launcherTitle->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

    launcherSizer->Add(launcherTitle, 0, wxALL, border);
    launcherSizer->Add(launcherLoadout, 0, wxALL, border);
    sizerRow2->Add(launcherSizer, 0, wxALL | wxEXPAND, border);


    // air complement table
    wxBoxSizer* airComplementSizer = new wxBoxSizer(wxVERTICAL);

    airComplementLabels.push_back("AirClass");
    airComplementLabels.push_back("Quantity");
    airComplementLabels.push_back("Prefix");
    airComplementLabels.push_back("ReadyLevel");

    airComplementFields.push_back("AirClass");
    airComplementFields.push_back("Quantity");
    airComplementFields.push_back("Prefix");
    airComplementFields.push_back("ReadyLevel");

    airComplement = new wxGrid(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, gridStyle, "AirComplement");
    airComplement->CreateGrid(2, airComplementLabels.size(), wxGrid::wxGridSelectCells);
    InitializeTableControl(airComplement, airComplementLabels);

    airComplementTitle = new wxStaticText(this, wxID_ANY, "Air Complement", wxDefaultPosition, wxDefaultSize);
    airComplementTitle->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    
    airComplementSizer->Add(airComplementTitle, 0, wxALL, border);
    airComplementSizer->Add(airComplement, 0, wxALL, border);
    sizerRow2->Add(airComplementSizer, 0, wxALL | wxEXPAND, border);


    // magazine tables

    //magazineLabels.push_back("MagazineId");
    magazineLabels.push_back("Item");
    magazineLabels.push_back("Quantity");

    //magazineFields.push_back("MagazineId");
    magazineFields.push_back("Item");
    magazineFields.push_back("Quantity");

    wxASSERT(magazineLoadout.size() == 0);
    magazineLoadout.clear();
    for (size_t n=0; n<5; n++)
    {
        wxString s = wxString::Format("Mag %d", n);
        wxStaticText* magTitle = new wxStaticText(this, wxID_ANY, s, wxDefaultPosition, wxDefaultSize);
        magTitle->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    

        wxGrid* magn = new wxGrid(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, gridStyle, "MagazineLoadout");
        magn->CreateGrid(2, magazineLabels.size(), wxGrid::wxGridSelectCells);
        InitializeTableControl(magn, magazineLabels);
        
        wxBoxSizer* magSizer = new wxBoxSizer(wxVERTICAL);
        magSizer->Add(magTitle, 0, wxALL, border);
        magSizer->Add(magn, 0, wxALL, border);
        sizerRow2->Add(magSizer, 0, wxALL | wxEXPAND, border);

        magazineLoadout.push_back(magn);
        magazineTitle.push_back(magTitle);
    }

    sizerTop->Add(sizerRow1);
    sizerTop->Add(sizerRow2);

    sizerTop->SetSizeHints(this);

    this->SetSizer(sizerTop);

    InitializeReferenceTables();
    
}

void tcSetupPanel::InitializeReferenceTables()
{
    launcherEquipmentTables.push_back("ballistic");
    launcherEquipmentTables.push_back("ballistic_missile");
    launcherEquipmentTables.push_back("torpedo");
    launcherEquipmentTables.push_back("missile");
    launcherEquipmentTables.push_back("cm");
    launcherEquipmentTables.push_back("sonobuoy");
    launcherEquipmentTables.push_back("fueltank");

    storesEquipmentTables.push_back("ballistic");
    storesEquipmentTables.push_back("ballistic_missile");
    storesEquipmentTables.push_back("torpedo");
    storesEquipmentTables.push_back("missile");
    storesEquipmentTables.push_back("cm");
    storesEquipmentTables.push_back("sonobuoy");
    storesEquipmentTables.push_back("item");
    storesEquipmentTables.push_back("fueltank");

    aircraftTables.push_back("air");
    aircraftTables.push_back("simpleair");

}

void tcSetupPanel::InitializeTableControl(wxGrid* grid, const wxArrayString& columnLabels)
{
    for (size_t n=0; n<columnLabels.size(); n++)
    {
        grid->SetColLabelValue(n, columnLabels[n]);
    }

    grid->SetColMinimalWidth(0, 250);
    grid->SetColLabelAlignment(wxALIGN_LEFT, wxALIGN_CENTRE);
    //grid->AutoSizeColumns(true);
}

/**
* @return true if table has been edited at all to be different from database values
*/
bool tcSetupPanel::IsTableControlChanged(wxGrid* grid, const wxString& tableName, const wxString& setupDatabaseClass, 
                                         const wxArrayString& fields, const wxString& additionalConstraint)
{
    bool changed = false;

    static wxColour modifiedColor(0xEEFFEE);

    std::vector<wxArrayString> data;

    data = tcDatabaseManager::Get()->GetPlatformTableData(tableName, setupDatabaseClass, fields, additionalConstraint);

    int nGridRows = grid->GetNumberRows();
    int nGridCols = grid->GetNumberCols();

    for (int row=0; (row<int(data.size()))&&(row<nGridRows-1); row++)
    {
        for (int col=0; col<int(data[row].size()); col++)
        {
            if (grid->GetCellValue(row, col) != data[row][col])
            {
                grid->SetCellBackgroundColour(row, col, modifiedColor);
                changed = true;
            }
            else
            {
                grid->SetCellBackgroundColour(row, col, wxColour(0xFFFFFF));
            }
        }
    }

    if ((nGridRows > 0) && (grid->GetCellValue(nGridRows-1, 0).size() > 0))
    {
        changed = true;
        for (int col=0; col<nGridCols; col++)
        {
            grid->SetCellBackgroundColour(nGridRows-1, col, modifiedColor);
        }
    }

    wxASSERT(nGridRows >= 0);

    if (size_t(nGridRows) < (data.size() + 1))
    { // deleted some rows
        changed = true;
    }

    //CheckTableReferences(grid, GetReferenceTables(grid));

    return changed;
}


void tcSetupPanel::OnNewSetup(wxCommandEvent& event)
{
    wxString newSetupName = GetNewSetupName();
    
    std::vector<wxArrayString> newData;
    wxArrayString newEntry;
    newEntry.push_back(newSetupName);
    newEntry.push_back("1900");
    newEntry.push_back("2999");

    wxString newAirComplementName = newSetupName + wxString("-A");
    wxString newLauncherLoadoutName = newSetupName + wxString("-L");
    wxString newMagazineLoadoutName = newSetupName + wxString("-M");

    newEntry.push_back(newAirComplementName);
    newEntry.push_back(newMagazineLoadoutName);
    newEntry.push_back(newLauncherLoadoutName);

    newData.push_back(newEntry);

    wxString constraint = wxString::Format("SetupName=\"%s\"", newSetupName.c_str());

    tcDatabaseManager::Get()->UpdatePlatformTableData("platform_setup", 
        databaseClass, setupFields, newData, constraint);

    AddDefaultLauncherLoadout(newLauncherLoadoutName);

    // update view
    UpdateSetupData();
    currentSetup = newSetupName;
    setupComboBox->SetValue(currentSetup);
    UpdateAllTableControls();
}

void tcSetupPanel::OnRenameSetup(wxCommandEvent& event)
{
    wxString newSetupName;

    tcRenameSetupDialog* dialog = new tcRenameSetupDialog(this, false, "Rename Setup", databaseClass, currentSetup, newSetupName);

    int result = dialog->ShowModal();

    if (result == 1)
    {
        UpdateSetupData();
        currentSetup = newSetupName;
        setupComboBox->SetValue(currentSetup);
        UpdateAllTableControls();
    }
}

void tcSetupPanel::OnDuplicateSetup(wxCommandEvent& event)
{
    wxString newSetupName;

    tcRenameSetupDialog* dialog = new tcRenameSetupDialog(this, true, "Copy Setup", databaseClass, currentSetup, newSetupName);

    int result = dialog->ShowModal();

    if (result == 1)
    {
        UpdateSetupData();
        currentSetup = newSetupName;
        setupComboBox->SetValue(currentSetup);
        UpdateAllTableControls();
    }
}

void tcSetupPanel::OnDeleteSetup(wxCommandEvent& event)
{
    if (currentSetup.size() == 0) return;

    wxString message = wxString::Format("Delete %s?", currentSetup.c_str());

    wxMessageDialog dialog(this, message, "Confirm Delete", wxOK | wxCANCEL, wxDefaultPosition);
    if (dialog.ShowModal() == wxID_OK)
    {
        wxString constraint = wxString::Format("SetupName=\"%s\"", currentSetup.c_str());
        if (tcDatabaseManager::Get()->DeleteRecord("platform_setup", databaseClass, constraint))
        {
            tcDatabaseManager::Get()->DeleteRecord("launcher_loadout", launcherLoadoutName);
            tcDatabaseManager::Get()->DeleteRecord("magazine_loadout", magazineLoadoutName);
            tcDatabaseManager::Get()->DeleteRecord("air_complement",airComplementName);

            UpdateSetupData();
            currentSetup = (setupNames.size() > 0) ? setupNames[0] : "";
            setupComboBox->SetValue(currentSetup);

            UpdateAllTableControls();
        }
    }
}


void tcSetupPanel::OnGridCellChange(wxGridEvent& event)
{
    int row = event.GetRow();
    int col = event.GetCol();

    wxGrid* eventGrid = dynamic_cast<wxGrid*>(event.GetEventObject());

    if (eventGrid == launcherLoadout)
    {
        IsTableControlChanged(launcherLoadout, "launcher_loadout", launcherLoadoutName, launcherFields, "");
    }
    else if (eventGrid == airComplement)
    {
        //wxASSERT(false);
    }
    else // check mag grids
    {
        std::vector<int> magazineIds = GetMagazineIdList();

        size_t nMags = magazineIds.size();
        wxASSERT(nMags <= 5);

        for (size_t n=0; n<nMags; n++)
        {
            if (eventGrid == magazineLoadout[n])
            {
                wxString idConstraint = wxString::Format("MagazineId=%d", magazineIds[n]);
                IsTableControlChanged(magazineLoadout[n], "magazine_loadout", magazineLoadoutName,magazineFields, idConstraint);
            }
        }
    }
}

void tcSetupPanel::OnGridLabelRClick(wxGridEvent& event)
{
    wxGrid* tableCtrl = launcherLoadout;

    // only act for row selection, return otherwise
    wxArrayInt selectedRows = tableCtrl->GetSelectedRows();
    if (selectedRows.size() == 0) return;

    wxArrayString ops;
    ops.push_back("Delete rows");
    ops.push_back("Insert row above");

    int x = -1;
    int y = -1;
    int width = 50;
    int height = 50;
    bool center = true;
    wxWindow* parent = NULL;

    wxString choice = wxGetSingleChoice("Select operation", "Select operation", 
        ops, parent, x, y, center, width, height);

    if (choice == ops[0])
    {
        DeleteSelectedRows();
    }
    else if (choice == ops[1])
    {
        InsertRowAbove();
    }

}



void tcSetupPanel::OnGridLeftDClick(wxGridEvent& event)
{
    int row = event.GetRow();
    int col = event.GetCol();

    if (col != 0) return;

    wxGrid* eventGrid = dynamic_cast<wxGrid*>(event.GetEventObject());
    if (eventGrid == 0) return;

    wxString databaseClass = eventGrid->GetCellValue(row, col);
    wxString matchingTable;
    bool referenceFound = false; //tcDatabaseManager::Get()->PlatformExistsInTableList(referenceTables, databaseClass, matchingTable);
    if (!referenceFound) return;

    wxString item = databaseClass + wxString(",") + matchingTable;

	wxCommandEvent command(wxEVT_COMMAND_BUTTON_CLICKED, JUMP_TO);    
	command.SetEventObject(this);    
    command.SetString(item);
    command.SetExtraLong(-1);
	AddPendingEvent(command);

    wxPostEvent(eventFrame, command);
}

void tcSetupPanel::OnGridRightClick(wxGridEvent& event)
{
    int row = event.GetRow();
    int col = event.GetCol();

    if (col != 0) return;

    wxGrid* eventGrid = dynamic_cast<wxGrid*>(event.GetEventObject());
    wxString selection = eventGrid->GetCellValue(row, col);

    // set cell color to indicate it's being edited
    wxColour startColor = eventGrid->GetCellBackgroundColour(row, col);
    eventGrid->SetCellBackgroundColour(wxColour(0xFFE0D0), row, col);
    eventGrid->Refresh();

    wxArrayString referenceTables;
    if (eventGrid == launcherLoadout)
    {
        referenceTables = launcherEquipmentTables;
    }
    else if (eventGrid == airComplement)
    {
        referenceTables = aircraftTables;
    }
    else
    {
        bool found = false;
        for (size_t n=0; (n<magazineLoadout.size())&&(!found); n++)
        {
            if (eventGrid == magazineLoadout[n])
            {
                referenceTables = storesEquipmentTables;
                found = true;
            }
        }
        if (!found)
        {
            wxASSERT(false);
            return;
        }
    }



    tcSelectFromTablesDialog* dialog = new tcSelectFromTablesDialog(this, "Select Record", referenceTables, selection);

    tcDatabaseManager* databaseManager = tcDatabaseManager::Get();

    wxString launcherClass;
    if (eventGrid == launcherLoadout)
    {
        // find launcher class for this row
        wxString query = wxString::Format("select LauncherClass from platform_launcher where DatabaseClass=\"%s\" and LauncherId=%s",
            databaseClass.c_str(), eventGrid->GetCellValue(row, 2).c_str());
        wxArrayString launcherClassArray = databaseManager->ExecuteQuery(query);

        if ((launcherClassArray.size() == 1) && (launcherClassArray[0].size() > 0))
        {
            launcherClass = launcherClassArray[0];
            wxString constraint;
            constraint.Printf("intersect select ChildClass from launcher_configuration where DatabaseClass=\"%s\"", launcherClass.c_str());
            dialog->SetConstraint(constraint);
            dialog->UpdateListWithTable(referenceTables[0]);
        }
    }

    int result = dialog->ShowModal();
    if (result == wxID_OK)
    {
        eventGrid->SetCellValue(row, col, selection);

        if ((eventGrid == launcherLoadout) && (launcherClass.size() > 0))
        {
            // update quantity automatically
            wxString query = wxString::Format("select ChildCapacity from launcher_configuration where DatabaseClass=\"%s\" and ChildClass=\"%s\"",
                launcherClass.c_str(), selection.c_str());
            wxArrayString quantityResult = databaseManager->ExecuteQuery(query);
            wxString quantityString = (quantityResult.size() > 0) ? quantityResult[0] : "";
            long nQuantity = 0;
            if (quantityString.ToLong(&nQuantity))
            {
                eventGrid->SetCellValue(row, 1, quantityString);
            }
        }
    }

    // reset color
    eventGrid->SetCellBackgroundColour(startColor, row, col);
    eventGrid->Refresh();
}

void tcSetupPanel::OnTextUpdated(wxCommandEvent& event)
{
    int commandId = event.GetId();

    if (commandId == SETUP_SELECT)
    {
        wxString newSetup = event.GetString();

        currentSetup = newSetup;

        setupComboBox->SetValue(currentSetup);

        UpdateAllTableControls();
    }
}

void tcSetupPanel::Save()
{
    // launcher loadout grid
    if ((launcherLoadoutName.size() > 0) && IsTableControlChanged(launcherLoadout, "launcher_loadout", launcherLoadoutName, launcherFields, ""))
    {
        SavePlatformTable(launcherLoadout, "launcher_loadout", launcherLoadoutName, launcherFields, "");
    }

    // air complement grid
    if ((airComplementName.size() > 0) && IsTableControlChanged(airComplement, "air_complement", airComplementName, airComplementFields, ""))
    {
        SavePlatformTable(airComplement, "air_complement", airComplementName, airComplementFields, "");
    }

    // magazine grids
    if (magazineLoadoutName.size() > 0)
    {
        std::vector<int> magazineIds = GetMagazineIdList();

        size_t nMags = magazineIds.size();
        wxASSERT(nMags <= 5);

        for (size_t n=0; n<nMags; n++)
        {
            SavePlatformTableMagazine(magazineLoadout[n], "magazine_loadout", magazineLoadoutName, magazineFields, magazineIds[n]);
        }
    }

    SaveSetupYears();


    tcBasePanel::Save();

    wxWindow::Update();
}

void tcSetupPanel::SavePlatformTable(wxGrid* grid, const wxString& tableName, const wxString& setupDatabaseClass, 
                                         const wxArrayString& fields, const wxString& additionalConstraint)
{

    if (!IsTableControlChanged(grid, tableName, setupDatabaseClass, fields, additionalConstraint))
    {
        return;
    }

    std::vector<wxArrayString> tableData;

    int nRows = grid->GetNumberRows();
    int nCols = grid->GetNumberCols();
    for (int row=0; row<nRows; row++)
    {
        bool isRowEmpty = true;
        for (int col=0; (col<nCols)&&(isRowEmpty); col++)
        {
            if (grid->GetCellValue(row, col).size() > 0)
            {
                isRowEmpty = false;
            }
        }

        if (!isRowEmpty)
        {
            wxArrayString rowData;
            for (int col=0; col<nCols; col++)
            {
                rowData.push_back(grid->GetCellValue(row, col));
            }
            tableData.push_back(rowData);
        }
    }

    tcDatabaseManager::Get()->UpdatePlatformTableData(tableName, setupDatabaseClass, fields, tableData, additionalConstraint);
}

/**
* Add in additional constraint, and add in MagazineId value to saved fields
*/
void tcSetupPanel::SavePlatformTableMagazine(wxGrid* grid, const wxString& tableName, const wxString& setupDatabaseClass, 
                                         const wxArrayString& fields, int magazineId)
{
    wxString additionalConstraint = wxString::Format("MagazineId=%d", magazineId);
    wxArrayString fieldsWithId = fields;
    fieldsWithId.push_back("MagazineId");
    wxString magazineIdString = wxString::Format("%d", magazineId);

    if (!IsTableControlChanged(grid, tableName, setupDatabaseClass, fields, additionalConstraint))
    {
        return;
    }

    std::vector<wxArrayString> tableData;

    int nRows = grid->GetNumberRows();
    int nCols = grid->GetNumberCols();
    for (int row=0; row<nRows; row++)
    {
        if (grid->GetCellValue(row, 0).size() > 0)
        {
            wxArrayString rowData;
            for (int col=0; col<nCols; col++)
            {
                rowData.push_back(grid->GetCellValue(row, col));
            }
            rowData.push_back(magazineIdString);
            tableData.push_back(rowData);
        }
    }

    tcDatabaseManager::Get()->UpdatePlatformTableData(tableName, setupDatabaseClass, fieldsWithId, tableData, additionalConstraint);

}

void tcSetupPanel::SaveSetupYears()
{
    if (!initialYear->IsEdited() && !finalYear->IsEdited()) return;

    wxString initialYearString = initialYear->GetEditValue();
    wxString finalYearString = finalYear->GetEditValue();

    double initialYearDouble = 0;
    double finalYearDouble = 0;

    bool initialValid = initialYearString.ToDouble(&initialYearDouble);
    bool finalValid = finalYearString.ToDouble(&finalYearDouble);

    if (!initialValid) initialYearString = initialYear->GetInitialValue();
    if (!finalValid) finalYearString = finalYear->GetInitialValue();

    wxString constraint = wxString::Format("SetupName=\"%s\"", currentSetup.c_str());

    tcDatabaseManager* databaseManager = tcDatabaseManager::Get();
    std::vector<wxArrayString> data = databaseManager->GetPlatformTableData("platform_setup", databaseClass, setupFields, constraint);

    if (data.size() > 0)
    {
        data[0][1] = wxString::Format("%.4f", initialYearDouble);
        data[0][2] = wxString::Format("%.4f", finalYearDouble);
        databaseManager->UpdatePlatformTableData("platform_setup", databaseClass, setupFields, data, constraint);
    }

}


void tcSetupPanel::SetDatabaseClass(const wxString& s)
{
    wxString previousDatabaseClass = databaseClass;

    tcBasePanel::SetDatabaseClass(s);

    UpdateSetupData();

    if (databaseClass != previousDatabaseClass)
    {
        currentSetup = (setupNames.size() > 0) ? setupNames[0] : "";
    }

    setupComboBox->SetValue(currentSetup);

    UpdateAllTableControls();
}


void tcSetupPanel::UpdateAllTableControls()
{    
    int idx = GetCurrentSetupIndex();

    if (idx >= 0)
    {
        launcherLoadoutName = setupData[idx][5];
        magazineLoadoutName = setupData[idx][4];
        airComplementName = setupData[idx][3];
    }
    else
    {
        launcherLoadoutName = "NONE-DEFINED";
        magazineLoadoutName = "NONE-DEFINED";
        airComplementName = "NONE-DEFINED";
    }

    Freeze();

    UpdateSetupYears(currentSetup);
    UpdateLauncherControl(launcherLoadoutName);
    UpdateMagazineControls(magazineLoadoutName);
    UpdateAirComplementControl(airComplementName);

    Layout();

    Thaw();
}

/**
* If grid doesn't have an empty row at the end, then add one
*/
void tcSetupPanel::UpdateGridRows(wxGrid* grid)
{
    if (grid == 0)
    {
        wxASSERT(false);
        return;
    }

    int nGridRows = grid->GetNumberRows();
    int nGridCols = grid->GetNumberCols();

    if (nGridRows <= 1)
    {
        grid->InsertRows(nGridRows, 1);
        grid->Update();
        return;
    }

    for (int col=0; col<nGridCols; col++)
    {
        wxString s = grid->GetCellValue(nGridRows-1, col);
        if (s.size() > 0)
        {
            grid->InsertRows(nGridRows, 1);
            grid->Update();
            return;
        }
    }
}

void tcSetupPanel::UpdateAirComplementControl(const wxString& setupName)
{
    wxGrid* grid = airComplement;

    int nRows = grid->GetNumberRows();
    if (nRows > 0) grid->DeleteRows(0, nRows);


    std::vector<wxArrayString> data = tcDatabaseManager::Get()->GetPlatformTableData("air_complement", setupName, airComplementFields);
    for (size_t row=0; row<data.size(); row++)
    {
        grid->AppendRows(1);

        for (size_t col=0; col<data[row].size(); col++)
        {
            grid->SetCellValue(int(row), int(col), data[row][col]);
        }
    }

    CheckTableReferences(grid, 0, aircraftTables);

    grid->AppendRows(1); // add extra row for new launcher
    grid->AutoSize();

    wxSize size = grid->GetVirtualSize();
    size.DecTo(this->GetClientSize());
    grid->SetSize(size);

    grid->Show((currentSetup.size() > 0) && HasAirComplement()); // hide grid if no valid currentSetup or air complement
    airComplementTitle->Show((currentSetup.size() > 0) && HasAirComplement());
   // grid->FitInside();
    //grid->AutoSizeRows(false);
    //grid->Layout();
    //grid->Refresh();
    //this->Refresh();
}

void tcSetupPanel::UpdateLauncherControl(const wxString& setupName)
{
    int nRows = launcherLoadout->GetNumberRows();
    if (nRows > 0) launcherLoadout->DeleteRows(0, nRows);


    std::vector<wxArrayString> data = tcDatabaseManager::Get()->GetPlatformTableData("launcher_loadout", setupName, launcherFields);
    for (size_t row=0; row<data.size(); row++)
    {
        launcherLoadout->AppendRows(1);

        for (size_t col=0; col<data[row].size(); col++)
        {
            launcherLoadout->SetCellValue(int(row), int(col), data[row][col]);
        }
    }

    CheckTableReferences(launcherLoadout, 0, launcherEquipmentTables);

    launcherLoadout->AppendRows(1); // add extra row for new launcher
    launcherLoadout->AutoSize();

    wxSize size = launcherLoadout->GetVirtualSize();
    size.DecTo(this->GetClientSize());
    launcherLoadout->SetSize(size);

	wxString titleText = "Launcher Loadout";
	wxString launcherSummary = GetLauncherSummary(data);
	if (launcherSummary.size() > 0)
	{
		titleText += "\n";
		titleText += launcherSummary;
	}
	launcherTitle->SetLabel(titleText);


    launcherLoadout->Show(currentSetup.size() > 0); // hide grid if no valid currentSetup
    launcherTitle->Show(currentSetup.size() > 0);

	
   // grid->FitInside();
    //grid->AutoSizeRows(false);
    //grid->Layout();
    //grid->Refresh();
    //this->Refresh();
}

void tcSetupPanel::UpdateMagazineControls(const wxString& setupName)
{
    std::vector<int> magazineIds = GetMagazineIdList();
    wxArrayString magazineNames = GetMagazineNameList();
    wxASSERT(magazineIds.size() == magazineNames.size());

    size_t nMags = magazineIds.size();
    wxASSERT(nMags <= 5);

    for (size_t n=0; n<nMags; n++)
    {
        wxGrid* grid = magazineLoadout[n];
        grid->Show(currentSetup.size() > 0); // hide grid if no valid currentSetup
        
        int nRows = grid->GetNumberRows();
        if (nRows > 0) grid->DeleteRows(0, nRows);

        wxString idConstraint = wxString::Format("MagazineId=%d", magazineIds[n]);

        std::vector<wxArrayString> data = 
            tcDatabaseManager::Get()->GetPlatformTableData("magazine_loadout", setupName, magazineFields, idConstraint);

        for (size_t row=0; row<data.size(); row++)
        {
            grid->AppendRows(1);

            for (size_t col=0; col<data[row].size(); col++)
            {
                grid->SetCellValue(int(row), int(col), data[row][col]);
            }
        }    

        CheckTableReferences(grid, 0, storesEquipmentTables);

        if (n < magazineNames.size())
        {
			bool isOkay = true;
            wxString title = magazineNames[n];
            title += "\n";
            title += GetMagazineSummary(magazineNames[n], data, isOkay);

            magazineTitle[n]->SetLabel(title);
            magazineTitle[n]->Show(currentSetup.size() > 0);
			if (isOkay)
			{
				magazineTitle[n]->SetForegroundColour(wxColour(unsigned long(0x000000))); // BBGGRR
			}
			else
			{
				magazineTitle[n]->SetForegroundColour(wxColour(unsigned long(0x000080))); // BBGGRR
			}
        }



        grid->AppendRows(1); // add extra row for new entry
        grid->AutoSize();



        wxSize size = grid->GetVirtualSize();
        size.DecTo(this->GetClientSize());
        grid->SetSize(size); 
    }
    
    // clear unused mag grids
    for (size_t n=nMags; n<5; n++)
    {
        wxGrid* grid = magazineLoadout[n];
        int nRows = grid->GetNumberRows();
        if (nRows > 0) grid->DeleteRows(0, nRows);

        grid->Show(false);
        magazineTitle[n]->Show(false);
    }

}

void tcSetupPanel::UpdateSetupYears(const wxString& setupName)
{
    initialYear->SetValue("");
    finalYear->SetValue("");

    wxArrayString yearFields;
    yearFields.push_back("InitialYear");
    yearFields.push_back("FinalYear");

    wxString constraint = wxString::Format("SetupName=\"%s\"", setupName.c_str());
    std::vector<wxArrayString> data = tcDatabaseManager::Get()->GetPlatformTableData("platform_setup", databaseClass, yearFields, constraint);
    if (data.size() > 0)
    {
        initialYear->SetValue(data[0][0]);
        finalYear->SetValue(data[0][1]);
    }
}



tcSetupPanel::tcSetupPanel(wxWindow* parent, const wxString& table_, const wxString& panelName) 
: tcBasePanel(parent, table_, panelName),
  errorFont(*wxNORMAL_FONT)
{
    InitializePanel();

    errorFont.SetWeight(wxFONTWEIGHT_BOLD);

    SetVirtualSizeHints(2800, -1, -1, -1);
    FitInside();
    SetScrollRate(10, 10);
}

tcSetupPanel::~tcSetupPanel()
{

}