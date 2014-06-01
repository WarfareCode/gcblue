/**
**  @file tcWeaponDamage.h
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

#ifndef _WEAPONDAMAGE_H_
#define _WEAPONDAMAGE_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <boost/shared_ptr.hpp>
#include <string>
#include "tcTableObject.h"
#include "sqlite/sqlite3x.hpp"

namespace database
{
	class tcSqlReader;

	/**
	*
	*/
    class tcWeaponDamage : public tcTableObject
	{
	public:
        float maxRange_m; ///< max range of weapon effect
        float probDetonate; ///< 0-1 probability of detonation
        bool isPenetration; ///< true if designed to explode after penetrating
        float blastCharge_kg;
        float fragCharge_kg;
        float radCharge_kg;
        float fragMetal_kg;
        float fragFragment_kg; ///< mass of individual fragment
        float fragSpread; ///< 0: every fragment hits target, 1: isotropic spread


		tcWeaponDamage();
		tcWeaponDamage(const tcWeaponDamage& obj);
        tcWeaponDamage(const std::string& s);
        tcWeaponDamage(sqlite3x::sqlite3_reader& reader);
		virtual ~tcWeaponDamage();

    private:
        

	};

} // namespace database

#endif

