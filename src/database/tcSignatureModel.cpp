/**
**  @file tcSignatureModel.cpp
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


#include "tcSignatureModel.h"
#include "database/tcSqlReader.h"
#include <sstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;

namespace database
{


/**
* Adds sql column definitions to columnString. This is used for
* SQL create table command
*/
void tcSignatureModel::AddSqlColumns(std::string& columnString)
{
    columnString += "DatabaseClass primary key,";

    columnString += "Top_dB real,";
    columnString += "Bottom_dB real,";

    for (int n=0; n<=18; n++)
    {
        wxString s = wxString::Format("Aspect%d real", 10*n);
        if (n < 18) s += ",";

        columnString += s.c_str();
    }
}

/**
* @return detection modifier based on target aspect
*/
float tcSignatureModel::GetModifier(float az_deg, float el_deg) const
{
    float x = 0.1f * az_deg;
    float xfloor = floorf(x);
    float alpha = x - xfloor;
    float one_minus_alpha = 1.0f - alpha;

    int idx_1 = int(xfloor);
    if (idx_1 < 0) idx_1 += 36;
    else if (idx_1 > 35) idx_1 -= 36;

    int idx_2 = idx_1 + 1; // have wraparound value so this okay, [36] == [0]

    wxASSERT((idx_1 >= 0) && (idx_1 < 37));
    wxASSERT((idx_2 >= 0) && (idx_2 < 37));

    return one_minus_alpha*aspectModifier_dB[idx_1] + alpha*aspectModifier_dB[idx_2];

}

const char* tcSignatureModel::GetName() const
{
    return mzClass.c_str();
}

void tcSignatureModel::ReadSql(tcSqlReader& entry)
{
    mzClass = entry.GetString("DatabaseClass").c_str();

    topModifier_dB = entry.GetDouble("Top_dB");
    bottomModifier_dB = entry.GetDouble("Bottom_dB");

    for (int n=0; n<=18; n++)
    {
        wxString s = wxString::Format("Aspect%d", 10*n);

        aspectModifier_dB[n] = entry.GetDouble(s.c_str());
    }

    // fill in symmetric values
    for (int n=19; n<37; n++)
    {
        aspectModifier_dB[n] = aspectModifier_dB[36-n];
    }
    
}

void tcSignatureModel::WriteSql(std::string& valueString)
{
	std::stringstream s;

    s << "'" << mzClass.c_str() << "'";

	s << ",";

	s << topModifier_dB << ",";                 
	s << bottomModifier_dB << ",";        

    for (int n=0; n<=18; n++)
    {
        s << aspectModifier_dB[n];

        if (n < 18) s << ",";
    }
	
	valueString += s.str();
}


tcSignatureModel::tcSignatureModel()
:   topModifier_dB(0),
    bottomModifier_dB(0)
{
    for (size_t n=0; n<37; n++)
    {
        aspectModifier_dB[n] = 0;
    }
}

tcSignatureModel::tcSignatureModel(const tcSignatureModel& obj)
:   topModifier_dB(obj.topModifier_dB),
    bottomModifier_dB(obj.bottomModifier_dB)
{
    for (size_t n=0; n<37; n++)
    {
        aspectModifier_dB[n] = obj.aspectModifier_dB[n];
    }
}

tcSignatureModel::~tcSignatureModel() 
{
}

}
