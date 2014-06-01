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

#ifndef _TCPARTICLEPLACER_H_
#define _TCPARTICLEPLACER_H_

#include <osgParticle/CenteredPlacer>
#include <osgParticle/Particle>

#include <osg/CopyOp>
#include <osg/Object>

namespace osgParticle
{

    /**    
	* A point-shaped particle placer.
    * This placer class uses the center point defined in its base class <CODE>CenteredPlacer</CODE>
    * to place there all incoming particles.
    */
    class tcParticlePlacer: public CenteredPlacer 
    {
    public:
        inline tcParticlePlacer();
        inline tcParticlePlacer(const tcParticlePlacer &copy, const osg::CopyOp &copyop = osg::CopyOp::SHALLOW_COPY);

        META_Object(osgParticle, tcParticlePlacer);
        
        /** Place a particle. 
            This method is called automatically by <CODE>ModularEmitter</CODE> and should not be called
            manually.
        */
		osg::Vec3 getControlPosition() const {return osg::Vec3(0, 0, 0);} // had to add to avoid error C2259

        inline void place(Particle *P) const;
		inline void placeAlongPath(Particle *P, float a) const;
		inline void setApplyJitter(bool applyJitter);
		inline void setCenter(float x, float y, float z);

    protected:
        osg::Vec3 previousCenter;
        osg::Vec3 previousCenter2; ///< center before previousCenter
		bool applyJitter_; ///< true to randomize placement of particle

        virtual ~tcParticlePlacer() {}
        tcParticlePlacer &operator=(const tcParticlePlacer &) { return *this; }        
    };

    // INLINE FUNCTIONS
    
    inline tcParticlePlacer::tcParticlePlacer()
    : CenteredPlacer(), 
      previousCenter(0, 0, 0),
      previousCenter2(0, 0, 0), 
      applyJitter_(false)
    {
    }
    
    inline tcParticlePlacer::tcParticlePlacer(const tcParticlePlacer &copy, const osg::CopyOp &copyop)
    : CenteredPlacer(copy, copyop)
    {
    }

    inline void tcParticlePlacer::place(Particle *P) const
    {
		float a;

		if (applyJitter_)
		{
			a = 1.1f * (float)rand() / (float)RAND_MAX;
		}
		else
		{
			a = 1.0;
		}
		float b = 1.0 - a;

		osg::Vec3 cen = getCenter();
		osg::Vec3 p(a*cen._v[0] + b*previousCenter2._v[0],
					a*cen._v[1] + b*previousCenter2._v[1],
					a*cen._v[2] + b*previousCenter2._v[2]);

        P->setPosition(p);
        /*
        osgParticle::rangef alphaRange = P->getAlphaRange();
        alphaRange.minimum = a;
        P->setAlphaRange(alphaRange);
        */
    }

	/**
	* Places particle along path between current time and last update position.
	* @param a fraction of distance traveled over last time step to place particle
	*/
    inline void tcParticlePlacer::placeAlongPath(Particle *P, float a) const
    {
		if (applyJitter_)
		{
			a = a + 0.05f * (float)rand() * 3.052e-5;
		}
		float b = 1.0 - a;

		osg::Vec3 cen = getCenter();
		osg::Vec3 p(b*cen._v[0] + a*previousCenter._v[0],
					b*cen._v[1] + a*previousCenter._v[1],
					b*cen._v[2] + a*previousCenter._v[2]);

        P->setPosition(p);
	}

	inline void tcParticlePlacer::setApplyJitter(bool applyJitter)
	{
		applyJitter_ = applyJitter;
	}


	inline void tcParticlePlacer::setCenter(float x, float y, float z)
	{
		const osg::Vec3& cen = getCenter();
		
		/* ignore and return if center hasn't changed
		** This avoids an invalid previousCenter when setCenter
		** is called more than once at the same time step
		*/
		float absDiff = abs(cen._v[0] - x) + 
			            abs(cen._v[1] - y) + 
						abs(cen._v[2] - z);
		if (absDiff < 0.01) return; 

        previousCenter2 = previousCenter;
		previousCenter = cen;
		CenteredPlacer::setCenter(x, y, z);



	}
}


#endif
