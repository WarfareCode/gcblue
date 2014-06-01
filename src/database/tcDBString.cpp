/*  
**  @file tcDBString.cpp
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
#include "tcDBString.h"
#include "tcString.h"
#include "common/tcStream.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

namespace database
{
    
    void tcDBString::AssignRandomString() 
    {
        str = "";

        int i;
        switch(i = rand() % 7) 
        {
        case 0: str += "Alpha"; break;
        case 1: str += "Beta"; break;
        case 2: str += "Delta"; break;
        case 3: str += "Echo"; break;
        case 4: str += "Golf"; break;
        case 5: str += "Hotel"; break;
        case 6: str += "Lima"; break;
        }
        /*
        switch(i = rand() % 7) {
        case 0:s += "Blue";break;
        case 1:s += "Red";break;
        case 2:s += "Black";break;
        case 3:s += "Clear";break;
        case 4:s += "Green";break;
        case 5:s += "White";break;
        case 6:s += "Orange";break;
        }
        switch(i = rand() % 7) {
        case 0:s += "Bat";break;
        case 1:s += "Rock";break;
        case 2:s += "Blob";break;
        case 3:s += "Shoe";break;
        case 4:s += "Hammer";break;
        case 5:s += "Fruit";break;
        case 6:s += "Wheel";break;
        }
        */
    }
    
    void tcDBString::AssignRandomStringB() 
    {
        str = "GC_";
        int i;
        switch(i = rand() % 7) 
        {
        case 0: str += "Alpha"; break;
        case 1: str += "Beta"; break;
        case 2: str += "Charlie"; break;
        case 3: str += "Delta"; break;
        case 4: str += "Echo"; break;
        case 5: str += "Foxtrot"; break;
        case 6: str += "Golf"; break;
        case 7: str += "Hotel"; break;
        case 8: str += "Indigo"; break;
        case 9: str += "Juliet"; break;
        }

        i = rand() % 100;
        wxString s2;
        s2.Format("_%d",i);
        str += s2;
    }

    void tcDBString::AssignRandomSuffix()
    {
        wxString s2;
        int i;
        switch(i = rand() % 7) 
        {
        case 0: str += "Alpha"; break;
        case 1: str += "Beta"; break;
        case 2: str += "Charlie"; break;
        case 3: str += "Delta"; break;
        case 4: str += "Echo"; break;
        case 5: str += "Foxtrot"; break;
        case 6: str += "Golf"; break;
        case 7: str += "Hotel"; break;
        case 8: str += "Indigo"; break;
        case 9: str += "Juliet"; break;
        }

        i = rand() % 100;
        s2.Format("_%d",i);
        str += s2;
    }
    
	const char* tcDBString::c_str() const
	{
        return str.c_str();
	}

    size_t tcDBString::size() const
    {
        return str.size();
    }

    tcDBString& tcDBString::operator= (const tcDBString& c) 
    {
        str = c.str;
        return (*this);
    }
    
    tcDBString& tcDBString::operator= (const char* s) 
    {
        str = s;
        return (*this);
    }

    tcDBString& tcDBString::operator+= (const char* s) 
    {
        str += s;
        return (*this);
    }
    
    int tcDBString::operator== (tcDBString& s) const
    {
        return (str.Cmp(s.str) == 0);
    }

    bool tcDBString::operator== (const char* s) const
    {
        return (str.Cmp(s) == 0);
    }
    
    tcStream& tcDBString::operator<<(tcStream& stream)
    {
        static unsigned char buffer[ERROR_SIZE+1];
        size_t len;

        stream.read((char*)&len, sizeof(len));
        if (len >= ERROR_SIZE)
        {
            std::cerr << "tcStream::operator>>(std::string& val) - length overflow\n";
        }
        else
        {
            stream.read((char*)buffer, (std::streamsize)len);
            buffer[len] = 0; // add terminating null char
            str = buffer;
        }

        return stream;
    }

    tcStream& tcDBString::operator>>(tcStream& stream)
    {
        size_t len = (size_t)str.size();
        stream.write((char*)&len, sizeof(len));
        stream.write(str.c_str(), (std::streamsize)len);

        return stream;
    }

    int tcDBString::Serialize(tcFile& file, bool mbLoad) 
    {
        wxASSERT(false); // out of date
        if (mbLoad) {
            //file.Read(mz, DB_STRING_SIZE);       
        }
        else {
            //file.Write(mz, DB_STRING_SIZE); 
        }
        return true;
    }

    tcDBString::tcDBString() 
        : str("DEFAULT")
    {
    }

    tcDBString::tcDBString(const char* buff) 
        : str(buff)
    {
    }

	tcDBString::tcDBString(const tcDBString& src)
        : str(src.str)
	{
	}
    

    tcDBString::~tcDBString() 
    {
    }
    
}

