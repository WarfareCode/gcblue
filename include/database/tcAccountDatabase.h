/** 
**  @file tcAccountDatabase.h
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

#ifndef _ACCOUNTDATABASE_H_
#define _ACCOUNTDATABASE_H_

#include <map>
#include <string>

class CMD5;

namespace sqlite3x
{
	class sqlite3_connection;
}

/**
* Interface to account database. Currently this mixes the database interface with
* game-related use of data. Eventually may want to separate this.
*/
class tcAccountDatabase
{
public:
	/// status codes
    enum
    {
        SUCCESS = 0,
        USER_NOT_FOUND = 1,
        PASSWORD_INVALID = 2,
        DUPLICATE_USER = 3,
        DUPLICATE_LOGIN = 4,
		INSUFFICIENT_PERMISSION = 5,
		UNKNOWN_ERROR = 99
    };

	struct UserData
	{
		/// permission flags
		enum
		{
			ALLIANCE_SWITCH = 1, ///< allows user to switch alliance at any time
			PLATFORM_CONTROL = 2, ///< allows user to take control of entities
		};

		std::string username;
		std::string password_hash;
		std::string email;
		std::string last_ip;
		unsigned int login_count;
		unsigned long last_login; ///< seconds since Jan 1, 1970
		unsigned long last_logout; ///< seconds since Jan 1, 1970
		unsigned int alliance; ///< 0 for no alliance selected
		float score;
		int flags; ///< permission flags

		bool CanControlPlatforms() const {return (flags & PLATFORM_CONTROL) != 0;}
		bool CanSwitchAlliance() const {return (flags & ALLIANCE_SWITCH) != 0;}
	};
    
    /// Add new user to account database
    int AddUser(const std::string& user, const std::string& hash,
                const std::string& email);
    
    /// @return SUCCESS if user is authenticated, otherwise error code
    int AuthenticateUser(const std::string& user, const std::string& hash);

	std::string ErrorCodeToString(int code);

	bool GetUserData(const std::string& user, UserData& userData);

	/// loads user to cachedUserData (if nessessary) and returns reference
	UserData& GetCachedUserData(const std::string& user);

	bool IsUserLoggedIn(const std::string& user);
    
    /// Call once at login to update database with login info for user
    int LogIn(const std::string& user, const std::string ipAddress);
    
    /// Call once to log out user
    int LogOut(const std::string& user);
    
	int LookupFieldIndex(const std::string& field);

	/// @return SUCCESS if alliance changed, otherwise error code
	int SetUserAlliance(const std::string& user, unsigned int alliance); 

	/// Updates all fields of database entry (user name cannot be changed this way)
	int UpdateDatabaseEntry(UserData& userData);

	const char* GetMD5digest(const char* plainText);
    const char* GetMD5digest(const std::string& plainText);

	static tcAccountDatabase* Get(); ///< singleton instance accessor
private:
    sqlite3x::sqlite3_connection* accountDatabase;
	std::map<std::string, unsigned int> columnLookup; // for faster access of data 
	CMD5* md5;
	UserData cachedUserData; ///< all columns from last read are stored in this structure

	const std::string databasePath;
	const std::string tableName;

	void Initialize(); ///< open connection to database and initialize columnLookup
	void TestUpdate();

	tcAccountDatabase();
	~tcAccountDatabase();
        
};

#endif
