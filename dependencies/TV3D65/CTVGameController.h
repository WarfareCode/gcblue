#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H


#pragma once


#include "tv_types.h"


class EXPORTCLASS CTVGameController
{
public:
	int iGameControllerIndex;
	CTVGameController(void);
	~CTVGameController(void);

	cTV_JOYSTATE GetControllerState();
	cTV_JOYSTATE2 GetControllerStateAdvanced();
	int GetControllerType();
	int GetControllerSubType();
	int GetButtonCount();
	void Poll();

	char* GetProductName();
	char* GetInstanceName();

	bool IsConnected();
	bool Initialize();
	bool InUse();

	void Destroy();
	bool GetButtonState(int iButtonIndex); 

	int GetAxisCount();

	char* GetInstanceGUID();
	char* GetProductGUID();
};

#endif

