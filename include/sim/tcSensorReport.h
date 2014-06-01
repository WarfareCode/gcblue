/**
**  @file tcSensorReport.h
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


#ifndef _SENSORREPORT_H_ 
#define _SENSORREPORT_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "simmath.h"
#include "tcFile.h"
#include <vector>
#include "tcAllianceInfo.h"

class tcSimState;
class tcUpdateStream;
class tcGameStream;

namespace database
{
	class tcDatabase;
}
using database::tcDatabase;


/**
* stores all state information needed by sensor for surveillance tracks
*/
class tcSensorReport
{
public:
    enum {LONLAT_VALID = 0x0001, ALT_VALID = 0x0002, SPEED_VALID = 0x0004, 
          HEADING_VALID = 0x0008, CLIMB_VALID = 0x0010};

    double timeStamp;
    double startTime; ///< start time of track from sensor making report
	long platformID; ///< id of contributing sensor's platform
    long sensorID; ///< database id of sensor
    unsigned int validFlags;

	std::vector<long> emitterList;
    unsigned int classification; // classification of target: air, sub, etc; 0 for unknown
    unsigned char alliance; // alliance number of target, or 0 if unknown
    long databaseID; // specific ID of target in database, -1 for unknown

    float lonEstimate_rad;
    float latEstimate_rad;
    float C11; // covariance terms
    float C22; // covariance terms
    float C12; // covariance terms

    // neglecting correlation between the terms below and lat/lon
    float altEstimate_m; 
    float altVariance;

    float speedEstimate_mps;
    float speedVariance;

    float headingEstimate_rad;
    float headingVariance;

    float climbEstimate_rad;
    float climbVariance;

    double GetTrackLife() const;
	bool IsIdentified() const;
    bool IsNew() const;
    float UncertaintyArea() const;

	tcGameStream& operator<<(tcGameStream& stream);
	tcGameStream& operator>>(tcGameStream& stream);

    const tcSensorReport& operator=(const tcSensorReport& obj);

    tcSensorReport();
    tcSensorReport(const tcSensorReport& obj);
    virtual ~tcSensorReport();
};





#endif 

