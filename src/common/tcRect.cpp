/**
**  @file tcRect.cpp
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


#include "tcRect.h"
#include "common/tcStream.h"


/**
*
*/
tcRect& tcRect::operator=(const tcRect& r)
{
    left = r.left;
    right = r.right;
    bottom = r.bottom;
    top = r.top;

    return *this;
}

bool tcRect::operator==(const tcRect& r) const
{
    return (left == r.left) && (right == r.right) &&
           (bottom == r.bottom) && (top == r.top);
}

bool tcRect::operator!=(const tcRect& r)
{
    return (left != r.left) || (right != r.right) ||
           (bottom != r.bottom) || (top != r.top);
}

/**
* Load
*/
tcStream& tcRect::operator<<(tcStream& stream)
{
    stream >> left;
    stream >> right;
    stream >> top;
    stream >> bottom;

    return stream;
}

/**
* Save
*/
tcStream& tcRect::operator>>(tcStream& stream)
{
    stream << left;
    stream << right;
    stream << top;
    stream << bottom;

    return stream;
}

/**
* @return true if point (x, y) is within rectangle
* left and bottom borders are inclusive
*/
bool tcRect::ContainsPoint(float x, float y) const
{
	return (x >= left) && (x < right) && (y >= bottom) && (y < top);
}

/**
* @return true if point (x, y) is within rectangle
* ALL borders are inclusive for this version
*/
bool tcRect::ContainsPointInclusive(float x, float y) const
{
	return (x >= left) && (x <= right) && (y >= bottom) && (y <= top);
}

/**
*
*/
void tcRect::Expand(float dx, float dy)
{
    left -= dx;
    right += dx;
    bottom -= dy;
    top += dy;
}

/**
*
*/
void tcRect::Offset(float dx, float dy) 
{
    left += dx;
    right += dx;
    bottom += dy;
    top += dy;
}




/**
*
*/
tcRect::tcRect()
: left(0), right(0), bottom(0), top(0)
{
}

/**
*
*/
tcRect::tcRect(float x1, float x2, float y1, float y2)
: left(x1), right(x2), bottom(y1), top(y2)

{
}

/**
*
*/
tcRect::tcRect(const tcRect& r)
: left(r.left),
  right(r.right),
  bottom(r.bottom),
  top(r.top)
{
}

/**
*
*/
tcRect::~tcRect()
{
}
