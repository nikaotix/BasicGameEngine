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
		auto filename = NameToString<SoundID>("sounds", id, ".wav");
		chunk = Mix_LoadWAV(filename.c_str());

	}
	~SDLMixChunkObj()
	{
		Mix_FreeChunk(chunk);
	}

	Mix_Chunk* Chunk() { return chunk; }
};