/** 
**  @file tcCommandObject.h
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

#ifndef _TCCOMMANDOBJECT_H_
#define _TCCOMMANDOBJECT_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class tcCommandStream;
class tcGameStream;
class tcLauncher;

/**
* Class to provide methods and variables for multiplayer command management
* In some cases both the parent of a class and the class itself can derive
* from this.
*/
class tcCommandObject
{
public:
    void ClearNewCommand();
    bool HasNewCommand() const;

    void SetNewCommand(int flag);

    static void SetClientMode(bool state) {clientMode = state;}

    tcGameStream& operator<<(tcGameStream& stream);
    tcGameStream& operator>>(tcGameStream& stream);

    tcCommandObject();
    virtual ~tcCommandObject();

private:
    /** 
    * bitfield to manage acknowledgement for command updates.
    * appropriate bit is set when new command update is generated,
    * bit is cleared when ack update is received.
    */
    int commandStatus; 

    static bool clientMode; ///< true if running as multiplayer client
};

#endif