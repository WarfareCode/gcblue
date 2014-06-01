/*  
**  @file tcPanelInterface.cpp
**  Python interface to tcPanel for scripting
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

#include "stdwx.h" // precompiled header file

#ifndef WX_PRECOMP
#include "wx/wx.h"
#ifdef WIN32
#include "wx/msw/private.h" // for MS Windows specific definitions
#endif // WIN32
#endif

#include "tcPanelInterface.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif 

namespace scriptinterface {

    void tcPanelInterface::AddItem(std::string caption, std::string command, 
        float x, float y, float width, float height)
    {
        if (mpPanel == NULL) {return;}
        mpPanel->AddItem(caption, command, x, y, width, height);
    }

    void tcPanelInterface::AddItemWithParam(std::string caption, std::string command, int param,
        float x, float y, float width, float height)
    {
        if (mpPanel == NULL) {return;}
        mpPanel->AddItem(caption, command, x, y, width, height, param);
    }

    void tcPanelInterface::AddItemUI(std::string caption, std::string callback, std::string input,
        float x, float y, float width, float height)
    {
        AddItemUIWithParam(caption,callback,input,-1,x,y,width,height);
    }

    void tcPanelInterface::AddItemUIWithParam(std::string caption, std::string callback, std::string input,
        int param, float x, float y, float width, float height)
    {
        if (mpPanel == NULL) {return;}
        char zBuff[64];
        strcpy(zBuff,input.c_str());
        if ((strcmp(zBuff,"Heading")!=0)&&(strcmp(zBuff,"Target")!=0)&&(strcmp(zBuff,"Datum")!=0)) {
            return;
        }
        mpPanel->AddItemUI(caption, callback, input, x, y, width, height, param);
    }

    void tcPanelInterface::BoldLastItem()
    {
        if (mpPanel == NULL) {return;}
        mpPanel->BoldLastItem();
    }

    void tcPanelInterface::Clear(void) 
    {
        if (mpPanel == NULL) {return;}
        mpPanel->Clear();
    }

    void tcPanelInterface::SetTitle(std::string new_title)
    {
        if (mpPanel == NULL) {return;}
        mpPanel->SetTitle(new_title);
    }

    tcPanel* tcPanelInterface::mpPanel = NULL;
}

