/**  
**  tcTerrainTextureFactory.h
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


#ifndef _TERRAINTEXTUREFACTORY_H_
#define _TERRAINTEXTUREFACTORY_H_

#ifdef WIN32
#pragma once
#endif 


#include <map>
#include <boost/shared_ptr.hpp>

class tc3DTerrain;
class tcTexture2D;
class CTVLandscape;

/**
* Class to do procedural texture generation for Demeter terrain
* Modify this to use iterator for std::map
* 25JUL Dewitt - This was reworked to use a single procedural texture.
*    There was no way to display terrain without seams with the old 
*    code derived from Demeter::TextureFactory
*/
class tcTerrainTextureFactory
{
public:
    void BuildTextures(); ///< rebuilds procedural textures, called when origin changes
	static tcTexture2D* CreateEmptyTexture(int texSize);

	void UpdateCommonTexture();
	void UpdateBaseTexture(tcTexture2D* texture);

    void Update(); ///< called every frame to distribute texture loading over multiple frames
    void UpdateTexture(tcTexture2D* pTexture, float originX, float originY, 
        float width, float height);

    tcTerrainTextureFactory(tc3DTerrain *tm);

    virtual ~tcTerrainTextureFactory();
    virtual tcTexture2D* GetTexture(int index, float originX, float originY, float width, float height);
    virtual void UnloadTexture(int index);
private:
    enum
    {
        NUM_TEXTURES=5
    };
    int gridDimension; ///< number of texture cells along one dimension of grid
    const int edgeDepthLow; ///< distance from edge of grid to use low resolution
    const int edgeDepthMed; ///< distance from edge of grid to use med res (if not low res)
    const float textureSize; ///< high resolution texture size
    const int textureSizeInt;
    const float textureSizeMed ; ///< medium resolution texture size
    const int textureSizeMedInt;
    const float textureSizeLow; ///< low resolution texture size
    const int textureSizeLowInt;
    bool updateScheduled;
    bool updating;
    float updateX;
    float updateY;
    bool doGradualUpdate; ///< true to calculate procedural textures over multiple frames


    tc3DTerrain* terrain; 


    boost::shared_ptr<tcTexture2D> seaTexture;
    boost::shared_ptr<tcTexture2D> coastTexture;
    boost::shared_ptr<tcTexture2D> sandTexture;
    boost::shared_ptr<tcTexture2D> grassTexture;
    boost::shared_ptr<tcTexture2D> mountainTexture;
	boost::shared_ptr<tcTexture2D> groundDetailTexture;

    boost::shared_ptr<tcTexture2D> defaultTexture;
    boost::shared_ptr<tcTexture2D> defaultTextureLand; // workaround to show land texture for default over land

    struct
    {
        float zmin; ///< minimum elevation for texture
        float zlow; ///< minimum elevation for opaque texture
        float zhigh; ///< maximum elevation for opaque texture
        float zmax; ///< maximum elevation for texture
        tcTexture2D* tex;
    } textureInfo[NUM_TEXTURES];


    int GetTextureIndex(float x, float y); ///< gets index of precalc tex for coord (x,y)
    void LoadTerrainTextures();

};

#endif

