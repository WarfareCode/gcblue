/**
** @file tcFIFO.h
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

#ifndef _TCFIFO_H_
#define _TCFIFO_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef WX_PRECOMP
#include "wx/wx.h" 
#ifdef WIN32
#include "wx/msw/private.h" // for MS Windows specific definitions
#endif // WIN32
#endif // WX_PRECOMP

#include "gctypes.h"

// FIFO for resource management, up to 64k elements (UINT16 id's)
class tcFIFO 
{
public:
   virtual bool GetIndex(UINT16& rnNewIndex);
   virtual void ReturnIndex(UINT16 anIndex);
   void Reset(void);

   tcFIFO(void);
   tcFIFO(UINT16 anSize);
   virtual ~tcFIFO(void);
protected:
   UINT16 mnSize;
   UINT16 mnOut;
   UINT16 *maAvailable; // array of free indices (FIFO)
   UINT16 mnCheckoutIndex; // maAvailable index for allocation
   UINT16 mnReturnIndex;  // maAvailable index for deallocation
};

// LIFO version
class tcStack : public tcFIFO 
{
public:
   bool GetIndex(UINT16& rnNewIndex);
   void ReturnIndex(UINT16 anIndex);
   UINT32 mnMinSize;  // minimum stack size to store outstanding indices
   void Reset() {mnMinSize=0;tcFIFO::Reset();}

   tcStack(void);
   tcStack(UINT16 anSize);
   virtual ~tcStack(void);
};

/**************************** tcStackManager template ******************************/
// class statically allocates SIZE members of T and manages with stack
// size must be less than 0xFFFF

#ifndef NULL16
#define NULL16 0xFFFF
#endif

template <class T, UINT16 SIZE> class tcStackManager 
{
public:
   T* Get(UINT16 anId);
   T* GetDataPointer(void);
   UINT16 GetNewElement(void);
   void ReturnElement(UINT16 anId);
   void Reset(void);
   UINT16 GetSize(void);
   UINT16 GetSizeBound(void);

	tcStackManager();
	virtual ~tcStackManager();
private:
   tcStack *mpId;
   T maData[SIZE];
   
};

/***** inline function definitions *****/
/**********************************************************/
template <class T, UINT16 SIZE>
T* tcStackManager<T,SIZE>::Get(UINT16 anId) {
   if (anId >= SIZE) {return NULL;}
   else {return &maData[anId];}
}

// returns pointer to first element of data
template <class T, UINT16 SIZE>
T* tcStackManager<T,SIZE>::GetDataPointer() {
   return &maData[0];
}

template <class T, UINT16 SIZE>
UINT16 tcStackManager<T,SIZE>::GetNewElement() {
   UINT16 anIdx;
   if (mpId->GetIndex(anIdx)) {
      return anIdx;
   }
   else {
      return NULL16;
   }
}

template <class T, UINT16 SIZE>
void tcStackManager<T,SIZE>::ReturnElement(UINT16 anId) {
   mpId->ReturnIndex(anId);
}

template <class T, UINT16 SIZE>
void tcStackManager<T,SIZE>::Reset() {
   mpId->Reset();
}

template <class T, UINT16 SIZE>
UINT16 tcStackManager<T,SIZE>::GetSize() {
   return SIZE;
}

template <class T, UINT16 SIZE>
UINT16 tcStackManager<T,SIZE>::GetSizeBound() {
   return mpId->mnMinSize;
}

template <class T, UINT16 SIZE>
tcStackManager<T,SIZE>::tcStackManager() {
   mpId = new tcStack(SIZE);
}

template <class T, UINT16 SIZE>
tcStackManager<T,SIZE>::~tcStackManager() {
   if(mpId != NULL) {delete mpId;}
}

#endif

