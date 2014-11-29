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
#ifndef _BASEPANEL_H_
#define _BASEPANEL_H_

#include "wx/panel.h"
#include "wx/scrolwin.h"
#include <vector>

class tcEditControl;
class wxXmlNode;
class wxBoxSizer;

/**
* Base class for common management of controls
*/
class tcBasePanel : public wxScrolledWindow
{
public:

    virtual void SetDatabaseClass(const wxString& s);
    virtual void Save();
    bool ValuesHaveChanged() const;

    tcBasePanel(wxWindow* parent, const wxString& table_, const wxString& panelName);
    tcBasePanel(wxWindow* parent, const wxString& table_, const wxString& panelName, const wxString& formPath);
    virtual ~tcBasePanel();

protected:
    wxString databaseClass;
    wxString table;


    std::vector<tcEditControl*> controls;
    wxArrayString fieldList;

    std::vector<tcEditControl*> infoControls; ///< controls for display only, no database update

    void AddControl(tcEditControl* ctrl);
    bool LoadLabelValueData(const wxString& fileName, wxArrayString& labels, wxArrayString& values);
    void LoadFromXml(const wxString& fileName);

    

private:
    void LoadXmlSizer(wxXmlNode* node, wxBoxSizer* parent);
    void AddXmlTextControl(wxXmlNode* node, wxBoxSizer* sizer);
    void AddXmlNumberControl(wxXmlNode* node, wxBoxSizer* sizer);
	void AddXmlCalculation(wxXmlNode* node, wxBoxSizer* sizer);
    void AddXmlCheckBox(wxXmlNode* node, wxBoxSizer* sizer);
    void AddXmlComboBox(wxXmlNode* node, wxBoxSizer* sizer);
    void AddXmlBitfield(wxXmlNode* node, wxBoxSizer* sizer);

    void ReadSizerProperties(wxXmlNode* node, wxOrientation& orientation, long& proportion, long& labelWidth, long& controlWidth);

    DECLARE_EVENT_TABLE()
};












#endif