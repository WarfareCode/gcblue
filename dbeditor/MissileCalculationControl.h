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
#ifndef _MISSILECALCULATIONCONTROL_H_
#define _MISSILECALCULATIONCONTROL_H_

#include "MissileCalculationControl.h"
#include "EditControl.h"
#include "mathplot.h"

#include "wx/panel.h"

class wxCheckBox;
class wxStaticText;
class wxXmlNode;
class wxTextCtrl;
class wxButton;

/**
* Class for calculation speed, range, etc
*/
class tcMissileCalculationControl : public tcEditControl
{
public:

    virtual void SetValue(const wxString& s);
	virtual void UpdateControl();

    void SetLabelWidth(int val);
    void SetControlWidth(int val);

	void LoadXmlConfig(wxXmlNode* config);
	void SaveXmlConfig(wxXmlNode* config);

	void OnUpdateCalculation(wxCommandEvent& event);

    tcMissileCalculationControl(wxWindow* parent, const wxSize& size, const wxString& label_);
    tcMissileCalculationControl(wxWindow* parent, const wxSize& size, const wxString& label_, 
							int textCtrlStyle, int textCtrlSizerFlags, int labelTextStyle, int labelTextSizerFlags);
    virtual ~tcMissileCalculationControl();

	static tcMissileCalculationControl* instance; // normally there is only one instance
	static tcMissileCalculationControl* Get();

private:
    enum {UPDATE_CALCULATION=24};

	wxButton* updateCalculation;

	wxTextCtrl* launchHeading;
	wxTextCtrl* launchElevation;
	wxTextCtrl* launchSpeed;
	wxTextCtrl* launchAltitude;

	wxTextCtrl* targetHeading;
	wxTextCtrl* targetSpeed;
	wxTextCtrl* targetAltitude;
	wxTextCtrl* targetRange;

	mpWindow* plotWindow;
	mpText* titleText;

	mpFXYVector* xyVectorSpeed;
	mpFXYVector* xyVectorAltitude;

    void CreateControls(int textCtrlStyle, int textCtrlSizerFlags, int labelTextStyle, int labelTextSizerFlags);
	void UpdateCalculation();

    DECLARE_EVENT_TABLE()
};

#endif