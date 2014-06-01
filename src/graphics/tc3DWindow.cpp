/**  
**  @file tc3DWindow.cpp: implementation of the tc3DWindow class.
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

#include <osg/ClipNode>
#include <osg/Depth>
#include <osg/DrawPixels>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/Group>
#include <osg/LineWidth>
#include <osg/MatrixTransform>
#include <osg/Projection>
#include <osg/Stencil>
#include <osg/Switch>
#include <osg/Texture2D>
#include <osgDB/ReadFile>
#include <osgText/Text>
#include <osgText/Font>
#include <osg/OccluderNode>
#include <osg/ConvexPlanarOccluder>

#include "tc3DWindow.h"
#include "tcGraphicsInfo.h"
#include "AError.h"
#include <stdio.h>
#include <iostream>
#include "tcString.h"
#include "tcSound.h"
#include "tc3DViewer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif 


BEGIN_EVENT_TABLE(tc3DWindow, wxWindow)
EVT_PAINT(tc3DWindow::OnPaint)
EVT_NC_PAINT(tc3DWindow::OnNcPaint)
EVT_ERASE_BACKGROUND(tc3DWindow::OnEraseBackground)
EVT_MOVE(tc3DWindow::OnMove)
EVT_LEFT_DOWN(tc3DWindow::OnLButtonDown) 
EVT_LEFT_DCLICK(tc3DWindow::OnLButtonDClick)
EVT_LEFT_UP(tc3DWindow::OnLButtonUp)  
EVT_RIGHT_DOWN(tc3DWindow::OnRButtonDown) 
EVT_MOTION(tc3DWindow::OnMouseMove)  
EVT_MOUSEWHEEL(tc3DWindow::OnMouseWheel) 
EVT_KEY_DOWN(tc3DWindow::OnKeyDown)  ///< any key has been pressed  
EVT_CHAR(tc3DWindow::OnChar)  
EVT_ENTER_WINDOW(tc3DWindow::OnEnterWindow)
EVT_LEAVE_WINDOW(tc3DWindow::OnLeaveWindow)
EVT_SHOW(tc3DWindow::OnShow)
EVT_SIZE(tc3DWindow::OnSize)
EVT_SET_FOCUS(tc3DWindow::OnSetFocus) 
EVT_KILL_FOCUS(tc3DWindow::OnKillFocus) 
EVT_CLOSE(tc3DWindow::OnClose)
END_EVENT_TABLE()

tc3DViewer* tc3DWindow::viewer = 0;


/**
* This override along with use of Freeze() Thaw() prevents 
* the flicker that happens when the window background is erased 
* by wxWindows.
*/
//long tc3DWindow::MSWWindowProc(WXUINT nMsg, WXWPARAM wParam, WXLPARAM lParam)
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


void tc3DWindow::OnChar(wxKeyEvent& event)
{
    event.Skip();
}

void tc3DWindow::OnClose(wxCloseEvent& event)
{
    event.Skip();
}

void tc3DWindow::OnEnterWindow(wxMouseEvent& event)
{
    SetFocus();
}

/**
* Do nothing for EraseBackground event.
*/
void tc3DWindow::OnEraseBackground(wxEraseEvent& event)
{
    //SetBackgroundColour(*wxBLACK);
    //fprintf(stdout, "Erase [%s]\n",GetName());
	return;
}

void tc3DWindow::OnNcPaint(wxNcPaintEvent& event)
{
	wxPaintDC dc(this);
}

/**
* Do nothing for OnPaint event.
*/
void tc3DWindow::OnPaint(wxPaintEvent& event)
{
    wxPaintDC dc(this);
    //fprintf(stdout, "Paint [%s]\n",GetName());
}

/**
* Do nothing for show event.
*/
void tc3DWindow::OnShow(wxShowEvent& event)
{
    return;
}

void tc3DWindow::OnKeyDown(wxKeyEvent& event)
{
    event.Skip();
}

void tc3DWindow::OnLButtonDown(wxMouseEvent& event)
{
    SkipMouseEvent(event);
}

void tc3DWindow::OnLButtonDClick(wxMouseEvent& event)
{
    SkipMouseEvent(event);
}

void tc3DWindow::OnLButtonUp(wxMouseEvent& event)
{
    SkipMouseEvent(event);
}

void tc3DWindow::OnLeaveWindow(wxMouseEvent& event)
{
	event.Skip();
}

void tc3DWindow::OnMouseMove(wxMouseEvent& event)
{
    event.Skip();
}

void tc3DWindow::OnMouseWheel(wxMouseEvent& event)
{
    event.Skip();
}



void tc3DWindow::OnMove(wxMoveEvent& event)
{

    wxPoint pos = event.GetPosition();
	wxSize size = wxWindow::GetSize();

	UpdatePositionAndSize(pos, size);
}

void tc3DWindow::OnRButtonDown(wxMouseEvent& event)
{
    SkipMouseEvent(event);
}

void tc3DWindow::OnSetFocus(wxFocusEvent& event)
{
}

void tc3DWindow::OnKillFocus(wxFocusEvent& event)
{
}

void tc3DWindow::OnSize(wxSizeEvent& event)
{
    wxSize size = event.GetSize();
    wxPoint pos = wxWindow::GetPosition();

   	UpdatePositionAndSize(pos, size);
}


/**
* Call after move or size event
*/
void tc3DWindow::UpdatePositionAndSize(const wxPoint& pos, const wxSize& size)
{
	bool sizeChanged = (size.GetWidth() != mnWidth) || (size.GetHeight() != mnHeight);
	mnWidth = size.GetWidth();
    mnHeight = size.GetHeight();

	int yOffset = 0;
	if (wxWindow* parent = wxWindow::GetParent())
	{
		wxSize parentSize = parent->GetSize();
		yOffset = parentSize.GetHeight() - 2*pos.y - mnHeight;
	}


    mrectWindow.x = pos.x;
	mrectWindow.width = size.GetWidth();
    mrectWindow.y = pos.y;
	mrectWindow.height = size.GetHeight();

	transform->setMatrix(osg::Matrix::translate(pos.x, pos.y + yOffset, 0)); 

	if (sizeChanged)
	{
		UpdateBackgroundShape();
	}
}

/**
* Adds child window to children vector. This
* allows drawing of children windows through
* DrawChildren() method.
*/
void tc3DWindow::AddChild(tc3DWindow* child)
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
void tc3DWindow::RemoveChild(tc3DWindow* child)
{
    wxASSERT(child);
    if (child == NULL) return;
    
    childrenToRemove.push(child);
}

/**
* Removes pending children for removal from children vector. 
*/
void tc3DWindow::UpdateChildren()
{
    /* for each child in the childrenToRemove queue
    ** iterate through children vector and remove if
    ** found */
    while (!childrenToRemove.empty())
    {
        tc3DWindow* child = childrenToRemove.front();
        childrenToRemove.pop();

        wxASSERT(child);
        if (child == NULL) return;
        std::vector<tc3DWindow*>::iterator iter = children.begin();
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
* and tc3DWindow use the same system for child windows. Possibly
* both can derive from the same 3D window class.
*
* @return projection that was just created
*/
osg::MatrixTransform* tc3DWindow::CreateDrawTransform()
{
	osg::MatrixTransform* childTransform = new osg::MatrixTransform; 
	childTransform->setDataVariance(osg::Object::DYNAMIC);
	//transform->addChild(childTransform);
	switchNode->addChild(childTransform);
	return childTransform;
}



/**
* Called at window creation or after window size change to update quad boundaries
*/
void tc3DWindow::UpdateBackgroundQuad()
{
	if (!backgroundQuad.valid())
	{
		backgroundQuad = new osg::Geometry;
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
	backgroundQuad->setColorBinding(osg::Geometry::BIND_OVERALL);

	/*
	osg::Vec3Array* normals = new osg::Vec3Array(1);
	(*normals)[0].set(1.0f, 0.0f, 0.0f);
	backgroundQuad->setNormalArray(normals);
	backgroundQuad->setNormalBinding(osg::Geometry::BIND_OVERALL);
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
}


/**
* Version to create rounded background quads
* Create background polygon and border graphics based on cornerRadius value.
* cornerRadius = 0 is square corners (no rounding)
*/
void tc3DWindow::UpdateBackgroundShape()
{
	//wxASSERT(!backgroundQuad.valid());
	
	if (cornerRadius == 0)
	{
		UpdateBackgroundQuad();
		return;
	}

	if (!backgroundQuad.valid())
	{
		backgroundQuad = new osg::Geometry;
	}

	if (!border.valid())
	{
		border = new osg::Geometry;
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
	colors->push_back(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f)); 
	backgroundQuad->setColorArray(colors);
	backgroundQuad->setColorBinding(osg::Geometry::BIND_OVERALL);

	backgroundQuad->addPrimitiveSet(new osg::DrawArrays(GL_TRIANGLES,0,vertices->size()));

	border->setVertexArray(borderVertices);
	osg::Vec4Array* borderColors = new osg::Vec4Array;
	borderColors->push_back(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f)); 
	border->setColorArray(borderColors);
	border->setColorBinding(osg::Geometry::BIND_OVERALL);

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
}



/** 
* @return wxString with IMAGE_PATH prepended to <fileName>
*/
wxString tc3DWindow::PrependImagePath(const char* fileName) 
{
	wxString s = wxString::Format("%s%s", IMAGE_PATH, fileName);

	return s;
}

/**
* Converts relative coordinates to screen coordinates
*/
wxRealPoint tc3DWindow::RelativeToScreen(float x, float y)
{
	wxRealPoint p;

	p.x = x * float(mnWidth);
	p.y = (1-y) * float(mnHeight);

	return p;
}

void tc3DWindow::ReleaseMouse()
{
	if (isMouseCaptured)
	{
		wxWindow::ReleaseMouse();
		isMouseCaptured = false;
	}
}


/**
* wxWindows (or MS Windows behind it) erases window region
* when the window is moved or Show() is used. This causes
* a flickering effect. Enable() is used to activate/deactivate 
* GUI inputs for the window.
*/
void tc3DWindow::SetActive(bool abActive) 
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

		switchNode->setAllChildrenOn();
    }
    else
    {
        wxWindow::Enable(false);

		switchNode->setAllChildrenOff();
    }

    mbActive = abActive;

}

/**
* Sets color of background quad
*/
void tc3DWindow::SetBackgroundColor(const osg::Vec4& color)
{
    backgroundColor = color;
    UpdateBackgroundQuad();
}

/**
* @param state true to enable background drawing, false to disable
*/
void tc3DWindow::SetBackgroundDraw(bool state)
{
	if (state == IsBackgroundEnabled()) return; // already set to state
	
	if (state)
	{
#ifdef _DEBUG
		//fprintf(stdout, "(%s) Adding background quad, bin: %d\n", wxWindow::GetName().c_str(),
		//	backgroundRoot->getStateSet()->getBinNumber());
#endif
		backgroundRoot->addDrawable(backgroundQuad.get());
		//root->addDrawable(backgroundQuad.get());
	}
	else
	{
		backgroundRoot->removeDrawable(backgroundQuad.get());
		//root->removeDrawable(backgroundQuad.get());
	}
    UpdateBackgroundQuad();
}




/**
* Adjusts wxMouseEvent position to parent's frame.
* Calls Skip() on event.
*/
void tc3DWindow::SkipMouseEvent(wxMouseEvent& event)
{
    wxPoint pos = wxWindow::GetPosition();
    event.m_x += pos.x;
    event.m_y += pos.y;
    event.Skip();
}


/**
* Creates default osg::Geometry object
*/
osg::Geometry* tc3DWindow::CreateDefaultGeometry()
{
	osg::Geometry* symbol = new osg::Geometry;

	symbol->setUseDisplayList(true);

	// set state
	osg::StateSet* stateSet = symbol->getOrCreateStateSet();
	stateSet->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF);
	stateSet->setMode(GL_DEPTH_WRITEMASK, osg::StateAttribute::OFF);
	stateSet->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	stateSet->setMode(GL_BLEND, osg::StateAttribute::ON);
	stateSet->setRenderBinDetails(baseRenderBin + rectRenderBin, "RenderBin");

	return symbol;
}

/**
* Angle of zero is up, angle increases in clockwise direction
* startAngle must be less than stopAngle (can use negative angles)
* @param startAngle in degrees
* @param stopAngle in degrees
*/
osg::Geometry* tc3DWindow::CreatePieGeometry(float width, float height, float startAngle, float stopAngle, 
											 osg::Vec4& color, int fillMode)
{
	unsigned int nArcPoints = 48;

	wxASSERT(startAngle < stopAngle);
	wxASSERT(nArcPoints > 1);

	osg::Geometry* symbol = CreateDefaultGeometry();

	// set color
	osg::Vec4Array* colors = new osg::Vec4Array;
	colors->push_back(color);
	symbol->setColorArray(colors);
	symbol->setColorBinding(osg::Geometry::BIND_OVERALL);

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
}

/**
* Create quad, textured with image specified by <symbolname>
*/
osg::Geometry* tc3DWindow::CreateTexturedSymbol(const char* imageName, float width)
{
    float w = 0.5f * width;
	
	osg::Geometry* symbol = new osg::Geometry;

	osg::Vec4Array* colors = new osg::Vec4Array;
	colors->push_back(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f));
	symbol->setColorArray(colors);
	symbol->setColorBinding(osg::Geometry::BIND_OVERALL);

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
    colors->push_back(osg::Vec4(0.5, 0.5, 1.0, 0.5));
	symbol->setColorArray(colors);
    symbol->setColorBinding(osg::Geometry::BIND_OVERALL);
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

	osg::Texture2D* texture = new osg::Texture2D;
	texture->setDataVariance(osg::Object::STATIC);
    texture->setImage(image);

	osg::StateSet* stateset = symbol->getOrCreateStateSet();
    stateset->setTextureAttributeAndModes(0, texture, 
		osg::StateAttribute::ON);

	return symbol;
}


/**
*
*/
void tc3DWindow::Draw() 
{
    DrawChildren();

	FinishDraw();
}



/**
* Call Draw() method for all children
*/
void tc3DWindow::DrawChildren()
{
    UpdateChildren();

    size_t nChildren = children.size();

    for(size_t n=0;n<nChildren;n++)
    {
		tc3DWindow* child = children[n];
        wxASSERT(child);
        
		if (child->IsActive()) child->Draw();
        
    }
}


/**
* Draw a border 
*/
void tc3DWindow::DrawBorder() 
{
	if (cornerRadius == 0)
	{
		osg::Vec4 white(1.0f, 1.0f, 1.0f, 0.7f);

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
}

/**
* Draws image using textured quad
* @param x center x coord
* @param y center y coord
* @param alignMode CENTER (default) or ALIGN_BOTTOM_LEFT
*/
void tc3DWindow::DrawImage(osg::Texture2D* texture, float x, float y, 
						   float width, float height, int alignMode)
{
	wxASSERT(texture);
	if (!texture) return;

	osg::Geometry* quad = GetImageQuadObject();
	wxASSERT(quad);
	wxASSERT(texture);

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
		fprintf(stderr, "tc3DWindow::DrawImage - corrupt vertex array\n");
		wxASSERT(0);
	}
    
    osg::StateSet* stateset = quad->getOrCreateStateSet();
    stateset->setTextureAttributeAndModes(0, texture, 
		osg::StateAttribute::ON);


}

/**
*
*/
void tc3DWindow::DrawLine(float x1, float y1, float x2, float y2, const osg::Vec4& color)
{
	osg::Geometry* line = GetLineObject();
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
		fprintf(stderr, "tc3DWindow::DrawLine - corrupt vertex array\n");
		wxASSERT(0);
	}		

}

/**
* @param fill FILL_ON to fill rectangle with solid color, FILL_OFF for outline only
*/
void tc3DWindow::DrawRectangle(const tcRect& rect, const osg::Vec4& color,
							   int fill)
{
	float x1 = rect.left;
	float y1 = rect.bottom;
	float width = rect.Width();
	float height = rect.Height();

	DrawRectangle(x1, y1, width, height, color, fill);
}

/**
* @param fill FILL_ON to fill rectangle with solid color, FILL_OFF for outline only
*/
void tc3DWindow::DrawRectangle(float x1, float y1, float width, float height, 
						  const osg::Vec4& color, int fill)
{
	osg::Vec4 white(1.0f, 1.0f, 1.0f, 1.0f);

	osg::Geometry* rect = GetRectObject();
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
		fprintf(stderr, "tc3DWindow::DrawRectangle - corrupt vertex array\n");
		wxASSERT(0);
	}		
}


/**
* @param maximumWidth text wraps at this width, set to 0 or negative for no wrapping
*/
void tc3DWindow::DrawText(const char* s, float x, float y, osgText::Font* font, 
					   const osg::Vec4& color, float fontSize, 
					   osgText::Text::AlignmentType alignment, float maximumWidth)
{ 
	if (strlen(s) == 0) return; 
	if (strcmp(s, " ") == 0) return;

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

}


/**
* @param r set to bounding box of text (not supported yet)
*/
//void tc3DWindow::DrawText(const char* s, float x, float y, osgText::Font* font, 
//						  const osg::Vec4& color, float fontSize, osgText::Text::AlignmentType alignment,
//						  tcRect& r)
//{
//	DrawText(s, x, y, font, color, fontSize, alignment);
//}

void tc3DWindow::DrawTextInRect(const char* s, const tcRect& r, osgText::Font* font, 
								const osg::Vec4& color, float fontSize, osgText::Text::AlignmentType alignment)
{
	float x = (alignment == CENTER_CENTER) ? r.XCenter() : r.left;
	float y = (alignment == CENTER_CENTER) || (alignment == LEFT_CENTER) ? r.YCenter() : r.bottom + 2;
	float maximumWidth = r.Width();

	DrawText(s, x, y, font, color, fontSize, alignment, maximumWidth);
}


/**
* This version draws a zoomed image on a quad, zoom rectangle specified by r
* @see tc3DWindow::DrawImage
*/
void tc3DWindow::DrawZoomedImage(osg::Texture2D* texture, float x, float y, float width, float height,
		const tcRect& r, int alignMode)
{
	wxASSERT(texture);
	if (!texture) return;

	osg::Geometry* quad = GetImageQuadObject();
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
		fprintf(stderr, "tc3DWindow::DrawZoomedImage - corrupt vertex array\n");
		wxASSERT(0);
	}
    
    osg::StateSet* stateset = quad->getOrCreateStateSet();
    stateset->setTextureAttributeAndModes(0, texture, 
		osg::StateAttribute::ON);
}




/**
* This method is used for inverted y coordinate system used by wxWindows
* y = 0 is at top of screen.
*/
void tc3DWindow::DrawImageR(osg::Texture2D* texture, float x, float y, 
							float width, float height, int alignMode)
{
	const float h = float(mnHeight);

	DrawImage(texture, x, h - y - height, width, height, alignMode);

}

/**
* This method is used for inverted y coordinate system used by wxWindows
* y = 0 is at top of screen.
*/
void tc3DWindow::DrawZoomedImageR(osg::Texture2D* texture, float x, float y, float width, float height,
		const tcRect& r, int alignMode)
{
    const float h = float(mnHeight);

	DrawZoomedImage(texture, x, h - y - height, width, height, r, alignMode);
}


/**
* This method is used for inverted y coordinate system used by wxWindows
* y = 0 is at top of screen.
*/
void tc3DWindow::DrawLineR(float x1, float y1, float x2, float y2, 
						   const osg::Vec4& color)
{
	const float h = float(mnHeight);

	DrawLine(x1, h - y1, x2, h - y2, color);
}


/**
* This method is used for inverted y coordinate system used by wxWindows
* y = 0 is at top of screen.
*/
void tc3DWindow::DrawRectangleR(float x1, float y1, float width, float height, const osg::Vec4& color,
								int fill)
{
	const float h = float(mnHeight);

	DrawRectangle(x1, h - y1 - height, width, height, color, fill);
}

/**
* This method is used for inverted y coordinate system used by wxWindows
* y = 0 is at top of screen.
*/
void tc3DWindow::DrawRectangleR(const tcRect& rect, const osg::Vec4& color,
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
void tc3DWindow::DrawTextR(const char* s, float x, float y, osgText::Font* font, 
						   const osg::Vec4& color, float fontSize, osgText::Text::AlignmentType alignment,
						   float maximumWidth)
{
	const float h = float(mnHeight);

	DrawText(s, x, h - y, font, color, fontSize, alignment, maximumWidth);
}

/**
* This method is used for inverted y coordinate system used by wxWindows
* y = 0 is at top of screen.
*/
void tc3DWindow::DrawTextR(const char* s, float x, float y, osgText::Font* font, 
						   const osg::Vec4& color, float fontSize, osgText::Text::AlignmentType alignment,
						   float maximumWidth, osg::BoundingBox& bb)
{
	const float h = float(mnHeight);

	DrawText(s, x, h - y, font, color, fontSize, alignment, maximumWidth);

	bb = lastTextBoundingBox;
} 

/**
* This method is used for inverted y coordinate system used by wxWindows
* y = 0 is at top of screen.
*/
void tc3DWindow::DrawTextInRectR(const char* s, const tcRect& r, osgText::Font* font, 
								 const osg::Vec4& color, float fontSize, osgText::Text::AlignmentType alignment)
{
	const float h = float(mnHeight);

	tcRect rect = r;
	float height = rect.Height();

	rect.bottom = h - rect.bottom;
	rect.top = rect.bottom + height;

	DrawTextInRect(s, rect, font, color, fontSize, alignment);

}


/**
* Optimize this later to check for case where geometry is already child
*/
void tc3DWindow::DrawGeometry(osg::Geometry* geometry, float x, float y)
{
	osg::MatrixTransform* transform = GetTransformObject();
	transform->setMatrix(osg::Matrix::translate(x, y, 0)); 
	

	transform->removeChild(0, transform->getNumChildren()); // shouldn't leak with ref ptrs
	

	osg::Geode* geode = new osg::Geode;
	geode->addDrawable(geometry);

	transform->addChild(geode);
}

/// workaround method for inverted coordinates
void tc3DWindow::DrawGeometryR(osg::Geometry* geometry, float x, float y)
{
	const float h = float(mnHeight);

	DrawGeometry(geometry, x, h - y);
}



/**
* There wasn't a direct replacement for the GDI+ version of this.
* This an approximate version as a stand-in.
*/
void tc3DWindow::MeasureText(osgText::Font* font, float fontSize, const char* s, 
							 wxSize& size) 
{
	wxASSERT(font);

	if (referenceText->getFont() != font)
	{
		referenceText->setFont(font);
	}
	referenceText->setCharacterSize(fontSize, 1.2f); // font height, aspect ratio
	referenceText->setText(s);

	osg::BoundingBox bb = referenceText->getBound();
	float width = bb.xMax() - bb.xMin();
	float height = bb.yMax() - bb.yMin();

	size.SetHeight(int(height));
	size.SetWidth(int(width));
}


/* Erase the surface with alpha = 0 */
void tc3DWindow::Erase() 
{
    //mp2DSurface->Erase();
}

/* Erase with alpha = 0xFF */
void tc3DWindow::EraseOpaque() 
{
    //mp2DSurface->EraseOpaque();
}

void tc3DWindow::Freeze() 
{
    if (!mbFrozen) wxWindow::Freeze();
    mbFrozen = true;
}

float tc3DWindow::GetCornerRadius() const
{
	return cornerRadius;
}

osgText::Font* tc3DWindow::GetDefaultFont()
{
	return defaultFont.get();
}

const osg::BoundingBox& tc3DWindow::GetLastTextBoundingBox() const
{
	return lastTextBoundingBox;
}

/**
* 
*/
void tc3DWindow::Maximize()
{
	if (!IsWindowMinimized()) return; // already maximized

	wxWindow::SetSize(normalPosition);
}

/**
*
*/
void tc3DWindow::Minimize()
{
	if (IsWindowMinimized()) return; // already minimized

	wxWindow::SetSize(iconPosition);
}

/**
* @return true if background drawing is enabled
*/
bool tc3DWindow::IsBackgroundEnabled() const
{
	return (backgroundQuad->getNumParents() != 0);
}

/**
* Called IsWindowMinimized to avoid possible conflict
* with wxWindows::IsMinimized
*/
bool tc3DWindow::IsWindowMinimized() const
{
	return mnWidth == iconSize;
}

bool tc3DWindow::IsSurfaceModified() 
{
//    return mp2DSurface->mbModified;
	return false;
}

void tc3DWindow::LoadBackgroundImage(const char* fileName) 
{
	wxString fileWithPath = PrependImagePath(fileName);

	osg::Image* backgroundImage = osgDB::readImageFile(fileWithPath.c_str());

	if (!backgroundImage)
	{
		fprintf(stderr, "Failed to load background image: %s\n", fileName);
		return;
	}

	//backgroundImage->scaleImage(mnWidth, mnHeight, backgroundImage->r());
	//background->setImage(backgroundImage.get());
	//background->setSubImageDimensions(0, 0, mnWidth, mnHeight);

	backgroundTexture = new osg::Texture2D;
	backgroundTexture->setDataVariance(osg::Object::STATIC);
	backgroundTexture->setImage(backgroundImage);
    
	
    osg::StateSet* stateSet = backgroundQuad->getOrCreateStateSet();
    stateSet->setTextureAttributeAndModes(0, backgroundTexture.get(), 
		osg::StateAttribute::ON);
	//stateSet->setRenderBinDetails(baseRenderBin + backgroundRenderBin, "RenderBin");
	

	SetBackgroundDraw(true);
}

/**
* Loads image (prepends image path automatically)
*/
osg::Image* tc3DWindow::LoadImage(const char* fileName)
{    
	wxString fileWithPath = PrependImagePath(fileName);
	osg::Image* image = osgDB::readImageFile(fileWithPath.c_str());

	if (!image)
	{
		fprintf(stderr, "Failed to load image: %s\n", fileName);
	}

	return image;
}

/**
* Image directory path is prepended in this routine. Use only 
* local file name.
*/
osg::Texture2D* tc3DWindow::LoadTexture(const char* fileName) 
{
	osg::Image* image = LoadImage(fileName);

    if (image != 0)
    {
        osg::Texture2D* tex = new osg::Texture2D;
        tex->setDataVariance(osg::Object::STATIC);
        tex->setImage(image);

        return tex;
    }
    else
    {
        wxASSERT(false);
        return 0;
    }
}

/**
*
*/
int tc3DWindow::GetBaseRenderBin() const
{
    return baseRenderBin;
}


/**
* @return alpha blending state for window.
*/
bool tc3DWindow::GetBlend() const
{
	return blendingOn;
}

/**
* Used to enable or disable (default state) alpha blending
* for window.
*/
void tc3DWindow::SetBlend(bool blend) 
{
    blendingOn = blend;


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
}

void tc3DWindow::SetCornerRadius(float r)
{
	if (cornerRadius != r)
	{
		cornerRadius = r;
		UpdateBackgroundShape();
	}
}


void tc3DWindow::SetOpaque()
{
 //   mp2DSurface->SetOpaque();
}

void tc3DWindow::SetPixel(int x, int y, unsigned int value) 
{
	/*
    if (mp2DSurface != NULL) {
        mp2DSurface->SetPixel(x,y,value);
    }
	*/
}



osg::Geometry* tc3DWindow::GetImageQuadObject()
{
	size_t nPool = imageQuadPool.size();

	if (imageQuadIdx < nPool)
	{
		osg::Geometry* quad = imageQuadPool[imageQuadIdx++].get();
		wxASSERT(quad);
		if (quad->getNumParents() == 0)
		{
			root->addDrawable(quad);
		}
		quad->dirtyBound();

		return quad;
	}
	else if (imageQuadIdx == nPool)
	{
		osg::ref_ptr<osg::Geometry> quad = new osg::Geometry;

		osg::Vec3Array* vertices = new osg::Vec3Array(4);
		(*vertices)[0] = osg::Vec3(0, mnHeight, 0);
		(*vertices)[1] = osg::Vec3(0, 0, 0);
		(*vertices)[2] = osg::Vec3(mnWidth, 0, 0);
		(*vertices)[3] = osg::Vec3(mnWidth, mnHeight, 0);
		quad->setVertexArray(vertices);

		osg::Vec2Array* texcoords = new osg::Vec2Array(4);
		(*texcoords)[0].set(0.0f,1.0f);
		(*texcoords)[1].set(0.0f,0.0f);
		(*texcoords)[2].set(1.0f,0.0f);
		(*texcoords)[3].set(1.0f,1.0f);
		quad->setTexCoordArray(0,texcoords);

		osg::Vec4Array* colors = new osg::Vec4Array;
		colors->push_back(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f)); 
		quad->setColorArray(colors);
		quad->setColorBinding(osg::Geometry::BIND_OVERALL);

		/*
		osg::Vec3Array* normals = new osg::Vec3Array(1);
		(*normals)[0].set(1.0f, 0.0f, 0.0f);
		quad->setNormalArray(normals);
		quad->setNormalBinding(osg::Geometry::BIND_OVERALL);
		*/

		quad->addPrimitiveSet(new osg::DrawArrays(GL_QUADS,0,4));
		
		quad->setUseDisplayList(false);

		osg::StateSet* stateSet = quad->getOrCreateStateSet();
		stateSet->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF);
		stateSet->setMode(GL_DEPTH_WRITEMASK, osg::StateAttribute::OFF);
		stateSet->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
		stateSet->setRenderBinDetails(baseRenderBin + imageRenderBin, "RenderBin");

		wxASSERT(root.valid());
		root->addDrawable(quad.get());
		
		imageQuadPool.push_back(quad);

		return imageQuadPool[imageQuadIdx++].get();
	}
	else
	{
		wxASSERT(0);
		fprintf(stderr, "tc3DWindow::GetImageQuadObject - Corrupt imageQuadIdx\n");
		return 0;
	}
}


osg::Geometry* tc3DWindow::GetLineObject()
{
	size_t nPool = linePool.size();

	if (lineIdx < nPool)
	{
		osg::Geometry* line = linePool[lineIdx++].get();
		wxASSERT(line);

		if (line->getNumParents() == 0)
		{
			//root->addDrawable(line);
			lineRoot->addDrawable(line);
		}
		line->dirtyBound();
		return line;
	}
	else if (lineIdx == nPool)
	{
		osg::Geometry* line = new osg::Geometry;

		osg::Vec3Array* vertices = new osg::Vec3Array(2);
		(*vertices)[0] = osg::Vec3(0, 0, 0);
		(*vertices)[1] = osg::Vec3(mnWidth, mnHeight, 0);
		line->setVertexArray(vertices);


        osg::Vec4Array* colors = new osg::Vec4Array;
        colors->push_back(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f)); 
        line->setColorArray(colors);
        line->setColorBinding(osg::Geometry::BIND_OVERALL);


		line->addPrimitiveSet(new osg::DrawArrays(GL_LINES, 0, 2));

		line->setUseDisplayList(false);


		/*
		osg::StateSet* stateSet = line->getOrCreateStateSet();
		stateSet->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF);
		stateSet->setMode(GL_DEPTH_WRITEMASK, osg::StateAttribute::OFF);
		stateSet->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
		stateSet->setMode(GL_BLEND, osg::StateAttribute::OFF);
		stateSet->setRenderBinDetails(baseRenderBin + lineRenderBin, "RenderBin");
		*/

		/*
		osg::LineWidth* lw = new osg::LineWidth;
		lw->setWidth(2);
		stateSet->setAttribute(lw);
		*/

		wxASSERT(lineRoot.valid());
		//root->addDrawable(line.get());
		lineRoot->addDrawable(line);

		linePool.push_back(line);
		lineIdx++;
		return line;
	}
	else
	{
		wxASSERT(0);
		fprintf(stderr, "tc3DWindow::GetLineObject - Corrupt lineIdx\n");
		return 0;
	}
}


osg::Geometry* tc3DWindow::GetRectObject()
{
	size_t nPool = rectPool.size();

	if (rectIdx < nPool)
	{
		osg::Geometry* rect = rectPool[rectIdx++].get();
		wxASSERT(rect);

		osg::StateSet* stateSet = rect->getOrCreateStateSet();

		int currentBin = stateSet->getBinNumber();
		if (currentBin != baseRenderBin + rectRenderBin)
		{
			stateSet->setRenderBinDetails(baseRenderBin + rectRenderBin, "RenderBin");
			fprintf(stderr, "Error - RectObject RenderBin changed! Correcting from %d to %d\n", 
				currentBin, baseRenderBin + rectRenderBin);
		}


		if (rect->getNumParents() == 0)
		{
			root->addDrawable(rect);
		}
		rect->dirtyBound();

		return rect;
	}
	else if (rectIdx == nPool)
	{
		osg::ref_ptr<osg::Geometry> rect = new osg::Geometry;

		osg::Vec3Array* vertices = new osg::Vec3Array(4);
		(*vertices)[0] = osg::Vec3(0, 1, 0);
		(*vertices)[1] = osg::Vec3(0, 0, 0);
		(*vertices)[2] = osg::Vec3(2, 0, 0);
		(*vertices)[3] = osg::Vec3(2, 1, 0);
		rect->setVertexArray(vertices);

		/*
		osg::Vec2Array* texcoords = new osg::Vec2Array(4);
		(*texcoords)[0].set(0.0f,1.0f);
		(*texcoords)[1].set(0.0f,0.0f);
		(*texcoords)[2].set(1.0f,0.0f);
		(*texcoords)[3].set(1.0f,1.0f);
		rect->setTexCoordArray(0,texcoords);
		*/

		osg::Vec3Array* normals = new osg::Vec3Array(1);
		(*normals)[0].set(1.0f, 0.0f, 0.0f);
		rect->setNormalArray(normals);
		rect->setNormalBinding(osg::Geometry::BIND_OVERALL);


        osg::Vec4Array* colors = new osg::Vec4Array;
        colors->push_back(osg::Vec4(1.0f,1.0f,1.0f,1.0f));
        rect->setColorArray(colors);
		rect->setColorBinding(osg::Geometry::BIND_OVERALL);


		rect->addPrimitiveSet(new osg::DrawArrays(GL_QUADS,0,4));

		rect->setUseDisplayList(false);

		osg::StateSet* stateSet = rect->getOrCreateStateSet();
		stateSet->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF);
		stateSet->setMode(GL_DEPTH_WRITEMASK, osg::StateAttribute::OFF);
		stateSet->setMode(GL_LIGHTING, osg::StateAttribute::OFF); 
		stateSet->setMode(GL_BLEND, osg::StateAttribute::ON); 
		stateSet->setRenderBinDetails(baseRenderBin + rectRenderBin, "RenderBin");

		wxASSERT(root.valid());
		root->addDrawable(rect.get());

		rectPool.push_back(rect);

		return rectPool[rectIdx++].get();
	}
	else
	{
		wxASSERT(0);
		fprintf(stderr, "tc3DWindow::GetRectObject - Corrupt rectIdx\n");
		return 0;
	}
}


osgText::Text* tc3DWindow::GetTextObject()
{
	size_t nPool = textPool.size();

	if (textIdx < nPool)
	{
		osgText::Text* text = textPool[textIdx++].get();
		wxASSERT(text);
		if (text->getNumParents() == 0)
		{
			textRoot->addDrawable(text);
		}
		else if (text->getNumParents() > 1)
		{
			fprintf(stderr, "Error - tc3DWindow::GetTextObject - too many parents\n");
		}

		
#if 0
		if (osg::StateSet* stateSet = textRoot->getStateSet())
		{		
			int currentBin = stateSet->getBinNumber();
			if (currentBin != baseRenderBin + textRenderBin)
			{
				fprintf(stderr, "Error - (%s) TextObject RenderBin changed! Correcting from %d to %d"
					" tidx: %d 3dwin:%ld ss:%ld\n", 
					wxWindow::GetName().c_str(), currentBin, baseRenderBin + textRenderBin, textIdx-1, 
					(unsigned long)this, (unsigned long)stateSet);

			    for (size_t k=0; k<nPool; k++)
				{
					fprintf(stderr, "   %d %ld\n", k, (unsigned long)textPool[k].get()->getStateSet());
				}

				stateSet->setRenderBinDetails(baseRenderBin + textRenderBin, "RenderBin");
			}

		}
		else
		{
			fprintf(stderr, "Error - TextObject null stateset\n");
		}
#endif
		text->dirtyBound();
		text->dirtyDisplayList();
		return text;
	}
	else if (textIdx == nPool)
	{
		osg::ref_ptr<osgText::Text> text = new osgText::Text();
		text->setFont(defaultFont.get());
		text->setColor(osg::Vec4(1.0, 1.0, 1.0, 1.0));
		text->setCharacterSize(16.0f, 1.2f); // font height, aspect ratio
		text->setPosition(osg::Vec3(20.0f, 20.0f, 0));
		text->setLayout(osgText::Text::LEFT_TO_RIGHT);
		text->setFontResolution(32, 32);
		//text->setFontResolution(64, 64);
		text->setText("UNINTIALIZED");

		text->setUseDisplayList(false);

		
		//osg::StateSet* stateSet = new osg::StateSet;

		//stateSet->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF);
		//stateSet->setMode(GL_DEPTH_WRITEMASK, osg::StateAttribute::OFF);
		//stateSet->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
		//stateSet->setMode(GL_BLEND, osg::StateAttribute::ON);

		//text->setStateSet(stateSet);






		wxASSERT(textRoot.valid());
		textRoot->addDrawable(text.get());

		textPool.push_back(text);

		return textPool[textIdx++].get();
	}
	else
	{
		wxASSERT(0);
		fprintf(stderr, "tc3DWindow::GetTextObject - Corrupt textIdx\n");
		return 0;
	}
}

/**
*
*/
osg::MatrixTransform* tc3DWindow::GetTransformObject()
{
	size_t nPool = transformPool.size();

	if (transformIdx < nPool)
	{
		osg::MatrixTransform* transform = transformPool[transformIdx++].get();
		wxASSERT(transform);
		if (transform->getNumParents() == 0)
		{
			groupRoot->addChild(transform);
		}
		return transform;
	}
	else if (transformIdx == nPool)
	{
		osg::ref_ptr<osg::MatrixTransform> transform = new osg::MatrixTransform;

		transform->setReferenceFrame(osg::MatrixTransform::RELATIVE_RF); 
		transform->setDataVariance(osg::Object::DYNAMIC);

		wxASSERT(groupRoot.valid());
		groupRoot->addChild(transform.get());

		transformPool.push_back(transform);

		return transformPool[transformIdx++].get();
	}
	else
	{
		wxASSERT(0);
		fprintf(stderr, "tc3DWindow::GetTransformObject - Corrupt transformIdx\n");
		return 0;
	}
}

void tc3DWindow::CaptureMouse()
{
	wxWindow::CaptureMouse();

	isMouseCaptured = true;
}


/**
*
*/
void tc3DWindow::ClearDrawObjects()
{
    textIdx = 0;
	imageQuadIdx = 0;
	lineIdx = 0;
	rectIdx = 0;
	transformIdx = 0;

    HideUnusedObjects();
	SetBackgroundDraw(false);

    for (size_t n=0; n<children.size(); n++)
    {
        children[n]->ClearDrawObjects();
    }
}


/**
* Newer name for HideUnusedObjects, use this for new code
*/
void tc3DWindow::FinishDraw()
{
	HideUnusedObjects();
}

/**
* removes unused (as of last Draw() call) objects from root scenegraph node
* This should be called once at the end of Draw()
* Deprecated, use FinishDraw()
*/
void tc3DWindow::HideUnusedObjects()
{

#if 0
	if (osg::StateSet* stateSet = backgroundRoot->getStateSet())
	{		
		int currentBin = stateSet->getBinNumber();
		if (currentBin != baseRenderBin + backgroundRenderBin)
		{
			stateSet->setRenderBinDetails(baseRenderBin + backgroundRenderBin, "RenderBin");
			fprintf(stderr, "Error - backgroundRoot RenderBin changed! Correcting from %d to %d"
				" 3dwin:%ld ss:%ld\n", 
				currentBin, baseRenderBin + backgroundRenderBin, 
				(unsigned long)this, (unsigned long)stateSet);
		}

	}
	else
	{
		fprintf(stderr, "Error - backgroundRoot null stateset\n");
	}
#endif
	


	// text pool
	for (unsigned idx = textIdx; idx < textPool.size(); idx++)
	{
		textRoot->removeDrawable(textPool[idx].get());
		//textPool[idx]->setPosition(osg::Vec3(10000.0f, 10000.0f, -10000.0f));
	}
	textIdx = 0;

	// image quad pool
	for (unsigned idx = imageQuadIdx; idx < imageQuadPool.size(); idx++)
	{
		root->removeDrawable(imageQuadPool[idx].get());
	}
	imageQuadIdx = 0;

	// line pool
	for (unsigned idx = lineIdx; idx < linePool.size(); idx++)
	{
		//root->removeDrawable(linePool[idx].get());
		lineRoot->removeDrawable(linePool[idx].get());
	}
	lineIdx = 0;

	// rect pool
	for (unsigned idx = rectIdx; idx < rectPool.size(); idx++)
	{
		root->removeDrawable(rectPool[idx].get());
	}
	rectIdx = 0;

	// transform pool
	for (unsigned idx = transformIdx; idx < transformPool.size(); idx++)
	{
		groupRoot->removeChild(transformPool[idx].get());
	}
	transformIdx = 0;

}

/**
* should be called once to initialize graphics pools
*/
void tc3DWindow::InitGraphicsObjects()
{
	textPool.clear();
	textIdx = 0;

	imageQuadPool.clear();
	imageQuadIdx = 0;

	linePool.clear();
	lineIdx = 0;

	rectPool.clear();
	rectIdx = 0;

	transformPool.clear();
	transformIdx = 0;
}


/**
* Sets region of window to display. This is intended
* to provide a zoomed view of a window e.g. the view
* area of the terrain map is a small region of the overall
* map that is zoomed to fit the map window.
* @param r RectF structure defining the display region bounds.
*/
void tc3DWindow::SetDisplayRegion(tcRect r) 
{
   // mp2DSurface->SetDisplayRegion(r.X,r.Y,r.GetRight(),r.GetBottom());
    mrectDisplay = r;
}

void tc3DWindow::MoveToTop()
{
    wxWindow::Raise();
}

void tc3DWindow::LogStatus()
{
	fprintf(stdout, "3DWindow status: %s\n", wxWindow::GetName().c_str());
	fprintf(stdout, "    transform num parents: %d, num children: %d\n", 
		transform->getNumParents(), transform->getNumChildren());
	fprintf(stdout, "    switch pos 0 val: %d\n", (int)switchNode->getValue(0));
}

void tc3DWindow::MoveWindow(int ax, int ay) 
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

void tc3DWindow::SetBaseRenderBin(int n)
{
	baseRenderBin = n;

	backgroundRoot->getOrCreateStateSet()->
		setRenderBinDetails(baseRenderBin + backgroundRenderBin, "RenderBin");
	//backgroundQuad->getOrCreateStateSet()->
	//	setRenderBinDetails(baseRenderBin + backgroundRenderBin, "RenderBin");

	//UpdateBackgroundQuadVertices();
	UpdateBackgroundShape();

	osg::StateSet* textStateSet = textRoot->getOrCreateStateSet();
	textStateSet->setRenderBinDetails(baseRenderBin + textRenderBin, "RenderBin");

	osg::StateSet* lineStateSet = lineRoot->getOrCreateStateSet();
	lineStateSet->setRenderBinDetails(baseRenderBin + lineRenderBin, "RenderBin");

	osg::StateSet* groupStateSet = groupRoot->getOrCreateStateSet();
    groupStateSet->setRenderBinDetails(baseRenderBin + geometryRenderBin, "RenderBin");


	size_t nChildren = children.size();

	for(size_t k=0; k<nChildren; k++)
	{
		wxASSERT(children[k]);

		children[k]->SetBaseRenderBin(baseRenderBin + 5);
	}
}

void tc3DWindow::SetName(const char* s)
{
	transform->setName(s);
}

void tc3DWindow::Thaw() 
{
    if (mbFrozen)
    {
        wxWindow::Thaw();
        mbFrozen = false;
    }
}



unsigned char tc3DWindow::GetStencilLayer() const
{
	return stencilLayer;
}


void tc3DWindow::SetStencilLayer(unsigned char n)
{
	if (stencilLayer != n)
	{
		stencilLayer = n;
		UpdateStencil();
	}
}


/**
* Updates stencil state. Call once after stencilLayer is changed.
*/
void tc3DWindow::UpdateStencil()
{
	{
		osg::StateSet* textStateSet = textRoot->getOrCreateStateSet();

		osg::Stencil* stencil = dynamic_cast<osg::Stencil*>(textStateSet->getAttribute(osg::StateAttribute::STENCIL));
		if (stencil == 0)
		{
			stencil = new osg::Stencil;
		}
		stencil->setFunction(osg::Stencil::EQUAL, stencilLayer, ~0u);
		stencil->setOperation(osg::Stencil::KEEP, osg::Stencil::KEEP, osg::Stencil::KEEP);


		stencil->setFunction(osg::Stencil::EQUAL, stencilLayer, ~0u); // set stencil val to 1
		stencil->setOperation(osg::Stencil::KEEP, osg::Stencil::KEEP, osg::Stencil::KEEP);
		osg::StateAttribute::Values stencilState = (stencilLayer > 0) ? osg::StateAttribute::ON : osg::StateAttribute::OFF;
		textStateSet->setAttributeAndModes(stencil, stencilState);
	}

	{
		osg::StateSet* backgroundStateSet = backgroundQuad->getOrCreateStateSet();
		
		osg::Stencil* backgroundStencil = dynamic_cast<osg::Stencil*>(backgroundStateSet->getAttribute(osg::StateAttribute::STENCIL));
		if (backgroundStencil == 0)
		{
			backgroundStencil = new osg::Stencil;
		}

		backgroundStencil->setFunction(osg::Stencil::ALWAYS, stencilLayer, ~0u);
		backgroundStencil->setOperation(osg::Stencil::REPLACE, osg::Stencil::REPLACE, osg::Stencil::REPLACE);

		backgroundStateSet->setAttributeAndModes(backgroundStencil, osg::StateAttribute::ON);
	}


}



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/**
* static method tc3DWindow::Set3DViewer must be called before constructing objects
*/
tc3DWindow::tc3DWindow(wxWindow *parent, const wxPoint& pos, const wxSize& size, 
        const wxString& name, tc3DWindow* graphicsHost) :
        wxWindow(parent, -1, pos, size, wxTRANSPARENT_WINDOW | wxNO_FULL_REPAINT_ON_RESIZE, name),   //| wxNO_FULL_REPAINT_ON_RESIZE |wxCLIP_CHILDREN
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
		fontSize(12.0),
		fontSizeLarge(18.0),
		fontSizeSmall(9.0),
        backgroundColor(1.0f, 1.0f, 1.0f, 1.0f),
        hostParent(graphicsHost),
        blendingOn(true),
		isMouseCaptured(false),
		cornerRadius(0),
		stencilLayer(0)

{
	wxASSERT(viewer);

    wxWindow::SetBackgroundColour(*wxBLACK);
    wxWindow::Show(FALSE);
    
    mbActive = false;
    mrectWindow.x = pos.x;
    mrectWindow.width = size.GetWidth();
    mrectWindow.y = pos.y;
    mrectWindow.height = size.GetHeight();
	
	int yOffset = 0;
	if (parent)
	{
		wxSize parentSize = parent->GetSize();
		yOffset = parentSize.GetHeight() - mnHeight - 2*pos.y;
	}



	root = new osg::Geode;
	root->setName(name.c_str());
	osg::StateSet* stateSet = root->getOrCreateStateSet();
	stateSet->setMode(GL_BLEND, osg::StateAttribute::ON);
	stateSet->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF);
	stateSet->setMode(GL_DEPTH_WRITEMASK, osg::StateAttribute::OFF);
	stateSet->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	root->setCullingActive(false);


	groupRoot = new osg::Group;
	osg::StateSet* groupStateSet = groupRoot->getOrCreateStateSet();
	groupStateSet->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF);
	groupStateSet->setMode(GL_DEPTH_WRITEMASK, osg::StateAttribute::OFF);
	groupStateSet->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	groupStateSet->setMode(GL_BLEND, osg::StateAttribute::ON);
    groupStateSet->setRenderBinDetails(baseRenderBin + geometryRenderBin, "RenderBin");
	

	textRoot = new osg::Geode;
	osg::StateSet* textStateSet = textRoot->getOrCreateStateSet();
	

	textStateSet->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF);
	textStateSet->setMode(GL_DEPTH_WRITEMASK, osg::StateAttribute::OFF);
	textStateSet->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	textStateSet->setMode(GL_BLEND, osg::StateAttribute::ON);
	textStateSet->setRenderBinDetails(baseRenderBin + textRenderBin, "RenderBin");


	backgroundRoot = new osg::Geode;
	
	osg::StateSet* backgroundStateSet = backgroundRoot->getOrCreateStateSet();
	// fprintf(stdout, "(%s) creating background stateset: %ld\n", wxWindow::GetName().c_str(),
	//	(unsigned long)backgroundStateSet); 
	backgroundStateSet->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF);
	backgroundStateSet->setMode(GL_DEPTH_WRITEMASK, osg::StateAttribute::OFF);
	backgroundStateSet->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	backgroundStateSet->setMode(GL_BLEND, osg::StateAttribute::ON);
	backgroundStateSet->setRenderBinDetails(baseRenderBin + backgroundRenderBin, "RenderBin");
	
	lineRoot = new osg::Geode;
	osg::StateSet* lineStateSet = lineRoot->getOrCreateStateSet();
	lineStateSet->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF);
	lineStateSet->setMode(GL_DEPTH_WRITEMASK, osg::StateAttribute::OFF);
	lineStateSet->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	lineStateSet->setMode(GL_BLEND, osg::StateAttribute::ON);
	lineStateSet->setRenderBinDetails(baseRenderBin + lineRenderBin, "RenderBin");
	lineRoot->setCullingActive(false);
	//osg::Depth* depth = new osg::Depth(osg::Depth::ALWAYS, 0, 0, false);
	//stateSet->setAttributeAndModes(depth, osg::StateAttribute::ON);



	switchNode = new osg::Switch;
	switchNode->addChild(root.get());
	switchNode->addChild(groupRoot.get());
	switchNode->addChild(textRoot.get());
	switchNode->addChild(backgroundRoot.get());
	switchNode->addChild(lineRoot.get());
	switchNode->setAllChildrenOff();

	/* kind of a hack here to handle both top-level window case
	** and child of window case */
	if (graphicsHost)
	{
		transform = graphicsHost->CreateDrawTransform();
		transform->setDataVariance(osg::Object::DYNAMIC);
		transform->setMatrix(osg::Matrix::translate(pos.x, pos.y + yOffset, 0)); 
		transform->setReferenceFrame(osg::MatrixTransform::RELATIVE_RF); 
	}
	else
	{
		transform = viewer->CreateDrawTransform();
		transform->setDataVariance(osg::Object::DYNAMIC);
		transform->setMatrix(osg::Matrix::translate(pos.x, pos.y + yOffset, 0)); 
		transform->setReferenceFrame(osg::MatrixTransform::ABSOLUTE_RF); 
	}

	
	transform->addChild(switchNode.get());

	SetName(name.c_str());


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

	//defaultFont = osgText::readFontFile("fonts/times.ttf");
	defaultFont = osgText::readFontFile("fonts/arial.ttf");

	InitGraphicsObjects();

	defaultTexture = new osg::Texture2D;
	defaultTexture->setDataVariance(osg::Object::STATIC);
	wxString texPath = PrependImagePath("start1_on.jpg");
    defaultTexture->setImage(osgDB::readImageFile(texPath.c_str()));

	testSymbol = new osg::Texture2D;
	texPath = PrependImagePath("symbology\\base.png");
	testSymbol->setImage(osgDB::readImageFile(texPath.c_str()));

	referenceText = new osgText::Text();
	referenceText->setFont(defaultFont.get());
	referenceText->setColor(osg::Vec4(1.0, 1.0, 1.0, 1.0));
	referenceText->setCharacterSize(16.0f, 1.2f); // font height, aspect ratio
	referenceText->setPosition(osg::Vec3(0, 0, 0));
	referenceText->setLayout(osgText::Text::LEFT_TO_RIGHT);
	referenceText->setFontResolution(32, 32);
	referenceText->setText("UNINITIALIZED");
	referenceText->setUseDisplayList(false);

	UpdateBackgroundShape();
	
	//LoadBackgroundImage("console_b.jpg");
	//SetBackgroundDraw(true);
}

tc3DWindow::~tc3DWindow() 
{
#ifdef _DEBUG
	/*
	fprintf(stdout, "Destroying 3D window %s, %d text obj, %d image quad obj"
		", line obj %d, rect obj %d, transform %d\n",
		wxWindow::GetName().c_str(), textPool.size(), imageQuadPool.size(),
		linePool.size(), rectPool.size(), transformPool.size());
	*/
#endif

	if (isMouseCaptured)
	{
		wxWindow::ReleaseMouse();
	}

	if (hostParent) 
	{       
		hostParent->RemoveChild(this); // watch out for destruction order problems here
	}
	
	{
		unsigned nParents = transform->getNumParents();
		for (unsigned n=0; n<nParents; n++)
		{
			osg::Group* parent = transform->getParent(n);
			parent->removeChild(transform.get());
		}
		
	}
}


