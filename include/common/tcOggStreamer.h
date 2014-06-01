/**  
**  @file tcOggStreamer.h
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
#endif 

#ifndef _OGGSTREAMER_H_
#define _OGGSTREAMER_H_

#include <openalpp/alpp.h>
#include <string>
#include <iostream>


/**
* Ogg streaming using OpenAL++ Stream
* Stream is threaded
*/
class tcOggStreamer
{
    enum
    {
        BUFFER_SIZE = 16*1024,
        NUM_BUFFERS = 8
    };
public:
    void Display();       
    bool GetPause() const {return paused;}
    bool IsPaused();
    bool IsPlaying();
    bool IsSongQueued() {return queuedSong.size() > 0;}
    bool IsStopped();
    float GetVolume() const {return volume;}
    void Open(const std::string& path);
    void Play();
    void Queue(const std::string& path);
    void Seek(double seekTime);
    void SetPause(bool state) {paused = state;}
    void SetVolume(float vol);
    void Stop();
    void Update();

    tcOggStreamer();
    ~tcOggStreamer();

private:
    openalpp::ref_ptr<openalpp::FileStream> stream;
    openalpp::ref_ptr<openalpp::Source> source;

    float volume; ///< linear gain for source, 0.5f = -6 dB
    std::string queuedSong; ///< complete file path of song to queue
    bool paused;
    bool initializingStream; ///< true when stream is initializing, cleared once playing
};


#endif 
