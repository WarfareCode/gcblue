/**
**  @file tcSonarEnvironment.cpp
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

#include "tcSonarEnvironment.h"
#include "tcSonarRay.h"
#include "tcOptions.h"
#include "tcGameStream.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


tcSonarEnvironment* tcSonarEnvironment::Get()
{
    static tcSonarEnvironment instance;
    return &instance;
}

std::vector<std::string> tcSonarEnvironment::templateNames;



tcGameStream& tcSonarEnvironment::operator<<(tcGameStream& stream)
{
    Clear();

    unsigned int val;
    stream >> val;
    SetSeaState(val);

    svp.clear();
    unsigned char nSVP;
    stream >> nSVP;
    for (unsigned char n=0; n<nSVP; n++)
    {
        float depth_m;
        float v_mps;
        stream >> depth_m;
        stream >> v_mps;

        AddSVPPoint(depth_m, v_mps);
    }

	stream >> layerDepth_m;
	stream >> sonarTemplateId;

	sonarTemplateId = -1;

    return stream;
}

tcGameStream& tcSonarEnvironment::operator>>(tcGameStream& stream)
{
    stream << seaState;

    unsigned char nSVP = svp.size();
    stream << nSVP;
    for (unsigned char n=0; n<nSVP; n++)
    {
        stream << svp[n].depth_m;
        stream << svp[n].v_mps;
    }

	stream << layerDepth_m;
	stream << sonarTemplateId;

    return stream;
}


void tcSonarEnvironment::AddSVPPoint(float depth_m, float speed_mps)
{
    SVPData data;

    data.depth_m = depth_m;
    data.v_mps = speed_mps;

    svp.push_back(data);

    if (svp.size() < 2) return;

    if (!ValidateSVP()) return;

    for (size_t k=0; k<svp.size()-1; k++)
    {
        float inv_gradient = 0;
        if (svp[k+1].v_mps != svp[k].v_mps)
        {
            inv_gradient = (svp[k+1].depth_m - svp[k].depth_m) / (svp[k+1].v_mps - svp[k].v_mps);
        }
        else
        {
            inv_gradient = 1e7;
        }

        float R = svp[k].v_mps * inv_gradient;
        svp[k].R_m = R;
        svp[k].R2_m = R*R;
    }

    svp.back().R_m = 1e10f;
    svp.back().R2_m = 1e20f;

    // update layerDepth_m automatically for simple TL model
    UpdateLayerDepth();
}

/**
* @param startDepth_m depth of sonar (positive number)
* @param startAngle_rad starting angle of ray, positive is down
* @param bottom_m depth of bottom (assume flat bottom for this model)
*/
const tcSonarRay& tcSonarEnvironment::CalculateRay(float startDepth_m, float startAngle_rad, float bottom_m)
{
    static tcSonarRay ray;

    ray.data.clear();

    const float max_x = 100e3;

    float x = 0;
    float y = std::min(startDepth_m, bottom_m - 1.0f);
    float angle = startAngle_rad;
//    unsigned int bounces = 0;
//    const unsigned int maxBounces = 4;
    float reflectionLossFactor = 1.0f;

    if (fabsf(angle) < 0.002f)
    {
        angle = (angle > 0) ? 0.002f : -0.002f;
    }

    if (!ValidateSVP())
    {
        return ray;
    }

    while ((x <= max_x) && (reflectionLossFactor > 0.001f) && (ray.data.size() < 100))
    {        
        tcSonarRay::RayPoint point;
        point.x = x;
        point.y = y;

        // find the SVP segment we're in
        size_t currentSegment = GetSVPSegment(y, angle);

        float R = svp[currentSegment].R_m;
        float R2 = svp[currentSegment].R2_m;
        float xc = x + R*sinf(angle);
        float yc = y - R*cosf(angle);

        float y_next = (angle >= 0) ? svp[currentSegment+1].depth_m : svp[currentSegment].depth_m;
        y_next = std::min(y_next, bottom_m); // limit to bottom

        float x_term = R2 - (y_next-yc)*(y_next-yc);
        float x_term2 = R2 - (y-yc)*(y-yc);
        float x_solve = 0;
        float y_solve = 0;

        if (x_term > 0)
        {
            float sqrt_x_term = sqrtf(x_term);
            float x_solve1 = xc + sqrt_x_term;
            float x_solve2 = xc - sqrt_x_term;

            if ((x_solve2 > x) && (x_solve2 < x_solve1)) x_solve = x_solve2;
            else x_solve = x_solve1;
            
            y_solve = y_next;
           
        }
        else if (x_term2 > 0)
        {
            x_solve = xc + sqrtf(x_term2);
            y_solve = y;
        }
        else
        {
            wxASSERT(false);
            return ray;
        }

        wxASSERT(x_solve > x); 
        float angle_solve = atanf((xc-x_solve)/(y_solve-yc));

        if (y_solve <= 0) // hit surface?
        {
            y = 0;
            angle_solve = (angle_solve < 0) ? -angle_solve : angle_solve;
            reflectionLossFactor *= surfaceLossFactor;
        }
        else if (y_solve >= bottom_m) // hit bottom?
        {
            y = bottom_m;
            angle_solve = (angle_solve > 0) ? -angle_solve : angle_solve;
            reflectionLossFactor *= bottomLossFactor;
        }

        x = x_solve;
        y = y_solve;
        angle = angle_solve;

        point.xmax = x;
        point.R = R;
        point.R2 = R2;
        point.xc = xc;
        point.yc = yc;
        point.reflectionLossFactor = reflectionLossFactor;

        ray.data.push_back(point);
    }


    return ray;
}

void tcSonarEnvironment::Clear()
{
    ClearSVP();   
    SetDefaultSVP();
    beamCache.clear();

    lastUpdateTime = 0;
}


void tcSonarEnvironment::ClearSVP()
{
    svp.clear();
    layerDepth_m = 10000.0f;
}

void tcSonarEnvironment::EditSVPPoint(size_t idx, float depth_m, float speed_mps)
{
    if (idx < svp.size())
    {
        svp[idx].v_mps = speed_mps;
        svp[idx].depth_m = depth_m;

		sonarTemplateId = -1; // reset template id since we're manually editing the SVP
    }
    else
    {
        return;
    }

    if (idx == 0) svp[0].depth_m = 0;

    if (idx > 0)
    {
        svp[idx].depth_m = std::max(svp[idx].depth_m, svp[idx-1].depth_m + 1.0f); // don't allow depth to be less than previous point
    }

    if ((idx+1) < svp.size())
    {
        svp[idx].depth_m = std::min(svp[idx].depth_m, svp[idx+1].depth_m - 1.0f); // don't allow depth to be greater than next point
    }

    for (size_t k=0; k<svp.size()-1; k++)
    {
        float inv_gradient = 0;
        if (svp[k+1].v_mps != svp[k].v_mps)
        {
            inv_gradient = (svp[k+1].depth_m - svp[k].depth_m) / (svp[k+1].v_mps - svp[k].v_mps);
        }
        else
        {
            inv_gradient = 1e7;
        }

        float R = svp[k].v_mps * inv_gradient;
        svp[k].R_m = R;
        svp[k].R2_m = R*R;
    }

    svp.back().R_m = 1e10f;
    svp.back().R2_m = 1e20f;



    UpdateLayerDepth();
}

float tcSonarEnvironment::GetAmbientNL(float freq_Hz) const
{
    return noiseLevelBase - noiseLevelSlope * log10f(freq_Hz);
}

size_t tcSonarEnvironment::GetBeamCount() const
{
    return beamCache.size();
}

/**
* @return bottom loss in dB (positive value)
*/
float tcSonarEnvironment::GetBottomLossDB() const
{
    return -10.0f*log10f(bottomLossFactor);
}

unsigned int tcSonarEnvironment::GetNumberTemplates() const
{
	return (unsigned int)templateNames.size();
}

unsigned int tcSonarEnvironment::GetSeaState() const
{
    return seaState;
}

/**
* @return surface loss in dB (positive value)
*/
float tcSonarEnvironment::GetSurfaceLossDB() const
{
    return -10.0f*log10f(surfaceLossFactor);
}


const std::vector<tcSonarEnvironment::SVPData>& tcSonarEnvironment::GetSVP() const
{
    return svp;
}

size_t tcSonarEnvironment::GetSVPSegment(float depth, float angle) const
{
    
    if (depth >= svp.back().depth_m) // used to be "bottom" defined with SVP, now means SVP doesn't go deep enough
    { 
        wxASSERT(false);
        return svp.size()-2;
    }

    
    if (angle >= 0)
    {
        for (size_t k=0;(k<svp.size()-1); k++)
        {
            if ((depth >= svp[k].depth_m) && (depth < svp[k+1].depth_m))
            {
                return k;
            }
        }
    }
    else
    {
        for (size_t k=0;(k<svp.size()-1); k++)
        {
            if ((depth > svp[k].depth_m) && (depth <= svp[k+1].depth_m))
            {
                return k;
            }
        }
    }

    if (depth == 0.0f)
    {
        return 0;
    }
    else
    {       
        wxASSERT(false);
        fprintf(stderr, "tcSonarEnvironment::GetSVPSegment - unknown error\n");
        return 0;
    }

}

/**
* For saving scenario data to py scen file
* @return "depth1_m,speed1_mps,depth2_m,speed2_mps,..." string form of SVP
*/
const wxString& tcSonarEnvironment::GetSVPString() const
{
    static wxString s;
    s.clear();

    for (size_t k=0; k<svp.size(); k++)
    {
        s += wxString::Format("%f,%f", svp[k].depth_m, svp[k].v_mps);
        if ((k+1) < svp.size())
        {
            s += ",";
        }
    }

    return s;
}

int tcSonarEnvironment::GetTemplate() const
{
	return sonarTemplateId;
}

const std::string& tcSonarEnvironment::GetTemplateName(unsigned int id) const
{
	static std::string errorString("Error");

	if (id < templateNames.size())
	{
		return templateNames[id];
	}
	else
	{
		return errorString;
	}
}

/**
* @return transmission loss in dB (positive loss)
* @param depth_m depth of sonar
*/
float tcSonarEnvironment::GetTL(long key, double t, float depth_m, float targetRange_m, float targetDepth_m, float bottomDepth_m)
{
    if ((targetRange_m < 2000.0f) || UsingSimplePropagation())
    {
        return GetTLSimple(depth_m, targetRange_m, targetDepth_m, bottomDepth_m);
    }

    bottomDepth_m = std::max(bottomDepth_m, 10.0f); // don't allow bottom < 10 m deep

    std::map<long, BeamData>::iterator iter = beamCache.find(key);
    if (iter == beamCache.end())
    {
        BeamData beamData;
        beamData.depth_m = -999.9f; // to force update
        beamData.t_update = t;
        beamCache[key] = beamData;
        iter = beamCache.find(key);
    }

    wxASSERT(iter != beamCache.end());

    if (fabsf(iter->second.depth_m - depth_m) >= depthUpdateThreshold_m)
    {
        UpdateBeam(iter->second.beam, depth_m, bottomDepth_m);
        iter->second.depth_m = depth_m;
    }

    return CalculateTL(iter->second.beam, targetRange_m, targetDepth_m);
}

/**
* Calculates sonar transmission loss basd on ray density. Ray paths and loss are calculated in CalculateRay method
*/
float tcSonarEnvironment::CalculateTL(const std::vector<tcSonarRay>& beam, float range_m, float depth_m) const
{
    depth_m = std::max(depth_m, 2.0f); // surface target considered min 2 m deep

    wxASSERT(beam.size() > 1);

    // iterate through rays and calculate beam depth and reflection loss
    std::vector<float> rayDepth_m;
    std::vector<float> rayLoss;
    size_t nRays = beam.size();
    for (size_t n=0; n<nRays; n++)
    {
        float reflectionLossFactor;
        rayDepth_m.push_back(beam[n].CalculateDepth(range_m, reflectionLossFactor));
        rayLoss.push_back(reflectionLossFactor);
    }

    // find pairs of rays that cross evaluation depth and accumulate radiated power 
    float ray_power = 1e-10f;
    float linearSpread_m = range_m * angleStep_rad; // expected spacing between rays with no refraction
    for (size_t n=0; n<nRays-1; n++)
    {
        bool pairSpansDepth = ((rayDepth_m[n] <= depth_m) && (rayDepth_m[n+1] > depth_m)) ||
                              ((rayDepth_m[n+1] <= depth_m) && (rayDepth_m[n] > depth_m));
        if (pairSpansDepth)
        {
            float raySeparation_m = std::max(fabsf(rayDepth_m[n] - rayDepth_m[n+1]), 0.5f); // to avoid divide by zero and too big of a caustic due to lack of precision
            float invSeparation = 1.0f / raySeparation_m;
            if (rayLoss[n] == rayLoss[n+1])
            {
                ray_power += (rayLoss[n] * linearSpread_m * invSeparation);
            }
            else
            {
                float x1_m = fabsf(rayDepth_m[n] - depth_m);
                float x2_m = fabsf(rayDepth_m[n+1] - depth_m);
                wxASSERT((((x1_m+x2_m) < 1.01f*raySeparation_m) && ((x1_m+x2_m) > 0.99f*raySeparation_m)) || (raySeparation_m == 0.5f));
                float weightedLoss = (x2_m*invSeparation)*rayLoss[n] + (x1_m*invSeparation)*rayLoss[n+1];

                ray_power += (weightedLoss * linearSpread_m * invSeparation);
            }
            
        }
    }

    // ray_power of 1 means spherical spreading
    float logTargetRange = log10f(range_m);
    float TL_dB = 10.0f * (2.0f*logTargetRange - log10f(ray_power));

    wxASSERT(TL_dB >= 0);

    // limit TL to cube law spreading
    return std::min(TL_dB, 30.0f * logTargetRange);
}

float tcSonarEnvironment::GetTLSimple(float depth_m, float targetRange_m, float targetDepth_m, float bottom_m)
{
    float TL_dB = 0;
    if (targetRange_m > bottom_m)
    {
        TL_dB = (10.0f * log10f(targetRange_m)) + (10.0f * log10f(bottom_m));
    }
    else
    {
        TL_dB = 20.0f * log10(targetRange_m);
    }


    // crude thermocline
    bool parentAbove = depth_m < layerDepth_m;
    bool targetAbove = targetDepth_m < layerDepth_m;
    if (parentAbove != targetAbove) TL_dB += 10.0f; // add 10 dB loss

    return TL_dB;
}


void tcSonarEnvironment::SetBottomLoss(float val_dB)
{
    bottomLossFactor = powf(10.0f, -0.1f*val_dB);
}

void tcSonarEnvironment::SetDefaultSVP()
{
    svp.clear();
    AddSVPPoint(0, 1515);
    AddSVPPoint(200, 1500);
    AddSVPPoint(300, 1510);
    AddSVPPoint(500, 1520);
    AddSVPPoint(5000, 1600);
}

/**
* Sets SVP, surface loss, and bottom loss
*/
void tcSonarEnvironment::SetTemplate(int id)
{
	SetSurfaceLoss(1.5f);
	SetBottomLoss(5.0f);
	svp.clear();

	sonarTemplateId = id;

	wxASSERT(templateNames.size() == 5); // template names needs to be manually synchronized with this method

	switch (id)
	{
	case 0: // simple propagation model (overrides user option setting)
		SetDefaultSVP();
		sonarTemplateId = 0; // SetDefaultSVP resets sonarTemplateId
		return;
		break;
	case 1: // north atlantic winter fig 5.14 Urick
		AddSVPPoint(C_FTTOM*0, C_FTTOM*4918);
		AddSVPPoint(C_FTTOM*700, C_FTTOM*4927);
		AddSVPPoint(C_FTTOM*1000, C_FTTOM*4925);
		AddSVPPoint(C_FTTOM*2000, C_FTTOM*4890);
		AddSVPPoint(C_FTTOM*3000, C_FTTOM*4872);
		AddSVPPoint(C_FTTOM*4000, C_FTTOM*4879);
		break;
	case 2: // north atlantic spring
		AddSVPPoint(C_FTTOM*0, C_FTTOM*4939);
		AddSVPPoint(C_FTTOM*300, C_FTTOM*4940);
		AddSVPPoint(C_FTTOM*1000, C_FTTOM*4934);
		AddSVPPoint(C_FTTOM*2000, C_FTTOM*4906);
		AddSVPPoint(C_FTTOM*3000, C_FTTOM*4886);
		AddSVPPoint(C_FTTOM*3500, C_FTTOM*4884);
		AddSVPPoint(C_FTTOM*4000, C_FTTOM*4887);
		break;
	case 3: // north atlantic summer
		AddSVPPoint(C_FTTOM*0, C_FTTOM*4960);
		AddSVPPoint(C_FTTOM*200, C_FTTOM*4938);
		AddSVPPoint(C_FTTOM*1000, C_FTTOM*4926);
		AddSVPPoint(C_FTTOM*2000, C_FTTOM*4894);
		AddSVPPoint(C_FTTOM*3000, C_FTTOM*4872);
		AddSVPPoint(C_FTTOM*4000, C_FTTOM*4879);
		break;
	case 4: // north atlantic autumn
		AddSVPPoint(C_FTTOM*0, C_FTTOM*4952);
		AddSVPPoint(C_FTTOM*200, C_FTTOM*4950);
		AddSVPPoint(C_FTTOM*1000, C_FTTOM*4938);
		AddSVPPoint(C_FTTOM*2000, C_FTTOM*4920);
		AddSVPPoint(C_FTTOM*3000, C_FTTOM*4890);
		AddSVPPoint(C_FTTOM*3600, C_FTTOM*4886);
		AddSVPPoint(C_FTTOM*4500, C_FTTOM*4890);
		break;
	default:
		wxASSERT(false); // bad id
		SetDefaultSVP();
		sonarTemplateId = -1;
		return;
		break;
	}

    AddSVPPoint(C_FTTOM*7750, C_FTTOM*4930);
	AddSVPPoint(C_FTTOM*9000, C_FTTOM*4945);
	AddSVPPoint(C_FTTOM*13000, C_FTTOM*5012);
	AddSVPPoint(C_FTTOM*17000, C_FTTOM*5079);

}

void tcSonarEnvironment::SetRayCoverage(float start_rad, float stop_rad, float step_rad)
{
    minAngle_rad = start_rad;
    maxAngle_rad = stop_rad;
    angleStep_rad = step_rad;
}

void tcSonarEnvironment::SetSeaState(unsigned int val)
{
    if (val > 7)
    {
        val = 7;
        wxASSERT(false);
    }

    seaState = val;

    noiseLevelSlope = 16.0;

    switch (seaState)
    {
    case 0: 
        noiseLevelBase = 3.0f*noiseLevelSlope + 44.0f;
        break;
    case 1: 
        noiseLevelBase = 3.0f*noiseLevelSlope + 53.0f;
        break;
    case 2: 
        noiseLevelBase = 3.0f*noiseLevelSlope + 58.0f;
        break;
    case 3: 
        noiseLevelBase = 3.0f*noiseLevelSlope + 62.0f;
        break;
    case 4: 
        noiseLevelBase = 3.0f*noiseLevelSlope + 65.0f;
        break;
    case 5: 
        noiseLevelBase = 3.0f*noiseLevelSlope + 67.0f;
        break;
    case 6: 
        noiseLevelBase = 3.0f*noiseLevelSlope + 69.0f;
        break;
    case 7: 
        noiseLevelBase = 3.0f*noiseLevelSlope + 73.0f;
        break;
    default:
        wxASSERT(false);
    }

}


void tcSonarEnvironment::SetSurfaceLoss(float val_dB)
{
    surfaceLossFactor = powf(10.0f, -0.1f*val_dB);
}

void tcSonarEnvironment::SetSVP(const std::vector<tcSonarEnvironment::SVPData>& svp_)
{
    svp = svp_;
}


void tcSonarEnvironment::Test()
{
    //osg::Timer_t t1 = osg::Timer::instance()->tick();

    float startDepth = 250.0f;
    float bottomDepth_m = 4000.0f;

    std::vector<tcSonarRay> beam;
    UpdateBeam(beam, startDepth, bottomDepth_m);

    //osg::Timer_t t2 = osg::Timer::instance()->tick();
    //double elapsedTime_ms = osg::Timer::instance()->delta_m(t1, t2);

    WriteBeamToCSV(beam, "beam.csv");
 
    float TL_dB = GetTL(1, 0, startDepth, 1000.0f, 300.0f, bottomDepth_m); // call once to calc beam

    // calculate TL vs. range
    //osg::Timer_t t3 = osg::Timer::instance()->tick();
    std::vector<float> range_vect;
    std::vector<float> loss_vect;
    for (float range_m=0; range_m<100000.0f; range_m+=250.0f)
    {
        TL_dB = GetTL(1, 0, startDepth, range_m, 50.0f, bottomDepth_m);

        range_vect.push_back(range_m);
        loss_vect.push_back(TL_dB);
    }
    //osg::Timer_t t4 = osg::Timer::instance()->tick();
    //double elapsedTime2_ms = osg::Timer::instance()->delta_m(t3, t4);

    WriteTLToCSV(range_vect, loss_vect, "TL.csv");

    wxString s;

    //s.Printf("Elapsed time for %d rays: %.1f ms (%.1f ms/ray)\n"
    //         "TL time for %d calcs: %.1f ms (%.1f ms/calc)",
    //         beam.size(), elapsedTime_ms, elapsedTime_ms / float(beam.size()),
    //         range_vect.size(), elapsedTime2_ms, elapsedTime2_ms / float(range_vect.size()));

    wxMessageBox(s);

}


/**
* Remove stale beams from beamCache
*/
void tcSonarEnvironment::Update(double t)
{
    if (t - lastUpdateTime < 61.0) return;
    lastUpdateTime = t;

    std::map<long, BeamData> temp;

    std::map<long, BeamData>::iterator iter = beamCache.begin();
    for (;iter != beamCache.end(); ++iter)
    {
        if ((t - iter->second.t_update) < 60.0)
        {
            temp.insert(*iter);
        }
    }

    beamCache = temp;
}

void tcSonarEnvironment::UpdateBeam(std::vector<tcSonarRay>& beam, float depth_m, float bottom_m)
{
    beam.clear();

    for (float angle=minAngle_rad; angle<=maxAngle_rad; angle += angleStep_rad)
    {
        beam.push_back(CalculateRay(depth_m, angle, bottom_m));
    }

}

void tcSonarEnvironment::UpdateLayerDepth()
{
    layerDepth_m = 9999.0f;

    for (size_t n=2; n<svp.size(); n++)
    {
        float speed_0 = svp[n-2].v_mps;
        float speed_1 = svp[n-1].v_mps;
        float speed_2 = svp[n].v_mps;

        if ((speed_0 < speed_1) && (speed_2 < speed_1))
        {
            layerDepth_m = svp[n-1].depth_m;
            return;
        }
    }
}

bool tcSonarEnvironment::UsingSimplePropagation() const
{
	return (tcOptions::Get()->useRayTracingSonar == 0) || (sonarTemplateId == 0);
}


/**
* @return true if SVP is valid, false otherwise
*/
bool tcSonarEnvironment::ValidateSVP()
{
    if (svp.size() < 2)
    {
        wxASSERT(false);
        fprintf(stderr, "tcSonarEnvironment::ValidateSVP - SVP must have at least 2 points\n");
        return false;
    }

    if (svp[0].depth_m != 0)
    {
        wxASSERT(false);
        fprintf(stderr, "tcSonarEnvironment::ValidateSVP - first SVP depth must be 0 (currently = %f)\n",
            svp[0].depth_m);
        return false;
    }

    for (size_t k=1; k<svp.size(); k++)
    {
        if (svp[k].depth_m <= svp[k-1].depth_m)
        {
            wxASSERT(false);
            fprintf(stderr, "tcSonarEnvironment::ValidateSVP - SVP depth must monotonically increase (%d,%f <= %d,%f)\n",
                k, svp[k].depth_m, k-1, svp[k-1].depth_m);
            return false;
        }
    }

    return true;    
}

void tcSonarEnvironment::WriteBeamToCSV(const std::vector<tcSonarRay>& beam, const std::string& fileName)
{
    tcFile log;
    log.Open(fileName.c_str(), tcFile::modeCreate | tcFile::modeWrite | tcFile::modeText);
    
    for (float range_km=0; range_km<100.0f; range_km+=0.25f)
    {
        wxString s;
        
        s.Printf("%.1f,", range_km);
        log.WriteString(s.c_str());

        for (size_t k=0; k<beam.size(); k++)
        {
            float reflectionLoss_dB;
            s.Printf("%.1f,", beam[k].CalculateDepth(1000.0f*range_km, reflectionLoss_dB));
            log.WriteString(s.c_str());
        }
        log.WriteString("\n");
    }
}

void tcSonarEnvironment::WriteTLToCSV(const std::vector<float>& range_vect, const std::vector<float>& loss_vect,
                                      const std::string& fileName)
{
    tcFile log;
    log.Open(fileName.c_str(), tcFile::modeCreate | tcFile::modeWrite | tcFile::modeText);
    
    for (size_t k=0; k<range_vect.size(); k++)
    {
        wxString s;
        
        s.Printf("%.1f,%.1f,%.1f,%.1f\n", range_vect[k], loss_vect[k], 10*log10(range_vect[k]), 30*log10(range_vect[k]));
        log.WriteString(s.c_str());
    }
}

/**
*
*/
tcSonarEnvironment::tcSonarEnvironment() :
    surfaceLossFactor(0.5f),
    bottomLossFactor(0.1f),
    minAngle_rad(-0.295f),
    maxAngle_rad(0.295f),
    angleStep_rad(0.02f),
    rayCount_dB(17.8f),
    depthUpdateThreshold_m(5.0f),
    fluxDecay(0.1f),
    seaState(0),
    lastUpdateTime(0),
    layerDepth_m(80.0f),
	sonarTemplateId(-1)
{
    SetDefaultSVP();
    SetSeaState(3);

	templateNames.clear();
	templateNames.push_back("Simple Propagation");
	templateNames.push_back("North Atlantic Winter");
	templateNames.push_back("North Atlantic Spring");
	templateNames.push_back("North Atlantic Summer");
	templateNames.push_back("North Atlantic Autumn");


    //Test();
}


/**
*
*/
tcSonarEnvironment::~tcSonarEnvironment() 
{
}