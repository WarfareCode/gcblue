/*
**  @file tc3DTerrain.cpp
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

//#ifndef WX_PRECOMP
//#include "wx/wx.h" 
//#ifdef WIN32
//#include "wx/msw/private.h" // for MS Windows specific definitions
//#endif // WIN32
//#endif // WX_PRECOMP

#include "tc3DTerrain.h"

#include "simmath.h"
#include "tcMapData.h"
#include "tcTerrainTextureFactory.h"
#include "tcTime.h"
//#include "tcShaderControl.h"

#include "tcTVEngine.h"
#include "CTVGraphicEffect.h"
#include "CTVRenderSurface.h"
#include "CTVLandscape.h"
#include "CTVMaterialFactory.h"
#include "tcTexture2D.h"
#include "tc3DWindow2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif 




/**
*
*/
void tc3DTerrain::SetupWater()
{
    tcTVEngine* engine = tcTVEngine::Get();
    CTVScene* scene = engine->GetScene();
    CTVTextureFactory* texFactory = engine->GetTextureFactory();


    if (water == 0)
    {
        water = scene->CreateMeshBuilder("water");

        int id = texFactory->LoadDUDVTexture("images\\waves.dds", 0, -1, -1, 16.0, true);

        const float waterSurface = 0;
//        const int waterRenderSize = 512;
        water->AddFloor(id, -50000, -50000, 50000, 50000, waterSurface, 2, 2);
    }


    if (waterReflection != 0)
    {
        waterReflection->Destroy();
        waterReflection = 0;
    }
    if (waterRefraction != 0)
    {
        waterRefraction->Destroy();
        waterRefraction = 0;
    }
    
    if (waterEffect == 0)
    {
        waterEffect = new CTVGraphicEffect();
    }


    waterReflection = scene->CreateRenderSurface(width, height, true);
    waterReflection->SetBackgroundColor(RGBA(0, 0, 0.1f, 1.0f));

    waterRefraction = scene->CreateRenderSurface(width, height, true);
    waterRefraction->SetBackgroundColor(RGBA(0, 0, 0.1f, 1.0f));

    waterPlane.Normal.set(0, 1, 0);
    waterPlane.Dist = 0;
    waterReflectionColor = cTV_COLOR(0.75f, 0.75f, 0.9f, 0.7f);

    waterRefractionColor = cTV_COLOR(0.25f, 0.25f, 0.25f, 0.3f);

    waterEffect->SetWaterReflection(water, waterReflection, waterRefraction, 0, &waterPlane);
    //waterEffect->SetWaterReflectionBumpAnimation(water, false, 0, 0);
    waterEffect->SetWaterReflectionColor(water, &waterReflectionColor, &waterRefractionColor, 0.5);

    waterEffect->SetWaterReflectionBumpAnimation(water, true, 0.01f, 0.01f);

    water->Enable(isEnabled);

	// create simple water mesh, a textured quad
	if (simpleWater == 0)
	{
		simpleWater = scene->CreateMeshBuilder("simplewater");
		int waterTexture = texFactory->LoadTexture("3d\\water2b.bmp");
		simpleWater->AddFloor(waterTexture, -50000.0f, -50000.0f, 50000.0f, 50000.0f, 0, 50.0f, 50.0f);
		simpleWater->SetCullMode(cTV_DOUBLESIDED);
		simpleWater->SetLightingMode(cTV_LIGHTING_NORMAL); // cTV_LIGHTING_NORMAL

		CTVMaterialFactory materialFactory;
		int waterMat = materialFactory.CreateMaterial("WaterMaterial");

		materialFactory.SetAmbient(waterMat, 1, 1, 1, 0);
		materialFactory.SetDiffuse(waterMat, 1, 1, 1, 1);
		materialFactory.SetEmissive(waterMat, 0, 0, 0, 0);
		materialFactory.SetSpecular(waterMat, 1, 1, 1, 0);
		materialFactory.SetPower(waterMat, 1);

		simpleWater->SetMaterial(waterMat);

        simpleWater->Enable(false);
    }

}

void tc3DTerrain::SetWaterColor(const Vec4& reflection, const Vec4& refraction, float customFresnel)
{
    waterReflectionColor = cTV_COLOR(reflection.x, reflection.y, reflection.z, reflection.w);
    waterRefractionColor = cTV_COLOR(refraction.x, refraction.y, refraction.z, refraction.w);

    waterEffect->SetWaterReflectionColor(water, &waterReflectionColor, &waterRefractionColor, customFresnel);
}


void tc3DTerrain::CheckElevations()
{
#if 0
    int errorCount = 0;
    wxASSERT(mapData);
    
    for(int i=0;i<GRID_DIM;i++)
    {            
        float y = (float)i * gridSpacing + gridOffset;
        float lat_deg = C_180OVERPI*YToLat(y); 
        float ycheck = LatToY(lat_deg*C_PIOVER180);
        if (fabsf(ycheck-y)>0.05f)
        {
            errorCount++;
        }
        for(int j=0;j<GRID_DIM;j++)
        {
            float x = (float)j * gridSpacing + gridOffset;
            float lon_deg = C_180OVERPI*XToLon(x);
            float xcheck = LonToX(lon_deg*C_PIOVER180);
            if (fabsf(xcheck-x)>0.05f)
            {
                errorCount++;
            }

            float height = mapData->GetTerrainHeight(lon_deg, lat_deg, gameTime);
            float setHeight = (height < 0) ? -500 : height;
            float terrainElevation = terrain->GetElevation(x,y);
            if (fabs(terrainElevation - setHeight) > 0.01f)
            {
                errorCount++;
            }
        }
    }
#endif
}

/**
* Call every frame to support gradual terrain loading
*/
void tc3DTerrain::Update()
{
//    wxASSERT(texFactory);
    //if (texFactory) texFactory->Update();
}

void tc3DTerrain::UpdateCameraPosition(const Vec3& pos)
{
    wxASSERT(water != 0);
    water->SetPosition(pos.x, 0, pos.z); // center water under camera
    waterPlane.Dist = 0;
}


void tc3DTerrain::UpdateElevations()
{
    wxASSERT(mapData);

    for(int i=0;i<GRID_DIM;i++)
    {            
        float y = (float)i * gridSpacing + gridOffset;
        float lat_deg = C_180OVERPI*YToLat(y); 
        for(int j=0;j<GRID_DIM;j++)
        {
            float x = (float)j * gridSpacing + gridOffset;
            float lon_deg = C_180OVERPI*XToLon(x);
            float height = mapData->GetTerrainHeight(lon_deg, lat_deg, gameTime);
            long idx = i*GRID_DIM + j;
            //elevationArray[idx] = (height < 0) ? 0.001f*height : height;
            elevationArray[idx] = height;
            
            //if ((i==5) && (j == 5))
            //{
            //    elevationArray[idx] = 2000.0f;
            //}
            //else
            //{
            //    elevationArray[idx] = 0;
            //}
            //
            //if (j % 2 == 0)
            //    elevationArray[idx] = 500.0f;
            //else
            //    elevationArray[idx] = 1500.0f;
            
        }
    }

    landscape->SetHeightArray(0, 0, 256, 256, elevationArray);
    landscape->FlushHeightChanges(true, true);


    terrainTextureFactory->UpdateTexture(terrainTexture.get(), gridOffset, gridOffset, 256e3, 256e3);

    landscape->SetTexture(terrainTexture->GetId());
    landscape->ExpandTexture(terrainTexture->GetId(), 0, 0, 4, 4);

    //landscape

    //terrain->SetAllElevations(&elevationArray[0], GRID_DIM, GRID_DIM, gridSpacing);

	//if (!terrainShaderOn)
	//{
	//	texFactory->UpdateBaseTexture(baseTexture);

	//	//texFactory->BuildTextures();

	//	terrain->SetTexture(baseTexture->GetBuffer(), baseTexture->GetWidth(),
	//		baseTexture->GetHeight());
	//}


//	unsigned t3 = tcTime::Get()->GetUpdated30HzCount();

    //terrain->SetMaximumVisibleBlockSize(64);
}

void tc3DTerrain::UpdateElevationsSlowly()
{
    wxASSERT(mapData);
    /*
    for(int i=0;i<GRID_DIM;i++)
    {            
        float y = (float)i * gridSpacing + gridOffset;
        float lat_deg = C_180OVERPI*YToLat(y); 
        for(int j=0;j<GRID_DIM;j++)
        {
            float x = (float)j * gridSpacing + gridOffset;
            float lon_deg = C_180OVERPI*XToLon(x);
            float height = mapData->GetTerrainHeight(lon_deg, lat_deg, gameTime);
            long idx = i*GRID_DIM + j;
            elevationArray[idx] = (height < 0) ? 0.001f*height : height;
        }
    }
    texFactory->BuildTextures();
    terrain->SetAllElevations(&elevationArray[0],GRID_DIM,GRID_DIM,gridSpacing);
    */
    //terrain->SetMaximumVisibleBlockSize(64);
}


void tc3DTerrain::Enable(bool state)
{
    if (isEnabled == state) return;

    isEnabled = state;

    wxASSERT((landscape != 0) && (water != 0));

    landscape->Enable(isEnabled);
    water->Enable(isEnabled);

}


float tc3DTerrain::GetElevation(float x, float y)
{
    float lat_deg = C_180OVERPI*YToLat(y); 
    float lon_deg = C_180OVERPI*XToLon(x);
    float elevation = mapData->GetTerrainHeight(lon_deg, lat_deg, gameTime);
    return elevation;
}

/**
* @return elevation at origin
*/
float tc3DTerrain::GetOriginElevation()
{
    return mapData->GetTerrainHeight(lonOrigin_rad, latOrigin_rad, gameTime);
}

CTVRenderSurface* tc3DTerrain::GetReflectionRS()
{
    return waterReflection;
}

CTVRenderSurface* tc3DTerrain::GetRefractionRS()
{
    return waterRefraction;
}

CTVLandscape* tc3DTerrain::GetLandscape()
{
    return landscape;
}

CTVMesh* tc3DTerrain::GetSimpleWaterMesh()
{
    return simpleWater;
}

CTVGraphicEffect* tc3DTerrain::GetWaterEffect()
{
    return waterEffect;
}

CTVMesh* tc3DTerrain::GetWaterMesh()
{
    return water;
}

/**
* This function and other similar ones were copied from tc3DViewer.
* @param lon longitude in radians
* @see LatToY, XToLon, YToLat
*/
float tc3DTerrain::LonToX(double lon) 
{
    return (float)((lon - lonOrigin_rad)*lonToGridX);
}

/**
* @param lat latitude in radians
*/
float tc3DTerrain::LatToY(double lat) 
{
    return (float)((lat - latOrigin_rad)*latToGridY);
}

/**
* @param x world coord to convert to longitude
*/
double tc3DTerrain::XToLon(float x) 
{
    return x*gridXToLon + lonOrigin_rad;
}

/**
* @param y world coord to convert to latitude
*/
double tc3DTerrain::YToLat(float y) 
{
    return y*gridYToLat + latOrigin_rad;
}

//void tc3DTerrain::Render()
//{
//    landscape->Render();
//    water->Render();
//}

/**
* Set the origin (0,0) of 3D world coordinates and
* update lonToGridX and gridXToLon scale factors which 
* change as a function of latitude. Call UpdateElevations to 
* update elevations for the map grid with new values based
* on the new origin.
*/
void tc3DTerrain::SetOrigin(double lon, double lat)
{
    lonOrigin_rad = lon;
    latOrigin_rad = lat;

    lonToGridX = C_RADTOM*cosf(latOrigin_rad);
    gridXToLon = 1/lonToGridX;

    latToGridY = C_RADTOM; 
    gridYToLat = C_MTORAD;

    UpdateElevations();
}

void tc3DTerrain::SetWindowSize(int width_, int height_)
{
    if ((width_ == width) && (height_ == height))
    {
        return;
    }

    width = width_;
    height = height_;

    SetupWater(); // have to recreate rendersurfaces and effects
}


tc3DTerrain::tc3DTerrain() :
    updateScheduled(false),
    updating(false),
    doGradualUpdate(true),
	mapData(0),
    landscape(0),
    water(0),
    simpleWater(0),
    waterReflection(0),
    waterRefraction(0),
    waterEffect(0),
	terrainTextureFactory(0),
    width(0),
    height(0),
    isEnabled(false)
{
	terrainShaderOn = tcOptions::Get()->terrainShaderOn != 0;

	gridSpacing = 1000.0f;


    tcTVEngine* engine = tcTVEngine::Get();
    CTVScene* scene = engine->GetScene();

    landscape = scene->CreateLandscape("gcb_terrain");

    int landscapePrecision = cTV_PRECISION_BEST;
    float landscapeScale = gridSpacing / float(landscapePrecision);
    gridOffset = -0.5f*((float)GRID_DIM)*gridSpacing;

    //gridOffset = -1000.0f;

    // material for landscape
    CTVMaterialFactory materialFactory;
    int landscapeMat = materialFactory.CreateMaterial("MainMaterial");

    materialFactory.SetAmbient(landscapeMat, 1, 1, 1, 0);
    materialFactory.SetDiffuse(landscapeMat, 1, 1, 1, 1);
    materialFactory.SetEmissive(landscapeMat, 0, 0, 0, 0);
    materialFactory.SetSpecular(landscapeMat, 1, 1, 1, 0);
    materialFactory.SetPower(landscapeMat, 1);

    // detail texture
    detailTexture = tc3DWindow2::LoadTexture("detail_tex.png");


    landscape->SetScale(landscapeScale, 1.0f, landscapeScale);
    landscape->CreateEmptyTerrain((cCONST_TV_LANDSCAPE_PRECISION)landscapePrecision, 4, 4, gridOffset, 0, gridOffset);
    landscape->EnableLOD(true, 512.0, cTV_PRECISION_BEST, 0, true);
    landscape->Enable(false);
    landscape->SetLightingMode(cTV_LIGHTING_MANAGED); // cTV_LIGHTING_NORMAL
    landscape->SetMaterial(landscapeMat);
    landscape->SetDetailTexture(detailTexture->GetId());
    landscape->SetDetailTextureScale(500.0f, 500.0f);

    landscape->SetDetailMode(cTV_DETAILMAP_MODULATE);

//    CTVTextureFactory* texFactory = engine->GetTextureFactory();

    //int id = texFactory->LoadTexture("tvm_test\\sand.jpg", "LandTexture");
    //landscape->SetTexture(id);

    terrainTextureFactory = new tcTerrainTextureFactory(this);
    terrainTexture = boost::shared_ptr<tcTexture2D>(new tcTexture2D());
    terrainTexture->Create(512, 512, false, "TerrainTexture");

    

	//baseTexture = tcTerrainTextureFactory::CreateEmptyTexture(BASE_TEX_DIM);

 //   terrain = new Demeter::Terrain(&elevationArray[0], GRID_DIM, GRID_DIM, 
	//	baseTexture->GetBuffer(), BASE_TEX_DIM, BASE_TEX_DIM, 
 //       NULL, 0, 0,
 //       gridSpacing, 1.0f, 50000,
 //       gridOffset, gridOffset);

 //   Demeter::DemeterDrawable* pDrawable = new Demeter::DemeterDrawable;
 //   pDrawable->SetTerrain(terrain.get());

	//if (!terrainShaderOn)
	//{
	//	texFactory = new tcTerrainTextureFactory(terrain.get(), this, TEX_CELL_DIM); 
	//
	//	if (tcOptions::Get()->shadersOn == 0)
	//	{
	//		texFactory->UpdateCommonTexture();
	//	}
	//}
	//else
	//{
	//	osg::StateSet* terrainState = pDrawable->getOrCreateStateSet();
	//	tcShaderControl::Get()->AddTerrainElevationShader(terrainState);
	//}

 //   terrainNode = new osg::Geode;

 //   terrainNode->addDrawable(pDrawable);
 //   terrainNode->setCullingActive(true); // disables small feature and view frustrum culling
 //   float detailThreshold = 6.0f;

	//if (terrainShaderOn)
	//{
	//	detailThreshold = 1.0f;
	//}


 //   terrain->SetDetailThreshold(detailThreshold);


}

tc3DTerrain::~tc3DTerrain()
{
    if (waterEffect) delete waterEffect;
    if (terrainTextureFactory) delete terrainTextureFactory;
    //if (texFactory) delete texFactory;
	//if (baseTexture) delete baseTexture;
}

