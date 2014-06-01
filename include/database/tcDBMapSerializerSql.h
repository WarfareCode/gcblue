/**
**  @file tcDBMapSerializerSql.h
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

#ifndef _DBMAPSERIALIZERSQL_H_
#define _DBMAPSERIALIZERSQL_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "tcDatabase.h"
#include <iostream>
#include <fstream>
#include <string>
#include "sqlite/sqlite3x.hpp"
#include "database/tcSqlReader.h"

#include <wx/wx.h>
#ifdef WIN32
#include <wx/msw/private.h> // for MS Windows specific definitions
#endif

using sqlite3x::sqlite3_reader;
using sqlite3x::sqlite3_command;
using sqlite3x::sqlite3_connection;


/** 
* Generalized version of tcDBObjSerializerSql
*
* Saves/loads objects of class T with std::map<std::string, T*> 
* Class T is any class with GetName(), AddSqlColumns(), ReadSql(), WriteSql()
*
* SQL version of serializer to work with sqlite3 and sqlite3_plus
* C++ wrapper
*/
namespace database
{

	template <class T> 
	class tcDBMapSerializerSql
	{
	public:
        tcDBMapSerializerSql(tcDatabase* db, std::map<std::string, T*>& m, 
            sqlite3x::sqlite3_connection& con, std::string s)
			: database(db), dataMap(m), sqlConn(con), tableName(s) {}
			bool Load();
			bool Save();
	private:
		tcDatabase* database;
        std::map<std::string, T*>& dataMap;
		std::string tableName;
		sqlite3x::sqlite3_connection& sqlConn;

	};


	template <class T>
		bool tcDBMapSerializerSql<T>::Load()
	{ 

		try
		{
			// check if the table exists, abort if it doesn't
			wxString command = wxString::Format("select count(*) from sqlite_master where name='%s';",
				tableName.c_str());
			string countStr = sqlConn.executestring(command.ToAscii());

			if (countStr == "0")
			{
				wxString message = wxString::Format(
					"tcDBMapSerializerSql<T>::Load() table (%s) not found\n",
					tableName.c_str());

				wxMessageBox(message.GetData(), "Error", wxICON_ERROR);
				return false;
			}

		}
		catch (exception& ex)
		{
			wxMessageBox(ex.what(), "Error", wxICON_ERROR);
			return false;
		}



		try
		{
			wxString command = wxString::Format("pragma table_info(%s);", tableName.c_str());
			sqlite3_command sqlCmd(sqlConn, command.ToAscii());

			sqlite3_reader tableInfo = sqlCmd.executereader();

			command = wxString::Format("select * from %s;", tableName.c_str());

			sqlite3_command sqlCmd2(sqlConn, command.ToAscii());
			sqlite3_reader tableData = sqlCmd2.executereader();

			tcSqlReader sqlReader(tableInfo, tableData);

			while (sqlReader.Read())
			{
				T* obj = new T;
				obj->ReadSql(sqlReader);
                
                // if the obj already exists, delete the old and add the new (update)
                // (doesn't work for duplicates within database since BuildDictionaries needs to be called)
                const std::string& s = obj->GetName();
                std::map<std::string, T*>::iterator iter = dataMap.find(s);
                if (iter != dataMap.end())
                {
                    fprintf(stdout, "Updating database map class: %s\n", obj->GetName());
                    T* oldObj = iter->second;
                    wxASSERT(oldObj != 0);
                    
                    delete oldObj;
                    dataMap.erase(iter);
                }

                dataMap[s] = obj;
			}

			tableInfo.close();
			tableData.close();

		}
		catch (exception& ex)
		{
			wxMessageBox(ex.what(), "Error", wxICON_ERROR);
			return false;
		}

		return true;
	}





	/**
	* This version starts from a clean slate, first erasing the table
	* in the database if it exists.
	*/
	template <class T>
		bool tcDBMapSerializerSql<T>::Save()
	{

		try
		{
			// delete table if it exists
			wxString command = wxString::Format("select count(*) from sqlite_master where name='%s';", 
				tableName.c_str());
			string countStr = sqlConn.executestring(command.ToAscii());


			if (countStr != "0")
			{
				command = wxString::Format("drop table %s;", tableName.c_str());
				sqlConn.executenonquery(command.ToAscii());
			}


			std::string columnString;
			T::AddSqlColumns(columnString);

#ifdef _DEBUG
			fprintf(stdout, "column str: (%s)\n", columnString.c_str());
#endif
			command = wxString::Format("create table %s (%s);", 
				tableName.c_str(), columnString.c_str());
			sqlConn.executenonquery(command.ToAscii());
		}
		catch(exception &ex) 
		{
			wxString message = wxString::Format("Database error in table %s: %s",
				tableName.c_str(), ex.what());
			wxMessageBox(message.GetData(), "Error", wxICON_ERROR);
		}

        // size_t nEntries = dataMap.size();
        std::map<std::string, T*>::const_iterator iter = dataMap.begin();


		for (;iter!=dataMap.end();++iter)
        {
            T* obj = iter->second;
            wxASSERT(obj != 0);

            try
            {
                std::string valueString;
                obj->WriteSql(valueString);

#ifdef _DEBUG
                fprintf(stdout, "value str: (%s)\n", valueString.c_str());
#endif
                wxString command = wxString::Format("insert into %s values (%s);",
                    tableName.c_str(), valueString.c_str());
                sqlConn.executenonquery(command.ToAscii());
            }
            catch(exception &ex) 
            {
                wxString message = wxString::Format(
                    "Error in table: %s, entry: %s, %s",
                    tableName.c_str(), obj->GetName(), ex.what());
                wxMessageBox(message.GetData(), "Database Error", wxICON_ERROR);
            }



		}


		return true;

	}

} // namespace database

#endif

