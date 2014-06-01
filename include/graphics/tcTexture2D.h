/**  
**  @file tcTexture2D.h
*/
/*
**  Copyright (c) 2014, GCBLUE PROJECT
**  All rights reserved.
**
**  Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
**
**  1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
**
**  2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the 
**     documentation and/or other materials provided with the distribution.
**
**  3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from 
**     this software without specific prior written permission.
**
**  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT 
**  NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE 
**  COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
**  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
**  HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING 
**  IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef _TCTEXTURE2D_H_
#define _TCTEXTURE2D_H_

#if _MSC_VER > 1000
#pragma once
#endif 

#include <string>
#include "tv_types.h"

class CTVTextureFactory;

/**
* Class to hold loaded texture ref for TV3D
*/
class tcTexture2D
{
public:
    long GetId() const; ///< @returns index of texture from tex factory
    int Height() const;
    int Width() const;
    bool IsLoaded() const;
    void Create(int width, int height, bool hasAlpha, const char* name);
    void Load(const std::string& filename);
    void Load(const std::string& filename, int width, int height);
    void Unload();
    void UpdateTextureInfo();

    void Lock();
    void Unlock();
    int GetPixel(int x, int y);
    void SetPixel(int x, int y, int color_argb);


	tcTexture2D();
    tcTexture2D(long id_);
    tcTexture2D(const std::string& filename);
    tcTexture2D(const std::string& filename, int width, int height);
    virtual ~tcTexture2D();

private:
    const static std::string imagePath;
    static CTVTextureFactory* texFactory;

    long id;
    cTV_TEXTURE info;
};

#endif


