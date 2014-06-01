/**
**  @file tcSonarEnvironment.h
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

#ifndef _TCSONARENVIRONMENT_H_
#define _TCSONARENVIRONMENT_H_

#include "simmath.h"
#include <map>
#include <vector>

class tcSonarRay;
class tcGameStream;

/**
* Class for sonar propagation modeling
*
* Initial version
*    - Assume bottom is always at 500 m (no bathy data yet)
*    - Calculate rays for sonar every 10 m depth from 0 to 500 m (50 sets of rays)
*
* Singleton class
*/
class tcSonarEnvironment
{
    friend class tcSonarInfoPopup;
public:

    struct SVPData
    {
        float depth_m;
        float v_mps;
        float R_m; ///< radius of curvature for this segment
        float R2_m; ///< square of radius of curvature
    };

    static tcSonarEnvironment* Get(); ///< singleton instance accessor

    const std::vector<SVPData>& GetSVP() const;
    const wxString& GetSVPString() const;
    void SetSVP(const std::vector<SVPData>& svp_);
    void ClearSVP();
    void AddSVPPoint(float depth_m, float speed_mps);
    void EditSVPPoint(size_t idx, float depth_m, float speed_mps);
    void SetDefaultSVP();
	void SetTemplate(int id);
	int GetTemplate() const;
	unsigned int GetNumberTemplates() const;
	const std::string& GetTemplateName(unsigned int id) const;

    void SetSurfaceLoss(float val_dB);
    float GetSurfaceLossDB() const;
    void SetBottomLoss(float val_dB);
    float GetBottomLossDB() const;

    void SetSeaState(unsigned int val);
    unsigned int GetSeaState() const;

    float GetAmbientNL(float freq_Hz) const;

    float GetTL(long key, double t, float depth_m, float targetRange_m, float targetDepth_m, float bottomDepth_m);

    size_t GetBeamCount() const;

    void Clear();

    void Test();
    void Update(double t);

    tcGameStream& operator<<(tcGameStream& stream);
    tcGameStream& operator>>(tcGameStream& stream);

private:
    struct BeamData
    {
        double t_update; ///< last update time
        float depth_m; ///< depth that rays were calculated at
        std::vector<tcSonarRay> beam; ///< rays over range of angles = "beam"
    };

    std::map<long, BeamData> beamCache;

    float surfaceLossFactor; ///< loss from surface reflection, power factor, 0-1
    float bottomLossFactor; ///< loss from bottom reflection, power factor, 0-1

    float minAngle_rad; ///< min angle for ray calc
    float maxAngle_rad; ///< max angle for ray calc
    float angleStep_rad; ///< angle increment for ray calc


    float depthUpdateThreshold_m; ///< update rays if depth change exceeds
    const float fluxDecay;
    float rayCount_dB; ///< 10*log10(# rays per beam)

    std::vector<float> range_m; ///< ranges that TL is evaluated at

    std::vector<SVPData> svp; ///< sound velocity profile <depth [m], speed [m/s] points

    unsigned int seaState; ///< 0-7 sea state
    float noiseLevelBase;
    float noiseLevelSlope;
    float layerDepth_m; ///< for simple propagation model
	int sonarTemplateId; ///< -1 for no template, 0 or higher for template
	static std::vector<std::string> templateNames;

    double lastUpdateTime;

    const tcSonarRay& CalculateRay(float startDepth_m, float startAngle_rad, float bottom_m);
    float CalculateTL(const std::vector<tcSonarRay>& beam, float range_m, float depth_m) const;
    size_t GetSVPSegment(float depth, float angle) const;
    void UpdateBeam(std::vector<tcSonarRay>& beam, float depth_m, float bottom_m);
    void WriteBeamToCSV(const std::vector<tcSonarRay>& beam, const std::string& filename);
    void WriteTLToCSV(const std::vector<float>& range_vect, const std::vector<float>& loss_vect,
                                      const std::string& fileName);
    float GetTLSimple(float depth_m, float targetRange_m, float targetDepth_m, float bottom_m);
    void InitRayAngles();
    bool ValidateSVP();
    void UpdateLayerDepth();
    void SetRayCoverage(float start_rad, float stop_rad, float step_rad);
	bool UsingSimplePropagation() const;


    tcSonarEnvironment();
    ~tcSonarEnvironment();
};





#endif