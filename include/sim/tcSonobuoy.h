/**
**  @file tcSonobuoy.h
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
#ifndef _TCSONOBUOY_H_
#define _TCSONOBUOY_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "tcGameObject.h"
#include "tcSensorPlatform.h"

namespace database
{
    class tcSonobuoyDBObject;
}
using database::tcSonobuoyDBObject;

class tcGameObject;
class tcGameStream;

/**
* Sonobuoy model
*/
class tcSonobuoy : public tcGameObject, public tcSensorPlatform
{
public:
    virtual void Clear();
    void PrintToFile(tcFile& file);
    void SaveToFile(tcFile& file);
    void LoadFromFile(tcFile& file);
    virtual void Serialize(tcFile& file, bool mbLoad);

    virtual void LaunchFrom(tcGameObject* obj, unsigned nLauncher);
    virtual void Update(double afStatusTime);

    virtual tcGameStream& operator<<(tcGameStream& stream);
    virtual tcGameStream& operator>>(tcGameStream& stream);

    tcSonobuoy();
    tcSonobuoy(tcSonobuoy&);
    tcSonobuoy(tcSonobuoyDBObject* obj);
    virtual ~tcSonobuoy();

private:
    tcSonobuoyDBObject* mpDBObject;
    float batteryTimeRemaining_s;
    long parentId;
	float sonobuoyDepth_m;

    void UpdateDrop(float dt_s);
};

#endif