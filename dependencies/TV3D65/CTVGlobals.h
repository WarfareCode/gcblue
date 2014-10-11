#ifndef GLOBAL_H
#define GLOBAL_H

#pragma once
#include "tv_types.h"
#include "CTVShader.h"
#include "CTVActor.h"
#include "CTVMesh.h"
#include "CTVMiniMesh.h"
#include "CTVLandscape.h"
#include "CTVCamera.h"
#include "CTVViewport.h"
#include "CTVParticleSystem.h"
#include "CTVNode.h"
#include "CTVRenderSurface.h"

class EXPORTCLASS CTVGlobals
{
public:
	int iGlobalsIndex;
	CTVGlobals(void);
	~CTVGlobals(void);
	int Colorkey(cCONST_TV_COLORKEY colorkey);
	int GetMat(const char* cMaterialName);
	int GetTex(const char* sTextureName);
	int GetLight( const char* sLightName);
	CTVShader* GetShader(const char* sShaderName); 
	HWND CreateWindowHandle();
	void DestroyWindowHandle(HWND handle);
	

	CTVMesh* GetMesh(const char* sMeshName);
	CTVMesh* GetMeshFromID(int iMeshID);
	CTVActor* GetActor(const char* sActorName);
	CTVActor* GetActorFromID(int iActorID); 

	cTV_COLOR DecodeRGBA(int iRGBA);

	char* GetDataSourceFromMemory(int i32BitsDataPointer, int iDataSize);
	char* GetDataSourceFromFilePart(const char* sFilename, int iByteOffset, int iDataSize);

	CTVActor* GetActorFromEntityID(int iEntityID);
	CTVMesh* GetMeshFromEntityID(int iEntityID);

	CTVLandscape* GetLandscape(const char* sLandName);
	CTVLandscape* GetLandscapeFromID(int iLandIndex);

	CTVMiniMesh* GetMiniMesh(const char* sMiniMeshName);
	CTVMiniMesh* GetMiniMeshFromID(int iMiniMeshIndex);

	void SetUserClipPlane(bool bEnable, int iPlaneID, float fNormalX, float fNormalY, float fNormalZ, float fDist);

	CTVViewport* GetViewport(const char* sViewportName);
	CTVViewport* GetViewportFromID(int iViewportID);

	CTVCamera* GetCameraFromID(int iCameraID);
	CTVCamera* GetCamera(const char* sCameraName);

	CTVParticleSystem* GetParticleSystem(const char* sParticleSystemName);
	CTVParticleSystem* GetParticleSystemFromID(int iParticleSystemID);

	CTVNode* GetNodeFromID(int iNodeID);
	CTVNode* GetNode(const char* sNodeName);

	CTVShader* GetShaderFromID(int iShaderID);

	CTVRenderSurface* CTVGlobals::GetRenderSurface(const char* sName);
	CTVRenderSurface* CTVGlobals::GetRenderSurfaceFromID(int iRenderSurfaceID);

};

#endif
