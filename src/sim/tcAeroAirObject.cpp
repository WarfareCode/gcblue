/**
**  @file tcAeroAirObject.cpp
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

#include "tcAeroAirObject.h"
#include "tcAirObject.h"
#include "tcJetDBObject.h"
#include "tcAero.h"
#include "math_constants.h"
#include "tc3DModel.h"
//#include "tcParticleEffect.h"
#include "common/tcStream.h"
#include "common/tcObjStream.h"
#include "common/tcGameStream.h"
#include "tcScenarioLogger.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace database;


tcCommandStream& tcAeroAirObject::operator<<(tcCommandStream& stream)
{
	ClearNewCommand();

    tcAirObject::operator<<(stream);

	stream >> throttleFraction;

	//fprintf(stdout, "received aero guidance update, id: %d, HSA %f, %f, %f\n", mnID,
	//	mcGS.mfGoalHeading_deg, mcGS.mfGoalSpeed_kts, mcGS.mfGoalAltitude_m);

    return stream;
}

tcCommandStream& tcAeroAirObject::operator>>(tcCommandStream& stream)
{
    tcAirObject::operator>>(stream);

    stream << throttleFraction;

	//fprintf(stdout, "sending aero guidance update, id: %d, HSA %f, %f, %f\n", mnID,
	//	mcGS.mfGoalHeading_deg, mcGS.mfGoalSpeed_kts, mcGS.mfGoalAltitude_m);
    return stream;
}

/**
* Load
*/
tcGameStream& tcAeroAirObject::operator<<(tcGameStream& stream)
{
    tcAirObject::operator<<(stream);

	stream >> throttleFraction;
    stream >> levelThrottleFraction;
	stream >> levelThrust_N;
    stream >> angleOfAttack;
	stream >> lastThrust_N;
	stream >> lastWeight_N;

    commandObj << stream;

    return stream;
}

/**
* Save
*/
tcGameStream& tcAeroAirObject::operator>>(tcGameStream& stream)
{
    tcAirObject::operator>>(stream);

	stream << throttleFraction;
    stream << levelThrottleFraction;
	stream << levelThrust_N;
    stream << angleOfAttack;
	stream << lastThrust_N;
	stream << lastWeight_N;

    commandObj >> stream;

    return stream;
}



void tcAeroAirObject::ClearNewCommand()
{
    tcAirObject::ClearNewCommand();
    commandObj.ClearNewCommand();
}

bool tcAeroAirObject::HasNewCommand() const
{
    return tcAirObject::HasNewCommand() || commandObj.HasNewCommand();
}

/**
* Computationally expensive, avoid calling this method frequently
* @param rho set to air density for this altitude [kg/m3]
* @return speed solution in m/s
*/
float tcAeroAirObject::SolveForSpeed(float throttle, float altitude_m, float& rho, float damageLevel, const tcJetDBObject* airData)
{ 
    rho = Aero::GetAirDensity(altitude_m);
    float vsound = Aero::GetSoundSpeed(altitude_m);
    float inv_vsound = 1.0f / vsound;
    float thrustFactor = airData->GetThrustFactor(altitude_m);
    float cdi = airData->GetInducedDragCoefficient();

    // find approximate solution
    float bestSolution_mps = 0;
    float bestThrustMargin = 0;

    for (float speed_mps = 100.0f; speed_mps<=1000.0f; speed_mps+=15.0f)
    {
        float thrust_N = GetThrust(throttle, thrustFactor, speed_mps, airData);

        float vmach = speed_mps * inv_vsound;
        float cdp = airData->GetParasiticDragCoefficient(vmach);
        float rhov2 = rho*speed_mps*speed_mps;
        float drag_N = (cdp*rhov2) + (cdi/rhov2);
        drag_N *= (1 + damageLevel); // additional drag factor for damage (must match calc in UpdateSpeed)

        float thrustMargin = thrust_N - drag_N;
        if (thrustMargin >= 0)
        {
            bestSolution_mps = speed_mps;
            bestThrustMargin = thrustMargin;
        }
    }


    if (bestSolution_mps == 0) return 0;

    // newton's method iterations to refine approximate solution
    const float maxError = 100.0f;
    unsigned nIterations = 0;
    float dv = 1.0f;
    float v = bestSolution_mps;
    float y = bestThrustMargin;
    while ((fabsf(y) > maxError) && (++nIterations < 7))
    {
        float vn = v + dv;
        float vn_mach = vn * inv_vsound;

        float thrust_N = GetThrust(throttle, thrustFactor, vn, airData);

        float cdp = airData->GetParasiticDragCoefficient(vn_mach);
        float rhov2 = rho*vn*vn; 
        float drag_N = (cdp*rhov2) + (cdi/rhov2);
        drag_N *= (1 + damageLevel);

        float yn = thrust_N - drag_N;
        float dvdy = dv / (yn - y);
        dv = -yn * dvdy;
        v = vn;
        y = yn;
    }

    wxASSERT(nIterations < 8); // means we hit max iteration count, bad solution?

    return std::min(v, airData->mfMaxSpeed_kts*C_KTSTOMPS);
}


/*
* @return throttle fraction to achieve speed_mps at altitude_m
*/
float tcAeroAirObject::SolveForThrottle(float speed_mps, float altitude_m, float damageLevel, const tcJetDBObject* airData)
{
    float rho = Aero::GetAirDensity(altitude_m);
    float vsound = Aero::GetSoundSpeed(altitude_m);
    float inv_vsound = 1.0f / vsound;   
    float speed_mach = speed_mps * inv_vsound;

    float cdp = airData->GetParasiticDragCoefficient(speed_mach);
    float cdi = airData->GetInducedDragCoefficient();

    float rhov2 = rho*speed_mps*speed_mps;
    float drag_N = (cdp*rhov2) + (cdi/rhov2);
    drag_N *= (1 + damageLevel); // additional drag factor for damage (must match calc in UpdateSpeed)


    float thrustDesired_N = drag_N;

    float thrustFactor = airData->GetThrustFactor(altitude_m);

    float maxMilThrust_N = GetThrust(1.0f, thrustFactor, speed_mps, airData);
    float maxABThrust_N = GetThrust(2.0f, thrustFactor, speed_mps, airData);

    if (thrustDesired_N <= maxMilThrust_N)
    {
        return thrustDesired_N / maxMilThrust_N;
    }
    else if (thrustDesired_N <= maxABThrust_N)
    {
        float throttle = (thrustDesired_N + maxABThrust_N - 2.0f*maxMilThrust_N) /
            (maxABThrust_N - maxMilThrust_N);
        return throttle;
    }
    else
    {
        return 2.0f;
    }
}

/**
* @return mil throttle setting (max 1.0) to achieve thrust_N for current aeroAirObj
*/
float tcAeroAirObject::MilThrottleForThrust(float thrust_N) const
{
	float thrustFactor = mpDBObject->GetThrustFactor(mcKin.mfAlt_m);
	float maxMilThrust_N = GetThrust(1.0f, thrustFactor, C_KTSTOMPS*mcKin.mfSpeed_kts, mpDBObject);

	if (thrust_N <= maxMilThrust_N)
    {
		return std::max(thrust_N / maxMilThrust_N, 0.0f);
    }
	else
	{
		return 1.0f;
	}
}

/**
* @return fuel rate in kg/s
*/
float tcAeroAirObject::CalculateFuelRate(float speed_mps, float alt_m) const
{
    float throttleSolution = SolveForThrottle(speed_mps, alt_m, mfDamageLevel, mpDBObject);

    float thrustFactor = 0;
    float fuelEfficiencyFactor = 0;
    mpDBObject->GetThrustAndEfficiencyFactors(alt_m, thrustFactor, fuelEfficiencyFactor);

    return GetFuelRate(throttleSolution, fuelEfficiencyFactor, thrustFactor, mfDamageLevel, mpDBObject);
}

/**
* Method to calculate speed and fuel consumption vs. altitude and throttle setting
*/
void tcAeroAirObject::CalculateSpeedParams(float altitude_m, float throttle,
        float& maxSpeed_mps, float& fuelRate_kgps, float damageLevel, const tcJetDBObject* airData)
{
    wxASSERT(airData != 0);
    float rho = 1.0f;
    float speed_mps = SolveForSpeed(throttle, altitude_m, rho, damageLevel, airData);

	float thrustFactor;
	float fuelEfficiencyFactor;
	airData->GetThrustAndEfficiencyFactors(altitude_m, thrustFactor, fuelEfficiencyFactor);

	fuelRate_kgps = GetFuelRate(throttle, fuelEfficiencyFactor, thrustFactor, damageLevel, airData);

	// disabled this 1 MAY 2011, may need to do this stall check in calling functions

	//float stallSpeed_mps = airData->stallSpeed_mps * powf(tcJetDBObject::inv_rho_sealevel * rho, -0.5f); // stall speed at altitude
    /* if (speed_mps >= stallSpeed_mps)
    {
        float thrustFactor;
        float fuelEfficiencyFactor;
        airData->GetThrustAndEfficiencyFactors(altitude_m, thrustFactor, fuelEfficiencyFactor);

        fuelRate_kgps = GetFuelRate(throttle, fuelEfficiencyFactor, thrustFactor, damageLevel, airData);
    }
    else
    {
        speed_mps = stallSpeed_mps;
        fuelRate_kgps = 99.0f;
    }*/

    maxSpeed_mps = speed_mps;
}

float tcAeroAirObject::GetCruiseRangeKm(float alt_m) const
{
	float vcruise_mps = 0;
	return GetAeroCruiseRangeKm(alt_m, fuel_kg, mfDamageLevel, mpDBObject, vcruise_mps);
}

float tcAeroAirObject::GetAeroCruiseRangeKm(float alt_m, float fuelLoad_kg, float damageLevel, const tcJetDBObject* airData, float& cruise_mps)
{
    wxASSERT(airData != 0);
    cruise_mps = airData->GetCruiseSpeedForAltitude(alt_m);

    float throttleSolution = SolveForThrottle(cruise_mps, alt_m, damageLevel, airData);
    if (throttleSolution > 1.0f)
    {
        float rho_temp;
        throttleSolution = 1.0f;
        cruise_mps = SolveForSpeed(throttleSolution, alt_m, rho_temp, damageLevel, airData);
    }

    float thrustFactor = 0;
    float fuelEfficiencyFactor = 0;
    airData->GetThrustAndEfficiencyFactors(alt_m, thrustFactor, fuelEfficiencyFactor);

    float fuelRate_kgps = GetFuelRate(throttleSolution, fuelEfficiencyFactor, thrustFactor, damageLevel, airData);
    wxASSERT(fuelRate_kgps >= 0);
    
    float time_s = fuelLoad_kg / (fuelRate_kgps + 0.0001f);
    float distance_km = 0.001f * cruise_mps * time_s;

    return distance_km;
}

/**
* Expensive, don't call this too often
* Checks for best cruise altitude every 1000 m between 6000 m and 13000 m altitude
*/
float tcAeroAirObject::GetCruiseAltitude() const
{
    float bestCruiseAlt_m = 1000.0f;
    float bestCruiseRange_km = 0.0f;

    for (float alt_m=6000.0f; alt_m<=13000.0f; alt_m += 1000.0f)
    {
        float range_km = GetCruiseRangeKm(alt_m);
        if (range_km > bestCruiseRange_km)
        {
            bestCruiseAlt_m = alt_m;
            bestCruiseRange_km = range_km;
        }
    }

    return bestCruiseAlt_m;
}

/**
* @return cruise speed in kts
*/
float tcAeroAirObject::GetCruiseSpeedForAltitude(float alt_m) const
{
    return C_MPSTOKTS * mpDBObject->GetCruiseSpeedForAltitude(alt_m);
}


/**
* @return stall speed in kts
*/
float tcAeroAirObject::GetStallSpeedForAltitude(float alt_m) const
{
    return C_MPSTOKTS * mpDBObject->GetStallSpeedForAltitude(alt_m);
}



/**
* @return current fuel burn rate in kg/s
* This info could be saved during Update() instead of being recalculated here
*/
float tcAeroAirObject::GetCurrentFuelRate() const
{
    float thrustFactor;
    float fuelEfficiencyFactor;
    mpDBObject->GetThrustAndEfficiencyFactors(mcKin.mfAlt_m, thrustFactor, fuelEfficiencyFactor);

    return GetFuelRate(throttleFraction, fuelEfficiencyFactor, thrustFactor, mfDamageLevel, mpDBObject);
}


float tcAeroAirObject::GetOpticalCrossSection() const
{
    return mpDBObject->opticalCrossSection_dBsm;
}



float tcAeroAirObject::GetIRSignature(float az_deg) const
{
    bool isSupersonic = (mcKin.mfSpeed_kts > 600.0f); // a rough test, no altitude variation
    bool afterburnersOn = (GetThrottleFraction() > 1.0f);

    if (!isSupersonic)
    {
        if (!afterburnersOn)
        {
            return mpDBObject->GetIRSig_dB(az_deg, tcAirDetectionDBObject::IRMODELA);
        }
        else
        {
            return mpDBObject->GetIRSig_dB(az_deg, tcAirDetectionDBObject::IRMODELB);
        }
    }
    else
    {
        if (!afterburnersOn)
        {
            return mpDBObject->GetIRSig_dB(az_deg, tcAirDetectionDBObject::IRMODELC);
        }
        else
        {
            return std::max(mpDBObject->GetIRSig_dB(az_deg, tcAirDetectionDBObject::IRMODELB),
                            mpDBObject->GetIRSig_dB(az_deg, tcAirDetectionDBObject::IRMODELC));
        }
    }

}


void tcAeroAirObject::Clear()  
{  
    tcAirObject::Clear();
}


void tcAeroAirObject::RandInitNear(float afLon_deg, float afLat_deg)
{
    if (mpDBObject == NULL) {return;}
    tcAirObject::RandInitNear(afLon_deg, afLat_deg);

    // overwrite tcAirObject random suffix
    mzUnit = "AIRX_";
    mzUnit.AssignRandomSuffix();

    throttleFraction = 0.7f;
    angleOfAttack = 0;
}

void tcAeroAirObject::PrintToFile(tcFile& file) 
{
    tcAirObject::PrintToFile(file);
}

void tcAeroAirObject::SaveToFile(tcFile& file) 
{
    tcAirObject::SaveToFile(file); 
    file.Write(&throttleFraction,sizeof(throttleFraction)); 
    file.Write(&angleOfAttack,sizeof(angleOfAttack));
}

void tcAeroAirObject::LoadFromFile(tcFile& file) 
{
    tcAirObject::LoadFromFile(file); 
    file.Read(&throttleFraction,sizeof(throttleFraction));
    file.Read(&angleOfAttack,sizeof(angleOfAttack));
}

void tcAeroAirObject::Serialize(tcFile& file, bool mbLoad) 
{
    if (mbLoad) 
    {
        LoadFromFile(file);
    }
    else 
    {
        SaveToFile(file);
    }
}

void tcAeroAirObject::SaveToPython(scriptinterface::tcScenarioLogger& logger)
{
	wxString s;

	tcPlatformObject::SaveToPython(logger);
	
	s.Printf("UI.SetThrottle(%f)", GetThrottleFraction());
	logger.AddScenarioText(s.ToStdString());
}

/**
* Solve for throttle setting for requested speed and
* set throttle with result
*/
void tcAeroAirObject::SetSpeed(float newSpeed) 
{
    tcPlatformObject::SetSpeed(newSpeed);

    float throttle = SolveForThrottle(C_KTSTOMPS*newSpeed, mcKin.mfAlt_m, mfDamageLevel, mpDBObject);

    SetThrottleFraction(throttle);
}

/**
* New throttle fraction system for afterburners, 
* 2.0 is max afterburner, 1.0-2.0 varies afterburner thrust continuously. This
* isn't realistic for most aircraft, but makes formation flying at afterburners 
* a lot easier
*/
void tcAeroAirObject::SetThrottleFraction(float fract) 
{
    throttleFraction = std::min(fract, 2.0f);
    levelThrottleFraction = 0; // cancel any automatic climb throttle adjust

	commandObj.SetNewCommand(THROTTLE_CMD);
}

void tcAeroAirObject::ApplyRestrictions() 
{
    tcAirObject::ApplyRestrictions();
}



/**
* Has problems for large time steps, > about 1 sec
*/
void tcAeroAirObject::UpdateClimb(float dt_s) 
{
    float climbAngleStart_rad = mcKin.mfClimbAngle_rad; // save for auto throttle adjust calculation

    tcAirObject::UpdateClimb(dt_s);
    mcKin.mfPitch_rad = angleOfAttack + mcKin.mfClimbAngle_rad;

    if ((mcKin.mfClimbAngle_rad == 0) && (levelThrottleFraction == 0))
    {
        return;
	}

	if ((mcKin.mfClimbAngle_rad == 0) && (levelThrottleFraction != 0))
	{	// restore old throttle setting       
		throttleFraction = levelThrottleFraction; // resume previous throttle setting
		levelThrottleFraction = 0;
		levelThrust_N = 0;
		return;
    }

	if (levelThrottleFraction == 0)
	{   // save level throttle and thrust settings
		levelThrottleFraction = throttleFraction;
		throttleFraction = std::max(throttleFraction, 1.0f);
		levelThrust_N = lastThrust_N;
	}

	bool climbChanging = (mcKin.mfClimbAngle_rad != climbAngleStart_rad);


	if (climbChanging)
	{
		float thrustNeededed_N = levelThrust_N + lastWeight_N * sinf(mcKin.mfClimbAngle_rad);
		throttleFraction = MilThrottleForThrust(thrustNeededed_N);
	}

}





void tcAeroAirObject::UpdateEffects()
{
    if (model)
    {
		if (mfDamageLevel > 0.1f)
		{
			model->SetSmokeMode(tc3DModel::DAMAGE);
		}
        else if (throttleFraction > 1.0f)
        {
            model->SetSmokeMode(tc3DModel::AFTERBURNER);
        }
        else
        {
            model->SetSmokeMode(tc3DModel::OFF);
        }
        model->UpdateEffects();
    }
}

void tcAeroAirObject::UpdateHeading(float dt_s) 
{
    tcAirObject::UpdateHeading(dt_s);
}

void tcAeroAirObject::Update(double afStatusTime) 
{
    const float min_update_s = 0.0f;
    float dt_s = (float)(afStatusTime - mfStatusTime);

    // shouldn't be called for child objects
    if (parent != NULL) {return;} // captive, let parent update if applicable
    if ((dt_s <= min_update_s)  && !tcGameObject::IsEditMode())
    {
        return;
    } // added for pause case

    wxASSERT(mpDBObject);
    
    UpdateEffects();

    if (mfDamageLevel >= 1.0f)
    {
        UpdateDestroyed(afStatusTime);
        mfStatusTime = afStatusTime;
        return;
    }

	/* In multiplayer mode, skip command based updates for client objects not controlled
	** by client. This will cause object to jump more but avoids having to broadcast command
	** changes to all alliance clients. The controller of the object will see smoother
	** behavior.
    ** CHANGED 24AUG2008 to remove the IsControlled() case, this jumps around too much at the client, defeating the purpose
	*/
	if (!IsClientMode())
	{
        formation.Update((tcAeroAirObject*)this);

        UpdateInFlightRefuel(dt_s);

		UpdateHeading(dt_s);

		UpdateSpeed(dt_s);

		UpdateClimb(dt_s);

		ApplyRestrictions();
	}
    else if (IsControlled())
    {
        UpdateHeading(dt_s);
    }

    Move(dt_s);

    UpdateLauncherState(dt_s);

    UpdateSensors(afStatusTime);

    UpdateAI(afStatusTime);

    Update3D();

    mfStatusTime = afStatusTime; 
}

/**
* @param vmach Speed divided by speed of sound (mach number)
* @return parasitic drag coeff including 0.5 factor
*/
float tcAeroAirObject::GetParasiticDragCoefficient(float vmach) const
{
    return mpDBObject->GetParasiticDragCoefficient(vmach);
}

/**
* @return kg/s fuel consumption
*/
float tcAeroAirObject::GetFuelRate(float throttle, float efficiencyFactor, float thrustFactor, float damageLevel, 
								   const tcJetDBObject* airData)
{
    float damagePenalty = 1.0f + 9.0f*damageLevel; // fuel consumption increases with damage

    wxASSERT((throttle >= 0) && (throttle <= 2.0f));

    if (throttle <= 1.0f)
    {
        return throttle * thrustFactor * efficiencyFactor * 
            damagePenalty * airData->mfFuelRate_kgps;
    }
    else
    {
        float standardRate = (2.0f - throttle) * thrustFactor * efficiencyFactor * 
            airData->mfFuelRate_kgps;

        float afterburnerRate = (throttle - 1.0f)*airData->mfAfterburnFuelRate_kgps;

        return damagePenalty * (standardRate + afterburnerRate);
    }
}

/**
* @param thrustFactor altitude dependent thrust factor (applied to military and afterburner thrust)
* @return thrust in Newtons
*/
float tcAeroAirObject::GetThrust(float throttle, float thrustFactor, float speed_mps, const tcJetDBObject* airData)
{
	wxASSERT(airData != 0);
    wxASSERT(throttle <= 2.0f);

    float a_mil = airData->militaryThrustSpeedSlope;
    float a_ab = airData->abThrustSpeedSlope;
    float adjustedMilThrust = airData->militaryThrust_N * (1.0f + (a_mil * speed_mps)); // could avoid 2 mults here by pre-calculating slope constant
    
    if (throttle <= 1.0f)
    {
        return adjustedMilThrust * throttle * thrustFactor;
    }
    else
    {
        float standardThrust_N = adjustedMilThrust * (2.0f - throttle);

        float adjustedABThrust = airData->mfAfterburnThrust_N * (1.0f + (a_ab * speed_mps));
        float burnerThrust_N = adjustedABThrust * (throttle - 1.0f); 
        
        return thrustFactor * (standardThrust_N + burnerThrust_N);
    }
}

/**
* Calculate thrust and fuel consumption. Update fuel.
* @return thrust in Newtons
*/
float tcAeroAirObject::UpdateThrust(float dt_s)
{
    if (fuel_kg > 0)
    {
        // calculate thrust decay factor based on altitude
        float thrustFactor;
		float fuelEfficiencyFactor;
        mpDBObject->GetThrustAndEfficiencyFactors(mcKin.mfAlt_m, thrustFactor, fuelEfficiencyFactor);

        float fuelRate_kgps = GetFuelRate(throttleFraction, fuelEfficiencyFactor, thrustFactor, 
			mfDamageLevel, mpDBObject);
        float thrust_N = GetThrust(throttleFraction, thrustFactor, mcKin.mfSpeed_kts*C_KTSTOMPS, mpDBObject);

        fuel_kg -= fuelRate_kgps * dt_s;
        if (fuel_kg < 0) fuel_kg = 0; // sets fuel back to zero after flame out 

        return thrust_N;
    }
    else
    {
        return 0; // out of fuel
    }
}

/**
* Uses aerodynamic model to update speed.
* @param dt_s time step since last update
*/
void tcAeroAirObject::UpdateSpeed(float dt_s)
{

    float rhv2;
    float K_dp;
    float vmach, vsound;
    float fDrag_N, fThrust_N;

    tcKinematics& k = mcKin;


    float mfSpeed_mps = k.mfSpeed_kts*C_KTSTOMPS;
	float rho = Aero::GetAirDensity(k.mfAlt_m);
    rhv2 = rho*mfSpeed_mps*mfSpeed_mps;
	vsound = Aero::GetSoundSpeed(k.mfAlt_m);
    vmach = mfSpeed_mps/vsound;

	float ias_mps = sqrtf(0.8f * rho) * mfSpeed_mps; // approximate indicated airspeed
	float inv_ias_mps = 1.0 / ias_mps; 
	float not_stall = float(ias_mps > mpDBObject->stallSpeed_mps);

    K_dp = GetParasiticDragCoefficient(vmach);
    
    fDrag_N = (K_dp * rhv2) + not_stall*(mpDBObject->GetInducedDragCoefficient() / rhv2);
    fDrag_N *= (1.0f + mfDamageLevel); // drag increases with fractional damage


    float mass_kg = mpDBObject->weight_kg + fuel_kg;
    float weight_N = 0.5f * C_G * mass_kg; // 0.5 is ad hoc factor
	lastWeight_N = weight_N;

    // calculate lift needed to balance weight
    //float lift_N = weight_N * cosf(k.mfClimbAngle_rad);
    //float Cl = lift_N / (rhv2 * mpDBObject->mfWingArea_sm);
    
  

	fThrust_N = UpdateThrust(dt_s);
	lastThrust_N = fThrust_N;

	const float aoaConstant = 5.0f; // for approximation, aoa = C / IAS
    angleOfAttack = aoaConstant * inv_ias_mps;

	const float stallPitch = -0.1f; // 10:1 glide ratio

	if (ias_mps <= mpDBObject->stallSpeed_mps)
    {
        throttleFraction = 1.0f;
		//mcGS.mfGoalAltitude_m = k.mfAlt_m - 50.0f; // avoid flooding connection with stall adjustments
		maxPitch_rad = std::min(maxPitch_rad, stallPitch);
    }    
	else if (ias_mps < mpDBObject->stallSpeed_mps + 50.0f)
    {
		maxPitch_rad = std::min(maxPitch_rad, stallPitch + 0.02f * (ias_mps - mpDBObject->stallSpeed_mps));
	}
	else
	{
        if (maxPitch_rad < 0) maxPitch_rad = MAX_PITCH_RAD; // reset to default
    }

    float netForce_N = fThrust_N - fDrag_N - weight_N *sinf(k.mfClimbAngle_rad);

    /* drag model has issues: acceleration is too slow, faster accel can
    ** obtained by climbing and then descending which is not correct.
    ** Adding a 4.0 factor for faster accel/decel
    */
    float accel_mps2 = 4.0f * netForce_N / mass_kg; 

    k.mfSpeed_kts += (accel_mps2 * dt_s)*C_MPSTOKTS;

    if (k.mfSpeed_kts > mpDBObject->mfMaxSpeed_kts) k.mfSpeed_kts = mpDBObject->mfMaxSpeed_kts;
	else if (k.mfSpeed_kts <= 40.0)
	{
		// shouldn't happen, but limit speed to 40 and slowly dive in this case
		k.mfSpeed_kts = 40.0;
		if (k.mfClimbAngle_rad > -0.1) k.mfClimbAngle_rad -= dt_s * 0.1f;
	}
}


/**
* Shouldn't use this form.
*/
tcAeroAirObject::tcAeroAirObject() 
: tcAirObject()
{
    wxASSERT(false);
    mnModelType = MTYPE_FIXEDWINGX;
}

/**
* Constructor that initializes using info from database entry.
*/
tcAeroAirObject::tcAeroAirObject(tcJetDBObject *obj)
: tcAirObject(obj),
  levelThrottleFraction(0),
  levelThrust_N(0),
  angleOfAttack(0),
  lastThrust_N(0),
  lastWeight_N(1)
{
    mpDBObject = obj;
    mnModelType = MTYPE_FIXEDWINGX;
    SetThrottleFraction(1.0f);
}

tcAeroAirObject::~tcAeroAirObject()
{
}
