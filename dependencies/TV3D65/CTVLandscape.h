#ifndef LANDSCAPE_H
#define LANDSCAPE_H

#pragma once
#include "tv_types.h"
#include "CTVShader.h"

class CTVCollisionResult;

class EXPORTCLASS CTVLandscape
{
	
public:
	int iLandscapeIndex;

	void SetIndex(int iIndex);
	int GetIndex();

	CTVLandscape(void);
	~CTVLandscape(void);

	bool GenerateTerrain(const char* sDataSource, cCONST_TV_LANDSCAPE_PRECISION ePrecision, int iWidthIn256SizedChunk,int iHeightIn256SizedChunk, float fPosX, float fPosY, float fPosZ, bool bSmoothTerrain = true);
	void SetAffineLevel(cCONST_TV_LANDSCAPE_AFFINE eAffileLevel);
	float GetHeight(float fX, float fZ);
	cTV_3DVECTOR GetNormal(float fX, float fZ);

	float GetSlope(float fX1, float fZ1, float fX2, float fZ2);
	float GetSlopeAngle(float fX1, float fZ1, float fX2, float fZ2);
	
	void Render();

	void SetLightingMode(cCONST_TV_LIGHTINGMODE eLightingMode = cTV_LIGHTING_MANAGED, int iNumMaxDirLights = -1, int iNumMaxPointLights = -1 );

	void SetPosition(float x, float y, float z);
	void SetRotation(float fAngleX, float fAngleY, float fAngleZ);
	void SetScale(float x, float y, float z);
	void SetMatrix(cTV_3DMATRIX* mMatrix);

	void SetTexture(int iTexture, int iChunkID = -1);
	void SetMaterial(int iMaterial, int iChunkID = -1);
		
	void ExpandTexture(int iTexture, int iStartChunkX = 0, int iStartChunkY = 0, int Width = -1, int Height = -1 , bool bDetailsAlso = false);
	
	void SetHeight(float fX, float fZ, float fNewHeight, bool bUpdateQuadtree = true, bool bDontUpdateNow = false, bool bRelative = false);
	void CreateEmptyTerrain(cCONST_TV_LANDSCAPE_PRECISION ePrecision, int iWidthIn256SizedChunk,int iHeightIn256SizedChunk, float fPosX, float fPosY, float fPosZ);
	int GetMaterial(int iChunkIndex = -1);
	int GetTexture(int iChunkIndex = -1);

	int SaveTerrainData(const char* sDataDestination, cCONST_TV_LANDSAVE eSaveMode);
	int LoadTerrainData(const char* sDataSource);

	void SetTerrainChunkEnable(int iChunkX, int iChunkZ, bool bEnable);
	bool IsChunkVisible(int iChunkIndex);

	void SetDetailTextureScale(float fTuScale, float fTvScale, int iChunkIndex = -1);
	void SetPagingSystem(bool bEnable , int iVisibleChunk = 5);


	int TexGen_AddLayer(const char* sTextureDataSource, int iAltitudeStart, int iAltitudeEnd, float fBlendPower = 1.0f, float fTextureScaleX = 1.0f, float fTextureScaleY = 1.0f, float fRandomness = 0.0f, float fSlopeMin = -1.0f, float fSlopeMax = -1.0f);
	void TexGen_ClearLayers();
	void TexGen_Generate(const char* sSourceHeightmap, const char* sCompileFile, cCONST_TV_TEXGENRESOLUTION eTexGenResolution);
    int TexGen_GetCount();
	void TexGen_DeleteLayer(int iLayer);
	char* TexGen_GetLayerSource(int iLayer);


    void FlushHeightChanges(bool bUpdateQuadTree = true, bool bUpdateNormals = true);

	void SetDetailTexture(int iDetailTexture, int iGroup = -1);
	void SetTextureScale(float fTuScale, float fTvScale, int iGroup = -1); 
	void SetDetailMode(cCONST_TV_DETAILMAP_MODE eMode);

	CTVCollisionResult* MousePick(int iMouseX, int iMouseY);
	CTVCollisionResult* AdvancedCollide(cTV_3DVECTOR* vStartPoint, cTV_3DVECTOR* vEndPoint); 
 
	void DeleteAll();
	bool IsActive(); 

	void SetCustomLightmap(int iLightmapTexture, int iChunkID = -1);
	void SetHeightmapMode(cCONST_TV_LANDSCAPE_HEIGHTMAP eHeightmapFormat); 

	void SetBlendingMode(cCONST_TV_BLENDINGMODE eMode);
	void SetBlendingModeEx(cCONST_TV_BLENDEX eSourceBlend, cCONST_TV_BLENDEX eDestBlend);
	void SetAlphaTest(bool bAlphaTest, int iAlphaRef = 128, bool bWriteToBuffer = true);
 
	void SetTag(const char* sTag);
	char* GetTag();
	void SetUserData(int i32bitsPointers);
	int GetUserData();
	void SetName(const char* sName);
	char* GetName();

	cTV_3DVECTOR GetPosition();
	cTV_3DMATRIX GetMatrix();
	cTV_3DVECTOR GetScale();

	void SetCullMode(cCONST_TV_CULLING eCullMode);
	bool SetHeightArray( int iVertexOffsetX, int iVertexOffsetZ, int iWidth, int iHeight, float* pFirstHeightOfArray);
	
	// splatting support.
	void SetSplattingEnable(bool bEnable, int iChunk = -1, float fSplattingAlpha = 1.0f);
	void AddSplattingTexture(int iBaseTexture, float fPriority, float fTilingU = 1, float fTilingV = 1, float fShiftU = 0, float fShiftV = 0);
	void SetSplattingTextureProperties(int iBaseSplatTexture, cTV_3DVECTOR* vLayerNormal, float fRotationRoll = 0.0f, float fTilingU = 1.0f, float fTilingV = 1.0f, float fShiftU = 0, float fShiftV = 0.0f);
	void RemoveAllSplattingTextures();

	void ExpandSplattingTexture(int iAlphaMap, int iBaseSplatTexture, int iStartX = 0, int iStartY = 0, int iWidth = -1, int iHeight = -1);
	void SetSplattingTexture(int iAlphaMap, int iBaseSplatTexture, int iChunk);
	void ClearAllSplattingLayers(int iChunk = -1);

	void EnableLOD(bool bEnable, float fLODSwitchDistance = 512.0f, cCONST_TV_LANDSCAPE_PRECISION iMinPrecision = cTV_PRECISION_ULTRA_LOW, float fStartDistance = 0.0f, bool bDiscardAltitude = true) ;
	void OptimizeSplatting(bool bShader = false, bool bCombinedAlphaMap = false, int iChunkAlphaMapWidth = -1, int iChunkAlphaMapHeight = -1);
	void ComputeNormals(bool bFixChunkBoundaries = true);
	void SetSplattingMode(bool bUsePS2Shader, bool bUseTextureAlphaAsSpecularMap = false);
	void SetProgressiveLOD(bool bEnable);
	void SetShader(CTVShader* pShader);

	int GetChunkCount();
	cCONST_TV_LANDSCAPE_PRECISION GetPrecision();
	int GetLandWidth();
	int GetLandHeight();

	bool SetHeightArrayEx(int iX, int iY, int iWidth, int iHeight, const char* sDatasource);
	void FixSeams(CTVLandscape* lOtherLand);
	void SetClamping(bool bEnable, int iChunkID = -1);

	void ReplaceSplattingTexture(int iCurrentSplatTexture, int iNewSplatTexture);
	void ReplaceSplattingAlpha(int iCurrentAlphaTexture, int iNewAlphaTexture);

	void Enable(bool bEnable);
	void SetCollisionEnable(bool bEnable);
	//void RemoveSplattingTexture();

	void GetBoundingBox(cTV_3DVECTOR* retBoundingBoxMin, cTV_3DVECTOR* retBoundingBoxMax);
	void GetChunkBoundingBox(int chunkx, int chunky, cTV_3DVECTOR* retBoundingBoxMin, cTV_3DVECTOR* retBoundingBoxMax);

	float GetLandRealWidth();
	float GetLandRealHeight();

	int GetChunkIDFromPosition(cTV_3DVECTOR* vPosition);
	int GetChunkID(int iChunkX, int iChunkZ);

	void SetTextureEx(int iLayer, int iTexture, int iChunkID = -1);
	int GetTextureEx(int iLayer, int iChunkID = 0);
	void RemoveSplattingTexture(int iBaseSplatTexture);
	void RemoveSplattingLayer(int iBaseSplatTexture, int iChunk);
	bool IsVisible();
	cTV_3DVECTOR GetRotation();
	bool GetHeightArray( int iVertexOffsetX, int iVertexOffsetZ, int iWidth, int iHeight, float* retAllocatedHeightArray);
	void Destroy();
	cTV_3DVECTOR GetInterpolatedNormal(float fX, float fZ);

	CTVShader* GetShader();
	bool GetProgressiveLOD();
	void SetNormal(float fX, float fZ, cTV_3DVECTOR* vVector,  bool bDontUpdateNow = false);

	void SetTerrainHole(int iVertexOffsetX, int iVertexOffsetZ,cCONST_TV_LANDSCAPE_HOLETYPE eHole);
	void SetTerrainHoleArray(int iVertexOffsetX, int iVertexOffsetZ, int iWidth, int iHeight, byte* pHoleTypeArray);
	void SetTerrainHoleList(int iNumQuad,cCONST_TV_LANDSCAPE_HOLETYPE eHole, int* pVertexIndexArray);
	cCONST_TV_LANDSCAPE_HOLETYPE GetTerrainHole(int iX, int iZ);
	void EnableTerrainHoles(bool bGlobalHoleEnable );
};

#endif
