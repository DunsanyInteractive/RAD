/*
 *  SoundManager.h
 *  Rad Adventure Development
 *
 *  Created by Enda McNally.
 *  Copyright 2010 Dunsany Interactive. All rights reserved.
 *
 */
#ifndef _SOUND_MANAGER_H_
#define _SOUND_MANAGER_H_

#define NUMBUFFERS              (4)

#include <AL/al.h>
#include <AL/alc.h>
#include <string>
#include <vorbis/vorbisfile.h>
#include "Sound.h"

#define BUFFERSIZE (4096 * 4)
class Sound;
namespace SoundManager
{
extern ALuint source;
extern ALuint staticSource;
extern ALuint staticBuffer;

extern ALfloat sourceVel[]; // velocity of the source
extern ALfloat sourcePos[]; // position of the source
extern ALfloat listenerVel[]; // velocity of the listener
extern ALfloat listenerPos[];	// position of the listener
// Listener Orientation = the direction the camera is pointed and the direction up is for the camera. (i.e 0,0,-1 (point of origin) and 0, 1, 0 (up on the y axis)
extern ALfloat ListenerOrient[];

void init();
void clean();

ALuint LoadALData(std::string *);
ALuint* setSourceNumber(int count);
void loadAudioFile();// contains variables needed to store info that Alut gives us
void SetListenerValues(); //useful for if the listener moves position/velocity/orientation
void KillALData(); //for shutdown procedure
int PlayStatic(ALuint, ALboolean, ALint);
void PauseSingleStatic(ALuint);
void StopSingleStatic(ALuint);
ALuint getSources();
bool PlayCheck();

bool loadWavFile(const std::string filename, ALuint* buffer, ALsizei* size, ALsizei* frequency, ALenum* format);

extern Sound *sound;

//Ogg Variables
extern OggVorbis_File oggStream;
extern ALuint oggbuffers[2];
extern ALuint source;
extern ALenum format;



//OGG Functions
//	void streamOgg();
void openFile(std::string);
//	void releaseFile();
void errorCheck();
std::string errorString(int);
void playOGG();
void release();
void empty();

};
namespace SM = SoundManager;
#endif
