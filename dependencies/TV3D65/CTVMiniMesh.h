#ifndef MINIMESH_H
#define MINIMESH_H

#pragma once
#include "CTVMesh.h"
#include "CTVShader.h"

typedef unsigned char byte;

class EXPORTCLASS CTVMiniMesh
{

public:
	CTVMiniMesh(void);
	~CTVMiniMesh(void);

	int iMiniMeshIndex;

	int CreateBillboard(float iWidth, float iHeight, bool bCenterHeight = false);
	int CreateFromMesh(CTVMesh* pMesh, bool bPrecomputeScale = true);
	
	void Render();
	void Destroy();

	int SetPositionArray(int iNumPositionElements, cTV_3DVECTOR* pPositionArray);
	int SetRotationArray(int iNumRotationElements, cTV_3DVECTOR* pRotationArray);
	int SetScaleArray(int iNumScaleElements, cTV_3DVECTOR* pScaleArray);
	int SetMatrixArray(int iNumMatrixElements, cTV_3DMATRIX* pMatrixArray);

	void SetFadeOptions(bool bEnableFading, float fFarDistance = 1024, float fStartFadingDistance = 768, float fFadeMaxAlpha = 1.0f);

	void SetTexture(int iTexture);
	void SetMaterial(int iMaterial);
	int GetTexture();
	int GetMaterial();

	void SetPosition(float x, float y, float z, int iIndex = 0);
	cTV_3DVECTOR GetPosition(int iIndex = 0);

	void SetScale(float x, float y, float z, int iIndex = -1);
	cTV_3DVECTOR GetScale(int iIndex = 0);

	void SetRotation(float x, float y, float z, int iIndex = -1);
	cTV_3DVECTOR GetRotation(int iIndex = 0);

	void SetMatrix(cTV_3DMATRIX* mMat, int iIndex = 0);
	cTV_3DMATRIX GetMatrix(int iIndex = 0);

	void SetMaxMeshCount(int iCount); 
	int GetMaxMeshCount(bool bOnlyEnabled);


	//
	void SetAlphaTest(bool bEnableAlphaTest, int iRefValue = 128, bool bWriteToZBuffer = true);
	void SetAlphaToCoverage(bool bEnable);
	void SetBlendingMode(cCONST_TV_BLENDINGMODE eBlendingMode);
	void SetRotationMode(cCONST_TV_BILLBOARDTYPE eRotationMode);
	void SetCullMode(cCONST_TV_CULLING eCulling);

	void Enable(bool bEnable);
	void EnableMiniMesh(int iIndex, bool bEnable);
	int SetEnableArray(int iNumEnableArray, byte* pEnableArray);

	void SetColor(int cColor, int iIndex = -1);
	int GetColor(int iIndex);
	int SetColorArray(int iNumColorArray, int* pColorArray);

	void SetColorMode(bool bUseColor);
	void SetGlobalPosition(float fX, float fY, float fZ);
	void SetAlphaSort(bool bEnable);
	void SetClamping(bool bEnable);


	void SetShader(CTVShader* pCustomShader);
	CTVShader* GetShader();
	void SetTextureEx(int iLayer, int iTextureID);

	int GetFirstDisabledMinimesh();
	bool IsMiniMeshEnabled(int iMiniMeshItem);
	void EnableFrustumCulling(bool bGlobalFrustumCulling, bool bPerItemFrustumCulling = true, bool bAutoComputeBoundings = true);
	CTVMiniMesh* Duplicate(const char* sDuplicateName = NULL);
	void ComputeBoundings();
	void GetFadeOptions(int* retEnableFading = NULL, float* retFarDistance = NULL, float* retStartFadingDistance = NULL, float* retMaxAlpha = NULL);
	void GetBoundingSphere(cTV_3DVECTOR* retBoundingSphereCenter, float* retSphereRadius);
	void GetBoundingBox(cTV_3DVECTOR* retBoundingBoxMin, cTV_3DVECTOR* retBoundingBoxMax);
	cTV_3DVECTOR GetGlobalPosition();

	void GetAlphaTest(bool* retbEnableAlphaTest, int* retRefValue, bool* retbWriteToZBuffer);
	void GetAlphaBlendingEx(bool* retbEnable, cCONST_TV_BLENDEX* reteSrcBlend, cCONST_TV_BLENDEX* reteDestBlend);

	char* GetTag();
	int GetUserData();
	void SetUserData(int i32bitsUserData);
	void SetTag(const char* sTag);

	int GetItemTriangleCount();
	int GetItemVertexCount();

	void SetName(const char* sName);
	char* GetName();

	void GetItemBoundingSphere(int iItem, cTV_3DVECTOR* retSphereCenter, float* retRadius, bool bWorldSpace);	
	void GetItemBoundingBox(int iItem, cTV_3DVECTOR* retBoundingBoxMin, cTV_3DVECTOR* retBoundingBoxMax, bool bWorldSpace);


};

#endif
