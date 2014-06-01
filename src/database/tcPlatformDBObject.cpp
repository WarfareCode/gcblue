/**
**  @file tcPlatformDBObject.cpp
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

#if _MSC_VER > 1000
#pragma warning(disable:4786) // suppress warning for STL bug in VC6, see Q167355 in the MSDN Library.
#endif

#include "tcPlatformDBObject.h"
#include "tcDatabase.h"
#include "tcFlightportDBObject.h"
#include "tcLauncherDBObject.h"
#include "math_constants.h"
#include "randfn.h"
#include "CsvTranslator.h"
#include "tc3DModel.h"
#include "common/tinyxml.h"
#include "database/tcSqlReader.h"
#include <sstream>
#include "tcStoresDBObject.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;

namespace database
{

tcDatabaseObject* tcPlatformDBObject::AsDatabaseObject()
{
	return this;
}

/**
* Update calculated parameters based on database values
*/
void tcPlatformDBObject::CalculateParams()
{
	fuelConsumptionConstant = (mfMaxSpeed_kts > 0) ? (mfFuelRate_kgps / mfMaxSpeed_kts) : 0;

	invMaxSpeed = (mfMaxSpeed_kts > 0) ? (1.0f / mfMaxSpeed_kts) : 0;
}


float tcPlatformDBObject::GetFuelConsumptionConstant(float speed_kts) const
{
	return fuelConsumptionConstant;
}

/**
* Call after tcDatabase::BuildDictionaries
*/
size_t tcPlatformDBObject::GetItemCapacityForLauncher(size_t launcherIdx, const std::string& item)
{
    if (launcherIdx < maLauncherClass.size())
    {
        tcDatabase* database = tcDatabase::Get();

        tcLauncherDBObject* launcherData = 
            dynamic_cast<tcLauncherDBObject*>(database->GetObject(maLauncherClass[launcherIdx]));

        if (launcherData != 0)
        {
            return (size_t)launcherData->GetCapacityForItem(item);
        }
        else
        {
            wxASSERT(false);
            return 0; 
        }
    }
    else
    {
        wxASSERT(false);
        return 0;
    }
}

/**
* @return relative az of launcher n or 0 for default or if error
* 13JUN2009 changed to use database instead of model for these parameters
*/
Vec2 tcPlatformDBObject::GetLauncherAttitude(unsigned n) const
{
    wxASSERT(n < launcherAz_deg.size());

    if ((int)n < mnNumLaunchers)
    {
        return Vec2(launcherAz_deg[n], launcherEl_deg[n]);
    }
    else
    {
        fprintf(stderr, "Error - GetLauncherAttitude - bad launcher index\n");
        return Vec2(0, 0);
    }


    /*if (tc3DModel* model = Get3DModel())
    {    
        float az, el;
        Vec3 pos;
        model->GetLauncherInfo(n, pos, az, el);
		return Vec2(az, el);
    }
	else
	{
		fprintf(stderr, "Error - GetLauncherAttitude - null model\n");
		return Vec2(0, 0);
	}*/
}

/**
* @return launcher az FOV in deg
* modified 13JUN2009 to put FOV in platform_launcher table (FiringArc_deg)
*/
float tcPlatformDBObject::GetLauncherFOV_deg(unsigned n) const
{    
    wxASSERT(n < launcherFOV_deg.size());

    if ((int)n < mnNumLaunchers)
	{
        return launcherFOV_deg[n];
    }
    else
    {		
        fprintf(stderr, "Error - GetLauncherFOV_deg - bad launcher index\n");
		return 0;
    }
}

/**
* @return launcher index of launcher matching id or -1 if not found
*/
int tcPlatformDBObject::GetLauncherIndex(unsigned int id) const
{
    for (size_t n=0; n<launcherId.size(); n++)
    {
        if (launcherId[n] == id) return int(n);
    }

    // not found, bad <id>
    return -1;
}

/**
* @returns a tc3DPoint object with (x,y,z) relative position of launcher n
* (0, 0, 0) is default
*/
tc3DPoint tcPlatformDBObject::GetLauncherPosition(unsigned n)
{
    tc3DPoint p;

	if ((int)n >= mnNumLaunchers)
	{
		fprintf(stderr, "Error - GetLauncherPosition - bad launcher index\n");
		return p;
	}

    if (tc3DModel* model = Get3DModel())
    {    
        float az, el;
        Vec3 pos;
        model->GetLauncherInfo(n, pos, az, el);
        p.x = pos.x;
        p.y = pos.y;
        p.z = pos.z;
    }

	return p;
}

/**
* @return info from platform_setup or 0 if setupName not found for this class
*/
tcLoadoutData* tcPlatformDBObject::GetLoadout(const std::string& setupName)
{
    static tcLoadoutData result;
    result.setupName = "";

    if (database->GetPlatformSetupData(mzClass.c_str(), setupName, result))
    {
        return &result;
    }
    else
    {
        return 0;
    }
}

/**
* @returns vector of all loadouts in platform_setup for this platform
* @param searchYear only return loadouts valid for this year (can use fractional values for precise date)
*/
const std::vector<tcLoadoutData>& tcPlatformDBObject::GetLoadoutList(float searchYear)
{
    static std::vector<tcLoadoutData> loadoutList;
    loadoutList.clear();

    std::vector<std::string> setupNames;
    database->FindPlatformSetups(mzClass.c_str(), searchYear, setupNames);

    for (size_t n=0; n<setupNames.size(); n++)
    {
        tcLoadoutData* loadoutData = GetLoadout(setupNames[n]);
        if (loadoutData != 0)
        {
            loadoutList.push_back(*loadoutData);
        }
    }
    
    return loadoutList;
}


float tcPlatformDBObject::GetInternalFuelCapacity() const
{
	return mfFuelCapacity_kg;
}

bool tcPlatformDBObject::HasInfiniteFuel() const
{
	return (mfFuelCapacity_kg <= 0);
}

/**
* Call after all data loaded, but before platforms are created.
* Swaps highest capacity magazine to front to workaround fuel issues
*/
void tcPlatformDBObject::ReorderMagazines()
{
    if (maMagazineClass.size() <= 1) return;

    size_t maxIdx = 0;
    unsigned long maxCapacity = 0;
    for (size_t n=0; n<maMagazineClass.size(); n++)
    {
        tcDatabaseObject* databaseObject = database->GetObject(maMagazineClass[n].c_str());       
        if (tcStoresDBObject* storesDBObj = dynamic_cast<tcStoresDBObject*>(databaseObject))
		{
            if (storesDBObj->capacity > maxCapacity)
            {
                maxIdx = n;
                maxCapacity = storesDBObj->capacity;
            }
		}
		else
		{
			fprintf(stderr, "Error - tcPlatformObject::ReorderMagazines"
                " - Stores obj not found for magazine class (%s)\n", maMagazineClass[n].c_str());
		}
    }

    // swap biggest capacity magazine to front to workaround fuel issues
    if (maxIdx != 0)
    {
        std::string tempClass = maMagazineClass[0];
        unsigned int tempId = magazineId[0];
        
        maMagazineClass[0] = maMagazineClass[maxIdx];
        magazineId[0] = magazineId[maxIdx];

        maMagazineClass[maxIdx] = tempClass;
        magazineId[maxIdx] = tempId;
    }
}


void tcPlatformDBObject::PrintToFile(tcFile& file) 
{
   tcString s;
   
   tcDatabaseObject::PrintToFile(file);

   float fG = (float)C_KTSTOMPS*(mfMaxSpeed_kts)*(mfTurnRate_degps)*
      (float)C_TWOPI/((float)C_G*360.0F);
   s.Format("   maxspeed:%2.1f kts accel:%1.2f kts/s turnrate:%2.1f deg/s (%2.2f G)\n",
      mfMaxSpeed_kts,mfAccel_ktsps,mfTurnRate_degps,fG);
   file.WriteString(s.GetBuffer());
   for(int i=0;i<mnNumLaunchers;i++) 
   {
      s.Format("   Launcher %d: class:%s \n",i,maLauncherClass[i].c_str());
      file.WriteString(s.GetBuffer());
   }
   
   tcSensorPlatformDBObject::PrintToFile(file);

   for(int i=0; i<mnNumMagazines; i++) 
   {
      s.Format("   Magazine %d: class:%s \n", i, maMagazineClass[i].c_str());
      file.WriteString(s.GetBuffer());
   }
}



/**
* Adds sql column definitions to columnString. This is used for
* SQL create table command
*/
void tcPlatformDBObject::AddSqlColumns(std::string& columnString)
{
	tcDatabaseObject::AddSqlColumns(columnString);
	
	columnString += ",";

    columnString += "InitialYear number(4),";
    columnString += "FinalYear number(4),";
    columnString += "Country varchar(30),";
    columnString += "Designation varchar(5),";

    columnString += "MaxSpeed_kts number(8),";
    columnString += "Accel_ktsps number(8),";
    columnString += "TurnRate_degps number(8),";
    columnString += "FuelCapacity_kg number(8),";
    columnString += "FuelRate_kgps number(8),";
    columnString += "Toughness number(8),";
	columnString += "DamageEffect varchar(30)";

    /*
    int i;
    for(i=0;i<MAXLAUNCHERS;i++) 
    {
        tcString s;
        s.Format("L%d_class varchar(30),",i+1);
        columnString += s.GetBuffer();

        s.Format("L%d_name varchar(30),",i+1);
        columnString += s.GetBuffer();
    }
	
	for (i=0; i<MAXMAGAZINES; i++) 
    {
        tcString s;
        s.Format("M%d_class varchar(30)", i+1);
        columnString += s.GetBuffer();

        if (i < MAXMAGAZINES - 1)
        {
            columnString += ",";
        }
    }

    tcSensorPlatformDBObject::AddSqlColumns(columnString);
    */

}

void tcPlatformDBObject::ReadSql(tcSqlReader& entry)
{
	tcDatabaseObject::ReadSql(entry);

	mfMaxSpeed_kts = entry.GetDouble("MaxSpeed_kts");               
	mfAccel_ktsps = entry.GetDouble("Accel_ktsps");        
	mfTurnRate_degps = entry.GetDouble("TurnRate_degps");            
	mfFuelCapacity_kg = entry.GetDouble("FuelCapacity_kg");        
	mfFuelRate_kgps = entry.GetDouble("FuelRate_kgps");            
	mfToughness = entry.GetDouble("Toughness");
    damageEffect = entry.GetString("DamageEffect");

	// read launchers
	mnNumLaunchers = 0;
    launcherName.clear();
    maLauncherClass.clear();
    launcherFireControl.clear();
    launcherId.clear();

    // no longer needed since covered by platform_launchers table
    /*
	int i;
	for(i=0;i<MAXLAUNCHERS;i++) 
	{
		std::string launcherClass;
        std::string displayName;
		tcString s;

		s.Format("L%d_class",i+1);
		launcherClass = entry.GetString(s.GetBuffer());

		s.Format("L%d_name",i+1);
		displayName = entry.GetString(s.GetBuffer());


		if (launcherClass.size() > 0)
		{
            maLauncherClass.push_back(launcherClass);
            launcherName.push_back(displayName);

			mnNumLaunchers++;
		}
	}
    */

	// read magazines
	mnNumMagazines = 0;
    maMagazineClass.clear();
    magazineId.clear();

    // no longer needed since all covered by platform_magazines table
    /*
    for (i=0; i<MAXMAGAZINES; i++) 
	{
		std::string magazineClass;
		tcString s;

		s.Format("M%d_class", i+1);
		magazineClass = entry.GetString(s.GetBuffer());

		if (magazineClass.size() > 0)
		{
            maMagazineClass.push_back(magazineClass);
            mnNumMagazines++;
		}

	}
    */

	CalculateParams();

    tcSensorPlatformDBObject::ReadSql(entry);

}

void tcPlatformDBObject::WriteSql(std::string& valueString)
{
	tcDatabaseObject::WriteSql(valueString);

	std::stringstream s;

	s << ",";

	s << mfMaxSpeed_kts << ",";               
	s << mfAccel_ktsps << ",";           
	s << mfTurnRate_degps << ",";              
	s << mfFuelCapacity_kg << ",";         
	s << mfFuelRate_kgps << ",";              
	s << mfToughness << ",";
    s << "'" << damageEffect.c_str() << "'";
	
    /*
	int i;
	for(i=0; i<MAXLAUNCHERS; i++) 
	{
		if (i < mnNumLaunchers) 
		{
			s << "'" << string(maLauncherClass[i].c_str()) << "',";
			s << "'" << launcherName[i].c_str() << "',";
		}
		else
		{
			s << "'',";
			s << "'',";
		}
	
	}
	
	for (i=0; i<MAXMAGAZINES; i++) 
	{
		if (i < mnNumMagazines) 
		{
			s << "'" << string(maMagazineClass[i].c_str()) << "'";
		}
		else
		{
			s << "''";
		}

        if (i < MAXMAGAZINES - 1)
        {
            s << ",";
        }
	}	
	*/

	valueString += s.str();
	
    //tcSensorPlatformDBObject::WriteSql(valueString);
}


tcPlatformDBObject::tcPlatformDBObject() : tcDatabaseObject(),
    tcSensorPlatformDBObject(),
    fuelConsumptionConstant(0),
	invMaxSpeed(0),
    mfMaxSpeed_kts(0),
    mfAccel_ktsps(0),
    mfTurnRate_degps(0),
    mfFuelCapacity_kg(0),
    mfFuelRate_kgps(0),
    mfToughness(1.0f),
    damageEffect(""),
    mnNumLaunchers(0),
    mnNumMagazines(0)
{
   mnModelType = MTYPE_SURFACE;
}

tcPlatformDBObject::tcPlatformDBObject(const tcPlatformDBObject& obj)
:   tcDatabaseObject(obj),
    tcSensorPlatformDBObject(obj),
    mfMaxSpeed_kts(obj.mfMaxSpeed_kts),
    mfAccel_ktsps(obj.mfAccel_ktsps),
    mfTurnRate_degps(obj.mfTurnRate_degps),
    mfFuelCapacity_kg(obj.mfFuelCapacity_kg),
    mfFuelRate_kgps(obj.mfFuelRate_kgps),
    mfToughness(obj.mfToughness),
    damageEffect(obj.damageEffect),
    mnNumLaunchers(obj.mnNumLaunchers),
    mnNumMagazines(obj.mnNumMagazines),
    launcherDescription(obj.launcherDescription),
    launcherName(obj.launcherName),
    launcherFOV_deg(obj.launcherFOV_deg),
    launcherAz_deg(obj.launcherAz_deg),
    launcherEl_deg(obj.launcherEl_deg),
    launcherFireControl(obj.launcherFireControl),
    launcherFireControl2(obj.launcherFireControl2),
    launcherIsReloadable(obj.launcherIsReloadable)
{             
    int i;
    for(i=0;i<mnNumLaunchers;i++)
    {
        maLauncherClass[i] = obj.maLauncherClass[i];  
        launcherName[i] = obj.launcherName[i];
    }

    for (i=0; i<MAXMAGAZINES; i++)
    {
        maMagazineClass[i] = obj.maMagazineClass[i];
        magazineId[i] = obj.magazineId[i]; // valid to do this? why not push_back?
    }

    animationInfo.clear();
    size_t nAn = obj.animationInfo.size();
    for(size_t n=0;n<nAn;n++)
    {
        animationInfo.push_back(obj.animationInfo[n]);
    }

	CalculateParams();
}

tcPlatformDBObject::~tcPlatformDBObject() 
{
}

}
