/*  
**  @file tcFloatCompressor.h
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

#ifndef _TCFLOATCOMPRESSOR_H_
#define _TCFLOATCOMPRESSOR_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class tcStream;


/**
* This class works with tcStream to compress/decompress floating point values
* to/from integer representation
* Used to save network bandwidth for multiplayer
*/
class tcFloatCompressor
{
public:

    virtual void WriteTo(tcStream& stream) const;
    virtual void ReadFrom(tcStream& stream);

    explicit tcFloatCompressor(float& val_);
    virtual ~tcFloatCompressor();

protected:
    float& val;
};


/**
* Maps radian angle over [-pi, pi) to short (2 byte) integer
*/
class tcAngleCompressor : public tcFloatCompressor
{
public:
    short Compress(float val);
    float Decompress(short val);

    void Test();

    virtual void WriteTo(tcStream& stream) const;
    virtual void ReadFrom(tcStream& stream);

    explicit tcAngleCompressor(float& val_);
    virtual ~tcAngleCompressor();

private:
    short compressedAngle;
};

/**
* Maps specified range to short (2 byte) integer
*/
class tcIntervalCompressor : public tcFloatCompressor
{
public:
    unsigned short Compress(float val);
    float Decompress(unsigned short val);

    void Test();

    virtual void WriteTo(tcStream& stream) const;
    virtual void ReadFrom(tcStream& stream);

    explicit tcIntervalCompressor(float& val_, float min_, float max_);
    virtual ~tcIntervalCompressor();

private:
    float minVal;
    float maxVal;

    unsigned short compressedValue;
};



#endif