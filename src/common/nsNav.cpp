/**
**  @file nsNav.cpp
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

#ifndef WX_PRECOMP
#include "wx/wx.h" 
#endif

#include "nsNav.h"
#include "simmath.h"
#include <stdio.h>
#include <cmath>
#include "math_constants.h"

using std::max;
using std::min;

/**
* @return elevation angle in radians from A to B relative to local tangent at A
*/
float nsNav::ElevationAngle(float altitudeA_m, float altitudeB_m, float range_m)
{
    float ra_m = C_REARTHM + altitudeA_m;
    float rb_m = C_REARTHM + altitudeB_m;
    float el_rad = acosf((0.5f/(ra_m*range_m))*(ra_m*ra_m + range_m*range_m - rb_m*rb_m)) - C_PIOVER2;
    return el_rad;
}

// great circle distance in radians between points a and b
// both points are assumed to be at sea level
#define GCDISTANCE_APPROXDELTA 2.0f*C_PIOVER180

float nsNav::GCDistance_rad(const GeoPoint& a, const GeoPoint& b) 
{
   
   float fDeltaLat = fabsf(a.mfLat_rad - b.mfLat_rad);
   float fDeltaLon = fabsf(a.mfLon_rad - b.mfLon_rad);
   bool bUseApprox = (fDeltaLat <= GCDISTANCE_APPROXDELTA)&&
      (fDeltaLon <= GCDISTANCE_APPROXDELTA);

   

   if (bUseApprox) 
   {
	  float cos_term = cosf(0.5f * (a.mfLat_rad + b.mfLat_rad));
	  float adjustedLon = cos_term * fDeltaLon;

      return sqrtf(fDeltaLat*fDeltaLat + adjustedLon*adjustedLon); 
   }
   else 
   {
      return acosf(sinf(a.mfLat_rad)*sinf(b.mfLat_rad) +
         cosf(a.mfLat_rad)*cosf(b.mfLat_rad)*cosf(fDeltaLon)); 
   }
}

/**
* version that always uses approximation
*/
float nsNav::GCDistanceApprox_rad(const GeoPoint& a, const GeoPoint& b) 
{
   float fDeltaLat = a.mfLat_rad - b.mfLat_rad;
   float fDeltaLon = a.mfLon_rad - b.mfLon_rad;
   if (fDeltaLon >= C_PI) {fDeltaLon -= C_TWOPI;}
   else if (fDeltaLon < -C_PI) {fDeltaLon += C_TWOPI;}

   float cos_term = cosf(0.5f * (a.mfLat_rad + b.mfLat_rad));
   float adjustedLon = cos_term * fDeltaLon;

   return sqrtf(fDeltaLat*fDeltaLat + adjustedLon*adjustedLon); 
}

float nsNav::GCDistanceApprox_rad(float afLatA_rad, float afLonA_rad, 
								  float afLatB_rad, float afLonB_rad) 
{
   float fDeltaLat = afLatA_rad - afLatB_rad;
   float fDeltaLon = afLonA_rad - afLonB_rad;
   if (fDeltaLon > C_PI) {fDeltaLon -= C_TWOPI;}
   else if (fDeltaLon < -C_PI) {fDeltaLon += C_TWOPI;}

   float cos_term = cosf(0.5f * (afLatA_rad + afLatB_rad));
   float adjustedLon = cos_term * fDeltaLon;

   return sqrtf(fDeltaLat*fDeltaLat + adjustedLon*adjustedLon); 
}


float nsNav::GCDistanceApprox_rad(float afLatA_rad, float afLonA_rad, 
								  float afLatB_rad, float afLonB_rad,
                                  float afAltA_m, float afAltB_m) 
{
   float fDeltaLat = afLatA_rad - afLatB_rad;
   float fDeltaLon = afLonA_rad - afLonB_rad;
   float fDeltaAlt = C_MTORAD*(afAltA_m - afAltB_m);
   if (fDeltaLon > C_PI) {fDeltaLon -= C_TWOPI;}
   else if (fDeltaLon < -C_PI) {fDeltaLon += C_TWOPI;}

   float cos_term = cosf(0.5f * (afLatA_rad + afLatB_rad));
   float adjustedLon = cos_term * fDeltaLon;

   return sqrtf(fDeltaLat*fDeltaLat + adjustedLon*adjustedLon + fDeltaAlt*fDeltaAlt); 
}

/**
* great circle heading from point a to point b
* stores distance in *apfDistance_rad if not NULL
*/
float nsNav::GCHeading_rad(const GeoPoint& a, const GeoPoint& b, float *apfDistance_rad) 
{
   float fDistanceRad = GCDistance_rad(a,b);

   if (apfDistance_rad != NULL) {*apfDistance_rad = fDistanceRad;}

   float fTerm = (sinf(b.mfLat_rad)-cosf(fDistanceRad)*sinf(a.mfLat_rad))/
      (sinf(fDistanceRad)*cosf(a.mfLat_rad));

   if (sinf(a.mfLon_rad-b.mfLon_rad) < 0) 
   {
      return acosf( max( min( fTerm,1.0f ),-1.0f ) );
   }
   else 
   {
      return C_TWOPI - acosf( max( min(fTerm,1.0f), -1.0f) );
   }
}

/**
* approximate heading from point a to point b
* approximation assuming short distances
* a few tenths of a deg of error for <= 2 deg lat/lon difference at 
* high (80+ deg) latitudes, less error near equator
*/
float nsNav::GCHeadingApprox_rad(const GeoPoint& a, const GeoPoint& b) 
{
   float fCosLatAvg_rad = cosf(0.5f*(a.mfLat_rad+b.mfLat_rad));
   float fDeltaLon = b.mfLon_rad - a.mfLon_rad;
   if (fDeltaLon > C_PI) {fDeltaLon -= C_TWOPI;}
   else if (fDeltaLon < -C_PI) {fDeltaLon += C_TWOPI;}

   return atan2f(fCosLatAvg_rad*fDeltaLon, b.mfLat_rad-a.mfLat_rad);
}

float nsNav::GCHeadingApprox_rad(float afLatA_rad, float afLonA_rad, 
								 float afLatB_rad, float afLonB_rad) 
{
   float fCosLatAvg_rad = cosf(0.5f*(afLatA_rad+afLatB_rad));
   float fDeltaLon = afLonB_rad - afLonA_rad;
   if (fDeltaLon > C_PI) {fDeltaLon -= C_TWOPI;}
   else if (fDeltaLon < -C_PI) {fDeltaLon += C_TWOPI;}

   return atan2f(fCosLatAvg_rad*fDeltaLon, afLatB_rad-afLatA_rad);
}

/**
* sets point b at heading afHeading_rad and range of afRange_rad from point a
* has accuracy issues (maybe this heading is only the initial heading or similar?)
*/
void nsNav::Offset(const GeoPoint& a, GeoPoint& b, 
				   float afHeading_rad, float afRange_rad) 
{
   float fTerm = sinf(a.mfLat_rad)*cosf(afRange_rad) +
      cosf(a.mfLat_rad)*sinf(afRange_rad)*cosf(afHeading_rad);

   if (fTerm > 1) {fTerm = 1;}
   else if (fTerm < -1) {fTerm = -1;}

   b.mfLat_rad = asinf(fTerm);
   fTerm = sinf(afHeading_rad)*sinf(afRange_rad)/cosf(a.mfLat_rad);

   if (fTerm > 1) {fTerm = 1;}
   else if (fTerm < -1) {fTerm = -1;}

   b.mfLon_rad = a.mfLon_rad + asinf(fTerm);
}

/**
* sets point b at heading afHeading_rad and range of afRange_rad from point a
*/
void nsNav::OffsetApprox(const GeoPoint& a, GeoPoint& b, 
						 float afHeading_rad, float afRange_rad) 
{
   b.mfLat_rad = a.mfLat_rad + cosf(afHeading_rad)*afRange_rad;
   b.mfLon_rad = a.mfLon_rad + sinf(afHeading_rad)*afRange_rad/cosf(a.mfLat_rad);
}


/**
* sets point b at heading afHeading_rad and range of afRange_rad from point a
*/
void nsNav::OffsetApprox(const tcPoint& a, tcPoint& b, 
						 float afHeading_rad, float afRange_rad) 
{
   b.y = a.y + cosf(afHeading_rad)*afRange_rad;
   b.x = a.x + sinf(afHeading_rad)*afRange_rad/cosf(a.y);
}


/**
* Calculates offset point from (afLatA_rad,afLonA_rad).
* @param afLatA_rad starting latitude in radians.
* @param afLonA_rad starting longitude in radians.
* @param afLatB_rad offset latitude in radians.
* @param afLonB_rad offset longitude in radians.
* @param afHeading_rad offset heading in radians.
* @param afRange_rad offset range in radians at equator.
*/
void nsNav::OffsetApprox(float afLatA_rad, float afLonA_rad, 
    float& afLatB_rad, float& afLonB_rad, float afHeading_rad, float afRange_rad) 
{
   afLatB_rad = afLatA_rad + cosf(afHeading_rad)*afRange_rad;
   afLonB_rad = afLonA_rad + sinf(afHeading_rad)*afRange_rad/cosf(afLatA_rad);
}

/**
* Calculates offset point from (afLatA_rad,afLonA_rad).
* @param afLatA_rad starting latitude in radians.
* @param afLonA_rad starting longitude in radians.
* @param afLatB_rad offset latitude in radians.
* @param afLonB_rad offset longitude in radians.
* @param afHeading_rad offset heading in radians.
* @param afRange_rad offset range in radians at equator.
*/
void nsNav::OffsetApprox(double afLatA_rad, double afLonA_rad, 
    double& afLatB_rad, double& afLonB_rad, float afHeading_rad, double afRange_rad) 
{
   afLatB_rad = afLatA_rad + cosf(afHeading_rad)*afRange_rad;
   afLonB_rad = afLonA_rad + sinf(afHeading_rad)*afRange_rad/cosf(afLatA_rad);
}

/**
* @return latitude of point at afLon_rad along GC path between a and b
*/
float nsNav::GetLatAlongGCPath(GeoPoint a, GeoPoint b, float afLon_rad) 
{
   float fNum, fDen;

   if (b.mfLon_rad == a.mfLon_rad) 
   {
      b.mfLon_rad = a.mfLon_rad + 0.001f;
   }

   fNum = sinf(a.mfLat_rad)*cosf(b.mfLat_rad)*sinf(afLon_rad-b.mfLon_rad) -
      sinf(b.mfLat_rad)*cosf(a.mfLat_rad)*sinf(afLon_rad-a.mfLon_rad);

   fDen = cosf(a.mfLat_rad)*cosf(b.mfLat_rad)*sinf(a.mfLon_rad-b.mfLon_rad);

   return atanf(fNum/fDen);
}

/**
* prints test info to file
*/
void nsNav::Test() 
{
   FILE* testfile=NULL;
   int nTrials = 8;

   testfile = fopen("navtest.txt","wt");
   if (testfile==NULL) 
   {
      wxMessageBox("Failed to open nav test file");
      return;
   }
   for(int i=0; i<nTrials; i++) 
   {
      GeoPoint a,b;
      a.mfLat_rad = 0.9f*randfc(C_PI);
      a.mfLon_rad = 0.5f*randfc(C_TWOPI);//-C_PI;
      b.mfLat_rad = 0.9f*randfc(C_PI);
      b.mfLon_rad = 0.5f*randfc(C_TWOPI);//-C_PI;
      if (a.mfLon_rad < -C_PI) {a.mfLon_rad += C_TWOPI;}
      fprintf(testfile,"A (lat %3.2f, lon %3.2f), \tB (lat %3.2f, lon %3.2f) [deg]\n",
         a.mfLat_rad*C_180OVERPI,a.mfLon_rad*C_180OVERPI,
         b.mfLat_rad*C_180OVERPI,b.mfLon_rad*C_180OVERPI);
      // range, heading
      {
         GeoPoint b2;
         float fRange_rad = GCDistance_rad(a,b);
         float fHeading_Rad = GCHeading_rad(a,b);
         if (fHeading_Rad < 0) {fHeading_Rad += C_TWOPI;}
         fprintf(testfile,"   Range: %4.1f km  Heading (A to B): %3.1f deg\n",
            fRange_rad*C_RADTOKM, fHeading_Rad*C_180OVERPI);
         Offset(a,b2,fHeading_Rad,fRange_rad);
         fprintf(testfile,"   \t\t\tBcalc:(lat %3.2f, lon %3.2f)\n",
            b2.mfLat_rad*C_180OVERPI,b2.mfLon_rad*C_180OVERPI);
      }
      // approximate range, heading
      {
         GeoPoint b2;
         float fRange_rad = GCDistanceApprox_rad(a,b);
         float fHeading_Rad = GCHeadingApprox_rad(a,b);
         if (fHeading_Rad < 0) {fHeading_Rad += C_TWOPI;}
         fprintf(testfile,"   Range: %4.1f km  Heading (A to B): %3.1f deg\n",
            fRange_rad*C_RADTOKM, fHeading_Rad*C_180OVERPI);
         OffsetApprox(a,b2,fHeading_Rad,fRange_rad);
         fprintf(testfile,"   \t\t\tBcalc:(lat %3.2f, lon %3.2f)\n",
            b2.mfLat_rad*C_180OVERPI,b2.mfLon_rad*C_180OVERPI);
      }
      fprintf(testfile,"\n");
      if (i==nTrials-1) {
         float fdLon = 0.1f*(b.mfLon_rad - a.mfLon_rad);
         float fLat;
         int nPoint = 1;
         for (float fLon = a.mfLon_rad + fdLon;nPoint<10;fLon+=fdLon) {
            fLat = GetLatAlongGCPath(a,b,fLon);
            fprintf(testfile,"Point %d  (lat %3.2f, lon %3.2f)\n",nPoint,
               fLat*C_180OVERPI,fLon*C_180OVERPI);
            nPoint++;
         }
      }
   }
   fclose(testfile);

}

