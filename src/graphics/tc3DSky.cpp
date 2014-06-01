/*
**  tc3DTerrain.cpp
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

#include "stdwx.h" // precompiled header file

#ifndef WX_PRECOMP
#include "wx/wx.h" 
#ifdef WIN32
#include "wx/msw/private.h" // for MS Windows specific definitions
#endif
#endif

#include "tc3DSky.h"
#include <osgDB/ReadFile>
#include "math_constants.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif 

void tc3DSky::CreateSky()
{
    skyGeometry = new osg::Geometry();

    osg::Vec3Array* vertices = new osg::Vec3Array;

    const int nFaces = 16;
    float dtheta = C_TWOPI/(float)nFaces;
    float radius = 150000;
    float height1 = -10000;
    float height2 = 50000;
    osg::Vec4 horizonColor(0.0f,0.0f,0.3f,1.0f);
    osg::Vec4 skyColor(0.6f,0.6f,1.0f,1.0f);

    osg::Vec3Array* normals = new osg::Vec3Array;

    osg::Vec4Array* colors = new osg::Vec4Array;

    osg::Vec3 center(0,0,height2);

    for (int n=0;n<nFaces;n++)
    {
        float theta1 = (float)n * dtheta;
        float theta2 = (float)(n+1) * dtheta;
        float x1 = radius*sin(theta1);
        float y1 = radius*cos(theta1);
        float x2 = radius*sin(theta2);
        float y2 = radius*cos(theta2);

        osg::Vec3 v1(x2, y2, height1);
        osg::Vec3 v2(x2, y2, height2);
        osg::Vec3 v3(x1, y1, height2);
        osg::Vec3 v4(x1, y1, height1);
        osg::Vec3 normVec = -((v2-v1)^(v4-v1));
        normVec.normalize();

        vertices->push_back(v1);
        vertices->push_back(v2);
        vertices->push_back(v3);
        vertices->push_back(v1);
        vertices->push_back(v3);
        vertices->push_back(v4);    
        // draw top
        vertices->push_back(center);
        vertices->push_back(v3);
        vertices->push_back(v2);    

        colors->push_back(horizonColor);
        colors->push_back(skyColor);
        colors->push_back(skyColor);
        colors->push_back(horizonColor);
        colors->push_back(skyColor);
        colors->push_back(horizonColor);
        colors->push_back(skyColor);
        colors->push_back(skyColor);
        colors->push_back(skyColor);

        normals->push_back(normVec);
        normals->push_back(normVec);
        normals->push_back(osg::Vec3(0,0,-1));
    }

    // pass the created vertex array to the points geometry object.
    skyGeometry->setVertexArray(vertices);

    // set the normal
    skyGeometry->setNormalArray(normals);
    skyGeometry->setNormalBinding(osg::Geometry::BIND_PER_PRIMITIVE);

    // set the color array 
    skyGeometry->setColorArray(colors);
    skyGeometry->setColorBinding(osg::Geometry::BIND_PER_VERTEX);


    // create and add a DrawArray Primitive (see include/osg/Primtive).  The first
    // paramter passed to the DrawArrays constructor is the Primtive::Mode which
    // in this case is POINTS (which has the same value GL_POINTS), the second
    // parameter is the index position into the vertex array of the first point
    // to draw, and the third parameter is the number of points to draw.
    skyGeometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::TRIANGLES,0,vertices->size()));

}

osg::ref_ptr<osg::Node> tc3DSky::GetSkyNode()
{
    osg::ref_ptr<osg::Geode> geo = new osg::Geode();
    geo->addDrawable(skyGeometry.get());
    osg::ref_ptr<osg::Node> node = geo.get(); // may be optional, but don't want trouble with ref ptrs
    return node;
}

tc3DSky::tc3DSky()
{
    CreateSky();
}

tc3DSky::~tc3DSky()
{
}

