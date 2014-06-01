/** 
**  @file tcSmoker.cpp 
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

#include "tcSmoker.h"
#include "tcGameObject.h"
#include "tcParticleEffect.h"
#include "tcParticlePlacer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



tcSmokeTrail& tcSmokeTrail::operator= (const tcSmokeTrail& rhs)
{
    smokeEffect = rhs.smokeEffect;
    smokePlacer = rhs.smokePlacer;
    smokeSource = rhs.smokeSource;

    return *this;
}

tcSmokeTrail::tcSmokeTrail()
{
}

tcSmokeTrail::tcSmokeTrail(const tcSmokeTrail& source)
{
    smokeEffect = source.smokeEffect;
    smokePlacer = source.smokePlacer;
    smokeSource = source.smokeSource;
}

tcSmokeTrail::~tcSmokeTrail()
{
}


osg::ref_ptr<osg::Group> tcSmoker::world;

/** 
* Static method to set common world frame to all tcSmoker objects
*/
void tcSmoker::SetWorldFrame(osg::Group* worldFrame)
{
    world = worldFrame;
}

/**
*
*/
void tcSmoker::AddSmokeTrail(const osg::Vec3& smokeSource, int smokeMode)
{
    osg::ref_ptr<tcSmokeTrail> trail = new tcSmokeTrail;

    trail->smokeEffect = new tcParticleEffect(smokeMode);
    trail->smokeEffect->AddToSceneGraph(world.get());
    trail->smokePlacer = trail->smokeEffect->GetParticlePlacer();
    trail->smokeSource = smokeSource;

    smokeTrails.push_back(trail);
}

/**
*
*/
void tcSmoker::DeleteTrails()
{
    size_t nSmoke = smokeTrails.size();
    for (size_t n=0; n<nSmoke; n++)
    {
        //smokeTrails[n]->smokeEffect->DetachFromSceneGraph();
        smokeTrails[n]->smokeEffect->PreDestroy();
//        delete smokeTrails[n]->smokeEffect.release(); // necessary?
//        delete smokeTrails[n]->smokePlacer.release();
//        delete smokeTrails[n].release();

    }
    smokeTrails.clear();
}


/**
*
*/
bool tcSmoker::IsEnabled() const
{
    return smokeTrails.size() != 0;
}

/**
*
*/
void tcSmoker::SetGameObject(tcGameObject* obj)
{
    gameObj = obj;
}

/**
*
*/
void tcSmoker::UpdateSmokePosition(float x, float y, float z)
{
    // create rotation matrix (using euler angles for now)
    const osg::Vec3 xaxis(-1, 0, 0);
    const osg::Vec3 yaxis(0, -1, 0);
    const osg::Vec3 zaxis(0, 0, 1);

    osg::Vec3 pos(x, y, z);

    // heading, pitch, roll
    osg::Matrixf rotation;

	if (gameObj)
	{
		rotation.makeRotate(gameObj->mcKin.mfHeading_rad, zaxis,
                             gameObj->mcKin.mfPitch_rad, xaxis,
                             gameObj->mcKin.mfRoll_rad, yaxis);
	}
	else
	{
		rotation.makeRotate(0, zaxis, 0, xaxis, 0, yaxis);
	}

    size_t nSmoke = smokeTrails.size();
    for (size_t n=0; n<nSmoke; n++)
    {
        wxASSERT(smokeTrails[n]->smokePlacer.valid());
        if (!smokeTrails[n]->smokePlacer.valid()) return;

        osg::Vec3 smokeOffset = rotation * smokeTrails[n]->smokeSource;
        osg::Vec3 offsetPos = pos + smokeOffset;
    
        smokeTrails[n]->smokePlacer->setCenter(offsetPos.x(), offsetPos.y(), offsetPos.z());
    }

}

/**
*
*/
tcSmoker::tcSmoker()
: gameObj(0)
{
}

/**
*
*/
tcSmoker::~tcSmoker()
{
    DeleteTrails();
}
