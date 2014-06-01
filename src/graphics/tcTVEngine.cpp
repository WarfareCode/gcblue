/**  
**  @file tcTVEngine.cpp
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

#include "tcTVEngine.h"
#include "CTVCamera.h"
#include "CTVAtmosphere.h"
#include "CTVInternalObjects.h"
#include "tcOptions.h"
#include "CTVMaterialFactory.h"
#include "tcDisplayModes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif 

/** 
* @return singleton instance 
*/
tcTVEngine* tcTVEngine::Get()
{
    static tcTVEngine instance;
    return &instance;
}

/**
* Writes text to tvdebug log
*/
void tcTVEngine::AddToLog(const char* text)
{
    engine->AddToLog(text);
}

void tcTVEngine::Clear(bool bOnlyZBuffer)
{
    engine->Clear(bOnlyZBuffer);
}

CTVRenderSurface* tcTVEngine::Create2DRenderSurface(int width, int height)
{
    CTVRenderSurface* rs = scene->CreateRenderSurfaceEx(width, height, cTV_TEXTUREFORMAT_A8R8G8B8, false);
    rs->SetBackgroundColor(D3DCOLOR_ARGB(0,0,0,0));

    return rs;
}

void tcTVEngine::ClearZBuffer()
{
    internalObjects->GetDevice3D()->Clear(0, NULL, D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(255,255,255), 1.0f, 0);
}

void tcTVEngine::DisableZBuffer()
{    
    //internalObjects->GetDevice3D()->SetRenderState(D3DRS_ZWRITEENABLE, D3DZB_FALSE);
    //internalObjects->GetDevice3D()->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
    internalObjects->GetDevice3D()->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
}

void tcTVEngine::EnableZBuffer()
{
    //internalObjects->GetDevice3D()->SetRenderState(D3DRS_ZWRITEENABLE, D3DZB_TRUE);
    //internalObjects->GetDevice3D()->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESS);
    internalObjects->GetDevice3D()->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
}

void tcTVEngine::DisableAlphaBlend()
{
    internalObjects->GetDevice3D()->SetRenderState(D3DRS_ALPHABLENDENABLE, D3DZB_FALSE);
}

void tcTVEngine::EnableAlphaBlend()
{
    internalObjects->GetDevice3D()->SetRenderState(D3DRS_ALPHABLENDENABLE, D3DZB_TRUE);
}

void tcTVEngine::ForceSourceAlpha()
{
    internalObjects->GetDevice3D()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
}


void tcTVEngine::Frame()
{    
    engine->RenderToScreen();
}

CTVAtmosphere* tcTVEngine::GetAtmosphere()
{
    return atmosphere;
}

CTVCamera* tcTVEngine::GetCamera()
{
    return camera;
}

int tcTVEngine::GetDefaultMaterial() const
{
    return defaultMaterial;
}

int tcTVEngine::GetFreeTextureMemory()
{
    return texFactory.GetFreeTextureMemory();
}

CTVLightEngine* tcTVEngine::GetLightEngine()
{
    return lightEngine;
}

CTVMaterialFactory* tcTVEngine::GetMaterialFactory()
{
    return &materialFactory;
}


int tcTVEngine::GetUsedTextureMemory()
{
    return texFactory.GetUsedTextureMemory();
}

CTVScene* tcTVEngine::GetScene()
{
    return scene;
}

CTVScreen2DImmediate* tcTVEngine::GetScreen2D()
{
    return &screen2D;
}

CTVScreen2DText* tcTVEngine::GetText2D()
{
    return &text2D;
}

CTVTextureFactory* tcTVEngine::GetTextureFactory()
{
    return &texFactory;
}

int tcTVEngine::GetTextureFilterMode2d() const
{
    return textureFilterMode2d;
}

CTVViewport* tcTVEngine::GetViewport()
{
    return engine->GetViewport();
}

void tcTVEngine::InitTV3D(HWND hwnd, bool isWindowed)
{
	// Create the pTV Interface first:
	engine = new CTVEngine();
	
   // engine->SetLicenseFile("BlueII.lic");

	engine->SetDebugMode(true, true);
	engine->SetDebugFile("log\\tvdebug.txt");
	engine->DisplayFPS(false);
    engine->SetFPUPrecision(true);

    engine->SetAntialiasing(false, (cCONST_TV_MULTISAMPLE_TYPE)antialiasing); // do before init to avoid reinit
    
    engine->SetWatermarkParameters(cTV_WATERMARK_BOTTOMRIGHT , 0.2f);

	// After setting the beta-key/license its time to init the engine:
    if (isWindowed || true)
    {
	    engine->Init3DWindowed(hwnd, enableTL);
        engine->SetWindowTitle("gcblue");
    }
    else // this doesn't work right, creates 2 windows that block mouse input for some reason
    {
        tcDisplayModes::Info modeInfo = tcDisplayModes::Get()->GetCurrentModeInfo();
        float gamma = 1.0f;
        engine->Init3DFullscreen(modeInfo.width, modeInfo.height, modeInfo.bits, enableTL, vsync, cTV_DEPTHBUFFER_BESTBUFFER, gamma, NULL);
    }

	// Something good to do is to enable the auto-resize feature:
	// Get the default viewport and set autoresize to true for it:
	engine->GetViewport()->SetAutoResize(true);

    #ifdef _DEBUG
	engine->DisplayFPS(true);
    #endif

	// Set the prefered angle system:
	engine->SetAngleSystem(cTV_ANGLE_RADIAN);

    engine->SetVSync(vsync);

    //engine->EnableSmoothTime(true, 10);

	// Now after we are done initializing the TVEngine component lets continue:
	// Create any other components after engine init->
	scene = new CTVScene();
    scene->SetTextureFilter(cCONST_TV_TEXTUREFILTER(textureFilterMode3d));
    screen2D.Settings_SetTextureFilter(cCONST_TV_TEXTUREFILTER(textureFilterMode2d));

    scene->SetBackgroundColor(0, 0, 0, 0.0);

        //cTV_TEXTUREMODE_16BITS = 0,
        //cTV_TEXTUREMODE_32BITS = 1,
        //cTV_TEXTUREMODE_COMPRESSED = 2,
        //cTV_TEXTUREMODE_BETTER = 3,
        //cTV_TEXTUREMODE_PALETTIZED8BITS = 4

    //texFactory.SetTextureMode(cTV_TEXTUREMODE_32BITS);
    texFactory.SetTextureMode(cTV_TEXTUREMODE_BETTER);
    //texFactory.SetTextureMode(cTV_TEXTUREMODE_16BITS);
    //texFactory.SetTextureMode(cTV_TEXTUREMODE_PALETTIZED8BITS);


    camera = scene->GetCamera();
    camera->SetViewFrustum(45.0, 80e3, 4);

    atmosphere = new CTVAtmosphere();

    lightEngine = new CTVLightEngine();
    lightEngine->DeleteAllLights();
    lightEngine->SetGlobalAmbient(0, 0, 0);

    //scene->SetRenderMode(cTV_LINE); // wireframe
    internalObjects = new CTVInternalObjects;

    //materialFactory.SetAmbient(0, 1, 1, 1, 1);

    //defaultMaterial = matFac.CreateLightMaterial(0.5f, 0.5f, 0.5f, 1.0, 0.4f, 0.3f, "DefaultMaterial");
    defaultMaterial = materialFactory.CreateLightMaterial(1.0f, 1.0f, 1.0f, 1.0, 0.4f, 0.3f, "StandardMaterial");
    //defaultMaterial = matFac.CreateMaterialQuick(1.0, 1.0, 1.0, 1.0, "DefaultMaterial");
}


void tcTVEngine::SetTextureFilterMode2d(int mode)
{
    screen2D.Settings_SetTextureFilter(cCONST_TV_TEXTUREFILTER(mode));
}

void tcTVEngine::TestFrame()
{
    engine->Clear(false);

    screen2D.Action_Begin2D();
    screen2D.Draw_Line(10.0, 10.0, 20.0, 20.0);
    screen2D.Action_End2D();

    text2D.Action_BeginText();
    text2D.TextureFont_DrawTextScaled("Text with iii's!", 300.0f, 50.0f, RGBA(1.0, 0.0, 0.0, 1.0), 2.0f, 2.0f);
    text2D.Action_EndText();

    // Render Everything
    //scene->RenderAll(true);

    engine->RenderToScreen();
}

void tcTVEngine::UpdateOptions()
{
    tcOptions* options = tcOptions::Get();

    int newAntialiasing;
    switch (options->antialiasing)
    {
    case 0: newAntialiasing = 0; break;
    case 1: newAntialiasing = 4; break;
    case 2: newAntialiasing = 16; break;
    default: newAntialiasing = antialiasing; wxASSERT(false); break;
    }

    if (antialiasing != newAntialiasing)
    {
        engine->SetAntialiasing(true, (cCONST_TV_MULTISAMPLE_TYPE)newAntialiasing);
        antialiasing = newAntialiasing;
    }

    bool newVsync = options->vsync != 0;
    if (vsync != newVsync)
    {
        engine->SetVSync(newVsync);
        vsync = newVsync;
    }

    int newTextureFilterMode3d = options->textureFilterMode3d;

    if (textureFilterMode3d != newTextureFilterMode3d)
    {
        scene->SetTextureFilter(cCONST_TV_TEXTUREFILTER(newTextureFilterMode3d));
        textureFilterMode3d = newTextureFilterMode3d;
    }

    int newTextureFilterMode2d = options->textureFilterMode2d;
    if (textureFilterMode2d != newTextureFilterMode2d)
    {
        screen2D.Settings_SetTextureFilter(cCONST_TV_TEXTUREFILTER(newTextureFilterMode2d));
        textureFilterMode2d = newTextureFilterMode2d;
    }

}

tcTVEngine::tcTVEngine()
: engine(0), 
  scene(0), 
  camera(0),
  atmosphere(0),
  antialiasing(0),
  vsync(false),
  enableTL(true),
  textureFilterMode3d(0),
  textureFilterMode2d(0),
  defaultMaterial(-1)
{
    tcOptions* options = tcOptions::Get();
    antialiasing = options->antialiasing;
    vsync = options->vsync != 0;
    textureFilterMode3d = options->textureFilterMode3d;
    textureFilterMode2d = options->textureFilterMode2d;
}

tcTVEngine::~tcTVEngine()
{
    scene->DestroyAllMeshes();
    scene->DestroyAllLandscapes();

    delete scene;
    scene = 0;

    delete atmosphere;
    atmosphere = 0;

    if (engine != 0)
    {
        delete engine;
        engine = 0;
    }

    delete lightEngine;
    lightEngine = 0;

    delete internalObjects;
}