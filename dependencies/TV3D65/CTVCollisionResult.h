#ifndef COLLISIONRESULT_H
#define COLLISIONRESULT_H


#pragma once
#include "tv_types.h"
#include "CTVActor.h"
#include "CTVMesh.h"
#include "CTVMiniMesh.h"
#include "CTVLandscape.h"


class EXPORTCLASS CTVCollisionResult
{
public:
	int iCollisionResultIndex;
	CTVCollisionResult(void);
	virtual ~CTVCollisionResult(void);  

	// get information about the collision result
	CTVMesh* GetCollisionMesh();
	CTVActor* GetCollisionActor();
	float GetCollisionDistance();
	CTVLandscape* GetCollisionLandscape();
	cCONST_TV_OBJECT_TYPE GetCollisionObjectType();
	cTV_3DVECTOR GetCollisionImpact();
	cTV_3DVECTOR GetCollisionNormal();
	cTV_2DVECTOR GetCollisionTriangleUV();
	cTV_2DVECTOR GetCollisionTextureUV();
	int GetCollisionLandscapeChunk();
	bool IsCollision(); 
	int GetCollisionBone();
	int GetCollisionGroup();
	int GetCollisionFaceId();
};

#endif
