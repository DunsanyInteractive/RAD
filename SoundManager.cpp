/*
 *  SoundManager.cpp
 *  Rad Adventure Development
 *
 *  Created by Enda McNally.
 *  Copyright 2010 Dunsany Interactive. All rights reserved.
 *
 */
#include <iostream>
#include <list>
#include <map>


#include "Game.h"

#include "SoundManager.h"

#define SAFE_DELETE(p)	{if (p)	{ delete (p); (p) = NULL; } }

Sound *SM::sound;
namespace SoundManager
{
std::map<std::string, ALuint> soundMap;
vorbis_info*    vorbisInfo;
vorbis_comment* vorbisComment;

ALuint staticSource;
ALuint staticBuffer;


ALuint source;

ALfloat sourceVel[] = {0.0, 0.0, 0.0};
ALfloat sourcePos[] = {0.0, 0.0, 0.0};
ALfloat listenerVel[] = {0.0, 0.0, 0.0};
ALfloat listenerPos[] = {0.0, 0.0, 0.0};
ALfloat ListenerOrient[] = {0.0, 0.0, -1.0, 0.0, 1.0, 0.0};

/* Not used yet, but thought they should be kept as globals */
ALCdevice *device;
ALCcontext *context;

//Ogg Variables
FILE* oggFile;
OggVorbis_File oggStream;
ALuint oggbuffers[2];


ALenum format;

void init()
{
    ALCdevice *device;
    ALCcontext *context;

    device = alcOpenDevice(NULL);
    if (device == NULL) {
        std::cout << "Device error" << std::endl;
    }
    alcGetError(device);

    context = alcCreateContext(device, NULL);
    if (!context) {
        std::cout << "Context error" << std::endl;
    }

    alcMakeContextCurrent(context);
    alGetError();
}

void flush()
{
    std::map<std::string, ALuint>::iterator soundIter;

    if (!soundMap.empty())
    {
        soundIter = soundMap.begin();
        while(soundIter != soundMap.end());
        {
            alDeleteBuffers(1, (const ALuint *)(*soundIter).second);
            soundIter++;
        }
    }
}

void clean()
{

}

ALuint LoadALData(std::string* audioTrack)
{
    /*Local OpenAl Variable Declarations*/
    std::map<std::string, ALuint>::iterator soundIter;
    ALenum format;
    ALsizei size;
    ALsizei freq;
    ALuint wavbuffer;

    if (loadWavFile(*audioTrack, &wavbuffer, &size, &freq, &format))
        soundMap[*audioTrack] = wavbuffer;
    else {
        std::cout << "Having an issue loadiing a wave file. Please make sure that the path and file are correct." << std::endl;
        wavbuffer = NULL;
    }
    return wavbuffer;
}

ALuint* setSourceNumber(int count)
{
    alGenSources(1, &staticSource);
    errorCheck();
    return &source;
}

void release()
{
    alSourceStop(source);
    empty();
    alDeleteSources(1, &source);
    errorCheck();
    alDeleteBuffers(1, oggbuffers);
    errorCheck();

    ov_clear(&oggStream);
}

void empty()
{
    int queued;

    alGetSourcei(source, AL_BUFFERS_QUEUED, &queued);

    while(queued--)
    {
        ALuint buffer;

        alSourceUnqueueBuffers(source, 1, &buffer);
        errorCheck();
    }
}

void KillALData()
{
    flush();
    /*	for (int i = 0; i < bufferCount; i++)
    	{
    	//	alDeleteBuffers(1, &wavbuffer);
    		alDeleteSources(1, &source);
    	}*/
}

void SetListenerValues()
{
    alListenerfv(AL_POSITION, listenerPos);
    alListenerfv(AL_VELOCITY, listenerVel);
    alListenerfv(AL_ORIENTATION, ListenerOrient);
}
void PauseSingleStatic(ALuint bufferChosen)
{
    alSourcePause(source);
}

void StopSingleStatic(ALuint bufferChosen)
{
    alSourceStop(source);
}

ALuint getSources()
{
    return source;
}

void streamOgg()
{
    openFile("Audio/Media/1812 Overture - V For Vendetta.ogg");
}

void openFile(std::string path)
{
    int result;

    if(!(oggFile = fopen(path.c_str(), "rb")))
        throw std::string("Could not open Ogg file.");

    if((result = ov_open(oggFile, &oggStream, NULL, 0)) < 0)
    {
        fclose(oggFile);

        throw std::string("Could not open Ogg stream. ") + errorString(result);
    }

    vorbisInfo = ov_info(&oggStream, -1);
    vorbisComment = ov_comment(&oggStream, -1);

    if(vorbisInfo->channels == 1)
        format = AL_FORMAT_MONO16;
    else
        format = AL_FORMAT_STEREO16;


    alGenBuffers(2, oggbuffers);
    errorCheck();
    alGenSources(1, &source);
    errorCheck();

    alSource3f(source, AL_POSITION,        0.0, 0.0, 0.0);
    alSource3f(source, AL_VELOCITY,        0.0, 0.0, 0.0);
    alSource3f(source, AL_DIRECTION,       0.0, 0.0, 0.0);
    alSourcef (source, AL_ROLLOFF_FACTOR,  0.0          );
    alSourcei (source, AL_SOURCE_RELATIVE, AL_TRUE      );
}

void clearBuffers()
{
    int queuedItems;

    alGetSourcei(source, AL_BUFFERS_QUEUED, &queuedItems);

    while(queuedItems--)
    {
        ALuint buffer;

        alSourceUnqueueBuffers(source, 1, &buffer);
        errorCheck();
    }

}

bool cleanUpQueue(ALuint buffer)
{
    char allocSize[BUFFERSIZE];
    int size = 0;
    int section;
    int result;
    while(size < BUFFERSIZE)
    {
        result = ov_read(&oggStream, allocSize + size, BUFFERSIZE - size, 0, 2, 1, &section);

        if(result > 0)
            size += result;
        else if(result < 0)
            throw errorString(result);
        else
            break;
    }
    return true;
}


bool PlayCheck()
{
    ALenum state;

    alGetSourcei(source, AL_SOURCE_STATE, &state);

    return (state == AL_PLAYING);
}

void errorCheck()
{
    int error = alGetError();

    if(error != AL_NO_ERROR)
        throw std::string("OpenAL error was raised.");
}


std::string errorString(int code)
{
    switch(code)
    {
    case OV_EREAD:
        return std::string("Read from media.");
    case OV_ENOTVORBIS:
        return std::string("Not Vorbis data.");
    case OV_EVERSION:
        return std::string("Vorbis version mismatch.");
    case OV_EBADHEADER:
        return std::string("Invalid Vorbis header.");
    case OV_EFAULT:
        return std::string("Internal logic fault (bug or heap/stack corruption.");
    default:
        return std::string("Unknown Ogg error.");
    }
}

bool playing()
{
    ALenum state;
    alGetSourcei(source, AL_SOURCE_STATE, &state);
    return (state == AL_PLAYING);
}

bool update()
{
    int processed;
    bool active = true;
    alGetSourcei(source, AL_BUFFERS_PROCESSED, &processed);
    while(processed--)
    {
        ALuint buffer;
        alSourceUnqueueBuffers(source, 1, &buffer);
        errorCheck();

        active = cleanUpQueue(buffer);
        alSourceQueueBuffers(source, 1, &buffer);
        errorCheck();
    }

    return active;
}

bool playback()
{
    if(playing())
        return true;

    if(!cleanUpQueue(oggbuffers[0]))
        return false;

    if(!cleanUpQueue(oggbuffers[1]))
        return false;

    alSourceQueueBuffers(source, 2, oggbuffers);
    alSourcePlay(source);

    return true;
}

void playOGG()
{

    openFile("Audio/Media/1812 Overture - V For Vendetta.ogg");

    if(!playback())
        std::cout << "oggStream refused to play";

    while(update())
    {
        if(!playing())
        {
            if(!playback())
                std::cout << "ogg stopped suddenly" << std::endl;
            else
                std::cout << "ogg was interrupted" << std::endl;
        }
        std::cout << "normal termination";
    }
    release();
}

/*
 *Struct that holds the RIFF data of the Wave file. The RIFF data is the meta data information
 *that holds, the ID, size and format of the wave file
 */
struct RIFF_Header {
    char chunkID[4];
    long chunkSize; // size of the file not including chunkSize and chunkID
    char format[4];

    void printFormat() {
        std::cout << "The format is : " << format << std::endl;
    }
};

/*
 * Struct to hold fmt subchunk data for WAVE files.
 */
struct WAVE_Format {
    char subChunkID[4];
    long subChunkSize;
    short audioFormat; // PCM = 1
    short numChannels;
    long sampleRate;
    long byteRate; // == sampleRate * numChannels * bitsPerSample / 8
    short blockAlign; // == numChannels * bitsPerSample / 8
    short bitsPerSample;
};

/*
 * Struct to hold the data of the wave file
 */
struct WAVE_Data {
    char subChunkID[4]; //should contain the word data
    long subChunk2Size; // == numSamples * numChannels * bitsPerSample/8
};

//TODO (Oliver) Also do proper checks to see if the data is correct

/*
 * Load wave file function. Bypasses
}	 */
bool loadWavFile(const std::string filename, ALuint* buffer, ALsizei* size, ALsizei* frequency, ALenum* format) {

    FILE* soundFile = NULL;
    WAVE_Format wave_format;
    RIFF_Header riff_header;
    WAVE_Data wave_data;
    unsigned char* data;
    std::string path = "Assets/Media/" + filename;

    try {
        soundFile = fopen(path.c_str(), "rb");
        if (!soundFile)
            throw (filename);

        // Read in the first chunk into the struct
        fread(&riff_header, sizeof(RIFF_Header), 1, soundFile);
        if ((riff_header.chunkID[0] != 'R' || riff_header.chunkID[1] != 'I' ||  //check for RIFF tag in memeory
                riff_header.chunkID[2] != 'F' || riff_header.chunkID[3] != 'F') &&
                (riff_header.format[0] != 'W' || riff_header.format[1] != 'A' ||	//check for WAVE tag in memory
                 riff_header.format[2] != 'V' || riff_header.format[3] != 'E'))
            throw ("Invalid RIFF or WAVE Header");

        // Read in the 2nd chunk for the wave info
        fread(&wave_format, sizeof(WAVE_Format), 1, soundFile);
        if (wave_format.subChunkID[0] != 'f' || wave_format.subChunkID[1] != 'm' ||	//check for fmt tag in memory
                wave_format.subChunkID[2] != 't' || wave_format.subChunkID[3] != ' ')
            throw ("Invalid Wave Format");

        //check for extra parameters;
        if (wave_format.subChunkSize > 16)
            fseek(soundFile, sizeof(short), SEEK_CUR);

        // Read in the the last byte of data before the sound file
        fread(&wave_data, sizeof(WAVE_Data), 1, soundFile);
        if (wave_data.subChunkID[0] != 'd' || wave_data.subChunkID[1] != 'a' ||	//check for data tag in memory
                wave_data.subChunkID[2] != 't' || wave_data.subChunkID[3] != 'a')
            throw ("Invalid data header");

        //Allocate memory for data
        data = new unsigned char[wave_data.subChunk2Size];
        // Read in the sound data into the soundData variable
        if (!fread(data, wave_data.subChunk2Size, 1, soundFile))
            throw ("error loading WAVE data into struct!");
        *size = wave_data.subChunk2Size;
        *frequency = wave_format.sampleRate;

        if (wave_format.numChannels == 1) {
            if (wave_format.bitsPerSample == 8)
                *format = AL_FORMAT_MONO8;
            else if (wave_format.bitsPerSample == 16)
                *format = AL_FORMAT_MONO16;
        } else if (wave_format.numChannels == 2) {
            if (wave_format.bitsPerSample == 8)
                *format = AL_FORMAT_STEREO8;
            else if (wave_format.bitsPerSample == 16)
                *format = AL_FORMAT_STEREO16;
        }

        alGenBuffers(1, buffer);
        errorCheck();
        alBufferData( *buffer, *format, (void*)data, *size, *frequency);
        errorCheck();

        fclose(soundFile);
        return true;
    } catch(std::string error) {
        std::cout << error << " : trying to load " << filename << std::endl;
        //clean up memory if wave loading fails
        if (soundFile != NULL)
            fclose(soundFile);
        return false;
    }
}
}
