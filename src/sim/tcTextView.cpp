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


#include "tcTextView.h"
#include <fstream>

using namespace std;

void tcTextView::LoadText(const char *azFile) {
   enum {MAX_LINE_LENGTH=256};
   char zBuff[MAX_LINE_LENGTH];
   fstream infile;
   int nLine = 0;

   infile.open(azFile,ios_base::in);

   infile.getline(zBuff,MAX_LINE_LENGTH);
   maText[nLine] = zBuff;
   maText[nLine++] += "\n";

   while ((infile.gcount() > 0)&&(nLine < MAX_LINES)) {
      infile.getline(zBuff,MAX_LINE_LENGTH);
      maText[nLine] = zBuff;
      maText[nLine++] += "\n";
   }
   mnLines = nLine;

   infile.close();
}

int tcTextView::Draw() {
   Graphics *pGraphics;
   float ftextx,ftexty;

   if (!GetGraphics(pGraphics)) {  
      throw "Failed to get Graphics in tcOOBView::Draw()\n";  
      return false;
   }      
   if (IsBackgroundLoaded()) {
      DrawBackground(pGraphics);
   }
   else {
      // erase
      mpBrush->SetColor(Color(255,0,0,0));
      pGraphics->FillRectangle(mpBrush,0,0,mnWidth,mnHeight);
   }

   /*** draw text ***/
   mpBrush->SetColor(Color(254,100,255,100));
   ftextx = 5.0f;
   ftexty = 5.0f;
   for(int n=0;n<mnLines;n++) {
      DrawText(pGraphics,mpFont,mpBrush,maText[n].c_str(),ftextx,ftexty);
      ftexty += 10.0f;
   }
    
   ReleaseGraphics(pGraphics);
   DrawBorder(); 
   return true;
}

tcTextView::tcTextView(void) {
   mnLines = 0;

   mpPen = new Pen(Color(0xFEFFFFFF),2);
   if (mpPen == NULL) {throw "tcTextView - mpPen creation failed\n";}

   FontFamily ff(L"Arial");
   mpFont = new Font(&ff,9,FontStyleBold,UnitPixel);
   if (mpFont == NULL) {throw "tcTextView - mpFont creation failed\n";}

   mpBrush = new SolidBrush(Color(0xFEFFFFFF)); // color is ARGB 
   if (mpBrush == NULL) {throw "tcTextView - mpBrush creation failed\n";}
}

tcTextView::~tcTextView(void) {
   if (mpPen != NULL) {delete mpPen;}
   if (mpFont != NULL) {delete mpFont;}
   if (mpBrush != NULL) {delete mpBrush;}
}
