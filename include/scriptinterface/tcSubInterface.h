/**
**  @file tcSubInterface.h
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

#ifndef __tcSubInterface_h__
#define __tcSubInterface_h__

#if _MSC_VER > 1000
#pragma once
#endif

class tcMessageInterface;
class tcPlatformObject;
class tcSubObject;
class tcSimState;
class tcSound;
class tcSoundConsole;
class tcCommandQueue;


namespace scriptinterface {
	/**
	* Interface class for submarine vehicle interface. 
	*/
	class tcSubInterface 
	{
	public:
		/// 0 - 1 battery charge
		float GetBatteryFraction() const;
        /// max depth of this sub
        float GetMaxDepth() const;
        /// command depth to periscope depth
        void GoToPeriscopeDepth();
        /// true if at periscope depth
        bool IsAtPeriscopeDepth() const;
		/// true if this is a diesel-electric sub
		bool IsDieselElectric() const;
        /// true if periscope is raised
        bool IsPeriscopeRaised() const;
        /// true if radar mast is raised
        bool IsRadarMastRaised() const;
		/// true if snorkeling
		bool IsSnorkeling() const;
        /// true if this is a valid interface
        bool IsValid() const;
        /// lower the scope
        void LowerPeriscope();
        /// lower the radar mast
        void LowerRadarMast();
        /// raise the scope (must be at periscope depth or shallower)
        void RaisePeriscope();
        /// raise the radar mast (must be at periscope depth or shallower)
        void RaiseRadarMast();
		/// start or stop snorkeling (must be at periscope depth or shallower)
		void SetSnorkelState(bool state);

        float GetCavitatingSpeed(float depth_m) const;

        tcSubInterface();
		tcSubInterface(tcPlatformObject* obj);
		~tcSubInterface();

	private:
        static tcSound* sound;
        static tcSimState* simState;
        static tcMessageInterface* messageInterface;

		tcSubObject* subObj;
	};
}
#endif