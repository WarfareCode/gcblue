/**  
**  @file tcSound.h
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


#ifndef _SOUND_H_
#define _SOUND_H_

#if _MSC_VER > 1000
#pragma once
#endif 

//#include <AL/al.h>
//#include <AL/alut.h>
//#include <AL/alc.h>

#include <openalpp/alpp.h>
//#include "osgAL/SoundNode"
//#include "osgAL/SoundRoot"
//#include "osgAL/SoundManager"
//#include "osgAL/SoundState"

#include <queue>
#include <string>
#include <map>

class tcOggStreamer;

#define WAV_PATH "sound\\wav\\"
#define OGG_PATH "sound\\ogg\\"


#define N_EFFECT_BUFFERS 16


enum teMusicState
{
    MS_STOPPED,
    MS_WAIT,
    MS_NEWCHANGE,
    MS_FADEOUT,
    MS_FADEIN
};



/**
* Singleton class for sound
*/
class tcSound  
{
public:
    static tcSound* Get();

    bool GetMusicPause() const;
    bool IsMusicStarted() const;
    void PlayEffect(const std::string& effectName);
    void PlayMusic(int anTrack);
    void PlayMusic(const std::string& song);
    void QueueMusic(const std::string& song);
    void QueueRandomMusic();
    void SeekMusic(double seekTime);
    void SetMusicPause(bool state);

    void SetEffectVolume(float volume);
    void SetMusicVolume(float volume);

    void StopMusic(int anTrack);
    void StopMusic();
    void PlayRandomMusic();
    void UpdateAutoMusic(double afStatusTime);
    void Test();
    void Update();

    bool Init();
    void UnInit();

#if 0
    // 3D sound methods
    osg::ref_ptr<osgAL::SoundNode> CreateSound(const std::string& file);

    osgAL::SoundRoot* GetSoundRoot();
    void InitOsgAL();
    void SetListenerDirection(const osg::Vec3& dir); 

    /// Set the transformation matrix for the listener
    void SetListenerMatrix(const osg::Matrix& matrix);
#endif

private: 
    tcSound();
    tcSound(const tcSound& source);
    ~tcSound();

    struct EffectInfo
    {
        size_t eventCount;
        unsigned int lastUpdate;
        unsigned int limitCount; ///< max number of these to allow per limitInterval
        unsigned int limitInterval; ///< reset eventCount at this time interval
    };

    std::map<std::string, openalpp::ref_ptr<openalpp::Sample> > effectMap;
    std::map<std::string, EffectInfo> effectStatus;

    /// buffer of openalpp::Source to use for non-directional sound effects
    std::vector<openalpp::ref_ptr<openalpp::Source> > effectBuffer;

    /// fifo of indices of available effectSounds
    std::deque<size_t> available;
    bool bufferAvailable[N_EFFECT_BUFFERS];

    tcOggStreamer *oggStreamer; ///< class for streaming Ogg music

    bool mbInitialized;
    int mnCurrentTrack;
    double mfLastMusicChange;
    teMusicState meMusicState;
    float effectVolume; ///< 0 to 1.0
    unsigned int lastEffectStatusUpdate;

   // osg::ref_ptr<osgAL::SoundRoot> soundRoot; ///< for 3D sound with osgAL

    void LoadXml();
    int GetEffectBuffer();
    void InitOpenAL();
    openalpp::Sample* LoadSample(const std::string& file);
    void ReleaseEffectBuffer(int bufferIdx);
    void ReleaseStoppedBuffers();
    void UpdateEffectStatus();
};

#endif 
