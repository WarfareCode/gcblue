/**  
**  @file tcTVEngine.h
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

#ifndef _TCTVENGINE_H_
#define _TCTVENGINE_H_

#if _MSC_VER > 1000
#pragma once
#endif 

#ifndef WX_PRECOMP
#include "wx/wx.h" 
#endif 

#include "HelperFunctions.h"
#include "CTVEngine.h"
#include "CTVGlobals.h"
#include "CTVScene.h"
#include "CTVScreen2DImmediate.h"
#include "CTVScreen2DText.h"
#include "CTVTextureFactory.h"
#include "CTVInputEngine.h"
#include "CTVLightEngine.h"
#include "CTVMaterialFactory.h"
#include "tv_types.h"


class CTVCamera;
class CTVAtmosphere;
class CTVInternalObjects;

class tcTVEngine
{
public:
    void Clear(bool bOnlyZBuffer = false);
    void Frame();
    static tcTVEngine* Get();

    CTVRenderSurface* Create2DRenderSurface(int width, int height);
    CTVCamera* GetCamera();
    CTVScene* GetScene();
    CTVScreen2DImmediate* GetScreen2D(); ///< @return 2D graphics draw object
    CTVScreen2DText* GetText2D(); ///< @return 2D text draw object
    CTVTextureFactory* GetTextureFactory();
    CTVViewport* GetViewport();
    CTVAtmosphere* GetAtmosphere();
    CTVLightEngine* GetLightEngine();
    CTVMaterialFactory* GetMaterialFactory();

    void InitTV3D(HWND hwnd, bool isWindowed);
    void TestFrame();
    void ClearZBuffer();
    void DisableZBuffer();
    void EnableZBuffer();

    void DisableAlphaBlend();
    void EnableAlphaBlend();
    void ForceSourceAlpha();

    int GetFreeTextureMemory();
    int GetUsedTextureMemory();

    void UpdateOptions();

    void AddToLog(const char* text);

    int GetDefaultMaterial() const;

    int GetTextureFilterMode2d() const;
    void SetTextureFilterMode2d(int mode);

private:
    CTVEngine* engine;
    CTVScene* scene;
    CTVCamera* camera;
    CTVAtmosphere* atmosphere;
    CTVInternalObjects* internalObjects;
    CTVLightEngine* lightEngine;


    CTVTextureFactory texFactory;
    CTVMaterialFactory materialFactory;
    CTVScreen2DImmediate screen2D;
    CTVScreen2DText text2D;
    CTVGlobals globals;

    int antialiasing;
    bool vsync;
    bool enableTL; // hardware transform and lighting
    int textureFilterMode3d;
    int textureFilterMode2d;
    int defaultMaterial;

    tcTVEngine();
    virtual ~tcTVEngine();
};


#endif


