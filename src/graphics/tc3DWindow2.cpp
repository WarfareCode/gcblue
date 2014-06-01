/**  
**  @file tc3DWindow2.cpp
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



#include "tc3DWindow2.h"
#include "AError.h"
#include <stdio.h>
#include <iostream>
#include "tcString.h"
#include "tcSound.h"
#include "tcTVEngine.h"
#include "tcFont.h"
#include "tcGeometry.h"
#include "tcTexture2D.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif 


BEGIN_EVENT_TABLE(tc3DWindow2, wxWindow)
EVT_PAINT(tc3DWindow2::OnPaint)
EVT_NC_PAINT(tc3DWindow2::OnNcPaint)
EVT_ERASE_BACKGROUND(tc3DWindow2::OnEraseBackground)
EVT_MOVE(tc3DWindow2::OnMove)
EVT_LEFT_DOWN(tc3DWindow2::OnLButtonDown) 
EVT_LEFT_DCLICK(tc3DWindow2::OnLButtonDClick)
EVT_LEFT_UP(tc3DWindow2::OnLButtonUp)  
EVT_RIGHT_DOWN(tc3DWindow2::OnRButtonDown) 
EVT_MOTION(tc3DWindow2::OnMouseMove)  
EVT_MOUSEWHEEL(tc3DWindow2::OnMouseWheel)
EVT_MIDDLE_DOWN(tc3DWindow2::OnMButtonDown)
EVT_MIDDLE_UP(tc3DWindow2::OnMButtonUp)
EVT_KEY_DOWN(tc3DWindow2::OnKeyDown)  ///< any key has been pressed  
EVT_CHAR(tc3DWindow2::OnChar)  
EVT_ENTER_WINDOW(tc3DWindow2::OnEnterWindow)
EVT_LEAVE_WINDOW(tc3DWindow2::OnLeaveWindow)
EVT_SHOW(tc3DWindow2::OnShow)
EVT_SIZE(tc3DWindow2::OnSize)
EVT_SET_FOCUS(tc3DWindow2::OnSetFocus) 
EVT_KILL_FOCUS(tc3DWindow2::OnKillFocus) 
EVT_CLOSE(tc3DWindow2::OnClose)
EVT_MOUSE_CAPTURE_LOST(tc3DWindow2::OnMouseCaptureLost)
END_EVENT_TABLE()

tcTVEngine* tc3DWindow2::engine = 0;
bool tc3DWindow2::drawingToRenderSurface = false;
std::string tc3DWindow2::imagePath = "images\\";

boost::shared_ptr<tcFont> tc3DWindow2::defaultFont;
boost::shared_ptr<tcFont> tc3DWindow2::monospacedFont;
boost::shared_ptr<tcFont> tc3DWindow2::boldFont;
boost::shared_ptr<tcFont> tc3DWindow2::italicFont;

/**
* This override along with use of Freeze() Thaw() prevents 
* the flicker that happens when the window background is erased 
* by wxWindows.
*/
//long tc3DWindow2::MSWWindowProc(WXUINT nMsg, WXWPARAM wParam, WXLPARAM lParam)
//{
//    switch (nMsg)
//    {        
//    case WM_ERASEBKGND:
//        return 0;
//        break;
//    default:
//        return wxWindow::MSWWindowProc(nMsg, wParam, lParam);
//        break;
//    }
//}


void tc3DWindow2::OnChar(wxKeyEvent& event)
{
    event.Skip();
    if (charPropagationLevel > 0)
    {
        event.ResumePropagation(charPropagationLevel);
    }
}

void tc3DWindow2::OnClose(wxCloseEvent& event)
{
    event.Skip();
}

void tc3DWindow2::OnEnterWindow(wxMouseEvent& event)
{
    SetFocus();
}

/**
* Do nothing for EraseBackground event.
*/
void tc3DWindow2::OnEraseBackground(wxEraseEvent& event)
{
    //SetBackgroundColour(*wxBLACK);
    //fprintf(stdout, "Erase [%s]\n",GetName());
	return;
}

void tc3DWindow2::OnNcPaint(wxNcPaintEvent& event)
{
	wxPaintDC dc(this);
}

/**
* Do nothing for OnPaint event.
*/
void tc3DWindow2::OnPaint(wxPaintEvent& event)
{
    wxPaintDC dc(this);
    //fprintf(stdout, "Paint [%s]\n",GetName());
}

/**
* Do nothing for show event.
*/
void tc3DWindow2::OnShow(wxShowEvent& event)
{
    return;
}

void tc3DWindow2::OnKeyDown(wxKeyEvent& event)
{
    event.Skip();
}

void tc3DWindow2::OnLButtonDown(wxMouseEvent& event)
{
    SkipMouseEvent(event);
}

void tc3DWindow2::OnLButtonDClick(wxMouseEvent& event)
{
    SkipMouseEvent(event);
}

void tc3DWindow2::OnLButtonUp(wxMouseEvent& event)
{
    SkipMouseEvent(event);
}

void tc3DWindow2::OnLeaveWindow(wxMouseEvent& event)
{
	event.Skip();
    if (leaveWindowPropagationLevel > 0)
    {
        event.ResumePropagation(leaveWindowPropagationLevel);
    }
}

void tc3DWindow2::OnMButtonDown(wxMouseEvent& event)
{
	SkipMouseEvent(event);
}

void tc3DWindow2::OnMButtonUp(wxMouseEvent& event)
{
	SkipMouseEvent(event);
}

void tc3DWindow2::OnMouseCaptureLost(wxMouseCaptureLostEvent& event)
{
    
}

void tc3DWindow2::OnMouseMove(wxMouseEvent& event)
{
    SkipMouseEvent(event);
}

void tc3DWindow2::OnMouseWheel(wxMouseEvent& event)
{
    SkipMouseEvent(event);
}



void tc3DWindow2::OnMove(wxMoveEvent& event)
{

    wxPoint pos = event.GetPosition();
	wxSize size = wxWindow::GetSize();

	UpdatePositionAndSize(pos, size);
}

void tc3DWindow2::OnRButtonDown(wxMouseEvent& event)
{
    SkipMouseEvent(event);
}

void tc3DWindow2::OnSetFocus(wxFocusEvent& event)
{
}

void tc3DWindow2::OnKillFocus(wxFocusEvent& event)
{
}

void tc3DWindow2::OnSize(wxSizeEvent& event)
{
    wxSize size = event.GetSize();
    wxPoint pos = wxWindow::GetPosition();

   	UpdatePositionAndSize(pos, size);
}

void tc3DWindow2::SetCharPropagationLevel(int n)
{
    charPropagationLevel = n;
}

void tc3DWindow2::SetLeaveWindowPropagationLevel(int n)
{
    leaveWindowPropagationLevel = n;
}

void tc3DWindow2::UpdateOrigin(tcPoint& p) const
{
    p.x += (float)mrectWindow.x;
    p.y += (float)mrectWindow.y;
    
    if (hostParent != 0)
    {
        hostParent->UpdateOrigin(p);
    }
}

/**
* @returns origin for drawing
*/
const tcPoint& tc3DWindow2::GetOrigin() const
{
    return origin;
}

void tc3DWindow2::GetOrigin(float& dx, float& dy) const
{
    dx = origin.x;
    dy = origin.y;
}




/**
* Call after move or size event
*/
void tc3DWindow2::UpdatePositionAndSize(const wxPoint& pos, const wxSize& size)
{
	bool sizeChanged = (size.GetWidth() != mnWidth) || (size.GetHeight() != mnHeight);
	mnWidth = size.GetWidth();
    mnHeight = size.GetHeight();


    tcPoint parentOrigin(0, 0);
	int yOffset = 0;
	if (wxWindow* parent = wxWindow::GetParent())
	{
		wxSize parentSize = parent->GetSize();
		yOffset = parentSize.GetHeight() - 2*pos.y - mnHeight;

        wxPoint parentPos = parent->GetPosition();
        parentOrigin.x = (float)parentPos.x;
        parentOrigin.y = (float)parentPos.y;
	}


    mrectWindow.x = pos.x;
	mrectWindow.width = size.GetWidth();
    mrectWindow.y = pos.y;
	mrectWindow.height = size.GetHeight();



	//transform->setMatrix(osg::Matrix::translate(pos.x, pos.y + yOffset, 0)); 

	if (sizeChanged)
	{
		UpdateBackgroundShape();
        if (useRenderSurface)
        {
            SetUseRenderSurface(false);
            SetUseRenderSurface(true); // recreate render surface for new size
        }
	}
}

/**
* Adds child window to children vector. This
* allows drawing of children windows through
* DrawChildren() method.
*/
void tc3DWindow2::AddChild(tc3DWindow2* child)
{
    wxASSERT(child);
    if (child == NULL) return;
    children.push_back(child);
}



/**
* Removes child window from children vector by adding
* to childrenToRemove queue for safe removal at the
* start of the next DrawChildren.
*/
void tc3DWindow2::RemoveChild(tc3DWindow2* child)
{
    wxASSERT(child);
    if (child == NULL) return;
    
    childrenToRemove.push(child);
}

/**
* Removes pending children for removal from children vector. 
*/
void tc3DWindow2::UpdateChildren()
{
    /* for each child in the childrenToRemove queue
    ** iterate through children vector and remove if
    ** found */
    while (!childrenToRemove.empty())
    {
        tc3DWindow2* child = childrenToRemove.front();
        childrenToRemove.pop();

        wxASSERT(child);
        if (child == NULL) return;
        std::vector<tc3DWindow2*>::iterator iter = children.begin();
        for (iter = children.begin(); iter != children.end(); )
        {
            if ((*iter) == child)
            {
                iter = children.erase(iter);
            }
			else
			{
				++iter;
			}
        }
    }
    
}

/**
* Creates new drawing projection and adds it to the root node of 
* the scene graph.
* New owner should remove the projection from the scenegraph if
* it is destroyed before this window.
* The default projection is the same size as the window.
*
* This method should eventually be generalized so that tc3DViewer
* and tc3DWindow2 use the same system for child windows. Possibly
* both can derive from the same 3D window class.
*
* @return projection that was just created
*/
//osg::MatrixTransform* tc3DWindow2::CreateDrawTransform()
//{
//	osg::MatrixTransform* childTransform = new osg::MatrixTransform; 
//	childTransform->setDataVariance(osg::Object::DYNAMIC);
//	//transform->addChild(childTransform);
//	switchNode->addChild(childTransform);
//	return childTransform;
//}



/**
* Called at window creation or after window size change to update quad boundaries
*/
void tc3DWindow2::UpdateBackgroundQuad()
{
#if 0
	if (!backgroundQuad.valid())
	{
		backgroundQuad = new tcGeometry;
	}

	osg::Vec3Array* vertices = new osg::Vec3Array(4);
	(*vertices)[0] = osg::Vec3(0, mnHeight, 0);
	(*vertices)[1] = osg::Vec3(0, 0, 0);
	(*vertices)[2] = osg::Vec3(mnWidth, 0, 0);
	(*vertices)[3] = osg::Vec3(mnWidth, mnHeight, 0);

	backgroundQuad->setVertexArray(vertices);

	osg::Vec2Array* texcoords = new osg::Vec2Array(4);
	(*texcoords)[0].set(0.0f,1.0f);
	(*texcoords)[1].set(0.0f,0.0f);
	(*texcoords)[2].set(1.0f,0.0f);
	(*texcoords)[3].set(1.0f,1.0f);
	backgroundQuad->setTexCoordArray(0,texcoords);

	osg::Vec4Array* colors = new osg::Vec4Array;
	colors->push_back(backgroundColor); 
	backgroundQuad->setColorArray(colors);
	backgroundQuad->setColorBinding(tcGeometry::BIND_OVERALL);

	/*
	osg::Vec3Array* normals = new osg::Vec3Array(1);
	(*normals)[0].set(1.0f, 0.0f, 0.0f);
	backgroundQuad->setNormalArray(normals);
	backgroundQuad->setNormalBinding(tcGeometry::BIND_OVERALL);
	*/

	backgroundQuad->addPrimitiveSet(new osg::DrawArrays(GL_QUADS,0,4));

	/*
	osg::StateSet* stateSet = backgroundQuad->getOrCreateStateSet();

	stateSet->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF);
	stateSet->setMode(GL_DEPTH_WRITEMASK, osg::StateAttribute::OFF);
	stateSet->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	//stateSet->setMode(GL_BLEND, osg::StateAttribute::OFF);
	stateSet->setRenderBinDetails(baseRenderBin + backgroundRenderBin, "RenderBin");
	*/

	/*
	osg::Depth* depth = new osg::Depth(osg::Depth::ALWAYS, 1, 1, false);
	depth->setWriteMask(0);
	stateSet->setAttribute(depth);
	*/
#endif
}


/**
* Version to create rounded background quads
* Create background polygon and border graphics based on cornerRadius value.
* cornerRadius = 0 is square corners (no rounding)
*/
void tc3DWindow2::UpdateBackgroundShape()
{
	//wxASSERT(!backgroundQuad.valid());
	
	if (cornerRadius == 0)
	{
		UpdateBackgroundQuad();
		return;
	}
#if 0
	if (!backgroundQuad.valid())
	{
		backgroundQuad = new tcGeometry;
	}

	if (!border.valid())
	{
		border = new tcGeometry;
	}

	osg::Vec3Array* vertices = new osg::Vec3Array;
	osg::Vec2Array* texcoords = new osg::Vec2Array;
	osg::Vec3Array* borderVertices = new osg::Vec3Array;

	float width = float(mnWidth);
	float height = float(mnHeight);
	float inv_width = 1.0f / width;
	float inv_height = 1.0f / height;
	float xc = 0.5 * width;
	float yc = 0.5 * height;


	int nAngles = 4; // number of points for rounded corner
	float dangle = C_PIOVER2 / float(nAngles);

	float x, y, xp, yp;
	float xcorner, ycorner; // center point for corner arc
	float angle;


	// add top section

	x = width - cornerRadius;
	y = height;
	vertices->push_back(osg::Vec3(x, y, 0));
	borderVertices->push_back(osg::Vec3(x, y, 0));
	texcoords->push_back(osg::Vec2(inv_width * x, inv_height * y));

	x = cornerRadius;
	y = height;
	vertices->push_back(osg::Vec3(x, y, 0));
	borderVertices->push_back(osg::Vec3(x, y, 0));
	texcoords->push_back(osg::Vec2(inv_width * x, inv_height * y));

	vertices->push_back(osg::Vec3(xc, yc, 0));
	//texcoords->push_back(osg::Vec2(inv_width * xc, inv_height * yc));
	texcoords->push_back(osg::Vec2(0.5f, 0.5f));



	

	
	// add top left corner
	xp = x;
	yp = y;
	xcorner = cornerRadius;
	ycorner = height - cornerRadius;

	angle = -dangle;
	for (int k=0; k<nAngles; k++)
	{
		x = xcorner + cornerRadius * sinf(angle);
		y = ycorner + cornerRadius * cosf(angle);

		vertices->push_back(osg::Vec3(xp, yp, 0));
		borderVertices->push_back(osg::Vec3(xp, yp, 0));
		texcoords->push_back(osg::Vec2(inv_width * xp, inv_height * yp));
		
		vertices->push_back(osg::Vec3(x, y, 0));
		borderVertices->push_back(osg::Vec3(x, y, 0));
		texcoords->push_back(osg::Vec2(inv_width * x, inv_height * y));

		vertices->push_back(osg::Vec3(xc, yc, 0));
		texcoords->push_back(osg::Vec2(inv_width * xc, inv_height * yc));

		xp = x;
		yp = y;
		angle -= dangle;
	}
	

	// add left section
	vertices->push_back(osg::Vec3(x, y, 0));
	borderVertices->push_back(osg::Vec3(x, y, 0));
	texcoords->push_back(osg::Vec2(inv_width * x, inv_height * y));

	x = 0;
	y = cornerRadius;
	vertices->push_back(osg::Vec3(x, y, 0));
	borderVertices->push_back(osg::Vec3(x, y, 0));
	texcoords->push_back(osg::Vec2(inv_width * x, inv_height * y));

	vertices->push_back(osg::Vec3(xc, yc, 0));
	texcoords->push_back(osg::Vec2(inv_width * xc, inv_height * yc));

	// add lower left corner
	xp = x;
	yp = y;
	xcorner = cornerRadius;
	ycorner = cornerRadius;

	angle = -(C_PIOVER2 + dangle);
	for (int k=0; k<nAngles; k++)
	{
		x = xcorner + cornerRadius * sinf(angle);
		y = ycorner + cornerRadius * cosf(angle);

		vertices->push_back(osg::Vec3(xp, yp, 0));
		borderVertices->push_back(osg::Vec3(xp, yp, 0));
		texcoords->push_back(osg::Vec2(inv_width * xp, inv_height * yp));

		vertices->push_back(osg::Vec3(x, y, 0));
		borderVertices->push_back(osg::Vec3(x, y, 0));
		texcoords->push_back(osg::Vec2(inv_width * x, inv_height * y));		
		
		vertices->push_back(osg::Vec3(xc, yc, 0));
		texcoords->push_back(osg::Vec2(inv_width * xc, inv_height * yc));

		xp = x;
		yp = y;
		angle -= dangle;
	}

	// add bottom section
	vertices->push_back(osg::Vec3(x, y, 0));
	borderVertices->push_back(osg::Vec3(x, y, 0));
	texcoords->push_back(osg::Vec2(inv_width * x, inv_height * y));

	x = width - cornerRadius;
	y = 0;
	vertices->push_back(osg::Vec3(x, y, 0));
	borderVertices->push_back(osg::Vec3(x, y, 0));
	texcoords->push_back(osg::Vec2(inv_width * x, inv_height * y));

	vertices->push_back(osg::Vec3(xc, yc, 0));
	texcoords->push_back(osg::Vec2(inv_width * xc, inv_height * yc));

	// add bottom right corner
	xp = x;
	yp = y;
	xcorner = width - cornerRadius;
	ycorner = cornerRadius;

	angle = C_PI - dangle;
	for (int k=0; k<nAngles; k++)
	{
		x = xcorner + cornerRadius * sinf(angle);
		y = ycorner + cornerRadius * cosf(angle);

		vertices->push_back(osg::Vec3(xp, yp, 0));
		borderVertices->push_back(osg::Vec3(xp, yp, 0));
		texcoords->push_back(osg::Vec2(inv_width * xp, inv_height * yp));

		vertices->push_back(osg::Vec3(x, y, 0));
		borderVertices->push_back(osg::Vec3(x, y, 0));
		texcoords->push_back(osg::Vec2(inv_width * x, inv_height * y));

		vertices->push_back(osg::Vec3(xc, yc, 0));
		texcoords->push_back(osg::Vec2(inv_width * xc, inv_height * yc));

		xp = x;
		yp = y;
		angle -= dangle;
	}

	// add right section
	vertices->push_back(osg::Vec3(x, y, 0));
	borderVertices->push_back(osg::Vec3(x, y, 0));
	texcoords->push_back(osg::Vec2(inv_width * x, inv_height * y));

	x = width;
	y = height - cornerRadius;
	vertices->push_back(osg::Vec3(x, y, 0));
	borderVertices->push_back(osg::Vec3(x, y, 0));
	texcoords->push_back(osg::Vec2(inv_width * x, inv_height * y));

	vertices->push_back(osg::Vec3(xc, yc, 0));
	texcoords->push_back(osg::Vec2(inv_width * xc, inv_height * yc));

	// add top right corner
	xp = x;
	yp = y;
	xcorner = width - cornerRadius;
	ycorner = height - cornerRadius;

	angle = C_PIOVER2 - dangle;
	for (int k=0; k<nAngles; k++)
	{
		x = xcorner + cornerRadius * sinf(angle);
		y = ycorner + cornerRadius * cosf(angle);

		vertices->push_back(osg::Vec3(xp, yp, 0));
		borderVertices->push_back(osg::Vec3(xp, yp, 0));
		texcoords->push_back(osg::Vec2(inv_width * xp, inv_height * yp));

		vertices->push_back(osg::Vec3(x, y, 0));
		borderVertices->push_back(osg::Vec3(x, y, 0));
		texcoords->push_back(osg::Vec2(inv_width * x, inv_height * y));

		vertices->push_back(osg::Vec3(xc, yc, 0));
		texcoords->push_back(osg::Vec2(inv_width * xc, inv_height * yc));

		xp = x;
		yp = y;
		angle -= dangle;
	}

	
	backgroundQuad->setVertexArray(vertices);
	backgroundQuad->setTexCoordArray(0, texcoords);

	osg::Vec4Array* colors = new osg::Vec4Array;
	colors->push_back(Vec4(1.0f, 1.0f, 1.0f, 1.0f)); 
	backgroundQuad->setColorArray(colors);
	backgroundQuad->setColorBinding(tcGeometry::BIND_OVERALL);

	backgroundQuad->addPrimitiveSet(new osg::DrawArrays(GL_TRIANGLES,0,vertices->size()));

	border->setVertexArray(borderVertices);
	osg::Vec4Array* borderColors = new osg::Vec4Array;
	borderColors->push_back(Vec4(1.0f, 1.0f, 1.0f, 1.0f)); 
	border->setColorArray(borderColors);
	border->setColorBinding(tcGeometry::BIND_OVERALL);

	border->addPrimitiveSet(new osg::DrawArrays(GL_LINES, 0, borderVertices->size()));


	/*
	osg::StateSet* stateSet = backgroundQuad->getOrCreateStateSet();
	stateSet->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF);
	stateSet->setMode(GL_DEPTH_WRITEMASK, osg::StateAttribute::OFF);
	stateSet->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	//stateSet->setMode(GL_BLEND, osg::StateAttribute::OFF);
	stateSet->setRenderBinDetails(baseRenderBin + backgroundRenderBin, "RenderBin");
	*/

	/*
	osg::Depth* depth = new osg::Depth(osg::Depth::ALWAYS, 1, 1, false);
	depth->setWriteMask(0);
	stateSet->setAttribute(depth);
	*/
#endif
}

void tc3DWindow2::SetImagePath(const std::string& s)
{
	imagePath = s;
}

/** 
* @return wxString with IMAGE_PATH prepended to <fileName>
*/
wxString tc3DWindow2::PrependImagePath(const char* fileName) 
{
	wxString s = wxString::Format("%s%s", imagePath.c_str(), fileName);

	return s;
}

/**
* Converts relative coordinates to screen coordinates
*/
wxRealPoint tc3DWindow2::RelativeToScreen(float x, float y)
{
	wxRealPoint p;

	p.x = x * float(mnWidth);
	p.y = (1-y) * float(mnHeight);

	return p;
}

void tc3DWindow2::ReleaseMouse()
{
	if (wxWindow::HasCapture())
	{
		wxWindow::ReleaseMouse();
	}
	else
	{
		//wxASSERT(false); // doesn't have capture
	}
}


/**
* wxWindows (or MS Windows behind it) erases window region
* when the window is moved or Show() is used. This causes
* a flickering effect. Enable() is used to activate/deactivate 
* GUI inputs for the window.
*/
void tc3DWindow2::SetActive(bool abActive) 
{
	if (abActive && mbActive) return; // don't repeat activate (but repeat deactivate)

    UpdateChildren(); // complete pending removes before accessing children

    size_t nChildren = children.size();
    for(size_t n=0;n<nChildren;n++)
    {
        children[n]->SetActive(abActive);
		//children[n]->SetBaseRenderBin(baseRenderBin + 30);
    }

	if (mbActive == abActive) return; 

    if (abActive)
    {
        if (!wxWindow::IsShown())
        {
            wxWindow::Show(TRUE);
        }
        wxWindow::Enable(true);

		//switchNode->setAllChildrenOn();
    }
    else
    {
        wxWindow::Enable(false);

		//switchNode->setAllChildrenOff();
    }

    mbActive = abActive;

}

/**
* Sets color of background quad
*/
void tc3DWindow2::SetBackgroundColor(const Vec4& color)
{
    backgroundColor = color;

    SetBackgroundDraw(true);

    UpdateBackgroundQuad();
}

/**
* @param state true to enable background drawing, false to disable
*/
void tc3DWindow2::SetBackgroundDraw(bool state)
{
	if (state == IsBackgroundEnabled()) return; // already set to state
	
    drawBackground = state;
	
    UpdateBackgroundQuad();
}


void tc3DWindow2::SetBorderColor(const Vec4& color)
{
    borderColor = color;

    SetBorderDraw(true);
}

void tc3DWindow2::SetBorderDraw(bool state)
{
    drawBorder = state;
}


/**
* Adjusts wxMouseEvent position to parent's frame.
* Calls Skip() on event.
*/
void tc3DWindow2::SkipMouseEvent(wxMouseEvent& event)
{
    wxPoint pos = wxWindow::GetPosition();
    event.m_x += pos.x;
    event.m_y += pos.y;
    event.Skip();
}


void tc3DWindow2::StartDraw()
{
    wxASSERT(!drawStarted);

    drawStarted = true;

    queuedText.clear();

    CTVScreen2DImmediate* screen2D = engine->GetScreen2D();
    screen2D->Action_Begin2D();

    origin.x = 0;
    origin.y = 0;
    if (!useRenderSurface) UpdateOrigin(origin);

    DrawBackground();
}


/**
* Creates default tcGeometry object
*/
boost::shared_ptr<tcGeometry> tc3DWindow2::CreateDefaultGeometry()
{
    boost::shared_ptr<tcGeometry> temp;
    return temp;
	//tcGeometry* symbol = new tcGeometry;

	//symbol->setUseDisplayList(true);

	//// set state
	//osg::StateSet* stateSet = symbol->getOrCreateStateSet();
	//stateSet->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF);
	//stateSet->setMode(GL_DEPTH_WRITEMASK, osg::StateAttribute::OFF);
	//stateSet->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	//stateSet->setMode(GL_BLEND, osg::StateAttribute::ON);
	//stateSet->setRenderBinDetails(baseRenderBin + rectRenderBin, "RenderBin");

	//return symbol;
}

/**
* Angle of zero is up, angle increases in clockwise direction
* startAngle must be less than stopAngle (can use negative angles)
* @param startAngle in degrees
* @param stopAngle in degrees
*/
boost::shared_ptr<tcGeometry> tc3DWindow2::CreatePieGeometry(float width, float height, float startAngle, float stopAngle, 
											 Vec4& color, int fillMode)
{
//	unsigned int nArcPoints = 48;
//	wxASSERT(nArcPoints > 1);

	wxASSERT(startAngle < stopAngle);

    boost::shared_ptr<tcGeometry> geometry(new tcGeometry());
    geometry->MakePie(width, height, startAngle, stopAngle, color, fillMode != 0);

    return geometry;

#if 0
	tcGeometry* symbol = CreateDefaultGeometry();

	// set color
	osg::Vec4Array* colors = new osg::Vec4Array;
	colors->push_back(color);
	symbol->setColorArray(colors);
	symbol->setColorBinding(tcGeometry::BIND_OVERALL);

	// create vertex array
	osg::Vec3Array* vertices = new osg::Vec3Array;
	symbol->setVertexArray(vertices);

	bool fullCircle = ((stopAngle - startAngle) >= 359.9f);

	startAngle *= C_PIOVER180;
	stopAngle *= C_PIOVER180;

	float deltaAngle = (stopAngle - startAngle) / float(nArcPoints-1);
	float half_width = 0.5f * width;
	float half_height = 0.5f * height;
	float xc = 0;
	float yc = 0;

	float angle = stopAngle;

	// add center point if not full circle
	if (!fullCircle)
	{
		vertices->push_back(osg::Vec3(xc, yc, 0));
	}

	for (unsigned int n = 0; n < nArcPoints; n++)
	{
		float x = xc + half_width * sinf(angle);
		float y = yc + half_height * cosf(angle);

		vertices->push_back(osg::Vec3(x, y, 0));
		angle -= deltaAngle;
	}

	unsigned int nPoints = vertices->size();


	if (fillMode == FILL_OFF)
	{
		symbol->addPrimitiveSet(new osg::DrawArrays(GL_LINE_LOOP, 0, nPoints));
	}
	else
	{
		symbol->addPrimitiveSet(new osg::DrawArrays(GL_TRIANGLE_FAN, 0, nPoints));
	}

	return symbol;
#endif
}

/**
* Create quad, textured with image specified by <symbolname>
*/
boost::shared_ptr<tcGeometry> tc3DWindow2::CreateTexturedSymbol(const char* imageName, float width)
{
//    float w = 0.5f * width;

    tcGeometry* symbol = new tcGeometry();
    symbol->MakeTexturedSymbol(LoadTexture(imageName), width);

    return boost::shared_ptr<tcGeometry>(symbol);

#if 0
	tcGeometry* symbol = new tcGeometry;

	osg::Vec4Array* colors = new osg::Vec4Array;
	colors->push_back(Vec4(1.0f, 1.0f, 1.0f, 1.0f));
	symbol->setColorArray(colors);
	symbol->setColorBinding(tcGeometry::BIND_OVERALL);

	symbol->setUseDisplayList(true);

	// set state
	osg::StateSet* stateSet = symbol->getOrCreateStateSet();
	stateSet->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF);
	stateSet->setMode(GL_DEPTH_WRITEMASK, osg::StateAttribute::OFF);
	stateSet->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	stateSet->setMode(GL_BLEND, osg::StateAttribute::ON);
	//stateSet->setRenderBinDetails(baseRenderBin + rectRenderBin, "RenderBin");



	// set color
	/*
	osg::Vec4Array* colors = new osg::Vec4Array;
    colors->push_back(Vec4(0.5, 0.5, 1.0, 0.5));
	symbol->setColorArray(colors);
    symbol->setColorBinding(tcGeometry::BIND_OVERALL);
    */
	

	// create vertex array
	osg::Vec3Array* vertices = new osg::Vec3Array;
	symbol->setVertexArray(vertices);

	vertices->push_back(osg::Vec3(-w, w, 0));
	vertices->push_back(osg::Vec3(-w, -w, 0));
	vertices->push_back(osg::Vec3(w, -w, 0));
	vertices->push_back(osg::Vec3(w, w, 0));

	// create texture coordinates
	osg::Vec2Array* texcoords = new osg::Vec2Array(4);
	(*texcoords)[0].set(0.0f, 1.0f);
	(*texcoords)[1].set(0.0f, 0.0f);
	(*texcoords)[2].set(1.0f, 0.0f);
	(*texcoords)[3].set(1.0f, 1.0f);
	symbol->setTexCoordArray(0,texcoords);

	symbol->addPrimitiveSet(new osg::DrawArrays(GL_QUADS,0,4));

	// add texture
	osg::Image* image = LoadImage(imageName);

	tcTexture2D* texture = new tcTexture2D;
	texture->setDataVariance(osg::Object::STATIC);
    texture->setImage(image);

	osg::StateSet* stateset = symbol->getOrCreateStateSet();
    stateset->setTextureAttributeAndModes(0, texture, 
		osg::StateAttribute::ON);

	return symbol;
#endif
}

/**
* Use this method to safely destroy the windw
*/
void tc3DWindow2::DestroyWindow()
{
	destroy = true;
}


/**
*
*/
void tc3DWindow2::Draw() 
{
    StartDraw();

	FinishDraw();    
}

/**
* Window will automatically draw to a render surface
* if this mode has been selected. Otherwise it does nothing.
*/
void tc3DWindow2::DrawToRenderSurface()
{
    drawingToRenderSurface = true;

    if (FinishDestroy())
    {
        return; // automatically destroys children?
    }

    if (!IsActive()) return;

    UpdateChildren();

    if (useRenderSurface)
    {
        rsUpdateCount++;
        if ((rsUpdateCount - rsLastUpdateCount) >= rsUpdateInterval)
        {
            rsLastUpdateCount = rsUpdateCount;

	        renderSurface->StartRender(false);

            Draw();
	    
            renderSurface->EndRender();
        }
    }

    DrawChildren();
}

void tc3DWindow2::DrawToScreen()
{
    drawingToRenderSurface = false;

    if (FinishDestroy())
    {
        return;
    }

    if (!IsActive()) return;

    std::string winName(GetName().c_str());

    if (!useRenderSurface)
    {
        Draw();
    }
    else
    {
        tcPoint p(0, 0);
        UpdateOrigin(p);

        if (hostParent != 0)
        {
            //hostParent->UpdateOrigin(p);
        }

        CTVScreen2DImmediate* screen2D = engine->GetScreen2D();
        screen2D->Action_Begin2D();

        wxASSERT(renderSurface != 0);
        long texId = renderSurface->GetTexture();

		float dx, dy;
		GetOrigin(dx, dy);
		const float h = float(mnHeight);
		const float width = float(mnWidth-renderSurfaceMargin);

		// DrawImageR( p.x, p.y, float(mnWidth-renderSurfaceMargin), float(mnHeight));
		// DrawImage(texture, x, h - y - height, width, height, alignMode);
		// screen2D->Draw_Texture(texture->GetId(), dx+x, dy+h - y - height, dx+x+width, dy+h - y);

		// screen2D->Draw_Texture(texId, dx+p.x, dy+p.y , dx+p.x+width, dy+p.y+h);


		// for cards that don't  support non-=power-of-two texture sizes,
		// draw only the part of the rendersurface that corresponds to the window size
		int rsWidth = renderSurface->GetWidth();
		int rsHeight = renderSurface->GetHeight();		
		float tu2 = 0;
		float tv2 = 0;

		if ((rsWidth == mnWidth) && (rsHeight == mnHeight))
		{
			tu2 = 1.0;
			tv2 = 1.0;
		}
		else
		{
			tu2 = width / float(renderSurface->GetWidth());
			tv2 = h / float(renderSurface->GetHeight());
		}

		screen2D->Draw_Texture(texId, dx+p.x, dy+p.y , dx+p.x+width-1.0f, dy+p.y+h-1.0f,
			-1, -2, -2, -2,
			0, 0, tu2, tv2);

        screen2D->Action_End2D();

    }

    DrawChildren();
}


/**
* Call Draw() method for all children
*/
void tc3DWindow2::DrawChildren()
{
    UpdateChildren();

    size_t nChildren = children.size();

    for(size_t n=0;n<nChildren;n++)
    {
		tc3DWindow2* child = children[n];
        wxASSERT(child);
        
		if (child->IsActive())
        {
            if (!drawingToRenderSurface)
            {
                child->DrawToScreen();
            }
            else
            {
                child->DrawToRenderSurface();
            }
        }
    }
}

void tc3DWindow2::DrawBackground()
{
    if (drawBackground)
    {
        if (backgroundTexture.get() != 0)
        {
            DrawImage(backgroundTexture.get(), 0, 0, float(mnWidth), float(mnHeight));
        }
        else
        {
            DrawRectangle(0, 0, float(mnWidth), float(mnHeight), backgroundColor, FILL_ON);
        }
    }
}

/**
* Draw a border 
*/
void tc3DWindow2::DrawBorder() 
{
    if (drawBorder)
    {
        DrawLine(0, 1, 0, mnHeight, borderColor); // left
        DrawLine(0, mnHeight, mnWidth-1, mnHeight, borderColor); // top
        DrawLine(mnWidth-1, 1, mnWidth-1, mnHeight, borderColor); // right
        DrawLine(0, 1, mnWidth-1, 1, borderColor); // bottom
    }

#if 0
	if (cornerRadius == 0)
	{
		Vec4 white(1.0f, 1.0f, 1.0f, 0.7f);

		DrawLine(0, 0, 0, mnHeight, white); // left
		DrawLine(0, mnHeight-1, mnWidth, mnHeight-1, white); // top
		DrawLine(mnWidth-1, 0, mnWidth-1, mnHeight, white); // right
		DrawLine(0, 0, mnWidth, 0, white); // bottom
	}
	else
	{
		wxASSERT(border.valid());
		DrawGeometry(border.get(), 0, 0);
	}
#endif
}

/**
* Draws image using textured quad
* @param x center x coord
* @param y center y coord
* @param alignMode CENTER (default) or ALIGN_BOTTOM_LEFT
*/
void tc3DWindow2::DrawImage(tcTexture2D* texture, float x, float y, 
						   float width, float height, int alignMode)
{
	wxASSERT(texture);
	if (!texture) return;

    float dx, dy;
    GetOrigin(dx, dy);

    const float h = float(mnHeight);
    CTVScreen2DImmediate* screen2D = engine->GetScreen2D();
    screen2D->Draw_Texture(texture->GetId(), dx+x, dy+h - y - height, dx+x+width, dy+h - y);
}

/**
* Draws image using textured quad
* @param x center x coord
* @param y center y coord
* @param color color vector to fade or alter image color
* @param alignMode CENTER (default) or ALIGN_BOTTOM_LEFT
*/
void tc3DWindow2::DrawImageColored(tcTexture2D* texture, float x, float y, 
						   float width, float height, const Vec4& color, int alignMode)
{
	wxASSERT(texture);
	if (!texture) return;

    int nColor = RGBA(color.x, color.y, color.z, color.w);

    float dx, dy;
    GetOrigin(dx, dy);

    const float h = float(mnHeight);
    CTVScreen2DImmediate* screen2D = engine->GetScreen2D();
    screen2D->Draw_Texture(texture->GetId(), dx+x, dy+h - y - height, dx+x+width, dy+h - y, nColor, nColor, nColor, nColor);
}


/**
*
*/
void tc3DWindow2::DrawLine(float x1, float y1, float x2, float y2, const Vec4& color)
{
    float& dx = origin.x;
    float& dy = origin.y;

    const float h = float(mnHeight);
    CTVScreen2DImmediate* screen2D = engine->GetScreen2D();

    screen2D->Draw_Line(dx+x1, dy+h - y1, dx+x2, dy+h - y2, RGBA(color.x, color.y, color.z, color.w));


#if 0
	tcGeometry* line = GetLineObject();
	wxASSERT(line);

    if (osg::Vec4Array* colors = dynamic_cast<osg::Vec4Array*>(line->getColorArray()))
	{
		colors->clear();
		colors->push_back(color);
	}
	else
	{
		wxASSERT(0);
	}
	
	if (osg::Vec3Array* vertices = dynamic_cast<osg::Vec3Array*>(line->getVertexArray()))
	{
		(*vertices)[0] = osg::Vec3(x1, y1, 0);
		(*vertices)[1] = osg::Vec3(x2, y2, 0);
	}
	else
	{
		fprintf(stderr, "tc3DWindow2::DrawLine - corrupt vertex array\n");
		wxASSERT(0);
	}	
#endif

}

/**
* @param fill FILL_ON to fill rectangle with solid color, FILL_OFF for outline only
*/
void tc3DWindow2::DrawRectangle(const tcRect& rect, const Vec4& color,
							   int fill)
{
	float x1 = rect.left;
	float y1 = rect.bottom;
	float width = rect.Width();
	float height = rect.Height();

	DrawRectangle(x1, y1, width, height, color, fill);
}

/**
* @param w half-width of line thickness
*/
void tc3DWindow2::DrawThickRectangle(const tcRect& rect, float w, const Vec4& color)
{
	float x1 = rect.left;
	float y1 = rect.bottom;
	float width = rect.Width();
	float height = rect.Height();

	DrawThickRectangle(x1, y1, width, height, w, color);
}

/**
* @param w half-width of line thickness
*/
void tc3DWindow2::DrawThickRectangle(float x1, float y1, float width, float height, float w, const Vec4& color)
{
    float x2 = x1 + width;
    float y2 = y1 + height;

    wxASSERT(x2 >= x1);
    wxASSERT(y2 >= y1);

    float x1b = x1 - w;
    float x2b = x2 + w;
    float y1b = y1 + w;
    float y2b = y2 - w;

    DrawThickLine(x1b, y1, x2b, y1, w, color);
    DrawThickLine(x1b, y2, x2b, y2, w, color);
    DrawThickLine(x1, y1b, x1, y2b, w, color);
    DrawThickLine(x2, y1b, x2, y2b, w, color);
}

/**
* @param w half-width of line thickness
*/
void tc3DWindow2::DrawThickRectangleR(const tcRect& rect, float w, const Vec4& color)
{
	const float h = float(mnHeight);

	tcRect rectFlip = rect;
	rectFlip.bottom = h - rectFlip.top;
	float height = rect.Height();
	rectFlip.top = rectFlip.bottom + height;

	DrawThickRectangle(rectFlip, w, color);
}

/**
* @param w half-width of line thickness
*/
void tc3DWindow2::DrawThickRectangleR(float x1, float y1, float width, float height, float w, const Vec4& color)
{
	const float h = float(mnHeight);

	DrawThickRectangle(x1, h - y1 - height, width, height, w, color);
}


/**
* @param fill FILL_ON to fill rectangle with solid color, FILL_OFF for outline only
*/
void tc3DWindow2::DrawRectangle(float x1, float y1, float width, float height, 
						  const Vec4& color, int fill)
{
	Vec4 white(1.0f, 1.0f, 1.0f, 1.0f);

    const float h = float(mnHeight);
    
    CTVScreen2DImmediate* screen2D = engine->GetScreen2D();

    float dx, dy;
    GetOrigin(dx, dy);

    if (fill == 0)
    {
        int nColor =  RGBA(color.x, color.y, color.z, color.w);
        screen2D->Draw_Line(dx+x1, dy+h-y1, dx+x1+width, dy+h-y1, nColor, nColor);
        screen2D->Draw_Line(dx+x1, dy+h-y1-height, dx+x1+width, dy+h-y1-height, nColor, nColor);
        screen2D->Draw_Line(dx+x1, dy+h-y1, dx+x1, dy+h-y1-height, nColor, nColor);
        screen2D->Draw_Line(dx+x1+width, dy+h-y1, dx+x1+width, dy+h-y1-height, nColor, nColor);
    }
    else
    {
        screen2D->Draw_FilledBox(dx+x1, dy+h-y1, dx+x1+width, dy+h-y1-height, RGBA(color.x, color.y, color.z, color.w));
    }
 

#if 0
	tcGeometry* rect = GetRectObject();
	wxASSERT(rect);

	osg::PrimitiveSet* primitiveSet = rect->getPrimitiveSet(0);
	wxASSERT(primitiveSet);
	if (fill == FILL_ON)
	{
		primitiveSet->setMode(GL_QUADS);
	}
	else
	{
		primitiveSet->setMode(GL_LINE_LOOP);
	}

	if (osg::Vec4Array* colors = dynamic_cast<osg::Vec4Array*>(rect->getColorArray()))
	{
		colors->clear();
		colors->push_back(color);
	}
	else
	{
		wxASSERT(0);
	}

	if (osg::Vec3Array* vertices = dynamic_cast<osg::Vec3Array*>(rect->getVertexArray()))
	{
		float x2 = x1 + width;
		float y2 = y1 + height;
		(*vertices)[0] = osg::Vec3(x1, y2, 0);
		(*vertices)[1] = osg::Vec3(x1, y1, 0);
		(*vertices)[2] = osg::Vec3(x2, y1, 0);
		(*vertices)[3] = osg::Vec3(x2, y2, 0);
	}
	else
	{
		fprintf(stderr, "tc3DWindow2::DrawRectangle - corrupt vertex array\n");
		wxASSERT(0);
	}		
#endif
}


/**
* @param maximumWidth text wraps at this width, set to 0 or negative for no wrapping, 15.0 is min value
*/
void tc3DWindow2::DrawText(const char* s, float x, float y, tcFont* font, 
					   const Vec4& color, float fontSize, 
					   AlignmentType alignment, float maximumWidth)
{
	if (strlen(s) == 0) return; 
	if (strcmp(s, " ") == 0) return;

    if (font == 0)
    {
        wxASSERT(false);
        return;
    }

    const float h = float(mnHeight);

    int fontSizeInt = (int)floorf(fontSize + 0.5f);

    TextInfo t;
    t.s = s;
    t.x = floorf(x + 0.5f);
    t.y = floorf(h - y + 0.5f);
    t.rgba = RGBA(color.x, color.y, color.z, color.w);
    t.fontId = font->GetId(fontSizeInt);
    t.alignment = alignment;
    t.maximumWidth = maximumWidth;

    

    wxSize textSize;
    MeasureText(font, fontSize, s, textSize);
    
    if ((maximumWidth <= 15.0) || (textSize.x < maximumWidth))
    {
        lastTextBoundingBox.Set(0, float(textSize.x), 0, float(textSize.y));
        queuedText.push_back(t);
    }
    else
    {
        wxString ellipses("...");
        wxSize ellipsesSize;
        MeasureText(font, fontSize, ellipses.c_str(), ellipsesSize);
        float ellipsesWidth = float(ellipsesSize.x);

        wxString trimmedText = s;
        while ((textSize.x > maximumWidth-ellipsesWidth) && (trimmedText.size() > 0))
        {
            trimmedText.RemoveLast();
            MeasureText(font, fontSize, trimmedText.c_str(), textSize);
        }
        trimmedText += "...";

        t.s = trimmedText.c_str();
        lastTextBoundingBox.Set(0, float(textSize.x), 0, float(textSize.y));
        queuedText.push_back(t);
    }

#if 0
	osgText::Text* text = GetTextObject();
	wxASSERT(text);
	wxASSERT(font);

    text->setFont(font);
	text->setAlignment(alignment);
    text->setColor(color);
    text->setCharacterSize(fontSize, 1.2f); // font height, aspect ratio
    text->setPosition(osg::Vec3(x, y, 0));
	text->setMaximumWidth(maximumWidth);
	text->setText(s);

	lastTextBoundingBox = text->getBound();
#endif

}


/**
* @param r set to bounding box of text (not supported yet)
*/
//void tc3DWindow2::DrawText(const char* s, float x, float y, tcFont* font, 
//						  const Vec4& color, float fontSize, AlignmentType alignment,
//						  tcRect& r)
//{
//	DrawText(s, x, y, font, color, fontSize, alignment);
//}

void tc3DWindow2::DrawTextInRect(const char* s, const tcRect& r, tcFont* font, 
								const Vec4& color, float fontSize, AlignmentType alignment)
{
	float x = (alignment == CENTER_CENTER) ? r.XCenter() : r.left + 3.0f;
	float y = (alignment == CENTER_CENTER) || (alignment == LEFT_CENTER) ? r.YCenter() : r.bottom;
	float maximumWidth = r.Width();

	DrawText(s, x, y, font, color, fontSize, alignment, maximumWidth);
}


/**
* This version draws a zoomed image on a quad, zoom rectangle specified by r
* @see tc3DWindow2::DrawImage
*/
void tc3DWindow2::DrawZoomedImage(tcTexture2D* texture, float x, float y, float width, float height,
		const tcRect& r, int alignMode)
{
	wxASSERT(texture);
	if (!texture) return;


	wxASSERT(texture);
	if (!texture) return;

    float& dx = origin.x;
    float& dy = origin.y;

    const float h = float(mnHeight);
    CTVScreen2DImmediate* screen2D = engine->GetScreen2D();
    screen2D->Draw_Texture(texture->GetId(), dx+x, dy+y, dx+x+width, dy+y+h,
        -1, -2, -2, -2,
        r.left, 1.0-r.top, r.right, 1.0-r.bottom);

#if 0

	tcGeometry* quad = GetImageQuadObject();
	wxASSERT(quad);
	wxASSERT(texture);

    // set the texture coordinates using zoom rect, r
    osg::Vec2Array* texcoords = dynamic_cast<osg::Vec2Array*>(quad->getTexCoordArray(0));
    wxASSERT(texcoords);

    float x1 = r.left;
    float x2 = r.right;
    float y1 = r.bottom;
    float y2 = r.top;

    (*texcoords)[0].set(x1, y2);
    (*texcoords)[1].set(x1, y1);
    (*texcoords)[2].set(x2, y1);
    (*texcoords)[3].set(x2, y2);



	if (osg::Vec3Array* vertices = dynamic_cast<osg::Vec3Array*>(quad->getVertexArray()))
	{
		float left, right, top, bottom;
		if (alignMode == CENTER)
		{
			const float half_width = 0.5f * width;
			const float half_height = 0.5f * height;
			left = x - half_width;
			right = x + half_width;
			top = y + half_height;
			bottom = y - half_height;
		}
		else
		{
			left = x;
			right = x + width;
			top = y + height;
			bottom = y;
		}

		(*vertices)[0] = osg::Vec3(left, top, 0);
		(*vertices)[1] = osg::Vec3(left, bottom, 0);
		(*vertices)[2] = osg::Vec3(right, bottom, 0);
		(*vertices)[3] = osg::Vec3(right, top, 0);
	}
	else
	{
		fprintf(stderr, "tc3DWindow2::DrawZoomedImage - corrupt vertex array\n");
		wxASSERT(0);
	}
    
    osg::StateSet* stateset = quad->getOrCreateStateSet();
    stateset->setTextureAttributeAndModes(0, texture, 
		osg::StateAttribute::ON);
#endif
}




/**
* This method is used for inverted y coordinate system used by wxWindows
* y = 0 is at top of screen.
*/
void tc3DWindow2::DrawImageR(tcTexture2D* texture, float x, float y, 
							float width, float height, int alignMode)
{
	const float h = float(mnHeight);

	DrawImage(texture, x, h - y - height, width, height, alignMode);

}

/**
* This method is used for inverted y coordinate system used by wxWindows
* y = 0 is at top of screen.
*/
void tc3DWindow2::DrawImageColoredR(tcTexture2D* texture, float x, float y, 
							float width, float height, const Vec4& color, int alignMode)
{
	const float h = float(mnHeight);

	DrawImageColored(texture, x, h - y - height, width, height, color, alignMode);

}

/**
* This method is used for inverted y coordinate system used by wxWindows
* y = 0 is at top of screen.
*/
void tc3DWindow2::DrawZoomedImageR(tcTexture2D* texture, float x, float y, float width, float height,
		const tcRect& r, int alignMode)
{
    const float h = float(mnHeight);

	DrawZoomedImage(texture, x, h - y - height, width, height, r, alignMode);
}


/**
* This method is used for inverted y coordinate system used by wxWindows
* y = 0 is at top of screen.
*/
void tc3DWindow2::DrawLineR(float x1, float y1, float x2, float y2, 
						   const Vec4& color)
{
	const float h = float(mnHeight);

	DrawLine(x1, h - y1, x2, h - y2, color);
}



void tc3DWindow2::DrawPieSectionR(float x, float y, float rx1, float ry1, float rx2, float ry2,
        float start_angle_rad, float stop_angle_rad, const Vec4& color, int fillMode)
{
	const float h = float(mnHeight);

    DrawPieSection(x, h - y, rx1, ry1, rx2, ry2,
        start_angle_rad, stop_angle_rad, color, fillMode);
}

/**
* rx1 is inner x radius, rx2 is outer x radius
* start and stop angle should proceed clockwise
*/
void tc3DWindow2::DrawPieSection(float x, float y, float rx1, float ry1, float rx2, float ry2,
        float start_angle_rad, float stop_angle_rad, const Vec4& color, int fillMode)
{
    float angle_span_rad = stop_angle_rad - start_angle_rad;
    if (angle_span_rad < 0) angle_span_rad += C_TWOPI;
    if (angle_span_rad > C_TWOPI) angle_span_rad = C_TWOPI;
    wxASSERT(angle_span_rad > 0);

    int nPoints = 2 + int(floorf(64.0f*angle_span_rad));

    nPoints = std::min(nPoints, 128);

    cTV_CUSTOM2DVERTEX* vertices = new cTV_CUSTOM2DVERTEX[2*nPoints];

    cTV_CUSTOM2DVERTEX temp;
    memset(&temp, 0, sizeof(temp));
    temp.color = RGBA(color.x, color.y, color.z, color.w);

    float delta_angle_rad = angle_span_rad / float(nPoints-1);

    float angle_rad = start_angle_rad;

    CTVScreen2DImmediate* screen2D = engine->GetScreen2D();

    float x1_prev = 0;
    float x2_prev = 0;
    float y1_prev = 0;
    float y2_prev = 0;

    for (int k=0; k<nPoints; k++)
    {    
        float sin_angle = sinf(angle_rad);
        float cos_angle = cosf(angle_rad);

        vertices[2*k] = temp;
        vertices[2*k + 1] = temp;

        float x2 = x + sin_angle*rx2;
        float y2 = y + cos_angle*ry2;
        float x1 = x + sin_angle*rx1;
        float y1 = y + cos_angle*ry1;

        vertices[2*k].x = x1;
        vertices[2*k].y = y1;
        vertices[2*k+1].x = x2;
        vertices[2*k+1].y = y2;

        angle_rad += delta_angle_rad;

        if (fillMode == FILL_OFF)
        {
            if (k > 0)
            {
                screen2D->Draw_Line(x1_prev, y1_prev, x1, y1, temp.color, temp.color);
                screen2D->Draw_Line(x2_prev, y2_prev, x2, y2, temp.color, temp.color);
            }

            if ((k == 0)||(k == nPoints-1))
            {
                screen2D->Draw_Line(x1, y1, x2, y2, temp.color, temp.color);
            }
        }

        x1_prev = x1;
        x2_prev = x2;
        y1_prev = y1;
        y2_prev = y2;
    }

    if (fillMode == FILL_ON)
    {
        screen2D->Draw_Line(0, 0, 0, 0, 0, 0);
        screen2D->Draw_Custom(-1, cTV_TRIANGLESTRIP, vertices, 2*nPoints);
    }

    delete[] vertices;
}


/**
* This method is used for inverted y coordinate system used by wxWindows
* y = 0 is at top of screen.
*/
void tc3DWindow2::DrawRectangleR(float x1, float y1, float width, float height, const Vec4& color,
								int fill)
{
	const float h = float(mnHeight);

	DrawRectangle(x1, h - y1 - height, width, height, color, fill);
}

/**
* This method is used for inverted y coordinate system used by wxWindows
* y = 0 is at top of screen.
*/
void tc3DWindow2::DrawRectangleR(const tcRect& rect, const Vec4& color,
								int fill)
{
	const float h = float(mnHeight);

	tcRect rectFlip = rect;
	rectFlip.bottom = h - rectFlip.top;
	float height = rect.Height();
	rectFlip.top = rectFlip.bottom + height;

	DrawRectangle(rectFlip, color, fill);
}


/**
* This method is used for inverted y coordinate system used by wxWindows
* y = 0 is at top of screen.
*/
void tc3DWindow2::DrawTextR(const char* s, float x, float y, tcFont* font, 
						   const Vec4& color, float fontSize, AlignmentType alignment,
						   float maximumWidth)
{
	const float h = float(mnHeight);

	DrawText(s, x, h - y, font, color, fontSize, alignment, maximumWidth);
}

/**
* This method is used for inverted y coordinate system used by wxWindows
* y = 0 is at top of screen.
*/
void tc3DWindow2::DrawTextR(const char* s, float x, float y, tcFont* font, 
						   const Vec4& color, float fontSize, AlignmentType alignment,
						   float maximumWidth, tcRect& bb)
{
	const float h = float(mnHeight);

	DrawText(s, x, h - y, font, color, fontSize, alignment, maximumWidth);

	bb = lastTextBoundingBox;
} 

/**
* This method is used for inverted y coordinate system used by wxWindows
* y = 0 is at top of screen.
*/
void tc3DWindow2::DrawTextInRectR(const char* s, const tcRect& r, tcFont* font, 
								 const Vec4& color, float fontSize, AlignmentType alignment)
{
	const float h = float(mnHeight);

	tcRect rectFlip = r;
	rectFlip.bottom = h - rectFlip.top;
	float height = r.Height();
	rectFlip.top = rectFlip.bottom + height;

	DrawTextInRect(s, rectFlip, font, color, fontSize, alignment);
}

/**
* @param w half-width of line
*/
void tc3DWindow2::DrawThickLine(float x1, float y1, float x2, float y2, float w, const Vec4& color)
{
    const float h = float(mnHeight);

    float dx = y2 - y1;
    float dy = x1 - x2;

    float a = w / sqrt(dx*dx + dy*dy);
    dx *= a;
    dy *= a;

    CTVScreen2DImmediate* screen2D = engine->GetScreen2D();

    int nColor = RGBA(color.x, color.y, color.z, color.w);

    float px1 = x1-dx+origin.x;
    float px2 = x2-dx+origin.x;
    float px3 = x2+dx+origin.x;
    float px4 = x1+dx+origin.x;

    float py1 = h-y1+dy+origin.y;
    float py2 = h-y2+dy+origin.y;
    float py3 = h-y2-dy+origin.y;
    float py4 = h-y1-dy+origin.y;

    screen2D->Draw_FilledTriangle(px1, py1, px2, py2, px3, py3, nColor, nColor, nColor);
    screen2D->Draw_FilledTriangle(px3, py3, px4, py4, px1, py1, nColor, nColor, nColor);
}

void tc3DWindow2::DrawThickLineR(float x1, float y1, float x2, float y2, float w, const Vec4& color)
{
    const float h = float(mnHeight);

    DrawThickLine(x1, h-y1, x2, h-y2, w, color);
}


void tc3DWindow2::DrawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, 
                               const Vec4& color, int fill)
{
    const float h = float(mnHeight);

    //float& dx = origin.x;
    float& dy = origin.y;

    CTVScreen2DImmediate* screen2D = engine->GetScreen2D();

    int nColor = RGBA(color.x, color.y, color.z, color.w);

    if (fill == FILL_ON)
    {
        screen2D->Draw_FilledTriangle(x1, dy+h-y1, x2, dy+h-y2, x3, dy+h-y3, nColor, nColor, nColor);
    }
    else
    {
        screen2D->Draw_Triangle(x1, dy+h-y1, x2, dy+h-y2, x3, dy+h-y3, nColor);
    }
}

void tc3DWindow2::DrawTriangleR(float x1, float y1, float x2, float y2, float x3, float y3, 
                                const Vec4& color, int fill)
{
	const float h = float(mnHeight);

    DrawTriangle(x1, h-y1, x2, h-y2, x3, h-y3, color, fill);
}


/**
* Optimize this later to check for case where geometry is already child
*/
void tc3DWindow2::DrawGeometry(tcGeometry* geometry, float x, float y)
{
    if (geometry != 0)
    {
        float dx, dy;
        GetOrigin(dx, dy);
        const float h = float(mnHeight);
        geometry->Draw(x+dx, h-y+dy);
    }
    else
    {
        wxASSERT(false);
        return;
    }

#if 0
	osg::MatrixTransform* transform = GetTransformObject();
	transform->setMatrix(osg::Matrix::translate(x, y, 0)); 
	

	transform->removeChild(0, transform->getNumChildren()); // shouldn't leak with ref ptrs
	

	osg::Geode* geode = new osg::Geode;
	geode->addDrawable(geometry);

	transform->addChild(geode);
#endif
}


void tc3DWindow2::DrawGeometryZoom(tcGeometry* geometry, float x, float y, float scale)
{
    if (geometry != 0)
    {
        float dx, dy;
        GetOrigin(dx, dy);
        const float h = float(mnHeight);
        geometry->DrawZoom(x+dx, h-y+dy, scale);
    }
    else
    {
        wxASSERT(false);
        return;
    }
}

/// workaround method for inverted coordinates
void tc3DWindow2::DrawGeometryR(tcGeometry* geometry, float x, float y)
{
	const float h = float(mnHeight);

	DrawGeometry(geometry, x, h - y);
}

/// workaround method for inverted coordinates
void tc3DWindow2::DrawGeometryZoomR(tcGeometry* geometry, float x, float y, float scale)
{
	const float h = float(mnHeight);

	DrawGeometryZoom(geometry, x, h - y, scale);
}

/**
* There wasn't a direct replacement for the GDI+ version of this.
* This an approximate version as a stand-in.
*/
void tc3DWindow2::MeasureText(tcFont* font, float fontSize, const char* s, 
							 wxSize& size) 
{
	wxASSERT(font);

    CTVScreen2DText* text2D = engine->GetText2D();

    int fontSizeInt = (int)floorf(fontSize + 0.5f);

    float width, height;
    text2D->TextureFont_GetTextSize(s, font->GetId(fontSizeInt), &width, &height);

    size.Set(ceilf(width), ceilf(height));
}


/**
* 
*/
void tc3DWindow2::WrapTextToWidth(tcFont* font, float fontSize, const char* s, float maxWidth, 
							 wxSize& size, wxString& wrappedText) 
{
    wrappedText.clear();

	wxASSERT(font);

    CTVScreen2DText* text2D = engine->GetText2D();

    int fontSizeInt = (int)floorf(fontSize + 0.5f);
    long fontId = font->GetId(fontSizeInt);

    float width, height;
    text2D->TextureFont_GetTextSize(s, fontId, &width, &height);

    if (width <= maxWidth)
    {
        size.Set(ceilf(width), ceilf(height));
        wrappedText = s;
        return;
    }

    wxString paragraph(s);
    wxString nextword = paragraph.BeforeFirst(' ');
    paragraph = paragraph.AfterFirst(' ');
    text2D->TextureFont_GetTextSize(nextword.c_str(), fontId, &width, &height);
    if (width > maxWidth) // just give up at this point
    {
        size.Set(ceilf(width), ceilf(height));
        wrappedText = s;
        return;
    }

    // fit the most words possible onto each line without exceeding maxWidth
    wxString line = nextword;
    bool wrapping = true;
    float maxWidthWithMargin = maxWidth - 2.0f;

    while (wrapping && (paragraph.size() > 0))
    {
        nextword = paragraph.BeforeFirst(' ');
        paragraph = paragraph.AfterFirst(' ');

        wxString biggerLine = line + wxString(' ');
        biggerLine += nextword;

        text2D->TextureFont_GetTextSize(biggerLine.c_str(), fontId, &width, &height);
        if (width <= maxWidthWithMargin)
        {
            line = biggerLine;
        }
        else
        {
            line += wxString("\n  ");
            line += nextword;
        }
    }

    size.Set(ceilf(width), ceilf(height));
    wrappedText = line;

}


/* Erase the surface with alpha = 0 */
void tc3DWindow2::Erase() 
{
    //mp2DSurface->Erase();
}

/* Erase with alpha = 0xFF */
void tc3DWindow2::EraseOpaque() 
{
    //mp2DSurface->EraseOpaque();
}

void tc3DWindow2::Freeze() 
{
    if (!mbFrozen) wxWindow::Freeze();
    mbFrozen = true;
}

float tc3DWindow2::GetCornerRadius() const
{
	return cornerRadius;
}

tcFont* tc3DWindow2::GetDefaultFont()
{
	return defaultFont.get();
}

tcFont* tc3DWindow2::GetMonospacedFont()
{
	return monospacedFont.get();
}

tcFont* tc3DWindow2::GetBoldFont()
{
	return boldFont.get();
}

tcFont*tc3DWindow2::GetItalicFont()
{
	return italicFont.get();
}

const tcRect& tc3DWindow2::GetLastTextBoundingBox() const
{
	return lastTextBoundingBox;
}

bool tc3DWindow2::HandleEraseBkgnd(WXHDC hDC)
{
    return TRUE;
}

/**
* 
*/
void tc3DWindow2::Maximize()
{
	if (!IsWindowMinimized()) return; // already maximized

	wxWindow::SetSize(normalPosition);
}

/**
*
*/
void tc3DWindow2::Minimize()
{
	if (IsWindowMinimized()) return; // already minimized

	wxWindow::SetSize(iconPosition);
}

/**
* @return true if background drawing is enabled
*/
bool tc3DWindow2::IsBackgroundEnabled() const
{
    return drawBackground;
}

/**
* Called IsWindowMinimized to avoid possible conflict
* with wxWindows::IsMinimized
*/
bool tc3DWindow2::IsWindowMinimized() const
{
	return mnWidth == iconSize;
}

bool tc3DWindow2::IsSurfaceModified() 
{
//    return mp2DSurface->mbModified;
	return false;
}

void tc3DWindow2::LoadBackgroundImage(const char* fileName) 
{
	wxString fileWithPath = PrependImagePath(fileName);

    backgroundTexture = boost::shared_ptr<tcTexture2D>(new tcTexture2D(fileWithPath.ToStdString()));

#if 0
	osg::Image* backgroundImage = osgDB::readImageFile(fileWithPath.c_str());

	if (!backgroundImage)
	{
		fprintf(stderr, "Failed to load background image: %s\n", fileName);
		return;
	}

	//backgroundImage->scaleImage(mnWidth, mnHeight, backgroundImage->r());
	//background->setImage(backgroundImage.get());
	//background->setSubImageDimensions(0, 0, mnWidth, mnHeight);

	backgroundTexture = new tcTexture2D;
	backgroundTexture->setDataVariance(osg::Object::STATIC);
	backgroundTexture->setImage(backgroundImage);
    
	
    osg::StateSet* stateSet = backgroundQuad->getOrCreateStateSet();
    stateSet->setTextureAttributeAndModes(0, backgroundTexture.get(), 
		osg::StateAttribute::ON);
	//stateSet->setRenderBinDetails(baseRenderBin + backgroundRenderBin, "RenderBin");
	
#endif
	SetBackgroundDraw(true);
}

/**
* Loads image (prepends image path automatically)
*/
//osg::Image* tc3DWindow2::LoadImage(const char* fileName)
//{    
//	wxString fileWithPath = PrependImagePath(fileName);
//	osg::Image* image = osgDB::readImageFile(fileWithPath.c_str());
//
//	if (!image)
//	{
//		fprintf(stderr, "Failed to load image: %s\n", fileName);
//	}
//
//	return image;
//}

/**
* Image directory path is prepended in this routine. Use only 
* local file name.
*/
boost::shared_ptr<tcTexture2D> tc3DWindow2::LoadTexture(const char* fileName) 
{
    wxString s = PrependImagePath(fileName);
    return boost::shared_ptr<tcTexture2D>(new tcTexture2D(s.ToStdString()));
}

/**
* Image directory path is prepended in this routine. Use only 
* local file name.
*/
boost::shared_ptr<tcTexture2D> tc3DWindow2::LoadTexture(const char* fileName, int width, int height) 
{
    wxString s = PrependImagePath(fileName);
    return boost::shared_ptr<tcTexture2D>(new tcTexture2D(s.ToStdString(), width, height));
}

/**
*
*/
int tc3DWindow2::GetBaseRenderBin() const
{
    return baseRenderBin;
}


/**
* @return alpha blending state for window.
*/
bool tc3DWindow2::GetBlend() const
{
	return blendingOn;
}

/**
* Used to enable or disable (default state) alpha blending
* for window.
*/
void tc3DWindow2::SetBlend(bool blend) 
{
    blendingOn = blend;

#if 0
    osg::StateAttribute::GLModeValue value;
    if (blendingOn)
    {
        value = osg::StateAttribute::ON;
    }
    else
    {
        value = osg::StateAttribute::OFF;
    }

	osg::StateSet* stateSet = root->getOrCreateStateSet();
	stateSet->setMode(GL_BLEND, value);

	osg::StateSet* groupStateSet = groupRoot->getOrCreateStateSet();
	groupStateSet->setMode(GL_BLEND, value);
	
	osg::StateSet* textStateSet = textRoot->getOrCreateStateSet();
	textStateSet->setMode(GL_BLEND, value);

	osg::StateSet* backgroundStateSet = backgroundRoot->getOrCreateStateSet();
	backgroundStateSet->setMode(GL_BLEND, value);
	
	osg::StateSet* lineStateSet = lineRoot->getOrCreateStateSet();
	lineStateSet->setMode(GL_BLEND, value);
#endif
}

void tc3DWindow2::SetCornerRadius(float r)
{
	if (cornerRadius != r)
	{
		cornerRadius = r;
		UpdateBackgroundShape();
	}
}


void tc3DWindow2::CaptureMouse()
{
	if (!wxWindow::HasCapture())
	{
		wxWindow::CaptureMouse();
	}
	else
	{
		wxASSERT(false); // already has capture
	}
}


/**
*
*/
void tc3DWindow2::ClearDrawObjects()
{
	SetBackgroundDraw(false);

    for (size_t n=0; n<children.size(); n++)
    {
        children[n]->ClearDrawObjects();
    }
}

/**
* If destroy is queued, destroy window and return true,
* otherwise do nothing and return false
*/
bool tc3DWindow2::FinishDestroy()
{
    if (destroy)
    {
        ClearDrawObjects();
        Destroy();
        return true;
    } 
	else // check children for destroy
    {
        //size_t nChildren = children.size();

        //for(size_t n=0;n<nChildren;n++)
        //{
        //    tc3DWindow2* child = children[n];
        //    wxASSERT(child);
        //    child->FinishDestroy();
        //}

		return false;
	}
}


/**
* Call at the end of window draw routine
*/
void tc3DWindow2::FinishDraw()
{
    wxASSERT(drawStarted);

    DrawBorder();

    float dx, dy;
    GetOrigin(dx, dy);

    CTVScreen2DImmediate* screen2D = engine->GetScreen2D();
    screen2D->Action_End2D();

    CTVScreen2DText* text2D = engine->GetText2D();
    text2D->Action_BeginText();

    for (size_t n=0; n<queuedText.size(); n++)
    {
        TextInfo& t = queuedText[n];

        float width, height;
        text2D->TextureFont_GetTextSize(t.s.c_str(), t.fontId, &width, &height);

        float xoffset = 0;
        float yoffset = 0;

        switch (t.alignment)
        {
        case LEFT_BASE_LINE:
        case LEFT_BOTTOM:
            xoffset = 0;
            yoffset = -height;
            break;
        case CENTER_CENTER:
            xoffset = floorf(-0.5f*width + 0.5f);
            yoffset = floorf(-0.5f*height + 0.5f);
            break;
        case LEFT_CENTER:
            xoffset = 0;
            yoffset = floorf(-0.5f*height + 0.5f);
            break;
        case RIGHT_CENTER:
            xoffset = -width;
            yoffset = floorf(-0.5f*height + 0.5f);
            break;
        case RIGHT_BASE_LINE:
            xoffset = -width;
            yoffset = -height;
            break;
        case LEFT_TOP:
            xoffset = 0;
            yoffset = 0;
            break;
        case CENTER_TOP:
            xoffset = floorf(-0.5f*width + 0.5f);
            yoffset = 0;
            break;
        default:
            wxASSERT(false); // bad alignment
            break;
        }

        text2D->TextureFont_DrawText(t.s.c_str(), t.x+xoffset+dx, t.y+yoffset+dy, t.rgba, t.fontId);
       
    }

    text2D->Action_EndText();


    drawStarted = false;
}






/**
* Sets region of window to display. This is intended
* to provide a zoomed view of a window e.g. the view
* area of the terrain map is a small region of the overall
* map that is zoomed to fit the map window.
* @param r RectF structure defining the display region bounds.
*/
void tc3DWindow2::SetDisplayRegion(tcRect r) 
{
   // mp2DSurface->SetDisplayRegion(r.X,r.Y,r.GetRight(),r.GetBottom());
    mrectDisplay = r;
}

void tc3DWindow2::MoveToTop()
{
    wxWindow::Raise();
}

void tc3DWindow2::LogStatus()
{
	fprintf(stdout, "3DWindow status: %s\n", wxWindow::GetName().c_str());
//	fprintf(stdout, "    transform num parents: %d, num children: %d\n", 
//		transform->getNumParents(), transform->getNumChildren());
//	fprintf(stdout, "    switch pos 0 val: %d\n", (int)switchNode->getValue(0));
}

void tc3DWindow2::MoveWindow(int ax, int ay) 
{
	
    mrectWindow.x = ax;
    mrectWindow.y = ay;
    mrectWindow.width = mnWidth;
    mrectWindow.height = mnHeight;

	/*
    if (yMirror)
        mp2DSurface->MoveWindow(ax,yMirror-mrectWindow.bottom);
    else
        mp2DSurface->MoveWindow(ax,ay);
		*/
    wxWindow::Move(wxPoint(ax,ay));
}

void tc3DWindow2::SetBaseRenderBin(int n)
{
	baseRenderBin = n;
#if 0
	backgroundRoot->getOrCreateStateSet()->
		setRenderBinDetails(baseRenderBin + backgroundRenderBin, "RenderBin");
	//backgroundQuad->getOrCreateStateSet()->
	//	setRenderBinDetails(baseRenderBin + backgroundRenderBin, "RenderBin");

	//UpdateBackgroundQuadVertices();
	UpdateBackgroundShape();

	/*osg::StateSet* textStateSet = textRoot->getOrCreateStateSet();
	textStateSet->setRenderBinDetails(baseRenderBin + textRenderBin, "RenderBin");

	osg::StateSet* lineStateSet = lineRoot->getOrCreateStateSet();
	lineStateSet->setRenderBinDetails(baseRenderBin + lineRenderBin, "RenderBin");

	osg::StateSet* groupStateSet = groupRoot->getOrCreateStateSet();
    groupStateSet->setRenderBinDetails(baseRenderBin + geometryRenderBin, "RenderBin");*/


	size_t nChildren = children.size();

	for(size_t k=0; k<nChildren; k++)
	{
		wxASSERT(children[k]);

		children[k]->SetBaseRenderBin(baseRenderBin + 5);
	}
#endif
}

void tc3DWindow2::SetName(const char* s)
{
	//transform->setName(s);
}

void tc3DWindow2::Thaw() 
{
    if (mbFrozen)
    {
        wxWindow::Thaw();
        mbFrozen = false;
    }
}



unsigned char tc3DWindow2::GetStencilLayer() const
{
	return stencilLayer;
}


void tc3DWindow2::SetRenderSurfaceUpdateInterval(unsigned int interval)
{
    rsUpdateInterval = interval;
}

void tc3DWindow2::SetStencilLayer(unsigned char n)
{
	if (stencilLayer != n)
	{
		stencilLayer = n;
		UpdateStencil();
	}
}

bool tc3DWindow2::GetUseRenderSurface() const
{
    return useRenderSurface;
}


/**
* @param margin reduces width of render surface to support transparent scroll bars
*/
void tc3DWindow2::SetUseRenderSurface(bool state, int margin)
{
    if (state == useRenderSurface) return;
    useRenderSurface = state;
    
    renderSurfaceMargin = margin;

    if (useRenderSurface)
    {
        //CTVScene* scene = tcTVEngine::Get()->GetScene();
        //renderSurface = scene->CreateAlphaRenderSurface(mnWidth, mnHeight, false);

        ////renderSurface->SetNewCamera(tcTVEngine::Get()->GetCamera());
        //renderSurface->SetBackgroundColor(RGBA(0, 0, 0, 1));


        renderSurface = tcTVEngine::Get()->Create2DRenderSurface(mnWidth-renderSurfaceMargin, mnHeight);

    }
    else
    {
        wxASSERT(renderSurface != 0);
        if (renderSurface != 0)
        {
            renderSurface->Destroy();
            DeleteTVObject(renderSurface);
            //delete renderSurface; // this trips ASSERT so use DeleteTVObject
            renderSurface = 0;
        }
        renderSurfaceMargin = 0;
    }

}



/**
* Updates stencil state. Call once after stencilLayer is changed.
*/
void tc3DWindow2::UpdateStencil()
{
	//{
	//	osg::StateSet* textStateSet = textRoot->getOrCreateStateSet();

	//	osg::Stencil* stencil = dynamic_cast<osg::Stencil*>(textStateSet->getAttribute(osg::StateAttribute::STENCIL));
	//	if (stencil == 0)
	//	{
	//		stencil = new osg::Stencil;
	//	}
	//	stencil->setFunction(osg::Stencil::EQUAL, stencilLayer, ~0u);
	//	stencil->setOperation(osg::Stencil::KEEP, osg::Stencil::KEEP, osg::Stencil::KEEP);


	//	stencil->setFunction(osg::Stencil::EQUAL, stencilLayer, ~0u); // set stencil val to 1
	//	stencil->setOperation(osg::Stencil::KEEP, osg::Stencil::KEEP, osg::Stencil::KEEP);
	//	osg::StateAttribute::Values stencilState = (stencilLayer > 0) ? osg::StateAttribute::ON : osg::StateAttribute::OFF;
	//	textStateSet->setAttributeAndModes(stencil, stencilState);
	//}

	//{
	//	osg::StateSet* backgroundStateSet = backgroundQuad->getOrCreateStateSet();
	//	
	//	osg::Stencil* backgroundStencil = dynamic_cast<osg::Stencil*>(backgroundStateSet->getAttribute(osg::StateAttribute::STENCIL));
	//	if (backgroundStencil == 0)
	//	{
	//		backgroundStencil = new osg::Stencil;
	//	}

	//	backgroundStencil->setFunction(osg::Stencil::ALWAYS, stencilLayer, ~0u);
	//	backgroundStencil->setOperation(osg::Stencil::REPLACE, osg::Stencil::REPLACE, osg::Stencil::REPLACE);

	//	backgroundStateSet->setAttributeAndModes(backgroundStencil, osg::StateAttribute::ON);
	//}


}



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/**
* static method tc3DWindow2::Set3DViewer must be called before constructing objects
*/
tc3DWindow2::tc3DWindow2(wxWindow *parent, const wxPoint& pos, const wxSize& size, 
        const wxString& name, tc3DWindow2* graphicsHost) :
        wxWindow(parent, -1, pos, size, wxTRANSPARENT_WINDOW | wxNO_FULL_REPAINT_ON_RESIZE | wxCLIP_CHILDREN, name),   //| wxNO_FULL_REPAINT_ON_RESIZE |wxCLIP_CHILDREN
        mnHeight(size.GetHeight()), mnWidth(size.GetWidth()),
		iconSize(32),
		normalPosition(pos, size),
		baseRenderBin(10),
		backgroundRenderBin(-1),
		imageRenderBin(0),
		lineRenderBin(1), // using 1 causes dropouts at some 3D viewer window sizes!?
		rectRenderBin(1),
        geometryRenderBin(1),
		textRenderBin(2),
		fontSize(10.0),
		fontSizeLarge(16.0),
		fontSizeSmall(7.0),
        backgroundColor(1.0f, 1.0f, 1.0f, 1.0f),
        borderColor(1.0f, 1.0f, 1.0f, 1.0f),
        hostParent(graphicsHost),
        blendingOn(true),
		cornerRadius(0),
		stencilLayer(0),
        drawBackground(false),
        drawBorder(false),
        drawStarted(false),
        useRenderSurface(false),
        rsUpdateCount(10),
        rsLastUpdateCount(0),
        rsUpdateInterval(1),
        renderSurface(0),
        renderSurfaceMargin(0),
        destroy(false),
        charPropagationLevel(0),
        leaveWindowPropagationLevel(0)

{

	SetName(name.c_str());
    mbActive = false;

    UpdatePositionAndSize(pos, size);


    wxWindow::SetBackgroundColour(*wxBLACK);
    wxWindow::Show(FALSE);
    


	/* need to update to create default icon position as a 
	** function of initial window position
	*/
	iconPosition = wxRect(normalPosition.GetRight() - iconSize, 
		                  normalPosition.GetBottom() - iconSize,
						  iconSize,
						  iconSize);


    mbFrozen = false;


	mbCloned = true;
	resizeable2DSurface = false;
	yMirror = 0;
	if (graphicsHost) 
	{       
		graphicsHost->AddChild(this); // adds this to parent's list of children to draw
	}

    if (defaultFont.get() == 0)
    {
        defaultFont = boost::shared_ptr<tcFont>(new tcFont("ArialA", "fonts/arial.ttf", true, false));

        monospacedFont = boost::shared_ptr<tcFont>(new tcFont("MonoSpacedA", "fonts/courier_bold.ttf", false, false));

        boldFont = boost::shared_ptr<tcFont>(new tcFont("ArialB", "fonts/arial.ttf", true, false));

		italicFont = boost::shared_ptr<tcFont>(new tcFont("ArialB", "fonts/arial.ttf", false, true));
    }

	//defaultFont = osgText::readFontFile("fonts/times.ttf");
	//defaultFont = osgText::readFontFile("fonts/arial.ttf");

#if 0
	defaultTexture = new tcTexture2D;
	defaultTexture->setDataVariance(osg::Object::STATIC);
	wxString texPath = PrependImagePath("start1_on.jpg");
    defaultTexture->setImage(osgDB::readImageFile(texPath.c_str()));

	testSymbol = new tcTexture2D;
	texPath = PrependImagePath("symbology\\base.png");
	testSymbol->setImage(osgDB::readImageFile(texPath.c_str()));

	referenceText = new osgText::Text();
	referenceText->setFont(defaultFont.get());
	referenceText->setColor(Vec4(1.0, 1.0, 1.0, 1.0));
	referenceText->setCharacterSize(16.0f, 1.2f); // font height, aspect ratio
	referenceText->setPosition(osg::Vec3(0, 0, 0));
	referenceText->setLayout(osgText::Text::LEFT_TO_RIGHT);
	referenceText->setFontResolution(32, 32);
	referenceText->setText("UNINITIALIZED");
	referenceText->setUseDisplayList(false);
#endif
	
	//LoadBackgroundImage("console_b.jpg");
	//SetBackgroundDraw(true);
}

tc3DWindow2::~tc3DWindow2() 
{    
    if (renderSurface != 0)
    {
        renderSurface->Destroy();
        DeleteTVObject(renderSurface); // straight delete crashes
    }

#ifdef _DEBUG
	/*
	fprintf(stdout, "Destroying 3D window %s, %d text obj, %d image quad obj"
		", line obj %d, rect obj %d, transform %d\n",
		wxWindow::GetName().c_str(), textPool.size(), imageQuadPool.size(),
		linePool.size(), rectPool.size(), transformPool.size());
	*/
#endif

	if (wxWindow::HasCapture())
	{
		wxWindow::ReleaseMouse();
	}

	if (hostParent) 
	{       
		hostParent->RemoveChild(this); // watch out for destruction order problems here
	}

}


