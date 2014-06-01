/**
**  @file tcOggStreamer.cpp
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

#include "stdwx.h" // precompiled header file

#ifndef WX_PRECOMP
#endif

#include "tcOggStreamer.h"

using namespace std;

/**
* Opens ogg file. If a file is already open, the file 
* is closed and the stream is reinitialized.
* This allows Open() to be called to switch the music.
* @param path string containing path and filename of
* oggfile to open.
*/
void tcOggStreamer::Open(const std::string& path)
{
    Queue(path);

    Stop();
}





/**
* Seeks to seekTime if song is playing
* (not implemented yet in this version using OpenAL++)
*/
void tcOggStreamer::Seek(double seekTime)
{
    wxASSERT(source.valid());
	if (!source.valid()) return;

    source->seek(seekTime);
}

/**
* Sets volume (linear gain) for OpenAL source
* associated with streaming music.
* @param vol voltage gain, e.g. 0.5 = -6 dB
*/
void tcOggStreamer::SetVolume(float vol)
{  
    volume = vol;

    wxASSERT(source.valid());
	if (!source.valid()) return;

    source->setGain(volume);
}

/**
* 
*/
void tcOggStreamer::Stop()
{
    wxASSERT(source.valid());
	if (!source.valid()) return;

    source->stop();
}


void tcOggStreamer::Display()
{
}



/**
*
*/
void tcOggStreamer::Play()
{
    wxASSERT(source.valid());
	if (!source.valid()) return;

    paused = false;

    if (!IsPlaying())
    {
        source->play();
    }
}



void tcOggStreamer::Queue(const std::string& path) 
{
    wxASSERT(source.valid());

#ifdef _DEBUG
    if (queuedSong.size() > 0)
    {
        fprintf(stderr, "Warning - tcOggStreamer::Queue - Replacing "
            "previously queued audio file (%s)\n", queuedSong.c_str());
    }
#endif

    queuedSong = path;
}

bool tcOggStreamer::IsPaused()
{
    wxASSERT(source.valid());
	if (!source.valid()) return false;

    return (source->getState() == openalpp::Paused);
}


bool tcOggStreamer::IsPlaying()
{
    wxASSERT(source.valid());
	if (!source.valid()) return false;

    return (source->getState() == openalpp::Playing);
}

bool tcOggStreamer::IsStopped()
{
    wxASSERT(source.valid());
	if (!source.valid()) return true;

    return (source->getState() == openalpp::Stopped);
}

void tcOggStreamer::Update()
{
	wxASSERT(source.valid());
	if (!source.valid()) return;

    if (queuedSong.size() == 0) return;

    openalpp::SourceState sourceState = source->getState();

    if (sourceState == openalpp::Playing)
    {
        initializingStream = false;
    }

    if (initializingStream) return;

    if ((sourceState == openalpp::Stopped) ||
        (sourceState == openalpp::Initial))
    {
        source = new openalpp::Source;

        //source->setGain(volume);
        source->setSound(new openalpp::FileStream(queuedSong));
        source->setAmbient();
        source->play();

		fprintf(stdout, "Starting new audio stream: %s\n", queuedSong.c_str());
        queuedSong = "";
        initializingStream = true;

    }
}

tcOggStreamer::tcOggStreamer()
:   volume(0.2f),
    queuedSong(""),
    paused(false),
    initializingStream(false)
{
	try
	{
		source = new openalpp::Source;
	}
	catch (openalpp::MemoryError e)
	{
		fprintf(stderr, "tcOggStreamer::tcOggStreamer: openalpp::MemoryError: %s\n", e.what());
		wxMessageBox(e.what(), "Memory Error", wxICON_ERROR);
	}
	catch (openalpp::NameError e)
	{
		fprintf(stderr, "tcOggStreamer::tcOggStreamer: openalpp::NameError: %s\n", e.what());
		wxMessageBox(e.what(), "Name Error", wxICON_ERROR);
	}
	catch (openalpp::FatalError e)
	{
		fprintf(stderr, "tcOggStreamer::tcOggStreamer: openalpp::FatalError: %s\n", e.what());
		wxMessageBox(e.what(), "Fatal Error", wxICON_ERROR);
	}
	catch (openalpp::Error e)
	{
		fprintf(stderr, "tcOggStreamer::tcOggStreamer: openalpp::Error: %s\n", e.what());
		wxMessageBox(e.what(), "General openAL++ Error", wxICON_ERROR);
	}
	catch (std::exception e)
	{
		fprintf(stderr, "tcOggStreamer::tcOggStreamer: std::exception: %s\n", e.what());
		wxMessageBox(e.what(), "Exception", wxICON_ERROR);
	}
	
	if (source.valid())
	{
		source->setAmbient();
		//source->setGain(volume);
	}
	else
	{
		fprintf(stderr, "OGG init error: music will be disabled!\n");
	}
}

tcOggStreamer::~tcOggStreamer()
{
    if (source.valid())
    {
        source->stop();
    }
    //wxUSleep(500);
    // wxMilliSleep(500); // 2.5 and above
}

