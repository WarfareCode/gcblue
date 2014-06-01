/**
**  @file tcWeaponTester.h
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
#endif // _MSC_VER > 1000

#ifndef _TCWEAPONTESTER_H_
#define _TCWEAPONTESTER_H_

class tcGameObject;
class tcPlatformObject;

/**
* Singleton class
* Class for dev mode testing of weapon damage and behavior
* Interacts with simstate to automate launch of weapon vs target platform
*/
class tcWeaponTester
{

public:
    static tcWeaponTester* Get();

    tcGameObject* GetPlatform();
    void SetTarget(const std::string& s);
    void SetWeapon(const std::string& s);
    void SetQuantity(unsigned int n);
    void SetLaunchInterval(float t);
    void SetLaunchRange_km(float val);
    void SetLaunchAltitude_m(float val);

    void InitializePlatform();

    void Update();

private:
    std::string targetName;
    std::string weaponClass;
    unsigned int quantity; ///< remaining quantity to launch
    float launchInterval_s; ///< time interval between launches
    float launchRange_km; ///< range offset from target to launch at
    float launchAltitude_m;

    double lastLaunch_s; ///< sim time of last launch
    double lastUpdate_s;

    tcPlatformObject* ghost; ///< "ghost" parent that launches weapon


    tcWeaponTester();
    ~tcWeaponTester();
};

#endif
