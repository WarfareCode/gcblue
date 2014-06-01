/** 
**  @file tcSmoker.h 
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

#ifndef _TCSMOKER_H_
#define _TCSMOKER_H_

#if _MSC_VER > 1000
#pragma once
#endif 

#include <osg/ref_ptr>
#include <osg/Group>
#include <osg/LOD>
#include <osg/MatrixTransform>

class tcGameObject;
class tcParticleEffect;

namespace osgParticle
{
    class tcParticlePlacer;
}

class tcGameObject;

/**
*
*/
class tcSmokeTrail : public osg::Referenced
{
public:
    osg::ref_ptr<tcParticleEffect> smokeEffect;
    osg::ref_ptr<osgParticle::tcParticlePlacer> smokePlacer;
    osg::Vec3 smokeSource; ///< position of smoke emitter in model coordinates

    tcSmokeTrail& operator= (const tcSmokeTrail& rhs);

    tcSmokeTrail();
    tcSmokeTrail(const tcSmokeTrail& source);
    virtual ~tcSmokeTrail();
};

/**
* Collection of smoke trails using particle effects
*/
class tcSmoker
{
public:
    void AddSmokeTrail(const osg::Vec3& smokeSource, int smokeMode);
    void DeleteTrails();
    bool IsEnabled() const;
    void SetGameObject(tcGameObject* obj);
    void UpdateSmokePosition(float x, float y, float z);

    static void SetWorldFrame(osg::Group* worldFrame);


    tcSmoker();
    ~tcSmoker();

private:
    std::vector<osg::ref_ptr<tcSmokeTrail> > smokeTrails;
    tcGameObject *gameObj; ///< game object to use to update model state

    static osg::ref_ptr<osg::Group> world;
};

#endif

