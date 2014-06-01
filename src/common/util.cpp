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

#include "util.h"


void RemoveWhitespace(tcString& s) {
   unsigned nLength = s.GetLength();
   unsigned nOut = 0;
   const char *inbuffer;
   char outbuffer[255];
   bool bInsideQuotes;

   inbuffer = s.GetBuffer();
   bInsideQuotes = false;
   for(unsigned n=0;n<nLength;n++) {
      if (inbuffer[n]=='"') {
         bInsideQuotes = !bInsideQuotes;
      }
      else if ((inbuffer[n]!=' ')&&(inbuffer[n]!='\t')) {
         outbuffer[nOut++] = inbuffer[n];
      }
   }
   outbuffer[nOut] = 0;
   s = outbuffer;
}

void ReplaceChars(tcString& s, char *azReplaceList, char anReplaceChar) {
   unsigned nLength = s.GetLength();
   unsigned nReplaceList = (unsigned)strlen(azReplaceList);
   const char *inbuffer;
   char outbuffer[255];
   
   inbuffer = s.GetBuffer();

   for(unsigned n=0;n<nLength;n++) {
      outbuffer[n] = inbuffer[n];
      for (unsigned k=0;k<nReplaceList;k++) {
         if (inbuffer[n]==azReplaceList[k]) {
            outbuffer[n] = anReplaceChar;
         }
      }
   }
   outbuffer[nLength] = 0;
   s = outbuffer;
}

void ExtractFromQuotes(tcString& s) {
   unsigned nLength = s.GetLength();
   unsigned nOut = 0;
   const char *inbuffer;
   char outbuffer[255];
   bool bInsideQuotes,bContinueParse;

   inbuffer = s.GetBuffer();
   bInsideQuotes = false;
   bContinueParse = true;
   for(unsigned n=0;(n<nLength)&&(bContinueParse);n++) {
      if (inbuffer[n]=='"') {
         if (bInsideQuotes) {
            bContinueParse = false; // stop parsing at end quote
         }
         else {
            bInsideQuotes = true;
         }
      }
      else if (bInsideQuotes) {
         outbuffer[nOut++] = inbuffer[n];
      }
   }
   outbuffer[nOut] = 0;
   s = outbuffer;
}

// Returns pointer to first character following <c>,
// returns NULL if the character isn't found or if 
// the character is the last character in the string.
const char* FindCharFollowing(const char *z, char c) {
   int nLength;
   bool bFound = false;
   int n;

   if (z==NULL) {return NULL;}
   nLength = (int)strlen(z);
   n = 0;
   while((n<nLength-1)&&(!bFound)) {  // -1 because open paren on last char is useless
      bFound = (z[n] == c);
      n++;
   }
   if (bFound) {return &z[n];}   // return ptr to char after open paren
   else {return NULL;}
}

// Returns net number of braces within tcString <s>.
// e.g. {{} = 1, {} = 0, {{}} = 0, {}} = -1 
int GetBraceLevel(tcString& s) {
   int n,nLength,nBraceLevel;
   const char *z;

   z = s.GetBuffer();
   if (z==NULL) {return 0;}
   nLength = (int)strlen(z);
   n = 0;
   nBraceLevel = 0;
   while(n<nLength) { 
      if (z[n] == '{') {nBraceLevel++;}
      else if (z[n] == '}') {nBraceLevel--;}
      n++;
   }
   return nBraceLevel;
}
