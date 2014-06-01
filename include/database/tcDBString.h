/*
**  @file tcDBString.h
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

#ifndef _DBSTRING_H_
#define _DBSTRING_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "tcPool.h"
#include "tcString.h" // CString replacement
#include "tcFile.h"  // CFile replacement



class tcStream;

namespace database 
{
    /** 
    * Rewritten to wrap wxString to fix problems with database name
    * truncation.
    */
    class tcDBString 
    {
    public:
        enum {ERROR_SIZE = 255};

        void AssignRandomString();
        void AssignRandomStringB();
        void AssignRandomSuffix(); // adds random suffix to existing string
		const char* c_str() const;
        size_t size() const;

        tcDBString& operator= (const tcDBString& c);
        tcDBString& operator= (const char* s);
        tcDBString& operator+=(const char* s);
        int operator== (tcDBString&) const;
        bool operator== (const char* s) const;

        tcStream& operator<<(tcStream& stream);
        tcStream& operator>>(tcStream& stream);

        int Serialize(tcFile& file, bool mbLoad);
        tcDBString();
        tcDBString(const char *buff);
		tcDBString(const tcDBString& src);
        ~tcDBString();
    private:
        wxString str;
    };
    
} // namespace database

#endif


