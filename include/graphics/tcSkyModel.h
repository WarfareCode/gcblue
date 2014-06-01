/**  
**  @file tcSkyModel.h
** 
**  Graphical model of sky based on
**  Preetham, Shirley, Smits, "A Practical Analytic Model for Daylight," published on 
**  University of Utah web site, http://www.cs.utah.edu/vissim/papers/sunsky/
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

#ifndef _TCSKYMODEL_H_
#define _TCSKYMODEL_H_

#if _MSC_VER > 1000
#pragma once
#endif 

#include <string>
#include "tv_types.h"

class tcDateTime;


/**
* Singleton class to model physics of 3D sky
*/
class tcSkyModel
{
public:
    
    static tcSkyModel* Get(); ///< singleton accessor

    Vec3 GetSkyColor(float el_rad, float az_rad) const;
    Vec3 GetZenithColor() const;
    void GetSunPosition(float& elevation_rad, float& azimuth_rad, const tcDateTime& t, float lat_rad, float lon_rad);
    void SetSunParameters(float el_rad, float az_rad, float T_);

private:
    float sun_el_rad; ///< 0 at horizon
    float sun_az_rad;
    float T;
    float pY[5];
    float px[5];
    float py[5];
    float Yz; ///< zenith luminance
    float xz; ///< zenith chromaticity
    float yz; ///< zenith chromaticity
    float inv_f_denom_Y;
    float inv_f_denom_x;
    float inv_f_denom_y;
    Vec3 k_sun; ///< direction vector for sun position

	tcSkyModel();
    virtual ~tcSkyModel();

    void CalcPerezCoefficients();
    void CalcZenithColors();
    Vec3 CIEtoRGB(float Y, float x, float y) const;

    float Perez(float theta, float gamma, const float* p) const;



};

#endif


