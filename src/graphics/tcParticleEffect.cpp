/** @file tcParticleEffect.cpp
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

#include "tcParticleEffect.h"

#include <osg/Group>
#include <osg/Geode>

#include <osgParticle/Particle>
#include <osgParticle/ParticleSystem>
#include <osgParticle/ParticleSystemUpdater>
#include <osgParticle/Emitter>
#include <osgParticle/ModularEmitter>
#include <osgParticle/ModularProgram>
#include <osgParticle/RandomRateCounter>
#include <osgParticle/SectorPlacer>
#include <osgParticle/RadialShooter>
#include <osgParticle/AccelOperator>
#include <osgParticle/FluidFrictionOperator>

#include <graphics/SmokeTrailEmitter.h>

#include "stdwx.h" // precompiled header file

#ifndef WX_PRECOMP
#include "wx/wx.h"
#ifdef WIN32
#include "wx/msw/private.h" // for MS Windows specific definitions
#endif
#endif

#include "tcParticlePlacer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif 

//////////////////////////////////////////////////////////////////////////////
// CUSTOM OPERATOR CLASS
//////////////////////////////////////////////////////////////////////////////

// This class demonstrates Operator subclassing. This way you can create
// custom operators to apply your motion effects to the particles. See docs
// for more details.
class VortexOperator: public osgParticle::Operator {
public:
	VortexOperator() 
		: osgParticle::Operator(), center_(0, 0, 0), axis_(0, 0, 1), intensity_(0.1f) {}

	VortexOperator(const VortexOperator &copy, const osg::CopyOp &copyop = osg::CopyOp::SHALLOW_COPY)
		: osgParticle::Operator(copy, copyop), center_(copy.center_), axis_(copy.axis_), intensity_(copy.intensity_) {}

	META_Object(osgParticle, VortexOperator);

	void setCenter(const osg::Vec3 &c)
	{
		center_ = c;
	}

	void setAxis(const osg::Vec3 &a)
	{
		axis_ = a / a.length();
	}

	// this method is called by ModularProgram before applying
	// operators on the particle set via the operate() method.	
	void beginOperate(osgParticle::Program *prg)
	{
		// we have to check whether the reference frame is relative to parents
		// or it's absolute; in the first case, we must transform the vectors
		// from local to world space.
        if (prg->getReferenceFrame() == osgParticle::Program::RELATIVE_RF) {
			// transform the center point (full transformation)
			xf_center_ = prg->transformLocalToWorld(center_);
			// transform the axis vector (only rotation and scale)
			xf_axis_ = prg->rotateLocalToWorld(axis_);
		} else {
			xf_center_ = center_;
			xf_axis_ = axis_;
		}
	}

	// apply a vortex-like acceleration. This code is not optimized,
	// it's here only for demonstration purposes.
	void operate(osgParticle::Particle *P, double dt)
	{
		float l = xf_axis_ * (P->getPosition() - xf_center_);
		osg::Vec3 lc = xf_center_ + xf_axis_ * l;
		osg::Vec3 R = P->getPosition() - lc;
		osg::Vec3 v = (R ^ xf_axis_) * P->getMassInv() * intensity_;

		// compute new position
		osg::Vec3 newpos = P->getPosition() + v * dt;

		// update the position of the particle without modifying its
		// velocity vector (this is unusual, normally you should call
		// the Particle::setVelocity() or Particle::addVelocity()
		// methods).
		P->setPosition(newpos);	
	}

protected:
	virtual ~VortexOperator() {}

private:
	osg::Vec3 center_;
	osg::Vec3 xf_center_;
	osg::Vec3 axis_;
	osg::Vec3 xf_axis_;
	float intensity_;
};



void tcParticleEffect::AddToSceneGraph(osg::Group* rootGroup)
{
    if (root)
    {
        fprintf(stderr, "Warning - tcParticleEffect already added to scene graph, "
            "detaching first\n");
        DetachFromSceneGraph();
    }

    root = rootGroup;

    // add the emitter to the scene graph
    wxASSERT(emitter.valid());
	root->addChild(emitter.get());

    // add program to the scene graph
    wxASSERT(program.valid());
	root->addChild(program.get());

	// add top-level geode to scene graph
    wxASSERT(geode.valid());
	root->addChild(geode.get());

	// add the updater node to the scene graph
    wxASSERT(updater.valid());
	root->addChild(updater.get());

}

/**
* Configures particle template based on smoke mode
*/
void tcParticleEffect::ConfigureForMode()
{
    osgParticle::Particle ptemplate;




    switch (smokeMode)
    {
    case MISSILE:
        {
        //counter->setRateRange(300, 350);
        ptemplate.setLifeTime(2);		
        ptemplate.setSizeRange(osgParticle::rangef(0.5f, 10.0f));
        ptemplate.setAlphaRange(osgParticle::rangef(0.0f, 0.5f));
        ptemplate.setColorRange(osgParticle::rangev4(
            Vec4(0.8f, 0.8f, 0.8f, 0.2f), 
            Vec4(0, 0.7f, 1.0f, 0.5f)));
        ptemplate.setRadius(1.0f);	
        ptemplate.setMass(0.05f);	
        
        //shooter->setInitialSpeedRange(0, 0);
        accelOp->setAcceleration(osg::Vec3(0, 0, -0.0f));
		
		particlePlacer->setApplyJitter(true);
        setDefaultAttributes("smoke.rgb", false, false);

        }
        break;
    case AFTERBURNER:
        {
        //counter->setRateRange(300, 350);
        ptemplate.setLifeTime(2);		
        ptemplate.setSizeRange(osgParticle::rangef(0.5f, 10.0f));
        ptemplate.setAlphaRange(osgParticle::rangef(0.1f, 0.3f));
        ptemplate.setColorRange(osgParticle::rangev4(
            Vec4(0.5f, 0.2f, 0.2f, 1.5f), 
            Vec4(0, 0.7f, 1.0f, 0.0f)));
        ptemplate.setRadius(1.0f);	
        ptemplate.setMass(0.05f);	

        //shooter->setInitialSpeedRange(0, 0);
        accelOp->setAcceleration(osg::Vec3(0, 0, 0));

		particlePlacer->setApplyJitter(true);
        setDefaultAttributes("smoke.rgb", false, false);
        }
        break;
    case DAMAGE:
        {
        counter->setRateRange(20, 40);
        ptemplate.setLifeTime(8);		// 3 seconds of life
        ptemplate.setSizeRange(osgParticle::rangef(2.5f, 5.0f));
        ptemplate.setAlphaRange(osgParticle::rangef(0.0f, 1.5f));
        ptemplate.setColorRange(osgParticle::rangev4(
            Vec4(0.0f, 0.0f, 0.0f, 1.5f), 
            Vec4(0.7, 0.6f, 0.6f, 0.0f)));
        ptemplate.setRadius(25.0f);	
        ptemplate.setMass(0.05f);	// for friction op I guess


        shooter->setInitialSpeedRange(3, 15);
        //shooter->setPhiRange(-0.5, 0.5);
        //shooter->setThetaRange(-0.5, 0.5);

        accelOp->setAcceleration(osg::Vec3(0, 0, -0.1));

        //osgParticle::FluidFrictionOperator *op = new osgParticle::FluidFrictionOperator;
        //op->setFluidToAir();
        //program->addOperator(op);
        setDefaultAttributes("smoke.rgb", false, false);
        }
        break;
    case GUN:
        {
        counter->setRateRange(20, 40);
        ptemplate.setLifeTime(8);		// 3 seconds of life
        ptemplate.setSizeRange(osgParticle::rangef(2.5f, 5.0f));
        ptemplate.setAlphaRange(osgParticle::rangef(0.0f, 1.5f));
        ptemplate.setColorRange(osgParticle::rangev4(
            Vec4(0.0f, 0.0f, 0.0f, 1.5f), 
            Vec4(0.7, 0.6f, 0.6f, 0.0f)));
        ptemplate.setRadius(25.0f);	
        ptemplate.setMass(0.05f);	// for friction op I guess


        shooter->setInitialSpeedRange(3, 15);
        shooter->setThetaRange(-0.1, 0.1);
        shooter->setPhiRange(0, 0);

        accelOp->setAcceleration(osg::Vec3(0, 0, -0.5));

        osgParticle::FluidFrictionOperator *op = new osgParticle::FluidFrictionOperator;
        op->setFluidToAir();
        program->addOperator(op);

        setDefaultAttributes("smoke.rgb", false, false);
        }
        break;
    case BUBBLES:
        {
        ptemplate.setLifeTime(20);		
        ptemplate.setSizeRange(osgParticle::rangef(1.5f, 2.5f));
        //ptemplate.setAlphaRange(osgParticle::rangef(0.1f, 0.3f));
        ptemplate.setColorRange(osgParticle::rangev4(
            Vec4(1.0f, 1.0f, 1.0f, 0.02f), 
            Vec4(1.0f, 1.0f, 1.0f, 0.01f)));
        ptemplate.setRadius(1.0f);	
        ptemplate.setMass(0.05f);	

        counter->setRateRange(5, 10);

        shooter->setInitialSpeedRange(0, 0.1);

        accelOp->setAcceleration(osg::Vec3(0, 0, 0));

		particlePlacer->setApplyJitter(false);
        setDefaultAttributes("water01.png", false, false);
        }
        break;
    default:
        break;
    }


    //setDefaultAttributes("water06b.png", false, false);

    setDefaultParticleTemplate(ptemplate);
}

void tcParticleEffect::DetachFromSceneGraph()
{
    if (!root)
    {
#ifdef _DEBUG
        fprintf(stderr, "Warning - tcParticleEffect already removed from scene graph,"
            "skipping\n");
#endif
        return;
    }

	// remove the updater node from the scene graph
    wxASSERT(updater.valid());
	root->removeChild(updater.get());

	// remove geode from scene graph
    wxASSERT(geode.valid());
	root->removeChild(geode.get());

    // remove program from scene graph
    wxASSERT(program.valid());
	root->removeChild(program.get());

    // remove emitter from scene graph
    wxASSERT(emitter.valid());
    root->removeChild(emitter.get());

    root = 0;
}

void tcParticleEffect::InitializeGunEffect()
{
    osgParticle::ModularEmitter* modularEmitter = new osgParticle::ModularEmitter;
    emitter = modularEmitter;

    modularEmitter->setParticleSystem(this);

    counter = new osgParticle::RandomRateCounter;

    modularEmitter->setCounter(counter.get());

    particlePlacer = new osgParticle::tcParticlePlacer;
    particlePlacer->setCenter(0, 0, 0);

    modularEmitter->setPlacer(particlePlacer);
    modularEmitter->setReferenceFrame(osgParticle::Emitter::ABSOLUTE_RF);

    shooter = new osgParticle::RadialShooter;

    modularEmitter->setShooter(shooter.get());

    program = new osgParticle::ModularProgram;
    program->setParticleSystem(this);

    // create an operator that simulates the gravity acceleration.
    accelOp = new osgParticle::AccelOperator;
    program->addOperator(accelOp.get());
}

/**
* Workaround for circular references with ref_ptr
* Call before deleting
*/
void tcParticleEffect::PreDestroy()
{
    if (emitter.valid())
    {
        emitter->setParticleSystem(0);
    }

    if (program.valid())
    {
        program->setParticleSystem(0);
    }
   
    if (program.valid())
    {
		program->setParticleSystem(0);
    }

    if (updater.valid())
    {
	    updater->removeParticleSystem(this);
    }

    if (geode.valid())
    {
        geode->removeDrawable(this);
    }
}

tcParticleEffect::tcParticleEffect(int smokeModeCode)
: root(0), smokeMode(smokeModeCode)
{
	if ((smokeModeCode == MISSILE) || (smokeModeCode == AFTERBURNER))
	{
		osgParticle::SmokeTrailEmitter* smokeTrailEmitter = 
			new osgParticle::SmokeTrailEmitter;
		emitter = smokeTrailEmitter;

		smokeTrailEmitter->setParticleSystem(this);

		particlePlacer = new osgParticle::tcParticlePlacer;
		particlePlacer->setCenter(0, 0, 0);
		smokeTrailEmitter->setPlacer(particlePlacer);
		smokeTrailEmitter->setReferenceFrame(osgParticle::Emitter::ABSOLUTE_RF);

		program = new osgParticle::ModularProgram;
		program->setParticleSystem(this);

		// create an operator that simulates the gravity acceleration.
		accelOp = new osgParticle::AccelOperator;
		program->addOperator(accelOp.get());
	}
	//else if (smokeModeCode == BUBBLES)
    //{
   // }
    else
	{
		osgParticle::ModularEmitter* modularEmitter = new osgParticle::ModularEmitter;
		emitter = modularEmitter;

		modularEmitter->setParticleSystem(this);

		counter = new osgParticle::RandomRateCounter;

		modularEmitter->setCounter(counter.get());

		particlePlacer = new osgParticle::tcParticlePlacer;
		particlePlacer->setCenter(0, 0, 0);

		modularEmitter->setPlacer(particlePlacer);
		modularEmitter->setReferenceFrame(osgParticle::Emitter::ABSOLUTE_RF);

		shooter = new osgParticle::RadialShooter;

		modularEmitter->setShooter(shooter.get());


		program = new osgParticle::ModularProgram;
		program->setParticleSystem(this);

		// create an operator that simulates the gravity acceleration.
		accelOp = new osgParticle::AccelOperator;
		program->addOperator(accelOp.get());

	}

    ConfigureForMode();

	// create a Geode to contain the particle system.
	geode = new osg::Geode;
	geode->addDrawable(this);

    updater = new osgParticle::ParticleSystemUpdater;
	updater->addParticleSystem(this);
}

tcParticleEffect::~tcParticleEffect()
{
    if (root) DetachFromSceneGraph();
}

