/**  
**  @file tcStringTable.cpp
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

#include "tcStringTable.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif 

namespace scriptinterface
{

	void tcStringTable::AddStringArray(const tcStringArray& s)
	{
		stringTable.push_back(s);
	}

	void tcStringTable::PushBack(const tcStringArray& s)
	{
		stringTable.push_back(s);
	}

	tcStringArray tcStringTable::GetStringArray(unsigned n) const
	{
		static tcStringArray nullArray;

		if (n < stringTable.size())
		{
			return stringTable[n];
		}
		else
		{
			return nullArray;
		}
	}

	/**
	* DEPRECATED, temporary method to support previous code
	*/
	std::string tcStringTable::GetString(unsigned n) const
	{
		static std::string nullString;
		if ((stringTable.size() > 0) && (stringTable[0].Size() > n))
		{
			return stringTable[0].GetString(n);
		}
		else
		{
			return nullString;
		}
	}

	unsigned int tcStringTable::Size()
	{
		return (unsigned int)stringTable.size();
	}

	void tcStringTable::Clear()
	{
		stringTable.clear();
	}

	tcStringTable::tcStringTable()
	{
	}

	tcStringTable::~tcStringTable()
	{
	}

}

