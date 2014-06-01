/*  
**  @file tc3DTerrain.h
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

#ifndef _3DTERRAIN_H_
#define _3DTERRAIN_H_

#ifdef WIN32
#pragma once
#endif 

#include "tv_types.h"
#include <boost/shared_ptr.hpp>


class tcMapData;
class tcTerrainTextureFactory;
class CTVGraphicEffect;
class CTVLandscape;
class CTVMesh;
class CTVRenderSurface;

class tcTexture2D;


/**
* Class to use Demeter terrain library to display 3D terrain
* using data in tcMapData.
*/
class tc3DTerrain
{
public:

    void AttachMapData(tcMapData *pMapData) {mapData=pMapData;}
    void Enable(bool state);
    float GetElevation(float x, float y);
	float GetOriginElevation(); 

    CTVRenderSurface* GetReflectionRS();
    CTVRenderSurface* GetRefractionRS();
    CTVGraphicEffect* GetWaterEffect();
    CTVLandscape* GetLandscape();
    CTVMesh* GetWaterMesh();
    CTVMesh* GetSimpleWaterMesh();

    void SetWaterColor(const Vec4& reflection, const Vec4& refraction, float customFresnel);

    void SetGameTime(double t) {gameTime = t;}
    void SetOrigin(double lon, double lat); ///< sets origin of 3D world coordinates
    void SetWindowSize(int width_, int height_);

    void Update();
    void UpdateCameraPosition(const Vec3& pos);

    tc3DTerrain();
    ~tc3DTerrain();
private:
	struct WaterTileInfo
	{
		float half_width;
		float xc;
		float yc;
	};
    enum 
    {
        GRID_DIM = 256,
        TEX_CELL_DIM = 1,  ///< number of texture cells on side of grid
		BASE_TEX_DIM = 515
    };
	tcMapData* mapData; ///< pointer to tcMapData object
    float gridSpacing; ///< distance between neighbors in terrain grid [world coord units=m]
    float gridOffset; ///< offset for x and y for (0,0) grid element
    float elevationArray[(GRID_DIM)*(GRID_DIM)];
    bool isEnabled;

    CTVLandscape* landscape;

    CTVMesh* water;
    CTVMesh* simpleWater;
    CTVRenderSurface* waterReflection;
    CTVRenderSurface* waterRefraction;
    CTVGraphicEffect* waterEffect;
    cTV_PLANE waterPlane;
    cTV_COLOR waterReflectionColor;
    cTV_COLOR waterRefractionColor;
    
    int width;
    int height;

    boost::shared_ptr<tcTexture2D> terrainTexture;
    boost::shared_ptr<tcTexture2D> detailTexture;

	//Demeter::Texture* baseTexture;  ///< texture to drape over terrain, RGB bytes

    //osg::ref_ptr<Demeter::Terrain> terrain; ///< Demeter terrain object
    //osg::ref_ptr<osg::Geode> terrainNode; ///< drawable terrain object to place into osg scenegraph
    //osg::ref_ptr<osg::Geometry> waterSurface;
    //osg::ref_ptr<osg::Texture2D> waterTexture;

    tcTerrainTextureFactory* terrainTextureFactory;

    // these members are the same as in tc3DViewer (copied for simplicity for now)
    double lonOrigin_rad; ///< longitude for x = 0 in 3D world coords
    double latOrigin_rad; ///< latitude for z = 0 in 3D world coords (-z is North)
    double lonToGridX; ///< scale factor to convert to world coords
    double latToGridY; ///< scale factor to convert to world coords
    double gridXToLon; ///< scale factor to convert from world coords
    double gridYToLat; ///< scale factor to convert from world coords
    double gameTime; ///< current game time [s]

    // variables for gradual update
    bool updateScheduled;
    bool updating;
    int update_i;
    bool doGradualUpdate; ///< true to update elevation over multiple frames
	bool terrainShaderOn;

    float LonToX(double lon); 
    float LatToY(double lat);
    double XToLon(float x); 
    double YToLat(float y);   
    void CheckElevations();
    void SetupWater();
    void UpdateElevations();
    void UpdateElevationsSlowly();
};

#endif

