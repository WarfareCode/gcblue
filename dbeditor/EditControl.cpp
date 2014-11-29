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
#include "EditControl.h"

#include "wx/sizer.h"

BEGIN_EVENT_TABLE(tcEditControl, wxPanel)
END_EVENT_TABLE()


int tcEditControl::labelWidth = 120;
int tcEditControl::controlWidth = 120;

    
wxFont tcEditControl::normalFont(8, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
wxFont tcEditControl::errorFont(8, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_ITALIC, wxFONTWEIGHT_BOLD);


const wxString& tcEditControl::GetEditValue() const
{
    return editValue;
}

const wxString& tcEditControl::GetFieldName() const
{
    return fieldName;
}

const wxString& tcEditControl::GetInitialValue() const
{
    return initialValue;
}

/**
* @return true if this control has been edited to value that's different from initial value
*/
bool tcEditControl::IsEdited() const
{
    return (editValue != initialValue);
}

bool tcEditControl::IsInfoOnly() const
{
    return infoOnly;
}

void tcEditControl::SetDatabaseClass(const wxString& s)
{
    databaseClass = s;
}

void tcEditControl::SetInfoOnly(bool state)
{
    infoOnly = state;
}

void tcEditControl::SetTooltipText(const wxString& s)
{
    tooltip = s;
}

void tcEditControl::SetValue(const wxString& s)
{
    initialValue = s;
    editValue = s;
}

/**
* Override in derived class
* Called to signal control to update itself
* with current database.
*/
void tcEditControl::UpdateControl()
{
}


tcEditControl::tcEditControl(wxWindow* parent, const wxSize& size, const wxString& fieldName_, const wxString& label_) 
: wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, "EditControlBase"),
  fieldName(fieldName_),
  label(label_),
  infoOnly(false),
  tooltip("")
{

}

tcEditControl::~tcEditControl()
{
}