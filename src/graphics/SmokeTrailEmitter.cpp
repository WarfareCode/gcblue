/**  
**  @file SmokeTrailEmitter.cpp
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
#endif

#include <graphics/SmokeTrailEmitter.h>
#include <osgParticle/Emitter>
#include "common/randfn.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif 

//#pragma warning (disable: 4273)  // inconsistent dll linkage

void osgParticle::SmokeTrailEmitter::InitializeStandardTemplate()
{
	Particle standardTemplate;

	standardTemplate.setLifeTime(2);		
	standardTemplate.setSizeRange(osgParticle::rangef(0.6f, 1.0f));
	standardTemplate.setAlphaRange(osgParticle::rangef(0.4f, 0.1f));
	standardTemplate.setColorRange(osgParticle::rangev4(
		osg::Vec4(0.5f, 0.5f, 0.5f, 0.5f), 
		osg::Vec4(0.7, 0.7f, 0.7f, 1.0f)));
	//standardTemplate.setRadius(0.1f);	
	standardTemplate.setMass(0.05f);	
	setParticleTemplate(standardTemplate);
}

osgParticle::SmokeTrailEmitter::SmokeTrailEmitter()
:    Emitter(),
    placer_(new tcParticlePlacer)
{
	InitializeStandardTemplate();
}
    
osgParticle::SmokeTrailEmitter::SmokeTrailEmitter(const SmokeTrailEmitter &copy, const osg::CopyOp &copyop)
:    Emitter(copy, copyop),
    placer_(static_cast<tcParticlePlacer*>(copyop(copy.placer_.get())))
{
	InitializeStandardTemplate();
}

void osgParticle::SmokeTrailEmitter::emit(double dt) 
{
	int nEmit = (dt > 0) ? 30 : 0;
	float inv_nEmit = (nEmit > 0) ? 1.0 / float(nEmit) : 1.0f;

	for (int i=0; i<nEmit; ++i)  
	{
		if (Particle* P = 
			getParticleSystem()->createParticle(&getParticleTemplate()))
		{
			float fractionalDistance = 0.2f + float(i) * inv_nEmit;
			placer_->placeAlongPath(P, fractionalDistance);

			float rand_val = randf(1.0f);
			P->setLifeTime(0.5f + 1.5 * rand_val);
			P->setRadius(0.5 + 0.25*rand_val);
		}

	}
}
