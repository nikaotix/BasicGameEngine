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

void SDLAudioServer::UpdateSounds(Scene& scene)
{
	auto sounds = SceneView<Sound>(scene);
	auto soundIter = sounds.begin();
	while (soundIter != sounds.end())
	{
		Sound* snd = scene.Get<Sound>(*soundIter);

		std::cout << "playing sound : " << snd->soundID << std::endl;
		// attempt to play the sound
		if (snd->playNow)
		{
			// verify the sound is loaded
			if (!soundRsrcMgr.Check(snd->soundID))
			{
				soundRsrcMgr.Load(snd->soundID);
			}
			PlaySound(snd->soundID);
			snd->playNow = false;
		}
		++soundIter;
	}
}

void SDLAudioServer::UpdateMusic(Scene& scene)
{
	auto music = SceneView<Music>(scene);
	auto musicIter = music.begin();

	while (musicIter != music.end())
	{
		Music* msc = scene.Get<Music>(*musicIter);

		if (msc->playNow)
		{
			StopMusic();
			if (msc->MusicID == stopMusic)
			{
				return;
			}
			if (!musicRsrcMgr.Check(msc->MusicID))
			{
				musicRsrcMgr.Load(msc->MusicID);
			}
			StartMusic(msc->MusicID);
			msc->playNow = false;
		}
		++musicIter;
	}
}
