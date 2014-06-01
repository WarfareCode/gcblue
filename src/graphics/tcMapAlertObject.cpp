/**  
**  @file tcMapAlertObject.cpp
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



#include "stdwx.h" // precompiled header file


#include "tcMapAlertObject.h"
#include "tc3DWindow2.h"
#include "tcMapView.h"
#include "math_constants.h"
#include "simmath.h"
#include "tcGeometry.h"
#include "tcTexture2D.h"
#include "common/tcStream.h"
#include "tcTime.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif 


/**
* Loads state from stream
*/
tcStream& tcMapAlertObject::operator<<(tcStream& stream)
{
	tcMapObject::operator<<(stream);

	stream >> caption;

	return stream;
}


/**
* Saves state to stream
*/
tcStream& tcMapAlertObject::operator>>(tcStream& stream)
{
	tcMapObject::operator>>(stream);

	stream << caption;

	return stream;
}


void tcMapAlertObject::Draw(tc3DWindow2* host)
{
    if (!isActive) return;
    tcPoint pscreen = GetScreenPoint();
    float x = pscreen.x;
    float y = pscreen.y;

    unsigned int life = tcTime::Get()->Get30HzCount() - birthCount;
    if (life >= 900)
    {
        FlagForDelete();
    }

    /*host->DrawTextR(caption.c_str(), x+5.0f, y, 
        mapView->GetDefaultFont(), color, 16.0, tc3DWindow2::LEFT_BASE_LINE);*/

    bool draw = (icon.get() != 0) && ((life > 30) || (life/2 % 4 == 0));
    if (draw)
    {
        float alpha = 0.001f * float(1000 - life);
        Vec4 color(1.0, 1.0, 1.0, alpha);
        icon->SetColor(color);

        if (!alignBottom)
        {
            host->DrawGeometryR(icon.get(), x, y);
        }
        else
        {
            host->DrawGeometryR(icon.get(), x, y - 0.5f*icon->GetSize());
        }
	}

    if (isHooked)
    {
        const Vec4 hookColor(1, 1, 1, 1);
        const float a = 10.0f;

		host->DrawLineR(x-a, y-a, x+a, y-a, hookColor);
		host->DrawLineR(x-a, y+a, x+a, y+a, hookColor);
		host->DrawLineR(x-a, y-a, x-a, y+a, hookColor);
		host->DrawLineR(x+a, y-a, x+a, y+a, hookColor);
    }

}


void tcMapAlertObject::LoadIcon(const std::string& fileName)
{
    float w = 32.0f;
	
    icon = boost::shared_ptr<tcGeometry>(new tcGeometry);
    
    tcTexture2D* tex = new tcTexture2D(fileName);
    icon->MakeTexturedSymbol(boost::shared_ptr<tcTexture2D>(tex), w);
}

/**
* @return false if keyCode is valid command for this object
*/
bool tcMapAlertObject::ProcessKey(int keyCode)
{
    wxString s(caption.c_str());

    if (keyCode == WXK_BACK)
    {
        if (s.size() > 0) s = s.Left(s.size()-1);
    }
    else if (isalnum(keyCode))
    { 
        s += wxChar(keyCode);
    }
    else if (keyCode == WXK_SPACE)
    {
        s += ' ';
    }
    else
    {
        return tcMapObject::ProcessKey(keyCode);
    }

    caption = s.c_str();

    return false;
}


void tcMapAlertObject::SetAlignBottom(bool state)
{
    alignBottom = state;
}


tcMapAlertObject::tcMapAlertObject()
: alignBottom(false)
{
    caption = "Uninitialized";
    birthCount = tcTime::Get()->Get30HzCount();
}

tcMapAlertObject::tcMapAlertObject(const std::string& text, double x, double y, bool useRel)
: tcMapObject(x, y, useRel), caption(text), alignBottom(false)
{
    birthCount = tcTime::Get()->Get30HzCount();
}


tcMapAlertObject::~tcMapAlertObject()
{
}

