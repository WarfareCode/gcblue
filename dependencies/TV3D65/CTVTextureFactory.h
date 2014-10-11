#pragma once
#include "tv_types.h"

class EXPORTCLASS CTVTextureFactory
{
public:
	int iTextureFactoryIndex;
	CTVTextureFactory(void);
	~CTVTextureFactory(void);
	int LoadTexture(const char* sFilename, const char* sTextureName = NULL, int iWidth = -1, int iHeight = -1, cCONST_TV_COLORKEY eColorKey = cTV_COLORKEY_NO, bool bFilterAndStretch = true);
	int LoadBumpTexture(const char* sFilename, const char* sTextureName = NULL, int iWidth = -1, int iHeight = -1, bool bTextureFilter = false, float fAmplitude = 32.0f);
	int LoadVolumeTexture(const char* sFilename,const char* sTextureName = NULL, cCONST_TV_COLORKEY eColorKey = cTV_COLORKEY_NO, bool bTextureFilter = false);
	int LoadCubeTexture(const char* sFilename, const char* sTextureName = NULL, int iCubeSize = -1, cCONST_TV_COLORKEY eColorKey = cTV_COLORKEY_NO, bool bTextureFilter = false);
	int LoadDUDVTexture(const char* sFilename,const char* sTextureName = NULL, int iWidth = -1, int iHeight = -1, float fAmplitude = 32.0f, bool bMipMapDecrease = true);
	int LoadAlphaTexture(const char* sFilename,const char* sTextureName = NULL, int iWidth = -1, int iHeight = -1);
	int SetTextureMode(cCONST_TV_TEXTUREMODE eTextureMode);
	bool SaveTexture(int iTextureID, const char* sFilename,  cCONST_TV_IMAGEFORMAT eImageFormat = cTV_IMAGE_BMP);
	void DeleteTexture(int lTexture);
	cTV_TEXTURE GetTextureInfo(int lTexture);
	int GetUsedTextureMemory();
	int GetFreeTextureMemory();
	int GetTextureCount(); 
	int GetActiveCount();

	void ConvertNormalMap(int iTexture, bool bFlipBinormalToDirectX = true, bool bInvertNormals = false, bool bFlipTangent = false);
	void DeleteAllTextures(bool bDeleteRendersurfacesToo = true);
	void SetTexturePathStorage(cCONST_TV_TEXTUREPATHSTORAGE eTexPathStorage);
 
	int AddAlphaChannel(int iSourceTexture, int iAlphaTexture, const char* sNewTextureName);
	int CreateTextureCycle(int iNumTextures, int* pFirstTextureOfArray, float fSpeed = 10.0f,const char* sTextureName = NULL); // 10 Frame Per Seconds
	void SetCycleProperties(int iCycleIndex, float fSpeed, bool bLooping = true);
	void ResetCycle(int iCycleIndex);

	bool LockTexture(int iTextureToLock, bool bReadOnly = false);
	void SetPixel(int iLockedTexture,int iX, int iY, int iColor); // color in TV ARGB format
	int GetPixel(int iLockedTexture,int iX, int iY);	// colr in TV ARGB format;
	void UnlockTexture(int iTextureToLock, bool bRebuildMipmap = false); 
	void ReleaseTextureDC(int iTextureID , bool bRegenMipmaps = false);
	int GetTextureDC(int iTextureID); 
	 
	int GetTextureRefCount(int iTextureID);
	int CreateTexture(int iWidth, int iHeight, bool bHasAlpha = true, const char* sTextureName = NULL);
	int CreateAlphaTexture(int iWidth, int iHeight, const char* sTextureName = NULL);

	void SetPixelArray(int iLockedTexture, int iX, int iY, int iWidth, int iHeight, int* pColorArray);
	void SetPixelAlphaArray(int iLockedTexture, int iX, int iY, int iWidth, int iHeight, byte* pAlphaValueArray);
	void SetPixelAlpha(int iLockedTexture, int iX, int iY, int alpha);
	void SetCycleKeyframe(int iCycleIndex, float fKeyFrame);
	float GetCycleKeyframe(int iCycleIndex);
	void DestroyTextureCycle(int iCycleIndex);


	bool TextureExists(const char* sName);
	void SetTextureSharing(bool bEnable, bool bReplaceTextureWithSameName = false);
	void ForceTextureLoading(bool bEnable);

	int CreateProceduralTexture(const char* sProceduralFunctionString, const char* sFunctionName, int iWidth, int iHeight, int iDepth, cCONST_TV_TEXTURETYPE eTextureType = cTV_TEXTURE_DIFFUSEMAP, const char* sTextureName = NULL);
	int CreateProceduralTextureFromFile(const char* sFunctionDataSource, const char* sFunctionName, int iWidth, int iHeight, int iDepth, cCONST_TV_TEXTURETYPE eTextureType = cTV_TEXTURE_DIFFUSEMAP,const char* sTextureName = NULL);

	int CreateNormalMap(int iHeightmapTexture, float fAmplitude = 32.0f);
	void GetPixelArray(int iLockedTexture, int iX, int iY, int iWidth, int iHeight, int* retAllocatedColorArray);

	void SetPixelFloat(int iLockedTexture , int iX, int iY, cTV_COLOR* cColor); 
	cTV_COLOR GetPixelFloat(int iLockedTexture , int iX, int iY);
	void SetPixelArrayFloat(int iLockedTexture, int iX, int iY, int iWidth, int iHeight, cTV_COLOR* pColorArray);
	void GetPixelArrayFloat(int iLockedTexture, int iX, int iY, int iWidth, int iHeight, cTV_COLOR* pAllocatedColorArray);
	void SetPixelArrayFloatEx(int iLockedTexture, int iX, int iY, int iWidth, int iHeight, float* pColorArray);
	void GetPixelArrayFloatEx(int iLockedTexture, int iX, int iY, int iWidth, int iHeight, float* retAllocatedColorArray);
	void DumpAllToDebug();
	void SetTextureName(int iTextureID, const char* sNewTextureName);
	int GetTextureByName (const char* TextureName );
};
