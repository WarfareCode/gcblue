#pragma once
#include "tv_types.h"
#include "CTVPath.h"


class EXPORTCLASS CTVAI
{
public:
	int iAIIndex;
	CTVAI(void);
	~CTVAI(void); 

	// Grid system.
	bool InitGridSystem(int iWidth, int iHeight);
	void SetGridWeightArray(int* pGridWeightsArray, int iRectLeft = -1, int iRectTop = -1, int iRectWidth = -1, int iRectHeight = -1);
	void SetGridWeight(int iWeight, int iX, int iY );
	int GetGridWeight(int iX, int iY);
	void SetGridParameters(bool bAllowDiagonal = true);
	CTVPath* FindGridPath(int iStartX, int iStartY, int iEndX, int iEndY, int* retFoundPath); 

 
	// Node system
	bool InitNodeSystem();
	int AddNode(float fX, float fY, float fZ, float fWeight = 1);
	int AddNodeEx(cTV_3DVECTOR* vNodePosition, float fWeight = 1);
	int AddNodeArray(cTV_3DVECTOR* pFirstNodeOfArray, float* fFirstWeightOfArray, int iNumNodesToAdd);
	int AddNodeArrayEx(float* fFirstCoordOfVectorArray, float* fFirstWeightOfArray, int iNumNodesToAdd);

	void RemoveNode(int iIndex);
	void SetNodeWeight(int iIndex, float fWeight);
	float GetNodeWeight(int iIndex);
	void EnableNode(int iIndex, bool bEnable);
	bool IsNodeEnabled(int iIndex);
	void CreateNodeGraph(bool bUseWorldCollision = true);
	void SetNodeSystemParameters(float fNodeSearchRadius, float fMaxAltitudeChange);
	CTVPath* FindNodePath(cTV_3DVECTOR* vStart,cTV_3DVECTOR* vEnd, int* bFoundPath );
	int GetNearestNode(cTV_3DVECTOR* vPos,bool bSearchDisabledToo = true);
	int GetNodeByPosition(cTV_3DVECTOR* vPos,bool bSearchDisabledToo = true);
	int GetNodeCount();


	// destroy..
	void Destroy();

	// save load
	bool Save(const char* sDatasource);
	bool Load(const char* sDatasource);

	void SetNodePosition(int iNode,  float fX, float fY, float fZ);
	cTV_3DVECTOR GetNodePosition(int iNode);

	void RemoveNodeLink(int iNode1, int iNode2);
	void AddNodeLink(int iNode1, int iNode2);

	void SetTag(const char* sTag);
	void SetUserData(int i32bitsUserData);
	int GetUserData();
	char* GetTag();

	bool FindGridPathEx(int iStartX, int iStartY, int iEndX, int iEndY, int* retPathXArray, int* retPathYArray, int* retPathSize);
	bool FindNodePathEx(cTV_3DVECTOR* vStart,cTV_3DVECTOR* vEnd, int* retNodeIDArray, int* retPathSize);
};
