/** 
** @file tcParticleEffect.h
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

#ifndef _TCPARTICLEEFFECT_H_
#define _TCPARTICLEEFFECT_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <osgParticle/ParticleSystem>
#include <osgParticle/ParticleSystemUpdater>

namespace osgParticle
{
    class tcParticlePlacer;
    class ModularEmitter;
    class RadialShooter;
    class RandomRateCounter;
    class ModularProgram;
    class AccelOperator;
	class SmokeTrailEmitter;
	class Emitter;
}


/**
 * osgFx-based particle effect class
 */
class tcParticleEffect : public osgParticle::ParticleSystem
{
public:
    enum
    {
        OFF = 0,
        MISSILE = 1,
        AFTERBURNER = 2,
        DAMAGE = 4,
        GUN = 8,
        BUBBLES = 16
    };

    osgParticle::tcParticlePlacer* GetParticlePlacer() const {return particlePlacer;}

    void AddToSceneGraph(osg::Group* rootGroup);
    void DetachFromSceneGraph();
    void PreDestroy();

    tcParticleEffect(int smokeModeCode);
    virtual ~tcParticleEffect();

private:
    int smokeMode;
    osg::ref_ptr<osgParticle::Emitter> emitter;
    osg::ref_ptr<osgParticle::RadialShooter> shooter;
    osg::ref_ptr<osgParticle::RandomRateCounter> counter;
    osg::ref_ptr<osgParticle::ModularProgram> program;
    osg::ref_ptr<osgParticle::AccelOperator> accelOp;
    osg::ref_ptr<osg::Geode> geode;
    osg::ref_ptr<osgParticle::ParticleSystemUpdater> updater;

    osgParticle::tcParticlePlacer* particlePlacer;
    osg::Group* root;

    void ConfigureForMode();
    void InitializeGunEffect();
};

#endif
