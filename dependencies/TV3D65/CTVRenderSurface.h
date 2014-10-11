#pragma once
#include "tv_types.h"
#include "CTVCamera.h"

class EXPORTCLASS CTVRenderSurface
{

public:
	CTVRenderSurface(void);
	~CTVRenderSurface(void);

 
	int iRenderSurfaceIndex;

	bool StartRender(bool bClearOnlyZ = false);
	bool EndRender();

	int CreateStaticTextureFromRenderSurface(int iWidth, int iHeight, int iColorKey = 0, char* sName= NULL, bool bGenerateMipmaps = true);
	int CreateStaticCubeMapFromRenderSurface(int iColorKey = 0, const char* sName= NULL, bool bGenerateMipmaps = true);
	void SetCamera(float fX , float fY, float fZ, float fLookAtX, float fLookAtY, float fLookAtZ);
	CTVCamera* GetCamera();

	int GetTexture();

	void SetBackgroundColor(int iColor);  

	bool StartCubeRender(int iFaceNum, bool bClearOnlyZ = false);
	bool EndCubeRender(int iFaceNum);
	void SetCubeMapProperties(bool bAutomaticCameraHandling, cTV_3DVECTOR* vPosition);
	void SetCubeMapMatrix(bool bRelativeCubeMapMatrix, cTV_3DMATRIX* mMatrix);
		 
	int GetWidth();
	int GetHeight();
	
	void Destroy();

	void SaveTexture(const char* sDataPlace, cCONST_TV_IMAGEFORMAT fFormat = cTV_IMAGE_DDS);
	bool BltFromMainBuffer();
	bool BltFromRenderSurface(CTVRenderSurface* pRenderSurf);

	void SetNewCamera(CTVCamera* cCamera);
	void SetSystemMemCopy(bool bEnable, bool bRestoreWhenReset = false);
	int GetTextureEx(int iRenderTargetIndex);
	void SetDepthBufferClear( bool bEnableDepthClear );

};
