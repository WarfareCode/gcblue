/**  
**  @file ObjectUpdater.cpp
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

#include "stdwx.h"

#include "ObjectUpdater.h"
#include "tcGameObject.h"
#include "tc3DModel.h"
#include "tc3DViewer.h"
#include "tcSimState.h"
#include "tcOptions.h"
#include "tcSensorMap.h"
#include "tcGameObject.h"
#include "tcMatrix3.h"

#include "CTVMesh.h"
#include "CTVMathLibrary.h"

//#include "tcParticleEffect.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif 



tc3DViewer* ObjectUpdater::viewer = 0;
tcSimState* ObjectUpdater::simState = 0;
tcSensorMap* ObjectUpdater::sensorMap = 0;
float ObjectUpdater::distanceFromCamera = 0;

ObjectUpdater* ObjectUpdater::Get()
{
    static ObjectUpdater instance;

    return &instance;
}


float ObjectUpdater::GetLastDistanceFromCamera()
{
    return distanceFromCamera;
}

void ObjectUpdater::GetLocationParams(tcGameObject* gameObj, LocationParams& p)
{
	if (gameObj)
	{
		if (!gameObj->parent)
		{
			tcKinematics* kin = &gameObj->mcKin;
			p.yaw = kin->mfHeading_rad;
			p.pitch = kin->mfPitch_rad;
			p.roll = kin->mfRoll_rad;
			p.x = viewer->LonToX(kin->mfLon_rad);
			p.z = viewer->LatToY(kin->mfLat_rad);
			p.y = kin->mfAlt_m;
			p.isVisible = true;
		}
		else // child object
		{
            if (gameObj->rel_pos.isVisible)
            {           
                GeoPoint loc = gameObj->parent->RelPosToLatLonAlt(gameObj->rel_pos.dx, 
										   gameObj->rel_pos.dy, gameObj->rel_pos.dz);

                p.yaw = gameObj->rel_pos.yaw;
                p.pitch = gameObj->rel_pos.pitch;
                p.roll = gameObj->rel_pos.roll;
                p.x = viewer->LonToX(loc.mfLon_rad);
                p.z = viewer->LatToY(loc.mfLat_rad);
                p.y = loc.mfAlt_m;
                p.isVisible = true;
            }
            else
            {
                p.x = 0;
                p.y = 0;
                p.z = -50000.0f;
                p.isVisible = false;
            }
		}
	}
#if 0
	else if (sensorTrack)
	{
		// if object is close to camera, use predicted track for position
		if ((distanceFromCamera < 10e3) || (sensorTrack->IsBearingOnly()))
		{
			tcTrack predicted;
			sensorTrack->GetPrediction(predicted, tcSimState::Get()->GetTime());
			p.x = viewer->LonToX(predicted.mfLon_rad);
			p.z = viewer->LatToY(predicted.mfLat_rad);
			p.y = predicted.GetOrGuessAltitude();
			p.yaw = predicted.mfHeading_rad;
			p.pitch = predicted.mfClimbAngle_rad;
			p.roll = 0;
		}
		else
		{
			p.x = viewer->LonToX(sensorTrack->mfLon_rad);
			p.z = viewer->LatToY(sensorTrack->mfLat_rad);
			p.y = sensorTrack->GetOrGuessAltitude();
			p.yaw = sensorTrack->mfHeading_rad;
			p.pitch = 0;
			p.roll = 0;
		}

		p.isVisible = true;
	}
#endif
}

void ObjectUpdater::GetLocationParams(tcSensorMapTrack* sensorTrack, LocationParams& p)
{
    if (sensorTrack)
	{
        tc3DModel* model = sensorTrack->GetModel();
        float trackModelDistance = model->GetDistanceFromCamera();

		// if object is close to camera, use predicted track for position
		if ((trackModelDistance < 10e3) || (sensorTrack->IsBearingOnly()))
		{
			tcTrack predicted;
			sensorTrack->GetPrediction(predicted, tcSimState::Get()->GetTime());
			p.x = viewer->LonToX(predicted.mfLon_rad);
			p.z = viewer->LatToY(predicted.mfLat_rad);
			p.y = predicted.GetOrGuessAltitude();
			p.yaw = predicted.mfHeading_rad;
			p.pitch = predicted.mfClimbAngle_rad;
			p.roll = 0;
		}
		else
		{
			p.x = viewer->LonToX(sensorTrack->mfLon_rad);
			p.z = viewer->LatToY(sensorTrack->mfLat_rad);
			p.y = sensorTrack->GetOrGuessAltitude();
			p.yaw = sensorTrack->mfHeading_rad;
			p.pitch = 0;
			p.roll = 0;
		}

		p.isVisible = true;
	}
}


void ObjectUpdater::Update(tcGameObject* obj)
{
    distanceFromCamera = 99999.0f;

    if (obj == 0)
    {
        wxASSERT(false);
        return;
    }

    tc3DModel* model = obj->GetModel();

    if (viewer->GetDatabaseViewState())
    {
        model->Enable(false);
        return;
    }


    LocationParams p;
	GetLocationParams(obj, p);
    
	float& x = p.x;
	float& y = p.y;
	float& z = p.z;
	float& yaw = p.yaw;
	float& pitch = p.pitch;
	float& roll = p.roll;
	bool& isVisible = p.isVisible;

	model->SetGenericMode(tc3DModel::USE_TRUE_MODEL);

    //pitch = 0;
    //roll = 0.5*sin(obj->mfStatusTime);
    //yaw = 0; //0.5*sin(obj->mfStatusTime);


	// not correct for child objects
	Vec3 cameraDelta = Vec3(x,y,z) - viewer->GetCameraPosition();
    distanceFromCamera = cameraDelta.Length();
	model->SetDistanceFromCamera(distanceFromCamera);

    if (isVisible && (distanceFromCamera < 10000.0f))
    {
        model->Enable(true);

        tcMatrix3 R;
        R.SetYawPitchRoll(yaw, -pitch, -roll);

        if (obj->parent != 0)
        {
            tcMatrix3 Rp;
            Rp.SetYawPitchRoll(obj->parent->mcKin.mfHeading_rad, -obj->parent->mcKin.mfPitch_rad,
                -obj->parent->mcKin.mfRoll_rad);

            Rp.PreMultiply(R);
            R = Rp;
        }

        model->SetPosition(x, y, z);
        model->SetRotationMatrix(R);
    }
    else
    {
        model->Enable(false);
        return;
    }

    UpdateAnimations(obj);


}

void ObjectUpdater::Update(tcSensorMapTrack* sensorTrack)
{
    if (sensorTrack == 0)
    {
        wxASSERT(false);
        return;
    }

    tc3DModel* model = sensorTrack->GetModel();

    if (viewer->GetDatabaseViewState())
    {
        model->Enable(false);
        return;
    }


    LocationParams p;
	GetLocationParams(sensorTrack, p);
    
	float& x = p.x;
	float& y = p.y;
	float& z = p.z;
	float& yaw = p.yaw;
	float& pitch = p.pitch;
	float& roll = p.roll;
	bool& isVisible = p.isVisible;

	model->SetGenericMode(tc3DModel::USE_TRUE_MODEL);


	// not correct for child objects
	Vec3 cameraDelta = Vec3(x,y,z) - viewer->GetCameraPosition();
    distanceFromCamera = cameraDelta.Length();
	model->SetDistanceFromCamera(distanceFromCamera);

    if (isVisible && (distanceFromCamera < 10000.0f))
    {
        model->Enable(true);

        tcMatrix3 R;
        R.SetYawPitchRoll(yaw, -pitch, -roll);

        model->SetPosition(x, y, z);
        model->SetRotationMatrix(R);
    }
    else
    {
        model->Enable(false);
        return;
    }
}



void ObjectUpdater::UpdateAnimations(tcGameObject* obj)
{    
    tc3DModel* model = obj->GetModel();
    size_t nAnimations = model->animationInfo.size();
    if (nAnimations == 0) return;

	tcGameObject* gameObject = model->GetGameObj();

    wxASSERT(gameObject);

    // do not update animations if camera is beyond animation LOD distance
    if (distanceFromCamera > 1000.0f) return;


//    CTVMesh* mesh = model->GetMesh();

    for(size_t n=0;n<nAnimations;n++)
    {
        tcAnimationInfo& info = model->animationInfo[n];
        int isActive = (info.switchVariable) ? *info.switchVariable : true;
        if (info.bound && isActive)
        {
            double dt = viewer->GetGameTime();
            double theta = info.omega * dt; // change in angle

            // scale rotation rate by platform speed for propeller animation type
            if (info.animationType == 0)
            {
                /* for subs and surface ships change rate with speed (omega is radians per second per knot)
                ** aircraft including helos use a fixed rate (omega is radians per second)
                */
                if (gameObject->mcKin.mfSpeed_kts < 50.0f) //hack method, improve this to isolate ships and subs, some ptbs exceed 70kts.
                {
                    theta *= gameObject->mcKin.mfSpeed_kts;
                }
            }
            
            CTVMesh* subMesh = model->GetSubmodelMesh(info.childIdx);
            subMesh->SetRotation(theta*info.axis.x, theta*info.axis.y, theta*info.axis.z);

        }
    }
}

/**
* This version updates animations for models attached to sensor tracks
*/
void ObjectUpdater::UpdateTrackAnimations()
{
#if 0
	size_t nAnimations = model->animationInfo.size();
	if (nAnimations == 0) return;

	tcSensorMapTrack* track = model->GetSensorTrack();
	wxASSERT(track);

	// do not update animations if camera is beyond animation LOD distance
	//if (distanceFromCamera > 10000.0f) return;

	for(size_t n=0;n<nAnimations;n++)
	{
		tcAnimationInfo& info = model->animationInfo[n];

		if (info.bound)
		{
			osg::MatrixTransform *xform = info.transform;
			//osg::Matrix matrix = xform->getMatrix();
			double dt = viewer->GetGameTimeStep();
			double theta = info.omega * dt; // change in angle

			// scale rotation rate by platform speed for propeller animation type
			if (info.animationType == 0)
			{
				/* for subs and surface ships change rate with speed (omega is radians per second per knot)
				** aircraft including helos use a fixed rate (omega is radians per second)
				*/
				if (track->mfSpeed_kts < 50.0f)//hack method, improve this to isolate ships and subs, some ptbs exceed 70kts.
				{
					theta *= track->mfSpeed_kts ;
				}
			}

			xform->preMult(osg::Matrix::rotate(theta , info.axis));
		}
	}
#endif
}

/**
* Omits child (captive object) updates
*/
void ObjectUpdater::UpdateTrack()
{	
#if 0
	tcSensorMapTrack* track = model->GetSensorTrack();

	if (track == 0) 
	{
		fprintf(stderr, "ObjectUpdater::UpdateTrack - null sensorTrack\n");
		wxASSERT(false);
		return;
	}
		

    int genericMode = 0;

    // first case assumes track identification is never wrong (currently true)
	if (track->GetDatabaseId() != -1) genericMode = tc3DModel::USE_TRUE_MODEL;
    else if (track->IsSurface()) genericMode = tc3DModel::USE_SURFACE_GENERIC;
    else if (track->IsAir()) genericMode = tc3DModel::USE_AIR_GENERIC;
    else if (track->IsMissile()) genericMode = tc3DModel::USE_AIR_GENERIC;
    else genericMode = tc3DModel::USE_UNKNOWN_GENERIC;

    model->SetGenericMode(genericMode);


	tc3DModel::LocationParams p;
	model->GetLocationParams(p);
    
	float& x = p.x;
	float& y = p.y;
	float& z = p.z;
	float& yaw = p.yaw;
	float& pitch = p.pitch;
	float& roll = p.roll;
	bool& isVisible = p.isVisible;




    // not correct for child objects
    osg::Vec3 cameraDelta = osg::Vec3(x,y,z) - viewer->GetCameraPosition();
    distanceFromCamera = cameraDelta.length();
    model->SetDistanceFromCamera(distanceFromCamera);


    if ((model->IsSmokeEnabled())&&(track->IsMissile()))
    {
        model->UpdateSmokePosition(x, y, z);
    }

    // TODO make this more efficient
    osg::Matrix m =  
        osg::Matrix::rotate(osg::inRadians(roll),0.0f,1.0f,0.0f)*
        osg::Matrix::rotate(osg::inRadians(pitch),1.0f,0.0f,0.0f)*
        osg::Matrix::rotate(-osg::inRadians(yaw),0.0f,0.0f,1.0f)*osg::Matrix::translate(x,y,z)
        ;

    UpdaterCallbackVisitor cv(m);
    node->accept(cv);
#endif

}



void ObjectUpdater::UpdateTrue()
{
#if 0
	tc3DModel::LocationParams p;
	model->GetLocationParams(p);
    
	float& x = p.x;
	float& y = p.y;
	float& z = p.z;
	float& yaw = p.yaw;
	float& pitch = p.pitch;
	float& roll = p.roll;
	bool& isVisible = p.isVisible;

	model->SetGenericMode(tc3DModel::USE_TRUE_MODEL);


	// not correct for child objects
	osg::Vec3 cameraDelta = osg::Vec3(x,y,z) - viewer->GetCameraPosition();
	distanceFromCamera = cameraDelta.length();
	model->SetDistanceFromCamera(distanceFromCamera);

	if (!isVisible) 
	{
		model->SetGenericMode(tc3DModel::DISABLE_MODEL);
		return;
	}
	
	if (model->IsSmokeEnabled())
	{
		model->UpdateSmokePosition(x, y, z);
	}

	osg::Matrix m =  
		osg::Matrix::rotate(osg::inRadians(roll),0.0f,1.0f,0.0f)*
		osg::Matrix::rotate(osg::inRadians(pitch),1.0f,0.0f,0.0f)*
		osg::Matrix::rotate(-osg::inRadians(yaw),0.0f,0.0f,1.0f)*osg::Matrix::translate(x,y,z)
		;


	UpdaterCallbackVisitor cv(m);
	node->accept(cv);
#endif
}

#if 0
/**
* Main update method.
* Updates position and attitude of object
* Fix this so that the track-only mode does not require a game object to be 
* present.
*/
void ObjectUpdater::operator()(Node* node, NodeVisitor* nv)
{
    tcGameObject* gameObject = model->GetGameObj();
	tcSensorMapTrack* sensorTrack = model->GetSensorTrack();

	bool use3Dcheat = tcOptions::Get()->mn3DCheatMode == 3;
    bool isServer = simState->IsMultiplayerServer();


    if (gameObject)
    {        
		if (use3Dcheat || isServer || simState->mpUserInfo->IsOwnAlliance(gameObject->GetAlliance()))
		{
			UpdateTrue(node);
		}
		else
		{
			wxASSERT(false);
		}

		UpdateAnimations();

		// must call any nested node callbacks and continue subgraph traversal.
		NodeCallback::traverse(node,nv);
	}
	else if (sensorTrack)
	{
		UpdateTrack(node);
		UpdateTrackAnimations();

		// must call any nested node callbacks and continue subgraph traversal.
		NodeCallback::traverse(node,nv);
	}
	else // no game object available
	{
		fprintf(stderr, "Error - ObjectUpdater::operator() - called with null game obj\n");
	}

}
#endif


ObjectUpdater::ObjectUpdater()
{
	simState = tcSimState::Get();
	sensorMap = simState->GetSensorMap();

    wxASSERT(viewer != 0);
}

    
ObjectUpdater::~ObjectUpdater()
{
}

