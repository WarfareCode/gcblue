/**  
**  @file tcGeometry.h
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

#ifndef _TCGEOMETRY_
#define _TCGEOMETRY_

#if _MSC_VER > 1000
#pragma once
#endif 

#include "tv_types.h"
#include <boost/shared_ptr.hpp>

class tcTexture2D;

/**
* Class to approximate osg::Geometry
*/
class tcGeometry
{
public:

    void Draw(float x, float y);
	void DrawZoom(float x, float y, float scale);

    void MakeBox(float width_, float height_, const Vec4& color_);
    void MakePie(float width_, float height_, float startAngle_deg, float stopAngle_deg, 
											 Vec4& color_, bool fill_);
    void MakeTexturedSymbol(boost::shared_ptr<tcTexture2D> tex, float size);

    const Vec4& GetColor() const;
    void SetColor(const Vec4& c);

    float GetSize() const;
    void SetSize(float val);

	tcGeometry();
    tcGeometry(const tcGeometry& src);
    tcGeometry& operator=(const tcGeometry& src);
    virtual ~tcGeometry();

private:    
    enum Mode 
    {
        UNDEFINED = 0,
        TEXTURE = 1,
        PIE = 2,
        BOX = 3
    } mode;


    // for TEXTURE mode
    boost::shared_ptr<tcTexture2D> image;
    float symbolWidth;

    // for PIE mode
    float width;
    float height;
    float startAngle_rad;
    float stopAngle_rad;
    bool fill;
    const unsigned int nArcPoints;

    // for ALL modes
    Vec4 color;
    int nColor; // integer version

    void DrawBox(float x, float y);
    void DrawPie(float x, float y);


};

#endif


