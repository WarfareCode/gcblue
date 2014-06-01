/** 
**  @file tcGameObjIterator.cpp 
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

#include "tcGameObjIterator.h"
#include "tcGameObject.h"
#include "tcSimState.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

tcSimState* tcGameObjIterator::simState = NULL;


void tcGameObjIterator::First()
{
    nSize = simState->maPlatformState.GetCount();
    nIterated = 0;

    if (nSize == 0)
    {
        currentPos = -1;
        currentObj = NULL;
        nIterated = 1;
        return;
    }
    currentPos = simState->maPlatformState.GetStartPosition();
    Next();
}

tcGameObject* tcGameObjIterator::Get()
{
    return currentObj;
}



/**
* Advance to next object in pool that meets filter criteria. If
* no objects are found, set currentObj to NULL
*/
void tcGameObjIterator::Next()
{

    bool searching = true;

    while ((nIterated <= nSize) && searching)
    {
        long id;
        if (nIterated < nSize) // kind of a hack, nIterated > nSize is used for end condition
        {
            simState->maPlatformState.GetNextAssoc(currentPos, id, currentObj);
        }
        nIterated++;

        if (PassesFilter(currentObj))
        {
            searching = false; // found eligible object
        }
        else
        {
            currentObj = NULL;
        }
    }
}

bool tcGameObjIterator::NotDone()
{
    return (nIterated <= nSize);
}

void tcGameObjIterator::SetAllianceFilter(unsigned alliance)
{
	allianceFilter = alliance;
}

/**
* Checks currentObj against filtering criteria. This is used
* to iterate through a filtered set of objects.
* @return true if current obj meets filtering criteria, false otherwise
*/
bool tcGameObjIterator::PassesFilter(const tcGameObject *obj)
{
    if (obj == NULL) return false;
	if ((allianceFilter != 0) && (obj->GetAlliance() != allianceFilter)) return false;

    if (!useRegion) return true;
    return region.ContainsPoint(obj->mcKin.mfLon_rad, 
                                obj->mcKin.mfLat_rad);
}


tcGameObjIterator::tcGameObjIterator(const tcGeoRect& filterRegion)
: allianceFilter(0)
{
    wxASSERT(simState);

    useRegion = true;
    region = filterRegion;

    First();
}

tcGameObjIterator::tcGameObjIterator()
: allianceFilter(0)
{
    wxASSERT(simState);

    useRegion = false;
    First();
}

tcGameObjIterator::~tcGameObjIterator()
{
}
