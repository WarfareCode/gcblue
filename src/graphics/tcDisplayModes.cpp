/** @file tcDisplayModes.cpp
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

#ifdef WIN32
#include "wx/msw/private.h" // for MS Windows specific definitions
#else
#error "tcDisplayModes is Windows only at the moment"
#endif

#include "tcDisplayModes.h"
#include "tcOptions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif 

/**
* Accessor for singleton instance
*/
tcDisplayModes* tcDisplayModes::Get()
{
	static tcDisplayModes instance;
	return &instance;
}


void tcDisplayModes::ChangeMode(unsigned width, unsigned height, unsigned bits, 
								unsigned freq)
{
	DEVMODE winModeInfo;

	winModeInfo.dmSize = sizeof(DEVMODE);
	winModeInfo.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT |
		DM_DISPLAYFREQUENCY;
	winModeInfo.dmBitsPerPel = bits;
	winModeInfo.dmPelsHeight = height;
	winModeInfo.dmPelsWidth = width;
	winModeInfo.dmDisplayFrequency = freq;
		
	if (!IsModeValid(width, height, bits, freq))
	{
		fprintf(stderr, "tcDisplayModes::ChangeMode - Invalid mode: "
			"W:%d, H:%d, Bits:%d, Freq:%d\n", width, height, bits, freq);
		return;
	}


	long result = ChangeDisplaySettings(&winModeInfo, 0); // change dynamically
	if (result == DISP_CHANGE_SUCCESSFUL)
	{
		currentMode.bits = bits;
		currentMode.width = width;
		currentMode.height = height;
		currentMode.frequency = freq;
	}
	else if (result == DISP_CHANGE_BADMODE)
	{
		fprintf(stderr, "tcDisplayModes::ChangeMode - Mode not supported: "
			"W:%d, H:%d, Bits:%d Freq:%d\n", width, height, bits, freq);
	}
	else
	{
		fprintf(stderr, "tcDisplayModes::ChangeMode - Mode change failed (%d)",
			result);
	}
}

/**
* Changes display mode info in options xml file. Mode will take effect
* after restart of game (if mode is valid).
*/
void tcDisplayModes::ChangeOptionsMode(unsigned width, unsigned height, unsigned bits, 
									   unsigned freq)
{
	if (!IsModeValid(width, height, bits, freq))
	{
		fprintf(stderr, "tcDisplayModes::ChangeOptionsMode - Invalid mode: "
			"W:%d, H:%d, Bits:%d Freq:%d\n", width, height, bits, freq);
		return;
	}

	wxString modeString = wxString::Format("%d %d %d %d", width, height, bits, freq);

	tcOptions::Get()->SetOptionString("DisplaySettings", modeString.GetData());
}

/**
* @return number of display modes (width, height, bits)
*/
unsigned int tcDisplayModes::GetModeCount() const
{
	return (unsigned int)modeInfo.size();
}

const tcDisplayModes::Info& tcDisplayModes::GetCurrentModeInfo() const
{
	return currentMode;
}

const tcDisplayModes::Info& tcDisplayModes::GetModeInfo(unsigned int n) const
{
	if (n >= modeInfo.size())
	{
		fprintf(stderr, "tcDisplayModes::GetModeInfo - index out of bounds\n");
		wxASSERT(0);
	}
	return modeInfo[n];
}

bool tcDisplayModes::IsCurrentMode(unsigned n) const
{
	if (n >= GetModeCount()) return false;

	tcDisplayModes::Info mode_n = modeInfo[n];
	
	return ((mode_n.bits == currentMode.bits)&&
		(mode_n.height == currentMode.height)&&
		(mode_n.width == currentMode.width)&&
		(mode_n.frequency == currentMode.frequency));
}

/**
* @return true if mode params match at least one of the modes in modeInfo
*/
bool tcDisplayModes::IsModeValid(unsigned width, unsigned height, unsigned bits, 
								 unsigned freq)
{
	unsigned int modeCount = GetModeCount();
	for (unsigned int n=0; n<modeCount; n++)
	{
		tcDisplayModes::Info& info = modeInfo[n];
		if ((info.bits == bits)&&
			(info.width == width)&&
			(info.height == height)&&
			(info.frequency == freq))
		{
			return true;
		}
	}
	return false;
}

void tcDisplayModes::LoadModeFromOptions()
{
	const char* modeString = tcOptions::Get()->GetOptionString("DisplaySettings");
	int width;
	int height;
	int bits;
	int freq;
	
	if (sscanf(modeString, "%d %d %d %d", &width, &height, &bits, &freq) < 4)
	{
		return;
	}

	ChangeMode(width, height, bits, freq);
}

/**
* Writes modeInfo to stdout. PopulateModeInfo should be called first
*/
void tcDisplayModes::LogModeInfo()
{
	unsigned int modeCount = GetModeCount();
	for (unsigned int n=0; n<modeCount; n++)
	{
		tcDisplayModes::Info& info = modeInfo[n];
		fprintf(stdout, "Display mode %d: W: %d, H: %d, Bits: %d Freq: %d (%s)\n",
			n, info.width, info.height, info.bits, info.frequency, info.deviceDescription.c_str());
	}
}

/**
* Initializes modeInfo vector with info on display modes. Ignores
* modes with less than 16 bits per pixel and modes with width < 800.
* WINDOWS ONLY for now. Next version of wxWidgets should have a
* cross-platform version of these functions that we can use instead.
*
* 23 FEB 2006, Can use wxDisplay, wxVideoMode for this
*/
void tcDisplayModes::PopulateModeInfo()
{
	modeInfo.clear();

	DEVMODE winModeInfo;
	winModeInfo.dmSize = sizeof(DEVMODE);

	unsigned lastBits = 0;
	unsigned lastWidth = 0;
	unsigned lastHeight = 0;
	unsigned lastFreq = 0;

	int i = 0;
	while ( EnumDisplaySettings(0, i++, &winModeInfo) ) 
	{
		tcDisplayModes::Info info;
		info.bits = winModeInfo.dmBitsPerPel;
		info.height = winModeInfo.dmPelsHeight;
		info.width = winModeInfo.dmPelsWidth;
		info.frequency = winModeInfo.dmDisplayFrequency;

		unsigned int driverVersion = winModeInfo.dmDriverVersion;
		wxString description = wxString::Format("%s %d.%d", winModeInfo.dmDeviceName,
			(driverVersion & 0xFF), ((driverVersion >> 8) & 0xFF));
		info.deviceDescription = description.c_str();

		bool matchesLast = ((info.bits == lastBits)&&
			(info.width == lastWidth)&&
			(info.height == lastHeight)&&
			(info.frequency == lastFreq));

		if ((info.bits >= 16)&&(info.width >= 800)&&(!matchesLast))
		{
			modeInfo.push_back(info);
		}

		lastBits = info.bits;
		lastWidth = info.width;
		lastHeight = info.height;
		lastFreq = info.frequency;
	}

    // ENUM_CURRENT_SETTINGS is defined as ((DWORD)-1) in windows.h
	EnumDisplaySettings(0, ENUM_CURRENT_SETTINGS, &winModeInfo); 
	currentMode.bits = winModeInfo.dmBitsPerPel;
	currentMode.height = winModeInfo.dmPelsHeight;
	currentMode.width = winModeInfo.dmPelsWidth;
	currentMode.frequency = winModeInfo.dmDisplayFrequency;

}


tcDisplayModes::tcDisplayModes()
{
	PopulateModeInfo();
	startMode = currentMode;
}

tcDisplayModes::~tcDisplayModes()
{
	ChangeMode(startMode.width, startMode.height, startMode.bits, 
		startMode.frequency);
}

