/*  
**  @file tcString.cpp
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

#include "tcString.h"

int tcString::Delete(int index, int count)
{
    erase(index, count);
    return 1;
}

int tcString::Find(char c, int nStart) 
{
    std::string::size_type idx;

    idx = find(c, nStart);
    if (idx == std::string::npos)
        return -1;
    else
        return (int)idx;
}

int tcString::Find(char* substr, int nStart)
{
    std::string::size_type idx;

    idx = find(substr, nStart);
    if (idx == std::string::npos)
        return -1;
    else
        return (int)idx;
}


void tcString::Format(char *azFormat, ...) {
   enum {STR_LENGTH = 128};
   static char zBuffer[STR_LENGTH];

   va_list arguments;

   va_start( arguments, azFormat);

   _vsnprintf_s(zBuffer, sizeof(zBuffer), _TRUNCATE, azFormat, arguments);
   va_end(arguments);
   *this = zBuffer; // copy to std::string
}

/**
* this ignores length, needs to be fixed, included for compatibility with CString
*/
const char* tcString::GetBufferSetLength(int anMaxLength) 
{
   return c_str();
}

/* untested replacement for MFC CString::Left */
tcString tcString::Left(int n)
{
    tcString s;
    int len = (int)size();

    if (n >= len)
    {
        s = *this;
    }
    else 
    {    
        char zBuff[128];
        strncpy(zBuff,c_str(),n);
        zBuff[n] = 0;
        tcString s = zBuff;
    }
    return s;
}

/* untested replacement for MFC CString::Right */
tcString tcString::Right(int n)
{
    tcString s;
    int len = (int)size();

    if (n >= len)
    {
        s = *this;
    }
    else 
    {    
        char zBuff[128];
        const char *p = c_str();
        strncpy(zBuff,&p[len-n],n);
        zBuff[n] = 0;
        tcString s = zBuff;
    }
    return s;
}




