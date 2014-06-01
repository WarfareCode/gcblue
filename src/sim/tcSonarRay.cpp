/**
**  @file tcSonarRay.cpp
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

#include "tcSonarRay.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif



/**
* @return depth of ray at range_m or -999.9f if beyond last point
*/
float tcSonarRay::CalculateDepth(float range_m, float& reflectionLossFactor) const
{
    const float beyondRay = -999.9f;

    reflectionLossFactor = 1e-10f;

    if (data.size() == 0)
    {
        wxASSERT(false);
        return beyondRay;
    }

    if (range_m >= data.back().xmax) return beyondRay;

    for (size_t k=0; k<data.size(); k++)
    {
        if (range_m < data[k].xmax)
        {
            reflectionLossFactor = (k > 0) ? data[k-1].reflectionLossFactor : 1.0f;

            float dx = range_m - data[k].xc;
            float yterm = sqrtf(data[k].R2 - dx*dx);

            return (data[k].R < 0) ? -yterm + data[k].yc : yterm + data[k].yc;
        }
    }

    wxASSERT(false); // error, not found in ray and not beyond ray
    return beyondRay;
}


/**
*
*/
tcSonarRay::tcSonarRay()
{
}


/**
*
*/
tcSonarRay::~tcSonarRay() 
{
}