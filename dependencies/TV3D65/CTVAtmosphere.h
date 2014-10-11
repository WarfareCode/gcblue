#pragma once
#include "tv_types.h"

#include "CTVParticleSystem.h"


class EXPORTCLASS CTVAtmosphere
{
public:
	int iAtmosphereIndex;

	CTVAtmosphere(void);
	~CTVAtmosphere(void);

	void Atmosphere_Render(void);

	void Fog_Enable(bool bEnable); 
	void Fog_GetColor(float* fRed, float* fGreen, float* fBlue);
	void Fog_SetColor(float fRed, float fGreen, float fBlue);
	void Fog_SetParameters(float fStartFog = 1.0f, float fEndFog = 1000.0f, float fDensity = 0.01f);
	void Fog_GetParameters(float* fStartFog, float* fEndFog, float* fDensity);
	void Fog_SetType(cCONST_TV_FOG eFogAlgo, cCONST_TV_FOGTYPE eFogType);
	void Fog_GetType(cCONST_TV_FOG* eFogAlgo, cCONST_TV_FOGTYPE* eFogType);
	bool Fog_IsEnabled();

	void LensFlare_Enable(bool bEnable);
	void LensFlare_SetLensNumber(int lNumber);
	void LensFlare_SetLensParams(int lLensIndex, int lTexture, float fSize, float fLinePosition, int lNormalColor, int lSpecularColor = 0xffffffff);
 
	void Rain_Enable(bool bEnable);
	void Rain_Init(float fDensity, int iRainTexture, float fFallSpeed = 1.0f, float fWindX = 0.0f, float fWindZ = 0.0f, float fRandomValue = 0.1f, float fDistRain = 20.0f, float fRainParticleSize = 1.0f, float fRainRadius = 20.0f, int iRainGeneratorSpeed = 20, float fRainSpeed = 1.0f);
	
	void SkyBox_Enable(bool bEnable);
	void SkyBox_SetRotation(float fRotationX, float fRotationY, float fRotationZ);
	void SkyBox_SetColor(float r, float g, float b, float a);
	void SkyBox_SetTexture(int iFront, int iBack, int iLeft, int iRight, int iTop, int iBottom);
	void SkyBox_SetScale(float x, float y, float z); 
	void SkyBox_GetColor(float* ret_fRed, float* ret_fGreen, float* ret_fBlue, float* ret_fAlpha);
	void SkyBox_GetScale(float* ret_fX, float* ret_fY, float* ret_fZ);
	void SkyBox_GetTexture(int* iFront, int* iBack, int* iLeft, int* iRight, int* iTop, int* iBottom);
	void SkyBox_SetDepthWrite(bool bEnableDepthWrite);
	bool SkyBox_IsEnabled();

	void SkySphere_Enable(bool bEnable);
	void SkySphere_SetRotation(float fRotationX, float fRotationY, float fRotationZ);
	void SkySphere_SetColor(float fRed, float fGreen, float fBlue, float fAlpha);
	void SkySphere_SetRadius(float fRadius);
	void SkySphere_SetTexture(int iTexture);
	void SkySphere_SetParameters(bool bUseHemisphere);
	void SkySphere_SetScale(float fX, float fY ,float fZ); 
	void SkySphere_SetPolyCount(int iNumRings);
	void SkySphere_SetDepthWrite(bool bEnableDepthWrite);
	bool SkySphere_IsEnabled();
	void SkySphere_GetColor(float* ret_fRed, float* ret_fGreen, float* ret_fBlue, float* ret_fAlpha);
	int SkySphere_GetTexture();
	void SkySphere_GetScale(float* ret_fX, float* ret_fY, float* ret_fZ);
	cTV_3DVECTOR SkyBox_GetRotation();
	cTV_3DVECTOR SkySphere_GetRotation();
	bool SkySphere_IsHemiSphere();
	int SkySphere_GetPolyCount();


	void Sun_Enable(bool bEnable);
	void Sun_SetColor(float fRed, float fGreen, float fBlue, float fAlpha);
	void Sun_SetPosition(float fPositionX, float fPositionY, float fPositionZ);
	void Sun_SetTexture(int iTexture);
	void Sun_SetBillboardSize(float fSize);
	void Sun_SetBlendingMode(cCONST_TV_BLENDINGMODE eBlendMode);

	void SkyBox_Render();
	void SkySphere_Render();

	void Clouds_Create(int iNumCloudLayers, float fCoverageWidth, float fCoverageHeight);
	void Clouds_SetLayerParameters(int iCloudLayer, float fAltitude, int iTexture, float fTextureScaleU  = 1.0f , float fTextureScaleV = 1.0f, float fTextureOffsetU = 0.0f, float fTextureOffsetV = 0.0f);
	void Clouds_SetLayerBlendMode(int iCloudLayer, cCONST_TV_BLENDINGMODE eMode = cTV_BLEND_ALPHA);
	void Clouds_SetLayerAnimation(int iCloudLayer, bool bEnable, float fAnimationSpeedU = 0.0f, float fAnimationSpeedV = 0.0f ); 
	void Clouds_Enable(bool bEnable, int iLayer = -1);
	void Clouds_SetLayerColor(int iCloudLayer, float fRed, float fGreen, float fBlue, float fAlpha);
	void Clouds_GetLayerColor(int iCloudLayer, float* fRed, float* fGreen, float* fBlue, float* fAlpha);
	void Clouds_Render(); 
	void Clouds_SetAlphaTest(int iCloudLayer, bool bAlphaTest = true, int iAlphaRef = 8, bool bWriteDepthBuffer = true);

	void Rain_Render();
	CTVParticleSystem* Rain_GetParticleSystem();

	void SkyBox_SetVerticalOffset(float fOffset = 0.0f);
	void SkySphere_SetVerticalOffset(float fOffset = 0.0f);
	float SkyBox_GetVerticalOffset();
	float SkySphere_GetVerticalOffset();

};
