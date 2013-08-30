/*
 *  Sound.cpp
 *  Rad Adventure Development
 *
 *  Created by Enda McNally.
 *  Copyright 2010 Dunsany Interactive. All rights reserved.
 *
 */
#include "Sound.h"
#include <fstream>
#include <iostream>
#include "SoundManager.h"

ALuint		uiEffectSlot, uiEffect;
ALuint		uiSource, uiBuffer;
ALboolean	bEffectCreated = AL_FALSE;

ALuint buffer;
ALuint source;


Sound::Sound()
{

}

Sound::Sound(std::string audioFile)
{
    alGenBuffers(1, &buffer);
    buffer = loadFile(audioFile);
    if( !buffer )
        std::cout << "Problem loading sound file: " << (char *)audioFile.c_str() << std::endl;


    alGenSources(1, &source);
}

Sound::~Sound()
{

    alDeleteSources(1, &source);

}

ALuint Sound::loadFile(std::string audioFile)
{
    return SM::LoadALData(&audioFile);
}

void Sound::setLoop(bool loop)
{
    alSourcei (this->source, AL_LOOPING, loop);
}

void Sound::setPitch(float pitch)
{
    alSourcef(this->source, AL_PITCH, pitch);
}

void Sound::setGain(float gain)
{
    alSourcef(this->source, AL_GAIN, gain);
}

void Sound::setSourcePos(float sourcePos[])
{
    alSourcefv(this->source, AL_POSITION, sourcePos);
}

void Sound::setSourceVel(float sourceVel[])
{
    alSourcefv(this->source, AL_VELOCITY, sourceVel);
}

void Sound::setOffsetSecs(int seconds)
{
    alSourcei (this->source, AL_SEC_OFFSET, seconds);
}

void Sound::setBufferToSource(ALuint source, ALuint buffer)
{
    alSourcei(source, AL_BUFFER, buffer);
}

void Sound::setSettings(float sourceVel[] = NULL, float sourcePos[] = NULL, bool loop = false, float pitch = 1.0f, float gain = 1.0f, int offset = 0)
{

    this->setLoop(loop);
    ALuint error = alGetError();
    this->setPitch(pitch);
    error = alGetError();

    this->setGain(gain);
    error = alGetError();
    this->setOffsetSecs(offset);
    error = alGetError();
    //SetReverbEffect(eaxHangar);
}

bool Sound::Play(std::string fileName)
{
    SM::staticBuffer = SM::LoadALData(&fileName);
    ALuint error = alGetError();
    alGenSources(1, &SM::staticSource);
    alSourcei(SM::staticSource, AL_BUFFER, SM::staticBuffer);
    error = alGetError();


    alSourcefv(SM::staticSource, AL_POSITION, SM::sourcePos);
    error = alGetError();
    alSourcefv(SM::staticSource, AL_VELOCITY, SM::sourceVel);
    error = alGetError();
    alSourcePlay(SM::staticSource);
    error = alGetError();
    if(error == AL_NO_ERROR)
    {
        return AL_TRUE;
    }

    return AL_FALSE;
}

bool Sound::play()
{
    alSourcei(this->source, AL_BUFFER, this->buffer);
    ALuint error = alGetError();
    error = alGetError();
    alSourcePlay(this->source);
    error = alGetError();
    if(alGetError() == AL_NO_ERROR)
    {
        return AL_TRUE;
    }

    return AL_FALSE;
}

bool Sound::stop()
{
    alSourceStop(this->source);
    if (alGetError() == AL_NO_ERROR)
    {
        return AL_TRUE;
    }

    return AL_FALSE;
}

bool Sound::pause()
{
    alSourcePause(this->source);

    if (alGetError() == AL_NO_ERROR)
    {
        return AL_TRUE;
    }

    return AL_FALSE;
}


void Sound::test()
{
    //Play();
}


/*void Sound::SetReverbEffect(EAXREVERBPROPERTIES reverbType)
{
	this->CreateAuxSlot();

	if (bEffectCreated)
		{
			std::cout << "Playing Source with Send to 'Hangar' Reverb Effect" << std::endl;

			// Reverb Preset is stored in legacy format, use helper function to convert to EFX EAX Reverb
			ConvertReverbParameters(&eaxHangar, &efxReverb);

			// Set the Effect parameters
			if (!SetEFXEAXReverbProperties(&efxReverb, uiEffect))
				std::cout << "Failed to set Reverb Parameters" << std::endl;

			// Load Effect into Auxiliary Effect Slot
			alAuxiliaryEffectSloti(uiEffectSlot, AL_EFFECTSLOT_EFFECT, uiEffect);

			// Enable (non-filtered) Send from Source to Auxiliary Effect Slot
			alSource3i(SM::Source, AL_AUXILIARY_SEND_FILTER, uiEffectSlot, 0, AL_FILTER_NULL);
	}

}

void Sound::CreateAuxSlot()
{
	if (ALFWIsEFXSupported())
	{
		if (CreateAuxEffectSlot(&uiEffectSlot))
		{
			if (CreateEffect(&uiEffect, AL_EFFECT_EAXREVERB))
			{
				bEffectCreated = AL_TRUE;
			}
			else
			{
				std::cout << "Failed to Create an EAX Reverb Effect" << std::endl;
			}
		}
		else
		{
			std::cout << "Failed to generate an Auxilary Effect Slot" << std::endl;
		}

		std::cout << "Playing Source without Effects" << std::endl;
	}
}

ALboolean SetEffects(ALuint *uiEffect, ALenum EffectType)
{
	if (uiEffect)
	{
		alGetError();

		alGenEffects(1, uiEffect);
		if (alGetError() == AL_NO_ERROR)
		{
			alEffecti(*uiEffect, AL_EFFECT_TYPE, EffectType);
			if (alGetError() == AL_NO_ERROR)
				return AL_TRUE;
			else
			{
				alDeleteEffects(1, uiEffect);
				return AL_FALSE;
			}
		}
	}
	return AL_FALSE;
}



ALboolean ALFWIsEFXSupported()
{
	ALCdevice *pDevice = NULL;
	ALCcontext *pContext = NULL;
	ALboolean bEFXSupport = AL_FALSE;

	pContext = alcGetCurrentContext();
	pDevice = alcGetContextsDevice(pContext);

	if (alcIsExtensionPresent(pDevice, (ALCchar*)ALC_EXT_EFX_NAME))
	{
		alGenEffects = (LPALGENEFFECTS)alGetProcAddress("alGenEffects");
		alDeleteEffects = (LPALDELETEEFFECTS )alGetProcAddress("alDeleteEffects");
		alIsEffect = (LPALISEFFECT )alGetProcAddress("alIsEffect");
		alEffecti = (LPALEFFECTI)alGetProcAddress("alEffecti");
		alEffectiv = (LPALEFFECTIV)alGetProcAddress("alEffectiv");
		alEffectf = (LPALEFFECTF)alGetProcAddress("alEffectf");
		alEffectfv = (LPALEFFECTFV)alGetProcAddress("alEffectfv");
		alGetEffecti = (LPALGETEFFECTI)alGetProcAddress("alGetEffecti");
		alGetEffectiv = (LPALGETEFFECTIV)alGetProcAddress("alGetEffectiv");
		alGetEffectf = (LPALGETEFFECTF)alGetProcAddress("alGetEffectf");
		alGetEffectfv = (LPALGETEFFECTFV)alGetProcAddress("alGetEffectfv");
		alGenFilters = (LPALGENFILTERS)alGetProcAddress("alGenFilters");
		alDeleteFilters = (LPALDELETEFILTERS)alGetProcAddress("alDeleteFilters");
		alIsFilter = (LPALISFILTER)alGetProcAddress("alIsFilter");
		alFilteri = (LPALFILTERI)alGetProcAddress("alFilteri");
		alFilteriv = (LPALFILTERIV)alGetProcAddress("alFilteriv");
		alFilterf = (LPALFILTERF)alGetProcAddress("alFilterf");
		alFilterfv = (LPALFILTERFV)alGetProcAddress("alFilterfv");
		alGetFilteri = (LPALGETFILTERI )alGetProcAddress("alGetFilteri");
		alGetFilteriv= (LPALGETFILTERIV )alGetProcAddress("alGetFilteriv");
		alGetFilterf = (LPALGETFILTERF )alGetProcAddress("alGetFilterf");
		alGetFilterfv= (LPALGETFILTERFV )alGetProcAddress("alGetFilterfv");
		alGenAuxiliaryEffectSlots = (LPALGENAUXILIARYEFFECTSLOTS)alGetProcAddress("alGenAuxiliaryEffectSlots");
		alDeleteAuxiliaryEffectSlots = (LPALDELETEAUXILIARYEFFECTSLOTS)alGetProcAddress("alDeleteAuxiliaryEffectSlots");
		alIsAuxiliaryEffectSlot = (LPALISAUXILIARYEFFECTSLOT)alGetProcAddress("alIsAuxiliaryEffectSlot");
		alAuxiliaryEffectSloti = (LPALAUXILIARYEFFECTSLOTI)alGetProcAddress("alAuxiliaryEffectSloti");
		alAuxiliaryEffectSlotiv = (LPALAUXILIARYEFFECTSLOTIV)alGetProcAddress("alAuxiliaryEffectSlotiv");
		alAuxiliaryEffectSlotf = (LPALAUXILIARYEFFECTSLOTF)alGetProcAddress("alAuxiliaryEffectSlotf");
		alAuxiliaryEffectSlotfv = (LPALAUXILIARYEFFECTSLOTFV)alGetProcAddress("alAuxiliaryEffectSlotfv");
		alGetAuxiliaryEffectSloti = (LPALGETAUXILIARYEFFECTSLOTI)alGetProcAddress("alGetAuxiliaryEffectSloti");
		alGetAuxiliaryEffectSlotiv = (LPALGETAUXILIARYEFFECTSLOTIV)alGetProcAddress("alGetAuxiliaryEffectSlotiv");
		alGetAuxiliaryEffectSlotf = (LPALGETAUXILIARYEFFECTSLOTF)alGetProcAddress("alGetAuxiliaryEffectSlotf");
		alGetAuxiliaryEffectSlotfv = (LPALGETAUXILIARYEFFECTSLOTFV)alGetProcAddress("alGetAuxiliaryEffectSlotfv");

		if (alGenEffects &&	alDeleteEffects && alIsEffect && alEffecti && alEffectiv &&	alEffectf &&
			alEffectfv && alGetEffecti && alGetEffectiv && alGetEffectf && alGetEffectfv &&	alGenFilters &&
			alDeleteFilters && alIsFilter && alFilteri && alFilteriv &&	alFilterf && alFilterfv &&
			alGetFilteri &&	alGetFilteriv && alGetFilterf && alGetFilterfv && alGenAuxiliaryEffectSlots &&
			alDeleteAuxiliaryEffectSlots &&	alIsAuxiliaryEffectSlot && alAuxiliaryEffectSloti &&
			alAuxiliaryEffectSlotiv && alAuxiliaryEffectSlotf && alAuxiliaryEffectSlotfv &&
			alGetAuxiliaryEffectSloti && alGetAuxiliaryEffectSlotiv && alGetAuxiliaryEffectSlotf &&
			alGetAuxiliaryEffectSlotfv)
			bEFXSupport = AL_TRUE;
	}

	return bEFXSupport;
}

ALboolean CreateAuxEffectSlot(ALuint *puiAuxEffectSlot)
{
	ALboolean bReturn = AL_FALSE;
	alGenAuxiliaryEffectSlots(1, puiAuxEffectSlot);
	alGetError();


	if (alGetError() == AL_NO_ERROR)
		bReturn = AL_TRUE;

	return bReturn;
}

ALboolean CreateEffect(ALuint *puiEffect, ALenum eEffectType)
{
	ALboolean bReturn = AL_FALSE;

	if (puiEffect)
	{
		alGetError();

		alGenEffects(1, puiEffect);
		if (alGetError() == AL_NO_ERROR)
		{
			alEffecti(*puiEffect, AL_EFFECT_TYPE, eEffectType);
			if (alGetError() == AL_NO_ERROR)
				bReturn = AL_TRUE;
			else
				alDeleteEffects(1, puiEffect);
		}
	}

	return bReturn;
}

ALboolean SetEFXEAXReverbProperties(EFXEAXREVERBPROPERTIES *pEFXEAXReverb, ALuint uiEffect)
{
	ALboolean bReturn = AL_FALSE;

	if (pEFXEAXReverb)
	{
		alGetError();

		alEffectf(uiEffect, AL_EAXREVERB_DENSITY, pEFXEAXReverb->flDensity);
		alEffectf(uiEffect, AL_EAXREVERB_DIFFUSION, pEFXEAXReverb->flDiffusion);
		alEffectf(uiEffect, AL_EAXREVERB_GAIN, pEFXEAXReverb->flGain);
		alEffectf(uiEffect, AL_EAXREVERB_GAINHF, pEFXEAXReverb->flGainHF);
		alEffectf(uiEffect, AL_EAXREVERB_GAINLF, pEFXEAXReverb->flGainLF);
		alEffectf(uiEffect, AL_EAXREVERB_DECAY_TIME, pEFXEAXReverb->flDecayTime);
		alEffectf(uiEffect, AL_EAXREVERB_DECAY_HFRATIO, pEFXEAXReverb->flDecayHFRatio);
		alEffectf(uiEffect, AL_EAXREVERB_DECAY_LFRATIO, pEFXEAXReverb->flDecayLFRatio);
		alEffectf(uiEffect, AL_EAXREVERB_REFLECTIONS_GAIN, pEFXEAXReverb->flReflectionsGain);
		alEffectf(uiEffect, AL_EAXREVERB_REFLECTIONS_DELAY, pEFXEAXReverb->flReflectionsDelay);
		alEffectfv(uiEffect, AL_EAXREVERB_REFLECTIONS_PAN, pEFXEAXReverb->flReflectionsPan);
		alEffectf(uiEffect, AL_EAXREVERB_LATE_REVERB_GAIN, pEFXEAXReverb->flLateReverbGain);
		alEffectf(uiEffect, AL_EAXREVERB_LATE_REVERB_DELAY, pEFXEAXReverb->flLateReverbDelay);
		alEffectfv(uiEffect, AL_EAXREVERB_LATE_REVERB_PAN, pEFXEAXReverb->flLateReverbPan);
		alEffectf(uiEffect, AL_EAXREVERB_ECHO_TIME, pEFXEAXReverb->flEchoTime);
		alEffectf(uiEffect, AL_EAXREVERB_ECHO_DEPTH, pEFXEAXReverb->flEchoDepth);
		alEffectf(uiEffect, AL_EAXREVERB_MODULATION_TIME, pEFXEAXReverb->flModulationTime);
		alEffectf(uiEffect, AL_EAXREVERB_MODULATION_DEPTH, pEFXEAXReverb->flModulationDepth);
		alEffectf(uiEffect, AL_EAXREVERB_AIR_ABSORPTION_GAINHF, pEFXEAXReverb->flAirAbsorptionGainHF);
		alEffectf(uiEffect, AL_EAXREVERB_HFREFERENCE, pEFXEAXReverb->flHFReference);
		alEffectf(uiEffect, AL_EAXREVERB_LFREFERENCE, pEFXEAXReverb->flLFReference);
		alEffectf(uiEffect, AL_EAXREVERB_ROOM_ROLLOFF_FACTOR, pEFXEAXReverb->flRoomRolloffFactor);
		alEffecti(uiEffect, AL_EAXREVERB_DECAY_HFLIMIT, pEFXEAXReverb->iDecayHFLimit);

		if (alGetError() == AL_NO_ERROR)
			bReturn = AL_TRUE;
	}

	return bReturn;
}*/

void Sound::sortqueue()
{

}

ALenum Sound::stateOfBuffer()
{
    ALenum state;

    alGetSourcei(this->source, AL_SOURCE_STATE, &state);

    return state;
}
