#pragma once
#include <string>
#include "ResourceManager.h"
#include "Scene.h"

class AudioServer
{
public:

	virtual void PlaySound(SoundID id) = 0;
	
	virtual void StartMusic(MusicID id) = 0;
	virtual void StopMusic() = 0;
	
	virtual unsigned int GetSoundVolume() = 0;
	virtual void SetSoundVolume(unsigned int vol) = 0;
	
	virtual unsigned int GetMusicVolume() = 0;
	virtual void SetMusicVolume(unsigned int vol) = 0;
	
	// load unloaded sounds/music used in this scene
	// and unload sounds/music unused in this scene
	virtual void UpdateSounds(Scene& scene) = 0;
	virtual void UpdateMusic(Scene& scene) = 0;
};

