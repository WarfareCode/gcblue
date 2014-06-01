/**  
**  @file tcOOBView.cpp
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

#ifndef WX_PRECOMP
#include "wx/wx.h" 
#endif

#include "tcOOBView.h"
#include "tcTacticalMapView.h"
#include "tcSimState.h"
#include "tcSound.h"
#include "tcAirfieldObject.h"
#include "tcHeloObject.h"
#include "tcSubObject.h"
#include "tcGroundObject.h"
#include "tcGroundVehicleObject.h"
#include "tcSensorMap.h"
#include "tcSensorTrackIterator.h"
#include "tcScrollBar.h"
#include "ai/Brain.h"

BEGIN_EVENT_TABLE(tcOOBView, tcXmlWindow)
EVT_COMMAND(1, wxEVT_COMMAND_BUTTON_CLICKED, tcOOBView::SetDisplayOwn)
EVT_COMMAND(2, wxEVT_COMMAND_BUTTON_CLICKED, tcOOBView::SetDisplayTrack)
EVT_COMMAND(-1, wxEVT_COMMAND_SCROLLBAR_UPDATED, tcOOBView::OnScrollbarUpdated)
END_EVENT_TABLE()


#ifdef _DEBUG
#define new DEBUG_NEW
#endif 




tsOOBInfo& tsOOBInfo::operator= (const tsOOBInfo& rhs)
{
    mnID = rhs.mnID;
    mzName = rhs.mzName;
    mnLeaderID = rhs.mnLeaderID;
    maFollowers.clear();
    for (size_t n = 0; n < rhs.maFollowers.size(); n++)
    {
        maFollowers.push_back(rhs.maFollowers[n]);
    }
    mbRadiating = rhs.mbRadiating;
    isTasked = rhs.isTasked;
    mfDamage_fract = rhs.mfDamage_fract;
    mzAction = rhs.mzAction;
    rectf = rhs.rectf;  
    remcon = rhs.remcon; 
    rdamage = rhs.rdamage; 
    raction = rhs.raction; 

    return *this;
}


void tcOOBView::Update() 
{

    UpdateData();
    UpdateTrackData();
    UpdateFormation();
    UpdateRect(mfYOffset - yOffset);
    
    PlaceIcons();

}




/**
* update maOOB data
*/
void tcOOBView::UpdateData()
{

    surfaceObj.clear();
    airObj.clear();
	carrierObj.clear();
    flightopsObj.clear(); 
    heloObj.clear();
    subObj.clear();
    groundObj.clear();

    wxASSERT(mpSimState);

    int alliance = (int)tcUserInfo::Get()->GetOwnAlliance();

    unsigned nCount = mpSimState->GetAlliancePlatforms(objKeys, MAX_OOB_OBJECTS, alliance);

    for (unsigned n = 0; n < nCount; n++) 
    {
        if (tcPlatformObject* platformObj = 
            dynamic_cast<tcPlatformObject*>(mpSimState->GetObject(objKeys[n])))
        {
            tsOOBInfo info;
            info.mnID = platformObj->mnID;
            info.mzName = platformObj->mzUnit;
            info.maFollowers.clear();
            
            info.mbRadiating = platformObj->IsRadiating();
            info.mfDamage_fract = platformObj->GetDamageLevel();     
            if (platformObj->formation.IsFollower())
            {
                info.mnLeaderID = platformObj->formation.leaderId;
            }
            else 
            {
                info.mnLeaderID = -1;
            }
            info.isLeader = platformObj->formation.IsLeader();

            ai::Brain* brain = platformObj->GetBrain();
            info.mzAction = brain->GetActionText();
            info.isTasked = brain->IsTasked();

            if (dynamic_cast<tcHeloObject*>(platformObj))
            {
                heloObj.push_back(info);
            }
            else if (dynamic_cast<tcAirObject*>(platformObj))
            {
                airObj.push_back(info);
            }
            else if (tcFlightOpsObject* flightOps = dynamic_cast<tcFlightOpsObject*>(platformObj))
            {
				if (dynamic_cast<tcAirfieldObject*>(platformObj))
				{
                    info.isTasked = true;
					flightopsObj.push_back(info);
				}
				else
				{
					if (flightOps->GetFlightPort()->GetHangarCapacity() > 3)
					{
						carrierObj.push_back(info);
					}
					else
					{
						surfaceObj.push_back(info);
					}
				}
            }
            else if (dynamic_cast<tcSurfaceObject*>(platformObj))
            {
                surfaceObj.push_back(info);
            }
            else if (dynamic_cast<tcSubObject*>(platformObj))
            {
                subObj.push_back(info);
            }
            else if (dynamic_cast<tcGroundObject*>(platformObj))
            {
                groundObj.push_back(info);
            }
            else if (dynamic_cast<tcGroundVehicleObject*>(platformObj))
            {
                groundObj.push_back(info);
            }
            else // unrecognized, do nothing
            {
            }
        }

    }

}


/**
*
*/
void tcOOBView::UpdateTrackData()
{
    int alliance = (int)tcUserInfo::Get()->GetOwnAlliance();

    surfaceTracks.clear();
    subTracks.clear();
    airTracks.clear(); 
    missileTracks.clear();
    unknownTracks.clear();

    tcGeoRect region;
    region.Set(-C_PI, C_PIM, -C_PIOVER2, C_PIOVER2); // all earth

    tcSensorTrackIterator iter(alliance, 0xFFFF, region);

    for (iter.First();iter.NotDone();iter.Next())
    {
        tcSensorMapTrack* track = iter.Get();

        wxASSERT(track);
        if (!track)
        {
            wxASSERT(false);
            fprintf(stderr, "tcOOBView::UpdateTrackData - NULL track\n");
            return;
        }

        tsOOBInfo info;

        info.mnID = track->mnID;

        wxString trackName = wxString::Format("Track %d", track->mnID);
        info.mzName = trackName.c_str();

        info.maFollowers.clear();
        info.mbRadiating = track->GetEmitterCount() > 0;
        info.mfDamage_fract = track->assessedDamage;
        info.mnLeaderID = -1;
        info.mzAction = "";
        info.isTasked = true;
        info.isLeader = false;

        unsigned int coarseClass = track->mnClassification & 0xFFF0;
        if (coarseClass & PTYPE_AIR)
        {
            airTracks.push_back(info);
        }
        else if (coarseClass & PTYPE_SURFACE)
        {
            surfaceTracks.push_back(info);
        }
        else if (coarseClass & PTYPE_SUBSURFACE)
        {    
            subTracks.push_back(info);
        }
        else if (coarseClass & PTYPE_MISSILE)
        {    
            missileTracks.push_back(info);
        }
        else // unknown
        {    
            unknownTracks.push_back(info);
        }

    }

}

/**
* update maOOB maFollowers array
* this can be expensive with many objects, 0(N^2)
*
* After recent mod, this only works for surface objects
*/
void tcOOBView::UpdateFormation() 
{
    return; // don't do this, it may have been years since this has done anything useful, dewitt JUN2008
#if 0
    wxASSERT(mpSimState);


    for (size_t n = 0; n < surfaceObj.size(); n++) 
    {
        tsOOBInfo& info = surfaceObj[n];

        // apply formation change if needed 
        if (msFormationChangeInfo.mbApply) 
        {
            if (msFormationChangeInfo.mnFollowerKey == info.mnID) 
            {
                // only allow formation change for surface objs 
                if (tcSurfaceObject* surfaceObj = 
                    dynamic_cast<tcSurfaceObject*>(mpSimState->GetObject(info.mnID)))
                {
                    info.mnLeaderID = msFormationChangeInfo.mnNewLeaderKey;
                    //surfaceObj->msFormationParameters.mnFormationLeader = info.mnLeaderID;
                    //surfaceObj->msFormationParameters.mbFormation = true;
                }
                msFormationChangeInfo.mbApply = false;
            }
        }
        // if the object is a follower in a formation update the leader's list
        if (info.mnLeaderID != NULL_INDEX)
        {
            info.rectf.bottom = -100; // to guard against no update
            // find leader
            bool bSearching = true;
            for (size_t k=0; (k<surfaceObj.size())&&(bSearching); k++) 
            {
                tsOOBInfo& leader = surfaceObj[k];
                if (leader.mnID == info.mnLeaderID) 
                {
                    leader.maFollowers.push_back(n);
                    bSearching = false;
                }
            }
        }
    }  
    msFormationChangeInfo.mbApply = false; // always clear formation change
#endif
}

/**
* update maOOB rectf
*/
void tcOOBView::UpdateRect(float yStart)
{
    float y = yStart;
    //float stopy = (float)mnHeight - mfRowSpacing;
    const float stopy = 32768.0f; // effectively disable stopy test
    const float yDisplayHeight = float(mnHeight) - mfYOffset - 2*mfRowSpacing;

    if (displayMode == SHOW_OWN)
    {
        for (size_t k=0; k<ownCategories.size(); k++)
        {
            float yk = y;

            UpdateRectCategory(*ownCategories[k].category, y, stopy);

            if (!ownCategories[k].isActive)
            {
                y = yk; // reset y if not active, do it here so header y is still correct
            }

            if (ownCategories[k].category->size() > 0) y += 2*mfRowSpacing;
        }
    }
    else if (displayMode == SHOW_TRACKS)
    {
        for (size_t k=0; k<trackCategories.size(); k++)
        {
            float yk = y;

            UpdateRectCategory(*trackCategories[k].category, y, stopy);

            if (!trackCategories[k].isActive)
            {
                y = yk; // reset y if not active, do it here so header y is still correct
            }

            if (trackCategories[k].category->size() > 0) y += 2*mfRowSpacing;

        }
    }

    if (y > yStart)
    {
        float scrollbarFraction =  yDisplayHeight / (y-yStart);
        scrollBar->SetBarFraction(scrollbarFraction);
    }
    else
    {
        scrollBar->SetBarFraction(1.1f);
    }

}

void tcOOBView::UpdateRectCategory(std::vector<tsOOBInfo>& objInfo, 
                                   float& y, float stopy)
{

    float x = mfXOffset;


    for (size_t n=0; (n < objInfo.size())&&(y < stopy); n++) 
    {
        tsOOBInfo& info = objInfo[n];
        //if (info.mnLeaderID == NULL_INDEX) 
        //{

        y += 2; // extra spacing to separate groups
        info.rectf.left = x;
        info.rectf.bottom = y;
        info.rectf.right = (float)mnWidth;
        info.rectf.top = y + mfRowSpacing;
        y += mfRowSpacing;

#if 0
        // draw followers
        for (size_t k = 0; k < info.maFollowers.size(); k++) 
        {
            size_t nFollowerIdx = info.maFollowers[k];
            if (nFollowerIdx >= objInfo.size()) 
            {
                fprintf(stderr, "tcOOBView - error - corrupt follower index\n");
                return;
            }
            tsOOBInfo& follower = objInfo[nFollowerIdx];
            follower.rectf.left = x + mfXIndent;
            follower.rectf.bottom = y;
            follower.rectf.right = (float)mnWidth;
            follower.rectf.top = y + mfRowSpacing;
            y += mfRowSpacing;

            // draw followers of follower (> 2 levels not supported)
            for (size_t k2=0; k2 < follower.maFollowers.size(); k2++) 
            {
                unsigned nFollowerIdx2 = follower.maFollowers[k2];
                if (nFollowerIdx2 >= objInfo.size())
                {
                    fprintf(stderr, "tcOOBView - error - corrupt follower2 index\n");
                    return;
                }
                tsOOBInfo& follower2 = objInfo[nFollowerIdx2];
                follower2.rectf.left = x + 2*mfXIndent;
                follower2.rectf.bottom = y;
                follower2.rectf.right = (float)mnWidth;
                follower2.rectf.top = y + mfRowSpacing;
                y += mfRowSpacing;
            }
        }
#endif

    }

}

/**
* Check if point is within category show/hide icon; and, if so, toggle the state of the icon
* @return true if point within category show/hide icon
*/
bool tcOOBView::CategoryShowHideClick(wxRealPoint p)
{
    if (displayMode == SHOW_OWN)
    {
        for (size_t k=0; k<ownCategories.size(); k++)
        {
            if (ownCategories[k].toggleIcon.ContainsPoint(p.x, p.y))
            {
                ownCategories[k].isActive = !ownCategories[k].isActive;
                return true;
            }
        }
    }
    else if (displayMode == SHOW_TRACKS)
    {
        for (size_t k=0; k<trackCategories.size(); k++)
        {
            if (trackCategories[k].toggleIcon.ContainsPoint(p.x, p.y))
            {
                trackCategories[k].isActive = !trackCategories[k].isActive;
                return true;
            }
        }
    }

    return false;
}

void tcOOBView::Draw() 
{
    //static int frameCount = 0;
    //if ((frameCount++ % 5) !=0 ) return;

    StartDraw();

    if (displayMode == SHOW_OWN)
    {
        DrawOwn();
    }
    else if (displayMode == SHOW_TRACKS)
    {
        DrawTracks();
    }

   /* DrawRectangleR(0, 0, mnWidth, mnHeight, 
        Vec4(0, 0, 0, 0.6f), FILL_ON);*/

    FinishDraw();
}

/**
*
*/
void tcOOBView::DrawOwn()
{
    Vec4 color(0.88f, 0.88f, 0.6f, 1.0f);

    DrawTextR("OWN PLATFORMS", mfXOffset, 20.0f, defaultFont.get(), 
            color, fontSize, LEFT_BASE_LINE);

    float stopy = (float)mnHeight - 2*mfRowSpacing;

    for (size_t k=0; k<ownCategories.size(); k++)
    {
        float yheader = GetCategoryY(*ownCategories[k].category);

        if ((yheader >= mfYOffset) && (yheader <= stopy))
        {
            const float iconSize = 12.0f;

            tcTexture2D* showHideIcon = 0;
            wxString caption;

            if (ownCategories[k].isActive)
            {
                showHideIcon = hideIcon.get();
                caption = ownCategories[k].caption.c_str();
            }
            else
            {
                showHideIcon = showIcon.get();
                caption.Printf("%s (%d)", ownCategories[k].caption.c_str(), ownCategories[k].category->size());
            }

            color.set(0.88f, 0.88f, 0.6f, 1.0f);
            DrawTextR(caption.c_str(), mfXOffset + iconSize + 4.0f, yheader - 5.0f, defaultFont.get(), 
                color, fontSize, LEFT_BASE_LINE);

            // draw show/hide icon to the left of the caption
            ownCategories[k].toggleIcon.left = mfXOffset;
            ownCategories[k].toggleIcon.right = ownCategories[k].toggleIcon.left + iconSize;
            ownCategories[k].toggleIcon.bottom = yheader - 7.0f - iconSize;
            ownCategories[k].toggleIcon.top = ownCategories[k].toggleIcon.bottom + iconSize;

            DrawImageR(showHideIcon, ownCategories[k].toggleIcon.left, ownCategories[k].toggleIcon.bottom, 
                iconSize, iconSize);
        }

        if (ownCategories[k].isActive)
        {
            DrawCategory(*ownCategories[k].category, stopy);
        }
    }

}

/**
*
*/
void tcOOBView::DrawTracks()
{
    Vec4 color(0.88f, 0.88f, 0.6f, 1.0f);

    float stopy = (float)mnHeight - 2*mfRowSpacing;

    DrawTextR("TRACKS", mfXOffset, 15.0f, defaultFont.get(), 
            color, fontSize, LEFT_BASE_LINE);

    for (size_t k=0; k<trackCategories.size(); k++)
    {
        float yheader = GetCategoryY(*trackCategories[k].category);

        if ((yheader >= mfYOffset) && (yheader <= stopy))
        {
            const float iconSize = 12.0f;

            tcTexture2D* showHideIcon = 0;
            wxString caption;

            if (trackCategories[k].isActive)
            {
                showHideIcon = hideIcon.get();
                caption = trackCategories[k].caption.c_str();
            }
            else
            {
                showHideIcon = showIcon.get();
                caption.Printf("%s (%d)", trackCategories[k].caption.c_str(), trackCategories[k].category->size());
            }

            color.set(0.88f, 0.88f, 0.6f, 1.0f);
            DrawTextR(caption.c_str(), mfXOffset + iconSize + 4.0f, yheader - 5.0f, defaultFont.get(), 
                color, fontSize, LEFT_BASE_LINE);

            // draw show/hide icon to the left of the caption
            trackCategories[k].toggleIcon.left = mfXOffset;
            trackCategories[k].toggleIcon.right = trackCategories[k].toggleIcon.left + iconSize;
            trackCategories[k].toggleIcon.bottom = yheader - 7.0f - iconSize;
            trackCategories[k].toggleIcon.top = trackCategories[k].toggleIcon.bottom + iconSize;

            DrawImageR(showHideIcon, trackCategories[k].toggleIcon.left, trackCategories[k].toggleIcon.bottom, 
                iconSize, iconSize);
        }

        if (trackCategories[k].isActive)
        {
            DrawCategory(*trackCategories[k].category, stopy);
        }
    }
}

void tcOOBView::DrawCategory(std::vector<tsOOBInfo>& objInfo, float stopy)
{
    Vec4 color(0.4f, 1, 0.4f, 1);
    Vec4 colorWarn(1, 1, 0.4f, 1);

    for (size_t n = 0; n < objInfo.size(); n++) 
    {
        tsOOBInfo& info = objInfo[n];
        float ftextx = info.rectf.left;
        float ftexty = info.rectf.top;
        if ((ftexty >= mfYOffset) && (ftexty < stopy)) 
        {
            if (info.mnID == mnSelectedKey)
                color.set(1, 1, 1, 1);
            else if (info.mfDamage_fract >= 0.5f)
                color.set(1, 0.4f, 0.4f, 1);
            else if (info.mfDamage_fract > 0)
                color.set(1, 1, 0.4f, 1);
            else
                color.set(0.4f, 1, 0.4f, 1);

            DrawTextR(info.mzName.c_str(), ftextx, ftexty, defaultFont.get(), 
                color, fontSize, LEFT_BASE_LINE, maxNameWidth);

            if (info.isLeader)
            {
                color.set(1.0f, 1.0f, 0.0f, 1.0f);
                DrawImageR(leaderIcon.get(), info.rleader.left, info.rleader.bottom, 
                    info.rleader.Width(), info.rleader.Width());
                //DrawRectangleR(info.rleader, color, FILL_ON);
            }

            if (info.mbRadiating) 
            {
                color.set(0.6f, 1.0f, 0.6f, 1.0f);
                
                tcRect r(info.remcon);
                r.right = r.left + 2.0f;

                //graphics->FillEllipse(mpBrush, info.remcon);
                DrawRectangleR(r, color, FILL_ON);

                r.Offset(4.0f, 0);
                DrawRectangleR(r, color, FILL_ON);

                r.Offset(4.0f, 0);
                DrawRectangleR(r, color, FILL_ON);
            }


            ftextx = info.raction.left;
            //ftexty = info.raction.top;

            if (info.isTasked)
            {           
                DrawTextR(info.mzAction.c_str(), ftextx, ftexty, defaultFont.get(), 
                    color, fontSize, LEFT_BASE_LINE);
            }
            else
            {
                DrawTextR("Orders?", ftextx, ftexty, defaultFont.get(), 
                    colorWarn, fontSize, LEFT_BASE_LINE);
            }


        }
    }

}


/**
* @return y value of top of first item in category, or zero if none exists
*/
float tcOOBView::GetCategoryY(std::vector<tsOOBInfo>& objInfo)
{

    if (objInfo.size())
    {
        return objInfo[0].rectf.bottom;
    }
    else
    {
        return 0;
    }

}

/**
* updates location of icon rectangles within each OOBInfo item
*/
void tcOOBView::PlaceIcons() 
{
    if (displayMode == SHOW_OWN)
    {
        PlaceIconsCategory(surfaceObj);
        PlaceIconsCategory(airObj);
        PlaceIconsCategory(subObj);
        PlaceIconsCategory(heloObj);
        PlaceIconsCategory(carrierObj);
        PlaceIconsCategory(flightopsObj);
        PlaceIconsCategory(groundObj);
    }
    else if (displayMode == SHOW_TRACKS)
    {
        PlaceIconsCategory(surfaceTracks);
        PlaceIconsCategory(subTracks);
        PlaceIconsCategory(airTracks);
        PlaceIconsCategory(missileTracks);
        PlaceIconsCategory(unknownTracks);
    }
}

void tcOOBView::PlaceIconsCategory(std::vector<tsOOBInfo>& objInfo)
{

    wxSize stringsize;

    for (size_t n=0; n < objInfo.size(); n++) 
    {
        tsOOBInfo& info = objInfo[n];

        MeasureText(defaultFont.get(), fontSize, info.mzName.c_str(), stringsize);
        float w = std::min(float(stringsize.GetWidth()), maxNameWidth);
        info.remcon.left = info.rectf.left + w + 12.0f;
        info.remcon.bottom = info.rectf.bottom - 2.0f;
        info.remcon.right = info.remcon.left + float(stringsize.GetHeight()-4);
        info.remcon.top = info.remcon.bottom + float(stringsize.GetHeight()-3);
        //info.remcon.Inflate(-2.0f,-2.0f);

        info.rleader = info.remcon;
        info.rleader.Offset(-info.remcon.Width(), 0);

        MeasureText(defaultFont.get(), fontSize, info.mzAction.c_str(), stringsize);

        info.raction.bottom = info.rectf.bottom - 1.0f;
        info.raction.left = info.remcon.GetRight() + 5.0f;
        if (info.raction.left < 120.0f) {info.raction.left = 120.0f;}
        info.raction.top = info.raction.bottom + float(stringsize.GetHeight());
        info.raction.right = info.raction.left + float(stringsize.GetHeight());
        //info.raction.Inflate(-2.0f,-2.0f);
    }

}

void tcOOBView::OnLButtonDClick(wxMouseEvent& event)
{
    wxPoint point = event.GetPosition();

    if (tsOOBInfo* info = 
        ButtonContainingPoint(wxRealPoint((float)point.x,(float)point.y)))
    {
        long new_key = info->mnID;
        if (new_key != -1)
        {
            long flags = 0;
            if (event.ShiftDown()) flags += 1;
            if (event.ControlDown()) flags += 2;
            if (event.AltDown()) flags += 4;

            wxCommandEvent command(wxEVT_COMMAND_BUTTON_CLICKED, ID_DCLICKHOOK) ;    
            command.SetEventObject(this);
            command.SetExtraLong(flags);
            AddPendingEvent(command);
        }
        mnSelectedKey = new_key;

        tcSound::Get()->PlayEffect("ShortBeep");
    }
}


void tcOOBView::OnLButtonDown(wxMouseEvent& event) 
{
    wxPoint point = event.GetPosition();

    wxRealPoint p(double(point.x), double(point.y));

    if (CategoryShowHideClick(p))
    {
        return;
    }

    if (tsOOBInfo* info = 
        ButtonContainingPoint(p))
    {
        long new_key = info->mnID;
        if (new_key != mnSelectedKey)
        {
            wxCommandEvent command(wxEVT_COMMAND_BUTTON_CLICKED, ID_NEWHOOK) ;    
            command.SetEventObject(this);
            command.SetExtraLong(new_key);
            AddPendingEvent(command);
        }
        mnSelectedKey = new_key;

        tcSound::Get()->PlayEffect("ShortBeep");

        mbMouseDrag = true;
        msFormationChangeInfo.mnFollowerKey = info->mnID;
    }
}

void tcOOBView::OnLButtonUp(wxMouseEvent& event) 
{
    if (!mbMouseDrag) {return;}

    wxPoint point = event.GetPosition();

    if (tsOOBInfo* info = 
        ButtonContainingPoint(wxRealPoint((float)point.x,(float)point.y))) 
    {
        if (info->mnID != mnSelectedKey) 
        {
            msFormationChangeInfo.mnNewLeaderKey = info->mnID;
            msFormationChangeInfo.mbApply = true;

            tcSound::Get()->PlayEffect("MutedBeep");
        }
    }
    mbMouseDrag = false;
}

void tcOOBView::OnLeaveWindow(wxMouseEvent& event)
{
    event.Skip();
    event.ResumePropagation(2); // so edge map scroll works
}

/**
* Skips mouse move to allow tactical map underneath to receive
*/
void tcOOBView::OnMouseMove(wxMouseEvent& event)
{
    event.Skip();
}

void tcOOBView::OnScrollbarUpdated(wxCommandEvent& event)
{
    yOffset = 0.25 * float(event.GetExtraLong());

    float yStart = mfYOffset - yOffset;
    UpdateRect(yStart);
    PlaceIcons();
}


void tcOOBView::BuildCategoryInfo()
{
    ownCategories.clear();
    trackCategories.clear();

    CategoryInfo info;

    // own
    info.category = &surfaceObj;
    info.caption = "Surface";
    ownCategories.push_back(info);

    info.category = &airObj;
    info.caption = "Air";
    ownCategories.push_back(info);

    info.category = &carrierObj;
    info.caption = "Carrier";
    ownCategories.push_back(info);

    info.category = &flightopsObj;
    info.caption = "Airfield";
    ownCategories.push_back(info);

    info.category = &heloObj;
    info.caption = "Helo";
    ownCategories.push_back(info);

    info.category = &subObj;
    info.caption = "Subsurface";
    ownCategories.push_back(info);

    info.category = &groundObj;
    info.caption = "Ground";
    ownCategories.push_back(info);

    for (size_t k=0; k<ownCategories.size(); k++)
    {
        ownCategories[k].isActive = true;
        ownCategories[k].toggleIcon.Set(0, 0, 0, 0);
    }

    // tracks
    info.category = &surfaceTracks;
    info.caption = "Surface";
    trackCategories.push_back(info);

    info.category = &subTracks;
    info.caption = "Subsurface";
    trackCategories.push_back(info);

    info.category = &airTracks;
    info.caption = "Air";
    trackCategories.push_back(info);

    info.category = &missileTracks;
    info.caption = "Missile";
    trackCategories.push_back(info);

    info.category = &unknownTracks;
    info.caption = "Unknown";
    trackCategories.push_back(info);

    for (size_t k=0; k<trackCategories.size(); k++)
    {
        trackCategories[k].isActive = true;
        trackCategories[k].toggleIcon.Set(0, 0, 0, 0);
    }

}

tsOOBInfo* tcOOBView::ButtonContainingPoint(wxRealPoint pointf) 
{
    std::vector<CategoryInfo>* pCategory = (displayMode == SHOW_OWN) ? &ownCategories : &trackCategories;

    for (size_t k=0; k<pCategory->size(); k++)
    {
        if (pCategory->at(k).isActive)
        {
            if (tsOOBInfo* info = ButtonContainingPointCategory(pointf, *pCategory->at(k).category))
            {
                return info;
            }
        }
    }

    return 0;
}

/**
*
*/
void tcOOBView::SetDisplayOwn(wxCommandEvent& event)
{
    displayMode = SHOW_OWN;
}

/**
*
*/
void tcOOBView::SetDisplayTrack(wxCommandEvent& event)
{
    displayMode = SHOW_TRACKS;
}


tsOOBInfo* tcOOBView::ButtonContainingPointCategory(wxRealPoint pointf, 
                                                    std::vector<tsOOBInfo>& objInfo)
{

    for (size_t n = 0; n < objInfo.size(); n++) 
    {
        tsOOBInfo* pInfo = &objInfo[n];
        if (pInfo->rectf.ContainsPoint(pointf.x, pointf.y)) 
        {
            return pInfo;
        }
    }

    return 0;

}


tcOOBView::tcOOBView(wxWindow *parent, 
                     const wxPoint& pos, const wxSize& size, 
                     const wxString& name,
					 tc3DWindow2* graphicsHost) :
	tcXmlWindow(parent, pos, size, "xml/oobview.xml", name, graphicsHost),
	mpMapView(0),
	mnSelectedKey(NULL_INDEX),
	mbMouseDrag(false),
	mfRowSpacing(12.0f),
	mfYOffset(40.0f),
	mfXOffset(5.0f),
	mfXIndent(15.0f),
    maxNameWidth(120.0f),
	displayMode(SHOW_OWN),
    yOffset(0)
{
    mpSimState = tcSimState::Get();

    SetBorderDraw(true);

    if (tcOptions::Get()->renderSurfaceLevel > 1)
    {
        SetUseRenderSurface(true);
        SetRenderSurfaceUpdateInterval(3);
    }

    fontSize = 12;

    leaderIcon = tc3DWindow2::LoadTexture("star.png");
    showIcon = tc3DWindow2::LoadTexture("plus_yellow.png");
    hideIcon = tc3DWindow2::LoadTexture("minus_yellow.png");

    SetBackgroundColor(Vec4(0, 0, 0, 0.8f));
    SetBackgroundDraw(true);

    const int scrollBarWidth = 12;
	scrollBar = new tcScrollBar(this, wxPoint(mnWidth-scrollBarWidth-2, 2), wxSize(scrollBarWidth, mnHeight-5));
	scrollBar->SetBackgroundAlpha(0.7f);
    if (tcOptions::Get()->renderSurfaceLevel > 1)
    {
        scrollBar->SetUseRenderSurface(true);
        scrollBar->SetRenderSurfaceUpdateInterval(3);
    }       
    scrollBar->SetBarFraction(1.5);
    scrollBar->SetActive(true);

    BuildCategoryInfo();
}

tcOOBView::~tcOOBView() 
{  

}