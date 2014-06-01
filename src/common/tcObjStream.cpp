/*  
**  @file tcObjStream.cpp
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

#include "common/tcStream.h"
#include "common/tcObjStream.h"
#include <iostream>
#include <sstream>


// ------------------------- tcCreateStream -------------------------

/**
* Added crosscast as workaround to support mixtures of streams
*/
tcCommandStream& tcCreateStream::AsCommandStream()
{
	return (tcCommandStream&)(*this);
}

/**
*
*/
tcCreateStream::tcCreateStream(const char* data, std::streamsize count)
: tcStream(data, count)
{
}


/**
* copy constructor
*/
tcCreateStream::tcCreateStream(const tcStream& stream)
: tcStream(stream)
{

}

/**
*
*/
tcCreateStream::tcCreateStream()
{
}

// ------------------------- tcCommandStream -------------------------

/**
* Added crosscast as workaround to support mixtures of streams
*/
tcCreateStream& tcCommandStream::AsCreateStream()
{
	return (tcCreateStream&)(*this);
}

/**
*
*/
tcCommandStream::tcCommandStream(const char* data, std::streamsize count)
: tcStream(data, count)
{
}

/**
* copy constructor
*/
tcCommandStream::tcCommandStream(const tcStream& stream)
: tcStream(stream)
{

}

/**
*
*/
tcCommandStream::tcCommandStream()
{
}

// ------------------------- tcUpdateStream -------------------------

/**
*
*/
tcUpdateStream::tcUpdateStream(const char* data, std::streamsize count)
: tcStream(data, count)
{
}


tcUpdateStream::tcUpdateStream(const tcStream& stream)
: tcStream(stream)
{

}

/**
* copy constructor
*/
tcUpdateStream::tcUpdateStream(const tcUpdateStream& stream)
: tcStream(stream)
{

}


tcUpdateStream::tcUpdateStream()
{
}
