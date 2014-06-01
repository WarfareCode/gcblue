/** 
**  @file tcTextDialog.cpp 
*/
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

#include "stdwx.h"
#include <wx/textctrl.h>
#include "tcTextDialog.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif 


wxString tcTextDialog::GetText()
{
    wxString s;
    for (int n=0; n<dialogText->GetNumberOfLines(); n++)
    {
        s += dialogText->GetLineText(n);
        s += '\n';
    }

    return s;
}


tcTextDialog::tcTextDialog (wxWindow * parent, wxWindowID id, const wxString & title,
                            const wxString& startText,
                            const wxPoint & position, const wxSize & size, long style)
:  wxDialog( parent, id, title, position, size, style)
{
	wxString dimensions = "", s;
	wxPoint p(10, 10);
	wxSize  sz;
 
	sz.SetWidth(size.GetWidth() - 20);
	sz.SetHeight(size.GetHeight() - 80);

	dialogText = new wxTextCtrl(this, -1, startText, p, sz, wxTE_MULTILINE);

    //dialogText->SetFocus();
    //dialogText->SetEditable(true);

	p.y += sz.GetHeight() + 10;
	wxButton * b = new wxButton(this, wxID_OK, _("OK"), p, wxDefaultSize );
	p.x += 110;
	wxButton * c = new wxButton(this, wxID_CANCEL, _("Cancel"), p, wxDefaultSize );
}

tcTextDialog::~tcTextDialog()
{
}