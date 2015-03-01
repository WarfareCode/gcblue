/** 
**  @file tcGameObject.h
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

#ifndef _TCGAMEOBJECT_H_
#define _TCGAMEOBJECT_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include <vector>
#include <sstream>


#include "tcSensorState.h"
#include "tcLauncherState.h"
#include "tcControllableObject.h"
#include "tv_types.h"


class tcMapData;
namespace database
{
    class tcDatabase;
}

namespace scriptinterface
{
	class tcScenarioLogger;
}

class tcSimState;
class tcStream;
class tcCommandStream;
class tcCreateStream;
class tcUpdateStream;
class tcGameStream;
class tcLauncher;
class CTVMesh;

class tcDamageModel;
struct Damage;



/**
 * 3D model coordinates relative to parent frame of
 * reference. Objects point in y direction.
 */
struct tsRelativePosition
{
    float dx; ///< right
    float dy; ///< forward
    float dz; ///< up
    float yaw, pitch, roll;
    bool isVisible;

	tsRelativePosition(float _dx, float _dy, float _dz)
		: dx(_dx), dy(_dy), dz(_dz) {}
    tsRelativePosition()
		: dx(0), dy(0), dz(0), yaw(0), pitch(0), roll(0), isVisible(false) {}
    tcStream& operator<<(tcStream& stream);
    tcStream& operator>>(tcStream& stream);
};

/**
* Base class for all game objects.
*/
class tcGameObject : public tcControllableObject
{
	friend class tcGameSerializer;
public:
    tcGameObject *parent;
    tsRelativePosition rel_pos;  ///< if parent is not NULL, this contains relative position
    std::vector<tcGameObject*> children;
    std::vector<tcGameObject*> toLaunch; ///< list of ex-children to launch
    tc3DModel* model;           ///< 3D model
    UINT mnModelType;          ///< class MTYPE_ identifier
    long mnID;
    tcDBString mzClass;        ///< name of database class
    long mnDBKey;       ///< key of database entry
    tcDBString mzUnit;         ///< specific name of class instance

    std::vector<long> targeters; ///< vector of ids of platforms that are targeting this one

    /** derived objects can have different DB obj type in their scope
    /* mpDBObject should always point to relevant data for current model class */
    tcDatabaseObject *mpDBObject;                          
    double mfStatusTime;        ///< timestamp for parameters
    tcKinematics mcKin;         ///< position, motion, etc parameters
    tcTerrainInfo mcTerrain;    ///< ground height ASL, water depth
    bool isInvulnerable;        ///< test mode, true to make immune from damage

    virtual void ApplyGeneralDamage(float damage, tcGameObject* damager); ///< called when new damage occurs
    virtual float ApplyAdvancedDamage(const Damage& damage, tcGameObject* damager); ///< called when new damage occurs

    virtual void ApplyRepairs(float repair); ///< called when repairs occur (damage removed)
    void SelfDestruct();
    void UpdateScoreForDamage(tcGameObject* damager, float priorDamage);
    float GetDamageLevel() const;

    void AddTargeter(long id);
    void RemoveTargeter(long id);
    void CleanupTargeters();

    float RangeTo(const tcGameObject& p) const;
    float BearingTo(const tcGameObject& p) const;
    float BearingToRad(const tcGameObject& p) const;
	bool CalculateCollisionPoint(tcGameObject* collider, Vec3& pos, float& dt, float& distance_m);
    bool CalculateCollisionPointDir(tcGameObject* collider, const Vec3& dir, Vec3& pos, float& distance_m);
	bool CalculateCollisionPointArb(const Vec3& start_eun, const Vec3& dir_eun, Vec3& pos, float& distance);
    bool CalculateCollisionPointOrigin(tcGameObject* collider, Vec3& pos, float& distance_m);
    float CalculateCrossSectionDir(const Vec3& dir_eun);
    unsigned int CalculateRandomHits(const Vec3& pos, const Vec3& dir_eun, float rangeOffset_m, float error_rad, unsigned int nRays);
	Vec3 ConvertModelCoordinatesToWorld(const Vec3& x) const;
    Vec3 GetRandomExteriorPoint();

    void AddChild(tcGameObject* child);
    void AddChildWithId(tcGameObject* child, long id_);
    tcGameObject* GetChild(size_t idx);
    tcGameObject* GetChildById(long id) const;
    tcGameObject* GetChildByName(const std::string& name) const;
    size_t GetNumberOfChildren() const;
    const char* GetName() const; ///< returns instance name of this obj (mzUnit)

    const char* GetDisplayClassName() const;

    tc3DModel* GetModel();
    bool IsChild(const tcGameObject* child) const;
    void RemoveChild(tcGameObject *child);
    virtual void Clear();
    virtual void ClearChildren();
    void GetRelPosOf(tcGameObject *obj, tsRelativePosition& rel_pos);
	void GetRelativeStateLocal(tcGameObject *obj, Vec3& position, Vec3& velocity);
	void GetRelativeStateWorld(tcGameObject *obj, Vec3& position, Vec3& velocity);
	Vec3 GetWorldVelocity() const;
    virtual void RandInitNear(float afLon_deg, float afLat_deg);
	GeoPoint RelPosToLatLonAlt(const tsRelativePosition& rel_pos) const;
	GeoPoint RelPosToLatLonAlt(const float& dx, const float& dy, const float& dz) const;

	virtual void LaunchFrom(tcGameObject* obj, unsigned nLauncher);
    virtual void PrintToFile(tcFile&);
    virtual void SaveToFile(tcFile& file);

    virtual bool IsPlatformObject() const;

    virtual tcCommandStream& operator<<(tcCommandStream& stream);
    virtual tcCreateStream& operator<<(tcCreateStream& stream);
    virtual tcUpdateStream& operator<<(tcUpdateStream& stream);
    virtual tcGameStream& operator<<(tcGameStream& stream);

    virtual tcCommandStream& operator>>(tcCommandStream& stream);
    virtual tcCreateStream& operator>>(tcCreateStream& stream);
    virtual tcUpdateStream& operator>>(tcUpdateStream& stream);
    virtual tcGameStream& operator>>(tcGameStream& stream);

    virtual void ClearNewCommand();
    virtual bool HasNewCommand() const;

	bool GetRecreate() const;
	void SetRecreate(bool state);

    virtual bool IsDestroyed();
    bool IsInvulnerable() const;
    void SetInvulnerable(bool state);

    float GetCost() const;
    void SetCost(float val);

    virtual void LoadFromFile(tcFile& file); 
    virtual void Serialize(tcFile& file, bool mbLoad);
	virtual void SaveToPython(scriptinterface::tcScenarioLogger& logger);
    virtual void Update(double afStatusTime) {}
    virtual void UpdateCaptivePosition();
    virtual void UpdateEffects();
    virtual void DesignateDatum(tcPoint p) {}
    virtual void DesignateLauncherDatum(GeoPoint p, unsigned int anLauncher) {}
    virtual bool DesignateLauncherTarget(long anID, unsigned anLauncher) {return false;}
    virtual void DesignateTarget(long anID) {}
    virtual void GetDatum(GeoPoint& p) {}
    virtual void GetLauncherState(tcLauncherState*& pLauncherState) {pLauncherState = NULL;}
	virtual tcLauncher* GetLauncher(unsigned idx) {return 0;}
	
    virtual float GetSonarSourceLevel(float az_deg) const;
    virtual float GetOpticalCrossSection() const;
    virtual float GetOpticalCrossSection(float view_alt_m, float view_dist_km) const;
    virtual float GetIRSignature(float az_deg) const;

	float GetSpan() const;
    float GetTerrainElevation() {return mcTerrain.mfHeight_m;}
    float GetZmin(); ///< return min height of model+
	float GetZmax(); ///< return max height of model
	float GetZmaxConst() const; ///< return max height of model
    bool IsOwnAlliance() const;
    bool IsHooked() const;
    virtual void Launch(long& rnKey, unsigned& rnLauncher) {}
    virtual void SetHeading(float afNewHeading) {}
    void SetRelativePosition(float dx, float dy, float dz);
    void SetRelativeOrientation(float yaw, float pitch, float roll);
    void SetVisible(bool vis) {rel_pos.isVisible = vis;}
    virtual void SetSpeed(float afNewSpeed) {}
    virtual int SetLaunch(int anLauncher, int anQuantity) {return 9;}

    bool MatchesClassificationMask(unsigned int mask) const;

    static bool IsClientMode() {return clientMode;}
	static bool IsEditMode() {return editMode;}
    static void SetClientMode(bool state) {clientMode = state;}
	static void SetEditMode(bool state) {editMode = state;}
    static void SetGameObjectDatabase(database::tcDatabase *db) {database = db;}
    static void SetGameObjectMapData(tcMapData *md) {mapData = md;}
    static void SetHookedId(long id) {hookedId = id;}
    static void SetSimState(tcSimState *ss) {simState = ss;}
    static void SetLastDamageDescription(const std::string& s);
    static const std::string& GetLastDamageDescription();
	static void SetAddTasksOnCreate(bool state);

    const tcGameObject* operator= (const tcGameObject *p) {return p;}
    tcGameObject();
    tcGameObject(tcGameObject&);
    tcGameObject(tcDatabaseObject *obj); ///< construct using database object
    virtual ~tcGameObject();
protected:
    float mfDamageLevel;       ///< 0 is no damage, 1 is fully damaged
	bool recreateFlag; ///< workaround, true to resend create request for obj (multiplayer client only)
    long nextChildId; ///< for assigning unique child id (until long is exhausted at least)
    float customCost; ///< custom cost assigned to this object for scoring

    static tcMapData* mapData;
    static database::tcDatabase* database;
    static tcSimState* simState;
    static long hookedId; ///< id hooked by user, used for messaging only
    static bool clientMode; ///< true if running as multiplayer client
	static bool editMode; ///< true if running mission editor
    static std::string lastDamageDescription; ///< tag for displaying info on last damage type that occurred
    static unsigned short launchedCounter; /// for assigning unique unit name to launched items
	static bool addTasksOnCreate; ///< true (default) to automatically add some default AI tasks when obj is created

    tcGameObject* CreateObject(const std::string& databaseClass);
    void Update3D();
    CTVMesh* GetDatabaseMesh();
};
#endif