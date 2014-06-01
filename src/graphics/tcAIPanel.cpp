/**
**  @file tcAIPanel.cpp
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

#include "tcAIPanel.h"

#include "ai/Brain.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif



void tcAIPanel::Draw(tc3DWindow2* context) 
{
    char zBuff[128];
    std::string s;

    if (!brain) return;
	wxASSERT(context);

	UpdateTaskInfo(context);

	Vec4 color(0.8f, 1.0f, 0.8f, 1.0f);
	tcFont* font = context->GetDefaultFont();
	tcFont* italicFont = context->GetItalicFont();

	float textx = window.left + 5.0f;
	float texty = window.bottom + 15.0f;

	context->DrawTextR(mzCaption.c_str(), textx, texty, 
        font, color, 11.0, tc3DWindow2::LEFT_BASE_LINE);

	DrawPageSelect(context);

	
	if (showHiddenTasks)
	{
		const Vec4 iconColor(1, 1, 1, 1);
		context->DrawImageColoredR(showHiddenIcon.get(), hideShowButton.XCenter()-5.0, hideShowButton.YCenter()-5.0, 10.0, 10.0, iconColor);
	}
	else
	{
		const Vec4 iconColor(0.5, 0.5, 0.5, 1);
		context->DrawImageColoredR(showNormalIcon.get(), hideShowButton.XCenter()-5.0, hideShowButton.YCenter()-5.0, 10.0, 10.0, iconColor);
	}

    texty += 15.0f;
    long nTargetID = brain->GetTarget();
    if (nTargetID != NULL_INDEX) 
    {
        sprintf(zBuff, "Target: %04d", nTargetID);
		context->DrawTextR(zBuff, textx, texty, 
			font, color, fontSize, tc3DWindow2::LEFT_BASE_LINE);
    }
    else 
    {
		color.set(0.4f, 0.5f, 0.4f, 1.0f);
		context->DrawTextR("Target: --", textx, texty, 
			font, color, fontSize, tc3DWindow2::LEFT_BASE_LINE);
		color.set(0.8f, 1.0f, 0.8f, 1.0f);
    }
    texty += 15.0f;

    size_t nTasks = taskInfo.size();


	if (nTasks > 0) 
	{   
		size_t row_start = currentPage * MAX_ROWS_PER_PAGE;
		size_t row_stop = row_start + MAX_ROWS_PER_PAGE;
		if (row_stop > nTasks) row_stop = nTasks;
		wxASSERT(row_start <= row_stop);

        for (size_t n=row_start; n<row_stop; n++)
        {
            color.set(0.8f, 1.0f, 0.8f, 1.0f);
            
#ifdef _DEBUG
            sprintf(zBuff, "%s %.0f", taskInfo[n].taskName.c_str(), taskInfo[n].priority);
#else
			sprintf(zBuff, "%s", taskInfo[n].taskName.c_str()); // don't draw priority in release mode
#endif
			tcFont* textFont = (taskInfo[n].isHidden) ? italicFont : font;
            context->DrawTextInRectR(zBuff, taskDrawBoxes[n], 
				textFont, color, fontSize, tc3DWindow2::LEFT_CENTER);

			const Vec4 color(0.5, 0.5, 0.5, 1);
			context->DrawImageColoredR(deleteIcon.get(), deleteButtons[n].XCenter()-5.0, deleteButtons[n].YCenter()-5.0, 10.0, 10.0, color);

			texty = taskDrawBoxes[n].top;
        }
    }
    else 
    {
        color.set(0.4f, 0.5f, 0.4f, 1.0f);
		context->DrawTextR("No tasks", textx, texty, 
				font, color, fontSize, tc3DWindow2::LEFT_BASE_LINE);
        texty += 10.0f;
    }

	color.set(0.4f, 1.0f, 0.4f, 1.0f);
    window.top = texty + 5.0f; 
	context->DrawRectangleR(window, color, tc3DWindow2::FILL_OFF);
}

/**
* Draw icons to switch between pages (if panel has multiple pages)
*/
void tcAIPanel::DrawPageSelect(tc3DWindow2* context)
{
    if (nPages <= 1) return; // don't draw anything for one page

    Vec4 color(0.7f, 0.7f, 0.7f, 0.7f);

    float x = window.left + 90.0f;
    float y = window.bottom + 5.0f;
    float w = 6.0f;

    pageSelectBoxes.clear();

    for (unsigned int n=0; n<nPages; n++)
    {
        tcRect r(x, x+w, y, y+w);
        pageSelectBoxes.push_back(r);

        int fillMode = (n == currentPage) ? tc3DWindow2::FILL_ON : tc3DWindow2::FILL_OFF;
        context->DrawRectangleR(r, color, fillMode);

        x += w + 2.0f;
    }

}

const Brain* tcAIPanel::GetAIData() const
{
    return brain;
}

/**
* @return true if panel contains point
*/
bool tcAIPanel::OnLButtonDown(const wxPoint& pos)
{
	wxASSERT(taskInfo.size() == deleteButtons.size());

	float x = (float)pos.x;
	float y = (float)pos.y;
	bool pointInside = window.ContainsPoint(x, y);

	if (!pointInside) return false;

	UpdatePageSelect(pos);

	if (hideShowButton.ContainsPoint(x, y))
	{
		showHiddenTasks = !showHiddenTasks;
		return true;
	}

	size_t nTasks = taskInfo.size();
	size_t row_start = currentPage * MAX_ROWS_PER_PAGE;
	size_t row_stop = row_start + MAX_ROWS_PER_PAGE;
	if (row_stop > nTasks) row_stop = nTasks;

	for (size_t n=row_start; n<row_stop; n++)
	{
		if (deleteButtons[n].ContainsPointInclusive(x, y))
		{
			if (brain != 0)
			{
				if (taskInfo[n].isPermanent)
				{
					brain->AddTask(taskInfo[n].taskName, taskInfo[n].priority, 0); // clear permanent attribute to enable remove
				}
				brain->RemoveTask(taskInfo[n].taskName);
			}
			return true;
		}
	}

	return true;
}


void tcAIPanel::SetPage(unsigned int page)
{
    currentPage = page;
    if (currentPage >= nPages)
    {
        currentPage = nPages - 1;
        wxASSERT(false);
    }
}

/**
* For multiple page panel, check if point is within a page select
* box. If so, then switch page.
*/
void tcAIPanel::UpdatePageSelect(const wxPoint& point)
{
    if (nPages <= 1) return;

    float x = float(point.x);
    float y = float(point.y);

    for (size_t k=0; k<pageSelectBoxes.size(); k++)
    {
        if (pageSelectBoxes[k].ContainsPoint(x, y))
        {
            SetPage(k);
            return;
        }
    }
}

void tcAIPanel::UpdateTaskInfo(tc3DWindow2* context)
{
	taskInfo.clear();
	taskDrawBoxes.clear();
	deleteButtons.clear();

	hideShowButton.Set(window.right-14.0, window.right-4.0, window.bottom + 3.0, window.bottom+13.0);

	if (!brain) return;

	std::vector<Brain::TaskInfo> allTaskInfo = brain->GetTaskListInfo();

    size_t nTasks = allTaskInfo.size();

	float ystart = window.bottom + 32.0f;
	float ytext = ystart;
	float xtext = window.left + 3.0f;
	const float rowHeight = 13.0;
	const float deleteSize = 10.0f;

	tcFont* font = context->GetDefaultFont();
	tcFont* italicFont = context->GetItalicFont();

	for (size_t n=0; n<nTasks; n++)
	{
		if (!allTaskInfo[n].isHidden || showHiddenTasks)
		{
			taskInfo.push_back(allTaskInfo[n]);

			wxSize size;
			tcFont* textFont = (taskInfo.back().isHidden) ? italicFont : font;
			context->MeasureText(textFont, fontSize, taskInfo.back().taskName.c_str(), size);
			float textWidth = float(size.GetWidth() + 5);

			tcRect drawBox(xtext, textWidth, ytext, ytext + rowHeight);

			float x1 = xtext + textWidth + 2.0f;
			float y1 = ytext + 0.5f * (rowHeight - deleteSize) + 1.0f;
			tcRect deleteBox(x1, x1 + deleteSize, 
				y1, y1 + deleteSize);

			taskDrawBoxes.push_back(drawBox);
			deleteButtons.push_back(deleteBox);

			ytext += rowHeight;

			if ((taskInfo.size() % MAX_ROWS_PER_PAGE) == 0)
			{
				ytext = ystart;
			}
		}
	}

	// calculate number of pages
	size_t nRows = taskInfo.size();
    if (nRows > 0)
    {
        /* with MAX_ROWS_PER_PAGE = 8
        ** 1 row = 1 page
        ** 8 rows = 1 page
        ** 9 rows = 2 pages
        ** 16 rows = 2 pages
        */
        nPages = ((nRows - 1) / MAX_ROWS_PER_PAGE) + 1;
    }
    else
    {
        nPages = 1;
    }

}

tcAIPanel::tcAIPanel() 
: 
brain(0),
mzCaption("TASK STATUS"),
fontSize(12.0),
showHiddenTasks(false),
currentPage(0)
{
	 deleteIcon = tc3DWindow2::LoadTexture("close.png");
	 showHiddenIcon = tc3DWindow2::LoadTexture("eye_icon.png");
     showNormalIcon = tc3DWindow2::LoadTexture("blank_icon.png");
}

tcAIPanel::~tcAIPanel() 
{
}
