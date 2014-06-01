/**
**  @file tcOptions.cpp
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

#include "tcOptions.h"
#include "tcFile.h"
#include "AError.h"
#include <stdio.h>
#include "common/tinyxml.h"




void tcOptions::OptionInfo::Clear()
{
    mnValue = 0;
    meType = OT_RADIOBUTTON;
    mnStateCount = 1;
    mzCaption.clear();
    associatedInt = 0;
    associatedFloat = 0;
    floatVal = 0;
    floatMin = 0;
    floatMax = 0;

    xmlTag.clear();
    group.clear();
}

tcOptions::OptionInfo::OptionInfo()
:   mnValue(0),
    meType(OT_RADIOBUTTON),
    mnStateCount(1),
    associatedInt(0),
    associatedFloat(0),
    floatVal(0),
    floatMin(0),
    floatMax(0)
{
}

tcOptions::OptionInfo::~OptionInfo()
{
}





/** 
* @return singleton instance 
*/
tcOptions* tcOptions::Get()
{
    static tcOptions instance;
    return &instance;
}

/******************************************************************************/
void tcOptions::AddLightingOptions()
{
    OptionInfo oi;

    oi.Clear();
    oi.meType = OptionInfo::OT_RADIOBUTTON;
    oi.mnStateCount = 2;
    oi.mnValue = 0;
    oi.associatedInt = &manualLighting;
    oi.mzCaption.push_back("Normal lighting");
    oi.mzCaption.push_back("Manual lighting");
    oi.xmlTag = "ManualLighting";
    oi.group = "Lighting";
    oi.description = "Enable Manual Lighting";
    AddOption(oi);

	oi.Clear();
    oi.meType = OptionInfo::OT_RADIOBUTTON;
    oi.mnStateCount = 4;
    oi.mnValue = 1;
    oi.associatedInt = &lightingMode;
    oi.mzCaption.push_back("Normal lighting");
    oi.mzCaption.push_back("Bump map");
	oi.mzCaption.push_back("Offset bump map");
	oi.mzCaption.push_back("Per vertex");
    oi.xmlTag = "BumpMapLighting";
    oi.group = "Lighting";
    oi.description = "Bumpmap Lighting Mode";
    AddOption(oi);

    oi.Clear();
    oi.meType = OptionInfo::OT_SLIDER;
    oi.mnStateCount = 1;
    oi.floatVal = 1.0f;
    oi.floatMin = 0;
    oi.floatMax = 1.0f;
    oi.associatedFloat = &sunAmbientRed;
    oi.mzCaption.push_back("Sun ambient R");
    oi.xmlTag = "SunAmbientR";
    oi.group = "Lighting";
    oi.description = "Sun Ambient R";
    AddOption(oi);

    oi.Clear();
    oi.meType = OptionInfo::OT_SLIDER;
    oi.mnStateCount = 1;
    oi.floatVal = 1.0f;
    oi.floatMin = 0;
    oi.floatMax = 1.0f;
    oi.associatedFloat = &sunAmbientGreen;
    oi.mzCaption.push_back("Sun ambient G");
    oi.xmlTag = "SunAmbientG";
    oi.group = "Lighting";
    oi.description = "Sun Ambient G";
    AddOption(oi);

    oi.Clear();
    oi.meType = OptionInfo::OT_SLIDER;
    oi.mnStateCount = 1;
    oi.floatVal = 1.0f;
    oi.floatMin = 0;
    oi.floatMax = 1.0f;
    oi.associatedFloat = &sunAmbientBlue;
    oi.mzCaption.push_back("Sun ambient B");
    oi.xmlTag = "SunAmbientB";
    oi.group = "Lighting";
    oi.description = "Sun Ambient B";
    AddOption(oi);


    oi.Clear();
    oi.meType = OptionInfo::OT_SLIDER;
    oi.mnStateCount = 1;
    oi.floatVal = 1.0f;
    oi.floatMin = 0;
    oi.floatMax = 1.0f;
    oi.associatedFloat = &sunDiffuseRed;
    oi.mzCaption.push_back("Sun diffuse R");
    oi.xmlTag = "SunDiffuseR";
    oi.group = "Lighting";
    oi.description = "Sun Diffuse R";
    AddOption(oi);

    oi.Clear();
    oi.meType = OptionInfo::OT_SLIDER;
    oi.mnStateCount = 1;
    oi.floatVal = 1.0f;
    oi.floatMin = 0;
    oi.floatMax = 1.0f;
    oi.associatedFloat = &sunDiffuseGreen;
    oi.mzCaption.push_back("Sun diffuse G");
    oi.xmlTag = "SunDiffuseG";
    oi.group = "Lighting";
    oi.description = "Sun Diffuse G";
    AddOption(oi);

    oi.Clear();
    oi.meType = OptionInfo::OT_SLIDER;
    oi.mnStateCount = 1;
    oi.floatVal = 1.0f;
    oi.floatMin = 0;
    oi.floatMax = 1.0f;
    oi.associatedFloat = &sunDiffuseBlue;
    oi.mzCaption.push_back("Sun diffuse B");
    oi.xmlTag = "SunDiffuseB";
    oi.group = "Lighting";
    oi.description = "Sun Diffuse B";
    AddOption(oi);


    oi.Clear();
    oi.meType = OptionInfo::OT_SLIDER;
    oi.mnStateCount = 1;
    oi.floatVal = 1.0f;
    oi.floatMin = 0;
    oi.floatMax = 1.0f;
    oi.associatedFloat = &sunSpecularRed;
    oi.mzCaption.push_back("Sun specular R");
    oi.xmlTag = "SunSpecularR";
    oi.group = "Lighting";
    oi.description = "Sun Specular R";
    AddOption(oi);

    oi.Clear();
    oi.meType = OptionInfo::OT_SLIDER;
    oi.mnStateCount = 1;
    oi.floatVal = 1.0f;
    oi.floatMin = 0;
    oi.floatMax = 1.0f;
    oi.associatedFloat = &sunSpecularGreen;
    oi.mzCaption.push_back("Sun specular G");
    oi.xmlTag = "SunSpecularG";
    oi.group = "Lighting";
    oi.description = "Sun Specular G";
    AddOption(oi);

    oi.Clear();
    oi.meType = OptionInfo::OT_SLIDER;
    oi.mnStateCount = 1;
    oi.floatVal = 1.0f;
    oi.floatMin = 0;
    oi.floatMax = 1.0f;
    oi.associatedFloat = &sunSpecularBlue;
    oi.mzCaption.push_back("Sun specular B");
    oi.xmlTag = "SunSpecularB";
    oi.group = "Lighting";
    oi.description = "Sun Specular B";
    AddOption(oi);



    oi.Clear();
    oi.meType = OptionInfo::OT_RADIOBUTTON;
    oi.mnStateCount = 2;
    oi.mnValue = 0;
    oi.associatedInt = &adjustWater;
    oi.mzCaption.push_back("Default water color");
    oi.mzCaption.push_back("Adjust water color");
    oi.xmlTag = "AdjustWaterColor";
    oi.group = "Water";
    oi.description = "Water Color";
    AddOption(oi);


    oi.Clear();
    oi.meType = OptionInfo::OT_SLIDER;
    oi.mnStateCount = 1;
    oi.floatVal = 1.0f;
    oi.floatMin = 0;
    oi.floatMax = 1.0f;
    oi.associatedFloat = &waterReflectionRed;
    oi.mzCaption.push_back("Water reflection R");
    oi.xmlTag = "WaterReflectionR";
    oi.group = "Water";
    oi.description = "Water Reflection R";
    AddOption(oi);

    oi.Clear();
    oi.meType = OptionInfo::OT_SLIDER;
    oi.mnStateCount = 1;
    oi.floatVal = 1.0f;
    oi.floatMin = 0;
    oi.floatMax = 1.0f;
    oi.associatedFloat = &waterReflectionGreen;
    oi.mzCaption.push_back("Water reflection G");
    oi.xmlTag = "WaterReflectionG";
    oi.group = "Water";
    oi.description = "Water Reflection G";
    AddOption(oi);

    oi.Clear();
    oi.meType = OptionInfo::OT_SLIDER;
    oi.mnStateCount = 1;
    oi.floatVal = 1.0f;
    oi.floatMin = 0;
    oi.floatMax = 1.0f;
    oi.associatedFloat = &waterReflectionBlue;
    oi.mzCaption.push_back("Water reflection B");
    oi.xmlTag = "WaterReflectionB";
    oi.group = "Water";
    oi.description = "Water Reflection B";
    AddOption(oi);

    oi.Clear();
    oi.meType = OptionInfo::OT_SLIDER;
    oi.mnStateCount = 1;
    oi.floatVal = 1.0f;
    oi.floatMin = 0;
    oi.floatMax = 1.0f;
    oi.associatedFloat = &waterReflectionAlpha;
    oi.mzCaption.push_back("Water reflection A");
    oi.xmlTag = "WaterReflectionA";
    oi.group = "Water";
    oi.description = "Water Reflection A";
    AddOption(oi);


    oi.Clear();
    oi.meType = OptionInfo::OT_SLIDER;
    oi.mnStateCount = 1;
    oi.floatVal = 1.0f;
    oi.floatMin = 0;
    oi.floatMax = 1.0f;
    oi.associatedFloat = &waterRefractionRed;
    oi.mzCaption.push_back("Water refraction R");
    oi.xmlTag = "WaterRefractionR";
    oi.group = "Water";
    oi.description = "Water Refraction R";
    AddOption(oi);

    oi.Clear();
    oi.meType = OptionInfo::OT_SLIDER;
    oi.mnStateCount = 1;
    oi.floatVal = 1.0f;
    oi.floatMin = 0;
    oi.floatMax = 1.0f;
    oi.associatedFloat = &waterRefractionGreen;
    oi.mzCaption.push_back("Water refraction G");
    oi.xmlTag = "WaterRefractionG";
    oi.group = "Water";
    oi.description = "Water Refraction G";
    AddOption(oi);

    oi.Clear();
    oi.meType = OptionInfo::OT_SLIDER;
    oi.mnStateCount = 1;
    oi.floatVal = 1.0f;
    oi.floatMin = 0;
    oi.floatMax = 1.0f;
    oi.associatedFloat = &waterRefractionBlue;
    oi.mzCaption.push_back("Water refraction B");
    oi.xmlTag = "WaterRefractionB";
    oi.group = "Water";
    oi.description = "Water Refraction B";
    AddOption(oi);

    oi.Clear();
    oi.meType = OptionInfo::OT_SLIDER;
    oi.mnStateCount = 1;
    oi.floatVal = 1.0f;
    oi.floatMin = 0;
    oi.floatMax = 1.0f;
    oi.associatedFloat = &waterRefractionAlpha;
    oi.mzCaption.push_back("Water refraction A");
    oi.xmlTag = "WaterRefractionA";
    oi.group = "Water";
    oi.description = "Water Refraction A";
    AddOption(oi);

    oi.Clear();
    oi.meType = OptionInfo::OT_SLIDER;
    oi.mnStateCount = 1;
    oi.floatVal = 0.5f;
    oi.floatMin = 0;
    oi.floatMax = 1.0f;
    oi.associatedFloat = &waterCustomFresnel;
    oi.mzCaption.push_back("Water fresnel");
    oi.xmlTag = "WaterFresnel";
    oi.group = "Water";
    oi.description = "Water Fresnel";
    AddOption(oi);



    // camera experimentation options
    oi.Clear();
    oi.meType = OptionInfo::OT_RADIOBUTTON;
    oi.mnStateCount = 2;
    oi.mnValue = 0;
    oi.associatedInt = &manualFOV;
    oi.mzCaption.push_back("Normal FOV");
    oi.mzCaption.push_back("Manual FOV ");
    oi.xmlTag = "ManualFOV";
    oi.group = "Other3D";
    oi.description = "Enable Manual FOV";
    AddOption(oi);

    oi.Clear();
    oi.meType = OptionInfo::OT_SLIDER;
    oi.mnStateCount = 1;
    oi.floatVal = 45.0;
    oi.floatMin = 5.0;
    oi.floatMax = 120.0f;
    oi.associatedFloat = &fov_deg;
    oi.mzCaption.push_back("Field of view");
    oi.xmlTag = "FOV";
    oi.group = "Other3D";
    oi.description = "Field of View";
    AddOption(oi);

    oi.Clear();
    oi.meType = OptionInfo::OT_RADIOBUTTON;
    oi.mnStateCount = 2;
    oi.mnValue = 0;
    oi.associatedInt = &adjustMaxView;
    oi.mzCaption.push_back("Fixed max view");
    oi.mzCaption.push_back("Adjust max view");
    oi.xmlTag = "AdjustMaxView";
    oi.group = "Other3D";
    oi.description = "Adjust Max View";
    AddOption(oi);

    oi.Clear();
    oi.meType = OptionInfo::OT_SLIDER;
    oi.mnStateCount = 1;
    oi.floatVal = 45.0;
    oi.floatMin = 5.0;
    oi.floatMax = 500.0f;
    oi.associatedFloat = &maxView_km;
    oi.mzCaption.push_back("Max view [km]");
    oi.xmlTag = "MaxView";
    oi.group = "Other3D";
    oi.description = "Max View [km]";
    AddOption(oi);







}


int tcOptions::Init() 
{
    OptionInfo oi;
    oi.Clear();
    oi.meType = OptionInfo::OT_RADIOBUTTON;
    oi.mnStateCount = 3;
    oi.mnValue = 2;
    oi.associatedInt = &mnViewMode;
    oi.mzCaption.push_back("Omniscient view");
    oi.mzCaption.push_back("Omniscient, no sensor tags");
    oi.mzCaption.push_back("Legal view");
    oi.xmlTag = "ViewMode";
    oi.group = "Game";
    oi.description = "View Mode";
    AddOption(oi);

    oi.Clear();
    oi.meType = OptionInfo::OT_RADIOBUTTON;
    oi.mnStateCount = 2;
    oi.mnValue = 1;
    oi.associatedInt = &mnCommandMode;
    oi.mzCaption.push_back("Control all");
    oi.mzCaption.push_back("Legal control (alliance only)");
    oi.xmlTag = "CommandMode";
    oi.group = "Game";
    oi.description = "Command Mode";
    AddOption(oi);

    oi.Clear();
    oi.meType = OptionInfo::OT_RADIOBUTTON;
    oi.mnStateCount = 3;
    oi.mnValue = 1;
    oi.associatedInt = &mnMapMode;
    oi.mzCaption.push_back("Copper-Blue Map");
    oi.mzCaption.push_back("Yellow-Blue Map");
    oi.mzCaption.push_back("Black-Blue Map");
    oi.xmlTag = "MapMode";
    oi.group = "Game";
    oi.description = "Map Mode";
    AddOption(oi);

    oi.Clear();
    oi.meType = OptionInfo::OT_RADIOBUTTON;
    oi.mnStateCount = 2;
    oi.mnValue = 0;
    oi.associatedInt = &mbFillRangeCircles;
    oi.mzCaption.push_back("Circle range regions");
    oi.mzCaption.push_back("Filled range regions");
    oi.xmlTag = "FillRangeCircles";
    oi.group = "Game";
    oi.description = "Fill Range Circles";
    AddOption(oi);

    oi.Clear();
    oi.meType = OptionInfo::OT_RADIOBUTTON;
    oi.mnStateCount = 2;
    oi.mnValue = 0;
    oi.associatedInt = &symbologyType;
    oi.mzCaption.push_back("Icon (2525B) symbols");
    oi.mzCaption.push_back("NTDS symbols");
    oi.xmlTag = "SymbologyType";
    oi.group = "Game";
    oi.description = "Symbology";
    AddOption(oi);

    oi.Clear();
    oi.meType = OptionInfo::OT_RADIOBUTTON;
    oi.mnStateCount = 4;
    oi.mnValue = 1;
    oi.associatedInt = &mn3DCheatMode;
    oi.mzCaption.push_back("Own-alliance 3D only");
    oi.mzCaption.push_back("Track 3D");
    oi.mzCaption.push_back("Track 3D+");
    oi.mzCaption.push_back("Cheat");
    oi.xmlTag = "CheatMode3D";
    oi.group = "Game";
    oi.description = "3D Cheat Mode";
    AddOption(oi);

    oi.Clear();
    oi.meType = OptionInfo::OT_RADIOBUTTON;
    oi.mnStateCount = 2;
    oi.mnValue = 1;
    oi.associatedInt = &useRayTracingSonar;
    oi.mzCaption.push_back("Simple sonar propagation");
    oi.mzCaption.push_back("Use ray tracing");
    oi.xmlTag = "SonarRayTracingEnabled";
    oi.group = "Game";
    oi.description = "Sonar Ray Tracing";
    AddOption(oi);

    oi.Clear();
    oi.meType = OptionInfo::OT_RADIOBUTTON;
    oi.mnStateCount = 2;
    oi.mnValue = 1;
    oi.associatedInt = &calcLineOfSight;
    oi.mzCaption.push_back("Sensors ignore terrain");
    oi.mzCaption.push_back("Allow terrain masking");
    oi.xmlTag = "TerrainMaskingEnabled";
    oi.group = "Game";
    oi.description = "Sensor Terrain Masking";
    AddOption(oi);

    oi.Clear();
    oi.meType = OptionInfo::OT_RADIOBUTTON;
    oi.mnStateCount = 2;
    oi.mnValue = 0;
    oi.associatedInt = &accurateCrossSection;
    oi.mzCaption.push_back("Simple cross-sections");
    oi.mzCaption.push_back("Enhanced accuracy");
    oi.xmlTag = "AccurateCrossSectionEnabled";
    oi.group = "Game";
    oi.description = "Damage Cross-Section Model";
    AddOption(oi);

    oi.Clear();
    oi.meType = OptionInfo::OT_RADIOBUTTON;
    oi.mnStateCount = 4;
    oi.mnValue = 3;
    oi.associatedInt = &surfVelocityLeader;
    oi.mzCaption.push_back("Non-air velocity leader fixed");
    oi.mzCaption.push_back("1 min");
    oi.mzCaption.push_back("2 min");
    oi.mzCaption.push_back("5 min");
    oi.xmlTag = "SurfVelocityLeader";
    oi.group = "Game";
    oi.description = "Non-Air Velocity Leader";
    AddOption(oi);

    oi.Clear();
    oi.meType = OptionInfo::OT_RADIOBUTTON;
    oi.mnStateCount = 4;
    oi.mnValue = 2;
    oi.associatedInt = &airVelocityLeader;
    oi.mzCaption.push_back("Air velocity leader fixed");
    oi.mzCaption.push_back("30 s");
    oi.mzCaption.push_back("1 min");
    oi.mzCaption.push_back("2 min");
    oi.xmlTag = "AirVelocityLeader";
    oi.group = "Game";
    oi.description = "Air Velocity Leader";
    AddOption(oi);

    oi.Clear();
    oi.meType = OptionInfo::OT_RADIOBUTTON;
    oi.mnStateCount = 2;
    oi.mnValue = 0;
    oi.associatedInt = &drawNavPointsMode;
    oi.mzCaption.push_back("Hooked platform waypoints");
    oi.mzCaption.push_back("All friendly waypoints");
    oi.xmlTag = "DrawNavPointsMode";
    oi.group = "Game";
    oi.description = "Waypoint Display";
    AddOption(oi);

    oi.Clear();
    oi.meType = OptionInfo::OT_RADIOBUTTON;
    oi.mnStateCount = 2;
    oi.mnValue = 0;
    oi.associatedInt = &fastAircraftReady;
    oi.mzCaption.push_back("Realistic aircraft ready times");
    oi.mzCaption.push_back("Fast ready");
    oi.xmlTag = "FastAircraftReady";
    oi.group = "Game";
    oi.description = "Aircraft Ready Times";
    AddOption(oi);

    oi.Clear();
    oi.meType = OptionInfo::OT_RADIOBUTTON;
    oi.mnStateCount = 2;
    oi.mnValue = 0;
    oi.associatedInt = &fastMaintenance;
    oi.mzCaption.push_back("Realistic aircraft maintenance times");
    oi.mzCaption.push_back("Fast maintenance");
    oi.xmlTag = "FastMaintenance";
    oi.group = "Game";
    oi.description = "Aircraft Maintenance Times";
    AddOption(oi);

    oi.Clear();
    oi.meType = OptionInfo::OT_RADIOBUTTON;
    oi.mnStateCount = 2;
    oi.mnValue = 0;
    oi.associatedInt = &fastLoad;
    oi.mzCaption.push_back("Realistic load times");
    oi.mzCaption.push_back("Fast load");
    oi.xmlTag = "FastLoad";
    oi.group = "Game";
    oi.description = "Equipment Load Times";
    AddOption(oi);



    oi.Clear();
    oi.meType = OptionInfo::OT_RADIOBUTTON;
    oi.mnStateCount = 2;
    oi.mnValue = 0;
    oi.associatedInt = &disableSound;
    oi.mzCaption.push_back("Sound Enabled");
    oi.mzCaption.push_back("Sound Disabled");
    oi.xmlTag = "SoundDisabled";
    oi.group = "Sound";
    oi.description = "Sound Enable";
    AddOption(oi);

    oi.Clear();
    oi.meType = OptionInfo::OT_RADIOBUTTON;
    oi.mnStateCount = 2;
    oi.mnValue = 0;
    oi.associatedInt = &mbPlayMusic;
    oi.mzCaption.push_back("Music OFF");
    oi.mzCaption.push_back("Music ON");
    oi.xmlTag = "MusicEnabled";
    oi.group = "Sound";
    oi.description = "Music Enable";
    AddOption(oi);

    oi.Clear();
    oi.meType = OptionInfo::OT_SLIDER;
    oi.mnStateCount = 1;
    oi.mnValue = 0;
    oi.associatedInt = 0;
    oi.associatedFloat = &musicVolume;
    oi.floatVal = 0.5;
    oi.floatMin = 0;
    oi.floatMax = 1;
    oi.mzCaption.push_back("Music Volume");
    oi.xmlTag = "MusicVolume";
    oi.group = "Sound";
    oi.description = "Music Volume";
    AddOption(oi);

    oi.Clear();
    oi.meType = OptionInfo::OT_SLIDER;
    oi.mnStateCount = 1;
    oi.mnValue = 0;
    oi.associatedInt = 0;
    oi.associatedFloat = &effectVolume;
    oi.floatVal = 1.0;
    oi.floatMin = 0;
    oi.floatMax = 1;
    oi.mzCaption.push_back("Effects Volume");
    oi.xmlTag = "EffectVolume";
    oi.group = "Sound";
    oi.description = "Sound Effects Volume";
    AddOption(oi);


    oi.Clear();
    oi.meType = OptionInfo::OT_RADIOBUTTON;
    oi.mnStateCount = 2;
    oi.mnValue = 0;
    oi.associatedInt = &windowedMode;
    oi.mzCaption.push_back("Full screen");
    oi.mzCaption.push_back("Windowed");
    oi.xmlTag = "WindowedMode";
    oi.group = "Graphics";
    oi.description = "Windowed Mode";
    AddOption(oi);


    oi.Clear();
    oi.meType = OptionInfo::OT_RADIOBUTTON;
    oi.mnStateCount = 3;
    oi.mnValue = 0;
    oi.associatedInt = &max3Drange;
    oi.mzCaption.push_back("50 km 3D range");
    oi.mzCaption.push_back("75 km 3D range");
    oi.mzCaption.push_back("100 km 3D range");
    oi.xmlTag = "Max3DRange";
    oi.group = "Graphics";
    oi.description = "Maximum 3D Range";
    AddOption(oi);

    //oi.Clear();
    //oi.meType = OptionInfo::OT_RADIOBUTTON;
    //oi.mnStateCount = 2;
    //oi.mnValue = 1;
    //oi.associatedInt = &terrainShaderOn;
    //oi.mzCaption.push_back("Terrain shader OFF");
    //oi.mzCaption.push_back("Terrain shader ON");
    //oi.xmlTag = "TerrainShaderOn";
    //oi.group = "Graphics";
    //AddOption(oi);

    oi.Clear();
    oi.meType = OptionInfo::OT_RADIOBUTTON;
    oi.mnStateCount = 2;
    oi.mnValue = 1;
    oi.associatedInt = &shadersOn;
    oi.mzCaption.push_back("Shaders OFF");
    oi.mzCaption.push_back("Shaders ON");
    oi.xmlTag = "ShadersEnabled";
    oi.group = "Graphics";
    oi.description = "3D Shader Enable";
    AddOption(oi);


    oi.Clear();
    oi.meType = OptionInfo::OT_RADIOBUTTON;
    oi.mnStateCount = 2;
    oi.mnValue = 1;
    oi.associatedInt = &waterShaderOn;
    oi.mzCaption.push_back("Water shader OFF");
    oi.mzCaption.push_back("Water shader ON");
    oi.xmlTag = "WaterShaderOn";
    oi.group = "Graphics";
    oi.description = "Water Shader Enable";
    AddOption(oi);


    oi.Clear();
    oi.meType = OptionInfo::OT_RADIOBUTTON;
    oi.mnStateCount = 2;
    oi.mnValue = 0;
    oi.associatedInt = &shadowsOn;
    oi.mzCaption.push_back("Shadows OFF");
    oi.mzCaption.push_back("Shadows ON");
    oi.xmlTag = "ShadowsEnabled";
    oi.group = "Graphics";
    oi.description = "3D Shadows Enable";
    AddOption(oi);


    oi.Clear();
    oi.meType = OptionInfo::OT_RADIOBUTTON;
    oi.mnStateCount = 2;
    oi.mnValue = 1;
    oi.associatedInt = &fogOn;
    oi.mzCaption.push_back("Fog OFF");
    oi.mzCaption.push_back("Fog ON");
    oi.xmlTag = "FogEnabled";
    oi.group = "Graphics";
    oi.description = "Fog Enable";
    AddOption(oi);


    oi.Clear();
    oi.meType = OptionInfo::OT_RADIOBUTTON;
    oi.mnStateCount = 2;
    oi.mnValue = 1;
    oi.associatedInt = &useFarSceneView;
    oi.mzCaption.push_back("Faster sceneview");
    oi.mzCaption.push_back("Reduce z-fighting");
    oi.xmlTag = "ReduceZFighting";
    oi.group = "Graphics";
    oi.description = "Z-Fighting Mode";
    AddOption(oi);

    oi.Clear();
    oi.meType = OptionInfo::OT_RADIOBUTTON;
    oi.mnStateCount = 2;
    oi.mnValue = 0;
    oi.associatedInt = &useFarSceneView;
    oi.mzCaption.push_back("Vsync disabled");
    oi.mzCaption.push_back("Vsync enabled");
    oi.xmlTag = "Vsync";
    oi.group = "Graphics";
    oi.description = "Vsync Enable";
    AddOption(oi);

    oi.Clear();
    oi.meType = OptionInfo::OT_RADIOBUTTON;
    oi.mnStateCount = 3;
    oi.mnValue = 0;
    oi.associatedInt = &useFarSceneView;
    oi.mzCaption.push_back("No antialiasing");
    oi.mzCaption.push_back("x4");
    oi.mzCaption.push_back("x16");
    oi.xmlTag = "Antialiasing";
    oi.group = "Graphics";
    oi.description = "Antialiasing Level";
    AddOption(oi);

    oi.Clear();
    oi.meType = OptionInfo::OT_RADIOBUTTON;
    oi.mnStateCount = 3;
    oi.mnValue = 1;
    oi.associatedInt = &renderSurfaceLevel;
    oi.mzCaption.push_back("RS min");
    oi.mzCaption.push_back("RS norm");
    oi.mzCaption.push_back("RS fast");
    oi.xmlTag = "RenderSurface";
    oi.group = "Graphics";
    oi.description = "Render Surface Caching";
    AddOption(oi);

    oi.Clear();
    oi.meType = OptionInfo::OT_RADIOBUTTON;
    oi.mnStateCount = 6;
    oi.mnValue = 2;
    oi.associatedInt = &textureFilterMode3d;
    oi.mzCaption.push_back("near");
    oi.mzCaption.push_back("bilin");
    oi.mzCaption.push_back("trilin");
    oi.mzCaption.push_back("aniso");
    oi.mzCaption.push_back("flat cub");
    oi.mzCaption.push_back("gauss cub");
    oi.xmlTag = "TextureFilter3d";
    oi.group = "Graphics";
    oi.description = "3D Texture Filtering";
    AddOption(oi);

    oi.Clear();
    oi.meType = OptionInfo::OT_RADIOBUTTON;
    oi.mnStateCount = 6;
    oi.mnValue = 0;
    oi.associatedInt = &textureFilterMode2d;
    oi.mzCaption.push_back("near");
    oi.mzCaption.push_back("bilin");
    oi.mzCaption.push_back("trilin");
    oi.mzCaption.push_back("aniso");
    oi.mzCaption.push_back("flat cub");
    oi.mzCaption.push_back("gauss cub");
    oi.xmlTag = "TextureFilter2d";
    oi.group = "Graphics";
    oi.description = "2D Texture Filtering";
    AddOption(oi);

    oi.Clear();
    oi.meType = OptionInfo::OT_RADIOBUTTON;
    oi.mnStateCount = 2;
    oi.mnValue = 1;
    oi.associatedInt = &autoScrollTheater;
    oi.mzCaption.push_back("Autoscroll theater OFF");
    oi.mzCaption.push_back("Autoscroll theater ON");
    oi.xmlTag = "AutoScrollTheater";
    oi.group = "Graphics";
    oi.description = "Auto Map Scroll";
    AddOption(oi);

    oi.Clear();
    oi.meType = OptionInfo::OT_RADIOBUTTON;
    oi.mnStateCount = 4;
    oi.mnValue = 2;
    oi.associatedInt = &mapSize;
    oi.mzCaption.push_back("512x512");
    oi.mzCaption.push_back("1024x1024");
    oi.mzCaption.push_back("2048x2048");
    oi.mzCaption.push_back("2048x4096");
    oi.xmlTag = "TacticalMapSize";
    oi.group = "Graphics";
    oi.description = "Tactical Map Size";
    AddOption(oi);

    oi.Clear();
    oi.meType = OptionInfo::OT_RADIOBUTTON;
    oi.mnStateCount = 2;
    oi.mnValue = 0;
    oi.associatedInt = &minimal3D;
    oi.mzCaption.push_back("Normal 3D");
    oi.mzCaption.push_back("Minimal 3D mode");
    oi.xmlTag = "Minimal3D";
    oi.group = "Graphics";
    oi.description = "Minimal 3D Mode";
    AddOption(oi);
    
    // lighting

    AddLightingOptions();


    //int speedUnits; ///< 0 - m/s, 1 - kts, 2 - km/h, 3 - mph
    //int altitudeUnits; ///< 0 - m, 1 - ft, 2 - yds
    //int distanceUnits; ///< 0 - km, 1 - nmi, 2 - kyd


    oi.Clear();
    oi.meType = OptionInfo::OT_RADIOBUTTON;
    oi.mnStateCount = 4;
    oi.mnValue = 1;
    oi.associatedInt = &speedUnits;
    oi.mzCaption.push_back("Speed m/s");
    oi.mzCaption.push_back("Speed kts");
    oi.mzCaption.push_back("Speed km/h");
    oi.mzCaption.push_back("Speed mph");
    oi.xmlTag = "SpeedUnits";
    oi.group = "Units";
    oi.description = "Speed Units";
    AddOption(oi);

    oi.Clear();
    oi.meType = OptionInfo::OT_RADIOBUTTON;
    oi.mnStateCount = 3;
    oi.mnValue = 0;
    oi.associatedInt = &altitudeUnits;
    oi.mzCaption.push_back("Altitude m");
    oi.mzCaption.push_back("Altitude ft");
    oi.mzCaption.push_back("Altitude yds");
    oi.xmlTag = "AltitudeUnits";
    oi.group = "Units";
    oi.description = "Altitude Units";
    AddOption(oi);

    oi.Clear();
    oi.meType = OptionInfo::OT_RADIOBUTTON;
    oi.mnStateCount = 3;
    oi.mnValue = 0;
    oi.associatedInt = &distanceUnits;
    oi.mzCaption.push_back("Distance km");
    oi.mzCaption.push_back("Distance nmi");
    oi.mzCaption.push_back("Distance kyd");
    oi.xmlTag = "DistanceUnits";
    oi.group = "Units";
    oi.description = "Distance Units";
    AddOption(oi);

    oi.Clear();
    oi.meType = OptionInfo::OT_RADIOBUTTON;
    oi.mnStateCount = 2;
    oi.mnValue = 0;
    oi.associatedInt = &massUnits;
    oi.mzCaption.push_back("Mass kg");
    oi.mzCaption.push_back("Mass lbs");
    oi.xmlTag = "MassUnits";
    oi.group = "Units";
    oi.description = "Mass Units";
    AddOption(oi);

    oi.Clear();
    oi.meType = OptionInfo::OT_RADIOBUTTON;
    oi.mnStateCount = 2;
    oi.mnValue = 0;
    oi.associatedInt = &natoNames;
    oi.mzCaption.push_back("Use primary platform names");
    oi.mzCaption.push_back("Use NATO/ASCC names");
    oi.xmlTag = "NATONames";
    oi.group = "Units";
    oi.description = "Platform Name System";
    AddOption(oi);


    oi.Clear();
    oi.meType = OptionInfo::OT_RADIOBUTTON;
    oi.mnStateCount = 7;
    oi.mnValue = 6;
    oi.associatedInt = &eventContactAny;
    oi.mzCaption.push_back("Pause");
    oi.mzCaption.push_back("1:1");
    oi.mzCaption.push_back("2:1");
    oi.mzCaption.push_back("4:1");
    oi.mzCaption.push_back("10:1");
    oi.mzCaption.push_back("30:1");
    oi.mzCaption.push_back("No limit");
    oi.xmlTag = "EventContactAny";
    oi.group = "Events";
    oi.description = "New Contact All";
    AddOption(oi);

    oi.Clear();
    oi.meType = OptionInfo::OT_RADIOBUTTON;
    oi.mnStateCount = 7;
    oi.mnValue = 6;
    oi.associatedInt = &eventContactAir;
    oi.mzCaption.push_back("Pause");
    oi.mzCaption.push_back("1:1");
    oi.mzCaption.push_back("2:1");
    oi.mzCaption.push_back("4:1");
    oi.mzCaption.push_back("10:1");
    oi.mzCaption.push_back("30:1");
    oi.mzCaption.push_back("No limit");
    oi.xmlTag = "EventContactAir";
    oi.group = "Events";
    oi.description = "New Air Contact";
    AddOption(oi);

    oi.Clear();
    oi.meType = OptionInfo::OT_RADIOBUTTON;
    oi.mnStateCount = 7;
    oi.mnValue = 6;
    oi.associatedInt = &eventContactMissile;
    oi.mzCaption.push_back("Pause");
    oi.mzCaption.push_back("1:1");
    oi.mzCaption.push_back("2:1");
    oi.mzCaption.push_back("4:1");
    oi.mzCaption.push_back("10:1");
    oi.mzCaption.push_back("30:1");
    oi.mzCaption.push_back("No limit");
    oi.xmlTag = "EventContactMissile";
    oi.group = "Events";
    oi.description = "New Missile Contact";
    AddOption(oi);


    oi.Clear();
    oi.meType = OptionInfo::OT_RADIOBUTTON;
    oi.mnStateCount = 7;
    oi.mnValue = 6;
    oi.associatedInt = &eventContactSurface;
    oi.mzCaption.push_back("Pause");
    oi.mzCaption.push_back("1:1");
    oi.mzCaption.push_back("2:1");
    oi.mzCaption.push_back("4:1");
    oi.mzCaption.push_back("10:1");
    oi.mzCaption.push_back("30:1");
    oi.mzCaption.push_back("No limit");
    oi.xmlTag = "EventContactSurface";
    oi.group = "Events";
    oi.description = "New Surface Contact";
    AddOption(oi);


    oi.Clear();
    oi.meType = OptionInfo::OT_RADIOBUTTON;
    oi.mnStateCount = 7;
    oi.mnValue = 6;
    oi.associatedInt = &eventContactSubmarine;
    oi.mzCaption.push_back("Pause");
    oi.mzCaption.push_back("1:1");
    oi.mzCaption.push_back("2:1");
    oi.mzCaption.push_back("4:1");
    oi.mzCaption.push_back("10:1");
    oi.mzCaption.push_back("30:1");
    oi.mzCaption.push_back("No limit");
    oi.xmlTag = "EventContactSubmarine";
    oi.group = "Events";
    oi.description = "New Subsurface Contact";
    AddOption(oi);

    oi.Clear();
    oi.meType = OptionInfo::OT_RADIOBUTTON;
    oi.mnStateCount = 7;
    oi.mnValue = 6;
    oi.associatedInt = &eventContactTorpedo;
    oi.mzCaption.push_back("Pause");
    oi.mzCaption.push_back("1:1");
    oi.mzCaption.push_back("2:1");
    oi.mzCaption.push_back("4:1");
    oi.mzCaption.push_back("10:1");
    oi.mzCaption.push_back("30:1");
    oi.mzCaption.push_back("No limit");
    oi.xmlTag = "EventContactTorpedo";
    oi.group = "Events";
    oi.description = "New Torpedo Contact";
    AddOption(oi);


    oi.Clear();
    oi.meType = OptionInfo::OT_RADIOBUTTON;
    oi.mnStateCount = 7;
    oi.mnValue = 6;
    oi.associatedInt = &eventContactGround;
    oi.mzCaption.push_back("Pause");
    oi.mzCaption.push_back("1:1");
    oi.mzCaption.push_back("2:1");
    oi.mzCaption.push_back("4:1");
    oi.mzCaption.push_back("10:1");
    oi.mzCaption.push_back("30:1");
    oi.mzCaption.push_back("No limit");
    oi.xmlTag = "EventContactGround";
    oi.group = "Events";
    oi.description = "New Ground Contact";
    AddOption(oi);


    oi.Clear();
    oi.meType = OptionInfo::OT_RADIOBUTTON;
    oi.mnStateCount = 7;
    oi.mnValue = 6;
    oi.associatedInt = &eventDamage;
    oi.mzCaption.push_back("Pause");
    oi.mzCaption.push_back("1:1");
    oi.mzCaption.push_back("2:1");
    oi.mzCaption.push_back("4:1");
    oi.mzCaption.push_back("10:1");
    oi.mzCaption.push_back("30:1");
    oi.mzCaption.push_back("No limit");
    oi.xmlTag = "EventDamage";
    oi.group = "Events";
    oi.description = "New Damage Reported";
    AddOption(oi);

    oi.Clear();
    oi.meType = OptionInfo::OT_RADIOBUTTON;
    oi.mnStateCount = 7;
    oi.mnValue = 6;
    oi.associatedInt = &eventLaunchWeapon;
    oi.mzCaption.push_back("Pause");
    oi.mzCaption.push_back("1:1");
    oi.mzCaption.push_back("2:1");
    oi.mzCaption.push_back("4:1");
    oi.mzCaption.push_back("10:1");
    oi.mzCaption.push_back("30:1");
    oi.mzCaption.push_back("No limit");
    oi.xmlTag = "EventLaunchWeapon";
    oi.group = "Events";
    oi.description = "New Weapon Launch";
    AddOption(oi);

    oi.Clear();
    oi.meType = OptionInfo::OT_RADIOBUTTON;
    oi.mnStateCount = 7;
    oi.mnValue = 6;
    oi.associatedInt = &eventIdlePlatform;
    oi.mzCaption.push_back("Pause");
    oi.mzCaption.push_back("1:1");
    oi.mzCaption.push_back("2:1");
    oi.mzCaption.push_back("4:1");
    oi.mzCaption.push_back("10:1");
    oi.mzCaption.push_back("30:1");
    oi.mzCaption.push_back("No limit");
    oi.xmlTag = "EventIdlePlatform";
    oi.group = "Events";
    oi.description = "Idle Platform";
    AddOption(oi);



    // interface
    oi.Clear();
    oi.meType = OptionInfo::OT_RADIOBUTTON;
    oi.mnStateCount = 2;
    oi.mnValue = 0;
    oi.associatedInt = &quickTarget;
    oi.mzCaption.push_back("Right Click");
    oi.mzCaption.push_back("Shift+Right Click");
    oi.xmlTag = "QuickTarget";
    oi.group = "Interface";
    oi.description = "Quick Target Command";
    AddOption(oi);

    oi.Clear();
    oi.meType = OptionInfo::OT_RADIOBUTTON;
    oi.mnStateCount = 2;
    oi.mnValue = 1;
    oi.associatedInt = &edgeScroll;
    oi.mzCaption.push_back("Disable");
    oi.mzCaption.push_back("Enable");
    oi.xmlTag = "EdgeScroll";
    oi.group = "Interface";
    oi.description = "Edge Scrolling";
    AddOption(oi);



    oi.Clear();
    oi.meType = OptionInfo::OT_RADIOBUTTON;
    oi.mnStateCount = 2;
    oi.mnValue = 1;
    oi.associatedInt = &syncClient;
    oi.mzCaption.push_back("Disable client sync");
    oi.mzCaption.push_back("Enable client sync");
    oi.xmlTag = "SyncClient";
    oi.group = "Multiplayer";
    oi.description = "Client Synchronization";
    AddOption(oi);

    oi.Clear();
    oi.meType = OptionInfo::OT_RADIOBUTTON;
    oi.mnStateCount = 2;
    oi.mnValue = 0;
    oi.associatedInt = &sendTrackDetails;
    oi.mzCaption.push_back("Disable");
    oi.mzCaption.push_back("Enable");
    oi.xmlTag = "SendTrackDetails";
    oi.group = "Multiplayer";
    oi.description = "Send Emitter Info";
    AddOption(oi);

    oi.Clear();
    oi.meType = OptionInfo::OT_RADIOBUTTON;
    oi.mnStateCount = 4;
    oi.mnValue = 2;
    oi.associatedInt = &sensorUpdateRate;
    oi.mzCaption.push_back("3 sec");
    oi.mzCaption.push_back("2 sec");
    oi.mzCaption.push_back("1 sec");
    oi.mzCaption.push_back("0.5 sec");
    oi.xmlTag = "SensorUpdateRate";
    oi.group = "Multiplayer";
    oi.description = "Sensor Update Interval";
    AddOption(oi);


    Serialize(true); // read option state from file (options.dat)



    return true;
}

void tcOptions::AddOption(OptionInfo& oi) 
{
    if (maOptionInfo.size() >= N_OPTIONS) return; // no room for more options
    
    if (oi.associatedInt != 0) *oi.associatedInt = oi.mnValue;
    if (oi.associatedFloat != 0) *oi.associatedFloat = oi.floatVal;

    maOptionInfo.push_back(oi);

    //OptionInfo* poi;
    //poi = &maOptionInfo[mnNumOptions++];
    //poi->meType = oi.meType;
    //poi->mnStateCount = oi.mnStateCount;
    //poi->mnValue = oi.mnValue;
    //poi->associatedInt = oi.associatedInt;
    //if (poi->associatedInt != NULL) {*poi->associatedInt = poi->mnValue;}
    //for(int k=0;(k<poi->mnStateCount)&&(k<N_OPTION_VALUES);k++) 
    //{
    //    poi->mzCaption[k] = oi.mzCaption[k];
    //}
}

/**
* @return option string value for string option matching optionName
* if option is not found, adds option with value "default"
*/
const char* tcOptions::GetOptionString(const char* optionName)
{
    TiXmlNode* node = rootNode->FirstChild(optionName);
    if (!node)
    {
        node = rootNode->InsertEndChild(TiXmlElement(optionName));
    }

    TiXmlNode* child = node->FirstChild();
    if (!child)
    {
        child = node->InsertEndChild(TiXmlText("default"));
    }

    return child->Value();
}

/**
* @return true if option string is defined, false otherwise
*/
bool tcOptions::OptionStringExists(const char* optionName) const
{
    TiXmlNode* node = rootNode->FirstChild(optionName);

    return (node != 0);
}

/**
* Updates option string value, creating if necessary
*/
void tcOptions::SetOptionString(const char* optionName, const char* optionValue)
{
    TiXmlNode* node = rootNode->FirstChild(optionName);
    if (!node)
    {
        node = rootNode->InsertEndChild(TiXmlElement(optionName));
    }

    TiXmlNode* child = node->FirstChild();
    if (child)
    {
        child->SetValue(optionValue);
    }
    else
    {
        child = node->InsertEndChild(TiXmlText(optionValue));
    }

}

/**
* Serialize(true) to read, serialize(false) to write
*/
void tcOptions::Serialize(int abRead) 
{
    //tcFile file;
    bool bWrite = !abRead;
    //unsigned nReadCount;

    if (abRead) 
    { 
        // load options from XML file
        for (size_t k=0; k<maOptionInfo.size(); k++)
        {
            const char* xmlTag = maOptionInfo[k].xmlTag.c_str();
            if (TiXmlNode* node = rootNode->FirstChild(xmlTag))
            {
                if (TiXmlElement* elt = node->ToElement())
                {
                    if (maOptionInfo[k].meType != OptionInfo::OT_SLIDER)
                    {
                        elt->Attribute("Value", maOptionInfo[k].associatedInt);
                        maOptionInfo[k].mnValue = *maOptionInfo[k].associatedInt;
                    }
                    else
                    {
                        elt->Attribute("Value", maOptionInfo[k].associatedFloat);
                        maOptionInfo[k].floatVal = *maOptionInfo[k].associatedFloat;
                        maOptionInfo[k].floatVal = std::min(maOptionInfo[k].floatVal, 
                            maOptionInfo[k].floatMax);
                        maOptionInfo[k].floatVal = std::max(maOptionInfo[k].floatVal, 
                            maOptionInfo[k].floatMin);
                    }
                }
            }
            else
            {
                node = rootNode->InsertEndChild(TiXmlElement(xmlTag));
                if (TiXmlElement* elt = node->ToElement())
                {
                    if (maOptionInfo[k].meType != OptionInfo::OT_SLIDER)
                    {
                        elt->SetAttribute("Value", *maOptionInfo[k].associatedInt);
                    }
                    else
                    {
                        elt->SetAttribute("Value", *maOptionInfo[k].associatedFloat);
                    }
                }
            }

        }
    }

    if (bWrite) 
    {
        // write options to XML
        for (size_t k=0; k<maOptionInfo.size(); k++)
        {
            TiXmlNode* node = rootNode->FirstChild(maOptionInfo[k].xmlTag.c_str());
            if (TiXmlElement* elt = node->ToElement())
            {
                if (maOptionInfo[k].meType != OptionInfo::OT_SLIDER)
                {
                    elt->SetAttribute("Value", *maOptionInfo[k].associatedInt);
                }
                else
                {
                    elt->SetAttribute("Value", (float)(*maOptionInfo[k].associatedFloat));
                }
            }
        }


        if (optionsXml != 0)
        {
            optionsXml->SaveFile();
        }
        else
        {
            wxASSERT(false);
        }
    }
}

/**
* Call this after changing an option variable
*/
void tcOptions::Synchronize() 
{
    // section to force compatible settings
    //if (minimal3D)
    //{
    //    max3Drange = 0;
	   // useFarSceneView = 0;
	   // shadersOn = 0; 
	   // shadowsOn = 0;
    //    textureFilterMode3d = 0;
    //}

    // synch code
    for(size_t n=0; n<maOptionInfo.size(); n++) 
    {
        if (maOptionInfo[n].associatedInt != NULL) 
        {
            maOptionInfo[n].mnValue = *maOptionInfo[n].associatedInt;
        }
    }
}

/**
*
*/
tcOptions::tcOptions() 
{
    optionsXml = new TiXmlDocument("xml//options.xml");
    if (!optionsXml->LoadFile())
    {
        std::cout << "Created empty XML options file " << std::endl;
        optionsXml->SaveFile();
    }
    optionsXml->LoadFile();
    rootNode = optionsXml->FirstChild("Options");
    if (!rootNode)
    {
        rootNode = optionsXml->InsertEndChild(TiXmlElement("Options"));
    }

    Init(); // initializes binary options data
}


/**
*
*/
tcOptions::~tcOptions() 
{
    if (optionsXml)
    {
        optionsXml->SaveFile();
        delete optionsXml;
    }

}

