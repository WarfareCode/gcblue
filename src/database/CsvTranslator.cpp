/*  
**  CsvTranslator.cpp
**
**  This file uses excerpts from 'The Practice of Programming'
**  by Brian W. Kernighan and Rob Pike, Copyright(C) 1999 Lucent Technologies
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

#if _MSC_VER > 1000
#pragma warning(disable:4786) // suppress warning for STL bug in VC6, see Q167355 in the MSDN Library.
#endif // _MSC_VER > 1000


#include "CsvTranslator.h"
#include "stdio.h"


using namespace std;

namespace database
{
/**
* endofline: check for and consume \r, \n, \r\n, or EOF
*/
int CsvTranslator::EndOfLine(char c)
{
    int eol;

    eol = (c=='\r' || c=='\n');
    if (c == '\r')
    {
		inputStream->get(c);
		if (!inputStream->eof() && c != '\n')
        {
		    inputStream->putback(c);	// read too far
        }
    }
    return eol;
}

// getline: get one line, grow as needed
int CsvTranslator::GetLine(string& str)
{	
    char c;

    for (line = ""; inputStream->get(c) && !EndOfLine(c); )
    {
		line += c;
    }
	ParseLine();
	str = line;
    fieldIdx = 0; // set to zero for >> operator
	return !inputStream->eof();
}

// split: split line into fields
int CsvTranslator::ParseLine()
{
	string fld;
	unsigned int i, j;

	nfield = 0;
	if (line.length() == 0) return 0;
	i = 0;

    do
    {
		if (i < line.length() && line[i] == '"')
			j = AdvQuoted(line, fld, ++i);	// skip quote
		else
			j = AdvPlain(line, fld, i);
		if ((unsigned)nfield >= field.size())
			field.push_back(fld);
		else
			field[nfield] = fld;
		nfield++;
		i = j + 1;
	}
    while (j < line.length());

	return nfield;
}

// advquoted: quoted field; return index of next separator
int CsvTranslator::AdvQuoted(const string& s, string& fld, int i)
{
    unsigned int j;

    fld = "";
    for (j = i; j < s.length(); j++)
    {
        if (s[j] == '"' && s[++j] != '"')
        {
			unsigned k = (unsigned)s.find_first_of(fieldsep, j);
			if (k > (unsigned)s.length())	// no separator found
				k = (unsigned)s.length();
			for (k -= j; k-- > 0; )
				fld += s[j++];
			break;
		}
		fld += s[j];
	}
	return j;
}

// advplain: unquoted field; return index of next separator
int CsvTranslator::AdvPlain(const string& s, string& fld, int i)
{
	unsigned j;

	j = (unsigned)s.find_first_of(fieldsep, i); // look for separator
	if (j > s.length())               // none found
		j = (unsigned)s.length();
	fld = string(s, i, j-i);
	return j;
}


// getfield: return n-th field
string CsvTranslator::GetField(int n)
{
	if (n < 0 || n >= nfield)
    {
        cerr << "Field out of bounds (GetField)\n";
		return "";
    }
	else
    {
		return field[n];
    }
}

/**
* @return field as float. Zero is returned if the field is empty.
* If the field has a bad format (e.g. a string field instead of a 
* numerical field), zero is returned and an error is logged.
*/
float CsvTranslator::GetFieldAsFloat(int n)
{
    float f;

	if (n < 0 || n >= nfield)
    {
        cerr << "Field out of bounds (GetFieldAsFloat)\n";
		return 0;
    }

    if (field[n].size() == 0) return 0; // do not log an error for null fields
// Change %d to %ld for long, %f for float, %lf for double
    int scanCount = sscanf(field[n].c_str(),"%f",&f);
    if (scanCount != 1)
    {
        fprintf(stderr, "Bad field type: '%s'(GetFieldAsFloat)\n",
            field[n].c_str());
		return 0;
    }
    return f;
}

/**
* @return field as integer. This will truncate a float.
* Zero is returned if the field is empty. If the field
* has a bad format (e.g. a string field instead of a 
* numerical field), zero is returned and an error is logged.
*/
int CsvTranslator::GetFieldAsInt(int n)
{
    int val;

	if (n < 0 || n >= nfield)
    {
        cerr << "Field out of bounds (GetFieldAsInt)\n";
		return -1;
    }
    if (field[n].size() == 0) return 0; // do not log an error for null fields

    int scanCount = sscanf(field[n].c_str(),"%d",&val);
    if (scanCount != 1)
    {
        fprintf(stderr, "Bad field type: '%s'(GetFieldAsInt)\n",
            field[n].c_str());
		return 0;
    }
    return val;
}

/**
* @return field as long integer. This will truncate a float.
* Zero is returned if the field is empty. If the field
* has a bad format (e.g. a string field instead of a 
* numerical field), zero is returned and an error is logged.
*/
long CsvTranslator::GetFieldAsLong(int n)
{
    long val;

	if (n < 0 || n >= nfield)
    {
        cerr << "Field out of bounds (GetFieldAsInt)\n";
		return -1;
    }
    if (field[n].size() == 0) return 0; // do not log an error for null fields

    int scanCount = sscanf(field[n].c_str(), "%d", &val);
    if (scanCount != 1)
    {
        fprintf(stderr, "Bad field type: '%s'(GetFieldAsLong)\n",
            field[n].c_str());
		return 0;
    }
    return val;
}

/**
* Set output stream. Reset field vector in case object has
* been used for reading.
*/
void CsvTranslator::SetOutputStream(ostream* _outputStream) 
{
    outputStream = _outputStream;
    field.clear();
}


/**
* Use float or double
*/
void CsvTranslator::WriteField(double val)
{
    char buff[64];
    sprintf(buff,"%lf",val);
    field.push_back(string(buff));
}


/**
* Use for int or long int
*/
void CsvTranslator::WriteField(long val)
{
    char buff[64];
    sprintf(buff,"%ld",val);
    field.push_back(string(buff));
}

void CsvTranslator::WriteField(string s)
{
    field.push_back(s);
}

int CsvTranslator::WriteLine()
{
    if (isWriteLineBlocked) return 1; 

    for (int n=0;n<(int)field.size()-1;n++)
    {
        *outputStream << field[n] << fieldsep;
    }
    *outputStream << field[field.size()-1] << "\n";
    field.clear();
    return 1;
}

CsvTranslator& CsvTranslator::operator>>(float& val)
{
    val = GetFieldAsFloat(fieldIdx++);
    return *this;
}

CsvTranslator& CsvTranslator::operator>>(double& val)
{
    val = GetFieldAsFloat(fieldIdx++);
    return *this;
}

CsvTranslator& CsvTranslator::operator>>(int& val)
{
    val = GetFieldAsInt(fieldIdx++);
    return *this;
} 

CsvTranslator& CsvTranslator::operator>>(short& val)
{
    val = (short int)GetFieldAsInt(fieldIdx++);
    return *this;
}

CsvTranslator& CsvTranslator::operator>>(unsigned int& val)
{
    val = (unsigned int)GetFieldAsInt(fieldIdx++);
    return *this;
} 

CsvTranslator& CsvTranslator::operator>>(unsigned short& val)
{
	val = (unsigned short)GetFieldAsInt(fieldIdx++);
	return *this;
}

CsvTranslator& CsvTranslator::operator>>(long& val)
{
    val = GetFieldAsInt(fieldIdx++);
    return *this;
} 

CsvTranslator& CsvTranslator::operator>>(unsigned long& val)
{
    val = GetFieldAsInt(fieldIdx++);
    return *this;
} 

CsvTranslator& CsvTranslator::operator>>(std::string& s)
{
    s = GetField(fieldIdx++);
    return *this;
}   

CsvTranslator& CsvTranslator::operator<<(double val)
{
    WriteField(val);
    return *this;
}

CsvTranslator& CsvTranslator::operator<<(long val)
{
    WriteField(val);
    return *this;
}   

CsvTranslator& CsvTranslator::operator<<(std::string s)
{
    WriteField(s);
    return *this;
}  

}
