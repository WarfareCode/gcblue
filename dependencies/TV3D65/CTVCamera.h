

#ifndef CAMERA_H
#define CAMERA_H

#pragma once

#include "tv_types.h"
#include "CTVMesh.h"
#include "CTVPath.h"
#include "CTVActor.h"

class EXPORTCLASS CTVCamera
{
public:
	int iCameraIndex;

	CTVCamera(void);
	~CTVCamera(void);
 
	void SetPath(CTVPath* pPath, bool bOrientCamera = true);
	void SetPathSpeed(float fSpeed, float fDelta, bool bConstantSpeed = false);

	int GetCameraIndex();
	void SetCameraIndex(int index);
	void SetPosition(float fPosX, float fPosY, float fPosZ);
	void SetLookAt(float fLookAtX, float fLookAtY, float fLookatZ);
	cTV_3DVECTOR GetPosition();
	cTV_3DVECTOR GetLookAt();
	void SetRotation(float fRotationAngleX, float fRotationAngleY, float fRotationAngleZ);
	void SetViewFrustum(float fDegreesFOV, float fFarPlane, float fNearPlane = 1.0f );
	void SetViewIsometric(float fZoom, float fFarPlane, float fNearPlane = 1.0f);

	void LookAtMesh(CTVMesh* mesh);
	void SimpleFollowing(CTVMesh* mesh, cTV_3DVECTOR* vLocalPosition);

	void RotateZ(float fAngleZ, bool bRelative = true);
	void RotateY(float fAngleY, bool bRelative = true);
	void RotateX(float fAngleX, bool bRelative = true);
	void SetCamera(float fX, float fY, float fZ, float fLookAtX, float fLookAtY, float fLookAtZ);
	void MoveRelative(float fFrontBack, float fUpDown, float fRightLeft, bool bMoveLookAt = true);

	cTV_3DMATRIX GetMatrix();
	void SetMatrix(cTV_3DMATRIX* matrix);
	void SetRotationMatrix(cTV_3DMATRIX* rotmatrix);
	cTV_3DMATRIX GetRotationMatrix();
	cTV_3DVECTOR GetRotation();

	// new 
	bool IsPointVisible(cTV_3DVECTOR* vPoint);
	bool IsBoxVisible(cTV_3DVECTOR* vBoxMin, cTV_3DVECTOR* vBoxMax);
	bool IsSphereVisible(cTV_3DVECTOR* vSphereCenter, float fSphereRadius);

	cTV_3DVECTOR GetDirection();
	cTV_3DVECTOR GetFrontPosition(float fDistanceInFrontOfCam);

	void SetCustomProjection(cTV_3DMATRIX* mCustomMatrix);
	void ChaseCameraMatrix(cTV_3DMATRIX* sMatrix, cTV_3DVECTOR* vRelativeEndPosition, cTV_3DVECTOR* vLookAtInMesh, float fCameraSpeed, bool bProgressiveSpeed = true, float fMaxSpeed = -1.0f  , float fMinSpeed =-1.0f, bool bUseTimeElapsed = true, bool bLockUp = true);
	void ChaseCamera(CTVMesh* pMesh ,cTV_3DVECTOR* vRelativeEndPosition, cTV_3DVECTOR* vLookAtInMesh, float fCameraSpeed, bool bProgressiveSpeed = true, float fMaxSpeed =-1.0f , float fMinSpeed = -1.0f,  bool bUseTimeElapsed = true , bool bLockUp = true);
	void ChaseCameraActor(CTVActor* pActor ,cTV_3DVECTOR* vRelativeEndPosition, cTV_3DVECTOR* vLookAtInMesh, float fCameraSpeed, bool bProgressiveSpeed = true, float fMaxSpeed = -1.0f , float fMinSpeed =-1.0f, bool bUseTimeElapsed = true, bool bLockUp = true);
	
	void RotateAxis(cTV_3DVECTOR* vAxis, float fAngle, bool bRelative  = true);
	cTV_3DMATRIX GetProjectionMatrix();
	cTV_3DMATRIX GetViewMatrix();

	cTV_3DQUATERNION GetQuaternion();
	void SetQuaternion(cTV_3DQUATERNION* qQuat);

	void AttachTo(cCONST_TV_NODETYPE eObjectType, int iObjectIndex, int iSubIndex, bool bKeepMatrix = true);
	void SetParent(cCONST_TV_NODETYPE eObjectType, int iObjectIndex, int iSubIndex);

	void SimpleFollowingActor(CTVActor* mMesh, cTV_3DVECTOR* vLocalPosition);
	void SimpleFollowingMatrix(cTV_3DMATRIX* mMatrix, cTV_3DVECTOR* vLocalPosition);
	cTV_3DVECTOR GetWorldPosition(cTV_3DVECTOR* pLocalPosition);
	void ResetPath(float fNodeKey = 0.0f);
	void SetProjectionClipPlane(bool bEnable, cTV_PLANE* pClipPlane);
	void GetBasisVectors(cTV_3DVECTOR* retFront, cTV_3DVECTOR* retUp, cTV_3DVECTOR* retRight);

	char* GetName();
	void SetName(const char* sName);
	void RotateAroundMesh(CTVMesh* pMesh, bool bAddRotation, float fAngle , float fDistance = 0.0f,  float fCameraRelativeAltitude = 0.0f);
	void SetCustomAspectRatio(float fCustomAspectRatio);

	void OccQuery_Init(int iNumMaxQueries);
	int OccQuery_Begin(int iQueryID = -1);
	void OccQuery_End();
	int OccQuery_GetData(int iQueryID = -1, bool bWaitResult = true);
	void OccQuery_DrawBox(cTV_3DVECTOR* vBoxMin, cTV_3DVECTOR* vBoxMax, bool bDoubleSided = false);
	void OccQuery_DrawBoxEx(cTV_3DVECTOR* vBoxMin, cTV_3DVECTOR* vBoxMax, cTV_3DMATRIX* mMatrix, bool bDoubleSided = false);
	void OccQuery_DrawQuad(cTV_3DVECTOR* vVector1, cTV_3DVECTOR* vVector2, cTV_3DVECTOR* vVector3, cTV_3DVECTOR* vVector4, bool bDoubleSided = false);
	void Destroy();
	void GetViewFrustum(float* fFOVInDegrees, float* fFarPlane, float* fNearplane = NULL);
	void GetFrustumPlanes(cTV_PLANE* retPlaneArray);
	float GetPathCurrentNode();

	void SetTag(const char* sTag);
	void SetUserData(int i32bitsUserData);
	int GetUserData();
	char* GetTag();


	int OccQuery_GetMaxQueries();

	void GetFrustumPoints(cTV_3DVECTOR* retVerticesArray);

};
#endif
