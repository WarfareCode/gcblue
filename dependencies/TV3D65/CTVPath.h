#pragma once
#include "tv_types.h"

class CTVCamera;

class EXPORTCLASS CTVPath
{
public:
	int iPathIndex;
	CTVPath(void);
	~CTVPath(void);

	int AddPathNode(cTV_3DVECTOR* vPos);
	int GetNodeCount();
	cTV_3DVECTOR GetNode(int iNodeIndex);
	int GetNodeID(float fT);
	cTV_3DVECTOR GetSplinePoint(float fStep);			
	void MoveNode(int iNodeIndex, cTV_3DVECTOR* vNewPos);
	void ResetPath();
	void SetPathType(cCONST_TV_PATHTYPE ePathType);	
	void MovePath(cTV_3DVECTOR* vPosition);
	cCONST_TV_PATHTYPE GetPathType();
	void EnableLooping(bool bLooping);
	void Destroy();
	void Save(const char* sDataSource);
	bool Load(const char* sDataSource);
	void CameraSpline(CTVCamera* pCameraObject, float fPathNode, float fDelta);
	float GetConstantSpeedAdvance(float fCurrentNode, float fNominalSpeed, float fDelta);
};
