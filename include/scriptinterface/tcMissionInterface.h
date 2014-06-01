/**  
**  @file tcMissionInterface.h
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

#ifndef _TCMISSIONINTERFACE_H_
#define _TCMISSIONINTERFACE_H_


#if _MSC_VER > 1000
#pragma once
#endif 


#include <boost/python.hpp>

using namespace boost::python;

namespace ai
{
    class tcAttackMission;
}

namespace scriptinterface 
{
    /**
    * Interface for platform to access mission details
    */
    class tcMissionInterface
    {
    public:        
        ai::tcAttackMission* mission;
        static ai::tcAttackMission* static_mission;
        
        // Interface class management functions
        static object GetInterface();
        static void SetObj(ai::tcAttackMission* mission_);

        void GetLocalObj();
        void SetMission(ai::tcAttackMission* mission_);

        // Interface functions to be called through Python
        bool IsValid();
        
        unsigned int GetMissionAircraftCount() const; ///< @returns number of mission aircraft
        unsigned int GetAirborneAircraftCount() const;
		long GetAirborneAircraftId(unsigned int idx) const;
        unsigned int GetSmallestWaypointIndex() const;

        tcMissionInterface();
        virtual ~tcMissionInterface();

    private:
        
    };

}

#endif

