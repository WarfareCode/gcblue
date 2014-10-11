//////////////////////////////////////////////////////////////////////////
// TrueVision3D TVScreen2DImmediate header
//////////////////////////////////////////////////////////////////////////
#pragma once
#include "tv_types.h"
#include "ctvshader.h"

class EXPORTCLASS CTVScreen2DImmediate
{
public:
	int iScreen2DImmediateIndex;
	CTVScreen2DImmediate(void);
	~CTVScreen2DImmediate(void);
	 
	// new
	void Draw_FilledEllipse(float x, float y, float radiusX, float radiusY, int step = 12, int color = -1);
	void Draw_Ellipse(float x, float y, float radiusX, float radiusY, int step = 12, int color = -1);
	// end new

	void Draw_Circle(float x, float y, float radius, int step = 12, int color = -1);
	void Draw_Triangle(float x1, float y1, float x2, float y2, float x3, float y3, int color = -1);
	void Draw_Box(float x1, float y1, float x2, float y2, int color = -1 );

	void Draw_Texture(int tex, float x1, float y1, float x2, float y2, int color1 = -1, int color2 = -2, int color3 = -2, int color4 = -2, float tu1 = 0.0f, float tv1 = 0.0f, float tu2 = 1.0f, float tv2 = 1.0f);
	void Draw_Sprite(int tex, float x, float y, int color = -1);
	void Draw_TextureRotated(int tex, float x, float y, float width, float height , float angle, int color1 = -1, int color2 = -2, int color3 = -2, int color4 = -2, float tu1 = 0.0f, float tv1 = 0.0f, float tu2 = 1.0f, float tv2 = 1.0f);
	void Draw_Line(float x, float y, float x1, float y1, int color1 = -1, int color2 = -2 );
	void Draw_Line3D(float x, float y, float z, float x1, float y1, float z1, int color1 = -1, int color2 = -2);
	void Draw_FilledTriangle(float x1, float y1, float x2, float y2, float x3, float y3, int color1 = -2, int color2 = -2, int color3 = -2);
	void Draw_FilledCircle(float x, float y, float radius, int step = 12, int color = -1);
	void Draw_FilledBox(float x1, float y1, float x2, float y2, int color1 = -1, int color2 = -2, int color3 = -2, int color4 = -2);

	void Draw_CustomWithShader(CTVShader* shader, cCONST_TV_PRIMITIVETYPE primitivetype, cTV_CUSTOM2DVERTEX* pVerticesArray, int numvertices, int tex1 = 0, int tex2 = 0, int tex3 = 0, int tex4 = 0);
	void Draw_Custom(int tex, cCONST_TV_PRIMITIVETYPE primitivetype, cTV_CUSTOM2DVERTEX* pVerticesArray, int numvertices);

	void Draw_Recorded(int lIndex);

	void Load_Background(char* sFilename, bool bTiling = false); 
	void Draw_Background();
	void Delete_Background();

	// settings.
	void Settings_SetClamping(bool bEnable);
	void Settings_SetAlphaTest(bool bEnable, int alpharef = 128);
	void Settings_SetAlphaBlending(bool bEnable, cCONST_TV_BLENDINGMODE eBlendingmode);
	void Settings_SetAlphaBlendingEx(bool bEnable, cCONST_TV_BLENDEX eSrcBlend, cCONST_TV_BLENDEX eDestBlend);
	void Settings_SetTextureFilter(cCONST_TV_TEXTUREFILTER eTextureFilter);
	void Settings_SetAutoDrawBackground(bool bEnable);

	// recording/call list.
	int Action_RecordEnd();
	void Action_RecordStart();

	// normal 2d
	void Action_End2D();
	void Action_Begin2D();

	// projection.
	bool Math_3DPointTo2D(cTV_3DVECTOR* vPoint, float* ret_x, float* ret_y, bool bFrontOnly = false);
 
	bool Draw_RollOver(int iTextureOver, int iTextureNormal, float fLeft, float fTop, float fRight, float fBottom);
	bool Draw_RollOverEx(int iTextureOver, int iTextureNormal, float fTextureLeft, float fTextureTop, float fTextureRight, float fTextureBottom, float fMouseLeft, float fMouseTop, float fMouseRight, float fMouseBottom);
 

	void Settings_Set3DLineParameters(bool bUseDepthTesting); 
	void Draw_FullscreenQuadWithShader(CTVShader* pShader, float fTULeft, float fTVTop, float fTURight, float fTUBottom, int iOptionalTextureLayer0 = 0, int iOptionalTextureLayer1 = 0);
	void Draw_Point(float fX, float fY, int iColor = -1);
	void Draw_SpriteScaled(int iTexture, float fX, float fY, int iColor = -1, float fScaleX = 1.0f, float fScaleY = 1.0f);
	void Action_RecordDelete(int iRecordIndex);

	cCONST_TV_TEXTUREFILTER Settings_GetTextureFilter();
	void Settings_GetAlphaBlendingEx(bool* retbEnable, cCONST_TV_BLENDEX* reteSrcBlend, cCONST_TV_BLENDEX* reteDestBlend);
	void Settings_GetAlphaTest(bool* retbEnable, int* retAlphaRef);

	void Draw_TextureRotatedEx(int iTexture, float fX, float fY, float fWidth, float fHeight , float fAngle, float fCenterX, float fCenterY, int color1 = -1, int color2 = -2, int color3 = -2, int color4 = -2, float tu1 = 0.0f, float tv1 = 0.0f, float tu2 = 1.0f, float tv2 = 1.0f);
	void Draw_Box3D(cTV_3DVECTOR* vBoxMin, cTV_3DVECTOR* vBoxMax, int iColor);
	void Draw_Box3DEx(cTV_3DVECTOR* vBoxMin, cTV_3DVECTOR* vBoxMax,  cTV_3DMATRIX* mMatrix, int iColor);
	void Draw_QuadWithShader(CTVShader* pShader, float fX1, float fY1, float fX2, float fY2, float fTu1, float fTv1, float fTu2, float fTv2, int iOptionalTextureLayer0 = 0, int iOptionalTextureLayer1 = 0);

};
