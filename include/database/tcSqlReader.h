/**
**  @file tcSqlReader.h
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

#ifndef _TCSQLREADER_H_
#define _TCSQLREADER_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include <string>
#include <map>

namespace sqlite3x
{
	class sqlite3_reader;
}

/** 
* Saves/loads objects of class T from database. 
* Class T is any class derived from tcDatabaseObject.
* Class T should be a leaf class for this to work properly.
*
* SQL version of serializer to work with sqlite3 and sqlite3_plus
* C++ wrapper
*/
namespace database
{
	/**
	* Class to wrap SQL sqlite_plus::reader class for reading by
	* column name
	*/
	class tcSqlReader
	{
	public:
		double GetDouble(const std::string& field);
		double GetDouble(const char* fmt, ...); 

		int GetInt(const std::string& field);
		int GetInt(const char* fmt, ...);

		long GetLong(const std::string& field);
		long GetLong(const char* fmt, ...);

		std::string GetString(const std::string& field);
		std::string GetString(const char* fmt, ...);
		
		bool GetStringError() const;

		bool Read();

		tcSqlReader(sqlite3x::sqlite3_reader& tableInfo, sqlite3x::sqlite3_reader& _data);
		~tcSqlReader();
	private:
		std::map<std::string, unsigned int> columnLookup;
		sqlite3x::sqlite3_reader& data; 
		char buffer[128]; ///< internal buffer for formatting column names, watch overrun!

		void BuildColumnLookup(sqlite3x::sqlite3_reader& tableInfo);
		unsigned int LookupFieldIndex(const std::string& field);
	};


} // namespace database

#endif

