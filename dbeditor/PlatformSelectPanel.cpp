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
#include "PlatformSelectPanel.h"
#include "DatabaseManager.h"
#include "ListSelectDialog.h"
#include "FilterDialog.h"

#include "wx/stattext.h"
#include "wx/button.h"
#include "wx/sizer.h"
#include "wx/choicdlg.h"

BEGIN_EVENT_TABLE(tcPlatformSelectPanel, wxPanel)
    EVT_BUTTON(PREV_PLATFORM, tcPlatformSelectPanel::OnPrevPlatform)
    EVT_BUTTON(NEXT_PLATFORM, tcPlatformSelectPanel::OnNextPlatform)
    EVT_BUTTON(OPEN_SELECT_DIALOG, tcPlatformSelectPanel::OnOpenSelectDialog)
	EVT_BUTTON(OPEN_FILTER_DIALOG, tcPlatformSelectPanel::OnOpenFilterDialog)
    EVT_MOUSEWHEEL(tcPlatformSelectPanel::OnMouseWheel)
END_EVENT_TABLE()

wxArrayString tcPlatformSelectPanel::countryFilter;
wxDateTime tcPlatformSelectPanel::startFilterDate(1, wxDateTime::Jan, 1900, 0, 0, 0, 0);
wxDateTime tcPlatformSelectPanel::endFilterDate(1, wxDateTime::Jan, 2999, 0, 0, 0, 0);

const wxString& tcPlatformSelectPanel::GetPlatform() const
{
    static wxString result;

    result = platformName->GetLabel();

    if (PlatformNameValid(result))
    {
        return result;
    }
    else
    {
        result = "";
        return result;
    }
}

bool tcPlatformSelectPanel::IndexValid(size_t index) const
{
    return (index < platformList.size());
}

size_t tcPlatformSelectPanel::LookupPlatformIndex(const wxString& s) const
{
    std::map<wxString, size_t>::const_iterator iter =
        platformIndexMap.find(s);
    if (iter != platformIndexMap.end())
    {
        return iter->second;
    }
    else
    {
        wxASSERT(false);
        return 999999;
    }
}

const wxString& tcPlatformSelectPanel::LookupPlatformName(size_t idx) const
{
    static wxString result;
    
    if (idx < platformList.size())
    {
        result = platformList[idx];
    }
    else
    {
        result = "Error";
    }

    return result;
}

void tcPlatformSelectPanel::OnMouseWheel(wxMouseEvent& event)
{
    if (event.GetWheelRotation() > 0)
    {
        StepSelectedPlatform(-1);
    }
    else
    {
        StepSelectedPlatform(1);
    }
}

void tcPlatformSelectPanel::OnNextPlatform(wxCommandEvent& event)
{
    StepSelectedPlatform(1);
}

void tcPlatformSelectPanel::OnOpenFilterDialog(wxCommandEvent& event)
{
	tcFilterDialog dialog(this, "Configure Database Filter Options", countryFilter, startFilterDate, endFilterDate);
	dialog.SetSize(250, 600);


	if (dialog.ShowModal() == wxOK)
	{
		UpdatePanel();
	}

	//
	//wxArrayString selectedChoices;

	//choices.push_back("A");
	//choices.push_back("BB");
	//choices.push_back("CCC");
	//choices.push_back("DDDD");

	//wxMultiChoiceDialog choiceDialog(this, "Select Countries to Filter", "Filter Options", choices, wxCHOICEDLG_STYLE, wxDefaultPosition);

	//if (choiceDialog.ShowModal() == wxOK)
	//{
	//	selectedChoices = choiceDialog.GetS
	//}
}

void tcPlatformSelectPanel::OnOpenSelectDialog(wxCommandEvent& event)
{
    tcListSelectDialog* dialog = new tcListSelectDialog(this, "Select Platform", platformList);

    int selectIdx = dialog->ShowModal();

    if ((selectIdx >= 0) && IndexValid(size_t(selectIdx)))
    {
        wxString newSelection = LookupPlatformName(size_t(selectIdx));
        SelectPlatform(newSelection);
    }

}

void tcPlatformSelectPanel::OnPrevPlatform(wxCommandEvent& event)
{
    StepSelectedPlatform(-1);
}

bool tcPlatformSelectPanel::PlatformNameValid(const wxString& s) const
{
    std::map<wxString, size_t>::const_iterator iter =
        platformIndexMap.find(s);
    return (iter != platformIndexMap.end());
}

/**
* @return platform name immediately before <s> in sorted platformList
*/
const wxString& tcPlatformSelectPanel::PreviousPlatformName(const wxString& s) const
{
    static wxString previous;
    previous = "";

    for (size_t n=0; n<platformList.size(); n++)
    {
        if ((platformList[n] < s) && (platformList[n] > previous))
        {
            previous = platformList[n];
        }
    }

    return previous;
}

/**
* Used to set initial value of platform for startup
*/
void tcPlatformSelectPanel::InitializePlatform(const wxString& s)
{
	platformName->SetLabel(s);
}

/**
* @return true if platform s passes filter parameters
*/
bool tcPlatformSelectPanel::PassesFilter(const wxString& s) const
{
	tcDatabaseManager* databaseManager = tcDatabaseManager::Get();

	wxString countryName = databaseManager->GetCountry(s);

	if ((countryFilter.size() > 0) && (countryName.size() > 0))
	{
		if (countryFilter.Index(countryName, true, false) == wxNOT_FOUND)
		{
			return false;
		}
	}

	bool isWithinDateRange = databaseManager->IsWithinDateRange(s, startFilterDate, endFilterDate);

	return isWithinDateRange;
}

/**
* Change platform selection to s and post message to parent
* @return true if selected platform is valid
*/
bool tcPlatformSelectPanel::SelectPlatform(const wxString& s)
{
    bool success = false;

    if (PlatformNameValid(s))
    {
        platformName->SetLabel(s);

        wxCommandEvent command(wxEVT_COMMAND_BUTTON_CLICKED, selectionUpdatedId);    
        command.SetEventObject(this);
        AddPendingEvent(command);

        success = true;
    }
    else
    {
        platformName->SetLabel("");
        success = false;
    }

    return success;
}

void tcPlatformSelectPanel::SetSelectionUpdatedId(long id)
{
    selectionUpdatedId = id;
}

/**
* Step platform selection ahead or back by indicated stepSize
*/
void tcPlatformSelectPanel::StepSelectedPlatform(int stepSize)
{
    wxString current = platformName->GetLabel();

    size_t idx = LookupPlatformIndex(current);
    if (idx >= platformList.size())
    {
        if (platformList.size() > 0)
        {
            SelectPlatform(platformList[0]);
            return;
        }
    }

    int nIdx = int(idx);

    int adjustedIdx = nIdx + stepSize;

    adjustedIdx = std::min(std::max(adjustedIdx, 0), int(platformList.size())-1);
    
    wxString newSelection = LookupPlatformName(size_t(adjustedIdx));

	SelectPlatform(newSelection);
}

void tcPlatformSelectPanel::UpdatePanel()
{    
    Freeze();

    platformList.clear();

    tcDatabaseManager* databaseManager = tcDatabaseManager::Get();
    if (databaseManager->IsOpen())
    {
        platformList = databaseManager->GetPlatformList(table);
    }
    else
    {
    }
	
	// filter platforms
	wxArrayString filteredPlatforms;
	for (size_t n=0; n<platformList.size(); n++)
	{
		if (PassesFilter(platformList[n]))
		{
			filteredPlatforms.push_back(platformList[n]);
		}
	}
	platformList = filteredPlatforms;
	//

    UpdatePlatformMaps();

    wxString current = platformName->GetLabel();
    if (!PlatformNameValid(current))
    {
        if (platformList.size() > 0)
        {
            wxString previousName = PreviousPlatformName(current);
            SelectPlatform(previousName);
        }
        else
        {
            SelectPlatform("");
        }
    }

	// filter button color if filtering
	bool dateFiltering = (startFilterDate > wxDateTime(1, wxDateTime::Jan, 1900, 0, 0, 0, 0)) ||
		(endFilterDate < wxDateTime(1, wxDateTime::Jan, 2999, 0, 0, 0, 0));

	if ((countryFilter.size() > 0) || (dateFiltering))
	{
		filterDialog->SetForegroundColour(wxColour(200, 0, 10));
		wxFont font = filterDialog->GetFont();
		font.SetWeight(wxFONTWEIGHT_BOLD);
		filterDialog->SetFont(font);
	}
	else
	{
		filterDialog->SetForegroundColour(wxColour(0, 0, 0));
		wxFont font = filterDialog->GetFont();
		font.SetWeight(wxFONTWEIGHT_NORMAL);
		filterDialog->SetFont(font);
	}

    Thaw();
    
}

void tcPlatformSelectPanel::UpdatePlatformMaps()
{
    platformIndexMap.clear();
    indexPlatformMap.clear();

    for (size_t n=0; n<platformList.size(); n++)
    {
        platformIndexMap[platformList[n]] = n;
        indexPlatformMap[n] = platformList[n];
    }
}


tcPlatformSelectPanel::tcPlatformSelectPanel(wxWindow* parent, const wxString& table_) 
: wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, "PlatformSelect"),
  table(table_),
  selectionUpdatedId(55)
{
    prevPlatform = new wxButton(this, PREV_PLATFORM, "<", wxDefaultPosition, wxSize(24, 24), 0, wxDefaultValidator, "PrevPlat");
    nextPlatform = new wxButton(this, NEXT_PLATFORM, ">", wxDefaultPosition, wxSize(24, 24), 0, wxDefaultValidator, "NextPlat");
    
	openSelectDialog = new wxButton(this, OPEN_SELECT_DIALOG, "*", wxDefaultPosition, wxSize(24, 24), 0, wxDefaultValidator, "OpenSelectDialog");
	openSelectDialog->SetToolTip("Select platform from list");

	filterDialog = new wxButton(this, OPEN_FILTER_DIALOG, "F", wxDefaultPosition, wxSize(24, 24), 0, wxDefaultValidator, "OpenFilterDialog");
	filterDialog->SetToolTip("Configure filter options");


    platformName = new wxStaticText(this, wxID_ANY, "NO SELECTION", wxDefaultPosition, wxSize(300, -1), wxALIGN_LEFT, "PlatformNameText");
    platformName->SetFont(wxFont(11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

    wxBoxSizer* hbox = new wxBoxSizer(wxHORIZONTAL);


    int border = 3;
    hbox->Add(prevPlatform, 0, wxALL | wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, border);
    hbox->Add(nextPlatform, 0, wxALL | wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, border);
    hbox->Add(openSelectDialog, 0, wxALL | wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, border);
	hbox->Add(filterDialog, 0, wxALL | wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, border);

    hbox->Add(platformName, 1, wxALL | wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL | wxEXPAND, 8);
    

    this->SetSizer(hbox);
    hbox->SetSizeHints(this);

}

tcPlatformSelectPanel::~tcPlatformSelectPanel()
{
}