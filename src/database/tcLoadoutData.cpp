/**
**  @file tcLoadoutData.cpp
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

#include "tcLoadoutData.h"
#include "tcPlatformDBObject.h"
#include "tcDatabase.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


namespace database
{

    // validate that launcherLoadout and magazineLoadout are compatible with platform
    bool tcLoadoutData::ValidateLoadout(tcPlatformDBObject* platformData)
    {
        for (size_t n=0; n<launcherLoadout.size(); n++)
        {
            int launcherIdx = platformData->GetLauncherIndex(launcherLoadout[n].launcherId);

            size_t cap = platformData->GetItemCapacityForLauncher(size_t(launcherIdx), launcherLoadout[n].item);
            if (cap < launcherLoadout[n].quantity)
            {
                fprintf(stderr, "tcLoadoutData::ValidateLoadout - Invalid loadout %s for %s id %d %s x %d\n",
                    setupName.c_str(), platformData->mzClass.c_str(), launcherLoadout[n].launcherId,
                    launcherLoadout[n].item.c_str(), launcherLoadout[n].quantity);
                return false;
            }
       
        }

        return true;
    }


    tcLoadoutData::tcLoadoutData()
    {
    }

    tcLoadoutData::~tcLoadoutData()
    {
    }


}
