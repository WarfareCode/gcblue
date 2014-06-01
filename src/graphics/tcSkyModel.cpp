/**  
**  @file tcSkyModel.cpp
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
#endif

#include "tcSkyModel.h"
#include "math_constants.h"
#include "tcDateTime.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif 

tcSkyModel* tcSkyModel::Get()
{
    static tcSkyModel instance;
    return &instance;
}


void tcSkyModel::CalcPerezCoefficients()
{
    pY[0] = 0.1787f*T - 1.463f;    
    pY[1] = -0.3554f*T + 0.4275f;
    pY[2] = -0.0227f*T + 5.3251f;
    pY[3] = 0.1206f*T - 2.5771f;
    pY[4] = -0.0670f*T + 0.3703f;

    px[0] = -0.0193f*T - 0.2592f;
    px[1] = -0.0665f*T + 0.0008f;
    px[2] = -0.0004f*T + 0.2125f;
    px[3] = -0.0641f*T - 0.8989f;
    px[4] = -0.0033f*T + 0.0452f;

    py[0] = -0.0167f*T - 0.2608f;
    py[1] = -0.0950f*T + 0.0092f;
    py[2] = -0.0079f*T + 0.2102f;
    py[3] = -0.0441f*T - 1.6537f;
    py[4] = -0.0109f*T + 0.0529f;

}

void tcSkyModel::CalcZenithColors()
{
    float theta_sun_rad;
    float darkness_factor = 1.0f;

    if (sun_el_rad >= 0)
    {
        theta_sun_rad = C_PIOVER2 - sun_el_rad;
    }
    else if (sun_el_rad >= - 0.1f)
    {
        theta_sun_rad = C_PIOVER2;
        darkness_factor = 10.0f * (sun_el_rad + 0.1f);
    }
    else
    {
        theta_sun_rad = C_PIOVER2;
        darkness_factor = 0;
    }

    float chi = (0.44444444f - 0.008333333f*T) * (C_PI - 2.0f*theta_sun_rad);
    
    Yz = (4.0453f*T - 4.9710f)*tanf(chi) - 0.2155f*T + 2.4192f;

    float theta_sun_rad2 = theta_sun_rad * theta_sun_rad;
    float theta_sun_rad3 = theta_sun_rad2 * theta_sun_rad;
    float T2 = T*T;

    xz = T2*(0.00166f*theta_sun_rad3 - 0.00375f*theta_sun_rad2 + 0.00209f * theta_sun_rad) +
         T*(-0.02903f*theta_sun_rad3 + 0.06377f*theta_sun_rad2 - 0.03202f*theta_sun_rad + 0.00394f) +
         0.11693f*theta_sun_rad3 - 0.21196f*theta_sun_rad2 + 0.06052f*theta_sun_rad + 0.25886f;

    yz = T2*(0.00275f*theta_sun_rad3- 0.00610f*theta_sun_rad2 + 0.00317f * theta_sun_rad) +
         T*(-0.04214f*theta_sun_rad3 + 0.08970f*theta_sun_rad2 - 0.04153f*theta_sun_rad + 0.00516f) +
         0.15346f*theta_sun_rad3 - 0.26756f*theta_sun_rad2 + 0.06670f*theta_sun_rad + 0.26688f;

    Yz *= darkness_factor;
}

/**
* http://ozviz.wasp.uwa.edu.au/~pbourke/texture_colour/convert/
* Rogers, David F., "Procedural Elements for Computer Graphics," McGraw-Hill, New York, 1985, p 390-398.
*/
Vec3 tcSkyModel::CIEtoRGB(float Y, float x, float y) const
{
    float z = 1.0f - x - y;

    float r = 2.739f*x - 1.145f*y - 0.424f*z;
    float g = -1.119f*x + 2.029f*y + 0.033f*z;
    float b = 0.138f*x - 0.333f*y + 1.105f*z;

    Y *= 0.1f;

    r *= Y;
    g *= Y;
    b *= Y;

    if (r < 0.08f) r = 0.08f;
    else if (r > 1) r = 1;

    if (g < 0.08f) g = 0.08f;
    else if (g > 1) g = 1;

    if (b < 0.1f) b = 0.1f;
    else if (b > 1) b = 1;

    Vec3 result(r, g, b);

    return result;
}

Vec3 tcSkyModel::GetSkyColor(float el_rad, float az_rad) const
{
    Vec3 result;

    if (el_rad < 0) el_rad = 0;
    
    float cos_gamma = cosf(el_rad)*sinf(az_rad) * k_sun.x +
                      cosf(el_rad)*cosf(az_rad) * k_sun.y + 
                      sinf(el_rad)* k_sun.z;

    cos_gamma = std::min(cos_gamma, 1.0f);
    cos_gamma = std::max(cos_gamma, -1.0f);

    float gamma = acosf(cos_gamma);
    float theta_rad = C_PIOVER2 - el_rad;

    float f_num_Y = Perez(theta_rad, gamma, pY);
    float f_num_x = Perez(theta_rad, gamma, px);
    float f_num_y = Perez(theta_rad, gamma, py);

    float Y = Yz * f_num_Y * inv_f_denom_Y;
    float x = xz * f_num_x * inv_f_denom_x;
    float y = yz * f_num_y * inv_f_denom_y;

//    float norm = sqrtf(k_sun.x*k_sun.x + k_sun.y*k_sun.y + k_sun.z*k_sun.z);


    return CIEtoRGB(Y, x, y);
}

Vec3 tcSkyModel::GetZenithColor() const
{
    return CIEtoRGB(Yz, xz, yz);

}

float tcSkyModel::Perez(float theta, float gamma, const float* p) const
{
    float cos_gamma = cosf(gamma);

    return (1.0f + p[0]*expf(p[1] / cosf(theta))) *
        (1.0f + p[2]*expf(p[3]*gamma) + p[4]*cos_gamma*cos_gamma);
}

/**
* @param elevation_rad set to elevation of sun, 0 is horizon, pi/2 zenith, negative below horizon
* @param azimuth_rad set to azimuth relative to north
* @param dt date-time object
* @param lat_rad latitude of observing position
* @param lon_rad longitude of observing position
*/
void tcSkyModel::GetSunPosition(float& elevation_rad, float& azimuth_rad, const tcDateTime& t, float lat_rad, float lon_rad)
{
    const float a1 = 2.0f * C_TWOPI / 373.0f;
    const float a2 = C_TWOPI / 355.0f;
    const float a3 = 12.0f / C_PI;
    const float a4 = C_TWOPI / 368.0f;
    const float a5 = C_PI / 12.0f;

    float J = float(t.GetDayOfYear()); // day of year 1-366
    float t_hours = float(t.GetHoursUTC());

    if (lon_rad < -C_PI) lon_rad += C_TWOPI;
    else if (lon_rad >= C_PI) lon_rad -= C_TWOPI;

    float t_solar = t_hours + 0.170f * sinf(a1*(J - 80.0f)) -
        0.129f * sinf(a2*(J - 8.0f)) + (a3 * lon_rad);
    float t_rad = a5 * t_solar;

    float dec_rad = 0.4093f * sinf(a4*(J - 81.0f));

    float sin_lat = sinf(lat_rad);
    float cos_lat = cosf(lat_rad);
    float sin_dec = sinf(dec_rad);
    float cos_dec = cosf(dec_rad);
    float sin_t = sinf(t_rad);
    float cos_t = cosf(t_rad);

    elevation_rad = asinf(sin_lat*sin_dec - cos_lat*cos_dec*cos_t);

    azimuth_rad = C_PI + atanf( (-cos_dec*sin_t) / (cos_lat*sin_dec - sin_lat*cos_dec*cos_t) );
    if (azimuth_rad >= C_PI) azimuth_rad -= C_TWOPI;

}


void tcSkyModel::SetSunParameters(float el_rad, float az_rad, float T_)
{
    sun_el_rad = el_rad;
    sun_az_rad = az_rad;
    T = T_;

    CalcPerezCoefficients();
    CalcZenithColors();

    float theta_sun_rad = C_PIOVER2 - sun_el_rad;

    inv_f_denom_Y = 1.0f / Perez(0, theta_sun_rad, pY);
    inv_f_denom_x = 1.0f / Perez(0, theta_sun_rad, px);
    inv_f_denom_y = 1.0f / Perez(0, theta_sun_rad, py);

    k_sun.z = sinf(sun_el_rad);
    k_sun.x = cosf(sun_el_rad)*sinf(sun_az_rad);
    k_sun.y = cosf(sun_el_rad)*cosf(sun_az_rad);
}


tcSkyModel::tcSkyModel()
{
    SetSunParameters(0.2f, C_PIOVER2, 2);
}

tcSkyModel::~tcSkyModel()
{
}