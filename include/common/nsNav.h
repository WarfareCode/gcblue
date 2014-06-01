/**
**  @file nsNav.h
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

#ifndef _NSNAV_H_
#define _NSNAV_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "stdwx.h"
#include "math_constants.h"
#include "simmath.h"

class nsNav 
{
public:

	static float GCDistance_rad(const GeoPoint& a, const GeoPoint& b);
	static float GCDistanceApprox_rad(const GeoPoint& a, const GeoPoint& b);
	static float GCDistanceApprox_rad(float afLatA_rad, float afLonA_rad, float afLatB_rad, float afLonB_rad);
	static float GCDistanceApprox_rad(float afLatA_rad, float afLonA_rad, float afLatB_rad, float afLonB_rad,
		float afAltA_m, float afAltB_m);

	static float GCHeading_rad(const GeoPoint& a, const GeoPoint& b, float *apfDistance_rad = 0);
	static float GCHeadingApprox_rad(const GeoPoint& a, const GeoPoint& b);
	static float GCHeadingApprox_rad(float afLatA_rad, float afLonA_rad, float afLatB_rad, float afLonB_rad);

	static void Offset(const GeoPoint& a, GeoPoint& b, float afHeading_rad, float afRange_rad);

	static void OffsetApprox(const GeoPoint& a, GeoPoint& b, float afHeading_rad, float afRange_rad);
    static void OffsetApprox(const tcPoint& a, tcPoint& b, float afHeading_rad, float afRange_rad);
	static void OffsetApprox(float afLatA_rad, float afLonA_rad, 
		            float& afLatB_rad, float& afLonB_rad, float afHeading_rad, float afRange_rad);

    static void OffsetApprox(double afLatA_rad, double afLonA_rad, 
                    double& afLatB_rad, double& afLonB_rad, float afHeading_rad, double afRange_rad);

	static float GetLatAlongGCPath(GeoPoint a, GeoPoint b, float afLon_rad);

    static float ElevationAngle(float altitudeA_m, float altitudeB_m, float range_m);
	static void Test();
};


#endif
