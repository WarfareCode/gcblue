#pragma once
#include "tv_types.h"
#include "CTVMesh.h"
#include "CTVRenderSurface.h"
class EXPORTCLASS CTVGraphicEffect
{
public:
	int iGraphicEffectIndex;
	CTVGraphicEffect(void);
	~CTVGraphicEffect(void);

	void ChangeGamma(float gamma);
	void AdvancedGamma(float RedGamma, float GreenGamma, float BlueGamma);
	void FadeIn(float speed = 2000);
	void FadeOut(float speed = 2000);
	void Flash(float r, float g, float b, float fSpeed = 500);
	void InstantFlash(float r, float g, float b, float fFlashFactor);
	void StopFade();
	void StopFlash();	
	bool IsFlashFinished();
	bool IsFadeFinished();

	void SetWaterReflection(CTVMesh* pMesh, CTVRenderSurface* pReflectionRS, CTVRenderSurface* pRefractionRS, int style, cTV_PLANE* pWaterPlane);
	void SetWaterReflectionColor(CTVMesh* pMesh, cTV_COLOR* pReflectionTint, cTV_COLOR* pRefractionTint, float fCustomFresnel = 0.5f);
	void SetWaterReflectionBumpAnimation(CTVMesh* pMesh, bool bDirectional, float fDirectionSpeedX, float fDirectionSpeedZ );


  
	void InitGlowEffect(CTVRenderSurface* iRenderSurface);
	void UnloadGlowEffect();

	void UpdateGlow();
	void DrawGlow(); 
 
	void DrawDepthOfField();
	void UpdateDepthOfField();
	void SetDepthOfFieldParameters(float fFocalPlane, float fFocalRange, float fBlur);
	bool InitDepthOfField(int iNumZLayers, CTVRenderSurface* iRenderSurfaceSource);
	void SetGlowParameters(cTV_COLOR* vGlowTint, float fItensity, float fOffsetScale);

	
	void InitHDR(cCONST_TV_RENDERSURFACEFORMAT eHDRFormat = cTV_TEXTUREFORMAT_HDR_FLOAT16);
	void StartRenderHDR();
	void EndRenderHDR();
	void DrawHDR();

	void InitMotionBlur(CTVRenderSurface* pSceneRenderSurface);
	void StartRenderMotionBlur();
	void EndRenderMotionBlur();
	void DrawMotionBlur();
	void SetMotionBlurParameters(float fBlurScale = 1.0f);
	void SetMotionBlurCamera(CTVCamera* cCam);

};
