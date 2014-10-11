#pragma once
#include "tv_types.h"

class EXPORTCLASS CTVLightEngine
{
public:
	int iLightEngineIndex;
	CTVLightEngine(void);
	~CTVLightEngine(void);

	int CreateDirectionalLight(cTV_3DVECTOR* direction, float red, float green, float blue,const char* name = NULL, float specularlevel = 0.3f );
	int CreateLight(cTV_LIGHT* light, const char* lightName = NULL);
	int CreatePointLight(cTV_3DVECTOR* point, float red, float green, float blue, float radius, const char* name = NULL, float specularlevel = 0.3f);
	int CreateSpotLight(cTV_3DVECTOR* position, cTV_3DVECTOR* direction, float red, float green, float blue, float radius, float phi, float theta,const char* name = NULL, float specularlevel = 0.3f);
 
	void SetLightPosition(int iLight, float x, float y, float z);
	void SetLightAttenuation(int iLight, float attenuation0, float attenuation1, float attenuation2);
	void SetLightColor(int iLight, float red, float green, float blue);
	void SetLightSpecularColor(int iLight, float red, float green, float blue);
	void SetLightAmbientColor(int iLight, float red, float green, float blue);
	void SetLightDiffuseColor(int iLight, float red, float green, float blue);
	void SetLightRange(int iLight, float radius);
	void SetLightDirection(int iLight, float x, float y, float z);

	void SetLight(int iLight, cTV_LIGHT* newLight);
	void GetLight(int iLight, cTV_LIGHT* retLightInfo);

	void SetLightProperties(int iLight, bool bManagedLight, bool bCastShadows, bool bUseForLightmapping);
   // new
	void SetBumpLightProperties(int iLight, bool bSpecular, bool bApproximatePointLightByDirLight);
   // end new
	
	void EnableLight(int iLight, bool bEnable);
	bool IsLightEnabled(int iLight);

	int GetLightFromName(const char* lightName); 


	int DeleteAllLights();
	int DeleteLight(int iLight);

	void SetSpecularLighting(bool bEnable = false); 
	void SetLightCubeMap(int iLightID, int iCubeTextureMap);

	void SetGlobalAmbient(float fRed, float fGreen, float fBlue); 
	int GetCount(); 
	int GetActiveCount();

	char* GetLightName(int iLight);

	void SetLightSpotAngles(int iLight, float fPhi, float fTheta);
	void SetLightType(int iLight, cCONST_TV_LIGHTTYPE eType);
	bool IsLightActive(int iLightID);
	void SetLightSpotFalloff(int iLight, float fFalloff);


	void GetLightProperties(int iLight,  bool* retbManagedLight, bool* retbCastShadows, bool* retbUseForLightmapping);
	void GetBumpLightProperties(int iLight, bool* retbSpecular, bool* retbApproximatePointLightByDirLight);
	void SetProjectiveShadowsProperties(int iLight, cCONST_TV_LIGHTSHADOW eShadow, int iMapSize = 512);
};
