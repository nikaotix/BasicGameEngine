#pragma once

typedef size_t SoundID;
typedef size_t MusicID;

class AudioServer
{
public:
	virtual void PlaySound(SoundID id) = 0;
	virtual void StartMusic(MusicID id) = 0;
	virtual void StopMusic() = 0;
	virtual unsigned int GetVolume() = 0;
	virtual void SetVolume(unsigned int vol) = 0;
};

