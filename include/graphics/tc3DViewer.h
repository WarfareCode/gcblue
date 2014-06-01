/**  
**  @file tc3DViewer.h
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

#ifndef _3DVIEWER_H_
#define _3DVIEWER_H_

#if _MSC_VER > 1000
#pragma once
#endif


#include "wx/wx.h"

#include "tcDateTime.h"
#include "tv_types.h"
#include <vector>
#include <boost/shared_ptr.hpp>
#include "tcRect.h"

class tcSimState;
class tcGameObject;
class tc3DModel;
class tc3DTerrain;
class tcSky;
class tcMapData;
class tcPoint;
class CTVRenderSurface;
class CTVMesh;
class CTVNode;
class CTVParticleSystem;
class CTVScreen2DImmediate;
class CTVGraphicEffect;
class tcTexture2D;
class tcRect;

/**
* Manages OSG 3D scenegraph and camera
*/
class tc3DViewer : public wxWindow
{
public:
    enum FogMode
    {
        FOG_OFF = 0, ///< deactivate fog
        FOG_AIR = 1, ///< for above ground view
        FOG_WATER = 2 ///< for underwater view
    };
#if 0
    osg::ref_ptr<osgUtil::SceneView> sceneView;
    osg::ref_ptr<osgUtil::SceneView> sceneViewFar;
	osg::ref_ptr<osgUtil::SceneView> guiView;
    osg::ref_ptr<osgUtil::SceneView> databaseView; ///< for viewing database objects

    osg::ref_ptr<osg::DisplaySettings> displaySettings;
    osg::ref_ptr<osg::NodeVisitor> updateVisitor;
    osg::ref_ptr<osg::NodeVisitor> updateVisitorFar;

	osg::ref_ptr<osgUtil::CullVisitor> cullVisitor;
	osg::ref_ptr<osg::NodeVisitor> guiUpdateVisitor;
    osg::ref_ptr<osg::FrameStamp> frameStamp;
    osg::ref_ptr<osg::FrameStamp> frameStampFar;
	osg::ref_ptr<osg::FrameStamp> guiFrameStamp;

    osg::ref_ptr<osgText::Text> viewerText; ///< text for debug/basic viewer info display
	osg::ref_ptr<osg::Geometry> border; ///< border graphics
	osg::ref_ptr<osg::MatrixTransform> guiObjects;
    osg::ref_ptr<osg::MatrixTransform> hudObjects; ///< add HUD objects to this transform
    osg::ref_ptr<osg::Projection> orthoProjection; ///< ortho projection for HUD objects
    osg::ref_ptr<osg::Geode> textGeode;
	osg::ref_ptr<osg::Geode> borderGeode;
	osg::ref_ptr<osg::Transform> skyTransform;
    osg::ref_ptr<osg::Group> foggedObjects; ///< fog applied to this group
    osg::ref_ptr<osg::Group> worldObjects; ///< add unit objects to this group
    osg::ref_ptr<osg::Group> rootnode;
    osg::ref_ptr<osg::Group> rootnodeFar;
    osg::ref_ptr<osg::Group> databaseViewGroup;

    osg::ref_ptr<osgParticle::ParticleSystemUpdater> particleSystemUpdater;
	
    osgUtil::Optimizer optimizer;

   // tc3DSky *sky;
    osg::ref_ptr<Sky> sky;
	osg::ref_ptr<osg::Group> skyLights;
	osg::ref_ptr<osg::Group> waterLights;
//	osg::ref_ptr<osgEphemeris::EphemerisModel> sky2;
#endif
    tc3DTerrain* terrainManager;
    tcSky* sky;

    // these methods are copied from tcWindow
    virtual void OnChar(wxKeyEvent& event);
    virtual void OnEnterWindow(wxMouseEvent& event);
    void OnEraseBackground(wxEraseEvent& event);
    virtual void OnKeyDown(wxKeyEvent& event);
    virtual void OnLButtonDown(wxMouseEvent& event);
	virtual void OnLButtonDClick(wxMouseEvent& event);
    virtual void OnLButtonUp(wxMouseEvent& event);
    virtual void OnLeaveWindow(wxMouseEvent& event);
    virtual void OnMouseMove(wxMouseEvent& event);
    virtual void OnMouseWheel(wxMouseEvent& event);    
    virtual void OnMove(wxMoveEvent& event);
    void OnPaint(wxPaintEvent& event);
    virtual void OnRButtonDown(wxMouseEvent& event);
    virtual void OnSize(wxSizeEvent& event);
    void AttachMapData(tcMapData *pMapData);
    void AttachSimState(tcSimState *ss);
    void SkipMouseEvent(wxMouseEvent& event); ///< adjusts position to parent frame
	bool HandleEraseBkgnd(WXHDC hDC); /// override of wxWindow method to eliminate flicker

    //void AddText(osgText::Text *text);
    //void RemoveText(osgText::Text *text);
	void AddDefaultTextObjects();
	void ClearDefaultTextObjects();
	void AddTextObject(int key, const Vec3& pos, float fontSize,
							   const Vec4& color,
							   int alignment);
	void ClearTextObject(int key);
	void ClearTextObjects();
	bool TextObjectExists(int key);
	void UpdateTextObject(int key, const std::string& text);

	//osg::MatrixTransform* CreateDrawTransform();
    void CreateScene();
    void CreateSky();
    void CreateTestGraph();
    void Render();
    void RenderRS();
    void RenderViewerToRS();

    void Freeze();
	float GetCameraAz() {return cameraAz;}
	float GetCameraEl() {return cameraEl;}
	float GetCameraRange() {return cameraRange;}
    Vec3 GetCameraPosition(); 
    double GetGameTime() const {return gameTime;}
	double GetGameTimeStep() const {return gameTime - lastGameTime;}
    const Vec3& GetHookedObjectPositionAndType(unsigned int& classification);
	bool GetTerrainActive() const {return isTerrainActive;}
    bool IsActive() {return isActive;}
    void LoadModel(tcGameObject *obj);
    const tcPoint& GetOrigin() const;

    void SetActive(bool b);
	void SetBorderActive(bool state);
    void SetCameraMode(bool lookAt, bool moveWith);
	void SetClearMode(int modeCode);

    void SetGameTime(double t);
    void SetGeoPosition(double lon_rad, double lat_rad, float alt_m);
    void SetHookID(long id);
    void SetLook(float az, float el);
    void SetCartesianOffset(float x, float y, float z);

	void SetPolarOffset(float az, float el, float range);

	void SetCameraAz(float az);
	void SetCameraEl(float el);
	void SetCameraRange(float range_m);
    void SetCameraSpinRate(float rate);
    void SetDatabaseView(bool state);
    bool GetDatabaseViewState() const;
    void SetDatabaseViewClass(const std::string& databaseClass);
    void SetFogMode(int mode);
	void SetShakeAirCamera(bool state);
	void SetTerrainActive(bool state);
    void SetText(const char *s);
	void SetTextPosition(int positionCode);
    void Swap();
    void ToggleFog();
    void ToggleWireframe();
    void Update(tcDateTime& dateZulu);
    float LonToX(double lon); 
    float LatToY(double lat);
    double XToLon(float x); 
    double YToLat(float y); 



    tc3DViewer(wxWindow *parent, 
        const wxPoint& pos, const wxSize& size, 
        const wxString& name = "tc3DViewer");
    virtual ~tc3DViewer();

private:
    enum WaterMode {SIMPLE = 0, SHADER = 1};
    CTVRenderSurface* renderSurface;
    int rsWidth; ///< width of render surface
    int rsHeight; ///< height of render surface

    bool isFrozen; ///< set true if window has been frozen 
    bool isActive;
	bool isBorderActive;
	bool isTerrainActive;
    bool temporaryTerrainDisable; ///< true to temp stop updating terrain for high altitude object (workaround)

	bool impostorModeActive; ///< true if 3D is in imposter mode
    bool viewWireframe;
    bool useRelativeChildPos;  ///< true to add children as children of parent transform group
    bool shakeAirCamera; ///< true to shake camera for air objects to simulate turbulence
    bool databaseViewEnabled; ///< true for special view mode with database model as target

    tcSimState *simState;
    int mnWidth;
    int mnHeight;
    long hookID;
    double lonOrigin_rad; ///< longitude for x = 0 in 3D world coords
    double latOrigin_rad; ///< latitude for z = 0 in 3D world coords (-z is North)
    double lonToGridX; ///< scale factor to convert to world coords
    double latToGridY; ///< scale factor to convert to world coords
    double gridXToLon; ///< scale factor to convert from world coords
    double gridYToLat; ///< scale factor to convert from world coords
    float shiftDistance; ///< reset origin if camera distance from origin exceeds this
    double gameTime; ///< current game time [s]
	double lastGameTime; ///< game time of previous call to Frame
    float zmin; ///< depth buffer limits
    float zmax;
    float zmid; ///< for split near/far render
    float fov_deg; ///< field of view 
	bool useFarSceneView; ///< true to use two scene views to suppress z-fighting
    bool useSimpleWater; ///< true to always use simple water texture (no shader)
	bool shadowsOn;

    // camera parameters
    bool lookAtTarget; ///< true to make camera point at target
    bool moveWithTarget; ///< true to make camera move with target
    bool usePolarOffset; ///< uses cameraAz, cameraEl, cameraRange for moveWith if true, otherwise use cameraPositionOffset
    double cameraLongitude; ///< lon,lat,alt pos of camera for non moveWith modes
    double cameraLatitude; ///< radians
    float cameraAltitude; ///< meters
    Vec3 cameraPosition; ///< current position of camera
    Vec3 cameraPositionOffset; ///< current position offset of camera rel to target, for moveWith
    Vec3 cameraTarget; ///< point camera is looking at for lookAt modes
	Vec3 cameraTargetOffset; ///< offset for lookAt modes
    Vec3 cameraWalkOffset; ///< offset for simulated turbulence with camera motion
    Vec3 lastWalkOffset;

    float cameraAz; ///< camera azimuth relative to target for moveWith modes
    float cameraEl; ///< camera elevation relative to target for moveWith modes
    float cameraRange; ///< range of camera relative to target for moveWith modes
    float cameraSpinRate; ///< rate in rad/frame to spin camera, use 0 to disable
    unsigned int lastSpinCount; ///< time at which spin az offset was adjusted
    float cameraLookAz; ///< look az for non-lookat modes
    float cameraLookEl; ///< look el for non-lookat modes
    wxPoint clickPoint;  ///< anchor point for mouse look
    float azStart; ///< camera az start for mouse look
    float elStart; ///< camera el start for mouse look
    float lookAzStart;  ///< camera look az start for mouse look
	float lookElStart;  ///< camera look el start for mouse look
    bool isMouseDown;
	//std::map<int, osgText::Text*> textMap;
	tc3DModel* defaultSensorModel; ///< default sensor model for non-ID'd tracks
    tc3DModel* databaseModel; ///< model for database view mode
    CTVParticleSystem* testParticleSystem;
    CTVParticleSystem* waterBubbles;
    Vec3 waterBubblePosition;

    cTV_LIGHT sunLight;
    boost::shared_ptr<tcTexture2D> sunTexture;
    Vec3 sunPosition; ///< relative to camera
    int sunLightId;

	// fog colors
	Vec4 airFog;
    Vec4 waterFog;
	int fogMode;
    bool fogEnabled; ///< true if automatic fog mode enabled, false to disable all fog

    // manual lighting mode params (for lighting experimentation)
    bool overrideLighting;
    Vec4 sunAmbientOverride;
    Vec4 sunDiffuseOverride;
    Vec4 sunSpecularOverride;


	// graphics for buttons (painful, tempting to convert to tc3DWindow2)
    boost::shared_ptr<tcTexture2D> minimizeImage;
    boost::shared_ptr<tcTexture2D> minimizeOverImage;
    boost::shared_ptr<tcTexture2D> maximizeImage;
    boost::shared_ptr<tcTexture2D> maximizeOverImage;
	tcRect minimizeRect;
	tcRect maximizeRect;
	bool mouseOverMinimize;
	bool mouseOverMaximize;


    void CreateLights();
    void CreateParticleEffects();
    CTVMesh* GetHookedMesh();
    WaterMode GetWaterMode() const;
    void InitLight();
	void InitGuiView();
    void InitSceneView(wxPoint pos, wxSize size);
    void InitDatabaseView(const wxPoint& pos, const wxSize& size);
    void InitState();
    void InitText();
	void InitButtons();
    bool MouseEventBypass(wxMouseEvent& event);
    void RenderRSDatabase();
    void RenderWaterRS();
    void RenderViewerToRSDatabase();
    void Render2DRS();
	void DrawButtons(CTVScreen2DImmediate* screen2D);

	void SendMinimizeRequest();
	void SendMaximizeRequest();

    void SetOrigin(double lon, double lat); ///< sets origin of 3D world coordinates
	void UpdateBorder();
    void UpdateCamera();
    void UpdateCameraSpin();
    void UpdateChildModels(tcGameObject *gameObj);
    void UpdateDatabaseView();
	void UpdateFog();
    bool UpdateOrigin();
    void UpdateModels();
    void UpdateProjectionMatrix(const wxSize& windowSize);
	void UpdateSensorModels(unsigned int alliance);
    void UpdateSky(tcDateTime& dateZulu);
    void UpdateRenderSurface(int width_, int height_);
    void UpdateOptions();

    // manual lighting
    void SetOverrideLighting(bool state);

    const Vec4& GetSunAmbientOverride() const;
    void SetSunAmbientOverride(const Vec4& color);
    const Vec4& GetSunDiffuseOverride() const;
    void SetSunDiffuseOverride(const Vec4& color);
    const Vec4& GetSunSpecularOverride() const;
    void SetSunSpecularOverride(const Vec4& color);

    DECLARE_EVENT_TABLE()
};

#endif