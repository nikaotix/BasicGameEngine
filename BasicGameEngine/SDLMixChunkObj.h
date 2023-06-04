#pragma once

#include <filesystem>

#include <SDL.h>
#include <SDL_mixer.h>

#include "AudioServer.h"
#include "Util.h"

class SDLMixChunkObj
{
private:
	Mix_Chunk* chunk;
public:
	SDLMixChunkObj(SoundID id)
	{
		//make the filename
		std::string fileName = id;
		fileName.append(".wav");

		//make the full file path
		std::filesystem::path soundPath = std::filesystem::current_path();
		soundPath.append("sound");
		soundPath.append(fileName);

		chunk = Mix_LoadWAV(soundPath.u8string().c_str());

	}
	~SDLMixChunkObj()
	{
		Mix_FreeChunk(chunk);
	}

	Mix_Chunk* Chunk() { return chunk; }
};