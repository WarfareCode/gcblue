/**
**  @file tcSensorReport.cpp
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

#include "tcSensorReport.h"
#include "common/tcObjStream.h"
#include "tcGameStream.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


/**
* Load
*/
tcGameStream& tcSensorReport::operator<<(tcGameStream& stream)
{
    stream >> timeStamp;
    stream >> startTime;
	stream >> platformID;
    stream >> sensorID;
    stream >> validFlags;

    emitterList.clear();
    unsigned int nEmitters;
    stream >> nEmitters;
    for (unsigned int k=0; k<nEmitters; k++)
    {
        long id;
        stream >> id;
        emitterList.push_back(id);
    }

    stream >> classification;
    stream >> alliance;
    stream >> databaseID;

    stream >> lonEstimate_rad;
    stream >> latEstimate_rad;
    stream >> C11;
    stream >> C22;
    stream >> C12;

    stream >> altEstimate_m;
    stream >> altVariance;

    stream >> speedEstimate_mps;
    stream >> speedVariance;

    stream >> headingEstimate_rad;
    stream >> headingVariance;

    stream >> climbEstimate_rad;
    stream >> climbVariance;


    return stream;
}

/**
* Save
*/
tcGameStream& tcSensorReport::operator>>(tcGameStream& stream)
{
    stream << timeStamp;
    stream << startTime;
	stream << platformID;
    stream << sensorID;
    stream << validFlags;

    unsigned int nEmitters = (unsigned int)emitterList.size();
    stream << nEmitters;
    for (unsigned int k=0; k<nEmitters; k++)
    {
        stream << emitterList[k];
    }

    stream << classification;
    stream << alliance;
    stream << databaseID;

    stream << lonEstimate_rad;
    stream << latEstimate_rad;
    stream << C11;
    stream << C22;
    stream << C12;

    stream << altEstimate_m;
    stream << altVariance;

    stream << speedEstimate_mps;
    stream << speedVariance;

    stream << headingEstimate_rad;
    stream << headingVariance;

    stream << climbEstimate_rad;
    stream << climbVariance;


    return stream;
}


double tcSensorReport::GetTrackLife() const
{
    return timeStamp - startTime;
}

bool tcSensorReport::IsIdentified() const
{
    return databaseID != -1;
}

bool tcSensorReport::IsNew() const
{
    return (timeStamp == 0);
}

/**
* @returns determinant of covariance matrix (rad^2 uncertainty area (or area squared?) )
*/
float tcSensorReport::UncertaintyArea() const
{
    return (C11*C22) - (C12*C12);
}

const tcSensorReport& tcSensorReport::operator=(const tcSensorReport& obj)
{
    timeStamp = obj.timeStamp;
    startTime = obj.startTime;
	platformID = obj.platformID;
    sensorID = obj.sensorID;
    validFlags = obj.validFlags;
    emitterList = obj.emitterList;
    classification = obj.classification;
    alliance = obj.alliance;
    databaseID = obj.databaseID;
    lonEstimate_rad = obj.lonEstimate_rad;
    latEstimate_rad = obj.latEstimate_rad;
    C11 = obj.C11;
    C22 = obj.C22;
    C12 = obj.C12;
    altEstimate_m = obj.altEstimate_m;
    altVariance = obj.altVariance;
    speedEstimate_mps = obj.speedEstimate_mps;
    speedVariance = obj.speedVariance;
    headingEstimate_rad = obj.headingEstimate_rad;
    headingVariance = obj.headingVariance;
    climbEstimate_rad = obj.climbEstimate_rad;
    climbVariance = obj.climbVariance;
    
    return *this;
}

tcSensorReport::tcSensorReport(const tcSensorReport& obj)
:   timeStamp(obj.timeStamp),
    startTime(obj.startTime),
	platformID(obj.platformID),
    sensorID(obj.sensorID),
    validFlags(obj.validFlags),
    emitterList(obj.emitterList),
    classification(obj.classification),
    alliance(obj.alliance),
    databaseID(obj.databaseID),
    lonEstimate_rad(obj.lonEstimate_rad),
    latEstimate_rad(obj.latEstimate_rad),
    C11(obj.C11),
    C22(obj.C22),
    C12(obj.C12),
    altEstimate_m(obj.altEstimate_m),
    altVariance(obj.altVariance),
    speedEstimate_mps(obj.speedEstimate_mps),
    speedVariance(obj.speedVariance),
    headingEstimate_rad(obj.headingEstimate_rad),
    headingVariance(obj.headingVariance),
    climbEstimate_rad(obj.climbEstimate_rad),
    climbVariance(obj.climbVariance)
{

}

tcSensorReport::tcSensorReport()
:   timeStamp(0),
    startTime(0),
	platformID(-1),
    sensorID(-1),
    validFlags(0),
    classification(0),
    alliance(0),
    databaseID(-1),
    lonEstimate_rad(0),
    latEstimate_rad(0),
    C11(0),
    C22(0),
    C12(0),
    altEstimate_m(0),
    altVariance(0),
    speedEstimate_mps(0),
    speedVariance(0),
    headingEstimate_rad(0),
    headingVariance(0),
    climbEstimate_rad(0),
    climbVariance(0)
{
}

tcSensorReport::~tcSensorReport()
{
}