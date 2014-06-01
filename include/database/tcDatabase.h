/**
**  @file tcDatabase.h
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

#ifndef _TCDATABASE_H_
#define _TCDATABASE_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "tcPool.h"
#include "tcString.h" // CString replacement
#include "tcFile.h"  // tcFile replacement
#include "tcDBString.h"
#include "tcDatabaseObject.h"
#include "sqlite/sqlite3x.hpp"
#include <map>
#include "tcDatabaseTable.h"
#include "tcWeaponDamage.h"
#include "tcDamageEffect.h"
#include "tcPlatformSetupContainers.h"
#include "tcLoadoutData.h"

#include <wx/wx.h>
#include <wx/string.h>
#include <wx/arrstr.h>


#include "gctypes.h"
#include <boost/shared_ptr.hpp>

class tcTexture2D;
class wxTextFile;
class wxProgressDialog;
class tcGameStream;

/**
* Contains database code for hierarchical database structure. 
* Historically this database started with a binary format, then went to a
* csv flat text format, and then finally SQL. An XML write-only format was
* also added to support a web effort that lost steam.
*/
namespace database 
{

	class CsvTranslator;
    class tcCountryData;
	class tcCountryNameChanges;
    class tcSignatureModel;
    class tcWeaponDamage;
    class tcDamageEffect;
    class tcAcousticModel;


#ifndef NULL_INDEX
#define NULL_INDEX -1
#endif

#define DATABASE_PATH "database\\"

#define N_DATABASE_OBJECTS 65536

	/**
	* Singleton class for interface with game object database
	*/
	class tcDatabase  
	{
	public:
        struct RecordSummary
        {
            std::string databaseClass;
            std::string databaseDisplayClass; ///< for NATO/ASCC option
            unsigned int classificationId;
            float yearStart;
            float yearStop;
            std::string country;
        };

		static tcDatabase* Get();

		tcPool<tcDatabaseObject,N_DATABASE_OBJECTS> mcObjectData; ///< need to add accessor and iterator for this

		tcString mstrCurrentFile;
		UINT32 mnVersion;
		
		void BuildDictionaries();
        void ClearDictionaries();
		void Clear();
        void ClearForNewScenario();
		int CreateObjectCopy(long anKey);
		int DeleteObject(long anKey);
		long GetRandomKey();
		tcDatabaseObject* GetRandomOfType(UINT model_type);
        const std::vector<RecordSummary>& GetTableSummary(const std::string& tableName) const;
        const std::vector<RecordSummary>& GetItemSummary(const wxArrayString& itemList) const;
        wxArrayString GetPlatformNames(const std::string& className);
        wxArrayString GetPlatformNamesByDate(const std::string& className, float dateYear);
        wxArrayString GetPlatformHulls(const std::string& className);
		const std::string& GetDisplayName(const std::string& className) const;

        bool CheckForErrors(const std::string& logFile);
        bool CheckTableReferences(const char* table, const char* field, const std::vector<std::string>& refTables, const char* refField, wxTextFile& log, unsigned int& errorCount);

		long GetSize() {return mcObjectData.GetCount();}
		int GetObject(long anKey, tcDatabaseObject*& rpobj);
		tcDatabaseObject* GetObject(long anKey);
		tcDatabaseObject* GetObject(const std::string& className); ///< gets object by class name
        const std::string& GetObjectClassName(long key);
        wxArrayString WildcardSearch(const wxString& expression, const wxString& filter);
		wxArrayString WildcardSearchLoaded(const wxString& expression, const wxString& filter);
		int GetObjectClass(long anKey, tcDBString& rzClass);
		long GetNextObjectOfSameClass(long anKey);
		long GetPrevObjectOfSameClass(long anKey);
		long GetKey(const char* s);
		void GetVersion(int& v1, int& v2, int& v3);
		bool IsUsingDynamicLoad() const;

        tcTexture2D* GetEnsign(const std::string& country);
        boost::shared_ptr<tcTexture2D> GetEnsignShared(const std::string& country);
        void GetCountryList(wxArrayString& countryList) const;
		const std::string& GetCountryNameSubstitution(const std::string& originalName, const wxDateTime& dateTime) const;


        tcSignatureModel* GetSignatureModel(const std::string& modelName);
        tcAcousticModel* GetAcousticModel(const std::string& modelName);
        const tcWeaponDamage* GetWeaponDamageData(const std::string& s) const;
        const tcDamageEffect* GetDamageEffectData(const std::string& s) const;
        bool ObjectExists(const std::string& className) const; ///< check if obj matching className already in db

        bool FindPlatformSetups(const std::string& databaseClass, float searchYear, std::vector<std::string>& setupNames);
        bool GetPlatformSetupData(const std::string& databaseClass, const std::string& setupName, 
                std::vector<AirComplement>& airComplement, std::vector<MagazineLoadout>& magazineLoadout,
                std::vector<LauncherLoadout>& launcherLoadout);
        bool GetPlatformSetupData(const std::string& databaseClass, const std::string& setupName, 
                                      tcLoadoutData& loadoutData);
		void PrintToFile(tcString);
		
        void LogSqlColumns(const std::string& fileName);
		void SerializeSql(const std::string& suffix, bool mbLoad);
		void ReadWriteSql(const std::string& fileName, bool load);
		void ReadWriteSql(sqlite3x::sqlite3_connection* sqlConnectionNew, bool load);
        void ExportPlatformTables();
        void ExportLauncherConfigurations();
        bool LoadRecordSqlForceKey(const char* databaseClass, long forcedKey);
        void LoadRecordOtherTables(long key);
		void ReloadRecord(const char* databaseClass); // for dbeditor updates

        void UpdateSql(const std::string& fileName); ///< updates db with add-on database

		void SetProgressReporting(wxProgressDialog* dlg, int p1, int p2);

		wxArrayString tcDatabase::GetFieldsForRow(const wxString& table, const wxString& databaseClass, const wxString& fields);

        tcGameStream& operator>>(tcGameStream& stream);
        tcGameStream& operator<<(tcGameStream& stream);

	private:
		sqlite3x::sqlite3_connection* sqlConnection; ///< pointer to allow external connection to be used
        sqlite3x::sqlite3_connection sqlConnectionLocal; ///< used for normal game mode
		std::map<std::string, long> nameToKey; ///< dictionary of (className, key) pairs
        std::map<std::string, std::string> nameToTable; ///< dictionary of (className, table name)
        std::map<std::string, std::vector<RecordSummary>> tableSummary; ///< dictionary of (table name, vector of RecordSummary)
        std::map<std::string, RecordSummary> classSummary;
        std::map<std::string, long> tableToIndex; ///< dictionary of long index for each table name for switch statement
		std::map<std::string, std::string> nameToDisplayName;
		std::map<std::string, std::string> crossReference; ///< cross-reference (lookup_name, db_name) for mapping multiple or old names to current record

        bool useDynamicLoad; ///< true to only load database entries when needed 
        
        std::map<std::string, tcCountryData> countryData;
		std::map<std::string, tcCountryNameChanges> countryNameChanges;
        boost::shared_ptr<tcTexture2D> unknownEnsign; ///< ensign if country not found

        std::map<std::string, tcSignatureModel*> signatureModelData;
        std::map<std::string, tcAcousticModel*> acousticModelData;

        // special tables for advanced damage model
        tcDatabaseTable<tcWeaponDamage> weaponDamageData;
        tcDatabaseTable<tcDamageEffect> damageEffectData;

        tcWeaponDamage weaponDamageDefault;
        tcDamageEffect damageEffectDefault;

		wxProgressDialog* progressDialog;
		int startProgress;
		int finishProgress;
        

        void CleanSqlColumnText(std::string& columnText);
		bool IsVersionSupported();
        bool LoadRecordSql(const char* databaseClass);
        bool LoadRecordSqlForceKeyExecute(const char* databaseClass, long forcedKey);

        void LoadPlatformTables();
        void LoadLauncherConfigs();
        long LoadLauncherData(const char* databaseClass, long forcedKey = -1);
		void LoadCrossReferenceTable();
		
        void ReadCountryData();
        void InitDamageDefaults();
        void BuildTableLookup();

		void ReportProgress(const wxString& msg, float fractionalProgess);

		tcDatabase();
		~tcDatabase();
	};

}

#endif

