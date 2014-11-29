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
#include "ToolPanel.h"

#include "wx/sizer.h"
#include "wx/wx.h"
#include "wx/dir.h"
#include "wx/file.h"
#include "wx/stattext.h"
#include "wx/xml/xml.h"
#include "wx/choicdlg.h"
#include "DatabaseExport.h"
#include "DatabaseManager.h"


BEGIN_EVENT_TABLE(tcToolPanel, wxPanel)
    EVT_DIRPICKER_CHANGED(-1, tcToolPanel::OnCSVDirSelect)
    EVT_BUTTON(ID_ExportAllDatabase, tcToolPanel::OnExport)
    EVT_BUTTON(ID_ImportAllDatabase, tcToolPanel::OnImport)
    EVT_BUTTON(ID_ExportTableDatabase, tcToolPanel::OnExportTable)
    EVT_BUTTON(ID_ImportTableDatabase, tcToolPanel::OnImportTable)
    EVT_BUTTON(ID_CreateIndices, tcToolPanel::OnCreateIndices)
END_EVENT_TABLE()


const wxString& tcToolPanel::GetLastCSVPath() const
{
    return lastCSVPath;
}

void tcToolPanel::OnCreateIndices(wxCommandEvent& event)
{
    if (!tcDatabaseManager::Get()->IsOpen())
    {
        wxMessageBox("Database is not open", "Create Indices Failed");
        return;
    }


    tcDatabaseManager* databaseManager = tcDatabaseManager::Get();
    if (databaseManager->CreateIndices())
    {
        textDisplay->AppendText("Created fast lookup indices");
    }
    else
    {
        textDisplay->AppendText("Error while creating fast lookup indices");
    }

}

void tcToolPanel::OnExport(wxCommandEvent& event)
{
    if (!tcDatabaseManager::Get()->IsOpen())
    {
        wxMessageBox("Database is not open", "Export Failed");
        return;
    }

    wxTextCtrl* dirTextCtrl = dirPicker->GetTextCtrl();

    wxString csvDir = dirPicker->GetPath();


    if (dirTextCtrl->IsModified())
    {
        csvDir = dirTextCtrl->GetValue();
    }

    if (wxDir::Exists(csvDir))
    {
        wxDir dir(csvDir);
        if (dir.HasFiles("*.csv"))
        {
            wxString msg(wxString::Format("Overwrite CSV files in output dir? (%s)", csvDir.c_str()));
            wxMessageDialog* confirm = new wxMessageDialog(NULL, msg, "Confirm Overwrite", wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION);
            if (confirm->ShowModal() != wxID_YES)
            {
                textDisplay->AppendText("Export cancelled\n");
                return;
            }
        }             
    }

    sqlite3_connection& sqlConnection = tcDatabaseManager::Get()->GetConnection();

    tcDatabaseTranslator translator;
    bool success = translator.ExportDatabaseToCSV(sqlConnection, csvDir);

    wxString msg;
    if (success)
    {
        msg.Printf("Exported database to  \"%s\"\n", csvDir.c_str());
    }
    else
    {
        msg.Printf("ERROR exporting database  to  \"%s\"\n", csvDir.c_str());
    }
    textDisplay->AppendText(msg);

}


void tcToolPanel::OnExportTable(wxCommandEvent& event)
{
    if (!tcDatabaseManager::Get()->IsOpen())
    {
        wxMessageBox("Database is not open", "Export Failed");
        return;
    }

    sqlite3_connection& sqlConnection = tcDatabaseManager::Get()->GetConnection();

    tcDatabaseTranslator translator;

	wxArrayString tableList = translator.GetTableList(sqlConnection);

	wxSingleChoiceDialog dialog(this, "Choose table", "Select", tableList, (char**)NULL, wxCHOICEDLG_STYLE, wxDefaultPosition);
	int result = dialog.ShowModal();
	wxString tableName = "None";

	if (result == wxID_OK)
	{
		tableName = dialog.GetStringSelection();
	}
	else
	{
		textDisplay->AppendText("Export cancelled\n");
		return;
	}

    wxTextCtrl* dirTextCtrl = dirPicker->GetTextCtrl();
    wxString csvDir = dirPicker->GetPath();


    if (dirTextCtrl->IsModified())
    {
        csvDir = dirTextCtrl->GetValue();
    }

    if (wxDir::Exists(csvDir))
    {
        wxDir dir(csvDir);
		wxString exportFileName = tableName + ".csv";
		if (dir.HasFiles(exportFileName))
        {
            wxString msg(wxString::Format("Overwrite CSV file in output dir? (%s)", csvDir.c_str()));
            wxMessageDialog* confirm = new wxMessageDialog(NULL, msg, "Confirm Overwrite", wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION);
            if (confirm->ShowModal() != wxID_YES)
            {
                textDisplay->AppendText("Export cancelled\n");
                return;
            }
        }             
    }

	bool success = translator.ExportTableToCSV(sqlConnection, tableName, csvDir);

    wxString msg;
    if (success)
    {
		msg.Printf("Exported %s to  \"%s\"\n", tableName.c_str(), csvDir.c_str());
    }
    else
    {
        msg.Printf("ERROR exporting %s  to  \"%s\"\n", tableName.c_str(), csvDir.c_str());
    }
    textDisplay->AppendText(msg);

}

void tcToolPanel::OnImport(wxCommandEvent& event)
{
    if (!tcDatabaseManager::Get()->IsOpen())
    {
        wxMessageBox("Database is not open", "Import Failed");
        return;
    }

    wxTextCtrl* dirTextCtrl = dirPicker->GetTextCtrl();

    wxString csvDir = dirPicker->GetPath();

    if (dirTextCtrl->IsModified())
    {
        csvDir = dirTextCtrl->GetValue();
    }

    bool inputValid = false;

    if (wxDir::Exists(csvDir))
    {
        wxDir dir(csvDir);
        if (dir.HasFiles("*.csv"))
        {
            inputValid = true;
        }
    }

    if (!inputValid)
    {
        wxString msg(wxString::Format("Input directory has no CSV files (%s)", csvDir.c_str()));
        wxMessageBox(msg, "Error", wxICON_ERROR);
        //SetStatusText(msg);
        return;
    }             

    textDisplay->Clear();

    sqlite3_connection& sqlConnection = tcDatabaseManager::Get()->GetConnection();

    tcDatabaseTranslator translator;
    bool success = translator.ImportDatabaseFromCSV(sqlConnection, csvDir);

    wxString msg;
    if (success)
    {
        msg.Printf("Imported CSV data from  \"%s\"  to database", csvDir.c_str());
        if (translator.statusRows.size() > 0)
        {
            textDisplay->AppendText("IMPORT LOG:\n\n");
            for (size_t n=0; n<translator.statusRows.size(); n++)
            {
                textDisplay->AppendText(translator.statusRows[n]);
            }
        }
        
    }
    else
    {
        msg.Printf("ERROR importing CSV data from \"%s\"  to database", csvDir.c_str());
    }
    //SetStatusText(msg);

}


void tcToolPanel::OnImportTable(wxCommandEvent& event)
{
    if (!tcDatabaseManager::Get()->IsOpen())
    {
        wxMessageBox("Database is not open", "Import Failed");
        return;
    }

    wxTextCtrl* dirTextCtrl = dirPicker->GetTextCtrl();

    wxString csvDir = dirPicker->GetPath();

    if (dirTextCtrl->IsModified())
    {
        csvDir = dirTextCtrl->GetValue();
    }

    bool inputValid = false;

    if (wxDir::Exists(csvDir))
    {
        wxDir dir(csvDir);
        if (dir.HasFiles("*.csv"))
        {
            inputValid = true;
        }
    }

    if (!inputValid)
    {
        wxString msg(wxString::Format("Input directory has no CSV files (%s)", csvDir.c_str()));
        wxMessageBox(msg, "Error", wxICON_ERROR);
        //SetStatusText(msg);
        return;
    }

	wxFileDialog dialog(this, "Choose table file", csvDir, "", "*.csv", wxFD_OPEN | wxFD_FILE_MUST_EXIST, wxDefaultPosition, wxDefaultSize, "filedlg");

	wxString fileToImport("");

    if (dialog.ShowModal() == wxID_OK)
    {    
		fileToImport = dialog.GetPath().c_str();
    }
	else
	{
		return;
	}

    textDisplay->Clear();

    sqlite3_connection& sqlConnection = tcDatabaseManager::Get()->GetConnection();

    tcDatabaseTranslator translator;
    bool success = translator.ImportTableFromCSV(sqlConnection, fileToImport);

    wxString msg;
    if (success)
    {
		msg.Printf("Imported CSV %s data from  \"%s\"  to database", fileToImport.c_str(), csvDir.c_str());
        if (translator.statusRows.size() > 0)
        {
            textDisplay->AppendText("IMPORT LOG:\n\n");
            for (size_t n=0; n<translator.statusRows.size(); n++)
            {
                textDisplay->AppendText(translator.statusRows[n]);
            }
        }
        
    }
    else
    {
        msg.Printf("ERROR importing CSV data from \"%s\"  to database", csvDir.c_str());
    }
    //SetStatusText(msg);

}


void tcToolPanel::OnCSVDirSelect(wxFileDirPickerEvent& event)
{
    lastCSVPath = event.GetPath();
}


void tcToolPanel::SetCSVPath(const wxString& val)
{
    lastCSVPath = val;
    dirPicker->SetPath(val);
}

tcToolPanel::tcToolPanel(wxWindow* parent) 
: wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, "ToolPanel")
{
    wxButton* button1 = new wxButton(this, ID_ExportAllDatabase, wxT("Export all to CSV"), wxDefaultPosition, wxDefaultSize);
    wxButton* button2 = new wxButton(this, ID_ImportAllDatabase, wxT("Import all from CSV"), wxDefaultPosition, wxDefaultSize);

    wxButton* button3 = new wxButton(this, ID_ExportTableDatabase, wxT("Export table to CSV"), wxDefaultPosition, wxDefaultSize);
    wxButton* button4 = new wxButton(this, ID_ImportTableDatabase, wxT("Import table from CSV"), wxDefaultPosition, wxDefaultSize);

    wxButton* button5 = new wxButton(this, ID_CreateIndices, wxT("Create Fast Lookup Indices"), wxDefaultPosition, wxDefaultSize);


    wxStaticText* csvText = new wxStaticText(this, wxID_ANY, "CSV directory:", wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT);
    csvText->SetFont(wxFont(11, wxDEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, "Arial"));

    dirPicker = new wxDirPickerCtrl(this, wxID_ANY, "", "Select directory for CSV import/export", wxDefaultPosition, wxSize(300, -1), wxDIRP_DEFAULT_STYLE);

    textDisplay = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_READONLY | wxTE_DONTWRAP);


    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer* databaseRow = new wxBoxSizer(wxHORIZONTAL);


    wxBoxSizer* csvRow = new wxBoxSizer(wxHORIZONTAL);
    csvRow->Add(csvText, 1, wxALL | wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 5);
    csvRow->Add(dirPicker, 2, wxALIGN_LEFT | wxEXPAND | wxALL, 10);

    wxBoxSizer* buttonRow = new wxBoxSizer(wxHORIZONTAL);
    //buttonRow->Add(new wxPanel(this, -1), 1, wxEXPAND | wxALL, 10);
    buttonRow->Add(button1, 0, wxALL, 10);
    buttonRow->Add(button2, 1, wxALL, 10);
    buttonRow->Add(button3, 1, wxALL, 10);
    buttonRow->Add(button4, 1, wxALL, 10);
    buttonRow->Add(button5, 1, wxALL, 10);
    //buttonRow->Add(new wxPanel(this, -1), 1, wxEXPAND | wxALL, 10);


    vbox->Add(databaseRow, 0,  wxEXPAND | wxALL, 10);
    vbox->Add(buttonRow, 0,  wxALIGN_LEFT | wxALL, 10);
    vbox->Add(csvRow, 0, wxALIGN_LEFT | wxEXPAND | wxALL, 10);
    vbox->Add(textDisplay, 1, wxEXPAND | wxALL, 10);

    this->SetSizer(vbox);
}

tcToolPanel::~tcToolPanel()
{
}