/**
**  @file tcDBObjSerializer.h
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

#ifndef _DBOBJSERIALIZER_H_
#define _DBOBJSERIALIZER_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "tcDatabase.h"
#include "CsvTranslator.h"
#include <iostream>
#include <fstream>
#include <string>

/** 
* Saves/loads objects of class T from database. 
* Class T is any class derived from tcDatabaseObject.
* Class T should be a leaf class for this to work properly.
*/
namespace database
{

template <class T> 
class tcDBObjSerializer
{
public:
    tcDBObjSerializer(std::string s, tcDatabase *db)
        : fileName(s), database(db) {}
    bool LoadCsv();
    bool SaveCsv();
private:
    std::string fileName;
    tcDatabase *database;
    
};

template <class T>
bool tcDBObjSerializer<T>::LoadCsv()
{ 
    std::ifstream infile; 
    CsvTranslator csv;
    std::string errorString = "Error - tcDatabase::SerializeCSV - error with file: ";
    errorString += fileName;

    infile.open(fileName.c_str());
    if (infile.fail()) 
    {
        wxMessageBox(errorString.c_str(),"Error",wxICON_ERROR);
        return false;
    }
    csv.SetInputStream(&infile);


    std::string line;
    // get column header line
    if (csv.GetLine(line) == 0)
    {
        errorString += "(empty file)";
        wxMessageBox(errorString.c_str(),"Error",wxICON_ERROR);
        return false;
    }


    while (csv.GetLine(line) != 0)
    {
        long key;
        T* obj = new T;
        obj->SerializeCSV(&csv, true); // load obj data from file
        database->mcObjectData.AddElement(obj, key); // add to database, key gets new key val
        obj->mnKey = key; // set key val of object (may not be necessary anymore)
    }

    infile.close();
    return true;
}


template <class T>
bool tcDBObjSerializer<T>::SaveCsv()
{
    std::ofstream outfile;
    CsvTranslator csv;
    std::string errorString = "Error - tcDatabase::SerializeCSV - error with file: ";
    errorString += fileName;
    
    
    long key;
    long nEntries = database->mcObjectData.GetCount();
    tcDatabaseObject *dbObj;
    
    
    long pos = database->mcObjectData.GetStartPosition();
    outfile.open(fileName.c_str());
    if (outfile.fail()) 
    {
        wxMessageBox(errorString.c_str(),"Error",wxICON_ERROR);
        return false;
    }
    csv.SetOutputStream(&outfile);
    T::WriteCSVHeader(&csv);
    for (long n=0;n<nEntries;n++) 
    {
        database->mcObjectData.GetNextAssoc(pos,key,dbObj);
        if (T* obj = dynamic_cast<T*>(dbObj))
        {
            obj->SerializeCSV(&csv, false);
        }
    }
    outfile.close();
    
    
    return true;
}

} // namespace database

#endif

