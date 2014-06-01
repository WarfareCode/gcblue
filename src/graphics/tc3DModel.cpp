/** 
**  @file tc3DModel.cpp 
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

#include "tc3DModel.h"
#include "tcGameObject.h"
#include "tcPlatformObject.h"
#include "tcOptions.h"
#include "ObjectUpdater.h"
//#include "tcParticleEffect.h"
//#include "tcParticlePlacer.h"
#include "tcSound.h"
#include "tcPlatformDBObject.h"
#include "tcSensorMapTrack.h"
#include "tcSimState.h"
#include "tc3DViewer.h"

#include "common/tinyxml.h"

#include "tcTVEngine.h"
#include "CTVMesh.h"
#include "CTVNode.h"
#include "CTVParticleSystem.h"

#include "tcMatrix3.h"


//#include <osgAL/SoundNode>
//#include <osgAL/SoundRoot>
//#include <osgAL/SoundManager>
//#include <osgAL/SoundState>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



std::string tc3DModel::model_path = "3d\\";

boost::shared_ptr<CTVMesh> tc3DModel::unknownAll;
boost::shared_ptr<CTVMesh> tc3DModel::unknownAir;
boost::shared_ptr<CTVMesh> tc3DModel::unknownLand;
boost::shared_ptr<CTVMesh> tc3DModel::unknownSurface;


tc3DViewer* tc3DModel::viewer = 0;
std::string tc3DModel::xmlFileName; // for error reporting

bool tc3DModel::useSmoothing = true;


//---------- tcAnimationInfo ---------- //

const tcAnimationInfo& tcAnimationInfo::operator=(const tcAnimationInfo& rhs)
{
    bound = rhs.bound;
    objectName = rhs.objectName;
    animationTypeName = rhs.animationTypeName;
    childIdx = rhs.childIdx;
    axis = rhs.axis;
    omega = rhs.omega;
    switchVariable = rhs.switchVariable;
    controlVariable = rhs.controlVariable;
    animationType = rhs.animationType;
    param = rhs.param;
    return *this;
}

tcAnimationInfo::tcAnimationInfo(const tcAnimationInfo& src) :
    bound(src.bound),
    objectName(src.objectName),
    animationTypeName(src.animationTypeName),
    childIdx(src.childIdx),
    axis(src.axis),
    omega(src.omega),
    switchVariable(src.switchVariable),
    controlVariable(src.controlVariable),
    animationType(src.animationType),
    param(src.param)
{
}

tcAnimationInfo::tcAnimationInfo() :
    bound(false),
    objectName(""),
    animationTypeName(""),
    childIdx(0),
    axis(1, 0, 0),
    omega(1),
    switchVariable(0),
    controlVariable(0),
    animationType(0),
    param(0)
{
}

tcAnimationInfo::~tcAnimationInfo()
{
}





#if 0
/** 
* Static method to set common world frame to all tc3DModel objects
*/
void tc3DModel::SetWorldFrame(osg::Group* worldFrame)
{
    world = worldFrame;
    tcSmoker::SetWorldFrame(worldFrame);
}
#endif

CTVNode* tc3DModel::GetChildPivot(size_t idx)
{
    if (idx < children.size())
    {
        return children[idx].pivot;
    }
    else
    {
        return 0;
    }
}

CTVMesh* tc3DModel::GetChildMesh(size_t idx)
{
    if (idx < children.size())
    {
        return children[idx].mesh;
    }
    else
    {
        return 0;
    }
}

float tc3DModel::GetDistanceFromCamera() const 
{
    return distanceFromCamera;
}



/**
* Static method to load unknowns models. Should be called
* once at startup
*/
void tc3DModel::LoadUnknowns()
{
    if (unknownAll.get() != 0) return; // models already loaded

    fprintf(stdout, "Loading unknowns: ");

    CTVScene* scene = tcTVEngine::Get()->GetScene();
	if (scene == 0) return;

    CTVMesh* all = scene->CreateMeshBuilder("UnknownAll");
	std::string fileName = model_path + "unk_all.tvm";
	all->LoadTVM(fileName.c_str(), true, true);

    CTVMesh* air = scene->CreateMeshBuilder("UnknownAir");
	fileName = model_path + "air_small.tvm";
	air->LoadTVM(fileName.c_str(), true, true);

    CTVMesh* land = scene->CreateMeshBuilder("UnknownLand");
	fileName = model_path + "surf_small.tvm";
	land->LoadTVM(fileName.c_str(), true, true);

    CTVMesh* surf = scene->CreateMeshBuilder("UnknownSurface");
	fileName = model_path + "surf_small.tvm";
    surf->LoadTVM(fileName.c_str(), true, true);

    unknownAll = boost::shared_ptr<CTVMesh>(all);
    unknownAll->Enable(false);

    unknownAir = boost::shared_ptr<CTVMesh>(air);
    unknownAir->Enable(false);

    unknownLand = boost::shared_ptr<CTVMesh>(land);
    unknownLand->Enable(false);

    unknownSurface = boost::shared_ptr<CTVMesh>(surf);
    unknownSurface->Enable(false);

    //if (!unknownAll.valid()) fprintf(stdout, "FAILED unk_all.3ds ");
    //if (!unknownAir.valid()) fprintf(stdout, "FAILED air_small.3ds ");
    //if (!unknownLand.valid()) fprintf(stdout, "FAILED surf_small.3ds ");
    //if (!unknownSurface.valid()) fprintf(stdout, "FAILED surf_small.3ds ");


	fprintf(stdout, "done\n");

	//if (useSmoothing)
	//{
	//	osgUtil::SmoothingVisitor smoothingVisitor;

	//	unknownAll->accept(smoothingVisitor);
	//	unknownAir->accept(smoothingVisitor);
	//	unknownLand->accept(smoothingVisitor);
	//	unknownSurface->accept(smoothingVisitor);
	//}

}

void tc3DModel::SetModelPath(const std::string& s)
{
	model_path = s;
}

const std::string& tc3DModel::GetModelPath()
{
	return model_path;
}


/**
* Adds child to modelTransform of this model.
*/
void tc3DModel::AddChild(tc3DModel *child)
{
    //modelTransform->addChild(child->GetNode().get());
}


/**
* Queues explosion particle effect at rel_pos relative to 
* origin of model.
*/
void tc3DModel::AddExplosion(const Vec3& rel_pos)
{
	explosionQueue.push_back(rel_pos);
}

tc3DModel* tc3DModel::Clone()
{
    tc3DModel *clonedModel = new tc3DModel(this);

    return clonedModel;
}

CTVParticleSystem* tc3DModel::CreateWake(const WakeInfo& wakeInfo)
{
	CTVScene* scene = tcTVEngine::Get()->GetScene();


	CTVParticleSystem* particleSystem = scene->CreateParticleSystem();
	std::string fileName = model_path + "particle\\wake.tvp";
	static char buffer[128];
	strncpy(buffer, fileName.c_str(), 127); // because CTVParticleSystem wants char* instead of const char* !
	particleSystem->Load(buffer);
    if (particleSystem->GetEmitterCount() != 2)
    {
        wxASSERT(false);
        fprintf(stderr, "tc3DModel::CreateWake -- Bad wake particle definition\n");
        return particleSystem;
    }

    particleSystem->AttachTo(0, cTV_NODETYPE_MESH, mesh->GetEntityIndex(), 0, false);
    particleSystem->AttachTo(1, cTV_NODETYPE_MESH, mesh->GetEntityIndex(), 0, false);

    Vec3 pos = wakeInfo.position;
    Vec3 dir = wakeInfo.direction;
    static Vec3 zeroDir(0, 0, 0);

    particleSystem->SetEmitterPosition(0, &pos);
    particleSystem->SetEmitterDirection(0, true, &dir, &zeroDir);
    particleSystem->SetEmitterGravity(0, false, &zeroDir);

    pos.x = -pos.x;
    dir.x = -dir.x;

    particleSystem->SetEmitterPosition(1, &pos);
    particleSystem->SetEmitterDirection(1, true, &dir, &zeroDir);
    particleSystem->SetEmitterGravity(1, false, &zeroDir);

	return particleSystem;
}


/**
* Do not call this in the middle of scene graph traversal.
* This leads to a crash!
*/
void tc3DModel::DisableSmoke()
{
    for (size_t n=0; n<smokeTrails.size(); n++)
    {
        if (smokeTrails[n].particleSystem != 0)
        {
            smokeTrails[n].particleSystem->Destroy();
            smokeTrails[n].particleSystem = 0;
        }
    }

    for (size_t n=0; n<damageSpots.size(); n++)
    {
        if (damageSpots[n].particleSystem != 0)
        {
            damageSpots[n].particleSystem->Destroy();
            damageSpots[n].particleSystem = 0;
        }
    }
}

void tc3DModel::DuplicateChildren(const tc3DModel* source)
{
    CTVScene* scene = tcTVEngine::Get()->GetScene();

    wxASSERT(children.size() == 0);
    children.clear();

    size_t nChildren = source->children.size();
    for (size_t k=0; k<nChildren; k++)
    {
        const ChildMeshInfo& info = source->children[k];
        CTVMesh* child = info.mesh->Duplicate();
        CTVNode* pivot = scene->CreateNode("");
        child->Enable(false);

        pivot->AttachTo(cTV_NODETYPE_MESH, mesh->GetEntityIndex(), info.childIdx, false);
        pivot->SetPosition(info.position.x, info.position.y, info.position.z);

        tcMatrix3 R;
        R.SetYawPitchRoll(info.rotation.x, info.rotation.y, info.rotation.z);
        pivot->SetRotationMatrix(R.GetMatrix());

        child->AttachTo(cTV_NODETYPE_NODE, pivot->iNodeIndex, 0, false);

        ChildMeshInfo duplicate;
        duplicate.name = info.name;
        duplicate.pivot = pivot;
        duplicate.mesh = child;
        duplicate.position = info.position;
        duplicate.rotation = info.rotation;
        duplicate.childIdx = info.childIdx;

        children.push_back(duplicate);
    }
}

/**
* TV3D doesn't recursively enable/disable children so
* do it this way. Engine designed assuming parent would
* normally be a TVNode (transformation matrix) not a mesh
*/
void tc3DModel::Enable(bool state)
{
    mesh->Enable(state);

    for (size_t k=0; k<children.size(); k++)
    {
        children[k].mesh->Enable(state);
    }

    if (state == false)
    {
        DisableSmoke();
    }
}

/**
* Do not call this in the middle of scene graph traversal.
* This leads to a crash!
*/
void tc3DModel::EnableSmoke()
{
    CTVScene* scene = tcTVEngine::Get()->GetScene();

    std::string effectName = model_path + ("particle\\");

    switch (smokeMode)
    {
    case AFTERBURNER:
        effectName += "missile_trail.tvp";
        break;
    case MISSILE:
        effectName += "missile_trail.tvp";
        break;
    case BUBBLES:
        effectName += "bubble_trail.tvp";
        break;
    case DAMAGE:
        effectName += "fire.tvp";
        break;
    case WAKE:
        effectName += "wake_test.tvp";
        break;
	case OFF:
		return;
		break;
    default:
        wxASSERT(false);
    };

    double createTime = (gameObj != 0) ? gameObj->mfStatusTime : 0;
    wxASSERT(gameObj != 0);

    if (smokeMode == WAKE)
    {
        //Vec3 wakePos(0, 0, 0);

        //CTVParticleSystem* particleSystem = scene->CreateParticleSystem();
        //particleSystem->Load(const_cast<char*>(effectName.c_str()));
        //particleSystem->AttachTo(0, cTV_NODETYPE_MESH, mesh->GetEntityIndex(), 0, false);
        //particleSystem->SetEmitterPosition(0, &wakePos);

    }
    else if (smokeMode != DAMAGE)
    {    
        for (size_t n=0; n<smokeTrails.size(); n++)
        {
            if (smokeTrails[n].particleSystem == 0)
            {
                CTVParticleSystem* particleSystem = scene->CreateParticleSystem();
                particleSystem->Load(const_cast<char*>(effectName.c_str()));
                particleSystem->AttachTo(0, cTV_NODETYPE_MESH, mesh->GetEntityIndex(), 0, false);
                particleSystem->SetEmitterPosition(0, &smokeTrails[n].position);
 
                smokeTrails[n].particleSystem = particleSystem;
                smokeTrails[n].createTime = createTime;
            }
            else
            {
                //smokeTrails[n].particleSystem->Load(const_cast<char*>(effectName.c_str()));
            }
            
        }
    }
    else
    {
        for (size_t n=0; n<damageSpots.size(); n++)
        {
            if (damageSpots[n].particleSystem == 0)
            {
                CTVParticleSystem* particleSystem = scene->CreateParticleSystem();
                particleSystem->Load(const_cast<char*>(effectName.c_str()));
                particleSystem->AttachTo(0, cTV_NODETYPE_MESH, mesh->GetEntityIndex(), 0, false);
                particleSystem->SetEmitterPosition(0, &damageSpots[n].position);
                
                damageSpots[n].particleSystem = particleSystem;
                damageSpots[n].createTime = createTime;
            }
        }
    }




#if 0
    switch (smokeMode)
    {
    case tc3DModel::AFTERBURNER:
    case tc3DModel::BUBBLES:
        for (size_t n=0; n<engineSmokeSources.size(); n++)
        {
            smokeTrails.AddSmokeTrail(engineSmokeSources[n], smokeMode);
        }
        break;
    default:
        smokeTrails.AddSmokeTrail(osg::Vec3(0, 0, 0), smokeMode);
        break;
    }
#endif

}

CTVMesh* tc3DModel::GetMesh()
{
    return mesh.get();
}

const std::string& tc3DModel::GetAuthor() const
{
    return author;
}

/**
* Retrieves launcher info for launcher <idx>
* Zeros are used as default if idx out of range (xml file missing launcher info)
*/
void tc3DModel::GetLauncherInfo(unsigned int idx, Vec3& pos, float& az, float& el) const
{
    if (idx >= launcherInfo.size())
    {
        pos.set(0, 0, 0);
        az = 0;
		el = 0;
        return;
    }

    pos = launcherInfo[idx].position;
    az = launcherInfo[idx].pointingAzimuth;
	el = launcherInfo[idx].pointingElevation;
}



/**
* Always returns radius of true model without considering generic
* models. 
* @see tc3DModel::GetRadiusGeneric
* @return radius of bounding sphere in meters
*/
float tc3DModel::GetRadius()
{
    cTV_3DVECTOR center;
    float radius;

    mesh->GetBoundingSphere(&center, &radius);
	return radius;
}



/**
* @return radius of rendered model, considering generics
*/
float tc3DModel::GetRadiusGeneric()
{
    cTV_3DVECTOR center;
    float radius;

    mesh->GetBoundingSphere(&center, &radius);
	return radius;

    //switch (genericMode)
    //{
    //case USE_TRUE_MODEL: return GetRadius();
    //case USE_UNKNOWN_GENERIC: return unknownAll.get()->getBound().radius();
    //case USE_AIR_GENERIC: return unknownAir.get()->getBound().radius();
    //case USE_LAND_GENERIC: return unknownLand.get()->getBound().radius();
    //case USE_SURFACE_GENERIC: return unknownSurface.get()->getBound().radius();
    //case DISABLE_MODEL: return unknownAll.get()->getBound().radius();
    //default:
    //    fprintf(stderr, "Error - tc3DModel::GetRadiusGeneric - invalid genericMode\n");
    //    return 1.0f;
    //}

}

/**
* Attempts to get bounding box for modelNode. Not sure how wells this works. Awkward because
* GetBoundingBox does not exist for osg::Node.
*/
const tcBoundingBox& tc3DModel::GetBoundingBox()
{
	if (boundingBoxComputed)
	{
		return boundingBox;
	}

    Vec3 p1;
    Vec3 p2;
    mesh->GetBoundingBox(&p1, &p2, false);

    boundingBox.Set(p1, p2);

	boundingBoxComputed = true;
	return boundingBox;
}

/**
* Workaround for const-ness requirements.
*/
const tcBoundingBox& tc3DModel::GetBoundingBoxConst() const
{
	static tcBoundingBox zeroBox; //(0, 0, 0, 0, 0, 0);

	if (boundingBoxComputed)
	{
		return boundingBox;
	}
	else
	{
		wxASSERT(false);
		return zeroBox;
	}

}


CTVMesh* tc3DModel::GetSubmodelMesh(size_t k)
{
    if (k < children.size())
    {
        return children[k].mesh;
    }
    else
    {
        return 0;
    }
}

/**
* @return true if smokeTrails object is active
*/
bool tc3DModel::IsSmokeEnabled() const 
{
    return false;
    //return smokeTrails.IsEnabled();
}

/**
* @param model_name model file name with extension
*/
void tc3DModel::Load(const std::string& model_name)
{
    if (mesh.get() != 0) return; // model already loaded

	tcOptions* options = tcOptions::Get();
    
    if (options->minimal3D != 0)
    {
        LoadMinimal(model_name);
        return;
    }

    std::string full_path = model_path + model_name;
    fileName = model_name;

    tcTVEngine* engine = tcTVEngine::Get();
    CTVScene* scene = engine->GetScene();

    mesh = boost::shared_ptr<CTVMesh>(scene->CreateMeshBuilder());

    if (mesh->LoadTVM(full_path.c_str(), true, true))
    {
		int lightingMode = 0;
		switch (options->lightingMode)
		{
		case 0: lightingMode = cTV_LIGHTING_NORMAL; break;
		case 1: lightingMode = cTV_LIGHTING_BUMPMAPPING_TANGENTSPACE; break;
		case 2: lightingMode = cTV_LIGHTING_OFFSETBUMPMAPPING_TANGENTSPACE; break;
		case 3: lightingMode = cTV_LIGHTING_PERVERTEX_PRT; break;
		default: lightingMode = cTV_LIGHTING_NORMAL; break;
		}
		
        mesh->SetLightingMode(cCONST_TV_LIGHTINGMODE(lightingMode));
        mesh->SetAlphaTest(false);
        mesh->SetBlendingMode(cTV_BLEND_ALPHA);
        mesh->SetCullMode(cTV_DOUBLESIDED);
        mesh->SetShadowCast(true, true);
        mesh->Enable(false);

        bool warnMaterial = true;
        int nGroups = mesh->GetGroupCount();
        for (int k=0; k<nGroups; k++)
        {
            CTVMaterialFactory* materialFactory = engine->GetMaterialFactory();
            int matId = mesh->GetMaterial(k);
            cTV_COLOR ambient = materialFactory->GetAmbient(matId);
            cTV_COLOR diffuse = materialFactory->GetDiffuse(matId);
            cTV_COLOR specular = materialFactory->GetSpecular(matId);

            if ( ((ambient.r + ambient.g + ambient.b) == 0) &&
                ((specular.r + specular.g + specular.b) == 0) &&
                ((diffuse.r + diffuse.g + diffuse.b) != 0))
            {
                materialFactory->SetAmbient(matId, 0.6f, 0.6f, 0.6f, 1.0f);
                materialFactory->SetDiffuse(matId, 0.8f, 0.8f, 0.8f, 1.0f);
                materialFactory->SetSpecular(matId, 0.2f, 0.2f, 0.2f, 1.0f);

                if (warnMaterial)
                {
                    fprintf(stderr, "tc3DModel::Load - Model %s replaced bad or missing material with default\n",
                        full_path.c_str());
                    warnMaterial = false;
                }
            }

        }
    }
    else   
    {
        fprintf(stderr, "Load of 3D model: %s failed (%s)\n", model_name.c_str(), xmlFileName.c_str());
        mesh = unknownAir;
        mesh->Enable(false);
    }
    
    const bool log3Ddetails = tcOptions::Get()->OptionStringExists("Log3DModelDetails");

	if (log3Ddetails)
	{
		fprintf(stdout, "tc3DModel--Loaded 3D model: %s\n", model_name.c_str());
	}

}

/**
* This version is for systems with limited video memory.
* Load the mesh, calculate the bounding box, then replace mesh with a box model
*/
void tc3DModel::LoadMinimal(const std::string& model_name)
{
    std::string full_path = model_path + model_name;
    fileName = model_name;

    tcTVEngine* engine = tcTVEngine::Get();
    CTVScene* scene = engine->GetScene();

    mesh = boost::shared_ptr<CTVMesh>(scene->CreateMeshBuilder());
    
    if (mesh->LoadTVM(full_path.c_str(), true, true))
    {
        Vec3 p1;
        Vec3 p2;
        mesh->GetBoundingBox(&p1, &p2, false);

        boundingBox.Set(p1, p2);
        boundingBoxComputed = true;

        Vec3 delta = p2 - p1;
        
        mesh->CreateBox(delta.x, delta.y, delta.z);
    }
    else
    {
        fprintf(stdout, "Load of 3D model: %s failed.\n", model_name.c_str());
        fprintf(stderr, "Load of 3D model: %s failed.\n", model_name.c_str());
        mesh = unknownAir;
        mesh->Enable(false);
    }
}



/**
* Newer 3D model system. Loads from an Xml file which has
* animation info along with model file name and other info.
* This can also be used to support multiple resolution and damage
* models in the future.
*/
void tc3DModel::LoadXml(const std::string& file_name)
{
    std::string fileNameWithPath = model_path; // default is "3d\\"
    fileNameWithPath += file_name;
    
    xmlFileName = file_name;

    TiXmlDocument* doc = new TiXmlDocument(fileNameWithPath.c_str());
    if (!doc->LoadFile())
    {
        delete doc;
        fprintf(stderr, "Error loading XML file %s\n", file_name.c_str());
        mesh = unknownAll;
        mesh->Enable(false);
        return;
    }

    TiXmlNode* node = doc->FirstChild("Model");

    if (!node)
    {
        delete doc;
        fprintf(stderr, "Model entry missing in XML file %s\n", file_name.c_str());
        mesh = unknownAll;
        mesh->Enable(false);
        return;
    }

    TiXmlElement* current = node->ToElement(); 
    wxASSERT(current);

    std::string modelFileName = current->Attribute("File");

#ifdef _DEBUG
    fprintf(stdout, "Loading model (%s) for xml file (%s)\n",
        modelFileName.c_str(), file_name.c_str());
#endif

    Load(modelFileName);

    LoadXmlSubmodels(doc);

    if (useSmoothing)
    {
//        osgUtil::SmoothingVisitor smoothingVisitor;
//		modelNode->accept(smoothingVisitor);
    }

    LoadXmlAnimationInfo(doc);

    LoadXmlMountInfo(doc);

    LoadXmlSmokeInfo(doc);

    LoadXmlWakeInfo(doc);

    ProcessAnimations();

    LoadXmlInfo(doc);
    
    delete doc;

    wxASSERT(mesh.get() != 0);
}

/**
* Loads animation info for model (if available)
* This will populate the animationInfo vector
*/
void tc3DModel::LoadXmlAnimationInfo(TiXmlDocument* doc)
{
    animationInfo.clear();

    TiXmlNode* current = doc->FirstChild("Animation");
    while (current)
    {
        if (TiXmlElement* elt = current->ToElement())
        {
            tcAnimationInfo ai;
            double axisx = 0;
            double axisy = 0;
            double axisz = 0;
            double angleRate = 0.1;

            ai.bound = false;
            ai.objectName = elt->Attribute("Object");
            ai.animationTypeName = elt->Attribute("Type");
            ai.param = 0;
//            ai.transform = 0;
            ai.axis.set(1, 0, 0); // default

            if (ai.animationTypeName == "Sensor")
            {
                elt->Attribute("SensorIndex", &ai.param);
                ai.animationType = 1;
            }
            else if (ai.animationTypeName == "Propeller")
            {
                ai.animationType = 0;
            }
            else if (ai.animationTypeName == "Rotor")
            {
                ai.animationType = 2;
            }
            else
            {
                fprintf(stderr, "Unrecognized animation type (%s)\n", ai.animationTypeName.c_str());
            }

            // read rotation axis values
            elt->Attribute("AxisX", &axisx);
            elt->Attribute("AxisY", &axisy);
            elt->Attribute("AxisZ", &axisz);

            ai.axis.set(axisx, axisy, axisz);
            ai.axis.operator/=(ai.axis.Length());

            elt->Attribute("AngleRate", &angleRate);
            ai.omega = angleRate;

            bool searching = true;
            for (size_t k=0; (k<children.size())&&searching; k++)
            {
                if (children[k].name == ai.objectName)
                {
                    ai.bound = true;
                    ai.childIdx = k;
                    searching = false;
                }
            }

            if (ai.bound)
            {
                animationInfo.push_back(ai);
            }
            else
            {
                fprintf(stderr, "LoadXmlAnimationInfo - (%s) animation obj (%s) not found (%s)\n",
                    fileName.c_str(), ai.objectName.c_str(), xmlFileName.c_str());
            }

        }
        current = current->NextSibling("Animation");
    }
}

/**
* Loads author info if available
*/
void tc3DModel::LoadXmlInfo(TiXmlDocument* doc)
{
    TiXmlNode* node = doc->FirstChild("Info");
    if (node)
    {
        TiXmlElement* element = node->ToElement(); 
        wxASSERT(element);
        author = element->Attribute("Author");
    }
}


/**
*
*/
void tc3DModel::LoadXmlMountInfo(TiXmlDocument* doc)
{
    launcherInfo.clear();

    TiXmlNode* current = doc->FirstChild("Launcher");
    while (current)
    {
        if (TiXmlElement* elt = current->ToElement())
        {
            LauncherMountInfo info;
            double x = 0;
            double y = 0;
            double z = 0;
            double az = 0;
		    double el = 0;
            elt->Attribute("X", &x);
            elt->Attribute("Y", &y);
            elt->Attribute("Z", &z);
            elt->Attribute("Az", &az);
			elt->Attribute("El", &el);

            info.position.set(x, y, z);
            info.pointingAzimuth = az;
			info.pointingElevation = el;

            launcherInfo.push_back(info);

        }
        current = current->NextSibling("Launcher");
    }
}

/**
* Loads smoke trails location info for model (if available)
* This will populate the engineSmokeSources vector
*/
void tc3DModel::LoadXmlSmokeInfo(TiXmlDocument* doc)
{
    engineSmokeSources.clear();

    TiXmlNode* current = doc->FirstChild("Smoke");
    while (current)
    {
        if (TiXmlElement* elt = current->ToElement())
        {
            double x = 0;
            double y = 0;
            double z = 0;

            elt->Attribute("X", &x);
            elt->Attribute("Y", &y);
            elt->Attribute("Z", &z);

            engineSmokeSources.push_back(Vec3(x, y, z));

            ParticleInfo smokeInfo;

            smokeInfo.position.set(x, y, z);
            smokeInfo.particleSystem = 0;

            smokeTrails.push_back(smokeInfo);
        }

        current = current->NextSibling("Smoke");
    }

}


void tc3DModel::LoadXmlSubmodels(TiXmlDocument* doc)
{           
    //if (!modelNode.valid())
    //{
    //    wxASSERT(false);
    //    return;
    //}

    const bool log3Ddetails = tcOptions::Get()->OptionStringExists("Log3DModelDetails");
    int childIdx = 0;

    TiXmlNode* current = doc->FirstChild("Submodel");
    while (current)
    {
        if (TiXmlElement* elt = current->ToElement())
        {
            std::string model_name; // file name to load mesh from
            std::string object_name; // object name for animation reference
            double x = 0;
            double y = 0;
            double z = 0;
            double yaw = 0;
            double pitch = 0;
            double roll = 0;

            const char* objName = elt->Attribute("Object");
            const char* modelName = elt->Attribute("File");

            if (modelName != 0)
            {
                model_name = elt->Attribute("File");
            }
            else
            {
                model_name = "Error";
            }

            if (objName != 0)
            {
                object_name = objName;
            }
            else // use model name if this field isn't populated in XML file
            {
                object_name = model_name; 
            }
            
            elt->Attribute("X", &x);
            elt->Attribute("Y", &y);
            elt->Attribute("Z", &z);
            elt->Attribute("Yaw", &yaw);
            elt->Attribute("Pitch", &pitch);
            elt->Attribute("Roll", &roll);

            std::string full_path = model_path + model_name;

            CTVScene* scene = tcTVEngine::Get()->GetScene();

            CTVNode* pivot = scene->CreateNode("");

            CTVMesh* subMesh = scene->CreateMeshBuilder();
        

            if (!subMesh->LoadTVM(full_path.c_str(), true, true))
            {
                fprintf(stderr, "Load of 3D submodel: %s failed.\n", model_name.c_str());

            }
            else
            {

                pivot->AttachTo(cTV_NODETYPE_MESH, mesh->GetEntityIndex(), childIdx, true);
                pivot->SetPosition(x, y, z);
                
                tcMatrix3 R;
                R.SetYawPitchRoll(yaw, pitch, roll);
                pivot->SetRotationMatrix(R.GetMatrix());
                
                subMesh->AttachTo(cTV_NODETYPE_NODE, pivot->iNodeIndex, 0, false);
                

                subMesh->SetLightingMode(cTV_LIGHTING_MANAGED); // cTV_LIGHTING_NORMAL
                subMesh->SetAlphaTest(false);
                subMesh->SetBlendingMode(cTV_BLEND_ALPHA);
                subMesh->SetCullMode(cTV_DOUBLESIDED);
                subMesh->Enable(false);



                ChildMeshInfo info;
                info.name = object_name;
                info.pivot = pivot;
                info.mesh = subMesh;
                info.position.set(x, y, z);
                info.rotation.set(yaw, pitch, roll);
                info.childIdx = childIdx++;
                children.push_back(info);
            }


           /* osg::Matrix m =                 
                osg::Matrix::rotate(osg::inDegrees(roll),0.0f,1.0f,0.0f)*
                osg::Matrix::rotate(osg::inDegrees(pitch),1.0f,0.0f,0.0f)*
                osg::Matrix::rotate(-osg::inDegrees(yaw),0.0f,0.0f,1.0f)*
                osg::Matrix::translate(x,y,z)
                ;

            osg::MatrixTransform* transform = new osg::MatrixTransform(m);
            transform->setDataVariance(osg::Object::STATIC);

            osg::Node* node = osgDB::readNodeFile(model_name.c_str());
            if (node == 0)
            {
                fprintf(stdout, "Load of 3D model: %s failed.\n", model_name.c_str());
                fprintf(stderr, "Load of 3D model: %s failed.\n", model_name.c_str());
            }

            transform->addChild(node);
            modelNode->addChild(transform);*/

            if (log3Ddetails)
            {
                fprintf(stdout, "tc3DModel--Loaded 3D submodel: %s\n", model_name.c_str());
            }

        }

        current = current->NextSibling("Submodel");
    }
}


/**
*
*/
void tc3DModel::LoadXmlWakeInfo(TiXmlDocument* doc)
{
    wakeSources.clear();

    //// start test
    //WakeInfo wakeInfo;
    //wakeInfo.position = Vec3(20, 0, 0);


    //float angle_rad = C_PIOVER180 * 45.0f;
    //float zdir = -cosf(angle_rad);
    //float xdir = sinf(angle_rad);
    //wakeInfo.direction.set(xdir, 0, zdir);

    //wakeSources.push_back(wakeInfo);
    return;
    // end test


    TiXmlNode* current = doc->FirstChild("Wake");
    while (current)
    {
        if (TiXmlElement* elt = current->ToElement())
        {
            double x = 0;
            double y = 0;
            double z = 0;
            double angle_deg = 45.0f;

            elt->Attribute("X", &x);
            elt->Attribute("Y", &y);
            elt->Attribute("Z", &z);
            elt->Attribute("Angle_deg", &angle_deg);

            WakeInfo wakeInfo;
            wakeInfo.position = Vec3(x, y, z);

            float angle_rad = C_PIOVER180*float(angle_deg);
            float zdir = -cosf(angle_rad);
            float xdir = sinf(angle_rad);
            wakeInfo.direction.set(xdir, 0, zdir);

            wakeSources.push_back(wakeInfo);

            ParticleInfo smokeInfo;

        }

        current = current->NextSibling("Wake");
    }
}


/**
*
*/
void tc3DModel::ProcessAnimations()
{
    //AnimationProcessor animationProcessor(animationInfo);
    //modelNode->accept(animationProcessor);
}


void tc3DModel::Render()
{
    mesh->Render();
}

void tc3DModel::SetDistanceFromCamera(float distance) 
{
    distanceFromCamera = distance;
}

void tc3DModel::SetPosition(float x, float y, float z)
{
    mesh->SetPosition(x, y, z);
}

void tc3DModel::SetRotationMatrix(tcMatrix3& R)
{
    mesh->SetRotationMatrix(R.GetMatrix());
}

/**
* Called once per instance with animations to bind
* animation variables.
* SetupUpdate must be called first to attach game object
*/
void tc3DModel::SetupAnimation(tcGameObject *obj)
{
    wxASSERT(obj);
    size_t nAnimations = animationInfo.size();
    for(size_t n=0;n<nAnimations;n++)
    {
        tcAnimationInfo& info = animationInfo[n];
        info.switchVariable = NULL;
        if (info.animationType == 0) // propeller, no switch var for now
        {
        }
		else if (info.animationType == 2) // rotor, no switch var for now
        {
        }
        else if (info.animationType == 1) // sensor, use switch var for sensor activity
        {
            if (tcPlatformObject *plat = dynamic_cast<tcPlatformObject*>(obj))
            {
                if (info.param >= (int)plat->GetSensorCount())
                {
                    fprintf(stderr, "tc3DModel::SetupAnimation - Sensor animation param out of range (%s)\n", obj->mzClass.c_str());
                    //wxASSERT(0);
                    return;
                }

                tcSensorState* sensor = plat->GetSensorMutable(info.param);
                info.switchVariable = &sensor->mbActive;
                float tscan = (sensor != 0) ? sensor->mfCurrentScanPeriod_s : 1.0f;
                info.omega = (tscan) ? C_TWOPI/tscan : 0;
            }
        }
        else
        {
            wxASSERT(0);
        }
    }
}

/**
* Switches mesh to one of several generic meshes based on
* classification type
*/
void tc3DModel::SetGenericMesh(unsigned int classification)
{
    if (mesh.get() != 0)
    {
        mesh->Enable(false);
    }

    switch (classification)
    {

    case PTYPE_SURFACE:
    case PTYPE_SMALLSURFACE:
    case PTYPE_LARGESURFACE:
    case PTYPE_CARRIER:
    case PTYPE_SUBSURFACE:
    case PTYPE_SUBMARINE:
        mesh = unknownSurface;
        break;

    case PTYPE_AIR:
    case PTYPE_FIXEDWING:
    case PTYPE_HELO:
        mesh = unknownAir;
        break;

    case PTYPE_MISSILE:
    case PTYPE_BALLISTIC:
        mesh = unknownAll;
        break;

    case PTYPE_GROUND:
    case PTYPE_AIRFIELD:
        mesh = unknownLand;
        break;

    case PTYPE_TORPEDO:
    case PTYPE_SONOBUOY:
        mesh = unknownAll;
        break;

    case PTYPE_UNKNOWN:
    default:
        mesh = unknownAll;
        break;
    }
}


/**
* Sets generic display mode for model.
* Mode controls switch selection at root
* Options for mode are
* 		USE_TRUE_MODEL = 0,
*		USE_UNKNOWN_GENERIC = 1,
*		USE_AIR_GENERIC = 2,
*		USE_LAND_GENERIC = 3,
*		USE_SURFACE_GENERIC = 4,
*	    DISABLE_MODEL = 5
*/
void tc3DModel::SetGenericMode(int mode)
{
	if (mode == DISABLE_MODEL)
	{
        genericMode = DISABLE_MODEL;
		//root->setAllChildrenOff();
		return;
	}

	if ((mode < 0) || (mode > 5))
	{
		fprintf(stderr, "Error - tc3DModel::SetGenericMode - Mode out of range\n");
		return;
	}
	//root->setSingleChildOn(mode);
    genericMode = mode;
}

/**
* Called once per instance to set and configure update callback.
* Bind switchVariable for animations
*/
void tc3DModel::SetupUpdate(tcGameObject* obj)
{
    gameObj = obj;
}


void tc3DModel::SetWakeEnable(bool state)
{
	if ((state == true) && (wakeTrails.size() == 0))
	{
        for (size_t k=0; k<wakeSources.size(); k++)
        {
		    ParticleInfo wake;
		    wake.particleSystem = CreateWake(wakeSources[k]);

		    wakeTrails.push_back(wake);
        }
	}
	else if ((state == false) && (wakeTrails.size() > 0))
	{
		for (size_t k=0; k<wakeTrails.size(); k++)
		{
			if (wakeTrails[k].particleSystem != 0) wakeTrails[k].particleSystem->Destroy();
            wakeTrails[k].particleSystem = 0;
		}
		wakeTrails.clear();
	}
}

/**
* Call outside of scene graph traversal
*/
void tc3DModel::UpdateEffects()
{
    
    bool disableSmoke = ((smokeMode == tc3DModel::OFF) || !mesh->IsEnabled() ||
        (gameObj && gameObj->parent) || (distanceFromCamera > 2000));
    bool smokeDisabled = !IsSmokeEnabled();

    if (disableSmoke != smokeDisabled)
    {
        if (disableSmoke)
        {
            DisableSmoke();
        }
        else
        {
            EnableSmoke();
        }
    }

    /*
    if (!disableSmoke)
    {
        double gameTime = gameObj->mfStatusTime;

        for (size_t k=0; k<smokeTrails.size(); k++)
        {
            //float particleTime = float(gameTime - smokeTrails[k].createTime);
            //smokeTrails[k].particleSystem->UpdateEx(0, particleTime);
        }
    }
    */

    if (mesh->IsEnabled())
    {
	    UpdateExplosions();
    }

}

/**
* Create explosion effects for any queued explosions.
* Explosions are added to world frame for now
*/
void tc3DModel::UpdateExplosions()
{
    if (activeExplosions.size() > 0)
    {
        wxASSERT(gameObj != 0);
        double dt = gameObj->mfStatusTime - activeExplosions.front().createTime;
        
        if (dt > 2.0)
        {
            CTVParticleSystem* explosion = activeExplosions.front().particleSystem;
            wxASSERT(explosion != 0);
            explosion->Destroy();
            activeExplosions.pop_front();
        }
    }

    if (explosionQueue.size() > 0)
    {
        CTVScene* scene = tcTVEngine::Get()->GetScene();

        Vec3 pos = explosionQueue.front();
        explosionQueue.pop_front();

        CTVParticleSystem* particleSystem = scene->CreateParticleSystem();
		std::string fileName = model_path + "particle\\explosion.tvp";
		static char buffer[128];
		strncpy(buffer, fileName.c_str(), 127); // because CTVParticleSystem wants char* instead of const char* !
		particleSystem->Load(buffer);
        //particleSystem->Load("3d\\particle\\mark2.tvp");
        particleSystem->AttachTo(0, cTV_NODETYPE_MESH, mesh->GetEntityIndex(), 0, true);
        particleSystem->AttachTo(1, cTV_NODETYPE_MESH, mesh->GetEntityIndex(), 0, true);
        particleSystem->SetEmitterPosition(0, &pos);
        particleSystem->SetEmitterPosition(1, &pos);

        ParticleInfo x;
        x.particleSystem = particleSystem;
        x.createTime = (gameObj != 0) ? gameObj->mfStatusTime : 0;
        wxASSERT(gameObj != 0);

        activeExplosions.push_back(x);
    }





}

void tc3DModel::UpdateSmokePosition(float x, float y, float z)
{
    //smokeTrails.UpdateSmokePosition(x, y, z);
}

/**
* This constructor is used for the source/factory, notionally
* stored as part of the database object.
* Skips initialization of members used in scene graph.
*/
tc3DModel::tc3DModel()
: gameObj(0),
  author(""),
  boundingBoxComputed(false),
  smokeMode(OFF)
{
}

/**
* SetupUpdate should be called after this to set update callback
* for model.
*/
tc3DModel::tc3DModel(const tc3DModel* source)
: distanceFromCamera(1e10),
  gameObj(source->gameObj),
  author(source->author),
  fileName(source->fileName),
  boundingBox(source->boundingBox),
  boundingBoxComputed(source->boundingBoxComputed),
  mesh(source->mesh->Duplicate(0)),
  smokeTrails(source->smokeTrails),
  wakeSources(source->wakeSources),
  smokeMode(OFF)
  //mesh(unknownAir->Duplicate())
  
{
    mesh->SetShadowCast(true, true);

    static int addCount = 0;

    DuplicateChildren(source);

    //CTVScene* scene = tcTVEngine::Get()->GetScene();
    //mesh = boost::shared_ptr<CTVMesh>(scene->CreateMeshBuilder("Teapot2"));
    //mesh->CreateTeapot();

    //wxASSERT(source->modelNode.valid()); // error if modelNode not loaded yet
	//wxASSERT(unknownAll.valid());

    //modelTransform = new osg::MatrixTransform;
    //modelTransform->setDataVariance(osg::Object::DYNAMIC);

	//root = new osg::Switch;
	//modelTransform->addChild(root.get());

#if 0 // osgAL experiment
    try
    {
        if (addCount < 0)
        {
            soundNode = tcSound::Get()->CreateSound("helolaunch.wav");
            modelTransform->addChild(soundNode.get());
            addCount++;
        }
    }
    catch (...)
    {
        fprintf(stderr, "Failed to load sound file\n");
    }
#endif
   

    /*modelGroup = new osg::LOD;

    root->addChild(modelGroup.get(), true);
	root->addChild(unknownAll.get(), false);
	root->addChild(unknownAir.get(), false);
	root->addChild(unknownLand.get(), false);
	root->addChild(unknownSurface.get(), false);*/
    genericMode = USE_TRUE_MODEL;


    animationInfo.clear();
    size_t nAnimations = source->animationInfo.size();
    for(size_t n=0;n<nAnimations;n++)
    {
        animationInfo.push_back(source->animationInfo[n]);
    }

    engineSmokeSources = source->engineSmokeSources;


    //modelNode = dynamic_cast<osg::Group*>(source->modelNode->clone(ModelCopyOp(this,true,0)));

    //// add children with varying level of detail
    //modelGroup->addChild(modelNode.get(),0,300.0);

    ///*
    //modelGroup->addChild(
    //    dynamic_cast<osg::Node*>(source->modelNode->clone(ModelCopyOp(this,false,2.0f)))
    //    , 200.0, 500.0);
    //*/
    //modelGroup->addChild(
    //    dynamic_cast<osg::Node*>(source->modelNode->clone(ModelCopyOp(this,false,4.0f)))
    //    , 300.0, 10000.0);

    //modelGroup->addChild(
    //    dynamic_cast<osg::Node*>(source->modelNode->clone(ModelCopyOp(this,false,10.0f)))
    //    , 10000.0, 20000.0);

//    unsigned nRanges =  modelGroup->getNumRanges();

		mesh->ComputeNormals();
}

tc3DModel::~tc3DModel()
{
    DisableSmoke();

    // clean up explosions
    while (activeExplosions.size() > 0)
    {
        CTVParticleSystem* explosion = activeExplosions.front().particleSystem;
        wxASSERT(explosion != 0);
        explosion->Destroy();
        activeExplosions.pop_front();
    }
}

