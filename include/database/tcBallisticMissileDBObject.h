/**
**  @file tcBallisticMissileDBObject.h
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

#ifndef _BALLISTICMISSILEDBOBJ_H_
#define _BALLISTICMISSILEDBOBJ_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "tcWeaponDBObject.h"
#include "tcAirDetectionDBObject.h"
#include <vector>

class TiXmlElement;

namespace database
{
    class tcSqlReader;


    class tcBallisticMissileDBObject : public tcWeaponDBObject, public tcAirDetectionDBObject
    {
    public:
        float gmax;                         ///< max Gs

        // flight model parameters
        float timeStage1_s;  
        float accelStage1_mps2;             ///< thrust accel for stage 1
        float bcStage1;                     ///< ballistic coeff = M/(CdA)

        float timeStage2_s;  
        float accelStage2_mps2;
        float bcStage2;

        float timeStage3_s;  
        float accelStage3_mps2;
        float bcStage3;

        float timeStage4_s;  
        float accelStage4_mps2;
        float bcStage4;

        // calculated
        float inv_bcStage1;
        float inv_bcStage2;
        float inv_bcStage3;
        float inv_bcStage4;
        float thrustShutoffTime_s; ///< time when last stage with thrust finishes

        virtual teWeaponLaunchMode GetLaunchMode() const;

        static void AddSqlColumns(std::string& columnString);
        void ReadSql(tcSqlReader& entry);
        void WriteSql(std::string& valueString);

        void CalculateParams();

        tcBallisticMissileDBObject();
        tcBallisticMissileDBObject(const tcBallisticMissileDBObject& obj); ///< copy constructor
        virtual ~tcBallisticMissileDBObject();
    };

}

#endif

