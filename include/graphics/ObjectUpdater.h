/** 
**  @file ObjectUpdater.h 
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

#ifndef _OBJECTUPDATER_H_
#define _OBJECTUPDATER_H_


class tc3DModel;
class tc3DViewer;
class tcSimState;
class tcSensorMap;
class tcGameObject;
class tcSensorMapTrack;


/**
* Updates 3D position and attitude of object based on
* data in attached tcGameObject and tc3DViewer.
* The interface with tc3DViewer is circular and should
* be reworked eventually.
*/
class ObjectUpdater
{
public:
	/// info needed to locate and orient model within world 
	struct LocationParams
	{
		float x;
		float y;
		float z;
		float yaw;
		float pitch;
		float roll;
		bool isVisible;
	};

    static void AttachViewer(tc3DViewer *v) {viewer = v;}
    static ObjectUpdater* Get();
    static void GetLocationParams(tcGameObject* gameObj, LocationParams& p);
    static void GetLocationParams(tcSensorMapTrack* sensorTrack, LocationParams& p);
    static float GetLastDistanceFromCamera();

    void Update(tcGameObject* obj);
    void Update(tcSensorMapTrack* sensorTrack);

private:
    ObjectUpdater();
    virtual ~ObjectUpdater();

    static tc3DViewer* viewer;
	static tcSimState* simState;
	static tcSensorMap* sensorMap;
    static float distanceFromCamera;


	void UpdateAnimations(tcGameObject* obj);
	void UpdateTrackAnimations();
	void UpdateTrack();
	void UpdateTrue();

};

#endif

