#pragma once
#include "tv_types.h"
#include "CTVShader.h"

// only for people who must use the internal objects.
#define DIRECTINPUT_VERSION  0x0800
#include <d3dx9.h>
#include <d3d9.h> 
#include <dinput.h>


//////////////////////////////////////////////////////////////////////////
// TrueVision3D Access to Internal Objects.
//
// WARNING //
/////////////
// As every object accessible here is a COM object coming from DirectX.
// When you use one of the "Get" function, the reference count of this 
// object is NOT incremented, and doesn't follow the COM rules.
//
// Be sure to NOT RELEASE the object when you don't use it anymore 
// The engine will do it itself.
//
//////////////////////////////////////////////////////////////////////////

class EXPORTCLASS CTVInternalObjects
{
public:
	int iInternalObjectsIndex;
	CTVInternalObjects(void);
	~CTVInternalObjects(void);

	// 3d device
	LPDIRECT3DDEVICE9 GetDevice3D();
	LPDIRECT3D9 GetDirect3D();
	
	// contents 
	LPD3DXMESH GetD3DMesh(int meshId);
	LPDIRECT3DBASETEXTURE9 GetTexture(int id);
	LPDIRECT3DSURFACE9 GetBackBuffer();

	// setting
	void SetTexture(int iTextureID, LPDIRECT3DBASETEXTURE9 pBaseTexture);
 
	// input
	LPDIRECTINPUT8 GetDirectInput();
	LPDIRECTINPUTDEVICE8 GetKeyboardDevice();
	LPDIRECTINPUTDEVICE8 GetMouseDevice(); 

	// shader
	void Shader_Begin(CTVShader* pShader, int iPass = 0);
	void Shader_End(CTVShader* pShader);
 
	int RegisterTexture(LPDIRECT3DBASETEXTURE9 pTexture, const char* sTextureName);
	void UpdateD3DMesh(int iMeshIndex);

};
