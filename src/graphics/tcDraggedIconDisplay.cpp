/**  
**  @file tcDraggedIconDisplay.cpp
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

#ifndef WX_PRECOMP
#include "wx/wx.h" 
#endif

#include "tcDraggedIconDisplay.h"
#include "tcDragStatus.h"
#include "tcGeometry.h"
#include "wx/utils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif 




void tcDraggedIconDisplay::Draw() 
{
    tcDragStatus* dragStatus = tcDragStatus::Get();
    if (dragStatus->IsDragging())
    {
        StartDraw();

        wxPoint pos = wxGetMousePosition(); // mouse pos in screen coordinates
        pos -= wxWindow::GetScreenPosition();
        tcGeometry* icon = dragStatus->GetIcon();

        size_t nItems = dragStatus->GetDraggedItemCount();
        nItems = std::min(nItems, size_t(10)); // don't draw any more than 10
        for (size_t n=nItems; n>1; n--)
        {
            float offset = float(n-1)*5.0f;
            DrawGeometryR(icon, pos.x-offset, pos.y-offset); // draw background icon to indicate multiple items being dragged
        }

       
		DrawGeometryR(icon, pos.x, pos.y);
		
		unsigned int quantity = dragStatus->GetQuantity();
		if (quantity)
		{
		    // draw quantity label
            wxString quantityText = wxString::Format("%d", quantity);
            const Vec4 color(1.0f, 1.0f, 1.0f, 1.0f);
            
            /* TODO: need something here to indicate icon size or make this
            ** part of the icon creation instead */
			DrawTextR(quantityText.c_str(), pos.x - 14.0f, pos.y + 13.0f, 
				defaultFont.get(), color, 12.0f, LEFT_BASE_LINE);
        }

        FinishDraw();
    }

	
}

boost::shared_ptr<tcGeometry> tcDraggedIconDisplay::GetIcon()
{
    return icon;
}

void tcDraggedIconDisplay::SetIcon(boost::shared_ptr<tcGeometry> icon_)
{
    icon = icon_;
}    


tcDraggedIconDisplay::tcDraggedIconDisplay(wxWindow *parent) :
    tc3DWindow2(parent, wxPoint(0, 0), wxSize(1, 1), "DraggedIconDisplay") 
{
    
}

tcDraggedIconDisplay::~tcDraggedIconDisplay() 
{

}

