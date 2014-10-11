#pragma once
#include "tv_types.h"

class EXPORTCLASS CTVMaterialFactory
{
public:
	int iMaterialFactoryIndex;
	CTVMaterialFactory(void);
	~CTVMaterialFactory(void);

	// Create materials
	int CreateMaterial(const char* matname = NULL);
	int CreateLightMaterial(float red, float green, float blue, float alpha, float fAmbientLevel = 0.4f, float fSpecularLevel = 0.3f, char* name = NULL);
	int CreateMaterialQuick(float r, float g, float b, float a, const char* matname);

	void SetSpecular(int iMaterialIndex, float r, float g, float b, float a);
	void SetAmbient(int iMaterialIndex, float r, float g, float b, float a);
	void SetDiffuse(int iMaterialIndex, float r, float g, float b, float a);
	void SetEmissive(int iMaterialIndex, float r, float g, float b, float a);
	void SetPower(int iMaterialIndex, float power);

	cTV_COLOR GetSpecular(int iMaterialIndex);
	cTV_COLOR GetAmbient(int iMaterialIndex);
	cTV_COLOR GetDiffuse(int iMaterialIndex);
	cTV_COLOR GetEmissive(int iMaterialIndex);
	float GetPower(int iMaterialIndex);

	void DeleteAllMaterials();
	void DeleteMaterial(int iMaterialIndex);
	int GetMaterialByName(const char* matName); 

	int GetCount(); 
	int GetActiveCount();
	bool IsMaterialActive(int iMaterialIndex);
	char* GetMaterialName(int iMaterialIndex);

	void SetOpacity(int iMaterial, float fAlpha);
	float GetOpacity(int iMaterial); 

	// prt methods
	void EnablePRTSubSurface(int iMaterial, bool bEnablePRTSubS);
	void SetPRTSubSurfAbsorption(int iMaterial, float fRed, float fGreen, float fBlue);
	void SetPRTSubSurfReducedScattering(int iMaterial, float fRed, float fGreen, float fBlue );
	void SetPRTSubSurfRefractionIndexRatio(int iMaterial, float fRatio);

	int Duplicate(int iMaterial, char* sNewMaterialName = NULL);
	void SetMaterialName(int iMaterialIndex, const char* sMaterialName);
};
