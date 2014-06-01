/**  
**  @file tcAccountDatabase.cpp
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
#include "wx/datetime.h"

#include "tcAccountDatabase.h"
#include "sqlite/sqlite3x.hpp"
#include "md5class.h"
#include <sstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


using sqlite3x::sqlite3_command;
using sqlite3x::sqlite3_connection;
using sqlite3x::sqlite3_reader;


tcAccountDatabase* tcAccountDatabase::Get()
{
	static tcAccountDatabase instance;

	return &instance;
}




int tcAccountDatabase::AddUser(const std::string& user, const std::string& hash,
							   const std::string& email)
{
	try
	{
		if (GetUserData(user, cachedUserData))
		{
			return DUPLICATE_USER;
		}
		
		std::string hashStore = "";
		if (hash.size() > 0)
		{
			hashStore = GetMD5digest(hash);
		}

		wxString s = wxString::Format("insert into %s (UserName,PasswordHash,Email) "
			"values (\'%s\',\'%s\',\'%s\');", 
			tableName.c_str(), user.c_str(), hashStore.c_str(), email.c_str());

		accountDatabase->executenonquery(s.ToAscii());

		return SUCCESS;

	}
	catch (std::exception& ex)
	{
		wxMessageBox(ex.what(), "Error", wxICON_ERROR);
		return UNKNOWN_ERROR;
	}

}

/**
* If password is empty in database, store hash as password and return SUCCESS
*/
int tcAccountDatabase::AuthenticateUser(const std::string& user, const std::string& hash)
{
	std::string hashCompare = GetMD5digest(hash);

	if (GetUserData(user, cachedUserData))
	{
		if (cachedUserData.password_hash.size() == 0)
		{
			cachedUserData.password_hash = hashCompare;
			return UpdateDatabaseEntry(cachedUserData);
		}
		else if (cachedUserData.password_hash == hashCompare)
		{
			return SUCCESS;
		}
		else
		{
			return PASSWORD_INVALID;
		}
	}
	else
	{
		return USER_NOT_FOUND;
	}
}

std::string tcAccountDatabase::ErrorCodeToString(int code)
{
	std::string s;

	if (code == SUCCESS)
	{
		s = "Success";
	}
	else if (code == USER_NOT_FOUND)
	{
		s = "Username not found";
	}
	else if (code == PASSWORD_INVALID)
	{
		s = "Invalid password";
	}
	else if (code == DUPLICATE_USER)
	{
		s = "Username already exists";
	}
	else if (code == DUPLICATE_LOGIN)
	{
		s = "User already logged in";
	}
	else
	{
		s = "Unknown error";
	}

	return s;
}

const char* tcAccountDatabase::GetMD5digest(const char* plainText)
{
	md5->setPlainText(plainText);

	return md5->getMD5Digest();
}

const char* tcAccountDatabase::GetMD5digest(const std::string& plainText)
{
	return GetMD5digest(plainText.c_str());
}


bool tcAccountDatabase::GetUserData(const std::string& user, UserData& userData)
{
	wxString command = wxString::Format("select * from %s where UserName='%s';", 
		tableName.c_str(), user.c_str());
	sqlite3_command sqlCmd(*accountDatabase, command.ToAscii());
	sqlite3x::sqlite3_reader tableData = sqlCmd.executereader();


	if (tableData.read())
	{
		userData.username = user;
		userData.alliance = (unsigned int)tableData.getint(LookupFieldIndex("Alliance"));
		userData.email = tableData.getstring(LookupFieldIndex("Email"));
		userData.last_ip = tableData.getstring(LookupFieldIndex("LastIP"));
		userData.last_login = (unsigned long)tableData.getlong(LookupFieldIndex("LastLogin"));
		userData.last_logout = (unsigned long)tableData.getlong(LookupFieldIndex("LastLogout"));
		userData.login_count = (unsigned int)tableData.getint(LookupFieldIndex("LoginCount"));
		userData.password_hash = tableData.getstring(LookupFieldIndex("PasswordHash"));
		userData.score = tableData.getdouble(LookupFieldIndex("Score"));
		userData.flags = tableData.getdouble(LookupFieldIndex("Flags"));
		
		tableData.close(); // VERY important to do this, otherwise prevents future writes to database
		return true;
	}
	else
	{
		userData.username = "";
		tableData.close();
		return false; // user not found, no data available
	}
}


tcAccountDatabase::UserData& tcAccountDatabase::GetCachedUserData(const std::string& user)
{
	if (cachedUserData.username != user)
	{
		GetUserData(user, cachedUserData);
	}

	return cachedUserData;
}

void tcAccountDatabase::Initialize()
{
	wxASSERT(accountDatabase == 0);
	
	try
	{
		accountDatabase = new sqlite3x::sqlite3_connection(databasePath.c_str());

		// build column lookup
		columnLookup.clear();
		wxString command = wxString::Format("pragma table_info(%s);", tableName.c_str());
		sqlite3_command sqlCmd(*accountDatabase, command.ToAscii());
		sqlite3x::sqlite3_reader tableInfo = sqlCmd.executereader();

		unsigned int fieldCount = 0;

		while (tableInfo.read())
		{
			columnLookup[tableInfo.getstring(1)] = fieldCount++;
		}

		md5 = new CMD5;
	}
	catch (std::exception& ex)
	{
		fprintf(stderr, "%s\n", ex.what());
	}

}

bool tcAccountDatabase::IsUserLoggedIn(const std::string& user)
{	
	UserData& data = GetCachedUserData(user);
	if (data.username.size() == 0)
	{   
		return false; // user not found
	}
	return (data.last_login > data.last_logout);
}


int tcAccountDatabase::LogIn(const std::string& user, const std::string ipAddress)
{
	UserData& data = GetCachedUserData(user);
	if (data.username.size() == 0)
	{   
		return USER_NOT_FOUND; // user not found
	}

	wxDateTime now = wxDateTime::Now();
	unsigned long currentTime = now.GetTicks();

	data.last_ip = ipAddress;
	data.last_login = currentTime;
	data.login_count++;

	return UpdateDatabaseEntry(data);
}


int tcAccountDatabase::LogOut(const std::string& user)
{
	UserData& data = GetCachedUserData(user);
	if (data.username.size() == 0)
	{   
		return USER_NOT_FOUND; // user not found
	}

	wxDateTime now = wxDateTime::Now();
	unsigned long currentTime = now.GetTicks();

	data.last_logout = currentTime;

	return UpdateDatabaseEntry(data);
}

/**
* @return index of field or -1 if not found
*/
int tcAccountDatabase::LookupFieldIndex(const std::string& field)
{
	std::map<std::string, unsigned int>::const_iterator mapIter;

	mapIter = columnLookup.find(field);
	if (mapIter == columnLookup.end()) 
	{
		return -1;
	}
	else
	{
		return mapIter->second;
	}
}

int tcAccountDatabase::SetUserAlliance(const std::string& user, unsigned int alliance)
{
	UserData& data = GetCachedUserData(user);
	if (data.username.size() == 0)
	{   
		return USER_NOT_FOUND; // user not found
	}

	data.alliance = alliance;

	return UpdateDatabaseEntry(data);
}


int tcAccountDatabase::UpdateDatabaseEntry(UserData& userData)
{
	std::stringstream valueString;


	valueString << "PasswordHash='" << userData.password_hash << "',";
	valueString << "Email='" << userData.email << "',";
	valueString << "LastIP='" << userData.last_ip << "',";
	valueString << "LastLogin=" << userData.last_login << ",";
	valueString << "LastLogout=" << userData.last_logout << ",";
	valueString << "LoginCount=" << userData.login_count << ",";
	valueString << "Alliance=" << userData.alliance << ",";
	valueString << "Score=" << userData.score << ",";
	valueString << "Flags=" << userData.flags;

	wxString s = wxString::Format("UPDATE OR IGNORE %s SET %s WHERE UserName='%s';",
		tableName.c_str(), valueString.str().c_str(), userData.username.c_str());

	try
	{
		accountDatabase->executenonquery(s.ToAscii());
	}
	catch (std::exception& ex)
	{
		fprintf(stderr, "UpdateDatabaseEntry - %s (%s)\n", ex.what(), s.c_str());
	}

	return SUCCESS;
}


void tcAccountDatabase::TestUpdate()
{
	std::stringstream valueString;

	
	valueString << "PasswordHash='" << "" << "',";
	valueString << "Email='" << "" << "',";
	valueString << "LastIP='" << "192.168.0.9" << "',";
	valueString << "LastLogin=" << 72 << ",";
	valueString << "LastLogout=" << 83 << ",";
	valueString << "LoginCount=" << 5;
	

	wxString s = wxString::Format("UPDATE OR IGNORE %s SET %s WHERE UserName='%s';",
		tableName.c_str(), valueString.str().c_str(), "dewitt");

//	wxString s = wxString::Format("UPDATE OR IGNORE account_info SET PasswordHash='64sdkljlskdjfkjsdlkjf',Email='',LoginCount=5,LastIP='blabbity',LastLogin=72,LastLogout=83 WHERE UserName='dewitt';");
		

	try
	{
		accountDatabase->executenonquery(s.ToAscii());
	}
	catch (std::exception& ex)
	{
		fprintf(stderr, "test UpdateDatabaseEntry - %s (%s)\n", ex.what(), s.ToAscii());
	}
}

tcAccountDatabase::tcAccountDatabase()
:   accountDatabase(0),
    md5(0),
    databasePath("database\\accounts.db"),
	tableName("account_info")
{
	Initialize();
}

tcAccountDatabase::~tcAccountDatabase()

{
	delete accountDatabase;
	delete md5;
}
