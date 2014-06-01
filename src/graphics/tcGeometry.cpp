/**  
**  @file tcGeometry.cpp
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

#include "tcGeometry.h"
#include "tcTVEngine.h"
#include "tcTexture2D.h"
#include "math_constants.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif 

void tcGeometry::Draw(float x, float y)
{
    switch (mode)
    {
    case TEXTURE:
        {
            if (image.get() == 0) return;

            CTVScreen2DImmediate* screen2D = tcTVEngine::Get()->GetScreen2D();
            float hw = 0.5f * symbolWidth;

            screen2D->Draw_Texture(image->GetId(), x-hw, y-hw, x+hw, y+hw, nColor);
        }
        break;
    case PIE:
        {
            DrawPie(x, y);
        }
        break;
    case BOX:
        {
            DrawBox(x, y);
        }
        break;
    case NULL:
        break;
    default:
        wxASSERT(false);
        break;
    }
}

void tcGeometry::DrawZoom(float x, float y, float scale)
{
    switch (mode)
    {
    case TEXTURE:
        {
            if (image.get() == 0) return;

            CTVScreen2DImmediate* screen2D = tcTVEngine::Get()->GetScreen2D();
            float hw = 0.5f * symbolWidth * scale;

            screen2D->Draw_Texture(image->GetId(), x-hw, y-hw, x+hw, y+hw, nColor);
        }
        break;
    case PIE:
        {
            DrawPie(x, y);
        }
        break;
    case BOX:
        {
            DrawBox(x, y);
        }
        break;
    case NULL:
        break;
    default:
        wxASSERT(false);
        break;
    }

}



void tcGeometry::DrawBox(float x, float y)
{
    CTVScreen2DImmediate* screen2D = tcTVEngine::Get()->GetScreen2D();

	float half_width = 0.5f * width;
	float half_height = 0.5f * height;

    screen2D->Draw_Box(x - half_width, y - half_height, x + half_width, y + half_height,
        nColor);
}


void tcGeometry::DrawPie(float x, float y)
{
    CTVScreen2DImmediate* screen2D = tcTVEngine::Get()->GetScreen2D();

    bool fullCircle = ((stopAngle_rad - startAngle_rad) >= C_TWOPIM);

    const float angleScale = 1.0f /  float(nArcPoints-1);
	float deltaAngle = (stopAngle_rad - startAngle_rad) * angleScale;
	float half_width = 0.5f * width;
	float half_height = 0.5f * height;
//	float xc = 0;
//	float yc = 0;

	float angle = stopAngle_rad;


    // int nColor = RGBA(color.x, color.y, color.z, color.w);

    if (fullCircle)
    {
        if (!fill)
        {
            screen2D->Draw_Ellipse(x, y, half_width, half_height, 3*nArcPoints, nColor);
        }
        else
        {
            screen2D->Draw_FilledEllipse(x, y, half_width, half_height, 3*nArcPoints, nColor);
        }
        return;
    }
    
    if (!fill)
    {
        float x1 = x;
        float y1 = y;
        float x2 = x + half_width*sinf(angle);
        float y2 = y - half_height*cosf(angle);


        screen2D->Draw_Line(x1, y1, x2, y2, nColor);

        for (unsigned int n = 0; n < nArcPoints; n++)
        {
            angle -= deltaAngle;

            x1 = x2;
            y1 = y2;
            x2 = x + half_width * sinf(angle);
            y2 = y - half_height * cosf(angle);

            screen2D->Draw_Line(x1, y1, x2, y2, nColor);
        }

        screen2D->Draw_Line(x2, y2, x, y, nColor);
    }
    else
    {
        float x1 = x;
        float y1 = y;
        float x2 = x + half_width*sinf(angle);
        float y2 = y - half_height*cosf(angle);

        for (unsigned int n = 0; n < nArcPoints; n++)
        {
            angle -= deltaAngle;

            x1 = x2;
            y1 = y2;
            x2 = x + half_width * sinf(angle);
            y2 = y - half_height * cosf(angle);

            screen2D->Draw_FilledTriangle(x, y, x1, y1, x2, y2, nColor);
        }
    }


#if 0
	// add center point if not full circle
	if (!fullCircle)
	{
		vertices->push_back(osg::Vec3(xc, yc, 0));
	}

	for (unsigned int n = 0; n < nArcPoints; n++)
	{
		float x = xc + half_width * sinf(angle);
		float y = yc + half_height * cosf(angle);

		vertices->push_back(osg::Vec3(x, y, 0));
		angle -= deltaAngle;
	}

	unsigned int nPoints = vertices->size();


	if (fillMode == FILL_OFF)
	{
		symbol->addPrimitiveSet(new osg::DrawArrays(GL_LINE_LOOP, 0, nPoints));
	}
	else
	{
		symbol->addPrimitiveSet(new osg::DrawArrays(GL_TRIANGLE_FAN, 0, nPoints));
	}
#endif
}

const Vec4& tcGeometry::GetColor() const
{
    return color;
}

float tcGeometry::GetSize() const
{
    return symbolWidth;
}

void tcGeometry::MakeBox(float width_, float height_, const Vec4& color_)
{
    mode = BOX;

    width = width_;
    height = height_;
    SetColor(color_);
}


void tcGeometry::MakePie(float width_, float height_, float startAngle_deg, float stopAngle_deg, 
											 Vec4& color_, bool fill_)
{
    mode = PIE;

    width = width_;
    height = height_; 
    startAngle_rad = C_PIOVER180 * startAngle_deg;
    stopAngle_rad = C_PIOVER180 * stopAngle_deg;
    SetColor(color_);
    fill = fill_;
}

void tcGeometry::MakeTexturedSymbol(boost::shared_ptr<tcTexture2D> tex, float size)
{
    mode = TEXTURE;

    image = tex;
    symbolWidth = size;
}

void tcGeometry::SetColor(const Vec4& c)
{
    color = c;
    nColor = RGBA(color.x, color.y, color.z, color.w);
}

void tcGeometry::SetSize(float val)
{
    symbolWidth = val;
}


tcGeometry::tcGeometry(const tcGeometry& src)
: mode(src.mode), image(src.image), symbolWidth(src.symbolWidth),
  nArcPoints(src.nArcPoints), color(src.color), nColor(src.nColor),
  width(src.width),
  height(src.height),
  startAngle_rad(src.startAngle_rad),
  stopAngle_rad(src.stopAngle_rad),
  fill(src.fill)
{
}

tcGeometry& tcGeometry::operator=(const tcGeometry& src)
{
    mode = src.mode;
    image = src.image;
    symbolWidth = src.symbolWidth;

    width = src.width;
    height = src.height;
    startAngle_rad = src.startAngle_rad;
    stopAngle_rad = src.stopAngle_rad;
    fill = src.fill;

    color = src.color;
    nColor = src.nColor;

    return *this;
}

tcGeometry::tcGeometry()
: symbolWidth(0),
  mode(UNDEFINED),
  nArcPoints(48),
  color(1, 1, 1, 1),
  nColor(-1)
{
}

tcGeometry::~tcGeometry()
{
}