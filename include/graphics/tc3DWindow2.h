/**  
**  @file tc3DWindow2.h
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

#ifndef _TC3DWINDOW2_H_
#define _TC3DWINDOW2_H_

#if _MSC_VER > 1000
#pragma once
#endif 

#ifndef WX_PRECOMP
#include "wx/wx.h" 
#endif 
#include <wx/event.h>

#include <queue>
#include <vector>

#include <boost/shared_ptr.hpp>
#include "tv_types.h"

//#include <osg/ref_ptr>
//#include <osgText/Text>

#include "common/simmath.h"

//namespace osg
//{
//	class ClipNode;
//	class DrawPixels;
//	class Geode;
//	class Geometry;
//	class Group;
//	class MatrixTransform;
//	class Projection;
//	class Switch;
//	class Texture2D;
////	class Vec4; // causes C1001, line 2701 compiler error !?
//}


class tcFont;
class tcGeometry;
class tcTexture2D;
class tcTVEngine;
class CTVRenderSurface;



// using directives do not work on gcc, used #defines as workaround
//#define LEFT_BASE_LINE osgText::Text::LEFT_BASE_LINE
//#define LEFT_CENTER osgText::Text::LEFT_CENTER
//#define RIGHT_CENTER osgText::Text::RIGHT_CENTER
//#define CENTER_CENTER osgText::Text::CENTER_CENTER

/**
* Window class for drawing using 3D
* Replacement and generalization of old tc3DWindow that worked with OSG
*/
class tc3DWindow2 : public wxWindow 
{
    friend class tcDraggableWindow;
public:
	enum {CENTER = 0, ALIGN_BOTTOM_LEFT = 1};
	enum {FILL_OFF = 0, FILL_ON = 1};
    enum AlignmentType {LEFT_BASE_LINE = 0, LEFT_CENTER = 1, RIGHT_CENTER = 2, CENTER_CENTER = 3, LEFT_TOP = 4, CENTER_TOP = 5, LEFT_BOTTOM = 6, RIGHT_BASE_LINE = 7};

    bool mbActive;
    tcRect mrectDisplay;

	virtual void DestroyWindow();

    void AddChild(tc3DWindow2* child);
    void RemoveChild(tc3DWindow2* child);

	boost::shared_ptr<tcGeometry> CreateDefaultGeometry();
	boost::shared_ptr<tcGeometry> CreatePieGeometry(float width, float height, float startAngle, float stopAngle, 
											 Vec4& color, int fillMode);
    static boost::shared_ptr<tcGeometry> CreateTexturedSymbol(const char* imageName, float width);

    
    virtual void Draw();

    void DrawToRenderSurface();
    void DrawToScreen();

	void DrawImage(tcTexture2D* texture, float x, float y, float width, float height,
		int alignMode = CENTER);

	/// workaround method for inverted coordinates
	void DrawImageR(tcTexture2D* texture, float x, float y, float width, float height,
		int alignMode = CENTER); 

	void DrawZoomedImage(tcTexture2D* texture, float x, float y, float width, float height,
		const tcRect& r, int alignMode = CENTER);

	/// workaround method for inverted coordinates
	void DrawZoomedImageR(tcTexture2D* texture, float x, float y, float width, float height,
		const tcRect& r, int alignMode = CENTER); 
	
	void DrawImageColored(tcTexture2D* texture, float x, float y, float width, float height,
		const Vec4& color, int alignMode = CENTER);

	/// workaround method for inverted coordinates
	void DrawImageColoredR(tcTexture2D* texture, float x, float y, float width, float height,
		const Vec4& color, int alignMode = CENTER); 


	void DrawLine(float x1, float y1, float x2, float y2, const Vec4& color);

	/// workaround method for inverted coordinates
	void DrawLineR(float x1, float y1, float x2, float y2, const Vec4& color);

    void DrawThickLine(float x1, float y1, float x2, float y2, float w, const Vec4& color);

    void DrawThickLineR(float x1, float y1, float x2, float y2, float w, const Vec4& color);

	void DrawRectangle(float x1, float y1, float width, float height, const Vec4& color,
		int fill = FILL_OFF);

	void DrawRectangle(const tcRect& rect, const Vec4& color,
		int fill = FILL_OFF);

	/// workaround method for inverted coordinates
	void DrawRectangleR(float x1, float y1, float width, float height, const Vec4& color,
		int fill = FILL_OFF);

	/// workaround method for inverted coordinates
	void DrawRectangleR(const tcRect& rect, const Vec4& color,
		int fill = FILL_OFF);

	void DrawThickRectangle(const tcRect& rect, float w, const Vec4& color);
	void DrawThickRectangle(float x1, float y1, float width, float height, float w, const Vec4& color);

	/// workaround method for inverted coordinates
	void DrawThickRectangleR(const tcRect& rect, float w, const Vec4& color);
	void DrawThickRectangleR(float x1, float y1, float width, float height, float w, const Vec4& color);

    void DrawText(const char* s, float x, float y, tcFont* font, 
		const Vec4& color, float fontSize, AlignmentType alignment,
		float maximumWidth = 0.0); 

	/// returns bounding box in r
  //  void DrawText(const char* s, float x, float y, tcFont* font, 
		//const Vec4& color, float fontSize, AlignmentType alignment,
		//float maximumWidth, tcRect& r); 

    void DrawTextInRect(const char* s, const tcRect& r, tcFont* font, 
		const Vec4& color, float fontSize, AlignmentType alignment);

	/// workaround method for inverted coordinates
    void DrawTextR(const char* s, float x, float y, tcFont* font, 
		const Vec4& color, float fontSize, AlignmentType alignment,
		float maximumWidth = 0.0); 

	/// workaround method for inverted coordinates
    void DrawTextR(const char* s, float x, float y, tcFont* font, 
		const Vec4& color, float fontSize, AlignmentType alignment,
		float maximumWidth, tcRect& bb); 

	/// workaround method for inverted coordinates
    void DrawTextInRectR(const char* s, const tcRect& r, tcFont* font, 
		const Vec4& color, float fontSize, AlignmentType alignment);

	void DrawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, const Vec4& color,
		int fill = FILL_OFF);

	void DrawTriangleR(float x1, float y1, float x2, float y2, float x3, float y3, const Vec4& color,
		int fill = FILL_OFF);

	void DrawGeometry(tcGeometry* geometry, float x, float y);

	/// workaround method for inverted coordinates
	void DrawGeometryR(tcGeometry* geometry, float x, float y);

	void DrawGeometryZoom(tcGeometry* geometry, float x, float y, float scale);

	/// workaround method for inverted coordinates
	void DrawGeometryZoomR(tcGeometry* geometry, float x, float y, float scale);

    void DrawPieSection(float x, float y, float rx1, float ry1, float rx2, float ry2,
        float start_angle_rad, float stop_angle_rad, const Vec4& color, int fillMode);

    void DrawPieSectionR(float x, float y, float rx1, float ry1, float rx2, float ry2,
        float start_angle_rad, float stop_angle_rad, const Vec4& color, int fillMode);


    void MeasureText(tcFont* font, float fontSize, const char* s, 
        wxSize& size);
    void WrapTextToWidth(tcFont* font, float fontSize, const char* s, float maxWidth, 
							 wxSize& size, wxString& wrappedText);

    void Erase();
    void EraseOpaque();
    virtual void Freeze();
	tcFont* GetDefaultFont();
    tcFont* GetMonospacedFont();
    tcFont* GetBoldFont();
	tcFont* GetItalicFont();
	const tcRect& GetLastTextBoundingBox() const;
	bool IsActive() const {return mbActive;}
	bool IsBackgroundEnabled() const;
    bool IsSurfaceModified();
	virtual bool IsWindowMinimized() const;
    void LoadBackgroundImage(const char* fileName);
	//static osg::Image* LoadImage(const char* fileName);
	static boost::shared_ptr<tcTexture2D> LoadTexture(const char* fileName);
    static boost::shared_ptr<tcTexture2D> LoadTexture(const char* fileName, int width, int height);
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
    void SetDisplayRegion(tcRect r);

    virtual void SetActive(bool abActive);
    void SetBackgroundColor(const Vec4& color);
	void SetBackgroundDraw(bool state);
    
    void SetBorderColor(const Vec4& color);
    void SetBorderDraw(bool state);

    void SetResizeable2D(bool abState) {resizeable2DSurface = abState;} ///< @see tc3DWindow2::OnSize
	unsigned char GetStencilLayer() const;
	void SetStencilLayer(unsigned char n); ///< set to 0 to deactivate
    virtual void SetYMirror(int y) {yMirror = y;}
    virtual void Thaw();
    bool HandleEraseBkgnd(WXHDC hDC); /// override of wxWindow method to eliminate flicker

    void SetUseRenderSurface(bool state, int margin = 0);
    bool GetUseRenderSurface() const;
    void SetRenderSurfaceUpdateInterval(unsigned int interval);
    void SetCharPropagationLevel(int n);
    void SetLeaveWindowPropagationLevel(int n);

	static void SetImagePath(const std::string& s);
	static void SetEngine(tcTVEngine* engine_) {engine = engine_;}

    tc3DWindow2(wxWindow* parent, 
        const wxPoint& pos, const wxSize& size, 
        const wxString& name = "tc3DWindow2", tc3DWindow2* graphicsHost = 0);
    virtual ~tc3DWindow2();
protected:
    std::vector<tc3DWindow2*> children;
    std::queue<tc3DWindow2*> childrenToRemove; ///< for safe removal of children
    tc3DWindow2* const hostParent;

	int baseRenderBin; ///< base offset for render bin for this window
	const int backgroundRenderBin;
	const int imageRenderBin;
	const int lineRenderBin;
	const int rectRenderBin;
	const int textRenderBin;
    const int geometryRenderBin;

    Vec4 backgroundColor;
    bool drawBackground;
    Vec4 borderColor;
    bool drawBorder;

    wxRect mrectWindow;                       // location for map in back buffer
    int mnWidth;   ///< window dimension--tried to make const, but problem in tcTerrainView
    int mnHeight;
    int yMirror; ///< workaround for opposite y directions of OpenGL vs. wxWindows
    /// true if 2DSurface should be resized with window, normally false for zoomed surfaces
    /// such as with the tcTerrainView
    /// @see tc3DWindow2::OnSize view OnSize method code to see how this is used
    bool resizeable2DSurface; 
    bool blendingOn; ///< true to enable alpha blending for window
	float fontSize; ///< default normal font size
	float fontSizeLarge; ///< default large font size
	float fontSizeSmall; ///< default small font size
	float cornerRadius; ///< radius of window corners, use 0 for square corners

	static boost::shared_ptr<tcFont> defaultFont;
    static boost::shared_ptr<tcFont> monospacedFont;
    static boost::shared_ptr<tcFont> boldFont;
	static boost::shared_ptr<tcFont> italicFont;

	boost::shared_ptr<tcTexture2D> backgroundTexture; 
	boost::shared_ptr<tcGeometry> backgroundQuad;
	boost::shared_ptr<tcGeometry> border;
	boost::shared_ptr<tcTexture2D> defaultTexture; 
	boost::shared_ptr<tcTexture2D> testSymbol;

    bool mbCloned;
    bool mbFrozen;
	wxRect normalPosition; ///< normal, non-minimized pos of window
	wxRect iconPosition; ///< minimized, icon pos of window
	const int iconSize;
	unsigned char stencilLayer; ///< Set non-zero to keep window graphics in window (0/off by default)
    CTVRenderSurface* renderSurface;
    bool drawStarted;

	static tcTVEngine* engine;
    static bool drawingToRenderSurface;
	static std::string imagePath;

	virtual void CaptureMouse();
	//osg::MatrixTransform* CreateDrawTransform();
    void ClearDrawObjects();

    void StartDraw();
	void FinishDraw();

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
	virtual void OnMButtonDown(wxMouseEvent& event);
	virtual void OnMButtonUp(wxMouseEvent& event);
    virtual void OnMouseCaptureLost(wxMouseCaptureLostEvent& event);
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
    struct TextInfo
    {
        std::string s;
        float x;
        float y;
        long fontId;
        int rgba;
        AlignmentType alignment;
        float maximumWidth;
    };
    std::vector<TextInfo> queuedText;

    unsigned int rsUpdateCount; ///< count used for updating RS every N frames for speed
    unsigned int rsLastUpdateCount; ///< count that RS was last updated
    unsigned int rsUpdateInterval; ///< count interval for updating RS, <= 1 is every frame
    bool useRenderSurface;
	bool destroy; ///< flag to delay destruction of window to safe time
    unsigned int charPropagationLevel; ///< set > 0 for default propagation to parent windows
    unsigned int leaveWindowPropagationLevel;

	//boost::shared_ptr<osgText::Text> referenceText; ///< text to make size measurements with

	/* eventually refactor this to use a template vs. recoding
	** a new pool system for each different object type */
	/*std::vector<boost::shared_ptr<osgText::Text> > textPool;
	unsigned int textIdx;

	std::vector<boost::shared_ptr<tcGeometry> > imageQuadPool;
	unsigned int imageQuadIdx;

	std::vector<boost::shared_ptr<tcGeometry> > linePool;
	unsigned int lineIdx;

	std::vector<boost::shared_ptr<tcGeometry> > rectPool;
	unsigned int rectIdx;

	std::vector<boost::shared_ptr<osg::MatrixTransform> > transformPool;
	unsigned int transformIdx;
*/
	tcRect lastTextBoundingBox; ///< bounding box for last text object
    tcPoint origin; ///< x,y offset for this window
    int renderSurfaceMargin; ///< reduce render surface width by this much

    void DrawBackground();
    void DrawBorder();
    void DrawChildren();

    bool FinishDestroy();
    inline const tcPoint& GetOrigin() const;
    inline void GetOrigin(float& dx, float& dy) const;
	void UpdateBackgroundQuad();
	void UpdateBackgroundShape();
    void UpdateOrigin(tcPoint& p) const;

	/*tcGeometry* GetImageQuadObject();
	tcGeometry* GetLineObject();
	tcGeometry* GetRectObject();
	osgText::Text* GetTextObject();
	osg::MatrixTransform* GetTransformObject();*/

	void LogStatus();
    void UpdateChildren();
	void UpdateStencil();

    DECLARE_EVENT_TABLE()
};

#endif


