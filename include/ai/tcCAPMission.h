/**
**  @file tcCAPMission.h
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

#ifndef _TCCAPMISSION_H_
#define _TCCAPMISSION_H_

#include "ai/tcMission.h"
#include "simmath.h"

class tcFlightPort;
class tcPoint;

class tcStream;
class tcCommandStream;
class tcUpdateStream;
class tcGameStream;

namespace ai {

class tcCAPMission : public tcMission
{
public:

	void SetStation(float lon_rad, float lat_rad);
    tcPoint GetStation() const;

    void GetPatrolOffset(float& range_km_, float& az_deg_) const;

	virtual void Update(double t);
    void UpdateStation();


    virtual tcUpdateStream& operator<<(tcUpdateStream& stream);
    virtual tcUpdateStream& operator>>(tcUpdateStream& stream);

    virtual tcGameStream& operator<<(tcGameStream& stream);
    virtual tcGameStream& operator>>(tcGameStream& stream);

	const tcCAPMission& operator=(const tcCAPMission& src);

    tcCAPMission(unsigned int id_, tcMissionManager* mm);
	tcCAPMission(const tcCAPMission& src);
	tcCAPMission();
	virtual ~tcCAPMission();

protected:
	unsigned int quantity; // number aircraft for mission
	tcPoint station;
	float range_km; // calculated
	float az_deg; // calculated

	void CalculatePatrolOffset();
	void MonitorMissionInProgress();

};

} // namespace


#endif