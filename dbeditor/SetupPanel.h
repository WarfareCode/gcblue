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
#ifndef _SETUPPANEL_H_
#define _SETUPPANEL_H_

#include "SetupPanel.h"
#include "BasePanel.h"

#include <vector>

class tcTextEditControl;
class wxGridEvent;
class wxGrid;
class wxButton;
class wxStaticText;
class tcComboEditControl;
class tcTextEditControl;

/**
* Class for displaying and updating platform_setup information
*/
class tcSetupPanel : public tcBasePanel
{
public:
    enum {JUMP_TO = 632, SETUP_SELECT = 491};

    virtual void Save();

    virtual void SetDatabaseClass(const wxString& s);

    static wxFrame* eventFrame;

    tcSetupPanel(wxWindow* parent, const wxString& table_, const wxString& panelName);
    virtual ~tcSetupPanel();

private:
    enum {NEW_SETUP, RENAME_SETUP, DUPLICATE_SETUP, DELETE_SETUP};
    wxFont errorFont;

    wxArrayString setupFields;
    std::vector<wxArrayString> setupData;
    wxArrayString setupNames;
    wxString currentSetup;
    wxString launcherLoadoutName;
    wxString magazineLoadoutName;
    wxString airComplementName;

    wxStaticText* launcherTitle;
    wxGrid* launcherLoadout;
    wxArrayString launcherLabels;
    wxArrayString launcherFields;

    std::vector<wxStaticText*> magazineTitle;
    std::vector<wxGrid*> magazineLoadout;
    wxArrayString magazineLabels;
    wxArrayString magazineFields;

    wxStaticText* airComplementTitle;
    wxGrid* airComplement;
    wxArrayString airComplementLabels;
    wxArrayString airComplementFields;

    tcComboEditControl* setupComboBox; // for selecting setup to edit
    tcTextEditControl* initialYear;
    tcTextEditControl* finalYear;

    wxButton* newButton;
    wxButton* renameButton;
    wxButton* duplicateButton;
    wxButton* deleteButton;

    wxArrayString launcherEquipmentTables;
    wxArrayString storesEquipmentTables;
    wxArrayString aircraftTables;

    void OnGridCellChange(wxGridEvent& event);
    void OnGridLabelRClick(wxGridEvent& event);
    void OnGridLeftDClick(wxGridEvent& event);
    void OnGridRightClick(wxGridEvent& event);
    void OnTextUpdated(wxCommandEvent& event);
    void OnNewSetup(wxCommandEvent& event);
    void OnRenameSetup(wxCommandEvent& event);
    void OnDuplicateSetup(wxCommandEvent& event);
    void OnDeleteSetup(wxCommandEvent& event);

    void InitializePanel();

    void InitializeTableControl(wxGrid* grid, const wxArrayString& columnLabels);

    bool IsTableControlChanged(wxGrid* grid, const wxString& tableName, const wxString& setupDatabaseClass, 
        const wxArrayString& fields, const wxString& additionalConstraint);

    void UpdateAirComplementControl(const wxString& setupName);
    void UpdateLauncherControl(const wxString& setupName);
    void UpdateMagazineControls(const wxString& setupName);
    void UpdateSetupYears(const wxString& setupName);

    void InitializeReferenceTables();
    void CheckTableReferences(wxGrid* grid, int col, const wxArrayString& referenceTables_);

    void DeleteSelectedRows();
    void InsertRowAbove();

    void UpdateAllTableControls();
    void SavePlatformTable(wxGrid* grid, const wxString& tableName, const wxString& setupDatabaseClass, 
                                         const wxArrayString& fields, const wxString& additionalConstraint);
    void SavePlatformTableMagazine(wxGrid* grid, const wxString& tableName, const wxString& setupDatabaseClass, 
                                         const wxArrayString& fields, int magazineId);
    void SaveSetupYears();
    void AddReferenceCombo(wxXmlNode* node, wxBoxSizer* sizer);

    void UpdateSetupData();
    int GetCurrentSetupIndex();
    const std::vector<int> GetLauncherIdList();
    const std::vector<int> GetMagazineIdList();
    const wxArrayString& GetMagazineNameList();
    bool HasLaunchers();
    bool HasMagazines();
    bool HasAirComplement();
    const wxString& GetNewSetupName();
    void UpdateGridRows(wxGrid* grid);
    void AddDefaultLauncherLoadout(const wxString& loadoutName);
	const wxString& GetLauncherSummary(const std::vector<wxArrayString>& data);
    const wxString& GetMagazineSummary(const wxString& magazineClass, const std::vector<wxArrayString>& data, bool& isOkay);

    DECLARE_EVENT_TABLE()
};












#endif