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

#ifdef WX_PRECOMP
#include "stdwx.h"
#else
#include "wx/wx.h" 
#include "wx/msw/private.h" // for MS Windows specific definitions
#endif

#include "tcTime.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/**
* Accessor for singleton instance
*/
tcTime* tcTime::Get()
{
	static tcTime instance;

	return &instance;
}


/**
* Assumes tcTime::Update() is being called from main loop.
* Use tcTime::GetUpdate30HzCount to update before reading counter
* @return 30 Hz counter count value
*/
unsigned tcTime::Get30HzCount()
{
	return snCount_30Hz;
}

/**
* Calls tcTime::Update() to update counter value
* @return 30 Hz counter count value
*/
unsigned tcTime::GetUpdated30HzCount()
{
	Update();
	return snCount_30Hz;
}

/**
* Initializes the tcTime object.
*/
void tcTime::Init()
{
	LARGE_INTEGER frequency;
	if (QueryPerformanceFrequency(&frequency) == false)
	{
		MessageBox(NULL, L"Error - high performance counter", L"Error", MB_OK);
		return;
	}
	snFrequency = (unsigned long)frequency.QuadPart;

	snDeltaCount = (unsigned int)(snFrequency/30); // 30 updates per second
}

/**
* Updates the tcTime object.
*/
void tcTime::Update()
{
	LARGE_INTEGER nCurrentCount;

	QueryPerformanceCounter(&nCurrentCount);

	unsigned long currentTime = (unsigned long)nCurrentCount.QuadPart;

	while ((currentTime - snLastCount) >= snDeltaCount)
	{
		snCount_30Hz++;
		snLastCount += snDeltaCount;
	}
}

/** 
* tcTime constructor.
*/
tcTime::tcTime() :
snDeltaCount(0),
snLastCount(0),
snCount_30Hz(0)
{
	Init();

}

/** 
* tcTime destructor.
*/
tcTime::~tcTime() 
{
}