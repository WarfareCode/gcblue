#pragma once

#include "tv_types.h"
#include "CTVGameController.h"
class EXPORTCLASS CTVGameControllers
{
public:
	int iGameControllersIndex;
	CTVGameControllers(void);
	~CTVGameControllers(void);

	int Count();
	void Clear();
	void Remove(CTVGameController* pGC);
	void RemoveEx(int iGameControllerIndex);
	void GetControllers();
	CTVGameController* Item(int iGameControllerIndex);
	CTVGameController* GetController(int iGameControllerIndex);
	CTVGameController* GetControllerByName(const char* sName);
	CTVGameController* GetControllerByProductName( const char* sProductName);
	CTVGameController* GetControllerByInstanceName(const char* sInstanceName);
};
 