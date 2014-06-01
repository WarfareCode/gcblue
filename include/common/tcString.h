/**
* @file tcString.h
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

#ifndef _TCSTRING_H_
#define _TCSTRING_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
#include <stdio.h>
#include <stdarg.h>


// no virtual destructor in std::string, but should be okay to derive since
// there isn't any specialized data in tcString
class tcString : public std::string {
    typedef std::string StdString; // workaround for MSVC 6 bug with scoped base names
public:
    int Delete(int index, int count);
    void Format(char *azFormat, ...);  
    int Find(char c, int nStart=0);
    int Find(char* substr, int nStart=0);
    const char* GetBuffer() {return c_str();}
    const char* GetBufferSetLength(int anMaxLength);
    int GetLength() {return (int)size();}
    tcString Left(int n);
    tcString Right(int n);

    tcString& operator=(const char * s) {StdString::operator=(s);return *this;}
    //tcString& operator=(tcString& s) {StdString::operator=(s);return *this;}
    tcString& operator=(const tcString& s) {StdString::operator=(s);return *this;}
    tcString& operator+=(const char * s) {StdString::operator+=(s);return *this;}
    //tcString& operator+=(tcString& s) {StdString::operator+=(s);return *this;}
    tcString& operator+=(const tcString& s) {StdString::operator+=(s);return *this;}
    tcString() : StdString() {}
    tcString(const char *s) : StdString(s) {}
};

#endif // _TCSTRING_H_

