/**  
**  @file tcWeaponInterface.h
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

#ifndef __TCWEAPONINTERFACE_H_
#define __TCWEAPONINTERFACE_H_


#if _MSC_VER > 1000
#pragma once
#endif 



#include <string>
#include <boost/python.hpp>
#include "tcScenarioInterface.h"

class tcSimState;
class tcSoundConsole;
class tcMapOverlay;
class tcWeaponObject;

using namespace boost::python;


namespace scriptinterface 
{
    /**
    * Interface for control of weapon through datalink
    */
    class tcWeaponInterface
    {
    public:        
        tcWeaponObject* weapon;
        static tcWeaponObject* static_weapon;
        
        // Interface class management functions
        static object GetInterface();
        static void SetObj(tcWeaponObject* obj) {static_weapon = obj;}

        void GetLocalObj() {weapon = static_weapon;}
        void SetWeapon(tcWeaponObject* obj) {weapon = obj;} ///< method to directly set local tcWeaponObject
        
        // Interface functions to be called through Python
        bool IsValid();
        std::string GetWeaponType();
        bool IsLinkActive();
        void UpdateTargetPosition(float lon_rad, float lat_rad);

        void DisplayMessage(const std::string& text);

		/// get unit name of platform
		std::string GetPlatformName();
		/// get database class name of platform
		std::string GetPlatformClass();
        /// get platform alliance
        unsigned int GetPlatformAlliance() const;
        float GetLongitude() const;
        float GetLatitude() const;
		float GetAltitude() const; 
		/// gets current platform speed in kts
		float GetSpeed(); 
		/// gets current heading in degrees
		float GetHeading(); 


        // mission edit mode only
		void DeletePlatform();
		/// move platform to new position [mission edit only]
		void MovePlatform(float afLon_rad, float afLat_rad);
		/// change name of platform [mission edit only]
		void RenamePlatform(const std::string& s);
        tcScenarioInterface GetScenarioInterface();

        static void AttachScenarioInterface(tcScenarioInterface* si) {scenarioInterface = si;}

        tcWeaponInterface();
        tcWeaponInterface(tcWeaponObject* weaponObject);
        virtual ~tcWeaponInterface();

    private:
        static tcScenarioInterface* scenarioInterface; ///< to allow hooked units access in edit mode

    };

}

#endif

