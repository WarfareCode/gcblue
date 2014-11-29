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
#include "GridPanel.h"
#include "TextEditControl.h"
#include "ComboEditControl.h"
#include "DatabaseManager.h"
#include "SelectFromTablesDialog.h"
#include "DatePickerDialog.h"

#include "wx/grid.h"
#include "wx/sizer.h"
#include "wx/textfile.h"
#include "wx/xml/xml.h"
#include "wx/msgdlg.h"
#include "wx/choicdlg.h"
#include "wx/frame.h"

BEGIN_EVENT_TABLE(tcGridPanel, tcBasePanel)
    EVT_GRID_CELL_CHANGE(tcGridPanel::OnGridCellChange)
    EVT_GRID_CELL_LEFT_DCLICK(tcGridPanel::OnGridLeftDClick)
    EVT_GRID_CELL_RIGHT_CLICK(tcGridPanel::OnGridRightClick)
    EVT_GRID_CMD_LABEL_RIGHT_CLICK(wxID_ANY, tcGridPanel::OnGridLabelRClick)
END_EVENT_TABLE()

DECLARE_EVENT_TYPE(JUMP_TO, -1)
DEFINE_EVENT_TYPE(JUMP_TO)



wxFrame* tcGridPanel::eventFrame = 0;


int DescendingSort(int* first, int* second)
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

void tcGridPanel::AddReferenceCombo(wxXmlNode* node, wxBoxSizer* sizer)
{
    if (referenceComboBox != 0) 
    {
        wxASSERT(false);
        return;
    }

    wxString value = node->GetPropVal("value", "Error");
    wxString label = node->GetPropVal("label", "Error");

    wxArrayString comboValues;
    wxArrayString comboLabels;
    

    wxXmlNode* child = node->GetChildren();

    wxArrayString referenceTables;
    wxArrayString referenceFields;

    while (child != 0)
    {
        if (child->GetName() == "update_reference") 
        {
            wxString refTable = child->GetPropVal("table", "");
            wxString refField = child->GetPropVal("field", "");
            if ((refTable.size() > 0) && (refField.size() > 0))
            {
                referenceTables.push_back(refTable);
                referenceFields.push_back(refField);
            }
        }

        child = child->GetNext();
    }
    if (referenceTables.size() == 0) return;

    tcEditControl::labelWidth = 70;
    tcEditControl::controlWidth = 300;

    referenceComboBox = new tcComboEditControl(this, wxSize(100, -1), value, label, comboValues, comboLabels);
    referenceComboBox->SetUpdateFromDatabaseReferences(referenceTables, referenceFields);
    referenceComboBox->SetInfoOnly(true);

    int border = 15;
    sizer->Add(referenceComboBox, 0, wxALL, border);

}

void tcGridPanel::CheckTableReferences(wxGrid* grid, const wxArrayString& referenceTables_)
{
    wxASSERT(grid != 0);

    int nRows = grid->GetNumberRows();
    int nCols = grid->GetNumberCols();

    tcDatabaseManager* databaseManager = tcDatabaseManager::Get();

    for (int row=0; row<nRows; row++)
    {
        wxString matchingTable;
        wxString databaseClass = grid->GetCellValue(row, 0);
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

void tcGridPanel::DeleteSelectedRows()
{
    wxArrayInt selectedRows = tableCtrl->GetSelectedRows();
    if (selectedRows.size() == 0) return;

    selectedRows.Sort(DescendingSort);

    for (size_t n=0; n<selectedRows.size(); n++)
    {
        tableCtrl->DeleteRows(selectedRows[n]);
    }

}

void tcGridPanel::InsertRowAbove()
{
    wxArrayInt selectedRows = tableCtrl->GetSelectedRows();
    if (selectedRows.size() == 0) return;

    tableCtrl->InsertRows(selectedRows[0]);
}


const wxArrayString& tcGridPanel::GetReferenceTables(wxGrid* grid) const
{
    return referenceTables;
}


void tcGridPanel::LoadFromXml(const wxString& xmlPath)
{
    wxXmlDocument doc;
    if (!doc.Load(xmlPath))
    {
        wxString msg = wxString::Format("tcGridPanel::LoadFromXml - file not found (%s)", xmlPath.c_str());
        wxMessageBox(msg, "Error");
        return;
    }

    wxXmlNode* root = doc.GetRoot();
    if (root->GetName() != "grid") return;

    // create sizer
    wxString propval = root->GetPropVal("orientation", "vertical");
    wxBoxSizer* sizerTop;
    if (propval.IsSameAs("horizontal", false))
    {
        sizerTop = new wxBoxSizer(wxHORIZONTAL);
    }
    else
    {
        sizerTop = new wxBoxSizer(wxVERTICAL);
    }


    // update table if specified
    table = root->GetPropVal("table", table);

    // load label/value and create wxGrid
    wxString labelValueFile = root->GetPropVal("label_value_file", "");
    LoadLabelValueData(labelValueFile, tableLabels, tableFields);

    long gridStyle = wxWANTS_CHARS; //|wxFULL_REPAINT_ON_RESIZE|wxHSCROLL|wxVSCROLL;

    tableCtrl = new wxGrid(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, gridStyle, "TableControl");
    tableCtrl->CreateGrid(2, tableLabels.size(), wxGrid::wxGridSelectCells);
    InitializeTableControl(tableCtrl, tableLabels);

    // load reference table data (refs for first column entries)
    referenceTables.clear();

    wxXmlNode* child = root->GetChildren();
    while (child != 0)
    {
        if (child->GetName() == "reference") 
        {
            wxString tableName = child->GetPropVal("table_name", "");
            if (tableName.size() > 0)
            {
                referenceTables.push_back(tableName);
            }
        }
        if (child->GetName() == "combobox") 
        {
            AddReferenceCombo(child, sizerTop);
        }
		if (child->GetName() == "datefield")
		{
			wxString columnString = child->GetPropVal("column", "");
			long column = 999;
			if (columnString.ToLong(&column))
			{
				isDateField[column] = true;
			}
		}

		
        child = child->GetNext();
    }    
    
    int border = 15;
    sizerTop->Add(tableCtrl, 0, wxALL | wxEXPAND, border);

    sizerTop->SetSizeHints(this);
    this->SetSizer(sizerTop);

    
}

void tcGridPanel::InitializeTableControl(wxGrid* grid, const wxArrayString& columnLabels)
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
bool tcGridPanel::IsTableControlChanged(wxGrid* grid, const wxString& tableName, const wxArrayString& fields)
{
    bool changed = false;

    static wxColour modifiedColor(0xEEFFEE);

    std::vector<wxArrayString> data = tcDatabaseManager::Get()->GetPlatformTableData(tableName, databaseClass, fields);

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

    if (grid->GetCellValue(nGridRows-1, 0).size() > 0)
    {
        changed = true;
        for (int col=0; col<nGridCols; col++)
        {
            grid->SetCellBackgroundColour(nGridRows-1, col, modifiedColor);
        }
    }

    if (size_t(nGridRows) < (data.size() + 1))
    { // deleted some rows
        changed = true;
    }

    CheckTableReferences(grid, GetReferenceTables(grid));

    return changed;
}



void tcGridPanel::OnGridCellChange(wxGridEvent& event)
{
    int row = event.GetRow();
    int col = event.GetCol();

    wxGrid* eventGrid = dynamic_cast<wxGrid*>(event.GetEventObject());
    if (eventGrid == tableCtrl)
    {
        IsTableControlChanged(tableCtrl, table, tableFields);
    }
    else
    {
        wxASSERT(false);
    }
}

void tcGridPanel::OnGridLabelRClick(wxGridEvent& event)
{
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



void tcGridPanel::OnGridLeftDClick(wxGridEvent& event)
{
    int row = event.GetRow();
    int col = event.GetCol();

    if (col != 0) return;

    wxGrid* eventGrid = dynamic_cast<wxGrid*>(event.GetEventObject());
    if (eventGrid == 0) return;

    wxString databaseClass = eventGrid->GetCellValue(row, col);
    wxString matchingTable;
    bool referenceFound = tcDatabaseManager::Get()->PlatformExistsInTableList(referenceTables, databaseClass, matchingTable);
    if (!referenceFound) return;

	if (IsTableControlChanged(tableCtrl, table, tableFields))
    {
		wxMessageDialog dialog(this, "Save changes to table?", "Save?", wxYES | wxNO | wxCANCEL, wxDefaultPosition);
        int response = dialog.ShowModal();
        if (response == wxID_YES)
        {
			SavePlatformTable(tableCtrl, table, tableFields);
		}
		else if (response == wxID_CANCEL)
		{
			return;
		}
    }

    wxString item = databaseClass + wxString(",") + matchingTable;

	wxCommandEvent command(wxEVT_COMMAND_BUTTON_CLICKED, JUMP_TO);    
	command.SetEventObject(this);    
    command.SetString(item);
    command.SetExtraLong(-1);
	AddPendingEvent(command);

    wxPostEvent(eventFrame, command);
}

void tcGridPanel::OnGridRightClick(wxGridEvent& event)
{
    int row = event.GetRow();
    int col = event.GetCol();

	bool dateFieldType = false;
    if (col != 0)
	{
		// check if this is a date field, open calendar control if so
		std::map<long, bool>::iterator iter = isDateField.find(long(col));
		if (iter != isDateField.end())
		{
			dateFieldType = true;
		}
		else
		{
			return;
		}
	}

    wxGrid* eventGrid = dynamic_cast<wxGrid*>(event.GetEventObject());
    wxString selection = eventGrid->GetCellValue(row, col);

    // set cell color to indicate it's being edited
    wxColour startColor = eventGrid->GetCellBackgroundColour(row, col);
    eventGrid->SetCellBackgroundColour(wxColour(0xFFE0D0), row, col);
    eventGrid->Refresh();

    if ((eventGrid != tableCtrl) || 
		((referenceTables.size() == 0) && (!dateFieldType))) return;

	int result = 0;
	if (!dateFieldType)
	{
		tcSelectFromTablesDialog* dialog = new tcSelectFromTablesDialog(this, "Select Record", referenceTables, selection);
		result = dialog->ShowModal();
	}
	else
	{
		if (selection.size() == 0)
		{
			selection = "1960";
		}

		double yearVal = 0;
		if (selection.ToDouble(&yearVal))
		{
			tcDatePickerDialog* dialog = new tcDatePickerDialog(this, "Select Record", yearVal);
			result = dialog->ShowModal();
			if (result == wxID_OK) selection.Printf("%.3f", yearVal);
		}
		else
		{
			wxASSERT(false); // invalid date type
		}
	}

    if (result == wxID_OK)
    {
        eventGrid->SetCellValue(row, col, selection);
    }

    // reset color
    eventGrid->SetCellBackgroundColour(startColor, row, col);
    eventGrid->Refresh();
}

void tcGridPanel::Save()
{
    if (IsTableControlChanged(tableCtrl, table, tableFields))
    {
        SavePlatformTable(tableCtrl, table, tableFields);
    }

    tcBasePanel::Save();

    wxWindow::Update();
}

void tcGridPanel::SavePlatformTable(wxGrid* grid, const wxString& tableName, const wxArrayString& fields)
{
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
            tableData.push_back(rowData);
        }
    }

    tcDatabaseManager::Get()->UpdatePlatformTableData(tableName, databaseClass, fields, tableData);
}

void tcGridPanel::SetDatabaseClass(const wxString& s)
{
    tcBasePanel::SetDatabaseClass(s);

    if (referenceComboBox != 0)
    {
        referenceComboBox->SetDatabaseClass(s);
        referenceComboBox->UpdateControl();
    }

    UpdateAllTableControls();
}


void tcGridPanel::UpdateAllTableControls()
{
    Freeze();

    UpdateTableControl(tableCtrl, table, tableFields);

    Thaw();
}

void tcGridPanel::UpdateTableControl(wxGrid* grid, const wxString& tableName, const wxArrayString& fields)
{
    int nRows = grid->GetNumberRows();
    if (nRows > 0) grid->DeleteRows(0, nRows);
    std::vector<wxArrayString> data = tcDatabaseManager::Get()->GetPlatformTableData(tableName, databaseClass, fields);
    for (size_t row=0; row<data.size(); row++)
    {
        grid->AppendRows(1);

        for (size_t col=0; col<data[row].size(); col++)
        {
            grid->SetCellValue(int(row), int(col), data[row][col]);
        }
    }

    CheckTableReferences(grid, GetReferenceTables(grid));

    grid->AppendRows(1); // add extra row for new launcher
    grid->AutoSize();

    wxSize size = grid->GetVirtualSize();
    size.DecTo(this->GetClientSize());
    grid->SetSize(size); 

   // grid->FitInside();
    //grid->AutoSizeRows(false);
    //grid->Layout();
    //grid->Refresh();
    //this->Refresh();
}


tcGridPanel::tcGridPanel(wxWindow* parent, const wxString& table_, const wxString& panelName, const wxString& xmlPath) 
: tcBasePanel(parent, table_, panelName),
  errorFont(*wxNORMAL_FONT),
  tableCtrl(0),
  referenceComboBox(0)
{
    LoadFromXml(xmlPath);

    errorFont.SetWeight(wxFONTWEIGHT_BOLD);
}

tcGridPanel::~tcGridPanel()
{

}