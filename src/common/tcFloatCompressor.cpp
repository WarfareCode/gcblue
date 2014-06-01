/*  
**  @file tcFloatCompressor.cpp
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

#include "tcFloatCompressor.h"
#include "common/tcStream.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif




void tcFloatCompressor::WriteTo(tcStream& stream) const
{
}

void tcFloatCompressor::ReadFrom(tcStream& stream)
{
}

tcFloatCompressor::tcFloatCompressor(float& val_)
: val(val_)
{
}

tcFloatCompressor::~tcFloatCompressor()
{
}

////////////////// tcAngleCompressor ///////////////////

short tcAngleCompressor::Compress(float val)
{
    const float scale = float(65536.0 * 0.159154943);

    return short(scale*val);
}

float tcAngleCompressor::Decompress(short val)
{
    const float scale = float(6.28318531 * 1.52587891e-5);

    return scale * float(val);
}


void tcAngleCompressor::WriteTo(tcStream& stream) const
{
    stream.write((char*)&compressedAngle, sizeof(compressedAngle));   
}

void tcAngleCompressor::ReadFrom(tcStream& stream)
{
    stream.read((char*)&compressedAngle, sizeof(compressedAngle));

    val = Decompress(compressedAngle);
}

void tcAngleCompressor::Test()
{
    float minError_rad = 9999.9f;
    float maxError_rad = -9999.9f;

    for (float angle_rad=-3.14159265f; angle_rad<3.14159265f; angle_rad += 0.1f)
    {
        short compressed = Compress(angle_rad);
        float decompressed = Decompress(compressed);

        float error_rad = decompressed - angle_rad;

        minError_rad = std::min(error_rad, minError_rad);
        maxError_rad = std::max(error_rad, maxError_rad);
    }
}

tcAngleCompressor::tcAngleCompressor(float& val_)
: tcFloatCompressor(val_)
{
    compressedAngle = Compress(val);
}

tcAngleCompressor::~tcAngleCompressor()
{
}


////////////////// tcIntervalCompressor ///////////////////

unsigned short tcIntervalCompressor::Compress(float val)
{
    const float scale = float(65535.0 / (maxVal - minVal));

    val = std::min(val, maxVal);
    val = std::max(val, minVal);

    return unsigned short((val - minVal) * scale + 0.5f);
}

float tcIntervalCompressor::Decompress(unsigned short val)
{
    const float scale = float((maxVal - minVal) * 1.52590219e-5);

    return (scale * float(val)) + minVal;
}


void tcIntervalCompressor::WriteTo(tcStream& stream) const
{
    stream.write((char*)&compressedValue, sizeof(compressedValue));   
}

void tcIntervalCompressor::ReadFrom(tcStream& stream)
{
    stream.read((char*)&compressedValue, sizeof(compressedValue));

    val = Decompress(compressedValue);
}

void tcIntervalCompressor::Test()
{
    float minError = 9999.9f;
    float maxError = -9999.9f;

    for (float x=minVal; x<=maxVal; x += 0.1f)
    {
        unsigned short compressed = Compress(x);
        float decompressed = Decompress(compressed);

        float error = decompressed - x;

        minError = std::min(error, minError);
        maxError = std::max(error, maxError);
    }
}

tcIntervalCompressor::tcIntervalCompressor(float& val_, float min_, float max_)
: tcFloatCompressor(val_),
  minVal(min_), 
  maxVal(max_)
{
    wxASSERT(max_ > min_);
    compressedValue = Compress(val);
}

tcIntervalCompressor::~tcIntervalCompressor()
{
}