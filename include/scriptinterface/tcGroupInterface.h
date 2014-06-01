/**  
**  @file tcGroupInterface.h
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


#ifndef __tcGroupInterface_h__
#define __tcGroupInterface_h__

#if _MSC_VER > 1000
#pragma once
#endif

#include <vector>
#include "tcScenarioInterface.h"

class tcSimState;
class tcCommandQueue;

namespace scriptinterface 
{
	class tcPlatformInterface;
    class tcWeaponInterface;
    class tcStringArray;

	/**
	* Class to control and build menus in python for groups of units
	*/
    class tcGroupInterface 
	{
    public:
		/// returns tcPlatformInterface object for unit <idx> in group
        tcPlatformInterface GetPlatformInterface(int idx);
		/// returns tcWeaponInterface object for unit <idx> in group
        tcWeaponInterface GetWeaponInterface(int idx);
		/// number of units in group, zero for none
		int GetUnitCount();
		/// unit id of unit <idx> in group, -1 for error
		long GetUnitId(int idx) const;
        bool IsPlatform(int idx) const; ///< @return true if this is a tcPlatformObject
        bool IsWeapon(int idx) const; ///< @return true if this is a tcWeaponObject
        /// return id of group member by name, or -1 if not found
        long LookupUnit(const std::string& name);
        int LookupUnitIdx(const std::string& name);
        /// vector of unit ids
        std::vector<long>& GetUnits();
		/// sets id vector for single unit in group
		void SetUnit(long unit);
		/// sets id vector for units in group
		void SetUnits(const std::vector<long>& units);
		/// release control of this group (multiplayer)
		void ReleaseControl();
		/// take control of this group (multiplayer)
		void TakeControl();

        void DeleteGroup();

        void RemoveUnit(long unit);

        void GetUserInput(std::string callback, std::string uitype);

        /// returns string array of tankers in group
        tcStringArray GetTankerList();

        tcScenarioInterface GetScenarioInterface();


        static void AttachSimState(tcSimState* ss) {simState = ss;}
        static void AttachCommandQueue(tcCommandQueue *cq) {mpCommandQueue = cq;}
        static void AttachScenarioInterface(tcScenarioInterface* si) {scenarioInterface = si;}

		tcGroupInterface();
		~tcGroupInterface();
    private:
        static tcSimState* simState;
        static tcCommandQueue *mpCommandQueue; // for requesting GUI commands
        static tcScenarioInterface* scenarioInterface; ///< to allow hooked units access in edit mode

		std::vector<long> groupUnits;
    };
}

#endif // __tcGroupInterface_h__

