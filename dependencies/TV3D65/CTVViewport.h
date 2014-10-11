#ifndef VIEWPORT_H
#define VIEWPORT_H

#pragma once

#include "tv_types.h"
#include "CTVCamera.h"


class EXPORTCLASS CTVViewport
{
public:
	int iViewportIndex;
	CTVViewport(void);
	~CTVViewport(void);
	void SetBackgroundColor(int iBackGroundColor);
	void SetAutoResize(bool bAutoResize);
	HWND GetHWND();
	void SetHWND(HWND hWnd);
	CTVCamera* GetCamera();
	void SetTargetArea(int x, int y, int lWidth, int lHeight);
	void GetTargetArea(int* retX, int* retY, int* retWidth, int* retHeight);
	void Resize();
	void SetCamera(CTVCamera* cCameraObject);
	int GetViewportIndex();
	void SetViewportIndex(int index);
	int GetWidth();
	int GetHeight();
	char* GetName();

};
 
#endif
