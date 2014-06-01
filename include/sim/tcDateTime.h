/**
**  @file tcDateTime.h
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

#if _MSC_VER > 1000
#pragma once
#endif

#ifndef _TCDATETIME_H_
#define _TCDATETIME_H_

class tcStream;

class tcDateTime 
{
public:
    void AdjustTimeSeconds(double dt_s);
    void AdjustTimeHours(double dt_hr);

    double GetJulianDate() const; ///< continuous count of days from 1 Jan 4713 BC
    int GetDayOfYear() const;
    double GetHoursUTC() const;

    int GetYear() const;
    int GetMonth() const;
    const char* GetMonthString() const;
    int GetDay() const;
    int GetHour() const;
    int GetMinute() const;
    int GetSecond() const;
    const char* asString() const;
    const char* asStringTOD() const;
    float GetFractionalYear() const;

    tcStream& operator<<(tcStream& stream);
    tcStream& operator>>(tcStream& stream);

    bool operator<(const tcDateTime& rhs) const;
    bool operator>(const tcDateTime& rhs) const;

    tcDateTime();
    tcDateTime(int year_, int month_, int day_, double hour_utc);
    tcDateTime(int year_, int month_, int day_, int hour_, int min_, int sec_);
    ~tcDateTime();

private:
    static const int yearOrdinal[13]; ///< index 1 to 12 with months

    int year;
    int month; ///< 1 <= month <= 12
    int day; ///< 1 <= day <= 31
    double hour; ///< 0 <= hour < 24

    int LastDayInMonth();
    bool IsLeapYear(int y) const;
};

#endif