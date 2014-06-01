/**
**  @file tcDatabaseObject.h
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

#ifndef _DATABASEOBJECT_H_
#define _DATABASEOBJECT_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wx/wx.h" 

#include "tcString.h"
#include "tcFile.h"
#include "tcDBString.h"
#include "gctypes.h"
#include <boost/shared_ptr.hpp>
#include <wx/string.h>

class tc3DModel;
class TiXmlElement;

class tcGeometry;


namespace database 
{
    class tcDatabase;
    class CsvTranslator;
	class tcSqlReader;
    
/************** VERSION INFO ***************/
#define VERSION_1_0_5  0x00010005   // numerous updates for 1.25
#define VERSION_1_0_4  0x00010004   // added ESM, restructured sensor DB objects
#define VERSION_1_0_3  0x00010003   // added target flags to missile
#define VERSION_1_0_2  0x00010002   // added 3D model name and description
#define VERSION_1_0_1  0x00010001
#define VERSION_CURRENT VERSION_1_0_5
#define BAD_VERSION 0x07 // bad version error code (clunky, fix sometime)
    

// platform types for classification purposes
#define PTYPE_UNKNOWN 0x0000
#define PTYPE_SURFACE 0x0010
#define PTYPE_SMALLSURFACE 0x0011
#define PTYPE_LARGESURFACE 0x0012
#define PTYPE_CARRIER 0x0016
#define PTYPE_AIR 0x0020
#define PTYPE_FIXEDWING 0x0021
#define PTYPE_HELO 0x0022
#define PTYPE_AIRCM 0x0024
#define PTYPE_MISSILE 0x0040
#define PTYPE_SUBSURFACE 0x0080
#define PTYPE_SUBMARINE 0x0081
#define PTYPE_TORPEDO 0x0082
#define PTYPE_SONOBUOY 0x0084
#define PTYPE_WATERCM 0x0088
#define PTYPE_WATERMINE 0x008A
#define PTYPE_GROUND 0x0100
#define PTYPE_AIRFIELD 0x0101
#define PTYPE_GROUNDVEHICLE 0x0102
#define PTYPE_BALLISTIC 0x0200

void ClassificationToString(UINT16 anType, char *azString);
    
// object model types (model class identifier)
#define MTYPE_OBJECT  0
#define MTYPE_SURFACE 1
#define MTYPE_CARRIER 2
#define MTYPE_AIR 3
#define MTYPE_FIXEDWING 4
#define MTYPE_MISSILE 5
#define MTYPE_HELO 6
#define MTYPE_SUBSURFACE 7
#define MTYPE_SUBMARINE 8
#define MTYPE_TORPEDO 9
#define MTYPE_FIXED 10
#define MTYPE_PLATFORM 11
#define MTYPE_FIXEDWINGX 12  // model with more realism
#define MTYPE_AIRFIELD 13
#define MTYPE_BALLISTIC 14
#define MTYPE_SONOBUOY 15
#define MTYPE_AIRCM 16 // air countermeasure model
#define MTYPE_GROUNDVEHICLE 17 // e.g. ground mobile SAM
#define MTYPE_FUELTANK 20
#define MTYPE_LASERGUIDEDBOMB 21
#define MTYPE_WATERCM 22 // water countermeasure model
#define MTYPE_BALLISTICMISSILE 23
#define MTYPE_ROCKET 24

    /**
    * Requirements for weapon launch
    */
    enum teWeaponLaunchMode 
    {
        DATUM_ONLY,  ///< needs a datum programmed to launch
        FC_TRACK,   ///< needs a fire-control track (launching platform) to launch, semi-active or command guidance
        SEEKER_TRACK,  ///< needs seeker track and FC track to launch
        AUTO,         ///< will launch and either proceed unguided or autonomously search out target
        TARGET_ONLY     ///< needs a target (no track requirements)
    };
    
    
    class tcDatabaseObject 
    {
    public:
        enum {DESCRIPTION_STRING_LENGTH = 2048}; // max length for file descriptions
        tcDBString mzClass;                 ///< name of platform class, e.g. "Spruance"
        std::string natoClass;              ///< NATO/ASCC name for display purposes
        long mnKey;                         ///< key of this object in map
        UINT mnType;                        ///< functional classification type: helo, air, surf, sub, land
        UINT mnModelType;                   ///< model class to use, e.g. tcSurfaceObject, tcAirObject
        float cost;                         ///< default cost for scoring purposes
        float weight_kg;                    ///< weight in kg
        float volume_m3;                    ///< volume in m^3 for storage
        float initialYear;                  ///< initial year this was introduced
        float finalYear;                    ///< final year this was operational
        std::string country;                ///< country affiliation
        std::string designation;            ///< designation code, e.g. DDG, SSN

        std::string imageList;              ///< semicolon delimited list of image files for DB info window
        tcDBString iconFileName;            ///< used for icon file name
        tcDBString mz3DModelFileName;
		std::string mzDescription;
        std::string notes;
        
        static void AttachDatabase(tcDatabase *db) {database = db;}
		const char* GetName() const; ///< returns name of this instance
        const char* GetDisplayName() const; ///< returns name of this instance for display (for NATO/ASCC option)
        virtual const char* GetClassName() const {return "Object";} ///< returns class name of database object
        float GetCost() const {return cost;}
        const char* GetCostString() const; ///< return cost as string
        virtual tc3DModel* Copy3DModel(); ///< creates copy of model (must be deleted)
        virtual tc3DModel* Get3DModel(); ///< gets pointer to database model
        const wxArrayString& GetParsedImageList();
        boost::shared_ptr<tcGeometry> GetIcon();

        void Load3DModel();
		void LoadIcon();
        virtual void PrintToFile(tcFile& file);

        virtual teWeaponLaunchMode GetLaunchMode() const;

		static void AddSqlColumns(std::string& columnString);
		void ReadSql(tcSqlReader& entry);
		void WriteSql(std::string& valueString);

        static const char* CostToString(float cost_);
        static bool displayNATO; ///< true to display NATO/ASCC names

        tcDatabaseObject();
        tcDatabaseObject(const tcDatabaseObject& obj); ///< copy constructor
        tcDatabaseObject(const std::string& databaseClass);
        virtual ~tcDatabaseObject();
    protected:
        static tcDatabase *database; ///< allows db objects to query for other db objects
        tc3DModel *model;
        boost::shared_ptr<tcGeometry> icon; ///< icon for drag/drop container gui
        wxArrayString parsedImageList;

		void LoadFileDescription();
    };
    
}

#endif
