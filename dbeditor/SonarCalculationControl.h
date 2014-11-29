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
#ifndef _SONARCALCULATIONCONTROL_H_
#define _SONARCALCULATIONCONTROL_H_

#include "SonarCalculationControl.h"
#include "EditControl.h"
#include "mathplot.h"

#include "wx/panel.h"

class wxCheckBox;
class wxStaticText;
class wxComboBox;
class wxTextCtrl;
class wxCheckBox;
class wxListBox;
class wxXmlNode;

/**
* Class for calculation air speed, range, etc
*/
class tcSonarCalculationControl : public tcEditControl
{
public:

    virtual void SetValue(const wxString& s);
	virtual void UpdateControl();

    void SetLabelWidth(int val);
    void SetControlWidth(int val);

	void OnSelectPlatform(wxCommandEvent& event);
	void OnSelectTarget(wxCommandEvent& event);
	void OnUpdateCalculation(wxCommandEvent& event);

	void LoadXmlConfig(wxXmlNode* sonarConfig);
	void SaveXmlConfig(wxXmlNode* sonarConfig);

    tcSonarCalculationControl(wxWindow* parent, const wxSize& size, const wxString& label_);
    tcSonarCalculationControl(wxWindow* parent, const wxSize& size, const wxString& label_, 
							int textCtrlStyle, int textCtrlSizerFlags, int labelTextStyle, int labelTextSizerFlags);
    virtual ~tcSonarCalculationControl();

	static tcSonarCalculationControl* instance; // normally there is only one instance
	static tcSonarCalculationControl* Get();

private:
    enum {UPDATE_CALCULATION=24, PLATFORM_SELECT=38, TARGET_SELECT=39};
	
	wxCheckBox* autoUpdate;
	wxButton* updateCalculation;

	wxButton* platformClass;
	wxTextCtrl* platformHeading;
	wxTextCtrl* platformSpeed;
	wxTextCtrl* platformDepth;

	wxButton* targetClass;
	wxTextCtrl* targetHeading;
	wxTextCtrl* targetSpeed;
	wxTextCtrl* targetDepth;

	wxString platformTable;
	wxString targetTable;

	wxTextCtrl* seaStateCtrl;
	wxTextCtrl* bottomDepthCtrl;
	wxComboBox* svpCtrl;
    
	mpWindow* plotWindow;
	mpText* titleText;
	mpFXYVector* xyVectorRangeSS1;
	mpFXYVector* xyVectorRangeSS3;
	mpFXYVector* xyVectorRangeSS5;

	mpWindow* detailedPlot;
	mpFXYVector* plot1;


    void CreateControls(int textCtrlStyle, int textCtrlSizerFlags, int labelTextStyle, int labelTextSizerFlags);
	void CreateDetailedPlot();
	void UpdateCalculation();

    DECLARE_EVENT_TABLE()
};

#endif