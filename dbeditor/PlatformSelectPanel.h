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
#ifndef _PLATFORMSELECTPANEL_H_
#define _PLATFORMSELECTPANEL_H_

#include "wx/panel.h"
#include <map>

class wxStaticText;
class wxButton;


class tcPlatformSelectPanel : public wxPanel
{
public:

    const wxString& GetPlatform() const;

    void UpdatePanel();

    bool SelectPlatform(const wxString& s);
    void InitializePlatform(const wxString& s);

    void SetSelectionUpdatedId(long id);

    tcPlatformSelectPanel(wxWindow* parent, const wxString& table_);
    virtual ~tcPlatformSelectPanel();

private:
    enum {PREV_PLATFORM = 99, NEXT_PLATFORM = 101, OPEN_SELECT_DIALOG = 100, OPEN_FILTER_DIALOG = 102};

    wxString table; ///< platform table to use

    wxStaticText* platformName;
    wxButton* prevPlatform;
    wxButton* nextPlatform;
    wxButton* openSelectDialog;
	wxButton* filterDialog;

	static wxArrayString countryFilter;
	static wxDateTime startFilterDate;
	static wxDateTime endFilterDate;

    wxArrayString platformList;
    std::map<wxString, size_t> platformIndexMap;
    std::map<size_t, wxString> indexPlatformMap;

    long selectionUpdatedId; ///< id of button command event that's posted to parent when selection is updated

    bool PlatformNameValid(const wxString& s) const;
    const wxString& PreviousPlatformName(const wxString& s) const;
    bool IndexValid(size_t index) const;
    const wxString& LookupPlatformName(size_t idx) const;
    size_t LookupPlatformIndex(const wxString& s) const;

    void UpdatePlatformMaps();

    void OnPrevPlatform(wxCommandEvent& event);
    void OnNextPlatform(wxCommandEvent& event);
    void OnOpenSelectDialog(wxCommandEvent& event);
	void OnOpenFilterDialog(wxCommandEvent& event);
    void OnMouseWheel(wxMouseEvent& event);

	bool PassesFilter(const wxString& s) const;

    void StepSelectedPlatform(int stepSize);

    

    DECLARE_EVENT_TABLE()
};












#endif