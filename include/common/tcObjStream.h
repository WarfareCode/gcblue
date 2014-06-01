/**  
**  @file tcObjStream.h
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

#ifndef _TCOBJSTREAM_H_
#define _TCOBJSTREAM_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "common/tcStream.h"

class tcCommandStream;
class tcCreateStream;
class tcUpdateStream;

/** 
 * This file holds the classes derived from tcStream that are used for obj
 * updates for multiplayer. If these grow in complexity, split into separate
 * files.
 */

/**
* Stream with all data necessary to create object (at client)
*/
class tcCreateStream : public tcStream
{
public:
	tcCommandStream& AsCommandStream();
    tcCreateStream();
    tcCreateStream(const char* data, std::streamsize count);
    explicit tcCreateStream(const tcStream& stream);
};

/**
* Stream for basic update of object kinematic state
*/
class tcUpdateStream : public tcStream
{
public:
    tcUpdateStream();
    tcUpdateStream(const char* data, std::streamsize count);
    explicit tcUpdateStream(const tcStream& stream);
    tcUpdateStream(const tcUpdateStream& stream);
};

/**
* Stream for update of command-related state, such as guidance
* changes, AI orders
*/
class tcCommandStream : public tcStream
{
public:
	tcCreateStream& AsCreateStream();

    tcCommandStream();
    tcCommandStream(const char* data, std::streamsize count);
    explicit tcCommandStream(const tcStream& stream);
};

#endif