#pragma once

//////////////////////////////////////////////////////////////////////////
// Temporary Physics class, for tests only, maybe will be in final release.
//////////////////////////////////////////////////////////////////////////


#include "tv_types.h"
#include "CTVMesh.h"
#include "CTVActor.h"
#include "CTVLandscape.h"

class EXPORTCLASS CTVPhysics
{
public:
	int iPhysicsIndex;
	void Initialize();
	void Unload();
	int CreateBody(float mass);
	void SetBodyInertia(int rigidBodyIndex,float iX, float iY, float iZ);
	void SetBodyPosition(int rigidBodyIndex,float fX, float fY, float fZ);
	void AddForce(int rigidBodyIndex, cTV_3DVECTOR* vForce, bool bLocalSpace = false);
	//void AddTorque(int rigidBodyIndex, cTV_3DVECTOR* vTorque, cTV_3DVECTOR* vWorldPoint);
	void AddImpulseToPoint(int rigidBodyIndex, cTV_3DVECTOR* vImpulse, cTV_3DVECTOR* vPoint, bool bLocalSpace = false);
	void AddImpulse(int rigidBodyIndex, cTV_3DVECTOR* vImpulse, bool bLocalSpace = false);
	void AddTorque(int rigidBodyIndex, cTV_3DVECTOR* vTorque, bool bLocalSpace = false);

	void Simulate(float dt);
	
	void SetBodyMovable(int rigidBodyIndex, bool bMovable);
	void SetBodyAngularVelocity(int rigidBodyIndex,cTV_3DVECTOR* vAngularVelocity, bool bLocalSpace = false);
	void SetBodyLinearVelocity(int rigidBodyIndex,cTV_3DVECTOR* vLinearVelocity, bool bLocalSpace = false);
	void AddMesh(int rigidBodyIndex, CTVMesh* pMesh, cCONST_TV_PHYSICSBODY_BOUNDING eBoundingType, bool bWorldSpace);
	void AddBox(int rigidBodyIndex, cTV_3DVECTOR* vBoxMin, cTV_3DVECTOR* vBoxMax);
	void AddSphere(int rigidBodyIndex, cTV_3DVECTOR* vSphereCenter, float fRadius);
	
	void SetGlobalGravity(cTV_3DVECTOR* vGravity);
	cTV_3DVECTOR GetGlobalGravity();
	int CreateStaticMeshBody(CTVMesh* pMesh,  bool bGroupsAsFaceAttribute = false, bool bOptimize = true);

	int GetActiveBodyCount();
	int GetBodyCount();
	int GetMemoryUsed();

	
	// ball joint
	int CreateBallJoint(int iAttachedBody, int iParentBody, cTV_3DVECTOR* vAttachPointInWorldSpace);
	void SetBallJointLimits(int iBallJoint, bool bLimitsEnable, cTV_3DVECTOR* vSocketAxis, float fMaxConeAngle, float fMaxTwistAngle );
	
	// hinge joint
	int CreateHingeJoint(int iAttachedBody, int iParentBody, cTV_3DVECTOR* vAttachPointInWorldSpace, cTV_3DVECTOR* vHingeAxis);
	void SetHingeJointLimits(int iHingeJoint, bool bLimitsEnable, float fMaxAngle, float fMinAngle);
 
	// slider joint
	int CreateSliderJoint(int iSlidingBody, int iSupportBody, cTV_3DVECTOR* vAttachPointInWorldSpace, cTV_3DVECTOR* vSlidingAxis);
	void SetSliderJointLimits(int iSliderJoint, bool bLimitsEnable, float fMaxPosition, float fMinPosition);

	// up joint
	int CreateUpJoint(int iBody, cTV_3DVECTOR* vDirectionInWorldSpace);
	void SetUpJointDirection(int iUpJoint, cTV_3DVECTOR* vDirectionInWorldSpace);
	cTV_3DVECTOR GetUpJointDirection(int iUpJoint);

	void SetJointBreakage(int iJoint, bool bEnable, float fMaxForceOnTheJoint, bool bAutoRemoveJoint = true);
	void DestroyJoint(int iJoint);

	void DestroyBody(int iBody, bool bDisableAttachedMeshes = false);
	
	int CreateMaterialGroup(char* sOptionalName = NULL);
	int GetDefaultMaterialGroup();
	
	void SetMaterialInteractionSoftness(int iMaterialGroup1 , int iMaterialGroup2 , float fSoftness);
	void SetMaterialInteractionFriction(int iMaterialGroup1 , int iMaterialGroup2 , float fStaticFriction, float fKineticFriction);
	void SetMaterialInteractionBounciness(int iMaterialGroup1, int iMaterialGroup2, float fBounciness);
	void SetMaterialInteractionCollision(int iMaterialGroup1, int iMaterialGroup2, bool bCollisionEnable);
	void SetMaterialInteractionEvents(int iMaterialGroup1, int iMaterialGroup2, bool bRaiseCollisionEvents= true , bool bOneEventPerBodyPairs = true, bool bDisableCollision = false);

	void SetBodyMaterialGroup(int iBody, int iMaterialGroup);
	int GetBodyMaterialGroup(int iBody);
	
	void SetDamping(int iBody, float fLinearDamping, cTV_3DVECTOR* vAngularDamping );

	void SetTorque(int iBody, cTV_3DVECTOR* vTorque, bool bLocalSpace = false);
	void SetForce(int iBody, cTV_3DVECTOR* vForce, bool bLocalSpace = false);

	cTV_3DVECTOR GetTorque(int iBody,bool bLocalSpace=false);
	cTV_3DVECTOR GetForce(int iBody,bool bLocalSpace=false);

	cTV_3DMATRIX GetBodyMatrix(int iBody);
	cTV_3DVECTOR GetBodyAngularVelocity(int iBody,bool bLocalSpace=false);
	cTV_3DVECTOR GetBodyLinearVelocity(int iBody,bool bLocalSpace=false );

	int CreateAutoRagdoll(CTVActor* aActor);
	int CreateStaticTerrainBody(CTVLandscape* lLand);

	void SetBodyMatrix(int iBody, cTV_3DMATRIX* mMatrix);
	void SetAutoFreeze(int iBody, bool bAutoFreezeEnable = true, float fLinearThreshold = 0.001f, float fAngularThreshold = 0.001f, int iNumStep = 20);
	bool IsBodyFrozen(int iBody);
	bool IsJointBroken(int iJoint);
	cTV_3DVECTOR GetJointForce(int iJoint);

	int GetMaterialGroupByName(char* sMaterialGroupName); 

	void SetBodyRotation(int iBody, float fRotationAngleX, float fRotationAngleY, float fRotationAngleZ);
	int CreateMeshBody(float fMass, CTVMesh* pMesh, cCONST_TV_PHYSICSBODY_BOUNDING eBoundingType = cTV_BODY_BOX, bool bRecenterMesh = true);
 
	// special addmesh EX with offset.
	void AddMeshEx(int rigidBodyIndex, CTVMesh* pMesh, cCONST_TV_PHYSICSBODY_BOUNDING eBoundingType, float fTranslationOffsetX, float fTranslationOffsetY, float fTranslationOffsetZ, float fRotationOffsetX, float fRotationOffsetY, float fRotationOffsetZ);
	void AddBoxEx(int rigidBodyIndex, cTV_3DVECTOR* vBoxSize, float fTranslationOffsetX, float fTranslationOffsetY, float fTranslationOffsetZ, float fRotationOffsetX, float fRotationOffsetY, float fRotationOffsetZ);
	void AddSphereEx(int rigidBodyIndex, float fSphereRadius, float fTranslationOffsetX, float fTranslationOffsetY, float fTranslationOffsetZ, float fRotationOffsetX, float fRotationOffsetY, float fRotationOffsetZ);
	

	cTV_3DVECTOR GetBodyPosition(int rigidBodyIndex); 
	void SetBodyBuoyancy(int rigidBodyIndex, bool bEnable, float fLiquidDensity, float fLinearFriction, float fAngularFriction, cTV_PLANE* pLiquidPlane);
	
	void SetHingeJointMotor(int iHingeJoint, bool bMotorEnable, bool bUseSpeedLimit, float fMaxAngularSpeed = 1.0f, float fMaxAcceleration = 1.0f, float fDamping = 0.1f );

	void AddCylinder(int rigidBodyIndex, float fRadius, float fHeight);
	void AddCylinderEx(int rigidBodyIndex, float fRadius, float fHeight, float fTranslationOffsetX, float fTranslationOffsetY, float fTranslationOffsetZ, float fRotationOffsetX, float fRotationOffsetY, float fRotationOffsetZ);
	void AddCone(int rigidBodyIndex, float fRadius, float fHeight);
	void AddConeEx(int rigidBodyIndex, float fRadius, float fHeight, float fTranslationOffsetX, float fTranslationOffsetY, float fTranslationOffsetZ, float fRotationOffsetX, float fRotationOffsetY, float fRotationOffsetZ);
	void AddConvexHull(int rigidBodyIndex, CTVMesh* pSourceMesh);
	void AddConvexHullEx(int rigidBodyIndex, CTVMesh* pSourceMesh, float fTranslationOffsetX, float fTranslationOffsetY, float fTranslationOffsetZ, float fRotationOffsetX, float fRotationOffsetY, float fRotationOffsetZ);

	int CreateVehicle(int iChassisBody);
	int AddVehicleWheel(int iVehicleIndex, float fMass, float fWidth, float fRadius, cTV_3DVECTOR* vRotationAxis, float fLocalPositionX, float fLocalPositionY, float fLocalPositionZ, CTVMesh* pAssociatedMesh = NULL);
	int AddVehicleWheelEx(int iVehicleIndex, float fMass, float fWidth, float fRadius, cTV_3DVECTOR* vRotationAxis, float fLocalPositionX, float fLocalPositionY, float fLocalPositionZ, float fLocalRotationX = 0.0f, float fLocalRotationY = 0.0f, float fLocalRotationZ = 0.0f, float fSuspensionLength = 0.2f, float fSuspensionShock = 1.0f, float fSuspensionSpring = 1.0f, CTVMesh* pAssociatedMesh = NULL);
	void DestroyVehicle(int iVehicleIndex);
	void SetVehicleWheelSteering(int iVehicleIndex, int iWheelIndex, float fSteering, float fDamping = 0.0f);
	void SetVehicleWheelTorque(int iVehicleIndex, int iWheelIndex, float fTorque, float fDamping = 0.0f);
	void DestroyVehicleWheel(int iVehicleIndex, int iWheelIndex);
	void SimulateFixedStep(float fDeltaTime, float fFixedStepTime);
	float GetVehicleWheelLoad(int iVehicleIndex, int iWheelIndex);

	void RenderDebugInfo(bool bWireFrame);
	void EnableDebugInfo(int iBodyIndex, bool bEnable = true, int iColor = -1);

	void SetBodyTag(int iBody, char* sTag);
	char* GetBodyTag(int iBody);

	int PollEvents();
	int GetEventType(int iEventID);
	cTV_EVENT_PHYSICSCOLLISION GetEventCollisionDesc(int iEventID);

	float GetHingeJointAngle(int iHingeJoint);
	float GetSliderJointPosition(int iSliderJoint);
	float GetHingeJointRotationSpeed(int iHingeJoint);
	void SetHingeTorque(int iHingeJoint, float fTorque);

	float GetVehicleWheelAngularVelocity(int iVehicleIndex, int iWheelIndex);
	void SetVehicleWheelParameters(int iVehicleIndex, int iWheelIndex, float fMaxSideSlip = 0.0f, float fSideSlipCoeff = 0.0f, float fMaxLongitudinalSlide = 0.0f, float fLongitudinalSlideCoeff = 0.0f);
	cTV_3DVECTOR GetBodyInertia(int iBody);

	void GetVehicleWheelSpeed(int iVehicle, int iWheelIndex, float* retLongitudinalSpeed, float* retLatitudeSpeed);
	void VehicleWheelHandBrake(int iVehicle, int iWheelIndex, float fCoefficient = 1.0f, float fMaxBrakeTorque = 500.0f);
	void VehicleWheelBrake(int iVehicle, int iWheelIndex, float fBrakeAcceleration, float fMaxBrakeTorque = 500.0f);

	bool IsVehicleWheelColliding(int iVehicle, int iWheelIndex);
	bool IsVehicleWheelLosingTraction(int iVehicle, int iWheelIndex);
	bool IsVehicleWheelLosingSideGrip(int iVehicle, int iWheelIndex);


	float VehicleWheelGetMaxBrakeAcceleration(int iVehicle, int iWheelIndex);
 
	void SetBodyContinuousCollision(int iBody, bool bEnableContinuousCollision = true);
	float GetBodyTotalVolume(int iBody);
	void SetBodyCoriolisForces(int iBody, bool bEnableCoriolisForce = false );
	void VehicleReset(int iVehicle);
	void SetBodyMass(int iBody, float fMass);
	void Explosion(cTV_3DVECTOR* vPosition, float fRadius, float fStrength, bool bCheckCollisions = false, float fMassLimit = -1.0f);
	void SetSolverModel(cCONST_TV_PHYSICS_SOLVER eSolverModel);
	void SetFrictionModel(cCONST_TV_PHYSICS_FRICTION eFrictionModel);
	void SetJointStiffness(int iJoint, float fStiffness);
	float GetVehicleWheelSteering(int iVehicle, int iWheel);

	void SetBodyQuaternion(int iBody, cTV_3DQUATERNION* quat);
	cTV_3DQUATERNION GetBodyQuaternion(int iBody);
	void AddConvexHullFromPoints(int rigidBodyIndex, cTV_3DVECTOR* vFirstElementOfArray, int iNumPoints, float fTranslationOffsetX, float fTranslationOffsetY, float fTranslationOffsetZ, float fRotationOffsetX, float fRotationOffsetY, float fRotationOffsetZ);
	void AddActorEx(int rigidBodyIndex, CTVActor* pActor, cCONST_TV_PHYSICSBODY_BOUNDING eBoundingType, float fTranslationOffsetX, float fTranslationOffsetY, float fTranslationOffsetZ, float fRotationOffsetX, float fRotationOffsetY, float fRotationOffsetZ);
	void AddActor(int rigidBodyIndex, CTVActor* pActor, cCONST_TV_PHYSICSBODY_BOUNDING eBoundingType, bool bUseActorTransformationAsOffset);
	int CreateActorBody(float fMass, CTVActor* pActor, cCONST_TV_PHYSICSBODY_BOUNDING eBoundingType);
	void AddActorBone(int rigidBodyIndex, CTVActor* pActor,int iActorBone);

	void AddEllipsoidEx(int rigidBodyIndex, cTV_3DVECTOR* vEllipsoidRadius, float fTranslationOffsetX, float fTranslationOffsetY, float fTranslationOffsetZ, float fRotationOffsetX, float fRotationOffsetY, float fRotationOffsetZ);
	void AddEllipsoid(int rigidBodyIndex, cTV_3DVECTOR* vEllipsoidCenter, cTV_3DVECTOR* vEllipsoidRadius);
	void FreezeBody(int iBody);
	void UnfreezeBody(int iBody);
	void SyncBodiesWithBones(CTVActor* pRagdollActor);
	void SetJointCollision(int iJoint, bool bCollision);
	void SetMaterialInteractionContinuousCollision(int iMaterialGroup1, int iMaterialGroup2, bool bEnable);
	void AddCapsule(int rigidBodyIndex, cTV_3DVECTOR* vCapsuleCenter, float fRadius, float fHeight);
	void AddCapsuleEx(int rigidBodyIndex, float fRadius, float fHeight,  float fTranslationOffsetX, float fTranslationOffsetY, float fTranslationOffsetZ, float fRotationOffsetX, float fRotationOffsetY, float fRotationOffsetZ);
	float GetBodyMass(int iBody);
	
	void SetBodyCenterOfMass(int iBody, cTV_3DVECTOR* vCenterOfMass);
	cTV_3DVECTOR GetBodyCenterOfMass(int iBody);
	void SetWorldSize(cTV_3DVECTOR* vWorldBoxMin, cTV_3DVECTOR* vWorldBoxMax);
	void GetWorldSize(cTV_3DVECTOR* retWorldBoxMin, cTV_3DVECTOR* retWorldBoxMax);
	int CreateUniversalJoint(int iAttachedBody, int iParentBody, cTV_3DVECTOR* vAttachPointInWorldSpace, cTV_3DVECTOR* vUnitAxis1, cTV_3DVECTOR* vUnitAxis2);
	void SetUniversalJointLimits(int iUniversalJoint, bool bLimitEnable, float fMaxAngle1, float fMinAngle1, float fMaxAngle2, float fMinAngle2);
	cTV_3DVECTOR GetBodyRotation(int iBody);
	void SetVehicleWheelMaterialGroup(int iMaterialGroup, int iVehicle, int iWheel = -1);
	void SetBodyCollidable(int iBody, bool bCollidable);

	bool AdvancedCollision(cTV_3DVECTOR* vStartRay, cTV_3DVECTOR* vEndRay, cTV_COLLISIONRESULT* retResult);
	void EnableCPUOptimizations(bool bEnable);
	void ComputeAccurateInertia(int iBodyID);


	void DestroySimulation(int iSimulationID);
	int GetActiveSimulation();
	void SetActiveSimulation(int iSimulationID);
	int CreateNewSimulation();

	bool TestCollision(int iBody1, int iBody2, bool bFillEvents);
	void SetMaxEventCount(int iMaxEventCount);
	void SetMultiThreadSolvePerIsland(bool bEnable);
	void SetThreadCount(int ThreadCount);
	void InvalideCache();

};