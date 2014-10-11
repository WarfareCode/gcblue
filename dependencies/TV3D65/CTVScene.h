
#ifndef SCENE_H
#define SCENE_H

#pragma once
#include "tv_types.h"

#include "ctvmesh.h"
#include "CTVShader.h"
#include "CTVCamera.h"
#include "CTVRenderSurface.h"
#include "CTVActor.h"
#include "CTVCollisionResult.h"
#include "CTVMiniMesh.h"
#include "CTVParticleSystem.h"
#include "CTVNode.h"
#include "CTVPath.h"
#include "CTVAI.h"
#include "CTVPackage.h"

class EXPORTCLASS CTVScene
{
public:
	int iSceneIndex;
	CTVScene(void);
	~CTVScene(void); 
	CTVMesh* CreateMeshBuilder(const char* MeshName = NULL);
	void SetCamera(float fPosX, float fPosY, float fPosZ, float fLookAtX, float fLookAtY, float fLookAtZ);
	CTVCamera* GetCamera();
	CTVShader* CreateShader(const char* sShadername = NULL);
	void SetBackgroundColor(float r, float g, float b, float a = 1.0f); 
	CTVRenderSurface* CreateRenderSurface(int iWidth, int iHeight, bool bUseDepthBuffer = true, cCONST_TV_RENDERSURFACEFORMAT iFormat = cTV_TEXTUREFORMAT_DEFAULT, char* sName = NULL);
	void DestroyMesh(CTVMesh* pMesh);
	bool Collision(cTV_3DVECTOR* pStart, cTV_3DVECTOR* pEnd, int eObjectType = 0, cCONST_TV_TESTTYPE eTestType = cTV_TESTTYPE_DEFAULT);
	bool AdvancedCollision(cTV_3DVECTOR* pStart, cTV_3DVECTOR* pEnd, cTV_COLLISIONRESULT* retFirstElementOfArray,  int eObjectType = 0, cCONST_TV_TESTTYPE eTestType = cTV_TESTTYPE_DEFAULT, int* iNumOfHits = NULL);
	CTVActor* CreateActor(const char* name = NULL);
	CTVParticleSystem* CreateParticleSystem(const char* name = NULL);
 
	void SetViewFrustum(float fFOVAngleDegrees,float fFarPlane)	 ;
	void SetMipmappingPrecision(float fMipmapPrecision);
	void SetAutoTransColor(int eColorKey, bool bAutoTextureStretch = true);
	void SetDepthBuffer(cCONST_TV_DEPTHBUFFER eDepthBuffer);
	void SetDithering(bool bEnable);
	CTVRenderSurface* CreateAlphaRenderSurface(int iWidth, int iHeight, bool bUseDepthBuffer = true,char* sName = NULL);
 //	int LoadTexture(char* sFilename, int iWidth = -1, int iHeight = -1, char* sTextureName = "");
	void DestroyAllMeshes();
	void SetTextureFilter(cCONST_TV_TEXTUREFILTER eTexFilter3D);
	void SetRenderMode(cCONST_TV_RENDERMODE eRenderMode);
	void SetShadeMode(cCONST_TV_SHADEMODE eShadeMode);

	int GetTriangleNumber();
	int GetCulledTriangleNumber();
	int GetTrianglesPerSecondCount();

	// new 01/29
	CTVMiniMesh* CreateMiniMesh(int iMaxSimultaneousMeshes = 1, const char* name = NULL);
	// end new

	// new 03/19
	CTVMesh* CreateBillboard(int iTexture, float fPosX, float fPosY, float fPosZ, float fWidth, float fHeight, const char* sBillboardMeshName = NULL, bool bRotationAtCenter = false);
    CTVCollisionResult* MousePick(int iMouseX, int iMouseY,   int eObjectTypeToTest = 0, cCONST_TV_TESTTYPE eObjectTestType = cTV_TESTTYPE_DEFAULT);
	bool MousePickEx(int iMouseX, int iMouseY, cTV_COLLISIONRESULT* retFirstElementArray, int eObjectTestType = 0 , cCONST_TV_TESTTYPE eTestType = cTV_TESTTYPE_DEFAULT , int* iNumOfHits = NULL);
	CTVRenderSurface* CreateCubeRenderSurface(int iSize,  bool bUseDepthBuffer = true, int iFormat = 0, char* sName = NULL);
 
	void RenderAllMeshes(bool bAlphaSort = false);
	void RenderAll(bool bAlphaSort, bool bUpdateAll = true); 
	void RenderMeshList(int iNumMeshs, int* pMeshIndicesListArray);

	void SetCursor(bool bEnable, int iTextureCursor, int iHotSpotX = 0, int iHotSpotY = 0, float fOptionalSizeX = 0.0f, float fOptionalSizeY = 0.0f, bool bHardwareCursor = false);
	CTVNode* CreateNode(const char* sName = NULL); 
	void FinalizeShadows();
	void SetShadowParameters(int cShadowColor, bool bMultiShadow);
	
	CTVMesh* MergeMeshes(CTVMesh* pMesh1, CTVMesh* pMesh2, bool bCompactMesh = true, const char* sNewName = NULL);
	CTVMesh* MergeMeshesList(int iNumMeshToMerge, int* pFirstMeshIndexOfListArray, bool bCompactMesh,const char* sNewName = NULL);

	void SetMaxAnisotropy(int iAnisotropyLevel);
	CTVRenderSurface* CreateRenderSurfaceEx(int iWidth, int iHeight, cCONST_TV_RENDERSURFACEFORMAT eFormat, bool bUseDepth, bool bUseMainBufferSize = false, float fMainBufferScale = 1.0f, char* sName = NULL);
 

	int SortMeshList(int iNumMeshs, int* pMeshIndicesListArray, int* retSortedIndicesListArray, bool bBackwards = false, bool bOnlyVisibleMeshs = false);
	CTVPath* CreatePath();
	CTVAI* CreateAI();
	CTVLandscape* CreateLandscape(const char* sName = NULL);

	int SortActorList(int iNumActors, int* pActorIndicesListArray, int* retSortedIndicesListArray, bool bBackwards = false, bool bOnlyVisibleActors = false);

	bool SaveTVS(int iPackageId, bool bExportOnlyEnabled = false);
	bool LoadTVS(int iPackageID);
	
	void DestroyAllActors();
	void DestroyAllMinimeshes();
	void DestroyAllParticleSystems();
	void DestroyAllLandscapes();


	void SetColorWriteEnable(bool bWriteRed, bool bWriteGreen, bool bWriteBlue, bool bWriteAlpha);
	CTVRenderSurface* CreateMultiRenderSurface(int iNumRenderTargets, int iWidth, int iHeight, bool bUseDepth, bool bUseMainBufferSize , float fMainBufferScale , cCONST_TV_RENDERSURFACEFORMAT iFormat1, cCONST_TV_RENDERSURFACEFORMAT iFormat2, cCONST_TV_RENDERSURFACEFORMAT iFormat3, cCONST_TV_RENDERSURFACEFORMAT iFormat4, char* sName = NULL);

	void RenderAllActors(bool bUpdateActors = true);
	void RenderAllParticleSystems(bool bUpdateParticles = true);

	void SetMousePickRangeLimit(float fFarplaneRatio);
	void RenderActorList(int iNumActors, int* pActorIndicesListArray);

	void RenderAllLandscapes();
	void RenderAllMiniMeshes();

};

#endif

