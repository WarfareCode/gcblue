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

#include "tcFile.h"


int tcFile::Open(const char *azFileName, unsigned int anFlags) 
{
	errno_t err = 1;

    if (mpFile != NULL) 
    {
        fclose(mpFile);
        mpFile = NULL;
    }

    if (anFlags & modeRead) 
    {
        if (anFlags & modeText)
            err = fopen_s(&mpFile, azFileName, "rt");
        else
            err = fopen_s(&mpFile, azFileName, "rb");
    }
    else if (anFlags & modeWrite) 
    {
        if (anFlags & modeText)
            err = fopen_s(&mpFile, azFileName, "wt");
        else
            err = fopen_s(&mpFile, azFileName, "wb");
    }
	
	if (err != 0) mpFile = NULL;

    return mpFile != NULL;
}

int tcFile::Close() 
{
    if (mpFile == 0) {return false;}
	int val = fclose(mpFile);
	if (val == 0)
	{
		mpFile = 0;
	}
    return val;
}

/**
* Version to write to file using a printf-like format string
*/
void tcFile::Printf(const char* formatString, ...)
{
    enum {STR_LENGTH = 1024};
    static char textBuffer[STR_LENGTH];
    
    va_list arguments;

    va_start(arguments, formatString);
    _vsnprintf_s(textBuffer, sizeof(textBuffer), _TRUNCATE, formatString, arguments);
    va_end(arguments);

    WriteString(textBuffer);
}

long tcFile::GetLength() 
{
    if (mpFile == NULL) {return 0;}

    long current_pos = ftell(mpFile);
    long file_length = 0;
    if (fseek(mpFile, 0L, SEEK_END) == 0)
    {
        file_length = ftell(mpFile);
    }
    fseek(mpFile, current_pos, SEEK_SET); // reset file pointer

    return file_length;
}

long tcFile::GetLengthFromCurrent() 
{
    if (mpFile == NULL) {return 0;}

    long current_pos = ftell(mpFile);
    long file_length = 0;
    if (fseek(mpFile, 0L, SEEK_END) == 0)
    {
        file_length = ftell(mpFile) - current_pos;
    }
    fseek(mpFile, current_pos, SEEK_SET); // reset file pointer

    return file_length;
}

/**
* @return true if file is opened
*/
bool tcFile::IsOpen() const
{
	return mpFile != NULL;
}

int tcFile::Read(void *apData, unsigned int anCount) 
{
    if (mpFile == NULL) 
    {
        return 0;
    }
    return (int)fread(apData,1,anCount,mpFile);
}

// reads up to 128 characters from file
int tcFile::ReadString(char *s)
{
    if (mpFile == NULL) return 0;
    return (fgets(s, 128, mpFile) != NULL);
}

// reads up to 128 characters from file
int tcFile::ReadString(tcString& s)
{
    char buff[255];
    if (mpFile == NULL) return 0;
    int result = (fgets(buff, 128, mpFile) != NULL);
    s = buff;
    return result;
}

/**
* @param offset offset in bytes from origin
* @param origin tcFile::begin or tcFile::current
* @return 0 on success
*/
int tcFile::Seek(int offset, unsigned int origin)
{
    if (mpFile == NULL) return 0xF;
    if (origin == current)
    {
        return fseek(mpFile, offset, SEEK_CUR);
    }
    else if (origin == begin)
    {
        return fseek(mpFile, offset, SEEK_SET);
    }
    else
    {
        return 0;
    }
}

int tcFile::Write(const void *apData, unsigned int anCount) 
{
    if (mpFile == NULL) return 0;
    
    return (int)fwrite(apData,anCount,1,mpFile);
}

void tcFile::WriteString(const char *azString) 
{
    if (mpFile == NULL) return;
    fputs(azString, mpFile); // doesn't write terminating null char
}


tcFile::tcFile() 
:  mpFile(0)
{
}

tcFile::tcFile(const std::string& fileName)
:  mpFile(0)
{
	if (Open(fileName.c_str(), modeWrite | modeText) == 0)
	{
		fprintf(stderr, "tcFile::tcFile - Error opening %s\n", fileName.c_str());
	}
}

tcFile::~tcFile() 
{
	if (IsOpen())
	{
		Close();
	}
}
