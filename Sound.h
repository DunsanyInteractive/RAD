/*
 *  Sound.h
 *  Rad Adventure Development
 *
 *  Created by Enda McNally.
 *  Copyright 2010 Dunsany Interactive. All rights reserved.
 *
 */
#ifndef SOUND_H
#define SOUND_H

#include <AL/al.h>
#include <string>

class Sound
{
public:
    Sound();
    // sound initializer which takes sound file name

    Sound(std::string);	/* Takes in name of sound file */
    ~Sound();

    // all these should have lower case first letters
    ALuint loadFile(std::string);
    void setLoop(bool);
    void setPitch(float);
    void setGain(float);
    void setSourcePos(float[]);
    void setSourceVel(float[]);
    void setOffsetSecs(int);
    void setBufferToSource(ALuint, ALuint);
    bool pause(); // New

    void reset(); // New
    bool stop();

    void sortqueue();

    static bool Play(std::string);

    bool play();

    void setSettings(float [], float [], bool, float, float, int);
    void test(); //  Should be taken out, test should be in sound manager if anywhere

    ALuint buffer;
    ALuint source;

    ALvoid playSource();

    ALenum stateOfBuffer();
};

#endif
