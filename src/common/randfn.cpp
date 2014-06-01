/**
**  @file randfn.cpp
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

#include "randfn.h"
#include "tcFile.h"

unsigned int Poisson(float lambda)
{
    wxASSERT(lambda > 0);

    if (lambda > 8.0)
    {
        return unsigned int(lambda);
    }

    float L = expf(-lambda);

    unsigned int k = 0;
    float p = 1.0f;

    bool generating = true;

    while (generating)
    {
        k++;
        p *= randf();
        generating = (p >= L);
    }

    return (k - 1);
}


GaussianRandom* GaussianRandom::Get()
{
    static GaussianRandom instance;

    return &instance;
}



/** 
* @return unit variance, 0 mean gaussian random number
* Generates pairs at a time
*/
float GaussianRandom::randn()
{
    static bool cacheIsValid = false;
    static float cacheValue = 0;

    if (cacheIsValid)
    {
        cacheIsValid = false;
        return cacheValue;
    }

    float x1 = randf();
    float x2 = randf();

    float mag = sqrtf(-2.0f * logf(x1));
    float phase = 6.2831853f * x2;

    float y1 = mag * cosf(phase);
    float y2 = mag * sinf(phase);

    cacheValue = y1;
    cacheIsValid = true;
    return y2;

}

/** 
* This version randomly reads from a pre-generated table
* @return unit variance, 0 mean gaussian random number
*/
float GaussianRandom::randn_fast()
{
    //size_t table_idx = rand() % TABLE_SIZE;
    size_t table_idx = rand() & (TABLE_SIZE-1); // assumes power of 2 table size

    return prestored[table_idx];
}

/**
* Generates table for randn_fast
*/
void GaussianRandom::GenerateTable()
{
    for (size_t k=0; k<TABLE_SIZE; k++)
    {
        prestored[k] = randn();
    }
}

void GaussianRandom::WriteTableToFile(const std::string& filename)
{
    tcFile log;
    log.Open(filename.c_str(), tcFile::modeWrite | tcFile::modeText);

    for (size_t k=0; k<TABLE_SIZE; k++)
    {
        wxString line;
        line.Printf("%f\n", prestored[k]);

        log.WriteString(line.c_str());
    }

    log.Close();
}

GaussianRandom::GaussianRandom()
{
    GenerateTable();
}

GaussianRandom::~GaussianRandom()
{
}



