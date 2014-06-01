/** 
**  @file tcStoresContainerItem.cpp 
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

#include "stdwx.h"

#ifndef WX_PRECOMP
#include "wx/wx.h" 
#endif

#include "tcStoresContainerItem.h"
#include "tcSimState.h"
#include "tcPlatformObject.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


/**
* @return pointer to stores object
* This is done dynamically to handle case where object is deleted
*/
tcStores* tcStoresContainerItem::GetStores() const
{
	tcPlatformObject* platform = 0;

	if (hostId == -1)
	{
		platform = dynamic_cast<tcPlatformObject*>
			(tcSimState::Get()->GetObject(platformId));
	}
	else
	{
		tcGameObject* parent = tcSimState::Get()->GetObject(hostId);
		if (parent == 0) return 0;
	    platform = dynamic_cast<tcPlatformObject*>(parent->GetChildById(platformId));
	}

	if (platform == 0) return 0;

    return platform->GetMagazine(storesIdx);
}

unsigned char tcStoresContainerItem::GetOpId() const
{
    return opId;
}

/**
* @return pointer to platform that holds this stores object, also sets storesIdx
* This is done dynamically to handle case where object is deleted
*/
tcPlatformObject* tcStoresContainerItem::GetPlatform(unsigned int& idx) const
{
	tcPlatformObject* platform = 0;

	if (hostId == -1)
	{
		platform = dynamic_cast<tcPlatformObject*>
			(tcSimState::Get()->GetObject(platformId));
	}
	else
	{
		tcGameObject* parent = tcSimState::Get()->GetObject(hostId);
		if (parent == 0) return 0;
	    platform = dynamic_cast<tcPlatformObject*>(parent->GetChildById(platformId));
	}

    idx = storesIdx;
    return platform;
}

bool tcStoresContainerItem::IsMoving() const
{
    return isMoving;
}

void tcStoresContainerItem::SetMoving(bool state)
{
    isMoving = state;
}

void tcStoresContainerItem::SetOpId(unsigned char val)
{
    opId = val;
}

void tcStoresContainerItem::SetStores(long id, long host, unsigned int idx)
{
	platformId = id;
	hostId = host;
	storesIdx = idx;
}

tcStoresContainerItem::tcStoresContainerItem()
:   platformId(-1),
    hostId(-1),
    storesIdx(0),
    isMoving(false),
    opId(0)
{
}

tcStoresContainerItem::~tcStoresContainerItem()
{
}


