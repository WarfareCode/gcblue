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

#include "DatabaseManager.h"

#include "wx/string.h"
#include "wx/dir.h"
#include "wx/file.h"
#include "wx/filefn.h"
#include "wx/msgdlg.h"
#include "wx/textfile.h"
#include "wx/xml/xml.h"
#include "wx/progdlg.h"

#include "tcDBObjSerializerSql.h"
#include "tcPool.h"
#include "tcSonarDBObject.h"
#include "tcPlatformDBObject.h"

#include <vector>


//#ifdef _DEBUG
//#define new DEBUG_NEW
//#endif

using sqlite3x::sqlite3_connection;
using sqlite3x::sqlite3_reader;
using sqlite3x::sqlite3_command;
using namespace database;

tcDatabaseManager* tcDatabaseManager::Get()
{
    static tcDatabaseManager instance;

    return &instance;
}

bool tcDatabaseManager::AreChangesPending() const
{
    return changesArePending;
}

/**
* Save copy of fileName in backup directory with timetag appended to name
*/
void tcDatabaseManager::BackupFile(const wxString& fileName)
{
    if (!wxDir::Exists("backup"))
    {
        wxMkdir("backup");
    }

    wxString databaseFile = fileName.AfterLast('\\').BeforeFirst('.');

    wxDateTime current = wxDateTime::Now();
    wxString timeStamp = wxString::Format("-%04d%02d%02d-%02d%02d%02d.db", current.GetYear(), 1+current.GetMonth(), current.GetDay(),
        current.GetHour(), current.GetMinute(), current.GetSecond());
    wxString backupFile = wxString("backup\\") + databaseFile + timeStamp;

    wxCopyFile(fileName, backupFile, true);
}

/**
* If database is open, close it
*/
bool tcDatabaseManager::Close()
{
    try
    {
        if (isOpen)
        {
            sqlConnection.close();
            return true;
        }
        else
        {
            return false;
        }
    }
    catch (sqlite3x::database_error err)
    {
        wxMessageBox(err.what(), "Close Error");
        return false;
    }
}

bool tcDatabaseManager::CheckAllSetups()
{
    wxArrayString platformList;
    for (size_t n=0; n<platformTables.size(); n++)
    {
        WX_APPEND_ARRAY(platformList, GetPlatformList(platformTables[n].c_str(), ""));
    }

    wxProgressDialog* progressDialog = new wxProgressDialog("Checking platform setups", "", 100, NULL, wxPD_SMOOTH);
	progressDialog->SetSize(300, 115);

    bool allOK = true;
    wxArrayString errorMessages;
    for (size_t n=0; n<platformList.size(); n++)
    {
        int progressValue = int(100.0f * float(n) / float(platformList.size()));
        progressDialog->Update(progressValue, platformList[n]);
        bool platformOK = CheckSetupData(platformList[n].ToStdString(), errorMessages);
        allOK = allOK && platformOK;
    }

    progressDialog->Destroy();


	wxTextFile log("database_setup_errors.txt");
	if (!log.Exists())
	{
		log.Create();
	}
	else
	{
		log.Open();
	}
	log.Clear();


    if (allOK)
    {
        wxMessageBox("All aircraft setups meet weight, all magazine setups have valid references", "Setup Check Results");
		log.AddLine("No errors in setups found");
    }
    else
    {
		for (size_t n=0; n<errorMessages.size(); n++)
        {
			log.AddLine(errorMessages[n]);
		}


        wxString combinedErrors("Errors detected in setups:\n");
        size_t maxLines = 30;
        for (size_t n=0; (n<errorMessages.size())&&(n<maxLines); n++)
        {
            combinedErrors += errorMessages[n];
            combinedErrors += "\n";
        }
        if (errorMessages.size() >= maxLines)
        {
            combinedErrors += wxString::Format("... more errors, only showing first %d, see database_setup_errors.txt\n", maxLines);
        }
        wxMessageDialog dialog(0, combinedErrors, "Setup Check Results", wxICON_ERROR);
        dialog.ShowModal();
    }

	log.Write();
	log.Close();

    return allOK;
}

bool tcDatabaseManager::CheckForErrors(const std::string& logFile)
{
    return tcDatabase::Get()->CheckForErrors(logFile);
}

bool tcDatabaseManager::CheckSetupData(const std::string& databaseClass, wxArrayString& errorMessages)
{
    std::vector<wxArrayString> setupData =
        GetPlatformTableData("platform_setup", databaseClass, setupFields);

    bool allOK = true;
    for (size_t n=0; n<setupData.size(); n++)
    {
        std::string setupName = setupData[n][0].c_str();
		std::string magazineLoadoutName = setupData[n][4].c_str();
        std::string launcherLoadoutName = setupData[n][5].c_str();

        bool setupOK = CheckLauncherSetup(databaseClass, launcherLoadoutName, errorMessages);
        allOK = allOK && setupOK;

		setupOK = CheckMagazineSetup(databaseClass, magazineLoadoutName, errorMessages);
        allOK = allOK && setupOK;
    }

    return allOK;
}

bool tcDatabaseManager::CheckLauncherSetup(const std::string& databaseClass, const std::string& setupName, 
                                           wxArrayString& errorMessages)
{
	unsigned int nErrors = 0;

    std::vector<wxArrayString> data = GetPlatformTableData("launcher_loadout", setupName, launcherFields);


	wxString matchingTable;
	double fuel_kg = 0;
	double maxTakeoffWeight_kg = 0;
	double weight_kg = 0;
	double dryWeight_kg = 0;

	bool checkAircraftWeight = false;

	if (PlatformExistsInTableList(aircraftTables, databaseClass, matchingTable))
	{
		std::vector<wxArrayString> aircraftData = GetPlatformTableData(matchingTable, databaseClass, aircraftFields);
		if (aircraftData.size() > 0)
		{
			aircraftData[0][0].ToDouble(&fuel_kg);
			aircraftData[0][1].ToDouble(&maxTakeoffWeight_kg);
			aircraftData[0][2].ToDouble(&dryWeight_kg);

			checkAircraftWeight = true;
		}
		else
		{
			wxASSERT(false);
		}
	}
	else
	{
		// don't check aircraft weight, but check for valid references
	}

	weight_kg = dryWeight_kg;



	// iterate through each item in data and update quantity, volume, and weight
	for (size_t n=0; n<data.size(); n++)
	{
		wxString item = data[n][0];
		long quantity_n = 0;
		data[n][1].ToLong(&quantity_n);

		wxString matchingTable;
		if (PlatformExistsInTableList(launcherEquipmentTables, item, matchingTable))
		{
			if (checkAircraftWeight)
			{
				std::vector<wxArrayString> itemData = GetPlatformTableData(matchingTable, item, itemFields);
				if (itemData.size() > 0)
				{
					double itemWeight_kg = 0;
					itemData[0][0].ToDouble(&itemWeight_kg);

					weight_kg += double(quantity_n) * itemWeight_kg;
				}
				if (matchingTable == "fueltank")
				{
					std::vector<wxArrayString> tankData = GetPlatformTableData(matchingTable, item, fueltankFields);
					if (tankData.size() > 0)
					{
						double fueltankFuel_kg = 0;
						tankData[0][0].ToDouble(&fueltankFuel_kg);
						weight_kg += double(quantity_n) * fueltankFuel_kg;
					}
				}
			}
		}
		else if (item.size() > 0) // non-blank item not found, bad reference
		{
			nErrors++;
			errorMessages.push_back(wxString::Format("%s setup %s item not found: %s",
				databaseClass.c_str(), setupName.c_str(), item.c_str()));
		}
	}


	if (checkAircraftWeight)
	{
		float totalWeight_kg = weight_kg + fuel_kg;
		if (totalWeight_kg > maxTakeoffWeight_kg)
		{
			nErrors++;
			errorMessages.push_back(wxString::Format("%s aircraft setup %s is overweight (%.1f/%.1f)",
				databaseClass.c_str(), setupName.c_str(), totalWeight_kg, maxTakeoffWeight_kg));
		}
	}


	return (nErrors == 0);
}


bool tcDatabaseManager::CheckMagazineSetup(const std::string& databaseClass, const std::string& setupName, 
                                           wxArrayString& errorMessages)
{
    std::vector<wxArrayString> data = GetPlatformTableData("magazine_loadout", setupName, magazineLoadoutFields);

	// just check that all items exist for now, TODO need to add weight/quantity check
	wxString matchingTable;
	
	size_t nRows = data.size();
	unsigned int nErrors = 0;
	for (size_t n=0; n<nRows; n++)
	{
		std::string itemName = data[n][0].c_str();
		if (PlatformExistsInTableList(magazineEquipmentTables, itemName, matchingTable))
		{
		}
		else
		{
			nErrors++;
			errorMessages.push_back(wxString::Format("%s setup %s. Item not found: %s",
				databaseClass.c_str(), setupName.c_str(), itemName.c_str()));
		}
	}
	
	return (nErrors == 0);
}


/**
* @param beginAgain true to begin another transaction, set false if application is closing
*/
void tcDatabaseManager::Commit(bool beginAgain)
{
    try
    {
        sqlite3x::sqlite3_command sqlCmd(sqlConnection, "COMMIT;");
        sqlCmd.executenonquery();
        changesArePending = false;

        if (beginAgain)
        {
            sqlite3x::sqlite3_command sqlCmdBegin(sqlConnection, "BEGIN IMMEDIATE;");
            sqlCmdBegin.executenonquery();
			
			tcDatabase::Get()->Clear();
			tcDatabase::Get()->ReadWriteSql(&sqlConnection, true);
        }

    }
    catch (sqlite3x::database_error err)
    {
        wxMessageBox(err.what(), "Commit Error");
    }
}

bool tcDatabaseManager::CreateIndices()
{
    try
    {
        if (!IsOpen()) return false;

        wxXmlDocument doc;
        wxString xmlPath("config/table_index.xml");
        if (!doc.Load(xmlPath))
        {
            wxString msg = wxString::Format("tcDatabaseManager::CreateIndices - file not found or corrupt (%s)", xmlPath.c_str());
            wxMessageBox(msg, "Error");
            return false;
        }

        wxXmlNode* root = doc.GetRoot();
        if (root == 0) return false;
        
        wxXmlNode* node = root->GetChildren();
        while (node != 0)
        {
            if (node->GetName() == "table")
            {
                wxString tableName = node->GetPropVal("name", "");
                wxString fieldName = node->GetPropVal("field", "");

                if ((tableName.size() > 0) && (fieldName.size() > 0))
                {
                    changesArePending = true;

                    try
                    {
                        wxString cmdText;
                        cmdText.Printf("DROP INDEX \"%s_autoidx\"", tableName.c_str());
                        sqlite3x::sqlite3_command dropCmd(sqlConnection, cmdText.ToStdString());
                        std::string msg = dropCmd.executestring();
                    }
                    catch (...)
                    {
                        // do nothing
                        wxString s = "Doing nothing";
                    }

                    wxString cmdText;
                    cmdText.Printf("CREATE INDEX %s_autoidx ON %s(%s ASC)",
                        tableName.c_str(), tableName.c_str(), fieldName.c_str());
                    sqlite3x::sqlite3_command sqlCmd(sqlConnection, cmdText.ToStdString());
                    sqlCmd.executenonquery();

                    
                }
            }

            node = node->GetNext();
        }



        return true;


    }
    catch (sqlite3x::database_error err)
    {
        wxMessageBox(err.what(), "Error creating indices");
        return false;
    }
}

bool tcDatabaseManager::DeleteRecord(const wxString& table, const wxString& databaseClass, const wxString& additionalConstraint)
{
    std::map<wxString, int>::const_iterator iter = 
        tableRenameTypes.find(table);

    int tableType = DEFAULT_TABLE;   
    
    if (iter != tableRenameTypes.end())
    {
        tableType = iter->second;
    }

    std::vector<wxString> tableList;

    switch (tableType)
    {
    case PLATFORM_TABLE:
        tableList.push_back(table);
        tableList.push_back("platform_launcher");
        tableList.push_back("platform_magazine");
        tableList.push_back("platform_sensor");
        tableList.push_back("platform_names");
        tableList.push_back("platform_setup");
        break;
    default:
        tableList.push_back(table);
        break;
    }

    for (size_t n=0; n<tableList.size(); n++)
    {
        wxString command = wxString::Format("delete from %s where DatabaseClass=\"%s\"", tableList[n].c_str(), databaseClass.c_str());
        if (additionalConstraint.size() > 0)
        {
            command += " and ";
            command += additionalConstraint;
        }
        sqlite3_command sqlCmd(sqlConnection, command.ToStdString());
        sqlCmd.executenonquery();
        
        changesArePending = true;
    }

    return true;
}


bool tcDatabaseManager::DuplicateRecord(const wxString& table, const wxString& databaseClass, const wxString& copyName)
{
    std::map<wxString, int>::const_iterator iter = 
        tableRenameTypes.find(table);

    int tableType = DEFAULT_TABLE;

    if (iter != tableRenameTypes.end())
    {
        tableType = iter->second;
    }

	bool duplicateSetups = false;

    std::vector<wxString> tableList;

    switch (tableType)
    {
    case PLATFORM_TABLE:
        tableList.push_back(table);
        tableList.push_back("platform_launcher");
        tableList.push_back("platform_magazine");
        tableList.push_back("platform_sensor");
        tableList.push_back("platform_names");
		duplicateSetups = true;
        break;
    default:
        tableList.push_back(table);
        break;
    }

    for (size_t n=0; n<tableList.size(); n++)
    {
        wxString command = wxString::Format("select * from %s where DatabaseClass=\"%s\";", tableList[n].c_str(), databaseClass.c_str());
        sqlite3_command selectCommand(sqlConnection, command.ToStdString());
        sqlite3_reader results = selectCommand.executereader();

        wxString s;

        wxArrayString valuesArray;

        while (results.read())
        {
            int nCols = results.GetNumberCols();
            wxString valuesString = wxString("\"") + copyName + wxString("\"");
            for (int m=1;m<nCols;m++)
            {
                valuesString += ",\"";
                valuesString += wxString(results.getstring(m).c_str());
                valuesString += "\"";
            }
            valuesArray.push_back(valuesString);
        }

        for (size_t k=0; k<valuesArray.size(); k++)
        {
            command = wxString::Format("insert into %s values (%s);", tableList[n].c_str(), valuesArray[k].c_str());
            sqlite3_command insertCommand(sqlConnection, command.ToStdString());
            try
            {
                insertCommand.executenonquery();
                changesArePending = true;
            }
            catch (sqlite3x::database_error err)
            {
                wxMessageBox(err.what(), "Database Error");
            }
        }

    }

	if (duplicateSetups)
	{
		wxString command = wxString::Format("select * from platform_setup where DatabaseClass=\"%s\";", databaseClass.c_str());
        sqlite3_command selectCommand(sqlConnection, command.ToStdString());
        sqlite3_reader results = selectCommand.executereader();

		int setupNumber = 1;
        wxArrayString valuesArray;
        while (results.read())
        {
            int nCols = results.GetNumberCols();
			wxASSERT(nCols == 7);
			
			wxString setupName(results.getstring(1).c_str());
			wxString initialYear(results.getstring(2).c_str());
			wxString finalYear(results.getstring(3).c_str());
			wxString airComplement(results.getstring(4).c_str());
			wxString magazineLoadout(results.getstring(5).c_str());
			wxString launcherLoadout(results.getstring(6).c_str());


            wxString valuesString;
			valuesString.Printf("\"%s\",\"%s-%d\",\"%s\",\"%s\",\"%s-%d-A\",\"%s-%d-M\",\"%s-%d-L\"", copyName.c_str(), copyName.c_str(), setupNumber,
				initialYear.c_str(), finalYear.c_str(),
				copyName.c_str(), setupNumber,
				copyName.c_str(), setupNumber,
				copyName.c_str(), setupNumber);

            valuesArray.push_back(valuesString);

			DuplicateRecord("air_complement", airComplement, wxString::Format("%s-%d-A", copyName.c_str(), setupNumber));
			DuplicateRecord("magazine_loadout", magazineLoadout, wxString::Format("%s-%d-M", copyName.c_str(), setupNumber));
			DuplicateRecord("launcher_loadout", launcherLoadout, wxString::Format("%s-%d-L", copyName.c_str(), setupNumber));

			setupNumber++;
        }

		for (size_t k=0; k<valuesArray.size(); k++)
        {
            command = wxString::Format("insert into platform_setup values (%s);", valuesArray[k].c_str());
            sqlite3_command insertCommand(sqlConnection, command.ToStdString());
            try
            {
                insertCommand.executenonquery();
                changesArePending = true;
            }
            catch (sqlite3x::database_error err)
            {
                wxMessageBox(err.what(), "Database Error");
            }
        }

	}

    return true;
}

const wxArrayString& tcDatabaseManager::ExecuteQuery(const wxString& query)
{
    static wxArrayString result;
    result.clear();

    if (!IsOpen()) return result;

    try
    {
        sqlite3_command sqlCmd(sqlConnection, query.ToStdString());
        sqlite3_reader results = sqlCmd.executereader();

        wxString s;

        while (results.read())
        {
            wxString s(results.getstring(0).c_str());
            result.push_back(s);
        }

        return result;
    }
    catch (...)
    {
        return result;
    }

}

sqlite3_connection& tcDatabaseManager::GetConnection()
{
    return sqlConnection;
}

/**
* @return vector of distinct values that occur in specified field, database class and table
*/
const std::vector<int> tcDatabaseManager::GetIdList(const wxString& table, const wxString& databaseClass, const wxString& field)
{
    static std::vector<int> idList;

    idList.clear();

    if (!IsOpen()) return idList;

    wxString command = wxString::Format("select distinct %s from %s where DatabaseClass=\"%s\";", field.c_str(), table.c_str(), databaseClass.c_str());
    try
    {
        sqlite3_command sqlCmd(sqlConnection, command.ToStdString());
        sqlite3_reader results = sqlCmd.executereader();

        wxString s;

        while (results.read())
        {
            wxString val(results.getstring(0).c_str());
            long nval = -1;
            if (val.ToLong(&nval))
            {
                idList.push_back(int(nval));
            }
        }

        return idList;
    }
    catch (...)
    {
        return idList;
    }
}

const wxString& tcDatabaseManager::GetCountry(const wxString& databaseClass)
{
	static wxString countryName;
	countryName.clear();

	tcDatabaseObject* data = tcDatabase::Get()->GetObject(databaseClass.ToStdString());
	if (tcPlatformDBObject* platformData = dynamic_cast<tcPlatformDBObject*>(data))
	{
		countryName = platformData->country.c_str();
	}

	return countryName;
}

/**
* Generalized version of GetPlatformList that returns unique list of records in table
*/
const wxArrayString& tcDatabaseManager::GetGeneralList(const wxString& table, const wxString& field, const wxString& constraint)
{
	static wxArrayString recordNames;

    recordNames.clear();

    if (!isOpen) return recordNames;


    wxString command;
    if (constraint.size() == 0)
    {
        command.Printf("select distinct %s from %s;", field.c_str(), table.c_str());
    }
    else
    {
        command.Printf("select distinct %s from %s %s;", field.c_str(), table.c_str(), constraint.c_str());
    }

    sqlite3_command sqlCmd(sqlConnection, command.ToStdString());
    sqlite3_reader results = sqlCmd.executereader();

    wxString s;

    while (results.read())
    {
        recordNames.push_back(wxString(results.getstring(0).c_str()));
    }

    recordNames.Sort();

    return recordNames;
}

const wxArrayString& tcDatabaseManager::GetPlatformList(const wxString& platformTable, const wxString& constraint)
{
    static wxArrayString platforms;

    platforms.clear();

    if (!isOpen) return platforms;

    wxString field("DatabaseClass");

    wxString command;
    if (constraint.size() == 0)
    {
        command.Printf("select distinct %s from %s;", field.c_str(), platformTable.c_str());
    }
    else
    {
        command.Printf("select distinct %s from %s %s;", field.c_str(), platformTable.c_str(), constraint.c_str());
    }

    sqlite3_command sqlCmd(sqlConnection, command.ToStdString());
    sqlite3_reader results = sqlCmd.executereader();

    wxString s;

    while (results.read())
    {
        platforms.push_back(wxString(results.getstring(0).c_str()));
    }

    platforms.Sort();

    return platforms;
}

/**
* Add date range to each name entry, if available
*/
const wxArrayString& tcDatabaseManager::GetPlatformListAnnotated(const wxString& platformTable, const wxString& constraint)
{
	static wxArrayString platformList;
	platformList.clear();

	int tableType = DEFAULT_TABLE;

    std::map<wxString, int>::const_iterator iter = 
        tableRenameTypes.find(platformTable);

    if (iter != tableRenameTypes.end())
    {
        tableType = iter->second;
    }

	platformList = GetPlatformList(platformTable, constraint);

	if ((platformTable == "sonobuoy") || ((tableType != PLATFORM_TABLE) && (tableType != LAUNCHER_EQUIPMENT_TABLE)))
	{
		return platformList;
	}

	// add InitialYear FinalYear info to each line
	for (size_t n=0; n<platformList.size(); n++)
	{

		wxString command;

		command.Printf("select DatabaseClass,InitialYear,FinalYear from %s where DatabaseClass=%s;", 
			platformTable.c_str(), platformList[n].c_str());

		sqlite3_command sqlCmd(sqlConnection, command.ToStdString());
		sqlite3_reader results = sqlCmd.executereader();

		wxString s;

		if (results.read())
		{
			platformList[n] = wxString::Format("%s (%s-%s)", 
				platformList[n].c_str(), results.getstring(1).c_str(), results.getstring(2).c_str());
		}
	}


	return platformList;
}


const std::vector<wxArrayString>& tcDatabaseManager::GetPlatformTableData(const wxString& table, const wxString& databaseClass, const wxArrayString& fieldList,
                                                                          const wxString additionalConstraint)
{
    static std::vector<wxArrayString> tableData;
    tableData.clear();

    if (!isOpen) return tableData;

    wxString fields;
    for (size_t n=0; n<fieldList.size(); n++)
    {
        fields += fieldList[n];
        if ((n+1)<fieldList.size()) fields += ",";
    }

    wxString field("DatabaseClass");
    wxString command = wxString::Format("select %s from %s where DatabaseClass=\"%s\"", fields.c_str(), table.c_str(), databaseClass.c_str());
    if (additionalConstraint.size() > 0)
    {
        command += " and ";
        command += additionalConstraint;
    }
    sqlite3_command sqlCmd(sqlConnection, command.ToStdString());

    try
    {
        sqlite3_reader results = sqlCmd.executereader();

        while (results.read())
        {
            wxArrayString row;
            for (size_t n=0; n<fieldList.size(); n++)
            {
                row.push_back(results.getstring(int(n)).c_str());
            }
            tableData.push_back(row);
        }
    }
    catch (sqlite3x::database_error err)
    {
        wxMessageBox(err.what(), "Database Error");
    }

    return tableData;
}



/**
* @return list of DatabaseClass values for cases where field matches value
*/
const wxArrayString& tcDatabaseManager::GetReferences(const wxString& table, const wxString& field, const wxString& value)
{
    static wxArrayString references;

    references.clear();

    wxString command = wxString::Format("select DatabaseClass from %s where %s = \"%s\"", table.c_str(), field.c_str(), value.c_str());
    sqlite3_command sqlCmd(sqlConnection, command.ToStdString());

    try
    {
        sqlite3_reader results = sqlCmd.executereader();

        while (results.read())
        {
            references.push_back(results.getstring(0).c_str());
        }
    }
    catch (sqlite3x::database_error err)
    {
        wxMessageBox(err.what(), "Database Error");
    }


    return references;
}


void tcDatabaseManager::Init()
{
    //enum {
    //    PLATFORM_TABLE = 1, 
    //    SENSOR_TABLE = 2, 
    //    LAUNCHER_EQUIPMENT_TABLE = 3, 
    //    STORES_TABLE = 4, 
    //    };

    tableRenameTypes["air"] = PLATFORM_TABLE;
    tableRenameTypes["ground"] = PLATFORM_TABLE;
    tableRenameTypes["ship"] = PLATFORM_TABLE;
    tableRenameTypes["simpleair"] = PLATFORM_TABLE;
    tableRenameTypes["sonobuoy"] = PLATFORM_TABLE;
    tableRenameTypes["sub"] = PLATFORM_TABLE;


    tableRenameTypes["ecm"] = SENSOR_TABLE;
    tableRenameTypes["esm"] = SENSOR_TABLE;
    tableRenameTypes["optical"] = SENSOR_TABLE;
    tableRenameTypes["radar"] = SENSOR_TABLE;
    tableRenameTypes["sonar"] = SENSOR_TABLE;

    tableRenameTypes["ballistic"] = LAUNCHER_EQUIPMENT_TABLE;
    tableRenameTypes["torpedo"] = LAUNCHER_EQUIPMENT_TABLE;
    tableRenameTypes["missile"] = LAUNCHER_EQUIPMENT_TABLE;
	tableRenameTypes["ballistic_missile"] = LAUNCHER_EQUIPMENT_TABLE;

    tableRenameTypes["stores"] = DEFAULT_TABLE;



    aircraftTables.push_back("air");
    aircraftTables.push_back("simpleair");

	platformTables.push_back("air");
	platformTables.push_back("simpleair");
	platformTables.push_back("ship");
	platformTables.push_back("sub");
	platformTables.push_back("ground");

    launcherEquipmentTables.push_back("ballistic");
    launcherEquipmentTables.push_back("ballistic_missile");
    launcherEquipmentTables.push_back("torpedo");
    launcherEquipmentTables.push_back("missile");
    launcherEquipmentTables.push_back("cm");
    launcherEquipmentTables.push_back("sonobuoy");
    launcherEquipmentTables.push_back("fueltank");

	magazineEquipmentTables = launcherEquipmentTables;
	magazineEquipmentTables.push_back("item");

    setupFields.push_back("SetupName");
    setupFields.push_back("InitialYear");
    setupFields.push_back("FinalYear");
    setupFields.push_back("AirComplement");
    setupFields.push_back("MagazineLoadout");
    setupFields.push_back("LauncherLoadout");

    launcherFields.push_back("Item");
    launcherFields.push_back("Quantity");
    launcherFields.push_back("LauncherId");

    magazineLoadoutFields.push_back("Item");
    magazineLoadoutFields.push_back("Quantity");
    magazineLoadoutFields.push_back("MagazineId");


	aircraftFields.push_back("FuelCapacity_kg");
	aircraftFields.push_back("MaxTakeoffWeight_kg");
	aircraftFields.push_back("Weight_kg");

	itemFields.push_back("Weight_kg");

	fueltankFields.push_back("FuelCapacity_kg");

}

double tcDatabaseManager::DateTimeToFloatYear(const wxDateTime& dt) const
{
	double result = 0;

	// convert back to floating point year
	result = double(dt.GetYear());
	if (wxDateTime::IsLeapYear(dt.GetYear()))
	{
		result += (double(dt.GetDayOfYear()) - 0.5) / 366.0;
	}
	else
	{
		result += (double(dt.GetDayOfYear()) - 0.5) / 365.0;
	}

	return result;
}


bool tcDatabaseManager::IsOpen() const
{
    return isOpen;
}

bool tcDatabaseManager::IsWithinDateRange(const wxString& s, const wxDateTime& startFilterDate, const wxDateTime& endFilterDate)
{
	static unsigned long errorCount = 0;

	double startDate = DateTimeToFloatYear(startFilterDate);
	double endDate = DateTimeToFloatYear(endFilterDate);

	tcDatabase* database = tcDatabase::Get();
	bool dynamicLoad = database->IsUsingDynamicLoad();

	tcDatabaseObject* data = database->GetObject(s.ToStdString());
	if (data != 0)
	{
		return (data->initialYear <= endDate) && (data->finalYear >= startDate);
	}
	else
	{
		return true; // changed this 15DEC2013 to keep non tcDatabaseObject tables from disappearing
		//if (errorCount++ <= 1)
		//{
		//	wxASSERT(false);
		//}
		//return false;
	}
}

bool tcDatabaseManager::Open(const std::string& inFile)
{
    try
    {
        if (isOpen)
        {
            sqlConnection.close();
        }

        BackupFile(inFile);

        sqlConnection.open(inFile.c_str());

        sqlite3x::sqlite3_command sqlCmdBegin(sqlConnection, "BEGIN IMMEDIATE;");
        sqlCmdBegin.executenonquery();

        isOpen = true;
        changesArePending = false;

		tcDatabase::Get()->ReadWriteSql(&sqlConnection, true);

        return true;
    }
    catch (...)
    {
        isOpen = false;
        changesArePending = false;
        return false;
    }
}

bool tcDatabaseManager::PlatformExistsInTable(const wxString& platformTable, const wxString& platformName)
{
    if (!isOpen) return false;

    wxString field("DatabaseClass");
    wxString command = wxString::Format("select * from %s where DatabaseClass=\"%s\";", platformTable.c_str(), platformName.c_str());
    sqlite3_command sqlCmd(sqlConnection, command.ToStdString());
    sqlite3_reader results = sqlCmd.executereader();

    wxString s;

    if (results.read())
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool tcDatabaseManager::PlatformExistsInTableList(const wxArrayString& platformTableList, const wxString& platformName, wxString& matchingTable)
{
    for (size_t n=0; n<platformTableList.size(); n++)
    {
        wxString table = platformTableList[n];
        if (PlatformExistsInTable(table, platformName))
        {
            matchingTable = table;
            return true;
        }
    }

    matchingTable.clear();

    return false;
}

/**
* Reads fields for objects derived from tcDatabaseClass or that have a DatabaseClass column as text primary key
*/
const wxArrayString& tcDatabaseManager::ReadDatabaseObjectFields(const wxString& table, const wxString& databaseClass, const wxArrayString& fieldList)
{
    static wxArrayString fields;
    fields.clear();

    if ((!isOpen) || (fieldList.size() == 0)) return fields;

    wxString columnDefinition;
    for (size_t k=0; k<fieldList.size(); k++)
    {
        columnDefinition += fieldList[k];
        if ((k+1) < fieldList.size()) columnDefinition += ",";
    }

	if (databaseClass.size() == 0)
	{
		return fields; // to keep "not an error" from being thrown below
	}

    wxString command = wxString::Format("select %s from %s where DatabaseClass=\"%s\";", 
        columnDefinition.c_str(), table.c_str(), databaseClass.c_str());

    try
    {   
        sqlite3_command sqlCmd(sqlConnection, command.ToStdString());
        sqlite3_reader results = sqlCmd.executereader();

        if (results.read())
        {
            for (size_t k=0; k<fieldList.size(); k++)
            {
                fields.push_back(results.getstring(k).c_str());
            }
        }

        wxASSERT(!results.read()); // should only be one result for unique DatabaseClass
    }
    catch (sqlite3x::database_error err)
    {
        wxMessageBox(err.what(), "ReadDatabaseObjectFields Error");
        throw std::exception("ReadDatabaseObjectFields Error");
    }

    return fields;
}

/**
* @return true if rename successful
*/
bool tcDatabaseManager::RenameRecord(const wxString& table, const wxString& originalName, const wxString& newName)
{
    std::map<wxString, int>::const_iterator iter = 
        tableRenameTypes.find(table);

    int tableType = DEFAULT_TABLE;

    if (iter != tableRenameTypes.end())
    {
        tableType = iter->second;
    }

    std::vector<wxString> tableList;

    switch (tableType)
    {
    case PLATFORM_TABLE:
        tableList.push_back(table);
        tableList.push_back("platform_launcher");
        tableList.push_back("platform_magazine");
        tableList.push_back("platform_sensor");
        tableList.push_back("platform_names");
        tableList.push_back("platform_setup");
        break;
    default:
        tableList.push_back(table);
        break;
    }

    for (size_t n=0; n<tableList.size(); n++)
    {
        wxString command = wxString::Format("update %s set DatabaseClass=\"%s\" where DatabaseClass=\"%s\";", tableList[n].c_str(), newName.c_str(), originalName.c_str());
        sqlite3_command sqlCmd(sqlConnection, command.ToStdString());
        sqlCmd.executenonquery();
        changesArePending = true;
    }

    return true;
}

void tcDatabaseManager::TestTemporaryLoad()
{
	if (!isOpen) return;

	/*tcDatabase* database = tcDatabase::Get();
	tcDBObjSerializerSql<tcSonarDBObject> serializer(database, sqlConnection, "sonar");

	tcSonarDBObject* sonar = serializer.LoadRecordTemporary("AQS-13B");
	delete sonar;*/

}

void tcDatabaseManager::UpdateDatabaseObject(const wxString& table, const wxString& databaseClass, const wxArrayString& fieldList, const wxArrayString& valueList)
{
    wxASSERT(fieldList.size() == valueList.size());
    wxString setExpression;

    for (size_t n=0; n<fieldList.size(); n++)
    {
        setExpression += wxString::Format("%s=\"%s\"", fieldList[n].c_str(), valueList[n].c_str());
        if ((n+1)<fieldList.size()) setExpression += ",";
    }

    try
    {
        wxString command = wxString::Format("update %s set %s where DatabaseClass=\"%s\";", 
            table.c_str(), setExpression.c_str(), databaseClass.c_str());
        sqlite3_command sqlCmd(sqlConnection, command.ToStdString());
        sqlCmd.executenonquery();
        changesArePending = true;

		tcDatabase::Get()->ReloadRecord(databaseClass.c_str());
    }
    catch (sqlite3x::database_error err)
    {
        wxString caption = wxString::Format("Update of %s failed", databaseClass.c_str());
        wxMessageBox(err.what(), caption);
    }

}

/**
* Updates platform tables like platform_launcher, platform_sensor, platform_magazine
* Deletes existing entries and then inserts updated data
*/
void tcDatabaseManager::UpdatePlatformTableData(const wxString& table, const wxString& databaseClass, const wxArrayString& fieldList,
         const std::vector<wxArrayString>& tableData, const wxString& additionalConstraint)
{
    if (!isOpen) return;

    try
    {
        wxString command = wxString::Format("delete from %s where DatabaseClass=\"%s\"", table.c_str(), databaseClass.c_str());
        if (additionalConstraint.size() > 0)
        {
            command += " and ";
            command += additionalConstraint;
        }
        sqlite3_command sqlCmd(sqlConnection, command.ToStdString());
        sqlCmd.executenonquery();
        changesArePending = true;

        wxString fields("DatabaseClass,");
        for (size_t n=0; n<fieldList.size(); n++)
        {
            fields += fieldList[n];
            if ((n+1)<fieldList.size()) fields += ",";
        }

        size_t nColumns = fieldList.size();
        for (size_t row=0; row<tableData.size(); row++)
        {
            wxASSERT(tableData[row].size() == nColumns);

            wxString values = wxString("\"") + databaseClass + wxString("\",");
            for (size_t n=0; n<nColumns; n++)
            {
                wxString value_n = wxString("\"") + tableData[row][n] + wxString("\"");
                values += value_n;
                if ((n+1) < nColumns) values += ",";
            }

            wxString command2 = wxString::Format("insert into %s (%s) values (%s)", table.c_str(), fields.c_str(), values.c_str());
            sqlite3_command sqlCmd2(sqlConnection, command2.ToStdString());
            sqlCmd2.executenonquery();
        }

		tcDatabase::Get()->ReloadRecord(databaseClass.c_str());

    }
    catch (sqlite3x::database_error err)
    {
        wxMessageBox(err.what(), "Database Error");
    }


}


tcDatabaseManager::tcDatabaseManager()
: isOpen(false),
  changesArePending(false)
{
    Init();
}

tcDatabaseManager::~tcDatabaseManager()
{
    Close();
}