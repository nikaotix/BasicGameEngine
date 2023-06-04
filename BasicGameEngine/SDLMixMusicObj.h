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
		//make the filename
		std::string fileName = id;
		fileName.append(".wav");

		//make the full file path
		std::filesystem::path musicPath = std::filesystem::current_path();
		musicPath.append("sound");
		musicPath.append(fileName);

		msc = Mix_LoadMUS(musicPath.u8string().c_str());

	}
	~SDLMixMusicObj()
	{
		Mix_FreeMusic(msc);
	}

	Mix_Music* Music() { return msc; }


};