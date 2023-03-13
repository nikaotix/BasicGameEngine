#include "SDLAudioServer.h"
#include "SDLUtil.h"

SDLAudioServer::SDLAudioServer()
{
	if (SDL_Init(SDL_INIT_AUDIO) < 0)
	{
		PrintSDLError("Couldn't init SDL audio");
		return;
	}
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048)) //TODO: define these constants somewhere
	{
		PrintSDLError("Couldn't open audio device");
	}
}

SDLAudioServer::~SDLAudioServer()
{
	Mix_CloseAudio();
	SDL_QuitSubSystem(SDL_INIT_AUDIO);
}
