/** 
**  @file tcDatabaseIterator.cpp 
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

#include "stdwx.h" // precompiled header file

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "tcDatabaseIterator.h"
#include "tcDatabase.h"
#include "tcDatabaseObject.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

namespace database
{

	tcDatabase* tcDatabaseIterator::database = 0;


	void tcDatabaseIterator::First()
	{
		nSize = database->mcObjectData.GetCount();
		nIterated = 0;

		if (nSize == 0)
		{
			currentPos = -1;
			currentObj = 0;
			nIterated = 1;
			return;
		}
		currentPos = database->mcObjectData.GetStartPosition();
		Next();
	}

	tcDatabaseObject* tcDatabaseIterator::Get()
	{
		return currentObj;
	}



	/**
	* Advance to next object in pool that meets filter criteria. If
	* no objects are found, set currentObj to NULL
	*/
	void tcDatabaseIterator::Next()
	{
		bool searching = true;

		while ((nIterated <= nSize) && searching)
		{
			long id;
			if (nIterated < nSize) // kind of a hack, nIterated > nSize is used for end condition
			{
				database->mcObjectData.GetNextAssoc(currentPos, id, currentObj);
			}
			nIterated++;

			if (PassesMask(currentObj))
			{
				searching = false; // found eligible object
			}
			else
			{
				currentObj = 0;
			}
		}
	}

	bool tcDatabaseIterator::IsDone()
	{
		return (nIterated > nSize);
	}


	/**
	* Checks currentObj against mask (filtering) criteria. This is used
	* to iterate through a filtered set of objects.
	* @return true if current obj meets mask criteria, false otherwise
	*/
	bool tcDatabaseIterator::PassesMask(const tcDatabaseObject* obj)
	{
		if (obj == 0) return false;
		if (mask == 0) return true;
		bool coarsePasses = (obj->mnType & mask & 0xFFF0) != 0;
		bool finePasses = (obj->mnType & mask & 0x000F) != 0;

        bool yearPasses = (filterYear == 0) || 
            ((filterYear >= obj->initialYear) && (filterYear <= obj->finalYear));

        bool countryPasses = (filterCountry.size() == 0) || (obj->country.size() == 0) ||
            (obj->country == filterCountry);
                             

		// if mask has fine classification set then use it, otherwise ignore
		if (mask & 0x000F) 
		{
			return coarsePasses && finePasses && yearPasses && countryPasses;
		}
		else
		{
			return coarsePasses && yearPasses && countryPasses;
		}
	}

    void tcDatabaseIterator::SetFilterCountry(const std::string& s)
    {
        filterCountry = s;
    }

    void tcDatabaseIterator::SetFilterYear(float val)
    {
        filterYear = val;
    }

	/**
	* @param classificationMask use 0 to pass all
	*/
	tcDatabaseIterator::tcDatabaseIterator(unsigned int classificationMask)
		: mask(classificationMask), filterYear(0), filterCountry("")
	{
		if (database == 0)
		{
			database = tcDatabase::Get();
		}

		First();
	}



	tcDatabaseIterator::~tcDatabaseIterator()
	{
	}

}