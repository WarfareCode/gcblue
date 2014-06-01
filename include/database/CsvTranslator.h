/**  
**  @file CsvTranslator.h
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

#ifndef _CSVTRANSLATOR_H_
#define _CSVTRANSLATOR_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

namespace database
{
/**
* Translate (read from/write to) comma separated value (CSV) files
*/
class CsvTranslator
{
    public:
    /// SetInputStream must be called if fin is NULL or defaults to NULL
       CsvTranslator(std::istream* fin = NULL, std::ostream* fout = NULL, std::string sep = ",") :
		isWriteLineBlocked(false), inputStream(fin), outputStream(fout), fieldsep(sep), fieldIdx(0)
        {}

	int GetLine(std::string&);
	std::string GetField(int n);
    float GetFieldAsFloat(int n);
    int GetFieldAsInt(int n);
	long GetFieldAsLong(int n);
	int GetFieldCount() const { return nfield; }
    void SetInputStream(std::istream* _inputStream) {inputStream = _inputStream;}
    void SetOutputStream(std::ostream* _outputStream);
    void SetWriteLineBlock(bool isBlocked) {isWriteLineBlocked = isBlocked;}
    void WriteField(double val);  ///< writes double to next field
    void WriteField(long val);    ///< writes long to next field
    void WriteField(std::string s);    ///< writes string to next field
    int WriteLine();  ///< writes fields to next line of CSV file

    CsvTranslator& operator>>(float& val);
    CsvTranslator& operator>>(double& val);
    CsvTranslator& operator>>(int& val);
	CsvTranslator& operator>>(short& val);
    CsvTranslator& operator>>(unsigned int& val);
	CsvTranslator& operator>>(unsigned short& val);
    CsvTranslator& operator>>(long& val); 
	CsvTranslator& operator>>(unsigned long& val); 
    CsvTranslator& operator>>(std::string& s);   

    CsvTranslator& operator<<(double val);
    CsvTranslator& operator<<(long val);   
    CsvTranslator& operator<<(std::string s);   

  private:
    bool isWriteLineBlocked;     ///< workaround to support DB objects inheriting from leaf DB objects
	std::istream* inputStream;   ///< input stream
    std::ostream* outputStream;  ///< output stream
	std::string line;            ///< input line
	std::vector<std::string> field;   ///< field strings
	int nfield;             ///< number of fields
	std::string fieldsep;        ///< separator characters
    int fieldIdx;           ///< field index for writing

	int ParseLine();
	int EndOfLine(char);
	int AdvPlain(const std::string& line, std::string& fld, int);
	int AdvQuoted(const std::string& line, std::string& fld, int);
};

}

#endif

