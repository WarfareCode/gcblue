/**  
**  @file tcMapAlertObject.h
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


#ifndef _TCMAPALERTOBJECT_H_
#define _TCMAPALERTOBJECT_H_

#if _MSC_VER > 1000
#pragma once
#endif 

#ifndef WX_PRECOMP
#include "wx/wx.h" 
#endif // WX_PRECOMP

#include "simmath.h"
#include <boost/shared_ptr.hpp>
#include "tv_types.h"
#include "tcMapObject.h"

class tc3DWindow2;

class tcStream;

class tcMapView;
class tcGeometry;

namespace scriptinterface
{
    class tcScenarioLogger;
}



/** 
* Class for displaying short term alert graphics on tactical map
*/
class tcMapAlertObject : public tcMapObject
{
public:
    std::string caption; ///< text to display

    virtual void Draw(tc3DWindow2* host);

    virtual bool ProcessKey(int keyCode);
    void LoadIcon(const std::string& fileName);

    void SetAlignBottom(bool state);

    virtual tcStream& operator<<(tcStream& stream);
    virtual tcStream& operator>>(tcStream& stream);

    tcMapAlertObject();
    tcMapAlertObject(const std::string& text, double x, double y, bool useRel = false);
    virtual ~tcMapAlertObject();
private:
    unsigned int birthCount;
    boost::shared_ptr<tcGeometry> icon;
    bool alignBottom; ///< true for bottom of icon to match y val
};

#endif

