/*  
**  @file tcShaderControl.h
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

#ifndef _SHADERCONTROL_H_
#define _SHADERCONTROL_H_

#ifdef WIN32
#pragma once
#endif 

#include <osg/ref_ptr>
#include <osg/Program>
#include <osg/Shader>
#include <osg/Uniform>
#include <osg/Texture2D>



/**
* Singleton class to add and manage shaders
* May want to distribute shader control, using this class for static helper methods only?
* 
* Started with OSG shader example by Mike Weiblen 
*/
class tcShaderControl
{
public:
	void AddTerrainElevationShader(osg::StateSet* ss);
	void AddTestShader(osg::StateSet* ss);
    void AddWaterShader(osg::StateSet* ss);

	static tcShaderControl* Get(); ///< singleton accessor
	static void LoadShaderSource(osg::Shader* shader, const std::string& fileName);

private:
	std::vector< osg::ref_ptr<osg::Program> > programList;
	osg::ref_ptr<osg::Texture2D> water1;
	osg::ref_ptr<osg::Texture2D> water2;

    osg::ref_ptr<osg::Texture2D> seaTexture;
    osg::ref_ptr<osg::Texture2D> coastTexture;
    osg::ref_ptr<osg::Texture2D> sandTexture;
    osg::ref_ptr<osg::Texture2D> grassTexture;
    osg::ref_ptr<osg::Texture2D> mountainTexture;


	void LoadTextures();
	tcShaderControl();
    ~tcShaderControl();
};

#endif

