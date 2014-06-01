/**  
**  @file tc3DViewer.cpp
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
#endif

//#include <GL/glew.h> // to avoid gl.h included before glew.h error
//#include "wx/glcanvas.h"

#include "tc3DViewer.h"
#include "math_constants.h"
#include "tcTVEngine.h"
#include "CTVCamera.h"
#include "CTVMesh.h"
#include "CTVParticleSystem.h"
#include "tcDateTime.h"
#include "tcSkyModel.h"


//#include <osg/AlphaFunc>
//#include <osg/BlendFunc>
//#include <osg/CullStack>
//#include <osg/Depth>
//#include <osg/Fog>
//#include <osg/LineWidth>
//#include <osg/MatrixTransform>
//#include <osg/PolygonMode>
//#include <osg/PositionAttitudeTransform>
//#include <osg/Stencil>
//#include <osgDB/Registry>
//#include <osgDB/ReadFile>
//#include <osgParticle/ParticleSystem>
//#include <osgParticle/ParticleSystemUpdater>
//#include <osgText/Font>
//#include <osgText/Text>
//#include <osgUtil/CullVisitor>
//#include <osgUtil/SceneView>
//#include <osgUtil/UpdateVisitor>
//#include <osgUtil/DisplayRequirementsVisitor>

//#include <osgAL/SoundNode>
//#include <osgAL/SoundRoot>
//#include <osgAL/SoundManager>
//#include <osgAL/SoundState>


#include "ObjectUpdater.h"
#include "tcSimState.h"
#include "tc3DTerrain.h"
#include "tcMapData.h"
#include "tcSky.h"
#include "tc3DModel.h"
//#include "tcParticleEffect.h"
#include "tcSensorTrackIterator.h"
#include "tcDatabase.h"
#include "tcTime.h"
#include "wxcommands.h"
#include "tcMatrix3.h"
#include "CTVAtmosphere.h"
#include "CTVGraphicEffect.h"
#include "tcTexture2D.h"
#include "tc3DWindow2.h"

#if defined(_MSC_VER)
// warning C4312: 'type cast' : conversion from 'WXWidget' to 'HWND' of greater size
#pragma warning( disable : 4312 )
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#endif 

using std::min;
using std::max;

BEGIN_EVENT_TABLE(tc3DViewer, wxWindow)
EVT_MOVE(tc3DViewer::OnMove)
EVT_LEFT_DOWN(tc3DViewer::OnLButtonDown) 
EVT_LEFT_DCLICK(tc3DViewer::OnLButtonDClick)
EVT_LEFT_UP(tc3DViewer::OnLButtonUp)  
EVT_RIGHT_DOWN(tc3DViewer::OnRButtonDown) 
EVT_MOTION(tc3DViewer::OnMouseMove)  
EVT_MOUSEWHEEL(tc3DViewer::OnMouseWheel) 
EVT_KEY_DOWN(tc3DViewer::OnKeyDown)  ///< any key has been pressed  
EVT_CHAR(tc3DViewer::OnChar)  
EVT_ENTER_WINDOW(tc3DViewer::OnEnterWindow)
EVT_LEAVE_WINDOW(tc3DViewer::OnLeaveWindow)
EVT_SIZE(tc3DViewer::OnSize)
END_EVENT_TABLE()


void tc3DViewer::OnChar(wxKeyEvent& event)
{
	int nChar = event.GetKeyCode();


	switch(nChar)
	{
	case 'l':
		if (moveWithTarget)
		{
			SetCameraMode(false, false);
			cameraLookAz = cameraAz + C_PI;
			cameraLookEl = -cameraEl;
		}
		else
		{
			SetCameraMode(true, true);
		}
		break;
	case WXK_UP:
		cameraTargetOffset.y += 1.0f;
		break;
	case WXK_DOWN:
		cameraTargetOffset.y -= 1.0f;
		break;
	case WXK_RIGHT:
		cameraTargetOffset.x += 1.0f;
		break;
	case WXK_LEFT:
		cameraTargetOffset.x -= 1.0f;
		break;
	default:
		event.Skip();
        event.ResumePropagation(1);
	}
}

void tc3DViewer::OnEnterWindow(wxMouseEvent& event)
{
    if (MouseEventBypass(event)) return;

    SetFocus();
}

void tc3DViewer::OnLeaveWindow(wxMouseEvent& event)
{
    if (MouseEventBypass(event)) return;

    isMouseDown = false;

	event.Skip(); // pass up to app level
    event.ResumePropagation(1); // so edge map scroll works
}

void tc3DViewer::OnKeyDown(wxKeyEvent& event)
{
    event.Skip();
}

/**
* Need to generalize this to handle different types of camera
* moves.
*/
void tc3DViewer::OnLButtonDown(wxMouseEvent& event)
{
    if (MouseEventBypass(event)) return;

	if (mouseOverMinimize)
	{
		SendMinimizeRequest();
		return;
	}
	if (mouseOverMaximize)
	{
		SendMaximizeRequest();
		return;
	}

    isMouseDown = true;

    clickPoint = event.GetPosition();
    azStart = cameraAz;
    elStart = cameraEl;

    lookAzStart = cameraLookAz;
    lookElStart = cameraLookEl;
    usePolarOffset = true;
}

void tc3DViewer::OnLButtonDClick(wxMouseEvent& event)
{
    if (MouseEventBypass(event)) return;

	//wxCommandEvent cmd(wxEVT_COMMAND_BUTTON_CLICKED, ID_SET3D);    
	//cmd.SetEventObject(this);
	//cmd.SetExtraLong(0); // 0 to deactivate 3D view

	//AddPendingEvent(cmd);
}

void tc3DViewer::OnLButtonUp(wxMouseEvent& event)
{
    if (MouseEventBypass(event)) return;

    isMouseDown = false;
}

void tc3DViewer::OnMouseMove(wxMouseEvent& event)
{
    if (MouseEventBypass(event)) return;

	event.Skip(); // pass up to app level

	mouseOverMinimize = false;
	mouseOverMaximize = false;

    wxPoint point = event.GetPosition();
    if (isMouseDown)
    {
        const float MAX_EL = 65.0f/180.0f*C_PI; // view problem at higher elevations
        float dAz = 0.02f*(float)(point.x - clickPoint.x);
        float dEl = 0.02f*(float)(point.y - clickPoint.y);

        // update mouselook scene panning
        cameraAz = dAz + azStart;
        cameraEl = dEl + elStart;
        if ( cameraAz < 0) { cameraAz += C_TWOPI;}
        else if ( cameraAz > C_TWOPI) {cameraAz -= C_TWOPI;}
        if (cameraEl < -MAX_EL) {cameraEl = -MAX_EL;}
        else if (cameraEl > MAX_EL) {cameraEl = MAX_EL;}


        // update mouselook scene panning
        cameraLookAz = dAz + lookAzStart;
        cameraLookEl = -dEl + lookElStart;
        if ( cameraLookAz < 0) { cameraLookAz += C_TWOPI;}
        else if ( cameraLookAz > C_TWOPI) {cameraLookAz -= C_TWOPI;}
        if (cameraLookEl < -MAX_EL) {cameraLookEl = -MAX_EL;}
        else if (cameraLookEl > MAX_EL) {cameraLookEl = MAX_EL;}
    }
	else
	{
		if (minimizeRect.ContainsPoint(float(point.x), float(point.y)))
		{
			mouseOverMinimize = true;
		}
		else if (maximizeRect.ContainsPoint(float(point.x), float(point.y)))
		{
			mouseOverMaximize = true;
		}
	}
}

/**
* Adjusts camera zoom
*/
void tc3DViewer::OnMouseWheel(wxMouseEvent& event)
{
    if (MouseEventBypass(event)) return;

    wxPoint point = event.GetPosition();
    int zDelta = event.GetWheelRotation();
    
    if (zDelta > 0) 
    {
        cameraRange *= 0.9f;
        if (cameraRange < 3.0f) cameraRange = 3.0f;
    }
    else if (zDelta < 0) 
    {
        cameraRange *= 1.1f;
    }
}

void tc3DViewer::OnMove(wxMoveEvent& event)
{
}

void tc3DViewer::OnRButtonDown(wxMouseEvent& event)
{
    if (MouseEventBypass(event)) return;
}

/**
* Update projection rectangle for camera. Assumes move has taken place.
*/
void tc3DViewer::OnSize(wxSizeEvent& event)
{
    wxSize size = event.GetSize();
    wxPoint pos = wxWindow::GetPosition();
    //wxWindow *parent = wxWindow::GetParent();
    //wxSize parentSize = parent->GetSize();
    //int parentHeight = parentSize.GetHeight();


    //int correctedY = parentHeight - (pos.y + size.GetHeight());
 //   sceneView->setViewport(pos.x,correctedY, size.GetWidth(),size.GetHeight());

	//if (sceneViewFar.valid())
	//{
	//	sceneViewFar->setViewport(pos.x,correctedY, size.GetWidth(),size.GetHeight());
	//}

    mnWidth = size.GetWidth();
    mnHeight = size.GetHeight();

    UpdateRenderSurface(mnWidth, mnHeight);

    UpdateProjectionMatrix(size);

    // update orthographic projection for HUD objects
    //orthoProjection->setMatrix(osg::Matrix::ortho2D(0,(double)size.GetWidth(),0,(double)size.GetHeight())); 
    //viewerText->setPosition(osg::Vec3(20.0f,(float)mnHeight * 0.9f,0.0f));

	UpdateBorder();

    terrainManager->SetWindowSize(mnWidth, mnHeight);
	
	InitButtons();

   // databaseView->setViewport(pos.x, correctedY, size.GetWidth(), size.GetHeight());
}



// -------- manual lighting mods

void tc3DViewer::SetOverrideLighting(bool state)
{
    overrideLighting = state;
}

const Vec4& tc3DViewer::GetSunAmbientOverride() const
{
    return sunAmbientOverride;
}

void tc3DViewer::SetSunAmbientOverride(const Vec4& color)
{
    sunAmbientOverride = color;
}

const Vec4& tc3DViewer::GetSunDiffuseOverride() const
{
    return sunDiffuseOverride;
}

void tc3DViewer::SetSunDiffuseOverride(const Vec4& color)
{
    sunDiffuseOverride = color;
}

const Vec4& tc3DViewer::GetSunSpecularOverride() const
{
    return sunSpecularOverride;
}

void tc3DViewer::SetSunSpecularOverride(const Vec4& color)
{
    sunSpecularOverride = color;
}




/**
* @param lon longitude in radians
*/
float tc3DViewer::LonToX(double lon) 
{
    return (float)((lon - lonOrigin_rad)*lonToGridX);
}

/**
* @param lat latitude in radians
*/
float tc3DViewer::LatToY(double lat) 
{
    return (float)((lat - latOrigin_rad)*latToGridY);
}

/**
* @param x world coord to convert to longitude
*/
double tc3DViewer::XToLon(float x) 
{
    return x*gridXToLon + lonOrigin_rad;
}

/**
* @param y world coord to convert to latitude
*/
double tc3DViewer::YToLat(float y) 
{
    return y*gridYToLat + latOrigin_rad;
}


bool tc3DViewer::MouseEventBypass(wxMouseEvent& event)
{
    if (!databaseViewEnabled)
    {
        return false;
    }
    else
    {
        event.Skip();
        return true;

        //// check if pos is in center portion of window, bypass if not
        // messy since viewer isn't child of startview
        //wxPoint pos = event.GetPosition();
        //bool inCenter = (pos.x > mnWidth/4) && (pos.x < (3*mnWidth)/4) &&
        //                (pos.y > mnHeight/4) && (pos.y < (3*mnHeight)/4);


        //if (inCenter)
        //{
        //    wxWindow::Raise();
        //    return false;
        //}
        //else
        //{
        //    wxWindow::Lower();
        //    event.Skip();
        //    return true;
        //}
    }
}

void tc3DViewer::SetActive(bool b)
{
	if (isActive == b) return; 

	isActive = b;
	wxWindow::Enable(b);
	wxWindow::Show(b);

    if (b == false)
    {
        databaseModel = false;
    }
}


/**
*
*/
void tc3DViewer::SetCameraMode(bool lookAt, bool moveWith)
{
    lookAtTarget = lookAt;
    moveWithTarget = moveWith;
}

void tc3DViewer::SetCartesianOffset(float x, float y, float z)
{
    cameraPositionOffset.set(x, y, z);
    usePolarOffset = false;
}

/**
* @param modeCode 0 - no clearing, 1 - depth only, 2 - depth and color buffers
*/
void tc3DViewer::SetClearMode(int modeCode)
{
#if 0
    osgUtil::RenderStage* stage = sceneView->getRenderStage();

	if (modeCode == 1)
	{
		stage->setClearMask(GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}
	else if (modeCode == 2)
	{
		if (useFarSceneView)
		{
			stage->setClearMask(GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		}
		else
		{
			stage->setClearMask(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		}
	}
	else
	{
		stage->setClearMask(0);
	}

	if (sceneViewFar.valid())
	{
		osgUtil::RenderStage* stageFar = sceneViewFar->getRenderStage();
		if (modeCode == 1)
		{
			stageFar->setClearMask(GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		}
		else if (modeCode == 2)
		{
			stageFar->setClearMask(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		}
		else
		{
			stageFar->setClearMask(0);
		}
	}
#endif

}

void tc3DViewer::SetDatabaseView(bool state)
{
    if (databaseViewEnabled == state) return;

    databaseViewEnabled = state;

    terrainManager->Enable(!databaseViewEnabled);

    if (!databaseViewEnabled)
    {
        if (testParticleSystem != 0)
        {
            testParticleSystem->Destroy();
            testParticleSystem = 0;
        }

        if (databaseModel != 0)
        {
            databaseModel->Enable(false);
        } 
    }
    else
    {
        SetFogMode(FOG_OFF);
        //CTVScene* scene = tcTVEngine::Get()->GetScene();
        //testParticleSystem = scene->CreateParticleSystem();
        //testParticleSystem->Load("3d\\particle\\fire.tvp");

       
    }
}

void tc3DViewer::SetDatabaseViewClass(const std::string& databaseClass)
{
    // disable previous mesh
    if (databaseModel != 0)
    {
        databaseModel->Enable(false);
    }

    database::tcDatabaseObject* obj = database::tcDatabase::Get()->GetObject(databaseClass);
    if (obj != 0)
    {
        databaseModel = obj->Get3DModel();
        wxASSERT(databaseModel);

		float r = 5.0f + 2.5f * databaseModel->GetRadius();
		r = std::min(r, 400.0f); // so big carriers look better

        SetCameraRange(r);

        if (testParticleSystem != 0)
        {
            testParticleSystem->Destroy();
            testParticleSystem = 0;
        }

        CTVScene* scene = tcTVEngine::Get()->GetScene();
        testParticleSystem = scene->CreateParticleSystem();

        //CTVMesh* mesh = databaseModel->GetMesh();
        //testParticleSystem->Load("3d\\particle\\fire.tvp");
        //testParticleSystem->AttachTo(0, cTV_NODETYPE_MESH, mesh->GetEntityIndex(), 0);

    }
}


void tc3DViewer::UpdateFog()
{
	tcTVEngine* engine = tcTVEngine::Get();
    CTVAtmosphere* atmosphere = engine->GetAtmosphere();

    if (!fogEnabled) fogMode = FOG_OFF;

    if (fogMode == FOG_OFF)
    {
        atmosphere->Fog_SetParameters(10000.0f, 100000.0f, 0.0000001f);
        atmosphere->Fog_Enable(false);
    }
    else if (fogMode == FOG_AIR)
    {
        atmosphere->Fog_SetParameters(1000.0f, 30000.0f, 0.00008f);
        atmosphere->Fog_SetColor(airFog.x, airFog.y, airFog.z);
    }
    else // fogMode == FOG_WATER
    {
        atmosphere->Fog_SetParameters(20.0f, 6000.0f, 0.006f);
        atmosphere->Fog_SetColor(waterFog.x, waterFog.y, waterFog.z);
    }

    if (renderSurface != 0)
	{
		if (fogMode != FOG_OFF)
		{
			renderSurface->SetBackgroundColor(RGBA(waterFog.x, waterFog.y, waterFog.z, 1));
		}
		else
		{
			renderSurface->SetBackgroundColor(0);
		}
    }

}


/**
*
*/
void tc3DViewer::SetFogMode(int mode)
{
//    wxASSERT(foggedObjects.valid());

    if (fogMode == mode) return;

	fogMode = mode;

    UpdateFog();
        
#if 0
    osg::StateSet* fogState = foggedObjects->getOrCreateStateSet();
    osg::Fog* fog = dynamic_cast<osg::Fog*>(fogState->getAttribute(osg::StateAttribute::FOG));
    if (!fog)
    {
        fog = new osg::Fog;
        fogState->setAttributeAndModes(fog, osg::StateAttribute::ON);
    }

	osgUtil::SceneView* view = (useFarSceneView) ? sceneViewFar.get() : sceneView.get();
	wxASSERT(view != 0);

    if (mode == FOG_OFF)
    {
        fogState->setMode(GL_FOG, osg::StateAttribute::OFF);
        view->setClearColor(osg::Vec4(0, 0, 0, 1));
        return;
    }

    fogState->setMode(GL_FOG, osg::StateAttribute::ON);

    fog->setMode(osg::Fog::EXP);

    if (mode == FOG_AIR)
    {
        fog->setColor(airFog); // blue-white fog
        fog->setStart(4000.0f);
        fog->setEnd(60000.0f);
        fog->setDensity(0.000015f); 
		//fog->setFogCoordinateSource(osg::Fog::FRAGMENT_DEPTH);
        view->setClearColor(airFog);
    }
    else
    {
        fog->setColor(waterFog); // dark blue fog   
        fog->setStart(30.0f);
        fog->setEnd(60000.0f);
        fog->setDensity(0.0006f); 
        view->setClearColor(waterFog);
    }
#endif


}

void tc3DViewer::SetGameTime(double t)
{
    lastGameTime = gameTime;

    gameTime = t;
//    terrainManager->SetGameTime(t);
}

/**
* Sets position of camera for non-movewith camera modes.
*/
void tc3DViewer::SetGeoPosition(double lon_rad, double lat_rad, float alt_m)
{
    cameraLongitude = lon_rad;
    cameraLatitude = lat_rad;
    cameraAltitude = alt_m;

    float x = LonToX(cameraLongitude);
    float y = LatToY(cameraLatitude);
    float z = cameraAltitude;

    cameraPosition.set(x,y,z);
}

void tc3DViewer::SetHookID(long id)
{
    hookID = id;
    cameraWalkOffset.set(0, 0, 0);
}

void tc3DViewer::SetLook(float az, float el)
{
    cameraLookAz = az;
    cameraLookEl = el;
}


void tc3DViewer::SetPolarOffset(float az, float el, float range)
{
    cameraAz = az;
    cameraEl = el;
    cameraRange = range;
    usePolarOffset = true;
}

void tc3DViewer::SetBorderActive(bool state)
{
	if (isBorderActive == state) return; // ignore if state not changed

#if 0
	if ((!borderGeode.valid()) || (!border.valid())) return;


	size_t nParents = border->getNumParents();

	if (state)
	{
		if (nParents == 0)
		{
			borderGeode->addDrawable(border.get());
		}
	}
	else
	{
		if (nParents > 0)
		{
			borderGeode->removeDrawable(border.get());
		}
	}
#endif

	isBorderActive = state;
}

/**
* @param az camera az in radians for lookat modes
*/
void tc3DViewer::SetCameraAz(float az)
{
	cameraAz = az;
}

/**
* @param el camera el in radians for lookat modes
*/
void tc3DViewer::SetCameraEl(float el)
{
	cameraEl = el;
}

/**
* @param range_m camera range in meters for lookat modes
*/
void tc3DViewer::SetCameraRange(float range_m)
{
	cameraRange = range_m;
}

void tc3DViewer::SetCameraSpinRate(float rate)
{
    cameraSpinRate = rate;
}

/**
* Set the origin (0,0) of 3D world coordinates and
* update lonToGridX and gridXToLon scale factors which 
* change as a function of latitude.
*/
void tc3DViewer::SetOrigin(double lon, double lat)
{

    lonOrigin_rad = lon;
    latOrigin_rad = lat;

    lonToGridX = C_RADTOM*cosf(latOrigin_rad);
    gridXToLon = 1/lonToGridX;

	if (isTerrainActive && (!temporaryTerrainDisable))
	{
		terrainManager->SetOrigin(lon, lat);
	}

//	if (sky.valid())
	{
		wxASSERT(simState != 0);
		tcDateTime dt = simState->GetDateTime();
		//sky->update(latOrigin_rad, lonOrigin_rad, dz);
	}
}

#if 0
osg::AnimationPath* createAnimationPath(double looptime)
{
    osg::Vec3 center(0.0f,0.0f,0.0f);
    float radius = 10.0f;
    // set up the animation path 
    osg::AnimationPath* animationPath = new osg::AnimationPath;
    animationPath->setLoopMode(osg::AnimationPath::LOOP);

    int numSamples = 40;
    float yaw = 0.0f;
    float yaw_delta = 2.0f*osg::PI/((float)numSamples-1.0f);
    float roll = osg::inDegrees(30.0f);

    double time=0.0f;
    double time_delta = looptime/(double)numSamples;
    for(int i=0;i<numSamples;++i)
    {
        osg::Vec3 position(center+osg::Vec3(sinf(yaw)*radius,cosf(yaw)*radius,0.0f));
        osg::Quat rotation(osg::Quat(roll,osg::Vec3(0.0,1.0,0.0))*osg::Quat(-(yaw+osg::inDegrees(90.0f)),osg::Vec3(0.0,0.0,1.0)));

        animationPath->insert(time,osg::AnimationPath::ControlPoint(position,rotation));

        yaw += yaw_delta;
        time += time_delta;

    }
    return animationPath;    
}

#endif

void tc3DViewer::AttachMapData(tcMapData *pMapData)
{
    terrainManager->AttachMapData(pMapData);
}


void tc3DViewer::AttachSimState(tcSimState *ss) 
{
	simState = ss;
}


#if 0
/**
* Adds text drawable to textGeode. Take care with reference count 
* issues with doing it this way.
*/
void tc3DViewer::AddText(osgText::Text *text)
{
    textGeode->addDrawable(text);
}


void tc3DViewer::RemoveText(osgText::Text *text)
{
    textGeode->removeDrawable(text);
}
#endif

void tc3DViewer::CreateLights()
{
    tcTVEngine* engine = tcTVEngine::Get();

    CTVLightEngine* lightEngine = engine->GetLightEngine();

    cTV_COLOR s;
    sunLight.ambient = cTV_COLOR(0.15f, 0.15f, 0.15f, 1.0);
    sunLight.diffuse = cTV_COLOR(0.5f, 0.5f, 0.3f, 1.0);
    sunLight.specular = cTV_COLOR(0.0, 0, 0.4f, 1.0);
    sunLight.type = cTV_LIGHT_DIRECTIONAL;
    sunLight.direction = Vec3(1, 1, 1);
    sunLight.direction /= sunLight.direction.Length();

    sunLightId = lightEngine->CreateLight(&sunLight, "SunLight");
	
	//lightEngine->SetLightProperties(sunLightId, bool bManagedLight, bool bCastShadows, bool bUseForLightmapping);
    lightEngine->SetLightProperties(sunLightId, false, shadowsOn, false);

    CTVScene* scene = tcTVEngine::Get()->GetScene();
    scene->SetShadowParameters(RGBA(0, 0, 0, 0.5f), false);
}

void tc3DViewer::CreateParticleEffects()
{
    CTVScene* scene = tcTVEngine::Get()->GetScene();
    waterBubbles = scene->CreateParticleSystem();
    waterBubbles->Load("3d\\particle\\bubbles.tvp");
    waterBubbles->SetEmitterEnable(0, false);

    waterBubbles->SetEmitterPosition(0, &waterBubblePosition);

    //waterBubbles->AttachTo(0, cTV_NODETYPE_CAMERA, scene->GetCamera()->GetCameraIndex(), 0, false);

}


void tc3DViewer::CreateScene()
{
    //static boost::shared_ptr<CTVMesh> teapot;

    tcTVEngine* engine = tcTVEngine::Get();
//    CTVScene* scene = engine->GetScene();

    //teapot = boost::shared_ptr<CTVMesh>(scene->CreateMeshBuilder("Teapot"));
    //teapot->CreateTeapot();

    /*teapot = boost::shared_ptr<CTVMesh>(scene->CreateMeshBuilder("air_small"));
    if (!teapot->LoadTVM("3d\\air_small.tvm", true, true))
    {
        wxASSERT(false);
    }



    teapot->SetPosition(0, 3, 30);
    teapot->SetScale(1.0, 1.0, 1.0);

    tcMatrix3 R;
    R.SetYawPitchRoll(0, 0, 0);
    teapot->SetRotationMatrix(R.GetMatrix());*/


    CTVCamera* camera = engine->GetCamera();


    camera->SetPosition(0, 5, 0);
    camera->SetLookAt(0, 3, 30);

    terrainManager = new tc3DTerrain();
    terrainManager->SetWindowSize(mnWidth, mnHeight);


    CTVAtmosphere* atmosphere = engine->GetAtmosphere();

    sunTexture = boost::shared_ptr<tcTexture2D>(new tcTexture2D("3d\\sun.png"));
    atmosphere->Sun_Enable(true);
    atmosphere->Sun_SetTexture(sunTexture->GetId());
    atmosphere->Sun_SetBillboardSize(4);
    atmosphere->Sun_SetPosition(500, 10, 500);
    atmosphere->Sun_SetBlendingMode(cTV_BLEND_ALPHA);
    atmosphere->Sun_SetColor(1.0f, 1.0f, 0.9f, 0.9f);
   


    atmosphere->SkyBox_Enable(false);
    atmosphere->SkySphere_Enable(false);

    //tcTexture2D back("tvm_test\\sunset\\Back.jpg");
    //tcTexture2D bottom("tvm_test\\sunset\\Down.jpg");
    //tcTexture2D front("tvm_test\\sunset\\Front.jpg");
    //tcTexture2D left("tvm_test\\sunset\\Left.jpg");
    //tcTexture2D right("tvm_test\\sunset\\Right.jpg");
    //tcTexture2D top("tvm_test\\sunset\\Up.jpg");

//    atmosphere->SkyBox_SetTexture(front.GetId(), back.GetId(), left.GetId(), right.GetId(), top.GetId(), bottom.GetId());
    //atmosphere->SkySphere_SetColor(0.1f, 0.1f, 0.5f, 1.0f);
    //atmosphere->SkySphere_Enable(true);


    tcTexture2D cloud("images\\clouds.dds");
    atmosphere->Clouds_Create(1, 100000, 100000);
    atmosphere->Clouds_SetLayerParameters(0, 4000.0f, cloud.GetId(), 10.0f, 10.0f);
    atmosphere->Clouds_Enable(true);

    atmosphere->Fog_Enable(true);
    atmosphere->Fog_SetType(cTV_FOG_EXP, cTV_FOGTYPE_PIXEL);
    atmosphere->Fog_SetParameters(1000.0f, 50000.0f, 0.001f);
    atmosphere->Fog_SetColor(0.3f, 0.3f, 0.6f);

    CreateSky();

    UpdateProjectionMatrix(wxSize(mnWidth, mnHeight));
    //camera->SetViewFrustum(fov_deg, zmax, zmin);

    CreateLights();

    CreateParticleEffects();


#if 0
	foggedObjects = new osg::Group;

    SetFogMode(FOG_AIR);
    /*
    osg::Fog *fog = new osg::Fog();
    fog->setColor(osg::Vec4(0.6f, 0.7f, 0.8f, 1.0f)); // blue-white fog
   
    fog->setMode(osg::Fog::EXP);
    fog->setStart(5000.0f);
    fog->setEnd(60000.0f);
    fog->setDensity(0.000006f); 
    */


 /*
    fog->setMode(osg::Fog::LINEAR);
    fog->setStart(5000.0f);
    fog->setEnd(60000.0f);
    fog->setDensity(0.000001f); 
 */

    /*
    osg::StateSet *fogState = foggedObjects->getOrCreateStateSet();
	fogState->setAttributeAndModes(fog, osg::StateAttribute::ON);
	foggedObjects->setStateSet(fogState);
    */
    {
        worldObjects = new osg::Group;

        osg::StateSet *objectState = worldObjects->getOrCreateStateSet();
        osg::BlendFunc *blendFunction = new osg::BlendFunc;
	    blendFunction->setFunction(osg::BlendFunc::SRC_ALPHA, osg::BlendFunc::ONE_MINUS_SRC_ALPHA);
	    objectState->setAttributeAndModes(blendFunction, osg::StateAttribute::ON);

 
       // osg::Depth* depth = new osg::Depth(osg::Depth::LESS, zmin, zmax);
       // objectState->setAttributeAndModes(depth, osg::StateAttribute::OFF );
    }




    osg::ref_ptr<osg::Node> terrainNode = terrainManager->GetTerrainNode().get();

    
    osg::StateSet *terrainState = terrainNode->getOrCreateStateSet();
    terrainState->setMode(GL_LIGHTING, osg::StateAttribute::ON);
	terrainState->setMode(GL_FOG, osg::StateAttribute::ON);
    terrainState->setMode(GL_CULL_FACE, osg::StateAttribute::OFF);
    
    osg::Depth* depth = new osg::Depth;
    depth->setFunction(osg::Depth::LESS);
    depth->setRange(0, 1);   
    depth->setWriteMask(true);
	terrainState->setAttributeAndModes(depth, osg::StateAttribute::ON);
    
    terrainState->setRenderBinDetails(-2, "RenderBin");
    terrainNode->setCullingActive(false);

    //osg::Depth* tdepth = new osg::Depth(osg::Depth::LESS, 2.0, 200000.0);
    //terrainState->setAttributeAndModes(tdepth, osg::StateAttribute::ON );

	skyTransform = new osg::PositionAttitudeTransform;

    CreateSky();

    InitText();
	UpdateBorder();

    skyTransform->addChild(sky.get());
	skyTransform->setCullingActive(false);

    foggedObjects->addChild(worldObjects.get());
    foggedObjects->addChild(terrainNode.get());
    foggedObjects->addChild(skyLights.get());
    tc3DModel::SetWorldFrame(rootnode.get());


    rootnode->addChild(foggedObjects.get());

	//rootnode->addChild(sky2.get());

    //rootnodeFar->addChild(skyTransform.get());

	//if (useFarSceneView)
	//{
	//	rootnodeFar->addChild(skyTransform.get());
	//}

    /* For some strange reason, adding the orthoProjection to
    ** rootnodeFar causes line and rect objects in the guiView
    ** (a DIFFERENT SceneView) to drop out.
    ** Adding to rootnode causes a double image of the hud objects,
    ** but this is the lesser of evils.
    ** TODO investigate this. There may be a significant problem 
    ** lurking here. */
    rootnode->addChild(orthoProjection.get()); 
#endif
	isTerrainActive = true;
}

void tc3DViewer::CreateSky() 
{
    sky = new tcSky();
    sky->SetRadius(0.9f*zmax);
    sky->BuildSkyDome();

}

void tc3DViewer::CreateTestGraph()
{
#if 0
    if (!rootnode) return;
    osg::Group* model = new osg::Group;
    //osg::Node* glider = osgDB::readNodeFile("cessna.osg");
    osg::Node* glider = osgDB::readNodeFile("hermes.3ds");
    if (glider)
    {
        const osg::BoundingSphere& bs = glider->getBound();

        float size = 1.0f;
        osg::MatrixTransform* positioned = new osg::MatrixTransform;
        positioned->setDataVariance(osg::Object::STATIC);

        positioned->setMatrix(osg::Matrix::translate(-bs.center())*
            osg::Matrix::scale(size,size,size)*
            osg::Matrix::rotate(osg::inDegrees(0.0f),0.0f,0.0f,1.0f));


        positioned->addChild(glider);        
        osg::PositionAttitudeTransform* xform = new osg::PositionAttitudeTransform; 
//        osg::AnimationPath* animationPath = createAnimationPath(10.0f);   
        //xform->setUpdateCallback(new osg::AnimationPathCallback(animationPath,0.0,1.0));
        xform->setUpdateCallback(new ObjectUpdater());
        xform->addChild(positioned);
        model->addChild(xform);
    }

    worldObjects->addChild(model);
#endif
}


void tc3DViewer::DrawButtons(CTVScreen2DImmediate* screen2D)
{
//    const float h = float(mnHeight);
//    const float w = float(mnWidth);

	long minTexId = mouseOverMinimize ? minimizeOverImage->GetId() : minimizeImage->GetId();
	long maxTexId = mouseOverMaximize ? maximizeOverImage->GetId() : maximizeImage->GetId();
	

	screen2D->Draw_Texture(minTexId, minimizeRect.left, minimizeRect.bottom, 
		minimizeRect.right, minimizeRect.top);

	screen2D->Draw_Texture(maxTexId, maximizeRect.left, maximizeRect.bottom, 
		maximizeRect.right, maximizeRect.top);

	
}

/**
* Render to render surface. Call before engine->Clear()
*/
void tc3DViewer::RenderRS()
{
    if (renderSurface == 0) return;

    if (databaseViewEnabled)
    {
        RenderRSDatabase();
        return;
    }

    //tcTVEngine* engine = tcTVEngine::Get();
//    CTVScene* scene = engine->GetScene();


//    CTVCamera* camera = engine->GetCamera();
    //Vec3 cameraPosition = camera->GetPosition();

    terrainManager->UpdateCameraPosition(cameraPosition);
    sky->UpdateCameraPosition(cameraPosition);

    RenderWaterRS();

    RenderViewerToRS();
}

/**
* Do rendering for water reflection and refraction render surfaces
*/
void tc3DViewer::RenderWaterRS()
{
    tcTVEngine* engine = tcTVEngine::Get();
    CTVScene* scene = engine->GetScene();
    CTVRenderSurface* waterReflection = terrainManager->GetReflectionRS();
    CTVRenderSurface* waterRefraction = terrainManager->GetRefractionRS();
    CTVLandscape* landscape = terrainManager->GetLandscape();
    CTVAtmosphere* atmosphere = engine->GetAtmosphere();
    CTVMesh* water = terrainManager->GetWaterMesh();
//    CTVGraphicEffect* waterEffect = terrainManager->GetWaterEffect();

    water->Enable(false);

    WaterMode waterMode = GetWaterMode();
    if (waterMode == SIMPLE)
    {
        return;
    }

    if (waterReflection == 0) return;
    

    // --- render reflection ---
    // -------------------------

    waterReflection->StartRender(false);

    // render sky
    //camera->SetPosition(0, cameraPosition.y, 0);


    atmosphere->Fog_Enable(false);
    engine->DisableZBuffer();
    sky->Render();
    engine->EnableZBuffer();

    atmosphere->Fog_Enable(true);
    landscape->Render();
    atmosphere->Clouds_Render();
    scene->RenderAllMeshes(false);

    waterReflection->EndRender();

    if (cameraPosition.y < 1000)
    {
        if (waterRefraction == 0)
        {
            return;
        }

        // --- render refraction ---
        // -------------------------
        waterRefraction->StartRender(false);


        // render sky
        atmosphere->Fog_Enable(false);
        engine->DisableZBuffer();
        sky->Render();    
        engine->EnableZBuffer();
        atmosphere->Fog_Enable(true);


        landscape->Render();
        atmosphere->Clouds_Render();
        scene->RenderAllMeshes(false);

        waterRefraction->EndRender();
    }
    else
    {
        waterRefraction->StartRender(false); // do start/end to clear RS
        waterRefraction->EndRender();
    }

}

/**
* Call this after rendering all 3D
*/
void tc3DViewer::Render2DRS()
{
    const float h = float(mnHeight);
    const float w = float(mnWidth);

    tcTVEngine* engine = tcTVEngine::Get();
    CTVScreen2DImmediate* screen2D = engine->GetScreen2D();

    screen2D->Action_Begin2D();

	DrawButtons(screen2D);

    if (isBorderActive)
    {
        screen2D->Draw_Box(0, 0, w-4, h-1, RGBA(1, 1, 1, 1));
    }

    screen2D->Action_End2D();
}

/**
* Database view mode
*/
void tc3DViewer::RenderRSDatabase()
{
    //tcTVEngine* engine = tcTVEngine::Get();
    //CTVViewport* viewport = engine->GetViewport();
//    CTVScene* scene = engine->GetScene();

//    int startWidth = viewport->GetWidth();
//    int startHeight = viewport->GetHeight();

    wxPoint pos = GetPosition();
    wxSize size = GetSize();

    //scene->RenderAllMeshes(false);

    if (databaseModel != 0) 
    {
        databaseModel->Render();
    }

    RenderViewerToRSDatabase();
}


void tc3DViewer::RenderViewerToRS()
{
    static unsigned renderCount = 0;

    if (renderCount++ % 100 == 0)
    {
        UpdateOptions();
    }

    renderSurface->StartRender(false);

    tcTVEngine* engine = tcTVEngine::Get();

    //CTVViewport* viewport = engine->GetViewport();
//    int startWidth = viewport->GetWidth();
//    int startHeight = viewport->GetHeight();

    wxPoint pos = GetPosition();
    wxSize size = GetSize();
    //viewport->SetTargetArea(pos.x, pos.y, size.GetWidth(), size.GetHeight());

    

    CTVAtmosphere* atmosphere = engine->GetAtmosphere();
    CTVLandscape* landscape = terrainManager->GetLandscape();


    WaterMode waterMode = GetWaterMode();
    CTVMesh* water = 0;
    if (waterMode == SIMPLE)
    {    
        water = terrainManager->GetSimpleWaterMesh();
        terrainManager->GetWaterMesh()->Enable(false);
    }
    else
    {
        water = terrainManager->GetWaterMesh();
        terrainManager->GetSimpleWaterMesh()->Enable(false);
    }

    CTVScene* scene = engine->GetScene();


    CTVCamera* camera = engine->GetCamera();
    Vec3 cameraPosition = camera->GetPosition();
    
    bool aboveWater = cameraPosition.y > -1.0f;

    if (useFarSceneView)
    {
        // -------- far view ---------
        camera->SetViewFrustum(fov_deg, zmax, zmid-10.0f);

        
        if (aboveWater)
        {
            atmosphere->Fog_Enable(false);
            engine->DisableZBuffer();
            sky->Render();
            atmosphere->Atmosphere_Render();
            engine->EnableZBuffer();
            atmosphere->Fog_Enable(true);
        }
		else
		{

		}

		atmosphere->Fog_Enable(true);

        landscape->Render();

        //atmosphere->Fog_Enable(false);
        //atmosphere->Fog_SetType(cTV_FOG_EXP, cTV_FOGTYPE_PIXEL);
        water->Enable(true);
        water->Render();
        water->Enable(false);
        
        //atmosphere->Fog_SetType(cTV_FOG_EXP, cTV_FOGTYPE_VERTEX);

        //atmosphere->Clouds_Render();


        scene->RenderAll(true);

        // -------- near view ---------

        engine->ClearZBuffer();

        camera->SetViewFrustum(fov_deg, zmid+10.0f, zmin);
    }
    else // single render
    {
        if (aboveWater)
        {
            atmosphere->Fog_Enable(false);
            engine->DisableZBuffer();
            sky->Render();
            atmosphere->Atmosphere_Render();
            engine->EnableZBuffer();
            atmosphere->Fog_Enable(true);
        }
		else
		{

		}
    }


    landscape->Render();


	CTVLightEngine* lightEngine = engine->GetLightEngine();
	sunLight.direction = -sunLight.direction;
	lightEngine->SetLight(sunLightId, &sunLight);

	if (shadowsOn)
	{
		scene->FinalizeShadows();
	}

	sunLight.direction = -sunLight.direction;
	lightEngine->SetLight(sunLightId, &sunLight);

    //atmosphere->Fog_SetType(cTV_FOG_EXP, cTV_FOGTYPE_PIXEL);
    water->Enable(true);
    water->Render();
    water->Enable(false);
    //atmosphere->Fog_SetType(cTV_FOG_EXP, cTV_FOGTYPE_VERTEX);
    //atmosphere->Atmosphere_Render();
    //atmosphere->Clouds_Render();



    scene->RenderAll(true);


    Render2DRS();

    renderSurface->EndRender();

}

void tc3DViewer::RenderViewerToRSDatabase()
{
    static unsigned renderCount = 0;

    if (renderCount++ % 100 == 0)
    {
        UpdateOptions();
    }

    renderSurface->StartRender(false);


    tcTVEngine* engine = tcTVEngine::Get();

    //CTVViewport* viewport = engine->GetViewport();
//    int startWidth = viewport->GetWidth();
//    int startHeight = viewport->GetHeight();

    wxPoint pos = GetPosition();
    wxSize size = GetSize();
   
//    CTVAtmosphere* atmosphere = engine->GetAtmosphere();
    CTVScene* scene = engine->GetScene();
    CTVCamera* camera = engine->GetCamera();
    Vec3 cameraPosition = camera->GetPosition();
    

    if (useFarSceneView)
    {
        // -------- far view ---------
        camera->SetViewFrustum(fov_deg, zmax, zmid-10.0f);

        scene->RenderAll(false);

        // -------- near view ---------

        engine->ClearZBuffer();

        camera->SetViewFrustum(fov_deg, zmid+10.0f, zmin);
    }
    else // single render
    {
    }

    scene->RenderAll(false);
    if (testParticleSystem != 0)
    {
        testParticleSystem->Render();
    }

    renderSurface->EndRender();
}




void tc3DViewer::Render()
{
    tcTVEngine* engine = tcTVEngine::Get();

    if (renderSurface == 0) return;

    wxPoint pos = GetPosition();
    wxSize size = GetSize();

    CTVScreen2DImmediate* screen2D = engine->GetScreen2D();

    //engine->DisableAlphaBlend();

    screen2D->Action_Begin2D();
    
    if ((pos.x > 210) && (!databaseViewEnabled))
    {
        // workaround for odd undesired alpha blending
        screen2D->Draw_FilledBox(pos.x, pos.y, pos.x+size.GetWidth(), pos.y+size.GetHeight(), RGBA(0,0,0,1));
    }


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
		tu2 = float(mnWidth) / float(renderSurface->GetWidth());
		tv2 = float(mnHeight) / float(renderSurface->GetHeight());
	}


    screen2D->Draw_Texture(renderSurface->GetTexture(), pos.x, pos.y, pos.x+size.GetWidth(), pos.y+size.GetHeight(),
		-1, -2, -2, -2,
		0, 0, tu2, tv2);

    screen2D->Action_End2D();

    //engine->EnableAlphaBlend();

	//lastGameTime = gameTime;
}



void tc3DViewer::SendMinimizeRequest()
{
	wxCommandEvent command(wxEVT_COMMAND_BUTTON_CLICKED, ID_MINIMIZE3D);
	command.SetEventObject(this);
    command.SetExtraLong(-1);
	AddPendingEvent(command);
}

void tc3DViewer::SendMaximizeRequest()
{
	wxCommandEvent command(wxEVT_COMMAND_BUTTON_CLICKED, ID_MAXIMIZE3D);
	command.SetEventObject(this);
	command.SetExtraLong(-1);
	AddPendingEvent(command);
}


/**
* Override of wxWindow::Freeze.
* Call before size event to prevent flicker.
* viewer is thawed automatically in Frame() method
*/
void tc3DViewer::Freeze()
{
    if (isFrozen) return; // already frozen, return
    isFrozen = true;
    wxWindow::Freeze();
}

/**
* Loads OSG model for object, setting obj->model field.
*/
void tc3DViewer::LoadModel(tcGameObject *obj)
{
#if 0
    if (obj->model.valid()) return; // model already loaded
    obj->model = new osg::Group;
    std::string model_name = obj->mpDBObject->mz3DModelFileName.mz;
    model_name = model_name + ".3ds";
    osg::ref_ptr<osg::Node> node = osgDB::readNodeFile(model_name.c_str());
    if (node.valid())
    {
        osg::ref_ptr<osg::MatrixTransform> positioned = new osg::MatrixTransform;
        positioned->setDataVariance(osg::Object::DYNAMIC);
        positioned->addChild(node.get());
        positioned->setUpdateCallback(new ObjectUpdater(obj));

        obj->model->addChild(positioned.get());
        fprintf(stdout,"Loaded 3D model: %s\n", model_name.c_str());

    }
    else
    {
        fprintf(stderr,"Error loading 3D model: %s\n", model_name.c_str());
    }
#endif
}



void tc3DViewer::UpdateBorder()
{
#if 0
	if (!borderGeode.valid())
	{
		borderGeode = new osg::Geode;
		hudObjects->addChild(borderGeode.get());
	}
	wxASSERT(borderGeode.valid());

	if (!border.valid())
	{
		border = new osg::Geometry;
		osg::Vec4Array* colors = new osg::Vec4Array;
		colors->push_back(osg::Vec4(1.0f, 1.0f, 1.0f, 0.7f)); // sets border color
		border->setColorArray(colors);
		border->setColorBinding(osg::Geometry::BIND_OVERALL);
		border->setUseDisplayList(true);

		// set state
		osg::StateSet* stateSet = border->getOrCreateStateSet();
		stateSet->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF);
		stateSet->setMode(GL_DEPTH_WRITEMASK, osg::StateAttribute::OFF);
		stateSet->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
		stateSet->setMode(GL_BLEND, osg::StateAttribute::ON);
		// osg::LineWidth  *lw = new osg::LineWidth(1.5);
		// stateSet->setAttribute(lw, osg::StateAttribute::ON);

		borderGeode->addDrawable(border.get());
		isBorderActive = true;
	}

    // create vertex array
	osg::Vec3Array* vertices = new osg::Vec3Array;
	border->setVertexArray(vertices);

	float w = float(mnWidth-1);
	float h = float(mnHeight-1);

	vertices->push_back(osg::Vec3(0, 0, 0));
	vertices->push_back(osg::Vec3(0, h, 0));
	vertices->push_back(osg::Vec3(w, h, 0));
	vertices->push_back(osg::Vec3(w, 0, 0));
	border->addPrimitiveSet(new osg::DrawArrays(GL_LINE_LOOP,0,4));
#endif
}


/**
* Version for 3D database object view
*/
void tc3DViewer::UpdateDatabaseView()
{
    if (databaseModel == 0) return;

    tcTVEngine* engine = tcTVEngine::Get();
    CTVCamera* camera = engine->GetCamera();

    const float yOffset = -150.0f; ///< to work around artifacts left at origin

    databaseModel->Enable(true);
    databaseModel->SetPosition(0, yOffset, 0);
    UpdateCameraSpin();


    float camx = cameraRange*cosf(cameraEl)*sinf(cameraAz);
    float camz = cameraRange*cosf(cameraEl)*cosf(cameraAz);
    float camy = cameraRange*sinf(cameraEl) + yOffset;

    cameraPosition = Vec3(camx,camy,camz);


    camera->SetPosition(cameraPosition.x, cameraPosition.y, cameraPosition.z);
    camera->SetLookAt(0, yOffset, 0);




    sunLight.position.set(10000.0f, 10000.0f, 10000.0f);
    sunLight.direction.set(1.0f, 1.0f, 1.0f);
	sunLight.direction /= sunLight.direction.Length();

	sunLight.ambient = cTV_COLOR(0.5f, 0.5f, 0.5f, 1.0f);
    sunLight.diffuse = cTV_COLOR(0.9f, 0.8f, 0.6f, 1.0f);
    sunLight.specular = cTV_COLOR(1.0f, 1.0f, 1.0f, 1.0f);

    CTVLightEngine* lightEngine = engine->GetLightEngine();
    lightEngine->SetLight(sunLightId, &sunLight);

    //testParticleSystem->Update();

#if 0
    float camx = cosf(cameraEl)*sinf(cameraAz);
    float camy = cosf(cameraEl)*cosf(cameraAz);
    float camz = sinf(cameraEl);
    cameraPosition = osg::Vec3(camx,camy,camz)*cameraRange;

    cameraTarget = cameraTargetOffset;

    databaseView->setViewMatrixAsLookAt(cameraPosition, cameraTarget, osg::Vec3(0,0,1));
#endif

}

void tc3DViewer::UpdateCamera()
{
    tcTVEngine* engine = tcTVEngine::Get();
    CTVCamera* camera = engine->GetCamera();

	unsigned int objClassification;
    Vec3 targetPosition = GetHookedObjectPositionAndType(objClassification);

    UpdateCameraSpin();
    Vec3 cameraOffset(0, 0, 0);


    if (moveWithTarget)
    {
        if (usePolarOffset)
        {
            float camx = cosf(cameraEl)*sinf(cameraAz);
            float camz = cosf(cameraEl)*cosf(cameraAz);
            float camy = sinf(cameraEl);

            cameraOffset = Vec3(camx,camy,camz)*cameraRange;

            cameraPosition = targetPosition + cameraOffset;
        }
        else
        {
            cameraOffset = cameraPositionOffset;

            cameraPosition = targetPosition + cameraOffset;
        }
    }
    else
    {
        // cameraPosition = GetCameraPosition(); // leave camera at pos set by SetGeoPosiiton
    }




    // limit min camera altitude for ground objects
    const unsigned int limitMask = (~PTYPE_GROUND) & 0xFFF0;

	
    if ((objClassification & limitMask) != 0)
    {
        if (cameraPosition.y < -480.0f) cameraPosition.y = -480.0f; 

        // avoid sea-air boundary glitch
        if ((cameraPosition.y > -1) && (cameraPosition.y < 1.5f))
        {
            cameraPosition.y = 1.5f;
        }
    }
    else
    {
        float min_y = std::max(1.0f, targetPosition.y + 2.0f);
        if (cameraPosition.y < min_y) cameraPosition.y = min_y; 
    }

    // camera shake code
    bool shakeEligible = ((objClassification & (PTYPE_AIR | PTYPE_MISSILE)) != 0) &&
        (cameraRange < 50.0f);
	
    if (shakeAirCamera && shakeEligible)
    {
        const float xscale(0.1f), yscale(0.08f), zscale(0.1f);
        float a(1);

        if (cameraRange > 25.0f) // linearly reduce shaking to zero from 25 to 50 m
        {
            a = 0.04f*(50.0f - cameraRange);
        }

        Vec3 walkOffset(randfc(xscale), randfc(yscale), randfc(zscale));
        Vec3 filteredOffset = walkOffset * 0.1f + lastWalkOffset * 0.9f;
        lastWalkOffset = filteredOffset;
        cameraWalkOffset += filteredOffset;
        
        cameraPosition += (cameraWalkOffset * a);
    }


    camera->SetPosition(cameraPosition.x, cameraPosition.y, cameraPosition.z);


    if (lookAtTarget)
    {
        cameraTarget = targetPosition + cameraTargetOffset;
    }
    else
    {
        float camx = cosf(cameraLookEl)*sinf(cameraLookAz);
        float camy = cosf(cameraLookEl)*cosf(cameraLookAz);
        float camz = sinf(cameraLookEl);
        Vec3 lookOffset(camx,camy,camz);

        cameraTarget = cameraPosition + lookOffset;
    }


    camera->SetLookAt(cameraTarget.x, cameraTarget.y, cameraTarget.z);

    if (cameraPosition.y >= -1.0f)
    {
        SetFogMode(FOG_AIR);
        //SetFogMode(FOG_OFF);

        waterBubbles->SetEmitterEnable(0, false);
    }
    else
    {
        SetFogMode(FOG_WATER);

        waterBubbles->SetEmitterEnable(0, true);


        waterBubblePosition = cameraPosition;
        waterBubbles->SetEmitterPosition(0, &waterBubblePosition);
        waterBubbles->Update();
    }

    // for high altitudes, temporarily disable terrain
    temporaryTerrainDisable = cameraPosition.y > 20e3f;

#if 0


	osg::Group* terrainRoot = (useFarSceneView) ? rootnodeFar.get() : rootnode.get();
    //osg::Group* terrainRoot = rootnode.get();

    // workaround for sky issue, deactivate sky when camera underwater
    if (cameraPosition._v[2] <= -1.0)
    {
        if (skyTransform->getNumParents())
        {
            terrainRoot->removeChild(skyTransform.get());
            SetFogMode(FOG_WATER);
			//terrainRoot->addChild(waterLights.get());
        }
    }
    else
    {
        if (isTerrainActive && (skyTransform->getNumParents() == 0))
        {
            terrainRoot->addChild(skyTransform.get());
            SetFogMode(FOG_AIR);
			//terrainRoot->removeChild(waterLights.get());
        }
    }

    

    sceneView->setViewMatrixAsLookAt(cameraPosition, cameraTarget, osg::Vec3(0,0,1));
	if (sceneViewFar.valid())
	{
		sceneViewFar->setViewMatrixAsLookAt(cameraPosition, cameraTarget, osg::Vec3(0,0,1));
	}

    //osgAL::SoundManager::instance()->getListener()->setPosition(cameraPosition.x(), cameraPosition.y(),
    //    cameraPosition.z());

	// update skyTransform based on camera position
	skyTransform->asPositionAttitudeTransform()->
        setPosition(osg::Vec3(cameraPosition.x(), cameraPosition.y(), 0));
#endif


}


void tc3DViewer::UpdateCameraSpin()
{
    if (cameraSpinRate == 0) return;

	unsigned currentTimeCount = tcTime::Get()->Get30HzCount();
	if (currentTimeCount - lastSpinCount >= 1)
	{
		SetCameraAz(GetCameraAz() + cameraSpinRate);
		lastSpinCount = currentTimeCount;
	}
}

/**
* Load models for new child objects.
* @param gameObj parent object
*/
void tc3DViewer::UpdateChildModels(tcGameObject *gameObj)
{
#if 0
    int nChildren = (int)gameObj->children.size();
    for (int n=0;n<nChildren;n++)
    {
        tcGameObject *childObj = gameObj->children.at(n);
        if (childObj->model->GetNumParents() == 0)
        {
            if (useRelativeChildPos)
            {
                // should be done as part of the GameObject::AddChild?
                gameObj->model->AddChild(childObj->model); 
            }
            else
            {
                worldObjects->addChild(childObj->model->GetNode().get());
            }
        }

    }
#endif
}

/**
* Load models for new objects.
*/
void tc3DViewer::UpdateModels()
{
	return; // obsolete

/*
    unsigned int nSize = simState->maPlatformState.GetCount();
    long poolpos = simState->maPlatformState.GetStartPosition();
    long nKey;
    unsigned int i = 0;

	bool use3Dcheat = tcOptions::Get()->mn3DCheatMode == 3;
    bool isServer = simState->IsMultiplayerServer();

    while (i++ < nSize) 
    {
        tcGameObject *gameObj;
        simState->maPlatformState.GetNextAssoc(poolpos,nKey,gameObj);
        wxASSERT(gameObj->model); // model should be created with gameObj
		if (isServer || gameObj->IsOwnAlliance() || use3Dcheat)
		{
#if 0
			if (gameObj->model->GetNumParents()==0)
			{
                worldObjects->addChild(gameObj->model->GetNode().get());
			}
#endif
			UpdateChildModels(gameObj);
		}
    }
    */

}


void tc3DViewer::UpdateRenderSurface(int width_, int height_)
{
    if ((width_ == rsWidth) && (height_ == rsHeight)) return;

    if (renderSurface != 0)
    {
        renderSurface->Destroy();
        DeleteTVObject(renderSurface);
        renderSurface = 0;
    }


    CTVScene* scene = tcTVEngine::Get()->GetScene();
    renderSurface = scene->CreateAlphaRenderSurface(width_, height_, true);

    rsWidth = width_;
    rsHeight = height_;

    if (renderSurface != 0)
    {
        renderSurface->SetNewCamera(tcTVEngine::Get()->GetCamera());
        if (fogMode != FOG_OFF)
		{
			renderSurface->SetBackgroundColor(RGBA(waterFog.x, waterFog.y, waterFog.z, 1));
		}
		else
		{
			renderSurface->SetBackgroundColor(0);
		}
    }

    

    //CTVCamera* camera = renderSurface->GetCamera();
    //camera->SetViewFrustum(fov_deg, zmax, zmin);

}

/**
* Load models for new sensor tracks
*/
void tc3DViewer::UpdateSensorModels(unsigned int alliance)
{
	bool use3Dcheat = tcOptions::Get()->mn3DCheatMode == 3;
	if (use3Dcheat) return;

    ObjectUpdater* objectUpdater = ObjectUpdater::Get();

    tcSensorTrackIterator iter(alliance, 0xFFFF);

    for (iter.First();iter.NotDone();iter.Next())
    {
        tcSensorMapTrack* track = iter.Get();

		wxASSERT(track);
		tc3DModel* model = (track != 0) ? track->GetModel() : 0;
		if (model)
		{
            objectUpdater->Update(track);
            ////model->SetupUpdate(track);
            //worldObjects->addChild(model->GetNode().get());

		}
		else
		{
			model = defaultSensorModel->Clone();
			track->SetModel(model);
			////model->SetupUpdate(track);
			
			//worldObjects->addChild(model->GetNode().get());
		}
	}

}

/**
* Calculate distance from camera to origin. If the 
* distance exceeds shiftDistance, then set the origin
* to current camera position.
* @return true if updated
*/
bool tc3DViewer::UpdateOrigin()
{
    float camx = cameraPosition.x;
    float camz = cameraPosition.z;
    float camRadius = sqrtf(camx*camx + camz*camz);

    if ((camRadius >= shiftDistance)&&(isActive))
    {
        double newLon = XToLon(cameraPosition.x);
        double newLat = YToLat(cameraPosition.z);
        cameraTarget.x -= cameraPosition.x;
        cameraTarget.z -= cameraPosition.z;
        cameraPosition.x = 0;
        cameraPosition.z = 0;
        SetOrigin(newLon, newLat);
        return true;
    }
    return false;
}

void tc3DViewer::UpdateSky(tcDateTime& dateZulu)
{
    tcTVEngine* engine = tcTVEngine::Get();
    CTVAtmosphere* atmosphere = engine->GetAtmosphere();
    static tcDateTime lastSkyUpdate;

    float sun_el_rad, sun_az_rad;

    tcDateTime t = dateZulu;

    tcSkyModel* skyModel = tcSkyModel::Get();

    skyModel->GetSunPosition(sun_el_rad, sun_az_rad, t, latOrigin_rad, lonOrigin_rad);

    if (abs(t.GetJulianDate() - lastSkyUpdate.GetJulianDate()) > 0.0001f)
    {
        skyModel->SetSunParameters(sun_el_rad, sun_az_rad, 2.0f);
        sky->BuildSkyDome();
        lastSkyUpdate = t;

        UpdateFog();
    }

    float lightElevation = std::max(sun_el_rad, 0.0f);
    Vec3 sunColor = skyModel->GetSkyColor(lightElevation, sun_az_rad);
    sunColor.x += 0.75f*(1.0-sunColor.x);
    sunColor.y += 0.75f*(1.0-sunColor.y);
    sunColor.z += 0.75f*(1.0-sunColor.z);

    const float sunRadius = 30000.0f;
    sunPosition.y = sunRadius * sinf(sun_el_rad);
    sunPosition.z = sunRadius * cosf(sun_el_rad) * cosf(sun_az_rad);
    sunPosition.x = sunRadius * cosf(sun_el_rad) * sinf(sun_az_rad);

    Vec3 lightDirection = sunPosition;
    lightDirection /= lightDirection.Length();
    //sunLightId

    sunLight.position = sunPosition;
    sunLight.direction = -lightDirection;


    if (sun_el_rad > -0.1)
    {
        sunLight.ambient = cTV_COLOR(0.8f, 0.8f, 0.5f, 1.0f);
        sunLight.ambient = cTV_COLOR(1, 1, 1, 1.0);
        sunLight.diffuse = cTV_COLOR(sunColor.x, sunColor.y, sunColor.z, 1.0);
        sunLight.specular = cTV_COLOR(0.3f, 0.3f, 0.5f, 1.0f);

		waterFog.set(0.1f, 0.2f, 0.3f, 1.0f);
        airFog.set(0.7f, 0.7f, 0.8f, 1.0f);
    }
    else if (sun_el_rad > -0.2)
	{
		float a = 10.0f*(sun_el_rad + 0.2);
		float b = 1.0f - a;

        sunLight.ambient = cTV_COLOR(a*0.50f+b*0.25f, a*0.50f+b*0.25f, 0.3f, 1.0f);
        sunLight.diffuse = cTV_COLOR(a*sunColor.x + b*0.15f, a*sunColor.y + b*0.15f, a*sunColor.z + b*0.3f, 1.0f);
        sunLight.specular = cTV_COLOR(0.05f, 0, 0.2f, 1.0f);

		waterFog.set(a*0.1f + b*0.05f, a*0.2f + b*0.1f, a*0.3f + b*0.15f, 1.0f);
        airFog.set(a*0.7f + b*0.1f, a*0.7f + b*0.1f, a*0.8f + b*0.15f, 1.0f);
	}
	else
    {
        sunLight.ambient = cTV_COLOR(0.15f, 0.15f, 0.2f, 1.0);
        sunLight.diffuse = cTV_COLOR(0.15f, 0.15f, 0.3f, 1.0);
        sunLight.specular = cTV_COLOR(0.05f, 0, 0.2f, 1.0);

		waterFog.set(0.05f, 0.1f, 0.15f, 1.0f);
        airFog.set(0.1f, 0.1f, 0.15f, 1.0f);
    }

    if (overrideLighting)
    {
        sunLight.ambient = 
            cTV_COLOR(sunAmbientOverride.x, sunAmbientOverride.y, sunAmbientOverride.z, sunAmbientOverride.w);
        sunLight.diffuse =
            cTV_COLOR(sunDiffuseOverride.x, sunDiffuseOverride.y, sunDiffuseOverride.z, sunDiffuseOverride.w);
        sunLight.specular =
            cTV_COLOR(sunSpecularOverride.x, sunSpecularOverride.y, sunSpecularOverride.z, sunSpecularOverride.w);
    }



    CTVLightEngine* lightEngine = engine->GetLightEngine();
    lightEngine->SetLight(sunLightId, &sunLight);

    atmosphere->Sun_SetPosition(sunPosition.x, -0.5*cameraPosition.y + sunPosition.y,
        sunPosition.z);
    atmosphere->Sun_SetColor(0.5f*sunColor.x + 0.5f, 0.5f*sunColor.y + 0.5f, 0.5f*sunColor.z + 0.5f, 1.0);
    
    atmosphere->Clouds_SetLayerColor(0, sunColor.x, sunColor.y, sunColor.z, 0.5f);
    //atmosphere->Sun_SetBlendingMode(cTV_BLEND_ADD);
    //atmosphere->Sun_SetPosition(

	//sky->update(latOrigin_rad, lonOrigin_rad, dateZulu);

	//airFog = sky->getHorizonColor(0);

}

/**
* @return camera position vec3 in world coordinates.
*/
Vec3 tc3DViewer::GetCameraPosition()
{
    return cameraPosition;
}


bool tc3DViewer::GetDatabaseViewState() const
{
    return databaseViewEnabled;
}


CTVMesh* tc3DViewer::GetHookedMesh()
{
	tcGameObject* obj = simState->GetObject(hookID);
    if (obj != 0)
    {
        return obj->model->GetMesh();
    }
    else
    {
        return 0;
    }
}

/**
* @return object position in world coordinates.
*/
const Vec3& tc3DViewer::GetHookedObjectPositionAndType(unsigned int& classification)
{
	static Vec3 lastPos(0, 0, 0);

    int n3DCheatMode = tcOptions::Get()->mn3DCheatMode;

	tcGameObject* obj = simState->GetObject(hookID);
    float x, y, z;

	// try to find in sensor map if null object (multiplayer client case)
	if (obj == 0)
	{
        tcSensorMap* sensorMap = simState->GetSensorMap();
        unsigned int ownAlliance = simState->mpUserInfo->GetOwnAlliance();
        
		if (tcSensorMapTrack* track = 
            sensorMap->GetSensorMapTrack(hookID, ownAlliance))
        {
            tcTrack predicted;
            track->GetPrediction(predicted, simState->GetTime());
            x = LonToX(predicted.mfLon_rad);
            z = LatToY(predicted.mfLat_rad);
            y = predicted.GetOrGuessAltitude();

			classification = predicted.mnClassification;
			lastPos.set(x, y, z);
        }
		else
		{
			classification = 0;
		}
		return lastPos;
	}


    if (n3DCheatMode == 3)
    {
        x = LonToX(obj->mcKin.mfLon_rad);
        z = LatToY(obj->mcKin.mfLat_rad);
        y = obj->mcKin.mfAlt_m;

		classification = obj->mpDBObject->mnType;
    }
    else
    {
        tcSensorMap* sensorMap = simState->GetSensorMap();
        unsigned int ownAlliance = simState->mpUserInfo->GetOwnAlliance();
        if (ownAlliance == obj->GetAlliance())
        {
            x = LonToX(obj->mcKin.mfLon_rad);
            z = LatToY(obj->mcKin.mfLat_rad);
            y = obj->mcKin.mfAlt_m;

			classification = obj->mpDBObject->mnType;
        }
        else if (tcSensorMapTrack* track = 
            sensorMap->GetSensorMapTrack(obj->mnID, ownAlliance))
        {
            tcTrack predicted;
            track->GetPrediction(predicted, simState->GetTime());
            x = LonToX(predicted.mfLon_rad);
            z = LatToY(predicted.mfLat_rad);
            y = predicted.GetOrGuessAltitude();

			classification = predicted.mnClassification;
        }
        else
        {	
			static unsigned errorCount = 0;
			x = lastPos.x;
			y = lastPos.y;
			z = lastPos.z;

			classification = 0;

			if (errorCount++ < 4)
			{
				fprintf(stderr, "tc3DViewer::GetHookedObjectPositionAndType - graphics error (%s)\n",
                    obj->GetName());
			}
        }
    }

	lastPos.set(x, y, z);
    return lastPos;
}

const tcPoint& tc3DViewer::GetOrigin() const
{
    static tcPoint p;

    p.x = lonOrigin_rad;
    p.y = latOrigin_rad;

    return p;
}

tc3DViewer::WaterMode tc3DViewer::GetWaterMode() const
{
    if (useSimpleWater || (cameraPosition.y > 2000.0f) || (cameraPosition.y < 0))
    {
        return SIMPLE;
    }
    else
    {
        return SHADER;
    }
}

bool tc3DViewer::HandleEraseBkgnd(WXHDC hDC)
{
    return TRUE;
}

void tc3DViewer::InitButtons()
{
	if (minimizeImage.get() == 0)
	{
		minimizeImage = boost::shared_ptr<tcTexture2D>(tc3DWindow2::LoadTexture("minimize.jpg"));
		minimizeOverImage = boost::shared_ptr<tcTexture2D>(tc3DWindow2::LoadTexture("minimize_over.jpg"));
		maximizeImage = boost::shared_ptr<tcTexture2D>(tc3DWindow2::LoadTexture("maximize.jpg"));
		maximizeOverImage = boost::shared_ptr<tcTexture2D>(tc3DWindow2::LoadTexture("maximize_over.jpg"));

		mouseOverMinimize = false;
		mouseOverMaximize = false;
	}

	float buttonWidth = 16.0f;
	maximizeRect.left = float(mnWidth-6)-buttonWidth;
	maximizeRect.bottom = 3.0f;
	maximizeRect.right = maximizeRect.left + buttonWidth;
	maximizeRect.top = maximizeRect.bottom + buttonWidth;

	minimizeRect = maximizeRect;
	minimizeRect.Offset(-buttonWidth - 3.0f, 0);

}

/**
* Creates scene view to display 3D objects for database viewer
*/
void tc3DViewer::InitDatabaseView(const wxPoint& pos, const wxSize& size)
{
#if 0
	databaseView = new osgUtil::SceneView();

    if (!displaySettings.valid())
    {
        wxASSERT(databaseView->getDisplaySettings()==NULL);
        displaySettings = new osg::DisplaySettings;
	    displaySettings->setDepthBuffer(true);
		displaySettings->setMinimumNumStencilBits(8);
		displaySettings->setDoubleBuffer(true);
		displaySettings->setMinimumNumAlphaBits(8);
    }

	databaseView->setDisplaySettings(displaySettings.get());
    databaseView->setDefaults();

	databaseView->getState()->setContextID(2); // (sceneView->getState());


    wxWindow* parent = wxWindow::GetParent();
    wxSize parentSize = parent->GetSize();
    int parentHeight = parentSize.GetHeight();
    int correctedY = parentHeight - (pos.y + size.GetHeight());

    // Update projection matrix
	float aspectRatio = (float)size.GetWidth() / (float)size.GetHeight();
	float zmid = sqrtf(zmin*zmax);
	databaseView->setProjectionMatrixAsPerspective(45.0, aspectRatio, zmin, zmid);
	

    databaseView->setViewport(pos.x, correctedY, size.GetWidth(), size.GetHeight());
	databaseView->setComputeNearFarMode(osgUtil::CullVisitor::DO_NOT_COMPUTE_NEAR_FAR);
	databaseView->setLightingMode(osgUtil::SceneView::NO_SCENEVIEW_LIGHT);
	databaseView->setCullingMode(osg::CullStack::NO_CULLING);

    // set up the clear mask.
    osgUtil::RenderStage *stage = databaseView->getRenderStage();
    stage->setClearMask(GL_DEPTH_BUFFER_BIT);
    stage->setClearDepth(1.0f);
#endif
}


/**
* 
*/
void tc3DViewer::InitGuiView()
{
#if 0
	guiView = new osgUtil::SceneView();

    wxASSERT(guiView->getDisplaySettings()==NULL);

	osg::DisplaySettings* guiDisplaySettings = new osg::DisplaySettings;
	guiDisplaySettings->setDepthBuffer(false);
	guiDisplaySettings->setMinimumNumStencilBits(8);
	guiDisplaySettings->setDoubleBuffer(true);
	guiDisplaySettings->setMinimumNumAlphaBits(8);
   


	guiView->setDisplaySettings(guiDisplaySettings);
    guiView->setDefaults();
	
	//guiView->setState(sceneView->getState());
	
	guiView->getState()->setContextID(1);

	//guiView->getState()->setContextID(0);

    wxWindow* parent = wxWindow::GetParent();
    wxSize parentSize = parent->GetSize();

	guiView->setProjectionMatrixAsOrtho2D(0, parentSize.GetWidth(),
					0, parentSize.GetHeight());


    guiView->setViewport(0, 0, parentSize.GetWidth(), parentSize.GetHeight());
	guiView->setComputeNearFarMode(osgUtil::CullVisitor::DO_NOT_COMPUTE_NEAR_FAR);
	guiView->setLightingMode(osgUtil::SceneView::NO_SCENEVIEW_LIGHT);
	guiView->setClearColor(osg::Vec4(0, 0, 0.4f, 1.0f));


	guiView->setCullingMode(osg::CullStack::NO_CULLING);

    // set up the clear mask.
    osgUtil::RenderStage *stage = guiView->getRenderStage();
    stage->setClearMask(GL_STENCIL_BUFFER_BIT);

    guiFrameStamp = new osg::FrameStamp;
    guiFrameStamp->setReferenceTime(gameTime);
    guiView->setFrameStamp(guiFrameStamp.get());

    guiUpdateVisitor = new osgUtil::UpdateVisitor();
    guiUpdateVisitor->setFrameStamp(guiFrameStamp.get());
    guiView->setUpdateVisitor(guiUpdateVisitor.get());

	//cullVisitor = new osgUtil::PrintCullVistor();
	cullVisitor = new osgUtil::CullVisitor();
	guiView->setCullVisitor(cullVisitor.get());


    guiObjects = new osg::MatrixTransform; 
    guiObjects->setMatrix(osg::Matrix::identity()); 
    guiObjects->setReferenceFrame(osg::MatrixTransform::ABSOLUTE_RF); 

    guiView->setSceneData(guiObjects.get());
#endif
}

void tc3DViewer::InitSceneView(wxPoint pos, wxSize size)
{
#if 0

	sceneView = new osgUtil::SceneView();

    wxASSERT(sceneView->getDisplaySettings()==NULL);

    displaySettings = new osg::DisplaySettings;
	displaySettings->setDepthBuffer(true);
	displaySettings->setMinimumNumStencilBits(8);
	displaySettings->setDoubleBuffer(true);
	displaySettings->setMinimumNumAlphaBits(8);


   // displaySettings->setRGB(true);
    //displaySettings->setDoubleBuffer(true);
    //displaySettings->setMinimumNumAlphaBits(4);

	sceneView->setDisplaySettings(displaySettings.get());
    sceneView->setDefaults();
	sceneView->getState()->setContextID(0);


	osg::StateSet* stateSet = sceneView->getGlobalStateSet();

	//stateSet->setMode(GL_STENCIL_TEST, osg::StateAttribute::ON);



    wxWindow *parent = wxWindow::GetParent();
    wxSize parentSize = parent->GetSize();
    int parentHeight = parentSize.GetHeight();
    int correctedY = parentHeight - (pos.y + size.GetHeight());

    UpdateProjectionMatrix(size);

    sceneView->setViewport(pos.x,correctedY,size.GetWidth(),size.GetHeight());
	sceneView->setComputeNearFarMode(osgUtil::CullVisitor::DO_NOT_COMPUTE_NEAR_FAR);
	sceneView->setLightingMode(osgUtil::SceneView::NO_SCENEVIEW_LIGHT);
	sceneView->setClearColor(osg::Vec4(0, 0, 0, 1.0f));
	
    //sceneView->setComputeNearFarMode(osgUtil::CullVisitor::COMPUTE_NEAR_FAR_USING_BOUNDING_VOLUMES);
	/*
	NO_CULLING                  = 0x0,
	VIEW_FRUSTUM_CULLING        = 0x1,
	NEAR_PLANE_CULLING          = 0x2,
	FAR_PLANE_CULLING           = 0x4,
	SMALL_FEATURE_CULLING       = 0x8,
	SHADOW_OCCLUSION_CULLING    = 0x10,
	ENABLE_ALL_CULLING  
	*/
	sceneView->setCullingMode( 
		osg::CullStack::NO_CULLING
		// osg::CullStack::FAR_PLANE_CULLING 
		// osg::CullStack::NEAR_PLANE_CULLING 
		// osg::CullStack::VIEW_FRUSTUM_CULLING
		// osg::CullStack::SMALL_FEATURE_CULLING
		);

    // set up the clear mask.
    osgUtil::RenderStage *stage = sceneView->getRenderStage();
   // stage->setClearMask(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    stage->setClearDepth(1.0f);
    //stage->setClearColor(osg::Vec4(0,0,0,1.0f));
    stage->setClearMask(GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    frameStamp = new osg::FrameStamp;
    frameStamp->setReferenceTime(gameTime);
    sceneView->setFrameStamp(frameStamp.get());

    updateVisitor = new osgUtil::UpdateVisitor();
    updateVisitor->setFrameStamp(frameStamp.get());
    sceneView->setUpdateVisitor(updateVisitor.get());
#endif
}




/**
* set global state at root node
*/
void tc3DViewer::InitState()
{
#if 0
    osg::StateSet * globalStateSet = sceneView->getGlobalStateSet();
    if (!globalStateSet)
    {
        globalStateSet = new osg::StateSet;
        sceneView->setGlobalStateSet(globalStateSet);
		//globalStateSet->setGlobalDefaults();
    }
#endif
    {

#if 0
        //globalStateSet->setGlobalDefaults();
        // enable depth testing by default.
        osg::Depth* depth = new osg::Depth(osg::Depth::LESS, 0, 1);
        globalStateSet->setAttributeAndModes(depth, osg::StateAttribute::ON );
		


        //globalStateSet->setMode(GL_DEPTH_TEST, osg::StateAttribute::ON);


        osg::PolygonMode  *pm = new osg::PolygonMode();
		pm->setMode(osg::PolygonMode::Face::FRONT_AND_BACK, osg::PolygonMode::FILL);
        globalStateSet->setAttribute(pm, osg::StateAttribute::ON);

        osg::LineWidth  *lw = new osg::LineWidth();
        lw->setWidth(1.0f);
        globalStateSet->setAttribute(lw, osg::StateAttribute::ON);

        // enable lighting by default
        globalStateSet->setMode(GL_LIGHTING, osg::StateAttribute::ON);

        /*
        osg::BlendFunc *blendFunction = new osg::BlendFunc;
	    blendFunction->setFunction(osg::BlendFunc::SRC_ALPHA, osg::BlendFunc::ONE_MINUS_SRC_ALPHA);
	    globalStateSet->setAttributeAndModes(blendFunction, osg::StateAttribute::ON);
		globalStateSet->setMode(GL_CULL_FACE, StateAttribute::OFF);
        */

        // set up an alphafunc by default to speed up blending operations.
        osg::AlphaFunc* alphafunc = new osg::AlphaFunc;
        alphafunc->setFunction(osg::AlphaFunc::GREATER,0.0f);
        globalStateSet->setAttributeAndModes(alphafunc, osg::StateAttribute::ON);

	



		//globalStateSet->setTextureMode(0, GL_TEXTURE_2D, osg::StateAttribute::INHERIT);
		//globalStateSet->setTextureMode(1, GL_TEXTURE_2D, osg::StateAttribute::INHERIT);


		globalStateSet->setTextureMode(0, GL_TEXTURE_2D, osg::StateAttribute::PROTECTED | osg::StateAttribute::ON);
#endif

    }
}

void tc3DViewer::InitText()
{
#if 0
    textGeode = new osg::Geode;
    viewerText = new osgText::Text;
    osgText::Font* font = osgText::readFontFile("fonts/arial.ttf");

    osg::Vec4 layoutColor(1.0f,1.0f,1.0f,1.0f); 
    
    viewerText->setFont(font);
    viewerText->setColor(layoutColor);
    viewerText->setCharacterSize(16.0f, 1.2f); // font height, aspect ratio
    viewerText->setPosition(osg::Vec3(20.0f,(float)mnHeight - 40.0f,0.0f));
    viewerText->setLayout(osgText::Text::LEFT_TO_RIGHT);
    viewerText->setFontResolution(32,32);
    viewerText->setText("TEST TEXT");
	

    osg::StateSet *textState = textGeode->getOrCreateStateSet();
	textState->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	textState->setMode(GL_FOG, osg::StateAttribute::OFF);
    textState->setMode(GL_DEPTH, osg::StateAttribute::OFF);
	textState->setMode(GL_BLEND, osg::StateAttribute::OFF );


    /*
    osg::Depth* depth = new osg::Depth;
    depth->setFunction(osg::Depth::ALWAYS);
    depth->setRange(1.0, 1.0);   
    depth->setWriteMask(false);
    textState->setAttributeAndModes(depth,StateAttribute::OFF);
    */

    textGeode->addDrawable(viewerText.get());
    hudObjects->addChild(textGeode.get());
#endif
}

void tc3DViewer::SetShakeAirCamera(bool state)
{
	shakeAirCamera = state;
}

/**
* Used to enable or disable terrain and sky
*/
void tc3DViewer::SetTerrainActive(bool state)
{
	if (isTerrainActive == state) return; // ignore if state already set

	isTerrainActive = state;

    terrainManager->Enable(state);


}

void tc3DViewer::SetText(const char *s)
{
    //viewerText->setText(s);
}

/**
* @param positionCode: 0 - upper left, 1 - top center, 2 - bottom center
*/
void tc3DViewer::SetTextPosition(int positionCode)
{
//	if (!viewerText.valid()) return;

#if 0
	if (positionCode == 0)
	{
		viewerText->setPosition(osg::Vec3(20.0f,(float)mnHeight - 40.0f,0.0f));
		viewerText->setAlignment(osgText::Text::LEFT_BASE_LINE);
	}
	else if (positionCode == 1)
	{
		viewerText->setPosition(osg::Vec3(0.5f * (float)mnWidth,
			(float)mnHeight - 40.0f, 0.0f));
		viewerText->setAlignment(osgText::Text::CENTER_CENTER);
	}
	else
	{
		viewerText->setPosition(osg::Vec3(0.5f * (float)mnWidth,
			(float)40.0f, 0.0f));
		viewerText->setAlignment(osgText::Text::CENTER_CENTER);
	}
#endif
}

void tc3DViewer::AddDefaultTextObjects()
{
#if 0
	osg::Vec3 upperLeft(20.0f, (float)mnHeight - 40.0f, 0.0f);
	osg::Vec3 upperRight((float)mnWidth - 150.0f, (float)mnHeight - 40.0f, 0.0f);
	osg::Vec3 bottomCenter(0.5 * (float)mnWidth, 0.2f*(float)mnHeight, 0.0f);
	osg::Vec3 topCenter(0.5 * (float)mnWidth, 0.8f*(float)mnHeight, 0.0f);
	osg::Vec4 color(0.4f, 0.4f, 0.8f, 0.8f);

	AddTextObject(0, upperLeft, 12.0, color, 
		osgText::Text::LEFT_BASE_LINE);

	AddTextObject(1, upperRight, 12.0, color,
		osgText::Text::LEFT_BASE_LINE);

	AddTextObject(2, bottomCenter, 16.0, osg::Vec4(0.9f, 0.9f, 0.7f, 0.9f),
		osgText::Text::CENTER_CENTER);

	AddTextObject(3, topCenter, 16.0, osg::Vec4(0.9f, 0.9f, 0.7f, 0.9f),
		osgText::Text::CENTER_CENTER);
#endif
}

void tc3DViewer::ClearDefaultTextObjects()
{
#if 0
	ClearTextObject(0);
	ClearTextObject(1);
	ClearTextObject(2);
	ClearTextObject(3);
#endif
}

void tc3DViewer::AddTextObject(int key, const Vec3& pos, float fontSize,
							   const Vec4& color,
							   int alignment)
{
#if 0
	osgText::Text* text = new osgText::Text;
    osgText::Font* font = osgText::readFontFile("fonts/arial.ttf");

    text->setFont(font);
    text->setColor(color);
    text->setCharacterSize(fontSize, 1.2f); // font height, aspect ratio
    text->setPosition(pos);
    text->setLayout(osgText::Text::LEFT_TO_RIGHT);
    text->setFontResolution(32,32);
    text->setText("");
	text->setAlignment(alignment);

    textGeode->addDrawable(text);

	if (TextObjectExists(key))
	{
		ClearTextObject(key);
		fprintf(stderr, "tc3DViewer::AddTextObject - Replacing existing text obj\n");
	}
	textMap[key] = text;
#endif
}

void tc3DViewer::ClearTextObject(int key)
{
#if 0
	std::map<int,osgText::Text*>::iterator iter;

    iter = textMap.find(key);
    if (iter == textMap.end())
	{
		fprintf(stderr, "tc3DViewer::ClearTextObject - "
			"Tried to clear non-existent text obj\n");
		return;
	}
	textGeode->removeDrawable(iter->second);
	textMap.erase(iter);
#endif
}

/**
* Not sure if destruction is done correctly here
*/
void tc3DViewer::ClearTextObjects()
{
#if 0
	std::map<int,osgText::Text*>::iterator iter;

    
    for (iter = textMap.begin(); iter != textMap.end(); ++iter)
	{
		textGeode->removeDrawable(iter->second);
	}

	textMap.clear();
#endif
}

/**
* @return true if text object matching key exists in map
*/
bool tc3DViewer::TextObjectExists(int key)
{
#if 0
	std::map<int,osgText::Text*>::const_iterator iter;

    iter = textMap.find(key);
    return !(iter == textMap.end());
#endif
    return false;
}

void tc3DViewer::UpdateTextObject(int key, const std::string& text)
{
#if 0
	std::map<int,osgText::Text*>::iterator iter;

	iter = textMap.find(key);
	if (iter == textMap.end())
	{
		fprintf(stderr, "tc3DViewer::UpdateTextObject - "
			"Tried to update non-existent text obj\n");
		return;
	}
	iter->second->setText(text.c_str());
#endif
}


void tc3DViewer::Swap()
{
    //glCanvas->SwapBuffers();
}

void tc3DViewer::ToggleFog()
{
#if 0
    osg::StateSet *fogState = foggedObjects->getOrCreateStateSet();
    if (fogState->getMode(GL_FOG) == osg::StateAttribute::ON)
    {
        fogState->setMode(GL_FOG, osg::StateAttribute::OFF);
    }
    else
    {
        fogState->setMode(GL_FOG, osg::StateAttribute::ON);
    }  
#endif
}

void tc3DViewer::ToggleWireframe()
{
    viewWireframe = !viewWireframe;
}

void tc3DViewer::Update(tcDateTime& dateZulu)
{
    static long lastHook = -1;

    if (databaseViewEnabled)
    {
        UpdateDatabaseView();
        return;
    }

    if (lastHook != hookID)
    {
		SetCameraMode(true, true);
		cameraTargetOffset.set(0, 0, 0);

        lastHook = hookID;
        tcGameObject *obj = simState->GetObject(hookID);
        if (obj)
        {
            // set camera position to 
            //const osg::BoundingSphere& bs = obj->model->GetNode()->getBound();
            //cameraRange = 4*bs.radius();
            cameraRange = 2 * obj->model->GetRadiusGeneric();
            if (cameraRange < 12.0f) cameraRange = 12.0f;
        }

    }

    UpdateModels();

	if (!simState->IsMultiplayerServer())
	{
		UpdateSensorModels(tcUserInfo::Get()->GetOwnAlliance());
	}

    UpdateCamera();

    if (UpdateOrigin())
    {
        UpdateModels();
        UpdateCamera();
    }

    UpdateSky(dateZulu);


}

/**
* Update graphics options based on latest tcOptions state
*/
void tc3DViewer::UpdateOptions()
{
    tcOptions* options = tcOptions::Get();

	useFarSceneView = options->useFarSceneView != 0;
    useSimpleWater = (options->waterShaderOn == 0) || (options->shadersOn == 0);
	shadowsOn = (options->shadowsOn != 0) && (options->shadersOn != 0);
    fogEnabled = (options->fogOn != 0);


    shakeAirCamera = true; //options->OptionStringExists("ShakeAirCamera");

	if (sunLightId != -1)
	{
		tcTVEngine* engine = tcTVEngine::Get();
		CTVLightEngine* lightEngine = engine->GetLightEngine();
		lightEngine->SetLightProperties(sunLightId, false, shadowsOn, false);
	}

    SetOverrideLighting(options->manualLighting != 0);

    sunAmbientOverride.set(options->sunAmbientRed, options->sunAmbientGreen, options->sunAmbientBlue, 1.0f);
    sunDiffuseOverride.set(options->sunDiffuseRed, options->sunDiffuseGreen, options->sunDiffuseBlue, 1.0f);
    sunSpecularOverride.set(options->sunSpecularRed, options->sunSpecularGreen, options->sunSpecularBlue, 1.0f);

    // camera options
    if (options->manualFOV == 0)
    {
        //fov_deg = 45.0f;
    }
    else
    {
        //fov_deg = options->fov_deg;
    }

    if (options->adjustMaxView == 0)
    {
        if (options->max3Drange == 2)
        {
            zmax = 100000.0f;
        }
        else if (options->max3Drange == 1)
        {
            zmax = 75000.0f;
        }
        else
        {
            zmax = 50000.0f;
        }
    }
    else
    {
        zmax = 1000.0f * options->maxView_km;
    }

    zmid = sqrt(zmin*zmax);

    // water FX colors
    if (options->adjustWater != 0)
    {
        Vec4 reflection(options->waterReflectionRed, options->waterReflectionGreen, 
            options->waterReflectionBlue, options->waterReflectionAlpha);
        Vec4 refraction(options->waterRefractionRed, options->waterRefractionGreen, 
            options->waterRefractionBlue, options->waterRefractionAlpha);

        if (terrainManager != 0)
        {
            terrainManager->SetWaterColor(reflection, refraction, options->waterCustomFresnel);
        }
    }

}

/**
* Updates sceneView projection matrix. Call once at initialization
* and once after any window size change.
*/
void tc3DViewer::UpdateProjectionMatrix(const wxSize& windowSize)
{
    tcTVEngine* engine = tcTVEngine::Get();
    CTVCamera* camera = engine->GetCamera();

    float w = float(windowSize.GetWidth());
    float h = float(windowSize.GetHeight());
    float aspect = w/h;
    camera->SetCustomAspectRatio(aspect);

    tcOptions* options = tcOptions::Get();
    if (options->manualFOV == 0)
    {
        fov_deg = aspect * 20.0f; //67.5;
    }
    else
    {
        fov_deg = aspect * options->fov_deg;
    }


    camera->SetViewFrustum(fov_deg, zmax, zmin);
}

tc3DViewer::tc3DViewer(wxWindow *parent, const wxPoint& pos, const wxSize& size, 
        const wxString& name) :
        wxWindow(parent, -1, pos, size, wxTRANSPARENT_WINDOW | wxNO_FULL_REPAINT_ON_RESIZE, name),   
        mnHeight(size.GetHeight()), mnWidth(size.GetWidth()),
        cameraWalkOffset(0, 0, 0),
        cameraSpinRate(0),
        lastSpinCount(0),
		isBorderActive(false),
		airFog(0.6f, 0.7f, 0.8f, 1.0f),
		waterFog(0.1f, 0.2f, 0.3f, 1.0f),
		fogMode(FOG_AIR),
        fogEnabled(true),
        terrainManager(0),
        fov_deg(45.0f),
        renderSurface(0),
        rsWidth(0),
        rsHeight(0),
        sky(0),
        databaseModel(0),
        testParticleSystem(0),
        waterBubbles(0),
        sunPosition(0, 0, 0),
		sunLightId(-1),
		shadowsOn(false),
        overrideLighting(false),
        sunAmbientOverride(1, 1, 1, 1),
        sunDiffuseOverride(1, 1, 1, 1),
        sunSpecularOverride(1, 1, 1, 1),
        temporaryTerrainDisable(false)
{
    //glCanvas = parent;
    SetBackgroundColour(*wxBLACK);
    Show(FALSE);

    lonToGridX = C_RADTOM;
    latToGridY = C_RADTOM; 
    gridXToLon = C_MTORAD;
    gridYToLat = C_MTORAD;
    latOrigin_rad = 0;
    lonOrigin_rad = 0;
    zmin = 3.0f;

	// user-selected options -------------------
	tcOptions* options = tcOptions::Get();
	if (options->max3Drange == 2)
	{
		zmax = 100000.0f;
	}
	else if (options->max3Drange == 1)
	{
		zmax = 75000.0f;
	}
	else
	{
		zmax = 50000.0f;
	}

    zmid = sqrt(zmin*zmax);

    UpdateOptions();

    // ----------------------

	//Sky::SetRadius(zmax - 100.0f);

    shiftDistance = 50000.0f;
    cameraAz = 0.5f*C_PI;
    cameraEl = 0.1f;
    cameraRange = 100.0f;
    isMouseDown = false;
    isActive = true;
	isTerrainActive = false;
    isFrozen = false;
    viewWireframe = false;
    useRelativeChildPos = true;
    moveWithTarget = true;
    lookAtTarget = true;
    usePolarOffset = true;
    databaseViewEnabled = false;

    cameraLongitude = 0;
    cameraLatitude = 0;
    cameraAltitude = 100.0f;
    cameraLookAz = 0; 
    cameraLookEl = 0; 
    gameTime = 0;
	lastGameTime = 0;

    simState = NULL;
    hookID = NULL_INDEX;
    ObjectUpdater::AttachViewer(this);
	tc3DModel::AttachViewer(this);

    InitSceneView(pos, size);

	InitGuiView();

    InitDatabaseView(pos, size);



#if 0
    rootnode = new osg::Group;

    sceneView->setSceneData(rootnode.get());

	if (useFarSceneView)
	{
		rootnodeFar = new osg::Group;
		rootnodeFar->addChild(rootnode.get());
		sceneViewFar->setSceneData(rootnodeFar.get());
	}

    hudObjects = new osg::MatrixTransform; 
    hudObjects->setMatrix(osg::Matrix::identity()); 
    hudObjects->setReferenceFrame(osg::MatrixTransform::ABSOLUTE_RF); 

    orthoProjection = new osg::Projection(); 
    orthoProjection->setMatrix(osg::Matrix::ortho2D(0,size.GetWidth(),0,size.GetHeight())); 
    orthoProjection->addChild(hudObjects.get());

    databaseViewGroup = new osg::Group();
    databaseView->setSceneData(databaseViewGroup.get());
#endif

    InitState();
    
    CreateScene();

	tc3DModel::LoadUnknowns();

	defaultSensorModel = new tc3DModel();
	defaultSensorModel->LoadXml("unknown.xml");

    UpdateRenderSurface(mnWidth, mnHeight);

	//osg::Light* light = sceneView->getLight();
	//osgUtil::SceneView::LightingMode lm = sceneView->getLightingMode();
	//light->setPosition(osg::Vec4(0, 0, 1, 0));

//    rootnode->addChild(tcSound::Get()->GetSoundRoot());


	InitButtons();
}

tc3DViewer::~tc3DViewer() 
{
    if (sky) delete sky;
    if (terrainManager) delete terrainManager;
	if (defaultSensorModel) delete defaultSensorModel;

    if (renderSurface != 0)
    {
        renderSurface->Destroy();
        DeleteTVObject(renderSurface);
    }

}
