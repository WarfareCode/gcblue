/** 
**  @file tcGameObject.cpp
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

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "tcGameObject.h"
#include "tcDatabase.h"
#include "tc3DModel.h"
#include "tcSimState.h"
#include "tcScenarioLogger.h"
#include "tcGoalTracker.h"
#include "common/tcStream.h"
#include "common/tcObjStream.h"
#include "tcGameStream.h"
#include "tcMatrix3.h"
#include "ObjectUpdater.h"
#include "CTVMesh.h"
#include "CTVMathLibrary.h"
#include "tcDamageModel.h"
#include "randfn.h."
#include "nsNav.h"
#include "tcFloatCompressor.h"
#include "tcScenarioRandomizer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/**
* Loads state from stream
*/
tcStream& tsRelativePosition::operator<<(tcStream& stream)
{   
    stream >> tcIntervalCompressor(dx, -1000.0f, 1000.0f);
    stream >> tcIntervalCompressor(dy, -1000.0f, 1000.0f);
    stream >> tcIntervalCompressor(dz, -1000.0f, 1000.0f);
    stream >> tcAngleCompressor(yaw);
    stream >> tcAngleCompressor(pitch);
    stream >> tcAngleCompressor(roll);
    stream >> isVisible;

    return stream;
}

/**
* Saves state to stream
*/
tcStream& tsRelativePosition::operator>>(tcStream& stream)
{    
    stream << tcIntervalCompressor(dx, -1000.0f, 1000.0f);
    stream << tcIntervalCompressor(dy, -1000.0f, 1000.0f);
    stream << tcIntervalCompressor(dz, -1000.0f, 1000.0f);
    stream << tcAngleCompressor(yaw);
    stream << tcAngleCompressor(pitch);
    stream << tcAngleCompressor(roll);
    stream << isVisible;

    return stream;
}



bool tcGameObject::clientMode = false;
bool tcGameObject::editMode = false;

tcMapData* tcGameObject::mapData = NULL;
database::tcDatabase* tcGameObject::database = NULL;
tcSimState* tcGameObject::simState = NULL;
long tcGameObject::hookedId = -1;
unsigned short tcGameObject::launchedCounter = 0;
bool tcGameObject::addTasksOnCreate = true;

std::string tcGameObject::lastDamageDescription;

void tcGameObject::SetLastDamageDescription(const std::string& s)
{
    lastDamageDescription = s;
}

const std::string& tcGameObject::GetLastDamageDescription()
{
    return lastDamageDescription;
}


void tcGameObject::SetInvulnerable(bool state)
{
    isInvulnerable = state;
}

void tcGameObject::SetAddTasksOnCreate(bool state)
{
	addTasksOnCreate = state;
}

/**
* Call to destroy object as name suggests
*/
void tcGameObject::SelfDestruct()
{
    float priorDamage = mfDamageLevel;
    mfDamageLevel = 1.0f;

    UpdateScoreForDamage(0, priorDamage);
}

/**
 *
 */
void tcGameObject::SetRelativePosition(float dx, float dy, float dz) 
{
    rel_pos.dx = dx; 
    rel_pos.dy = dy; 
    rel_pos.dz = dz;
}

/**
 *
 */
void tcGameObject::SetRelativeOrientation(float yaw, float pitch, float roll) 
{
    rel_pos.yaw = yaw; 
    rel_pos.pitch = pitch; 
    rel_pos.roll = roll;
}

/**
 *
 */
void tcGameObject::ClearChildren() 
{
    {
        size_t child_count = children.size();
        for (size_t i=0;i<child_count;i++) 
        {
            tcGameObject* child = children.at(i);
            if (child != 0) 
            {
                simState->UnregisterChildObject(child->GetName());
                delete child;
            }   
        }
        children.clear();
    }
    {
        size_t launch_count = toLaunch.size();
        for (size_t i=0;i<launch_count;i++) 
        {
            tcGameObject* gameObj = toLaunch.at(i);
            if (gameObj != 0) 
            {
                delete gameObj;
            }   
        }
        toLaunch.clear();
    }
}

/**
* Gets relative model coordinates of obj relative to this GameObject
* Modified to new coord system: dx right, dy up, dz forward
* Old system: dx right, dy forward, dz up
*
* @param rel_pos Relative position structure to store results in.
*/
void tcGameObject::GetRelPosOf(tcGameObject *obj, tsRelativePosition& rel_pos)
{
    rel_pos.pitch = 0;
    rel_pos.roll = 0;
    rel_pos.yaw = 0;
    rel_pos.dy = obj->mcKin.mfAlt_m - mcKin.mfAlt_m;

    double delta_lat = obj->mcKin.mfLat_rad - mcKin.mfLat_rad;
    double delta_lon = obj->mcKin.mfLon_rad - mcKin.mfLon_rad;
    delta_lon = delta_lon*cosf((float)mcKin.mfLat_rad); // correct for latitude
    float delta_lat_m = (float)(delta_lat*C_RADTOM);
    float delta_lon_m = (float)(delta_lon*C_RADTOM);

    float hdg = mcKin.mfHeading_rad;
    float cos_hdg = cosf(hdg);
    float sin_hdg = sinf(hdg);
    float dx = cos_hdg*delta_lon_m - sin_hdg*delta_lat_m;
    float dz = cos_hdg*delta_lat_m + sin_hdg*delta_lon_m;

    rel_pos.dx = dx;
    rel_pos.dz = dz;
}


/**
* Gets relative position and velocity of obj relative to this GameObject
* dx east, dz north, dy up
* 
* Results are in the local world frame of reference
*/
void tcGameObject::GetRelativeStateWorld(tcGameObject *obj, Vec3& position, Vec3& velocity)
{
	// local world coordinates, x--east, y--up, z--north

	// store relative position in local world frame
	position.y =  obj->mcKin.mfAlt_m - mcKin.mfAlt_m;

    double delta_lat = obj->mcKin.mfLat_rad - mcKin.mfLat_rad;
    double delta_lon = obj->mcKin.mfLon_rad - mcKin.mfLon_rad;
    delta_lon = delta_lon*cosf((float)mcKin.mfLat_rad); // correct for latitude
    position.z = (float)(delta_lat*C_RADTOM);
    position.x = (float)(delta_lon*C_RADTOM);


	Vec3 v1 = GetWorldVelocity();
	Vec3 v2 = obj->GetWorldVelocity();

	velocity = v2 - v1; // relative velocity in local world frame
}


/**
* Gets relative position and velocity of obj relative to this GameObject
* dx right, dy up, dz forward
* 
* Results are in the frame of reference of this object
*/
void tcGameObject::GetRelativeStateLocal(tcGameObject *obj, Vec3& position, Vec3& velocity)
{
    // relative world coordinates, x--east, y--up, z--north
	GetRelativeStateWorld(obj, position, velocity);

	//osg::Matrix world_to_obj = 
	//	osg::Matrix::rotate(osg::inRadians(mcKin.mfYaw_rad),0.0f,0.0f,1.0f)*
	//	osg::Matrix::rotate(-osg::inRadians(mcKin.mfPitch_rad),1.0f,0.0f,0.0f)*
	//	osg::Matrix::rotate(-osg::inRadians(mcKin.mfRoll_rad),0.0f,1.0f,0.0f);

	//position = world_to_obj.preMult(position);
	//velocity = world_to_obj.preMult(velocity);
 


    tcMatrix3 world_to_body;
    world_to_body.SetInverseYawPitchRoll(mcKin.mfYaw_rad, -mcKin.mfPitch_rad, -mcKin.mfRoll_rad);

    position = world_to_body * position;
    velocity = world_to_body * velocity;
}

/**
* Convert coordinates in model frame of reference to local world frame.
* Would be faster to use saved transform matrix from ObjectUpdater
* instead of recalculating it here.
*
* @return x--east, y--up, z--north
*/
Vec3 tcGameObject::ConvertModelCoordinatesToWorld(const Vec3& x) const
{
    tcMatrix3 body_to_world;
    body_to_world.SetYawPitchRoll(mcKin.mfYaw_rad, mcKin.mfPitch_rad, mcKin.mfRoll_rad);

    Vec3 temp(x);
	return body_to_world * temp;
}



/**
* @return velocity in local world coords in m/s
* x--east, y--up, z--north
*/
Vec3 tcGameObject::GetWorldVelocity() const
{
	float hdg = mcKin.mfHeading_rad;
	float climb = mcKin.mfClimbAngle_rad;

	float speed_mps = C_KTSTOMPS * mcKin.mfSpeed_kts;
    float cos_hdg = cosf(hdg);
    float sin_hdg = sinf(hdg);
	float cos_climb = cosf(climb);
	float sin_climb = sinf(climb);

	float vxy = cos_climb * speed_mps;

	float vy = sin_climb * speed_mps;
	float vz = cos_hdg * vxy;
	float vx = sin_hdg * vxy;

	return Vec3(vx, vy, vz);
}


/**
* @returns sonar source level of object or, if object has active sonar on, maximum of source level of 
* target and max active sonar source level.
* @param az_deg aspect angle with respect to target heading
*/
float tcGameObject::GetSonarSourceLevel(float az_deg) const
{
    return -999.0f;	
}

/**
* @return optical cross-section of object in dBsm as viewed from the air
*/
float tcGameObject::GetOpticalCrossSection() const
{
    return -999.0f;	
}

/**
* @return optical cross-section of object in dBsm as viewed from the air
*/
float tcGameObject::GetOpticalCrossSection(float view_alt_m, float view_dist_km) const
{
    return -999.0f;	
}


/**
* @return IR signature of object in relative dB as viewed from the air
*/
float tcGameObject::GetIRSignature(float az_deg) const
{
    return -999.0f;	
}


/**
* Uses 3D model for size info (diameter of bounding sphere)
* @return largest dimension of object in meters or 0 if no model available
*/
float tcGameObject::GetSpan() const
{
	if (model)
	{
		return 2.0f*model->GetRadius();
	}
	else
	{
		return 0;
	}
}

bool tcGameObject::IsDestroyed()
{
    return (mfDamageLevel >= 1.0f);
}


/**
* Used to decide when to display info messages and play sound
* effects.
* @return true if object is hooked by user
*/
bool tcGameObject::IsHooked() const
{
    return (mnID == hookedId) && (mnID != -1);
}

bool tcGameObject::IsInvulnerable() const
{
    return isInvulnerable;
}

/**
* Used to decide when to display info messages and play sound
* effects.
* @return true if object is under user control
*/
bool tcGameObject::IsOwnAlliance() const
{
    return simState->mpUserInfo->IsOwnAlliance(GetAlliance());
}

/**
* To avoid dynamic_cast for testing if tcPlatformObject
*/
bool tcGameObject::IsPlatformObject() const
{
    return false;
}

void tcGameObject::LaunchFrom(tcGameObject* obj, unsigned nLauncher)
{
	wxASSERT(false); //this should be overridden in derived class
}

GeoPoint tcGameObject::RelPosToLatLonAlt(const tsRelativePosition& rel_pos) const
{
	return RelPosToLatLonAlt(rel_pos.dx, rel_pos.dy, rel_pos.dz);
}

/**
* Modified to new coord system: dx right, dy up, dz forward
* Old system: dx right, dy forward, dz up
*/
GeoPoint tcGameObject::RelPosToLatLonAlt(const float& dx, 
										   const float& dy, const float& dz) const
{
	GeoPoint p;

    tcMatrix3 R;
    R.SetYawPitchRoll(mcKin.mfHeading_rad, -mcKin.mfPitch_rad, -mcKin.mfRoll_rad);

    Vec3 xyz(dx, dy, dz);
    Vec3 xyz_rot = R * xyz;

	p.mfAlt_m = mcKin.mfAlt_m + xyz_rot.y;

	p.mfLon_rad = mcKin.mfLon_rad + (C_MTORAD / cosf((float)mcKin.mfLat_rad)) * xyz_rot.x;

    p.mfLat_rad = mcKin.mfLat_rad + C_MTORAD * xyz_rot.z;

 //   float hdg = mcKin.mfHeading_rad;
 //   float cos_hdg = cosf(hdg);
 //   float sin_hdg = sinf(hdg);

	//p.mfAlt_m = mcKin.mfAlt_m + dy;
	//p.mfLon_rad = (C_MTORAD / cosf((float)mcKin.mfLat_rad)) * 
	//	(cos_hdg * dx + sin_hdg * dz) + mcKin.mfLon_rad;
	//p.mfLat_rad = C_MTORAD * (cos_hdg * dz - sin_hdg * dx) + mcKin.mfLat_rad;

	return p;
}

/**
* Calculates collision point or closest point of approach in model coordinates
* @return true if collision occurs, false otherwise
* @param distance_m range to collision in meters
*/
bool tcGameObject::CalculateCollisionPoint(tcGameObject* collider, Vec3& pos, float& dt, float& distance_m)
{
	Vec3 x_collider; // position of collider in model frame
	Vec3 v_collider; // velocity of collider in model frame

	GetRelativeStateLocal(collider, x_collider, v_collider);

    float speed_mps = v_collider.Length();

    distance_m = 9999.0f;

    Vec3 vdir = v_collider / speed_mps;

    // construct segment +/- 100 m from current point
	Vec3 x2_collider = x_collider + vdir * 100.0f; 
    Vec3 x1_collider = x_collider - vdir * 100.0f;

    CTVMesh* mesh = GetDatabaseMesh(); // use database mesh, because obj mesh seems to be affected by rendering
    if (mesh == 0)
    {
        wxASSERT(false);
        return false;
    }

    //Vec3 bbMin, bbMax;
    //mesh->GetBoundingBox(&bbMin, &bbMax, true);
    //mesh->ComputeBoundings();

    // probably unnecessary to allocate an array, but just in case check if second
    cTV_COLLISIONRESULT collisionInfo[2]; 
    collisionInfo[1].bHasCollided = true;

    mesh->AdvancedCollision(&x1_collider, &x2_collider, collisionInfo, cTV_TESTTYPE_BOUNDINGBOX);//cTV_TESTTYPE_ACCURATETESTING);

    wxASSERT(collisionInfo[1].bHasCollided == true);

    if (!collisionInfo[0].bHasCollided) return false;

    pos = collisionInfo[0].vCollisionImpact;
    
    Vec3 dx = (pos - x_collider);

    distance_m = (pos - x_collider).Length();
    dt = distance_m / speed_mps;

    if (dx.Dot(v_collider) < 0)
    {
        dt = -dt;
    }

    return true;

}

/**
* Calculates collision point along specified direction in model coordinates
* @return true if collision occurs, false otherwise
* @param distance_m range to collision in meters
* @param dir direction vector in local coords to check for collision
*/
bool tcGameObject::CalculateCollisionPointDir(tcGameObject* collider, const Vec3& dir, Vec3& pos, float& distance_m)
{
	Vec3 x_collider; // position of collider in model frame
	Vec3 v_collider; // velocity of collider in model frame

	GetRelativeStateLocal(collider, x_collider, v_collider);

    distance_m = 9999.0f;

    Vec3 vdir = dir;

    // construct segment +/- 100 m from current point
	Vec3 x2_collider = x_collider + vdir * 100.0f; 
    Vec3 x1_collider = x_collider - vdir * 100.0f;

    CTVMesh* mesh = GetDatabaseMesh(); // use database mesh, because obj mesh seems to be affected by rendering
    if (mesh == 0)
    {
        wxASSERT(false);
        return false;
    }

    // probably unnecessary to allocate an array, but just in case check if second
    cTV_COLLISIONRESULT collisionInfo[2]; 
    collisionInfo[1].bHasCollided = true;

    mesh->AdvancedCollision(&x1_collider, &x2_collider, collisionInfo, cTV_TESTTYPE_BOUNDINGBOX);//cTV_TESTTYPE_ACCURATETESTING);

    wxASSERT(collisionInfo[1].bHasCollided == true);

    if (!collisionInfo[0].bHasCollided) return false;

    pos = collisionInfo[0].vCollisionImpact;
    
    distance_m = (pos - x_collider).Length();

    return true;

}

/**
* Calculates collision point along ray to model origin
* @return true if collision occurs, false otherwise
* @param distance_m range to collision in meters
* @param dir direction vector in local coords to check for collision
*/
bool tcGameObject::CalculateCollisionPointOrigin(tcGameObject* collider, Vec3& pos, float& distance_m)
{
	Vec3 x_collider; // position of collider in model frame
	Vec3 v_collider; // velocity of collider in model frame

	GetRelativeStateLocal(collider, x_collider, v_collider);

    distance_m = 9999.0f;

	Vec3 x2_collider(0, 0, 0);
    Vec3 x1_collider = x_collider;

    CTVMesh* mesh = GetDatabaseMesh(); // use database mesh, because obj mesh seems to be affected by rendering
    if (mesh == 0)
    {
        wxASSERT(false);
        return false;
    }

    // probably unnecessary to allocate an array, but just in case check if second
    cTV_COLLISIONRESULT collisionInfo[2]; 
    collisionInfo[1].bHasCollided = true;

    mesh->AdvancedCollision(&x1_collider, &x2_collider, collisionInfo, cTV_TESTTYPE_BOUNDINGBOX);//cTV_TESTTYPE_ACCURATETESTING);

    wxASSERT(collisionInfo[1].bHasCollided == true);

    if (!collisionInfo[0].bHasCollided) return false;

    pos = collisionInfo[0].vCollisionImpact;
    
    distance_m = (pos - x_collider).Length();

    return true;

}



/**
* Calculates collision point in model coordinates from arbitrary start point
* @return true if collision occurs, false otherwise
* @param start_enu east-up-north offset of start pos relative to this unit
* @param dir_enu EUN direction vector of ray from start pos
* @param distance distance in meters to collision point if collision occurs
*/
bool tcGameObject::CalculateCollisionPointArb(const Vec3& start_eun, const Vec3& dir_eun, Vec3& pos, float& distance)
{
    Vec3 x_collider = start_eun;
    Vec3 v_collider = dir_eun; // assume dir_enu is unit vector


    tcMatrix3 world_to_body;
    world_to_body.SetInverseYawPitchRoll(mcKin.mfYaw_rad, -mcKin.mfPitch_rad, -mcKin.mfRoll_rad);

    x_collider = world_to_body * x_collider;
    v_collider = world_to_body * v_collider;



    Vec3 x2_collider = x_collider + v_collider * 1000.0f;

    CTVMesh* mesh = GetDatabaseMesh(); // use database mesh, because obj mesh seems to be affected by rendering
    if (mesh == 0)
    {
        wxASSERT(false);
        return false;
    }


    // probably unnecessary to allocate an array, but just in case check if second
    cTV_COLLISIONRESULT collisionInfo[2]; 
    collisionInfo[1].bHasCollided = true;

    mesh->AdvancedCollision(&x_collider, &x2_collider, collisionInfo, cTV_TESTTYPE_ACCURATETESTING);

    wxASSERT(collisionInfo[1].bHasCollided == true);

    if (!collisionInfo[0].bHasCollided) return false;

    pos = collisionInfo[0].vCollisionImpact;
    distance = collisionInfo[0].fDistance;
    return true;
}

/**
* @return cross-section in square meters as observed from point in dir_eun
*/
float tcGameObject::CalculateCrossSectionDir(const Vec3& dir_eun)
{

    CTVMesh* mesh = GetDatabaseMesh(); // use database mesh, because obj mesh seems to be affected by rendering
    if (mesh == 0)
    {
        wxASSERT(false);
        return false;
    }

    Vec3 pmin;
    Vec3 pmax;
    mesh->GetBoundingBox(&pmin, &pmax, false);

    Vec3 kdir = dir_eun;
    tcMatrix3 world_to_body;
    world_to_body.SetInverseYawPitchRoll(mcKin.mfYaw_rad, -mcKin.mfPitch_rad, -mcKin.mfRoll_rad);
    kdir = world_to_body * kdir; // now in body coords
    kdir = kdir / kdir.Length();

    // define axes in cross-section plane, perpendicular to dir vector
    CTVMathLibrary math;
    Vec3 udir;
    Vec3 vdir;
    if ((kdir.x != 0) || (kdir.z != 0))
    {
        Vec3 up(0, 1.0f, 0);
        udir = kdir.Cross(up);
        udir = udir / udir.Length();
        
        vdir = kdir.Cross(udir);
        vdir = vdir / vdir.Length();
    }
    else
    {
        udir.set(1.0f, 0, 0);
        vdir.set(0, 0, 1.0f);
    }
    
    Vec2 pxy[8];
    Vec3 v;

    v.set(pmin.x, pmin.y, pmin.z);
    pxy[0].x = udir.Dot(v);
    pxy[0].y = vdir.Dot(v);
    
    v.set(pmin.x, pmin.y, pmax.z);
    pxy[1].x = udir.Dot(v);
    pxy[1].y = vdir.Dot(v);

    v.set(pmin.x, pmax.y, pmin.z);
    pxy[2].x = udir.Dot(v);
    pxy[2].y = vdir.Dot(v);
    
    v.set(pmin.x, pmax.y, pmax.z);
    pxy[3].x = udir.Dot(v);
    pxy[3].y = vdir.Dot(v);

    v.set(pmax.x, pmin.y, pmin.z);
    pxy[4].x = udir.Dot(v);
    pxy[4].y = vdir.Dot(v);
    
    v.set(pmax.x, pmin.y, pmax.z);
    pxy[5].x = udir.Dot(v);
    pxy[5].y = vdir.Dot(v);

    v.set(pmax.x, pmax.y, pmin.z);
    pxy[6].x = udir.Dot(v);
    pxy[6].y = vdir.Dot(v);
    
    v.set(pmax.x, pmax.y, pmax.z);
    pxy[7].x = udir.Dot(v);
    pxy[7].y = vdir.Dot(v);

    float umin = 99999.9f;
    float umax = -99999.9f;
    float vmin = 99999.9f;
    float vmax = -99999.9f;
    for (unsigned k=0; k<8; k++)
    {
        umin = std::min(umin, pxy[k].x);
        umax = std::max(umax, pxy[k].x);
        vmin = std::min(vmin, pxy[k].y);
        vmax = std::max(vmax, pxy[k].y);
    }


    float uv_hull_area = (umax-umin)*(vmax-vmin); // cross-section based on extrema of u and v

    if (tcOptions::Get()->accurateCrossSection == 0)
    {
        return 0.3f * uv_hull_area;
    }

    float du = 0.125*(umax-umin);
    float dv = 0.125*(vmax-vmin);

    Vec3 x1_collider = kdir * 1000.0f;
    Vec3 x2_collider = kdir * -1000.0f;
    unsigned int hits = 0;

    for (float u=0.5*du+umin; u<umax; u+=du)
    {
        for (float v=0.5*dv+vmin; v<vmax; v+=dv)
        {
            cTV_COLLISIONRESULT collisionInfo[2]; 
            collisionInfo[1].bHasCollided = true;

            Vec3 uv_offset = udir*u + vdir*v;
            Vec3 x1 = x1_collider + uv_offset;
            Vec3 x2 = x2_collider + uv_offset;

            mesh->AdvancedCollision(&x1, &x2, collisionInfo, cTV_TESTTYPE_ACCURATETESTING);

            wxASSERT(collisionInfo[1].bHasCollided == true);

            if (collisionInfo[0].bHasCollided) hits++;

        }
    }

    wxASSERT(hits <= 64);
    
    const float den = 1.0f / 64.0f;
    float scaledArea_m2 = uv_hull_area * float(hits) * den;

    return scaledArea_m2;

    //

    //Vec3 x_collider = start_eun;
    //Vec3 v_collider = dir_eun; // assume dir_enu is unit vector


   
    //v_collider = world_to_body * v_collider;
}


/**
* @return number of random hits
*/
unsigned int tcGameObject::CalculateRandomHits(const Vec3& pos_eun, const Vec3& dir_eun, float rangeOffset_m, float error_rad, unsigned int nRays)
{

    CTVMesh* mesh = GetDatabaseMesh(); // use database mesh, because obj mesh seems to be affected by rendering
    if (mesh == 0)
    {
        wxASSERT(false);
        return false;
    }

    Vec3 kdir = dir_eun;
    tcMatrix3 world_to_body;
    world_to_body.SetInverseYawPitchRoll(mcKin.mfYaw_rad, -mcKin.mfPitch_rad, -mcKin.mfRoll_rad);

    kdir = world_to_body * kdir; // principal direction vector in body coords
    kdir = kdir / kdir.Length();

    Vec3 pos = pos_eun;
    pos = world_to_body * pos; // start pos in body coords

    pos = pos - kdir * rangeOffset_m; // apply range offset (move start point back to launch point)

    CTVMathLibrary math; 
    cTV_3DMATRIX rot;
    unsigned int hits = 0;

    enum cCONST_TV_TESTTYPE collisionTest = (tcOptions::Get()->accurateCrossSection == 1) ?
        cTV_TESTTYPE_ACCURATETESTING : cTV_TESTTYPE_BOUNDINGBOX;

    for (unsigned int ray=0; ray<nRays; ray++)
    {
        Vec3 axis(randfc(1.0f), randfc(1.0f), randfc(1.0f));
        axis = axis - (kdir * kdir.Dot(axis));
        axis = axis / axis.Length();
        //float res = axis.Dot(kdir);

        float angle_rad = error_rad * GaussianRandom::Get()->randn_fast();
       
        math.TVMatrixRotationAxis(&rot, &axis, angle_rad);

        Vec3 kdir_err;
        math.TVVec3TransformCoord(&kdir_err, &kdir, &rot);
        

        cTV_COLLISIONRESULT collisionInfo; 

        Vec3 x2 = pos + kdir_err * (rangeOffset_m + 1000.0f);

        mesh->AdvancedCollision(&pos, &x2, &collisionInfo, collisionTest);


        if (collisionInfo.bHasCollided) hits++;
    }




    return hits;
}


/**
 *
 */
void tcGameObject::Clear()
{
    parent = NULL;
    ClearChildren();

    mzClass = "NONE";
    mzUnit = "NONE";
    SetAlliance(0);
    mfStatusTime = 0;
    mcKin.Clear();    
    mcTerrain.Clear();
    mfDamageLevel = 0;       
    mpDBObject = NULL;
    model = NULL;

    toLaunch.clear();
    targeters.clear();
}

/**
* @return range in km not considering altitude difference
*/
float tcGameObject::RangeTo(const tcGameObject& p) const
{
    return mcKin.RangeToKm(p.mcKin);
}

/**
 *
 */
void tcGameObject::AddChild(tcGameObject *child)
{
    child->mnID = nextChildId++; // id of child is index within children vect
    child->parent = this;
    children.push_back(child);

    simState->RegisterChildObject(child->GetName(), this);
}

/**
* Version that forces id and does not increment nextChildId
*/
void tcGameObject::AddChildWithId(tcGameObject *child, long id_)
{
    child->mnID = id_;
    child->parent = this;
    children.push_back(child);

    simState->RegisterChildObject(child->GetName(), this);
}

void tcGameObject::AddTargeter(long id)
{
    // clumsy, but targeter removal is very sketchy
    // do garbage collect if targeters size gets too big
    if (targeters.size() > 10) CleanupTargeters();

    bool isNew = true;
    for (size_t n=0; n<targeters.size(); n++)
    {
        if (targeters[n] == id) isNew = false;
    }

    if (isNew)
    {
        targeters.push_back(id);
    }
}

/**
* @return pointer to child with matching id, or 0 if not found
*/
tcGameObject* tcGameObject::GetChildById(long id) const
{
    size_t nChildren = children.size();
	for (size_t n=0; n<nChildren; n++)
	{
		if (children[n]->mnID == id)
		{
            return children[n];
		}
	}    
	
	return 0;
}

/**
* Linear search for child with matching name
*/
tcGameObject* tcGameObject::GetChildByName(const std::string& name) const
{
    size_t nChildren = children.size();
	for (size_t n=0; n<nChildren; n++)
	{
        if (name == children[n]->mzUnit.c_str())
		{
            return children[n];
		}
	}    
	
	return 0;
}


tcGameObject* tcGameObject::GetChild(size_t idx)
{
    if (idx < children.size())
    {
        return children[idx];
    }
    else
    {
        return 0;
    }
}

tc3DModel* tcGameObject::GetModel()
{
    return model;
}

const char* tcGameObject::GetName() const
{
    return mzUnit.c_str();
}

size_t tcGameObject::GetNumberOfChildren() const
{
    return children.size();
}

/**
* @return a random point on exterior of model in model
* coordinates by colliding ray with random direction
*/
Vec3 tcGameObject::GetRandomExteriorPoint()
{
    static Vec3 errorVal(0, 0, 0);


    const float r = 5000.0f;
    float az_rad = C_TWOPI * randf();
    float el_rad = C_PI * randfc(1.0f);
    float z = r*sinf(el_rad);
    float xy = r*cosf(el_rad);
    float x = xy*sinf(az_rad);
    float y = xy*cosf(az_rad);

    Vec3 xstart(x, y, z);
	Vec3 origin(0, 0, 0);


    CTVMesh* mesh = GetDatabaseMesh(); // use database mesh, because obj mesh seems to be affected by rendering
    if (mesh == 0)
    {
        fprintf(stderr, "tcGameObject::GetRandomExteriorPoint() - NULL mesh error\n");
        wxASSERT(false);
        return errorVal;
    }

    // probably unnecessary to allocate an array, but just in case check if second
    cTV_COLLISIONRESULT collisionInfo[8]; 
    collisionInfo[1].bHasCollided = true;

    mesh->AdvancedCollision(&xstart, &origin, collisionInfo, cTV_TESTTYPE_ACCURATETESTING);

    wxASSERT(collisionInfo[1].bHasCollided == true);

    if (collisionInfo[0].bHasCollided)
    {
        Vec3 pos = collisionInfo[0].vCollisionImpact;
        return pos;
    }
    else
    {
        fprintf(stderr, "tcGameObject::GetRandomExteriorPoint() - collision fail error (library problem?), using origin as default\n");
        return errorVal;
    }

}


/**
* @return the maximum vertical coordinate of the 3D model for this object
* Useful for estimating radar antenna height and effective height for radar horizon
*/
float tcGameObject::GetZmax()
{
    return model->GetBoundingBox().ymax();
}

/**
* @return the maximum vertical coordinate of the 3D model for this object
* Useful for estimating radar antenna height and effective height for radar horizon
* Workaround for const-ness requirements
*/
float tcGameObject::GetZmaxConst() const
{
    return std::max(model->GetBoundingBoxConst().ymax(), 3.0f);
}

/**
* @return the minimum vertical coordinate of the 3D model for this object
* Useful for estimating keel depth of ship
*/
float tcGameObject::GetZmin()
{
    return model->GetBoundingBox().ymin();
}

/**
* Linear search to verify child
*/
bool tcGameObject::IsChild(const tcGameObject* child) const
{
    size_t nChildren = children.size();
	for (size_t n=0; n<nChildren; n++)
	{
		if (children[n] == child)
		{
            return true;
		}
	}    
	
	return false;
}

/**
 * Removes child without freeing memory (use for transfers only).
 */
void tcGameObject::RemoveChild(tcGameObject *child)
{
    size_t nChildren = children.size();
	for (size_t n=0; n<nChildren; n++)
	{
		if (children[n] == child)
		{
			children[n] = children.back();
			children.pop_back();

            simState->UnregisterChildObject(child->GetName());
			return;
		}
	}

	fprintf(stderr, "tcGameObject::RemoveChild - child not found\n");
    wxASSERT(false);
}

void tcGameObject::RemoveTargeter(long id)
{
    std::vector<long> temp;

    for (size_t n=0; n<targeters.size(); n++)
    {
        if (targeters[n] != id)
        {
            temp.push_back(targeters[n]);
        }
    }

    targeters = temp;
}


void tcGameObject::ApplyGeneralDamage(float damage, tcGameObject* damager)
{
    float priorDamage = mfDamageLevel;
    mfDamageLevel += damage;
    mfDamageLevel = std::min(mfDamageLevel, 1.0f);

    UpdateScoreForDamage(damager, priorDamage);
}


/**
* @return damage fraction for new damage, 0 means no new damage
*/
float tcGameObject::ApplyAdvancedDamage(const Damage& damage, tcGameObject* damager)
{
    wxASSERT(false); // this should be overridden in base class
    return 0;
}


/**
* Called when repairs remove damage. Launchers, sensors, etc.
* are tested for fix.
* @param fractional amount of new repairs
*/
void tcGameObject::ApplyRepairs(float repair)
{
}

/**
 * @return bearing to p in degrees
 */
float tcGameObject::BearingTo(const tcGameObject& p) const
{
    return C_180OVERPI * BearingToRad(p);
}

/**
* @return bearing to p in radians
*/
float tcGameObject::BearingToRad(const tcGameObject& p) const
{
    return nsNav::GCHeadingApprox_rad(mcKin.mfLat_rad, mcKin.mfLon_rad, 
								    p.mcKin.mfLat_rad, p.mcKin.mfLon_rad);
}

/**
* @see tcTrack::MatchesMask -- should be same logic
*/
bool tcGameObject::MatchesClassificationMask(unsigned int mask) const
{
    bool coarseMatch = ((mpDBObject->mnType & mask & 0xFFF0) != 0);
    bool fineMatch = ((mask & 0x000F) == 0) || ((mask & 0x000F) == (mpDBObject->mnType & 0x000F));

    return coarseMatch && fineMatch;
}

/**
 * mapData must be set with SetGameObjectMapData before using this method.
 * @see SetGameObjectMapData
 */
void tcGameObject::RandInitNear(float afLon_deg, float afLat_deg) 
{
    if (mpDBObject == NULL) {return;}
    wxASSERT(mapData);
    mzClass = mpDBObject->mzClass;
    mzUnit = "OBJ_";
    mzUnit.AssignRandomSuffix();

    mfStatusTime = 0;        
    mcKin.mfLon_rad = C_PIOVER180*(afLon_deg + randfc(1.1f));      
    mcKin.mfLat_rad = C_PIOVER180*(afLat_deg + randfc(1.1f));
    mcKin.mfAlt_m = 0;               
    mcKin.mfHeading_rad = C_TWOPI*randf();           
    mfDamageLevel = 0;     
}


/**
 *
 */
void tcGameObject::PrintToFile(tcFile& file)
{
    tcString s;

    file.WriteString("-----------------------------------------------------------------------\n");
    s.Format("%s (%s) ID:%d DBKEY:%d Alliance:%d \n",mzUnit.c_str(),mzClass.c_str(),mnID,mnDBKey,GetAlliance());
    file.WriteString(s.GetBuffer());

    s.Format("(%3.2f,%3.2f)  speed: %2.1f kts heading: %3.1f deg\n",
        mcKin.mfLat_rad,mcKin.mfLon_rad,mcKin.mfSpeed_kts,mcKin.mfHeading_rad);
    file.WriteString(s.GetBuffer());
}

/**
 *
 */
void tcGameObject::SaveToFile(tcFile& file)
{
    file.Write(&mnID,sizeof(mnID));
    mzClass.Serialize(file,false);
    file.Write(&mnDBKey,sizeof(mnDBKey));
    mzUnit.Serialize(file,false);
//    file.Write(&mnAlliance,sizeof(mnAlliance));                        
    file.Write(&mfStatusTime,sizeof(mfStatusTime));        
    mcKin.Serialize(file,false);      
    mcTerrain.Serialize(file,false); 
    file.Write(&mfDamageLevel,sizeof(mfDamageLevel));       
}

/**
* Score is units of $. Partial damage gets up to 50% of the value of the object. Full
* damage gets the remaining 50%
* Call after damage has been applied to damagee
*/
void tcGameObject::UpdateScoreForDamage(tcGameObject* damager, float priorDamage)
{
    if (priorDamage >= 1.0f) return; // already destroyed

    float& damageLevel = mfDamageLevel;
    if (damageLevel <= priorDamage) return; // no damage
    if (damageLevel > 1.0f) damageLevel = 1.0f;

    float cost = GetCost();
    float newDamage = damageLevel - priorDamage;
    float damageCredit = 0.5f * newDamage * cost;

    if (damageLevel >= 1.0f)
    {
        damageCredit += 0.5f * cost;
    }

    tcGoalTracker::DamageReport report;
    report.unitName = mzUnit.c_str();
    report.alliance = GetAlliance();
    report.classification = mpDBObject->mnType;
    report.damageFraction = damageLevel;
    report.landed = (this->parent != 0); // if it has a parent, then assume "landed" state
    report.databaseClass = mpDBObject->mzClass.c_str();
    report.time = mfStatusTime;

    if (damager != 0)
    {   
        report.damagerClass.push_back(damager->mpDBObject->mzClass.c_str());
        report.damagerQuantity.push_back(1);

        if (damager->GetAffiliationWith(this) == tcAllianceInfo::HOSTILE)
        {
            tcGoalTracker::Get()->AdjustAllianceScore(damager->GetAlliance(), damageCredit);
        }
        else // penalize damage of friendly or neutral units
        {
            tcGoalTracker::Get()->AdjustAllianceScore(damager->GetAlliance(), -2.0f * damageCredit);
        }
    }
    tcGoalTracker::Get()->AdjustAllianceScore(GetAlliance(), -damageCredit);


    tcGoalTracker::Get()->AddDamageReport(mzUnit.c_str(), report);



#ifdef _DEBUG
    wxString s;
    if (damager != 0)
    {
        s.Printf("%s damaged by %s, %s adjustment for alliance %d\n", mzUnit.c_str(), damager->mzUnit.c_str(),
            tcDatabaseObject::CostToString(damageCredit), damager->GetAlliance());
        fprintf(stdout, s.c_str());
    }
    s.Printf("%s damaged, %s adjustment for alliance %d\n\n", mzUnit.c_str(),
        tcDatabaseObject::CostToString(-damageCredit), GetAlliance());
    fprintf(stdout, s.c_str());

#endif
}

float tcGameObject::GetCost() const
{
    if (customCost < 0)
    {
        return mpDBObject->cost;
    }
    else
    {
        return customCost;
    }
}

void tcGameObject::SetCost(float val)
{
    customCost = val;
}

/**
* @return class name for display purposes (option for NATO/ASCC)
*/
const char* tcGameObject::GetDisplayClassName() const
{
    return mpDBObject->GetDisplayName();
}

float tcGameObject::GetDamageLevel() const
{
    return mfDamageLevel;
}


/**
*
*/
CTVMesh* tcGameObject::GetDatabaseMesh()
{
    tc3DModel* pModel = mpDBObject->Get3DModel();
    wxASSERT(pModel != 0);

    return pModel->GetMesh();
}

/**
* Loads state from command stream
*/
tcCommandStream& tcGameObject::operator<<(tcCommandStream& stream)
{
    // no command updates for tcGameObject
    return stream;
}

/**
* Saves state to command stream
*/
tcCommandStream& tcGameObject::operator>>(tcCommandStream& stream)
{
    // no command updates for tcGameObject
    return stream;
}

/**
* Loads state from create stream
*/
tcCreateStream& tcGameObject::operator<<(tcCreateStream& stream)
{
    stream >> mnModelType;
    stream >> mnID; // redundant, can remove later

    mzClass << stream;

    //stream >> mnDBKey; // redundant, can remove later, 20SEP2009 removed

    mzUnit << stream;

    stream >> customCost;

	tcControllableObject::operator<<(stream);

    return stream;
}


/**
* Saves state to create stream
*/
tcCreateStream& tcGameObject::operator>>(tcCreateStream& stream)
{
    stream << mnModelType;
    stream << mnID; // redundant, can remove later

    mzClass >> stream;

    // stream << mnDBKey; // redundant, can remove later, 20SEP2009 removed

    mzUnit >> stream;

    stream << customCost;

	tcControllableObject::operator>>(stream);

    return stream;
}

/**
* Loads state from update stream
*/
tcUpdateStream& tcGameObject::operator<<(tcUpdateStream& stream)
{
    unsigned char hasParent;
    stream >> hasParent;
    if (hasParent)
    {
        rel_pos << stream;
    }
	else
	{
		mcKin << stream;       

		stream >> tcIntervalCompressor(mcTerrain.mfHeight_m, -15000.0f, 15000.0f);

		stream >> tcIntervalCompressor(mfDamageLevel, 0.0f, 1.1f);

		tcControllableObject::operator<<(stream);
	}


    stream >> mfStatusTime;

    return stream;
}

/**
* Saves state to update stream
*/
tcUpdateStream& tcGameObject::operator>>(tcUpdateStream& stream)
{
    unsigned char hasParent = (parent != 0);
    stream << hasParent;
    if (hasParent)
    {
        rel_pos >> stream;
    }
	else
	{
		mcKin >> stream;

		stream << tcIntervalCompressor(mcTerrain.mfHeight_m, -15000.0f, 15000.0f);

		stream << tcIntervalCompressor(mfDamageLevel, 0.0f, 1.1f);

		tcControllableObject::operator>>(stream);
	}

    stream << mfStatusTime;

    return stream;
}

/**
* Save state to game stream
*/
tcGameStream& tcGameObject::operator>>(tcGameStream& stream)
{
    rel_pos >> stream;
    stream << mnModelType;
    mzClass >> stream;
    mzUnit >> stream;
    stream << mfStatusTime;
    mcKin >> stream;
    mcTerrain >> stream;
    stream << mfDamageLevel;
    stream << nextChildId;
    stream << customCost;

	tcControllableObject::operator>>(stream);

    // save child objects
    size_t nChildren = children.size();
    stream << nChildren;

    for (size_t n=0; n<nChildren; n++)
    {
        std::string databaseClass = children[n]->mzClass.c_str();
        long id = children[n]->mnID;

        stream << databaseClass;
        stream << id;
        children[n]->operator>>(stream);
    }

    size_t nLaunch = toLaunch.size();
    stream << nLaunch;

    for (size_t n=0; n<nLaunch; n++)
    {
        std::string databaseClass = toLaunch[n]->mzClass.c_str();
        long id = toLaunch[n]->mnID;

        stream << databaseClass;
        stream << id;
        toLaunch[n]->operator>>(stream);
    }

    CleanupTargeters();
    size_t nTargeters = targeters.size();
    stream << nTargeters;
    for (size_t n=0; n<nTargeters; n++)
    {
        long id = targeters[n];
        stream << id;
    }


    stream.WriteCheckValue(3456);

    return stream;
}

/**
* Load state from game stream
*/
tcGameStream& tcGameObject::operator<<(tcGameStream& stream)
{
    rel_pos << stream;
    stream >> mnModelType;
    mzClass << stream;
    mzUnit << stream;
    stream >> mfStatusTime;
    mcKin << stream;
    mcTerrain << stream;
    stream >> mfDamageLevel;
    stream >> nextChildId;
    stream >> customCost;

	tcControllableObject::operator<<(stream);

    // load child objects
    size_t nChildren;
    stream >> nChildren;

    for (size_t n=0; n<nChildren; n++)
    {
        std::string databaseClass;
        stream >> databaseClass;

        long id;
        stream >> id;

        tcGameObject* child = CreateObject(databaseClass);
        child->operator<<(stream);
        AddChildWithId(child, id);
    }

    size_t nLaunch;
    stream >> nLaunch;

    for (size_t n=0; n<nLaunch; n++)
    {
        std::string databaseClass;
        stream >> databaseClass;

        long id;
        stream >> id;

        tcGameObject* child = CreateObject(databaseClass);
        child->operator<<(stream);
        child->mnID = id;

        toLaunch.push_back(child);

        wxASSERT(false); // just curious if this condition is ever exercised
    }

    targeters.clear();
    size_t nTargeters;
    stream >> nTargeters;
    for (size_t n=0; n<nTargeters; n++)
    {
        long id;
        stream >> id;
        targeters.push_back(id);
    }



    stream.ReadCheckValue(3456);

    return stream;
}

/**
* remove all targeters that don't exist anymore in simState
*/
void tcGameObject::CleanupTargeters()
{
    std::vector<long> temp;

    for (size_t n=0; n<targeters.size(); n++)
    {
        if (tcGameObject* obj = simState->GetObject(targeters[n]))
        {
            temp.push_back(targeters[n]);
        }
    }

    targeters = temp;
}

tcGameObject* tcGameObject::CreateObject(const std::string& databaseClass)
{
    tcDatabaseObject* dataObj = database->GetObject(databaseClass);
    if (dataObj == 0)
    {
        wxString errorMessage = 
            wxString::Format("Error while loading binary save file. Could not find child class name \"%s\" in database, "
            "check entry in scenario \"%s\"\n", 
            databaseClass.c_str(), simState->GetScenarioName());

        fprintf(stderr, errorMessage.c_str());
        return 0;
    }

    tcGameObject* obj = simState->CreateGameObject(dataObj);
    if (obj == 0)
    {
        fprintf(stderr, "Error while loading binary save file. Game child obj creation error\n");
        return false;
    }

    return obj;

}

void tcGameObject::ClearNewCommand()
{
}

bool tcGameObject::HasNewCommand() const
{
    return false;
}

bool tcGameObject::GetRecreate() const
{
	return recreateFlag;
}

void tcGameObject::SetRecreate(bool state)
{
	recreateFlag = state;
}


/**
 *
 */
void tcGameObject::LoadFromFile(tcFile& file)
{
    file.Read(&mnID,sizeof(mnID));
    mzClass.Serialize(file,true);
    file.Read(&mnDBKey,sizeof(mnDBKey));
    mzUnit.Serialize(file,true);
    //file.Read(&mnAlliance,sizeof(mnAlliance));                        
    file.Read(&mfStatusTime,sizeof(mfStatusTime));        
    mcKin.Serialize(file,true);
    mcTerrain.Serialize(file,true); 
    file.Read(&mfDamageLevel,sizeof(mfDamageLevel));  
}

void tcGameObject::SaveToPython(scriptinterface::tcScenarioLogger& logger)
{
    tcScenarioRandomizer* randomizer = tcScenarioRandomizer::Get();

	wxString s;

	logger.AddScenarioText("unit = SM.GetDefaultUnit()");
    
	s.Printf("unit.className = '%s'", mzClass.c_str());
	logger.AddScenarioText(s);

	s.Printf("unit.unitName = \"%s\"", mzUnit.c_str());
	logger.AddScenarioText(s);

	wxASSERT((mcKin.mfLon_rad >= -C_PI) && (mcKin.mfLon_rad < C_PI));
	wxASSERT((mcKin.mfLat_rad >= -C_PIOVER2) && (mcKin.mfLat_rad <= C_PIOVER2));

    std::vector<tcRect> randomBoxes = randomizer->GetRandomBoxes(mzUnit.c_str());
    if (randomBoxes.size() == 0)
    {
	    s.Printf("unit.SetPosition(%f, %f, %.1f)", C_180OVERPI*mcKin.mfLon_rad,
		    C_180OVERPI*mcKin.mfLat_rad, mcKin.mfAlt_m);
	    logger.AddScenarioText(s);
    }
    else
    {
        s = "boxes = [";
        for (size_t k=0; k<randomBoxes.size(); k++)
        {
            if (k > 0) s += ",";
            s += wxString::Format("[%.4f, %.4f, %.4f, %.4f]",
                C_180OVERPI*randomBoxes[k].left, C_180OVERPI*randomBoxes[k].right, 
                C_180OVERPI*randomBoxes[k].bottom, C_180OVERPI*randomBoxes[k].top);
        }
        s += "]";
        logger.AddScenarioText(s);

        s.Printf("box = boxes[int(%d*random())]", randomBoxes.size());
        logger.AddScenarioText(s);

        logger.AddScenarioText("lon_deg = random()*(box[1]-box[0]) + box[0]");
        logger.AddScenarioText("lat_deg = random()*(box[3]-box[2]) + box[2]");

        s.Printf("unit.SetPosition(lon_deg, lat_deg, %.1f)", mcKin.mfAlt_m);
	    logger.AddScenarioText(s);
    }

	s.Printf("unit.heading = %.2f", C_180OVERPI*mcKin.mfHeading_rad);
    logger.AddScenarioText(s);

	s.Printf("unit.speed = %.1f", mcKin.mfSpeed_kts);
	logger.AddScenarioText(s);

    if (GetCost() >= 0)
    {
        s.Printf("unit.cost = %.1f", GetCost());
        logger.AddScenarioText(s);
    }

	s.Printf("SM.AddUnitToAlliance(unit, %d)", GetAlliance());
	logger.AddScenarioText(s);

    logger.AddScenarioText("UI = SM.GetUnitInterface(unit.unitName)");
}

/**
 *
 */
void tcGameObject::Serialize(tcFile& file, bool mbLoad)
{
    if (mbLoad)
    {
        LoadFromFile(file);
    }
    else {
        SaveToFile(file);
    }
}

/**
* Update mesh state for 3D model
*/
void tcGameObject::Update3D()
{
    static tcUserInfo* userInfo = tcUserInfo::Get();
    static tcOptions* options = tcOptions::Get();

    bool use3Dcheat = options->mn3DCheatMode == 3;

    if (userInfo->IsOwnAlliance(GetAlliance()) || use3Dcheat)
    {
        ObjectUpdater* objectUpdater = ObjectUpdater::Get();
        objectUpdater->Update(this);

        if (objectUpdater->GetLastDistanceFromCamera() < 1000.0f)
        {
            size_t nChildren = children.size();
            for (size_t n=0; n<nChildren; n++)
            {
                objectUpdater->Update(children[n]);
            }
        }
        else
        {
            size_t nChildren = children.size();
            for (size_t n=0; n<nChildren; n++)
            {
                children[n]->model->Enable(false);
            }
        }
    }
    else
    {
        model->SetDistanceFromCamera(100000.0f);
        model->Enable(false);
        size_t nChildren = children.size();
        for (size_t n=0; n<nChildren; n++)
        {
            children[n]->model->Enable(false);
        }
    }
}

/**
 * Updates mcKin based on parent position and rel_pos.
 */
void tcGameObject::UpdateCaptivePosition()
{
    if (parent == NULL) {return;}
    // TODO, do this correctly, check Euler matrix
    mcKin = parent->mcKin;
    mcKin.mfRoll_rad += rel_pos.roll;
    mcKin.mfPitch_rad += rel_pos.pitch;
    mcKin.mfHeading_rad += rel_pos.yaw;
}

void tcGameObject::UpdateEffects()
{
	if (model)
	{
		model->UpdateEffects();
	}
}

/**
 *
 */
tcGameObject::tcGameObject()
: nextChildId(1),
  isInvulnerable(false)
{
    Clear();
    mnModelType = MTYPE_OBJECT;
}

/**
 *
 */
tcGameObject::tcGameObject(tcGameObject& o)
: tcControllableObject(o),
  nextChildId(o.nextChildId),
  isInvulnerable(o.isInvulnerable),
  customCost(o.customCost)
{
    children = o.children;
    mcKin = o.mcKin;
    mcTerrain = o.mcTerrain;
    mfDamageLevel = o.mfDamageLevel;  
    mfStatusTime = o.mfStatusTime;    
    mnDBKey = o.mnDBKey;
    mnID = o.mnID;
    mnModelType = MTYPE_OBJECT;
    model = new tc3DModel(o.model); // straight copy is wrong, don't know if this is right
    mpDBObject = o.mpDBObject;
    mzClass = o.mzClass;
    mzUnit = o.mzUnit;
    parent = o.parent;
    rel_pos = o.rel_pos;
    toLaunch = o.toLaunch;
}

/** 
* initializes using database object. database and simState must be set
* before using this method.
* @see SetGameObjectDatabase
*/
tcGameObject::tcGameObject(tcDatabaseObject *obj)
:  recreateFlag(false),
   mnID(-1),
   nextChildId(1),
   isInvulnerable(false),
   customCost(-1.0f)
{
    wxASSERT(database);
    wxASSERT(simState);
    wxASSERT(obj);

    Clear();
    mnDBKey = obj->mnKey;
    mzClass = obj->mzClass;
    mpDBObject = obj;
    model = obj->Copy3DModel();
	if (model) model->SetupUpdate(this);
}

/**
 *
 */
tcGameObject::~tcGameObject() 
{
    ClearChildren();
    if (model)
    {
        model->GetMesh()->Enable(false); // causes crash when game closing
        delete model;
    }
}