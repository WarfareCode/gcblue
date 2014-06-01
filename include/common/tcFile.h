/**
* @file tcFile.h
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

#ifndef _TCFILE_H_
#define _TCFILE_H_ 

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <stdio.h>
#include "tcString.h"

class tcFile
{
public:
   enum 
   {
      modeCreate = 1,
      modeWrite = 2,
      modeRead = 4,
      modeText = 8,
      begin = 16,
      current = 32
   };
   int Open(const char *azFileName, unsigned int anFlags);
   int Open(tcString& s, unsigned int anFlags) {return Open(s.GetBuffer(), anFlags);}
   int Close(void);
   long GetLength(); ///< size of file in bytes
   long GetLengthFromCurrent(); ///< size from current pos to end of file in bytes
   bool IsOpen() const;
   int Read(void *apData, unsigned int anCount); ///< TODO add operator>> for this 
   int ReadString(char *s);
   int ReadString(tcString& s);
   int Seek(int offset, unsigned int origin);
   int SeekToBegin() {return Seek(0, tcFile::begin);}
   int Write(const void *apData, unsigned int anCount); ///< TODO add operator<< for this 
   void WriteString(const char *azString);
   void Printf(const char* formatString, ...);

   tcFile();
   tcFile(const std::string& fileName);
   virtual ~tcFile();
private:
   FILE *mpFile;
};

#endif // _TCFILE_H_
