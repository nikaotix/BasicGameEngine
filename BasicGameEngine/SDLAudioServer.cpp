#include "SDLAudioServer.h"
#include "SDLUtil.h"

SDLAudioServer::SDLAudioServer()
{
	if (SDL_Init(SDL_INIT_AUDIO) < 0)
	{
		PrintSDLError("Couldn't init SDL audio");
		return;
	}
	if (Mix_OpenAudio(44100, SDL_AUDIOSERVER_FORMAT, SDL_AUDIOSERVER_CHANNELS, SDL_AUDIOSERVER_BUFFER))
	{
		PrintSDLError("Couldn't open audio device");
	}
}

SDLAudioServer::~SDLAudioServer()
{
	Mix_CloseAudio();
	SDL_QuitSubSystem(SDL_INIT_AUDIO);
}

void SDLAudioServer::PlaySound(SoundID id)
{
	auto lockedRsrc = soundRsrcMgr.Get(id);
	Mix_PlayChannel(-1, lockedRsrc.rsrc->Chunk(), 0);
}

void SDLAudioServer::StartMusic(MusicID id)
{
	auto lockedRsrc = musicRsrcMgr.Get(id);
	Mix_PlayMusic(lockedRsrc.rsrc->Music(), -1);
}

void SDLAudioServer::StopMusic()
{
	Mix_HaltMusic();
}

unsigned int SDLAudioServer::GetSoundVolume()
{
	return Mix_Volume(-1, -1);
}

void SDLAudioServer::SetSoundVolume(unsigned int vol)
{
	Mix_Volume(-1, vol);
}

unsigned int SDLAudioServer::GetMusicVolume()
{
	return Mix_VolumeMusic(-1);
}

void SDLAudioServer::SetMusicVolume(unsigned int vol)
{
	Mix_VolumeMusic(vol);
}