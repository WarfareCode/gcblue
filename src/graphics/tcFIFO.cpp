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

#include "stdwx.h" // precompiled header file

#ifndef WX_PRECOMP
#include "wx/wx.h" 
#endif

#include "tcFIFO.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif 

bool tcFIFO::GetIndex(UINT16& rnNewIndex) {
   if (mnOut >= mnSize) {return false;} // no free indices
   rnNewIndex = maAvailable[mnCheckoutIndex++];
   if (mnCheckoutIndex >= mnSize) {
      mnCheckoutIndex = 0;
   }
   mnOut++;
   return true;
}

void tcFIFO::ReturnIndex(UINT16 anIndex) {
   maAvailable[mnReturnIndex++] = anIndex;
   if (mnReturnIndex >= mnSize) {
      mnReturnIndex = 0;
   }
   mnOut--;
}

void tcFIFO::Reset() {
   mnOut = 0;
   mnCheckoutIndex = 0;
   mnReturnIndex = 0;
   for(UINT16 k=0;k<mnSize;k++) {
      maAvailable[k] = k;
   }
}

tcFIFO::tcFIFO(UINT16 anSize) {
   maAvailable = new UINT16[anSize];
   if (maAvailable==NULL) {
      mnSize = 0;
   }
   else {
      mnSize = anSize;
   }
   Reset();
}

tcFIFO::tcFIFO(void) {
   tcFIFO(0);
}

tcFIFO::~tcFIFO(void) {
   if (maAvailable != NULL) {delete maAvailable;}
}

/*************** tcStack *****************/
bool tcStack::GetIndex(UINT16& rnNewIndex) {
   if (mnOut >= mnSize) {return false;} // no free indices
   rnNewIndex = maAvailable[mnCheckoutIndex++];
   mnOut++;
   if ((UINT32)rnNewIndex >= mnMinSize) {
      mnMinSize = rnNewIndex + 1;
   }
   return true;
}

void tcStack::ReturnIndex(UINT16 anIndex) {
   if (mnOut==0) {return;} // error, nothing should be out to return
   maAvailable[--mnCheckoutIndex] = anIndex;
   mnOut--;
}


tcStack::tcStack(UINT16 anSize) : tcFIFO(anSize) {
   mnMinSize = 0;
}

tcStack::tcStack(void) {
   tcStack(0);
}

tcStack::~tcStack(void) {
   mnMinSize = 0;
}

