/**  
**  @file tcObjectControl.h
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

#ifndef _AIPANEL_H_
#define _AIPANEL_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "wx/wx.h" 
#include "tc3DWindow2.h"
#include "ai/Brain.h"
#include <string>


namespace ai
{
    class Brain;
}

using ai::Brain;


class tcAIPanel 
{
public:
    tcRect window;
    std::string mzCaption;
	bool showHiddenTasks;

	bool OnLButtonDown(const wxPoint& pos);
    const Brain* GetAIData() const;
    void SetAIData(Brain* brain_) {brain = brain_;}
    void SetLocation(tcRect rect) {window = rect;}
    void Draw(tc3DWindow2* context);
    tcAIPanel();
    ~tcAIPanel();
private:
    enum
    {
        MAX_ROWS_PER_PAGE = 8
    };

    Brain* brain;
	const float fontSize;
	

	std::vector<Brain::TaskInfo> taskInfo;
	std::vector<tcRect> taskDrawBoxes;
	std::vector<tcRect> deleteButtons;
    unsigned int currentPage;
    size_t nPages;
    std::vector<tcRect> pageSelectBoxes;
	boost::shared_ptr<tcTexture2D> deleteIcon;
	boost::shared_ptr<tcTexture2D> showHiddenIcon;
	boost::shared_ptr<tcTexture2D> showNormalIcon;
	tcRect hideShowButton;

	void DrawPageSelect(tc3DWindow2* context);
	void SetPage(unsigned int page);
	void UpdatePageSelect(const wxPoint& point);
	void UpdateTaskInfo(tc3DWindow2* context);
};


#endif
