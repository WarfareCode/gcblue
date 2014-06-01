/**
**  @file tcSound.cpp
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
#include "wx/wx.h"
#ifdef WIN32
#include "wx/msw/private.h" // for MS Windows specific definitions
#endif
#endif

#include "wx/dir.h"
#include "tcSound.h"
#include "tcOggStreamer.h"
#include "tcOptions.h"
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include "simmath.h"
#include "wx/xml/xml.h"
#include "tcTime.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif 

using openalpp::Source;

/* With the "Enable minimum rebuild option" compiler error C1055 out of keys occurs
** with this file and several graphics files. The error started occuring after modifications
** related to the FlightPort and platform script interface (added HasFlightPort() I think).
** But these mods had nothing to do with the files with C1055 problems. Based on google 
** search the problem seems to be a compiler bug vs. a problem with the code. 
*/


bool tcSound::GetMusicPause() const
{
    //wxASSERT(oggStreamer);
    if (!oggStreamer) return false;
    return oggStreamer->GetPause();
}




/**
*
*/
openalpp::Sample* tcSound::LoadSample(const std::string& file)
{
    static std::string pathPrefix("sound\\wav\\");

    std::string filePath = pathPrefix + file;

    // Create a sample, load a .wav file.
	try
	{
		openalpp::Sample* sample = new openalpp::Sample(filePath);
		return sample;
	}
	catch (openalpp::FileError e)
	{
		fprintf(stderr, "tcSound::LoadSample - %s\n", e.what());
		return 0;
	}

   
}

/**
* Load effect map and sound config info from xml
*/
void tcSound::LoadXml()
{
    wxString fileName = "xml/sound_effect.xml";
    wxXmlDocument doc;
    if (!doc.Load(fileName))
    {
        wxString errorMsg;
        errorMsg.Printf("Error loading sound xml file: %s", fileName.c_str());
        fprintf(stderr, errorMsg.c_str());
        wxMessageBox(errorMsg, "Error", wxICON_ERROR);
        return;
    }

    wxXmlNode* root = doc.GetRoot();
    if ((root == 0) || (root->GetName() != "sound_config"))
    {
        wxString errorMsg;
        errorMsg.Printf("Error loading sound xml file: %s", fileName.c_str());
        fprintf(stderr, errorMsg.c_str());
        wxMessageBox(errorMsg, "Error", wxICON_ERROR);
        return;
    }


    wxXmlNode* child = root->GetChildren();
    while (child != 0)
    {
        if (child->GetName() == "effect")
        {
            std::string effectName = std::string(child->GetPropVal("name", "").c_str());
            std::string fileName = std::string(child->GetPropVal("file", "").c_str());
            wxString maxCount = child->GetPropVal("max_count", "99");
            wxString timeInterval = child->GetPropVal("time_interval", "1.0");

            unsigned long nMaxCount = 99;
            maxCount.ToULong(&nMaxCount);
            
            double timeInterval_s = 1.0;
            timeInterval.ToDouble(&timeInterval_s);

            if ((effectName.size() > 0) && (fileName.size() > 0))
            {
                EffectInfo info;
                info.eventCount = 0;
                info.lastUpdate = 0;
                info.limitCount = nMaxCount;
                info.limitInterval = unsigned int(ceil(30.0 * timeInterval_s)); // convert to 30 Hz tics

                effectMap[effectName] = LoadSample(fileName);
                effectStatus[effectName] = info;
            }
        }
        child = child->GetNext();
    }

}

bool tcSound::Init() 
{
	try
	{
		InitOpenAL();
	}
	catch (openalpp::InitError e)
	{
		e.what();
		wxMessageBox(e.what(), 
			"Error", wxICON_ERROR);
		throw e;
	}

    LoadXml();

 //   effectMap["Explosion"] = LoadSample("Explosion.wav");
 //   effectMap["Implosion"] = LoadSample("Implosion.wav");
 //   effectMap["ShortBeep"] = LoadSample("ShortBeep.wav");
 //   effectMap["MissileLaunch"] = LoadSample("MissileLaunch.wav");
 //   effectMap["TwoBeeps"] = LoadSample("TwoBeeps.wav");
 //   effectMap["consolebeep"] = LoadSample("consolebeep.wav");
 //   effectMap["Beep2"] = LoadSample("Beep2.wav");
 //   effectMap["RejectBeep"] = LoadSample("RejectBeep.wav");
 //   effectMap["Ping"] = LoadSample("Ping.wav");
 //   effectMap["Ping2"] = LoadSample("Ping2.wav");
 //   effectMap["radarping"] = LoadSample("radarping.wav");
 //   effectMap["LowBeep"] = LoadSample("LowBeep.wav");
 //   effectMap["Bloop"] = LoadSample("Bloop.wav");
 //   effectMap["NoisyBeepLow"] = LoadSample("NoisyBeepLow.wav");
 //   effectMap["Thuck"] = LoadSample("Thuck.wav");
 //   effectMap["Explosion2"] = LoadSample("Explosion2.wav");
 //   effectMap["Welcome"] = LoadSample("NavyWhistle.wav");
 //   effectMap["jetlaunch"] = LoadSample("jetlaunch.wav");
 //   effectMap["MutedBeep"] = LoadSample("MutedBeep.wav");
 //   effectMap["intercom"] = LoadSample("intercom.wav");
 //   effectMap["fslide"] = LoadSample("fslide.wav");
	//effectMap["NavalGun1"] = LoadSample("NavalGun1.wav");
	//effectMap["helolaunch"] = LoadSample("helolaunch.wav");
	//effectMap["radar_on"] = LoadSample("radar_on.wav");
	//effectMap["radar_off"] = LoadSample("radar_off.wav");
 //   effectMap["torpedo_launch"] = LoadSample("torpedo_launch.wav");
 //   effectMap["shishding"] = LoadSample("shishding.wav");
 //   effectMap["Gatling"] = LoadSample("gatling.wav");
 //   effectMap["Alarm"] = LoadSample("alarm.wav");
    
    SetMusicVolume(0.5f);

    mbInitialized = true;
    return true;
}



/**
* Initialization associated with osgAL. Should be called once at
* startup.
*/
void tcSound::InitOpenAL()
{
	fprintf(stdout, "InitOpenAL - Initializing buffer ");

    wxASSERT(available.size() == 0);
    wxASSERT(effectBuffer.size() == 0);

    // create Sources's to use as buffers
    for (size_t n=0; n<N_EFFECT_BUFFERS; n++)
    {		
		fprintf(stdout, "%d", n);
        wxString stateName = wxString::Format("state%d", n);

        openalpp::ref_ptr<Source> source(new Source);
        fprintf(stdout, ".");
        source->stop();
		fprintf(stdout, ".");
        source->setAmbient();
		fprintf(stdout, ".");
        source->setGain(0.5f); // volume
		fprintf(stdout, ".");
        source->setLooping(false);
		fprintf(stdout, ".");
    
        effectBuffer.push_back(source);
        available.push_back(n);
        bufferAvailable[n] = true;

    }
	fprintf(stdout, "\n");
}

bool tcSound::IsMusicStarted() const
{
    return (meMusicState != MS_STOPPED);
}


void tcSound::Test() 
{
    //oggStreamer->Queue("sound\\ogg\\gcb_theme2.ogg");

    //while (true)
    //{
    //    int jj = 4;
    //    jj++;
    //    oggStreamer->Update();
    //}
    // int nTestEffect = "ShortBeep";
    /*  int nTestEffect = "RejectBeep";
    if (!mbInitialized) return;
    PlayEffect(nTestEffect);
    */
}


void tcSound::PlayMusic(int anTrack) 
{   
    /*
    int isize;
    if (!mbInitialized) return;
 
    if ((anTrack<0)||(anTrack>=N_MUSIC_BUFFERS)) return;
    if(isize>0)
    {
        mnCurrentTrack = anTrack;
        meMusicState = MS_WAIT;
    }
    */
}

void tcSound::PlayMusic(const std::string& song) 
{   
    if (!mbInitialized) return;
    if (!oggStreamer) return;

    std::string musicPath = OGG_PATH;
    musicPath += song;
    musicPath += ".ogg";
    meMusicState = MS_WAIT;
    oggStreamer->Open(musicPath);

    // oggStreamer->Display(); // uncomment to log ogg info to stdout
    //oggStreamer->Play();
    oggStreamer->SetPause(false);
}

void tcSound::QueueMusic(const std::string& song)
{
    if (!mbInitialized) return;
    if (oggStreamer) oggStreamer->Queue(song);
}

void tcSound::QueueRandomMusic()
{
    if (!mbInitialized) return;
    if (!oggStreamer) return;

    wxArrayString fileList;
    int fileCount = (int)wxDir::GetAllFiles(OGG_PATH, &fileList, "*.ogg", wxDIR_FILES);
    if (fileCount == 0) return; // return if no music files found
    int randIdx = rand() % fileCount;
    wxString fileName = fileList[randIdx];
    const char *buff = fileName.GetData();
    oggStreamer->Queue(buff);
}

void tcSound::SeekMusic(double seekTime)
{
    if (!mbInitialized) return;
    if (oggStreamer) oggStreamer->Seek(seekTime);
}

void tcSound::SetEffectVolume(float volume)
{
    effectVolume = volume;
}

void tcSound::SetMusicPause(bool state)
{
    if (!mbInitialized) return;
    if (oggStreamer) oggStreamer->SetPause(state);
}



void tcSound::SetMusicVolume(float volume)
{
    if (!mbInitialized) return;
    if (oggStreamer) oggStreamer->SetVolume(volume);
}


void tcSound::StopMusic(int anTrack) 
{
    if (!mbInitialized) return;
//    if ((anTrack<0)||(anTrack>=N_MUSIC_BUFFERS)) return;
    mnCurrentTrack = -1;
    meMusicState = MS_STOPPED;
}


void tcSound::StopMusic() 
{
    if (!mbInitialized) return;
    if (meMusicState != MS_STOPPED) 
    {
        StopMusic(mnCurrentTrack);
        if (oggStreamer) oggStreamer->Stop();
    }
}


void tcSound::PlayRandomMusic(void) 
{
    /*
    int nTrack = rand() % N_SMUSIC;
    if(mnCurrentTrack!=-1) {StopMusic(mnCurrentTrack);}
    PlayMusic(nTrack);
    */
}

/**
* Should be periodically called from top level to update sound effect timeouts
*/
void tcSound::Update()
{
    UpdateEffectStatus();
}


void tcSound::UpdateAutoMusic(double afStatusTime) 
{
    if (!mbInitialized) return;
    if (!oggStreamer) return;

    if (meMusicState == MS_STOPPED) return;

    if (oggStreamer->IsPaused())
    {
        oggStreamer->Play();
    }
//    bool isPlaying = oggStreamer->IsPlaying();
	if (!oggStreamer->IsSongQueued() && (tcOptions::Get()->mbPlayMusic))
    {
        QueueRandomMusic();
    }

    oggStreamer->Update();

   // oggStreamer->Playback();

    /*  int nTrack;
    long nVolume;
    DWORD nPlayCursor; 
    static DWORD nLastPlayCursor = 0;

    switch (meMusicState) {
    case MS_WAIT: // do nothing for a while
    if ((afStatusTime - mfLastMusicChange) > 5.0f) {
    mfLastMusicChange = afStatusTime;
    if (mnCurrentTrack!=-1) {
    BufferMusic[mnCurrentTrack]->GetCurrentPosition(&nLastPlayCursor,NULL);
    }
    meMusicState = MS_NEWCHANGE;
    }
    break;
    case MS_NEWCHANGE: // wait till end of track to apply
    if (mnCurrentTrack==-1) {
    nTrack = rand() % N_SMUSIC;
    PlayMusic(nTrack);
    mfLastMusicChange = afStatusTime;
    meMusicState = MS_WAIT;
    return;
    }
    if ((afStatusTime - mfLastMusicChange) > 0.1f) {
    mfLastMusicChange = afStatusTime;
    BufferMusic[mnCurrentTrack]->GetCurrentPosition(&nPlayCursor,NULL);
    if (nPlayCursor<nLastPlayCursor) {
    switch (rand()%2) {
    case 0:
    nTrack = rand() % N_SMUSIC;
    if (nTrack != mnCurrentTrack) {
    StopMusic(mnCurrentTrack);
    PlayMusic(nTrack);
    }
    meMusicState = MS_WAIT;
    break;
    case 1:
    meMusicState = MS_FADEOUT;
    break;
    }
    }
    else {
    nLastPlayCursor = nPlayCursor;
    }

    //if ((rand()%3)==0) {meMusicState = MS_FADEOUT;}
    }
    break;
    case MS_FADEOUT:
    if ((afStatusTime - mfLastMusicChange) > 0.5f) {
    mfLastMusicChange = afStatusTime;
    BufferMusic[mnCurrentTrack]->GetVolume(&nVolume);
    BufferMusic[mnCurrentTrack]->SetVolume(nVolume-100);
    if (nVolume < -2800) {
    StopMusic(mnCurrentTrack);
    meMusicState = MS_WAIT;
    }
    }
    break;
    case MS_FADEIN:
    break;
    }

    */
}

void tcSound::UpdateEffectStatus()
{
    unsigned int t = tcTime::Get()->GetUpdated30HzCount();

    if ((t - lastEffectStatusUpdate) <= 30) return;
    lastEffectStatusUpdate = t;

    std::map<std::string, EffectInfo>::iterator iter;

    for (iter=effectStatus.begin(); iter!=effectStatus.end(); ++iter)
    {
        unsigned int dt = t - iter->second.lastUpdate;
        if (dt > iter->second.limitInterval)
        {
            iter->second.eventCount = 0;
            iter->second.lastUpdate = t;
        }
    }
}

/**
*
*/
void tcSound::ReleaseStoppedBuffers() 
{
    for(size_t i=0; i<effectBuffer.size(); i++)
    {
        openalpp::SourceState bufferState = effectBuffer[i]->getState();
        if ((bufferState != openalpp::Playing) && (!bufferAvailable[i]))
        {
            if (bufferState == openalpp::Stopped)
            {
                ReleaseEffectBuffer(i);
            }
            else
            {
                effectBuffer[i]->stop(); /// previous Sample remains in buffer until reset    
            }
        }
    }
}


/**
* @returns -1 if none available, otherwise returns index to use
*/
int tcSound::GetEffectBuffer() 
{
    if (available.size() < 4) 
    {
        ReleaseStoppedBuffers();
    }

    if (available.size() == 0) {return -1;}

    // take index from front of queue
    size_t idx = (size_t)available.front();
    available.pop_front();
    bufferAvailable[idx] = false;

    return idx;
}


void tcSound::ReleaseEffectBuffer(int bufferIdx) 
{
    if ((bufferIdx < 0)||(bufferIdx >= (int)effectBuffer.size())) {return;} // error, out of range

    wxASSERT(available.size() <= N_EFFECT_BUFFERS);
    wxASSERT(effectBuffer[bufferIdx].valid());
    wxASSERT(effectBuffer[bufferIdx]->getState() == openalpp::Stopped);

    available.push_back((size_t)bufferIdx);
    bufferAvailable[bufferIdx] = true;
}


void tcSound::PlayEffect(const std::string& effectName)
{
    if (!mbInitialized) return;
    if (effectName.length() == 0) return;

    ReleaseStoppedBuffers();

    std::map<std::string, openalpp::ref_ptr<openalpp::Sample> >::iterator mapIter;

    mapIter = effectMap.find(effectName);
    if (mapIter == effectMap.end())
    {
        fprintf(stderr, "Error - tcSound::PlayEffect - effectName (%s) not found in map.\n",
            effectName.c_str());
        return;
    }
    openalpp::Sample* sample = mapIter->second.get();

    int nFreeBufferIdx = GetEffectBuffer(); // returns -1 if none available
    if ((nFreeBufferIdx < 0)||(nFreeBufferIdx >= (int)effectBuffer.size())) 
    {
        return;
    }

    std::map<std::string, EffectInfo>::iterator statusIter = effectStatus.find(effectName);
    if (statusIter != effectStatus.end())
    {
        EffectInfo& status = statusIter->second;
        status.eventCount++;

        if (status.eventCount > status.limitCount)
        {
            return;
        }
    }

    openalpp::Source* source = effectBuffer[nFreeBufferIdx].get();
    wxASSERT(source);
    source->setSound(sample);
    source->setGain(effectVolume);
    float pitchFactor = 1.0f + randfc(0.02f);
    source->setPitch(pitchFactor);
    source->play();
}





void tcSound::UnInit() 
{
    if (!mbInitialized) return;

    //effectBuffer.clear();

    std::map<std::string, openalpp::Sample*>::iterator iter;

    /** mem leak?
    for (iter = effectMap.begin(); iter != effectMap.end(); ++iter)
    {
        delete iter->second;
    }
    */

    //effectMap.clear();

    //osgAL::SoundManager::instance()->shutdown();

    mbInitialized = false;

}

/**
* Method for accessing singleton instance.
*/
tcSound* tcSound::Get()
{
    static tcSound instance;

    return &instance;
}

tcSound::tcSound()
:  mbInitialized(false),
   mnCurrentTrack(-1),
   mfLastMusicChange(0),
   meMusicState(MS_STOPPED),
   effectVolume(1.0f),
   lastEffectStatusUpdate(0)
{
    std::cout << "Creating OGG streamer" << std::endl;
    oggStreamer = new tcOggStreamer();
    std::cout << "Success - Create OGG streamer" << std::endl;
}


/**
* Should never be called.
*/
tcSound::tcSound(const tcSound& source)
{
    wxASSERT(false);
}

tcSound::~tcSound() 
{
    if (oggStreamer) delete oggStreamer;

}


