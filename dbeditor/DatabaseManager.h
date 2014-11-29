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
#ifndef _DATABASEMANAGER_H_
#define _DATABASEMANAGER_H_

#include "sqlite/sqlite3x.hpp"
#include "wx/string.h"
#include "wx/arrstr.h"
#include "wx/datetime.h"

#include <map>
#include <vector>

using sqlite3x::sqlite3_connection;

class tcDatabaseManager
{
public:

    bool Open(const std::string& inFile);
    bool Close();
    void Commit(bool beginAgain);
    bool IsOpen() const;
    bool AreChangesPending() const;

    sqlite3_connection& GetConnection();

    const wxArrayString& ReadDatabaseObjectFields(const wxString& table, const wxString& databaseClass, const wxArrayString& fieldList);
    void UpdateDatabaseObject(const wxString& table, const wxString& databaseClass, const wxArrayString& fieldList, const wxArrayString& valueList);

	const wxArrayString& GetGeneralList(const wxString& table, const wxString& field, const wxString& constraint="");
    const wxArrayString& GetPlatformList(const wxString& platformTable, const wxString& constraint="");
	const wxArrayString& GetPlatformListAnnotated(const wxString& platformTable, const wxString& constraint="");
    const std::vector<wxArrayString>& GetPlatformTableData(const wxString& table, const wxString& databaseClass, 
        const wxArrayString& fieldList, const wxString additionalConstraint="");
    void UpdatePlatformTableData(const wxString& table, const wxString& databaseClass, const wxArrayString& fieldList,
         const std::vector<wxArrayString>& tableData, const wxString& additionalConstraint="");
    const wxArrayString& GetReferences(const wxString& table, const wxString& field, const wxString& value);
    const std::vector<int> GetIdList(const wxString& table, const wxString& databaseClass, const wxString& field);
    const wxArrayString& ExecuteQuery(const wxString& query);

    bool PlatformExistsInTable(const wxString& platformTable, const wxString& platformName);
    bool PlatformExistsInTableList(const wxArrayString& platformTableList, const wxString& platformName, wxString& matchingTable);
    bool RenameRecord(const wxString& table, const wxString& originalName, const wxString& newName);
    bool DeleteRecord(const wxString& table, const wxString& databaseClass, const wxString& additionalConstraint="");
    bool DuplicateRecord(const wxString& table, const wxString& databaseClass, const wxString& copyName);

	const wxString& GetCountry(const wxString& databaseClass);
	bool IsWithinDateRange(const wxString& s, const wxDateTime& startFilterDate, const wxDateTime& endFilterDate);
	double DateTimeToFloatYear(const wxDateTime& dt) const;

    bool CreateIndices();

    bool CheckForErrors(const std::string& logFile);
    bool CheckAllSetups();
    bool CheckSetupData(const std::string& databaseClass, wxArrayString& errorMessages);
    bool CheckLauncherSetup(const std::string& databaseClass, const std::string& setupName, wxArrayString& errorMessages);
	bool CheckMagazineSetup(const std::string& databaseClass, const std::string& setupName, wxArrayString& errorMessages);
    static tcDatabaseManager* Get();

private:
    enum {
        PLATFORM_TABLE = 1, 
        SENSOR_TABLE = 2, 
        LAUNCHER_EQUIPMENT_TABLE = 3, 
        STORES_TABLE = 4,
        DEFAULT_TABLE = 5
        };

    sqlite3_connection sqlConnection;
    bool isOpen;
    bool changesArePending;

    std::map<wxString, int> tableRenameTypes;
    wxArrayString aircraftTables;
	wxArrayString platformTables;

    wxArrayString launcherEquipmentTables;
	wxArrayString magazineEquipmentTables;
    wxArrayString setupFields;
    wxArrayString launcherFields;
	wxArrayString magazineLoadoutFields;
	wxArrayString aircraftFields;
	wxArrayString itemFields;
	wxArrayString fueltankFields;

    void Init();
    void BackupFile(const wxString& fileName);

	void TestTemporaryLoad();

    tcDatabaseManager();
    virtual ~tcDatabaseManager();


};


#endif