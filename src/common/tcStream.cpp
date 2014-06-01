/**  
**  @file tcStream.cpp
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

#include "tcStream.h"
#include <iostream>
#include <fstream>
#include "tcFloatCompressor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/**
* creates stream from char array
*/
tcStream::tcStream(const char* data, std::streamsize count)
: detailLevel(0),
  maxSize(99999),
  doneFlag(false),
  direction(UNDEFINED)
{
    std::stringstream::write(data, count);
}

/**
* copy constructor
*/
tcStream::tcStream(const tcStream& stream)
: std::stringstream(stream.str()),
  maxSize(stream.maxSize),
  doneFlag(stream.doneFlag),
  direction(stream.direction)
{
}

/**
* default constructor
*/
tcStream::tcStream()
: detailLevel(0),
  maxSize(99999),
  doneFlag(false),
  metaString(""),
  direction(UNDEFINED)
{
}

const std::string& tcStream::asString()
{
	static std::string s;
	s = str();

	return s;
}

void tcStream::clear()
{
    std::stringstream::str("");
}

/**
* @return true if end of stream has been reached
*/
bool tcStream::eof()
{
    return std::stringstream::eof();
}

void tcStream::read(char* buff, std::streamsize count)
{
    std::stringstream::read(buff, count);
}

/**
* @return size of stream in bytes
*/
size_t tcStream::size() const
{
    return std::stringstream::str().size();
}

/**
* Skips over count bytes from current read stream position
*/
void tcStream::skip_read(unsigned int count)
{
    unsigned int maxSkip = (unsigned int)size() - std::stringstream::tellg();
    if (count > maxSkip) count = maxSkip;
    std::stringstream::seekg(count, ios_base::cur);
}

/**
* @return write position relative to beginning of stream, -1 for error
*/
int tcStream::tellp()
{
    return (int)std::stringstream::tellp();
}



void tcStream::write(const char* buff, std::streamsize count)
{
    std::stringstream::write(buff, count);
}

tcStream::StreamDirection tcStream::GetDirection() const
{
    return direction;
}

void tcStream::SetDirection(StreamDirection dir)
{
    direction = dir;
}


void tcStream::LoadFromFile(const char* fileName)
{
    clear();

    detailLevel = 0;
    maxSize = 4*1024*1024;
    doneFlag = false;
    metaString = "";

    std::ifstream file;
	
    file.open(fileName, std::ios::binary);

    
    while (file.good())
    { 
        char byte;
        file.read(&byte, 1);

        operator<<(byte);
    }

    file.close();
}


void tcStream::SaveToFile(const char* fileName)
{
    std::ofstream file;
	
    file.open(fileName, std::ios::binary);

    while (!eof())
    {
        char byte;
        operator>>(byte);

        file.write(&byte, 1);
    }

    file.close();
}

/**
* @return detail level for stream
*/
int tcStream::GetDetailLevel() const
{
    return detailLevel;
}

/**
* Sets detail level for stream. This controls what state
* data is written to the stream by game objects. detailLevel
* has no effect during read.
*/
void tcStream::SetDetailLevel(int dl)
{
    detailLevel = dl;
}


bool tcStream::GetDoneFlag() const
{
    return doneFlag;
}

void tcStream::SetDoneFlag(bool state)
{
    doneFlag = state;
}


size_t tcStream::GetMaxSize() const
{
    return maxSize;
}

void tcStream::SetMaxSize(size_t n)
{
    maxSize = n;
}

const std::string& tcStream::GetMetaString() const
{
	return metaString;
}

void tcStream::SetMetaString(const std::string& s)
{
	metaString = s;
}

/*** write operators ***/

tcStream& tcStream::operator<<(const int& val)
{
    wxASSERT(direction != OUTPUT);

    write((char*)&val, sizeof(val));      
    return *this;
}

tcStream& tcStream::operator<<(const long& val)
{
    wxASSERT(direction != OUTPUT);

    write((char*)&val, sizeof(val));   
    return *this;
}

tcStream& tcStream::operator<<(const short& val)
{
    wxASSERT(direction != OUTPUT);

    write((char*)&val, sizeof(val));   
    return *this;
}

tcStream& tcStream::operator<<(const char& val)
{
    wxASSERT(direction != OUTPUT);

    write((char*)&val, sizeof(val));   
    return *this;
}

tcStream& tcStream::operator<<(const unsigned char& val)
{
    wxASSERT(direction != OUTPUT);

    write((char*)&val, sizeof(val));   
    return *this;
}

tcStream& tcStream::operator<<(const unsigned short& val)
{
    wxASSERT(direction != OUTPUT);

    write((char*)&val, sizeof(val));   
    return *this;
}

tcStream& tcStream::operator<<(const unsigned int& val)
{
    wxASSERT(direction != OUTPUT);

    write((char*)&val, sizeof(val));   
    return *this;
}

tcStream& tcStream::operator<<(const unsigned long& val)
{
    wxASSERT(direction != OUTPUT);

    write((char*)&val, sizeof(val));   
    return *this;
}

tcStream& tcStream::operator<<(const bool& val)
{
    wxASSERT(direction != OUTPUT);

    write((char*)&val, sizeof(val));   
    return *this;
}

tcStream& tcStream::operator<<(const float& val)
{
    wxASSERT(direction != OUTPUT);

    write((char*)&val, sizeof(val));   
    return *this;
}

tcStream& tcStream::operator<<(const double& val)
{
    wxASSERT(direction != OUTPUT);

    write((char*)&val, sizeof(val));   
    return *this;
}

tcStream& tcStream::operator<<(const std::string& val)
{
    wxASSERT(direction != OUTPUT);

    size_t len = val.size();
	if (len >= 2048)
	{
        fprintf(stderr, "tcStream::operator<<(std::string& val) - length overflow, truncating (%d)\n",
			len);
		len = 2047; // truncate
        wxASSERT(false);
	}
    write((char*)&len, sizeof(len));
    write(val.c_str(), (std::streamsize)len);

    return *this;
}


tcStream& tcStream::operator<<(const wxString& val)
{
    wxASSERT(direction != OUTPUT);

    size_t len = val.size();
	if (len >= 2048)
	{
        fprintf(stderr, "tcStream::operator<<(const wxString& val) - length overflow, truncating (%d)\n",
			len);
		len = 2047; // truncate
        wxASSERT(false);
	}
    write((char*)&len, sizeof(len));
    write(val.c_str(), (std::streamsize)len);

    return *this;
}


tcStream& tcStream::operator<<(const tcStream& stream)
{
    wxASSERT(direction != OUTPUT);

    size_t len = stream.size();
    write(stream.str().c_str(), (std::streamsize)len);

    return *this;
}

tcStream& tcStream::operator<<(const tcFloatCompressor& x)
{
    x.WriteTo(*this);

    return *this;
}

tcStream& tcStream::operator<<(const std::vector<std::string>& val)
{
    unsigned int nVal = val.size();
    *this << nVal;
    
    for (unsigned int n=0; n<nVal; n++)
    {
        *this << val[n];
    }

    return *this;
}

tcStream& tcStream::operator<<(const std::vector<unsigned int>& val)
{
    unsigned int nVal = val.size();
    *this << nVal;
    
    for (unsigned int n=0; n<nVal; n++)
    {
        *this << val[n];
    }

    return *this;
}



void tcStream::WriteCheckValue(int val)
{
    operator<<(val);
}



/*** read operators ***/

tcStream& tcStream::operator>>(int& val)
{
    wxASSERT(direction != INPUT);

    read((char*)&val, sizeof(val));      
    return *this;
}

tcStream& tcStream::operator>>(long& val)
{
    wxASSERT(direction != INPUT);

    read((char*)&val, sizeof(val));   
    return *this;
}

tcStream& tcStream::operator>>(short& val)
{
    wxASSERT(direction != INPUT);

    read((char*)&val, sizeof(val));   
    return *this;
}

tcStream& tcStream::operator>>(char& val)
{
    wxASSERT(direction != INPUT);

    read((char*)&val, sizeof(val));   
    return *this;
}

tcStream& tcStream::operator>>(unsigned char& val)
{
    wxASSERT(direction != INPUT);

    read((char*)&val, sizeof(val));   
    return *this;
}

tcStream& tcStream::operator>>(unsigned short& val)
{
    wxASSERT(direction != INPUT);

    read((char*)&val, sizeof(val));   
    return *this;
}

tcStream& tcStream::operator>>(unsigned int& val)
{
    wxASSERT(direction != INPUT);

    read((char*)&val, sizeof(val));   
    return *this;
}

tcStream& tcStream::operator>>(unsigned long& val)
{
    wxASSERT(direction != INPUT);

    read((char*)&val, sizeof(val));   
    return *this;
}

tcStream& tcStream::operator>>(bool& val)
{
    wxASSERT(direction != INPUT);

    read((char*)&val, sizeof(val));   
    return *this;
}

tcStream& tcStream::operator>>(float& val)
{
    wxASSERT(direction != INPUT);

    read((char*)&val, sizeof(val));   
    return *this;
}

tcStream& tcStream::operator>>(double& val)
{
    wxASSERT(direction != INPUT);

    read((char*)&val, sizeof(val));   
    return *this;
}

tcStream& tcStream::operator>>(std::string& val)
{
    wxASSERT(direction != INPUT);

    size_t len;

    read((char*)&len, sizeof(len));
    if (len >= 2048)
    {
        fprintf(stderr, "tcStream::operator>>(std::string& val) - length overflow (%d)\n",
			len);
        wxASSERT(false);
    }
    else
    {
        char* buffer = new char[len+1];
        read(buffer, (std::streamsize)len);
        buffer[len] = 0; // add terminating null char
        val = buffer;
        delete buffer;
    }

    return *this;
}

tcStream& tcStream::operator>>(wxString& val)
{
    wxASSERT(direction != INPUT);

    size_t len;

    read((char*)&len, sizeof(len));
    if (len >= 2048)
    {
        fprintf(stderr, "tcStream::operator>>(wxString& val) - length overflow (%d)\n",
			len);
        wxASSERT(false);
    }
    else
    {
        char* buffer = new char[len+1];
        read(buffer, (std::streamsize)len);
        buffer[len] = 0; // add terminating null char
        val = buffer;
        delete buffer;
    }

    return *this;
}

tcStream& tcStream::operator>>(tcStream& stream)
{
    wxASSERT(direction != INPUT);

    size_t len = size();
    stream.write(str().c_str(), (std::streamsize)len);

    return *this;
}

tcStream& tcStream::operator>>(tcFloatCompressor& x)
{
    x.ReadFrom(*this);

    return *this;
}

tcStream& tcStream::operator>>(std::vector<std::string>& val)
{
    unsigned int nVal;
    *this >> nVal;

    val.clear();
    
    for (unsigned int n=0; n<nVal; n++)
    {
        std::string valn;
        *this >> valn;
        val.push_back(valn);
    }

    return *this;
}

tcStream& tcStream::operator>>(std::vector<unsigned int>& val)
{
    unsigned int nVal;
    *this >> nVal;

    val.clear();
    
    for (unsigned int n=0; n<nVal; n++)
    {
        unsigned int valn;
        *this >> valn;
        val.push_back(valn);
    }

    return *this;
}



/**
* @return true if stream value matches expected check value
*/
bool tcStream::ReadCheckValue(int val)
{
    int streamVal;
    operator>>(streamVal);

    if (streamVal == val)
    {
        return true;
    }
    else
    {
        fprintf(stderr, "tcStream::ReadCheckValue - Stream check failed (%d != %d)\n",
            streamVal, val);
        wxASSERT(false);
        throw "Stream corruption";
        return false;
    }
}