#ifndef MESH_H
#define MESH_H

#pragma once
#include "tv_types.h"
#include "CTVShader.h"
#include "CTVPath.h"
#include "math.h"

class EXPORTCLASS CTVMesh
{
private:

public:	
	CTVMesh(void);
	virtual ~CTVMesh(void); 
	int iMeshIndex; 
	
	void SetPath(CTVPath* pPath,bool bOrientMesh = true);
	void SetPathSpeed(float fSpeed, bool bConstantSpeed = false);

	int CreateSphere(float fRadius, int iNumSlices = 12, int iNumStacks = 12);
	// NEW ONES !!
	int CreateCylinder(float fRadius, float fHeight, int iPrecision, bool bCapped = true);
	int CreateBox(float fWidth, float fHeight, float fDepth, bool bSixGroups = false);
	int GetEntityIndex();
	// END NEW ONES !!

	void SetMeshName(const char* sMeshName);
	char* GetMeshName(void);

	// Load files.
	bool LoadXFile(const char* sFilename, bool bLoadTextures = true, bool bLoadMaterials = true);
	bool LoadTVM(const char* sFilename , bool bLoadTextures = true, bool bLoadMaterials = true);
	bool SaveTVM(const char* sFilename);

	// rendering process
	void Render();

	bool SetShader(CTVShader* sShader);  // the engine will try to adapt itsself the shader to the mesh.
	bool SetShaderEx(CTVShader* sShader, bool bMatchMeshFormat = true, int iGroupIndex = -1);
 
	void SetTexture(int iTexture, int iGroup = -1);
	void SetTextureEx(int iLayer, int iTexture, int iGroup = -1);	

	int GetTexture(int iGroup = -1);
	int GetTextureEx(int iLayer, int iGroup = -1);

	void SetTextureLayer(int iLayer, int iTextureMode, int iGroup = -1);

 
	// entity thingy.
	void SetPosition( float x, float y, float z);
	void SetRotation( float angleX, float angleY, float angleZ);
	void SetScale( float scaleX, float scaleY, float scaleZ);
	void SetRotationMatrix( cTV_3DMATRIX* mMatrix);
	void SetMatrix( cTV_3DMATRIX* mMatrix);
	void RotateX( float angleX, bool bRelative = true);
	void RotateY( float angleY, bool bRelative = true);
	void RotateZ( float angleZ, bool bRelative = true);

	cTV_3DVECTOR GetPosition();
	cTV_3DMATRIX GetMatrix();
	cTV_3DMATRIX GetRotationMatrix();
	cTV_3DVECTOR GetRotation();
	cTV_3DVECTOR GetScale();

	bool SetMeshFormatEx(cTV_VERTEXELEMENT* eFirstOfElementsArray, int iNumElements );
	bool SetMeshFormat(int eCombinedFormat);

	 
	bool Collision(cTV_3DVECTOR* pStart, cTV_3DVECTOR* pEnd, cCONST_TV_TESTTYPE eTestType = cTV_TESTTYPE_ACCURATETESTING);
	bool AdvancedCollision(cTV_3DVECTOR* pStart, cTV_3DVECTOR* pEnd, cTV_COLLISIONRESULT* retResult, cCONST_TV_TESTTYPE eTestType = cTV_TESTTYPE_ACCURATETESTING);
	void SetCollisionEnable(bool bEnableCollision, int iMeshGroup = -1, cCONST_TV_TESTTYPE eDefaultTestType = cTV_TESTTYPE_DEFAULT);

	// add/set vertex
	int AddVertexEx(void* pVertex, int iSize);
	int AddVertex(float x, float y, float z, float nx, float ny, float nz, float tu1, float tv1, float tu2 = 0.0f, float tv2 = 0.0f, int color = -1);
  
	int SetVertex(int iVertexId, float x, float y, float z, float nx, float ny, float nz, float tu1, float tv1, float tu2, float tv2, int color);
	int GetVertex(int iVertexId, float* fX, float* fY, float* fZ, float* fNx, float* fNy, float* fNz, float* fTu1, float* fTv1, float* fTu2, float* fTv2, int* iColor);

	int SetVertexEx(int iVertexId, void* data, int size);
	int GetVertexEx(int iVertexId, void* retData, int size);

	void SetMaterial(int iMaterial, int iGroup = -1);
	int GetMaterial(int Group); 
	
	void SetColor(int cColor, bool bForLighting = false);


	void InvertNormals();
	void GenerateLightMap(int iWidth, int iHeight, float scale,  bool bCastShadow = true);
	void Destroy();
	void SetLightingMode(cCONST_TV_LIGHTINGMODE eLightingMode, int iMaxDirLight = -1, int iMaxPointLight = -1 );

	// culling mode
	void SetCullMode(cCONST_TV_CULLING eCullingMode);
	cCONST_TV_CULLING GetCullMode();

	// optimizations.
	int CompactMesh(bool bCollapseToOneGroup = false, int iGroupSettingsToUse = 0);

	void SetAlphaTest(bool bEnable = true, int cReferenceValue = 128, bool bDepthBufferWrite = true, int iGroup = -1);
	void SetAlphaToCoverage(bool bEnable, int iGroup = -1);
	void SetBlendingMode(cCONST_TV_BLENDINGMODE eMode, int iGroup = -1);
	void SetBlendingModeEx(cCONST_TV_BLENDEX eSourceBlend, cCONST_TV_BLENDEX eDestBlend, int iGroup = -1);


	CTVMesh* Duplicate(const char* newMeshName = NULL, bool bShareMemory = true);

	void ComputeOctree(int iMaxFacePerLeaf = 32);
	void GetBoundingSphere(cTV_3DVECTOR* retCenter, float* retRadius, bool pLocalMode = true);
	void GetBoundingBox(cTV_3DVECTOR* retBoundingBoxMin, cTV_3DVECTOR* retBoundingBoxMax, bool pLocalMode = false);

	void SetTextureModEnable(bool bEnable, int iGroup = -1, int iLayer = 0);
	void SetTextureModMatrix(cTV_3DMATRIX* mMat, cCONST_TV_TEXTUREMOD eMode = cTV_TEXTUREMOD_USECURRENTCOORDS , int iGroup = -1, int iLayer = 0);
	void SetTextureModTranslationScale(float fTranslationU = 0,  float fTranslationV = 0, float fScaleU = 1, float fScaleV = 1, int iGroup = -1, int iLayer = 0);
	void SetTextureModRotation(float fAngleZ, int iGroup = -1, int iLayer = 0);

	int GetGroupsNumber();
	char* GetTag(); // return internal address, don't delete it !
	void SetTag(const char* sTagString);

	// set geometry
	void SetGeometry(cTV_SVERTEX* vVerticesArray, int iNumVertices, int* pIndicesArray, int iNumFaces, int iNumGroups = 0,  int* iFaceGroupIDArray = NULL, bool bOptimizeMesh = true);
	void SetGeometryEx(float* fFirstElementOfVertexArray, int vStride, int iNumVertices, int* pIndicesArray, int iNumFaces, int iNumGroups = 0,  int* iFaceGroupIDArray = NULL,bool bOptimizeMesh = true);


	// support function for billboards/walls/floor.
	void SetPrimitiveType(cCONST_TV_PRIMITIVETYPE ePrimitiveType);


	// all the prototypes things. (AddWall/AddFloor)
	int AddWall(int iTexture, float fX1, float fZ1, float fX2, float fZ2, float fHeight, float fAltitude = 0, float fTileW = 1, float fTileH = 1, bool bNewGroup = true);
	int AddWall2(int iTexture, float fX1, float fZ1, float fX2, float fZ2, float fHeight1, float fHeight2, float fAltitude1 = 0, float fAltitude2 = 0, float fTileW = 1, float fTileH = 1, bool bNewGroup = true);
    int AddTriangle(int iTexture, float fX1, float fY1, float fZ1, float fX2, float fY2, float fZ2, float fX3, float fY3, float fZ3, float fTileW = 1, float fTileH = 1, bool bNewGroup = false );
	int AddFloor(int iTexture, float fX1, float fZ1, float fX2, float fZ2, float fAltitude = 0, float fTileW = 1, float fTileH = 1, bool fNewGroup = true);
	int AddFace(int iTexture = 0);
	int AddFaceFromPoint(int iTexture, float fX1, float fY1, float fZ1, float fX2, float fY2, float fZ2, float fX3, float fY3, float fZ3, float fX4, float fY4, float fZ4, float fTileW = 1, float fTileH = 1, bool bNewGroup = true);
	int AddWall3D(int iTexture, float fX1 , float fZ1 , float fX2 , float fZ2 , float fHeight , float fDepth = 10.0f, bool bDisableTop = false, bool bDisableBottom  = false, float fAltitude = 0.0f, float fTilew = 1.0f, float fFileH= 1.0f);


    // some mesh states
	int GetTriangleCount();
	int GetVertexCount();
	int GetGroupCount();

	// billboards
	void SetBillboardType(cCONST_TV_BILLBOARDTYPE eBillboardType);


	void ComputeNormals();
	void ComputeNormalsEx(bool bFixSeams = true, float fAngleThreshold = 0.0f);
	void ComputeBoundings() ;
	void Enable(bool bEnable);
	bool IsEnabled();
	bool IsVisible(); 
	void SetShadowCast(bool bEnable, bool bUseAdditiveShadows);
	int GenerateNormalMap(CTVMesh* pHighPolyMesh, bool bUseTangent, int iWidth, int iHeight, bool bAntialias, bool bUseHeightLayer = false, float fScaleHint = 1.0f);

	void Update();
	void ForceMatrixUpdate();

	cTV_3DVECTOR GetWorldPosition(cTV_3DVECTOR* vLocalPoint);
	cTV_3DVECTOR GetLocalPosition(cTV_3DVECTOR* vWorldSpacePoint);

	void ResetMesh();
	bool WeldVertices(float fPositionEpsilon = 0.1f, float fNormalEpsilon = 1.0f);

	void ShowBoundingBox(bool bShow, int cColor = 0xffffff00); 
	void MoveRelative(float fForward, float fUp, float fRight);

	void SetMeshCenter(float fX, float fY, float fZ);
	void TransformByMatrix(cTV_3DMATRIX* mMatrix);

	void SetTextureClamping(bool bClampTextures);
	
	int GetVertexCountEx(int iGroup = -1);
	int GetTriangleCountEx(int iGroup = -1); 

	void SetUserData(int iUserDataOrPointer);
	int GetUserData(); 

	void SetSphereMapping(bool bEnable, int iMode = 0, int iGroup = -1, int iLayer = 0); 
	void CreateTeapot();

	void AttachTo(cCONST_TV_NODETYPE eObjectType, int iObjectIndex, int iSubIndex, bool bKeepMatrix = true, bool bRemoveScale = false);
	void SetParent(cCONST_TV_NODETYPE eObjectType, int iObjectIndex, int iSubIndex);
	void SetParentEx(cCONST_TV_NODETYPE eObjectType, int iObjectIndex, int iSubIndex, float fTranslationOffsetX = 0.0f, float fTranslationOffsetY = 0.0f, float fTranslationOffsetZ = 0.0f, float fRotationOffsetX = 0.0f, float fRotationOffsetY = 0.0f, float fRotationOffsetZ = 0.0f, bool bRemoveScale = false);
	bool GetParent(int* retNodeType, int* retObjectIndex, int* retSubIndex);

	bool ComputePRT(bool bUseSubSurface = false, int iOrder = 6, int iNumRays = 1024, int iNumBouces = 1); 

	void SetGroupName(int iGroup, const char* sName);
	char* GetGroupName(int iGroup);

	int CreateCone(float fRadius, float fHeight, int iPrecision, bool bCapped);
	void LookAtPoint(cTV_3DVECTOR* vPoint, bool bOnlyRotationY = false);
	void GetBasisVectors(cTV_3DVECTOR* retDirection, cTV_3DVECTOR* retUp, cTV_3DVECTOR* retSide); 
	void SetQuaternion(cTV_3DQUATERNION* qQuat);
	cTV_3DQUATERNION GetQuaternion();

	void SetGroupEnable(int iGroup, bool bEnable);
	bool GetGroupEnable(int iGroup);

	void SetPointParameters(bool bPointSprite, bool bPointScale, float fPointSize = 0.1f);
	int AddFloorGrid(int iTexture, float fX1, float fZ1, float fX2, float fZ2, int iNumCellsX, int iNumCellsZ, float fAltitude = 0.0f, float fTileU = 1.0f, float fTileV = 1.0f, bool bNewGroup = true);
	int AddWallGrid(int iTexture, float fX1, float fZ1, float fX2, float fZ2, int iNumCellsX, int iNumCellsZ, float fHeight, float fAltitude = 0.0f, float fTileU = 1.0f, float fTileV = 1.0f, bool bNewGroup = true);
	void Create3DText(const char* sText, const char* sFontName, float fFontSize, float fExtrude = 1.0f, float fDeviation = 0.0f, bool bFontBold = false, bool bFontUnderline = false);
	void SetOverlay(bool bEnable);

	void GenerateUV(int iTextureWidth, int iTextureHeight, int iMaxCharts = 0, int iLayerCoord = 1);
	bool ComputePerPixelPRT(int iTextureWidth, int iTextureHeight, bool bUseSubSurface = false, int iOrder = 6, int iNumRays = 1024, int iNumBounces = 1); 

	void EnableFrustumCulling(bool bEnable, bool bUseBoxCulling = false);
	cTV_3DMATRIX GetTextureModMatrix(int iGroup = 0, int iLayer = 0);
	void SetAttachMode(bool bRemoveParentScale = true, bool bOnlyPosition = false);
	void GetTriangleInfo(int iFaceID, int* retVertex1, int* retVertex2, int* retVertex3, int* retGroup);
	void ResetPath(float fNodeKey = 0.0f);


	bool IsGeneratingNormalMap();
	bool IsComputingPRT();
	float GetNormalMapGenerationProgress();
	float GetPRTComputationProgress();

	cCONST_TV_LIGHTINGMODE GetLightingMode();
	void CancelGeneration();
	void SetCollisionUVSet(int iTexCoordSet);
	void SetGroupRenderOrder(bool bRenderOrderEnable,int iNumGroupToRender, int* pGroupOrderArray);
	CTVShader* GetShader(int iGroup = -1);

	void GetGeometry(cTV_SVERTEX* pVerticesArray, int* retIndicesArray, int* retFaceGroupIDArray);
	void GetGeometryEx(float* retVerticesAllocatedArray, int* retStride, int* retIndicesArray,int* retFaceGroupIDArray);
	float GetPathCurrentNode();

	void GetAlphaBlendingEx(bool* retbEnable, cCONST_TV_BLENDEX* reteSrcBlend, cCONST_TV_BLENDEX* reteDestBlend, int iGroup = 0);
	void GetAlphaTest(bool* retbEnable, int* retAlphaRef, int iGroup = 0);

	int GetGroupFromName(const char* sName);
	int GetGroupFromVertex(int iVertex);
	
	void SetTangentParameters(float fMaxAngleForSharedNormals, float fMaxAngleForSharedTangents,  bool bUseFaceAdjacency = true);

	void SetCustomLights( bool bUseCustomManagedLights, int iNumLights, int* pLightArray);
}; 

#endif
