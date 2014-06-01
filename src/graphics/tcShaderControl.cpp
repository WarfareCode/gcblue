/*
**  @file tcShaderControl.cpp
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
#endif // WX_PRECOMP

#include "tcShaderControl.h"
#include <osgDB/ReadFile>
#include <osgDB/FileUtils>
#include <osg/Notify>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif 


///////////////////////////////////////////////////////////////////////////
// for demo simplicity, this one callback animates all the shaders, instancing
// for each uniform but with a specific operation each time.

class AnimateCallback: public osg::Uniform::Callback
{
    public:
    
        enum Operation
        {
            OFFSET,
            SIN,
            COLOR1,
            COLOR2,
			BLEND
        };
    
        AnimateCallback(Operation op) : _enabled(true),_operation(op) {}

        virtual void operator() ( osg::Uniform* uniform, osg::NodeVisitor* nv )
        {
            if( _enabled )
            {
                float angle = 0.3*2.0 * nv->getFrameStamp()->getReferenceTime();
                float sine = sinf( angle );        // -1 -> 1
                float v01 = 0.5f * sine + 0.5f;        //  0 -> 1
                float v10 = 1.0f - v01;                //  1 -> 0
                switch(_operation)
                {
                    case OFFSET : uniform->set( osg::Vec3(0.505f, 0.8f*v01, 0.0f) ); break;
                    case SIN : uniform->set( sine ); break;
                    case COLOR1 : uniform->set( osg::Vec3(v10, 0.0f, 0.0f) ); break;
                    case COLOR2 : uniform->set( osg::Vec3(v01, v01, v10) ); break;
					case BLEND : uniform->set(v01); break;
                }
            }
        }

    private:
        bool _enabled;
        Operation _operation;
};
///////////////////////////////////////////////////////////////////////////


tcShaderControl* tcShaderControl::Get()
{
	static tcShaderControl instance;

	return &instance;
}


/**
* Loads shader source from a file
*/
void tcShaderControl::LoadShaderSource(osg::Shader* shader, const std::string& fileName)
{
    std::string filePath = osgDB::findDataFile(fileName);
    if (filePath.length() != 0 )
    {
        shader->loadShaderSourceFromFile(filePath.c_str() );
    }
    else
    {
        osg::notify(osg::WARN) << "File \"" << fileName << "\" not found." << std::endl;
    }
}

void tcShaderControl::AddTerrainElevationShader(osg::StateSet* ss)
{
	ss->setTextureAttribute(0, coastTexture.get());
	ss->setTextureAttribute(1, sandTexture.get());
	ss->setTextureAttribute(2, grassTexture.get());
	ss->setTextureAttribute(3, mountainTexture.get());

	osg::Program* terrainProgram = new osg::Program;
	terrainProgram->setName("terrain");
	programList.push_back(terrainProgram);

	osg::Shader* terrainVertObj = new osg::Shader(osg::Shader::VERTEX);
	osg::Shader* terrainFragObj = new osg::Shader(osg::Shader::FRAGMENT);

	terrainProgram->addShader(terrainVertObj);
	terrainProgram->addShader(terrainFragObj);
	ss->setAttributeAndModes(terrainProgram, osg::StateAttribute::ON);

	ss->addUniform(new osg::Uniform("coastTex", 0));
	ss->addUniform(new osg::Uniform("sandTex", 1));
	ss->addUniform(new osg::Uniform("grassTex", 2));
	ss->addUniform(new osg::Uniform("mountainTex", 3));

	LoadShaderSource(terrainVertObj, "shaders/terrain.vert");
    LoadShaderSource(terrainFragObj, "shaders/terrain.frag");



}


void tcShaderControl::AddTestShader(osg::StateSet* ss)
{
	osg::Uniform* offsetUniform = new osg::Uniform( "Offset", osg::Vec3(0.0f, 0.0f, 0.0f) );
	osg::Uniform* sineUniform   = new osg::Uniform( "Sine", 0.0f );
	osg::Uniform* color1Uniform = new osg::Uniform( "Color1", osg::Vec3(0.0f, 0.0f, 0.0f) );
	osg::Uniform* color2uniform = new osg::Uniform( "Color2", osg::Vec3(0.0f, 0.0f, 0.0f) );

	offsetUniform->setUpdateCallback(new AnimateCallback(AnimateCallback::OFFSET));
	sineUniform->setUpdateCallback(new AnimateCallback(AnimateCallback::SIN));
	color1Uniform->setUpdateCallback(new AnimateCallback(AnimateCallback::COLOR1));
	color2uniform->setUpdateCallback(new AnimateCallback(AnimateCallback::COLOR2));


	ss->addUniform(offsetUniform);
	ss->addUniform(sineUniform);
	ss->addUniform(color1Uniform);
	ss->addUniform(color2uniform);


	osg::Program* blockyProgram = new osg::Program;
	blockyProgram->setName("blocky");
	programList.push_back(blockyProgram);

	osg::Shader* blockyVertObj = new osg::Shader(osg::Shader::VERTEX);
	osg::Shader* blockyFragObj = new osg::Shader(osg::Shader::FRAGMENT);
	blockyProgram->addShader(blockyFragObj);
	blockyProgram->addShader(blockyVertObj);

	ss->setAttributeAndModes(blockyProgram, osg::StateAttribute::ON);

    LoadShaderSource(blockyVertObj, "shaders/blocky.vert");
    LoadShaderSource(blockyFragObj, "shaders/blocky.frag");
}

void tcShaderControl::AddWaterShader(osg::StateSet* ss)
{
	osg::Uniform* sineUniform = new osg::Uniform("Sine", 0.0f);
	sineUniform->setUpdateCallback(new AnimateCallback(AnimateCallback::BLEND));
	ss->addUniform(sineUniform);

	//ss->setTextureMode(4, GL_TEXTURE_2D, osg::StateAttribute::ON);
	//ss->setTextureMode(1, GL_TEXTURE_2D, osg::StateAttribute::OFF);

	ss->setTextureAttribute(0, water1.get());
	ss->setTextureAttribute(1, water2.get());


	osg::Program* waterProgram = new osg::Program;
	waterProgram->setName("water");
	programList.push_back(waterProgram);

	osg::Shader* waterVertObj = new osg::Shader(osg::Shader::VERTEX);
	osg::Shader* waterFragObj = new osg::Shader(osg::Shader::FRAGMENT);


	waterProgram->addShader(waterVertObj);
	waterProgram->addShader(waterFragObj);
	ss->setAttributeAndModes(waterProgram, osg::StateAttribute::ON);

	ss->addUniform(new osg::Uniform("water1tex", 0));
	ss->addUniform(new osg::Uniform("water2tex", 1));

	LoadShaderSource(waterVertObj, "shaders/water.vert");
    LoadShaderSource(waterFragObj, "shaders/water.frag");

}


void tcShaderControl::LoadTextures()
{
    water1 = new osg::Texture2D;
    water1->setImage(osgDB::readImageFile("water2b.bmp"));
    water1->setWrap(osg::Texture::WRAP_S, osg::Texture::MIRROR);
    water1->setWrap(osg::Texture::WRAP_T, osg::Texture::MIRROR);

    water2 = new osg::Texture2D;
    water2->setImage(osgDB::readImageFile("water2_256.bmp"));
    water2->setWrap(osg::Texture::WRAP_S, osg::Texture::MIRROR);
    water2->setWrap(osg::Texture::WRAP_T, osg::Texture::MIRROR);

	seaTexture = new osg::Texture2D;
	seaTexture->setImage(osgDB::readImageFile("rock_texture_b.jpg"));
    seaTexture->setWrap(osg::Texture::WRAP_S, osg::Texture::MIRROR);
    seaTexture->setWrap(osg::Texture::WRAP_T, osg::Texture::MIRROR);

	coastTexture = new osg::Texture2D;
    coastTexture->setImage(osgDB::readImageFile("sea1.bmp"));
    coastTexture->setWrap(osg::Texture::WRAP_S, osg::Texture::MIRROR);
    coastTexture->setWrap(osg::Texture::WRAP_T, osg::Texture::MIRROR);

	sandTexture = new osg::Texture2D;
    sandTexture->setImage(osgDB::readImageFile("sand12.bmp"));
    sandTexture->setWrap(osg::Texture::WRAP_S, osg::Texture::MIRROR);
    sandTexture->setWrap(osg::Texture::WRAP_T, osg::Texture::MIRROR);

	grassTexture = new osg::Texture2D;
    grassTexture->setImage(osgDB::readImageFile("grass20.bmp"));
    grassTexture->setWrap(osg::Texture::WRAP_S, osg::Texture::MIRROR);
    grassTexture->setWrap(osg::Texture::WRAP_T, osg::Texture::MIRROR);

	mountainTexture = new osg::Texture2D;
	mountainTexture->setImage(osgDB::readImageFile("rock04.bmp"));
    mountainTexture->setWrap(osg::Texture::WRAP_S, osg::Texture::MIRROR);
    mountainTexture->setWrap(osg::Texture::WRAP_T, osg::Texture::MIRROR);

}

tcShaderControl::tcShaderControl()
{
	LoadTextures();
}

tcShaderControl::~tcShaderControl()
{
}

