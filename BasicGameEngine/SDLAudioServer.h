#pragma once
#include <SDL.h>
#include <SDL_mixer.h>
#include <unordered_map>
#include "AudioServer.h"
#include "ResourceManagerWithoutOwner.h"
#include "SDLMixChunkObj.h"
#include "SDLMixMusicObj.h"
#include "Util.h"

#define SDL_AUDIOSERVER_FORMAT MIX_DEFAULT_FORMAT
#define SDL_AUDIOSERVER_CHANNELS 2
#define SDL_AUDIOSERVER_BUFFER 2048
class SDLAudioServer : public AudioServer
{
public:
	SDLAudioServer();
	~SDLAudioServer();

	virtual void PlaySound(SoundID id);
	virtual void StartMusic(MusicID id);
	virtual void StopMusic();
	virtual unsigned int GetSoundVolume();
	virtual void SetSoundVolume(unsigned int vol);
	virtual unsigned int GetMusicVolume();
	virtual void SetMusicVolume(unsigned int vol);

private:

	ResourceManagerWithoutOwner<SoundID, SDLMixChunkObj> soundRsrcMgr;
	ResourceManagerWithoutOwner<MusicID, SDLMixMusicObj> musicRsrcMgr;
};

