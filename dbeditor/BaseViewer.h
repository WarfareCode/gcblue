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
#ifndef _BASEVIEWER_H_
#define _BASEVIEWER_H_

#include "EditorMainPage.h"

class wxButton;
class wxNotebook;
class wxBookCtrlEvent;
class tcPlatformSelectPanel;
class tcBasePanel;

class tcBaseViewer : public tcEditorMainPage
{
public:

    void AddPage(tcBasePanel* panel, const wxString& pageName);
    void AddPage(const wxString& pageName, const wxString& formPath);
    void AddGridPage(const wxString& pageName, const wxString& xmlPath);
    void AddSetupPanel(const wxString& pageName);

    const wxString& GetTable() const;
	const wxString& GetPlatformName() const;

    void SetDatabaseClass(const wxString& s);
	void InitializeDatabaseClass(const wxString& s);

    virtual void Save();
    virtual void UpdatePage();

    tcBaseViewer(wxWindow* parent, const wxString& table_, const wxString& viewerName);
    virtual ~tcBaseViewer();

protected:
    tcPlatformSelectPanel* platformSelectPanel;

    wxButton* renameButton;
    wxButton* duplicateButton;
    wxButton* applyButton;
    wxButton* undoButton;
    wxButton* deleteButton;
    wxNotebook* panelNotebook;

    wxString platformName; ///< name of current selected platform
    wxString table; ///< name of platform table

    enum {RENAME_PLATFORM = 88, APPLY_EDITS = 1776, UNDO_EDITS = 89, DELETE_PLATFORM = 86, DUPLICATE_PLATFORM = 77, SELECTION_UPDATED = 222};

    virtual void OnPlatformUpdated(wxCommandEvent& event);
    virtual void OnDeletePlatform(wxCommandEvent& event);
    virtual void OnDuplicatePlatform(wxCommandEvent& event);
    virtual void OnRenamePlatform(wxCommandEvent& event);
    virtual void OnUndoEdits(wxCommandEvent& event);
    virtual void OnApplyEdits(wxCommandEvent& event);
    virtual void OnPageChanged(wxBookCtrlEvent& event);
    virtual void OnPageChanging(wxBookCtrlEvent& event);


    DECLARE_EVENT_TABLE()
};


#endif