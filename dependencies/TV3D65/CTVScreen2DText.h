#pragma once
#include "tv_types.h"

class EXPORTCLASS CTVScreen2DText
{
public:
	int iScreen2DTextIndex;
	CTVScreen2DText(void);
	~CTVScreen2DText(void);

	int NormalFont_Create(const char* sUserFont, const char* sFontName, int iSize, bool bBold, bool bUnderlined, bool bItalic);

	void NormalFont_DrawText(const char* sText, float x, float y, int iColor, int iNFont = 0);

	int TextureFont_Create(const char* sUserFont,const char* sFontName, int iSize, bool bBold, bool bUnderlined, bool bItalic, bool bInternational, bool bUseClearTypeAntialiasing = false);
	void TextureFont_GetTextSize(const char* sText, int iTextureFontID, float* retWidth, float* retHeight );
	void TextureFont_DrawBillboardText(const char* sText, float x, float y, float z, int iColor, int iFontID = 0, float fBillboardScaleX = 1, float fBillboardScaleY = 1);
	void TextureFont_DrawText(const char* sText, float x, float y, int iColor, int iTFont = 0);
	void TextureFont_DrawTextEx(const char* sText, cTV_3DMATRIX* mMat, int iColor, int iTFont = 0); 
	void TextureFont_DrawTextScaled(const char* sText, float x, float y, int iColor, float fScaleX = 1.0f, float fScaleY = 1.0f, int iTFont = 0); 
	int TextureFont_GetTexture(int iFontId);
	int TextureFont_CreateCustom(const char* sFontName, int iTextureID, int iNumChars, cTV_TEXTUREFONT_CHAR* pCharArray);

	void Font_DeleteAll();
	void Font_Delete(int iIndex);

	void Action_BeginText(bool bUseScreen2D = false);
	void Action_EndText();
 
	int NormalFont_GetFontByName(const char* sFontName);
	int TextureFont_GetFontByName(const char* sFontName);

	void TextureFont_GetFontData(int iFontID, int* retNumChars, cTV_TEXTUREFONT_CHAR* pCharArray);
	void NormalFont_GetTextSize(const char* sText, int iNormalFontID, float* retWidth, float* retHeight );

	void NormalFont_DrawTextUnicode(const WCHAR* sUnicodeText, float x, float y, int iColor, int iNFont);
	void NormalFont_GetTextSizeUnicode(const WCHAR* sUnicodeText, int iNormalFontID, float* retWidth, float* retHeight );

	bool TextureFont_Save(int iTextureFontID, const char* sDataSource, bool bIncludeTexture = true);
	int TextureFont_Load(const char* sDataSource,  bool bLoadTexture = true, int iDefaultTexture = 0);

};
 