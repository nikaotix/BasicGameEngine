#pragma once
/// <summary>
/// This component is music that can be triggered by an entity.
/// TODO: add panning/volume stuff, and some way to stop all music?
/// </summary>

typedef std::string MusicID;
const MusicID stopMusic = "STOP_MUSIC";

typedef struct
{
	MusicID MusicID;
	bool playNow;
} Music;
