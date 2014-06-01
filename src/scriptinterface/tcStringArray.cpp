/**  
**  @file tcStringArray.cpp
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

#include "tcStringArray.h"
#include <map>
#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif 

namespace scriptinterface
{
    
	// tcStringArray
	void tcStringArray::AddString(const std::string& s) 
	{
		stringArray.push_back(s);
	}

    void tcStringArray::Clear()
    {
        stringArray.clear();
    }

	std::string tcStringArray::GetString(unsigned n) const
	{
		return stringArray[n];
	}

    void tcStringArray::PushBack(const std::string& s)
    {
        stringArray.push_back(s);
    }

    void tcStringArray::RemoveDuplicates()
    {
        std::map<std::string, bool> temp;

        for (size_t n=0; n<stringArray.size(); n++)
        {
            temp[stringArray[n]] = true;
        }

        stringArray.clear();
        std::map<std::string, bool>::const_iterator iter = temp.begin();
        for ( ;iter != temp.end(); ++iter)
        {
            stringArray.push_back(iter->first);
        }
    }

    void tcStringArray::SetStringArray(const std::vector<std::string>& x)
    {
        stringArray = x;
    }

	unsigned int tcStringArray::Size() 
	{
		return stringArray.size();
	}

    /**
    * Sorts into alphabetical order
    */
    void tcStringArray::Sort()
    {
        std::sort(stringArray.begin(), stringArray.end());
    }

	tcStringArray::tcStringArray() 
	{
	}

	tcStringArray::~tcStringArray() 
	{
	}




}

