/**  
**  @file tcUnits.cpp
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

#include "tcUnits.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

tcUnits* tcUnits::Get()
{
    static tcUnits instance;

    return &instance;
}

float tcUnits::UserSpeedUnits(float speed_kts) const
{
    return speedConversion * speed_kts;
}

const char* tcUnits::GetSpeedUnitLabel() const
{
    return speedUnitLabel.c_str();
}

const char* tcUnits::GetUserSpeedString(float speed_kts) const
{
    static wxString s;

    s.Printf(speedFormatString.c_str(), UserSpeedUnits(speed_kts));

    return s.c_str();
}

float tcUnits::UserSpeedToKts(float speed_user) const
{
    return invSpeedConversion * speed_user;
}


float tcUnits::UserAltitudeUnits(float alt_m) const
{
    return (alt_m < highAltitude_m) ? altitudeConversion * alt_m : altitudeConversionHigh * alt_m;
}

const char* tcUnits::GetAltitudeUnitLabel(float alt_m) const
{
    return (alt_m < highAltitude_m) ? altitudeUnitLabel.c_str() : altitudeUnitLabelHigh.c_str();
}

const char* tcUnits::GetUserAltitudeString(float alt_m) const
{
    static wxString s;

    if (alt_m < highAltitude_m)
    {
        s.Printf(altitudeFormatString.c_str(), UserAltitudeUnits(alt_m));
    }
    else
    {
        s.Printf(altitudeFormatStringHigh.c_str(), UserAltitudeUnits(alt_m));
    }

    return s.c_str();
}

float tcUnits::UserDistanceUnits(float dist_m) const
{
    return distanceConversion * dist_m;
}

const char* tcUnits::GetDistanceUnitLabel() const
{
    return distanceUnitLabel.c_str();
}

const char* tcUnits::GetUserDistanceString(float dist_m) const
{
    static wxString s;

    s.Printf(distanceFormatString.c_str(), UserDistanceUnits(dist_m));

    return s.c_str();
}

float tcUnits::UserMassUnits(float mass_kg) const
{
    return massConversion * mass_kg;
}

const char* tcUnits::GetMassUnitLabel() const
{
    return massUnitLabel.c_str();
}

const char* tcUnits::GetUserMassString(float mass_kg) const
{
    static wxString s;

    s.Printf(massFormatString.c_str(), UserMassUnits(mass_kg));

    return s.c_str();
}


void tcUnits::Update()
{
    //int speedUnits; ///< 0 - m/s, 1 - kts, 2 - km/h, 3 - mph
    //int altitudeUnits; ///< 0 - m, 1 - ft, 2 - yds
    //int distanceUnits; ///< 0 - km, 1 - nmi, 2 - kyd

    switch (options->speedUnits)
    {
        case 0: // m/s
            speedConversion = C_KTSTOMPS;
            invSpeedConversion = C_MPSTOKTS;
            speedUnitLabel = "m/s";
            speedFormatString = "%.0f m/s";
            break;
        case 1: // kts
            speedConversion = 1;
            invSpeedConversion = 1;
            speedUnitLabel = "kts";
            speedFormatString = "%.0f kts";
            break;
        case 2: // km/h
            speedConversion = C_NMITOKM;
            invSpeedConversion = C_KMTONMI;
            speedUnitLabel = "km/h";
            speedFormatString = "%.0f km/h";
            break;
        case 3: // mph
            speedConversion = C_NMITOMI;
            invSpeedConversion = C_MITONMI;
            speedUnitLabel = "mph";
            speedFormatString = "%.0f mph";
            break;
        default:
            speedConversion = 0;
            invSpeedConversion = 0;
            speedUnitLabel = "err";
            speedFormatString = "err";
            wxASSERT(false);
            break;
    }

    switch (options->altitudeUnits)
    {
        case 0: // m
            altitudeConversion = 1;
            altitudeUnitLabel = "m";
            altitudeFormatString = "%.0f m";

            altitudeConversionHigh = 0.001f;
            altitudeUnitLabelHigh = "km";
            altitudeFormatStringHigh = "%.1f km";
            break;
        case 1: // ft
            altitudeConversion = C_MTOFT;
            altitudeUnitLabel = "ft";
            altitudeFormatString = "%.0f ft";

            altitudeConversionHigh = C_MTOMI;
            altitudeUnitLabelHigh = "mi";
            altitudeFormatStringHigh = "%.1f mi";
            break;
        case 2: // yds
            altitudeConversion = 0.333333f * C_MTOFT;
            altitudeUnitLabel = "yds";
            altitudeFormatString = "%.0f yds";

            altitudeConversionHigh = C_MTOMI;
            altitudeUnitLabelHigh = "mi";
            altitudeFormatStringHigh = "%.1f mi";
            break;
        default:
            altitudeConversion = 0;
            altitudeUnitLabel = "err";
            altitudeFormatString = "err";
            break;
    }

    switch (options->distanceUnits)
    {
        case 0: // km
            distanceConversion = 0.001f;
            distanceUnitLabel = "km";
            distanceFormatString = "%.1f km";
            break;
        case 1: // nmi
            distanceConversion = 0.001f * C_KMTONMI;
            distanceUnitLabel = "nmi";
            distanceFormatString = "%.1f nmi";
            break;
        case 2: // kyd
            distanceConversion = 0.001f * C_KMTOKYD;
            distanceUnitLabel = "kyd";
            distanceFormatString = "%.1f kyd";
            break;
        default:
            distanceConversion = 0;
            distanceUnitLabel = "err";
            distanceFormatString = "err";
            break;
    }

    switch (options->massUnits)
    {
        case 0: // kg
            massConversion = 1.0f;
            massUnitLabel = "kg";
            massFormatString = "%.0f kg";
            break;
        case 1: // lbs
            massConversion = C_KGTOLBS;
            massUnitLabel = "lbs";
            massFormatString = "%.0f lbs";
            break;
        default:
            massConversion = 0;
            massUnitLabel = "err";
            massFormatString = "err";
            break;
    }

}




tcUnits::tcUnits()
: options(tcOptions::Get()),
  highAltitude_m(30e3)
{
    Update();

}

tcUnits::~tcUnits()
{
}

