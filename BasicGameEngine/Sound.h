#pragma once
/// <summary>
/// This component is a sound that can be triggered by an entity.
/// TODO: add panning/volume stuff?
/// </summary>

typedef std::string SoundID;
typedef struct
{
	SoundID soundID;
	bool playNow;
} Sound;