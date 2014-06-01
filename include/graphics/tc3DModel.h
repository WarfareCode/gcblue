/** 
**  @file tc3DModel.h 
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

#ifndef _TC3DMODEL_H_
#define _TC3DMODEL_H_

#if _MSC_VER > 1000
#pragma once
#endif 


#include <boost/shared_ptr.hpp>
#include "tv_types.h"
#include <string>
#include <vector>
#include <deque>
#include "tcBoundingBox.h"

class tc3DViewer;
class tcGameObject;
class tcParticleEffect;
class tcMatrix3;
class CTVMesh;
class CTVNode;
class CTVParticleSystem;


class tcSensorMapTrack;


/**
* animation description stored in CSV database entry
*/
struct animationDBInfo
{
    std::string objectName; ///< name of object within model to animate
    std::string animationType; ///< "propeller"
    int param; ///< sensor number for radar animations
};



class tcAnimationInfo
{
public:
    bool bound; ///< true if animation was successfully found in 3D model and associated with sim model
    std::string objectName; ///< name of object within model to animate
    std::string animationTypeName; ///< "propeller"
    size_t childIdx; ///< child index of corresponding submodel in children vector

    Vec3 axis;
    float omega; ///< radians per second
    short int *switchVariable; ///< rotate if switchVariable is NULL or *switchVariable is non-zero
    float *controlVariable;
    //osg::MatrixTransform* transform; ///< transform to rotate
    int animationType; ///< 0 - propeller, 1 - sensor mast, 2 - helo rotor
    int param; ///< sensor number

    const tcAnimationInfo& operator=(const tcAnimationInfo& rhs);
    tcAnimationInfo(const tcAnimationInfo& src);
    tcAnimationInfo();
    ~tcAnimationInfo();
};



class TiXmlDocument;

/**
* Each database object holds source copy of object's tc3DModel.
* tc3DModel is cloned to instantiate an object into the sim. 
* Clones share leaf nodes using ref_ptr.
*/
class tc3DModel 
{
public:
	enum
	{
		USE_TRUE_MODEL = 0,
		USE_UNKNOWN_GENERIC = 1,
		USE_AIR_GENERIC = 2,
		USE_LAND_GENERIC = 3,
		USE_SURFACE_GENERIC = 4,
		DISABLE_MODEL = 5
	};

	enum SmokeMode
	{
		OFF = 0,
		BUBBLES = 1,
		AFTERBURNER = 2,
		DAMAGE = 3,
		MISSILE = 4,
        WAKE = 5
	};

    std::vector<tcAnimationInfo> animationInfo; ///< animation transforms to update at model level
    void AddChild(tc3DModel *child);
	void AddExplosion(const Vec3& rel_pos);
    tc3DModel* Clone();

    const std::string& GetAuthor() const;
    tcGameObject* GetGameObj() const {return gameObj;}
    void GetLauncherInfo(unsigned int idx, Vec3& pos, float& az, float& el) const;

    // pass through mesh functions to work on collection of meshes contained in tc3DModel
    void Enable(bool state); ///< set enable state of child meshes
    void SetPosition(float x, float y, float z);
    void SetRotationMatrix(tcMatrix3& R);
    void Render();

    CTVMesh* GetMesh();
    CTVMesh* GetSubmodelMesh(size_t k);

    const tcBoundingBox& GetBoundingBox();
	const tcBoundingBox& GetBoundingBoxConst() const;
	float GetRadius();
    float GetRadiusGeneric();
    bool IsSmokeEnabled() const;

    void LoadXml(const std::string& file_name);

    void SetupAnimation(tcGameObject *obj);
    float GetDistanceFromCamera() const;
    void SetDistanceFromCamera(float distance);
	void SetGenericMode(int mode);
    void SetSmokeMode(int mode) {smokeMode = mode;}
	void SetWakeEnable(bool state);
    void SetupUpdate(tcGameObject *obj);
    void UpdateEffects();
    void UpdateSmokePosition(float x, float y, float z);

    void SetGenericMesh(unsigned int classification);

    tc3DModel();
    tc3DModel(const tc3DModel* source);
    ~tc3DModel();

	static void AttachViewer(tc3DViewer* v) {viewer = v;}
	static void LoadUnknowns();
	static void SetModelPath(const std::string& s);
	static const std::string& GetModelPath();


//    static void SetWorldFrame(osg::Group* worldFrame);

    CTVNode* GetChildPivot(size_t idx);
    CTVMesh* GetChildMesh(size_t idx);
private:
    struct LauncherMountInfo
    {
        Vec3 position; ///< start pos for launched item in body coords, default (0,0,0)
        float pointingAzimuth; ///< start rel az of launched item rel to nose, default 0
		float pointingElevation; ///< relative elevation, default 0
    };

    struct ChildMeshInfo
    {
        std::string name;
        CTVNode* pivot;
        CTVMesh* mesh;
        Vec3 position;
        Vec3 rotation; ///< yaw, pitch, roll
        int childIdx;
    };

    struct ParticleInfo
    {
        Vec3 position;
        CTVParticleSystem* particleSystem;
        double createTime;
    };
    
    struct WakeInfo
    {
        Vec3 position;
        Vec3 direction;
    };

    std::string author; // from Info Author attribute in xml model file
    std::string fileName; ///< added for debug

    std::vector<ParticleInfo> smokeTrails;
    std::vector<ParticleInfo> damageSpots;
	std::vector<ParticleInfo> wakeTrails;

    //tcSmoker smokeTrails;

    ///< position of smoke emitters in model coordinates for afterburner and propeller
    std::vector<Vec3> engineSmokeSources;
    std::vector<LauncherMountInfo> launcherInfo;
	std::deque<Vec3> explosionQueue;
	std::vector<WakeInfo> wakeSources;
    std::deque<ParticleInfo> activeExplosions;

    int smokeMode;

    boost::shared_ptr<CTVMesh> mesh;
    std::vector<ChildMeshInfo> children; ///< submodels

	/*osg::ref_ptr<osg::Switch> root; ///< top level group for model
    osg::ref_ptr<osg::LOD> modelGroup; ///< top level group for (identified) model, not shared
    osg::ref_ptr<osg::MatrixTransform> modelTransform; ///< positions object in world, not shared
    osg::ref_ptr<osg::Group> modelNode; ///< shared between instances of model*/

    // osgAL sound node for 3D sound
    //osg::ref_ptr<osgAL::SoundNode> soundNode;

    //static osg::ref_ptr<osg::Group> world;
	static tc3DViewer* viewer; ///< to allow model to calculate its own location

	/// models for unidentified platforms
    static boost::shared_ptr<CTVMesh> unknownAll;
	static boost::shared_ptr<CTVMesh> unknownAir;
	static boost::shared_ptr<CTVMesh> unknownLand;
	static boost::shared_ptr<CTVMesh> unknownSurface;
    static bool useSmoothing;
    static std::string model_path;
    static std::string xmlFileName;

    tcGameObject* gameObj; ///< game object to use to update model state

    float distanceFromCamera;
    int genericMode;

	tcBoundingBox boundingBox;
	bool boundingBoxComputed;


    void DisableSmoke();
    void EnableSmoke();

	CTVParticleSystem* CreateWake(const WakeInfo& wakeInfo);
    void Load(const std::string& model_name);
    void LoadMinimal(const std::string& model_name);
    void LoadXmlAnimationInfo(TiXmlDocument* doc);
    void LoadXmlInfo(TiXmlDocument* doc);
    void LoadXmlMountInfo(TiXmlDocument* doc);
    void LoadXmlSmokeInfo(TiXmlDocument* doc);
    void LoadXmlSubmodels(TiXmlDocument* doc);
    void LoadXmlWakeInfo(TiXmlDocument* doc);
    void ProcessAnimations();
	void UpdateExplosions();
    void DuplicateChildren(const tc3DModel* source);
};

#endif

