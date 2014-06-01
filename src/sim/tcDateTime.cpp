/**
** @file tcDateTime.cpp
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

#ifdef WX_PRECOMP
#include "stdwx.h"
#else
#include "wx/wx.h" 
#endif

#include "tcDateTime.h"
#include "common/tcStream.h"
#include "wx/datetime.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


const int tcDateTime::yearOrdinal[13] = {0, 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};


/**
* @return true if time is earlier than rhs
*/
bool tcDateTime::operator<(const tcDateTime& rhs) const
{
    return (GetJulianDate() < rhs.GetJulianDate());
}

/**
* @return true if time is later than rhs
*/
bool tcDateTime::operator>(const tcDateTime& rhs) const
{
    return (GetJulianDate() > rhs.GetJulianDate());
}


/**
* Loads state from stream
*/
tcStream& tcDateTime::operator<<(tcStream& stream)
{
    stream >> year;
	stream >> month;
    stream >> day;
    stream >> hour;

    return stream;
}

/**
* Saves state to stream
*/
tcStream& tcDateTime::operator>>(tcStream& stream)
{
    stream << year;
	stream << month;
    stream << day;
    stream << hour;

    return stream;
}

void tcDateTime::AdjustTimeHours(double dt_hr)
{
    double floor_current_hour = floor(hour);
    long long_current_hour = long(floor_current_hour);
    double fract_current_hour = hour - floor_current_hour;

    wxDateTime current(GetJulianDate());
    //wxDateTime current(day, wxDateTime::Month(month-1), year, long_current_hour, 0, 0, 0);
    //current.MakeUTC();

    double floor_dt_hr = floor(dt_hr);
    double fract_dt_hr = dt_hr - floor_dt_hr; // fractional part of dt_hr

    long long_dt_hr = long(floor_dt_hr);
    wxTimeSpan span(long_dt_hr, 0, 0, 0);
    //span.Set(long(floor_dt_hr));

    current = current.Add(span);

    year = current.GetYear(wxDateTime::GMT0);
    month = int(current.GetMonth(wxDateTime::GMT0)) + 1;
    day = current.GetDay(wxDateTime::GMT0);
    hour = double(current.GetHour(wxDateTime::GMT0)) + fract_current_hour;

    AdjustTimeSeconds(3600.0 * fract_dt_hr);
}

/**
* Use this for small time adjustments, less than 24 hours
*/
void tcDateTime::AdjustTimeSeconds(double dt_s)
{
    double dt_hr = 0.000277777777777778 * dt_s; // hours

    wxASSERT(fabsf(dt_hr) < 24.0);

    hour += dt_hr;

    // update for rollover
    if ((hour >= 0) && (hour < 24.0))
    {
        return;
    }
    else if (hour >= 24.0)
    {
        hour -= 24.0;
        day++;
        if (day > LastDayInMonth())
        {
            month++;
            day = 1;
            if (month > 12)
            {
                year++;
                month = 1;
            }
        }
    }
    else if (hour < 0)
    {
        hour += 24.0;
        day--;
        if (day < 1)
        {
            month--;
            if (month < 1)
            {
                month = 12;
                year--;
            }
            day = LastDayInMonth();
        }
    }

}

const char* tcDateTime::asString() const
{
    static wxString s;

    s.Printf("%04d/%02d/%02d %02d%02d%02d",
        year, month, day, GetHour(), GetMinute(), GetSecond());

    return s.c_str();
}

/**
* @return time of day string
*/
const char* tcDateTime::asStringTOD() const
{
    static wxString s;

    s.Printf("%02d:%02d:%02d",
        GetHour(), GetMinute(), GetSecond());

    return s.c_str();
}

double tcDateTime::GetHoursUTC() const
{
    return hour;
}

int tcDateTime::GetDayOfYear() const
{
    int leapDay = (month > 2) && IsLeapYear(year) ? 1 : 0;

//    int days = yearOrdinal[month];
    return day + yearOrdinal[month] + leapDay;
}

/**
* Formula from http://aa.usno.navy.mil/faq/docs/JD_Formula.html
* JD = 367K - <(7(K+<(M+9)/12>))/4> + <(275M)/9> + I + 1721013.5 + UT/24 - 0.5sign(100K+M-190002.5) + 0.5
* Last 2 terms are skipped assuming a date range of 1900 Mar 1 to 2099 Dec 30
*/
double tcDateTime::GetJulianDate() const
{
    const double inv12 = 1.0 / 12.0;
    const double inv24 = 1.0 / 24.0;
    const double r7ov4 = 7.0 / 4.0;
    const double r275ov9 = 275.0 / 9.0;

    double fYear = double(year);
    double fMonth = double(month);
    double fDay = double(day);

    double julianDate = 367.0*fYear;
    julianDate -= floor(r7ov4 * (fYear + floor(inv12 * (fMonth + 9.0))));
    julianDate += floor(r275ov9 * fMonth) + fDay + 1721013.5 + (inv24 * hour);

    return julianDate;
}

/**
* @return float year with fractional value for precise date
* only uses middle of current month for date estimate
*/
float tcDateTime::GetFractionalYear() const
{
    return (float(year) + (1/12.0f)*(float(month)-0.5f));
}

int tcDateTime::GetYear() const
{
    return year;
}

int tcDateTime::GetMonth() const
{
    return month;
}

const char* tcDateTime::GetMonthString() const
{
    switch (month)
    {
    case 1: return "January"; break;
    case 2: return "February"; break;
    case 3: return "March"; break;
    case 4: return "April"; break;
    case 5: return "May"; break;
    case 6: return "June"; break;
    case 7: return "July"; break;
    case 8: return "August"; break;
    case 9: return "September"; break;
    case 10: return "October"; break;
    case 11: return "November"; break;
    case 12: return "December"; break;
    default: return "Unknown"; break;
    }
}

int tcDateTime::GetDay() const
{
    return day;
}

int tcDateTime::GetHour() const
{
    return int(hour);
}

int tcDateTime::GetMinute() const
{
    return int(60.0*(hour - floorf(hour)));
}

int tcDateTime::GetSecond() const
{
    return int(3600.0*(hour - floorf(hour))) % 60;
}


bool tcDateTime::IsLeapYear(int y) const
{
    return ((year % 4) == 0) && (((year % 100) != 0) || ((year % 400) == 0));
}

/**
* @return last day in current month
*/
int tcDateTime::LastDayInMonth()
{
    if (month != 2)
    {
        return yearOrdinal[month] - yearOrdinal[month-1];
    }
    else
    { 
        int leapDay = (month > 2) && IsLeapYear(year) ? 1 : 0;
        return 28 + leapDay;
    }
}

tcDateTime::tcDateTime(int year_, int month_, int day_, double hour_utc)
: year(year_),
  month(month_),
  day(day_),
  hour(hour_utc)
{

}

tcDateTime::tcDateTime(int year_, int month_, int day_, int hour_, int min_, int sec_)
: year(year_),
  month(month_),
  day(day_),
  hour(double(hour_) + 0.0166666667*double(min_) + 0.000277777778*double(sec_))
{
}


tcDateTime::tcDateTime()
: year(1920),
  month(1),
  day(2),
  hour(12.0)
{

}

tcDateTime::~tcDateTime() 
{
}