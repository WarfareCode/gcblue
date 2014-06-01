/**  
**  @file tcMapOverlay.cpp
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

#ifndef WX_PRECOMP
#include "wx/wx.h" 
#endif // WX_PRECOMP

#include "tcMapOverlay.h"
#include "tcMapObject.h"
#include "tcMapObject.h"
#include "tcTacticalMapView.h"
#include "common/tcStream.h"
#include "common/tcObjStream.h"
#include "common/tcGameStream.h"
#include "tcMapMissionObject.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif 


/**
* Loads state from stream
*/
tcUpdateStream& tcMapOverlay::operator<<(tcUpdateStream& stream)
{
	overlayObjects.clear();

	unsigned int nObjects;
	stream >> nObjects;

	for (unsigned int n=0; n<nObjects; n++)
	{
		unsigned char typeCode;
		stream >> typeCode;

		if (typeCode == 1)
		{
			tcMapObject* obj = new tcMapTextObject();
			obj->operator<<(stream);

			AddMapObject(obj);
		}
        else if (typeCode == 0) // ignore
        {
        }
		else
		{
			fprintf(stderr, "tcMapOverlay::operator<< -- unrecognized type code\n");
			wxASSERT(false);
		}
	}

	return stream;
}

/**
* Saves state to stream
*/
tcUpdateStream& tcMapOverlay::operator>>(tcUpdateStream& stream)
{
	unsigned int nObjects = (unsigned int)overlayObjects.size();
	stream << nObjects;

	for (unsigned int n=0; n<nObjects; n++)
	{
		unsigned char typeCode = 0;
		tcMapObject* obj = overlayObjects[n];

        tcMapTextObject* mapText = dynamic_cast<tcMapTextObject*>(obj);
		if (mapText != 0)
		{
			typeCode = 1;
			stream << typeCode;
			overlayObjects[n]->operator>>(stream);
		}
        else
		{
			typeCode = 0;
			stream << typeCode;
		}
	}

	return stream;
}



/**
* Loads state from game stream
*/
tcGameStream& tcMapOverlay::operator<<(tcGameStream& stream)
{
	overlayObjects.clear();

	unsigned int nObjects;
	stream >> nObjects;

	for (unsigned int n=0; n<nObjects; n++)
	{
		unsigned char typeCode;
		stream >> typeCode;

		if (typeCode == 1)
		{
			tcMapObject* obj = new tcMapTextObject();
			obj->operator<<(stream);

			AddMapObject(obj);
		}
		else if (typeCode == 0) // ignore
        {
        }
        else
		{
			fprintf(stderr, "tcMapOverlay::operator<< -- unrecognized type code\n");
			wxASSERT(false);
		}
	}

	return stream;
}

/**
* Saves state to game stream
*/
tcGameStream& tcMapOverlay::operator>>(tcGameStream& stream)
{
	unsigned int nObjects = (unsigned int)overlayObjects.size();
	stream << nObjects;

	for (unsigned int n=0; n<nObjects; n++)
	{
		unsigned char typeCode = 0;
		tcMapObject* obj = overlayObjects[n];
		if (dynamic_cast<tcMapTextObject*>(obj))
		{
			typeCode = 1;
			stream << typeCode;
			overlayObjects[n]->operator>>(stream);
		}
		else
		{
			typeCode = 0;
			stream << typeCode;
		}
	}

	return stream;
}




void tcMapOverlay::AddMapObject(tcMapObject *obj)
{
    overlayObjects.push_back(obj);

    redraw = true;
}

void tcMapOverlay::ClearInteraction()
{
    if (hookedIdx < overlayObjects.size())
    {
        overlayObjects[hookedIdx]->SetIsHooked(false);
        overlayObjects[hookedIdx]->SetDragActive(false);
    }

    isInteracting = false;
    hookedIdx = 99999;
    
    Redraw();
}

void tcMapOverlay::ClearMapObjects()
{
    for (size_t n=0; n < overlayObjects.size(); n++)
    {
        delete overlayObjects[n];
    }
    overlayObjects.clear();

    redraw = true;
    isInteracting = false;
}

/**
* Safely delete objects that are IsFlaggedForDelete()
*/
void tcMapOverlay::DeleteFlaggedObjects()
{
    tcMapObject* hookedObj = 0;

    if (isInteracting && (hookedIdx < overlayObjects.size()))
    {
        hookedObj = overlayObjects[hookedIdx];
    }

    std::vector<tcMapObject*> temp;

    for (size_t n=0; n<overlayObjects.size(); n++)
    {
        if (!overlayObjects[n]->IsFlaggedForDelete())
        {
            temp.push_back(overlayObjects[n]);
        }
        else
        {
            redraw = true;
        }
    }

    overlayObjects = temp;

    if (hookedObj != 0)
    {
        for (size_t n=0; n<overlayObjects.size(); n++)
        {
            if (overlayObjects[n] == hookedObj)
            {
                hookedIdx = n;
                return;
            }
        }
    }

    ClearInteraction(); // hooked object was deleted


}

void tcMapOverlay::Draw()
{
    //static int updateCounter = 0;

    //if (updateCounter++ % 10 == 0)
    //{
    //    redraw = true;
    //}

    //if (!redraw) return;

    DeleteFlaggedObjects();

    StartDraw();

    for (size_t n=0; n < overlayObjects.size(); n++)
    {
        overlayObjects[n]->Draw(this);
    }

    FinishDraw();

    redraw = false;
}

tcMapMissionObject* tcMapOverlay::GetMissionObject(unsigned int missionId)
{
    for (size_t n=0; n < overlayObjects.size(); n++)
    {
        if (tcMapMissionObject* missionObject = 
            dynamic_cast<tcMapMissionObject*>(overlayObjects[n]))
        {
            if (missionObject->GetMissionId() == missionId)
            {
                return missionObject;
            }
        }
    }

    return 0;
}

tcMapObject* tcMapOverlay::GetObjectByRegisteredId(long id)
{
    for (size_t n=0; n<overlayObjects.size(); n++)
    {
        tcMapObject* obj_n = overlayObjects[n];
        if (obj_n->GetKey() == id) return obj_n;
    }
    return 0;
}


void tcMapOverlay::HookObject(size_t idx)
{
    if (isInteracting && (hookedIdx == idx))
    {
        return; // already hooked
    }

    if (hookedIdx < overlayObjects.size())
    {
        overlayObjects[hookedIdx]->SetIsHooked(false); // clear previous hook
        overlayObjects[hookedIdx]->SetDragActive(false);
    }

    if (idx >= overlayObjects.size()) // clear hook
    {
        ClearInteraction();
        return;
    }

    overlayObjects[idx]->SetIsHooked(true);
    hookedIdx = idx;
    isInteracting = true;
}


/**
* @return true if player is interacting with overlay
*/
bool tcMapOverlay::IsInteracting() const
{
    return isInteracting;
}

bool tcMapOverlay::IsInteractionBlocked() const
{
    return interactionBlocked;
}

void tcMapOverlay::SetInteractionBlocked(bool state)
{
    if (interactionBlocked == state) return;

    interactionBlocked = state;
    if (interactionBlocked)
    {
        ClearInteraction();
    }
}


void tcMapOverlay::OnChar(wxKeyEvent& event)
{
    if (!isInteracting)
    {
        event.ResumePropagation(1);
        event.Skip();
        return;
    }

    int nChar = event.GetKeyCode();

    if (nChar == WXK_ESCAPE)
    {
        ClearInteraction();
        return;
    }

    if (isInteracting && (hookedIdx < overlayObjects.size()))
    {
        overlayObjects[hookedIdx]->ProcessKey(nChar);
    }
    else
    {
	    event.Skip();
    }
}


void tcMapOverlay::OnLButtonDClick(wxMouseEvent& event)
{
    if (IsInteracting())
    {
        ClearInteraction();
    }
    else
    {
        event.ResumePropagation(1);
        event.Skip();
        return;
    }
}


void tcMapOverlay::OnLButtonDown(wxMouseEvent& event)
{
    if (interactionBlocked)
    {
        event.ResumePropagation(1);
        event.Skip();
        return;
    }

    wxPoint pos = event.GetPosition();

    for (size_t n=0; n < overlayObjects.size(); n++)
    {
        tcMapObject* obj = overlayObjects[n];

        if (obj->IsInteractive())
        {
            float dist = overlayObjects[n]->GetScreenDistanceFrom(pos);
            if (dist < 5.0f)
            {
                HookObject(n);
                tacticalMap->ClearHook();
                overlayObjects[n]->SetDragActive(true);
                Redraw();
                return;
            }
        }
        else if (obj->IsComplexInteractive())
        {
            if (obj->ProcessLButtonDown(pos))
            {
                HookObject(n);
                Redraw();
                return;
            }
        }
    }

    ClearInteraction();
    event.ResumePropagation(1);
    event.Skip();
}

void tcMapOverlay::OnLButtonUp(wxMouseEvent& event)
{
    if (!isInteracting)
    {
        event.ResumePropagation(1);
        event.Skip();
        return;
    }

    if (hookedIdx < overlayObjects.size())
    {
        overlayObjects[hookedIdx]->SetDragActive(false);
    }

    isInteracting = false;
}

void tcMapOverlay::OnLeaveWindow(wxMouseEvent& event)
{
    tacticalMap->OnLeaveWindow(event);
}

void tcMapOverlay::OnMouseMove(wxMouseEvent& event)
{
    if (!isInteracting)
    {
        event.ResumePropagation(1);
        event.Skip();
        return;
    }

    if (hookedIdx >= overlayObjects.size())
    {
        wxASSERT(false);
        return;
    }

    if (overlayObjects[hookedIdx]->IsDragActive())
    {
        overlayObjects[hookedIdx]->MoveToScreenPoint(event.GetPosition());
        Redraw();
    }
}

void tcMapOverlay::OnMButtonDown(wxMouseEvent& event)
{
    event.ResumePropagation(1);
    event.Skip();
}

void tcMapOverlay::OnMButtonUp(wxMouseEvent& event)
{
    event.ResumePropagation(1);
    event.Skip();
}

void tcMapOverlay::OnMouseWheel(wxMouseEvent& event)
{
    event.ResumePropagation(1);
    event.Skip();
}


void tcMapOverlay::OnRButtonDown(wxMouseEvent& event)
{
    event.ResumePropagation(1);
    event.Skip();
}


void tcMapOverlay::OnSize(wxSizeEvent& event)
{
    tc3DWindow2::OnSize(event);
}


void tcMapOverlay::Redraw()
{
    redraw = true;
}

/**
* Intended for edit mode
*/
void tcMapOverlay::SetAllTextInteractive(bool state)
{
    for (size_t n=0; n < overlayObjects.size(); n++)
    {
        if (tcMapTextObject* textObj = dynamic_cast<tcMapTextObject*>(overlayObjects[n]))
        {
            textObj->SetInteractive(state);
        }
    }
}

void tcMapOverlay::SetColor(const Vec4& color)
{
	for (size_t n=0; n < overlayObjects.size(); n++)
    {
        tcMapObject* obj = overlayObjects[n];
        if ((obj->GetAttributes() & tcMapObject::AUTO_COLOR) != 0)
        {
            overlayObjects[n]->SetColor(color);
        }
    }
}


tcMapOverlay::tcMapOverlay(tcTacticalMapView* parent, 
            const wxPoint& pos, const wxSize& size, 
            const wxString& name) :
    tc3DWindow2(parent, pos, size, name, parent),
    redraw(false),
    isInteracting(false),
    hookedIdx(0),
    tacticalMap(parent),
    interactionBlocked(false)
{


}

tcMapOverlay::~tcMapOverlay()
{
    ClearMapObjects();
}

