/** 
**  @file tcAero.h interface for the tcAero class. tcAero
**  provides simple flight dynamics modeling for missiles.
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

#ifndef _TCAERO_H_
#define _TCAERO_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "tcMissileDBObject.h"

#define G_MPS2 9.80665f 

class tcStream;
class tcGameStream;

class Aero  
{
public:
	struct tsMissileKState 
	{
		float mfFlightTime;
		float mfSpeed_mps; ///< speed through air
		float mfGroundSpeed_mps; ///< speed along ground
		float mfPitch_rad;
		float mfHeading_rad;
		float mfAltitude_m;

		tcStream& operator<<(tcStream& stream);
		tcStream& operator>>(tcStream& stream);
		tcGameStream& operator<<(tcGameStream& stream);
		tcGameStream& operator>>(tcGameStream& stream);
	};

    // atmosphere table
    static std::vector<float> altitude_m;
    static std::vector<float> rho_kgm3;
    static std::vector<float> rho_relative;
    static std::vector<float> c_mps;
    static std::vector<float> T_K;
    static float inv_altitude_step_m; // 1 / step size in altitude

    static void LoadAtmosphereTable();
    static void ClearTables();

    static float GetInterpolationParams(float alt_m, size_t& base_idx);

	static float GetSoundSpeed(float alt_m);	
	static float GetAirDensity(float alt_m);
    static float GetRelativeAirDensity(float alt_m);
	static void UpdateMissileKState(tsMissileKState& k, const database::tcMissileDBObject *apMissileData, float afTimeStep);
};


#endif 
