/**  
**  @file tcOptions.h
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


#if !defined _TCOPTIONS_H_
#define _TCOPTIONS_H_

#include "wx/wx.h"
#include <string>
#include <vector>

class TiXmlDocument;
class TiXmlNode;



/**
* A singleton class for game configuration options
* Eventually the older binary options format will be replaced with
* XML. Currently XML can handle string options via GetOptionString
* and SetOptionString.
*
* TODO: fix option drawing
*/
class tcOptions  
{
public:

	enum 
	{
		N_OPTIONS = 128,       // max number of options
		N_OPTION_VALUES = 32 // max number of states for each option
	};
	class OptionInfo
	{
    public:
		int mnValue;
		enum teType 
		{
			OT_BOOLEAN,
			OT_RADIOBUTTON,
            OT_SLIDER
		} meType;
		int mnStateCount;
        std::vector<wxString> mzCaption;
		int* associatedInt; ///< variable to change to match mnValue

        float* associatedFloat;
        float floatVal;
        float floatMin;
        float floatMax;

        wxString xmlTag; ///< xml attribute for this option
        wxString group; ///< options group
        wxString description; ///< description for this option

        void Clear();

        OptionInfo();
        virtual ~OptionInfo();
	};

    // game play
    int mnCommandMode;
    int mnViewMode; ///<   "Omniscient view" "Omniscient, no sensor tags" "Legal view"
    int mnMapMode;
    int mbFillRangeCircles;
    int symbologyType; // 0 - 2525, 1 - NTDS computer, 2 - NTDS image
	/// 0 - own-alliance only, 1 - raw track data,  2 - add true pitch roll if available, 3 - use true data if avail
	int mn3DCheatMode; 
    int useRayTracingSonar; ///< 0 - simple spherical spreading, 1 - ray tracing
    int calcLineOfSight; ///< 0 - ignore terrain blockage, 1 - calculate terrain blockage
    int accurateCrossSection; ///< 0 - simple cross-section calc, 1 - collision testing
    int surfVelocityLeader; ///< 0 - fixed velocity leader, 1 - 1 min, 2 - 2 min, 3 - 5 min
    int airVelocityLeader; ///< 0 - fixed velocity leader, 1 - 30 sec, 2 - 1 min, 3 - 2 min
    int drawNavPointsMode; ///< 0 - hooked only, 1 - all friendly
    int fastAircraftReady; ///< 0 - normal (realistic), 1 - fast
    int fastLoad; ///< 0 - normal (realistic), 1 - fast
    int fastMaintenance; ///< 0 - normal (realistic), 1 - fast

    // sound
    int mbPlayMusic;
    int disableSound;
    float musicVolume;
    float effectVolume;

    // graphics
    int windowedMode; ///< 0 - not windowed, 1 - windowed
	int max3Drange; ///< 0 - 50 km, 1 - 75 km, 2 - 100 km
	int useFarSceneView; ///< 0 - only one scene view, 1 - use near and far scene views (help with z-fighting)
	int terrainShaderOn; ///< 1 - enable terrain elevation shader
    int waterShaderOn; ///< 1 - enable water shader
	int shadersOn; ///< 0 - 3D shaders disabled, 1 - shaders activated
	int shadowsOn; ///< 0 - 3D shadows disabled, 1 - shadows enabled
    int fogOn; ///<0 - fog disabled, 1 - fog enabled
    int vsync; ///< 0 - no vsync, 1 - vsync
    int antialiasing; ///< 0 - none, 1 - x4, 2 - x16
    int renderSurfaceLevel; ///< 0 - min, 1 - 3 more
    int textureFilterMode3d; ///< 0 - nearest point, 1 - bilinear, 2 - trilinear, 3 - anisotropic, 4 - flat cubic, 5 - gaussian cubic
    int textureFilterMode2d; ///< 0 - nearest point, 1 - bilinear, 2 - trilinear, 3 - anisotropic, 4 - flat cubic, 5 - gaussian cubic
    int autoScrollTheater; ///< 0 - don't autoscroll theater area, 1 - autoscroll theater area
    int mapSize; ///< 0 - 512x512, 1-1024x1024, 2-1024x2048, 3-2048x2048
    int minimal3D; ///< 0 - normal, 1 - use minimal 3D mode, loads models for bounding box only

    // lighting
    int manualLighting; ///< 0 - normal, 1 - manual
	int lightingMode; ///< 0 - normal, 1 - bump map, 2 - offset bump map, 3 - per vertex

    float sunAmbientRed;
    float sunAmbientGreen;
    float sunAmbientBlue;

    float sunDiffuseRed;
    float sunDiffuseGreen;
    float sunDiffuseBlue;

    float sunSpecularRed;
    float sunSpecularGreen;
    float sunSpecularBlue;

    // other 3D
    int manualFOV; ///< 0 - normal, 1 - manual
    float fov_deg;
    int adjustMaxView;
    float maxView_km;

    int adjustWater; ///< 0 - default, 1 - manual

    float waterReflectionRed;
    float waterReflectionGreen;
    float waterReflectionBlue;
    float waterReflectionAlpha;

    float waterRefractionRed;
    float waterRefractionGreen;
    float waterRefractionBlue;
    float waterRefractionAlpha;

    float waterCustomFresnel;

    // units
    int speedUnits; ///< 0 - m/s, 1 - kts, 2 - km/h, 3 - mph
    int altitudeUnits; ///< 0 - m, 1 - ft, 2 - yds
    int distanceUnits; ///< 0 - km, 1 - nmi, 2 - kyd
    int massUnits; ///< 0 - kg, 1 - lbs
    int natoNames; ///< 0 - no, 1 - use NATO/ASCC

    // events (sets max time acceleration)
    int eventContactAny; ///< 0 - pause, 1 - 1:1, 2 - 2:1, 3 - 4:1, 4 - 10:1, 5 - 30:1, 6: - no limit
    int eventContactAir;
    int eventContactMissile;
    int eventContactSurface;
    int eventContactSubmarine;
    int eventContactTorpedo;
    int eventContactGround;
    int eventDamage;
    int eventLaunchWeapon;
    int eventIdlePlatform;

    // interface
    int quickTarget; ///< 0 - right click, 1 - shift right click
    int edgeScroll;  ///< 0 - disable edge scroll, 1 - enable

    // multiplayer
    int syncClient; ///< 0 - disabled, 1 - enabled
    int sendTrackDetails; ///< 0 - disabled (conserve bw), 1 - send contributors and emitters
    int sensorUpdateRate; ///< 0 - 3 sec, 1 - 2 sec, 2 - 1 sec, 3 - 0.5 sec

    std::vector<OptionInfo> maOptionInfo;

    void AddOption(OptionInfo& oi);

    const char* GetOptionString(const char* optionName);
    bool OptionStringExists(const char* optionName) const;
    void SetOptionString(const char* optionName, const char* optionValue);

    void Synchronize();
    void Serialize(int abRead);

    static tcOptions* Get(); ///< accessor for singleton instance

private:   
    TiXmlDocument *optionsXml; ///< XML options file
    TiXmlNode* rootNode; ///< root node for XML options file

    int Init();
    void AddLightingOptions();

    tcOptions();
    ~tcOptions();
};

#endif 
