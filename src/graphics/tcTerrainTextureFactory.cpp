/**
**  tcTerrainTextureFactory.cpp
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
#ifdef WIN32
#include "wx/msw/private.h" // for MS Windows specific definitions
#endif // WIN32
#endif // WX_PRECOM


#include "tcTerrainTextureFactory.h"
#include "tcTexture2D.h"
#include "tc3DTerrain.h"
#include "CTVLandscape.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif 




void tcTerrainTextureFactory::UpdateBaseTexture(tcTexture2D* texture)
{
	//UpdateTexture(texture, 0, 0, terrainx->GetWidth(), terrainx->GetHeight());
}


/**
* Create empty textures and update procedural texture data
* if doGradualUpdate is true, set updateScheduled to true and
* return instead.
*/
void tcTerrainTextureFactory::BuildTextures()
{
    if (doGradualUpdate)
    {
        updateScheduled = true;
        return;
    }
#if 0
    float gridWidth = terrainx->GetWidth();
    float gridHeight = terrainx->GetHeight();
    float gridStepX = gridWidth / (float)gridDimension;
    float gridStepY = gridHeight / (float)gridDimension;

    int nY = 0;


    for (float y = 0; y < gridHeight; y += gridStepY)
    {
        nY++;
        int nX = 0;
        for (float x = 0; x < gridWidth; x += gridStepX)
        {
            nX++;

            int cacheIdx = GetTextureIndex(x, y);
            Demeter::Texture* pTexture = m_Textures[cacheIdx];
            // create a new texture if one doesn't exist ("lazy init")
            if (pTexture == NULL)
            {
                m_Textures[cacheIdx] = CreateEmptyTexture(nX, nY);
                pTexture = m_Textures[cacheIdx];
                //fprintf(stdout,"created tex:%d (x,y):(%.0f,%.0f)\n",cacheIdx,x,y);
            }

            UpdateTexture(pTexture, x, y, gridStepX, gridStepY);
        }
    }
#endif

}

            



void tcTerrainTextureFactory::UpdateTexture(tcTexture2D* pTexture, 
                                            float originX, float originY, 
                                            float width, float height)
{

	int nTexSize = pTexture->Width();
	float texSize = nTexSize;
    float texelSpacing = width / texSize;  // assumes square texture
    

    pTexture->Lock();
    for (int k=0; k<NUM_TEXTURES; k++)
    {
        textureInfo[k].tex->Lock();
    }


    //pTexture->UnloadTexture();

    float alpha[NUM_TEXTURES];


	float y = originY;
    for (long yIdx = 0; yIdx < nTexSize; yIdx++)
    {
		float x = originX;
		for (long xIdx = 0; xIdx < nTexSize; xIdx++)
        {

            float elev = terrain->GetElevation(x, y);


            // calculate alpha for each texture
            bool searching = true;
            int nTex = 0;
            for (nTex=0;(nTex<NUM_TEXTURES)&& searching;nTex++)
            {
                float zmin = textureInfo[nTex].zmin;
                float zlow = textureInfo[nTex].zlow;
                float zhigh = textureInfo[nTex].zhigh;
                float zmax = textureInfo[nTex].zmax;
                if ((elev < zmin)||(elev >= zmax))
                    alpha[nTex] = 0;
                else if (elev < zlow)
                    alpha[nTex] = (elev - zmin)/(zlow-zmin);
                else if (elev < zhigh)
                {
                    alpha[nTex] = 1.0f;
                    searching = false;
                }
                else
                    alpha[nTex] = 1.0f - (elev - zhigh)/(zmax-zhigh);
            }
            for (;nTex<NUM_TEXTURES;nTex++)
            {
                alpha[nTex] = 0;
            }

            float red = 0;
            float green = 0;
            float blue = 0;


            // calculate red, green, blue
            for (nTex=0; nTex<NUM_TEXTURES; nTex++)
            {
                int N = textureInfo[nTex].tex->Width();
                int argb = textureInfo[nTex].tex->GetPixel(xIdx % N, yIdx % N);
                
                red += alpha[nTex] * float((argb >> 16) & 0xFF);
                green += alpha[nTex] * float((argb >> 8) & 0xFF);
                blue += alpha[nTex] * float(argb & 0xFF);

            }

            int argb_out = 0xFF000000 + (int(red) << 16) + (int(green) << 8) + int(blue);
            pTexture->SetPixel(xIdx, yIdx, argb_out);

			x += texelSpacing;
        }

		y += texelSpacing;
    }

    for (int k=0; k<NUM_TEXTURES; k++)
    {
        textureInfo[k].tex->Unlock();
    }
    pTexture->Unlock();

}


/**
* Calculates cache index for texture with origin at (x,y).
* (x,y) relative to (0,0) = SW corner of terrainx grid
*/
int tcTerrainTextureFactory::GetTextureIndex(float x, float y)
{
    return 0;
#if 0
    float gridWidth = terrainx->GetWidth();
    float gridHeight = terrainx->GetHeight();
    int i = (int)floorf(y/gridHeight*(float)gridDimension + 0.5);
    int j = (int)floorf(x/gridWidth*(float)gridDimension + 0.5);
    int idx = i*gridDimension + j;

    wxASSERT((idx >= 0)&&(idx < gridDimension*gridDimension));
    return idx;
#endif
}


void tcTerrainTextureFactory::LoadTerrainTextures()
{
    int n = 0;
    //seaTexture = osgDB::readImageFile("water2b.bmp");
    seaTexture->Load("3d\\rock_texture_b.jpg");
    textureInfo[n].zmin = -1000.0f;
    textureInfo[n].zlow = -999.0f;
    textureInfo[n].zhigh = -150.0f;
    textureInfo[n].zmax = -60.0f;
    textureInfo[n].tex = seaTexture.get();
    n++;

    coastTexture->Load("3d\\rock04.bmp");
    textureInfo[n].zmin = textureInfo[n-1].zhigh;
    textureInfo[n].zlow = textureInfo[n-1].zmax;
    textureInfo[n].zhigh = -15.0f;
    textureInfo[n].zmax = 0.0f;
    textureInfo[n].tex = coastTexture.get();
    n++;

    sandTexture->Load("3d\\sand12.bmp");
    textureInfo[n].zmin = textureInfo[n-1].zhigh;
    textureInfo[n].zlow = textureInfo[n-1].zmax;
    textureInfo[n].zhigh = 5.0f;
    textureInfo[n].zmax = 15.0f;
    textureInfo[n].tex = sandTexture.get();
    n++;

    grassTexture->Load("3d\\grass20.bmp");
    textureInfo[n].zmin = textureInfo[n-1].zhigh;
    textureInfo[n].zlow = textureInfo[n-1].zmax;
    textureInfo[n].zhigh = 60.0f;
    textureInfo[n].zmax = 90.0f;
    textureInfo[n].tex = grassTexture.get();
    n++;

    mountainTexture->Load("3d\\rock04b.bmp"); // same thing as rock04.bmp
    textureInfo[n].zmin = textureInfo[n-1].zhigh;
    textureInfo[n].zlow = textureInfo[n-1].zmax;
    textureInfo[n].zhigh = 10000.0f;
    textureInfo[n].zmax = 10001.0f;
    textureInfo[n].tex = mountainTexture.get();
    n++;

    // load default texture
    //wxASSERT(seaTexture->s()==seaTexture->t());
    //int texSize = seaTexture->s();
    //defaultTexture = new Demeter::Texture(seaTexture->data(),texSize,texSize,
    //    texSize,0,true,false,false);

    //wxASSERT(mountainTexture->s()==mountainTexture->t());
    //texSize = mountainTexture->s();
    //defaultTextureLand = new Demeter::Texture(mountainTexture->data(),texSize,texSize,
    //    texSize,0,true,false,false);

    groundDetailTexture->Load("3d\\sand_tex.bmp");

}



tcTexture2D* tcTerrainTextureFactory::GetTexture(int index,
                                                      float originX,float originY,
                                                      float width,float height)
{
    return 0;
#if 0
    int cacheIdx = GetTextureIndex(originX, originY);
    //fprintf(stdout, "originX,Y: %.0f, %.0f, cacheIdx:%d\n",originX,originY,cacheIdx);
	Demeter::Texture *tex = m_Textures[cacheIdx]; 
	if (tex == NULL)
	{
		float originHeight = terrain->GetOriginElevation();
		//	terrain->GetElevation(originX + 0.5*width, originY + 0.5*height);
		if (originHeight < 0)
		{
			return defaultTexture;
		}
		else
		{
		/* This is part of a workaround to show a land texture when loading 
		** textures over land. 
		*/
			return defaultTextureLand;
		}
	}
    else
    {
        return (updating) ? defaultTexture : tex;
    }
#endif
}



void tcTerrainTextureFactory::UnloadTexture(int index)
{
    // Called by the Demeter terrainx when a texture is no longer visible.
    // We could unload the texture here, set it to a lower priority for OpenGL, etc.
    // m_Textures[index]->UnloadTexture();
    // Keep the texture for now ...
}

/**
* Update one grid square every time through
*/
void tcTerrainTextureFactory::Update()
{
#if 0
    if (updateScheduled)
    {
        updateX = 0;
        updateY = 0;
        updateScheduled = false;
        updating = true;
    }

    if (!updating) return;

    float gridWidth = terrainx->GetWidth();
    float gridHeight = terrainx->GetHeight();
    float gridStepX = gridWidth / (float)gridDimension;
    float gridStepY = gridHeight / (float)gridDimension;

    if (updateY < gridHeight)
    {
        if (updateX < gridWidth)
        {
            int cacheIdx = GetTextureIndex(updateX, updateY);
            Demeter::Texture* pTexture = m_Textures[cacheIdx];

            // create a new texture if one doesn't exist ("lazy init")
            if (pTexture == NULL)
            {
                int nX = (int)floorf((updateX / gridStepX) + 0.1f);
                int nY = (int)floorf((updateY / gridStepY) + 0.1f);

                m_Textures[cacheIdx] = CreateEmptyTexture(nX, nY);
                pTexture = m_Textures[cacheIdx];
            }

            UpdateTexture(pTexture, updateX, updateY, gridStepX, gridStepY);

            updateX += gridStepX;
        }
        else
        {
            updateX = 0;
            updateY += gridStepY;
        }
    }
    else
    {
        updating = false;
    }
#endif

}

void tcTerrainTextureFactory::UpdateCommonTexture()
{
#if 0
	if (terrainx)
	{
		terrainx->SetCommonTexture(groundDetailTexture->data(), 
			groundDetailTexture->s(), groundDetailTexture->t());
	}
#endif
}


tcTerrainTextureFactory::tcTerrainTextureFactory(tc3DTerrain *tm)
:   edgeDepthLow(2), 
    edgeDepthMed(3),
    textureSize(128.0f),
    textureSizeInt(128),
    textureSizeMed(64.0f),
    textureSizeMedInt(64),
    textureSizeLow(32.0f),
    textureSizeLowInt(32),
    updateScheduled(false),
    updating(false),
    doGradualUpdate(false),
    gridDimension(256),
    seaTexture(new tcTexture2D()),
    coastTexture(new tcTexture2D()),
    sandTexture(new tcTexture2D()),
    grassTexture(new tcTexture2D()),
    mountainTexture(new tcTexture2D()),
	groundDetailTexture(new tcTexture2D()),
    defaultTexture(new tcTexture2D()),
    defaultTextureLand(new tcTexture2D())

{
    terrain = tm;
    LoadTerrainTextures();
}

tcTerrainTextureFactory::~tcTerrainTextureFactory()
{

}
