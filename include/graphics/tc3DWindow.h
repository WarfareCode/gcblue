/**  
**  @file tc3DWindow.h
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

#ifndef _TC3DWINDOW_H_
#define _TC3DWINDOW_H_

#if _MSC_VER > 1000
#pragma once
#endif 

#ifndef WX_PRECOMP
#include "wx/wx.h" 
#endif 
#include <wx/event.h>

#include <queue>
#include <vector>

#include <osg/ref_ptr>
#include <osgText/Text>

#include "common/simmath.h"

namespace osg
{
	class ClipNode;
	class DrawPixels;
	class Geode;
	class Geometry;
	class Group;
	class MatrixTransform;
	class Projection;
	class Switch;
	class Texture2D;
//	class Vec4; // causes C1001, line 2701 compiler error !?
}


class tcGraphicsInfo;
class tc3DViewer;

#define IMAGE_PATH "images\\"


// using directives do not work on gcc, used #defines as workaround
#define LEFT_BASE_LINE osgText::Text::LEFT_BASE_LINE
#define LEFT_CENTER osgText::Text::LEFT_CENTER
#define RIGHT_CENTER osgText::Text::RIGHT_CENTER
#define CENTER_CENTER osgText::Text::CENTER_CENTER

/**
* Window class for drawing to a 3D OSG scenegraph.
* This is intended as a cross-platform replacement for tc3DWindow.
* tc3DWindow heavily used the Windows GDI+ libary. 
*/
class tc3DWindow : public wxWindow 
{
public:
	enum {CENTER = 0, ALIGN_BOTTOM_LEFT = 1};
	enum {FILL_OFF = 0, FILL_ON = 1};
    bool mbActive;
    tcRect mrectDisplay;

    void AddChild(tc3DWindow* child);
    void RemoveChild(tc3DWindow* child);

	osg::Geometry* CreateDefaultGeometry();
	osg::Geometry* CreatePieGeometry(float width, float height, float startAngle, float stopAngle, 
											 osg::Vec4& color, int fillMode);
	static osg::Geometry* CreateTexturedSymbol(const char* imageName, float width);

    
    virtual void Draw();
    virtual void DrawChildren(); // virtual void DrawChildren(Gdiplus::Graphics *graphics);

    void DrawBorder();

	void DrawImage(osg::Texture2D* texture, float x, float y, float width, float height,
		int alignMode = CENTER);

	/// workaround method for inverted coordinates
	void DrawImageR(osg::Texture2D* texture, float x, float y, float width, float height,
		int alignMode = CENTER); 

	void DrawZoomedImage(osg::Texture2D* texture, float x, float y, float width, float height,
		const tcRect& r, int alignMode = CENTER);

	/// workaround method for inverted coordinates
	void DrawZoomedImageR(osg::Texture2D* texture, float x, float y, float width, float height,
		const tcRect& r, int alignMode = CENTER); 
	
	void DrawLine(float x1, float y1, float x2, float y2, const osg::Vec4& color);

	/// workaround method for inverted coordinates
	void DrawLineR(float x1, float y1, float x2, float y2, const osg::Vec4& color);

	void DrawRectangle(float x1, float y1, float width, float height, const osg::Vec4& color,
		int fill = FILL_OFF);

	void DrawRectangle(const tcRect& rect, const osg::Vec4& color,
		int fill = FILL_OFF);

	/// workaround method for inverted coordinates
	void DrawRectangleR(float x1, float y1, float width, float height, const osg::Vec4& color,
		int fill = FILL_OFF);

	/// workaround method for inverted coordinates
	void DrawRectangleR(const tcRect& rect, const osg::Vec4& color,
		int fill = FILL_OFF);

    void DrawText(const char* s, float x, float y, osgText::Font* font, 
		const osg::Vec4& color, float fontSize, osgText::Text::AlignmentType alignment,
		float maximumWidth = 0.0); 

	/// returns bounding box in r
  //  void DrawText(const char* s, float x, float y, osgText::Font* font, 
		//const osg::Vec4& color, float fontSize, osgText::Text::AlignmentType alignment,
		//float maximumWidth, tcRect& r); 

    void DrawTextInRect(const char* s, const tcRect& r, osgText::Font* font, 
		const osg::Vec4& color, float fontSize, osgText::Text::AlignmentType alignment);

	/// workaround method for inverted coordinates
    void DrawTextR(const char* s, float x, float y, osgText::Font* font, 
		const osg::Vec4& color, float fontSize, osgText::Text::AlignmentType alignment,
		float maximumWidth = 0.0); 

	/// workaround method for inverted coordinates
    void DrawTextR(const char* s, float x, float y, osgText::Font* font, 
		const osg::Vec4& color, float fontSize, osgText::Text::AlignmentType alignment,
		float maximumWidth, osg::BoundingBox& bb); 

	/// workaround method for inverted coordinates
    void DrawTextInRectR(const char* s, const tcRect& r, osgText::Font* font, 
		const osg::Vec4& color, float fontSize, osgText::Text::AlignmentType alignment);


	void DrawGeometry(osg::Geometry* geometry, float x, float y);

	/// workaround method for inverted coordinates
	void DrawGeometryR(osg::Geometry* geometry, float x, float y);

    void MeasureText(osgText::Font* font, float fontSize, const char* s, 
        wxSize& size);

    void Erase();
    void EraseOpaque();
    virtual void Freeze();
	osgText::Font* GetDefaultFont();
	const osg::BoundingBox& GetLastTextBoundingBox() const;
	bool IsActive() const {return mbActive;}
	bool IsBackgroundEnabled() const;
    bool IsSurfaceModified();
	virtual bool IsWindowMinimized() const;
    void LoadBackgroundImage(const char* fileName);
	static osg::Image* LoadImage(const char* fileName);
	static osg::Texture2D* LoadTexture(const char* fileName);
	virtual void Maximize();
	virtual void Minimize();
    void MoveToTop(); ///< moves window to top
    void MoveWindow(int ax, int ay);
	wxRealPoint RelativeToScreen(float x, float y);

    bool GetBlend() const;
    void SetBlend(bool blend);
    int GetBaseRenderBin() const;
	virtual void SetBaseRenderBin(int n);
	float GetCornerRadius() const;
	void SetCornerRadius(float r);
	void SetName(const char* s);
    void SetOpaque();
    void SetPixel(int x, int y, unsigned int value);
    void SetDisplayRegion(tcRect r);

    virtual void SetActive(bool abActive);
    void SetBackgroundColor(const osg::Vec4& color);
	void SetBackgroundDraw(bool state);
    void SetResizeable2D(bool abState) {resizeable2DSurface = abState;} ///< @see tc3DWindow::OnSize
	unsigned char GetStencilLayer() const;
	void SetStencilLayer(unsigned char n); ///< set to 0 to deactivate
    virtual void SetYMirror(int y) {yMirror = y;}
    virtual void Thaw();

	static void Set3DViewer(tc3DViewer* aviewer) {viewer = aviewer;}

    tc3DWindow(wxWindow* parent, 
        const wxPoint& pos, const wxSize& size, 
        const wxString& name = "tc3DWindow", tc3DWindow* graphicsHost = 0);
    virtual ~tc3DWindow();
protected:
    std::vector<tc3DWindow*> children;
    std::queue<tc3DWindow*> childrenToRemove; ///< for safe removal of children
    tc3DWindow* const hostParent;

	int baseRenderBin; ///< base offset for render bin for this window
	const int backgroundRenderBin;
	const int imageRenderBin;
	const int lineRenderBin;
	const int rectRenderBin;
	const int textRenderBin;
    const int geometryRenderBin;

    osg::Vec4 backgroundColor;


    wxRect mrectWindow;                       // location for map in back buffer
    int mnWidth;   ///< window dimension--tried to make const, but problem in tcTerrainView
    int mnHeight;
    int yMirror; ///< workaround for opposite y directions of OpenGL vs. wxWindows
    /// true if 2DSurface should be resized with window, normally false for zoomed surfaces
    /// such as with the tcTerrainView
    /// @see tc3DWindow::OnSize view OnSize method code to see how this is used
    bool resizeable2DSurface; 
    bool blendingOn; ///< true to enable alpha blending for window
	float fontSize; ///< default normal font size
	float fontSizeLarge; ///< default large font size
	float fontSizeSmall; ///< default small font size
	float cornerRadius; ///< radius of window corners, use 0 for square corners

	osg::ref_ptr<osgText::Font> defaultFont;

	osg::ref_ptr<osg::Texture2D> backgroundTexture; 
	osg::ref_ptr<osg::Geometry> backgroundQuad;
	osg::ref_ptr<osg::Geometry> border;
	osg::ref_ptr<osg::Texture2D> defaultTexture; 
	osg::ref_ptr<osg::Texture2D> testSymbol;

    bool mbCloned;
    bool mbFrozen;
	bool isMouseCaptured; ///< true if wxWindow::CaptureMouse has been called, false normally
	wxRect normalPosition; ///< normal, non-minimized pos of window
	wxRect iconPosition; ///< minimized, icon pos of window
	const int iconSize;
	unsigned char stencilLayer; ///< Set non-zero to keep window graphics in window (0/off by default)


	static tc3DViewer* viewer;

	virtual void CaptureMouse();
	osg::MatrixTransform* CreateDrawTransform();
    void ClearDrawObjects();
	void FinishDraw();
	void HideUnusedObjects();
    static wxString PrependImagePath(const char* fileName);

    virtual void OnChar(wxKeyEvent& event);
    virtual void OnClose(wxCloseEvent& event);
    virtual void OnEnterWindow(wxMouseEvent& event);
    void OnEraseBackground(wxEraseEvent& event);
    virtual void OnKeyDown(wxKeyEvent& event);    
    virtual void OnKillFocus(wxFocusEvent& event);
    virtual void OnLButtonDown(wxMouseEvent& event);
	virtual void OnLButtonDClick(wxMouseEvent& event);
    virtual void OnLButtonUp(wxMouseEvent& event);
    virtual void OnLeaveWindow(wxMouseEvent& event);
    virtual void OnMouseMove(wxMouseEvent& event);
    virtual void OnMouseWheel(wxMouseEvent& event);    
    virtual void OnMove(wxMoveEvent& event);
	void OnNcPaint(wxNcPaintEvent& event);
    void OnPaint(wxPaintEvent& event);
    virtual void OnRButtonDown(wxMouseEvent& event);
    virtual void OnSetFocus(wxFocusEvent& event);
    virtual void OnShow(wxShowEvent& event);
    virtual void OnSize(wxSizeEvent& event);
	virtual void ReleaseMouse();
    void SkipMouseEvent(wxMouseEvent& event); ///< adjusts position to parent frame
	virtual void UpdatePositionAndSize(const wxPoint& pos, const wxSize& size);

private:
	osg::ref_ptr<osg::MatrixTransform> transform; ///< transform node for 3D draw objects
	osg::ref_ptr<osg::Switch> switchNode; ///< node to enable/disable window
	osg::ref_ptr<osg::Geode> root; ///< root node for drawables 
	osg::ref_ptr<osg::Group> groupRoot; ///< root node for transforms
	osg::ref_ptr<osg::Geode> textRoot; ///< root node for text graphics
	osg::ref_ptr<osg::Geode> backgroundRoot; ///< root node for background graphics
	osg::ref_ptr<osg::Geode> lineRoot; ///< root node for lines and rectangle graphics
    
	osg::ref_ptr<osgText::Text> referenceText; ///< text to make size measurements with

	/* eventually refactor this to use a template vs. recoding
	** a new pool system for each different object type */
	std::vector<osg::ref_ptr<osgText::Text> > textPool;
	unsigned int textIdx;

	std::vector<osg::ref_ptr<osg::Geometry> > imageQuadPool;
	unsigned int imageQuadIdx;

	std::vector<osg::ref_ptr<osg::Geometry> > linePool;
	unsigned int lineIdx;

	std::vector<osg::ref_ptr<osg::Geometry> > rectPool;
	unsigned int rectIdx;

	std::vector<osg::ref_ptr<osg::MatrixTransform> > transformPool;
	unsigned int transformIdx;

	osg::BoundingBox lastTextBoundingBox; ///< bounding box for last text object


	void UpdateBackgroundQuad();
	void UpdateBackgroundShape();

	osg::Geometry* GetImageQuadObject();
	osg::Geometry* GetLineObject();
	osg::Geometry* GetRectObject();
	osgText::Text* GetTextObject();
	osg::MatrixTransform* GetTransformObject();

	void InitGraphicsObjects();
	void LogStatus();
    void UpdateChildren();
	void UpdateStencil();

    DECLARE_EVENT_TABLE()
};

#endif


