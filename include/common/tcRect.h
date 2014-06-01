/**
**  @file tcRect.h
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

#ifndef _TCRECT_H_
#define _TCRECT_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class tcStream;

class tcRect 
{
public:
    float left; // x1
    float right; // x2
    float top; // y2
    float bottom; // y1

    virtual bool ContainsPoint(float x, float y) const;
    virtual bool ContainsPointInclusive(float x, float y) const;
    virtual void Expand(float dx, float dy);
	virtual float GetLeft() const {return left;}
	virtual float GetRight() const {return right;}
	virtual float GetTop() const {return top;}
	virtual float GetBottom() const {return bottom;}
    virtual float Width() const {return right-left;}
    virtual float Height() const {return top-bottom;}
    virtual float XCenter() const {return 0.5f*(right+left);}
    virtual float YCenter() const {return 0.5f*(top+bottom);}
    virtual void Offset(float dx, float dy);
    virtual void Set(float x1,float x2,float y1,float y2) {left=x1;right=x2;bottom=y1;top=y2;}

    tcRect& operator=(const tcRect& r);
    bool operator==(const tcRect& r) const;
    bool operator!=(const tcRect& r);
    virtual tcStream& operator<<(tcStream& stream);
    virtual tcStream& operator>>(tcStream& stream);

    tcRect();
    tcRect(float x1, float x2, float y1, float y2);
    tcRect(const tcRect& r);
    virtual ~tcRect();
};


#endif

