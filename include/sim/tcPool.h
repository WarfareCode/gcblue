/**  
**  @file tcPool.h
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

#if !defined _TCPOOL_H_
#define _TCPOOL_H_

#include "wx/wx.h"  // for NULL definition
#include <iostream>

#define NULL_INDEX -1

template <class T, int POOLSIZE> class tcPool {
public:
   bool Lookup(long n,T*& pt);
   const T* LookupConst(long n) const;
   long GetStartPosition(void);
   long GetCount(void);
   void GetNextAssoc(long& pos, long& index, T*& pt);
   long GetNextKey(long pos);
   long GetPrevKey(long pos);
   T operator[] (long index) const;  // r-value version
   bool CheckForCorruption();
   //T*& operator[] (long index); // l-value version, T has to support assignment
   bool CreateAndAddElement(T*& pt, long& newkey);  // T object created with new
   bool AddElement(T* pt, long& newkey);  // T object already created
   bool AddElementForceKey(T* pt, long newkey);  // T object already created
   bool RemoveKey(long n);
   bool RemoveKeyWithoutDelete(long n);
   void RemoveAll(void);
   long GetPoolSize(void);
	tcPool();
	virtual ~tcPool();
private:
   long mnSize; // current number of elements in pool
   long mnBase; // index of base element (first element)
   long mnTail; // index of last element
   T* mpool[POOLSIZE]; // array of pointers to T
   long maPrev[POOLSIZE]; // index of previous element
   long maNext[POOLSIZE]; // index of next element
   long maAvailable[POOLSIZE]; // array of free indices (FIFO)
   long mnCheckoutIndex; // maAvailable index for allocation
   long mnReturnIndex; // maAvailable index for deallocation
};

/***** inline function definitions *****/
/**********************************************************/


template <class T, int POOLSIZE>
bool tcPool<T,POOLSIZE>::CheckForCorruption() 
{
    return false;
    // this trips once the POOLSIZE-1 object is actually used, so disabled 11OCT2009

    //if (mpool[POOLSIZE-1] != NULL)
    //{
    //    return true;
    //}
    //else
    //{
    //    return false;
    //}
}


template <class T, int POOLSIZE>
bool tcPool<T,POOLSIZE>::Lookup(long n,T*& pt) {
   if ((n >=0)&&(n < POOLSIZE))
   {
      pt = mpool[n];
   }
   else 
   {
      pt = NULL;
      if (n >=0) 
      {
          std::cerr << "error - invalid pool index" << std::endl;
      }
      return false;
   }
   return (mpool[n] != NULL);
}

template <class T, int POOLSIZE>
const T* tcPool<T,POOLSIZE>::LookupConst(long n) const
{
    T* pt;
    if ((n >=0)&&(n < POOLSIZE))
    {
        pt = mpool[n];
    }
    else 
    {
        pt = NULL;
    }
    return pt;
}


/**********************************************************/
template <class T, int POOLSIZE>
bool tcPool<T,POOLSIZE>::CreateAndAddElement(T*& pt, long& newkey) {
   if (mnSize >= POOLSIZE) {
      newkey = NULL_INDEX;
      pt = NULL;
      std::cerr << "error - pool out of memory" << std::endl;
      return false;  // out of memory
   }
   newkey = maAvailable[mnCheckoutIndex];
   mnCheckoutIndex++;
   mnSize++;
   if (mnCheckoutIndex == POOLSIZE) {
      mnCheckoutIndex = 0;
   }
   pt = new T;
   mpool[newkey] = pt;
   // insert at beginning of list
   maNext[newkey] = mnBase; // newkey next points to old base
   maPrev[newkey] = maPrev[mnBase]; // newkey prev points to prev of old base
   maPrev[mnBase] = newkey; // old base prev now points to newkey
   mnBase = newkey; // newkey becomes the new base
   if (mnSize==1) {mnTail = newkey;} // first element is the tail
   return true;
}
/**********************************************************/
template <class T, int POOLSIZE>
bool tcPool<T,POOLSIZE>::AddElement(T* pt, long& newkey) {
   if (mnSize >= POOLSIZE) {
      newkey = NULL_INDEX;
      std::cerr << "error - pool out of memory" << std::endl;
      return false;  // out of memory
   }
   newkey = maAvailable[mnCheckoutIndex];
   maAvailable[mnCheckoutIndex] = -1; // 11JUN2011
   mnCheckoutIndex++;
   mnSize++;
   if (mnCheckoutIndex == POOLSIZE) {
      mnCheckoutIndex = 0;
   }

   mpool[newkey] = pt;
   // insert at beginning of list
   maNext[newkey] = mnBase; // newkey next points to old base
   if (mnBase != NULL_INDEX) {
      maPrev[newkey] = maPrev[mnBase]; // newkey prev points to prev of old base
      maPrev[mnBase] = newkey; // old base prev now points to newkey
   } 
   mnBase = newkey; // newkey becomes the new base
   if (mnSize==1) {
      mnTail = newkey; // first element is the tail
      maPrev[newkey] = NULL_INDEX;
   } 
   //fprintf(stdout,"added element %d\n",newkey);
   return true;
}
/**********************************************************/
// forces element to use key <newkey>
// If this key is already taken, the element is not added.
// This can be significantly slower than AddElement and should only be used
// when trying to reconstruct a tcPool from a file.
template <class T, int POOLSIZE>
bool tcPool<T,POOLSIZE>::AddElementForceKey(T* pt, long newkey) {
   long nDefaultKey;

   if (mnSize >= POOLSIZE)
   {
      std::cerr << "error - pool out of memory" << std::endl;
      return false;  // out of memory
   }
   nDefaultKey = maAvailable[mnCheckoutIndex]; // the key normally assigned

   // search for newkey in fifo and trade with default key if found
   bool bFound = false;
   if (mnCheckoutIndex >= mnReturnIndex) // >= because default init has these both equal to 0, doesn't matter that ret = checkout since none checked out yet
   {
	   for (long k=mnCheckoutIndex;(k<POOLSIZE)&&(!bFound);k++) 
	   {
		   if (maAvailable[k] == newkey) {
			   maAvailable[k] = nDefaultKey;
			   bFound = true;
		   }
	   }
	   for (long k=0;(k<mnReturnIndex)&&(!bFound);k++) 
	   {
		   if (maAvailable[k] == newkey) {
			   maAvailable[k] = nDefaultKey;
			   bFound = true;
		   }
	   }
   }
   else
   {
	   for (long k=mnCheckoutIndex;(k<mnReturnIndex)&&(!bFound);k++) 
	   {
		   if (maAvailable[k] == newkey) {
			   maAvailable[k] = nDefaultKey;
			   bFound = true;
		   }
	   }
   }
   if (!bFound) 
   {
       std::cerr << "error - AddElementForceKey - pool element not found" << std::endl;
       return false;
   } // return without adding element if not found

   mnCheckoutIndex++;
   mnSize++;
   if (mnCheckoutIndex == POOLSIZE) {
      mnCheckoutIndex = 0;
   }

   mpool[newkey] = pt;
   // insert at beginning of list
   maNext[newkey] = mnBase; // newkey next points to old base
   if (mnBase != NULL_INDEX) {
      maPrev[newkey] = maPrev[mnBase]; // newkey prev points to prev of old base
      maPrev[mnBase] = newkey; // old base prev now points to newkey
   } 
   mnBase = newkey; // newkey becomes the new base
   if (mnSize==1) {
      mnTail = newkey; // first element is the tail
      maPrev[newkey] = NULL_INDEX;
   } 
   return true;
}
/**********************************************************/
template <class T, int POOLSIZE>
long tcPool<T,POOLSIZE>::GetStartPosition(void) {
   return mnBase;
}
/**********************************************************/
template <class T, int POOLSIZE>
long tcPool<T,POOLSIZE>::GetCount(void) {
   return mnSize;
}
/**********************************************************/
template <class T, int POOLSIZE>
void tcPool<T,POOLSIZE>::GetNextAssoc(long& pos, long& index, T*& pt){
   if ((pos < 0)||(pos >= POOLSIZE)) {
      pt = NULL;
      index = NULL_INDEX;
      if (pos >=0) 
      {
          std::cerr << "error - bad pool index" << std::endl;
      }
      return;
   }
   pt = mpool[pos];
   index = pos;
   pos = maNext[pos];
}
/**********************************************************/
template <class T, int POOLSIZE>
long tcPool<T,POOLSIZE>::GetNextKey(long pos){
    if ((pos < 0)||(pos >= POOLSIZE)) 
    {
        if (pos >=0)
        {
            std::cerr << "error - bad pool index" << std::endl;
        }
        return NULL_INDEX;
    }
    if (maNext[pos] == NULL_INDEX) 
    {
        return mnBase; // end of list, circle to beginning
    }
    else {
        return maNext[pos];
    }
}
/**********************************************************/
template <class T, int POOLSIZE>
long tcPool<T,POOLSIZE>::GetPrevKey(long pos)
{
    if ((pos < 0)||(pos >= POOLSIZE)) 
    {
        if (pos >=0) 
        {
            std::cerr << "error - bad pool index" << std::endl;
        }
        return NULL_INDEX;
    }
    if (maPrev[pos] == NULL_INDEX) 
    {
        return mnTail; // beginning of list, circle to end
    }
    else 
    {
        return maPrev[pos];
    }
}
/**********************************************************/
template <class T, int POOLSIZE>
T tcPool<T,POOLSIZE>::operator[] (long index) const 
{
    if ((index < 0)||(index >= POOLSIZE)) 
    {
        std::cerr << "error - operator[] - bad pool index" << std::endl;
        return *mpool[0];
    }
    else 
    {
        return *mpool[index];
    }
}  

/**********************************************************/
template <class T, int POOLSIZE>
bool tcPool<T,POOLSIZE>::RemoveKey(long n) 
{
    if ((mnSize == 0)||(mnReturnIndex==mnCheckoutIndex)) 
    {
        std::cerr << "error - RemoveKey - empty pool, nothing to remove" << std::endl;
        return false;  // empty pool, nothing to remove 
    }
    if (n < 0) 
    {
        std::cerr << "error - RemoveKey - bad pool index" << std::endl;
        return false;
    }
   // return key to available
   maAvailable[mnReturnIndex++] = n; 
   if (mnReturnIndex == POOLSIZE) {
       mnReturnIndex = 0;
   }
   // remove from list   
   delete mpool[n];
   mpool[n] = NULL;
   if (n==mnBase) {
       mnBase = maNext[n]; // if n is base then n next becomes new base
   }
   if (n==mnTail) {
       mnTail = maPrev[n]; // if n is tail then n prev becomes new tail
   }
   if ((maPrev[n] >= 0)&&(maPrev[n] < POOLSIZE))
   {
       maNext[maPrev[n]] = maNext[n]; // maNext[n] can be invalid
   }
   if ((maNext[n] >=0 )&&(maNext[n] < POOLSIZE)) 
   {
       maPrev[maNext[n]] = maPrev[n]; // maPrev[n] can be invalid
   }
   mnSize--;
   return true;
}
/**********************************************************/
/**
* Removes key from pool but does not delete object pointed to
* by deleted member.
*/
template <class T, int POOLSIZE>
bool tcPool<T,POOLSIZE>::RemoveKeyWithoutDelete(long n) 
{
    if ((mnSize == 0)||(mnReturnIndex==mnCheckoutIndex)) 
    {
        std::cerr << 
            "error - RemoveKeyWithoutDelete - empty pool, nothing to remove" 
            << std::endl;
        return false;  // empty pool, nothing to remove 
    }
    if ((n < 0)||(n >= POOLSIZE)||(mpool[n]==NULL)) 
    {
        std::cerr << "error - RemoveKeyWithoutDelete - bad index" << std::endl;
        return false;
    }
    // return key to available
    maAvailable[mnReturnIndex++] = n; 
    if (mnReturnIndex == POOLSIZE) {
        mnReturnIndex = 0;
    }
    // remove from list   
    mpool[n] = NULL;
    if (n==mnBase) {
        mnBase = maNext[n]; // if n is base then n next becomes new base
    }
    if (n==mnTail) {
        mnTail = maPrev[n]; // if n is tail then n prev becomes new tail
    }
    if ((maPrev[n] >= 0)&&(maPrev[n] < POOLSIZE))
    {
        maNext[maPrev[n]] = maNext[n]; // maNext[n] can be invalid
    }
    if ((maNext[n] >= 0)&&(maNext[n] < POOLSIZE))
    {
        maPrev[maNext[n]] = maPrev[n]; // maPrev[n] can be invalid
    }
    mnSize--;
    return true;
}
/**********************************************************/
template <class T, int POOLSIZE>
void tcPool<T,POOLSIZE>::RemoveAll() 
{
   for(long k=0;k<POOLSIZE;k++) 
   {
      if (mpool[k] != NULL) 
      {
         delete mpool[k];
         mpool[k] = NULL;
      }
      maPrev[k] = NULL_INDEX;
      maNext[k] = NULL_INDEX;
      maAvailable[k] = (k + 1) % POOLSIZE; ///< start with 1 as index (for debugging)
   }
   mnSize = 0;
   mnBase = NULL_INDEX; 
   mnTail = NULL_INDEX;
   mnCheckoutIndex = 0;
   mnReturnIndex = 0;
}
/**********************************************************/
template <class T, int POOLSIZE>
tcPool<T,POOLSIZE>::tcPool()
{
   mnSize = 0;
   mnBase = NULL_INDEX; // value NULL_INDEX is OOB and used as invalid
   mnTail = NULL_INDEX;
   mnCheckoutIndex = 0;
   mnReturnIndex = 0;
   for(long k=0;k<POOLSIZE;k++) 
   {
      mpool[k] = NULL;
      maPrev[k] = NULL_INDEX;
      maNext[k] = NULL_INDEX;
      maAvailable[k] = (k + 1) % POOLSIZE; ///< start with 1 as index (for debugging)
   }
}
/**********************************************************/
template <class T, int POOLSIZE>
tcPool<T,POOLSIZE>::~tcPool() 
{
   for(long k=0;k<POOLSIZE;k++) 
   {
      // TODO: without the extra check this occasionally causes an exception/
      // due to deleting an invalid memory location
      if ((mpool[k] != NULL)&&(mpool[k] > (void*)0x000000FF)) 
      { 
         delete mpool[k];
         mpool[k] = NULL;
      }
   }
}
/**********************************************************/
template <class T, int POOLSIZE>
long tcPool<T,POOLSIZE>::GetPoolSize() 
{
   return POOLSIZE;
}

#endif 
