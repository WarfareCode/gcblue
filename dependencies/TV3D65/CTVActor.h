

#ifndef ACTOR_H
#define ACTOR_H

#pragma once
class CTVMesh;

#include "tv_types.h"
#include "CTVPath.h"
#include "CTVShader.h"

class EXPORTCLASS CTVActor
{
public:
	int iActorIndex;
 
	CTVActor(void);
	virtual ~CTVActor(void); // now fixed !
	
	void SetPath(CTVPath* pPath, bool bOrientActor = true);
	void SetPathSpeed(float fSpeed, bool bConstantSpeed = false);

	// generic loading
	bool Load(const char* datasource, bool bLoadTextures = true, bool bLoadMaterials = true);
	
	// specific loading
	bool LoadTVA(const char* datasource, bool bLoadTextures = true, bool bLoadMaterials = true);
	bool LoadXFile(const char* datasource, bool bLoadTextures = true, bool bLoadMaterials = true);
	bool SaveTVA(const char* datasource);

	void SetAnimationID(int iAnimationID);
	void PlayAnimation(float speed = 1.0f);
	void StopAnimation();
	void PauseAnimation();
	void BlendAnimationTo(int iNewAnimation, float fTransitionLengthSec = 1.0f);  

	void SetMaterial(int matid, int group = -1);
	int GetMaterial(int group = 0);

	// rendering updating 
	void Update();
	void Render(bool bUpdate = true);

	void SetIndex(int iIndex);
	int GetIndex() ;


	// bone manipulating.
	void SetBoneRotation(int iBone, float aRotateX, float aRotateY, float aRotateZ, bool bRelative);
	void SetBoneRotationMatrix(int iBone, cTV_3DMATRIX* mRotateMatrix, bool bRelative);
	void SetBoneMatrix(int iBone, cTV_3DMATRIX* mMatrix, bool bRelative = true, bool bModelSpace = false);
	void SetBoneTranslation(int iBone, float fTranslationX, float fTranslationY, float fTranslationZ, bool bRelative = false);
	void SetBoneScale(int iBone, float fScaleX, float fScaleY, float fScaleZ);
	void SetBoneGlobalMatrix(int iBone, cTV_3DMATRIX* mMatrix); 

	cTV_3DMATRIX GetBoneMatrix(int iBone, bool bModelSpace = false);
	cTV_3DVECTOR GetBonePosition(int iBone, bool bLocal = false);

	int GetBoneParent(int iBone); 
	int GetBoneCount();
	char* GetBoneName(int iBone);
	int GetBoneID(const char* sBoneName);


	// entity. 
	void RotateZ( float fAngleZ, bool bRelative =true);
	void RotateY( float fAngleY, bool bRelative =true) ;
	void RotateX( float fAngleX, bool bRelative = true);
	void SetMatrix( cTV_3DMATRIX* mMatrix);
	void SetRotationMatrix( cTV_3DMATRIX* mMatrix);
	void SetScale( float fScaleX, float fScaleY, float fScaleZ);
	void SetRotation( float fAngleX, float fAngleY, float fAngleZ);
	void SetPosition( float x, float y, float z); 
	
	cTV_3DMATRIX GetRotationMatrix();
	cTV_3DMATRIX GetMatrix();
	cTV_3DVECTOR GetPosition();
	cTV_3DVECTOR GetScale();
	cTV_3DVECTOR GetRotation();

	// new
	void SetActorMode(cCONST_TV_ACTORMODE eActorMode);

	void SetTexture(int iTexture, int iGroup = -1);
	void SetTextureEx(int iLayer, int iTexture, int iGroup = -1);

	void SetLightingMode(cCONST_TV_LIGHTINGMODE eLightMode, int iMaxDirLight = -1, int iMaxPointLights = -1);

	// 
	void Destroy();

	void SetShadowCast(bool bEnable, bool bUseAdditiveShadows, bool bFastShadow = false); 

	void SetCullMode(cCONST_TV_CULLING eCullMode);
    CTVActor* Duplicate(const char* sNewActorName = NULL);

	int GetGroupCount();
	void SetCollisionEnable(bool bEnableColision, int iActorGroup = -1, cCONST_TV_TESTTYPE eDefaultTestType = cTV_TESTTYPE_DEFAULT);
	
	int GetCurrentAnimation();
	char* GetAnimationName(int iAnimationID);
	int GetAnimationCount();
	float GetAnimationLength(int iAnimationID);

	char* GetName();
	void SetName(const char* sNewName);
	
	bool IsAnimationFinished();
	void SetAnimationLoop(bool bLooped); 

	void SetAnimationByName(const char* sAnimationName);
	float GetKeyFrame();
	void SetKeyFrame(float fKeyFrame);
	void GetBoundingBox(cTV_3DVECTOR* retBoxMin, cTV_3DVECTOR* retBoxMax, bool bLocal = false);
	void GetBoundingSphere(cTV_3DVECTOR* retSphereCenter, float* retRadius, bool bLocal = false);

	void SetAlphaTest(bool bEnable, int iAlphaRef = 128, bool bWriteToDepthBuffer = true);
	void Enable(bool bEnable);
	bool IsEnabled();
	bool IsVisible();

	int GetTexture(int iGroup = -1);
	int GetTextureEx(int iLayer, int iGroup = -1 );
	
	void MorphTargetCompiler_Clear();
	void MorphTargetCompiler_AddMorphTargetMesh(const char* sName, CTVMesh* pMesh, bool bReference = false);
	void MorphTargetCompiler_DeleteMorphTargetMesh(const char* sName);
	void MorphTargetCompiler_Compile();

	void MorphTarget_Enable(bool bEnable, bool bDynamic = false);
	void MorphTarget_SetWeight(int iPose, float fWeight);
	void MorphTarget_SetWeightByName(const char* sMorphTarget, float fWeight); 
	char* MorphTarget_GetName(int iPose);
	float MorphTarget_GetWeight(int iPose);
	int MorphTarget_GetCount();

	int GetTriangleCount(); 
	int GetVertexCount();

	void ComputeNormals();
	int GetAnimationIDByName(const char* sName); 
	void ShowBoundingBox(bool bShow, int cColor = -1, bool bShowHitBoxes = false);

	int AddAnimationRange(int iAnimationSource, float fStartFrame, float fEndFrame, const char* sNewAnimationName = NULL); 
	void SetAnimationRange(int iAnimationSource, float fStartFrame, float fEndFrame);
	void SetCustomAnimation(float fStartFrame, float fEndFrame);

//	void SetAnimationSpeed(int iAnimation, float fAnimationSpeed);

	void SetTag(const char* sTag);
	char* GetTag();

	void SetUserData(int i32bitsData);
	int GetUserData();

	void AttachTo(cCONST_TV_NODETYPE eObjectType, int iObjectIndex, int iSubIndex, bool bKeepMatrix = true, bool bRemoveScale = false);
	void SetParent(cCONST_TV_NODETYPE eObjectType, int iObjectIndex, int iSubIndex);
	void SetParentEx(cCONST_TV_NODETYPE eObjectType, int iObjectIndex, int iSubIndex, float fTranslationOffsetX = 0.0f, float fTranslationOffsetY = 0.0f, float fTranslationOffsetZ = 0.0f, float fRotationOffsetX = 0.0f, float fRotationOffsetY = 0.0f, float fRotationOffsetZ = 0.0f, bool bRemoveScale = false);
 	void LookAtPoint(cTV_3DVECTOR* vPoint, bool bOnlyRotationY = false);
	void GetBasisVectors(cTV_3DVECTOR* retDirection, cTV_3DVECTOR* retUp, cTV_3DVECTOR* retSide);
	void SetQuaternion(cTV_3DQUATERNION* qQuat);
	cTV_3DQUATERNION GetQuaternion();

	void SetGroupEnable(int iGroup, bool bEnable);
	bool GetGroupEnable(int iGroup);

	void ExportAnimations(const char* sDatasource, int iSpecificAnimation = -1);
	bool ImportAnimations(const char* sDatasource, bool bAppendAnimations = true, bool bMatchBoneNames = true);

	void MoveRelative(float fFront = 0.0f, float fUp = 0.0f, float fRight = 0.0f);

	void SetShader( CTVShader* sShader );
	void SetShaderEx( CTVShader* sShader, bool bMatchActorFormat, int iGroupIndex);

	void SetMaxUpdateFrequency(bool bEnableLimit, int iMaxUpdateFPS);
	void RenameAnimation(int iAnimationID, const char* sNewName);
	void InvertNormals();
	int GetEntityIndex();

	void SetBlendingModeEx(cCONST_TV_BLENDEX eSourceBlend, cCONST_TV_BLENDEX eDestBlend);
	void SetBlendingMode(cCONST_TV_BLENDINGMODE eBlending);

	void SetColor(int cColor, bool bForLighting = false);
	void SetAttachMode(bool bRemoveParentScale , bool bOnlyPosition );

	char* GetGroupName(int iGroup);
	void SetGroupName(int iGroup, char* sGroupName);
	int GetGroupByName(char* sGroup);

	void EnableMotionBlur(bool bEnable);

	void SetBlendedAnimationID(int iAnimationID, float fWeight = 1.0f, int iBlendedAnimationLayer = 0);
	void SetBlendedAnimationByName(char* sAnimationName, float fWeight = 1.0f, int iBlendedAnimationLayer = 0);
	void PlayBlendedAnimation(float fAnimationSpeed, int iBlendedAnimationLayer = 0);
	void PauseBlendedAnimation(int iBlendedAnimationLayer = 0);
	void StopBlendedAnimation(int iBlendedAnimationLayer = 0);
	void SetBlendedAnimationWeight(float fWeight, int iBlendedAnimationLayer = 0 );
	void SetBlendedAnimationLoop(bool bLooping, int iBlendedAnimationLayer = 0);

	bool GetParent(int* retNodeType, int* retObjectIndex, int* retSubIndex);
	void ResetPath(float fNodeKey = 0.0f);
	void SetOverlay(bool bOverlayEnable);
	void ForceMatrixUpdate();

	void SetClamping(bool bEnable);

	int GetAnimationID();
	int GetBlendedAnimationID(int iBlendedAnimationLayer);
	void SetBoneEnable(int iBoneId, bool bEnable);
	bool IsBoneEnabled(int iBoneId);
	
	void SetBlendedAnimationKeyFrame(float fKeyFrame, int iBlendedAnimationLayer = 0);
	float GetBlendedAnimationKeyFrame(int iBlendedAnimationLayer = 0);

	void OptimizeAnimations();
	bool AdvancedCollision(cTV_3DVECTOR* vStartRay, cTV_3DVECTOR* vEndRay, cTV_COLLISIONRESULT* pRetCollResult, cCONST_TV_TESTTYPE eCollisionType = cTV_TESTTYPE_DEFAULT);
	bool Collision(cTV_3DVECTOR* vStartRay, cTV_3DVECTOR* vEndRay, cCONST_TV_TESTTYPE eCollisionType = cTV_TESTTYPE_DEFAULT);
	void SetGroupRenderOrder(bool bRenderOrderEnable,int iNumGroupToRender, int* pGroupOrderArray);

	CTVMesh* GetDeformedMesh();
	cTV_3DVECTOR GetWorldPosition(cTV_3DVECTOR* vLocalPosition);
	CTVShader* GetShader(int iGroup = -1);
	void DeleteAnimationRange(int iAnimationIDRange);
	bool GetAnimationRangeInfo(int iAnimationID, int* iSourceAnimation, float* fStartKeyFrame, float* fEndKeyFrame);
	void SetAnimationRangeInfo(int iAnimationID, int iSourceAnimation, float fStartKeyFrame, float fEndKeyFrame);
	void BindToActor(CTVActor* pParentActor);
	void BindToActorEx(CTVActor* pParentActor, int iNumMatchingBones, int* pMatchingBonesArray);
	void ResetTime();
	float GetPathCurrentNode();

	bool IsBlendedAnimationFinished(int iBlendAnimationLayer);
	void UpdateEx(float fElapsedTime);

	void GetAlphaTest(bool* retbEnableAlphaTest, int* retRefValue, bool* retbWriteToZBuffer);
	void GetAlphaBlendingEx(bool* retbEnable, cCONST_TV_BLENDEX* reteSrcBlend, cCONST_TV_BLENDEX* reteDestBlend);

	void SetTangentParameters(float fMaxAngleForSharedNormals, float fMaxAngleForSharedTangents,  bool bUseAdjacency = true );
	void SetCustomLights( bool bUseCustomManagedLights, int iNumLights = 0, int* pLightArray = NULL);

	void WeldVertices(float fPositionEpsilon = 0.0f, float fNormalEpsilon = 0.0f, float fUVEpsilon = 0.0f);
};
#endif

