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
#ifndef _COMBOEDITCONTROL_H_
#define _COMBOEDITCONTROL_H_

#include "EditControl.h"


class wxComboBox;

/**
* Class for updating a single field of database record
*/
class tcComboEditControl : public tcEditControl
{
public:
    virtual void SetValue(const wxString& s);
    virtual void UpdateControl();

    void SetCommand(long val);
    void SetValuesAndLabels(const wxArrayString& values, const wxArrayString& labels);
    void SetUpdateFromDatabaseTable(const wxString& table);
    void SetUpdateFromDatabaseReferences(const wxArrayString& tableList, const wxArrayString& fieldList);

    tcComboEditControl(wxWindow* parent, const wxSize& size, const wxString& fieldName_, const wxString& label_, const wxArrayString& values, const wxArrayString& labels);
    virtual ~tcComboEditControl();

private:
    enum {COMBO_CTRL = 34};
    enum UpdateMode
    {
        NORMAL = 1, ///< don't update, use initial value/label pairs
        DATABASE_TABLE = 2, ///< update from database table
        DATABASE_REFERENCE = 3 ///< show records that are referring to databaseClass
    };
    long commandId;
    wxComboBox* comboCtrl;

    wxArrayString databaseValues; ///< values written to/read from database
    wxArrayString displayLabels; ///< corresponding choices displayed to user

    UpdateMode updateMode;

    wxString updateTable;
    wxArrayString referenceTables;
    wxArrayString referenceFields;

    const wxString& ValueToLabel(const wxString& s) const;
    const wxString& LabelToValue(const wxString& s) const;

    void OnTextUpdated(wxCommandEvent& event);
    void IndicateChanges();

    DECLARE_EVENT_TABLE()
};

#endif