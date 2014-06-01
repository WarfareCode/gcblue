/**  
**  @file tcPythonInterface.h
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

#ifndef __tcPythonInterface_h__
#define __tcPythonInterface_h__

#if _MSC_VER > 1000
#pragma once
#endif

#include "wx/wx.h"
#ifdef WIN32
#include "wx/msw/private.h" // for MS Windows specific definitions
#endif // WIN32
#include <string>
#include <boost/python.hpp>

//namespace boost
//{
//    namespace python
//    {
//		namespace api
//		{
//			class object;
//		}
//    }
//}

using namespace boost::python;

namespace scriptinterface 
{
    class tcPythonInterface 
	{
    public:
		object main_module;
		object main_namespace;
        //dict *mpDictionary;

        void Test();
        void Test2();
        void Test3();
        void Test4();
        char* ReadFile(const char* filename); 

        tcPythonInterface();
        virtual ~tcPythonInterface();
    };

    struct World 
	{
        void set(std::string msg) { this->msg = msg; }
        std::string greet() { return msg; }
        std::string msg;
    };


    class tcOutside 
	{
    public:
        int maValues[10];

        int GetValue(int n) {if ((n>0)&&(n<10)) {return maValues[n];} else return -1;}
    };

    class tcTest 
	{
    public:
        int x;
        int y;
        static tcOutside *mpOutside;

        int cube(int n) {return n*n*n;}
        void setytox2() {y = cube(x);}
        void setx(int ax) {x = ax;}
        int gety() {return y;}
        int geto(int n) {
            if (mpOutside==NULL) {return -2;} 
            else {return mpOutside->GetValue(n);}
        }
    private:

    };

}

#endif // __tcPythonInterface_h__

