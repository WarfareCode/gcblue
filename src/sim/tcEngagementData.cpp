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
#include "tcEngagementData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

tcEngagementData::tcEngagementData()
{
    mnCount = 0;
}

void tcEngagementData::Update(long* aaTracks, float* afRanges, unsigned anCount)
{
    float fMaxRange; // range and index of largest range in current engagement list
    unsigned nMaxIdx;
    bool bInList;
    bool abUpdated[MAX_ENGAGEMENTS];

    for(unsigned k=0;k<MAX_ENGAGEMENTS;k++)
    {
        abUpdated[k] = false;
    }

    for(unsigned i=0;i<anCount;i++)
    {
        bInList = false;
        fMaxRange = maTrackInfo[0].mfRange_km;
        nMaxIdx = 0;
        for(unsigned k=0;(k<mnCount)&&(!bInList);k++)
        {
            if (maTrackInfo[k].mnID==aaTracks[i])
            {
                bInList = true;
                abUpdated[k] = true;
            }
            else if (maTrackInfo[k].mfRange_km > fMaxRange) {
                fMaxRange = maTrackInfo[k].mfRange_km;
                nMaxIdx = k;
            }
        }
        if (!bInList) {
            if (mnCount<MAX_ENGAGEMENTS) {
                maTrackInfo[mnCount].mnID = aaTracks[i];
                maTrackInfo[mnCount].mfRange_km = afRanges[i];
                abUpdated[mnCount] = true;
                maTrackInfo[mnCount++].mbEngaged = false;
            }
            else if (afRanges[i] < fMaxRange) {  // add if closer than element already in list
                maTrackInfo[nMaxIdx].mnID = aaTracks[i];
                maTrackInfo[nMaxIdx].mfRange_km = afRanges[i];
                maTrackInfo[nMaxIdx].mbEngaged = false;
                abUpdated[nMaxIdx] = true;
            }
        }
    }

    unsigned int k=0;
    
    while(k<mnCount)
    {
        if (!abUpdated[k])
        { // remove if not updated
            maTrackInfo[k] = maTrackInfo[mnCount-1];
            mnCount--;
        }
        else
        {
            k++;
        }
    }
}