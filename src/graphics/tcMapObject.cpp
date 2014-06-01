/**  
**  @file tcMapObject.cpp
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


#include "tcMapObject.h"
#include "tc3DWindow2.h"
#include "tcMapView.h"
#include "math_constants.h"
#include "simmath.h"
#include "tcGeometry.h"
#include "tcTexture2D.h"
#include "common/tcStream.h"
#include "tcCommandQueue.h"
#include "tcTime.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif 


tcMapView* tcMapObject::mapView = NULL;

boost::shared_ptr<tcGeometry> tcMapObject::marker;
tcCommandQueue* tcMapObject::commandInterface = 0;

/**
* Loads state from stream
*/
tcStream& tcMapObject::operator<<(tcStream& stream)
{
	stream >> color.x;
	stream >> color.y;
	stream >> color.z;
	stream >> color.w;

    stream >> isActive;
	stream >> markerEnabled;
	stream >> useRelativeCoords;
    stream >> _x;
    stream >> _y;

	return stream;
}

/**
* Saves state to stream
*/
tcStream& tcMapObject::operator>>(tcStream& stream)
{
	stream << color.x;
	stream << color.y;
	stream << color.z;
	stream << color.w;

    stream << isActive;
	stream << markerEnabled;
	stream << useRelativeCoords;
    stream << _x;
    stream << _y;

	return stream;
}

void tcMapObject::LoadMarker(const std::string& filename)
{
    float w = 16.0f;
	
    marker = boost::shared_ptr<tcGeometry>(new tcGeometry);
    
    tcTexture2D* tex = new tcTexture2D("images\\black_marker.png");
    marker->MakeTexturedSymbol(boost::shared_ptr<tcTexture2D>(tex), w);
}

void tcMapObject::SetCommandInterface(tcCommandQueue* ci)
{
    commandInterface = ci;
}

/**
* 
*/
wxString tcMapObject::GetColorString() const
{
    wxString s;

    unsigned int R = unsigned int(255.0f*color.x);
    unsigned int G = unsigned int(255.0f*color.y);
    unsigned int B = unsigned int(255.0f*color.z);
    unsigned int A = unsigned int(255.0f*color.w);

    s.Printf("0x%02X%02X%02X%02X", R, G, B, A);

    return s;
}

void tcMapObject::ConfigureWithString(const std::string& str)
{
    wxString s(str.c_str());

    if (s.Find("0x") == wxNOT_FOUND)
    {
        if (s == "auto")
        {
            SetColor(Vec4(0, 0, 0, 1));
            SetAttributes(tcMapObject::AUTO_COLOR);
        }
        else if (s == "black")
        {
            SetColor(Vec4(0, 0, 0, 1));
        }
        else if (s == "white")
        {
            SetColor(Vec4(1, 1, 1, 1));
        }
        else if (s == "blue")
        {
            SetColor(Vec4(0, 0, 1, 1));
        }
        else if (s == "red")
        {
            SetColor(Vec4(1, 0, 0, 1));
        }
        else
        {
            SetColor(Vec4(0, 0, 0, 1));
            SetAttributes(tcMapObject::AUTO_COLOR);
        }
    }
    else
    {
        long nVal;
        s.ToLong(&nVal, 0);

        const float a = 1.0f/255.0f;
        float R = a * float((nVal >> 24) & 0xFF);
        float G = a * float((nVal >> 16) & 0xFF);
        float B = a * float((nVal >> 8) & 0xFF);
        float A = a * float(nVal & 0xFF);

        SetColor(Vec4(R, G, B, A));
    }
}

void tcMapObject::Draw(tc3DWindow2* host)
{
    if (!isActive) return;
    tcPoint pscreen = GetScreenPoint();
    float x = pscreen.x;
    float y = pscreen.y;

	if (markerEnabled)
	{
		host->DrawLineR(x-8, y-8, x+8, y+8, color);
		host->DrawLineR(x+8, y-8, x-8, y+8, color);
	}

    if (isHooked)
    {
		host->DrawLineR(x-8, y-10, x+8, y-10, color);
    }
}

void tcMapObject::FlagForDelete()
{
    flaggedForDelete = true;
    isActive = false;
}


unsigned int tcMapObject::GetCreateTime() const
{
    return createTime;
}

/**
* @return screen distance from screen point pos
*/
float tcMapObject::GetScreenDistanceFrom(const wxPoint& pos)
{
    tcPoint screenPoint = GetScreenPoint();
    tcPoint refPoint((float)pos.x, (float)pos.y);

    return screenPoint.DistanceTo(refPoint);
}

bool tcMapObject::IsComplexInteractive() const
{
    return isComplexInteractive;
}

bool tcMapObject::IsDragActive() const
{
    return dragActive;
}


bool tcMapObject::IsFlaggedForDelete() const
{
    return flaggedForDelete;
}


bool tcMapObject::IsInteractive() const
{
    return isInteractive;
}

int tcMapObject::GetAttributes() const
{
    return attributes;
}

/**
* @return screen coordinates of map object
*/
tcPoint tcMapObject::GetScreenPoint() const
{
    wxASSERT(mapView);
	if (useRelativeCoords)
	{
		wxRealPoint p = mapView->RelativeToScreen(_x, _y);
		return tcPoint(p.x, p.y);
	}
	else
	{
		return mapView->GeoToScreen(_x, _y);
	}
}

void tcMapObject::MoveToScreenPoint(const wxPoint& pos)
{
    wxASSERT(mapView);
	if (!useRelativeCoords)
	{
        tcPoint p = mapView->ScreenToGeo((float)pos.x, (float)pos.y);
        _x = p.x;
        _y = p.y;
	}
	else
	{
        _x = (double)pos.x;
        _y = (double)pos.y;
	}
}

/**
* @return false if keyCode is valid command for this object
*/
bool tcMapObject::ProcessKey(int keyCode)
{
    switch (keyCode)
    {
    case 'b':
        SetColor(Vec4(0, 0, 0, 1));
        break;
    case 'w':
        SetColor(Vec4(1, 1, 1, 1));
        break;
    case WXK_DELETE:
        FlagForDelete();
        break;
    default:
        break;
    }

    return false;
}

bool tcMapObject::ProcessLButtonDown(const wxPoint& pos)
{
    return false;
}

void tcMapObject::SetAttributes(int val)
{
    attributes = val;
}

void tcMapObject::SetColor(const Vec4& c)
{
    color = c;
}

void tcMapObject::SetComplexInteractive(bool state)
{
    isInteractive = false;

    isComplexInteractive = state;
}

void tcMapObject::SetCreateTime(unsigned int n)
{
    createTime = n;
}

void tcMapObject::SetDragActive(bool state)
{
    dragActive = state;
}

void tcMapObject::SetFontSize(float fontSize_)
{
    fontSize = fontSize_;
}


void tcMapObject::SetIsHooked(bool state)
{
    isHooked = state;
}

void tcMapObject::SetInteractive(bool state)
{
    isComplexInteractive = false;

    isInteractive = state;
}

/**
* mapView is used to translate lat/lon coords into screen coords.
* SetMapView has to be called before each draw if there are multiple maps.
*/
void tcMapObject::SetMapView(tcMapView *mv)
{
    mapView = mv;
}

/**
* Updates isVisible which supports time delay and fade-in effects for tcMapObjects
*/
void tcMapObject::UpdateVisibility()
{
    unsigned int t = tcTime::Get()->Get30HzCount();
    unsigned int dt_create = t - createTime; // need this too since we're doing unsigned math
    unsigned int dt = t - createTime - showDelay;

    if (dt_create <= showDelay)
    {       
        isVisible = false;
        fadeInAlpha = 0;
    }
    else if (dt > fadeInTime)
    {
        isVisible = true;
        fadeInAlpha = 1.0f;
    }
    else
    {
        isVisible = true;
        fadeInAlpha = float(dt) / float(fadeInTime);
    }
}

tcMapObject::tcMapObject() :
  _x(0), _y(0),
  isActive(true),
  useRelativeCoords(false),
  isInteractive(false),
  isComplexInteractive(false),
  isHooked(false),
  flaggedForDelete(false),
  dragActive(false),
  markerEnabled(true),
  attributes(0),
  isVisible(true),
  showDelay(90),
  fadeInTime(15),
  fadeInAlpha(1),
  fontSize(16.0f)
{
    createTime = tcTime::Get()->Get30HzCount();
}

tcMapObject::tcMapObject(double x, double y, bool useRel)
: useRelativeCoords(useRel),
  isActive(true),
  isInteractive(false),
  isComplexInteractive(false),
  isHooked(false),
  flaggedForDelete(false),
  dragActive(false),
  markerEnabled(true),
  attributes(0),
  isVisible(true),
  showDelay(90),
  fadeInTime(15),
  fadeInAlpha(1),
  fontSize(16.0f)
{
	if (useRel)
	{
		_x = x;
		_y = y;
	}
	else
	{
		_x = x * C_PIOVER180; // convert to radian lon/lat
		_y = y * C_PIOVER180;
	}
	color =  Vec4(0.392f, 1.0f, 0.392f, 1.0f); // green default

    if (marker.get() == 0) LoadMarker("black_marker.png");

    createTime = tcTime::Get()->Get30HzCount();
}

tcMapObject::~tcMapObject()
{
}


/********** tcMapTextObject **************/

/**
* Loads state from stream
*/
tcStream& tcMapTextObject::operator<<(tcStream& stream)
{
	tcMapObject::operator<<(stream);

	stream >> caption;

	return stream;
}


/**
* Saves state to stream
*/
tcStream& tcMapTextObject::operator>>(tcStream& stream)
{
	tcMapObject::operator>>(stream);

	stream << caption;

	return stream;
}


void tcMapTextObject::Draw(tc3DWindow2* host)
{
    if (!isActive) return;
    tcPoint pscreen = GetScreenPoint();
    float x = pscreen.x;
    float y = pscreen.y;


    host->DrawTextR(caption.c_str(), x+5.0f, y, 
        mapView->GetDefaultFont(), color, fontSize, tc3DWindow2::AlignmentType(textAlignment));

	if (markerEnabled) // avoids parent draw overhead this way
	{
        host->DrawGeometryR(marker.get(), x, y);
		//mapView->DrawLineR(x-8, y-8, x+8, y+8, color);
		//mapView->DrawLineR(x+8, y-8, x-8, y+8, color);
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


/**
* @return false if keyCode is valid command for this object
*/
bool tcMapTextObject::ProcessKey(int keyCode)
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

void tcMapTextObject::SetTextAlignment(int mode)
{
    textAlignment = mode;
}


tcMapTextObject::tcMapTextObject()
: caption("Uninitialized"), textAlignment(tc3DWindow2::LEFT_BASE_LINE)
{
}

tcMapTextObject::tcMapTextObject(const std::string& text, double x, double y, bool useRel)
: tcMapObject(x, y, useRel), caption(text), textAlignment(tc3DWindow2::LEFT_BASE_LINE)
{
    if (useRel)
    {
        markerEnabled = false; // never draw marker for relative coordinates
    }
}


tcMapTextObject::~tcMapTextObject()
{
}

