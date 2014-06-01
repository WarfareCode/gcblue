/*  
**  tcPythonInterface.cpp
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
#endif // WX_PRECOMP

#include "tcPythonInterface.h"

#include <boost/python.hpp>
using namespace boost::python;
using namespace scriptinterface;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif 

void tcPythonInterface::Test() 
{
  PyRun_SimpleString("from time import time,ctime\n"
                     "print 'Today is',ctime(time())\n");
}

void tcPythonInterface::Test2() 
{
   handle<> main_module(borrowed( PyImport_AddModule("__main__") ));
   handle<> main_namespace(borrowed( PyModule_GetDict(main_module.get()) ));
   handle<>( PyRun_String("hello = file('hello.txt', 'w')\n"
      "hello.write('Hello world!')\n"
      "hello.close()", Py_file_input,
      main_namespace.get(), main_namespace.get()) );
   
}


void tcPythonInterface::Test3() 
{
   std::string s;
   
   s = "import test_script\n";

   handle<> main_module(borrowed( PyImport_AddModule("__main__") ));
   handle<> main_namespace(borrowed( PyModule_GetDict(main_module.get()) ));

   try {

      handle<>( PyRun_String("import test_script\ntest_script.test()",
         Py_file_input,
         main_namespace.get(), main_namespace.get()));

   }
   catch(error_already_set) {
      // handle the exception in some way
      fprintf(stderr,"Exception occured\n");
      PyErr_Print();
   }
}


float mysin(float x) {return sinf(x);}

tcOutside* tcTest::mpOutside = NULL;

void tcPythonInterface::Test4() 
{
   tcOutside outside;
   outside.maValues[0] = 10;
   outside.maValues[1] = 11;
   outside.maValues[2] = 12;

   tcTest::mpOutside = &outside;

   PyDict_SetItemString(main_namespace.ptr(), "Y", PyInt_FromLong(2));      /* dict['Y']=2 */
   
   object class_a = class_<tcTest>("test")
      .def_readwrite("x", &tcTest::x)
      .def("setx",&tcTest::setx)
      .def("setytox2",&tcTest::setytox2)
      .def("gety",&tcTest::gety)
      .def("geto",&tcTest::geto);
      ; // creates a class object
   
   object instance_a = class_a();
   instance_a.attr("x") = 77;

   PyDict_SetItemString(main_namespace.ptr(), "A", instance_a.ptr());     

   try {   

      handle<>( PyRun_String("outfile = file('test4.txt', 'w')\n"
         "outfile.write('Started!')\n"
         //"Y = 5\n"
         "outfile.write(str(Y))\n"
         "outfile.write('\\n')\n"
         "outfile.write('A.x is ' + str(A.x)+'\\n')\n"
         "outfile.write('A.geto(1) is '+str(A.geto(1))+'\\n')\n"
         "outfile.close()\n"
         , Py_file_input, main_namespace.ptr(), main_namespace.ptr()) );

      handle<>( PyRun_String(
         "A.setx(99)\n"
         "A.setytox2()\n"
         "A.setx(A.geto(1))\n"
         , Py_file_input, main_namespace.ptr(), main_namespace.ptr()) );
   }
   catch(error_already_set) {
      // handle the exception in some way
      fprintf(stderr,"Exception occured\n");
      PyErr_Print();
   }
   
   int x = extract<int>(instance_a.attr("x"));
   fprintf(stdout,"A.x is now %d\n",x);
}




char* tcPythonInterface::ReadFile(const char* filename) 
{
 char* buffer = 0;
 FILE* file = fopen(filename, "r");
 fseek(file, 0, SEEK_END);
 size_t size = ftell(file);
 if (size)
 {
  buffer = (char*)malloc(size + 1);
  fseek(file, 0, SEEK_SET);
  size = fread(buffer, sizeof(char), size, file);
  buffer[size] = 0;
 }
 fclose(file);
 return buffer;
}




tcPythonInterface::tcPythonInterface()
{
   Py_Initialize(); 



   main_module = object(handle<>(borrowed(PyImport_AddModule("__main__"))));

   main_namespace = main_module.attr("__dict__");

   // untested code:
   char *path, *newpath;
   path=Py_GetPath();
   newpath=new char[strlen(path)+256];
   //strcpy(newpath, path);
   strcpy(newpath, ";.\\scripts;.\\scenarios");  // ":." for unix, or ";." for windows
   PySys_SetPath(newpath);
   delete(newpath);

   /*** redirect standard error ***/
   /*
   PyRun_SimpleString(
      "import StringIO\n"
      "import sys\n"
      "myout = StringIO.StringIO()\n"
      "myerr = StringIO.StringIO()\n"
      "sys.stdout = myout\n"
      "sys.stderr = myerr\n"
      );
   */

   /* create fresh dictionary */
   //mpDictionary = new dict(handle<>(borrowed(PyDict_New())));
   PyDict_SetItemString(main_namespace.ptr(), "__builtins__", PyEval_GetBuiltins());

}

tcPythonInterface::~tcPythonInterface() 
{
	/*** print standard error to file ***/
	/*
	PyRun_SimpleString(
	"outfile = file('log\\pyout.txt', 'w')\n"
	"errfile = file('log\\pyerr.txt', 'w')\n"
	"outfile.write(myout.getvalue())\n"
	"errfile.write(myerr.getvalue())\n"
	"outfile.close()\n"
	"errfile.close()\n"
	);
	*/

	Py_Finalize();
}
