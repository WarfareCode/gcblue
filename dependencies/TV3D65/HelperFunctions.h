#pragma once

//////////////////////////////////////////////////////////////////////////
// TrueVision3D Helper functions (optional but useful)
//////////////////////////////////////////////////////////////////////////
#include "tv_types.h"
#include "CTVMathLibrary.h"
#include "CTVShader.h"
#include "CTVMesh.h"

int EXPORTFUNC GetMat(const char* cMaterialName);
int EXPORTFUNC GetTex(const char* sTextureName);
int EXPORTFUNC RGBA(float r, float g, float b, float a);
int EXPORTFUNC RGBA256(int r, int g, int b,  int a); 
cTV_COLOR EXPORTFUNC TVColor(float r, float g, float b, float a);
void EXPORTFUNC DeleteTVObject(void* pObject);
void EXPORTFUNC DeleteMesh(CTVMesh* pMesh);

// create vector easily.
__inline cTV_3DVECTOR Vector3(float x, float y, float z)
{
	cTV_3DVECTOR v;
	v.x = x;
	v.y = y;
	v.z = z;
	return v;
}

__inline cTV_3DVECTOR Vector(float x, float y, float z)
{
	cTV_3DVECTOR v;
	v.x = x;
	v.y = y;
	v.z = z;
	return v;
}

__inline cTV_4DVECTOR Vector4(float x, float y, float z, float w)
{
	cTV_4DVECTOR v;
	v.x = x;
	v.y = y;
	v.z = z;
	v.w = w;
	return v;
}

__inline cTV_2DVECTOR Vector2(float x, float y)
{
	cTV_2DVECTOR v;
	v.x = x;
	v.y = y;
	return v;
}

__inline cTV_3DQUATERNION Quaternion(float x, float y, float z, float w)
{
	cTV_3DQUATERNION q;
	q.x =x;
	q.y =y;
	q.z =z;
	q.w =w;
	return q;
}

