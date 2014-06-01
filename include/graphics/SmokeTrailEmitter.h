/* -*-c++-*- OpenSceneGraph - Copyright (C) 1998-2003 Robert Osfield 
 *
 * This library is open source and may be redistributed and/or modified under  
 * the terms of the OpenSceneGraph Public License (OSGPL) version 0.0 or 
 * (at your option) any later version.  The full license is in LICENSE file
 * included with this distribution, and on the openscenegraph.org website.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
 * OpenSceneGraph Public License for more details.
*/
//osgParticle - Copyright (C) 2002 Marco Jez

#ifndef OSGPARTICLE_SmokeTrailEmitter_
#define OSGPARTICLE_SmokeTrailEmitter_ 1

#include <osgParticle/Export>
#include <osgParticle/Emitter>
#include <osgParticle/Particle>
#include <osgParticle/RandomRateCounter>
#include <graphics/tcParticlePlacer.h>
#include <osgParticle/PointPlacer>
#include <osgParticle/Shooter>
#include <osgParticle/RadialShooter>
#include <osgParticle/ParticleSystem>

#include <osg/ref_ptr>
#include <osg/CopyOp>
#include <osg/Object>
#include <osg/Node>
#include <osg/NodeVisitor>

namespace osgParticle
{

    /**    An emitter class that holds three objects to control the creation of particles.
        These objects are a <I>counter</I>, a <I>placer</I> and a <I>shooter</I>.
        The counter controls the number of particles to be emitted at each frame; 
        the placer must initialize the particle's position vector, while the shooter initializes 
        its velocity vector.
        You can use the predefined counter/placer/shooter classes, or you can create your own.
    */
    class SmokeTrailEmitter: public Emitter 
	{
    public:
        SmokeTrailEmitter();
        SmokeTrailEmitter(const SmokeTrailEmitter &copy, const osg::CopyOp &copyop = osg::CopyOp::SHALLOW_COPY);
        
        META_Node(osgParticle,SmokeTrailEmitter);
              
        /// Get the tcParticlePlacer object.
        inline tcParticlePlacer *getPlacer();
        
        /// Get the const tcParticlePlacer object.        
        inline const tcParticlePlacer *getPlacer() const;
        
        /// Set the tcParticlePlacer object.
        inline void setPlacer(tcParticlePlacer *p);

    protected:
        virtual ~SmokeTrailEmitter() {}
        SmokeTrailEmitter &operator=(const SmokeTrailEmitter &) { return *this; }
        
        void emit(double dt);
        
    private:
        osg::ref_ptr<tcParticlePlacer> placer_;

		void InitializeStandardTemplate();

    };
    
    // INLINE FUNCTIONS

    inline tcParticlePlacer* SmokeTrailEmitter::getPlacer()
    {
        return placer_.get();
    }

    inline const tcParticlePlacer* SmokeTrailEmitter::getPlacer() const
    {
        return placer_.get();
    }

    inline void SmokeTrailEmitter::setPlacer(tcParticlePlacer *p)
    {
        placer_ = p;
    }


}

#endif
