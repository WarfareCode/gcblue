#pragma once
#include "tv_types.h"
#include "CTVCamera.h"

class EXPORTCLASS CTVCameraFactory
{
public:
	int iCameraFactoryIndex;
	CTVCameraFactory(void);
	~CTVCameraFactory(void);
	
	CTVCamera* CreateCamera(const char* sName =  NULL);
	CTVCamera* GetCamera(int iCamIndex);
	CTVCamera* GetCameraByName(const char* sName);
	CTVCamera* GetDefaultCamera();
	void RemoveCamera(CTVCamera* pCamera); 

	int GetCount();
	int GetActiveCount();
	
	
};
