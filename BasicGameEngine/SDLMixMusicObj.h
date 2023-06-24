#pragma once

#include <filesystem>

#include <SDL.h>
#include <SDL_mixer.h>

#include "AudioServer.h"
#include "Util.h"

class SDLMixMusicObj
{
private:
	Mix_Music* msc;
public:
	SDLMixMusicObj(SoundID id)
	{

		auto filename = NameToString<SoundID>("music", id, ".ogg");

		msc = Mix_LoadMUS(filename.c_str());

	}
	~SDLMixMusicObj()
	{
		Mix_FreeMusic(msc);
	}

	Mix_Music* Music() { return msc; }


};