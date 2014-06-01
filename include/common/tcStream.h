/**  
**  @file tcStream.h
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

#ifndef _TCSTREAM_H_
#define _TCSTREAM_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <sstream>
#include <vector>
#include <wx/string.h>

class tcFloatCompressor;

class tcStream : protected std::stringstream
{
public:
    enum
    {
        WRITE_DYNAMIC = 0,
        WRITE_ALL = 1
    };
    enum StreamDirection 
    {
        UNDEFINED = 0, 
        INPUT = 1, 
        OUTPUT = 2
    };

    void clear();
    bool eof();
    void read(char* buff, std::streamsize count);
    size_t size() const;
    void skip_read(unsigned int count);
    int tellp();
    void write(const char* buff, std::streamsize count);
	const std::string& asString();

    void LoadFromFile(const char* fileName);
    void SaveToFile(const char* fileName);

    int GetDetailLevel() const;
    void SetDetailLevel(int dl);

	const std::string& GetMetaString() const;
	void SetMetaString(const std::string& s);

    size_t GetMaxSize() const;
    void SetMaxSize(size_t n);

    bool GetDoneFlag() const;
    void SetDoneFlag(bool state);

    StreamDirection GetDirection() const;
    void SetDirection(StreamDirection dir);

    void WriteCheckValue(int val);
    bool ReadCheckValue(int val);


    /// write operators
    tcStream& operator<<(const int& val);
    tcStream& operator<<(const long& val);
    tcStream& operator<<(const short& val);
    tcStream& operator<<(const bool& val);
    tcStream& operator<<(const char& val);
    tcStream& operator<<(const unsigned char& val);
    tcStream& operator<<(const unsigned short& val);
    tcStream& operator<<(const unsigned int& val);
	tcStream& operator<<(const unsigned long& val);
    tcStream& operator<<(const float& val);
    tcStream& operator<<(const double& val);
    tcStream& operator<<(const std::string& val);
    tcStream& operator<<(const wxString& val);
    tcStream& operator<<(const tcStream& stream);
    tcStream& operator<<(const tcFloatCompressor& x);
    tcStream& operator<<(const std::vector<std::string>& val);
    tcStream& operator<<(const std::vector<unsigned int>& val);

    /// read operators
    tcStream& operator>>(int& val);
    tcStream& operator>>(long& val);
    tcStream& operator>>(short& val);
    tcStream& operator>>(bool& val);
	tcStream& operator>>(char& val);
    tcStream& operator>>(unsigned char& val);
    tcStream& operator>>(unsigned short& val);
    tcStream& operator>>(unsigned int& val);
	tcStream& operator>>(unsigned long& val);
    tcStream& operator>>(float& val);
    tcStream& operator>>(double& val);
    tcStream& operator>>(std::string& val);
    tcStream& operator>>(wxString& val);
    tcStream& operator>>(tcStream& stream);
    tcStream& operator>>(tcFloatCompressor& x);
    tcStream& operator>>(std::vector<std::string>& val);
    tcStream& operator>>(std::vector<unsigned int>& val);

    tcStream(const char* data, std::streamsize count); ///< creates stream from char array
    tcStream(const tcStream& stream);
    tcStream();
private:
    int detailLevel;
	std::string metaString; ///< additional data
    size_t maxSize;
    bool doneFlag;
    StreamDirection direction;
};


#endif
