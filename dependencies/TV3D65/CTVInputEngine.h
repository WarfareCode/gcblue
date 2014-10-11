#pragma once
#include "tv_types.h"
#include "CTVGameControllers.h"
class EXPORTCLASS CTVInputEngine
{
public:
	int iInputEngineIndex;
	CTVInputEngine(void);
	~CTVInputEngine(void);
	bool Initialize(bool bKeyboard = true , bool bMouse = true);
	bool IsKeyPressed(cCONST_TV_KEY eKey);
	void GetMouseState(int* retRelativeX, int* retRelativeY, bool* retButton1 = NULL, bool* retButton2 = NULL, bool* retButton3 = NULL, bool* retButton4 = NULL, int* retRoll = NULL);
	void GetAbsMouseState(int* retAbsoluteX, int* retAbsoluteY, bool* retButton1= NULL, bool* retButton2= NULL, bool* retButton3= NULL, bool* retButton4= NULL, int* retRoll = NULL);
	void SetMouseSensitivity(float fSensitivity);
	void GetMousePosition(int* retX, int* retY);
	void GetKeyBuffer(cTV_KEYDATA* keyDataArray, int* iNumKeyData); 
	void SetRepetitionDelay(int iRepetitionDelayInMs, int iRepetitionPeriodInMs = 0); 
	void GetKeyPressedArray(byte* pKeyArray255Elements);
	int GetASCIIFromKey(cCONST_TV_KEY eKey);
	void ForceUpdate();
	void SetMousePosition(int iX, int iY);
	CTVGameControllers* GetControllers();
	bool IsMouseButtonPressed(int iButtonId);
	void ClearKeyBuffer();
	void EnableWindowsKey(bool bEnable = true);

};

