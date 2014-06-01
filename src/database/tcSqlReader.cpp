/**  
**  @file tcSqlReader.cpp
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
#include "tcSqlReader.h"
#include "sqlite/sqlite3x.hpp"
#include <stdarg.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

namespace database
{

	/**
	* Builds column lookup std::map
	*/
	void tcSqlReader::BuildColumnLookup(sqlite3x::sqlite3_reader& tableInfo)
	{
		unsigned int fieldCount = 0;


		while(tableInfo.read())
		{
			columnLookup[tableInfo.getstring(1)] = fieldCount++;
		}
	}

	/**
	* throws exception if column <field> not found in map
	* @return data element from column name <field> as double
	*/
	double tcSqlReader::GetDouble(const std::string& field)
	{
		unsigned int index = LookupFieldIndex(field);

		return data.getdouble((int)index);
	}

	/**
	* Version that accepts format string with variable arguments
	* to create field string.
	*/
	double tcSqlReader::GetDouble(const char* fmt, ...)
	{
		va_list argp;
   
		va_start(argp, fmt);
		//vsprintf(buffer, fmt, argp);
        _vsnprintf_s(buffer, sizeof(buffer), _TRUNCATE, fmt, argp);
		va_end(argp);

		return GetDouble(std::string(buffer));
	}

	/**
	* throws exception if column <field> not found in map
	* @return data element from column name <field> as int
	*/
	int tcSqlReader::GetInt(const std::string& field)
	{
		unsigned int index = LookupFieldIndex(field);

		return data.getint((int)index);
	}

	/**
	* Version that accepts format string with variable arguments
	* to create field string.
	*/
	int tcSqlReader::GetInt(const char* fmt, ...)
	{
		va_list argp;
   
		va_start(argp, fmt);
		//vsprintf(buffer, fmt, argp);
        _vsnprintf_s(buffer, sizeof(buffer), _TRUNCATE, fmt, argp);
		va_end(argp);

		return GetInt(std::string(buffer));
	}

	/**
	* throws exception if column <field> not found in map
	* @return data element from column name <field> as int
	*/
	long tcSqlReader::GetLong(const std::string& field)
	{
		unsigned int index = LookupFieldIndex(field);

		return data.getlong((int)index);
	}

	/**
	* Version that accepts format string with variable arguments
	* to create field string.
	*/
	long tcSqlReader::GetLong(const char* fmt, ...)
	{
		va_list argp;
   
		va_start(argp, fmt);
		//vsprintf(buffer, fmt, argp);
        _vsnprintf_s(buffer, sizeof(buffer), _TRUNCATE, fmt, argp);
		va_end(argp);

		return GetLong(std::string(buffer));
	}

	/**
	* throws exception if column <field> not found in map
	* @return data element from column name <field> as string
	*/
	std::string tcSqlReader::GetString(const std::string& field)
	{
		unsigned int index = LookupFieldIndex(field);

		return data.getstring((int)index);
	}

	/**
	* Version that accepts format string with variable arguments
	* to create field string.
	*/
	std::string tcSqlReader::GetString(const char* fmt, ...)
	{
		va_list argp;
   
		va_start(argp, fmt);
		//vsprintf(buffer, fmt, argp);
        _vsnprintf_s(buffer, sizeof(buffer), _TRUNCATE, fmt, argp);
		va_end(argp);

		return GetString(std::string(buffer));
	}


	bool tcSqlReader::GetStringError() const
	{
		return data.getStringError();
	}

	unsigned int tcSqlReader::LookupFieldIndex(const std::string& field)
	{
		static std::string errorMessage;

		std::map<std::string, unsigned int>::const_iterator mapIter;

		mapIter = columnLookup.find(field);
		if (mapIter == columnLookup.end()) 
		{
			errorMessage = wxString::Format("tcSqlReader - field not found (%s)", field.c_str()).c_str();
			throw std::invalid_argument(errorMessage);
		}
		else
		{
			return mapIter->second;
		}
	}


    /**
	* Advance to next row of data
	* @return true if next row is available, false if out of data
	*/
	bool tcSqlReader::Read()
	{
		return data.read();
	}



	tcSqlReader::tcSqlReader(sqlite3x::sqlite3_reader& tableInfo, sqlite3x::sqlite3_reader& _data) 
		: data(_data) 
	{
		BuildColumnLookup(tableInfo);
	}

	tcSqlReader::~tcSqlReader()
	{
	}

}
