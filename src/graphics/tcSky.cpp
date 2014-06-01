/**  
**  @file tcSky.cpp
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

#include "tcSky.h"
#include "tcTVEngine.h"
#include "math_constants.h"
#include "tcSkyModel.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif 


void tcSky::BuildSkyDome()
{
    tcTVEngine* engine = tcTVEngine::Get();
    CTVScene* scene = engine->GetScene();
    tcSkyModel* skyModel = tcSkyModel::Get();

    if (skyDomeTop != 0)
    {
        scene->DestroyMesh(skyDomeTop);
    }
    if (skyDomeBase != 0)
    {
        scene->DestroyMesh(skyDomeBase);
    }

    skyDomeTop = scene->CreateMeshBuilder("SkyDomeTop");
    skyDomeBase = scene->CreateMeshBuilder("SkyDomeBase");



	float maxElevation_rad = C_PIOVER180*maxElevation_deg;
	float minElevation_rad = C_PIOVER180*minElevation_deg;

    // create top
    skyDomeTop->SetLightingMode(cTV_LIGHTING_NONE);
    skyDomeTop->SetPrimitiveType(cTV_TRIANGLEFAN);
    skyDomeTop->SetCullMode(cTV_DOUBLESIDED);
    skyDomeTop->SetMeshFormat(cTV_MESHFORMAT_NOLIGHTING | cTV_MESHFORMAT_NOTEX | cTV_MESHFORMAT_DIFFUSE); //  
    skyDomeTop->SetOverlay(true);
    skyDomeTop->SetAlphaTest(false, 128, false);
    skyDomeTop->EnableFrustumCulling(false);

    float y_top = radius * sinf(maxElevation_rad);
    float r_top = radius * cosf(maxElevation_rad); // radius of dome top
	
    Vec3 zenithColor = skyModel->GetZenithColor();
    int color_top = RGBA(zenithColor.x, zenithColor.y, zenithColor.z, 1);

    // add center
    skyDomeTop->AddVertex(0, y_top, 0, 0, 1, 0, 0, 0, 0, 0, color_top);

    float daz = C_TWOPI / float(resolutionAz);
    int color_k_int = -1;
    for (int k=0; k<resolutionAz; k++)
    {   
        float az_k = float(k)*daz;
        float x_top = r_top * sinf(az_k);
        float z_top = r_top * cosf(az_k);

        Vec3 color_k = skyModel->GetSkyColor(maxElevation_rad, az_k);    
        color_k_int = RGBA(color_k.x, color_k.y, color_k.z, 1.0f);
        skyDomeTop->AddVertex(x_top, y_top, z_top, 0, -1, 0, 0, 0, 0, 0, color_k_int);
    }

    skyDomeTop->AddVertex(0, y_top, r_top, 0, -1, 0, 0, 0, 0, 0, color_k_int); // complete circle


    // create base
    skyDomeBase->SetLightingMode(cTV_LIGHTING_NONE);
    skyDomeBase->SetPrimitiveType(cTV_TRIANGLESTRIP);
    skyDomeBase->SetCullMode(cTV_FRONT_CULL); //cTV_DOUBLESIDED);
    skyDomeBase->SetMeshFormat(cTV_MESHFORMAT_NOLIGHTING | cTV_MESHFORMAT_NOTEX | cTV_MESHFORMAT_DIFFUSE ); //  );
    skyDomeBase->SetOverlay(true);
    skyDomeBase->SetAlphaTest(false, 128, false);

    skyDomeBase->EnableFrustumCulling(false);


    float del = (maxElevation_rad - minElevation_rad) / float(resolutionEl);
//    float el_rad = maxElevation_rad;

    for (int k=0; k<resolutionEl; k++)
    {
        float el_rad_top = maxElevation_rad - float(k)*del;
        float el_rad_bottom = maxElevation_rad - float(k+1)*del;

        float y_top = radius * sinf(el_rad_top);
        float y_bottom = radius * sinf(el_rad_bottom);
        float r_top = radius * cosf(el_rad_top);
        float r_bottom = radius * cosf(el_rad_bottom);


        

        for (int k=0; k<resolutionAz; k++)
        {    
            float az_k = float(k)*daz;

            float x_top = r_top * sinf(az_k);
            float z_top = r_top * cosf(az_k);
            float x_bottom = r_bottom * sinf(az_k);
            float z_bottom = r_bottom * cosf(az_k);

            Vec3 colorTop = skyModel->GetSkyColor(el_rad_top, az_k);
            Vec3 colorBottom = skyModel->GetSkyColor(el_rad_bottom, az_k);
            int color_top = RGBA(colorTop.x, colorTop.y, colorTop.z, 1.0f);
            int color_bottom = RGBA(colorBottom.x, colorBottom.y, colorBottom.z, 1.0f);

            skyDomeBase->AddVertex(x_top, y_top, z_top, 0, -1, 0, 0, 0, 0, 0, color_top);
            skyDomeBase->AddVertex(x_bottom, y_bottom, z_bottom, 0, -1, 0, 0, 0, 0, 0, color_bottom);
        }

        Vec3 colorTop = skyModel->GetSkyColor(el_rad_top, 0);
        Vec3 colorBottom = skyModel->GetSkyColor(el_rad_bottom, 0);
        int color_top = RGBA(colorTop.x, colorTop.y, colorTop.z, 1.0f);
        int color_bottom = RGBA(colorBottom.x, colorBottom.y, colorBottom.z, 1.0f);

        skyDomeBase->AddVertex(0, y_top, r_top, 0, -1, 0, 0, 0, 0, 0, color_top);
        skyDomeBase->AddVertex(0, y_bottom, r_bottom, 0, -1, 0, 0, 0, 0, 0, color_bottom);

    }

    skyDomeTop->Enable(false);
    skyDomeBase->Enable(false);




}



void tcSky::Render()
{
    wxASSERT(skyDomeTop != 0);

    skyDomeTop->Enable(true);
    skyDomeBase->Enable(true);

    skyDomeTop->Render();
    skyDomeBase->Render();
    
    skyDomeTop->Enable(false);
    skyDomeBase->Enable(false);

}

void tcSky::SetRadius(float val)
{
    if (radius == val) return;

    radius = val;
    if (skyDomeTop == 0) return;
    BuildSkyDome(); // rebuild with new radius
}

void tcSky::UpdateCameraPosition(const Vec3& pos)
{
    skyDomeTop->SetPosition(pos.x, 0, pos.z);
    skyDomeBase->SetPosition(pos.x, 0, pos.z);
}


tcSky::tcSky()
:
  baseDayAmbient(1, 1, 1),
  baseNightAmbient(0, 0, 0),
  baseDayColor(0, 0, 1),
  baseNightColor(0, 0, 0),
  resolutionAz(64),
  resolutionEl(32),
  maxElevation_deg(55),
  minElevation_deg(-15),
  radius(14e8),
  heightScale(1),
  origin(0, 0, 0),
  skyDomeTop(0),
  skyDomeBase(0)
{
}

tcSky::~tcSky()
{
}