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
#ifndef _RENAMESETUPDIALOG_H_
#define _RENAMESETUPDIALOG_H_

#include "wx/dialog.h"


class wxStaticText;
class wxTextCtrl;
class wxArrayString;

class tcRenameSetupDialog : public wxDialog
{
public:

    tcRenameSetupDialog(wxWindow* parent, bool makeCopy_, const wxString& title, const wxString& databaseClass_, const wxString& originalName, wxString& newName_);
    virtual ~tcRenameSetupDialog();

private:
    enum {EDIT_CONTROL = 77};
    wxString databaseClass;
    wxString setupName;
    wxString& newName;
    bool newNameValid;
    bool makeCopy;

    wxArrayString duplicateNameCheckTables;
    wxArrayString setupFields;

    wxStaticText* originalNameText;
    wxTextCtrl* renameEditCtrl;

    void OnOK(wxCommandEvent& event);
    void OnCancel(wxCommandEvent& event);
    void OnTextUpdated(wxCommandEvent& event);

    bool SetupExists() const;
    void Init();

    DECLARE_EVENT_TABLE()
};



#endif