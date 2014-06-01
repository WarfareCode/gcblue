/** @file tcCommandObject.cpp
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

#include "tcCommandObject.h"
#include "tcLauncher.h"
#include "common/tcStream.h"
#include "common/tcObjStream.h"
#include "tcGameStream.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

bool tcCommandObject::clientMode = false;


tcGameStream& tcCommandObject::operator<<(tcGameStream& stream)
{
    stream >> commandStatus;

    return stream;
}

tcGameStream& tcCommandObject::operator>>(tcGameStream& stream)
{
    stream << commandStatus;

    return stream;
}


void tcCommandObject::ClearNewCommand()
{
    commandStatus = 0;
}

bool tcCommandObject::HasNewCommand() const
{
    return (commandStatus != 0);
}


/**
* Called on new command. Sets bit in commandStatus and 
* sets newCommand to true.
*/
void tcCommandObject::SetNewCommand(int flag) 
{
    commandStatus |= flag;
}


tcCommandObject::tcCommandObject()
:   commandStatus(0)
{
}

tcCommandObject::~tcCommandObject()
{
}