/**  
**  @file tcTexture2D.cpp
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

#include "tcTexture2D.h"
#include "tcTVEngine.h"
#include "wx/string.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif 

const std::string tcTexture2D::imagePath = "images/";
CTVTextureFactory* tcTexture2D::texFactory = 0;

/**
* Create texture in memory (vs. loading from file)
*/
void tcTexture2D::Create(int width, int height, bool hasAlpha, const char* name)
{
    if (IsLoaded())
    {
        bool isSameSize = (width == Width()) && (height == Height());
        if (isSameSize)
        {
            return; // already created, just return
        }
        else
        {
            Unload();
        }
        
#ifdef _DEBUG
        fprintf(stdout, "tcTexture2D::Create - Recreating texture with different size\n");
#endif
    }

    wxASSERT(texFactory != 0);
    id = texFactory->CreateTexture(width, height, hasAlpha, name);
    info = texFactory->GetTextureInfo(id);
}

long tcTexture2D::GetId() const
{
    return id;
}

/**
* @return color in ARGB format
*/
int tcTexture2D::GetPixel(int x, int y)
{
    return texFactory->GetPixel(id, x, y);
}

int tcTexture2D::Height() const
{
    return info.Height;
}

int tcTexture2D::Width() const
{
    return info.Width;
}

bool tcTexture2D::IsLoaded() const
{
    return (id != 0);
}

void tcTexture2D::Load(const std::string& filename)
{
    wxASSERT(texFactory != 0);
    id = texFactory->LoadTexture(filename.c_str(), 0, -1, -1, cTV_COLORKEY_USE_ALPHA_CHANNEL , true);
    if (id != 0)
    {
        info = texFactory->GetTextureInfo(id);

#ifdef _DEBUG
        fprintf(stdout, "tcTexture2D::Load - loaded %s, idx %d\n", filename.c_str(), id);
#endif
    }
    else
    {
        fprintf(stderr, "tcTexture2D::Load - load FAILED for %s\n", filename.c_str());
        wxASSERT(false); 
    }
}

void tcTexture2D::Load(const std::string& filename, int width, int height)
{
    wxASSERT(texFactory != 0);
    id = texFactory->LoadTexture(filename.c_str(), 0, width, height, cTV_COLORKEY_USE_ALPHA_CHANNEL , true);
    if (id != 0)
    {
        info = texFactory->GetTextureInfo(id);

#ifdef _DEBUG
        fprintf(stdout, "tcTexture2D::Load - loaded %s, idx %d (w:%d,h:%d)\n", filename.c_str(), id, width, height);
#endif
    }
    else
    {
        fprintf(stderr, "tcTexture2D::Load - load FAILED for %s\n", filename.c_str());
        wxASSERT(false); 
    }
}

void tcTexture2D::Lock()
{
    wxASSERT(texFactory != 0);
    texFactory->LockTexture(id, false);
}

void tcTexture2D::SetPixel(int x, int y, int color_argb)
{
    texFactory->SetPixel(id, x, y, color_argb);
}


void tcTexture2D::Unload()
{
    wxASSERT(texFactory != 0);
    if (texFactory != 0) texFactory->DeleteTexture(id);
}

void tcTexture2D::Unlock()
{
    wxASSERT(texFactory != 0);
    texFactory->UnlockTexture(id, true);
}

void tcTexture2D::UpdateTextureInfo()
{
    wxASSERT(texFactory != 0);
    info = texFactory->GetTextureInfo(id);
}


tcTexture2D::tcTexture2D()
: id(0)
{
}

/**
* Use this constructor for passing id to methods that
* need tcTexture2D
*
* Revisit this if destructor is ever modified to delete texture
*/
tcTexture2D::tcTexture2D(long id_)
: id(id_)
{
    if (texFactory == 0)
    {
        texFactory = tcTVEngine::Get()->GetTextureFactory();
    }
}

tcTexture2D::tcTexture2D(const std::string& filename)
{    
    if (texFactory == 0)
    {
        texFactory = tcTVEngine::Get()->GetTextureFactory();
    }

    Load(filename);
}

tcTexture2D::tcTexture2D(const std::string& filename, int width, int height)
{    
    if (texFactory == 0)
    {
        texFactory = tcTVEngine::Get()->GetTextureFactory();
    }

    Load(filename, width, height);
}


tcTexture2D::~tcTexture2D()
{
//    CTVTextureFactory* texFactory = tcTVEngine::Get()->GetTextureFactory();
//    if (texFactory != 0) texFactory->DeleteTexture(id);
}