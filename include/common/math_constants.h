/**
** @file math_constants.h
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

#ifndef _MATHCONSTANTS_H_
#define _MATHCONSTANTS_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define C_TWOPI 6.2831853f
#define C_TWOPIM 6.283184f // slightly less
#define C_PI 3.14159265f
#define C_PIM 3.141591f // slightly less
#define C_FOURPI 12.56637f
#define C_PIOVER2 1.57079633f
#define C_PIOVER2M 1.570794f // slightly less
#define C_PIOVER180 0.0174532925f
#define C_DEGTORAD 0.0174532925f
#define C_180OVERPI 57.295779513f
#define C_RADTODEG 57.295779513f
#define C_NMITOM 1852.0f
#define C_NMITOKM 1.852f
#define C_NMITOMI 1.150779f
#define C_MITONMI 0.86897658f
#define C_KMTONMI 0.53995680f
#define C_KMTODEG 0.0089992800f
#define C_KMTOKYD 1.09361221f
#define C_MTODEG 0.0000089992800f
#define C_DEGTOKM 111.12f
#define C_DEGTOM 111120.0f
#define C_KTSTOMPS 0.51444444f
#define C_KTSTOKMPS 0.51444444e-3f
#define C_MPSTOKTS 1.94384450f
#define C_MPSTODEGPS 8.999280e-006f
#define C_MPSTORADPS 1.5706707e-7f
#define C_G 9.80665f  ///< gravitational acceleration in m/s^2
#define C_G2 96.170384f  ///< g^2
#define C_GINV 0.1019716f ///< 1/G
#define C_GM 3.986e14f ///< earth grav constant in m^3/s^2
#define C_GMINV 2.508781e-15f ///< 1/grav constant
#define C_KGTOLBS 2.2046226f
#define C_KTSTODEGPS 4.6296296296296e-6f
#define C_KTSTORADPS 8.0802280e-8f
#define C_REARTHKM 6378.140f
#define C_REARTHM 6378140.0f 
#define C_RADTOKM 6378.140f
#define C_RADTOM 6378140.0f
#define C_KMTORAD 1.5678552e-4f
#define C_MTORAD 1.5678552e-7f
#define C_MTOFT 3.2808399f
#define C_MTOMI 0.000621371f
#define C_FTTOM 0.30480f
#define C_RADARHOR 3.92482f ///< radar horizon in km = constant*sqrt(h in meters)
#define C_VISUALHOR 2.78f ///< visible horizon in km = constant*sqrt(h in meters)
#define C_RADTOHRS 3.819719f
#define C_U2GSIG 0.5773503f ///< 2/sqrt(12) factor to convert from uniform +/- error to gaussian stdev
#define C_U2GVAR 0.3333333f ///< 1/3 = square of C_U2GSIG
#define C_CLIGHT_MPS 299792458.0f

class UnitConversions
{
public:
    static double toRadians(double deg);
    static float toRadians(float deg);
    static double toDegrees(double rad);
    static float toDegrees(float rad);
};


#endif
