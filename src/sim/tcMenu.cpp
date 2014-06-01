/**  
**  @file tcMenu.cpp
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

#include "tcMenu.h"
#include "tcGeometry.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif 

using namespace std;


tc3DWindow2* tcMenu::parentWindow = 0;

boost::shared_ptr<tcGeometry> tcMenu::submenuIcon;
boost::shared_ptr<tcGeometry> tcMenu::stayOpenIcon;
bool tcMenu::newItemsStayOpen = false;

float tcMenu::yOffset = 400.0f;

void tcMenu::SetStayOpen(bool state)
{
    newItemsStayOpen = state;
}

void tcMenu::InitSubmenuIcon()
{
    submenuIcon = boost::shared_ptr<tcGeometry>(new tcGeometry);

    submenuIcon->MakeTexturedSymbol(tc3DWindow2::LoadTexture("arrow_right.png"), 8.0f);

    stayOpenIcon = boost::shared_ptr<tcGeometry>(new tcGeometry);

    stayOpenIcon->MakeTexturedSymbol(tc3DWindow2::LoadTexture("stay_open.png"), 8.0f);

#if 0

    osg::Vec4Array* colors = new osg::Vec4Array;
    colors->push_back(Vec4(0.0f, 0.0f, 0.0f, 1.0f));
    submenuIcon->setColorArray(colors);
    submenuIcon->setColorBinding(osg::Geometry::BIND_OVERALL);

    // create vertex array
    osg::Vec3Array* vertices = new osg::Vec3Array;
    submenuIcon->setVertexArray(vertices);


    vertices->push_back(osg::Vec3(w, 0, 0));
    vertices->push_back(osg::Vec3(-w, w, 0));
    vertices->push_back(osg::Vec3(-w, -w, 0));
    submenuIcon->addPrimitiveSet(new osg::DrawArrays(GL_TRIANGLES, 0, 3));



    submenuIcon->setUseDisplayList(true);

    // set state
    osg::StateSet* stateSet = submenuIcon->getOrCreateStateSet();
    stateSet->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF);
    stateSet->setMode(GL_DEPTH_WRITEMASK, osg::StateAttribute::OFF);
    stateSet->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
    stateSet->setMode(GL_BLEND, osg::StateAttribute::ON);
    stateSet->setRenderBinDetails(31, "RenderBin");
#endif
}

void tcMenu::SetSubmenuIconRenderBin(int bin)
{
#if 0
    wxASSERT(submenuIcon.valid());

    osg::StateSet* stateSet = submenuIcon->getOrCreateStateSet();
    stateSet->setRenderBinDetails(bin, "RenderBin");
#endif
}


void tcMenu::AddItem(const std::string& caption, int command) 
{
    if (mpCurrent == this) 
    {
        tsMenuData md;

        md.Clear();
        md.mzCaption = caption;
        md.mzCommand = "";
        md.mzUserInput = "";
        md.mnCommand = command;
        md.closePopup = !newItemsStayOpen;
        maMenuData.push_back(md);
    }
    else 
    {
        mpCurrent->AddItem(caption, command);
    }
}

void tcMenu::AddItem(const std::string& caption, const std::string& command, int param) 
{
    if (mpCurrent == this) 
    {
        tsMenuData md;

        md.Clear();
        md.mzCaption = caption;
        md.mzCommand = command;
        md.mzUserInput = "";
        md.mnCommand = param;
        md.closePopup = !newItemsStayOpen;
        maMenuData.push_back(md);
    }
    else 
    {
        mpCurrent->AddItem(caption, command, param);
    }
}

/**
* Version that accepts std::string param
*/
void tcMenu::AddItem(const std::string& caption, const std::string& command, 
					 const std::string& textParam)
{
    if (mpCurrent == this) 
    {
        tsMenuData md;

        md.Clear();
        md.mzCaption = caption;
        md.mzCommand = command;
        md.mzUserInput = "";
        md.mnCommand = -1;
        md.textParam = textParam;
        md.closePopup = !newItemsStayOpen;
        maMenuData.push_back(md);
    }
    else 
    {
        mpCurrent->AddItem(caption, command, textParam);
    }
}


/* version for user input with callback
** if param != -1 it is passed as an argument to the python callback
*/
void tcMenu::AddItemUI(const std::string& caption, const std::string& callback, 
					   const std::string& input, int param) 
{
    if (mpCurrent == this) 
    {
        tsMenuData md;

        md.Clear();
        md.mzCaption = caption;
        md.mzCommand = callback;
        md.mzUserInput = input;
        md.mnCommand = param;
        md.closePopup = true; // 14AUG2011 should always close on UI input !newItemsStayOpen;
        maMenuData.push_back(md);
    }
    else 
    {
        mpCurrent->AddItemUI(caption, callback, input, param);
    }
}

void tcMenu::AddItemUI(const std::string& caption, const std::string& callback, 
		const std::string& input, const std::string& textParam)
{
    if (mpCurrent == this) 
    {
        tsMenuData md;

        md.Clear();
        md.mzCaption = caption;
        md.mzCommand = callback;
        md.mzUserInput = input;
        md.mnCommand = -1;
		md.textParam = textParam;
        md.closePopup = true; // 14AUG2011 should always close on UI input !newItemsStayOpen;
        maMenuData.push_back(md);
    }
    else 
    {
        mpCurrent->AddItemUI(caption, callback, input, textParam);
    }
}

void tcMenu::BeginSubMenu() 
{
    if (mpCurrent == this) 
    {
        int nSize = (int)maMenuData.size();

        if (nSize == 0) {return;} // can't add submenu to empty menu
        tsMenuData& md = maMenuData[nSize-1];
        if (md.mpSubMenu == NULL) 
        {
            // create new menu with this as parent
            tcMenu *pNewMenu = new tcMenu(this); 
            md.mpSubMenu = pNewMenu;
        }
        // set mpCurrent to submenu of last item
        mpCurrent = md.mpSubMenu;
        md.mnCommand = 0; // item with subitems can't have command
        md.mzCommand = "";
    }
    else 
    {
        mpCurrent->BeginSubMenu();
    }
}

void tcMenu::EndSubMenu()
{
    if (mpCurrent == this) 
    {
        if (mpParent == NULL) {return;} // error endsub on top level
        mpParent->mpCurrent = mpParent;
    }
    else {
        mpCurrent->EndSubMenu();
    }
}

void tcMenu::ClearSelected() 
{
    int nMenuSize = (int)maMenuData.size();  

    for(int i=0;i<nMenuSize;i++) 
    {
        tsMenuData *pmd = &maMenuData[i];
        pmd->mbSelected = false;
        if (pmd->mpSubMenu != NULL) {pmd->mpSubMenu->ClearSelected();}
    }
}

void tcMenu::Clear() 
{
    int nMenuSize = (int)maMenuData.size();  

    // clear submenus first
    for(int i=0;i<nMenuSize;i++) 
    {
        tsMenuData *pmd = &maMenuData[i];
        if (pmd->mpSubMenu != NULL)
        {
            pmd->mpSubMenu->Clear();
            delete pmd->mpSubMenu;
            pmd->mpSubMenu = NULL;
        }
    }

    maMenuData.clear();
    mbUpdateRegions = true;
    mpCurrent = this;
    mpParent = NULL;
}

void tcMenu::Draw() 
{
    if (mbUpdateRegions) 
    {
        UpdateRegions();
        mbUpdateRegions = false;
    }
    int nMenuSize = (int)maMenuData.size();  // number of items in menu

    for (int i=0; i<nMenuSize; i++) 
    {
        tsMenuData *pmd = &maMenuData[i];
        DrawItem(pmd);
    }
}

void tcMenu::DrawItem(tsMenuData *apMD) 
{
    float alpha = 0.8f;

    Vec4 color(0, 0, 0, 1);

    wxASSERT(parentWindow);

    //if the menu item is selected
    if (apMD->mbSelected) 
    {
        color.set(0, 0.6f, 1.0f, alpha);
    }
    else 
    { 
        color.set(0.8f, 0.8f, 0.84f, alpha);

    }

    tcRect item_rect = apMD->mrect;
    item_rect.Offset(anchor.x, anchor.y);
    parentWindow->DrawRectangleR(item_rect, color, tc3DWindow2::FILL_ON);
    parentWindow->DrawRectangleR(item_rect, Vec4(0, 0, 0, 0.25f), tc3DWindow2::FILL_OFF);

    if (apMD->mbSelected) 
    {
        color.set(1, 1, 1, alpha);
    }
    else 
    { 
        color.set(0, 0, 0, alpha);
    }

    wxRealPoint pointf(apMD->mrect.GetLeft() + 5.0f, apMD->mrect.GetTop() - 2.0f);  
    pointf = pointf + anchor;

    parentWindow->DrawTextR(apMD->mzCaption.c_str(), pointf.x, pointf.y,
        parentWindow->GetDefaultFont(), color, fontSize, tc3DWindow2::LEFT_BASE_LINE);




    if (apMD->mpSubMenu != NULL) 
    {
        float subx = item_rect.left + mfItemWidth - 4.0f;
        float suby = item_rect.YCenter();


        parentWindow->DrawGeometryR(submenuIcon.get(), subx, suby);

        // if item is selected, draw the submenu
        if (apMD->mbSelected) 
        {
            wxRealPoint submenu_offset;
            submenu_offset.x = item_rect.GetRight()-1.0f;

            // check if menu runs off bottom of page, if so draw bottom to top
            float menuHeight = apMD->mpSubMenu->maMenuData.size() * (mfItemHeight - 1.0f);
            float yMenu = float(parentWindow->GetPosition().y) - yOffset;
            float yBottom = yMenu + anchor.y + item_rect.GetBottom() + menuHeight;
            float screenBottom = float(parentWindow->GetParent()->GetSize().GetHeight());

            if (yBottom < screenBottom)
            {
                submenu_offset.y = item_rect.GetBottom();
            }
            else
            {
                submenu_offset.y = item_rect.GetTop() - menuHeight + 2.0f*(mfItemHeight-1.0f);
            }
            
            apMD->mpSubMenu->SetAnchor(submenu_offset);
            apMD->mpSubMenu->Draw();


            
        }
    }
    else if (!apMD->closePopup)
    {
        // 14AUG2011 disabled this, why show an indication that the menu stays open?
        //float x = item_rect.left + mfItemWidth - 4.0f;
        //float y = item_rect.YCenter();

        //parentWindow->DrawGeometryR(stayOpenIcon.get(), x, y);
    }

}

/**
* Generate vector describing current selected menu tree
* Empty indicates no items selected
* Each element indicates index of item selected in corresponding
* submenu, starting with zero as the first item
*/
void tcMenu::GetCurrentSelections(std::vector<unsigned int>& selection) const
{
    size_t nMenuSize = maMenuData.size();  // number of items in menu

    for (size_t n=0; n<nMenuSize; n++) 
    {
        const tsMenuData* pmd = &maMenuData[n];

        if (pmd->mbSelected)
        {
            selection.push_back(n);
            if (pmd->mpSubMenu != 0)
            {
                pmd->mpSubMenu->GetCurrentSelections(selection);
            }
        }
    }
}

/**
* Forces current menu selection, useful for restoring user selection after 
* menu has been rebuilt
*/
void tcMenu::SetCurrentSelections(const std::vector<unsigned int>& selection)
{
    ClearSelected();

    if (selection.size() == 0) return;

    unsigned int select_idx = selection[0];

    if (select_idx < maMenuData.size())
    {
        maMenuData[select_idx].mbSelected = true;
        tcMenu* subMenu = maMenuData[select_idx].mpSubMenu;
        if (subMenu != 0)
        {
            std::vector<unsigned int> selectionTail;
            for (size_t n=1; n<selection.size(); n++)
            {
                selectionTail.push_back(selection[n]);
                subMenu->SetCurrentSelections(selectionTail);
            }
        }
    }
}


/**
* @return pointer to item (NULL for none) containing point 
*/
tsMenuData* tcMenu::ItemContainingPoint(const wxRealPoint& point) 
{
    int nMenuSize = (int)maMenuData.size();  

    wxRealPoint local_point = point - anchor; // adjust for anchor


    for(int i=0; i<nMenuSize; i++) 
    {
        tsMenuData *pmd = &maMenuData[i];
        if (pmd->mrect.ContainsPoint(local_point.x, local_point.y)) 
        {
            return pmd;
        }

        // if item is selected and has submenu, check submenu
        if ((pmd->mpSubMenu != NULL) && (pmd->mbSelected)) 
        {
            tsMenuData *psub = pmd->mpSubMenu->ItemContainingPoint(point);
            if (psub != NULL) {return psub;}
        }
    }
    return NULL; // not found
}


/**
* select menu item and all parent items containing point 
*/
bool tcMenu::UpdateSelection(const wxRealPoint& point) 
{
    int nMenuSize = (int)maMenuData.size();  

    wxRealPoint local_point = point - anchor; // adjust for anchor

    //   if (!menubox.Contains(point)) { return NULL;}
    bool bResult = false;

    for(int i=0; i<nMenuSize; i++) 
    {
        tsMenuData *pmd = &maMenuData[i];
        tcMenu *pSubMenu = pmd->mpSubMenu;
        bool bSelected = pmd->mbSelected;
        if (!bResult && pmd->mrect.ContainsPoint(local_point.x, local_point.y)) 
        {
            pmd->mbSelected = true;
            if (pSubMenu != NULL) {pSubMenu->ClearSelected();}
            bResult = true;
        }
        else if ((pSubMenu != NULL)&&(bSelected)) 
        {
            if (pSubMenu->UpdateSelection(point) == false)
            {
                pmd->mbSelected = false;
            }
            else
            {
                bResult = true;
            }
        }
        else 
        {
            pmd->mbSelected = false;
        }
    }

    // if point is outside of all menu items, check if point is close to top or bottom
    // to avoid closing submenu in these cases
    if (!bResult && (nMenuSize > 0))
    {
        tcRect overall = maMenuData[0].mrect;
        overall.top = maMenuData[nMenuSize-1].mrect.top;

        overall.left -= 0.0f;
        overall.right += 15.0f;
        overall.top += 15.0f;
        overall.bottom -= 15.0f;

        return overall.ContainsPoint(local_point.x, local_point.y);
    }

    return bResult; // not found
}

void tcMenu::UpdateRegions() 
{

    int maxWidth = 0;
    int maxHeight = 0;
    tsMenuData *pmd;

    int nMenuSize = (int)maMenuData.size();  

    // find max item width and height
    for(int i=0; i<nMenuSize; i++) 
    {
        wxSize boundingBox;

        pmd = &maMenuData[i];
        parentWindow->MeasureText(parentWindow->GetDefaultFont(), fontSize, pmd->mzCaption.c_str(), 
            boundingBox);

        int w = boundingBox.GetWidth();
        if (pmd->mpSubMenu) w += 3;

        maxWidth = (w > maxWidth) ? w : maxWidth;
        maxHeight = (boundingBox.GetHeight() > maxHeight) ? boundingBox.GetHeight() : maxHeight;


    }

    mfItemWidth = float(maxWidth) + 12.0f;
    mfItemHeight = float(maxHeight) + 3.0f;
    menubox.left = 0;
    menubox.bottom = 0; // upper-left corner
    menubox.right = menubox.left + float(maxWidth) + 12.0f;
    menubox.top = menubox.bottom + (float(maxHeight) + 4.0f)*((float)nMenuSize);

    // set item rectangles
    tcRect itemrect;

    itemrect.Set(0, mfItemWidth, 0, mfItemHeight);

    for(int i=0; i<nMenuSize; i++) 
    {
        pmd = &maMenuData[i];
        pmd->mrect = itemrect;
        itemrect.bottom += mfItemHeight - 1.0f;
        itemrect.top += mfItemHeight - 1.0f;
    }

}

tcMenu::tcMenu() 
: fontSize(14.0),
  anchor(5.0, yOffset)
{
    maMenuData.clear();
    mbUpdateRegions = true;
    mpCurrent = this;
    mpParent = NULL;

    if (submenuIcon.get() == 0)
    {
        InitSubmenuIcon();
    }
}

tcMenu::tcMenu(tcMenu* apParent) 
: fontSize(14.0),
  anchor(5.0, 5.0)
{
    maMenuData.clear();
    mbUpdateRegions = true;
    mpCurrent = this;
    mpParent = apParent;

    if (submenuIcon.get() == 0)
    {
        InitSubmenuIcon();
    }
}



tcMenu::~tcMenu() 
{
    Clear();
}
