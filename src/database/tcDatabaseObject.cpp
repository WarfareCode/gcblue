/**  
**  @file tcDatabaseObject.cpp
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


#include "tcDatabaseObject.h"
#include "tcDatabase.h"
#include "math_constants.h"
#include "randfn.h"
#include <iostream>
#include <fstream>
#include "CsvTranslator.h"
#include "tc3DModel.h"
#include "common/tinyxml.h"
#include "database/tcSqlReader.h"
#include "tcGeometry.h"
#include "tcTexture2D.h"
#include "tc3DWindow2.h" // for CreateTexturedSymbol method
#include <sstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

namespace database
{
    bool tcDatabaseObject::displayNATO = false;

    tcDatabase* tcDatabaseObject::database = NULL;
    
    
    void ClassificationToString(UINT16 anType, char *azString) 
    {
        switch (anType) 
        { // classification type
        case PTYPE_UNKNOWN:strcpy(azString,"Unknown");break;
        case PTYPE_SURFACE:strcpy(azString,"Surface");break;
        case PTYPE_SMALLSURFACE:strcpy(azString,"Small surface");break;
        case PTYPE_LARGESURFACE:strcpy(azString,"Large surface");break;
        case PTYPE_CARRIER:strcpy(azString,"Carrier");break;
        case PTYPE_AIR:strcpy(azString,"Air");break;
        case PTYPE_FIXEDWING:strcpy(azString,"Fixed-wing air"); break;
        case PTYPE_MISSILE:strcpy(azString,"Missile");break;
        case PTYPE_HELO:strcpy(azString,"Helo");break;
        case PTYPE_SUBSURFACE:strcpy(azString,"Subsurface");break;
        case PTYPE_SUBMARINE:strcpy(azString,"Submarine");break;
        case PTYPE_TORPEDO:strcpy(azString,"Torpedo");break;
        case PTYPE_WATERMINE:strcpy(azString,"Mine");break;
        case PTYPE_GROUND:strcpy(azString,"Fixed land");break;
        case PTYPE_AIRFIELD:strcpy(azString,"Airfield");break;
        case PTYPE_GROUNDVEHICLE:strcpy(azString,"Ground Veh");break;
        case PTYPE_AIRCM:strcpy(azString, "CM"); break;
        default:strcpy(azString,"Error");break;
        }
    }
    
    
    /***************************** tcDatabaseObject ***********************************/



    /**
    *
    */
    tc3DModel* tcDatabaseObject::Copy3DModel() 
    {
        if (model)
        {
            return model->Clone();
        }
        else
        {
            Load3DModel();
            if (model)
            {
                return model->Clone();
            }
            else
            {        
                wxASSERT(false);
                return NULL;
            }
        }
    }

    /**
    *
    */
    tc3DModel* tcDatabaseObject::Get3DModel() 
    {
        if (model)
        {
            return model;
        }
        else
        {
            Load3DModel();
            if (model)
            {
                return model;
            }
            else
            {        
                wxASSERT(false);
                return NULL;
            }
        }
    }

    /**
    * Static method to convert dollar amount into string
    */
    const char* tcDatabaseObject::CostToString(float cost_)
    {
        static wxString s;

        float abs_cost = fabsf(cost_);

        if (abs_cost == 0)
        {
            s = "";
        }
        else if (abs_cost >= 1e9)
        {
            s.Printf("$%.1fB", 1e-9 * abs_cost);
        }
        else if (abs_cost >= 1e6)
        {
            s.Printf("$%.1fM", 1e-6 * abs_cost);
        }
        else if (abs_cost >= 1e3)
        {
            s.Printf("$%.1fK", 1e-3 * abs_cost);
        }
        else 
        {
            s.Printf("$%.0f", abs_cost);
        }

        if (cost_ < 0)
        {
            s.Prepend("-");
        }

        return s.c_str();

    }

    const char* tcDatabaseObject::GetCostString() const
    {
        return CostToString(cost);
    }

    
	/**
	* @return pointer to icon for gui operations
	*/
	boost::shared_ptr<tcGeometry> tcDatabaseObject::GetIcon()
	{
		if (icon.get() == 0)
		{
			LoadIcon();
		}
		return icon;
	}

    teWeaponLaunchMode tcDatabaseObject::GetLaunchMode() const
    {
        return AUTO;
    }

	const char* tcDatabaseObject::GetName() const
	{
		return mzClass.c_str();
	}

    const char* tcDatabaseObject::GetDisplayName() const
    {
        if (!displayNATO)
        {
            return mzClass.c_str();
        }
        else
        {
            return natoClass.c_str();
        }
    }

    /**
    * @return string array with parsed filenames of images for this db object
    * Database image files are stored in the images\db folder
    */
    const wxArrayString& tcDatabaseObject::GetParsedImageList()
    {
        if ((parsedImageList.size() > 0) || (imageList.size() < 3))
        {
            return parsedImageList;
        }

        wxString s(imageList.c_str());
        while (!s.IsEmpty())
        {
            wxString fileName = s.BeforeFirst(';');
            fileName.Prepend("db\\");
            parsedImageList.Add(fileName);
            s = s.AfterFirst(';');
        }
        return parsedImageList;
        
    }


    void tcDatabaseObject::Load3DModel() 
    {
        if ( (mz3DModelFileName.size() <= 1)  ||
             (mz3DModelFileName == "NONE"))
        {
            return;
        }
        model = new tc3DModel();
        wxASSERT(model);
        model->LoadXml(mz3DModelFileName.c_str());
    }

	/**
	* If description string starts with /fname=<filename>, load
	* description from file instead
	*/
	void tcDatabaseObject::LoadFileDescription()
	{
		if (mzDescription.size() < 10) return;

		wxString s(mzDescription.c_str());
		wxString filename;

		if (!s.StartsWith("/fname=", &filename)) return;

		filename.Prepend("database/");

		std::ifstream in_stream(filename.ToAscii());
		if (!in_stream)
		{
			fprintf(stderr, "tcDatabaseObject::LoadFileDescription -- Bad file name (%s) in description field for %s\n",
				filename.c_str(), mzClass.c_str());
			return;
		}

		std::stringstream ss;
		ss << in_stream.rdbuf();

		mzDescription = ss.str();
	}


	void tcDatabaseObject::LoadIcon()
	{
		wxString fileWithPath;

		if (iconFileName.size() > 4)
		{
			fileWithPath.Printf("icons\\%s", iconFileName.c_str());
		}
		else
		{
			fileWithPath.Printf("icons\\%s", "unknown.jpg");
		}
		
        icon = tc3DWindow2::CreateTexturedSymbol(fileWithPath.c_str(), 32.0f);
	}
    

    
    void tcDatabaseObject::PrintToFile(tcFile& file) {
        tcString s;
        
        file.WriteString("-----------------------------------------------------------------------\n");
        s.Format("%s mnKey:%d mnModelType:%d mnType:%d\n",mzClass.c_str(),
            mnKey,mnModelType,mnType);
        file.WriteString(s.GetBuffer());
        s.Format("   imagefile:%s \n",iconFileName.c_str());
        file.WriteString(s.GetBuffer());
    }
    

	/**
	* Adds sql column definitions to columnString. This is used for
	* SQL create table command
	*/
	void tcDatabaseObject::AddSqlColumns(std::string& columnString)
	{
		// DatabaseClass varchar(30), ModelClassId number(3)
		columnString += "DatabaseClass text primary key,";
        columnString += "NATO_ASCC text,";
        columnString += "ModelClassId numeric,";  
        columnString += "ClassificationId numeric,";
        columnString += "Cost number(7),";
        columnString += "Weight_kg numeric,";
        columnString += "Volume_m3 numeric,";
        columnString += "InitialYear numeric,";
        columnString += "FinalYear numeric,";
        columnString += "Country text,";
        columnString += "Designation text,";
        columnString += "ImageList text," ;
        columnString += "IconFileName text," ;
        columnString += "ModelFileName text,";
        columnString += "Description text,";
        columnString += "Notes text";
	}

	void tcDatabaseObject::ReadSql(tcSqlReader& entry)
	{
		mzClass = entry.GetString("DatabaseClass").c_str();
        natoClass = entry.GetString("NATO_ASCC").c_str();
		mnModelType = entry.GetInt("ModelClassId");
		mnType = entry.GetInt("ClassificationId");
        cost = entry.GetDouble("Cost");
        weight_kg = entry.GetDouble("Weight_kg");
        volume_m3 = entry.GetDouble("Volume_m3");
        initialYear = entry.GetDouble("InitialYear");
        finalYear = entry.GetDouble("FinalYear");
        country = entry.GetString("Country").c_str();
        designation = entry.GetString("Designation").c_str();
        imageList = entry.GetString("ImageList").c_str();
		iconFileName = entry.GetString("IconFileName").c_str();
		mz3DModelFileName = entry.GetString("ModelFileName").c_str();

		mzDescription = entry.GetString("Description").c_str();
		LoadFileDescription();

        notes = entry.GetString("Notes").c_str();

        if (natoClass.size() == 0)
        {
            natoClass = mzClass.c_str();
        }

#ifdef _DEBUG
		//if (entry.GetStringError())
		//{
		//	fprintf(stderr, "tcDatabaseObject::ReadSql - warning: null string occurred in entry: %s\n",
		//		mzClass.c_str());
		//}
#endif
	}

	void tcDatabaseObject::WriteSql(std::string& valueString)
	{
		wxString str = wxString::Format("'%s','%s',%d,%d,%f,%f,%f,%f,%f,'%s','%s','%s','%s','%s','%s','%s'",
			mzClass.c_str(),
            natoClass.c_str(),
			mnModelType,
			mnType,
            cost,
            weight_kg,
            volume_m3,
            initialYear,
            finalYear,
            country.c_str(),
            designation.c_str(),
            imageList.c_str(),
			iconFileName.c_str(),
			mz3DModelFileName.c_str(),
			mzDescription.c_str(),
            notes.c_str());
		
		valueString += str.GetData();

	}

    tcDatabaseObject::tcDatabaseObject(const std::string& databaseClass) :
        mzClass(databaseClass.c_str()),
        cost(0),
        weight_kg(0),
        volume_m3(0),
        initialYear(0),
        finalYear(2999),
        country(""),
        designation(""),
        iconFileName(""),
        mz3DModelFileName(""),
        mnKey(0),
        mnModelType(MTYPE_OBJECT),
        mnType(PTYPE_UNKNOWN),
        model(0),
		mzDescription("No description is available.")
    {
    }


    tcDatabaseObject::tcDatabaseObject() :
        mzClass("UNDEFINED"),
        cost(0),
        weight_kg(0),
        volume_m3(0),
        initialYear(0),
        finalYear(2999),
        country(""),
        designation(""),
        iconFileName(""),
        mz3DModelFileName(""),
        mnKey(0),
        mnModelType(MTYPE_OBJECT),
        mnType(PTYPE_UNKNOWN),
        model(0),
		mzDescription("No description is available.")
    {

    }

	tcDatabaseObject::tcDatabaseObject(const tcDatabaseObject& obj) :
		mzClass(obj.mzClass),
        natoClass(obj.natoClass),
        cost(obj.cost),
        weight_kg(obj.weight_kg),
        volume_m3(obj.volume_m3),
        initialYear(obj.initialYear),
        finalYear(obj.finalYear),
        country(obj.country),
        designation(obj.designation),
        imageList(obj.imageList),
		iconFileName(obj.iconFileName),
        mz3DModelFileName(obj.mz3DModelFileName),
        parsedImageList(obj.parsedImageList),
		mzDescription(obj.mzDescription),
        mnKey(obj.mnKey),
        mnType(obj.mnType),
        mnModelType(obj.mnModelType)
    {
        model = 0; // model not copied
    }
    
    tcDatabaseObject::~tcDatabaseObject() 
    {
        if (model)
        {
            delete model;
        }
    }   
    
    
    
}
