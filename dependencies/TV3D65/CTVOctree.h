#pragma once
#include "tv_types.h"

class EXPORTCLASS CTVOctree
{
public:
	int iOctreeIndex; 
	CTVOctree(void);
	~CTVOctree(void);
	void Load(char* sFilename, bool UseLightmaps, char* sTexturePath, bool bUseTextureNumbers);
	void Render(void);
};
