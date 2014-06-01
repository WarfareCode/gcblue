/**
**  @file tcDatabaseTable.h
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

#ifndef _DATABASETABLE_H_
#define _DATABASETABLE_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <boost/shared_ptr.hpp>
#include <string>


namespace database
{
	class tcSqlReader;

	/**
	* Template class to hold std::map of T. T should be of tcTableObject type
    */
    template <class T> 
	class tcDatabaseTable
	{
	public:     

        void ReadSql(sqlite3x::sqlite3_connection& sqlConnection, const std::string& tableName);
        const T* GetData(const std::string& databaseClass) const;

        tcDatabaseTable() {}
        ~tcDatabaseTable() {}

    private:
        std::map<std::string, T> tableData;

    };



    template <class T>
    void tcDatabaseTable<T>::ReadSql(sqlite3x::sqlite3_connection& sqlConnection, const std::string& tableName)
    {
        tableData.clear();

        wxString command = wxString::Format("select * from %s;", tableName.c_str());

        sqlite3_command sqlCmd(sqlConnection, command.ToAscii());
        sqlite3_reader reader = sqlCmd.executereader();
        while (reader.read())
        {
            T temp(reader);

            std::string s = temp.GetDatabaseClass();
            tableData[s] = temp;
        }
    }

    template <class T>
    const T* tcDatabaseTable<T>::GetData(const std::string& databaseClass) const
    {
        std::map<std::string, T>::const_iterator iter = 
            tableData.find(databaseClass);

        if (iter != tableData.end())
        {
            return &iter->second;
        }
        else
        {
            return 0;
        }
    }


} // namespace database

#endif

