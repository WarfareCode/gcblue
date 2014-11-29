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

#include "GameEngineInit.h"

#include "wx/dir.h"

#include "simmath.h"
#include "tcDBObjSerializerSql.h"
#include "tcPool.h"
#include "tcSonarDBObject.h"
#include "tcPlatformDBObject.h"
#include "tcPlatformObject.h"
#include "DatabaseManager.h"
#include "tcDatabase.h"
#include "tcSimState.h"
#include "tcAllianceInfo.h"
#include "tc3DModel.h"
#include "tcTVEngine.h"
#include "tcAero.h"
#include "tcOptions.h"
#include "tc3DWindow2.h"
#include "tcSonarEnvironment.h"

using namespace database;




void tcGameEngineInit::Init(wxWindow* win)
{
	Aero::LoadAtmosphereTable();

	tcDatabaseManager* databaseManager = tcDatabaseManager::Get();


	sqlite3x::sqlite3_connection& sqlConnection = databaseManager->GetConnection();

	tcDatabase* database = tcDatabase::Get();
	tcGameObject::SetGameObjectDatabase(database);
	tcGameObject::SetSimState(tcSimState::Get());
	tcSimState::Get()->AttachDB(database);
	tcLauncherState::mpDatabase = database;

	tcControllableObject::AttachAllianceInfo();
	tcControllableObject::AttachDatabase();
	tcControllableObject::AttachUserInfo();

	tcTVEngine* tvEngine = tcTVEngine::Get();
    HWND hwnd = reinterpret_cast<HWND>(win->GetHandle());

    bool isWindowed = false;
    tvEngine->InitTV3D(hwnd, isWindowed);

	// test if this is a debug or "tactical" installation
	if (wxDir::Exists("..\\images") && wxDir::Exists("..\\3d"))
	{
		tc3DWindow2::SetImagePath("..\\images\\");
		tc3DModel::SetModelPath("..\\3d\\");
	}
	else if (wxDir::Exists("..\\..\\images") && wxDir::Exists("..\\..\\3d"))
	{
		tc3DWindow2::SetImagePath("..\\..\\images\\");
		tc3DModel::SetModelPath("..\\..\\3d\\");
	}
	else
	{
		wxMessageBox("Unable to locate images and 3d directories", "Error");
		return;
	}



	tc3DModel::LoadUnknowns();


	tcAllianceInfo::Get()->SetAllianceDefaultCountry(0, "Alliance0");
	tcAllianceInfo::Get()->SetAllianceName(0, "Alliance0");
	tcAllianceInfo::Get()->SetAllianceDefaultCountry(1, "Alliance1");
	tcAllianceInfo::Get()->SetAllianceName(1, "Alliance1");


	tcGameObject::SetAddTasksOnCreate(false); // to keep python from being initialized and causing errors




	tcSonarEnvironment* sonarEnvironment = tcSonarEnvironment::Get();
	sonarEnvironment->SetDefaultSVP();

	tcOptions* options = tcOptions::Get();
	options->useRayTracingSonar = 0;
}


tcGameEngineInit::tcGameEngineInit() 
{
}

tcGameEngineInit::~tcGameEngineInit()
{
}