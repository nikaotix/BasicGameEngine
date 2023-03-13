#pragma once
#include <SDL.h>
#include <SDL_mixer.h>
#include "AudioServer.h"
class SDLAudioServer : public AudioServer
{
public:
	SDLAudioServer();
	~SDLAudioServer();

};

