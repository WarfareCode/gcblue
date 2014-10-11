#pragma once

#include "tv_types.h"
class EXPORTCLASS CTVNode
{
public:
	CTVNode(void);
	~CTVNode(void);
	
	int iNodeIndex;

	// this class will simply have the simple movement functions
	void SetPosition(float fX, float fY, float fZ);
	void SetRotation(float fRotationAngleX, float fRotationAngleY, float fRotationAngleZ);
	void SetScale(float fX, float fY, float fZ);

	cTV_3DVECTOR GetPosition();
	cTV_3DVECTOR GetRotation();

	cTV_3DMATRIX GetRotationMatrix();
	cTV_3DMATRIX GetMatrix();

	void MoveRelative(float fFrontBack, float fUpDown, float fLeftRight);
	void RotateX(float fAngleX, bool bRelative = true);
	void RotateY(float fAngleY, bool bRelative = true);
	void RotateZ(float fAngleZ, bool bRelative = true);

	void SetMatrix(cTV_3DMATRIX* mMatrix);
	void SetRotationMatrix(cTV_3DMATRIX* mRotationMatrix);

	cTV_3DVECTOR GetAbsolutePosition();
	cTV_3DMATRIX GetAbsoluteMatrix();

	void RotateAxis(cTV_3DVECTOR* vRotateAxis, float fAngle, bool bRelative = true);

	void AttachTo(cCONST_TV_NODETYPE eObjectType, int iObjectIndex, int iSubIndex, bool bKeepMatrix = true);
	void SetParent(cCONST_TV_NODETYPE eObjectType, int iObjectIndex, int iSubIndex);
	void SetParentEx(cCONST_TV_NODETYPE eObjectType, int iObjectIndex, int iSubIndex, float fTranslationOffsetX = 0.0f, float fTranslationOffsetY = 0.0f, float fTranslationOffsetZ = 0.0f, float fRotationOffsetX = 0.0f, float fRotationOffsetY = 0.0f, float fRotationOffsetZ = 0.0f);

	void LookAtPoint(cTV_3DVECTOR* vPoint, bool bOnlyRotationY);

	int GetUserData();
	void SetUserData(int i32BitsPointerOrData);
	char* GetTag();
	void SetTag(const char* sTag);

};
