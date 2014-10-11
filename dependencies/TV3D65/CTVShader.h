#ifndef SHADER_H
#define SHADER_H

#pragma once

//////////////////////////////////////////////////////////////////////////
// TrueVision3D TVShader header
//////////////////////////////////////////////////////////////////////////

#include "tv_types.h"

class EXPORTCLASS CTVShader
{
public:
	int iShaderIndex;
	CTVShader(void); 
	~CTVShader(void);

	// creation function for the shader.
	bool CreateFromEffectFile(const char* filename);
	bool CreateFromEffectString(const char* str);

	void SetEffectParamMatrix(const char* param, cTV_3DMATRIX* mMatrix);
	void SetEffectParamVector(const char* param, cTV_4DVECTOR* vVect);
	void SetEffectParamBoolean(const char* param, bool bBoolean);
	void SetEffectParamFloat(const char* param, float fValue);
	void SetEffectParamTexture(const char* param, int iTexture);
	
	
	int GetEffectParameterCount();
		
	char* GetLastError();

	int GetIndex() { return iShaderIndex; }; 
	void SetIndex(int lNewIndex) { iShaderIndex = lNewIndex; }; 

	bool SetTechniqueByID(int iTechniqueIndex);
	int GetTechniqueCount();
	bool SetTechnique(const char* hTechnique);
	char* GetTechniqueName(int iTechniqueIndex); 
	int GetTechniqueByName(const char* Name); 
	int GetPassCount();

	void SetHalfPrecisionMode(bool bEnable); 

	bool GetEffectParamBoolean(const char* sName);
	float GetEffectParamFloat(const char* sName);
	cTV_3DMATRIX GetEffectParamMatrix(const char* sName);
	cTV_4DVECTOR GetEffectParamVector(const char* sName);
	int GetEffectParamByName(const char* sParamName);
	char* GetEffectParamNameBySemantic(const char* sSemantic);
	int GetEffectParamBySemantic(const char* sSemantic);
	cCONST_TV_SHADERPARAMETERTYPE GetEffectParamType(int iParam);
	char* GetEffectParamString(const char* sName);
	void SetPassEnable(int iPass, bool bEnable);
	int GetEffectParamTexture(const char* sName);
	void SetTimePeriod(float fTimePeriodInSeconds);
    char* GetEffectParamName(int iParamIndex);

	void SetEffectParamVector2(const char* sName, cTV_2DVECTOR* vVect);
	void SetEffectParamVector3(const char* sName, cTV_3DVECTOR* vVect);
	void SetEffectParamVector4(const char* sName, cTV_4DVECTOR* vVect);
	void SetEffectParamColor(const char* sName, cTV_COLOR* cColor);

	void Destroy();

	int GetEffectParamInteger(const char* sName);
	void SetEffectParamInteger(const char* sName, int iIntValue);

	void SetEffectParamVectorArray4(const char* sName, cTV_4DVECTOR* pVectorArray, int iNumVectors);
	void SetEffectParamMatrixArray(const char* sName, cTV_3DMATRIX* pMatrixArray, int iNumMatrix);
	void SetEffectParamFloatArray(const char* sName, float* pFloatArray, int iNumFloats);	
	void SetEffectParamVectorArray2(const char* param, cTV_2DVECTOR* pVectorArray, int iNumVectors);
	void SetEffectParamVectorArray3(const char* param, cTV_3DVECTOR* pVectorArray, int iNumVectors);
	char* GetDisassembledEffect(bool bEnableColorCode);

	void RemoveDefines();
	void AddDefine(const char* sKey, const char* sValue);

	char* GetName();

	bool LoadPrecompiledShader(const char* sDataSource);

	void SetTimeScale(float fTimeScale);
	void SetAsGlobal( bool bGlobal, cCONST_TV_SHADEROBJECT_TYPE eObjectType = cTV_SHADEROBJECT_ALL, const char* TechniqueName = NULL);

	void SetEffectParamRawFloatArray(const char* param, float* pFloatArray, int iNumFloats, int iParameterOffsetInFloats = 0);


};	

#endif
